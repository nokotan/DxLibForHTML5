// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�ʐM�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.22c
// 
// -------------------------------------------------------------------------------

#ifndef DXARCHIVE_H
#define DXARCHIVE_H

// �C���N���[�h -------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"
#include "DxThread.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �c�w�A�[�J�C�u�֘A

/*
	�o�[�W�������Ƃ̈Ⴂ

	0x0002 DARC_FILEHEAD �� PressDataSize ��ǉ�
	0x0004 DARC_HEAD �� CharCodeFormat ��ǉ�
	0x0005 �Í����������ꕔ�ύX
	0x0006 64bit��
	0x0007 �Í���������ύX( �p�X���[�h���w�肵���ꍇ�̉�Ǔ�x������ )
	0x0008 �Í����̒�����56bit�ɕύX


	�f�[�^�}�b�v
		
	DXARC_HEAD
	�t�@�C�����f�[�^
	�t�@�C�����e�[�u��
	DXARC_FILEHEAD �e�[�u��
	DXARC_DIRECTORY �e�[�u��


	�t�@�C�����̃f�[�^�`��
	2byte:������̒���(�o�C�g�T�C�Y���S)
	2byte:������̃p���e�B�f�[�^(�S�Ă̕����̒l�𑫂�������)
	�p���͑啶���ɕϊ����ꂽ�t�@�C�����̃f�[�^(�S�̔{���̃T�C�Y)
	�p�����啶���ɕϊ�����Ă��Ȃ��t�@�C�����̃f�[�^
*/

#define DXAHEAD							*((WORD *)"DX")		// �w�b�_
#define DXAVER							(0x0008)			// �o�[�W����
#define DXAVER_MIN						(0x0008)			// �Ή����Ă���Œ�o�[�W����
#define DXA_KEY_BYTES					(7)					// ���̃o�C�g��
#define DXA_KEY_STRING_LENGTH			(63)				// ���p������̒���
#define DXA_KEY_STRING_MAXLENGTH		(2048)				// ���p������o�b�t�@�̃T�C�Y
#define DXA_DIR_MAXARCHIVENUM			(4096)				// �����ɊJ���Ă�����A�[�J�C�u�t�@�C���̐�
#define DXA_DIR_MAXFILENUM				(32768)				// �����ɊJ���Ă�����t�@�C���̐�
#define DXA_MAXDRIVENUM					(64)				// �Ή�����h���C�u�̍ő吔
	
// �t���O
#define DXA_FLAG_NO_KEY					(0x00000001)	// ����������
#define DXA_FLAG_NO_HEAD_PRESS			(0x00000002)	// �w�b�_�̈��k����

// �\���̒�` --------------------------------------------------------------------

// �A�[�J�C�u�f�[�^�̍ŏ��̃w�b�_
struct DXARC_HEAD
{
	WORD						Head ;							// �h�c
	WORD						Version ;						// �o�[�W����
	DWORD						HeadSize ;						// �w�b�_���� DXARC_HEAD �𔲂����S�T�C�Y
	ULONGLONG					DataStartAddress ;				// �ŏ��̃t�@�C���̃f�[�^���i�[����Ă���f�[�^�A�h���X(�t�@�C���̐擪�A�h���X���A�h���X�O�Ƃ���)
	ULONGLONG					FileNameTableStartAddress ;		// �t�@�C�����e�[�u���̐擪�A�h���X(�t�@�C���̐擪�A�h���X���A�h���X�O�Ƃ���)
	ULONGLONG					FileTableStartAddress ;			// �t�@�C���e�[�u���̐擪�A�h���X(�����o�ϐ� FileNameTableStartAddress �̃A�h���X���O�Ƃ���)
	ULONGLONG					DirectoryTableStartAddress ;	// �f�B���N�g���e�[�u���̐擪�A�h���X(�����o�ϐ� FileNameTableStartAddress �̃A�h���X���O�Ƃ���)
																// �A�h���X�O����z�u����Ă��� DXARC_DIRECTORY �\���̂����[�g�f�B���N�g��
	DWORD						CharCodeFormat ;				// �t�@�C�����Ɏg�p���Ă���R�[�h�y�[�W�ԍ�
	DWORD						Flags ;							// �t���O( DXA_FLAG_NO_KEY �� )
	BYTE						HuffmanEncodeKB ;				// �t�@�C���̑O��̃n�t�}�����k����T�C�Y( �P�ʁF�L���o�C�g 0xff �̏ꍇ�͂��ׂĈ��k���� )
	BYTE						Reserve[ 15 ] ;					// �\��̈�
} ;

