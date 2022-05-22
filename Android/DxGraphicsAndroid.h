// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�`�揈���v���O����( Android )�w�b�_�t�@�C��
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

#ifndef DX_GRAPHICSANDROID_H
#define DX_GRAPHICSANDROID_H


#include "../DxCompileConfig.h"

#ifndef DX_NON_GRAPHICS

// �C���N���[�h ------------------------------------------------------------------
#include "../DxLib.h"
#include "../DxGraphics.h"
#include "../DxArchive_.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "DxShader_DataType_Android.h"
#include "DxShader_FS_Android.h"
#include "DxShader_VS_Android.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

#define GANDR										GraphicsHardDataAndroid

// Graphics_Android_DrawPreparation �֐��ɓn���t���O
#define DX_ANDROID_DRAWPREP_TRANS						(0x00001)
#define DX_ANDROID_DRAWPREP_VECTORINT					(0x00002)
#define DX_ANDROID_DRAWPREP_GOURAUDSHADE				(0x00008)
#define DX_ANDROID_DRAWPREP_PERSPECTIVE					(0x00010)
#define DX_ANDROID_DRAWPREP_DIFFUSERGB					(0x00020)
#define DX_ANDROID_DRAWPREP_DIFFUSEALPHA				(0x00040)
#define DX_ANDROID_DRAWPREP_FOG							(0x00080)
#define DX_ANDROID_DRAWPREP_NOBLENDSETTING				(0x00100)
#define DX_ANDROID_DRAWPREP_LIGHTING					(0x00200)
#define DX_ANDROID_DRAWPREP_SPECULAR					(0x00400)
#define DX_ANDROID_DRAWPREP_3D							(0x00800)
#define DX_ANDROID_DRAWPREP_TEXADDRESS					(0x01000)
#define DX_ANDROID_DRAWPREP_NOTSHADERRESET				(0x02000)
#define DX_ANDROID_DRAWPREP_CULLING						(0x04000)
#define DX_ANDROID_DRAWPREP_TEXTURE						(0x08000)
#define DX_ANDROID_DRAWPREP_TEXALPHACH					(0x10000)
#define DX_ANDROID_DRAWPREP_TEXALPHATEST				(0x20000)

// �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h
#define ANDROID_FS_ALPHATEST_CMP_GREATER				(0)				// �`��A���t�@�l���e�X�g�A���t�@�l���傫����Ε`��
#define ANDROID_FS_ALPHATEST_CMP_OTHER					(1)				// GREATER �ȊO�̔�r���[�h
#define ANDROID_FS_ALPHATEST_NUM						(2)

// GL Extensions
#define ANDROID_GL_EXTENSION_DEPTH24						(0)				// GL_OES_depth24
#define ANDROID_GL_EXTENSION_DEPTH32						(1)				// GL_OES_depth32
#define ANDROID_GL_EXTENSION_ELEMENT_INDEX_UNIT				(2)				// GL_OES_element_index_uint
#define ANDROID_GL_EXTENSION_TEXTURE_FLOAT					(3)				// GL_OES_texture_float
#define ANDROID_GL_EXTENSION_TEXTURE_FLOAT_LINEAR			(4)				// GL_OES_texture_float_linear
#define ANDROID_GL_EXTENSION_COMPRESSED_PALETTED_TEXTURE	(5)				// GL_OES_compressed_paletted_texture
#define ANDROID_GL_EXTENSION_COMPRESSED_ETC1_RGB8_TEXTURE	(6)				// GL_OES_compressed_ETC1_RGB8_texture
#define ANDROID_GL_EXTENSION_DEPTH_TEXTURE					(7)				// GL_OES_depth_texture
#define ANDROID_GL_EXTENSION_TEXTURE_HALF_FLOAT				(8)				// GL_OES_texture_half_float
#define ANDROID_GL_EXTENSION_TEXTURE_HALF_FLOAT_LINEAR		(9)				// GL_OES_texture_half_float_linear
#define ANDROID_GL_EXTENSION_VERTEX_HALF_FLOAT				(10)			// GL_OES_vertex_half_float
#define ANDROID_GL_EXTENSION_TEXTURE_3D						(11)			// GL_OES_texture_3D
#define ANDROID_GL_EXTENSION_TEXTURE_FORMAT_BGRA8888		(12)			// GL_EXT_texture_format_BGRA8888
#define ANDROID_GL_EXTENSION_NUM							(13)

// �s�N�Z���t�H�[�}�b�g
#define ANDROID_PIXEL_FORMAT_R8G8B8A8					(0)
#define ANDROID_PIXEL_FORMAT_R8G8B8						(1)
#define ANDROID_PIXEL_FORMAT_A4B4G4R4					(2)
#define ANDROID_PIXEL_FORMAT_A1B5G5R5					(3)
#define ANDROID_PIXEL_FORMAT_B5G6R5						(4)
#define ANDROID_PIXEL_FORMAT_R8G8B8_PAL4				(5)
#define ANDROID_PIXEL_FORMAT_R8G8B8_PAL8				(6)
#define ANDROID_PIXEL_FORMAT_R8G8B8A8_PAL4				(7)
#define ANDROID_PIXEL_FORMAT_R8G8B8A8_PAL8				(8)
#define ANDROID_PIXEL_FORMAT_A1B5G5R5_PAL4				(9)
#define ANDROID_PIXEL_FORMAT_A1B5G5R5_PAL8				(10)
#define ANDROID_PIXEL_FORMAT_R8							(11)
#define ANDROID_PIXEL_FORMAT_R16G16B16_FLOAT			(12)
#define ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT			(13)
#define ANDROID_PIXEL_FORMAT_R16G16B16A16_FLOAT			(14)
#define ANDROID_PIXEL_FORMAT_R32G32B32A32_FLOAT			(15)
#define ANDROID_PIXEL_FORMAT_NUM						(16)

// �W���`�撸�_�t�H�[�}�b�g
#define ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D				(0)				// ( VERTEX_NOTEX_2D                      �\���̌`�� )���C���A�{�b�N�X�`��p���_�t�H�[�}�b�g
#define ANDROID_VERTEX_INPUTLAYOUT_2D					(1)				// ( VERTEX2D or VERTEX_2D                �\���̌`�� )�g�����X�t�H�[���ςݒ��_�t�H�[�}�b�g
#define ANDROID_VERTEX_INPUTLAYOUT_BLENDTEX_2D			(2)				// ( VERTEX_BLENDTEX_2D or VERTEX2DSHADER �\���̌`�� )���u�����h�e�N�X�`���t���g�����X�t�H�[���ςݒ��_�t�H�[�}�b�g
#define ANDROID_VERTEX_INPUTLAYOUT_NOTEX_3D				(3)				// ( VERTEX_NOTEX_3D                      �\���̌`�� )���C���A�{�b�N�X�`��p���_�t�H�[�}�b�g�A�R�c�p( ���o�[�W�����p )
#define ANDROID_VERTEX_INPUTLAYOUT_3D					(4)				// ( VERTEX_3D                            �\���̌`�� )�O���t�B�b�N�X�`��p���_�t�H�[�}�b�g�A�R�c�p( ���o�[�W�����p )
#define ANDROID_VERTEX_INPUTLAYOUT_3D_LIGHT				(5)				// ( VERTEX3D                             �\���̌`�� )�O���t�B�b�N�X�`��p���_�t�H�[�}�b�g
#define ANDROID_VERTEX_INPUTLAYOUT_SHADER_3D			(6)				// ( VERTEX3DSHADER                       �\���̌`�� )�V�F�[�_�[�`��p���_�t�H�[�}�b�g
#define ANDROID_VERTEX_INPUTLAYOUT_NUM					(7)

// �`��^�C�v
#define ANDROID_RENDER_TYPE_NORMAL						(0)				// 0:�ʏ�`��
#define ANDROID_RENDER_TYPE_MUL							(1)				// 1:��Z�`��
#define ANDROID_RENDER_TYPE_INVERSE						(2)				// 2:RGB���]
#define ANDROID_RENDER_TYPE_X4							(3)				// 3:�`��P�x4�{
#define ANDROID_RENDER_TYPE_PMA_NORMAL					(4)				// 4:��Z�ς݃��u�����h���[�h�̒ʏ�`��
#define ANDROID_RENDER_TYPE_PMA_INVERSE					(5)				// 5:��Z�ς݃��u�����h���[�h��RGB���]
#define ANDROID_RENDER_TYPE_PMA_X4						(6)				// 6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{
#define ANDROID_RENDER_TYPE_NUM							(7)

// ���_�f�[�^
#define ANDROID_VERTEX_ATTR_POS_F2								(0)			// ���W( x, y )
#define ANDROID_VERTEX_ATTR_POS_F3								(1)			// ���W( x, y, z )
#define ANDROID_VERTEX_ATTR_POS_F4								(2)			// ���W( x, y, z, w )
#define ANDROID_VERTEX_ATTR_NRM									(3)			// �@��
#define ANDROID_VERTEX_ATTR_DIF									(4)			// �f�B�t���[�Y�J���[
#define ANDROID_VERTEX_ATTR_SPC									(5)			// �X�y�L�����J���[
#define ANDROID_VERTEX_ATTR_TEXUV0_F2							(6)			// �e�N�X�`�����W�O( x, y )
#define ANDROID_VERTEX_ATTR_TEXUV1_F2							(7)			// �e�N�X�`�����W�P( x, y )
#define ANDROID_VERTEX_ATTR_TEXUV2_F2							(8)			// �e�N�X�`�����W�Q( x, y )
#define ANDROID_VERTEX_ATTR_TEXUV3_F2							(9)			// �e�N�X�`�����W�R( x, y )
#define ANDROID_VERTEX_ATTR_TEXUV4_F2							(10)		// �e�N�X�`�����W�S( x, y )
#define ANDROID_VERTEX_ATTR_TEXUV5_F2							(11)		// �e�N�X�`�����W�T( x, y )
#define ANDROID_VERTEX_ATTR_TEXUV6_F2							(12)		// �e�N�X�`�����W�U( x, y )
#define ANDROID_VERTEX_ATTR_TEXUV7_F2							(13)		// �e�N�X�`�����W�V( x, y )
#define ANDROID_VERTEX_ATTR_TEXUV0_F4							(14)		// �e�N�X�`�����W�O( x, y, z, w )
#define ANDROID_VERTEX_ATTR_TEXUV1_F4							(15)		// �e�N�X�`�����W�P( x, y, z, w )
#define ANDROID_VERTEX_ATTR_TAN									(16)		// �ڐ�( ���[�J����� )
#define ANDROID_VERTEX_ATTR_BIN									(17)		// �]�@��( ���[�J����� )
#define ANDROID_VERTEX_ATTR_BLENDIND0							(18)		// �{�[�������p Float�^�萔�z��C���f�b�N�X�O
#define ANDROID_VERTEX_ATTR_BLENDWEIGHT0						(19)		// �{�[�������p�E�G�C�g�l�O
#define ANDROID_VERTEX_ATTR_BLENDIND1							(20)		// �{�[�������p Float�^�萔�z��C���f�b�N�X�P
#define ANDROID_VERTEX_ATTR_BLENDWEIGHT1						(21)		// �{�[�������p�E�G�C�g�l�P
#define ANDROID_VERTEX_ATTR_NUM									(22)
#define ANDROID_VERTEX_ATTR_OTHER								(-1)

