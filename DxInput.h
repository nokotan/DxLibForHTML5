// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		���͏��v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

#ifndef DX_INPUT_H
#define DX_INPUT_H

#include "DxCompileConfig.h"

#ifndef DX_NON_INPUT

// �C���N���[�h ------------------------------------------------------------------
#include "DxLib.h"
#include "DxStatic.h"

#ifdef WINDOWS_DESKTOP_OS
#include "Windows/DxInputWin.h"
#endif // WINDOWS_DESKTOP_OS

#ifdef __ANDROID__
#include "Android/DxInputAndroid.h"
#endif // __ANDROID__

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
		#include "iOS/DxInputiOS.h"
    #endif // TARGET_OS_IPHONE
#endif // __APPLE__




#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �ێ�����}�E�X�̃N���b�N���
#define MOUSEINPUT_LOG_NUM			(64)

// �������͂̍ő�l
#define DIRINPUT_MAX				(1000)

// �U���p���[�̍ő�l
#define DX_FFNOMINALMAX				(10000)

// ���[�^�[�̔ԍ���`
#define DINPUTPAD_MOTOR_LEFT		0
#define DINPUTPAD_MOTOR_RIGHT		1
#define DINPUTPAD_MOTOR_NUM			2

#define INPUTTOUCH_LOG_NUM			(120)				// �^�b�`���̃��O�̐�

// �\���̒�` --------------------------------------------------------------------

// �^�b�`�p�l���̃^�b�`�̏��
struct INPUTTOUCHDATA
{
	int						LogNum ;							// �L���ȃ^�b�`���O���̐�
	TOUCHINPUTDATA			Log[ INPUTTOUCH_LOG_NUM ] ;			// �^�b�`���O���
	int						LogStartIndex ;						// �^�b�`���O���̐擪�f�[�^���i�[����Ă���C���f�b�N�X

	int						DownLogNum ;						// �^�b�`���ꂽ���W�̃��O�̐�
	TOUCHINPUTPOINT			DownLog[ INPUTTOUCH_LOG_NUM ] ;		// �^�b�`���ꂽ���W�̃��O���
	int						DownLogStartIndex ;					// �^�b�`���ꂽ���W�̃��O���̐擪�f�[�^���i�[����Ă���C���f�b�N�X

	int						UpLogNum ;							// �^�b�`�������ꂽ���W�̃��O�̐�
	TOUCHINPUTPOINT			UpLog[ INPUTTOUCH_LOG_NUM ] ;		// �^�b�`�������ꂽ���W�̃��O���
	int						UpLogStartIndex ;					// �^�b�`�������ꂽ���W�̃��O���̐擪�f�[�^���i�[����Ă���C���f�b�N�X

	int						MouseInputDevice ;					// �}�E�X���͂Ƃ���^�b�`����Device
	int						MouseInputID ;						// �}�E�X���͂Ƃ���^�b�`����ID
	int						MouseInputIndex ;					// �}�E�X���͂Ƃ���^�b�`���̃C���f�b�N�X
	TOUCHINPUTDATA			NowData ;							// �ŐV�̃^�b�`���
} ;

// �U���̏��
struct INPUTVIBRATIONDATA
{
	int						PlayFlag ;							// �G�t�F�N�g���Đ������A�t���O
	int						Power ;								// �G�t�F�N�g�̋���
	int						Time ;								// �G�t�F�N�g�̒���
	int						CompTime ;							// �G�t�F�N�g���J�n���Ă���o�߂�������
	int						BackTime ;							// �G�t�F�N�g�̑O�񒲂ׂ�����

	int						PlayState ;							// �U���̍Đ����(�\�t�g����A�N�e�B�u�ɂȂ�΍Đ���~�����)
	int						SetPower ;							// �U���̐ݒ�p���[

	INPUTVIBRATIONDATA_PF	PF ;								// ���ˑ����
} ;

// �Q�[���p�b�h�̏��
struct INPUTPADDATA
{
	int						GetTime ;							// �擾����
	INPUTVIBRATIONDATA		Effect[ DINPUTPAD_MOTOR_NUM ] ;		// ���[�^�[�̏��
	DWORD					DeadZone ;							// �����]�[��( 65536 = 100% )
	double					DeadZoneD ;							// �����]�[��( 1.0 = 100% )
	int						Buttons ;							// �L���ȃ{�^���̐�

	DINPUT_JOYSTATE			State ;								// ���
	XINPUT_STATE			XInputState ;						// XInput�ł̃p�b�h�̏��

	INPUTPADDATA_PF			PF ;								// ���ˑ����
} ;

