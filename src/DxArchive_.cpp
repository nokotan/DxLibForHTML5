// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�A�[�J�C�u����v���O����
// 
// 				Ver 3.24d
// 
// -------------------------------------------------------------------------------


// �c�w���C�u�����쐬���p��`
#define DX_MAKE

// �C���N���[�h-------------------------------------------------------------------
#include "DxArchive_.h"
#include "DxBaseFunc.h"
#include "DxMemory.h"
#include "DxFile.h"
#include "DxFont.h"
#include "DxLog.h"
#include "DxChar.h"
#include "DxThread.h"
#include "DxSystem.h"
#include <stdio.h>


#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

#ifndef DX_NON_DXA

// �}�N����` --------------------------------------------------------------------

#define DXARCD						DX_ArchiveDirData
//#define CHECKMULTIBYTECHAR(CP)		(( (unsigned char)*(CP) >= 0x81 && (unsigned char)*(CP) <= 0x9F ) || ( (unsigned char)*(CP) >= 0xE0 && (unsigned char)*(CP) <= 0xFC ))	// TRUE:�Q�o�C�g����  FALSE:�P�o�C�g����
#define CHARUP(C)					( (C) >= 'a' && (C) <= 'z' ? (C) - 'a' + 'A' : (C))

#define DXARC_ID_AND_VERSION_SIZE	(sizeof( WORD ) * 2)

#define DXARC_HEAD_VER8_SIZE		(64)

#define DXARC_FILEHEAD_VER8_SIZE	(72)			// Ver0x0008 �� DXARC_FILEHEAD �\���̂̃T�C�Y

#ifdef USE_ULL
#define NONE_PAL		(0xffffffffffffffffULL)
#else
#define NONE_PAL		(0xffffffffffffffff)
#endif

// �\���̒�` --------------------------------------------------------------------

// DXA_DIR_FindFirst ���̏����Ŏg�p����\����
struct DXA_DIR_FINDDATA
{
	int							UseArchiveFlag;					// �A�[�J�C�u�t�@�C�����g�p���Ă��邩�t���O
	int							UseArchiveIndex;				// �A�[�J�C�u���g�p���Ă���ꍇ�A�g�p���Ă���A�[�J�C�u�t�@�C���f�[�^�̃C���f�b�N�X
	DWORD_PTR					FindHandle;						// �t�@�C�������p�n���h��
} ;

// DXA_FindFirst ���̏����Ŏg�p����\����
struct DXA_FINDDATA
{
	DXARC						*Container;						// �����Ώۂ̂c�w�`�t�@�C��
	BYTE						SearchStr[ FILEPATH_MAX ] ;		// ����������
	DXARC_DIRECTORY				*Directory;						// �����Ώۂ̃f�B���N�g��
	DWORD						ObjectCount;					// ���ɓn���f�B���N�g�����I�u�W�F�N�g�̃C���f�b�N�X
} ;

#endif // DX_NON_DXA

// ���l���Ƃ̏o������Z�o���ꂽ�G���R�[�h��̃r�b�g���A���������̏�񓙂̍\����
struct HUFFMAN_NODE
{
	ULONGLONG					Weight ;						// �o����( �����f�[�^�ł͏o�����𑫂������m )
	int							BitNum ;						// ���k��̃r�b�g��̃r�b�g��( �����f�[�^�ł͎g��Ȃ� )
	unsigned char				BitArray[ 32 ] ;				// ���k��̃r�b�g��( �����f�[�^�ł͎g��Ȃ� )
	int							Index ;							// �����f�[�^�Ɋ��蓖�Ă�ꂽ�Q�ƃC���f�b�N�X( 0 or 1 )
	
	int							ParentNode ;					// ���̃f�[�^���]���Ă��錋���f�[�^�̗v�f�z��̃C���f�b�N�X
	int							ChildNode[ 2 ] ;				// ���̃f�[�^�������������Q�v�f�̗v�f�z��C���f�b�N�X( �����f�[�^�ł͂Ȃ��ꍇ�͂ǂ���� -1 )
} ;

// �r�b�g�P�ʓ��o�͗p�f�[�^�\����
struct BIT_STREAM
{
	BYTE						*Buffer ;
	ULONGLONG					Bytes ;
	DWORD						Bits ;
} ;

// �n�t�}�����k�f�[�^�̃w�b�_�̍\��
//   6bit      ���k�O�̃f�[�^�̃T�C�Y�̃r�b�g��(A) - 1( 0=1�r�b�g 63=64�r�b�g )
//   (A)bit    ���k�O�̃f�[�^�̃T�C�Y
//   6bit      ���k��̃f�[�^�̃T�C�Y�̃r�b�g��(B) - 1( �w�b�_�����܂܂Ȃ� )( 0=1�r�b�g 63=64�r�b�g )
//   (B)bit    ���k��̃f�[�^�̃T�C�Y
//
//   3bit      ���l���Ƃ̏o���p�x�̍����l�̃r�b�g��(C) / 2 - 1( 0=2�r�b�g 7=16�r�b�g )
//   1bit      �����r�b�g( 0=�v���X  1=�}�C�i�X )
//   (C)bit    ���l���Ƃ̏o���p�x�̍����l
//   �����ꂪ256����

#ifndef DX_NON_DXA

// �������ϐ��錾 --------------------------------------------------------------

BYTE Ascii_DotStr[ 2 ]       = { '.',       0 } ;
BYTE Ascii_DoubleDotStr[ 3 ] = { '.',  '.', 0 } ;
BYTE Ascii_EnStr[ 2 ]        = { '\\',      0 } ;
BYTE Ascii_SlashStr[ 2 ]     = { '/',       0 } ;

// �f�t�H���g��������
static char DefaultKeyString[ 9 ] = { 0x44, 0x58, 0x42, 0x44, 0x58, 0x41, 0x52, 0x43, 0x00 } ; // "DXLIBARC"

// �A�[�J�C�u���f�B���N�g���Ɍ����Ă�ׂ̃f�[�^
DXARC_DIR DX_ArchiveDirData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

static DXARC_FILEHEAD      *DXA_GetFileHeader(		DXARC *DXA, const BYTE *FilePath, DXARC_DIRECTORY **DirectoryP ) ;						// �t�@�C���̏��𓾂�
static int		DXA_ConvSearchData(					DXARC *DXA, DXARC_SEARCHDATA *Dest, const BYTE *Src, int *Length ) ;					// ������������p�̃f�[�^�ɕϊ�( �k�������� \ ����������I�� )
static int		DXA_ChangeCurrentDirectoryFast(		DXARC *DXA, DXARC_SEARCHDATA *SearchData ) ;											// �A�[�J�C�u���̃f�B���N�g���p�X��ύX����( 0:����  -1:���s )
static int		DXA_ChangeCurrentDirectoryBase(		DXARC *DXA, const BYTE *DirectoryPath, bool ErrorIsDirectoryReset, DXARC_SEARCHDATA *LastSearchData = NULL ) ;		// �A�[�J�C�u���̃f�B���N�g���p�X��ύX����( 0:����  -1:���s )
static size_t	DXA_CreateKeyFileString(			DXARC *DXA, DXARC_DIRECTORY *Directory, DXARC_FILEHEAD *FileHead, BYTE *FileString ) ;	// �J�����g�f�B���N�g���ɂ���w��̃t�@�C���̌��p�̕�������쐬����A�߂�l�͕�����̒���( �P�ʁFByte )( FileString �� DXA_KEY_STRING_MAXLENGTH �̒������K�v )
//static int	DXA_Decode(							void *Src, void *Dest ) ;																// �f�[�^���𓀂���( �߂�l:�𓀌�̃f�[�^�T�C�Y )
static void		DXA_KeyCreate(						const char *Source, size_t SourceBytes, unsigned char *Key ) ;							// ����������쐬
static void		DXA_KeyConv(						void *Data, LONGLONG  SizeLL, LONGLONG  PositionLL,  unsigned char *Key ) ;				// ����������g�p���� Xor ���Z( Key �͕K�� DXA_KEYSTR_LENGTH �̒������Ȃ���΂Ȃ�Ȃ� )
static void		DXA_KeyConvFileRead(				void *Data, ULONGLONG Size,   DWORD_PTR FilePointer, unsigned char *Key, LONGLONG Position = -1 ) ;	// �t�@�C������ǂݍ��񂾃f�[�^������������g�p���� Xor ���Z����֐�( Key �͕K�� DXA_KEYSTR_LENGTH �̒������Ȃ���΂Ȃ�Ȃ� )
static int		DXA_FindProcess(					DXA_FINDDATA *FindData, FILEINFOW *FileInfo );											// �����ɓK������I�u�W�F�N�g����������(�����Ώۂ� ObjectCount ���C���f�b�N�X�Ƃ����Ƃ��납��)(�߂�l -1:�G���[ 0:����)

static int		DXA_DIR_OpenArchive(				const wchar_t *FilePath, void *FileImage = NULL, int FileSize = -1, int FileImageCopyFlag = FALSE, int FileImageReadOnly = FALSE, int ArchiveIndex = -1, int OnMemory = FALSE, int ASyncThread = FALSE ) ;	// �A�[�J�C�u�t�@�C�����J��
static int		DXA_DIR_GetArchive(					const wchar_t *FilePath, void *FileImage = NULL ) ;										// ���ɊJ����Ă���A�[�J�C�u�̃n���h�����擾����( �߂�l: -1=�������� 0�ȏ�:�n���h�� )
static int		DXA_DIR_CloseArchive(				int ArchiveHandle ) ;																	// �A�[�J�C�u�t�@�C�������
static void		DXA_DIR_CloseWaitArchive(			int AlwaysClose = FALSE ) ;																// �g�p�����̂�҂��Ă���A�[�J�C�u�t�@�C����S�ĕ���
static int		DXA_DIR_ConvertFullPath(			const wchar_t *Src, wchar_t *Dest, size_t BufferBytes, int CharUp = 1 ) ;				// �S�Ẳp����������啶���ɂ��Ȃ���A�t���p�X�ɕϊ�����
static int		DXA_DIR_AnalysisFileNameAndDirPath( DXARC *DXA, const BYTE *Src, BYTE *FileName = 0, size_t FileNameBytes = 0, BYTE *DirPath = 0, size_t DirPathBytes = 0 ) ;					// �t�@�C�������ꏏ�ɂȂ��Ă���ƕ������Ă���p�X������t�@�C�����ƃf�B���N�g���p�X�𕪊�����B�t���p�X�ł���K�v�͖����A�t�@�C���������ł��ǂ��ADirPath �̏I�[�� �� �}�[�N�͕t���Ȃ�
static int		DXA_DIR_FileNameCmp(				DXARC *DXA, const BYTE *Src, const BYTE *CmpStr );										// CmpStr �̏����� Src ���K�����邩�ǂ����𒲂ׂ�( 0:�K������  -1:�K�����Ȃ� )
static int		DXA_DIR_OpenTest(					const wchar_t *FilePath, int *ArchiveIndex, BYTE *ArchiveFilePath, size_t BufferBytes ) ;	// �A�[�J�C�u�t�@�C�����t�H���_�Ɍ����Ăăt�@�C�����J�����̏��𓾂�( -1:�A�[�J�C�u�Ƃ��Ă͑��݂��Ȃ�����  0:���݂��� )

static int		DXA_DirectoryKeyConv(				DXARC *DXA, DXARC_DIRECTORY *Dir, char *KeyStringBuffer ) ;								// �w��̃f�B���N�g���f�[�^�̈Í�������������( �ۂ��ƃ������ɓǂݍ��񂾏ꍇ�p )

#endif // DX_NON_DXA

static void			BitStream_Init(  BIT_STREAM *BitStream, void *Buffer, bool IsRead ) ;			// �r�b�g�P�ʓ��o�͂̏�����
static void			BitStream_Write( BIT_STREAM *BitStream, BYTE BitNum, ULONGLONG OutputData ) ;	// �r�b�g�P�ʂ̐��l�̏������݂��s��
static ULONGLONG	BitStream_Read(  BIT_STREAM *BitStream, BYTE BitNum ) ;							// �r�b�g�P�ʂ̐��l�̓ǂݍ��݂��s��
static BYTE			BitStream_GetBitNum( ULONGLONG Data ) ;											// �w��̐��l�̃r�b�g�����擾����
static ULONGLONG	BitStream_GetBytes( BIT_STREAM *BitStream ) ;									// �r�b�g�P�ʂ̓��o�̓f�[�^�̃T�C�Y( �o�C�g�� )���擾����

// �v���O���� --------------------------------------------------------------------

// �r�b�g�P�ʓ��o�͂̏�����
void BitStream_Init( BIT_STREAM *BitStream, void *Buffer, bool IsRead )
{
	BitStream->Buffer = ( BYTE * )Buffer ;
	BitStream->Bytes = 0 ;
	BitStream->Bits = 0 ;
	if( IsRead == false )
	{
		BitStream->Buffer[ 0 ] = 0 ;
	}
}

// �r�b�g�P�ʂ̐��l�̏������݂��s��
void BitStream_Write( BIT_STREAM *BitStream, BYTE BitNum, ULONGLONG OutputData )
{
	DWORD i ;
	for( i = 0 ; i < BitNum ; i ++ )
	{
		BitStream->Buffer[ BitStream->Bytes ] |= ( ( OutputData >> ( BitNum - 1 - i ) ) & 1 ) << ( 7 - BitStream->Bits ) ;
		BitStream->Bits ++ ;
		if( BitStream->Bits == 8 )
		{
			BitStream->Bytes ++ ;
			BitStream->Bits = 0 ;
			BitStream->Buffer[ BitStream->Bytes ] = 0 ;
		}
	}
}

// �r�b�g�P�ʂ̐��l�̓ǂݍ��݂��s��
ULONGLONG BitStream_Read( BIT_STREAM *BitStream, BYTE BitNum )
{
	ULONGLONG Result = 0 ;
	DWORD i ;
	for( i = 0 ; i < BitNum ; i ++ )
	{
		Result |= ( ( ULONGLONG )( ( BitStream->Buffer[ BitStream->Bytes ] >> ( 7 - BitStream->Bits ) ) & 1 ) ) << ( BitNum - 1 - i ) ;
		BitStream->Bits ++ ;
		if( BitStream->Bits == 8 )
		{
			BitStream->Bytes ++ ;
			BitStream->Bits = 0 ;
		}
	}

	return Result ;
}

// �w��̐��l�̃r�b�g�����擾����
BYTE BitStream_GetBitNum( ULONGLONG Data )
{
	DWORD i ;
	for( i = 1 ; i < 64 ; i ++ )
	{
		if( Data < ( ULL_NUM( 1 ) << i ) )
		{
			return ( BYTE )i ;
		}
	}

	return ( BYTE )i ;
}

// �r�b�g�P�ʂ̓��o�̓f�[�^�̃T�C�Y( �o�C�g�� )���擾����
ULONGLONG BitStream_GetBytes( BIT_STREAM *BitStream )
{
	return BitStream->Bytes + ( BitStream->Bits != 0 ? 1 : 0 ) ;
}

#ifndef DX_NON_DXA

// �t�@�C���̏��𓾂�
static DXARC_FILEHEAD *DXA_GetFileHeader( DXARC *DXA, const BYTE *FilePath, DXARC_DIRECTORY **DirectoryP )
{
	DXARC_DIRECTORY *OldDir ;
	DXARC_FILEHEAD *FileH ;
	DWORD FileHeadSize ;
	BYTE *NameData ;
	int i, j, k, Num ;
	DXARC_SEARCHDATA SearchData ;

	// ���̃f�B���N�g����ۑ����Ă���
	OldDir = DXA->CurrentDirectory ;

	// �t�@�C���p�X�� \ or / ���܂܂�Ă���ꍇ�A�f�B���N�g���ύX���s��
	if( CL_strchr( DXA->CharCodeFormat, ( const char * )FilePath, '\\' ) != NULL ||
		CL_strchr( DXA->CharCodeFormat, ( const char * )FilePath, '/'  ) != NULL )
	{
		// �J�����g�f�B���N�g����ړI�̃t�@�C��������f�B���N�g���ɕύX����
		if( DXA_ChangeCurrentDirectoryBase( DXA, FilePath, false, &SearchData ) >= 0 )
		{
			// �G���[���N���Ȃ������ꍇ�̓t�@�C�������f�B���N�g�����������ƂɂȂ�̂ŃG���[
			goto ERR ;
		}
	}
	else
	{
		// �t�@�C�����������p�f�[�^�ɕϊ�����
		DXA_ConvSearchData( DXA, &SearchData, FilePath, NULL ) ;
	}

	// �����̃t�@�C����T��
	FileHeadSize = DXARC_FILEHEAD_VER8_SIZE ;
	FileH        = ( DXARC_FILEHEAD * )( DXA->Table.FileTable + DXA->CurrentDirectory->FileHeadAddress ) ;
	Num          = ( int )DXA->CurrentDirectory->FileHeadNum ;
	for( i = 0 ; i < Num ; i ++, FileH = (DXARC_FILEHEAD *)( (BYTE *)FileH + FileHeadSize ) )
	{
		// �f�B���N�g���`�F�b�N
		if( ( FileH->Attributes & FILE_ATTRIBUTE_DIRECTORY ) != 0 )
		{
			continue ;
		}

		// �����񐔂ƃp���e�B�`�F�b�N
		NameData = DXA->Table.NameTable + FileH->NameAddress ;
		if( SearchData.PackNum != ( ( WORD * )NameData )[ 0 ] ||
			SearchData.Parity  != ( ( WORD * )NameData )[ 1 ] )
		{
			continue ;
		}

		// ������`�F�b�N
		NameData += 4 ;
		for( j = 0, k = 0 ; j < SearchData.PackNum ; j ++, k += 4 )
		{
			if( *( ( DWORD * )&SearchData.FileName[ k ] ) != *( ( DWORD * )&NameData[ k ] ) )
			{
				break ;
			}
		}

		// �K�������t�@�C�����������炱���ŏI��
		if( SearchData.PackNum == j )
		{
			break ;
		}
	}

	// ����������G���[
	if( i == Num )
	{
		goto ERR ;
	}

	// �f�B���N�g�����擾����w�肪�������ꍇ�͑��
	if( DirectoryP != NULL )
	{
		*DirectoryP = DXA->CurrentDirectory ;
	}
	
	// �f�B���N�g�������ɖ߂�
	DXA->CurrentDirectory = OldDir ;
	
	// �ړI�̃t�@�C���̃A�h���X��Ԃ�
	return FileH ;
	
ERR :
	// �f�B���N�g�������ɖ߂�
	DXA->CurrentDirectory = OldDir ;
	
	// �G���[�I��
	return NULL ;
}


// ������������p�̃f�[�^�ɕϊ�( �k�������� \ ����������I�� )
static int DXA_ConvSearchData( DXARC *DXA, DXARC_SEARCHDATA *Dest, const BYTE *Src, int *Length )
{
	int i, j ;
	int StringLength ;
	WORD  ParityData ;
	DWORD CharCode ;
	int CharBytes ;

	ParityData = 0 ;
	i          = 0 ;
	for(;;)
	{
		CharCode = GetCharCode( ( const char * )&Src[ i ], DXA->CharCodeFormat, &CharBytes ) ;
		if( CharCode == '\0' || CharCode == '\\' || CharCode == '/' )
		{
			break ;
		}

		// �������̏ꍇ�͑啶���ɕϊ�
		if( CharCode >= 'a' && CharCode <= 'z' )
		{
			CharCode = CharCode - 'a' + 'A' ;
			PutCharCode( CharCode, DXA->CharCodeFormat, ( char * )&Dest->FileName[ i ], sizeof( Dest->FileName ) - i ) ;

			switch( CharBytes )
			{
			case 1 :
				ParityData += Dest->FileName[ i ] ;
				break ;

			case 2 :
				ParityData += Dest->FileName[ i ] + Dest->FileName[ i + 1 ] ;
				break ;

			case 4 :
				ParityData += Dest->FileName[ i ] + Dest->FileName[ i + 1 ] + Dest->FileName[ i + 2 ] + Dest->FileName[ i + 3 ] ;
				break ;

			default :
				for( j = 0 ; j < CharBytes ; j ++ )
				{
					ParityData += Dest->FileName[ i + j ] ;
				}
				break ;
			}
		}
		else
		{
			switch( CharBytes )
			{
			case 1 :
				Dest->FileName[ i ] = Src[ i ] ;
				ParityData += Src[ i ] ;
				break ;

			case 2 :
				*( ( WORD * )&Dest->FileName[ i ] ) = *( ( WORD * )&Src[ i ] ) ;
				ParityData += Src[ i ] + Src[ i + 1 ] ;
				break ;

			case 4 :
				*( ( DWORD * )&Dest->FileName[ i ] ) = *( ( DWORD * )&Src[ i ] ) ;
				ParityData += Src[ i ] + Src[ i + 1 ] + Src[ i + 2 ] + Src[ i + 3 ] ;
				break ;

			default :
				for( j = 0 ; j < CharBytes ; j ++ )
				{
					Dest->FileName[ i + j ] = Src[ i + j ] ;
					ParityData += Src[ i + j ] ;
				}
				break ;
			}
		}

		i += CharBytes ;
	}

	// ������̒�����ۑ�
	if( Length != NULL )
	{
		*Length = i ;
	}

	// �S�̔{���̈ʒu�܂łO����
	StringLength = ( ( i + 1 ) + 3 ) / 4 * 4 ;
	_MEMSET( &Dest->FileName[ i ], 0, ( size_t )( StringLength - i ) ) ;

	// �p���e�B�f�[�^�̕ۑ�
	Dest->Parity = ParityData ;

	// �p�b�N�f�[�^���̕ۑ�
	Dest->PackNum = ( WORD )( StringLength / 4 ) ;

	// ����I��
	return 0 ;
}







// �����쐬
static void DXA_KeyCreate( const char *Source, size_t SourceBytes, unsigned char *Key )
{
	char SourceTempBuffer[ 1024 ] ;
	char WorkBuffer[ 1024 ] ;
	char *UseWorkBuffer ;
	DWORD i, j ;
	DWORD CRC32_0 ;
	DWORD CRC32_1 ;

	if( SourceBytes == 0 )
	{
		SourceBytes = CL_strlen( DX_CHARCODEFORMAT_ASCII, Source ) ;
	}

	if( SourceBytes < 4 )
	{
		CL_strcpy( DX_CHARCODEFORMAT_ASCII, SourceTempBuffer, Source ) ;
		CL_strcpy( DX_CHARCODEFORMAT_ASCII, &SourceTempBuffer[ SourceBytes ], DefaultKeyString ) ;
		Source = SourceTempBuffer ;
		SourceBytes = CL_strlen( DX_CHARCODEFORMAT_ASCII, Source ) ;
	}

	if( SourceBytes / 2 > sizeof( WorkBuffer ) )
	{
		UseWorkBuffer = ( char * )DXALLOC( SourceBytes / 2 ) ;
	}
	else
	{
		UseWorkBuffer = WorkBuffer ;
	}

	j = 0 ;
	for( i = 0 ; i < SourceBytes ; i += 2, j++ )
	{
		UseWorkBuffer[ j ] = Source[ i ] ;
	}
	CRC32_0 = HashCRC32( UseWorkBuffer, j ) ;

	j = 0 ;
	for( i = 1 ; i < SourceBytes ; i += 2, j++ )
	{
		UseWorkBuffer[ j ] = Source[ i ] ;
	}
	CRC32_1 = HashCRC32( UseWorkBuffer, j ) ;

	Key[ 0 ] = ( BYTE )( CRC32_0 >>  0 ) ;
	Key[ 1 ] = ( BYTE )( CRC32_0 >>  8 ) ;
	Key[ 2 ] = ( BYTE )( CRC32_0 >> 16 ) ;
	Key[ 3 ] = ( BYTE )( CRC32_0 >> 24 ) ;
	Key[ 4 ] = ( BYTE )( CRC32_1 >>  0 ) ;
	Key[ 5 ] = ( BYTE )( CRC32_1 >>  8 ) ;
	Key[ 6 ] = ( BYTE )( CRC32_1 >> 16 ) ;

	if( SourceBytes > sizeof( WorkBuffer ) )
	{
		DXFREE( UseWorkBuffer ) ;
	}
}

// �����g�p���� Xor ���Z( Key �͕K�� DXA_KEY_BYTES �̒������Ȃ���΂Ȃ�Ȃ� )
static void DXA_KeyConv( void *Data, LONGLONG  SizeLL, LONGLONG  PositionLL,  unsigned char *Key )
{
	int Position ;

	Position = ( int )( PositionLL % DXA_KEY_BYTES ) ;

	if( SizeLL <= 0xffffffff )
	{
		DWORD SizeT ;
		SizeT = ( DWORD )SizeLL ;

		BYTE *DataBP ;
		BYTE *KeyBP ;

		DataBP = ( BYTE * )Data ;
		KeyBP = ( BYTE * )Key ;
		if( SizeT >= DXA_KEY_BYTES )
		{
			if( Position != 0 )
			{
				do
				{
					*DataBP ^= KeyBP[ Position ] ;
					Position ++ ;
					DataBP ++ ;
					SizeT -- ;
				}while( Position < DXA_KEY_BYTES ) ;
				Position = 0 ;
			}

			if( SizeT >= DXA_KEY_BYTES )
			{
				DWORD SetNum ;
				DWORD Key1 ;
				WORD Key2 ;
				BYTE Key3 ;

				SetNum = SizeT / DXA_KEY_BYTES ;
				SizeT -= SetNum * DXA_KEY_BYTES ;
				Key1 = ( ( DWORD * )KeyBP )[ 0 ] ;
				Key2 = ( (  WORD * )KeyBP )[ 2 ] ;
				Key3 = ( (  BYTE * )KeyBP )[ 6 ] ;

				do
				{
					( ( DWORD * )DataBP )[ 0 ] ^= Key1 ;
					( (  WORD * )DataBP )[ 2 ] ^= Key2 ;
					( (  BYTE * )DataBP )[ 6 ] ^= Key3 ;
					DataBP += DXA_KEY_BYTES ;
					SetNum -- ;
				}while( SetNum > 0 ) ;
			}
		}

		if( SizeT > 0 )
		{
			do
			{
				*DataBP ^= KeyBP[ Position ] ;
				DataBP ++ ;
				Position ++ ;
				if( Position == DXA_KEY_BYTES )
					Position = 0 ;
				SizeT -- ;
			}while( SizeT > 0 ) ;
		}
	}
	else
	{
		BYTE *DataBP ;
		BYTE *KeyBP ;

		DataBP = ( BYTE * )Data ;
		KeyBP = ( BYTE * )Key ;
		if( SizeLL >= DXA_KEY_BYTES )
		{
			if( Position != 0 )
			{
				do
				{
					*DataBP ^= KeyBP[ Position ] ;
					Position ++ ;
					DataBP ++ ;
					SizeLL -- ;
				}while( Position < DXA_KEY_BYTES ) ;
				Position = 0 ;
			}

			if( SizeLL >= DXA_KEY_BYTES )
			{
				DWORD SetNum ;
				DWORD Key1 ;
				WORD  Key2 ;
				BYTE  Key3 ;

				SetNum = ( DWORD )( SizeLL / DXA_KEY_BYTES ) ;
				SizeLL -= SetNum * DXA_KEY_BYTES ;
				Key1 = ( ( DWORD * )KeyBP )[ 0 ] ;
				Key2 = ( ( WORD  * )KeyBP )[ 2 ] ;
				Key3 = ( ( BYTE  * )KeyBP )[ 6 ] ;

				do
				{
					( ( DWORD * )DataBP )[ 0 ] ^= Key1 ;
					( ( WORD  * )DataBP )[ 2 ] ^= Key2 ;
					( ( BYTE  * )DataBP )[ 6 ] ^= Key3 ;
					DataBP += DXA_KEY_BYTES ;
					SetNum -- ;
				}while( SetNum > 0 ) ;
			}
		}

		if( SizeLL > 0 )
		{
			do
			{
				*DataBP ^= KeyBP[ Position ] ;
				DataBP ++ ;
				Position ++ ;
				if( Position == DXA_KEY_BYTES )
					Position = 0 ;
				SizeLL -- ;
			}while( SizeLL > 0 ) ;
		}
	}
}

// �t�@�C������ǂݍ��񂾃f�[�^������������g�p���� Xor ���Z����֐�( Key �͕K�� DXA_KEYSTR_LENGTH �̒������Ȃ���΂Ȃ�Ȃ� )
void DXA_KeyConvFileRead( void *Data, ULONGLONG  Size, DWORD_PTR FilePointer, unsigned char *Key, LONGLONG Position )
{
	LONGLONG pos = 0 ;

	if( Key != NULL )
	{
		// �t�@�C���̈ʒu���擾���Ă���
		pos = Position == -1 ? ReadOnlyFileAccessTell( FilePointer ) : Position ;
	}

	// �ǂݍ���
	ReadOnlyFileAccessRead( Data, ( size_t )Size, 1, FilePointer ) ;
	while( ReadOnlyFileAccessIdleCheck( FilePointer ) == FALSE )
	{
		Thread_Sleep( 1 ) ;
	}

	if( Key != NULL )
	{
		// �f�[�^������������g���� Xor ���Z
		DXA_KeyConv( Data, ( LONGLONG )Size, pos, Key ) ;
	}
}

// �����ɓK������I�u�W�F�N�g����������(�����Ώۂ� ObjectCount ���C���f�b�N�X�Ƃ����Ƃ��납��)(�߂�l -1:�G���[ 0:����)
static int DXA_FindProcess( DXA_FINDDATA *FindData, FILEINFOW *FileInfo )
{
	BYTE  *nameTable ;
	DXARC *DXA ;
	BYTE  *str ;
	BYTE  *name ;
	DWORD fileHeadSize ;
	BYTE  TempName[ 2048 ] ;
	BYTE  DotStr[ 16 ] ;
	BYTE  DoubleDotStr[ 16 ] ;

	DXA       = FindData->Container;
	nameTable = DXA->Table.NameTable;
	str       = FindData->SearchStr;

	ConvString( ( const char * )Ascii_DotStr,       -1, DX_CHARCODEFORMAT_ASCII, ( char * )DotStr,       sizeof( DotStr       ), DXA->CharCodeFormat ) ;
	ConvString( ( const char * )Ascii_DoubleDotStr, -1, DX_CHARCODEFORMAT_ASCII, ( char * )DoubleDotStr, sizeof( DoubleDotStr ), DXA->CharCodeFormat ) ;

	{
		ULONGLONG i, num, addnum ;
		DXARC_DIRECTORY *dir ;
		DXARC_FILEHEAD *file ;

		dir          = FindData->Directory ;
		num          = dir->FileHeadNum ;
		addnum       = ( ULONGLONG )( dir->ParentDirectoryAddress == NONE_PAL ? 1 : 2 ) ;
		fileHeadSize = DXARC_FILEHEAD_VER8_SIZE ;

		if( FindData->ObjectCount == ( DWORD )( num + addnum ) )
		{
			return -1 ;
		}

		file = ( DXARC_FILEHEAD * )( DXA->Table.FileTable + dir->FileHeadAddress + fileHeadSize * FindData->ObjectCount ) ;
		for( i = FindData->ObjectCount; i < num + addnum; i ++ )
		{
			if( i >= num )
			{
				if( i - num == 0 )
				{
					if( DXA_DIR_FileNameCmp( DXA, DotStr,       str ) == 0 )
					{
						break ;
					}
				}
				else
				if( i - num == 1 )
				{
					if( DXA_DIR_FileNameCmp( DXA, DoubleDotStr, str ) == 0 )
					{
						break;
					}
				}
			}
			else
			{
				name = ( BYTE * )( nameTable + file->NameAddress + 4 ) ;
				if( DXA_DIR_FileNameCmp( DXA, name, str ) == 0 )
				{
					break ;
				}

				file = (DXARC_FILEHEAD *)( (BYTE *)file + fileHeadSize ) ;
			}
		}
		FindData->ObjectCount = ( DWORD )i ;
		if( i == num + addnum )
		{
			return -1 ;
		}

		if( FileInfo )
		{
			if( i >= num )
			{
				switch( i - num )
				{
				default :
				case 0:
					CL_strcpy_s( DXA->CharCodeFormat, ( char * )TempName, sizeof( TempName ), ( const char * )DotStr       ) ;
					break ;

				case 1 :
					CL_strcpy_s( DXA->CharCodeFormat, ( char * )TempName, sizeof( TempName ), ( const char * )DoubleDotStr ) ;
					break ;
				}
				FileInfo->DirFlag = 1 ;
				FileInfo->Size    = 0 ;
				_MEMSET( &FileInfo->CreationTime,  0, sizeof( FileInfo->CreationTime  ) ) ;
				_MEMSET( &FileInfo->LastWriteTime, 0, sizeof( FileInfo->LastWriteTime ) ) ;
			}
			else
			{
				name = ( BYTE * )( nameTable + file->NameAddress ) ;
				CL_strcpy_s( DXA->CharCodeFormat, ( char * )TempName, sizeof( TempName ), ( const char * )( name + ( ( WORD * )name )[ 0 ] * 4 + 4 ) ) ;
				FileInfo->DirFlag = ( file->Attributes & FILE_ATTRIBUTE_DIRECTORY ) != 0 ? TRUE : FALSE ;
				FileInfo->Size    = ( LONGLONG)file->DataSize ;
#ifdef WINDOWS_DESKTOP_OS
				_FileTimeToLocalDateData( ( FILETIME * )&file->Time.Create,    &FileInfo->CreationTime  ) ;
				_FileTimeToLocalDateData( ( FILETIME * )&file->Time.LastWrite, &FileInfo->LastWriteTime ) ;
#else // WINDOWS_DESKTOP_OS
				_MEMSET( &FileInfo->CreationTime,  0, sizeof( FileInfo->CreationTime  ) ) ;
				_MEMSET( &FileInfo->LastWriteTime, 0, sizeof( FileInfo->LastWriteTime ) ) ;
#endif // WINDOWS_DESKTOP_OS
			}

			ConvString( ( const char * )TempName, -1, DXA->CharCodeFormat, ( char * )FileInfo->Name, sizeof( FileInfo->Name ), WCHAR_T_CHARCODEFORMAT ) ;
		}
	}

	return 0 ;
}



