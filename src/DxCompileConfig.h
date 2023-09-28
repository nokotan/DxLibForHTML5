// ----------------------------------------------------------------------------
//
//		�c�w���C�u�����@�R���p�C���R���t�B�O�w�b�_�t�@�C��
//
//				Ver 3.24b
//
// ----------------------------------------------------------------------------

/*
<<����>>
�@�@���̃w�b�_�t�@�C���� #define �̃R�����g�A�E�g��Ԃ�ύX���Ă��A
  �c�w���C�u�������̂̍ăR���p�C�����s��Ȃ��ƌ��ʂ͂���܂���B
*/

// ���d�C���N���[�h�h�~�p�}�N��
#ifndef DXCOMPILECONFIG_H
#define DXCOMPILECONFIG_H

// �X�^�e�B�b�N���C�u�������������C�u�����@�\�����p��` -----------------------

// C����p�Ƃ��ăR���p�C������ꍇ�͎��̃R�����g���O���Ă�������
//#define DX_COMPILE_TYPE_C_LANGUAGE

// namespace DxLib ���g�p���Ȃ��ꍇ�͎��̃R�����g���O���Ă�������
//#define DX_NON_NAMESPACE

// DxLib.h �ɏ�����Ă��� using namespace DxLib ; ���g�p���Ȃ��ꍇ�͎��̃R�����g���O���Ă�������
//#define DX_NON_USING_NAMESPACE_DXLIB

// �C�����C���A�Z���u�����g�p���Ȃ��\�[�X�R�[�h�ŃR���p�C������ꍇ�͈ȉ��̃R�����g�A�E�g���O���Ă�������
#define DX_NON_INLINE_ASM

// �c�w���C�u�����̃v���O�������當�������ؔr������ꍇ�̓R�����g���O���Ă�������
// (�o�C�i���G�f�B�^�Ŏ��s�t�@�C�����J���Ă��c�w���C�u�������g�p���Ă��邱�Ƃ��������Ȃ�܂�(�悭���ׂ�Γ��R������܂���)
//  ���݂ɁA�G���[�o�͂���؂���Ȃ��Ȃ�܂��̂ŊǗ��l�̑Ή����Ɏx�����������������܂���)
// #define DX_NON_LITERAL_STRING

// ���ׂĂ̊֐����X���b�h�Z�[�t�ɂ���ꍇ�̓R�����g���O���Ă�������
// #define DX_THREAD_SAFE

// �l�b�g���[�N�֘A�̊֐������X���b�h�Z�[�t�ɂ���ꍇ�̓R�����g���O���ĉ�����
// #define DX_THREAD_SAFE_NETWORK_ONLY

// �c�w�A�[�J�C�u������Ȃ����͎��̃R�����g���O���Ă�������
// ( �c�w�A�[�J�C�u�𖳌��ɂ���ƁA�c�w�A�[�J�C�u������Ŏg���Ă���֌W�� DX_NON_MODEL �� DX_NON_FILTER �� DX_NON_MOVIE �� DX_NON_NORMAL_DRAW_SHADER ���L���ɂȂ�܂� )
// #define DX_NON_DXA

// ���[�r�[�@�\������Ȃ����͎��̃R�����g���O���Ă�������
// #define DX_NON_MOVIE

// �a�l�o�摜�̓ǂݍ��݋@�\������Ȃ����͎��̃R�����g���O���Ă�������
// #define DX_NON_BMPREAD

// �s�f�`�摜�̓ǂݍ��݋@�\������Ȃ����͎��̃R�����g���O���Ă�������
// #define DX_NON_TGA

// �i�o�d�f�摜�̓ǂ݂��݋@�\������Ȃ����͎��̃R�����g���O���Ă�������
// ��DxUseCLib.lib ���ăR���p�C������K�v������܂�
// #define DX_NON_JPEGREAD

// �o�m�f�摜�̓ǂ݂��݋@�\������Ȃ����͎��̃R�����g���O���Ă�������
// ��DxUseCLib.lib ���ăR���p�C������K�v������܂�
// #define DX_NON_PNGREAD

