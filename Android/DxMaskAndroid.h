// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�}�X�N�f�[�^�Ǘ��v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

#ifndef DX_MASKANDROID_H
#define DX_MASKANDROID_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_MASK

// �C���N���[�h ------------------------------------------------------------------
#include "../DxLib.h"
#include "../DxGraphics.h"
#include "../DxArchive_.h"
#include <GLES2/gl2.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

#define MASKANDR					MaskManageData_Android

// �\���̒�` --------------------------------------------------------------------

// Android �p�̃}�X�N�������\����
struct MASKMANAGEDATA_ANDR
{
	int								MaskTextureSizeX ;				// �}�X�N�e�N�X�`���̃T�C�Y
	int								MaskTextureSizeY ;

	GLuint							MaskScreenFrameBuffer ;			// �}�X�N�����p����ʃt���[���o�b�t�@
	GLuint							MaskScreenTextureBuffer ;		// �}�X�N�����p����ʃe�N�X�`���o�b�t�@
	GLuint							MaskScreenDepthBuffer ;			// �}�X�N�����p����ʐ[�x�o�b�t�@

	GLuint							MaskScreenOldFrameBuffer ;		// �Â��}�X�N�����p����ʃt���[���o�b�t�@
	GLuint							MaskScreenOldTextureBuffer ;	// �Â��}�X�N�����p����ʃe�N�X�`���o�b�t�@
	GLuint							MaskScreenOldDepthBuffer ;		// �Â��}�X�N�����p����ʐ[�x�o�b�t�@

	GLuint							MaskImageTextureBuffer ;		// �}�X�N�C���[�W�e�N�X�`���o�b�t�@

	GLuint							DestTargetFrameBuffer ;			// �`��Ώۂ̃t���[���o�b�t�@
	GLuint							DestTargetTextureBuffer ;		// �`��Ώۂ̃e�N�X�`���o�b�t�@
	GLuint							DestTargetDepthBuffer ;			// �`��Ώۂ̐[�x�o�b�t�@
	GLuint							DestTargetWidth ;				// �`��Ώۂ̕�
	GLuint							DestTargetHeight ;				// �`��Ώۂ̍���
} ;

// �������ϐ��錾 --------------------------------------------------------------

extern MASKMANAGEDATA_ANDR MaskManageData_Android ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_MASK

#endif // DX_MASKANDROID_H