// �A�[�J�C�u�t�@�C���������ׂ̍\���̂�����������
extern	int	DXA_Initialize( DXARC *DXA )
{
	_MEMSET( DXA, 0, sizeof( DXARC ) ) ;

	// �I��
	return 0 ;
}

// �A�[�J�C�u�t�@�C���������ׂ̍\���̂̌�n��������
extern int DXA_Terminate( DXARC *DXA )
{
	DXA_CloseArchive( DXA ) ;

	_MEMSET( DXA, 0, sizeof( DXARC ) ) ;

	// �I��
	return 0 ;
}

// �w��̃f�B���N�g���f�[�^�̈Í�������������( �ۂ��ƃ������ɓǂݍ��񂾏ꍇ�p )
static int DXA_DirectoryKeyConv( DXARC *DXA, DXARC_DIRECTORY *Dir, char *KeyStringBuffer )
{
	// �������C���[�W�ł͂Ȃ��ꍇ�̓G���[
	if( DXA->MemoryOpenFlag == FALSE )
		return -1 ;

	// ���������s��Ȃ��w��̏ꍇ�͉��������ɏI��
	if( DXA->NoKey )
		return -1 ;

	// �Í������������J�n
	{
		DWORD i, FileHeadSize ;
		DXARC_FILEHEAD *File ;
		unsigned char Key[ DXA_KEY_BYTES ] ;
		size_t KeyStringBytes ;

		// �i�[����Ă���t�@�C���̐������J��Ԃ�
		FileHeadSize = DXARC_FILEHEAD_VER8_SIZE ;
		File = ( DXARC_FILEHEAD * )( DXA->Table.FileTable + Dir->FileHeadAddress ) ;
		for( i = 0 ; i < Dir->FileHeadNum ; i ++, File = ( DXARC_FILEHEAD * )( ( BYTE * )File + FileHeadSize ) )
		{
			// �f�B���N�g�����ǂ����ŏ����𕪊�
			if( File->Attributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				// �f�B���N�g���̏ꍇ�͍ċA��������
				DXA_DirectoryKeyConv( DXA, ( DXARC_DIRECTORY * )( DXA->Table.DirectoryTable + File->DataAddress ), KeyStringBuffer ) ;
			}
			else
			{
				BYTE *DataP ;

				// �t�@�C���̏ꍇ�͈Í�������������
				
				// �f�[�^������ꍇ�̂ݏ���
				if( File->DataSize != 0 )
				{
					// �f�[�^�ʒu���Z�b�g����
					DataP = ( BYTE * )DXA->MemoryImage + DXA->Head.DataStartAddress + File->DataAddress ;

					// �t�@�C���ʂ̌����쐬
					KeyStringBytes = DXA_CreateKeyFileString( DXA, Dir, File, ( BYTE * )KeyStringBuffer ) ;
					DXA_KeyCreate( KeyStringBuffer, KeyStringBytes, Key ) ;

					// �n�t�}�����k����Ă��邩�ǂ����ŏ����𕪊�
					if( File->HuffPressDataSize != NONE_PAL )
					{
						// �n�t�}�����k����Ă���ꍇ

						// �ʏ�̃f�[�^���k������Ă��邩�ǂ����ŏ����𕪊�
						if( File->PressDataSize != NONE_PAL )
						{
							// �t�@�C���̑O��̂݃n�t�}�����k����Ă��邩�ǂ����Ō���K�p����T�C�Y�𕪊�
							if( DXA->Head.HuffmanEncodeKB != 0xff && File->PressDataSize > DXA->Head.HuffmanEncodeKB * 1024 * 2 )
							{
								DXA_KeyConv( DataP, ( LONGLONG )( File->HuffPressDataSize + File->PressDataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 ), ( LONGLONG )File->DataSize, Key ) ;
							}
							else
							{
								DXA_KeyConv( DataP, ( LONGLONG )File->HuffPressDataSize, ( LONGLONG )File->DataSize, Key ) ;
							}
						}
						else
						{
							// �t�@�C���̑O��̂݃n�t�}�����k����Ă��邩�ǂ����Ō���K�p����T�C�Y�𕪊�
							if( DXA->Head.HuffmanEncodeKB != 0xff && File->DataSize > DXA->Head.HuffmanEncodeKB * 1024 * 2 )
							{
								DXA_KeyConv( DataP, ( LONGLONG )( File->HuffPressDataSize + File->DataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 ), ( LONGLONG )File->DataSize, Key ) ;
							}
							else
							{
								DXA_KeyConv( DataP, ( LONGLONG )File->HuffPressDataSize, ( LONGLONG )File->DataSize, Key ) ;
							}
						}
					}
					else
					// �f�[�^�����k����Ă��邩�ǂ����ŏ����𕪊�
					if( File->PressDataSize != NONE_PAL )
					{
						// ���k����Ă���ꍇ
						DXA_KeyConv( DataP, ( LONGLONG )File->PressDataSize, ( LONGLONG )File->DataSize, Key ) ;
					}
					else
					{
						// ���k����Ă��Ȃ��ꍇ
						DXA_KeyConv( DataP, ( LONGLONG )File->DataSize, ( LONGLONG )File->DataSize, Key ) ;
					}
				}
			}
		}
	}

	// �I��
	return 0 ;
}

// ��������ɂ���A�[�J�C�u�t�@�C���C���[�W���J��( 0:����  -1:���s )
extern int DXA_OpenArchiveFromMem( DXARC *DXA, void *ArchiveImage, int ArchiveSize, int ArchiveImageCopyFlag, int ArchiveImageReadOnlyFlag, const char *KeyString, const wchar_t *EmulateArchivePath )
{
	// �������C���[�W���R�s�[���Ďg�p����ꍇ�͓ǂݎ���p�ɂ͂��Ȃ�
	if( ArchiveImageCopyFlag )
	{
		ArchiveImageReadOnlyFlag = FALSE ;
	}

	// ���ɂȂ�炩�̃A�[�J�C�u���J���Ă����ꍇ�̓G���[
	if( DXA->ReadAccessOnlyFilePointer != 0 || DXA->MemoryImage != NULL ) return -1 ;

	// ��������̕ۑ��ƌ��̍쐬
	{
		// �w�肪�����ꍇ�̓f�t�H���g�̌���������g�p����
		if( KeyString == NULL )
		{
			KeyString = DefaultKeyString ;
		}

		DXA->KeyStringBytes = CL_strlen( DX_CHARCODEFORMAT_ASCII, KeyString ) ;
		if( DXA->KeyStringBytes > DXA_KEY_STRING_LENGTH )
		{
			DXA->KeyStringBytes = DXA_KEY_STRING_LENGTH ;
		}
		_MEMCPY( DXA->KeyString, KeyString, DXA->KeyStringBytes ) ;
		DXA->KeyString[ DXA->KeyStringBytes ] = '\0' ;

		// ���̍쐬
		DXA_KeyCreate( DXA->KeyString, DXA->KeyStringBytes, DXA->Key ) ;
	}

	// �t�@�C���p�X��ۑ�
	if( EmulateArchivePath != NULL )
	{
		_WCSCPY_S( DXA->FilePath, sizeof( DXA->FilePath ), EmulateArchivePath ) ;
	}
	else
	{
		_MEMSET( DXA->FilePath, 0, sizeof( DXA->FilePath ) ) ;
	}

	DXA->Table.Top       = NULL ;
	DXA->MemoryImage     = NULL ;
	DXA->MemoryImageSize = ArchiveSize ;
	if( ArchiveImageCopyFlag )
	{
		// �C���[�W���R�s�[����t���O�������Ă���ꍇ�̓R�s�[��̃������̈���m��
		DXA->MemoryImage = DXALLOC( ( size_t )ArchiveSize ) ;
		if( DXA->MemoryImage == NULL )
		{
			return -1 ;
		}

		// �A�[�J�C�u�t�@�C���C���[�W�̓��e���m�ۂ����������ɃR�s�[
		_MEMCPY( DXA->MemoryImage, ArchiveImage, ( size_t )ArchiveSize ) ;

		// �R�s�[�����������C���[�W���g�p����
		DXA->MemoryImageOriginal = ArchiveImage ;
		ArchiveImage             = DXA->MemoryImage ;
	}
	else
	{
		// �|�C���^��ۑ�
		DXA->MemoryImage         = ArchiveImage ;
		DXA->MemoryImageOriginal = NULL ;
	}

	// �ŏ��ɂh�c�ƃo�[�W�������R�s�[
	_MEMCPY( &DXA->Head, ArchiveImage, DXARC_ID_AND_VERSION_SIZE ) ;

	// �h�c���Ⴄ�ꍇ�̓G���[
	if( DXA->Head.Head != DXAHEAD )
	{
		goto ERR ;
	}

	// ���Ή��o�[�W�����̏ꍇ�̓G���[
	if( DXA->Head.Version > DXAVER || DXA->Head.Version < DXAVER_MIN )
	{
		goto ERR ;
	}

	// �w�b�_�������R�s�[
	_MEMCPY( &DXA->Head, ArchiveImage, DXARC_HEAD_VER8_SIZE ) ;

	DXA->Head.CharCodeFormat = 0 ;

	// �w�b�_�����
	{
		// ���������s���Ă��Ȃ������擾����
		DXA->NoKey = ( DXA->Head.Flags & DXA_FLAG_NO_KEY ) != 0 ;

		// �����R�[�h�`�����Z�b�g
		switch( DXA->Head.CharCodeFormat )
		{
		case DX_CHARCODEFORMAT_UHC :
		case DX_CHARCODEFORMAT_BIG5 :
		case DX_CHARCODEFORMAT_GB2312 :
		case DX_CHARCODEFORMAT_SHIFTJIS :
		case DX_CHARCODEFORMAT_UTF16LE :
		case DX_CHARCODEFORMAT_UTF16BE :
		case DX_CHARCODEFORMAT_WINDOWS_1252 :
		case DX_CHARCODEFORMAT_ISO_IEC_8859_15 :
		case DX_CHARCODEFORMAT_UTF8 :
		case DX_CHARCODEFORMAT_UTF32LE :
		case DX_CHARCODEFORMAT_UTF32BE :
			DXA->CharCodeFormat = ( int )DXA->Head.CharCodeFormat ;
			break ;

		default :
			DXA->CharCodeFormat = DX_CHARCODEFORMAT_SHIFTJIS ;
			break ;
		}

		// ���e�[�u���̃T�C�Y���̃��������m�ۂ���
		DXA->Table.Top = ( BYTE * )DXALLOC( ( size_t )DXA->Head.HeadSize ) ;
		if( DXA->Table.Top == NULL )
		{
			goto ERR ;
		}

		// �w�b�_�����k����Ă���ꍇ�͉𓀂���
		if( ( DXA->Head.Flags & DXA_FLAG_NO_HEAD_PRESS ) != 0 )
		{
			// ���k����Ă��Ȃ��ꍇ�͕��ʂɓǂݍ���
			_MEMCPY( DXA->Table.Top, ( BYTE * )DXA->MemoryImage + DXA->Head.FileNameTableStartAddress, DXA->Head.HeadSize ) ;
			if( DXA->NoKey == false ) DXA_KeyConv( DXA->Table.Top, DXA->Head.HeadSize, 0, DXA->Key ) ;
		}
		else
		{
			void *HuffHeadBuffer ;
			ULONGLONG HuffHeadSize ;
			void *LzHeadBuffer ;
			ULONGLONG LzHeadSize ;

			// �n�t�}�����k���ꂽ�w�b�_�̗e�ʂ��擾����
			HuffHeadSize = ( DWORD )( ( ULONGLONG )DXA->MemoryImageSize - DXA->Head.FileNameTableStartAddress ) ;

			// �n�t�}�����k���ꂽ�w�b�_��ǂݍ��ރ��������m�ۂ���
			HuffHeadBuffer = DXALLOC( ( size_t )HuffHeadSize ) ;
			if( HuffHeadBuffer == NULL )
			{
				goto ERR ;
			}

			// ���k���ꂽ�w�b�_���R�s�[�ƈÍ�������
			_MEMCPY( HuffHeadBuffer, ( BYTE * )DXA->MemoryImage + DXA->Head.FileNameTableStartAddress, ( size_t )HuffHeadSize ) ;
			if( DXA->NoKey == false ) DXA_KeyConv( HuffHeadBuffer, HuffHeadSize, 0, DXA->Key ) ;

			// �n�t�}�����k���ꂽ�w�b�_�̉𓀌�̗e�ʂ��擾����
			LzHeadSize = Huffman_Decode( HuffHeadBuffer, NULL ) ;

			// �n�t�}�����k���ꂽ�w�b�_�̉𓀌�̃f�[�^���i�[���郁�����p��̊m��
			LzHeadBuffer = DXALLOC( ( size_t )LzHeadSize ) ;
			if( LzHeadBuffer == NULL )
			{
				DXFREE( HuffHeadBuffer ) ;
				goto ERR ;
			}

			// ���k���ꂽ�w�b�_���𓀂���
			Huffman_Decode( HuffHeadBuffer, LzHeadBuffer ) ;

			// LZ���k���ꂽ�w�b�_���𓀂���
			DXA_Decode( LzHeadBuffer, DXA->Table.Top ) ;

			// �������̉��
			DXFREE( HuffHeadBuffer ) ;
			DXFREE( LzHeadBuffer ) ;
		}

		// �e���e�[�u���̃A�h���X���Z�b�g����
		DXA->Table.NameTable		= DXA->Table.Top ;
		DXA->Table.FileTable		= DXA->Table.NameTable + DXA->Head.FileTableStartAddress ;
		DXA->Table.DirectoryTable	= DXA->Table.NameTable + DXA->Head.DirectoryTableStartAddress ;

		// �J�����g�f�B���N�g���̃Z�b�g
		DXA->CurrentDirectory = ( DXARC_DIRECTORY * )DXA->Table.DirectoryTable ;
	}

	DXA->MemoryOpenFlag					= TRUE ;						// �������C���[�W����J���Ă���t���O�𗧂Ă�
	DXA->UserMemoryImageFlag			= TRUE ;						// ���[�U�[�̃C���[�W����J�����t���O�𗧂Ă�
	DXA->MemoryImageCopyFlag			= ArchiveImageCopyFlag ;		// �������C���[�W���R�s�[���Ďg�p���Ă��邩�ǂ����̃t���O��ۑ�
	DXA->MemoryImageReadOnlyFlag        = ArchiveImageReadOnlyFlag ;	// �������C���[�W��ǂݎ���p�ɂ��邩�ǂ����̃t���O��ۑ�

	// �S�Ẵt�@�C���f�[�^�̈Í�������������
	if( DXA->NoKey == false && ArchiveImageReadOnlyFlag == FALSE )
	{
		char KeyStringBuffer[ DXA_KEY_STRING_MAXLENGTH ] ;
		DXA_DirectoryKeyConv( DXA, ( DXARC_DIRECTORY * )DXA->Table.DirectoryTable, KeyStringBuffer ) ;
	}

	// �I��
	return 0 ;

ERR :
	if( ArchiveImageCopyFlag )
	{
		if( DXA->MemoryImage != NULL )
		{
			DXFREE( DXA->MemoryImage ) ;
			DXA->MemoryImage = NULL ;
		}
	}
	else
	if( DXA->Table.Top != NULL )
	{
		DXFREE( DXA->Table.Top ) ;
		DXA->Table.Top = NULL ;
	}
	
	// �I��
	return -1 ;
}

// �A�[�J�C�u�t�@�C�����������������������𓾂�( TRUE:�����Ă���  FALSE:�����Ă��Ȃ� )
extern int DXA_CheckIdle( DXARC *DXA )
{
	// �񓯊��I�[�v�����ł͂Ȃ���Γ��ɂ�邱�Ƃ͂Ȃ�
	if( DXA->ASyncOpenFlag == FALSE )
	{
		return TRUE ;
	}

	// �t�@�C���ǂݍ��݂��������Ă��邩���ׂ�
	if( ReadOnlyFileAccessIdleCheck( DXA->ASyncOpenFilePointer ) == FALSE )
	{
		return FALSE ;
	}

	// �t�@�C�������
	ReadOnlyFileAccessClose( DXA->ASyncOpenFilePointer ) ;
	DXA->ASyncOpenFilePointer = 0;

	// ���ׂẴf�[�^�𔽓]����
	if( DXA->NoKey == false )
	{
		char KeyStringBuffer[ DXA_KEY_STRING_MAXLENGTH ] ;
		DXA_DirectoryKeyConv( DXA, ( DXARC_DIRECTORY * )DXA->Table.DirectoryTable, KeyStringBuffer ) ;
	}

	// �񓯊��I�[�v�����t���O��|��
	DXA->ASyncOpenFlag = FALSE ;

	// �I��
	return TRUE ;
}

// �A�[�J�C�u�t�@�C�����J���ŏ��ɂ��ׂă�������ɓǂݍ���ł��珈������( 0:����  -1:���s )
extern int DXA_OpenArchiveFromFileUseMem( DXARC *DXA, const wchar_t *ArchivePath, const char *KeyString , int ASyncThread )
{
	// ���ɂȂ�炩�̃A�[�J�C�u���J���Ă����ꍇ�̓G���[
	if( DXA->ReadAccessOnlyFilePointer != 0 || DXA->MemoryImage )
	{
		return -1 ;
	}

	// ��������̕ۑ��ƌ��̍쐬
	{
		// �w�肪�����ꍇ�̓f�t�H���g�̌���������g�p����
		if( KeyString == NULL )
		{
			KeyString = DefaultKeyString ;
		}

		DXA->KeyStringBytes = CL_strlen( DX_CHARCODEFORMAT_ASCII, KeyString ) ;
		if( DXA->KeyStringBytes > DXA_KEY_STRING_LENGTH )
		{
			DXA->KeyStringBytes = DXA_KEY_STRING_LENGTH ;
		}
		_MEMCPY( DXA->KeyString, KeyString, DXA->KeyStringBytes ) ;
		DXA->KeyString[ DXA->KeyStringBytes ] = '\0' ;

		// ���̍쐬
		DXA_KeyCreate( DXA->KeyString, DXA->KeyStringBytes, DXA->Key ) ;
	}

	// �t�@�C�����J��
	DXA->ASyncOpenFilePointer = 0 ;
	DXA->MemoryImage          = NULL ;
	DXA->ASyncOpenFilePointer = ReadOnlyFileAccessOpen( ArchivePath, FALSE, TRUE, FALSE ) ;
	if( DXA->ASyncOpenFilePointer == 0 )
	{
		return -1 ;
	}

	// �t�@�C���p�X��ۑ�
	_WCSCPY_S( DXA->FilePath, sizeof( DXA->FilePath ), ArchivePath ) ;

	// �t�@�C���̃T�C�Y���擾����
	ReadOnlyFileAccessSeek( DXA->ASyncOpenFilePointer, 0L, SEEK_END ) ;
	DXA->MemoryImageSize = ReadOnlyFileAccessTell( DXA->ASyncOpenFilePointer ) ;
	ReadOnlyFileAccessSeek( DXA->ASyncOpenFilePointer, 0L, SEEK_SET ) ;

	// �t�@�C���̓��e��S�ă������ɓǂݍ��ވׂ̃������̈�̊m��
	DXA->MemoryImage = DXALLOC( ( size_t )DXA->MemoryImageSize ) ;

	// �h�c�ƃo�[�W�����ԍ�����������ǂݍ���
	ReadOnlyFileAccessRead( &DXA->Head, DXARC_ID_AND_VERSION_SIZE, 1, DXA->ASyncOpenFilePointer ) ;

	// �h�c���Ⴄ�ꍇ�̓G���[
	if( DXA->Head.Head != DXAHEAD )
	{
		goto ERR ;
	}

	// ���Ή��o�[�W�����̏ꍇ�̓G���[
	if( DXA->Head.Version > DXAVER || DXA->Head.Version < DXAVER_MIN )
	{
		goto ERR ;
	}

	// �t�@�C�����ۂ��Ɠǂݍ���
	ReadOnlyFileAccessSeek( DXA->ASyncOpenFilePointer, 0L, SEEK_SET ) ;
	ReadOnlyFileAccessRead( DXA->MemoryImage, ( size_t )DXA->MemoryImageSize, 1, DXA->ASyncOpenFilePointer );

	// �w�b�_�������R�s�[
	_MEMCPY( &DXA->Head, DXA->MemoryImage, DXARC_HEAD_VER8_SIZE ) ;

	// �w�b�_�����
	{
		// ���������s���Ă��Ȃ������擾����
		DXA->NoKey = ( DXA->Head.Flags & DXA_FLAG_NO_KEY ) != 0 ;

		// �����R�[�h�`�����Z�b�g
		switch( DXA->Head.CharCodeFormat )
		{
		case DX_CHARCODEFORMAT_UHC :
		case DX_CHARCODEFORMAT_BIG5 :
		case DX_CHARCODEFORMAT_GB2312 :
		case DX_CHARCODEFORMAT_SHIFTJIS :
		case DX_CHARCODEFORMAT_UTF16LE :
		case DX_CHARCODEFORMAT_UTF16BE :
		case DX_CHARCODEFORMAT_WINDOWS_1252 :
		case DX_CHARCODEFORMAT_ISO_IEC_8859_15 :
		case DX_CHARCODEFORMAT_UTF8 :
		case DX_CHARCODEFORMAT_UTF32LE :
		case DX_CHARCODEFORMAT_UTF32BE :
			DXA->CharCodeFormat = ( int )DXA->Head.CharCodeFormat ;
			break ;

		default :
			DXA->CharCodeFormat = DX_CHARCODEFORMAT_SHIFTJIS ;
			break ;
		}
		
		// ���e�[�u���̃T�C�Y���̃��������m�ۂ���
		DXA->Table.Top = ( BYTE * )DXALLOC( DXA->Head.HeadSize ) ;
		if( DXA->Table.Top == NULL )
		{
			goto ERR ;
		}
		
		// �w�b�_�����k����Ă���ꍇ�͉𓀂���
		if( ( DXA->Head.Flags & DXA_FLAG_NO_HEAD_PRESS ) != 0 )
		{
			// ���k����Ă��Ȃ��ꍇ�͕��ʂɓǂݍ���
			_MEMCPY( DXA->Table.Top, ( BYTE * )DXA->MemoryImage + DXA->Head.FileNameTableStartAddress, DXA->Head.HeadSize ) ;
			if( DXA->NoKey == false ) DXA_KeyConv( DXA->Table.Top, DXA->Head.HeadSize, 0, DXA->Key ) ;
		}
		else
		{
			void *HuffHeadBuffer ;
			ULONGLONG HuffHeadSize ;
			void *LzHeadBuffer ;
			ULONGLONG LzHeadSize ;

			// �n�t�}�����k���ꂽ�w�b�_�̗e�ʂ��擾����
			HuffHeadSize = ( DWORD )( ( ULONGLONG )DXA->MemoryImageSize - DXA->Head.FileNameTableStartAddress ) ;

			// �n�t�}�����k���ꂽ�w�b�_��ǂݍ��ރ��������m�ۂ���
			HuffHeadBuffer = DXALLOC( ( size_t )HuffHeadSize ) ;
			if( HuffHeadBuffer == NULL )
			{
				goto ERR ;
			}

			// ���k���ꂽ�w�b�_���R�s�[�ƈÍ�������
			_MEMCPY( HuffHeadBuffer, ( BYTE * )DXA->MemoryImage + DXA->Head.FileNameTableStartAddress, ( size_t )HuffHeadSize ) ;
			if( DXA->NoKey == false ) DXA_KeyConv( HuffHeadBuffer, HuffHeadSize, 0, DXA->Key ) ;

			// �n�t�}�����k���ꂽ�w�b�_�̉𓀌�̗e�ʂ��擾����
			LzHeadSize = Huffman_Decode( HuffHeadBuffer, NULL ) ;

			// �n�t�}�����k���ꂽ�w�b�_�̉𓀌�̃f�[�^���i�[���郁�����p��̊m��
			LzHeadBuffer = DXALLOC( ( size_t )LzHeadSize ) ;
			if( LzHeadBuffer == NULL )
			{
				DXFREE( HuffHeadBuffer ) ;
				goto ERR ;
			}

			// ���k���ꂽ�w�b�_���𓀂���
			Huffman_Decode( HuffHeadBuffer, LzHeadBuffer ) ;

			// LZ���k���ꂽ�w�b�_���𓀂���
			DXA_Decode( LzHeadBuffer, DXA->Table.Top ) ;

			// �������̉��
			DXFREE( HuffHeadBuffer ) ;
			DXFREE( LzHeadBuffer ) ;
		}

		// �e���e�[�u���̃A�h���X���Z�b�g����
		DXA->Table.NameTable		= DXA->Table.Top ;
		DXA->Table.FileTable		= DXA->Table.NameTable + DXA->Head.FileTableStartAddress ;
		DXA->Table.DirectoryTable	= DXA->Table.NameTable + DXA->Head.DirectoryTableStartAddress ;

		// �J�����g�f�B���N�g���̃Z�b�g
		DXA->CurrentDirectory = ( DXARC_DIRECTORY * )DXA->Table.DirectoryTable ;
	}

	// �t�@�C���񓯊��I�[�v�������Ƃ������Ƃ��Z�b�g���Ă���
	DXA->ASyncOpenFlag = TRUE ;

	DXA->MemoryOpenFlag					= TRUE ;			// �������C���[�W����J���Ă���t���O�𗧂Ă�
	DXA->UserMemoryImageFlag			= FALSE ;			// ���[�U�[�̃C���[�W����J�����킯�ł͂Ȃ��̂Ńt���O��|��
	DXA->MemoryImageCopyFlag			= FALSE ;			// �������C���[�W���R�s�[���Ďg�p���Ă���t���O��|��
	DXA->MemoryImageReadOnlyFlag        = FALSE ;			// �������C���[�W��ǂݎ���p�ɂ��邩�ǂ����̃t���O��|��

	// �����I�[�v���̏ꍇ�͂����ŊJ���I���̂�҂�
	if( ASyncThread == FALSE )
	{
		while( DXA_CheckIdle( DXA ) == FALSE )
		{
			Thread_Sleep( 0 ) ;
		}
	}

	// �I��
	return 0 ;

ERR :
	if( DXA->ASyncOpenFilePointer )
	{
		ReadOnlyFileAccessClose( DXA->ASyncOpenFilePointer );
		DXA->ASyncOpenFilePointer = 0;
	}

	if( DXA->MemoryImage )
	{
		DXFREE( DXA->MemoryImage );
		DXA->MemoryImage = 0;
	}

	DXA->ASyncOpenFlag = FALSE ;

	// �I��
	return -1 ;
}

// �A�[�J�C�u�t�@�C�����J��( 0:����  -1:���s )
extern int DXA_OpenArchiveFromFile( DXARC *DXA, const wchar_t *ArchivePath, const char *KeyString )
{
	// ���ɂȂ�炩�̃A�[�J�C�u���J���Ă����ꍇ�̓G���[
	if( DXA->ReadAccessOnlyFilePointer != 0 || DXA->MemoryImage )
	{
		return -1 ;
	}

	// �w�b�_�̏�����
	_MEMSET( &DXA->Head, 0, sizeof( DXA->Head ) ) ;
	
	// �A�[�J�C�u�t�@�C�����J�����Ǝ��݂�
	DXA->ReadAccessOnlyFilePointer = ReadOnlyFileAccessOpen( ArchivePath, FALSE, TRUE, FALSE ) ;
	if( DXA->ReadAccessOnlyFilePointer == 0 )
	{
		return -1 ;
	}

	// �t�@�C���p�X��ۑ�
	_WCSCPY_S( DXA->FilePath, sizeof( DXA->FilePath ), ArchivePath ) ;

	// ��������̕ۑ��ƌ��̍쐬
	{
		// �w�肪�����ꍇ�̓f�t�H���g�̌���������g�p����
		if( KeyString == NULL )
		{
			KeyString = DefaultKeyString ;
		}

		DXA->KeyStringBytes = CL_strlen( DX_CHARCODEFORMAT_ASCII, KeyString ) ;
		if( DXA->KeyStringBytes > DXA_KEY_STRING_LENGTH )
		{
			DXA->KeyStringBytes = DXA_KEY_STRING_LENGTH ;
		}
		_MEMCPY( DXA->KeyString, KeyString, DXA->KeyStringBytes ) ;
		DXA->KeyString[ DXA->KeyStringBytes ] = '\0' ;

		// ���̍쐬
		DXA_KeyCreate( DXA->KeyString, DXA->KeyStringBytes, DXA->Key ) ;
	}

	// �h�c�ƃo�[�W�����ԍ�����������ǂݍ���
	ReadOnlyFileAccessRead( &DXA->Head, DXARC_ID_AND_VERSION_SIZE, 1, DXA->ReadAccessOnlyFilePointer ) ;

	// �h�c���Ⴄ�ꍇ�̓G���[
	if( DXA->Head.Head != DXAHEAD )
	{
		goto ERR ;
	}

	// ���Ή��o�[�W�����̏ꍇ�̓G���[
	if( DXA->Head.Version > DXAVER || DXA->Head.Version < DXAVER_MIN )
	{
		goto ERR ;
	}

	// �w�b�_�̎c��̕�����ǂݍ���
	ReadOnlyFileAccessRead( ( BYTE * )&DXA->Head + DXARC_ID_AND_VERSION_SIZE, DXARC_HEAD_VER8_SIZE - DXARC_ID_AND_VERSION_SIZE, 1, DXA->ReadAccessOnlyFilePointer ) ;

	// �w�b�_�����
	{
		// ���������s���Ă��Ȃ������擾����
		DXA->NoKey = ( DXA->Head.Flags & DXA_FLAG_NO_KEY ) != 0 ;

		// �����R�[�h�`�����Z�b�g
		switch( DXA->Head.CharCodeFormat )
		{
		case DX_CHARCODEFORMAT_UHC :
		case DX_CHARCODEFORMAT_BIG5 :
		case DX_CHARCODEFORMAT_GB2312 :
		case DX_CHARCODEFORMAT_SHIFTJIS :
		case DX_CHARCODEFORMAT_UTF16LE :
		case DX_CHARCODEFORMAT_UTF16BE :
		case DX_CHARCODEFORMAT_WINDOWS_1252 :
		case DX_CHARCODEFORMAT_ISO_IEC_8859_15 :
		case DX_CHARCODEFORMAT_UTF8 :
		case DX_CHARCODEFORMAT_UTF32LE :
		case DX_CHARCODEFORMAT_UTF32BE :
			DXA->CharCodeFormat = ( int )DXA->Head.CharCodeFormat ;
			break ;

		default :
			DXA->CharCodeFormat = DX_CHARCODEFORMAT_SHIFTJIS ;
			break ;
		}

		// ���e�[�u���̃T�C�Y���̃��������m�ۂ���
		DXA->Table.Top = ( BYTE * )DXALLOC( DXA->Head.HeadSize ) ;
		if( DXA->Table.Top == NULL )
		{
			goto ERR ;
		}
		
		// �w�b�_�����k����Ă���ꍇ�͉𓀂���
		if( ( DXA->Head.Flags & DXA_FLAG_NO_HEAD_PRESS ) != 0 )
		{
			// ���k����Ă��Ȃ��ꍇ�͕��ʂɓǂݍ���
			ReadOnlyFileAccessSeek( DXA->ReadAccessOnlyFilePointer, DXA->Head.FileNameTableStartAddress, SEEK_SET ) ;
			DXA_KeyConvFileRead( DXA->Table.Top, DXA->Head.HeadSize, DXA->ReadAccessOnlyFilePointer, DXA->NoKey ? NULL : DXA->Key, 0 ) ;
		}
		else
		{
			void *HuffHeadBuffer ;
			ULONGLONG HuffHeadSize ;
			void *LzHeadBuffer ;
			ULONGLONG LzHeadSize ;
			LONGLONG FileSize ;

			// ���k���ꂽ�w�b�_�̗e�ʂ��擾����
			ReadOnlyFileAccessSeek( DXA->ReadAccessOnlyFilePointer, 0, SEEK_END ) ;
			FileSize = ReadOnlyFileAccessTell( DXA->ReadAccessOnlyFilePointer ) ;
			ReadOnlyFileAccessSeek( DXA->ReadAccessOnlyFilePointer, DXA->Head.FileNameTableStartAddress, SEEK_SET ) ;
			HuffHeadSize = ( ULONGLONG )( FileSize - ReadOnlyFileAccessTell( DXA->ReadAccessOnlyFilePointer ) ) ;

			// ���k���ꂽ�w�b�_��ǂݍ��ރ��������m�ۂ���
			HuffHeadBuffer = DXALLOC( ( size_t )HuffHeadSize ) ;
			if( HuffHeadBuffer == NULL )
			{
				goto ERR ;
			}

			// ���k���ꂽ�w�b�_���������ɓǂݍ���
			DXA_KeyConvFileRead( HuffHeadBuffer, HuffHeadSize, DXA->ReadAccessOnlyFilePointer, DXA->NoKey ? NULL : DXA->Key, 0 ) ;

			// �n�t�}�����k���ꂽ�w�b�_�̉𓀌�̗e�ʂ��擾����
			LzHeadSize = Huffman_Decode( HuffHeadBuffer, NULL ) ;

			// �n�t�}�����k���ꂽ�w�b�_�̉𓀌�̃f�[�^���i�[���郁�����p��̊m��
			LzHeadBuffer = DXALLOC( ( size_t )LzHeadSize ) ;
			if( LzHeadBuffer == NULL )
			{
				DXFREE( HuffHeadBuffer ) ;
				goto ERR ;
			}

			// ���k���ꂽ�w�b�_���𓀂���
			Huffman_Decode( HuffHeadBuffer, LzHeadBuffer ) ;

			// LZ���k���ꂽ�w�b�_���𓀂���
			DXA_Decode( LzHeadBuffer, DXA->Table.Top ) ;

			// �������̉��
			DXFREE( HuffHeadBuffer ) ;
			DXFREE( LzHeadBuffer ) ;
		}

		// �e���e�[�u���̃A�h���X���Z�b�g����
		DXA->Table.NameTable		= DXA->Table.Top ;
		DXA->Table.FileTable		= DXA->Table.NameTable + DXA->Head.FileTableStartAddress ;
		DXA->Table.DirectoryTable	= DXA->Table.NameTable + DXA->Head.DirectoryTableStartAddress ;

		// �J�����g�f�B���N�g���̃Z�b�g
		DXA->CurrentDirectory = ( DXARC_DIRECTORY * )DXA->Table.DirectoryTable ;
	}

	DXA->MemoryOpenFlag					= FALSE ;			// �������C���[�W����J���Ă���t���O��|��
	DXA->UserMemoryImageFlag			= FALSE ;			// ���[�U�[�̃C���[�W����J�����킯�ł͂Ȃ��̂Ńt���O��|��
	DXA->MemoryImageCopyFlag			= FALSE ;			// �������C���[�W���R�s�[���Ďg�p���Ă���t���O��|��
	DXA->MemoryImageReadOnlyFlag        = FALSE ;			// �������C���[�W��ǂݎ���p�ɂ��邩�ǂ����̃t���O��|��

	// �I��
	return 0 ;

ERR :
	if( DXA->ReadAccessOnlyFilePointer != 0 )
	{
		ReadOnlyFileAccessClose( DXA->ReadAccessOnlyFilePointer ) ;
		DXA->ReadAccessOnlyFilePointer = 0 ;
	}

	if( DXA->Table.Top != NULL )
	{
		DXFREE( DXA->Table.Top ) ;
		DXA->Table.Top = NULL ;
	}
	
	// �I��
	return -1 ;
}

