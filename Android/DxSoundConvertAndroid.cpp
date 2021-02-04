//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�T�E���h�f�[�^�ϊ��v���O����
// 
//  	Ver 3.22c
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_SOUND

// �C���N���[�h----------------------------------------------------------------
#include "DxSoundConvertAndroid.h"
#include "../DxSoundConvert.h"
#include "../DxSystem.h"
#include "../DxHeap.h"
#include "../DxMemory.h"
#include "../DxLog.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����`------------------------------------------------------------------

// �^��`----------------------------------------------------------------------

// �f�[�^�錾------------------------------------------------------------------

SOUNDCONVERTDATA_ANDR GSoundConvertData_Android ;

// �֐��v���g�^�C�v�錾 -------------------------------------------------------

// �v���O����------------------------------------------------------------------

// �������E�I���֐�

// �T�E���h�f�[�^�ϊ������̊��ˑ��̏��������s��
extern	int InitializeSoundConvert_PF( void )
{
	// ����I��
	return 0 ;
}

// �T�E���h�f�[�^�ϊ������̊��ˑ��̏I���������s��
extern	int TerminateSoundConvert_PF( void )
{
	// ����I��
	return 0 ;
}









// (���ˑ�����)�ϊ������̃Z�b�g�A�b�v( [��] -1:�G���[ )
extern	int SetupSoundConvert_PF( SOUNDCONV *SoundConv, STREAMDATA *Stream, int DisableReadSoundFunctionMask )
{
	return -1 ;
}

// (���ˑ�����)�ϊ������̈ʒu��ύX����( �T���v���P�� )
extern	int SetSampleTimeSoundConvert_PF(    SOUNDCONV *SoundConv, LONGLONG SampleTime )
{
	int res = -1 ;

	return res ;
}

// (���ˑ�����)�ϊ���̃o�b�t�@�Ƀf�[�^���[����
extern	int ConvertProcessSoundConvert_PF(  SOUNDCONV *SoundConv )
{
	int res = -1 ;

	return res ;
}

// (���ˑ�����)�ϊ������̌�n�����s��
extern	int TerminateSoundConvert_PF(        SOUNDCONV *SoundConv )
{
	return 0 ;
}

// (���ˑ�����)�ϊ���̑�}�̃f�[�^�T�C�Y�𓾂�
extern	LONGLONG GetSoundConvertDestSize_Fast_PF( SOUNDCONV *SoundConv )
{
	return 0 ;
}





















#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_SOUND

