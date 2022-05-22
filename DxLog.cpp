// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		���O�v���O����
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

// �C���N���[�h ------------------------------------------------------------------
#include "DxLog.h"

#ifndef DX_NON_LOG

#include "DxLib.h"
#include "DxFont.h"
#include "DxStatic.h"
#include "DxBaseFunc.h"
#include "DxUseCLib.h"
#include "DxSystem.h"
#include "DxMemory.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

LOGDATA LogData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

#ifndef DX_NON_PRINTF_DX

// ���O�o�͋@�\�֐�
static	int			RefreshLogFont( void ) ;												// ���O�����Ŏg�p���Ă���t�H���g���X�V����
static	int			CrLog( void ) ;															// ���s����
static	int			AddCharLog( const wchar_t *C ) ;										// �ꕶ�����邩���ׂāA�K�v�Ȃ���s����
static	int			AddLog( const wchar_t *String ) ;										// ���O�o��
static	int			ClrLog( void ) ;														// ���O�̏�����

#endif // DX_NON_PRINTF_DX

// �v���O���� --------------------------------------------------------------------

// ���O�t�@�C���p�X���쐬����
static void CreateErrorLogFilePath( wchar_t *FilePathBuffer, size_t BufferBytes )
{
	int Len ;

	// ���O�o�̓t�H���_���w�肳��Ă��Ȃ��ꍇ�̓J�����g�f�B���N�g���ɂ���
	if( LogData.LogOutDirectory[ 0 ] == L'\0' )
	{
		DX_FGETDIR( FilePathBuffer, BufferBytes ) ; 
		_WCSCPY_S( LogData.LogOutDirectory, sizeof( LogData.LogOutDirectory ), FilePathBuffer ) ;
	}
	else
	{
		_WCSCPY_S( FilePathBuffer, BufferBytes, LogData.LogOutDirectory ) ;
	}

	Len = ( int )_WCSLEN( FilePathBuffer ) ;
	if( FilePathBuffer[ Len - 1 ] != L'\\' &&
		FilePathBuffer[ Len - 1 ] != L'/' )
	{
		_WCSCAT_S( FilePathBuffer, BufferBytes, L"\\" ) ;
		Len = ( int )_WCSLEN( FilePathBuffer ) ;
	}
	_WCSCPY_S( FilePathBuffer + Len, BufferBytes - Len * sizeof( wchar_t ), LogData.LogFileName ) ;
}

// ���O�t�@�C��������������
extern int LogFileInitialize( void )
{
	wchar_t LogFilePath[ 1024 ] ;

	// ���ɏ���������Ă����牽�������I��
	if( LogData.InitializeFlag )
	{
		return 0 ;
	}

	// ���O�o�͗}���t���O�������Ă���ꍇ�͏o�͂��s��Ȃ�
	if( LogData.NotLogOutFlag == TRUE )
	{
		return 0 ;
	}

	// ���[�U�[�w��̃��O�t�@�C����������ꍇ�͂�����g�p����
	if( LogData.UserLogFileName[ 0 ] != L'\0' )
	{
		_WCSCPY_S( LogData.LogFileName, sizeof( LogData.LogFileName ), LogData.UserLogFileName ) ;
	}
	else
	// ���t���̃��O�o�͂��w�肳��Ă���ꍇ�̓t�@�C�������쐬
	if( LogData.UseLogDateName == TRUE )
	{
		DATEDATA Date ;
		wchar_t String[128] ;

		// ���t���擾
		NS_GetDateTime( &Date ) ;

		// ������̍쐬
		_WCSCPY( LogData.LogFileName, L"Log" ) ;
		_ITOAW( Date.Year, String, 10 ) ;
		_WCSCAT( LogData.LogFileName, String ) ;
		_WCSCAT( LogData.LogFileName, L"_" ) ;
		_ITOAW( Date.Mon, String, 10 ) ;
		_WCSCAT( LogData.LogFileName, String ) ;
		_WCSCAT( LogData.LogFileName, L"_" ) ;
		_ITOAW( Date.Day, String, 10 ) ;
		_WCSCAT( LogData.LogFileName, String ) ;
		_WCSCAT( LogData.LogFileName, L"_" ) ;
		_ITOAW( Date.Hour, String, 10 ) ;
		_WCSCAT( LogData.LogFileName, String ) ;
		_WCSCAT( LogData.LogFileName, L"_" ) ;
		_ITOAW( Date.Min, String, 10 ) ;
		_WCSCAT( LogData.LogFileName, String ) ;
		_WCSCAT( LogData.LogFileName, L"_" ) ;
		_ITOAW( Date.Sec, String, 10 ) ;
		_WCSCAT( LogData.LogFileName, String ) ;
		_WCSCAT( LogData.LogFileName, L".txt" ) ;
	}
	else
	{
		// ����ȊO�̏ꍇ�͒ʏ�̃t�@�C����
		_WCSCPY( LogData.LogFileName, L"Log.txt" ) ;
	}

	// ���O�t�@�C���̃p�X���쐬
	CreateErrorLogFilePath( LogFilePath, sizeof( LogFilePath ) ) ;

	// �N���e�B�J���Z�N�V�����̏�����
	CriticalSection_Initialize( &LogData.CriticalSection ) ;

	// ���ˑ�����
	if( LogFileInitialize_PF( LogFilePath ) < 0 )
	{
		return -1 ;
	}

	// �^�u����������
	LogData.LogFileTabNum = 0 ; 

	// �^�u�o�̓X�g�b�v�t���O��|��
	LogData.LogFileTabStop = FALSE ;

	// �X�^�[�g���̃^�C���X�^���v���擾
	LogData.LogStartTime = NS_GetNowCount( FALSE ) ;

	// �������t���O�𗧂Ă�
	LogData.InitializeFlag = TRUE ;

	// �I��
	return 0 ;
}

// ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���
extern int LogFileAdd_WCHAR_T( int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const wchar_t *String )
{
	wchar_t			LogFilePath[ FILEPATH_MAX ] ;
	wchar_t *		UseBuffer ;
	wchar_t 		DefaultBuffer[ 1024 ] ;
	wchar_t *		AllocBuffer = NULL ;
	wchar_t *		Dest ;

	// �G���[�R�[�h�� 0 �ȊO��������G���[���ݒ���s��
	if( ErrorCode != 0 )
	{
		DxLib_SetLastError( ErrorCode, String ) ;
	}

	// ���O�o�͗}���t���O�������Ă���ꍇ�͏o�͂��s��Ȃ�
	if( LogData.NotLogOutFlag == TRUE )
	{
		return ErrorCode != 0 ? -1 : 0 ;
	}

	// ����������Ă��Ȃ������珉��������
	if( LogData.InitializeFlag == FALSE )
	{
		if( LogFileInitialize() < 0 )
		{
			return -1 ;
		}
	}

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &LogData.CriticalSection ) ;

	// �����^�C���X�^���v��^�u���܂߂������񂪃f�t�H���g�̃o�b�t�@��������������e���|�����̈�������Ŋm�ۂ���
	{
		DWORD StringLength ;

		StringLength = ( DWORD )_WCSLEN( String ) ;
		if( StringLength * 2 + 16 + LogData.LogFileTabNum > sizeof( DefaultBuffer ) / sizeof( wchar_t ) - 1 )
		{
			AllocBuffer = ( wchar_t * )NS_DxAlloc( ( StringLength * 2 + 16 + LogData.LogFileTabNum ) * sizeof( wchar_t ), NULL, -1 ) ;
			UseBuffer   = AllocBuffer ;
		}
		else
		{
			UseBuffer = DefaultBuffer ;
		}
		Dest = UseBuffer ;
	}

	// �K�蕪�����^�u�ǉ�
	if( LogData.LogFileTabStop == FALSE )
	{
		int i ;	

		// �^�C���X�^���v���o��
		if( LogData.NonUseTimeStampFlag == 0 )
		{
			_SWPRINTF( Dest, L"%d:", NS_GetNowCount( FALSE ) - LogData.LogStartTime ) ;
			Dest += _WCSLEN( Dest ) ;
		}

		if( LogData.LogFileTabNum != 0 )
		{
			for( i = 0 ; i < LogData.LogFileTabNum ; i ++, Dest ++ )
			{
				*Dest = L'\t' ;
			}
			*Dest = L'\0' ;
		}
	}

	// \n �� \r\n �ɕϊ����Ȃ���o�͕�������R�s�[
	{
		const wchar_t *	p1 ;
		const wchar_t *	p2 ;

		p1 = String ;
		p2 = _WCSCHR( p1, L'\n' ) ;
		while( p2 != NULL && ( String == p2 || p2[ -1 ] != L'\r' ) )
		{
			_MEMCPY( Dest, p1, ( p2 - p1 ) * sizeof( wchar_t ) ) ;
			Dest     += p2 - p1 ;
			Dest[ 0 ] = L'\r' ;
			Dest[ 1 ] = L'\n' ;
			Dest[ 2 ] = L'\0' ;
			Dest     += 2 ;
			p1        = p2 + 1 ;
			p2        = _WCSCHR( p1, L'\n' ) ;
		}
		_WCSCPY( Dest, p1 ) ;
	}

	// �Ō�̕��������s�ӊO�������ꍇ�̓^�u�X�g�b�v�t���O�𗧂Ă�
	LogData.LogFileTabStop = UseBuffer[ _WCSLEN( UseBuffer ) - 1 ] != L'\n' ? TRUE : FALSE ;

	// ���O�t�@�C���̃p�X���쐬
	CreateErrorLogFilePath( LogFilePath, sizeof( LogFilePath ) ) ;

	// ���ˑ�����
	LogFileAdd_WCHAR_T_PF( LogFilePath, UseBuffer ) ;

	// �e���|�����̈���m�ۂ��Ă�����J������
	if( AllocBuffer != NULL )
	{
		NS_DxFree( AllocBuffer ) ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &LogData.CriticalSection ) ;
	
	// �I��
	return ErrorCode != 0 ? -1 : 0 ;
}















// ���O�t�@�C���ɕ�����������o��( char�� )
extern int LogFileAddA( const char *String )
{
#ifdef UNICODE
	int Result ;

	SHIFT_JIS_TO_WCHAR_T_STRING_ONE_BEGIN( String, return -1 ) ;

	Result = LogFileAdd_WCHAR_T( 0, UseStringBuffer ) ;

	SHIFT_JIS_TO_WCHAR_T_STRING_END( String ) ;

	return Result ;
#else
	int Result ;

	CHAR_TO_WCHAR_T_STRING_BEGIN( String )
	CHAR_TO_WCHAR_T_STRING_SETUP( String, return -1, DX_CHARCODEFORMAT_SHIFTJIS ) ;

	Result = LogFileAdd_WCHAR_T( 0, UseStringBuffer ) ;

	CHAR_TO_WCHAR_T_STRING_END( String ) ;

	return Result ;
#endif
}

// ���O�t�@�C���ɕ�����������o��( wchar_t�� )
extern int LogFileAddW( const wchar_t *String )
{
	return LogFileAdd_WCHAR_T( 0, String ) ;
}

// ���O�t�@�C���ɕ�����������o��( UTF16LE�� )
extern int LogFileAddUTF16LE( const char *String )
{
	int Result ;

	CHAR_TO_WCHAR_T_STRING_BEGIN( String )
	CHAR_TO_WCHAR_T_STRING_SETUP( String, return -1, DX_CHARCODEFORMAT_UTF16LE ) ;

	Result = LogFileAdd_WCHAR_T( 0, UseStringBuffer ) ;

	CHAR_TO_WCHAR_T_STRING_END( String ) ;

	return Result ;
}

// ���O�t�@�C���ɏ����t��������������o��( char�� )
extern int LogFileFmtAddA( const char *FormatString , ... )
{
	va_list VaList ;
	char String[ 2048 ] ;
	
	// ���O�o�͗p�̃��X�g���Z�b�g����
	va_start( VaList , FormatString ) ;

	// �ҏW��̕�������擾����
	CL_vsnprintf( DX_CHARCODEFORMAT_SHIFTJIS, FALSE, DX_CHARCODEFORMAT_SHIFTJIS, WCHAR_T_CHARCODEFORMAT, String , sizeof( String ), FormatString , VaList ) ;
	
	// �ϒ����X�g�̃|�C���^�����Z�b�g����
	va_end( VaList ) ;

	// ���s������ǉ�����
	_STRCAT_S( String, sizeof( String ), "\n" ) ;

	// ���O�o�͂���
	return LogFileAddA( String ) ;
}