// �A�[�J�C�u�t�@�C�������
extern int DXA_CloseArchive( DXARC *DXA )
{
	// ���ɕ��Ă����牽�������I��
	if( DXA->ReadAccessOnlyFilePointer == 0 && DXA->MemoryImage == NULL )
	{
		return 0 ;
	}

	// �񓯊������I�[�v�����̏ꍇ�͂����ŊJ���I���̂�҂�
	if( DXA->ASyncOpenFlag == TRUE )
	{
		while( DXA_CheckIdle( DXA ) == FALSE )
		{
			Thread_Sleep( 0 ) ;
		}
	}

	// ���e�[�u���p�Ɋm�ۂ��Ă��������������
	if( DXA->Table.Top != NULL )
	{
		DXFREE( DXA->Table.Top ) ;
		DXA->Table.Top = NULL ;
	}

	// ����������J���Ă��邩�ǂ����ŏ����𕪊�
	if( DXA->MemoryOpenFlag == TRUE )
	{
		// �A�[�J�C�u�v���O�������������ɓǂݍ��񂾏ꍇ�Ƃ����łȂ��ꍇ�ŏ����𕪊�
		if( DXA->UserMemoryImageFlag == TRUE )
		{
			// ���[�U�[����n���ꂽ�f�[�^�������ꍇ

			// �A�[�J�C�u�C���[�W���R�s�[���Ďg�p���Ă����ꍇ�͒P���ɉ������
			if( DXA->MemoryImageCopyFlag )
			{
				if( DXA->MemoryImage != NULL )
				{
					DXFREE( DXA->MemoryImage ) ;
					DXA->MemoryImage = NULL ;
				}
			}
			else
			// �n���ꂽ�������A�h���X��̓��e�𒼐ڎg�p���Ă����ꍇ�͔��]�����f�[�^�����ɖ߂�
			if( DXA->MemoryImageReadOnlyFlag == FALSE )
			{
				if( DXA->NoKey == false )
				{
					char KeyStringBuffer[ DXA_KEY_STRING_MAXLENGTH ] ;
					DXA_DirectoryKeyConv( DXA, ( DXARC_DIRECTORY * )DXA->Table.DirectoryTable, KeyStringBuffer ) ;
				}
			}
		}
		else
		{
			// �A�[�J�C�u�v���O�������������ɓǂݍ��񂾏ꍇ

			// �m�ۂ��Ă������������J������
			DXFREE( DXA->MemoryImage ) ;
		}
	}
	else
	{
		// �A�[�J�C�u�t�@�C�������
		ReadOnlyFileAccessClose( DXA->ReadAccessOnlyFilePointer ) ;
	}

	// ������
	_MEMSET( DXA, 0, sizeof( DXARC ) ) ;

	// �I��
	return 0 ;
}

// �A�[�J�C�u���̃f�B���N�g���p�X��ύX����( 0:����  -1:���s )
static int DXA_ChangeCurrentDirectoryFast( DXARC *DXA, DXARC_SEARCHDATA *SearchData )
{
	int i, j, k, Num ;
	BYTE *NameData, *PathData ;
	WORD PackNum, Parity ;
	DWORD FileHeadSize ;

	// �񓯊������I�[�v�����̏ꍇ�͂����ŊJ���I���̂�҂�
	if( DXA->ASyncOpenFlag == TRUE )
	{
		while( DXA_CheckIdle( DXA ) == FALSE )
		{
			Thread_Sleep( 0 ) ;
		}
	}

	PackNum  = SearchData->PackNum ;
	Parity   = SearchData->Parity ;
	PathData = SearchData->FileName ;

	// �J�����g�f�B���N�g�����瓯���̃f�B���N�g����T��
	{
		DXARC_FILEHEAD *FileH ;

		FileH        = ( DXARC_FILEHEAD * )( DXA->Table.FileTable + DXA->CurrentDirectory->FileHeadAddress ) ;
		Num          = ( int )DXA->CurrentDirectory->FileHeadNum ;
		FileHeadSize = DXARC_FILEHEAD_VER8_SIZE ;
		for( i = 0 ; i < Num ; i ++, FileH = (DXARC_FILEHEAD *)( (BYTE *)FileH + FileHeadSize ) )
		{
			// �f�B���N�g���`�F�b�N
			if( ( FileH->Attributes & FILE_ATTRIBUTE_DIRECTORY ) == 0 )
			{
				continue ;
			}

			// �����񐔂ƃp���e�B�`�F�b�N
			NameData = DXA->Table.NameTable + FileH->NameAddress ;
			if( PackNum != ( ( WORD * )NameData )[ 0 ] ||
				Parity  != ( ( WORD * )NameData )[ 1 ] )
			{
				continue ;
			}

			// ������`�F�b�N
			NameData += 4 ;
			for( j = 0, k = 0 ; j < PackNum ; j ++, k += 4 )
			{
				if( *( ( DWORD * )&PathData[ k ] ) != *( ( DWORD * )&NameData[ k ] ) )
				{
					break ;
				}
			}

			// �K�������f�B���N�g�����������炱���ŏI��
			if( PackNum == j )
			{
				break ;
			}
		}

		// ����������G���[
		if( i == Num )
		{
			return -1 ;
		}

		// �݂�����J�����g�f�B���N�g����ύX
		DXA->CurrentDirectory = ( DXARC_DIRECTORY * )( DXA->Table.DirectoryTable + FileH->DataAddress ) ;
	}

	// ����I��
	return 0 ;
}

// �A�[�J�C�u���̃f�B���N�g���p�X��ύX����( 0:����  -1:���s )
extern int DXA_ChangeCurrentDir( DXARC *DXA, int CharCodeFormat, const char *DirPath )
{
	BYTE TempBuffer[ 4096 ] ;
	const BYTE *DirPathB ;

	// �����R�[�h�`�����قȂ�ꍇ�͕ϊ�����
	if( CharCodeFormat != DXA->CharCodeFormat )
	{
		ConvString( DirPath, -1, CharCodeFormat, ( char * )TempBuffer, sizeof( TempBuffer ), DXA->CharCodeFormat ) ;
		DirPathB = TempBuffer ;
	}
	else
	{
		DirPathB = ( const BYTE * )DirPath ;
	}

	return DXA_ChangeCurrentDirectoryBase( DXA, DirPathB, true ) ;
}

// �A�[�J�C�u���̃f�B���N�g���p�X��ύX����( 0:����  -1:���s )
static int DXA_ChangeCurrentDirectoryBase( DXARC *DXA, const BYTE *DirectoryPath, bool ErrorIsDirectoryReset, DXARC_SEARCHDATA *LastSearchData )
{
	DXARC_DIRECTORY *OldDir ;
	DXARC_SEARCHDATA SearchData ;

	// �񓯊������I�[�v�����̏ꍇ�͂����ŊJ���I���̂�҂�
	if( DXA->ASyncOpenFlag == TRUE )
	{
		while( DXA_CheckIdle( DXA ) == FALSE )
		{
			Thread_Sleep( 0 ) ;
		}
	}

	// �����ɗ��܂�p�X�������疳��
	if( CL_strcmp_str2_ascii( DXA->CharCodeFormat, ( const char * )DirectoryPath, ( const char * )Ascii_DotStr ) == 0 )
	{
		return 0 ;
	}

	// �w\ or /�x�����̏ꍇ�̓��[�g�f�B���N�g���ɖ߂�
	if( CL_strcmp_str2_ascii( DXA->CharCodeFormat, ( const char * )DirectoryPath, ( const char * )Ascii_EnStr    ) == 0 ||
		CL_strcmp_str2_ascii( DXA->CharCodeFormat, ( const char * )DirectoryPath, ( const char * )Ascii_SlashStr ) == 0 )
	{
		DXA->CurrentDirectory   = ( DXARC_DIRECTORY      * )DXA->Table.DirectoryTable ;
		return 0 ;
	}

	// ���Ɉ������p�X�������珈���𕪊�
	if( CL_strcmp_str2_ascii( DXA->CharCodeFormat, ( const char * )DirectoryPath, ( const char * )Ascii_DoubleDotStr ) == 0 )
	{
		// ���[�g�f�B���N�g���ɋ�����G���[
		if( DXA->CurrentDirectory->ParentDirectoryAddress == NONE_PAL ) return -1 ;
			
		// �e�f�B���N�g�����������炻����Ɉڂ�
		DXA->CurrentDirectory   = ( DXARC_DIRECTORY      * )( DXA->Table.DirectoryTable + DXA->CurrentDirectory->ParentDirectoryAddress ) ;
		return 0 ;
	}

	// ����ȊO�̏ꍇ�͎w��̖��O�̃f�B���N�g����T��
	
	// �ύX�ȑO�̃f�B���N�g����ۑ����Ă���
	OldDir = DXA->CurrentDirectory ;

	// �p�X���Ɂw\�x�����邩�ǂ����ŏ����𕪊�
	if( CL_strchr( DXA->CharCodeFormat, ( const char * )DirectoryPath, '\\' ) == NULL &&
		CL_strchr( DXA->CharCodeFormat, ( const char * )DirectoryPath, '/'  ) == NULL )
	{
		// �t�@�C������������p�̌`���ɕϊ�����
		DXA_ConvSearchData( DXA, &SearchData, DirectoryPath, NULL ) ;

		// �f�B���N�g����ύX
		if( DXA_ChangeCurrentDirectoryFast( DXA, &SearchData ) < 0 ) goto ERR ;
	}
	else
	{
		// \ or / ������ꍇ�͌q�������f�B���N�g������ÂύX���Ă䂭
		int i ;
		int StrLength ;
		int CharBytes ;
		int CharBytes2 ;
		DWORD CharCode ;
		DWORD CharCode2 ;

		i = 0 ;

		// ���[�v
		for(;;)
		{
			// ��������擾����
			DXA_ConvSearchData( DXA, &SearchData, &DirectoryPath[ i ], &StrLength ) ;
			i += StrLength ;

			// ���������[�� \ or / �������ꍇ�̓��[�g�f�B���N�g���ɗ��Ƃ�
			CharCode = GetCharCode( ( const char * )&DirectoryPath[ i ], DXA->CharCodeFormat, &CharBytes ) ;
			if( StrLength == 0 && ( CharCode == '\\' || CharCode == '/' ) )
			{
				BYTE EnStr[ 16 ] ;

				ConvString( ( const char * )Ascii_EnStr, -1, DX_CHARCODEFORMAT_ASCII, ( char * )EnStr, sizeof( EnStr ), DXA->CharCodeFormat ) ;
				DXA_ChangeCurrentDirectoryBase( DXA, EnStr, false ) ;
			}
			else
			{
				// ����ȊO�̏ꍇ�͕��ʂɃf�B���N�g���ύX
				if( DXA_ChangeCurrentDirectoryFast( DXA, &SearchData ) < 0 )
				{
					// �G���[���N���āA�X�ɃG���[���N�������Ɍ��̃f�B���N�g���ɖ߂���
					// �t���O�������Ă���ꍇ�͌��̃f�B���N�g���ɖ߂�
					if( ErrorIsDirectoryReset == true )
					{
						DXA->CurrentDirectory = OldDir ;
					}

					// �G���[�I��
					goto ERR ;
				}
			}

			// �����I�[�����ŏI�������ꍇ�̓��[�v���甲����
			// ���͂��� \ or / �����Ȃ��ꍇ�����[�v���甲����
			if( CharCode == '\0' )
			{
				break ;
			}
			else
			{
				CharCode2 = GetCharCode( ( const char * )&DirectoryPath[ i + CharBytes ], DXA->CharCodeFormat, &CharBytes2 ) ;
				if( ( CharCode == '\\' && CharCode2 == '\0' ) ||
					( CharCode == '/'  && CharCode2 == '\0' ) )
				{
					break ;
				}
			}
			i += CharBytes ;
		}
	}

	if( LastSearchData != NULL )
	{
		_MEMCPY( LastSearchData->FileName, SearchData.FileName, ( size_t )( SearchData.PackNum * 4 ) ) ;
		LastSearchData->Parity  = SearchData.Parity ;
		LastSearchData->PackNum = SearchData.PackNum ;
	}

	// ����I��
	return 0 ;

ERR:
	if( LastSearchData != NULL )
	{
		_MEMCPY( LastSearchData->FileName, SearchData.FileName, ( size_t )( SearchData.PackNum * 4 ) ) ;
		LastSearchData->Parity  = SearchData.Parity ;
		LastSearchData->PackNum = SearchData.PackNum ;
	}

	// �G���[�I��
	return -1 ;
}

// �J�����g�f�B���N�g���ɂ���w��̃t�@�C���̌��p�̕�������쐬����A�߂�l�͕�����̒���( �P�ʁFByte )( FileString �� DXA_KEY_STRING_MAXLENGTH �̒������K�v )
static size_t DXA_CreateKeyFileString( DXARC *DXA, DXARC_DIRECTORY *Directory, DXARC_FILEHEAD *FileHead, BYTE *FileString )
{
	size_t StartAddr ;

	// �ŏ��Ƀp�X���[�h�̕�������Z�b�g
	if( DXA->KeyStringBytes != 0 )
	{
		_MEMCPY( FileString, DXA->KeyString, DXA->KeyStringBytes ) ;
		FileString[ DXA->KeyStringBytes ] = '\0' ;
		StartAddr = DXA->KeyStringBytes ;
	}
	else
	{
		FileString[ 0 ] = '\0' ;
		StartAddr = 0 ;
	}
	_MEMSET( &FileString[ DXA_KEY_STRING_MAXLENGTH - 8 ], 0, 8 ) ;

	// ���Ƀt�@�C�����̕�������Z�b�g
	CL_strcat_s( DXA->CharCodeFormat, ( char * )&FileString[ StartAddr ], ( DXA_KEY_STRING_MAXLENGTH - 8 ) - StartAddr, ( char * )( DXA->Table.NameTable + FileHead->NameAddress + 4 ) ) ;

	// ���̌�Ƀf�B���N�g���̕�������Z�b�g
	if( Directory->ParentDirectoryAddress != NONE_PAL )
	{
		do
		{
			CL_strcat_s( DXA->CharCodeFormat, ( char * )&FileString[ StartAddr ], ( DXA_KEY_STRING_MAXLENGTH - 8 ) - StartAddr, ( char * )( DXA->Table.NameTable + ( ( DXARC_FILEHEAD * )( DXA->Table.FileTable + Directory->DirectoryAddress ) )->NameAddress + 4 ) ) ;
			Directory = ( DXARC_DIRECTORY * )( DXA->Table.DirectoryTable + Directory->ParentDirectoryAddress ) ;
		}while( Directory->ParentDirectoryAddress != NONE_PAL ) ;
	}

	return StartAddr + CL_strlen( DXA->CharCodeFormat, ( char * )&FileString[ StartAddr ] ) * GetCharCodeFormatUnitSize( DXA->CharCodeFormat ) ;
}

// �A�[�J�C�u���̃J�����g�f�B���N�g���p�X���擾����
//extern int DXA_GetCurrentDir( DXARC *DXA, char *DirPathBuffer, int BufferSize )
//{
//	char DirPath[FILEPATH_MAX] ;
//	int Depth, i ;
//
//	// �񓯊������I�[�v�����̏ꍇ�͂����ŊJ���I���̂�҂�
//	if( DXA->ASyncOpenFlag == TRUE )
//	{
//		while( DXA_CheckIdle( DXA ) == FALSE )
//		{
//			Thread_Sleep( 0 ) ;
//		}
//	}
//
//	if( DXA->V5Flag )
//	{
//		DXARC_DIRECTORY_VER5 *Dir[200], *DirTempP ;
//
//		// ���[�g�f�B���N�g���ɒ����܂Ō�������
//		Depth = 0 ;
//		DirTempP = DXA->CurrentDirectoryV5 ;
//		while( DirTempP->DirectoryAddress != 0xffffffff && DirTempP->DirectoryAddress != 0 )
//		{
//			Dir[Depth] = DirTempP ;
//			DirTempP = ( DXARC_DIRECTORY_VER5 * )( DXA->Table.DirectoryTable + DirTempP->ParentDirectoryAddress ) ;
//			Depth ++ ;
//		}
//		
//		// �p�X����A������
//		DirPath[0] = '\0' ;
//		for( i = Depth - 1 ; i >= 0 ; i -- )
//		{
//			_STRCAT( DirPath, "\\" ) ;
//			_STRCAT( DirPath, (char *)DXA->Table.NameTable + ((DXARC_FILEHEAD_VER5 *)( DXA->Table.FileTable + Dir[i]->DirectoryAddress ))->NameAddress ) ;
//		}
//	}
//	else
//	{
//		DXARC_DIRECTORY *Dir[200], *DirTempP ;
//
//		// ���[�g�f�B���N�g���ɒ����܂Ō�������
//		Depth = 0 ;
//		DirTempP = DXA->CurrentDirectory ;
//		while( DirTempP->DirectoryAddress != 0xffffffff && DirTempP->DirectoryAddress != 0 )
//		{
//			Dir[Depth] = DirTempP ;
//			DirTempP = ( DXARC_DIRECTORY * )( DXA->Table.DirectoryTable + DirTempP->ParentDirectoryAddress ) ;
//			Depth ++ ;
//		}
//		
//		// �p�X����A������
//		DirPath[0] = '\0' ;
//		for( i = Depth - 1 ; i >= 0 ; i -- )
//		{
//			_STRCAT( DirPath, "\\" ) ;
//			_STRCAT( DirPath, (char *)DXA->Table.NameTable + ((DXARC_FILEHEAD *)( DXA->Table.FileTable + Dir[i]->DirectoryAddress ))->NameAddress ) ;
//		}
//	}
//
//	// �o�b�t�@�̒������O���A����������Ȃ��Ƃ��̓f�B���N�g�����̒�����Ԃ�
//	if( BufferSize == 0 || BufferSize < (int)_STRLEN( DirPath ) )
//	{
//		return _STRLEN( DirPath ) + 1 ;
//	}
//	else
//	{
//		// �f�B���N�g�������o�b�t�@�ɓ]������
//		_STRCPY( DirPathBuffer, DirPath ) ;
//	}
//
//	// �I��
//	return 0 ;
//}

// �A�[�J�C�u���̃I�u�W�F�N�g����������( -1:�G���[ -1�ȊO:DXA�����n���h�� )
extern DWORD_PTR DXA_FindFirst( DXARC *DXA, const BYTE *FilePath, FILEINFOW *Buffer )
{
	DXA_FINDDATA *find ;
	BYTE Dir[  FILEPATH_MAX ] ;
	BYTE Name[ FILEPATH_MAX ] ;
	int CharBytes ;

	// �񓯊������I�[�v�����̏ꍇ�͂����ŊJ���I���̂�҂�
	if( DXA->ASyncOpenFlag == TRUE )
	{
		while( DXA_CheckIdle( DXA ) == FALSE )
		{
			Thread_Sleep( 0 ) ;
		}
	}

	// �������̊m��
	find = ( DXA_FINDDATA * )DXALLOC( sizeof( *find ) ) ;
	if( find == NULL )
	{
		return ( DWORD_PTR )-1 ;
	}

	find->Container = DXA;
	DXA_DIR_AnalysisFileNameAndDirPath( DXA, FilePath, Name, sizeof( Name ), Dir, sizeof( Dir ) );

	// �S�đ啶���ɂ���
	CL_strupr( DXA->CharCodeFormat, ( char * )Dir  ) ;
	CL_strupr( DXA->CharCodeFormat, ( char * )Name ) ;

	// �����Ώۂ̃f�B���N�g�����擾
	if( GetCharCode( ( const char * )Dir, DXA->CharCodeFormat, &CharBytes ) == '\0' )
	{
		find->Directory = DXA->CurrentDirectory ;
	}
	else
	{
		DXARC_DIRECTORY *OldDir;

		OldDir = DXA->CurrentDirectory;

		// �w��̃f�B���N�g���������ꍇ�̓G���[
		if( DXA_ChangeCurrentDirectoryBase( DXA, Dir, false ) == -1 )
		{
			DXFREE( find ) ;
			DXA->CurrentDirectory = OldDir ;
			return ( DWORD_PTR )-1 ;
		}

		find->Directory       = DXA->CurrentDirectory ;
		DXA->CurrentDirectory = OldDir ;
	}

	find->ObjectCount = 0;
	CL_strcpy_s( DXA->CharCodeFormat, ( char * )find->SearchStr, sizeof( find->SearchStr ), ( const char * )Name ) ;

	// �K������ŏ��̃t�@�C������������
	if( DXA_FindProcess( find, Buffer ) == -1 )
	{
		DXFREE( find );
		return ( DWORD_PTR )-1 ;
	}
	find->ObjectCount ++ ;

	// �n���h����Ԃ�
	return ( DWORD_PTR )find ;
}

// �A�[�J�C�u���̃I�u�W�F�N�g����������( -1:�G���[ 0:���� )
extern int DXA_FindNext( DWORD_PTR DxaFindHandle, FILEINFOW *Buffer )
{
	DXA_FINDDATA *find;

	find = ( DXA_FINDDATA * )DxaFindHandle ;
	if( DXA_FindProcess( find, Buffer ) == -1 )
	{
		return -1 ;
	}
	find->ObjectCount ++ ;

	return 0 ;
}

// �A�[�J�C�u���̃I�u�W�F�N�g�������I������
extern int DXA_FindClose( DWORD_PTR DxaFindHandle )
{
	DXA_FINDDATA *find ;

	find = ( DXA_FINDDATA * )DxaFindHandle ;
	DXFREE( find ) ;

	return 0 ;
}

// �A�[�J�C�u�t�@�C�����������ɓǂݍ��񂾏ꍇ�̃t�@�C���C���[�W���i�[����Ă���擪�A�h���X���擾����( DXA_OpenArchiveFromFileUseMem �Ⴕ���� DXA_OpenArchiveFromMem �ŊJ�����ꍇ�ɗL�� )
extern void *DXA_GetFileImage( DXARC *DXA )
{
	// �񓯊������I�[�v�����̏ꍇ�͂����ŊJ���I���̂�҂�
	if( DXA->ASyncOpenFlag == TRUE )
	{
		while( DXA_CheckIdle( DXA ) == FALSE )
		{
			Thread_Sleep( 0 ) ;
		}
	}

	// �������C���[�W����J���Ă��Ȃ�������G���[
	if( DXA->MemoryOpenFlag == FALSE )
	{
		return NULL ;
	}

	// �擪�A�h���X��Ԃ�
	return DXA->MemoryImage ;
}

// �A�[�J�C�u�t�@�C�����̎w��̃t�@�C���̃t�@�C�����̈ʒu�ƃt�@�C���̑傫���𓾂�( -1:�G���[ )
extern int DXA_GetFileInfo( DXARC *DXA, int CharCodeFormat, const char *FilePath, int *Position, int *Size )
{
	BYTE TempBuffer[ 4096 ] ;
	const BYTE *FilePathB ;

	// �����R�[�h�`�����قȂ�ꍇ�͕ϊ�����
	if( CharCodeFormat != DXA->CharCodeFormat )
	{
		ConvString( FilePath, -1, CharCodeFormat, ( char * )TempBuffer, sizeof( TempBuffer ), DXA->CharCodeFormat ) ;
		FilePathB = TempBuffer ;
	}
	else
	{
		FilePathB = ( const BYTE * )FilePath ;
	}

	// �񓯊������I�[�v�����̏ꍇ�͂����ŊJ���I���̂�҂�
	if( DXA->ASyncOpenFlag == TRUE )
	{
		while( DXA_CheckIdle( DXA ) == FALSE )
		{
			Thread_Sleep( 0 ) ;
		}
	}

	{
		DXARC_FILEHEAD *FileH ;
		DXARC_DIRECTORY *Directory ;

		// �w��̃t�@�C���̏��𓾂�
		FileH = DXA_GetFileHeader( DXA, FilePathB, &Directory ) ;
		if( FileH == NULL )
		{
			return -1 ;
		}

		// �t�@�C���̃f�[�^������ʒu�ƃt�@�C���T�C�Y��ۑ�����
		if( Position != NULL )
		{
			*Position = ( int )( DXA->Head.DataStartAddress + FileH->DataAddress ) ;
		}

		if( Size     != NULL )
		{
			*Size     = ( int )( FileH->DataSize ) ;
		}
	}

	// �����I��
	return 0 ;
}



