// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�t�@�C���֌W�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.24b
// 
// -------------------------------------------------------------------------------

#ifndef DX_FILEANDROID_H
#define DX_FILEANDROID_H

// �C���N���[�h ------------------------------------------------------------------
#include "../DxCompileConfig.h"
#include "../DxThread.h"
#include <android/asset_manager.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// Android�p�t�@�C���A�N�Z�X�����p�\����
struct FILEACCESS_PF
{
	AAsset					*Asset ;							// �t�@�C���A�N�Z�X�p�A�Z�b�g
	FILE					*FilePointer ;						// �t�@�C���A�N�Z�X�p�t�@�C���|�C���^
} ;

// �t�@�C�����������p�\����
struct FINDINFO_PF
{
	AAssetDir				*AssetDir ;							// �f�B���N�g���A�N�Z�X�p�A�Z�b�g�f�B���N�g��
	DIR						*Dir ;								// �f�B���N�g���A�N�Z�X�p�f�B���N�g��
	wchar_t					SearchFileName[ 1024 ] ;			// �����t�@�C����
} ;

// �t�@�C���A�N�Z�X�������g�p����O���[�o���f�[�^�̊��ˑ��f�[�^�\����
struct FILEMANAGEDATA_PF
{
	AAssetManager *			AssetManagerP ;
	const char *			InternalDataPath ;
	int						InternalDataPathLength ;
	const char *			ExternalDataPath ;
	int						ExternalDataPathLength ;
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern void SetAssetManager( AAssetManager *AManager ) ;
extern void SetInternalAndExternalDataPath( const char *InternalDataPath, const char *ExternalDataPath ) ;

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_FILEANDROID_H
