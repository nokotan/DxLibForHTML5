// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		Objective-C メソッド呼び出し用プログラムヘッダファイル
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

// インクルード ------------------------------------------------------------------

// マクロ定義 --------------------------------------------------------------------

// 構造体定義 --------------------------------------------------------------------

// テーブル-----------------------------------------------------------------------

// 内部大域変数宣言 --------------------------------------------------------------

// 関数プロトタイプ宣言-----------------------------------------------------------

class DxObjectiveCPP_Class
{
public:
	static void NSLog( const char *format, ... ) ;
	static int GetDocumentPath( char *Buffer, int BufferBytes ) ;
	static int GetLibrary_CachesPath( char *Buffer, int BufferBytes ) ;
	static int GetTmpPath( char *Buffer, int BufferBytes ) ;
} ;
