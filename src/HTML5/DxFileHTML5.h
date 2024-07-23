// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用ファイル関係プログラムヘッダファイル
// 
<<<<<<< HEAD
// 				Ver 3.24b
=======
// 				Ver 3.24d
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
// 
// -------------------------------------------------------------------------------

#ifndef DX_FILEHTML5_H
#define DX_FILEHTML5_H

// インクルード ------------------------------------------------------------------
#include "../DxCompileConfig.h"
#include "../DxThread.h"
<<<<<<< HEAD
=======
#include <android/asset_manager.h>
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

// 構造体定義 --------------------------------------------------------------------

// HTML5用ファイルアクセス処理用構造体
struct FILEACCESS_PF
{
<<<<<<< HEAD
=======
	AAsset					*Asset ;							// ファイルアクセス用アセット
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
	FILE					*FilePointer ;						// ファイルアクセス用ファイルポインタ
} ;

// ファイル検索処理用構造体
struct FINDINFO_PF
{
<<<<<<< HEAD
=======
	AAssetDir				*AssetDir ;							// ディレクトリアクセス用アセットディレクトリ
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
	DIR						*Dir ;								// ディレクトリアクセス用ディレクトリ
	wchar_t					SearchFileName[ 1024 ] ;			// 検索ファイル名
} ;

// ファイルアクセス処理が使用するグローバルデータの環境依存データ構造体
struct FILEMANAGEDATA_PF
{
<<<<<<< HEAD
=======
	AAssetManager *			AssetManagerP ;
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
	const char *			InternalDataPath ;
	int						InternalDataPathLength ;
	const char *			ExternalDataPath ;
	int						ExternalDataPathLength ;
} ;

// テーブル-----------------------------------------------------------------------

// 内部大域変数宣言 --------------------------------------------------------------

// 関数プロトタイプ宣言-----------------------------------------------------------

<<<<<<< HEAD
=======
extern void SetAssetManager( AAssetManager *AManager ) ;
extern void SetInternalAndExternalDataPath( const char *InternalDataPath, const char *ExternalDataPath ) ;

>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_FILEHTML5_H