// �A�[�J�C�u�t�@�C�����̃t�@�C�����J��(�t�@�C�������Ƃ͕K�v�Ȃ�)
extern int DXA_STREAM_Initialize( DXARC_STREAM *DXAStream, DXARC *DXA, const BYTE *FilePath, int UseASyncReadFlag )
{
	// �񓯊������I�[�v�����̏ꍇ�͂����ŊJ���I���̂�҂�
	if( DXA->ASyncOpenFlag == TRUE )
	{
		while( DXA_CheckIdle( DXA ) == FALSE )
		{
			Thread_Sleep( 0 ) ;
		}
	}

	// �f�[�^�̃Z�b�g
	DXAStream->Archive          = DXA ;
	DXAStream->EOFFlag          = FALSE ;
	DXAStream->FilePoint        = 0 ;
	DXAStream->DecodeDataBuffer = NULL ;
	DXAStream->DecodeTempBuffer = NULL ;
	DXAStream->UseASyncReadFlag = UseASyncReadFlag ;
	DXAStream->ASyncState       = DXARC_STREAM_ASYNCSTATE_IDLE ;

	{
		DXARC_FILEHEAD *FileH ;
		DXARC_DIRECTORY *Directory ;

		// �w��̃t�@�C���̏��𓾂�
		FileH = DXA_GetFileHeader( DXA, FilePath, &Directory ) ;
		if( FileH == NULL )
		{
			return -1 ;
		}

		// �t�@�C������J���Ă���ꍇ�̓A�[�J�C�u�t�@�C���̃t�@�C���|�C���^���쐬
		if( DXA->MemoryOpenFlag == FALSE )
		{
			DXAStream->ReadOnlyFilePointer = ReadOnlyFileAccessOpen( DXA->FilePath, FALSE, TRUE, FALSE ) ;
			if( DXAStream->ReadOnlyFilePointer == 0 )
			{
				return -1 ;
			}
		}

		// �t�@�C�������Z�b�g
		DXAStream->FileHead = FileH ;

		// ���������s��Ȃ����ǂ�����ۑ�
		DXAStream->NoKey = DXA->NoKey ;

		// �����쐬����
		if( DXAStream->NoKey == false )
		{
			char KeyString[ DXA_KEY_STRING_MAXLENGTH ] ;
			size_t KeyStringBytes ;
			KeyStringBytes = DXA_CreateKeyFileString( DXA, Directory, FileH, ( BYTE * )KeyString ) ;
			DXA_KeyCreate( KeyString, KeyStringBytes, DXAStream->Key ) ;
		}

		// �t�@�C�������k����Ă���ꍇ�͉𓀃f�[�^�����܂郁�����̈�̊m��
		if( FileH->PressDataSize != NONE_PAL || FileH->HuffPressDataSize != NONE_PAL )
		{
			DXAStream->DecodeDataBuffer = DXALLOC( ( size_t )FileH->DataSize ) ;
			if( DXAStream->DecodeDataBuffer == NULL )
			{
				goto ERR ;
			}
		}

		// �t�@�C�������k����Ă��邩�ǂ����ŏ����𕪊�
		if( FileH->PressDataSize != NONE_PAL )
		{
			// �n�t�}�����k������Ă��邩�ǂ����ŏ����𕪊�
			if( FileH->HuffPressDataSize != NONE_PAL )
			{
				// ��������ɓǂݍ��܂�Ă��邩�ǂ����ŏ����𕪊�
				if( DXA->MemoryOpenFlag == TRUE )
				{
					if( DXA->MemoryImageReadOnlyFlag )
					{
						// ���k�f�[�^�����܂郁�����̈�̊m��
						DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )( FileH->PressDataSize + FileH->HuffPressDataSize ) ) ;
						if( DXAStream->DecodeTempBuffer == NULL )
						{
							goto ERR ;
						}

						// ���k�f�[�^�̃R�s�[�ƌ�����
						_MEMCPY( DXAStream->DecodeTempBuffer, ( BYTE * )DXA->MemoryImage + DXA->Head.DataStartAddress + FileH->DataAddress, ( size_t )FileH->HuffPressDataSize ) ;
						if( DXAStream->NoKey == false ) DXA_KeyConv( DXAStream->DecodeTempBuffer, ( LONGLONG )FileH->HuffPressDataSize, ( LONGLONG )FileH->DataSize, DXAStream->Key ) ;

						// �n�t�}�����k�f�[�^����
						Huffman_Decode( DXAStream->DecodeTempBuffer, ( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize ) ;

						// �t�@�C���̑O��̂݃n�t�}�����k����Ă����ꍇ�͎c���LZ���k�f�[�^���R�s�[
						if( DXA->Head.HuffmanEncodeKB != 0xff && FileH->PressDataSize > DXA->Head.HuffmanEncodeKB * 1024 * 2 )
						{
							// �𓀂����f�[�^�̓��A��딼�����ړ�����
							_MEMMOVE( 
								( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize + FileH->PressDataSize - DXA->Head.HuffmanEncodeKB * 1024,
								( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize + DXA->Head.HuffmanEncodeKB * 1024,
								DXA->Head.HuffmanEncodeKB * 1024
							) ;

							// �c���LZ���k�f�[�^��]��
							_MEMCPY(
								( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize + DXA->Head.HuffmanEncodeKB * 1024,
								( BYTE * )DXA->MemoryImage + DXA->Head.DataStartAddress + FileH->DataAddress + FileH->HuffPressDataSize,
								( size_t )( FileH->PressDataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 )
							) ;
							if( DXAStream->NoKey == false ) DXA_KeyConv( ( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize + DXA->Head.HuffmanEncodeKB * 1024, ( LONGLONG )( FileH->PressDataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 ), ( LONGLONG )( FileH->DataSize + FileH->HuffPressDataSize ), DXAStream->Key ) ;
						}

						// ��
						DXA_Decode( ( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize, DXAStream->DecodeDataBuffer ) ;
				
						// ��Ɨp�������̉��
						DXFREE( DXAStream->DecodeTempBuffer ) ;
						DXAStream->DecodeTempBuffer = NULL ;
					}
					else
					{
						// ���k�f�[�^�����܂郁�����̈�̊m��
						DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )FileH->PressDataSize ) ;
						if( DXAStream->DecodeTempBuffer == NULL )
						{
							goto ERR ;
						}

						// �n�t�}�����k�f�[�^����
						Huffman_Decode( ( BYTE * )DXA->MemoryImage + DXA->Head.DataStartAddress + FileH->DataAddress, DXAStream->DecodeTempBuffer ) ;

						// �t�@�C���̑O��̂݃n�t�}�����k����Ă����ꍇ�͎c���LZ���k�f�[�^���R�s�[
						if( DXA->Head.HuffmanEncodeKB != 0xff && FileH->PressDataSize > DXA->Head.HuffmanEncodeKB * 1024 * 2 )
						{
							// �𓀂����f�[�^�̓��A��딼�����ړ�����
							_MEMMOVE( 
								( BYTE * )DXAStream->DecodeTempBuffer + FileH->PressDataSize - DXA->Head.HuffmanEncodeKB * 1024,
								( BYTE * )DXAStream->DecodeTempBuffer + DXA->Head.HuffmanEncodeKB * 1024,
								DXA->Head.HuffmanEncodeKB * 1024
							) ;

							// �c���LZ���k�f�[�^��]��
							_MEMCPY(
								( BYTE * )DXAStream->DecodeTempBuffer + DXA->Head.HuffmanEncodeKB * 1024,
								( BYTE * )DXA->MemoryImage + DXA->Head.DataStartAddress + FileH->DataAddress + FileH->HuffPressDataSize,
								( size_t )( FileH->PressDataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 )
							) ;
						}

						// ��
						DXA_Decode( DXAStream->DecodeTempBuffer, DXAStream->DecodeDataBuffer ) ;
				
						// ��Ɨp�������̉��
						DXFREE( DXAStream->DecodeTempBuffer ) ;
						DXAStream->DecodeTempBuffer = NULL ;
					}
				}
				else
				{
					// ���k�f�[�^�̈ʒu�փt�@�C���|�C���^���ړ�
					DXAStream->ASyncReadFileAddress = DXA->Head.DataStartAddress + FileH->DataAddress ;
					ReadOnlyFileAccessSeek( DXAStream->ReadOnlyFilePointer, ( LONGLONG )DXAStream->ASyncReadFileAddress, SEEK_SET ) ;

					// �񓯊��̏ꍇ�͓ǂݍ��݂ƌ�������ʁX�ɍs��
					if( DXAStream->UseASyncReadFlag == TRUE )
					{
						// �t�@�C���̑O��̂݃n�t�}�����k����Ă��邩�ǂ����œǂݍ��ޗe�ʂ𕪊�
						if( DXA->Head.HuffmanEncodeKB != 0xff && FileH->PressDataSize > DXA->Head.HuffmanEncodeKB * 1024 * 2 )
						{
							// ���k�f�[�^�����܂郁�����̈�̊m��
							DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )( FileH->PressDataSize + FileH->HuffPressDataSize + DXA->Head.HuffmanEncodeKB * 1024 * 3 ) ) ;
							if( DXAStream->DecodeTempBuffer == NULL )
							{
								goto ERR ;
							}

							// ���k�f�[�^�̓ǂݍ���
							ReadOnlyFileAccessRead( ( BYTE * )DXAStream->DecodeTempBuffer + DXA->Head.HuffmanEncodeKB * 1024 * 2, ( size_t )( FileH->HuffPressDataSize + FileH->PressDataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 ), 1, DXAStream->ReadOnlyFilePointer ) ;
						}
						else
						{
							// ���k�f�[�^�����܂郁�����̈�̊m��
							DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )( FileH->PressDataSize + FileH->HuffPressDataSize ) ) ;
							if( DXAStream->DecodeTempBuffer == NULL )
							{
								goto ERR ;
							}

							// ���k�f�[�^�̓ǂݍ���
							ReadOnlyFileAccessRead( DXAStream->DecodeTempBuffer, ( size_t )FileH->HuffPressDataSize, 1, DXAStream->ReadOnlyFilePointer ) ;
						}
						DXAStream->ASyncState = DXARC_STREAM_ASYNCSTATE_PRESSREAD ;
					}
					else
					{
						// ���k�f�[�^�����܂郁�����̈�̊m��
						DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )( FileH->PressDataSize + FileH->HuffPressDataSize ) ) ;
						if( DXAStream->DecodeTempBuffer == NULL )
						{
							goto ERR ;
						}

						// ���k�f�[�^�̓ǂݍ��݂ƌ�����
						DXA_KeyConvFileRead( DXAStream->DecodeTempBuffer, FileH->HuffPressDataSize, DXAStream->ReadOnlyFilePointer, DXAStream->NoKey ? NULL : DXAStream->Key, ( LONGLONG )FileH->DataSize ) ;

						// �n�t�}�����k�f�[�^����
						Huffman_Decode( DXAStream->DecodeTempBuffer, ( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize ) ;

						// �t�@�C���̑O��̂݃n�t�}�����k���Ă���ꍇ�͏����𕪊�
						if( DXA->Head.HuffmanEncodeKB != 0xff && FileH->PressDataSize > DXA->Head.HuffmanEncodeKB * 1024 * 2 )
						{
							// �𓀂����f�[�^�̓��A��딼�����ړ�����
							_MEMMOVE( 
								( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize + FileH->PressDataSize - DXA->Head.HuffmanEncodeKB * 1024,
								( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize + DXA->Head.HuffmanEncodeKB * 1024,
								DXA->Head.HuffmanEncodeKB * 1024 ) ;

							// �c��̃f�[�^��ǂݍ���
							DXA_KeyConvFileRead(
								( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize + DXA->Head.HuffmanEncodeKB * 1024,
								FileH->PressDataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2,
								DXAStream->ReadOnlyFilePointer, DXAStream->NoKey ? NULL : DXAStream->Key, FileH->DataSize + FileH->HuffPressDataSize ) ;
						}

						// ��
						DXA_Decode( ( BYTE * )DXAStream->DecodeTempBuffer + FileH->HuffPressDataSize, DXAStream->DecodeDataBuffer ) ;
				
						// �������̉��
						DXFREE( DXAStream->DecodeTempBuffer ) ;
						DXAStream->DecodeTempBuffer = NULL ;
					}
				}
			}
			else
			{
				// ��������ɓǂݍ��܂�Ă��邩�ǂ����ŏ����𕪊�
				if( DXA->MemoryOpenFlag == TRUE )
				{
					if( DXA->MemoryImageReadOnlyFlag )
					{
						// ���k�f�[�^�����܂郁�����̈�̊m��
						DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )FileH->PressDataSize ) ;
						if( DXAStream->DecodeTempBuffer == NULL )
						{
							goto ERR ;
						}

						// ���k�f�[�^�̓ǂݍ���
						_MEMCPY( DXAStream->DecodeTempBuffer, ( BYTE * )DXA->MemoryImage + DXA->Head.DataStartAddress + FileH->DataAddress, ( size_t )FileH->PressDataSize ) ;
						if( DXAStream->NoKey == false ) DXA_KeyConv( DXAStream->DecodeTempBuffer, ( LONGLONG )FileH->PressDataSize, ( LONGLONG )FileH->DataSize, DXAStream->Key ) ;

						// ��
						DXA_Decode( DXAStream->DecodeTempBuffer, DXAStream->DecodeDataBuffer ) ;
				
						// �������̉��
						DXFREE( DXAStream->DecodeTempBuffer ) ;
						DXAStream->DecodeTempBuffer = NULL ;
					}
					else
					{
						// ��
						DXA_Decode( (BYTE *)DXA->MemoryImage + DXA->Head.DataStartAddress + FileH->DataAddress, DXAStream->DecodeDataBuffer ) ;
					}
				}
				else
				{
					// ���k�f�[�^�����܂郁�����̈�̊m��
					DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )FileH->PressDataSize ) ;
					if( DXAStream->DecodeTempBuffer == NULL )
					{
						goto ERR ;
					}

					// ���k�f�[�^�̈ʒu�փt�@�C���|�C���^���ړ�
					DXAStream->ASyncReadFileAddress = DXA->Head.DataStartAddress + FileH->DataAddress;
					ReadOnlyFileAccessSeek( DXAStream->ReadOnlyFilePointer, ( LONGLONG )DXAStream->ASyncReadFileAddress, SEEK_SET ) ;

					// �񓯊��̏ꍇ�͓ǂݍ��݂ƌ�������ʁX�ɍs��
					if( DXAStream->UseASyncReadFlag == TRUE )
					{
						// ���k�f�[�^�̓ǂݍ���
						ReadOnlyFileAccessRead( DXAStream->DecodeTempBuffer, ( size_t )FileH->PressDataSize, 1, DXAStream->ReadOnlyFilePointer ) ;
						DXAStream->ASyncState = DXARC_STREAM_ASYNCSTATE_PRESSREAD ;
					}
					else
					{
						// ���k�f�[�^�̓ǂݍ��݂ƌ�����
						DXA_KeyConvFileRead( DXAStream->DecodeTempBuffer, FileH->PressDataSize, DXAStream->ReadOnlyFilePointer, DXAStream->NoKey ? NULL : DXAStream->Key, ( LONGLONG )FileH->DataSize ) ;

						// ��
						DXA_Decode( DXAStream->DecodeTempBuffer, DXAStream->DecodeDataBuffer ) ;
				
						// �������̉��
						DXFREE( DXAStream->DecodeTempBuffer ) ;
						DXAStream->DecodeTempBuffer = NULL ;
					}
				}
			}
		}
		else
		// �n�t�}�����k��������Ă��邩�ǂ����ŏ����𕪊�
		if( FileH->HuffPressDataSize != NONE_PAL )
		{
			// ��������ɓǂݍ��܂�Ă��邩�ǂ����ŏ����𕪊�
			if( DXA->MemoryOpenFlag == TRUE )
			{
				if( DXA->MemoryImageReadOnlyFlag )
				{
					// ���k�f�[�^�����܂郁�����̈�̊m��
					DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )FileH->HuffPressDataSize ) ;
					if( DXAStream->DecodeTempBuffer == NULL )
					{
						goto ERR ;
					}

					// ���k�f�[�^�̃R�s�[�ƌ�����
					_MEMCPY( DXAStream->DecodeTempBuffer, ( BYTE * )DXA->MemoryImage + DXA->Head.DataStartAddress + FileH->DataAddress, ( size_t )FileH->HuffPressDataSize ) ;
					if( DXAStream->NoKey == false ) DXA_KeyConv( DXAStream->DecodeTempBuffer, ( LONGLONG )FileH->HuffPressDataSize, ( LONGLONG )FileH->DataSize, DXAStream->Key ) ;

					// �n�t�}�����k�f�[�^����
					Huffman_Decode( DXAStream->DecodeTempBuffer, DXAStream->DecodeDataBuffer ) ;

					// �t�@�C���̑O��̂݃n�t�}�����k���Ă���ꍇ�͏����𕪊�
					if( DXA->Head.HuffmanEncodeKB != 0xff && FileH->DataSize > DXA->Head.HuffmanEncodeKB * 1024 * 2 )
					{
						// �𓀂����f�[�^�̓��A��딼�����ړ�����
						_MEMMOVE( 
							( BYTE * )DXAStream->DecodeDataBuffer + FileH->DataSize - DXA->Head.HuffmanEncodeKB * 1024,
							( BYTE * )DXAStream->DecodeDataBuffer + DXA->Head.HuffmanEncodeKB * 1024,
							DXA->Head.HuffmanEncodeKB * 1024 ) ;

						// �c��̃f�[�^���R�s�[����
						_MEMCPY(
							( BYTE * )DXAStream->DecodeDataBuffer + DXA->Head.HuffmanEncodeKB * 1024,
							( BYTE * )DXA->MemoryImage + DXA->Head.DataStartAddress + FileH->DataAddress + FileH->HuffPressDataSize,
							( size_t )( FileH->DataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 )
						) ;
						if( DXAStream->NoKey == false ) DXA_KeyConv( ( BYTE * )DXAStream->DecodeDataBuffer + DXA->Head.HuffmanEncodeKB * 1024, ( LONGLONG )( FileH->DataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 ), ( LONGLONG )( FileH->DataSize + FileH->HuffPressDataSize ), DXAStream->Key ) ;
					}
				
					// ��Ɨp�������̉��
					DXFREE( DXAStream->DecodeTempBuffer ) ;
					DXAStream->DecodeTempBuffer = NULL ;
				}
				else
				{
					// �n�t�}�����k�f�[�^����
					Huffman_Decode( ( BYTE * )DXA->MemoryImage + DXA->Head.DataStartAddress + FileH->DataAddress, DXAStream->DecodeDataBuffer ) ;

					// �t�@�C���̑O��̂݃n�t�}�����k���Ă���ꍇ�͏����𕪊�
					if( DXA->Head.HuffmanEncodeKB != 0xff && FileH->DataSize > DXA->Head.HuffmanEncodeKB * 1024 * 2 )
					{
						// �𓀂����f�[�^�̓��A��딼�����ړ�����
						_MEMMOVE( 
							( BYTE * )DXAStream->DecodeDataBuffer + FileH->DataSize - DXA->Head.HuffmanEncodeKB * 1024,
							( BYTE * )DXAStream->DecodeDataBuffer + DXA->Head.HuffmanEncodeKB * 1024,
							DXA->Head.HuffmanEncodeKB * 1024 ) ;

						// �c��̃f�[�^���R�s�[����
						_MEMCPY(
							( BYTE * )DXAStream->DecodeDataBuffer + DXA->Head.HuffmanEncodeKB * 1024,
							( BYTE * )DXA->MemoryImage + DXA->Head.DataStartAddress + FileH->DataAddress + FileH->HuffPressDataSize,
							( size_t )( FileH->DataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 )
						) ;
					}
				}
			}
			else
			{
				// ���k�f�[�^�̈ʒu�փt�@�C���|�C���^���ړ�
				DXAStream->ASyncReadFileAddress = DXA->Head.DataStartAddress + FileH->DataAddress ;
				ReadOnlyFileAccessSeek( DXAStream->ReadOnlyFilePointer, ( LONGLONG )DXAStream->ASyncReadFileAddress, SEEK_SET ) ;

				// �񓯊��̏ꍇ�͓ǂݍ��݂ƌ�������ʁX�ɍs��
				if( DXAStream->UseASyncReadFlag == TRUE )
				{
					// �t�@�C���̑O��̂݃n�t�}�����k����Ă��邩�ǂ����œǂݍ��ޗe�ʂ𕪊�
					if( DXA->Head.HuffmanEncodeKB != 0xff && FileH->DataSize > DXA->Head.HuffmanEncodeKB * 1024 * 2 )
					{
						// ���k�f�[�^�����܂郁�����̈�̊m��
						DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )( FileH->HuffPressDataSize + FileH->DataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 ) ) ;
						if( DXAStream->DecodeTempBuffer == NULL )
						{
							goto ERR ;
						}

						// ���k�f�[�^�̓ǂݍ���
						ReadOnlyFileAccessRead( DXAStream->DecodeTempBuffer, ( size_t )( FileH->HuffPressDataSize + FileH->DataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2 ), 1, DXAStream->ReadOnlyFilePointer ) ;
					}
					else
					{
						// ���k�f�[�^�����܂郁�����̈�̊m��
						DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )FileH->HuffPressDataSize ) ;
						if( DXAStream->DecodeTempBuffer == NULL )
						{
							goto ERR ;
						}

						// ���k�f�[�^�̓ǂݍ���
						ReadOnlyFileAccessRead( DXAStream->DecodeTempBuffer, ( size_t )FileH->HuffPressDataSize, 1, DXAStream->ReadOnlyFilePointer ) ;
					}
					DXAStream->ASyncState = DXARC_STREAM_ASYNCSTATE_PRESSREAD ;
				}
				else
				{
					// ���k�f�[�^�����܂郁�����̈�̊m��
					DXAStream->DecodeTempBuffer = DXALLOC( ( size_t )FileH->HuffPressDataSize ) ;
					if( DXAStream->DecodeTempBuffer == NULL )
					{
						goto ERR ;
					}

					// ���k�f�[�^�̓ǂݍ��݂ƌ�����
					DXA_KeyConvFileRead( DXAStream->DecodeTempBuffer, FileH->HuffPressDataSize, DXAStream->ReadOnlyFilePointer, DXAStream->NoKey ? NULL : DXAStream->Key, ( LONGLONG )FileH->DataSize ) ;

					// �n�t�}�����k�f�[�^����
					Huffman_Decode( DXAStream->DecodeTempBuffer, DXAStream->DecodeDataBuffer ) ;
				
					// �t�@�C���̑O��̂݃n�t�}�����k���Ă���ꍇ�͏����𕪊�
					if( DXA->Head.HuffmanEncodeKB != 0xff && FileH->DataSize > DXA->Head.HuffmanEncodeKB * 1024 * 2 )
					{
						// �𓀂����f�[�^�̓��A��딼�����ړ�����
						_MEMMOVE( 
							( BYTE * )DXAStream->DecodeDataBuffer + FileH->DataSize - DXA->Head.HuffmanEncodeKB * 1024,
							( BYTE * )DXAStream->DecodeDataBuffer + DXA->Head.HuffmanEncodeKB * 1024,
							DXA->Head.HuffmanEncodeKB * 1024 ) ;
						
						// �c��̃f�[�^��ǂݍ���
						DXA_KeyConvFileRead(
							( BYTE * )DXAStream->DecodeDataBuffer + DXA->Head.HuffmanEncodeKB * 1024,
							FileH->DataSize - DXA->Head.HuffmanEncodeKB * 1024 * 2,
							DXAStream->ReadOnlyFilePointer, DXAStream->NoKey ? NULL : DXAStream->Key, FileH->DataSize + FileH->HuffPressDataSize ) ;
					}

					// �������̉��
					DXFREE( DXAStream->DecodeTempBuffer ) ;
					DXAStream->DecodeTempBuffer = NULL ;
				}
			}
		}
	}

	// �I��
	return 0 ;

ERR :
	if( DXAStream->DecodeDataBuffer != NULL )
	{
		DXFREE( DXAStream->DecodeDataBuffer ) ;
		DXAStream->DecodeDataBuffer = NULL ;
	}
	if( DXAStream->DecodeTempBuffer != NULL )
	{
		DXFREE( DXAStream->DecodeTempBuffer ) ;
		DXAStream->DecodeTempBuffer = NULL ;
	}

	// �G���[�I��
	return -1 ;
}

// �A�[�J�C�u�t�@�C�����̃t�@�C�������
extern int DXA_STREAM_Terminate( DXARC_STREAM *DXAStream )
{
	// �񓯊��ǂݍ��݂ŏ�Ԃ��܂��ҋ@��Ԃł͂Ȃ�������ҋ@��ԂɂȂ�܂ő҂�
	if( DXAStream->UseASyncReadFlag == TRUE && DXAStream->ASyncState != DXARC_STREAM_ASYNCSTATE_IDLE )
	{
		while( DXA_STREAM_IdleCheck( DXAStream ) == FALSE )
		{
			Thread_Sleep( 1 ) ;
		}
	}

	// �������̉��
	if( DXAStream->DecodeDataBuffer != NULL )
	{
		DXFREE( DXAStream->DecodeDataBuffer ) ;
		DXAStream->DecodeDataBuffer = NULL ;
	}

	if( DXAStream->DecodeTempBuffer != NULL )
	{
		DXFREE( DXAStream->DecodeTempBuffer ) ;
		DXAStream->DecodeTempBuffer = NULL ;
	}

	// �t�@�C�������
	if( DXAStream->Archive->MemoryOpenFlag == FALSE )
	{
		ReadOnlyFileAccessClose( DXAStream->ReadOnlyFilePointer ) ;
		DXAStream->ReadOnlyFilePointer = 0 ;
	}

	// �[��������
	_MEMSET( DXAStream, 0, sizeof( DXARC_STREAM ) ) ;

	// �I��
	return 0 ;
}

// �t�@�C���̓��e��ǂݍ���
extern int DXA_STREAM_Read( DXARC_STREAM *DXAStream, void *Buffer, size_t ReadLength )
{
	size_t ReadSize ;
	ULONGLONG DataSize ;
	ULONGLONG DataStartAddress ;
	ULONGLONG DataAddress ;

	// �񓯊��ǂݍ��݂ŏ�Ԃ��܂��ҋ@��Ԃł͂Ȃ�������ҋ@��ԂɂȂ�܂ő҂�
	if( DXAStream->UseASyncReadFlag == TRUE && DXAStream->ASyncState != DXARC_STREAM_ASYNCSTATE_IDLE )
	{
		while( DXA_STREAM_IdleCheck( DXAStream ) == FALSE )
		{
			Thread_Sleep( 1 ) ;
		}
	}

	{
		DataSize = DXAStream->FileHead->DataSize ;
		DataAddress = DXAStream->FileHead->DataAddress ;
		DataStartAddress = DXAStream->Archive->Head.DataStartAddress ;
	}

	// EOF �t���O�������Ă�����O��Ԃ�
	if( DXAStream->EOFFlag == TRUE )
	{
		return 0 ;
	}

	// EOF ���o
	if( DataSize == DXAStream->FilePoint )
	{
		DXAStream->EOFFlag = TRUE ;
		return 0 ;
	}

	// �f�[�^��ǂݍ��ޗʂ�ݒ肷��
	ReadSize = ReadLength < DataSize - DXAStream->FilePoint ? ReadLength : ( size_t )( DataSize - DXAStream->FilePoint ) ;

	// �f�[�^�����k����Ă������ǂ����ŏ����𕪊�
	if( DXAStream->DecodeDataBuffer != NULL )
	{
		// �f�[�^���R�s�[����
		_MEMCPY( Buffer, (BYTE *)DXAStream->DecodeDataBuffer + DXAStream->FilePoint, ReadSize ) ;
	}
	else
	{
		// ��������Ƀf�[�^�����邩�ǂ����ŏ����𕪊�
		if( DXAStream->Archive->MemoryOpenFlag == TRUE )
		{
			// ��������ɂ���ꍇ

			// �f�[�^���R�s�[����
			_MEMCPY( Buffer, (BYTE *)DXAStream->Archive->MemoryImage + DataStartAddress + DataAddress + DXAStream->FilePoint, ReadSize ) ;

			if( DXAStream->Archive->MemoryImageReadOnlyFlag )
			{
				if( DXAStream->NoKey == false ) DXA_KeyConv( Buffer, ( LONGLONG )ReadSize, ( LONGLONG )( DataSize + DXAStream->FilePoint ), DXAStream->Key ) ;
			}
		}
		else
		{
			// �t�@�C������ǂݍ���ł���ꍇ

			// �A�[�J�C�u�t�@�C���|�C���^�ƁA���z�t�@�C���|�C���^����v���Ă��邩���ׂ�
			// ��v���Ă��Ȃ�������A�[�J�C�u�t�@�C���|�C���^���ړ�����
			DXAStream->ASyncReadFileAddress = DataAddress + DataStartAddress + DXAStream->FilePoint ;
			if( ( ULONGLONG )ReadOnlyFileAccessTell( DXAStream->ReadOnlyFilePointer ) != DXAStream->ASyncReadFileAddress )
			{
				ReadOnlyFileAccessSeek( DXAStream->ReadOnlyFilePointer, ( LONGLONG )DXAStream->ASyncReadFileAddress, SEEK_SET ) ;
			}

			// �񓯊��ǂݍ��݂̏ꍇ�Ɠ����ǂݍ��݂̏ꍇ�ŏ����𕪊�
			if( DXAStream->UseASyncReadFlag )
			{
				// �t�@�C������ǂݍ���
				ReadOnlyFileAccessRead( Buffer, ReadSize, 1, DXAStream->ReadOnlyFilePointer ) ;
				DXAStream->ReadBuffer = Buffer;
				DXAStream->ReadSize = ( int )ReadSize;
				DXAStream->ASyncState = DXARC_STREAM_ASYNCSTATE_READ ;
			}
			else
			{
				// �f�[�^��ǂݍ���
				DXA_KeyConvFileRead( Buffer, ReadSize, DXAStream->ReadOnlyFilePointer, DXAStream->NoKey ? NULL : DXAStream->Key, ( LONGLONG )( DataSize + DXAStream->FilePoint ) ) ;
			}
		}
	}
	
	// EOF �t���O��|��
	DXAStream->EOFFlag = FALSE ;

	// �ǂݍ��񂾕������t�@�C���|�C���^���ړ�����
	DXAStream->FilePoint += ( int )ReadSize ;
	
	// �ǂݍ��񂾗e�ʂ�Ԃ�
	return ( int )ReadSize ;
}
	
// �t�@�C���|�C���^��ύX����
extern	int DXA_STREAM_Seek( DXARC_STREAM *DXAStream, LONGLONG SeekPoint, int SeekMode )
{
	ULONGLONG DataSize ;

	// �񓯊��ǂݍ��݂ŏ�Ԃ��܂��ҋ@��Ԃł͂Ȃ�������ҋ@��ԂɂȂ�܂ő҂�
	if( DXAStream->UseASyncReadFlag == TRUE && DXAStream->ASyncState != DXARC_STREAM_ASYNCSTATE_IDLE )
	{
		while( DXA_STREAM_IdleCheck( DXAStream ) == FALSE )
		{
			Thread_Sleep( 1 ) ;
		}
	}

	{
		DataSize = DXAStream->FileHead->DataSize ;
	}

	// �V�[�N�^�C�v�ɂ���ď����𕪊�
	switch( SeekMode )
	{
	case SEEK_SET : break ;		
	case SEEK_CUR : SeekPoint += ( LONGLONG )( DXAStream->FilePoint ) ; break ;
	case SEEK_END :	SeekPoint  = ( LONGLONG )( DataSize + SeekPoint ) ; break ;
	}
	
	// �␳
	if( SeekPoint > ( LONGLONG )DataSize ) SeekPoint = ( LONGLONG )DataSize ;
	if( SeekPoint < 0 ) SeekPoint = 0 ;
	
	// �Z�b�g
	DXAStream->FilePoint = ( ULONGLONG )SeekPoint ;
	
	// EOF�t���O��|��
	DXAStream->EOFFlag = FALSE ;
	
	// �I��
	return 0 ;
}

// ���݂̃t�@�C���|�C���^�𓾂�
extern	LONGLONG DXA_STREAM_Tell( DXARC_STREAM *DXAStream )
{
	// �񓯊��ǂݍ��݂ŏ�Ԃ��܂��ҋ@��Ԃł͂Ȃ�������ҋ@��ԂɂȂ�܂ő҂�
	if( DXAStream->UseASyncReadFlag == TRUE && DXAStream->ASyncState != DXARC_STREAM_ASYNCSTATE_IDLE )
	{
		while( DXA_STREAM_IdleCheck( DXAStream ) == FALSE )
		{
			Thread_Sleep( 1 ) ;
		}
	}

	return ( LONGLONG )DXAStream->FilePoint ;
}

// �t�@�C���̏I�[�ɗ��Ă��邩�A�̃t���O�𓾂�
extern	int DXA_STREAM_Eof( DXARC_STREAM *DXAStream )
{
	// �񓯊��ǂݍ��݂ŏ�Ԃ��܂��ҋ@��Ԃł͂Ȃ�������ҋ@��ԂɂȂ�܂ő҂�
	if( DXAStream->UseASyncReadFlag == TRUE && DXAStream->ASyncState != DXARC_STREAM_ASYNCSTATE_IDLE )
	{
		while( DXA_STREAM_IdleCheck( DXAStream ) == FALSE )
		{
			Thread_Sleep( 1 ) ;
		}
	}

	return DXAStream->EOFFlag ? EOF : 0 ;
}

// �ǂݍ��ݏ������������Ă��邩�ǂ����𒲂ׂ�
extern	int	DXA_STREAM_IdleCheck( DXARC_STREAM *DXAStream )
{
	// �񓯊��ǂݍ��݂ł͂Ȃ��ꍇ�͉������� TRUE ��Ԃ�
	if( DXAStream->UseASyncReadFlag == FALSE )
	{
		return TRUE ;
	}

	// ��Ԃɂ���ď����𕪊�
	switch( DXAStream->ASyncState )
	{
	case DXARC_STREAM_ASYNCSTATE_IDLE:			// �ҋ@���
		return TRUE;

	case DXARC_STREAM_ASYNCSTATE_PRESSREAD:		// ���k�f�[�^�ǂݍ��ݑ҂�

		// �ǂݍ��ݏI���҂�
		if( ReadOnlyFileAccessIdleCheck( DXAStream->ReadOnlyFilePointer ) == FALSE )
		{
			return FALSE;
		}

		// ���k����Ă��邩�ǂ����ŏ����𕪊�
		if( DXAStream->FileHead->PressDataSize != NONE_PAL )
		{
			// �n�t�}�����k������Ă��邩�ǂ����ŏ����𕪊�
			if( DXAStream->FileHead->HuffPressDataSize != NONE_PAL )
			{
				// �t�@�C���̑O��̂݃n�t�}�����k����Ă��邩�ǂ����ŏ����𕪊�
				if( DXAStream->Archive->Head.HuffmanEncodeKB != 0xff && DXAStream->FileHead->PressDataSize > DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2 )
				{
					// ��������
					if( DXAStream->NoKey == false ) DXA_KeyConv( ( BYTE * )DXAStream->DecodeTempBuffer + DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2, ( LONGLONG )( DXAStream->FileHead->HuffPressDataSize + DXAStream->FileHead->PressDataSize - DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2 ), ( LONGLONG )DXAStream->FileHead->DataSize, DXAStream->Key ) ;

					// �n�t�}�����k�f�[�^����
					Huffman_Decode( ( BYTE * )DXAStream->DecodeTempBuffer + DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2, ( BYTE * )DXAStream->DecodeTempBuffer ) ;

					// LZ���k�f�[�^�̑O��ɉ𓀂����f�[�^��]��
					_MEMCPY(
						( BYTE * )DXAStream->DecodeTempBuffer + DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2 + DXAStream->FileHead->HuffPressDataSize + DXAStream->FileHead->PressDataSize - DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2,
						( BYTE * )DXAStream->DecodeTempBuffer + DXAStream->Archive->Head.HuffmanEncodeKB * 1024,
						DXAStream->Archive->Head.HuffmanEncodeKB * 1024
					) ;
					_MEMCPY(
						( BYTE * )DXAStream->DecodeTempBuffer + DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2 + DXAStream->FileHead->HuffPressDataSize - DXAStream->Archive->Head.HuffmanEncodeKB * 1024,
						( BYTE * )DXAStream->DecodeTempBuffer,
						DXAStream->Archive->Head.HuffmanEncodeKB * 1024
					) ;

					// ��
					DXA_Decode( ( BYTE * )DXAStream->DecodeTempBuffer + DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2 + DXAStream->FileHead->HuffPressDataSize - DXAStream->Archive->Head.HuffmanEncodeKB * 1024, DXAStream->DecodeDataBuffer ) ;
				}
				else
				{
					// ��������
					if( DXAStream->NoKey == false ) DXA_KeyConv( DXAStream->DecodeTempBuffer, ( LONGLONG )DXAStream->FileHead->HuffPressDataSize, ( LONGLONG )DXAStream->FileHead->DataSize, DXAStream->Key ) ;

					// �n�t�}�����k�f�[�^����
					Huffman_Decode( DXAStream->DecodeTempBuffer, ( BYTE * )DXAStream->DecodeTempBuffer + DXAStream->FileHead->HuffPressDataSize ) ;

					// ��
					DXA_Decode( ( BYTE * )DXAStream->DecodeTempBuffer + DXAStream->FileHead->HuffPressDataSize, DXAStream->DecodeDataBuffer ) ;
				}
			}
			else
			{
				// ��������
				if( DXAStream->NoKey == false ) DXA_KeyConv( DXAStream->DecodeTempBuffer, ( LONGLONG )DXAStream->FileHead->PressDataSize, ( LONGLONG )DXAStream->FileHead->DataSize, DXAStream->Key ) ;

				// ��
				DXA_Decode( DXAStream->DecodeTempBuffer, DXAStream->DecodeDataBuffer ) ;
			}
		}
		else
		// �n�t�}�����k��������Ă��邩�ǂ����ŏ����𕪊�
		if( DXAStream->FileHead->HuffPressDataSize != NONE_PAL )
		{
			// �t�@�C���̑O��̂݃n�t�}�����k����Ă��邩�ǂ����ŏ����𕪊�
			if( DXAStream->Archive->Head.HuffmanEncodeKB != 0xff && DXAStream->FileHead->DataSize > DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2 )
			{
				// ��������
				if( DXAStream->NoKey == false ) DXA_KeyConv( DXAStream->DecodeTempBuffer, ( LONGLONG )( DXAStream->FileHead->HuffPressDataSize + DXAStream->FileHead->DataSize - DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2 ), ( LONGLONG )DXAStream->FileHead->DataSize, DXAStream->Key ) ;

				// �n�t�}�����k�f�[�^����
				Huffman_Decode( DXAStream->DecodeTempBuffer, ( BYTE * )DXAStream->DecodeDataBuffer ) ;

				// �𓀂����f�[�^���㔼�����Ɉړ�
				_MEMCPY(
					( BYTE * )DXAStream->DecodeDataBuffer + DXAStream->FileHead->DataSize - DXAStream->Archive->Head.HuffmanEncodeKB * 1024,
					( BYTE * )DXAStream->DecodeDataBuffer + DXAStream->Archive->Head.HuffmanEncodeKB * 1024,
					DXAStream->Archive->Head.HuffmanEncodeKB * 1024
				) ;

				// �c��̕������R�s�[
				_MEMCPY(
					( BYTE * )DXAStream->DecodeDataBuffer + DXAStream->Archive->Head.HuffmanEncodeKB * 1024,
					( BYTE * )DXAStream->DecodeTempBuffer + DXAStream->FileHead->HuffPressDataSize,
					( size_t )( DXAStream->FileHead->DataSize - DXAStream->Archive->Head.HuffmanEncodeKB * 1024 * 2 )
				) ;
			}
			else
			{
				// ��������
				if( DXAStream->NoKey == false ) DXA_KeyConv( DXAStream->DecodeTempBuffer, ( LONGLONG )DXAStream->FileHead->HuffPressDataSize, ( LONGLONG )DXAStream->FileHead->DataSize, DXAStream->Key ) ;

				// �n�t�}�����k�f�[�^����
				Huffman_Decode( DXAStream->DecodeTempBuffer, DXAStream->DecodeDataBuffer ) ;
			}
		}
	
		// �������̉��
		DXFREE( DXAStream->DecodeTempBuffer ) ;
		DXAStream->DecodeTempBuffer = NULL ;

		// ��Ԃ�ҋ@��Ԃɂ���
		DXAStream->ASyncState = DXARC_STREAM_ASYNCSTATE_IDLE;
		return TRUE;

	case DXARC_STREAM_ASYNCSTATE_READ:			// �ǂݍ��ݑ҂�

		// �ǂݍ��ݏI���҂�
		if( ReadOnlyFileAccessIdleCheck( DXAStream->ReadOnlyFilePointer ) == FALSE )
		{
			return FALSE;
		}

		// �ǂݍ��ݏI������献������
		if( DXAStream->NoKey == false ) DXA_KeyConv( DXAStream->ReadBuffer, ( LONGLONG )DXAStream->ReadSize, ( LONGLONG )( DXAStream->FileHead->DataSize + ( DXAStream->ASyncReadFileAddress - ( DXAStream->FileHead->DataAddress + DXAStream->Archive->Head.DataStartAddress ) ) ), DXAStream->Key ) ;

		// ��Ԃ�ҋ@��Ԃɂ���
		DXAStream->ASyncState = DXARC_STREAM_ASYNCSTATE_IDLE;
		return TRUE;
	}

	return TRUE ;
}