// �V�F�[�_�[�̒萔���
#define ANDROID_SHADER_UNIFORM_SRC_TEX							(0)			// �\�[�X�e�N�X�`��
#define ANDROID_SHADER_UNIFORM_BLEND_TEX						(1)			// �u�����h�e�N�X�`��
#define ANDROID_SHADER_UNIFORM_DIF_MAP_TEX						(2)			// �f�B�t���[�Y�}�b�v�e�N�X�`��
#define ANDROID_SHADER_UNIFORM_NRM_MAP_TEX						(3)			// �@���}�b�v�e�N�X�`��
#define ANDROID_SHADER_UNIFORM_SPC_MAP_TEX						(4)			// �X�y�L�����}�b�v�e�N�X�`��
#define ANDROID_SHADER_UNIFORM_TOON_DIF_GRAD_TEX				(5)			// �g�D�[�������_�����O�p�f�B�t���[�Y�J���[�O���f�[�V�����e�N�X�`��
#define ANDROID_SHADER_UNIFORM_TOON_SPC_GRAD_TEX				(6)			// �g�D�[�������_�����O�p�X�y�L�����J���[�O���f�[�V�����e�N�X�`��
#define ANDROID_SHADER_UNIFORM_TOON_SPHERE_MAP_TEX				(7)			// �g�D�[�������_�����O�p�X�t�B�A�}�b�v�e�N�X�`��
#define ANDROID_SHADER_UNIFORM_TOON_RGB_TO_VMAXRGBVOL_TEX		(8)			// �g�D�[�������_�����O�pRGB�P�x�O�a�����p�{�����[���e�N�X�`��
#define ANDROID_SHADER_UNIFORM_SUB_TEX							(9)			// �T�u�e�N�X�`��
#define ANDROID_SHADER_UNIFORM_SHADOW_MAP0_TEX					(10)		// �V���h�E�}�b�v0�e�N�X�`��
#define ANDROID_SHADER_UNIFORM_SHADOW_MAP1_TEX					(11)		// �V���h�E�}�b�v1�e�N�X�`��
#define ANDROID_SHADER_UNIFORM_SHADOW_MAP2_TEX					(12)		// �V���h�E�}�b�v2�e�N�X�`��
#define ANDROID_SHADER_UNIFORM_AMB_EMI							(13)		// �G�~�b�V�u�J���[�{�A���r�G���g�J���[( �G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[ )
#define ANDROID_SHADER_UNIFORM_MAT_DIF							(14)		// �f�B�t���[�Y�J���[
#define ANDROID_SHADER_UNIFORM_MAT_SPC							(15)		// �X�y�L�����J���[
#define ANDROID_SHADER_UNIFORM_MAT_POW							(16)		// �X�y�L�����̋���
#define ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM0					(17)		// �}�e���A���p�����[�^0
#define ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM1					(18)		// �}�e���A���p�����[�^1
#define ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM2					(19)		// �}�e���A���p�����[�^2
#define ANDROID_SHADER_UNIFORM_LIGHT_POS						(20)		// ���W( �r���[��� )
#define ANDROID_SHADER_UNIFORM_LIGHT_DIR						(21)		// ����( �r���[��� )
#define ANDROID_SHADER_UNIFORM_LIGHT_DIF						(22)		// �f�B�t���[�Y�J���[
#define ANDROID_SHADER_UNIFORM_LIGHT_SPC						(23)		// �X�y�L�����J���[
#define ANDROID_SHADER_UNIFORM_LIGHT_AMB						(24)		// �A���r�G���g�J���[
#define ANDROID_SHADER_UNIFORM_LIGHT_RANGE_FALLOFF_AT0_AT1		(25)		// x:�L������  y:�X�|�b�g���C�g�pFllOff  z:�����ɂ�錸�������p�p�����[�^�O  w:�����ɂ�錸�������p�p�����[�^�P
#define ANDROID_SHADER_UNIFORM_LIGHT_AT2_SPOTP0_SPOTP1			(26)		// x:�����ɂ�錸�������p�p�����[�^�Q  y:�X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0 ) )  z:�X�|�b�g���C�g�p�p�����[�^�P( 1.0 / ( cos( Theta / 2.0 ) - cos( Phi / 2.0 ) ) )
#define ANDROID_SHADER_UNIFORM_ANTI_VIEW_PORT_MAT				(27)		// ���[���h�@���@�r���[�s��
#define ANDROID_SHADER_UNIFORM_VIEW_MAT							(28)		// ���[���h�@���@�r���[�s��
#define ANDROID_SHADER_UNIFORM_PROJ_MAT							(29)		// �r���[�@���@�v���W�F�N�V�����s��
#define ANDROID_SHADER_UNIFORM_FOG								(30)		// �t�H�O�p�p�����[�^( x:end/(end - start)  y:-1/(end - start)  z:density  w:���R�ΐ��̒� )
#define ANDROID_SHADER_UNIFORM_TOON_OUTLINE_SIZE				(31)		// �g�D�[���̗֊s���̑傫��
#define ANDROID_SHADER_UNIFORM_DIFSRC_SPCSRC_MULSPECOL			(32)		// x:�f�B�t���[�Y�J���[( 0.0:�}�e���A��  1.0:���_ )  y:�X�y�L�����J���[(   0.0:�}�e���A��  1.0:���_ )  z:�X�y�L�����J���[�l�ɏ�Z����l( �X�y�L�������������Ŏg�p )
#define ANDROID_SHADER_UNIFORM_SM_LVP_MAT						(33)		// �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������
#define ANDROID_SHADER_UNIFORM_TEX_MAT							(34)		// �e�N�X�`�����W����p�s��
#define ANDROID_SHADER_UNIFORM_LW_MAT							(35)		// ���[�J���@���@���[���h�s��
#define ANDROID_SHADER_UNIFORM_MUL_ALPHA_COLOR					(36)		// �J���[�ɃA���t�@�l����Z���邩�ǂ���( 0.0:��Z���Ȃ�  1.0:��Z���� )
#define ANDROID_SHADER_UNIFORM_ALPHA_TEST_REF					(37)		// ���e�X�g�l
#define ANDROID_SHADER_UNIFORM_ALPHA_TEST_CMPMODE				(38)
#define ANDROID_SHADER_UNIFORM_FOG_COLOR						(39)		// �t�H�O�J���[
#define ANDROID_SHADER_UNIFORM_FACTOR_COLOR						(40)		// �t�@�N�^�[�J���[
#define ANDROID_SHADER_UNIFORM_IGNORE_TEXTURE_COLOR				(41)		// �e�N�X�`���J���[���������p�J���[
#define ANDROID_SHADER_UNIFORM_ADD_COLOR						(42)		// ���Z�J���[
#define ANDROID_SHADER_UNIFORM_SHADOWMAP_LIGHT_ENABLE			(43)		// �V���h�E�}�b�v�O�E�P�E�Q�̃��C�g�L�����( x:�V���h�E�}�b�v�O�Ń��C�gn���L����  y:�V���h�E�}�b�v�P�Ń��C�gn���L����  z:�V���h�E�}�b�v�Q�Ń��C�gn���L���� )
#define ANDROID_SHADER_UNIFORM_SHADOWMAP_DADJ_GRAD				(44)		// �V���h�E�}�b�v�̏��( x:臒l�[�x�␳�l  y:�O���f�[�V�����͈�  )
#define ANDROID_SHADER_UNIFORM_NUM								(45)
#define ANDROID_SHADER_UNIFORM_OTHER							(-1)

// ���_�o�b�t�@�̃T�C�Y
#define DX_GLES2_VERTBUFFERSIZE							(64 * 1024)		// 64KB

// �V�F�[�_�[ Uniform �Z�b�g�̃w���p�[�}�N��
#define UNIFORM_SET_MATRIX4( index, _matrix4 )	glUniformMatrix4fv( (index), 1, GL_FALSE, _matrix4 ) ;
#define UNIFORM_SET_FLOAT4(  index, _float4  )	glUniform4f(        (index), _float4[ 0 ], _float4[ 1 ], _float4[ 2 ], _float4[ 3 ] ) ;
#define UNIFORM_SET_FLOAT3(  index, _float3  )	glUniform3f(        (index), _float3[ 0 ], _float3[ 1 ], _float3[ 2 ] ) ;
#define UNIFORM_SET_FLOAT2(  index, _float2  )	glUniform2f(        (index), _float2[ 0 ], _float2[ 1 ] ) ;
#define UNIFORM_SET_FLOAT1(  index, _float1  )	glUniform1f(        (index), _float1 ) ;
#define UNIFORM_SET_INT1(    index, _int1    )	glUniform1i(        (index), _int1   ) ;

// GRAPHICS_ANDROID_SHADER_LIST ��Ɋ܂܂�� GRAPHICS_ANDROID_SHADER �̐�
#define SHADERS_LIST_DATA_NUM							(256)

// �\���̒�` --------------------------------------------------------------------

// Android�p �e�N�X�`�����
struct GRAPHICS_ANDROID_TEXTURE
{
	GLuint							TextureBuffer ;							// �e�N�X�`���o�b�t�@
	int								MipMapCount ;							// �~�b�v�}�b�v��( Level0 �����Ȃ��ꍇ�� 1, Level1 �܂ł���ꍇ�� 2 )
	int								PixelFormat ;							// �e�N�X�`���̃s�N�Z���t�H�[�}�b�g( ANDROID_PIXEL_FORMAT_R8G8B8A8 �Ȃ� )
	GLuint							Width ;									// �e�N�X�`���̕�
	GLuint							Height ;								// �e�N�X�`���̍���
	GLint							MagFilter ;								// �g��t�B���^�[( GL_TEXTURE_MAG_FILTER �̃p�����[�^�A GL_NEAREST �Ȃ� )
	GLint							MinFilter ;								// �k���t�B���^�[( GL_TEXTURE_MIN_FILTER �̃p�����[�^�A GL_NEAREST �Ȃ� )
	GLint							WrapS ;									// �e�N�X�`���A�h���X���[�h�r( GL_TEXTURE_WRAP_S �̃p�����[�^�A GL_REPEAT �Ȃ� )
	GLint							WrapT ;									// �e�N�X�`���A�h���X���[�h�s( GL_TEXTURE_WRAP_T �̃p�����[�^�A GL_REPEAT �Ȃ� )
	GLint							WrapR ;									// �e�N�X�`���A�h���X���[�h�q( GL_TEXTURE_WRAP_R �̃p�����[�^�A GL_REPEAT �Ȃ� )
} ;

// Android�p �n�[�h�E�G�A�����_�����O�p�I���W�i���摜�e�N�X�`�����
struct IMAGEDATA_ORIG_HARD_TEX_PF
{
	GLuint							MSRenderTarget ;						// �}���`�T���v���p�����_�[�^�[�Q�b�g

	GLuint							FrameBuffer ;							// �t���[���o�b�t�@
	GRAPHICS_ANDROID_TEXTURE		Texture ;								// �e�N�X�`��
	GLuint							DepthBuffer ;							// �[�x�o�b�t�@
} ;

// Android�p �V���h�E�}�b�v���
struct SHADOWMAPDATA_PF
{
	GLuint							FrameBuffer ;							// �[�x�l�������ݗp�t���[���o�b�t�@
	GRAPHICS_ANDROID_TEXTURE		Texture ;								// �[�x�l�������ݗp�e�N�X�`��
	GLuint							DepthBuffer ;							// �[�x�o�b�t�@
} ;

// �s�N�Z���t�H�[�}�b�g�̏��
struct PIXELFORMAT_INFO_ANDR
{
	int								IsExtFormat ;							// �g���t�H�[�}�b�g���ǂ���
	int								PixelBits ;								// �P�s�N�Z��������̃r�b�g��
	int								AddDataBytes ;							// �ǉ����̃o�C�g��( �p���b�g���Ȃ� )
	GLint							InternalFormat ;						// GL_RGBA , GL_PALETTE4_RGB8_OES �Ȃ�
	GLenum							Format ;								// GL_RGBA �Ȃ�
	GLenum							Type ;									// GL_UNSIGNED_SHORT_4_4_4_4 �Ȃ�
} ;

// ���_�f�[�^�v�f�������̊�{���
struct VERTEXBUFFER_INPUT_ELEMENT_INFO_BASE_ANDR
{
	const GLchar *								AttrName ;					// �f�[�^��
	GLint										Size ;						// �f�[�^��
	GLenum										DataFormat ;				// �f�[�^�`��
	GLboolean									Normalized ;				// ���K�����邩�ǂ���
} ;

// ���_�f�[�^�v�f�������̏��
struct VERTEXBUFFER_INPUT_ELEMENT_INFO_ANDR
{
	int											ElementBase ;				// ���_��{���( ANDROID_VERTEX_ATTR_POS �Ȃ� )
	VERTEXBUFFER_INPUT_ELEMENT_INFO_BASE_ANDR *	OtherAttr ;					// �v���Z�b�g�ɂȂ����̏ꍇ�̎Q�Ɛ�( Attr �� ANDROID_VERTEX_ATTR_OTHER �̏ꍇ�Ɏg�p���� )
	GLuint										Offset ;					// �I�t�Z�b�g
} ;

// ���_�V�F�[�_�[�̓��͏��
struct VERTEXBUFFER_INPUT_INFO_ANDR
{
	GLuint										VertexDataSize ;			// ���_�f�[�^�������̃o�C�g��
	int											ElementInfoNum ;			// ���͒��_�f�[�^�̗v�f��
	VERTEXBUFFER_INPUT_ELEMENT_INFO_ANDR		ElementInfo[ 32 ] ;			// ���͒��_�f�[�^���
} ;

// Android�p ���_�o�b�t�@�n���h�����
struct VERTEXBUFFERHANDLEDATA_PF
{
	GLuint							VertexBuffer ;
} ;

// Android�p �C���f�b�N�X�o�b�t�@�n���h�����
struct INDEXBUFFERHANDLEDATA_PF
{
	GLuint							IndexBuffer ;
} ;

// Android �̃V�F�[�_�[��ӂ�̏���Z�߂��\����
struct GRAPHICS_ANDROID_SHADER
{
	GLuint							Shader ;
	GLushort						AttributeIndex[ ANDROID_VERTEX_ATTR_NUM ] ;		// �e���_�v�f�����Ԗڂ̗v�f�ƂȂ��Ă��邩�̏��( 0xffffffff �̏ꍇ�͂��̗v�f���Ȃ��Ƃ������� )
	GLushort						UniformIndex[ ANDROID_SHADER_UNIFORM_NUM ] ;	// �e�V�F�[�_�[�p�萔�v�f�����Ԗڂ̗v�f�ƂȂ��Ă��邩�̏��( 0xffffffff �̏ꍇ�͂��̗v�f���Ȃ��Ƃ������� )
	int								ApplyUniformUpdateCount ;						// �K�p����Ă���萔�̕ύX�o�[�W����
} ;

// Android�p �V�F�[�_�[�n���h�����
struct SHADERHANDLEDATA_PF
{
	GLuint							Shader ;
} ;

// Android�p �V�F�[�_�[�p�萔�o�b�t�@�n���h�����ˑ����̍\����
struct SHADERCONSTANTBUFFERHANDLEDATA_PF
{
	int								Dummy ;
} ;

// Android �̕W���`��p�̃V�F�[�_�[��Z�߂��\����
struct GRAPHICS_HARDWARE_ANDROID_SHADER_BASE
{
	// �W���`��p�̕��G�ȏ������s��Ȃ����_�V�F�[�_�[
	GLuint						BaseSimple_VS[ ANDROID_VERTEX_INPUTLAYOUT_NUM ] ;

