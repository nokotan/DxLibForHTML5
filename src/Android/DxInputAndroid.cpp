//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p���͏��v���O����
// 
//  	Ver 3.24d
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_INPUT

// �C���N���[�h----------------------------------------------------------------
#include "DxInputAndroid.h"
#include "DxSystemAndroid.h"
#include "../DxLog.h"
#include "../DxInput.h"
#include "../DxSystem.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����`------------------------------------------------------------------

#define DEADZONE_XINPUT( ZONE )				(short)( 32767 * (ZONE) / 65536)
#define DEADZONE_XINPUT_TRIGGER( ZONE )		(short)(   255 * (ZONE) / 65536)
#define VALIDRANGE_XINPUT( ZONE )			( 32767 - DEADZONE_XINPUT(ZONE))
#define VALIDRANGE_XINPUT_TRIGGER( ZONE )	(   255 - DEADZONE_XINPUT_TRIGGER(ZONE))

// �^��`----------------------------------------------------------------------

// �萔��` ----------------------------------------------------------------------

// �f�[�^�錾------------------------------------------------------------------

const static int32_t g_AndroidInputSourceTable[ ANDR_INPUT_SOURCE_NUM ] =
{
	AINPUT_SOURCE_UNKNOWN,
	AINPUT_SOURCE_KEYBOARD,
	AINPUT_SOURCE_DPAD,
	AINPUT_SOURCE_GAMEPAD,
	AINPUT_SOURCE_TOUCHSCREEN,
	AINPUT_SOURCE_MOUSE,
	AINPUT_SOURCE_STYLUS,
	AINPUT_SOURCE_TRACKBALL,
	AINPUT_SOURCE_TOUCHPAD,
	AINPUT_SOURCE_TOUCH_NAVIGATION,
	AINPUT_SOURCE_JOYSTICK,
} ;