// �t�@�C���̎��ԏ��
struct DXARC_FILETIME
{
	ULONGLONG					Create ;						// �쐬����
	ULONGLONG					LastAccess ;					// �ŏI�A�N�Z�X����
	ULONGLONG					LastWrite ;						// �ŏI�X�V����
} ;

// �t�@�C�����f�[�^�\����
struct DXARC_FILENAME
{
	WORD						Length ;						// ������̒������S
	WORD						Parity ;						// �p���e�B���
} ;

// �t�@�C���i�[���
struct DXARC_FILEHEAD
{
	ULONGLONG					NameAddress ;					// �t�@�C�������i�[����Ă���A�h���X( ARCHIVE_HEAD�\���� �̃����o�ϐ� FileNameTableStartAddress �̃A�h���X���A�h���X�O�Ƃ���) 
	ULONGLONG					Attributes ;					// �t�@�C������
	DXARC_FILETIME				Time ;							// ���ԏ��
	ULONGLONG					DataAddress ;					// �t�@�C�����i�[����Ă���A�h���X
																//			�t�@�C���̏ꍇ�FDXARC_HEAD�\���� �̃����o�ϐ� DataStartAddress �������A�h���X���A�h���X�O�Ƃ���
																//			�f�B���N�g���̏ꍇ�FDXARC_HEAD�\���� �̃����o�ϐ� DirectoryTableStartAddress �̂������A�h���X���A�h���X�O�Ƃ���
	ULONGLONG					DataSize ;						// �t�@�C���̃f�[�^�T�C�Y
	ULONGLONG					PressDataSize ;					// ���k��̃f�[�^�̃T�C�Y( 0xffffffff:���k����Ă��Ȃ� ) ( Ver0x0002 �Œǉ����ꂽ )
	ULONGLONG					HuffPressDataSize ;				// �n�t�}�����k��̃f�[�^�̃T�C�Y( 0xffffffffffffffff:���k����Ă��Ȃ� ) ( Ver0x0008 �Œǉ����ꂽ )
} ;

// �f�B���N�g���i�[���
struct DXARC_DIRECTORY
{
	ULONGLONG					DirectoryAddress ;				// ������ DXARC_FILEHEAD ���i�[����Ă���A�h���X( DXARC_HEAD �\���� �̃����o�ϐ� FileTableStartAddress �������A�h���X���A�h���X�O�Ƃ���)
	ULONGLONG					ParentDirectoryAddress ;		// �e�f�B���N�g���� DXARC_DIRECTORY ���i�[����Ă���A�h���X( DXARC_HEAD�\���� �̃����o�ϐ� DirectoryTableStartAddress �������A�h���X���A�h���X�O�Ƃ���)
	ULONGLONG					FileHeadNum ;					// �f�B���N�g�����̃t�@�C���̐�
	ULONGLONG					FileHeadAddress ;				// �f�B���N�g�����̃t�@�C���̃w�b�_�񂪊i�[����Ă���A�h���X( DXARC_HEAD�\���� �̃����o�ϐ� FileTableStartAddress �������A�h���X���A�h���X�O�Ƃ���) 
} ;



// �t�@�C���������p�f�[�^�\����
struct DXARC_SEARCHDATA
{
	BYTE						FileName[ 1024 ] ;				// �t�@�C����
	WORD						Parity ;						// �p���e�B���
	WORD						PackNum ;						// ������̒������S
} ;

