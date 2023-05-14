//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�}�X�N�f�[�^�Ǘ��v���O����
// 
//  	Ver 3.24b
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_MASK

// �C���N���[�h ---------------------------------------------------------------
#include "DxGraphicsAndroid.h"
#include "DxMaskAndroid.h"
#include "../DxModel.h"
#include "../DxSystem.h"
#include "../DxLog.h"
#include "../DxMask.h"
#include "../DxMemory.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` -----------------------------------------------------------------

// �\���̐錾 -----------------------------------------------------------------

// �f�[�^��` -----------------------------------------------------------------

MASKMANAGEDATA_ANDR MaskManageData_Android ;

// �֐��錾 -------------------------------------------------------------------

// �v���O���� -----------------------------------------------------------------

// ���ˑ��֐�

// �}�X�N�X�N���[�����쐬����֐�
extern	int			Mask_CreateScreenFunction_Timing0_PF( void )
{
	MASKANDR.MaskScreenOldFrameBuffer   = MASKANDR.MaskScreenFrameBuffer ;
	MASKANDR.MaskScreenOldTextureBuffer = MASKANDR.MaskScreenTextureBuffer ;
	MASKANDR.MaskScreenOldDepthBuffer   = MASKANDR.MaskScreenDepthBuffer ;

	if( MASKANDR.MaskImageTextureBuffer != 0 )
	{
		glDeleteTextures( 1, &MASKANDR.MaskImageTextureBuffer ) ;
		MASKANDR.MaskImageTextureBuffer = 0 ;
	}

	// ����I��
	return 0 ;
}

