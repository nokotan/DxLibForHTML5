//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�t�@�C���֌W�v���O����
// 
//  	Ver 3.22a
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

// �C���N���[�h ---------------------------------------------------------------
#include "../DxFile.h"
#include "../DxLog.h"
#include "../DxChar.h"
#include "../DxBaseFunc.h"
#include "../DxMemory.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` -----------------------------------------------------------------

#define MAX_PATH_LENGTH		1024
#define NUM_OPS				1024
#define MAX_FH_NUM			1024
#define MAX_DH_NUM			256
#define CHUNK_SIZE			2048

// �\���̐錾 -----------------------------------------------------------------

// �f�[�^��` -----------------------------------------------------------------

// �p�X�̎n�܂肪 / �� \\ �������ꍇ�A���[�g�f�B���N�g�����w�肵�����Ƃɂ��邩( 1:���[�g�f�B���N�g�����w�肵�����Ƃɂ���  0:���[�g�f�B���N�g�����w�肵�����Ƃɂ��Ȃ� )
int g_EnableRootDirName = 0 ;

// �ǉ��̃h���C�u���̐�
int g_AddDriveNameNum = 0 ;

// �ǉ��̃h���C�u��
const char * g_AddDriveName[ 16 ] =
{
	NULL
} ;

// �֐��錾 -------------------------------------------------------------------

// �v���O���� -----------------------------------------------------------------

extern void SetAssetManager( AAssetManager *AManager )
{
	GFileData.PF.AssetManagerP = AManager ;
}

extern void SetInternalAndExternalDataPath( const char *InternalDataPath, const char *ExternalDataPath )
{
	GFileData.PF.InternalDataPath = InternalDataPath ;
	GFileData.PF.InternalDataPathLength = CL_strlen( DX_CHARCODEFORMAT_UTF8, InternalDataPath ) ;
	GFileData.PF.ExternalDataPath = ExternalDataPath ;
	GFileData.PF.ExternalDataPathLength = CL_strlen( DX_CHARCODEFORMAT_UTF8, ExternalDataPath ) ;
}

// �t�@�C���A�N�Z�X�����̏������E�I���֐�

// �t�@�C���A�N�Z�X�����̏������֐��̊��ˑ��̏������s���֐�
extern int InitializeFile_PF( void )
{
	return 0 ;
}

// �t�@�C���A�N�Z�X�����̌�n���֐��̊��ˑ��̏������s���֐�
extern int TerminateFile_PF( void )
{
	return 0 ;
}

// �t�@�C���A�N�Z�X�֐�
static int ANDR_wchar_t_to_utf8_Path( const wchar_t *Path, char *utf8_PathBuffer, size_t utf8_PathBufferBytes )
{
	wchar_t DirPath[ 512 ], FullPath[ 512 ] ;

	// �J�����g�f�B���N�g���̎擾
	_WGETCWD( DirPath, sizeof( DirPath ) ) ;

	// �t���p�X���쐬
	ConvertFullPathW_( Path, FullPath, sizeof( FullPath ), DirPath ) ;

	// �p�X���� \ �� / �ɒu������
	ChangeEnMarkToSlashW_( FullPath ) ;

//	// �h���C�u�����啶���ɂȂ��Ă����珬�����ɂ���
//	{
//		int i ;
//
//		for( i = 0 ; FullPath[ i ] != '\0' && FullPath[ i ] != L':' ; i ++ )
//		{
//			if( FullPath[ i ] >= L'A' && FullPath[ i ] <= L'Z' )
//			{
//				FullPath[ i ] = FullPath[ i ] - L'A' + L'a' ;
//			}
//		}
//	}

	// wchar_t ���� UTF-8 �ɕϊ�
	ConvString( ( const char * )FullPath, -1, WCHAR_T_CHARCODEFORMAT, utf8_PathBuffer, utf8_PathBufferBytes, DX_CHARCODEFORMAT_UTF8 ) ;

	return 0 ;
}

