// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用システムプログラムヘッダファイル
// 
<<<<<<< HEAD
// 				Ver 3.24b
=======
// 				Ver 3.24d
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
// 
// -------------------------------------------------------------------------------

#ifndef DX_SYSTEMHTML5_H
#define DX_SYSTEMHTML5_H

// インクルード ------------------------------------------------------------------
#include "../DxCompileConfig.h"
#include <pthread.h>
#include <sched.h>
<<<<<<< HEAD
#include <GLES2/gl2.h>
=======
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

// ソフトがアクティブかどうかをチェックする
#define CheckActiveState()					\
		if( g_HTML5Sys.NonActiveRunFlag == FALSE )\
		{\
			DxActiveWait_HTML5() ;\
		}

// 構造体定義 --------------------------------------------------------------------

struct DXLIB_HTML5_SYSTEMINFO
{
<<<<<<< HEAD
=======
	volatile int				NonActiveRunFlag ;					// アプリがアクティブではなくても処理を実行するかどうかのフラグ

	pthread_t					SoftThread ;						// ソフト実行用スレッド
	volatile int				SoftThreadRunning ;					// ソフト実行用スレッドの実行が開始されたかどうか( 0:開始されていない  1:開始された )
	volatile int				SoftThreadDestroyedStart ;			// ソフト実行用スレッドの終了処理を開始したかどうか( 0:開始されていない  1:開始された )
	volatile int				SoftThreadDestroyed ;				// ソフト実行用スレッドが終了したかどうか( 0:終了していない  1:終了した )
	volatile int				SoftThreadWait ;					// ソフト実行用スレッドが待ち状態かどうか( 1:待ち状態  0:実行状態 )

	volatile int				SoundAndMoviePause ;				// ウインドウが非アクティブになりサウンドと動画が一時停止しているかどうか( TRUE:一時停止している  FALSE:一時停止していない )

>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	volatile void				( *LostFocusCallbackFunction )( void *Data ) ;		// アプリのフォーカスが失われた際に呼ばれるコールバック関数
	volatile void				*LostFocusCallbackFunctionData ;					// アプリのフォーカスが失われた際に呼ばれるコールバック関数に渡すポインタ
	volatile void				( *GainedFocusCallbackFunction )( void *Data ) ;	// アプリのフォーカスが得られた際に呼ばれるコールバック関数
	volatile void				*GainedFocusCallbackFunctionData ;					// アプリのフォーカスが得られた際に呼ばれるコールバック関数に渡すポインタ
<<<<<<< HEAD
	
	volatile int				NonActiveRunFlag ;					// アプリがアクティブではなくても処理を実行するかどうかのフラグ

	int							ViewWidth;
	int							ViewHeight;
	GLuint						ViewFrameBuffer ;					// フレームバッファ
	GLuint						ViewDepthBuffer ;					// フレームバッファ
	GLuint						ViewRenderBuffer ;					// フレームバッファ
=======
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
} ;

// テーブル-----------------------------------------------------------------------

// 内部大域変数宣言 --------------------------------------------------------------

extern DXLIB_HTML5_SYSTEMINFO g_HTML5Sys ;
extern int g_HTML5RunFlag ;

// 関数プロトタイプ宣言-----------------------------------------------------------

// アクティブになるまで何もしない
extern void DxActiveWait_HTML5( void ) ;

// アプリの外部データ保存用のディレクトリパスを取得する
extern int GetDocumentsDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

// アプリのデータ保存用のディレクトリパスを取得する
extern int GetLibraryPreferencesDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

// アプリのキャッシュファイル保存用のディレクトリパスを取得する
extern int GetLibraryCachesDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

// アプリの一時ファイル保存用のディレクトリパスを取得する
extern int GetTmpDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

<<<<<<< HEAD
extern int GetGraphicsViewFramebufferInfo( unsigned int *ViewFrameBuffer, int *Width, int *Height ) ;

extern void GraphicsViewRenderBufferPresent( void ) ;

=======
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

<<<<<<< HEAD
=======
// C++ 側での初期化を行う
extern int DxSystemInitialize_CPP( void ) ;



>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
#endif // DX_SYSTEMHTML5_H