// �t�@�C���̃T�C�Y���擾����
extern	LONGLONG DXA_STREAM_Size( DXARC_STREAM *DXAStream )
{
	return ( LONGLONG )DXAStream->FileHead->DataSize ;
}







// �t���p�X�ł͂Ȃ��p�X��������t���p�X�ɕϊ�����
static int DXA_DIR_ConvertFullPath( const wchar_t *Src, wchar_t *Dest, size_t BufferBytes, int CharUp )
{
	int Result ;

	Result = ConvertFullPathW_( Src, Dest, BufferBytes, NULL ) ;
	if( CharUp )
	{
		CL_strupr( WCHAR_T_CHARCODEFORMAT, ( char * )Dest ) ;
	}

	return Result ;

#if 0
	int     i, k ;
	wchar_t iden[ FILEPATH_MAX ] ;
	wchar_t CurrentDir[ FILEPATH_MAX ] ;
	DWORD   CharCode1 ;
	int     CharBytes1 ;
	DWORD   CharCode2 ;
	int     CharBytes2 ;
	DWORD   LastCharCode ;
	int     LastCharBytes ;
	char *  LastCharAddress ;
	int     CharNum ;
	size_t	DestBytes ;

	// �J�����g�f�B���N�g���𓾂�
	_WGETCWD( CurrentDir, sizeof( CurrentDir ) ) ;
	_WCSUPR( CurrentDir ) ;
	if( Src == NULL )
	{
		_WCSCPY_S( Dest, BufferBytes, CurrentDir ) ;
		goto END ;
	}

	i = 0 ;
	k = 0 ;

	DestBytes = 0 ;

	// �P�����ڂƂQ�����ڂ��擾
	CharCode1 = GetCharCode( ( const char * )&( ( BYTE * )Src )[ 0 ], WCHAR_T_CHARCODEFORMAT, &CharBytes1 ) ;
	CharCode2 = 0 ;
	if( CharCode1 != 0 )
	{
		CharCode2 = GetCharCode( ( const char * )&( ( BYTE * )Src )[ CharBytes1 ], WCHAR_T_CHARCODEFORMAT, &CharBytes2 ) ;
	}

	// �ŏ��Ɂw\�x���́w/�x���Q��A���ő����Ă���ꍇ�̓l�b�g���[�N����Ă���Ɣ��f

	if( ( CharCode1 == '\\' && CharCode2 == '\\' ) ||
		( CharCode1 == '/'  && CharCode2 == '/'  ) )
	{
		DestBytes += PutCharCode( '\\', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;
		PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;

		i += CharBytes1 + CharBytes2 ;
	}
	else
	// �ŏ����w\�x���́w/�x�̏ꍇ�̓J�����g�h���C�u�̃��[�g�f�B���N�g���܂ŗ�����
	if( CharCode1 == '\\' || CharCode1 == '/' )
	{
		DWORD CurCharCode1 ;
		DWORD CurCharCode2 ;
		int   CurCharBytes1 ;
		int   CurCharBytes2 ;

		CurCharCode1 = GetCharCode( ( char * )&( ( BYTE * )CurrentDir )[ 0             ], WCHAR_T_CHARCODEFORMAT, &CurCharBytes1 ) ;
		CurCharCode2 = GetCharCode( ( char * )&( ( BYTE * )CurrentDir )[ CurCharBytes1 ], WCHAR_T_CHARCODEFORMAT, &CurCharBytes2 ) ;
		DestBytes += PutCharCode( CurCharCode1, WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;
		DestBytes += PutCharCode( CurCharCode2, WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;
		PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;

		i += CharBytes1 ;
	}
	else
	// �h���C�u����������Ă����炻�̃h���C�u��
	if( CharCode2 == ':' )
	{
		DestBytes += PutCharCode( CharUp ? CHARUP( CharCode1 ) : CharCode1, WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;
		DestBytes += PutCharCode(                  CharCode2              , WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;
		PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;

		i += CharBytes1 + CharBytes2 ;

		// : �̌�� \ �}�[�N�͔�΂�
		CharCode1 = GetCharCode( ( const char * )&( ( BYTE * )Src )[ i ], WCHAR_T_CHARCODEFORMAT, &CharBytes1 ) ;
		if( CharCode1 == '\\' )
		{
			i += CharBytes1 ;
		}
	}
	else
	// ����ȊO�̏ꍇ�̓J�����g�f�B���N�g��
	{
		_WCSCPY_S( Dest, BufferBytes, CurrentDir ) ;
		DestBytes += _WCSLEN( Dest ) * sizeof( wchar_t ) ;

		CharNum = GetStringCharNum(  ( const char * )CurrentDir, WCHAR_T_CHARCODEFORMAT ) ;
		if( CharNum != 0 )
		{
			LastCharAddress = ( char * )GetStringCharAddress( ( const char * )CurrentDir, WCHAR_T_CHARCODEFORMAT, CharNum - 1 ) ;
			LastCharCode    = GetCharCode( LastCharAddress, WCHAR_T_CHARCODEFORMAT, &LastCharBytes ) ;
			if( LastCharCode == '\\' || LastCharCode == '/' )
			{
				PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, LastCharAddress, BUFFERBYTES_CANCEL ) ;
				DestBytes -= LastCharBytes ;
			}
		}
	}

	for(;;)
	{
		CharCode1 = GetCharCode( ( const char * )&( ( BYTE * )Src )[ i ], WCHAR_T_CHARCODEFORMAT, &CharBytes1 ) ;
		switch( CharCode1 )
		{
		case '\0' :
			if( k != 0 )
			{
				CharCode2 = GetCharCode( ( const char * )&( ( BYTE * )Dest )[ 0 ], WCHAR_T_CHARCODEFORMAT, &CharBytes2 ) ;
				if( CharCode2 != '\0' )
				{
					DestBytes += PutCharCode( '\\', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;
				}
				_WCSCPY_S( ( wchar_t * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes, iden ) ;
				DestBytes = _WCSLEN( Dest ) * sizeof( wchar_t ) ;
				k  = 0 ;
			}
			goto END ;

		case '\\' :
		case '/' :
			// �����񂪖���������X�L�b�v
			if( k == 0 )
			{
				i += CharBytes1 ;
				break ;
			}
			if( _WCSCMP( iden, L"." ) == 0 )
			{
				// �Ȃɂ����Ȃ�
			}
			else
			if( _WCSCMP( iden, L".." ) == 0 )
			{
				// ��󂢃f�B���N�g����
				PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;
				CharNum         = GetStringCharNum(  ( const char * )Dest, WCHAR_T_CHARCODEFORMAT ) ;
				LastCharAddress = ( char * )GetStringCharAddress( ( const char * )Dest, WCHAR_T_CHARCODEFORMAT, CharNum - 1 ) ;
				LastCharCode    = GetCharCode( LastCharAddress, WCHAR_T_CHARCODEFORMAT, &LastCharBytes ) ;
				DestBytes -= LastCharBytes ;
				for(;;)
				{
					if( LastCharCode == '\\' || LastCharCode == '/' || LastCharCode == ':' )
					{
						break ;
					}

					PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;
					CharNum -- ;
					LastCharAddress = ( char * )GetStringCharAddress( ( const char * )Dest, WCHAR_T_CHARCODEFORMAT, CharNum - 1 ) ;
					LastCharCode    = GetCharCode( LastCharAddress, WCHAR_T_CHARCODEFORMAT, &LastCharBytes ) ;
					DestBytes -= LastCharBytes ;
				}

				if( LastCharCode != ':' )
				{
					PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;
				}
				else
				{
					if( BufferBytes - DestBytes > ( size_t )LastCharBytes )
					{
						DestBytes += LastCharBytes ;
					}
				}
			}
			else
			{
				CharCode2 = GetCharCode( ( const char * )&( ( BYTE * )Dest )[ 0 ], WCHAR_T_CHARCODEFORMAT, &CharBytes2 ) ;
				if( CharCode2 != '\0' )
				{
					DestBytes += PutCharCode( '\\', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes ) ;
				}
				_WCSCPY_S( ( wchar_t * )&( ( BYTE * )Dest )[ DestBytes ], BufferBytes - DestBytes, iden ) ;
				DestBytes = _WCSLEN( Dest ) * sizeof( wchar_t ) ;
			}

			k = 0 ;
			i += CharBytes1 ;
			break ;
		
		default :
			k += PutCharCode( CharUp ? CHARUP( CharCode1 ) : CharCode1, WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )iden )[ k ], sizeof( iden ) - k ) ;
			     PutCharCode( '\0',                                     WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )iden )[ k ], sizeof( iden ) - k ) ;

			i += CharBytes1 ;
			break ;
		}
	}
	
END :
	// ����I��
	return 0 ;
#endif
}

// �t�@�C�������ꏏ�ɂȂ��Ă���ƕ������Ă���p�X������t�@�C�����ƃf�B���N�g���p�X�𕪊�����
// �t���p�X�ł���K�v�͖����A�t�@�C���������ł��ǂ�
// DirPath �̏I�[�� �� �}�[�N�͕t���Ȃ�
static int DXA_DIR_AnalysisFileNameAndDirPath( DXARC *DXA, const BYTE *Src, BYTE *FileName, size_t FileNameBytes, BYTE *DirPath, size_t DirPathBytes )
{
	int   i ;
	int   Last ;
	int   LastCharBytes = 0 ;
	DWORD CharCode ;
	int   CharBytes ;
	
	// �t�@�C�����𔲂��o��
	i    = 0 ;
	Last = -1 ;
	for(;;)
	{
		CharCode = GetCharCode( ( const char * )&Src[ i ], DXA->CharCodeFormat, &CharBytes ) ;
		if( CharCode == '\0' )
		{
			break ;
		}

		if( CharCode == '\\' || CharCode == '/' || CharCode == '\0' || CharCode == ':' )
		{
			Last          = i ;
			LastCharBytes = CharBytes ;
		}

		i += CharBytes ;
	}

	if( FileName != NULL )
	{
		if( Last != -1 )
		{
			if( FileNameBytes > ( size_t )( Last + LastCharBytes ) )
			{
				CL_strncpy_s( DXA->CharCodeFormat, ( char * )FileName, FileNameBytes, ( const char * )&Src[ Last + LastCharBytes ], ( int )( ( FileNameBytes - ( Last + LastCharBytes ) ) / GetCharCodeFormatUnitSize( DXA->CharCodeFormat ) ) ) ;
			}
		}
		else
		{
			CL_strncpy_s( DXA->CharCodeFormat, ( char * )FileName, FileNameBytes, ( const char * )Src, ( int )( FileNameBytes / GetCharCodeFormatUnitSize( DXA->CharCodeFormat ) ) ) ;
		}
	}
	
	// �f�B���N�g���p�X�𔲂��o��
	if( DirPath != NULL )
	{
		if( Last != -1 )
		{
			if( DirPathBytes > ( size_t )Last + 1 )
			{
				_MEMCPY( DirPath, Src, ( size_t )Last ) ;
				PutCharCode( '\0', DXA->CharCodeFormat, ( char * )&DirPath[ Last ], BUFFERBYTES_CANCEL ) ;
			}
		}
		else
		{
			PutCharCode( '\0', DXA->CharCodeFormat, ( char * )&DirPath[ 0 ], DirPathBytes ) ;
		}
	}
	
	// �I��
	return 0 ;
}

// CmpStr �̏����� Src ���K�����邩�ǂ����𒲂ׂ�( 0:�K������  -1:�K�����Ȃ� )
static int DXA_DIR_FileNameCmp( DXARC *DXA, const BYTE *Src, const BYTE *CmpStr )
{
	const BYTE *s, *c ;
	DWORD SrcCharCode ;
	int   SrcCharBytes ;
	DWORD CmpCharCode ;
	int   CmpCharBytes ;

	s = Src ;
	c = CmpStr ;
	for(;;)
	{
		SrcCharCode = GetCharCode( ( const char * )s, DXA->CharCodeFormat, &SrcCharBytes ) ;
		CmpCharCode = GetCharCode( ( const char * )c, DXA->CharCodeFormat, &CmpCharBytes ) ;

		if( SrcCharCode != '\0' && CmpCharCode == '\0' )
		{
			return -1 ;
		}

		if( SrcCharCode == '\0' && CmpCharCode != '\0' )
		{
			if( CmpCharCode != '*' )
			{
				return -1 ;
			}

			while( CmpCharCode == '*' )
			{
				c += CmpCharBytes ;
				CmpCharCode = GetCharCode( ( const char * )c, DXA->CharCodeFormat, &CmpCharBytes ) ;
			}
			if( CmpCharCode != '\0' )
			{
				return -1 ;
			}

			break ;
		}

		if( SrcCharCode == '\0' && CmpCharCode == '\0' )
		{
			break ;
		}

		switch( CmpCharCode )
		{
		case '?':
			c += CmpCharBytes ;
			s += SrcCharBytes ;
			break;

		case '*':
			while( CmpCharCode == '*' )
			{
				c += CmpCharBytes ;
				CmpCharCode = GetCharCode( ( const char * )c, DXA->CharCodeFormat, &CmpCharBytes ) ;
			}
			if( CmpCharCode == '\0' )
			{
				return 0 ;
			}

			while( SrcCharCode != '\0' && SrcCharCode != CmpCharCode )
			{
				s += SrcCharBytes ;
				SrcCharCode = GetCharCode( ( const char * )s, DXA->CharCodeFormat, &SrcCharBytes ) ;
			}
			if( SrcCharCode == '\0' )
			{
				return -1 ;
			}

			c += CmpCharBytes ;
			s += SrcCharBytes ;
			break;

		default:
			if( CmpCharCode != SrcCharCode )
			{
				return -1 ;
			}

			c += CmpCharBytes ;
			s += SrcCharBytes ;
			break;
		}

		if( ( CmpCharCode == '\0' && SrcCharCode != '\0' ) ||
			( CmpCharCode != '\0' && SrcCharCode == '\0' ) )
		{
			return -1 ;
		}
	}

	return 0 ;
}

// �A�[�J�C�u�t�@�C�����t�H���_�Ɍ����Ăăt�@�C�����J�����̏��𓾂�( -1:�A�[�J�C�u�Ƃ��Ă͑��݂��Ȃ�����  0:���݂��� )
static int DXA_DIR_OpenTest( const wchar_t *FilePath, int *ArchiveIndex, BYTE *ArchiveFilePath, size_t BufferBytes )
{
	int   i ;
	int   len ;
	int   arcindex ;
	wchar_t fullpath[ FILEPATH_MAX ] ;
	wchar_t fullpath_up[ FILEPATH_MAX ] ;
	wchar_t path[ FILEPATH_MAX ] ;
	wchar_t temp[ FILEPATH_MAX ] ;
	wchar_t dir[ FILEPATH_MAX ] ;
	wchar_t *p ;
	int   BackUseDirectoryPathCharValid ;
	DWORD BackUseDirectoryPathCharCode = 0 ;
	int   BackUseDirectoryPathCharBytes = 0 ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &DXARCD.CriticalSection ) ;

	// �t���p�X�𓾂�
	if( DXARCD.NotArchivePathCharUp )
	{
		DXA_DIR_ConvertFullPath( FilePath, fullpath, sizeof( fullpath ), 0 ) ;
		CL_strcpy( WCHAR_T_CHARCODEFORMAT, ( char * )fullpath_up, ( char * )fullpath ) ;
		CL_strupr( WCHAR_T_CHARCODEFORMAT, ( char * )fullpath_up ) ;
	}
	else
	{
		DXA_DIR_ConvertFullPath( FilePath, fullpath, sizeof( fullpath ), 1 ) ;
	}

	// �O��Ǝg�p����A�[�J�C�u�̃p�X�������ꍇ�͓����A�[�J�C�u���g�p����
	BackUseDirectoryPathCharValid = FALSE ;
	if( DXARCD.BackUseDirectoryPathLength != 0 && _MEMCMP( fullpath, DXARCD.BackUseDirectory, DXARCD.BackUseDirectoryPathLength ) == 0 )
	{
		BackUseDirectoryPathCharValid = TRUE ;
		BackUseDirectoryPathCharCode  = GetCharCode( ( const char * )&( ( BYTE * )fullpath )[ DXARCD.BackUseDirectoryPathLength ], WCHAR_T_CHARCODEFORMAT, &BackUseDirectoryPathCharBytes ) ;
	}
	if( BackUseDirectoryPathCharValid &&
		( BackUseDirectoryPathCharCode == '\\' || BackUseDirectoryPathCharCode == '/' ) )
	{
		// �O��g�p�����c�w�`�t�@�C�����J��
		arcindex = DXA_DIR_OpenArchive( DXARCD.BackUseDirectory, NULL, -1, FALSE, FALSE, DXARCD.BackUseArchiveIndex ) ;
		if( arcindex == -1 )
		{
			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

			return -1 ;
		}

		// �c�w�`�t�@�C��������ꏊ�ȍ~�̃p�X���쐬����
		if( DXARCD.NotArchivePathCharUp )
		{
			p = ( wchar_t * )&( ( BYTE * )fullpath_up )[ DXARCD.BackUseDirectoryPathLength + BackUseDirectoryPathCharBytes ] ;
		}
		else
		{
			p = ( wchar_t * )&( ( BYTE * )fullpath    )[ DXARCD.BackUseDirectoryPathLength + BackUseDirectoryPathCharBytes ] ;
		}
	}
	else
	{
		DWORD CharCode1 ;
		int   CharBytes1 ;
		DWORD CharCode2 ;
		int   CharBytes2 = 0 ;

		// �O��Ƃ͈Ⴄ�p�X�̏ꍇ�͈ꂩ�璲�ׂ�

		// �f�B���N�g�������ǂ��čs��
		p   = fullpath ;
		len = 0 ;
		for(;;)
		{
			// �l�b�g���[�N����Ă����ꍇ�̐�p����
			if( p - fullpath == 0 )
			{
				// fullpath �̂P�����ڂƂQ�����ڂ��擾
				CharCode1 = GetCharCode( ( const char * )&( ( BYTE * )fullpath )[ 0 ], WCHAR_T_CHARCODEFORMAT, &CharBytes1 ) ;
				CharCode2 = 0 ;
				if( CharCode1 != 0 )
				{
					CharCode2 = GetCharCode( ( const char * )&( ( BYTE * )fullpath )[ CharBytes1 ], WCHAR_T_CHARCODEFORMAT, &CharBytes2 ) ;
				}

				if( CharCode1 == '\\' && CharCode2 == '\\' )
				{
					len += PutCharCode( '\\', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )path )[ len ], sizeof( path ) - len ) ;
					len += PutCharCode( '\\', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )path )[ len ], sizeof( path ) - len ) ;
					       PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )path )[ len ], sizeof( path ) - len ) ;

					p = ( wchar_t * )( ( BYTE * )p + CharBytes1 + CharBytes2 ) ;
				}
			}

			// �f�B���N�g��������
			i = 0 ;
			for(;;)
			{
				CharCode1 = GetCharCode( ( const char * )p, WCHAR_T_CHARCODEFORMAT, &CharBytes1 ) ;
				p = ( wchar_t * )( ( BYTE * )p + CharBytes1 ) ;
				if( ( wchar_t * )( ( BYTE * )p - CharBytes1 ) != fullpath && ( CharCode1 == '\0' || CharCode1 == '/' || CharCode1 == '\\' ) )
				{
					break ;
				}

				len += PutCharCode( CharCode1, WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )path )[ len ], sizeof( path ) - len ) ;
				i   += PutCharCode( CharCode1, WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )dir  )[ i   ], sizeof( dir  ) - i ) ;

			}

			if( CharCode1 == '\0' || i == 0 )
			{
				// �N���e�B�J���Z�N�V�����̉��
				CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

				return -1 ;
			}

			PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )path )[ len ], sizeof( path ) - len ) ;
			PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )dir  )[ i   ], sizeof( dir  ) - i   ) ;

			// �t�H���_����DX�A�[�J�C�u�t�@�C�����ɂ���
			{
				int TempLen ;

				_MEMCPY( temp, path, len ) ;
				TempLen = len ;

				TempLen += PutCharCode( '.', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )temp )[ TempLen ], sizeof( temp ) - TempLen ) ;
				if( DXARCD.ArchiveExtensionLength == 0 )
				{
					if( DXARCD.NotArchivePathCharUp )
					{
						TempLen += PutCharCode( 'd',  WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )temp )[ TempLen ], sizeof( temp ) - TempLen ) ;
						TempLen += PutCharCode( 'x',  WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )temp )[ TempLen ], sizeof( temp ) - TempLen ) ;
						TempLen += PutCharCode( 'a',  WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )temp )[ TempLen ], sizeof( temp ) - TempLen ) ;
					}
					else
					{
						TempLen += PutCharCode( 'D',  WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )temp )[ TempLen ], sizeof( temp ) - TempLen ) ;
						TempLen += PutCharCode( 'X',  WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )temp )[ TempLen ], sizeof( temp ) - TempLen ) ;
						TempLen += PutCharCode( 'A',  WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )temp )[ TempLen ], sizeof( temp ) - TempLen ) ;
					}
					TempLen += PutCharCode( '\0', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )temp )[ TempLen ], sizeof( temp ) - TempLen ) ;
				}
				else
				{
					_WCSCPY_S( ( wchar_t * )&( ( BYTE * )temp )[ TempLen ], sizeof( temp ) - TempLen, DXARCD.ArchiveExtension ) ;
				}
			}

			// �c�w�`�t�@�C���Ƃ��ĊJ���Ă݂�
			arcindex = DXA_DIR_OpenArchive( temp ) ;
			if( arcindex != -1 )
			{
				break ;
			}

			// �J���Ȃ������玟�̊K�w��
			len += PutCharCode( '\\', WCHAR_T_CHARCODEFORMAT, ( char * )&( ( BYTE * )path )[ len ], sizeof( path ) - len ) ;
		}

		// �J�����獡��̏���ۑ�����
		_WCSCPY_S( DXARCD.BackUseDirectory, sizeof( DXARCD.BackUseDirectory ), temp ) ;
//		if( DXARCD.ArchiveExtensionLength == 0 )
//		{
//			_MEMCPY( DXARCD.BackUseDirectory, temp, len + ( 1 /* . */ + 3 /* DXA */ + 1 /* '\0' */ ) * sizeof( wchar_t ) ) ;
//		}
//		else
//		{
//			_MEMCPY( DXARCD.BackUseDirectory, temp, len + ( 1 /* . */ + DXARCD.ArchiveExtensionLength + 1 /* '\0' */ ) * sizeof( wchar_t ) ) ;
//		}
		DXARCD.BackUseDirectoryPathLength = len ;
		DXARCD.BackUseArchiveIndex        = arcindex ;

		if( DXARCD.NotArchivePathCharUp )
		{
			p = fullpath_up + ( p - fullpath ) ;
		}
	}

	// �����Z�b�g����
	*ArchiveIndex = arcindex;

	if( ArchiveFilePath )
	{
		int DestCharCodeFormat ;

		DestCharCodeFormat = DXARCD.Archive[ arcindex ]->Archive.CharCodeFormat ;
		ConvString( ( const char * )p, -1, WCHAR_T_CHARCODEFORMAT, ( char * )ArchiveFilePath, BufferBytes, DestCharCodeFormat ) ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

	// �I��
	return 0;
}

// �A�[�J�C�u�t�@�C�����J��
static int DXA_DIR_OpenArchive( const wchar_t *FilePath, void *FileImage, int FileSize, int FileImageCopyFlag, int FileImageReadOnly, int ArchiveIndex, int OnMemory, int ASyncThread )
{
	int					i ;
	int					index ;
	int					newindex ;
	DXARC_DIR_ARCHIVE *	arc ;
	DXARC_DIR_ARCHIVE *	tarc ;
	DXARC				temparc ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &DXARCD.CriticalSection ) ;

	// �A�[�J�C�u�̎w�肪����ꍇ�͂��̂܂܎g�p����
	if( ArchiveIndex != -1 )
	{
		tarc = DXARCD.Archive[ ArchiveIndex ] ;
		if( tarc != NULL )
		{
			if(	_WCSCMP( FilePath, tarc->Path ) == 0 )
			{
				DXARCD.Archive[ ArchiveIndex ]->UseCounter ++ ;

				// �N���e�B�J���Z�N�V�����̉��
				CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

				return ArchiveIndex ;
			}
		}
	}

	// ���ɊJ����Ă��邩���ׂ�
	newindex = -1 ;
	index    = 0 ;
	for( i = 0 ; i < DXARCD.ArchiveNum ; index ++ )
	{
		arc = DXARCD.Archive[ index ] ;
		if( arc == NULL )
		{
			newindex = index ;
			continue ;
		}
		
		i ++ ;

		if( _WCSICMP( arc->Path, FilePath ) == 0 )
		{
			// ���ɊJ����Ă����ꍇ�͂��̃C���f�b�N�X��Ԃ�
			arc->UseCounter ++ ;

			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

			return index ;
		}
	}
	
	// �Ȃ������ꍇ�͐V�K�Ƀf�[�^��ǉ�����

	// �n���h�������Ɉ�t�̏ꍇ�͎g�p����Ă��Ȃ��A�[�J�C�u�n���h�����������
	if( DXARCD.ArchiveNum == DXA_DIR_MAXARCHIVENUM )
	{
		// ���g�p�̃n���h�������
		DXA_DIR_CloseWaitArchive() ;
		
		// ����ł���t�ł���ꍇ�̓G���[
		if( DXARCD.ArchiveNum == DXA_DIR_MAXARCHIVENUM )
		{
			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

			return -1 ;
		}
	} 
	if( newindex == -1 )
	{
		for( newindex = 0 ; DXARCD.Archive[ newindex ] != NULL ; newindex ++ ){}
	}

	// �A�[�J�C�u�t�@�C�������݂��Ă��邩�m�F���Ă珉��������
	DXA_Initialize( &temparc ) ;
	if( FileImage != NULL )
	{
		// ��������ɓW�J���ꂽ�t�@�C���C���[�W���g�p����ꍇ
		if( DXA_OpenArchiveFromMem( &temparc, FileImage, FileSize, FileImageCopyFlag, FileImageReadOnly, DXARCD.ValidKeyString == TRUE ? DXARCD.KeyString : NULL, FilePath ) < 0 )
		{
			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &DXARCD.CriticalSection ) ;
			return -1 ;
		}
	}
	else
	if( OnMemory == TRUE )
	{
		// �������ɓǂݍ��ޏꍇ
		if( DXA_OpenArchiveFromFileUseMem( &temparc, FilePath, DXARCD.ValidKeyString == TRUE ? DXARCD.KeyString : NULL, ASyncThread ) < 0 )
		{
			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &DXARCD.CriticalSection ) ;
			return -1 ;
		}
	}
	else
	{
		// �t�@�C������ǂݍ��ޏꍇ
		if( DXA_OpenArchiveFromFile( &temparc, FilePath, DXARCD.ValidKeyString == TRUE ? DXARCD.KeyString : NULL ) < 0 )
		{
			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &DXARCD.CriticalSection ) ;
			return -1 ;
		}
	}

	// �V�����A�[�J�C�u�f�[�^�p�̃��������m�ۂ���
	arc = DXARCD.Archive[ newindex ] = ( DXARC_DIR_ARCHIVE * )DXALLOC( sizeof( DXARC_DIR_ARCHIVE ) ) ;
	if( DXARCD.Archive[ newindex ] == NULL )
	{
		DXA_CloseArchive( &temparc ) ;
		DXA_Terminate( &temparc ) ;

		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

		return -1 ;
	}

	// ���Z�b�g
	_MEMCPY( &arc->Archive, &temparc, sizeof( DXARC ) ) ;
	arc->UseCounter = 1 ;
	_WCSCPY_S( arc->Path, sizeof( arc->Path ), FilePath ) ;

	// �g�p���̃A�[�J�C�u�̐��𑝂₷
	DXARCD.ArchiveNum ++ ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

	// �C���f�b�N�X��Ԃ�
	return newindex ;
}

// ���ɊJ����Ă���A�[�J�C�u�̃n���h�����擾����( �߂�l: -1=�������� 0�ȏ�:�n���h�� )
static int DXA_DIR_GetArchive( const wchar_t *FilePath, void *FileImage )
{
	int i, index ;
	DXARC_DIR_ARCHIVE *arc ;

	index = 0 ;
	for( i = 0 ; i < DXARCD.ArchiveNum ; index ++ )
	{
		arc = DXARCD.Archive[index] ;
		if( arc == NULL )
		{
			continue ;
		}

		i ++ ;

		if( FilePath )
		{
			if( _WCSCMP( arc->Path, FilePath ) == 0 )
			{
				return index ;
			}
		}
		else
		{
			if( arc->Archive.MemoryImageCopyFlag )
			{
				if( arc->Archive.MemoryImageOriginal == FileImage )
				{
					return index ;
				}
			}
			else
			{
				if( arc->Archive.MemoryImage == FileImage )
				{
					return index ;
				}
			}
		}
	}

	return -1 ;
}

// �A�[�J�C�u�t�@�C�������
static int DXA_DIR_CloseArchive( int ArchiveHandle )
{
	DXARC_DIR_ARCHIVE *arc ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &DXARCD.CriticalSection ) ;

	// �g�p����Ă��Ȃ������牽�������I��
	arc = DXARCD.Archive[ArchiveHandle] ;
	if( arc == NULL || arc->UseCounter == 0 )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

		return -1 ;
	}

	// �Q�ƃJ�E���^�����炷
	arc->UseCounter -- ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

	// �I��
	return 0 ;
}

// �g�p�����̂�҂��Ă���A�[�J�C�u�t�@�C����S�ĕ���
static void DXA_DIR_CloseWaitArchive( int AlwaysClose )
{
	int i, Num, index ;
	DXARC_DIR_ARCHIVE *arc ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &DXARCD.CriticalSection ) ;
	
	Num = DXARCD.ArchiveNum ;
	for( i = 0, index = 0 ; i < Num ; index ++ )
	{
		if( DXARCD.Archive[index] == NULL )
		{
			continue ;
		}
		i ++ ;

		arc = DXARCD.Archive[index] ;

		// �g���Ă����������Ȃ�
		if( arc->UseCounter > 0 && AlwaysClose == FALSE )
		{
			continue ;
		}

		// ��n��
		DXA_CloseArchive( &arc->Archive ) ;
		DXA_Terminate( &arc->Archive ) ;
		DXFREE( arc ) ;
		DXARCD.Archive[index] = NULL ;
		
		// �A�[�J�C�u�̐������炷
		DXARCD.ArchiveNum -- ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &DXARCD.CriticalSection ) ;
}

// �A�[�J�C�u���f�B���N�g���Ɍ����Ă鏈���̏�����
extern	int DXA_DIR_Initialize( void )
{
	// ���ɏ������ς݂̏ꍇ�͉������Ȃ�
	if( DXARCD.InitializeFlag )
	{
		return -1 ;
	}

	// �N���e�B�J���Z�N�V�����̏�����
	CriticalSection_Initialize( &DXARCD.CriticalSection ) ;

//	_MEMSET( &DXARCD, 0, sizeof( DXARC_DIR ) ) ;
//	DXA_DIR_Terminate() ;

	// �g�p����Ă��Ȃ��A�[�J�C�u�t�@�C�����������
	DXA_DIR_CloseWaitArchive() ;

	// �����������t���O�𗧂Ă�
	DXARCD.InitializeFlag = TRUE ;

	// �I��
	return 0 ;
}


// �A�[�J�C�u���f�B���N�g���Ɍ����Ă鏈���̌�n��
extern int DXA_DIR_Terminate( void )
{
	// ���Ɍ�n���ς݂̏ꍇ�͉������Ȃ�
	if( DXARCD.InitializeFlag == FALSE )
	{
		return -1 ;
	}

	// �g�p����Ă��Ȃ��A�[�J�C�u�t�@�C�����������
	DXA_DIR_CloseWaitArchive( TRUE ) ;

	// �N���e�B�J���Z�N�V�����̌�n��
	CriticalSection_Delete( &DXARCD.CriticalSection ) ;

	// �����������t���O��|��
	DXARCD.InitializeFlag = FALSE ;

	// �I��
	return 0 ;
}

// �A�[�J�C�u�t�@�C���̃p�X��啶���ɂ��Ȃ����ǂ����̃t���O���Z�b�g����
extern int DXA_DIR_SetNotArchivePathCharUp( int NotArchivePathCharUpFlag )
{
	DXARCD.NotArchivePathCharUp = NotArchivePathCharUpFlag ;

	// �I��
	return 0 ;
}

// �A�[�J�C�u�t�@�C���̊g���q��ݒ肷��
extern int DXA_DIR_SetArchiveExtension( const wchar_t *Extension )
{
	int Length ;
	
	Length = ( int )_WCSLEN( Extension ) ;

	if( Length >= 64 || Extension == NULL || Extension[0] == _T( '\0' ) )
	{
		DXARCD.ArchiveExtension[ 0 ]  = 0 ;
		DXARCD.ArchiveExtensionLength = 0 ;
	}
	else
	{
		DXARCD.ArchiveExtensionLength = Length ;
		_WCSCPY_S( DXARCD.ArchiveExtension, sizeof( DXARCD.ArchiveExtension ), Extension ) ;
	}

	// �I��
	return 0 ;
}

// �A�[�J�C�u�t�@�C���ƒʏ�̃t�H���_�̂ǂ�������݂����ꍇ�A�ǂ����D�悳���邩��ݒ肷��( 1:�t�H���_��D�� 0:�c�w�A�[�J�C�u�t�@�C����D��(�f�t�H���g) )
extern int DXA_DIR_SetDXArchivePriority( int Priority )
{
	DXARCD.DXAPriority = Priority ;

	// �I��
	return 0 ;
}