// ���O�t�@�C���ɏ����t��������������o��( wchar_t�� )
extern int LogFileFmtAddW( const wchar_t *FormatString , ... )
{
	va_list VaList ;
	wchar_t String[ 2048 ] ;
	
	// ���O�o�͗p�̃��X�g���Z�b�g����
	va_start( VaList , FormatString ) ;

	// �ҏW��̕�������擾����
	_VSWNPRINTF( String, sizeof( String ) / 2, FormatString, VaList ) ;
	
	// �ϒ����X�g�̃|�C���^�����Z�b�g����
	va_end( VaList ) ;

	// ���s������ǉ�����
	_WCSCAT_S( String, sizeof( String ), L"\n" ) ;

	// ���O�o�͂���
	return LogFileAddW( String ) ;
}

// ���O�t�@�C���ɏ����t��������������o��( UTF16LE�� )
extern int LogFileFmtAddUTF16LE( const char *FormatString , ... )
{
	va_list VaList ;
	char String[ 2048 ] ;
	BYTE UTF16LE_EN_N[ 4 ] = { '\n', 0, 0, 0 } ;
	
	// ���O�o�͗p�̃��X�g���Z�b�g����
	va_start( VaList , FormatString ) ;

	// �ҏW��̕�������擾����
	CL_vsnprintf( DX_CHARCODEFORMAT_UTF16LE, TRUE, CHAR_CHARCODEFORMAT, DX_CHARCODEFORMAT_UTF16LE, String, sizeof( String ) / 2, FormatString, VaList ) ;
	
	// �ϒ����X�g�̃|�C���^�����Z�b�g����
	va_end( VaList ) ;

	// ���s������ǉ�����
	CL_strcat_s( DX_CHARCODEFORMAT_UTF16LE, String, sizeof( String ), ( const char * )UTF16LE_EN_N ) ;

	// ���O�o�͂���
	return LogFileAddUTF16LE( String ) ;
}










// ���O�t�@�C���ɕ�����������o���A�G���[�R�[�h�ݒ��( char�� )
extern int LogFileAddWithErrorCode_A( int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const char *String )
{
#ifdef UNICODE
	int Result ;

	SHIFT_JIS_TO_WCHAR_T_STRING_ONE_BEGIN( String, return -1 ) ;

	Result = LogFileAdd_WCHAR_T( ErrorCode, UseStringBuffer ) ;

	SHIFT_JIS_TO_WCHAR_T_STRING_END( String ) ;

	return Result ;
#else
	int Result ;

	CHAR_TO_WCHAR_T_STRING_BEGIN( String )
	CHAR_TO_WCHAR_T_STRING_SETUP( String, return -1, DX_CHARCODEFORMAT_SHIFTJIS ) ;

	Result = LogFileAdd_WCHAR_T( ErrorCode, UseStringBuffer ) ;

	CHAR_TO_WCHAR_T_STRING_END( String ) ;

	return Result ;
#endif
}

// ���O�t�@�C���ɕ�����������o���A�G���[�R�[�h�ݒ��( wchar_t�� )
extern int LogFileAddWithErrorCode_W( int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const wchar_t *String )
{
	return LogFileAdd_WCHAR_T( ErrorCode, String ) ;
}

// ���O�t�@�C���ɕ�����������o���A�G���[�R�[�h�ݒ��( UTF16LE�� )
extern int LogFileAddWithErrorCode_UTF16LE( int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const char *String )
{
	int Result ;

	CHAR_TO_WCHAR_T_STRING_BEGIN( String )
	CHAR_TO_WCHAR_T_STRING_SETUP( String, return -1, DX_CHARCODEFORMAT_UTF16LE ) ;

	Result = LogFileAdd_WCHAR_T( ErrorCode, UseStringBuffer ) ;

	CHAR_TO_WCHAR_T_STRING_END( String ) ;

	return Result ;
}

// ���O�t�@�C���ɏ����t��������������o���A�G���[�R�[�h�ݒ��( char�� )
extern int LogFileFmtAddWithErrorCode_A( int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const char *FormatString , ... )
{
	va_list VaList ;
	char String[ 2048 ] ;
	
	// ���O�o�͗p�̃��X�g���Z�b�g����
	va_start( VaList , FormatString ) ;

	// �ҏW��̕�������擾����
	_VSNPRINTF( String , sizeof( String ), FormatString , VaList ) ;
	
	// �ϒ����X�g�̃|�C���^�����Z�b�g����
	va_end( VaList ) ;

	// ���s������ǉ�����
	_STRCAT_S( String, sizeof( String ), "\n" ) ;

	// ���O�o�͂���
	return LogFileAddWithErrorCode_A( ErrorCode, String ) ;
}

// ���O�t�@�C���ɏ����t��������������o���A�G���[�R�[�h�ݒ��( wchar_t�� )
extern int LogFileFmtAddWithErrorCode_W( int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const wchar_t *FormatString , ... )
{
	va_list VaList ;
	wchar_t String[ 2048 ] ;
	
	// ���O�o�͗p�̃��X�g���Z�b�g����
	va_start( VaList , FormatString ) ;

	// �ҏW��̕�������擾����
	_VSWNPRINTF( String, sizeof( String ) / 2, FormatString, VaList ) ;
	
	// �ϒ����X�g�̃|�C���^�����Z�b�g����
	va_end( VaList ) ;

	// ���s������ǉ�����
	_WCSCAT_S( String, sizeof( String ), L"\n" ) ;

	// ���O�o�͂���
	return LogFileAddWithErrorCode_W( ErrorCode, String ) ;
}

