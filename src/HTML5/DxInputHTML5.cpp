//-----------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用入力情報プログラム
// 
//  	Ver 3.24b
// 
//-----------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_INPUT

// インクルード----------------------------------------------------------------
#include "DxInputHTML5.h"
#include "DxSystemHTML5.h"
#include "../DxLog.h"
#include "../DxInput.h"
#include "../DxSystem.h"

#include "DxInputKeyCodesHTML5.h"
#include <emscripten/html5.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義------------------------------------------------------------------

#define DEADZONE_XINPUT( ZONE )				(short)( 32767 * (ZONE) / 65536)
#define DEADZONE_XINPUT_TRIGGER( ZONE )		(short)(   255 * (ZONE) / 65536)
#define VALIDRANGE_XINPUT( ZONE )			( 32767 - DEADZONE_XINPUT(ZONE))
#define VALIDRANGE_XINPUT_TRIGGER( ZONE )	(   255 - DEADZONE_XINPUT_TRIGGER(ZONE))

// 型定義----------------------------------------------------------------------

// 定数定義 ----------------------------------------------------------------------

// データ宣言------------------------------------------------------------------

const static unsigned char g_HTML5InputSourceTable[ HTML5_INPUT_SOURCE_NUM ] =
{
	HTML5_INPUT_SOURCE_UNKNOWN,
	HTML5_INPUT_SOURCE_KEYBOARD,
	HTML5_INPUT_SOURCE_TOUCHSCREEN,
	HTML5_INPUT_SOURCE_MOUSE,
	HTML5_INPUT_SOURCE_JOYSTICK
} ;