// �}�X�N�X�N���[�����쐬����֐�
extern	int			Mask_CreateScreenFunction_Timing1_PF( int Width, int Height )
{
	MASKANDR.MaskTextureSizeX = Width ;
	MASKANDR.MaskTextureSizeY = Height ;

	// �}�X�N�p�C���[�W�e�N�X�`���̍쐬
	if( MASKANDR.MaskImageTextureBuffer == 0 )
	{
		PIXELFORMAT_INFO_ANDR *PixelFormat ;

		PixelFormat = &g_AndroidPixelFormat[ GANDR.Device.Caps.MaskAlphaFormat ] ;
		glGenTextures( 1, &MASKANDR.MaskImageTextureBuffer ) ;
		glActiveTexture( GL_TEXTURE0 ) ;
		glBindTexture( GL_TEXTURE_2D, MASKANDR.MaskImageTextureBuffer ) ;

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ) ;

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ) ;

		if( PixelFormat->IsExtFormat )
		{
			glCompressedTexImage2D(
				GL_TEXTURE_2D,
				0,
				PixelFormat->InternalFormat,
				MASKANDR.MaskTextureSizeX,
				MASKANDR.MaskTextureSizeY,
				0,
				0,
				0
			) ;
		}
		else
		{
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				PixelFormat->InternalFormat,
				MASKANDR.MaskTextureSizeX,
				MASKANDR.MaskTextureSizeY,
				0,
				PixelFormat->Format,
				PixelFormat->Type,
				0
			) ;
		}

		// �}�X�N�p�C���[�W�̓]��
		{
			RECT SrcRect ;
			RECT DestRect ;
			BASEIMAGE MaskBaseImage ;
			BASEIMAGE AlphaBaseImage ;

			SrcRect.left   = 0 ;
			SrcRect.top    = 0 ;
			SrcRect.right  = MASKANDR.MaskTextureSizeX ;
			SrcRect.bottom = MASKANDR.MaskTextureSizeY ;
			DestRect = SrcRect ;

			_MEMSET( &AlphaBaseImage, 0, sizeof( AlphaBaseImage ) ) ;
			MaskBaseImage.ColorData			= *Graphics_Android_GetDataFormatColorData( GANDR.Device.Caps.MaskAlphaFormat ) ;
			MaskBaseImage.Width				= MASKANDR.MaskTextureSizeX ;
			MaskBaseImage.Height			= MASKANDR.MaskTextureSizeY ;
			MaskBaseImage.Pitch				= MASKD.MaskBufferPitch ;
			MaskBaseImage.GraphData			= MASKD.MaskBuffer ;
			MaskBaseImage.MipMapCount		= 0 ;
			MaskBaseImage.GraphDataCount	= 0 ;

			Graphics_Android_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
				&SrcRect,
				&DestRect,
				MASKANDR.MaskImageTextureBuffer,
				1,
				MASKANDR.MaskTextureSizeX,
				MASKANDR.MaskTextureSizeY,
				MASKANDR.MaskTextureSizeX,
				MASKANDR.MaskTextureSizeY,
				&MaskBaseImage,
				&AlphaBaseImage,
				GANDR.Device.Caps.MaskAlphaFormat,
				FALSE,
				FALSE,
				0,
				FALSE
			) ;
		}
	}

	// �}�X�N�p�X�N���[���e�N�X�`���̍쐬
	if( MASKANDR.MaskScreenFrameBuffer == 0 )
	{
		// Offscreen position framebuffer texture target
		glGenTextures( 1, &MASKANDR.MaskScreenTextureBuffer ) ;
		glActiveTexture( GL_TEXTURE0 ) ;
		glBindTexture( GL_TEXTURE_2D, MASKANDR.MaskScreenTextureBuffer ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ) ;
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, MASKANDR.MaskTextureSizeX, MASKANDR.MaskTextureSizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 0 ) ;

		glGenFramebuffers( 1, &MASKANDR.MaskScreenFrameBuffer ) ;
		glBindFramebuffer( GL_FRAMEBUFFER, MASKANDR.MaskScreenFrameBuffer ) ;

		// �����_�[�o�b�t�@���ʎq�𐶐����܂��B
		glGenRenderbuffers( 1, &MASKANDR.MaskScreenDepthBuffer ) ;

		// �����_�[�o�b�t�@���ʎq�ɑΉ����������_�[�o�b�t�@�I�u�W�F�N�g�𐶐����܂��B
		glBindRenderbuffer( GL_RENDERBUFFER, MASKANDR.MaskScreenDepthBuffer ) ;

		// �����_�[�o�b�t�@�̕��ƍ������w�肵�܂��B
		glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, MASKANDR.MaskTextureSizeX, MASKANDR.MaskTextureSizeY ) ;

		// �t���[���o�b�t�@�̃A�^�b�`�����g�Ƃ��ă����_�[�o�b�t�@���A�^�b�`���܂��B
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, MASKANDR.MaskScreenDepthBuffer ) ;

		// �t���[���o�b�t�@�̃A�^�b�`�����g�Ƃ��� 2D �e�N�X�`�����A�^�b�`���܂��B
		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, MASKANDR.MaskScreenTextureBuffer, 0 ) ;

		// �t���[���o�b�t�@�����S���ǂ����`�F�b�N���܂��B
		GLint status = glCheckFramebufferStatus( GL_FRAMEBUFFER ) ;
		if( status != GL_FRAMEBUFFER_COMPLETE )
		{
			DXST_LOGFILE_ADDUTF16LE( "\xde\x30\xb9\x30\xaf\x30\x28\x75\xd5\x30\xec\x30\xfc\x30\xe0\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�}�X�N�p�t���[���o�b�t�@�̍쐬�Ɏ��s���܂���\n" @*/ ) ;
			return -1 ;
		}
		glBindFramebuffer( GL_FRAMEBUFFER, 0 ) ;
	}

	// ����I��
	return 0 ;
}

