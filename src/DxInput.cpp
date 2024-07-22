// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�c�����������h������������v���O����
// 
// 				Ver 3.24d
// 
// -------------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "DxInput.h"

#ifndef DX_NON_INPUT

// �C���N���[�h ------------------------------------------------------------------
#include "DxLib.h"
#include "DxSystem.h"
#include "DxLog.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` -------------------------------------

// �\���̒�` --------------------------------------------------------------------

// �萔��` ----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// ���̓V�X�e���p�f�[�^
INPUTSYSTEMDATA InputSysData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

static	int UpdateJoypadInputState( int padno ) ;								// �p�b�h�̓��͏�Ԃ̍X�V

// �v���O���� --------------------------------------------------------------------

// ���̓V�X�e���̏������A�I���֐�

// ���̓V�X�e��������������
extern int InitializeInputSystem( void )
{
	// ���ɏ���������Ă����牽�������ɏI��
	if( InputSysData.InitializeFlag )
	{
		return 0 ;
	}

	// �����������t���O�𗧂Ă�
	InputSysData.InitializeFlag = TRUE ;

	// �f�t�H���g�̃f�b�h�]�[�����ݒ肳��Ă��Ȃ�������ݒ肷��
	if( InputSysData.EnablePadDefaultDeadZone == FALSE )
	{
		InputSysData.EnablePadDefaultDeadZone = TRUE ;
		InputSysData.PadDefaultDeadZone  = PAD_DEFAULT_DEADZONE ;
		InputSysData.PadDefaultDeadZoneD = PAD_DEFAULT_DEADZONE_D ;
	}

	// ���ˑ�����
	if( InitializeInputSystem_PF_Timing0() != 0 )
	{
		// �����������t���O��|��
		InputSysData.InitializeFlag = FALSE ;

		return -1 ;
	}

	// POV ����͖����̏�Ԃɂ��Ă���
	{
		int i ;
		int j ;

		for( i = 0 ; i < MAX_JOYPAD_NUM ; i ++ )
		{
			for( j = 0 ; j < 4 ; j ++ )
			{
				InputSysData.Pad[ i ].State.POV[ j ] = 0xffffffff ;
			}
		}
	}

	// ����I��
	return 0 ;
}

// ���̓V�X�e���̎g�p���I������
extern int TerminateInputSystem( void )
{
	// ���Ɍ�n�����I����Ă����牽�������ɏI��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return 0 ;
	}

	// ���ˑ�����
	if( TerminateInputSystem_PF_Timing0() != 0 )
	{
		return -1 ;
	}

	// �����������t���O��|��
	InputSysData.InitializeFlag = FALSE ;

	// ����I��
	return 0 ;
}

// �W���C�p�b�h�̃Z�b�g�A�b�v���s��
extern int SetupJoypad( void )
{
	// ����������
	if( InputSysData.InitializeFlag == FALSE )
	{
		return -1 ;
	}

	// ���ˑ�����
	if( SetupJoypad_PF() != 0 )
	{
		return -1 ;
	}

	DXST_LOGFILE_ADDUTF16LE( "\xb8\x30\xe7\x30\xa4\x30\xd1\x30\xc3\x30\xc9\x30\x6e\x30\x1d\x52\x1f\x67\x16\x53\x6f\x30\x63\x6b\x38\x5e\x6b\x30\x42\x7d\x86\x4e\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�W���C�p�b�h�̏������͐���ɏI�����܂���\n" @*/ ) ;

	// �I��
	return 0 ;
}

// �W���C�p�b�h�̌�n�����s��
extern int TerminateJoypad( void )
{
	// ����������
	if( InputSysData.InitializeFlag == FALSE )
	{
		return -1 ;
	}

	// ���ˑ�����
	if( TerminateJoypad_PF() != 0 )
	{
		return -1 ;
	}

	// �I��
	return 0 ;
}









// F10 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern int SetF10Input( void )
{
	InputSysData.F10Flag = TRUE ;
//	InputSysData.F10InputTime = NS_GetNowCount( FALSE ) ;

	// �I��
	return 0 ;
}

// F10 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern int ResetF10Input( void )
{
	InputSysData.F10Flag = FALSE ;

	// �I��
	return 0 ;
}

// F12 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern int SetF12Input( void )
{
	InputSysData.F12Flag = TRUE ;
//	InputSysData.F12InputTime = NS_GetNowCount( FALSE ) ;

	// �I��
	return 0 ;
}

// F12 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern int ResetF12Input( void )
{
	InputSysData.F12Flag = FALSE ;

	// �I��
	return 0 ;
}











// �}�E�X�֌W�̊֐�

// �}�E�X�̓��͏���ۑ�����
extern void StockMouseInputLogData( int Button, int ClickX, int ClickY )
{
	MOUSEINPUTLOGDATA *MInput ;

	// ���O�̐����ő吔�ɒB���Ă����牽�������I��
	if( InputSysData.MouseInputLogNum >= MOUSEINPUT_LOG_NUM ) return ;

	// ����ۑ�
	MInput = &InputSysData.MouseInputLog[ InputSysData.MouseInputLogNum ] ;
	MInput->ClickX = ClickX ;
	MInput->ClickY = ClickY ;
	MInput->Button = Button ;
	MInput->LogType = MOUSE_INPUT_LOG_DOWN ;

	// ���̐��𑝂₷
	InputSysData.MouseInputLogNum ++ ;
}

// �}�E�X�̓��͏���ۑ����� GetMouseInputLog2 �p
extern void StockMouseInputLogData2( int Button, int ClickX, int ClickY, int LogType, int IsDummy )
{
	MOUSEINPUTLOGDATA *MInput ;
	int Index = 0 ;

	// ���O�̐����ő吔�ɒB���Ă����牽�������I��
	if( InputSysData.MouseInputLog2Num >= MOUSEINPUT_LOG_NUM ) return ;

	// ���߂̃{�^�����O�ɋL�^���邽�߂̃C���f�b�N�X������o���Ă���
	switch( Button )
	{
	case MOUSE_INPUT_LEFT   : Index = 0 ; break ;
	case MOUSE_INPUT_RIGHT  : Index = 1 ; break ;
	case MOUSE_INPUT_MIDDLE : Index = 2 ; break ;
	}

	// �_�~�[���ł͂Ȃ��ꍇ�݂̂̏������s��
	if( IsDummy == FALSE )
	{
		int i ;

		// �_�~�[�̏��Əd��������ł������ꍇ�̓_�~�[���ɏ㏑������
		for( i = InputSysData.MouseInputLog2Num - 1 ; i >= 0 ; i -- )
		{
			if( InputSysData.MouseInputLog2[ i ].Button != Button ||
				InputSysData.MouseInputLog2[ i ].LogType != LogType )
			{
				continue ;
			}

			if( InputSysData.MouseInputLog2[ i ].IsDummy == TRUE )
			{
				MInput = &InputSysData.MouseInputLog2[ InputSysData.MouseInputLog2Num ] ;
				MInput->ClickX = ClickX ;
				MInput->ClickY = ClickY ;
				MInput->Button = Button ;
				MInput->LogType = LogType ;
				MInput->IsDummy = IsDummy ;

				// ���߂̃}�E�X�̓��͏����X�V
				InputSysData.MouseInputLog2PrevEnable[ Index ] = TRUE ;
				InputSysData.MouseInputLog2Prev[ Index ] = *MInput ;

				return ;
			}

			break ;
		}

		// ����̃{�^���œ��� LogType ���A�������ꍇ�͑΂̑��삪�E�B���h�E�O�ōs��ꂽ�Ɣ��f���� ClickX=-1, ClickY=-1 �̃��O��ǉ�����
		if( InputSysData.MouseInputLog2PrevEnable[ Index ] &&
			InputSysData.MouseInputLog2Prev[ Index ].LogType == LogType )
		{
			// ����ۑ�
			MInput = &InputSysData.MouseInputLog2[ InputSysData.MouseInputLog2Num ] ;
			MInput->ClickX = -100 ;
			MInput->ClickY = -100 ;
			MInput->Button = Button ;
			MInput->LogType = LogType == MOUSE_INPUT_LOG_DOWN ? MOUSE_INPUT_LOG_UP : MOUSE_INPUT_LOG_DOWN ;
			MInput->IsDummy = TRUE ;

			// ���߂̃}�E�X�̓��͏����X�V
			InputSysData.MouseInputLog2PrevEnable[ Index ] = TRUE ;
			InputSysData.MouseInputLog2Prev[ Index ] = *MInput ;

			// ���̐��𑝂₷
			InputSysData.MouseInputLog2Num ++ ;

			// ���O�̐����ő吔�ɒB���Ă����炱���ŏI��
			if( InputSysData.MouseInputLog2Num >= MOUSEINPUT_LOG_NUM )
			{
				return ;
			}
		}
	}

	// ����ۑ�
	MInput = &InputSysData.MouseInputLog2[ InputSysData.MouseInputLog2Num ] ;
	MInput->ClickX = ClickX ;
	MInput->ClickY = ClickY ;
	MInput->Button = Button ;
	MInput->LogType = LogType ;
	MInput->IsDummy = IsDummy ;

	// ���̐��𑝂₷
	InputSysData.MouseInputLog2Num ++ ;

	// ���߂̃}�E�X���͏����X�V
	InputSysData.MouseInputLog2PrevEnable[ Index ] = TRUE ;
	InputSysData.MouseInputLog2Prev[ Index ] = *MInput ;
}