// �s�h�e�e�摜�̓ǂ݂��݋@�\������Ȃ����͎��̃R�����g���O���Ă�������
// ��DxUseCLib.lib ���ăR���p�C������K�v������܂�
#define DX_NON_TIFFREAD

// GraphFilter �� GraphBlend ���g�p���Ȃ����͎��̃R�����g���O���ĉ�����
// #define DX_NON_FILTER

// �ʏ�`��Ƀv���O���}�u���V�F�[�_�[���g�p���Ȃ����͎��̃R�����g���O���Ă�������
// #define DX_NON_NORMAL_DRAW_SHADER

// �O���t�B�b�N�X����������Ȃ����͎��̃R�����g���O���Ă�������
// #define DX_NON_GRAPHICS

// �\�t�g�E�G�A�Q�c�`�悪����Ȃ����͎��̃R�����g���O���Ă�������
#define DX_NON_2DDRAW

// �W�� WAVE �t�@�C���ȊO�̉����t�@�C�����g�p���Ȃ����͎��̃R�����g���O���Ă�������
//#define DX_NON_ACM

// �W�� WAVE �t�@�C�����g�p���Ȃ����͎��̃R�����g���O���Ă�������
// #define DX_NON_WAVE

// DirectShow ���g�p���� MP3 �t�@�C���̃f�R�[�h���s��Ȃ��ꍇ�͎��̃R�����g���͂����Ă�������
//#define DX_NON_DSHOW_MP3

// DirectShow ���g�p��������t�@�C���̃f�R�[�h���s��Ȃ��ꍇ�͎��̃R�����g���͂����Ă�������
//#define DX_NON_DSHOW_MOVIE

// Media Foundation ���g�p��������t�@�C���̃f�R�[�h���s��Ȃ��ꍇ�͎��̃R�����g���͂����Ă�������
//#define DX_NON_MEDIA_FOUNDATION

// �L�[�{�[�h�̊�{�I�ȓ��͋@�\�ȊO�͂���Ȃ����͎��̃R�����g���O���Ă�������
//#define DX_NON_KEYEX

// ��������͋@�\�͂���Ȃ����͎��̃R�����g���O���ĉ�����
//#define DX_NON_INPUTSTRING

// �ʐM�@�\������Ȃ����͎��̃R�����g���O���Ă�������
#define DX_NON_NETWORK

// �}�X�N�@�\������Ȃ����͎��̃R�����g���O���Ă�������
// #define DX_NON_MASK

// �n���� �u���������� �f�[�^���g�p���Ȃ����͎��̃R�����g���͂����Ă�������
// ��DxUseCLib.lib ���ăR���p�C������K�v������܂�
// #define DX_NON_OGGVORBIS

// �n���� �s���������� �f�[�^���g�p���Ȃ����͎��̃R�����g���͂����Ă�������
// ��DxUseCLib.lib ���ăR���p�C������K�v������܂�
#define DX_NON_OGGTHEORA

// Opus �f�[�^���g�p���Ȃ����͎��̃R�����g���͂����Ă�������
// ��DxUseCLib.lib ���ăR���p�C������K�v������܂�
#define DX_NON_OPUS

// ASIO ���g�p���Ȃ����͎��̃R�����g���͂����Ă�������
#define DX_NON_ASIO

// ����������� Mersenne Twister ���g�p���Ȃ��ꍇ�͈ȉ��̃R�����g���O���ĉ�����
// ��DxUseCLib.lib ���ăR���p�C������K�v������܂�
//#define DX_NON_MERSENNE_TWISTER

// �c�w���C�u�������̊m�ۃ������̃_���v�@�\��L���ɂ���ꍇ�͎��̃R�����g���O���Ă�������
// #define DX_USE_DXLIB_MEM_DUMP

// ���f���f�[�^�������@�\���g�p���Ȃ����͎��̃R�����g���O���Ă�������
// #define DX_NON_MODEL

// Bullet Physics �������N���Ȃ��ꍇ�͎��̃R�����g���O���Ă�������
// ��DxUseCLib.lib ���ăR���p�C������K�v������܂�
// #define DX_NON_BULLET_PHYSICS

// �e�a�w�t�@�C����ǂݍ��ދ@�\���g�p������͎��̃R�����g���O���Ă�������( �g�p�ɂ� FBX SDK �̃Z�b�g�A�b�v���K�v�ł� )
//#define DX_LOAD_FBX_MODEL

// �r�[�v���@�\������Ȃ����͎��̃R�����g���O���Ă�������
//#define DX_NON_BEEP

// �^�X�N�X�C�b�`���n�e�e�ɂ���@�\������Ȃ����͎��̃R�����g���O���Ă�������
// ( �^�X�N�X�C�b�`�n�e�e�@�\�͎g�p�s�ł� )
//#define DX_NON_STOPTASKSWITCH

// ���O�o�͂��s��Ȃ��ꍇ�͎��̃R�����g���O���ĉ�����
//#define DX_NON_LOG

// printfDx �𖳌��ɂ���ꍇ�͎��̃R�����g���O���ĉ�����
//#define DX_NON_PRINTF_DX

// �񓯊��ǂݍ��݂𖳌��ɂ���ꍇ�͎��̃R�����g���O���ĉ�����
//#define DX_NON_ASYNCLOAD

// �t�@�C���ۑ��@�\�𖳌��ɂ���ꍇ�͎��̃R�����g���O���ĉ�����
//#define DX_NON_SAVEFUNCTION

// �\�t�g�E�F�A�ň����C���[�W�𖳌��ɂ���ꍇ�͎��̃R�����g���O���ĉ�����
// #define DX_NON_SOFTIMAGE

// �t�H���g�`��@�\�𖳌��ɂ���ꍇ�͎��̃R�����g���O���ĉ�����
//#define DX_NON_FONT

// �u���E�U�ˑ��̃t�H���g�`��@�\��L���ɂ���ꍇ�͎��̃R�����g���O���ĉ�����
// #define DX_USE_BROWSER_FONT

// �T�E���h�Đ��@�\( �\�t�g�E�G�A�T�E���h�AMIDI�܂� )�𖳌��ɂ���ꍇ�͎��̃R�����g���O���ĉ�����
//#define DX_NON_SOUND

// ���͋@�\�𖳌��ɂ���ꍇ�͎��̃R�����g���O���ĉ�����
//#define DX_NON_INPUT

// �}���`�X���b�h���g�p���Ȃ��ꍇ�͎��̃R�����g���O���Ă�������
//#define DX_NON_MULTITHREAD

// �e�n���h���̃G���[�`�F�b�N�𖳌��ɂ���ꍇ�͎��̃R�����g���O���Ă�������( �኱��������������ɖ����ȃn���h�����֐��ɓn���Ƒ��s���ȃ������A�N�Z�X�G���[����������悤�ɂȂ�܂� )
// #define DX_NON_HANDLE_ERROR_CHECK

// Direct3D11 ���g�p���Ȃ��ꍇ�͈ȉ��̃R�����g���O���Ă�������( ���݊J�����Ȃ̂ŁA�K���R�����g���O������Ԃɂ��Ă������� )
#define DX_NON_DIRECT3D11

// Direct3D9 ���g�p���Ȃ��ꍇ�͈ȉ��̃R�����g���O���Ă�������
#define DX_NON_DIRECT3D9

// �y�ʃo�[�W�����̂c�w���C�u�����𐶐�����ꍇ�͎��̃R�����g���O���Ă�������
// #define DX_LIB_LITEVER

// �R���p�C���ς݂̃V�F�[�_�[�o�C�i�����g�p�����A�V�F�[�_�[�R�[�h�̎��s���R���p�C���𗘗p����ꍇ�͎��̃R�����g���O���Ă�������
//#define DX_NON_SHADERCODE_BINARY

// Live2D Cubism 4 �֘A�̋@�\���g�p���Ȃ��ꍇ�͎��̃R�����g���O���Ă�������
#define DX_NON_LIVE2D_CUBISM4

// �E�B���h�E���쐬���Ȃ��ꍇ�͎��̃R�����g���O���Ă�������
//#define DX_NON_WINDOW

#ifndef __cplusplus
	#ifndef DX_COMPILE_TYPE_C_LANGUAGE
		#define DX_COMPILE_TYPE_C_LANGUAGE
	#endif // DX_COMPILE_TYPE_C_LANGUAGE
#endif // __cplusplus

#ifdef DX_COMPILE_TYPE_C_LANGUAGE
	#ifndef DX_NON_NAMESPACE
		#define DX_NON_NAMESPACE
	#endif // DX_NON_NAMESPACE
#endif // DX_COMPILE_TYPE_C_LANGUAGE

#ifndef __APPLE__
#ifndef __ANDROID__
#ifndef EMSCRIPTEN
	#define WINDOWS_DESKTOP_OS
#endif // EMSCRIPTEN
#endif // __ANDROID__
#endif // __APPLE__

#if defined( DX_GCC_COMPILE ) || defined( __ANDROID__ ) || defined( __APPLE__ ) || defined( BC2_COMPILER ) || defined( EMSCRIPTEN )
	#define USE_ULL
#endif


#ifndef WINDOWS_DESKTOP_OS
	#ifndef DX_NON_BEEP
		#define DX_NON_BEEP
	#endif // DX_NON_BEEP
	#ifndef DX_NON_ACM
		#define DX_NON_ACM
	#endif // DX_NON_ACM
	#ifndef DX_NON_DSHOW_MP3
		#define DX_NON_DSHOW_MP3
	#endif // DX_NON_DSHOW_MP3
	#ifndef DX_NON_DSHOW_MOVIE
		#define DX_NON_DSHOW_MOVIE
	#endif // DX_NON_DSHOW_MOVIE
	#ifndef DX_NON_MEDIA_FOUNDATION
		#define DX_NON_MEDIA_FOUNDATION
	#endif // DX_NON_MEDIA_FOUNDATION
#endif // WINDOWS_DESKTOP_OS

#if defined( __ANDROID__ ) || defined( __APPLE__ ) || defined ( EMSCRIPTEN )
//#define DX_NON_2DDRAW
#define DX_NON_ACM
#define DX_NON_DSHOW_MP3
#define DX_NON_DSHOW_MOVIE
#define DX_NON_MEDIA_FOUNDATION
#define DX_NON_KEYEX
#define DX_NON_INPUTSTRING
#define DX_NON_NETWORK
#define DX_NON_STOPTASKSWITCH
#define DX_NON_DIRECT3D11
#define DX_NON_DIRECT3D9
#endif

// #ifdef EMSCRIPTEN
// #define DX_NON_MULTITHREAD
// #endif




#ifdef DX_LIB_LITEVER
#define DX_NON_ACM
#define DX_NON_2DDRAW
#define DX_NON_MOVIE
#define DX_NON_KEYEX
#define DX_NON_NETWORK
#define DX_NON_MASK
#define DX_NON_JPEGREAD
#define DX_NON_PNGREAD
#define DX_NON_TIFFREAD
#define DX_NON_BEEP
#define DX_NON_OGGVORBIS
#define DX_NON_OGGTHEORA
#define DX_NON_OPUS
#define DX_NON_MODEL
#define DX_NON_SHADERCODE_BINARY
#define DX_NON_INPUTSTRING
#endif

#ifdef DX_NON_WINDOW
	#ifndef DX_NON_GRAPHICS
		#define DX_NON_GRAPHICS
	#endif
	#ifndef DX_NON_SOUND
		#define DX_NON_SOUND
	#endif
	#ifndef DX_NON_INPUT
		#define DX_NON_INPUT
	#endif
	#ifndef DX_NON_NETWORK
		#define DX_NON_NETWORK
	#endif
#endif // DX_NON_WINDOW

#ifdef DX_NON_GRAPHICS
	#ifndef DX_NON_FONT
		#define DX_NON_FONT
	#endif
	#ifndef DX_NON_MOVIE
		#define DX_NON_MOVIE
	#endif
	#ifndef DX_NON_FILTER
		#define DX_NON_FILTER
	#endif
	#ifndef DX_NON_2DDRAW
		#define DX_NON_2DDRAW
	#endif
	#ifndef DX_NON_MASK
		#define DX_NON_MASK
	#endif
	#ifndef DX_NON_MODEL
		#define DX_NON_MODEL
	#endif
	#ifndef DX_NON_BULLET_PHYSICS
		#define DX_NON_BULLET_PHYSICS
	#endif
	#ifndef DX_NON_PRINTF_DX
		#define DX_NON_PRINTF_DX
	#endif
	#ifndef DX_NON_KEYEX
		#define DX_NON_KEYEX
	#endif
	#ifndef DX_NON_DIRECT3D11
		#define DX_NON_DIRECT3D11
	#endif
	#ifndef DX_NON_DIRECT3D9
		#define DX_NON_DIRECT3D9
	#endif
	#ifndef DX_NOTUSE_DRAWFUNCTION
		#define DX_NOTUSE_DRAWFUNCTION
	#endif
#endif // DX_NON_GRAPHICS

#ifdef DX_NON_SOUND
	#ifndef DX_NON_OPUS
		#define DX_NON_OPUS
	#endif
	#ifndef DX_NON_OGGVORBIS
		#define DX_NON_OGGVORBIS
	#endif
	#ifndef DX_NON_OGGTHEORA
		#define DX_NON_OGGTHEORA
	#endif
	#ifndef DX_NON_ACM
		#define DX_NON_ACM
	#endif
	#ifndef DX_NON_DSHOW_MP3
		#define DX_NON_DSHOW_MP3
	#endif
	#ifndef DX_NON_DSHOW_MOVIE
		#define DX_NON_DSHOW_MOVIE
	#endif
	#ifndef DX_NON_MEDIA_FOUNDATION
		#define DX_NON_MEDIA_FOUNDATION
	#endif
	#ifndef DX_NON_MOVIE
		#define DX_NON_MOVIE
	#endif
#endif // DX_NON_SOUND

#ifdef DX_NON_MULTITHREAD
	#ifndef DX_NON_ASYNCLOAD
		#define DX_NON_ASYNCLOAD
	#endif
	#ifdef DX_THREAD_SAFE
		#undef DX_THREAD_SAFE
	#endif
#endif

#ifdef DX_NON_INPUTSTRING
	#ifndef DX_NON_KEYEX
		#define DX_NON_KEYEX
	#endif
#endif

#ifdef DX_NON_DXA
	#ifndef DX_NON_NORMAL_DRAW_SHADER
		#define DX_NON_NORMAL_DRAW_SHADER
	#endif
	#ifndef DX_NON_MODEL
		#define DX_NON_MODEL
	#endif
	#ifndef DX_NON_FILTER
		#define DX_NON_FILTER
	#endif
	#ifndef DX_NON_MOVIE
		#define DX_NON_MOVIE
	#endif
#endif

#ifdef DX_NON_MOVIE
	#ifndef DX_NON_OGGTHEORA
		#define DX_NON_OGGTHEORA
	#endif
	#ifndef DX_NON_MEDIA_FOUNDATION
		#define DX_NON_MEDIA_FOUNDATION
	#endif // DX_NON_MEDIA_FOUNDATION
#endif

#ifdef DX_NON_INPUT
	#ifndef DX_NON_KEYEX
		#define DX_NON_KEYEX
	#endif
#endif

#ifdef DX_NON_FONT
	#ifndef DX_NON_PRINTF_DX
		#define DX_NON_PRINTF_DX
	#endif
	#ifndef DX_NON_KEYEX
		#define DX_NON_KEYEX
	#endif
#endif

#ifdef DX_NON_OGGVORBIS
	#ifndef DX_NON_OGGTHEORA
		#define DX_NON_OGGTHEORA
	#endif
	#ifndef DX_NON_OPUS
		#define DX_NON_OPUS
	#endif
#endif


#if defined( _WIN64 ) || defined( __LP64__ )
	#ifndef PLATFORM_64BIT
		#define PLATFORM_64BIT
	#endif
#endif



#if defined( _WIN64 ) || defined( __ANDROID__ ) || defined( __APPLE__ ) || defined( DX_GCC_COMPILE ) || defined( EMSCRIPTEN )
	#ifndef DX_NON_INLINE_ASM
		#define DX_NON_INLINE_ASM
	#endif
#endif




#include "DxDataType.h"

#endif // DXCOMPILECONFIG_H