const static unsigned char g_HTML5KeyToDXInputKey[][ 2 /* 0:HTML5キーコード  1:DirectInputキーコード  */ ] =
{
	{ HTML_KEYCODE_BACK,		KEY_INPUT_BACK },		// BackSpaceキー
	{ HTML_KEYCODE_TAB,			KEY_INPUT_TAB },		// Tabキー
	{ HTML_KEYCODE_RETURN,		KEY_INPUT_RETURN },		// Enterキー

	{ HTML_KEYCODE_LSHIFT,		KEY_INPUT_LSHIFT },		// 左Shiftキー
	{ HTML_KEYCODE_RSHIFT,		KEY_INPUT_RSHIFT },		// 右Shiftキー
	{ HTML_KEYCODE_LCONTROL,	KEY_INPUT_LCONTROL },	// 左Ctrlキー
	{ HTML_KEYCODE_RCONTROL,	KEY_INPUT_RCONTROL },	// 右Ctrlキー
	{ HTML_KEYCODE_ESCAPE,		KEY_INPUT_ESCAPE },		// Escキー
	{ HTML_KEYCODE_SPACE,		KEY_INPUT_SPACE },		// スペースキー
	{ HTML_KEYCODE_PGUP,		KEY_INPUT_PGUP },		// PageUpキー
	{ HTML_KEYCODE_PGDN,		KEY_INPUT_PGDN },		// PageDownキー
	{ HTML_KEYCODE_END,			KEY_INPUT_END },		// Endキー
	{ HTML_KEYCODE_HOME,		KEY_INPUT_HOME },		// Homeキー
	{ HTML_KEYCODE_LEFT,		KEY_INPUT_LEFT },		// 左キー
	{ HTML_KEYCODE_UP,			KEY_INPUT_UP },			// 上キー
	{ HTML_KEYCODE_RIGHT,		KEY_INPUT_RIGHT },		// 右キー
	{ HTML_KEYCODE_DOWN,		KEY_INPUT_DOWN },		// 下キー
	{ HTML_KEYCODE_INSERT,		KEY_INPUT_INSERT },		// Insertキー
	{ HTML_KEYCODE_DELETE,		KEY_INPUT_DELETE },		// Deleteキー


	{ HTML_KEYCODE_MINUS,			KEY_INPUT_MINUS },		// −キー
	{ HTML_KEYCODE_YEN,				KEY_INPUT_YEN },		// ￥キー
	{ HTML_KEYCODE_PREVTRACK,		KEY_INPUT_PREVTRACK },	// ＾キー
	{ HTML_KEYCODE_PERIOD,			KEY_INPUT_PERIOD },		// ．キー
	{ HTML_KEYCODE_SLASH,			KEY_INPUT_SLASH },		// ／キー
	{ HTML_KEYCODE_LALT,			KEY_INPUT_LALT },		// 左Altキー
	{ HTML_KEYCODE_RALT,			KEY_INPUT_RALT },		// 右Altキー
	{ HTML_KEYCODE_SCROLL,			KEY_INPUT_SCROLL },		// ScrollLockキー
	{ HTML_KEYCODE_SEMICOLON,		KEY_INPUT_SEMICOLON },	// ；キー
	{ HTML_KEYCODE_COLON,			KEY_INPUT_COLON },		// ：キー
	{ HTML_KEYCODE_LBRACKET,		KEY_INPUT_LBRACKET },	// ［キー
	{ HTML_KEYCODE_RBRACKET,		KEY_INPUT_RBRACKET },	// ］キー
	{ HTML_KEYCODE_AT,				KEY_INPUT_AT },			// ＠キー
	{ HTML_KEYCODE_BACKSLASH,		KEY_INPUT_BACKSLASH },	// ＼キー
	{ HTML_KEYCODE_COMMA,			KEY_INPUT_COMMA },		// ，キー
//	{ HTML_KEYCODE_ZENKAKU_HANKAKU,	KEY_INPUT_KANJI },		// 漢字キー
//	{ HTML_KEYCODE_HENKAN,			KEY_INPUT_CONVERT },	// 変換キー
//	{ HTML_KEYCODE_MUHENKAN,		KEY_INPUT_NOCONVERT },	// 無変換キー
//	{ HTML_KEYCODE_KANA,			KEY_INPUT_KANA },		// カナキー
//	{ HTML_KEYCODE_APPS,			KEY_INPUT_APPS },		// アプリケーションメニューキー
//	{ HTML_KEYCODE_CAPSLOCK,		KEY_INPUT_CAPSLOCK },	// CaspLockキー
//	{ HTML_KEYCODE_SYSRQ,			KEY_INPUT_SYSRQ },		// PrintScreenキー
	{ HTML_KEYCODE_PAUSE,			KEY_INPUT_PAUSE },		// PauseBreakキー
	{ HTML_KEYCODE_LWIN,			KEY_INPUT_LWIN },		// 左Winキー
	{ HTML_KEYCODE_RWIN,			KEY_INPUT_RWIN },		// 右Winキー

	{ HTML_KEYCODE_NUMLOCK,		KEY_INPUT_NUMLOCK },	// テンキーNumLockキー
	{ HTML_KEYCODE_NUMPAD0,		KEY_INPUT_NUMPAD0 },	// テンキー０
	{ HTML_KEYCODE_NUMPAD1,		KEY_INPUT_NUMPAD1 },	// テンキー１
	{ HTML_KEYCODE_NUMPAD2,		KEY_INPUT_NUMPAD2 },	// テンキー２
	{ HTML_KEYCODE_NUMPAD3,		KEY_INPUT_NUMPAD3 },	// テンキー３
	{ HTML_KEYCODE_NUMPAD4,		KEY_INPUT_NUMPAD4 },	// テンキー４
	{ HTML_KEYCODE_NUMPAD5,		KEY_INPUT_NUMPAD5 },	// テンキー５
	{ HTML_KEYCODE_NUMPAD6,		KEY_INPUT_NUMPAD6 },	// テンキー６
	{ HTML_KEYCODE_NUMPAD7,		KEY_INPUT_NUMPAD7 },	// テンキー７
	{ HTML_KEYCODE_NUMPAD8,		KEY_INPUT_NUMPAD8 },	// テンキー８
	{ HTML_KEYCODE_NUMPAD9,		KEY_INPUT_NUMPAD9 },	// テンキー９
	{ HTML_KEYCODE_MULTIPLY,	KEY_INPUT_MULTIPLY },	// テンキー＊キー
	{ HTML_KEYCODE_ADD,			KEY_INPUT_ADD },		// テンキー＋キー
	{ HTML_KEYCODE_SUBTRACT,	KEY_INPUT_SUBTRACT },	// テンキー−キー
	{ HTML_KEYCODE_DECIMAL,		KEY_INPUT_DECIMAL },	// テンキー．キー
	{ HTML_KEYCODE_DIVIDE,		KEY_INPUT_DIVIDE },		// テンキー／キー
	{ HTML_KEYCODE_NUMPADENTER,	KEY_INPUT_NUMPADENTER },// テンキーのエンターキー

	{ HTML_KEYCODE_F1,				KEY_INPUT_F1 },			// Ｆ１キー
	{ HTML_KEYCODE_F2,				KEY_INPUT_F2 },			// Ｆ２キー
	{ HTML_KEYCODE_F3,				KEY_INPUT_F3 },			// Ｆ３キー
	{ HTML_KEYCODE_F4,				KEY_INPUT_F4 },			// Ｆ４キー
	{ HTML_KEYCODE_F5,				KEY_INPUT_F5 },			// Ｆ５キー
	{ HTML_KEYCODE_F6,				KEY_INPUT_F6 },			// Ｆ６キー
	{ HTML_KEYCODE_F7,				KEY_INPUT_F7 },			// Ｆ７キー
	{ HTML_KEYCODE_F8,				KEY_INPUT_F8 },			// Ｆ８キー
	{ HTML_KEYCODE_F9,				KEY_INPUT_F9 },			// Ｆ９キー
	{ HTML_KEYCODE_F10,				KEY_INPUT_F10 },		// Ｆ１０キー
	{ HTML_KEYCODE_F11,				KEY_INPUT_F11 },		// Ｆ１１キー
	{ HTML_KEYCODE_F12,				KEY_INPUT_F12 },		// Ｆ１２キー

	{ HTML_KEYCODE_A,				KEY_INPUT_A },			// Ａキー
	{ HTML_KEYCODE_B,				KEY_INPUT_B },			// Ｂキー
	{ HTML_KEYCODE_C,				KEY_INPUT_C },			// Ｃキー
	{ HTML_KEYCODE_D,				KEY_INPUT_D },			// Ｄキー
	{ HTML_KEYCODE_E,				KEY_INPUT_E },			// Ｅキー
	{ HTML_KEYCODE_F,				KEY_INPUT_F },			// Ｆキー
	{ HTML_KEYCODE_G,				KEY_INPUT_G },			// Ｇキー
	{ HTML_KEYCODE_H,				KEY_INPUT_H },			// Ｈキー
	{ HTML_KEYCODE_I,				KEY_INPUT_I },			// Ｉキー
	{ HTML_KEYCODE_J,				KEY_INPUT_J },			// Ｊキー
	{ HTML_KEYCODE_K,				KEY_INPUT_K },			// Ｋキー
	{ HTML_KEYCODE_L,				KEY_INPUT_L },			// Ｌキー
	{ HTML_KEYCODE_M,				KEY_INPUT_M },			// Ｍキー
	{ HTML_KEYCODE_N,				KEY_INPUT_N },			// Ｎキー
	{ HTML_KEYCODE_O,				KEY_INPUT_O },			// Ｏキー
	{ HTML_KEYCODE_P,				KEY_INPUT_P },			// Ｐキー
	{ HTML_KEYCODE_Q,				KEY_INPUT_Q },			// Ｑキー
	{ HTML_KEYCODE_R,				KEY_INPUT_R },			// Ｒキー
	{ HTML_KEYCODE_S,				KEY_INPUT_S },			// Ｓキー
	{ HTML_KEYCODE_T,				KEY_INPUT_T },			// Ｔキー
	{ HTML_KEYCODE_U,				KEY_INPUT_U },			// Ｕキー
	{ HTML_KEYCODE_V,				KEY_INPUT_V },			// Ｖキー
	{ HTML_KEYCODE_W,				KEY_INPUT_W },			// Ｗキー
	{ HTML_KEYCODE_X,				KEY_INPUT_X },			// Ｘキー
	{ HTML_KEYCODE_Y,				KEY_INPUT_Y },			// Ｙキー
	{ HTML_KEYCODE_Z,				KEY_INPUT_Z },			// Ｚキー

	{ HTML_KEYCODE_0,				KEY_INPUT_0 },			// ０キー
	{ HTML_KEYCODE_1,				KEY_INPUT_1 },			// １キー
	{ HTML_KEYCODE_2,				KEY_INPUT_2 },			// ２キー
	{ HTML_KEYCODE_3,				KEY_INPUT_3 },			// ３キー
	{ HTML_KEYCODE_4,				KEY_INPUT_4 },			// ４キー
	{ HTML_KEYCODE_5,				KEY_INPUT_5 },			// ５キー
	{ HTML_KEYCODE_6,				KEY_INPUT_6 },			// ６キー
	{ HTML_KEYCODE_7,				KEY_INPUT_7 },			// ７キー
	{ HTML_KEYCODE_8,				KEY_INPUT_8 },			// ８キー
	{ HTML_KEYCODE_9,				KEY_INPUT_9 },			// ９キー

	{ HTML_KEYCODE_BACK,			KEY_INPUT_ESCAPE },		// HTML5 の Backボタン

	{ 0xff,					0xff },
} ;

// 関数プロトタイプ宣言 -------------------------------------------------------

static EM_BOOL onKeyAction(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);
static EM_BOOL onMouseWheel(int eventType, const EmscriptenWheelEvent *wheelEvent, void *userData);
static EM_BOOL onMouseAction(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
static EM_BOOL onTouchAction(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData);
static EM_BOOL onGamepadAction(int eventType, const EmscriptenGamepadEvent *gamepadEvent, void *userData);

// プログラム------------------------------------------------------------------

// 入力システムを初期化する処理の環境依存処理
extern int InitializeInputSystem_PF_Timing0( void )
{
	static int NowInitialize = FALSE ;
	int i, j ;

	// 既に初期化処理が開始されている場合も何もせずに終了
	if( NowInitialize )
	{
		return 0 ;
	}

	// 初期化中フラグを立てる
	NowInitialize = TRUE ;

	// 無効ゾーンのセット
	for( i = 0 ; i < MAX_JOYPAD_NUM ; i ++ )
	{
		InputSysData.Pad[ i ].DeadZone = InputSysData.PadDefaultDeadZone ;
		InputSysData.Pad[ i ].DeadZoneD = InputSysData.PadDefaultDeadZoneD ;
	}

	// キーボードとジョイパッドの入力のデフォルトの対応表を設定する
	if( InputSysData.KeyToJoypadInputInitializeFlag == FALSE )
	{
		InputSysData.KeyToJoypadInputInitializeFlag = TRUE ;

		for( i = 0 ; i < MAX_JOYPAD_NUM ; i ++ )
		{
			for ( j = 0 ; j < 32 ; j ++ )
			{
				InputSysData.KeyToJoypadInput[ i ][ j ][ 0 ] = -1 ;
				InputSysData.KeyToJoypadInput[ i ][ j ][ 1 ] = -1 ;
			}
		}
		InputSysData.KeyToJoypadInput[ 0 ][  0 ][ 0 ] = KEY_INPUT_NUMPAD2 ;
		InputSysData.KeyToJoypadInput[ 0 ][  0 ][ 1 ] = KEY_INPUT_DOWN ;
		InputSysData.KeyToJoypadInput[ 0 ][  1 ][ 0 ] = KEY_INPUT_NUMPAD4 ;
		InputSysData.KeyToJoypadInput[ 0 ][  1 ][ 1 ] = KEY_INPUT_LEFT ;
		InputSysData.KeyToJoypadInput[ 0 ][  2 ][ 0 ] = KEY_INPUT_NUMPAD6 ;
		InputSysData.KeyToJoypadInput[ 0 ][  2 ][ 1 ] = KEY_INPUT_RIGHT ;
		InputSysData.KeyToJoypadInput[ 0 ][  3 ][ 0 ] = KEY_INPUT_NUMPAD8 ;
		InputSysData.KeyToJoypadInput[ 0 ][  3 ][ 1 ] = KEY_INPUT_UP ;
		InputSysData.KeyToJoypadInput[ 0 ][  4 ][ 0 ] = KEY_INPUT_Z ;
		InputSysData.KeyToJoypadInput[ 0 ][  5 ][ 0 ] = KEY_INPUT_X ;
		InputSysData.KeyToJoypadInput[ 0 ][  6 ][ 0 ] = KEY_INPUT_C ;
		InputSysData.KeyToJoypadInput[ 0 ][  7 ][ 0 ] = KEY_INPUT_A ;
		InputSysData.KeyToJoypadInput[ 0 ][  8 ][ 0 ] = KEY_INPUT_S ;
		InputSysData.KeyToJoypadInput[ 0 ][  9 ][ 0 ] = KEY_INPUT_D ;
		InputSysData.KeyToJoypadInput[ 0 ][ 10 ][ 0 ] = KEY_INPUT_Q ;
		InputSysData.KeyToJoypadInput[ 0 ][ 11 ][ 0 ] = KEY_INPUT_W ;
		InputSysData.KeyToJoypadInput[ 0 ][ 12 ][ 0 ] = KEY_INPUT_RETURN ;
		InputSysData.KeyToJoypadInput[ 0 ][ 13 ][ 0 ] = KEY_INPUT_SPACE ;
	}

	InputSysData.PF.UseInputInfoNum = 0 ;

	emscripten_set_keydown_callback("canvas", NULL, true, &onKeyAction);
	emscripten_set_keyup_callback("canvas", NULL, true, &onKeyAction);
	emscripten_set_mousedown_callback("canvas", NULL, true, &onMouseAction);
	emscripten_set_mousemove_callback("canvas", NULL, true, &onMouseAction);
	emscripten_set_mouseup_callback("canvas", NULL, true, &onMouseAction);
	emscripten_set_wheel_callback("canvas", NULL, true, &onMouseWheel);
	emscripten_set_touchmove_callback("canvas", NULL, true, &onTouchAction);
	emscripten_set_gamepadconnected_callback(NULL, true, &onGamepadAction);
	emscripten_set_gamepaddisconnected_callback(NULL, true, &onGamepadAction);

	// 初期化中フラグを倒す
	NowInitialize = FALSE ;

	// 正常終了
	return 0 ;
}

// 入力システムの後始末をする処理の環境依存処理
extern int TerminateInputSystem_PF_Timing0( void )
{
	// 正常終了
	return 0 ;
}

// 自動初期化を行う環境依存処理
extern int AutoInitialize_PF( void )
{
	return 0 ;
}

// ジョイパッドのセットアップの環境依存処理
extern int SetupJoypad_PF( void )
{
	// 正常終了
	return 0 ;
}

// ジョイパッドの後始末を行う処理の環境依存処理
extern int TerminateJoypad_PF( void )
{
	// 正常終了
	return 0 ;
}

// 入力状態の更新の環境依存処理
extern int UpdateKeyboardInputState_PF( int UseProcessMessage )
{
	_MEMSET( &InputSysData.KeyInputBuf, 0, sizeof( InputSysData.KeyInputBuf ) ) ;
	if( InputSysData.PF.SourceNum[ HTML5_INPUT_SOURCE_KEYBOARD ] > 0 )
	{
		int i, j ;

		for( j = 0 ; j < InputSysData.PF.SourceNum[ HTML5_INPUT_SOURCE_KEYBOARD ] ; j ++ )
		{
			INPUT_HTML5_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.SourceNoToInputInfoTable[ HTML5_INPUT_SOURCE_KEYBOARD ][ j ] ] ;

			for( i = 0 ; g_HTML5KeyToDXInputKey[i][0] != 0xff ; i ++ )
			{
				InputSysData.KeyInputBuf[ g_HTML5KeyToDXInputKey[ i ][ 1 ] ] |= Info->KeyState[ g_HTML5KeyToDXInputKey[ i ][ 0 ] ] ? 0x80 : 0x00 ;
			}
		}
	}

	return 0 ;
}

