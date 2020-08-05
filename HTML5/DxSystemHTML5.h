// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		iOS用システムプログラムヘッダファイル
// 
// 				Ver 3.21d
// 
// -------------------------------------------------------------------------------

#ifndef DX_SYSTEMIOS_H
#define DX_SYSTEMIOS_H

// インクルード ------------------------------------------------------------------
#include "../DxCompileConfig.h"
#include <pthread.h>
#include <sched.h>
#include <GLES2/gl2.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

// ソフトがアクティブかどうかをチェックする
#define CheckActiveState()					\
		if( g_iOSSys.NonActiveRunFlag == FALSE )\
		{\
			DxActiveWait_iOS() ;\
		}

// 構造体定義 --------------------------------------------------------------------

struct DXLIB_IOS_SYSTEMINFO
{
	volatile void				( *LostFocusCallbackFunction )( void *Data ) ;		// アプリのフォーカスが失われた際に呼ばれるコールバック関数
	volatile void				*LostFocusCallbackFunctionData ;					// アプリのフォーカスが失われた際に呼ばれるコールバック関数に渡すポインタ
	volatile void				( *GainedFocusCallbackFunction )( void *Data ) ;	// アプリのフォーカスが得られた際に呼ばれるコールバック関数
	volatile void				*GainedFocusCallbackFunctionData ;					// アプリのフォーカスが得られた際に呼ばれるコールバック関数に渡すポインタ
	
	volatile int				NonActiveRunFlag ;					// アプリがアクティブではなくても処理を実行するかどうかのフラグ

	int							ViewWidth;
	int							ViewHeight;
	GLuint						ViewFrameBuffer ;					// フレームバッファ
	GLuint						ViewDepthBuffer ;					// フレームバッファ
	GLuint						ViewRenderBuffer ;					// フレームバッファ
} ;

// テーブル-----------------------------------------------------------------------

// 内部大域変数宣言 --------------------------------------------------------------

extern DXLIB_IOS_SYSTEMINFO g_iOSSys ;
extern int g_iOSRunFlag ;

// 関数プロトタイプ宣言-----------------------------------------------------------

// アクティブになるまで何もしない
extern void DxActiveWait_iOS( void ) ;

// アプリの外部データ保存用のディレクトリパスを取得する
extern int GetDocumentsDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

// アプリのデータ保存用のディレクトリパスを取得する
extern int GetLibraryPreferencesDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

// アプリのキャッシュファイル保存用のディレクトリパスを取得する
extern int GetLibraryCachesDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

// アプリの一時ファイル保存用のディレクトリパスを取得する
extern int GetTmpDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

extern int GetGraphicsViewFramebufferInfo( unsigned int *ViewFrameBuffer, int *Width, int *Height ) ;

extern void GraphicsViewRenderBufferPresent( void ) ;

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_SYSTEMIOS_H