// �}�E�X����

// �}�E�X�̃{�^���������������擾����( �߂�l  -1:���O���������� )
extern int NS_GetMouseInputLog( int *Button, int *ClickX, int *ClickY, int LogDelete )
{
	MOUSEINPUTLOGDATA *MInput ;

	// ���O������������ -1 ��Ԃ�
	if( InputSysData.MouseInputLogNum == 0 ) return -1 ;

	// ����Ԃ�
	MInput = &InputSysData.MouseInputLog[ 0 ] ;
	if( Button ) *Button = MInput->Button ;
	if( ClickX ) *ClickX = MInput->ClickX ;
	if( ClickY ) *ClickY = MInput->ClickY ;

	// ���O���폜����w�肪����ꍇ�͍폜����
	if( LogDelete )
	{
		InputSysData.MouseInputLogNum -- ;
		if( InputSysData.MouseInputLogNum )
			_MEMMOVE( InputSysData.MouseInputLog, &InputSysData.MouseInputLog[ 1 ], sizeof( MOUSEINPUTLOGDATA ) * InputSysData.MouseInputLogNum ) ;
	}

	// �I��
	return 0 ;
}

// �}�E�X�̃{�^�����������藣�����肵�������擾����( �߂�l  -1:���O���������� )
extern int NS_GetMouseInputLog2( int *Button, int *ClickX, int *ClickY, int *LogType, int LogDelete )
{
	MOUSEINPUTLOGDATA *MInput ;

	// �⏕����
	{
		static int ButtonTable[ 3 ] = { MOUSE_INPUT_LEFT, MOUSE_INPUT_RIGHT, MOUSE_INPUT_MIDDLE } ;
		int NowInput = NS_GetMouseInput() ;
		int i ;

		for( i = 0 ; i < 3 ; i ++ )
		{
			// ���߂̃��O���w�{�^�����������x�ŁA�����݃{�^����������Ă�����}�E�X�̃{�^���𗣂����Ƃ������X�g�b�N����
			if( InputSysData.MouseInputLog2PrevEnable[ i ] &&
				InputSysData.MouseInputLog2Prev[ i ].LogType == MOUSE_INPUT_LOG_DOWN &&
				( NowInput & ButtonTable[ i ] ) == 0 )
			{
				int mx, my ;
				NS_GetMousePoint( &mx, &my ) ;
				StockMouseInputLogData2( ButtonTable[ i ], mx, my, MOUSE_INPUT_LOG_UP ) ;
			}

			// ���߂̃��O���������A�w�{�^���𗣂����x�ŁA�����݃{�^����������Ă�����}�E�X�̃{�^�����������Ƃ������X�g�b�N����
			if( ( InputSysData.MouseInputLog2PrevEnable[ i ] == FALSE ||
				  InputSysData.MouseInputLog2Prev[ i ].LogType == MOUSE_INPUT_LOG_UP ) &&
				( NowInput & ButtonTable[ i ] ) != 0 )
			{
				int mx, my ;
				NS_GetMousePoint( &mx, &my ) ;
				StockMouseInputLogData2( ButtonTable[ i ], mx, my, MOUSE_INPUT_LOG_DOWN ) ;
			}
		}
	}

	// ���O�����������珈���𕪊�
	if( InputSysData.MouseInputLog2Num == 0 )
	{
		return -1 ;
	}

	// ����Ԃ�
	MInput = &InputSysData.MouseInputLog2[ 0 ] ;
	if( Button  ) *Button  = MInput->Button ;
	if( ClickX  ) *ClickX  = MInput->ClickX ;
	if( ClickY  ) *ClickY  = MInput->ClickY ;
	if( LogType ) *LogType = MInput->LogType ;

	// ���O���폜����w�肪����ꍇ�͍폜����
	if( LogDelete )
	{
		InputSysData.MouseInputLog2Num -- ;
		if( InputSysData.MouseInputLog2Num )
			_MEMMOVE( InputSysData.MouseInputLog2, &InputSysData.MouseInputLog2[ 1 ], sizeof( MOUSEINPUTLOGDATA ) * InputSysData.MouseInputLog2Num ) ;
	}

	// �I��
	return 0 ;
}

// �}�E�X�̈ʒu���擾����
extern int NS_GetMousePoint( int *XBuf, int *YBuf )
{
//	// �^�b�`�p�l���̓��͂�����ꍇ�͂�����}�E�X�|�C���^�̈ʒu�Ƃ���
//	if( InputSysData.Touch.NowData.PointNum > 0 && InputSysData.Touch.MouseInputID >= 0 )
//	{
//		if( XBuf != NULL )
//		{
//			*XBuf = InputSysData.Touch.NowData.Point[ InputSysData.Touch.MouseInputIndex ].PositionX ;
//		}
//
//		if( YBuf != NULL )
//		{
//			*YBuf = InputSysData.Touch.NowData.Point[ InputSysData.Touch.MouseInputIndex ].PositionY ;
//		}
//	}
//	else
	{
		// ����ȊO�̏ꍇ�͊��ˑ��̃}�E�X��擾���������s����
		return GetMousePoint_PF( XBuf, YBuf ) ;
	}

//	// ����I��
//	return 0 ;
}

// �}�E�X�̈ʒu���Z�b�g����
extern int NS_SetMousePoint( int PointX , int PointY )
{
	// ���ˑ����������s����
	return SetMousePoint_PF( PointX, PointY ) ;
}

// �}�E�X�̃{�^���̏�Ԃ𓾂� 
extern int NS_GetMouseInput( void )
{
	int MInput ;

	// ���ˑ����������s
	MInput = GetMouseInput_PF() ;

//	// �^�b�`�p�l���̓��͂�����ꍇ�͍��N���b�N����Ă��邱�Ƃɂ���
//	if( InputSysData.Touch.NowData.PointNum > 0 && InputSysData.Touch.MouseInputID >= 0 )
//	{
//		MInput |= MOUSE_INPUT_LEFT ;
//	}
	
	return MInput ;
}

// �}�E�X�z�C�[���̉�]�ʂ𓾂�
extern int NS_GetMouseWheelRotVol( int CounterReset )
{
	return GetMouseWheelRotVol_PF( CounterReset ) ;
}

// �����}�E�X�z�C�[���̉�]�ʂ𓾂�
extern int NS_GetMouseHWheelRotVol( int CounterReset )
{
	return GetMouseHWheelRotVol_PF( CounterReset ) ;
}

// �}�E�X�z�C�[���̉�]�ʂ𓾂�( �߂�l�� float �^ )
extern float NS_GetMouseWheelRotVolF( int CounterReset )
{
	return GetMouseWheelRotVolF_PF( CounterReset ) ;
}

// �����}�E�X�z�C�[���̉�]�ʂ𓾂�( �߂�l�� float �^ )
extern float NS_GetMouseHWheelRotVolF( int CounterReset )
{
	return GetMouseHWheelRotVolF_PF( CounterReset ) ;
}














// �^�b�`�p�l���֌W�̊֐�

// �����ꂽ�^�b�`����ǉ�����
static void AddTouchDownInputPointLog( TOUCHINPUTPOINT *TouchPointData )
{
	int AddIndex ;

	// ���̐����ő吔�𒴂��Ă�����擪�f�[�^�̃C���f�b�N�X�����炷
	if( InputSysData.Touch.DownLogNum == INPUTTOUCH_LOG_NUM )
	{
		AddIndex = InputSysData.Touch.DownLogStartIndex ;

		InputSysData.Touch.DownLogStartIndex ++ ;
		if( InputSysData.Touch.DownLogStartIndex == INPUTTOUCH_LOG_NUM )
		{
			InputSysData.Touch.DownLogStartIndex = 0 ;
		}
	}
	else
	{
		AddIndex = InputSysData.Touch.DownLogStartIndex + InputSysData.Touch.DownLogNum ;
		if( AddIndex >= INPUTTOUCH_LOG_NUM )
		{
			AddIndex -= INPUTTOUCH_LOG_NUM ;
		}

		InputSysData.Touch.DownLogNum ++ ;
	}

	// �����ꂽ�^�b�`�����Z�b�g
	InputSysData.Touch.DownLog[ AddIndex ] = *TouchPointData ;
}

// �����ꂽ�^�b�`����ǉ�����
static void AddTouchUpInputPointLog( TOUCHINPUTPOINT *TouchPointData )
{
	int AddIndex ;

	// ���̐����ő吔�𒴂��Ă�����擪�f�[�^�̃C���f�b�N�X�����炷
	if( InputSysData.Touch.UpLogNum == INPUTTOUCH_LOG_NUM )
	{
		AddIndex = InputSysData.Touch.UpLogStartIndex ;

		InputSysData.Touch.UpLogStartIndex ++ ;
		if( InputSysData.Touch.UpLogStartIndex == INPUTTOUCH_LOG_NUM )
		{
			InputSysData.Touch.UpLogStartIndex = 0 ;
		}
	}
	else
	{
		AddIndex = InputSysData.Touch.UpLogStartIndex + InputSysData.Touch.UpLogNum ;
		if( AddIndex >= INPUTTOUCH_LOG_NUM )
		{
			AddIndex -= INPUTTOUCH_LOG_NUM ;
		}

		InputSysData.Touch.UpLogNum ++ ;
	}

	// �����ꂽ�^�b�`�����Z�b�g
	InputSysData.Touch.UpLog[ AddIndex ] = *TouchPointData ;
}

// �^�b�`�p�l���̓��͏������O�ɒǉ�����
static void AddTouchInputLog( TOUCHINPUTDATA *TouchData )
{
	int AddIndex ;

	// �^�b�`���̐����ő吔�𒴂��Ă�����擪�f�[�^�̃C���f�b�N�X�����炷
	if( InputSysData.Touch.LogNum == INPUTTOUCH_LOG_NUM )
	{
		AddIndex = InputSysData.Touch.LogStartIndex ;

		InputSysData.Touch.LogStartIndex ++ ;
		if( InputSysData.Touch.LogStartIndex == INPUTTOUCH_LOG_NUM )
		{
			InputSysData.Touch.LogStartIndex = 0 ;
		}
	}
	else
	{
		AddIndex = InputSysData.Touch.LogStartIndex + InputSysData.Touch.LogNum ;
		if( AddIndex >= INPUTTOUCH_LOG_NUM )
		{
			AddIndex -= INPUTTOUCH_LOG_NUM ;
		}

		InputSysData.Touch.LogNum ++ ;
	}

	// �f�[�^���Z�b�g
	InputSysData.Touch.Log[ AddIndex ] = *TouchData ;
}

// �^�b�`�p�l���̓��͏���ǉ�����
extern	int AddTouchInputData( TOUCHINPUTDATA *TouchData )
{
	int i ;
	int j ;

	// �ŏ��̃^�b�`��񂾂�����u�����ꂽ�v���O�ɒǉ�����
	if( InputSysData.Touch.LogNum == 0 )
	{
		for( i = 0 ; i < TouchData->PointNum ; i ++ )
		{
			AddTouchDownInputPointLog( &TouchData->Point[ i ] ) ;
		}
	}
	else
	{
		// ��O�̃��O�ł͑��݂��Ȃ������^�b�`���������烍�O�ɒǉ�����
		for( i = 0 ; i < TouchData->PointNum ; i ++ )
		{
			for( j = 0 ; j < InputSysData.Touch.NowData.PointNum ; j ++ )
			{
				if( TouchData->Point[ i ].ID == InputSysData.Touch.NowData.Point[ j ].ID )
				{
					break ;
				}
			}
			if( j != InputSysData.Touch.NowData.PointNum )
			{
				continue ;
			}

			AddTouchDownInputPointLog( &TouchData->Point[ i ] ) ;
		}
	}

	// ��O�̃��O���Ɣ�r���āA�����ꂽ�^�b�`���������烍�O�ɒǉ�����
	if( InputSysData.Touch.LogNum >= 1 )
	{
		for( i = 0 ; i < InputSysData.Touch.NowData.PointNum ; i ++ )
		{
			for( j = 0 ; j < TouchData->PointNum ; j ++ )
			{
				if( InputSysData.Touch.NowData.Point[ i ].ID == TouchData->Point[ j ].ID )
				{
					break ;
				}
			}
			if( j != TouchData->PointNum )
			{
				continue ;
			}

			AddTouchUpInputPointLog( &InputSysData.Touch.NowData.Point[ i ] ) ;
		}
	}

	// ���O�ɒǉ�����
	AddTouchInputLog( TouchData ) ;

	// �ŐV�̃^�b�`���ɂ��Z�b�g
	InputSysData.Touch.NowData = *TouchData ;

	// �}�E�X���͂Ƃ���^�b�`���̂h�c���X�V
	{
		// ����^�b�`��񂪂Ȃ���� -1 ����
		if( TouchData->PointNum == 0 )
		{
			InputSysData.Touch.MouseInputDevice = -1 ;
			InputSysData.Touch.MouseInputID = -1 ;
			InputSysData.Touch.MouseInputIndex = -1 ;
		}
		else
		{
			// ���܂łƓ����h�c������������X�V
			for( i = 0 ; i < TouchData->PointNum ; i ++ )
			{
				if( InputSysData.Touch.MouseInputDevice == ( int )TouchData->Point[ i ].Device &&
					InputSysData.Touch.MouseInputID     == ( int )TouchData->Point[ i ].ID )
				{
					InputSysData.Touch.MouseInputIndex = i ;
					break ;
				}
			}
			if( i == TouchData->PointNum )
			{
				InputSysData.Touch.MouseInputDevice = TouchData->Point[ 0 ].Device ;
				InputSysData.Touch.MouseInputID     = TouchData->Point[ 0 ].ID ;
				InputSysData.Touch.MouseInputIndex  = 0 ;
			}
		}
	}

	// ����I��
	return 0 ;
}

// �^�b�`�p�l�����͊֌W�֐�

// �^�b�`����Ă��鐔���擾����
extern int NS_GetTouchInputNum( void )
{
	return InputSysData.Touch.NowData.PointNum ;
}

// �^�b�`�̏����擾����
extern int NS_GetTouchInput( int InputNo, int *PositionX, int *PositionY, int *ID , int *Device, float *Pressure )
{
	if( InputNo >= InputSysData.Touch.NowData.PointNum )
	{
		return -1 ;
	}

	if( PositionX != NULL )
	{
		*PositionX = InputSysData.Touch.NowData.Point[ InputNo ].PositionX ;
	}

	if( PositionY != NULL )
	{
		*PositionY = InputSysData.Touch.NowData.Point[ InputNo ].PositionY ;
	}

	if( ID != NULL )
	{
		*ID = InputSysData.Touch.NowData.Point[ InputNo ].ID ;
	}

	if( Device != NULL )
	{
		*Device = InputSysData.Touch.NowData.Point[ InputNo ].Device ;
	}

	if( Pressure != NULL )
	{
		*Pressure = InputSysData.Touch.NowData.Point[ InputNo ].Pressure ;
	}

	return 0 ;
}

// �X�g�b�N����Ă���^�b�`���̐����擾����
extern int NS_GetTouchInputLogNum( void )
{
	return InputSysData.Touch.LogNum ;
}