// �A�[�J�C�u�t�@�C���̌��������ݒ肷��
extern int DXA_DIR_SetKeyString( const char *KeyString )
{
	if( KeyString == NULL )
	{
		DXARCD.ValidKeyString = FALSE ;
	}
	else
	{
		DXARCD.ValidKeyString = TRUE ;
		if( _STRLEN( KeyString ) > DXA_KEY_STRING_LENGTH )
		{
			_MEMCPY( DXARCD.KeyString, KeyString, DXA_KEY_STRING_LENGTH ) ;
			DXARCD.KeyString[ DXA_KEY_STRING_LENGTH ] = '\0' ;
		}
		else
		{
			_STRCPY( DXARCD.KeyString, KeyString ) ;
		}
	}

	// �I��
	return 0 ;
}

// �t�@�C�����ۂ��Ɠǂݍ��ފ֐�
extern LONGLONG DXA_DIR_LoadFile( const wchar_t *FilePath, void *Buffer, int BufferSize )
{
	LONGLONG siz ;
	DWORD_PTR handle ;

	handle = DXA_DIR_Open( FilePath ) ;
	if( handle == 0 )
	{
		return false ;
	}

	DXA_DIR_Seek( handle, 0L, SEEK_END ) ;
	siz = DXA_DIR_Tell( handle ) ;
	DXA_DIR_Seek( handle, 0L, SEEK_SET ) ;

	if( siz <= BufferSize )
	{
		DXA_DIR_Read( Buffer, ( size_t )siz, 1, handle ) ;
	}

	DXA_DIR_Close( handle ) ;

	// �I��
	return siz ;
}

// DXA_DIR_Open �̊�{�֐�
extern DWORD_PTR DXA_DIR_Open( const wchar_t *FilePath, int UseCacheFlag, int /*BlockReadFlag*/, int UseASyncReadFlag )
{
	int index ;
	DXARC_DIR_FILE *file ;
//	char DXAErrorStr[ FILEPATH_MAX ] ;
	BYTE DxaInFilePath[ FILEPATH_MAX ] ;

	// ����������Ă��Ȃ������珉��������
	if( DXARCD.InitializeFlag == FALSE )
	{
		DXA_DIR_Initialize() ;
	}

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &DXARCD.CriticalSection ) ;

//	UseCacheFlag  = UseCacheFlag ;
//	BlockReadFlag = BlockReadFlag ;
//	DXAErrorStr[ 0 ] = 0 ;

	// �󂫃f�[�^��T��
	if( DXARCD.FileNum == DXA_DIR_MAXFILENUM )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

		DXST_LOGFILE_ADDUTF16LE( "\x0c\x54\x42\x66\x6b\x30\x8b\x95\x51\x30\x8b\x30\xd5\x30\xa1\x30\xa4\x30\xeb\x30\x6e\x30\x70\x65\x4c\x30\x50\x96\x4c\x75\x92\x30\x85\x8d\x48\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�����ɊJ����t�@�C���̐������E�𒴂��܂���\n" @*/ ) ;
		return 0 ;
	}
	for( index = 0 ; DXARCD.File[index] != NULL ; index ++ ){}

	// �������̊m��
	DXARCD.File[ index ] = (DXARC_DIR_FILE *)DXALLOC( sizeof( DXARC_DIR_FILE ) ) ;
	if( DXARCD.File[ index ] == NULL )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

		DXST_LOGFILE_ADDUTF16LE( "\xd5\x30\xa1\x30\xa4\x30\xeb\x30\x6e\x30\xc5\x60\x31\x58\x92\x30\x3c\x68\x0d\x7d\x59\x30\x8b\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�t�@�C���̏����i�[���郁�����̊m�ۂɎ��s���܂���\n" @*/ ) ;
		return 0 ;
	}
	file = DXARCD.File[index] ;

	// �A�[�J�C�u�t�@�C���ƃt�H���_�̂ǂ����D�悷�邩�ŏ����𕪊�
	if( DXARCD.DXAPriority == 0 )
	{
		int FileOpen = FALSE ;

		// �A�[�J�C�u��D�悷��ꍇ

		// �A�[�J�C�u�t�@�C�������������ׂ�
		if( DXA_DIR_OpenTest( FilePath, ( int * )&file->UseArchiveIndex, DxaInFilePath, sizeof( DxaInFilePath ) ) == 0 )
		{
			// �f�B���N�g�����Ɠ����̂c�w�`�t�@�C�����J�����炻�̒�����w��̃t�@�C����ǂݍ������Ƃ���
			if( DXA_STREAM_Initialize( &file->DXAStream, &DXARCD.Archive[ file->UseArchiveIndex ]->Archive, DxaInFilePath, UseASyncReadFlag ) < 0 )
			{
//				_STRCPY( DXAErrorStr, DXSTRING( "�c�w�`�t�@�C���̒��Ɏw��̃t�@�C���͌�����܂���ł���\n" ) ) ;
				DXA_DIR_CloseArchive( ( int )file->UseArchiveIndex ) ;
			}
			else
			{
				// �A�[�J�C�u���g�p���Ă���t���O�𗧂Ă�
				file->UseArchiveFlag = 1 ;

				FileOpen = TRUE ;
			}
		}

		if( FileOpen == FALSE )
		{
			// �A�[�J�C�u�t�@�C�������������畁�ʂ̃t�@�C������ǂݍ��ސݒ���s��
			file->UseArchiveFlag = 0 ;

			// ���ʂ̃t�@�C�������������ׂ�
			file->ReadOnlyFilePointer = ReadOnlyFileAccessOpen( FilePath, UseCacheFlag, TRUE, UseASyncReadFlag ) ;
			if( file->ReadOnlyFilePointer == 0 )
			{
				goto ERR ;
			}
			else
			{
				FileOpen = TRUE ;
			}
		}
	}
	else
	{
		// ���ʂ̃t�@�C����D�悷��ꍇ

		// ���ʂ̃t�@�C�������������ׂ�
		if( ( file->ReadOnlyFilePointer = ReadOnlyFileAccessOpen( FilePath, UseCacheFlag, TRUE, UseASyncReadFlag ) ) != 0 )
		{
			// �J�����畁�ʂ̃t�@�C������ǂݍ��ސݒ���s��
			file->UseArchiveFlag = 0 ;
		}
		else
		{
			// �A�[�J�C�u�t�@�C�������������ׂ�
			if( DXA_DIR_OpenTest( FilePath, (int *)&file->UseArchiveIndex, DxaInFilePath, sizeof( DxaInFilePath ) ) == 0 )
			{
				// �f�B���N�g�����Ɠ����̂c�w�`�t�@�C�����J�����炻�̒�����w��̃t�@�C����ǂݍ������Ƃ���
				if( DXA_STREAM_Initialize( &file->DXAStream, &DXARCD.Archive[ file->UseArchiveIndex ]->Archive, DxaInFilePath, UseASyncReadFlag ) < 0 )
				{
//					_STRCPY( DXAErrorStr, DXSTRING( "�c�w�`�t�@�C���̒��Ɏw��̃t�@�C���͌�����܂���ł���\n" ) ) ;
					DXA_DIR_CloseArchive( ( int )file->UseArchiveIndex ) ;
					goto ERR ;
				}
				else
				{
					// �A�[�J�C�u���g�p���Ă���t���O�𗧂Ă�
					file->UseArchiveFlag = 1 ;
				}
			}
			else
			{
				// ����������G���[
				goto ERR;
			}
		}
	}

	// �n���h���̐��𑝂₷
	DXARCD.FileNum ++ ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

	// �C���f�b�N�X��Ԃ�
	return index | 0xF0000000 ;

ERR:
	// �������̉��
	if( DXARCD.File[index] != NULL ) DXFREE( DXARCD.File[index] ) ;
	DXARCD.File[index] = NULL ;
	
	// �G���[������o��
//	DXST_LOGFILEFMT_ADDW(( L"�t�@�C�� %s �̃I�[�v���Ɏ��s���܂���\n", FilePath )) ;
//	if( DXAErrorStr[0] != '\0' ) DXST_LOGFILEFMT_ADDW(( "�c�w�`�G���[�F%s", DXAErrorStr )) ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

	// �G���[�I��
	return 0 ;
}

// �t�@�C�������
extern int DXA_DIR_Close( DWORD_PTR Handle )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &DXARCD.CriticalSection ) ;

	DXARC_DIR_FILE *file = DXARCD.File[Handle & 0x0FFFFFFF] ;

	// �g�p����Ă��Ȃ������牽�������I��
	if( file == NULL )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

		return -1 ;
	}
	
	// �A�[�J�C�u���g�p���Ă��邩�ǂ����ŕ���
	if( file->UseArchiveFlag == FALSE )
	{
		// �g�p���Ă��Ȃ��ꍇ�͕W�����o�͂̃t�@�C���|�C���^���������
		ReadOnlyFileAccessClose( file->ReadOnlyFilePointer ) ;
		file->ReadOnlyFilePointer = 0 ;
	}
	else
	{
		// �A�[�J�C�u���g�p���Ă����ꍇ�̓A�[�J�C�u�̎Q�Ɛ������炷
		
		// �A�[�J�C�u�t�@�C���̎Q�Ɛ������炷
		DXA_DIR_CloseArchive( ( int )file->UseArchiveIndex ) ;

		// �A�[�J�C�u�t�@�C���̌�n��
		DXA_STREAM_Terminate( &file->DXAStream ) ;
	}

	// ���������������
	DXFREE( file ) ;
	DXARCD.File[Handle & 0x0FFFFFFF] = NULL ;
	
	// �������炷
	DXARCD.FileNum -- ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &DXARCD.CriticalSection ) ;

	// �I��
	return 0 ;
}

// �t�@�C���|�C���^�̈ʒu���擾����
extern	LONGLONG DXA_DIR_Tell( DWORD_PTR Handle )
{
	DXARC_DIR_FILE *file = DXARCD.File[Handle & 0x0FFFFFFF] ;
	if( file == NULL )
	{
		return -1 ;
	}

	if( file->UseArchiveFlag == 0 )
	{
		return ReadOnlyFileAccessTell( file->ReadOnlyFilePointer ) ;
	}
	else
	{
		return DXA_STREAM_Tell( &file->DXAStream ) ;
	}
}

// �t�@�C���|�C���^�̈ʒu��ύX����
extern int DXA_DIR_Seek( DWORD_PTR Handle, LONGLONG SeekPoint, int SeekType )
{
	DXARC_DIR_FILE *file = DXARCD.File[Handle & 0x0FFFFFFF] ;
	if( file == NULL )
	{
		return -1 ;
	}

	if( file->UseArchiveFlag == 0 )
	{
		return ReadOnlyFileAccessSeek( file->ReadOnlyFilePointer, SeekPoint, SeekType ) ;
	}
	else
	{
		return DXA_STREAM_Seek( &file->DXAStream, SeekPoint, SeekType ) ;
	}
}

// �t�@�C������f�[�^��ǂݍ���
extern size_t DXA_DIR_Read( void *Buffer, size_t BlockSize, size_t BlockNum, DWORD_PTR Handle )
{
	DXARC_DIR_FILE *file = DXARCD.File[Handle & 0x0FFFFFFF] ;
	if( file == NULL )
	{
		return ( size_t )-1 ;
	}

	if( file->UseArchiveFlag == 0 )
	{
		return ReadOnlyFileAccessRead( Buffer, BlockSize, BlockNum, file->ReadOnlyFilePointer ) ;
	}
	else
	{
		return DXA_STREAM_Read( &file->DXAStream, Buffer, BlockSize * BlockNum ) / BlockSize ;
	}
}

// �t�@�C���̏I�[�𒲂ׂ�
extern int DXA_DIR_Eof( DWORD_PTR Handle )
{
	DXARC_DIR_FILE *file = DXARCD.File[Handle & 0x0FFFFFFF] ;
	if( file == NULL )
	{
		return -1 ;
	}

	if( file->UseArchiveFlag == 0 )
	{
		return ReadOnlyFileAccessEof( file->ReadOnlyFilePointer ) ;
	}
	else
	{
		return DXA_STREAM_Eof( &file->DXAStream ) ;
	}
}

extern	int DXA_DIR_ChDir( const wchar_t *Path )
{
	_WCHDIR( Path ) ;

	return 0 ;
}

extern	int DXA_DIR_GetDir( wchar_t *Buffer )
{
	_WGETCWD( Buffer, BUFFERBYTES_CANCEL ) ;

	return 0 ;
}

extern	int DXA_DIR_GetDirS( wchar_t *Buffer, size_t BufferBytes )
{
	_WGETCWD( Buffer, BufferBytes ) ;

	return 0 ;
}

extern	int DXA_DIR_IdleCheck( DWORD_PTR Handle )
{
	DXARC_DIR_FILE *file = DXARCD.File[Handle & 0x0FFFFFFF] ;
	if( file == NULL )
	{
		return -1 ;
	}

	if( file->UseArchiveFlag == 0 )
	{
		return ReadOnlyFileAccessIdleCheck( file->ReadOnlyFilePointer ) ;
	}
	else
	{
		return DXA_STREAM_IdleCheck( &file->DXAStream ) ;
	}
}

// �߂�l: -1=�G���[  0=�c�w�A�[�J�C�u�t�@�C�����̃t�@�C���ł͂Ȃ�  1=�c�w�A�[�J�C�u�t�@�C�����̃t�@�C��
extern int DXA_DIR_IsDXA( DWORD_PTR Handle )
{
	DXARC_DIR_FILE *file = DXARCD.File[Handle & 0x0FFFFFFF] ;
	if( file == NULL )
	{
		return -1 ;
	}

	return file->UseArchiveFlag ;
}

// �߂�l: -1=�G���[  -1�ȊO=FindHandle
extern DWORD_PTR DXA_DIR_FindFirst( const wchar_t *FilePath, FILEINFOW *Buffer )
{
	DXA_DIR_FINDDATA *find ;
	BYTE nPath[ FILEPATH_MAX ] ;

	// �������̊m��
	find = ( DXA_DIR_FINDDATA * )DXALLOC( sizeof( DXA_DIR_FINDDATA ) ) ;
	if( find == NULL )
	{
		return ( DWORD_PTR )-1 ;
	}
	_MEMSET( find, 0, sizeof( *find ) ) ;

	// �w��̃I�u�W�F�N�g���A�[�J�C�u�t�@�C���������ׂ�
	if( DXA_DIR_OpenTest( FilePath, &find->UseArchiveIndex, nPath, sizeof( nPath ) ) == -1 )
	{
		// �A�[�J�C�u�t�@�C�����ł͂Ȃ������ꍇ�̓t�@�C�����猟������
		find->UseArchiveFlag = 0 ;
		find->FindHandle = ReadOnlyFileAccessFindFirst( FilePath, Buffer ) ;
	}
	else
	{
		// �A�[�J�C�u�t�@�C�����̏ꍇ�̓A�[�J�C�u�t�@�C�������猟������
		find->UseArchiveFlag = 1 ;
		find->FindHandle = DXA_FindFirst( &DXARCD.Archive[ find->UseArchiveIndex ]->Archive, nPath, Buffer ) ;
	}

	// �����n���h�����擾�ł��Ȃ������ꍇ�̓G���[
	if( find->FindHandle == ( DWORD_PTR )-1 )
	{
		// �A�[�J�C�u�t�@�C�����̏ꍇ�̓A�[�J�C�u�t�@�C���̎g�p�J�E���g�����炷
		if( find->UseArchiveFlag != 0 )
		{
			DXA_DIR_CloseArchive( find->UseArchiveIndex ) ;
		}

		DXFREE( find );
		return ( DWORD_PTR )-1 ;
	}

	// �n���h����Ԃ�
	return (DWORD_PTR)find ;
}

// �߂�l: -1=�G���[  0=����
extern int DXA_DIR_FindNext( DWORD_PTR FindHandle, FILEINFOW *Buffer )
{
	DXA_DIR_FINDDATA *find;

	find = (DXA_DIR_FINDDATA *)FindHandle;
	if( find->UseArchiveFlag == 0 )
	{
		return ReadOnlyFileAccessFindNext( find->FindHandle, Buffer ) ;
	}
	else
	{
		return DXA_FindNext( find->FindHandle, Buffer ) ;
	}
}

// �߂�l: -1=�G���[  0=����
extern int DXA_DIR_FindClose( DWORD_PTR FindHandle )
{
	DXA_DIR_FINDDATA *find;

	find = (DXA_DIR_FINDDATA *)FindHandle;
	if( find->UseArchiveFlag == 0 )
	{
		ReadOnlyFileAccessFindClose( find->FindHandle ) ;
	}
	else
	{
		DXA_FindClose( find->FindHandle );
		DXA_DIR_CloseArchive( find->UseArchiveIndex ) ;
	}

	DXFREE( find );

	return 0;
}




// �w��̂c�w�`�t�@�C�����ۂ��ƃ������ɓǂݍ���( �߂�l: -1=�G���[  0=���� )
extern int NS_DXArchivePreLoad( const TCHAR *FilePath , int ASyncThread )
{
	wchar_t fullpath[ FILEPATH_MAX ] ;

	// �t���p�X�𓾂�(���łɑS�Ă̕�����啶���ɂ���)
#ifdef UNICODE
	DXA_DIR_ConvertFullPath( FilePath, fullpath, sizeof( fullpath ), DXARCD.NotArchivePathCharUp == FALSE ? 1 : 0 ) ;
#else // UNICODE
	wchar_t FilePathBuffer[ FILEPATH_MAX ] ;

	ConvString( ( const char * )FilePath, -1, _TCHARCODEFORMAT, ( char * )FilePathBuffer, sizeof( FilePathBuffer ), WCHAR_T_CHARCODEFORMAT ) ;
	DXA_DIR_ConvertFullPath( FilePathBuffer, fullpath, sizeof( fullpath ), DXARCD.NotArchivePathCharUp == FALSE ? 1 : 0 ) ;
#endif // UNICODE

	return DXA_DIR_OpenArchive( fullpath, NULL, -1, FALSE, FALSE, -1, TRUE, ASyncThread ) == -1 ? -1 : 0 ;
}

// �w��̂c�w�`�t�@�C�����ۂ��ƃ������ɓǂݍ���( �߂�l  -1:�G���[  0:���� )
extern int NS_DXArchivePreLoadWithStrLen( const TCHAR *FilePath, size_t FilePathLength, int ASyncThread )
{
	int Result ;
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_ONE_BEGIN( FilePath, FilePathLength, return -1 )
	Result = NS_DXArchivePreLoad( UseFilePathBuffer , ASyncThread ) ;
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( FilePath )
	return Result ;
}

// �w��̂c�w�`�t�@�C���̎��O�ǂݍ��݂������������ǂ������擾����( �߂�l�F TRUE=�������� FALSE=�܂� )
extern int NS_DXArchiveCheckIdle( const TCHAR *FilePath )
{
	int handle;
	wchar_t fullpath[FILEPATH_MAX];

	// �t���p�X�𓾂�(���łɑS�Ă̕�����啶���ɂ���)
#ifdef UNICODE
	DXA_DIR_ConvertFullPath( FilePath, fullpath, sizeof( fullpath ), DXARCD.NotArchivePathCharUp == FALSE ? 1 : 0 ) ;
#else // UNICODE
	wchar_t FilePathBuffer[ FILEPATH_MAX ] ;

	ConvString( ( const char * )FilePath, -1, _TCHARCODEFORMAT, ( char * )FilePathBuffer, sizeof( FilePathBuffer ), WCHAR_T_CHARCODEFORMAT ) ;
	DXA_DIR_ConvertFullPath( FilePathBuffer, fullpath, sizeof( fullpath ), DXARCD.NotArchivePathCharUp == FALSE ? 1 : 0 ) ;
#endif // UNICODE

	// �t�@�C���p�X����n���h�����擾����
	handle = DXA_DIR_GetArchive( fullpath ) ;
	if( handle == -1 )
	{
		return 0 ;
	}

	// �����������������ǂ����𓾂�
	return DXA_CheckIdle( &DXARCD.Archive[handle]->Archive ) ;
}

