// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用フォント関係プログラムヘッダファイル
// 
// 				Ver 3.21d
// 
// -------------------------------------------------------------------------------

#ifndef DX_FONTHTML5_H
#define DX_FONTHTML5_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_FONT

// インクルード ------------------------------------------------------------------
#include "../DxFile.h"
#include <ft2build.h>

#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H
#include FT_GLYPH_H
#include FT_TRUETYPE_IDS_H

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

#define FSYSHTML5			FontSystemHTML5

// 構造体定義 --------------------------------------------------------------------

/* Cached glyph information */
typedef struct cached_glyph {
    int stored;
    FT_UInt index;
    FT_Bitmap bitmap;
    FT_Bitmap pixmap;
    int minx;
    int maxx;
    int miny;
    int maxy;
    int yoffset;
    int advance;
    uint16_t cached;
} c_glyph;

// HTML5用 フォントキャッシュの環境依存管理データ
struct FONTMANAGE_PF
{
   /* Freetype2 maintains all sorts of useful info itself */
    FT_Face face;

    /* We'll cache these ourselves */
    int width;
    int height;
    int ascent;
    int descent;
    int lineskip;

    /* The font style */
    int italic;
    int style;
    int outline;

    /* Whether kerning is desired */
    int kerning;

    /* Extra width in glyph bounds for text styles */
    int glyph_overhang;
    float glyph_italics;

    /* Information in the font for underlining */
    int underline_offset;
    int underline_height;

    /* We are responsible for closing the font stream */
    int src;
    int freesrc;
    FT_Open_Args args;

    /* For non-scalable formats, we must remember which font index size */
    int font_size_family;

    /* really just flags passed into FT_Load_Glyph */
    int hinting;
} ;

// HTML5用 フォントシステム用構造体
struct FONTSYSTEM_HTML5
{
	int 					initialized;
	FT_Library 				library;
} ;

// 内部大域変数宣言 --------------------------------------------------------------

extern FONTSYSTEM_HTML5 FontSystemHTML5 ;

// 関数プロトタイプ宣言-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_FONT

#endif // DX_FONTHTML5_H