// ���e�[�u���\����
struct DXARC_TABLE
{
	BYTE						*Top ;							// ���e�[�u���̐擪�|�C���^
	BYTE						*FileTable ;					// �t�@�C�����e�[�u���ւ̃|�C���^
	BYTE						*DirectoryTable ;				// �f�B���N�g�����e�[�u���ւ̃|�C���^
	BYTE						*NameTable ;					// ���O���e�[�u���ւ̃|�C���^
} ;

// �A�[�J�C�u�����p���\����
struct DXARC
{
	DXARC_HEAD					Head ;							// �A�[�J�C�u�̃w�b�_
	int							CharCodeFormat ;				// �����R�[�h�`��
	DWORD_PTR					ReadAccessOnlyFilePointer ;		// �A�[�J�C�u�t�@�C���̃|�C���^	
	void						*MemoryImage ;					// �������C���[�W���J�����ꍇ�̃A�h���X
	DXARC_TABLE					Table ;							// �e�e�[�u���ւ̐擪�A�h���X���i�[���ꂽ�\����
	DXARC_DIRECTORY				*CurrentDirectory ;				// �J�����g�f�B���N�g���f�[�^�ւ̃|�C���^

	wchar_t						FilePath[ 1024 ] ;				// �t�@�C���p�X
	bool						NoKey ;							// ���������s��Ȃ����ǂ���
	unsigned char				Key[ DXA_KEY_BYTES ] ;			// ��
	char						KeyString[ DXA_KEY_STRING_LENGTH + 1 ] ;	// ��������
	size_t						KeyStringBytes ;				// ��������̃o�C�g��
	int							MemoryOpenFlag ;				// ��������̃t�@�C�����J���Ă��邩�A�t���O
	int							UserMemoryImageFlag ;			// ���[�U�[���W�J�����������C���[�W���g�p���Ă��邩�A�t���O
	LONGLONG					MemoryImageSize ;				// ��������̃t�@�C������J���Ă����ꍇ�̃C���[�W�̃T�C�Y
	int							MemoryImageCopyFlag ;			// ��������̃C���[�W���R�s�[���Ďg�p���Ă��邩�ǂ����̃t���O
	int							MemoryImageReadOnlyFlag ;		// ��������̃C���[�W���ǂݎ���p���ǂ����̃t���O
	void						*MemoryImageOriginal ;			// ��������̃C���[�W���R�s�[���Ďg�p���Ă���ꍇ�́A�R�s�[���̃f�[�^���i�[����Ă��郁�����̈�

	int							ASyncOpenFlag ;					// �񓯊��ǂݍ��ݒ����t���O( TRUE:�񓯊��ǂݍ��ݒ� FALSE:�Ⴄ )
	DWORD_PTR					ASyncOpenFilePointer ;			// �񓯊��I�[�v�������Ɏg�p����t�@�C���̃|�C���^
} ;

// �񓯊��ǂݍ��ݏ��
#define DXARC_STREAM_ASYNCSTATE_IDLE			(0)				// �������Ă��Ȃ�
#define DXARC_STREAM_ASYNCSTATE_PRESSREAD		(1)				// ���k���ꂽ�t�@�C����ǂݍ��ݒ�
#define DXARC_STREAM_ASYNCSTATE_READ			(2)				// �f�[�^��ǂݍ��ݒ�

// �A�[�J�C�u���̃t�@�C����ʏ�̃t�@�C���ǂݍ��݂̂悤�ɏ�������ׂ̍\����
struct DXARC_STREAM
{
	DXARC						*Archive ;						// �A�[�J�C�u�f�[�^�ւ̃|�C���^
	DXARC_FILEHEAD				*FileHead ;						// �t�@�C�����ւ̃|�C���^
	void						*DecodeDataBuffer ;				// �𓀂����f�[�^���i�[����Ă��郁�����̈�ւ̃|�C���^( �t�@�C�������k�f�[�^�������ꍇ�̂ݗL�� )
	void						*DecodeTempBuffer ;				// ���k�f�[�^�ꎞ�ۑ��p�������̈�ւ̃|�C���^
	DWORD_PTR					ReadOnlyFilePointer ;			// �A�[�J�C�u�t�@�C���̃|�C���^

