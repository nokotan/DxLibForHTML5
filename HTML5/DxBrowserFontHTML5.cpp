//-----------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用フォント関係プログラム
// 
//  	Ver 3.23 
// 
//-----------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

#if !defined(DX_NON_FONT) && defined(DX_USE_BROWSER_FONT)

// インクルード ---------------------------------------------------------------
#include "DxBrowserFontHTML5.h"
#include "DxBaseFuncHTML5.h"
#include "DxSystemHTML5.h"
#include "../DxFont.h"
#include "../DxFile.h"
#include "../DxMemory.h"
#include "../DxBaseFunc.h"
#include "../DxSystem.h"
#include "../DxArchive_.h"
#include "../DxLog.h"

#include <emscripten.h>
#include <math.h>
#include <stdint.h>

#define FT_FLOOR(X) ((X & -64) / 64)
#define FT_CEIL(X)  (((X + 63) & -64) / 64)

/* FIXME: Right now we assume the gray-scale renderer Freetype is using
   supports 256 shades of gray, but we should instead key off of num_grays
   in the result FT_Bitmap after the FT_Render_Glyph() call. */
#define NUM_GRAYS       256

// #define DEBUG_FONTS

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 -----------------------------------------------------------------

// 構造体宣言 -----------------------------------------------------------------
typedef struct tagFONTDATA 
{
    BYTE* Bitmap;
    int BitmapWidth;
    int BitmapHeight;
    int BitmapLeft;
    int BitmapTop;
    float AdvanceX;
} FONTDATA;

// データ定義 -----------------------------------------------------------------

FONTSYSTEM_HTML5 FontSystemHTML5 ;

// 関数宣言 -------------------------------------------------------------------

// プログラム -----------------------------------------------------------------

// フォントの HTML5 専用データを解放する
static int TerminateFontHandle_HTML5( FONTMANAGE *ManageData )
{            
	// 終了
	return 0 ;
}

EM_JS(int, InitializeFontRenderingOnBrowser, (), {
    
    Module["DxLib"].TextRenderingCanvas = document.createElement('canvas');
    Module["DxLib"].TextRenderingContext = Module["DxLib"].TextRenderingCanvas.getContext("2d");

    Module["DxLib"].NextFontDataId = 1;
    Module["DxLib"].FontData = [];
    
    return 0;
})

// InitFontManage の環境依存処理を行う関数
extern int InitFontManage_PF( void )
{
	InitializeFontRenderingOnBrowser();

	FontSystemHTML5.initialized = TRUE;
    return 0;
}

// TermFontManage の環境依存処理を行う関数
extern int TermFontManage_PF( void )
{
	return 0 ;
}



EM_JS(int, CreateFontOnBrowser, (char* FontName, int FontSize), {
    const FontNameString = UTF8ToString(FontName);
    const FontSpec = `${FontSize}px '${FontNameString}'`;

    const id = Module["DxLib"].NextFontDataId++;
    Module["DxLib"].FontData[id] = {
        font: FontSpec,
        size: FontSize
    };
    return id;
})

// CreateFontToHandle の環境依存処理を行う関数
extern int CreateFontToHandle_PF( CREATEFONTTOHANDLE_GPARAM *GParam, FONTMANAGE *ManageData, int DefaultCharSet )
{
	// フォントデータファイルを使用する場合は何もせずに終了
	if( ManageData->UseFontDataFile )
	{
		return 0 ;
	}

	int ptSize = ManageData->BaseInfo.FontSize;
	FONTMANAGE_PF* font = ManageData->PF;

    if ( ! FontSystemHTML5.initialized ) {
        return -1;
    }

	{
		char UTF8_FontName[ 128 * 4 ] ;	
		 int FontId = 0;

		ConvString( ( char * )ManageData->FontName, -1, WCHAR_T_CHARCODEFORMAT, UTF8_FontName, sizeof( UTF8_FontName ), DX_CHARCODEFORMAT_UTF8 ) ;
		FontId = CreateFontOnBrowser(UTF8_FontName, ptSize);

        font->FontId = FontId;
    }

    {
        ManageData->BaseInfo.FontHeight    = ptSize ;
		ManageData->BaseInfo.FontAddHeight = 0 ;
		ManageData->BaseInfo.MaxWidth      = ptSize;
		ManageData->BaseInfo.Ascent        = ptSize;
    }

	// 戻り値を返す
	return 0 ;
}

// CreateFontToHandle の環境依存エラー処理を行う関数
extern int CreateFontToHandle_Error_PF( FONTMANAGE * ManageData )
{
	// 解放処理を実行
	TerminateFontHandle_HTML5( ManageData ) ;

	// 終了
	return 0 ;
}

// TerminateFontHandle の環境依存処理を行う関数
extern int TerminateFontHandle_PF( FONTMANAGE *ManageData )
{
	// 解放処理を実行
	TerminateFontHandle_HTML5( ManageData ) ;

	// 終了
	return 0 ;
}

// SetupFontCache の環境依存処理を行う関数
extern int SetupFontCache_PF( CREATEFONTTOHANDLE_GPARAM * /* GParam */, FONTMANAGE * /* ManageData */, int /* ASyncThread */ )
{
	// 特に何もしない
	return 0 ;
}