const static unsigned short g_AndroidKeyToDXInputKey[][ 2 /* 0:Android�L�[�R�[�h  1:DirectInput�L�[�R�[�h  */ ] =
{
	{ AKEYCODE_DEL,				KEY_INPUT_BACK },		// BackSpace�L�[
	{ AKEYCODE_TAB,				KEY_INPUT_TAB },		// Tab�L�[
	{ AKEYCODE_ENTER,			KEY_INPUT_RETURN },		// Enter�L�[

	{ AKEYCODE_SHIFT_LEFT,		KEY_INPUT_LSHIFT },		// ��Shift�L�[
	{ AKEYCODE_SHIFT_RIGHT,		KEY_INPUT_RSHIFT },		// �EShift�L�[
	{ AKEYCODE_CTRL_LEFT,		KEY_INPUT_LCONTROL },	// ��Ctrl�L�[
	{ AKEYCODE_CTRL_RIGHT,		KEY_INPUT_RCONTROL },	// �ECtrl�L�[
	{ AKEYCODE_ESCAPE,			KEY_INPUT_ESCAPE },		// Esc�L�[
	{ AKEYCODE_SPACE,			KEY_INPUT_SPACE },		// �X�y�[�X�L�[
	{ AKEYCODE_PAGE_UP,			KEY_INPUT_PGUP },		// PageUp�L�[
	{ AKEYCODE_PAGE_DOWN,		KEY_INPUT_PGDN },		// PageDown�L�[
	{ AKEYCODE_MOVE_END,		KEY_INPUT_END },		// End�L�[
	{ AKEYCODE_MOVE_HOME,		KEY_INPUT_HOME },		// Home�L�[
	{ AKEYCODE_DPAD_LEFT,		KEY_INPUT_LEFT },		// ���L�[
	{ AKEYCODE_DPAD_UP,			KEY_INPUT_UP },			// ��L�[
	{ AKEYCODE_DPAD_RIGHT,		KEY_INPUT_RIGHT },		// �E�L�[
	{ AKEYCODE_DPAD_DOWN,		KEY_INPUT_DOWN },		// ���L�[
	{ AKEYCODE_INSERT,			KEY_INPUT_INSERT },		// Insert�L�[
	{ AKEYCODE_FORWARD_DEL,		KEY_INPUT_DELETE },		// Delete�L�[

	{ AKEYCODE_MINUS,			KEY_INPUT_MINUS },		// �|�L�[
	{ AKEYCODE_YEN,				KEY_INPUT_YEN },		// ���L�[
	{ AKEYCODE_EQUALS,			KEY_INPUT_PREVTRACK },	// �O�L�[
	{ AKEYCODE_PERIOD,			KEY_INPUT_PERIOD },		// �D�L�[
	{ AKEYCODE_SLASH,			KEY_INPUT_SLASH },		// �^�L�[
	{ AKEYCODE_ALT_LEFT,		KEY_INPUT_LALT },		// ��Alt�L�[
	{ AKEYCODE_ALT_RIGHT,		KEY_INPUT_RALT },		// �EAlt�L�[
	{ AKEYCODE_SCROLL_LOCK,		KEY_INPUT_SCROLL },		// ScrollLock�L�[
	{ AKEYCODE_SEMICOLON,		KEY_INPUT_SEMICOLON },	// �G�L�[
	{ AKEYCODE_APOSTROPHE,		KEY_INPUT_COLON },		// �F�L�[
	{ AKEYCODE_LEFT_BRACKET,	KEY_INPUT_LBRACKET },	// �m�L�[
	{ AKEYCODE_RIGHT_BRACKET,	KEY_INPUT_RBRACKET },	// �n�L�[
	{ AKEYCODE_AT,				KEY_INPUT_AT },			// ���L�[
	{ AKEYCODE_RO,				KEY_INPUT_BACKSLASH },	// �_�L�[
	{ AKEYCODE_COMMA,			KEY_INPUT_COMMA },		// �C�L�[
	{ AKEYCODE_ZENKAKU_HANKAKU,	KEY_INPUT_KANJI },		// �����L�[
	{ AKEYCODE_HENKAN,			KEY_INPUT_CONVERT },	// �ϊ��L�[
	{ AKEYCODE_MUHENKAN,		KEY_INPUT_NOCONVERT },	// ���ϊ��L�[
	{ AKEYCODE_KANA,			KEY_INPUT_KANA },		// �J�i�L�[
	{ AKEYCODE_SEARCH,			KEY_INPUT_APPS },		// �A�v���P�[�V�������j���[�L�[
	{ AKEYCODE_CAPS_LOCK,		KEY_INPUT_CAPSLOCK },	// CaspLock�L�[
	{ AKEYCODE_SYSRQ,			KEY_INPUT_SYSRQ },		// PrintScreen�L�[
	{ AKEYCODE_BREAK,			KEY_INPUT_PAUSE },		// PauseBreak�L�[
//	{							KEY_INPUT_LWIN },		// ��Win�L�[
//	{							KEY_INPUT_RWIN },		// �EWin�L�[

	{ AKEYCODE_NUM_LOCK,		KEY_INPUT_NUMLOCK },	// �e���L�[NumLock�L�[
	{ AKEYCODE_NUMPAD_0,		KEY_INPUT_NUMPAD0 },	// �e���L�[�O
	{ AKEYCODE_NUMPAD_1,		KEY_INPUT_NUMPAD1 },	// �e���L�[�P
	{ AKEYCODE_NUMPAD_2,		KEY_INPUT_NUMPAD2 },	// �e���L�[�Q
	{ AKEYCODE_NUMPAD_3,		KEY_INPUT_NUMPAD3 },	// �e���L�[�R
	{ AKEYCODE_NUMPAD_4,		KEY_INPUT_NUMPAD4 },	// �e���L�[�S
	{ AKEYCODE_NUMPAD_5,		KEY_INPUT_NUMPAD5 },	// �e���L�[�T
	{ AKEYCODE_NUMPAD_6,		KEY_INPUT_NUMPAD6 },	// �e���L�[�U
	{ AKEYCODE_NUMPAD_7,		KEY_INPUT_NUMPAD7 },	// �e���L�[�V
	{ AKEYCODE_NUMPAD_8,		KEY_INPUT_NUMPAD8 },	// �e���L�[�W
	{ AKEYCODE_NUMPAD_9,		KEY_INPUT_NUMPAD9 },	// �e���L�[�X
	{ AKEYCODE_NUMPAD_MULTIPLY,	KEY_INPUT_MULTIPLY },	// �e���L�[���L�[
	{ AKEYCODE_NUMPAD_ADD,		KEY_INPUT_ADD },		// �e���L�[�{�L�[
	{ AKEYCODE_NUMPAD_SUBTRACT,	KEY_INPUT_SUBTRACT },	// �e���L�[�|�L�[
	{ AKEYCODE_NUMPAD_DOT,		KEY_INPUT_DECIMAL },	// �e���L�[�D�L�[
	{ AKEYCODE_NUMPAD_DIVIDE,	KEY_INPUT_DIVIDE },		// �e���L�[�^�L�[
	{ AKEYCODE_NUMPAD_ENTER,	KEY_INPUT_NUMPADENTER },// �e���L�[�̃G���^�[�L�[

	{ AKEYCODE_F1,				KEY_INPUT_F1 },			// �e�P�L�[
	{ AKEYCODE_F2,				KEY_INPUT_F2 },			// �e�Q�L�[
	{ AKEYCODE_F3,				KEY_INPUT_F3 },			// �e�R�L�[
	{ AKEYCODE_F4,				KEY_INPUT_F4 },			// �e�S�L�[
	{ AKEYCODE_F5,				KEY_INPUT_F5 },			// �e�T�L�[
	{ AKEYCODE_F6,				KEY_INPUT_F6 },			// �e�U�L�[
	{ AKEYCODE_F7,				KEY_INPUT_F7 },			// �e�V�L�[
	{ AKEYCODE_F8,				KEY_INPUT_F8 },			// �e�W�L�[
	{ AKEYCODE_F9,				KEY_INPUT_F9 },			// �e�X�L�[
	{ AKEYCODE_F10,				KEY_INPUT_F10 },		// �e�P�O�L�[
	{ AKEYCODE_F11,				KEY_INPUT_F11 },		// �e�P�P�L�[
	{ AKEYCODE_F12,				KEY_INPUT_F12 },		// �e�P�Q�L�[

	{ AKEYCODE_A,				KEY_INPUT_A },			// �`�L�[
	{ AKEYCODE_B,				KEY_INPUT_B },			// �a�L�[
	{ AKEYCODE_C,				KEY_INPUT_C },			// �b�L�[
	{ AKEYCODE_D,				KEY_INPUT_D },			// �c�L�[
	{ AKEYCODE_E,				KEY_INPUT_E },			// �d�L�[
	{ AKEYCODE_F,				KEY_INPUT_F },			// �e�L�[
	{ AKEYCODE_G,				KEY_INPUT_G },			// �f�L�[
	{ AKEYCODE_H,				KEY_INPUT_H },			// �g�L�[
	{ AKEYCODE_I,				KEY_INPUT_I },			// �h�L�[
	{ AKEYCODE_J,				KEY_INPUT_J },			// �i�L�[
	{ AKEYCODE_K,				KEY_INPUT_K },			// �j�L�[
	{ AKEYCODE_L,				KEY_INPUT_L },			// �k�L�[
	{ AKEYCODE_M,				KEY_INPUT_M },			// �l�L�[
	{ AKEYCODE_N,				KEY_INPUT_N },			// �m�L�[
	{ AKEYCODE_O,				KEY_INPUT_O },			// �n�L�[
	{ AKEYCODE_P,				KEY_INPUT_P },			// �o�L�[
	{ AKEYCODE_Q,				KEY_INPUT_Q },			// �p�L�[
	{ AKEYCODE_R,				KEY_INPUT_R },			// �q�L�[
	{ AKEYCODE_S,				KEY_INPUT_S },			// �r�L�[
	{ AKEYCODE_T,				KEY_INPUT_T },			// �s�L�[
	{ AKEYCODE_U,				KEY_INPUT_U },			// �t�L�[
	{ AKEYCODE_V,				KEY_INPUT_V },			// �u�L�[
	{ AKEYCODE_W,				KEY_INPUT_W },			// �v�L�[
	{ AKEYCODE_X,				KEY_INPUT_X },			// �w�L�[
	{ AKEYCODE_Y,				KEY_INPUT_Y },			// �x�L�[
	{ AKEYCODE_Z,				KEY_INPUT_Z },			// �y�L�[

	{ AKEYCODE_0,				KEY_INPUT_0 },			// �O�L�[
	{ AKEYCODE_1,				KEY_INPUT_1 },			// �P�L�[
	{ AKEYCODE_2,				KEY_INPUT_2 },			// �Q�L�[
	{ AKEYCODE_3,				KEY_INPUT_3 },			// �R�L�[
	{ AKEYCODE_4,				KEY_INPUT_4 },			// �S�L�[
	{ AKEYCODE_5,				KEY_INPUT_5 },			// �T�L�[
	{ AKEYCODE_6,				KEY_INPUT_6 },			// �U�L�[
	{ AKEYCODE_7,				KEY_INPUT_7 },			// �V�L�[
	{ AKEYCODE_8,				KEY_INPUT_8 },			// �W�L�[
	{ AKEYCODE_9,				KEY_INPUT_9 },			// �X�L�[

	{ AKEYCODE_BACK,			KEY_INPUT_ESCAPE },		// Android �� Back�{�^��

	{ 0xffff,					0xffff },
} ;

