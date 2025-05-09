// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用BaseImageプログラムヘッダファイル
// 
// 				Ver 3.24d
// 
// -------------------------------------------------------------------------------

#ifndef DX_BASEIMAGEHTML5_H
#define DX_BASEIMAGEHTML5_H

// インクルード ------------------------------------------------------------------
#include "../DxCompileConfig.h"
#include "../DxLib.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

// 構造体定義 --------------------------------------------------------------------

// 内部大域変数宣言 --------------------------------------------------------------

// 関数プロトタイプ宣言-----------------------------------------------------------

extern int SaveBaseImage(const char *pFilePathW, const char *pFilePathA, BASEIMAGE *BaseImage, int ImageSaveType, double Quality);

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_BASEIMAGEHTML5_H
