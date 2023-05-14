//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�������֌W�v���O����
// 
//  	Ver 3.24b
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

// �C���N���[�h ---------------------------------------------------------------
#include "../DxMemory.h"
#include "../DxLog.h"
#include "../DxBaseFunc.h"
#include <stdlib.h>
#include <new>
#include <cstdlib>
#include <cerrno>

#ifndef DX_NON_NAMESPACE

using namespace DxLib ;

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` -----------------------------------------------------------------

// �\���̐錾 -----------------------------------------------------------------

// �f�[�^��` -----------------------------------------------------------------

// �֐��錾 -------------------------------------------------------------------

// �v���O���� -----------------------------------------------------------------

// �����������̏��������s���֐��̊��ˑ�����
extern int MemoryInitialize_PF( void )
{
	return 0 ;
}

// �����������̌�n�����s���֐��̊��ˑ�����
extern int MemoryTerminate_PF( void )
{
	return 0 ;
}

// �����������̎����I�����̊��ˑ�����
extern int MemoryProcess_PF( void )
{
	return 0 ;
}

// �������̃G���[�`�F�b�N�̊��ˑ�����
extern int MemoryErrorCheck_PF( void )
{
	return 0 ;
}

// Android �̃q�[�v�p�̃������̈���m�ۂ��邽�߂̃R�[���o�b�N�֐��Q�� AutoAlloc_CreateHeapCallback
extern int NormalMemory_AutoAlloc_CreateHeapCallback_PF( int Param, void *Buffer, ALLOCMEM_SIZE_TYPE Size )
{
	PLATFORMHEAP_ANDR *			PlatformHeap = ( PLATFORMHEAP_ANDR * )Buffer ;

	// �o�b�t�@�T�C�Y�`�F�b�N
	if( sizeof( PLATFORMHEAP_ANDR ) > ALLOCHEAP_CALLBACK_INFO_SIZE )
	{
		*( ( DWORD * )0x00000000 ) = 0xffffffff ;
	}

	// ���������m��
	PlatformHeap->AllocAddress = malloc( Size ) ;
	if( PlatformHeap->AllocAddress == NULL )
	{
		return -1 ;
	}
	PlatformHeap->AllocSize = Size ;

	return 0 ;
}

// ���ˑ��̈�ʓI�ȃq�[�v�p�̃������̈���m�ۂ��邽�߂̃R�[���o�b�N�֐��Q�� AutoAlloc_GetHeapAddressCallback
extern void * NormalMemory_AutoAlloc_GetHeapAddressCallback_PF( int Param, void *Buffer )
{
	PLATFORMHEAP_ANDR *			PlatformHeap = ( PLATFORMHEAP_ANDR * )Buffer ;

	return PlatformHeap->AllocAddress ;
}

// ���ˑ��̈�ʓI�ȃq�[�v�p�̃������̈���m�ۂ��邽�߂̃R�[���o�b�N�֐��Q�� AutoAlloc_GetHeapSizeCallback
extern ALLOCMEM_SIZE_TYPE NormalMemory_AutoAlloc_GetHeapSizeCallback_PF( int Param, void *Buffer )
{
	PLATFORMHEAP_ANDR *			PlatformHeap = ( PLATFORMHEAP_ANDR * )Buffer ;

	return ( ALLOCMEM_SIZE_TYPE )PlatformHeap->AllocSize ;
}

// ���ˑ��̈�ʓI�ȃq�[�v�p�̃������̈���m�ۂ��邽�߂̃R�[���o�b�N�֐��Q�� AutoAlloc_DeleteHeapCallback
extern int NormalMemory_AutoAlloc_DeleteHeapCallback_PF( int Param, void *Buffer )
{
	PLATFORMHEAP_ANDR *			PlatformHeap = ( PLATFORMHEAP_ANDR * )Buffer ;

	// �����������
	free( PlatformHeap->AllocAddress ) ;

	return 0 ;
}

// �m�ۂ��Ă��郁������񋓂���֐��̊��ˑ�����
extern int DxDumpAlloc_PF( void )
{
	return 0 ;
}



#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