// �֐��v���g�^�C�v�錾 -------------------------------------------------------

// �v���O����------------------------------------------------------------------

// ���̓V�X�e�������������鏈���̊��ˑ�����
extern int InitializeInputSystem_PF_Timing0( void )
{
	static int NowInitialize = FALSE ;
	int i, j ;

	// ���ɏ������������J�n����Ă���ꍇ�����������ɏI��
	if( NowInitialize )
	{
		return 0 ;
	}

	// ���������t���O�𗧂Ă�
	NowInitialize = TRUE ;

	// �����]�[���̃Z�b�g
	for( i = 0 ; i < MAX_JOYPAD_NUM ; i ++ )
	{
		InputSysData.Pad[ i ].DeadZone = InputSysData.PadDefaultDeadZone ;
		InputSysData.Pad[ i ].DeadZoneD = InputSysData.PadDefaultDeadZoneD ;
	}

	// �L�[�{�[�h�ƃW���C�p�b�h�̓��͂̃f�t�H���g�̑Ή��\��ݒ肷��
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

	// ���������t���O��|��
	NowInitialize = FALSE ;

	// ����I��
	return 0 ;
}

// ���̓V�X�e���̌�n�������鏈���̊��ˑ�����
extern int TerminateInputSystem_PF_Timing0( void )
{
	// ����I��
	return 0 ;
}

// �������������s�����ˑ�����
extern int AutoInitialize_PF( void )
{
	return 0 ;
}

// �W���C�p�b�h�̃Z�b�g�A�b�v�̊��ˑ�����
extern int SetupJoypad_PF( void )
{
	// ����I��
	return 0 ;
}

// �W���C�p�b�h�̌�n�����s�������̊��ˑ�����
extern int TerminateJoypad_PF( void )
{
	// ����I��
	return 0 ;
}

