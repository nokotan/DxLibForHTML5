//-----------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用BaseImageプログラム
// 
//  	Ver 3.24b
// 
//-----------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

// インクルード ---------------------------------------------------------------
#include "DxBaseImageHTML5.h"
#include "../DxStatic.h"
#include "../DxMemory.h"
#include "../DxBaseFunc.h"

#include <emscripten.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 -----------------------------------------------------------------

// 構造体宣言 -----------------------------------------------------------------

typedef struct tagDECODEDIMAGE
{
	BYTE* DecodedImage;
	int Length;
	int Width;
	int Height;
} DECODEDIMAGE;

// 関数宣言 -------------------------------------------------------------------

// データ定義 -----------------------------------------------------------------

int ( *DefaultImageLoadFunc_PF[] )( STREAMDATA *Src, BASEIMAGE *BaseImage, int GetFormatOnly ) =
{
	NULL
} ;

// プログラム -----------------------------------------------------------------

// 環境依存初期化・終了関数
int DecodeImageOnBrowser(BYTE* Src, int Size, DECODEDIMAGE* Decoded) {
#ifdef ASYNCIFY
	return EM_ASM_INT({
		return Asyncify.handleSleep(function(wakeUp) {
			if (!Module["decodeCanvas"]) {
				Module["decodeCanvas"] = document.createElement('canvas');
				Module["decodeContext"] = Module["decodeCanvas"].getContext("2d");
			}

			const imageData = new Uint8ClampedArray(HEAPU8.buffer, Src, Size);
			const imageBlob = new Blob([ imageData ]);
			const image = new Image();

			image.onload = function() {
				Module["decodeCanvas"].width = image.width;
				Module["decodeCanvas"].height = image.height;
				Module["decodeContext"].drawImage(image, 0, 0);

				const decodedImageData = Module["decodeContext"].getImageData(0, 0, image.width, image.height).data;
				const dataBuffer = Module["_malloc"](decodedImageData.length);

				HEAPU8.set(decodedImageData, dataBuffer);

				HEAPU32[(Decoded>>2)+0] = dataBuffer;
				HEAPU32[(Decoded>>2)+1] = decodedImageData.length;
				HEAPU32[(Decoded>>2)+2] = image.width;
				HEAPU32[(Decoded>>2)+3] = image.height;

				URL.revokeObjectURL(image.src);
				wakeUp(0);
			};
			image.onerror = function() {
				URL.revokeObjectURL(image.src);
				wakeUp(-1);
			};
			image.src = URL.createObjectURL(imageBlob);
		})
	});
#else
	return 0;
#endif
}

// 基本イメージ管理情報の環境依存処理の初期化
extern int InitializeBaseImageManage_PF( void )
{
	return 0 ;
}

// 基本イメージ管理情報の環境依存処理の後始末
extern int TerminateBaseImageManage_PF( void )
{
	return 0 ;
}

extern int LoadImageFromBrowser(STREAMDATA *Stream, BASEIMAGE *BaseImage, int GetFormatOnly)
{
	DWORD_PTR sp;
	STREAMDATASHRED *sstr;
	size_t FileSize;
	BYTE *ImageData = NULL;
	BYTE *DecodedImageData = NULL;
	size_t DecodedImageSize;
	DECODEDIMAGE DecodedImage;

	{
		sstr = &Stream->ReadShred ;
		sp   = Stream->DataPoint ;

		// ファイルサイズを得る
		sstr->Seek( sp, 0, STREAM_SEEKTYPE_END ) ;
		FileSize = ( size_t )sstr->Tell( sp ) ;
		sstr->Seek( sp, 0, STREAM_SEEKTYPE_SET ) ;
	}

	// デコード後のデータを格納するメモリ領域の確保
	ImageData = (BYTE *)DXALLOC( ( size_t )FileSize ) ;	
	if( ImageData == NULL ) goto ERR ;
	if( ( sstr->Read( ImageData, sizeof(BYTE), FileSize, sp ) ) <= 0 ) goto ERR ;
	if( DecodeImageOnBrowser(ImageData, FileSize, &DecodedImage) == -1 ) goto ERR ;

	DecodedImageSize = ( size_t )(DecodedImage.Width *  DecodedImage.Height * 4);
	DecodedImageData = (BYTE *)DXALLOC( DecodedImageSize ) ;	
	_MEMCPY(DecodedImageData, DecodedImage.DecodedImage, DecodedImageSize);

	{
		BaseImage->Width = DecodedImage.Width;
		BaseImage->Height = DecodedImage.Height;
		BaseImage->Pitch = DecodedImage.Width * 4;
		BaseImage->GraphData = DecodedImageData;

		// アルファチャンネルありにする
		NS_CreateFullColorData( &BaseImage->ColorData ) ;
		BaseImage->ColorData.ColorBitDepth	= 32 ;
		BaseImage->ColorData.PixelByte		= 4 ;
		BaseImage->ColorData.AlphaLoc		= 24 ;
		BaseImage->ColorData.AlphaWidth		= 8 ;
		BaseImage->ColorData.AlphaMask		= 0xff000000 ;
		BaseImage->ColorData.BlueLoc		= 16 ;
		BaseImage->ColorData.BlueWidth		= 8 ;
		BaseImage->ColorData.BlueMask		= 0x00ff0000 ;
		BaseImage->ColorData.GreenLoc		= 8 ;
		BaseImage->ColorData.GreenWidth		= 8 ;
		BaseImage->ColorData.GreenMask		= 0x0000ff00 ;
		BaseImage->ColorData.RedLoc			= 0 ;
		BaseImage->ColorData.RedWidth		= 8 ;
		BaseImage->ColorData.RedMask		= 0x000000ff ;
	}

	DXFREE(ImageData);
	free(DecodedImage.DecodedImage);
	
	return 0;

ERR:
	DXFREE(ImageData);

	return -1;
}

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

