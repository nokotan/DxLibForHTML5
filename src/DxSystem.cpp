// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�V�X�e���v���O����
// 
// 				Ver 3.24d
// 
// -------------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

// �C���N���[�h ------------------------------------------------------------------
#include "DxSystem.h"
#include "DxMemory.h"
#include "DxBaseFunc.h"
#include "DxLog.h"
#include "DxUseCLib.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

DXSYSTEMDATA DxSysData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �v���O���� --------------------------------------------------------------------

// �������E�I���֌W

// DxSysData �֌W�̏��������s��
extern int DxLib_SysInit( void )
{
	// �I�����N�G�X�g�̃t���O��|��
	DxSysData.EndRequestFlag = FALSE ;

	// �I��
	return 0 ;
}

// �I�����N�G�X�g���s��
extern int DxLib_EndRequest( void )
{
	DxSysData.EndRequestFlag = TRUE ;

	// �I��
	return 0 ;
}

// �I�����N�G�X�g�̏�Ԃ��擾����
extern int DxLib_GetEndRequest( void )
{
	return DxSysData.EndRequestFlag ;
}







// ���C�u����������������Ă��邩�ǂ������擾����( �߂�l: TRUE=����������Ă���  FALSE=����Ă��Ȃ� )
extern int NS_DxLib_IsInit( void )
{
	return DxSysData.DxLib_InitializeFlag ;
}






// �G���[�����֐�

// �Ō�ɔ��������G���[�̃G���[�R�[�h���擾����( �߂�l�@0:�G���[���������Ă��Ȃ��A���̓G���[�R�[�h�o�͂ɑΉ������G���[���������Ă��Ȃ��@�@0�ȊO�F�G���[�R�[�h�ADX_ERRORCODE_WIN_DESKTOP_24BIT_COLOR �Ȃ� )
extern int NS_GetLastErrorCode( void )
{
	return DxSysData.LastErrorCode ;
}

// �Ō�ɔ��������G���[�̃G���[���b�Z�[�W���w��̕�����o�b�t�@�Ɏ擾����
extern int NS_GetLastErrorMessage( TCHAR *StringBuffer, int StringBufferBytes )
{
	ConvString( ( char * )DxSysData.LastErrorMessage, -1, WCHAR_T_CHARCODEFORMAT, ( char * )StringBuffer, StringBufferBytes, _TCHARCODEFORMAT ) ;

	return 0 ;
}

// �G���[�R�[�h�E���b�Z�[�W��ݒ肷��
extern int DxLib_SetLastError( int ErrorCode/* DX_ERRORCODE_WIN_24BIT_COLOR �Ȃ� */, const wchar_t *ErrorMessage )
{
	DxSysData.LastErrorCode = ErrorCode ;

	if( ErrorMessage == NULL )
	{
		DxSysData.LastErrorMessage[ 0 ] = L'\0' ;
	}
	else
	{
		CL_strcpy_s( WCHAR_T_CHARCODEFORMAT, ( char * )DxSysData.LastErrorMessage, sizeof( DxSysData.LastErrorMessage ), ( char * )ErrorMessage ) ;
	}

	return 0 ;
}

// �����t�����C�u�����̃G���[�������s��
extern int DxLib_FmtError( const wchar_t *FormatString , ... )
{
	va_list VaList ;
	wchar_t String[ 1024 ];

	// ���O�o�͗p�̃��X�g���Z�b�g����
	va_start( VaList , FormatString ) ;

	// �ҏW��̕�������擾����
	_VSWNPRINTF( String , sizeof( String ) / 2, FormatString , VaList ) ;

	// �ϒ����X�g�̃|�C���^�����Z�b�g����
	va_end( VaList ) ;

	// �G���[�����ɂ܂킷
	return DxLib_Error( String ) ;
}

// �����t�����C�u�����̃G���[�������s��
extern int DxLib_FmtErrorUTF16LE( const char *FormatString , ... )
{
	va_list VaList ;
	char String[ 2048 ];

	// ���O�o�͗p�̃��X�g���Z�b�g����
	va_start( VaList , FormatString ) ;

	// �ҏW��̕�������擾����
	CL_vsnprintf( DX_CHARCODEFORMAT_UTF16LE, TRUE, CHAR_CHARCODEFORMAT, WCHAR_T_CHARCODEFORMAT, String, sizeof( String ) / 2, FormatString, VaList ) ;

	// �ϒ����X�g�̃|�C���^�����Z�b�g����
	va_end( VaList ) ;

	// �G���[�����ɂ܂킷
	return DxLib_ErrorUTF16LE( String ) ;
}

















// �N���b�v�{�[�h�֌W

// �N���b�v�{�[�h�Ɋi�[����Ă���e�L�X�g�f�[�^��ǂݏo���A-1 �̏ꍇ�̓N���b�v�{�[�h�Ƀe�L�X�g�f�[�^�͖����Ƃ�������( DestBuffer �� NULL ��n���Ɗi�[�ɕK�v�ȃf�[�^�T�C�Y���Ԃ��Ă��� )
extern int NS_GetClipboardText( TCHAR *DestBuffer, int DestBufferBytes )
{
	return GetClipboardText_PF( DestBuffer, DestBufferBytes ) ;
}

// �N���b�v�{�[�h�Ɋi�[����Ă���e�L�X�g�f�[�^��ǂݏo���A-1 �̏ꍇ�̓N���b�v�{�[�h�Ƀe�L�X�g�f�[�^�͖����Ƃ�������( DestBuffer �� NULL ��n���Ɗi�[�ɕK�v�ȃf�[�^�T�C�Y���Ԃ��Ă��� )
extern int GetClipboardText_WCHAR_T( wchar_t *DestBuffer, int DestBufferBytes )
{
	return GetClipboardText_WCHAR_T_PF( DestBuffer, DestBufferBytes ) ;
}

// �N���b�v�{�[�h�Ƀe�L�X�g�f�[�^���i�[����
extern int NS_SetClipboardText( const TCHAR *Text )
{
#ifdef UNICODE
	return SetClipboardText_WCHAR_T_PF( Text ) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( Text, return -1 )

	Result = SetClipboardText_WCHAR_T_PF( UseTextBuffer ) ;

	TCHAR_TO_WCHAR_T_STRING_END( Text )

	return Result ;
#endif
}

