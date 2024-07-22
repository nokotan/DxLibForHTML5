// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		���O�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.24d
// 
// -------------------------------------------------------------------------------

#ifndef DX_LOG_H
#define DX_LOG_H

// �C���N���[�h ------------------------------------------------------------------

#include "DxCompileConfig.h"
#include "DxFile.h"
#include "DxThread.h"
#include <stdarg.h>

#ifdef WINDOWS_DESKTOP_OS
#include "Windows/DxLogWin.h"
#endif // WINDOWS_DESKTOP_OS

#ifdef __ANDROID__
#include "Android/DxLogAndroid.h"
#endif // __ANDROID__

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
		#include "iOS/DxLogiOS.h"
    #endif // TARGET_OS_IPHONE
#endif // __APPLE__




#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

//�c�w���C�u�������̃��e������������ɗ͌��炷���ǂ����̒�`�𔽉f����ׂ̃}�N��
#if !defined( DX_NON_LITERAL_STRING ) && !defined( DX_NON_LOG )
	#define DXSTRING( x )									x
	#define DXST_LOGFILE_ADDA( x )							LogFileAddA( x )
	#define DXST_LOGFILE_ADDW( x )							LogFileAddW( x )
	#define DXST_LOGFILE_ADDUTF16LE( x )					LogFileAddUTF16LE( x )
	#define DXST_LOGFILEFMT_ADDA( x )						LogFileFmtAddA x
	#define DXST_LOGFILEFMT_ADDW( x )						LogFileFmtAddW x
	#define DXST_LOGFILEFMT_ADDUTF16LE( x )					LogFileFmtAddUTF16LE x
	#define DXST_LOGFILE_ERRCODE_ADDA( ercode, x )			LogFileAddWithErrorCode_A( ercode, x )
	#define DXST_LOGFILE_ERRCODE_ADDW( ercode, x )			LogFileAddWithErrorCode_W( ercode, x )
	#define DXST_LOGFILE_ERRCODE_ADDUTF16LE( ercode, x )	LogFileAddWithErrorCode_UTF16LE( ercode, x )
	#define DXST_LOGFILEFMT_ERRCODE_ADDA( x )				LogFileFmtAddWithErrorCode_A x
	#define DXST_LOGFILEFMT_ERRCODE_ADDW( x )				LogFileFmtAddWithErrorCode_W x
	#define DXST_LOGFILEFMT_ERRCODE_ADDUTF16LE( x )			LogFileFmtAddWithErrorCode_UTF16LE x
	#define DXST_LOGFILE_TABADD								NS_LogFileTabAdd()
	#define DXST_LOGFILE_TABSUB								NS_LogFileTabSub()
	#define DXERRORNETLOG_ADD( x )							ErrorNetLogAdd( x )
	#define DXERRORNETWORK( x )								ErrorNetWork x
#else
	#define DXSTRING( x )									" "
	#define DXST_LOGFILE_ADDA( x )							(-1)
	#define DXST_LOGFILE_ADDW( x )							(-1)
	#define DXST_LOGFILE_ADDUTF16LE( x )					(-1)
	#define DXST_LOGFILEFMT_ADDA( x )						(-1)
	#define DXST_LOGFILEFMT_ADDW( x )						(-1)
	#define DXST_LOGFILEFMT_ADDUTF16LE( x )					(-1)
	#define DXST_LOGFILE_ERRCODE_ADDA( ercode, x )			(-1)
	#define DXST_LOGFILE_ERRCODE_ADDW( ercode, x )			(-1)
	#define DXST_LOGFILE_ERRCODE_ADDUTF16LE( ercode, x )	(-1)
	#define DXST_LOGFILEFMT_ERRCODE_ADDA( x )				(-1)
	#define DXST_LOGFILEFMT_ERRCODE_ADDW( x )				(-1)
	#define DXST_LOGFILEFMT_ERRCODE_ADDUTF16LE( x )			(-1)
	#define DXST_LOGFILE_TABADD								(0)
	#define DXST_LOGFILE_TABSUB								(0)
	#define DXERRORNETLOG_ADD( x )							(-1)
	#define DXERRORNETWORK( x )								(-1)
#endif


#ifndef DX_NON_LOG

#define LOG_MAXHEIGHT				(80)				// �P��ʂɓ��郍�O�̍ő�s
#define LOG_MAXLENGTH				(255)				// �P�s�̃��O�Ɏg���镶����̒���

// ���O�����p��`
#define LOG_FONTSIZE				(16)				// ���O�Ɏg���t�H���g�̃T�C�Y
#define LOG_FONTTICK				(4)					// ���O�\���Ɏg���t�H���g�̑���
#define LOG_TABWIDTH				(4)					// �^�u����̕�

// �\���̒�` --------------------------------------------------------------------

// ���O�����f�[�^�\����
struct LOGDATA
{
	int						InitializeFlag ;					// �����������t���O

	int						NonUseTimeStampFlag ;				// �^�C���X�^���v���o�͂��Ȃ����ǂ����̃t���O
	int						NotLogOutFlag ;						// ���O�o�͂��s�����t���O(TRUE�ōs��Ȃ�)
	int						NotSystemLogOutFlag ;				// �c�w���C�u���������̃��O�o�͂��s�����t���O(TRUE�ōs��Ȃ�)
	int						LogStartTime ;						// �N�����̃^�C���X�^���v
	wchar_t					UserLogFileName[ 256 ] ;			// SetApplicationLogFileName �Őݒ肳�ꂽ���O�t�@�C����
	wchar_t					LogOutDirectory[ FILEPATH_MAX ] ;	// ���O�o�͂��s���t�@�C����ۑ�����f�B���N�g��
	int						UseLogDateName ;					// ���O�o�͂��s���t�@�C���ɓ��t�����邩�ǂ����̃t���O
	wchar_t					LogFileName[256] ;					// ���O�o�͂��s���t�@�C���̖��O
	int						LogFileTabNum ;						// ���O�o�͎��̃^�u�̐�
	int						LogFileTabStop ;					// ���O�o�͎��̃^�u�o�̓X�g�b�v�t���O
	DX_CRITICAL_SECTION		CriticalSection ;					// �f�[�^�A�N�Z�X���p�N���e�B�J���Z�N�V����

#ifndef DX_NON_PRINTF_DX
	int						LogInitializeFlag ;					// ���O�f�[�^������������Ă��邩�t���O
	int						LogUserFontHandle ;					// ���[�U�[�w��̃��O�`��p�t�H���g�n���h��
	int						LogFontHandle ;						// ���O�`��p�t�H���g�n���h��
	int						LogFontHandleLostFlag ;				// �t�H���g�n���h�����폜���ꂽ�ۂɗ��t���O
	int						LogX ,LogY ;						// ���݂̃��O�̃J�[�\���ʒu
	wchar_t					LogString[LOG_MAXHEIGHT][LOG_MAXLENGTH] ; // ���O������
	int						LogStringColor[LOG_MAXHEIGHT][LOG_MAXLENGTH][2] ;	// ���O������̐F( 0:�{�̐F  1;���̐F )
	int						LogCharColorEnable ;				// LogCharColor ���L�����ǂ���
	int						LogCharColor[2] ;					// ���O������ɕt����F( 0:�{�̐F  1;���̐F )
	int						LogDrawFlag ;						// ���O����ʏ�ɕ\�����邩�A�t���O
	int						LogFontSize ;						// ���O�t�H���g�̃T�C�Y
	int						LogTabWidth ;						// ���O�̃^�u�̕�
	int						LogDrawWidth ;						// ���݃J�[�\��������s�̕`�敝
	int						LogFileOutFlag ;					// ���O���t�@�C���o�͂��邩�A�t���O
	RECT					LogDrawArea ;						// ���O��`�悷��̈�
#endif // DX_NON_PRINTF_DX


	LOGDATA_PF				PF ;								// ���ˑ����
} ;

// �������ϐ��錾 --------------------------------------------------------------

extern LOGDATA LogData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// ���O�o�͋@�\�֐�
extern	int			LogFileInitialize(		void ) ;										// ���O�t�@�C��������������
extern	int			LogFileTerminate(		void ) ;										// ���O�t�@�C���̌�n��

extern	int			LogFileAddA(			const char    *String ) ;						// ���O�t�@�C���ɕ�����������o��( char�� )
extern	int			LogFileAddW(			const wchar_t *String ) ;						// ���O�t�@�C���ɕ�����������o��( wchar_t�� )
extern	int			LogFileAddUTF16LE(		const char    *String ) ;						// ���O�t�@�C���ɕ�����������o��( UTF16LE�� )
extern 	int			LogFileFmtAddA(			const char    *FormatString , ... ) ;			// ���O�t�@�C���ɏ����t��������������o��( char�� )
extern 	int			LogFileFmtAddW(			const wchar_t *FormatString , ... ) ;			// ���O�t�@�C���ɏ����t��������������o��( wchar_t�� )
extern 	int			LogFileFmtAddUTF16LE(	const char    *FormatString , ... ) ;			// ���O�t�@�C���ɏ����t��������������o��( UTF16LE�� )