// �}�E�X�̓��̓��O���
struct MOUSEINPUTLOGDATA
{
	int						LogType ;							// ���O�^�C�v( MOUSE_INPUT_LOG_DOWN ���� MOUSE_INPUT_LOG_UP )
	int						Button ;							// �N���b�N�����{�^��
	int						ClickX, ClickY ;					// �N���b�N�����N���C�A���g���W
	int						IsDummy ;							// GetMousePoint �� GetMouseInput ���g�p�����_�~�[��񂩂ǂ���
} ;

// ���̓V�X�e���p�f�[�^�\���̌^
struct INPUTSYSTEMDATA
{
	volatile int			InitializeFlag ;					// �����������t���O

	int						NoUseVibrationFlag ;				// �c�����������h���������̐U���@�\���g�p���Ȃ����ǂ����̃t���O
	int						KeyInputGetTime ;					// ��O�ɏ�Ԃ��擾��������
	unsigned char			KeyInputBuf[ 256 ] ;				// �L�[�{�[�h�̓��͏��

	int						KeyToJoypadInputInitializeFlag ;	// KeyToJoypadInput ����x�ł��������������ǂ����̃t���O
	int						KeyToJoypadInput[ MAX_JOYPAD_NUM ][ 32 ][ 4 ] ;	// �W���C�p�b�h�̓��͂ɑΉ������L�[�{�[�h�̓���

	int						MouseInputBufValidFlag ;			// MouseInputBuf ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	BYTE					MouseInputBuf[ 8 ] ;				// �}�E�X�̓��͏��( 0:LEFT 1:RIGHT 2:MIDDLE 3:4�{�^��(XBUTTON1) 4:5�{�^��(XBUTTON2) )
	int						MouseMoveZ ;						// �}�E�X�z�C�[���̈ړ��l
	int						MouseMoveHZ ;						// �}�E�X�̐����z�C�[���̈ړ���

	int						MouseInputLogNum ;						// �}�E�X�̓��͏��̐�( GetMouseInputLog�p )
	MOUSEINPUTLOGDATA		MouseInputLog[ MOUSEINPUT_LOG_NUM ] ;	// �}�E�X�̓��͏��( GetMouseInputLog�p )

	int						MouseInputLog2Num ;							// �}�E�X�̓��͏��̐�( GetMouseInputLog2�p )
	MOUSEINPUTLOGDATA		MouseInputLog2[ MOUSEINPUT_LOG_NUM ] ;	// �}�E�X�̓��͏��( GetMouseInputLog2�p )

	int						MouseInputLog2PrevEnable[ 3 ] ;			// ���߂̃}�E�X�̓��͏�񂪗L�����ǂ���( TRUE:�L��  FALSE:���� )( GetMouseInputLog2�p )
	MOUSEINPUTLOGDATA		MouseInputLog2Prev[ 3 ] ;				// ���߂̃}�E�X�̓��͏��

	int						PadNum ;							// �W���C�p�b�h�̐�
	INPUTPADDATA			Pad[ MAX_JOYPAD_NUM ] ;				// �p�b�h�f�o�C�X���

	int						EndFlag ;

	int						F10Flag ;							// F10 �������ꂽ���t���O
	int						F10InputTime ;						// F10 �������ꂽ����
	int						F12Flag ;							// F12 �������ꂽ���t���O
	int						F12InputTime ;						// F12 �������ꂽ����

	INPUTTOUCHDATA			Touch ;								// �^�b�`�p�l���̃^�b�`���

	INPUTSYSTEMDATA_PF		PF ;								// ���ˑ����
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// ���̓V�X�e���p�f�[�^
extern INPUTSYSTEMDATA InputSysData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// ���̓V�X�e���̏������A�I���֐�
extern	int InitializeInputSystem( void ) ;											// ���̓V�X�e�������������� 
extern	int TerminateInputSystem( void ) ;											// ���̓V�X�e���̌�n��������

extern	int JoypadEffectProcess( void ) ;											// �p�b�h�G�t�F�N�g�Ɋւ���t���[���������s��
extern	int RefreshEffectPlayState( void ) ;										// �p�b�h�G�t�F�N�g�̍Đ���Ԃ��X�V����(�\�t�g����A�N�e�B�u�ɂȂ邱�Ƃ����邽��)
extern	int UpdateKeyboardInputState( int UseProcessMessage = TRUE ) ;				// ���͏�Ԃ̍X�V
extern	int SetupJoypad( void ) ;													// �W���C�p�b�h�̃Z�b�g�A�b�v���s��
extern	int TerminateJoypad( void ) ;												// �W���C�p�b�h�̌�n�����s��

extern	int SetF10Input( void ) ;													// F10 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern	int ResetF10Input( void ) ;													// F10 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern	int SetF12Input( void ) ;													// F12 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern	int ResetF12Input( void ) ;													// F12 �������ꂽ���Ƃɂ���t���O�𗧂Ă�


// �}�E�X�̓��̓��O����ۑ�����
extern	void StockMouseInputLogData(  int Button, int ClickX, int ClickY ) ;
extern	void StockMouseInputLogData2( int Button, int ClickX, int ClickY, int LogType, int IsDummy = FALSE ) ;


// �^�b�`�p�l���֌W�̊֐�
extern	int AddTouchInputData( TOUCHINPUTDATA *TouchData ) ;						// �^�b�`�p�l���̓��͏���ǉ�����


// wchar_t�Ŋ֐�
extern int GetJoypadName_WCHAR_T( int InputType, wchar_t *InstanceNameBuffer, wchar_t *ProductNameBuffer ) ;


// ���ˑ��֌W�֐�
extern	int InitializeInputSystem_PF_Timing0( void ) ;								// ���̓V�X�e�������������鏈���̊��ˑ�����
extern	int TerminateInputSystem_PF_Timing0( void ) ;								// ���̓V�X�e���̌�n�������鏈���̊��ˑ�����

extern	int	AutoInitialize_PF( void ) ;												// �������������s�����ˑ�����

extern	int SetupJoypad_PF( void ) ;												// �W���C�p�b�h�̃Z�b�g�A�b�v�̊��ˑ�����
extern	int TerminateJoypad_PF( void ) ;											// �W���C�p�b�h�̌�n�����s�������̊��ˑ�����

extern	int UpdateKeyboardInputState_PF( int UseProcessMessage = TRUE ) ;			// ���͏�Ԃ̍X�V�̊��ˑ�����
extern	int UpdateJoypadInputState_PF( int PadNo ) ;								// �p�b�h�̓��͏�Ԃ̍X�V�̊��ˑ�����
extern	int RefreshEffectPlayState_PF( void ) ;										// �p�b�h�G�t�F�N�g�̍Đ���Ԃ��X�V����֐��̊��ˑ�����

extern	int CheckJoypadVibrationEnable_PF( INPUTPADDATA *pad, int EffectIndex ) ;	// �w��̃p�b�h���U���ɑΉ����Ă��邩�ǂ������擾����( TRUE:�Ή����Ă���  FALSE:�Ή����Ă��Ȃ� )
extern	int CheckJoypadXInput_PF( int InputType ) ;									// �w��̓��̓f�o�C�X�� XInput �ɑΉ����Ă��邩�ǂ������擾���鏈���̊��ˑ�����( �߂�l  TRUE:XInput�Ή��̓��̓f�o�C�X  FALSE:XInput��Ή��̓��̓f�o�C�X   -1:�G���[ )( DX_INPUT_KEY �� DX_INPUT_KEY_PAD1 �ȂǁA�L�[�{�[�h�����ރ^�C�v�� InputType �ɓn���ƃG���[�ƂȂ� -1 ��Ԃ� )
extern	int GetJoypadType_PF( int InputType ) ;										// �W���C�p�b�h�̃^�C�v���擾����( �߂�l  -1:�G���[  0�ȏ�:�W���C�p�b�h�^�C�v( DX_PADTYPE_XBOX_360 �Ȃ� ) )
extern	int SetJoypadDeadZone_PF( INPUTPADDATA *pad ) ;								// �W���C�p�b�h�̖����]�[���̐ݒ���s���֐��̊��ˑ�����

extern	int		GetMousePoint_PF( int *XBuf, int *YBuf ) ;							// �}�E�X�̈ʒu���擾���鏈���̊��ˑ�����
extern	int		SetMousePoint_PF( int PointX, int PointY ) ;						// �}�E�X�̈ʒu���Z�b�g���鏈���̊��ˑ�����
extern	int		GetMouseInput_PF( void ) ;											// �}�E�X�̃{�^���̏�Ԃ𓾂鏈���̊��ˑ�����
extern	int		GetMouseWheelRotVol_PF(   int CounterReset = TRUE ) ;				// �����}�E�X�z�C�[���̉�]�ʂ��擾����
extern	int		GetMouseHWheelRotVol_PF(  int CounterReset = TRUE ) ;				// �����}�E�X�z�C�[���̉�]�ʂ��擾����
extern	float	GetMouseWheelRotVolF_PF(  int CounterReset = TRUE ) ;				// �����}�E�X�z�C�[���̉�]�ʂ��擾����( �߂�l�� float �^ )
extern	float	GetMouseHWheelRotVolF_PF( int CounterReset = TRUE ) ;				// �����}�E�X�z�C�[���̉�]�ʂ��擾����( �߂�l�� float �^ )



#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_INPUT

#endif // DX_INPUT_H