// �X�g�b�N����Ă���^�b�`�����N���A����
extern int NS_ClearTouchInputLog( void )
{
	InputSysData.Touch.LogNum = 0 ;
	InputSysData.Touch.LogStartIndex = 0 ;

	return 0 ;
}

// �X�g�b�N����Ă���^�b�`��񂩂��ԌÂ������ЂƂ擾����
extern TOUCHINPUTDATA NS_GetTouchInputLogOne( int PeekFlag )
{
	TOUCHINPUTDATA Return ;

	if( InputSysData.Touch.LogNum == 0 )
	{
		_MEMSET( &Return, 0, sizeof( Return ) ) ;
	}
	else
	{
		Return = InputSysData.Touch.Log[ InputSysData.Touch.LogStartIndex ] ;

		if( PeekFlag == FALSE )
		{
			InputSysData.Touch.LogStartIndex ++ ;
			if( InputSysData.Touch.LogStartIndex == INPUTTOUCH_LOG_NUM )
			{
				InputSysData.Touch.LogStartIndex = 0 ;
			}

			InputSysData.Touch.LogNum -- ;
		}
	}

	return Return ;
}

// �X�g�b�N����Ă���^�b�`��񂩂�Â����Ɏw�萔�o�b�t�@�Ɏ擾����( �߂�l  -1:�G���[  0�ȏ�:�擾�������̐� )
extern int NS_GetTouchInputLog( TOUCHINPUTDATA *TouchData, int GetNum, int PeekFlag )
{
	int i ;
	int GetIndex ;

	if( InputSysData.Touch.LogNum == 0 )
	{
		return 0 ;
	}

	if( InputSysData.Touch.LogNum < GetNum )
	{
		GetNum = InputSysData.Touch.LogNum ;
	}

	GetIndex = InputSysData.Touch.LogStartIndex ;
	for( i = 0 ; i < GetNum ; i ++ )
	{
		TouchData[ i ] = InputSysData.Touch.Log[ GetIndex ] ;

		GetIndex ++ ;
		if( GetIndex == INPUTTOUCH_LOG_NUM )
		{
			GetIndex = 0 ;
		}
	}

	if( PeekFlag == FALSE )
	{
		InputSysData.Touch.LogNum -= GetNum ;
		InputSysData.Touch.LogStartIndex = GetIndex ;
	}

	return GetNum ;
}







// �X�g�b�N����Ă���^�b�`����n�߂����̐����擾����
extern int NS_GetTouchInputDownLogNum( void )
{
	return InputSysData.Touch.DownLogNum ;
}

// �X�g�b�N����Ă���^�b�`����n�߂������N���A����
extern int NS_ClearTouchInputDownLog( void )
{
	InputSysData.Touch.DownLogNum = 0 ;
	InputSysData.Touch.DownLogStartIndex = 0 ;

	return 0 ;
}

// �X�g�b�N����Ă���^�b�`����n�߂���񂩂��ԌÂ������ЂƂ擾����
extern TOUCHINPUTPOINT NS_GetTouchInputDownLogOne( int PeekFlag )
{
	TOUCHINPUTPOINT Return ;

	if( InputSysData.Touch.DownLogNum == 0 )
	{
		_MEMSET( &Return, 0, sizeof( Return ) ) ;
	}
	else
	{
		Return = InputSysData.Touch.DownLog[ InputSysData.Touch.DownLogStartIndex ] ;

		if( PeekFlag == FALSE )
		{
			InputSysData.Touch.DownLogStartIndex ++ ;
			if( InputSysData.Touch.DownLogStartIndex == INPUTTOUCH_LOG_NUM )
			{
				InputSysData.Touch.DownLogStartIndex = 0 ;
			}

			InputSysData.Touch.DownLogNum -- ;
		}
	}

	return Return ;
}

// �X�g�b�N����Ă���^�b�`����n�߂���񂩂�Â����Ɏw�萔�o�b�t�@�Ɏ擾����( �߂�l  -1:�G���[  0�ȏ�:�擾�������̐� )
extern int NS_GetTouchInputDownLog( TOUCHINPUTPOINT *TouchData, int GetNum, int PeekFlag )
{
	int i ;
	int GetIndex ;

	if( InputSysData.Touch.DownLogNum == 0 )
	{
		return 0 ;
	}

	if( InputSysData.Touch.DownLogNum < GetNum )
	{
		GetNum = InputSysData.Touch.DownLogNum ;
	}

	GetIndex = InputSysData.Touch.DownLogStartIndex ;
	for( i = 0 ; i < GetNum ; i ++ )
	{
		TouchData[ i ] = InputSysData.Touch.DownLog[ GetIndex ] ;

		GetIndex ++ ;
		if( GetIndex == INPUTTOUCH_LOG_NUM )
		{
			GetIndex = 0 ;
		}
	}

	if( PeekFlag == FALSE )
	{
		InputSysData.Touch.DownLogNum -= GetNum ;
		InputSysData.Touch.DownLogStartIndex = GetIndex ;
	}

	return GetNum ;
}











// �X�g�b�N����Ă���^�b�`�������ꂽ���̐����擾����
extern int NS_GetTouchInputUpLogNum( void )
{
	return InputSysData.Touch.UpLogNum ;
}

// �X�g�b�N����Ă���^�b�`�������ꂽ�����N���A����
extern int NS_ClearTouchInputUpLog( void )
{
	InputSysData.Touch.UpLogNum = 0 ;
	InputSysData.Touch.UpLogStartIndex = 0 ;

	return 0 ;
}

// �X�g�b�N����Ă���^�b�`�������ꂽ��񂩂��ԌÂ������ЂƂ擾����
extern TOUCHINPUTPOINT NS_GetTouchInputUpLogOne( int PeekFlag )
{
	TOUCHINPUTPOINT Return ;

	if( InputSysData.Touch.UpLogNum == 0 )
	{
		_MEMSET( &Return, 0, sizeof( Return ) ) ;
	}
	else
	{
		Return = InputSysData.Touch.UpLog[ InputSysData.Touch.UpLogStartIndex ] ;

		if( PeekFlag == FALSE )
		{
			InputSysData.Touch.UpLogStartIndex ++ ;
			if( InputSysData.Touch.UpLogStartIndex == INPUTTOUCH_LOG_NUM )
			{
				InputSysData.Touch.UpLogStartIndex = 0 ;
			}

			InputSysData.Touch.UpLogNum -- ;
		}
	}

	return Return ;
}

// �X�g�b�N����Ă���^�b�`�������ꂽ��񂩂�Â����Ɏw�萔�o�b�t�@�Ɏ擾����( �߂�l  -1:�G���[  0�ȏ�:�擾�������̐� )
extern int NS_GetTouchInputUpLog( TOUCHINPUTPOINT *TouchData, int GetNum, int PeekFlag )
{
	int i ;
	int GetIndex ;

	if( InputSysData.Touch.UpLogNum == 0 )
	{
		return 0 ;
	}

	if( InputSysData.Touch.UpLogNum < GetNum )
	{
		GetNum = InputSysData.Touch.UpLogNum ;
	}

	GetIndex = InputSysData.Touch.UpLogStartIndex ;
	for( i = 0 ; i < GetNum ; i ++ )
	{
		TouchData[ i ] = InputSysData.Touch.UpLog[ GetIndex ] ;

		GetIndex ++ ;
		if( GetIndex == INPUTTOUCH_LOG_NUM )
		{
			GetIndex = 0 ;
		}
	}

	if( PeekFlag == FALSE )
	{
		InputSysData.Touch.UpLogNum -= GetNum ;
		InputSysData.Touch.UpLogStartIndex = GetIndex ;
	}

	return GetNum ;
}

















// ���͏�Ԏ擾�֐�

// �L�[�{�[�h�̏�Ԏ擾
extern int NS_CheckHitKey( int KeyCode )
{
	int Result ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	// �L�[�{�[�h�̓��͏�Ԃ��X�V
	UpdateKeyboardInputState() ;

	// �w��̃L�[�̏�Ԃ�Ԃ�
	Result = ( InputSysData.KeyInputBuf[ KeyCode ] & 0x80 ) != 0 ;
	
	return Result ;
}

