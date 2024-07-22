//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�T�E���h�v���O����
// 
//  	Ver 3.24d
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_SOUND

// �C���N���[�h----------------------------------------------------------------
#include "DxSoundAndroid.h"
#include "DxFileAndroid.h"
#include "DxJavaAndroid.h"
#include "../DxSound.h"
#include "../DxSystem.h"
#include "../DxMemory.h"
#include "../DxLog.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����`------------------------------------------------------------------

// �X�g���[���Đ��p�̃o�b�t�@��ӂ�̃T���v����
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(512)
#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(735)
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(1024)
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(2048)
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(4096)
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(8192)

// �^��`----------------------------------------------------------------------

// �f�[�^�錾------------------------------------------------------------------

// �����f�[�^
static BYTE g_NoneSound8bit[  STREAM_SOUND_BUFFER_UNIT_SAPMLES ] ;
static WORD g_NoneSound16bit[ STREAM_SOUND_BUFFER_UNIT_SAPMLES ] ;

// �֐��v���g�^�C�v�錾 -------------------------------------------------------

static int SelfMixingPlayer_Setup( void ) ;														// ���O�~�L�V���O�p�̃T�E���h�Đ��̏������s��
static int SelfMixingPlayer_Terminate( void ) ;													// ���O�~�L�V���O�p�̃T�E���h�Đ��̌�n�����s��
static void SelfMixingPlayerBufferQueueCallback( SLAndroidSimpleBufferQueueItf , void *Data ) ;	// ���O�~�L�V���O�p�̃T�E���h�f�[�^���T�E���h�o�b�t�@�ɒǉ�����֐�
static void SelfMixingEnqueueSoundBuffer( void ) ;												// ���O�~�L�V���O�p�̃T�E���h�f�[�^���T�E���h�o�b�t�@�ɒǉ�����֐�

static void RefreshSoundBufferCurrentTime( SOUNDBUFFER *Buffer, SLAndroidSimpleBufferQueueState BufferQueState, int IsCriticalsectionLock = TRUE, int EnableStopSoundBuffer = FALSE ) ;	// �T�E���h�o�b�t�@�̍Đ����Ԃ��X�V����
static void PlayerBufferQueueCallback( SLAndroidSimpleBufferQueueItf , void *Data ) ;	// �T�E���h�f�[�^���T�E���h�o�b�t�@�ɒǉ�����
static void EnqueueSoundBuffer( SOUNDBUFFER *Buffer ) ;									// �T�E���h�f�[�^���T�E���h�o�b�t�@�ɒǉ�����
static void *StreamSoundThreadFunction( void *argc ) ;

static void SoundBuffer_Add_StopSoundBufferList( SOUNDBUFFER *Buffer ) ;			// ��~�҂��T�E���h�o�b�t�@���X�g�Ɏw��̃T�E���h�o�b�t�@��������
static void SoundBuffer_Sub_StopSoundBufferList( SOUNDBUFFER *Buffer ) ;			// ��~�҂��T�E���h�o�b�t�@���X�g����w��̃T�E���h�o�b�t�@���O��

static void TerminateSoundBufferPlayInfo( int InfoIndex ) ;							// �T�E���h�o�b�t�@�Đ��p���̌�n�����s��( �N���e�B�J���Z�N�V���������b�N������ԂŌĂԂ��� )
static int NotUseSoundBufferPlayInfo( int InfoIndex ) ;								// �w��̃T�E���h�o�b�t�@�Đ��p�����g�p���Ă��Ȃ���ԂɕύX����
static int SetupSoundBufferPlayInfo( SOUNDBUFFER *Buffer ) ;						// �T�E���h�o�b�t�@�Đ��p���̃Z�b�g�A�b�v�ƁA�Z�b�g�A�b�v�������̔ԍ����擾����
static int GetSoundBufferPlayInfo( int *ReleaseFlag ) ;								// ��ɏ��擾�p�ɍĐ������ς݂̏��̔ԍ����擾����( SoundBufferPlayInfosCriticalSection �̃��b�N������Ă���ĂԕK�v������ )

static int SetupEqualizerInfo( int PlayInfoIndex = -1 ) ;							// �C�R���C�U�[���̃Z�b�g�A�b�v���s��
static void TerminateEqualizerInfo( void ) ;										// �C�R���C�U�[���̌�n�����s��

// �v���O����------------------------------------------------------------------

// ��~�҂��T�E���h�o�b�t�@���X�g�Ɏw��̃T�E���h�o�b�t�@��������
static void SoundBuffer_Add_StopSoundBufferList( SOUNDBUFFER *Buffer )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;

	// ���X�g�ɒǉ�
	if( Buffer->PF.StopSoundBufferValid == FALSE )
	{
		Buffer->PF.StopSoundBufferValid = TRUE ;

		Buffer->PF.StopSoundBufferPrev = NULL ;
		Buffer->PF.StopSoundBufferNext = SoundSysData.PF.StopSoundBuffer ;
		if( SoundSysData.PF.StopSoundBuffer != NULL )
		{
			SoundSysData.PF.StopSoundBuffer->PF.StopSoundBufferPrev = Buffer ;
		}
		SoundSysData.PF.StopSoundBuffer = Buffer ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;
}

// ��~�҂��T�E���h�o�b�t�@���X�g����w��̃T�E���h�o�b�t�@���O��
static void SoundBuffer_Sub_StopSoundBufferList( SOUNDBUFFER *Buffer )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;

	if( Buffer->PF.StopSoundBufferValid )
	{
		Buffer->PF.StopSoundBufferValid = FALSE ;

		if( Buffer->PF.StopSoundBufferNext != NULL )
		{
			Buffer->PF.StopSoundBufferNext->PF.StopSoundBufferPrev = Buffer->PF.StopSoundBufferPrev ;
		}

		if( Buffer->PF.StopSoundBufferPrev != NULL )
		{
			Buffer->PF.StopSoundBufferPrev->PF.StopSoundBufferNext = Buffer->PF.StopSoundBufferNext ;
		}
		else
		{
			SoundSysData.PF.StopSoundBuffer = Buffer->PF.StopSoundBufferNext ;
		}

		Buffer->PF.StopSoundBufferNext = NULL ;
		Buffer->PF.StopSoundBufferPrev = NULL ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;
}

// ��~�҂��T�E���h�o�b�t�@���X�g�ɓo�^����Ă���T�E���h�o�b�t�@���~����
extern void SoundBuffer_Apply_StopSoundBufferList( void )
{
	for(;;)
	{
		SOUNDBUFFER *StopSoundBuffer = NULL ;

		// �N���e�B�J���Z�N�V�����̎擾
		CRITICALSECTION_LOCK( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;

		StopSoundBuffer = SoundSysData.PF.StopSoundBuffer ;

		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;

		// �o�^����Ă���T�E���h�o�b�t�@��������ΏI��
		if( StopSoundBuffer == NULL )
		{
			break ;
		}

		// �Đ��̒�~
		SoundBuffer_Stop( StopSoundBuffer ) ;
	}

}

// ���O�~�L�V���O�p�̃T�E���h�Đ��̏������s��
static int SelfMixingPlayer_Setup( void )
{
	SLresult Result = 0 ;

	// �o�̓I�u�W�F�N�g�̍쐬
	Result = ( *SoundSysData.PF.EngineInterface )->CreateOutputMix( SoundSysData.PF.EngineInterface, &SoundSysData.PF.SelfMixing_OutputMixObject, 0, NULL, NULL /* 1, ids, req */ ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x75\x00\x74\x00\x70\x00\x75\x00\x74\x00\x4d\x00\x69\x00\x78\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"OutputMix �̍쐬�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, Result )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// �o�̓I�u�W�F�N�g�̃��A���C�Y
	Result = ( *SoundSysData.PF.SelfMixing_OutputMixObject )->Realize( SoundSysData.PF.SelfMixing_OutputMixObject, SL_BOOLEAN_FALSE ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x75\x00\x74\x00\x70\x00\x75\x00\x74\x00\x4d\x00\x69\x00\x78\x00\x20\x00\x6e\x30\xea\x30\xa2\x30\xe9\x30\xa4\x30\xba\x30\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"OutputMix �̃��A���C�Y�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, Result )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// ���O�~�L�V���O�t�H�[�}�b�g�����Z�b�g
	_MEMSET( &SoundSysData.SelfMixingFormat, 0, sizeof( SoundSysData.SelfMixingFormat ) ) ;
	SoundSysData.SelfMixingFormat.cbSize          = 0 ;
	SoundSysData.SelfMixingFormat.wFormatTag      = WAVE_FORMAT_PCM ;
	SoundSysData.SelfMixingFormat.nChannels       = 2 ;
	SoundSysData.SelfMixingFormat.nSamplesPerSec  = SoundSysData.PF.AudioManager_SampleRate ;
	SoundSysData.SelfMixingFormat.wBitsPerSample  = 16 ;
	SoundSysData.SelfMixingFormat.nBlockAlign     = SoundSysData.SelfMixingFormat.nChannels * SoundSysData.SelfMixingFormat.wBitsPerSample / 8 ;
	SoundSysData.SelfMixingFormat.nAvgBytesPerSec = SoundSysData.SelfMixingFormat.nSamplesPerSec * SoundSysData.SelfMixingFormat.nBlockAlign ;

	SoundSysData.SelfMixingFormatValidBitsPerSample = 16 ;
	SoundSysData.SelfMixingFormatIsMSB = FALSE ;
	SoundSysData.SelfMixingFormatIsFloat = FALSE ;

	// �v���C���[�I�u�W�F�N�g�쐬
	{
		SLDataLocator_AndroidSimpleBufferQueue	LocBufq ;
		SLDataFormat_PCM						FormatPcm ;
		SLDataSource							AudioSrc ;
		SLDataLocator_OutputMix					LocOutmix ;
		SLDataSink								AudioDataSink ;
//		const SLInterfaceID						ids[ 4 ] = { SL_IID_PLAY,     SL_IID_BUFFERQUEUE, SL_IID_VOLUME,   SL_IID_EQUALIZER } ;
//		const SLboolean							req[ 4 ] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,    SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE  } ;
		const SLInterfaceID						ids[ 3 ] = { SL_IID_PLAY,     SL_IID_ANDROIDSIMPLEBUFFERQUEUE, SL_IID_VOLUME    } ;
		const SLboolean							req[ 3 ] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,                 SL_BOOLEAN_FALSE } ;

		FormatPcm.formatType	= SL_DATAFORMAT_PCM;
		FormatPcm.numChannels	= ( SLuint32 )2 ;
		FormatPcm.samplesPerSec	= ( SLuint32 )SoundSysData.PF.AudioManager_SampleRate * 1000 ;
		FormatPcm.bitsPerSample	= SL_PCMSAMPLEFORMAT_FIXED_16 ;
		FormatPcm.containerSize	= SL_PCMSAMPLEFORMAT_FIXED_16 ;
		FormatPcm.channelMask	= SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT ;
		FormatPcm.endianness	= SL_BYTEORDER_LITTLEENDIAN ;

		LocBufq.locatorType		= SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE ;
		LocBufq.numBuffers		= 2 ;
		AudioSrc.pLocator		= &LocBufq ;
		AudioSrc.pFormat		= &FormatPcm ;

		LocOutmix.locatorType	= SL_DATALOCATOR_OUTPUTMIX ;
		LocOutmix.outputMix		= SoundSysData.PF.SelfMixing_OutputMixObject ;

		AudioDataSink.pLocator	= &LocOutmix ;
		AudioDataSink.pFormat	= NULL ;

		Result = ( *SoundSysData.PF.EngineInterface )->CreateAudioPlayer(
			SoundSysData.PF.EngineInterface,
			&SoundSysData.PF.SelfMixing_PlayerObject,
			&AudioSrc,
			&AudioDataSink,
			3,
//			SoundSysData.PF.UseEqualizer ? 4 : 3,
			ids,
			req
		) ;
		if( Result != SL_RESULT_SUCCESS )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd7\x30\xec\x30\xa4\x30\xe4\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"�v���C���[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, Result )) ;
			DXST_LOGFILE_TABSUB ;
			return -1 ;
		}
	}

	// �v���C���[�I�u�W�F�N�g�̃��A���C�Y
	Result = ( *SoundSysData.PF.SelfMixing_PlayerObject )->Realize( SoundSysData.PF.SelfMixing_PlayerObject, SL_BOOLEAN_FALSE ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\xd7\x30\xec\x30\xa4\x30\xe4\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\xea\x30\xa2\x30\xe9\x30\xa4\x30\xba\x30\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"�v���C���[�I�u�W�F�N�g�̃��A���C�Y�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, Result )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// �Đ��C���^�[�t�F�[�X�̎擾
	Result = ( *SoundSysData.PF.SelfMixing_PlayerObject )->GetInterface( SoundSysData.PF.SelfMixing_PlayerObject, SL_IID_PLAY, &SoundSysData.PF.SelfMixing_PlayerPlayInterface ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x8d\x51\x1f\x75\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xa4\x30\xb9\x30\x6e\x30\xd6\x53\x97\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"�Đ��C���^�[�t�F�C�X�̎擾�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, Result )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// �o�b�t�@�L���[�C���^�[�t�F�[�X�̎擾
	Result = ( *SoundSysData.PF.SelfMixing_PlayerObject )->GetInterface( SoundSysData.PF.SelfMixing_PlayerObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &SoundSysData.PF.SelfMixing_PlayerBufferQueueInterface ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\xb7\x30\xf3\x30\xd7\x30\xeb\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\xad\x30\xe5\x30\xfc\x30\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xa4\x30\xb9\x30\x6e\x30\xd6\x53\x97\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"�V���v���o�b�t�@�L���[�C���^�[�t�F�C�X�̎擾�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, Result )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// �o�b�t�@�L���[�C���^�[�t�F�[�X�̃R�[���o�b�N�֐��̐ݒ�
	Result = ( *SoundSysData.PF.SelfMixing_PlayerBufferQueueInterface )->RegisterCallback( SoundSysData.PF.SelfMixing_PlayerBufferQueueInterface, SelfMixingPlayerBufferQueueCallback, NULL ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\xb7\x30\xf3\x30\xd7\x30\xeb\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\xad\x30\xe5\x30\xfc\x30\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xa4\x30\xb9\x30\x6e\x30\xb3\x30\xfc\x30\xeb\x30\xd0\x30\xc3\x30\xaf\x30\xa2\x95\x70\x65\x6e\x30\x2d\x8a\x9a\x5b\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"�V���v���o�b�t�@�L���[�C���^�[�t�F�C�X�̃R�[���o�b�N�֐��̐ݒ�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, Result )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// �o�b�t�@�L���[�ɃT�E���h�f�[�^��ǉ�
	SelfMixingEnqueueSoundBuffer() ;
	SelfMixingEnqueueSoundBuffer() ;

	// �Đ����J�n
	Result = ( *SoundSysData.PF.SelfMixing_PlayerPlayInterface )->SetPlayState( SoundSysData.PF.SelfMixing_PlayerPlayInterface, SL_PLAYSTATE_PLAYING ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\xb5\x30\xa6\x30\xf3\x30\xc9\x30\x6e\x30\x8d\x51\x1f\x75\x8b\x95\xcb\x59\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"�T�E���h�̍Đ��J�n�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, Result )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// ����I��
	return 0 ;
}

// ���O�~�L�V���O�p�̃T�E���h�Đ��̌�n�����s��
static int SelfMixingPlayer_Terminate( void )
{
	if( SoundSysData.PF.SelfMixing_PlayerObject )
	{
		if( SoundSysData.PF.SelfMixing_PlayerPlayInterface != NULL )
		{
			( *SoundSysData.PF.SelfMixing_PlayerPlayInterface )->SetPlayState( SoundSysData.PF.SelfMixing_PlayerPlayInterface, SL_PLAYSTATE_STOPPED ) ;
		}

		( *SoundSysData.PF.SelfMixing_PlayerObject)->Destroy( SoundSysData.PF.SelfMixing_PlayerObject ) ;
		SoundSysData.PF.SelfMixing_PlayerObject = NULL ;
	}

	if( SoundSysData.PF.SelfMixing_OutputMixObject != NULL )
	{
		( *SoundSysData.PF.SelfMixing_OutputMixObject )->Destroy( SoundSysData.PF.SelfMixing_OutputMixObject ) ;
		SoundSysData.PF.SelfMixing_OutputMixObject = NULL ;
	}

	// ����I��
	return 0 ;
}

// ���O�~�L�V���O�p�̃T�E���h�f�[�^���T�E���h�o�b�t�@�ɒǉ�����֐�
static void SelfMixingPlayerBufferQueueCallback( SLAndroidSimpleBufferQueueItf, void* /* Data */ )
{
	SoundSysData.PF.SelfMixing_TotalPlaySampleCount += SoundSysData.PF.AudioManager_FramesPerBuffer ;

	SelfMixingEnqueueSoundBuffer() ;
}

// ���O�~�L�V���O�p�̃T�E���h�f�[�^���T�E���h�o�b�t�@�ɒǉ�����֐�
static void SelfMixingEnqueueSoundBuffer( void )
{
//	SLAndroidSimpleBufferQueueState BufferQueState ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	if( SoundSysData.PF.SelfMixing_PlayerObject == NULL ||
		SoundSysData.PF.SelfMixing_PlayerPlayInterface == NULL ||
		SoundSysData.PF.SelfMixing_PlayerBufferQueueInterface == NULL /* ||
		( *SoundSysData.PF.SelfMixing_PlayerBufferQueueInterface )->GetState( SoundSysData.PF.SelfMixing_PlayerBufferQueueInterface, &BufferQueState ) != SL_RESULT_SUCCESS */ )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;
		return ;
	}

	WriteSelfMixingSample( SoundSysData.PF.SelfMixing_OutputBuffer, SoundSysData.PF.SelfMixing_OutputBuffer + 2, 4, SoundSysData.PF.AudioManager_FramesPerBuffer ) ;

	( *SoundSysData.PF.SelfMixing_PlayerBufferQueueInterface )->Enqueue(
		SoundSysData.PF.SelfMixing_PlayerBufferQueueInterface,
		SoundSysData.PF.SelfMixing_OutputBuffer,
		4 * SoundSysData.PF.AudioManager_FramesPerBuffer
	) ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;
}

// �T�E���h�o�b�t�@�̍Đ����Ԃ��X�V����
static void RefreshSoundBufferCurrentTime( SOUNDBUFFER *Buffer, SLAndroidSimpleBufferQueueState BufferQueState, int IsCriticalsectionLock, int EnableStopSoundBuffer )
{
	if( IsCriticalsectionLock )
	{
		// �N���e�B�J���Z�N�V�����̎擾
		CRITICALSECTION_LOCK( &Buffer->PF.CriticalSection ) ;
	}

	// �Đ��ʒu�̍X�V
	if( Buffer->PF.EnqueueInfoNum > 0 )
	{
		int OutputNum ;

		OutputNum = Buffer->PF.EnqueueInfoNum - BufferQueState.count ;
		if( OutputNum > 0 )
		{
			int i ;

			Buffer->PlayPos = Buffer->PF.EnqueueInfo[ OutputNum - 1 ].CompPos ;
			for( i = 0 ; i < OutputNum ; i ++ )
			{
				Buffer->PF.WorkBufferUseFlag[ Buffer->PF.EnqueueInfo[ i ].WorkBufferIndex ] = FALSE ;
			}

			Buffer->PF.EnqueueInfoNum -= OutputNum ;
			if( Buffer->PF.EnqueueInfoNum > 0 )
			{
				_MEMMOVE(
					( void * )&Buffer->PF.EnqueueInfo[ 0 ],
					( void * )&Buffer->PF.EnqueueInfo[ OutputNum ],
					sizeof( BUFFERENQUEUE_INFO ) * Buffer->PF.EnqueueInfoNum
				) ;
			}

			if( Buffer->PlayPos == Buffer->SampleNum && Buffer->PF.BufferEndPlayEnqueueNum > 0 )
			{
				if( EnableStopSoundBuffer )
				{
					SoundBuffer_Stop( Buffer ) ;
				}
				else
				{
					// ��~�҂��T�E���h�o�b�t�@���X�g�ɒǉ�
					SoundBuffer_Add_StopSoundBufferList( Buffer ) ;
				}
			}
		}
	}

	if( IsCriticalsectionLock )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;
	}
}

// �o�b�t�@�L���[�C���^�[�t�F�[�X����Ă΂��R�[���o�b�N�֐�
static void PlayerBufferQueueCallback( SLAndroidSimpleBufferQueueItf BufferQueueInterface, void *Data )
{
	EnqueueSoundBuffer( ( SOUNDBUFFER * )Data ) ;
}

// �T�E���h�f�[�^���T�E���h�o�b�t�@�ɒǉ�����
static void EnqueueSoundBuffer( SOUNDBUFFER *Buffer )
{
	DWORD BytesRequired ;
	SLAndroidSimpleBufferQueueState BufferQueState ;
	int AddMaxCount ;
	int i ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &Buffer->PF.CriticalSection ) ;
	CRITICALSECTION_LOCK( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	if( Buffer->State == FALSE ||
		Buffer->PF.UseSoundBufferPlayInfoIndex < 0 ||
		Buffer->PF.UseSoundBufferPlayInfoIndex >= SOUNDBUFFERPLAYINFO_MAX_NUM )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;
		CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;
		return ;
	}

	SOUNDBUFFERPLAYINFO *SoundBufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ Buffer->PF.UseSoundBufferPlayInfoIndex ] ;

	int CompPos ;
	float CompPosF ;
	int Loop ;
	void *SampleBuffer ;
	int BlockAlign ;

	if( SoundBufferPlayInfo->UseFlag == FALSE ||
		SoundBufferPlayInfo->PlayerObject == NULL ||
		SoundBufferPlayInfo->PlayerPlayInterface == NULL ||
		SoundBufferPlayInfo->PlayerBufferQueueInterface == NULL ||
		( *SoundBufferPlayInfo->PlayerBufferQueueInterface )->GetState( SoundBufferPlayInfo->PlayerBufferQueueInterface, &BufferQueState ) != SL_RESULT_SUCCESS )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;
		CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;
		return ;
	}

	// �Đ��ʒu�̍X�V
	RefreshSoundBufferCurrentTime( Buffer, BufferQueState, FALSE ) ;

	SampleBuffer	= Buffer->Wave->DoubleSizeBuffer ? Buffer->Wave->DoubleSizeBuffer : Buffer->Wave->Buffer ;
	BlockAlign		= Buffer->Format.wBitsPerSample * Buffer->Format.nChannels / 8 ;
	BytesRequired	= STREAM_SOUND_BUFFER_UNIT_SAPMLES * BlockAlign ;

	CompPos		= Buffer->CompPos ;
	CompPosF	= Buffer->CompPosF ;
	Loop		= Buffer->Loop ;
	AddMaxCount	= BUFFERQUEUE_BUFFER_NUM - BufferQueState.count ;

	// CompPosF ���L�����ǂ����ŏ����𕪊�
	if( Buffer->EnableComPosF )
	{
		for( i = 0 ; i < AddMaxCount ; i ++ )
		{
			void *AddBuffer = NULL ;
			SLuint32 AddBytes = 0 ;

			CompPos	 = Buffer->CompPos ;
			CompPosF = Buffer->CompPosF ;

			if( CompPos >= Buffer->SampleNum )
			{
				if( Loop )
				{
					while( CompPos >= Buffer->SampleNum )
					{
						CompPosF -= Buffer->SampleNum ;
						CompPos = _FTOL( CompPosF ) ;
					}

					goto COPYDATA_FREQ ;
				}
				else
				{
					// �����o�b�t�@��ς�
					switch( Buffer->Format.wBitsPerSample )
					{
					case 8:
						AddBuffer = g_NoneSound8bit ;
						AddBytes = sizeof( g_NoneSound8bit ) ;
						break ;

					case 16:
						AddBuffer = g_NoneSound16bit ;
						AddBytes = sizeof( g_NoneSound16bit ) ;
						break ;
					}

					if( Buffer->PF.PlaySetupComp )
					{
						( *SoundBufferPlayInfo->PlayerBufferQueueInterface )->Enqueue(
							SoundBufferPlayInfo->PlayerBufferQueueInterface,
							AddBuffer,
							AddBytes
						) ;
					}

					Buffer->PF.EnqueueInfo[ Buffer->PF.EnqueueInfoNum ].CompPos = Buffer->SampleNum ;
					Buffer->PF.EnqueueInfo[ Buffer->PF.EnqueueInfoNum ].AddBytes = AddBytes ;
					Buffer->PF.EnqueueInfoNum ++ ;

					Buffer->PF.BufferEndPlayEnqueueNum ++ ;
					break ;
				}
			}
			else
			{
				// �g�p�����Ɨp�o�b�t�@��T��
				WORD BufferIndex ;

			COPYDATA_FREQ:

				for( BufferIndex = 0 ; Buffer->PF.WorkBufferUseFlag[ BufferIndex ] ; BufferIndex ++ ){}
				Buffer->PF.WorkBufferUseFlag[ BufferIndex ] = TRUE ;

				int IsEndSrc ;
				DWORD BufferSetSamples ;
				SoundBuffer_ConvertFrequency(
					SampleBuffer, Buffer->SampleNum, Buffer->PF.WorkBuffer[ BufferIndex ], STREAM_SOUND_BUFFER_UNIT_SAPMLES,
					Buffer->Format.nChannels, Buffer->Format.wBitsPerSample, Buffer->Format.wBitsPerSample, ( float )Buffer->Frequency / Buffer->Format.nSamplesPerSec,
					Loop, &CompPos, &CompPosF, &IsEndSrc, &BufferSetSamples ) ;

				if( Buffer->PF.PlaySetupComp )
				{
					( *SoundBufferPlayInfo->PlayerBufferQueueInterface )->Enqueue(
						SoundBufferPlayInfo->PlayerBufferQueueInterface,
						Buffer->PF.WorkBuffer[ BufferIndex ],
						BufferSetSamples * BlockAlign
					) ;
				}

				Buffer->PF.EnqueueInfo[ Buffer->PF.EnqueueInfoNum ].CompPos = CompPos ;
				Buffer->PF.EnqueueInfo[ Buffer->PF.EnqueueInfoNum ].AddBytes = BufferSetSamples * BlockAlign ;
				Buffer->PF.EnqueueInfo[ Buffer->PF.EnqueueInfoNum ].WorkBufferIndex = BufferIndex ;
				Buffer->PF.EnqueueInfoNum ++ ;

				Buffer->CompPos  = CompPos ;
				Buffer->CompPosF = CompPosF ;

				Buffer->PF.BufferEndPlayEnqueueNum = 0 ;
			}
		}
	}
	else
	{
		for( i = 0 ; i < AddMaxCount ; i ++ )
		{
			void *AddBuffer = NULL ;
			SLuint32 AddBytes = 0 ;

			if( CompPos >= Buffer->SampleNum )
			{
				if( Loop )
				{
					CompPos = 0 ;
					goto COPYDATA ;
				}
				else
				{
	//				if( i == 0 && BufferQueState.count == 0 )
	//				{
	//					SoundBuffer_Stop( Buffer ) ;
	//				}

									// �����o�b�t�@��ς�
					switch( Buffer->Format.wBitsPerSample )
					{
					case 8:
						AddBuffer = g_NoneSound8bit ;
						AddBytes = sizeof( g_NoneSound8bit ) ;
						break ;

					case 16:
						AddBuffer = g_NoneSound16bit ;
						AddBytes = sizeof( g_NoneSound16bit ) ;
						break ;
					}

					if( Buffer->PF.PlaySetupComp )
					{
						( *SoundBufferPlayInfo->PlayerBufferQueueInterface )->Enqueue(
							SoundBufferPlayInfo->PlayerBufferQueueInterface,
							AddBuffer,
							AddBytes
						) ;
					}

					Buffer->PF.EnqueueInfo[ Buffer->PF.EnqueueInfoNum ].CompPos = Buffer->SampleNum ;
					Buffer->PF.EnqueueInfo[ Buffer->PF.EnqueueInfoNum ].AddBytes = AddBytes ;
					Buffer->PF.EnqueueInfoNum ++ ;

					Buffer->PF.BufferEndPlayEnqueueNum ++ ;
					break ;
				}
			}
			else
			{
				DWORD NowBytes ;
				DWORD AddSamples ;

			COPYDATA:
				NowBytes = ( DWORD )( CompPos * BlockAlign ) ;
				AddBuffer = ( BYTE * )SampleBuffer + NowBytes ;
				AddSamples = ( DWORD )( Buffer->SampleNum - CompPos ) ;
				AddBytes = AddSamples * BlockAlign ;
				if( AddBytes > BytesRequired )
				{
					AddSamples = BytesRequired / BlockAlign ;
					AddBytes = AddSamples * BlockAlign ;
				}

				if( Buffer->PF.PlaySetupComp )
				{
					( *SoundBufferPlayInfo->PlayerBufferQueueInterface )->Enqueue(
						SoundBufferPlayInfo->PlayerBufferQueueInterface,
						AddBuffer,
						AddBytes
					) ;
				}

				Buffer->PF.EnqueueInfo[ Buffer->PF.EnqueueInfoNum ].CompPos = CompPos ;
				Buffer->PF.EnqueueInfo[ Buffer->PF.EnqueueInfoNum ].AddBytes = AddBytes ;
				Buffer->PF.EnqueueInfoNum ++ ;

				Buffer->PF.BufferEndPlayEnqueueNum = 0 ;

				CompPos += AddSamples ;
			}

			Buffer->CompPos = CompPos ;
		}
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;
	CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;
}

// �X�g���[���T�E���h�����p�X���b�h
static void *StreamSoundThreadFunction( void *argc )
{
	SLmillisecond PrevMsec = 0 ;
	SLmillisecond NowMsec = 0 ;
	int MsecNoChangeCounter = 0 ;

	while( SoundSysData.PF.ProcessSoundThreadEndRequest == FALSE )
	{
		// �N���e�B�J���Z�N�V�����̎擾
		CRITICALSECTION_LOCK( &HandleManageArray[ DX_HANDLETYPE_SOUND ].CriticalSection ) ;

		// ��~�҂��T�E���h�o�b�t�@���X�g�ɓo�^����Ă���T�E���h�o�b�t�@���~����
		SoundBuffer_Apply_StopSoundBufferList() ;

		// �X�g���[�~���O����
		NS_ProcessStreamSoundMemAll() ;

		// �Đ����I��������n���h�����폜���鏈�����s��
//		ProcessPlayFinishDeleteSoundMemAll() ;

		// �R�c�T�E���h���Đ����Ă���T�E���h�n���h���ɑ΂��鏈�����s��
		ProcessPlay3DSoundMemAll() ;

		// �Đ����Ă���T�E���h�n���h���ɑ΂��鏈�����s��
		ProcessPlaySoundMemAll() ;

		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &HandleManageArray[ DX_HANDLETYPE_SOUND ].CriticalSection ) ;


		// �N���e�B�J���Z�N�V�����̎擾
		CRITICALSECTION_LOCK( &HandleManageArray[ DX_HANDLETYPE_SOFTSOUND ].CriticalSection ) ;

		// �X�g���[�~���O����
		ST_SoftSoundPlayerProcessAll() ;

		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &HandleManageArray[ DX_HANDLETYPE_SOFTSOUND ].CriticalSection ) ;


		// ���O�~�L�V���O�p�� Open SL �I�u�W�F�N�g�����������Ă�����쐬���Ȃ���
		if( SoundSysData.EnableSelfMixingFlag )
		{
			SLuint32 State ;
			SLresult Result ;

			Result = ( *SoundSysData.PF.SelfMixing_PlayerPlayInterface )->GetPlayState( SoundSysData.PF.SelfMixing_PlayerPlayInterface, &State ) ;

			PrevMsec = NowMsec ;
			( *SoundSysData.PF.SelfMixing_PlayerPlayInterface )->GetPosition( SoundSysData.PF.SelfMixing_PlayerPlayInterface, &NowMsec );
			if( PrevMsec == NowMsec )
			{
				MsecNoChangeCounter++ ;
			}
			else
			{
				MsecNoChangeCounter = 0 ;
			}

			if( Result != SL_RESULT_SUCCESS || State == SL_PLAYSTATE_STOPPED || MsecNoChangeCounter > 10 )
			{
				SelfMixingPlayer_Terminate() ;
				SelfMixingPlayer_Setup() ;
			}
		}

		// �҂�
		Thread_Sleep( 10 ) ;
	}

	return NULL ;
}

// �T�E���h�V�X�e��������������֐��̊��ˑ��������s���֐�
extern int InitializeSoundSystem_PF_Timing0( void )
{
	int i ;

	if( SoundSysData.PF.EngineObjectInitialize )
	{
		return 0 ;
	}

	DXST_LOGFILE_ADDUTF16LE( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\x1d\x52\x1f\x67\x16\x53\x8b\x95\xcb\x59\x0a\x00\x00"/*@ L"OpenSL ES �̏������J�n\n" @*/ ) ;

	DXST_LOGFILE_TABADD ;

	// �I�[�f�B�I�f�o�C�X�ɓK�����o�b�t�@�T�C�Y�ƃT���v�����O���[�g���擾����
	if( JAVAANDR.fieldint_Build_VERSION_SDK_INT >= 17 )
	{
		JNIEnv *env ;

		pthread_mutex_lock( &g_AndroidSys.NativeActivityMutex ) ;

		if( g_AndroidSys.NativeActivity != NULL )
		{
			// JavaVM �ƃ\�t�g���s�p�X���b�h���֘A�t��
			if( g_AndroidSys.NativeActivity->vm->AttachCurrentThreadAsDaemon( &env, NULL ) == JNI_OK )
			{
				jobject object_AudioManager = NULL ;

				object_AudioManager = env->CallObjectMethod( g_AndroidSys.NativeActivity->clazz, JAVAANDR.methodID_Context_getSystemService, JAVAANDR.fieldobject_Context_AUDIO_SERVICE ) ;
				if( object_AudioManager != NULL )
				{
					jstring string_sampleRate = NULL ;

					string_sampleRate = ( jstring )env->CallObjectMethod( object_AudioManager, JAVAANDR.methodID_AudioManager_getProperty, JAVAANDR.fieldstring_AudioManager_PROPERTY_OUTPUT_SAMPLE_RATE ) ;
					if( string_sampleRate != NULL )
					{
						jstring string_framesPerBuffer = NULL ;

						string_framesPerBuffer = ( jstring )env->CallObjectMethod( object_AudioManager, JAVAANDR.methodID_AudioManager_getProperty, JAVAANDR.fieldstring_AudioManager_PROPERTY_OUTPUT_FRAMES_PER_BUFFER ) ;
						if( string_framesPerBuffer != NULL )
						{
							SoundSysData.PF.AudioManager_SampleRate      = env->CallStaticIntMethod( JAVAANDR.class_Integer, JAVAANDR.methodID_Integer_parseInt, string_sampleRate ) ;
							SoundSysData.PF.AudioManager_FramesPerBuffer = env->CallStaticIntMethod( JAVAANDR.class_Integer, JAVAANDR.methodID_Integer_parseInt, string_framesPerBuffer ) ;

							// ��Ɨp�o�b�t�@�̏���
							if( SetupSelfMixingWorkBuffer( SoundSysData.SelfMixingFormatIsFloat, SoundSysData.PF.AudioManager_FramesPerBuffer ) >= 0 )
							{
								DXST_LOGFILEFMT_ADDUTF16LE(( "\xaa\x30\xfc\x30\xc7\x30\xa3\x30\xaa\x30\xc7\x30\xd0\x30\xa4\x30\xb9\x30\x6e\x30\xcd\x30\xa4\x30\xc6\x30\xa3\x30\xd6\x30\x6a\x30\xb5\x30\xf3\x30\xd7\x30\xea\x30\xf3\x30\xb0\x30\xec\x30\xfc\x30\xc8\x30\x20\x00\x20\x00\x20\x00\x20\x00\x20\x00\x20\x00\x20\x00\x3a\x00\x20\x00\x25\x00\x64\x00\x20\x00\x48\x00\x7a\x00\x00"/*@ L"�I�[�f�B�I�f�o�C�X�̃l�C�e�B�u�ȃT���v�����O���[�g       : %d Hz" @*/, SoundSysData.PF.AudioManager_SampleRate )) ;
								DXST_LOGFILEFMT_ADDUTF16LE(( "\xaa\x30\xfc\x30\xc7\x30\xa3\x30\xaa\x30\xc7\x30\xd0\x30\xa4\x30\xb9\x30\x6e\x30\xcd\x30\xa4\x30\xc6\x30\xa3\x30\xd6\x30\x6a\x30\xaa\x30\xfc\x30\xc7\x30\xa3\x30\xaa\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\xb5\x30\xa4\x30\xba\x30\x20\x00\x3a\x00\x20\x00\x25\x00\x64\x00\x00"/*@ L"�I�[�f�B�I�f�o�C�X�̃l�C�e�B�u�ȃI�[�f�B�I�o�b�t�@�T�C�Y : %d" @*/, SoundSysData.PF.AudioManager_FramesPerBuffer )) ;

								SoundSysData.EnableSelfMixingFlag = TRUE ;
							}

							env->DeleteLocalRef( string_framesPerBuffer ) ;
							string_framesPerBuffer = NULL ;
						}

						env->DeleteLocalRef( string_sampleRate ) ;
						string_sampleRate = NULL ;
					}

					env->DeleteLocalRef( object_AudioManager ) ;
					object_AudioManager = NULL ;
				}

				// JavaVM �Ƃ��̃X���b�h�̊֘A�t���I��
				g_AndroidSys.NativeActivity->vm->DetachCurrentThread() ;
			}
		}

		pthread_mutex_unlock( &g_AndroidSys.NativeActivityMutex ) ;
	}

	// �X�g�b�v�T�E���h�o�b�t�@�p�̃N���e�B�J���Z�N�V������������
	if( CriticalSection_Initialize( &SoundSysData.PF.StopSoundBufferCriticalSection ) < 0 )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x5c\x50\x62\x6b\xe6\x51\x06\x74\x28\x75\x6e\x30\xaf\x30\xea\x30\xc6\x30\xa3\x30\xab\x30\xeb\x30\xbb\x30\xaf\x30\xb7\x30\xe7\x30\xf3\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenSL ES �̃T�E���h�o�b�t�@��~�����p�̃N���e�B�J���Z�N�V�����̍쐬�Ɏ��s���܂���\n" @*/ )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// �T�E���h�o�b�t�@�Đ��������p�̃N���e�B�J���Z�N�V������������
	if( CriticalSection_Initialize( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) < 0 )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x8d\x51\x1f\x75\xe6\x51\x06\x74\xc5\x60\x31\x58\x28\x75\x6e\x30\xaf\x30\xea\x30\xc6\x30\xa3\x30\xab\x30\xeb\x30\xbb\x30\xaf\x30\xb7\x30\xe7\x30\xf3\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenSL ES �̃T�E���h�o�b�t�@�Đ��������p�̃N���e�B�J���Z�N�V�����̍쐬�Ɏ��s���܂���\n" @*/ )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// �����f�[�^�̏�����
	for( i = 0 ; i < STREAM_SOUND_BUFFER_UNIT_SAPMLES ; i ++ )
	{
		g_NoneSound8bit[ i ]  = 128 ;
		g_NoneSound16bit[ i ] = 0 ;
	}
 
	// �G���W���I�u�W�F�N�g�쐬
	if( slCreateEngine( &SoundSysData.PF.EngineObject, 0, NULL, 0, NULL, NULL ) != SL_RESULT_SUCCESS )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xa8\x30\xf3\x30\xb8\x30\xf3\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenSL ES �̃G���W���I�u�W�F�N�g�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}
 
	// �G���W���I�u�W�F�N�g�̃��A���C�Y
    if( ( *SoundSysData.PF.EngineObject )->Realize( SoundSysData.PF.EngineObject, SL_BOOLEAN_FALSE ) != SL_RESULT_SUCCESS )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xa8\x30\xf3\x30\xb8\x30\xf3\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\xea\x30\xa2\x30\xe9\x30\xa4\x30\xba\x30\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenSL ES �̃G���W���I�u�W�F�N�g�̃��A���C�Y�Ɏ��s���܂���\n" @*/ )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// �G���W���I�u�W�F�N�g�̃C���^�[�t�F�[�X���擾
    if( ( *SoundSysData.PF.EngineObject )->GetInterface( SoundSysData.PF.EngineObject, SL_IID_ENGINE, &SoundSysData.PF.EngineInterface ) != SL_RESULT_SUCCESS )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xa8\x30\xf3\x30\xb8\x30\xf3\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xa4\x30\xb9\x30\xd6\x53\x97\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenSL ES �̃G���W���I�u�W�F�N�g�̃C���^�[�t�F�[�X�擾�Ɏ��s���܂���\n" @*/ )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// ���O�~�L�V���O���s���ꍇ�͂����ŏo�̓I�u�W�F�N�g�Ȃǂ��쐬����
	if( SoundSysData.EnableSelfMixingFlag )
	{
		// �T�E���h�o�͗p�o�b�t�@�̊m��
		SoundSysData.PF.SelfMixing_OutputBuffer = ( BYTE * )DXALLOC( 4 * SoundSysData.PF.AudioManager_FramesPerBuffer ) ;
		if( SoundSysData.PF.SelfMixing_OutputBuffer == NULL )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xfa\x51\x9b\x52\x28\x75\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�E���h�o�͗p�o�b�t�@�̊m�ۂɎ��s���܂���\n" @*/ )) ;
			DXST_LOGFILE_TABSUB ;
			return -1 ;
		}
		_MEMSET( SoundSysData.PF.SelfMixing_OutputBuffer, 0, 4 * SoundSysData.PF.AudioManager_FramesPerBuffer ) ;

		// �Đ��̏���
		if( SelfMixingPlayer_Setup() < 0 )
		{
			return -1 ;
		}
	}

	// ProcessStreamSoundMemAll �����ĂԃX���b�h�̊J�n
	{
		pthread_attr_t attr ;
		int returnCode ;

		pthread_attr_init( &attr ) ;
		pthread_attr_setstacksize( &attr, 128 * 1024 ) ;

		returnCode = pthread_create(
			&SoundSysData.PF.ProcessSoundThread,
			&attr,
			StreamSoundThreadFunction,
			NULL
		) ;
		if( returnCode != 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\x50\x00\x72\x00\x6f\x00\x63\x00\x65\x00\x73\x00\x73\x00\x53\x00\x74\x00\x72\x00\x65\x00\x61\x00\x6d\x00\x53\x00\x6f\x00\x75\x00\x6e\x00\x64\x00\x4d\x00\x65\x00\x6d\x00\x41\x00\x6c\x00\x6c\x00\x20\x00\x49\x7b\x92\x30\x7c\x54\x76\x30\xb9\x30\xec\x30\xc3\x30\xc9\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"ProcessStreamSoundMemAll �����ĂԃX���b�h�̍쐬�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, returnCode )) ;
			DXST_LOGFILE_TABSUB ;
			return -1 ;
		}
	}

	DXST_LOGFILE_TABSUB ;

	SoundSysData.PF.EngineObjectInitialize = TRUE ;

	DXST_LOGFILE_ADDUTF16LE( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\x1d\x52\x1f\x67\x16\x53\x8c\x5b\x86\x4e\x0a\x00\x00"/*@ L"OpenSL ES �̏���������\n" @*/ ) ;

	// �I��
	return 0 ;
}


// �T�E���h�V�X�e��������������֐��̊��ˑ��������s���֐�( ���s�ӏ���ʂP )
extern	int		InitializeSoundSystem_PF_Timing1( void )
{
#ifndef DX_NON_MULTITHREAD
	SoundSysData.PF.DXSoundProcessStart = TRUE ;
#endif // DX_NON_MULTITHREAD

	// �C�R���C�U�̏��̎擾
	if( SetupEqualizerInfo() < 0 )
	{
		// ���s�����ꍇ�̓C�R���C�U���g�p���Ȃ�
		SoundSysData.PF.UseEqualizer = FALSE ;
	}

	// ����I��
	return 0 ;
}




// �T�E���h�V�X�e���̌�n��������֐��̊��ˑ��������s���֐�( ���s�ӏ���ʂO )
extern	int		TerminateSoundSystem_PF_Timing0( void )
{
#ifndef DX_NON_MULTITHREAD
	SoundSysData.PF.DXSoundProcessStart = FALSE ;
#endif // DX_NON_MULTITHREAD

	// ProcessStreamSoundMemAll �����ĂԃX���b�h���I������
	SoundSysData.PF.ProcessSoundThreadEndRequest = TRUE ;
	pthread_join( SoundSysData.PF.ProcessSoundThread, NULL ) ;

	// ����I��
	return 0 ;
}


// �T�E���h�V�X�e���̌�n��������֐��̊��ˑ��������s���֐�( ���s�ӏ���ʂP )
extern	int		TerminateSoundSystem_PF_Timing1( void )
{
	SoundSysData.PF.EngineObjectInitialize = FALSE ;

	// �T�E���h�o�b�t�@�Đ��p���̌�n��
	{
		int i ;
		SOUNDBUFFERPLAYINFO *BufferPlayInfo ;

		// �N���e�B�J���Z�N�V�����̎擾
		CRITICALSECTION_LOCK( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

		BufferPlayInfo = SoundSysData.PF.SoundBufferPlayInfos ;
		for( i = 0 ; i < SOUNDBUFFERPLAYINFO_MAX_NUM ; i ++, BufferPlayInfo ++ )
		{
			if( BufferPlayInfo->SetupFlag )
			{
				TerminateSoundBufferPlayInfo( i ) ;
			}
		}

		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;
	}

	// ���O�~�L�V���O�̏ꍇ�͂����ōĐ��p�I�u�W�F�N�g�Ȃǂ����
	if( SoundSysData.EnableSelfMixingFlag )
	{
		SelfMixingPlayer_Terminate() ;

		if( SoundSysData.PF.SelfMixing_OutputBuffer != NULL )
		{
			DXFREE( SoundSysData.PF.SelfMixing_OutputBuffer ) ;
			SoundSysData.PF.SelfMixing_OutputBuffer = NULL ;
		}
	}

	// �G���W���I�u�W�F�N�g�̌�n��
    if( SoundSysData.PF.EngineObject )
	{
        ( *SoundSysData.PF.EngineObject )->Destroy( SoundSysData.PF.EngineObject ) ;
        SoundSysData.PF.EngineObject = NULL ;
    }

	// �C�R���C�U�[���̌�n�����s��
	TerminateEqualizerInfo() ;

	// �X�g�b�v�T�E���h�o�b�t�@�p�̃N���e�B�J���Z�N�V�������폜
	CriticalSection_Delete( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;

	// �T�E���h�o�b�t�@�Đ��������p�̃N���e�B�J���Z�N�V�������폜
	CriticalSection_Delete( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	// ����I��
	return 0 ;
}

// �T�E���h�V�X�e���Ŏ����I�ɍs�������p�̊֐��̊��ˑ��������s���֐�
extern	int		ProcessSoundSystem_PF( void )
{
	return 0 ;
}

// �T�E���h�V�X�e���̏������`�F�b�N�̊��ˑ��������s���֐�( TRUE:����������Ă���  FALSE:����������Ă��Ȃ� )
extern	int		CheckSoundSystem_Initialize_PF( void )
{
	return SoundSysData.PF.EngineObjectInitialize ;
}

// �T�E���h�V�X�e���̑��Đ����Ԃ��擾����
extern	int		GetSoundSystemTotalPlaySamples_PF( ULONGLONG *TotalPlaySamples, ULONGLONG *Frequency )
{
	if( SoundSysData.EnableSelfMixingFlag )
	{
		*TotalPlaySamples = SoundSysData.PF.SelfMixing_TotalPlaySampleCount ;
		*Frequency = SoundSysData.PF.AudioManager_SampleRate ;

		return 0 ;
	}

	return -1 ;
}

// �l�h�c�h�n���h���̌�n�����s���֐��̊��ˑ�����
extern	int		TerminateMidiHandle_PF( MIDIHANDLEDATA *MusicData )
{
	// ����I��
	return 0 ;
}

// �v���Z�b�g�̂R�c�T�E���h�p�̃��o�[�u�p�����[�^���擾���鏈���̊��ˑ��������s���֐�
extern	int		Get3DPresetReverbParamSoundMem_PF( SOUND3D_REVERB_PARAM *ParamBuffer, int PresetNo /* DX_REVERB_PRESET_DEFAULT �� */ )
{
	return 0 ;
}

// �R�c�T�E���h�̃��X�i�[�̈ʒu�ƃ��X�i�[�̑O���ʒu�ƃ��X�i�[�̏�����ʒu��ݒ肷�鏈���̊��ˑ��������s���֐�
extern int Set3DSoundListenerPosAndFrontPosAndUpVec_PF( VECTOR Position, VECTOR FrontPosition, VECTOR UpVector )
{
	return 0 ;
}

// �R�c�T�E���h�̃��X�i�[�̈ړ����x��ݒ肷�鏈���̊��ˑ��������s���֐�
extern int Set3DSoundListenerVelocity_PF( VECTOR Velocity )
{
	return 0 ;
}

// �R�c�T�E���h�̃��X�i�[�̉��p�x�͈͂�ݒ肷�鏈���̊��ˑ��������s���֐�
extern int Set3DSoundListenerConeAngle_PF( float InnerAngle, float OuterAngle )
{
	return 0 ;
}

// �R�c�T�E���h�̃��X�i�[�̉��p�x�͈͂̉��ʔ{����ݒ肷�鏈���̊��ˑ��������s���֐�
extern int Set3DSoundListenerConeVolume_PF( float InnerAngleVolume, float OuterAngleVolume )
{
	return 0 ;
}

// LoadMusicMemByMemImage �̎������֐��̊��ˑ��������s���֐�
extern int LoadMusicMemByMemImage_Static_PF( MIDIHANDLEDATA *MusicData, int ASyncThread )
{
	return 0 ;
}

// �ǂݍ��񂾂l�h�c�h�f�[�^�̉��t���J�n���鏈���̊��ˑ��������s���֐�
extern int PlayMusicMem_PF( MIDIHANDLEDATA *MusicData, int PlayType )
{
	return 0 ;
}

// �l�h�c�h�f�[�^�̉��t���~���鏈���̊��ˑ��������s��
extern int StopMusicMem_PF( MIDIHANDLEDATA *MusicData )
{
	return 0 ;
}

// �l�h�c�h�f�[�^�����t�����ǂ������擾����( TRUE:���t��  FALSE:��~�� )�����̊��ˑ��������s���֐�
extern int CheckMusicMem_PF( MIDIHANDLEDATA *MusicData )
{
	return 0 ;
}

// �l�h�c�h�f�[�^�̎����I�����̊��ˑ��������s���֐�
extern int ProcessMusicMem_PF( MIDIHANDLEDATA *MusicData )
{
	return 0 ;
}

// �l�h�c�h�f�[�^�̌��݂̍Đ��ʒu���擾���鏈���̊��ˑ��������s���֐�
extern int GetMusicMemPosition_PF( MIDIHANDLEDATA *MusicData )
{
	return 0 ;
}

// �l�h�c�h�̍Đ����ʂ��Z�b�g���鏈���̊��ˑ��������s���֐�
extern int SetVolumeMusic_PF( int Volume )
{
	return 0 ;
}

// �l�h�c�h�̌��݂̍Đ��ʒu���擾���鏈���̊��ˑ��������s���֐�
extern int GetMusicPosition_PF( void )
{
	return 0 ;
}









// �T�E���h�o�b�t�@�Đ��p���̌�n�����s��( �N���e�B�J���Z�N�V���������b�N������ԂŌĂԂ��� )
static void TerminateSoundBufferPlayInfo( int InfoIndex )
{
	SOUNDBUFFERPLAYINFO *BufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ InfoIndex ] ;

	if( InfoIndex < 0 || InfoIndex >= SOUNDBUFFERPLAYINFO_MAX_NUM )
	{
		return ;
	}

	if( BufferPlayInfo->SetupFlag == FALSE )
	{
		return ;
	}

	BufferPlayInfo->UseFlag = FALSE ;
	BufferPlayInfo->SetupFlag = FALSE ;
	SoundSysData.PF.SoundBufferPlayInfoSetupNum -- ;

	if( BufferPlayInfo->PlayerObject )
	{
		if( BufferPlayInfo->PlayerPlayInterface != NULL )
		{
			( *BufferPlayInfo->PlayerPlayInterface )->SetPlayState( BufferPlayInfo->PlayerPlayInterface, SL_PLAYSTATE_STOPPED ) ;
		}

		( *BufferPlayInfo->PlayerObject)->Destroy( BufferPlayInfo->PlayerObject ) ;
		BufferPlayInfo->PlayerObject = NULL ;
	}

	if( BufferPlayInfo->OutputMixObject != NULL )
	{
		( *BufferPlayInfo->OutputMixObject )->Destroy( BufferPlayInfo->OutputMixObject ) ;
		BufferPlayInfo->OutputMixObject = NULL ;
	}

	BufferPlayInfo->PlayerPlayInterface = NULL ;
	BufferPlayInfo->PlayerBufferQueueInterface = NULL ;
	BufferPlayInfo->PlayerVolumeInterface = NULL ;
	BufferPlayInfo->PlayerEqualizerInterface = NULL ;
}

// �w��̃T�E���h�o�b�t�@�Đ��p�����g�p���Ă��Ȃ���ԂɕύX����
static int NotUseSoundBufferPlayInfo( int InfoIndex )
{
	SOUNDBUFFERPLAYINFO *BufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ InfoIndex ] ;

	if( InfoIndex < 0 || InfoIndex >= SOUNDBUFFERPLAYINFO_MAX_NUM )
	{
		return -1 ;
	}

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	// ���Ɏg�p���Ă��Ȃ���ԂɂȂ��Ă����牽�������ɏI��
	if( BufferPlayInfo->UseFlag == FALSE )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;
		
		return 0 ;
	}

	// �g�p���Ă��Ȃ���ԂɕύX
	BufferPlayInfo->UseFlag = FALSE ;

	// �Đ����~
	if( BufferPlayInfo->PlayerObject &&
		BufferPlayInfo->PlayerPlayInterface != NULL )
	{
		( *BufferPlayInfo->PlayerPlayInterface )->SetPlayState( BufferPlayInfo->PlayerPlayInterface, SL_PLAYSTATE_STOPPED ) ;
	}

	// �o�b�t�@���N���A
	if(  BufferPlayInfo->PlayerBufferQueueInterface != NULL &&
		*BufferPlayInfo->PlayerBufferQueueInterface != NULL )
	{
		( *BufferPlayInfo->PlayerBufferQueueInterface )->Clear( BufferPlayInfo->PlayerBufferQueueInterface ) ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	// ����I��
	return 0 ;
}

// �T�E���h�o�b�t�@�Đ��p���̃Z�b�g�A�b�v�ƁA�Z�b�g�A�b�v�������̔ԍ����擾����
static int SetupSoundBufferPlayInfo( SOUNDBUFFER *Buffer )
{
	SOUNDBUFFERPLAYINFO						*BufferPlayInfo ;
	SLDataLocator_AndroidSimpleBufferQueue	LocBufq ;
	SLDataFormat_PCM						FormatPcm ;
	SLDataSource							AudioSrc ;
	SLDataLocator_OutputMix					LocOutmix ;
	SLDataSink								AudioDataSink ;
	SLresult								Result = 0 ;
	const SLInterfaceID						ids[ 4 ] = { SL_IID_PLAY,     SL_IID_BUFFERQUEUE, SL_IID_VOLUME,   SL_IID_EQUALIZER } ;
	const SLboolean							req[ 4 ] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,    SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE  } ;
	int i, j ;
	int NoUseIndex ;
	int NoSetupIndex ;
	int NewIndex ;
	int ErrorType = -1 ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	// �����t�H�[�}�b�g�Ŋ��g�p����Ă��Ȃ��Đ�����T��
	BufferPlayInfo = SoundSysData.PF.SoundBufferPlayInfos ;
	NoUseIndex = -1 ;
	NoSetupIndex = -1 ;
	j = 0 ;
	for( i = 0 ; i < SOUNDBUFFERPLAYINFO_MAX_NUM && j < SoundSysData.PF.SoundBufferPlayInfoSetupNum ; i ++, BufferPlayInfo ++ )
	{
		if( BufferPlayInfo->SetupFlag == FALSE )
		{
			// �Z�b�g�A�b�v����Ă��Ȃ��v�f��ۑ�
			if( NoSetupIndex == -1 )
			{
				NoSetupIndex = i ;
			}
			continue ;
		}

		j ++ ;

		if( BufferPlayInfo->UseFlag )
		{
			continue ;
		}

		// �g�p����Ă��Ȃ��v�f��ۑ�
		if( NoUseIndex == -1 )
		{
			NoUseIndex = i ;
		}

		if( Buffer != NULL &&
			BufferPlayInfo->Channels      == Buffer->Format.nChannels      &&
			BufferPlayInfo->BitsPerSample == Buffer->Format.wBitsPerSample &&
			BufferPlayInfo->SamplesPerSec == Buffer->Format.nSamplesPerSec )
		{
			// ����������g�p��Ԃɂ��ĕԂ�
			BufferPlayInfo->UseFlag = TRUE ;

			// �o�b�t�@�L���[�C���^�[�t�F�[�X�̃R�[���o�b�N�֐��̐ݒ�
			Result = ( *BufferPlayInfo->PlayerBufferQueueInterface )->RegisterCallback( BufferPlayInfo->PlayerBufferQueueInterface, PlayerBufferQueueCallback, Buffer ) ;
			if( Result != SL_RESULT_SUCCESS )
			{
				// �g�p��Ԃ�����
				BufferPlayInfo->UseFlag = FALSE ;

				// �N���e�B�J���Z�N�V�����̉��
				CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

				DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\xad\x30\xe5\x30\xfc\x30\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xfc\x30\xb9\x30\x6e\x30\xb3\x30\xfc\x30\xeb\x30\xd0\x30\xc3\x30\xaf\x30\xa2\x95\x70\x65\x6e\x30\x7b\x76\x32\x93\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃o�b�t�@�L���[�C���^�[�t�F�[�X�̃R�[���o�b�N�֐��̓o�^�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
				return -1 ;
			}

			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

			// �Ԃ�
			return i ;
		}
	}

	// �Z�b�g�A�b�v����Ă��Ȃ��v�f���������炻�����g�p����
	if( NoSetupIndex >= 0 )
	{
		NewIndex = NoSetupIndex ;
	}
	else
	// �Đ���񂪍ő吔�ɒB���Ă���ꍇ����
	if( SoundSysData.PF.SoundBufferPlayInfoSetupNum >= SOUNDBUFFERPLAYINFO_MAX_NUM )
	{
		// �g�p����Ă��Ȃ��v�f������������G���[
		if( NoUseIndex < 0 )
		{
			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

			DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xfa\x51\x9b\x52\xbb\x30\xc3\x30\xc8\x30\xa2\x30\xc3\x30\xd7\x30\xa8\x30\xe9\x30\xfc\x30\x01\x30\x8d\x51\x1f\x75\xc5\x60\x31\x58\x70\x65\x4c\x30\x00\x67\x27\x59\x70\x65\x20\x00\x25\x00\x64\x00\x20\x00\x6b\x30\x54\x90\x57\x30\x66\x30\x44\x30\x7e\x30\x59\x30\x0a\x00\x00"/*@ L"OpenSL ES �̃T�E���h�o�̓Z�b�g�A�b�v�G���[�A�Đ���񐔂��ő吔 %d �ɒB���Ă��܂�\n" @*/, BUFFERQUEUE_BUFFER_NUM )) ;
			return -1 ;
		}

		// �g�p����Ă��Ȃ��v�f���������ꍇ�͉���������s��
		TerminateSoundBufferPlayInfo( NoUseIndex ) ;

		// �g�p����o�b�t�@�̃A�h���X���Z�b�g
		NewIndex = NoUseIndex ;
	}
	else
	{
		// �ő吔�ɒB���Ă��Ȃ��ꍇ�͔z��̎g�p���ĂȂ��v�f�̃A�h���X���Z�b�g
		NewIndex = SoundSysData.PF.SoundBufferPlayInfoSetupNum ;
	}

SETUP :

	if( NewIndex < 0 || NewIndex >= SOUNDBUFFERPLAYINFO_MAX_NUM )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xfa\x51\x9b\x52\xbb\x30\xc3\x30\xc8\x30\xa2\x30\xc3\x30\xd7\x30\xa8\x30\xe9\x30\xfc\x30\x01\x30\x4e\x00\x65\x00\x77\x00\x49\x00\x6e\x00\x64\x00\x65\x00\x78\x00\x20\x00\x24\x50\x4c\x30\x0d\x4e\x63\x6b\x0a\x00\x00"/*@ L"OpenSL ES �̃T�E���h�o�̓Z�b�g�A�b�v�G���[�ANewIndex �l���s��\n" @*/ )) ;
		return -1 ;
	}

	// �ő吔�ɒB���Ă��Ȃ��Ă��A�G���[�������������ɒB���Ă�����G���[����
	if( SoundSysData.PF.SoundBufferPlayInfoSetupErrorNum != 0 &&
		SoundSysData.PF.SoundBufferPlayInfoSetupErrorNum <= SoundSysData.PF.SoundBufferPlayInfoSetupNum )
	{
		goto ERR ;
	}

	BufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ NewIndex ] ;

	// �t�H�[�}�b�g��ۑ�
	if( Buffer == NULL )
	{
		BufferPlayInfo->Channels      = 2 ;
		BufferPlayInfo->BitsPerSample = 16 ;
		BufferPlayInfo->SamplesPerSec = 44100 ;
	}
	else
	{
		BufferPlayInfo->Channels      = Buffer->Format.nChannels      ;
		BufferPlayInfo->BitsPerSample = Buffer->Format.wBitsPerSample ;
		BufferPlayInfo->SamplesPerSec = Buffer->Format.nSamplesPerSec ;
	}

	// �o�̓I�u�W�F�N�g�쐬
	Result = ( *SoundSysData.PF.EngineInterface )->CreateOutputMix( SoundSysData.PF.EngineInterface, &BufferPlayInfo->OutputMixObject, 0, NULL, NULL ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		ErrorType = 0 ;
		goto ERR ;
	}

	// �o�̓I�u�W�F�N�g�̃��A���C�Y
	Result = ( *BufferPlayInfo->OutputMixObject )->Realize( BufferPlayInfo->OutputMixObject, SL_BOOLEAN_FALSE ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		ErrorType = 1 ;
		goto ERR ;
	}

	FormatPcm.formatType	= SL_DATAFORMAT_PCM;
	FormatPcm.numChannels	= ( SLuint32 )BufferPlayInfo->Channels ;
	FormatPcm.samplesPerSec	= ( SLuint32 )BufferPlayInfo->SamplesPerSec * 1000 ;
	FormatPcm.bitsPerSample	= ( SLuint32 )BufferPlayInfo->BitsPerSample ;
	FormatPcm.containerSize	= ( SLuint32 )BufferPlayInfo->BitsPerSample ;
	FormatPcm.channelMask	= BufferPlayInfo->Channels == 1 ? SL_SPEAKER_FRONT_CENTER : ( SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT ) ;
	FormatPcm.endianness	= SL_BYTEORDER_LITTLEENDIAN ;

	LocBufq.locatorType		= SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE ;
	LocBufq.numBuffers		= BUFFERQUEUE_BUFFER_NUM ;
	AudioSrc.pLocator		= &LocBufq ;
	AudioSrc.pFormat		= &FormatPcm ;

	LocOutmix.locatorType	= SL_DATALOCATOR_OUTPUTMIX ;
	LocOutmix.outputMix		= BufferPlayInfo->OutputMixObject ;

	AudioDataSink.pLocator	= &LocOutmix ;
	AudioDataSink.pFormat	= NULL ;

	// �v���C���[�I�u�W�F�N�g�쐬
	Result = ( *SoundSysData.PF.EngineInterface )->CreateAudioPlayer(
		SoundSysData.PF.EngineInterface,
		&BufferPlayInfo->PlayerObject,
		&AudioSrc,
		&AudioDataSink,
		SoundSysData.PF.UseEqualizer ? 4 : 3,
		ids,
		req
	) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		ErrorType = 2 ;
		goto ERR ;
	}

	// �v���C���[�I�u�W�F�N�g�̃��A���C�Y
	Result = ( *BufferPlayInfo->PlayerObject )->Realize( BufferPlayInfo->PlayerObject, SL_BOOLEAN_FALSE ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		ErrorType = 3 ;
		goto ERR ;
	}

	// �Đ��C���^�[�t�F�[�X�̎擾
	Result = ( *BufferPlayInfo->PlayerObject )->GetInterface(BufferPlayInfo->PlayerObject, SL_IID_PLAY, &BufferPlayInfo->PlayerPlayInterface ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		ErrorType = 4 ;
		goto ERR ;
	}

	// �o�b�t�@�L���[�C���^�[�t�F�[�X�̎擾
	Result = ( *BufferPlayInfo->PlayerObject )->GetInterface(BufferPlayInfo->PlayerObject, SL_IID_BUFFERQUEUE, &BufferPlayInfo->PlayerBufferQueueInterface ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		ErrorType = 5 ;
		goto ERR ;
	}

	// ���ʃC���^�[�t�F�[�X�̎擾
	Result = ( *BufferPlayInfo->PlayerObject )->GetInterface(BufferPlayInfo->PlayerObject, SL_IID_VOLUME, &BufferPlayInfo->PlayerVolumeInterface ) ;
	if( Result != SL_RESULT_SUCCESS )
	{
		ErrorType = 6 ;
		goto ERR ;
	}

	// �C�R���C�U�[���g�p����ꍇ�̓C�R���C�U�[�C���^�[�t�F�[�X���擾����
	if( SoundSysData.PF.UseEqualizer )
	{
		// �C�R���C�U�C���^�[�t�F�[�X�̎擾
		Result = ( *BufferPlayInfo->PlayerObject )->GetInterface(BufferPlayInfo->PlayerObject, SL_IID_EQUALIZER, &BufferPlayInfo->PlayerEqualizerInterface ) ;
		if( Result != SL_RESULT_SUCCESS )
		{
			ErrorType = 7 ;
			goto ERR ;
		}

		// �C�R���C�U�[�̃Z�b�g�A�b�v���s��
		{
			// �C�R���C�U��L���ɂ���
			( *BufferPlayInfo->PlayerEqualizerInterface )->SetEnabled( BufferPlayInfo->PlayerEqualizerInterface, SL_BOOLEAN_TRUE ) ;

			// �v���Z�b�g�̎w��
			( *BufferPlayInfo->PlayerEqualizerInterface )->UsePreset( BufferPlayInfo->PlayerEqualizerInterface, SoundSysData.PF.EqualizerInfo.CurrentPresetIndex ) ;

			// �o���h�̐ݒ�
			for( i = 0 ; i < SoundSysData.PF.EqualizerInfo.BandNum ; i ++ )
			{
				( *BufferPlayInfo->PlayerEqualizerInterface )->SetBandLevel( BufferPlayInfo->PlayerEqualizerInterface, ( SLuint16 )i, ( SLmillibel )SoundSysData.PF.EqualizerInfo.BandInfo[ i ].Level ) ;
			}
		}
	}
	else
	{
		BufferPlayInfo->PlayerEqualizerInterface = NULL ;
	}

	// �o�b�t�@�L���[�C���^�[�t�F�[�X�̃R�[���o�b�N�֐��̐ݒ�
	if( Buffer != NULL )
	{
		Result = ( *BufferPlayInfo->PlayerBufferQueueInterface )->RegisterCallback( BufferPlayInfo->PlayerBufferQueueInterface, PlayerBufferQueueCallback, Buffer ) ;
		if( Result != SL_RESULT_SUCCESS )
		{
			ErrorType = 8 ;
			goto ERR ;
		}
	}

	// �Z�b�g�A�b�v������Ԃɂ���
	BufferPlayInfo->SetupFlag = TRUE ;
	SoundSysData.PF.SoundBufferPlayInfoSetupNum ++ ;

	// �g�p��Ԃɂ���
	BufferPlayInfo->UseFlag = TRUE ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	// ����I��
	return NewIndex ;


	// �G���[����
ERR :

	// �I�u�W�F�N�g�̌�n��
	{
		if( BufferPlayInfo->PlayerObject )
		{
			if( BufferPlayInfo->PlayerPlayInterface != NULL )
			{
				( *BufferPlayInfo->PlayerPlayInterface )->SetPlayState( BufferPlayInfo->PlayerPlayInterface, SL_PLAYSTATE_STOPPED ) ;
			}

			( *BufferPlayInfo->PlayerObject)->Destroy( BufferPlayInfo->PlayerObject ) ;
			BufferPlayInfo->PlayerObject = NULL ;
		}

		if( BufferPlayInfo->OutputMixObject != NULL )
		{
			( *BufferPlayInfo->OutputMixObject )->Destroy( BufferPlayInfo->OutputMixObject ) ;
			BufferPlayInfo->OutputMixObject = NULL ;
		}

		BufferPlayInfo->UseFlag = FALSE ;
		BufferPlayInfo->PlayerPlayInterface = NULL ;
		BufferPlayInfo->PlayerBufferQueueInterface = NULL ;
		BufferPlayInfo->PlayerVolumeInterface = NULL ;
		BufferPlayInfo->PlayerEqualizerInterface = NULL ;
	}

	// �Z�b�g�A�b�v����Ă��Ċ��g�p����Ă��Ȃ��v�f����������
	BufferPlayInfo = SoundSysData.PF.SoundBufferPlayInfos ;
	NoUseIndex = -1 ;
	j = 0 ;
	for( i = 0 ; i < SOUNDBUFFERPLAYINFO_MAX_NUM && j < SoundSysData.PF.SoundBufferPlayInfoSetupNum ; i ++, BufferPlayInfo ++ )
	{
		if( BufferPlayInfo->SetupFlag == FALSE )
		{
			continue ;
		}

		j ++ ;

		if( BufferPlayInfo->UseFlag == FALSE )
		{
			NoUseIndex = i ;
			break ;
		}
	}

	// �Z�b�g�A�b�v����Ă��Ċ��g�p����Ă��Ȃ��v�f�������ꍇ�̓G���[
	if( NoUseIndex == -1 )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

		// �O��G���[�����������ۂƃZ�b�g�A�b�v�ł��Ă���v�f�����قȂ�ꍇ�̂݃G���[���O���o��
		if( SoundSysData.PF.SoundBufferPlayInfoSetupErrorNum != 0 &&
			SoundSysData.PF.SoundBufferPlayInfoSetupErrorNum != SoundSysData.PF.SoundBufferPlayInfoSetupNum )
		{
			SoundSysData.PF.SoundBufferPlayInfoSetupErrorNum = SoundSysData.PF.SoundBufferPlayInfoSetupNum ;

			switch( ErrorType )
			{
			case 0 :
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xfa\x51\x9b\x52\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃T�E���h�o�̓I�u�W�F�N�g�̍쐬�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
				break ;

			case 1 :
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xfa\x51\x9b\x52\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\xea\x30\xa2\x30\xe9\x30\xa4\x30\xba\x30\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃T�E���h�o�̓I�u�W�F�N�g�̃��A���C�Y�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
				break ;

			case 2 :
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xd7\x30\xec\x30\xa4\x30\xe4\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃v���C���[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
				break ;

			case 3 :
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xd7\x30\xec\x30\xa4\x30\xe4\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\xea\x30\xa2\x30\xe9\x30\xa4\x30\xba\x30\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃v���C���[�I�u�W�F�N�g�̃��A���C�Y�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
				break ;

			case 4 :
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\x8d\x51\x1f\x75\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xfc\x30\xb9\x30\x6e\x30\xd6\x53\x97\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̍Đ��C���^�[�t�F�[�X�̎擾�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
				break ;

			case 5 :
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\xad\x30\xe5\x30\xfc\x30\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xfc\x30\xb9\x30\x6e\x30\xd6\x53\x97\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃o�b�t�@�L���[�C���^�[�t�F�[�X�̎擾�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
				break ;

			case 6 :
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xf3\x97\xcf\x91\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xfc\x30\xb9\x30\x6e\x30\xd6\x53\x97\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̉��ʃC���^�[�t�F�[�X�̎擾�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
				break ;

			case 7 :
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xa4\x30\xb3\x30\xe9\x30\xa4\x30\xb6\x30\xfc\x30\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xfc\x30\xb9\x30\x6e\x30\xd6\x53\x97\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃C�R���C�U�[�C���^�[�t�F�[�X�̎擾�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
				break ;

			case 8 :
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\xad\x30\xe5\x30\xfc\x30\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xfc\x30\xb9\x30\x6e\x30\xb3\x30\xfc\x30\xeb\x30\xd0\x30\xc3\x30\xaf\x30\xa2\x95\x70\x65\x6e\x30\x7b\x76\x32\x93\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃o�b�t�@�L���[�C���^�[�t�F�[�X�̃R�[���o�b�N�֐��̓o�^�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
				break ;
			}

			DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xfa\x51\x9b\x52\xbb\x30\xc3\x30\xc8\x30\xa2\x30\xc3\x30\xd7\x30\xa8\x30\xe9\x30\xfc\x30\x01\x30\xbb\x30\xc3\x30\xc8\x30\xa2\x30\xc3\x30\xd7\x30\x55\x30\x8c\x30\x66\x30\x44\x30\x66\x30\x14\x4e\x64\x30\x7f\x4f\x28\x75\x55\x30\x8c\x30\x66\x30\x44\x30\x6a\x30\x44\x30\x81\x89\x20\x7d\x4c\x30\x8b\x89\x64\x30\x4b\x30\x8a\x30\x7e\x30\x5b\x30\x93\x30\x67\x30\x57\x30\x5f\x30\x28\x00\x20\x00\x0c\x54\x42\x66\x8d\x51\x1f\x75\x70\x65\x1a\xff\x25\x00\x64\x00\x20\x00\x29\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃T�E���h�o�̓Z�b�g�A�b�v�G���[�A�Z�b�g�A�b�v����Ă��Ċ��g�p����Ă��Ȃ��v�f��������܂���ł���( �����Đ����F%d )\n" @*/, SoundSysData.PF.SoundBufferPlayInfoSetupNum )) ;
		}
		return -1 ;
	}

	// �Z�b�g�A�b�v����Ă��Ċ��g�p���Ă��Ȃ��v�f��������čă`�������W
	TerminateSoundBufferPlayInfo( NoUseIndex ) ;

	// �g�p����C���f�b�N�X�Ƃ��ăZ�b�g
	NewIndex = NoUseIndex ;

	goto SETUP ;
}

// ��ɏ��擾�p�ɍĐ������ς݂̏��̔ԍ����擾����( SoundBufferPlayInfosCriticalSection �̃��b�N������Ă���ĂԕK�v������ )
static int GetSoundBufferPlayInfo( int *ReleaseFlag )
{
	int PlayInfoIndex = -1 ;

	*ReleaseFlag = FALSE ;

	// �g�p���̏���T��
	if( SoundSysData.PF.SoundBufferPlayInfoSetupNum > 0 )
	{
		int i ;

		for( i = 0 ; i < SOUNDBUFFERPLAYINFO_MAX_NUM ; i ++ )
		{
			if( SoundSysData.PF.SoundBufferPlayInfos[ i ].SetupFlag )
			{
				PlayInfoIndex = i ;
				break ;
			}
		}
	}

	// �Đ����̃o�b�t�@�������ꍇ�͂����ōĐ��������s��
	if( PlayInfoIndex < 0 )
	{
		*ReleaseFlag = TRUE ;

		// �Đ��������s��
		PlayInfoIndex = SetupSoundBufferPlayInfo( NULL ) ;
	}

	// �l��Ԃ�
	return PlayInfoIndex ;
}

// �Đ��̏������s��
static int SoundBuffer_Play_Setup( SOUNDBUFFER *Buffer )
{
	// �Đ��������ł��Ă���ꍇ�͉������Ȃ�
	if( Buffer->PF.PlaySetupComp == TRUE )
	{
		return 0 ;
	}

	Buffer->PF.UseSoundBufferPlayInfoIndex = SetupSoundBufferPlayInfo( Buffer ) ;
	if( Buffer->PF.UseSoundBufferPlayInfoIndex < 0 )
	{
//		DXST_LOGFILE_ADDUTF16LE( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xfa\x51\x9b\x52\xbb\x30\xc3\x30\xc8\x30\xa2\x30\xc3\x30\xd7\x30\x4c\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenSL ES �̃T�E���h�o�̓Z�b�g�A�b�v�����s���܂���\n" @*/ ) ;
		return -1 ;
	}

	// �Đ���������
	Buffer->PF.PlaySetupComp = TRUE ;

	// ���ʂ̐ݒ�
	SoundBuffer_RefreshVolume_PF( Buffer ) ;

	// ����I��
	return 0 ;

//	SLDataLocator_AndroidSimpleBufferQueue	LocBufq ;
//	SLDataFormat_PCM						FormatPcm ;
//	SLDataSource							AudioSrc ;
//	SLDataLocator_OutputMix					LocOutmix ;
//	SLDataSink								AudioDataSink ;
//	SLresult								Result ;
//	const SLInterfaceID						ids[ 3 ] = { SL_IID_PLAY,     SL_IID_BUFFERQUEUE, SL_IID_VOLUME   } ;
//	const SLboolean							req[ 3 ] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,    SL_BOOLEAN_TRUE } ;
//
//	// �Đ��������ł��Ă���ꍇ�͉������Ȃ�
//	if( Buffer->PF.PlaySetupComp == TRUE )
//	{
//		return 0 ;
//	}
//
//	// �o�̓I�u�W�F�N�g�쐬
//	Result = ( *SoundSysData.PF.EngineInterface )->CreateOutputMix( SoundSysData.PF.EngineInterface, &Buffer->PF.OutputMixObject, 0, NULL, NULL ) ;
//	if( Result != SL_RESULT_SUCCESS )
//	{
//		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xfa\x51\x9b\x52\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃T�E���h�o�̓I�u�W�F�N�g�̍쐬�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
//		goto ERR ;
//	}
//
//	// �o�̓I�u�W�F�N�g�̃��A���C�Y
//	Result = ( *Buffer->PF.OutputMixObject )->Realize( Buffer->PF.OutputMixObject, SL_BOOLEAN_FALSE ) ;
//	if( Result != SL_RESULT_SUCCESS )
//	{
//		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xfa\x51\x9b\x52\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\xea\x30\xa2\x30\xe9\x30\xa4\x30\xba\x30\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃T�E���h�o�̓I�u�W�F�N�g�̃��A���C�Y�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
//		goto ERR ;
//	}
//
//	FormatPcm.formatType	= SL_DATAFORMAT_PCM;
//	FormatPcm.numChannels	= ( SLuint32 )Buffer->Format.nChannels ;
//	FormatPcm.samplesPerSec	= ( SLuint32 )Buffer->Format.nSamplesPerSec * 1000 ;
//	FormatPcm.bitsPerSample	= ( SLuint32 )Buffer->Format.wBitsPerSample ;
//	FormatPcm.containerSize	= ( SLuint32 )Buffer->Format.wBitsPerSample ;
//	FormatPcm.channelMask	= Buffer->Format.nChannels == 1 ? SL_SPEAKER_FRONT_CENTER : ( SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT ) ;
//	FormatPcm.endianness	= SL_BYTEORDER_LITTLEENDIAN ;
//
//	LocBufq.locatorType		= SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE ;
//	LocBufq.numBuffers		= BUFFERQUEUE_BUFFER_NUM ;
//	AudioSrc.pLocator		= &LocBufq ;
//	AudioSrc.pFormat		= &FormatPcm ;
//
//	LocOutmix.locatorType	= SL_DATALOCATOR_OUTPUTMIX ;
//	LocOutmix.outputMix		= Buffer->PF.OutputMixObject ;
//
//	AudioDataSink.pLocator	= &LocOutmix ;
//	AudioDataSink.pFormat	= NULL ;
//
//	// �v���C���[�I�u�W�F�N�g�쐬
//	Result = ( *SoundSysData.PF.EngineInterface )->CreateAudioPlayer(
//		SoundSysData.PF.EngineInterface,
//		&Buffer->PF.PlayerObject,
//		&AudioSrc,
//		&AudioDataSink,
//		3,
//		ids,
//		req
//	) ;
//	if( Result != SL_RESULT_SUCCESS )
//	{
//		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xd7\x30\xec\x30\xa4\x30\xe4\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃v���C���[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
//		goto ERR ;
//	}
//
//	// �v���C���[�I�u�W�F�N�g�̃��A���C�Y
//	Result = ( *Buffer->PF.PlayerObject )->Realize( Buffer->PF.PlayerObject, SL_BOOLEAN_FALSE ) ;
//	if( Result != SL_RESULT_SUCCESS )
//	{
//		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xd7\x30\xec\x30\xa4\x30\xe4\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\xea\x30\xa2\x30\xe9\x30\xa4\x30\xba\x30\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃v���C���[�I�u�W�F�N�g�̃��A���C�Y�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
//		goto ERR ;
//	}
//
//	// �Đ��C���^�[�t�F�[�X�̎擾
//	Result = ( *Buffer->PF.PlayerObject )->GetInterface(Buffer->PF.PlayerObject, SL_IID_PLAY, &Buffer->PF.PlayerPlayInterface ) ;
//	if( Result != SL_RESULT_SUCCESS )
//	{
//		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\x8d\x51\x1f\x75\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xfc\x30\xb9\x30\x6e\x30\xd6\x53\x97\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̍Đ��C���^�[�t�F�[�X�̎擾�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
//		goto ERR ;
//	}
//
//	// �o�b�t�@�L���[�C���^�[�t�F�[�X�̎擾
//	Result = ( *Buffer->PF.PlayerObject )->GetInterface(Buffer->PF.PlayerObject, SL_IID_BUFFERQUEUE, &Buffer->PF.PlayerBufferQueueInterface ) ;
//	if( Result != SL_RESULT_SUCCESS )
//	{
//		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\xad\x30\xe5\x30\xfc\x30\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xfc\x30\xb9\x30\x6e\x30\xd6\x53\x97\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃o�b�t�@�L���[�C���^�[�t�F�[�X�̎擾�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
//		goto ERR ;
//	}
//
//	// ���ʃC���^�[�t�F�[�X�̎擾
//	Result = ( *Buffer->PF.PlayerObject )->GetInterface(Buffer->PF.PlayerObject, SL_IID_VOLUME, &Buffer->PF.PlayerVolumeInterface ) ;
//	if( Result != SL_RESULT_SUCCESS )
//	{
//		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xf3\x97\xcf\x91\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xfc\x30\xb9\x30\x6e\x30\xd6\x53\x97\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̉��ʃC���^�[�t�F�[�X�̎擾�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
//		goto ERR ;
//	}
//
//	// �o�b�t�@�L���[�C���^�[�t�F�[�X�̃R�[���o�b�N�֐��̐ݒ�
//	Result = ( *Buffer->PF.PlayerBufferQueueInterface )->RegisterCallback( Buffer->PF.PlayerBufferQueueInterface, PlayerBufferQueueCallback, Buffer ) ;
//	if( Result != SL_RESULT_SUCCESS )
//	{
//		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x53\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x6e\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\xad\x30\xe5\x30\xfc\x30\xa4\x30\xf3\x30\xbf\x30\xfc\x30\xd5\x30\xa7\x30\xfc\x30\xb9\x30\x6e\x30\xb3\x30\xfc\x30\xeb\x30\xd0\x30\xc3\x30\xaf\x30\xa2\x95\x70\x65\x6e\x30\x7b\x76\x32\x93\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x20\x00\xa8\x30\xe9\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x3a\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x78\x00\x0a\x00\x00"/*@ L"OpenSL ES �̃o�b�t�@�L���[�C���^�[�t�F�[�X�̃R�[���o�b�N�֐��̓o�^�Ɏ��s���܂���  �G���[�R�[�h:0x%08x\n" @*/, Result )) ;
//		goto ERR ;
//	}
//
//	// �Đ���������
//	Buffer->PF.PlaySetupComp = TRUE ;
//
//	// ���ʂ̐ݒ�
//	SoundBuffer_RefreshVolume_PF( Buffer ) ;
//
//	// ����I��
//	return 0 ;
//
//	// �G���[����
//ERR :
//
//	if( Buffer->PF.PlayerObject )
//	{
//		if( Buffer->PF.PlayerPlayInterface != NULL )
//		{
//			( *Buffer->PF.PlayerPlayInterface )->SetPlayState( Buffer->PF.PlayerPlayInterface, SL_PLAYSTATE_STOPPED ) ;
//		}
//
//		( *Buffer->PF.PlayerObject)->Destroy( Buffer->PF.PlayerObject ) ;
//		Buffer->PF.PlayerObject = NULL ;
//	}
//
//	if( Buffer->PF.OutputMixObject != NULL )
//	{
//		( *Buffer->PF.OutputMixObject )->Destroy( Buffer->PF.OutputMixObject ) ;
//		Buffer->PF.OutputMixObject = NULL ;
//	}
//
//	Buffer->PF.PlayerPlayInterface = NULL ;
//	Buffer->PF.PlayerBufferQueueInterface = NULL ;
//	Buffer->PF.PlayerVolumeInterface = NULL ;
//	Buffer->PlayerEqualizerInterface = NULL ;
//
//	return -1 ;
}

// �Đ��̌�n�����s��
static int SoundBuffer_Play_Terminate( SOUNDBUFFER *Buffer )
{
	// �Đ�����������Ă��Ȃ���Ή��������ɏI��
	if( Buffer->PF.PlaySetupComp == FALSE )
	{
		return 0 ;
	}

	// �T�E���h�o�b�t�@�Đ��p�������g�p���Ă��Ȃ���ԂɕύX
	NotUseSoundBufferPlayInfo( Buffer->PF.UseSoundBufferPlayInfoIndex ) ;
	Buffer->PF.UseSoundBufferPlayInfoIndex = -1 ;

	// �Z�b�g�A�b�v����Ă��Ȃ���ԂɕύX
	Buffer->PF.PlaySetupComp = FALSE ;

	return 0 ;
}

extern int SoundBuffer_Initialize_Timing0_PF( SOUNDBUFFER *Buffer, DWORD Bytes, WAVEFORMATEX *Format, SOUNDBUFFER *Src, int Is3DSound )
{
	int InitializeCriticalSection = FALSE ;

	// �[��������
	_MEMSET( &Buffer->PF, 0, sizeof( Buffer->PF ) ) ;

	// �N���e�B�J���Z�N�V������������
	if( CriticalSection_Initialize( &Buffer->PF.CriticalSection ) < 0 )
	{
		goto ERR ;
	}
	InitializeCriticalSection = TRUE ;

	// �T�E���h�o�b�t�@�p�̃��������m��
	if( Src != NULL )
	{
		Buffer->SampleNum	= Src->SampleNum ;
		Buffer->Format		= Src->Format ;
		Buffer->Wave		= DuplicateWaveData( Src->Wave ) ;
	}
	else
	{
		Buffer->Format		= *Format ;
		Buffer->SampleNum	= ( int )( Bytes / Format->nBlockAlign ) ;
		Buffer->Wave		= AllocWaveData( ( int )Bytes, FALSE ) ;
	}
	if( Buffer->Wave == NULL )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�E���h�o�b�t�@�p�̃������̊m�ۂɎ��s���܂���\n" @*/ )) ;
		goto ERR ;
	}

	// ��Ɨp�o�b�t�@�p�̃��������m��
	{
		int i ;
		DWORD OneWorkBufferSize = STREAM_SOUND_BUFFER_UNIT_SAPMLES * Buffer->Format.wBitsPerSample * Buffer->Format.nChannels / 8 ;

		Buffer->PF.WorkBufferBase = DXALLOC( BUFFERQUEUE_BUFFER_NUM * OneWorkBufferSize ) ;
		if( Buffer->PF.WorkBufferBase == NULL )
		{
			DXST_LOGFILEFMT_ADDUTF16LE( ( "\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x6e\x30\x5c\x4f\x6d\x69\x28\x75\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�E���h�o�b�t�@�̍�Ɨp�������̊m�ۂɎ��s���܂���\n" @*/ ) ) ;
			goto ERR ;
		}

		for( i = 0 ; i < BUFFERQUEUE_BUFFER_NUM ; i ++ )
		{
			Buffer->PF.WorkBuffer[ i ] = ( BYTE * )Buffer->PF.WorkBufferBase + i * OneWorkBufferSize ;
		}
	}

	// ����I��
	return 0 ;

	// �G���[����
ERR :

	if( InitializeCriticalSection )
	{
		CriticalSection_Delete( &Buffer->PF.CriticalSection ) ;
	}

	return -1 ;
}

extern int SoundBuffer_Initialize_Timing1_PF( SOUNDBUFFER *Buffer, SOUNDBUFFER *Src, int Is3DSound )
{
	return 0 ;
}

extern int SoundBuffer_Terminate_PF( SOUNDBUFFER *Buffer )
{
	// �N���e�B�J���Z�N�V�����̍폜
	CriticalSection_Delete( &Buffer->PF.CriticalSection ) ;

	return 0 ;
}

extern int SoundBuffer_CheckEnable_PF( SOUNDBUFFER *Buffer )
{
	return TRUE ;
}

extern int SoundBuffer_Play_PF( SOUNDBUFFER *Buffer, int Loop )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &Buffer->PF.CriticalSection ) ;

	// ��~�҂��T�E���h�o�b�t�@���X�g����T�E���h�o�b�t�@���O��
	SoundBuffer_Sub_StopSoundBufferList( Buffer ) ;

	// �Đ�����������Ă��Ȃ�������
	if( Buffer->PF.PlaySetupComp == FALSE )
	{
		// �o�b�t�@�L���[�֌W�̏��̏�����
		Buffer->PF.EnqueueInfoNum = 0 ;
		Buffer->PF.BufferEndPlayEnqueueNum = 0 ;
		_MEMSET( Buffer->PF.WorkBufferUseFlag, 0, sizeof( Buffer->PF.WorkBufferUseFlag ) ) ;

		// �Đ�����
		if( SoundBuffer_Play_Setup( Buffer ) < 0 )
		{
			Buffer->State = FALSE ;

			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;
			return -1 ;
		}
	}

	Buffer->State = TRUE ;

	// �Đ����������������ꍇ�̂ݏ������s��
	if( Buffer->PF.PlaySetupComp )
	{
		// �o�b�t�@�L���[�ɃT�E���h�f�[�^��ǉ�����
		EnqueueSoundBuffer( Buffer ) ;

		// �Đ���ԂɕύX
		if( Buffer->PF.PlaySetupComp )
		{
			SOUNDBUFFERPLAYINFO *SoundBufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ Buffer->PF.UseSoundBufferPlayInfoIndex ] ;

			if( Buffer->PF.UseSoundBufferPlayInfoIndex < 0 || Buffer->PF.UseSoundBufferPlayInfoIndex >= SOUNDBUFFERPLAYINFO_MAX_NUM )
			{
				return -1 ;
			}

			( *SoundBufferPlayInfo->PlayerPlayInterface )->SetPlayState( SoundBufferPlayInfo->PlayerPlayInterface, SL_PLAYSTATE_PLAYING ) ;
		}
	}

	Buffer->StopTimeState = 1 ;
	Buffer->StopTime = 0 ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;

	return 0 ;
}

extern int SoundBuffer_Stop_PF(	SOUNDBUFFER *Buffer, int EffectStop )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &Buffer->PF.CriticalSection ) ;

	// �Đ�����������Ă���ꍇ�̂ݏ���
	if( Buffer->PF.PlaySetupComp )
	{
		SOUNDBUFFERPLAYINFO *SoundBufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ Buffer->PF.UseSoundBufferPlayInfoIndex ] ;

		if( Buffer->PF.UseSoundBufferPlayInfoIndex < 0 || Buffer->PF.UseSoundBufferPlayInfoIndex >= SOUNDBUFFERPLAYINFO_MAX_NUM )
		{
			return -1 ;
		}

	//	( *Buffer->PF.PlayerPlayInterface )->SetPlayState( Buffer->PF.PlayerPlayInterface, SL_PLAYSTATE_PAUSED ) ;
		( *SoundBufferPlayInfo->PlayerPlayInterface )->SetPlayState( SoundBufferPlayInfo->PlayerPlayInterface, SL_PLAYSTATE_STOPPED ) ;

		// �Đ������̌�n��
		SoundBuffer_Play_Terminate( Buffer ) ;

		// �o�b�t�@�L���[�֌W�̏��̏�����
		Buffer->PF.EnqueueInfoNum = 0 ;
		Buffer->PF.BufferEndPlayEnqueueNum = 0 ;
		_MEMSET( Buffer->PF.WorkBufferUseFlag, 0, sizeof( Buffer->PF.WorkBufferUseFlag ) ) ;
	}

	Buffer->State = FALSE ;

	// ��~�҂��T�E���h�o�b�t�@���X�g����T�E���h�o�b�t�@���O��
	SoundBuffer_Sub_StopSoundBufferList( Buffer ) ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;

	return 0 ;
}

extern int SoundBuffer_CheckPlay_PF( SOUNDBUFFER *Buffer )
{
	return Buffer->State ;
}

extern int SoundBuffer_Lock_PF( SOUNDBUFFER *Buffer, DWORD WritePos , DWORD WriteSize, void **LockPos1, DWORD *LockSize1, void **LockPos2, DWORD *LockSize2 )
{
	return 2 ;
}

extern int SoundBuffer_Unlock_PF( SOUNDBUFFER *Buffer, void *LockPos1, DWORD LockSize1, void *LockPos2, DWORD LockSize2 )
{
	DWORD i ;

	// �_�u���T�C�Y�̏ꍇ�̓X�e���I�f�[�^�ɂ���
	if( Buffer->Wave->DoubleSizeBuffer != NULL )
	{
		switch( Buffer->Format.wBitsPerSample )
		{
		case 8 :
			{
				BYTE *Src8bit ;
				WORD *Dest8bit ;
				DWORD SampleNum ;

				Src8bit = ( BYTE * )LockPos1 ;
				Dest8bit = ( WORD * )Buffer->Wave->DoubleSizeBuffer + ( ( BYTE * )LockPos1 - ( BYTE * )Buffer->Wave->Buffer ) ;
				SampleNum = LockSize1 ;
				for( i = 0 ; i < SampleNum ; i ++ )
				{
					Dest8bit[ i ] = ( WORD )( Src8bit[ i ] + ( Src8bit[ i ] << 8 ) ) ;
				}

				Src8bit = ( BYTE * )LockPos2 ;
				Dest8bit = ( WORD * )Buffer->Wave->DoubleSizeBuffer + ( ( BYTE * )LockPos2 - ( BYTE * )Buffer->Wave->Buffer ) ;
				SampleNum = LockSize2 ;
				for( i = 0 ; i < SampleNum ; i ++ )
				{
					Dest8bit[ i ] = ( WORD )( Src8bit[ i ] + ( Src8bit[ i ] << 8 ) ) ;
				}
			}
			break ;

		case 16 :
			{
				WORD *Src16bit ;
				DWORD *Dest16bit ;
				DWORD SampleNum ;

				Src16bit = ( WORD * )LockPos1 ;
				Dest16bit = ( DWORD * )Buffer->Wave->DoubleSizeBuffer + ( ( WORD * )LockPos1 - ( WORD * )Buffer->Wave->Buffer ) ;
				SampleNum = LockSize1 / 2 ;
				for( i = 0 ; i < SampleNum ; i ++ )
				{
					Dest16bit[ i ] = ( DWORD )( Src16bit[ i ] + ( Src16bit[ i ] << 16 ) ) ;
				}

				Src16bit = ( WORD * )LockPos2 ;
				Dest16bit = ( DWORD * )Buffer->Wave->DoubleSizeBuffer + ( ( WORD * )LockPos2 - ( WORD * )Buffer->Wave->Buffer ) ;
				SampleNum = LockSize2 / 2 ;
				for( i = 0 ; i < SampleNum ; i ++ )
				{
					Dest16bit[ i ] = ( DWORD )( Src16bit[ i ] + ( Src16bit[ i ] << 16 ) ) ;
				}
			}
			break ;
		}
	}

	return 0 ;
}

extern int SoundBuffer_SetFrequency_PF( SOUNDBUFFER *Buffer, DWORD Frequency )
{
	return 0 ;
}

extern int SoundBuffer_GetFrequency_PF( SOUNDBUFFER *Buffer, LPDWORD Frequency )
{
	return 2 ;
}

extern int SoundBuffer_RefreshVolume_PF( SOUNDBUFFER *Buffer )
{
	LONG CalcVolume[ 2 ] ;
	LONG TempVolume[ 2 ] ;
	LONG Volume ;
	LONG Pan ;

	TempVolume[ 0 ] = Buffer->Volume[ 0 ] ;
	if( Buffer->Format.nChannels == 1 )
	{
		TempVolume[ 1 ] = Buffer->Volume[ 0 ] ;
	}
	else
	{
		TempVolume[ 1 ] = Buffer->Volume[ 1 ] ;
	}

	if( Buffer->Pan < 0 )
	{
		CalcVolume[ 0 ] = 10000 ;
		CalcVolume[ 1 ] = 10000 + Buffer->Pan ;
	}
	else
	{
		CalcVolume[ 0 ] = 10000 - Buffer->Pan ;
		CalcVolume[ 1 ] = 10000 ;
	}

	if( TempVolume[ 0 ] > 0 )
	{
		TempVolume[ 0 ] = 0 ;
	}
	else
	if( TempVolume[ 0 ] < -10000 )
	{
		TempVolume[ 0 ] = -10000 ;
	}
	if( TempVolume[ 1 ] > 0 )
	{
		TempVolume[ 1 ] = 0 ;
	}
	else
	if( TempVolume[ 1 ] < -10000 )
	{
		TempVolume[ 1 ] = -10000 ;
	}

	CalcVolume[ 0 ] = CalcVolume[ 0 ] * ( TempVolume[ 0 ] + 10000 ) / 10000 ;
	CalcVolume[ 1 ] = CalcVolume[ 1 ] * ( TempVolume[ 0 ] + 10000 ) / 10000 ;

	if( CalcVolume[ 0 ] > CalcVolume[ 1 ] )
	{
		Volume = CalcVolume[ 0 ] - 10000 ;
		Pan =    _FTOL( CalcVolume[ 1 ] * ( 10000.0f / CalcVolume[ 0 ] ) ) - 10000 ;
	}
	else
	if( CalcVolume[ 0 ] < CalcVolume[ 1 ] )
	{
		Volume = CalcVolume[ 1 ] - 10000 ;
		Pan = -( _FTOL( CalcVolume[ 0 ] * ( 10000.0f / CalcVolume[ 1 ] ) ) - 10000 ) ;
	}
	else
	{
		Volume = CalcVolume[ 0 ] - 10000 ;
		Pan = 0 ;
	}

	// �Đ����������������ꍇ�̂ݏ������s��
	if( Buffer->PF.PlaySetupComp )
	{
		SOUNDBUFFERPLAYINFO *SoundBufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ Buffer->PF.UseSoundBufferPlayInfoIndex ] ;

		if( Buffer->PF.UseSoundBufferPlayInfoIndex < 0 || Buffer->PF.UseSoundBufferPlayInfoIndex >= SOUNDBUFFERPLAYINFO_MAX_NUM )
		{
			return -1 ;
		}

		if( CalcVolume[ 0 ] == CalcVolume[ 1 ] )
		{
			( *SoundBufferPlayInfo->PlayerVolumeInterface )->EnableStereoPosition( SoundBufferPlayInfo->PlayerVolumeInterface, SL_BOOLEAN_FALSE ) ;
			( *SoundBufferPlayInfo->PlayerVolumeInterface )->SetStereoPosition( SoundBufferPlayInfo->PlayerVolumeInterface, 0 ) ;
		}
		else
		{
			( *SoundBufferPlayInfo->PlayerVolumeInterface )->EnableStereoPosition( SoundBufferPlayInfo->PlayerVolumeInterface, SL_BOOLEAN_TRUE ) ;
			( *SoundBufferPlayInfo->PlayerVolumeInterface )->SetStereoPosition( SoundBufferPlayInfo->PlayerVolumeInterface, ( SLmillibel )( Pan * 0x7fff / 10000 ) ) ;
		}
	
//		( *SoundBufferPlayInfo->PlayerVolumeInterface )->SetVolumeLevel( SoundBufferPlayInfo->PlayerVolumeInterface, ( SLmillibel )( Volume * 0x7fff / 10000 ) ) ;
		( *SoundBufferPlayInfo->PlayerVolumeInterface )->SetVolumeLevel( SoundBufferPlayInfo->PlayerVolumeInterface, ( SLmillibel )( Volume ) ) ;
	}

	return 0 ;
}

extern int SoundBuffer_GetCurrentPosition_PF(	SOUNDBUFFER *Buffer, LPDWORD PlayPos, LPDWORD WritePos )
{
//	SLAndroidSimpleBufferQueueState BufferQueState ;
//
//	// �N���e�B�J���Z�N�V�����̎擾
//	CRITICALSECTION_LOCK( &Buffer->PF.CriticalSection ) ;
//
//	// �Đ����������������ꍇ�̂ݏ������s��
//	if( Buffer->PF.PlaySetupComp )
//	{
//		if( ( *Buffer->PF.PlayerBufferQueueInterface )->GetState( Buffer->PF.PlayerBufferQueueInterface, &BufferQueState ) == SL_RESULT_SUCCESS )
//		{
//			// �Đ��ʒu�̍X�V
//			RefreshSoundBufferCurrentTime( Buffer, BufferQueState, FALSE ) ;
//		}
//	}
//
//	// �N���e�B�J���Z�N�V�����̉��
//	CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;

	return 2 ;
}

extern int SoundBuffer_SetCurrentPosition_PF( SOUNDBUFFER *Buffer, DWORD NewPos )
{
	int OldState = Buffer->State ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &Buffer->PF.CriticalSection ) ;

	if( OldState == TRUE )
	{
		SoundBuffer_Stop( Buffer ) ;
	}

	// �Đ����������������ꍇ�̂ݏ������s��
	if( Buffer->PF.PlaySetupComp )
	{
		SOUNDBUFFERPLAYINFO *SoundBufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ Buffer->PF.UseSoundBufferPlayInfoIndex ] ;

		if( Buffer->PF.UseSoundBufferPlayInfoIndex < 0 || Buffer->PF.UseSoundBufferPlayInfoIndex >= SOUNDBUFFERPLAYINFO_MAX_NUM )
		{
			return -1 ;
		}

		// �o�b�t�@�L���[�̃T�E���h�f�[�^���N���A����
		( *SoundBufferPlayInfo->PlayerBufferQueueInterface )->Clear( SoundBufferPlayInfo->PlayerBufferQueueInterface ) ;
	}

	Buffer->PlayPos  = ( int )( NewPos / Buffer->Format.nBlockAlign ) ;
	Buffer->CompPos  = Buffer->PlayPos ;
	Buffer->CompPosF = _FTOL( Buffer->CompPos ) ;
	if( Buffer->Frequency < 0 || Buffer->Frequency == Buffer->Format.nSamplesPerSec )
	{
		Buffer->EnableComPosF = FALSE ;
	}

	Buffer->PF.EnqueueInfoNum = 0 ;
	Buffer->PF.BufferEndPlayEnqueueNum = 0 ;
	_MEMSET( Buffer->PF.WorkBufferUseFlag, 0, sizeof( Buffer->PF.WorkBufferUseFlag ) ) ;

	if( OldState == TRUE )
	{
		SoundBuffer_Play( Buffer, Buffer->Loop ) ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;

	return 0 ;
}

extern int SoundBuffer_CycleProcess_PF( SOUNDBUFFER *Buffer )
{
	return -1 ;
}

extern int SoundBuffer_Set3DPosition_PF( SOUNDBUFFER *Buffer, VECTOR *Position )
{
	return 0 ;
}

extern int SoundBuffer_Set3DRadius_PF( SOUNDBUFFER *Buffer, float Radius )
{
	return 0 ;
}

extern int SoundBuffer_Set3DInnerRadius_PF(	SOUNDBUFFER *Buffer, float Radius )
{
	return 0 ;
}

extern int SoundBuffer_Set3DVelocity_PF( SOUNDBUFFER *Buffer, VECTOR *Velocity )
{
	return 0 ;
}

extern int SoundBuffer_Set3DFrontPosition_PF( SOUNDBUFFER *Buffer, VECTOR *FrontPosition, VECTOR *UpVector )
{
	return 0 ;
}

extern int SoundBuffer_Set3DConeAngle_PF( SOUNDBUFFER *Buffer, float InnerAngle, float OuterAngle )
{
	return 0 ;
}

extern int SoundBuffer_Set3DConeVolume_PF( SOUNDBUFFER *Buffer, float InnerAngleVolume, float OuterAngleVolume )
{
	return 0 ;
}

extern int SoundBuffer_Refresh3DSoundParam_PF(	SOUNDBUFFER *Buffer, int AlwaysFlag )
{
	// �I��
	return 0 ;
}

extern int SoundBuffer_SetReverbParam_PF( SOUNDBUFFER *Buffer, SOUND3D_REVERB_PARAM *Param )
{
	return 0 ;
}

extern int SoundBuffer_SetPresetReverbParam_PF( SOUNDBUFFER *Buffer, int PresetNo )
{
	return 0 ;
}





















// �l�h�c�h���t�I�����Ă΂��R�[���o�b�N�֐�
extern int MidiCallBackProcess( void )
{
	return 0 ;
}

















// ���ɍ쐬����T�E���h�n���h���ŃC�R���C�U�[�@�\���g�p���邩�ǂ�����ݒ肷��
// UseFlag  TRUE:�g�p����  FALSE:�g�p���Ȃ�
extern int SetUseEqualizer( int UseFlag )
{
	// �������ς݂̏ꍇ�̓G���[
	if( SoundSysData.InitializeFlag != FALSE )
	{
		return -1 ;
	}

	// �t���O��ۑ�
	SoundSysData.PF.UseEqualizer = UseFlag ;

	// �I��
	return 0 ;
}




// �C�R���C�U�[�֌W�֐�

// �C�R���C�U�[�̗^����ꂽ���g���ɍł��e����^������g���ш���擾���܂�( �߂�l�@-1:�G���[  0�ȏ�F���g���ш�C���f�b�N�X )
extern int SearchEqualizerBandIndex( int Frequency )
{
	int ReleaseFlag ;
	int PlayInfoIndex ;
	int Result = -1 ;
	SOUNDBUFFERPLAYINFO *BufferPlayInfo ;
	SLuint16 uint16Value ;

	if( CheckSoundSystem_Initialize_PF() == FALSE )
	{
		return -1 ;
	}

	// �C�R���C�U���g�p���Ă��Ȃ��ꍇ�̓G���[
	if( SoundSysData.PF.UseEqualizer == FALSE )
	{
		return -1 ;
	}

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	// �Đ������擾
	PlayInfoIndex = GetSoundBufferPlayInfo( &ReleaseFlag ) ;
	if( PlayInfoIndex < 0 )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

		// �G���[
		return -1 ;
	}
	BufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ PlayInfoIndex ] ;

	( *BufferPlayInfo->PlayerEqualizerInterface )->GetBand( BufferPlayInfo->PlayerEqualizerInterface, ( SLmilliHertz )( Frequency * 1000 ), &uint16Value ) ;
	Result = ( int )uint16Value ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	// �l��Ԃ�
	return Result ;
}

// �C�R���C�U�[�Ɏw��ł�����g���ш�̐����擾����
extern int GetEqualizerBandNum( void )
{
	if( CheckSoundSystem_Initialize_PF() == FALSE )
	{
		return -1 ;
	}

	if( SoundSysData.PF.UseEqualizer == FALSE )
	{
		return -1 ;
	}

	return SoundSysData.PF.EqualizerInfo.BandNum ;
}

// �^����ꂽ�C�R���C�U�[�̎��g���ш��^����ꂽ�Q�C���l�ɐݒ肵�܂�
extern int SetEqualizerBandLevel( int BandIndex, int Level )
{
	if( CheckSoundSystem_Initialize_PF() == FALSE )
	{
		return -1 ;
	}

	if( SoundSysData.PF.UseEqualizer == FALSE )
	{
		return -1 ;
	}

	if( BandIndex < 0 || BandIndex >= SoundSysData.PF.EqualizerInfo.BandNum )
	{
		return -1 ;
	}

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	// ���x���̃Z�b�g
	SoundSysData.PF.EqualizerInfo.BandInfo[ BandIndex ].Level = Level ;

	// �Đ��������������Ă���S�Ă̍Đ����ɔ��f����
	{
		int i ;
		int j ;
		SOUNDBUFFERPLAYINFO *BufferPlayInfo ;

		j = 0 ;
		BufferPlayInfo = SoundSysData.PF.SoundBufferPlayInfos ;
		for( i = 0 ; i < SOUNDBUFFERPLAYINFO_MAX_NUM && j < SoundSysData.PF.SoundBufferPlayInfoSetupNum ; i ++, BufferPlayInfo ++ )
		{
			if( BufferPlayInfo->SetupFlag == FALSE )
			{
				continue ;
			}

			j++ ;

			( *BufferPlayInfo->PlayerEqualizerInterface )->SetBandLevel( BufferPlayInfo->PlayerEqualizerInterface, ( SLuint16 )BandIndex, ( SLmillibel )SoundSysData.PF.EqualizerInfo.BandInfo[ BandIndex ].Level ) ;
		}
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	// ����I��
	return 0 ;
}

// �C�R���C�U�[�̎w�肳�ꂽ���g�����̃Q�C���l���擾���܂�
extern int GetEqualizerBandLevel( int BandIndex )
{
	if( CheckSoundSystem_Initialize_PF() == FALSE )
	{
		return -1 ;
	}

	if( SoundSysData.PF.UseEqualizer == FALSE )
	{
		return -1 ;
	}

	if( BandIndex < 0 || BandIndex >= SoundSysData.PF.EqualizerInfo.BandNum )
	{
		return -1 ;
	}

	return SoundSysData.PF.EqualizerInfo.BandInfo[ BandIndex ].Level ;
}

// �C�R���C�U�[�̎w�肳�ꂽ���g���ш�̎��g���͈͂��擾���܂�( pMin �� pMax �ɍŏ����g���ƍő���g�����i�[����܂�( �P�ʁF�w���c ) )
extern int GetEqualizerBandFreqRange( int BandIndex, int *pMin, int *pMax )
{
	if( CheckSoundSystem_Initialize_PF() == FALSE )
	{
		return -1 ;
	}

	if( SoundSysData.PF.UseEqualizer == FALSE )
	{
		return -1 ;
	}

	if( BandIndex < 0 || BandIndex >= SoundSysData.PF.EqualizerInfo.BandNum )
	{
		return -1 ;
	}

	if( pMin ) *pMin = ( int )SoundSysData.PF.EqualizerInfo.BandInfo[ BandIndex ].FrequencyMin / 1000 ;
	if( pMax ) *pMax = ( int )SoundSysData.PF.EqualizerInfo.BandInfo[ BandIndex ].FrequencyMax / 1000 ;

	// ����I��
	return 0 ;
}

// �C�R���C�U�[�̎w�肳�ꂽ���g���ш�̒��S���g�����擾���܂�( �߂�l�@���S���g��( �P�ʁF�w���c ) )
extern int GetEqualizerBandCenterFreq( int BandIndex )
{
	if( CheckSoundSystem_Initialize_PF() == FALSE )
	{
		return -1 ;
	}

	if( SoundSysData.PF.UseEqualizer == FALSE )
	{
		return -1 ;
	}

	if( BandIndex < 0 || BandIndex >= SoundSysData.PF.EqualizerInfo.BandNum )
	{
		return -1 ;
	}

	return ( int )SoundSysData.PF.EqualizerInfo.BandInfo[ BandIndex ].CenterFrequency / 1000 ;
}

// �C�R���C�U�[�̌��݂̃v���Z�b�g���擾���܂�( �߂�l�@�v���Z�b�g�ԍ� )
extern int GetEqualizerCurrentPreset( void )
{
	if( CheckSoundSystem_Initialize_PF() == FALSE )
	{
		return -1 ;
	}

	if( SoundSysData.PF.UseEqualizer == FALSE )
	{
		return -1 ;
	}

	return ( int )SoundSysData.PF.EqualizerInfo.CurrentPresetIndex ;
}

// �C�R���C�U�[�̃v���Z�b�g�����擾���܂�( �߂�l�@�v���Z�b�g���̕����񂪊i�[���ꂽ�������̈�̐擪�A�h���X )
extern const TCHAR *GetEqualizerPresetName( int PresetIndex )
{
	if( CheckSoundSystem_Initialize_PF() == FALSE )
	{
		return NULL ;
	}

	if( SoundSysData.PF.UseEqualizer == FALSE )
	{
		return NULL ;
	}

	if( PresetIndex < 0 || PresetIndex >= SoundSysData.PF.EqualizerInfo.PresetNum )
	{
		return NULL ;
	}

	return SoundSysData.PF.EqualizerInfo.PresetInfo[ PresetIndex ].Name ;
}

// �C�R���C�U�[�̃v���Z�b�g�̐����擾���܂�( �߂�l�@�v���Z�b�g�̐� )
extern int GetEqualizerPresetNum( void )
{
	if( CheckSoundSystem_Initialize_PF() == FALSE )
	{
		return -1 ;
	}

	if( SoundSysData.PF.UseEqualizer == FALSE )
	{
		return -1 ;
	}

	return SoundSysData.PF.EqualizerInfo.PresetNum ;
}

// �w�肵���v���Z�b�g�ɏ]���ăC�R���C�U�[��ݒ肵�܂�
extern int SetUseEqualizerPreset( int PresetIndex )
{
	SOUNDBUFFERPLAYINFO *BufferPlayInfo ;
	int SetupInfoFlag = FALSE ;
	int PlayInfoIndex ;
	int ReleaseFlag ;

	if( CheckSoundSystem_Initialize_PF() == FALSE )
	{
		return -1 ;
	}

	if( SoundSysData.PF.UseEqualizer == FALSE )
	{
		return -1 ;
	}

	if( PresetIndex < 0 || PresetIndex >= SoundSysData.PF.EqualizerInfo.PresetNum )
	{
		return -1 ;
	}

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	// �Đ��������������Ă���Đ����̃v���Z�b�g��ύX
	{
		int i ;
		int j ;

		j = 0 ;
		BufferPlayInfo = SoundSysData.PF.SoundBufferPlayInfos ;
		for( i = 0 ; i < SOUNDBUFFERPLAYINFO_MAX_NUM && j < SoundSysData.PF.SoundBufferPlayInfoSetupNum ; i ++, BufferPlayInfo ++ )
		{
			if( BufferPlayInfo->SetupFlag == FALSE )
			{
				continue ;
			}

			j++ ;

			( *BufferPlayInfo->PlayerEqualizerInterface )->UsePreset( BufferPlayInfo->PlayerEqualizerInterface, ( SLuint16 )PresetIndex ) ;

			// ���̃Z�b�g�A�b�v���܂��������炱���ŃZ�b�g�A�b�v���s��
			if( SetupInfoFlag == FALSE )
			{
				SetupInfoFlag = TRUE ;

				SetupEqualizerInfo( i ) ;
			}
		}
	}

	// �Đ��������������Ă���Đ���񂪂ЂƂ����������ꍇ�͂����ōĐ��������s��
	if( SetupInfoFlag == FALSE )
	{
		// �Đ��������������Ă���Đ������擾
		PlayInfoIndex = GetSoundBufferPlayInfo( &ReleaseFlag ) ;
		if( PlayInfoIndex < 0 )
		{
			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

			// �G���[
			return -1 ;
		}

		// �g�p����v���Z�b�g�̕ύX
		BufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ PlayInfoIndex ] ;
		( *BufferPlayInfo->PlayerEqualizerInterface )->UsePreset( BufferPlayInfo->PlayerEqualizerInterface, ( SLuint16 )PresetIndex ) ;

		// ���̃Z�b�g�A�b�v
		SetupEqualizerInfo( PlayInfoIndex ) ;

		// �Đ�����������
		if( ReleaseFlag )
		{
			NotUseSoundBufferPlayInfo( PlayInfoIndex ) ;
		}
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

	return 0 ;
}







// �C�R���C�U�[���̃Z�b�g�A�b�v���s��
static int SetupEqualizerInfo( int PlayInfoIndex )
{
	// �C�R���C�U���g�p����ꍇ�͂����ŏ��̎擾���s��
	if( SoundSysData.PF.UseEqualizer )
	{
		int ReleaseFlag = FALSE ;
		SOUNDBUFFERPLAYINFO *BufferPlayInfo ;

		// �N���e�B�J���Z�N�V�����̎擾
		CRITICALSECTION_LOCK( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

		// �C�R���C�U�[���̌�n�����s��
		TerminateEqualizerInfo() ;

		// �Đ����̎w�肪�����ꍇ�͍Đ����������ɍs���Ă���o�b�t�@��T��
		if( PlayInfoIndex < 0 )
		{
			PlayInfoIndex = GetSoundBufferPlayInfo( &ReleaseFlag ) ;
		}

		// �L���ȍĐ��o�b�t�@��������Ȃ�������G���[
		if( PlayInfoIndex < 0 )
		{
			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

			// �G���[
			return -1 ;
		}
		else
		{
			SLuint16 uint16value ;
			SLmillibel millibelValue1, millibelValue2 ;
			SLmilliHertz milliHertzValue1, milliHertzValue2 ;
			const SLchar *charP ;
			int i ;

			BufferPlayInfo = &SoundSysData.PF.SoundBufferPlayInfos[ PlayInfoIndex ] ;

			// �o���h�̐����擾
			( *BufferPlayInfo->PlayerEqualizerInterface )->GetNumberOfBands( BufferPlayInfo->PlayerEqualizerInterface, &uint16value ) ;
			SoundSysData.PF.EqualizerInfo.BandNum = ( int )uint16value ;

			// �o���h�����̃��������m��
			SoundSysData.PF.EqualizerInfo.BandInfo = ( EQUALIZER_BAND_INFO * )DXALLOC( sizeof( EQUALIZER_BAND_INFO ) * SoundSysData.PF.EqualizerInfo.BandNum ) ;
			if( SoundSysData.PF.EqualizerInfo.BandInfo == NULL )
			{
				// �N���e�B�J���Z�N�V�����̉��
				CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

				DXST_LOGFILEFMT_ADDUTF16LE(( "\xa4\x30\xb3\x30\xe9\x30\xa4\x30\xb6\x30\xfc\x30\x6e\x30\xd0\x30\xf3\x30\xc9\x30\xc5\x60\x31\x58\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�C�R���C�U�[�̃o���h���p�̃������̊m�ۂɎ��s���܂���\n" @*/ )) ;
				return -1 ;
			}

			// �o���h�����擾
			( *BufferPlayInfo->PlayerEqualizerInterface )->GetBandLevelRange( BufferPlayInfo->PlayerEqualizerInterface, &millibelValue1, &millibelValue2 ) ;
			SoundSysData.PF.EqualizerInfo.BandLevelRangeMin = ( int )millibelValue1 ;
			SoundSysData.PF.EqualizerInfo.BandLevelRangeMax = ( int )millibelValue2 ;
			for( i = 0 ; i < SoundSysData.PF.EqualizerInfo.BandNum ; i ++ )
			{
				( *BufferPlayInfo->PlayerEqualizerInterface )->GetBandLevel( BufferPlayInfo->PlayerEqualizerInterface, i, &millibelValue1 ) ;
				SoundSysData.PF.EqualizerInfo.BandInfo[ i ].Level = ( int )millibelValue1 ;

				( *BufferPlayInfo->PlayerEqualizerInterface )->GetCenterFreq( BufferPlayInfo->PlayerEqualizerInterface, i, &milliHertzValue1 ) ;
				SoundSysData.PF.EqualizerInfo.BandInfo[ i ].CenterFrequency = ( int )milliHertzValue1 ;

				( *BufferPlayInfo->PlayerEqualizerInterface )->GetBandFreqRange( BufferPlayInfo->PlayerEqualizerInterface, i, &milliHertzValue1, &milliHertzValue2 ) ;
				SoundSysData.PF.EqualizerInfo.BandInfo[ i ].FrequencyMin = ( int )milliHertzValue1 ;
				SoundSysData.PF.EqualizerInfo.BandInfo[ i ].FrequencyMax = ( int )milliHertzValue2 ;
			}

			// �v���Z�b�g���̐����擾
			( *BufferPlayInfo->PlayerEqualizerInterface )->GetNumberOfPresets( BufferPlayInfo->PlayerEqualizerInterface, &uint16value ) ;
			SoundSysData.PF.EqualizerInfo.PresetNum = ( int )uint16value ;

			// �v���Z�b�g���p�̃��������m��
			SoundSysData.PF.EqualizerInfo.PresetInfo = ( EQUALIZER_PRESET_INFO * )DXALLOC( sizeof( EQUALIZER_PRESET_INFO ) * SoundSysData.PF.EqualizerInfo.PresetNum ) ;
			if( SoundSysData.PF.EqualizerInfo.PresetInfo == NULL )
			{
				// �N���e�B�J���Z�N�V�����̉��
				CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;

				DXST_LOGFILEFMT_ADDUTF16LE(( "\xa4\x30\xb3\x30\xe9\x30\xa4\x30\xb6\x30\xfc\x30\x6e\x30\xd7\x30\xea\x30\xbb\x30\xc3\x30\xc8\x30\xc5\x60\x31\x58\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�C�R���C�U�[�̃v���Z�b�g���p�̃������̊m�ۂɎ��s���܂���\n" @*/ )) ;
				return -1 ;
			}

			// �v���Z�b�g�̏����擾
			( *BufferPlayInfo->PlayerEqualizerInterface )->GetCurrentPreset( BufferPlayInfo->PlayerEqualizerInterface, &uint16value ) ;
			SoundSysData.PF.EqualizerInfo.CurrentPresetIndex = ( int )uint16value ;
			for( i = 0 ; i < SoundSysData.PF.EqualizerInfo.PresetNum ; i ++ )
			{
				( *BufferPlayInfo->PlayerEqualizerInterface )->GetPresetName( BufferPlayInfo->PlayerEqualizerInterface, i, &charP ) ;
				ConvString( ( const char * )charP, -1, DX_CHARCODEFORMAT_UTF8, ( char * )SoundSysData.PF.EqualizerInfo.PresetInfo[ i ].Name, sizeof( SoundSysData.PF.EqualizerInfo.PresetInfo[ i ].Name ), _TCHARCODEFORMAT ) ;
			}

			// �Đ�����������
			if( ReleaseFlag )
			{
				NotUseSoundBufferPlayInfo( PlayInfoIndex ) ;
			}
		}

		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.SoundBufferPlayInfosCriticalSection ) ;
	}

	// ����I��
	return 0 ;
}


// �C�R���C�U�[���̌�n�����s��
static void TerminateEqualizerInfo( void )
{
	// �C�R���C�U�[�p�Ɋm�ۂ��Ă������������������
	if( SoundSysData.PF.UseEqualizer )
	{
		if( SoundSysData.PF.EqualizerInfo.BandInfo != NULL )
		{
			DXFREE( SoundSysData.PF.EqualizerInfo.BandInfo ) ;
			SoundSysData.PF.EqualizerInfo.BandInfo = NULL ;
		}

		if( SoundSysData.PF.EqualizerInfo.PresetInfo != NULL )
		{
			DXFREE( SoundSysData.PF.EqualizerInfo.PresetInfo ) ;
			SoundSysData.PF.EqualizerInfo.PresetInfo = NULL ;
		}
	}
}













#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_SOUND