// ���͏�Ԃ̍X�V�̊��ˑ�����
extern int UpdateKeyboardInputState_PF( int UseProcessMessage )
{
	_MEMSET( &InputSysData.KeyInputBuf, 0, sizeof( InputSysData.KeyInputBuf ) ) ;
	if( InputSysData.PF.SourceNum[ ANDR_INPUT_SOURCE_KEYBOARD ] > 0 )
	{
		int i, j ;

		for( j = 0 ; j < InputSysData.PF.SourceNum[ ANDR_INPUT_SOURCE_KEYBOARD ] ; j ++ )
		{
			INPUT_ANDROID_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.SourceNoToInputInfoTable[ ANDR_INPUT_SOURCE_KEYBOARD ][ j ] ] ;

			for( i = 0 ; g_AndroidKeyToDXInputKey[i][0] != 0xffff ; i ++ )
			{
				InputSysData.KeyInputBuf[ g_AndroidKeyToDXInputKey[ i ][ 1 ] ] |= Info->KeyState[ g_AndroidKeyToDXInputKey[ i ][ 0 ] ] ? 0x80 : 0x00 ;
			}
		}
	}

	return 0 ;
}

// �p�b�h�̓��͏�Ԃ̍X�V�̊��ˑ�����
extern int UpdateJoypadInputState_PF( int PadNo )
{
	INPUTPADDATA *pad = &InputSysData.Pad[ PadNo ] ;
//	INPUT_ANDROID_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.SourceNoToInputInfoTable[ ANDR_INPUT_SOURCE_GAMEPAD ][ PadNo ] ] ;
	INPUT_ANDROID_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.GamePadSourceNoToInputInfoTable[ PadNo ] ] ;
	float DeadZone = pad->DeadZone / 65536.0f ;

//	if( InputSysData.PF.SourceNum[ ANDR_INPUT_SOURCE_GAMEPAD ] <= 0 )
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
	pad->State.Buttons[  0 ] = Info->KeyState[ AKEYCODE_BUTTON_A      ] ? 0x80 : 0x00 ;
	pad->State.Buttons[  1 ] = Info->KeyState[ AKEYCODE_BUTTON_B      ] ? 0x80 : 0x00 ;
	pad->State.Buttons[  2 ] = Info->KeyState[ AKEYCODE_BUTTON_X      ] ? 0x80 : 0x00 ;
	pad->State.Buttons[  3 ] = Info->KeyState[ AKEYCODE_BUTTON_Y      ] ? 0x80 : 0x00 ;
	pad->State.Buttons[  4 ] = Info->KeyState[ AKEYCODE_BUTTON_L1     ] ? 0x80 : 0x00 ;
	pad->State.Buttons[  5 ] = Info->KeyState[ AKEYCODE_BUTTON_R1     ] ? 0x80 : 0x00 ;
	pad->State.Buttons[  6 ] = Info->KeyState[ AKEYCODE_BUTTON_L2     ] ? 0x80 : 0x00 ;
	pad->State.Buttons[  7 ] = Info->KeyState[ AKEYCODE_BUTTON_R2     ] ? 0x80 : 0x00 ;
	pad->State.Buttons[  8 ] = Info->KeyState[ AKEYCODE_BUTTON_THUMBL ] ? 0x80 : 0x00 ;
	pad->State.Buttons[  9 ] = Info->KeyState[ AKEYCODE_BUTTON_THUMBR ] ? 0x80 : 0x00 ;
	pad->State.Buttons[ 10 ] = Info->KeyState[ AKEYCODE_BUTTON_SELECT ] ? 0x80 : 0x00 ;
	pad->State.Buttons[ 11 ] = Info->KeyState[ AKEYCODE_BUTTON_START  ] ? 0x80 : 0x00 ;
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

