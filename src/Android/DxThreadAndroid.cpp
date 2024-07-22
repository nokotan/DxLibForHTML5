//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�X���b�h�֌W�v���O����
// 
//  	Ver 3.24d
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

// �C���N���[�h ---------------------------------------------------------------
#include "DxThreadAndroid.h"
#include "../DxMemory.h"
#include "../DxBaseFunc.h"
#include <unistd.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` -----------------------------------------------------------------

#define THREAD_STACK_SIZE				(128 * 1024)			// �X���b�h�̃X�^�b�N�T�C�Y

#define THREAD_SUSPEND_EVENT_BIT		(0x00000001)			// �x�~��ԏ����p�̃C�x���g�̃r�b�g

// �\���̐錾 -----------------------------------------------------------------

// �f�[�^��` -----------------------------------------------------------------

// �֐��錾 -------------------------------------------------------------------

// �v���O���� -----------------------------------------------------------------

// �X���b�h�̏���������������
extern void Thread_Initialize( void )
{
	return ;
}

// �X���b�h�����s����֐�
static void * ThreadRunFunction( void *pArgBlock )
{
	THREAD_INFO *pInfo = ( THREAD_INFO * )pArgBlock ;

	Thread_Suspend( pInfo ) ;

	// �X���b�h�쐬���ɓn���ꂽ�֐������s
	pInfo->pFunction( pInfo, pInfo->pParam ) ;

	return NULL ;
}

// �X���b�h���쐬����
extern int Thread_Create( THREAD_INFO *pThreadInfo, void ( *pFunction )( THREAD_INFO *, void * ), void *pParam )
{
	// �l��������
	pThreadInfo->Thread_valid		= 0 ;
	pThreadInfo->Threadattr_valid	= 0 ;
	pThreadInfo->Cond_valid			= 0 ;
	pThreadInfo->Mutex_valid		= 0 ;
	pThreadInfo->Mutexaddr_valid	= 0 ;
	pThreadInfo->SuspendFlag		= FALSE ;

	// �p�����[�^�̕ۑ�
	pThreadInfo->pFunction	= pFunction ;
	pThreadInfo->pParam		= pParam ;

	// �~���[�e�b�N�X�����̏�����
	if( pthread_mutexattr_init( &pThreadInfo->Mutexattr ) != 0 )
	{
		goto ERR ;
	}
	pThreadInfo->Mutexaddr_valid = 1 ;

	// �ċA���b�N�\�ɂ���
	if( pthread_mutexattr_settype( &pThreadInfo->Mutexattr, PTHREAD_MUTEX_RECURSIVE ) != 0 )
	{
		goto ERR ;
	}

	// �~���[�e�b�N�X�̍쐬
	if( pthread_mutex_init( &pThreadInfo->Mutex, &pThreadInfo->Mutexattr ) != 0 )
	{
		goto ERR ;
	}
	pThreadInfo->Mutex_valid = 1 ;

	// �����ϐ��̍쐬
	if( pthread_cond_init( &pThreadInfo->Cond, NULL ) != 0 )
	{
		goto ERR ;
	}
	pThreadInfo->Cond_valid = 1 ;

	// �X���b�h�����̏�����
	if( pthread_attr_init( &pThreadInfo->Threadattr ) != 0 )
	{
		goto ERR ;
	}
	pThreadInfo->Threadattr_valid = 1 ;

	// �X���b�h�����̃Z�b�g
//	if( pthread_attr_setdetachstate( &pThreadInfo->Threadattr, PTHREAD_CREATE_DETACHED ) != 0 )
//	{
//		goto ERR ;
//	}

	// �X�^�b�N�T�C�Y�̃Z�b�g
	if( pthread_attr_setstacksize( &pThreadInfo->Threadattr, THREAD_STACK_SIZE ) != 0 )
	{
		goto ERR ;
	}

	// �X���b�h�̍쐬
	if( pthread_create( &pThreadInfo->Thread, &pThreadInfo->Threadattr, ThreadRunFunction, pThreadInfo ) != 0 )
	{
		goto ERR ;
	}
	pThreadInfo->Thread_valid = 1 ;

	// ����I��
	return 0 ;

ERR :

	if( pThreadInfo->Mutex_valid )
	{
		pthread_mutex_destroy( &pThreadInfo->Mutex ) ;
		pThreadInfo->Mutex_valid = 0 ;
	}

	if( pThreadInfo->Mutexaddr_valid )
	{
		pthread_mutexattr_destroy( &pThreadInfo->Mutexattr ) ;
		pThreadInfo->Mutexaddr_valid = 0 ;
	}

	if( pThreadInfo->Cond_valid )
	{
		pthread_cond_destroy( &pThreadInfo->Cond ) ;
		pThreadInfo->Cond_valid = 0 ;
	}

	if( pThreadInfo->Threadattr_valid )
	{
		pthread_attr_destroy( &pThreadInfo->Threadattr ) ;
		pThreadInfo->Threadattr_valid = 0 ;
	}

	if( pThreadInfo->Thread_valid )
	{
		pthread_detach( pThreadInfo->Thread ) ;
		pThreadInfo->Thread_valid = 0 ;
	}

	// �G���[�I��
	return -1 ;
}

