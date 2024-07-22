// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�T�E���h�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.24d
// 
// -------------------------------------------------------------------------------

#ifndef DX_SOUNDANDROID_H
#define DX_SOUNDANDROID_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_SOUND

// �C���N���[�h ------------------------------------------------------------------
#include "../DxLib.h"
#include "../DxThread.h"

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �X�g���[���֌W�̒�`
#define STS_BUFSEC_FILE						(256)			// �X�g���[�����T�E���h�Đ����Ɋm�ۂ���T�E���h�o�b�t�@�̎���( �P�ʂ� STS_DIVNUM����1�b )( �t�@�C������̃X�g���[���Đ��p )
#define STS_ADVANCECOPYSEC_FILE				(192)			// �X�g���[�����T�E���h�Đ����ɉ����f�[�^���s�W�J���Ă����ő厞��( �P�ʂ� STS_DIVNUM����1�b )( �t�@�C������̃X�g���[���Đ��p )
#define STS_MINADVANCECOPYSEC_FILE			(96)			// �X�g���[�����T�E���h�Đ����ɉ����f�[�^���s�W�J���Ă����ŏ�����( �P�ʂ� STS_DIVNUM����1�b )( �t�@�C������̃X�g���[���Đ��p )

// ��̃o�b�t�@�[�L���[�̃o�b�t�@�̐�
#define BUFFERQUEUE_BUFFER_NUM				(16)

// �T�E���h�o�b�t�@�Đ������p���̍ő吔
#define SOUNDBUFFERPLAYINFO_MAX_NUM			(512)

// �\���̒�` --------------------------------------------------------------------

// �o�b�t�@�L���[�ɓn�����f�[�^�̏��
struct BUFFERENQUEUE_INFO
{
	DWORD							CompPos ;
	DWORD							AddBytes ;
	WORD							WorkBufferIndex ;
	WORD							Padding ;
} ;

// �T�E���h�o�b�t�@�Đ������p���\����
struct SOUNDBUFFERPLAYINFO
{
	int								SetupFlag ;							// �o�̓I�u�W�F�N�g�Ȃǂ̍쐬���ς�ł��邩�ǂ����̃t���O
	int								UseFlag ;							// �Đ��̂��߂Ɏg�p���Ă��邩�ǂ����̃t���O

	DWORD							Channels ;							// �`�����l����
	DWORD							BitsPerSample ;						// �P�T���v��������̃r�b�g��
	DWORD							SamplesPerSec ;						// �Đ����g��

	SLObjectItf						OutputMixObject ;					// �o�̓I�u�W�F�N�g
	SLObjectItf						PlayerObject;						// �v���C���[�I�u�W�F�N�g
	SLPlayItf						PlayerPlayInterface ;				// �v���C���[�Đ��C���^�t�F�[�X
	SLAndroidSimpleBufferQueueItf	PlayerBufferQueueInterface ;		// �v���C���[�o�b�t�@�L���[�C���^�t�F�[�X
	SLVolumeItf						PlayerVolumeInterface ;				// �v���C���[���ʃC���^�t�F�[�X
	SLEqualizerItf					PlayerEqualizerInterface ;			// �v���C���[�C�R���C�U�C���^�t�F�[�X
} ;

// �T�E���h�o�b�t�@���ˑ����\����
struct SOUNDBUFFER_PF
{
	DX_CRITICAL_SECTION				CriticalSection ;					// �N���e�B�J���Z�N�V����

	void *							WorkBufferBase ;					// ���g���ύX����Ɨp�o�b�t�@
	void *							WorkBuffer[ BUFFERQUEUE_BUFFER_NUM ] ;	// ���g���ύX����Ɨp�o�b�t�@�̃A�h���X
	BYTE							WorkBufferUseFlag[ BUFFERQUEUE_BUFFER_NUM ] ;	// ���g���ύX����Ɨp�o�b�t�@���g�p���Ă��邩�ǂ����̃t���O

	volatile int					EnqueueInfoNum ;					// �o�b�t�@�L���[�ɓn�����f�[�^�̐�
	volatile BUFFERENQUEUE_INFO		EnqueueInfo[ BUFFERQUEUE_BUFFER_NUM ] ;	// �o�b�t�@�L���[�ɓn�����f�[�^�̏��

	int								BufferEndPlayEnqueueNum ;			// �o�b�t�@�L���[�ɍĐ��I����̃L���[��ς񂾉�

	int								PlaySetupComp ;						// �Đ��������ł��Ă��邩( TRUE:�ł��Ă���  FALSE:�ł��Ă��Ȃ� )
	int								UseSoundBufferPlayInfoIndex ;		// �g�p���Ă���Đ������p���
//	SLObjectItf						OutputMixObject ;					// �o�̓I�u�W�F�N�g
//	SLObjectItf						PlayerObject;						// �v���C���[�I�u�W�F�N�g
//	SLPlayItf						PlayerPlayInterface ;				// �v���C���[�Đ��C���^�t�F�[�X
//	SLAndroidSimpleBufferQueueItf	PlayerBufferQueueInterface ;		// �v���C���[�o�b�t�@�L���[�C���^�t�F�[�X
//	SLVolumeItf						PlayerVolumeInterface ;				// �v���C���[���ʃC���^�t�F�[�X

	int								StopSoundBufferValid ;
	struct SOUNDBUFFER *			StopSoundBufferPrev ;
	struct SOUNDBUFFER *			StopSoundBufferNext ;
} ;

// �C�R���C�U�[�̃o���h���
struct EQUALIZER_BAND_INFO
{
	int							Level ;
	int							CenterFrequency ;
	int							FrequencyMin ;
	int							FrequencyMax ;
} ;

// �C�R���C�U�[�̃v���Z�b�g���
struct EQUALIZER_PRESET_INFO
{
	TCHAR						Name[ 256 ] ;
} ;

// �C�R���C�U�[���
struct SOUNDBUFFER_EQUALIZER_INFO
{
	int							Enabled ;
	int							BandNum ;
	EQUALIZER_BAND_INFO			*BandInfo ;
	int							BandLevelRangeMin ;
	int							BandLevelRangeMax ;
	int							PresetNum ;
	EQUALIZER_PRESET_INFO		*PresetInfo ;
	int							CurrentPresetIndex ;
} ;

// �T�E���h�V�X�e���p���ˑ��f�[�^�\����
struct SOUNDSYSTEMDATA_PF
{
	int							EngineObjectInitialize ;
	SLObjectItf					EngineObject ;							// �G���W���I�u�W�F�N�g
	SLEngineItf					EngineInterface ;						// �G���W���C���^�t�F�[�X

	pthread_t					ProcessSoundThread ;					// ProcessStreamSoundMemAll �����ĂԃX���b�h��ID
	volatile int				ProcessSoundThreadEndRequest ;			// ProcessStreamSoundMemAll �����ĂԃX���b�h���I�����邩�ǂ���

	int							DXSoundProcessStart ;					// �c�w���C�u�����̃T�E���h�������J�n�������ǂ���

	int							AudioManager_SampleRate ;				// �I�[�f�B�I�f�o�C�X�ɓK�����T���v�����O���[�g
	int							AudioManager_FramesPerBuffer ;			// �I�[�f�B�I�f�o�C�X�ɓK�����o�b�t�@�T�C�Y

	SLObjectItf						SelfMixing_OutputMixObject ;			// ���O�~�L�V���O�p�@�o�̓I�u�W�F�N�g
	BYTE *							SelfMixing_OutputBuffer ;				// ���O�~�L�V���O�p�@���o�͗p�o�b�t�@
	SLObjectItf						SelfMixing_PlayerObject;				// ���O�~�L�V���O�p�@�v���C���[�I�u�W�F�N�g
	SLPlayItf						SelfMixing_PlayerPlayInterface ;		// ���O�~�L�V���O�p�@�v���C���[�Đ��C���^�t�F�[�X
	SLAndroidSimpleBufferQueueItf	SelfMixing_PlayerBufferQueueInterface ;	// ���O�~�L�V���O�p�@�v���C���[�o�b�t�@�L���[�C���^�t�F�[�X
	ULONGLONG						SelfMixing_TotalPlaySampleCount ;		// ���O�~�L�V���O�ōĐ������T���v����

	int							UseEqualizer ;							// �C�R���C�U�[�@�\���g�p���邩�ǂ���( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
	SOUNDBUFFER_EQUALIZER_INFO	EqualizerInfo ;							// �C�R���C�U�[���

	DX_CRITICAL_SECTION			StopSoundBufferCriticalSection ;		// �N���e�B�J���Z�N�V����
	struct SOUNDBUFFER *		StopSoundBuffer ;

	DX_CRITICAL_SECTION			SoundBufferPlayInfosCriticalSection ;					// �T�E���h�o�b�t�@�̍Đ������ɕK�v�ȏ��p�̃N���e�B�J���Z�N�V����
	int							SoundBufferPlayInfoSetupErrorNum ;						// �T�E���h�o�b�t�@�̍Đ������ɕK�v�ȏ��̃Z�b�g�A�b�v�Ɏ��s�����ۂ̃Z�b�g�A�b�v���ς�ł���v�f��
	int							SoundBufferPlayInfoSetupNum ;							// �T�E���h�o�b�t�@�̍Đ������ɕK�v�ȏ��̃Z�b�g�A�b�v���ς�ł���v�f�̐�
	SOUNDBUFFERPLAYINFO			SoundBufferPlayInfos[ SOUNDBUFFERPLAYINFO_MAX_NUM ] ;	// �T�E���h�o�b�t�@�̍Đ������ɕK�v�ȏ��̍\����
} ;

// �l�h�c�h�f�[�^���ˑ����
struct MIDIHANDLEDATA_PF
{
	int							Dummy ;
} ;

// �l�h�c�h�V�X�e���p���ˑ��f�[�^�\����
struct MIDISYSTEMDATA_PF
{
	int							Dummy ;
} ;

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern	int		MidiCallBackProcess( void ) ;																			// �l�h�c�h���t�I�����Ă΂��R�[���o�b�N�֐�

extern	void	SoundBuffer_Apply_StopSoundBufferList( void ) ;							// ��~�҂��T�E���h�o�b�t�@���X�g�ɓo�^����Ă���T�E���h�o�b�t�@���~����


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_SOUND

#endif // DX_SOUNDANDROID_H