// �w��̂c�w�`�t�@�C���̎��O�ǂݍ��݂������������ǂ������擾����( �߂�l  TRUE:�������� FALSE:�܂� )
extern int NS_DXArchiveCheckIdleWithStrLen( const TCHAR *FilePath, size_t FilePathLength )
{
	int Result ;
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_ONE_BEGIN( FilePath, FilePathLength, return -1 )
	Result = NS_DXArchiveCheckIdle( UseFilePathBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( FilePath )
	return Result ;
}

// �w��̂c�w�`�t�@�C��������������������
extern int NS_DXArchiveRelease( const TCHAR *FilePath )
{
	int handle;
	wchar_t fullpath[ FILEPATH_MAX ] ;

	// �t���p�X�𓾂�(���łɑS�Ă̕�����啶���ɂ���)
#ifdef UNICODE
	DXA_DIR_ConvertFullPath( FilePath, fullpath, sizeof( fullpath ), DXARCD.NotArchivePathCharUp == FALSE ? 1 : 0 ) ;
#else // UNICODE
	wchar_t FilePathBuffer[ FILEPATH_MAX ] ;

	ConvString( ( const char * )FilePath, -1, _TCHARCODEFORMAT, ( char * )FilePathBuffer, sizeof( FilePathBuffer ), WCHAR_T_CHARCODEFORMAT ) ;
	DXA_DIR_ConvertFullPath( FilePathBuffer, fullpath, sizeof( fullpath ), DXARCD.NotArchivePathCharUp == FALSE ? 1 : 0 ) ;
#endif // UNICODE

	// �t�@�C���p�X����n���h�����擾����
	handle = DXA_DIR_GetArchive( fullpath ) ;
	if( handle == -1 )
	{
		return 0 ;
	}

	// ����
	DXA_DIR_CloseArchive( handle ) ;
	DXA_DIR_CloseWaitArchive() ;

	// �I��
	return 0 ;
}

// �w��̂c�w�`�t�@�C��������������������
extern int NS_DXArchiveReleaseWithStrLen( const TCHAR *FilePath, size_t FilePathLength )
{
	int Result ;
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_ONE_BEGIN( FilePath, FilePathLength, return -1 )
	Result = NS_DXArchiveRelease( UseFilePathBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( FilePath )
	return Result ;
}

// �c�w�`�t�@�C���̒��Ɏw��̃t�@�C�������݂��邩�ǂ����𒲂ׂ�ATargetFilePath �͂c�w�`�t�@�C�����J�����g�t�H���_�Ƃ����ꍇ�̃p�X( �߂�l:  -1=�G���[  0:����  1:���� )
extern int NS_DXArchiveCheckFile( const TCHAR *FilePath, const TCHAR *TargetFilePath )
{
	int index, ret ;
	DXARC_DIR_ARCHIVE *Archive ;
	wchar_t fullpath[ FILEPATH_MAX ] ;

	// �t���p�X�𓾂�(���łɑS�Ă̕�����啶���ɂ���)
#ifdef UNICODE
	DXA_DIR_ConvertFullPath( FilePath, fullpath, sizeof( fullpath ), DXARCD.NotArchivePathCharUp == FALSE ? 1 : 0 ) ;
#else // UNICODE
	wchar_t FilePathBuffer[ FILEPATH_MAX ] ;

	ConvString( ( const char * )FilePath, -1, _TCHARCODEFORMAT, ( char * )FilePathBuffer, sizeof( FilePathBuffer ), WCHAR_T_CHARCODEFORMAT ) ;
	DXA_DIR_ConvertFullPath( FilePathBuffer, fullpath, sizeof( fullpath ), DXARCD.NotArchivePathCharUp == FALSE ? 1 : 0 ) ;
#endif // UNICODE

	// �A�[�J�C�u�t�@�C�������邩�ǂ������ׂ�
	index = DXA_DIR_OpenArchive( fullpath ) ;
	if( index == -1 )
	{
		return -1 ;
	}

	// �A�[�J�C�u�̒��Ɏw��̃t�@�C�������邩�ǂ����𒲂ׂ�
	Archive = DXARCD.Archive[ index ] ;
	ret = DXA_GetFileInfo( &Archive->Archive, _TCHARCODEFORMAT, ( const char * )TargetFilePath, NULL, NULL ) ;

	DXA_DIR_CloseArchive( index ) ;

	// ���ʂ�Ԃ�
	return ret == -1 ? 0 : 1 ;
}

// �c�w�`�t�@�C���̒��Ɏw��̃t�@�C�������݂��邩�ǂ����𒲂ׂ�ATargetFilePath �͂c�w�`�t�@�C�����J�����g�t�H���_�Ƃ����ꍇ�̃p�X( �߂�l:  -1=�G���[  0:����  1:���� )
extern int NS_DXArchiveCheckFileWithStrLen( const TCHAR *FilePath, size_t FilePathLength, const TCHAR *TargetFilePath, size_t TargetFilePathLength )
{
	int Result = -1 ;
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( FilePath )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_BEGIN( TargetFilePath )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( FilePath,       FilePathLength,       goto ERR )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_SETUP( TargetFilePath, TargetFilePathLength, goto ERR )

	Result = NS_DXArchiveCheckFile( UseFilePathBuffer, UseTargetFilePathBuffer ) ;

ERR :

	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( FilePath )
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( TargetFilePath )
	return Result ;
}

// ��������ɓW�J���ꂽ�c�w�`�t�@�C�����w��̃t�@�C���p�X�ɂ��邱�Ƃɂ���
extern int NS_DXArchiveSetMemImage(		void *ArchiveImage, int ArchiveImageSize, const TCHAR *EmulateFilePath, int ArchiveImageCopyFlag, int ArchiveImageReadOnly )
{
	wchar_t fullpath[ FILEPATH_MAX ] ;

	// �t���p�X�𓾂�(���łɑS�Ă̕�����啶���ɂ���)
#ifdef UNICODE
	DXA_DIR_ConvertFullPath( EmulateFilePath, fullpath, sizeof( fullpath ), DXARCD.NotArchivePathCharUp == FALSE ? 1 : 0 ) ;
#else // UNICODE
	wchar_t FilePathBuffer[ FILEPATH_MAX ] ;

	ConvString( ( const char * )EmulateFilePath, -1, _TCHARCODEFORMAT, ( char * )FilePathBuffer, sizeof( FilePathBuffer ), WCHAR_T_CHARCODEFORMAT ) ;
	DXA_DIR_ConvertFullPath( FilePathBuffer, fullpath, sizeof( fullpath ), DXARCD.NotArchivePathCharUp == FALSE ? 1 : 0 ) ;
#endif // UNICODE

	return DXA_DIR_OpenArchive( fullpath, ArchiveImage, ArchiveImageSize, ArchiveImageCopyFlag, ArchiveImageReadOnly, -1, FALSE, FALSE ) == -1 ? -1 : 0;
}

// ��������ɓW�J���ꂽ�c�w�`�t�@�C�����w��̃t�@�C���p�X�ɂ��邱�Ƃɂ���( EmulateFilePath �͌����Ă� dxa �t�@�C���̃p�X�A�Ⴆ�΂c�w�`�t�@�C���C���[�W�� Image.dxa �Ƃ����t�@�C������ c:\Temp �ɂ��邱�Ƃɂ������ꍇ�� EmulateFilePath �� "c:\\Temp\\Image.dxa" ��n���ASetDXArchiveExtension �Ŋg���q��ύX���Ă���ꍇ�� EmulateFilePath �ɓn���t�@�C���p�X�̊g���q������ɍ��킹��K�v���� )
extern int NS_DXArchiveSetMemImageWithStrLen( void *ArchiveImage, int ArchiveImageSize, const TCHAR *EmulateFilePath, size_t EmulateFilePathLength, int ArchiveImageCopyFlag, int ArchiveImageReadOnly )
{
	int Result ;
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_ONE_BEGIN( EmulateFilePath, EmulateFilePathLength, return -1 )
	Result = NS_DXArchiveSetMemImage( ArchiveImage, ArchiveImageSize, UseEmulateFilePathBuffer, ArchiveImageCopyFlag, ArchiveImageReadOnly ) ;
	TCHAR_STRING_WITH_STRLEN_TO_TCHAR_STRING_END( EmulateFilePath )
	return Result ;
}

// DXArchiveSetMemImage �̐ݒ����������
extern int NS_DXArchiveReleaseMemImage(	void *ArchiveImage )
{
	int handle;

	// �t�@�C���p�X����n���h�����擾����
	handle = DXA_DIR_GetArchive( NULL, ArchiveImage ) ;
	if( handle == -1 )
	{
		return 0 ;
	}

	// ����
	DXA_DIR_CloseArchive( handle ) ;
	DXA_DIR_CloseWaitArchive() ;

	// �I��
	return 0 ;
}

#endif


// �f�[�^���𓀂���( �߂�l:�𓀌�̃f�[�^�T�C�Y )
#define MIN_COMPRESS		(4)						// �Œሳ�k�o�C�g��
#define MAX_SEARCHLISTNUM	(64)					// �ő��v����T���ׂ̃��X�g��H��ő吔
#define MAX_SUBLISTNUM		(65536)					// ���k���ԒZ�k�̂��߂̃T�u���X�g�̍ő吔
#define MAX_COPYSIZE 		(0x1fff + MIN_COMPRESS)	// �Q�ƃA�h���X����R�s�[�o�؂�ő�T�C�Y( ���k�R�[�h���\���ł���R�s�[�T�C�Y�̍ő�l + �Œሳ�k�o�C�g�� )
#define MAX_ADDRESSLISTNUM	(1024 * 1024 * 1)		// �X���C�h�����̍ő�T�C�Y
#define MAX_POSITION		(1 << 24)				// �Q�Ɖ\�ȍő告�΃A�h���X( 16MB )

// ���k���ԒZ�k�p���X�g
typedef struct LZ_LIST
{
	LZ_LIST *next, *prev ;
	DWORD address ;
} LZ_LIST ;

// �f�[�^�����k����( �߂�l:���k��̃f�[�^�T�C�Y )
extern	int	DXA_Encode( void *Src, DWORD SrcSize, void *Dest )
{
	int dstsize ;
	int    bonus,    conbo,    conbosize,        address,    addresssize ;
	int maxbonus, maxconbo, maxconbosize = 0, maxaddress, maxaddresssize = 0 ;
	BYTE keycode, *srcp, *destp, *dp, *sp, *sp2, *sp1 ;
	DWORD srcaddress, code ;
	int j ;
	DWORD i, m ;
	DWORD maxlistnum, maxlistnummask, listaddp ;
	DWORD sublistnum, sublistmaxnum ;
	LZ_LIST *listbuf, *listtemp, *list, *newlist ;
	BYTE *listfirsttable, *usesublistflagtable, *sublistbuf ;
	
	// �T�u���X�g�̃T�C�Y�����߂�
	{
			 if( SrcSize < 100 * 1024 )			sublistmaxnum = 1 ;
		else if( SrcSize < 3 * 1024 * 1024 )	sublistmaxnum = MAX_SUBLISTNUM / 3 ;
		else									sublistmaxnum = MAX_SUBLISTNUM ;
	}

	// ���X�g�̃T�C�Y�����߂�
	{
		maxlistnum = MAX_ADDRESSLISTNUM ;
		if( maxlistnum > SrcSize )
		{
			while( ( maxlistnum >> 1 ) > 0x100 && ( maxlistnum >> 1 ) > SrcSize )
				maxlistnum >>= 1 ;
		}
		maxlistnummask = maxlistnum - 1 ;
	}

	// �������̊m��
	usesublistflagtable   = (BYTE *)DXALLOC(
		sizeof( DWORD_PTR )	* 65536 +					// ���C�����X�g�̐擪�I�u�W�F�N�g�p�̈�
		sizeof( LZ_LIST   )	* maxlistnum +				// ���C�����X�g�p�̈�
		sizeof( BYTE      )	* 65536 +					// �T�u���X�g���g�p���Ă��邩�t���O�p�̈�
		sizeof( DWORD_PTR )	* 256 * sublistmaxnum ) ;	// �T�u���X�g�p�̈�
		
	// �A�h���X�̃Z�b�g
	listfirsttable =     usesublistflagtable + sizeof( BYTE      ) * 65536 ;
	sublistbuf     =          listfirsttable + sizeof( DWORD_PTR ) * 65536 ;
	listbuf        = (LZ_LIST *)( sublistbuf + sizeof( DWORD_PTR ) * 256 * sublistmaxnum ) ;
	
	// ������
	_MEMSET( usesublistflagtable, 0, sizeof( BYTE      ) * 65536               ) ;
	_MEMSET(          sublistbuf, 0, sizeof( DWORD_PTR ) * 256 * sublistmaxnum ) ;
	_MEMSET(      listfirsttable, 0, sizeof( DWORD_PTR ) * 65536               ) ;
	list = listbuf ;
	for( i = maxlistnum / 8 ; i ; i --, list += 8 )
	{
		list[0].address =
		list[1].address =
		list[2].address =
		list[3].address =
		list[4].address =
		list[5].address =
		list[6].address =
		list[7].address = 0xffffffff ;
	}

	srcp  = (BYTE *)Src ;
	destp = (BYTE *)Dest ;

	// ���k���f�[�^�̒��ň�ԏo���p�x���Ⴂ�o�C�g�R�[�h����������
	{
		DWORD qnum, table[256], mincode ;

		for( i = 0 ; i < 256 ; i ++ )
			table[i] = 0 ;
		
		sp   = srcp ;
		qnum = SrcSize / 8 ;
		i    = qnum * 8 ;
		for( ; qnum ; qnum --, sp += 8 )
		{
			table[sp[0]] ++ ;
			table[sp[1]] ++ ;
			table[sp[2]] ++ ;
			table[sp[3]] ++ ;
			table[sp[4]] ++ ;
			table[sp[5]] ++ ;
			table[sp[6]] ++ ;
			table[sp[7]] ++ ;
		}
		for( ; i < SrcSize ; i ++, sp ++ )
			table[*sp] ++ ;
			
		keycode = 0 ;
		mincode = table[0] ;
		for( i = 1 ; i < 256 ; i ++ )
		{
			if( mincode < table[i] ) continue ;
			mincode = table[i] ;
			keycode = (BYTE)i ;
		}
	}

	// ���k���̃T�C�Y���Z�b�g
	((DWORD *)destp)[0] = SrcSize ;

	// �L�[�R�[�h���Z�b�g
	destp[8] = keycode ;

	// ���k����
	dp               = destp + 9 ;
	sp               = srcp ;
	srcaddress       = 0 ;
	dstsize          = 0 ;
	listaddp         = 0 ;
	sublistnum       = 0 ;
	while( srcaddress < SrcSize )
	{
		// �c��T�C�Y���Œሳ�k�T�C�Y�ȉ��̏ꍇ�͈��k���������Ȃ�
		if( srcaddress + MIN_COMPRESS >= SrcSize ) goto NOENCODE ;

		// ���X�g���擾
		code = *((WORD *)sp) ;
		list = (LZ_LIST *)( listfirsttable + code * sizeof( DWORD_PTR ) ) ;
		if( usesublistflagtable[code] == 1 )
		{
			list = (LZ_LIST *)( (DWORD_PTR *)list->next + sp[2] ) ;
		}
		else
		{
			if( sublistnum < sublistmaxnum )
			{
				list->next = (LZ_LIST *)( sublistbuf + sizeof( DWORD_PTR ) * 256 * sublistnum ) ;
				list       = (LZ_LIST *)( (DWORD_PTR *)list->next + sp[2] ) ;
			
				usesublistflagtable[code] = 1 ;
				sublistnum ++ ;
			}
		}

		// ��Ԉ�v���̒����R�[�h��T��
		maxconbo   = -1 ;
		maxaddress = -1 ;
		maxbonus   = -1 ;
		for( m = 0, listtemp = list->next ; /*m < MAX_SEARCHLISTNUM &&*/ listtemp != NULL ; listtemp = listtemp->next, m ++ )
		{
			address = ( int )( srcaddress - listtemp->address ) ;
			if( address >= MAX_POSITION )
			{
				if( listtemp->prev ) listtemp->prev->next = listtemp->next ;
				if( listtemp->next ) listtemp->next->prev = listtemp->prev ;
				listtemp->address = 0xffffffff ;
				continue ;
			}
			
			sp2 = &sp[-address] ;
			sp1 = sp ;
			if( srcaddress + MAX_COPYSIZE < SrcSize )
			{
				conbo = MAX_COPYSIZE / 4 ;
				while( conbo && *((DWORD *)sp2) == *((DWORD *)sp1) )
				{
					sp2 += 4 ;
					sp1 += 4 ;
					conbo -- ;
				}
				conbo = MAX_COPYSIZE - ( MAX_COPYSIZE / 4 - conbo ) * 4 ;

				while( conbo && *sp2 == *sp1 )
				{
					sp2 ++ ;
					sp1 ++ ;
					conbo -- ;
				}
				conbo = MAX_COPYSIZE - conbo ;
			}
			else
			{
				for( conbo = 0 ;
						conbo < MAX_COPYSIZE &&
						conbo + srcaddress < SrcSize &&
						sp[conbo - address] == sp[conbo] ;
							conbo ++ ){}
			}

			if( conbo >= 4 )
			{
				conbosize   = ( conbo - MIN_COMPRESS ) < 0x20 ? 0 : 1 ;
				addresssize = address < 0x100 ? 0 : ( address < 0x10000 ? 1 : 2 ) ;
				bonus       = conbo - ( 3 + conbosize + addresssize ) ;

				if( bonus > maxbonus )
				{
					maxconbo       = conbo ;
					maxaddress     = address ;
					maxaddresssize = addresssize ;
					maxconbosize   = conbosize ;
					maxbonus       = bonus ;
				}
			}
		}

		// ���X�g�ɓo�^
		newlist = &listbuf[listaddp] ;
		if( newlist->address != 0xffffffff )
		{
			if( newlist->prev ) newlist->prev->next = newlist->next ;
			if( newlist->next ) newlist->next->prev = newlist->prev ;
			newlist->address = 0xffffffff ;
		}
		newlist->address = srcaddress ;
		newlist->prev    = list ;
		newlist->next    = list->next ;
		if( list->next != NULL ) list->next->prev = newlist ;
		list->next       = newlist ;
		listaddp         = ( listaddp + 1 ) & maxlistnummask ;

		// ��v�R�[�h��������Ȃ�������񈳏k�R�[�h�Ƃ��ďo��
		if( maxconbo == -1 )
		{
NOENCODE:
			// �L�[�R�[�h�������ꍇ�͂Q��A���ŏo�͂���
			if( *sp == keycode )
			{
				if( destp != NULL )
				{
					dp[0]  =
					dp[1]  = keycode ;
					dp += 2 ;
				}
				dstsize += 2 ;
			}
			else
			{
				if( destp != NULL )
				{
					*dp = *sp ;
					dp ++ ;
				}
				dstsize ++ ;
			}
			sp ++ ;
			srcaddress ++ ;
		}
		else
		{
			// ���������ꍇ�͌������ʒu�ƒ������o�͂���
			
			// �L�[�R�[�h�ƌ������ʒu�ƒ������o��
			if( destp != NULL )
			{
				// �L�[�R�[�h�̏o��
				*dp++ = keycode ;

				// �o�͂���A�����͍Œ� MIN_COMPRESS ���邱�Ƃ��O��Ȃ̂� - MIN_COMPRESS �������̂��o�͂���
				maxconbo -= MIN_COMPRESS ;

				// �A�����O�`�S�r�b�g�ƘA�����A���΃A�h���X�̃r�b�g�����o��
				*dp = (BYTE)( ( ( maxconbo & 0x1f ) << 3 ) | ( maxconbosize << 2 ) | maxaddresssize ) ;

				// �L�[�R�[�h�̘A���̓L�[�R�[�h�ƒl�̓������񈳏k�R�[�h��
				// ���f���邽�߁A�L�[�R�[�h�̒l�ȏ�̏ꍇ�͒l���{�P����
				if( *dp >= keycode ) dp[0] += 1 ;
				dp ++ ;

				// �A�����T�`�P�Q�r�b�g���o��
				if( maxconbosize == 1 )
					*dp++ = (BYTE)( ( maxconbo >> 5 ) & 0xff ) ;

				// maxconbo �͂܂��g������ - MIN_COMPRESS ��������߂�
				maxconbo += MIN_COMPRESS ;

				// �o�͂��鑊�΃A�h���X�͂O��( ���݂̃A�h���X�|�P )��}���̂ŁA�|�P�������̂��o�͂���
				maxaddress -- ;

				// ���΃A�h���X���o��
				*dp++ = (BYTE)( maxaddress ) ;
				if( maxaddresssize > 0 )
				{
					*dp++ = (BYTE)( maxaddress >> 8 ) ;
					if( maxaddresssize == 2 )
						*dp++ = (BYTE)( maxaddress >> 16 ) ;
				}
			}
			
			// �o�̓T�C�Y�����Z
			dstsize += 3 + maxaddresssize + maxconbosize ;
			
			// ���X�g�ɏ���ǉ�
			if( srcaddress + maxconbo < SrcSize )
			{
				sp2 = &sp[1] ;
				for( j = 1 ; j < maxconbo && (DWORD_PTR)&sp2[2] - (DWORD_PTR)srcp < SrcSize ; j ++, sp2 ++ )
				{
					code = *((WORD *)sp2) ;
					list = (LZ_LIST *)( listfirsttable + code * sizeof( DWORD_PTR ) ) ;
					if( usesublistflagtable[code] == 1 )
					{
						list = (LZ_LIST *)( (DWORD_PTR *)list->next + sp2[2] ) ;
					}
					else
					{
						if( sublistnum < sublistmaxnum )
						{
							list->next = (LZ_LIST *)( sublistbuf + sizeof( DWORD_PTR ) * 256 * sublistnum ) ;
							list       = (LZ_LIST *)( (DWORD_PTR *)list->next + sp2[2] ) ;
						
							usesublistflagtable[code] = 1 ;
							sublistnum ++ ;
						}
					}

					newlist = &listbuf[listaddp] ;
					if( newlist->address != 0xffffffff )
					{
						if( newlist->prev ) newlist->prev->next = newlist->next ;
						if( newlist->next ) newlist->next->prev = newlist->prev ;
						newlist->address = 0xffffffff ;
					}
					newlist->address = srcaddress + j ;
					newlist->prev = list ;
					newlist->next = list->next ;
					if( list->next != NULL ) list->next->prev = newlist ;
					list->next = newlist ;
					listaddp = ( listaddp + 1 ) & maxlistnummask ;
				}
			}
			
			sp         += maxconbo ;
			srcaddress += maxconbo ;
		}
	}

	// ���k��̃f�[�^�T�C�Y��ۑ�����
	*((DWORD *)&destp[4]) = ( DWORD )( dstsize + 9 ) ;

	// �m�ۂ����������̉��
	DXFREE( usesublistflagtable ) ;

	// �f�[�^�̃T�C�Y��Ԃ�
	return dstsize + 9 ;
}

extern int DXA_Decode( void *Src, void *Dest )
{
	DWORD srcsize, destsize, code, indexsize, keycode, conbo, index = 0 ;
	BYTE *srcp, *destp, *dp, *sp ;

	destp = (BYTE *)Dest ;
	srcp  = (BYTE *)Src ;
	
	// �𓀌�̃f�[�^�T�C�Y�𓾂�
	destsize = GET_MEM_DWORD( &srcp[0] ) ;

	// ���k�f�[�^�̃T�C�Y�𓾂�
	srcsize = GET_MEM_DWORD( &srcp[4] ) - 9 ;

	// �L�[�R�[�h
	keycode = srcp[8] ;
	
	// �o�͐悪�Ȃ��ꍇ�̓T�C�Y�����Ԃ�
	if( Dest == NULL )
	{
		return ( int )destsize ;
	}
	
	// �W�J�J�n
	sp  = srcp + 9 ;
	dp  = destp ;
	while( srcsize )
	{
		// �L�[�R�[�h�������ŏ����𕪊�
		if( sp[0] != keycode )
		{
			// �񈳏k�R�[�h�̏ꍇ�͂��̂܂܏o��
			*dp = *sp ;
			dp      ++ ;
			sp      ++ ;
			srcsize -- ;
			continue ;
		}
	
		// �L�[�R�[�h���A�����Ă����ꍇ�̓L�[�R�[�h���̂��o��
		if( sp[1] == keycode )
		{
			*dp = (BYTE)keycode ;
			dp      ++ ;
			sp      += 2 ;
			srcsize -= 2 ;
			
			continue ;
		}

		// ���o�C�g�𓾂�
		code = sp[1] ;

		// �����L�[�R�[�h�����傫�Ȓl�������ꍇ�̓L�[�R�[�h
		// �Ƃ̃o�b�e�B���O�h�~�ׂ̈Ɂ{�P���Ă���̂Ł|�P����
		if( code > keycode ) code -- ;

		sp      += 2 ;
		srcsize -= 2 ;

		// �A�������擾����
		conbo = code >> 3 ;
		if( code & ( 0x1 << 2 ) )
		{
			conbo |= *sp << 5 ;
			sp      ++ ;
			srcsize -- ;
		}
		conbo += MIN_COMPRESS ;	// �ۑ����Ɍ��Z�����ŏ����k�o�C�g���𑫂�

		// �Q�Ƒ��΃A�h���X���擾����
		indexsize = code & 0x3 ;
		switch( indexsize )
		{
		case 0 :
			index = *sp ;
			sp      ++ ;
			srcsize -- ;
			break ;
			
		case 1 :
			index = GET_MEM_WORD( sp ) ;
			sp      += 2 ;
			srcsize -= 2 ;
			break ;
			
		case 2 :
			index = ( DWORD )( GET_MEM_WORD( sp ) | ( sp[2] << 16 ) ) ;
			sp      += 3 ;
			srcsize -= 3 ;
			break ;
		}
		index ++ ;		// �ۑ����Ɂ|�P���Ă���̂Ł{�P����

		// �W�J
		if( index < conbo )
		{
			DWORD num ;

			num  = index ;
			while( conbo > num )
			{
				_MEMCPY( dp, dp - num, num ) ;
				dp    += num ;
				conbo -= num ;
				num   += num ;
			}
			if( conbo != 0 )
			{
				_MEMCPY( dp, dp - num, conbo ) ;
				dp += conbo ;
			}
		}
		else
		{
			_MEMCPY( dp, dp - index, conbo ) ;
			dp += conbo ;
		}
	}

	// �𓀌�̃T�C�Y��Ԃ�
	return (int)destsize ;
}

// �f�[�^���n�t�}�����k����( �߂�l:���k��̃T�C�Y  0 �̓G���[  Dest �� NULL ������ƈ��k�f�[�^�i�[�ɕK�v�ȃT�C�Y���Ԃ� )
extern ULONGLONG Huffman_Encode( void *Src, ULONGLONG SrcSize, void *Dest )
{
    // �����f�[�^�Ɛ��l�f�[�^�A�O�`�Q�T�T�܂ł����l�f�[�^
    // (�����f�[�^�̐��ƈ��k����f�[�^�̎�ނ̐��𑫂��ƕK���w��ނ̐��{(��ނ̐��|�P)�x�ɂȂ�B
    // �w�z���g���H�x�Ǝv������̓n�t�}�����k�̐����ŏo�Ă����`,�a,�b,�c,�d�̌��������̐���
    // �����Ă݂ĉ������A��ނ��T�ɑ΂��Č��������͈���Ȃ��S�ɂȂ��Ă���͂��ł��B
    // ��ނ��U�̎��͌��������͂T�ɁA�����Ď�ނ��Q�T�U���̎��͌��������͂Q�T�T�ɂȂ�܂�)
    HUFFMAN_NODE Node[256 + 255] ;

    unsigned char *SrcPoint ;
    ULONGLONG PressBitCounter, PressSizeCounter, SrcSizeCounter ;
    ULONGLONG i ;

    // void �^�̃|�C���^�ł̓A�h���X�̑��삪�o���Ȃ��̂� unsigned char �^�̃|�C���^�ɂ���
    SrcPoint = ( unsigned char * )Src ;

    // �e���l�̈��k��̃r�b�g����Z�o����
    {
        int NodeIndex, MinNode1, MinNode2 ;
        int NodeNum, DataNum ;

        // ���l�f�[�^������������
        for( i = 0 ; i < 256 ; i ++ )
        {
            Node[i].Weight = 0 ;           // �o�����͂��ꂩ��Z�o����̂łO�ɏ�����
            Node[i].ChildNode[0] = -1 ;    // ���l�f�[�^���I�_�Ȃ̂� -1 ���Z�b�g����
            Node[i].ChildNode[1] = -1 ;    // ���l�f�[�^���I�_�Ȃ̂� -1 ���Z�b�g����
            Node[i].ParentNode = -1 ;      // �܂��ǂ̗v�f�Ƃ���������Ă��Ȃ��̂� -1 ���Z�b�g����
        }

        // �e���l�̏o�������J�E���g
        for( i = 0 ; i < SrcSize ; i ++ )
        {
            Node[ SrcPoint[i] ].Weight ++ ;
        }

		// �o������ 0�`65535 �̔䗦�ɕϊ�����
		for( i = 0 ; i < 256 ; i ++ )
		{
			Node[ i ].Weight = Node[ i ].Weight * 0xffff / SrcSize ;
		}

        // �o�����̏��Ȃ����l�f�[�^ or �����f�[�^���q����
        // �V���������f�[�^���쐬�A�S�Ă̗v�f���q���Ŏc��P�ɂȂ�܂ŌJ��Ԃ�
        DataNum = 256 ; // �c��v�f��
        NodeNum = 256 ; // ���ɐV������錋���f�[�^�̗v�f�z��̃C���f�b�N�X
        while( DataNum > 1 )
        {
            // �o�����l�̒Ⴂ�v�f���T��
            {
                MinNode1 = -1 ;
                MinNode2 = -1 ;
                
                // �c���Ă���v�f�S�Ă𒲂ׂ�܂Ń��[�v
                NodeIndex = 0 ;
                for( i = 0 ; i < ( ULONGLONG )DataNum ; NodeIndex ++ )
                {
                    // �������ɉ������̗v�f�ƌ�������Ă���ꍇ�͑ΏۊO
                    if( Node[NodeIndex].ParentNode != -1 ) continue ;
                    
                    i ++ ;
                    
                    // �܂��L���ȗv�f���Z�b�g���Ă��Ȃ����A���o�����l��
                    // ���Ȃ��v�f������������X�V
                    if( MinNode1 == -1 || Node[MinNode1].Weight > Node[NodeIndex].Weight )
                    {
                        // ���܂ň�ԏo�����l�����Ȃ������Ǝv��ꂽ
                        // �v�f�͓�Ԗڂɍ~�i
                        MinNode2 = MinNode1 ;

                        // �V������Ԃ̗v�f�̗v�f�z��̃C���f�b�N�X��ۑ�
                        MinNode1 = NodeIndex ;
                    }
                    else
                    {
                        // ��Ԃ��͏o�����l�������Ă��A��Ԗڂ��͏o�����l��
                        // ���Ȃ���������Ȃ��̂ňꉞ�`�F�b�N(���͓�Ԗڂɏo�����l��
                        // ���Ȃ��v�f���Z�b�g����Ă��Ȃ������ꍇ���Z�b�g)
                        if( MinNode2 == -1 || Node[MinNode2].Weight > Node[NodeIndex].Weight )
                        {
                            MinNode2 = NodeIndex ;
                        }
                    }
                }
            }
            
            // ��̗v�f���q���ŐV�����v�f(�����f�[�^)�����
            Node[NodeNum].ParentNode = -1 ;  // �V�����f�[�^�͓��R�܂������Ƃ��q�����Ă��Ȃ��̂� -1 
            Node[NodeNum].Weight = Node[MinNode1].Weight + Node[MinNode2].Weight ;    // �o�����l�͓�̐��l�𑫂������̂��Z�b�g����
            Node[NodeNum].ChildNode[0] = MinNode1 ;    // ���̌������� 0 ��I�񂾂�o�����l����ԏ��Ȃ��v�f�Ɍq����
            Node[NodeNum].ChildNode[1] = MinNode2 ;    // ���̌������� 1 ��I�񂾂�o�����l����Ԗڂɏ��Ȃ��v�f�Ɍq����

            // �������ꂽ�v�f��ɁA�����B�ɉ��̒l�����蓖�Ă�ꂽ�����Z�b�g����
            Node[MinNode1].Index = 0 ;    // ��ԏo�����l�����Ȃ��v�f�� 0 ��
            Node[MinNode2].Index = 1 ;    // ��Ԗڂɏo�����l�����Ȃ��v�f�� 1 ��

            // �������ꂽ�v�f��ɁA�����B���������������f�[�^�̗v�f�z��C���f�b�N�X���Z�b�g����
            Node[MinNode1].ParentNode = NodeNum ;
            Node[MinNode2].ParentNode = NodeNum ;

            // �v�f�̐�������₷
            NodeNum ++ ;

            // �c��v�f�̐��́A��v�f���V�����ǉ����ꂽ�����
            // ��̗v�f����������Č����̑Ώۂ���O�ꂽ�̂�
            // ���� 1 - 2 �� -1 
            DataNum -- ;
        }
        
        // �e���l�̈��k��̃r�b�g�������o��
        {
            unsigned char TempBitArray[32] ;
            int TempBitIndex, TempBitCount, BitIndex, BitCount ;
        
            // ���l�f�[�^�̎�ނ̐������J��Ԃ�
            for( i = 0 ; i < 256 ; i ++ )
            {
                // ���l�f�[�^���猋���f�[�^����֏�ւƒH���ăr�b�g���𐔂���
                {
                    // �r�b�g�������������Ă���
                    Node[i].BitNum = 0 ;
                    
                    // �ꎞ�I�ɐ��l�f�[�^����k���Ă������Ƃ��̃r�b�g���ۑ����鏈���̏���
                    TempBitIndex = 0 ;
                    TempBitCount = 0 ;
                    TempBitArray[TempBitIndex] = 0 ;
                    
                    // �������ƌ�������Ă������J�E���g��������(�V�ӂ͉����Ƃ���������Ă��Ȃ��̂ŏI�_���ƕ�����)
                    for( NodeIndex = ( int )i ; Node[NodeIndex].ParentNode != -1 ; NodeIndex = Node[NodeIndex].ParentNode )
                    {
                        // �z��v�f��ɓ���r�b�g�f�[�^�͂W�Ȃ̂ŁA�����z��v�f��
                        // ���ɂW�ۑ����Ă����玟�̔z��v�f�ɕۑ����ύX����
                        if( TempBitCount == 8 )
                        {
                            TempBitCount = 0 ;
                            TempBitIndex ++ ;
                            TempBitArray[TempBitIndex] = 0 ;
                        }
                        
                        // �V�����������ޏ��ō��܂ł̃f�[�^���㏑�����Ă��܂�Ȃ��悤�ɂP�r�b�g���ɃV�t�g����
                        TempBitArray[TempBitIndex] <<= 1 ;

                        // �����f�[�^�Ɋ���U��ꂽ�C���f�b�N�X���ŉ��ʃr�b�g(��ԉE���̃r�b�g)�ɏ�������
                        TempBitArray[TempBitIndex] |= (unsigned char)Node[NodeIndex].Index ;

                        // �ۑ������r�b�g���𑝂₷
                        TempBitCount ++ ;

                        // �r�b�g���𑝂₷
                        Node[i].BitNum ++ ;
                    }
                }
				
                // TempBitArray �ɗ��܂����f�[�^�͐��l�f�[�^���猋���f�[�^��V�ӂɌ�������
                // ��֏�ւƑk���Ă��������̃r�b�g��Ȃ̂ŁA�t���܂ɂ��Ȃ��ƈ��k��̃r�b�g
                // �z��Ƃ��Ďg���Ȃ�(�W�J���ɓV�ӂ̌����f�[�^���琔�l�f�[�^�܂ŒH�邱�Ƃ�
                // �o���Ȃ�)�̂ŁA�������t���܂ɂ������̂𐔒l�f�[�^���̃r�b�g��o�b�t�@�ɕۑ�����
                {
                    BitCount = 0 ;
                    BitIndex = 0 ;
                    
                    // �ŏ��̃o�b�t�@�����������Ă���
                    // (�S�� �_���a(or)���Z �ŏ������ނ̂ŁA�ŏ�����P�ɂȂ��Ă���
                    // �r�b�g�ɂO����������ł��P�̂܂܂ɂȂ��Ă��܂�����)
                    Node[i].BitArray[BitIndex] = 0 ;
                    
                    // �ꎞ�I�ɕۑ����Ă������r�b�g��̍ŏ��܂ők��
                    while( TempBitIndex >= 0 )
                    {
                        // �������񂾃r�b�g������̔z��v�f�ɓ���W�r�b�g��
                        // �B���Ă��܂����玟�̔z��v�f�Ɉڂ�
                        if( BitCount == 8 )
                        {
                            BitCount = 0 ;
                            BitIndex ++ ;
                            Node[i].BitArray[BitIndex] = 0 ;
                        }

                        // �܂������������܂�Ă��Ȃ��r�b�g�A�h���X�ɂP�r�b�g��������
                        Node[i].BitArray[BitIndex] |= (unsigned char)( ( TempBitArray[TempBitIndex] & 1 ) << BitCount ) ;
						
                        // �������ݏI������r�b�g�͂�������Ȃ��̂Ŏ��̃r�b�g��
                        // �������߂�悤�ɂP�r�b�g�E�ɃV�t�g����
                        TempBitArray[TempBitIndex] >>= 1 ;
                        
                        // �P�r�b�g�������񂾂̂Ŏc��r�b�g�����P���炷
                        TempBitCount -- ;
                        
                        // �������ݏ������݌��ƂȂ��Ă���z��v�f�ɏ�������ł��Ȃ�
                        // �r�b�g��񂪖����Ȃ����玟�̔z��v�f�Ɉڂ�
                        if( TempBitCount == 0 )
                        {
                            TempBitIndex -- ;
                            TempBitCount = 8 ;
                        }
                        
                        // �������񂾃r�b�g���𑝂₷
                        BitCount ++ ;
                    }
                }
            }
        }
    }

    // �ϊ�����
    {
        unsigned char *PressData ;
        int BitData, BitCounter, BitIndex, BitNum, NodeIndex ;
        
        // ���k�f�[�^���i�[����A�h���X���Z�b�g
        // (���k�f�[�^�{�̂͌��̃T�C�Y�A���k��̃T�C�Y�A�e���l�̏o��������
        // �i�[����f�[�^�̈�̌�Ɋi�[����)
        PressData = ( unsigned char * )Dest ;
        
        // ���k����f�[�^�̎Q�ƃA�h���X��������
        SrcSizeCounter = 0 ;
        
        // ���k�����f�[�^�̎Q�ƃA�h���X��������
        PressSizeCounter = 0 ;
        
        // ���k�����r�b�g�f�[�^�̃J�E���^��������
        PressBitCounter = 0 ;
        
        // ���k�f�[�^�̍ŏ��̃o�C�g�����������Ă���
        if( Dest != NULL ) PressData[PressSizeCounter] = 0 ;

        // ���k�ΏƂ̃f�[�^��S�Ĉ��k��̃r�b�g��ɕϊ�����܂Ń��[�v
        for( SrcSizeCounter = 0 ; SrcSizeCounter < SrcSize ; SrcSizeCounter ++ )
        {
            // �ۑ����鐔�l�f�[�^�̃C���f�b�N�X���擾
            NodeIndex = SrcPoint[SrcSizeCounter] ;
            
            // �w��̐��l�f�[�^�̈��k��̃r�b�g����o��
            {
                // �Q�Ƃ���z��̃C���f�b�N�X��������
                BitIndex = 0 ;
                
                // �z��v�f���̏o�͂����r�b�g���̏�����
                BitNum = 0 ;
                
                // �ŏ��ɏ������ރr�b�g��̔z��v�f���Z�b�g
                BitData = Node[NodeIndex].BitArray[0] ;

                // �S�Ẵr�b�g���o�͂���܂Ń��[�v
                for( BitCounter = 0 ; BitCounter < Node[NodeIndex].BitNum ; BitCounter ++ )
                {
                    // �����������񂾃r�b�g�����W�ɂȂ��Ă����玟�̔z��v�f�Ɉڂ�
                    if( PressBitCounter == 8 )
                    {
                        PressSizeCounter ++ ;
                        if( Dest != NULL ) PressData[PressSizeCounter] = 0 ;
                        PressBitCounter = 0 ;
                    }
                    
                    // ���������o�����r�b�g�����W�ɂȂ��Ă����玟�̔z��v�f�Ɉڂ�
                    if( BitNum == 8 )
                    {
                        BitIndex ++ ;
                        BitData = Node[NodeIndex].BitArray[BitIndex] ;
                        BitNum = 0 ;
                    }
                    
                    // �܂������������܂�Ă��Ȃ��r�b�g�A�h���X�ɂP�r�b�g��������
                    if( Dest != NULL ) PressData[PressSizeCounter] |= (unsigned char)( ( BitData & 1 ) << PressBitCounter ) ;

                    // �������񂾃r�b�g���𑝂₷
                    PressBitCounter ++ ;

                    // ���ɏ����o���r�b�g���ŉ��ʃr�b�g(��ԉE�̃r�b�g)�ɂ���ׂ�
                    // �P�r�b�g�E�V�t�g����
                    BitData >>= 1 ;
                    
                    // �����o�����r�b�g���𑝂₷
                    BitNum ++ ;
                }
            }
        }
        
        // �Ō�̂P�o�C�g���̃T�C�Y�𑫂�
        PressSizeCounter ++ ;
    }
    
    // ���k�f�[�^�̏���ۑ�����
    {
		BIT_STREAM BitStream ;
		BYTE HeadBuffer[ 256 * 2 + 32 ] ;
		BYTE BitNum ;
		ULONGLONG HeadSize ;
		int WeightSaveData[ 256 ] ;

		BitStream_Init( &BitStream, HeadBuffer, false ) ;

        // ���̃f�[�^�̃T�C�Y���Z�b�g
		BitNum = BitStream_GetBitNum( SrcSize ) ;
		if( BitNum > 0 )
		{
			BitNum -- ;
		}
        BitStream_Write( &BitStream, 6, BitNum ) ;
		BitStream_Write( &BitStream, BitNum + 1, SrcSize ) ;
        
        // ���k��̃f�[�^�̃T�C�Y���Z�b�g
		BitNum = BitStream_GetBitNum( PressSizeCounter ) ;
        BitStream_Write( &BitStream, 6, BitNum ) ;
		BitStream_Write( &BitStream, BitNum + 1, PressSizeCounter ) ;
        
        // �e���l�̏o�����̍����l��ۑ�����
		WeightSaveData[ 0 ] = ( int )Node[ 0 ].Weight ;
        for( i = 1 ; i < 256 ; i ++ )
        {
			WeightSaveData[ i ] = ( int )Node[ i ].Weight - ( int )Node[ i - 1 ].Weight ;
        }
        for( i = 0 ; i < 256 ; i ++ )
        {
			ULONGLONG OutputNum ;
			bool Minus ;

			if( WeightSaveData[ i ] < 0 )
			{
				OutputNum = ( ULONGLONG )( -WeightSaveData[ i ] ) ;
				Minus = true ;
			}
			else
			{
				OutputNum = ( ULONGLONG )WeightSaveData[ i ] ;
				Minus = false ;
			}

			BitNum = ( BitStream_GetBitNum( OutputNum ) + 1 ) / 2 ;
			if( BitNum > 0 )
			{
				BitNum -- ;
			}
	        BitStream_Write( &BitStream, 3, BitNum ) ;
			BitStream_Write( &BitStream, 1, Minus ? 1 : 0 ) ;
			BitStream_Write( &BitStream, ( BitNum + 1 ) * 2, OutputNum ) ;
        }
		
		// �w�b�_�T�C�Y���擾
		HeadSize = BitStream_GetBytes( &BitStream ) ;

		// ���k�f�[�^�̏������k�f�[�^�ɃR�s�[����
		if( Dest != NULL )
		{
			ULONGLONG j ;

			// �w�b�_�̕������ړ�
			for( j = PressSizeCounter - 1 ; j >= 0 ; j -- )
			{
				( ( BYTE * )Dest )[ HeadSize + j ] = ( ( BYTE * )Dest )[ j ] ;
				if( j == 0 )
				{
					break ;
				}
			}

			// �w�b�_����������
			_MEMCPY( Dest, HeadBuffer, ( size_t )HeadSize ) ;
		}

		// ���k��̃T�C�Y��Ԃ�
		return PressSizeCounter + HeadSize ;
    }
}

// �n�t�}�����k���ꂽ�f�[�^���𓀂���( �߂�l:�𓀌�̃T�C�Y  0 �̓G���[  Dest �� NULL ������Ɖ𓀃f�[�^�i�[�ɕK�v�ȃT�C�Y���Ԃ� )
extern ULONGLONG Huffman_Decode( void *Press, void *Dest )
{
    // �����f�[�^�Ɛ��l�f�[�^�A�O�`�Q�T�T�܂ł����l�f�[�^
    HUFFMAN_NODE Node[256 + 255] ;

    ULONGLONG PressSizeCounter, DestSizeCounter, DestSize ;
    unsigned char *PressPoint, *DestPoint ;
	ULONGLONG OriginalSize ;
//	ULONGLONG PressSize ;
	ULONGLONG HeadSize ;
	WORD Weight[ 256 ] ;
    int i ;

    // void �^�̃|�C���^�ł̓A�h���X�̑��삪�o���Ȃ��̂� unsigned char �^�̃|�C���^�ɂ���
    PressPoint = ( unsigned char * )Press ;
    DestPoint = ( unsigned char * )Dest ;

    // ���k�f�[�^�̏����擾����
	{
		BIT_STREAM BitStream ;
		BYTE BitNum ;
		BYTE Minus ;
		WORD SaveData ;

		BitStream_Init( &BitStream, PressPoint, true ) ;

		OriginalSize = BitStream_Read( &BitStream, ( BYTE )( BitStream_Read( &BitStream, 6 ) + 1 ) ) ;
//		PressSize    = BitStream_Read( &BitStream, ( BYTE )( BitStream_Read( &BitStream, 6 ) + 1 ) ) ;
		BitStream_Read( &BitStream, ( BYTE )( BitStream_Read( &BitStream, 6 ) + 1 ) ) ;

		// �o���p�x�̃e�[�u���𕜌�����
		BitNum      = ( BYTE )( BitStream_Read( &BitStream, 3 ) + 1 ) * 2 ;
		Minus       = ( BYTE )BitStream_Read( &BitStream, 1 ) ;
		SaveData    = ( WORD )BitStream_Read( &BitStream, BitNum ) ;
		Weight[ 0 ] = SaveData ;
        for( i = 1 ; i < 256 ; i ++ )
        {
			BitNum      = ( BYTE )( BitStream_Read( &BitStream, 3 ) + 1 ) * 2 ;
			Minus       = ( BYTE )BitStream_Read( &BitStream, 1 ) ;
			SaveData    = ( WORD )BitStream_Read( &BitStream, BitNum ) ;
			Weight[ i ] = Minus == 1 ? Weight[ i - 1 ] - SaveData : Weight[ i - 1 ] + SaveData ;
        }

		HeadSize = BitStream_GetBytes( &BitStream ) ;
	}
    
    // Dest �� NULL �̏ꍇ�� �𓀌�̃f�[�^�̃T�C�Y��Ԃ�
    if( Dest == NULL )
        return OriginalSize ;

    // �𓀌�̃f�[�^�̃T�C�Y���擾����
    DestSize = OriginalSize ;

    // �e���l�̌����f�[�^���\�z����
    {
        int NodeIndex, MinNode1, MinNode2 ;
        int NodeNum, DataNum ;

        // ���l�f�[�^������������
        for( i = 0 ; i < 256 + 255 ; i ++ )
        {
            Node[i].Weight = i < 256 ? Weight[i] : 0 ;	// �o�����͕ۑ����Ă������f�[�^����R�s�[
            Node[i].ChildNode[0] = -1 ;					// ���l�f�[�^���I�_�Ȃ̂� -1 ���Z�b�g����
            Node[i].ChildNode[1] = -1 ;					// ���l�f�[�^���I�_�Ȃ̂� -1 ���Z�b�g����
            Node[i].ParentNode = -1 ;					// �܂��ǂ̗v�f�Ƃ���������Ă��Ȃ��̂� -1 ���Z�b�g����
        }

        // �o�����̏��Ȃ����l�f�[�^ or �����f�[�^���q����
        // �V���������f�[�^���쐬�A�S�Ă̗v�f���q���Ŏc��P�ɂȂ�܂ŌJ��Ԃ�
        // (���k���Ɠ����R�[�h�ł�)
        DataNum = 256 ; // �c��v�f��
        NodeNum = 256 ; // ���ɐV������錋���f�[�^�̗v�f�z��̃C���f�b�N�X
        while( DataNum > 1 )
        {
            // �o�����l�̒Ⴂ�v�f���T��
            {
                MinNode1 = -1 ;
                MinNode2 = -1 ;
                
                // �c���Ă���v�f�S�Ă𒲂ׂ�܂Ń��[�v
                NodeIndex = 0 ;
                for( i = 0 ; i < DataNum ; NodeIndex ++ )
                {
                    // �������ɉ������̗v�f�ƌ�������Ă���ꍇ�͑ΏۊO
                    if( Node[NodeIndex].ParentNode != -1 ) continue ;
                    
                    i ++ ;
                    
                    // �܂��L���ȗv�f���Z�b�g���Ă��Ȃ����A���o�����l��
                    // ���Ȃ��v�f������������X�V
                    if( MinNode1 == -1 || Node[MinNode1].Weight > Node[NodeIndex].Weight )
                    {
                        // ���܂ň�ԏo�����l�����Ȃ������Ǝv��ꂽ
                        // �v�f�͓�Ԗڂɍ~�i
                        MinNode2 = MinNode1 ;

                        // �V������Ԃ̗v�f�̗v�f�z��̃C���f�b�N�X��ۑ�
                        MinNode1 = NodeIndex ;
                    }
                    else
                    {
                        // ��Ԃ��͏o�����l�������Ă��A��Ԗڂ��͏o�����l��
                        // ���Ȃ���������Ȃ��̂ňꉞ�`�F�b�N(���͓�Ԗڂɏo�����l��
                        // ���Ȃ��v�f���Z�b�g����Ă��Ȃ������ꍇ���Z�b�g)
                        if( MinNode2 == -1 || Node[MinNode2].Weight > Node[NodeIndex].Weight )
                        {
                            MinNode2 = NodeIndex ;
                        }
                    }
                }
            }
            
            // ��̗v�f���q���ŐV�����v�f(�����f�[�^)�����
            Node[NodeNum].ParentNode = -1 ;  // �V�����f�[�^�͓��R�܂������Ƃ��q�����Ă��Ȃ��̂� -1 
            Node[NodeNum].Weight = Node[MinNode1].Weight + Node[MinNode2].Weight ;    // �o�����l�͓�̐��l�𑫂������̂��Z�b�g����
            Node[NodeNum].ChildNode[0] = MinNode1 ;    // ���̌������� 0 ��I�񂾂�o�����l����ԏ��Ȃ��v�f�Ɍq����
            Node[NodeNum].ChildNode[1] = MinNode2 ;    // ���̌������� 1 ��I�񂾂�o�����l����Ԗڂɏ��Ȃ��v�f�Ɍq����

            // �������ꂽ�v�f��ɁA�����B�ɉ��̒l�����蓖�Ă�ꂽ�����Z�b�g����
            Node[MinNode1].Index = 0 ;    // ��ԏo�����l�����Ȃ��v�f�� 0 ��
            Node[MinNode2].Index = 1 ;    // ��Ԗڂɏo�����l�����Ȃ��v�f�� 1 ��

            // �������ꂽ�v�f��ɁA�����B���������������f�[�^�̗v�f�z��C���f�b�N�X���Z�b�g����
            Node[MinNode1].ParentNode = NodeNum ;
            Node[MinNode2].ParentNode = NodeNum ;

            // �v�f�̐�������₷
            NodeNum ++ ;

            // �c��v�f�̐��́A��v�f���V�����ǉ����ꂽ�����
            // ��̗v�f����������Č����̑Ώۂ���O�ꂽ�̂�
            // ���� 1 - 2 �� -1 
            DataNum -- ;
        }

        // �e���l�̈��k���̃r�b�g�������o��
        {
            unsigned char TempBitArray[32] ;
            int TempBitIndex, TempBitCount, BitIndex, BitCount ;
        
            // ���l�f�[�^�ƌ����f�[�^�̐������J��Ԃ�
            for( i = 0 ; i < 256 + 254 ; i ++ )
            {
                // ���l�f�[�^���猋���f�[�^����֏�ւƒH���ăr�b�g���𐔂���
                {
                    // �r�b�g�������������Ă���
                    Node[i].BitNum = 0 ;
                    
                    // �ꎞ�I�ɐ��l�f�[�^����k���Ă������Ƃ��̃r�b�g���ۑ����鏈���̏���
                    TempBitIndex = 0 ;
                    TempBitCount = 0 ;
                    TempBitArray[TempBitIndex] = 0 ;
                    
                    // �������ƌ�������Ă������J�E���g��������(�V�ӂ͉����Ƃ���������Ă��Ȃ��̂ŏI�_���ƕ�����)
                    for( NodeIndex = ( int )i ; Node[NodeIndex].ParentNode != -1 ; NodeIndex = Node[NodeIndex].ParentNode )
                    {
                        // �z��v�f��ɓ���r�b�g�f�[�^�͂W�Ȃ̂ŁA�����z��v�f��
                        // ���ɂW�ۑ����Ă����玟�̔z��v�f�ɕۑ����ύX����
                        if( TempBitCount == 8 )
                        {
                            TempBitCount = 0 ;
                            TempBitIndex ++ ;
                            TempBitArray[TempBitIndex] = 0 ;
                        }
                        
                        // �V�����������ޏ��ō��܂ł̃f�[�^���㏑�����Ă��܂�Ȃ��悤�ɂP�r�b�g���ɃV�t�g����
                        TempBitArray[TempBitIndex] <<= 1 ;

                        // �����f�[�^�Ɋ���U��ꂽ�C���f�b�N�X���ŉ��ʃr�b�g(��ԉE���̃r�b�g)�ɏ�������
                        TempBitArray[TempBitIndex] |= (unsigned char)Node[NodeIndex].Index ;

                        // �ۑ������r�b�g���𑝂₷
                        TempBitCount ++ ;

                        // �r�b�g���𑝂₷
                        Node[i].BitNum ++ ;
                    }
                }
				
                // TempBitArray �ɗ��܂����f�[�^�͐��l�f�[�^���猋���f�[�^��V�ӂɌ�������
                // ��֏�ւƑk���Ă��������̃r�b�g��Ȃ̂ŁA�t���܂ɂ��Ȃ��ƈ��k��̃r�b�g
                // �z��Ƃ��Ďg���Ȃ�(�W�J���ɓV�ӂ̌����f�[�^���琔�l�f�[�^�܂ŒH�邱�Ƃ�
                // �o���Ȃ�)�̂ŁA�������t���܂ɂ������̂𐔒l�f�[�^���̃r�b�g��o�b�t�@�ɕۑ�����
                {
                    BitCount = 0 ;
                    BitIndex = 0 ;
                    
                    // �ŏ��̃o�b�t�@�����������Ă���
                    // (�S�� �_���a(or)���Z �ŏ������ނ̂ŁA�ŏ�����P�ɂȂ��Ă���
                    // �r�b�g�ɂO����������ł��P�̂܂܂ɂȂ��Ă��܂�����)
                    Node[i].BitArray[BitIndex] = 0 ;
                    
                    // �ꎞ�I�ɕۑ����Ă������r�b�g��̍ŏ��܂ők��
                    while( TempBitIndex >= 0 )
                    {
                        // �������񂾃r�b�g������̔z��v�f�ɓ���W�r�b�g��
                        // �B���Ă��܂����玟�̔z��v�f�Ɉڂ�
                        if( BitCount == 8 )
                        {
                            BitCount = 0 ;
                            BitIndex ++ ;
                            Node[i].BitArray[BitIndex] = 0 ;
                        }

                        // �܂������������܂�Ă��Ȃ��r�b�g�A�h���X�ɂP�r�b�g��������
                        Node[i].BitArray[BitIndex] |= (unsigned char)( ( TempBitArray[TempBitIndex] & 1 ) << BitCount ) ;
						
                        // �������ݏI������r�b�g�͂�������Ȃ��̂Ŏ��̃r�b�g��
                        // �������߂�悤�ɂP�r�b�g�E�ɃV�t�g����
                        TempBitArray[TempBitIndex] >>= 1 ;
                        
                        // �P�r�b�g�������񂾂̂Ŏc��r�b�g�����P���炷
                        TempBitCount -- ;
                        
                        // �������ݏ������݌��ƂȂ��Ă���z��v�f�ɏ�������ł��Ȃ�
                        // �r�b�g��񂪖����Ȃ����玟�̔z��v�f�Ɉڂ�
                        if( TempBitCount == 0 )
                        {
                            TempBitIndex -- ;
                            TempBitCount = 8 ;
                        }
                        
                        // �������񂾃r�b�g���𑝂₷
                        BitCount ++ ;
                    }
                }
            }
		}
    }

    // �𓀏���
    {
        unsigned char *PressData ;
        int PressBitCounter, PressBitData, Index, NodeIndex ;
		int NodeIndexTable[ 512 ] ;
		int j ;

		// �e�r�b�g�z�񂪂ǂ̃m�[�h�Ɍq���邩�̃e�[�u�����쐬����
		{
			WORD BitMask[ 9 ] ;

			for( i = 0 ; i < 9 ; i ++ )
			{
				BitMask[ i ] = ( WORD )( ( 1 << ( i + 1 ) ) - 1 ) ;
			}

			for( i = 0 ; i < 512 ; i ++ )
			{
				NodeIndexTable[ i ] = -1 ;

				// �r�b�g��ɓK�������m�[�h��T��
				for( j = 0 ; j < 256 + 254 ; j ++ )
				{
					WORD BitArray01 ;

					if( Node[ j ].BitNum > 9 )
					{
						continue ;
					}

					BitArray01 = ( WORD )Node[ j ].BitArray[ 0 ] | ( Node[ j ].BitArray[ 1 ] << 8 ) ;
					if( ( i & BitMask[ Node[ j ].BitNum - 1 ] ) == ( BitArray01 & BitMask[ Node[ j ].BitNum - 1 ] ) )
					{
						NodeIndexTable[ i ] = j ;
						break ;
					}
				}
			}
		}

        // ���k�f�[�^�{�̂̐擪�A�h���X���Z�b�g
        // (���k�f�[�^�{�̂͌��̃T�C�Y�A���k��̃T�C�Y�A�e���l�̏o��������
        // �i�[����f�[�^�̈�̌�ɂ���)
        PressData = PressPoint + HeadSize ;

        // �𓀂����f�[�^�̊i�[�A�h���X��������
        DestSizeCounter = 0 ;
        
        // ���k�f�[�^�̎Q�ƃA�h���X��������
        PressSizeCounter = 0 ;
        
        // ���k�r�b�g�f�[�^�̃J�E���^��������
        PressBitCounter = 0 ;
        
        // ���k�f�[�^�̂P�o�C�g�ڂ��Z�b�g
        PressBitData = PressData[PressSizeCounter] ;

        // ���k�O�̃f�[�^�T�C�Y�ɂȂ�܂ŉ𓀏������J��Ԃ�
        for( DestSizeCounter = 0 ; DestSizeCounter < DestSize ; DestSizeCounter ++ )
        {
            // �r�b�g�񂩂琔�l�f�[�^����������
            {
				// �Ō��17byte���̃f�[�^�͓V�ӂ���T��( �Ō�̎��̃o�C�g��ǂݏo�����Ƃ��ă������̕s���ȃA�N�Z�X�ɂȂ�\�������邽�� )
				if( DestSizeCounter >= DestSize - 17 )
				{
					// �����f�[�^�̓V�ӂ͈�ԍŌ�̌����f�[�^���i�[�����T�P�O�Ԗ�(�O�Ԃ��琔����)
					// �V�ӂ��珇�ɉ��ɍ~��Ă���
					NodeIndex = 510 ;
				}
				else
				{
					// ����ȊO�̏ꍇ�̓e�[�u�����g�p����

                    // ���� PressBitData �Ɋi�[����Ă���S�Ă�
                    // �r�b�g�f�[�^���g���؂��Ă��܂����ꍇ�͎���
                    // �r�b�g�f�[�^���Z�b�g����
                    if( PressBitCounter == 8 )
                    {
                        PressSizeCounter ++ ;
                        PressBitData = PressData[PressSizeCounter] ;
                        PressBitCounter = 0 ;
                    }

					// ���k�f�[�^��9bit���p�ӂ���
					PressBitData = ( PressBitData | ( PressData[ PressSizeCounter + 1 ] << ( 8 - PressBitCounter ) ) ) & 0x1ff ;

					// �e�[�u������ŏ��̌����f�[�^��T��
					NodeIndex = NodeIndexTable[ PressBitData ] ;

					// �g���������k�f�[�^�̃A�h���X��i�߂�
					PressBitCounter += Node[ NodeIndex ].BitNum ;
					if( PressBitCounter >= 16 )
					{
						PressSizeCounter += 2 ;
						PressBitCounter -= 16 ;
						PressBitData = PressData[PressSizeCounter] >> PressBitCounter ;
					}
					else
					if( PressBitCounter >= 8 )
					{
						PressSizeCounter ++ ;
						PressBitCounter -= 8 ;
						PressBitData = PressData[PressSizeCounter] >> PressBitCounter ;
					}
					else
					{
						PressBitData >>= Node[ NodeIndex ].BitNum ;
					}
				}
                
                // ���l�f�[�^�ɒH�蒅���܂Ō����f�[�^������Ă���
                while( NodeIndex > 255 )
                {
                    // ���� PressBitData �Ɋi�[����Ă���S�Ă�
                    // �r�b�g�f�[�^���g���؂��Ă��܂����ꍇ�͎���
                    // �r�b�g�f�[�^���Z�b�g����
                    if( PressBitCounter == 8 )
                    {
                        PressSizeCounter ++ ;
                        PressBitData = PressData[PressSizeCounter] ;
                        PressBitCounter = 0 ;
                    }
                    
                    // �P�r�b�g�擾����
                    Index = PressBitData & 1 ;
                    
                    // �g�p�����P�r�b�g�������E�ɃV�t�g����
                    PressBitData >>= 1 ;
                    
                    // �g�p�����r�b�g��������₷
                    PressBitCounter ++ ;
                    
                    // ���̗v�f(�����f�[�^�����l�f�[�^���͂܂�������Ȃ�)�Ɉڂ�
                    NodeIndex = Node[NodeIndex].ChildNode[Index] ;
                }
            }

            // �H�蒅�������l�f�[�^���o��
            DestPoint[DestSizeCounter] = (unsigned char)NodeIndex ;
        }
    }

    // �𓀌�̃T�C�Y��Ԃ�
    return OriginalSize ;
}

// �o�C�i���f�[�^�𔼊p������ɕϊ�����( �߂�l:�ϊ���̃f�[�^�T�C�Y )
static unsigned char BinToChar128Table[ 128 ] =
{
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,
	0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
	0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0xA1, 0xA2,
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
	0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2,
	0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2,
} ;
static unsigned char Char128ToBinTable[ 256 ] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e,
	0x5f, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
	0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e,
	0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e,
	0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e,
	0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x4e, 0x4f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c,
	0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c,
	0x7d, 0x7e, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
} ;
extern DWORD BinToChar128( void *Src, DWORD SrcSize, void *Dest )
{
	unsigned int DestSize ;

	DestSize  = SrcSize + ( SrcSize + 6 ) / 7 + 5 ;

	if( Dest != NULL )
	{
		unsigned int PackNum ;
		unsigned int ModNum ;
		unsigned char *DestP ;
		unsigned char *SrcP ;
		unsigned int i ;

		DestP = ( unsigned char * )Dest ;
		SrcP  = ( unsigned char * )&SrcSize ;

		DestP[ 0 ] = BinToChar128Table[                                 ( SrcP[ 0 ] >> 1 ) ] ;
		DestP[ 1 ] = BinToChar128Table[ ( ( SrcP[ 0 ] & 0x01 ) << 6 ) | ( SrcP[ 1 ] >> 2 ) ] ;
		DestP[ 2 ] = BinToChar128Table[ ( ( SrcP[ 1 ] & 0x03 ) << 5 ) | ( SrcP[ 2 ] >> 3 ) ] ;
		DestP[ 3 ] = BinToChar128Table[ ( ( SrcP[ 2 ] & 0x07 ) << 4 ) | ( SrcP[ 3 ] >> 4 ) ] ;
		DestP[ 4 ] = BinToChar128Table[ ( ( SrcP[ 3 ] & 0x0f ) << 3 )                      ] ;

		DestP += 5 ;

		PackNum = SrcSize / 7 ;
		ModNum  = SrcSize - PackNum * 7 ;
		SrcP  = ( unsigned char * )Src ;
		for( i = 0 ; i < PackNum ; i ++ )
		{
			DestP[ 0 ] = BinToChar128Table[                                 ( SrcP[ 0 ] >> 1 ) ] ;
			DestP[ 1 ] = BinToChar128Table[ ( ( SrcP[ 0 ] & 0x01 ) << 6 ) | ( SrcP[ 1 ] >> 2 ) ] ;
			DestP[ 2 ] = BinToChar128Table[ ( ( SrcP[ 1 ] & 0x03 ) << 5 ) | ( SrcP[ 2 ] >> 3 ) ] ;
			DestP[ 3 ] = BinToChar128Table[ ( ( SrcP[ 2 ] & 0x07 ) << 4 ) | ( SrcP[ 3 ] >> 4 ) ] ;
			DestP[ 4 ] = BinToChar128Table[ ( ( SrcP[ 3 ] & 0x0f ) << 3 ) | ( SrcP[ 4 ] >> 5 ) ] ;
			DestP[ 5 ] = BinToChar128Table[ ( ( SrcP[ 4 ] & 0x1f ) << 2 ) | ( SrcP[ 5 ] >> 6 ) ] ;
			DestP[ 6 ] = BinToChar128Table[ ( ( SrcP[ 5 ] & 0x3f ) << 1 ) | ( SrcP[ 6 ] >> 7 ) ] ;
			DestP[ 7 ] = BinToChar128Table[ ( ( SrcP[ 6 ] & 0x7f )      )                      ] ;

			DestP += 8 ;
			SrcP  += 7 ;
		}

		if( ModNum != 0 )
		{
			DestP[ 0 ] = BinToChar128Table[                                 ( SrcP[ 0 ] >> 1 ) ] ;
			if( ModNum == 1 )
			{
				DestP[ 1 ] = BinToChar128Table[ ( ( SrcP[ 0 ] & 0x01 ) << 6 ) ] ;
			}
			else
			{
				DestP[ 1 ] = BinToChar128Table[ ( ( SrcP[ 0 ] & 0x01 ) << 6 ) | ( SrcP[ 1 ] >> 2 ) ] ;
				if( ModNum == 2 )
				{
					DestP[ 2 ] = BinToChar128Table[ ( ( SrcP[ 1 ] & 0x03 ) << 5 ) ] ;
				}
				else
				{
					DestP[ 2 ] = BinToChar128Table[ ( ( SrcP[ 1 ] & 0x03 ) << 5 ) | ( SrcP[ 2 ] >> 3 ) ] ;
					if( ModNum == 3 )
					{
						DestP[ 3 ] = BinToChar128Table[ ( ( SrcP[ 2 ] & 0x07 ) << 4 ) ] ;
					}
					else
					{
						DestP[ 3 ] = BinToChar128Table[ ( ( SrcP[ 2 ] & 0x07 ) << 4 ) | ( SrcP[ 3 ] >> 4 ) ] ;
						if( ModNum == 4 )
						{
							DestP[ 4 ] = BinToChar128Table[ ( ( SrcP[ 3 ] & 0x0f ) << 3 ) ] ;
						}
						else
						{
							DestP[ 4 ] = BinToChar128Table[ ( ( SrcP[ 3 ] & 0x0f ) << 3 ) | ( SrcP[ 4 ] >> 5 ) ] ;
							if( ModNum == 5 )
							{
								DestP[ 5 ] = BinToChar128Table[ ( ( SrcP[ 4 ] & 0x1f ) << 2 ) ] ;
							}
							else
							{
								DestP[ 5 ] = BinToChar128Table[ ( ( SrcP[ 4 ] & 0x1f ) << 2 ) | ( SrcP[ 5 ] >> 6 ) ] ;
								if( ModNum == 6 )
								{
									DestP[ 6 ] = BinToChar128Table[ ( ( SrcP[ 5 ] & 0x3f ) << 1 ) ] ;
								}
								else
								{
									DestP[ 6 ] = BinToChar128Table[ ( ( SrcP[ 5 ] & 0x3f ) << 1 ) | ( SrcP[ 6 ] >> 7 ) ] ;
									DestP[ 7 ] = BinToChar128Table[ ( ( SrcP[ 6 ] & 0x7f )      )                      ] ;
								}
							}
						}
					}
				}
			}
		}
	}

	return DestSize ;
}

// ���p��������o�C�i���f�[�^�ɕϊ�����( �߂�l:�ϊ���̃f�[�^�T�C�Y )
extern DWORD Char128ToBin( void *Src, void *Dest )
{
	unsigned int DestSize ;
	unsigned char *SrcP ;
	unsigned char *DestP ;

	SrcP    = ( unsigned char * )Src ;
	DestP   = ( unsigned char * )&DestSize ;

	DestP[ 0 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 0 ] ] << 1 ) | ( Char128ToBinTable[ SrcP[ 1 ] ] >> 6 ) ) ;
	DestP[ 1 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 1 ] ] << 2 ) | ( Char128ToBinTable[ SrcP[ 2 ] ] >> 5 ) ) ;
	DestP[ 2 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 2 ] ] << 3 ) | ( Char128ToBinTable[ SrcP[ 3 ] ] >> 4 ) ) ;
	DestP[ 3 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 3 ] ] << 4 ) | ( Char128ToBinTable[ SrcP[ 4 ] ] >> 3 ) ) ;

	SrcP += 5 ;

	if( Dest != NULL )
	{
		unsigned int PackNum ;
		unsigned int ModNum ;
		unsigned int i ;

		PackNum = DestSize / 7 ;
		ModNum  = DestSize - PackNum * 7 ;
		DestP = ( unsigned char * )Dest ;
		for( i = 0 ; i < PackNum ; i ++ )
		{
			DestP[ 0 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 0 ] ] << 1 ) | ( Char128ToBinTable[ SrcP[ 1 ] ] >> 6 ) ) ;
			DestP[ 1 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 1 ] ] << 2 ) | ( Char128ToBinTable[ SrcP[ 2 ] ] >> 5 ) ) ;
			DestP[ 2 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 2 ] ] << 3 ) | ( Char128ToBinTable[ SrcP[ 3 ] ] >> 4 ) ) ;
			DestP[ 3 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 3 ] ] << 4 ) | ( Char128ToBinTable[ SrcP[ 4 ] ] >> 3 ) ) ;
			DestP[ 4 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 4 ] ] << 5 ) | ( Char128ToBinTable[ SrcP[ 5 ] ] >> 2 ) ) ;
			DestP[ 5 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 5 ] ] << 6 ) | ( Char128ToBinTable[ SrcP[ 6 ] ] >> 1 ) ) ;
			DestP[ 6 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 6 ] ] << 7 ) | ( Char128ToBinTable[ SrcP[ 7 ] ]      ) ) ;

			DestP += 7 ;
			SrcP  += 8 ;
		}

		if( ModNum != 0 )
		{
			DestP[ 0 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 0 ] ] << 1 ) | ( Char128ToBinTable[ SrcP[ 1 ] ] >> 6 ) ) ;
			if( ModNum > 1 )
			{
				DestP[ 1 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 1 ] ] << 2 ) | ( Char128ToBinTable[ SrcP[ 2 ] ] >> 5 ) ) ;
				if( ModNum > 2 )
				{
					DestP[ 2 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 2 ] ] << 3 ) | ( Char128ToBinTable[ SrcP[ 3 ] ] >> 4 ) ) ;
					if( ModNum > 3 )
					{
						DestP[ 3 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 3 ] ] << 4 ) | ( Char128ToBinTable[ SrcP[ 4 ] ] >> 3 ) ) ;
						if( ModNum > 4 )
						{
							DestP[ 4 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 4 ] ] << 5 ) | ( Char128ToBinTable[ SrcP[ 5 ] ] >> 2 ) ) ;
							if( ModNum > 5 )
							{
								DestP[ 5 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 5 ] ] << 6 ) | ( Char128ToBinTable[ SrcP[ 6 ] ] >> 1 ) ) ;
								if( ModNum > 6 )
								{
									DestP[ 6 ] = ( unsigned char )( ( Char128ToBinTable[ SrcP[ 6 ] ] << 7 ) | ( Char128ToBinTable[ SrcP[ 7 ] ]      ) ) ;
								}
							}
						}
					}
				}
			}
		}
	}

	return DestSize ;
}



