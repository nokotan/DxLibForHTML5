//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�W���֐��̌݊��֐��v���O����
// 
//  	Ver 3.24d
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

// �C���N���[�h ---------------------------------------------------------------
#include "DxBaseFuncAndroid.h"
#include "../DxBaseFunc.h"
#include "../DxChar.h"
#include "../DxLog.h"
#include <math.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` -----------------------------------------------------------------

#define CURRENTDIRECTORY_MAX_LENGTH		(2048)

// �\���̐錾 -----------------------------------------------------------------

// �f�[�^��` -----------------------------------------------------------------

static wchar_t g_CurrentDirectory[ CURRENTDIRECTORY_MAX_LENGTH ] = L"";

// �֐��錾 -------------------------------------------------------------------

// �v���O���� -----------------------------------------------------------------

extern void	_SET_DEFAULT_CHARCODEFORMAT( void )
{
	_SET_WCHAR_T_CHARCODEFORMAT( sizeof( wchar_t ) > 2 ? DX_CHARCODEFORMAT_UTF32LE : DX_CHARCODEFORMAT_UTF16LE ) ;
//	_SET_CHARSET( DX_CHARSET_SHFTJIS ) ;
//	_SET_CHAR_CHARCODEFORMAT( DX_CHARCODEFORMAT_SHIFTJIS ) ;
	_SET_CHARSET( DX_CHARSET_UTF8 ) ;
	_SET_CHAR_CHARCODEFORMAT( DX_CHARCODEFORMAT_UTF8 ) ;
}

extern char *_GETCWD( char *Buffer, size_t BufferBytes )
{
	ConvString( ( const char * )L"", -1, ANDROID_WCHAR_CHARCODEFORMAT, Buffer, BufferBytes, CHAR_CHARCODEFORMAT ) ;

	return Buffer ;
}

extern wchar_t *_WGETCWD( wchar_t *Buffer, size_t BufferBytes )
{
	ConvString( ( const char * )L"", -1, ANDROID_WCHAR_CHARCODEFORMAT, ( char * )Buffer, BufferBytes, WCHAR_T_CHARCODEFORMAT ) ;

	return Buffer ;
}

extern int _CHDIR( const char *DirName )
{
	wchar_t TempBuffer[ 1024 ] ;

	ConvString( DirName, -1, CHAR_CHARCODEFORMAT, ( char * )TempBuffer, sizeof( TempBuffer ), ANDROID_WCHAR_CHARCODEFORMAT ) ;
	return _WCHDIR( TempBuffer ) ;
}

extern int _WCHDIR(  const wchar_t * DirName )
{
	int Result = 0 ;

	CreateRelativePathW_( DirName, g_CurrentDirectory, g_CurrentDirectory, sizeof( g_CurrentDirectory ) ) ;

	return Result != 0 ? 0 : -1 ;
}

extern int _FPCLASS( double x )
{
	int Return = 0 ;

	if( isnan( x ) )
	{
		Return = _FPCLASS_SNAN ;
	}
	else
	if( isinf( x ) )
	{
		Return = _FPCLASS_NINF ;
	}

	return Return ;
}

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

