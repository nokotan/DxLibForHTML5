// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p���͏��v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.22a
// 
// -------------------------------------------------------------------------------

#ifndef DX_INPUTANDROID_H
#define DX_INPUTANDROID_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_INPUT

// �C���N���[�h ------------------------------------------------------------------
#include "../DxLib.h"
#include <Android/input.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

#define ANDR_INPUT_LOG_NUM					(64)
#define ANDR_DEVICE_MAX_NUM					(64)
#define ANDR_POINTER_MAX_NUM				(256)
#define ANDR_KEYCODE_MAX					(320)

// ���̓\�[�X
#define ANDR_INPUT_SOURCE_UNKNOWN			(0)
#define ANDR_INPUT_SOURCE_KEYBOARD			(1)
#define ANDR_INPUT_SOURCE_DPAD				(2)
#define ANDR_INPUT_SOURCE_GAMEPAD			(3)
#define ANDR_INPUT_SOURCE_TOUCHSCREEN		(4)
#define ANDR_INPUT_SOURCE_MOUSE				(5)
#define ANDR_INPUT_SOURCE_STYLUS			(6)
#define ANDR_INPUT_SOURCE_TRACKBALL			(7)
#define ANDR_INPUT_SOURCE_TOUCHPAD			(8)
#define ANDR_INPUT_SOURCE_TOUCH_NAVIGATION	(9)
#define ANDR_INPUT_SOURCE_JOYSTICK			(10)
#define ANDR_INPUT_SOURCE_NUM				(11)

// �\���̒�` --------------------------------------------------------------------

// �U���̊��ˑ����
struct INPUTVIBRATIONDATA_PF
{
	int						Dummy ;
} ;

// �Q�[���p�b�h�̊��ˑ����
struct INPUTPADDATA_PF
{
	int						Dummy ;
} ;

// ��̓��̓f�o�C�X�̓��͏��
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

// ���̓V�X�e���p���ˑ��f�[�^�\���̌^
struct INPUTSYSTEMDATA_PF
{
	LONGLONG					UpdateCount ;
	int							UseInputInfoNum ;
	INPUT_ANDROID_DEVICE_INFO	InputInfo[ ANDR_DEVICE_MAX_NUM ] ;
	int							SourceNum[ ANDR_INPUT_SOURCE_NUM ] ;
	int							SourceNoToInputInfoTable[ ANDR_INPUT_SOURCE_NUM ][ ANDR_DEVICE_MAX_NUM ] ;
	int							GamePadSourceNum ;											// �Q�[���p�b�h�̐�
	int							GamePadSourceNoToInputInfoTable[ ANDR_DEVICE_MAX_NUM ] ;	// �Q�[���p�b�h�̃i���o�[�� InputInfoTable �̑Ή��e�[�u�� 
	TOUCHINPUTDATA				TouchInputData ;
} ;

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern	int GetAndroidDeviceIdToInputInfoNo( int32_t Source, int32_t DeviceId ) ;	// �f�o�C�X�h�c����l�������ׂ����͏��ԍ����擾����
extern	int RefreshAndroidSourceNoToInputInfoTable( int32_t Source ) ;				// ���̓\�[�X�ԍ��Ɠ��͏��Ƃ̑Ή��e�[�u�����X�V����
extern	int RefreshAndroidGamePadSourceNoToInputInfoTable( void ) ;					// �Q�[���p�b�h�̔ԍ��Ɠ��͏��Ƃ̑Ή��e�[�u�����X�V����
extern	int32_t ProcessInputEvent( AInputEvent* event ) ;							// ���̓C�x���g����������

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_INPUT

#endif // DX_INPUTANDROID_H