// �S�L�[�̉�����Ԃ��擾
extern int NS_CheckHitKeyAll( int CheckType )
{
	int i ;
	unsigned char *KeyData ;

#ifdef WINDOWS_DESKTOP_OS
	if( WinData.MainWindow == NULL )
		return -1 ;
#endif // WINDOWS_DESKTOP_OS

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	// �L�[�{�[�h�̃`�F�b�N
	if( CheckType & DX_CHECKINPUT_KEY )
	{
		// �L�[�{�[�h�̓��͏�Ԃ��X�V
		UpdateKeyboardInputState() ;

		// �ǂꂩ��ł��L�[��������Ă��邩����
		KeyData = InputSysData.KeyInputBuf ;
		for( i = 0 ; i < 256 ; i ++ , KeyData ++ )
		{
			if( ( *KeyData & 0x80 ) && i != KEY_INPUT_KANJI && i != KEY_INPUT_CAPSLOCK && i != KEY_INPUT_KANA )
				return i ;
		}
		if( InputSysData.F10Flag )
		{
			return KEY_INPUT_F10 ;
		}
	}

	// �W���C�p�b�h�̃`�F�b�N
	if( CheckType & DX_CHECKINPUT_PAD )
	{
		for( i = 0 ; i < InputSysData.PadNum ; i ++ )
		{
			if( NS_GetJoypadInputState( i + 1 ) != 0 )
				return -1 ;
		}
	}

	// �}�E�X�{�^���̃`�F�b�N
	if( CheckType & DX_CHECKINPUT_MOUSE )
	{
#ifdef WINDOWS_DESKTOP_OS
		int x, y ;
		RECT Rect ;

		NS_GetMousePoint( &x, &y ) ;

		NS_GetWindowCRect( &Rect ) ;
		if( x >= 0                      && y >= 0                      && NS_GetWindowActiveFlag() &&
			x <= Rect.right - Rect.left && y <= Rect.bottom - Rect.top && NS_GetMouseInput() != 0 )
			return -1 ;
#else // WINDOWS_DESKTOP_OS
		if( NS_GetMouseInput() != 0 )
		{
			return -1 ;
		}
#endif // WINDOWS_DESKTOP_OS
	}

	// �I��
	return 0 ;
}

// ���ׂẴL�[�̉�����Ԃ��擾����
extern int NS_GetHitKeyStateAll( char *KeyStateBuf )
{
	int i ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	// �L�[�{�[�h�̓��͏�Ԃ��X�V
	UpdateKeyboardInputState() ;

	// �L�[�̓��͒l��ϊ�
	for( i = 0 ; i < 256 ; i ++ , KeyStateBuf ++ )
	{
		*KeyStateBuf = ( BYTE )( InputSysData.KeyInputBuf[i] ) >> 7 ;
	}

	// �I��
	return 0 ;
}

// ���ׂẴL�[�̉�����Ԃ��擾����(
// KeyStateBuf:int�^256���̔z��̐擪�A�h���X
// �z��̊e�v�f�̏��
//   0:������Ă��Ȃ�
//
//    1    �F�����ꂽ�P���
//    2�ȏ�F�����ꑱ���Ă����
//
//   -1    �F������ė����ꂽ�P���
//   -2�ȉ��F������ė�����Ă���̉� )
extern int NS_GetHitKeyStateAllEx( int *KeyStateArray )
{
	int i ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	// �L�[�{�[�h�̓��͏�Ԃ��X�V
	UpdateKeyboardInputState() ;

	// �L�[�̓��͒l��ϊ�
	for( i = 0 ; i < 256 ; i ++ )
	{
		if( ( ( BYTE )( InputSysData.KeyInputBuf[ i ] ) >> 7 ) != 0 )
		{
			if( KeyStateArray[ i ] <= 0 )
			{
				KeyStateArray[ i ] = 1 ;
			}
			else
			if( KeyStateArray[ i ] < 2147483647 )
			{
				KeyStateArray[ i ]++ ;
			}
		}
		else
		{
			if( KeyStateArray[ i ] > 0 )
			{
				KeyStateArray[ i ] = -1 ;
			}
			else
			if( KeyStateArray[ i ] < 0 && KeyStateArray[ i ] > -2147483647 )
			{
				KeyStateArray[ i ]-- ;
			}
		}
	}

	// �I��
	return 0 ;
}





// �W���C�p�b�h���ڑ�����Ă��鐔���擾����
extern int NS_GetJoypadNum( void )
{
	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	return InputSysData.PadNum ;
}

// �W���C�p�b�h�̃{�^���̐����擾����
extern int NS_GetJoypadButtonNum( int InputType )
{
	INPUTPADDATA *pad ;
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		return -1 ;
	}

	pad = &InputSysData.Pad[ JoypadNum ] ;

	// �{�^���̐���Ԃ�
	return pad->Buttons ;
}

// �W���C�o�b�h�̓��͏�Ԏ擾
extern int NS_GetJoypadInputState( int InputType )
{
	int BackData = 0 ;
	INPUTPADDATA *pad ;
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;
	int iX , iY ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	if( ( JoypadNum < -1 || JoypadNum >= InputSysData.PadNum ) && 
		( InputSysData.PadNum != 0 && ( InputType & DX_INPUT_KEY ) == 0 ) )
	{
		return 0 ;
	}

	if( JoypadNum != -1 && InputSysData.PadNum != 0 && JoypadNum < InputSysData.PadNum )
	{
		pad = &InputSysData.Pad[ JoypadNum ] ;

		// �p�b�h�̏����擾����
		{
			// ���̍X�V
			UpdateJoypadInputState( JoypadNum ) ;
			if( ( JoypadNum < -1 || JoypadNum >= InputSysData.PadNum ) && 
				( InputSysData.PadNum != 0 && ( InputType & DX_INPUT_KEY ) == 0 ) )
			{
				return 0 ;
			}

			// ���͏�Ԃ�ۑ�
			iX = pad->State.X ;
			iY = pad->State.Y ;

			// �J�[�\���{�^������
			     if( iX < 0 ) BackData |= PAD_INPUT_LEFT ;			// �����͔���
			else if( iX > 0 ) BackData |= PAD_INPUT_RIGHT ;			// �����͔���

			     if( iY < 0 ) BackData |= PAD_INPUT_UP ;			// �����͔���
			else if( iY > 0 ) BackData |= PAD_INPUT_DOWN ;			// �����͔���

			// �n�b�g�X�C�b�`�̏�Ԃ������{�^���ɔ��f����
			switch( pad->State.POV[ 0 ] )
			{
			case 0 :		BackData |= PAD_INPUT_UP						;	break ;
			case 4500 :		BackData |= PAD_INPUT_UP    | PAD_INPUT_RIGHT	;	break ;
			case 9000 :		BackData |= PAD_INPUT_RIGHT						;	break ;
			case 13500 :	BackData |= PAD_INPUT_RIGHT | PAD_INPUT_DOWN	;	break ;
			case 18000 :	BackData |= PAD_INPUT_DOWN						;	break ;
			case 22500 :	BackData |= PAD_INPUT_DOWN  | PAD_INPUT_LEFT	;	break ;
			case 27000 :	BackData |= PAD_INPUT_LEFT						;	break ;
			case 31500 :	BackData |= PAD_INPUT_LEFT  | PAD_INPUT_UP		;	break ;
			}

			// �{�^�����͔���
			{
				int i ;

				// ���͏�Ԃ�ۑ�
				for( i = 0 ; i < 24 ; i ++ )
				{
					BackData |= ( pad->State.Buttons[ i ] & 0x80 ) != 0 ? 1 << ( i + 4 ) : 0 ;
				}
			}
		}
	}

	// �L�[���͎w����������ꍇ�̓L�[�̓��͏�Ԃ����f������
	if( InputType & DX_INPUT_KEY )
	{
		BYTE *KeyBuf ;
		int *Map ;
		int i, j ;
		unsigned int pad_bit ;

		// �L�[�{�[�h�̓��͏�Ԃ��X�V
		UpdateKeyboardInputState() ;

		KeyBuf = InputSysData.KeyInputBuf ;
		Map = InputSysData.KeyToJoypadInput[ JoypadNum < 0 ? 0 : JoypadNum ][ 0 ] ;

		pad_bit = 1 ;
		for( i = 0 ; i < 32 ; i ++, pad_bit <<= 1, Map += 4 )
		{
			for( j = 0 ; j < 4 ; j ++ )
			{
				if( Map[ j ] > 0 && ( KeyBuf[ Map[ j ] ] & 0x80 ) )
				{
					BackData |= ( int )pad_bit ;
					break ; 
				}
			}
		}
	}

	// �I��
	return BackData ;
}