// �}�X�N�X�N���[�����쐬����֐�
extern	int			Mask_CreateScreenFunction_Timing2_PF( int MaskBufferSizeXOld, int MaskBufferSizeYOld )
{
	RECT UpdateRect ;

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// �}�X�N�p�C���[�W�̓]��
	{
		RECT SrcRect ;
		RECT DestRect ;
		BASEIMAGE MaskBaseImage ;
		BASEIMAGE AlphaBaseImage ;

		SrcRect.left   = 0 ;
		SrcRect.top    = 0 ;
		SrcRect.right  = MASKANDR.MaskTextureSizeX ;
		SrcRect.bottom = MASKANDR.MaskTextureSizeY ;
		DestRect = SrcRect ;

		_MEMSET( &AlphaBaseImage, 0, sizeof( AlphaBaseImage ) ) ;
		MaskBaseImage.ColorData			= *Graphics_Android_GetDataFormatColorData( GANDR.Device.Caps.MaskAlphaFormat ) ;
		MaskBaseImage.Width				= MASKANDR.MaskTextureSizeX ;
		MaskBaseImage.Height			= MASKANDR.MaskTextureSizeY ;
		MaskBaseImage.Pitch				= MASKD.MaskBufferPitch ;
		MaskBaseImage.GraphData			= MASKD.MaskBuffer ;
		MaskBaseImage.MipMapCount		= 0 ;
		MaskBaseImage.GraphDataCount	= 0 ;

		Graphics_Android_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
			&SrcRect,
			&DestRect,
			MASKANDR.MaskImageTextureBuffer,
			1,
			MASKANDR.MaskTextureSizeX,
			MASKANDR.MaskTextureSizeY,
			MASKANDR.MaskTextureSizeX,
			MASKANDR.MaskTextureSizeY,
			&MaskBaseImage,
			&AlphaBaseImage,
			GANDR.Device.Caps.MaskAlphaFormat,
			FALSE,
			FALSE,
			0,
			FALSE
		) ;
	}

	// �}�X�N�p�X�N���[���e�N�X�`���ɍ��܂ł̓��e��]��
	UpdateRect.left   = 0 ;
	UpdateRect.top    = 0 ;
	UpdateRect.right  = MaskBufferSizeXOld ;
	UpdateRect.bottom = MaskBufferSizeYOld ;
	Graphics_Android_StretchRect(
		MASKANDR.MaskScreenOldTextureBuffer, MaskBufferSizeXOld,        MaskBufferSizeYOld,        &UpdateRect,
		MASKANDR.MaskScreenFrameBuffer,      MASKANDR.MaskTextureSizeX, MASKANDR.MaskTextureSizeY, &UpdateRect
	) ;

	// �����_�[�^�[�Q�b�g�ɂ���Ă�����ύX����
	if( GANDR.Device.State.TargetFrameBuffer == MASKANDR.MaskScreenOldFrameBuffer )
	{
		Graphics_Android_DeviceState_SetRenderTarget( MASKANDR.MaskScreenFrameBuffer, MASKANDR.MaskTextureSizeX, MASKANDR.MaskTextureSizeY ) ;
	}

	// �ȑO�̃}�X�N�X�N���[�������J��
	{
		if( MASKANDR.MaskScreenOldFrameBuffer != 0 )
		{
			glDeleteFramebuffers( 1, &MASKANDR.MaskScreenOldFrameBuffer ) ;
			MASKANDR.MaskScreenOldFrameBuffer = 0 ;
		}

		if( MASKANDR.MaskScreenOldTextureBuffer != 0 )
		{
			glDeleteTextures( 1, &MASKANDR.MaskScreenOldTextureBuffer ) ;
			MASKANDR.MaskScreenOldTextureBuffer = 0 ;
		}

		if( MASKANDR.MaskScreenOldDepthBuffer != 0 )
		{
			glDeleteRenderbuffers( 1, &MASKANDR.MaskScreenOldDepthBuffer ) ;
			MASKANDR.MaskScreenOldDepthBuffer = 0 ;
		}
	}

	// ����I��
	return 0 ;
}

