//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�pBaseImage�v���O����
// 
//  	Ver 3.24b
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

// �C���N���[�h ---------------------------------------------------------------
#include "DxBaseImageAndroid.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` -----------------------------------------------------------------

// �\���̐錾 -----------------------------------------------------------------

// �֐��錾 -------------------------------------------------------------------

// �f�[�^��` -----------------------------------------------------------------

int ( *DefaultImageLoadFunc_PF[] )( STREAMDATA *Src, BASEIMAGE *BaseImage, int GetFormatOnly ) =
{
	NULL
} ;

// �v���O���� -----------------------------------------------------------------

// ���ˑ��������E�I���֐�

// ��{�C���[�W�Ǘ����̊��ˑ������̏�����
extern int InitializeBaseImageManage_PF( void )
{
	return 0 ;
}

// ��{�C���[�W�Ǘ����̊��ˑ������̌�n��
extern int TerminateBaseImageManage_PF( void )
{
	return 0 ;
}








#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