// �N���b�v�{�[�h�Ƀe�L�X�g�f�[�^���i�[����
extern int SetClipboardText_WCHAR_T( const wchar_t *Text )
{
	return SetClipboardText_WCHAR_T_PF( Text ) ;
}

// �N���b�v�{�[�h�Ƀe�L�X�g�f�[�^���i�[����
extern int NS_SetClipboardTextWithStrLen( const TCHAR *Text, size_t TextLength )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( Text, TextLength, return -1 )
	Result = SetClipboardText_WCHAR_T( UseTextBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( Text )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( Text, TextLength, return -1 )
	Result = SetClipboardText_WCHAR_T( UseTextBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( Text )
#endif
	return Result ;
}

// �N���b�v�{�[�h�Ƀe�L�X�g�f�[�^���i�[����
extern int SetClipboardTextWithStrLen_WCHAR_T( const wchar_t *Text, size_t TextLength )
{
	int Result ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( Text, TextLength, return -1 )
	Result = SetClipboardText_WCHAR_T( UseTextBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( Text )
	return Result ;
}


























// ini�t�@�C���֌W

// GetPrivateProfileString �̂c�w���C�u������
struct GetPrivateProfileStringDxInfo
{
	BYTE		*FileBuffer ;
	size_t		FileSize ;
	DWORD		FileAddr ;
	DWORD		Semicolon ;
	DWORD		BracketL ;
	DWORD		BracketR ;
	DWORD		Equal ;
	DWORD		Space ;
	DWORD		Tab ;
	DWORD		CR ;
	DWORD		LF ;
	int			IniFileCharCodeFormat ;
	DWORD		UnitBytes ;
	TCHAR		*ReturnedStringBuffer ;
	size_t		ReturnedStringBufferBytes ;
	DWORD		DestBytes ;
} ;

__inline DWORD GetPrivateProfileStringDx_NextChar( GetPrivateProfileStringDxInfo &Info, int *pCharBytes, int EnableSemicolon, int LFEnd )
{
	*pCharBytes = 0 ;
	while( Info.FileAddr < Info.FileSize )
	{
		DWORD CharCode ;
		int CharBytes ;

		CharCode = GetCharCode( ( char * )( Info.FileBuffer + Info.FileAddr ), Info.IniFileCharCodeFormat, &CharBytes ) ;
		if( CharCode == Info.LF && LFEnd )
		{
			return 0 ;
		}
		else
		if( CharCode == Info.Space || CharCode == Info.Tab || CharCode == Info.CR || CharCode == Info.LF )
		{
			Info.FileAddr += CharBytes ;
		}
		else
		if( CharCode == Info.Semicolon && EnableSemicolon )
		{
			Info.FileAddr += CharBytes ;
			while( Info.FileAddr < Info.FileSize )
			{
				CharCode = GetCharCode( ( char * )( Info.FileBuffer + Info.FileAddr ), Info.IniFileCharCodeFormat, &CharBytes ) ;
				Info.FileAddr += CharBytes ;
				if( CharCode == Info.LF )
				{
					if( LFEnd )
					{
						return 0 ;
					}
					break ;
				}
			}
		}
		else
		{
			*pCharBytes = CharBytes ;
			return CharCode ;
		}
	}

	return 0 ;
}

__inline void GetPrivateProfileStringDx_NextLine( GetPrivateProfileStringDxInfo &Info )
{
	while( Info.FileAddr < Info.FileSize )
	{
		DWORD CharCode ;
		int CharBytes ;

		CharCode = GetCharCode( ( char * )( Info.FileBuffer + Info.FileAddr ), Info.IniFileCharCodeFormat, &CharBytes ) ;
		Info.FileAddr += CharBytes ;
		if( CharCode == Info.LF )
		{
			return ;
		}
	}
}

__inline DWORD GetPrivateProfileStringDx_GetName( GetPrivateProfileStringDxInfo &Info, DWORD &NameBytes, int *pCharBytes, int EqualEnd )
{
	NameBytes = 0 ;
	while( Info.FileAddr + NameBytes < Info.FileSize )
	{
		DWORD CharCode ;
		int CharBytes ;

		CharCode = GetCharCode( ( char * )( Info.FileBuffer + Info.FileAddr + NameBytes ), Info.IniFileCharCodeFormat, &CharBytes ) ;
		if( ( EqualEnd && CharCode == Info.Equal ) ||
			CharCode == Info.Space    ||
			CharCode == Info.Tab      ||
			CharCode == Info.CR       ||
			CharCode == Info.LF       ||
			CharCode == Info.BracketR )
		{
			*pCharBytes = CharBytes ;
			return CharCode ;
		}
		else
		{
			NameBytes++ ;
		}
	}

	return 0 ;
}


__inline void GetPrivateProfileStringDx_PutString( GetPrivateProfileStringDxInfo &Info, const TCHAR *PutString, DWORD PutBytes )
{
	int i, j ;
	DWORD CharCode ;
	int CharBytes = 0 ;
	int PutCharBytes ;
	char CharString[ 18 ] ;
	int PutCharCodeFormat = _TCHARCODEFORMAT ;

	for( i = 0 ; ( DWORD )i < PutBytes ; i += CharBytes )
	{
		CharCode = GetCharCode( ( char * )( ( BYTE * )PutString + i ), Info.IniFileCharCodeFormat, &CharBytes ) ;
		PutCharBytes = PutCharCode( ConvCharCode( CharCode, Info.IniFileCharCodeFormat, PutCharCodeFormat ), PutCharCodeFormat, CharString, sizeof( CharString ) ) ;

		for( j = 0 ; j < PutCharBytes ; j += Info.UnitBytes )
		{
			if( Info.ReturnedStringBufferBytes < Info.DestBytes + Info.UnitBytes )
			{
				return ;
			}

			switch( Info.UnitBytes )
			{
			case 1 : *( ( BYTE  * )( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes ) ) = ( ( BYTE  * )CharString )[ j ] ; break ;
			case 2 : *( ( WORD  * )( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes ) ) = ( ( WORD  * )CharString )[ j ] ; break ;
			case 4 : *( ( DWORD * )( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes ) ) = ( ( DWORD * )CharString )[ j ] ; break ;
			}
			Info.DestBytes += Info.UnitBytes ;
		}
	}
}

extern int NS_GetPrivateProfileStringDx( const TCHAR *AppName, const TCHAR *KeyName, const TCHAR *Default, TCHAR *ReturnedStringBuffer, size_t ReturnedStringBufferBytes, const TCHAR *IniFilePath, int IniFileCharCodeFormat )
{
	int Return = -1 ;
	void *IniFileImage = NULL ;
	size_t IniFileImageBytes = 0 ;
	DWORD_PTR fp = 0 ;
	TCHAR_TO_WCHAR_T_STRING_BEGIN( IniFilePath )
	TCHAR_TO_WCHAR_T_STRING_SETUP( IniFilePath, goto END )

	// �t�@�C�����ۂ��Ɠǂݍ���
	{
		fp = DX_FOPEN( UseIniFilePathBuffer ) ;
		if( fp == 0 )
		{
			goto END ;
		}
		DX_FSEEK( fp, 0, SEEK_END ) ;
		IniFileImageBytes = ( size_t )DX_FTELL( fp ) ;
		DX_FSEEK( fp, 0, SEEK_SET ) ;
		IniFileImage = DXALLOC( IniFileImageBytes ) ;
		if( IniFileImage == NULL )
		{
			goto END ;
		}
		DX_FREAD( IniFileImage, IniFileImageBytes, 1, fp ) ;
		DX_FCLOSE( fp ) ;
		fp = 0 ;
	}

	Return = NS_GetPrivateProfileStringDxForMem( AppName, KeyName, Default, ReturnedStringBuffer, ReturnedStringBufferBytes, IniFileImage, IniFileImageBytes, IniFileCharCodeFormat ) ;

END :

	TCHAR_TO_WCHAR_T_STRING_END( IniFilePath )

	if( fp != 0 )
	{
		DX_FCLOSE( fp ) ;
		fp = 0 ;
	}

	if( IniFileImage != NULL )
	{
		DXFREE( IniFileImage ) ;
		IniFileImage = NULL ;
	}

	return Return ;
}

// GetPrivateProfileString �̂c�w���C�u������
extern int NS_GetPrivateProfileStringDxWithStrLen( const TCHAR *AppName, size_t AppNameLength, const TCHAR *KeyName, size_t KeyNameLength, const TCHAR *Default, size_t DefaultLength, TCHAR *ReturnedString, size_t ReturnedStringBufferBytes, const TCHAR *IniFilePath, size_t IniFilePathLength, int IniFileCharCodeFormat )
{
	int Result = -1 ;

	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( AppName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( KeyName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( Default     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( IniFilePath )

	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( AppName,     AppNameLength,     goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( KeyName,     KeyNameLength,     goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( Default,     DefaultLength,     goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( IniFilePath, IniFilePathLength, goto ERR )

	Result = NS_GetPrivateProfileStringDx( AppNameBuffer, KeyNameBuffer, Default, ReturnedString, ReturnedStringBufferBytes, IniFilePathBuffer, IniFileCharCodeFormat ) ;

ERR :
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( AppName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( KeyName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( Default     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( IniFilePath )

	return Result ;
}

// GetPrivateProfileInt �̂c�w���C�u������
extern int NS_GetPrivateProfileIntDx( const TCHAR *AppName, const TCHAR *KeyName, int Default, const TCHAR *IniFilePath, int IniFileCharCodeFormat )
{
	TCHAR TempString[ 2048 ] ;
	int Size ;

	if( AppName == NULL || KeyName == NULL )
	{
		return Default ;
	}

	Size = NS_GetPrivateProfileStringDx( AppName, KeyName, NULL, TempString, sizeof( TempString ), IniFilePath, IniFileCharCodeFormat ) ;
	if( Size <= 0 )
	{
		return Default ;
	}

	return CL_atoi( _TCHARCODEFORMAT, ( char * )TempString ) ;
}

// GetPrivateProfileInt �̂c�w���C�u������
extern int NS_GetPrivateProfileIntDxWithStrLen( const TCHAR *AppName, size_t AppNameLength, const TCHAR *KeyName, size_t KeyNameLength, int Default, const TCHAR *IniFilePath, size_t IniFilePathLength, int IniFileCharCodeFormat )
{
	int Result = -1 ;

	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( AppName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( KeyName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( IniFilePath )

	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( AppName,     AppNameLength,     goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( KeyName,     KeyNameLength,     goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( IniFilePath, IniFilePathLength, goto ERR )

	Result = NS_GetPrivateProfileIntDx( AppNameBuffer, KeyNameBuffer, Default, IniFilePathBuffer, IniFileCharCodeFormat ) ;

ERR :
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( AppName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( KeyName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( IniFilePath )

	return Result ;
}

// GetPrivateProfileStringDx �̃���������ǂݍ��ޔ�
extern int NS_GetPrivateProfileStringDxForMem( const TCHAR *AppName, const TCHAR *KeyName, const TCHAR *Default, TCHAR *ReturnedStringBuffer, size_t ReturnedStringBufferBytes, const void *IniFileImage, size_t IniFileImageBytes, int IniFileCharCodeFormat )
{
	int Return = -1 ;
	DWORD CharCode ;
	int CharBytes ;
	DWORD NameBytes ;
	GetPrivateProfileStringDxInfo Info = { NULL, 0, 0 } ;
	DWORD AppNameBytes = 0 ;
	DWORD KeyNameBytes = 0 ;
	TCHAR_TO_CHAR_STRING_BEGIN( AppName )
	TCHAR_TO_CHAR_STRING_BEGIN( KeyName )
	TCHAR_TO_CHAR_STRING_BEGIN( Default )

	Info.FileSize = IniFileImageBytes ;
	Info.FileBuffer = ( BYTE * )IniFileImage ;

	// �t�@�C���̕����R�[�h���`�F�b�N
	{
		if( IniFileCharCodeFormat < 0 )
		{
			IniFileCharCodeFormat = _TCHARCODEFORMAT ;
		}

		if( Info.FileSize >= 3 )
		{
			if( Info.FileBuffer[ 0 ] == 0xef && Info.FileBuffer[ 1 ] == 0xbb && Info.FileBuffer[ 2 ] == 0xbf )
			{
				IniFileCharCodeFormat = DX_CHARCODEFORMAT_UTF8 ;
				Info.FileAddr = 3 ;
			}
		}
		else
		if( Info.FileSize >= 2 )
		{
			if( Info.FileBuffer[ 0 ] == 0xff && Info.FileBuffer[ 1 ] == 0xfe )
			{
				IniFileCharCodeFormat = DX_CHARCODEFORMAT_UTF16LE ;
				Info.FileAddr = 2 ;
			}
			else
			if( Info.FileBuffer[ 0 ] == 0xfe && Info.FileBuffer[ 1 ] == 0xff )
			{
				IniFileCharCodeFormat = DX_CHARCODEFORMAT_UTF16BE ;
				Info.FileAddr = 2 ;
			}
		}
		Info.IniFileCharCodeFormat = IniFileCharCodeFormat ;
	}

	// �ꕶ���ӂ�̃o�C�g������
	Info.UnitBytes = GetCharCodeFormatUnitSize( _TCHARCODEFORMAT ) ;

	// �o�͐��������
	Info.ReturnedStringBuffer = ReturnedStringBuffer ;
	Info.ReturnedStringBufferBytes = ReturnedStringBufferBytes ;
	Info.DestBytes = 0 ;

	// �t�@�C���t�H�[�}�b�g�ɍ�����������̏���
	TCHAR_TO_CHAR_STRING_SETUP( AppName, goto END, IniFileCharCodeFormat )
	TCHAR_TO_CHAR_STRING_SETUP( KeyName, goto END, IniFileCharCodeFormat )
	TCHAR_TO_CHAR_STRING_SETUP( Default, goto END, IniFileCharCodeFormat )
	Info.Semicolon = ConvCharCode( GetCharCode( ";",  DX_CHARCODEFORMAT_ASCII, NULL ), DX_CHARCODEFORMAT_ASCII, IniFileCharCodeFormat ) ;
	Info.BracketL  = ConvCharCode( GetCharCode( "[",  DX_CHARCODEFORMAT_ASCII, NULL ), DX_CHARCODEFORMAT_ASCII, IniFileCharCodeFormat ) ;
	Info.BracketR  = ConvCharCode( GetCharCode( "]",  DX_CHARCODEFORMAT_ASCII, NULL ), DX_CHARCODEFORMAT_ASCII, IniFileCharCodeFormat ) ;
	Info.Equal     = ConvCharCode( GetCharCode( "=",  DX_CHARCODEFORMAT_ASCII, NULL ), DX_CHARCODEFORMAT_ASCII, IniFileCharCodeFormat ) ;
	Info.Space     = ConvCharCode( GetCharCode( " ",  DX_CHARCODEFORMAT_ASCII, NULL ), DX_CHARCODEFORMAT_ASCII, IniFileCharCodeFormat ) ;
	Info.Tab       = ConvCharCode( GetCharCode( "\t", DX_CHARCODEFORMAT_ASCII, NULL ), DX_CHARCODEFORMAT_ASCII, IniFileCharCodeFormat ) ;
	Info.CR        = ConvCharCode( GetCharCode( "\r", DX_CHARCODEFORMAT_ASCII, NULL ), DX_CHARCODEFORMAT_ASCII, IniFileCharCodeFormat ) ;
	Info.LF        = ConvCharCode( GetCharCode( "\n", DX_CHARCODEFORMAT_ASCII, NULL ), DX_CHARCODEFORMAT_ASCII, IniFileCharCodeFormat ) ;

	// �Z�N�V�����ƃL�[�̃o�C�g�����Z�o
	if( AppName != NULL )
	{
		AppNameBytes = ( DWORD )CL_strlen( IniFileCharCodeFormat, ( char * )UseAppNameBuffer ) * GetCharCodeFormatUnitSize( IniFileCharCodeFormat ) ;
	}
	if( KeyName != NULL )
	{
		KeyNameBytes = ( DWORD )CL_strlen( IniFileCharCodeFormat, ( char * )UseKeyNameBuffer ) * GetCharCodeFormatUnitSize( IniFileCharCodeFormat ) ;
	}

	// �Z�N�V�����̃��X�g�A�b�v�̏ꍇ
	if( AppName == NULL )
	{
		if( Info.ReturnedStringBufferBytes < Info.UnitBytes * 2 )
		{
			Return = 0 ;
			goto END ;
		}

		while( Info.FileAddr < Info.FileSize )
		{
			CharCode = GetPrivateProfileStringDx_NextChar( Info, &CharBytes, TRUE, FALSE ) ;
			if( Info.FileAddr >= Info.FileSize )
			{
				break ;
			}

			// �劇�ʂ�������Z�N�V����
			if( CharCode == Info.BracketL )
			{
				Info.FileAddr += ( DWORD )CharBytes ;

				CharCode = GetPrivateProfileStringDx_NextChar( Info, &CharBytes, FALSE, TRUE ) ;
				if( Info.FileAddr >= Info.FileSize )
				{
					break ;
				}

				if( CharBytes > 0 )
				{
					GetPrivateProfileStringDx_GetName( Info, NameBytes, &CharBytes, FALSE ) ;
					if( NameBytes > 0 )
					{
						GetPrivateProfileStringDx_PutString( Info, ( TCHAR * )( Info.FileBuffer + Info.FileAddr ), NameBytes ) ;
						Info.FileAddr += NameBytes ;
						if( Info.DestBytes + Info.UnitBytes * 2 >= Info.ReturnedStringBufferBytes )
						{
							_MEMSET( Info.ReturnedStringBuffer + Info.ReturnedStringBufferBytes - Info.UnitBytes * 2, 0, Info.UnitBytes * 2 ) ;
							Return = ( int )( Info.ReturnedStringBufferBytes - Info.UnitBytes * 2 ) ;
							goto END ;
						}
						_MEMSET( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes, 0, Info.UnitBytes ) ;
						Info.DestBytes += Info.UnitBytes ;
						if( Info.DestBytes + Info.UnitBytes * 3 > Info.ReturnedStringBufferBytes )
						{
							_MEMSET( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes, 0, Info.UnitBytes ) ;
							Return = ( int )Info.ReturnedStringBufferBytes ;
							goto END ;
						}
					}
				}
			}

			// ���̍s�ֈړ�
			GetPrivateProfileStringDx_NextLine( Info ) ;
		}
		_MEMSET( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes, 0, Info.UnitBytes ) ;
		Return = ( int )( Info.DestBytes / Info.UnitBytes ) ;
	}
	else
	{
		// �Z�N�V�����̌���
		while( Info.FileAddr < Info.FileSize )
		{
			CharCode = GetPrivateProfileStringDx_NextChar( Info, &CharBytes, TRUE, FALSE ) ;
			if( Info.FileAddr >= Info.FileSize )
			{
				goto DEFAULT_END ;
			}

			if( CharCode == Info.BracketL )
			{
				Info.FileAddr += ( DWORD )CharBytes ;

				CharCode = GetPrivateProfileStringDx_NextChar( Info, &CharBytes, FALSE, TRUE ) ;
				if( Info.FileAddr >= Info.FileSize )
				{
					goto DEFAULT_END ;
				}

				if( CharBytes > 0 )
				{
					CharCode = GetPrivateProfileStringDx_GetName( Info, NameBytes, &CharBytes, FALSE ) ;
					if( AppNameBytes == NameBytes && _MEMCMP( Info.FileBuffer + Info.FileAddr, UseAppNameBuffer, NameBytes ) == 0 )
					{
						break ;
					}
					Info.FileAddr += NameBytes ;
				}
			}

			// ���̍s�ֈړ�
			GetPrivateProfileStringDx_NextLine( Info ) ;
		}
		if( Info.FileAddr >= Info.FileSize )
		{
			goto DEFAULT_END ;
		}
		GetPrivateProfileStringDx_NextLine( Info ) ;

		// �L�[�̃��X�g�A�b�v�̏ꍇ
		if( KeyName == NULL )
		{
			if( Info.ReturnedStringBufferBytes < Info.UnitBytes * 2 )
			{
				Return = 0 ;
				goto END ;
			}

			while( Info.FileAddr < Info.FileSize )
			{
				CharCode = GetPrivateProfileStringDx_NextChar( Info, &CharBytes, TRUE, FALSE ) ;
				if( Info.FileAddr >= Info.FileSize || CharCode == Info.BracketL )
				{
					break ;
				}

				GetPrivateProfileStringDx_GetName( Info, NameBytes, &CharBytes, TRUE ) ;
				if( NameBytes > 0 )
				{
					BYTE *Addr = Info.FileBuffer + Info.FileAddr ;
					Info.FileAddr += NameBytes ;

					// ���̕����� = ���ǂ������m�F
					CharCode = GetPrivateProfileStringDx_NextChar( Info, &CharBytes, TRUE, TRUE ) ;
					if( Info.FileAddr < Info.FileSize && CharCode == Info.Equal )
					{
						Info.FileAddr += CharBytes ;

						GetPrivateProfileStringDx_PutString( Info, ( TCHAR * )Addr, NameBytes ) ;
						if( Info.DestBytes + Info.UnitBytes * 2 > Info.ReturnedStringBufferBytes )
						{
							_MEMSET( Info.ReturnedStringBuffer + Info.ReturnedStringBufferBytes - Info.UnitBytes * 2, 0, Info.UnitBytes * 2 ) ;
							Return = ( int )( Info.ReturnedStringBufferBytes / Info.UnitBytes - 2 ) ;
							goto END ;
						}
						_MEMSET( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes, 0, Info.UnitBytes ) ;
						Info.DestBytes += Info.UnitBytes ;
						if( Info.DestBytes + Info.UnitBytes * 3 > Info.ReturnedStringBufferBytes )
						{
							_MEMSET( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes, 0, Info.UnitBytes ) ;
							Return = ( int )( Info.ReturnedStringBufferBytes / Info.UnitBytes ) - 1 ;
							goto END ;
						}
					}
				}

				// ���̍s�ֈړ�
				GetPrivateProfileStringDx_NextLine( Info ) ;
			}
			_MEMSET( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes, 0, Info.UnitBytes ) ;
			Return = ( int )( Info.DestBytes / Info.UnitBytes ) ;
		}
		else
		// �L�[�̎擾�̏ꍇ
		{
			if( Info.ReturnedStringBufferBytes <= Info.UnitBytes )
			{
				if( Info.ReturnedStringBufferBytes == Info.UnitBytes )
				{
					_MEMSET( Info.ReturnedStringBuffer, 0, Info.ReturnedStringBufferBytes ) ;
				}

				Return = 0 ;
				goto END ;
			}

			// �L�[�̌���
			while( Info.FileAddr < Info.FileSize )
			{
				CharCode = GetPrivateProfileStringDx_NextChar( Info, &CharBytes, TRUE, FALSE ) ;
				if( Info.FileAddr >= Info.FileSize || CharCode == Info.BracketL )
				{
					goto DEFAULT_END ;
				}

				CharCode = GetPrivateProfileStringDx_GetName( Info, NameBytes, &CharBytes, TRUE ) ;
				if( KeyNameBytes == NameBytes && _MEMCMP( Info.FileBuffer + Info.FileAddr, UseKeyNameBuffer, NameBytes ) == 0 )
				{
					Info.FileAddr += NameBytes ;
					break ;
				}
				Info.FileAddr += NameBytes ;

				// ���̍s�ֈړ�
				GetPrivateProfileStringDx_NextLine( Info ) ;
			}
			if( Info.FileAddr >= Info.FileSize )
			{
				goto DEFAULT_END ;
			}

			// ���̕����� = ���ǂ������m�F
			CharCode = GetPrivateProfileStringDx_NextChar( Info, &CharBytes, TRUE, TRUE ) ;
			if( Info.FileAddr >= Info.FileSize || CharCode != Info.Equal )
			{
				goto DEFAULT_END ;
			}
			Info.FileAddr += CharBytes ;

			// ������̎擾
			CharCode = GetPrivateProfileStringDx_NextChar( Info, &CharBytes, FALSE, TRUE ) ;
			if( CharCode == 0 )
			{
				Return = 0 ;
				_MEMSET( Info.ReturnedStringBuffer, 0, Info.UnitBytes ) ;
			}
			else
			{
				NameBytes = 0 ;
				while( Info.FileAddr + NameBytes < Info.FileSize )
				{
					CharCode = GetCharCode( ( char * )( Info.FileBuffer + Info.FileAddr + NameBytes ), Info.IniFileCharCodeFormat, &CharBytes ) ;
					if( CharCode == Info.CR || CharCode == Info.LF )
					{
						break ;
					}
					NameBytes += CharBytes ;
				}
				if( NameBytes == 0 )
				{
					Return = 0 ;
					_MEMSET( Info.ReturnedStringBuffer, 0, Info.UnitBytes ) ;
				}
				else
				{
					GetPrivateProfileStringDx_PutString( Info, ( TCHAR * )( Info.FileBuffer + Info.FileAddr ), NameBytes ) ;
					if( Info.DestBytes > Info.ReturnedStringBufferBytes - Info.UnitBytes )
					{
						Info.DestBytes = ( DWORD )( Info.ReturnedStringBufferBytes - Info.UnitBytes ) ;
					}
					_MEMSET( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes, 0, Info.UnitBytes ) ;
					Return = ( int )( Info.DestBytes / Info.UnitBytes ) ;
				}
			}
		}
	}

END :

	TCHAR_TO_CHAR_STRING_END( AppName )
	TCHAR_TO_CHAR_STRING_END( KeyName )
	TCHAR_TO_CHAR_STRING_END( Default )

	return Return ;

DEFAULT_END :
	if( Default != NULL )
	{
		GetPrivateProfileStringDx_PutString( Info, ( TCHAR * )UseDefaultBuffer, ( DWORD )CL_strlen( IniFileCharCodeFormat, ( char * )UseDefaultBuffer ) * GetCharCodeFormatUnitSize( IniFileCharCodeFormat ) ) ;
		if( Info.DestBytes > Info.ReturnedStringBufferBytes - Info.UnitBytes )
		{
			Info.DestBytes = ( DWORD )( Info.ReturnedStringBufferBytes - Info.UnitBytes ) ;
		}
	}
	_MEMSET( ( BYTE * )Info.ReturnedStringBuffer + Info.DestBytes, 0, Info.UnitBytes ) ;
	Return = ( int )( Info.DestBytes / Info.UnitBytes ) ;
	goto END ;
}

// GetPrivateProfileStringDx �̃���������ǂݍ��ޔ�
extern int NS_GetPrivateProfileStringDxForMemWithStrLen( const TCHAR *AppName, size_t AppNameLength, const TCHAR *KeyName, size_t KeyNameLength, const TCHAR *Default, size_t DefaultLength, TCHAR *ReturnedString, size_t ReturnedStringBufferBytes, const void *IniFileImage, size_t IniFileImageBytes, int IniFileCharCodeFormat )
{
	int Result = -1 ;

	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( AppName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( KeyName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( Default     )

	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( AppName,     AppNameLength,     goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( KeyName,     KeyNameLength,     goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( Default,     DefaultLength,     goto ERR )

	Result = NS_GetPrivateProfileStringDxForMem( AppNameBuffer, KeyNameBuffer, Default, ReturnedString, ReturnedStringBufferBytes, IniFileImage, IniFileImageBytes, IniFileCharCodeFormat ) ;

ERR :
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( AppName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( KeyName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( Default     )

	return Result ;
}

// GetPrivateProfileIntDx �̃���������ǂݍ��ޔ�
extern int NS_GetPrivateProfileIntDxForMem( const TCHAR *AppName, const TCHAR *KeyName, int Default, const void *IniFileImage, size_t IniFileImageBytes, int IniFileCharCodeFormat )
{
	TCHAR TempString[ 2048 ] ;
	int Size ;

	if( AppName == NULL || KeyName == NULL )
	{
		return Default ;
	}

	Size = NS_GetPrivateProfileStringDxForMem( AppName, KeyName, NULL, TempString, sizeof( TempString ), IniFileImage, IniFileImageBytes, IniFileCharCodeFormat ) ;
	if( Size <= 0 )
	{
		return Default ;
	}

	return CL_atoi( _TCHARCODEFORMAT, ( char * )TempString ) ;
}

// GetPrivateProfileIntDx �̃���������ǂݍ��ޔ�
extern int NS_GetPrivateProfileIntDxForMemWithStrLen( const TCHAR *AppName, size_t AppNameLength, const TCHAR *KeyName, size_t KeyNameLength, int Default, const void *IniFileImage, size_t IniFileImageBytes, int IniFileCharCodeFormat )
{
	int Result = -1 ;

	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( AppName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( KeyName     )

	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( AppName,     AppNameLength,     goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( KeyName,     KeyNameLength,     goto ERR )

	Result = NS_GetPrivateProfileIntDxForMem( AppNameBuffer, KeyNameBuffer, Default, IniFileImage, IniFileImageBytes, IniFileCharCodeFormat ) ;

ERR :
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( AppName     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( KeyName     )

	return Result ;
}

















#if defined( __APPLE__ ) || defined( __ANDROID__ )



// ���[���A�v���𑗐M���[���ҏW��ԂŋN������
// MailAddr    : ����( NULL �Ŗ��� )�A���[���A�h���X����������ꍇ�̓J���}�w,�x�ŋ�؂��Ă�������
// MainCCAddr  : CC �̈���( NULL �Ŗ��� )�A���[���A�h���X����������ꍇ�̓J���}�w,�x�ŋ�؂��Ă�������
// MainBCCAddr : BCC �̈���( NULL �Ŗ��� )�A���[���A�h���X����������ꍇ�̓J���}�w,�x�ŋ�؂��Ă�������
// Subject     : �^�C�g��( NULL �Ŗ��� )�A���[���A�h���X����������ꍇ�̓J���}�w,�x�ŋ�؂��Ă�������
// Text        : �{��( NULL �Ŗ��� )�A���[���A�h���X����������ꍇ�̓J���}�w,�x�ŋ�؂��Ă�������
extern int MailApp_Send_WCHAR_T( const wchar_t *MailAddr, const wchar_t *MailCCAddr, const wchar_t *MailBCCAddr, const wchar_t *Subject, const wchar_t *Text )
{
	// ���ˑ��֐����Ă�
	return MailApp_Send_WCHAR_T_PF( MailAddr, MailCCAddr, MailBCCAddr, Subject, Text ) ;
}

extern int MailApp_Send( const TCHAR *MailAddr, const TCHAR *MailCCAddr, const TCHAR *MailBCCAddr, const TCHAR *Subject, const TCHAR *Text )
{
#ifdef UNICODE
	return MailApp_Send_WCHAR_T( MailAddr, MailCCAddr, MailBCCAddr, Subject, Text ) ;
#else
	int Result = -1 ;
	CHAR_TO_WCHAR_T_STRING_BEGIN( MailAddr    )
	CHAR_TO_WCHAR_T_STRING_BEGIN( MailCCAddr  )
	CHAR_TO_WCHAR_T_STRING_BEGIN( MailBCCAddr )
	CHAR_TO_WCHAR_T_STRING_BEGIN( Subject     )
	CHAR_TO_WCHAR_T_STRING_BEGIN( Text        )
	CHAR_TO_WCHAR_T_STRING_SETUP( MailAddr,    goto END, _TCHARCODEFORMAT )
	CHAR_TO_WCHAR_T_STRING_SETUP( MailCCAddr,  goto END, _TCHARCODEFORMAT )
	CHAR_TO_WCHAR_T_STRING_SETUP( MailBCCAddr, goto END, _TCHARCODEFORMAT )
	CHAR_TO_WCHAR_T_STRING_SETUP( Subject,     goto END, _TCHARCODEFORMAT )
	CHAR_TO_WCHAR_T_STRING_SETUP( Text,        goto END, _TCHARCODEFORMAT )

	Result = MailApp_Send_WCHAR_T( UseMailAddrBuffer, UseMailCCAddrBuffer, UseMailBCCAddrBuffer, UseSubjectBuffer, UseTextBuffer ) ;

END :
	TCHAR_TO_WCHAR_T_STRING_END( MailAddr    )
	TCHAR_TO_WCHAR_T_STRING_END( MailCCAddr  )
	TCHAR_TO_WCHAR_T_STRING_END( MailBCCAddr )
	TCHAR_TO_WCHAR_T_STRING_END( Subject     )
	TCHAR_TO_WCHAR_T_STRING_END( Text        )

	return Result ;
#endif
}

extern int MailApp_SendWithStrLen( const TCHAR *MailAddr, size_t MailAddrLength, const TCHAR *MailCCAddr, size_t MailCCAddrLength, const TCHAR *MailBCCAddr, size_t MailBCCAddrLength, const TCHAR *Subject, size_t SubjectLength, const TCHAR *Text, size_t TextLength )
{
	int Result = -1 ;
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( MailAddr    )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( MailCCAddr  )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( MailBCCAddr )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( Subject     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( Text        )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( MailAddr,    MailAddrLength,    goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( MailCCAddr,  MailCCAddrLength,  goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( MailBCCAddr, MailBCCAddrLength, goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( Subject,     SubjectLength,     goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( Text,        TextLength,        goto ERR )

	Result = MailApp_Send( UseMailAddrBuffer, UseMailCCAddrBuffer, UseMailBCCAddrBuffer, UseSubjectBuffer, UseTextBuffer ) ;

ERR :
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( MailAddr    )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( MailCCAddr  )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( MailBCCAddr )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( Subject     )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( Text        )

	return Result ;
}

#endif // defined( __APPLE__ ) || defined( __ANDROID__ )

















// �ǂݍ��ݏ����n�̊֐��Ŕ񓯊��ǂݍ��݂��s�����ǂ�����ݒ肷��( �񓯊��ǂݍ��݂ɑΉ����Ă���֐��̂ݗL�� )( TRUE:�񓯊��ǂݍ��݂��s��  FALSE:�񓯊��ǂݍ��݂��s��Ȃ�( �f�t�H���g ) )
extern int NS_SetUseASyncLoadFlag( int Flag )
{
	DxSysData.ASyncLoadFlag = Flag ;

	// �I��
	return 0 ;
}

// �ǂݍ��ݏ����n�̊֐��Ŕ񓯊��ǂݍ��݂��s�����ǂ������擾����( �񓯊��ǂݍ��݂ɑΉ����Ă���֐��̂ݗL�� )( TRUE:�񓯊��ǂݍ��݂��s��  FALSE:�񓯊��ǂݍ��݂��s��Ȃ�( �f�t�H���g ) )
extern int NS_GetUseASyncLoadFlag( void )
{
	return GetASyncLoadFlag() ;
}

// �񓯊��ǂݍ��݂��s�����ǂ������擾����( TRUE:�񓯊��ǂݍ��݂��s��   FALSE:�񓯊��ǂݍ��݂��s��Ȃ� )
extern int GetASyncLoadFlag( void )
{
	return DxSysData.ASyncLoadFlag ? TRUE : FALSE ;
}

// �c�w���C�u�����̃E�C���h�E�֘A�̋@�\���g�p���Ȃ��t���O
extern int NS_SetNotWinFlag( int Flag )
{
	if( Flag == TRUE ) DxSysData.NotDrawFlag = TRUE;
	DxSysData.NotWinFlag = Flag ;

	return 0 ;
}

// �`��@�\���g�����ǂ����̃t���O���Z�b�g����
extern int NS_SetNotDrawFlag( int Flag )
{
	DxSysData.NotDrawFlag = Flag ;

	return 0 ;
}

// �`��@�\���g�����ǂ����̃t���O���擾����
extern int NS_GetNotDrawFlag( void )
{
	return DxSysData.NotDrawFlag ;
}

// �T�E���h�@�\���g�����ǂ����̃t���O���Z�b�g����
extern int NS_SetNotSoundFlag( int Flag )
{
	DxSysData.NotSoundFlag = Flag ;

	return 0;
}

// ���͏�Ԏ擾�@�\���g�����ǂ����̃t���O���Z�b�g����
extern int NS_SetNotInputFlag( int Flag )
{
	DxSysData.NotInputFlag = Flag ;

	return 0;
}














// �E�G�C�g�n�֐�

// �w��̎��Ԃ����������Ƃ߂�
extern int NS_WaitTimer( int WaitTime )
{
	ULONGLONG StartTime, EndTime ;

	StartTime = NS_GetNowSysPerformanceCount() ;

	// 4msec�O�܂ŐQ��
	if( WaitTime > 4 )
	{
		// �w�莞�Ԃ̊ԃ��b�Z�[�W���[�v
		EndTime = StartTime + NS_ConvMilliSecondsToSysPerformanceCount( WaitTime - 4 ) ;
		while( EndTime > NS_GetNowSysPerformanceCount() )
		{
			// �E�B���h�E������ꂽ�ꍇ�͑����ɏI��
			if( NS_ProcessMessage() != 0 )
			{
				return 0 ;
			}
			Thread_Sleep( 1 ) ;
		}

	}

	// 4msec�ȉ��̕��͐��m�ɑ҂�
	EndTime = StartTime + NS_ConvMilliSecondsToSysPerformanceCount( WaitTime ) ;
	while( EndTime > NS_GetNowSysPerformanceCount() ){}

	// �I��
	return 0 ;
}

// �w��̎��Ԃ����X���b�h�𖰂点��
extern int NS_SleepThread( int WaitTime )
{
	if( WaitTime < 0 ) WaitTime = 0 ;

	Thread_Sleep( ( DWORD )WaitTime ) ;

	// �I��
	return 0 ;
}

#ifndef DX_NON_INPUT

// �L�[�̓��͑҂�
extern int NS_WaitKey( void )
{
	int BackCode = 0 ;

	while( ProcessMessage() == 0 && CheckHitKeyAll( DX_CHECKINPUT_ALL ) != 0 )
	{
		Thread_Sleep( 1 ) ;
	}

	while( ProcessMessage() == 0 && ( BackCode = CheckHitKeyAll( DX_CHECKINPUT_ALL ) ) == 0 )
	{
		Thread_Sleep( 1 ) ;
	}

//	while( ProcessMessage() == 0 && CheckHitKeyAll() != 0 )
//	{
//		Thread_Sleep( 1 ) ;
//	}

	return BackCode ;
}

#endif // DX_NON_INPUT






// �����擾

#ifndef DX_NON_MERSENNE_TWISTER

// �����̏����l��ݒ肷��
extern int NS_SRand( int Seed )
{
	// �����l�Z�b�g
	srandMT( ( unsigned int )Seed ) ;

	// �I��
	return 0 ;
}

// �������擾����( RandMax : �Ԃ��ė���l�̍ő�l )
extern int NS_GetRand( int RandMax )
{
	int Result ;
	LONGLONG RandMaxLL ;

	RandMaxLL = RandMax ;
	RandMaxLL ++ ;
	Result = ( int )( ( ( LONGLONG )randMT() * RandMaxLL ) >> 32 ) ;

	return Result ;
}

// �����Z���k�E�c�C�X�^�[�A���S���Y���Ő������ꂽ�����l�𖳉��H�Ŏ擾����
extern DWORD NS_GetMersenneTwisterRand( void )
{
	return randMT() ;
}

// �����n���h�����쐬����( �߂�l�@0�ȊO:�����n���h���@0:�G���[ )
extern DWORD_PTR NS_CreateRandHandle( int Seed )
{
	MERSENNE_TWISTER_DATA *MTData ;

	// �V���������n���h���p�̃��������m�ۂ���
	MTData = ( MERSENNE_TWISTER_DATA * )DXALLOC( sizeof( MERSENNE_TWISTER_DATA ) ) ;
	if( MTData == NULL )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x71\x4e\x70\x65\xcf\x30\xf3\x30\xc9\x30\xeb\x30\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x00"/*@ L"�����n���h���p�̃������̊m�ۂɎ��s���܂���" @*/ )) ;
		return 0 ;
	}

	// ��������������
	NS_SRandHandle( ( DWORD_PTR )MTData, ( unsigned int )( Seed >= 0 ? Seed : NS_GetRand( 0x7fffffff ) ) ) ;

	// �n���h����Ԃ�
	return ( DWORD_PTR )MTData ;
}

// �����n���h�����폜����
extern int NS_DeleteRandHandle( DWORD_PTR RandHandle )
{
	// ���������������
	if( RandHandle != 0 )
	{
		DXFREE( ( void * )RandHandle ) ;
	}

	// �I��
	return 0 ;
}

// �����n���h���̏����l���Đݒ肷��
extern int NS_SRandHandle( DWORD_PTR RandHandle, int Seed )
{
	// �G���[�`�F�b�N
	if( RandHandle == 0 )
	{
		return -1 ;
	}

	// ��������������
	initMTData( ( MERSENNE_TWISTER_DATA * )RandHandle, ( unsigned int )Seed ) ;

	// �I��
	return 0 ;
}

// �����n���h�����g�p���ė������擾����( RandMax : �Ԃ��ė���l�̍ő�l )
extern int NS_GetRandHandle( DWORD_PTR RandHandle, int RandMax )
{
	int Result ;
	LONGLONG RandMaxLL ;

	// �G���[�`�F�b�N
	if( RandHandle == 0 )
	{
		return -1 ;
	}

	RandMaxLL = RandMax ;
	RandMaxLL ++ ;
	Result = ( int )( ( ( LONGLONG )randMTData( ( MERSENNE_TWISTER_DATA * )RandHandle ) * RandMaxLL ) >> 32 ) ;

	return Result ;
}

// �����n���h�����g�p���ă����Z���k�E�c�C�X�^�[�A���S���Y���Ő������ꂽ�����l�𖳉��H�Ŏ擾����
extern DWORD NS_GetMersenneTwisterRandHandle( DWORD_PTR RandHandle )
{
	return randMTData( ( MERSENNE_TWISTER_DATA * )RandHandle ) ;
}

#else // DX_NON_MERSENNE_TWISTER

// �����̏����l��ݒ肷��
extern int NS_SRand( int Seed )
{
	// �����l�Z�b�g
	srand( Seed ) ;

	// �I��
	return 0 ;
}

// �������擾����( RandMax : �Ԃ��ė���l�̍ő�l )
extern int NS_GetRand( int RandMax )
{
	int Result ;
	LONGLONG RandMaxLL ;

	RandMaxLL = RandMax ;
	RandMaxLL ++ ;
	Result = ( int )( ( ( LONGLONG )rand() * RandMaxLL ) / ( ( LONGLONG )RAND_MAX + 1 ) ) ;

	return Result ;
}

#endif // DX_NON_MERSENNE_TWISTER









#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE





