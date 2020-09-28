// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�X���b�h�֌W�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.22a
// 
// -------------------------------------------------------------------------------

#ifndef DX_THREADANDROID_H
#define DX_THREADANDROID_H

// �C���N���[�h ------------------------------------------------------------------
#include "../DxCompileConfig.h"
#include <pthread.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// �N���e�B�J���Z�N�V����
struct DX_CRITICAL_SECTION
{
	int						Mutex_valid ;								// Mutex ���L�����ǂ���
	pthread_mutex_t			Mutex ;										// �x�~��ԏ����p�̃~���[�e�b�N�X
	int						Mutexaddr_valid ;							// Mutexaddr ���L�����ǂ���
	pthread_mutexattr_t		Mutexattr ;									// �x�~��ԏ����p�̃~���[�e�b�N�X�̑������
#if defined( _DEBUG )
	char					FilePath[ 512 ] ;
	int						LineNo ;
	DWORD_PTR				ThreadID ;
#endif
} ;

// ��̃X���b�h�̏��
struct THREAD_INFO
{
	void					( *pFunction )( THREAD_INFO *, void * ) ;	// ���s����֐�
	void					*pParam ;									// ���s����֐��ɓn���p�����[�^
	int						Thread_valid ;								// Thread ���L�����ǂ���
	pthread_t				Thread ;									// �X���b�h
	int						Threadattr_valid ;							// Threadattr ���L�����ǂ���
	pthread_attr_t			Threadattr ;								// �X���b�h�̑������
	int						Cond_valid ;								// Cond ���L�����ǂ���
	pthread_cond_t			Cond ;										// �x�~��ԏ����p�̏����ϐ�
	int						Mutex_valid ;								// Mutex ���L�����ǂ���
	pthread_mutex_t			Mutex ;										// �x�~��ԏ����p�̃~���[�e�b�N�X
	int						Mutexaddr_valid ;							// Mutexaddr ���L�����ǂ���
	pthread_mutexattr_t		Mutexattr ;									// �x�~��ԏ����p�̃~���[�e�b�N�X�̑������
	int						SuspendFlag ;								// �x�~��Ԃ��ǂ����̃t���O
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_THREADANDROID_H
