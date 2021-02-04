// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�pGraphFilter�n�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.22c
// 
// -------------------------------------------------------------------------------

#ifndef DX_GRAPHICSFILTERANDROID_H
#define DX_GRAPHICSFILTERANDROID_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_FILTER

// �C���N���[�h ------------------------------------------------------------------
#include "../DxLib.h"
#include "../DxGraphicsFilter.h"
#include "../DxArchive_.h"
#include "DxGraphicsAndroid.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// �t�B���^�[�����p�̏��\����
struct GRAPHFILTER_SYSTEMIFNO_ANDR
{
	int						WorkDrawValidGrHandle[ 2 ][ 18 ][ 18 ][ 2 ] ;	// �t�B���^�[������Ɨp�`��\�e�N�X�`��[ 0:�����e�N�X�`�� 1:���������_�e�N�X�`�� ][ �Q�̂��� ][ ��Ɨp�Q�� ]

	GRAPHICS_ANDROID_SHADER	Gauss[ 3 ] ;							// �K�E�X�t�B���^�̃s�N�Z���V�F�[�_�[
	GRAPHICS_ANDROID_SHADER	BrightClip[ 2 ][ 2 ][ 2 ] ;				// ���邳�ŃN���b�v����t�B���^�̃s�N�Z���V�F�[�_�[[ 1:���ȏ�N���b�v  0:���ȉ��N���b�v ][ 1:�N���b�v�h��Ԃ����� 0:�h��Ԃ��Ȃ� ][ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	BrightScale[ 2 ] ;						// �w��̖��邳�̗̈���g�傷��t�B���^�̃s�N�Z���V�F�[�_�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	DownScale[ 3 ] ;						// �k���t�B���^�[( 0:X2 1:X4 2:X8 )
	GRAPHICS_ANDROID_SHADER	Hsb[ 3 ][ 2 ] ;							// �g�r�a�t�B���^�[[ 0:RGB to HSI  1:HSI to RGB  2:HSB �� HLock ][ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	Mono ;									// ���m�g�[���t�B���^�[
	GRAPHICS_ANDROID_SHADER	Invert[ 2 ] ;							// �K�����]�t�B���^�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	Level[ 2 ] ;							// ���x���␳�t�B���^�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	TwoColor[ 2 ] ;							// �Q�l���t�B���^�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	Replacement[ 2 ] ;						// �F�̒u���t�B���^�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	GradientMap[ 2 ][ 2 ] ;					// �O���f�[�V�����}�b�v�t�B���^�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	PreMulAlpha ;							// �ʏ�摜�����Z�ς݃A���t�@�摜���쐬����ׂ̃t�B���^�[
	GRAPHICS_ANDROID_SHADER	InterpAlpha ;							// ��Z�ς݃A���t�@�摜����ʏ�摜���쐬����ׂ̃t�B���^�[
	GRAPHICS_ANDROID_SHADER	YUVtoRGB[ 4 ] ;							// YUV�J���[��RGB�J���[�ɕϊ�����t�B���^�[
	GRAPHICS_ANDROID_SHADER	Bicubic ;								// �o�C�L���[�r�b�N��ԃt�B���^�[
	GRAPHICS_ANDROID_SHADER	Lanczos3 ;								// Lanczos-3��ԃt�B���^�[

	GRAPHICS_ANDROID_SHADER	BasicBlend[ DX_GRAPH_BLEND_NUM ] ;		// ��{�I�ȃu�����h�t�B���^�[
	GRAPHICS_ANDROID_SHADER	RgbaMixBase[ 2 ] ;						// RGBAMix�u�����h��{[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	RgbaMixSRGBB[ 4 ][ 2 ] ;				// RGBAMix�u�����h�� A ���� BRGBA �̂S��[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	RgbaMixSRRRB[ 4 ][ 4 ][ 2 ] ;			// RGBAMix�u�����h�� SYYY BX �̂P�U�� [ Y ][ X ][ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_ANDROID_SHADER	RgbaMixS[ 4 ][ 4 ][ 4 ][ 4 ][ 2 ] ;		// RGBAMix�u�����h�� S �����̑g�ݍ��킹256��[ R ][ G ][ B ][ A ][ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
} ;

// �������ϐ��錾 --------------------------------------------------------------

extern GRAPHFILTER_SYSTEMIFNO_ANDR GraphFilterSystemInfoAndroid ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �t�B���^�[�Ŏg�p���Ă���S�ẴV�F�[�_�[���������
extern int GraphFilter_Android_ReleaseShaderAll( void ) ;

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_FILTER

#endif // DX_GRAPHICSFILTERANDROID_H

