// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		iOS�p�V�X�e���v���O����
// 
// 				Ver 3.21d
// 
// -------------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

// �C���N���[�h ------------------------------------------------------------------
#include "DxSystemHTML5.h"
#include "DxGraphicsHTML5.h"
#include "DxGraphicsFilterHTML5.h"
#include "DxLogHTML5.h"
#include "DxMaskHTML5.h"
#include "DxModelHTML5.h"
#include "DxSoundHTML5.h"
#include "../DxLib.h"
#include "../DxArchive_.h"
#include "../DxSystem.h"
#include "../DxGraphics.h"
#include "../DxModel.h"
#include "../DxMask.h"
#include "../DxFile.h"
#include "../DxNetwork.h"
#include "../DxInputString.h"
#include "../DxInput.h"
#include "../DxSound.h"
#include "../DxSoundConvert.h"
#include "../DxBaseImage.h"
#include "../DxSoftImage.h"
#include "../DxMovie.h"
#include "../DxFont.h"
#include "../DxLog.h"
#include "../DxASyncLoad.h"
#include "../DxLive2DCubism4.h"
#include "../DxUseCLib.h"
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../DxBaseFunc.h"
#include "../DxMemory.h"

#include <emscripten.h>

EM_JS(int, canvas_width, (), {
	return Module.canvas.width;
});

EM_JS(int, canvas_height, (), {
	return Module.canvas.height;
});

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

#define TIME_DISTANCE( now, time )			( (now) < (time) ? 0x7fffffff - (time) + (now) : (now) - (time) )

// �\���̒�` --------------------------------------------------------------------

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

DXLIB_IOS_SYSTEMINFO g_iOSSys ;
int g_iOSRunFlag ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------
   
// �v���O���� --------------------------------------------------------------------

// UTF16LE �̏���������� UTF8 �̃p�����[�^����������O�o�͂���
static void OutputiOSOSInfo_LogAddUTF8( const char *UTF16LEFormatStr, const char *UTF8Str )
{
//	char TempStr[ 1024 ] ;
//
//	ConvString( UTF8Str, -1, DX_CHARCODEFORMAT_UTF8, TempStr, sizeof( TempStr ), DX_CHARCODEFORMAT_UTF16LE ) ;
//	DXST_LOGFILEFMT_ADDUTF16LE(( UTF16LEFormatStr, TempStr )) ;
}