//	if( Info->KeyState[ AKEYCODE_DPAD_LEFT  ] != 0 ) pad->State.X = -1000 ;
//	if( Info->KeyState[ AKEYCODE_DPAD_RIGHT ] != 0 ) pad->State.X =  1000 ;
//	if( Info->KeyState[ AKEYCODE_DPAD_UP    ] != 0 ) pad->State.Y = -1000 ;
//	if( Info->KeyState[ AKEYCODE_DPAD_DOWN  ] != 0 ) pad->State.Y =  1000 ;
//
//	if( Info->KeyState[ AKEYCODE_J          ] != 0 ) pad->State.Z  = -1000 ;
//	if( Info->KeyState[ AKEYCODE_L          ] != 0 ) pad->State.Z  =  1000 ;
//	if( Info->KeyState[ AKEYCODE_I          ] != 0 ) pad->State.Rz = -1000 ;
//	if( Info->KeyState[ AKEYCODE_K          ] != 0 ) pad->State.Rz =  1000 ;
//
//	if( Info->KeyState[ AKEYCODE_2          ] != 0 ) pad->State.Buttons[  0 ] = 0x80 ;
//	if( Info->KeyState[ AKEYCODE_3          ] != 0 ) pad->State.Buttons[  1 ] = 0x80 ;
//	if( Info->KeyState[ AKEYCODE_1          ] != 0 ) pad->State.Buttons[  2 ] = 0x80 ;
//	if( Info->KeyState[ AKEYCODE_4          ] != 0 ) pad->State.Buttons[  3 ] = 0x80 ;
//	if( Info->KeyState[ AKEYCODE_5          ] != 0 ) pad->State.Buttons[  4 ] = 0x80 ;
//	if( Info->KeyState[ AKEYCODE_6          ] != 0 ) pad->State.Buttons[  5 ] = 0x80 ;
//	if( Info->KeyState[ AKEYCODE_7          ] != 0 ) pad->State.Buttons[  6 ] = 0x80 ;
//	if( Info->KeyState[ AKEYCODE_8          ] != 0 ) pad->State.Buttons[  7 ] = 0x80 ;
//	if( Info->KeyState[ AKEYCODE_9          ] != 0 ) pad->State.Buttons[  8 ] = 0x80 ;
//	if( Info->KeyState[ AKEYCODE_0          ] != 0 ) pad->State.Buttons[  9 ] = 0x80 ;
//
//	if( Info->KeyState[ AKEYCODE_DEL        ] != 0 ) pad->State.Buttons[ 10 ] = 0x80 ;
//	if( Info->KeyState[ AKEYCODE_ENTER      ] != 0 ) pad->State.Buttons[ 11 ] = 0x80 ;
//
//	if( Info->KeyState[ AKEYCODE_D ] )
//	{
//		if( Info->KeyState[ AKEYCODE_S ] )
//		{
//			pad->State.POV[ 0 ] = 13500 ;
//		}
//		else
//		if( Info->KeyState[ AKEYCODE_W ] )
//		{
//			pad->State.POV[ 0 ] = 4500 ;
//		}
//		else
//		{
//			pad->State.POV[ 0 ] = 9000 ;
//		}
//	}
//	else
//	if( Info->KeyState[ AKEYCODE_A ] )
//	{
//		if( Info->KeyState[ AKEYCODE_S ] )
//		{
//			pad->State.POV[ 0 ] = 22500 ;
//		}
//		else
//		if( Info->KeyState[ AKEYCODE_W ] )
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
//		if( Info->KeyState[ AKEYCODE_S ] )
//		{
//			pad->State.POV[ 0 ] = 18000 ;
//		}
//		else
//		if( Info->KeyState[ AKEYCODE_W ] )
//		{
//			pad->State.POV[ 0 ] = 0 ;
//		}
//	}

	// �I��
	return 0 ;
}

// �p�b�h�G�t�F�N�g�̍Đ���Ԃ��X�V����֐��̊��ˑ�����
extern int RefreshEffectPlayState_PF( void )
{
	// �I��
	return 0 ;
}

// �w��̃p�b�h���U���ɑΉ����Ă��邩�ǂ������擾����( TRUE:�Ή����Ă���  FALSE:�Ή����Ă��Ȃ� )
extern int CheckJoypadVibrationEnable_PF( INPUTPADDATA *pad, int EffectIndex )
{
	return FALSE ;
}

// �w��̓��̓f�o�C�X�� XInput �ɑΉ����Ă��邩�ǂ������擾���鏈���̊��ˑ�����( �߂�l  TRUE:XInput�Ή��̓��̓f�o�C�X  FALSE:XInput��Ή��̓��̓f�o�C�X   -1:�G���[ )( DX_INPUT_KEY �� DX_INPUT_KEY_PAD1 �ȂǁA�L�[�{�[�h�����ރ^�C�v�� InputType �ɓn���ƃG���[�ƂȂ� -1 ��Ԃ� )�̊��ˑ�����
extern int CheckJoypadXInput_PF( int InputType )
{
	return FALSE ;
}

// �W���C�p�b�h�̃^�C�v���擾����( �߂�l  -1:�G���[  0�ȏ�:�W���C�p�b�h�^�C�v( DX_PADTYPE_XBOX_360 �Ȃ� ) )
extern int GetJoypadType_PF( int InputType )
{
	return DX_PADTYPE_OTHER ;
}

// �}�E�X�̃{�^���̏�Ԃ𓾂鏈���̊��ˑ�����
extern int GetMouseInput_PF( void )
{
	int res = 0 ;
	int i ;

	for( i = 0 ; i < InputSysData.PF.SourceNum[ ANDR_INPUT_SOURCE_MOUSE ] ; i ++ )
	{
		INPUT_ANDROID_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.SourceNoToInputInfoTable[ ANDR_INPUT_SOURCE_MOUSE ][ i ] ] ;

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

// �����}�E�X�z�C�[���̉�]�ʂ��擾����
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

// �����}�E�X�z�C�[���̉�]�ʂ��擾����
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

// �����}�E�X�z�C�[���̉�]�ʂ��擾����( �߂�l�� float �^ )
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

// �����}�E�X�z�C�[���̉�]�ʂ��擾����( �߂�l�� float �^ )
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

// �}�E�X�̈ʒu���擾����
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

	if( InputSysData.PF.SourceNum[ ANDR_INPUT_SOURCE_MOUSE ] > 0 )
	{
		int ScreenX, ScreenY ;
		INPUT_ANDROID_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.SourceNoToInputInfoTable[ ANDR_INPUT_SOURCE_MOUSE ][ 0 ] ] ;

		ScreenX = ( int )Info->AxisX ;
		ScreenY = ( int )Info->AxisY ;

		ScreenX = ( int )InputSysData.PF.MouseX ;
		ScreenY = ( int )InputSysData.PF.MouseY ;
		ConvScreenPositionToDxScreenPosition( ScreenX, ScreenY, XBuf, YBuf ) ;
	}

	return 0 ;
}

// �}�E�X�̈ʒu���Z�b�g����
extern int SetMousePoint_PF( int PointX , int PointY )
{
	return 0 ;
}

// �W���C�p�b�h�̖����]�[���̐ݒ���s���֐��̊��ˑ�����
extern int SetJoypadDeadZone_PF( INPUTPADDATA *pad )
{
	// ����I��
	return 0 ;
}

// �f�o�C�X�h�c����l�������ׂ����͏��ԍ����擾����
extern int GetAndroidDeviceIdToInputInfoNo( int32_t Source, int32_t DeviceId )
{
	int i ;
//	int Src ;
//
//	for( Src = 0 ; Src < ANDR_INPUT_SOURCE_NUM ; Src ++ )
//	{
//		if( g_AndroidInputSourceTable[ Src ] == Source )
//		{
//			break ;
//		}
//	}
//	if( Src == ANDR_INPUT_SOURCE_NUM )
//	{
//		return -1 ;
//	}

	for( i = 0 ; i < InputSysData.PF.UseInputInfoNum ; i ++ )
	{
		if( /* InputSysData.PF.InputInfo[ i ].Source   == Source   && */
			   InputSysData.PF.InputInfo[ i ].DeviceId == DeviceId )
		{
			int UpdateFlag = FALSE ;

			if( ( InputSysData.PF.InputInfo[ i ].Source & Source ) != Source )
			{
				UpdateFlag = TRUE ;
			}

			InputSysData.PF.InputInfo[ i ].Source |= Source ;
			InputSysData.PF.InputInfo[ i ].UpdateCount = InputSysData.PF.UpdateCount ;
			InputSysData.PF.UpdateCount ++ ;

			if( UpdateFlag )
			{
				RefreshAndroidSourceNoToInputInfoTable( Source ) ;
				RefreshAndroidGamePadSourceNoToInputInfoTable() ;
			}
			return i ;
		}
	}

	if( InputSysData.PF.UseInputInfoNum == ANDR_DEVICE_MAX_NUM )
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

		RefreshAndroidSourceNoToInputInfoTable( Source ) ;
		RefreshAndroidGamePadSourceNoToInputInfoTable() ;

		return MinUpdateCountNo ;
	}

	i = InputSysData.PF.UseInputInfoNum ;
	InputSysData.PF.UseInputInfoNum ++ ;

	_MEMSET( &InputSysData.PF.InputInfo[ i ], 0, sizeof( InputSysData.PF.InputInfo[ i ] ) ) ;
	InputSysData.PF.InputInfo[ i ].Source = Source ;
	InputSysData.PF.InputInfo[ i ].DeviceId = DeviceId ;
	InputSysData.PF.InputInfo[ i ].UpdateCount = InputSysData.PF.UpdateCount ;
	InputSysData.PF.UpdateCount ++ ;

	RefreshAndroidSourceNoToInputInfoTable( Source ) ;
	RefreshAndroidGamePadSourceNoToInputInfoTable() ;
	
	return i ;
}

