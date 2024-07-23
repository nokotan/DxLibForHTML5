//-----------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用ログプログラム
// 
<<<<<<< HEAD
//  	Ver 3.24b
=======
//  	Ver 3.24d
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
// 
//-----------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

// インクルード ---------------------------------------------------------------
#ifndef DX_NON_LOG

#include "DxLogHTML5.h"
#include "DxFileHTML5.h"
#include "DxSystemHTML5.h"
#include "../DxStatic.h"
#include "../DxLib.h"
#include "../DxLog.h"
#include "../DxBaseFunc.h"
#include "../DxMemory.h"
#include "../DxGraphics.h"
#include "DxGraphicsHTML5.h"
<<<<<<< HEAD
#include <stdio.h>
#include <wchar.h>
=======
#include <wchar.h>
#include <android/log.h>
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 -----------------------------------------------------------------

<<<<<<< HEAD
#define LOGI(...) ((void)printf(__VA_ARGS__))
#define LOGW(...) ((void)printf(__VA_ARGS__))
=======
#define LOGI(...) ((void)__android_log_print(HTML5_LOG_INFO, "DxLibLog", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(HTML5_LOG_WARN, "DxLibLog", __VA_ARGS__))
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)

// 構造体宣言 -----------------------------------------------------------------

// データ定義 -----------------------------------------------------------------

// 関数宣言 -------------------------------------------------------------------

// プログラム -----------------------------------------------------------------

// ログファイルを初期化する処理の環境依存部分
extern int LogFileInitialize_PF( const wchar_t *LogFilePath )
{
	// 既に初期化済みの場合は何もしない
	if( LogData.PF.InitializeFlag == TRUE )
	{
		return 0 ;
	}

	// 初期化フラグを立てる
	LogData.PF.InitializeFlag = TRUE ;

<<<<<<< HEAD
=======
	// エラーログファイルのパスをコピー
	if( g_HTML5Sys.NativeActivity == NULL ||
		g_HTML5Sys.NativeActivity->externalDataPath == NULL )
	{
		LogData.PF.ExternalDataPath[ 0 ] = 0 ;
	}
	else
	{
		CL_strcpy_s( DX_CHARCODEFORMAT_UTF8, LogData.PF.ExternalDataPath, sizeof( LogData.PF.ExternalDataPath ), g_HTML5Sys.NativeActivity->externalDataPath ) ;
	}

>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
	// エラーログファイルを再作成する
	if( LogData.PF.ExternalDataPath[ 0 ] != '\0' )
	{
		char TempLogFilePath[ 1024 ] ;
		char LogFileNameUTF8[ 256 ] ;
		int Length ;

		ConvString( ( char * )LogData.LogFileName, -1, WCHAR_T_CHARCODEFORMAT, LogFileNameUTF8, sizeof( LogFileNameUTF8 ), DX_CHARCODEFORMAT_UTF8 ) ;

		Length = CL_strlen( DX_CHARCODEFORMAT_UTF8, LogData.PF.ExternalDataPath ) ;
		if( Length + CL_strlen( DX_CHARCODEFORMAT_UTF8, LogFileNameUTF8 ) + 1 < sizeof( TempLogFilePath ) - 16 )
		{
			FILE *fp ;

			CL_strcpy( DX_CHARCODEFORMAT_UTF8, TempLogFilePath, LogData.PF.ExternalDataPath ) ;
			if( TempLogFilePath[ Length - 1 ] != '/' )
			{
				TempLogFilePath[ Length ] = '/' ;
				TempLogFilePath[ Length + 1 ] = '\0' ;
			}
			CL_strcat( DX_CHARCODEFORMAT_UTF8, TempLogFilePath, LogFileNameUTF8 ) ;
			remove( TempLogFilePath ) ;
			fp = fopen( TempLogFilePath, "wb" ) ;
			if( fp != NULL )
			{
				BYTE HEAD[ 3 ] = { 0xef, 0xbb, 0xbf } ;
				fwrite( &HEAD, 3, 1, fp ) ;

				fclose( fp ) ;
			}
		}
	}

	// 終了
	return 0 ;
}

