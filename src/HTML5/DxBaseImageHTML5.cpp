//-----------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用BaseImageプログラム
// 
//  	Ver 3.24d
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
#include "../DxFile.h"
#include "../DxChar.h"

#include <emscripten.h>
#include <emscripten/threading.h>
#include <emscripten/proxying.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 -----------------------------------------------------------------

// 構造体宣言 -----------------------------------------------------------------

typedef struct tagDECODEDIMAGE
{
	BYTE* SrcImage;
	int SrcLength;
	BYTE* DecodedImage;
	int Length;
	int Width;
	int Height;
} DECODEDIMAGE;

typedef struct tagENCODEDIMAGE
{
	BYTE* SrcImage;
	int SrcLength;
	BYTE* EncodedImage;
	int Length;
	int Width;
	int Height;
	int ImageSaveType;
	float Quality;
} ENCODEDIMAGE;

// 関数宣言 -------------------------------------------------------------------

static int LoadImageFromBrowser(STREAMDATA *Stream, BASEIMAGE *BaseImage, int GetFormatOnly);

// データ定義 -----------------------------------------------------------------

int ( *DefaultImageLoadFunc_PF[] )( STREAMDATA *Src, BASEIMAGE *BaseImage, int GetFormatOnly ) =
{
	LoadImageFromBrowser,
	NULL
} ;

// プログラム -----------------------------------------------------------------