// �W���C�p�b�h�̃A�i���O�I�ȃX�e�B�b�N���͏��𓾂�
extern int NS_GetJoypadAnalogInput( int *XBuf , int *YBuf , int InputType )
{
	int BackData = 0 ;
	INPUTPADDATA *pad ;
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;
	
	if( XBuf != NULL ) *XBuf = 0 ;
	if( YBuf != NULL ) *YBuf = 0 ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	if( ( JoypadNum < -1 || JoypadNum >= InputSysData.PadNum ) && 
		( InputSysData.PadNum != 0 && ( InputType & DX_INPUT_KEY ) == 0 ) )
	{
		return 0 ;
	}

	if( JoypadNum != -1 && InputSysData.PadNum != 0 )
	{
		pad = &InputSysData.Pad[ JoypadNum ] ;

		// ���͏�Ԃ̍X�V
		UpdateJoypadInputState( JoypadNum ) ;
		if( ( JoypadNum < -1 || JoypadNum >= InputSysData.PadNum ) && 
			( InputSysData.PadNum != 0 && ( InputType & DX_INPUT_KEY ) == 0 ) )
		{
			return 0 ;
		}

		// ���͏�Ԃ�ۑ�
		if( XBuf ) *XBuf = pad->State.X ;
		if( YBuf ) *YBuf = pad->State.Y ;
	}

	// �L�[���͎w����������ꍇ�̓L�[�̓��͏�Ԃ����f������
	if( InputType & DX_INPUT_KEY )
	{
		BYTE *KeyBuf ;

		// �L�[�{�[�h�̓��͏�Ԃ��X�V
		UpdateKeyboardInputState() ;

		KeyBuf = InputSysData.KeyInputBuf ;
		if( XBuf )
		{
			if( KeyBuf[ KEY_INPUT_NUMPAD4 ] & 0x80 || KeyBuf[ KEY_INPUT_LEFT  ] & 0x80 ) *XBuf = -DIRINPUT_MAX ;		// �S�L�[���`�F�b�N
			if( KeyBuf[ KEY_INPUT_NUMPAD6 ] & 0x80 || KeyBuf[ KEY_INPUT_RIGHT ] & 0x80 ) *XBuf =  DIRINPUT_MAX	;		// �U�L�[���L�[�`�F�b�N
		}
		if( YBuf )
		{
			if( KeyBuf[ KEY_INPUT_NUMPAD2 ] & 0x80 || KeyBuf[ KEY_INPUT_DOWN  ] & 0x80 ) *YBuf =  DIRINPUT_MAX	;		// �Q�L�[���L�[�`�F�b�N
			if( KeyBuf[ KEY_INPUT_NUMPAD8 ] & 0x80 || KeyBuf[ KEY_INPUT_UP    ] & 0x80 ) *YBuf = -DIRINPUT_MAX ;		// �W�L�[���L�[�`�F�b�N
		}
	}

	// �I��
	return BackData ;
}

// �W���C�p�b�h�̃A�i���O�I�ȃX�e�B�b�N���͏��𓾂�(�E�X�e�B�b�N�p)
extern int NS_GetJoypadAnalogInputRight( int *XBuf, int *YBuf, int InputType )
{
	int BackData = 0 ;
	INPUTPADDATA *pad ;
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;
	
	if( XBuf != NULL ) *XBuf = 0 ;
	if( YBuf != NULL ) *YBuf = 0 ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	if( JoypadNum < -1 || JoypadNum >= InputSysData.PadNum )
		return 0 ;

	if( JoypadNum != -1 )
	{
		pad = &InputSysData.Pad[ JoypadNum ] ;

		// ���͏�Ԃ̍X�V
		UpdateJoypadInputState( JoypadNum ) ;
		if( JoypadNum < -1 || JoypadNum >= InputSysData.PadNum )
			return 0 ;

		// ���͏�Ԃ�ۑ�( XInput ���ǂ����ŏ����𕪊� )
		if( NS_CheckJoypadXInput( InputType ) )
		{
			if( XBuf ) *XBuf = pad->State.Rx ;
			if( YBuf ) *YBuf = pad->State.Ry ;
		}
		else
		{
			if( XBuf ) *XBuf = pad->State.Z ;
			if( YBuf ) *YBuf = pad->State.Rz ;
		}
	}

	// �I��
	return BackData ;
}

// �W���C�p�b�h���� DirectInput ���瓾���鐶�̃f�[�^���擾����( DX_CHECKINPUT_KEY �� DX_INPUT_KEY_PAD1 �������ɓn���ƃG���[ )
extern	int	NS_GetJoypadDirectInputState( int InputType, DINPUT_JOYSTATE *DInputState )
{
	INPUTPADDATA *pad ;
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		_MEMSET( DInputState, 0, sizeof( DINPUT_JOYSTATE ) ) ;
		DInputState->POV[ 0 ] = 0xffffffff ;
		DInputState->POV[ 1 ] = 0xffffffff ;
		DInputState->POV[ 2 ] = 0xffffffff ;
		DInputState->POV[ 3 ] = 0xffffffff ;
		return -1 ;
	}

	pad = &InputSysData.Pad[ JoypadNum ] ;

	// ���͏�Ԃ̍X�V
	UpdateJoypadInputState( JoypadNum ) ;
	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		_MEMSET( DInputState, 0, sizeof( DINPUT_JOYSTATE ) ) ;
		DInputState->POV[ 0 ] = 0xffffffff ;
		DInputState->POV[ 1 ] = 0xffffffff ;
		DInputState->POV[ 2 ] = 0xffffffff ;
		DInputState->POV[ 3 ] = 0xffffffff ;
		return -1 ;
	}

	// ���͏�Ԃ�������
	if( DInputState )
	{
		*DInputState = pad->State ;
	}

	// ����I��
	return 0 ;
}

// �w��̓��̓f�o�C�X�� XInput �ɑΉ����Ă��邩�ǂ������擾����
// ( �߂�l  TRUE:XInput�Ή��̓��̓f�o�C�X  FALSE:XInput��Ή��̓��̓f�o�C�X   -1:�G���[ )
// ( DX_INPUT_KEY �� DX_INPUT_KEY_PAD1 �ȂǁA�L�[�{�[�h�����ރ^�C�v�� InputType �ɓn���ƃG���[�ƂȂ� -1 ��Ԃ� )
extern int NS_CheckJoypadXInput( int InputType )
{
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		return -1 ;
	}

	// ���ˑ������ɔC����
	return CheckJoypadXInput_PF( InputType ) ;
}

// �W���C�p�b�h�̃^�C�v���擾����( �߂�l  -1:�G���[  0�ȏ�:�W���C�p�b�h�^�C�v( DX_PADTYPE_XBOX_360 �Ȃ� ) )
extern int NS_GetJoypadType( int InputType )
{
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		return -1 ;
	}

	// ���ˑ������ɔC����
	return GetJoypadType_PF( InputType ) ;
}

// XInput ���瓾������̓f�o�C�X( Xbox360�R���g���[���� )�̐��̃f�[�^���擾����( XInput��Ή��̃p�b�h�̏ꍇ�̓G���[�ƂȂ� -1 ��Ԃ��ADX_INPUT_KEY �� DX_INPUT_KEY_PAD1 �ȂǁA�L�[�{�[�h�����ރ^�C�v�� InputType �ɓn���ƃG���[�ƂȂ� -1 ��Ԃ� )
extern int NS_GetJoypadXInputState(	int InputType, XINPUT_STATE *XInputState )
{
	INPUTPADDATA *pad ;
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		_MEMSET( XInputState, 0, sizeof( XINPUT_STATE ) ) ;
		return -1 ;
	}

	pad = &InputSysData.Pad[ JoypadNum ] ;

	// XInput �ɑΉ����Ă��Ȃ�������G���[
	if( NS_CheckJoypadXInput( InputType ) == FALSE )
	{
		_MEMSET( XInputState, 0, sizeof( XINPUT_STATE ) ) ;
		return -1 ;
	}

	// ���͏�Ԃ̍X�V
	UpdateJoypadInputState( JoypadNum ) ;
	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		_MEMSET( XInputState, 0, sizeof( XINPUT_STATE ) ) ;
		return -1 ;
	}

	// ���͏�Ԃ�������
	if( XInputState )
	{
		*XInputState = pad->XInputState ;
	}

	// ����I��
	return 0 ;
}