extern	int			LogFileAddWithErrorCode_A(			int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const char    *ErrorStr ) ;					// ���O�t�@�C���ɕ�����������o���A�G���[�R�[�h�ݒ��( char�� )
extern	int			LogFileAddWithErrorCode_W(			int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const wchar_t *ErrorStr ) ;					// ���O�t�@�C���ɕ�����������o���A�G���[�R�[�h�ݒ��( wchar_t�� )
extern	int			LogFileAddWithErrorCode_UTF16LE(	int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const char    *ErrorStr ) ;					// ���O�t�@�C���ɕ�����������o���A�G���[�R�[�h�ݒ��( UTF16LE�� )
extern 	int			LogFileFmtAddWithErrorCode_A(		int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const char	   *FormatString , ... ) ;			// ���O�t�@�C���ɏ����t��������������o���A�G���[�R�[�h�ݒ��( char�� )
extern 	int			LogFileFmtAddWithErrorCode_W(		int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const wchar_t *FormatString , ... ) ;			// ���O�t�@�C���ɏ����t��������������o���A�G���[�R�[�h�ݒ��( wchar_t�� )
extern 	int			LogFileFmtAddWithErrorCode_UTF16LE(	int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const char    *FormatString , ... ) ;			// ���O�t�@�C���ɏ����t��������������o���A�G���[�R�[�h�ݒ��( UTF16LE�� )

// wchar_t�Ŋ֐�
extern	int			LogFileAdd_WCHAR_T(		int IsSystem, int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const wchar_t *ErrorStr ) ;					// ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���
extern 	int			LogFileFmtAdd_WCHAR_T(	int IsSystem, int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const wchar_t *FormatString , ... ) ;			// �����t���� ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���( ������ printf �Ɠ��� )

extern	int			SetApplicationLogSaveDirectory_WCHAR_T(	const wchar_t *DirectoryPath );	// ���O�t�@�C��( Log.txt ) ��ۑ�����f�B���N�g���p�X��ݒ肷��
extern	int			SetApplicationLogFileName_WCHAR_T(      const wchar_t *FileName ) ;		// ���O�t�@�C���̖��O��ݒ肷��( Log.txt �ȊO�ɂ������ꍇ�Ɏg�p )

// va_list �֐�
extern 	int			LogFileFmtAdd_VaList(	const TCHAR *FormatString, va_list VaList ) ;	// �����t���� ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���( ������ printf �Ɠ��� )
extern 	int			ErrorLogFmtAdd_VaList(	const TCHAR *FormatString, va_list VaList ) ;	// LogFileFmtAdd �̋����̊֐�
extern 	int			AppLogAdd_VaList(		const TCHAR *String, va_list VaList ) ;			// LogFileFmtAdd �Ɠ����@�\�̊֐�
extern 	int			printfDx_VaList(		const TCHAR *FormatString , va_list VaList ) ;	// printf �Ɠ��������ŉ�ʂɕ������\�����邽�߂̊֐�

// ���ˑ��֐�
extern	int			LogFileInitialize_PF( const wchar_t *LogFilePath ) ;					// ���O�t�@�C�������������鏈���̊��ˑ�����
extern	int			LogFileTerminate_PF( void ) ;											// ���O�t�@�C���̌�n���̊��ˑ�����
extern	int			LogFileAdd_WCHAR_T_PF( const wchar_t *LogFilePath, const wchar_t *ErrorStr ) ;	// ���O�t�@�C���֕�����������o�������̊��ˑ�����



#ifndef DX_NON_PRINTF_DX

extern	int			IsInitializeLog( void ) ;												// ���O�@�\�̏��������s�����ǂ������擾����
extern	int			InitializeLog( void ) ;													// ���O�@�\�̏�����
extern	int			TerminateLog( void ) ;													// ���O�����̌�n�����s��
extern	int			DrawLog( void ) ;														// ���O��`�悷��
extern 	int			printfDxBase( const TCHAR *String ) ;									// printfDx �̏���������ł͂Ȃ�������������Ƃ���o�[�W����

// wchar_t�Ŋ֐�
extern 	int			printfDx_WCHAR_T(		 const wchar_t *FormatString , ... ) ;				// printf �Ɠ��������ŉ�ʂɕ������\�����邽�߂̊֐�
extern 	int			printfDxBase_WCHAR_T(	 const wchar_t *String ) ;							// printfDx_WCHAR_T �̏���������ł͂Ȃ�������������Ƃ���o�[�W����
extern 	int			putsDx_WCHAR_T(			 const wchar_t *String , int NewLine ) ;			// puts �Ɠ��������ŉ�ʂɕ������\�����邽�߂̊֐�

#endif // DX_NON_PRINTF_DX

#endif // DX_NON_LOG

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_LOG_H