	bool						NoKey ;							// ���������s��Ȃ����ǂ���
	unsigned char				Key[ DXA_KEY_BYTES ] ;			// ��

	int							EOFFlag ;						// EOF�t���O
	ULONGLONG					FilePoint ;						// �t�@�C���|�C���^
	int							UseASyncReadFlag ;				// �񓯊��ǂݍ��݃t���O
	int							ASyncState ;					// �񓯊��ǂݍ��ݏ��( DXARC_STREA_ASYNCSTATE �n )
	ULONGLONG					ASyncReadFileAddress ;			// �񓯊��ǂݍ��ݎ��̃t�@�C���|�C���^

	void						*ReadBuffer ;					// �񓯊��ǂݍ��ݎ��̈����ɓn���ꂽ�o�b�t�@�ւ̃|�C���^
	LONGLONG					ReadSize ;						// �񓯊��ǂݍ��ݎ��̈����ɓn���ꂽ�ǂݍ��݃T�C�Y�ւ̃|�C���^
} ;



// �A�[�J�C�u�t�@�C�����f�B���N�g���Ɍ����Ă鏈���p�̊J���Ă���A�[�J�C�u�t�@�C���̏��
struct DXARC_DIR_ARCHIVE
{
	int							UseCounter ;					// ���̃A�[�J�C�u�t�@�C�����g�p����Ă��鐔
	DXARC						Archive ;						// �A�[�J�C�u�t�@�C���f�[�^
	wchar_t						Path[ 520 ] ;					// �A�[�J�C�u�t�@�C���̃p�X
} ;

// �A�[�J�C�u�t�@�C�����f�B���N�g���Ɍ����Ă鏈���p�̊J���Ă���A�[�J�C�u�t�@�C�����̃t�@�C���̏��
struct DXARC_DIR_FILE
{
	int							UseArchiveFlag ;				// �A�[�J�C�u�t�@�C�����g�p���Ă��邩�t���O
	DWORD_PTR					ReadOnlyFilePointer ;			// �A�[�J�C�u���g�p���Ă��Ȃ��ꍇ�́A�t�@�C���|�C���^
	DWORD						UseArchiveIndex ;				// �A�[�J�C�u���g�p���Ă���ꍇ�A�g�p���Ă���A�[�J�C�u�t�@�C���f�[�^�̃C���f�b�N�X
	DXARC_STREAM				DXAStream ;						// �A�[�J�C�u�t�@�C�����g�p���Ă���ꍇ�̃t�@�C���A�N�Z�X�p�f�[�^
} ;

// �A�[�J�C�u���f�B���N�g���Ɍ����Ă鏈���p�̍\����
struct DXARC_DIR
{
	int							InitializeFlag ;				// �����������t���O
	DX_CRITICAL_SECTION			CriticalSection ;				// �����ɃA�[�J�C�u�t�@�C���̃��X�g�𑀍삵�Ȃ��悤�ɂ��邽�߂̃N���e�B�J���Z�N�V����

	int							NotArchivePathCharUp ;			// �A�[�J�C�u�p�X�̉p���̏�������啶���ɂ��Ȃ����ǂ���

	DXARC_DIR_ARCHIVE			*Archive[DXA_DIR_MAXARCHIVENUM] ;	// �g�p���Ă���A�[�J�C�u�t�@�C���̃f�[�^
	DXARC_DIR_FILE				*File[DXA_DIR_MAXFILENUM] ;		// �J���Ă���t�@�C���̃f�[�^
	wchar_t						ArchiveExtension[ 64 ] ;		// �A�[�J�C�u�t�@�C���̊g���q
	int							ArchiveExtensionLength ;		// �A�[�J�C�u�t�@�C���̊g���q�̒���
	int							DXAPriority ;					// �c�w�A�[�J�C�u�t�@�C���̗D��x( 1:�t�H���_�D�� 0:DX�A�[�J�C�u�D�� )

	int							ValidKeyString ;						// KeyString ���L�����ǂ���
	char						KeyString[ DXA_KEY_STRING_LENGTH + 1 ] ;	// ��������

