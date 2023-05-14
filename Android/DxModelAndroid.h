// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p���f���f�[�^����v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.24b
// 
// -------------------------------------------------------------------------------

#ifndef DX_MODELANDROID_H
#define DX_MODELANDROID_H

// �C���N���[�h ------------------------------------------------------------------
#include "../DxCompileConfig.h"

#ifndef DX_NON_MODEL

#include "../DxLib.h"
#include "../DxModel.h"
#include <GLES2/gl2.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// Android�p ���f���f�[�^�Ǘ��p�\����
struct MV1_MODEL_MANAGE_ANDR
{
	void *					CommonBuffer ;						// ��ɃV�F�C�v���W�̍X�V�Ŏg�p����ėp�o�b�t�@
	int						CommonBufferSize ;					// ��ɃV�F�C�v���W�̍X�V�Ŏg�p����ėp�o�b�t�@�̃T�C�Y

	int						EnableLightNum ;					// �L���ȃ��C�g�̐�
} ;

// Android�p ���_�o�b�t�@���ˑ����
struct MV1_VERTEXBUFFER_PF
{
	GLuint					VertexBufferObject ;				// ���_�o�b�t�@
	GLuint					IndexBufferObject ;					// �C���f�b�N�X�o�b�t�@
} ;

// Android�p �g���C�A���O�����X�g��f�[�^���ˑ����
struct MV1_TRIANGLE_LIST_BASE_PF
{
	BYTE					SkinFreeBoneVertexBufferUpdate ;	// �X�{�[���ȏ�̃X�L�j���O���b�V�������p���_�f�[�^���X�V�������ǂ���( TRUE:�X�V�ς�  FALSE:���X�V )
	void *					SkinFreeBoneVertexBuffer ;			// �X�{�[���ȏ�̃X�L�j���O���b�V�������p���_�f�[�^
} ;

// Android�p �g���C�A���O�����X�g���ˑ����
struct MV1_TRIANGLE_LIST_PF
{
	void *					SkinFreeBoneVertexPositionBuffer ;	// �X�{�[���ȏ�̃X�L�j���O���b�V�������p���_���W�f�[�^
	GLuint					VertexBufferObject ;				// ���_�o�b�t�@
} ;

// �������ϐ��錾 --------------------------------------------------------------

extern MV1_MODEL_MANAGE_ANDR MV1Man_Android ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �ėp�o�b�t�@�֐�
extern	int				MV1_ANDR_CommonBuffer_Setup( int Size ) ;						// �w��T�C�Y�̔ėp�o�b�t�@�̏������s��
extern	int				MV1_ANDR_CommonBuffer_Terminate( void ) ;						// �ėp�o�b�t�@�̌�n�����s��

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_MODEL

#endif // DX_MODELANDROID_H
