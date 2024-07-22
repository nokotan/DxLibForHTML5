// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用フォント関係プログラムヘッダファイル
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

#ifndef DX_FONTHTML5_H
#define DX_FONTHTML5_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_FONT

// インクルード ------------------------------------------------------------------
#include "../DxFile.h"

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
    int FontId;
} ;

// HTML5用 フォントシステム用構造体
struct FONTSYSTEM_HTML5
{
	int 					initialized;
} ;

// 内部大域変数宣言 --------------------------------------------------------------

extern FONTSYSTEM_HTML5 FontSystemHTML5 ;

// 関数プロトタイプ宣言-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_FONT

#endif // DX_FONTHTML5_H