// �W���C�p�b�h�̓��͂ɑΉ������L�[�{�[�h�̓��͂�ݒ肷��
extern	int NS_SetJoypadInputToKeyInput( int InputType, int PadInput, int KeyInput1, int KeyInput2 , int KeyInput3 , int KeyInput4 )
{
	unsigned int Bit , i ;

	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;

	if( JoypadNum < 0 || JoypadNum >= MAX_JOYPAD_NUM )
		return 0 ;

	Bit = (unsigned int)PadInput ;
	for( i = 0 ; i < 32 ; i ++ )
	{
		if( Bit & ( 1 << i ) )
		{
			InputSysData.KeyToJoypadInput[ JoypadNum ][ i ][ 0 ] = KeyInput1 ;
			InputSysData.KeyToJoypadInput[ JoypadNum ][ i ][ 1 ] = KeyInput2 ;
			InputSysData.KeyToJoypadInput[ JoypadNum ][ i ][ 2 ] = KeyInput3 ;
			InputSysData.KeyToJoypadInput[ JoypadNum ][ i ][ 3 ] = KeyInput4 ;
		}
	}

	// ����I��
	return 0 ;
}

// �W���C�p�b�h�̖����]�[���̐ݒ���s��
extern	int NS_SetJoypadDeadZone( int InputType, double Zone )
{
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;
	INPUTPADDATA *pad = &InputSysData.Pad[ JoypadNum ] ;
	DWORD ZoneI ;

	// �l�̕␳
	if( Zone < 0.0 )
	{
		Zone = 0.0f ;
	}
	else
	if( Zone > 1.0 )
	{
		Zone = 1.0 ;
	}

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;
	
	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	// �G���[�`�F�b�N
	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		return 0 ;
	}

	// ���܂łƓ����]�[���̏ꍇ�͉��������I��
	ZoneI = ( DWORD )_DTOL( Zone * 65536 ) ;
	if( pad->DeadZone == ZoneI )
	{
		pad->DeadZoneD = Zone ;
		return 0 ;
	}

	// �]�[����ۑ�
	pad->DeadZone = ZoneI ;
	pad->DeadZoneD = Zone ;

	// ���[�U�[���ύX�������Ƃ��L�^
	pad->UserChangeDeadZone = TRUE ;

	// ���ˑ�����
	SetJoypadDeadZone_PF( pad ) ;

	// ����I��
	return 0 ;
}

// �W���C�p�b�h�̖����]�[���̐ݒ���擾����( InputType:�ݒ��ύX����p�b�h�̎��ʎq( DX_INPUT_PAD1�� )   �߂�l:�����]�[��( 0.0 �` 1.0 )
extern	double NS_GetJoypadDeadZone( int InputType )
{
	INPUTPADDATA *pad ;
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		AutoInitialize_PF() ;
	}

	// �G���[�`�F�b�N
	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		return -1.0 ;
	}

	pad = &InputSysData.Pad[ JoypadNum ] ;

	// �l��Ԃ�
	return pad->DeadZoneD ;
}

// �W���C�p�b�h�̃f�t�H���g�̖����]�[����ݒ肷��( Zone:�V���������]�[��( 0.0 �` 1.0 )�A�f�t�H���g�l�� 0.35 )
extern	int SetJoypadDefaultDeadZoneAll( double Zone )
{
	DWORD ZoneI ;
	INPUTPADDATA *pad ;
	int i ;

	// �l�̕␳
	if( Zone < 0.0 )
	{
		Zone = 0.0f ;
	}
	else
	if( Zone > 1.0 )
	{
		Zone = 1.0 ;
	}

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ���܂łƓ����]�[���̏ꍇ�͉��������I��
	ZoneI = ( DWORD )_DTOL( Zone * 65536 ) ;
	if( InputSysData.EnablePadDefaultDeadZone == TRUE && InputSysData.PadDefaultDeadZone == ZoneI )
	{
		return 0 ;
	}

	// �]�[����ۑ�
	InputSysData.PadDefaultDeadZone = ZoneI ;
	InputSysData.PadDefaultDeadZoneD = Zone ;

	// PadDefaultDeadZone �� PadDefaultDeadZoneD ���L�����ǂ����̃t���O�𗧂Ă�
	InputSysData.EnablePadDefaultDeadZone = TRUE ;

	// ���[�U�[���f�b�h�]�[����ύX���Ă��Ȃ��W���C�p�b�h�ɓK�p
	pad = InputSysData.Pad ;
	for( i = 0 ; i < InputSysData.PadNum ; i ++ , pad ++ )
	{
		if( pad->UserChangeDeadZone )
		{
			continue ;
		}

		// �l��ۑ�
		pad->DeadZone = ZoneI ;
		pad->DeadZoneD = Zone ;

		// ���ˑ�����
		SetJoypadDeadZone_PF( pad ) ;
	}

	// �I��
	return 0 ;
}

// �W���C�p�b�h�̃f�t�H���g�̖����]�[�����擾����( �߂�l:�����]�[��( 0.0 �` 1.0 ) )
extern	double GetJoypadDefaultDeadZoneAll( void )
{
	return InputSysData.PadDefaultDeadZoneD ;
}

// �W���C�p�b�h�̐U�����J�n����
extern	int NS_StartJoypadVibration( int InputType, int Power, int Time, int EffectIndex )
{
	int               SetPower ;
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;
	INPUTPADDATA *pad = &InputSysData.Pad[ JoypadNum ] ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	// �G���[�`�F�b�N
	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		return 0 ;
	}

	// EffectIndex ���}�C�i�X�̏ꍇ�͏����𕪊�
	if( EffectIndex < 0 )
	{
		if( Power < 0 )
		{
			NS_StartJoypadVibration( InputType, pad->Effect[ DINPUTPAD_MOTOR_LEFT ].Power, Time, DINPUTPAD_MOTOR_LEFT ) ;
		}
		else
		{
			SetPower = Power * 2 ;
			if( SetPower > DX_FFNOMINALMAX / 10 )
			{
				SetPower = DX_FFNOMINALMAX / 10 ;
			}
			NS_StartJoypadVibration( InputType, SetPower, Time, DINPUTPAD_MOTOR_LEFT ) ;
		}

		if( Power < 0 )
		{
			NS_StartJoypadVibration( InputType, pad->Effect[ DINPUTPAD_MOTOR_RIGHT ].Power, Time, DINPUTPAD_MOTOR_RIGHT ) ;
		}
		else
		{
			SetPower = ( Power - ( DX_FFNOMINALMAX / 10 / 2 ) ) * 2 ;
			if( SetPower <= 0 )
			{
				SetPower = 0 ;
			}
			else
			if( SetPower > DX_FFNOMINALMAX / 10 )
			{
				SetPower = DX_FFNOMINALMAX / 10 ;
			}
			NS_StartJoypadVibration( InputType, SetPower, Time, DINPUTPAD_MOTOR_RIGHT ) ;
		}

		// �I��
		return 0 ;
	}

	if( EffectIndex >= DINPUTPAD_MOTOR_NUM )
	{
		return 0 ;
	}

	// �U���ɑΉ����Ă��Ȃ���΂����ŏI��
	if( CheckJoypadVibrationEnable_PF( pad, EffectIndex ) == FALSE )
	{
		return 0 ;
	}

	// ���̑傫���� DirectInput �̌^�ɍ��킹��
	if( Power < 0 )
	{
		Power = pad->Effect[ EffectIndex ].Power ;
	}
	else
	{
		Power *= 10 ;
		if( Power >  DX_FFNOMINALMAX )
		{
			Power =  DX_FFNOMINALMAX ;
		}
	}

	// �h��̑傫�����O�̏ꍇ�͐U�����X�g�b�v����
	if( Power == 0 )
	{
		NS_StopJoypadVibration( InputType, EffectIndex ) ;
	}
	else
	{
		// �Đ��J�n�����Ȃǂ��Z�b�g
		pad->Effect[ EffectIndex ].BackTime	= NS_GetNowCount( FALSE ) ;
		pad->Effect[ EffectIndex ].Time		= Time ;
		pad->Effect[ EffectIndex ].CompTime	= 0 ;
		pad->Effect[ EffectIndex ].PrevSetTime = -1 ;

		// ���ɍĐ����ł��̑傫���������ꍇ�͉������Ȃ�
		if( pad->Effect[ EffectIndex ].PlayFlag == TRUE && pad->Effect[ EffectIndex ].Power == Power )
		{
			return 0 ;
		}

		// �Đ��ݒ��ۑ�
		pad->Effect[ EffectIndex ].PlayFlag	= TRUE ;
		pad->Effect[ EffectIndex ].Power	= Power ;

		// �Đ���Ԃ̐ݒ�𔽉f
		RefreshEffectPlayState() ;
	}

	// �I��
	return 0 ;
}