#ifdef PROXY_TO_PTHREAD
EM_JS(void, DecodeImage, (em_proxying_ctx* ctx, void* Decoded),
#else
EM_JS(void, DecodeImage, (DECODEDIMAGE* Decoded),
#endif
	{
		function DecodeImageImpl(wakeUp) {
			if (!Module["decodeCanvas"]) {
				Module["decodeCanvas"] = document.createElement('canvas');
				Module["decodeContext"] = Module["decodeCanvas"].getContext("2d");
			}

			const Src = HEAPU32[(Decoded>>2)+0];
			const Size = HEAPU32[(Decoded>>2)+1];

			const imageData = new Uint8ClampedArray(HEAPU8.buffer, Src, Size);
			const clonedData = new ArrayBuffer(Size);
			const clonedDataView = new Uint8ClampedArray(clonedData);
			clonedDataView.set(imageData);
			const imageBlob = new Blob([ clonedDataView ]);

			const image = new Image();

			image.onload = function() {
				Module["decodeCanvas"].width = image.width;
				Module["decodeCanvas"].height = image.height;
				Module["decodeContext"].drawImage(image, 0, 0);

				const decodedImageData = Module["decodeContext"].getImageData(0, 0, image.width, image.height).data;
				const dataBuffer = _malloc(decodedImageData.length);

				HEAPU8.set(decodedImageData, dataBuffer);

				HEAPU32[(Decoded>>2)+2] = dataBuffer;
				HEAPU32[(Decoded>>2)+3] = decodedImageData.length;
				HEAPU32[(Decoded>>2)+4] = image.width;
				HEAPU32[(Decoded>>2)+5] = image.height;

				URL.revokeObjectURL(image.src);
				wakeUp();
			};
			image.onerror = function() {
				HEAPU32[(Decoded>>2)+2] = 0;

				URL.revokeObjectURL(image.src);
				wakeUp();
			};
			image.src = URL.createObjectURL(imageBlob);
		}

#ifdef ASYNCIFY
		return Asyncify.handleSleep(DecodeImageImpl);
#elif defined(PROXY_TO_PTHREAD)
		DecodeImageImpl(function() {
			_emscripten_proxy_finish(ctx);
		});
#endif
	}
);

// 環境依存初期化・終了関数
static int DecodeImageOnBrowser(DECODEDIMAGE* Decoded) {

#ifdef ASYNCIFY
	DecodeImage(Decoded);
#elif defined(PROXY_TO_PTHREAD)
	auto defaultQueue = emscripten_proxy_get_system_queue();
	emscripten_proxy_sync_with_ctx(
		defaultQueue,
		emscripten_main_runtime_thread_id(),
		&DecodeImage,
		(void*)Decoded);
#endif

	return (Decoded->DecodedImage != NULL ? 0 : -1);
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

static int LoadImageFromBrowser(STREAMDATA *Stream, BASEIMAGE *BaseImage, int GetFormatOnly)
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

	{
		DecodedImage.SrcImage = ImageData ;
		DecodedImage.SrcLength = FileSize ;
	}

	if( DecodeImageOnBrowser(&DecodedImage) == -1 ) goto ERR ;

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

#ifdef PROXY_TO_PTHREAD
EM_JS(void, EncodeImage, (em_proxying_ctx* ctx, void* Encoded),
#else
EM_JS(void, EncodeImage, (DECODEDIMAGE* Encoded),
#endif
	{
		function EncodeImageImpl(wakeUp) {
			if (!Module["encodeCanvas"]) {
				Module["encodeCanvas"] = document.createElement('canvas');
				Module["encodeContext"] = Module["encodeCanvas"].getContext("2d");
			}

			const Src = HEAPU32[(Encoded>>2)+0];
			const Size = HEAPU32[(Encoded>>2)+1];
			const rawImageData = new Uint8ClampedArray(HEAPU8.buffer, Src, Size);
			const width = HEAPU32[(Encoded>>2)+4];
			const height = HEAPU32[(Encoded>>2)+5];

			const imageSaveType = HEAPU32[(Encoded>>2)+6];
			const quality = HEAPF32[(Encoded>>2)+7];
		
			const imageData = new ImageData(width, height);
			imageData.data.set(rawImageData);

			Module["encodeCanvas"].width = width;
			Module["encodeCanvas"].height = height;
			Module["encodeContext"].putImageData(imageData, 0, 0);

			Module["encodeCanvas"].toBlob(
				async function(blob) {
					const encodedImageData = await blob.arrayBuffer();
					const encodedImageDataView = new Uint8Array(encodedImageData);

					const dataBuffer = _malloc(encodedImageDataView.byteLength);
					HEAPU8.set(encodedImageDataView, dataBuffer);

					HEAPU32[(Encoded>>2)+2] = dataBuffer;
					HEAPU32[(Encoded>>2)+3] = encodedImageDataView.byteLength;

					wakeUp();
				},
				imageSaveType == 1 ? "image/jpeg" : "image/png",
				quality
			);
		}

#ifdef ASYNCIFY
		return Asyncify.handleSleep(DecodeImageImpl);
#elif defined(PROXY_TO_PTHREAD)
		EncodeImageImpl(function() {
			_emscripten_proxy_finish(ctx);
		});
#endif
	}
);

static int EncodeImageOnBrowser(ENCODEDIMAGE* Encoded) {

#ifdef ASYNCIFY
	EncodeImage(Encoded);
#elif defined(PROXY_TO_PTHREAD)
	auto defaultQueue = emscripten_proxy_get_system_queue();
	emscripten_proxy_sync_with_ctx(
		defaultQueue,
		emscripten_main_runtime_thread_id(),
		&EncodeImage,
		(void*)Encoded);
#endif

	return (Encoded->EncodedImage != NULL ? 0 : -1);
}

extern int SaveBaseImage(const char *pFilePathW, const char *pFilePathA, BASEIMAGE *BaseImage, int ImageSaveType, double Quality)
{
	DWORD_PTR fp ;
	char*  buffer = NULL ;
	char*  sample;
	int r, g, b, a, i, j;
	ENCODEDIMAGE EncodedImage;

	// 保存用のファイルを開く
	if( pFilePathW )
	{
		fp = WriteOnlyFileAccessOpenWCHAR( pFilePathW ) ;
	}
	else
	{
		char TempBuffer[ 1024 ] ;

		ConvString( pFilePathA, -1, CHAR_CHARCODEFORMAT, TempBuffer, sizeof( TempBuffer ), WCHAR_T_CHARCODEFORMAT ) ;
		fp = WriteOnlyFileAccessOpenWCHAR( TempBuffer ) ;
	}
	if( fp == 0 ) return -1;

	// 圧縮用データの用意
	{
		// バッファの確保
		buffer = (char*)DXALLOC( sizeof( char* ) * BaseImage->Width * BaseImage->Height );
		if( buffer == NULL ) goto ERR;
		_MEMSET( buffer, 0, sizeof( char* ) * BaseImage->Width * BaseImage->Height );
		sample = buffer;
		for( i = 0; i < BaseImage->Height; i++ )
		{
			for( j = 0; j < BaseImage->Width; j ++, sample += 4 )
			{
				NS_GetPixelBaseImage( BaseImage, j, i, &r, &g, &b, &a );
				sample[0] = (char)r;
				sample[1] = (char)g;
				sample[2] = (char)b;
				sample[3] = (char)a;
			}		
		}
	}

	{
		EncodedImage.SrcImage = (BYTE*)buffer;
		EncodedImage.SrcLength = BaseImage->Width * BaseImage->Height * 4;
		EncodedImage.Width = BaseImage->Width;
		EncodedImage.Height = BaseImage->Height;
		EncodedImage.ImageSaveType = ImageSaveType;
		EncodedImage.Quality = (float)Quality;

		if( EncodeImageOnBrowser(&EncodedImage) == -1 ) goto ERR ;
		
		WriteOnlyFileAccessWrite( fp, EncodedImage.EncodedImage, EncodedImage.Length ) ;
		free( EncodedImage.EncodedImage );
	}

	if( buffer )
	{		
		DXFREE( buffer );
	}
	if( fp ) WriteOnlyFileAccessClose( fp );
	return 0;
ERR:
	if( buffer )
	{		
		DXFREE( buffer );
	}
	if( fp ) WriteOnlyFileAccessClose( fp );
	return -1;
}

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