extern int ReadOnlyFileAccessOpen_PF( FILEACCESS *FileAccess, const wchar_t *Path, int UseCacheFlag, int BlockReadFlag )
{
	char FullPathUTF8[ 1024 ] ;

	// wchar_t ���� UTF-8 �ɕϊ�
	ANDR_wchar_t_to_utf8_Path( Path, FullPathUTF8, sizeof( FullPathUTF8 ) ) ;

	FileAccess->PF.Asset = NULL ;
	FileAccess->PF.FilePointer = NULL ;

//	// InternalDataPath �� ExternalDataPath �̃f�B���N�g�����w�肳��Ă���ꍇ�͕W�����o�͂��g�p����
//	if( ( GFileData.PF.InternalDataPathLength != 0 && CL_strncmp( DX_CHARCODEFORMAT_UTF8, FullPathUTF8, GFileData.PF.InternalDataPath, GFileData.PF.InternalDataPathLength ) == 0 ) ||
//		( GFileData.PF.ExternalDataPathLength != 0 && CL_strncmp( DX_CHARCODEFORMAT_UTF8, FullPathUTF8, GFileData.PF.ExternalDataPath, GFileData.PF.ExternalDataPathLength ) == 0 ) )
	// �P�����ڂ� / �� \\ ��������W�����o�͂��g�p����
	if( FullPathUTF8[ 0 ] == '/' || FullPathUTF8[ 0 ] == '\\' )
	{
		FileAccess->PF.FilePointer = fopen( FullPathUTF8, "rb" ) ;
		if( FileAccess->PF.FilePointer == NULL )
		{
			return -1 ;
		}

		// �t�@�C���T�C�Y���擾
		fseek( FileAccess->PF.FilePointer, 0, SEEK_END ) ;
		FileAccess->Size = ftell( FileAccess->PF.FilePointer ) ;
		fseek( FileAccess->PF.FilePointer, 0, SEEK_SET ) ;
	}
	else
	{
		// ����ȊO�̓A�Z�b�g�}�l�[�W���[����t�@�C�����J��
		FileAccess->PF.Asset = AAssetManager_open( GFileData.PF.AssetManagerP, FullPathUTF8, AASSET_MODE_UNKNOWN ) ;
		if( FileAccess->PF.Asset == NULL )
		{
			return -1 ;
		}

		// �t�@�C���T�C�Y���擾
		FileAccess->Size = AAsset_getLength64( FileAccess->PF.Asset ) ;
	}

	// ����I��
	return 0 ;
}

extern int ReadOnlyFileAccessClose_PF( FILEACCESS *FileAccess )
{
	// �t�@�C�������
	if( FileAccess->PF.FilePointer != NULL )
	{
		fclose( FileAccess->PF.FilePointer ) ;
		FileAccess->PF.FilePointer = NULL ;
	}
	if( FileAccess->PF.Asset != NULL )
	{
		AAsset_close( FileAccess->PF.Asset ) ;
		FileAccess->PF.Asset = NULL ;
	}

	return 0 ;
}

extern int ReadOnlyFileAccessSeek_PF( FILEACCESS *FileAccess, LONGLONG SeekPoint )
{
	// �t�@�C���A�N�Z�X�ʒu��ύX����
	if( FileAccess->PF.FilePointer != NULL )
	{
		fseek( FileAccess->PF.FilePointer, SeekPoint, SEEK_SET ) ;
	}
	else
	{
		AAsset_seek64( FileAccess->PF.Asset, SeekPoint, SEEK_SET ) ;
	}

	// ����I��
	return 0 ;
}

extern size_t ReadOnlyFileAccessRead_PF( void *Buffer, size_t BlockSize, size_t DataNum, FILEACCESS *FileAccess )
{
	int BytesRead ;

	if( BlockSize == 0 || DataNum == 0 )
	{
		return 0 ;
	}

	if( FileAccess->PF.FilePointer != NULL )
	{
		BytesRead = fread( Buffer, BlockSize, DataNum, FileAccess->PF.FilePointer ) * BlockSize ;
	}
	else
	{
		BytesRead = AAsset_read( FileAccess->PF.Asset, Buffer, BlockSize * DataNum ) ;
	}

	return BytesRead ;
}

extern int ReadOnlyFileAccessIdleCheck_PF(	FILEACCESS *FileAccess )
{
	return TRUE ;
}

