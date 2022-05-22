// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		iOS専用関数プロトタイプ宣言用ヘッダファイル
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

#ifndef DX_FUNCTIONIOS_H
#define DX_FUNCTIONIOS_H

// インクルード ------------------------------------------------------------------
#include "DxLib.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{
    
#endif // DX_NON_NAMESPACE

extern int LoadImageFromBrowser(STREAMDATA *Src, BASEIMAGE *BaseImage, int GetFormatOnly);

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_FUNCTIONIOS_H