// ���O�t�@�C���ɏ����t��������������o���A�G���[�R�[�h�ݒ��( UTF16LE�� )
extern int LogFileFmtAddWithErrorCode_UTF16LE( int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const char *FormatString , ... )
{
	va_list VaList ;
	char String[ 2048 ] ;
	BYTE UTF16LE_EN_N[ 4 ] = { '\n', 0, 0, 0 } ;
	
	// ���O�o�͗p�̃��X�g���Z�b�g����
	va_start( VaList , FormatString ) ;

	// �ҏW��̕�������擾����
	CL_vsnprintf( DX_CHARCODEFORMAT_UTF16LE, TRUE, CHAR_CHARCODEFORMAT, DX_CHARCODEFORMAT_UTF16LE, String, sizeof( String ) / 2, FormatString, VaList ) ;
	
	// �ϒ����X�g�̃|�C���^�����Z�b�g����
	va_end( VaList ) ;

	// ���s������ǉ�����
	CL_strcat_s( DX_CHARCODEFORMAT_UTF16LE, String, sizeof( String ), ( const char * )UTF16LE_EN_N ) ;

	// ���O�o�͂���
	return LogFileAddWithErrorCode_UTF16LE( ErrorCode, String ) ;
}
















// LogFileAdd �̋����̊֐�
extern int NS_ErrorLogAdd( const TCHAR *String )
{
	NS_LogFileAdd( String ) ;
	return -1 ;
}

// ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���
extern int NS_LogFileAdd( const TCHAR *String )
{
#ifdef UNICODE
	return LogFileAdd_WCHAR_T( 0, String ) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( String, return -1 ) ;

	Result = LogFileAdd_WCHAR_T( 0, UseStringBuffer ) ;

	TCHAR_TO_WCHAR_T_STRING_END( String )

	return Result ;
#endif
}

// ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���
extern int NS_LogFileAddWithStrLen( const TCHAR *String, size_t StringLength )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( String, StringLength, return -1 )
	Result = LogFileAdd_WCHAR_T( 0, UseStringBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( String )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( String, StringLength, return -1 )
	Result = LogFileAdd_WCHAR_T( 0, UseStringBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( String )
#endif
	return Result ;
}

// LogFileFmtAdd �̋����̊֐�
extern int NS_ErrorLogFmtAdd( const TCHAR *FormatString , ... )
{
	TCHAR_FORMATSTRING_SETUP

	// ���s������ǉ�����
	_TSTRCAT_S( String, sizeof( String ), _T( "\n" ) ) ;

	// ���O�o�͂���
	NS_LogFileAdd( String ) ;
	
	return -1 ;
}

// �����t���� ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���( ������ printf �Ɠ��� )
extern int NS_LogFileFmtAdd( const TCHAR *FormatString , ... )
{
	int Result ;

	TCHAR_FORMATSTRING_SETUP

	// ���s������ǉ�����
	_TSTRCAT_S( String, sizeof( String ), _T( "\n" ) ) ;

	// ���O�o�͂���
	Result = NS_LogFileAdd( String ) ;
	
	return Result ;
}

// �����t���� ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���( ������ printf �Ɠ��� )
extern int LogFileFmt_WCHAR_T( int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ�*/, const wchar_t *FormatString , ... )
{
	int Result ;

	WCHAR_T_FORMATSTRING_SETUP

	// ���s������ǉ�����
	_WCSCAT_S( String, sizeof( String ), L"\n" ) ;

	// ���O�o�͂���
	Result = LogFileAdd_WCHAR_T( ErrorCode, String ) ;
	
	return Result ;
}


// LogFileTabAdd �̋����̊֐�
extern int NS_ErrorLogTabAdd( void )
{
	return NS_LogFileTabAdd() ;
}

// ���O�t�@�C��( Log.txt ) �ɏo�͂��镶����̑O�ɕt����^�u�̐�������₷
extern int NS_LogFileTabAdd( void )
{
	LogData.LogFileTabNum ++ ;

	return 0 ;
}

// LogFileTabSub �̋����̊֐�
extern int NS_ErrorLogTabSub( void )
{
	return NS_LogFileTabSub() ;
}

// ���O�t�@�C��( Log.txt ) �ɏo�͂��镶����̑O�ɕt����^�u�̐�������炷
extern int NS_LogFileTabSub( void )
{
	if( LogData.LogFileTabNum != 0 ) LogData.LogFileTabNum -- ;

	return 0 ;
}

// �^�C���X�^���v�̗L����ݒ肷��
extern int NS_SetUseTimeStampFlag( int UseFlag )
{
	LogData.NonUseTimeStampFlag = UseFlag != 0 ? 0 : 1 ;

	return 0 ;
}

// �����t�����O������������o��
extern int NS_AppLogAdd( const TCHAR *String, ... )
{
	va_list VaList ;
	TCHAR StringBuf[ 2048 ] ;

	va_start( VaList, String ) ;
	_TVSNPRINTF( StringBuf, sizeof( StringBuf ) / sizeof( TCHAR ), String, VaList ) ;
	va_end( VaList ) ;

	return NS_ErrorLogAdd( StringBuf ) ;
}

// ���O�t�@�C���̌�n��
extern int LogFileTerminate( void )
{
	// ���ˑ��������s��
	LogFileTerminate_PF() ;

	// �N���e�B�J���Z�N�V�����̍폜
	CriticalSection_Delete( &LogData.CriticalSection ) ;

	// �������t���O��|��
	LogData.InitializeFlag = FALSE ;

	// �I��
	return 0 ; 
}

// ���O�t�@�C�����ɓ��t�����邩�ǂ������Z�b�g����
extern int NS_SetUseDateNameLogFile( int Flag )
{
	LogData.UseLogDateName = Flag ;

	// �I��
	return 0 ;
}

// ���O�o�͂��s�����ۂ��̃Z�b�g
extern int NS_SetOutApplicationLogValidFlag( int Flag )
{
	// �t���O�Z�b�g
	LogData.NotLogOutFlag = !Flag ;

	// �I��
	return 0 ;
}

// ���O�t�@�C����ۑ�����f�B���N�g���p�X��ݒ肷��
extern int NS_SetApplicationLogSaveDirectory( const TCHAR *DirectoryPath )
{
#ifdef UNICODE
	return SetApplicationLogSaveDirectory_WCHAR_T( DirectoryPath ) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( DirectoryPath, return -1 )

	Result = SetApplicationLogSaveDirectory_WCHAR_T( UseDirectoryPathBuffer ) ;

	TCHAR_TO_WCHAR_T_STRING_END( DirectoryPath )

	return Result ;
#endif
}

// ���O�t�@�C��( Log.txt ) ��ۑ�����f�B���N�g���p�X��ݒ肷��
extern int NS_SetApplicationLogSaveDirectoryWithStrLen( const TCHAR *DirectoryPath, size_t DirectoryPathLength )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( DirectoryPath, DirectoryPathLength, return -1 )
	Result = SetApplicationLogSaveDirectory_WCHAR_T( UseDirectoryPathBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( DirectoryPath )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( DirectoryPath, DirectoryPathLength, return -1 )
	Result = SetApplicationLogSaveDirectory_WCHAR_T( UseDirectoryPathBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( DirectoryPath )
#endif
	return Result ;
}

// ���O�t�@�C����ۑ�����f�B���N�g���p�X��ݒ肷��
extern int SetApplicationLogSaveDirectory_WCHAR_T( const wchar_t *DirectoryPath )
{
	// �p�X�̒������o�b�t�@�̃T�C�Y�𒴂���ꍇ�̓G���[
	if( ( _WCSLEN( DirectoryPath ) + 1 ) * sizeof( wchar_t ) > sizeof( LogData.LogOutDirectory ) )
	{
		return -1 ;
	}

	// �p�X�̕ۑ�
	_WCSCPY( LogData.LogOutDirectory, DirectoryPath ) ;

	// �I��
	return 0 ;
}

// ���O�t�@�C���̖��O��ݒ肷��( Log.txt �ȊO�ɂ������ꍇ�Ɏg�p )
extern int NS_SetApplicationLogFileName( const TCHAR *FileName )
{
#ifdef UNICODE
	return SetApplicationLogFileName_WCHAR_T( FileName ) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( FileName, return -1 )

	Result = SetApplicationLogFileName_WCHAR_T( UseFileNameBuffer ) ;

	TCHAR_TO_WCHAR_T_STRING_END( FileName )

	return Result ;
#endif
}

// ���O�t�@�C���̖��O��ݒ肷��( Log.txt �ȊO�ɂ������ꍇ�Ɏg�p )
extern int NS_SetApplicationLogFileNameWithStrLen( const TCHAR *FileName, size_t FileNameLength )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( FileName, FileNameLength, return -1 )
	Result = SetApplicationLogFileName_WCHAR_T( UseFileNameBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( FileName )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( FileName, FileNameLength, return -1 )
	Result = SetApplicationLogFileName_WCHAR_T( UseFileNameBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( FileName )
#endif
	return Result ;
}

// ���O�t�@�C���̖��O��ݒ肷��( Log.txt �ȊO�ɂ������ꍇ�Ɏg�p )
extern int SetApplicationLogFileName_WCHAR_T( const wchar_t *FileName )
{
	// �t�@�C�������o�b�t�@�̃T�C�Y�𒴂���ꍇ�̓G���[
	if( ( _WCSLEN( FileName ) + 1 ) * sizeof( wchar_t ) > sizeof( LogData.UserLogFileName ) )
	{
		return -1 ;
	}

	// �t�@�C�����̕ۑ�
	_WCSCPY( LogData.UserLogFileName, FileName ) ;

	// �I��
	return 0 ;
}

// va_list �֐�

// �����t���� ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���( ������ printf �Ɠ��� )
extern int LogFileFmtAdd_VaList( const TCHAR *FormatString, va_list VaList )
{
	int Result ;

	TCHAR_FORMATSTRING_VALIST_SETUP

	// ���s������ǉ�����
	_TSTRCAT_S( String, sizeof( String ), _T( "\n" ) ) ;

	// ���O�o�͂���
	Result = NS_LogFileAdd( String ) ;
	
	return Result ;
}

// LogFileFmtAdd �̋����̊֐�
extern int ErrorLogFmtAdd_VaList( const TCHAR *FormatString, va_list VaList )
{
	TCHAR_FORMATSTRING_VALIST_SETUP

	// ���s������ǉ�����
	_TSTRCAT_S( String, sizeof( String ), _T( "\n" ) ) ;

	// ���O�o�͂���
	NS_LogFileAdd( String ) ;
	
	return -1 ;
}

// LogFileFmtAdd �Ɠ����@�\�̊֐�
extern int AppLogAdd_VaList( const TCHAR *String, va_list VaList )
{
	TCHAR StringBuf[ 2048 ] ;

	_TVSNPRINTF( StringBuf, sizeof( StringBuf ) / sizeof( TCHAR ), String, VaList ) ;

	return NS_ErrorLogAdd( StringBuf ) ;
}

// printf �Ɠ��������ŉ�ʂɕ������\�����邽�߂̊֐�
extern int printfDx_VaList( const TCHAR *FormatString, va_list VaList )
{
	int Result ;

	TCHAR_FORMATSTRING_VALIST_SETUP

#ifdef UNICODE
	Result = printfDxBase_WCHAR_T( String ) ;
#else
	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( String, return -1 )

	Result = printfDxBase_WCHAR_T( UseStringBuffer ) ;

	TCHAR_TO_WCHAR_T_STRING_END( String )
#endif

	// �I��
	return Result ;
}









#ifndef DX_NON_PRINTF_DX

// ���O�o�͋@�\�֐�

// ���O�@�\�̏�����
extern int InitializeLog( void )
{
	if( IsInitializeLog() == FALSE ) return -1 ;

	// ���ɏ���������Ă����牽�����Ȃ�
	if( LogData.LogInitializeFlag == TRUE ) return 0 ;

	// �������t���O�𗧂Ă�
	LogData.LogInitializeFlag = TRUE ;

	// ���O�t�H���g�̃T�C�Y���Z�b�g
	LogData.LogFontSize = LOG_FONTSIZE ;

	// �t�H���g�̍쐬
	LogData.LogFontHandle = -1 ;
	LogData.LogFontHandleLostFlag = TRUE ;

	// ���O�̗L�薳���t���O���Z�b�g
	LogData.LogDrawFlag = FALSE ;

	// ���O�̃t�@�C���o�͗L�薳���t���O���Z�b�g
	LogData.LogFileOutFlag = FALSE ;

	// ���O�̕����Z�b�g
	LogData.LogTabWidth = LOG_TABWIDTH ;

	// �J�[�\���̈ʒu���Z�b�g
	LogData.LogX = LogData.LogY = 0 ;

	// �X�g�����O��������
	_MEMSET( LogData.LogString, 0, sizeof( LogData.LogString ) ) ;

	// �I��
	return 0 ;
}

// ���O�����̌�n�����s��
extern int TerminateLog( void )
{
	// ���O����������������Ă��Ȃ������Ȃɂ����Ȃ�
	if( LogData.LogInitializeFlag == FALSE ) return 0 ;

	// �t�H���g�n���h�����폜����
	if( LogData.LogFontHandleLostFlag == FALSE && LogData.LogFontHandle > 0 )
	{
		NS_DeleteFontToHandle( LogData.LogFontHandle ) ;
	}
	LogData.LogFontHandleLostFlag = TRUE ;
	LogData.LogFontHandle = -1 ;

	// �������t���O��|��
	LogData.LogInitializeFlag = FALSE ;

	// �I��
	return 0 ;
}

// ���O�����Ŏg�p���Ă���t�H���g���X�V����
static int RefreshLogFont( void )
{
	if( LogData.LogInitializeFlag == FALSE )
	{
		if( InitializeLog() < 0 )
		{
			return 0 ;
		}
	}

	if( LogData.LogFontHandleLostFlag == FALSE )
	{
		return 0 ;
	}

	// �t�H���g�n���h�����쐬����
	CREATEFONTTOHANDLE_GPARAM GParam ;
	InitCreateFontToHandleGParam( &GParam ) ;
	LogData.LogFontHandle = CreateFontToHandle_UseGParam( &GParam, NULL, LogData.LogFontSize, LOG_FONTTICK, DX_FONTTYPE_EDGE, -1, -1, FALSE, -1, FALSE ) ;
	if( LogData.LogFontHandle >= 0 )
	{
		// �t�H���g�n���h�����폜���ꂽ�ۂɗ��t���O�̃|�C���^���Z�b�g����
		NS_SetFontLostFlag( LogData.LogFontHandle, &LogData.LogFontHandleLostFlag  ) ;
	}
	else
	{
		LogData.LogFontHandle = DX_DEFAULT_FONT_HANDLE ;
	}

	LogData.LogFontHandleLostFlag = FALSE ;

	return 0 ;
}

// ���s����
static int CrLog( void )
{
	int ScWidth, ScHeight, StrHeight ;
	int FontSize = -1 ;

	if( LogData.LogInitializeFlag == FALSE )
	{
		if( InitializeLog() < 0 )
		{
			return 0 ;
		}
	}

	// �t�H���g���폜����Ă���ꍇ�͍č쐬����
	RefreshLogFont() ;

	// ��ʂ̃T�C�Y���擾
	NS_GetDrawScreenSize( &ScWidth , &ScHeight ) ;
	
	// ��ʓ��Ɏ��܂�s�����Z�o
	if( LogData.LogUserFontHandle > 0 )
	{
		FontSize = NS_GetFontSizeToHandle( LogData.LogUserFontHandle ) ;
	}
	if( FontSize < 0 )
	{
		LogData.LogUserFontHandle = 0 ;
		FontSize = LogData.LogFontSize ;
	}
	StrHeight = ScHeight / FontSize ;
	if( StrHeight > LOG_MAXHEIGHT ) StrHeight = LOG_MAXHEIGHT ;

	// ���s�������ʂ���O��Ă��܂�Ȃ������ׁA�O��邩�ǂ����ŏ����𕪊�
	if( StrHeight <= LogData.LogY + 1 )
	{
		// �O���ꍇ�͈�s���f�[�^��S�ďグ��

		// ��������P�s�����炷
		_MEMMOVE( LogData.LogString[0], LogData.LogString[1], sizeof( wchar_t ) * LOG_MAXLENGTH * LogData.LogY ) ;
	}
	else
	{
		// �x���W���C���N�������g
		LogData.LogY ++ ;
	}

	// �V�����s�̕����������������
	_MEMSET( LogData.LogString[ LogData.LogY ], 0, sizeof( wchar_t ) * LOG_MAXLENGTH ) ;

	// �`�敝��������
	LogData.LogDrawWidth = 0 ;

	// �w���W������������
	LogData.LogX = 0 ;

	// �I��
	return 0 ;
}

// �ꕶ�����O�ɒǉ�����A�K�v�Ȃ���s����
static int AddCharLog( const wchar_t *C )
{
	int ScWidth, ScHeight ;
	int Width = 0, Length, i ;
	int Color[ 2 ] ;

	if( LogData.LogInitializeFlag == FALSE )
	{
		if( InitializeLog() < 0 )
		{
			return 0 ;
		}
	}

	// �t�H���g���폜����Ă���ꍇ�͍č쐬����
	RefreshLogFont() ;

	// ��ʂ̃T�C�Y���擾
	NS_GetDrawScreenSize( &ScWidth , &ScHeight ) ;

	// �V���������̕`�敝���擾
	if( CHECK_WCHAR_T_DOUBLE( *C ) == TRUE )
	{
		Length = 2 ;
	}
	else
	{
		Length = 1 ;
	}

	// �����񂪃o�b�t�@���I�[�o�[���Ȃ������ׂ�A�o��ꍇ�͉��s����
	if( LogData.LogX + Length >= LOG_MAXLENGTH )
	{
		CrLog() ;
	}
	else
	{
		// ��ʊO�ɏo�Ȃ������ׂ�A�o��ꍇ�͉��s����
		Width = GetDrawStringWidthToHandle_WCHAR_T( C, 0, Length, LogData.LogFontHandle, FALSE ) ;
		if( Width + LogData.LogDrawWidth >= ScWidth ) 
		{
			CrLog() ;
		}
	}

	// �`�敝�����Z
	LogData.LogDrawWidth += Width ;

	// �F������
	if( LogData.LogCharColorEnable )
	{
		Color[ 0 ] = LogData.LogCharColor[ 0 ] ;
		Color[ 1 ] = LogData.LogCharColor[ 1 ] ;
	}
	else
	{
		Color[ 0 ] = NS_GetColor( 255,255,255 ) ;
		Color[ 1 ] = NS_GetColor( 0,0,0 ) ;
	}

	// ������ǉ�
	for( i = 0 ; i < Length ; i ++ )
	{
		LogData.LogString[ LogData.LogY ][ LogData.LogX + i ] = C[ i ]  ;
		LogData.LogStringColor[ LogData.LogY ][ LogData.LogX + i ][ 0 ] = Color[ 0 ] ;
		LogData.LogStringColor[ LogData.LogY ][ LogData.LogX + i ][ 1 ] = Color[ 1 ] ;
	}
	LogData.LogString[ LogData.LogY ][ LogData.LogX + i ] = L'\0' ;

	// �J�[�\���ʒu���C���N�������g
	LogData.LogX += Length  ;

	// �I��
	return Length ;
}


// ���O�o��
static int AddLog( const wchar_t *String )
{
	int StrLen ;

	if( LogData.LogInitializeFlag == FALSE )
	{
		if( InitializeLog() < 0 )
		{
			return 0 ;
		}
	}

	// �t�H���g���폜����Ă���ꍇ�͍č쐬����
	RefreshLogFont() ;

	// �ꕶ���Âǉ����Ă���
	{
		int i ;
		const wchar_t *C ;

		// �������r�؂��܂ŌJ��Ԃ�
		StrLen = ( int )_WCSLEN( String ) ;
		for( i = 0 ; i < StrLen ; i ++ )
		{
			C = &String[ i ] ;

			// ���̕����̃^�C�v�ɂ���ď����𕪊�
			switch( *C )
			{
			case L'\n' :
				// ���s�R�[�h�̏ꍇ�͉��s�������s��
				CrLog() ;
				break ;

			case L'\t' :
				{
					int j ;

					// �^�u�̏ꍇ�̓^�u�̕��������X�y�[�X��ǉ�
					for( j = 0 ; j < LogData.LogTabWidth ; j ++ )
						AddCharLog( L" " )  ;
				}
				break ;

			case L'\a' : case L'\b' : 
			case L'\f' : case L'\r' : case L'\v' :
				break ;

			default :
				// ����ȊO�̏ꍇ�͕��ʂɒǉ�
				if( AddCharLog( C ) == 2 ) i ++ ;
				break ;
			}
		}
	}

	// �I��
	return 0 ;
}

// ���O�̏�����
static int ClrLog( void )
{
	if( LogData.LogInitializeFlag == FALSE )
	{
		if( InitializeLog() < 0 )
		{
			return 0 ;
		}
	}

	// �t�H���g���폜����Ă���ꍇ�͍č쐬����
	RefreshLogFont() ;

	// ���O��������
	_MEMSET( LogData.LogString, 0, sizeof( LogData.LogString ) ) ;

	// �J�[�\���ʒu��������
	LogData.LogX = LogData.LogY = 0 ;
	LogData.LogDrawWidth = 0 ;

	// �I��
	return 0 ;
}

// ���O�o�̓t���O���Z�b�g����
extern int NS_SetLogDrawOutFlag( int DrawFlag )
{
	// ���O�`��o�̓t���O���Z�b�g����
	LogData.LogDrawFlag = DrawFlag ;

	// �I��
	return 0 ;
}

// ���O�o�͂����邩�t���O�̎擾
extern int NS_GetLogDrawFlag( void )
{
	return LogData.LogDrawFlag ;
}

// printfDx �ŉ�ʂɏo�͂��郍�O�t�H���g�̃T�C�Y��ύX����
extern int NS_SetLogFontSize( int Size )
{
	if( Size < 0 ) Size = LOG_FONTSIZE;

	LogData.LogFontSize = Size;

	if( LogData.LogFontHandle >= 0 )
	{
		DeleteFontToHandle( LogData.LogFontHandle );
		LogData.LogFontHandle = -1;
		LogData.LogFontHandleLostFlag = TRUE;
	}

	RefreshLogFont();

	// �I��
	return 0;
}

// printfDx �̌��ʂ���ʂɏo�͂���ۂɎg�p����t�H���g�̃n���h����ύX����
extern int NS_SetLogFontHandle( int FontHandle )
{
	LogData.LogUserFontHandle = FontHandle ;

	// �I��
	return 0 ;
}

// printfDx �̌��ʂ���ʂɏo�͂���ۂ̕`�悷��̈��ݒ肷��
extern int NS_SetLogDrawArea( int x1, int y1, int x2, int y2 )
{
	LogData.LogDrawArea.left   = x1 ;
	LogData.LogDrawArea.top    = y1 ;
	LogData.LogDrawArea.right  = x2 ;
	LogData.LogDrawArea.bottom = y2 ;

	// �I��
	return 0 ;
}

// ���O��`�悷��
extern int DrawLog( void )
{
	int StrHeight , i ;
	int DrawX, DrawY ;
	int DrawXTemp ;
	int DrawW, DrawH ;
	int FontSize = -1 ;
	int FontHandle ;
	int Color ;
	int EdgeColor ;
	wchar_t String[ LOG_MAXLENGTH ] ;
	int Addr ;
	int StrLength ;

	if( LogData.LogInitializeFlag == FALSE )
	{
		if( InitializeLog() < 0 )
		{
			return 0 ;
		}
	}

	// �L���ȕ`��͈͂��ݒ肳��Ă�����g�p����
	DrawX = LogData.LogDrawArea.left ;
	DrawY = LogData.LogDrawArea.top ;
	DrawW = LogData.LogDrawArea.right  - LogData.LogDrawArea.left ;
	DrawH = LogData.LogDrawArea.bottom - LogData.LogDrawArea.top ;
	if( DrawW == 0 || DrawH == 0 )
	{
		// �W���ł͕`���͉�ʍ���
		DrawX = 0 ;
		DrawY = 0 ;

		// ��ʂ̃T�C�Y���擾����
		NS_GetDrawScreenSize( &DrawW , &DrawH ) ;
	}

	// �t�H���g���폜����Ă���ꍇ�͍č쐬����
	RefreshLogFont() ;
	
	// ��ʂɃ��O��`�悷��
	if( LogData.LogUserFontHandle > 0 )
	{
		FontSize = NS_GetFontSizeToHandle( LogData.LogUserFontHandle ) ;
	}
	if( FontSize < 0 )
	{
		LogData.LogUserFontHandle = 0 ;
		FontSize = LogData.LogFontSize ;
		FontHandle = LogData.LogFontHandle ;
	}
	else
	{
		FontHandle = LogData.LogUserFontHandle ;
	}
	StrHeight = DrawH / FontSize  ;
	if( StrHeight >= LOG_MAXHEIGHT ) StrHeight = LOG_MAXHEIGHT ;

	Color = NS_GetColor( 255, 255, 255 ) ;
	EdgeColor = NS_GetColor( 0, 0, 0 ) ;
	for( i = 0 ; i < StrHeight ; i ++ )
	{
		DrawXTemp = DrawX ;
		Addr = 0 ;
		StrLength = 0 ;
		Color     = LogData.LogStringColor[ i ][ Addr ][ 0 ] ;
		EdgeColor = LogData.LogStringColor[ i ][ Addr ][ 1 ] ;
		while( LogData.LogString[ i ][ Addr ] != L'\0' )
		{
			if( Color     != LogData.LogStringColor[ i ][ Addr ][ 0 ] ||
				EdgeColor != LogData.LogStringColor[ i ][ Addr ][ 1 ] )
			{
				String[ StrLength ] = L'\0' ;
				DrawStringToHandle_WCHAR_T( DrawXTemp , DrawY + i * FontSize , String , StrLength , Color, FontHandle , EdgeColor, FALSE ) ;
				DrawXTemp += GetDrawStringWidthToHandle_WCHAR_T( String, 0, StrLength, FontHandle, FALSE ) ;
				StrLength = 0 ;
				Color     = LogData.LogStringColor[ i ][ Addr ][ 0 ] ;
				EdgeColor = LogData.LogStringColor[ i ][ Addr ][ 1 ] ;
			}
			String[ StrLength ] = LogData.LogString[ i ][ Addr ] ;
			StrLength ++ ;
			Addr ++ ;
		}

		if( StrLength > 0 )
		{
			String[ StrLength ] = L'\0' ;
			DrawStringToHandle_WCHAR_T( DrawXTemp , DrawY + i * FontSize , String , StrLength , Color, FontHandle , EdgeColor, FALSE ) ;
			DrawXTemp += GetDrawStringWidthToHandle_WCHAR_T( String, 0, StrLength, FontHandle, FALSE ) ;
			StrLength = 0 ;
		}

//		DrawStringToHandle_WCHAR_T( DrawX , DrawY + i * FontSize , LogData.LogString[ i ] , _WCSLEN( LogData.LogString[ i ] ) , Color, FontHandle , EdgeColor, FALSE ) ;
	}

	// �I��
	return 0 ;
}






// �ȈՉ�ʏo�͊֐�
extern int printfDxBase( const TCHAR *String )
{
	int Result ;

#ifdef UNICODE
	Result = printfDxBase_WCHAR_T( String ) ;
#else
	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( String, return -1 )

	Result = printfDxBase_WCHAR_T( UseStringBuffer ) ;

	TCHAR_TO_WCHAR_T_STRING_END( String )
#endif

	// �I��
	return Result ;
}

// �ȈՉ�ʏo�͊֐�
extern int NS_printfDx( const TCHAR *FormatString , ... )
{
	int Result ;

	TCHAR_FORMATSTRING_SETUP

#ifdef UNICODE
	Result = printfDxBase_WCHAR_T( String ) ;
#else
	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( String, return -1 )

	Result = printfDxBase_WCHAR_T( UseStringBuffer ) ;

	TCHAR_TO_WCHAR_T_STRING_END( String )
#endif

	// �I��
	return Result ;
}

// �ȈՉ�ʏo�͊֐�
extern int printfDx_WCHAR_T( const wchar_t *FormatString , ... )
{
	int Result ;

	WCHAR_T_FORMATSTRING_SETUP

	// ���O�o�̓t���O�𗧂Ă�
	LogData.LogDrawFlag = TRUE ;

	// ���O�o�͊֐����Ă�
	Result = AddLog( String ) ;

	// �I��
	return Result ;
}

// printfDx_WCHAR_T �̏���������ł͂Ȃ�������������Ƃ���o�[�W����
extern int printfDxBase_WCHAR_T( const wchar_t *String )
{
	int Result ;

	// ���O�o�̓t���O�𗧂Ă�
	LogData.LogDrawFlag = TRUE ;

	// ���O�o�͊֐����Ă�
	Result = AddLog( String ) ;

	// �I��
	return Result ;
}

// puts �Ɠ��������ŉ�ʂɕ������\�����邽�߂̊֐�
extern int NS_putsDx( const TCHAR *String, int NewLine )
{
#ifdef UNICODE
	return putsDx_WCHAR_T( String, NewLine ) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( String, return -1 )

	Result = putsDx_WCHAR_T( UseStringBuffer, NewLine ) ;

	TCHAR_TO_WCHAR_T_STRING_END( String )

	return Result ;
#endif
}

// puts �Ɠ��������ŉ�ʂɕ������\�����邽�߂̊֐�
extern int NS_putsDxWithStrLen( const TCHAR *String, size_t StringLength, int NewLine )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( String, StringLength, return -1 )
	Result = putsDx_WCHAR_T( UseStringBuffer, NewLine ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( String )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( String, StringLength, return -1 )
	Result = putsDx_WCHAR_T( UseStringBuffer, NewLine ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( String )
#endif
	return Result ;
}

// puts �Ɠ��������ŉ�ʂɕ������\�����邽�߂̊֐�
extern int putsDx_WCHAR_T( const wchar_t *String , int NewLine )
{
	int Result ;

	// ���O�o�̓t���O�𗧂Ă�
	LogData.LogDrawFlag = TRUE ;

	// ���O�o�͊֐����Ă�
	Result = AddLog( String ) ;
	if( Result < 0 )
	{
		return -1 ;
	}

	// ���s��ǉ�
	if( NewLine )
	{
		Result = AddLog( L"\n" ) ;
	}

	// �I��
	return Result ;
}

// �ȈՉ�ʏo�͂��N���A����
extern int NS_clsDx( void )
{
	// ���O������
	ClrLog() ;

	// ���O�o�̓t���O��|��
	LogData.LogDrawFlag = FALSE ;

	// �I��
	return 0 ;
}

// printf �� puts �ŕ\�����镶����̐F���w�肷��
extern int NS_setPrintColorDx( int Color, int EdgeColor )
{
	// �F����ۑ�����
	LogData.LogCharColorEnable = TRUE ;
	LogData.LogCharColor[ 0 ] = Color ;
	LogData.LogCharColor[ 1 ] = EdgeColor ;

	// �I��
	return 0 ;
}

#endif // DX_NON_PRINTF_DX


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_LOG

