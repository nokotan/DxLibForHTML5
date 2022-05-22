//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p����v���O����
// 
//  	Ver 3.23 
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_MOVIE

// �C���N���[�h----------------------------------------------------------------
#include "DxMovieAndroid.h"
#include "DxFileAndroid.h"
#include "DxMemoryAndroid.h"
#include "../DxLog.h"
#include "../DxMovie.h"
#include "../DxSystem.h"
#include "../DxMemory.h"
#include "../DxBaseFunc.h"
// #include <videodec.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����`------------------------------------------------------------------

// �^��`----------------------------------------------------------------------

// �f�[�^�錾------------------------------------------------------------------

// �֐��v���g�^�C�v�錾 -------------------------------------------------------

// �v���O����------------------------------------------------------------------

// ���[�r�[�֘A�̊Ǘ������̏������̊��ˑ�����
extern int InitializeMovieManage_PF( void )
{
	return 0 ;
}

// ���[�r�[�֘A�̊Ǘ������̌�n���̊��ˑ�����
extern int TerminateMovieManage_PF( void )
{
	return 0 ;
}

// OpenMovie �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W�����̊��ˑ�����
extern int OpenMovie_UseGParam_PF( MOVIEGRAPH * Movie, OPENMOVIE_GPARAM *GParam, const wchar_t *FileName, int *Width, int *Height, int SurfaceMode, int ImageSizeGetOnly, int ASyncThread )
{
	return -1 ;
}

// ���[�r�[�p�̃O���t�B�b�N�n���h���쐬�p�̃p�����[�^���J�X�^�}�C�Y����
extern int OpenMovie_CustomGraphHandleGParam_PF( MOVIEGRAPH * Movie, struct SETUP_GRAPHHANDLE_GPARAM *InitGraphHandleGParam )
{
	return 0 ;
}

// ���[�r�[�n���h���̌�n�����s��
extern int TerminateMovieHandle_PF( HANDLEINFO *HandleInfo )
{
	// ����I��
	return 0 ;
}

// ���[�r�[�̍Đ����J�n���鏈���̊��ˑ�����
extern int PlayMovie__PF( MOVIEGRAPH * Movie, int PlayType, int SysPlay )
{
	// ����I��
	return 0 ;
}

// ���[�r�[�̍Đ����X�g�b�v���鏈���̊��ˑ�����
extern 	int PauseMovie_PF( MOVIEGRAPH * Movie, int SysPause )
{
	// ����I��
	return 0 ;
}

// ���[�r�[�̍Đ��ʒu��ݒ肷��(�~���b�P��)�����̊��ˑ�����
extern int SeekMovie_PF( MOVIEGRAPH * Movie, int Time )
{
	// ����I��
	return 0 ;
}

// ���[�r�[�̍Đ����x��ݒ肷��( 1.0 = ���{��  2.0 = �Q�{�� )�����̊��ˑ�����
extern int SetPlaySpeedRateMovie_PF( MOVIEGRAPH * Movie, double SpeedRate )
{
	// ����I��
	return 0 ;
}

// ���[�r�[�̍Đ���Ԃ𓾂鏈���̊��ˑ�����
extern int GetMovieState_PF( MOVIEGRAPH * Movie )
{
	return Movie->PlayFlag ;
}

// ���[�r�[�̃{�����[�����Z�b�g����(0�`10000)�����̊��ˑ�����
extern int SetMovieVolume_PF( MOVIEGRAPH * Movie, int Volume )
{
	// ����I��
	return 0 ;
}

// ���[�r�[�̊�{�C���[�W�f�[�^���擾���鏈���̊��ˑ�����
extern	BASEIMAGE *GetMovieBaseImage_PF( MOVIEGRAPH * Movie, int *ImageUpdateFlag, int ImageUpdateFlagSetOnly )
{
	return NULL ;
}

// ���[�r�[�̑��t���[�����𓾂�
extern int GetMovieTotalFrame_PF( MOVIEGRAPH * Movie )
{
	return -1 ;
}

// ���[�r�[�̍Đ��ʒu���擾����(�~���b�P��)�����̊��ˑ�����
extern int TellMovie_PF( MOVIEGRAPH * Movie )
{
//	return Movie->PF.PlayTime / 1000 ;
	return 0 ;
}

// ���[�r�[�̍Đ��ʒu���擾����(�t���[���P��)�����̊��ˑ�����
extern int TellMovieToFrame_PF( MOVIEGRAPH * Movie )
{
//	return Movie->PF.FrameCount < 0 ? 0 : Movie->PF.FrameCount ;
	return 0 ;
}

// ���[�r�[�̍Đ��ʒu��ݒ肷��(�t���[���P��)�����̊��ˑ�����
extern int SeekMovieToFrame_PF( MOVIEGRAPH * Movie, int Frame )
{
	// ����I��
	return 0 ;
}

// ���[�r�[�̂P�t���[��������̎��Ԃ𓾂鏈���̊��ˑ�����
extern LONGLONG GetOneFrameTimeMovie_PF( MOVIEGRAPH * Movie )
{
	return ( LONGLONG )( 1000000.0f / 29.970f ) ;
}





// ���[�r�[�̍X�V���s�������̊��ˑ�����
extern int UpdateMovie_PF( MOVIEGRAPH * Movie, int AlwaysFlag )
{
	// ����I��
	return 0 ;
}



#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_MOVIE