	int							ArchiveNum ;					// �g�p���Ă���A�[�J�C�u�t�@�C���̐�
	int							FileNum ;						// �J���Ă���t�@�C���̐�

	int							BackUseArchiveIndex ;			// �O��g�p�����A�[�J�C�u�̃C���f�b�N�X
	wchar_t						BackUseDirectory[ 512 * 3 ] ;	// �O��g�p�����f�B���N�g���p�X
	int							BackUseDirectoryPathLength ;	// �O��g�p�����f�B���N�g���p�X�̒���
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 -------------------------------------------------------------

extern DXARC_DIR DX_ArchiveDirData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

#ifndef DX_NON_DXA

extern	int			DXA_Initialize(					DXARC *DXA ) ;													// �A�[�J�C�u�t�@�C���������ׂ̍\���̂�����������
extern	int			DXA_Terminate(					DXARC *DXA ) ;													// �A�[�J�C�u�t�@�C���������ׂ̍\���̂̌�n��������
extern	int			DXA_OpenArchiveFromFile(		DXARC *DXA, const wchar_t *ArchivePath, const char *KeyString = NULL ) ;							// �A�[�J�C�u�t�@�C�����J��( 0:����  -1:���s )
extern	int			DXA_OpenArchiveFromFileUseMem(	DXARC *DXA, const wchar_t *ArchivePath, const char *KeyString = NULL , int ASync = FALSE ) ;		// �A�[�J�C�u�t�@�C�����J���ŏ��ɂ��ׂă�������ɓǂݍ���ł��珈������( 0:����  -1:���s )
extern	int			DXA_OpenArchiveFromMem(			DXARC *DXA, void *ArchiveImage, int ArchiveSize, int ArchiveImageCopyFlag, int ArchiveImageReadOnlyFlag, const char *KeyString = NULL, const wchar_t *EmulateArchivePath = NULL ) ;				// ��������ɂ���A�[�J�C�u�t�@�C���C���[�W���J��( 0:����  -1:���s )
extern	int			DXA_CheckIdle(					DXARC *DXA ) ;													// �A�[�J�C�u�t�@�C�����������������������𓾂�( TRUE:�����Ă���  FALSE:�����Ă��Ȃ� )
extern	int			DXA_CloseArchive(				DXARC *DXA ) ;													// �A�[�J�C�u�t�@�C�������

//extern int		DXA_LoadFile(					DXARC *DXA, const char *FilePath, void *Buffer, ULONGLONG BufferSize ) ;	// �A�[�J�C�u�t�@�C�����̎w��̃t�@�C�����������ɓǂݍ���( -1:�G���[ 0�ȏ�:�t�@�C���T�C�Y )
extern	void *		DXA_GetFileImage(				DXARC *DXA ) ;													// �A�[�J�C�u�t�@�C�����������ɓǂݍ��񂾏ꍇ�̃t�@�C���C���[�W���i�[����Ă���擪�A�h���X���擾����( DXA_OpenArchiveFromFileUseMem �Ⴕ���� DXA_OpenArchiveFromMem �ŊJ�����ꍇ�ɗL���A�f�[�^�����k����Ă���ꍇ�͒��� )
extern	int			DXA_GetFileInfo(				DXARC *DXA, int CharCodeFormat, const char *FilePath, int *Position, int *Size ) ;	// �A�[�J�C�u�t�@�C�����̎w��̃t�@�C���̃t�@�C�����̈ʒu�ƃt�@�C���̑傫���𓾂�( -1:�G���[ )
extern	int			DXA_ChangeCurrentDir(			DXARC *DXA, int CharCodeFormat, const char *DirPath ) ;								// �A�[�J�C�u���̃J�����g�f�B���N�g����ύX����( 0:����  -1:���s )
//extern int		DXA_GetCurrentDir(				DXARC *DXA, int CharCodeFormat, char *DirPathBuffer, int BufferSize ) ;				// �A�[�J�C�u���̃J�����g�f�B���N�g�����擾����
extern	DWORD_PTR	DXA_FindFirst(					DXARC *DXA, const BYTE *FilePath, FILEINFOW *Buffer ) ;			// �A�[�J�C�u���̃I�u�W�F�N�g����������( -1:�G���[ -1�ȊO:DXA�����n���h�� )
extern	int			DXA_FindNext(					DWORD_PTR DxaFindHandle, FILEINFOW *Buffer ) ;					// �A�[�J�C�u���̃I�u�W�F�N�g����������( -1:�G���[ 0:���� )
extern	int			DXA_FindClose(					DWORD_PTR DxaFindHandle ) ;										// �A�[�J�C�u���̃I�u�W�F�N�g�������I������

extern	int			DXA_STREAM_Initialize(			DXARC_STREAM *DXAStream, DXARC *DXA, const BYTE *FilePath, int UseASyncReadFlag ) ;	// �A�[�J�C�u�t�@�C�����̃t�@�C�����J��
extern	int			DXA_STREAM_Terminate(			DXARC_STREAM *DXAStream ) ;										// �A�[�J�C�u�t�@�C�����̃t�@�C�������
extern	int			DXA_STREAM_Read(				DXARC_STREAM *DXAStream, void *Buffer, size_t ReadLength ) ;	// �t�@�C���̓��e��ǂݍ���
extern	int			DXA_STREAM_Seek(				DXARC_STREAM *DXAStream, LONGLONG SeekPoint, int SeekMode ) ;	// �t�@�C���|�C���^��ύX����
extern	LONGLONG	DXA_STREAM_Tell(				DXARC_STREAM *DXAStream ) ;										// ���݂̃t�@�C���|�C���^�𓾂�
extern	int			DXA_STREAM_Eof(					DXARC_STREAM *DXAStream ) ;										// �t�@�C���̏I�[�ɗ��Ă��邩�A�̃t���O�𓾂�
extern	int			DXA_STREAM_IdleCheck(			DXARC_STREAM *DXAStream ) ;										// �ǂݍ��ݏ������������Ă��邩�ǂ����𒲂ׂ�
extern	LONGLONG	DXA_STREAM_Size(				DXARC_STREAM *DXAStream ) ;										// �t�@�C���̃T�C�Y���擾����


extern	int			DXA_DIR_Initialize(				void ) ;														// �A�[�J�C�u���f�B���N�g���Ɍ����Ă鏈���̏�����
extern	int			DXA_DIR_Terminate(				void ) ;														// �A�[�J�C�u���f�B���N�g���Ɍ����Ă鏈���̌�n��
extern	int			DXA_DIR_SetNotArchivePathCharUp( int NotArchivePathCharUpFlag ) ;								// �A�[�J�C�u�t�@�C���̃p�X��啶���ɂ��Ȃ����ǂ����̃t���O���Z�b�g����
extern	int			DXA_DIR_SetArchiveExtension(	const wchar_t *Extension = NULL ) ;								// �A�[�J�C�u�t�@�C���̊g���q��ݒ肷��
extern	int			DXA_DIR_SetDXArchivePriority(	int Priority = 0 ) ;											// �A�[�J�C�u�t�@�C���ƒʏ�̃t�H���_�̂ǂ�������݂����ꍇ�A�ǂ����D�悳���邩��ݒ肷��( 1:�t�H���_��D�� 0:�c�w�A�[�J�C�u�t�@�C����D��(�f�t�H���g) )
extern	int			DXA_DIR_SetKeyString(			const char *KeyString = NULL ) ;								// �A�[�J�C�u�t�@�C���̌��������ݒ肷��
extern	LONGLONG	DXA_DIR_LoadFile(				const wchar_t *FilePath, void *Buffer, int BufferSize ) ;			// �t�@�C�����ۂ��Ɠǂݍ��ފ֐�

extern	DWORD_PTR	DXA_DIR_Open(					const wchar_t *FilePath, int UseCacheFlag = FALSE, int BlockReadFlag = TRUE, int UseASyncReadFlag = FALSE ) ;	// �t�@�C�����J��( �G���[�F-1  �����F�n���h�� )
extern	int			DXA_DIR_Close(					DWORD_PTR Handle ) ;											// �t�@�C�������
extern	LONGLONG	DXA_DIR_Tell(					DWORD_PTR Handle ) ;											// �t�@�C���|�C���^�̈ʒu���擾����
extern	int			DXA_DIR_Seek(					DWORD_PTR Handle, LONGLONG SeekPoint, int SeekType ) ;			// �t�@�C���|�C���^�̈ʒu��ύX����
extern	size_t		DXA_DIR_Read(					void *Buffer, size_t BlockSize, size_t BlockNum, DWORD_PTR Handle ) ; // �t�@�C������f�[�^��ǂݍ���
extern	int			DXA_DIR_Eof(					DWORD_PTR Handle ) ;											// �t�@�C���̏I�[�𒲂ׂ�
extern	int			DXA_DIR_IsDXA(					DWORD_PTR Handle ) ;											// �߂�l: -1=�G���[  0=�c�w�A�[�J�C�u�t�@�C�����̃t�@�C���ł͂Ȃ�  1=�c�w�A�[�J�C�u�t�@�C�����̃t�@�C��
extern	int			DXA_DIR_ChDir(					const wchar_t *Path ) ;
extern	int			DXA_DIR_GetDir(					wchar_t *Buffer ) ;
extern	int			DXA_DIR_GetDirS(				wchar_t *Buffer, size_t BufferBytes ) ;
extern	int			DXA_DIR_IdleCheck(				DWORD_PTR Handle ) ;
extern	DWORD_PTR	DXA_DIR_FindFirst(				const wchar_t *FilePath, FILEINFOW *Buffer ) ;					// �߂�l: -1=�G���[  -1�ȊO=FindHandle
extern	int			DXA_DIR_FindNext(				DWORD_PTR FindHandle, FILEINFOW *Buffer ) ;						// �߂�l: -1=�G���[  0=����
extern	int			DXA_DIR_FindClose(				DWORD_PTR FindHandle ) ;										// �߂�l: -1=�G���[  0=����

#endif

extern	int			DXA_Encode(						void *Src, DWORD SrcSize, void *Dest ) ;						// �f�[�^�����k����( �߂�l:���k��̃f�[�^�T�C�Y )
extern	int			DXA_Decode(						void *Src, void *Dest ) ;										// �f�[�^���𓀂���( �߂�l:�𓀌�̃f�[�^�T�C�Y )

extern	ULONGLONG	Huffman_Encode(					void *Src, ULONGLONG SrcSize, void *Dest ) ;					// �f�[�^���n�t�}�����k����( �߂�l:���k��̃T�C�Y  0 �̓G���[  Dest �� NULL ������ƈ��k�f�[�^�i�[�ɕK�v�ȃT�C�Y���Ԃ� )
extern	ULONGLONG	Huffman_Decode(					void *Press, void *Dest ) ;										// �n�t�}�����k���ꂽ�f�[�^���𓀂���( �߂�l:�𓀌�̃T�C�Y  0 �̓G���[  Dest �� NULL ������Ɖ𓀃f�[�^�i�[�ɕK�v�ȃT�C�Y���Ԃ� )

extern	DWORD		BinToChar128(					void *Src, DWORD SrcSize, void *Dest ) ;						// �o�C�i���f�[�^�𔼊p������ɕϊ�����( �߂�l:�ϊ���̃f�[�^�T�C�Y )
extern	DWORD		Char128ToBin(					void *Src, void *Dest ) ;										// ���p��������o�C�i���f�[�^�ɕϊ�����( �߂�l:�ϊ���̃f�[�^�T�C�Y )

extern	DWORD		BinToBase64(					void *Src, unsigned int SrcSize, void *Dest ) ;					// �o�C�i���f�[�^��Base64������ɕϊ�����( �߂�l:�ϊ���̃f�[�^�T�C�Y )
extern	DWORD		Base64ToBin(					void *Src, void *Dest ) ;										// Base64��������o�C�i���f�[�^�ɕϊ�����( �߂�l:�ϊ���̃f�[�^�T�C�Y )

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DXARCHIVE_H
