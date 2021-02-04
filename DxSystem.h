// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�V�X�e���v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.22c
// 
// -------------------------------------------------------------------------------

#ifndef DX_SYSTEM_H
#define DX_SYSTEM_H

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"
#include "DxStatic.h"
#include "DxBaseFunc.h"

#ifdef WINDOWS_DESKTOP_OS
#include "Windows/DxSystemWin.h"
#endif // WINDOWS_DESKTOP_OS

#ifdef __ANDROID__
#include "Android/DxSystemAndroid.h"
#endif // __ANDROID__

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
		#include "iOS/DxSystemiOS.h"
    #endif // TARGET_OS_IPHONE
#endif // __APPLE__

#ifdef EMSCRIPTEN
#include "HTML5/DxSystemHTML5.h"
#endif




#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------


// �\���̒�` --------------------------------------------------------------------

// �V�X�e���f�[�^�\����
struct DXSYSTEMDATA
{
	int						DxLib_InitializeFlag ;				// �c�w���C�u�����̏��������������Ă��邩�t���O
	int						DxLib_RunInitializeFlag ;			// �c�w���C�u�����̏����������A�t���O

	int						NotWinFlag ;						// �c�w���C�u�����̃E�C���h�E�֘A�@�\���g�p���Ȃ��t���O
	int						NotDrawFlag ;						// �`��@�\���g�p���Ȃ��t���O
	int						NotSoundFlag ;						// �T�E���h�@�\���g�p���Ȃ��t���O
	int						NotInputFlag ;						// ���͏�Ԏ擾�@�\���g�p���Ȃ��t���O

	int						EndRequestFlag ;					// �I�����N�G�X�g�t���O
	int						ASyncLoadFlag ;						// �񓯊��ǂݍ��݃t���O

	int						LastErrorCode ;						// �Ō�ɔ��������G���[�̃G���[�R�[�h( DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ� )
	wchar_t					LastErrorMessage[ 4096 ] ;			// �Ō�ɔ��������G���[�̃G���[���b�Z�[�W
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

extern DXSYSTEMDATA DxSysData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �������E�I���֌W
extern	int			DxLib_SysInit( void ) ;													// DxSysData �֌W�̏��������s��
extern	int			DxLib_EndRequest( void ) ;												// �I�����N�G�X�g���s��
extern	int			DxLib_GetEndRequest( void ) ;											// �I�����N�G�X�g�̏�Ԃ��擾����

// �G���[�����֐�
extern	int			DxLib_SetLastError(    int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ� */, const wchar_t *ErrorMessage ) ;			// �G���[�R�[�h�E���b�Z�[�W��ݒ肷��

extern	int			DxLib_Error(           const wchar_t *ErrorStr ) ;				// ���C�u�����̃G���[�������s��
extern	int			DxLib_ErrorUTF16LE(    const char    *ErrorStr ) ;				// ���C�u�����̃G���[�������s��( UTF16LE�� )
extern	int			DxLib_FmtError(        const wchar_t *FormatString, ... ) ;		// �����t�����C�u�����̃G���[�������s��
extern	int			DxLib_FmtErrorUTF16LE( const char    *FormatString, ... ) ;		// �����t�����C�u�����̃G���[�������s��( UTF16LE�� )

// �X�N���[�����W���c�w���C�u������ʍ��W�ɕϊ�����
extern	int			ConvScreenPositionToDxScreenPosition( int ScreenX, int ScreenY, int *DxScreenX, int *DxScreenY ) ;

// �񓯊��ǂݍ��݊֌W
extern	int			GetASyncLoadFlag( void ) ;												// �񓯊��ǂݍ��݂��s�����ǂ������擾����

// ���ˑ��֐�
extern	int			GetClipboardText_PF(					TCHAR   *DestBuffer ) ;						// �N���b�v�{�[�h�Ɋi�[����Ă���e�L�X�g�f�[�^��ǂݏo��( DestBuffer:��������i�[����o�b�t�@�̐擪�A�h���X   �߂�l  -1:�N���b�v�{�[�h�Ƀe�L�X�g�f�[�^������  -1�ȊO:�N���b�v�{�[�h�Ɋi�[����Ă��镶����f�[�^�̃T�C�Y( �P��:byte ) ) 
extern	int			GetClipboardText_WCHAR_T_PF(			wchar_t *DestBuffer ) ;						// �N���b�v�{�[�h�Ɋi�[����Ă���e�L�X�g�f�[�^��ǂݏo��( DestBuffer:��������i�[����o�b�t�@�̐擪�A�h���X   �߂�l  -1:�N���b�v�{�[�h�Ƀe�L�X�g�f�[�^������  -1�ȊO:�N���b�v�{�[�h�Ɋi�[����Ă��镶����f�[�^�̃T�C�Y( �P��:byte ) ) 
extern	int			SetClipboardText_WCHAR_T_PF(			const wchar_t *Text                    ) ;	// �N���b�v�{�[�h�Ƀe�L�X�g�f�[�^���i�[����
extern	int			MailApp_Send_WCHAR_T_PF(				const wchar_t *MailAddr, const wchar_t *MailCCAddr, const wchar_t *MailBCCAddr, const wchar_t *Subject, const wchar_t *Text ) ;

// wchar_t�Ŋ֐�
extern	int			GetClipboardText_WCHAR_T(		    wchar_t *DestBuffer ) ;
extern	int			SetClipboardText_WCHAR_T(		    const wchar_t *Text ) ;
extern	int			SetClipboardTextWithStrLen_WCHAR_T( const wchar_t *Text, size_t TextLength ) ;
extern	int			MailApp_Send_WCHAR_T(				const wchar_t *MailAddr, const wchar_t *MailCCAddr, const wchar_t *MailBCCAddr, const wchar_t *Subject, const wchar_t *Text ) ;


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_SYSTEM_H

