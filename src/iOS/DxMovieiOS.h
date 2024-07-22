// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		iOS用動画プログラムヘッダファイル
// 
// 				Ver 3.24b
// 
// -------------------------------------------------------------------------------

#ifndef DX_MOVIEIOS_H
#define DX_MOVIEIOS_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_MOVIE

// インクルード ------------------------------------------------------------------
#include "../DxLib.h"
#include "../DxFile.h"
//#include <videodec.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

// 構造体定義 --------------------------------------------------------------------

// ムービーグラフィック環境依存データ型
struct MOVIEGRAPH_PF
{
	int							Dummy ;
} ;

// ムービーデータ環境依存管理構造体
struct MOVIEGRAPHMANAGE_PF
{
	int						Dummy ;
} ;

// 内部大域変数宣言 --------------------------------------------------------------

// 関数プロトタイプ宣言-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_MOVIE

#endif // DX_MOVIEIOS_H