// FontCacheCharaAddToHandleの環境依存処理を行う関数( 実行箇所区別 0 )
extern int FontCacheCharAddToHandle_Timing0_PF( FONTMANAGE *ManageData )
{
	// とくにすること無し
	return 0 ;
}

EM_JS(int, RenderFontBitmap, (int FontId, DWORD CharCode, FONTDATA* FontData), {
    const font = Module["DxLib"].FontData[FontId].font;
    const size = Module["DxLib"].FontData[FontId].size;

    Module["DxLib"].TextRenderingContext.fillStyle = "0xfff";
    Module["DxLib"].TextRenderingContext.font = font;
    Module["DxLib"].TextRenderingContext.textBaseline = "bottom";

    const text = String.fromCharCode(CharCode);
    const textMetrix = Module["DxLib"].TextRenderingContext.measureText(text);
    const fontWidth = Math.ceil(Math.abs(textMetrix.actualBoundingBoxLeft) + Math.abs(textMetrix.actualBoundingBoxRight)) || 1;
    const fontHeight = Math.ceil(Math.abs(textMetrix.actualBoundingBoxAscent) + Math.abs(textMetrix.actualBoundingBoxDescent)) || 1;
    const fontXAdvance = textMetrix.width;

    Module["DxLib"].TextRenderingContext.clearRect(0, 0, Module["DxLib"].TextRenderingCanvas.width, Module["DxLib"].TextRenderingCanvas.height);
    Module["DxLib"].TextRenderingContext.fillText(text, Math.abs(textMetrix.actualBoundingBoxLeft), fontHeight);

    const textBitmap = Module["DxLib"].TextRenderingContext.getImageData(0, 0, fontWidth, fontHeight).data;
    const dataBuffer = Module["_malloc"](textBitmap.length);

    HEAPU8.set(textBitmap, dataBuffer);

    HEAP32[FontData>>2] = dataBuffer; FontData += 4;                            // buffer
    HEAP32[FontData>>2] = fontWidth; FontData += 4;                             // width
    HEAP32[FontData>>2] = fontHeight; FontData += 4;                            // height
    HEAP32[FontData>>2] = textMetrix.actualBoundingBoxLeft; FontData += 4;      // left
    HEAP32[FontData>>2] = size - textMetrix.actualBoundingBoxAscent; FontData += 4; // top
    HEAPF32[FontData>>2] = fontXAdvance; FontData += 4;                         // xAdvance

    return 0;
})

// FontCacheCharaAddToHandleの環境依存処理を行う関数( 実行箇所区別 1 )
extern int FontCacheCharAddToHandle_Timing1_PF( FONTMANAGE *ManageData, FONTCHARDATA *CharData, DWORD CharCode, DWORD IVSCode, int TextureCacheUpdate )
{
    int Space;

	FONTMANAGE_PF* font = ManageData->PF;
    FONTDATA FontData;
    size_t BitmapSize;
    BYTE *AlphaChannel = NULL;

	// スペースかどうかを取得しておく
	Space = CharCode == L' ' ? 1 : ( CharCode == ( DWORD )FSYS.DoubleByteSpaceCharCode ? 2 : 0 ) ;

    if ( !font || !font->FontId ) {
        DXST_LOGFILEFMT_ADDA(("Font Error: Parameter is NULL!\n"));
        return -1;
    }

    RenderFontBitmap(font->FontId, CharCode, &FontData);
    BitmapSize = FontData.BitmapWidth * FontData.BitmapHeight;

    AlphaChannel = (BYTE*)DXALLOC(BitmapSize);

    {
        BYTE* pSrc = FontData.Bitmap;
        BYTE* pDst = AlphaChannel;
        int i;

        for (i = 0; i < BitmapSize; i++)
        {
            *pDst = *(pSrc + 3);
            if (*pDst < 64) {
                *pDst = 0;
            }
            pSrc += 4;
            pDst += 1;
        }
    }

    {
        if (Space != 0) {
            FontCacheCharImageBltToHandle(
                ManageData,
                CharData,
                CharCode,
                IVSCode,
                TRUE,
                DX_FONT_SRCIMAGETYPE_8BIT_ON_OFF,
                NULL,
                0,
                0,
                0,
                0,
                0,
                FontData.AdvanceX, 
                FALSE
            );
        } else {
            FontCacheCharImageBltToHandle(
                ManageData,
                CharData,
                CharCode,
                IVSCode,
                FALSE,
                DX_FONT_SRCIMAGETYPE_8BIT_ON_OFF,
                AlphaChannel,
                FontData.BitmapWidth,
                FontData.BitmapHeight,
                FontData.BitmapWidth,
                FontData.BitmapLeft,
                FontData.BitmapTop,
                FontData.AdvanceX, 
                TextureCacheUpdate
            );
        }
    }

    DXFREE(AlphaChannel);

	// 戻り値を返す
	return 0 ;
}

// FontCacheCharaAddToHandleの環境依存処理を行う関数( 実行箇所区別 2 )
extern int FontCacheCharAddToHandle_Timing2_PF( FONTMANAGE *ManageData )
{
	// 特に何もしない
	return 0 ;
}

// EnumFontName の環境依存処理を行う関数
extern int EnumFontName_PF( ENUMFONTDATA *EnumFontData, int IsEx, int CharSet )
{
	// 正常終了
	return 0 ;
}



#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE


#endif // DX_NON_FONT

