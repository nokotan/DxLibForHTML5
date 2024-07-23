// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用入力情報プログラムヘッダファイル
// 
<<<<<<< HEAD
// 				Ver 3.24b
=======
// 				Ver 3.24d
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
// 
// -------------------------------------------------------------------------------

#ifndef DX_INPUTHTML5_H
#define DX_INPUTHTML5_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_INPUT

// インクルード ------------------------------------------------------------------
#include "../DxLib.h"
<<<<<<< HEAD
=======
#include <HTML5/input.h>
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

#define HTML5_INPUT_LOG_NUM					(64)
#define HTML5_DEVICE_MAX_NUM					(64)
<<<<<<< HEAD
#define HTML5_INPUT_SOURCE_NUM				(64)
=======
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)
#define HTML5_POINTER_MAX_NUM				(256)
#define HTML5_KEYCODE_MAX					(320)

// 入力ソース
#define HTML5_INPUT_SOURCE_UNKNOWN			(0)
#define HTML5_INPUT_SOURCE_KEYBOARD			(1)
<<<<<<< HEAD
#define HTML5_INPUT_SOURCE_TOUCHSCREEN		(2)
#define HTML5_INPUT_SOURCE_MOUSE			(3)
#define HTML5_INPUT_SOURCE_JOYSTICK			(4)


=======
#define HTML5_INPUT_SOURCE_DPAD				(2)
#define HTML5_INPUT_SOURCE_GAMEPAD			(3)
#define HTML5_INPUT_SOURCE_TOUCHSCREEN		(4)
#define HTML5_INPUT_SOURCE_MOUSE				(5)
#define HTML5_INPUT_SOURCE_STYLUS			(6)
#define HTML5_INPUT_SOURCE_TRACKBALL			(7)
#define HTML5_INPUT_SOURCE_TOUCHPAD			(8)
#define HTML5_INPUT_SOURCE_TOUCH_NAVIGATION	(9)
#define HTML5_INPUT_SOURCE_JOYSTICK			(10)
#define HTML5_INPUT_SOURCE_NUM				(11)
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)

// 構造体定義 --------------------------------------------------------------------

// 振動の環境依存情報
struct INPUTVIBRATIONDATA_PF
{
	int						Dummy ;
} ;

// ゲームパッドの環境依存情報
struct INPUTPADDATA_PF
{
	int						Dummy ;
} ;

// 一つの入力デバイスの入力情報
struct INPUT_HTML5_DEVICE_INFO
{
	int32_t					Source ;
	int32_t					DeviceId ;
	LONGLONG				UpdateCount ;
	BYTE					KeyState[ HTML5_KEYCODE_MAX ] ;
	int32_t					ButtonState ;
	BYTE					PointerState[ HTML5_POINTER_MAX_NUM ] ;
	float					AxisX ;
	float					AxisY ;
	float					AxisZ ;
	float					AxisRx ;
	float					AxisRy ;
	float					AxisRz ;
	float					AxisHatX ;
	float					AxisHatY ;
	float					AxisLTrigger ;
	float					AxisRTrigger ;
	float					Wheel ;
	float					VScroll ;
	float					HScroll ;
	float					Pressure ;
	float					Size ;
	float					TouchMajor ;
	float					TouchMinor ;
	float					ToolMajor ;
	float					ToolMinor ;
	float					Orientation ;
	float					Tilt ;
	float					Distance ;
} ;

// 入力システム用環境依存データ構造体型
struct INPUTSYSTEMDATA_PF
{
	LONGLONG					UpdateCount ;
	int							UseInputInfoNum ;
	INPUT_HTML5_DEVICE_INFO	InputInfo[ HTML5_DEVICE_MAX_NUM ] ;
	int							SourceNum[ HTML5_INPUT_SOURCE_NUM ] ;
	int							SourceNoToInputInfoTable[ HTML5_INPUT_SOURCE_NUM ][ HTML5_DEVICE_MAX_NUM ] ;
	int							GamePadSourceNum ;											// ゲームパッドの数
	int							GamePadSourceNoToInputInfoTable[ HTML5_DEVICE_MAX_NUM ] ;	// ゲームパッドのナンバーと InputInfoTable の対応テーブル 
	TOUCHINPUTDATA				TouchInputData ;
	float						MouseX ;													// マウスカーソルのX座標
	float						MouseY ;													// マウスカーソルのY座標
} ;

// 内部大域変数宣言 --------------------------------------------------------------

// 関数プロトタイプ宣言-----------------------------------------------------------

extern	int GetHTML5DeviceIdToInputInfoNo( int32_t Source, int32_t DeviceId ) ;	// デバイスＩＤから値を代入すべき入力情報番号を取得する
extern	int RefreshHTML5SourceNoToInputInfoTable( int32_t Source ) ;				// 入力ソース番号と入力情報との対応テーブルを更新する
extern	int RefreshHTML5GamePadSourceNoToInputInfoTable( void ) ;					// ゲームパッドの番号と入力情報との対応テーブルを更新する
<<<<<<< HEAD
extern	int32_t ProcessInputEvent( ) ;												// 入力イベントを処理する
=======
extern	int32_t ProcessInputEvent( AInputEvent* event ) ;							// 入力イベントを処理する
>>>>>>> b66228f ([Bot] Update Android Part before 3.24d)

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_INPUT

#endif // DX_INPUTHTML5_H