// �}�X�N�X�N���[�����ꎞ�폜����
extern	int			Mask_ReleaseSurface_PF( void )
{
	if( MASKANDR.MaskImageTextureBuffer != 0 )
	{
		glDeleteTextures( 1, &MASKANDR.MaskImageTextureBuffer ) ;
		MASKANDR.MaskImageTextureBuffer = 0 ;
	}

	if( MASKANDR.MaskScreenFrameBuffer != 0 )
	{
		glDeleteFramebuffers( 1, &MASKANDR.MaskScreenFrameBuffer ) ;
		MASKANDR.MaskScreenFrameBuffer = 0 ;
	}

	if( MASKANDR.MaskScreenTextureBuffer != 0 )
	{
		glDeleteTextures( 1, &MASKANDR.MaskScreenTextureBuffer ) ;
		MASKANDR.MaskScreenTextureBuffer = 0 ;
	}

	if( MASKANDR.MaskScreenDepthBuffer != 0 )
	{
		glDeleteRenderbuffers( 1, &MASKANDR.MaskScreenDepthBuffer ) ;
		MASKANDR.MaskScreenDepthBuffer = 0 ;
	}

	return 0 ;
}

// �}�X�N�g�p���[�h��ύX
extern	int			Mask_SetUseMaskScreenFlag_PF( void )
{
	IMAGEDATA     *Image     = NULL ;
	SHADOWMAPDATA *ShadowMap = NULL ;

	// �`���̉摜�f�[�^�A�h���X���擾����
	if( GSYS.DrawSetting.ShadowMapDrawSetupRequest )
	{
		ShadowMap = Graphics_ShadowMap_GetData( GSYS.DrawSetting.ShadowMapDrawHandle ) ;
	}
	else
	{
		Image = Graphics_Image_GetData( GSYS.DrawSetting.TargetScreen[ 0 ] ) ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I������
	Graphics_Android_RenderEnd() ;

	// �`����ύX����

	// �}�X�N�T�[�t�F�X�����݂��Ă��Ċ��L���ȏꍇ�̓}�X�N�T�[�t�F�X��`��Ώۂɂ���
	if( MASKD.MaskValidFlag && MASKANDR.MaskScreenFrameBuffer )
	{
		Graphics_Android_DeviceState_SetRenderTarget( MASKANDR.MaskScreenFrameBuffer, MASKANDR.MaskTextureSizeX, MASKANDR.MaskTextureSizeY ) ;
	}
	else
	// �V���h�E�}�b�v���L���ȏꍇ�̓V���h�E�}�b�v��`��Ώۂɂ���
	if( ShadowMap )
	{
		Graphics_Android_DeviceState_SetRenderTarget( ShadowMap->PF->FrameBuffer, ShadowMap->PF->Texture.Width, ShadowMap->PF->Texture.Height ) ;
	}
	else
	// �`��\�摜���L���ȏꍇ�͕`��\�摜��`��Ώۂɂ���
	if( Image )
	{
		if( Image->Hard.Draw[ 0 ].Tex->PF->MSRenderTarget != 0 )
		{
			Graphics_Android_DeviceState_SetRenderTarget( Image->Hard.Draw[ 0 ].Tex->PF->MSRenderTarget, Image->Hard.Draw[ 0 ].Tex->PF->Texture.Width, Image->Hard.Draw[ 0 ].Tex->PF->Texture.Height ) ;
		}
		else
		{
			Graphics_Android_DeviceState_SetRenderTarget( Image->Hard.Draw[ 0 ].Tex->PF->FrameBuffer, Image->Hard.Draw[ 0 ].Tex->PF->Texture.Width, Image->Hard.Draw[ 0 ].Tex->PF->Texture.Height ) ;
		}
	}
	else
	// ����ȊO�̏ꍇ�̓T�u�o�b�N�o�b�t�@��`��Ώۂɂ���
	{
		Graphics_Android_DeviceState_SetRenderTarget( GANDR.Device.Screen.SubBackBufferFrameBuffer, GANDR.Device.Screen.SubBackBufferTextureSizeX, GANDR.Device.Screen.SubBackBufferTextureSizeY ) ;
	}

	// �g�p����y�o�b�t�@�̃Z�b�g�A�b�v
	Graphics_Screen_SetupUseZBuffer() ;

	// �r���[�|�[�g�����ɖ߂�
	GANDR.Device.DrawSetting.CancelSettingEqualCheck = TRUE ;
	Graphics_Android_DeviceState_SetViewportEasy(
		GSYS.DrawSetting.DrawArea.left,
		GSYS.DrawSetting.DrawArea.top,
		GSYS.DrawSetting.DrawArea.right,
		GSYS.DrawSetting.DrawArea.bottom
	) ;
	GANDR.Device.DrawSetting.CancelSettingEqualCheck = FALSE ;

	// ����I��
	return 0 ;
}

// �}�X�N���g�p�����`��̑O�ɌĂԊ֐�( ���łɃT�u�o�b�t�@���g�p�����`��G���A�@�\���g�p���Ă���ꍇ�̏���������Ă��܂��Ă���� )
extern	int			Mask_DrawBeginFunction_PF( RECT *Rect )
{
	IMAGEDATA     *Image     = NULL ;
	SHADOWMAPDATA *ShadowMap = NULL ;

	// �`���̉摜�f�[�^�A�h���X���擾����
	if( GSYS.DrawSetting.ShadowMapDraw == FALSE )
	{
		ShadowMap = Graphics_ShadowMap_GetData( GSYS.DrawSetting.ShadowMapDrawHandle ) ;
	}
	else
	{
		Image = Graphics_Image_GetData( GSYS.DrawSetting.TargetScreen[ 0 ] ) ;
	}

	// �}�X�N���g�p���Ă���Ƃ��̂ݓ��ʂȏ���������
	if( MASKD.MaskValidFlag && MASKANDR.MaskScreenFrameBuffer )
	{
		// �ŏI�o�͐�̌���
		
		// �`��\�摜���`���̏ꍇ�͂�����A����ȊO�̏ꍇ�̓T�u�o�b�N�o�b�t�@���g�p���Ă���ꍇ�̓T�u�o�b�N�o�b�t�@���A
		// �����ł͂Ȃ��ꍇ�̓o�b�N�o�b�t�@���o�͐�ɂ���
		if( ShadowMap )
		{
			MASKANDR.DestTargetTextureBuffer = ShadowMap->PF->Texture.TextureBuffer ;
			MASKANDR.DestTargetFrameBuffer   = ShadowMap->PF->FrameBuffer ;
			MASKANDR.DestTargetWidth         = ShadowMap->PF->Texture.Width ;
			MASKANDR.DestTargetHeight        = ShadowMap->PF->Texture.Height ;
		}
		else
		if( Image )
		{
			MASKANDR.DestTargetTextureBuffer = Image->Hard.Draw[ 0 ].Tex->PF->Texture.TextureBuffer ;
			if( Image->Hard.Draw[ 0 ].Tex->PF->MSRenderTarget != 0 )
			{
				MASKANDR.DestTargetFrameBuffer = Image->Hard.Draw[ 0 ].Tex->PF->MSRenderTarget ;
			}
			else
			{
				MASKANDR.DestTargetFrameBuffer = Image->Hard.Draw[ 0 ].Tex->PF->FrameBuffer ;
			}
			MASKANDR.DestTargetWidth  = Image->Hard.Draw[ 0 ].Tex->PF->Texture.Width ;
			MASKANDR.DestTargetHeight = Image->Hard.Draw[ 0 ].Tex->PF->Texture.Height ;
		}
		else
		{
			MASKANDR.DestTargetTextureBuffer = GANDR.Device.Screen.SubBackBufferTexture ;
			MASKANDR.DestTargetFrameBuffer   = GANDR.Device.Screen.SubBackBufferFrameBuffer ;
			MASKANDR.DestTargetWidth         = GANDR.Device.Screen.SubBackBufferTextureSizeX ;
			MASKANDR.DestTargetHeight        = GANDR.Device.Screen.SubBackBufferTextureSizeY ;
		}

		// �ŏI�o�͐悩��}�X�N�X�N���[���Ɍ��݂̕`��󋵂��R�s�[����
		Graphics_Android_StretchRect(
			MASKANDR.DestTargetTextureBuffer, MASKANDR.DestTargetWidth,  MASKANDR.DestTargetHeight, Rect,
			MASKANDR.MaskScreenFrameBuffer,   MASKANDR.MaskTextureSizeX, MASKANDR.MaskTextureSizeY, Rect
		) ; 
	}

	// ����I��
	return 0 ;
}

// �}�X�N���g�p�����`��̌�ɌĂԊ֐�( ���łɃT�u�o�b�t�@���g�p�����`��G���A�@�\���g�p���Ă���ꍇ�̏���������Ă��܂��Ă���� )
extern	int			Mask_DrawAfterFunction_PF( RECT *Rect )
{
	// �}�X�N���g�p���Ă���ꍇ�̂݃}�X�N�摜�ƍ������ē]��
	if( MASKD.MaskValidFlag && MASKANDR.MaskScreenFrameBuffer )
	{
		IMAGEDATA               *MaskScreenImage = NULL ;
		GLuint                  MaskImageTextureBuffer ;
		int						MaskImageTextureWidth ;
		int						MaskImageTextureHeight ;
		GRAPHICS_ANDROID_SHADER *MaskShader ;
		int                     AlphaBlend ;

		// �}�X�N�p�O���t�B�b�N�n���h�����L���ȏꍇ�̓}�X�N�p�O���t�B�b�N�n���h���̏����擾����
		if( MASKD.MaskScreenGraphHandle != 0 )
		{
			MaskScreenImage = Graphics_Image_GetData( MASKD.MaskScreenGraphHandle ) ;

			// ���ɖ����ɂȂ��Ă�����ݒ�� 0 �ɂ���
			if( MaskScreenImage == NULL )
			{
				MASKD.MaskScreenGraphHandle = 0 ;
			}
		}

		// �g�p����}�X�N�C���[�W�e�N�X�`�����Z�b�g
		if( MaskScreenImage != NULL )
		{
			MaskImageTextureBuffer = MaskScreenImage->Hard.Draw[ 0 ].Tex->PF->Texture.TextureBuffer ;
			MaskImageTextureWidth  = MaskScreenImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width ;
			MaskImageTextureHeight = MaskScreenImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height ;
			MaskShader     = MASKD.MaskReverseEffectFlag ?
				&GANDR.Device.Shader.Base.MaskEffect_UseGraphHandle_ReverseEffect_Shader[ MASKD.MaskScreenGraphHandleUseChannel ] :
				&GANDR.Device.Shader.Base.MaskEffect_UseGraphHandle_Shader[ MASKD.MaskScreenGraphHandleUseChannel ] ;
			AlphaBlend             = TRUE ;
		}
		else
		{
			MaskImageTextureBuffer = MASKANDR.MaskImageTextureBuffer ;
			MaskImageTextureWidth  = MASKANDR.MaskTextureSizeX ;
			MaskImageTextureHeight = MASKANDR.MaskTextureSizeY ;
			MaskShader             = MASKD.MaskReverseEffectFlag ? &GANDR.Device.Shader.Base.MaskEffect_ReverseEffect_Shader : &GANDR.Device.Shader.Base.MaskEffect_Shader ;
			AlphaBlend             = FALSE ;
		}

		Graphics_Android_StretchRect(
			MASKANDR.MaskScreenTextureBuffer, MASKANDR.MaskTextureSizeX, MASKANDR.MaskTextureSizeY, Rect,
			MASKANDR.DestTargetFrameBuffer,   MASKANDR.DestTargetWidth,  MASKANDR.DestTargetHeight, Rect,
			GL_NEAREST,
			AlphaBlend,
			MaskShader,
			MaskImageTextureBuffer,           MaskImageTextureWidth,     MaskImageTextureHeight,    Rect
		) ;
	}

	return 0 ;
}

// �}�X�N�X�N���[�����w��̐F�œh��Ԃ�
extern	int			Mask_FillMaskScreen_PF( int Flag )
{
//	int i ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I������
	Graphics_Android_RenderEnd() ;

	// �}�X�N�p�C���[�W�̓]��
	{
		RECT SrcRect ;
		RECT DestRect ;
		BASEIMAGE MaskBaseImage ;
		BASEIMAGE AlphaBaseImage ;

		SrcRect.left   = 0 ;
		SrcRect.top    = 0 ;
		SrcRect.right  = MASKANDR.MaskTextureSizeX ;
		SrcRect.bottom = MASKANDR.MaskTextureSizeY ;
		DestRect = SrcRect ;

		_MEMSET( &AlphaBaseImage, 0, sizeof( AlphaBaseImage ) ) ;
		MaskBaseImage.ColorData			= *Graphics_Android_GetDataFormatColorData( GANDR.Device.Caps.MaskAlphaFormat ) ;
		MaskBaseImage.Width				= MASKANDR.MaskTextureSizeX ;
		MaskBaseImage.Height			= MASKANDR.MaskTextureSizeY ;
		MaskBaseImage.Pitch				= MASKD.MaskBufferPitch ;
		MaskBaseImage.GraphData			= MASKD.MaskBuffer ;
		MaskBaseImage.MipMapCount		= 0 ;
		MaskBaseImage.GraphDataCount	= 0 ;

		Graphics_Android_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
			&SrcRect,
			&DestRect,
			MASKANDR.MaskImageTextureBuffer,
			1,
			MASKANDR.MaskTextureSizeX,
			MASKANDR.MaskTextureSizeY,
			MASKANDR.MaskTextureSizeX,
			MASKANDR.MaskTextureSizeY,
			&MaskBaseImage,
			&AlphaBaseImage,
			GANDR.Device.Caps.MaskAlphaFormat,
			FALSE,
			FALSE,
			0,
			FALSE
		) ;
	}

	return 0 ;
}