// �W���C�p�b�h�̐U�����~����
extern	int NS_StopJoypadVibration( int InputType, int EffectIndex )
{
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;
	INPUTPADDATA *pad = &InputSysData.Pad[ JoypadNum ] ;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;
	
	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		return AutoInitialize_PF() ;
	}

	// �G���[�`�F�b�N
	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum )
	{
		return 0 ;
	}

	// EffectIndex ���}�C�i�X�̏ꍇ�͏����𕪊�
	if( EffectIndex < 0 )
	{
		// ���E���[�^�[�̐U�����~�߂�
		NS_StopJoypadVibration( InputType, DINPUTPAD_MOTOR_LEFT ) ;
		NS_StopJoypadVibration( InputType, DINPUTPAD_MOTOR_RIGHT ) ;

		// �I��
		return 0 ;
	}

	if( EffectIndex >= DINPUTPAD_MOTOR_NUM )
	{
		return 0 ;
	}

	// �U���ɑΉ����Ă��Ȃ���΂����ŏI��
	if( CheckJoypadVibrationEnable_PF( pad, EffectIndex ) == FALSE )
	{
		return 0 ;
	}

	// ���ɍĐ�����~���Ă����牽�����Ȃ�
	if( pad->Effect[ EffectIndex ].PlayFlag == FALSE )
	{
		return 0 ;
	}

	// �Đ��t���O��|��
	pad->Effect[ EffectIndex ].PlayFlag = FALSE ;

	// �U���̋�����������
	pad->Effect[ EffectIndex ].Power = DX_FFNOMINALMAX ;

	// �Đ���Ԃ̐ݒ�𔽉f
	RefreshEffectPlayState() ;

	// �I��
	return 0 ;
}

// �W���C�p�b�h�̂o�n�u���͂̏�Ԃ𓾂�( �P�ʂ͊p�x�̂P�O�O�{  ���S�ʒu�ɂ���ꍇ�� -1 ���Ԃ� )
extern int NS_GetJoypadPOVState( int InputType, int POVNumber )
{
	int JoypadNum = ( InputType & ~DX_INPUT_KEY ) - 1 ;
	INPUTPADDATA *pad = &InputSysData.Pad[ JoypadNum ] ;
	DWORD pov;

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;
	
	// ����������Ă��Ȃ�����������t���ŏ��������s��
	if( InputSysData.InitializeFlag == FALSE )
	{
		AutoInitialize_PF() ;
		return -1 ;
	}

	// �G���[�`�F�b�N
	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum || POVNumber >= 4 )
	{
		return -1 ;
	}

	// ���̍X�V
	UpdateJoypadInputState( JoypadNum ) ;
	if( JoypadNum < 0 || JoypadNum >= InputSysData.PadNum || POVNumber >= 4 )
	{
		return -1 ;
	}

	pov = pad->State.POV[ POVNumber ] ;

	// ���S�`�F�b�N
	if( ( pov & 0xffff ) == 0xffff )
	{
		return -1 ;
	}

	// ���炩�̊p�x������ꍇ�͂��̂܂ܕԂ�
	return ( int )pov ;
}

// �W���C�p�b�h�̍ăZ�b�g�A�b�v���s��( �V���ɐڑ����ꂽ�W���C�p�b�h������ꍇ�Ɍ��o����� )
extern int NS_ReSetupJoypad( void )
{
	// �W���C�p�b�h�̍ăZ�b�g�A�b�v���s��
	return SetupJoypad() ;
}

// ���̓V�X�e���̍ăZ�b�g�A�b�v���s��
extern int NS_ReSetupInputSystem( void )
{
	// ���̓V�X�e���̏I���������s��
	TerminateInputSystem() ;

	// ���̓V�X�e���̏������������s��
	return InitializeInputSystem() ;
}

// �L�[�{�[�h�̓��͏�Ԃ̍X�V
extern int UpdateKeyboardInputState( int UseProcessMessage )
{
	static BOOL InFunction = FALSE ;
	int Result ;

	// �����ċA�h�~
	if( InFunction == TRUE )
	{
		return 0 ;
	}
	InFunction = TRUE ;

	// ���ˑ�����
	Result = UpdateKeyboardInputState_PF( UseProcessMessage ) ;

	InFunction = FALSE ;

	return Result ;
}

// �p�b�h�̓��͏�Ԃ̍X�V
static int UpdateJoypadInputState( int padno )
{
	int Result ;

	// �p�b�h�ԍ��`�F�b�N
	if( padno < 0 || padno >= MAX_JOYPAD_NUM )
	{
		return -1 ;
	}

	// ���ˑ�����
	Result = UpdateJoypadInputState_PF( padno ) ;

	// ����I��
	return Result ;
}

// �W���C�p�b�h�̐U���@�\���g�p���邩�ǂ����̃t���O���Z�b�g����
extern int NS_SetUseJoypadVibrationFlag( int Flag )
{
	InputSysData.NoUseVibrationFlag = !Flag ;

	// �I��
	return 0 ;
}

// �p�b�h�̃G�t�F�N�g�����Ɋւ���t���[���������s��
extern int JoypadEffectProcess( void )
{
	int        i ;
	int        j ;
	int        num ;
	int        time ;
	INPUTPADDATA *Pad ;

	// ����������
	if( InputSysData.InitializeFlag == FALSE )
	{
		return 0 ;
	}

	// �p�b�h�f�o�C�X�̍Ď擾
	num = InputSysData.PadNum ;
	Pad = InputSysData.Pad ;
	time = NS_GetNowCount( FALSE ) ;
	for( i = 0 ; i < num ; i ++, Pad ++ )
	{
		for( j = 0 ; j < DINPUTPAD_MOTOR_NUM ; j ++ )
		{
			if( CheckJoypadVibrationEnable_PF( Pad, j ) == FALSE )
			{
				continue ;
			}

			if( Pad->Effect[ j ].PlayFlag == FALSE )
			{
				continue ;
			}

			// �����Đ��̏ꍇ�͓��ɉ������Ȃ�
			if( Pad->Effect[ j ].Time < 0 )
			{
				continue ;
			}

			// �O�񂩂玞�����ς���Ă��Ȃ������牽�����Ȃ�
			if( Pad->Effect[ j ].BackTime == time )
			{
				continue ;
			}

			// �o�ߎ��Ԃ̉��Z
			if( time < Pad->Effect[ j ].BackTime )
			{
				Pad->Effect[ j ].BackTime = time ;
			}
			Pad->Effect[ j ].CompTime += time - Pad->Effect[ j ].BackTime ;

			// ����̎�����ۑ�
			Pad->Effect[ j ].BackTime = time ;

			// �Đ���~�̃`�F�b�N
			if( Pad->Effect[ j ].CompTime >= Pad->Effect[ j ].Time )
			{
				NS_StopJoypadVibration( i + 1, j ) ;
			}
		}
	}

	// �Đ���Ԃ̍X�V
	RefreshEffectPlayState() ;

	// �I��
	return 0 ;
}

// �p�b�h�G�t�F�N�g�̍Đ���Ԃ��X�V����(�\�t�g����A�N�e�B�u�ɂȂ邱�Ƃ����邽��)
extern int RefreshEffectPlayState( void )
{
	// ����������
	if( InputSysData.InitializeFlag == FALSE )
	{
		return 0 ;
	}

	// ���ˑ�����
	RefreshEffectPlayState_PF() ;

	// �I��
	return 0 ;
}

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_INPUT
