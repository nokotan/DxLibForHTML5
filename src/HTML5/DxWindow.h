// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用システムプログラムヘッダファイル
// 
// 				Ver 3.24b
// 
// -------------------------------------------------------------------------------

#ifndef DX_WINDOWHTML5_H
#define DX_WINDOWHTML5_H

// インクルード ------------------------------------------------------------------
#include "../DxCompileConfig.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// 関数プロトタイプ宣言-----------------------------------------------------------

// 初期化終了系関数
extern int			InitializeWindow( void ) ;												// ウインドウ関係の初期化関数

extern void         UpdateMainWindowSize( void ) ;

extern void         GetMainWindowSize( int* Width, int* Height ) ;

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_SYSTEMHTML5_H