// ���̓\�[�X�ԍ��Ɠ��͏��Ƃ̑Ή��e�[�u�����X�V����
extern int RefreshAndroidSourceNoToInputInfoTable( int32_t Source )
{
	INPUT_ANDROID_DEVICE_INFO *Info ;
	int *SourceNoTable ;
	int i, j ;
	int Num ;
	int NoTable[ ANDR_DEVICE_MAX_NUM ] ;
	INPUT_ANDROID_DEVICE_INFO *InfoTable[ ANDR_DEVICE_MAX_NUM ] ;
	int Src ;

	for( Src = 0 ; Src < ANDR_INPUT_SOURCE_NUM ; Src ++ )
	{
		if( Source == g_AndroidInputSourceTable[ Src ] )
		{
			break ;
		}
	}
	if( Src == ANDR_INPUT_SOURCE_NUM )
	{
		return -1 ;
	}

	Num = 0 ;
	Info = InputSysData.PF.InputInfo ;
	for( i = 0 ; i < InputSysData.PF.UseInputInfoNum ; i ++, Info ++ )
	{
		if( ( Info->Source & Source ) == Source )
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

	// �I��
	return 0 ;
}

// �Q�[���p�b�h�̔ԍ��Ɠ��͏��Ƃ̑Ή��e�[�u�����X�V����
extern int RefreshAndroidGamePadSourceNoToInputInfoTable( void )
{
	INPUT_ANDROID_DEVICE_INFO *Info ;
	int *SourceNoTable ;
	int i, j ;
	int Num ;
	int NoTable[ ANDR_DEVICE_MAX_NUM ] ;
	INPUT_ANDROID_DEVICE_INFO *InfoTable[ ANDR_DEVICE_MAX_NUM ] ;

	Num = 0 ;
	Info = InputSysData.PF.InputInfo ;
	for( i = 0 ; i < InputSysData.PF.UseInputInfoNum ; i ++, Info ++ )
	{
		// �c�w���C�u�������Q�[���p�b�h�Ƃ��Ĉ����v�f�������Ă���ꍇ�̓Q�[���p�b�h�Ƃ���
		if( ( ( Info->Source & AINPUT_SOURCE_GAMEPAD  ) == AINPUT_SOURCE_GAMEPAD ) ||
			( ( Info->Source & AINPUT_SOURCE_JOYSTICK ) == AINPUT_SOURCE_JOYSTICK ) )
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

	// �I��
	return 0 ;
}

// ���̓C�x���g����������
extern int32_t ProcessInputEvent( AInputEvent* event )
{
	int32_t InputType ;
	int32_t Source ;
	int32_t DeviceId ;
	int InputNo ;

	Source		= AInputEvent_getSource( event ) ;
	InputType	= AInputEvent_getType( event ) ;
	DeviceId	= AInputEvent_getDeviceId( event ) ;

	InputNo = GetAndroidDeviceIdToInputInfoNo( Source, DeviceId ) ;

	if( InputType == AINPUT_EVENT_TYPE_MOTION )
	{
		TOUCHINPUTDATA TouchInputData ;
		int32_t PointerCount ;
		int32_t Action ;
		int32_t PIndex ;
		Action = AMotionEvent_getAction( event ) ;
		PIndex = ( Action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK ) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT ;
		Action &= AMOTION_EVENT_ACTION_MASK ;

		if( ( Source & AINPUT_SOURCE_TOUCHSCREEN ) == AINPUT_SOURCE_TOUCHSCREEN ||
			( Source & AINPUT_SOURCE_TOUCHPAD    ) == AINPUT_SOURCE_TOUCHPAD )
		{
			TouchInputData.PointNum = 0 ;
			TouchInputData.Time = ( LONGLONG )AMotionEvent_getEventTime( event ) ;
			TouchInputData.Source = Source ;

			if( Action != AMOTION_EVENT_ACTION_UP &&
				Action != AMOTION_EVENT_ACTION_HOVER_ENTER &&
				Action != AMOTION_EVENT_ACTION_HOVER_EXIT &&
				Action != AMOTION_EVENT_ACTION_HOVER_MOVE )
			{
				PointerCount = AMotionEvent_getPointerCount( event ) ;
				if( PointerCount > 0 )
				{
					int32_t i ;
					TOUCHINPUTPOINT *TouchPoint ;

					TouchPoint = TouchInputData.Point ;
					for( i = 0; i < PointerCount; i++ )
					{
						int ScreenX, ScreenY ;

						if( PIndex == i && Action == AMOTION_EVENT_ACTION_POINTER_UP )
						{
							continue ;
						}

						TouchPoint->Device = 0 ;
						TouchPoint->ID = AMotionEvent_getPointerId( event, i ) ;
						ScreenX = AMotionEvent_getX( event, i ) ;
						ScreenY = AMotionEvent_getY( event, i ) ;
						ConvScreenPositionToDxScreenPosition( ScreenX, ScreenY, &TouchPoint->PositionX, &TouchPoint->PositionY ) ;

						TouchPoint->Pressure    = AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_PRESSURE,    i ) ;
						TouchPoint->Orientation = AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_ORIENTATION, i ) ;
						TouchPoint->Tilt        = AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_TILT,        i ) ;
						TouchPoint->ToolType    = AMotionEvent_getToolType( event, i ) ;

						TouchInputData.PointNum ++ ;
						TouchPoint ++ ;
					}
				}
			}

			AddTouchInputData( &TouchInputData ) ;
		}

		if( ( Source & AINPUT_SOURCE_STYLUS      ) == AINPUT_SOURCE_STYLUS &&
			( Source & AINPUT_SOURCE_TOUCHSCREEN ) != AINPUT_SOURCE_TOUCHSCREEN )
		{
			TouchInputData.PointNum = 0 ;
			TouchInputData.Time = ( LONGLONG )AMotionEvent_getEventTime( event ) ;
			TouchInputData.Source = Source ;

			if( Action != AMOTION_EVENT_ACTION_HOVER_EXIT )
			{
				PointerCount = AMotionEvent_getPointerCount( event ) ;
				if( PointerCount > 0 )
				{
					int32_t i ;
					TOUCHINPUTPOINT *TouchPoint ;

					TouchPoint = TouchInputData.Point ;
					for( i = 0; i < PointerCount; i++ )
					{
						int ScreenX, ScreenY ;

						if( PIndex == i && Action == AMOTION_EVENT_ACTION_POINTER_UP )
						{
							continue ;
						}

						TouchPoint->Device = 0 ;
						TouchPoint->ID = AMotionEvent_getPointerId( event, i ) ;
						ScreenX = AMotionEvent_getX( event, i ) ;
						ScreenY = AMotionEvent_getY( event, i ) ;
						ConvScreenPositionToDxScreenPosition( ScreenX, ScreenY, &TouchPoint->PositionX, &TouchPoint->PositionY ) ;

						TouchPoint->Pressure    = AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_PRESSURE,    i ) ;
						TouchPoint->Orientation = AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_ORIENTATION, i ) ;
						TouchPoint->Tilt        = AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_TILT,        i ) ;
						TouchPoint->ToolType    = AMotionEvent_getToolType( event, i ) ;

						if( TouchPoint->ToolType != 0 )
						{
							TouchInputData.PointNum ++ ;
							TouchPoint ++ ;
						}
					}
				}
			}

			AddTouchInputData( &TouchInputData ) ;
		}

		if( ( Source & AINPUT_SOURCE_MOUSE ) == AINPUT_SOURCE_MOUSE )
		{
			if( InputNo >= 0 && InputNo < ANDR_DEVICE_MAX_NUM )
			{
				int LogType = -1 ;

				if( PIndex >= 0 && PIndex < ANDR_POINTER_MAX_NUM )
				{
					if( Action == AMOTION_EVENT_ACTION_POINTER_DOWN )
					{
						LogType = MOUSE_INPUT_LOG_DOWN ;
						InputSysData.PF.InputInfo[ InputNo ].PointerState[ PIndex ] = 1 ;
					}
					else
					if( Action == AMOTION_EVENT_ACTION_POINTER_UP )
					{
						LogType = MOUSE_INPUT_LOG_UP ;
						InputSysData.PF.InputInfo[ InputNo ].PointerState[ PIndex ] = 0 ;
					}
				}

				InputSysData.PF.InputInfo[ InputNo ].ButtonState	= AMotionEvent_getButtonState( event ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisX			= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_X,			0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisY			= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_Y,			0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].Wheel			= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_WHEEL,		0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].VScroll		= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_VSCROLL,		0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].HScroll		= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_HSCROLL,		0 ) ;

				InputSysData.PF.MouseX = InputSysData.PF.InputInfo[ InputNo ].AxisX ;
				InputSysData.PF.MouseY = InputSysData.PF.InputInfo[ InputNo ].AxisY ;

				InputSysData.MouseMoveZ  += InputSysData.PF.InputInfo[ InputNo ].VScroll ;
				InputSysData.MouseMoveHZ += InputSysData.PF.InputInfo[ InputNo ].HScroll ;

				// ���O��ǉ�
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
			}

			// �}�E�X���͂��������ۂ̓^�b�v�̓��͂𖳌�������( �X�^�C���X�y���̏ꍇ�͖��������Ȃ� )
			if( ( Source & AINPUT_SOURCE_STYLUS ) == 0 )
			{
				TouchInputData.PointNum = 0 ;
				TouchInputData.Time = ( LONGLONG )AMotionEvent_getEventTime( event ) ;

				AddTouchInputData( &TouchInputData ) ;
			}
		}

		if( ( Source & AINPUT_SOURCE_JOYSTICK ) == AINPUT_SOURCE_JOYSTICK )
		{
			if( InputNo >= 0 && InputNo < ANDR_DEVICE_MAX_NUM )
			{
				InputSysData.PF.InputInfo[ InputNo ].AxisX			= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_X,			0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisY			= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_Y,			0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisZ			= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_Z,			0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisRx			= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_RX,			0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisRy			= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_RY,			0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisRz			= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_RZ,			0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisHatX		= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_HAT_X,		0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisHatY		= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_HAT_Y,		0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisLTrigger	= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_LTRIGGER,	0 ) ;
				InputSysData.PF.InputInfo[ InputNo ].AxisRTrigger	= AMotionEvent_getAxisValue( event, AMOTION_EVENT_AXIS_RTRIGGER,	0 ) ;
			}
		}

		return 1 ;
	}
	else
	if( InputType == AINPUT_EVENT_TYPE_KEY )
	{
		int32_t Action ;
		int32_t KeyCode ;
		int32_t res = 1 ; 

		Action = AKeyEvent_getAction( event ) ;
		KeyCode = AKeyEvent_getKeyCode( event ) ;
		if( InputNo >= 0 && InputNo < ANDR_DEVICE_MAX_NUM )
		{
			if( KeyCode < ANDR_KEYCODE_MAX )
			{
				if( Action == AKEY_EVENT_ACTION_DOWN )
				{
					InputSysData.PF.InputInfo[ InputNo ].KeyState[ KeyCode ] = 1 ;
				}
				else
				if( Action == AKEY_EVENT_ACTION_UP )
				{
					InputSysData.PF.InputInfo[ InputNo ].KeyState[ KeyCode ] = 0 ;
				}
			}
		}

		if( KeyCode == AKEYCODE_VOLUME_UP   ||
			KeyCode == AKEYCODE_VOLUME_DOWN ||
			KeyCode == AKEYCODE_POWER       ||
			KeyCode == AKEYCODE_HOME        ||
			KeyCode == AKEYCODE_CAMERA )
		{
			res = 0 ;
		}

		return res ;
	}

	return 0 ;
}


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_INPUT


