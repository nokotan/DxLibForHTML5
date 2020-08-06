// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用サウンドデータ変換プログラムヘッダファイル
// 
// 				Ver 3.21d
// 
// -------------------------------------------------------------------------------

#ifndef DX_SOUNDCONVERTHTML5_H
#define DX_SOUNDCONVERTHTML5_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_SOUND

// インクルード ------------------------------------------------------------------
#include "../DxLib.h"
#include "../DxSoundConvert.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

// 構造体定義 --------------------------------------------------------------------

// サウンド変換処理全体で使用するデータ構造体で HTML5 に依存している情報の構造体
struct SOUNDCONVERTDATA_HTML5
{
	int							Dummy ;
} ;

// 内部大域変数宣言 --------------------------------------------------------------

// 関数プロトタイプ宣言-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_SOUND

#endif // DX_SOUNDCONVERTHTML5_H