	// �Œ�@�\�p�C�v���C���݊��̒��_�V�F�[�_�[( �e�N�X�`���Ȃ� )
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint						BaseNoneTex_FS[ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// �Œ�@�\�p�C�v���C���݊��̃V�F�[�_�[( �e�N�X�`���Ȃ� )
	// [ �W���`�撸�_�t�H�[�}�b�g ]
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*BaseNoneTex_Shader[ ANDROID_VERTEX_INPUTLAYOUT_NUM ][ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// �Œ�@�\�p�C�v���C���݊��̃t���O�����g�V�F�[�_�[( �e�N�X�`������ )
	// [ �u�����h�摜�Ƃ̃u�����h�^�C�v( 0:�Ȃ�  1:DX_BLENDGRAPHTYPE_NORMAL  2:DX_BLENDGRAPHTYPE_WIPE  3:DX_BLENDGRAPHTYPE_ALPHA ) ]
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �e�N�X�`��RGB����( 0:�������Ȃ�  1:�������� ) ]
	// [ �e�N�X�`��Alpha����( 0:�������Ȃ�  1:�������� ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint						BaseUseTex_FS[ 4 ][ ANDROID_RENDER_TYPE_NUM ][ 2 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ; 

	// �Œ�@�\�p�C�v���C���݊��̃V�F�[�_�[( �e�N�X�`������ )
	// [ �W���`�撸�_�t�H�[�}�b�g ]
	// [ �u�����h�摜�Ƃ̃u�����h�^�C�v( 0:�Ȃ�  1:DX_BLENDGRAPHTYPE_NORMAL  2:DX_BLENDGRAPHTYPE_WIPE  3:DX_BLENDGRAPHTYPE_ALPHA ) ]
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �e�N�X�`��RGB����( 0:�������Ȃ�  1:�������� ) ]
	// [ �e�N�X�`��Alpha����( 0:�������Ȃ�  1:�������� ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*BaseUseTex_Shader[ ANDROID_VERTEX_INPUTLAYOUT_NUM ][ 4 ][ ANDROID_RENDER_TYPE_NUM ][ 2 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// �}�X�N�����p�V�F�[�_�[
	GRAPHICS_ANDROID_SHADER		MaskEffect_Shader ;
	GRAPHICS_ANDROID_SHADER		MaskEffect_ReverseEffect_Shader ;
	GRAPHICS_ANDROID_SHADER		MaskEffect_UseGraphHandle_Shader[ 4 ] ;
	GRAPHICS_ANDROID_SHADER		MaskEffect_UseGraphHandle_ReverseEffect_Shader[ 4 ] ;

	// �P���]���p�V�F�[�_�[
	GLuint		StretchRect_VS ;
	GLuint		StretchRectTex2_VS ;
	GLuint		StretchRectTex8_VS ;
	GRAPHICS_ANDROID_SHADER		StretchRect_Shader ;

	// �����_�[�^�[�Q�b�g�N���A�p�V�F�[�_�[
	GRAPHICS_ANDROID_SHADER		ClearRT_Shader ;
} ;

// Android �̕W���R�c�`��p�̃V�F�[�_�[��Z�߂��\����
struct GRAPHICS_HARDWARE_ANDROID_SHADER_BASE3D
{
	// �W���R�c�`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̒��_�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	GLuint		Base3D_PixelLighting_VS[ 2 ][ 4 ] ;

	// �W���R�c�`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃t���O�����g�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ ���C�g�C���f�b�N�X ]
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		Base3D_PixelLighting_Normal_FS[ 2 ][ 84 ][ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// �W���R�c�`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃V�F�[�_�[( ���X�g�͔z��̍����� )
	// �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� )
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// �t���O�����g�V�F�[�_�[[ ���C�g�C���f�b�N�X ]
	// �t���O�����g�V�F�[�_�[[ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*Base3D_PixelLighting_Normal_Shader[ 2 ][ 4 ][ 84 ][ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// �W���R�c�`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p���_�V�F�[�_�[
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	GLuint		Base3D_ShadowMap_VS[ 2 ] ;

	// �W���R�c�`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p�t���O�����g�V�F�[�_�[
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		Base3D_ShadowMap_Normal_FS[ ANDROID_FS_ALPHATEST_NUM ] ;

	// �W���R�c�`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p�V�F�[�_�[
	// ���_�V�F�[�_�[[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*Base3D_ShadowMap_Normal_Shader[ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// �W���R�c�`��p�̃��C�e�B���O�Ȃ����_�V�F�[�_�[
	// [ �t�H�O�^�C�v ]
	GLuint		Base3D_NoLighting_VS[ 4 ] ;

	// �W���R�c�`��p�̃��C�e�B���O�Ȃ��t���O�����g�V�F�[�_�[
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		Base3D_NoLighting_Normal_FS[ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// �W���R�c�`��p�̃��C�e�B���O�Ȃ��V�F�[�_�[
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// �t���O�����g�V�F�[�_�[[ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*Base3D_NoLighting_Normal_Shader[ 4 ][ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// �W���R�c�`��p�̒��_�P�ʃ��C�e�B���O���_�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	// [ ���C�g�C���f�b�N�X ]
	GLuint		Base3D_VertexLighting_VS[ 2 ][ 4 ][ 20 ] ;

	// �W���R�c�`��p�̒��_�P�ʃ��C�e�B���O�t���O�����g�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ ���C�g�C���f�b�N�X ]
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		Base3D_VertexLighting_Normal_FS[ 2 ][ 10 ][ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// �W���R�c�`��p�̒��_�P�ʃ��C�e�B���O�V�F�[�_�[
	// �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� )
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// ���_�V�F�[�_�[[ ���C�g�C���f�b�N�X ]
	// �t���O�����g�V�F�[�_�[[ ���C�g�C���f�b�N�X ]
	// �t���O�����g�V�F�[�_�[[ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*Base3D_VertexLighting_Normal_Shader[ 2 ][ 4 ][ 20 ][ 10 ][ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;
} ;


#ifndef DX_NON_MODEL

// Android �̃��f���`��p�̃V�F�[�_�[��Z�߂��\����
struct GRAPHICS_HARDWARE_ANDROID_SHADER_MODEL
{
	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̒��_�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V�� 2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	GLuint		MV1_PixelLighting_VS[ 2 ][ 3 ][ 2 ][ 4 ] ;


	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃g�D�[���^�C�v�P�p�t���O�����g�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// [ �g�D�[�������_�����O�̃X�y�L�����O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]
	// [ �L���ȃ��C�g�̐� - 1 ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		MV1_PixelLighting_ToonType1_FS[ 2 ][ 2 ][ 2 ][ 2 ][ DX_ANDR_COMMON_CONST_LIGHT_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃g�D�[���^�C�v�P�p�V�F�[�_�[( ���X�g�͔z��̍����� )
	// �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� )
	// �o���v�}�b�v�̗L��( 0:���� 1:�L�� )
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V�� 2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�̃X�y�L�����O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// �t���O�����g�V�F�[�_�[[ �L���ȃ��C�g�̐� - 1 ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_PixelLighting_ToonType1_Shader[ 2 ][ 2 ][ 3 ][ 4 ][ 2 ][ 2 ][ DX_ANDR_COMMON_CONST_LIGHT_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃g�D�[���^�C�v�Q�p�t���O�����g�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖���   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ �L���ȃ��C�g�̐� - 1 ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		MV1_PixelLighting_ToonType2_FS[ 2 ][ 3 ][ DX_ANDR_COMMON_CONST_LIGHT_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃g�D�[���^�C�v�Q�p�V�F�[�_�[( ���X�g�͔z��̍����� )
	// �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� )
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V�� 2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖���   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// �t���O�����g�V�F�[�_�[[ �L���ȃ��C�g�̐� - 1 ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_PixelLighting_ToonType2_Shader[ 2 ][ 3 ][ 2 ][ 4 ][ 3 ][ DX_ANDR_COMMON_CONST_LIGHT_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃t���O�����g�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]
	// [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]
	// [ �L���ȃ��C�g�̐� - 1 ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		MV1_PixelLighting_Normal_FS[ 2 ][ 5 ][ 2 ][ DX_ANDR_COMMON_CONST_LIGHT_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃V�F�[�_�[( ���X�g�͔z��̍����� )
	// �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� )
	// �o���v�}�b�v�̗L��( 0:���� 1:�L�� )
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V�� 2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// �t���O�����g�V�F�[�_�[[ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]
	// �t���O�����g�V�F�[�_�[[ �L���ȃ��C�g�̐� - 1 ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_PixelLighting_Normal_Shader[ 2 ][ 2 ][ 3 ][ 4 ][ 5 ][ DX_ANDR_COMMON_CONST_LIGHT_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;






	// ���f���`��p�̃}�e���A���v�f�`��p�t���O�����g�V�F�[�_�[
	// �}�e���A���^�C�v( DX_MATERIAL_TYPE_MAT_SPEC_LUMINANCE_UNORM �Ȃ� )
	// �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h
	GLuint		MV1_MaterialType_FS[ DX_MATERIAL_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̃}�e���A���v�f�`��p�V�F�[�_�[
	// MV1_NoLighting_VS + MV1_MaterialType_FS
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// �t���O�����g�V�F�[�_�[[ �}�e���A���^�C�v( DX_MATERIAL_TYPE_MAT_SPEC_LUMINANCE_UNORM �Ȃ� ) ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_MaterialType_Shader[ 3 ][ 2 ][ DX_MATERIAL_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;




	// ���f���`��p�̃V���h�E�}�b�v�ւ̃g�D�[�������_�����O�֊s���`��p���_�V�F�[�_�[
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	GLuint		MV1_ToonOutLine_ShadowMap_VS[ 3 ][ 2 ] ;

	// ���f���`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p�V�F�[�_�[
	// MV1_ToonOutLine_ShadowMap_VS + MV1_ShadowMap_Normal_FS
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_ToonOutLine_ShadowMap_Shader[ 3 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// ���f���`��p�̃g�D�[�������_�����O�̗֊s���`��p���_�V�F�[�_�[
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	GLuint		MV1_ToonOutLine_VS[ 3 ][ 2 ][ 4 ] ;

	// ���f���`��p�̃��C�e�B���O�Ȃ��V�F�[�_�[
	// MV1_ToonOutLine_VS + MV1_NoLighting_Normal_FS[ 0 ]
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_ToonOutLine_Shader[ 3 ][ 2 ][ 4 ][ ANDROID_FS_ALPHATEST_NUM ] ;




	// ���f���`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p���_�V�F�[�_�[
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	GLuint		MV1_ShadowMap_VS[ 3 ][ 2 ] ;


	// ���f���`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p�t���O�����g�V�F�[�_�[
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		MV1_ShadowMap_Normal_FS[ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p�V�F�[�_�[
	// MV1_ShadowMap_VS + MV1_ShadowMap_Normal_FS
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_ShadowMap_Normal_Shader[ 3 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// ���f���`��p�̃V���h�E�}�b�v�ւ̃g�D�[�������_�����O�p�t���O�����g�V�F�[�_�[
	// [ �g�D�[�������_�����O�^�C�v( 0:�g�D�[�������_�����O type 1   1:�g�D�[�������_�����O type 2 ) ]
	// [ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖���   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		MV1_ShadowMap_Toon_FS[ 2 ][ 3 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̃V���h�E�}�b�v�ւ̃g�D�[�������_�����O�p�V�F�[�_�[
	// MV1_ShadowMap_VS + MV1_ShadowMap_Toon_FS
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�^�C�v( 0:�g�D�[�������_�����O type 1   1:�g�D�[�������_�����O type 2 ) ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖���   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_ShadowMap_Toon_Shader[ 3 ][ 2 ][ 2 ][ 3 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// ���f���`��p�̃��C�e�B���O�Ȃ����_�V�F�[�_�[
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	GLuint		MV1_NoLighting_VS[ 3 ][ 2 ][ 4 ] ;


	// ���f���`��p�̃��C�e�B���O�Ȃ��g�D�[���p�t���O�����g�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �g�D�[�������_�����O�^�C�v( 0:�g�D�[�������_�����O type 1   1:�g�D�[�������_�����O type 2 ) ]
	// [ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT or �g�D�[�������_�����O�ł͂Ȃ�  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		MV1_NoLighting_Toon_FS[ 2 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̃��C�e�B���O�Ȃ��g�D�[���p�V�F�[�_�[( ���X�g�͔z��̍����� )
	// MV1_NoLighting_VS + MV1_NoLighting_Toon_FS
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�^�C�v( 0:�g�D�[�������_�����O type 1   1:�g�D�[�������_�����O type 2 ) ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT or �g�D�[�������_�����O�ł͂Ȃ�  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_NoLighting_Toon_Shader[ 3 ][ 2 ][ 4 ][ 2 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// ���f���`��p�̃��C�e�B���O�Ȃ��t���O�����g�V�F�[�_�[
	// [ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		MV1_NoLighting_Normal_FS[ 5 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̃��C�e�B���O�Ȃ��V�F�[�_�[
	// MV1_NoLighting_VS + MV1_NoLighting_Normal_FS
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// �t���O�����g�V�F�[�_�[[ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_NoLighting_Normal_Shader[ 3 ][ 2 ][ 4 ][ 5 ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// ���f���`��p�̒��_�P�ʃ��C�e�B���O���蒸�_�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	// [ ���C�g�C���f�b�N�X ]
	GLuint		MV1_VertexLighting_VS[ 2 ][ 3 ][ 2 ][ 4 ][ 20 ] ;


	// ���f���`��p�̒��_�P�ʃ��C�e�B���O����g�D�[���^�C�v�P�p�t���O�����g�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// [ �g�D�[�������_�����O�̃X�y�L�����O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]
	// [ ���C�g�C���f�b�N�X ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		MV1_VertexLighting_ToonType1_FS[ 2 ][ 2 ][ 2 ][ 2 ][ 10 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̒��_�P�ʃ��C�e�B���O����g�D�[���^�C�v�P�p�V�F�[�_�[
	// �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� )
	// �o���v�}�b�v�̗L��( 0:���� 1:�L�� )
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// ���_�V�F�[�_�[[ ���C�g�C���f�b�N�X ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�̃X�y�L�����O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// �t���O�����g�V�F�[�_�[[ ���C�g�C���f�b�N�X ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_VertexLighting_ToonType1_Shader[ 2 ][ 2 ][ 3 ][ 4 ][ 20 ][ 2 ][ 2 ][ 10 ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// ���f���`��p�̒��_�P�ʃ��C�e�B���O����g�D�[���^�C�v�Q�p�t���O�����g�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖���   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ ���C�g�C���f�b�N�X ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		MV1_VertexLighting_ToonType2_FS[ 2 ][ 3 ][ 10 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̒��_�P�ʃ��C�e�B���O����g�D�[���^�C�v�Q�p�V�F�[�_�[
	// �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� )
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// ���_�V�F�[�_�[[ ���C�g�C���f�b�N�X ]
	// �t���O�����g�V�F�[�_�[[ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖���   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// �t���O�����g�V�F�[�_�[[ ���C�g�C���f�b�N�X ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_VertexLighting_ToonType2_Shader[ 2 ][ 3 ][ 2 ][ 4 ][ 20 ][ 3 ][ 10 ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// ���f���`��p�̒��_�P�ʃ��C�e�B���O����t���O�����g�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]
	// [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]
	// [ ���C�g�C���f�b�N�X ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GLuint		MV1_VertexLighting_Normal_FS[ 2 ][ 5 ][ 2 ][ 10 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̒��_�P�ʃ��C�e�B���O����V�F�[�_�[
	// �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� )
	// �o���v�}�b�v�̗L��( 0:���� 1:�L�� )
	// ���_�V�F�[�_�[[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// ���_�V�F�[�_�[[ �t�H�O�^�C�v ]
	// ���_�V�F�[�_�[[ ���C�g�C���f�b�N�X ]
	// �t���O�����g�V�F�[�_�[[ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]
	// �t���O�����g�V�F�[�_�[[ ���C�g�C���f�b�N�X ]
	// �t���O�����g�V�F�[�_�[[ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_ANDROID_SHADER		*MV1_VertexLighting_Normal_Shader[ 2 ][ 2 ][ 3 ][ 4 ][ 20 ][ 5 ][ 10 ][ ANDROID_FS_ALPHATEST_NUM ] ;
} ;
#endif // DX_NON_MODEL

// Android �̒萔����Z�߂��\����
struct GRAPHICS_HARDWARE_ANDROID_CONSTANT
{
	// ���_�V�F�[�_�[�A�t���O�����g�V�F�[�_�[����
	DX_ANDR_SHADER_FLOAT4			uAmb_Emi ;									// �G�~�b�V�u�J���[�{�A���r�G���g�J���[( �G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[ )

	DX_ANDR_SHADER_FLOAT4			uMatDif ;									// �f�B�t���[�Y�J���[
	DX_ANDR_SHADER_FLOAT4			uMatSpc ;									// �X�y�L�����J���[
	DX_ANDR_SHADER_FLOAT			uMatPow ;									// �X�y�L�����̋���
	DX_ANDR_SHADER_FLOAT			uMatTypeParam0 ;							// �^�C�v�p�����[�^0
	DX_ANDR_SHADER_FLOAT			uMatTypeParam1 ;							// �^�C�v�p�����[�^1
	DX_ANDR_SHADER_FLOAT			uMatTypeParam2 ;							// �^�C�v�p�����[�^2

	DX_ANDR_SHADER_FLOAT3			uLightPos[ 6 /* ���_�V�F�[�_�[�Ŏg�p����̂� 3 */ ] ;					// ���W( �r���[��� )
	DX_ANDR_SHADER_FLOAT3			uLightDir[ 6 /* ���_�V�F�[�_�[�Ŏg�p����̂� 3 */ ] ;					// ����( �r���[��� )
	DX_ANDR_SHADER_FLOAT4			uLightDif[ 6 /* ���_�V�F�[�_�[�Ŏg�p����̂� 3 */ ] ;					// �f�B�t���[�Y�J���[
	DX_ANDR_SHADER_FLOAT4			uLightSpc[ 6 /* ���_�V�F�[�_�[�Ŏg�p����̂� 3 */ ] ;					// �X�y�L�����J���[
	DX_ANDR_SHADER_FLOAT4			uLightAmb[ 6 /* ���_�V�F�[�_�[�Ŏg�p����̂� 3 */ ] ;					// �A���r�G���g�J���[
	DX_ANDR_SHADER_FLOAT4			uLightRange_FallOff_AT0_AT1[ 6 /* ���_�V�F�[�_�[�Ŏg�p����̂� 3 */ ] ;	// x:�L������  y:�X�|�b�g���C�g�pFllOff  z:�����ɂ�錸�������p�p�����[�^�O  w:�����ɂ�錸�������p�p�����[�^�P
	DX_ANDR_SHADER_FLOAT4			uLightAT2_SpotP0_SpotP1[ 6 /* ���_�V�F�[�_�[�Ŏg�p����̂� 3 */ ] ;		// x:�����ɂ�錸�������p�p�����[�^�Q  y:�X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0 ) )  z:�X�|�b�g���C�g�p�p�����[�^�P( 1.0 / ( cos( Theta / 2.0 ) - cos( Phi / 2.0 ) ) )


	// ���_�V�F�[�_�[�p
	DX_ANDR_SHADER_FLOAT4			uAntiVPMat[ 4 ] ;							// �r���[�|�[�g�s��̌��ʂ�ł������s��
	DX_ANDR_SHADER_FLOAT4			uViewMat[ 3 ] ;								// ���[���h�@���@�r���[�s��
	DX_ANDR_SHADER_FLOAT4			uProjMat[ 4 ] ;								// �r���[�@���@�v���W�F�N�V�����s��
	DX_ANDR_SHADER_FLOAT4			uFog ;										// �t�H�O�p�p�����[�^( x:end/(end - start)  y:-1/(end - start)  z:density  w:���R�ΐ��̒� )

	DX_ANDR_SHADER_FLOAT4			uToonOutLineSize ;							// �g�D�[���̗֊s���̑傫��
	DX_ANDR_SHADER_FLOAT4			uDifSrc_SpeSrc_MulSpeCol ;					// x:�f�B�t���[�Y�J���[( 0.0:�}�e���A��  1.0:���_ )  y:�X�y�L�����J���[(   0.0:�}�e���A��  1.0:���_ )  z:�X�y�L�����J���[�l�ɏ�Z����l( �X�y�L�������������Ŏg�p )

	DX_ANDR_SHADER_FLOAT4			uSMLVPMat[ 12 /* [ 3 ][ 4 ] */ ] ;	// �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������

	DX_ANDR_SHADER_FLOAT4			uTexMat[ 6 /* [ DX_VS_CONSTF_TEXTURE_MATRIX_NUM ][ 2 ] */ ] ;	// �e�N�X�`�����W����p�s��
	DX_ANDR_SHADER_FLOAT4			uLWMat[ 162 /* DX_VS_CONSTF_WORLD_MAT_NUM * 3 */ ] ;		// ���[�J���@���@���[���h�s��


	// �t���O�����g�V�F�[�_�[�p
	DX_ANDR_SHADER_FLOAT			uMulAlphaColor ;							// �J���[�ɃA���t�@�l����Z���邩�ǂ���( 0.0:��Z���Ȃ�  1.0:��Z���� )

	DX_ANDR_SHADER_FLOAT			uATestRef ;									// ���e�X�g�l
	DX_ANDR_SHADER_INT				uATestCmpMode ;

	DX_ANDR_SHADER_FLOAT4			uFogColor ;									// �t�H�O�J���[
	DX_ANDR_SHADER_FLOAT4			uFactorColor ;								// �t�@�N�^�[�J���[
	DX_ANDR_SHADER_FLOAT4			uIgnoreTextureColor ;						// �e�N�X�`���J���[���������p�J���[
	DX_ANDR_SHADER_FLOAT4			uAddColor ;									// ���Z����F

	DX_ANDR_SHADER_FLOAT4			uShadowMapLightEnable[ 6 ] ;				// �V���h�E�}�b�v�O�E�P�E�Q�̃��C�g�L�����( x:�V���h�E�}�b�v�O�Ń��C�gn���L����  y:�V���h�E�}�b�v�P�Ń��C�gn���L����  z:�V���h�E�}�b�v�Q�Ń��C�gn���L���� )
	DX_ANDR_SHADER_FLOAT2			uShadowMap_DAdj_Grad[ 3 ] ;					// �V���h�E�}�b�v�̏��( x:臒l�[�x�␳�l  y:�O���f�[�V�����͈�  )

	int								UpdateCount ;								// �萔�̓��e���ύX���ꂽ��

	int								SetNormalMaterial ;							// �萔�o�b�t�@�ɕW���`��p�̃}�e���A���p�����[�^���ݒ肳��Ă��邩�ǂ���( TRUE:�ݒ肳��Ă���  FALSE:�ݒ肳��Ă��Ȃ� )
	int								SetNormalColorSource ;						// �萔�o�b�t�@�ɕW���`��p�́u�f�B�t���[�Y�J���[�E�X�y�L�����J���[���}�e���A�����g�p���邩�A���_�f�[�^���g�p���邩�v�̐ݒ肪����Ă��邩�ǂ���( TRUE:�ݒ肳��Ă���  FALSE:�ݒ肳��Ă��Ȃ� )
	int								SetNormalTextureAddressTransformMatrix ;	// �萔�o�b�t�@�ɕW���`��p�̃e�N�X�`�����W�p�s�񂪐ݒ肳��Ă��邩�ǂ���( TRUE:�ݒ肳��Ă���  FALSE:�ݒ肳��Ă��Ȃ� )
} ;

// �V�F�[�_�[��񃊃X�g�\����
struct GRAPHICS_ANDROID_SHADER_LIST
{
	int								UseNum ;									// Shaders �Ŏg�p���Ă���z��̐�
	GRAPHICS_ANDROID_SHADER			Shaders[ SHADERS_LIST_DATA_NUM ] ;			// �V�F�[�_�[���
	GRAPHICS_ANDROID_SHADER_LIST	*Next ;										// ���̃V�F�[�_�[���X�g
} ;

// Android �̃V�F�[�_�[����Z�߂��\����
struct GRAPHICS_HARDWARE_ANDROID_SHADER
{
	GRAPHICS_HARDWARE_ANDROID_CONSTANT				Constant ;						// �萔����Z�߂��\����

	GRAPHICS_ANDROID_SHADER_LIST					*ShadersListFirst ;				// �V�F�[�_�[��񃊃X�g(��[)
	GRAPHICS_ANDROID_SHADER_LIST					*ShadersListLast ;				// �V�F�[�_�[��񃊃X�g(���[)

	GRAPHICS_HARDWARE_ANDROID_SHADER_BASE			Base ;							// �W���`�揈���p�̃V�F�[�_�[��Z�߂��\����
	GRAPHICS_HARDWARE_ANDROID_SHADER_BASE3D			Base3D ;						// �W���R�c�`�揈���p�̃V�F�[�_�[��Z�߂��\����

#ifndef DX_NON_MODEL
	GRAPHICS_HARDWARE_ANDROID_SHADER_MODEL			Model ;							// ���f���`�揈���p�̃V�F�[�_�[��Z�߂��\����
#endif // DX_NON_MODEL
} ;









// AndroidDevice �ɐݒ肵�Ă���l��Z�߂��\����
struct GRAPHICS_HARDDATA_ANDROID_DEVICE_STATE
{
	int								FogEnable ;										// �t�H�O���L�����ǂ���( TRUE:�L��  FALSE:���� )
	int								FogMode ;										// �t�H�O���[�h
	DWORD							FogColor ;										// �t�H�O�J���[
	float							FogStart ;										// �t�H�O�J�n����
	float							FogEnd ;										// �t�H�O�I������
	float							FogDensity ;									// �t�H�O���x

	COLOR_U8						BackgroundColor ;								// �w�i�F

	COLOR_F							GlobalAmbientLightColor ;						// �O���[�o���A���r�G���g���C�g�J���[
	int								LightEnableMaxIndex ;							// �L���ȃ��C�g�̍ő�C���f�b�N�X
	int								LightEnableFlag[ DX_ANDR_COMMON_CONST_LIGHT_NUM ] ;// ���C�g���L�����ǂ����t���O( TRUE:�L��  FALSE:���� )
	LIGHTPARAM						LightParam[ DX_ANDR_COMMON_CONST_LIGHT_NUM ] ;	// ���C�g�̃p�����[�^
	int								Lighting ;										// ���C�e�B���O���s�����ǂ����̃t���O( TRUE:���C�e�B���O���s��  FALSE:���C�e�B���O�Ȃ� )

	int								UseSpecular ;									// �X�y�L�������g�p���邩�ǂ���
	MATERIALPARAM					Material ;										// �}�e���A��
	float							MaterialTypeParam[ MATERIAL_TYPEPARAM_MAX_NUM ] ;	// �}�e���A���ʃ^�C�v�p�����[�^
	int								MaterialUseVertexDiffuseColor ;					// ���_�̃f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�Ƃ��Ďg�p���邩�ǂ���
	int								MaterialUseVertexSpecularColor ;				// ���_�̃X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�Ƃ��Ďg�p���邩�ǂ���

	int								DrawMode ;										// �`�惂�[�h( DX_DRAWMODE_BILINEAR �Ȃ� )�A�W���̃t�B���^�����O���[�h�ł͂Ȃ��ꍇ�� -1
	int								MaxAnisotropy ;									// �ő�ٕ����A�S�ẴT���v���ɑ΂��ē����ݒ肪�s���Ă��Ȃ��ꍇ�� -1
	int								MaxAnisotropyDim[ USE_TEXTURESTAGE_NUM ] ;		// �e�T���v���̍ő�ٕ���
	GLint							TexMagFilter[ USE_TEXTURESTAGE_NUM ] ;			// �g��t�B���^�[( GL_TEXTURE_MAG_FILTER �̃p�����[�^�A GL_NEAREST �Ȃ� )
	GLint							TexMinFilter[ USE_TEXTURESTAGE_NUM ] ;			// �k���t�B���^�[( GL_TEXTURE_MIN_FILTER �̃p�����[�^�A GL_NEAREST �Ȃ� )
	GLint							TexAddressModeU[ USE_TEXTURESTAGE_NUM ] ;		// �e�N�X�`���A�h���X���[�h�t( GL_TEXTURE_WRAP_S �̃p�����[�^�A GL_REPEAT �Ȃ� )
	GLint							TexAddressModeV[ USE_TEXTURESTAGE_NUM ] ;		// �e�N�X�`���A�h���X���[�h�u( GL_TEXTURE_WRAP_T �̃p�����[�^�A GL_REPEAT �Ȃ� )
	GLint							TexAddressModeW[ USE_TEXTURESTAGE_NUM ] ;		// �e�N�X�`���A�h���X���[�h�v( GL_TEXTURE_WRAP_R �̃p�����[�^�A GL_REPEAT �Ȃ� )

	RECT							ViewportRect ;									// �r���[�|�[�g�̋�`

	int								CullEnable ;									// �J�����O���s�����ǂ���
	GLenum							CullFace ;										// �J�����O��( GL_BACK �Ȃ� )
	int								DepthBias ;										// �[�x�l�o�C�A�X

	int								DepthEnable ;									// �[�x�o�b�t�@�̗L���t���O( �[�x�o�b�t�@�L���A������ glEnable( GL_DEPTH_TEST ), glDisable( GL_DEPTH_TEST ) �ōs�� )
	int								DepthWriteEnable ;								// �[�x�o�b�t�@�ւ̏������݂��L�����ǂ���( �������݂��s�����ǂ����̐ݒ�� glDepthMask �ōs�� )
	GLenum							DepthFunc ;										// �[�x�l�̔�r���[�h( GL_LEQUAL �Ȃ� )

	int								BlendMode ;										// ���݃f�o�C�X�ɐݒ肳��Ă���u�����h���[�h�A�v���Z�b�g�̃u�����h���[�h�ȊO�̏ꍇ�� -1 ������
	int								NotWriteAlphaChannelFlag ;						// �A���t�@�`�����l���̓��e�����������Ȃ����ǂ����̃t���O

	GRAPHICS_ANDROID_TEXTURE		*SetTexture[ USE_TEXTURESTAGE_NUM ] ;			// �`�掞�Ɏg�p����e�N�X�`��

	RECT							ScissorRect ;									// �V�U�[��`
	int								AlphaTestEnable ;								// �A���t�@�e�X�g���g�p���邩�ǂ���
	int								AlphaTestCmpMode ;								// �A���t�@�e�X�g�Ŏg�p�����r���[�h( DX_CMP_NEVER �Ȃ� )
	int								AlphaTestRef ;									// �A���t�@�e�X�g�Ŏg�p����Q�ƒl
	int								AlphaTestModeShaderIndex ;						// �A���t�@�e�X�g�̐ݒ�l�ɑΉ�����t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h( ANDROID_FS_ALPHATEST_CMP_GREATER �Ȃ� )

	int								SetNormalShader ;								// �ʏ�`��p�V�F�[�_�[���Z�b�g����Ă��邩�ǂ���
	GRAPHICS_ANDROID_SHADER	*		SetShader ;										// ���݃Z�b�g���Ă���V�F�[�_�[
	GRAPHICS_ANDROID_SHADER	*		SetShader_Force ;								// NULL �ȊO�̏ꍇ�D��I�Ɏg�p����V�F�[�_�[( ���ꏈ���p )

	GLuint							SetVertexBuffer ;								// ���݃Z�b�g���Ă��钸�_�o�b�t�@
	int								VertexAttrEnable[ ANDROID_VERTEX_ATTR_NUM ] ;	// �L���ɂȂ��Ă��钸�_�f�[�^

	GLuint							TargetFrameBuffer ;								// �`��Ώۂ̃t���[���o�b�t�@
	GLuint							TargetFrameBufferWidth ;						// �`��Ώۂ̃t���[���o�b�t�@�̕�
	GLuint							TargetFrameBufferHeight ;						// �`��Ώۂ̃t���[���o�b�t�@�̍���

	int								TextureAddressTransformMatrixUse ;				// �e�N�X�`�����W�ϊ��s����g�p���邩�ǂ���( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
	MATRIX							TextureAddressTransformMatrix ;					// �e�N�X�`�����W�ϊ��s��
} ;


// AndroidDevice �̕`�揈���Ɋւ����̍\����
struct GRAPHICS_HARDDATA_ANDROID_DRAWINFO
{
	BYTE *						VertexBufferNextAddr ;						// ���̃f�[�^���i�[���ׂ����_�o�b�t�@���̃A�h���X
	BYTE						VertexBuffer[ DX_GLES2_VERTBUFFERSIZE ] ;	// ���_�o�b�t�@
	int							Use3DVertex ;							// �R�c���_���g�p���Ă��邩�ǂ���( 1:�g�p���Ă���  0:�g�p���Ă��Ȃ� )
	int							VertexNum ; 							// ���_�o�b�t�@�Ɋi�[����Ă��钸�_�̐�
	int							VertexType ;							// ���_�o�b�t�@�Ɋi�[����Ă��钸�_�f�[�^( VERTEXTYPE_TEX �Ȃ� )
	GLenum						PrimitiveType ;							// ���_�o�b�t�@�Ɋi�[����Ă��钸�_�f�[�^�̃v���~�e�B�u�^�C�v

	DWORD						DiffuseColor ;							// �f�B�t���[�Y�J���[

	int							BeginSceneFlag ;						// Graphics_Android_BeginScene �����s���Ă��邩�ǂ���
	int							BlendMaxNotDrawFlag ;					// �u�����h�l���ő�ł��邱�Ƃɂ��`����s��Ȃ����ǂ����A�t���O
} ;

// AndroidDevice �̉�ʊ֌W�̏��̍\����
struct GRAPHICS_HARDDATA_ANDROID_SCREENINFO
{
	EGLDisplay					Display ;								// �o�͐�� EGLDisplay
	EGLSurface					Surface ;								// �o�͐�̃f�B�X�v���C�� EGLSurface
	EGLContext					Context ;								// �o�͐�̃f�B�X�v���C�� EGLContext
	EGLint						Width ;									// �o�͐�T�[�t�F�X�̕�
	EGLint						Height ;								// �o�͐�T�[�t�F�X�̍���

	int							FrontScreenCopyTime ;					// �\��ʂ�`���Ƃ��Ă���ꍇ�ɍs�� ScreenCopy ���s��������

	int							SubBackBufferTextureSizeX ;				// �T�u�o�b�N�o�b�t�@�e�N�X�`���̉���
	int							SubBackBufferTextureSizeY ;				// �T�u�o�b�N�o�b�t�@�e�N�X�`���̏c��
	GLuint						SubBackBufferTextureInternalFormat ;	// �T�u�o�b�N�o�b�t�@�e�N�X�`���̓����t�H�[�}�b�g
	GLenum						SubBackBufferTexturePixelFormat ;		// �T�u�o�b�N�o�b�t�@�e�N�X�`���̃s�N�Z���t�H�[�}�b�g
	GLuint						SubBackBufferTexturePixelType ;			// �T�u�o�b�N�o�b�t�@�e�N�X�`���̃s�N�Z���^�C�v
	void *						SubBackBufferTextureTempBuffer ;		// �T�u�o�b�N�o�b�t�@�e�N�X�`���ɃC���[�W��]������ۂɎg�p����o�b�t�@
	GLuint						SubBackBufferFrameBuffer ;				// ScreenCopy �� GetDrawScreen ���������邽�߂Ɏg�p����t���[���o�b�t�@
	GLuint						SubBackBufferTexture ;					// ScreenCopy �� GetDrawScreen ���������邽�߂Ɏg�p����e�N�X�`���o�b�t�@
	GLuint						SubBackBufferDepthBuffer ;				// ScreenCopy �� GetDrawScreen ���������邽�߂Ɏg�p����[�x�o�b�t�@

	void *						DrawScreenLockImage ;					// �`���̃��b�N���ɍ쐬����e���|�����C���[�W
	GLuint						DrawScreenLockImagePitch ;				// ���b�N�C���[�W�̃s�b�`
} ;


// AndroidDevice �̕`��ݒ�Ɋւ����̍\����
struct GRAPHICS_HARDDATA_ANDROID_DRAWSETTING
{
	int								DrawPrepParamFlag ;						// �O�� Graphics_Android_DrawPreparation �ɓ������Ƃ��� ParamFlag �p�����[�^
	int								DrawPrepAlwaysFlag ;					// �K�� Graphics_Android_DrawPreparation ���s�����ǂ����̃t���O

	int								AlphaChannelValidFlag ;					// ���`�����l���L���t���O
	int								AlphaTestValidFlag ;					// ���e�X�g�L���t���O( Func �͕K�� D_D3DCMP_GREATEREQUAL )
	int								AlphaTestMode ;							// �A���t�@�e�X�g���[�h
	int								AlphaTestParam ;						// �A���t�@�e�X�g�p�����[�^
	int								BlendMode ;								// �u�����h���[�h
	int								ChangeBlendParamFlag ;					// �u�����h�ݒ�Ɋւ�镔���̕ύX�����������A�t���O
	int								ChangeTextureFlag ;						// �e�N�X�`�����ύX���ꂽ���A�t���O
	int								NotWriteAlphaChannelFlag ;				// �A���t�@�`�����l���̓��e�����������Ȃ����ǂ����̃t���O
	int								IgnoreGraphColorFlag ;					// �`�悷��摜�̂q�f�a�����𖳎����邩�ǂ����̃t���O
	int								IgnoreGraphAlphaFlag ;					// �`�悷��摜�̂`�����𖳎����邩�ǂ����̃t���O
//	int								UseDiffuseRGBColor ;					// �f�B�t���[�Y�J���[�̂q�f�a�l���g�p���邩�A�t���O
//	int								UseDiffuseAlphaColor ;					// �f�B�t���[�Y�J���[�̃��l���g�p���邩�A�t���O
	int								BlendGraphType ;						// �u�����h�摜�^�C�v
	int								BlendGraphFadeRatio ;					// �u�����h�摜�̃t�F�[�h�p�����[�^
	int								BlendGraphBorderParam ;					// �u�����h�摜�̋��E�p�����[�^(�O(�u�����h�摜�̉e���O)�@���@(�u�����h�摜�̉e�����Ȃ�)�@���@�P�Q�W(�u�����h�摜�̉e���P�O�O��)�@���@(�u�����h�摜�̉e���𒴂��Ĕ�`�敔����������)�@���Q�T�T(�S���`�悳��Ȃ�) )
	int								BlendGraphBorderRange ;					// �u�����h�摜�̋��E��(�O�`�Q�T�T�@�����`�L���@�������S�i�K)
	float							BlendTextureWidth ;						// �u�����h�e�N�X�`���̕�
	float							BlendTextureHeight ;					// �u�����h�e�N�X�`���̍���
	float							InvBlendTextureWidth ;					// �u�����h�e�N�X�`���̕��̋t��
	float							InvBlendTextureHeight ;					// �u�����h�e�N�X�`���̍����̋t��

	GRAPHICS_ANDROID_TEXTURE		*RenderTexture ;						// �`�掞�Ɏg�p����e�N�X�`���[
	GRAPHICS_ANDROID_TEXTURE		*BlendTexture ;							// �`�掞�ɕ`��e�N�X�`���[�ƃu�����h���郿�`�����l���e�N�X�`���[

	int								CancelSettingEqualCheck ;				// ���̃t���O�������Ă���ꍇ�͌��݂̐ݒ�ƕύX��̐ݒ肪�������ǂ����Ɋւ�炸�A�K���ύX���������s����
} ;


// AndroidDevice �֌W�̐ݒ���̍\����
struct GRAPHICS_HARDDATA_ANDROID_DEVICE_SETTING
{
	void					( *DeviceRestoreCallbackFunction)( void *Data ) ;	// �f�o�C�X���X�g���畜�A�����Ƃ��ɌĂԊ֐�
	void					  *DeviceRestoreCallbackData ;						// �f�o�C�X���X�g���畜�A�����Ƃ��ɌĂԊ֐��ɓn���|�C���^

	void					( *DeviceLostCallbackFunction)( void *Data ) ;		// �f�o�C�X���X�g���畜�A����O�ɌĂԊ֐�
	void					  *DeviceLostCallbackData ;							// �f�o�C�X���X�g���畜�A����O�ɌĂԊ֐��ɓn���|�C���^
} ;


// AndroidDevice �̔\�͏��\����
struct GRAPHICS_HARDDATA_ANDROID_DEVICE_CAPS
{
	TCHAR *						Version ;
	TCHAR *						Renderer ;
	TCHAR *						Vendor ;

	unsigned char				Extensions[ ANDROID_GL_EXTENSION_NUM ] ;			// Extensions
	int							ExtensionNum ;										// Extension �̐�
	TCHAR **					ExtensionNames ;									// Extension ���̔z��

	TCHAR *						Shading_Language_Version ;

	GLint						Shader_Max_Vertex_Attribs ;							// GL_MAX_VERTEX_ATTRIBS
	GLint						Shader_Max_Vertex_Uniform_Vectors ;					// GL_MAX_VERTEX_UNIFORM_VECTORS
	GLint						Shader_Max_Varying_Vectors ;						// GL_MAX_VARYING_VECTORS
	GLint						Shader_Max_Combined_Texture_Image_Units ;			// GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
	GLint						Shader_Max_Vertex_Texture_Image_Units ;				// GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
	GLint						Shader_Max_Texture_Image_Units ;					// GL_MAX_TEXTURE_IMAGE_UNITS
	GLint						Shader_Max_Fragment_Uniform_Vectors ;				// GL_MAX_FRAGMENT_UNIFORM_VECTORS

	int							ScreenFormat ;										// ��ʃJ���[�t�H�[�}�b�g
	int							TextureFormat[ DX_GRAPHICSIMAGE_FORMAT_3D_NUM ] ;	// �e�N�X�`���t�H�[�}�b�g
	int							MaskAlphaFormat ;									// �}�X�N�A���t�@�`�����l���p�t�H�[�}�b�g
	GLenum						DepthBufferFormat[ ZBUFFER_FORMAT_NUM ] ;			// �[�x�o�b�t�@�t�H�[�}�b�g
} ;


// Android ���g�����`�揈���Ŏg�p����f�[�^�̓��� AndroidDevice �̃��Z�b�g��
// ��������������K�v������AAndroidDevice �ɖ��ڂɊւ��������Z�߂��\����
struct GRAPHICS_HARDDATA_ANDROID_DEVICE
{
	GRAPHICS_HARDDATA_ANDROID_DEVICE_CAPS			Caps ;					// �f�o�C�X�\�͏��\����		

	GRAPHICS_HARDDATA_ANDROID_DEVICE_SETTING		Setting ;				// �f�o�C�X�֌W�̐ݒ����Z�߂��\����

	GRAPHICS_HARDDATA_ANDROID_SCREENINFO			Screen ;				// ��ʊ֌W�̏��\����

	GRAPHICS_HARDWARE_ANDROID_SHADER				Shader ;				// �V�F�[�_�[��Z�߂��\����

//	GRAPHICS_HARDWARE_ANDROID_INPUTLAYOUT			InputLayout ;			// ���̓��C�A�E�g��Z�߂��\����

	GRAPHICS_HARDDATA_ANDROID_DRAWSETTING			DrawSetting ;			// �`��ݒ�Ɋւ�����Z�߂��\����

	GRAPHICS_HARDDATA_ANDROID_DRAWINFO				DrawInfo ;				// �`�揈���Ɋւ�����Z�߂��\����

	GRAPHICS_HARDDATA_ANDROID_DEVICE_STATE			State ;					// AndroidDevice �ɐݒ肵�Ă���l��Z�߂��\����
} ;













// �V�F�[�_�[�R�[�h��̏��\����
struct GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO
{
	void					*Binary ;								// �V�F�[�_�[�R�[�h�o�C�i���̃A�h���X
	int						Size ;									// �V�F�[�_�[�R�[�h�o�C�i���̃f�[�^�T�C�Y
} ;


// Android �� �W���`��p�̃V�F�[�_�[�R�[�h�̌��f�[�^��Z�߂��\����
struct GRAPHICS_HARDWARE_ANDROID_SHADERCODE_BASE
{
	int						BaseShaderInitializeFlag ;				// �V�F�[�_�[�o�C�i���̃Z�b�g�A�b�v���������Ă��邩�ǂ����̃t���O( TRUE:�������Ă���  FALSE:�������Ă��Ȃ� )

	// ���C�g�C���f�b�N�X���X�g
	short					LightIndexList84[ 4 ][ 4 ][ 4 ][ 4 ][ 4 ][ 4 ] ;
	short					LightIndexList20[ 4 ][ 4 ][ 4 ] ;
	short					LightIndexList10[ 3 ][ 3 ][ 3 ] ;

	void					*Base2DShaderPackageImage ;				// �W���Q�c�`��p�V�F�[�_�[�p�b�P�[�W�o�C�i���C���[�W

	// �W���`��p�̕��G�ȏ������s��Ȃ����_�V�F�[�_�[
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO BaseSimple_VS_Code[ ANDROID_VERTEX_INPUTLAYOUT_NUM ] ;

	// �Œ�@�\�p�C�v���C���݊��̃t���O�����g�V�F�[�_�[( �e�N�X�`���Ȃ� )
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO BaseNoneTex_FS_Code[ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// �Œ�@�\�p�C�v���C���݊��̃t���O�����g�V�F�[�_�[( �e�N�X�`������ )
	// [ �u�����h�摜�Ƃ̃u�����h�^�C�v( 0:�Ȃ�  1:DX_BLENDGRAPHTYPE_NORMAL  2:DX_BLENDGRAPHTYPE_WIPE  3:DX_BLENDGRAPHTYPE_ALPHA ) ]
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �e�N�X�`��RGB����( 0:�������Ȃ�  1:�������� ) ]
	// [ �e�N�X�`��Alpha����( 0:�������Ȃ�  1:�������� ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO BaseUseTex_FS_Code[ 4 ][ ANDROID_RENDER_TYPE_NUM ][ 2 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// �}�X�N�����p�V�F�[�_�[
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MaskEffect_VS_Code ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MaskEffect_FS_Code ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MaskEffect_ReverseEffect_FS_Code ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MaskEffect_UseGraphHandle_FS_Code[ 4 ] ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MaskEffect_UseGraphHandle_ReverseEffect_FS_Code[ 4 ] ;

	// �P���]���p�V�F�[�_�[
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO StretchRect_VS_Code ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO StretchRectTex2_VS_Code ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO StretchRectTex8_VS_Code ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO StretchRect_FS_Code ;

	// �N���A�����p�V�F�[�_�[
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ClearRT_VS_Code ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ClearRT_FS_Code ;

#ifndef DX_NON_FILTER
	DXARC					FilterShaderBinDxa ;					// �t�B���^�[�V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�\����
	void					*FilterShaderBinDxaImage ;				// �t�B���^�[�V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�̃o�C�i���C���[�W

	void					*RGBAMixS_ShaderPackImage ;				// RGBAMix �� S �����̑g�ݍ��킹�Q�T�U�̃V�F�[�_�[�p�b�P�[�W�o�C�i���C���[�W

	// RGBAMix �� S �����̑g�ݍ��킹�Q�T�U�̃V�F�[�_�[[ R ][ G ][ B ][ A ][ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO RGBAMixS_FS_Code[ 4 ][ 4 ][ 4 ][ 4 ][ 2 ] ;
#endif // DX_NON_FILTER
} ;

// Android �� �W���R�c�`��p�̃V�F�[�_�[�R�[�h�̌��f�[�^��Z�߂��\����
struct GRAPHICS_HARDWARE_ANDROID_SHADERCODE_BASE3D
{
	volatile int			Base3DShaderInitializeFlag ;			// �V�F�[�_�[�o�C�i���̃Z�b�g�A�b�v���������Ă��邩�ǂ����̃t���O( TRUE:�������Ă���  FALSE:�������Ă��Ȃ� )

	void					*Base3DShaderPackageImage ;				// �W���R�c�`��p�V�F�[�_�[�p�b�P�[�W�o�C�i���C���[�W

	// �W���R�c�`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̒��_�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// /* [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V�� 2:8�{�[�����X�L�j���O���b�V�� ) ] */
	// /* [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ] */
	// [ �t�H�O�^�C�v ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO Base3D_PixelLighting_VS_Code[ 2 ]/*[ 3 ]*//*[ 2 ]*/[ 4 ] ;

	// �W���R�c�`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃t���O�����g�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// /*[ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]*/
	// /*[ �X�y�L�����}�b�v ( 0:���� 1:���� ) ]*/
	// /*[ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]*/
	// [ ���C�g�C���f�b�N�X ]
	// /*[ �X�y�L�����̗L��( 0:���� 1:�L�� ) ]*/
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO Base3D_PixelLighting_Normal_FS_Code[ 2 ]/*[ 5 ]*//*[ 2 ]*//*[ 2 ]*/[ 84 ]/*[ 2 ]*/[ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;



	// �W���R�c�`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p���_�V�F�[�_�[
	// /*[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]*/
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO Base3D_ShadowMap_VS_Code/*[ 3 ]*/[ 2 ] ;

	// �W���R�c�`��p�̃��C�e�B���O�Ȃ����_�V�F�[�_�[
	// /*[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]*/
	// [ �t�H�O�^�C�v ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO Base3D_NoLighting_VS_Code/*[ 3 ]*/[ 4 ] ;

	// �W���R�c�`��p�̒��_�P�ʃ��C�e�B���O���_�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// /*[ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]*/
	// /*[ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]*/
	// [ �t�H�O�^�C�v ]
	// [ ���C�g�C���f�b�N�X ]
	// /*[ �X�y�L�����̗L��( 0:���� 1:�L�� ) ]*/
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO Base3D_VertexLighting_VS_Code[ 2 ]/*[ 3 ]*//*[ 2 ]*/[ 4 ][ 20 ]/*[ 2 ]*/ ;

	// �W���R�c�`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p�t���O�����g�V�F�[�_�[
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO Base3D_ShadowMap_Normal_FS_Code[ ANDROID_FS_ALPHATEST_NUM ] ;

	// �W���R�c�`��p�̃��C�e�B���O�Ȃ��t���O�����g�V�F�[�_�[
	// /*[ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]*/
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO Base3D_NoLighting_Normal_FS_Code/*[ 5 ]*/[ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// �W���R�c�`��p�̒��_�P�ʃ��C�e�B���O�t���O�����g�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// /* [ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ] */
	// /* [ �X�y�L�����}�b�v ( 0:���� 1:���� ) ] */
	// /* [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ] */
	// [ ���C�g�C���f�b�N�X ]
	// /*[ �X�y�L�����̗L��( 0:���� 1:�L�� ) ]*/
	// [ �������( 0:�ʏ�`��  1:��Z�`��  2:RGB���]  3:�`��P�x�S�{  4:��Z�ς݃��u�����h���[�h�̒ʏ�`��  5:��Z�ς݃��u�����h���[�h��RGB���]  6:��Z�ς݃��u�����h���[�h�̕`��P�x4�{ ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO Base3D_VertexLighting_Normal_FS_Code[ 2 ]/*[ 5 ]*//*[ 2 ]*//*[ 2 ]*/[ 10 ]/*[ 2 ]*/[ ANDROID_RENDER_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;
} ;

#ifndef DX_NON_MODEL

// Android �� ���f���`��p�̃V�F�[�_�[�R�[�h�̌��f�[�^��Z�߂��\����
struct GRAPHICS_HARDWARE_ANDROID_SHADERCODE_MODEL
{
	volatile int			ModelShaderInitializeFlag ;				// ���f���p�̃V�F�[�_�[�o�C�i���̃Z�b�g�A�b�v���������Ă��邩�ǂ����̃t���O( TRUE:�������Ă���  FALSE:�������Ă��Ȃ� )

	void					*ModelShaderPackImage ;					// �R�c���f���p�V�F�[�_�[�p�b�P�[�W�o�C�i���C���[�W

	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̒��_�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V�� 2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_PixelLighting_VS_Code[ 2 ][ 3 ][ 2 ][ 4 ] ;

	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃g�D�[���^�C�v�P�p�t���O�����g�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// [ �g�D�[�������_�����O�̃X�y�L�����O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]
	// [ �L���ȃ��C�g�̐� - 1 ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_PixelLighting_ToonType1_FS_Code[ 2 ][ 2 ][ 2 ][ 2 ][ DX_ANDR_COMMON_CONST_LIGHT_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃g�D�[���^�C�v�Q�p�t���O�����g�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖���   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ �L���ȃ��C�g�̐� - 1 ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_PixelLighting_ToonType2_FS_Code[ 2 ][ 3 ][ DX_ANDR_COMMON_CONST_LIGHT_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�s�N�Z���P�ʃ��C�e�B���O�^�C�v�̃t���O�����g�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]
	// [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]
	// [ �L���ȃ��C�g�̐� - 1 ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_PixelLighting_Normal_FS_Code[ 2 ][ 5 ][ 2 ][ DX_ANDR_COMMON_CONST_LIGHT_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;






	// ���f���`��p�̃}�e���A���v�f�`��p�t���O�����g�V�F�[�_�[
	// [ �}�e���A���^�C�v( DX_MATERIAL_TYPE_MAT_SPEC_LUMINANCE_UNORM �Ȃ� ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_MaterialType_FS_Code[ DX_MATERIAL_TYPE_NUM ][ ANDROID_FS_ALPHATEST_NUM ] ;






	// ���f���`��p�̃V���h�E�}�b�v�ւ̃g�D�[�������_�����O�֊s���`��p���_�V�F�[�_�[
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_ToonOutLine_ShadowMap_VS_Code[ 3 ][ 2 ] ;

	// ���f���`��p�̃g�D�[�������_�����O�̗֊s���`��p���_�V�F�[�_�[
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_ToonOutLine_VS_Code[ 3 ][ 2 ][ 4 ] ;

	// ���f���`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p���_�V�F�[�_�[
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_ShadowMap_VS_Code[ 3 ][ 2 ] ;

	// ���f���`��p�̃��C�e�B���O�Ȃ����_�V�F�[�_�[
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_NoLighting_VS_Code[ 3 ][ 2 ][ 4 ] ;

	// ���f���`��p�̒��_�P�ʃ��C�e�B���O���蒸�_�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	// [ ���C�g�C���f�b�N�X ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_VertexLighting_VS_Code[ 2 ][ 3 ][ 2 ][ 4 ][ 20 ] ;

	// ���f���`��p�̃V���h�E�}�b�v�ւ̃g�D�[�������_�����O�p�t���O�����g�V�F�[�_�[
	// [ �g�D�[�������_�����O�^�C�v( 0:�g�D�[�������_�����O type 1   1:�g�D�[�������_�����O type 2 ) ]
	// [ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖���   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_ShadowMap_Toon_FS_Code[ 2 ][ 3 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̃V���h�E�}�b�v�ւ̃����_�����O�p�t���O�����g�V�F�[�_�[
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_ShadowMap_Normal_FS_Code[ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̃��C�e�B���O�Ȃ��g�D�[���p�t���O�����g�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �g�D�[�������_�����O�^�C�v( 0:�g�D�[�������_�����O type 1   1:�g�D�[�������_�����O type 2 ) ]
	// [ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT or �g�D�[�������_�����O�ł͂Ȃ�  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_NoLighting_Toon_FS_Code[ 2 ][ 2 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̃��C�e�B���O�Ȃ��t���O�����g�V�F�[�_�[
	// [ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_NoLighting_Normal_FS_Code[ 5 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̒��_�P�ʃ��C�e�B���O����g�D�[���^�C�v�P�p�t���O�����g�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// [ �g�D�[�������_�����O�̃X�y�L�����O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT  1:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]
	// [ ���C�g�C���f�b�N�X ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_VertexLighting_ToonType1_FS_Code[ 2 ][ 2 ][ 2 ][ 2 ][ 10 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̒��_�P�ʃ��C�e�B���O����g�D�[���^�C�v�Q�p�t���O�����g�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖���   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ ���C�g�C���f�b�N�X ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_VertexLighting_ToonType2_FS_Code[ 2 ][ 3 ][ 10 ][ ANDROID_FS_ALPHATEST_NUM ] ;

	// ���f���`��p�̒��_�P�ʃ��C�e�B���O����t���O�����g�V�F�[�_�[
	// [ �V���h�E�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �}���`�e�N�X�`���̃u�����h���[�h�AMV1_LAYERBLEND_TYPE_TRANSLUCENT �Ȃǂ� +1 �������� ( 0:�}���`�e�N�X�`������  1:���u�����h  2:���Z�u�����h  3:��Z�u�����h  4:��Z�u�����h�~2 ) ]
	// [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]
	// [ ���C�g�C���f�b�N�X ]
	// [ �t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h ]
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO MV1_VertexLighting_Normal_FS_Code[ 2 ][ 5 ][ 2 ][ 10 ][ ANDROID_FS_ALPHATEST_NUM ] ;
} ;

#endif // DX_NON_MODEL


// �V�F�[�_�[�R�[�h�̌��f�[�^��Z�߂��\����
struct GRAPHICS_HARDWARE_ANDROID_SHADERCODE
{
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_BASE	Base ;				// �W���`�揈���p�̃V�F�[�_�[�R�[�h��Z�߂��\����
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_BASE3D	Base3D ;			// �W���R�c�`�揈���p�̃V�F�[�_�[�R�[�h��Z�߂��\����

#ifndef DX_NON_MODEL
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_MODEL	Model ;				// ���f���`�揈���p�̃V�F�[�_�[�R�[�h��Z�߂��\����
#endif // DX_NON_MODEL
} ;


// Android �֌W�̐ݒ���̍\����
struct GRAPHICS_HARDDATA_ANDROID_SETTING
{
	int								UseMinFeatureLevelAndroid ;				// Android �Ŏg�p����Œ�@�\���x��
	int								UserDepthBufferSizeSet ;					// �O������[�x�o�b�t�@�T�C�Y�̎w�肪���������ǂ���
	int								UserDepthBufferBitDepthSet ;				// �O������[�x�o�b�t�@�̃r�b�g�[�x�w�肪���������ǂ���

	int								UseOldDrawModiGraphCodeFlag ;				// �ȑO�� DrawModiGraph �֐��R�[�h���g�p���邩�ǂ����̃t���O
} ;



// Android �̃e�N�X�`�������p���̍\����
struct GRAPHICS_HARDDATA_ANDROID_TEXTURE
{
	void *											CommonBuffer ;					// �e�N�X�`���摜�]���p�̋��L������
	unsigned int									CommonBufferSize ;				// �e�N�X�`���摜�]���p�̋��L�������̃T�C�Y
} ;

// Android ���g�����O���t�B�b�N�X�������̍\����
struct GRAPHICS_HARDDATA_ANDR
{
	int												UsePixelLightingShader ;	// �s�N�Z���P�ʂŃ��C�e�B���O���s���^�C�v�̃V�F�[�_�[���g�p���邩�ǂ���( TRUE:�g�p����  FALSE:�g�p���Ȃ� )

	GRAPHICS_HARDDATA_ANDROID_SETTING				Setting ;					// Android �֌W�̐ݒ���

	GRAPHICS_HARDDATA_ANDROID_DEVICE				Device ;					// AndroidDevice �ɖ��ڂɊ֘A�������

	GRAPHICS_HARDWARE_ANDROID_SHADERCODE			ShaderCode ;				// FragmentShader �� VertexShader �̌��ƂȂ�V�F�[�_�[�R�[�h�f�[�^��Z�߂��\����

	GRAPHICS_HARDDATA_ANDROID_TEXTURE				Texture ;					// Android �̃e�N�X�`�������p���̍\����
} ;

struct DX_ANDROID_RENDER_BLEND_INFO
{
	int									RenderType ;
	int									BlendEnable ;
	GLenum								ColorSourceMul ;
	GLenum								ColorDestMul ;
	GLenum								ColorBlendFunc ;
	GLenum								AlphaSourceMul ;
	GLenum								AlphaDestMul ;
	GLenum								AlphaBlendFunc ;
	int									AlphaZeroNotDrawFlag ;
} ;

// �������ϐ��錾 --------------------------------------------------------------

extern GLenum g_DXCmpModeToGLES2CompareFunc[ 9 ] ;
extern DX_ANDROID_RENDER_BLEND_INFO g_DefaultBlendDescArray[ DX_BLENDMODE_NUM ] ;
extern PIXELFORMAT_INFO_ANDR g_AndroidPixelFormat[ ANDROID_PIXEL_FORMAT_NUM ] ;
extern GRAPHICS_HARDDATA_ANDR GraphicsHardDataAndroid ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// Android �̏������֌W
extern	int		Graphics_Android_Initialize( void ) ;								// Android ���g�p�����O���t�B�b�N�X�����̏��������s��( 0:���� -1:���s )
extern	int		Graphics_Android_Terminate( void ) ;								// Android ���g�p�����O���t�B�b�N�X�����̌�n�����s��

extern	int		Graphics_Android_ReleaseObjectAll( void ) ;							// ���ׂĂ� OpenGL ES �n�I�u�W�F�N�g���������
extern	int		Graphics_Android_CreateObjectAll( void ) ;							// ���ׂĂ� OpenGL ES �n�I�u�W�F�N�g���쐬����


















// �V�F�[�_�[�R�[�h�֌W
extern	int		Graphics_Android_ShaderCode_Base_Initialize( void ) ;				// Android �̕W���`��p�̃V�F�[�_�[�R�[�h�̏��������s��
extern	int		Graphics_Android_ShaderCode_Base_Terminate( void ) ;				// Android �̕W���`��p�̃V�F�[�_�[�R�[�h�̌�n�����s��

extern	int		Graphics_Android_ShaderCode_Base3D_Initialize( void ) ;			// Android �̕W���R�c�`��p�̃V�F�[�_�[�R�[�h�̏��������s��
extern	int		Graphics_Android_ShaderCode_Base3D_Terminate( void ) ;			// Android �̕W���R�c�`��p�̃V�F�[�_�[�R�[�h�̌�n�����s��

#ifndef DX_NON_MODEL

extern	int		Graphics_Android_ShaderCode_Model_Initialize( void ) ;			// Android �̃��f���`��p�̃V�F�[�_�[�R�[�h�̏��������s��
extern	int		Graphics_Android_ShaderCode_Model_Terminate( void ) ;			// Android �̃��f���`��p�̃V�F�[�_�[�R�[�h�̌�n�����s��

#endif // DX_NON_MODEL

extern	int		Graphics_Android_Shader_Initialize( void ) ;					// Android �̃V�F�[�_�[�̏��������s��
extern	int		Graphics_Android_Shader_Terminate( void ) ;						// Android �̃V�F�[�_�[�̌�n��������

extern	GRAPHICS_ANDROID_SHADER *Graphics_Android_GetShaderStruct( void ) ;		// �V�����V�F�[�_�[�\���̂��擾����
extern	int		Graphics_Android_ShaderList_Terminate( void ) ;					// �V�F�[�_�[��񃊃X�g�̌�n�����s��

extern	int		Graphics_Android_VertexShader_Create(			GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*Code, GLuint *pDestShader, int Num ) ;		// �V�F�[�_�[�R�[�h���璸�_�V�F�[�_�[���쐬����
extern	void	Graphics_Android_VertexShaderArray_Release(		GLuint										*pObject,					int Num ) ;		// ���_�V�F�[�_�[�z����������
extern	int		Graphics_Android_FragmentShader_Create(			GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*Code, GLuint *pDestShader, int Num ) ;		// �V�F�[�_�[�R�[�h����t���O�����g�V�F�[�_�[���쐬����
extern	void	Graphics_Android_FragmentShaderArray_Release(	GLuint										*pObject,					int Num ) ;		// �t���O�����g�V�F�[�_�[�z����������

extern	GLuint	Graphics_Android_Shader_GetUniformIndex(		GRAPHICS_ANDROID_SHADER *ShaderInfo, const GLchar *UniformName ) ;						// �V�F�[�_�[�� Uniform �ԍ����擾����
extern	int		Graphics_Android_Shader_Create(					GRAPHICS_ANDROID_SHADER *ShaderInfo, GLuint VertexShader, GLuint FragmentShader ) ;		// ���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[����V�F�[�_�[�����Z�b�g�A�b�v����
extern	void	Graphics_Android_ShaderArray_Release(			GRAPHICS_ANDROID_SHADER *pShaderInfo,	int Num ) ;										// �V�F�[�_�[�z����������

extern	int		Graphics_Android_Shader_Normal3DDraw_Setup( void ) ;				// �R�c�W���`��̎w��̒��_�p�̕`��p�V�F�[�_�[���Z�b�g�A�b�v����
extern	int		Graphics_Android_Shader_GetAlphaTestModeIndex( int AlphaTestEnable, int AlphaTestMode /* DX_CMP_NEVER �� */ ) ;	// �A���t�@�e�X�g�̔�r���[�h����t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h( ANDROID_FS_ALPHATEST_CMP_GREATER �� )���擾����










// ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�֌W










// Android �̉�ʊ֌W
extern	int		Graphics_Android_SetupSubBackBuffer( void ) ;															// �T�u�o�b�N�o�b�t�@���g�p���鏀�����s��( 0:����  -1:���s )
extern	int		Graphics_Android_TerminateSubBackBuffer( void ) ;														// �T�u�o�b�N�o�b�t�@�̌�n�����s��( 0:����  -1:���s )
extern	int		Graphics_Android_FrontScreenProcess( void ) ;															// �\��ʂ��`���̍ۂ̒������















// Android �̉摜�֌W
extern COLORDATA *Graphics_Android_GetDataFormatColorData( int PixelFormat ) ;									// ANDROID_PIXEL_FORMAT_R8G8B8A8 �Ȃǂ̃t�H�[�}�b�g�ɍ��킹���J���[�t�H�[�}�b�g�����擾����

// �`���p�e�N�X�`���ƕ`��p�e�N�X�`����������Ă���ꍇ�ɁA�`��p�e�N�X�`���ɕ`���p�e�N�X�`���̓��e�𔽉f����
//extern	int		Graphics_Android_UpdateDrawTexture( IMAGEDATA_ORIG_HARD_TEX *OrigTex, int TargetSurface, D_DXGI_FORMAT Format ) ;

extern	int		Graphics_Android_Texture_SetupCommonBuffer( unsigned int Size ) ;		// �e�N�X�`���摜�]���p�̋��L�������̃Z�b�g�A�b�v���s��
extern	int		Graphics_Android_Texture_TerminateCommonBuffer( void ) ;				// �e�N�X�`���摜�]���p�̋��L�������̌�n�����s��

// �t���[���o�b�t�@�Ƀe�N�X�`���̒P���]�����s��
extern	int		Graphics_Android_StretchRect(
	GLuint					SrcTexture,				uint32_t SrcTextureWidth,       uint32_t SrcTextureHeight,       const RECT *SrcRect,			// NULL �őS��
	GLuint					FrameBuffer,			uint32_t FrameBufferWidth,      uint32_t FrameBufferHeight,      const RECT *DestRect,			// NULL �őS��
	GLenum					FilterType = GL_NEAREST,
	int						AlphaBlend = FALSE,
	GRAPHICS_ANDROID_SHADER	*Shader = NULL,
	GLuint					BlendTexture = 0,		uint32_t BlendTextureWidth = 0, uint32_t BlendTextureHeight = 0, const RECT *BlendRect = NULL,	// NULL �őS��
	VERTEX_TEX8_2D *		Texcoord8Vertex = NULL
) ;

// �w��̃e�N�X�`���̓��e�ɓǂݍ��݃A�N�Z�X�ł���悤�ɂ���
extern	int		Graphics_Android_Texture_Map(
	GLuint				TargetTexture,
	GLuint				TargetFrameBuffer/* = 0 */,
	GLuint				TargetWidth,
	GLuint				TargetHeight,
	const RECT *		MapRect /* NULL �őS�� */,
	BASEIMAGE *			MapBaseImage,
	void **				MapTempImage
) ;

// �w��̃e�N�X�`���̓��e�ւ̓ǂݍ��݃A�N�Z�X���I������
extern	int		Graphics_Android_Texture_Unmap( void * MapTempImage ) ;

// �e�N�X�`���ɃC���[�W�f�[�^��]������
extern int Graphics_Android_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
	const RECT				*SrcRect,
	const RECT				*DestRect,
	      GLuint			UseTex,
	      int				ImageNum,
	      int				TexWidth,
	      int				TexHeight,
	      int				TexUseWidth,
	      int				TexUseHeight,
	const BASEIMAGE			*RgbBaseImage,
	const BASEIMAGE			*AlphaBaseImage,
	      int				DestColorFormat,
	      int				RedIsAlphaFlag,
	      int				UseTransColorConvAlpha,
	      unsigned int		TransCode,
	      int				ASyncThread
) ;




// AndroidDevice �̏������֌W
extern	int		Graphics_Android_Device_Create( void ) ;																// Direct3DDevice11 �I�u�W�F�N�g�̍쐬( 0:����  -1:���s )
extern	int		Graphics_Android_Device_Delete( void ) ;																// �f�o�C�X�̔j���ɑ������鏈�����s��

extern	int		Graphics_Android_Device_Initialize( void ) ;															// Direct3DDevice11 �֌W�̏�����









// AndroidDevice �X�e�[�^�X�֌W
extern	void	Graphics_Android_DeviceState_RefreshRenderState( void ) ;												// �`��ݒ�����t���b�V��
extern	int		Graphics_Android_DeviceState_SetBaseState( void ) ;														// Direct3DDevice11 �̊�{�ݒ���s��
extern	int		Graphics_Android_DeviceState_SetSampleFilterMode( GLenum Filter, int Sampler = -1 ) ;		// �T���v���[�̃e�N�X�`���t�B���^�����O���[�h��ݒ肷��
extern	int		Graphics_Android_DeviceState_SetDepthEnable( BOOL DepthEnable )  ;									// �[�x�o�b�t�@�̗L�������̃Z�b�g
extern	int		Graphics_Android_DeviceState_SetDepthWriteEnable( int Flag ) ;										// �[�x�o�b�t�@�̏������݂̗L�����Z�b�g
extern	int		Graphics_Android_DeviceState_SetDepthFunc( GLenum DepthFunc ) ;						// �[�x�l�̔�r�^�C�v���Z�b�g
extern	int		Graphics_Android_DeviceState_SetDepthBias( int DepthBias ) ;										// �[�x�l�̃o�C�A�X���Z�b�g
extern	int		Graphics_Android_DeviceState_SetWorldMatrix( const MATRIX *Matrix ) ;								// ���[���h�ϊ��p�s����Z�b�g����
extern	int		Graphics_Android_DeviceState_SetViewMatrix( const MATRIX *Matrix ) ;								// �r���[�ϊ��p�s����Z�b�g����
extern	int		Graphics_Android_DeviceState_SetProjectionMatrix( const MATRIX *Matrix ) ;							// ���e�ϊ��p�s����Z�b�g����
extern	int		Graphics_Android_DeviceState_SetAntiViewportMatrix( const MATRIX *Matrix ) ;							// �A���`�r���[�|�[�g�s����Z�b�g����
extern	int		Graphics_Android_DeviceState_SetLightState( int LightNumber, LIGHTPARAM *Light ) ;					// ���C�g�̃Z�b�g
extern	int		Graphics_Android_DeviceState_SetLightEnable( int LightNumber, int EnableState ) ;						// ���C�g�̗L���A������ύX
extern	int		Graphics_Android_DeviceState_SetMaterial( MATERIALPARAM *Material ) ;									// �}�e���A���̃Z�b�g
extern	int		Graphics_Android_DeviceState_SetSpecularEnable( int UseFlag ) ;										// �X�y�L�������g�p���邩�ǂ������Z�b�g
extern	int		Graphics_Android_DeviceState_SetUseVertexDiffuseColor( int UseFlag ) ;								// ���_�̃f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�Ƃ��Ďg�p���邩�ǂ�����ݒ肷��
extern	int		Graphics_Android_DeviceState_SetUseVertexSpecularColor( int UseFlag ) ;								// ���_�̃X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�Ƃ��Ďg�p���邩�ǂ�����ݒ肷��
extern	int		Graphics_Android_DeviceState_SetCullMode( int State ) ;												// �J�����O�̗L�����Z�b�g 
extern	int		Graphics_Android_DeviceState_SetAmbient( COLOR_F *Color ) ;											// �A���r�G���g�J���[�̃Z�b�g
extern	int		Graphics_Android_DeviceState_SetTextureAddress( int AddressMode, int Sampler = -1 ) ;				// �e�N�X�`���[�̃A�h���b�V���O���[�h���Z�b�g����
extern	int		Graphics_Android_DeviceState_SetTextureAddressU( int AddressMode, int Sampler = -1 ) ;				// �e�N�X�`���[�̃A�h���b�V���O���[�h���Z�b�g����
extern	int		Graphics_Android_DeviceState_SetTextureAddressV( int AddressMode, int Sampler = -1 ) ;				// �e�N�X�`���[�̃A�h���b�V���O���[�h���Z�b�g����
extern	int		Graphics_Android_DeviceState_SetTextureAddressW( int AddressMode, int Sampler = -1 ) ;				// �e�N�X�`���[�̃A�h���b�V���O���[�h���Z�b�g����
extern	int		Graphics_Android_DeviceState_SetTextureAddressUVW( int AddressModeU, int AddressModeV, int AddressModeW, int Sampler = -1 ) ;		// �e�N�X�`���[�̃A�h���b�V���O���[�h���Z�b�g����
extern	int		Graphics_Android_DeviceState_SetTextureAddressTransformMatrix( int Use, MATRIX *Matrix ) ;			// �e�N�X�`�����W�ϊ��s����Z�b�g����
extern	int		Graphics_Android_DeviceState_SetFogEnable( int Flag ) ;												// �t�H�O��L���ɂ��邩�ǂ�����ݒ肷��( TRUE:�L��  FALSE:���� )
extern	int		Graphics_Android_DeviceState_SetFogVertexMode( int Mode /* DX_FOGMODE_NONE �� */ ) ;				// �t�H�O���[�h��ݒ肷��
extern	int		Graphics_Android_DeviceState_SetFogColor( unsigned int Color ) ;									// �t�H�O�J���[��ύX����
extern	int		Graphics_Android_DeviceState_SetFogStartEnd( float Start, float End ) ;								// �t�H�O���n�܂鋗���ƏI�����鋗����ݒ肷��( 0.0f �` 1.0f )
extern	int		Graphics_Android_DeviceState_SetFogDensity( float Density ) ;										// �t�H�O�̖��x��ݒ肷��( 0.0f �` 1.0f )
extern	int		Graphics_Android_DeviceState_SetLighting( int UseFlag ) ;											// ���C�e�B���O�̗L���t���O���Z�b�g����
extern	int		Graphics_Android_DeviceState_SetMaxAnisotropy( int MaxAnisotropy, int Sampler = -1 ) ;				// �ő�ٕ������Z�b�g����
extern	int		Graphics_Android_DeviceState_SetViewport( RECT *Viewport ) ;										// �r���[�|�[�g���Z�b�g����
extern	int		Graphics_Android_DeviceState_SetViewportEasy( int x1, int y1, int x2, int y2 ) ;					// �r���[�|�[�g���Z�b�g����( �ȈՔ� )
extern	int		Graphics_Android_DeviceState_SetDrawMode( int DrawMode ) ;											// �`�惂�[�h�̃Z�b�g
extern	int		Graphics_Android_DeviceState_SetAlphaTestCmpMode( int AlphaTestCmpMode /* DX_CMP_NEVER �Ȃ� */ ) ;	// �A���t�@�e�X�g�Ŏg�p�����r���[�h��ݒ肷��
extern	int		Graphics_Android_DeviceState_SetAlphaTestRef( int AlphaTestRef ) ;									// �A���t�@�e�X�g�Ŏg�p����Q�ƒl��ݒ肷��
extern	int		Graphics_Android_DeviceState_SetMulAlphaColor( int UseMulAlphaColor ) ;								// �J���[�ɃA���t�@�l����Z���邩�ǂ�����ݒ肷��
extern	int		Graphics_Android_DeviceState_SetBackgroundColor( int Red, int Green, int Blue, int Alpha ) ;		// �w�i�F��ݒ肷��
extern	int		Graphics_Android_DeviceState_SetFactorColor( const DX_ANDR_SHADER_FLOAT4 *FactorColor ) ;			// Factor Color ��ݒ肷��
extern	int		Graphics_Android_DeviceState_SetToonOutLineSize( float Size ) ;										// �g�D�[�������_�����O�̗֊s���̑�����ݒ肷��
extern	int		Graphics_Android_DeviceState_SetBlendMode( int BlendMode, int NotWriteAlphaChannelFlag ) ;			// �`��u�����h���[�h�̃Z�b�g
extern	int		Graphics_Android_DeviceState_SetRenderTarget( GLuint TargetFrameBuffer, GLuint TargetFrameBufferWidth, GLuint TargetFrameBufferHeight ) ;	// �`��Ώۂ̕ύX
extern	int		Graphics_Android_DeviceState_SetShader( GRAPHICS_ANDROID_SHADER *Shader, int NormalVertexShader = FALSE ) ;			// �g�p����V�F�[�_�[��ύX����
extern	int		Graphics_Android_DeviceState_ResetShader( int SetNormalShaderCancel = FALSE ) ;						// �V�F�[�_�[�̎g�p���~�߂�
extern	int		Graphics_Android_DeviceState_UpdateShaderUniform( GRAPHICS_ANDROID_SHADER *Shader, int LightNum, int UseLocalWorldMatrixUniformNum = 3 ) ;	// �V�F�[�_�[�� Uniform ���X�V����
extern	int		Graphics_Android_DeviceState_SetupShaderVertexData( GRAPHICS_ANDROID_SHADER *Shader, VERTEXBUFFER_INPUT_INFO_ANDR *VertexInputInfo, const void *VertexData, GLuint VertexBuffer = 0 ) ;	// �w��̃V�F�[�_�[�̒��_�t�H�[�}�b�g�̒��_�f�[�^�̕`�揀�����s��
extern	int		Graphics_Android_DeviceState_SetVertexBuffer( GLuint VertexBuffer ) ;								// �g�p���钸�_�o�b�t�@��ύX����
extern	int		Graphics_Android_DeviceState_SetTexture( int SlotIndex, GRAPHICS_ANDROID_TEXTURE *Texture ) ;		// �V�F�[�_�[�Ŏg�p����e�N�X�`����ύX����
extern	int		Graphics_Android_DeviceState_NormalDrawSetup( void ) ;												// �W���`��̏������s��
//extern	int		Graphics_Android_DeviceState_SetupStateAndConstantBuffer( void ) ;								// ���݂̐ݒ�Ɋ�Â��� ANDRSampler�AANDRPrimitiveSetup�AANDRDepthStencilControl�AANDRBlendControl �̃Z�b�g�A�b�v�ƁA�萔�o�b�t�@�̃A�b�v�f�[�g���s��






// �`��ݒ�֌W�֐�
extern	int		Graphics_Android_DrawSetting_SetDrawBlendMode( int BlendMode, int AlphaTestValidFlag, int AlphaChannelValidFlag ) ;	// �`��u�����h���[�h�̐ݒ�
extern	int		Graphics_Android_DrawSetting_SetIgnoreDrawGraphColor( int EnableFlag ) ;							// �`�掞�̉摜�̂q�f�a�𖳎����邩�ǂ�����ݒ肷��
extern	int		Graphics_Android_DrawSetting_SetIgnoreDrawGraphAlpha( int EnableFlag ) ;							// �`�掞�̉摜�̂`�𖳎����邩�ǂ�����ݒ肷��
extern	int		Graphics_Android_DrawSetting_SetWriteAlphaChannelFlag( int NotFlag ) ;								// �`���̃A���t�@�`�����l���̓��e�����������邩��ݒ肷��
extern	int		Graphics_Android_DrawSetting_SetDrawAlphaTest( int TestMode, int TestParam ) ;						// �A���t�@�e�X�g�̐ݒ�
extern	int		Graphics_Android_DrawSetting_SetBlendTextureParam( int BlendType, int *Param ) ;					// �u�����h����e�N�X�`���̃p�����[�^���Z�b�g����
extern	int		Graphics_Android_DrawSetting_SetTexture(      GRAPHICS_ANDROID_TEXTURE *RenderTexture ) ;			// �e�N�X�`�����Z�b�g���� 
extern	int		Graphics_Android_DrawSetting_SetBlendTexture( GRAPHICS_ANDROID_TEXTURE *BlendTexture ) ;			// �u�����h����e�N�X�`�����Z�b�g���� 












// Android �̕`�揈�������֌W
extern	int		Graphics_Android_RenderVertex( int NextUse3DVertex = -1, int ASyncThread = FALSE ) ;	// ���_�o�b�t�@�ɗ��܂������_�f�[�^�������_�����O����
extern	void	FASTCALL Graphics_Android_DrawPreparation( int ParamFlag = 0 ) ;						// �`�揀�����s��
extern	void	Graphics_Android_RenderBegin( void ) ;													// �`��R�}���h���J�n����
extern	void	Graphics_Android_RenderEnd( void ) ;													// �`��R�}���h���I������












// Android ���g�����`��֌W
extern	void	Graphics_Android_DrawModiTex( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, IMAGEDATA_HARD_DRAW *DrawTex, bool SimpleDrawFlag ) ;								// �e�N�X�`����ό`���ĕ`�悷��
extern	void	Graphics_Android_DrawPreparationToShader( int ParamFlag, int Is2D ) ;											// �V�F�[�_�[�`��p�`��O�Z�b�g�A�b�v�֐�










#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_GRAPHICS

#endif // DX_GRAPHICSANDROID_H

