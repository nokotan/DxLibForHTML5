// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用ログプログラムヘッダファイル
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

#ifndef DX_LOGHTML5_H
#define DX_LOGHTML5_H

// インクルード ------------------------------------------------------------------
#include "../DxCompileConfig.h"

#ifndef DX_NON_LOG

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

// 構造体定義 --------------------------------------------------------------------

// ログ処理用環境依存データ構造体
struct LOGDATA_PF
{
	int		InitializeFlag ;
	char	ExternalDataPath[ 2048 ] ;
	FILE	*fp ;
} ;

// テーブル-----------------------------------------------------------------------

// 内部大域変数宣言 --------------------------------------------------------------

// 関数プロトタイプ宣言-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_LOG

#endif // DX_LOGHTML5_H
