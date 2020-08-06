// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用入力情報プログラムヘッダファイル
// 
// 				Ver 3.21d
// 
// -------------------------------------------------------------------------------

#ifndef DX_INPUTANDROID_H
#define DX_INPUTANDROID_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_INPUT

// インクルード ------------------------------------------------------------------
#include "../DxLib.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

#define ANDR_INPUT_LOG_NUM					(64)
#define ANDR_DEVICE_MAX_NUM					(64)
#define ANDR_INPUT_SOURCE_NUM				(64)
#define ANDR_POINTER_MAX_NUM				(256)
#define ANDR_KEYCODE_MAX					(320)

// 入力ソース
#define HTML5_INPUT_SOURCE_UNKNOWN			(0)
#define HTML5_INPUT_SOURCE_KEYBOARD			(1)
#define HTML5_INPUT_SOURCE_TOUCHSCREEN		(2)
#define HTML5_INPUT_SOURCE_MOUSE			(3)
#define HTML5_INPUT_SOURCE_JOYSTICK			(4)



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
struct INPUT_ANDROID_DEVICE_INFO
{
	int32_t					Source ;
	int32_t					DeviceId ;
	LONGLONG				UpdateCount ;
	BYTE					KeyState[ ANDR_KEYCODE_MAX ] ;
	int32_t					ButtonState ;
	BYTE					PointerState[ ANDR_POINTER_MAX_NUM ] ;
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
} ;

// 入力システム用環境依存データ構造体型
struct INPUTSYSTEMDATA_PF
{
	LONGLONG					UpdateCount ;
	int							UseInputInfoNum ;
	INPUT_ANDROID_DEVICE_INFO	InputInfo[ ANDR_DEVICE_MAX_NUM ] ;
	int							SourceNum[ ANDR_INPUT_SOURCE_NUM ] ;
	int							SourceNoToInputInfoTable[ ANDR_INPUT_SOURCE_NUM ][ ANDR_DEVICE_MAX_NUM ] ;
	int							GamePadSourceNum ;											// ゲームパッドの数
	int							GamePadSourceNoToInputInfoTable[ ANDR_DEVICE_MAX_NUM ] ;	// ゲームパッドのナンバーと InputInfoTable の対応テーブル 
	TOUCHINPUTDATA				TouchInputData ;
} ;

// 内部大域変数宣言 --------------------------------------------------------------

// 関数プロトタイプ宣言-----------------------------------------------------------

extern	int GetAndroidDeviceIdToInputInfoNo( int32_t Source, int32_t DeviceId ) ;	// デバイスＩＤから値を代入すべき入力情報番号を取得する
extern	int RefreshAndroidSourceNoToInputInfoTable( int32_t Source ) ;				// 入力ソース番号と入力情報との対応テーブルを更新する
extern	int RefreshAndroidGamePadSourceNoToInputInfoTable( void ) ;					// ゲームパッドの番号と入力情報との対応テーブルを更新する
extern	int32_t ProcessInputEvent( ) ;												// 入力イベントを処理する

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_INPUT

#endif // DX_INPUTANDROID_H