// ���C�u�����������֐�
extern int NS_DxLib_Init( void )
{
	// ���ɏ������ς݂̏ꍇ�͉��������I��
	if( DxSysData.DxLib_InitializeFlag == TRUE )
	{
		return 0 ;
	}

	DXST_LOGFILE_ADDA( "Start initialization processing of DX library\n" /*"�c�w���C�u�����̏����������J�n"*/ ) ;
	DXST_LOGFILE_TABADD ;

	// ���������t���O�𗧂Ă�
	DxSysData.DxLib_RunInitializeFlag = TRUE ;

#ifndef DX_NON_LITERAL_STRING
	// �c�w���C�u�����̃o�[�W�������o�͂���
	DXST_LOGFILEFMT_ADDA(( "DX library Ver%s\n", DXLIB_VERSION_STR_T /*"�c�w���C�u���� Ver%s\n"*/ )) ;
#endif

	// OS���o��
	{
	}

	// DxSysData �̋��ʏ���������
	DxLib_SysInit() ;

	// DxBaseFunc �̏�����
	_INIT_BASEFUNC() ;

	// �L�����N�^�[�R�[�h�֌W�̏��������s��
	InitCharCode() ;

	// �g�p���镶���Z�b�g���Z�b�g
	_SET_DEFAULT_CHARCODEFORMAT() ;

#ifndef DX_NON_ASYNCLOAD
	// �񓯊��ǂݍ��ݏ����̏�����
	InitializeASyncLoad( Thread_GetCurrentId() ) ;
#endif // DX_NON_ASYNCLOAD

	// �t�@�C���A�N�Z�X�����̏�����
	InitializeFile() ;
	
#ifndef DX_NON_OGGTHEORA
	// Theora �p�̏�����
	TheoraDecode_GrobalInitialize() ;
#endif

	// �A�[�J�C�u�t�@�C���A�N�Z�X�p�̃f�[�^��������
#ifndef DX_NON_DXA
	DXA_DIR_Initialize() ;
#endif

	// �X�g���[���f�[�^�ǂݍ��ݐ���p�|�C���^�\���̂̃f�t�H���g�l���Z�b�g
	NS_ChangeStreamFunction( NULL ) ;
	
#ifndef DX_NON_LOG
	// ���O�t�@�C���̏�����
	LogFileInitialize() ;
#endif

	// �V�X�e�����O���o��
//	OutSystemInfo() ;

#ifndef DX_NON_GRAPHICS
	// �f�t�H���g�̃O���t�B�b�N�����֐���o�^
	NS_SetRestoreGraphCallback( NULL ) ;
#endif // DX_NON_GRAPHICS
	
	// �e�����n�̏�����
	if( DxSysData.NotInputFlag == FALSE )
	{
#ifndef DX_NON_INPUT
		if( InitializeInputSystem() == -1 ) goto ERROR_DX ;			// ���̓V�X�e���̏�����
#endif // DX_NON_INPUT
	}

	if( DxSysData.NotSoundFlag == FALSE )
	{
#ifndef DX_NON_SOUND
		InitializeSoundConvert() ;									// �T�E���h�ϊ������̏�����
		InitializeSoundSystem() ;									// �T�E���h�V�X�e���̂̏�����
#endif // DX_NON_SOUND
	}
	if( DxSysData.NotDrawFlag == FALSE )
	{
		InitializeBaseImageManage() ;
#ifndef DX_NON_SOFTIMAGE
		InitializeSoftImageManage() ;
#endif // DX_NON_SOFTIMAGE
#ifndef DX_NON_MOVIE
		InitializeMovieManage() ;
#endif
	
#ifndef DX_NON_GRAPHICS
		if( Graphics_Initialize() < 0 ) goto ERROR_DX ;
#endif // DX_NON_GRAPHICS
	}
#ifndef DX_NON_INPUTSTRING
	InitializeInputCharBuf() ;									// �����R�[�h�o�b�t�@�̏�����
#endif // DX_NON_INPUTSTRING

	// �c�w���C�u���������������t���O�����Ă�
	DxSysData.DxLib_InitializeFlag = TRUE ;
	
	// �u�r�x�m�b�҂�������
//	NS_SetWaitVSyncFlag( TRUE ) ;

#if !defined( DX_NON_LOG ) && !defined( DX_NON_PRINTF_DX )
	// ���O�o�͏����̏��������s��
	InitializeLog() ;
#endif
	
#ifndef DX_NON_GRAPHICS
	// �`���̕ύX
	NS_SetDrawScreen( DX_SCREEN_BACK ) ;
	NS_SetDrawScreen( DX_SCREEN_FRONT ) ;
#endif // DX_NON_GRAPHICS
	
	if( DxSysData.NotDrawFlag == FALSE )
	{
#ifndef DX_NON_MODEL
		// ���f���o�[�W�����P�̏�����
		if( MV1Initialize() < 0 )
		{
			goto ERROR_DX ;
		}
#endif

#ifndef DX_NON_LIVE2D_CUBISM4
		// Live2D Cubism4 �֘A�̏�����
		Live2DCubism4_Initialize() ;
#endif // DX_NON_LIVE2D_CUBISM4
	}
	
	// �����_���W����������
#ifndef DX_NON_MERSENNE_TWISTER
	srandMT( ( unsigned int )NS_GetNowCount() ) ;
#else
	srand( NS_GetNowCount() ) ;
#endif

#ifndef DX_NON_ASYNCLOAD
	// �񓯊��ǂݍ��ݏ������s���X���b�h�𗧂Ă�
	if( SetupASyncLoadThread( 3 ) < 0 )
	{
		DXST_LOGFILE_ADDA( "Startup of asynchronous read processing thread failed\n"/*"�񓯊��ǂݍ��ݏ������s���X���b�h�̗����グ�Ɏ��s���܂���\n"*/ ) ;
		goto ERROR_DX ;
	}
#endif // DX_NON_ASYNCLOAD

	// ���������t���O��|��
	DxSysData.DxLib_RunInitializeFlag = FALSE ;

	DXST_LOGFILE_TABSUB ;
	DXST_LOGFILEFMT_ADDA(( "DX library initialization processing end" /*"�c�w���C�u�����̏����������I��"*/ ) ) ;

	// �I��
	return 0 ;

ERROR_DX:
	NS_DxLib_End() ;

	DXST_LOGFILE_TABSUB ;
	DXST_LOGFILEFMT_ADDA(( "Failed to initialize the DX library" /*"�c�w���C�u�����̏������������s"*/ )) ;

	// ���������t���O��|��
	DxSysData.DxLib_RunInitializeFlag = FALSE ;

	return -1 ;
} 

// ���C�u�����g�p�̏I���֐�
extern int NS_DxLib_End( void )
{
	// ���ɏI���������s���Ă��邩�A������������������Ă��Ȃ��ꍇ�͉������Ȃ�
	if( DxSysData.DxLib_InitializeFlag == FALSE )
	{
		return 0 ;
	}

#ifndef DX_NON_SOFTIMAGE
	// �o�^�����S�Ẵ\�t�g�C���[�W���폜
	InitSoftImage() ;
#endif // DX_NON_SOFTIMAGE

	// �e�����n�̏I��
#if !defined( DX_NON_LOG ) && !defined( DX_NON_PRINTF_DX )
	TerminateLog() ;			// ���O�����̌�n��
#endif

#ifndef DX_NON_NETWORK
	TerminateNetWork() ;		// �v�����r�������������֌W�̏I��
#endif

#ifndef DX_NON_LIVE2D_CUBISM4
	// Live2D Cubism4 �֘A�̌�n��
	Live2DCubism4_Terminate() ;
#endif // DX_NON_LIVE2D_CUBISM4

#ifndef DX_NON_SOUND
	NS_StopMusic() ;			// �l�h�c�h�����t����Ă����Ԃ̏ꍇ������~�߂�
#endif // DX_NON_SOUND

#ifndef DX_NON_MODEL
	MV1Terminate() ;			// ���f���o�[�W�����P�̌�n��
#endif

#ifndef DX_NON_GRAPHICS
	Graphics_Terminate() ;
#endif // DX_NON_GRAPHICS

	TerminateBaseImageManage() ;

#ifndef DX_NON_SOFTIMAGE
	TerminateSoftImageManage() ;
#endif // DX_NON_SOFTIMAGE

#ifndef DX_NON_MOVIE
	TerminateMovieManage() ;
#endif

#ifndef DX_NON_INPUT
	TerminateInputSystem() ;	// ���̓V�X�e���̏I��
#endif // DX_NON_INPUT

#ifndef DX_NON_SOUND
	TerminateSoundSystem() ;	// �T�E���h�V�X�e���̌�n��
	TerminateSoundConvert() ;	// �T�E���h�ϊ������̏I��
#endif // DX_NON_SOUND

	// �c�w���C�u���������������t���O��|��
	DxSysData.DxLib_InitializeFlag = FALSE ;

	// �A�[�J�C�u�t�@�C���A�N�Z�X�p�̃f�[�^�̌�n��
#ifndef DX_NON_DXA
	DXA_DIR_Terminate() ;
#endif

#ifndef DX_NON_ASYNCLOAD
	// �񓯊��ǂݍ��ݏ����p�̃X���b�h�����
	CloseASyncLoadThread() ;
#endif // DX_NON_ASYNCLOAD

	// �t�@�C���A�N�Z�X�����̌�n��
	TerminateFile() ;

#ifndef DX_NON_ASYNCLOAD
	// �񓯊��ǂݍ��ݏ����̌�n��
	TerminateASyncLoad() ;
#endif // DX_NON_ASYNCLOAD

#ifdef DX_USE_DXLIB_MEM_DUMP
	// �������_���v���s��
	NS_DxDumpAlloc() ;
#endif

#ifndef DX_NON_LOG
	// ���O�t�@�C���̌�n��
	LogFileTerminate() ;
#endif

	// �������̌�n�����s��
	MemoryTerminate() ;

	// �I��
	return 0 ;
}

// ���C�u�����̓����Ŏg�p���Ă���\���̂��[�����������āADxLib_Init �̑O�ɍs�����ݒ�𖳌�������( DxLib_Init �̑O�ł̂ݗL�� )
extern int NS_DxLib_GlobalStructInitialize( void )
{
//	_MEMSET( &GRA2, 0, sizeof( GRA2 ) ) ;

#ifndef DX_NON_GRAPHICS
	_MEMSET( &GraphicsSysData, 0, sizeof( GraphicsSysData ) );
#endif // DX_NON_GRAPHICS

	_MEMSET( &BaseImageManage, 0, sizeof( BaseImageManage ) ) ;
#ifndef DX_NON_SOUND
	_MEMSET( &SoundSysData, 0, sizeof( SoundSysData ) );
#endif // DX_NON_SOUND

	return 0;
}











// �G���[�����֐�

// �G���[����
extern int DxLib_Error( const wchar_t *ErrorStr )
{
	// �G���[���O�̔r�o
	DXST_LOGFILE_ADDW( ErrorStr ) ;
	DXST_LOGFILE_ADDW( L"\n" ) ;

	// �e�����n�̏I��
	NS_DxLib_End() ;

	exit( -1 ) ;

	return -1 ;
}

// ���C�u�����̃G���[�������s��( UTF16LE�� )
extern int DxLib_ErrorUTF16LE( const char *ErrorStr )
{
	int Result ;

	CHAR_TO_WCHAR_T_STRING_BEGIN( ErrorStr )
	CHAR_TO_WCHAR_T_STRING_SETUP( ErrorStr, return -1, DX_CHARCODEFORMAT_UTF16LE )

	Result = DxLib_Error( UseErrorStrBuffer ) ;

	CHAR_TO_WCHAR_T_STRING_END( ErrorStr )

	return Result ;
}



























// �J�E���^�y�ю����擾�n�֐�

// �~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
extern int NS_GetNowCount( int /*UseRDTSCFlag*/ )
{
	LONGLONG ResultLL ;
	int Result ;

	ResultLL  = NS_GetNowHiPerformanceCount() / 1000 ;
	ResultLL &= 0x7fffffff ;
	Result    = ( int )ResultLL ;

	return Result ;
}

// GetNowTime�̍����x�o�[�W����
extern LONGLONG NS_GetNowHiPerformanceCount( int /*UseRDTSCFlag*/ )
{
	LONGLONG NowTime ;
	timeval ltimeval ;

	gettimeofday( &ltimeval, NULL ) ;

	NowTime = ( LONGLONG )ltimeval.tv_sec * 1000000 + ltimeval.tv_usec ;

	return NowTime ;
}

// OS���񋟂��鍂���x�J�E���^�̌��݂̒l�𓾂�
extern ULONGLONG NS_GetNowSysPerformanceCount( void )
{
	return ( ULONGLONG )NS_GetNowHiPerformanceCount() ;
}

// OS���񋟂��鍂���x�J�E���^�̎��g��( 1�b�ӂ�̃J�E���g�� )�𓾂�
extern ULONGLONG NS_GetSysPerformanceFrequency( void )
{
	return 1000000 ;
}

// OS���񋟂��鍂���x�J�E���^�̒l��b�̒l�ɕϊ�����
extern ULONGLONG NS_ConvSysPerformanceCountToSeconds( ULONGLONG Count )
{
	return Count / 1000000 ;
}

// OS���񋟂��鍂���x�J�E���^�̒l���~���b�̒l�ɕϊ�����
extern ULONGLONG NS_ConvSysPerformanceCountToMilliSeconds( ULONGLONG Count )
{
	return Count / 1000 ;
}

// OS���񋟂��鍂���x�J�E���^�̒l���}�C�N���b�̒l�ɕϊ�����
extern ULONGLONG NS_ConvSysPerformanceCountToMicroSeconds( ULONGLONG Count )
{
	return Count ;
}

// OS���񋟂��鍂���x�J�E���^�̒l���i�m�b�̒l�ɕϊ�����
extern ULONGLONG NS_ConvSysPerformanceCountToNanoSeconds( ULONGLONG Count )
{
	return Count * 1000 ;
}

// �b�̒l��OS���񋟂��鍂���x�J�E���^�̒l�ɕϊ�����
extern ULONGLONG NS_ConvSecondsToSysPerformanceCount( ULONGLONG Seconds )
{
	return Seconds * 1000000 ;
}

// �~���b�̒l��OS���񋟂��鍂���x�J�E���^�̒l�ɕϊ�����
extern ULONGLONG NS_ConvMilliSecondsToSysPerformanceCount( ULONGLONG MilliSeconds )
{
	return MilliSeconds * 1000 ;
}

// �}�C�N���b�̒l��OS���񋟂��鍂���x�J�E���^�̒l�ɕϊ�����
extern ULONGLONG NS_ConvMicroSecondsToSysPerformanceCount( ULONGLONG MicroSeconds )
{
	return MicroSeconds ;
}

// �i�m�b�̒l��OS���񋟂��鍂���x�J�E���^�̒l�ɕϊ�����
extern ULONGLONG NS_ConvNanoSecondsToSysPerformanceCount( ULONGLONG NanoSeconds )
{
	return NanoSeconds / 1000 ;
}

// ���ݎ������擾����
extern int NS_GetDateTime( DATEDATA *DateBuf )
{
	time_t nowtime ;
	tm *datetime ;

	time( &nowtime ) ;

	datetime = localtime( &nowtime ) ;

	// ���[�J�������f�[�^�����ɐ�p�̃f�[�^�^�f�[�^�Ɏ�����ɉh������
	DateBuf->Year	= datetime->tm_year + 1900 ;
	DateBuf->Mon	= datetime->tm_mon + 1 ;
	DateBuf->Day	= datetime->tm_mday ;
	DateBuf->Hour	= datetime->tm_hour ;
	DateBuf->Min	= datetime->tm_min ;
	DateBuf->Sec	= datetime->tm_sec ;

	// �I��
	return 0 ;
}



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

// �o�b�e���[�֘A

// �d�r�̎c�ʂ� % �Ŏ擾����( �߂�l�F 100=�t���[�d���  0=�[�d�c�ʖ��� )
extern int NS_GetBatteryLifePercent( void )
{
	// ������
	return -1 ;
}







// �N���b�v�{�[�h�֌W

// �N���b�v�{�[�h�Ɋi�[����Ă���e�L�X�g�f�[�^��ǂݏo���A-1 �̏ꍇ�̓N���b�v�{�[�h�Ƀe�L�X�g�f�[�^�͖����Ƃ�������( DestBuffer �� NULL ��n���Ɗi�[�ɕK�v�ȃf�[�^�T�C�Y���Ԃ��Ă��� )
extern int GetClipboardText_PF( TCHAR *DestBuffer )
{
	// ������
	return -1 ;
}

// �N���b�v�{�[�h�Ɋi�[����Ă���e�L�X�g�f�[�^��ǂݏo���A-1 �̏ꍇ�̓N���b�v�{�[�h�Ƀe�L�X�g�f�[�^�͖����Ƃ�������( DestBuffer �� NULL ��n���Ɗi�[�ɕK�v�ȃf�[�^�T�C�Y���Ԃ��Ă��� )
extern int GetClipboardText_WCHAR_T_PF( wchar_t *DestBuffer )
{
	// ������
	return -1 ;
}

// �N���b�v�{�[�h�Ƀe�L�X�g�f�[�^���i�[����
extern int SetClipboardText_WCHAR_T_PF( const wchar_t *Text )
{
	// ������
	return -1 ;
}










// ���[���A�v���𑗐M���[���ҏW��ԂŋN������
// MailAddr    : ����( NULL �Ŗ��� )�A���[���A�h���X����������ꍇ�̓J���}�w,�x�ŋ�؂��Ă�������
// MainCCAddr  : CC �̈���( NULL �Ŗ��� )�A���[���A�h���X����������ꍇ�̓J���}�w,�x�ŋ�؂��Ă�������
// MainBCCAddr : BCC �̈���( NULL �Ŗ��� )�A���[���A�h���X����������ꍇ�̓J���}�w,�x�ŋ�؂��Ă�������
// Subject     : �^�C�g��( NULL �Ŗ��� )�A���[���A�h���X����������ꍇ�̓J���}�w,�x�ŋ�؂��Ă�������
// Text        : �{��( NULL �Ŗ��� )�A���[���A�h���X����������ꍇ�̓J���}�w,�x�ŋ�؂��Ă�������
extern int MailApp_Send_WCHAR_T_PF( const wchar_t *MailAddr, const wchar_t *MailCCAddr, const wchar_t *MailBCCAddr, const wchar_t *Subject, const wchar_t *Text )
{
	int Result = -1 ;
	char *MailAddrUTF8 = NULL ;
	char *MailCCAddrUTF8 = NULL ;
	char *MailBCCAddrUTF8 = NULL ;
	char *SubjectUTF8 = NULL ;
	char *TextUTF8 = NULL ;
	int Bytes ;

	if( MailAddr != NULL )
	{
		Bytes = ConvString( ( char * )MailAddr, -1, WCHAR_T_CHARCODEFORMAT, NULL, 0, DX_CHARCODEFORMAT_UTF8 ) ;
		MailAddrUTF8 = ( char * )DXALLOC( Bytes ) ;
		if( MailAddrUTF8 == NULL )
		{
			goto END ;
		}
		ConvString( ( char * )MailAddr, -1, WCHAR_T_CHARCODEFORMAT, MailAddrUTF8, Bytes, DX_CHARCODEFORMAT_UTF8 ) ;
	}

	if( MailCCAddr != NULL )
	{
		Bytes = ConvString( ( char * )MailCCAddr, -1, WCHAR_T_CHARCODEFORMAT, NULL, 0, DX_CHARCODEFORMAT_UTF8 ) ;
		MailCCAddrUTF8 = ( char * )DXALLOC( Bytes ) ;
		if( MailCCAddrUTF8 == NULL )
		{
			goto END ;
		}
		ConvString( ( char * )MailCCAddr, -1, WCHAR_T_CHARCODEFORMAT, MailCCAddrUTF8, Bytes, DX_CHARCODEFORMAT_UTF8 ) ;
	}

	if( MailBCCAddr != NULL )
	{
		Bytes = ConvString( ( char * )MailBCCAddr, -1, WCHAR_T_CHARCODEFORMAT, NULL, 0, DX_CHARCODEFORMAT_UTF8 ) ;
		MailBCCAddrUTF8 = ( char * )DXALLOC( Bytes ) ;
		if( MailBCCAddrUTF8 == NULL )
		{
			goto END ;
		}
		ConvString( ( char * )MailBCCAddr, -1, WCHAR_T_CHARCODEFORMAT, MailBCCAddrUTF8, Bytes, DX_CHARCODEFORMAT_UTF8 ) ;
	}

	if( Subject != NULL )
	{
		Bytes = ConvString( ( char * )Subject, -1, WCHAR_T_CHARCODEFORMAT, NULL, 0, DX_CHARCODEFORMAT_UTF8 ) ;
		SubjectUTF8 = ( char * )DXALLOC( Bytes ) ;
		if( SubjectUTF8 == NULL )
		{
			goto END ;
		}
		ConvString( ( char * )Subject, -1, WCHAR_T_CHARCODEFORMAT, SubjectUTF8, Bytes, DX_CHARCODEFORMAT_UTF8 ) ;
	}

	if( Text != NULL )
	{
		Bytes = ConvString( ( char * )Text, -1, WCHAR_T_CHARCODEFORMAT, NULL, 0, DX_CHARCODEFORMAT_UTF8 ) ;
		TextUTF8 = ( char * )DXALLOC( Bytes ) ;
		if( TextUTF8 == NULL )
		{
			goto END ;
		}
		ConvString( ( char * )Text, -1, WCHAR_T_CHARCODEFORMAT, TextUTF8, Bytes, DX_CHARCODEFORMAT_UTF8 ) ;
	}

	Result = -1;

END :
	if( MailAddrUTF8 != NULL )
	{
		DXFREE( MailAddrUTF8 ) ;
		MailAddrUTF8 = NULL ;
	}

	if( MailCCAddrUTF8 != NULL )
	{
		DXFREE( MailCCAddrUTF8 ) ;
		MailCCAddrUTF8 = NULL ;
	}

	if( MailBCCAddrUTF8 != NULL )
	{
		DXFREE( MailBCCAddrUTF8 ) ;
		MailBCCAddrUTF8 = NULL ;
	}

	if( SubjectUTF8 != NULL )
	{
		DXFREE( SubjectUTF8 ) ;
		SubjectUTF8 = NULL ;
	}

	if( TextUTF8 != NULL )
	{
		DXFREE( TextUTF8 ) ;
		TextUTF8 = NULL ;
	}

	// �߂�l��Ԃ�
	return Result ;
}









#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE
































#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �E�C���h�E�Y�̃��b�Z�[�W���[�v�ɑ��鏈�����s��
extern int NS_ProcessMessage( void )
{
	static int EndFlag = FALSE ;

	// �����t���O�������Ă�����Ȃɂ������I��
	if( EndFlag )
	{
		return 0 ;
	}

	// �t�@�C�������̎����I�������s��
//	ReadOnlyFileAccessProcessAll() ;

#ifndef DX_NON_SOUND
	{
		// �T�E���h�̎����I�������s��
//		NS_ProcessStreamSoundMemAll() ;
//		ST_SoftSoundPlayerProcessAll() ;
		ProcessPlayFinishDeleteSoundMemAll() ;
//		SoundBuffer_Apply_StopSoundBufferList() ;
//		ProcessPlay3DSoundMemAll() ;
		UpdateSound_PF();
	}
#endif // DX_NON_SOUND

#ifndef DX_NON_ASYNCLOAD
	// ���C���X���b�h����������񓯊��ǂݍ��݂̏������s��
	ProcessASyncLoadRequestMainThread() ;
#endif // DX_NON_ASYNCLOAD

	// ���t�̎����I�������s��
#ifndef DX_NON_SOUND
	NS_ProcessMusicMem() ;
#endif // DX_NON_SOUND

#ifndef DX_NON_INPUT
	// �L�[�{�[�h���͂̍X�V�������s��
	UpdateKeyboardInputState( FALSE ) ;

	// �p�b�h�̎����I�������s��
	JoypadEffectProcess() ;
#endif // DX_NON_INPUT

#ifndef DX_NON_NETWORK
	// �ʐM�֌W�̃��b�Z�[�W�������s��
	NS_ProcessNetMessage( TRUE ) ;
#endif

	// �������֌W�̎����I�������s��
	MemoryProcess() ;

#ifndef DX_NON_GRAPHICS
	// ��ʊ֌W�̎����������s��
	Graphics_iOS_FrontScreenProcess() ;
#endif // DX_NON_GRAPHICS

#ifndef DX_NON_KEYEX
	// �L�[���͏������s��
	{
		// �t���O�����Ă�
		EndFlag = TRUE ;

		NS_ProcessActKeyInput() ;

		// �t���O��|��
		EndFlag = FALSE ;
	}
#endif

	// �C�x���g�������[�v
	ProcessInputEvent();

	// �ʏ�I��
	return 0 ;
}

// �A�v�����A�N�e�B�u�ł͂Ȃ���Ԃł������𑱍s���邩�A�t���O���Z�b�g����
extern int NS_SetAlwaysRunFlag( int Flag )
{
	// �t���O���Z�b�g
	g_iOSSys.NonActiveRunFlag = Flag ;
	
	// �I��
	return 0 ;
}

// �\�t�g����A�N�e�B�u�ɂȂ����ۂɌĂ΂��R�[���o�b�N�֐���o�^����
extern int SetiOSLostFocusCallbackFunction( void (* Callback )( void *Data ), void *CallbackData )
{
	g_iOSSys.LostFocusCallbackFunction     = ( volatile void ( * )( void * ) )Callback ;
	g_iOSSys.LostFocusCallbackFunctionData = ( volatile void * )CallbackData ;

	return 0 ;
}

// �\�t�g���A�N�e�B�u�ɂȂ����ۂɌĂ΂��R�[���o�b�N�֐���o�^����
extern int SetiOSGainedFocusCallbackFunction( void (* Callback )( void *Data ), void *CallbackData )
{
	g_iOSSys.GainedFocusCallbackFunction     = ( volatile void ( * )( void * ) )Callback ;
	g_iOSSys.GainedFocusCallbackFunctionData = ( volatile void * )CallbackData ;

	return 0 ;
}

// �X�N���[�����W���c�w���C�u������ʍ��W�ɕϊ�����
extern int ConvScreenPositionToDxScreenPosition( int ScreenX, int ScreenY, int *DxScreenX, int *DxScreenY )
{
#ifdef DX_NON_GRAPHICS
	*DxScreenX = ScreenX ;
	*DxScreenY = ScreenY ;
#else // DX_NON_GRAPHICS

	RECT DestRect ;
	DWORD DestW ;
	DWORD DestH ;

	if( GSYS.Screen.FullScreenFitScalingFlag )
	{
		if( DxScreenX != NULL )
		{
			*DxScreenX = ScreenX * GIOS.Device.Screen.SubBackBufferTextureSizeX / GIOS.Device.Screen.Width ;
		}

		if( DxScreenY != NULL )
		{
			*DxScreenY = ScreenY * GIOS.Device.Screen.SubBackBufferTextureSizeY / GIOS.Device.Screen.Height ;
		}
	}
	else
	{
		DestW = GIOS.Device.Screen.Width ;
		DestH = GIOS.Device.Screen.Width * GIOS.Device.Screen.SubBackBufferTextureSizeY / GIOS.Device.Screen.SubBackBufferTextureSizeX ;
		if( DestH > GIOS.Device.Screen.Height )
		{
			DestW = GIOS.Device.Screen.Height * GIOS.Device.Screen.SubBackBufferTextureSizeX / GIOS.Device.Screen.SubBackBufferTextureSizeY ;
			DestH = GIOS.Device.Screen.Height ;
		}

		DestRect.left   = ( GIOS.Device.Screen.Width  - DestW ) / 2 ;
		DestRect.top    = ( GIOS.Device.Screen.Height - DestH ) / 2 ;
		DestRect.right  = DestRect.left + DestW ;
		DestRect.bottom = DestRect.top  + DestH ;

		if( DxScreenX != NULL )
		{
			*DxScreenX = ( ScreenX - DestRect.left ) * GIOS.Device.Screen.SubBackBufferTextureSizeX / ( int )DestW ;
		}

		if( DxScreenY != NULL )
		{
			*DxScreenY = ( ScreenY - DestRect.top  ) * GIOS.Device.Screen.SubBackBufferTextureSizeY / ( int )DestH ;
		}
	}

#endif // DX_NON_GRAPHICS

	// �I��
	return 0 ;
}

// �A�N�e�B�u�ɂȂ�܂ŉ������Ȃ�
extern void DxActiveWait_iOS( void )
{
//	while(
//		g_iOSSys.NonActiveRunFlag == FALSE
//		)
//	)
//	{
//		if( NS_ProcessMessage() < 0 )
//		{
//			break ;
//		}
//		Thread_Sleep( 32 ) ;
//	}
}

static const char *GetHomeDirectory() {
	return "/";
}

static const char *GetTmpDirectory() {
	return "/tmp/";
}

// �f�B���N�g���p�X��Ԃ��֐��̋��ʏ����p�̊֐�
static int DirPathCommonFunction( const char *AddPath, TCHAR *PathBuffer, int PathBufferBytes )
{
	const char *HomeDir = GetHomeDirectory() ;
	char DirPath[ 2048 ] ;
	int Result ;
	size_t Length = CL_strlen( DX_CHARCODEFORMAT_UTF8, HomeDir ) + CL_strlen( DX_CHARCODEFORMAT_UTF8, AddPath ) ;

	if( Length + 1 > sizeof( DirPath ) )
	{
		return -1 ;
	}

	CL_strcpy( DX_CHARCODEFORMAT_UTF8, DirPath, HomeDir ) ;
	CL_strcat( DX_CHARCODEFORMAT_UTF8, DirPath, AddPath ) ;

	if( PathBuffer == NULL )
	{
		TCHAR *TempBuffer ;
		size_t BufferSize ;

		BufferSize = ( Length + 1 ) * 16 ;
		TempBuffer = ( TCHAR * )DXALLOC( BufferSize ) ;
		if( TempBuffer == NULL )
		{
			return -1 ;
		}
		Result = ConvString( DirPath, -1, DX_CHARCODEFORMAT_UTF8, TempBuffer, BufferSize, _TCHARCODEFORMAT ) ;
		DXFREE( TempBuffer ) ;
		TempBuffer = NULL ;
	}
	else
	{
		Result = ConvString( DirPath, -1, DX_CHARCODEFORMAT_UTF8, PathBuffer, PathBufferBytes, _TCHARCODEFORMAT ) ;
	}

	// �I��
	return Result ;
}

// �\�t�g�̊O���f�[�^�ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetDocumentsDirPath( TCHAR *PathBuffer, size_t PathBufferBytes )
{
	return DirPathCommonFunction( "/Documents", PathBuffer, PathBufferBytes ) ;
}

// �\�t�g�̃f�[�^�ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetLibraryPreferencesDirPath( TCHAR *PathBuffer, size_t PathBufferBytes )
{
	return DirPathCommonFunction( "/Library/Preferences", PathBuffer, PathBufferBytes ) ;
}

// �\�t�g�̃L���b�V���t�@�C���ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetLibraryCachesDirPath( TCHAR *PathBuffer, size_t PathBufferBytes )
{
	return DirPathCommonFunction( "/Library/Caches", PathBuffer, PathBufferBytes ) ;
}

// �f�B���N�g���p�X��Ԃ��֐��̋��ʏ����p�̊֐�
static int DirPathCommonFunctionForChar( const char *AddPath, char *PathBuffer, int PathBufferBytes )
{
	const char *HomeDir = GetHomeDirectory() ;
	size_t Length = CL_strlen( DX_CHARCODEFORMAT_UTF8, HomeDir ) + CL_strlen( DX_CHARCODEFORMAT_UTF8, AddPath ) ;

	if( Length + 1 > PathBufferBytes )
	{
		return Length + 1 ;
	}

	if( PathBuffer != NULL )
	{
		CL_strcpy( DX_CHARCODEFORMAT_UTF8, PathBuffer, HomeDir ) ;
		CL_strcat( DX_CHARCODEFORMAT_UTF8, PathBuffer, AddPath ) ;
	}

	// �I��
	return Length + 1 ;
}

// �\�t�g�̊O���f�[�^�ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetDocumentsDirPathForChar( char *PathBuffer, size_t PathBufferBytes )
{
	return DirPathCommonFunctionForChar( "/Documents", PathBuffer, PathBufferBytes ) ;
}

// �\�t�g�̃f�[�^�ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetLibraryPreferencesDirPathForChar( char *PathBuffer, size_t PathBufferBytes )
{
	return DirPathCommonFunctionForChar( "/Library/Preferences", PathBuffer, PathBufferBytes ) ;
}

// �\�t�g�̃L���b�V���t�@�C���ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetLibraryCachesDirPathForChar( char *PathBuffer, size_t PathBufferBytes )
{
	return DirPathCommonFunctionForChar( "/Library/Caches", PathBuffer, PathBufferBytes ) ;
}

// �\�t�g�̈ꎞ�t�@�C���ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetTmpDirPathForChar( char *PathBuffer, size_t PathBufferBytes )
{
	const char *TmpDirPath = GetTmpDirectory() ;
	int Length = CL_strlen( DX_CHARCODEFORMAT_UTF8, TmpDirPath ) ;

	if( Length + 1 > PathBufferBytes )
	{
		return Length + 1 ;
	}

	if( PathBuffer != NULL )
	{
		CL_strcpy_s( DX_CHARCODEFORMAT_UTF8, PathBuffer, PathBufferBytes, TmpDirPath ) ;
	}

	// �I��
	return Length + 1 ;
}










#ifndef DX_NON_GRAPHICS

static int SetupViewBuffer( void )
{
	if( g_iOSSys.ViewFrameBuffer == 0 )
	{
		// glGenFramebuffers( 1, &g_iOSSys.ViewFrameBuffer ) ;
		// glBindFramebuffer( GL_FRAMEBUFFER, g_iOSSys.ViewFrameBuffer ) ;

		// glGenRenderbuffers( 1, &g_iOSSys.ViewDepthBuffer ) ;
		// glBindRenderbuffer( GL_RENDERBUFFER, g_iOSSys.ViewDepthBuffer ) ;
		// glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, GLsizei(canvas_width()), GLsizei(canvas_height()) );

		// glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_iOSSys.ViewDepthBuffer ) ;

		// glGenRenderbuffers( 1, &g_iOSSys.ViewRenderBuffer ) ;
		// glBindRenderbuffer( GL_RENDERBUFFER, g_iOSSys.ViewRenderBuffer ) ;

		// glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA4, GLsizei(canvas_width()), GLsizei(canvas_height()) );
		// glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, g_iOSSys.ViewRenderBuffer ) ;
	}

	return 0;
}

extern int GetGraphicsViewFramebufferInfo( unsigned int *ViewFrameBuffer, int *Width, int *Height ) {
	if( g_iOSSys.ViewWidth != GLsizei(canvas_width()) ||
		g_iOSSys.ViewHeight != GLsizei(canvas_height()) )
	{
		// TerminateViewBuffer() ;

		SetupViewBuffer() ;

		g_iOSSys.ViewWidth = GLsizei(canvas_width());
		g_iOSSys.ViewHeight = GLsizei(canvas_height()) ;

		Graphics_iOS_SetScreenSize( g_iOSSys.ViewWidth, g_iOSSys.ViewHeight );
	}

    if( ViewFrameBuffer ) *ViewFrameBuffer = g_iOSSys.ViewFrameBuffer;
    if( Width ) *Width = g_iOSSys.ViewWidth;
    if( Height ) *Height = g_iOSSys.ViewHeight;
    
	
    return 0;
}

extern void GraphicsViewRenderBufferPresent( void ) {
	glBindRenderbuffer( GL_RENDERBUFFER, g_iOSSys.ViewRenderBuffer ) ;
}

#endif

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE