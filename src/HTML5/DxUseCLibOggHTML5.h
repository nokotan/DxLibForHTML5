// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用Ogg関係ヘッダファイル
// 
<<<<<<< HEAD
// 				Ver 3.24b
=======
// 				Ver 3.24f
>>>>>>> c642b76 ([Bot] Create Patch of 3.24f (Android))
// 
// -------------------------------------------------------------------------------

#ifndef DX_USECLIBOGGHTML5_H
#define DX_USECLIBOGGHTML5_H

// インクルード ------------------------------------------------------------------
#include "../DxCompileConfig.h"
#include "../DxLib.h"
#include "DxUseCLibOggHTML5.h"
//#include <alloca.h>

#if !defined( DX_NON_OGGVORBIS ) && !defined( DX_NON_OGGTHEORA )

//namespace DxLib
//{

// マクロ定義 --------------------------------------------------------------------

// 構造体定義 --------------------------------------------------------------------

// Ogg Theora デコード処理用環境依存データ構造体
struct DECODE_THEORA_PF
{
	int									Dummy ;
} ;

// 内部大域変数宣言 --------------------------------------------------------------

// 関数プロトタイプ宣言-----------------------------------------------------------

//}

#endif // #if !defined( DX_NON_OGGVORBIS ) || !defined( DX_NON_OGGTHEORA )

#endif // DX_USECLIBOGGHTML5_H
