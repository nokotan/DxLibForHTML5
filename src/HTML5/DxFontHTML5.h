// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用フォント関係プログラムヘッダファイル
// 
<<<<<<< HEAD
// 				Ver 3.24b
=======
// 				Ver 3.24d
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
// 
// -------------------------------------------------------------------------------

#ifndef DX_FONTHTML5_H
#define DX_FONTHTML5_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_FONT

// インクルード ------------------------------------------------------------------
#include "../DxFile.h"
<<<<<<< HEAD
#include <ft2build.h>

#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H
#include FT_GLYPH_H
#include FT_TRUETYPE_IDS_H
=======
#include <jni.h>
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

#define FSYSHTML5			FontSystemHTML5

// 構造体定義 --------------------------------------------------------------------

<<<<<<< HEAD
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
=======
// HTML5用 フォントキャッシュの環境依存管理データ
struct FONTMANAGE_PF
{
	int						ReferenceNumUp ;						// Javaオブジェクトの参照数を増やしているか

	jobject					object_Bitmap ;							// 文字の出力結果を一時的に保存する Bitmap
	jobject					object_Canvas ;							// 文字の出力を行うための Canvas
	jobject					object_Paint ;							// 文字の出力を行うための Paint
	jobject					object_Typeface ;						// 文字のフォントタイプなどを指定するための Typeface
	jobject					object_OldTypeface ;					// Paint に最初から設定されていた Typeface

	jint					BitmapSizeX ;							// 文字の出力結果を一時的に保存する Bitmap のサイズX
	jint					BitmapSizeY ;							// 文字の出力結果を一時的に保存する Bitmap のサイズY
	jintArray				intArray_ClearBitmapBuffer ;			// 文字の出力結果の Bitmap をクリアするための int配列
	jintArray				intArray_BitmapBuffer ;					// 文字の出力結果を取得するための int配列
	void					*ImageBuffer ;							// 文字の出力結果をテクスチャに転送する形にしたものを保存するためのバッファ

	float					PaintFontMetrics_ascent ;				// 使用するフォントの ascent
	float					PaintFontMetrics_bottom ;				// 使用するフォントの bottom
	float					PaintFontMetrics_descent ;				// 使用するフォントの descent
	float					PaintFontMetrics_leading ;				// 使用するフォントの leading
	float					PaintFontMetrics_top ;					// 使用するフォントの top
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
} ;

// HTML5用 フォントシステム用構造体
struct FONTSYSTEM_HTML5
{
<<<<<<< HEAD
	int 					initialized;
	FT_Library 				library;
=======
	int						Dummy ;
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
} ;

// 内部大域変数宣言 --------------------------------------------------------------

extern FONTSYSTEM_HTML5 FontSystemHTML5 ;

// 関数プロトタイプ宣言-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_FONT

#endif // DX_FONTHTML5_H