// �w��̈�̃}�X�N�C���[�W�e�N�X�`�����X�V����
extern	int			Mask_UpdateMaskImageTexture_PF( RECT *Rect )
{
//	int i ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I������
	Graphics_Android_RenderEnd() ;

	// �}�X�N�p�C���[�W�̓]��
	{
		BASEIMAGE MaskBaseImage ;
		BASEIMAGE AlphaBaseImage ;

		_MEMSET( &AlphaBaseImage, 0, sizeof( AlphaBaseImage ) ) ;
		MaskBaseImage.ColorData			= *Graphics_Android_GetDataFormatColorData( GANDR.Device.Caps.MaskAlphaFormat ) ;
		MaskBaseImage.Width				= MASKANDR.MaskTextureSizeX ;
		MaskBaseImage.Height			= MASKANDR.MaskTextureSizeY ;
		MaskBaseImage.Pitch				= MASKD.MaskBufferPitch ;
		MaskBaseImage.GraphData			= MASKD.MaskBuffer ;
		MaskBaseImage.MipMapCount		= 0 ;
		MaskBaseImage.GraphDataCount	= 0 ;

		Graphics_Android_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
			Rect,
			Rect,
			MASKANDR.MaskImageTextureBuffer,
			1,
			MASKANDR.MaskTextureSizeX,
			MASKANDR.MaskTextureSizeY,
			MASKANDR.MaskTextureSizeX,
			MASKANDR.MaskTextureSizeY,
			&MaskBaseImage,
			&AlphaBaseImage,
			GANDR.Device.Caps.MaskAlphaFormat,
			FALSE,
			FALSE,
			0,
			FALSE
		) ;
	}

	return 0 ;
}






#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_MASK