// ログファイルの後始末の環境依存部分
extern int LogFileTerminate_PF( void )
{
	return 0 ;
}

// ログファイルへ文字列を書き出す処理の環境依存部分
extern int LogFileAdd_WCHAR_T_PF( const wchar_t *LogFilePath, const wchar_t *ErrorStr )
{
	char ErrorStrDefaultBuffer[ 1024 ] ;
	char *ErrorStrTempBuffer = NULL ;
	char *ErrorStrUseBuffer = NULL ;
	int ErrorStrUseBufferBytes ;
	int Bytes ;
	int StringBytes ;

	// UTF8 の文字列に変換する
	StringBytes = ( ( int )_WCSLEN( ErrorStr ) + 1 ) * sizeof( wchar_t ) ;
	if( ( size_t )StringBytes > sizeof( ErrorStrDefaultBuffer ) )
	{
		ErrorStrTempBuffer = ( char * )DXALLOC( StringBytes ) ;
		if( ErrorStrTempBuffer == NULL )
		{
			return -1 ;
		}
		ErrorStrUseBuffer = ErrorStrTempBuffer ;
		ErrorStrUseBufferBytes = StringBytes ;
	}
	else
	{
		ErrorStrUseBuffer = ErrorStrDefaultBuffer ;
		ErrorStrUseBufferBytes = sizeof( ErrorStrDefaultBuffer ) ;
	}

	Bytes = ConvString( ( char * )ErrorStr, -1, WCHAR_T_CHARCODEFORMAT, ErrorStrUseBuffer, ErrorStrUseBufferBytes, DX_CHARCODEFORMAT_UTF8 ) ;

	// エラーログファイルを開く
	if( Bytes > 1 &&
		LogData.PF.ExternalDataPath[ 0 ] != '\0' )
	{
		char TempLogFilePath[ 1024 ] ;
		char LogFileNameUTF8[ 256 ] ;
		int Length ;

		ConvString( ( char * )LogData.LogFileName, -1, WCHAR_T_CHARCODEFORMAT, LogFileNameUTF8, sizeof( LogFileNameUTF8 ), DX_CHARCODEFORMAT_UTF8 ) ;

		Length = CL_strlen( DX_CHARCODEFORMAT_UTF8, LogData.PF.ExternalDataPath ) ;
		if( Length + CL_strlen( DX_CHARCODEFORMAT_UTF8, LogFileNameUTF8 ) + 1 < sizeof( TempLogFilePath ) - 16 )
		{
			FILE *fp ;

			CL_strcpy( DX_CHARCODEFORMAT_UTF8, TempLogFilePath, LogData.PF.ExternalDataPath ) ;
			if( TempLogFilePath[ Length - 1 ] != '/' )
			{
				TempLogFilePath[ Length ] = '/' ;
				TempLogFilePath[ Length + 1 ] = '\0' ;
			}
			CL_strcat( DX_CHARCODEFORMAT_UTF8, TempLogFilePath, LogFileNameUTF8 ) ;
			fp = fopen( TempLogFilePath, "ab" ) ;
			if( fp != NULL )
			{
				// エラーログファイルに書き出す
				fwrite( ErrorStrUseBuffer, ( DWORD )( Bytes - 1 ), 1, fp ) ;

				// ファイルを閉じる
				fclose( fp ) ;
			}
		}
	}

	// コンソールにも出力
	LOGI( "%s", ErrorStrUseBuffer ) ;

	if( ErrorStrTempBuffer != NULL )
	{
		DXFREE( ErrorStrTempBuffer ) ;
		ErrorStrTempBuffer = NULL ;
	}

	// 終了
	return 0 ;
}


// ログ機能の初期化を行うかどうかを取得する
extern int IsInitializeLog( void )
{
	return TRUE ;
}


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_LOG