extern int ReadOnlyFileAccessChDir_PF( const wchar_t *Path )
{
	return _WCHDIR( Path ) ;
}

extern int ReadOnlyFileAccessGetDirS_PF( wchar_t *Buffer, size_t BufferBytes )
{
	_WGETCWD( Buffer, BufferBytes ) ;

	return 0 ;
}

extern int ReadOnlyFileAccessFindFirst_PF(	FINDINFO *FindInfo, const wchar_t *FilePath, FILEINFOW *Buffer )
{
	wchar_t DirPath[ 1024 ] ;
	char DirPathUTF8[ 1024 ] ;

	// �f�B���N�g���p�X�ƃt�@�C�����𕪂���
	AnalysisFileNameAndDirPathW_( FilePath, FindInfo->PF.SearchFileName, sizeof( FindInfo->PF.SearchFileName ), DirPath, sizeof( DirPath ) ) ;

	// �f�B���N�g���p�X�� wchar_t ���� UTF-8 �ɕϊ�
	ANDR_wchar_t_to_utf8_Path( DirPath, DirPathUTF8, sizeof( DirPathUTF8 ) ) ;

	FindInfo->PF.AssetDir = NULL ;
	FindInfo->PF.Dir = NULL ;

//	// InternalDataPath �� ExternalDataPath �̃f�B���N�g�����w�肳��Ă���ꍇ�͕W�����o�͂��g�p����
//	if( CL_strncmp( DX_CHARCODEFORMAT_UTF8, DirPathUTF8, GFileData.PF.InternalDataPath, GFileData.PF.InternalDataPathLength ) == 0 ||
//		CL_strncmp( DX_CHARCODEFORMAT_UTF8, DirPathUTF8, GFileData.PF.ExternalDataPath, GFileData.PF.ExternalDataPathLength ) == 0 )
	// �P�����ڂ� / �� \\ ��������W�����o�͂��g�p����
	if( DirPathUTF8[ 0 ] == '/' || DirPathUTF8[ 0 ] == '\\' )
	{
		FindInfo->PF.Dir = opendir( DirPathUTF8 ) ;
		if( FindInfo->PF.Dir == NULL )
		{
			return -1 ;
		}
	}
	else
	{
		// �A�Z�b�g�}�l�[�W���[���g�p���ăf�B���N�g�����J��
		FindInfo->PF.AssetDir = AAssetManager_openDir( GFileData.PF.AssetManagerP, DirPathUTF8 ) ;
		if( FindInfo->PF.AssetDir == NULL )
		{
			return -1 ;
		}
	}

	// �ŏ��̃t�@�C������������
	if( ReadOnlyFileAccessFindNext_PF( FindInfo, Buffer ) < 0 )
	{
		if( FindInfo->PF.Dir != NULL )
		{
			closedir( FindInfo->PF.Dir ) ;
			FindInfo->PF.Dir = NULL ;
		}

		if( FindInfo->PF.AssetDir != NULL )
		{
			AAssetDir_close( FindInfo->PF.AssetDir ) ;
			FindInfo->PF.AssetDir = NULL ;
		}

		return -1 ;
	}

	return 0 ;
}

extern int ReadOnlyFileAccessFindNext_PF(	FINDINFO *FindInfo, FILEINFOW *Buffer )
{
	const char *FileName ;
	wchar_t FileNameW[ 1024 ] ;

	if( FindInfo->PF.AssetDir == NULL && FindInfo->PF.Dir == NULL )
	{
		return -1 ;
	}

	if( FindInfo->PF.Dir != NULL )
	{
		for(;;)
		{
			dirent *ret = readdir( FindInfo->PF.Dir ) ;
			if( ret == NULL )
			{
				return -1 ;
			}

			ConvString( ret->d_name, -1, DX_CHARCODEFORMAT_UTF8, ( char * )FileNameW, sizeof( FileNameW ), WCHAR_T_CHARCODEFORMAT ) ;

			if( Strcmp_Str2_WildcardW_( FileNameW, FindInfo->PF.SearchFileName ) == 0 )
			{
				if( Buffer )
				{
					CL_strcpy( WCHAR_T_CHARCODEFORMAT, ( char * )Buffer->Name, ( char * )FileNameW ) ;
					Buffer->DirFlag = ret->d_type == DT_DIR ? TRUE : FALSE ;
					Buffer->Size = 0 ;
					_MEMSET( &Buffer->CreationTime, 0, sizeof( Buffer->CreationTime ) ) ;
					_MEMSET( &Buffer->LastWriteTime, 0, sizeof( Buffer->LastWriteTime ) ) ;
				}

				return 0 ;
			}
		}
	}
	else
	{
		for(;;)
		{
			FileName = AAssetDir_getNextFileName( FindInfo->PF.AssetDir ) ;
			if( FileName == NULL )
			{
				return -1 ;
			}

			ConvString( FileName, -1, DX_CHARCODEFORMAT_UTF8, ( char * )FileNameW, sizeof( FileNameW ), WCHAR_T_CHARCODEFORMAT ) ;

			if( Strcmp_Str2_WildcardW_( FileNameW, FindInfo->PF.SearchFileName ) == 0 )
			{
				if( Buffer )
				{
					CL_strcpy( WCHAR_T_CHARCODEFORMAT, ( char * )Buffer->Name, ( char * )FileNameW ) ;
					Buffer->DirFlag = 0 ;
					Buffer->Size = 0 ;
					_MEMSET( &Buffer->CreationTime, 0, sizeof( Buffer->CreationTime ) ) ;
					_MEMSET( &Buffer->LastWriteTime, 0, sizeof( Buffer->LastWriteTime ) ) ;
				}

				return 0 ;
			}
		}
	}

	return -1 ;
}

extern int ReadOnlyFileAccessFindClose_PF( FINDINFO *FindInfo )
{
	if( FindInfo->PF.Dir != NULL )
	{
		closedir( FindInfo->PF.Dir ) ;
		FindInfo->PF.Dir = NULL ;
	}

	if( FindInfo->PF.AssetDir != NULL )
	{
		AAssetDir_close( FindInfo->PF.AssetDir ) ;
		FindInfo->PF.AssetDir = NULL ;
	}

	return 0 ;
}













// �������ݐ�p�t�@�C���A�N�Z�X�֐�
extern	int			WriteOnlyFileAccessDelete_PF( const wchar_t *Path )
{
	char FullPathUTF8[ 1024 ] ;

	// wchar_t ���� UTF-8 �ɕϊ�
	ANDR_wchar_t_to_utf8_Path( Path, FullPathUTF8, sizeof( FullPathUTF8 ) ) ;

	remove( FullPathUTF8 ) ;

	return 0 ;
}

extern	DWORD_PTR	WriteOnlyFileAccessOpen_PF(  const wchar_t *Path )
{
	char FullPathUTF8[ 1024 ] ;
	FILE *fp ;

	// wchar_t ���� UTF-8 �ɕϊ�
	ANDR_wchar_t_to_utf8_Path( Path, FullPathUTF8, sizeof( FullPathUTF8 ) ) ;

	// �t�@�C�����J��
	fp = fopen( FullPathUTF8, "wb" ) ;
	if( fp == NULL )
	{
		return 0 ;
	}

	return ( DWORD_PTR )fp ;
}

extern	int			WriteOnlyFileAccessClose_PF( DWORD_PTR Handle )
{
	FILE *fp = ( FILE * )Handle ;

	fclose( fp ) ;

	return 0 ;
}

extern	int			WriteOnlyFileAccessSeek_PF(  DWORD_PTR Handle, LONGLONG SeekPoint, int SeekType )
{
	FILE *fp = ( FILE * )Handle ;

	fseek( fp, SeekPoint, SeekType ) ;

	return 0 ;
}

extern	int			WriteOnlyFileAccessWrite_PF( DWORD_PTR Handle, void *Buffer, size_t WriteSize, size_t *GetWriteSize )
{
	FILE *fp = ( FILE * )Handle ;
	size_t lWriteSize ;

	lWriteSize = fwrite( Buffer, 1, WriteSize, fp ) ;

	if( GetWriteSize )
	{
		*GetWriteSize = lWriteSize ;
	}

	return 0 ;
}







#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