// �X���b�h�̌�n�����s��
extern void Thread_Delete( THREAD_INFO *pThreadInfo )
{
	if( pThreadInfo->Mutex_valid )
	{
		pthread_mutex_destroy( &pThreadInfo->Mutex ) ;
		pThreadInfo->Mutex_valid = 0 ;
	}

	if( pThreadInfo->Mutexaddr_valid )
	{
		pthread_mutexattr_destroy( &pThreadInfo->Mutexattr ) ;
		pThreadInfo->Mutexaddr_valid = 0 ;
	}

	if( pThreadInfo->Cond_valid )
	{
		pthread_cond_destroy( &pThreadInfo->Cond ) ;
		pThreadInfo->Cond_valid = 0 ;
	}

	if( pThreadInfo->Threadattr_valid )
	{
		pthread_attr_destroy( &pThreadInfo->Threadattr ) ;
		pThreadInfo->Threadattr_valid = 0 ;
	}

	if( pThreadInfo->Thread_valid )
	{
		pthread_detach( pThreadInfo->Thread ) ;
		pThreadInfo->Thread_valid = 0 ;
	}
}

// �X���b�h���L�����ǂ������擾����( 1:�L��  0:���� )
extern int Thread_IsValid( THREAD_INFO *pThreadInfo )
{
	return pThreadInfo->Thread_valid ;
}


// �X���b�h�̎��s�D�揇�ʂ�ݒ肷��
extern void Thread_SetPriority( THREAD_INFO *pThreadInfo, int Priority /* DX_THREAD_PRIORITY_LOWEST �Ȃ� */ )
{
	sched_param param ;
	volatile static int InitPriorityTable = 0 ;
	volatile static int PriorityTable[ DX_THREAD_PRIORITY_NUM ] ;

	if( Priority < 0 || Priority >= DX_THREAD_PRIORITY_NUM )
	{
		return ;
	}

	if( InitPriorityTable == 0 )
	{
		int MinPrio ;
		int MaxPrio ;

		MaxPrio = sched_get_priority_max( SCHED_NORMAL ) ;
		MinPrio = sched_get_priority_min( SCHED_NORMAL ) ;

		PriorityTable[ DX_THREAD_PRIORITY_LOWEST       ] = ( MaxPrio - MinPrio ) * 0 / 3 + MinPrio ;
		PriorityTable[ DX_THREAD_PRIORITY_BELOW_NORMAL ] = ( MaxPrio - MinPrio ) * 1 / 3 + MinPrio ;
		PriorityTable[ DX_THREAD_PRIORITY_NORMAL       ] = ( MaxPrio - MinPrio ) * 2 / 3 + MinPrio ;
		PriorityTable[ DX_THREAD_PRIORITY_HIGHEST      ] = ( MaxPrio - MinPrio ) * 3 / 3 + MinPrio ;

		InitPriorityTable = 1 ;
	}
	
	param.sched_priority = PriorityTable[ Priority ] ;
	pthread_setschedparam( pThreadInfo->Thread, SCHED_NORMAL, &param ) ;
}

// �J�����g�X���b�h�̂h�c���擾����
extern DWORD_PTR Thread_GetCurrentId( void )
{
	return ( DWORD_PTR )pthread_self() ;
}

// �X���b�h�̂h�c���擾����
extern DWORD_PTR Thread_GetId( THREAD_INFO *pThreadInfo )
{
	return ( DWORD_PTR )pThreadInfo->Thread ;
}

// �X���b�h���x�~��Ԃɂ���
extern void Thread_Suspend( THREAD_INFO *pThreadInfo )
{
	// �~���[�e�b�N�X�����b�N
	pthread_mutex_lock( &pThreadInfo->Mutex ) ;

	// �x�~��Ԃ̃t���O�𗧂Ă�
	pThreadInfo->SuspendFlag = TRUE ;

	// �V�O�i���҂��ɂ���
	pthread_cond_wait( &pThreadInfo->Cond, &pThreadInfo->Mutex ) ;

	// �~���[�e�b�N�X���A�����b�N
	pthread_mutex_unlock( &pThreadInfo->Mutex ) ;
}

// �X���b�h�̋x�~��Ԃ���������( 0:�x�~��Ԃ���Ȃ�����  1:�x�~��Ԃ����� )
extern int Thread_Resume( THREAD_INFO *pThreadInfo )
{
	// �~���[�e�b�N�X�����b�N
	pthread_mutex_lock( &pThreadInfo->Mutex ) ;

	// �x�~��Ԃł͂Ȃ������炷���ɔ�����
	if( pThreadInfo->SuspendFlag == FALSE )
	{
		// �~���[�e�b�N�X���A�����b�N
		pthread_mutex_unlock( &pThreadInfo->Mutex ) ;

		// �x�~��Ԃł͂Ȃ������̖߂�l
		return 0 ;
	}

	// �x�~��Ԃ̃t���O��|��
	pThreadInfo->SuspendFlag = FALSE ;

	// �V�O�i���𑗂�
	pthread_cond_signal( &pThreadInfo->Cond ) ; 

	// �~���[�e�b�N�X���A�����b�N
	pthread_mutex_unlock( &pThreadInfo->Mutex ) ;

	// �x�~��Ԃ������̖߂�l
	return 1 ;
}

// �w�莞�ԃX���b�h���~����
extern void Thread_Sleep( DWORD MiliSecond )
{
	usleep( MiliSecond * 1000 ) ;
}





// �N���e�B�J���Z�N�V�����̏�����
extern int CriticalSection_Initialize( DX_CRITICAL_SECTION *pCSection )
{
	pCSection->Mutex_valid		= 0 ;
	pCSection->Mutexaddr_valid	= 0 ;

	// �~���[�e�b�N�X�����̏�����
	if( pthread_mutexattr_init( &pCSection->Mutexattr ) != 0 )
	{
		goto ERR ;
	}
	pCSection->Mutexaddr_valid = 1 ;

	// �ċA���b�N�\�ɂ���
	if( pthread_mutexattr_settype( &pCSection->Mutexattr, PTHREAD_MUTEX_RECURSIVE ) != 0 )
	{
		goto ERR ;
	}

	// �~���[�e�b�N�X�̍쐬
	if( pthread_mutex_init( &pCSection->Mutex, &pCSection->Mutexattr ) != 0 )
	{
		goto ERR ;
	}
	pCSection->Mutex_valid = 1 ;

#if defined( _DEBUG )
	int i ;
	for( i = 0 ; i < 256 ; i ++ )
	{
		pCSection->FilePath[ 0 ] = '\0' ;
	}
#endif

	return 0 ;

ERR :

	if( pCSection->Mutex_valid )
	{
		pthread_mutex_destroy( &pCSection->Mutex ) ;
		pCSection->Mutex_valid = 0 ;
	}

	if( pCSection->Mutexaddr_valid )
	{
		pthread_mutexattr_destroy( &pCSection->Mutexattr ) ;
		pCSection->Mutexaddr_valid = 0 ;
	}

	return -1 ;
}

// �N���e�B�J���Z�N�V�����̍폜
extern int CriticalSection_Delete( DX_CRITICAL_SECTION *pCSection )
{
	if( pCSection->Mutex_valid )
	{
		pthread_mutex_destroy( &pCSection->Mutex ) ;
		pCSection->Mutex_valid = 0 ;
	}

	if( pCSection->Mutexaddr_valid )
	{
		pthread_mutexattr_destroy( &pCSection->Mutexattr ) ;
		pCSection->Mutexaddr_valid = 0 ;
	}

	return 0 ;
}

// �N���e�B�J���Z�N�V�����̃��b�N�̎擾
//#if defined( _DEBUG )
#if 1
extern int CriticalSection_Lock( DX_CRITICAL_SECTION *pCSection, const char *FilePath, int LineNo )
#else
extern int CriticalSection_Lock( DX_CRITICAL_SECTION *pCSection )
#endif
{
#if defined( _DEBUG )
	DWORD_PTR ThreadID = Thread_GetCurrentId() ;
#endif

	// �~���[�e�b�N�X�����b�N
	pthread_mutex_lock( &pCSection->Mutex ) ;

#if defined( _DEBUG )
	int Length = ( int )_STRLEN( FilePath ) ;
	if( Length >= 512 ) Length = 511 ;
	_MEMCPY( pCSection->FilePath, FilePath, ( size_t )Length ) ;
	pCSection->FilePath[ Length ] = '\0' ;
	pCSection->LineNo = LineNo ;
	pCSection->ThreadID = ThreadID ;
#endif

	return 0 ;
}

// �N���e�B�J���Z�N�V�����̃��b�N���������
extern int CriticalSection_Unlock( DX_CRITICAL_SECTION *pCSection )
{
	// �~���[�e�b�N�X������
	pthread_mutex_unlock( &pCSection->Mutex ) ;

	return 0 ;
}




#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

