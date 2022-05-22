// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�t�H���g�֌W�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

#ifndef DX_FONTANDROID_H
#define DX_FONTANDROID_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_FONT

// �C���N���[�h ------------------------------------------------------------------
#include "../DxFile.h"
#include <jni.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

#define FSYSANDR			FontSystemAndroid

// �\���̒�` --------------------------------------------------------------------

// Android�p �t�H���g�L���b�V���̊��ˑ��Ǘ��f�[�^
struct FONTMANAGE_PF
{
	int						ReferenceNumUp ;						// Java�I�u�W�F�N�g�̎Q�Ɛ��𑝂₵�Ă��邩

	jobject					object_Bitmap ;							// �����̏o�͌��ʂ��ꎞ�I�ɕۑ����� Bitmap
	jobject					object_Canvas ;							// �����̏o�͂��s�����߂� Canvas
	jobject					object_Paint ;							// �����̏o�͂��s�����߂� Paint
	jobject					object_Typeface ;						// �����̃t�H���g�^�C�v�Ȃǂ��w�肷�邽�߂� Typeface
	jobject					object_OldTypeface ;					// Paint �ɍŏ�����ݒ肳��Ă��� Typeface

	jint					BitmapSizeX ;							// �����̏o�͌��ʂ��ꎞ�I�ɕۑ����� Bitmap �̃T�C�YX
	jint					BitmapSizeY ;							// �����̏o�͌��ʂ��ꎞ�I�ɕۑ����� Bitmap �̃T�C�YY
	jintArray				intArray_ClearBitmapBuffer ;			// �����̏o�͌��ʂ� Bitmap ���N���A���邽�߂� int�z��
	jintArray				intArray_BitmapBuffer ;					// �����̏o�͌��ʂ��擾���邽�߂� int�z��
	void					*ImageBuffer ;							// �����̏o�͌��ʂ��e�N�X�`���ɓ]������`�ɂ������̂�ۑ����邽�߂̃o�b�t�@

	float					PaintFontMetrics_ascent ;				// �g�p����t�H���g�� ascent
	float					PaintFontMetrics_bottom ;				// �g�p����t�H���g�� bottom
	float					PaintFontMetrics_descent ;				// �g�p����t�H���g�� descent
	float					PaintFontMetrics_leading ;				// �g�p����t�H���g�� leading
	float					PaintFontMetrics_top ;					// �g�p����t�H���g�� top
} ;

// Android�p �t�H���g�V�X�e���p�\����
struct FONTSYSTEM_ANDR
{
	int						Dummy ;
} ;

// �������ϐ��錾 --------------------------------------------------------------

extern FONTSYSTEM_ANDR FontSystemAndroid ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_FONT

#endif // DX_FONTANDROID_H