// �o�C�i���f�[�^��Base64������ɕϊ�����( �߂�l:�ϊ���̃f�[�^�T�C�Y )
static unsigned char BinToBase64Table[ 64 ] =
{
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,	0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,	0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
	0x77, 0x78, 0x79, 0x7A, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x2B, 0x2F
} ;
static unsigned char Base64ToBinTable[ 256 ] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x3F,
	0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
	0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
} ;
extern DWORD BinToBase64( void *Src, unsigned int SrcSize, void *Dest )
{
	unsigned int DestSize ;
	unsigned int ModNum ;
	unsigned int PackNum ;

	PackNum = SrcSize / 3 ;
	ModNum  = SrcSize - PackNum * 3 ;
	DestSize  = PackNum * 4 + ( ModNum > 0 ? ModNum + 1 : 0 ) + 6 ;

	if( Dest != NULL )
	{
		unsigned char *DestP ;
		unsigned char *SrcP ;
		unsigned int i ;

		DestP = ( unsigned char * )Dest ;
		SrcP  = ( unsigned char * )&SrcSize ;

		DestP[ 0 ] = BinToBase64Table[                                 ( SrcP[ 0 ] >> 2 ) ] ;
		DestP[ 1 ] = BinToBase64Table[ ( ( SrcP[ 0 ] & 0x03 ) << 4 ) | ( SrcP[ 1 ] >> 4 ) ] ;
		DestP[ 2 ] = BinToBase64Table[ ( ( SrcP[ 1 ] & 0x0f ) << 2 ) | ( SrcP[ 2 ] >> 6 ) ] ;
		DestP[ 3 ] = BinToBase64Table[ ( ( SrcP[ 2 ] & 0x3f )      )                      ] ;
		DestP[ 4 ] = BinToBase64Table[                                 ( SrcP[ 3 ] >> 2 ) ] ;
		DestP[ 5 ] = BinToBase64Table[ ( ( SrcP[ 3 ] & 0x03 ) << 4 )                      ] ;

		DestP += 6 ;

		SrcP  = ( unsigned char * )Src ;
		for( i = 0 ; i < PackNum ; i ++ )
		{
			DestP[ 0 ] = BinToBase64Table[                                 ( SrcP[ 0 ] >> 2 ) ] ;
			DestP[ 1 ] = BinToBase64Table[ ( ( SrcP[ 0 ] & 0x03 ) << 4 ) | ( SrcP[ 1 ] >> 4 ) ] ;
			DestP[ 2 ] = BinToBase64Table[ ( ( SrcP[ 1 ] & 0x0f ) << 2 ) | ( SrcP[ 2 ] >> 6 ) ] ;
			DestP[ 3 ] = BinToBase64Table[ ( ( SrcP[ 2 ] & 0x3f )      )                      ] ;

			DestP += 4 ;
			SrcP  += 3 ;
		}

		if( ModNum != 0 )
		{
			DestP[ 0 ] = BinToBase64Table[ ( SrcP[ 0 ] >> 2 ) ] ;
			if( ModNum == 1 )
			{
				DestP[ 1 ] = BinToBase64Table[ ( ( SrcP[ 0 ] & 0x03 ) << 4 )                      ] ;
				DestP += 2 ;
			}
			else
			{
				DestP[ 1 ] = BinToBase64Table[ ( ( SrcP[ 0 ] & 0x03 ) << 4 ) | ( SrcP[ 1 ] >> 4 ) ] ;
				DestP[ 2 ] = BinToBase64Table[ ( ( SrcP[ 1 ] & 0x0f ) << 2 )                      ] ;
				DestP += 3 ;
			}
		}
	}

	return DestSize ;
}

// Base64��������o�C�i���f�[�^�ɕϊ�����( �߂�l:�ϊ���̃f�[�^�T�C�Y )
extern DWORD Base64ToBin( void *Src, void *Dest )
{
	unsigned int DestSize ;
	unsigned char *SrcP ;
	unsigned char *DestP ;

	SrcP    = ( unsigned char * )Src ;
	DestP   = ( unsigned char * )&DestSize ;

	DestP[ 0 ] = ( Base64ToBinTable[ SrcP[ 0 ] ] << 2 ) | ( Base64ToBinTable[ SrcP[ 1 ] ] >> 4 ) ;
	DestP[ 1 ] = ( Base64ToBinTable[ SrcP[ 1 ] ] << 4 ) | ( Base64ToBinTable[ SrcP[ 2 ] ] >> 2 ) ;
	DestP[ 2 ] = ( Base64ToBinTable[ SrcP[ 2 ] ] << 6 ) | ( Base64ToBinTable[ SrcP[ 3 ] ]      ) ;
	DestP[ 3 ] = ( Base64ToBinTable[ SrcP[ 4 ] ] << 2 ) | ( Base64ToBinTable[ SrcP[ 5 ] ] >> 4 ) ;

	SrcP += 6 ;

	if( Dest != NULL )
	{
		unsigned int PackNum ;
		unsigned int ModNum ;
		unsigned int i ;

		PackNum = DestSize / 3 ;
		ModNum  = DestSize - PackNum * 3 ;
		DestP = ( unsigned char * )Dest ;
		for( i = 0 ; i < PackNum ; i ++ )
		{
			DestP[ 0 ] = ( Base64ToBinTable[ SrcP[ 0 ] ] << 2 ) | ( Base64ToBinTable[ SrcP[ 1 ] ] >> 4 ) ;
			DestP[ 1 ] = ( Base64ToBinTable[ SrcP[ 1 ] ] << 4 ) | ( Base64ToBinTable[ SrcP[ 2 ] ] >> 2 ) ;
			DestP[ 2 ] = ( Base64ToBinTable[ SrcP[ 2 ] ] << 6 ) | ( Base64ToBinTable[ SrcP[ 3 ] ]      ) ;

			DestP += 3 ;
			SrcP  += 4 ;
		}

		if( ModNum != 0 )
		{
			DestP[ 0 ] = ( Base64ToBinTable[ SrcP[ 0 ] ] << 2 ) | ( Base64ToBinTable[ SrcP[ 1 ] ] >> 4 ) ;
			if( ModNum > 1 )
			{
				DestP[ 1 ] = ( Base64ToBinTable[ SrcP[ 1 ] ] << 4 ) | ( Base64ToBinTable[ SrcP[ 2 ] ] >> 2 ) ;
				if( ModNum > 2 )
				{
					DestP[ 2 ] = ( Base64ToBinTable[ SrcP[ 2 ] ] << 6 ) | ( Base64ToBinTable[ SrcP[ 3 ] ]      ) ;
				}
			}
		}
	}

	return DestSize ;
}





// �o�C�i���f�[�^������ CRC32 �̃n�b�V���l���v�Z����
extern DWORD HashCRC32( const void *SrcData, size_t SrcDataSize )
{
	static DWORD CRC32Table[ 256 ] ;
	static int CRC32TableInit = 0 ;
	DWORD CRC = 0xffffffff ;
	BYTE *SrcByte = ( BYTE * )SrcData ;
	DWORD i ;

	// �e�[�u��������������Ă��Ȃ������珉��������
	if( CRC32TableInit == 0 )
	{
		DWORD Magic = 0xedb88320 ;	// 0x4c11db7 ���r�b�g���x���ŏ��Ԃ��t�ɂ������̂� 0xedb88320
		DWORD j ;

		for( i = 0; i < 256; i++ )
		{
			DWORD Data = i ;
			for( j = 0; j < 8; j++ )
			{
				int b = ( Data & 1 ) ;
				Data >>= 1 ;
				if( b != 0 )
				{
					Data ^= Magic ;
				}
			}
			CRC32Table[ i ] = Data ;
		}

		// �e�[�u���������������t���O�𗧂Ă�
		CRC32TableInit = 1 ;
	}

	for( i = 0 ; i < SrcDataSize ; i ++ )
	{
		CRC = CRC32Table[ ( BYTE )( CRC ^ SrcByte[ i ] ) ] ^ ( CRC >> 8 ) ;
	}

	return CRC ^ 0xffffffff ;
}



#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