// パッドの入力状態の更新の環境依存処理
extern int UpdateJoypadInputState_PF( int PadNo )
{
	INPUTPADDATA *pad = &InputSysData.Pad[ PadNo ] ;
//	INPUT_HTML5_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.SourceNoToInputInfoTable[ HTML5_INPUT_SOURCE_GAMEPAD ][ PadNo ] ] ;
	INPUT_HTML5_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.GamePadSourceNoToInputInfoTable[ PadNo ] ] ;
	float DeadZone = pad->DeadZone / 65536.0f ;

//	if( InputSysData.PF.SourceNum[ HTML5_INPUT_SOURCE_GAMEPAD ] <= 0 )
	if( InputSysData.PF.GamePadSourceNum <= 0 )
	{
		return 0 ;
	}

	pad->State.X  = Info->AxisX  < DeadZone && Info->AxisX  > -DeadZone ? 0 : ( int )( Info->AxisX  * 1000.0f ) ;
	pad->State.Y  = Info->AxisY  < DeadZone && Info->AxisY  > -DeadZone ? 0 : ( int )( Info->AxisY  * 1000.0f ) ;
	pad->State.Z  = Info->AxisZ  < DeadZone && Info->AxisZ  > -DeadZone ? 0 : ( int )( Info->AxisZ  * 1000.0f ) ;
	pad->State.Rx = Info->AxisRx < DeadZone && Info->AxisRx > -DeadZone ? 0 : ( int )( Info->AxisRx * 1000.0f ) ;
	pad->State.Ry = Info->AxisRy < DeadZone && Info->AxisRy > -DeadZone ? 0 : ( int )( Info->AxisRy * 1000.0f ) ;
	pad->State.Rz = Info->AxisRz < DeadZone && Info->AxisRz > -DeadZone ? 0 : ( int )( Info->AxisRz * 1000.0f ) ;
	pad->State.Slider[ 0 ]   = ( int )( Info->AxisLTrigger * 1000.0f ) ;
	pad->State.Slider[ 1 ]   = ( int )( Info->AxisRTrigger * 1000.0f ) ;
	if( Info->AxisHatX > 0.5f )
	{
		if( Info->AxisHatY > 0.5f )
		{
			pad->State.POV[ 0 ] = 13500 ;
		}
		else
		if( Info->AxisHatY < -0.5f )
		{
			pad->State.POV[ 0 ] = 4500 ;
		}
		else
		{
			pad->State.POV[ 0 ] = 9000 ;
		}
	}
	else
	if( Info->AxisHatX < -0.5f )
	{
		if( Info->AxisHatY > 0.5f )
		{
			pad->State.POV[ 0 ] = 22500 ;
		}
		else
		if( Info->AxisHatY < -0.5f )
		{
			pad->State.POV[ 0 ] = 31500 ;
		}
		else
		{
			pad->State.POV[ 0 ] = 27000 ;
		}
	}
	else
	{
		if( Info->AxisHatY > 0.5f )
		{
			pad->State.POV[ 0 ] = 18000 ;
		}
		else
		if( Info->AxisHatY < -0.5f )
		{
			pad->State.POV[ 0 ] = 0 ;
		}
		else
		{
			pad->State.POV[ 0 ] = 0xffffffff ;
		}
	}
	pad->State.POV[ 1 ]      = 0xffffffff ;
	pad->State.POV[ 2 ]      = 0xffffffff ;
	pad->State.POV[ 3 ]      = 0xffffffff ;
	pad->State.Buttons[  0 ] = ((Info->ButtonState & PAD_INPUT_1) 	|| Info->KeyState[  0 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[  1 ] = ((Info->ButtonState & PAD_INPUT_2) 	|| Info->KeyState[  1 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[  2 ] = ((Info->ButtonState & PAD_INPUT_3) 	|| Info->KeyState[  2 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[  3 ] = ((Info->ButtonState & PAD_INPUT_4) 	|| Info->KeyState[  3 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[  4 ] = ((Info->ButtonState & PAD_INPUT_5) 	|| Info->KeyState[  4 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[  5 ] = ((Info->ButtonState & PAD_INPUT_6) 	|| Info->KeyState[  5 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[  6 ] = ((Info->ButtonState & PAD_INPUT_7) 	|| Info->KeyState[  6 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[  7 ] = ((Info->ButtonState & PAD_INPUT_8) 	|| Info->KeyState[  7 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[  8 ] = ((Info->ButtonState & PAD_INPUT_9) 	|| Info->KeyState[  8 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[  9 ] = ((Info->ButtonState & PAD_INPUT_10) 	|| Info->KeyState[  9 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[ 10 ] = ((Info->ButtonState & PAD_INPUT_11) 	|| Info->KeyState[ 10 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[ 11 ] = ((Info->ButtonState & PAD_INPUT_12) 	|| Info->KeyState[ 11 ]) ? 0x80 : 0x00 ;
	pad->State.Buttons[ 12 ] = 0 ;
	pad->State.Buttons[ 13 ] = 0 ;
	pad->State.Buttons[ 14 ] = 0 ;
	pad->State.Buttons[ 15 ] = 0 ;
	pad->State.Buttons[ 16 ] = 0 ;
	pad->State.Buttons[ 17 ] = 0 ;
	pad->State.Buttons[ 18 ] = 0 ;
	pad->State.Buttons[ 19 ] = 0 ;
	pad->State.Buttons[ 20 ] = 0 ;
	pad->State.Buttons[ 21 ] = 0 ;
	pad->State.Buttons[ 22 ] = 0 ;
	pad->State.Buttons[ 23 ] = 0 ;
	pad->State.Buttons[ 24 ] = 0 ;
	pad->State.Buttons[ 25 ] = 0 ;
	pad->State.Buttons[ 26 ] = 0 ;
	pad->State.Buttons[ 27 ] = 0 ;
	pad->State.Buttons[ 28 ] = 0 ;
	pad->State.Buttons[ 29 ] = 0 ;
	pad->State.Buttons[ 30 ] = 0 ;
	pad->State.Buttons[ 31 ] = 0 ;

//	if( Info->KeyState[ HTML_KEYCODE_DPAD_LEFT  ] != 0 ) pad->State.X = -1000 ;
//	if( Info->KeyState[ HTML_KEYCODE_DPAD_RIGHT ] != 0 ) pad->State.X =  1000 ;
//	if( Info->KeyState[ HTML_KEYCODE_DPAD_UP    ] != 0 ) pad->State.Y = -1000 ;
//	if( Info->KeyState[ HTML_KEYCODE_DPAD_DOWN  ] != 0 ) pad->State.Y =  1000 ;
//
//	if( Info->KeyState[ HTML_KEYCODE_J          ] != 0 ) pad->State.Z  = -1000 ;
//	if( Info->KeyState[ HTML_KEYCODE_L          ] != 0 ) pad->State.Z  =  1000 ;
//	if( Info->KeyState[ HTML_KEYCODE_I          ] != 0 ) pad->State.Rz = -1000 ;
//	if( Info->KeyState[ HTML_KEYCODE_K          ] != 0 ) pad->State.Rz =  1000 ;
//
//	if( Info->KeyState[ HTML_KEYCODE_2          ] != 0 ) pad->State.Buttons[  0 ] = 0x80 ;
//	if( Info->KeyState[ HTML_KEYCODE_3          ] != 0 ) pad->State.Buttons[  1 ] = 0x80 ;
//	if( Info->KeyState[ HTML_KEYCODE_1          ] != 0 ) pad->State.Buttons[  2 ] = 0x80 ;
//	if( Info->KeyState[ HTML_KEYCODE_4          ] != 0 ) pad->State.Buttons[  3 ] = 0x80 ;
//	if( Info->KeyState[ HTML_KEYCODE_5          ] != 0 ) pad->State.Buttons[  4 ] = 0x80 ;
//	if( Info->KeyState[ HTML_KEYCODE_6          ] != 0 ) pad->State.Buttons[  5 ] = 0x80 ;
//	if( Info->KeyState[ HTML_KEYCODE_7          ] != 0 ) pad->State.Buttons[  6 ] = 0x80 ;
//	if( Info->KeyState[ HTML_KEYCODE_8          ] != 0 ) pad->State.Buttons[  7 ] = 0x80 ;
//	if( Info->KeyState[ HTML_KEYCODE_9          ] != 0 ) pad->State.Buttons[  8 ] = 0x80 ;
//	if( Info->KeyState[ HTML_KEYCODE_0          ] != 0 ) pad->State.Buttons[  9 ] = 0x80 ;
//
//	if( Info->KeyState[ HTML_KEYCODE_DEL        ] != 0 ) pad->State.Buttons[ 10 ] = 0x80 ;
//	if( Info->KeyState[ HTML_KEYCODE_ENTER      ] != 0 ) pad->State.Buttons[ 11 ] = 0x80 ;
//
//	if( Info->KeyState[ HTML_KEYCODE_D ] )
//	{
//		if( Info->KeyState[ HTML_KEYCODE_S ] )
//		{
//			pad->State.POV[ 0 ] = 13500 ;
//		}
//		else
//		if( Info->KeyState[ HTML_KEYCODE_W ] )
//		{
//			pad->State.POV[ 0 ] = 4500 ;
//		}
//		else
//		{
//			pad->State.POV[ 0 ] = 9000 ;
//		}
//	}
//	else
//	if( Info->KeyState[ HTML_KEYCODE_A ] )
//	{
//		if( Info->KeyState[ HTML_KEYCODE_S ] )
//		{
//			pad->State.POV[ 0 ] = 22500 ;
//		}
//		else
//		if( Info->KeyState[ HTML_KEYCODE_W ] )
//		{
//			pad->State.POV[ 0 ] = 31500 ;
//		}
//		else
//		{
//			pad->State.POV[ 0 ] = 27000 ;
//		}
//	}
//	else
//	{
//		if( Info->KeyState[ HTML_KEYCODE_S ] )
//		{
//			pad->State.POV[ 0 ] = 18000 ;
//		}
//		else
//		if( Info->KeyState[ HTML_KEYCODE_W ] )
//		{
//			pad->State.POV[ 0 ] = 0 ;
//		}
//	}

	// 終了
	return 0 ;
}

// パッドエフェクトの再生状態を更新する関数の環境依存処理
extern int RefreshEffectPlayState_PF( void )
{
	// 終了
	return 0 ;
}

// 指定のパッドが振動に対応しているかどうかを取得する( TRUE:対応している  FALSE:対応していない )
extern int CheckJoypadVibrationEnable_PF( INPUTPADDATA *pad, int EffectIndex )
{
	return FALSE ;
}

// 指定の入力デバイスが XInput に対応しているかどうかを取得する処理の環境依存処理( 戻り値  TRUE:XInput対応の入力デバイス  FALSE:XInput非対応の入力デバイス   -1:エラー )( DX_INPUT_KEY や DX_INPUT_KEY_PAD1 など、キーボードが絡むタイプを InputType に渡すとエラーとなり -1 を返す )の環境依存処理
extern int CheckJoypadXInput_PF( int InputType )
{
	return FALSE ;
}

// ジョイパッドのタイプを取得する( 戻り値  -1:エラー  0以上:ジョイパッドタイプ( DX_PADTYPE_XBOX_360 など ) )
extern int GetJoypadType_PF( int InputType )
{
	return DX_PADTYPE_OTHER ;
}

// マウスのボタンの状態を得る処理の環境依存処理
extern int GetMouseInput_PF( void )
{
	int res = 0 ;
	int i ;

	for( i = 0 ; i < InputSysData.PF.SourceNum[ HTML5_INPUT_SOURCE_MOUSE ] ; i ++ )
	{
		INPUT_HTML5_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.SourceNoToInputInfoTable[ HTML5_INPUT_SOURCE_MOUSE ][ i ] ] ;

		if( ( Info->ButtonState & 0x01 ) != 0 ) res |= MOUSE_INPUT_1 ;
		if( ( Info->ButtonState & 0x02 ) != 0 ) res |= MOUSE_INPUT_2 ;
		if( ( Info->ButtonState & 0x04 ) != 0 ) res |= MOUSE_INPUT_3 ;
		if( ( Info->ButtonState & 0x08 ) != 0 ) res |= MOUSE_INPUT_4 ;
		if( ( Info->ButtonState & 0x10 ) != 0 ) res |= MOUSE_INPUT_5 ;
		if( ( Info->ButtonState & 0x20 ) != 0 ) res |= MOUSE_INPUT_6 ;
		if( ( Info->ButtonState & 0x40 ) != 0 ) res |= MOUSE_INPUT_7 ;
		if( ( Info->ButtonState & 0x80 ) != 0 ) res |= MOUSE_INPUT_8 ;
	}

	return res ;
}

// 垂直マウスホイールの回転量を取得する
extern int GetMouseWheelRotVol_PF( int CounterReset )
{
	int Vol ;

	Vol = InputSysData.MouseMoveZ ;
	if( CounterReset )
	{
		InputSysData.MouseMoveZ -= Vol ;
	}

	return Vol ;
}

// 水平マウスホイールの回転量を取得する
extern int GetMouseHWheelRotVol_PF( int CounterReset )
{
	int Vol ;

	Vol = InputSysData.MouseMoveHZ ;
	if( CounterReset )
	{
		InputSysData.MouseMoveHZ -= Vol ;
	}

	return Vol ;
}

// 垂直マウスホイールの回転量を取得する( 戻り値が float 型 )
extern float GetMouseWheelRotVolF_PF( int CounterReset )
{
	float Vol ;

	Vol = ( float )InputSysData.MouseMoveZ ;
	if( CounterReset )
	{
		InputSysData.MouseMoveZ = 0 ;
	}

	return Vol ;
}

// 水平マウスホイールの回転量を取得する( 戻り値が float 型 )
extern float GetMouseHWheelRotVolF_PF( int CounterReset )
{
	float Vol ;

	Vol = ( float )InputSysData.MouseMoveHZ ;
	if( CounterReset )
	{
		InputSysData.MouseMoveHZ = 0 ;
	}

	return Vol ;
}

// マウスの位置を取得する
extern int GetMousePoint_PF( int *XBuf, int *YBuf )
{
	if( XBuf != NULL )
	{
		*XBuf = 0 ;
	}

	if( YBuf != NULL )
	{
		*YBuf = 0 ;
	}

	if( InputSysData.PF.SourceNum[ HTML5_INPUT_SOURCE_MOUSE ] > 0 )
	{
		int ScreenX, ScreenY ;
		INPUT_HTML5_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.SourceNoToInputInfoTable[ HTML5_INPUT_SOURCE_MOUSE ][ 0 ] ] ;

		ScreenX = ( int )Info->AxisX ;
		ScreenY = ( int )Info->AxisY ;

		ScreenX = ( int )InputSysData.PF.MouseX ;
		ScreenY = ( int )InputSysData.PF.MouseY ;
		ConvScreenPositionToDxScreenPosition( ScreenX, ScreenY, XBuf, YBuf ) ;
	}

	return 0 ;
}

// マウスの位置をセットする
extern int SetMousePoint_PF( int PointX , int PointY )
{
	return 0 ;
}

// ジョイパッドの無効ゾーンの設定を行う関数の環境依存処理
extern int SetJoypadDeadZone_PF( INPUTPADDATA *pad )
{
	// 正常終了
	return 0 ;
}

// デバイスＩＤから値を代入すべき入力情報番号を取得する
extern int GetHTML5DeviceIdToInputInfoNo( int32_t Source, int32_t DeviceId )
{
	int i ;
//	int Src ;
//
//	for( Src = 0 ; Src < HTML5_INPUT_SOURCE_NUM ; Src ++ )
//	{
//		if( g_HTML5InputSourceTable[ Src ] == Source )
//		{
//			break ;
//		}
//	}
//	if( Src == HTML5_INPUT_SOURCE_NUM )
//	{
//		return -1 ;
//	}

	for( i = 0 ; i < InputSysData.PF.UseInputInfoNum ; i ++ )
	{
		if(    InputSysData.PF.InputInfo[ i ].Source   == Source   &&
			   InputSysData.PF.InputInfo[ i ].DeviceId == DeviceId )
		{
			// int UpdateFlag = FALSE ;

			// if( InputSysData.PF.InputInfo[ i ].Source != Source )
			// {
			// 	UpdateFlag = TRUE ;
			// }

			// InputSysData.PF.InputInfo[ i ].Source = Source ;
			InputSysData.PF.InputInfo[ i ].UpdateCount = InputSysData.PF.UpdateCount ;
			InputSysData.PF.UpdateCount ++ ;

			// if( UpdateFlag )
			// {
			// 	RefreshHTML5SourceNoToInputInfoTable( Source ) ;
			// 	RefreshHTML5GamePadSourceNoToInputInfoTable() ;
			// }
			return i ;
		}
	}

	if( InputSysData.PF.UseInputInfoNum == HTML5_DEVICE_MAX_NUM )
	{
		int MinUpdateCountNo ;

		MinUpdateCountNo = 0 ;
		for( i = 1 ; i < InputSysData.PF.UseInputInfoNum ; i ++ )
		{
			if( InputSysData.PF.InputInfo[ MinUpdateCountNo ].UpdateCount > InputSysData.PF.InputInfo[ i ].UpdateCount )
			{
				MinUpdateCountNo = i ;
			}
		}

		_MEMSET( &InputSysData.PF.InputInfo[ MinUpdateCountNo ], 0, sizeof( InputSysData.PF.InputInfo[ MinUpdateCountNo ] ) ) ;
		InputSysData.PF.InputInfo[ MinUpdateCountNo ].Source = Source ;
		InputSysData.PF.InputInfo[ MinUpdateCountNo ].DeviceId = DeviceId ;
		InputSysData.PF.InputInfo[ MinUpdateCountNo ].UpdateCount = InputSysData.PF.UpdateCount ;
		InputSysData.PF.UpdateCount ++ ;

		RefreshHTML5SourceNoToInputInfoTable( Source ) ;
		RefreshHTML5GamePadSourceNoToInputInfoTable() ;

		return MinUpdateCountNo ;
	}

	i = InputSysData.PF.UseInputInfoNum ;
	InputSysData.PF.UseInputInfoNum ++ ;

	_MEMSET( &InputSysData.PF.InputInfo[ i ], 0, sizeof( InputSysData.PF.InputInfo[ i ] ) ) ;
	InputSysData.PF.InputInfo[ i ].Source = Source ;
	InputSysData.PF.InputInfo[ i ].DeviceId = DeviceId ;
	InputSysData.PF.InputInfo[ i ].UpdateCount = InputSysData.PF.UpdateCount ;
	InputSysData.PF.UpdateCount ++ ;

	RefreshHTML5SourceNoToInputInfoTable( Source ) ;
	RefreshHTML5GamePadSourceNoToInputInfoTable() ;
	
	return i ;
}

// 入力ソース番号と入力情報との対応テーブルを更新する
extern int RefreshHTML5SourceNoToInputInfoTable( int32_t Source )
{
	INPUT_HTML5_DEVICE_INFO *Info ;
	int *SourceNoTable ;
	int i, j ;
	int Num ;
	int NoTable[ HTML5_DEVICE_MAX_NUM ] ;
	INPUT_HTML5_DEVICE_INFO *InfoTable[ HTML5_DEVICE_MAX_NUM ] ;
	int Src ;

	for( Src = 0 ; Src < HTML5_INPUT_SOURCE_NUM ; Src ++ )
	{
		if( Source == g_HTML5InputSourceTable[ Src ] )
		{
			break ;
		}
	}
	if( Src == HTML5_INPUT_SOURCE_NUM )
	{
		return -1 ;
	}

	Num = 0 ;
	Info = InputSysData.PF.InputInfo ;
	for( i = 0 ; i < InputSysData.PF.UseInputInfoNum ; i ++, Info ++ )
	{
		if( Info->Source  == Source )
		{
			InfoTable[ Num ] = Info ;
			Num ++ ;
		}
	}
	InputSysData.PF.SourceNum[ Src ] = Num ;

	if( Num == 0 )
	{
		return 0 ;
	}

	NoTable[ 0 ] = 0 ;
	for( i = 1 ; i < Num ; i ++ )
	{
		for( j = 0 ; j < i ; j ++ )
		{
			if( InfoTable[ NoTable[ j ] ]->DeviceId < InfoTable[ i ]->DeviceId )
			{
				_MEMMOVE( &NoTable[ j + 1 ], &NoTable[ j ], sizeof( int ) * ( i - j ) ) ;
				NoTable[ j ] = i ;
				break ;
			}
		}
		if( j == i )
		{
			NoTable[ j ] = i ;
		}
	}

	SourceNoTable = InputSysData.PF.SourceNoToInputInfoTable[ Src ] ;
	for( i = 0 ; i < Num ; i ++ )
	{
		SourceNoTable[ i ] = InfoTable[ NoTable[ i ] ] - InputSysData.PF.InputInfo ;
	}

	// 終了
	return 0 ;
}

// ゲームパッドの番号と入力情報との対応テーブルを更新する
extern int RefreshHTML5GamePadSourceNoToInputInfoTable( void )
{
	INPUT_HTML5_DEVICE_INFO *Info ;
	int *SourceNoTable ;
	int i, j ;
	int Num ;
	int NoTable[ HTML5_DEVICE_MAX_NUM ] ;
	INPUT_HTML5_DEVICE_INFO *InfoTable[ HTML5_DEVICE_MAX_NUM ] ;

	Num = 0 ;
	Info = InputSysData.PF.InputInfo ;
	for( i = 0 ; i < InputSysData.PF.UseInputInfoNum ; i ++, Info ++ )
	{
		// ＤＸライブラリがゲームパッドとして扱う要素を持っている場合はゲームパッドとする
		if( Info->Source == HTML5_INPUT_SOURCE_JOYSTICK )
		{
			InfoTable[ Num ] = Info ;
			Num ++ ;
		}
	}
	InputSysData.PF.GamePadSourceNum = Num ;

	if( Num == 0 )
	{
		return 0 ;
	}

	NoTable[ 0 ] = 0 ;
	for( i = 1 ; i < Num ; i ++ )
	{
		for( j = 0 ; j < i ; j ++ )
		{
			if( InfoTable[ NoTable[ j ] ]->DeviceId < InfoTable[ i ]->DeviceId )
			{
				_MEMMOVE( &NoTable[ j + 1 ], &NoTable[ j ], sizeof( int ) * ( i - j ) ) ;
				NoTable[ j ] = i ;
				break ;
			}
		}
		if( j == i )
		{
			NoTable[ j ] = i ;
		}
	}

	SourceNoTable = InputSysData.PF.GamePadSourceNoToInputInfoTable ;
	for( i = 0 ; i < Num ; i ++ )
	{
		SourceNoTable[ i ] = InfoTable[ NoTable[ i ] ] - InputSysData.PF.InputInfo ;
	}

	InputSysData.PadNum = Num > MAX_JOYPAD_NUM ? MAX_JOYPAD_NUM : Num ;

	// 終了
	return 0 ;
}

// 入力イベントを処理する
extern int32_t ProcessInputEvent( )
{
	int gamePadCount;
	int i;
	EmscriptenGamepadEvent event;

	emscripten_sample_gamepad_data();
	gamePadCount = emscripten_get_num_gamepads();

	for (i = 0; i < gamePadCount; i++) {

		int32_t Source ;
		int32_t DeviceId ;
		int InputNo ;
		EMSCRIPTEN_RESULT SampleResult ;

		SampleResult = emscripten_get_gamepad_status(i, &event);

		if (SampleResult != EMSCRIPTEN_RESULT_SUCCESS || !event.connected) {
			continue;
		}

		Source = HTML5_INPUT_SOURCE_JOYSTICK;
		DeviceId = event.index;
		InputNo = GetHTML5DeviceIdToInputInfoNo( Source, DeviceId ) ;

		if( InputNo >= 0 && InputNo < HTML5_DEVICE_MAX_NUM )
		{
			int j;

			InputSysData.PF.InputInfo[ InputNo ].AxisX			= event.numAxes > 0 ? event.axis[0] : 0.0f ;
			InputSysData.PF.InputInfo[ InputNo ].AxisY			= event.numAxes > 1 ? event.axis[1] : 0.0f ;
			InputSysData.PF.InputInfo[ InputNo ].AxisZ			= event.numAxes > 2 ? event.axis[2] : 0.0f ;
			InputSysData.PF.InputInfo[ InputNo ].AxisRx			= event.numAxes > 3 ? event.axis[3] : 0.0f ;
			InputSysData.PF.InputInfo[ InputNo ].AxisRy			= event.numAxes > 4 ? event.axis[4] : 0.0f ;
			InputSysData.PF.InputInfo[ InputNo ].AxisRz			= event.numAxes > 5 ? event.axis[5] : 0.0f ;
			InputSysData.PF.InputInfo[ InputNo ].AxisHatX		= event.numAxes > 6 ? event.axis[6] : 0.0f ;
			InputSysData.PF.InputInfo[ InputNo ].AxisHatY		= event.numAxes > 7 ? event.axis[7] : 0.0f ;

			InputSysData.PF.InputInfo[ InputNo ].ButtonState 	= 0;

			for ( j = 0; j < 32 && j < event.numButtons; j++) {
				if (event.digitalButton[j] != 0) {
					InputSysData.PF.InputInfo[ InputNo ].ButtonState	|=  (PAD_INPUT_1 << j);
				}
			}
		}
	}
	
	return 0 ;
}


static EM_BOOL onKeyAction(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData) {
	int32_t Source ;
	int32_t DeviceId ;
	int InputNo ;
	EM_BOOL preventDefault ;

	int32_t KeyCode ;

	preventDefault = EM_FALSE;
	Source = HTML5_INPUT_SOURCE_KEYBOARD;
	DeviceId = 0;
	InputNo = GetHTML5DeviceIdToInputInfoNo( Source, DeviceId ) ;
	KeyCode = keyEvent->keyCode;

	if( InputNo >= 0 && InputNo < HTML5_DEVICE_MAX_NUM )
	{
		if( KeyCode < HTML5_KEYCODE_MAX )
		{
			if( eventType == EMSCRIPTEN_EVENT_KEYDOWN )
			{
				InputSysData.PF.InputInfo[ InputNo ].KeyState[ KeyCode ] = 1 ;
			}
			else
			if( eventType == EMSCRIPTEN_EVENT_KEYUP )
			{
				InputSysData.PF.InputInfo[ InputNo ].KeyState[ KeyCode ] = 0 ;
			}
		}

		preventDefault = EM_TRUE;
	}

	return preventDefault;
}

static EM_BOOL onMouseWheel(int eventType, const EmscriptenWheelEvent *wheelEvent, void *userData) {
	int32_t Source ;
	int32_t DeviceId ;
	int InputNo ;
	EM_BOOL preventDefault ;

	int32_t KeyCode ;

	preventDefault = EM_FALSE;

	Source = HTML5_INPUT_SOURCE_MOUSE;
	DeviceId = 0;
	InputNo = GetHTML5DeviceIdToInputInfoNo( Source, DeviceId ) ;

	if( InputNo >= 0 && InputNo < HTML5_DEVICE_MAX_NUM )
	{
		int LogType = -1 ;
		
		if( eventType == EMSCRIPTEN_EVENT_MOUSEDOWN )
		{
			LogType = MOUSE_INPUT_LOG_DOWN ;
			InputSysData.PF.InputInfo[ InputNo ].PointerState[ 0 ] = 1 ;
		}
		else if( eventType == EMSCRIPTEN_EVENT_MOUSEUP )
		{
			LogType = MOUSE_INPUT_LOG_UP ;
			InputSysData.PF.InputInfo[ InputNo ].PointerState[ 0 ] = 0 ;
		}
		
		InputSysData.PF.InputInfo[ InputNo ].ButtonState	= wheelEvent->mouse.buttons ;
		InputSysData.PF.InputInfo[ InputNo ].AxisX			= wheelEvent->mouse.targetX ;
		InputSysData.PF.InputInfo[ InputNo ].AxisY			= wheelEvent->mouse.targetY ;
		InputSysData.PF.InputInfo[ InputNo ].Wheel			= wheelEvent->deltaX ;

		InputSysData.PF.MouseX = InputSysData.PF.InputInfo[ InputNo ].AxisX ;
		InputSysData.PF.MouseY = InputSysData.PF.InputInfo[ InputNo ].AxisY ;
	
		InputSysData.MouseMoveZ  += InputSysData.PF.InputInfo[ InputNo ].Wheel ;

		// ログを追加
		if( LogType != -1 )
		{
			int MouseX, MouseY ;
			int i ;
			int Button ;

			ConvScreenPositionToDxScreenPosition(
				InputSysData.PF.InputInfo[ InputNo ].AxisX,
				InputSysData.PF.InputInfo[ InputNo ].AxisY,
				&MouseX,
				&MouseY
			) ;

			for( i = 0 ; i < 8 ; i ++ )
			{
				Button = 1 << i ;
				if( ( InputSysData.PF.InputInfo[ InputNo ].ButtonState & Button ) != 0 )
				{
					if( LogType == MOUSE_INPUT_LOG_DOWN )
					{
						StockMouseInputLogData( Button, MouseX, MouseY ) ;
					}
					StockMouseInputLogData2( Button, MouseX, MouseY, LogType ) ;
				}
			}
		}

		preventDefault = EM_TRUE;
	}

	// マウス入力があった際はタップの入力を無効化する
	{
		TOUCHINPUTDATA TouchInputData ;

		TouchInputData.PointNum = 0 ;
		TouchInputData.Time = 0 ;

		AddTouchInputData( &TouchInputData ) ;
	}

	return preventDefault;
}

static EM_BOOL onMouseAction(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) {
	EmscriptenWheelEvent wheelEvent;
	EM_BOOL preventDefault ;

	wheelEvent.mouse = *mouseEvent;
	wheelEvent.deltaX = 0;
	wheelEvent.deltaMode = 0;

	onMouseWheel(eventType, &wheelEvent, userData);
	preventDefault = false;
	
	return preventDefault;
}

static EM_BOOL onTouchAction(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData) {
	int32_t Source ;
	int32_t DeviceId ;
	int InputNo ;
	EM_BOOL preventDefault ;

	int32_t KeyCode ;

	Source = HTML5_INPUT_SOURCE_TOUCHSCREEN;
	DeviceId = 0;
	InputNo = GetHTML5DeviceIdToInputInfoNo( Source, DeviceId ) ;
	preventDefault = EM_FALSE;

	if( InputNo >= 0 && InputNo < HTML5_DEVICE_MAX_NUM )
	{
		TOUCHINPUTDATA TouchInputData ;
		int32_t PointerCount ;

		TouchInputData.PointNum = 0 ;
		TouchInputData.Time = 0 ; // No support.			
		PointerCount = touchEvent->numTouches;

		if( PointerCount > 0 )
		{
			int32_t i ;
			TOUCHINPUTPOINT *TouchPoint ;

			TouchPoint = TouchInputData.Point ;
			for( i = 0; i < PointerCount; i++ )
			{
				int ScreenX, ScreenY ;

				TouchPoint->Device = 0 ;
				TouchPoint->ID = touchEvent->touches[i].identifier ;
				ScreenX = touchEvent->touches[i].targetX ;
				ScreenY = touchEvent->touches[i].targetY ;
				ConvScreenPositionToDxScreenPosition( ScreenX, ScreenY, &TouchPoint->PositionX, &TouchPoint->PositionY ) ;

				TouchInputData.PointNum ++ ;
				TouchPoint ++ ;
			}
		}
		
		AddTouchInputData( &TouchInputData ) ;
		preventDefault = EM_TRUE;
	}

	return preventDefault;
}

static EM_BOOL onGamepadAction(int eventType, const EmscriptenGamepadEvent *gamepadEvent, void *userData) {
	// Disconnected & connected.
	return false;
}

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_INPUT


