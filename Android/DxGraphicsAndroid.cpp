//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�`�揈���v���O����( Android )
// 
//  	Ver 3.22a
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_GRAPHICS

// �C���N���[�h ---------------------------------------------------------------
#include "DxGraphicsAndroid.h"
#include "DxGraphicsFilterAndroid.h"
#include "DxLive2DCubism4Android.h"
#include "DxMaskAndroid.h"
#include "DxMemoryAndroid.h"
#include "DxSystemAndroid.h"
#include "../DxSystem.h"
#include "../DxLog.h"
#include "../DxModel.h"
#include "../DxMemory.h"
#include "../DxMovie.h"
#include "../DxMask.h"
#include "../DxMath.h"
#include "../DxBaseFunc.h"
#include "../DxGraphics.h"
#include "../DxGraphicsFilter.h"
#include "../DxInput.h"
#include "../DxASyncLoad.h"
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//#include <error.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` -----------------------------------------------------------------

#define ANDR_CHECKVALID_HARDWARE									\
		( ( g_AndroidSys.NativeWindow  != NULL &&							\
		    GANDR.Device.Screen.Context != EGL_NO_CONTEXT ) ? TRUE : FALSE )

// Graphics_Android_DrawPreparation ���ĂԒ�^��
#define DX_ANDROID_DRAWPREP_NOTEX( FLAG )													\
	if( GANDR.Device.DrawInfo.BeginSceneFlag == FALSE ) Graphics_Android_RenderBegin() ;	\
	if( GANDR.Device.DrawSetting.RenderTexture != NULL )									\
		Graphics_Android_DrawSetting_SetTexture( NULL ) ;									\
	if( GSYS.ChangeSettingFlag ||															\
		GANDR.Device.DrawSetting.DrawPrepAlwaysFlag != FALSE ||								\
		GANDR.Device.DrawSetting.DrawPrepParamFlag  != FLAG )								\
		Graphics_Android_DrawPreparation( FLAG ) ;												


#define DX_ANDROID_DRAWPREP_TEX( ORIG, TEX, FLAG )											\
	FLAG |= DX_ANDROID_DRAWPREP_TEXTURE ;													\
	if( (ORIG)->FormatDesc.AlphaChFlag   ) FLAG |= DX_ANDROID_DRAWPREP_TEXALPHACH ;			\
	if( (ORIG)->FormatDesc.AlphaTestFlag ) FLAG |= DX_ANDROID_DRAWPREP_TEXALPHATEST ;		\
	if( GANDR.Device.DrawInfo.BeginSceneFlag == FALSE ) Graphics_Android_RenderBegin() ;		\
	if( GANDR.Device.DrawSetting.RenderTexture != (TEX) )								\
		Graphics_Android_DrawSetting_SetTexture( (TEX) ) ;									\
	if( GSYS.ChangeSettingFlag ||														\
		GANDR.Device.DrawSetting.DrawPrepAlwaysFlag != FALSE ||							\
		GANDR.Device.DrawSetting.DrawPrepParamFlag  != FLAG )							\
		Graphics_Android_DrawPreparation( FLAG ) ;


#define GETVERTEX_POINT( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex != 0 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_POINTS ||\
		  GANDR.Device.DrawInfo.VertexNum + 1 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 0 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_POINTS ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;


#define GETVERTEX_POINT3D( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex != 1 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_POINTS ||\
		  GANDR.Device.DrawInfo.VertexNum + 1 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 1 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_POINTS ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;


#define GETVERTEX_LINEBOX( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex != 0 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_TRIANGLES ||\
		  GANDR.Device.DrawInfo.VertexNum + 24 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 0 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_TRIANGLES ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;


#define GETVERTEX_LINETRIANGLE( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex != 0 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_LINES ||\
		  GANDR.Device.DrawInfo.VertexNum + 6 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 0 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_LINES ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;


#define GETVERTEX_LINETRIANGLE3D( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex != 1 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_LINES ||\
		  GANDR.Device.DrawInfo.VertexNum + 6 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 1 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_LINES ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;


#define GETVERTEX_LINE( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex == 1 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_LINES ||\
		  GANDR.Device.DrawInfo.VertexNum + 2 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 0 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_LINES ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;


#define GETVERTEX_LINE3D( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex != 1 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_LINES ||\
		  GANDR.Device.DrawInfo.VertexNum + 2 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 1 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_LINES ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;



#define GETVERTEX_QUAD( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex != 0 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_TRIANGLES ||\
		  GANDR.Device.DrawInfo.VertexNum + 6 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 0 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_TRIANGLES ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;


#define GETVERTEX_TRIANGLE( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex != 0 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_TRIANGLES ||\
		  GANDR.Device.DrawInfo.VertexNum + 3 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 0 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_TRIANGLES ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;


#define GETVERTEX_TRIANGLE3D( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex != 1 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_TRIANGLES ||\
		  GANDR.Device.DrawInfo.VertexNum + 3 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 1 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_TRIANGLES ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;


#define GETVERTEX_BILLBOARD( p )		\
	MV1DRAWPACKDRAWMODEL		\
	if(\
		  GANDR.Device.DrawInfo.Use3DVertex != 1 ||\
		  GANDR.Device.DrawInfo.PrimitiveType != GL_TRIANGLES ||\
		  GANDR.Device.DrawInfo.VertexNum + 6 >= ANDROID_VertexBuffer_MaxVertexNum[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ]\
	  )\
	{\
		Graphics_Android_RenderVertex( 1 ) ;\
		GANDR.Device.DrawInfo.PrimitiveType = GL_TRIANGLES ;\
	}\
	*( ( void ** )&p ) = ( void * )GANDR.Device.DrawInfo.VertexBufferNextAddr ;




#define ADD4VERTEX_POINT		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_NOTEX_2D ) ;	\
		GANDR.Device.DrawInfo.VertexNum ++ ;

#define ADD4VERTEX_POINT3D		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_NOTEX_3D ) ;	\
		GANDR.Device.DrawInfo.VertexNum ++ ;

#define ADD4VERTEX_LINEBOX			\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_NOTEX_2D ) * 24 ;\
		GANDR.Device.DrawInfo.VertexNum += 24 ;

#define ADD4VERTEX_LINETRIANGLE		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_NOTEX_2D ) * 6 ;	\
		GANDR.Device.DrawInfo.VertexNum += 6 ;

#define ADD4VERTEX_LINETRIANGLE3D		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_NOTEX_3D ) * 6 ;	\
		GANDR.Device.DrawInfo.VertexNum += 6 ;

#define ADD4VERTEX_LINE			\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_NOTEX_2D ) * 2 ;	\
		GANDR.Device.DrawInfo.VertexNum += 2 ;

#define ADD4VERTEX_LINE3D		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_NOTEX_3D ) * 2 ;	\
		GANDR.Device.DrawInfo.VertexNum += 2 ;

#define ADD4VERTEX_NOTEX		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_NOTEX_2D ) * 6 ;	\
		GANDR.Device.DrawInfo.VertexNum += 6 ;

#define ADD4VERTEX_TEX			\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_2D ) * 6 ;	\
		GANDR.Device.DrawInfo.VertexNum += 6 ;

#define ADD4VERTEX_BLENDTEX		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_BLENDTEX_2D ) * 6 ;	\
		GANDR.Device.DrawInfo.VertexNum += 6 ;

#define ADD3VERTEX_NOTEX		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_NOTEX_2D ) * 3 ;	\
		GANDR.Device.DrawInfo.VertexNum += 3 ;

#define ADD3VERTEX_TEX			\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_2D ) * 3 ;	\
		GANDR.Device.DrawInfo.VertexNum += 3 ;

#define ADD3VERTEX_BLENDTEX		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_BLENDTEX_2D ) * 3 ;	\
		GANDR.Device.DrawInfo.VertexNum += 3 ;

#define ADD3VERTEX_NOTEX3D		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_NOTEX_3D ) * 3 ;	\
		GANDR.Device.DrawInfo.VertexNum += 3 ;

#define ADD4VERTEX_BILLBOARD		\
		GANDR.Device.DrawInfo.VertexBufferNextAddr += sizeof( VERTEX_3D ) * 6 ;	\
		GANDR.Device.DrawInfo.VertexNum += 6 ;

#define SETUPCOLOR( DEST )		\
	if( GSYS.HardInfo.UseVertexColorBGRAFormat )\
	{\
		DEST  = ( ( ( ( ( 	GANDR.Device.DrawInfo.DiffuseColor & 0x00ff0000 ) >> 16 ) * Red   ) / 255 ) << 16 ) |\
				( ( ( ( ( 	GANDR.Device.DrawInfo.DiffuseColor & 0x0000ff00 ) >> 8  ) * Green ) / 255 ) << 8  ) |\
				( ( ( ( (	GANDR.Device.DrawInfo.DiffuseColor & 0x000000ff )       ) * Blue  ) / 255 )       ) | \
				( 			GANDR.Device.DrawInfo.DiffuseColor & 0xff000000 ) ;\
	}\
	else\
	{\
		DEST  = ( ( ( ( ( 	GANDR.Device.DrawInfo.DiffuseColor & 0x000000ff )       ) * Red   ) / 255 )       ) |\
				( ( ( ( ( 	GANDR.Device.DrawInfo.DiffuseColor & 0x0000ff00 ) >> 8  ) * Green ) / 255 ) << 8  ) |\
				( ( ( ( (	GANDR.Device.DrawInfo.DiffuseColor & 0x00ff0000 ) >> 16 ) * Blue  ) / 255 ) << 16 ) | \
				( 			GANDR.Device.DrawInfo.DiffuseColor & 0xff000000 ) ;\
	}


// RGB�l���P�x�ő��RGB�l�ɕϊ����邽�߂̃{�����[���e�N�X�`���̃T�C�Y
#define RGBTOVMAXRGB_TEX_SIZE		(128)

// �\���̐錾 -----------------------------------------------------------------

// �W���`��p�̕��G�ȏ������s��Ȃ����_�V�F�[�_�[�̏��
typedef struct tagGRAPHICS_ANDROID_BASE_SIMPLE_VERTEXSHADER_INFO
{
	const char *					ShaderFileName ;			// �g�p���钸�_�V�F�[�_�[�t�@�C����
	VERTEXBUFFER_INPUT_INFO_ANDR	InputInfo ;					// ���͒��_�f�[�^���
} GRAPHICS_ANDROID_BASE_SIMPLE_VERTEXSHADER_INFO ;

// �f�[�^��` -----------------------------------------------------------------

DX_ANDROID_RENDER_BLEND_INFO g_DefaultBlendDescArray[ DX_BLENDMODE_NUM ] =
{
	{ ANDROID_RENDER_TYPE_NORMAL,		FALSE, GL_ONE,					GL_ZERO,				GL_FUNC_ADD,				GL_ONE,			GL_ZERO,				GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_NOBLEND			�m�[�u�����h
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_SRC_ALPHA,			GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				GL_SRC_ALPHA,	GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_ALPHA			���u�����h
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_SRC_ALPHA,			GL_ONE,					GL_FUNC_ADD,				GL_SRC_ALPHA,	GL_ONE,					GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_ADD				���Z�u�����h
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_ONE_MINUS_DST_COLOR,	GL_ZERO,				GL_FUNC_ADD,				GL_DST_ALPHA,	GL_ZERO,				GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_SUB				���Z�u�����h
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_ZERO,					GL_SRC_COLOR,			GL_FUNC_ADD,				GL_ZERO,		GL_SRC_ALPHA,			GL_FUNC_ADD,				FALSE },	// DX_BLENDMODE_MUL				��Z�u�����h
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_SRC_ALPHA,			GL_ONE,					GL_FUNC_ADD,				GL_SRC_ALPHA,	GL_ONE,					GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_SUB2			���������p���Z�u�����h�P
	{ ANDROID_RENDER_TYPE_NORMAL,		FALSE, GL_ONE,					GL_ZERO,				GL_FUNC_ADD,				GL_ONE,			GL_ZERO,				GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_XOR				XOR�u�����h(��Ή�)
	{ ANDROID_RENDER_TYPE_NORMAL,		FALSE, GL_ONE,					GL_ZERO,				GL_FUNC_ADD,				GL_ONE,			GL_ZERO,				GL_FUNC_ADD,				 TRUE },	// ����
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_ZERO,					GL_ONE,					GL_FUNC_ADD,				GL_ZERO,		GL_ONE,					GL_FUNC_ADD,				FALSE },	// DX_BLENDMODE_DESTCOLOR		�J���[�͍X�V����Ȃ�
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_ONE_MINUS_DST_COLOR,	GL_ZERO,				GL_FUNC_ADD,				GL_DST_ALPHA,	GL_ZERO,				GL_FUNC_ADD,				FALSE },	// DX_BLENDMODE_INVDESTCOLOR	�`���̐F�̔��]�l���|����
	{ ANDROID_RENDER_TYPE_INVERSE,		TRUE,  GL_SRC_ALPHA,			GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				GL_SRC_ALPHA,	GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_INVSRC			�`�挳�̐F�𔽓]����
	{ ANDROID_RENDER_TYPE_MUL,			TRUE,  GL_ZERO,					GL_SRC_COLOR,			GL_FUNC_ADD,				GL_ZERO,		GL_SRC_ALPHA,			GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_MULA			�A���t�@�`�����l���l���t����Z�u�����h
	{ ANDROID_RENDER_TYPE_X4,			TRUE,  GL_SRC_ALPHA,			GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				GL_SRC_ALPHA,	GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_ALPHA_X4		���u�����h�̕`�摤�̋P�x���ő�S�{�ɂł��郂�[�h
	{ ANDROID_RENDER_TYPE_X4,			TRUE,  GL_SRC_ALPHA,			GL_ONE,					GL_FUNC_ADD,				GL_SRC_ALPHA,	GL_ONE,					GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_ADD_X4			���Z�u�����h�̕`�摤�̋P�x���ő�S�{�ɂł��郂�[�h
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_ONE,					GL_ZERO,				GL_FUNC_ADD,				GL_ONE,			GL_ZERO,				GL_FUNC_ADD,				FALSE },	// DX_BLENDMODE_SRCCOLOR		�`�挳�̃J���[�ł��̂܂ܕ`�悳���
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_ONE,					GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				GL_ONE,			GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				FALSE },	// DX_BLENDMODE_HALF_ADD		�����Z�u�����h
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_SRC_ALPHA,			GL_ONE,					GL_FUNC_REVERSE_SUBTRACT,	GL_SRC_ALPHA,	GL_ONE,					GL_FUNC_REVERSE_SUBTRACT,	 TRUE },	// DX_BLENDMODE_SUB1			�o�̓u�����h���g�p�\�ȏꍇ�̌��Z�u�����h

	{ ANDROID_RENDER_TYPE_PMA_NORMAL,	TRUE,  GL_ONE,					GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				GL_ONE,			GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_PMA_ALPHA		��Z�ς݃��u�����h���[�h�̃��u�����h
	{ ANDROID_RENDER_TYPE_PMA_NORMAL,	TRUE,  GL_ONE,					GL_ONE,					GL_FUNC_ADD,				GL_ONE,			GL_ONE,					GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_PMA_ADD			��Z�ς݃��u�����h���[�h�̉��Z�u�����h
	{ ANDROID_RENDER_TYPE_PMA_NORMAL,	TRUE,  GL_ONE,					GL_ONE,					GL_FUNC_REVERSE_SUBTRACT,	GL_ONE,			GL_ONE,					GL_FUNC_REVERSE_SUBTRACT,	 TRUE },	// DX_BLENDMODE_PMA_SUB			��Z�ς݃��u�����h���[�h�̌��Z�u�����h
	{ ANDROID_RENDER_TYPE_PMA_INVERSE,	TRUE,  GL_ONE,					GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				GL_ONE,			GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_PMA_INVSRC		��Z�ς݃��u�����h���[�h�̕`�挳�̐F�𔽓]����
	{ ANDROID_RENDER_TYPE_PMA_X4,		TRUE,  GL_ONE,					GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				GL_ONE,			GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_PMA_ALPHA_X4	��Z�ς݃��u�����h���[�h�̃��u�����h�̕`�摤�̋P�x���ő�S�{�ɂł��郂�[�h
	{ ANDROID_RENDER_TYPE_PMA_X4,		TRUE,  GL_ONE,					GL_ONE,					GL_FUNC_ADD,				GL_ONE,			GL_ONE,					GL_FUNC_ADD,				 TRUE },	// DX_BLENDMODE_PMA_ADD_X4		��Z�ς݃��u�����h���[�h�̉��Z�u�����h�̕`�摤�̋P�x���ő�S�{�ɂł��郂�[�h

	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_ZERO,					GL_ZERO,				GL_FUNC_ADD,				GL_ZERO,		GL_ZERO,				GL_FUNC_ADD,				 FALSE },	// DX_BLENDMODE_LIVE2D_ZERO		Live2D �̃u�����h���[�h Zero �p
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_ONE,					GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				GL_ONE,			GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				 FALSE },	// DX_BLENDMODE_LIVE2D_NORMAL	Live2D �̃u�����h���[�h Normal �p
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_ONE,					GL_ONE,					GL_FUNC_ADD,				GL_ZERO,		GL_ONE,					GL_FUNC_ADD,				 FALSE },	// DX_BLENDMODE_LIVE2D_ADD		Live2D �̃u�����h���[�h Add �p
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_DST_COLOR,			GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				GL_ZERO,		GL_ONE,					GL_FUNC_ADD,				 FALSE },	// DX_BLENDMODE_LIVE2D_MULT		Live2D �̃u�����h���[�h Mult �p
	{ ANDROID_RENDER_TYPE_NORMAL,		TRUE,  GL_ZERO,					GL_ONE_MINUS_SRC_COLOR,	GL_FUNC_ADD,				GL_ZERO,		GL_ONE_MINUS_SRC_ALPHA,	GL_FUNC_ADD,				 FALSE },	// DX_BLENDMODE_LIVE2D_MASK		Live2D �̃u�����h���[�h Mask �p
} ;

// ���_�o�b�t�@�Ɋi�[�ł��钸�_�̍ő吔�̃e�[�u��
static const int ANDROID_VertexBuffer_MaxVertexNum[ ANDROID_VERTEX_INPUTLAYOUT_NUM ] =
{
	DX_GLES2_VERTBUFFERSIZE / sizeof( VERTEX_NOTEX_2D    ),
	DX_GLES2_VERTBUFFERSIZE / sizeof( VERTEX_2D          ),
	DX_GLES2_VERTBUFFERSIZE / sizeof( VERTEX_BLENDTEX_2D ),
	DX_GLES2_VERTBUFFERSIZE / sizeof( VERTEX_NOTEX_3D    ),
	DX_GLES2_VERTBUFFERSIZE / sizeof( VERTEX_3D          ),
	DX_GLES2_VERTBUFFERSIZE / sizeof( VERTEX3D           ),
	DX_GLES2_VERTBUFFERSIZE / sizeof( VERTEX3DSHADER     ),
} ;

// �R�c���_���ǂ����ƒ��_�^�C�v�̑g�ݍ��킹�ɑΉ����钸�_�f�[�^�^�C�v[ 0:�Q�c���_  1:�R�c���_ ][ ���_�^�C�v ]
static const int g_VertexTypeToInputLayout[ 2 ][ VERTEXTYPE_NUM ] =
{
	{
		ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D,
		ANDROID_VERTEX_INPUTLAYOUT_2D,
		ANDROID_VERTEX_INPUTLAYOUT_BLENDTEX_2D,
	},

	{
		ANDROID_VERTEX_INPUTLAYOUT_NOTEX_3D,
		ANDROID_VERTEX_INPUTLAYOUT_3D,
		-1,
	},
} ;

// �P�ʍs��
static MATRIX ANDROID_GlobalIdentMatrix =
{
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	}
} ;

// �c�w���C�u�����̃v���~�e�B�u�^�C�v�� SceGxmPrimitiveType �ɕϊ����邽�߂̃e�[�u��
GLenum g_DXPrimitiveTypeToGLES2PrimitiveType[] =
{
	0,
	GL_POINTS,				// DX_PRIMTYPE_POINTLIST		(1)
	GL_LINES,				// DX_PRIMTYPE_LINELIST			(2)
	GL_LINE_STRIP,			// DX_PRIMTYPE_LINESTRIP		(3)
	GL_TRIANGLES,			// DX_PRIMTYPE_TRIANGLELIST		(4)
	GL_TRIANGLE_STRIP,		// DX_PRIMTYPE_TRIANGLESTRIP	(5)
	GL_TRIANGLE_FAN,		// DX_PRIMTYPE_TRIANGLEFAN		(6)
} ;

// �c�w���C�u�����̔�r���[�h�� SceGxmDepthFunc �ɕϊ����邽�߂̃e�[�u��
GLenum g_DXCmpModeToGLES2CompareFunc[ 9 ] =
{
	0,
	GL_NEVER,				// DX_CMP_NEVER			(1)		// FALSE
	GL_LESS,				// DX_CMP_LESS			(2)		// Src <  Dest		DrawAlpha <  TestParam
	GL_EQUAL,				// DX_CMP_EQUAL			(3)		// Src == Dest		DrawAlpha == TestParam
	GL_LEQUAL,				// DX_CMP_LESSEQUAL		(4)		// Src <= Dest		DrawAlpha <= TestParam
	GL_GREATER,				// DX_CMP_GREATER		(5)		// Src >  Dest		DrawAlpha >  TestParam
	GL_NOTEQUAL,			// DX_CMP_NOTEQUAL		(6)		// Src != Dest		DrawAlpha != TestParam
	GL_GEQUAL,				// DX_CMP_GREATEREQUAL	(7)		// Src >= Dest		DrawAlpha >= TestParam
	GL_ALWAYS,				// DX_CMP_ALWAYS		(8)		// TRUE
} ;

#define GLES2WrapModeToDXTexAddrMode( GLMode )	\
	((GLMode) == GL_REPEAT ? DX_TEXADDRESS_WRAP : ( (GLMode) == GL_MIRRORED_REPEAT ? DX_TEXADDRESS_MIRROR : DX_TEXADDRESS_CLAMP ))


// �c�w���C�u�����̃e�N�X�`���A�h���X���[�h�� ANDRWrapMode �ɕϊ����邽�߂̃e�[�u��
GLenum g_DXTexAddrModeToGLES2WrapMode[ DX_TEXADDRESS_NUM ] =
{
	0,						// �c�w���C�u�����ł͖��g�p
	GL_REPEAT,				// DX_TEXADDRESS_WRAP	(1)
	GL_MIRRORED_REPEAT,		// DX_TEXADDRESS_MIRROR	(2)
	GL_CLAMP_TO_EDGE,		// DX_TEXADDRESS_CLAMP	(3)
	GL_CLAMP_TO_EDGE,		// DX_TEXADDRESS_BORDER	(4)
} ;

// ���_�f�[�^�v�f��{���
VERTEXBUFFER_INPUT_ELEMENT_INFO_BASE_ANDR g_VertexElementInfoBase[ ANDROID_VERTEX_ATTR_NUM ] =
{
	{ "aPosF2",			2, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_POS_F2
	{ "aPos",			3, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_POS_F3
	{ "aPosF4",			4, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_POS_F4
	{ "aNrm",			3, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_NRM
	{ "aDif",			4, GL_UNSIGNED_BYTE,	GL_TRUE  },	// ANDROID_VERTEX_ATTR_DIF
	{ "aSpc",			4, GL_UNSIGNED_BYTE,	GL_TRUE  },	// ANDROID_VERTEX_ATTR_SPC
	{ "aTexUV0",		2, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TEXUV0_F2
	{ "aTexUV1",		2, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TEXUV1_F2
	{ "aTexUV2",		2, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TEXUV2_F2
	{ "aTexUV3",		2, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TEXUV3_F2
	{ "aTexUV4",		2, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TEXUV4_F2
	{ "aTexUV5",		2, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TEXUV5_F2
	{ "aTexUV6",		2, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TEXUV6_F2
	{ "aTexUV7",		2, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TEXUV7_F2
	{ "aTexUV0F4",		4, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TEXUV0_F4
	{ "aTexUV1F4",		4, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TEXUV1_F4
	{ "aTan",			3, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_TAN
	{ "aBin",			3, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_BIN
	{ "aBlendInd0",		4, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_BLENDIND0
	{ "aBlendWeight0",	4, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_BLENDWEIGHT0
	{ "aBlendInd1",		4, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_BLENDIND1
	{ "aBlendWeight1",	4, GL_FLOAT,			GL_FALSE },	// ANDROID_VERTEX_ATTR_BLENDWEIGHT1
} ;

// StretchRect�p���_�f�[�^�̏��
VERTEXBUFFER_INPUT_INFO_ANDR	g_StretchRectVertexInputInfo =
{
	sizeof( float ) * 4,
	2,
	{
		{ ANDROID_VERTEX_ATTR_POS_F2,    NULL, 0 },
		{ ANDROID_VERTEX_ATTR_TEXUV0_F2, NULL, 8 },
	},
} ;
VERTEXBUFFER_INPUT_INFO_ANDR	g_StretchRectTex2VertexInputInfo =
{
	sizeof( float ) * 6,
	3,
	{
		{ ANDROID_VERTEX_ATTR_POS_F2,    NULL,  0 },
		{ ANDROID_VERTEX_ATTR_TEXUV0_F2, NULL,  8 },
		{ ANDROID_VERTEX_ATTR_TEXUV1_F2, NULL, 16 },
	},
} ;
VERTEXBUFFER_INPUT_INFO_ANDR	g_StretchRectTex8VertexInputInfo =
{
	sizeof( float ) * 18,
	9,
	{
		{ ANDROID_VERTEX_ATTR_POS_F2,    NULL,  0 },
		{ ANDROID_VERTEX_ATTR_TEXUV0_F2, NULL,  8 },
		{ ANDROID_VERTEX_ATTR_TEXUV1_F2, NULL, 16 },
		{ ANDROID_VERTEX_ATTR_TEXUV2_F2, NULL, 24 },
		{ ANDROID_VERTEX_ATTR_TEXUV3_F2, NULL, 32 },
		{ ANDROID_VERTEX_ATTR_TEXUV4_F2, NULL, 40 },
		{ ANDROID_VERTEX_ATTR_TEXUV5_F2, NULL, 48 },
		{ ANDROID_VERTEX_ATTR_TEXUV6_F2, NULL, 56 },
		{ ANDROID_VERTEX_ATTR_TEXUV7_F2, NULL, 64 },
	},
} ;

// �}�X�N�p���_�f�[�^�̏��
VERTEXBUFFER_INPUT_INFO_ANDR	g_MaskVertexInputInfo =
{
	sizeof( float ) * 6,
	3,
	{
		{ ANDROID_VERTEX_ATTR_POS_F2,    NULL,  0 },
		{ ANDROID_VERTEX_ATTR_TEXUV0_F2, NULL,  8 },
		{ ANDROID_VERTEX_ATTR_TEXUV1_F2, NULL, 16 },
	},
} ;

// �N���A�����p���_�f�[�^�̏��
VERTEXBUFFER_INPUT_INFO_ANDR	g_ClearRTVertexInputInfo =
{
	sizeof( float ) * 2,
	1,
	{
		{ ANDROID_VERTEX_ATTR_POS_F2, NULL,  0 },
	},
} ;

// �W���`��p�̕��G�ȏ������s��Ȃ����_�V�F�[�_�[�̏��
static GRAPHICS_ANDROID_BASE_SIMPLE_VERTEXSHADER_INFO g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_NUM ] =
{
	// ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D( VERTEX_NOTEX_2D )
	{
		"Base_VERTEX_NOTEX_2D.vert",
		{
			sizeof( VERTEX_NOTEX_2D ),
			2,
			{
				{ ANDROID_VERTEX_ATTR_POS_F4,		NULL,	0	},
				{ ANDROID_VERTEX_ATTR_DIF,			NULL,	16	},
			},
		},
	},

	// ANDROID_VERTEX_INPUTLAYOUT_2D( VERTEX2D or VERTEX_2D )
	{
		"Base_VERTEX2D.vert",
		{
			sizeof( VERTEX2D ),
			3,
			{
				{ ANDROID_VERTEX_ATTR_POS_F4,		NULL,	0	},
				{ ANDROID_VERTEX_ATTR_DIF,			NULL,	16	},
				{ ANDROID_VERTEX_ATTR_TEXUV0_F2,	NULL,	20	},
			},
		},
	},

	// ANDROID_VERTEX_INPUTLAYOUT_BLENDTEX_2D( VERTEX_BLENDTEX_2D or VERTEX2DSHADER )
	{
		"Base_VERTEX_BLENDTEX_2D.vert",
		{
			sizeof( VERTEX_BLENDTEX_2D ),
			4,
			{
				{ ANDROID_VERTEX_ATTR_POS_F4,		NULL,	0	},
				{ ANDROID_VERTEX_ATTR_DIF,			NULL,	16	},
				{ ANDROID_VERTEX_ATTR_TEXUV0_F2,	NULL,	24	},
				{ ANDROID_VERTEX_ATTR_TEXUV1_F2,	NULL,	32	},
			},
		},
	},

	// ANDROID_VERTEX_INPUTLAYOUT_NOTEX_3D( VERTEX_NOTEX_3D )
	{
		"Base_VERTEX_NOTEX_3D.vert",
		{
			sizeof( VERTEX_NOTEX_3D ),
			2,
			{
				{ ANDROID_VERTEX_ATTR_POS_F3,		NULL,	0	},
				{ ANDROID_VERTEX_ATTR_DIF,			NULL,	12	},
			},
		},
	},

	// ANDROID_VERTEX_INPUTLAYOUT_3D( VERTEX_3D )
	{
		"Base_VERTEX_3D.vert",
		{
			sizeof( VERTEX_3D ),
			3,
			{
				{ ANDROID_VERTEX_ATTR_POS_F3,		NULL,	0	},
				{ ANDROID_VERTEX_ATTR_DIF,			NULL,	12	},
				{ ANDROID_VERTEX_ATTR_TEXUV0_F2,	NULL,	16	},
			},
		},
	},

	// ANDROID_VERTEX_INPUTLAYOUT_3D_LIGHT( VERTEX3D )
	{
		"Base_VERTEX3D.vert",
		{
			sizeof( VERTEX3D ),
			6,
			{
				{ ANDROID_VERTEX_ATTR_POS_F3,		NULL,	0	},
				{ ANDROID_VERTEX_ATTR_NRM,			NULL,	12	},
				{ ANDROID_VERTEX_ATTR_DIF,			NULL,	24	},
				{ ANDROID_VERTEX_ATTR_SPC,			NULL,	28	},
				{ ANDROID_VERTEX_ATTR_TEXUV0_F2,	NULL,	32	},
				{ ANDROID_VERTEX_ATTR_TEXUV1_F2,	NULL,	40	},
			},
		},
	},

	// ANDROID_VERTEX_INPUTLAYOUT_SHADER_3D( VERTEX3DSHADER )
	{
		"Base_VERTEX3DSHADER.vert",
		{
			sizeof( VERTEX3DSHADER ),
			9,
			{
				{ ANDROID_VERTEX_ATTR_POS_F3,		NULL,	0	},
				{ ANDROID_VERTEX_ATTR_POS_F4,		NULL,	12	},
				{ ANDROID_VERTEX_ATTR_NRM,			NULL,	28	},
				{ ANDROID_VERTEX_ATTR_TAN,			NULL,	40	},
				{ ANDROID_VERTEX_ATTR_BIN,			NULL,	52	},
				{ ANDROID_VERTEX_ATTR_DIF,			NULL,	64	},
				{ ANDROID_VERTEX_ATTR_SPC,			NULL,	68	},
				{ ANDROID_VERTEX_ATTR_TEXUV0_F2,	NULL,	72	},
				{ ANDROID_VERTEX_ATTR_TEXUV1_F2,	NULL,	80	},
			},
		},
	},
} ;

// �s�N�Z���t�H�[�}�b�g
PIXELFORMAT_INFO_ANDR g_AndroidPixelFormat[ ANDROID_PIXEL_FORMAT_NUM ] =
{
	{ FALSE,	 32,	      0,	GL_RGBA,					GL_RGBA,		GL_UNSIGNED_BYTE			},	// ANDROID_PIXEL_FORMAT_R8G8B8A8
	{ FALSE,	 24,	      0,	GL_RGB,						GL_RGB,			GL_UNSIGNED_BYTE			},	// ANDROID_PIXEL_FORMAT_R8G8B8
	{ FALSE,	 16,	      0,	GL_RGBA,					GL_RGBA,		GL_UNSIGNED_SHORT_4_4_4_4	},	// ANDROID_PIXEL_FORMAT_R4G4B4A4
	{ FALSE,	 16,	      0,	GL_RGBA,					GL_RGBA,		GL_UNSIGNED_SHORT_5_5_5_1	},	// ANDROID_PIXEL_FORMAT_R5G5B5A1
	{ FALSE,	 16,	      0,	GL_RGB,						GL_RGB,			GL_UNSIGNED_SHORT_5_6_5		},	// ANDROID_PIXEL_FORMAT_R5G6B5
	{ TRUE,		  4,	 16 * 3,	GL_PALETTE4_RGB8_OES,		0,				0							},	// ANDROID_PIXEL_FORMAT_R8G8B8_PAL4
	{ TRUE,		  8,	256 * 3,	GL_PALETTE8_RGB8_OES,		0,				0							},	// ANDROID_PIXEL_FORMAT_R8G8B8_PAL8
	{ TRUE,		  4,	 16 * 4,	GL_PALETTE4_RGBA8_OES,		0,				0							},	// ANDROID_PIXEL_FORMAT_R8G8B8A8_PAL4
	{ TRUE,		  8,	256 * 4,	GL_PALETTE8_RGBA8_OES,		0,				0							},	// ANDROID_PIXEL_FORMAT_R8G8B8A8_PAL8
	{ TRUE,		  4,	 16 * 2,	GL_PALETTE4_RGB5_A1_OES,	0,				0							},	// ANDROID_PIXEL_FORMAT_R5G5B5A1_PAL4
	{ TRUE,		  8,	256 * 2,	GL_PALETTE8_RGB5_A1_OES,	0,				0							},	// ANDROID_PIXEL_FORMAT_R5G5B5A1_PAL8
	{ FALSE,	  8,	      0,	GL_LUMINANCE,				GL_LUMINANCE,	GL_UNSIGNED_BYTE			},	// ANDROID_PIXEL_FORMAT_R8
	{ FALSE,	 48,	      0,	GL_RGB,						GL_RGB,			GL_HALF_FLOAT_OES			},	// ANDROID_PIXEL_FORMAT_R16G16B16_FLOAT
	{ FALSE,	 96,	      0,	GL_RGB,						GL_RGB,			GL_FLOAT					},	// ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT
	{ FALSE,	 64,	      0,	GL_RGBA,					GL_RGBA,		GL_HALF_FLOAT_OES			},	// ANDROID_PIXEL_FORMAT_R16G16B16A16_FLOAT
	{ FALSE,	128,	      0,	GL_RGBA,					GL_RGBA,		GL_FLOAT					},	// ANDROID_PIXEL_FORMAT_R32G32B32A32_FLOAT
} ;

// Extension �̖��O
const char *g_AndroidGLExtensionName[ ANDROID_GL_EXTENSION_NUM ] =
{
	"GL_OES_depth24",						// ANDROID_GL_EXTENSION_DEPTH24						
	"GL_OES_depth32",						// ANDROID_GL_EXTENSION_DEPTH32						
	"GL_OES_element_index_uint",			// ANDROID_GL_EXTENSION_ELEMENT_INDEX_UNIT			
	"GL_OES_texture_float",					// ANDROID_GL_EXTENSION_TEXTURE_FLOAT				
	"GL_OES_texture_float_linear",			// ANDROID_GL_EXTENSION_TEXTURE_FLOAT_LINEAR		
	"GL_OES_compressed_paletted_texture",	// ANDROID_GL_EXTENSION_COMPRESSED_PALETTED_TEXTURE	
	"GL_OES_compressed_ETC1_RGB8_texture",	// ANDROID_GL_EXTENSION_COMPRESSED_ETC1_RGB8_TEXTURE
	"GL_OES_depth_texture",					// ANDROID_GL_EXTENSION_DEPTH_TEXTURE				
	"GL_OES_texture_half_float",			// ANDROID_GL_EXTENSION_TEXTURE_HALF_FLOAT			
	"GL_OES_texture_half_float_linear",		// ANDROID_GL_EXTENSION_TEXTURE_HALF_FLOAT_LINEAR	
	"GL_OES_vertex_half_float",				// ANDROID_GL_EXTENSION_VERTEX_HALF_FLOAT
	"GL_OES_texture_3D",					// ANDROID_GL_EXTENSION_TEXTURE_3D
	"GL_EXT_texture_format_BGRA8888",		// ANDROID_GL_EXTENSION_TEXTURE_FORMAT_BGRA8888
} ;

// Uniform �̖��O
const GLchar *g_UniformName[ ANDROID_SHADER_UNIFORM_NUM ] =
{
	"uSrcTex",						// ANDROID_SHADER_UNIFORM_SRC_TEX
	"uBlendTex",					// ANDROID_SHADER_UNIFORM_BLEND_TEX
	"uDifMapTex",					// ANDROID_SHADER_UNIFORM_DIF_MAP_TEX
	"uNrmMapTex",					// ANDROID_SHADER_UNIFORM_NRM_MAP_TEX
	"uSpcMapTex",					// ANDROID_SHADER_UNIFORM_SPC_MAP_TEX
	"uToonDifGradTex",				// ANDROID_SHADER_UNIFORM_TOON_DIF_GRAD_TEX
	"uToonSpcGradTex",				// ANDROID_SHADER_UNIFORM_TOON_SPC_GRAD_TEX
	"uToonSphereMapTex",			// ANDROID_SHADER_UNIFORM_TOON_SPHERE_MAP_TEX
	"uToonRGBtoVMaxRGBVolTex",		// ANDROID_SHADER_UNIFORM_TOON_RGB_TO_VMAXRGBVOL_TEX
	"uSubTex",						// ANDROID_SHADER_UNIFORM_SUB_TEX
	"uShadowMap0Tex",				// ANDROID_SHADER_UNIFORM_SHADOW_MAP0_TEX
	"uShadowMap1Tex",				// ANDROID_SHADER_UNIFORM_SHADOW_MAP1_TEX
	"uShadowMap2Tex",				// ANDROID_SHADER_UNIFORM_SHADOW_MAP2_TEX
	"uAmb_Emi",						// ANDROID_SHADER_UNIFORM_AMB_EMI
	"uMatDif",						// ANDROID_SHADER_UNIFORM_MAT_DIF
	"uMatSpc",						// ANDROID_SHADER_UNIFORM_MAT_SPC
	"uMatPow",						// ANDROID_SHADER_UNIFORM_MAT_POW
	"uMatTypeParam0",				// ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM0
	"uMatTypeParam1",				// ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM1
	"uMatTypeParam2",				// ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM2
	"uLightPos",					// ANDROID_SHADER_UNIFORM_LIGHT_POS
	"uLightDir",					// ANDROID_SHADER_UNIFORM_LIGHT_DIR
	"uLightDif",					// ANDROID_SHADER_UNIFORM_LIGHT_DIF
	"uLightSpc",					// ANDROID_SHADER_UNIFORM_LIGHT_SPC
	"uLightAmb",					// ANDROID_SHADER_UNIFORM_LIGHT_AMB
	"uLightRange_FallOff_AT0_AT1",	// ANDROID_SHADER_UNIFORM_LIGHT_RANGE_FALLOFF_AT0_AT1
	"uLightAT2_SpotP0_SpotP1",		// ANDROID_SHADER_UNIFORM_LIGHT_AT2_SPOTP0_SPOTP1
	"uAntiVPMat",					// ANDROID_SHADER_UNIFORM_ANTI_VIEW_PORT_MAT
	"uViewMat",						// ANDROID_SHADER_UNIFORM_VIEW_MAT
	"uProjMat",						// ANDROID_SHADER_UNIFORM_PROJ_MAT
	"uFog",							// ANDROID_SHADER_UNIFORM_FOG
	"uToonOutLineSize",				// ANDROID_SHADER_UNIFORM_TOON_OUTLINE_SIZE
	"uDifSrc_SpeSrc_MulSpeCol",		// ANDROID_SHADER_UNIFORM_DIFSRC_SPCSRC_MULSPECOL
	"uSMLVPMat",					// ANDROID_SHADER_UNIFORM_SM_LVP_MAT
	"uTexMat",						// ANDROID_SHADER_UNIFORM_TEX_MAT
	"uLWMat",						// ANDROID_SHADER_UNIFORM_LW_MAT
	"uMulAlphaColor",				// ANDROID_SHADER_UNIFORM_MUL_ALPHA_COLOR
	"uATestRef",					// ANDROID_SHADER_UNIFORM_ALPHA_TEST_REF
	"uATestCmpMode",				// ANDROID_SHADER_UNIFORM_ALPHA_TEST_CMPMODE
	"uFogColor",					// ANDROID_SHADER_UNIFORM_FOG_COLOR
	"uFactorColor",					// ANDROID_SHADER_UNIFORM_FACTOR_COLOR
	"uIgnoreTextureColor",			// ANDROID_SHADER_UNIFORM_IGNORE_TEXTURE_COLOR
	"uShadowMapLightEnable",		// ANDROID_SHADER_UNIFORM_SHADOWMAP_LIGHT_ENABLE
	"uShadowMap_DAdj_Grad",			// ANDROID_SHADER_UNIFORM_SHADOWMAP_DADJ_GRAD
} ;

GLenum g_TextureEnum[ USE_TEXTURESTAGE_NUM ] =
{
	GL_TEXTURE0,
	GL_TEXTURE1,
	GL_TEXTURE2,
	GL_TEXTURE3,
	GL_TEXTURE4,
	GL_TEXTURE5,
	GL_TEXTURE6,
	GL_TEXTURE7,
	GL_TEXTURE8,
	GL_TEXTURE9,
	GL_TEXTURE10,
	GL_TEXTURE11,
	GL_TEXTURE12,
	GL_TEXTURE13,
	GL_TEXTURE14,
	GL_TEXTURE15,
} ;

// Android ���g�����O���t�B�b�N�X�������̍\����
GRAPHICS_HARDDATA_ANDR GraphicsHardDataAndroid ;

// �V�F�[�_�[�o�C�i���z��
extern BYTE DxShaderCodeBin_Model_ANDR[] ;
extern BYTE DxShaderCodeBin_Filter_ANDR[] ;
extern BYTE DxShaderCodeBin_Base_ANDR[] ;
extern BYTE DxShaderCodeBin_Base3D_ANDR[] ;
extern BYTE DxShaderCodeBin_RgbaMix_ANDR[] ;

// �֐��錾 -------------------------------------------------------------------

static int Graphics_Android_DeviceState_SetNormalTextureAddressTransformMatrix_ConstBuffer( void ) ;	// �W���`��p�̃e�N�X�`�����W�ϊ��s���萔�o�b�t�@�ɃZ�b�g����
static int Graphics_Android_DeviceState_UpdateConstantFogParam( void ) ;								// �t�H�O�̐F�ȊO�̒萔�����X�V����
static void Graphics_Android_DeviceState_RefreshAmbientAndEmissiveParam( void ) ;						// �A���r�G���g���C�g�ƃG�~�b�V�u�J���[���|�����킹���p�����[�^���X�V����

// glTexSubImage2D �̔񓯊����s�p�̊֐�
static int glTexSubImage2D_ASync(
	GLuint texture,
	GLenum target,
	GLint level,
	GLint xoffset, GLint yoffset,
	GLsizei width, GLsizei height,
	GLenum format, GLenum type,
	const GLvoid* pixels,
	int ASyncThread
) ;


// Android �ɐݒ肷��ˉe�s����X�V����
static void Graphics_Hardware_ANDROID_RefreshProjectionMatrix( void ) ;

static int Graphics_Android_BltBmpOrBaseImageToGraph3_MipMapBlt(
	      IMAGEDATA_ORIG	*Orig,
	const RECT				*SrcRect,
	const RECT				*DestRect,
	      GLuint			UseTex,
	      int				TexWidth,
	      int				TexHeight,
	const BASEIMAGE			*RgbBaseImage,
	const BASEIMAGE			*AlphaBaseImage,
	      int				DestColorFormat,
	      int				RedIsAlphaFlag,
	      int				UseTransColorConvAlpha,
	      int				ASyncThread
) ;

__inline	static DWORD GetDiffuseColor( void )															// ���݂̃f�B�t���[�Y�J���[�𓾂�
			{
				if( GSYS.HardInfo.UseVertexColorBGRAFormat )
				{
					return  ( DWORD )( ( GSYS.DrawSetting.DrawBright.Red   << 16 ) |
									   ( GSYS.DrawSetting.DrawBright.Green << 8  ) |
									   ( GSYS.DrawSetting.DrawBright.Blue        ) |
									   ( ( ( GSYS.DrawSetting.BlendMode != DX_BLENDMODE_NOBLEND || GSYS.DrawSetting.UseNoBlendModeParam ) ? GSYS.DrawSetting.BlendParam : 255 ) << 24 ) ) ;
				}
				else
				{
					return  ( DWORD )( ( GSYS.DrawSetting.DrawBright.Red         ) |
									   ( GSYS.DrawSetting.DrawBright.Green << 8  ) |
									   ( GSYS.DrawSetting.DrawBright.Blue  << 16 ) |
									   ( ( ( GSYS.DrawSetting.BlendMode != DX_BLENDMODE_NOBLEND || GSYS.DrawSetting.UseNoBlendModeParam ) ? GSYS.DrawSetting.BlendParam : 255 ) << 24 ) ) ;
				}
			}


// �v���O���� -----------------------------------------------------------------

// Android ���g�p�����O���t�B�b�N�X�����̏��������s��( 0:���� -1:���s )
extern	int		Graphics_Android_Initialize( void )
{
	// ��ʃ��[�h�ύX�ł̓T�u�o�b�N�o�b�t�@�̍�蒼�������s��
	if( GSYS.Screen.Graphics_Screen_ChangeModeFlag )
	{
		// �T�u�o�b�N�o�b�t�@�̍쐬
		if( Graphics_Android_SetupSubBackBuffer() < 0 )
		{
			return -1 ;
		}

		return 0 ;
	}

	// Android �̃O���t�B�b�N�X�����̎�ȏ��������s��
	if( Graphics_Android_Device_Create() != 0 )
	{
		goto ERR ;
	}

	// �V�F�[�_�[�̍쐬
	if( Graphics_Android_Shader_Initialize() != 0 )
	{
		goto ERR ;
	}

	GSYS.Setting.ValidHardware = GSYS.Setting.NotUseHardware ? FALSE : TRUE ;

	// �I��
	return 0 ;

	// �G���[�I��
ERR :

	// ��n�����s��
	Graphics_Android_Terminate() ;

	return -1 ;
}

// Android ���g�p�����O���t�B�b�N�X�����̌�n�����s��
extern int Graphics_Android_Terminate( void )
{
	// ��ʃ��[�h�ύX�ł̓T�u�o�b�N�o�b�t�@�̍폜�����s��
	if( GSYS.Screen.Graphics_Screen_ChangeModeFlag )
	{
		Graphics_Android_TerminateSubBackBuffer() ;

		return 0 ;
	}

	// �`�揈���̏I��
	Graphics_Android_RenderEnd() ;

#ifndef DX_NON_MODEL
	// ���f���̒��_�o�b�t�@�����
	MV1TerminateVertexBufferAll() ;
#endif // DX_NON_MODEL

	// �e�N�X�`���։摜��]�����邽�߂̃������̌�n�����s��
	Graphics_Android_Texture_TerminateCommonBuffer() ;

	// �V�F�[�_�[�̉��
	Graphics_Android_Shader_Terminate() ;

	// Android �̃O���t�B�b�N�����̌�n�����s��
	Graphics_Android_Device_Delete() ;

	// �I��
	return 0 ;
}

// ���ׂĂ� OpenGL ES �n�I�u�W�F�N�g���������
extern int Graphics_Android_ReleaseObjectAll( void )
{
	int i ;
	SHADERHANDLEDATA                          *Shader ;
	VERTEXBUFFERHANDLEDATA                    *VertexBuffer ;
	INDEXBUFFERHANDLEDATA                     *IndexBuffer ;
	IMAGEDATA                                 *Image ;
	SHADOWMAPDATA                             *ShadowMap ;

	if( HandleManageArray[ DX_HANDLETYPE_GRAPH ].InitializeFlag )
	{
		for( i = HandleManageArray[ DX_HANDLETYPE_GRAPH ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_GRAPH ].AreaMax ; i ++ )
		{
			Image = ( IMAGEDATA * )HandleManageArray[ DX_HANDLETYPE_GRAPH ].Handle[ i ] ;
			if( Image == NULL ) continue ;

#ifndef DX_NON_ASYNCLOAD
			WaitASyncLoad( Image->HandleInfo.Handle ) ;
#endif

			if( Image->Orig == NULL ) continue ;
			Graphics_Hardware_ReleaseOrigTexture_PF( Image->Orig ) ;

#ifndef DX_NON_MOVIE
			if( Image->Orig->MovieHandle != -1 )
			{
				ReleaseMovieSurface( Image->Orig->MovieHandle ) ;
			}
#endif
		}
	}

	if( HandleManageArray[ DX_HANDLETYPE_SHADOWMAP ].InitializeFlag )
	{
		for( i = HandleManageArray[ DX_HANDLETYPE_SHADOWMAP ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_SHADOWMAP ].AreaMax ; i ++ )
		{
			ShadowMap = ( SHADOWMAPDATA * )HandleManageArray[ DX_HANDLETYPE_SHADOWMAP ].Handle[ i ] ;
			if( ShadowMap == NULL ) continue ;

#ifndef DX_NON_ASYNCLOAD
			WaitASyncLoad( ShadowMap->HandleInfo.Handle ) ;
#endif

			Graphics_Hardware_ShadowMap_ReleaseTexture_PF( ShadowMap  ) ;
		}
	}

	if( HandleManageArray[ DX_HANDLETYPE_VERTEX_BUFFER ].InitializeFlag )
	{
		for( i = HandleManageArray[ DX_HANDLETYPE_VERTEX_BUFFER ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_VERTEX_BUFFER ].AreaMax ; i ++ )
		{
			VertexBuffer = ( VERTEXBUFFERHANDLEDATA * )HandleManageArray[ DX_HANDLETYPE_VERTEX_BUFFER ].Handle[ i ] ;
			if( VertexBuffer == NULL ) continue ;

#ifndef DX_NON_ASYNCLOAD
			WaitASyncLoad( VertexBuffer->HandleInfo.Handle ) ;
#endif

			Graphics_Hardware_VertexBuffer_Terminate_PF( VertexBuffer ) ;
		}
	}

	if( HandleManageArray[ DX_HANDLETYPE_INDEX_BUFFER ].InitializeFlag )
	{
		for( i = HandleManageArray[ DX_HANDLETYPE_INDEX_BUFFER ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_INDEX_BUFFER ].AreaMax ; i ++ )
		{
			IndexBuffer = ( INDEXBUFFERHANDLEDATA * )HandleManageArray[ DX_HANDLETYPE_INDEX_BUFFER ].Handle[ i ] ;
			if( IndexBuffer == NULL ) continue ;

#ifndef DX_NON_ASYNCLOAD
			WaitASyncLoad( IndexBuffer->HandleInfo.Handle ) ;
#endif

			Graphics_Hardware_IndexBuffer_Terminate_PF( IndexBuffer ) ;
		}
	}

	if( HandleManageArray[ DX_HANDLETYPE_SHADER ].InitializeFlag )
	{
		for( i = HandleManageArray[ DX_HANDLETYPE_SHADER ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_SHADER ].AreaMax ; i ++ )
		{
			Shader = ( SHADERHANDLEDATA * )HandleManageArray[ DX_HANDLETYPE_SHADER ].Handle[ i ] ;
			if( Shader == NULL ) continue ;

#ifndef DX_NON_ASYNCLOAD
			WaitASyncLoad( Shader->HandleInfo.Handle ) ;
#endif

			if( Shader->ShaderType == DX_SHADERTYPE_VERTEX )
			{
				Graphics_Android_VertexShaderArray_Release( &Shader->PF->Shader, 1 ) ;
			}
			else
			{
				Graphics_Android_FragmentShaderArray_Release( &Shader->PF->Shader, 1 ) ;
			}
		}
	}

	// �f�o�C�X�Z�b�g����������
	_MEMSET( GANDR.Device.State.SetTexture, 0, sizeof( GANDR.Device.State.SetTexture ) ) ;
	GANDR.Device.State.SetShader            = NULL ;
	GANDR.Device.State.SetShader_Force		= NULL ;
	_MEMSET( GANDR.Device.State.VertexAttrEnable, 0, sizeof( GANDR.Device.State.VertexAttrEnable ) ) ;
	GANDR.Device.State.SetVertexBuffer      = 0 ;
	GANDR.Device.State.TargetFrameBuffer    = 0 ;

	// �I��
	return 0 ;
}

// ���ׂĂ� OpenGL ES �n�I�u�W�F�N�g���쐬����
extern int Graphics_Android_CreateObjectAll( void )
{
	int                                       i ;
	SHADERHANDLEDATA                          *Shader ;
	VERTEXBUFFERHANDLEDATA                    *VertexBuffer ;
	INDEXBUFFERHANDLEDATA                     *IndexBuffer ;
	IMAGEDATA                                 *Image ;
	SHADOWMAPDATA                             *ShadowMap ;

	if( HandleManageArray[ DX_HANDLETYPE_GRAPH ].InitializeFlag && HandleManageArray[ DX_HANDLETYPE_GRAPH ].Num > 0 )
	{
		DXST_LOGFILE_ADDUTF16LE( "\xb0\x30\xe9\x30\xd5\x30\xa3\x30\xc3\x30\xaf\x30\xcf\x30\xf3\x30\xc9\x30\xeb\x30\x6e\x30\x20\x00\x4f\x00\x70\x00\x65\x00\x6e\x00\x47\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x8d\x51\x5c\x4f\x10\x62\x2e\x00\x2e\x00\x2e\x00\x2e\x00\x20\x00\x00"/*@ L"�O���t�B�b�N�n���h���� OpenGL ES �I�u�W�F�N�g�̍č쐬.... " @*/ ) ;

		for( i = HandleManageArray[ DX_HANDLETYPE_GRAPH ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_GRAPH ].AreaMax ; i ++ )
		{
			Image = ( IMAGEDATA * )HandleManageArray[ DX_HANDLETYPE_GRAPH ].Handle[ i ] ;

			if( Image == NULL ) continue ;
			if( Image->Orig == NULL ) continue ;
			if( Graphics_Hardware_CreateOrigTexture_PF( Image->Orig ) < 0 )
			{
				DXST_LOGFILEFMT_ADDUTF16LE(( "\xb0\x30\xe9\x30\xd5\x30\xa3\x30\xc3\x30\xaf\x30\xcf\x30\xf3\x30\xc9\x30\xeb\x30\x20\x00\x25\x00\x30\x00\x38\x00\x78\x00\x20\x00\x67\x30\x31\x59\x57\x65\x00\x30\xb5\x30\xa4\x30\xba\x30\x20\x00\x25\x00\x64\x00\x78\x00\x25\x00\x64\x00\x20\x00\x0a\x00\x00"/*@ L"�O���t�B�b�N�n���h�� %08x �Ŏ��s�@�T�C�Y %dx%d \n" @*/, Image->HandleInfo.Handle, Image->WidthI, Image->HeightI )) ;
			}
		}

		DXST_LOGFILE_ADDUTF16LE( "\x10\x62\x9f\x52\x0a\x00\x00"/*@ L"����\n" @*/ ) ;
	}

	if( HandleManageArray[ DX_HANDLETYPE_SHADOWMAP ].InitializeFlag && HandleManageArray[ DX_HANDLETYPE_SHADOWMAP ].Num > 0 )
	{
		DXST_LOGFILE_ADDUTF16LE( "\xb7\x30\xe3\x30\xc9\x30\xa6\x30\xde\x30\xc3\x30\xd7\x30\xcf\x30\xf3\x30\xc9\x30\xeb\x30\x6e\x30\x20\x00\x4f\x00\x70\x00\x65\x00\x6e\x00\x47\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x8d\x51\x5c\x4f\x10\x62\x2e\x00\x2e\x00\x2e\x00\x2e\x00\x20\x00\x00"/*@ L"�V���h�E�}�b�v�n���h���� OpenGL ES �I�u�W�F�N�g�̍č쐬.... " @*/ ) ;

		for( i = HandleManageArray[ DX_HANDLETYPE_SHADOWMAP ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_SHADOWMAP ].AreaMax ; i ++ )
		{
			ShadowMap = ( SHADOWMAPDATA * )HandleManageArray[ DX_HANDLETYPE_SHADOWMAP ].Handle[ i ] ;

			if( ShadowMap == NULL ) continue ;
			Graphics_Hardware_ShadowMap_CreateTexture_PF( ShadowMap ) ;
		}

		DXST_LOGFILE_ADDUTF16LE( "\x10\x62\x9f\x52\x0a\x00\x00"/*@ L"����\n" @*/ ) ;
	}

	if( HandleManageArray[ DX_HANDLETYPE_VERTEX_BUFFER ].InitializeFlag && HandleManageArray[ DX_HANDLETYPE_VERTEX_BUFFER ].Num > 0 )
	{
		DXST_LOGFILE_ADDUTF16LE( "\x02\x98\xb9\x70\xd0\x30\xc3\x30\xd5\x30\xa1\x30\xcf\x30\xf3\x30\xc9\x30\xeb\x30\x6e\x30\x20\x00\x4f\x00\x70\x00\x65\x00\x6e\x00\x47\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x8d\x51\x5c\x4f\x10\x62\x2e\x00\x2e\x00\x2e\x00\x2e\x00\x20\x00\x00"/*@ L"���_�o�b�t�@�n���h���� OpenGL ES �I�u�W�F�N�g�̍č쐬.... " @*/ ) ;

		for( i = HandleManageArray[ DX_HANDLETYPE_VERTEX_BUFFER ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_VERTEX_BUFFER ].AreaMax ; i ++ )
		{
			VertexBuffer = ( VERTEXBUFFERHANDLEDATA * )HandleManageArray[ DX_HANDLETYPE_VERTEX_BUFFER ].Handle[ i ] ;
			if( VertexBuffer == NULL ) continue ;
			Graphics_Hardware_VertexBuffer_Create_PF( VertexBuffer ) ;
		}

		DXST_LOGFILE_ADDUTF16LE( "\x10\x62\x9f\x52\x0a\x00\x00"/*@ L"����\n" @*/ ) ;
	}

	if( HandleManageArray[ DX_HANDLETYPE_INDEX_BUFFER ].InitializeFlag && HandleManageArray[ DX_HANDLETYPE_INDEX_BUFFER ].Num > 0 )
	{
		DXST_LOGFILE_ADDUTF16LE( "\xa4\x30\xf3\x30\xc7\x30\xc3\x30\xaf\x30\xb9\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\xcf\x30\xf3\x30\xc9\x30\xeb\x30\x6e\x30\x20\x00\x4f\x00\x70\x00\x65\x00\x6e\x00\x47\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x8d\x51\x5c\x4f\x10\x62\x2e\x00\x2e\x00\x2e\x00\x2e\x00\x20\x00\x00"/*@ L"�C���f�b�N�X�o�b�t�@�n���h���� OpenGL ES �I�u�W�F�N�g�̍č쐬.... " @*/ ) ;

		for( i = HandleManageArray[ DX_HANDLETYPE_INDEX_BUFFER ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_INDEX_BUFFER ].AreaMax ; i ++ )
		{
			IndexBuffer = ( INDEXBUFFERHANDLEDATA * )HandleManageArray[ DX_HANDLETYPE_INDEX_BUFFER ].Handle[ i ] ;
			if( IndexBuffer == NULL ) continue ;
			Graphics_Hardware_IndexBuffer_Create_PF( IndexBuffer ) ;
		}

		DXST_LOGFILE_ADDUTF16LE( "\x10\x62\x9f\x52\x0a\x00\x00"/*@ L"����\n" @*/ ) ;
	}

	if( HandleManageArray[ DX_HANDLETYPE_SHADER ].InitializeFlag && HandleManageArray[ DX_HANDLETYPE_SHADER ].Num > 0 )
	{
		DXST_LOGFILE_ADDUTF16LE( "\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xcf\x30\xf3\x30\xc9\x30\xeb\x30\x6e\x30\x20\x00\x4f\x00\x70\x00\x65\x00\x6e\x00\x47\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x8d\x51\x5c\x4f\x10\x62\x2e\x00\x2e\x00\x2e\x00\x2e\x00\x20\x00\x00"/*@ L"�V�F�[�_�[�n���h���� OpenGL ES �I�u�W�F�N�g�̍č쐬.... " @*/ ) ;

		for( i = HandleManageArray[ DX_HANDLETYPE_SHADER ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_SHADER ].AreaMax ; i ++ )
		{
			GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ShaderCodeInfo ;

			Shader = ( SHADERHANDLEDATA * )HandleManageArray[ DX_HANDLETYPE_SHADER ].Handle[ i ] ;
			if( Shader == NULL ) continue ;

			ShaderCodeInfo.Binary = Shader->FunctionCode ;
			ShaderCodeInfo.Size   = Shader->FunctionCodeSize ;
			if( Shader->ShaderType == DX_SHADERTYPE_VERTEX )
			{
				Graphics_Android_VertexShader_Create( &ShaderCodeInfo, &Shader->PF->Shader, 1 ) ;
			}
			else
			{
				Graphics_Android_FragmentShader_Create( &ShaderCodeInfo, &Shader->PF->Shader, 1 ) ;
			}
		}

		DXST_LOGFILE_ADDUTF16LE( "\x10\x62\x9f\x52\x0a\x00\x00"/*@ L"����\n" @*/ ) ;
	}

	// �I��
	return 0 ;
}



































// �V�F�[�_�[�R�[�h�֌W

// �V�F�[�_�[�R�[�h�p�b�P�[�W����V�F�[�_�[�R�[�h�o�C�i���̃A�h���X�ƃT�C�Y���擾����
static void Graphics_Android_ShaderCodePackage_GetInfo( WORD **pSize, BYTE **pCode, GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO *DestInfo, int Num )
{
	WORD *Size ;
	BYTE *Code ;
	int i ;

	Size = *pSize ;
	Code = *pCode ;
	for( i = 0 ; i < Num ; i ++, Size ++, DestInfo ++ )
	{
		if( *Size != 0 )
		{
			DestInfo->Binary = ( void * )Code ;
			DestInfo->Size   = *Size ;
			Code            += *Size ;
		}
	}

	*pSize = Size ;
	*pCode = Code ;
}

// Android �̕W���`��p�̃V�F�[�_�[�R�[�h�̏��������s��
extern int Graphics_Android_ShaderCode_Base_Initialize( void )
{
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_BASE *SCBASE = &GraphicsHardDataAndroid.ShaderCode.Base ;
	int   Size = 0 ;
	BYTE  *ShaderAddr = NULL ;
	WORD  *SizeBuf    = NULL ;

	// ���łɏ���������Ă����牽�����Ȃ�
	if( SCBASE->BaseShaderInitializeFlag == TRUE )
	{
		return TRUE ;
	}

	// ���C�g�C���f�b�N�X���X�g�̍\�z
	{
		int l0, l1, l2, l3, l4, l5, ind ;

		ind = 0 ;
		for( l0 = 0 ; l0 < 4 ; l0 ++ )
		{
			for( l1 = 0 ; l1 <= l0 ; l1 ++ )
			{
				for( l2 = 0 ; l2 <= l1 ; l2 ++ )
				{
					for( l3 = 0 ; l3 <= l2 ; l3 ++ )
					{
						for( l4 = 0 ; l4 <= l3 ; l4 ++ )
						{
							for( l5 = 0 ; l5 <= l4 ; l5 ++ )
							{
								SCBASE->LightIndexList84[ l0 ][ l1 ][ l2 ][ l3 ][ l4 ][ l5 ] = ( short )ind ;
								ind ++ ;
							}
						}
					}
				}
			}
		}

		ind = 0 ;
		for( l0 = 0 ; l0 < 4 ; l0 ++ )
		{
			for( l1 = 0 ; l1 <= l0 ; l1 ++ )
			{
				for( l2 = 0 ; l2 <= l1 ; l2 ++ )
				{
					SCBASE->LightIndexList20[ l0 ][ l1 ][ l2 ] = ( short )ind ;
					ind ++ ;
				}
			}
		}

		ind = 0 ;
		for( l0 = 0 ; l0 < 3 ; l0 ++ )
		{
			for( l1 = 0 ; l1 <= l0 ; l1 ++ )
			{
				for( l2 = 0 ; l2 <= l1 ; l2 ++ )
				{
					SCBASE->LightIndexList10[ l0 ][ l1 ][ l2 ] = ( short )ind ;
					ind ++ ;
				}
			}
		}
	}

#ifndef DX_NON_FILTER
	SCBASE->FilterShaderBinDxaImage = NULL ;
	SCBASE->RGBAMixS_ShaderPackImage = NULL ;
#endif // DX_NON_FILTER

	SCBASE->Base2DShaderPackageImage = NULL ;

	// �W���`��p�V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�����k�����f�[�^���𓀂���
	{
		Size = DXA_Decode( DxShaderCodeBin_Base_ANDR, NULL ) ;
		SCBASE->Base2DShaderPackageImage = DXALLOC( ( size_t )Size ) ;
		if( SCBASE->Base2DShaderPackageImage == NULL )
		{
			goto ERR ;
		}

		DXA_Decode( DxShaderCodeBin_Base_ANDR, SCBASE->Base2DShaderPackageImage ) ;
	}

	// �A�h���X���X�g�̃Z�b�g
	{
		DWORD HeadSize ;

		HeadSize = sizeof( WORD ) * (
				sizeof( SCBASE->BaseSimple_VS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->BaseNoneTex_FS_Code              ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->BaseUseTex_FS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->MaskEffect_VS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->MaskEffect_FS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->MaskEffect_ReverseEffect_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->MaskEffect_UseGraphHandle_FS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->MaskEffect_UseGraphHandle_ReverseEffect_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->StretchRect_VS_Code              ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->StretchRectTex2_VS_Code          ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->StretchRectTex8_VS_Code          ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->StretchRect_FS_Code              ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->ClearRT_VS_Code                  ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE->ClearRT_FS_Code                  ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		HeadSize = ( HeadSize + 15 ) / 16 * 16 ;

		SizeBuf    = ( WORD * )SCBASE->Base2DShaderPackageImage ;
		ShaderAddr = ( BYTE * )SCBASE->Base2DShaderPackageImage + HeadSize ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE->BaseSimple_VS_Code,                sizeof( SCBASE->BaseSimple_VS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE->BaseNoneTex_FS_Code,               sizeof( SCBASE->BaseNoneTex_FS_Code              ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE->BaseUseTex_FS_Code,                sizeof( SCBASE->BaseUseTex_FS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&SCBASE->MaskEffect_VS_Code,               sizeof( SCBASE->MaskEffect_VS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&SCBASE->MaskEffect_FS_Code,               sizeof( SCBASE->MaskEffect_FS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&SCBASE->MaskEffect_ReverseEffect_FS_Code, sizeof( SCBASE->MaskEffect_ReverseEffect_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE->MaskEffect_UseGraphHandle_FS_Code,               sizeof( SCBASE->MaskEffect_UseGraphHandle_FS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE->MaskEffect_UseGraphHandle_ReverseEffect_FS_Code, sizeof( SCBASE->MaskEffect_UseGraphHandle_ReverseEffect_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&SCBASE->StretchRect_VS_Code,              sizeof( SCBASE->StretchRect_VS_Code              ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&SCBASE->StretchRectTex2_VS_Code,          sizeof( SCBASE->StretchRectTex2_VS_Code          ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&SCBASE->StretchRectTex8_VS_Code,          sizeof( SCBASE->StretchRectTex8_VS_Code          ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&SCBASE->StretchRect_FS_Code,              sizeof( SCBASE->StretchRect_FS_Code              ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&SCBASE->ClearRT_VS_Code,                  sizeof( SCBASE->ClearRT_VS_Code                  ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&SCBASE->ClearRT_FS_Code,                  sizeof( SCBASE->ClearRT_FS_Code                  ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
	}

#ifndef DX_NON_FILTER

	// RGBAMix�V�F�[�_�[�p�b�N���k�t�@�C����W�J����
	{
		Size = DXA_Decode( DxShaderCodeBin_RgbaMix_ANDR, NULL ) ;
		SCBASE->RGBAMixS_ShaderPackImage = DXALLOC( ( size_t )Size ) ;
		if( SCBASE->RGBAMixS_ShaderPackImage == NULL )
		{
			goto ERR ;
		}

		DXA_Decode( DxShaderCodeBin_RgbaMix_ANDR, SCBASE->RGBAMixS_ShaderPackImage ) ;

		// �A�h���X���X�g�̃Z�b�g
		SizeBuf    = ( WORD  * )SCBASE->RGBAMixS_ShaderPackImage ;
		ShaderAddr = ( BYTE  * )SCBASE->RGBAMixS_ShaderPackImage +
			sizeof( WORD ) * (
				sizeof( SCBASE->RGBAMixS_FS_Code )  / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE->RGBAMixS_FS_Code,  sizeof( SCBASE->RGBAMixS_FS_Code )  / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
	}

	// �t�B���^�[�V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�����k�����f�[�^���𓀂���
	{
		Size = DXA_Decode( DxShaderCodeBin_Filter_ANDR, NULL ) ;
		SCBASE->FilterShaderBinDxaImage = DXALLOC( ( size_t )Size ) ;
		if( SCBASE->FilterShaderBinDxaImage == NULL )
		{
			goto ERR ;
		}

		DXA_Decode( DxShaderCodeBin_Filter_ANDR, SCBASE->FilterShaderBinDxaImage ) ;

		// �c�w�`�t�@�C�����I�[�v������
		DXA_Initialize( &SCBASE->FilterShaderBinDxa ) ;
		if( DXA_OpenArchiveFromMem( &SCBASE->FilterShaderBinDxa, SCBASE->FilterShaderBinDxaImage, Size, FALSE, FALSE ) != 0 )
		{
			goto ERR ;
		}
	}

#endif // DX_NON_FILTER

	SCBASE->BaseShaderInitializeFlag = TRUE ;

	// ����I��
	return TRUE ;

ERR :
	if( SCBASE->Base2DShaderPackageImage != NULL )
	{
		DXFREE( SCBASE->Base2DShaderPackageImage ) ;
		SCBASE->Base2DShaderPackageImage = NULL ;
	}

#ifndef DX_NON_FILTER
	if( SCBASE->FilterShaderBinDxaImage != NULL )
	{
		DXFREE( SCBASE->FilterShaderBinDxaImage ) ;
		SCBASE->FilterShaderBinDxaImage = NULL ;
	}

	if( SCBASE->RGBAMixS_ShaderPackImage != NULL )
	{
		DXFREE( SCBASE->RGBAMixS_ShaderPackImage ) ;
		SCBASE->RGBAMixS_ShaderPackImage = NULL ;
	}
#endif // DX_NON_FILTER

	return FALSE ;
}

// Android �̕W���`��p�̃V�F�[�_�[�R�[�h�̌�n�����s��
extern int Graphics_Android_ShaderCode_Base_Terminate( void )
{
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_BASE *SCBASE = &GraphicsHardDataAndroid.ShaderCode.Base ;

	// ���łɌ�n������Ă����牽�����Ȃ�
	if( SCBASE->BaseShaderInitializeFlag == FALSE )
	{
		return TRUE ;
	}

	// �𓀂����V�F�[�_�[���i�[���Ă����������̉��
	if( SCBASE->Base2DShaderPackageImage != NULL )
	{
		DXFREE( SCBASE->Base2DShaderPackageImage ) ;
		SCBASE->Base2DShaderPackageImage = NULL ;
	}

#ifndef DX_NON_FILTER

	// �t�B���^�[�V�F�[�_�[�p�c�w�`�̌�n��
	DXA_Terminate( &SCBASE->FilterShaderBinDxa ) ;

	if( SCBASE->RGBAMixS_ShaderPackImage )
	{
		DXFREE( SCBASE->RGBAMixS_ShaderPackImage ) ;
		SCBASE->RGBAMixS_ShaderPackImage = NULL ;
	}
	if( SCBASE->FilterShaderBinDxaImage )
	{
		DXFREE( SCBASE->FilterShaderBinDxaImage ) ;
		SCBASE->FilterShaderBinDxaImage = NULL ;
	}

#endif // DX_NON_FILTER

	// �������t���O��|��
	SCBASE->BaseShaderInitializeFlag = FALSE ;

	// ����I��
	return TRUE ;
}

// Android �̕W���R�c�`��p�̃V�F�[�_�[�R�[�h�̏��������s��
extern int Graphics_Android_ShaderCode_Base3D_Initialize( void )
{
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_BASE3D *SCBASE3D = &GraphicsHardDataAndroid.ShaderCode.Base3D ;
	HANDLEMANAGE *HandleManage = &HandleManageArray[ DX_HANDLETYPE_GRAPH ] ;
	int   Size = 0 ;
	BYTE  *ShaderAddr = NULL ;
	WORD  *SizeBuf    = NULL ;

	// ���łɏ���������Ă����牽�����Ȃ�
	if( SCBASE3D->Base3DShaderInitializeFlag == TRUE )
	{
		return TRUE ;
	}

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &HandleManage->CriticalSection ) ;

	// �N���e�B�J���Z�N�V�������擾������ŉ��߂ď������m�F
	if( SCBASE3D->Base3DShaderInitializeFlag == TRUE )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &HandleManage->CriticalSection ) ;

		return TRUE ;
	}

	SCBASE3D->Base3DShaderPackageImage = NULL ;

	// ���k�f�[�^�̉�
	{
		Size = DXA_Decode( DxShaderCodeBin_Base3D_ANDR, NULL ) ;
		SCBASE3D->Base3DShaderPackageImage = DXCALLOC( ( size_t )Size ) ;
		if( SCBASE3D->Base3DShaderPackageImage == NULL )
		{
			goto ERR ;
		}

		DXA_Decode( DxShaderCodeBin_Base3D_ANDR, SCBASE3D->Base3DShaderPackageImage ) ;
	}

	// �A�h���X���X�g�̃Z�b�g
	{
		DWORD HeadSize ;

		HeadSize = sizeof( WORD ) * (
				sizeof( SCBASE3D->Base3D_PixelLighting_VS_Code         ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE3D->Base3D_PixelLighting_Normal_FS_Code  ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE3D->Base3D_ShadowMap_VS_Code             ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE3D->Base3D_NoLighting_VS_Code            ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE3D->Base3D_VertexLighting_VS_Code        ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE3D->Base3D_ShadowMap_Normal_FS_Code      ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE3D->Base3D_NoLighting_Normal_FS_Code     ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
				sizeof( SCBASE3D->Base3D_VertexLighting_Normal_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		HeadSize = ( HeadSize + 15 ) / 16 * 16 ;

		SizeBuf    = ( WORD * )SCBASE3D->Base3DShaderPackageImage ;
		ShaderAddr = ( BYTE * )SCBASE3D->Base3DShaderPackageImage + HeadSize ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE3D->Base3D_PixelLighting_VS_Code,         sizeof( SCBASE3D->Base3D_PixelLighting_VS_Code         ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE3D->Base3D_PixelLighting_Normal_FS_Code,  sizeof( SCBASE3D->Base3D_PixelLighting_Normal_FS_Code  ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE3D->Base3D_ShadowMap_VS_Code,             sizeof( SCBASE3D->Base3D_ShadowMap_VS_Code             ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE3D->Base3D_NoLighting_VS_Code,            sizeof( SCBASE3D->Base3D_NoLighting_VS_Code            ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE3D->Base3D_VertexLighting_VS_Code,        sizeof( SCBASE3D->Base3D_VertexLighting_VS_Code        ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE3D->Base3D_ShadowMap_Normal_FS_Code,      sizeof( SCBASE3D->Base3D_ShadowMap_Normal_FS_Code      ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE3D->Base3D_NoLighting_Normal_FS_Code,     sizeof( SCBASE3D->Base3D_NoLighting_Normal_FS_Code     ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCBASE3D->Base3D_VertexLighting_Normal_FS_Code, sizeof( SCBASE3D->Base3D_VertexLighting_Normal_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
	}

	SCBASE3D->Base3DShaderInitializeFlag = TRUE ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &HandleManage->CriticalSection ) ;

	// ����I��
	return TRUE ;

ERR :
	if( SCBASE3D->Base3DShaderPackageImage != NULL )
	{
		DXFREE( SCBASE3D->Base3DShaderPackageImage ) ;
		SCBASE3D->Base3DShaderPackageImage = NULL ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &HandleManage->CriticalSection ) ;

	return FALSE ;
}


// Android �̕W���R�c�`��p�̃V�F�[�_�[�R�[�h�̌�n�����s��
extern int Graphics_Android_ShaderCode_Base3D_Terminate( void )
{
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_BASE3D *SCBASE3D = &GraphicsHardDataAndroid.ShaderCode.Base3D ;

	// ���łɌ�n������Ă����牽�����Ȃ�
	if( SCBASE3D->Base3DShaderInitializeFlag == FALSE )
	{
		return TRUE ;
	}

	if( SCBASE3D->Base3DShaderPackageImage )
	{
		DXFREE( SCBASE3D->Base3DShaderPackageImage ) ;
		SCBASE3D->Base3DShaderPackageImage = NULL ;
	}

	// �������t���O��|��
	SCBASE3D->Base3DShaderInitializeFlag = FALSE ;

	// ����I��
	return TRUE ;
}


#ifndef DX_NON_MODEL

// Android �̃��f���`��p�̃V�F�[�_�[�R�[�h�̏��������s��
extern	int		Graphics_Android_ShaderCode_Model_Initialize( void )
{
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_MODEL *SCMODEL = &GraphicsHardDataAndroid.ShaderCode.Model ;
	HANDLEMANAGE *HandleManage = &HandleManageArray[ DX_HANDLETYPE_GRAPH ] ;
	int   Size = 0 ;
	BYTE  *ShaderAddr = NULL ;
	WORD  *SizeBuf    = NULL ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &HandleManage->CriticalSection ) ;

	// ���łɏ���������Ă����牽�����Ȃ�
	if( SCMODEL->ModelShaderInitializeFlag == TRUE )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &HandleManage->CriticalSection ) ;

		return TRUE ;
	}

	SCMODEL->ModelShaderPackImage = NULL ;

	// ���k�f�[�^�̉�
	{
		Size = DXA_Decode( DxShaderCodeBin_Model_ANDR, NULL ) ;
		SCMODEL->ModelShaderPackImage = DXCALLOC( ( size_t )Size ) ;
		if( SCMODEL->ModelShaderPackImage == NULL )
		{
			goto ERR ;
		}

		DXA_Decode( DxShaderCodeBin_Model_ANDR, SCMODEL->ModelShaderPackImage ) ;
	}

	// �A�h���X���X�g�̃Z�b�g
	{
		DWORD HeadSize ;

		HeadSize = sizeof( WORD ) * (
			sizeof( SCMODEL->MV1_PixelLighting_VS_Code            ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_PixelLighting_ToonType1_FS_Code  ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_PixelLighting_ToonType2_FS_Code  ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_PixelLighting_Normal_FS_Code     ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_MaterialType_FS_Code             ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_ToonOutLine_ShadowMap_VS_Code    ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_ToonOutLine_VS_Code              ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_ShadowMap_VS_Code                ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_NoLighting_VS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_VertexLighting_VS_Code           ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_ShadowMap_Toon_FS_Code           ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_ShadowMap_Normal_FS_Code         ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_NoLighting_Toon_FS_Code          ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_NoLighting_Normal_FS_Code        ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_VertexLighting_ToonType1_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_VertexLighting_ToonType2_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) +
			sizeof( SCMODEL->MV1_VertexLighting_Normal_FS_Code    ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		HeadSize = ( HeadSize + 15 ) / 16 * 16 ;

		SizeBuf    = ( WORD * )SCMODEL->ModelShaderPackImage ;
		ShaderAddr = ( BYTE * )SCMODEL->ModelShaderPackImage + HeadSize ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_PixelLighting_VS_Code,            sizeof( SCMODEL->MV1_PixelLighting_VS_Code            ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_PixelLighting_ToonType1_FS_Code,  sizeof( SCMODEL->MV1_PixelLighting_ToonType1_FS_Code  ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_PixelLighting_ToonType2_FS_Code,  sizeof( SCMODEL->MV1_PixelLighting_ToonType2_FS_Code  ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_PixelLighting_Normal_FS_Code,     sizeof( SCMODEL->MV1_PixelLighting_Normal_FS_Code     ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_MaterialType_FS_Code,             sizeof( SCMODEL->MV1_MaterialType_FS_Code             ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_ToonOutLine_ShadowMap_VS_Code,    sizeof( SCMODEL->MV1_ToonOutLine_ShadowMap_VS_Code    ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_ToonOutLine_VS_Code,              sizeof( SCMODEL->MV1_ToonOutLine_VS_Code              ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_ShadowMap_VS_Code,                sizeof( SCMODEL->MV1_ShadowMap_VS_Code                ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_NoLighting_VS_Code,               sizeof( SCMODEL->MV1_NoLighting_VS_Code               ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_VertexLighting_VS_Code,           sizeof( SCMODEL->MV1_VertexLighting_VS_Code           ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_ShadowMap_Toon_FS_Code,           sizeof( SCMODEL->MV1_ShadowMap_Toon_FS_Code           ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_ShadowMap_Normal_FS_Code,         sizeof( SCMODEL->MV1_ShadowMap_Normal_FS_Code         ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_NoLighting_Toon_FS_Code,          sizeof( SCMODEL->MV1_NoLighting_Toon_FS_Code          ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_NoLighting_Normal_FS_Code,        sizeof( SCMODEL->MV1_NoLighting_Normal_FS_Code        ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_VertexLighting_ToonType1_FS_Code, sizeof( SCMODEL->MV1_VertexLighting_ToonType1_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_VertexLighting_ToonType2_FS_Code, sizeof( SCMODEL->MV1_VertexLighting_ToonType2_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		Graphics_Android_ShaderCodePackage_GetInfo( &SizeBuf, &ShaderAddr, ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )SCMODEL->MV1_VertexLighting_Normal_FS_Code,    sizeof( SCMODEL->MV1_VertexLighting_Normal_FS_Code    ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
	}

	SCMODEL->ModelShaderInitializeFlag = TRUE ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &HandleManage->CriticalSection ) ;

	// ����I��
	return TRUE ;

ERR :
	if( SCMODEL->ModelShaderPackImage != NULL )
	{
		DXFREE( SCMODEL->ModelShaderPackImage ) ;
		SCMODEL->ModelShaderPackImage = NULL ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &HandleManage->CriticalSection ) ;

	return FALSE ;
}

// Android �̃��f���`��p�̃V�F�[�_�[�R�[�h�̌�n�����s��
extern	int		Graphics_Android_ShaderCode_Model_Terminate( void )
{
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_MODEL *SCMODEL = &GraphicsHardDataAndroid.ShaderCode.Model ;

	// ���łɌ�n������Ă����牽�����Ȃ�
	if( SCMODEL->ModelShaderInitializeFlag == FALSE )
	{
		return TRUE ;
	}

	if( SCMODEL->ModelShaderPackImage )
	{
		DXFREE( SCMODEL->ModelShaderPackImage ) ;
		SCMODEL->ModelShaderPackImage = NULL ;
	}

	// �������t���O��|��
	SCMODEL->ModelShaderInitializeFlag = FALSE ;

	// ����I��
	return TRUE ;
}

#endif // DX_NON_MODEL



// �V�����V�F�[�_�[�\���̂��擾����
extern GRAPHICS_ANDROID_SHADER *Graphics_Android_GetShaderStruct( void )
{
	GRAPHICS_ANDROID_SHADER_LIST *UseList ;

	if( GraphicsHardDataAndroid.Device.Shader.ShadersListFirst == NULL &&
		GraphicsHardDataAndroid.Device.Shader.ShadersListLast  == NULL )
	{
		GraphicsHardDataAndroid.Device.Shader.ShadersListFirst = ( GRAPHICS_ANDROID_SHADER_LIST * )DXALLOC( sizeof( GRAPHICS_ANDROID_SHADER_LIST ) ) ;
		if( GraphicsHardDataAndroid.Device.Shader.ShadersListFirst == NULL )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xc5\x60\x31\x58\xea\x30\xb9\x30\xc8\x30\x3c\x68\x0d\x7d\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�V�F�[�_�[��񃊃X�g�i�[�p�̃������̊m�ۂɎ��s���܂���\n" @*/ )) ;
			return NULL ;
		}
		_MEMSET( GraphicsHardDataAndroid.Device.Shader.ShadersListFirst, 0, sizeof( GRAPHICS_ANDROID_SHADER_LIST ) ) ;
		GraphicsHardDataAndroid.Device.Shader.ShadersListLast = GraphicsHardDataAndroid.Device.Shader.ShadersListFirst ;

		UseList = GraphicsHardDataAndroid.Device.Shader.ShadersListFirst ;
	}
	else
	{
		UseList = GraphicsHardDataAndroid.Device.Shader.ShadersListLast ;
	}

	if( UseList->UseNum >= SHADERS_LIST_DATA_NUM )
	{
		GRAPHICS_ANDROID_SHADER_LIST *NewList ;

		NewList = ( GRAPHICS_ANDROID_SHADER_LIST * )DXALLOC( sizeof( GRAPHICS_ANDROID_SHADER_LIST ) ) ;
		if( NewList == NULL )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xfd\x8f\xa0\x52\x6e\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xc5\x60\x31\x58\xea\x30\xb9\x30\xc8\x30\x3c\x68\x0d\x7d\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�ǉ��̃V�F�[�_�[��񃊃X�g�i�[�p�̃������̊m�ۂɎ��s���܂���\n" @*/ )) ;
			return NULL ;
		}
		_MEMSET( NewList, 0, sizeof( GRAPHICS_ANDROID_SHADER_LIST ) ) ;
		UseList->Next = NewList ;
		UseList = NewList ;

		GraphicsHardDataAndroid.Device.Shader.ShadersListLast = NewList ;
	}

	UseList->UseNum ++ ;
	return &UseList->Shaders[ UseList->UseNum - 1 ] ;
}

// �V�F�[�_�[��񃊃X�g�̌�n�����s��
extern int Graphics_Android_ShaderList_Terminate( void )
{
	GRAPHICS_ANDROID_SHADER_LIST *UseList ;

	if( GraphicsHardDataAndroid.Device.Shader.ShadersListFirst == NULL &&
		GraphicsHardDataAndroid.Device.Shader.ShadersListLast  == NULL )
	{
		return 0 ;
	}

	UseList = GraphicsHardDataAndroid.Device.Shader.ShadersListFirst ;
	while( UseList != NULL )
	{
		GRAPHICS_ANDROID_SHADER_LIST *Prev ;

		Graphics_Android_ShaderArray_Release( UseList->Shaders, UseList->UseNum ) ;

		Prev = UseList ;
		UseList = UseList->Next ;
		DXFREE( Prev ) ;
		Prev = NULL ;
	}

	GraphicsHardDataAndroid.Device.Shader.ShadersListFirst = NULL ;
	GraphicsHardDataAndroid.Device.Shader.ShadersListLast  = NULL ;

	return 0 ;
}

// �V�F�[�_�[�R�[�h���璸�_�V�F�[�_�[���쐬����
extern int Graphics_Android_VertexShader_Create( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO *Code, GLuint *pDestShader, int Num )
{
	int i ;

	for( i = 0; i < Num; i++, Code++, pDestShader++ )
	{
		GLuint shader ;

		shader = glCreateShader( GL_VERTEX_SHADER );
		glShaderSource( shader, 1, ( const GLchar ** )&Code->Binary, ( const GLint * )&Code->Size ); 
		glCompileShader( shader );

		GLint compiled;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );

		if( !compiled )
		{
			// �R���p�C���G���[�̕�����̒������擾
			GLint logLen;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );

			// �R���p�C���G���[��������擾
			GLchar *log = ( GLchar * )DXALLOC( sizeof( GLchar ) * ( logLen + 1 ) );
			if( log != NULL )
			{
				glGetShaderInfoLog( shader, logLen, 0, log ) ;
				DXST_LOGFILE_ADDA( log ) ;
				DXST_LOGFILE_ADDA( "\n" ) ;
				DXFREE( log ) ;
				log = NULL ;
				return -1 + i ;
			}
		}

		*pDestShader = shader ;
	}

	return 0 ;
}

// �V�F�[�_�[�R�[�h����t���O�����g�V�F�[�_�[���쐬����
extern int Graphics_Android_FragmentShader_Create( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO *Code, GLuint *pDestShader, int Num )
{
	int i ;

	for( i = 0; i < Num; i++, Code++, pDestShader++ )
	{
		GLuint shader;

		shader = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource( shader, 1, ( const GLchar ** )&Code->Binary, ( const GLint * )&Code->Size ); 
		glCompileShader( shader );

		GLint compiled;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );

		if( !compiled )
		{
			// �R���p�C���G���[�̕�����̒������擾
			GLint logLen;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );

			// �R���p�C���G���[��������擾
			GLchar *log = ( GLchar * )DXALLOC( sizeof( GLchar ) * ( logLen + 1 ) );
			if( log != NULL )
			{
				glGetShaderInfoLog( shader, logLen, 0, log );
				DXST_LOGFILE_ADDA( log ) ;
				DXST_LOGFILE_ADDA( "\n" ) ;
				DXFREE( log ) ;
				log = NULL ;
				return -1 + i ;
			}
		}

		*pDestShader = shader ;
	}

	return 0 ;
}

// �V�F�[�_�[�� Uniform �ԍ����擾����
extern GLuint Graphics_Android_Shader_GetUniformIndex( GRAPHICS_ANDROID_SHADER *ShaderInfo, const GLchar *UniformName )
{
	GLuint lResult ;

	lResult = glGetUniformLocation( ShaderInfo->Shader, UniformName ) ;
	if( lResult == 0xffffffff )
	{
		char lTempStr[ 128 ] ;

		CL_strcpy_s( DX_CHARCODEFORMAT_ASCII, lTempStr, sizeof( lTempStr ), UniformName ) ;
		CL_strcat_s( DX_CHARCODEFORMAT_ASCII, lTempStr, sizeof( lTempStr ), "[0]" ) ;
		lResult = glGetUniformLocation( ShaderInfo->Shader, lTempStr ) ;
	}

	return lResult ;
}

// ���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[����V�F�[�_�[�����Z�b�g�A�b�v����
extern int Graphics_Android_Shader_Create( GRAPHICS_ANDROID_SHADER *ShaderInfo, GLuint VertexShader, GLuint FragmentShader )
{
	int i ;

	ShaderInfo->Shader = glCreateProgram() ;

    glAttachShader( ShaderInfo->Shader, VertexShader );
    glAttachShader( ShaderInfo->Shader, FragmentShader );

    glLinkProgram( ShaderInfo->Shader );

	for( i = 0 ; i < ANDROID_VERTEX_ATTR_NUM ; i ++ )
	{
		ShaderInfo->AttributeIndex[ i ] = glGetAttribLocation( ShaderInfo->Shader, g_VertexElementInfoBase[ i ].AttrName ) ;
	}

	for( i = 0 ; i < ANDROID_SHADER_UNIFORM_NUM ; i ++ )
	{
		ShaderInfo->UniformIndex[ i ] = Graphics_Android_Shader_GetUniformIndex( ShaderInfo, g_UniformName[ i ] ) ;
	}

	return 0 ;
}

// ���_�V�F�[�_�[�z����������
extern void Graphics_Android_VertexShaderArray_Release( GLuint *pObject, int Num )
{
	int i ;

	for( i = 0 ; i < Num ; i++, pObject++ )
	{
		if( *pObject != 0xffffffff && *pObject != 0 )
		{
			glDeleteShader( *pObject ) ;
			*pObject = 0 ;
		}
	}
}

// �t���O�����g�V�F�[�_�[�z����������
extern void Graphics_Android_FragmentShaderArray_Release( GLuint *pObject, int Num )
{
	int i ;

	for( i = 0 ; i < Num ; i++, pObject++ )
	{
		if( *pObject != 0xffffffff && *pObject != 0 )
		{
			glDeleteShader( *pObject ) ;
			*pObject = 0 ;
		}
	}
}

// �V�F�[�_�[�z����������
extern void Graphics_Android_ShaderArray_Release( GRAPHICS_ANDROID_SHADER *pShaderInfo, int Num )
{
	int i ;

	for( i = 0 ; i < Num ; i++, pShaderInfo++ )
	{
		if( pShaderInfo->Shader != 0xffffffff && pShaderInfo->Shader != 0 )
		{
			glDeleteProgram( pShaderInfo->Shader ) ;
			pShaderInfo->Shader = 0 ;
		}
	}
}

// Android �̃V�F�[�_�[�̏��������s��
extern int Graphics_Android_Shader_Initialize( void )
{
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE      *ShaderCode = &GraphicsHardDataAndroid.ShaderCode ;
	GRAPHICS_HARDWARE_ANDROID_SHADER          *Shader     = &GraphicsHardDataAndroid.Device.Shader ;
	int Result ;
	static GLuint MaskEffect_VS ;
	static GLuint MaskEffect_FS ;
	static GLuint MaskEffect_ReverseEffect_FS ;
	static GLuint MaskEffect_UseGraphHandle_FS[ 4 ] ;
	static GLuint MaskEffect_UseGraphHandle_ReverseEffect_FS[ 4 ] ;
	static GLuint StretchRect_FS ;
	static GLuint ClearRT_VS ;
	static GLuint ClearRT_FS ;
	int i ;
//	int j ;
//	int k ;
//	int l ;
//	int m ;
//	int n ;
	int FunctionResult = -1 ;

	// ���ɍ쐬����Ă����Ƃ��̂��߂ɍ폜�������s��
	//TerminateAndroidShader() ;
	Graphics_Android_Shader_Terminate() ;

//	return 0 ;

	DXST_LOGFILE_ADDUTF16LE( "\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\xa2\x95\xc2\x4f\x6e\x30\x1d\x52\x1f\x67\x16\x53\x2e\x00\x2e\x00\x2e\x00\x2e\x00\x20\x00\x00"/*@ L"�V�F�[�_�[�R�[�h�֌W�̏�����.... " @*/ ) ;

	// Android �̏ꍇ�̓V�F�[�_�[�͕K���g�p�ł���
	GSYS.HardInfo.UseShader = TRUE ;

	// �W���`��p�V�F�[�_�[�R�[�h���W�J����Ă��Ȃ��ꍇ�͓W�J
	if( Graphics_Android_ShaderCode_Base_Initialize() == FALSE )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xb3\x30\xfc\x30\xc9\x30\x92\x30\x55\x5c\x8b\x95\x59\x30\x8b\x30\xe1\x30\xe2\x30\xea\x30\x18\x98\xdf\x57\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�V�F�[�_�[�R�[�h��W�J���郁�����̈�̊m�ۂɎ��s���܂���\n" @*/ )) ;
		GSYS.HardInfo.UseShader = FALSE ;
		goto END ;
	}

	// ��{�I�ȕ`�揈���Ɏg�p����V�F�[�_�[���쐬����
	{
//		// �W���`��p�̕��G�ȏ������s��Ȃ����_�V�F�[�_�[�̍쐬
//		Result = Graphics_Android_VertexShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )ShaderCode->Base.BaseSimple_VS_Code, Shader->Base.BaseSimple_VS, sizeof( ShaderCode->Base.BaseSimple_VS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
//		if( Result < 0 )
//		{
//			DXST_LOGFILEFMT_ADDUTF16LE(( "\x19\x6a\x96\x6e\xcf\x63\x3b\x75\x28\x75\x6e\x30\x07\x89\xd1\x96\x6a\x30\xe6\x51\x06\x74\x92\x30\x4c\x88\x8f\x30\x6a\x30\x44\x30\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�W���`��p�̕��G�ȏ������s��Ȃ����_�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
//			GSYS.HardInfo.UseShader = FALSE ;
//			goto END ;
//		}
//
//		// �Œ�@�\�p�C�v���C���݊��̃t���O�����g�V�F�[�_�[( �e�N�X�`���Ȃ� )�̍쐬
//		Result = Graphics_Android_FragmentShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )ShaderCode->Base.BaseNoneTex_FS_Code, &Shader->Base.BaseNoneTex_FS[ 0 ][ 0 ], sizeof( ShaderCode->Base.BaseNoneTex_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
//		if( Result < 0 )
//		{
//			DXST_LOGFILEFMT_ADDUTF16LE(( "\xfa\x56\x9a\x5b\x5f\x6a\xfd\x80\xd1\x30\xa4\x30\xd7\x30\xe9\x30\xa4\x30\xf3\x30\x92\x4e\xdb\x63\x6e\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x28\x00\x20\x00\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\x6a\x30\x57\x30\x20\x00\x29\x00\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�Œ�@�\�p�C�v���C���݊��̃t���O�����g�V�F�[�_�[�I�u�W�F�N�g( �e�N�X�`���Ȃ� ) No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
//			GSYS.HardInfo.UseShader = FALSE ;
//			goto END ;
//		}
//
//		// �Œ�@�\�p�C�v���C���݊��̃V�F�[�_�[( �e�N�X�`���Ȃ� )�̍쐬
//		// ( �����ł͎g�p�p�x�̍����V�F�[�_�[�̂ݍ쐬 )
//		for( i = 0 ; i < ANDROID_VERTEX_INPUTLAYOUT_NUM ; i ++ )
//		{
//			if( i != ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D &&
//				i != ANDROID_VERTEX_INPUTLAYOUT_NOTEX_3D )
//			{
//				continue ;
//			}
//
//			for( j = 0 ; j < ANDROID_RENDER_TYPE_NUM ; j ++ )
//			{
//				if( j != ANDROID_RENDER_TYPE_NORMAL &&
//					j != ANDROID_RENDER_TYPE_PMA_NORMAL )
//				{
//					continue ;
//				}
//
//				for( k = 0 ; k < ANDROID_FS_ALPHATEST_NUM ; k ++ )
//				{
//					Shader->Base.BaseNoneTex_Shader[ i ][ j ][ k ] = Graphics_Android_GetShaderStruct() ;
//					if( Shader->Base.BaseNoneTex_Shader[ i ][ j ][ k ] == NULL )
//					{
//						GSYS.HardInfo.UseShader = FALSE ;
//						goto END ;
//					}
//					Result = Graphics_Android_Shader_Create( Shader->Base.BaseNoneTex_Shader[ i ][ j ][ k ], Shader->Base.BaseSimple_VS[ i ], Shader->Base.BaseNoneTex_FS[ j ][ k ] ) ;
//					if( Result < 0 )
//					{
//						DXST_LOGFILEFMT_ADDUTF16LE(( "\xfa\x56\x9a\x5b\x5f\x6a\xfd\x80\xd1\x30\xa4\x30\xd7\x30\xe9\x30\xa4\x30\xf3\x30\x92\x4e\xdb\x63\x6e\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x28\x00\x20\x00\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\x6a\x30\x57\x30\x20\x00\x29\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�Œ�@�\�p�C�v���C���݊��̃V�F�[�_�[�I�u�W�F�N�g( �e�N�X�`���Ȃ� )�̍쐬�Ɏ��s���܂���\n" @*/ ) ) ;
//						GSYS.HardInfo.UseShader = FALSE ;
//						goto END ;
//					}
//				}
//			}
//		}

		// �Œ�@�\�p�C�v���C���݊��̃V�F�[�_�[( �e�N�X�`������ )�̍쐬
		// ( �����ł͎g�p�p�x�̍����V�F�[�_�[�̂ݍ쐬 )
//		for( i = 0 ; i < ANDROID_VERTEX_INPUTLAYOUT_NUM ; i ++ )
//		{
//			if( i != ANDROID_VERTEX_INPUTLAYOUT_2D &&
//				i != ANDROID_VERTEX_INPUTLAYOUT_3D &&
//				i != ANDROID_VERTEX_INPUTLAYOUT_3D_LIGHT )
//			{
//				continue ;
//			}
//
//			for( j = 0 ; j < 4 ; j ++ )
//			{
//				if( j != 0 )
//				{
//					continue ;
//				}
//
//				for( k = 0 ; k < ANDROID_RENDER_TYPE_NUM ; k ++ )
//				{
//					if( k != ANDROID_RENDER_TYPE_NORMAL &&
//						k != ANDROID_RENDER_TYPE_PMA_NORMAL )
//					{
//						continue ;
//					}
//
//					for( l = 0 ; l < 2 ; l ++ )
//					{
//						if( l != 0 )
//						{
//							continue ;
//						}
//
//						for( m = 0 ; m < 2 ; m ++ )
//						{
//							for( n = 0 ; n < ANDROID_FS_ALPHATEST_NUM ; n ++ )
//							{
//								Result = Graphics_Android_FragmentShader_Create( &ShaderCode->Base.BaseUseTex_FS_Code[ j ][ k ][ l ][ m ][ n ], &Shader->Base.BaseUseTex_FS[ j ][ k ][ l ][ m ][ n ], 1 ) ;
//								if( Result < 0 )
//								{
//									DXST_LOGFILEFMT_ADDUTF16LE(( "\xfa\x56\x9a\x5b\x5f\x6a\xfd\x80\xd1\x30\xa4\x30\xd7\x30\xe9\x30\xa4\x30\xf3\x30\x92\x4e\xdb\x63\x6e\x30\xd5\x30\xe9\x30\xb0\x30\xe1\x30\xf3\x30\xc8\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x28\x00\x20\x00\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\x42\x30\x8a\x30\x20\x00\x29\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�Œ�@�\�p�C�v���C���݊��̃t���O�����g�V�F�[�_�[�I�u�W�F�N�g( �e�N�X�`������ ) �̍쐬�Ɏ��s���܂���\n" @*/ )) ;
//									GSYS.HardInfo.UseShader = FALSE ;
//									goto END ;
//								}
//
//								Shader->Base.BaseUseTex_Shader[ i ][ j ][ k ][ l ][ m ][ n ] = Graphics_Android_GetShaderStruct() ;
//								if( Shader->Base.BaseUseTex_Shader[ i ][ j ][ k ][ l ][ m ][ n ] == NULL )
//								{
//									GSYS.HardInfo.UseShader = FALSE ;
//									goto END ;
//								}
//								Result = Graphics_Android_Shader_Create( Shader->Base.BaseUseTex_Shader[ i ][ j ][ k ][ l ][ m ][ n ], Shader->Base.BaseSimple_VS[ i ], Shader->Base.BaseUseTex_FS[ j ][ k ][ l ][ m ][ n ] ) ;
//								if( Result < 0 )
//								{
//									DXST_LOGFILEFMT_ADDUTF16LE(( "\xfa\x56\x9a\x5b\x5f\x6a\xfd\x80\xd1\x30\xa4\x30\xd7\x30\xe9\x30\xa4\x30\xf3\x30\x92\x4e\xdb\x63\x6e\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x28\x00\x20\x00\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\x42\x30\x8a\x30\x20\x00\x29\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�Œ�@�\�p�C�v���C���݊��̃V�F�[�_�[�I�u�W�F�N�g( �e�N�X�`������ )�̍쐬�Ɏ��s���܂���\n" @*/ ) ) ;
//									GSYS.HardInfo.UseShader = FALSE ;
//									goto END ;
//								}
//							}
//						}
//					}
//				}
//			}
//		}

		// �}�X�N�����p���_�V�F�[�_�[�̍쐬
		Result = Graphics_Android_VertexShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&ShaderCode->Base.MaskEffect_VS_Code, &MaskEffect_VS, sizeof( ShaderCode->Base.MaskEffect_VS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xde\x30\xb9\x30\xaf\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�}�X�N�����p�̒��_�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}

		// �}�X�N�����p�t���O�����g�V�F�[�_�[�̍쐬
		Result = Graphics_Android_FragmentShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&ShaderCode->Base.MaskEffect_FS_Code, &MaskEffect_FS, sizeof( ShaderCode->Base.MaskEffect_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xde\x30\xb9\x30\xaf\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�}�X�N�����p�̃t���O�����g�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}
		Result = Graphics_Android_FragmentShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&ShaderCode->Base.MaskEffect_ReverseEffect_FS_Code, &MaskEffect_ReverseEffect_FS, sizeof( ShaderCode->Base.MaskEffect_ReverseEffect_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xcd\x53\xe2\x8e\xb9\x52\x9c\x67\xde\x30\xb9\x30\xaf\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"���]���ʃ}�X�N�����p�̃t���O�����g�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}
		Result = Graphics_Android_FragmentShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )ShaderCode->Base.MaskEffect_UseGraphHandle_FS_Code, MaskEffect_UseGraphHandle_FS, sizeof( ShaderCode->Base.MaskEffect_UseGraphHandle_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xde\x30\xb9\x30\xaf\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�}�X�N�����p�̃t���O�����g�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}
		Result = Graphics_Android_FragmentShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )ShaderCode->Base.MaskEffect_UseGraphHandle_ReverseEffect_FS_Code, MaskEffect_UseGraphHandle_ReverseEffect_FS, sizeof( ShaderCode->Base.MaskEffect_UseGraphHandle_ReverseEffect_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xcd\x53\xe2\x8e\xb9\x52\x9c\x67\xde\x30\xb9\x30\xaf\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"���]���ʃ}�X�N�����p�̃t���O�����g�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}

		// �}�X�N�p�V�F�[�_�[�̍쐬
		Result = Graphics_Android_Shader_Create( &Shader->Base.MaskEffect_Shader, MaskEffect_VS, MaskEffect_FS ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xde\x30\xb9\x30\xaf\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�}�X�N�����p�̃V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���\n" @*/ ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}
		Result = Graphics_Android_Shader_Create( &Shader->Base.MaskEffect_ReverseEffect_Shader, MaskEffect_VS, MaskEffect_ReverseEffect_FS ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xcd\x53\xe2\x8e\xb9\x52\x9c\x67\xde\x30\xb9\x30\xaf\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"���]���ʃ}�X�N�����p�̃V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���\n" @*/ ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}
		for( i = 0 ; i < 4 ; i ++ )
		{
			Result = Graphics_Android_Shader_Create( &Shader->Base.MaskEffect_UseGraphHandle_Shader[ i ], MaskEffect_VS, MaskEffect_UseGraphHandle_FS[ i ] ) ;
			if( Result < 0 )
			{
				DXST_LOGFILEFMT_ADDUTF16LE(( "\xde\x30\xb9\x30\xaf\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�}�X�N�����p�̃V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���\n" @*/ ) ) ;
				GSYS.HardInfo.UseShader = FALSE ;
				goto END ;
			}
		}
		for( i = 0 ; i < 4 ; i ++ )
		{
			Result = Graphics_Android_Shader_Create( &Shader->Base.MaskEffect_UseGraphHandle_ReverseEffect_Shader[ i ], MaskEffect_VS, MaskEffect_UseGraphHandle_ReverseEffect_FS[ i ] ) ;
			if( Result < 0 )
			{
				DXST_LOGFILEFMT_ADDUTF16LE(( "\xcd\x53\xe2\x8e\xb9\x52\x9c\x67\xde\x30\xb9\x30\xaf\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"���]���ʃ}�X�N�����p�̃V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���\n" @*/ ) ) ;
				GSYS.HardInfo.UseShader = FALSE ;
				goto END ;
			}
		}

		// �P���]���p���_�V�F�[�_�[�E�t���O�����g�V�F�[�_�[�̍쐬
		Result = Graphics_Android_VertexShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&ShaderCode->Base.StretchRect_VS_Code, &Shader->Base.StretchRect_VS, sizeof( ShaderCode->Base.StretchRect_VS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\x58\x53\x14\x7d\xe2\x8e\x01\x90\x28\x75\x6e\x30\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�P���]���p�̒��_�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}
		Result = Graphics_Android_VertexShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&ShaderCode->Base.StretchRectTex2_VS_Code, &Shader->Base.StretchRectTex2_VS, sizeof( ShaderCode->Base.StretchRectTex2_VS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\xa7\x5e\x19\x6a\x32\x00\x0b\x50\x6e\x30\x58\x53\x14\x7d\xe2\x8e\x01\x90\x28\x75\x6e\x30\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�e�N�X�`�����W2�̒P���]���p�̒��_�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}
		Result = Graphics_Android_VertexShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&ShaderCode->Base.StretchRectTex8_VS_Code, &Shader->Base.StretchRectTex8_VS, sizeof( ShaderCode->Base.StretchRectTex8_VS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\xa7\x5e\x19\x6a\x38\x00\x0b\x50\x6e\x30\x58\x53\x14\x7d\xe2\x8e\x01\x90\x28\x75\x6e\x30\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�e�N�X�`�����W8�̒P���]���p�̒��_�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}
		Result = Graphics_Android_FragmentShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&ShaderCode->Base.StretchRect_FS_Code, &StretchRect_FS, sizeof( ShaderCode->Base.StretchRect_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\x58\x53\x14\x7d\xe2\x8e\x01\x90\x28\x75\x6e\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�P���]���p�̃t���O�����g�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}

		// �P���]���p�V�F�[�_�[�̍쐬
		Result = Graphics_Android_Shader_Create( &Shader->Base.StretchRect_Shader, Shader->Base.StretchRect_VS, StretchRect_FS ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\x58\x53\x14\x7d\xe2\x8e\x01\x90\x28\x75\x6e\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�P���]���p�̃V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���\n" @*/ ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}

		// �N���A�����p���_�V�F�[�_�[�E�t���O�����g�V�F�[�_�[�̍쐬
		Result = Graphics_Android_VertexShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&ShaderCode->Base.ClearRT_VS_Code, &ClearRT_VS, sizeof( ShaderCode->Base.ClearRT_VS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xaf\x30\xea\x30\xa2\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�N���A�����p�̒��_�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}
		Result = Graphics_Android_FragmentShader_Create( ( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO * )&ShaderCode->Base.ClearRT_FS_Code, &ClearRT_FS, sizeof( ShaderCode->Base.ClearRT_FS_Code ) / sizeof( GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ) ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xaf\x30\xea\x30\xa2\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x20\x00\x4e\x00\x6f\x00\x2e\x00\x25\x00\x64\x00\x20\x00\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�N���A�����p�̃t���O�����g�V�F�[�_�[�I�u�W�F�N�g No.%d �̍쐬�Ɏ��s���܂���\n" @*/, -( Result + 1 ) ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}

		// �N���A�����p�V�F�[�_�[�̍쐬
		Result = Graphics_Android_Shader_Create( &Shader->Base.ClearRT_Shader, ClearRT_VS, ClearRT_FS ) ;
		if( Result < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xaf\x30\xea\x30\xa2\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�N���A�����p�̃V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���\n" @*/ ) ) ;
			GSYS.HardInfo.UseShader = FALSE ;
			goto END ;
		}
	}

	DXST_LOGFILE_ADDUTF16LE( "\x10\x62\x9f\x52\x0a\x00\x00"/*@ L"����\n" @*/ ) ;

	FunctionResult = 0 ;

END :

	// �V�F�[�_�[�̌�n��
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )&MaskEffect_VS,								sizeof( MaskEffect_VS )									/ sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )&MaskEffect_FS,								sizeof( MaskEffect_FS )									/ sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )&MaskEffect_ReverseEffect_FS,					sizeof( MaskEffect_ReverseEffect_FS )					/ sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )MaskEffect_UseGraphHandle_FS,					sizeof( MaskEffect_UseGraphHandle_FS )					/ sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )MaskEffect_UseGraphHandle_ReverseEffect_FS,	sizeof( MaskEffect_UseGraphHandle_ReverseEffect_FS )	/ sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )&StretchRect_FS,								sizeof( StretchRect_FS )								/ sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )&ClearRT_VS,									sizeof( ClearRT_VS )									/ sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )&ClearRT_FS,									sizeof( ClearRT_FS )									/ sizeof( GLuint ) ) ;

	// �I��
	return FunctionResult ;
}


// Android �̃V�F�[�_�[�̌�n��������
extern int Graphics_Android_Shader_Terminate( void )
{
	GRAPHICS_HARDDATA_ANDROID_DEVICE *Device = &GraphicsHardDataAndroid.Device ;
	GRAPHICS_HARDWARE_ANDROID_SHADER *Shader = &Device->Shader ;

	Graphics_Android_DeviceState_ResetShader() ;

	_MEMSET( Shader->Base.BaseNoneTex_Shader, 0, sizeof( Shader->Base.BaseNoneTex_Shader ) ) ;
	_MEMSET( Shader->Base.BaseUseTex_Shader,  0, sizeof( Shader->Base.BaseUseTex_Shader  ) ) ;
	Graphics_Android_ShaderArray_Release( ( GRAPHICS_ANDROID_SHADER * )&Shader->Base.MaskEffect_Shader,                             sizeof( Shader->Base.MaskEffect_Shader                              ) / sizeof( GRAPHICS_ANDROID_SHADER ) ) ;
	Graphics_Android_ShaderArray_Release( ( GRAPHICS_ANDROID_SHADER * )&Shader->Base.MaskEffect_ReverseEffect_Shader,               sizeof( Shader->Base.MaskEffect_ReverseEffect_Shader                ) / sizeof( GRAPHICS_ANDROID_SHADER ) ) ;
	Graphics_Android_ShaderArray_Release( ( GRAPHICS_ANDROID_SHADER * )Shader->Base.MaskEffect_UseGraphHandle_Shader,               sizeof( Shader->Base.MaskEffect_UseGraphHandle_Shader               ) / sizeof( GRAPHICS_ANDROID_SHADER ) ) ;
	Graphics_Android_ShaderArray_Release( ( GRAPHICS_ANDROID_SHADER * )Shader->Base.MaskEffect_UseGraphHandle_ReverseEffect_Shader, sizeof( Shader->Base.MaskEffect_UseGraphHandle_ReverseEffect_Shader ) / sizeof( GRAPHICS_ANDROID_SHADER ) ) ;
	Graphics_Android_VertexShaderArray_Release( ( GLuint * )&Shader->Base.StretchRect_VS,                                           sizeof( Shader->Base.StretchRect_VS                                 ) / sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release( ( GLuint * )&Shader->Base.StretchRectTex2_VS,                                       sizeof( Shader->Base.StretchRectTex2_VS                             ) / sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release( ( GLuint * )&Shader->Base.StretchRectTex8_VS,                                       sizeof( Shader->Base.StretchRectTex8_VS                             ) / sizeof( GLuint ) ) ;
	Graphics_Android_ShaderArray_Release( ( GRAPHICS_ANDROID_SHADER * )&Shader->Base.StretchRect_Shader,                            sizeof( Shader->Base.StretchRect_Shader                             ) / sizeof( GRAPHICS_ANDROID_SHADER ) ) ;
	Graphics_Android_ShaderArray_Release( ( GRAPHICS_ANDROID_SHADER * )&Shader->Base.ClearRT_Shader,                                sizeof( Shader->Base.ClearRT_Shader                                 ) / sizeof( GRAPHICS_ANDROID_SHADER ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Base.BaseSimple_VS,											sizeof( Shader->Base.BaseSimple_VS									) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Base.BaseNoneTex_FS,											sizeof( Shader->Base.BaseNoneTex_FS									) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Base.BaseUseTex_FS,											sizeof( Shader->Base.BaseUseTex_FS									) / sizeof( GLuint ) ) ; 

	_MEMSET( Shader->Base3D.Base3D_PixelLighting_Normal_Shader,  0, sizeof( Shader->Base3D.Base3D_PixelLighting_Normal_Shader  ) ) ;
	_MEMSET( Shader->Base3D.Base3D_ShadowMap_Normal_Shader,      0, sizeof( Shader->Base3D.Base3D_ShadowMap_Normal_Shader      ) ) ;
	_MEMSET( Shader->Base3D.Base3D_NoLighting_Normal_Shader,     0, sizeof( Shader->Base3D.Base3D_NoLighting_Normal_Shader     ) ) ;
	_MEMSET( Shader->Base3D.Base3D_VertexLighting_Normal_Shader, 0, sizeof( Shader->Base3D.Base3D_VertexLighting_Normal_Shader ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Base3D.Base3D_PixelLighting_VS,                               sizeof( Shader->Base3D.Base3D_PixelLighting_VS             ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Base3D.Base3D_PixelLighting_Normal_FS,                        sizeof( Shader->Base3D.Base3D_PixelLighting_Normal_FS      ) / sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Base3D.Base3D_ShadowMap_VS,                                   sizeof( Shader->Base3D.Base3D_ShadowMap_VS                 ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Base3D.Base3D_ShadowMap_Normal_FS,                            sizeof( Shader->Base3D.Base3D_ShadowMap_Normal_FS          ) / sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Base3D.Base3D_NoLighting_VS,                                  sizeof( Shader->Base3D.Base3D_NoLighting_VS                ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Base3D.Base3D_NoLighting_Normal_FS,                           sizeof( Shader->Base3D.Base3D_NoLighting_Normal_FS         ) / sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Base3D.Base3D_VertexLighting_VS,                              sizeof( Shader->Base3D.Base3D_VertexLighting_VS            ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Base3D.Base3D_VertexLighting_Normal_FS,                       sizeof( Shader->Base3D.Base3D_VertexLighting_Normal_FS     ) / sizeof( GLuint ) ) ;

#ifndef DX_NON_MODEL

	_MEMSET( Shader->Model.MV1_PixelLighting_ToonType1_Shader,  0, sizeof( Shader->Model.MV1_PixelLighting_ToonType1_Shader  ) ) ;
	_MEMSET( Shader->Model.MV1_PixelLighting_ToonType2_Shader,  0, sizeof( Shader->Model.MV1_PixelLighting_ToonType2_Shader  ) ) ;
	_MEMSET( Shader->Model.MV1_PixelLighting_Normal_Shader,     0, sizeof( Shader->Model.MV1_PixelLighting_Normal_Shader     ) ) ;
	_MEMSET( Shader->Model.MV1_MaterialType_Shader,             0, sizeof( Shader->Model.MV1_MaterialType_Shader             ) ) ;
	_MEMSET( Shader->Model.MV1_ToonOutLine_ShadowMap_Shader,    0, sizeof( Shader->Model.MV1_ToonOutLine_ShadowMap_Shader    ) ) ;
	_MEMSET( Shader->Model.MV1_ToonOutLine_Shader,              0, sizeof( Shader->Model.MV1_ToonOutLine_Shader              ) ) ;
	_MEMSET( Shader->Model.MV1_ShadowMap_Normal_Shader,         0, sizeof( Shader->Model.MV1_ShadowMap_Normal_Shader         ) ) ;
	_MEMSET( Shader->Model.MV1_ShadowMap_Toon_Shader,           0, sizeof( Shader->Model.MV1_ShadowMap_Toon_Shader           ) ) ;
	_MEMSET( Shader->Model.MV1_NoLighting_Toon_Shader,          0, sizeof( Shader->Model.MV1_NoLighting_Toon_Shader          ) ) ;
	_MEMSET( Shader->Model.MV1_NoLighting_Normal_Shader,        0, sizeof( Shader->Model.MV1_NoLighting_Normal_Shader        ) ) ;
	_MEMSET( Shader->Model.MV1_VertexLighting_ToonType1_Shader, 0, sizeof( Shader->Model.MV1_VertexLighting_ToonType1_Shader ) ) ;
	_MEMSET( Shader->Model.MV1_VertexLighting_ToonType2_Shader, 0, sizeof( Shader->Model.MV1_VertexLighting_ToonType2_Shader ) ) ;
	_MEMSET( Shader->Model.MV1_VertexLighting_Normal_Shader,    0, sizeof( Shader->Model.MV1_VertexLighting_Normal_Shader    ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Model.MV1_PixelLighting_VS,                                 sizeof( Shader->Model.MV1_PixelLighting_VS                ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_PixelLighting_ToonType1_FS,                       sizeof( Shader->Model.MV1_PixelLighting_ToonType1_FS      ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_PixelLighting_ToonType2_FS,                       sizeof( Shader->Model.MV1_PixelLighting_ToonType2_FS      ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_PixelLighting_Normal_FS,                          sizeof( Shader->Model.MV1_PixelLighting_Normal_FS         ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_MaterialType_FS,                                  sizeof( Shader->Model.MV1_MaterialType_FS                 ) / sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Model.MV1_ToonOutLine_ShadowMap_VS,                         sizeof( Shader->Model.MV1_ToonOutLine_ShadowMap_VS        ) / sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Model.MV1_ToonOutLine_VS,                                   sizeof( Shader->Model.MV1_ToonOutLine_VS                  ) / sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Model.MV1_ShadowMap_VS,                                     sizeof( Shader->Model.MV1_ShadowMap_VS                    ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_ShadowMap_Normal_FS,                              sizeof( Shader->Model.MV1_ShadowMap_Normal_FS             ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_ShadowMap_Toon_FS,                                sizeof( Shader->Model.MV1_ShadowMap_Toon_FS               ) / sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Model.MV1_NoLighting_VS,                                    sizeof( Shader->Model.MV1_NoLighting_VS                   ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_NoLighting_Toon_FS,                               sizeof( Shader->Model.MV1_NoLighting_Toon_FS              ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_NoLighting_Normal_FS,                             sizeof( Shader->Model.MV1_NoLighting_Normal_FS            ) / sizeof( GLuint ) ) ;
	Graphics_Android_VertexShaderArray_Release(   ( GLuint * )Shader->Model.MV1_VertexLighting_VS,                                sizeof( Shader->Model.MV1_VertexLighting_VS               ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_VertexLighting_ToonType1_FS,                      sizeof( Shader->Model.MV1_VertexLighting_ToonType1_FS     ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_VertexLighting_ToonType2_FS,                      sizeof( Shader->Model.MV1_VertexLighting_ToonType2_FS     ) / sizeof( GLuint ) ) ;
	Graphics_Android_FragmentShaderArray_Release( ( GLuint * )Shader->Model.MV1_VertexLighting_Normal_FS,                         sizeof( Shader->Model.MV1_VertexLighting_Normal_FS        ) / sizeof( GLuint ) ) ;

#endif // DX_NON_MODEL

	Graphics_Android_ShaderList_Terminate() ;

#ifndef DX_NON_FILTER
	GraphFilter_Android_ReleaseShaderAll() ;
#endif // DX_NON_FILTER

#ifndef DX_NON_LIVE2D_CUBISM4
	Live2D_Cubism4_Android_ReleaseShaderAll() ;
#endif // DX_NON_LIVE2D_CUBISM4

	// ����I��
	return 0 ;
}

// �R�c�W���`��̎w��̒��_�p�̕`��p�V�F�[�_�[���Z�b�g�A�b�v����
extern int Graphics_Android_Shader_Normal3DDraw_Setup( void )
{
	GRAPHICS_HARDWARE_ANDROID_SHADER_BASE3D		*SB3D  = &GANDR.Device.Shader.Base3D ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_BASE3D	*SCB3D = &GANDR.ShaderCode.Base3D ;
	int											ValidPL ;
	GRAPHICS_ANDROID_SHADER						**Shader_PL		= NULL ;
	GLuint										*VS_PL			= NULL ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*VSAddress_PL	= NULL ;
	GLuint										*FS_PL			= NULL ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*FSAddress_PL	= NULL ;
	GRAPHICS_ANDROID_SHADER						**Shader		= NULL ;
	GLuint										*VS				= NULL ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*VSAddress		= NULL ;
	GLuint										*FS				= NULL ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*FSAddress		= NULL ;
	int											ShadowMap ;
	int											IgnoreTextureAlpha ;
	int											FogType ;
	int											LightIndex84 ;
	int											LightIndex20 ;
	int											LightIndex10 ;
	int											AlphaTestMode ;
	int											BumpMap ;
	int											RenderType ;
	int											NextBlendMode ;

	if( GANDR.ShaderCode.Base3D.Base3DShaderInitializeFlag == FALSE &&
		Graphics_Android_ShaderCode_Base3D_Initialize() == FALSE )
	{
		return FALSE ;
	}

	// �e�N�X�`���A���t�@�𖳎����邩�ǂ������Z�b�g
	IgnoreTextureAlpha = 1 ;
	if( GANDR.Device.DrawSetting.AlphaChannelValidFlag ||
		GANDR.Device.DrawSetting.AlphaTestValidFlag ||
		GANDR.Device.State.DepthEnable )
	{
		IgnoreTextureAlpha = 0 ;
	}
	if( IgnoreTextureAlpha != GANDR.Device.DrawSetting.IgnoreGraphAlphaFlag )
	{
		Graphics_Android_DrawSetting_SetIgnoreDrawGraphAlpha( IgnoreTextureAlpha ) ;
	}

	// �u�����h���[�h�̌���
	{
		NextBlendMode = GANDR.Device.DrawSetting.BlendMode ;
		switch( GANDR.Device.DrawSetting.BlendMode )
		{
		case DX_BLENDMODE_SUB :
			// ���Z�u�����h�̏ꍇ��14�Ԗڂ̃u�����h���[�h���g�p����
			NextBlendMode = DX_BLENDMODE_SUB1 ;
			break ;

		case DX_BLENDMODE_NOBLEND :
			// �`���Ƀ��l������ꍇ�� DX_BLENDMODE_NOBLEND �ł��u�����h���[�h�� DX_BLENDMODE_SRCCOLOR �ɂ���
			if( GSYS.DrawSetting.AlphaChDrawMode )
			{
				NextBlendMode = DX_BLENDMODE_SRCCOLOR ;
			}

			// �`�挳�摜�Ƀ��`�����l��������ꍇ��u�����h�摜�̗L���ȂǏ�������� DX_BLENDMODE_ALPHA ���g�p����
			if( GANDR.Device.DrawSetting.RenderTexture != NULL )
			{
				if( GANDR.Device.DrawSetting.AlphaChannelValidFlag == TRUE )
				{
					NextBlendMode = DX_BLENDMODE_ALPHA ;
				}
			}
			break ;
		}
	}

	ShadowMap       = GSYS.DrawSetting.UseShadowMapNum != 0 ? 1 : 0 ;
	FogType         = GANDR.Device.State.FogEnable ? GANDR.Device.State.FogMode : DX_FOGMODE_NONE ;
	RenderType = g_DefaultBlendDescArray[ NextBlendMode ].RenderType ;
	AlphaTestMode   = GANDR.Device.State.AlphaTestModeShaderIndex ;
	BumpMap         = 0 ;

	if( GSYS.DrawSetting.ShadowMapDraw )
	{
		// �V���h�E�}�b�v�ւ̕`��

		VS           =  &SB3D->Base3D_ShadowMap_VS     [ BumpMap ] ;
		VSAddress    = &SCB3D->Base3D_ShadowMap_VS_Code[ BumpMap ] ;

		FS           =  &SB3D->Base3D_ShadowMap_Normal_FS     [ AlphaTestMode ] ;
		FSAddress    = &SCB3D->Base3D_ShadowMap_Normal_FS_Code[ AlphaTestMode ] ;

		Shader       = &SB3D->Base3D_ShadowMap_Normal_Shader[ BumpMap ][ AlphaTestMode ] ;
	}
	else
	if( GANDR.Device.State.Lighting )
	{
		// ���C�e�B���O����`��

		int LightMode[ DX_PIXELLIGHTING_LIGHT_NUM ] ;
		int i ;

		for( i = 0 ; i < DX_PIXELLIGHTING_LIGHT_NUM ; i ++ )
		{
			LightMode[ i ] = GANDR.Device.State.LightEnableFlag[ i ] ? GANDR.Device.State.LightParam[ i ].LightType : 0 ;
		}

		LightIndex84 = GANDR.ShaderCode.Base.LightIndexList84[ LightMode[ 0 ] ][ LightMode[ 1 ] ][ LightMode[ 2 ] ][ LightMode[ 3 ] ][ LightMode[ 4 ] ][ LightMode[ 5 ] ] ;
		LightIndex20 = GANDR.ShaderCode.Base.LightIndexList20[ LightMode[ 0 ] ][ LightMode[ 1 ] ][ LightMode[ 2 ] ] ;
		LightIndex10 = GANDR.ShaderCode.Base.LightIndexList10
				[ LightMode[ 0 ] == DX_LIGHTTYPE_D3DLIGHT_DIRECTIONAL ? 2 : ( LightMode[ 0 ] ? 1 : 0 ) ]
				[ LightMode[ 1 ] == DX_LIGHTTYPE_D3DLIGHT_DIRECTIONAL ? 2 : ( LightMode[ 1 ] ? 1 : 0 ) ]
				[ LightMode[ 2 ] == DX_LIGHTTYPE_D3DLIGHT_DIRECTIONAL ? 2 : ( LightMode[ 2 ] ? 1 : 0 ) ] ;

		VS_PL        =  &SB3D->Base3D_PixelLighting_VS     [ ShadowMap ][ FogType ] ;
		VSAddress_PL = &SCB3D->Base3D_PixelLighting_VS_Code[ ShadowMap ][ FogType ] ;

		FS_PL        =  &SB3D->Base3D_PixelLighting_Normal_FS     [ ShadowMap ][ LightIndex84 ][ RenderType ][ AlphaTestMode ] ;
		FSAddress_PL = &SCB3D->Base3D_PixelLighting_Normal_FS_Code[ ShadowMap ][ LightIndex84 ][ RenderType ][ AlphaTestMode ] ;

		Shader_PL    =  &SB3D->Base3D_PixelLighting_Normal_Shader[ ShadowMap ][ FogType ][ LightIndex84 ][ RenderType ][ AlphaTestMode ] ;

		VS           =  &SB3D->Base3D_VertexLighting_VS     [ ShadowMap ][ FogType ][ LightIndex20 ] ;
		VSAddress    = &SCB3D->Base3D_VertexLighting_VS_Code[ ShadowMap ][ FogType ][ LightIndex20 ] ;

		FS           =  &SB3D->Base3D_VertexLighting_Normal_FS     [ ShadowMap ][ LightIndex10 ][ RenderType ][ AlphaTestMode ] ;
		FSAddress    = &SCB3D->Base3D_VertexLighting_Normal_FS_Code[ ShadowMap ][ LightIndex10 ][ RenderType ][ AlphaTestMode ] ;

		Shader       =  &SB3D->Base3D_VertexLighting_Normal_Shader[ ShadowMap ][ FogType ][ LightIndex20 ][ LightIndex10 ][ RenderType ][ AlphaTestMode ] ;
	}
	else
	{
		// ���C�e�B���O�Ȃ��`��

		VS           =  &SB3D->Base3D_NoLighting_VS     [ FogType ] ;
		VSAddress    = &SCB3D->Base3D_NoLighting_VS_Code[ FogType ] ;

		FS           =  &SB3D->Base3D_NoLighting_Normal_FS     [ RenderType ][ AlphaTestMode ] ;
		FSAddress    = &SCB3D->Base3D_NoLighting_Normal_FS_Code[ RenderType ][ AlphaTestMode ] ;

		Shader       =  &SB3D->Base3D_NoLighting_Normal_Shader[ FogType ][ RenderType ][ AlphaTestMode ] ;
	}

	ValidPL = 
		VSAddress_PL != NULL && VSAddress_PL->Binary != NULL &&
		FSAddress_PL != NULL && FSAddress_PL->Binary != NULL ;

	if( ( GSYS.Light.EnableNum > DX_VERTEXLIGHTING_LIGHT_NUM || GANDR.UsePixelLightingShader ) && ValidPL )
	{
		// ���_�V�F�[�_�[�����邩�ǂ����𒲂ׂ�
		if( *VS_PL == 0 )
		{
			// ���_�V�F�[�_�[�̍쐬�����݂�
			if( Graphics_Android_VertexShader_Create( VSAddress_PL, VS_PL, 1 ) != 0 )
			{
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x41\x00\x6e\x00\x64\x00\x72\x00\x6f\x00\x69\x00\x64\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x5f\x00\x4e\x00\x6f\x00\x72\x00\x6d\x00\x61\x00\x6c\x00\x33\x00\x44\x00\x44\x00\x72\x00\x61\x00\x77\x00\x5f\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"Graphics_Android_Shader_Normal3DDraw_Setup �Ńs�N�Z�����C�e�B���O�p���_�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
				return FALSE ;
			}
		}

		// �t���O�����g�V�F�[�_�[�����邩�ǂ����𒲂ׂ�
		if( *FS_PL == 0 )
		{
			// �t���O�����g�V�F�[�_�[�̍쐬�����݂�
			if( Graphics_Android_FragmentShader_Create( FSAddress_PL, FS_PL, 1 ) != 0 )
			{
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x41\x00\x6e\x00\x64\x00\x72\x00\x6f\x00\x69\x00\x64\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x5f\x00\x4e\x00\x6f\x00\x72\x00\x6d\x00\x61\x00\x6c\x00\x33\x00\x44\x00\x44\x00\x72\x00\x61\x00\x77\x00\x5f\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\xd5\x30\xe9\x30\xb0\x30\xe1\x30\xf3\x30\xc8\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"Graphics_Android_Shader_Normal3DDraw_Setup �Ńs�N�Z�����C�e�B���O�p�t���O�����g�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
				return FALSE ;
			}
		}

		// �V�F�[�_�[�����邩�ǂ����𒲂ׂ�
		if( *Shader_PL == NULL )
		{
			*Shader_PL = Graphics_Android_GetShaderStruct() ;
			if( *Shader_PL == NULL )
			{
				return FALSE ;
			}
		}
		if( ( *Shader_PL )->Shader == 0 )
		{
			// �V�F�[�_�[�̍쐬�����݂�
			if( Graphics_Android_Shader_Create( *Shader_PL, *VS_PL, *FS_PL ) != 0 )
			{
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x41\x00\x6e\x00\x64\x00\x72\x00\x6f\x00\x69\x00\x64\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x5f\x00\x4e\x00\x6f\x00\x72\x00\x6d\x00\x61\x00\x6c\x00\x33\x00\x44\x00\x44\x00\x72\x00\x61\x00\x77\x00\x5f\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"Graphics_Android_Shader_Normal3DDraw_Setup �Ńs�N�Z�����C�e�B���O�p�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
				return FALSE ;
			}
		}

		// �V�F�[�_�[�̃Z�b�g�A�b�v
		Graphics_Android_DeviceState_SetShader( *Shader_PL, FALSE ) ;
	}
	else
	{
		// �V�F�[�_�[�����邩�ǂ����𒲂ׂ�
		if( *VS == 0 )
		{
			// �V�F�[�_�[�̍쐬�����݂�
			if( Graphics_Android_VertexShader_Create( VSAddress, VS, 1 ) != 0 )
			{
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x41\x00\x6e\x00\x64\x00\x72\x00\x6f\x00\x69\x00\x64\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x5f\x00\x4e\x00\x6f\x00\x72\x00\x6d\x00\x61\x00\x6c\x00\x33\x00\x44\x00\x44\x00\x72\x00\x61\x00\x77\x00\x5f\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\x02\x98\xb9\x70\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"Graphics_Android_Shader_Normal3DDraw_Setup �Œ��_���C�e�B���O�p���_�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
				return FALSE ;
			}
		}


		// �V�F�[�_�[�����邩�ǂ����𒲂ׂ�
		if( *FS == 0 )
		{
			// �V�F�[�_�[�̍쐬�����݂�
			if( Graphics_Android_FragmentShader_Create( FSAddress, FS, 1 ) != 0 )
			{
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x41\x00\x6e\x00\x64\x00\x72\x00\x6f\x00\x69\x00\x64\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x5f\x00\x4e\x00\x6f\x00\x72\x00\x6d\x00\x61\x00\x6c\x00\x33\x00\x44\x00\x44\x00\x72\x00\x61\x00\x77\x00\x5f\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\x02\x98\xb9\x70\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\xd5\x30\xe9\x30\xb0\x30\xe1\x30\xf3\x30\xc8\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"Graphics_Android_Shader_Normal3DDraw_Setup �Œ��_���C�e�B���O�p�t���O�����g�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
				return FALSE ;
			}
		}

		// �V�F�[�_�[�����邩�ǂ����𒲂ׂ�
		if( *Shader == NULL )
		{
			*Shader = Graphics_Android_GetShaderStruct() ;
			if( *Shader == NULL )
			{
				return FALSE ;
			}
		}
		if( ( *Shader )->Shader == 0 )
		{
			// �V�F�[�_�[�̍쐬�����݂�
			if( Graphics_Android_Shader_Create( *Shader, *VS, *FS ) != 0 )
			{
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x41\x00\x6e\x00\x64\x00\x72\x00\x6f\x00\x69\x00\x64\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x5f\x00\x4e\x00\x6f\x00\x72\x00\x6d\x00\x61\x00\x6c\x00\x33\x00\x44\x00\x44\x00\x72\x00\x61\x00\x77\x00\x5f\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\x02\x98\xb9\x70\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"Graphics_Android_Shader_Normal3DDraw_Setup �Œ��_���C�e�B���O�p�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
				return FALSE ;
			}
		}

		// �V�F�[�_�[�̃Z�b�g�A�b�v
		Graphics_Android_DeviceState_SetShader( *Shader, FALSE ) ;
	}

	// �I��
	return TRUE ;
}

// �A���t�@�e�X�g�̔�r���[�h����t���O�����g�V�F�[�_�[�̃A���t�@�e�X�g���[�h( ANDROID_FS_ALPHATEST_CMP_GREATER �� )���擾����
extern int Graphics_Android_Shader_GetAlphaTestModeIndex( int AlphaTestEnable, int AlphaTestMode /* DX_CMP_NEVER �� */ )
{
	if( AlphaTestEnable == FALSE )
	{
		return ANDROID_FS_ALPHATEST_CMP_GREATER ;
	}

	switch( AlphaTestMode )
	{
	default:
		return ANDROID_FS_ALPHATEST_CMP_OTHER ;

	case DX_CMP_GREATER :		// DrawAlpha >  TestParam
		return ANDROID_FS_ALPHATEST_CMP_GREATER ;
	}
}
































// Android �̉�ʊ֌W

// ScreenCopy �� GetDrawScreen ���������邽�߂Ɏg�p����e���|�����o�b�t�@�̍쐬( 0:����  -1:���s )
extern	int		Graphics_Android_SetupSubBackBuffer( void )
{
	GANDR.Device.Screen.SubBackBufferTextureSizeX = GSYS.Screen.MainScreenSizeX ;
	GANDR.Device.Screen.SubBackBufferTextureSizeY = GSYS.Screen.MainScreenSizeY ;

	// �s�N�Z���^�C�v�̌���
	if( GSYS.Screen.UserScreenImage != NULL )
	{
		DWORD i ;
		DWORD PixelNum = GANDR.Device.Screen.SubBackBufferTextureSizeX * GANDR.Device.Screen.SubBackBufferTextureSizeY ;
		BYTE *p ;

		switch( GSYS.Screen.UserScreenImagePixelFormat )
		{
		case DX_USER_SCREEN_PIXEL_FORMAT_R5G6B5:
			GANDR.Device.Screen.SubBackBufferTextureInternalFormat = GL_RGB ;
			GANDR.Device.Screen.SubBackBufferTexturePixelFormat = GL_RGB ;
			GANDR.Device.Screen.SubBackBufferTexturePixelType = GL_UNSIGNED_SHORT_5_6_5 ;
			break ;

		case DX_USER_SCREEN_PIXEL_FORMAT_R5G5B5X1:
			GANDR.Device.Screen.SubBackBufferTextureInternalFormat = GL_RGBA ;
			GANDR.Device.Screen.SubBackBufferTexturePixelFormat = GL_RGBA ;
			GANDR.Device.Screen.SubBackBufferTexturePixelType = GL_UNSIGNED_SHORT_5_5_5_1 ;
			break ;

		case DX_USER_SCREEN_PIXEL_FORMAT_X1R5G5B5:
			GANDR.Device.Screen.SubBackBufferTextureInternalFormat = GL_RGBA ;
			GANDR.Device.Screen.SubBackBufferTexturePixelFormat = GL_RGBA ;
			GANDR.Device.Screen.SubBackBufferTexturePixelType = GL_UNSIGNED_SHORT_5_5_5_1 ;

			GANDR.Device.Screen.SubBackBufferTextureTempBuffer = DXALLOC( GANDR.Device.Screen.SubBackBufferTextureSizeX * GANDR.Device.Screen.SubBackBufferTextureSizeY * 2 ) ;
			if( GANDR.Device.Screen.SubBackBufferTextureTempBuffer == NULL )
			{
				DXST_LOGFILE_ADDUTF16LE( "\xb5\x30\xd6\x30\xd0\x30\xc3\x30\xaf\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x78\x30\x6e\x30\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\xe2\x8e\x01\x90\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�u�o�b�N�o�b�t�@�ւ̃e�N�X�`���]���p�̃������m�ۂɎ��s���܂���\n" @*/ ) ;
				return -1 ;
			}

			// �]���p�o�b�t�@�̓��e��������
			p = ( BYTE * )GANDR.Device.Screen.SubBackBufferTextureTempBuffer ;
			for( i = 0 ; i < PixelNum ; i ++ )
			{
				( ( WORD * )p )[ i ] = 0x0001 ;
			}
			break ;

		case DX_USER_SCREEN_PIXEL_FORMAT_X8B8G8R8:
			GANDR.Device.Screen.SubBackBufferTextureInternalFormat = GL_RGBA ;
			GANDR.Device.Screen.SubBackBufferTexturePixelFormat = GL_RGBA ;
			GANDR.Device.Screen.SubBackBufferTexturePixelType = GL_UNSIGNED_BYTE ;
			break ;

		case DX_USER_SCREEN_PIXEL_FORMAT_X8R8G8B8:
			if( GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_TEXTURE_FORMAT_BGRA8888 ] )
			{
				GANDR.Device.Screen.SubBackBufferTextureInternalFormat = GL_BGRA_EXT ;
				GANDR.Device.Screen.SubBackBufferTexturePixelFormat = GL_BGRA_EXT ;
			}
			else
			{
				GANDR.Device.Screen.SubBackBufferTextureInternalFormat = GL_RGBA ;
				GANDR.Device.Screen.SubBackBufferTexturePixelFormat = GL_RGBA ;
				GANDR.Device.Screen.SubBackBufferTextureTempBuffer = DXALLOC( GANDR.Device.Screen.SubBackBufferTextureSizeX * GANDR.Device.Screen.SubBackBufferTextureSizeY * 4 ) ;
				if( GANDR.Device.Screen.SubBackBufferTextureTempBuffer == NULL )
				{
					DXST_LOGFILE_ADDUTF16LE( "\xb5\x30\xd6\x30\xd0\x30\xc3\x30\xaf\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x78\x30\x6e\x30\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\xe2\x8e\x01\x90\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�u�o�b�N�o�b�t�@�ւ̃e�N�X�`���]���p�̃������m�ۂɎ��s���܂���\n" @*/ ) ;
					return -1 ;
				}

				// �]���p�o�b�t�@�̓��e��������
				p = ( BYTE * )GANDR.Device.Screen.SubBackBufferTextureTempBuffer ;
				for( i = 0 ; i < PixelNum ; i ++ )
				{
					( ( DWORD * )p )[ i ] = 0xff000000 ;
				}
			}
			GANDR.Device.Screen.SubBackBufferTexturePixelType = GL_UNSIGNED_BYTE ;
			break ;
		}
	}
	else
	if( GSYS.Setting.NotUseHardware )
	{
		if( GSYS.Screen.MainScreenColorBitDepth == 16 )
		{
			GANDR.Device.Screen.SubBackBufferTextureInternalFormat = GL_RGB ;
			GANDR.Device.Screen.SubBackBufferTexturePixelFormat = GL_RGB ;
			GANDR.Device.Screen.SubBackBufferTexturePixelType = GL_UNSIGNED_SHORT_5_6_5 ;
		}
		else
		{
			if( GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_TEXTURE_FORMAT_BGRA8888 ] )
			{
				GANDR.Device.Screen.SubBackBufferTextureInternalFormat = GL_BGRA_EXT ;
				GANDR.Device.Screen.SubBackBufferTexturePixelFormat = GL_BGRA_EXT ;
			}
			else
			{
				DWORD i ;
				DWORD PixelNum ;
				DWORD *p ;

				GANDR.Device.Screen.SubBackBufferTextureInternalFormat = GL_RGBA ;
				GANDR.Device.Screen.SubBackBufferTexturePixelFormat = GL_RGBA ;
				GANDR.Device.Screen.SubBackBufferTextureTempBuffer = DXALLOC( GANDR.Device.Screen.SubBackBufferTextureSizeX * GANDR.Device.Screen.SubBackBufferTextureSizeY * 4 ) ;
				if( GANDR.Device.Screen.SubBackBufferTextureTempBuffer == NULL )
				{
					DXST_LOGFILE_ADDUTF16LE( "\xb5\x30\xd6\x30\xd0\x30\xc3\x30\xaf\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x78\x30\x6e\x30\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\xe2\x8e\x01\x90\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�u�o�b�N�o�b�t�@�ւ̃e�N�X�`���]���p�̃������m�ۂɎ��s���܂���\n" @*/ ) ;
					return -1 ;
				}

				// �]���p�o�b�t�@�̓��e��������
				PixelNum = GANDR.Device.Screen.SubBackBufferTextureSizeX * GANDR.Device.Screen.SubBackBufferTextureSizeY ;
				p = ( DWORD * )GANDR.Device.Screen.SubBackBufferTextureTempBuffer ;
				for( i = 0 ; i < PixelNum ; i ++ )
				{
					p[ i ] = 0xff000000 ;
				}
			}
			GANDR.Device.Screen.SubBackBufferTexturePixelType = GL_UNSIGNED_BYTE ;
		}
	}
	else
	{
		GANDR.Device.Screen.SubBackBufferTextureInternalFormat = GL_RGB ;
		GANDR.Device.Screen.SubBackBufferTexturePixelFormat = GL_RGB ;
		GANDR.Device.Screen.SubBackBufferTexturePixelType = GL_UNSIGNED_BYTE ;
	}

	// Offscreen position framebuffer texture target
	glGenTextures( 1, &GANDR.Device.Screen.SubBackBufferTexture ) ;
	glBindTexture( GL_TEXTURE_2D, GANDR.Device.Screen.SubBackBufferTexture ) ;
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ) ;
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ) ;
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ) ;
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ) ;
	glTexImage2D( GL_TEXTURE_2D, 0, GANDR.Device.Screen.SubBackBufferTextureInternalFormat, GANDR.Device.Screen.SubBackBufferTextureSizeX, GANDR.Device.Screen.SubBackBufferTextureSizeY, 0, GANDR.Device.Screen.SubBackBufferTexturePixelFormat, GANDR.Device.Screen.SubBackBufferTexturePixelType, 0 ) ;

	// �\�t�g�E�F�A�����_�����O���[�h�ł͂Ȃ��ꍇ�̂݃t���[���o�b�t�@���쐬����
	if( GSYS.Setting.NotUseHardware == FALSE )
	{
		glGenFramebuffers( 1, &GANDR.Device.Screen.SubBackBufferFrameBuffer ) ;
		glBindFramebuffer( GL_FRAMEBUFFER, GANDR.Device.Screen.SubBackBufferFrameBuffer ) ;

		// �����_�[�o�b�t�@���ʎq�𐶐����܂��B
		glGenRenderbuffers( 1, &GANDR.Device.Screen.SubBackBufferDepthBuffer ) ;

		// �����_�[�o�b�t�@���ʎq�ɑΉ����������_�[�o�b�t�@�I�u�W�F�N�g�𐶐����܂��B
		glBindRenderbuffer( GL_RENDERBUFFER, GANDR.Device.Screen.SubBackBufferDepthBuffer ) ;

		// �����_�[�o�b�t�@�̕��ƍ������w�肵�܂��B
		glRenderbufferStorage( GL_RENDERBUFFER, GANDR.Device.Caps.DepthBufferFormat[ ZBUFFER_FORMAT_24BIT ], GANDR.Device.Screen.SubBackBufferTextureSizeX, GANDR.Device.Screen.SubBackBufferTextureSizeY ) ;

		// �t���[���o�b�t�@�̃A�^�b�`�����g�Ƃ��ă����_�[�o�b�t�@���A�^�b�`���܂��B
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, GANDR.Device.Screen.SubBackBufferDepthBuffer ) ;

		// �t���[���o�b�t�@�̃A�^�b�`�����g�Ƃ��� 2D �e�N�X�`�����A�^�b�`���܂��B
		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GANDR.Device.Screen.SubBackBufferTexture, 0 ) ;

		// �t���[���o�b�t�@�����S���ǂ����`�F�b�N���܂��B
		GLint status = glCheckFramebufferStatus( GL_FRAMEBUFFER ) ;
		if( status != GL_FRAMEBUFFER_COMPLETE )
		{
			DXST_LOGFILE_ADDUTF16LE( "\xb5\x30\xd6\x30\xd0\x30\xc3\x30\xaf\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�u�o�b�N�o�b�t�@�̍쐬�Ɏ��s���܂���\n" @*/ ) ;
			return -1 ;
		}
		glBindFramebuffer( GL_FRAMEBUFFER, 0 ) ;
	}

	// �I��
	return 0 ;
}

// �T�u�o�b�N�o�b�t�@�̌�n�����s��( 0:����  -1:���s )
extern int Graphics_Android_TerminateSubBackBuffer( void )
{
	if( GANDR.Device.Screen.SubBackBufferTextureTempBuffer != NULL )
	{
		DXFREE( GANDR.Device.Screen.SubBackBufferTextureTempBuffer ) ;
		GANDR.Device.Screen.SubBackBufferTextureTempBuffer = NULL ;
	}

	if( GANDR.Device.Screen.SubBackBufferFrameBuffer != 0 )
	{
		glDeleteFramebuffers( 1, &GANDR.Device.Screen.SubBackBufferFrameBuffer ) ;
		GANDR.Device.Screen.SubBackBufferFrameBuffer = 0 ;
	}

	if( GANDR.Device.Screen.SubBackBufferTexture != 0 )
	{
		glDeleteTextures( 1, &GANDR.Device.Screen.SubBackBufferTexture ) ;
		GANDR.Device.Screen.SubBackBufferTexture = 0 ;
	}

	if( GANDR.Device.Screen.SubBackBufferDepthBuffer != 0 )
	{
		glDeleteRenderbuffers( 1, &GANDR.Device.Screen.SubBackBufferDepthBuffer ) ;
		GANDR.Device.Screen.SubBackBufferDepthBuffer = 0 ;
	}

	// �I��
	return 0 ;
}

// �\��ʂ��`���̍ۂ̒������
extern int Graphics_Android_FrontScreenProcess( void )
{
	int NowTime ;

	// �`��悪�\��ʂł͂Ȃ��ꍇ�͉������Ȃ�
	if( ( DWORD )GSYS.DrawSetting.TargetScreen[ 0 ] != DX_SCREEN_FRONT )
	{
		return 0 ;
	}

	// �O�� ScreenCopy �����Ă��� 16ms �ȏ�o�߂��Ă����� ScreenCopy ���s��
	NowTime = NS_GetNowCount() ;
	if( NowTime - GANDR.Device.Screen.FrontScreenCopyTime > 16 )
	{
		Graphics_Screen_ScreenCopyBase( TRUE ) ;

		GANDR.Device.Screen.FrontScreenCopyTime = NowTime ;
	}

	// �I��
	return 0 ;
}
























// Android �̉摜�֌W

// ANDROID_PIXEL_FORMAT_R8G8B8A8 �Ȃǂ̃t�H�[�}�b�g�ɍ��킹���J���[�t�H�[�}�b�g�����擾����
extern COLORDATA *Graphics_Android_GetDataFormatColorData( int PixelFormat )
{
	static int InitializeFlag = FALSE ;
	static COLORDATA R8G8B8A8_ColorData ;
	static COLORDATA R8G8B8_ColorData ;
	static COLORDATA A4B4G4R4_ColorData ;
	static COLORDATA A1B5G5R5_ColorData ;
	static COLORDATA B5G6R5_ColorData ;
	static COLORDATA R8_ColorData ;
	static COLORDATA R16G16B16F_ColorData ;
	static COLORDATA R32G32B32F_ColorData ;
	static COLORDATA R16G16B16A16F_ColorData ;
	static COLORDATA R32G32B32A32F_ColorData ;

	if( InitializeFlag == FALSE )
	{
		InitializeFlag = TRUE ;
		NS_CreateColorData( &R8G8B8A8_ColorData,       32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000 ) ;
		NS_CreateColorData( &R8G8B8_ColorData,         24, 0x000000ff, 0x0000ff00, 0x00ff0000, 0x00000000 ) ;
		NS_CreateColorData( &A4B4G4R4_ColorData,       16, 0x0000f000, 0x00000f00, 0x000000f0, 0x0000000f ) ;
		NS_CreateColorData( &A1B5G5R5_ColorData,       16, 0x0000f800, 0x000007c0, 0x0000003e, 0x00000001 ) ;
		NS_CreateColorData( &B5G6R5_ColorData,         16, 0x0000f800, 0x000007e0, 0x0000001f, 0x00000000 ) ;
		NS_CreateColorData( &R8_ColorData,			    8, 0x000000ff, 0x00000000, 0x00000000, 0x00000000 ) ;
		NS_CreateColorData( &R16G16B16F_ColorData,      0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 3, 16,  TRUE ) ;
		NS_CreateColorData( &R32G32B32F_ColorData,      0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 3, 32,  TRUE ) ;
		NS_CreateColorData( &R16G16B16A16F_ColorData,   0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 4, 16,  TRUE ) ;
		NS_CreateColorData( &R32G32B32A32F_ColorData,   0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 4, 32,  TRUE ) ;
	}

	     if( PixelFormat == ANDROID_PIXEL_FORMAT_R8G8B8A8			) return &R8G8B8A8_ColorData ;
	else if( PixelFormat == ANDROID_PIXEL_FORMAT_R8G8B8				) return &R8G8B8_ColorData ;
	else if( PixelFormat == ANDROID_PIXEL_FORMAT_A4B4G4R4			) return &A4B4G4R4_ColorData ;
	else if( PixelFormat == ANDROID_PIXEL_FORMAT_A1B5G5R5			) return &A1B5G5R5_ColorData ;
	else if( PixelFormat == ANDROID_PIXEL_FORMAT_B5G6R5				) return &B5G6R5_ColorData ;
	else if( PixelFormat == ANDROID_PIXEL_FORMAT_R8					) return &R8_ColorData ;
	else if( PixelFormat == ANDROID_PIXEL_FORMAT_R16G16B16_FLOAT	) return &R16G16B16F_ColorData ;
	else if( PixelFormat == ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT	) return &R32G32B32F_ColorData ;
	else if( PixelFormat == ANDROID_PIXEL_FORMAT_R16G16B16A16_FLOAT	) return &R16G16B16A16F_ColorData ;
	else if( PixelFormat == ANDROID_PIXEL_FORMAT_R32G32B32A32_FLOAT	) return &R32G32B32A32F_ColorData ;

	return NULL ;
}



// ��{�C���[�W�̃t�H�[�}�b�g�� DX_BASEIMAGE_FORMAT_NORMAL �ɕϊ�����K�v�����邩�ǂ������`�F�b�N����
// ( RequiredRgbBaseImageConvFlag �� RequiredAlphaBaseImageConvFlag �ɓ���l  TRUE:�ϊ�����K�v������  FALSE:�ϊ�����K�v�͖��� )
extern	int		Graphics_CheckRequiredNormalImageConv_BaseImageFormat_PF(
	IMAGEDATA_ORIG *Orig,
	int             RgbBaseImageFormat,
	int            *RequiredRgbBaseImageConvFlag,
	int             AlphaBaseImageFormat,
	int            *RequiredAlphaBaseImageConvFlag
)
{
	int RgbConvFlag   = FALSE ;
	int AlphaConvFlag = FALSE ;

	if( Orig->FormatDesc.TextureFlag )
	{
		if( RgbBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT2 || RgbBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT4 )
		{
			RgbConvFlag = TRUE ;
		}

		if( AlphaBaseImageFormat >= 0 )
		{
			if( AlphaBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT2 || AlphaBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT4 )
			{
				AlphaConvFlag = TRUE ;
			}
		}
	}
	else
	{
		if( RgbBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT1 ||
			RgbBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT2 ||
			RgbBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT3 ||
			RgbBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT4 ||
			RgbBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT5 ||
			RgbBaseImageFormat == DX_BASEIMAGE_FORMAT_BC7_UNORM ||
			RgbBaseImageFormat == DX_BASEIMAGE_FORMAT_BC7_UNORM_SRGB )
		{
			RgbConvFlag = TRUE ;
		}

		if( AlphaBaseImageFormat >= 0 )
		{
			if( AlphaBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT1 ||
				AlphaBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT2 ||
				AlphaBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT3 ||
				AlphaBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT4 ||
				AlphaBaseImageFormat == DX_BASEIMAGE_FORMAT_DXT5 ||
				AlphaBaseImageFormat == DX_BASEIMAGE_FORMAT_BC7_UNORM ||
				AlphaBaseImageFormat == DX_BASEIMAGE_FORMAT_BC7_UNORM_SRGB )
			{
				AlphaConvFlag = TRUE ;
			}
		}
	}

	if( RequiredRgbBaseImageConvFlag != NULL )
	{
		*RequiredRgbBaseImageConvFlag = RgbConvFlag ;
	}

	if( RequiredAlphaBaseImageConvFlag != NULL )
	{
		*RequiredAlphaBaseImageConvFlag = AlphaConvFlag ;
	}

	// ����I��
	return 0 ;
}

// �e�N�X�`���摜�]���p�̋��L�������̃Z�b�g�A�b�v���s��
extern int Graphics_Android_Texture_SetupCommonBuffer( unsigned int Size )
{
	// ���Ɏw��̃T�C�Y���m�ۂ��Ă������牽�������ɏI��
	if( GANDR.Texture.CommonBufferSize >= Size )
	{
		return 0 ;
	}

	// �����̃����������
	DXFREE( GANDR.Texture.CommonBuffer ) ;
	GANDR.Texture.CommonBuffer     = NULL ;
	GANDR.Texture.CommonBufferSize = 0 ;

	// �e�ʂ�ǉ�����
	Size += 512 * 1024 ;

	// �������̊m��
	GANDR.Texture.CommonBuffer = DXALLOC( Size ) ;
	if( GANDR.Texture.CommonBuffer == NULL )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\x6b\x30\x3b\x75\xcf\x50\x92\x30\xe2\x8e\x01\x90\x59\x30\x8b\x30\x5f\x30\x81\x30\x6e\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x5b\x00\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x44\x00\x33\x00\x44\x00\x31\x00\x31\x00\x5f\x00\x54\x00\x65\x00\x78\x00\x74\x00\x75\x00\x72\x00\x65\x00\x5f\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x43\x00\x6f\x00\x6d\x00\x6d\x00\x6f\x00\x6e\x00\x42\x00\x75\x00\x66\x00\x66\x00\x65\x00\x72\x00\x5d\x00\x0a\x00\x00"/*@ L"�e�N�X�`���ɉ摜��]�����邽�߂̃������̊m�ۂɎ��s���܂���[Graphics_Android_Texture_SetupCommonBuffer]\n" @*/ )) ;
		return -1 ;
	}

	// �m�ۂ����������̃T�C�Y��ۑ�
	GANDR.Texture.CommonBufferSize = Size ;

	// �I��
	return 0 ;
}

// �e�N�X�`���摜�]���p�̋��L�������̌�n�����s��
extern int Graphics_Android_Texture_TerminateCommonBuffer( void )
{
	// ���������m�ۂ��Ă�������
	if( GANDR.Texture.CommonBuffer != NULL )
	{
		DXFREE( GANDR.Texture.CommonBuffer ) ;
		GANDR.Texture.CommonBuffer = NULL ;
	}
	GANDR.Texture.CommonBufferSize = 0 ;

	// �I��
	return 0 ;
}

// �����_�[�^�[�Q�b�g�e�N�X�`���Ƀe�N�X�`���̒P���]�����s��
extern int		Graphics_Android_StretchRect(
	GLuint					SrcTexture,			uint32_t SrcTextureWidth,   uint32_t SrcTextureHeight,   const RECT *SrcRect,	// NULL �őS��
	GLuint					FrameBuffer,		uint32_t FrameBufferWidth,  uint32_t FrameBufferHeight,  const RECT *DestRect,	// NULL �őS��
	GLenum					FilterType,
	int						AlphaBlend,
	GRAPHICS_ANDROID_SHADER	*Shader,
	GLuint					BlendTexture,		uint32_t BlendTextureWidth, uint32_t BlendTextureHeight, const RECT *BlendRect,	// NULL �őS��
	VERTEX_TEX8_2D *		Texcoord8Vertex
)
{
	float *VertexDataP ;
	float VertexData[ 4 * 18 ] ;
	uint32_t	SrcTexWidth ;
	uint32_t	SrcTexHeight ;
	uint32_t	DestTexWidth ;
	uint32_t	DestTexHeight ;
	RECTF		SrcRectF ;
	RECTF		DestRectF ;
	RECTF		BlendRectF = { 0.0f } ;
	RECT		SrcRectTemp ;
	RECT		DestRectTemp ;
	RECT		BlendRectTemp ;
	int			BlendMode ;
	int			NotWriteAlphaChannelFlag ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �e�N�X�`�������擾
	SrcTexWidth  = SrcTextureWidth ;
	SrcTexHeight = SrcTextureHeight ;
	DestTexWidth  = FrameBufferWidth ;
	DestTexHeight = FrameBufferHeight ;

	if( SrcRect == NULL )
	{
		SrcRectTemp.left   = 0 ;
		SrcRectTemp.top    = 0 ;
		SrcRectTemp.right  = ( LONG )SrcTexWidth ;
		SrcRectTemp.bottom = ( LONG )SrcTexHeight ;

		SrcRect = &SrcRectTemp ;
	}

	if( DestRect == NULL )
	{
		DestRectTemp.left   = 0 ;
		DestRectTemp.top    = 0 ;
		DestRectTemp.right  = ( LONG )DestTexWidth ;
		DestRectTemp.bottom = ( LONG )DestTexHeight ;

		DestRect = &DestRectTemp ;
	}

	// ���_�����o��
	DRAWSTOCKINFO

	// �`��I��
	Graphics_Android_RenderEnd() ;

	// ���_�f�[�^������
	if( Texcoord8Vertex == NULL )
	{
		DestRectF.left   = ( float )DestRect->left   / DestTexWidth  * 2.0f - 1.0f ;
		DestRectF.top    = ( float )DestRect->top    / DestTexHeight * 2.0f - 1.0f ;
		DestRectF.right  = ( float )DestRect->right  / DestTexWidth  * 2.0f - 1.0f ;
		DestRectF.bottom = ( float )DestRect->bottom / DestTexHeight * 2.0f - 1.0f ;

		SrcRectF.left    = ( float )SrcRect->left    / SrcTexWidth ;
		SrcRectF.top     = ( float )SrcRect->top     / SrcTexHeight ;
		SrcRectF.right   = ( float )SrcRect->right   / SrcTexWidth ;
		SrcRectF.bottom  = ( float )SrcRect->bottom  / SrcTexHeight ;

		if( BlendTexture != 0 )
		{
			if( BlendRect == NULL )
			{
				BlendRectTemp.left   = 0 ;
				BlendRectTemp.top    = 0 ;
				BlendRectTemp.right  = ( LONG )BlendTextureWidth ;
				BlendRectTemp.bottom = ( LONG )BlendTextureHeight ;

				BlendRect = &BlendRectTemp ;
			}

			BlendRectF.left    = ( float )BlendRect->left    / BlendTextureWidth ;
			BlendRectF.top     = ( float )BlendRect->top     / BlendTextureHeight ;
			BlendRectF.right   = ( float )BlendRect->right   / BlendTextureWidth ;
			BlendRectF.bottom  = ( float )BlendRect->bottom  / BlendTextureHeight ;
		}

		// ���_�f�[�^���Z�b�g
		VertexDataP = VertexData ;

		VertexDataP[ 0 ] = DestRectF.left ;
		VertexDataP[ 1 ] = DestRectF.top ;
		VertexDataP[ 2 ] = SrcRectF.left ;
		VertexDataP[ 3 ] = SrcRectF.top ;
		VertexDataP += 4 ;
		if( BlendTexture != 0 )
		{
			VertexDataP[ 0 ] = BlendRectF.left ;
			VertexDataP[ 1 ] = BlendRectF.top ;
			VertexDataP += 2 ;
		}

		VertexDataP[ 0 ] = DestRectF.right ;
		VertexDataP[ 1 ] = DestRectF.top ;
		VertexDataP[ 2 ] = SrcRectF.right ;
		VertexDataP[ 3 ] = SrcRectF.top ;
		VertexDataP += 4 ;
		if( BlendTexture != 0 )
		{
			VertexDataP[ 0 ] = BlendRectF.right ;
			VertexDataP[ 1 ] = BlendRectF.top ;
			VertexDataP += 2 ;
		}

		VertexDataP[ 0 ] = DestRectF.left ;
		VertexDataP[ 1 ] = DestRectF.bottom ;
		VertexDataP[ 2 ] = SrcRectF.left ;
		VertexDataP[ 3 ] = SrcRectF.bottom ;
		VertexDataP += 4 ;
		if( BlendTexture != 0 )
		{
			VertexDataP[ 0 ] = BlendRectF.left ;
			VertexDataP[ 1 ] = BlendRectF.bottom ;
			VertexDataP += 2 ;
		}

		VertexDataP[ 0 ] = DestRectF.right ;
		VertexDataP[ 1 ] = DestRectF.bottom ;
		VertexDataP[ 2 ] = SrcRectF.right ;
		VertexDataP[ 3 ] = SrcRectF.bottom ;
		VertexDataP += 4 ;
		if( BlendTexture != 0 )
		{
			VertexDataP[ 0 ] = BlendRectF.right ;
			VertexDataP[ 1 ] = BlendRectF.bottom ;
			VertexDataP += 2 ;
		}
	}
	else
	{
		int i ;

		// ���_�f�[�^���Z�b�g
		VertexDataP = VertexData ;

		for( i = 0 ; i < 4 ; i ++ )
		{
			VertexDataP[  0 ] = Texcoord8Vertex[ i ].pos.x / DestTexWidth  * 2.0f - 1.0f ;
			VertexDataP[  1 ] = Texcoord8Vertex[ i ].pos.y / DestTexHeight * 2.0f - 1.0f ;

			VertexDataP[  2 ] = Texcoord8Vertex[ i ].u0 ;
			VertexDataP[  3 ] = Texcoord8Vertex[ i ].v0 ;
			VertexDataP[  4 ] = Texcoord8Vertex[ i ].u1 ;
			VertexDataP[  5 ] = Texcoord8Vertex[ i ].v1 ;
			VertexDataP[  6 ] = Texcoord8Vertex[ i ].u2 ;
			VertexDataP[  7 ] = Texcoord8Vertex[ i ].v2 ;
			VertexDataP[  8 ] = Texcoord8Vertex[ i ].u3 ;
			VertexDataP[  9 ] = Texcoord8Vertex[ i ].v3 ;
			VertexDataP[ 10 ] = Texcoord8Vertex[ i ].u4 ;
			VertexDataP[ 11 ] = Texcoord8Vertex[ i ].v4 ;
			VertexDataP[ 12 ] = Texcoord8Vertex[ i ].u5 ;
			VertexDataP[ 13 ] = Texcoord8Vertex[ i ].v5 ;
			VertexDataP[ 14 ] = Texcoord8Vertex[ i ].u6 ;
			VertexDataP[ 15 ] = Texcoord8Vertex[ i ].v6 ;
			VertexDataP[ 16 ] = Texcoord8Vertex[ i ].u7 ;
			VertexDataP[ 17 ] = Texcoord8Vertex[ i ].v7 ;

			VertexDataP += 18 ;
		}
	}

	// �`��̊J�n���s��
	Graphics_Android_RenderBegin() ;

	// StretchRect�p�̐ݒ���s��
	{
		// �`���̃t���[���o�b�t�@��ύX( �ݒ�� Graphics_Android_DeviceState_RefreshRenderState �Ŗ߂� )
		glBindFramebuffer( GL_FRAMEBUFFER, FrameBuffer ) ;

		// �r���[�|�[�g���Z�b�g( �ݒ�� Graphics_Android_DeviceState_RefreshRenderState �Ŗ߂� )
		glViewport( 0, 0, FrameBufferWidth, FrameBufferHeight ) ;

		// �V�F�[�_�[���Z�b�g
		if( Shader == NULL )
		{
			Shader = &GANDR.Device.Shader.Base.StretchRect_Shader ;
		}
		Graphics_Android_DeviceState_SetShader( Shader, FALSE ) ;

		// Uniform �̍X�V
		Graphics_Android_DeviceState_UpdateShaderUniform( Shader, 0 ) ;

		// �e�N�X�`�����Z�b�g( �ݒ�� Graphics_Android_DeviceState_RefreshRenderState �Ŗ߂� )
		glActiveTexture( GL_TEXTURE0 ) ;
		glBindTexture( GL_TEXTURE_2D, SrcTexture ) ;

		// �e�N�X�`���t�B���^�����O�ݒ���s��
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterType ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterType ) ;

		// �u�����h�e�N�X�`�����Z�b�g
		if( BlendTexture != 0 )
		{
			// �e�N�X�`�����Z�b�g( �ݒ�� Graphics_Android_DeviceState_RefreshRenderState �Ŗ߂� )
			glActiveTexture( GL_TEXTURE1 ) ;
			glBindTexture( GL_TEXTURE_2D, BlendTexture ) ;

			// �e�N�X�`���t�B���^�����O�ݒ���s��
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterType ) ;
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterType ) ;
		}

		// �u�����h���[�h��ύX
		BlendMode = GANDR.Device.State.BlendMode ;
		NotWriteAlphaChannelFlag = GANDR.Device.State.NotWriteAlphaChannelFlag ;
		Graphics_Android_DeviceState_SetBlendMode( AlphaBlend ? DX_BLENDMODE_ALPHA : DX_BLENDMODE_NOBLEND, FALSE ) ;

		// ���_�f�[�^�̃Z�b�g�A�b�v
		Graphics_Android_DeviceState_SetupShaderVertexData(
			Shader,
			Texcoord8Vertex != NULL ? &g_StretchRectTex8VertexInputInfo : ( BlendTexture != 0 ? &g_StretchRectTex2VertexInputInfo : &g_StretchRectVertexInputInfo ),
			VertexData
		) ;
	}

	// �`��
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 ) ;
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	// �ݒ�����ɖ߂�
	{
		// �u�����h���[�h��ύX
		Graphics_Android_DeviceState_SetBlendMode( BlendMode, NotWriteAlphaChannelFlag ) ;

		// ���܂ł̐ݒ�𕜋A����
		Graphics_Android_DeviceState_RefreshRenderState() ;
	}

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// ����I��
	return 0 ;
}

// �w��̃e�N�X�`���̓��e�ɓǂݍ��݃A�N�Z�X�ł���悤�ɂ���
extern	int		Graphics_Android_Texture_Map(
	GLuint				TargetTexture,
	GLuint				TargetFrameBuffer,
	GLuint				TargetWidth,
	GLuint				TargetHeight,
	const RECT *		MapRect /* NULL �őS�� */,
	BASEIMAGE *			MapBaseImage,
	void **				MapTempImage
)
{
	GLuint Width ;
	GLuint Height ;
	RECT   TempRect ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( MapRect == NULL )
	{
		TempRect.left   = 0 ;
		TempRect.top    = 0 ;
		TempRect.right  = ( LONG )TargetWidth ;
		TempRect.bottom = ( LONG )TargetHeight ;
		MapRect         = &TempRect ;
	}

	// �G���[�`�F�b�N
	if( MapRect->left >= MapRect->right ||
		MapRect->top  >= MapRect->bottom ||
		MapRect->left   < 0 ||
		MapRect->top    < 0 ||
		MapRect->right  > ( int )TargetWidth ||
		MapRect->bottom > ( int )TargetHeight )
	{
		return -1 ;
	}

	Width  = ( GLuint )( MapRect->right  - MapRect->left ) ;
	Height = ( GLuint )( MapRect->bottom - MapRect->top ) ;

	// �C���[�W�f�[�^��ۑ����郁�����̈�̊m��
	*MapTempImage = DXALLOC( Width * Height * 4 * 2 ) ;
	if( *MapTempImage == NULL )
	{
		return -1 ;
	}

	// �e�N�X�`���̏ꍇ�̓t���[���o�b�t�@�ɏ����o��
	if( TargetFrameBuffer == 0 )
	{
		GLuint TempFrameBuffer = 0 ;
		GLuint TempTexture = 0 ;

		// ��Ɨp�e�N�X�`���̍쐬
		glGenTextures( 1, &TempTexture ) ;
		glBindTexture( GL_TEXTURE_2D, TempTexture ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ) ;
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0 ) ;

		// ��Ɨp�t���[���o�b�t�@�̍쐬
		glGenFramebuffers( 1, &TempFrameBuffer );
		glBindFramebuffer( GL_FRAMEBUFFER, TempFrameBuffer );
		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TempTexture, 0 ) ;
		if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )   
		{
			DXFREE( *MapTempImage ) ;
			*MapTempImage = NULL ;
			return -1 ;
		}

		// ��Ɨp�t���[���o�b�t�@�Ƀe�N�X�`���̓��e��]��
		Graphics_Android_StretchRect( TargetTexture, TargetWidth, TargetHeight, MapRect, TempFrameBuffer, Width, Height, NULL ) ;

		// �s�N�Z���f�[�^�̓ǂݎ��
		glBindFramebuffer( GL_FRAMEBUFFER, TempFrameBuffer ) ;
		glReadPixels( 0, 0, Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, *MapTempImage ) ;
		glBindFramebuffer( GL_FRAMEBUFFER, GANDR.Device.State.TargetFrameBuffer ) ;

		// �t���[���o�b�t�@�ƃe�N�X�`���̍폜
		glBindTexture( GL_TEXTURE_2D, 0 ) ;
		glDeleteTextures( 1, &TempTexture ) ;
		glDeleteFramebuffers( 1, &TempFrameBuffer ) ;
	}
	else
	{
//		GLint ext_format, ext_type ;
//		glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &ext_format);
//		glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, &ext_type);

// �e�X�g�R�[�h
//#ifdef _DEBUG
//		_MEMSET( *MapTempImage, 0xff, Width * Height * 2 * 4 ) ;
//#endif

		// �s�N�Z���f�[�^�̓ǂݎ��
		glBindFramebuffer( GL_FRAMEBUFFER, TargetFrameBuffer ) ;

		GLint pack_backup, unpack_backup ;
		glGetIntegerv( GL_PACK_ALIGNMENT,   &pack_backup ) ;
		glGetIntegerv( GL_UNPACK_ALIGNMENT, &unpack_backup ) ;
		glPixelStorei( GL_PACK_ALIGNMENT,   1 ) ;
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ) ;
		glReadPixels( ( GLuint )MapRect->left, ( GLuint )MapRect->top, Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, *MapTempImage ) ;
		glPixelStorei( GL_PACK_ALIGNMENT,   pack_backup ) ;
		glPixelStorei( GL_UNPACK_ALIGNMENT, unpack_backup ) ;

		glBindFramebuffer( GL_FRAMEBUFFER, GANDR.Device.State.TargetFrameBuffer ) ;

// �e�X�g�R�[�h
//#ifdef _DEBUG
//		int kk ;
//		for( kk = Width * Height * 2 * 4 - 1 ; kk >= 0; kk -- )
//		{
//			if( ( ( BYTE * )*MapTempImage )[ kk ] != 0xff )
//			{
//				break ;
//			}
//		}
//		if( kk >= Width * Height * 4 )
//		{
//			kk = 0 ;
//		}
//#endif
	}

	// ��{�C���[�W�\���̂̃f�[�^�ɃZ�b�g
	MapBaseImage->ColorData      = *Graphics_Android_GetDataFormatColorData( ANDROID_PIXEL_FORMAT_R8G8B8A8 ) ;
	MapBaseImage->Width          = ( int )Width ;
	MapBaseImage->Height         = ( int )Height ;
	MapBaseImage->Pitch          = Width * 4 ;
	MapBaseImage->GraphData      = ( BYTE * )*MapTempImage ;
	MapBaseImage->MipMapCount    = 0 ;
	MapBaseImage->GraphDataCount = 0 ;

	// ����I��
	return 0 ;
}

// �w��̃e�N�X�`���̓��e�ւ̓ǂݍ��݃A�N�Z�X���I������
extern	int		Graphics_Android_Texture_Unmap( void * MapTempImage )
{
	// �������̉��
	if( MapTempImage != NULL )
	{
		DXFREE( MapTempImage ) ;
		MapTempImage = NULL ;
	}

	// �I��
	return 0 ;
}












































// AndroidDevice �̏������֌W

// �f�o�C�X�̍쐬�ɑ������鏈�����s��( 0:����  -1:���s )
extern	int		Graphics_Android_Device_Create( void )
{
	// OpenGL ES �� EGL �̏�����

	// �ړI�̍\���̑����������Ŏw�肵�܂��B
	// �ȉ��ŁA�I���X�N���[�� �E�B���h�E��
	// �݊����̂���A�e�F�Œ� 8 �r�b�g�̃R���|�[�l���g�� EGLConfig ��I�����܂�
	EGLint format ;
	EGLint numConfigs ;
	EGLConfig config ;
	EGLint Major, Minor ;

	EGLint attribs[] = 
	{
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	} ;
	EGLint context_attribs[] = 
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	} ;

	GANDR.Device.Screen.Display = eglGetDisplay( EGL_DEFAULT_DISPLAY ) ;

	// �\�t�g�E�F�A�n�� 16bit��ʃ��[�h�̏ꍇ�� R5G6B5 �ɂ���
	if( ( GSYS.Screen.UserScreenImage != NULL &&
		  ( GSYS.Screen.UserScreenImagePixelFormat == DX_USER_SCREEN_PIXEL_FORMAT_R5G6B5 ||
		    GSYS.Screen.UserScreenImagePixelFormat == DX_USER_SCREEN_PIXEL_FORMAT_R5G5B5X1 ||
		    GSYS.Screen.UserScreenImagePixelFormat == DX_USER_SCREEN_PIXEL_FORMAT_X1R5G5B5 ) ) ||
		( GSYS.Setting.NotUseHardware && GSYS.Screen.MainScreenColorBitDepth == 16 ) )
	{
		attribs[ 2 * 1 + 1 ] = 5 ;
		attribs[ 2 * 2 + 1 ] = 6 ;
		attribs[ 2 * 3 + 1 ] = 5 ;
	}

	// EGL ��������
	Major = 0 ;
	Minor = 0 ;
	eglInitialize(      GANDR.Device.Screen.Display, &Major, &Minor ) ;
	eglChooseConfig(    GANDR.Device.Screen.Display, attribs, &config, 1, &numConfigs ) ;
	eglGetConfigAttrib( GANDR.Device.Screen.Display, config, EGL_NATIVE_VISUAL_ID, &format ) ;

	ANativeWindow_setBuffersGeometry( ( ANativeWindow * )g_AndroidSys.NativeWindow, 0, 0, format ) ;

	GANDR.Device.Screen.Surface = eglCreateWindowSurface( GANDR.Device.Screen.Display, config, ( ANativeWindow * )g_AndroidSys.NativeWindow, NULL ) ;
	GANDR.Device.Screen.Context = eglCreateContext(       GANDR.Device.Screen.Display, config, EGL_NO_CONTEXT, context_attribs ) ;

	if( eglMakeCurrent( GANDR.Device.Screen.Display, GANDR.Device.Screen.Surface, GANDR.Device.Screen.Surface, GANDR.Device.Screen.Context ) == EGL_FALSE )
	{
		DXST_LOGFILE_ADDUTF16LE( "\x65\x00\x67\x00\x6c\x00\x4d\x00\x61\x00\x6b\x00\x65\x00\x43\x00\x75\x00\x72\x00\x72\x00\x65\x00\x6e\x00\x74\x00\x20\x00\x4c\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"eglMakeCurrent �����s���܂���\n" @*/ ) ;
		return -1 ;
	}

	// ��ʃT�C�Y�擾
	if( g_AndroidSys.NativeWindow == NULL )
	{
		eglQuerySurface( GANDR.Device.Screen.Display, GANDR.Device.Screen.Surface, EGL_WIDTH,  &GANDR.Device.Screen.Width ) ;
		eglQuerySurface( GANDR.Device.Screen.Display, GANDR.Device.Screen.Surface, EGL_HEIGHT, &GANDR.Device.Screen.Height ) ;
	}
	else
	{
		GANDR.Device.Screen.Width = ANativeWindow_getWidth( ( ANativeWindow * )g_AndroidSys.NativeWindow ) ;
		GANDR.Device.Screen.Height = ANativeWindow_getHeight( ( ANativeWindow * )g_AndroidSys.NativeWindow ) ;
	}
	DXST_LOGFILEFMT_ADDUTF16LE(( "\xb9\x30\xaf\x30\xea\x30\xfc\x30\xf3\x30\xb5\x30\xa4\x30\xba\x30\x3a\x00\x25\x00\x64\x00\x20\x00\x78\x00\x20\x00\x25\x00\x64\x00\x00"/*@ L"�X�N���[���T�C�Y:%d x %d" @*/, GANDR.Device.Screen.Width, GANDR.Device.Screen.Height )) ;

	if( GSYS.Screen.NotWaitVSyncFlag )
	{
		eglSwapInterval( GANDR.Device.Screen.Display, 0 ) ;
	}

	// �o�[�W������x���_�[�����擾
	{
		const GLubyte *Version					= glGetString( GL_VERSION ) ;
		const GLubyte *Renderer					= glGetString( GL_RENDERER ) ;
		const GLubyte *Vendor					= glGetString( GL_VENDOR ) ;
		const GLubyte *Shading_Language_Version	= glGetString( GL_SHADING_LANGUAGE_VERSION ) ;
		char TempStr[ 1024 ] ;
		int Length ;

		if( Version != NULL )
		{
			Length = CL_strlen( DX_CHARCODEFORMAT_ASCII, ( char * )Version ) ;
			GANDR.Device.Caps.Version = ( TCHAR * )DXALLOC( sizeof( TCHAR ) * ( Length + 1 ) ) ;
			ConvString( ( char * )Version, -1, DX_CHARCODEFORMAT_ASCII, GANDR.Device.Caps.Version, sizeof( TCHAR ) * ( Length + 1 ), _TCHARCODEFORMAT ) ;
			if( ( DWORD )( Length * 4 + 2 )  < sizeof( TempStr ) )
			{
				ConvString( ( char * )Version, -1, DX_CHARCODEFORMAT_ASCII, TempStr, sizeof( TempStr ), DX_CHARCODEFORMAT_UTF16LE ) ;
				DXST_LOGFILEFMT_ADDUTF16LE(( "\xd0\x30\xfc\x30\xb8\x30\xe7\x30\xf3\x30\x3a\x00\x25\x00\x73\x00\x00"/*@ L"�o�[�W����:%s" @*/, TempStr )) ;
			}
		}

		if( Renderer != NULL )
		{
			Length = CL_strlen( DX_CHARCODEFORMAT_ASCII, ( char * )Renderer ) ;
			GANDR.Device.Caps.Renderer = ( TCHAR * )DXALLOC( sizeof( TCHAR ) * ( Length + 1 ) ) ;
			ConvString( ( char * )Renderer, -1, DX_CHARCODEFORMAT_ASCII, GANDR.Device.Caps.Renderer, sizeof( TCHAR ) * ( Length + 1 ), _TCHARCODEFORMAT ) ;
			if( ( DWORD )( Length * 4 + 2 ) < sizeof( TempStr ) )
			{
				ConvString( ( char * )Renderer, -1, DX_CHARCODEFORMAT_ASCII, TempStr, sizeof( TempStr ), DX_CHARCODEFORMAT_UTF16LE ) ;
				DXST_LOGFILEFMT_ADDUTF16LE(( "\xec\x30\xf3\x30\xc0\x30\xe9\x30\xfc\x30\x3a\x00\x25\x00\x73\x00\x00"/*@ L"�����_���[:%s" @*/, TempStr )) ;
			}
		}

		if( Vendor != NULL )
		{
			Length = CL_strlen( DX_CHARCODEFORMAT_ASCII, ( char * )Vendor ) ;
			GANDR.Device.Caps.Vendor = ( TCHAR * )DXALLOC( sizeof( TCHAR ) * ( Length + 1 ) ) ;
			ConvString( ( char * )Vendor, -1, DX_CHARCODEFORMAT_ASCII, GANDR.Device.Caps.Vendor, sizeof( TCHAR ) * ( Length + 1 ), _TCHARCODEFORMAT ) ;
			if( ( DWORD )( Length * 4 + 2 ) < sizeof( TempStr ) )
			{
				ConvString( ( char * )Vendor, -1, DX_CHARCODEFORMAT_ASCII, TempStr, sizeof( TempStr ), DX_CHARCODEFORMAT_UTF16LE ) ;
				DXST_LOGFILEFMT_ADDUTF16LE(( "\xd9\x30\xf3\x30\xc0\x30\xfc\x30\x3a\x00\x25\x00\x73\x00\x00"/*@ L"�x���_�[:%s" @*/, TempStr )) ;
			}
		}

		if( Shading_Language_Version != NULL )
		{
			Length = CL_strlen( DX_CHARCODEFORMAT_ASCII, ( char * )Shading_Language_Version ) ;
			GANDR.Device.Caps.Shading_Language_Version = ( TCHAR * )DXALLOC( sizeof( TCHAR ) * ( Length + 1 ) ) ;
			ConvString( ( char * )Shading_Language_Version, -1, DX_CHARCODEFORMAT_ASCII, GANDR.Device.Caps.Shading_Language_Version, sizeof( TCHAR ) * ( Length + 1 ), _TCHARCODEFORMAT ) ;
			if( ( DWORD )( Length * 4 + 2 ) < sizeof( TempStr ) )
			{
				ConvString( ( char * )Shading_Language_Version, -1, DX_CHARCODEFORMAT_ASCII, TempStr, sizeof( TempStr ), DX_CHARCODEFORMAT_UTF16LE ) ;
				DXST_LOGFILEFMT_ADDUTF16LE(( "\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x00\x8a\x9e\x8a\xd0\x30\xfc\x30\xb8\x30\xe7\x30\xf3\x30\x3a\x00\x25\x00\x73\x00\x00"/*@ L"�V�F�[�_�[����o�[�W����:%s" @*/, TempStr )) ;
			}
		}
	}

	// Extensions ���
	{
		const GLubyte *lExtensions = glGetString( GL_EXTENSIONS );
		const GLubyte *lExtensionsTemp ;
		int i ;
		int j ;
		int k ;
		int l ;

		DXST_LOGFILE_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x47\x00\x4c\x00\x20\x00\x45\x00\x53\x00\x20\x00\x45\x00\x78\x00\x74\x00\x65\x00\x6e\x00\x73\x00\x69\x00\x6f\x00\x6e\x00\x73\x00\x20\x00\x00\x4e\xa7\x89\x0a\x00\x00"/*@ L"OpenGL ES Extensions �ꗗ\n" @*/ )) ;

		_MEMSET( GANDR.Device.Caps.Extensions, 0, sizeof( GANDR.Device.Caps.Extensions ) ) ;

		GANDR.Device.Caps.ExtensionNum = 0 ;
		j = 0 ;
		lExtensionsTemp = lExtensions ;
		for(;;)
		{
			if( lExtensionsTemp[ j ] == '\0' )
			{
				break ;
			}

			// ���O�ɏo��
			{
				char lTempStr[ 256 ] ;
				for( i = 0 ; i < 230 && lExtensionsTemp[ j + i ] != '\0' && lExtensionsTemp[ j + i ] != ' '; i++ )
				{
					lTempStr[ i + 1 ] = lExtensionsTemp[ j + i ] ;
				}
				lTempStr[ 0 ]     = '\t' ;
				lTempStr[ i ]     = '\n' ;
				lTempStr[ i + 1 ] = '\0' ;
				DXST_LOGFILE_ADDA( lTempStr ) ;
			}

			for( i = 0; i < ANDROID_GL_EXTENSION_NUM; i++ )
			{
				k = 0 ;
				for(;;)
				{
					if( lExtensionsTemp[ j + k ] == '\0' || lExtensionsTemp[ j + k ] == ' ' )
					{
						break ;
					}

					if( g_AndroidGLExtensionName[ i ][ k ] == '\0' )
					{
						break ;
					}

					if( lExtensionsTemp[ j + k ] != g_AndroidGLExtensionName[ i ][ k ] )
					{
						break ;
					}

					k ++ ;
				}
				if( g_AndroidGLExtensionName[ i ][ k ] == '\0' &&
					( lExtensionsTemp[ j + k ] == ' ' || lExtensionsTemp[ j + k ] == '\0' ) )
				{
					GANDR.Device.Caps.Extensions[ i ] = TRUE ;
				}
			}
			GANDR.Device.Caps.ExtensionNum ++ ;

			for( ; lExtensionsTemp[ j ] != ' ' && lExtensionsTemp[ j ] != '\0'; j++ ){}
			if( lExtensionsTemp[ j ] == '\0' )
			{
				break;
			}
			j++ ;
		}

		GANDR.Device.Caps.ExtensionNames = ( TCHAR ** )DXALLOC( sizeof( TCHAR * ) * ( GANDR.Device.Caps.ExtensionNum + 1 ) ) ;
		j = 0 ;
		l = 0 ;
		lExtensionsTemp = lExtensions ;
		for(;;)
		{
			GLchar *TempBuffer ;

			if( lExtensionsTemp[ j ] == '\0' )
			{
				break ;
			}

			for( k = 0; lExtensionsTemp[ j + k ] != ' ' && lExtensionsTemp[ j + k ] != '\0'; k++ ){}
			TempBuffer = ( GLchar * )DXALLOC( sizeof( GLchar ) * ( k + 1 ) ) ;
			_MEMCPY( TempBuffer, &lExtensionsTemp[ j ], sizeof( GLchar ) * k ) ;
			TempBuffer[ k ] = 0 ;
			GANDR.Device.Caps.ExtensionNames[ l ] = ( TCHAR * )DXALLOC( sizeof( TCHAR ) * ( k + 1 ) ) ;
			ConvString( TempBuffer, -1, DX_CHARCODEFORMAT_ASCII, GANDR.Device.Caps.ExtensionNames[ l ], sizeof( TCHAR ) * ( k + 1 ), _TCHARCODEFORMAT ) ;
			l ++ ;
			DXFREE( TempBuffer ) ;
			TempBuffer = NULL ;

			j += k ;
			if( lExtensionsTemp[ j ] == '\0' )
			{
				break;
			}

			j++ ;
		}
		GANDR.Device.Caps.ExtensionNames[ l ] = NULL ;
	}

	// �V�F�[�_�[�֌W�̔\�͎擾
	glGetIntegerv( GL_MAX_VERTEX_ATTRIBS,									&GANDR.Device.Caps.Shader_Max_Vertex_Attribs ) ;
	DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x61\x00\x78\x00\x20\x00\x56\x00\x65\x00\x72\x00\x74\x00\x65\x00\x78\x00\x20\x00\x41\x00\x74\x00\x74\x00\x72\x00\x69\x00\x62\x00\x73\x00\x1a\xff\x25\x00\x64\x00\x00"/*@ L"Max Vertex Attribs�F%d" @*/,				 GANDR.Device.Caps.Shader_Max_Vertex_Attribs )) ;
	glGetIntegerv( GL_MAX_VERTEX_UNIFORM_VECTORS,							&GANDR.Device.Caps.Shader_Max_Vertex_Uniform_Vectors ) ;
	DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x61\x00\x78\x00\x20\x00\x56\x00\x65\x00\x72\x00\x74\x00\x65\x00\x78\x00\x20\x00\x55\x00\x6e\x00\x69\x00\x66\x00\x6f\x00\x72\x00\x6d\x00\x20\x00\x56\x00\x65\x00\x63\x00\x74\x00\x6f\x00\x72\x00\x73\x00\x1a\xff\x25\x00\x64\x00\x00"/*@ L"Max Vertex Uniform Vectors�F%d" @*/,		 GANDR.Device.Caps.Shader_Max_Vertex_Uniform_Vectors )) ;
	glGetIntegerv( GL_MAX_VARYING_VECTORS,									&GANDR.Device.Caps.Shader_Max_Varying_Vectors ) ;
	DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x61\x00\x78\x00\x20\x00\x56\x00\x61\x00\x72\x00\x79\x00\x69\x00\x6e\x00\x67\x00\x20\x00\x56\x00\x65\x00\x63\x00\x74\x00\x6f\x00\x72\x00\x73\x00\x1a\xff\x25\x00\x64\x00\x00"/*@ L"Max Varying Vectors�F%d" @*/,				 GANDR.Device.Caps.Shader_Max_Varying_Vectors )) ;
	glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,						&GANDR.Device.Caps.Shader_Max_Combined_Texture_Image_Units ) ;
	DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x61\x00\x78\x00\x20\x00\x43\x00\x6f\x00\x6d\x00\x62\x00\x69\x00\x6e\x00\x65\x00\x64\x00\x20\x00\x54\x00\x65\x00\x78\x00\x74\x00\x75\x00\x72\x00\x65\x00\x20\x00\x49\x00\x6d\x00\x61\x00\x67\x00\x65\x00\x20\x00\x55\x00\x6e\x00\x69\x00\x74\x00\x73\x00\x1a\xff\x25\x00\x64\x00\x00"/*@ L"Max Combined Texture Image Units�F%d" @*/,	 GANDR.Device.Caps.Shader_Max_Combined_Texture_Image_Units )) ;
	glGetIntegerv( GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,						&GANDR.Device.Caps.Shader_Max_Vertex_Texture_Image_Units ) ;
	DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x61\x00\x78\x00\x20\x00\x56\x00\x65\x00\x72\x00\x74\x00\x65\x00\x78\x00\x20\x00\x54\x00\x65\x00\x78\x00\x74\x00\x75\x00\x72\x00\x65\x00\x20\x00\x49\x00\x6d\x00\x61\x00\x67\x00\x65\x00\x20\x00\x55\x00\x6e\x00\x69\x00\x74\x00\x73\x00\x1a\xff\x25\x00\x64\x00\x00"/*@ L"Max Vertex Texture Image Units�F%d" @*/,	 GANDR.Device.Caps.Shader_Max_Vertex_Texture_Image_Units )) ;
	glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS,								&GANDR.Device.Caps.Shader_Max_Texture_Image_Units ) ;
	DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x61\x00\x78\x00\x20\x00\x54\x00\x65\x00\x78\x00\x74\x00\x75\x00\x72\x00\x65\x00\x20\x00\x49\x00\x6d\x00\x61\x00\x67\x00\x65\x00\x20\x00\x55\x00\x6e\x00\x69\x00\x74\x00\x73\x00\x1a\xff\x25\x00\x64\x00\x00"/*@ L"Max Texture Image Units�F%d" @*/,			 GANDR.Device.Caps.Shader_Max_Texture_Image_Units )) ;
	glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_VECTORS,							&GANDR.Device.Caps.Shader_Max_Fragment_Uniform_Vectors ) ;	
	DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x61\x00\x78\x00\x20\x00\x46\x00\x72\x00\x61\x00\x67\x00\x6d\x00\x65\x00\x6e\x00\x74\x00\x20\x00\x55\x00\x6e\x00\x69\x00\x66\x00\x6f\x00\x72\x00\x6d\x00\x20\x00\x56\x00\x65\x00\x63\x00\x74\x00\x6f\x00\x72\x00\x73\x00\x1a\xff\x25\x00\x64\x00\x00"/*@ L"Max Fragment Uniform Vectors�F%d" @*/,		 GANDR.Device.Caps.Shader_Max_Fragment_Uniform_Vectors )) ;

	// RGB�̃u�����h�ݒ�Ƃ͕ʂɃA���t�@�`�����l���̃u�����h�ݒ肪�s����
	GSYS.HardInfo.SeparateAlphaBlendEnable = TRUE ;

	// ���Z�u�����h���\���ǂ������Z�b�g����
	GSYS.HardInfo.ValidSubBlend = TRUE ;

	// ��ʂ̂x�����㉺����
	GSYS.HardInfo.ScreenAxisYReverse = TRUE ;

	// DxLib_Init �ďo����ł� SetWaitVSyncFlag �̌Ăяo���ɑΉ�
	GSYS.HardInfo.UseOfSetWaitVSyncFlagIsSupportedEvenAfterDxLib_Init = TRUE ;

	// ��ʃ��[�h�̕ύX�ł̓T�u�o�b�N�o�b�t�@�̕ύX�̂ݍs���悤�ɂ���
	GSYS.HardInfo.ChangeGraphModeOnlyChangeSubBackbuffer = TRUE ;

	// �e�N�X�`���������`�ł���K�v�����邩�ǂ������擾����
	GSYS.HardInfo.TextureSquareOnly = FALSE ;

	// ��x�Ɏg�p���邱�Ƃ̏o����ő咸�_�����擾����
	GSYS.HardInfo.MaxVertexIndex = 0xffff ;

	// ���_���W�^�C�v�� DX_DRAWFLOATCOORDTYPE_DIRECT3D10
	GSYS.HardInfo.DrawFloatCoordType = DX_DRAWFLOATCOORDTYPE_DIRECT3D10 ;

	// �����Ƀ����_�����O�ł���^�[�Q�b�g�̐���ۑ�
	GSYS.HardInfo.RenderTargetNum = 8 ;

	// �e�N�X�`���̍ő啝�ƍő卂����ۑ�����
	{
		GLint MaxTextureSize ;

		glGetIntegerv( GL_MAX_TEXTURE_SIZE, &MaxTextureSize ) ;
		GSYS.HardInfo.MaxTextureWidth  = MaxTextureSize ;
		GSYS.HardInfo.MaxTextureHeight = MaxTextureSize ;
		GSYS.HardInfo.MaxTextureSize = MaxTextureSize ;
	}

	// �e�N�X�`���̃T�C�Y���Q�̂���ł���K�v�͖���
	GSYS.HardInfo.TextureSizePow2 = FALSE ;

	// �����t�Ńe�N�X�`���̃T�C�Y���Q�̂���ł͂Ȃ��Ă����v
	GSYS.HardInfo.TextureSizeNonPow2Conditional = TRUE ;

	// ���_�J���[��RGBA�J���[�^�C�v���g�p����
	GSYS.HardInfo.UseVertexColorBGRAFormat = FALSE ;

	// ��x�ɕ`��ł���ő�v���~�e�B�u�����擾����
	GSYS.HardInfo.MaxPrimitiveCount = 65536 ;

	// Graphics_Android_DrawPreparation ���s���ׂ��t���O�𗧂Ă�
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �e��t�H�[�}�b�g���Z�b�g
	{
		GANDR.Device.Caps.ScreenFormat = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;

		// �p���b�g�e�N�X�`���͖��Ή�
		if( FALSE )
//		if( GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_COMPRESSED_PALETTED_TEXTURE ] )
		{
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_PAL4                  ] = ANDROID_PIXEL_FORMAT_R8G8B8_PAL4 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_PAL8                  ] = ANDROID_PIXEL_FORMAT_R8G8B8_PAL8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHA_PAL4            ] = ANDROID_PIXEL_FORMAT_R8G8B8A8_PAL4 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHA_PAL8            ] = ANDROID_PIXEL_FORMAT_R8G8B8A8_PAL8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHATEST_PAL4        ] = ANDROID_PIXEL_FORMAT_A1B5G5R5_PAL4 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHATEST_PAL8        ] = ANDROID_PIXEL_FORMAT_A1B5G5R5_PAL8 ;
		}
		else
		{
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_PAL4                  ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_PAL8                  ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHA_PAL4            ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHA_PAL8            ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHATEST_PAL4        ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHATEST_PAL8        ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		}
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_RGB16                 ] = ANDROID_PIXEL_FORMAT_B5G6R5 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_RGB32                 ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHA_RGB16           ] = ANDROID_PIXEL_FORMAT_A4B4G4R4 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHA_RGB32           ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHATEST_RGB16       ] = ANDROID_PIXEL_FORMAT_A1B5G5R5 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ALPHATEST_RGB32       ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DXT1                  ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DXT2                  ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DXT3                  ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DXT4                  ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DXT5                  ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_BC7_UNORM             ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_BC7_UNORM_SRGB        ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_PLATFORM0             ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_PLATFORM1             ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_PLATFORM2             ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_PLATFORM3             ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ABGR_I16              ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;

		if( GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_TEXTURE_HALF_FLOAT ] || GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_TEXTURE_HALF_FLOAT_LINEAR ] )
		{
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ABGR_F16              ] = ANDROID_PIXEL_FORMAT_R16G16B16A16_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ONE_F16               ] = ANDROID_PIXEL_FORMAT_R16G16B16_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_TWO_F16               ] = ANDROID_PIXEL_FORMAT_R16G16B16_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ABGR_F16    ] = ANDROID_PIXEL_FORMAT_R16G16B16A16_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_F16     ] = ANDROID_PIXEL_FORMAT_R16G16B16_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_TWO_F16     ] = ANDROID_PIXEL_FORMAT_R16G16B16_FLOAT ;
		}
		else
		if( GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_TEXTURE_FLOAT ] || GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_TEXTURE_FLOAT_LINEAR ] )
		{
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ABGR_F16              ] = ANDROID_PIXEL_FORMAT_R32G32B32A32_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ONE_F16               ] = ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_TWO_F16               ] = ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ABGR_F16    ] = ANDROID_PIXEL_FORMAT_R32G32B32A32_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_F16     ] = ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_TWO_F16     ] = ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT ;
		}
		else
		{
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ABGR_F16              ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ONE_F16               ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_TWO_F16               ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ABGR_F16    ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_F16     ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_TWO_F16     ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		}

		if( GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_TEXTURE_FLOAT ] || GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_TEXTURE_FLOAT_LINEAR ] )
		{
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ABGR_F32              ] = ANDROID_PIXEL_FORMAT_R32G32B32A32_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ONE_F32               ] = ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_TWO_F32               ] = ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ABGR_F32    ] = ANDROID_PIXEL_FORMAT_R32G32B32A32_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_F32     ] = ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_TWO_F32     ] = ANDROID_PIXEL_FORMAT_R32G32B32_FLOAT ;
		}
		else
		{
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ABGR_F32              ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ONE_F32               ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_TWO_F32               ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ABGR_F32    ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_F32     ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
			GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_TWO_F32     ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		}

		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ONE_I8                ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_ONE_I16               ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_TWO_I8                ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_TWO_I16               ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_RGB16       ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_RGB32       ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ALPHA_RGB32 ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ABGR_I16    ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_I8      ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_I16     ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_TWO_I8      ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;
		GANDR.Device.Caps.TextureFormat[      DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_TWO_I16     ] = ANDROID_PIXEL_FORMAT_R8G8B8A8 ;

		GANDR.Device.Caps.MaskAlphaFormat = ANDROID_PIXEL_FORMAT_R8 ;
		GANDR.Device.Caps.DepthBufferFormat[ ZBUFFER_FORMAT_16BIT ] = GL_DEPTH_COMPONENT16 ;
		GANDR.Device.Caps.DepthBufferFormat[ ZBUFFER_FORMAT_24BIT ] = GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_DEPTH24 ] ? GL_DEPTH_COMPONENT24_OES : GL_DEPTH_COMPONENT16 ;
		GANDR.Device.Caps.DepthBufferFormat[ ZBUFFER_FORMAT_32BIT ] = GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_DEPTH32 ] ? GL_DEPTH_COMPONENT32_OES : ( GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_DEPTH24 ] ? GL_DEPTH_COMPONENT24_OES : GL_DEPTH_COMPONENT16 ) ;
	}

	// �J���[�t�H�[�}�b�g���̏��������s��
	Graphics_Android_GetDataFormatColorData( ANDROID_PIXEL_FORMAT_R8G8B8A8 ) ;

	// �T�u�o�b�N�o�b�t�@�̍쐬
	if( Graphics_Android_SetupSubBackBuffer() < 0 )
	{
		return -1 ;
	}

	// �I��
	return 0 ;
}

// �f�o�C�X�̔j���ɑ������鏈�����s��
extern	int		Graphics_Android_Device_Delete( void )
{
	// �T�u�o�b�N�o�b�t�@�֌W�̌�n��
	Graphics_Android_TerminateSubBackBuffer() ;

	if( GANDR.Device.Screen.Display != EGL_NO_DISPLAY ) 
	{
		eglMakeCurrent( GANDR.Device.Screen.Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT ) ;

		if( GANDR.Device.Screen.Context != EGL_NO_CONTEXT )
		{
			eglDestroyContext( GANDR.Device.Screen.Display, GANDR.Device.Screen.Context ) ;
		}

		if( GANDR.Device.Screen.Surface != EGL_NO_SURFACE )
		{
			eglDestroySurface( GANDR.Device.Screen.Display, GANDR.Device.Screen.Surface ) ;
		}

		eglTerminate( GANDR.Device.Screen.Display ) ;
	}

	g_AndroidSys.SoftThreadWait = 0 ;
	GANDR.Device.Screen.Display = EGL_NO_DISPLAY ;
	GANDR.Device.Screen.Context = EGL_NO_CONTEXT ;
	GANDR.Device.Screen.Surface = EGL_NO_SURFACE ;

	// �������̉��
	if( GANDR.Device.Caps.ExtensionNames != NULL )
	{
		int i ;

		for( i = 0 ; i < GANDR.Device.Caps.ExtensionNum ; i ++ )
		{
			if( GANDR.Device.Caps.ExtensionNames[ i ] != NULL )
			{
				DXFREE( GANDR.Device.Caps.ExtensionNames[ i ] ) ;
				GANDR.Device.Caps.ExtensionNames[ i ] = NULL ;
			}
		}
		DXFREE( GANDR.Device.Caps.ExtensionNames ) ;
		GANDR.Device.Caps.ExtensionNames = NULL ;
	}
	if( GANDR.Device.Caps.Version != NULL )
	{
		DXFREE( GANDR.Device.Caps.Version ) ;
		GANDR.Device.Caps.Version = NULL ;
	}
	if( GANDR.Device.Caps.Renderer != NULL )
	{
		DXFREE( GANDR.Device.Caps.Renderer ) ;
		GANDR.Device.Caps.Renderer = NULL ;
	}
	if( GANDR.Device.Caps.Vendor != NULL )
	{
		DXFREE( GANDR.Device.Caps.Vendor ) ;
		GANDR.Device.Caps.Vendor = NULL ;
	}
	if( GANDR.Device.Caps.Shading_Language_Version != NULL )
	{
		DXFREE( GANDR.Device.Caps.Shading_Language_Version ) ;
		GANDR.Device.Caps.Shading_Language_Version = NULL ;
	}

	// �f�o�C�X�Z�b�g����������
	_MEMSET( GANDR.Device.State.SetTexture, 0, sizeof( GANDR.Device.State.SetTexture ) ) ;
	GANDR.Device.State.SetNormalShader = FALSE ;
	GANDR.Device.State.SetShader = NULL ;
	GANDR.Device.State.SetShader_Force = NULL ;
	GANDR.Device.State.TargetFrameBuffer = 0 ;
	GANDR.Device.State.TargetFrameBufferWidth = 0 ;
	GANDR.Device.State.TargetFrameBufferHeight = 0 ;
	GANDR.Device.State.SetVertexBuffer = 0 ;

	return 0 ;
}

// Direct3DDevice11 �֌W�̏�����
extern	int		Graphics_Android_Device_Initialize( void )
{
	int i ;

#ifndef DX_NON_FILTER
	GraphFilter_Initialize() ;
#endif // DX_NON_FILTER

	// �`��X�e�[�^�X�̃Z�b�g
	{
		GANDR.Device.DrawSetting.CancelSettingEqualCheck = TRUE ;

		// �`����̏����l���Z�b�g
		{
			GANDR.Device.State.CullEnable		= FALSE ;
			GANDR.Device.State.CullFace			= GL_BACK ;
			GANDR.Device.State.DepthBias		= 0 ;

			GANDR.Device.State.DepthEnable		= FALSE ;
			GANDR.Device.State.DepthWriteEnable	= FALSE ;
			GANDR.Device.State.DepthFunc		= GL_LEQUAL ;

			GANDR.Device.State.BlendMode		= DX_BLENDMODE_NOBLEND ;

			for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
			{
				GANDR.Device.State.TexMagFilter[ i ]		= GL_NEAREST ;
				GANDR.Device.State.TexMinFilter[ i ]		= GL_NEAREST ;
				GANDR.Device.State.TexAddressModeU[ i ]		= GL_CLAMP_TO_EDGE ;
				GANDR.Device.State.TexAddressModeV[ i ]		= GL_CLAMP_TO_EDGE ;
				GANDR.Device.State.TexAddressModeW[ i ]		= GL_CLAMP_TO_EDGE ;
				GANDR.Device.State.MaxAnisotropyDim[ i ]	= 0 ;
			}
		}

		// �`�惂�[�h���Z�b�g
		Graphics_Android_DeviceState_SetDrawMode( DX_DRAWMODE_NEAREST ) ;

		// �ő�ٕ������Z�b�g
		Graphics_Android_DeviceState_SetMaxAnisotropy( 16 ) ;

		// �e�N�X�`�����W�ϊ��s����g�p���邩�ǂ����̐ݒ���Z�b�g
		Graphics_Android_DeviceState_SetTextureAddressTransformMatrix(
			FALSE,
			&ANDROID_GlobalIdentMatrix ) ;

		// ���C�e�B���O�n�m
		Graphics_Android_DeviceState_SetLighting( TRUE ) ;

		// �}�e���A���̃p�����[�^��ݒ�
		{
			MATERIALPARAM Material ;
			Material.Diffuse.r  = 0.8f ;
			Material.Diffuse.g  = 0.8f ;
			Material.Diffuse.b  = 0.8f ;
			Material.Diffuse.a  = 1.0f ;
			Material.Specular.r = 0.8f ;
			Material.Specular.g = 0.8f ;
			Material.Specular.b = 0.8f ;
			Material.Specular.a = 0.0f ;
			Material.Emissive.r = 0.0f ;
			Material.Emissive.g = 0.0f ;
			Material.Emissive.b = 0.0f ;
			Material.Emissive.a = 0.0f ;
			Material.Ambient.r  = 0.0f ;
			Material.Ambient.g  = 0.0f ;
			Material.Ambient.b  = 0.0f ;
			Material.Ambient.a  = 0.0f ;
			Material.Power      = 20.0f ;
			Graphics_Android_DeviceState_SetMaterial( &Material ) ;
		}

		// ���_�̃J���[�l���}�e���A���̃f�B�t���[�Y�J���[��X�y�L�����J���[�Ƃ��Ďg�p���邩�ǂ����̐ݒ��������
		Graphics_Android_DeviceState_SetUseVertexDiffuseColor( TRUE ) ;
		Graphics_Android_DeviceState_SetUseVertexSpecularColor( TRUE ) ;

		// �X�y�L�����������g�p���邩�ǂ�����������
		Graphics_Android_DeviceState_SetSpecularEnable( TRUE ) ;

		// �t�H�O�֌W�̐ݒ�
		Graphics_Android_DeviceState_SetFogEnable( FALSE ) ;
		Graphics_Android_DeviceState_SetFogColor( 0 ) ;
		Graphics_Android_DeviceState_SetFogVertexMode( DX_FOGMODE_NONE ) ;
		Graphics_Android_DeviceState_SetFogStartEnd( 0.0f, 1.0f ) ;
		Graphics_Android_DeviceState_SetFogDensity( 1.0f ) ;

		// �O���[�o���A���r�G���g�J���[�Z�b�g
		{
			COLOR_F GAmbColor = { 0.0f } ;

			Graphics_Android_DeviceState_SetAmbient( &GAmbColor ) ;
		}

		// �r���[�|�[�g��ݒ�
		{
			RECT Viewport ;

			Viewport.left		= 0 ;
			Viewport.top		= 0 ;
			Viewport.right		= ( float )GSYS.Screen.MainScreenSizeX ;
			Viewport.bottom		= ( float )GSYS.Screen.MainScreenSizeY ;
			Graphics_Android_DeviceState_SetViewport( &Viewport ) ;
		}

		// �`��摜�̂q�f�a�𖳎����邩�ǂ������Z�b�g
		Graphics_Android_DrawSetting_SetIgnoreDrawGraphColor( FALSE ) ;

		// �`��摜�̂`�𖳎����邩�ǂ������Z�b�g
		Graphics_Android_DrawSetting_SetIgnoreDrawGraphAlpha( FALSE ) ;

		// �`���̃A���t�@�`�����l���̓��e�����������邩��ݒ肷��
		Graphics_Android_DrawSetting_SetWriteAlphaChannelFlag( FALSE ) ;

		// �`���ݒ�
//		Graphics_Android_DeviceState_SetRenderTarget(
//			&GANDR.Device.Screen.DispBuffer[ GANDR.Device.Screen.BackBufferIndex ].RenderTarget
//		) ;

		// �u�����h���[�h�ݒ�
		Graphics_Android_DeviceState_SetBlendMode( DX_BLENDMODE_NOBLEND, FALSE ) ;

		// �A���t�@�e�X�g�ݒ��������
		Graphics_Android_DrawSetting_SetDrawAlphaTest( -1, 0 ) ;

		// �u�����h�e�N�X�`���֌W��������
		Graphics_Android_DrawSetting_SetBlendTexture( NULL ) ;
		GANDR.Device.DrawSetting.BlendGraphBorderParam	= -1 ;
		GANDR.Device.DrawSetting.BlendGraphType			= 0 ;

		// �`��e�N�X�`���֌W��������
		Graphics_Android_DrawSetting_SetTexture( NULL ) ;
		GANDR.Device.DrawSetting.AlphaChannelValidFlag	= FALSE ;
		GANDR.Device.DrawSetting.AlphaTestValidFlag		= FALSE ;

		GANDR.Device.DrawSetting.CancelSettingEqualCheck = FALSE ;
	}

	// �f�o�C�X�ݒ�����t���b�V��
	Graphics_Android_DeviceState_RefreshRenderState() ;

	// �t���O��������
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag		= TRUE ;
	GANDR.Device.DrawSetting.AlphaChannelValidFlag	= FALSE ;
	GANDR.Device.DrawSetting.AlphaTestValidFlag		= FALSE ;
	GANDR.Device.DrawSetting.AlphaTestMode			= -1 ;
	GANDR.Device.DrawSetting.AlphaTestParam			= 0 ;
	GANDR.Device.DrawSetting.BlendMode				= DX_BLENDMODE_NOBLEND ;
	GANDR.Device.DrawSetting.ChangeBlendParamFlag	= TRUE ;
	GANDR.Device.DrawSetting.ChangeTextureFlag		= FALSE ;
	GANDR.Device.DrawSetting.IgnoreGraphColorFlag	= FALSE ;
	GANDR.Device.DrawSetting.BlendGraphType			= 0 ;
	GANDR.Device.DrawSetting.BlendGraphBorderParam	= -1 ;
	GANDR.Device.DrawSetting.RenderTexture			= NULL ;
	GANDR.Device.DrawSetting.BlendTexture			= NULL ;

	// �`�����������
	GANDR.Device.DrawInfo.DiffuseColor				= 0xffffffff ;
	GANDR.Device.DrawInfo.BlendMaxNotDrawFlag		= FALSE ;
	GANDR.Device.DrawInfo.BeginSceneFlag			= FALSE ;
	GANDR.Device.DrawInfo.VertexNum					= 0 ;
	GANDR.Device.DrawInfo.Use3DVertex				= 0 ;
	GANDR.Device.DrawInfo.VertexType				= VERTEXTYPE_TEX ;
	GANDR.Device.DrawInfo.PrimitiveType				= GL_TRIANGLES ;

	// ���_�o�b�t�@�̃A�h���X���Z�b�g
	GANDR.Device.DrawInfo.VertexBufferNextAddr = GANDR.Device.DrawInfo.VertexBuffer ;

	// �I��
	return 0 ;
}

// �ꎞ�I�� Direct3DDevice11 ��j�������ۂɁA�j���O�̏�Ԃ����o�����߂̊֐�
extern	int		Graphics_Android_Device_ReInitialize( void )
{
	int i ;

	// �������t���O�𗧂Ă�
	GANDR.Device.DrawSetting.CancelSettingEqualCheck = TRUE ;

	// �K�� Graphics_D3D9_DrawPreparation �����s����t���O�𗧂Ă�
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �폜�O�Ɠ����������o��
	{
		// �`��e�N�X�`���֌W��������
		Graphics_Android_DrawSetting_SetTexture( NULL ) ;
		GANDR.Device.DrawSetting.AlphaChannelValidFlag	= FALSE ;
		GANDR.Device.DrawSetting.AlphaTestValidFlag	= FALSE ;

		// �`�撸�_�������Z�b�g
		GANDR.Device.DrawInfo.VertexNum = 0 ;

		// �`��u�����h���[�h�̐ݒ�
		Graphics_Android_DrawSetting_SetDrawBlendMode( GANDR.Device.DrawSetting.BlendMode, GANDR.Device.DrawSetting.AlphaTestValidFlag, GANDR.Device.DrawSetting.AlphaChannelValidFlag ) ;

		// �`��摜�̂q�f�a�𖳎����邩�ǂ������Z�b�g����
		Graphics_Android_DrawSetting_SetIgnoreDrawGraphColor( GANDR.Device.DrawSetting.IgnoreGraphColorFlag ) ;

		// �`��摜�̂`�𖳎����邩�ǂ������Z�b�g����
		Graphics_Android_DrawSetting_SetIgnoreDrawGraphAlpha( GANDR.Device.DrawSetting.IgnoreGraphAlphaFlag ) ;

		// �`���̃A���t�@�`�����l���̓��e�����������邩��ݒ肷��
		Graphics_Android_DrawSetting_SetWriteAlphaChannelFlag( GANDR.Device.DrawSetting.NotWriteAlphaChannelFlag ) ;

		// �ٕ����t�B���^�����O�̐ݒ���Z�b�g
		Graphics_Android_DeviceState_SetMaxAnisotropy( GANDR.Device.State.MaxAnisotropy ) ;

		// UV�A�h���b�V���O���[�h�̐ݒ���Z�b�g
		for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
		{
			Graphics_Android_DeviceState_SetTextureAddressUVW(
				GLES2WrapModeToDXTexAddrMode( GANDR.Device.State.TexAddressModeU[ i ] ),
				GLES2WrapModeToDXTexAddrMode( GANDR.Device.State.TexAddressModeV[ i ] ),
				GLES2WrapModeToDXTexAddrMode( GANDR.Device.State.TexAddressModeW[ i ] ),
				i ) ;
		}

		// �e�N�X�`�����W�ϊ��s����g�p���邩�ǂ����̐ݒ���Z�b�g
		Graphics_Android_DeviceState_SetTextureAddressTransformMatrix(
			GANDR.Device.State.TextureAddressTransformMatrixUse,
			&GANDR.Device.State.TextureAddressTransformMatrix ) ;

		// �t�H�O�̐ݒ���Z�b�g
		Graphics_Android_DeviceState_SetFogEnable(     GANDR.Device.State.FogEnable ) ;
		Graphics_Android_DeviceState_SetFogVertexMode( GANDR.Device.State.FogMode ) ;
		Graphics_Android_DeviceState_SetFogColor(      GANDR.Device.State.FogColor ) ;
		Graphics_Android_DeviceState_SetFogStartEnd(   GANDR.Device.State.FogStart, GANDR.Device.State.FogEnd ) ;
		Graphics_Android_DeviceState_SetFogDensity(    GANDR.Device.State.FogDensity ) ;

		// �s��̍Đݒ�
		NS_SetTransformToWorldD(                              &GSYS.DrawSetting.WorldMatrix ) ;
		NS_SetTransformToViewD(                               &GSYS.DrawSetting.ViewMatrix ) ;
		Graphics_DrawSetting_SetTransformToProjection_Direct( &GSYS.DrawSetting.ProjectionMatrix ) ;
		NS_SetTransformToViewportD(                           &GSYS.DrawSetting.ViewportMatrix ) ;

		// ���C�g�̍Đݒ�
		Graphics_Android_DeviceState_SetAmbient( &GANDR.Device.State.GlobalAmbientLightColor ) ;
		Graphics_Android_DeviceState_SetLighting( GANDR.Device.State.Lighting ) ;
		for( i = 0 ; i < DX_ANDR_COMMON_CONST_LIGHT_NUM ; i ++ )
		{
			if( GANDR.Device.State.LightParam[ i ].LightType == 0 )
			{
				continue ;
			}

			Graphics_Android_DeviceState_SetLightState( i, &GANDR.Device.State.LightParam[ i ] ) ;
			Graphics_Android_DeviceState_SetLightEnable( i, GANDR.Device.State.LightEnableFlag[ i ] ) ;
		}
	}

	// �������t���O��|��
	GANDR.Device.DrawSetting.CancelSettingEqualCheck = FALSE ;

	// ��L�ȊO�̐ݒ�����t���b�V��
	Graphics_Android_DeviceState_RefreshRenderState() ;

	// �I��
	return 0 ;
}
























// AndroidDevice �X�e�[�^�X�֌W

// �`��ݒ�����t���b�V��
extern	void	Graphics_Android_DeviceState_RefreshRenderState( void )
{
	RECT Viewport = GANDR.Device.State.ViewportRect ;

	// �������t���O�𗧂Ă�
	GANDR.Device.DrawSetting.CancelSettingEqualCheck = TRUE ;

	// Graphics_Android_DrawPreparation ���s���ׂ��t���O�𗧂Ă�
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �ݒ�̃��t���b�V��
	Graphics_Android_DeviceState_SetFogEnable             ( GANDR.Device.State.FogEnable           ) ;
//	Graphics_Android_DeviceState_SetScissorRect           ( &GANDR.Device.State.ScissorRect        ) ;
	Graphics_Android_DrawSetting_SetTexture               ( GANDR.Device.DrawSetting.RenderTexture ) ;
	Graphics_Android_DrawSetting_SetBlendTexture          ( GANDR.Device.DrawSetting.BlendTexture ) ;
	Graphics_Android_DeviceState_SetBaseState             (                                       ) ;
	Graphics_Android_DeviceState_SetDrawMode              ( GANDR.Device.State.DrawMode            ) ;
//	Graphics_Android_DrawSetting_SetDrawBlendMode         ( GANDR.Device.DrawSetting.BlendMode, GANDR.Device.DrawSetting.AlphaChannelValidFlag  ) ;
	Graphics_Android_DeviceState_NormalDrawSetup          (                                       ) ;
	Graphics_Android_DeviceState_SetDepthEnable           ( GANDR.Device.State.DepthEnable         ) ;
	Graphics_Android_DeviceState_SetDepthWriteEnable      ( GANDR.Device.State.DepthWriteEnable    ) ;
	Graphics_Android_DeviceState_SetDepthFunc             ( GANDR.Device.State.DepthFunc           ) ;
	Graphics_Android_DeviceState_SetDepthBias             ( GANDR.Device.State.DepthBias           ) ;
	Graphics_Android_DeviceState_SetCullMode              ( GANDR.Device.State.CullEnable == FALSE ? 0 : ( GANDR.Device.State.CullFace == GL_FRONT ? 1 : 2 ) ) ;
//	Graphics_Android_DeviceState_SetShadeMode             ( GANDR.Device.State.ShadeMode           ) ;
	Graphics_Android_DeviceState_SetMaterial              ( &GANDR.Device.State.Material           ) ;
	Graphics_Android_DeviceState_SetSpecularEnable        ( GANDR.Device.State.UseSpecular         ) ;
	Graphics_Android_DeviceState_SetUseVertexDiffuseColor ( GANDR.Device.State.MaterialUseVertexDiffuseColor ) ;
	Graphics_Android_DeviceState_SetUseVertexSpecularColor( GANDR.Device.State.MaterialUseVertexSpecularColor ) ;
	Graphics_Android_DeviceState_SetShader                ( GANDR.Device.State.SetShader, GANDR.Device.State.SetNormalShader ) ;
	Graphics_Android_DeviceState_SetRenderTarget          ( GANDR.Device.State.TargetFrameBuffer, GANDR.Device.State.TargetFrameBufferWidth, GANDR.Device.State.TargetFrameBufferHeight ) ;
	Graphics_Android_DeviceState_SetViewport              ( &Viewport ) ;
	Graphics_Android_DeviceState_SetBackgroundColor       ( GANDR.Device.State.BackgroundColor.r, GANDR.Device.State.BackgroundColor.g, GANDR.Device.State.BackgroundColor.b, GANDR.Device.State.BackgroundColor.a ) ;

	// �e�N�X�`�����Z�b�g
	{
		int i ;

		for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
		{
			Graphics_Android_DeviceState_SetTexture( i, GANDR.Device.State.SetTexture[ i ] ) ;
		}
	}

	// �萔�o�b�t�@�����t���b�V��
	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �������t���O��|��
	GANDR.Device.DrawSetting.CancelSettingEqualCheck = FALSE ;
}

// OpenGL �̊�{�ݒ���s��
extern int Graphics_Android_DeviceState_SetBaseState( void )
{
	// �����o��
	DRAWSTOCKINFO

	// �I��
	return 0 ;
}

// �T���v���[�̃e�N�X�`���t�B���^�����O���[�h��ݒ肷��
extern int Graphics_Android_DeviceState_SetSampleFilterMode( GLenum Filter, int Sampler )
{
	int i ;
	GLenum MagFilter ;
	GLenum MinFilter ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	MinFilter = Filter ;
	switch( Filter )
	{
	case GL_NEAREST :
	case GL_NEAREST_MIPMAP_NEAREST :
	case GL_NEAREST_MIPMAP_LINEAR :
		MagFilter = GL_NEAREST ;
		break ;

	case GL_LINEAR :
	case GL_LINEAR_MIPMAP_NEAREST :
	case GL_LINEAR_MIPMAP_LINEAR :
		MagFilter = GL_LINEAR ;
		break ;

	default :
		return -1 ;
	}

	if( Sampler < 0 )
	{
		if( Filter == GL_NEAREST ||
			Filter == GL_LINEAR )
		{
			GANDR.Device.State.DrawMode = -1 ;
		}

		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
			{
				if( ( DWORD )GANDR.Device.State.TexMagFilter[ i ] != MagFilter ||
					( DWORD )GANDR.Device.State.TexMinFilter[ i ] != MinFilter )
				{
					break ;
				}
			}
			if( i == USE_TEXTURESTAGE_NUM )
			{
				return 0 ;
			}
		}

		DRAWSTOCKINFO

		for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
		{
			if( ( DWORD )GANDR.Device.State.TexMagFilter[ i ] == MagFilter &&
				( DWORD )GANDR.Device.State.TexMinFilter[ i ] == MinFilter &&
				GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
			{
				continue ;
			}

			GANDR.Device.State.TexMagFilter[ i ] = MagFilter ;
			GANDR.Device.State.TexMinFilter[ i ] = MinFilter ;

			if( GANDR.Device.State.SetTexture[ i ] != NULL )
			{
				glActiveTexture( g_TextureEnum[ i ] ) ;
				glBindTexture( GL_TEXTURE_2D, GANDR.Device.State.SetTexture[ i ]->TextureBuffer ) ;
				if( GANDR.Device.State.SetTexture[ i ]->MagFilter != GANDR.Device.State.TexMagFilter[ i ] )
				{
					GANDR.Device.State.SetTexture[ i ]->MagFilter = GANDR.Device.State.TexMagFilter[ i ] ;
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GANDR.Device.State.SetTexture[ i ]->MagFilter ) ;
				}
				if( GANDR.Device.State.SetTexture[ i ]->MinFilter != GANDR.Device.State.TexMinFilter[ i ] )
				{
					GLenum MinFilterTmp = MinFilter ;
					if( GANDR.Device.State.SetTexture[ i ]->MipMapCount <= 1 && MinFilter == GL_LINEAR_MIPMAP_LINEAR )
					{
						MinFilterTmp = GL_LINEAR ;
					}
					if( GANDR.Device.State.SetTexture[ i ]->MinFilter != MinFilterTmp )
					{
						GANDR.Device.State.SetTexture[ i ]->MinFilter = MinFilterTmp ;
						glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GANDR.Device.State.SetTexture[ i ]->MinFilter ) ;
					}
				}
			}
		}
	}
	else
	{
		if( Sampler < 0 || Sampler >= USE_TEXTURESTAGE_NUM )
		{
			return 0 ;
		}

		GANDR.Device.State.DrawMode = -1 ;

		if( ( DWORD )GANDR.Device.State.TexMagFilter[ Sampler ] == MagFilter &&
			( DWORD )GANDR.Device.State.TexMinFilter[ Sampler ] == MinFilter &&
			GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			return 0 ;
		}

		DRAWSTOCKINFO

		GANDR.Device.State.TexMagFilter[ Sampler ] = MagFilter ;
		GANDR.Device.State.TexMinFilter[ Sampler ] = MinFilter ;

		if( GANDR.Device.State.SetTexture[ Sampler ] != NULL )
		{
			glActiveTexture( g_TextureEnum[ Sampler ] ) ;
			glBindTexture( GL_TEXTURE_2D, GANDR.Device.State.SetTexture[ Sampler ]->TextureBuffer ) ;
			if( GANDR.Device.State.SetTexture[ Sampler ]->MagFilter != GANDR.Device.State.TexMagFilter[ Sampler ] )
			{
				GANDR.Device.State.SetTexture[ Sampler ]->MagFilter = GANDR.Device.State.TexMagFilter[ Sampler ] ;
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GANDR.Device.State.SetTexture[ Sampler ]->MagFilter ) ;
			}
			if( GANDR.Device.State.SetTexture[ Sampler ]->MinFilter != GANDR.Device.State.TexMinFilter[ Sampler ] )
			{
				GLenum MinFilterTmp = MinFilter ;
				if( GANDR.Device.State.SetTexture[ Sampler ]->MipMapCount <= 1 && MinFilter == GL_LINEAR_MIPMAP_LINEAR )
				{
					MinFilterTmp = GL_LINEAR ;
				}
				if( GANDR.Device.State.SetTexture[ Sampler ]->MinFilter != MinFilterTmp )
				{
					GANDR.Device.State.SetTexture[ Sampler ]->MinFilter = MinFilterTmp ;
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GANDR.Device.State.SetTexture[ Sampler ]->MinFilter ) ;
				}
			}
		}
	}

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �[�x�o�b�t�@�̗L�������̃Z�b�g
extern int Graphics_Android_DeviceState_SetDepthEnable( BOOL DepthEnable )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// ���[�h�������������牽�������I��
	if( GANDR.Device.State.DepthEnable == DepthEnable &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}
	
	DRAWSTOCKINFO

	GANDR.Device.State.DepthEnable = DepthEnable ;

	if( DepthEnable )
	{
		glEnable( GL_DEPTH_TEST ) ;
	}
	else
	{
		glDisable( GL_DEPTH_TEST ) ;
	}

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �[�x�o�b�t�@�̏������݂̗L�����Z�b�g
extern int Graphics_Android_DeviceState_SetDepthWriteEnable( int Flag )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// ���[�h�������������牽�������I��
	if( GANDR.Device.State.DepthWriteEnable == Flag &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}
	
	DRAWSTOCKINFO

	GANDR.Device.State.DepthWriteEnable = Flag ;

	glDepthMask( Flag ? GL_TRUE : GL_FALSE ) ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �[�x�l�̔�r�^�C�v���Z�b�g
extern int Graphics_Android_DeviceState_SetDepthFunc( GLenum DepthFunc )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// ���[�h�������������牽�������I��
	if( GANDR.Device.State.DepthFunc == DepthFunc &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}
	
	DRAWSTOCKINFO

	GANDR.Device.State.DepthFunc = DepthFunc ;

	glDepthFunc( DepthFunc ) ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �[�x�l�̃o�C�A�X���Z�b�g
extern int Graphics_Android_DeviceState_SetDepthBias( int DepthBias )
{
	// ���[�h�������������牽�������I��
	if( GANDR.Device.State.DepthBias == DepthBias &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}
	
	DRAWSTOCKINFO

	GANDR.Device.State.DepthBias = DepthBias ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// ���[���h�ϊ��p�s����Z�b�g����
extern int Graphics_Android_DeviceState_SetWorldMatrix( const MATRIX *Matrix )
{
	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 0 ] = Matrix->m[ 0 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 1 ] = Matrix->m[ 1 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 2 ] = Matrix->m[ 2 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 3 ] = Matrix->m[ 3 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 0 ] = Matrix->m[ 0 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 1 ] = Matrix->m[ 1 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 2 ] = Matrix->m[ 2 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 3 ] = Matrix->m[ 3 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 0 ] = Matrix->m[ 0 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 1 ] = Matrix->m[ 1 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 2 ] = Matrix->m[ 2 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 3 ] = Matrix->m[ 3 ][ 2 ] ;

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �I��
	return 0 ;
}

// �r���[�ϊ��p�s����Z�b�g����
extern int Graphics_Android_DeviceState_SetViewMatrix( const MATRIX *Matrix )
{
	// ���C�g�̈ʒu�E�����̍Čv�Z
	{
		int    i ;
		VECTOR Direction ;
		VECTOR Position ;

		for( i = 0 ; i < DX_ANDR_COMMON_CONST_LIGHT_NUM ; i ++ )
		{
			VectorTransformSR( &Direction, &GANDR.Device.State.LightParam[ i ].Direction, Matrix ) ;
			VectorTransform(   &Position,  &GANDR.Device.State.LightParam[ i ].Position,  Matrix ) ;
			GANDR.Device.Shader.Constant.uLightPos[ i ][ 0 ]  = Position.x ;
			GANDR.Device.Shader.Constant.uLightPos[ i ][ 1 ]  = Position.y ;
			GANDR.Device.Shader.Constant.uLightPos[ i ][ 2 ]  = Position.z ;
			GANDR.Device.Shader.Constant.uLightDir[ i ][ 0 ] = Direction.x ;
			GANDR.Device.Shader.Constant.uLightDir[ i ][ 1 ] = Direction.y ;
			GANDR.Device.Shader.Constant.uLightDir[ i ][ 2 ] = Direction.z ;
		}
	}

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uViewMat[ 0 ][ 0 ] = Matrix->m[ 0 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 0 ][ 1 ] = Matrix->m[ 1 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 0 ][ 2 ] = Matrix->m[ 2 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 0 ][ 3 ] = Matrix->m[ 3 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 1 ][ 0 ] = Matrix->m[ 0 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 1 ][ 1 ] = Matrix->m[ 1 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 1 ][ 2 ] = Matrix->m[ 2 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 1 ][ 3 ] = Matrix->m[ 3 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 2 ][ 0 ] = Matrix->m[ 0 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 2 ][ 1 ] = Matrix->m[ 1 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 2 ][ 2 ] = Matrix->m[ 2 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uViewMat[ 2 ][ 3 ] = Matrix->m[ 3 ][ 2 ] ;

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �I��
	return 0 ;
}

// ���e�ϊ��p�s����Z�b�g����
extern int Graphics_Android_DeviceState_SetProjectionMatrix( const MATRIX *Matrix )
{
	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uProjMat[ 0 ][ 0 ] = Matrix->m[ 0 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 0 ][ 1 ] = Matrix->m[ 1 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 0 ][ 2 ] = Matrix->m[ 2 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 0 ][ 3 ] = Matrix->m[ 3 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 1 ][ 0 ] = Matrix->m[ 0 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 1 ][ 1 ] = Matrix->m[ 1 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 1 ][ 2 ] = Matrix->m[ 2 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 1 ][ 3 ] = Matrix->m[ 3 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 2 ][ 0 ] = Matrix->m[ 0 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 2 ][ 1 ] = Matrix->m[ 1 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 2 ][ 2 ] = Matrix->m[ 2 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 2 ][ 3 ] = Matrix->m[ 3 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 3 ][ 0 ] = Matrix->m[ 0 ][ 3 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 3 ][ 1 ] = Matrix->m[ 1 ][ 3 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 3 ][ 2 ] = Matrix->m[ 2 ][ 3 ] ;
	GANDR.Device.Shader.Constant.uProjMat[ 3 ][ 3 ] = Matrix->m[ 3 ][ 3 ] ;

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �I��
	return 0 ;
}

// �A���`�r���[�|�[�g�s����Z�b�g����
extern int Graphics_Android_DeviceState_SetAntiViewportMatrix( const MATRIX *Matrix )
{
	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uAntiVPMat[ 0 ][ 0 ] = Matrix->m[ 0 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 0 ][ 1 ] = Matrix->m[ 1 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 0 ][ 2 ] = Matrix->m[ 2 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 0 ][ 3 ] = Matrix->m[ 3 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 1 ][ 0 ] = Matrix->m[ 0 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 1 ][ 1 ] = Matrix->m[ 1 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 1 ][ 2 ] = Matrix->m[ 2 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 1 ][ 3 ] = Matrix->m[ 3 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 2 ][ 0 ] = Matrix->m[ 0 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 2 ][ 1 ] = Matrix->m[ 1 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 2 ][ 2 ] = Matrix->m[ 2 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 2 ][ 3 ] = Matrix->m[ 3 ][ 2 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 3 ][ 0 ] = Matrix->m[ 0 ][ 3 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 3 ][ 1 ] = Matrix->m[ 1 ][ 3 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 3 ][ 2 ] = Matrix->m[ 2 ][ 3 ] ;
	GANDR.Device.Shader.Constant.uAntiVPMat[ 3 ][ 3 ] = Matrix->m[ 3 ][ 3 ] ;

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �I��
	return 0 ;
}

// �A���r�G���g���C�g�ƃG�~�b�V�u�J���[���|�����킹���p�����[�^���X�V����
extern void Graphics_Android_DeviceState_RefreshAmbientAndEmissiveParam( void )
{
	int i ;

	// �L���ȃ��C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z�������̂��V�F�[�_�[�ɃZ�b�g����
	for( i = 0 ; i <= GANDR.Device.State.LightEnableMaxIndex ; i ++ )
	{
		if( GANDR.Device.State.LightEnableFlag[ i ] == FALSE )
		{
			continue ;
		}

		// �萔�o�b�t�@�ɔ��f����
		GANDR.Device.Shader.Constant.uLightAmb[ i ][ 0 ] = GANDR.Device.State.LightParam[ i ].Ambient.r * GANDR.Device.State.Material.Ambient.r ;
		GANDR.Device.Shader.Constant.uLightAmb[ i ][ 1 ] = GANDR.Device.State.LightParam[ i ].Ambient.g * GANDR.Device.State.Material.Ambient.g ;
		GANDR.Device.Shader.Constant.uLightAmb[ i ][ 2 ] = GANDR.Device.State.LightParam[ i ].Ambient.b * GANDR.Device.State.Material.Ambient.b ;
		GANDR.Device.Shader.Constant.uLightAmb[ i ][ 3 ] = GANDR.Device.State.LightParam[ i ].Ambient.a * GANDR.Device.State.Material.Ambient.a ;
	}

	// �O���[�o���A���r�G���g���C�g�J���[�ƃ}�e���A���A���r�G���g�J���[����Z�������̂ƃG�~�b�V�u�J���[�����Z�������̂��쐬����
	GANDR.Device.Shader.Constant.uAmb_Emi[ 0 ] = GANDR.Device.State.GlobalAmbientLightColor.r * GANDR.Device.State.Material.Ambient.r + GANDR.Device.State.Material.Emissive.r ;
	GANDR.Device.Shader.Constant.uAmb_Emi[ 1 ] = GANDR.Device.State.GlobalAmbientLightColor.g * GANDR.Device.State.Material.Ambient.g + GANDR.Device.State.Material.Emissive.g ;
	GANDR.Device.Shader.Constant.uAmb_Emi[ 2 ] = GANDR.Device.State.GlobalAmbientLightColor.b * GANDR.Device.State.Material.Ambient.b + GANDR.Device.State.Material.Emissive.b ;
	GANDR.Device.Shader.Constant.uAmb_Emi[ 3 ] = GANDR.Device.State.GlobalAmbientLightColor.a * GANDR.Device.State.Material.Ambient.a + GANDR.Device.State.Material.Emissive.a ;

	GANDR.Device.Shader.Constant.UpdateCount ++ ;
}



// ���C�g�̃Z�b�g
extern int Graphics_Android_DeviceState_SetLightState( int LightNumber, LIGHTPARAM *Light )
{
	VECTOR  Direction ;
	VECTOR  Position ;
	float   ThetaSin ;
	float   ThetaCos ;
	float   PhiSin ;
	float   PhiCos ;

	if( LightNumber < 0 || LightNumber >= DX_ANDR_COMMON_CONST_LIGHT_NUM )
	{
		return -1 ;
	}

	if( _MEMCMP( &GANDR.Device.State.LightParam[ LightNumber ], Light, sizeof( LIGHTPARAM ) ) == 0 &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	// �p�����[�^�̕ۑ�
	GANDR.Device.State.LightParam[ LightNumber ] = *Light ;

	// �萔�f�[�^�ɔ��f
	_SINCOS( Light->Theta / 2.0f, &ThetaSin, &ThetaCos ) ;
	_SINCOS( Light->Phi   / 2.0f, &PhiSin,   &PhiCos ) ;

	VectorTransformSR( &Direction, &Light->Direction, &GSYS.DrawSetting.ViewMatrixF ) ;
	VectorTransform(   &Position,  &Light->Position,  &GSYS.DrawSetting.ViewMatrixF ) ;
	GANDR.Device.Shader.Constant.uLightPos[ LightNumber ][ 0 ]						= Position.x ;
	GANDR.Device.Shader.Constant.uLightPos[ LightNumber ][ 1 ]						= Position.y ;
	GANDR.Device.Shader.Constant.uLightPos[ LightNumber ][ 2 ]						= Position.z ;
	GANDR.Device.Shader.Constant.uLightDir[ LightNumber ][ 0 ]						= Direction.x ;
	GANDR.Device.Shader.Constant.uLightDir[ LightNumber ][ 1 ]						= Direction.y ;
	GANDR.Device.Shader.Constant.uLightDir[ LightNumber ][ 2 ]						= Direction.z ;
	GANDR.Device.Shader.Constant.uLightDif[ LightNumber ][ 0 ]						= Light->Diffuse.r ;
	GANDR.Device.Shader.Constant.uLightDif[ LightNumber ][ 1 ]						= Light->Diffuse.g ;
	GANDR.Device.Shader.Constant.uLightDif[ LightNumber ][ 2 ]						= Light->Diffuse.b ;
	GANDR.Device.Shader.Constant.uLightDif[ LightNumber ][ 3 ]						= Light->Diffuse.a ;
	GANDR.Device.Shader.Constant.uLightSpc[ LightNumber ][ 0 ]						= Light->Specular.r ;
	GANDR.Device.Shader.Constant.uLightSpc[ LightNumber ][ 1 ]						= Light->Specular.g ;
	GANDR.Device.Shader.Constant.uLightSpc[ LightNumber ][ 2 ]						= Light->Specular.b ;
	GANDR.Device.Shader.Constant.uLightSpc[ LightNumber ][ 3 ]						= Light->Specular.a ;
	GANDR.Device.Shader.Constant.uLightAmb[ LightNumber ][ 0 ]						= Light->Ambient.r ;
	GANDR.Device.Shader.Constant.uLightAmb[ LightNumber ][ 1 ]						= Light->Ambient.g ;
	GANDR.Device.Shader.Constant.uLightAmb[ LightNumber ][ 2 ]						= Light->Ambient.b ;
	GANDR.Device.Shader.Constant.uLightAmb[ LightNumber ][ 3 ]						= Light->Ambient.a ;
	GANDR.Device.Shader.Constant.uLightRange_FallOff_AT0_AT1[ LightNumber ][ 0 ]	= Light->Range * Light->Range ;
	GANDR.Device.Shader.Constant.uLightRange_FallOff_AT0_AT1[ LightNumber ][ 1 ]	= Light->Falloff ;
	GANDR.Device.Shader.Constant.uLightRange_FallOff_AT0_AT1[ LightNumber ][ 2 ]	= Light->Attenuation0 ;
	GANDR.Device.Shader.Constant.uLightRange_FallOff_AT0_AT1[ LightNumber ][ 3 ]	= Light->Attenuation1 ;
	GANDR.Device.Shader.Constant.uLightAT2_SpotP0_SpotP1[ LightNumber ][ 0 ]		= Light->Attenuation2 ;
	GANDR.Device.Shader.Constant.uLightAT2_SpotP0_SpotP1[ LightNumber ][ 1 ]		= PhiCos ;
	if( _FABS( ThetaCos - PhiCos ) < 0.0000001f )
	{
		GANDR.Device.Shader.Constant.uLightAT2_SpotP0_SpotP1[ LightNumber ][ 2 ]    = 100000.0f ;
	}
	else
	{
		GANDR.Device.Shader.Constant.uLightAT2_SpotP0_SpotP1[ LightNumber ][ 2 ]	= 1.0f / ( ThetaCos - PhiCos ) ;
	}
	GANDR.Device.Shader.Constant.uLightAT2_SpotP0_SpotP1[ LightNumber ][ 3 ]		= 0.0f ;
	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �A���r�G���g�J���[�ƃG�~�b�V�u�J���[���|�����킹�������X�V����
	Graphics_Android_DeviceState_RefreshAmbientAndEmissiveParam() ;

	// �I��
	return 0 ;
}

// ���C�g�̗L���A������ύX
extern int Graphics_Android_DeviceState_SetLightEnable( int LightNumber, int EnableState )
{
	if( LightNumber < 0 || LightNumber >= DX_ANDR_COMMON_CONST_LIGHT_NUM )
	{
		return -1 ;
	}

	if( GANDR.Device.State.LightEnableFlag[ LightNumber ] == EnableState &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	GANDR.Device.State.LightEnableFlag[ LightNumber ] = EnableState ;

	// �L���ȃ��C�g�̍ő�C���f�b�N�X���X�V
	if( EnableState == TRUE )
	{
		if( GANDR.Device.State.LightEnableMaxIndex < LightNumber )
			GANDR.Device.State.LightEnableMaxIndex = LightNumber ;
	}
	else
	{
		if( GANDR.Device.State.LightEnableMaxIndex == LightNumber )
		{
			int i ;

			for( i = LightNumber ; i > 0 && GANDR.Device.State.LightEnableFlag[ i ] == FALSE ; i -- ){}
			GANDR.Device.State.LightEnableMaxIndex = i ;
		}
	}

	// �A���r�G���g�J���[�ƃG�~�b�V�u�J���[���|�����킹�������X�V����
	Graphics_Android_DeviceState_RefreshAmbientAndEmissiveParam() ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �}�e���A���̃Z�b�g
extern int Graphics_Android_DeviceState_SetMaterial( MATERIALPARAM *Material )
{
	if( _MEMCMP( GSYS.Light.MaterialTypeParam, GANDR.Device.State.MaterialTypeParam, sizeof( GSYS.Light.MaterialTypeParam) ) == 0 &&
		_MEMCMP( Material, &GANDR.Device.State.Material, sizeof( MATERIALPARAM ) ) == 0 &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	GANDR.Device.State.Material = *Material ;
	_MEMCPY( GANDR.Device.State.MaterialTypeParam, GSYS.Light.MaterialTypeParam, sizeof( GSYS.Light.MaterialTypeParam ) ) ;

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uMatDif[ 0 ]   = Material->Diffuse.r ;
	GANDR.Device.Shader.Constant.uMatDif[ 1 ]   = Material->Diffuse.g ;
	GANDR.Device.Shader.Constant.uMatDif[ 2 ]   = Material->Diffuse.b ;
	GANDR.Device.Shader.Constant.uMatDif[ 3 ]   = Material->Diffuse.a ;
	GANDR.Device.Shader.Constant.uMatSpc[ 0 ]   = Material->Specular.r ;
	GANDR.Device.Shader.Constant.uMatSpc[ 1 ]   = Material->Specular.g ;
	GANDR.Device.Shader.Constant.uMatSpc[ 2 ]   = Material->Specular.b ;
	GANDR.Device.Shader.Constant.uMatSpc[ 3 ]   = Material->Specular.a ;
	GANDR.Device.Shader.Constant.uMatPow        = Material->Power < 0.00000000001f ? 0.00000000001f : Material->Power ;
	GANDR.Device.Shader.Constant.uMatTypeParam0 = GANDR.Device.State.MaterialTypeParam[ 0 ] ;
	GANDR.Device.Shader.Constant.uMatTypeParam1 = GANDR.Device.State.MaterialTypeParam[ 1 ] ;
	GANDR.Device.Shader.Constant.uMatTypeParam2 = GANDR.Device.State.MaterialTypeParam[ 2 ] ;
	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �A���r�G���g�J���[�ƃG�~�b�V�u�J���[���|�����킹�������X�V����
	Graphics_Android_DeviceState_RefreshAmbientAndEmissiveParam() ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �X�y�L�������g�p���邩�ǂ������Z�b�g
extern int Graphics_Android_DeviceState_SetSpecularEnable( int UseFlag )
{
	// �����̃p�����[�^�Ɠ����ꍇ�͉������Ȃ�
	if( GANDR.Device.State.UseSpecular == UseFlag &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uDifSrc_SpeSrc_MulSpeCol[ 2 ] = UseFlag ? 1.0f : 0.0f ;
	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	GANDR.Device.State.UseSpecular = UseFlag ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// ���_�̃f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�Ƃ��Ďg�p���邩�ǂ�����ݒ肷��
extern int Graphics_Android_DeviceState_SetUseVertexDiffuseColor( int UseFlag )
{
	if( UseFlag == GANDR.Device.State.MaterialUseVertexDiffuseColor &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uDifSrc_SpeSrc_MulSpeCol[ 0 ] = UseFlag ? 1.0f : 0.0f ;
	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	GANDR.Device.State.MaterialUseVertexDiffuseColor = UseFlag ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// ���_�̃X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�Ƃ��Ďg�p���邩�ǂ�����ݒ肷��
extern int Graphics_Android_DeviceState_SetUseVertexSpecularColor( int UseFlag )
{
	if( UseFlag == GANDR.Device.State.MaterialUseVertexSpecularColor &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uDifSrc_SpeSrc_MulSpeCol[ 1 ] = UseFlag ? 1.0f : 0.0f ;
	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	GANDR.Device.State.MaterialUseVertexSpecularColor = UseFlag ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �J�����O�̗L�����Z�b�g 
extern int Graphics_Android_DeviceState_SetCullMode( int State )
{
	int Enable = FALSE ;
	GLenum CullFace = GL_BACK ;
	GLenum FrontFace = GL_CW ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	switch( State )
	{
	case 0 :
	default :
		Enable = FALSE ;
		break ;

	case 1 :
		Enable = TRUE ;
		CullFace = GL_FRONT ;
		break ;

	case 2 :
		Enable = TRUE ;
		CullFace = GL_BACK ;
		break ;
	}

	// ���[�h�������������牽�������I��
	if( GANDR.Device.State.CullEnable == Enable &&
		GANDR.Device.State.CullFace == CullFace &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}
	
	DRAWSTOCKINFO

	GANDR.Device.State.CullEnable = Enable ;
	GANDR.Device.State.CullFace   = CullFace ;

	if( Enable )
	{
		glEnable( GL_CULL_FACE ) ;
	}
	else
	{
//		glEnable( GL_CULL_FACE ) ;
		glDisable( GL_CULL_FACE ) ;
	}

	glCullFace( CullFace ) ;
	glFrontFace( FrontFace ) ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �A���r�G���g�J���[�̃Z�b�g
extern int Graphics_Android_DeviceState_SetAmbient( COLOR_F *Color )
{
	if( _MEMCMP( Color, &GANDR.Device.State.GlobalAmbientLightColor, sizeof( COLOR_F ) ) == 0 &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	GANDR.Device.State.GlobalAmbientLightColor = *Color ;

	// �A���r�G���g�J���[�ƃG�~�b�V�u�J���[���|�����킹�������X�V����
	Graphics_Android_DeviceState_RefreshAmbientAndEmissiveParam() ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �e�N�X�`���[�̃A�h���b�V���O���[�h���Z�b�g����
extern int  Graphics_Android_DeviceState_SetTextureAddress( int AddressMode, int Sampler )
{
	int i ;
	GLenum WrapMode ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( AddressMode < 0 || AddressMode >= DX_TEXADDRESS_NUM )
	{
		return -1 ;
	}

	WrapMode = g_DXTexAddrModeToGLES2WrapMode[ AddressMode ] ;

	if( Sampler < 0 )
	{
		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
			{
				if( WrapMode != ( DWORD )GANDR.Device.State.TexAddressModeU[ i ] ||
					WrapMode != ( DWORD )GANDR.Device.State.TexAddressModeV[ i ] ||
					WrapMode != ( DWORD )GANDR.Device.State.TexAddressModeW[ i ] )
				{
					break ;
				}
			}
			if( i == USE_TEXTURESTAGE_NUM )
			{
				return 0 ;
			}
		}

		DRAWSTOCKINFO

		for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
		{
			if( WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeU[ i ] &&
				WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeV[ i ] &&
				WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeW[ i ] &&
				GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
			{
				continue ;
			}

			GANDR.Device.State.TexAddressModeU[ i ] = WrapMode ;
			GANDR.Device.State.TexAddressModeV[ i ] = WrapMode ;
			GANDR.Device.State.TexAddressModeW[ i ] = WrapMode ;

			if( GANDR.Device.State.SetTexture[ i ] != NULL )
			{
				glActiveTexture( g_TextureEnum[ i ] ) ;
				glBindTexture( GL_TEXTURE_2D, GANDR.Device.State.SetTexture[ i ]->TextureBuffer ) ;
				if( GANDR.Device.State.SetTexture[ i ]->WrapS != GANDR.Device.State.TexAddressModeU[ i ] )
				{
					GANDR.Device.State.SetTexture[ i ]->WrapS = GANDR.Device.State.TexAddressModeU[ i ] ;
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GANDR.Device.State.SetTexture[ i ]->WrapS ) ;
				}
				if( GANDR.Device.State.SetTexture[ i ]->WrapT != GANDR.Device.State.TexAddressModeV[ i ] )
				{
					GANDR.Device.State.SetTexture[ i ]->WrapT = GANDR.Device.State.TexAddressModeV[ i ] ;
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GANDR.Device.State.SetTexture[ i ]->WrapT ) ;
				}
			}
		}
	}
	else
	{
		if( Sampler < 0 || Sampler >= USE_TEXTURESTAGE_NUM )
		{
			return -1 ;
		}

		if( WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeU[ Sampler ] &&
			WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeV[ Sampler ] &&
			WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeW[ Sampler ] &&
			GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			return 0 ;
		}

		DRAWSTOCKINFO

		GANDR.Device.State.TexAddressModeU[ Sampler ] = WrapMode ;
		GANDR.Device.State.TexAddressModeV[ Sampler ] = WrapMode ;
		GANDR.Device.State.TexAddressModeW[ Sampler ] = WrapMode ;

		if( GANDR.Device.State.SetTexture[ Sampler ] != NULL )
		{
			glActiveTexture( g_TextureEnum[ Sampler ] ) ;
			glBindTexture( GL_TEXTURE_2D, GANDR.Device.State.SetTexture[ Sampler ]->TextureBuffer ) ;
			if( GANDR.Device.State.SetTexture[ Sampler ]->WrapS != GANDR.Device.State.TexAddressModeU[ Sampler ] )
			{
				GANDR.Device.State.SetTexture[ Sampler ]->WrapS = GANDR.Device.State.TexAddressModeU[ Sampler ] ;
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GANDR.Device.State.SetTexture[ Sampler ]->WrapS ) ;
			}
			if( GANDR.Device.State.SetTexture[ Sampler ]->WrapT != GANDR.Device.State.TexAddressModeV[ Sampler ] )
			{
				GANDR.Device.State.SetTexture[ Sampler ]->WrapT = GANDR.Device.State.TexAddressModeV[ Sampler ] ;
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GANDR.Device.State.SetTexture[ Sampler ]->WrapT ) ;
			}
		}
	}

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �e�N�X�`���[�̃A�h���b�V���O���[�h���Z�b�g����
extern int Graphics_Android_DeviceState_SetTextureAddressU( int AddressMode, int Sampler )
{
	int i ;
	GLenum WrapMode ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( AddressMode < 0 || AddressMode >= DX_TEXADDRESS_NUM )
	{
		return -1 ;
	}

	WrapMode = g_DXTexAddrModeToGLES2WrapMode[ AddressMode ] ;

	if( Sampler == -1 )
	{
		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
			{
				if( WrapMode != ( DWORD )GANDR.Device.State.TexAddressModeU[ i ] )
				{
					break ;
				}
			}
			if( i == USE_TEXTURESTAGE_NUM )
			{
				return 0 ;
			}
		}

		DRAWSTOCKINFO

		for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
		{
			if( WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeU[ i ] &&
				GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
			{
				continue ;
			}

			GANDR.Device.State.TexAddressModeU[ i ] = WrapMode ;

			if( GANDR.Device.State.SetTexture[ i ] != NULL )
			{
				glActiveTexture( g_TextureEnum[ i ] ) ;
				glBindTexture( GL_TEXTURE_2D, GANDR.Device.State.SetTexture[ i ]->TextureBuffer ) ;
				if( GANDR.Device.State.SetTexture[ i ]->WrapS != GANDR.Device.State.TexAddressModeU[ i ] )
				{
					GANDR.Device.State.SetTexture[ i ]->WrapS = GANDR.Device.State.TexAddressModeU[ i ] ;
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GANDR.Device.State.SetTexture[ i ]->WrapS ) ;
				}
			}
		}
	}
	else
	{
		if( Sampler < 0 || Sampler >= USE_TEXTURESTAGE_NUM )
		{
			return -1 ;
		}

		if( WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeU[ Sampler ] &&
			GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			return 0 ;
		}

		DRAWSTOCKINFO

		GANDR.Device.State.TexAddressModeU[ Sampler ] = WrapMode ;

		if( GANDR.Device.State.SetTexture[ Sampler ] != NULL )
		{
			glActiveTexture( g_TextureEnum[ Sampler ] ) ;
			glBindTexture( GL_TEXTURE_2D, GANDR.Device.State.SetTexture[ Sampler ]->TextureBuffer ) ;
			if( GANDR.Device.State.SetTexture[ Sampler ]->WrapS != GANDR.Device.State.TexAddressModeU[ Sampler ] )
			{
				GANDR.Device.State.SetTexture[ Sampler ]->WrapS = GANDR.Device.State.TexAddressModeU[ Sampler ] ;
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GANDR.Device.State.SetTexture[ Sampler ]->WrapS ) ;
			}
		}
	}

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �e�N�X�`���[�̃A�h���b�V���O���[�h���Z�b�g����
extern int Graphics_Android_DeviceState_SetTextureAddressV( int AddressMode, int Sampler )
{
	int i ;
	GLenum WrapMode ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( AddressMode < 0 || AddressMode >= DX_TEXADDRESS_NUM )
	{
		return -1 ;
	}

	WrapMode = g_DXTexAddrModeToGLES2WrapMode[ AddressMode ] ;

	if( Sampler == -1 )
	{
		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
			{
				if( WrapMode != ( DWORD )GANDR.Device.State.TexAddressModeV[ i ] )
				{
					break ;
				}
			}
			if( i == USE_TEXTURESTAGE_NUM )
			{
				return 0 ;
			}
		}

		DRAWSTOCKINFO

		for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
		{
			if( WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeV[ i ] &&
				GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
			{
				continue ;
			}

			GANDR.Device.State.TexAddressModeV[ i ] = WrapMode ;

			if( GANDR.Device.State.SetTexture[ i ] != NULL )
			{
				glActiveTexture( g_TextureEnum[ i ] ) ;
				glBindTexture( GL_TEXTURE_2D, GANDR.Device.State.SetTexture[ i ]->TextureBuffer ) ;
				if( GANDR.Device.State.SetTexture[ i ]->WrapT != GANDR.Device.State.TexAddressModeV[ i ] )
				{
					GANDR.Device.State.SetTexture[ i ]->WrapT = GANDR.Device.State.TexAddressModeV[ i ] ;
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GANDR.Device.State.SetTexture[ i ]->WrapT ) ;
				}
			}
		}
	}
	else
	{
		if( Sampler < 0 || Sampler >= USE_TEXTURESTAGE_NUM )
		{
			return -1 ;
		}

		if( WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeV[ Sampler ] &&
			GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			return 0 ;
		}

		DRAWSTOCKINFO

		GANDR.Device.State.TexAddressModeV[ Sampler ] = WrapMode ;

		if( GANDR.Device.State.SetTexture[ Sampler ] != NULL )
		{
			glActiveTexture( g_TextureEnum[ Sampler ] ) ;
			glBindTexture( GL_TEXTURE_2D, GANDR.Device.State.SetTexture[ Sampler ]->TextureBuffer ) ;
			if( GANDR.Device.State.SetTexture[ Sampler ]->WrapT != GANDR.Device.State.TexAddressModeV[ Sampler ] )
			{
				GANDR.Device.State.SetTexture[ Sampler ]->WrapT = GANDR.Device.State.TexAddressModeV[ Sampler ] ;
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GANDR.Device.State.SetTexture[ Sampler ]->WrapT ) ;
			}
		}
	}

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �e�N�X�`���[�̃A�h���b�V���O���[�h���Z�b�g����
extern int Graphics_Android_DeviceState_SetTextureAddressW( int AddressMode, int Sampler )
{
	int i ;
	GLenum WrapMode ;

	if( AddressMode < 0 || AddressMode >= DX_TEXADDRESS_NUM )
	{
		return -1 ;
	}

	WrapMode = g_DXTexAddrModeToGLES2WrapMode[ AddressMode ] ;

	if( Sampler == -1 )
	{
		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
			{
				if( WrapMode != ( DWORD )GANDR.Device.State.TexAddressModeW[ i ] )
				{
					break ;
				}
			}
			if( i == USE_TEXTURESTAGE_NUM )
			{
				return 0 ;
			}
		}

		DRAWSTOCKINFO

		for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
		{
			if( WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeW[ i ] &&
				GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
			{
				continue ;
			}

			GANDR.Device.State.TexAddressModeW[ i ] = WrapMode ;
		}
	}
	else
	{
		if( Sampler < 0 || Sampler >= USE_TEXTURESTAGE_NUM )
		{
			return -1 ;
		}

		if( WrapMode == ( DWORD )GANDR.Device.State.TexAddressModeW[ Sampler ] &&
			GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			return 0 ;
		}

		DRAWSTOCKINFO

		GANDR.Device.State.TexAddressModeW[ Sampler ] = WrapMode ;
	}

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �e�N�X�`���[�̃A�h���b�V���O���[�h���Z�b�g����
extern int Graphics_Android_DeviceState_SetTextureAddressUVW( int AddressModeU, int AddressModeV, int AddressModeW, int Sampler )
{
	if( Graphics_Android_DeviceState_SetTextureAddressU( AddressModeU, Sampler ) < 0 )
	{
		return -1 ;
	}

	if( Graphics_Android_DeviceState_SetTextureAddressV( AddressModeV, Sampler ) < 0 )
	{
		return -1 ;
	}

	if( Graphics_Android_DeviceState_SetTextureAddressW( AddressModeW, Sampler ) < 0 )
	{
		return -1 ;
	}

	return 0 ;
}

// �W���`��p�̃e�N�X�`�����W�ϊ��s���萔�o�b�t�@�ɃZ�b�g����
static int Graphics_Android_DeviceState_SetNormalTextureAddressTransformMatrix_ConstBuffer( void )
{
	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uTexMat[ 0 ][ 0 ] = GANDR.Device.State.TextureAddressTransformMatrix.m[ 0 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uTexMat[ 0 ][ 1 ] = GANDR.Device.State.TextureAddressTransformMatrix.m[ 1 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uTexMat[ 0 ][ 2 ] = GANDR.Device.State.TextureAddressTransformMatrix.m[ 2 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uTexMat[ 0 ][ 3 ] = GANDR.Device.State.TextureAddressTransformMatrix.m[ 3 ][ 0 ] ;
	GANDR.Device.Shader.Constant.uTexMat[ 1 ][ 0 ] = GANDR.Device.State.TextureAddressTransformMatrix.m[ 0 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uTexMat[ 1 ][ 1 ] = GANDR.Device.State.TextureAddressTransformMatrix.m[ 1 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uTexMat[ 1 ][ 2 ] = GANDR.Device.State.TextureAddressTransformMatrix.m[ 2 ][ 1 ] ;
	GANDR.Device.Shader.Constant.uTexMat[ 1 ][ 3 ] = GANDR.Device.State.TextureAddressTransformMatrix.m[ 3 ][ 1 ] ;
	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �W���`��p�̃e�N�X�`���p�����[�^���ݒ肳��Ă��邩�ǂ����t���O�𗧂Ă�
	GANDR.Device.Shader.Constant.SetNormalTextureAddressTransformMatrix = TRUE ;

	// ����I��
	return 0 ;
}

// �e�N�X�`�����W�ϊ��s����Z�b�g����
extern int  Graphics_Android_DeviceState_SetTextureAddressTransformMatrix( int Use, MATRIX *Matrix )
{
	if( GANDR.Device.State.TextureAddressTransformMatrixUse == FALSE &&
		Use == FALSE && 
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	// �e�N�X�`�����W�ϊ��s����g�p���邩�ǂ�����ۑ�
	GANDR.Device.State.TextureAddressTransformMatrixUse = Use ;

	// �e�N�X�`�����W�ϊ��s����Z�b�g
	if( Use == TRUE )
	{
		GANDR.Device.State.TextureAddressTransformMatrix = *Matrix ;
	}
	else
	{
		CreateIdentityMatrix( &GANDR.Device.State.TextureAddressTransformMatrix ) ;
	}

	// �萔�o�b�t�@�ɔ��f����
	Graphics_Android_DeviceState_SetNormalTextureAddressTransformMatrix_ConstBuffer() ;

	return 0 ;
}

// �t�H�O��L���ɂ��邩�ǂ�����ݒ肷��( TRUE:�L��  FALSE:���� )
extern int  Graphics_Android_DeviceState_SetFogEnable( int Flag )
{
	if( Flag == GANDR.Device.State.FogEnable &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	GANDR.Device.State.FogEnable = Flag ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �t�H�O���[�h��ݒ肷��
extern int  Graphics_Android_DeviceState_SetFogVertexMode( int Mode /* DX_FOGMODE_NONE �� */ )
{
	if( Mode == GANDR.Device.State.FogMode &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	GANDR.Device.State.FogMode = Mode ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �t�H�O�J���[��ύX����
extern int  Graphics_Android_DeviceState_SetFogColor( unsigned int Color )
{
	if( Color == GANDR.Device.State.FogColor &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uFogColor[ 0 ] = ( ( Color >> 16 ) & 0xff ) / 255.0f ;
	GANDR.Device.Shader.Constant.uFogColor[ 1 ] = ( ( Color >>  8 ) & 0xff ) / 255.0f ;
	GANDR.Device.Shader.Constant.uFogColor[ 2 ] = ( ( Color >>  0 ) & 0xff ) / 255.0f ;
	GANDR.Device.Shader.Constant.uFogColor[ 3 ] = 1.0f ;
	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	GANDR.Device.State.FogColor = Color ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �t�H�O�̐F�ȊO�̒萔�����X�V����
static int Graphics_Android_DeviceState_UpdateConstantFogParam( void )
{
	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uFog[ 0 ] = GANDR.Device.State.FogEnd / ( GANDR.Device.State.FogEnd - GANDR.Device.State.FogStart ) ;
	GANDR.Device.Shader.Constant.uFog[ 1 ] = -1.0f / ( GANDR.Device.State.FogEnd - GANDR.Device.State.FogStart ) ;
	GANDR.Device.Shader.Constant.uFog[ 2 ] = GANDR.Device.State.FogDensity ;
	GANDR.Device.Shader.Constant.uFog[ 3 ] = 2.71828183f ;
	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �I��
	return 0 ;
}

// �t�H�O���n�܂鋗���ƏI�����鋗����ݒ肷��( 0.0f �` 1.0f )
extern int  Graphics_Android_DeviceState_SetFogStartEnd( float Start, float End )
{
	int UpdateFlag ;

	DRAWSTOCKINFO

	UpdateFlag = FALSE ;

	if( Start != GANDR.Device.State.FogStart ||
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == TRUE )
	{
		GANDR.Device.State.FogStart = Start ;
		UpdateFlag = TRUE ;
	}

	if( End != GANDR.Device.State.FogEnd ||
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == TRUE )
	{
		GANDR.Device.State.FogEnd = End ;
		UpdateFlag = TRUE ;
	}

	if( UpdateFlag )
	{
		// �萔�����X�V
		Graphics_Android_DeviceState_UpdateConstantFogParam() ;
	}

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �t�H�O�̖��x��ݒ肷��( 0.0f �` 1.0f )
extern int  Graphics_Android_DeviceState_SetFogDensity( float Density )
{
	if( Density == GANDR.Device.State.FogDensity &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	GANDR.Device.State.FogDensity = Density ;

	// �萔�����X�V
	Graphics_Android_DeviceState_UpdateConstantFogParam() ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// ���C�e�B���O�̗L���t���O���Z�b�g����
extern int  Graphics_Android_DeviceState_SetLighting( int UseFlag )
{
	if( UseFlag == GANDR.Device.State.Lighting &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	GANDR.Device.State.Lighting = UseFlag ;

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �ő�ٕ������Z�b�g����
extern	int		Graphics_Android_DeviceState_SetMaxAnisotropy( int MaxAnisotropy, int Sampler )
{
	int i ;
	int SetAnisotropy = MaxAnisotropy ;

	if( Sampler < 0 )
	{
		if( GANDR.Device.State.MaxAnisotropy == MaxAnisotropy &&
			GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			return 0 ;
		}

		GANDR.Device.State.MaxAnisotropy = MaxAnisotropy ;

		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
			{
				if( GANDR.Device.State.MaxAnisotropyDim[ i ] != SetAnisotropy )
				{
					break ;
				}
			}
			if( i == USE_TEXTURESTAGE_NUM )
			{
				return 0 ;
			}
		}

		DRAWSTOCKINFO

		for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
		{
			if( GANDR.Device.State.MaxAnisotropyDim[ i ] == SetAnisotropy &&
				GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
			{
				continue ;
			}

			GANDR.Device.State.MaxAnisotropyDim[ i ] = SetAnisotropy ;
		}
	}
	else
	{
		if( Sampler < 0 || Sampler >= USE_TEXTURESTAGE_NUM )
		{
			return 0 ;
		}

		GANDR.Device.State.MaxAnisotropy = -1 ;

		if( GANDR.Device.State.MaxAnisotropyDim[ Sampler ] == SetAnisotropy &&
			GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			return 0 ;
		}

		DRAWSTOCKINFO

		GANDR.Device.State.MaxAnisotropyDim[ Sampler ] = SetAnisotropy ;
	}

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �r���[�|�[�g���Z�b�g����
extern	int		Graphics_Android_DeviceState_SetViewport( RECT *Viewport )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( Viewport->left   == GANDR.Device.State.ViewportRect.left   &&
		Viewport->top    == GANDR.Device.State.ViewportRect.top    &&
		Viewport->right  == GANDR.Device.State.ViewportRect.right  &&
		Viewport->bottom == GANDR.Device.State.ViewportRect.bottom &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	// �����o��
	if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		DRAWSTOCKINFO
	}

	// �`����I�������Ă���
	Graphics_Android_RenderEnd() ;

	// �r���[�|�[�g�̐ݒ�𔽉f
    glViewport(
		Viewport->left,
		Viewport->top,
		Viewport->right  - Viewport->left,
		Viewport->bottom - Viewport->top
	) ;

	// �r���[�|�[�g�̏��̕ۑ�
	GANDR.Device.State.ViewportRect = *Viewport ;

	// �I��
	return 0 ;
}

// �r���[�|�[�g���Z�b�g����( �ȈՔ� )
extern	int		Graphics_Android_DeviceState_SetViewportEasy( int x1, int y1, int x2, int y2 )
{
	RECT Viewport ;

	Viewport.left   = x1 ;
	Viewport.top    = y1 ;
	Viewport.right  = x2 ;
	Viewport.bottom = y2 ;

	return Graphics_Android_DeviceState_SetViewport( &Viewport ) ;
}

// �`�惂�[�h�̃Z�b�g
extern	int		Graphics_Android_DeviceState_SetDrawMode( int DrawMode )
{
	if( GANDR.Device.State.DrawMode == DrawMode &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		DRAWSTOCKINFO
	}

	// �����_�����O�ݒ��ύX����
	switch( DrawMode )
	{
	case DX_DRAWMODE_BILINEAR :
		// �o�C���j�A�`��
		Graphics_Android_DeviceState_SetSampleFilterMode( GL_LINEAR_MIPMAP_LINEAR, -1 ) ;
		break ;

	case DX_DRAWMODE_NEAREST :
		// ��A���X�g�l�C�o�[
		Graphics_Android_DeviceState_SetSampleFilterMode( GL_NEAREST, -1 ) ;
		break ;

	case DX_DRAWMODE_ANISOTROPIC :
		// �ٕ����t�B���^�����O
		Graphics_Android_DeviceState_SetSampleFilterMode( GL_LINEAR_MIPMAP_LINEAR, -1 ) ;
		break ;

	default : return -1 ;
	}

	GANDR.Device.State.DrawMode                 = DrawMode ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �A���t�@�e�X�g�Ŏg�p�����r���[�h��ݒ肷��
extern	int		Graphics_Android_DeviceState_SetAlphaTestCmpMode( int AlphaTestCmpMode /* DX_CMP_NEVER �Ȃ� */ )
{
	if( GANDR.Device.State.AlphaTestCmpMode == AlphaTestCmpMode &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	// �l��ۑ�
	GANDR.Device.State.AlphaTestCmpMode = AlphaTestCmpMode ;

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uATestCmpMode = AlphaTestCmpMode ;

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �I��
	return 0 ;
}

// �A���t�@�e�X�g�Ŏg�p����Q�ƒl��ݒ肷��
extern	int		Graphics_Android_DeviceState_SetAlphaTestRef( int AlphaTestRef )
{
	if( GANDR.Device.State.AlphaTestRef == AlphaTestRef &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	// �l��ۑ�
	GANDR.Device.State.AlphaTestRef = AlphaTestRef ;

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uATestRef = AlphaTestRef / 255.0f ;

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �I��
	return 0 ;
}

// �J���[�ɃA���t�@�l����Z���邩�ǂ�����ݒ肷��
extern	int		Graphics_Android_DeviceState_SetMulAlphaColor( int UseMulAlphaColor )
{
	DRAWSTOCKINFO

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uMulAlphaColor = UseMulAlphaColor ? 1.0f : 0.0f ;

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �I��
	return 0 ;
}

// �w�i�F��ݒ肷��
extern	int		Graphics_Android_DeviceState_SetBackgroundColor( int Red, int Green, int Blue, int Alpha )
{
	float RedF ;
	float GreenF ;
	float BlueF ;
	float AlphaF ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( GANDR.Device.State.BackgroundColor.r == Red &&
		GANDR.Device.State.BackgroundColor.g == Green &&
		GANDR.Device.State.BackgroundColor.b == Blue &&
		GANDR.Device.State.BackgroundColor.a == Alpha &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	RedF   = ( float )Red   / 255.0f ;
	GreenF = ( float )Green / 255.0f ;
	BlueF  = ( float )Blue  / 255.0f ;
	AlphaF = ( float )Alpha / 255.0f ;

	DRAWSTOCKINFO

	glClearColor( RedF, GreenF, BlueF, AlphaF ) ;

	GANDR.Device.State.BackgroundColor.r = ( BYTE )Red ;
	GANDR.Device.State.BackgroundColor.g = ( BYTE )Green ;
	GANDR.Device.State.BackgroundColor.b = ( BYTE )Blue ;
	GANDR.Device.State.BackgroundColor.a = ( BYTE )Alpha ;
	
	// �I��
	return 0 ;
}

// Factor Color ��ݒ肷��
extern	int		Graphics_Android_DeviceState_SetFactorColor( const DX_ANDR_SHADER_FLOAT4 *FactorColor )
{
	if( GANDR.Device.Shader.Constant.uFactorColor[ 0 ] == (*FactorColor)[ 0 ] &&
		GANDR.Device.Shader.Constant.uFactorColor[ 1 ] == (*FactorColor)[ 1 ] &&
		GANDR.Device.Shader.Constant.uFactorColor[ 2 ] == (*FactorColor)[ 2 ] &&
		GANDR.Device.Shader.Constant.uFactorColor[ 3 ] == (*FactorColor)[ 3 ] &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uFactorColor[ 0 ] = (*FactorColor)[ 0 ] ;
	GANDR.Device.Shader.Constant.uFactorColor[ 1 ] = (*FactorColor)[ 1 ] ;
	GANDR.Device.Shader.Constant.uFactorColor[ 2 ] = (*FactorColor)[ 2 ] ;
	GANDR.Device.Shader.Constant.uFactorColor[ 3 ] = (*FactorColor)[ 3 ] ;

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �I��
	return 0 ;
}

// �g�D�[�������_�����O�̗֊s���̑�����ݒ肷��
extern int Graphics_Android_DeviceState_SetToonOutLineSize( float Size )
{
	if( GANDR.Device.Shader.Constant.uToonOutLineSize[ 0 ] == Size &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	// �萔�f�[�^�ɔ��f
	GANDR.Device.Shader.Constant.uToonOutLineSize[ 0 ] = Size ;
	GANDR.Device.Shader.Constant.uToonOutLineSize[ 1 ] = Size ;
	GANDR.Device.Shader.Constant.uToonOutLineSize[ 2 ] = Size ;
	GANDR.Device.Shader.Constant.uToonOutLineSize[ 3 ] = Size ;

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �I��
	return 0 ;
}

// �`��u�����h���[�h�̃Z�b�g
extern	int		Graphics_Android_DeviceState_SetBlendMode( int BlendMode, int NotWriteAlphaChannelFlag )
{
	DX_ANDROID_RENDER_BLEND_INFO *BlendInfo ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( GANDR.Device.State.BlendMode == BlendMode &&
		GANDR.Device.State.NotWriteAlphaChannelFlag == NotWriteAlphaChannelFlag &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	DRAWSTOCKINFO

	GANDR.Device.State.BlendMode = BlendMode ;
	GANDR.Device.State.NotWriteAlphaChannelFlag = NotWriteAlphaChannelFlag ;

	BlendInfo = &g_DefaultBlendDescArray[ BlendMode ] ;

	if( BlendInfo->BlendEnable )
	{
		glEnable( GL_BLEND ) ;
		if( GANDR.Device.State.NotWriteAlphaChannelFlag )
		{
			glBlendEquationSeparate(
				BlendInfo->ColorBlendFunc,
				GL_FUNC_ADD
			) ;
			glBlendFuncSeparate(
				BlendInfo->ColorSourceMul, BlendInfo->ColorDestMul,
				GL_ZERO, GL_ONE
			) ;
		}
		else
		{
			glBlendEquationSeparate(
				BlendInfo->ColorBlendFunc,
				BlendInfo->AlphaBlendFunc
			) ;
			glBlendFuncSeparate(
				BlendInfo->ColorSourceMul, BlendInfo->ColorDestMul,
				BlendInfo->AlphaSourceMul, BlendInfo->AlphaDestMul
			) ;
		}
	}
	else
	{
		glDisable( GL_BLEND ) ;
	}

	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	return 0 ;
}

// �`��Ώۂ̕ύX
extern	int		Graphics_Android_DeviceState_SetRenderTarget( GLuint TargetFrameBuffer, GLuint TargetFrameBufferWidth, GLuint TargetFrameBufferHeight )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( GANDR.Device.State.TargetFrameBuffer == TargetFrameBuffer &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck  == FALSE )
	{
		return 0 ;
	}

	// ���_�����o��
	DRAWSTOCKINFO

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// �����_�����O�^�[�Q�b�g�̕ۑ�
	GANDR.Device.State.TargetFrameBuffer = TargetFrameBuffer ;
	GANDR.Device.State.TargetFrameBufferWidth = TargetFrameBufferWidth ;
	GANDR.Device.State.TargetFrameBufferHeight = TargetFrameBufferHeight ;

	// �����_�����O�^�[�Q�b�g�̕ύX
	glBindFramebuffer( GL_FRAMEBUFFER, TargetFrameBuffer ) ;

	// �r���[�|�[�g�̐ݒ�l���X�V
	if( TargetFrameBuffer != 0 )
	{
		Graphics_Android_DeviceState_SetViewportEasy( 0, 0, TargetFrameBufferWidth, TargetFrameBufferHeight ) ;
	}

	// �I��
	return  0 ;
}

// �g�p����V�F�[�_�[��ύX����
extern	int	Graphics_Android_DeviceState_SetShader( GRAPHICS_ANDROID_SHADER *Shader, int NormalShader )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( GANDR.Device.State.SetShader == Shader &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	if( Shader != NULL )
	{
	    glUseProgram( Shader->Shader ) ;
	}

	GANDR.Device.State.SetShader          = Shader ;
	GANDR.Device.State.SetNormalShader    = NormalShader ;
	if( NormalShader == FALSE )
	{
		GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;
	}

	// �I��
	return 0 ;
}

// �V�F�[�_�[�̎g�p���~�߂�
extern	int		Graphics_Android_DeviceState_ResetShader( int SetNormalShaderCancel )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( GANDR.Device.State.SetNormalShader &&
		SetNormalShaderCancel &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE &&
		GANDR.Device.State.SetShader == NULL )
	{
		return 0 ;
	}

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

    glUseProgram( 0 ) ;

	GANDR.Device.State.SetShader = NULL ;

	GANDR.Device.State.SetNormalShader    = FALSE ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �V�F�[�_�[�� Uniform ���X�V����
extern int Graphics_Android_DeviceState_UpdateShaderUniform( GRAPHICS_ANDROID_SHADER *Shader, int LightNum, int UseLocalWorldMatrixUniformNum )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// ���݂̃V�F�[�_�[�ɓK�p����Ă��� Uniform �X�V�ԍ��ƁA
	// �O���[�o���Ŏ����Ă���V�F�[�_�[�̍X�V�ԍ�����v���Ă���ꍇ�͉��������ɏI��
	if( Shader == NULL ||
		( Shader->ApplyUniformUpdateCount == GANDR.Device.Shader.Constant.UpdateCount &&
		  GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE ) )
	{
		return 0 ;
	}

	// �V�F�[�_�[���g�p��ԂɃZ�b�g
	glUseProgram( Shader->Shader ) ;

	// �V�F�[�_�[�ɃO���[�o���� Uniform ��K�p����

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SRC_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SRC_TEX ], 0 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_BLEND_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_BLEND_TEX ], 1 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_DIF_MAP_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_DIF_MAP_TEX ], 0 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_NRM_MAP_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_NRM_MAP_TEX ], 1 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SPC_MAP_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SPC_MAP_TEX ], 2 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_TOON_DIF_GRAD_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_TOON_DIF_GRAD_TEX ], 3 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_TOON_SPC_GRAD_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_TOON_SPC_GRAD_TEX ], 4 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_TOON_SPHERE_MAP_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_TOON_SPHERE_MAP_TEX ], 5 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SHADOW_MAP0_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SHADOW_MAP0_TEX ], 8 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SHADOW_MAP1_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SHADOW_MAP0_TEX ], 9 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SHADOW_MAP2_TEX ] != 0xffff )
	{
		glUniform1i( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SHADOW_MAP0_TEX ], 10 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_AMB_EMI ] != 0xffff )
	{
		UNIFORM_SET_FLOAT4( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_AMB_EMI ], GANDR.Device.Shader.Constant.uAmb_Emi ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_DIF ] != 0xffff )
	{
		UNIFORM_SET_FLOAT4( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_DIF ], GANDR.Device.Shader.Constant.uMatDif ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_SPC ] != 0xffff )
	{
		UNIFORM_SET_FLOAT4( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_SPC ], GANDR.Device.Shader.Constant.uMatSpc ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_POW ] != 0xffff )
	{
		UNIFORM_SET_FLOAT1( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_POW ], GANDR.Device.Shader.Constant.uMatPow ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM0 ] != 0xffff )
	{
		UNIFORM_SET_FLOAT1( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM0 ], GANDR.Device.Shader.Constant.uMatTypeParam0 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM1 ] != 0xffff )
	{
		UNIFORM_SET_FLOAT1( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM1 ], GANDR.Device.Shader.Constant.uMatTypeParam1 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM2 ] != 0xffff )
	{
		UNIFORM_SET_FLOAT1( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MAT_TYPE_PARAM2 ], GANDR.Device.Shader.Constant.uMatTypeParam2 ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_POS ] != 0xffff )
	{
		glUniform3fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_POS ], LightNum, GANDR.Device.Shader.Constant.uLightPos[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_DIR ] != 0xffff )
	{
		glUniform3fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_DIR ], LightNum, GANDR.Device.Shader.Constant.uLightDir[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_DIF ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_DIF ], LightNum, GANDR.Device.Shader.Constant.uLightDif[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_SPC ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_SPC ], LightNum, GANDR.Device.Shader.Constant.uLightSpc[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_AMB ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_AMB ], LightNum, GANDR.Device.Shader.Constant.uLightAmb[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_RANGE_FALLOFF_AT0_AT1 ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_RANGE_FALLOFF_AT0_AT1 ], LightNum, GANDR.Device.Shader.Constant.uLightRange_FallOff_AT0_AT1[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_AT2_SPOTP0_SPOTP1 ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LIGHT_AT2_SPOTP0_SPOTP1 ], LightNum, GANDR.Device.Shader.Constant.uLightAT2_SpotP0_SpotP1[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_ANTI_VIEW_PORT_MAT ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_ANTI_VIEW_PORT_MAT ], 4, GANDR.Device.Shader.Constant.uAntiVPMat[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_VIEW_MAT ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_VIEW_MAT ], 3, GANDR.Device.Shader.Constant.uViewMat[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_PROJ_MAT ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_PROJ_MAT ], 4, GANDR.Device.Shader.Constant.uProjMat[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_FOG ] != 0xffff )
	{
		UNIFORM_SET_FLOAT4( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_FOG ], GANDR.Device.Shader.Constant.uFog ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_TOON_OUTLINE_SIZE ] != 0xffff )
	{
		UNIFORM_SET_FLOAT4( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_TOON_OUTLINE_SIZE ], GANDR.Device.Shader.Constant.uToonOutLineSize ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_DIFSRC_SPCSRC_MULSPECOL ] != 0xffff )
	{
		UNIFORM_SET_FLOAT4( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_DIFSRC_SPCSRC_MULSPECOL ], GANDR.Device.Shader.Constant.uDifSrc_SpeSrc_MulSpeCol ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SM_LVP_MAT ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SM_LVP_MAT ], 12, GANDR.Device.Shader.Constant.uSMLVPMat[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_TEX_MAT ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_TEX_MAT ], 6, GANDR.Device.Shader.Constant.uTexMat[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LW_MAT ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_LW_MAT ], UseLocalWorldMatrixUniformNum, GANDR.Device.Shader.Constant.uLWMat[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MUL_ALPHA_COLOR ] != 0xffff )
	{
		UNIFORM_SET_FLOAT1( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_MUL_ALPHA_COLOR ], GANDR.Device.Shader.Constant.uMulAlphaColor ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_ALPHA_TEST_REF ] != 0xffff )
	{
		UNIFORM_SET_FLOAT1( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_ALPHA_TEST_REF ], GANDR.Device.Shader.Constant.uATestRef ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_ALPHA_TEST_CMPMODE ] != 0xffff )
	{
		UNIFORM_SET_INT1( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_ALPHA_TEST_CMPMODE ], GANDR.Device.Shader.Constant.uATestCmpMode ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_FOG_COLOR ] != 0xffff )
	{
		UNIFORM_SET_FLOAT4( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_FOG_COLOR ], GANDR.Device.Shader.Constant.uFogColor ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_FACTOR_COLOR ] != 0xffff )
	{
		UNIFORM_SET_FLOAT4( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_FACTOR_COLOR ], GANDR.Device.Shader.Constant.uFactorColor ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_IGNORE_TEXTURE_COLOR ] != 0xffff )
	{
		UNIFORM_SET_FLOAT4( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_IGNORE_TEXTURE_COLOR ], GANDR.Device.Shader.Constant.uIgnoreTextureColor ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SHADOWMAP_LIGHT_ENABLE ] != 0xffff )
	{
		glUniform4fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SHADOWMAP_LIGHT_ENABLE ], 3, GANDR.Device.Shader.Constant.uShadowMapLightEnable[ 0 ] ) ;
	}

	if( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SHADOWMAP_DADJ_GRAD ] != 0xffff )
	{
		glUniform2fv( Shader->UniformIndex[ ANDROID_SHADER_UNIFORM_SHADOWMAP_DADJ_GRAD ], 3, GANDR.Device.Shader.Constant.uShadowMap_DAdj_Grad[ 0 ] ) ;
	}

	// �K�p�����ԍ����X�V����
	Shader->ApplyUniformUpdateCount = GANDR.Device.Shader.Constant.UpdateCount ;

	// �I��
	return 0 ;
}

// �w��̃V�F�[�_�[�̒��_�t�H�[�}�b�g�̒��_�f�[�^�̕`�揀�����s��
extern int Graphics_Android_DeviceState_SetupShaderVertexData( GRAPHICS_ANDROID_SHADER *Shader, VERTEXBUFFER_INPUT_INFO_ANDR *VertexInputInfo, const void *VertexData, GLuint VertexBuffer )
{
	int i ;
	int UseAttr[ ANDROID_VERTEX_ATTR_NUM ] = { 0 } ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// ���_�f�[�^�������ȏꍇ�͒��_�o�b�t�@���g�p����
	if( VertexData == NULL )
	{
		// ���_�o�b�t�@���Z�b�g
		glBindBuffer( GL_ARRAY_BUFFER, VertexBuffer ) ;
	}
	else
	{
		// ���_�o�b�t�@���g�p���Ȃ��ꍇ�͒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�͖����ɂ���
		glBindBuffer( GL_ARRAY_BUFFER, 0 ) ;
	}

	for( i = 0 ; i < VertexInputInfo->ElementInfoNum ; i ++ )
	{
		VERTEXBUFFER_INPUT_ELEMENT_INFO_ANDR *Element = &VertexInputInfo->ElementInfo[ i ] ;

		if( Element->ElementBase == ANDROID_VERTEX_ATTR_OTHER ||
			Shader->AttributeIndex[ Element->ElementBase ] == 0xffff )
		{
			continue ;
		}

		VERTEXBUFFER_INPUT_ELEMENT_INFO_BASE_ANDR *ElementBase = &g_VertexElementInfoBase[ Element->ElementBase ] ;

		UseAttr[ Shader->AttributeIndex[ Element->ElementBase ] ] = TRUE ;
		if( GANDR.Device.State.VertexAttrEnable[ Shader->AttributeIndex[ Element->ElementBase ] ] == FALSE )
		{
			GANDR.Device.State.VertexAttrEnable[ Shader->AttributeIndex[ Element->ElementBase ] ] = TRUE ;
			glEnableVertexAttribArray( Shader->AttributeIndex[ Element->ElementBase ] ) ;
		}

		glVertexAttribPointer(
			Shader->AttributeIndex[ Element->ElementBase ],
			ElementBase->Size,
			ElementBase->DataFormat,
			ElementBase->Normalized,
			VertexInputInfo->VertexDataSize,
			( BYTE * )VertexData + Element->Offset
		) ;
	}

	// �g�p����Ă��Ȃ��v�f�͖���������
	for( i = 0 ; i < ANDROID_VERTEX_ATTR_NUM ; i ++ )
	{
		if( UseAttr[ i ] == FALSE && GANDR.Device.State.VertexAttrEnable[ i ] == TRUE )
		{
			GANDR.Device.State.VertexAttrEnable[ i ] = FALSE ;
			glDisableVertexAttribArray( i ) ;
		}
	}

	// �I��
	return 0 ;
}

// �g�p���钸�_�o�b�t�@��ύX����
extern	int		Graphics_Android_DeviceState_SetVertexBuffer( GLuint VertexBuffer )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( GANDR.Device.State.SetVertexBuffer == VertexBuffer &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

    glBindBuffer( GL_ARRAY_BUFFER, VertexBuffer ) ;

	GANDR.Device.State.SetVertexBuffer = VertexBuffer ;

	// �I��
	return 0 ;
}

// �V�F�[�_�[�Ŏg�p����e�N�X�`����ύX����
extern int Graphics_Android_DeviceState_SetTexture( int SlotIndex, GRAPHICS_ANDROID_TEXTURE *Texture )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( SlotIndex < 0 || SlotIndex >= USE_TEXTURESTAGE_NUM )
	{
		return -1 ;
	}

	if( Texture == GANDR.Device.State.SetTexture[ SlotIndex ] &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	GANDR.Device.State.SetTexture[ SlotIndex ] = Texture ;

	glActiveTexture( g_TextureEnum[ SlotIndex ] ) ;
	if( Texture == NULL )
	{
		glBindTexture( GL_TEXTURE_2D, 0 ) ;
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D, Texture->TextureBuffer ) ;

		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck )
		{
			Texture->WrapS = GANDR.Device.State.TexAddressModeU[ SlotIndex ] ;
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Texture->WrapS ) ;

			Texture->WrapT = GANDR.Device.State.TexAddressModeV[ SlotIndex ] ;
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Texture->WrapT ) ;

			Texture->MagFilter = GANDR.Device.State.TexMagFilter[ SlotIndex ] ;
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Texture->MagFilter ) ;

			GLenum MinFilterTmp = GANDR.Device.State.TexMinFilter[ SlotIndex ] ;
			if( Texture->MipMapCount <= 1 && MinFilterTmp == GL_LINEAR_MIPMAP_LINEAR )
			{
				MinFilterTmp = GL_LINEAR ;
			}
			Texture->MinFilter = MinFilterTmp ;
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Texture->MinFilter ) ;
		}
		else
		{
			if( Texture->WrapS != GANDR.Device.State.TexAddressModeU[ SlotIndex ] )
			{
				Texture->WrapS = GANDR.Device.State.TexAddressModeU[ SlotIndex ] ;
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Texture->WrapS ) ;
			}
			if( Texture->WrapT != GANDR.Device.State.TexAddressModeV[ SlotIndex ] )
			{
				Texture->WrapT = GANDR.Device.State.TexAddressModeV[ SlotIndex ] ;
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Texture->WrapT ) ;
			}
			if( Texture->MagFilter != GANDR.Device.State.TexMagFilter[ SlotIndex ] )
			{
				Texture->MagFilter = GANDR.Device.State.TexMagFilter[ SlotIndex ] ;
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Texture->MagFilter ) ;
			}
			if( Texture->MinFilter != GANDR.Device.State.TexMinFilter[ SlotIndex ] )
			{
				GLenum MinFilterTmp = GANDR.Device.State.TexMinFilter[ SlotIndex ] ;
				if( Texture->MipMapCount <= 1 && MinFilterTmp == GL_LINEAR_MIPMAP_LINEAR )
				{
					MinFilterTmp = GL_LINEAR ;
				}
				if( Texture->MinFilter != MinFilterTmp )
				{
					Texture->MinFilter = MinFilterTmp ;
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Texture->MinFilter ) ;
				}
			}
		}
	}

	// �I��
	return 0 ;
}

// �W���`��̏������s��
extern	int		Graphics_Android_DeviceState_NormalDrawSetup( void )
{
	int											IgnoreTextureAlpha ;
	int											NextBlendMode ;
	int											UseFloatFactorColor = FALSE ;
	DX_ANDR_SHADER_FLOAT4						FloatFactorColor ;
	int											AlphaTestRef = 0 ;
	int											AlphaTestCmpMode = 0 ;
	GRAPHICS_ANDROID_TEXTURE					*UseTexture[ USE_TEXTURESTAGE_NUM ] ;
	int											UseTextureNum = 0 ;
	GRAPHICS_HARDWARE_ANDROID_SHADER_BASE		*SB  = &GANDR.Device.Shader.Base ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_BASE	*SCB = &GANDR.ShaderCode.Base ;
	GLuint										*VS			= NULL ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*VSAddress	= NULL ;
	GLuint										*FS			= NULL ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*FSAddress	= NULL ;
	GRAPHICS_ANDROID_SHADER						**UseShader	= NULL ;

	// �e�N�X�`�����ύX���ꂽ�A�t���O��|��
	GANDR.Device.DrawSetting.ChangeTextureFlag = FALSE ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �p�����[�^���ύX���ꂽ�A�t���O��|��
	GANDR.Device.DrawSetting.ChangeBlendParamFlag = FALSE ;

	// �u�����h���[�h�̌���
	{
		NextBlendMode = GANDR.Device.DrawSetting.BlendMode ;
		switch( GANDR.Device.DrawSetting.BlendMode )
		{
		case DX_BLENDMODE_SUB :
			// ���Z�u�����h�̏ꍇ��14�Ԗڂ̃u�����h���[�h���g�p����
			NextBlendMode = DX_BLENDMODE_SUB1 ;
			break ;

		case DX_BLENDMODE_NOBLEND :
			// �`���Ƀ��l������ꍇ�� DX_BLENDMODE_NOBLEND �ł��u�����h���[�h�� DX_BLENDMODE_SRCCOLOR �ɂ���
			if( GSYS.DrawSetting.AlphaChDrawMode )
			{
				NextBlendMode = DX_BLENDMODE_SRCCOLOR ;
			}

			// �`�挳�摜�Ƀ��`�����l��������ꍇ��u�����h�摜�̗L���ȂǏ�������� DX_BLENDMODE_ALPHA ���g�p����
			if( GANDR.Device.DrawSetting.RenderTexture != NULL )
			{
				if( GANDR.Device.DrawSetting.BlendTexture != NULL )
				{
					switch( GANDR.Device.DrawSetting.BlendGraphType )
					{
					case DX_BLENDGRAPHTYPE_NORMAL :
					case DX_BLENDGRAPHTYPE_ALPHA :
						if( GANDR.Device.DrawSetting.AlphaTestValidFlag    == TRUE ||
							GANDR.Device.DrawSetting.AlphaChannelValidFlag == TRUE )
						{
							NextBlendMode = DX_BLENDMODE_ALPHA ;
						}
						break ;

					case DX_BLENDGRAPHTYPE_WIPE :
						NextBlendMode = DX_BLENDMODE_ALPHA ;
						break ;
					}
				}
				else
				{
					if( GANDR.Device.DrawSetting.AlphaChannelValidFlag == TRUE )
					{
						NextBlendMode = DX_BLENDMODE_ALPHA ;
					}
				}
			}
			break ;
		}
	}
	
	// �J�����g�e�N�X�`���������ꍇ�Ƃ���ꍇ�ŕ���
	if( GANDR.Device.DrawSetting.RenderTexture == NULL )
	{
		// �J�����g�e�N�X�`���������ꍇ�͐��┠�̕`��Ɣ��f�A�e�N�X�`���X�e�[�W�͖����ɂ���

		// �Ƃ肠�����`�揈�����s��
		GANDR.Device.DrawInfo.BlendMaxNotDrawFlag = FALSE ;

		// �A���t�@�e�X�g�p�����[�^���L���ȏꍇ�͂����D�悷��
		if( GANDR.Device.DrawSetting.AlphaTestMode != -1 )
		{
			GANDR.Device.State.AlphaTestEnable = TRUE ;
			AlphaTestCmpMode = GANDR.Device.DrawSetting.AlphaTestMode ;
			AlphaTestRef     = GANDR.Device.DrawSetting.AlphaTestParam ;
		}
		else
		{
			GANDR.Device.State.AlphaTestEnable = FALSE ;
		}

		// ���_�^�C�v�̃Z�b�g
		GANDR.Device.DrawInfo.VertexType = VERTEXTYPE_NOTEX ;

		// �g�p����V�F�[�_�[�̎擾
		GANDR.Device.State.AlphaTestModeShaderIndex = Graphics_Android_Shader_GetAlphaTestModeIndex( GANDR.Device.State.AlphaTestEnable, AlphaTestCmpMode ) ;

		VS        =  &SB->BaseSimple_VS     [ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ] ;
		VSAddress = &SCB->BaseSimple_VS_Code[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ] ;

		FS        = & SB->BaseNoneTex_FS     [ g_DefaultBlendDescArray[ NextBlendMode ].RenderType ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;
		FSAddress = &SCB->BaseNoneTex_FS_Code[ g_DefaultBlendDescArray[ NextBlendMode ].RenderType ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;

		UseShader = &SB->BaseNoneTex_Shader[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ][ g_DefaultBlendDescArray[ NextBlendMode ].RenderType ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;
	}
	else
	{
		// �J�����g�e�N�X�`��������ꍇ�̓e�N�X�`���X�e�[�W�u�����h�e�[�u������l���擾����

		// �g�p����e�N�X�`���u�����h�X�e�[�W�X�e�[�^�X�e�[�u���̃C���f�b�N�X���Z�b�g
		IgnoreTextureAlpha = 1 ;
		if( GANDR.Device.DrawSetting.AlphaChannelValidFlag ||
			GANDR.Device.DrawSetting.AlphaTestValidFlag    ||
			( GANDR.Device.State.DepthEnable &&
			  GANDR.Device.DrawSetting.BlendTexture == NULL ) )
		{
			IgnoreTextureAlpha = 0 ;
		}

		// �u�����h�e�N�X�`���[���g�p���邩�ǂ����ŕ���
		if( GANDR.Device.DrawSetting.BlendTexture != NULL )
		{
			int RenderType ;

			// �u�����h�e�N�X�`���[������ꍇ�� AlphaTestValidFlag �͖���

			// �g�p����e�[�u���̃C���f�b�N�X������o��
			RenderType = g_DefaultBlendDescArray[ NextBlendMode ].RenderType ;

			// �g�p����e�N�X�`���[�A�h���X���Z�b�g
			UseTexture[ 0 ] = GANDR.Device.DrawSetting.RenderTexture ;
			UseTexture[ 1 ] = GANDR.Device.DrawSetting.BlendTexture ;
			UseTextureNum = 2 ;

			// ���_�^�C�v�̃Z�b�g
			GANDR.Device.DrawInfo.VertexType = VERTEXTYPE_BLENDTEX ;

			// �u�����h�^�C�v�ɂ���ď����𕪊�
			switch( GANDR.Device.DrawSetting.BlendGraphType )
			{
			case DX_BLENDGRAPHTYPE_NORMAL :
				// �Ƃ肠�����`�揈�����s��
				GANDR.Device.DrawInfo.BlendMaxNotDrawFlag = FALSE ;

				// �A���t�@�e�X�g�p�����[�^���L���ȏꍇ�͂����D�悷��
				if( GANDR.Device.DrawSetting.AlphaTestMode != -1 )
				{
					GANDR.Device.State.AlphaTestEnable = TRUE ;
					AlphaTestCmpMode = GANDR.Device.DrawSetting.AlphaTestMode ;
					AlphaTestRef     = GANDR.Device.DrawSetting.AlphaTestParam ;
				}
				else
				{
					// ���������L���ȏꍇ�̓��l���O�̏ꍇ�̂ݕ\������Ȃ��悤�ɂ���
					if( GANDR.Device.DrawSetting.AlphaTestValidFlag == TRUE ||
						g_DefaultBlendDescArray[ NextBlendMode ].BlendEnable == TRUE ||
						GANDR.Device.DrawSetting.AlphaChannelValidFlag == TRUE )
					{
						GANDR.Device.State.AlphaTestEnable = TRUE ;
						AlphaTestRef     = 0 ;
						AlphaTestCmpMode = DX_CMP_GREATER ;
					}
					else
					{
						GANDR.Device.State.AlphaTestEnable = FALSE ;
					}
				}

				// �N���X�t�F�[�h����ݒ肷��
				UseFloatFactorColor = TRUE ;
				FloatFactorColor[ 0 ] = 1.0f ;
				FloatFactorColor[ 1 ] = 1.0f ;
				FloatFactorColor[ 2 ] = 1.0f ;
				FloatFactorColor[ 3 ] = GANDR.Device.DrawSetting.BlendGraphFadeRatio / 255.0f ;

				// �g�p����V�F�[�_�[���Z�b�g
				GANDR.Device.State.AlphaTestModeShaderIndex = Graphics_Android_Shader_GetAlphaTestModeIndex( GANDR.Device.State.AlphaTestEnable, AlphaTestCmpMode ) ;

				VS        =  &SB->BaseSimple_VS     [ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ] ;
				VSAddress = &SCB->BaseSimple_VS_Code[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ] ;

				FS        =  &SB->BaseUseTex_FS     [ 1 ][ RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;
				FSAddress = &SCB->BaseUseTex_FS_Code[ 1 ][ RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;

				UseShader = &SB->BaseUseTex_Shader[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ][ 1 ][ RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;
				break ;

			case DX_BLENDGRAPHTYPE_WIPE :
				// �u�����h���E�l���ő�̏ꍇ�͉����`�悵�Ȃ�
				GANDR.Device.DrawInfo.BlendMaxNotDrawFlag = GANDR.Device.DrawSetting.BlendGraphBorderParam == 255 ? TRUE : FALSE ;

				// float�^�� FactorColor ���g�p����
				UseFloatFactorColor = TRUE ;
				FloatFactorColor[ 0 ] = 0.0f ;
				FloatFactorColor[ 1 ] = 0.0f ;
				FloatFactorColor[ 2 ] = 0.0f ;
				FloatFactorColor[ 3 ] = 0.0f ;

				// ���E�͈͂��P�ȉ����ǂ����ŏ����𕪊�
				if( GANDR.Device.DrawSetting.BlendGraphBorderRange <= 1 )
				{
					// �����͂����w�Ǘ�O���� -------------------------------------------

					// ���e�X�g���g�p����
					GANDR.Device.State.AlphaTestEnable = TRUE ;
					AlphaTestRef     = GANDR.Device.DrawSetting.BlendGraphBorderParam ;
					AlphaTestCmpMode = DX_CMP_GREATEREQUAL ;

					// ���u�����h�@�\�n�e�e
					NextBlendMode = DX_BLENDMODE_NOBLEND ;

					// �������郿�l�͖���
					FloatFactorColor[ 3 ] = 0.0f ;
					FloatFactorColor[ 2 ] = 1.0f ;

					// �����摜�����`�����l�����g�p���Ă��āA���� BlendGraphBorderParam �� 0 �������� AlphaRef ���O�ɂ��Ȃ�
					if( ( GANDR.Device.DrawSetting.AlphaChannelValidFlag ||
						  GANDR.Device.DrawSetting.AlphaTestValidFlag ) &&
						GANDR.Device.DrawSetting.BlendGraphBorderParam == 0 )
					{
						AlphaTestRef = 1 ;
					}
				}
				else
				{
					int p ;
				
					// ���u�����h�ɂ��e�N�X�`���u�����h

					// ���e�X�g�͍s��Ȃ�
					GANDR.Device.State.AlphaTestEnable = FALSE ;

					// ���E�͈͂ɂ���ĂS�i�K
					if( GANDR.Device.DrawSetting.BlendGraphBorderRange <= 64 )
					{
						// �~�S

						p = 1280 - GANDR.Device.DrawSetting.BlendGraphBorderParam * 1280 / 255 ; 

						// �u�����h�e�N�X�`���̃u�����h�l�ɂ���č����p�����[�^��ύX
						if( p < 1024 )
						{
							FloatFactorColor[ 3 ] = - ( float )( 255 - p * 255 / 1024 ) / 255.0f ;
						}
						else
						{
							FloatFactorColor[ 3 ] =   ( float )( 64 * ( p - 1024 ) / 256 ) / 255.0f ;
						}

						FloatFactorColor[ 2 ] = 4.0f ;
					}
					else
					if( GANDR.Device.DrawSetting.BlendGraphBorderRange <= 128 )
					{
						// �~�Q

						p = 768 - GANDR.Device.DrawSetting.BlendGraphBorderParam * 768 / 255 ; 

						// �u�����h�e�N�X�`���̃u�����h�l�ɂ���č����p�����[�^��ύX
						if( p < 512 )
						{
							FloatFactorColor[ 3 ] = - ( float )( 255 - p * 255 / 512 ) / 255.0f ;
						}
						else
						{
							FloatFactorColor[ 3 ] =   ( float )( 128 * ( p - 512 ) / 256 ) / 255.0f ;
						}

						FloatFactorColor[ 2 ] = 2.0f ;
					}
					else
					{
						// �~�P

						p = 512 - GANDR.Device.DrawSetting.BlendGraphBorderParam * 512 / 255 ; 

						// �u�����h�e�N�X�`���̃u�����h�l�ɂ���č����p�����[�^��ύX
						if( p < 256 )
						{
							FloatFactorColor[ 3 ] = - ( float )( 255 - p * 255 / 256 ) / 255.0f ;
						}
						else
						{
							FloatFactorColor[ 3 ] =   ( float )( 255 * ( p - 256 ) / 256 ) / 255.0f ;
						}

						FloatFactorColor[ 2 ] = 1.0f ;
					}
				}

				// �g�p����V�F�[�_�[���Z�b�g
				GANDR.Device.State.AlphaTestModeShaderIndex = Graphics_Android_Shader_GetAlphaTestModeIndex( GANDR.Device.State.AlphaTestEnable, AlphaTestCmpMode ) ;

				VS        =  &SB->BaseSimple_VS     [ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ] ;
				VSAddress = &SCB->BaseSimple_VS_Code[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ] ;

				FS        =  &SB->BaseUseTex_FS     [ 2 ][ RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;
				FSAddress = &SCB->BaseUseTex_FS_Code[ 2 ][ RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;

				UseShader = &SB->BaseUseTex_Shader[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ][ 2 ][ RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;
				break ;

			case DX_BLENDGRAPHTYPE_ALPHA :
				// �Ƃ肠�����`�揈�����s��
				GANDR.Device.DrawInfo.BlendMaxNotDrawFlag = FALSE ;

				// �A���t�@�e�X�g�p�����[�^���L���ȏꍇ�͂����D�悷��
				if( GANDR.Device.DrawSetting.AlphaTestMode != -1 )
				{
					GANDR.Device.State.AlphaTestEnable = TRUE ;
					AlphaTestCmpMode = GANDR.Device.DrawSetting.AlphaTestMode ;
					AlphaTestRef     = GANDR.Device.DrawSetting.AlphaTestParam ;
				}
				else
				{
					// ���������L���ȏꍇ�̓��l���O�̏ꍇ�̂ݕ\������Ȃ��悤�ɂ���
					if( g_DefaultBlendDescArray[ NextBlendMode ].BlendEnable == TRUE )
					{
						GANDR.Device.State.AlphaTestEnable = TRUE ;
						AlphaTestRef     = 0 ;
						AlphaTestCmpMode = DX_CMP_GREATER ;
					}
					else
					{
						GANDR.Device.State.AlphaTestEnable = FALSE ;
					}
				}

				// �g�p����V�F�[�_�[���Z�b�g
				GANDR.Device.State.AlphaTestModeShaderIndex = Graphics_Android_Shader_GetAlphaTestModeIndex( GANDR.Device.State.AlphaTestEnable, AlphaTestCmpMode ) ;

				VS        =  &SB->BaseSimple_VS     [ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ] ;
				VSAddress = &SCB->BaseSimple_VS_Code[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ] ;

				FS        =  &SB->BaseUseTex_FS     [ 3 ][ RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;
				FSAddress = &SCB->BaseUseTex_FS_Code[ 3 ][ RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;

				UseShader = &SB->BaseUseTex_Shader[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ][ 3 ][ RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;
				break ;
			}
		}
		else
		{
			// �u�����h�e�N�X�`���[�������ꍇ

			// �Ƃ肠�����`�揈�����s��
			GANDR.Device.DrawInfo.BlendMaxNotDrawFlag = FALSE ;

			// ���_�^�C�v�̃Z�b�g
			GANDR.Device.DrawInfo.VertexType = VERTEXTYPE_TEX ;

			// �A���t�@�e�X�g�p�����[�^���L���ȏꍇ�͂����D�悷��
			if( GANDR.Device.DrawSetting.AlphaTestMode != -1 )
			{
				GANDR.Device.State.AlphaTestEnable = TRUE ;
				AlphaTestCmpMode = GANDR.Device.DrawSetting.AlphaTestMode ;
				AlphaTestRef     = GANDR.Device.DrawSetting.AlphaTestParam ;
			}
			else
			{
				// ���e�X�g���g�p���邩�ǂ����ŏ����𕪊�
				if( GANDR.Device.DrawSetting.AlphaTestValidFlag == TRUE )
				{
					// ���e�X�g���s��(���ߐF�����ȊO�Ƀ��e�X�g�̓u�����h�e�N�X�`���ł��g�p���Ă���)
					GANDR.Device.State.AlphaTestEnable = TRUE ;
					AlphaTestRef     = 16 ;
					AlphaTestCmpMode = DX_CMP_GREATER ;
				}
				else
				{
					// ���������L���ȏꍇ�̓u�����h���[�h�ɂ���Ă̓��l���O�̏ꍇ�̂ݕ\������Ȃ��悤�ɂ���
					if( g_DefaultBlendDescArray[ NextBlendMode ].BlendEnable == TRUE &&
						g_DefaultBlendDescArray[ NextBlendMode ].AlphaZeroNotDrawFlag == TRUE )
					{
						GANDR.Device.State.AlphaTestEnable = TRUE ;
						AlphaTestRef     = 0 ;
						AlphaTestCmpMode = DX_CMP_GREATER ;
					}
					else
					{
						GANDR.Device.State.AlphaTestEnable = FALSE ;
					}
				}
			}

			// �g�p����t���O�����g�V�F�[�_�[���Z�b�g
			GANDR.Device.State.AlphaTestModeShaderIndex = Graphics_Android_Shader_GetAlphaTestModeIndex( GANDR.Device.State.AlphaTestEnable, AlphaTestCmpMode ) ;

			VS        =  &SB->BaseSimple_VS     [ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ] ;
			VSAddress = &SCB->BaseSimple_VS_Code[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ] ;

			FS        =  &SB->BaseUseTex_FS     [ 0 ][ g_DefaultBlendDescArray[ NextBlendMode ].RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;
			FSAddress = &SCB->BaseUseTex_FS_Code[ 0 ][ g_DefaultBlendDescArray[ NextBlendMode ].RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;

			UseShader = &SB->BaseUseTex_Shader[ g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ][ 0 ][ g_DefaultBlendDescArray[ NextBlendMode ].RenderType ][ GANDR.Device.DrawSetting.IgnoreGraphColorFlag ? 1 : 0 ][ IgnoreTextureAlpha ][ GANDR.Device.State.AlphaTestModeShaderIndex ] ;

			// �g�p����e�N�X�`���[�A�h���X���Z�b�g
			UseTexture[ 0 ] = GANDR.Device.DrawSetting.RenderTexture ;

			// �g�p����e�N�X�`���̐��͈��
			UseTextureNum = 1 ;
		}
	}

	// ���_�V�F�[�_�[�����邩�ǂ����𒲂ׂ�
	if( *VS == 0 )
	{
		// ���_�V�F�[�_�[�̍쐬�����݂�
		if( Graphics_Android_VertexShader_Create( VSAddress, VS, 1 ) != 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x41\x00\x6e\x00\x64\x00\x72\x00\x6f\x00\x69\x00\x64\x00\x5f\x00\x44\x00\x65\x00\x76\x00\x69\x00\x63\x00\x65\x00\x53\x00\x74\x00\x61\x00\x74\x00\x65\x00\x5f\x00\x4e\x00\x6f\x00\x72\x00\x6d\x00\x61\x00\x6c\x00\x44\x00\x72\x00\x61\x00\x77\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"Graphics_Android_DeviceState_NormalDrawSetup �Œ��_�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
			return -1 ;
		}
	}

	// �t���O�����g�V�F�[�_�[�����邩�ǂ����𒲂ׂ�
	if( *FS == 0 )
	{
		// �t���O�����g�V�F�[�_�[�̍쐬�����݂�
		if( Graphics_Android_FragmentShader_Create( FSAddress, FS, 1 ) != 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x41\x00\x6e\x00\x64\x00\x72\x00\x6f\x00\x69\x00\x64\x00\x5f\x00\x44\x00\x65\x00\x76\x00\x69\x00\x63\x00\x65\x00\x53\x00\x74\x00\x61\x00\x74\x00\x65\x00\x5f\x00\x4e\x00\x6f\x00\x72\x00\x6d\x00\x61\x00\x6c\x00\x44\x00\x72\x00\x61\x00\x77\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\xd5\x30\xe9\x30\xb0\x30\xe1\x30\xf3\x30\xc8\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"Graphics_Android_DeviceState_NormalDrawSetup �Ńt���O�����g�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
			return -1 ;
		}
	}

	// �V�F�[�_�[���쐬����Ă��Ȃ�������V�F�[�_�[�̍쐬�����݂�
	if( *UseShader == NULL )
	{
		*UseShader = Graphics_Android_GetShaderStruct() ;
		if( *UseShader == NULL )
		{
			return -1 ;
		}
	}
	if( ( *UseShader )->Shader == 0 )
	{
		if( Graphics_Android_Shader_Create( *UseShader, *VS, *FS ) != 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x41\x00\x6e\x00\x64\x00\x72\x00\x6f\x00\x69\x00\x64\x00\x5f\x00\x44\x00\x65\x00\x76\x00\x69\x00\x63\x00\x65\x00\x53\x00\x74\x00\x61\x00\x74\x00\x65\x00\x5f\x00\x4e\x00\x6f\x00\x72\x00\x6d\x00\x61\x00\x6c\x00\x44\x00\x72\x00\x61\x00\x77\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"Graphics_Android_DeviceState_NormalDrawSetup �ŃV�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
			return -1 ;
		}
	}

	if( UseTextureNum > 0 )
	{
		int i ;

		for( i = 0 ; i < UseTextureNum ; i ++ )
		{
			Graphics_Android_DeviceState_SetTexture( i, UseTexture[ i ] ) ;
		}
	}

	if( GANDR.Device.State.AlphaTestEnable )
	{
		Graphics_Android_DeviceState_SetAlphaTestRef( AlphaTestRef ) ;
		Graphics_Android_DeviceState_SetAlphaTestCmpMode( AlphaTestCmpMode ) ;
	}
	else
	{
		Graphics_Android_DeviceState_SetAlphaTestRef( -1 ) ;
		Graphics_Android_DeviceState_SetAlphaTestCmpMode( DX_CMP_GREATER ) ;
	}

	if( UseFloatFactorColor )
	{
		Graphics_Android_DeviceState_SetFactorColor( &FloatFactorColor ) ;
	}

	Graphics_Android_DeviceState_SetBlendMode( NextBlendMode, GANDR.Device.DrawSetting.NotWriteAlphaChannelFlag ) ;
	Graphics_Android_DeviceState_SetShader( *UseShader, TRUE ) ;

	// �I��
	return 0 ;
}


























// �`��ݒ�֌W�֐�

// �`��u�����h���[�h�̐ݒ�
extern int Graphics_Android_DrawSetting_SetDrawBlendMode( int BlendMode, int AlphaTestValidFlag, int AlphaChannelValidFlag )
{
	if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE &&
		GANDR.Device.DrawSetting.BlendMode               == BlendMode &&
		GANDR.Device.DrawSetting.AlphaTestValidFlag      == AlphaTestValidFlag &&
		GANDR.Device.DrawSetting.AlphaChannelValidFlag   == AlphaChannelValidFlag )
	{
		return 0 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	GANDR.Device.DrawSetting.BlendMode             = BlendMode ;
	GANDR.Device.DrawSetting.AlphaChannelValidFlag = AlphaChannelValidFlag ;
	GANDR.Device.DrawSetting.AlphaTestValidFlag    = AlphaTestValidFlag ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag    = TRUE ;

	// �p�����[�^���ύX���ꂽ�A�t���O�𗧂Ă�
	GANDR.Device.DrawSetting.ChangeBlendParamFlag = TRUE ;

	return 0 ;
}

// �`�掞�̉摜�̂q�f�a�𖳎����邩�ǂ�����ݒ肷��
extern int Graphics_Android_DrawSetting_SetIgnoreDrawGraphColor( int EnableFlag )
{
	if( GANDR.Device.DrawSetting.IgnoreGraphColorFlag == EnableFlag &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �l��ۑ�
	GANDR.Device.DrawSetting.IgnoreGraphColorFlag = EnableFlag ;

	// �萔�f�[�^�ɔ��f
	if( GANDR.Device.DrawSetting.IgnoreGraphColorFlag )
	{
		GANDR.Device.Shader.Constant.uIgnoreTextureColor[ 0 ] = 1.0f ;
		GANDR.Device.Shader.Constant.uIgnoreTextureColor[ 1 ] = 1.0f ;
		GANDR.Device.Shader.Constant.uIgnoreTextureColor[ 2 ] = 1.0f ;
	}
	else
	{
		GANDR.Device.Shader.Constant.uIgnoreTextureColor[ 0 ] = 0.0f ;
		GANDR.Device.Shader.Constant.uIgnoreTextureColor[ 1 ] = 0.0f ;
		GANDR.Device.Shader.Constant.uIgnoreTextureColor[ 2 ] = 0.0f ;
	}

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

//	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �p�����[�^���ύX���ꂽ�A�t���O�𗧂Ă�
	GANDR.Device.DrawSetting.ChangeBlendParamFlag = TRUE ;

	return 0 ;
}

// �`�掞�̉摜�̂`�𖳎����邩�ǂ�����ݒ肷��
extern int Graphics_Android_DrawSetting_SetIgnoreDrawGraphAlpha( int EnableFlag )
{
	if( GANDR.Device.DrawSetting.IgnoreGraphAlphaFlag == EnableFlag &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �l��ۑ�
	GANDR.Device.DrawSetting.IgnoreGraphAlphaFlag = EnableFlag ;

	// �萔�f�[�^�ɔ��f
	if( GANDR.Device.DrawSetting.IgnoreGraphAlphaFlag )
	{
		GANDR.Device.Shader.Constant.uIgnoreTextureColor[ 3 ] = 1.0f ;
	}
	else
	{
		GANDR.Device.Shader.Constant.uIgnoreTextureColor[ 3 ] = 0.0f ;
	}

	GANDR.Device.Shader.Constant.UpdateCount ++ ;

	// �p�����[�^���ύX���ꂽ�A�t���O�𗧂Ă�
	GANDR.Device.DrawSetting.ChangeBlendParamFlag = TRUE ;

	return 0 ;
}

// �`���̃A���t�@�`�����l���̓��e�����������邩��ݒ肷��
extern int Graphics_Android_DrawSetting_SetWriteAlphaChannelFlag( int NotFlag )
{
	if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE &&
		GANDR.Device.DrawSetting.NotWriteAlphaChannelFlag == NotFlag )
	{
		return 0 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	GANDR.Device.DrawSetting.NotWriteAlphaChannelFlag = NotFlag ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag    = TRUE ;

	// �p�����[�^���ύX���ꂽ�A�t���O�𗧂Ă�
	GANDR.Device.DrawSetting.ChangeBlendParamFlag = TRUE ;

	return 0 ;
}

// �A���t�@�e�X�g�̐ݒ�
extern int Graphics_Android_DrawSetting_SetDrawAlphaTest( int TestMode, int TestParam )
{
	if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE &&
		GANDR.Device.DrawSetting.AlphaTestMode  == TestMode &&
		GANDR.Device.DrawSetting.AlphaTestParam == TestParam )
	{
		return 0 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	GANDR.Device.DrawSetting.AlphaTestMode      = TestMode ;
	GANDR.Device.DrawSetting.AlphaTestParam     = TestParam ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �p�����[�^���ύX���ꂽ�A�t���O�𗧂Ă�
	GANDR.Device.DrawSetting.ChangeBlendParamFlag = TRUE ;

	return 0 ;
}

// �u�����h����e�N�X�`���̃p�����[�^���Z�b�g����
extern int Graphics_Android_DrawSetting_SetBlendTextureParam( int BlendType, int *Param )
{
	// �p�����[�^��ۑ�
	switch( BlendType )
	{
	case DX_BLENDGRAPHTYPE_NORMAL :
		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE &&
			BlendType == GANDR.Device.DrawSetting.BlendGraphType &&
			GANDR.Device.DrawSetting.BlendGraphFadeRatio == Param[ 0 ] )
		{
			return 0 ;
		}

		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			// �`��ҋ@���Ă���`�敨��`��
			DRAWSTOCKINFO
		}

		GANDR.Device.DrawSetting.BlendGraphFadeRatio = Param[ 0 ] ;
		break;

	case DX_BLENDGRAPHTYPE_WIPE:
		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE &&
			BlendType == GANDR.Device.DrawSetting.BlendGraphType &&
			GANDR.Device.DrawSetting.BlendGraphBorderParam == Param[ 0 ] &&
			GANDR.Device.DrawSetting.BlendGraphBorderRange == Param[ 1 ] )
		{
			return 0 ;
		}

		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			// �`��ҋ@���Ă���`�敨��`��
			DRAWSTOCKINFO
		}

		GANDR.Device.DrawSetting.BlendGraphBorderParam = Param[ 0 ] ;
		GANDR.Device.DrawSetting.BlendGraphBorderRange = Param[ 1 ] ;
		break;

	case DX_BLENDGRAPHTYPE_ALPHA :
		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE &&
			BlendType == GANDR.Device.DrawSetting.BlendGraphType )
		{
			return 0 ;
		}

		if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
		{
			// �`��ҋ@���Ă���`�敨��`��
			DRAWSTOCKINFO
		}
		break;
	}

	// �u�����h�^�C�v��ۑ�����
	GANDR.Device.DrawSetting.BlendGraphType = BlendType ;

	// �p�����[�^���ύX���ꂽ�A�t���O�𗧂Ă�
	GANDR.Device.DrawSetting.ChangeBlendParamFlag = TRUE ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �e�N�X�`�����Z�b�g���� 
extern int Graphics_Android_DrawSetting_SetTexture( GRAPHICS_ANDROID_TEXTURE *RenderTexture )
{
	if( RenderTexture == GANDR.Device.DrawSetting.RenderTexture &&
		GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		return 0 ;
	}

	if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		// �`��ҋ@���Ă���`�敨��`��
		DRAWSTOCKINFO
	}

	// �e�N�X�`�����ύX���ꂽ�A�t���O�𗧂Ă�
	GANDR.Device.DrawSetting.ChangeTextureFlag = TRUE ;

	// �e�N�X�`���̗L�薳�����ύX���ꂽ�ꍇ�̓u�����h�p�����[�^�̕ύX���s���t���O���Z�b�g����
	if( ( GANDR.Device.DrawSetting.RenderTexture == NULL && RenderTexture != NULL ) ||
		( GANDR.Device.DrawSetting.RenderTexture != NULL && RenderTexture == NULL ) )
	{
		GANDR.Device.DrawSetting.ChangeBlendParamFlag = TRUE ;
	}

	// �e�N�X�`���Z�b�g
	GANDR.Device.DrawSetting.RenderTexture      = RenderTexture ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �I��
	return 0 ;
}

// �u�����h����e�N�X�`�����Z�b�g���� 
extern int Graphics_Android_DrawSetting_SetBlendTexture( GRAPHICS_ANDROID_TEXTURE *BlendTexture )
{
	if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE &&
		BlendTexture == GANDR.Device.DrawSetting.BlendTexture )
	{
		return 0 ;
	}

	if( GANDR.Device.DrawSetting.CancelSettingEqualCheck == FALSE )
	{
		// �`��ҋ@���Ă���`�敨��`��
		DRAWSTOCKINFO
	}

	// �e�N�X�`�����ύX���ꂽ�A�t���O�𗧂Ă�
	GANDR.Device.DrawSetting.ChangeTextureFlag = TRUE ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;

	// �u�����h�e�N�X�`���̗L�薳�����ύX���ꂽ�ꍇ�̓u�����h�p�����[�^�̕ύX���s���t���O���Z�b�g����
	if( ( GANDR.Device.DrawSetting.BlendTexture == NULL && BlendTexture != NULL ) ||
		( GANDR.Device.DrawSetting.BlendTexture != NULL && BlendTexture == NULL ) )
	{
		GANDR.Device.DrawSetting.ChangeBlendParamFlag = TRUE ;
	}

	// �e�N�X�`���Z�b�g
	GANDR.Device.DrawSetting.BlendTexture    = BlendTexture ;

	// �e�N�X�`���̕��ƍ�����ۑ�
	if( BlendTexture != NULL )
	{
		GANDR.Device.DrawSetting.BlendTextureWidth  = ( float )BlendTexture->Width  ;
		GANDR.Device.DrawSetting.BlendTextureHeight = ( float )BlendTexture->Height ;
		GANDR.Device.DrawSetting.InvBlendTextureWidth  = 1.0F / GANDR.Device.DrawSetting.BlendTextureWidth ;
		GANDR.Device.DrawSetting.InvBlendTextureHeight = 1.0F / GANDR.Device.DrawSetting.BlendTextureHeight ;
	}

	// �I��
	return 0 ;
}
































// Android �̕`�揈�������֌W

#ifndef DX_NON_ASYNCLOAD
static int Graphics_Android_RenderVertexASyncCallback( ASYNCLOAD_MAINTHREAD_REQUESTINFO * Info )
{
	return Graphics_Android_RenderVertex(
		( int )Info->Data[ 0 ],
		FALSE ) ;
}
#endif // DX_NON_ASYNCLOAD

// ���_�o�b�t�@�ɗ��܂������_�f�[�^�������_�����O����
extern	int		Graphics_Android_RenderVertex( int NextUse3DVertex, int ASyncThread )
{
	DWORD InputLayout ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

#ifndef DX_NON_ASYNCLOAD
	if( ASyncThread )
	{
		ASYNCLOAD_MAINTHREAD_REQUESTINFO AInfo ;

		AInfo.Function = Graphics_Android_RenderVertexASyncCallback ;
		AInfo.Data[ 0 ] = ( DWORD_PTR )NextUse3DVertex ;
		return AddASyncLoadRequestMainThreadInfo( &AInfo ) ;
	}
#endif // DX_NON_ASYNCLOAD

	InputLayout = g_VertexTypeToInputLayout[ GANDR.Device.DrawInfo.Use3DVertex ][ GANDR.Device.DrawInfo.VertexType ] ;

	// ���_���������������`��͍s��Ȃ�
	if( GANDR.Device.DrawInfo.VertexNum != 0 && DxLib_GetEndRequest() == FALSE && GANDR.Device.State.SetShader != NULL )
	{
		// ��`��t���O�������Ă��Ȃ���΃����_�����O����
		if( GANDR.Device.DrawInfo.BlendMaxNotDrawFlag == FALSE )
		{
			// �V�F�[�_�[���Z�b�g
			if( InputLayout == ANDROID_VERTEX_INPUTLAYOUT_3D_LIGHT )
			{
				if( Graphics_Android_Shader_Normal3DDraw_Setup() == FALSE )
				{
					return -1 ;
				}
			}
//			else
//			{
//				Graphics_Android_DeviceState_SetVertexShader( &GANDR.Device.Shader.Base.BaseSimple_VS[ InputLayout ], TRUE ) ;
//			}

			// �e�N�X�`���̃Z�b�g
			for( int i = 0; i < USE_TEXTURESTAGE_NUM; i++ )
			{
				if( GANDR.Device.State.SetTexture[ i ] == NULL )
				{
					continue ;
				}

				glActiveTexture( g_TextureEnum[ i ] ) ;
				glBindTexture( GL_TEXTURE_2D, GANDR.Device.State.SetTexture[ i ]->TextureBuffer ) ;
			}

			// Uniform �̍X�V
			Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

			// ���_�f�[�^�̃Z�b�g�A�b�v
			Graphics_Android_DeviceState_SetupShaderVertexData(
				GANDR.Device.State.SetShader,
				&g_BaseSimpleVertexShaderInfo[ InputLayout ].InputInfo,
				GANDR.Device.DrawInfo.VertexBuffer
			) ;

			// �`��
			glDrawArrays( GANDR.Device.DrawInfo.PrimitiveType, 0, GANDR.Device.DrawInfo.VertexNum );
			GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;
		}
	}

	GANDR.Device.DrawInfo.VertexNum = 0 ;
	GANDR.Device.DrawInfo.VertexBufferNextAddr = GANDR.Device.DrawInfo.VertexBuffer ;

	if( NextUse3DVertex >= 0 )
	{
		int PrevUse3DVertex = GANDR.Device.DrawInfo.Use3DVertex ;

		GANDR.Device.DrawInfo.Use3DVertex = NextUse3DVertex ;

		if( PrevUse3DVertex != NextUse3DVertex )
		{
			Graphics_Android_DeviceState_NormalDrawSetup() ;
		}
	}

	// �I��
	return 0 ;
}

// �`�揀�����s��
extern	void	FASTCALL Graphics_Android_DrawPreparation( int ParamFlag )
{
	int AlphaTest ;
	int AlphaChannel ;
	int Specular ;
	int i ;

	// �K�� Graphics_Android_DrawPreparation ���s���ׂ��Ƃ����t���O��|��
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = FALSE ;

	// �ݒ肪�ύX���ꂽ���ǂ����̃t���O��|��
	GSYS.ChangeSettingFlag = FALSE ;

	// ���C�g���g�����ǂ����ŏ����𕪊�
	if( ( ParamFlag & DX_ANDROID_DRAWPREP_LIGHTING ) != 0 && GSYS.Light.ProcessDisable == FALSE )
	{
		// ���C�g�̐ݒ肪�ύX����Ă�����ύX��K������
		if( GSYS.Light.HardwareChange )
		{
			Graphics_Light_RefreshState() ;
		}
		else
		{
			// ���C�g���L���Ȃ̂Ɉꎞ�I�ɖ����ɂȂ��Ă�����L���ɂ���
			if( GANDR.Device.State.Lighting == 0 )
			{
				Graphics_Android_DeviceState_SetLighting( TRUE ) ;
			}
		}

		// �}�e���A���̐ݒ肪�O������ύX����Ă����猳�ɖ߂�
		if( GSYS.Light.ChangeMaterial )
		{
			GSYS.Light.ChangeMaterial = 0 ;
			Graphics_Android_DeviceState_SetMaterial( &GSYS.Light.Material ) ;
		}

		// ���_�J���[���}�e���A���̃J���[�Ƃ��Ďg�p���邩�ǂ������Z�b�g����
		if( ( GSYS.Light.MaterialNotUseVertexDiffuseColor ? FALSE : TRUE ) != GANDR.Device.State.MaterialUseVertexDiffuseColor )
		{
			Graphics_Android_DeviceState_SetUseVertexDiffuseColor( GSYS.Light.MaterialNotUseVertexDiffuseColor ? FALSE : TRUE ) ;
		}

		if( ( GSYS.Light.MaterialNotUseVertexSpecularColor ? FALSE : TRUE ) != GANDR.Device.State.MaterialUseVertexSpecularColor )
		{
			Graphics_Android_DeviceState_SetUseVertexSpecularColor( GSYS.Light.MaterialNotUseVertexSpecularColor ? FALSE : TRUE ) ;
		}
	}
	else
	{
		// ���C�g���L���ɂȂ��Ă����疳���ɂ���
		if( GANDR.Device.State.Lighting == 1 )
		{
			Graphics_Android_DeviceState_SetLighting( FALSE ) ;
		}

		// ���_�J���[���}�e���A���̃J���[�Ƃ��Ďg�p����
		if( GANDR.Device.State.MaterialUseVertexDiffuseColor == FALSE )
		{
			Graphics_Android_DeviceState_SetUseVertexDiffuseColor( TRUE ) ;
		}

		if( GANDR.Device.State.MaterialUseVertexSpecularColor == FALSE )
		{
			Graphics_Android_DeviceState_SetUseVertexSpecularColor( TRUE ) ;
		}
	}

	// �X�y�L�������g�p���邩�ǂ����̐ݒ���s��
	Specular = ( GSYS.DrawSetting.NotUseSpecular == FALSE && ( ParamFlag & DX_ANDROID_DRAWPREP_SPECULAR ) != 0 ) ? TRUE : FALSE ;
	if( Specular != GANDR.Device.State.UseSpecular )
	{
		Graphics_Android_DeviceState_SetSpecularEnable( Specular ) ;
	}

	// �ˉe�s��̐ݒ���s��
//	Graphics_DrawSetting_SetUse2DProjectionMatrix( ( ParamFlag & DX_ANDROID_DRAWPREP_3D ) == 0 ? TRUE : FALSE ) ;

	// �y�o�b�t�@�̐ݒ���s��
	{
		BOOL			DepthEnable ;
		int				WriteDepthBuffer ;
		GLenum			DepthFunc ;
		int				DepthBias ;

		if( ParamFlag & DX_ANDROID_DRAWPREP_3D )
		{
			DepthEnable      = GSYS.DrawSetting.EnableZBufferFlag3D ;
			WriteDepthBuffer = GSYS.DrawSetting.WriteZBufferFlag3D ;
			DepthFunc        = g_DXCmpModeToGLES2CompareFunc[ GSYS.DrawSetting.ZBufferCmpType3D ] ;
			DepthBias        = GSYS.DrawSetting.ZBias3D ;
		}
		else
		{
			DepthEnable      = GSYS.DrawSetting.EnableZBufferFlag2D ;
			WriteDepthBuffer = GSYS.DrawSetting.WriteZBufferFlag2D ;
			DepthFunc        = g_DXCmpModeToGLES2CompareFunc[ GSYS.DrawSetting.ZBufferCmpType2D ] ;
			DepthBias        = GSYS.DrawSetting.ZBias2D ;
		}

		if( DepthEnable )
		{
			if( GANDR.Device.State.DepthEnable != DepthEnable )
			{
				Graphics_Android_DeviceState_SetDepthEnable( DepthEnable ) ;
			}

			if( GANDR.Device.State.DepthWriteEnable != WriteDepthBuffer  )
			{
				Graphics_Android_DeviceState_SetDepthWriteEnable( WriteDepthBuffer  ) ;
			}

			if( GANDR.Device.State.DepthFunc != DepthFunc )
			{
				Graphics_Android_DeviceState_SetDepthFunc( DepthFunc ) ;
			}

			if( GANDR.Device.State.DepthBias != DepthBias )
			{
				Graphics_Android_DeviceState_SetDepthBias( DepthBias ) ;
			}
		}
		else
		{
			if( GANDR.Device.State.DepthEnable )
			{
				Graphics_Android_DeviceState_SetDepthEnable( FALSE ) ;
			}

			if( GANDR.Device.State.DepthWriteEnable != FALSE  )
			{
				Graphics_Android_DeviceState_SetDepthWriteEnable( FALSE ) ;
			}
		}
	}

	// �t�H�O�̐ݒ���s��
	if( ParamFlag & DX_ANDROID_DRAWPREP_FOG )
	{
		if( GANDR.Device.State.FogEnable != GSYS.DrawSetting.FogEnable )
		{
			Graphics_Android_DeviceState_SetFogEnable( GSYS.DrawSetting.FogEnable ) ;
		}
	}
	else
	{
		if( GANDR.Device.State.FogEnable )
		{
			Graphics_Android_DeviceState_SetFogEnable( FALSE ) ;
		}
	}

	// �u�����f�B���O�֌W�̃Z�b�e�B���O���s���ꍇ�̂ݎ��s����
	if( ( ParamFlag & DX_ANDROID_DRAWPREP_NOBLENDSETTING ) == 0 )
	{
		// �t���O�̏�����
		AlphaTest    = FALSE ;
		AlphaChannel = FALSE ;

		// �e�N�X�`���[���g�p���邩�ǂ����ŏ����𕪊�
		// �g�p���Ȃ��ꍇ�͏����l�̂܂�
		if( ParamFlag & DX_ANDROID_DRAWPREP_TEXTURE )
		{
			// ���ߐF�������s��Ȃ��ꍇ�̓J���[�L�[�����e�X�g�����`�����l�����g�p���Ȃ��̂ŏ����l�̂܂�
			// ���ߐF�������s���ꍇ�̂ݏ���������
			if( ParamFlag & DX_ANDROID_DRAWPREP_TRANS )
			{
				int TexAlphaTestFlag = ( ParamFlag & DX_ANDROID_DRAWPREP_TEXALPHATEST ) != 0 ? 1 : 0 ;
				int TexAlphaChFlag   = ( ParamFlag & DX_ANDROID_DRAWPREP_TEXALPHACH   ) != 0 ? 1 : 0 ;

				// �e�N�X�`���Ƀ��r�b�g�����邩�ǂ����ŏ����𕪊�
				if( TexAlphaTestFlag || TexAlphaChFlag )
				{
					// ���e�X�g�ł����_���W�̃f�[�^�^�����������_�^�ŁA���e�N�X�`���t�B���^�����O���[�h��
					// ���`��Ԃł��邩�A�u�����h���[�h�� DX_BLENDMODE_NOBLEND �ȊO�������烿�`�����l���Ƃ��Ĉ���
					if( ( GSYS.DrawSetting.BlendMode != DX_BLENDMODE_NOBLEND && GSYS.DrawSetting.BlendMode != DX_BLENDMODE_DESTCOLOR ) ||
						( ( ParamFlag & DX_ANDROID_DRAWPREP_VECTORINT ) == 0   && GSYS.DrawSetting.DrawMode  == DX_DRAWMODE_BILINEAR   ) )
					{
						AlphaChannel = TRUE ;
					}
					else
					{
						// ����ȊO�̏ꍇ�̓e�N�X�`���[�̃t���O�Ɉς˂�
						AlphaTest    = TexAlphaTestFlag ;
						AlphaChannel = TexAlphaChFlag ;
					}
				}
			}
		}

		// �������ꂽ�p�����[�^���Z�b�g����
		if( GANDR.Device.DrawSetting.IgnoreGraphColorFlag  != GSYS.DrawSetting.IgnoreGraphColorFlag )
		{
			Graphics_Android_DrawSetting_SetIgnoreDrawGraphColor( GSYS.DrawSetting.IgnoreGraphColorFlag ) ;
		}

		if( GANDR.Device.DrawSetting.NotWriteAlphaChannelFlag  != GSYS.DrawSetting.NotWriteAlphaChannelFlag )
		{
			Graphics_Android_DrawSetting_SetWriteAlphaChannelFlag( GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		}

		if( GANDR.Device.DrawSetting.BlendMode             != GSYS.DrawSetting.BlendMode ||
			GANDR.Device.DrawSetting.AlphaTestValidFlag    != AlphaTest ||
			GANDR.Device.DrawSetting.AlphaChannelValidFlag != AlphaChannel               )
		{
			Graphics_Android_DrawSetting_SetDrawBlendMode( GSYS.DrawSetting.BlendMode, AlphaTest, AlphaChannel ) ;
		}

		if( GANDR.Device.DrawSetting.AlphaTestMode         != GSYS.DrawSetting.AlphaTestMode ||
			GANDR.Device.DrawSetting.AlphaTestParam        != GSYS.DrawSetting.AlphaTestParam )
		{
			Graphics_Android_DrawSetting_SetDrawAlphaTest( GSYS.DrawSetting.AlphaTestMode, GSYS.DrawSetting.AlphaTestParam ) ;
		}

		if( GANDR.Device.DrawSetting.ChangeBlendParamFlag ||
			GANDR.Device.DrawSetting.ChangeTextureFlag ||
			( GSYS.HardInfo.UseShader &&
			  GANDR.Device.State.SetNormalShader == FALSE ) )
		{
			Graphics_Android_DeviceState_NormalDrawSetup() ;
		}
	}

	if( GANDR.Device.State.DrawMode != GSYS.DrawSetting.DrawMode )
	{
		Graphics_Android_DeviceState_SetDrawMode( GSYS.DrawSetting.DrawMode ) ;
	}

	if( GANDR.Device.State.MaxAnisotropy != GSYS.DrawSetting.MaxAnisotropy )
	{
		Graphics_Android_DeviceState_SetMaxAnisotropy( GSYS.DrawSetting.MaxAnisotropy ) ;
	}

	if( ParamFlag & DX_ANDROID_DRAWPREP_CULLING )
	{
		int SetCullMode ;

		if( GANDR.Device.State.CullEnable == FALSE )
		{
			SetCullMode = 0 ;
		}
		else
		{
			switch( GANDR.Device.State.CullFace )
			{
			default :
				SetCullMode = 0 ;
				break ;

			case GL_FRONT :
				SetCullMode = 1 ;
				break ;

			case GL_BACK :
				SetCullMode = 2 ;
				break ;
			}
		}

		if( SetCullMode != GSYS.DrawSetting.CullMode )
		{
			Graphics_Android_DeviceState_SetCullMode( GSYS.DrawSetting.CullMode ) ;
		}
	}
	else
	{
		if( GANDR.Device.State.CullEnable )
		{
			Graphics_Android_DeviceState_SetCullMode( DX_CULLING_NONE ) ;
		}
	}

	if( GSYS.DrawSetting.MatchHardwareTextureAddressTransformMatrix == FALSE )
	{
		Graphics_Android_DeviceState_SetTextureAddressTransformMatrix( GSYS.DrawSetting.TextureAddressTransformUse, &GSYS.DrawSetting.TextureAddressTransformMatrix ) ;
		GSYS.DrawSetting.MatchHardwareTextureAddressTransformMatrix = TRUE ;
		GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;
	}

	if( ParamFlag & DX_ANDROID_DRAWPREP_TEXADDRESS )
	{
		for( i = 0; i < USE_TEXTURESTAGE_NUM; i++ )
		{
			if( GSYS.DrawSetting.TexAddressModeU[ i ] == GSYS.DrawSetting.TexAddressModeV[ i ] )
			{
				if( ( DWORD )GANDR.Device.State.TexAddressModeU[ i ] != g_DXTexAddrModeToGLES2WrapMode[ GSYS.DrawSetting.TexAddressModeU[ i ] ] ||
					( DWORD )GANDR.Device.State.TexAddressModeV[ i ] != g_DXTexAddrModeToGLES2WrapMode[ GSYS.DrawSetting.TexAddressModeV[ i ] ] )
				{
					Graphics_Android_DeviceState_SetTextureAddress( GSYS.DrawSetting.TexAddressModeU[ i ], i ) ;
				}
			}
			else
			{
				if( ( DWORD )GANDR.Device.State.TexAddressModeU[ i ] != g_DXTexAddrModeToGLES2WrapMode[ GSYS.DrawSetting.TexAddressModeU[ i ] ] )
				{
					Graphics_Android_DeviceState_SetTextureAddressU( GSYS.DrawSetting.TexAddressModeU[ i ], i ) ;
				}

				if( ( DWORD )GANDR.Device.State.TexAddressModeV[ i ] != g_DXTexAddrModeToGLES2WrapMode[ GSYS.DrawSetting.TexAddressModeV[ i ] ] )
				{
					Graphics_Android_DeviceState_SetTextureAddressV( GSYS.DrawSetting.TexAddressModeV[ i ], i ) ;
				}
			}
		}
	}
	else
	{
		for( i = 0; i < 4; i++ )
		{
			if( GANDR.Device.State.TexAddressModeU[ i ] != GL_CLAMP_TO_EDGE ||
				GANDR.Device.State.TexAddressModeV[ i ] != GL_CLAMP_TO_EDGE )
			{
				Graphics_Android_DeviceState_SetTextureAddress( DX_TEXADDRESS_CLAMP, i ) ;
			}
		}
	}

	// RenderBegin �����s���Ă��Ȃ���������s����
	if( GANDR.Device.DrawInfo.BeginSceneFlag == FALSE )
	{
		Graphics_Android_RenderBegin() ;
	}

	// �p�����[�^��ۑ�
	GANDR.Device.DrawSetting.DrawPrepParamFlag = ParamFlag ;
}


// �`��R�}���h���J�n����
extern	void	Graphics_Android_RenderBegin( void )
{
	if( GANDR.Device.DrawInfo.BeginSceneFlag == TRUE )
	{
		return ;
	}

	GANDR.Device.DrawInfo.BeginSceneFlag = TRUE ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;
}

// �`��R�}���h���I������
extern	void	Graphics_Android_RenderEnd( void )
{
	if( GANDR.Device.DrawInfo.BeginSceneFlag == FALSE )
	{
		return ;
	}

	GANDR.Device.DrawInfo.BeginSceneFlag = FALSE ;
}



























// Android ���g�����`��֌W

// ���_�o�b�t�@�ɗ��܂������_�f�[�^�������_�����O����
extern	int		Graphics_Hardware_RenderVertex( int ASyncThread )
{
	return Graphics_Android_RenderVertex( -1, ASyncThread ) ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawBillboard3D
extern	int		Graphics_Hardware_DrawBillboard3D_PF( VECTOR Pos, float cx, float cy, float Size, float Angle, IMAGEDATA *Image, IMAGEDATA *BlendImage, int TransFlag, int ReverseXFlag, int ReverseYFlag, int DrawFlag, RECT *DrawArea )
{
	VERTEX_2D *DrawVert ;
	VERTEX_2D TempVect[ 4 ] ;
	VERTEX_3D *DrawVert3D ;
	VERTEX_BLENDTEX_2D *DrawVertB ;
	VERTEX_BLENDTEX_2D TempVert[ 4 ] ;
	IMAGEDATA_HARD_DRAW *DrawTex ;
	IMAGEDATA_HARD_DRAW *BlendDrawTex ;
	IMAGEDATA_ORIG *Orig ;
	IMAGEDATA_HARD_VERT *TexVert ;
	IMAGEDATA_HARD_VERT *BlendTexVert = NULL ;
	DWORD DiffuseColor ;
	int DrawTexNum ;
	int i ;
	int Flag ;
	int BlendGraphNoIncFlag ;
	float SizeX ;
	float SizeY ;
	float f ;
	VECTOR SrcVec[ 4 ] ;
	VECTOR SrcVec2[ 4 ] ;
	float Sin = 0.0f ;
	float Cos = 1.0f ;
	float ScaleX ;
	float ScaleY ;
	float dleft = 0.0f ;
	float dright = 0.0f ;
	float dtop = 0.0f ;
	float dbottom = 0.0f ;
	float z ;
	float rhw ;
	float u[ 2 ] ;
	float v[ 2 ] ;

	Orig = Image->Orig ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`�揀��
	if( DrawFlag )
	{
		Flag = TransFlag | DX_ANDROID_DRAWPREP_3D | DX_ANDROID_DRAWPREP_FOG | DX_ANDROID_DRAWPREP_TEXADDRESS ;
		DX_ANDROID_DRAWPREP_TEX( Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )
	}
	else
	{
		dleft   = -100000000.0f ;
		dright  =  100000000.0f ;
		dtop    = -100000000.0f ;
		dbottom =  100000000.0f ;
	}

	// ���_�f�[�^���擾
	DiffuseColor = GANDR.Device.DrawInfo.DiffuseColor ;

	// �`����̐����Z�b�g
	DrawTexNum = Image->Hard.DrawNum ;

	// �`����̐����u�����h�摜�ƈقȂ��Ă�����O�Ԗڂ̃e�N�X�`���������g�p����
	BlendGraphNoIncFlag = FALSE ;
	if( BlendImage != NULL && BlendImage->Hard.DrawNum != Image->Hard.DrawNum )
	{
		BlendGraphNoIncFlag = TRUE ;
	}

	// �`����z��̃A�h���X���Z�b�g���Ă���
	DrawTex = Image->Hard.Draw ;
	BlendDrawTex = NULL ;
	if( BlendImage != NULL )
	{
		BlendDrawTex = BlendImage->Hard.Draw ;
	}

	// �T�C�Y�ƍ��W�֌W�̎��O�v�Z
	SizeX = Size ;
	SizeY = Size * ( float )Image->HeightF / ( float )Image->WidthF ;

	ScaleX = SizeX / Image->WidthF ;
	ScaleY = SizeY / Image->HeightF ;
	cx *= Image->WidthF ;
	cy *= Image->HeightF ;

	// ��]����ꍇ�͉�]�l�����߂Ă���
	if( Angle != 0.0 )
	{
		_SINCOS( (float)Angle, &Sin, &Cos ) ;
	}

	// �e�N�X�`���[�̐������J��Ԃ�
	for( i = 0 ; i < DrawTexNum ; i ++, DrawTex ++ )
	{
		// �`�悷��e�N�X�`���[�̃Z�b�g
		if( DrawFlag )
		{
			Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;

			if( BlendDrawTex != NULL )
			{
				Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture );
			}

			if( GANDR.Device.DrawSetting.ChangeTextureFlag )
			{
				Graphics_Android_DeviceState_NormalDrawSetup() ;
			}
		}

		TexVert = DrawTex->Vertex ;
		if( BlendDrawTex != NULL )
		{
			BlendTexVert = BlendDrawTex->Vertex ;
		}

		// �u�����h�O���t�B�b�N���g�p���Ă��Ȃ��āA���`�悷��ꍇ�͍����ȏ������g�p����
		if( GANDR.Device.DrawInfo.VertexType != VERTEXTYPE_BLENDTEX && DrawFlag == TRUE )
		{
			GETVERTEX_BILLBOARD( DrawVert3D ) ;

			// ��]����ꍇ�Ƃ��Ȃ��ꍇ�ŏ����𕪊�
			if( Angle != 0.0 )
			{
				// ���[�J�����W����
				SrcVec[2].x = SrcVec[0].x = ( -cx + TexVert[0].x ) * ScaleX ;
				SrcVec[3].x = SrcVec[1].x = ( -cx + TexVert[1].x ) * ScaleX ;

				SrcVec[1].y = SrcVec[0].y = ( -cy + Image->HeightF - TexVert[0].y ) * ScaleY ;
				SrcVec[3].y = SrcVec[2].y = ( -cy + Image->HeightF - TexVert[2].y ) * ScaleY ;

				// ��]�v�Z
				f             = SrcVec[ 0 ].x * Cos - SrcVec[ 0 ].y * Sin ;	
				SrcVec[ 0 ].y = SrcVec[ 0 ].x * Sin + SrcVec[ 0 ].y * Cos ;
				SrcVec[ 0 ].x = f ;

				f             = SrcVec[ 1 ].x * Cos - SrcVec[ 1 ].y * Sin ;	
				SrcVec[ 1 ].y = SrcVec[ 1 ].x * Sin + SrcVec[ 1 ].y * Cos ;
				SrcVec[ 1 ].x = f ;

				f             = SrcVec[ 2 ].x * Cos - SrcVec[ 2 ].y * Sin ;	
				SrcVec[ 2 ].y = SrcVec[ 2 ].x * Sin + SrcVec[ 2 ].y * Cos ;
				SrcVec[ 2 ].x = f ;

				f             = SrcVec[ 3 ].x * Cos - SrcVec[ 3 ].y * Sin ;	
				SrcVec[ 3 ].y = SrcVec[ 3 ].x * Sin + SrcVec[ 3 ].y * Cos ;
				SrcVec[ 3 ].x = f ;

				// �r���{�[�h���W�����[���h���W�֕ϊ�
				DrawVert3D[ 0 ].pos.x = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
				DrawVert3D[ 0 ].pos.y = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
				DrawVert3D[ 0 ].pos.z = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

				DrawVert3D[ 1 ].pos.x = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + SrcVec[ 1 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
				DrawVert3D[ 1 ].pos.y = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + SrcVec[ 1 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
				DrawVert3D[ 1 ].pos.z = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + SrcVec[ 1 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

				DrawVert3D[ 2 ].pos.x = SrcVec[ 2 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
				DrawVert3D[ 2 ].pos.y = SrcVec[ 2 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
				DrawVert3D[ 2 ].pos.z = SrcVec[ 2 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

				DrawVert3D[ 3 ].pos.x = SrcVec[ 3 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + SrcVec[ 3 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
				DrawVert3D[ 3 ].pos.y = SrcVec[ 3 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + SrcVec[ 3 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
				DrawVert3D[ 3 ].pos.z = SrcVec[ 3 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + SrcVec[ 3 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

				DrawVert3D[ 4 ].pos.x = SrcVec[ 2 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
				DrawVert3D[ 4 ].pos.y = SrcVec[ 2 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
				DrawVert3D[ 4 ].pos.z = SrcVec[ 2 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

				DrawVert3D[ 5 ].pos.x = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + SrcVec[ 1 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
				DrawVert3D[ 5 ].pos.y = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + SrcVec[ 1 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
				DrawVert3D[ 5 ].pos.z = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + SrcVec[ 1 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;
			}
			else
			{
				VECTOR TempVecX[ 2 ], TempVecY[ 2 ] ;

				// ���[�J�����W����
				SrcVec[0].x = ( -cx + TexVert[0].x ) * ScaleX ;
				SrcVec[1].x = ( -cx + TexVert[1].x ) * ScaleX ;

				SrcVec[0].y = ( -cy + Image->HeightF - TexVert[0].y ) * ScaleY ;
				SrcVec[2].y = ( -cy + Image->HeightF - TexVert[2].y ) * ScaleY ;

				// �r���{�[�h���W�����[���h���W�֕ϊ�
				TempVecX[ 0 ].x = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + Pos.x ;
				TempVecX[ 0 ].y = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + Pos.y ;
				TempVecX[ 0 ].z = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + Pos.z ;

				TempVecX[ 1 ].x = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + Pos.x ;
				TempVecX[ 1 ].y = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + Pos.y ;
				TempVecX[ 1 ].z = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + Pos.z ;

				TempVecY[ 0 ].x = SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] ;
				TempVecY[ 0 ].y = SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] ;
				TempVecY[ 0 ].z = SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] ;

				TempVecY[ 1 ].x = SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] ;
				TempVecY[ 1 ].y = SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] ;
				TempVecY[ 1 ].z = SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] ;

				DrawVert3D[ 0 ].pos.x = TempVecX[ 0 ].x + TempVecY[ 0 ].x ;
				DrawVert3D[ 0 ].pos.y = TempVecX[ 0 ].y + TempVecY[ 0 ].y ;
				DrawVert3D[ 0 ].pos.z = TempVecX[ 0 ].z + TempVecY[ 0 ].z ;

				DrawVert3D[ 1 ].pos.x = TempVecX[ 1 ].x + TempVecY[ 0 ].x ;
				DrawVert3D[ 1 ].pos.y = TempVecX[ 1 ].y + TempVecY[ 0 ].y ;
				DrawVert3D[ 1 ].pos.z = TempVecX[ 1 ].z + TempVecY[ 0 ].z ;

				DrawVert3D[ 2 ].pos.x = TempVecX[ 0 ].x + TempVecY[ 1 ].x ;
				DrawVert3D[ 2 ].pos.y = TempVecX[ 0 ].y + TempVecY[ 1 ].y ;
				DrawVert3D[ 2 ].pos.z = TempVecX[ 0 ].z + TempVecY[ 1 ].z ;

				DrawVert3D[ 3 ].pos.x = TempVecX[ 1 ].x + TempVecY[ 1 ].x ;
				DrawVert3D[ 3 ].pos.y = TempVecX[ 1 ].y + TempVecY[ 1 ].y ;
				DrawVert3D[ 3 ].pos.z = TempVecX[ 1 ].z + TempVecY[ 1 ].z ;

				DrawVert3D[ 4 ].pos.x = TempVecX[ 0 ].x + TempVecY[ 1 ].x ;
				DrawVert3D[ 4 ].pos.y = TempVecX[ 0 ].y + TempVecY[ 1 ].y ;
				DrawVert3D[ 4 ].pos.z = TempVecX[ 0 ].z + TempVecY[ 1 ].z ;

				DrawVert3D[ 5 ].pos.x = TempVecX[ 1 ].x + TempVecY[ 0 ].x ;
				DrawVert3D[ 5 ].pos.y = TempVecX[ 1 ].y + TempVecY[ 0 ].y ;
				DrawVert3D[ 5 ].pos.z = TempVecX[ 1 ].z + TempVecY[ 0 ].z ;
			}

			*( ( DWORD * )&DrawVert3D[0].b ) = DiffuseColor ;
			*( ( DWORD * )&DrawVert3D[1].b ) = DiffuseColor ;
			*( ( DWORD * )&DrawVert3D[2].b ) = DiffuseColor ;
			*( ( DWORD * )&DrawVert3D[3].b ) = DiffuseColor ;
			*( ( DWORD * )&DrawVert3D[4].b ) = DiffuseColor ; 
			*( ( DWORD * )&DrawVert3D[5].b ) = DiffuseColor ;

			if( ReverseXFlag )
			{
				DrawVert3D[0].u = TexVert[1].u ;
				DrawVert3D[1].u = TexVert[0].u ;
				DrawVert3D[2].u = TexVert[1].u ;
				DrawVert3D[3].u = TexVert[0].u ;
				DrawVert3D[4].u = TexVert[1].u ;
				DrawVert3D[5].u = TexVert[0].u ;
			}
			else
			{
				DrawVert3D[0].u = TexVert[0].u ;
				DrawVert3D[1].u = TexVert[1].u ;
				DrawVert3D[2].u = TexVert[0].u ;
				DrawVert3D[3].u = TexVert[1].u ;
				DrawVert3D[4].u = TexVert[0].u ;
				DrawVert3D[5].u = TexVert[1].u ;
			}
			if( ReverseYFlag )
			{
				DrawVert3D[0].v = TexVert[2].v ;
				DrawVert3D[1].v = TexVert[2].v ;
				DrawVert3D[2].v = TexVert[0].v ;
				DrawVert3D[3].v = TexVert[0].v ;
				DrawVert3D[4].v = TexVert[0].v ;
				DrawVert3D[5].v = TexVert[2].v ;
			}
			else
			{
				DrawVert3D[0].v = TexVert[0].v ;
				DrawVert3D[1].v = TexVert[0].v ;
				DrawVert3D[2].v = TexVert[2].v ;
				DrawVert3D[3].v = TexVert[2].v ;
				DrawVert3D[4].v = TexVert[2].v ;
				DrawVert3D[5].v = TexVert[0].v ;
			}

			// �e�N�X�`���[��`�悷��
			ADD4VERTEX_BILLBOARD
		}
		else
		{
			VECTOR DrawPos[ 4 ] ;

			// �r���{�[�h�̂S���_�𓾂�
			{
				// ��]����ꍇ�Ƃ��Ȃ��ꍇ�ŏ����𕪊�
				if( Angle != 0.0 )
				{
					// ���[�J�����W����
					SrcVec[2].x = SrcVec[0].x = ( -cx + TexVert[0].x ) * ScaleX ;
					SrcVec[3].x = SrcVec[1].x = ( -cx + TexVert[1].x ) * ScaleX ;

					SrcVec[1].y = SrcVec[0].y = ( -cy + Image->HeightF - TexVert[0].y ) * ScaleY ;
					SrcVec[3].y = SrcVec[2].y = ( -cy + Image->HeightF - TexVert[2].y ) * ScaleY ;

					// ��]�v�Z
					f             = SrcVec[ 0 ].x * Cos - SrcVec[ 0 ].y * Sin ;	
					SrcVec[ 0 ].y = SrcVec[ 0 ].x * Sin + SrcVec[ 0 ].y * Cos ;
					SrcVec[ 0 ].x = f ;

					f             = SrcVec[ 1 ].x * Cos - SrcVec[ 1 ].y * Sin ;	
					SrcVec[ 1 ].y = SrcVec[ 1 ].x * Sin + SrcVec[ 1 ].y * Cos ;
					SrcVec[ 1 ].x = f ;

					f             = SrcVec[ 2 ].x * Cos - SrcVec[ 2 ].y * Sin ;	
					SrcVec[ 2 ].y = SrcVec[ 2 ].x * Sin + SrcVec[ 2 ].y * Cos ;
					SrcVec[ 2 ].x = f ;

					f             = SrcVec[ 3 ].x * Cos - SrcVec[ 3 ].y * Sin ;	
					SrcVec[ 3 ].y = SrcVec[ 3 ].x * Sin + SrcVec[ 3 ].y * Cos ;
					SrcVec[ 3 ].x = f ;

					// �r���{�[�h���W�����[���h���W�֕ϊ�
					SrcVec2[ 0 ].x = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
					SrcVec2[ 0 ].y = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
					SrcVec2[ 0 ].z = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

					SrcVec2[ 1 ].x = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + SrcVec[ 1 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
					SrcVec2[ 1 ].y = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + SrcVec[ 1 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
					SrcVec2[ 1 ].z = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + SrcVec[ 1 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

					SrcVec2[ 2 ].x = SrcVec[ 2 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
					SrcVec2[ 2 ].y = SrcVec[ 2 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
					SrcVec2[ 2 ].z = SrcVec[ 2 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

					SrcVec2[ 3 ].x = SrcVec[ 3 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + SrcVec[ 3 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
					SrcVec2[ 3 ].y = SrcVec[ 3 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + SrcVec[ 3 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
					SrcVec2[ 3 ].z = SrcVec[ 3 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + SrcVec[ 3 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;
				}
				else
				{
					VECTOR TempVecX[ 2 ], TempVecY[ 2 ] ;

					// ���[�J�����W����
					SrcVec[0].x = ( -cx + TexVert[0].x ) * ScaleX ;
					SrcVec[1].x = ( -cx + TexVert[1].x ) * ScaleX ;

					SrcVec[0].y = ( -cy + Image->HeightF - TexVert[0].y ) * ScaleY ;
					SrcVec[2].y = ( -cy + Image->HeightF - TexVert[2].y ) * ScaleY ;

					// �r���{�[�h���W�����[���h���W�֕ϊ�
					TempVecX[ 0 ].x = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + Pos.x ;
					TempVecX[ 0 ].y = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + Pos.y ;
					TempVecX[ 0 ].z = SrcVec[ 0 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + Pos.z ;

					TempVecX[ 1 ].x = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + Pos.x ;
					TempVecX[ 1 ].y = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + Pos.y ;
					TempVecX[ 1 ].z = SrcVec[ 1 ].x * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + Pos.z ;

					TempVecY[ 0 ].x = SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] ;
					TempVecY[ 0 ].y = SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] ;
					TempVecY[ 0 ].z = SrcVec[ 0 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] ;

					TempVecY[ 1 ].x = SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][0] ;
					TempVecY[ 1 ].y = SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][1] ;
					TempVecY[ 1 ].z = SrcVec[ 2 ].y * GSYS.DrawSetting.BillboardMatrixF.m[1][2] ;

					SrcVec2[ 0 ].x = TempVecX[ 0 ].x + TempVecY[ 0 ].x ;
					SrcVec2[ 0 ].y = TempVecX[ 0 ].y + TempVecY[ 0 ].y ;
					SrcVec2[ 0 ].z = TempVecX[ 0 ].z + TempVecY[ 0 ].z ;

					SrcVec2[ 1 ].x = TempVecX[ 1 ].x + TempVecY[ 0 ].x ;
					SrcVec2[ 1 ].y = TempVecX[ 1 ].y + TempVecY[ 0 ].y ;
					SrcVec2[ 1 ].z = TempVecX[ 1 ].z + TempVecY[ 0 ].z ;

					SrcVec2[ 2 ].x = TempVecX[ 0 ].x + TempVecY[ 1 ].x ;
					SrcVec2[ 2 ].y = TempVecX[ 0 ].y + TempVecY[ 1 ].y ;
					SrcVec2[ 2 ].z = TempVecX[ 0 ].z + TempVecY[ 1 ].z ;

					SrcVec2[ 3 ].x = TempVecX[ 1 ].x + TempVecY[ 1 ].x ;
					SrcVec2[ 3 ].y = TempVecX[ 1 ].y + TempVecY[ 1 ].y ;
					SrcVec2[ 3 ].z = TempVecX[ 1 ].z + TempVecY[ 1 ].z ;
				}
			}

			// ���_�^�C�v�ɂ���ď����𕪊�
			switch( GANDR.Device.DrawInfo.VertexType )
			{
			case VERTEXTYPE_BLENDTEX :
				// �u�����h�e�N�X�`�����g�p����

				// ���_�o�b�t�@�̎擾
				if( DrawFlag )
				{
					GETVERTEX_QUAD( DrawVertB )
				}
				else
				{
					DrawVertB = TempVert ;
				}

				DrawVertB[0].color = DiffuseColor ;
				DrawVertB[1].color = DiffuseColor ;
				DrawVertB[2].color = DiffuseColor ;
				DrawVertB[3].color = DiffuseColor ;
				DrawVertB[4].color = DiffuseColor ;
				DrawVertB[5].color = DiffuseColor ;

				// �X�N���[�����W�ɕϊ�
				rhw = 1.0f / ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][3] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][3] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][3] + GSYS.DrawSetting.Blend3DMatrixF.m[3][3] ) ;
				z   = rhw  * ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][2] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][2] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][2] + GSYS.DrawSetting.Blend3DMatrixF.m[3][2] ) ;

				DrawPos[ 0 ].x = ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawPos[ 0 ].y = ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawPos[ 1 ].x = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawPos[ 1 ].y = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawPos[ 2 ].x = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawPos[ 2 ].y = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawPos[ 3 ].x = ( SrcVec2[3].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[3].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[3].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawPos[ 3 ].y = ( SrcVec2[3].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[3].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[3].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;

				DrawVertB[0].pos.x = DrawPos[ 0 ].x ;
				DrawVertB[0].pos.y = DrawPos[ 0 ].y ;
				DrawVertB[1].pos.x = DrawPos[ 1 ].x ;
				DrawVertB[1].pos.y = DrawPos[ 1 ].y ;
				DrawVertB[2].pos.x = DrawPos[ 2 ].x ;
				DrawVertB[2].pos.y = DrawPos[ 2 ].y ;
				DrawVertB[3].pos.x = DrawPos[ 3 ].x ;
				DrawVertB[3].pos.y = DrawPos[ 3 ].y ;
				DrawVertB[4].pos.x = DrawPos[ 2 ].x ;
				DrawVertB[4].pos.y = DrawPos[ 2 ].y ;
				DrawVertB[5].pos.x = DrawPos[ 1 ].x ;
				DrawVertB[5].pos.y = DrawPos[ 1 ].y ;

				switch( GSYS.DrawSetting.BlendGraphPosMode )
				{
				default :
				case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
					u[ 0 ] = ( TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u[ 1 ] = ( TexVert[1].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					v[ 0 ] = ( TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v[ 1 ] = ( TexVert[2].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[0].u1 = u[ 0 ] ;
					DrawVertB[0].v1 = v[ 0 ] ;
					DrawVertB[1].u1 = u[ 1 ] ;
					DrawVertB[1].v1 = v[ 0 ] ;
					DrawVertB[2].u1 = u[ 0 ] ;
					DrawVertB[2].v1 = v[ 1 ] ;
					DrawVertB[3].u1 = u[ 1 ] ;
					DrawVertB[3].v1 = v[ 1 ] ;
					DrawVertB[4].u1 = u[ 0 ] ;
					DrawVertB[4].v1 = v[ 1 ] ;
					DrawVertB[5].u1 = u[ 1 ] ;
					DrawVertB[5].v1 = v[ 0 ] ;
					break ;

				case DX_BLENDGRAPH_POSMODE_SCREEN :
					DrawVertB[0].u1 = ( DrawPos[ 0 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[0].v1 = ( DrawPos[ 0 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[1].u1 = ( DrawPos[ 1 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[1].v1 = ( DrawPos[ 1 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[2].u1 = ( DrawPos[ 2 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[2].v1 = ( DrawPos[ 2 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[3].u1 = ( DrawPos[ 3 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[3].v1 = ( DrawPos[ 3 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[4].u1 = ( DrawPos[ 2 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[4].v1 = ( DrawPos[ 2 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[5].u1 = ( DrawPos[ 1 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[5].v1 = ( DrawPos[ 1 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					break ;
				}

				if( ReverseXFlag )
				{
					DrawVertB[0].u2 = TexVert[1].u ;
					DrawVertB[1].u2 = TexVert[0].u ;
					DrawVertB[2].u2 = TexVert[1].u ;
					DrawVertB[3].u2 = TexVert[0].u ;
					DrawVertB[4].u2 = TexVert[1].u ;
					DrawVertB[5].u2 = TexVert[0].u ;
				}
				else
				{
					DrawVertB[0].u2 = TexVert[0].u ;
					DrawVertB[1].u2 = TexVert[1].u ;
					DrawVertB[2].u2 = TexVert[0].u ;
					DrawVertB[3].u2 = TexVert[1].u ;
					DrawVertB[4].u2 = TexVert[0].u ;
					DrawVertB[5].u2 = TexVert[1].u ;
				}
				if( ReverseYFlag )
				{
					DrawVertB[0].v2 = TexVert[2].v ;
					DrawVertB[1].v2 = TexVert[2].v ;
					DrawVertB[2].v2 = TexVert[0].v ;
					DrawVertB[3].v2 = TexVert[0].v ;
					DrawVertB[4].v2 = TexVert[0].v ;
					DrawVertB[5].v2 = TexVert[2].v ;
				}
				else
				{
					DrawVertB[0].v2 = TexVert[0].v ;
					DrawVertB[1].v2 = TexVert[0].v ;
					DrawVertB[2].v2 = TexVert[2].v ;
					DrawVertB[3].v2 = TexVert[2].v ;
					DrawVertB[4].v2 = TexVert[2].v ;
					DrawVertB[5].v2 = TexVert[0].v ;
				}

				DrawVertB[0].pos.z = z ;
				DrawVertB[1].pos.z = z ;
				DrawVertB[2].pos.z = z ;
				DrawVertB[3].pos.z = z ;
				DrawVertB[4].pos.z = z ;
				DrawVertB[5].pos.z = z ;

				DrawVertB[0].rhw = rhw ;
				DrawVertB[1].rhw = rhw ;
				DrawVertB[2].rhw = rhw ;
				DrawVertB[3].rhw = rhw ;
				DrawVertB[4].rhw = rhw ;
				DrawVertB[5].rhw = rhw ;

				// �e�N�X�`���[��`�悷��
				if( DrawFlag )
				{
					ADD4VERTEX_BLENDTEX
				}
				else
				{
					if( dright  > DrawVertB[ 0 ].pos.x ) dright  = DrawVertB[ 0 ].pos.x ;
					if( dright  > DrawVertB[ 1 ].pos.x ) dright  = DrawVertB[ 1 ].pos.x ;
					if( dright  > DrawVertB[ 2 ].pos.x ) dright  = DrawVertB[ 2 ].pos.x ;
					if( dright  > DrawVertB[ 3 ].pos.x ) dright  = DrawVertB[ 3 ].pos.x ;

					if( dleft   < DrawVertB[ 0 ].pos.x ) dleft   = DrawVertB[ 0 ].pos.x ;
					if( dleft   < DrawVertB[ 1 ].pos.x ) dleft   = DrawVertB[ 1 ].pos.x ;
					if( dleft   < DrawVertB[ 2 ].pos.x ) dleft   = DrawVertB[ 2 ].pos.x ;
					if( dleft   < DrawVertB[ 3 ].pos.x ) dleft   = DrawVertB[ 3 ].pos.x ;

					if( dbottom > DrawVertB[ 0 ].pos.y ) dbottom = DrawVertB[ 0 ].pos.y ;
					if( dbottom > DrawVertB[ 1 ].pos.y ) dbottom = DrawVertB[ 1 ].pos.y ;
					if( dbottom > DrawVertB[ 2 ].pos.y ) dbottom = DrawVertB[ 2 ].pos.y ;
					if( dbottom > DrawVertB[ 3 ].pos.y ) dbottom = DrawVertB[ 3 ].pos.y ;

					if( dtop    < DrawVertB[ 0 ].pos.y ) dtop    = DrawVertB[ 0 ].pos.y ;
					if( dtop    < DrawVertB[ 1 ].pos.y ) dtop    = DrawVertB[ 1 ].pos.y ;
					if( dtop    < DrawVertB[ 2 ].pos.y ) dtop    = DrawVertB[ 2 ].pos.y ;
					if( dtop    < DrawVertB[ 3 ].pos.y ) dtop    = DrawVertB[ 3 ].pos.y ;
				}

				if( BlendGraphNoIncFlag == FALSE )
				{
					BlendDrawTex ++ ;
				}
				break ;

			case VERTEXTYPE_TEX :
				// �u�����h�e�N�X�`�����g�p���Ȃ�

				// ���_�o�b�t�@�̎擾
				if( DrawFlag )
				{
					GETVERTEX_QUAD( DrawVert )
				}
				else
				{
					DrawVert = TempVect;
				}

				// �X�N���[�����W�ɕϊ�
				rhw = 1.0f / ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][3] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][3] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][3] + GSYS.DrawSetting.Blend3DMatrixF.m[3][3] ) ;
				z   = rhw  * ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][2] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][2] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][2] + GSYS.DrawSetting.Blend3DMatrixF.m[3][2] ) ;

				DrawVert[0].pos.x = ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[0].pos.y = ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawVert[1].pos.x = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[1].pos.y = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawVert[2].pos.x = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[2].pos.y = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawVert[3].pos.x = ( SrcVec2[3].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[3].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[3].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[3].pos.y = ( SrcVec2[3].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[3].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[3].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawVert[4].pos.x = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[4].pos.y = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawVert[5].pos.x = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[5].pos.y = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;

				DrawVert[0].pos.z = z ;
				DrawVert[1].pos.z = z ;
				DrawVert[2].pos.z = z ;
				DrawVert[3].pos.z = z ;
				DrawVert[4].pos.z = z ;
				DrawVert[5].pos.z = z ;

				DrawVert[0].rhw = rhw ;
				DrawVert[1].rhw = rhw ;
				DrawVert[2].rhw = rhw ;
				DrawVert[3].rhw = rhw ;
				DrawVert[4].rhw = rhw ;
				DrawVert[5].rhw = rhw ;

				DrawVert[0].color = DiffuseColor ;
				DrawVert[1].color = DiffuseColor ;
				DrawVert[2].color = DiffuseColor ;
				DrawVert[3].color = DiffuseColor ;
				DrawVert[4].color = DiffuseColor ;
				DrawVert[5].color = DiffuseColor ;

				if( ReverseXFlag )
				{
					DrawVert[0].u = TexVert[1].u ;
					DrawVert[1].u = TexVert[0].u ;
					DrawVert[2].u = TexVert[1].u ;
					DrawVert[3].u = TexVert[0].u ;
					DrawVert[4].u = TexVert[1].u ;
					DrawVert[5].u = TexVert[0].u ;
				}
				else
				{
					DrawVert[0].u = TexVert[0].u ;
					DrawVert[1].u = TexVert[1].u ;
					DrawVert[2].u = TexVert[0].u ;
					DrawVert[3].u = TexVert[1].u ;
					DrawVert[4].u = TexVert[0].u ;
					DrawVert[5].u = TexVert[1].u ;
				}
				if( ReverseYFlag )
				{
					DrawVert[0].v = TexVert[2].v ;
					DrawVert[1].v = TexVert[2].v ;
					DrawVert[2].v = TexVert[0].v ;
					DrawVert[3].v = TexVert[0].v ;
					DrawVert[4].v = TexVert[0].v ;
					DrawVert[5].v = TexVert[2].v ;
				}
				else
				{
					DrawVert[0].v = TexVert[0].v ;
					DrawVert[1].v = TexVert[0].v ;
					DrawVert[2].v = TexVert[2].v ;
					DrawVert[3].v = TexVert[2].v ;
					DrawVert[4].v = TexVert[2].v ;
					DrawVert[5].v = TexVert[0].v ;
				}

				// �e�N�X�`���[��`�悷��
				if( DrawFlag )
				{
					ADD4VERTEX_TEX
				}
				else
				{
					if( dright  > DrawVert[ 0 ].pos.x ) dright  = DrawVert[ 0 ].pos.x ;
					if( dright  > DrawVert[ 1 ].pos.x ) dright  = DrawVert[ 1 ].pos.x ;
					if( dright  > DrawVert[ 2 ].pos.x ) dright  = DrawVert[ 2 ].pos.x ;
					if( dright  > DrawVert[ 3 ].pos.x ) dright  = DrawVert[ 3 ].pos.x ;

					if( dleft   < DrawVert[ 0 ].pos.x ) dleft   = DrawVert[ 0 ].pos.x ;
					if( dleft   < DrawVert[ 1 ].pos.x ) dleft   = DrawVert[ 1 ].pos.x ;
					if( dleft   < DrawVert[ 2 ].pos.x ) dleft   = DrawVert[ 2 ].pos.x ;
					if( dleft   < DrawVert[ 3 ].pos.x ) dleft   = DrawVert[ 3 ].pos.x ;

					if( dbottom > DrawVert[ 0 ].pos.y ) dbottom = DrawVert[ 0 ].pos.y ;
					if( dbottom > DrawVert[ 1 ].pos.y ) dbottom = DrawVert[ 1 ].pos.y ;
					if( dbottom > DrawVert[ 2 ].pos.y ) dbottom = DrawVert[ 2 ].pos.y ;
					if( dbottom > DrawVert[ 3 ].pos.y ) dbottom = DrawVert[ 3 ].pos.y ;

					if( dtop    < DrawVert[ 0 ].pos.y ) dtop    = DrawVert[ 0 ].pos.y ;
					if( dtop    < DrawVert[ 1 ].pos.y ) dtop    = DrawVert[ 1 ].pos.y ;
					if( dtop    < DrawVert[ 2 ].pos.y ) dtop    = DrawVert[ 2 ].pos.y ;
					if( dtop    < DrawVert[ 3 ].pos.y ) dtop    = DrawVert[ 3 ].pos.y ;
				}
				break ;
			}
		}
	}

	if( DrawFlag == FALSE )
	{
		DrawArea->left   = _FTOL( dleft   ) - 1 ;
		DrawArea->right  = _FTOL( dright  ) + 1 ;
		DrawArea->top    = _FTOL( dtop    ) - 1 ;
		DrawArea->bottom = _FTOL( dbottom ) + 1 ;
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawModiBillboard3D
extern	int		Graphics_Hardware_DrawModiBillboard3D_PF( VECTOR Pos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, IMAGEDATA *Image, IMAGEDATA *BlendImage, int TransFlag, int DrawFlag, RECT *DrawArea )
{
	VERTEX_2D *DrawVert ;
	VERTEX_3D *DrawVert3D ;
	VERTEX_BLENDTEX_2D *DrawVertB ;
	IMAGEDATA_HARD_DRAW *DrawTex ;
	IMAGEDATA_HARD_DRAW *BlendDrawTex ;
	IMAGEDATA_ORIG *Orig ;
	IMAGEDATA_HARD_VERT *TexVert ;
	IMAGEDATA_HARD_VERT *BlendTexVert = NULL ;
	DWORD DiffuseColor ;
	int DrawTexNum ;
	int i, Flag ;
	int BlendGraphNoIncFlag ;
	VECTOR SrcVec2[ 4 ] ;
	float dleft = 0.0f, dright = 0.0f, dtop = 0.0f, dbottom = 0.0f;
	float z ;
	float rhw ;
	float u[ 2 ] ;
	float v[ 2 ] ;

	Orig = Image->Orig ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`�揀��
	if( DrawFlag )
	{
		Flag = TransFlag | DX_ANDROID_DRAWPREP_3D | DX_ANDROID_DRAWPREP_FOG | DX_ANDROID_DRAWPREP_TEXADDRESS ;
		DX_ANDROID_DRAWPREP_TEX( Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )
	}
	else
	{
		dleft   = -100000000.0f ;
		dright  =  100000000.0f ;
		dtop    = -100000000.0f ;
		dbottom =  100000000.0f ;
	}

	// ���_�f�[�^���擾
	DiffuseColor = GANDR.Device.DrawInfo.DiffuseColor ;

	// �`����̐����Z�b�g
	DrawTexNum = Image->Hard.DrawNum ;

	// �`����̐����u�����h�摜�ƈقȂ��Ă�����O�Ԗڂ̃e�N�X�`���������g�p����
	BlendGraphNoIncFlag = FALSE ;
	if( BlendImage != NULL && BlendImage->Hard.DrawNum != Image->Hard.DrawNum )
	{
		BlendGraphNoIncFlag = TRUE ;
	}

	// �`����z��̃A�h���X���Z�b�g���Ă���
	DrawTex = Image->Hard.Draw ;
	BlendDrawTex = NULL ;
	if( BlendImage != NULL )
	{
		BlendDrawTex = BlendImage->Hard.Draw ;
	}

	// �e�N�X�`���[�̐������J��Ԃ�
	for( i = 0 ; i < DrawTexNum ; i ++, DrawTex ++ )
	{
		// �`�悷��e�N�X�`���[�̃Z�b�g
		if( DrawFlag )
		{
			Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;

			if( BlendDrawTex != NULL )
			{
				Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture );
			}

			if( GANDR.Device.DrawSetting.ChangeTextureFlag )
			{
				Graphics_Android_DeviceState_NormalDrawSetup() ;
			}
		}

		TexVert = DrawTex->Vertex ;
		if( BlendDrawTex != NULL )
		{
			BlendTexVert = BlendDrawTex->Vertex ;
		}

		// �u�����h�O���t�B�b�N���g�p���Ă��Ȃ��āA���`�悷��ꍇ�͍����ȏ������g�p����
		if( GANDR.Device.DrawInfo.VertexType != VERTEXTYPE_BLENDTEX && DrawFlag == TRUE )
		{
			GETVERTEX_BILLBOARD( DrawVert3D ) ;

			// �r���{�[�h���W�����[���h���W�֕ϊ�
			DrawVert3D[ 0 ].pos.x = x1 * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + y1 * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
			DrawVert3D[ 0 ].pos.y = x1 * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + y1 * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
			DrawVert3D[ 0 ].pos.z = x1 * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + y1 * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

			DrawVert3D[ 1 ].pos.x = x2 * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + y2 * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
			DrawVert3D[ 1 ].pos.y = x2 * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + y2 * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
			DrawVert3D[ 1 ].pos.z = x2 * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + y2 * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

			DrawVert3D[ 2 ].pos.x = x4 * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + y4 * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
			DrawVert3D[ 2 ].pos.y = x4 * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + y4 * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
			DrawVert3D[ 2 ].pos.z = x4 * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + y4 * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

			DrawVert3D[ 3 ].pos.x = x3 * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + y3 * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
			DrawVert3D[ 3 ].pos.y = x3 * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + y3 * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
			DrawVert3D[ 3 ].pos.z = x3 * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + y3 * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

			DrawVert3D[ 4 ].pos.x = x4 * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + y4 * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
			DrawVert3D[ 4 ].pos.y = x4 * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + y4 * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
			DrawVert3D[ 4 ].pos.z = x4 * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + y4 * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

			DrawVert3D[ 5 ].pos.x = x2 * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + y2 * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
			DrawVert3D[ 5 ].pos.y = x2 * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + y2 * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
			DrawVert3D[ 5 ].pos.z = x2 * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + y2 * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

			*( ( DWORD * )&DrawVert3D[0].b ) = DiffuseColor ;
			*( ( DWORD * )&DrawVert3D[1].b ) = DiffuseColor ;
			*( ( DWORD * )&DrawVert3D[2].b ) = DiffuseColor ;
			*( ( DWORD * )&DrawVert3D[3].b ) = DiffuseColor ;
			*( ( DWORD * )&DrawVert3D[4].b ) = DiffuseColor ;
			*( ( DWORD * )&DrawVert3D[5].b ) = DiffuseColor ;

			DrawVert3D[0].u = TexVert[0].u ;
			DrawVert3D[0].v = TexVert[0].v ;
			DrawVert3D[1].u = TexVert[1].u ;
			DrawVert3D[1].v = TexVert[0].v ;
			DrawVert3D[2].u = TexVert[0].u ;
			DrawVert3D[2].v = TexVert[2].v ;
			DrawVert3D[3].u = TexVert[1].u ;
			DrawVert3D[3].v = TexVert[2].v ;
			DrawVert3D[4].u = TexVert[0].u ;
			DrawVert3D[4].v = TexVert[2].v ;
			DrawVert3D[5].u = TexVert[1].u ;
			DrawVert3D[5].v = TexVert[0].v ;

			// �e�N�X�`���[��`�悷��
			ADD4VERTEX_BILLBOARD
		}
		else
		{
			VECTOR DrawPos[ 4 ] ;

			// �r���{�[�h�̂S���_�𓾂�
			{
				// �r���{�[�h���W�����[���h���W�֕ϊ�
				SrcVec2[ 0 ].x = x1 * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + y1 * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
				SrcVec2[ 0 ].y = x1 * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + y1 * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
				SrcVec2[ 0 ].z = x1 * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + y1 * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

				SrcVec2[ 1 ].x = x2 * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + y2 * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
				SrcVec2[ 1 ].y = x2 * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + y2 * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
				SrcVec2[ 1 ].z = x2 * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + y2 * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

				SrcVec2[ 2 ].x = x4 * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + y4 * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
				SrcVec2[ 2 ].y = x4 * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + y4 * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
				SrcVec2[ 2 ].z = x4 * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + y4 * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;

				SrcVec2[ 3 ].x = x3 * GSYS.DrawSetting.BillboardMatrixF.m[0][0] + y3 * GSYS.DrawSetting.BillboardMatrixF.m[1][0] + Pos.x ;
				SrcVec2[ 3 ].y = x3 * GSYS.DrawSetting.BillboardMatrixF.m[0][1] + y3 * GSYS.DrawSetting.BillboardMatrixF.m[1][1] + Pos.y ;
				SrcVec2[ 3 ].z = x3 * GSYS.DrawSetting.BillboardMatrixF.m[0][2] + y3 * GSYS.DrawSetting.BillboardMatrixF.m[1][2] + Pos.z ;
			}

			// ���_�^�C�v�ɂ���ď����𕪊�
			switch( GANDR.Device.DrawInfo.VertexType )
			{
			case VERTEXTYPE_BLENDTEX :
				// �u�����h�e�N�X�`�����g�p����

				// ���_�o�b�t�@�̎擾
				GETVERTEX_QUAD( DrawVertB )

				DrawVertB[0].color = DiffuseColor ;
				DrawVertB[1].color = DiffuseColor ;
				DrawVertB[2].color = DiffuseColor ;
				DrawVertB[3].color = DiffuseColor ;
				DrawVertB[4].color = DiffuseColor ;
				DrawVertB[5].color = DiffuseColor ;

				// �X�N���[�����W�ɕϊ�
				rhw = 1.0f / ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][3] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][3] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][3] + GSYS.DrawSetting.Blend3DMatrixF.m[3][3] ) ;
				z   = rhw  * ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][2] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][2] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][2] + GSYS.DrawSetting.Blend3DMatrixF.m[3][2] ) ;

				DrawPos[ 0 ].x = ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawPos[ 0 ].y = ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawPos[ 1 ].x = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawPos[ 1 ].y = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawPos[ 2 ].x = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawPos[ 2 ].y = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawPos[ 3 ].x = ( SrcVec2[3].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[3].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[3].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawPos[ 3 ].y = ( SrcVec2[3].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[3].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[3].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;

				DrawVertB[0].pos.x = DrawPos[ 0 ].x ;
				DrawVertB[0].pos.y = DrawPos[ 0 ].y ;
				DrawVertB[1].pos.x = DrawPos[ 1 ].x ;
				DrawVertB[1].pos.y = DrawPos[ 1 ].y ;
				DrawVertB[2].pos.x = DrawPos[ 2 ].x ;
				DrawVertB[2].pos.y = DrawPos[ 2 ].y ;
				DrawVertB[3].pos.x = DrawPos[ 3 ].x ;
				DrawVertB[3].pos.y = DrawPos[ 3 ].y ;
				DrawVertB[4].pos.x = DrawPos[ 2 ].x ;
				DrawVertB[4].pos.y = DrawPos[ 2 ].y ;
				DrawVertB[5].pos.x = DrawPos[ 1 ].x ;
				DrawVertB[5].pos.y = DrawPos[ 1 ].y ;

				switch( GSYS.DrawSetting.BlendGraphPosMode )
				{
				default :
				case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
					u[ 0 ] = ( TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u[ 1 ] = ( TexVert[1].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					v[ 0 ] = ( TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v[ 1 ] = ( TexVert[2].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[0].u1 = u[ 0 ] ;
					DrawVertB[0].v1 = v[ 0 ] ;
					DrawVertB[1].u1 = u[ 1 ] ;
					DrawVertB[1].v1 = v[ 0 ] ;
					DrawVertB[2].u1 = u[ 0 ] ;
					DrawVertB[2].v1 = v[ 1 ] ;
					DrawVertB[3].u1 = u[ 1 ] ;
					DrawVertB[3].v1 = v[ 1 ] ;
					DrawVertB[4].u1 = u[ 0 ] ;
					DrawVertB[4].v1 = v[ 1 ] ;
					DrawVertB[5].u1 = u[ 1 ] ;
					DrawVertB[5].v1 = v[ 0 ] ;
					break ;

				case DX_BLENDGRAPH_POSMODE_SCREEN :
					DrawVertB[0].u1 = ( DrawPos[ 0 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[0].v1 = ( DrawPos[ 0 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[1].u1 = ( DrawPos[ 1 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[1].v1 = ( DrawPos[ 1 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[2].u1 = ( DrawPos[ 2 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[2].v1 = ( DrawPos[ 2 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[3].u1 = ( DrawPos[ 3 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[3].v1 = ( DrawPos[ 3 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[4].u1 = ( DrawPos[ 2 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[4].v1 = ( DrawPos[ 2 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[5].u1 = ( DrawPos[ 1 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[5].v1 = ( DrawPos[ 1 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					break ;
				}

				DrawVertB[0].u2 = TexVert[0].u ;
				DrawVertB[0].v2 = TexVert[0].v ;
				DrawVertB[1].u2 = TexVert[1].u ;
				DrawVertB[1].v2 = TexVert[0].v ;
				DrawVertB[2].u2 = TexVert[0].u ;
				DrawVertB[2].v2 = TexVert[2].v ;
				DrawVertB[3].u2 = TexVert[1].u ;
				DrawVertB[3].v2 = TexVert[2].v ;
				DrawVertB[4].u2 = TexVert[0].u ;
				DrawVertB[4].v2 = TexVert[2].v ;
				DrawVertB[5].u2 = TexVert[1].u ;
				DrawVertB[5].v2 = TexVert[0].v ;

				DrawVertB[0].pos.z = z ;
				DrawVertB[1].pos.z = z ;
				DrawVertB[2].pos.z = z ;
				DrawVertB[3].pos.z = z ;
				DrawVertB[4].pos.z = z ;
				DrawVertB[5].pos.z = z ;

				DrawVertB[0].rhw = rhw ;
				DrawVertB[1].rhw = rhw ;
				DrawVertB[2].rhw = rhw ;
				DrawVertB[3].rhw = rhw ;
				DrawVertB[4].rhw = rhw ;
				DrawVertB[5].rhw = rhw ;

				// �e�N�X�`���[��`�悷��
				if( DrawFlag )
				{
					ADD4VERTEX_BLENDTEX
				}
				else
				{
					if( dright  > DrawVertB[ 0 ].pos.x ) dright  = DrawVertB[ 0 ].pos.x ;
					if( dright  > DrawVertB[ 1 ].pos.x ) dright  = DrawVertB[ 1 ].pos.x ;
					if( dright  > DrawVertB[ 2 ].pos.x ) dright  = DrawVertB[ 2 ].pos.x ;
					if( dright  > DrawVertB[ 3 ].pos.x ) dright  = DrawVertB[ 3 ].pos.x ;

					if( dleft   < DrawVertB[ 0 ].pos.x ) dleft   = DrawVertB[ 0 ].pos.x ;
					if( dleft   < DrawVertB[ 1 ].pos.x ) dleft   = DrawVertB[ 1 ].pos.x ;
					if( dleft   < DrawVertB[ 2 ].pos.x ) dleft   = DrawVertB[ 2 ].pos.x ;
					if( dleft   < DrawVertB[ 3 ].pos.x ) dleft   = DrawVertB[ 3 ].pos.x ;

					if( dbottom > DrawVertB[ 0 ].pos.y ) dbottom = DrawVertB[ 0 ].pos.y ;
					if( dbottom > DrawVertB[ 1 ].pos.y ) dbottom = DrawVertB[ 1 ].pos.y ;
					if( dbottom > DrawVertB[ 2 ].pos.y ) dbottom = DrawVertB[ 2 ].pos.y ;
					if( dbottom > DrawVertB[ 3 ].pos.y ) dbottom = DrawVertB[ 3 ].pos.y ;

					if( dtop    < DrawVertB[ 0 ].pos.y ) dtop    = DrawVertB[ 0 ].pos.y ;
					if( dtop    < DrawVertB[ 1 ].pos.y ) dtop    = DrawVertB[ 1 ].pos.y ;
					if( dtop    < DrawVertB[ 2 ].pos.y ) dtop    = DrawVertB[ 2 ].pos.y ;
					if( dtop    < DrawVertB[ 3 ].pos.y ) dtop    = DrawVertB[ 3 ].pos.y ;
				}

				if( BlendGraphNoIncFlag == FALSE )
				{
					BlendDrawTex ++ ;
				}
				break ;

			case VERTEXTYPE_TEX :
				// �u�����h�e�N�X�`�����g�p���Ȃ�

				// ���_�o�b�t�@�̎擾
				GETVERTEX_QUAD( DrawVert )

				// �X�N���[�����W�ɕϊ�
				rhw = 1.0f / ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][3] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][3] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][3] + GSYS.DrawSetting.Blend3DMatrixF.m[3][3] ) ;
				z   = rhw  * ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][2] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][2] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][2] + GSYS.DrawSetting.Blend3DMatrixF.m[3][2] ) ;

				DrawVert[0].pos.x = ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[0].pos.y = ( SrcVec2[0].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[0].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[0].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawVert[1].pos.x = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[1].pos.y = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawVert[2].pos.x = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[2].pos.y = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawVert[3].pos.x = ( SrcVec2[3].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[3].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[3].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[3].pos.y = ( SrcVec2[3].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[3].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[3].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawVert[4].pos.x = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[4].pos.y = ( SrcVec2[2].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[2].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[2].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;
				DrawVert[5].pos.x = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0] ) * rhw ;
				DrawVert[5].pos.y = ( SrcVec2[1].x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + SrcVec2[1].y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + SrcVec2[1].z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1] ) * rhw ;

				DrawVert[0].pos.z = z ;
				DrawVert[1].pos.z = z ;
				DrawVert[2].pos.z = z ;
				DrawVert[3].pos.z = z ;
				DrawVert[4].pos.z = z ;
				DrawVert[5].pos.z = z ;

				DrawVert[0].rhw = rhw ;
				DrawVert[1].rhw = rhw ;
				DrawVert[2].rhw = rhw ;
				DrawVert[3].rhw = rhw ;
				DrawVert[4].rhw = rhw ;
				DrawVert[5].rhw = rhw ;

				DrawVert[0].color = DiffuseColor ;
				DrawVert[1].color = DiffuseColor ;
				DrawVert[2].color = DiffuseColor ;
				DrawVert[3].color = DiffuseColor ;
				DrawVert[4].color = DiffuseColor ;
				DrawVert[5].color = DiffuseColor ;

				DrawVert[0].u = TexVert[0].u ;
				DrawVert[1].u = TexVert[1].u ;
				DrawVert[2].u = TexVert[0].u ;
				DrawVert[3].u = TexVert[1].u ;
				DrawVert[4].u = TexVert[0].u ;
				DrawVert[5].u = TexVert[1].u ;

				DrawVert[0].v = TexVert[0].v ;
				DrawVert[1].v = TexVert[0].v ;
				DrawVert[2].v = TexVert[2].v ;
				DrawVert[3].v = TexVert[2].v ;
				DrawVert[4].v = TexVert[2].v ;
				DrawVert[5].v = TexVert[0].v ;

				// �e�N�X�`���[��`�悷��
				if( DrawFlag )
				{
					ADD4VERTEX_TEX
				}
				else
				{
					if( dright  > DrawVert[ 0 ].pos.x ) dright  = DrawVert[ 0 ].pos.x ;
					if( dright  > DrawVert[ 1 ].pos.x ) dright  = DrawVert[ 1 ].pos.x ;
					if( dright  > DrawVert[ 2 ].pos.x ) dright  = DrawVert[ 2 ].pos.x ;
					if( dright  > DrawVert[ 3 ].pos.x ) dright  = DrawVert[ 3 ].pos.x ;

					if( dleft   < DrawVert[ 0 ].pos.x ) dleft   = DrawVert[ 0 ].pos.x ;
					if( dleft   < DrawVert[ 1 ].pos.x ) dleft   = DrawVert[ 1 ].pos.x ;
					if( dleft   < DrawVert[ 2 ].pos.x ) dleft   = DrawVert[ 2 ].pos.x ;
					if( dleft   < DrawVert[ 3 ].pos.x ) dleft   = DrawVert[ 3 ].pos.x ;

					if( dbottom > DrawVert[ 0 ].pos.y ) dbottom = DrawVert[ 0 ].pos.y ;
					if( dbottom > DrawVert[ 1 ].pos.y ) dbottom = DrawVert[ 1 ].pos.y ;
					if( dbottom > DrawVert[ 2 ].pos.y ) dbottom = DrawVert[ 2 ].pos.y ;
					if( dbottom > DrawVert[ 3 ].pos.y ) dbottom = DrawVert[ 3 ].pos.y ;

					if( dtop    < DrawVert[ 0 ].pos.y ) dtop    = DrawVert[ 0 ].pos.y ;
					if( dtop    < DrawVert[ 1 ].pos.y ) dtop    = DrawVert[ 1 ].pos.y ;
					if( dtop    < DrawVert[ 2 ].pos.y ) dtop    = DrawVert[ 2 ].pos.y ;
					if( dtop    < DrawVert[ 3 ].pos.y ) dtop    = DrawVert[ 3 ].pos.y ;
				}
				break ;
			}
		}
	}

	if( DrawFlag == FALSE )
	{
		DrawArea->left   = _FTOL( dleft   ) - 1 ;
		DrawArea->right  = _FTOL( dright  ) + 1 ;
		DrawArea->top    = _FTOL( dtop    ) - 1 ;
		DrawArea->bottom = _FTOL( dbottom ) + 1 ;
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawGraph
extern	int		Graphics_Hardware_DrawGraph_PF( int x, int y, float xf, float yf, IMAGEDATA *Image, IMAGEDATA *BlendImage, int TransFlag, int IntFlag )
{
	VERTEX_2D			*DrawVert ;
	VERTEX_BLENDTEX_2D	*DrawVertB ;
	IMAGEDATA_HARD_DRAW	*DrawTex ;
	IMAGEDATA_HARD_DRAW	*BlendDrawTex = NULL ;
	IMAGEDATA_ORIG		*Orig ;
	IMAGEDATA_HARD_VERT	*TexVert ;
	IMAGEDATA_HARD_VERT	*BlendTexVert ;
	DWORD				DiffuseColor ;
	int					DrawTexNum ;
	int					i ;
	int					j ;
	int					Flag ;
	int					BlendGraphNoIncFlag ;
	float				left ;
	float				right ;
	float				top ;
	float				bottom ;
	float				Vx ;
	float				Vy ;
	float				VBx ;
	float				VBy ;
	DWORD				drawz ;
	float				u[ 2 ] ;
	float				v[ 2 ] ;

	Orig = Image->Orig ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// float���W�␳
//	xf -= 0.5F ;
//	yf -= 0.5F ;

	// �`�揀��
	Flag = TransFlag | ( IntFlag << 1 ) ;
	DX_ANDROID_DRAWPREP_TEX( Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )

	// ���_�f�[�^���擾
	DiffuseColor = GANDR.Device.DrawInfo.DiffuseColor ;

	// �`����̐����Z�b�g
	DrawTexNum = Image->Hard.DrawNum ;

	// �`����̐����u�����h�摜�ƈقȂ��Ă�����O�Ԗڂ̃e�N�X�`���������g�p����
	BlendGraphNoIncFlag = FALSE ;
	if( BlendImage != NULL && BlendImage->Hard.DrawNum != Image->Hard.DrawNum )
	{
		BlendGraphNoIncFlag = TRUE ;
	}

	// �`����z��̃A�h���X���Z�b�g���Ă���
	DrawTex = Image->Hard.Draw ;
	if( BlendImage != NULL )
	{
		BlendDrawTex = BlendImage->Hard.Draw ;
	}

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *( ( DWORD * )&GSYS.DrawSetting.DrawZ ) ;

	// �`��͈͂���͂ݏo�Ă��邩�ǂ����ŏ����𕪊�
	if( GSYS.DrawSetting.Valid2DMatrix || IN_DRAWAREA_CHECK( x, y, x + Image->WidthI, y + Image->HeightI ) )
//	if( x + Image->Width  < GSYS.DrawSetting.DrawArea.right  && x > GSYS.DrawSetting.DrawArea.left &&
//		y + Image->Height < GSYS.DrawSetting.DrawArea.bottom && y > GSYS.DrawSetting.DrawArea.right )
	{
		// �͂ݏo�Ă��Ȃ��ꍇ

		// ���_�^�C�v�ɂ���ď����𕪊�
		if( GANDR.Device.DrawInfo.VertexType == VERTEXTYPE_BLENDTEX )
		{
			// �u�����h�e�N�X�`�����g�p����

			// �e�N�X�`���[�̐������J��Ԃ�
			for( i = 0 ; i < DrawTexNum ; i ++, DrawTex ++ )
			{
				// �`�悷��e�N�X�`���[�̃Z�b�g
				Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
				Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

				if( GANDR.Device.DrawSetting.ChangeTextureFlag )
				{
					Graphics_Android_DeviceState_NormalDrawSetup() ;
				}

				// ���_�o�b�t�@�̎擾
				GETVERTEX_QUAD( DrawVertB )
				
				TexVert = DrawTex->Vertex ;
				BlendTexVert = BlendDrawTex->Vertex ;

				DrawVertB[0].color = ( DWORD )DiffuseColor ;
				DrawVertB[1].color = ( DWORD )DiffuseColor ;
				DrawVertB[2].color = ( DWORD )DiffuseColor ;
				DrawVertB[3].color = ( DWORD )DiffuseColor ;
				DrawVertB[4].color = ( DWORD )DiffuseColor ;
				DrawVertB[5].color = ( DWORD )DiffuseColor ;

				DrawVertB[0].pos.x = xf + TexVert[0].x ;
				DrawVertB[0].pos.y = yf + TexVert[0].y ;
				DrawVertB[1].pos.x = xf + TexVert[1].x ;
				DrawVertB[1].pos.y = yf + TexVert[0].y ;
				DrawVertB[2].pos.x = xf + TexVert[0].x ;
				DrawVertB[2].pos.y = yf + TexVert[2].y ;
				DrawVertB[3].pos.x = xf + TexVert[1].x ;
				DrawVertB[3].pos.y = yf + TexVert[2].y ;
				DrawVertB[4].pos.x = xf + TexVert[0].x ;
				DrawVertB[4].pos.y = yf + TexVert[2].y ;
				DrawVertB[5].pos.x = xf + TexVert[1].x ;
				DrawVertB[5].pos.y = yf + TexVert[0].y ;

				switch( GSYS.DrawSetting.BlendGraphPosMode )
				{
				default :
				case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
					u[ 0 ] = TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ;
					u[ 1 ] = TexVert[1].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ;
					v[ 0 ] = TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ;
					v[ 1 ] = TexVert[2].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ;
					break ;

				case DX_BLENDGRAPH_POSMODE_SCREEN :
					u[ 0 ] = ( xf + TexVert[0].x ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ;
					u[ 1 ] = ( xf + TexVert[1].x ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ;
					v[ 0 ] = ( yf + TexVert[0].y ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ;
					v[ 1 ] = ( yf + TexVert[2].y ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ;
					break ;
				}

				u[ 0 ] *= GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				u[ 1 ] *= GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 0 ] *= GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				v[ 1 ] *= GANDR.Device.DrawSetting.InvBlendTextureHeight ;

				DrawVertB[0].u1 = u[ 0 ] ;
				DrawVertB[0].v1 = v[ 0 ] ;
				DrawVertB[1].u1 = u[ 1 ] ;
				DrawVertB[1].v1 = v[ 0 ] ;
				DrawVertB[2].u1 = u[ 0 ] ;
				DrawVertB[2].v1 = v[ 1 ] ;
				DrawVertB[3].u1 = u[ 1 ] ;
				DrawVertB[3].v1 = v[ 1 ] ;
				DrawVertB[4].u1 = u[ 0 ] ;
				DrawVertB[4].v1 = v[ 1 ] ;
				DrawVertB[5].u1 = u[ 1 ] ;
				DrawVertB[5].v1 = v[ 0 ] ;

				DrawVertB[0].u2 = TexVert[0].u ;
				DrawVertB[0].v2 = TexVert[0].v ;
				DrawVertB[1].u2 = TexVert[1].u ;
				DrawVertB[1].v2 = TexVert[0].v ;
				DrawVertB[2].u2 = TexVert[0].u ;
				DrawVertB[2].v2 = TexVert[2].v ;
				DrawVertB[3].u2 = TexVert[1].u ;
				DrawVertB[3].v2 = TexVert[2].v ;
				DrawVertB[4].u2 = TexVert[0].u ;
				DrawVertB[4].v2 = TexVert[2].v ;
				DrawVertB[5].u2 = TexVert[1].u ;
				DrawVertB[5].v2 = TexVert[0].v ;

				*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[2].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[3].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[4].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[5].pos.z) = drawz ;

				DrawVertB[0].rhw = 1.0f ;
				DrawVertB[1].rhw = 1.0f ;
				DrawVertB[2].rhw = 1.0f ;
				DrawVertB[3].rhw = 1.0f ;
				DrawVertB[4].rhw = 1.0f ;
				DrawVertB[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_BLENDTEX

				if( BlendGraphNoIncFlag == FALSE )
				{
					BlendDrawTex ++ ;
				}
			}
		}
		else
		{
			// �u�����h�e�N�X�`�����g�p���Ȃ�

			// �e�N�X�`���[�̐������J��Ԃ�
			i = 0 ;
			for(;;)
			{
				// ���_�o�b�t�@�̎擾
				GETVERTEX_QUAD( DrawVert )

				// ���_�f�[�^����
				TexVert = DrawTex->Vertex ;
				DrawVert[0].color	= DiffuseColor ;
				DrawVert[1].color	= DiffuseColor ;
				DrawVert[2].color	= DiffuseColor ;
				DrawVert[3].color	= DiffuseColor ;
				DrawVert[4].color	= DiffuseColor ;
				DrawVert[5].color	= DiffuseColor ;

				DrawVert[0].pos.x = TexVert[0].x + xf ;
				DrawVert[0].pos.y = TexVert[0].y + yf ;
				DrawVert[1].pos.x = TexVert[1].x + xf ;
				DrawVert[1].pos.y = TexVert[0].y + yf ;
				DrawVert[2].pos.x = TexVert[0].x + xf ;
				DrawVert[2].pos.y = TexVert[2].y + yf ;
				DrawVert[3].pos.x = TexVert[1].x + xf ;
				DrawVert[3].pos.y = TexVert[2].y + yf ;
				DrawVert[4].pos.x = TexVert[0].x + xf ;
				DrawVert[4].pos.y = TexVert[2].y + yf ;
				DrawVert[5].pos.x = TexVert[1].x + xf ;
				DrawVert[5].pos.y = TexVert[0].y + yf ;

				DrawVert[0].u = TexVert[0].u ;
				DrawVert[0].v = TexVert[0].v ;
				DrawVert[1].u = TexVert[1].u ;
				DrawVert[1].v = TexVert[0].v ;
				DrawVert[2].u = TexVert[0].u ;
				DrawVert[2].v = TexVert[2].v ;
				DrawVert[3].u = TexVert[1].u ;
				DrawVert[3].v = TexVert[2].v ;
				DrawVert[4].u = TexVert[0].u ;
				DrawVert[4].v = TexVert[2].v ;
				DrawVert[5].u = TexVert[1].u ;
				DrawVert[5].v = TexVert[0].v ;

				*((DWORD *)&DrawVert[0].pos.z) = drawz ;
				*((DWORD *)&DrawVert[1].pos.z) = drawz ;
				*((DWORD *)&DrawVert[2].pos.z) = drawz ;
				*((DWORD *)&DrawVert[3].pos.z) = drawz ;
				*((DWORD *)&DrawVert[4].pos.z) = drawz ;
				*((DWORD *)&DrawVert[5].pos.z) = drawz ;

				DrawVert[0].rhw = 1.0f ;
				DrawVert[1].rhw = 1.0f ;
				DrawVert[2].rhw = 1.0f ;
				DrawVert[3].rhw = 1.0f ;
				DrawVert[4].rhw = 1.0f ;
				DrawVert[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_TEX

				i ++ ;
				if( i >= DrawTexNum ) break ;

				// �`�悷��e�N�X�`���[�̃Z�b�g
				DrawTex ++ ;
				Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
				Graphics_Android_DeviceState_NormalDrawSetup() ;
			}
		}
	}
	else
	{
		// �͂ݏo�Ă���ꍇ

		// ���S�ɂ͂ݏo�Ă����牽�������I��
		if( OUT_DRAWAREA_CHECK( x, y, x + Image->WidthI, y + Image->HeightI ) ) return 0 ;
//		if( x > GSYS.DrawSetting.DrawArea.right || x + Image->Width < GSYS.DrawSetting.DrawArea.left ||
//			y > GSYS.DrawSetting.DrawArea.bottom || y + Image->Height < GSYS.DrawSetting.DrawArea.top ) return 0 ;

		// �`���`�̕ۑ�
		left	= GSYS.DrawSetting.DrawAreaF.left   ;
		top		= GSYS.DrawSetting.DrawAreaF.top    ;
		right	= GSYS.DrawSetting.DrawAreaF.right  ;
		bottom	= GSYS.DrawSetting.DrawAreaF.bottom ;

		// ���_�^�C�v�ɂ���ď����𕪊�
		switch( GANDR.Device.DrawInfo.VertexType )
		{
		case VERTEXTYPE_BLENDTEX :
			// �u�����h�e�N�X�`�����g�p����

			// �e�N�X�`���[�̐������J��Ԃ�
			for( i = 0 ; i < DrawTexNum ; i ++, DrawTex ++ )
			{
				VECTOR DrawPos[ 4 ] ;
				float u1[ 4 ] ;
				float v1[ 4 ] ;
				float u2[ 4 ] ;
				float v2[ 4 ] ;

				// �`�悷��e�N�X�`���[�̃Z�b�g
				Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
				Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

				if( GANDR.Device.DrawSetting.ChangeTextureFlag )
				{
					Graphics_Android_DeviceState_NormalDrawSetup() ;
				}

				// ���_�o�b�t�@�̎擾
				GETVERTEX_QUAD( DrawVertB )
				
				TexVert = DrawTex->Vertex ;
				BlendTexVert = BlendDrawTex->Vertex ;

				Vx  = 1.0F / ( float )DrawTex->Tex->TexWidth  ;
				Vy  = 1.0F / ( float )DrawTex->Tex->TexHeight ;
				VBx = GANDR.Device.DrawSetting.InvBlendTextureWidth  ;
				VBy = GANDR.Device.DrawSetting.InvBlendTextureHeight ;

				DrawVertB[0].color = ( DWORD )DiffuseColor ;
				DrawVertB[1].color = ( DWORD )DiffuseColor ;
				DrawVertB[2].color = ( DWORD )DiffuseColor ;
				DrawVertB[3].color = ( DWORD )DiffuseColor ;
				DrawVertB[4].color = ( DWORD )DiffuseColor ;
				DrawVertB[5].color = ( DWORD )DiffuseColor ;

				DrawPos[0].x = TexVert[0].x + xf ;
				DrawPos[0].y = TexVert[0].y + yf ;
				DrawPos[1].x = TexVert[1].x + xf ;
				DrawPos[1].y = TexVert[0].y + yf ;
				DrawPos[2].x = TexVert[0].x + xf ;
				DrawPos[2].y = TexVert[2].y + yf ;
				DrawPos[3].x = TexVert[1].x + xf ;
				DrawPos[3].y = TexVert[2].y + yf ;

				u2[2] = u2[0] = TexVert[0].u ;
				u2[3] = u2[1] = TexVert[1].u ;
				v2[1] = v2[0] = TexVert[0].v ;
				v2[3] = v2[2] = TexVert[2].v ;

				switch( GSYS.DrawSetting.BlendGraphPosMode )
				{
				default :
				case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
					u1[2] = u1[0] = ( TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u1[3] = u1[1] = ( TexVert[1].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					v1[1] = v1[0] = ( TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v1[3] = v1[2] = ( TexVert[2].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					break ;

				case DX_BLENDGRAPH_POSMODE_SCREEN :
					u1[2] = u1[0] = ( ( xf + TexVert[0].x ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u1[3] = u1[1] = ( ( xf + TexVert[1].x ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					v1[1] = v1[0] = ( ( yf + TexVert[0].y ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v1[3] = v1[2] = ( ( yf + TexVert[2].y ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					break ;
				}

				for( j = 0 ; j < 4 ; j ++ )
				{
					// �`���`����o�Ă����ꍇ�̕␳����
					if( DrawPos[ j ].x < left )
					{
						u2[ j ] += ( left - DrawPos[ j ].x ) * Vx ;
						u1[ j ] += ( left - DrawPos[ j ].x ) * VBx ;
						DrawPos[ j ].x = left ;
					}
					else
					if( DrawPos[ j ].x > right )
					{
						u2[ j ] -= ( DrawPos[ j ].x - right ) * Vx ;
						u1[ j ] -= ( DrawPos[ j ].x - right ) * VBx ;
						DrawPos[ j ].x = right ;
					}	

					if( DrawPos[ j ].y < top )
					{
						v2[ j ] += ( top - DrawPos[ j ].y ) * Vy ;
						v1[ j ] += ( top - DrawPos[ j ].y ) * VBy ;
						DrawPos[ j ].y = top ;
					}
					else
					if( DrawPos[ j ].y > bottom )
					{
						v2[ j ] -= ( DrawPos[ j ].y - bottom ) * Vy ;
						v1[ j ] -= ( DrawPos[ j ].y - bottom ) * VBy ;
						DrawPos[ j ].y = bottom ;
					}
				}

				DrawVertB[0].pos.x = DrawPos[0].x ;
				DrawVertB[0].pos.y = DrawPos[0].y ;
				DrawVertB[1].pos.x = DrawPos[1].x ;
				DrawVertB[1].pos.y = DrawPos[1].y ;
				DrawVertB[2].pos.x = DrawPos[2].x ;
				DrawVertB[2].pos.y = DrawPos[2].y ;
				DrawVertB[3].pos.x = DrawPos[3].x ;
				DrawVertB[3].pos.y = DrawPos[3].y ;
				DrawVertB[4].pos.x = DrawPos[2].x ;
				DrawVertB[4].pos.y = DrawPos[2].y ;
				DrawVertB[5].pos.x = DrawPos[1].x ;
				DrawVertB[5].pos.y = DrawPos[1].y ;

				DrawVertB[0].u1 = u1[0] ;
				DrawVertB[0].v1 = v1[0] ;
				DrawVertB[1].u1 = u1[1] ;
				DrawVertB[1].v1 = v1[1] ;
				DrawVertB[2].u1 = u1[2] ;
				DrawVertB[2].v1 = v1[2] ;
				DrawVertB[3].u1 = u1[3] ;
				DrawVertB[3].v1 = v1[3] ;
				DrawVertB[4].u1 = u1[2] ;
				DrawVertB[4].v1 = v1[2] ;
				DrawVertB[5].u1 = u1[1] ;
				DrawVertB[5].v1 = v1[1] ;

				DrawVertB[0].u2 = u2[0] ;
				DrawVertB[0].v2 = v2[0] ;
				DrawVertB[1].u2 = u2[1] ;
				DrawVertB[1].v2 = v2[1] ;
				DrawVertB[2].u2 = u2[2] ;
				DrawVertB[2].v2 = v2[2] ;
				DrawVertB[3].u2 = u2[3] ;
				DrawVertB[3].v2 = v2[3] ;
				DrawVertB[4].u2 = u2[2] ;
				DrawVertB[4].v2 = v2[2] ;
				DrawVertB[5].u2 = u2[1] ;
				DrawVertB[5].v2 = v2[1] ;

				*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[2].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[3].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[4].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[5].pos.z) = drawz ;

				DrawVertB[0].rhw = 1.0f ;
				DrawVertB[1].rhw = 1.0f ;
				DrawVertB[2].rhw = 1.0f ;
				DrawVertB[3].rhw = 1.0f ;
				DrawVertB[4].rhw = 1.0f ;
				DrawVertB[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_BLENDTEX

				if( BlendGraphNoIncFlag == FALSE )
				{
					BlendDrawTex ++ ;
				}
			}
			break ;
		
		case VERTEXTYPE_TEX :
			// �u�����h�e�N�X�`�����g�p���Ȃ�

			// �e�N�X�`���[�̐������J��Ԃ�
			i = 0 ;
			for(;;)
			{
				VECTOR DrawPos[ 4 ] ;
				float u[ 4 ] ;
				float v[ 4 ] ;

				// ���_�o�b�t�@�̎擾
				GETVERTEX_QUAD( DrawVert )
				
				// ���_�f�[�^����
				TexVert = DrawTex->Vertex ;
				DrawVert[0].color	= DiffuseColor ;
				DrawVert[1].color	= DiffuseColor ;
				DrawVert[2].color	= DiffuseColor ;
				DrawVert[3].color	= DiffuseColor ;
				DrawVert[4].color	= DiffuseColor ;
				DrawVert[5].color	= DiffuseColor ;

				DrawPos[0].x = TexVert[0].x + xf ;
				DrawPos[0].y = TexVert[0].y + yf ;
				DrawPos[1].x = TexVert[1].x + xf ;
				DrawPos[1].y = TexVert[0].y + yf ;
				DrawPos[2].x = TexVert[0].x + xf ;
				DrawPos[2].y = TexVert[2].y + yf ;
				DrawPos[3].x = TexVert[1].x + xf ;
				DrawPos[3].y = TexVert[2].y + yf ;

				u[2] = u[0] = TexVert[0].u ;
				u[3] = u[1] = TexVert[1].u ;
				v[1] = v[0] = TexVert[0].v ;
				v[3] = v[2] = TexVert[2].v ;
				
				// ���_�f�[�^������������
				Vx	= 1.0F / ( float )DrawTex->Tex->TexWidth ;
				Vy	= 1.0F / ( float )DrawTex->Tex->TexHeight ;
				for( j = 0 ; j < 4 ; j ++ )
				{
					// �`���`����o�Ă����ꍇ�̕␳����
					if( DrawPos[ j ].x < left )
					{
						u[ j ] += ( left - DrawPos[ j ].x ) * Vx ;
						DrawPos[ j ].x = left ;
					}
					else
					if( DrawPos[ j ].x > right )
					{
						u[ j ] -= ( DrawPos[ j ].x - right ) * Vx ;
						DrawPos[ j ].x = right ;
					}	

					if( DrawPos[ j ].y < top )
					{
						v[ j ] += ( top - DrawPos[ j ].y ) * Vy ;
						DrawPos[ j ].y = top ;
					}
					else
					if( DrawPos[ j ].y > bottom )
					{
						v[ j ] -= ( DrawPos[ j ].y - bottom ) * Vy ;
						DrawPos[ j ].y = bottom ;
					}
				}

				DrawVert[0].pos.x = DrawPos[0].x ;
				DrawVert[0].pos.y = DrawPos[0].y ;
				DrawVert[1].pos.x = DrawPos[1].x ;
				DrawVert[1].pos.y = DrawPos[1].y ;
				DrawVert[2].pos.x = DrawPos[2].x ;
				DrawVert[2].pos.y = DrawPos[2].y ;
				DrawVert[3].pos.x = DrawPos[3].x ;
				DrawVert[3].pos.y = DrawPos[3].y ;
				DrawVert[4].pos.x = DrawPos[2].x ;
				DrawVert[4].pos.y = DrawPos[2].y ;
				DrawVert[5].pos.x = DrawPos[1].x ;
				DrawVert[5].pos.y = DrawPos[1].y ;

				DrawVert[0].u = u[0] ;
				DrawVert[0].v = v[0] ;
				DrawVert[1].u = u[1] ;
				DrawVert[1].v = v[1] ;
				DrawVert[2].u = u[2] ;
				DrawVert[2].v = v[2] ;
				DrawVert[3].u = u[3] ;
				DrawVert[3].v = v[3] ;
				DrawVert[4].u = u[2] ;
				DrawVert[4].v = v[2] ;
				DrawVert[5].u = u[1] ;
				DrawVert[5].v = v[1] ;

				*((DWORD *)&DrawVert[0].pos.z) = drawz ;
				*((DWORD *)&DrawVert[1].pos.z) = drawz ;
				*((DWORD *)&DrawVert[2].pos.z) = drawz ;
				*((DWORD *)&DrawVert[3].pos.z) = drawz ;
				*((DWORD *)&DrawVert[4].pos.z) = drawz ;
				*((DWORD *)&DrawVert[5].pos.z) = drawz ;

				DrawVert[0].rhw = 1.0f ;
				DrawVert[1].rhw = 1.0f ;
				DrawVert[2].rhw = 1.0f ;
				DrawVert[3].rhw = 1.0f ;
				DrawVert[4].rhw = 1.0f ;
				DrawVert[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_TEX

				i ++ ;
				if( i >= DrawTexNum ) break ;

				// �`�悷��e�N�X�`���[�̃Z�b�g
				DrawTex ++ ;
				Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
				Graphics_Android_DeviceState_NormalDrawSetup() ;
			}
			break ;
		}
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawExtendGraph
extern	int		Graphics_Hardware_DrawExtendGraph_PF( int x1, int y1, int x2, int y2, float x1f, float y1f, float x2f, float y2f, IMAGEDATA *Image, IMAGEDATA *BlendImage, int TransFlag, int IntFlag )
{
	VERTEX_2D *DrawVert ;
	VERTEX_BLENDTEX_2D *DrawVertB ; 
	IMAGEDATA_HARD_DRAW *DrawTex ;
	IMAGEDATA_HARD_DRAW *BlendDrawTex = NULL ;
	IMAGEDATA_HARD_VERT *TexVert ;
	IMAGEDATA_HARD_VERT *BlendTexVert ;
	IMAGEDATA_ORIG *Orig ;
	int DrawTexNum ;
	int i, j ;
	int BlendGraphNoIncFlag ;
	float GraphExRateX, GraphExRateY ;
//	int ReverseX = FALSE, ReverseY = FALSE ;
//	int Reverse ;
//	int AdjX = FALSE, AdjY = FALSE ;
	float left, right, top, bottom ;
	float Vx, Vy ;
	float VBx, VBy ;
	DWORD DiffuseColor ;
	DWORD drawz ;
	int Flag ;
	float XBuf[ 2 ] ;
	float YBuf[ 2 ] ;
	float u[ 2 ] ;
	float v[ 2 ] ;

	Orig = Image->Orig ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`�攻��
//	if( x2 - x1 == Image->Width && y2 - y1 == Image->Height ) return G_D3D_DrawGraph( x1, y1, GraphData, TransFlag ) ; 	

	// �����Ȃ������ꍇ�̓G���[
	if( x1 == x2 || y1 == y2 ) return -1 ;

	// �`��̏���
	Flag = TransFlag | ( IntFlag ? ( GSYS.DrawSetting.DrawMode == DX_DRAWMODE_BILINEAR ? 0 : DX_ANDROID_DRAWPREP_VECTORINT ) : 0 ) ;
	DX_ANDROID_DRAWPREP_TEX( Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )

	// �f�B�t���[�Y�J���[�̎擾
	DiffuseColor = GANDR.Device.DrawInfo.DiffuseColor ;

	// �`����̐����Z�b�g
	DrawTexNum = Image->Hard.DrawNum ;

	// �`����̐����u�����h�摜�ƈقȂ��Ă�����O�Ԗڂ̃e�N�X�`���������g�p����
	BlendGraphNoIncFlag = FALSE ;
	if( BlendImage != NULL && BlendImage->Hard.DrawNum != Image->Hard.DrawNum )
	{
		BlendGraphNoIncFlag = TRUE ;
	}

	// �`����z��̃A�h���X���Z�b�g���Ă���
	DrawTex = Image->Hard.Draw ;
	if( BlendImage != NULL )
	{
		BlendDrawTex = BlendImage->Hard.Draw ;
	}

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �g�嗦���擾���Ă���
	GraphExRateX = ( x2f - x1f ) / Image->WidthF ;
	GraphExRateY = ( y2f - y1f ) / Image->HeightF ;
//	Reverse = ( GraphExRateX < 0 ) != ( GraphExRateY < 0 ) ;

//	x1f -= 0.5F ;
//	y1f -= 0.5F ;

	if( x1 > x2 ){ i = x2; x2 = x1; x1 = i; }
	if( y1 > y2 ){ i = y2; y2 = y1; y1 = i; }

	// �`��͈͂���͂ݏo�Ă��邩�ǂ����ŏ����𕪊�
	if( GSYS.DrawSetting.Valid2DMatrix || IN_DRAWAREA_CHECK( x1, y1, x2, y2 ) )
	{
		// ���_�^�C�v�ɂ���ď����𕪊�
		switch( GANDR.Device.DrawInfo.VertexType )
		{
		case VERTEXTYPE_BLENDTEX :	// �u�����h�e�N�X�`�����g�p����
			// �e�N�X�`���[�̐������J��Ԃ�
			for( i = 0 ; i < DrawTexNum ; i ++, DrawTex ++ )
			{
				// �`�悷��e�N�X�`���[�̃Z�b�g
				Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
				Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

				if( GANDR.Device.DrawSetting.ChangeTextureFlag )
				{
					Graphics_Android_DeviceState_NormalDrawSetup() ;
				}

				// ���_�f�[�^������������
				GETVERTEX_QUAD( DrawVertB )
				
				TexVert = DrawTex->Vertex ;
				BlendTexVert = BlendDrawTex->Vertex ;

				DrawVertB[0].color = ( DWORD )DiffuseColor ;
				DrawVertB[1].color = ( DWORD )DiffuseColor ;
				DrawVertB[2].color = ( DWORD )DiffuseColor ;
				DrawVertB[3].color = ( DWORD )DiffuseColor ;
				DrawVertB[4].color = ( DWORD )DiffuseColor ;
				DrawVertB[5].color = ( DWORD )DiffuseColor ;

				XBuf[ 0 ] = TexVert[0].x * GraphExRateX + x1f ;
				XBuf[ 1 ] = TexVert[1].x * GraphExRateX + x1f ;
				YBuf[ 0 ] = TexVert[0].y * GraphExRateY + y1f ;
				YBuf[ 1 ] = TexVert[2].y * GraphExRateY + y1f ;
				DrawVertB[0].pos.x = XBuf[ 0 ] ;
				DrawVertB[0].pos.y = YBuf[ 0 ] ;
				DrawVertB[1].pos.x = XBuf[ 1 ] ;
				DrawVertB[1].pos.y = YBuf[ 0 ] ;
				DrawVertB[2].pos.x = XBuf[ 0 ] ;
				DrawVertB[2].pos.y = YBuf[ 1 ] ;
				DrawVertB[3].pos.x = XBuf[ 1 ] ;
				DrawVertB[3].pos.y = YBuf[ 1 ] ;
				DrawVertB[4].pos.x = XBuf[ 0 ] ;
				DrawVertB[4].pos.y = YBuf[ 1 ] ;
				DrawVertB[5].pos.x = XBuf[ 1 ] ;
				DrawVertB[5].pos.y = YBuf[ 0 ] ;

				switch( GSYS.DrawSetting.BlendGraphPosMode )
				{
				default :
				case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
					u[ 0 ] = TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ;
					u[ 1 ] = TexVert[1].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ;
					v[ 0 ] = TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ;
					v[ 1 ] = TexVert[2].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ;
					break ;

				case DX_BLENDGRAPH_POSMODE_SCREEN :
					u[ 0 ] = XBuf[ 0 ] - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ;
					u[ 1 ] = XBuf[ 1 ] - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ;
					v[ 0 ] = YBuf[ 0 ] - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ;
					v[ 1 ] = YBuf[ 1 ] - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ;
					break ;
				}

				u[ 0 ] *= GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				u[ 1 ] *= GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 0 ] *= GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				v[ 1 ] *= GANDR.Device.DrawSetting.InvBlendTextureHeight ;

				DrawVertB[0].u1 = u[ 0 ] ;
				DrawVertB[0].v1 = v[ 0 ] ;
				DrawVertB[1].u1 = u[ 1 ] ;
				DrawVertB[1].v1 = v[ 0 ] ;
				DrawVertB[2].u1 = u[ 0 ] ;
				DrawVertB[2].v1 = v[ 1 ] ;
				DrawVertB[3].u1 = u[ 1 ] ;
				DrawVertB[3].v1 = v[ 1 ] ;
				DrawVertB[4].u1 = u[ 0 ] ;
				DrawVertB[4].v1 = v[ 1 ] ;
				DrawVertB[5].u1 = u[ 1 ] ;
				DrawVertB[5].v1 = v[ 0 ] ;

				DrawVertB[0].u2 = TexVert[0].u ;
				DrawVertB[0].v2 = TexVert[0].v ;
				DrawVertB[1].u2 = TexVert[1].u ;
				DrawVertB[1].v2 = TexVert[0].v ;
				DrawVertB[2].u2 = TexVert[0].u ;
				DrawVertB[2].v2 = TexVert[2].v ;
				DrawVertB[3].u2 = TexVert[1].u ;
				DrawVertB[3].v2 = TexVert[2].v ;
				DrawVertB[4].u2 = TexVert[0].u ;
				DrawVertB[4].v2 = TexVert[2].v ;
				DrawVertB[5].u2 = TexVert[1].u ;
				DrawVertB[5].v2 = TexVert[0].v ;

				*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[2].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[3].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[4].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[5].pos.z) = drawz ;

				DrawVertB[0].rhw = 1.0f ;
				DrawVertB[1].rhw = 1.0f ;
				DrawVertB[2].rhw = 1.0f ;
				DrawVertB[3].rhw = 1.0f ;
				DrawVertB[4].rhw = 1.0f ;
				DrawVertB[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_BLENDTEX

				if( BlendGraphNoIncFlag == FALSE )
				{
					BlendDrawTex ++ ;
				}
			}
			break ;

		case VERTEXTYPE_TEX :	// �u�����h�e�N�X�`�����g�p���Ȃ�
			// �e�N�X�`���[�̐������J��Ԃ�
			i = 0 ;
			for(;;)
			{
				// ���_�f�[�^������������
				GETVERTEX_QUAD( DrawVert )
				
				TexVert = DrawTex->Vertex ;
				
				DrawVert[0].color = ( DWORD )DiffuseColor ;
				DrawVert[1].color = ( DWORD )DiffuseColor ;
				DrawVert[2].color = ( DWORD )DiffuseColor ;
				DrawVert[3].color = ( DWORD )DiffuseColor ;
				DrawVert[4].color = ( DWORD )DiffuseColor ;
				DrawVert[5].color = ( DWORD )DiffuseColor ;

				XBuf[ 0 ] = TexVert[0].x * GraphExRateX + x1f ;
				XBuf[ 1 ] = TexVert[1].x * GraphExRateX + x1f ;
				YBuf[ 0 ] = TexVert[0].y * GraphExRateY + y1f ;
				YBuf[ 1 ] = TexVert[2].y * GraphExRateY + y1f ;
				DrawVert[0].pos.x = XBuf[ 0 ] ;
				DrawVert[0].pos.y = YBuf[ 0 ] ;
				DrawVert[1].pos.x = XBuf[ 1 ] ;
				DrawVert[1].pos.y = YBuf[ 0 ] ;
				DrawVert[2].pos.x = XBuf[ 0 ] ;
				DrawVert[2].pos.y = YBuf[ 1 ] ;
				DrawVert[3].pos.x = XBuf[ 1 ] ;
				DrawVert[3].pos.y = YBuf[ 1 ] ;
				DrawVert[4].pos.x = XBuf[ 0 ] ;
				DrawVert[4].pos.y = YBuf[ 1 ] ;
				DrawVert[5].pos.x = XBuf[ 1 ] ;
				DrawVert[5].pos.y = YBuf[ 0 ] ;

				DrawVert[0].u = TexVert[0].u ;
				DrawVert[0].v = TexVert[0].v ;
				DrawVert[1].u = TexVert[1].u ;
				DrawVert[1].v = TexVert[0].v ;
				DrawVert[2].u = TexVert[0].u ;
				DrawVert[2].v = TexVert[2].v ;
				DrawVert[3].u = TexVert[1].u ;
				DrawVert[3].v = TexVert[2].v ;
				DrawVert[4].u = TexVert[0].u ;
				DrawVert[4].v = TexVert[2].v ;
				DrawVert[5].u = TexVert[1].u ;
				DrawVert[5].v = TexVert[0].v ;

				*((DWORD *)&DrawVert[0].pos.z) = drawz ;
				*((DWORD *)&DrawVert[1].pos.z) = drawz ;
				*((DWORD *)&DrawVert[2].pos.z) = drawz ;
				*((DWORD *)&DrawVert[3].pos.z) = drawz ;
				*((DWORD *)&DrawVert[4].pos.z) = drawz ;
				*((DWORD *)&DrawVert[5].pos.z) = drawz ;

				DrawVert[0].rhw = 1.0f ;
				DrawVert[1].rhw = 1.0f ;
				DrawVert[2].rhw = 1.0f ;
				DrawVert[3].rhw = 1.0f ;
				DrawVert[4].rhw = 1.0f ;
				DrawVert[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_TEX

				i ++ ;
				if( i >= DrawTexNum ) break ;

				// �`�悷��e�N�X�`���[�̃Z�b�g
				DrawTex ++ ;
				Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
				Graphics_Android_DeviceState_NormalDrawSetup() ;
			}
			break ;
		}
	}
	else
	{
		// ���S�ɂ͂ݏo�Ă����牽�������I��
		if( OUT_DRAWAREA_CHECK( x1, y1, x2, y2 ) ) return 0 ;

		// �`���`�̕ۑ�
		left	= GSYS.DrawSetting.DrawAreaF.left   ;
		top		= GSYS.DrawSetting.DrawAreaF.top    ;
		right	= GSYS.DrawSetting.DrawAreaF.right  ;
		bottom	= GSYS.DrawSetting.DrawAreaF.bottom ;

		// ���_�^�C�v�ɂ���ď����𕪊�
		switch( GANDR.Device.DrawInfo.VertexType )
		{
		case VERTEXTYPE_BLENDTEX :	// �u�����h�e�N�X�`�����g�p����
			// �e�N�X�`���[�̐������J��Ԃ�
			for( i = 0 ; i < DrawTexNum ; i ++, DrawTex ++ )
			{
				VECTOR DrawPos[ 4 ] ;
				float u1[ 4 ] ;
				float v1[ 4 ] ;
				float u2[ 4 ] ;
				float v2[ 4 ] ;

				// �`�悷��e�N�X�`���[�̃Z�b�g
				Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
				Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

				if( GANDR.Device.DrawSetting.ChangeTextureFlag )
				{
					Graphics_Android_DeviceState_NormalDrawSetup() ;
				}

				GETVERTEX_QUAD( DrawVertB )
				
				Vx = 1.0F / ( DrawTex->Tex->TexWidth * GraphExRateX ) ;
				Vy = 1.0F / ( DrawTex->Tex->TexHeight * GraphExRateY ) ;
				VBx = GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				VBy = GANDR.Device.DrawSetting.InvBlendTextureHeight ;

				// ���_�f�[�^������������
				TexVert = DrawTex->Vertex ;
				BlendTexVert = BlendDrawTex->Vertex ;

				DrawVertB[0].color = ( DWORD )DiffuseColor ;
				DrawVertB[1].color = ( DWORD )DiffuseColor ;
				DrawVertB[2].color = ( DWORD )DiffuseColor ;
				DrawVertB[3].color = ( DWORD )DiffuseColor ;
				DrawVertB[4].color = ( DWORD )DiffuseColor ;
				DrawVertB[5].color = ( DWORD )DiffuseColor ;

				XBuf[ 0 ] = TexVert[0].x * GraphExRateX + x1f ;
				XBuf[ 1 ] = TexVert[1].x * GraphExRateX + x1f ;
				YBuf[ 0 ] = TexVert[0].y * GraphExRateY + y1f ;
				YBuf[ 1 ] = TexVert[2].y * GraphExRateY + y1f ;
				DrawPos[0].x = XBuf[ 0 ] ;
				DrawPos[0].y = YBuf[ 0 ] ;
				DrawPos[1].x = XBuf[ 1 ] ;
				DrawPos[1].y = YBuf[ 0 ] ;
				DrawPos[2].x = XBuf[ 0 ] ;
				DrawPos[2].y = YBuf[ 1 ] ;
				DrawPos[3].x = XBuf[ 1 ] ;
				DrawPos[3].y = YBuf[ 1 ] ;

				switch( GSYS.DrawSetting.BlendGraphPosMode )
				{
				default :
				case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
					u1[2] = u1[0] = ( TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u1[3] = u1[1] = ( TexVert[1].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					v1[1] = v1[0] = ( TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v1[3] = v1[2] = ( TexVert[2].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					break ;

				case DX_BLENDGRAPH_POSMODE_SCREEN :
					u1[2] = u1[0] = ( XBuf[ 0 ] - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u1[3] = u1[1] = ( XBuf[ 1 ] - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					v1[1] = v1[0] = ( YBuf[ 0 ] - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v1[3] = v1[2] = ( YBuf[ 1 ] - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					break ;
				}

				u2[2] = u2[0] = TexVert[0].u ;
				u2[3] = u2[1] = TexVert[1].u ;
				v2[1] = v2[0] = TexVert[0].v ;
				v2[3] = v2[2] = TexVert[2].v ;

				for( j = 0 ; j < 4 ; j ++ )
				{
					// �`���`����o�Ă����ꍇ�̕␳����
					if( DrawPos[ j ].x < left )
					{
						u2[ j ] += ( left - DrawPos[ j ].x ) * Vx ;
						u1[ j ] += ( left - DrawPos[ j ].x ) * VBx ;
						DrawPos[ j ].x = left ;
					}
					else
					if( DrawPos[ j ].x > right )
					{
						u2[ j ] -= ( DrawPos[ j ].x - right ) * Vx ;
						u1[ j ] -= ( DrawPos[ j ].x - right ) * VBx ;
						DrawPos[ j ].x = right ;
					}	

					if( DrawPos[ j ].y < top )
					{
						v2[ j ] += ( top - DrawPos[ j ].y ) * Vy ;
						v1[ j ] += ( top - DrawPos[ j ].y ) * VBy ;
						DrawPos[ j ].y = top ;
					}
					else
					if( DrawPos[ j ].y > bottom )
					{
						v2[ j ] -= ( DrawPos[ j ].y - bottom ) * Vy ;
						v1[ j ] -= ( DrawPos[ j ].y - bottom ) * VBy ;
						DrawPos[ j ].y = bottom ;
					}
				}

				DrawVertB[0].pos.x = DrawPos[0].x ;
				DrawVertB[0].pos.y = DrawPos[0].y ;
				DrawVertB[1].pos.x = DrawPos[1].x ;
				DrawVertB[1].pos.y = DrawPos[1].y ;
				DrawVertB[2].pos.x = DrawPos[2].x ;
				DrawVertB[2].pos.y = DrawPos[2].y ;
				DrawVertB[3].pos.x = DrawPos[3].x ;
				DrawVertB[3].pos.y = DrawPos[3].y ;
				DrawVertB[4].pos.x = DrawPos[2].x ;
				DrawVertB[4].pos.y = DrawPos[2].y ;
				DrawVertB[5].pos.x = DrawPos[1].x ;
				DrawVertB[5].pos.y = DrawPos[1].y ;

				DrawVertB[0].u1 = u1[0] ;
				DrawVertB[0].v1 = v1[0] ;
				DrawVertB[1].u1 = u1[1] ;
				DrawVertB[1].v1 = v1[1] ;
				DrawVertB[2].u1 = u1[2] ;
				DrawVertB[2].v1 = v1[2] ;
				DrawVertB[3].u1 = u1[3] ;
				DrawVertB[3].v1 = v1[3] ;
				DrawVertB[4].u1 = u1[2] ;
				DrawVertB[4].v1 = v1[2] ;
				DrawVertB[5].u1 = u1[1] ;
				DrawVertB[5].v1 = v1[1] ;

				DrawVertB[0].u2 = u2[0] ;
				DrawVertB[0].v2 = v2[0] ;
				DrawVertB[1].u2 = u2[1] ;
				DrawVertB[1].v2 = v2[1] ;
				DrawVertB[2].u2 = u2[2] ;
				DrawVertB[2].v2 = v2[2] ;
				DrawVertB[3].u2 = u2[3] ;
				DrawVertB[3].v2 = v2[3] ;
				DrawVertB[4].u2 = u2[2] ;
				DrawVertB[4].v2 = v2[2] ;
				DrawVertB[5].u2 = u2[1] ;
				DrawVertB[5].v2 = v2[1] ;

				*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[2].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[3].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[4].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[5].pos.z) = drawz ;

				DrawVertB[0].rhw = 1.0f ;
				DrawVertB[1].rhw = 1.0f ;
				DrawVertB[2].rhw = 1.0f ;
				DrawVertB[3].rhw = 1.0f ;
				DrawVertB[4].rhw = 1.0f ;
				DrawVertB[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_BLENDTEX

				if( BlendGraphNoIncFlag == FALSE )
				{
					BlendDrawTex ++ ;
				}
			}
			break ;

		case VERTEXTYPE_TEX :	// �u�����h�e�N�X�`�����g�p���Ȃ�
			// �e�N�X�`���[�̐������J��Ԃ�
			i = 0 ;
			for(;;)
			{
				VECTOR DrawPos[ 4 ] ;
				float u[ 4 ] ;
				float v[ 4 ] ;

				// ���_�f�[�^������������
				GETVERTEX_QUAD( DrawVert )
				
				TexVert = DrawTex->Vertex ;

				DrawVert[0].color = ( DWORD )DiffuseColor ;
				DrawVert[1].color = ( DWORD )DiffuseColor ;
				DrawVert[2].color = ( DWORD )DiffuseColor ;
				DrawVert[3].color = ( DWORD )DiffuseColor ;
				DrawVert[4].color = ( DWORD )DiffuseColor ;
				DrawVert[5].color = ( DWORD )DiffuseColor ;

				XBuf[ 0 ] = TexVert[0].x * GraphExRateX + x1f ;
				XBuf[ 1 ] = TexVert[1].x * GraphExRateX + x1f ;
				YBuf[ 0 ] = TexVert[0].y * GraphExRateY + y1f ;
				YBuf[ 1 ] = TexVert[2].y * GraphExRateY + y1f ;
				DrawPos[0].x = XBuf[ 0 ] ;
				DrawPos[0].y = YBuf[ 0 ] ;
				DrawPos[1].x = XBuf[ 1 ] ;
				DrawPos[1].y = YBuf[ 0 ] ;
				DrawPos[2].x = XBuf[ 0 ] ;
				DrawPos[2].y = YBuf[ 1 ] ;
				DrawPos[3].x = XBuf[ 1 ] ;
				DrawPos[3].y = YBuf[ 1 ] ;

				u[2] = u[0] = TexVert[0].u ;
				u[3] = u[1] = TexVert[1].u ;
				v[1] = v[0] = TexVert[0].v ;
				v[3] = v[2] = TexVert[2].v ;

				Vx = 1.0F / ( DrawTex->Tex->TexWidth * GraphExRateX ) ;
				Vy = 1.0F / ( DrawTex->Tex->TexHeight * GraphExRateY ) ;
				for( j = 0 ; j < 4 ; j ++ )
				{
					// �`���`����o�Ă����ꍇ�̕␳����
					if( DrawPos[ j ].x < left )
					{
						u[ j ] += ( left - DrawPos[ j ].x ) * Vx ;
						DrawPos[ j ].x = left ;
					}
					else
					if( DrawPos[ j ].x > right )
					{
						u[ j ] -= ( DrawPos[ j ].x - right ) * Vx ;
						DrawPos[ j ].x = right ;
					}	

					if( DrawPos[ j ].y < top )
					{
						v[ j ] += ( top - DrawPos[ j ].y ) * Vy ;
						DrawPos[ j ].y = top ;
					}
					else
					if( DrawPos[ j ].y > bottom )
					{
						v[ j ] -= ( DrawPos[ j ].y - bottom ) * Vy ;
						DrawPos[ j ].y = bottom ;
					}
				}

				DrawVert[0].pos.x = DrawPos[0].x ;
				DrawVert[0].pos.y = DrawPos[0].y ;
				DrawVert[1].pos.x = DrawPos[1].x ;
				DrawVert[1].pos.y = DrawPos[1].y ;
				DrawVert[2].pos.x = DrawPos[2].x ;
				DrawVert[2].pos.y = DrawPos[2].y ;
				DrawVert[3].pos.x = DrawPos[3].x ;
				DrawVert[3].pos.y = DrawPos[3].y ;
				DrawVert[4].pos.x = DrawPos[2].x ;
				DrawVert[4].pos.y = DrawPos[2].y ;
				DrawVert[5].pos.x = DrawPos[1].x ;
				DrawVert[5].pos.y = DrawPos[1].y ;

				DrawVert[0].u = u[0] ;
				DrawVert[0].v = v[0] ;
				DrawVert[1].u = u[1] ;
				DrawVert[1].v = v[1] ;
				DrawVert[2].u = u[2] ;
				DrawVert[2].v = v[2] ;
				DrawVert[3].u = u[3] ;
				DrawVert[3].v = v[3] ;
				DrawVert[4].u = u[2] ;
				DrawVert[4].v = v[2] ;
				DrawVert[5].u = u[1] ;
				DrawVert[5].v = v[1] ;

				*((DWORD *)&DrawVert[0].pos.z) = drawz ;
				*((DWORD *)&DrawVert[1].pos.z) = drawz ;
				*((DWORD *)&DrawVert[2].pos.z) = drawz ;
				*((DWORD *)&DrawVert[3].pos.z) = drawz ;
				*((DWORD *)&DrawVert[4].pos.z) = drawz ;
				*((DWORD *)&DrawVert[5].pos.z) = drawz ;

				DrawVert[0].rhw = 1.0f ;
				DrawVert[1].rhw = 1.0f ;
				DrawVert[2].rhw = 1.0f ;
				DrawVert[3].rhw = 1.0f ;
				DrawVert[4].rhw = 1.0f ;
				DrawVert[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_TEX

				i ++ ;
				if( i >= DrawTexNum ) break ;

				// �`�悷��e�N�X�`���[�̃Z�b�g
				DrawTex ++ ;
				Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
				Graphics_Android_DeviceState_NormalDrawSetup() ;
			}
			break ;
		}
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawRotaGraph
extern	int		Graphics_Hardware_DrawRotaGraph_PF( int x, int y, float xf, float yf, double ExRate, double Angle, IMAGEDATA *Image, IMAGEDATA *BlendImage, int TransFlag, int ReverseXFlag, int ReverseYFlag, int IntFlag )
{
	VERTEX_2D *DrawVert ;
	VERTEX_BLENDTEX_2D *DrawVertB ;
	VECTOR DrawPos[ 4 ] ;
	DWORD DiffuseColor ;
	IMAGEDATA_HARD_DRAW *DrawTex ;
	IMAGEDATA_HARD_DRAW *BlendDrawTex = NULL ;
	IMAGEDATA_HARD_VERT *TexVert ;
	IMAGEDATA_HARD_VERT *BlendTexVert ;
	int DrawTexNum ;
	int i ; 
	float Sin = 0.0f, Cos = 1.0f ;
	int BlendGraphNoIncFlag ;
	float XBuf[ 8 ], YBuf[ 8 ] ;
	float u[ 4 ], v[ 4 ] ;
	float ExtendRate = ( float )ExRate ; 
	float ExtendRateX ;
	float ExtendRateY ;
	DWORD drawz ;
//	BOOL Adj = FALSE ;
	float CenX, CenY ;
	float fx, fy ;
	int hx = 0, hy = 0 ;
	int FastCode, SinCosNone, AngleCheck, AlwaysCheck ;
	int Flag ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �����Ȃ������ꍇ�̓G���[
	if( ExRate == 0.0 ) return -1 ;

	// �`��̏���
	Flag = TransFlag ;
	DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )

	// ��]�v�f�����������ׂ�
	if( Angle == 0.0 )
	{
		SinCosNone = 1;
	}
	else
	{
		SinCosNone = 0;
		_SINCOS( (float)Angle, &Sin, &Cos ) ;
	}
//	if( _FABS( (float)Angle ) < 0.0001 && ExRate < 1.001 && ExRate > 0.999 ) Adj = TRUE ;

	// ���W�̕␳
	if( IntFlag || GSYS.DrawSetting.DrawMode == DX_DRAWMODE_NEAREST )
	{
		AlwaysCheck = 0 ;
		FastCode    = 0 ;
		hx          = Image->WidthI % 2 ;
		hy          = Image->HeightI % 2 ;
		fx = xf - ( float )x ;
		fy = yf - ( float )y ;
		if( fx < 0.0f ) fx = -fx;
		if( fy < 0.0f ) fy = -fy;
		if( fx < 0.00001f && fy < 0.00001f )
		{
			if( ExRate == 1.0 )
			{
				if( hx == hy )
				{
					if( hx == 0 )
					{
						CenX = ( float )(Image->WidthI >> 1) ;
						CenY = ( float )(Image->HeightI >> 1) ;
						xf   = ( float )x ;
						yf   = ( float )y ;
					}
					else
					{
						CenX = ( float )Image->WidthI * 0.5F ;
						CenY = ( float )Image->HeightI * 0.5F ;
						xf   = ( float )x - 0.5F ;
						yf   = ( float )y - 0.5F ;
						FastCode = 1;
					}
				}
				else
				{
					CenX = ( float )Image->WidthI * 0.5F ;
					CenY = ( float )Image->HeightI * 0.5F ;
					xf   = ( float )x ;
					yf   = ( float )y ;
						
					if( hx != 0 ) CenX -= 0.5F ;
					if( hy != 0 ) CenY -= 0.5F ;
				}
			}
			else
			{
				CenX = ( float )Image->WidthI * 0.5F ;
				CenY = ( float )Image->HeightI * 0.5F ;
				xf   = ( float )x ;
				yf   = ( float )y ;
				FastCode = 1 ;
			}
		}
		else
		{
			CenX = ( float )Image->WidthI * 0.5F ;
			CenY = ( float )Image->HeightI * 0.5F ;
			xf   = ( float )x + 0.5f ;
			yf   = ( float )y + 0.5f ;
			AlwaysCheck = 1 ;
		}
	}
	else
	{
		CenX = ( float )Image->WidthF * 0.5F ;
		CenY = ( float )Image->HeightF * 0.5F ;
//		xf -= 0.5F ;
//		yf -= 0.5F ;
		AngleCheck = 0 ;
		AlwaysCheck = 0 ;
		FastCode = 1 ;
	}

	// �����ȉ�]�l�̃`�F�b�N���s�����ǂ����𒲂ׂ�
	if( IntFlag == TRUE && AlwaysCheck == 0 && SinCosNone == 0 && ( hx == 1 || hy == 1 ) &&
		( ( Angle < DX_PI / 180.0 *         - 4.0   ) ||
		  ( Angle > DX_PI / 180.0 * ( 360.0 + 4.0 ) ) ||
		  ( Angle > DX_PI / 180.0 *         - 4.0   && Angle < DX_PI / 180.0 *           4.0   ) ||
		  ( Angle > DX_PI / 180.0 * (  90.0 - 4.0 ) && Angle < DX_PI / 180.0 * (  90.0 + 4.0 ) ) ||
		  ( Angle > DX_PI / 180.0 * ( 180.0 - 4.0 ) && Angle < DX_PI / 180.0 * ( 180.0 + 4.0 ) ) ||
		  ( Angle > DX_PI / 180.0 * ( 270.0 - 4.0 ) && Angle < DX_PI / 180.0 * ( 270.0 + 4.0 ) ) ||
		  ( Angle > DX_PI / 180.0 * ( 360.0 - 4.0 ) && Angle < DX_PI / 180.0 * ( 360.0 + 4.0 ) ) ) )
	{
		AngleCheck = 1 ;
	}
	else
	{
		AngleCheck = 0 ;
	}

	// ���_�f�[�^���擾�i���̂Ƃ���F���̃Z�b�g�̂݁j
	DiffuseColor = GANDR.Device.DrawInfo.DiffuseColor ;

	// �`����̐����Z�b�g
	DrawTexNum = Image->Hard.DrawNum ;

	// �`����̐����u�����h�摜�ƈقȂ��Ă�����O�Ԗڂ̃e�N�X�`���������g�p����
	BlendGraphNoIncFlag = FALSE ;
	if( BlendImage != NULL && BlendImage->Hard.DrawNum != Image->Hard.DrawNum )
	{
		BlendGraphNoIncFlag = TRUE ;
	}

	// �`����z��̃A�h���X���Z�b�g���Ă���
	DrawTex = Image->Hard.Draw ;
	if( BlendImage != NULL )
	{
		BlendDrawTex = BlendImage->Hard.Draw ;
	}

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// ���]���l�������g�嗦���Z�b�g
	ExtendRateX = ( ( ReverseXFlag == TRUE ) ? -1.0f : 1.0f ) * ExtendRate ;
	ExtendRateY = ( ( ReverseYFlag == TRUE ) ? -1.0f : 1.0f ) * ExtendRate ;

	// ���_�^�C�v�ɂ���ď����𕪊�
	switch( GANDR.Device.DrawInfo.VertexType )
	{
	case VERTEXTYPE_BLENDTEX :	// �u�����h�e�N�X�`�����g�p����
		// �e�N�X�`���[�̐������J��Ԃ�
		if( DrawTexNum == 1 && FastCode == 1 )
		{
			// �`�悷��e�N�X�`���[�̃Z�b�g
			Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
			Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

			if( GANDR.Device.DrawSetting.ChangeTextureFlag )
			{
				Graphics_Android_DeviceState_NormalDrawSetup() ;
			}

			// ���_�f�[�^������������
			GETVERTEX_QUAD( DrawVertB )

			TexVert = DrawTex->Vertex ;
			BlendTexVert = BlendDrawTex->Vertex ;

			DrawVertB[0].color = ( DWORD )DiffuseColor ;
			DrawVertB[1].color = ( DWORD )DiffuseColor ;
			DrawVertB[2].color = ( DWORD )DiffuseColor ;
			DrawVertB[3].color = ( DWORD )DiffuseColor ;
			DrawVertB[4].color = ( DWORD )DiffuseColor ;
			DrawVertB[5].color = ( DWORD )DiffuseColor ;

			XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX ;
			YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY ;
			XBuf[1] = XBuf[0] * Cos - YBuf[0] * Sin ;
			YBuf[1] = XBuf[0] * Sin + YBuf[0] * Cos ;

			XBuf[2] = ( TexVert[1].x - CenX ) * ExtendRateX ;
			YBuf[2] = ( TexVert[1].y - CenY ) * ExtendRateY ;
			XBuf[3] = XBuf[2] * Cos - YBuf[2] * Sin ;
			YBuf[3] = XBuf[2] * Sin + YBuf[2] * Cos ;

			DrawVertB[0].pos.x =  XBuf[1] + xf ;
			DrawVertB[0].pos.y =  YBuf[1] + yf ;
			DrawVertB[1].pos.x =  XBuf[3] + xf ;
			DrawVertB[1].pos.y =  YBuf[3] + yf ;
			DrawVertB[2].pos.x = -XBuf[3] + xf ;
			DrawVertB[2].pos.y = -YBuf[3] + yf ;
			DrawVertB[3].pos.x = -XBuf[1] + xf ;
			DrawVertB[3].pos.y = -YBuf[1] + yf ;
			DrawVertB[4].pos.x = -XBuf[3] + xf ;
			DrawVertB[4].pos.y = -YBuf[3] + yf ;
			DrawVertB[5].pos.x =  XBuf[3] + xf ;
			DrawVertB[5].pos.y =  YBuf[3] + yf ;

			switch( GSYS.DrawSetting.BlendGraphPosMode )
			{
			default :
			case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
				u[ 0 ] = TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				u[ 1 ] = TexVert[1].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 0 ] = TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				v[ 1 ] = TexVert[2].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[0].u1 = u[ 0 ] ;
				DrawVertB[0].v1 = v[ 0 ] ;
				DrawVertB[1].u1 = u[ 1 ] ;
				DrawVertB[1].v1 = v[ 0 ] ;
				DrawVertB[2].u1 = u[ 0 ] ;
				DrawVertB[2].v1 = v[ 1 ] ;
				DrawVertB[3].u1 = u[ 1 ] ;
				DrawVertB[3].v1 = v[ 1 ] ;
				DrawVertB[4].u1 = u[ 0 ] ;
				DrawVertB[4].v1 = v[ 1 ] ;
				DrawVertB[5].u1 = u[ 1 ] ;
				DrawVertB[5].v1 = v[ 0 ] ;
				break ;

			case DX_BLENDGRAPH_POSMODE_SCREEN :
				DrawVertB[0].u1 = ( (  XBuf[1] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[0].v1 = ( (  YBuf[1] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[1].u1 = ( (  XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[1].v1 = ( (  YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[2].u1 = ( ( -XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[2].v1 = ( ( -YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[3].u1 = ( ( -XBuf[1] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[3].v1 = ( ( -YBuf[1] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[4].u1 = ( ( -XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[4].v1 = ( ( -YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[5].u1 = ( (  XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[5].v1 = ( (  YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				break ;
			}

			DrawVertB[0].u2 = TexVert[0].u ;
			DrawVertB[0].v2 = TexVert[0].v ;
			DrawVertB[1].u2 = TexVert[1].u ;
			DrawVertB[1].v2 = TexVert[0].v ;
			DrawVertB[2].u2 = TexVert[0].u ;
			DrawVertB[2].v2 = TexVert[2].v ;
			DrawVertB[3].u2 = TexVert[1].u ;
			DrawVertB[3].v2 = TexVert[2].v ;
			DrawVertB[4].u2 = TexVert[0].u ;
			DrawVertB[4].v2 = TexVert[2].v ;
			DrawVertB[5].u2 = TexVert[1].u ;
			DrawVertB[5].v2 = TexVert[0].v ;

			*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[2].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[3].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[4].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[5].pos.z) = drawz ;

			DrawVertB[0].rhw = 1.0f ;
			DrawVertB[1].rhw = 1.0f ;
			DrawVertB[2].rhw = 1.0f ;
			DrawVertB[3].rhw = 1.0f ;
			DrawVertB[4].rhw = 1.0f ;
			DrawVertB[5].rhw = 1.0f ;

			// �e�N�X�`���[��`�悷��
			ADD4VERTEX_BLENDTEX

			if( BlendGraphNoIncFlag == FALSE )
			{
				BlendDrawTex ++ ;
			}
		}
		else
		{
			// �e�N�X�`���[�̐������J��Ԃ�
			for( i = 0 ; i < DrawTexNum ; i ++, DrawTex ++ )
			{
				// �`�悷��e�N�X�`���[�̃Z�b�g
				Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
				Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

				if( GANDR.Device.DrawSetting.ChangeTextureFlag )
				{
					Graphics_Android_DeviceState_NormalDrawSetup() ;
				}

				// ���_�f�[�^������������
				GETVERTEX_QUAD( DrawVertB )

				TexVert = DrawTex->Vertex ;
				BlendTexVert = BlendDrawTex->Vertex ;

				DrawVertB[0].color = ( DWORD )DiffuseColor ;
				DrawVertB[1].color = ( DWORD )DiffuseColor ;
				DrawVertB[2].color = ( DWORD )DiffuseColor ;
				DrawVertB[3].color = ( DWORD )DiffuseColor ;
				DrawVertB[4].color = ( DWORD )DiffuseColor ;
				DrawVertB[5].color = ( DWORD )DiffuseColor ;

				XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX ;
				YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY ;
				XBuf[1] = XBuf[0] * Cos - YBuf[0] * Sin ;
				YBuf[1] = XBuf[0] * Sin + YBuf[0] * Cos ;

				XBuf[2] = ( TexVert[1].x - CenX ) * ExtendRateX ;
				YBuf[2] = ( TexVert[1].y - CenY ) * ExtendRateY ;
				XBuf[3] = XBuf[2] * Cos - YBuf[2] * Sin ;
				YBuf[3] = XBuf[2] * Sin + YBuf[2] * Cos ;

				XBuf[4] = ( TexVert[2].x - CenX ) * ExtendRateX ;
				YBuf[4] = ( TexVert[2].y - CenY ) * ExtendRateY ;
				XBuf[5] = XBuf[4] * Cos - YBuf[4] * Sin ;
				YBuf[5] = XBuf[4] * Sin + YBuf[4] * Cos ;

				XBuf[6] = ( TexVert[3].x - CenX ) * ExtendRateX ;
				YBuf[6] = ( TexVert[3].y - CenY ) * ExtendRateY ;
				XBuf[7] = XBuf[6] * Cos - YBuf[6] * Sin ;
				YBuf[7] = XBuf[6] * Sin + YBuf[6] * Cos ;

				DrawVertB[0].pos.x = XBuf[1] + xf ;
				DrawVertB[0].pos.y = YBuf[1] + yf ;
				DrawVertB[1].pos.x = XBuf[3] + xf ;
				DrawVertB[1].pos.y = YBuf[3] + yf ;
				DrawVertB[2].pos.x = XBuf[5] + xf ;
				DrawVertB[2].pos.y = YBuf[5] + yf ;
				DrawVertB[3].pos.x = XBuf[7] + xf ;
				DrawVertB[3].pos.y = YBuf[7] + yf ;
				DrawVertB[4].pos.x = XBuf[5] + xf ;
				DrawVertB[4].pos.y = YBuf[5] + yf ;
				DrawVertB[5].pos.x = XBuf[3] + xf ;
				DrawVertB[5].pos.y = YBuf[3] + yf ;

				switch( GSYS.DrawSetting.BlendGraphPosMode )
				{
				default :
				case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
					u[ 0 ] = ( TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u[ 1 ] = ( TexVert[1].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u[ 2 ] = ( TexVert[2].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u[ 3 ] = ( TexVert[3].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					
					v[ 0 ] = ( TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v[ 1 ] = ( TexVert[1].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v[ 2 ] = ( TexVert[2].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v[ 3 ] = ( TexVert[3].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;

					DrawVertB[0].u1 = u[ 0 ] ;
					DrawVertB[0].v1 = v[ 0 ] ;
					DrawVertB[1].u1 = u[ 1 ] ;
					DrawVertB[1].v1 = v[ 1 ] ;
					DrawVertB[2].u1 = u[ 2 ] ;
					DrawVertB[2].v1 = v[ 2 ] ;
					DrawVertB[3].u1 = u[ 3 ] ;
					DrawVertB[3].v1 = v[ 3 ] ;
					DrawVertB[4].u1 = u[ 2 ] ;
					DrawVertB[4].v1 = v[ 2 ] ;
					DrawVertB[5].u1 = u[ 1 ] ;
					DrawVertB[5].v1 = v[ 1 ] ;
					break ;

				case DX_BLENDGRAPH_POSMODE_SCREEN :
					DrawVertB[0].u1 = ( ( XBuf[1] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[0].v1 = ( ( YBuf[1] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[1].u1 = ( ( XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[1].v1 = ( ( YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[2].u1 = ( ( XBuf[5] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[2].v1 = ( ( YBuf[5] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[3].u1 = ( ( XBuf[7] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[3].v1 = ( ( YBuf[7] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[4].u1 = ( ( XBuf[5] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[4].v1 = ( ( YBuf[5] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[5].u1 = ( ( XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[5].v1 = ( ( YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					break ;
				}

				DrawVertB[0].u2 = TexVert[0].u ;
				DrawVertB[0].v2 = TexVert[0].v ;
				DrawVertB[1].u2 = TexVert[1].u ;
				DrawVertB[1].v2 = TexVert[0].v ;
				DrawVertB[2].u2 = TexVert[0].u ;
				DrawVertB[2].v2 = TexVert[2].v ;
				DrawVertB[3].u2 = TexVert[1].u ;
				DrawVertB[3].v2 = TexVert[2].v ;
				DrawVertB[4].u2 = TexVert[0].u ;
				DrawVertB[4].v2 = TexVert[2].v ;
				DrawVertB[5].u2 = TexVert[1].u ;
				DrawVertB[5].v2 = TexVert[0].v ;

				*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[2].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[3].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[4].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[5].pos.z) = drawz ;

				DrawVertB[0].rhw = 1.0f ;
				DrawVertB[1].rhw = 1.0f ;
				DrawVertB[2].rhw = 1.0f ;
				DrawVertB[3].rhw = 1.0f ;
				DrawVertB[4].rhw = 1.0f ;
				DrawVertB[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_BLENDTEX

				if( BlendGraphNoIncFlag == FALSE )
				{
					BlendDrawTex ++ ;
				}
			}
		}
		break ;

	case VERTEXTYPE_TEX :	// �u�����h�e�N�X�`�����g�p���Ȃ�
		// �e�N�X�`���[�̐������J��Ԃ�
		if( DrawTexNum == 1 && FastCode == 1 )
		{
			if( SinCosNone == 0 )
			{
				// ���_�f�[�^������������
				GETVERTEX_QUAD( DrawVert )
				
				TexVert = DrawTex->Vertex ;

				DrawVert[0].color = ( DWORD )DiffuseColor ;
				DrawVert[1].color = ( DWORD )DiffuseColor ;
				DrawVert[2].color = ( DWORD )DiffuseColor ;
				DrawVert[3].color = ( DWORD )DiffuseColor ;
				DrawVert[4].color = ( DWORD )DiffuseColor ;
				DrawVert[5].color = ( DWORD )DiffuseColor ;

				DrawVert[0].u = TexVert[0].u ;
				DrawVert[0].v = TexVert[0].v ;
				DrawVert[1].u = TexVert[1].u ;
				DrawVert[1].v = TexVert[0].v ;
				DrawVert[2].v = TexVert[2].v ;
				DrawVert[2].u = TexVert[0].u ;
				DrawVert[3].u = TexVert[1].u ;
				DrawVert[3].v = TexVert[2].v ;
				DrawVert[4].u = TexVert[0].u ;
				DrawVert[4].v = TexVert[2].v ;
				DrawVert[5].u = TexVert[1].u ;
				DrawVert[5].v = TexVert[0].v ;

				XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX ;
				YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY ;
				XBuf[1] = XBuf[0] * Cos - YBuf[0] * Sin ;
				YBuf[1] = XBuf[0] * Sin + YBuf[0] * Cos ;
				
				XBuf[2] = ( TexVert[1].x - CenX ) * ExtendRateX ;
				YBuf[2] = ( TexVert[1].y - CenY ) * ExtendRateY ;
				XBuf[3] = XBuf[2] * Cos - YBuf[2] * Sin ;
				YBuf[3] = XBuf[2] * Sin + YBuf[2] * Cos ;

				if( AlwaysCheck )
				{
					DrawPos[0].x =  XBuf[1] + xf ;
					DrawPos[0].y =  YBuf[1] + yf ;
					DrawPos[1].x =  XBuf[3] + xf ;
					DrawPos[1].y =  YBuf[3] + yf ;
					DrawPos[2].x = -XBuf[3] + xf ;
					DrawPos[2].y = -YBuf[3] + yf ;
					DrawPos[3].x = -XBuf[1] + xf ;
					DrawPos[3].y = -YBuf[1] + yf ;

					if( ( ( ( *((DWORD *)&DrawPos[0].x) == *((DWORD *)&DrawPos[2].x) ) ||
							( ( DrawPos[0].x > DrawPos[2].x ) && ( DrawPos[0].x < DrawPos[2].x + 0.01f ) ) ||
							( ( DrawPos[2].x > DrawPos[0].x ) && ( DrawPos[2].x < DrawPos[0].x + 0.01f ) ) ) &&
							_FABS( DrawPos[0].x - _FTOL( DrawPos[0].x ) ) < 0.0001f ) ||
						( ( ( *((DWORD *)&DrawPos[0].x) == *((DWORD *)&DrawPos[1].x) ) ||
							( ( DrawPos[0].x > DrawPos[1].x ) && ( DrawPos[0].x < DrawPos[1].x + 0.01f ) ) ||
							( ( DrawPos[1].x > DrawPos[0].x ) && ( DrawPos[1].x < DrawPos[0].x + 0.01f ) ) ) &&
							_FABS( DrawPos[0].x - _FTOL( DrawPos[0].x ) ) < 0.0001f ) )
					{
						DrawPos[0].x -= 0.5f;
						DrawPos[1].x -= 0.5f;
						DrawPos[2].x -= 0.5f;
						DrawPos[3].x -= 0.5f;
					}

					if( ( ( ( *((DWORD *)&DrawPos[0].y) == *((DWORD *)&DrawPos[2].y) ) ||
							( ( DrawPos[0].y > DrawPos[2].y ) && ( DrawPos[0].y < DrawPos[2].y + 0.01f ) ) ||
							( ( DrawPos[2].y > DrawPos[0].y ) && ( DrawPos[2].y < DrawPos[0].y + 0.01f ) ) ) &&
							_FABS( DrawPos[0].y - _FTOL( DrawPos[0].y ) ) < 0.0001f ) ||
						( ( ( *((DWORD *)&DrawPos[0].y) == *((DWORD *)&DrawPos[1].y) ) ||
							( ( DrawPos[0].y > DrawPos[1].y ) && ( DrawPos[0].y < DrawPos[1].y + 0.01f ) ) ||
							( ( DrawPos[1].y > DrawPos[0].y ) && ( DrawPos[1].y < DrawPos[0].y + 0.01f ) ) ) &&
							_FABS( DrawPos[0].y - _FTOL( DrawPos[0].y ) ) < 0.0001f ) )
					{
						DrawPos[0].y -= 0.5f;
						DrawPos[1].y -= 0.5f;
						DrawPos[2].y -= 0.5f;
						DrawPos[3].y -= 0.5f;
					}

					DrawVert[0].pos.x = DrawPos[0].x ;
					DrawVert[0].pos.y = DrawPos[0].y ;
					DrawVert[1].pos.x = DrawPos[1].x ;
					DrawVert[1].pos.y = DrawPos[1].y ;
					DrawVert[2].pos.x = DrawPos[2].x ;
					DrawVert[2].pos.y = DrawPos[2].y ;
					DrawVert[3].pos.x = DrawPos[3].x ;
					DrawVert[3].pos.y = DrawPos[3].y ;
					DrawVert[4].pos.x = DrawPos[2].x ;
					DrawVert[4].pos.y = DrawPos[2].y ;
					DrawVert[5].pos.x = DrawPos[1].x ;
					DrawVert[5].pos.y = DrawPos[1].y ;
				}
				else
				if( AngleCheck )
				{
					DrawPos[0].x =  XBuf[1] + xf ;
					DrawPos[0].y =  YBuf[1] + yf ;
					DrawPos[3].x = -XBuf[1] + xf ;
					DrawPos[3].y = -YBuf[1] + yf ;

					DrawPos[1].x =  XBuf[3] + xf ;
					DrawPos[1].y =  YBuf[3] + yf ;
					DrawPos[2].x = -XBuf[3] + xf ;
					DrawPos[2].y = -YBuf[3] + yf ;

					if( hx &&
						( ( *((DWORD *)&DrawPos[0].x) == *((DWORD *)&DrawPos[2].x) ) ||
						  ( ( DrawPos[0].x > DrawPos[2].x - 0.01f ) && ( DrawPos[0].x < DrawPos[2].x + 0.01f ) ) ||
						  ( ( DrawPos[2].x > DrawPos[0].x - 0.01f ) && ( DrawPos[2].x < DrawPos[0].x + 0.01f ) ) ||
						  ( *((DWORD *)&DrawPos[0].x) == *((DWORD *)&DrawPos[1].x) ) ||
						  ( ( DrawPos[0].x > DrawPos[1].x - 0.01f ) && ( DrawPos[0].x < DrawPos[1].x + 0.01f ) ) ||
						  ( ( DrawPos[1].x > DrawPos[0].x - 0.01f ) && ( DrawPos[1].x < DrawPos[0].x + 0.01f ) ) ) )
					{
						DrawPos[0].x -= 0.5f;
						DrawPos[1].x -= 0.5f;
						DrawPos[2].x -= 0.5f;
						DrawPos[3].x -= 0.5f;
					}

					if( hy &&
						( ( *((DWORD *)&DrawPos[0].y) == *((DWORD *)&DrawPos[1].y) ) ||
						  ( ( DrawPos[0].y > DrawPos[1].y - 0.01f ) && ( DrawPos[0].y < DrawPos[1].y + 0.01f ) ) ||
						  ( ( DrawPos[1].y > DrawPos[0].y - 0.01f ) && ( DrawPos[1].y < DrawPos[0].y + 0.01f ) ) ||
						  ( *((DWORD *)&DrawPos[0].y) == *((DWORD *)&DrawPos[2].y) ) ||
						  ( ( DrawPos[0].y > DrawPos[2].y - 0.01f ) && ( DrawPos[0].y < DrawPos[2].y + 0.01f ) ) ||
						  ( ( DrawPos[2].y > DrawPos[0].y - 0.01f ) && ( DrawPos[2].y < DrawPos[0].y + 0.01f ) ) ) )
					{
						DrawPos[0].y -= 0.5f;
						DrawPos[1].y -= 0.5f;
						DrawPos[2].y -= 0.5f;
						DrawPos[3].y -= 0.5f;
					}

					DrawVert[0].pos.x = DrawPos[0].x ;
					DrawVert[0].pos.y = DrawPos[0].y ;
					DrawVert[1].pos.x = DrawPos[1].x ;
					DrawVert[1].pos.y = DrawPos[1].y ;
					DrawVert[2].pos.x = DrawPos[2].x ;
					DrawVert[2].pos.y = DrawPos[2].y ;
					DrawVert[3].pos.x = DrawPos[3].x ;
					DrawVert[3].pos.y = DrawPos[3].y ;
					DrawVert[4].pos.x = DrawPos[2].x ;
					DrawVert[4].pos.y = DrawPos[2].y ;
					DrawVert[5].pos.x = DrawPos[1].x ;
					DrawVert[5].pos.y = DrawPos[1].y ;
				}
				else
				{
					DrawVert[0].pos.x =  XBuf[1] + xf ;
					DrawVert[0].pos.y =  YBuf[1] + yf ;
					DrawVert[1].pos.x =  XBuf[3] + xf ;
					DrawVert[1].pos.y =  YBuf[3] + yf ;
					DrawVert[2].pos.x = -XBuf[3] + xf ;
					DrawVert[2].pos.y = -YBuf[3] + yf ;
					DrawVert[3].pos.x = -XBuf[1] + xf ;
					DrawVert[3].pos.y = -YBuf[1] + yf ;
					DrawVert[4].pos.x = -XBuf[3] + xf ;
					DrawVert[4].pos.y = -YBuf[3] + yf ;
					DrawVert[5].pos.x =  XBuf[3] + xf ;
					DrawVert[5].pos.y =  YBuf[3] + yf ;
				}

				*((DWORD *)&DrawVert[0].pos.z) = drawz ;
				*((DWORD *)&DrawVert[1].pos.z) = drawz ;
				*((DWORD *)&DrawVert[2].pos.z) = drawz ;
				*((DWORD *)&DrawVert[3].pos.z) = drawz ;
				*((DWORD *)&DrawVert[4].pos.z) = drawz ;
				*((DWORD *)&DrawVert[5].pos.z) = drawz ;

				DrawVert[0].rhw = 1.0f ;
				DrawVert[1].rhw = 1.0f ;
				DrawVert[2].rhw = 1.0f ;
				DrawVert[3].rhw = 1.0f ;
				DrawVert[4].rhw = 1.0f ;
				DrawVert[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_TEX
			}
			else
			{
				// ���_�f�[�^������������
				GETVERTEX_QUAD( DrawVert )
				
				TexVert = DrawTex->Vertex ;

				DrawVert[0].color = ( DWORD )DiffuseColor ;
				DrawVert[1].color = ( DWORD )DiffuseColor ;
				DrawVert[2].color = ( DWORD )DiffuseColor ;
				DrawVert[3].color = ( DWORD )DiffuseColor ;
				DrawVert[4].color = ( DWORD )DiffuseColor ;
				DrawVert[5].color = ( DWORD )DiffuseColor ;

				DrawVert[0].u = TexVert[0].u ;
				DrawVert[0].v = TexVert[0].v ;
				DrawVert[1].u = TexVert[1].u ;
				DrawVert[1].v = TexVert[0].v ;
				DrawVert[2].u = TexVert[0].u ;
				DrawVert[2].v = TexVert[2].v ;
				DrawVert[3].u = TexVert[1].u ;
				DrawVert[3].v = TexVert[2].v ;
				DrawVert[4].u = TexVert[0].u ;
				DrawVert[4].v = TexVert[2].v ;
				DrawVert[5].u = TexVert[1].u ;
				DrawVert[5].v = TexVert[0].v ;

				XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX ;
				YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY ;

				XBuf[1] = ( TexVert[1].x - CenX ) * ExtendRateX ;
				YBuf[1] = ( TexVert[1].y - CenY ) * ExtendRateY ;

				DrawVert[0].pos.x =  XBuf[0] + xf ;
				DrawVert[0].pos.y =  YBuf[0] + yf ;
				DrawVert[1].pos.x =  XBuf[1] + xf ;
				DrawVert[1].pos.y =  YBuf[1] + yf ;
				DrawVert[2].pos.x = -XBuf[1] + xf ;
				DrawVert[2].pos.y = -YBuf[1] + yf ;
				DrawVert[3].pos.x = -XBuf[0] + xf ;
				DrawVert[3].pos.y = -YBuf[0] + yf ;
				DrawVert[4].pos.x = -XBuf[1] + xf ;
				DrawVert[4].pos.y = -YBuf[1] + yf ;
				DrawVert[5].pos.x =  XBuf[1] + xf ;
				DrawVert[5].pos.y =  YBuf[1] + yf ;

				*((DWORD *)&DrawVert[0].pos.z) = drawz ;
				*((DWORD *)&DrawVert[1].pos.z) = drawz ;
				*((DWORD *)&DrawVert[2].pos.z) = drawz ;
				*((DWORD *)&DrawVert[3].pos.z) = drawz ;
				*((DWORD *)&DrawVert[4].pos.z) = drawz ;
				*((DWORD *)&DrawVert[5].pos.z) = drawz ;

				DrawVert[0].rhw = 1.0f ;
				DrawVert[1].rhw = 1.0f ;
				DrawVert[2].rhw = 1.0f ;
				DrawVert[3].rhw = 1.0f ;
				DrawVert[4].rhw = 1.0f ;
				DrawVert[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_TEX
			}
		}
		else
		{
			if( SinCosNone == 0 )
			{
				// �e�N�X�`���[�̐������J��Ԃ�
				i = 0 ;
				for(;;)
				{
					// ���_�f�[�^������������
					GETVERTEX_QUAD( DrawVert )
					
					TexVert = DrawTex->Vertex ;

					DrawVert[0].color = ( DWORD )DiffuseColor ;
					DrawVert[1].color = ( DWORD )DiffuseColor ;
					DrawVert[2].color = ( DWORD )DiffuseColor ;
					DrawVert[3].color = ( DWORD )DiffuseColor ;
					DrawVert[4].color = ( DWORD )DiffuseColor ;
					DrawVert[5].color = ( DWORD )DiffuseColor ;

					DrawVert[0].u = TexVert[0].u ;
					DrawVert[0].v = TexVert[0].v ;
					DrawVert[1].u = TexVert[1].u ;
					DrawVert[1].v = TexVert[0].v ;
					DrawVert[2].u = TexVert[0].u ;
					DrawVert[2].v = TexVert[2].v ;
					DrawVert[3].u = TexVert[1].u ;
					DrawVert[3].v = TexVert[2].v ;
					DrawVert[4].u = TexVert[0].u ;
					DrawVert[4].v = TexVert[2].v ;
					DrawVert[5].u = TexVert[1].u ;
					DrawVert[5].v = TexVert[0].v ;

					XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX ;
					YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY ;
					XBuf[1] = XBuf[0] * Cos - YBuf[0] * Sin ;
					YBuf[1] = XBuf[0] * Sin + YBuf[0] * Cos ;

					XBuf[2] = ( TexVert[1].x - CenX ) * ExtendRateX ;
					YBuf[2] = ( TexVert[1].y - CenY ) * ExtendRateY ;
					XBuf[3] = XBuf[2] * Cos - YBuf[2] * Sin ;
					YBuf[3] = XBuf[2] * Sin + YBuf[2] * Cos ;

					XBuf[4] = ( TexVert[2].x - CenX ) * ExtendRateX ;
					YBuf[4] = ( TexVert[2].y - CenY ) * ExtendRateY ;
					XBuf[5] = XBuf[4] * Cos - YBuf[4] * Sin ;
					YBuf[5] = XBuf[4] * Sin + YBuf[4] * Cos ;

					XBuf[6] = ( TexVert[3].x - CenX ) * ExtendRateX ;
					YBuf[6] = ( TexVert[3].y - CenY ) * ExtendRateY ;
					XBuf[7] = XBuf[6] * Cos - YBuf[6] * Sin ;
					YBuf[7] = XBuf[6] * Sin + YBuf[6] * Cos ;

					if( AlwaysCheck )
					{
						float f;

						DrawPos[0].x = XBuf[1] + xf ;
						DrawPos[0].y = YBuf[1] + yf ;
						DrawPos[1].x = XBuf[3] + xf ;
						DrawPos[1].y = YBuf[3] + yf ;
						DrawPos[2].x = XBuf[5] + xf ;
						DrawPos[2].y = YBuf[5] + yf ;
						DrawPos[3].x = XBuf[7] + xf ;
						DrawPos[3].y = YBuf[7] + yf ;

						f = _FABS( DrawPos[0].x - _FTOL( DrawPos[0].x ) );
						if( ( ( ( *((DWORD *)&DrawPos[0].x) == *((DWORD *)&DrawPos[2].x) ) ||
							    ( ( DrawPos[0].x >= DrawPos[2].x - 0.01f ) && ( DrawPos[0].x < DrawPos[2].x + 0.01f ) ) ||
							    ( ( DrawPos[2].x >= DrawPos[0].x - 0.01f ) && ( DrawPos[2].x < DrawPos[0].x + 0.01f ) ) ) &&
							    ( f < 0.001f || f > 0.999f ) ) ||
							( ( ( *((DWORD *)&DrawPos[0].x) == *((DWORD *)&DrawPos[1].x) ) ||
							    ( ( DrawPos[0].x >= DrawPos[1].x - 0.01f ) && ( DrawPos[0].x < DrawPos[1].x + 0.01f ) ) ||
							    ( ( DrawPos[1].x >= DrawPos[0].x - 0.01f ) && ( DrawPos[1].x < DrawPos[0].x + 0.01f ) ) ) &&
							    ( f < 0.001f || f > 0.999f ) ) )
						{
							DrawPos[0].x -= 0.5f;
							DrawPos[1].x -= 0.5f;
							DrawPos[2].x -= 0.5f;
							DrawPos[3].x -= 0.5f;
						}

						f = _FABS( DrawPos[0].y - _FTOL( DrawPos[0].y ) );
						if( ( ( ( *((DWORD *)&DrawPos[0].y) == *((DWORD *)&DrawPos[2].y) ) ||
							    ( ( DrawPos[0].y >= DrawPos[2].y - 0.01f ) && ( DrawPos[0].y < DrawPos[2].y + 0.01f ) ) ||
							    ( ( DrawPos[2].y >= DrawPos[0].y - 0.01f ) && ( DrawPos[2].y < DrawPos[0].y + 0.01f ) ) ) &&
							    ( f < 0.001f || f > 0.999f ) ) ||
							( ( ( *((DWORD *)&DrawPos[0].y) == *((DWORD *)&DrawPos[1].y) ) ||
							    ( ( DrawPos[0].y >= DrawPos[1].y - 0.01f ) && ( DrawPos[0].y < DrawPos[1].y + 0.01f ) ) ||
							    ( ( DrawPos[1].y >= DrawPos[0].y - 0.01f ) && ( DrawPos[1].y < DrawPos[0].y + 0.01f ) ) ) &&
							    ( f < 0.001f || f > 0.999f ) ) )
						{
							DrawPos[0].y -= 0.5f;
							DrawPos[1].y -= 0.5f;
							DrawPos[2].y -= 0.5f;
							DrawPos[3].y -= 0.5f;
						}

						DrawVert[0].pos.x = DrawPos[0].x ;
						DrawVert[0].pos.y = DrawPos[0].y ;
						DrawVert[1].pos.x = DrawPos[1].x ;
						DrawVert[1].pos.y = DrawPos[1].y ;
						DrawVert[2].pos.x = DrawPos[2].x ;
						DrawVert[2].pos.y = DrawPos[2].y ;
						DrawVert[3].pos.x = DrawPos[3].x ;
						DrawVert[3].pos.y = DrawPos[3].y ;
						DrawVert[4].pos.x = DrawPos[2].x ;
						DrawVert[4].pos.y = DrawPos[2].y ;
						DrawVert[5].pos.x = DrawPos[1].x ;
						DrawVert[5].pos.y = DrawPos[1].y ;
					}
					else
					if( AngleCheck )
					{
						float f;

						DrawPos[0].x = XBuf[1] + xf ;
						DrawPos[0].y = YBuf[1] + yf ;
						DrawPos[1].x = XBuf[3] + xf ;
						DrawPos[1].y = YBuf[3] + yf ;
						DrawPos[2].x = XBuf[5] + xf ;
						DrawPos[2].y = YBuf[5] + yf ;
						DrawPos[3].x = XBuf[7] + xf ;
						DrawPos[3].y = YBuf[7] + yf ;

						if( hx )
						{
							f = _FABS( DrawPos[0].x - _FTOL( DrawPos[0].x ) );
							if( ( ( ( *((DWORD *)&DrawPos[0].x) == *((DWORD *)&DrawPos[2].x) ) ||
									( ( DrawPos[0].x >= DrawPos[2].x - 0.01f ) && ( DrawPos[0].x < DrawPos[2].x + 0.01f ) ) ||
									( ( DrawPos[2].x >= DrawPos[0].x - 0.01f ) && ( DrawPos[2].x < DrawPos[0].x + 0.01f ) ) ) &&
									( f < 0.001f || f > 0.999f ) ) ||
								( ( ( *((DWORD *)&DrawPos[0].x) == *((DWORD *)&DrawPos[1].x) ) ||
									( ( DrawPos[0].x >= DrawPos[1].x - 0.01f ) && ( DrawPos[0].x < DrawPos[1].x + 0.01f ) ) ||
									( ( DrawPos[1].x >= DrawPos[0].x - 0.01f ) && ( DrawPos[1].x < DrawPos[0].x + 0.01f ) ) ) &&
									( f < 0.001f || f > 0.999f ) ) )
							{
								DrawPos[0].x -= 0.5f;
								DrawPos[1].x -= 0.5f;
								DrawPos[2].x -= 0.5f;
								DrawPos[3].x -= 0.5f;
							}
						}

						if( hy )
						{
							f = _FABS( DrawPos[0].y - _FTOL( DrawPos[0].y ) );
							if( ( ( ( *((DWORD *)&DrawPos[0].y) == *((DWORD *)&DrawPos[2].y) ) ||
									( ( DrawPos[0].y >= DrawPos[2].y - 0.01f ) && ( DrawPos[0].y < DrawPos[2].y + 0.01f ) ) ||
									( ( DrawPos[2].y >= DrawPos[0].y - 0.01f ) && ( DrawPos[2].y < DrawPos[0].y + 0.01f ) ) ) &&
									( f < 0.001f || f > 0.999f ) ) ||
								( ( ( *((DWORD *)&DrawPos[0].y) == *((DWORD *)&DrawPos[1].y) ) ||
									( ( DrawPos[0].y >= DrawPos[1].y - 0.01f ) && ( DrawPos[0].y < DrawPos[1].y + 0.01f ) ) ||
									( ( DrawPos[1].y >= DrawPos[0].y - 0.01f ) && ( DrawPos[1].y < DrawPos[0].y + 0.01f ) ) ) &&
									( f < 0.001f || f > 0.999f ) ) )
							{
								DrawPos[0].y -= 0.5f;
								DrawPos[1].y -= 0.5f;
								DrawPos[2].y -= 0.5f;
								DrawPos[3].y -= 0.5f;
							}
						}

						DrawVert[0].pos.x = DrawPos[0].x ;
						DrawVert[0].pos.y = DrawPos[0].y ;
						DrawVert[1].pos.x = DrawPos[1].x ;
						DrawVert[1].pos.y = DrawPos[1].y ;
						DrawVert[2].pos.x = DrawPos[2].x ;
						DrawVert[2].pos.y = DrawPos[2].y ;
						DrawVert[3].pos.x = DrawPos[3].x ;
						DrawVert[3].pos.y = DrawPos[3].y ;
						DrawVert[4].pos.x = DrawPos[2].x ;
						DrawVert[4].pos.y = DrawPos[2].y ;
						DrawVert[5].pos.x = DrawPos[1].x ;
						DrawVert[5].pos.y = DrawPos[1].y ;
					}
					else
					{
						DrawVert[0].pos.x = XBuf[1] + xf ;
						DrawVert[0].pos.y = YBuf[1] + yf ;
						DrawVert[1].pos.x = XBuf[3] + xf ;
						DrawVert[1].pos.y = YBuf[3] + yf ;
						DrawVert[2].pos.x = XBuf[5] + xf ;
						DrawVert[2].pos.y = YBuf[5] + yf ;
						DrawVert[3].pos.x = XBuf[7] + xf ;
						DrawVert[3].pos.y = YBuf[7] + yf ;
						DrawVert[4].pos.x = XBuf[5] + xf ;
						DrawVert[4].pos.y = YBuf[5] + yf ;
						DrawVert[5].pos.x = XBuf[3] + xf ;
						DrawVert[5].pos.y = YBuf[3] + yf ;
					}

					*((DWORD *)&DrawVert[0].pos.z) = drawz ;
					*((DWORD *)&DrawVert[1].pos.z) = drawz ;
					*((DWORD *)&DrawVert[2].pos.z) = drawz ;
					*((DWORD *)&DrawVert[3].pos.z) = drawz ;
					*((DWORD *)&DrawVert[4].pos.z) = drawz ;
					*((DWORD *)&DrawVert[5].pos.z) = drawz ;

					DrawVert[0].rhw = 1.0f ;
					DrawVert[1].rhw = 1.0f ;
					DrawVert[2].rhw = 1.0f ;
					DrawVert[3].rhw = 1.0f ;
					DrawVert[4].rhw = 1.0f ;
					DrawVert[5].rhw = 1.0f ;

					// �e�N�X�`���[��`�悷��
					ADD4VERTEX_TEX

					i ++ ;
					if( i >= DrawTexNum ) break ;

					// �`�悷��e�N�X�`���[�̃Z�b�g
					DrawTex ++ ;
					Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
					Graphics_Android_DeviceState_NormalDrawSetup() ;
				}
			}
			else
			{
				// �e�N�X�`���[�̐������J��Ԃ�
				i = 0 ;
				for(;;)
				{
					// ���_�f�[�^������������
					GETVERTEX_QUAD( DrawVert )
					
					TexVert = DrawTex->Vertex ;

					DrawVert[0].color = ( DWORD )DiffuseColor ;
					DrawVert[1].color = ( DWORD )DiffuseColor ;
					DrawVert[2].color = ( DWORD )DiffuseColor ;
					DrawVert[3].color = ( DWORD )DiffuseColor ;
					DrawVert[4].color = ( DWORD )DiffuseColor ;
					DrawVert[5].color = ( DWORD )DiffuseColor ;

					DrawVert[0].u = TexVert[0].u ;
					DrawVert[0].v = TexVert[0].v ;
					DrawVert[1].u = TexVert[1].u ;
					DrawVert[1].v = TexVert[0].v ;
					DrawVert[2].v = TexVert[2].v ;
					DrawVert[2].u = TexVert[0].u ;
					DrawVert[3].u = TexVert[1].u ;
					DrawVert[3].v = TexVert[2].v ;
					DrawVert[4].u = TexVert[0].u ;
					DrawVert[4].v = TexVert[2].v ;
					DrawVert[5].u = TexVert[1].u ;
					DrawVert[5].v = TexVert[0].v ;

					XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX + xf ;
					YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY + yf ;
					XBuf[1] = ( TexVert[1].x - CenX ) * ExtendRateX + xf ;
					YBuf[1] = ( TexVert[1].y - CenY ) * ExtendRateY + yf ;
					XBuf[2] = ( TexVert[2].x - CenX ) * ExtendRateX + xf ;
					YBuf[2] = ( TexVert[2].y - CenY ) * ExtendRateY + yf ;
					XBuf[3] = ( TexVert[3].x - CenX ) * ExtendRateX + xf ;
					YBuf[3] = ( TexVert[3].y - CenY ) * ExtendRateY + yf ;

					DrawVert[0].pos.x = XBuf[0] ;
					DrawVert[0].pos.y = YBuf[0] ;
					DrawVert[1].pos.x = XBuf[1] ;
					DrawVert[1].pos.y = YBuf[1] ;
					DrawVert[2].pos.x = XBuf[2] ;
					DrawVert[2].pos.y = YBuf[2] ;
					DrawVert[3].pos.x = XBuf[3] ;
					DrawVert[3].pos.y = YBuf[3] ;
					DrawVert[4].pos.x = XBuf[2] ;
					DrawVert[4].pos.y = YBuf[2] ;
					DrawVert[5].pos.x = XBuf[1] ;
					DrawVert[5].pos.y = YBuf[1] ;

					*((DWORD *)&DrawVert[0].pos.z) = drawz ;
					*((DWORD *)&DrawVert[1].pos.z) = drawz ;
					*((DWORD *)&DrawVert[2].pos.z) = drawz ;
					*((DWORD *)&DrawVert[3].pos.z) = drawz ;
					*((DWORD *)&DrawVert[4].pos.z) = drawz ;
					*((DWORD *)&DrawVert[5].pos.z) = drawz ;

					DrawVert[0].rhw = 1.0f ;
					DrawVert[1].rhw = 1.0f ;
					DrawVert[2].rhw = 1.0f ;
					DrawVert[3].rhw = 1.0f ;
					DrawVert[4].rhw = 1.0f ;
					DrawVert[5].rhw = 1.0f ;

					// �e�N�X�`���[��`�悷��
					ADD4VERTEX_TEX

					i ++ ;
					if( i >= DrawTexNum ) break ;

					// �`�悷��e�N�X�`���[�̃Z�b�g
					DrawTex ++ ;
					Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
					Graphics_Android_DeviceState_NormalDrawSetup() ;
				}
			}
		}
		break ;
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawRotaGraphFast
extern	int		Graphics_Hardware_DrawRotaGraphFast_PF( int x, int y, float xf, float yf, float ExtendRate, float Angle, IMAGEDATA *Image, IMAGEDATA *BlendImage, int TransFlag, int ReverseXFlag, int ReverseYFlag, int IntFlag )
{
	VERTEX_2D *DrawVert ;
	VERTEX_BLENDTEX_2D *DrawVertB ;
	DWORD DiffuseColor ;
	IMAGEDATA_HARD_DRAW *DrawTex ;
	IMAGEDATA_HARD_DRAW *BlendDrawTex = NULL ;
	IMAGEDATA_HARD_VERT *TexVert ;
	IMAGEDATA_HARD_VERT *BlendTexVert ;
	int DrawTexNum ;
	int i ; 
	float Sin = 0.0f, Cos = 1.0f ;
	int BlendGraphNoIncFlag ;
	float XBuf[ 8 ] ;
	float YBuf[ 8 ] ;
	float u[ 4 ] ;
	float v[ 4 ] ;
	float ExtendRateX ;
	float ExtendRateY ;
	DWORD drawz ;
//	BOOL Adj = FALSE ;
	float CenX, CenY ;
	int SinCosNone ;
	int Flag ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �����Ȃ������ꍇ�̓G���[
	if( ExtendRate == 0.0f ) return -1 ;

	// �`��̏���
	Flag = TransFlag ;
	DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )

	// ��]�v�f�����������ׂ�
	if( Angle == 0.0f )
	{
		SinCosNone = 1;
	}
	else
	{
		SinCosNone = 0;
		_TABLE_SINCOS( (float)Angle, &Sin, &Cos ) ;
	}

	// ���S���W�̎Z�o
	CenX = ( float )Image->WidthF * 0.5F ;
	CenY = ( float )Image->HeightF * 0.5F ;

	// ���_�f�[�^���擾�i���̂Ƃ���F���̃Z�b�g�̂݁j
	DiffuseColor = GANDR.Device.DrawInfo.DiffuseColor ;

	// �`����̐����Z�b�g
	DrawTexNum = Image->Hard.DrawNum ;

	// �`����̐����u�����h�摜�ƈقȂ��Ă�����O�Ԗڂ̃e�N�X�`���������g�p����
	BlendGraphNoIncFlag = FALSE ;
	if( BlendImage != NULL && BlendImage->Hard.DrawNum != Image->Hard.DrawNum )
	{
		BlendGraphNoIncFlag = TRUE ;
	}

	// �`����z��̃A�h���X���Z�b�g���Ă���
	DrawTex = Image->Hard.Draw ;
	if( BlendImage != NULL )
	{
		BlendDrawTex = BlendImage->Hard.Draw ;
	}

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// ���]���l�������g�嗦���Z�b�g
	ExtendRateX = ( ( ReverseXFlag == TRUE ) ? -1.0f : 1.0f ) * ExtendRate ;
	ExtendRateY = ( ( ReverseYFlag == TRUE ) ? -1.0f : 1.0f ) * ExtendRate ;

	// ���_�^�C�v�ɂ���ď����𕪊�
	switch( GANDR.Device.DrawInfo.VertexType )
	{
	case VERTEXTYPE_BLENDTEX :	// �u�����h�e�N�X�`�����g�p����
		// �e�N�X�`���[�̐������J��Ԃ�
		if( DrawTexNum == 1 )
		{
			// �`�悷��e�N�X�`���[�̃Z�b�g
			Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
			Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

			if( GANDR.Device.DrawSetting.ChangeTextureFlag )
			{
				Graphics_Android_DeviceState_NormalDrawSetup() ;
			}

			// ���_�f�[�^������������
			GETVERTEX_QUAD( DrawVertB )

			TexVert = DrawTex->Vertex ;
			BlendTexVert = BlendDrawTex->Vertex ;

			DrawVertB[0].color = ( DWORD )DiffuseColor ;
			DrawVertB[1].color = ( DWORD )DiffuseColor ;
			DrawVertB[2].color = ( DWORD )DiffuseColor ;
			DrawVertB[3].color = ( DWORD )DiffuseColor ;
			DrawVertB[4].color = ( DWORD )DiffuseColor ;
			DrawVertB[5].color = ( DWORD )DiffuseColor ;

			XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX ;
			YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRate ;
			XBuf[1] = XBuf[0] * Cos - YBuf[0] * Sin ;
			YBuf[1] = XBuf[0] * Sin + YBuf[0] * Cos ;

			XBuf[2] = ( TexVert[1].x - CenX ) * ExtendRateX ;
			YBuf[2] = ( TexVert[1].y - CenY ) * ExtendRateY ;
			XBuf[3] = XBuf[2] * Cos - YBuf[2] * Sin ;
			YBuf[3] = XBuf[2] * Sin + YBuf[2] * Cos ;

			DrawVertB[0].pos.x =  XBuf[1] + xf ;
			DrawVertB[0].pos.y =  YBuf[1] + yf ;
			DrawVertB[1].pos.x =  XBuf[3] + xf ;
			DrawVertB[1].pos.y =  YBuf[3] + yf ;
			DrawVertB[2].pos.x = -XBuf[3] + xf ;
			DrawVertB[2].pos.y = -YBuf[3] + yf ;
			DrawVertB[3].pos.x = -XBuf[1] + xf ;
			DrawVertB[3].pos.y = -YBuf[1] + yf ;
			DrawVertB[4].pos.x = -XBuf[3] + xf ;
			DrawVertB[4].pos.y = -YBuf[3] + yf ;
			DrawVertB[5].pos.x =  XBuf[3] + xf ;
			DrawVertB[5].pos.y =  YBuf[3] + yf ;

			switch( GSYS.DrawSetting.BlendGraphPosMode )
			{
			default :
			case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
				u[ 0 ] = TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				u[ 1 ] = TexVert[1].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 0 ] = TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				v[ 1 ] = TexVert[2].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[0].u1 = u[ 0 ] ;
				DrawVertB[0].v1 = v[ 0 ] ;
				DrawVertB[1].u1 = u[ 1 ] ;
				DrawVertB[1].v1 = v[ 0 ] ;
				DrawVertB[2].u1 = u[ 0 ] ;
				DrawVertB[2].v1 = v[ 1 ] ;
				DrawVertB[3].u1 = u[ 1 ] ;
				DrawVertB[3].v1 = v[ 1 ] ;
				DrawVertB[4].u1 = u[ 0 ] ;
				DrawVertB[4].v1 = v[ 1 ] ;
				DrawVertB[5].u1 = u[ 1 ] ;
				DrawVertB[5].v1 = v[ 0 ] ;
				break ;

			case DX_BLENDGRAPH_POSMODE_SCREEN :
				DrawVertB[0].u1 = ( (  XBuf[1] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[0].v1 = ( (  YBuf[1] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[1].u1 = ( (  XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[1].v1 = ( (  YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[2].u1 = ( ( -XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[2].v1 = ( ( -YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[3].u1 = ( ( -XBuf[1] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[3].v1 = ( ( -YBuf[1] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[4].u1 = ( ( -XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[4].v1 = ( ( -YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				DrawVertB[5].u1 = ( (  XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				DrawVertB[5].v1 = ( (  YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				break ;
			}

			DrawVertB[0].u2 = TexVert[0].u ;
			DrawVertB[0].v2 = TexVert[0].v ;
			DrawVertB[1].u2 = TexVert[1].u ;
			DrawVertB[1].v2 = TexVert[0].v ;
			DrawVertB[2].u2 = TexVert[0].u ;
			DrawVertB[2].v2 = TexVert[2].v ;
			DrawVertB[3].u2 = TexVert[1].u ;
			DrawVertB[3].v2 = TexVert[2].v ;
			DrawVertB[4].u2 = TexVert[0].u ;
			DrawVertB[4].v2 = TexVert[2].v ;
			DrawVertB[5].u2 = TexVert[1].u ;
			DrawVertB[5].v2 = TexVert[0].v ;

			*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[2].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[3].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[4].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[5].pos.z) = drawz ;

			DrawVertB[0].rhw = 1.0f ;
			DrawVertB[1].rhw = 1.0f ;
			DrawVertB[2].rhw = 1.0f ;
			DrawVertB[3].rhw = 1.0f ;
			DrawVertB[4].rhw = 1.0f ;
			DrawVertB[5].rhw = 1.0f ;

			// �e�N�X�`���[��`�悷��
			ADD4VERTEX_BLENDTEX

			if( BlendGraphNoIncFlag == FALSE )
			{
				BlendDrawTex ++ ;
			}
		}
		else
		{
			// �e�N�X�`���[�̐������J��Ԃ�
			for( i = 0 ; i < DrawTexNum ; i ++, DrawTex ++ )
			{
				// �`�悷��e�N�X�`���[�̃Z�b�g
				Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
				Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

				if( GANDR.Device.DrawSetting.ChangeTextureFlag )
				{
					Graphics_Android_DeviceState_NormalDrawSetup() ;
				}

				// ���_�f�[�^������������
				GETVERTEX_QUAD( DrawVertB )

				TexVert = DrawTex->Vertex ;
				BlendTexVert = BlendDrawTex->Vertex ;

				DrawVertB[0].color = ( DWORD )DiffuseColor ;
				DrawVertB[1].color = ( DWORD )DiffuseColor ;
				DrawVertB[2].color = ( DWORD )DiffuseColor ;
				DrawVertB[3].color = ( DWORD )DiffuseColor ;
				DrawVertB[4].color = ( DWORD )DiffuseColor ;
				DrawVertB[5].color = ( DWORD )DiffuseColor ;

				XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX ;
				YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY ;
				XBuf[1] = XBuf[0] * Cos - YBuf[0] * Sin ;
				YBuf[1] = XBuf[0] * Sin + YBuf[0] * Cos ;

				XBuf[2] = ( TexVert[1].x - CenX ) * ExtendRateX ;
				YBuf[2] = ( TexVert[1].y - CenY ) * ExtendRateY ;
				XBuf[3] = XBuf[2] * Cos - YBuf[2] * Sin ;
				YBuf[3] = XBuf[2] * Sin + YBuf[2] * Cos ;

				XBuf[4] = ( TexVert[2].x - CenX ) * ExtendRateX ;
				YBuf[4] = ( TexVert[2].y - CenY ) * ExtendRateY ;
				XBuf[5] = XBuf[4] * Cos - YBuf[4] * Sin ;
				YBuf[5] = XBuf[4] * Sin + YBuf[4] * Cos ;

				XBuf[6] = ( TexVert[3].x - CenX ) * ExtendRateX ;
				YBuf[6] = ( TexVert[3].y - CenY ) * ExtendRateY ;
				XBuf[7] = XBuf[6] * Cos - YBuf[6] * Sin ;
				YBuf[7] = XBuf[6] * Sin + YBuf[6] * Cos ;

				DrawVertB[0].pos.x = XBuf[1] + xf ;
				DrawVertB[0].pos.y = YBuf[1] + yf ;
				DrawVertB[1].pos.x = XBuf[3] + xf ;
				DrawVertB[1].pos.y = YBuf[3] + yf ;
				DrawVertB[2].pos.x = XBuf[5] + xf ;
				DrawVertB[2].pos.y = YBuf[5] + yf ;
				DrawVertB[3].pos.x = XBuf[7] + xf ;
				DrawVertB[3].pos.y = YBuf[7] + yf ;
				DrawVertB[4].pos.x = XBuf[5] + xf ;
				DrawVertB[4].pos.y = YBuf[5] + yf ;
				DrawVertB[5].pos.x = XBuf[3] + xf ;
				DrawVertB[5].pos.y = YBuf[3] + yf ;

				switch( GSYS.DrawSetting.BlendGraphPosMode )
				{
				default :
				case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
					u[ 0 ] = ( TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u[ 1 ] = ( TexVert[1].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u[ 2 ] = ( TexVert[2].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					u[ 3 ] = ( TexVert[3].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					
					v[ 0 ] = ( TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v[ 1 ] = ( TexVert[1].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v[ 2 ] = ( TexVert[2].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					v[ 3 ] = ( TexVert[3].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;

					DrawVertB[0].u1 = u[ 0 ] ;
					DrawVertB[0].v1 = v[ 0 ] ;
					DrawVertB[1].u1 = u[ 1 ] ;
					DrawVertB[1].v1 = v[ 1 ] ;
					DrawVertB[2].u1 = u[ 2 ] ;
					DrawVertB[2].v1 = v[ 2 ] ;
					DrawVertB[3].u1 = u[ 3 ] ;
					DrawVertB[3].v1 = v[ 3 ] ;
					DrawVertB[4].u1 = u[ 2 ] ;
					DrawVertB[4].v1 = v[ 2 ] ;
					DrawVertB[5].u1 = u[ 1 ] ;
					DrawVertB[5].v1 = v[ 1 ] ;
					break ;

				case DX_BLENDGRAPH_POSMODE_SCREEN :
					DrawVertB[0].u1 = ( ( XBuf[1] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[0].v1 = ( ( YBuf[1] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[1].u1 = ( ( XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[1].v1 = ( ( YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[2].u1 = ( ( XBuf[5] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[2].v1 = ( ( YBuf[5] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[3].u1 = ( ( XBuf[7] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[3].v1 = ( ( YBuf[7] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[4].u1 = ( ( XBuf[5] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[4].v1 = ( ( YBuf[5] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[5].u1 = ( ( XBuf[3] + xf ) - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[5].v1 = ( ( YBuf[3] + yf ) - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					break ;
				}

				DrawVertB[0].u2 = TexVert[0].u ;
				DrawVertB[0].v2 = TexVert[0].v ;
				DrawVertB[1].u2 = TexVert[1].u ;
				DrawVertB[1].v2 = TexVert[0].v ;
				DrawVertB[2].u2 = TexVert[0].u ;
				DrawVertB[2].v2 = TexVert[2].v ;
				DrawVertB[3].u2 = TexVert[1].u ;
				DrawVertB[3].v2 = TexVert[2].v ;
				DrawVertB[4].u2 = TexVert[0].u ;
				DrawVertB[4].v2 = TexVert[2].v ;
				DrawVertB[5].u2 = TexVert[1].u ;
				DrawVertB[5].v2 = TexVert[0].v ;

				*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[2].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[3].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[4].pos.z) = drawz ;
				*((DWORD *)&DrawVertB[5].pos.z) = drawz ;

				DrawVertB[0].rhw = 1.0f ;
				DrawVertB[1].rhw = 1.0f ;
				DrawVertB[2].rhw = 1.0f ;
				DrawVertB[3].rhw = 1.0f ;
				DrawVertB[4].rhw = 1.0f ;
				DrawVertB[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_BLENDTEX

				if( BlendGraphNoIncFlag == FALSE )
				{
					BlendDrawTex ++ ;
				}
			}
		}
		break ;

	case VERTEXTYPE_TEX :	// �u�����h�e�N�X�`�����g�p���Ȃ�
		// �e�N�X�`���[�̐������J��Ԃ�
		if( DrawTexNum == 1 )
		{
			if( SinCosNone == 0 )
			{
				// ���_�f�[�^������������
				GETVERTEX_QUAD( DrawVert )
				
				TexVert = DrawTex->Vertex ;

				DrawVert[0].color = ( DWORD )DiffuseColor ;
				DrawVert[1].color = ( DWORD )DiffuseColor ;
				DrawVert[2].color = ( DWORD )DiffuseColor ;
				DrawVert[3].color = ( DWORD )DiffuseColor ;
				DrawVert[4].color = ( DWORD )DiffuseColor ;
				DrawVert[5].color = ( DWORD )DiffuseColor ;

				DrawVert[0].u = TexVert[0].u ;
				DrawVert[0].v = TexVert[0].v ;
				DrawVert[1].u = TexVert[1].u ;
				DrawVert[1].v = TexVert[0].v ;
				DrawVert[2].v = TexVert[2].v ;
				DrawVert[2].u = TexVert[0].u ;
				DrawVert[3].u = TexVert[1].u ;
				DrawVert[3].v = TexVert[2].v ;
				DrawVert[4].u = TexVert[0].u ;
				DrawVert[4].v = TexVert[2].v ;
				DrawVert[5].u = TexVert[1].u ;
				DrawVert[5].v = TexVert[0].v ;

				XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX ;
				YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY ;
				XBuf[1] = XBuf[0] * Cos - YBuf[0] * Sin ;
				YBuf[1] = XBuf[0] * Sin + YBuf[0] * Cos ;
				
				XBuf[2] = ( TexVert[1].x - CenX ) * ExtendRateX ;
				YBuf[2] = ( TexVert[1].y - CenY ) * ExtendRateY ;
				XBuf[3] = XBuf[2] * Cos - YBuf[2] * Sin ;
				YBuf[3] = XBuf[2] * Sin + YBuf[2] * Cos ;

				DrawVert[0].pos.x =  XBuf[1] + xf ;
				DrawVert[0].pos.y =  YBuf[1] + yf ;
				DrawVert[1].pos.x =  XBuf[3] + xf ;
				DrawVert[1].pos.y =  YBuf[3] + yf ;
				DrawVert[2].pos.x = -XBuf[3] + xf ;
				DrawVert[2].pos.y = -YBuf[3] + yf ;
				DrawVert[3].pos.x = -XBuf[1] + xf ;
				DrawVert[3].pos.y = -YBuf[1] + yf ;
				DrawVert[4].pos.x = -XBuf[3] + xf ;
				DrawVert[4].pos.y = -YBuf[3] + yf ;
				DrawVert[5].pos.x =  XBuf[3] + xf ;
				DrawVert[5].pos.y =  YBuf[3] + yf ;

				*((DWORD *)&DrawVert[0].pos.z) = drawz ;
				*((DWORD *)&DrawVert[1].pos.z) = drawz ;
				*((DWORD *)&DrawVert[2].pos.z) = drawz ;
				*((DWORD *)&DrawVert[3].pos.z) = drawz ;
				*((DWORD *)&DrawVert[4].pos.z) = drawz ;
				*((DWORD *)&DrawVert[5].pos.z) = drawz ;

				DrawVert[0].rhw = 1.0f ;
				DrawVert[1].rhw = 1.0f ;
				DrawVert[2].rhw = 1.0f ;
				DrawVert[3].rhw = 1.0f ;
				DrawVert[4].rhw = 1.0f ;
				DrawVert[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_TEX
			}
			else
			{
				// ���_�f�[�^������������
				GETVERTEX_QUAD( DrawVert )
				
				TexVert = DrawTex->Vertex ;

				DrawVert[0].color = ( DWORD )DiffuseColor ;
				DrawVert[1].color = ( DWORD )DiffuseColor ;
				DrawVert[2].color = ( DWORD )DiffuseColor ;
				DrawVert[3].color = ( DWORD )DiffuseColor ;
				DrawVert[4].color = ( DWORD )DiffuseColor ;
				DrawVert[5].color = ( DWORD )DiffuseColor ;

				DrawVert[0].u = TexVert[0].u ;
				DrawVert[0].v = TexVert[0].v ;
				DrawVert[1].u = TexVert[1].u ;
				DrawVert[1].v = TexVert[0].v ;
				DrawVert[2].u = TexVert[0].u ;
				DrawVert[2].v = TexVert[2].v ;
				DrawVert[3].u = TexVert[1].u ;
				DrawVert[3].v = TexVert[2].v ;
				DrawVert[4].u = TexVert[0].u ;
				DrawVert[4].v = TexVert[2].v ;
				DrawVert[5].u = TexVert[1].u ;
				DrawVert[5].v = TexVert[0].v ;

				XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX ;
				YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY ;

				XBuf[1] = ( TexVert[1].x - CenX ) * ExtendRateX ;
				YBuf[1] = ( TexVert[1].y - CenY ) * ExtendRateY ;

				DrawVert[0].pos.x =  XBuf[0] + xf ;
				DrawVert[0].pos.y =  YBuf[0] + yf ;
				DrawVert[1].pos.x =  XBuf[1] + xf ;
				DrawVert[1].pos.y =  YBuf[1] + yf ;
				DrawVert[2].pos.x = -XBuf[1] + xf ;
				DrawVert[2].pos.y = -YBuf[1] + yf ;
				DrawVert[3].pos.x = -XBuf[0] + xf ;
				DrawVert[3].pos.y = -YBuf[0] + yf ;
				DrawVert[4].pos.x = -XBuf[1] + xf ;
				DrawVert[4].pos.y = -YBuf[1] + yf ;
				DrawVert[5].pos.x =  XBuf[1] + xf ;
				DrawVert[5].pos.y =  YBuf[1] + yf ;

				*((DWORD *)&DrawVert[0].pos.z) = drawz ;
				*((DWORD *)&DrawVert[1].pos.z) = drawz ;
				*((DWORD *)&DrawVert[2].pos.z) = drawz ;
				*((DWORD *)&DrawVert[3].pos.z) = drawz ;
				*((DWORD *)&DrawVert[4].pos.z) = drawz ;
				*((DWORD *)&DrawVert[5].pos.z) = drawz ;

				DrawVert[0].rhw = 1.0f ;
				DrawVert[1].rhw = 1.0f ;
				DrawVert[2].rhw = 1.0f ;
				DrawVert[3].rhw = 1.0f ;
				DrawVert[4].rhw = 1.0f ;
				DrawVert[5].rhw = 1.0f ;

				// �e�N�X�`���[��`�悷��
				ADD4VERTEX_TEX
			}
		}
		else
		{
			if( SinCosNone == 0 )
			{
				// �e�N�X�`���[�̐������J��Ԃ�
				i = 0 ;
				for(;;)
				{
					// ���_�f�[�^������������
					GETVERTEX_QUAD( DrawVert )
					
					TexVert = DrawTex->Vertex ;

					DrawVert[0].color = ( DWORD )DiffuseColor ;
					DrawVert[1].color = ( DWORD )DiffuseColor ;
					DrawVert[2].color = ( DWORD )DiffuseColor ;
					DrawVert[3].color = ( DWORD )DiffuseColor ;
					DrawVert[4].color = ( DWORD )DiffuseColor ;
					DrawVert[5].color = ( DWORD )DiffuseColor ;

					DrawVert[0].u = TexVert[0].u ;
					DrawVert[0].v = TexVert[0].v ;
					DrawVert[1].u = TexVert[1].u ;
					DrawVert[1].v = TexVert[0].v ;
					DrawVert[2].u = TexVert[0].u ;
					DrawVert[2].v = TexVert[2].v ;
					DrawVert[3].u = TexVert[1].u ;
					DrawVert[3].v = TexVert[2].v ;
					DrawVert[4].u = TexVert[0].u ;
					DrawVert[4].v = TexVert[2].v ;
					DrawVert[5].u = TexVert[1].u ;
					DrawVert[5].v = TexVert[0].v ;

					XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX ;
					YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY ;
					XBuf[1] = XBuf[0] * Cos - YBuf[0] * Sin ;
					YBuf[1] = XBuf[0] * Sin + YBuf[0] * Cos ;

					XBuf[2] = ( TexVert[1].x - CenX ) * ExtendRateX ;
					YBuf[2] = ( TexVert[1].y - CenY ) * ExtendRateY ;
					XBuf[3] = XBuf[2] * Cos - YBuf[2] * Sin ;
					YBuf[3] = XBuf[2] * Sin + YBuf[2] * Cos ;

					XBuf[4] = ( TexVert[2].x - CenX ) * ExtendRateX ;
					YBuf[4] = ( TexVert[2].y - CenY ) * ExtendRateY ;
					XBuf[5] = XBuf[4] * Cos - YBuf[4] * Sin ;
					YBuf[5] = XBuf[4] * Sin + YBuf[4] * Cos ;

					XBuf[6] = ( TexVert[3].x - CenX ) * ExtendRateX ;
					YBuf[6] = ( TexVert[3].y - CenY ) * ExtendRateY ;
					XBuf[7] = XBuf[6] * Cos - YBuf[6] * Sin ;
					YBuf[7] = XBuf[6] * Sin + YBuf[6] * Cos ;

					DrawVert[0].pos.x = XBuf[1] + xf ;
					DrawVert[0].pos.y = YBuf[1] + yf ;
					DrawVert[1].pos.x = XBuf[3] + xf ;
					DrawVert[1].pos.y = YBuf[3] + yf ;
					DrawVert[2].pos.x = XBuf[5] + xf ;
					DrawVert[2].pos.y = YBuf[5] + yf ;
					DrawVert[3].pos.x = XBuf[7] + xf ;
					DrawVert[3].pos.y = YBuf[7] + yf ;
					DrawVert[4].pos.x = XBuf[5] + xf ;
					DrawVert[4].pos.y = YBuf[5] + yf ;
					DrawVert[5].pos.x = XBuf[3] + xf ;
					DrawVert[5].pos.y = YBuf[3] + yf ;

					*((DWORD *)&DrawVert[0].pos.z) = drawz ;
					*((DWORD *)&DrawVert[1].pos.z) = drawz ;
					*((DWORD *)&DrawVert[2].pos.z) = drawz ;
					*((DWORD *)&DrawVert[3].pos.z) = drawz ;
					*((DWORD *)&DrawVert[4].pos.z) = drawz ;
					*((DWORD *)&DrawVert[5].pos.z) = drawz ;

					DrawVert[0].rhw = 1.0f ;
					DrawVert[1].rhw = 1.0f ;
					DrawVert[2].rhw = 1.0f ;
					DrawVert[3].rhw = 1.0f ;
					DrawVert[4].rhw = 1.0f ;
					DrawVert[5].rhw = 1.0f ;

					// �e�N�X�`���[��`�悷��
					ADD4VERTEX_TEX

					i ++ ;
					if( i >= DrawTexNum ) break ;

					// �`�悷��e�N�X�`���[�̃Z�b�g
					DrawTex ++ ;
					Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
					Graphics_Android_DeviceState_NormalDrawSetup() ;
				}
			}
			else
			{
				// �e�N�X�`���[�̐������J��Ԃ�
				i = 0 ;
				for(;;)
				{
					// ���_�f�[�^������������
					GETVERTEX_QUAD( DrawVert )
					
					TexVert = DrawTex->Vertex ;

					DrawVert[0].color = ( DWORD )DiffuseColor ;
					DrawVert[1].color = ( DWORD )DiffuseColor ;
					DrawVert[2].color = ( DWORD )DiffuseColor ;
					DrawVert[3].color = ( DWORD )DiffuseColor ;
					DrawVert[4].color = ( DWORD )DiffuseColor ;
					DrawVert[5].color = ( DWORD )DiffuseColor ;

					DrawVert[0].u = TexVert[0].u ;
					DrawVert[0].v = TexVert[0].v ;
					DrawVert[1].u = TexVert[1].u ;
					DrawVert[1].v = TexVert[0].v ;
					DrawVert[2].v = TexVert[2].v ;
					DrawVert[2].u = TexVert[0].u ;
					DrawVert[3].u = TexVert[1].u ;
					DrawVert[3].v = TexVert[2].v ;
					DrawVert[4].u = TexVert[0].u ;
					DrawVert[4].v = TexVert[2].v ;
					DrawVert[5].u = TexVert[1].u ;
					DrawVert[5].v = TexVert[0].v ;

					XBuf[0] = ( TexVert[0].x - CenX ) * ExtendRateX + xf ;
					YBuf[0] = ( TexVert[0].y - CenY ) * ExtendRateY + yf ;
					XBuf[1] = ( TexVert[1].x - CenX ) * ExtendRateX + xf ;
					YBuf[1] = ( TexVert[1].y - CenY ) * ExtendRateY + yf ;
					XBuf[2] = ( TexVert[2].x - CenX ) * ExtendRateX + xf ;
					YBuf[2] = ( TexVert[2].y - CenY ) * ExtendRateY + yf ;
					XBuf[3] = ( TexVert[3].x - CenX ) * ExtendRateX + xf ;
					YBuf[3] = ( TexVert[3].y - CenY ) * ExtendRateY + yf ;

					DrawVert[0].pos.x = XBuf[0] ;
					DrawVert[0].pos.y = YBuf[0] ;
					DrawVert[1].pos.x = XBuf[1] ;
					DrawVert[1].pos.y = YBuf[1] ;
					DrawVert[2].pos.x = XBuf[2] ;
					DrawVert[2].pos.y = YBuf[2] ;
					DrawVert[3].pos.x = XBuf[3] ;
					DrawVert[3].pos.y = YBuf[3] ;
					DrawVert[4].pos.x = XBuf[2] ;
					DrawVert[4].pos.y = YBuf[2] ;
					DrawVert[5].pos.x = XBuf[1] ;
					DrawVert[5].pos.y = YBuf[1] ;

					*((DWORD *)&DrawVert[0].pos.z) = drawz ;
					*((DWORD *)&DrawVert[1].pos.z) = drawz ;
					*((DWORD *)&DrawVert[2].pos.z) = drawz ;
					*((DWORD *)&DrawVert[3].pos.z) = drawz ;
					*((DWORD *)&DrawVert[4].pos.z) = drawz ;
					*((DWORD *)&DrawVert[5].pos.z) = drawz ;

					DrawVert[0].rhw = 1.0f ;
					DrawVert[1].rhw = 1.0f ;
					DrawVert[2].rhw = 1.0f ;
					DrawVert[3].rhw = 1.0f ;
					DrawVert[4].rhw = 1.0f ;
					DrawVert[5].rhw = 1.0f ;

					// �e�N�X�`���[��`�悷��
					ADD4VERTEX_TEX

					i ++ ;
					if( i >= DrawTexNum ) break ;

					// �`�悷��e�N�X�`���[�̃Z�b�g
					DrawTex ++ ;
					Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
					Graphics_Android_DeviceState_NormalDrawSetup() ;
				}
			}
		}
		break ;
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawModiGraph
extern	int		Graphics_Hardware_DrawModiGraph_PF( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, IMAGEDATA *Image, IMAGEDATA *BlendImage, int TransFlag, bool SimpleDrawFlag )
{
	if( x1 == x3 && x2 == x4 && y1 == y2 && y3 == y4 ) return Graphics_Hardware_DrawExtendGraph_PF( x1, y1, x4, y4, ( float )x1, ( float )y1, ( float )x4, ( float )y4, Image, BlendImage, TransFlag, TRUE ) ; 

	// �����u�����h�e�N�X�`�����g�p�����A���^�֐����g�p����t���O�������Ă��Ȃ����
	// �����������s���`��֐����g�p����
	if( GANDR.Setting.UseOldDrawModiGraphCodeFlag == FALSE && GSYS.DrawSetting.BlendGraph <= 0 )
		return Graphics_Hardware_DrawModiGraphF_PF( (float)x1, (float)y1, (float)x2, (float)y2, (float)x3, (float)y3, (float)x4, (float)y4, Image, BlendImage, TransFlag, SimpleDrawFlag ) ;

	VERTEX_2D           *DrawVert ;
	VERTEX_BLENDTEX_2D	*DrawVertB ;
	IMAGEDATA_HARD_DRAW *DrawTex ;
	IMAGEDATA_HARD_DRAW *BlendDrawTex = NULL ;
	IMAGEDATA_HARD_VERT *TexVert ;
	IMAGEDATA_HARD_VERT *BlendTexVert ;
	float GraphSizeX, GraphSizeY ;
	float XBuf, YBuf ;
	int DrawTexNum ;
	unsigned char *VertType ;
	int i, j ; 
	int BlendGraphNoIncFlag ;
	float Reverse0 ;
	float ExRate1X1, ExRate1Y1, ExRate2X1, ExRate2Y1 ;
	float ExRate1X2, ExRate1Y2, ExRate2X2, ExRate2Y2 ;
	DWORD DiffuseColor ;
	VECTOR DrawPos[ 4 ] ;
	float u[ 4 ] ;
	float v[ 4 ] ;
	float  xf1, yf1, xf4, yf4;
	DWORD drawz ;
	int Flag ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Flag = TransFlag | DX_ANDROID_DRAWPREP_VECTORINT ;
	DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )

	GraphSizeX = ( float )Image->WidthF ;  GraphSizeY = ( float )Image->HeightF ;
	ExRate1X1 = ( x2 - x1 ) /  GraphSizeX ;  ExRate1X2 = ( x3 - x1 ) /  GraphSizeY ;
	ExRate1Y1 = ( y3 - y1 ) /  GraphSizeY ;  ExRate1Y2 = ( y2 - y1 ) /  GraphSizeX ;
	ExRate2X1 = ( x3 - x4 ) / -GraphSizeX ;  ExRate2X2 = ( x2 - x4 ) / -GraphSizeY ;
	ExRate2Y1 = ( y2 - y4 ) / -GraphSizeY ;  ExRate2Y2 = ( y3 - y4 ) / -GraphSizeX ;
//	xf1 = (float)x1 - 0.5F ; yf1 = (float)y1 - 0.5F ;
//	xf4 = (float)x4 - 0.5F ; yf4 = (float)y4 - 0.5F ; 
	xf1 = (float)x1 ; yf1 = (float)y1 ;
	xf4 = (float)x4 ; yf4 = (float)y4 ; 

	// ���_�f�[�^���擾�i���̂Ƃ���F���̃Z�b�g�̂݁j
	DiffuseColor = GANDR.Device.DrawInfo.DiffuseColor ;

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �`����̐����Z�b�g
	DrawTexNum = Image->Hard.DrawNum ;

	// �`����̐����u�����h�摜�ƈقȂ��Ă�����O�Ԗڂ̃e�N�X�`���������g�p����
	BlendGraphNoIncFlag = FALSE ;
	if( BlendImage != NULL && BlendImage->Hard.DrawNum != Image->Hard.DrawNum )
	{
		BlendGraphNoIncFlag = TRUE ;
	}

	// �`����z��̃A�h���X���Z�b�g���Ă���
	DrawTex = Image->Hard.Draw ;
	if( BlendImage != NULL )
	{
		BlendDrawTex = BlendImage->Hard.Draw ;
	}

	// ���_�^�C�v�ɂ���ď����𕪊�
	switch( GANDR.Device.DrawInfo.VertexType )
	{
	case VERTEXTYPE_BLENDTEX :	// �u�����h�e�N�X�`�����g�p����
		// �e�N�X�`���[�̐������J��Ԃ�
		for( i = 0 ; i < DrawTexNum ; i ++, DrawTex ++ )
		{
			// �`�悷��e�N�X�`���[�̃Z�b�g
			Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
			Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

			Graphics_Android_DeviceState_NormalDrawSetup() ;

			// ���_�o�b�t�@�̎擾
			GETVERTEX_QUAD( DrawVertB )

			DrawVertB[0].color = ( DWORD )DiffuseColor ;
			DrawVertB[1].color = ( DWORD )DiffuseColor ;
			DrawVertB[2].color = ( DWORD )DiffuseColor ;
			DrawVertB[3].color = ( DWORD )DiffuseColor ;
			DrawVertB[4].color = ( DWORD )DiffuseColor ;
			DrawVertB[5].color = ( DWORD )DiffuseColor ;

			VertType     = DrawTex->VertType ;
			TexVert      = DrawTex->Vertex ;
			BlendTexVert = BlendDrawTex->Vertex ;

			for( j = 0 ; j < 4 ; j ++, TexVert ++ )
			{
				// ���_���W�̎Z�o
				if( *VertType ++ )
				{
					// �O�p�̏㑤
					DrawPos[ j ].x = ( TexVert->x * ExRate1X1 ) + ( TexVert->y * ExRate1X2 ) + xf1 ;
					DrawPos[ j ].y = ( TexVert->y * ExRate1Y1 ) + ( TexVert->x * ExRate1Y2 ) + yf1 ;
				} 
				else
				{
					// �O�p�̉���
					XBuf = TexVert->x - GraphSizeX ;
					YBuf = TexVert->y - GraphSizeY ;
					DrawPos[ j ].x = ( XBuf * ExRate2X1 ) + ( YBuf * ExRate2X2 ) + xf4 ;
					DrawPos[ j ].y = ( YBuf * ExRate2Y1 ) + ( XBuf * ExRate2Y2 ) + yf4 ;
				}

				u[ j ] = ( TexVert->x - BlendTexVert->x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ j ] = ( TexVert->y - BlendTexVert->y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
			}

			// ���]���菈��
			Reverse0 =  ( DrawPos[ 1 ].x - DrawPos[ 0 ].x ) * ( DrawPos[ 2 ].y - DrawPos[ 0 ].y ) -
						( DrawPos[ 2 ].x - DrawPos[ 0 ].x ) * ( DrawPos[ 1 ].y - DrawPos[ 0 ].y ) ;
//			Reverse1 = -( DrawPos[ 1 ].x - DrawPos[ 3 ].x ) * ( DrawPos[ 2 ].y - DrawPos[ 3 ].y ) +
//						( DrawPos[ 1 ].y - DrawPos[ 3 ].y ) * ( DrawPos[ 2 ].x - DrawPos[ 3 ].x ) ;
			TexVert = DrawTex->Vertex ;
			if( Reverse0 <= 0 )
			{
				DrawVertB[ 0 ].pos.x = DrawPos[ 0 ].x ;
				DrawVertB[ 0 ].pos.y = DrawPos[ 0 ].y ;
				DrawVertB[ 1 ].pos.x = DrawPos[ 2 ].x ;
				DrawVertB[ 1 ].pos.y = DrawPos[ 2 ].y ;
				DrawVertB[ 2 ].pos.x = DrawPos[ 1 ].x ;
				DrawVertB[ 2 ].pos.y = DrawPos[ 1 ].y ;
				DrawVertB[ 3 ].pos.x = DrawPos[ 3 ].x ;
				DrawVertB[ 3 ].pos.y = DrawPos[ 3 ].y ;
				DrawVertB[ 4 ].pos.x = DrawPos[ 1 ].x ;
				DrawVertB[ 4 ].pos.y = DrawPos[ 1 ].y ;
				DrawVertB[ 5 ].pos.x = DrawPos[ 2 ].x ;
				DrawVertB[ 5 ].pos.y = DrawPos[ 2 ].y ;

				switch( GSYS.DrawSetting.BlendGraphPosMode )
				{
				default :
				case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
					DrawVertB[ 0 ].u1 = u[ 0 ] ;
					DrawVertB[ 0 ].v1 = v[ 0 ] ;
					DrawVertB[ 1 ].u1 = u[ 2 ] ;
					DrawVertB[ 1 ].v1 = v[ 2 ] ;
					DrawVertB[ 2 ].u1 = u[ 1 ] ;
					DrawVertB[ 2 ].v1 = v[ 1 ] ;
					DrawVertB[ 3 ].u1 = u[ 3 ] ;
					DrawVertB[ 3 ].v1 = v[ 3 ] ;
					DrawVertB[ 4 ].u1 = u[ 1 ] ;
					DrawVertB[ 4 ].v1 = v[ 1 ] ;
					DrawVertB[ 5 ].u1 = u[ 2 ] ;
					DrawVertB[ 5 ].v1 = v[ 2 ] ;
					break ;

				case DX_BLENDGRAPH_POSMODE_SCREEN :
					DrawVertB[ 0 ].u1 = ( DrawPos[ 0 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 0 ].v1 = ( DrawPos[ 0 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[ 1 ].u1 = ( DrawPos[ 2 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 1 ].v1 = ( DrawPos[ 2 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[ 2 ].u1 = ( DrawPos[ 1 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 2 ].v1 = ( DrawPos[ 1 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[ 3 ].u1 = ( DrawPos[ 3 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 3 ].v1 = ( DrawPos[ 3 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[ 4 ].u1 = ( DrawPos[ 1 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 4 ].v1 = ( DrawPos[ 1 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[ 5 ].u1 = ( DrawPos[ 2 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 5 ].v1 = ( DrawPos[ 2 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					break ;
				}

				DrawVertB[ 0 ].u2 = TexVert[ 0 ].u ;
				DrawVertB[ 0 ].v2 = TexVert[ 0 ].v ;
				DrawVertB[ 1 ].u2 = TexVert[ 2 ].u ;
				DrawVertB[ 1 ].v2 = TexVert[ 2 ].v ;
				DrawVertB[ 2 ].u2 = TexVert[ 1 ].u ;
				DrawVertB[ 2 ].v2 = TexVert[ 1 ].v ;
				DrawVertB[ 3 ].u2 = TexVert[ 3 ].u ;
				DrawVertB[ 3 ].v2 = TexVert[ 3 ].v ;
				DrawVertB[ 4 ].u2 = TexVert[ 1 ].u ;
				DrawVertB[ 4 ].v2 = TexVert[ 1 ].v ;
				DrawVertB[ 5 ].u2 = TexVert[ 2 ].u ;
				DrawVertB[ 5 ].v2 = TexVert[ 2 ].v ;
			}
			else
			{
				DrawVertB[ 0 ].pos.x = DrawPos[ 0 ].x ;
				DrawVertB[ 0 ].pos.y = DrawPos[ 0 ].y ;
				DrawVertB[ 1 ].pos.x = DrawPos[ 1 ].x ;
				DrawVertB[ 1 ].pos.y = DrawPos[ 1 ].y ;
				DrawVertB[ 2 ].pos.x = DrawPos[ 2 ].x ;
				DrawVertB[ 2 ].pos.y = DrawPos[ 2 ].y ;
				DrawVertB[ 3 ].pos.x = DrawPos[ 3 ].x ;
				DrawVertB[ 3 ].pos.y = DrawPos[ 3 ].y ;
				DrawVertB[ 4 ].pos.x = DrawPos[ 2 ].x ;
				DrawVertB[ 4 ].pos.y = DrawPos[ 2 ].y ;
				DrawVertB[ 5 ].pos.x = DrawPos[ 1 ].x ;
				DrawVertB[ 5 ].pos.y = DrawPos[ 1 ].y ;

				switch( GSYS.DrawSetting.BlendGraphPosMode )
				{
				default :
				case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
					DrawVertB[ 0 ].u1 = u[ 0 ] ;
					DrawVertB[ 0 ].v1 = v[ 0 ] ;
					DrawVertB[ 1 ].u1 = u[ 1 ] ;
					DrawVertB[ 1 ].v1 = v[ 1 ] ;
					DrawVertB[ 2 ].u1 = u[ 2 ] ;
					DrawVertB[ 2 ].v1 = v[ 2 ] ;
					DrawVertB[ 3 ].u1 = u[ 3 ] ;
					DrawVertB[ 3 ].v1 = v[ 3 ] ;
					DrawVertB[ 4 ].u1 = u[ 2 ] ;
					DrawVertB[ 4 ].v1 = v[ 2 ] ;
					DrawVertB[ 5 ].u1 = u[ 1 ] ;
					DrawVertB[ 5 ].v1 = v[ 1 ] ;
					break ;

				case DX_BLENDGRAPH_POSMODE_SCREEN :
					DrawVertB[ 0 ].u1 = ( DrawPos[ 0 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 0 ].v1 = ( DrawPos[ 0 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[ 1 ].u1 = ( DrawPos[ 1 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 1 ].v1 = ( DrawPos[ 1 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[ 2 ].u1 = ( DrawPos[ 2 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 2 ].v1 = ( DrawPos[ 2 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[ 3 ].u1 = ( DrawPos[ 3 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 3 ].v1 = ( DrawPos[ 3 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[ 4 ].u1 = ( DrawPos[ 2 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 4 ].v1 = ( DrawPos[ 2 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					DrawVertB[ 5 ].u1 = ( DrawPos[ 1 ].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
					DrawVertB[ 5 ].v1 = ( DrawPos[ 1 ].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
					break ;
				}

				DrawVertB[ 0 ].u2 = TexVert[ 0 ].u ;
				DrawVertB[ 0 ].v2 = TexVert[ 0 ].v ;
				DrawVertB[ 1 ].u2 = TexVert[ 1 ].u ;
				DrawVertB[ 1 ].v2 = TexVert[ 1 ].v ;
				DrawVertB[ 2 ].u2 = TexVert[ 2 ].u ;
				DrawVertB[ 2 ].v2 = TexVert[ 2 ].v ;
				DrawVertB[ 3 ].u2 = TexVert[ 3 ].u ;
				DrawVertB[ 3 ].v2 = TexVert[ 3 ].v ;
				DrawVertB[ 4 ].u2 = TexVert[ 2 ].u ;
				DrawVertB[ 4 ].v2 = TexVert[ 2 ].v ;
				DrawVertB[ 5 ].u2 = TexVert[ 1 ].u ;
				DrawVertB[ 5 ].v2 = TexVert[ 1 ].v ;
			}

			*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[2].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[3].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[4].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[5].pos.z) = drawz ;

			DrawVertB[0].rhw = 1.0f ;
			DrawVertB[1].rhw = 1.0f ;
			DrawVertB[2].rhw = 1.0f ;
			DrawVertB[3].rhw = 1.0f ;
			DrawVertB[4].rhw = 1.0f ;
			DrawVertB[5].rhw = 1.0f ;

			// �e�N�X�`���[��`�悷��
			ADD4VERTEX_BLENDTEX

			if( BlendGraphNoIncFlag == FALSE )
			{
				BlendDrawTex ++ ;
			}
		}
		break ;

	case VERTEXTYPE_TEX :	// �u�����h�e�N�X�`�����g�p���Ȃ�
		// �e�N�X�`���[�̐������J��Ԃ�
		i = 0 ;
		for(;;)
		{
			// ���_�o�b�t�@�̎擾
			GETVERTEX_QUAD( DrawVert )

			// ���_�f�[�^���Z�b�g����
			DrawVert[0].color = ( DWORD )DiffuseColor ;
			DrawVert[1].color = ( DWORD )DiffuseColor ;
			DrawVert[2].color = ( DWORD )DiffuseColor ;
			DrawVert[3].color = ( DWORD )DiffuseColor ;
			DrawVert[4].color = ( DWORD )DiffuseColor ;
			DrawVert[5].color = ( DWORD )DiffuseColor ;

			VertType = DrawTex->VertType ;
			TexVert  = DrawTex->Vertex ;

			for( j = 0 ; j < 4 ; j ++, TexVert ++ )
			{
				// ���_���W�̎Z�o
				if( *VertType ++ )
				{
					// �O�p�̏㑤
					DrawPos[ j ].x = ( TexVert->x * ExRate1X1 ) + ( TexVert->y * ExRate1X2 ) + xf1 ;
					DrawPos[ j ].y = ( TexVert->y * ExRate1Y1 ) + ( TexVert->x * ExRate1Y2 ) + yf1 ;
				} 
				else
				{
					// �O�p�̉���
					XBuf = TexVert->x - GraphSizeX ;
					YBuf = TexVert->y - GraphSizeY ;
					DrawPos[ j ].x = ( XBuf * ExRate2X1 ) + ( YBuf * ExRate2X2 ) + xf4 ;
					DrawPos[ j ].y = ( YBuf * ExRate2Y1 ) + ( XBuf * ExRate2Y2 ) + yf4 ;
				}
			}

			// ���]���菈��
			Reverse0 =  ( DrawPos[ 1 ].x - DrawPos[ 0 ].x ) * ( DrawPos[ 2 ].y - DrawPos[ 0 ].y ) -
						( DrawPos[ 2 ].x - DrawPos[ 0 ].x ) * ( DrawPos[ 1 ].y - DrawPos[ 0 ].y ) ;
			TexVert = DrawTex->Vertex ;
			if( Reverse0 <= 0 )
			{
				DrawVert[ 0 ].pos.x = DrawPos[ 0 ].x ;
				DrawVert[ 0 ].pos.y = DrawPos[ 0 ].y ;
				DrawVert[ 1 ].pos.x = DrawPos[ 2 ].x ;
				DrawVert[ 1 ].pos.y = DrawPos[ 2 ].y ;
				DrawVert[ 2 ].pos.x = DrawPos[ 1 ].x ;
				DrawVert[ 2 ].pos.y = DrawPos[ 1 ].y ;
				DrawVert[ 3 ].pos.x = DrawPos[ 3 ].x ;
				DrawVert[ 3 ].pos.y = DrawPos[ 3 ].y ;
				DrawVert[ 4 ].pos.x = DrawPos[ 1 ].x ;
				DrawVert[ 4 ].pos.y = DrawPos[ 1 ].y ;
				DrawVert[ 5 ].pos.x = DrawPos[ 2 ].x ;
				DrawVert[ 5 ].pos.y = DrawPos[ 2 ].y ;

				DrawVert[ 0 ].u = TexVert[ 0 ].u ;
				DrawVert[ 0 ].v = TexVert[ 0 ].v ;
				DrawVert[ 1 ].u = TexVert[ 2 ].u ;
				DrawVert[ 1 ].v = TexVert[ 2 ].v ;
				DrawVert[ 2 ].u = TexVert[ 1 ].u ;
				DrawVert[ 2 ].v = TexVert[ 1 ].v ;
				DrawVert[ 3 ].u = TexVert[ 3 ].u ;
				DrawVert[ 3 ].v = TexVert[ 3 ].v ;
				DrawVert[ 4 ].u = TexVert[ 1 ].u ;
				DrawVert[ 4 ].v = TexVert[ 1 ].v ;
				DrawVert[ 5 ].u = TexVert[ 2 ].u ;
				DrawVert[ 5 ].v = TexVert[ 2 ].v ;
			}
			else
			{
				DrawVert[ 0 ].pos.x = DrawPos[ 0 ].x ;
				DrawVert[ 0 ].pos.y = DrawPos[ 0 ].y ;
				DrawVert[ 1 ].pos.x = DrawPos[ 1 ].x ;
				DrawVert[ 1 ].pos.y = DrawPos[ 1 ].y ;
				DrawVert[ 2 ].pos.x = DrawPos[ 2 ].x ;
				DrawVert[ 2 ].pos.y = DrawPos[ 2 ].y ;
				DrawVert[ 3 ].pos.x = DrawPos[ 3 ].x ;
				DrawVert[ 3 ].pos.y = DrawPos[ 3 ].y ;
				DrawVert[ 4 ].pos.x = DrawPos[ 2 ].x ;
				DrawVert[ 4 ].pos.y = DrawPos[ 2 ].y ;
				DrawVert[ 5 ].pos.x = DrawPos[ 1 ].x ;
				DrawVert[ 5 ].pos.y = DrawPos[ 1 ].y ;

				DrawVert[ 0 ].u = TexVert[ 0 ].u ;
				DrawVert[ 0 ].v = TexVert[ 0 ].v ;
				DrawVert[ 1 ].u = TexVert[ 1 ].u ;
				DrawVert[ 1 ].v = TexVert[ 1 ].v ;
				DrawVert[ 2 ].u = TexVert[ 2 ].u ;
				DrawVert[ 2 ].v = TexVert[ 2 ].v ;
				DrawVert[ 3 ].u = TexVert[ 3 ].u ;
				DrawVert[ 3 ].v = TexVert[ 3 ].v ;
				DrawVert[ 4 ].u = TexVert[ 2 ].u ;
				DrawVert[ 4 ].v = TexVert[ 2 ].v ;
				DrawVert[ 5 ].u = TexVert[ 1 ].u ;
				DrawVert[ 5 ].v = TexVert[ 1 ].v ;
			}

			*((DWORD *)&DrawVert[0].pos.z) = drawz ; 
			*((DWORD *)&DrawVert[1].pos.z) = drawz ; 
			*((DWORD *)&DrawVert[2].pos.z) = drawz ; 
			*((DWORD *)&DrawVert[3].pos.z) = drawz ;
			*((DWORD *)&DrawVert[4].pos.z) = drawz ;
			*((DWORD *)&DrawVert[5].pos.z) = drawz ;

			DrawVert[0].rhw = 1.0f ;
			DrawVert[1].rhw = 1.0f ;
			DrawVert[2].rhw = 1.0f ;
			DrawVert[3].rhw = 1.0f ;
			DrawVert[4].rhw = 1.0f ;
			DrawVert[5].rhw = 1.0f ;

			ADD4VERTEX_TEX

			i ++ ;
			if( i >= DrawTexNum ) break ;

			// �`�悷��e�N�X�`���[�̃Z�b�g
			DrawTex ++ ;
			Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
			Graphics_Android_DeviceState_NormalDrawSetup() ;
		}
		break ;
	}

	// �I��
	return 0 ;
}

// �Q�����z��I�ɔz�u���ꂽ���_�f�[�^�𒸓_�o�b�t�@�ɒǉ�����
static int ANDROID_Graphics_SetPlaneVertexHardware( VERTEX_2D *GraphVert, int xnum, int ynum )
{
	int i, j, k, l ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( xnum < 2 || ynum < 2 ) return -1 ;

	// �g���C�A���O�����X�g���[�h�̏ꍇ�̓o�b�t�@�͎g�p���Ȃ�
	DRAWSTOCKINFO

	// �o�b�t�@���g�p���Ȃ��ݒ�ɂȂ��Ă����炱�̏�ŕ`��
	{
#define MAX_POSNUM		1000
		WORD list[MAX_POSNUM] ;

		// ���_�C���f�b�N�X���X�g���쐬����
		k = 0 ;
		l = 0 ;
		for( i = 0 ; i < ynum - 1 ; i ++ )
		{
			// ���_��������������������`��
			if( k + xnum * 2 + 2 > MAX_POSNUM )
			{
				// Uniform �̍X�V
				Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

				// ���_�f�[�^�̃Z�b�g�A�b�v
				Graphics_Android_DeviceState_SetupShaderVertexData(
					GANDR.Device.State.SetShader,
					&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_2D ].InputInfo,
					GraphVert
				) ;

				// �`��
				glDrawElements( GL_TRIANGLE_STRIP, k, GL_UNSIGNED_SHORT, list );
				GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;
					
				k = 0 ;
			}

			// �O�̍s����̑����������ꍇ�̓X�g���b�v�̘A���p�̒��_���o��		
			if( k != 0 )
			{
				list[k] = ( WORD )( l + xnum ) ;
				k ++ ;
			}
			
			for( j = 0 ; j < xnum ; j ++, l ++ )
			{
				list[k] = ( WORD )( l + xnum ) ;
				list[k+1] = ( WORD )l ;
				k += 2 ;
			}
			if( i != ynum - 2 )
			{
				list[k] = list[k-1] ;
				k ++ ;
			}
		}
		if( k != 0 )
		{
			// Uniform �̍X�V
			Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

			// ���_�f�[�^�̃Z�b�g�A�b�v
			Graphics_Android_DeviceState_SetupShaderVertexData(
				GANDR.Device.State.SetShader,
				&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_2D ].InputInfo,
				GraphVert
			) ;

			// �`��
			glDrawElements( GL_TRIANGLE_STRIP, k, GL_UNSIGNED_SHORT, list );
			GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;
		}
#undef	MAX_POSNUM
	}

	// �I��
	return 0 ;
}

// �e�N�X�`����ό`���ĕ`�悷��
extern	void	Graphics_Android_DrawModiTex( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, IMAGEDATA_HARD_DRAW *DrawTex, bool SimpleDrawFlag )
{
	IMAGEDATA_HARD_VERT *TexVert ;
	VERTEX_2D *vec ; 
	float xx1, yy1, xx2, yy2, xx3, yy3, xx4, yy4/*, r1, r2, r3, r4*/ ;
//	float xtmp1, ytmp1, xtmp2, ytmp2 ;
	int c/*, f1, f2*/ ;
	DWORD DiffuseColor ;
	float Reverse0, Reverse1;
	DWORD drawz ;
	float u[ 2 ] ;
	float v[ 2 ] ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return ;
	}

	// �`�悷��e�N�X�`���[�̃Z�b�g
	Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
	if( GANDR.Device.DrawSetting.ChangeTextureFlag )
	{
		Graphics_Android_DeviceState_NormalDrawSetup() ;
	}

	// ���_�f�[�^���擾�i���̂Ƃ���F���̃Z�b�g�̂݁j
	DiffuseColor = GANDR.Device.DrawInfo.DiffuseColor ;

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	TexVert = DrawTex->Vertex ;

	// ���]����p����
	Reverse0 =  ( x2 - x1 ) * ( y3 - y1 ) - ( x3 - x1 ) * ( y2 - y1 ) ;
	Reverse1 = -( x2 - x4 ) * ( y3 - y4 ) + ( y2 - y4 ) * ( x3 - x4 ) ;

	if( SimpleDrawFlag ) goto R1 ;

	// ���s�l�ӌ`�ȏ�̕ό`���N���Ă��Ȃ������畁�ʂ̏��������s
//	f1 = f2 = 0 ;
	c = 0 ;
	xx1 = x2 - x1 ; xx2 = x4 - x3 ;
	yy1 = y2 - y1 ; yy2 = y4 - y3 ;

	xx3 = x3 - x1 ; xx4 = x4 - x2 ;
	yy3 = y3 - y1 ; yy4 = y4 - y2 ;

	if( _FABS( xx1 - xx2 ) < 1.0F && _FABS( yy1 - yy2 ) < 1.0F ) c ++/*, f1 = 1*/ ;
	if( _FABS( xx3 - xx4 ) < 1.0F && _FABS( yy3 - yy4 ) < 1.0F ) c ++/*, f2 = 1*/ ;
	if( c == 2 ) goto R1 ;

/*
	// ��`�����S�Ȏ��R�l�p�`���𔻒�
	f1 = f2 = c = 0 ;
	r1 = _SQRT( xx1 * xx1 + yy1 * yy1 ) ;	xtmp1 = xx1 / r1 ;	ytmp1 = yy1 / r1 ;
	r2 = _SQRT( xx2 * xx2 + yy2 * yy2 ) ;	xtmp2 = xx2 / r2 ;	ytmp2 = yy2 / r2 ;
	if( _FABS( xtmp1 - xtmp2 ) < 0.001F && _FABS( ytmp1 - ytmp2 ) < 0.001F ) c ++, f1 = 1 ;
	
	r3 = _SQRT( xx3 * xx3 + yy3 * yy3 ) ;	xtmp1 = xx3 / r3 ;	ytmp1 = yy3 / r3 ;
	r4 = _SQRT( xx4 * xx4 + yy4 * yy4 ) ;	xtmp2 = xx4 / r4 ;	ytmp2 = yy4 / r4 ;
	if( _FABS( xtmp1 - xtmp2 ) < 0.001F && _FABS( ytmp1 - ytmp2 ) < 0.001F ) c ++, f2 = 1 ;
*/

	{
#define TDIVNUM		5
#define TDN			(1 + ( 1 << TDIVNUM ))
#define ADJUSTUV	(0.001f)
		int DivNum, tdn ;
		static VERTEX_2D VectData2[TDN * TDN] ;
		VERTEX_2D *v ;
		float xxx1, yyy1, xxx2, yyy2, xxx3, yyy3 ;
		float adx1, ady1, adx2, ady2, adx3, ady3, adtu, adtv, tu, tv ; 
		int i, j ;
		float adjust_u_l, adjust_u_r, adjust_v_t, adjust_v_b ;

		// �����摜�̏ꍇ�ׂ̉摜�̃s�N�Z��������Ȃ����߂̕␳�t�u�l���쐬����
		{
			if( TexVert[ 0 ].u < 0.000001f )
			{
				adjust_u_l = 0.0f ;
			}
			else
			{
				adjust_u_l =  ( TexVert[ 3 ].u - TexVert[ 0 ].u ) / ( TexVert[ 3 ].x - TexVert[ 0 ].x ) * ADJUSTUV ;
			}

			if( TexVert[ 3 ].u > 0.99999f )
			{
				adjust_u_r = 0.0f ;
			}
			else
			{
				adjust_u_r = -( TexVert[ 3 ].u - TexVert[ 0 ].u ) / ( TexVert[ 3 ].x - TexVert[ 0 ].x ) * ADJUSTUV ;
			}

			if( TexVert[ 0 ].v < 0.000001f )
			{
				adjust_v_t = 0.0f ;
			}
			else
			{
				adjust_v_t =  ( TexVert[ 3 ].v - TexVert[ 0 ].v ) / ( TexVert[ 3 ].y - TexVert[ 0 ].y ) * ADJUSTUV ;
			}

			if( TexVert[ 3 ].v > 0.99999f )
			{
				adjust_v_b = 0.0f ;
			}
			else
			{
				adjust_v_b = -( TexVert[ 3 ].v - TexVert[ 0 ].v ) / ( TexVert[ 3 ].y - TexVert[ 0 ].y ) * ADJUSTUV ;
			}
		}

		// �������̎Z�o
		{
			float v1x, v1y, v2x, v2y ;
			float rate ;
			const float Table[] = { 2.0F, 1.0F, 0.6F, 0.1F, 0.05F } ;

			v1x = x4 - x1 ;		v1y = y4 - y1 ;
			v2x = x3 - x2 ;		v2y = y3 - y2 ;
			rate = (float)( 
				( _SQRT( v1x * v1x + v1y * v1y ) + _SQRT( v2x * v2x + v2y * v2y ) ) /
				( ( _SQRT( (float)( GSYS.DrawSetting.DrawSizeX * GSYS.DrawSetting.DrawSizeX + 
						GSYS.DrawSetting.DrawSizeY * GSYS.DrawSetting.DrawSizeY ) ) * 2 ) ) ) ;
			tdn = 8 ;
			if( tdn < 8 ) tdn = 8 ;
			else if( tdn > TDN ) tdn = TDN ;
			for( DivNum = TDIVNUM ; DivNum > 0 && rate < Table[TDIVNUM - DivNum] ; DivNum -- ){}
		}

		// ���R�l�p�`����
		adx1 = xx3 / ( tdn - 1 ) ;	ady1 = yy3 / ( tdn - 1 ) ;
		adx2 = xx4 / ( tdn - 1 ) ;	ady2 = yy4 / ( tdn - 1 ) ;
		xxx1 = x1 ;		yyy1 = y1 ;
		xxx2 = x2 ;		yyy2 = y2 ;
		adtu = ( ( TexVert[3].u + adjust_u_r ) - ( TexVert[0].u + adjust_u_l ) ) / ( tdn - 1 ) ;
		adtv = ( ( TexVert[3].v + adjust_v_b ) - ( TexVert[0].v + adjust_v_t ) ) / ( tdn - 1 ) ;
		tv = TexVert[0].v + adjust_v_t ;
		v = VectData2 ;
		for( i = 0 ; i < tdn ; i ++, tv += adtv,
									 xxx1 += adx1, yyy1 += ady1,
									 xxx2 += adx2, yyy2 += ady2 )
		{
			adx3 = ( xxx2 - xxx1 ) / ( tdn - 1 ) ;
			ady3 = ( yyy2 - yyy1 ) / ( tdn - 1 ) ;

//			xxx3 = xxx1 - 0.5F ;	yyy3 = yyy1 - 0.5F ;
			xxx3 = xxx1 ;
			yyy3 = yyy1 ;
			tu = TexVert[0].u + adjust_u_l ;
			for( j = 0 ; j < tdn ; j ++, tu += adtu,
										 xxx3 += adx3, yyy3 += ady3, v ++ )
			{
				v->pos.x = (float)xxx3 ;
				v->pos.y = (float)yyy3 ;
				*((DWORD *)&v->pos.z) = drawz ;
				v->rhw   = 1.0F ;
				v->u     = (float)tu ;
				v->v     = (float)tv ;
				v->color = DiffuseColor ;
			}
		}

		// ���_�ǉ�����
		ANDROID_Graphics_SetPlaneVertexHardware( VectData2, tdn, tdn ) ;

#undef TDIVNUM
#undef TDN
	}

	return ;
		
R1 :
	// ���ʂɕ`��
	GETVERTEX_QUAD( vec )

	vec[0].color = ( DWORD )DiffuseColor ;
	vec[1].color = ( DWORD )DiffuseColor ;
	vec[2].color = ( DWORD )DiffuseColor ;
	vec[3].color = ( DWORD )DiffuseColor ;
	vec[4].color = ( DWORD )DiffuseColor ;
	vec[5].color = ( DWORD )DiffuseColor ;

	u[ 0 ] = TexVert[0].u + 0.0625f / DrawTex->Tex->TexWidth ;
	u[ 1 ] = TexVert[1].u - 0.0625f / DrawTex->Tex->TexWidth ;
	v[ 0 ] = TexVert[0].v + 0.0625f / DrawTex->Tex->TexHeight ;
	v[ 1 ] = TexVert[2].v - 0.0625f / DrawTex->Tex->TexHeight ;

	if( Reverse0 <= 0  &&  Reverse1 <= 0 )
	{
		vec[0].pos.x = x1 ;	
		vec[0].pos.y = y1 ;
		vec[1].pos.x = x3 ;
		vec[1].pos.y = y3 ;
		vec[2].pos.x = x2 ;	
		vec[2].pos.y = y2 ;
		vec[3].pos.x = x4 ;
		vec[3].pos.y = y4 ;
		vec[4].pos.x = x2 ;	
		vec[4].pos.y = y2 ;
		vec[5].pos.x = x3 ;
		vec[5].pos.y = y3 ;

		vec[0].u = u[ 0 ] ;
		vec[0].v = v[ 0 ] ;
		vec[1].u = u[ 0 ] ;
		vec[1].v = v[ 1 ] ;
		vec[2].u = u[ 1 ] ;
		vec[2].v = v[ 0 ] ;
		vec[3].u = u[ 1 ] ;
		vec[3].v = v[ 1 ] ;
		vec[4].u = u[ 1 ] ;
		vec[4].v = v[ 0 ] ;
		vec[5].u = u[ 0 ] ;
		vec[5].v = v[ 1 ] ;
	}
	else
	{
		vec[0].pos.x = x1 ;	
		vec[0].pos.y = y1 ;
		vec[1].pos.x = x2 ;	
		vec[1].pos.y = y2 ;
		vec[2].pos.x = x3 ;
		vec[2].pos.y = y3 ;
		vec[3].pos.x = x4 ;
		vec[3].pos.y = y4 ;
		vec[4].pos.x = x3 ;
		vec[4].pos.y = y3 ;
		vec[5].pos.x = x2 ;	
		vec[5].pos.y = y2 ;

		vec[0].u = u[ 0 ] ;
		vec[0].v = v[ 0 ] ;
		vec[1].u = u[ 1 ] ;
		vec[1].v = v[ 0 ] ;
		vec[2].u = u[ 0 ] ;
		vec[2].v = v[ 1 ] ;
		vec[3].u = u[ 1 ] ;
		vec[3].v = v[ 1 ] ;
		vec[4].u = u[ 0 ] ;
		vec[4].v = v[ 1 ] ;
		vec[5].u = u[ 1 ] ;
		vec[5].v = v[ 0 ] ;
	}

	*((DWORD *)&vec[0].pos.z) = drawz ;
	*((DWORD *)&vec[1].pos.z) = drawz ;
	*((DWORD *)&vec[2].pos.z) = drawz ;
	*((DWORD *)&vec[3].pos.z) = drawz ;
	*((DWORD *)&vec[4].pos.z) = drawz ;
	*((DWORD *)&vec[5].pos.z) = drawz ;

	vec[0].rhw = 1.0f ;
	vec[1].rhw = 1.0f ;
	vec[2].rhw = 1.0f ;
	vec[3].rhw = 1.0f ;
	vec[4].rhw = 1.0f ;
	vec[5].rhw = 1.0f ;

	ADD4VERTEX_TEX
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawModiGraphF
extern	int		Graphics_Hardware_DrawModiGraphF_PF( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, IMAGEDATA *Image, IMAGEDATA *BlendImage, int TransFlag, bool SimpleDrawFlag )
{
	int Flag ;

	// �����u�����h�e�N�X�`���t�̏ꍇ�͓����������s��Ȃ��`��֐����g�p����
	if( GSYS.DrawSetting.BlendGraph > 0 ) return Graphics_Hardware_DrawModiGraph_PF( _FTOL( x1 ), _FTOL( y1 ), _FTOL( x2 ), _FTOL( y2 ), _FTOL( x3 ), _FTOL( y3 ), _FTOL( x4 ), _FTOL( y4 ), Image, BlendImage, TransFlag, SimpleDrawFlag ) ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��̏���
	Flag = TransFlag ;
	DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )

	// �e�N�X�`���[���P���݂̂̏ꍇ�͏����𕪊�
	if( Image->Hard.DrawNum == 1 )
	{
		// ���̂܂ܕ`��
		Graphics_Android_DrawModiTex( x1, y1, x2, y2, x3, y3, x4, y4, &Image->Hard.Draw[ 0 ], false ) ;
	}
	else
	{
		IMAGEDATA_HARD_DRAW *DrawTex ;
		IMAGEDATA_HARD_VERT *TexVert ;
		int DrawTexNum ;
		int i, j ;
		double /*xx1, yy1, xx2, yy2,*/ xx3, yy3, xx4, yy4, xt1, yt1, xt2, yt2 ;
		double w, h, r ;
		float x[4], y[4], *xp, *yp ;

//		xx1 = x2 - x1 ; xx2 = x4 - x3 ;
//		yy1 = y2 - y1 ; yy2 = y4 - y3 ;

		xx3 = x3 - x1 ; xx4 = x4 - x2 ;
		yy3 = y3 - y1 ; yy4 = y4 - y2 ;
		
//		w = 1.0F / (float)Image->Width ;
//		h = 1.0F / (float)Image->Height ;
		w = 1.0F / (double)Image->WidthF ;
		h = 1.0F / (double)Image->HeightF ;

		// �`����̐����Z�b�g
		DrawTexNum = Image->Hard.DrawNum ;

		// �`����z��̃A�h���X���Z�b�g���Ă���
		DrawTex = Image->Hard.Draw ;

		// �e�N�X�`���[�̐������J��Ԃ�
		for( i = 0 ; i < DrawTexNum ; i ++, DrawTex ++ )
		{
			// �e�N�X�`���[�̃f�[�^�A�h���X���擾
			TexVert = DrawTex->Vertex ;

			// ���W���Z�o
			xp = x ;
			yp = y ;
			for( j = 0 ; j < 4 ; j ++, TexVert ++ )
			{
				r = TexVert->y * h ;
				xt1 = x1 + xx3 * r ;	yt1 = y1 + yy3 * r ;
				xt2 = x2 + xx4 * r ;	yt2 = y2 + yy4 * r ;

				r = TexVert->x * w ;
				*xp++ = (float)( ( xt2 - xt1 ) * r + xt1 ) ;
				*yp++ = (float)( ( yt2 - yt1 ) * r + yt1 ) ;
			}

			// �`��
			Graphics_Android_DrawModiTex( x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3], DrawTex, false ) ;
		}
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawSimpleQuadrangleGraphF
extern	int		Graphics_Hardware_DrawSimpleQuadrangleGraphF_PF( const GRAPHICS_DRAW_DRAWSIMPLEQUADRANGLEGRAPHF_PARAM *Param, IMAGEDATA *Image, IMAGEDATA *BlendImage )
{
	VERTEX_2D *DrawVert ;
	VERTEX_BLENDTEX_2D *DrawVertB ;
	DWORD DiffuseColor ;
	IMAGEDATA_HARD_DRAW *DrawTex ;
	IMAGEDATA_HARD_DRAW *BlendDrawTex = NULL ;
	IMAGEDATA_HARD_VERT *TexVert ;
	IMAGEDATA_HARD_VERT *BlendTexVert ;
	DWORD drawz ;
	int Flag ;
	float u[ 4 ] ;
	float v[ 4 ] ;
	int i ;
	const GRAPHICS_DRAW_DRAWSIMPLEANGLEGRAPHF_VERTEX *ParamV ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �e�N�X�`���̐����P�ȊO�̏ꍇ�̓G���[
	if( Image->Hard.DrawNum != 1 )
	{
		return -1 ;
	}

	// �`��̏���
	Flag = Param->TransFlag ;
	DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )

	// ���_�f�[�^���擾�i���̂Ƃ���F���̃Z�b�g�̂݁j
	DiffuseColor = GANDR.Device.DrawInfo.DiffuseColor ;

	// �`����z��̃A�h���X���Z�b�g���Ă���
	DrawTex = Image->Hard.Draw ;
	if( BlendImage != NULL )
	{
		BlendDrawTex = BlendImage->Hard.Draw ;
	}

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// ���_�^�C�v�ɂ���ď����𕪊�
	switch( GANDR.Device.DrawInfo.VertexType )
	{
	case VERTEXTYPE_BLENDTEX :	// �u�����h�e�N�X�`�����g�p����
		// �`�悷��e�N�X�`���[�̃Z�b�g
		Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
		Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

		if( GANDR.Device.DrawSetting.ChangeTextureFlag )
		{
			Graphics_Android_DeviceState_NormalDrawSetup() ;
		}

		TexVert = DrawTex->Vertex ;
		BlendTexVert = BlendDrawTex->Vertex ;

		// ���_�f�[�^������������
		ParamV = Param->Vertex ;
		for( i = 0 ; i < Param->QuadrangleNum ; i ++, ParamV += 4 )
		{
			GETVERTEX_QUAD( DrawVertB )

			DrawVertB[0].color = ( DWORD )DiffuseColor ;
			DrawVertB[1].color = ( DWORD )DiffuseColor ;
			DrawVertB[2].color = ( DWORD )DiffuseColor ;
			DrawVertB[3].color = ( DWORD )DiffuseColor ;
			DrawVertB[4].color = ( DWORD )DiffuseColor ;
			DrawVertB[5].color = ( DWORD )DiffuseColor ;

			DrawVertB[0].pos.x = ParamV[ 0 ].x ;
			DrawVertB[0].pos.y = ParamV[ 0 ].y ;
			DrawVertB[1].pos.x = ParamV[ 1 ].x ;
			DrawVertB[1].pos.y = ParamV[ 1 ].y ;
			DrawVertB[2].pos.x = ParamV[ 2 ].x ;
			DrawVertB[2].pos.y = ParamV[ 2 ].y ;
			DrawVertB[3].pos.x = ParamV[ 3 ].x ;
			DrawVertB[3].pos.y = ParamV[ 3 ].y ;
			DrawVertB[4].pos.x = ParamV[ 2 ].x ;
			DrawVertB[4].pos.y = ParamV[ 2 ].y ;
			DrawVertB[5].pos.x = ParamV[ 1 ].x ;
			DrawVertB[5].pos.y = ParamV[ 1 ].y ;

			switch( GSYS.DrawSetting.BlendGraphPosMode )
			{
			default :
			case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
				u[ 0 ] = ( TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 0 ] = ( TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				u[ 1 ] = ( TexVert[1].x - BlendTexVert[1].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 1 ] = ( TexVert[1].y - BlendTexVert[1].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				u[ 2 ] = ( TexVert[2].x - BlendTexVert[2].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 2 ] = ( TexVert[2].y - BlendTexVert[2].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				u[ 3 ] = ( TexVert[3].x - BlendTexVert[3].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 3 ] = ( TexVert[3].y - BlendTexVert[3].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				break ;

			case DX_BLENDGRAPH_POSMODE_SCREEN :
				u[ 0 ] = ( ParamV[0].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 0 ] = ( ParamV[0].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				u[ 1 ] = ( ParamV[1].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 1 ] = ( ParamV[1].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				u[ 2 ] = ( ParamV[2].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 2 ] = ( ParamV[2].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				u[ 3 ] = ( ParamV[3].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 3 ] = ( ParamV[3].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				break ;
			}

			DrawVertB[0].u1 = u[ 0 ] ;
			DrawVertB[0].v1 = v[ 0 ] ;
			DrawVertB[1].u1 = u[ 1 ] ;
			DrawVertB[1].v1 = v[ 1 ] ;
			DrawVertB[2].u1 = u[ 2 ] ;
			DrawVertB[2].v1 = v[ 2 ] ;
			DrawVertB[3].u1 = u[ 3 ] ;
			DrawVertB[3].v1 = v[ 3 ] ;
			DrawVertB[4].u1 = u[ 2 ] ;
			DrawVertB[4].v1 = v[ 2 ] ;
			DrawVertB[5].u1 = u[ 1 ] ;
			DrawVertB[5].v1 = v[ 1 ] ;

			DrawVertB[0].u2 = ParamV[ 0 ].u ;
			DrawVertB[0].v2 = ParamV[ 0 ].v ;
			DrawVertB[1].u2 = ParamV[ 1 ].u ;
			DrawVertB[1].v2 = ParamV[ 1 ].v ;
			DrawVertB[2].u2 = ParamV[ 2 ].u ;
			DrawVertB[2].v2 = ParamV[ 2 ].v ;
			DrawVertB[3].u2 = ParamV[ 3 ].u ;
			DrawVertB[3].v2 = ParamV[ 3 ].v ;
			DrawVertB[4].u2 = ParamV[ 2 ].u ;
			DrawVertB[4].v2 = ParamV[ 2 ].v ;
			DrawVertB[5].u2 = ParamV[ 1 ].u ;
			DrawVertB[5].v2 = ParamV[ 1 ].v ;

			*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[2].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[3].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[4].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[5].pos.z) = drawz ;

			DrawVertB[0].rhw = 1.0f ;
			DrawVertB[1].rhw = 1.0f ;
			DrawVertB[2].rhw = 1.0f ;
			DrawVertB[3].rhw = 1.0f ;
			DrawVertB[4].rhw = 1.0f ;
			DrawVertB[5].rhw = 1.0f ;

			// �e�N�X�`���[��`�悷��
			ADD4VERTEX_BLENDTEX
		}
		break ;

	case VERTEXTYPE_TEX :	// �u�����h�e�N�X�`�����g�p���Ȃ�
		TexVert = DrawTex->Vertex ;

		// ���_�f�[�^������������
		ParamV = Param->Vertex ;
		for( i = 0 ; i < Param->QuadrangleNum ; i ++, ParamV += 4 )
		{
			GETVERTEX_QUAD( DrawVert )

			DrawVert[0].color = ( DWORD )DiffuseColor ;
			DrawVert[1].color = ( DWORD )DiffuseColor ;
			DrawVert[2].color = ( DWORD )DiffuseColor ;
			DrawVert[3].color = ( DWORD )DiffuseColor ;
			DrawVert[4].color = ( DWORD )DiffuseColor ;
			DrawVert[5].color = ( DWORD )DiffuseColor ;

			DrawVert[0].u = ParamV[ 0 ].u ;
			DrawVert[0].v = ParamV[ 0 ].v ;
			DrawVert[1].u = ParamV[ 1 ].u ;
			DrawVert[1].v = ParamV[ 1 ].v ;
			DrawVert[2].u = ParamV[ 2 ].u ;
			DrawVert[2].v = ParamV[ 2 ].v ;
			DrawVert[3].u = ParamV[ 3 ].u ;
			DrawVert[3].v = ParamV[ 3 ].v ;
			DrawVert[4].u = ParamV[ 2 ].u ;
			DrawVert[4].v = ParamV[ 2 ].v ;
			DrawVert[5].u = ParamV[ 1 ].u ;
			DrawVert[5].v = ParamV[ 1 ].v ;

			DrawVert[0].pos.x = ParamV[ 0 ].x ;
			DrawVert[0].pos.y = ParamV[ 0 ].y ;
			DrawVert[1].pos.x = ParamV[ 1 ].x ;
			DrawVert[1].pos.y = ParamV[ 1 ].y ;
			DrawVert[2].pos.x = ParamV[ 2 ].x ;
			DrawVert[2].pos.y = ParamV[ 2 ].y ;
			DrawVert[3].pos.x = ParamV[ 3 ].x ;
			DrawVert[3].pos.y = ParamV[ 3 ].y ;
			DrawVert[4].pos.x = ParamV[ 2 ].x ;
			DrawVert[4].pos.y = ParamV[ 2 ].y ;
			DrawVert[5].pos.x = ParamV[ 1 ].x ;
			DrawVert[5].pos.y = ParamV[ 1 ].y ;

			*((DWORD *)&DrawVert[0].pos.z) = drawz ;
			*((DWORD *)&DrawVert[1].pos.z) = drawz ;
			*((DWORD *)&DrawVert[2].pos.z) = drawz ;
			*((DWORD *)&DrawVert[3].pos.z) = drawz ;
			*((DWORD *)&DrawVert[4].pos.z) = drawz ;
			*((DWORD *)&DrawVert[5].pos.z) = drawz ;

			DrawVert[0].rhw = 1.0f ;
			DrawVert[1].rhw = 1.0f ;
			DrawVert[2].rhw = 1.0f ;
			DrawVert[3].rhw = 1.0f ;
			DrawVert[4].rhw = 1.0f ;
			DrawVert[5].rhw = 1.0f ;

			// �e�N�X�`���[��`�悷��
			ADD4VERTEX_TEX
		}
		break ;
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawSimpleTriangleGraphF
extern	int		Graphics_Hardware_DrawSimpleTriangleGraphF_PF( const GRAPHICS_DRAW_DRAWSIMPLETRIANGLEGRAPHF_PARAM *Param, IMAGEDATA *Image, IMAGEDATA *BlendImage )
{
	VERTEX_2D *DrawVert ;
	VERTEX_BLENDTEX_2D *DrawVertB ;
	DWORD DiffuseColor ;
	IMAGEDATA_HARD_DRAW *DrawTex ;
	IMAGEDATA_HARD_DRAW *BlendDrawTex = NULL ;
	IMAGEDATA_HARD_VERT *TexVert ;
	IMAGEDATA_HARD_VERT *BlendTexVert ;
	DWORD drawz ;
	int Flag ;
	float u[ 3 ] ;
	float v[ 3 ] ;
	int i ;
	const GRAPHICS_DRAW_DRAWSIMPLEANGLEGRAPHF_VERTEX *ParamV ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �e�N�X�`���̐����P�ȊO�̏ꍇ�̓G���[
	if( Image->Hard.DrawNum != 1 )
	{
		return -1 ;
	}

	// �`��̏���
	Flag = Param->TransFlag ;
	DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )

	// ���_�f�[�^���擾�i���̂Ƃ���F���̃Z�b�g�̂݁j
	DiffuseColor = GANDR.Device.DrawInfo.DiffuseColor ;

	// �`����z��̃A�h���X���Z�b�g���Ă���
	DrawTex = Image->Hard.Draw ;
	if( BlendImage != NULL )
	{
		BlendDrawTex = BlendImage->Hard.Draw ;
	}

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// ���_�^�C�v�ɂ���ď����𕪊�
	switch( GANDR.Device.DrawInfo.VertexType )
	{
	case VERTEXTYPE_BLENDTEX :	// �u�����h�e�N�X�`�����g�p����
		// �`�悷��e�N�X�`���[�̃Z�b�g
		Graphics_Android_DrawSetting_SetTexture( &DrawTex->Tex->PF->Texture ) ;
		Graphics_Android_DrawSetting_SetBlendTexture( &BlendDrawTex->Tex->PF->Texture ) ;

		if( GANDR.Device.DrawSetting.ChangeTextureFlag )
		{
			Graphics_Android_DeviceState_NormalDrawSetup() ;
		}

		TexVert = DrawTex->Vertex ;
		BlendTexVert = BlendDrawTex->Vertex ;

		// ���_�f�[�^������������
		ParamV = Param->Vertex ;
		for( i = 0 ; i < Param->TriangleNum ; i ++, ParamV += 3 )
		{
			GETVERTEX_TRIANGLE( DrawVertB )

			DrawVertB[0].color = ( DWORD )DiffuseColor ;
			DrawVertB[1].color = ( DWORD )DiffuseColor ;
			DrawVertB[2].color = ( DWORD )DiffuseColor ;

			DrawVertB[0].pos.x = ParamV[ 0 ].x ;
			DrawVertB[0].pos.y = ParamV[ 0 ].y ;
			DrawVertB[1].pos.x = ParamV[ 1 ].x ;
			DrawVertB[1].pos.y = ParamV[ 1 ].y ;
			DrawVertB[2].pos.x = ParamV[ 2 ].x ;
			DrawVertB[2].pos.y = ParamV[ 2 ].y ;

			switch( GSYS.DrawSetting.BlendGraphPosMode )
			{
			default :
			case DX_BLENDGRAPH_POSMODE_DRAWGRAPH:
				u[ 0 ] = ( TexVert[0].x - BlendTexVert[0].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 0 ] = ( TexVert[0].y - BlendTexVert[0].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				u[ 1 ] = ( TexVert[1].x - BlendTexVert[1].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 1 ] = ( TexVert[1].y - BlendTexVert[1].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				u[ 2 ] = ( TexVert[2].x - BlendTexVert[2].x + GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 2 ] = ( TexVert[2].y - BlendTexVert[2].y + GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				break ;

			case DX_BLENDGRAPH_POSMODE_SCREEN :
				u[ 0 ] = ( ParamV[0].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 0 ] = ( ParamV[0].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				u[ 1 ] = ( ParamV[1].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 1 ] = ( ParamV[1].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				u[ 2 ] = ( ParamV[2].x - BlendTexVert[0].x - GSYS.DrawSetting.BlendGraphX ) * GANDR.Device.DrawSetting.InvBlendTextureWidth ;
				v[ 2 ] = ( ParamV[2].y - BlendTexVert[0].y - GSYS.DrawSetting.BlendGraphY ) * GANDR.Device.DrawSetting.InvBlendTextureHeight ;
				break ;
			}

			DrawVertB[0].u1 = u[ 0 ] ;
			DrawVertB[0].v1 = v[ 0 ] ;
			DrawVertB[1].u1 = u[ 1 ] ;
			DrawVertB[1].v1 = v[ 1 ] ;
			DrawVertB[2].u1 = u[ 2 ] ;
			DrawVertB[2].v1 = v[ 2 ] ;

			DrawVertB[0].u2 = ParamV[ 0 ].u ;
			DrawVertB[0].v2 = ParamV[ 0 ].v ;
			DrawVertB[1].u2 = ParamV[ 1 ].u ;
			DrawVertB[1].v2 = ParamV[ 1 ].v ;
			DrawVertB[2].u2 = ParamV[ 2 ].u ;
			DrawVertB[2].v2 = ParamV[ 2 ].v ;

			*((DWORD *)&DrawVertB[0].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[1].pos.z) = drawz ;
			*((DWORD *)&DrawVertB[2].pos.z) = drawz ;

			DrawVertB[0].rhw = 1.0f ;
			DrawVertB[1].rhw = 1.0f ;
			DrawVertB[2].rhw = 1.0f ;

			// �e�N�X�`���[��`�悷��
			ADD3VERTEX_BLENDTEX
		}
		break ;

	case VERTEXTYPE_TEX :	// �u�����h�e�N�X�`�����g�p���Ȃ�
		TexVert = DrawTex->Vertex ;

		// ���_�f�[�^������������
		ParamV = Param->Vertex ;
		for( i = 0 ; i < Param->TriangleNum ; i ++, ParamV += 3 )
		{
			GETVERTEX_TRIANGLE( DrawVert )

			DrawVert[0].color = ( DWORD )DiffuseColor ;
			DrawVert[1].color = ( DWORD )DiffuseColor ;
			DrawVert[2].color = ( DWORD )DiffuseColor ;

			DrawVert[0].u = ParamV[ 0 ].u ;
			DrawVert[0].v = ParamV[ 0 ].v ;
			DrawVert[1].u = ParamV[ 1 ].u ;
			DrawVert[1].v = ParamV[ 1 ].v ;
			DrawVert[2].u = ParamV[ 2 ].u ;
			DrawVert[2].v = ParamV[ 2 ].v ;

			DrawVert[0].pos.x = ParamV[ 0 ].x ;
			DrawVert[0].pos.y = ParamV[ 0 ].y ;
			DrawVert[1].pos.x = ParamV[ 1 ].x ;
			DrawVert[1].pos.y = ParamV[ 1 ].y ;
			DrawVert[2].pos.x = ParamV[ 2 ].x ;
			DrawVert[2].pos.y = ParamV[ 2 ].y ;

			*((DWORD *)&DrawVert[0].pos.z) = drawz ;
			*((DWORD *)&DrawVert[1].pos.z) = drawz ;
			*((DWORD *)&DrawVert[2].pos.z) = drawz ;

			DrawVert[0].rhw = 1.0f ;
			DrawVert[1].rhw = 1.0f ;
			DrawVert[2].rhw = 1.0f ;

			// �e�N�X�`���[��`�悷��
			ADD3VERTEX_TEX
		}
		break ;
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawFillBox
extern	int		Graphics_Hardware_DrawFillBox_PF( int x1, int y1, int x2, int y2, unsigned int Color )
{
	VERTEX_NOTEX_2D *vec ;
	RECT drect = { 0 } ;
	int Red, Green, Blue, Flag ;
	DWORD drawz ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// ���]����
	{
		int b ;

		if( x1 > x2 ){ b = x1 ; x1 = x2 ; x2 = b ; }
		if( y1 > y2 ){ b = y1 ; y1 = y2 ; y2 = b ; }
	}
	
	// �N���b�s���O����
	if( GSYS.DrawSetting.Valid2DMatrix == FALSE )
	{
		drect.left   = x1 ;
		drect.right  = x2 ;
		drect.top    = y1 ;
		drect.bottom = y2 ;
		RectClipping_Inline( &drect, &GSYS.DrawSetting.DrawArea ) ;
		if( drect.left == drect.right || drect.top == drect.bottom ) return 0 ;
	}

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag ) ;

	// �F���̑��X�e�[�^�X�̃Z�b�g
	NS_GetColor2( Color, &Red, &Green, &Blue ) ;
	SETUPCOLOR( Color )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// ���_�f�[�^�̃Z�b�g
	GETVERTEX_QUAD( vec )
	
	vec[0].color = Color ;
	vec[1].color = Color ;
	vec[2].color = Color ;
	vec[3].color = Color ;
	vec[4].color = Color ;
	vec[5].color = Color ;
	
	vec[0].pos.x = ( float )drect.left   ;
	vec[0].pos.y = ( float )drect.top    ;
	vec[1].pos.x = ( float )drect.right  ;
	vec[1].pos.y = ( float )drect.top    ;
	vec[2].pos.x = ( float )drect.left   ;
	vec[2].pos.y = ( float )drect.bottom ;
	vec[3].pos.x = ( float )drect.right  ;
	vec[3].pos.y = ( float )drect.bottom ;
	vec[4].pos.x = ( float )drect.left   ;
	vec[4].pos.y = ( float )drect.bottom ;
	vec[5].pos.x = ( float )drect.right  ;
	vec[5].pos.y = ( float )drect.top    ;

	*((DWORD *)&vec[0].pos.z) = drawz ;
	*((DWORD *)&vec[1].pos.z) = drawz ;
	*((DWORD *)&vec[2].pos.z) = drawz ;
	*((DWORD *)&vec[3].pos.z) = drawz ;
	*((DWORD *)&vec[4].pos.z) = drawz ;
	*((DWORD *)&vec[5].pos.z) = drawz ;

	vec[0].rhw = 1.0f ;
	vec[1].rhw = 1.0f ;
	vec[2].rhw = 1.0f ;
	vec[3].rhw = 1.0f ;
	vec[4].rhw = 1.0f ;
	vec[5].rhw = 1.0f ;

	// ���_�f�[�^�̏o��
	ADD4VERTEX_NOTEX

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawLineBox
extern	int		Graphics_Hardware_DrawLineBox_PF( int x1, int y1, int x2, int y2, unsigned int Color )
{
	VERTEX_NOTEX_2D *VertData ;
	int Red, Green, Blue ;
	float fx1, fx2, fy1, fy2 ;
	int Flag;
	DWORD drawz ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag ) ;

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �F���̑��X�e�[�^�X�̃Z�b�g
	NS_GetColor2( Color, &Red, &Green, &Blue ) ;
	SETUPCOLOR( Color )

	// ���]����
	{
		int bx, by ;

		if( x1 > x2 || y1 > y2 )
		{
			bx = x1 ; by = y1 ;
			x1 = x2 ; y1 = y2 ;
			x2 = bx ; y2 = by ;
		}
	}

	fx1 = ( float )x1 ;
	fy1 = ( float )y1 ;
	fx2 = ( float )x2 ;
	fy2 = ( float )y2 ;

	GETVERTEX_LINEBOX( VertData ) ;

	VertData[ 0].color = Color ;
	VertData[ 1].color = Color ;
	VertData[ 2].color = Color ;
	VertData[ 3].color = Color ;
	VertData[ 4].color = Color ;
	VertData[ 5].color = Color ;
	VertData[ 6].color = Color ;
	VertData[ 7].color = Color ;
	VertData[ 8].color = Color ;
	VertData[ 9].color = Color ;
	VertData[10].color = Color ;
	VertData[11].color = Color ;
	VertData[12].color = Color ;
	VertData[13].color = Color ;
	VertData[14].color = Color ;
	VertData[15].color = Color ;
	VertData[16].color = Color ;
	VertData[17].color = Color ;
	VertData[18].color = Color ;
	VertData[19].color = Color ;
	VertData[20].color = Color ;
	VertData[21].color = Color ;
	VertData[22].color = Color ;
	VertData[23].color = Color ;

	*((DWORD *)&VertData[ 0].pos.z) = drawz ;
	*((DWORD *)&VertData[ 1].pos.z) = drawz ;
	*((DWORD *)&VertData[ 2].pos.z) = drawz ;
	*((DWORD *)&VertData[ 3].pos.z) = drawz ;
	*((DWORD *)&VertData[ 4].pos.z) = drawz ;
	*((DWORD *)&VertData[ 5].pos.z) = drawz ;
	*((DWORD *)&VertData[ 6].pos.z) = drawz ;
	*((DWORD *)&VertData[ 7].pos.z) = drawz ;
	*((DWORD *)&VertData[ 8].pos.z) = drawz ;
	*((DWORD *)&VertData[ 9].pos.z) = drawz ;
	*((DWORD *)&VertData[10].pos.z) = drawz ;
	*((DWORD *)&VertData[11].pos.z) = drawz ;
	*((DWORD *)&VertData[12].pos.z) = drawz ;
	*((DWORD *)&VertData[13].pos.z) = drawz ;
	*((DWORD *)&VertData[14].pos.z) = drawz ;
	*((DWORD *)&VertData[15].pos.z) = drawz ;
	*((DWORD *)&VertData[16].pos.z) = drawz ;
	*((DWORD *)&VertData[17].pos.z) = drawz ;
	*((DWORD *)&VertData[18].pos.z) = drawz ;
	*((DWORD *)&VertData[19].pos.z) = drawz ;
	*((DWORD *)&VertData[20].pos.z) = drawz ;
	*((DWORD *)&VertData[21].pos.z) = drawz ;
	*((DWORD *)&VertData[22].pos.z) = drawz ;
	*((DWORD *)&VertData[23].pos.z) = drawz ;

	VertData[ 0].rhw = 1.0f ;
	VertData[ 1].rhw = 1.0f ;
	VertData[ 2].rhw = 1.0f ;
	VertData[ 3].rhw = 1.0f ;
	VertData[ 4].rhw = 1.0f ;
	VertData[ 5].rhw = 1.0f ;
	VertData[ 6].rhw = 1.0f ;
	VertData[ 7].rhw = 1.0f ;
	VertData[ 8].rhw = 1.0f ;
	VertData[ 9].rhw = 1.0f ;
	VertData[10].rhw = 1.0f ;
	VertData[11].rhw = 1.0f ;
	VertData[12].rhw = 1.0f ;
	VertData[13].rhw = 1.0f ;
	VertData[14].rhw = 1.0f ;
	VertData[15].rhw = 1.0f ;
	VertData[16].rhw = 1.0f ;
	VertData[17].rhw = 1.0f ;
	VertData[18].rhw = 1.0f ;
	VertData[19].rhw = 1.0f ;
	VertData[20].rhw = 1.0f ;
	VertData[21].rhw = 1.0f ;
	VertData[22].rhw = 1.0f ;
	VertData[23].rhw = 1.0f ;

	VertData[0].pos.x = fx1			; VertData[0].pos.y = fy1		 ;
	VertData[1].pos.x = fx2			; VertData[1].pos.y = fy1		 ;
	VertData[2].pos.x = fx1			; VertData[2].pos.y = fy1 + 1.0f ;

	VertData[3].pos.x = fx2			; VertData[3].pos.y = fy1 + 1.0f ;
	VertData[4].pos.x = fx1			; VertData[4].pos.y = fy1 + 1.0f ;
	VertData[5].pos.x = fx2			; VertData[5].pos.y = fy1		 ;

	VertData += 6 ;


	VertData[0].pos.x = fx2 - 1.0f	; VertData[0].pos.y = fy1 + 1.0f ;
	VertData[1].pos.x = fx2			; VertData[1].pos.y = fy1 + 1.0f ;
	VertData[2].pos.x = fx2	- 1.0f	; VertData[2].pos.y = fy2		 ;

	VertData[3].pos.x = fx2			; VertData[3].pos.y = fy2		 ;
	VertData[4].pos.x = fx2 - 1.0f	; VertData[4].pos.y = fy2		 ;
	VertData[5].pos.x = fx2			; VertData[5].pos.y = fy1 + 1.0f ;

	VertData += 6 ;


	VertData[0].pos.x = fx1			; VertData[0].pos.y = fy1 + 1.0f ;
	VertData[1].pos.x = fx1 + 1.0f	; VertData[1].pos.y = fy1 + 1.0f ;
	VertData[2].pos.x = fx1			; VertData[2].pos.y = fy2		 ;

	VertData[3].pos.x = fx1 + 1.0f	; VertData[3].pos.y = fy2		 ;
	VertData[4].pos.x = fx1			; VertData[4].pos.y = fy2		 ;
	VertData[5].pos.x = fx1 + 1.0f	; VertData[5].pos.y = fy1 + 1.0f ;

	VertData += 6 ;


	VertData[0].pos.x = fx1 + 1.0f	; VertData[0].pos.y = fy2 - 1.0f ;
	VertData[1].pos.x = fx2 - 1.0f	; VertData[1].pos.y = fy2 - 1.0f ;
	VertData[2].pos.x = fx1 + 1.0f	; VertData[2].pos.y = fy2		 ;

	VertData[3].pos.x = fx2 - 1.0f	; VertData[3].pos.y = fy2		 ;
	VertData[4].pos.x = fx1 + 1.0f	; VertData[4].pos.y = fy2		 ;
	VertData[5].pos.x = fx2 - 1.0f	; VertData[5].pos.y = fy2 - 1.0f ;

	VertData += 6 ;

	// ���_�̒ǉ�
	ADD4VERTEX_LINEBOX

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawLine
extern	int		Graphics_Hardware_DrawLine_PF( int x1, int y1, int x2, int y2, unsigned int Color )
{
	VERTEX_NOTEX_2D *VectData ;
	int Red, Green, Blue, Flag ;
	DWORD drawz ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( x2 - x1 == 0 && y2 - y1 == 0 ) return 0 ; 

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �F���Z�b�g
	GETVERTEX_LINE( VectData ) ;
	NS_GetColor2( Color, &Red, &Green, &Blue ) ;
	SETUPCOLOR( Color )
	VectData[ 0 ].color = Color ;
	VectData[ 1 ].color = Color ;
	*((DWORD *)&VectData[ 0 ].pos.z) = drawz ;
	*((DWORD *)&VectData[ 1 ].pos.z) = drawz ;
	VectData[ 0 ].rhw =
	VectData[ 1 ].rhw = 1.0f ;

	// ���W���Z�b�g
	VectData[ 0 ].pos.x = ( float )( x1 + 0.5f ) ;
	VectData[ 0 ].pos.y = ( float )( y1 + 0.5f ) ;

	VectData[ 1 ].pos.x = ( float )( x2 + 0.5f ) ;
	VectData[ 1 ].pos.y = ( float )( y2 + 0.5f ) ;

	// ���W�̕␳
	if( x1 == x2 )
	{
		if( y1 < y2 )
		{
			VectData[ 0 ].pos.y -= 0.1f ;
			VectData[ 1 ].pos.y -= 0.1f ;
		}
		else
		{
			VectData[ 0 ].pos.y += 0.1f ;
			VectData[ 1 ].pos.y += 0.1f ;
		}
	}

	if( y1 == y2 )
	{
		if( x1 < x2 )
		{
			VectData[ 0 ].pos.x -= 0.1f ;
			VectData[ 1 ].pos.x -= 0.1f ;
		}
		else
		{
			VectData[ 0 ].pos.x += 0.1f ;
			VectData[ 1 ].pos.x += 0.1f ;
		}
	}

	// ���_�̒ǉ�
	ADD4VERTEX_LINE

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawLine3D
extern	int		Graphics_Hardware_DrawLine3D_PF( VECTOR Pos1, VECTOR Pos2, unsigned int Color, int DrawFlag, RECT *DrawArea )
{
	VERTEX_NOTEX_3D *VectData ;
	int Red, Green, Blue, Flag ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( DrawFlag )
	{
		// �`��̏���
		Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB | DX_ANDROID_DRAWPREP_3D | DX_ANDROID_DRAWPREP_FOG ;
		DX_ANDROID_DRAWPREP_NOTEX( Flag )

		GETVERTEX_LINE3D( VectData ) ;

		// �F���Z�b�g
		NS_GetColor2( Color, &Red, &Green, &Blue ) ;
		SETUPCOLOR( Color )
		*( ( DWORD * )&VectData[ 0 ].b ) = Color ;
		*( ( DWORD * )&VectData[ 1 ].b ) = Color ;

		// ���W���Z�b�g
		VectData[ 0 ].pos = Pos1 ;
		VectData[ 1 ].pos = Pos2 ;

		// ���_�̒ǉ�
		ADD4VERTEX_LINE3D
	}
	else
	{
		VERTEX_2D TempVect[ 2 ] ;
		float dleft, dright, dtop, dbottom ;

		dleft   = -100000000.0f ;
		dright  =  100000000.0f ;
		dtop    = -100000000.0f ;
		dbottom =  100000000.0f ;

		// �X�N���[�����W�ɕϊ�
		TempVect[0].pos.x = Pos1.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + Pos1.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + Pos1.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0]  ;
		TempVect[0].pos.y = Pos1.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + Pos1.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + Pos1.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1]  ;
		TempVect[0].pos.z = Pos1.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][2] + Pos1.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][2] + Pos1.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][2] + GSYS.DrawSetting.Blend3DMatrixF.m[3][2]  ;
		TempVect[0].rhw   = Pos1.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][3] + Pos1.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][3] + Pos1.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][3] + GSYS.DrawSetting.Blend3DMatrixF.m[3][3]  ;

		TempVect[1].pos.x = Pos2.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + Pos2.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + Pos2.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0]  ;
		TempVect[1].pos.y = Pos2.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + Pos2.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + Pos2.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1]  ;
		TempVect[1].pos.z = Pos2.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][2] + Pos2.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][2] + Pos2.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][2] + GSYS.DrawSetting.Blend3DMatrixF.m[3][2]  ;
		TempVect[1].rhw   = Pos2.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][3] + Pos2.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][3] + Pos2.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][3] + GSYS.DrawSetting.Blend3DMatrixF.m[3][3]  ;

		TempVect[0].rhw = 1.0F / TempVect[0].rhw ;
		TempVect[0].pos.x *= TempVect[0].rhw ;
		TempVect[0].pos.y *= TempVect[0].rhw ;
		TempVect[0].pos.z *= TempVect[0].rhw ;

		TempVect[1].rhw = 1.0F / TempVect[1].rhw ;
		TempVect[1].pos.x *= TempVect[1].rhw ;
		TempVect[1].pos.y *= TempVect[1].rhw ;
		TempVect[1].pos.z *= TempVect[1].rhw ;

		if( dright  > TempVect[ 0 ].pos.x ) dright  = TempVect[ 0 ].pos.x ;
		if( dright  > TempVect[ 1 ].pos.x ) dright  = TempVect[ 1 ].pos.x ;

		if( dleft   < TempVect[ 0 ].pos.x ) dleft   = TempVect[ 0 ].pos.x ;
		if( dleft   < TempVect[ 1 ].pos.x ) dleft   = TempVect[ 1 ].pos.x ;

		if( dbottom > TempVect[ 0 ].pos.y ) dbottom = TempVect[ 0 ].pos.y ;
		if( dbottom > TempVect[ 1 ].pos.y ) dbottom = TempVect[ 1 ].pos.y ;

		if( dtop    < TempVect[ 0 ].pos.y ) dtop    = TempVect[ 0 ].pos.y ;
		if( dtop    < TempVect[ 1 ].pos.y ) dtop    = TempVect[ 1 ].pos.y ;

		DrawArea->left   = _FTOL( dleft   ) - 1 ;
		DrawArea->right  = _FTOL( dright  ) + 1 ;
		DrawArea->top    = _FTOL( dtop    ) - 1 ;
		DrawArea->bottom = _FTOL( dbottom ) + 1 ;
	}

	// �I��
	return 0 ;
}



#define ANDROID_CIRCLE_VERTEX_NUM			(2000)

#define DX_ANDROID_CIRCLE_THICKNESS											\
	if( x1 < DrawRect.left      ) x1 = DrawRect.left ;						\
	if( x2 > DrawRect.right - 1 ) x2 = DrawRect.right - 1 ;					\
																			\
	VertBuf[ VectNum ].pos.x  = ( float )x1 + 0.1f ;						\
	VertBuf[ VectNum ].pos.y  = y1f + 0.1f ;								\
	VertBuf[ VectNum ].color = Color ;										\
	VertBuf[ VectNum ].rhw   = 1.0f ;										\
	*((DWORD *)&VertBuf[ VectNum ].pos.z) = drawz ;							\
	VectNum ++ ;															\
																			\
	VertBuf[ VectNum ].pos.x =  ( float )( x2 + 1 ) + 0.1f ;				\
	VertBuf[ VectNum ].pos.y =  y1f + 0.1f ;								\
	VertBuf[ VectNum ].color = Color ;										\
	VertBuf[ VectNum ].rhw   = 1.0f ;										\
	*((DWORD *)&VertBuf[ VectNum ].pos.z) = drawz ;							\
	VectNum  ++ ;															\
																			\
	if( VectNum >= ANDROID_CIRCLE_VERTEX_NUM )								\
	{																		\
		/* Uniform �̍X�V */												\
		Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;\
																			\
		/* ���_�f�[�^�̃Z�b�g�A�b�v */										\
		Graphics_Android_DeviceState_SetupShaderVertexData(					\
			GANDR.Device.State.SetShader,									\
			&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D ].InputInfo,\
			VertBuf															\
		) ;																	\
																			\
		/* �`�� */															\
		glDrawArrays( GL_LINES, 0, VectNum );								\
		GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;						\
																			\
		VectNum = 0 ;														\
	}																		

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawCircle( �����w�肠�� )
extern	int		Graphics_Hardware_DrawCircle_Thickness_PF( int x, int y, int r, unsigned int Color, int Thickness )
{
	VERTEX_NOTEX_2D *VertBuf ;
	int VectNum ;
	short ( *CirclePos )[ 5 ] ;
	int Red, Green, Blue, Flag ;
	RECT DrawRect ;
	DWORD drawz ;
	int i ;
//	int j ;
	int x1, x2 ;
	float y1f ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �������Q�ȉ��������牽�������I��
	if( Thickness < 2 )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��p�������̊m��
	if( Graphics_Other_AllocCommonBuffer( 0, sizeof( VERTEX_NOTEX_2D ) * ANDROID_CIRCLE_VERTEX_NUM ) < 0 )
	{
		return -1 ;
	}
	VertBuf = ( VERTEX_NOTEX_2D * )GSYS.Resource.CommonBuffer[ 0 ] ;

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �␳
	DrawRect = GSYS.DrawSetting.DrawArea ;

	NS_GetColor2( Color, &Red, &Green, &Blue ) ;
	SETUPCOLOR( Color )

	// �~�̍��W��������o�b�t�@���擾
	if( Graphics_Other_AllocCommonBuffer( 1, sizeof( short ) * 5 * DrawRect.bottom ) < 0 )
	{
		return -1 ;
	}
	CirclePos = ( short (*)[ 5 ] )GSYS.Resource.CommonBuffer[ 1 ] ;
	_MEMSET( CirclePos, 0, sizeof( short ) * 5 * DrawRect.bottom ) ;

	// �~�̍��W���X�g�쐬
	Graphics_Draw_GetCircle_ThicknessDrawPosition( x, y, r, Thickness, CirclePos ) ;

	// �`�揈��
	VectNum = 0 ;
	for( i = DrawRect.top ; i < DrawRect.bottom ; i ++ )
	{
		if( CirclePos[ i ][ 4 ] == 0 )
		{
			continue ;
		}

		y1f = ( float )i ;

		if( ( CirclePos[ i ][ 4 ] & ( 4 | 8 ) ) == 0 || CirclePos[ i ][ 2 ] >= CirclePos[ i ][ 3 ] )
		{
			x1 = CirclePos[ i ][ 0 ] ;
			x2 = CirclePos[ i ][ 1 ] ;
			DX_ANDROID_CIRCLE_THICKNESS
		}
		else
		{
			x1 = CirclePos[ i ][ 0 ] ;
			x2 = CirclePos[ i ][ 2 ] ;
			DX_ANDROID_CIRCLE_THICKNESS

			x1 = CirclePos[ i ][ 3 ] ;
			x2 = CirclePos[ i ][ 1 ] ;
			DX_ANDROID_CIRCLE_THICKNESS
		}
	}
	if( VectNum )
	{
		// Uniform �̍X�V
		Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

		// ���_�f�[�^�̃Z�b�g�A�b�v
		Graphics_Android_DeviceState_SetupShaderVertexData(
			GANDR.Device.State.SetShader,
			&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D ].InputInfo,
			VertBuf
		) ;	

		// �`��
		glDrawArrays( GL_LINES, 0, VectNum ) ;
		GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawOval( �����w�肠�� )
extern	int		Graphics_Hardware_DrawOval_Thickness_PF( int x, int y, int rx, int ry, unsigned int Color, int Thickness )
{
	VERTEX_NOTEX_2D *VertBuf ;
	int VectNum ;
	short ( *CirclePos )[ 5 ] ;
	int Red, Green, Blue, Flag ;
	RECT DrawRect ;
	DWORD drawz ;
	int i ;
//	int j ;
	int x1, x2 ;
	float y1f ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �������Q�ȉ��������牽�������I��
	if( Thickness < 2 )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��p�������̊m��
	if( Graphics_Other_AllocCommonBuffer( 0, sizeof( VERTEX_NOTEX_2D ) * ANDROID_CIRCLE_VERTEX_NUM ) < 0 )
	{
		return -1 ;
	}
	VertBuf = ( VERTEX_NOTEX_2D * )GSYS.Resource.CommonBuffer[ 0 ] ;

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �␳
	DrawRect = GSYS.DrawSetting.DrawArea ;

	NS_GetColor2( Color, &Red, &Green, &Blue ) ;
	SETUPCOLOR( Color )

	// �~�̍��W��������o�b�t�@���擾
	if( Graphics_Other_AllocCommonBuffer( 1, sizeof( short ) * 5 * DrawRect.bottom ) < 0 )
	{
		return -1 ;
	}
	CirclePos = ( short (*)[ 5 ] )GSYS.Resource.CommonBuffer[ 1 ] ;
	_MEMSET( CirclePos, 0, sizeof( short ) * 5 * DrawRect.bottom ) ;

	// �ȉ~�̍��W���X�g�쐬
	if( Graphics_Draw_GetOval_ThicknessDrawPosition( x, y, rx, ry, Thickness, CirclePos ) < 0 )
	{
		return -1 ;
	}

	// �`�揈��
	VectNum = 0 ;
	for( i = DrawRect.top ; i < DrawRect.bottom ; i ++ )
	{
		if( CirclePos[ i ][ 4 ] == 0 )
		{
			continue ;
		}

		y1f = ( float )i ;

		if( ( CirclePos[ i ][ 4 ] & ( 4 | 8 ) ) == 0 || CirclePos[ i ][ 2 ] >= CirclePos[ i ][ 3 ] )
		{
			x1 = CirclePos[ i ][ 0 ] ;
			x2 = CirclePos[ i ][ 1 ] ;
			DX_ANDROID_CIRCLE_THICKNESS
		}
		else
		{
			x1 = CirclePos[ i ][ 0 ] ;
			x2 = CirclePos[ i ][ 2 ] ;
			DX_ANDROID_CIRCLE_THICKNESS

			x1 = CirclePos[ i ][ 3 ] ;
			x2 = CirclePos[ i ][ 1 ] ;
			DX_ANDROID_CIRCLE_THICKNESS
		}
	}
	if( VectNum )
	{
		// Uniform �̍X�V
		Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

		// ���_�f�[�^�̃Z�b�g�A�b�v
		Graphics_Android_DeviceState_SetupShaderVertexData(
			GANDR.Device.State.SetShader,
			&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D ].InputInfo,
			VertBuf
		) ;	

		// �`��
		glDrawArrays( GL_LINES, 0, VectNum ) ;
		GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;
	}

	// �I��
	return 0 ;
}




#define DX_ANDROID_CIRCLE																	\
			if( !( ( x2 < DrawRect.left ) || ( x1 >= DrawRect.right  ) ||				\
			       ( y1 < DrawRect.top  ) || ( y1 >= DrawRect.bottom ) || LineDrawBuf[ y1 ] ) )		\
			{																			\
				if( x1 < DrawRect.left ) x1 = DrawRect.left ;							\
				if( x2 > DrawRect.right - 1 ) x2 = DrawRect.right - 1 ;					\
																						\
				VertBuf[ VectNum ].pos.x  = ( float )x1 + 0.1f ;						\
				VertBuf[ VectNum ].pos.y  = ( float )y1 + 0.2f ;						\
				VertBuf[ VectNum ].color = Color ;										\
				VertBuf[ VectNum ].rhw   = 1.0f ;										\
				*((DWORD *)&VertBuf[ VectNum ].pos.z) = drawz ;							\
				VectNum ++ ;															\
				LineDrawBuf[y1] = TRUE ;												\
																						\
				VertBuf[ VectNum ].pos.x =  ( float )( x2 + 1 ) + 0.1f ;				\
				VertBuf[ VectNum ].pos.y =  ( float )y1 + 0.2f ;						\
				VertBuf[ VectNum ].color = Color ;										\
				VertBuf[ VectNum ].rhw   = 1.0f ;										\
				*((DWORD *)&VertBuf[ VectNum ].pos.z) = drawz ;							\
				VectNum  ++ ;															\
																						\
				if( VectNum >= ANDROID_CIRCLE_VERTEX_NUM )								\
				{																		\
					/* Uniform �̍X�V */												\
					Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;\
																						\
					/* ���_�f�[�^�̃Z�b�g�A�b�v */										\
					Graphics_Android_DeviceState_SetupShaderVertexData(					\
						GANDR.Device.State.SetShader,									\
						&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D ].InputInfo,\
						VertBuf															\
					) ;																	\
																						\
					/* �`�� */															\
					glDrawArrays( GL_LINES, 0, VectNum );								\
					GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;						\
					VectNum = 0 ;														\
				}																		\
			}

#define DX_ANDROID_CIRCLE_PSET															\
			if( !( ( x1 < DrawRect.left ) || ( x1 >= DrawRect.right  ) ||				\
				   ( y1 < DrawRect.top  ) || ( y1 >= DrawRect.bottom ) ) )				\
			{																			\
				VertBuf[ VectNum ].pos.x  = ( float )x1 + 0.1f ;						\
				VertBuf[ VectNum ].pos.y  = ( float )y1 + 0.1f ;						\
				VertBuf[ VectNum ].color = Color ;										\
				VertBuf[ VectNum ].rhw   = 1.0f ;										\
				*((DWORD *)&VertBuf[ VectNum ].pos.z) = drawz ;							\
				VectNum ++ ;															\
																						\
				if( VectNum >= ANDROID_CIRCLE_VERTEX_NUM )								\
				{																		\
					/* Uniform �̍X�V */												\
					Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;\
																						\
					/* ���_�f�[�^�̃Z�b�g�A�b�v */										\
					Graphics_Android_DeviceState_SetupShaderVertexData(					\
						GANDR.Device.State.SetShader,									\
						&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D ].InputInfo,\
						VertBuf															\
					) ;																	\
																						\
					/* �`�� */															\
					glDrawArrays( GL_POINTS, 0, VectNum );								\
					GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;						\
					VectNum = 0 ;														\
				}																		\
			}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawCircle
extern	int		Graphics_Hardware_DrawCircle_PF( int x, int y, int r, unsigned int Color, int FillFlag, int Rx_One_Minus, int Ry_One_Minus )
{
	VERTEX_NOTEX_2D *VertBuf ;
	int             VectNum ;
	BYTE            *LineDrawBuf ;
	int             Red ;
	int             Green ;
	int             Blue ;
	int             Flag ;
	RECT            DrawRect ;
	DWORD           drawz ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	Rx_One_Minus = Rx_One_Minus ? 1 : 0 ;
	Ry_One_Minus = Ry_One_Minus ? 1 : 0 ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��p�������̊m��
	if( Graphics_Other_AllocCommonBuffer( 0, sizeof( VERTEX_NOTEX_2D ) * ANDROID_CIRCLE_VERTEX_NUM ) < 0 )
	{
		return -1 ;
	}
	VertBuf = ( VERTEX_NOTEX_2D * )GSYS.Resource.CommonBuffer[ 0 ] ;

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �␳
	DrawRect = GSYS.DrawSetting.DrawArea ;

	NS_GetColor2( Color, &Red, &Green, &Blue ) ;
	SETUPCOLOR( Color )

	// �`�揈��
	{
		int Dx, Dy, F/*, i, j*/ ;
		int x1, x2, y1 ;

		// �����l�Z�b�g
		Dx = r ; Dy = 0 ; F = -2 * r + 3 ;
		VectNum = 0 ;

//		j = 0 ;
		// �`��J�n
		if( FillFlag )
		{
			if( Graphics_Other_AllocCommonBuffer( 1, ( DWORD )DrawRect.bottom ) < 0 )
			{
				return DXST_LOGFILE_ADDUTF16LE( "\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x69\x00\x6e\x00\x20\x00\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x48\x00\x61\x00\x72\x00\x64\x00\x77\x00\x61\x00\x72\x00\x65\x00\x5f\x00\x44\x00\x72\x00\x61\x00\x77\x00\x43\x00\x69\x00\x72\x00\x63\x00\x6c\x00\x65\x00\x5f\x00\x50\x00\x46\x00\x00"/*@ L"�������̊m�ۂɎ��s���܂��� in Graphics_Hardware_DrawCircle_PF" @*/ ) ;
			}
			LineDrawBuf = ( BYTE * )GSYS.Resource.CommonBuffer[ 1 ] ;
			_MEMSET( LineDrawBuf, 0, ( size_t )DrawRect.bottom ) ;

			// �ŏ��̃��C����`��
			{
				if( Ry_One_Minus == FALSE )
				{
					x2 = Dx + x - Rx_One_Minus ; x1 = -Dx + x ; y1 = Dy + y ;
					DX_ANDROID_CIRCLE ;
				}

				// ���W�f�[�^��i�߂�
				if( F >= 0 )
				{
					x2 = Dy + x - Rx_One_Minus ; x1 = -Dy + x ; y1 = Dx + y - Ry_One_Minus ;
					DX_ANDROID_CIRCLE ;
					x2 = Dy + x - Rx_One_Minus ; x1 = -Dy + x ; y1 = -Dx + y;
					DX_ANDROID_CIRCLE ;

					Dx -- ;
					F -= 4 * Dx ;
				}	

				Dy ++ ;
				F += 4 * Dy + 2 ;
			}

			while( Dx >= Dy )
			{
				x2 = Dx + x - Rx_One_Minus ; x1 = -Dx + x ; y1 = Dy + y - Ry_One_Minus ;
				DX_ANDROID_CIRCLE ;
				x2 = Dx + x - Rx_One_Minus ; x1 = -Dx + x ; y1 = -Dy + y ;
				DX_ANDROID_CIRCLE ;

				// ���W�f�[�^��i�߂�
				if( F >= 0 )
				{
					x2 = Dy + x - Rx_One_Minus ; x1 = -Dy + x ; y1 = Dx + y - Ry_One_Minus ;
					DX_ANDROID_CIRCLE ;
					x2 = Dy + x - Rx_One_Minus ; x1 = -Dy + x ; y1 = -Dx + y ;
					DX_ANDROID_CIRCLE ;

					Dx -- ;
					F -= 4 * Dx ;
				}

				Dy ++ ;
				F += 4 * Dy + 2 ;
			}
			if( VectNum )
			{
				// Uniform �̍X�V
				Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

				// ���_�f�[�^�̃Z�b�g�A�b�v
				Graphics_Android_DeviceState_SetupShaderVertexData(
					GANDR.Device.State.SetShader,
					&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D ].InputInfo,
					VertBuf
				) ;	

				// �`��
				glDrawArrays( GL_LINES, 0, VectNum ) ;
				GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;
			}
		}
		else
		{
			// �ŏ��̓_��`��
			{
				if( Ry_One_Minus == FALSE )
				{
					x1 = -Dx + x ; y1 = Dy + y ;
					DX_ANDROID_CIRCLE_PSET ;
					x1 = Dx + x - Rx_One_Minus ;  
					DX_ANDROID_CIRCLE_PSET ;
				}

				if( Rx_One_Minus == FALSE )
				{
					x1 = Dy + x ; y1 = Dx + y - Ry_One_Minus ;
					DX_ANDROID_CIRCLE_PSET ;

					x1 = Dy + x ; y1 = -Dx + y;
					DX_ANDROID_CIRCLE_PSET ;
				}

				// ���W�f�[�^��i�߂�
				if( F >= 0 )
				{
					Dx -- ;
					F -= 4 * Dx ;
				}	

				Dy ++ ;
				F += 4 * Dy + 2 ;
			}

			while( Dx >= Dy )
			{
				x1 = -Dx + x ; y1 = Dy + y - Ry_One_Minus ;
				DX_ANDROID_CIRCLE_PSET ;
				x1 = Dx + x - Rx_One_Minus ;  
				DX_ANDROID_CIRCLE_PSET ;

				x1 = Dy + x - Rx_One_Minus ; y1 = Dx + y - Ry_One_Minus ;
				DX_ANDROID_CIRCLE_PSET ;
				x1 = -Dy + x ; 
				DX_ANDROID_CIRCLE_PSET ;
			
				x1 = Dx + x - Rx_One_Minus ; y1 = -Dy + y ;
				DX_ANDROID_CIRCLE_PSET ;
				x1 = -Dx + x ; 
				DX_ANDROID_CIRCLE_PSET ;

				x1 = Dy + x - Rx_One_Minus ; y1 = -Dx + y ;
				DX_ANDROID_CIRCLE_PSET ;
				x1 = -Dy + x ; 
				DX_ANDROID_CIRCLE_PSET ;

				// ���W�f�[�^��i�߂�
				if( F >= 0 )
				{
					Dx -- ;
					F -= 4 * Dx ;
				}

				Dy ++ ;
				F += 4 * Dy + 2 ;
			}
			if( VectNum )
			{
				// Uniform �̍X�V
				Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

				// ���_�f�[�^�̃Z�b�g�A�b�v
				Graphics_Android_DeviceState_SetupShaderVertexData(
					GANDR.Device.State.SetShader,
					&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D ].InputInfo,
					VertBuf
				) ;	

				// �`��
				glDrawArrays( GL_POINTS, 0, VectNum ) ;
				GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;
			}
		}
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawOval
extern	int		Graphics_Hardware_DrawOval_PF( int x, int y, int rx, int ry, unsigned int Color, int FillFlag, int Rx_One_Minus, int Ry_One_Minus )
{
	VERTEX_NOTEX_2D *VertBuf ;
	int VectNum ;
	BYTE *LineDrawBuf ;
//	VERTEX_NOTEX_2D *VectData ;
//	int i, j, r2 ;
//	float xd, x2, y2 ;
//	float d, yd ;
	int Red, Green, Blue, Flag ;
	RECT DrawRect ;
	DWORD drawz ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	Rx_One_Minus = Rx_One_Minus ? 1 : 0 ;
	Ry_One_Minus = Ry_One_Minus ? 1 : 0 ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	if( !rx || !ry ) return -1 ;

	// �`��p�������̊m��
	if( Graphics_Other_AllocCommonBuffer( 0, sizeof( VERTEX_NOTEX_2D ) * ANDROID_CIRCLE_VERTEX_NUM ) < 0 )
	{
		return -1 ;
	}
	VertBuf = ( VERTEX_NOTEX_2D * )GSYS.Resource.CommonBuffer[ 0 ] ;

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �␳
	if( rx < 0 ) rx *= -1 ;
	if( ry < 0 ) ry *= -1 ;
	DrawRect = GSYS.DrawSetting.DrawArea ;

	NS_GetColor2( Color, &Red, &Green, &Blue ) ;
	SETUPCOLOR( Color )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	VectNum = 0 ;

	// �`�揈��
	{
		int Dx, Dy, F, H/*, j, i */ ;
		int x1, x2, y1, Df ;
		int yc, xc, rc, r ;

//		j = 0 ;
		// �`��J�n
		if( FillFlag )
		{
			if( Graphics_Other_AllocCommonBuffer( 1, ( DWORD )DrawRect.bottom ) < 0 )
			{
				return DXST_LOGFILE_ADDUTF16LE( "\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x69\x00\x6e\x00\x20\x00\x47\x00\x5f\x00\x44\x00\x33\x00\x44\x00\x5f\x00\x44\x00\x72\x00\x61\x00\x77\x00\x43\x00\x69\x00\x72\x00\x63\x00\x6c\x00\x65\x00\x00"/*@ L"�������̊m�ۂɎ��s���܂��� in G_D3D_DrawCircle" @*/ ) ;
			}
			LineDrawBuf = ( BYTE * )GSYS.Resource.CommonBuffer[ 1 ] ;
			_MEMSET( LineDrawBuf, 0, ( size_t )DrawRect.bottom ) ;

			if( rx >= ry )
			{
				// �����l���Z�b�g
				rc = ( rx * rx ) / ry ;

				xc = 0 ; yc = 0 ;
				r = rx ;
				Df = 1 ;
		
				Dx = r ;
				Dy = 0;
				F = -2 * r + 1 + 2 * 1;
				H = -4 * r + 2 + 1;

				// �ŏ��̐���`��
				{
					if( Ry_One_Minus == FALSE )
					{
						x1 = -Dx + x ; x2 = Dx + x - Rx_One_Minus ; y1 = Dy + y ;
						DX_ANDROID_CIRCLE ;
					}

					Df = 0 ;

					// ���W�f�[�^��i�߂�
					if( F < 0 )
					{
						yc += ry ;
						if( yc >= rc )
						{
							Dy ++ ;
							yc -= rc ;
							Df = 1 ;
						}
						F += 4 * Dy + 2 ;
						H += 4 * Dy;
					}
					else
					{
						Df = 1 ;

						if( H>=0 )
						{
							Dx--;
							F -= 4 * Dx;
							H -= 4 * Dx - 2 ;
						}
						else
						{
							Dx--;	
							yc += ry ;
							if( yc >= rc )
							{
								Dy ++ ;
								yc -= rc ;
								Df = 1 ;
							}
							F += 4 * Dy - 4 * Dx + 2 ;
							H += 4 * Dy - 4 * Dx + 2 ;
						}
					}
				}

				while( Dx >= 0 )
				{
					if( Df )
					{
						x1 = -Dx + x ; x2 = Dx + x - Rx_One_Minus ; y1 = Dy + y - Ry_One_Minus ;
						DX_ANDROID_CIRCLE ;

						y1 = -Dy + y ;
						DX_ANDROID_CIRCLE ;
					}

					Df = 0 ;

					// ���W�f�[�^��i�߂�
					if( F < 0 )
					{
						yc += ry ;
						if( yc >= rc )
						{
							Dy ++ ;
							yc -= rc ;
							Df = 1 ;
						}
						F += 4 * Dy + 2 ;
						H += 4 * Dy;
					}
					else
					{
						if( H>=0 )
						{
							Dx--;
							F -= 4 * Dx;
							H -= 4 * Dx - 2 ;
						}
						else
						{
							Dx--;	
							yc += ry ;
							if( yc >= rc )
							{
								Dy ++ ;
								yc -= rc ;
								Df = 1 ;
							}
							F += 4 * Dy - 4 * Dx + 2 ;
							H += 4 * Dy - 4 * Dx + 2 ;
						}
					}
				}

				// �Ō�̐���`��
				x1 = -Dx + x ; x2 = Dx + x - Rx_One_Minus ; y1 = -Dy + y;
				DX_ANDROID_CIRCLE ;
			}
			else
			{
				// �����l���Z�b�g
				rc = ( ry * ry ) / rx ;

				yc = 0 ; xc = 0 ;
				r = ry ;
		
				Dy = r ;
				Dx = 0;
				F = -2 * r + 1 + 2 * 1;
				H = -4 * r + 2 + 1;

				// �ŏ��̐���`��
				{
					// ���W�f�[�^��i�߂�
					if( F < 0 )
					{
						xc += rx ;
						if( xc >= rc )
						{
							Dx ++ ;
							xc -= rc ;
						}
						F += 4 * Dx + 2 ;
						H += 4 * Dx;
					}
					else
					{
						if( H>=0 )
						{
							Dy--;
							F -= 4 * Dy;
							H -= 4 * Dy - 2 ;
						}
						else
						{
							Dy--;	
							xc += rx ;
							if( xc >= rc )
							{
								Dx ++ ;
								xc -= rc ;
							}
							F += 4 * Dx - 4 * Dy + 2 ;
							H += 4 * Dx - 4 * Dy + 2 ;
						}
					}
				}

				while( Dy >= 0 )
				{
					// ���W�f�[�^��i�߂�
					if( F < 0 )
					{
						xc += rx ;
						if( xc >= rc )
						{
							Dx ++ ;
							xc -= rc ;
						}
						F += 4 * Dx + 2 ;
						H += 4 * Dx;
					}
					else
					{
						y1 = -Dy + y ; x1 = -Dx + x ; x2 = Dx + x - Rx_One_Minus ;
						DX_ANDROID_CIRCLE ;

						y1 = Dy + y - Ry_One_Minus ;
						DX_ANDROID_CIRCLE ;

						if( H>=0 )
						{
							Dy--;
							F -= 4 * Dy;
							H -= 4 * Dy - 2 ;
						}
						else
						{
							Dy--;	
							xc += rx ;
							if( xc >= rc )
							{
								Dx ++ ;
								xc -= rc ;
							}
							F += 4 * Dx - 4 * Dy + 2 ;
							H += 4 * Dx - 4 * Dy + 2 ;
						}
					}
				}
			}
			if( VectNum )
			{
				// Uniform �̍X�V
				Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

				// ���_�f�[�^�̃Z�b�g�A�b�v
				Graphics_Android_DeviceState_SetupShaderVertexData(
					GANDR.Device.State.SetShader,
					&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D ].InputInfo,
					VertBuf
				) ;	

				// �`��
				glDrawArrays( GL_LINES, 0, VectNum ) ;
				GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;
			}
		}
		else
		{
			if( rx >= ry )
			{
				// �����l���Z�b�g
				rc = ( rx * rx ) / ry ;

				xc = 0 ; yc = 0 ;
				r = rx ;
				Df = 2 ;
		
				Dx = r ;
				Dy = 0;
				F = -2 * r + 1 + 2 * 1;
				H = -4 * r + 2 + 1;

				// �ŏ��̓_��`��
				{
					if( Ry_One_Minus == FALSE )
					{
						x1 = -Dx + x ; y1 = Dy + y ;
						DX_ANDROID_CIRCLE_PSET ;
						x1 = Dx + x - Rx_One_Minus ;  
						DX_ANDROID_CIRCLE_PSET ;
					}

					Df = 0 ;

					// ���W�f�[�^��i�߂�
					if( F < 0 )
					{
						yc += ry ;
						if( yc >= rc )
						{
							Dy ++ ;
							yc -= rc ;
							Df = 1 ;
						}
						F += 4 * Dy + 2 ;
						H += 4 * Dy;
					}
					else
					{
						Df = 1 ;

						if( H>=0 )
						{
							Dx--;
							F -= 4 * Dx;
							H -= 4 * Dx - 2 ;
						}
						else
						{
							Dx--;	
							yc += ry ;
							if( yc >= rc )
							{
								Dy ++ ;
								yc -= rc ;
								Df = 1 ;
							}
							F += 4 * Dy - 4 * Dx + 2 ;
							H += 4 * Dy - 4 * Dx + 2 ;
						}
					}
				}

				while( Dx > 0 )
				{
					if( Df )
					{
						x1 = -Dx + x ; y1 = Dy + y - Ry_One_Minus ;
						DX_ANDROID_CIRCLE_PSET ;
						x1 = Dx + x - Rx_One_Minus ;
						DX_ANDROID_CIRCLE_PSET ;

						x1 = -Dx + x ; y1 = -Dy + y ;
						DX_ANDROID_CIRCLE_PSET ;
						x1 = Dx + x - Rx_One_Minus ;
						DX_ANDROID_CIRCLE_PSET ;
					}

					Df = 0 ;

					// ���W�f�[�^��i�߂�
					if( F < 0 )
					{
						yc += ry ;
						if( yc >= rc )
						{
							Dy ++ ;
							yc -= rc ;
							Df = 1 ;
						}
						F += 4 * Dy + 2 ;
						H += 4 * Dy;
					}
					else
					{
						Df = 1 ;

						if( H>=0 )
						{
							Dx--;
							F -= 4 * Dx;
							H -= 4 * Dx - 2 ;
						}
						else
						{
							Dx--;	
							yc += ry ;
							if( yc >= rc )
							{
								Dy ++ ;
								yc -= rc ;
								Df = 1 ;
							}
							F += 4 * Dy - 4 * Dx + 2 ;
							H += 4 * Dy - 4 * Dx + 2 ;
						}
					}
				}

				// �Ō�̓_��`��
				if( Rx_One_Minus == FALSE )
				{
					x1 = Dx + x ; y1 = -Dy + y ;
					DX_ANDROID_CIRCLE_PSET ;

					x1 = -Dx + x ; y1 = Dy + y - Ry_One_Minus ;
					DX_ANDROID_CIRCLE_PSET ;
				}
			}
			else
			{
				// �����l���Z�b�g
				rc = ( ry * ry ) / rx ;

				xc = 0 ; yc = 0 ;
				r = ry ;
				Df = 1 ;
		
				Dy = r ;
				Dx = 0;
				F = -2 * r + 1 + 2 * 1;
				H = -4 * r + 2 + 1;

				// �ŏ��̓_��`��
				{
					if( Ry_One_Minus == FALSE )
					{
						y1 = -Dy + y ; x1 = Dx + x ;
						DX_ANDROID_CIRCLE_PSET ;
						y1 = Dy + y - Ry_One_Minus ;  
						DX_ANDROID_CIRCLE_PSET ;
					}

					Df = 0 ;

					// ���W�f�[�^��i�߂�
					if( F < 0 )
					{
						xc += rx ;
						if( xc >= rc )
						{
							Dx ++ ;
							xc -= rc ;
							Df = 1 ;
						}
						F += 4 * Dx + 2 ;
						H += 4 * Dx;
					}
					else
					{
						Df = 1 ;

						if( H>=0 )
						{
							Dy--;
							F -= 4 * Dy;
							H -= 4 * Dy - 2 ;
						}
						else
						{
							Dy--;	
							xc += rx ;
							if( xc >= rc )
							{
								Dx ++ ;
								xc -= rc ;
								Df = 1 ;
							}
							F += 4 * Dx - 4 * Dy + 2 ;
							H += 4 * Dx - 4 * Dy + 2 ;
						}
					}
				}

				while( Dy > 0 )
				{
					if( Df )
					{
						y1 = -Dy + y ; x1 = Dx + x - Rx_One_Minus ;
						DX_ANDROID_CIRCLE_PSET ;
						y1 = Dy + y - Ry_One_Minus ;
						DX_ANDROID_CIRCLE_PSET ;

						y1 = -Dy + y ; x1 = -Dx + x ;
						DX_ANDROID_CIRCLE_PSET ;
						y1 = Dy + y - Ry_One_Minus ;
						DX_ANDROID_CIRCLE_PSET ;
					}

					Df = 0 ;

					// ���W�f�[�^��i�߂�
					if( F < 0 )
					{
						xc += rx ;
						if( xc >= rc )
						{
							Dx ++ ;
							xc -= rc ;
							Df = 1 ;
						}
						F += 4 * Dx + 2 ;
						H += 4 * Dx;
					}
					else
					{
						Df = 1 ;

						if( H>=0 )
						{
							Dy--;
							F -= 4 * Dy;
							H -= 4 * Dy - 2 ;
						}
						else
						{
							Dy--;	
							xc += rx ;
							if( xc >= rc )
							{
								Dx ++ ;
								xc -= rc ;
								Df = 1 ;
							}
							F += 4 * Dx - 4 * Dy + 2 ;
							H += 4 * Dx - 4 * Dy + 2 ;
						}
					}
				}

				// �Ō�̓_��`��
				if( Rx_One_Minus == FALSE )
				{
					y1 = Dy + y ; x1 = -Dx + x ;
					DX_ANDROID_CIRCLE_PSET ;

					y1 = -Dy + y ; x1 = Dx + x - Rx_One_Minus ;
					DX_ANDROID_CIRCLE_PSET ;
				}
			}
			if( VectNum )
			{
				// Uniform �̍X�V
				Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

				// ���_�f�[�^�̃Z�b�g�A�b�v
				Graphics_Android_DeviceState_SetupShaderVertexData(
					GANDR.Device.State.SetShader,
					&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_NOTEX_2D ].InputInfo,
					VertBuf
				) ;	

				// �`��
				glDrawArrays( GL_POINTS, 0, VectNum ) ;
				GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;
			}
		}
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawTriangle
extern	int		Graphics_Hardware_DrawTriangle_PF( int x1, int y1, int x2, int y2, int x3, int y3, unsigned int Color, int FillFlag )
{
	VERTEX_NOTEX_2D *vec ; 
	int Red, Green, Blue ;
	int Flag ;
	int sx1, sx2, sy1, sy2 ;
	DWORD drawz ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �F���̑��X�e�[�^�X�̃Z�b�g
	NS_GetColor2( Color, &Red, &Green, &Blue ) ;
	SETUPCOLOR( Color )

	// ���C�����ǂ����ŏ����𕪊�
	if( FillFlag )
	{
		GETVERTEX_TRIANGLE( vec ) ;

		vec[ 0 ].color =
		vec[ 1 ].color =
		vec[ 2 ].color = Color ;

		vec[ 0 ].pos.x = ( float )x1 ; vec[ 0 ].pos.y = ( float )y1 ;

		// �J�����O���L���ɂȂ��Ă���ꍇ�̓J�����O����Ȃ��悤�ɂ���
		switch( GSYS.DrawSetting.CullMode )
		{
		case 0 :	// �J�����O�Ȃ�
			vec[ 1 ].pos.x = ( float )x2 ; vec[ 1 ].pos.y = ( float )y2 ;
			vec[ 2 ].pos.x = ( float )x3 ; vec[ 2 ].pos.y = ( float )y3 ;
			break ;

		case 1 :	// �����J�����O
			sx1 = x2 - x1 ;		sy1 = y2 - y1 ;
			sx2 = x3 - x1 ;		sy2 = y3 - y1 ;
			if( sx1 * sy2 - sy1 * sx2 > 0 )
			{
				vec[ 1 ].pos.x = ( float )x2 ; vec[ 1 ].pos.y = ( float )y2 ;
				vec[ 2 ].pos.x = ( float )x3 ; vec[ 2 ].pos.y = ( float )y3 ;
			}
			else
			{
				vec[ 1 ].pos.x = ( float )x3 ; vec[ 1 ].pos.y = ( float )y3 ;
				vec[ 2 ].pos.x = ( float )x2 ; vec[ 2 ].pos.y = ( float )y2 ;
			}
			break ;

		case 2 :	// �E���J�����O
			sx1 = x2 - x1 ;		sy1 = y2 - y1 ;
			sx2 = x3 - x1 ;		sy2 = y3 - y1 ;
			if( sx1 * sy2 - sy1 * sx2 < 0 )
			{
				vec[ 1 ].pos.x = ( float )x2 ; vec[ 1 ].pos.y = ( float )y2 ;
				vec[ 2 ].pos.x = ( float )x3 ; vec[ 2 ].pos.y = ( float )y3 ;
			}
			else
			{
				vec[ 1 ].pos.x = ( float )x3 ; vec[ 1 ].pos.y = ( float )y3 ;
				vec[ 2 ].pos.x = ( float )x2 ; vec[ 2 ].pos.y = ( float )y2 ;
			}
			break ;
		}

		*( ( DWORD * )&vec[ 0 ].pos.z ) = drawz ;
		*( ( DWORD * )&vec[ 1 ].pos.z ) = drawz ;
		*( ( DWORD * )&vec[ 2 ].pos.z ) = drawz ;

		vec[ 0 ].rhw =
		vec[ 1 ].rhw =
		vec[ 2 ].rhw = 1.0f ;

		ADD3VERTEX_NOTEX
	}
	else
	{
		GETVERTEX_LINETRIANGLE( vec )

		vec[ 0 ].color =
		vec[ 1 ].color =
		vec[ 2 ].color = Color ;

		vec[ 0 ].pos.x = ( float )x1 ; vec[ 0 ].pos.y = ( float )y1 ;
		vec[ 1 ].pos.x = ( float )x2 ; vec[ 1 ].pos.y = ( float )y2 ;
		vec[ 2 ].pos.x = ( float )x3 ; vec[ 2 ].pos.y = ( float )y3 ;
		*( ( DWORD * )&vec[ 0 ].pos.z ) = drawz ;
		*( ( DWORD * )&vec[ 1 ].pos.z ) = drawz ;
		*( ( DWORD * )&vec[ 2 ].pos.z ) = drawz ;

		vec[ 0 ].rhw =
		vec[ 1 ].rhw =
		vec[ 2 ].rhw = 1.0f ;

		ADD4VERTEX_LINETRIANGLE
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawTriangle3D
extern	int		Graphics_Hardware_DrawTriangle3D_PF( VECTOR Pos1, VECTOR Pos2, VECTOR Pos3, unsigned int Color, int FillFlag, int DrawFlag, RECT *DrawArea )
{
	VERTEX_NOTEX_3D *vec ; 
	int Red, Green, Blue ;
	int Flag ;

	if( DrawFlag )
	{
		if( ANDR_CHECKVALID_HARDWARE == FALSE )
		{
			return -1 ;
		}

		// �`��̏���
		Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB | DX_ANDROID_DRAWPREP_3D | DX_ANDROID_DRAWPREP_FOG | DX_ANDROID_DRAWPREP_CULLING ;
		DX_ANDROID_DRAWPREP_NOTEX( Flag )

		// �F���̑��X�e�[�^�X�̃Z�b�g
		NS_GetColor2( Color, &Red, &Green, &Blue ) ;
		SETUPCOLOR( Color )

		// ���C�����ǂ����ŏ����𕪊�
		if( FillFlag )
		{
			GETVERTEX_TRIANGLE3D( vec ) ;

			*( ( DWORD * )&vec[ 0 ].b ) =
			*( ( DWORD * )&vec[ 1 ].b ) =
			*( ( DWORD * )&vec[ 2 ].b ) = ( DWORD )Color ;
			vec[ 0 ].pos = Pos1 ;
			vec[ 1 ].pos = Pos2 ;
			vec[ 2 ].pos = Pos3 ;

			ADD3VERTEX_NOTEX3D
		}
		else
		{
			GETVERTEX_LINETRIANGLE3D( vec )

			*( ( DWORD * )&vec[ 0 ].b ) = ( DWORD )Color ;
			*( ( DWORD * )&vec[ 1 ].b ) = ( DWORD )Color ;
			*( ( DWORD * )&vec[ 2 ].b ) = ( DWORD )Color ;
			*( ( DWORD * )&vec[ 3 ].b ) = ( DWORD )Color ;
			*( ( DWORD * )&vec[ 4 ].b ) = ( DWORD )Color ;
			*( ( DWORD * )&vec[ 5 ].b ) = ( DWORD )Color ;

			vec[ 0 ].pos = Pos1 ;
			vec[ 1 ].pos = Pos2 ;
			vec[ 2 ].pos = Pos2 ;
			vec[ 3 ].pos = Pos3 ;
			vec[ 4 ].pos = Pos3 ;
			vec[ 5 ].pos = Pos1 ;

			ADD4VERTEX_LINETRIANGLE3D
		}
	}
	else
	{
		VERTEX_2D TempVect[ 3 ] ;
		float dleft, dright, dtop, dbottom ;

		dleft   =  100000000.0f ;
		dright  = -100000000.0f ;
		dtop    =  100000000.0f ;
		dbottom = -100000000.0f ;

		// �X�N���[�����W�ɕϊ�
		TempVect[0].pos.x = Pos1.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + Pos1.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + Pos1.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0]  ;
		TempVect[0].pos.y = Pos1.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + Pos1.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + Pos1.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1]  ;
		TempVect[0].pos.z = Pos1.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][2] + Pos1.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][2] + Pos1.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][2] + GSYS.DrawSetting.Blend3DMatrixF.m[3][2]  ;
		TempVect[0].rhw   = Pos1.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][3] + Pos1.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][3] + Pos1.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][3] + GSYS.DrawSetting.Blend3DMatrixF.m[3][3]  ;

		TempVect[1].pos.x = Pos2.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + Pos2.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + Pos2.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0]  ;
		TempVect[1].pos.y = Pos2.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + Pos2.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + Pos2.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1]  ;
		TempVect[1].pos.z = Pos2.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][2] + Pos2.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][2] + Pos2.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][2] + GSYS.DrawSetting.Blend3DMatrixF.m[3][2]  ;
		TempVect[1].rhw   = Pos2.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][3] + Pos2.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][3] + Pos2.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][3] + GSYS.DrawSetting.Blend3DMatrixF.m[3][3]  ;

		TempVect[2].pos.x = Pos3.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + Pos3.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + Pos3.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0]  ;
		TempVect[2].pos.y = Pos3.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + Pos3.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + Pos3.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1]  ;
		TempVect[2].pos.z = Pos3.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][2] + Pos3.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][2] + Pos3.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][2] + GSYS.DrawSetting.Blend3DMatrixF.m[3][2]  ;
		TempVect[2].rhw   = Pos3.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][3] + Pos3.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][3] + Pos3.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][3] + GSYS.DrawSetting.Blend3DMatrixF.m[3][3]  ;

		TempVect[0].rhw = 1.0F / TempVect[0].rhw ;
		TempVect[0].pos.x *= TempVect[0].rhw ;
		TempVect[0].pos.y *= TempVect[0].rhw ;
		TempVect[0].pos.z *= TempVect[0].rhw ;

		TempVect[1].rhw = 1.0F / TempVect[1].rhw ;
		TempVect[1].pos.x *= TempVect[1].rhw ;
		TempVect[1].pos.y *= TempVect[1].rhw ;
		TempVect[1].pos.z *= TempVect[1].rhw ;

		TempVect[2].rhw = 1.0F / TempVect[2].rhw ;
		TempVect[2].pos.x *= TempVect[2].rhw ;
		TempVect[2].pos.y *= TempVect[2].rhw ;
		TempVect[2].pos.z *= TempVect[2].rhw ;

		if( dright  < TempVect[ 0 ].pos.x ) dright  = TempVect[ 0 ].pos.x ;
		if( dright  < TempVect[ 1 ].pos.x ) dright  = TempVect[ 1 ].pos.x ;
		if( dright  < TempVect[ 2 ].pos.x ) dright  = TempVect[ 2 ].pos.x ;

		if( dleft   > TempVect[ 0 ].pos.x ) dleft   = TempVect[ 0 ].pos.x ;
		if( dleft   > TempVect[ 1 ].pos.x ) dleft   = TempVect[ 1 ].pos.x ;
		if( dleft   > TempVect[ 2 ].pos.x ) dleft   = TempVect[ 2 ].pos.x ;

		if( dbottom < TempVect[ 0 ].pos.y ) dbottom = TempVect[ 0 ].pos.y ;
		if( dbottom < TempVect[ 1 ].pos.y ) dbottom = TempVect[ 1 ].pos.y ;
		if( dbottom < TempVect[ 2 ].pos.y ) dbottom = TempVect[ 2 ].pos.y ;

		if( dtop    > TempVect[ 0 ].pos.y ) dtop    = TempVect[ 0 ].pos.y ;
		if( dtop    > TempVect[ 1 ].pos.y ) dtop    = TempVect[ 1 ].pos.y ;
		if( dtop    > TempVect[ 2 ].pos.y ) dtop    = TempVect[ 2 ].pos.y ;

		DrawArea->left   = _FTOL( dleft   ) - 1 ;
		DrawArea->right  = _FTOL( dright  ) + 1 ;
		DrawArea->top    = _FTOL( dtop    ) - 1 ;
		DrawArea->bottom = _FTOL( dbottom ) + 1 ;
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawQuadrangle
extern	int		Graphics_Hardware_DrawQuadrangle_PF( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, unsigned int Color, int FillFlag )
{
	VERTEX_NOTEX_2D *vec ;
	int Red, Green, Blue ;
	int Flag ;
	DWORD drawz ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �F���̑��X�e�[�^�X�̃Z�b�g
	NS_GetColor2( Color, &Red, &Green, &Blue ) ;
	SETUPCOLOR( Color )

	// �h��Ԃ����ǂ����ŏ����𕪊�
	if( FillFlag )
	{
		// �h��Ԃ��̏ꍇ

		// ���_�f�[�^�̃Z�b�g
		GETVERTEX_QUAD( vec )

		vec[ 0 ].color = Color ;
		vec[ 1 ].color = Color ;
		vec[ 2 ].color = Color ;
		vec[ 3 ].color = Color ;
		vec[ 4 ].color = Color ;
		vec[ 5 ].color = Color ;
		
		vec[ 0 ].pos.x = ( float )x1 ; vec[ 0 ].pos.y = ( float )y1 ;
		vec[ 1 ].pos.x = ( float )x2 ; vec[ 1 ].pos.y = ( float )y2 ;
		vec[ 2 ].pos.x = ( float )x4 ; vec[ 2 ].pos.y = ( float )y4 ;
		vec[ 3 ].pos.x = ( float )x3 ; vec[ 3 ].pos.y = ( float )y3 ;
		vec[ 4 ].pos.x = ( float )x4 ; vec[ 4 ].pos.y = ( float )y4 ;
		vec[ 5 ].pos.x = ( float )x2 ; vec[ 5 ].pos.y = ( float )y2 ;

		*((DWORD *)&vec[ 0 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 1 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 2 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 3 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 4 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 5 ].pos.z) = drawz ;

		vec[0].rhw = 1.0f ;
		vec[1].rhw = 1.0f ;
		vec[2].rhw = 1.0f ;
		vec[3].rhw = 1.0f ;
		vec[4].rhw = 1.0f ;
		vec[5].rhw = 1.0f ;

		// ���_�f�[�^�̏o��
		ADD4VERTEX_NOTEX
	}
	else
	{
		// �h��Ԃ��ł͖����ꍇ

		GETVERTEX_LINE( vec ) ;

		vec[ 0 ].color = Color ;
		vec[ 1 ].color = Color ;

		*((DWORD *)&vec[ 0 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 1 ].pos.z) = drawz ;

		vec[ 0 ].rhw =
		vec[ 1 ].rhw = 1.0f ;

		vec[ 0 ].pos.x = ( float )( x1 ) ;
		vec[ 0 ].pos.y = ( float )( y1 ) ;

		vec[ 1 ].pos.x = ( float )( x2 ) ;
		vec[ 1 ].pos.y = ( float )( y2 ) ;

		// ���_�̒ǉ�
		ADD4VERTEX_LINE


		GETVERTEX_LINE( vec ) ;

		vec[ 0 ].color = Color ;
		vec[ 1 ].color = Color ;

		*((DWORD *)&vec[ 0 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 1 ].pos.z) = drawz ;

		vec[ 0 ].rhw =
		vec[ 1 ].rhw = 1.0f ;

		vec[ 0 ].pos.x = ( float )( x2 ) ;
		vec[ 0 ].pos.y = ( float )( y2 ) ;

		vec[ 1 ].pos.x = ( float )( x3 ) ;
		vec[ 1 ].pos.y = ( float )( y3 ) ;

		// ���_�̒ǉ�
		ADD4VERTEX_LINE


		GETVERTEX_LINE( vec ) ;

		vec[ 0 ].color = Color ;
		vec[ 1 ].color = Color ;

		*((DWORD *)&vec[ 0 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 1 ].pos.z) = drawz ;

		vec[ 0 ].rhw =
		vec[ 1 ].rhw = 1.0f ;

		vec[ 0 ].pos.x = ( float )( x3 ) ;
		vec[ 0 ].pos.y = ( float )( y3 ) ;

		vec[ 1 ].pos.x = ( float )( x4 ) ;
		vec[ 1 ].pos.y = ( float )( y4 ) ;

		// ���_�̒ǉ�
		ADD4VERTEX_LINE


		GETVERTEX_LINE( vec ) ;

		vec[ 0 ].color = Color ;
		vec[ 1 ].color = Color ;

		*((DWORD *)&vec[ 0 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 1 ].pos.z) = drawz ;

		vec[ 0 ].rhw =
		vec[ 1 ].rhw = 1.0f ;

		vec[ 0 ].pos.x = ( float )( x4 ) ;
		vec[ 0 ].pos.y = ( float )( y4 ) ;

		vec[ 1 ].pos.x = ( float )( x1 ) ;
		vec[ 1 ].pos.y = ( float )( y1 ) ;

		// ���_�̒ǉ�
		ADD4VERTEX_LINE
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawQuadrangle
extern	int		Graphics_Hardware_DrawQuadrangleF_PF( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, unsigned int Color, int FillFlag )
{
	VERTEX_NOTEX_2D *vec ;
	int Red, Green, Blue ;
	int Flag ;
	DWORD drawz ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �F���̑��X�e�[�^�X�̃Z�b�g
	NS_GetColor2( Color, &Red, &Green, &Blue ) ;
	SETUPCOLOR( Color )

	// �h��Ԃ����ǂ����ŏ����𕪊�
	if( FillFlag )
	{
		// �h��Ԃ��̏ꍇ

		// ���_�f�[�^�̃Z�b�g
		GETVERTEX_QUAD( vec )

		vec[ 0 ].color = Color ;
		vec[ 1 ].color = Color ;
		vec[ 2 ].color = Color ;
		vec[ 3 ].color = Color ;
		vec[ 4 ].color = Color ;
		vec[ 5 ].color = Color ;
		
		vec[ 0 ].pos.x = x1 ; vec[ 0 ].pos.y = y1 ;
		vec[ 1 ].pos.x = x2 ; vec[ 1 ].pos.y = y2 ;
		vec[ 2 ].pos.x = x4 ; vec[ 2 ].pos.y = y4 ;
		vec[ 3 ].pos.x = x3 ; vec[ 3 ].pos.y = y3 ;
		vec[ 4 ].pos.x = x4 ; vec[ 4 ].pos.y = y4 ;
		vec[ 5 ].pos.x = x2 ; vec[ 5 ].pos.y = y2 ;

		*((DWORD *)&vec[ 0 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 1 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 2 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 3 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 4 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 5 ].pos.z) = drawz ;

		vec[0].rhw = 1.0f ;
		vec[1].rhw = 1.0f ;
		vec[2].rhw = 1.0f ;
		vec[3].rhw = 1.0f ;
		vec[4].rhw = 1.0f ;
		vec[5].rhw = 1.0f ;

		// ���_�f�[�^�̏o��
		ADD4VERTEX_NOTEX
	}
	else
	{
		// �h��Ԃ��ł͖����ꍇ

		GETVERTEX_LINE( vec ) ;

		vec[ 0 ].color = Color ;
		vec[ 1 ].color = Color ;

		*((DWORD *)&vec[ 0 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 1 ].pos.z) = drawz ;

		vec[ 0 ].rhw =
		vec[ 1 ].rhw = 1.0f ;

		vec[ 0 ].pos.x = x1 ;
		vec[ 0 ].pos.y = y1 ;

		vec[ 1 ].pos.x = x2 ;
		vec[ 1 ].pos.y = y2 ;

		// ���_�̒ǉ�
		ADD4VERTEX_LINE


		GETVERTEX_LINE( vec ) ;

		vec[ 0 ].color = Color ;
		vec[ 1 ].color = Color ;

		*((DWORD *)&vec[ 0 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 1 ].pos.z) = drawz ;

		vec[ 0 ].rhw =
		vec[ 1 ].rhw = 1.0f ;

		vec[ 0 ].pos.x = x2 ;
		vec[ 0 ].pos.y = y2 ;

		vec[ 1 ].pos.x = x3 ;
		vec[ 1 ].pos.y = y3 ;

		// ���_�̒ǉ�
		ADD4VERTEX_LINE


		GETVERTEX_LINE( vec ) ;

		vec[ 0 ].color = Color ;
		vec[ 1 ].color = Color ;

		*((DWORD *)&vec[ 0 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 1 ].pos.z) = drawz ;

		vec[ 0 ].rhw =
		vec[ 1 ].rhw = 1.0f ;

		vec[ 0 ].pos.x = x3 ;
		vec[ 0 ].pos.y = y3 ;

		vec[ 1 ].pos.x = x4 ;
		vec[ 1 ].pos.y = y4 ;

		// ���_�̒ǉ�
		ADD4VERTEX_LINE


		GETVERTEX_LINE( vec ) ;

		vec[ 0 ].color = Color ;
		vec[ 1 ].color = Color ;

		*((DWORD *)&vec[ 0 ].pos.z) = drawz ;
		*((DWORD *)&vec[ 1 ].pos.z) = drawz ;

		vec[ 0 ].rhw =
		vec[ 1 ].rhw = 1.0f ;

		vec[ 0 ].pos.x = x4 ;
		vec[ 0 ].pos.y = y4 ;

		vec[ 1 ].pos.x = x1 ;
		vec[ 1 ].pos.y = y1 ;

		// ���_�̒ǉ�
		ADD4VERTEX_LINE
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawPixel
extern	int		Graphics_Hardware_DrawPixel_PF( int x, int y, unsigned int Color )
{
	VERTEX_NOTEX_2D *VectData ;
	int Red, Green, Blue, Flag ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �F���̑��X�e�[�^�X�̃Z�b�g
	GETVERTEX_POINT( VectData ) ;

	if( GANDR.Device.DrawInfo.DiffuseColor == 0xffffffff )
	{
		NS_GetColor2( Color, &Red, &Green, &Blue ) ;
		if( GSYS.HardInfo.UseVertexColorBGRAFormat )
		{
			VectData->color = 0xff000000 | ( Red << 16 ) | ( Green << 8 ) | ( Blue ) ;
		}
		else
		{
			VectData->color = 0xff000000 | ( Red ) | ( Green << 8 ) | ( Blue << 16 ) ;
		}
	}
	else
	{
		NS_GetColor2( Color, &Red, &Green, &Blue ) ;
		SETUPCOLOR( VectData->color )
	}

	// ���W�̃Z�b�g
	VectData->pos.x = ( float )x + 0.1f ;
	VectData->pos.y = ( float )y + 0.1f ;
	VectData->pos.z = GSYS.DrawSetting.DrawZ ;
	VectData->rhw   = 1.0f ;

	// ���_�̒ǉ�
	ADD4VERTEX_POINT

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawPixel3D
extern	int		Graphics_Hardware_DrawPixel3D_PF( VECTOR Pos, unsigned int Color, int DrawFlag, RECT *DrawArea )
{
	VERTEX_NOTEX_3D *VectData ; 
	int Red, Green, Blue ;
	int Flag ;

	if( DrawFlag )
	{
		if( ANDR_CHECKVALID_HARDWARE == FALSE )
		{
			return -1 ;
		}

		// �`��̏���
		Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB | DX_ANDROID_DRAWPREP_3D | DX_ANDROID_DRAWPREP_FOG ;
		DX_ANDROID_DRAWPREP_NOTEX( Flag )

		// �F���̑��X�e�[�^�X�̃Z�b�g
		GETVERTEX_POINT3D( VectData ) ;

		NS_GetColor2( Color, &Red, &Green, &Blue ) ;
		if( GANDR.Device.DrawInfo.DiffuseColor == 0xffffffff )
		{
			if( GSYS.HardInfo.UseVertexColorBGRAFormat )
			{
				*( ( DWORD * )&VectData->b ) = 0xff000000 | ( Red << 16 ) | ( Green << 8 ) | ( Blue ) ;
			}
			else
			{
				*( ( DWORD * )&VectData->b ) = 0xff000000 | ( Red ) | ( Green << 8 ) | ( Blue << 16 ) ;
			}
		}
		else
		{
			SETUPCOLOR( *( ( DWORD * )&VectData->b ) )
		}

		// ���W�̃Z�b�g
		VectData->pos = Pos ;

		// ���_�̒ǉ�
		ADD4VERTEX_POINT3D
	}
	else
	{
		VERTEX_2D TempVect ;

		// �X�N���[�����W�ɕϊ�
		TempVect.pos.x = Pos.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][0] + Pos.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][0] + Pos.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][0] + GSYS.DrawSetting.Blend3DMatrixF.m[3][0]  ;
		TempVect.pos.y = Pos.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][1] + Pos.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][1] + Pos.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][1] + GSYS.DrawSetting.Blend3DMatrixF.m[3][1]  ;
		TempVect.pos.z = Pos.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][2] + Pos.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][2] + Pos.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][2] + GSYS.DrawSetting.Blend3DMatrixF.m[3][2]  ;
		TempVect.rhw   = Pos.x * GSYS.DrawSetting.Blend3DMatrixF.m[0][3] + Pos.y * GSYS.DrawSetting.Blend3DMatrixF.m[1][3] + Pos.z * GSYS.DrawSetting.Blend3DMatrixF.m[2][3] + GSYS.DrawSetting.Blend3DMatrixF.m[3][3]  ;

		TempVect.rhw = 1.0F / TempVect.rhw ;
		TempVect.pos.x *= TempVect.rhw ;
		TempVect.pos.y *= TempVect.rhw ;
		TempVect.pos.z *= TempVect.rhw ;

		DrawArea->left   = _FTOL( TempVect.pos.x ) - 1 ;
		DrawArea->right  = _FTOL( TempVect.pos.x ) + 1 ;
		DrawArea->top    = _FTOL( TempVect.pos.y ) - 1 ;
		DrawArea->bottom = _FTOL( TempVect.pos.y ) + 1 ;
	}

	// �I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawPixelSet
extern	int		Graphics_Hardware_DrawPixelSet_PF( const POINTDATA *PointData, int Num )
{
	VERTEX_NOTEX_2D *VectData ;
	int i ;
	COLORDATA ColorData ;
	int MaxRed, MaxGreen, MaxBlue ; 
	unsigned int Color ;
	int Flag ;
	DWORD drawz ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �x�N�g����{�X�e�[�^�X���擾
	ColorData = *( ( COLORDATA * )NS_GetDispColorData() ) ;
	
	MaxRed		= ( 1 << ColorData.RedWidth	  ) - 1 ; 
	MaxGreen	= ( 1 << ColorData.GreenWidth ) - 1 ;
	MaxBlue		= ( 1 << ColorData.BlueWidth  ) - 1 ; 

	for( i = 0 ; i < Num ; i ++, PointData ++ )
	{
		GETVERTEX_POINT( VectData ) ;

		Color = PointData->color ;
		VectData->color = ( PointData->pal << 24 ) |
						( ( ( ( ( ( Color & ColorData.RedMask	) >> ColorData.RedLoc	) << 8 ) - 1 ) / MaxRed		)       ) |
						( ( ( ( ( ( Color & ColorData.GreenMask	) >> ColorData.GreenLoc	) << 8 ) - 1 ) / MaxGreen	) << 8  ) |
						( ( ( ( ( ( Color & ColorData.BlueMask	) >> ColorData.BlueLoc	) << 8 ) - 1 ) / MaxBlue	) << 16 ) ; 

		VectData->pos.x = ( float )PointData->x + 0.1f ;
		VectData->pos.y = ( float )PointData->y + 0.1f ;
		*((DWORD *)&VectData->pos.z) = drawz ;
		VectData->rhw    = 1.0f ;

		// ���_�̒ǉ�
		ADD4VERTEX_POINT
	}

	// �I��
	return 0;
}

// �n�[�h�E�G�A�A�N�Z�����[�^�g�p�� DrawLineSet
extern	int		Graphics_Hardware_DrawLineSet_PF( const LINEDATA *LineData, int Num )
{
	int i ;
	VERTEX_NOTEX_2D *VectData ;
	COLORDATA ColorData ;
	int MaxRed, MaxGreen, MaxBlue ; 
	unsigned int Color ;
	int Flag ;
	DWORD drawz ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Flag = DX_ANDROID_DRAWPREP_DIFFUSERGB ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	// �y�o�b�t�@�ɏ������ނy�l���Z�b�g����
	drawz = *((DWORD *)&GSYS.DrawSetting.DrawZ);

	// �x�N�g����{�X�e�[�^�X���擾
	ColorData = *( ( COLORDATA * )NS_GetDispColorData() ) ;
	
	MaxRed		= ( 1 << ColorData.RedWidth	) - 1 ; 
	MaxGreen	= ( 1 << ColorData.GreenWidth ) - 1 ;
	MaxBlue		= ( 1 << ColorData.BlueWidth ) - 1 ; 

	for( i = 0 ; i < Num ; i ++, LineData ++ )
	{
		GETVERTEX_LINE( VectData ) ;

		Color = LineData->color ;
		VectData->color = ( LineData->pal << 24 ) |
						( ( ( ( ( ( Color & ColorData.RedMask	) >> ColorData.RedLoc	) << 8 ) - 1 ) / MaxRed		)       ) |
						( ( ( ( ( ( Color & ColorData.GreenMask	) >> ColorData.GreenLoc	) << 8 ) - 1 ) / MaxGreen	) << 8  ) |
						( ( ( ( ( ( Color & ColorData.BlueMask	) >> ColorData.BlueLoc	) << 8 ) - 1 ) / MaxBlue	) << 16 ) ; 
		VectData[1].color = VectData[0].color ;
		*((DWORD *)&VectData[0].pos.z) = drawz ;
		*((DWORD *)&VectData[1].pos.z) = drawz ;
		VectData[0].rhw   =
		VectData[1].rhw   = 1.0f ;
 
		// ���W�̃Z�b�g���E�C���h�E���ڕ`�掞�␳
		VectData[0].pos.x = ( float )LineData->x1 ;
		VectData[0].pos.y = ( float )LineData->y1 ;
		VectData[1].pos.x = ( float )LineData->x2 ;
		VectData[1].pos.y = ( float )LineData->y2 ;

		// ���W�̕␳
		if( LineData->x1 == LineData->x2 ) VectData[ 1 ].pos.y += LineData->y2 > LineData->y1 ? -0.1F : 0.1F ;
		if( LineData->y1 == LineData->y2 ) VectData[ 1 ].pos.x += LineData->x2 > LineData->x1 ? -0.1F : 0.1F ;

		// ���_�̒ǉ�
		ADD4VERTEX_LINE
	}

	// �I��
	return 0 ;
}














// DrawPrimitive3D �n�̋��ʂ̏����������s���֐�
__inline int Graphics_Android_DrawPrimitive3DPreparation( int AddFlag, IMAGEDATA *Image, int TransFlag, int TextureNo = 0 )
{
	int Flag ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Flag = TransFlag | DX_ANDROID_DRAWPREP_3D | DX_ANDROID_DRAWPREP_FOG | DX_ANDROID_DRAWPREP_TEXADDRESS | DX_ANDROID_DRAWPREP_CULLING | AddFlag ;
	if( Image )
	{
		DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ TextureNo ].Tex->PF->Texture, Flag )
	}
	else
	{
		int WhiteHandle ;

		WhiteHandle = Graphics_Image_GetWhiteTexHandle() ;
		if( GRAPHCHK( WhiteHandle, Image ) )
		{
			return -1 ;
		}
//		DX_ANDROID_DRAWPREP_NOTEX( Flag )
		DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )
	}

	return 0 ;
}

extern	int		Graphics_Hardware_DrawPrimitive_PF( const VERTEX_3D *Vertex, int VertexNum, int PrimitiveType, IMAGEDATA *Image, int TransFlag )
{
	int i ;
	VERTEX_3D *VertP ;
	unsigned char tmp ;
	int BackupUse3DVertex ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	if( Graphics_Android_DrawPrimitive3DPreparation( 0, Image, TransFlag ) < 0 )
	{
		return -1 ;
	}

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX_3D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->b ;
			VertP->b = VertP->r ;
			VertP->r = tmp ;
		}
	}

	BackupUse3DVertex = GANDR.Device.DrawInfo.Use3DVertex ;
	GANDR.Device.DrawInfo.Use3DVertex = 1 ;
	Graphics_Android_DeviceState_NormalDrawSetup() ;
	GANDR.Device.DrawInfo.Use3DVertex = BackupUse3DVertex ;

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_3D ].InputInfo,
		Vertex
	) ;	

	// �`��
	glDrawArrays( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], 0, VertexNum ) ;
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX_3D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->b ;
			VertP->b = VertP->r ;
			VertP->r = tmp ;
		}
	}

	// �I��
	return 0 ;
}

extern	int		Graphics_Hardware_DrawIndexedPrimitive_PF( const VERTEX_3D *Vertex, int VertexNum, const WORD *Indices, int IndexNum, int PrimitiveType, IMAGEDATA *Image, int TransFlag )
{
	int i ;
	VERTEX_3D *VertP ;
	unsigned char tmp ;
	int BackupUse3DVertex ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	if( Graphics_Android_DrawPrimitive3DPreparation( 0, Image, TransFlag ) < 0 )
	{
		return -1 ;
	}

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX_3D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->b ;
			VertP->b = VertP->r ;
			VertP->r = tmp ;
		}
	}

	BackupUse3DVertex = GANDR.Device.DrawInfo.Use3DVertex ;
	GANDR.Device.DrawInfo.Use3DVertex = 1 ;
	Graphics_Android_DeviceState_NormalDrawSetup() ;
	GANDR.Device.DrawInfo.Use3DVertex = BackupUse3DVertex ;

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_3D ].InputInfo,
		Vertex
	) ;

	// �`��
	glDrawElements( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], IndexNum, GL_UNSIGNED_SHORT, Indices );
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX_3D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->b ;
			VertP->b = VertP->r ;
			VertP->r = tmp ;
		}
	}

	// �I��
	return 0 ;
}

extern	int		Graphics_Hardware_DrawPrimitiveLight_PF( const VERTEX3D *Vertex, int VertexNum, int PrimitiveType, IMAGEDATA *Image, int TransFlag )
{
	int i ;
	VERTEX3D *VertP ;
	unsigned char tmp ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	if( Graphics_Android_DrawPrimitive3DPreparation( DX_ANDROID_DRAWPREP_LIGHTING | DX_ANDROID_DRAWPREP_SPECULAR, Image, TransFlag ) < 0 )
	{
		return -1 ;
	}

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX3D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->dif.b ;
			VertP->dif.b = VertP->dif.r ;
			VertP->dif.r = tmp ;

			tmp = VertP->spc.b ;
			VertP->spc.b = VertP->spc.r ;
			VertP->spc.r = tmp ;
		}
	}

	// �V�F�[�_�[���Z�b�g
	if( Graphics_Android_Shader_Normal3DDraw_Setup() == FALSE )
	{
		return -1 ;
	}

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_3D_LIGHT ].InputInfo,
		Vertex
	) ;	

	// �`��
	glDrawArrays( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], 0, VertexNum ) ;
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX3D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->dif.b ;
			VertP->dif.b = VertP->dif.r ;
			VertP->dif.r = tmp ;

			tmp = VertP->spc.b ;
			VertP->spc.b = VertP->spc.r ;
			VertP->spc.r = tmp ;
		}
	}

	// �I��
	return 0 ;
}

extern	int		Graphics_Hardware_DrawIndexedPrimitiveLight_PF( const VERTEX3D *Vertex, int VertexNum, const WORD *Indices, int IndexNum, int PrimitiveType, IMAGEDATA *Image, int TransFlag )
{
	int i ;
	VERTEX3D *VertP ;
	unsigned char tmp ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	if( Graphics_Android_DrawPrimitive3DPreparation( DX_ANDROID_DRAWPREP_LIGHTING | DX_ANDROID_DRAWPREP_SPECULAR, Image, TransFlag ) < 0 )
	{
		return -1 ;
	}

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX3D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->dif.b ;
			VertP->dif.b = VertP->dif.r ;
			VertP->dif.r = tmp ;

			tmp = VertP->spc.b ;
			VertP->spc.b = VertP->spc.r ;
			VertP->spc.r = tmp ;
		}
	}

	// �V�F�[�_�[���Z�b�g
	if( Graphics_Android_Shader_Normal3DDraw_Setup() == FALSE )
	{
		return -1 ;
	}

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_3D_LIGHT ].InputInfo,
		Vertex
	) ;

	// �`��
	glDrawElements( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], IndexNum, GL_UNSIGNED_SHORT, Indices );
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX3D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->dif.b ;
			VertP->dif.b = VertP->dif.r ;
			VertP->dif.r = tmp ;

			tmp = VertP->spc.b ;
			VertP->spc.b = VertP->spc.r ;
			VertP->spc.r = tmp ;
		}
	}

	// �I��
	return 0 ;
}

extern	int		Graphics_Hardware_DrawPrimitiveLight_UseVertexBuffer_PF( 
	VERTEXBUFFERHANDLEDATA *VertexBuffer,
	int						PrimitiveType,
	int						StartVertex,
	int						UseVertexNum,
	IMAGEDATA *				Image,
	int						TransFlag 
)
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// VERTEX3D�\���̂̂ݑΉ�
	if( VertexBuffer->Type != DX_VERTEX_TYPE_NORMAL_3D )
	{
		return -1 ;
	}

	if( Graphics_Android_DrawPrimitive3DPreparation( DX_ANDROID_DRAWPREP_LIGHTING | DX_ANDROID_DRAWPREP_SPECULAR, Image, TransFlag ) < 0 )
	{
		return -1 ;
	}

	// ���_�V�F�[�_�[���Z�b�g
	if( Graphics_Android_Shader_Normal3DDraw_Setup() == FALSE )
	{
		return -1 ;
	}

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_3D_LIGHT ].InputInfo,
		NULL,
		VertexBuffer->PF->VertexBuffer
	) ;

	// �`��
	glDrawArrays( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], StartVertex, UseVertexNum );
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	// �I��
	return 0 ;
}

extern	int		Graphics_Hardware_DrawIndexedPrimitiveLight_UseVertexBuffer_PF(
	VERTEXBUFFERHANDLEDATA *	VertexBuffer,
	INDEXBUFFERHANDLEDATA *		IndexBuffer,
	int							PrimitiveType,
	int							BaseVertex,
	int							StartVertex,
	int							UseVertexNum,
	int							StartIndex,
	int							UseIndexNum,
	IMAGEDATA *					Image,
	int							TransFlag
)
{
	GLenum IndexFormat ;
//	int    IndexSize ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// ����ł� StartIndex �� 0 �ȊO�̏ꍇ�͕`��ł��Ȃ�
	if( StartIndex != 0 )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// VERTEX3D�\���̂̂ݑΉ�
	if( VertexBuffer->Type != DX_VERTEX_TYPE_NORMAL_3D )
	{
		return -1 ;
	}

	switch( IndexBuffer->Type )
	{
	default :
	case DX_INDEX_TYPE_16BIT :
		IndexFormat = GL_UNSIGNED_SHORT ;
		break ;

	case DX_INDEX_TYPE_32BIT :
		IndexFormat = GL_UNSIGNED_INT ;
		break ;
	}
//	IndexSize = IndexFormat == GL_UNSIGNED_SHORT ? 2 : 4 ;

	if( Graphics_Android_DrawPrimitive3DPreparation( DX_ANDROID_DRAWPREP_LIGHTING | DX_ANDROID_DRAWPREP_SPECULAR, Image, TransFlag ) < 0 )
	{
		return -1 ;
	}

	// ���_�V�F�[�_�[���Z�b�g
	if( Graphics_Android_Shader_Normal3DDraw_Setup() == FALSE )
	{
		return -1 ;
	}


	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_3D_LIGHT ].InputInfo,
		NULL,
		VertexBuffer->PF->VertexBuffer
	) ;

	// �`��
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->PF->IndexBuffer ) ;

	glDrawElements( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], UseIndexNum, IndexFormat, NULL );
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ) ;

	// �I��
	return 0 ;
}

extern	int		Graphics_Hardware_DrawPrimitive2D_PF( VERTEX_2D *Vertex, int VertexNum, int PrimitiveType, IMAGEDATA *Image, int TransFlag, int BillboardFlag, int Is3D, int ReverseXFlag, int ReverseYFlag, int TextureNo, int IsShadowMap )
{
	int Flag ;
	int i ;
	VERTEX_2D *Vert ;
	int SmHandle ;
	SHADOWMAPDATA *ShadowMap ;
	VERTEX_2D *VertP ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	if( BillboardFlag == TRUE )
	{
		Flag = TransFlag | ( Is3D ? DX_ANDROID_DRAWPREP_3D | DX_ANDROID_DRAWPREP_FOG : 0 ) | DX_ANDROID_DRAWPREP_TEXADDRESS ;
	}
	else
	{
		Flag = TransFlag | ( Is3D ? DX_ANDROID_DRAWPREP_3D | DX_ANDROID_DRAWPREP_FOG : 0 ) | DX_ANDROID_DRAWPREP_TEXADDRESS | DX_ANDROID_DRAWPREP_CULLING ;
	}

	if( IsShadowMap )
	{
		SmHandle = ( int )( DWORD_PTR )Image ;
		if( !SHADOWMAPCHKFULL( SmHandle, ShadowMap ) )
		{
			Flag |= DX_ANDROID_DRAWPREP_TEXTURE ;
			Graphics_Android_DrawSetting_SetTexture( &ShadowMap->PF->Texture ) ;

			if( GSYS.ChangeSettingFlag ||
				GANDR.Device.DrawSetting.DrawPrepAlwaysFlag != FALSE ||
				GANDR.Device.DrawSetting.DrawPrepParamFlag != Flag )
			{
				Graphics_Android_DrawPreparation( Flag ) ;
			}
		}
	}
	else
	if( Image )
	{
		DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ TextureNo ].Tex->PF->Texture, Flag )
	}
	else
	{
		DX_ANDROID_DRAWPREP_NOTEX( Flag )
	}

	// �r���{�[�h�̏ꍇ�͂t�u�l���T�[�t�F�X�f�[�^����擾����
	if( BillboardFlag == TRUE )
	{
		float tu1, tv1, tu2, tv2 ;
		int Num ;
		
		Vert = Vertex ;
		Num = VertexNum / 6 ;
		tu1 = Image->Hard.Draw[ 0 ].Vertex[ 0 ].u ;
		tv1 = Image->Hard.Draw[ 0 ].Vertex[ 0 ].v ;
		tu2 = Image->Hard.Draw[ 0 ].Vertex[ 3 ].u ;
		tv2 = Image->Hard.Draw[ 0 ].Vertex[ 3 ].v ;
		for( i = 0 ; i < Num ; i ++, Vert += 6 )
		{
			if( ReverseXFlag )
			{
				Vert[ 0 ].u = tu2 ;
				Vert[ 1 ].u = tu1 ;
				Vert[ 2 ].u = tu2 ;
				Vert[ 3 ].u = tu1 ;
			}
			else
			{
				Vert[ 0 ].u = tu1 ;
				Vert[ 1 ].u = tu2 ;
				Vert[ 2 ].u = tu1 ;
				Vert[ 3 ].u = tu2 ;
			}
			if( ReverseYFlag )
			{
				Vert[ 0 ].v = tv2 ;
				Vert[ 1 ].v = tv2 ;
				Vert[ 2 ].v = tv1 ;
				Vert[ 3 ].v = tv1 ;
			}
			else
			{
				Vert[ 0 ].v = tv1 ;
				Vert[ 1 ].v = tv1 ;
				Vert[ 2 ].v = tv2 ;
				Vert[ 3 ].v = tv2 ;
			}

			Vert[ 4 ].u = Vert[ 2 ].u ;
			Vert[ 4 ].v = Vert[ 2 ].v ;
			Vert[ 5 ].u = Vert[ 1 ].u ;
			Vert[ 5 ].v = Vert[ 1 ].v ;
		}
	}

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX_2D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			VertP->color =	(   VertP->color & 0xff00ff00 ) |
							( ( VertP->color & 0x00ff0000 ) >> 16 ) |
							( ( VertP->color & 0x000000ff ) << 16 ) ;
		}
	}

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_2D ].InputInfo,
		Vertex
	) ;	

	// �`��
	glDrawArrays( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], 0, VertexNum ) ;
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX_2D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			VertP->color =	(   VertP->color & 0xff00ff00 ) |
							( ( VertP->color & 0x00ff0000 ) >> 16 ) |
							( ( VertP->color & 0x000000ff ) << 16 ) ;
		}
	}

	// �I��
	return 0 ;
}

extern	int		Graphics_Hardware_DrawPrimitive2DUser_PF( const VERTEX2D *Vertex, int VertexNum, int PrimitiveType, IMAGEDATA *Image, int TransFlag, int Is3D, int ReverseXFlag, int ReverseYFlag, int TextureNo )
{
	int Flag ;
	int i ;
	VERTEX2D *VertP ;
	unsigned char tmp ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Flag = TransFlag | ( Is3D ? DX_ANDROID_DRAWPREP_3D | DX_ANDROID_DRAWPREP_FOG : 0 ) | DX_ANDROID_DRAWPREP_TEXADDRESS | DX_ANDROID_DRAWPREP_CULLING ;
	if( Image )
	{
		DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ TextureNo ].Tex->PF->Texture, Flag )
	}
	else
	{
		DX_ANDROID_DRAWPREP_NOTEX( Flag )
	}

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX2D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->dif.b ;
			VertP->dif.b = VertP->dif.r ;
			VertP->dif.r = tmp ;
		}
	}

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_2D ].InputInfo,
		Vertex
	) ;	

	// �`��
	glDrawArrays( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], 0, VertexNum ) ;
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX2D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->dif.b ;
			VertP->dif.b = VertP->dif.r ;
			VertP->dif.r = tmp ;
		}
	}

	// �I��
	return 0 ;
}

extern	int		Graphics_Hardware_DrawIndexedPrimitive2DUser_PF( const VERTEX2D *Vertex, int VertexNum, const WORD *Indices, int IndexNum, int PrimitiveType, IMAGEDATA *Image, int TransFlag )
{
	int Flag ;
	int i ;
	VERTEX2D *VertP ;
	unsigned char tmp ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Flag = TransFlag | DX_ANDROID_DRAWPREP_TEXADDRESS | DX_ANDROID_DRAWPREP_CULLING ;
	if( Image )
	{
		DX_ANDROID_DRAWPREP_TEX( Image->Orig, &Image->Hard.Draw[ 0 ].Tex->PF->Texture, Flag )
	}
	else
	{
		DX_ANDROID_DRAWPREP_NOTEX( Flag )
	}

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX2D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->dif.b ;
			VertP->dif.b = VertP->dif.r ;
			VertP->dif.r = tmp ;
		}
	}

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_2D ].InputInfo,
		Vertex
	) ;

	// �`��
	glDrawElements( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], IndexNum, GL_UNSIGNED_SHORT, Indices );
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	if( GSYS.HardInfo.UseVertexColorBGRAFormat == FALSE )
	{
		VertP = ( VERTEX2D * )Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, VertP ++ )
		{
			tmp = VertP->dif.b ;
			VertP->dif.b = VertP->dif.r ;
			VertP->dif.r = tmp ;
		}
	}

	// �I��
	return 0 ;
}












// �V�F�[�_�[�`��p�`��O�Z�b�g�A�b�v�֐�
extern void Graphics_Android_DrawPreparationToShader( int ParamFlag, int Is2D )
{
	int							Flag ;

	// ��{�I�ȃZ�b�g�A�b�v����
	Flag = ParamFlag | DX_ANDROID_DRAWPREP_SPECULAR | DX_ANDROID_DRAWPREP_TEXADDRESS | DX_ANDROID_DRAWPREP_NOBLENDSETTING | DX_ANDROID_DRAWPREP_CULLING | ( Is2D ? 0 : DX_ANDROID_DRAWPREP_3D ) ;
	DX_ANDROID_DRAWPREP_NOTEX( Flag )

	Graphics_Android_DeviceState_SetBlendMode( GSYS.DrawSetting.BlendMode, GANDR.Device.DrawSetting.NotWriteAlphaChannelFlag ) ;
}

// �V�F�[�_�[���g���ĂQ�c�v���~�e�B�u��`�悷��
extern	int		Graphics_Hardware_DrawPrimitive2DToShader_PF(        const VERTEX2DSHADER *Vertex, int VertexNum,                                              int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Graphics_Android_DrawPreparationToShader( 0, TRUE ) ;

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_BLENDTEX_2D ].InputInfo,
		Vertex
	) ;	

	// �`��
	glDrawArrays( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], 0, VertexNum ) ;
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	// �I��
	return 0 ;
}

// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��
extern	int		Graphics_Hardware_DrawPrimitive3DToShader_PF(        const VERTEX3DSHADER *Vertex, int VertexNum,                                              int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Graphics_Android_DrawPreparationToShader( DX_ANDROID_DRAWPREP_LIGHTING | DX_ANDROID_DRAWPREP_FOG, FALSE ) ;

	// �R�c�s����n�[�h�E�G�A�ɔ��f����
	if( GSYS.DrawSetting.MatchHardware3DMatrix == FALSE )
		Graphics_DrawSetting_ApplyLib3DMatrixToHardware() ;


	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_SHADER_3D ].InputInfo,
		Vertex
	) ;	

	// �`��
	glDrawArrays( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], 0, VertexNum ) ;
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	// �I��
	return 0 ;
}

// �V�F�[�_�[���g���ĂQ�c�v���~�e�B�u��`�悷��( ���_�C���f�b�N�X���g�p���� )
extern	int		Graphics_Hardware_DrawPrimitiveIndexed2DToShader_PF( const VERTEX2DSHADER *Vertex, int VertexNum, const unsigned short *Indices, int IndexNum, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Graphics_Android_DrawPreparationToShader( 0, TRUE ) ;

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_BLENDTEX_2D ].InputInfo,
		Vertex
	) ;

	// �`��
	glDrawElements( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], IndexNum, GL_UNSIGNED_SHORT, Indices );
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	// �I��
	return 0 ;
}

// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�C���f�b�N�X���g�p���� )
extern	int		Graphics_Hardware_DrawPrimitiveIndexed3DToShader_PF( const VERTEX3DSHADER *Vertex, int VertexNum, const unsigned short *Indices, int IndexNum, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Graphics_Android_DrawPreparationToShader( DX_ANDROID_DRAWPREP_LIGHTING | DX_ANDROID_DRAWPREP_FOG, FALSE ) ;

	// �R�c�s����n�[�h�E�G�A�ɔ��f����
	if( GSYS.DrawSetting.MatchHardware3DMatrix == FALSE )
		Graphics_DrawSetting_ApplyLib3DMatrixToHardware() ;

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_SHADER_3D ].InputInfo,
		Vertex
	) ;

	// �`��
	glDrawElements( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], IndexNum, GL_UNSIGNED_SHORT, Indices );
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	// �I��
	return 0 ;
}

// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�o�b�t�@�g�p�� )
extern	int		Graphics_Hardware_DrawPrimitive3DToShader_UseVertexBuffer2_PF(
	int VertexBufHandle,
	int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */,
	int StartVertex,
	int UseVertexNum
)
{
	VERTEXBUFFERHANDLEDATA *VertexBuffer ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// �G���[����
	if( VERTEXBUFFERCHK( VertexBufHandle, VertexBuffer ) )
	{
		return -1 ;
	}

	// �V�F�[�_�[�p���_�f�[�^�ł͂Ȃ��ꍇ�̓G���[
	if( VertexBuffer->Type != DX_VERTEX_TYPE_SHADER_3D )
	{
		return -1 ;
	}

	// �R�c�s����n�[�h�E�G�A�ɔ��f����
	if( GSYS.DrawSetting.MatchHardware3DMatrix == FALSE )
		Graphics_DrawSetting_ApplyLib3DMatrixToHardware() ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Graphics_Android_DrawPreparationToShader( DX_ANDROID_DRAWPREP_LIGHTING | DX_ANDROID_DRAWPREP_FOG, FALSE ) ;


	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_SHADER_3D ].InputInfo,
		NULL,
		VertexBuffer->PF->VertexBuffer
	) ;

	// �`��
	glDrawArrays( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], StartVertex, UseVertexNum );
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	// �I��
	return 0 ;
}

// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�g�p�� )
extern	int		Graphics_Hardware_DrawPrimitiveIndexed3DToShader_UseVertexBuffer2_PF(
	int VertexBufHandle,
	int IndexBufHandle,
	int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */,
	int BaseVertex,
	int StartVertex,
	int UseVertexNum,
	int StartIndex,
	int UseIndexNum
)
{
	VERTEXBUFFERHANDLEDATA *VertexBuffer ;
	INDEXBUFFERHANDLEDATA  *IndexBuffer ;
	GLenum					IndexFormat ;
//	int                     IndexSize ;
	GRAPHICS_ANDROID_TEXTURE *UseTexture[ USE_TEXTURESTAGE_NUM ] ;
	int						 UseTextureNum = 0 ;
	int i ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// ����ł� StartIndex �� 0 �ȊO�̏ꍇ�͕`��ł��Ȃ�
	if( StartIndex != 0 )
	{
		return -1 ;
	}

	if( PrimitiveType < DX_PRIMTYPE_MIN || PrimitiveType > DX_PRIMTYPE_MAX )
	{
		return -1 ;
	}

	// �G���[����
	if( VERTEXBUFFERCHK( VertexBufHandle, VertexBuffer ) )
	{
		return -1 ;
	}
	if( INDEXBUFFERCHK( IndexBufHandle, IndexBuffer ) )
	{
		return -1 ;
	}

	// �V�F�[�_�[�p���_�f�[�^�ł͂Ȃ��ꍇ�̓G���[
	if( VertexBuffer->Type != DX_VERTEX_TYPE_SHADER_3D )
	{
		return -1 ;
	}

	switch( IndexBuffer->Type )
	{
	default :
	case DX_INDEX_TYPE_16BIT :
		IndexFormat = GL_UNSIGNED_SHORT ;
		break ;

	case DX_INDEX_TYPE_32BIT :
		IndexFormat = GL_UNSIGNED_INT ;
		break ;
	}
//	IndexSize = IndexFormat == GL_UNSIGNED_SHORT ? 2 : 4 ;

	// �R�c�s����n�[�h�E�G�A�ɔ��f����
	if( GSYS.DrawSetting.MatchHardware3DMatrix == FALSE )
		Graphics_DrawSetting_ApplyLib3DMatrixToHardware() ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`��̏���
	Graphics_Android_DrawPreparationToShader( DX_ANDROID_DRAWPREP_LIGHTING | DX_ANDROID_DRAWPREP_FOG, FALSE ) ;

	// �g�p����e�N�X�`�����
	UseTextureNum = 0 ;
	for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
	{
		IMAGEDATA     *TempImage ;
		SHADOWMAPDATA *TempShadowMap ;

		if( !GRAPHCHKFULL( GSYS.DrawSetting.UserShaderRenderInfo.SetTextureGraphHandle[ i ], TempImage ) )
		{
			UseTexture[ i ] = &TempImage->Hard.Draw[ 0 ].Tex->PF->Texture ;
		}
		else
		if( !SHADOWMAPCHKFULL( GSYS.DrawSetting.UserShaderRenderInfo.SetTextureGraphHandle[ i ], TempShadowMap ) )
		{
			UseTexture[ i ] = &TempShadowMap->PF->Texture ;
		}
		else
		{
			continue ;
		}

		UseTextureNum = i + 1 ;
	}

	// �g�p����e�N�X�`�����Z�b�g
	if( UseTextureNum > 0 )
	{
		for( i = 0 ; i < UseTextureNum ; i ++ )
		{
			Graphics_Android_DeviceState_SetTexture( i, UseTexture[ i ] ) ;
		}
	}

	// Uniform �̍X�V
	Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader_Force != NULL ? GANDR.Device.State.SetShader_Force : GANDR.Device.State.SetShader, 3 ) ;

	// ���_�f�[�^�̃Z�b�g�A�b�v
	Graphics_Android_DeviceState_SetupShaderVertexData(
		GANDR.Device.State.SetShader_Force != NULL ? GANDR.Device.State.SetShader_Force : GANDR.Device.State.SetShader,
		&g_BaseSimpleVertexShaderInfo[ ANDROID_VERTEX_INPUTLAYOUT_SHADER_3D ].InputInfo,
		NULL,
		VertexBuffer->PF->VertexBuffer
	) ;

	// �`��
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->PF->IndexBuffer ) ;

	glDrawElements( g_DXPrimitiveTypeToGLES2PrimitiveType[ PrimitiveType ], UseIndexNum, IndexFormat, NULL );
	GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ) ;

	// �I��
	return 0 ;
}




























// ���ˑ��������֌W

// �`�揈���̊��ˑ������̏��������s���֐�( ���s�ӏ���ʂO )
extern	int		Graphics_Initialize_Timing0_PF( void )
{
	// g_AndroidSys.NativeWindow �ɒl����������܂ő҂�
	while( g_AndroidSys.NativeWindow == NULL )
	{
		NS_ProcessMessage() ;
		Thread_Sleep( 1 ) ;
	}

	// Android ���g�p�����O���t�B�b�N�X�����̏�����
	if( Graphics_Android_Initialize() == -1 )
	{
		return -1 ;
	}

	// ����I��
	return 0 ;
}

// �`�揈���̊��ˑ������̏��������s���֐�( ���s�ӏ���ʂQ )
extern	int		Graphics_Initialize_Timing1_PF( void )
{
	// �f�o�C�X�̐ݒ�����t���b�V��
	Graphics_Android_DeviceState_RefreshRenderState() ;

	// ��ʂ̏�����
	Graphics_Hardware_ClearDrawScreen_PF( NULL ) ;

	// ����I��
	return 0 ;
}

// �n�[�h�E�G�A�A�N�Z�����[�^���g�p����ꍇ�̊��ˑ��̏������������s��
extern	int		Graphics_Hardware_Initialize_PF( void )
{
	return Graphics_Android_Device_Initialize() ;
}

// �`�揈���̊��ˑ������̌�n�����s���֐�
extern	int		Graphics_Terminate_PF( void )
{
	// Android �̕`�揈���̌�n��
	Graphics_Android_Terminate() ;

	// �V�F�[�_�[�R�[�h�̌�n��
	Graphics_Android_ShaderCode_Base_Terminate() ;
	Graphics_Android_ShaderCode_Base3D_Terminate() ;

#ifndef DX_NON_MODEL
	Graphics_Android_ShaderCode_Model_Terminate() ;
#endif // DX_NON_MODEL

	// �I��
	return 0 ;
}

// �O���t�B�b�N�X�V�X�e���̕��A�A���͕ύX�t���̍ăZ�b�g�A�b�v���s��
extern	int		Graphics_RestoreOrChangeSetupGraphSystem_PF( int Change, int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int RefreshRate )
{
#ifndef DX_NON_ASYNCLOAD
	// �񓯊��ǂݍ��݂̓r���̏ꍇ�́A�񓯊��ǂݍ��݂��I������܂ő҂�
	while( NS_GetASyncLoadNum() > 0 )
	{
		ProcessASyncLoadRequestMainThread() ;
		Thread_Sleep( 0 ) ;
	}
#endif // DX_NON_ASYNCLOAD

//	int i ;

	if( Change == TRUE )
	{
		// ��ʃ��[�h�̃Z�b�g
		Graphics_Screen_SetMainScreenSize( ScreenSizeX, ScreenSizeY ) ;
		GSYS.Screen.MainScreenColorBitDepth = ColorBitDepth ;
		GSYS.Screen.MainScreenRefreshRate   = RefreshRate ;
//		SetMemImgDefaultColorType( ColorBitDepth == 32 ? 1 : 0 ) ;

		// �T�u�o�b�N�o�b�t�@�̍�蒼�����s��
		Graphics_Android_TerminateSubBackBuffer() ;

		// �T�u�o�b�N�o�b�t�@�̍쐬
		if( Graphics_Android_SetupSubBackBuffer() < 0 )
		{
			return -1 ;
		}

		if( ( DWORD )GSYS.DrawSetting.TargetScreen[ 0 ] == DX_SCREEN_BACK ||
			( DWORD )GSYS.DrawSetting.TargetScreen[ 0 ] == DX_SCREEN_FRONT ) 
		{
			NS_SetDrawScreen( GSYS.DrawSetting.TargetScreen[ 0 ] ) ;
		}

		return 0 ;
	}
	else
	{
		// DirectInput �I�u�W�F�N�g�̍ăZ�b�g�A�b�v
#ifndef DX_NON_INPUT
		TerminateInputSystem() ;
		InitializeInputSystem() ;
#endif // DX_NON_INPUT
	}

//	DXST_LOGFILEFMT_ADDUTF16LE(( L"�m�ۃ�������:%d  �m�ۃ��������T�C�Y:%dByte(%dKByte)", NS_DxGetAllocNum(), NS_DxGetAllocSize(), NS_DxGetAllocSize() / 1024 )) ;

	if( DxSysData.NotDrawFlag == FALSE )
	{
		MATRIX_D ViewMatrix, ProjectionMatrix, ViewportMatrix ;

		// OpenGL ES �ɂ��`�揈���̏�����
		GSYS.Screen.FullScreenResolutionModeAct = GSYS.Screen.FullScreenResolutionMode ;
		Graphics_Android_Initialize() ;

		// �O���t�B�b�N�n���h�������� OpenGL ES �I�u�W�F�N�g�̍č쐬
		Graphics_Android_CreateObjectAll() ;

#ifndef DX_NON_MASK
		// �}�X�N�T�[�t�F�X�̍č쐬
		Mask_ReCreateSurface() ;
#endif
		// �A�N�e�B�u�O���t�B�b�N�̃A�h���X���ēx�ݒ�
		if( Change == FALSE )
		{
			ViewMatrix       = GSYS.DrawSetting.ViewMatrix ;
			ProjectionMatrix = GSYS.DrawSetting.ProjectionMatrix ;
			ViewportMatrix   = GSYS.DrawSetting.ViewportMatrix ;
		}
//		NS_SetRenderTargetToShader( 0, GSYS.DrawSetting.TargetScreen[ 0 ], GSYS.DrawSetting.TargetScreenSurface[ 0 ] ) ;
		NS_SetDrawScreen( GSYS.DrawSetting.TargetScreen[ 0 ] ) ;

		// �O���t�B�b�N�֌W�̐ݒ��������
		Graphics_Android_Device_ReInitialize() ;

		// ��ʂ̏�����
//		NS_ClearDrawScreen() ;
//		NS_ScreenFlip() ;
//		NS_ClearDrawScreen() ;
//		NS_ScreenFlip() ;

		// �f�o�C�X���X�g�������ɍ폜����t���O�������Ă���O���t�B�b�N���폜����
		Graphics_Image_DeleteDeviceLostDelete() ;

		// �O���t�B�b�N�̕���
		NS_RunRestoreShred() ;

		// �O���t�B�b�N�X�f�o�C�X�̃��X�g���畜�A����O�ɌĂԊ֐����o�^����Ă�������s����
		if( GANDR.Device.Setting.DeviceLostCallbackFunction )
		{
			GANDR.Device.Setting.DeviceLostCallbackFunction( GANDR.Device.Setting.DeviceLostCallbackData ) ;
		}

		// �O���t�B�b�N�X�f�o�C�X�̃��X�g���畜�A�����Ƃ��ɌĂԊ֐����o�^����Ă�������s����
		if( GANDR.Device.Setting.DeviceRestoreCallbackFunction )
		{
			GANDR.Device.Setting.DeviceRestoreCallbackFunction( GANDR.Device.Setting.DeviceRestoreCallbackData ) ;
		}

		// �n�[�h�E�G�A�̐ݒ�����t���b�V��
		Graphics_Android_DeviceState_RefreshRenderState() ;

#ifndef DX_NON_MODEL
		// ���_�o�b�t�@�̃Z�b�g�A�b�v
		MV1SetupVertexBufferAll() ;
#endif

		// ���C�g�̐ݒ�� Direct3D �ɍĔ��f����悤�Ƀt���O���Z�b�g
		GSYS.Light.HardwareRefresh = TRUE ;

		// ���̑��̍Đݒ�
		if( Change == FALSE )
		{
			NS_SetDrawArea( GSYS.DrawSetting.OriginalDrawRect.left, GSYS.DrawSetting.OriginalDrawRect.top, GSYS.DrawSetting.OriginalDrawRect.right, GSYS.DrawSetting.OriginalDrawRect.bottom ) ;
			NS_SetTransformToWorldD( &GSYS.DrawSetting.WorldMatrix );
			NS_SetTransformToViewD( &ViewMatrix );
			NS_SetTransformToProjectionD( &ProjectionMatrix );
			NS_SetTransformToViewportD( &ViewportMatrix );
		}

//		// �O�ȊO�̃^�[�Q�b�g�̃Z�b�g�A�b�v
//		for( i = 1 ; i < GSYS.HardInfo.RenderTargetNum ; i ++ )
//		{
//			NS_SetRenderTargetToShader( i, GSYS.DrawSetting.TargetScreen[ i ], GSYS.DrawSetting.TargetScreenSurface[ i ] ) ;
//		}
	}

	// �I��
	return 0 ;
}

// �`��p�f�o�C�X���L�����ǂ������擾����( �߂�l  TRUE:�L��  FALSE:���� )
extern	int		Graphics_Hardware_CheckValid_PF( void )
{
	return ANDR_CHECKVALID_HARDWARE ;
}














































// ���ˑ��`��ݒ�֌W

// �V�F�[�_�[�`��ł̕`����ݒ肷��
extern	int		Graphics_Hardware_SetRenderTargetToShader_PF( int TargetIndex, int DrawScreen, int SurfaceIndex, int MipLevel )
{
	IMAGEDATA *Image ;
	IMAGEDATA *OldImage ;

	// �^�[�Q�b�g���O�ȊO�̏ꍇ�̓V�F�[�_�[���g�p�ł��Ȃ��ꍇ�͉������Ȃ�
	if( GSYS.HardInfo.UseShader == FALSE )
		return -1 ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �Z�b�g���Ă����e�N�X�`���[���O��
	Graphics_Android_DrawSetting_SetTexture( NULL ) ;

	// ���܂ł̕`���̉摜���̎擾
	if( GRAPHCHKFULL( GSYS.DrawSetting.TargetScreen[ TargetIndex ], OldImage ) )
	{
		OldImage = NULL ;
	}

	// �摜���ǂ����𔻒�
	if( GRAPHCHKFULL( DrawScreen, Image ) )
	{
		// �摜�ł͂Ȃ��ꍇ�͕`��Ώۂ𖳌��ɂ���
		GSYS.DrawSetting.TargetScreen[ TargetIndex ] = 0 ;
		GSYS.DrawSetting.TargetScreenSurface[ TargetIndex ] = 0 ;
//		Graphics_Android_DeviceState_SetRenderTarget( 0, 0, 0 ) ;
		return 0 ;
	}

	// �摜�������ꍇ�͕`��\�ł͖����ꍇ�̓G���[
	if( Image->Orig->FormatDesc.DrawValidFlag == FALSE )
	{
		return -1 ;
	}

	// �`�����Z�b�g
	Graphics_Android_DeviceState_SetRenderTarget( Image->Hard.Draw[ 0 ].Tex->PF->FrameBuffer, Image->Hard.Draw[ 0 ].Tex->PF->Texture.Width, Image->Hard.Draw[ 0 ].Tex->PF->Texture.Height ) ;

	// ����I��
	return 0 ;
}

// ���C���E�C���h�E�̔w�i�F��ݒ肷��( Red,Green,Blue:���ꂼ�� �O�`�Q�T�T )
extern	int		Graphics_Hardware_SetBackgroundColor_PF( int Red, int Green, int Blue, int Alpha )
{
	Graphics_Android_DeviceState_SetBackgroundColor( Red, Green, Blue, Alpha ) ;

	return 0 ;
}

// SetDrawBright �̈��������
extern	int		Graphics_Hardware_SetDrawBrightToOneParam_PF( DWORD Bright )
{
	// �f�B�t�[�Y�J���[�̍X�V
	GANDR.Device.DrawInfo.DiffuseColor = GetDiffuseColor() ;

	// ����I��
	return 0 ;
}

// �`��u�����h���[�h���Z�b�g����
extern	int		Graphics_Hardware_SetDrawBlendMode_PF( int BlendMode, int BlendParam )
{
	// �f�B�t�[�Y�J���[�̍X�V
	GANDR.Device.DrawInfo.DiffuseColor = GetDiffuseColor() ;

	// ����I��
	return 0 ;
}

// �`�掞�̃A���t�@�e�X�g�̐ݒ���s��( TestMode:DX_CMP_GREATER��( -1:�f�t�H���g����ɖ߂� )  TestParam:�`��A���t�@�l�Ƃ̔�r�Ɏg�p����l )
extern	int		Graphics_Hardware_SetDrawAlphaTest_PF( int TestMode, int TestParam )
{
	// �f�B�t�[�Y�J���[�̍X�V
	GANDR.Device.DrawInfo.DiffuseColor = GetDiffuseColor() ;

	// ����I��
	return 0 ;
}

// �`�惂�[�h���Z�b�g����
extern	int		Graphics_Hardware_SetDrawMode_PF( int DrawMode )
{
	Graphics_Android_DeviceState_SetDrawMode( DrawMode ) ;

	// ����I��
	return 0 ;
}

// �`��P�x���Z�b�g
extern	int		Graphics_Hardware_SetDrawBright_PF( int RedBright, int GreenBright, int BlueBright )
{
	// �f�B�t�[�Y�J���[�̍X�V
	GANDR.Device.DrawInfo.DiffuseColor = GetDiffuseColor() ;

	// ����I��
	return 0 ;
}

// SetBlendGraphParam �̉ϒ������p�����[�^�t��
extern	int		Graphics_Hardware_SetBlendGraphParamBase_PF( IMAGEDATA *BlendImage, int BlendType, int *Param )
{
	// �u�����h�摜�� NULL �������̓e�N�X�`���ł͂Ȃ�������u�����h�摜�����̉���
	if( BlendImage == NULL || BlendImage->Orig->FormatDesc.TextureFlag == FALSE )
	{
		GSYS.DrawSetting.BlendGraph = -1 ;
		Graphics_Android_DrawSetting_SetBlendTexture( NULL ) ;
	}
	else
	{
		// �u�����h�p�����[�^���Z�b�g����
		Graphics_Android_DrawSetting_SetBlendTexture( &BlendImage->Hard.Draw[ 0 ].Tex[ 0 ].PF->Texture ) ;
		Graphics_Android_DrawSetting_SetBlendTextureParam( BlendType, Param ) ;
	}

	// ����I��
	return 0 ;
}

// �ő�ٕ����̒l���Z�b�g����
extern	int		Graphics_Hardware_SetMaxAnisotropy_PF( int MaxAnisotropy )
{
	// ����I��
	return 0 ;
}

// ���[���h�ϊ��p�s����Z�b�g����
extern	int		Graphics_Hardware_SetTransformToWorld_PF( const MATRIX *Matrix )
{
	Graphics_Android_DeviceState_SetWorldMatrix( Matrix ) ;

	// ����I��
	return 0 ;
}

// �r���[�ϊ��p�s����Z�b�g����
extern	int		Graphics_Hardware_SetTransformToView_PF( const MATRIX *Matrix )
{
	Graphics_Android_DeviceState_SetViewMatrix( Matrix ) ;

	// ����I��
	return 0 ;
}

// Android �ɐݒ肷��ˉe�s����X�V����
static void Graphics_Hardware_ANDROID_RefreshProjectionMatrix( void )
{
	MATRIX *UseProjectionMatrix ;
	MATRIX *UseViewportMatrix ;
	MATRIX TempMatrix ;

//	if( GSYS.DrawSetting.UseProjectionMatrix2D )
//	{
//		if( AlwaysUpdate == FALSE && Update2DProjection == FALSE )
//		{
//			return ;
//		}
//
//		UseProjectionMatrix = &GSYS.DrawSetting.ProjectionMatrix2D ;
//		UseViewportMatrix   = &GSYS.DrawSetting.ViewportMatrix2D ;
//	}
//	else
//	{
//		if( AlwaysUpdate == FALSE && Update3DProjection == FALSE )
//		{
//			return ;
//		}

		UseProjectionMatrix = &GSYS.DrawSetting.ProjectionMatrixF ;
		UseViewportMatrix   = &GSYS.DrawSetting.ViewportMatrixF ;
//	}
	if( GSYS.DrawSetting.MatchHardware_2DMatrix )
	{
		CreateMultiplyMatrix( &TempMatrix, &GSYS.DrawSetting._2DMatrixF, &GSYS.DrawSetting.Direct3DViewportMatrixAntiF ) ;
	}
	else
	{
		CreateMultiplyMatrix( &TempMatrix, UseProjectionMatrix, UseViewportMatrix                             ) ;
		CreateMultiplyMatrix( &TempMatrix, &TempMatrix,         &GSYS.DrawSetting.Direct3DViewportMatrixAntiF ) ;
	}

	Graphics_Android_DeviceState_SetProjectionMatrix( &TempMatrix ) ;
}

// ���e�ϊ��p�s����Z�b�g����
extern	int		Graphics_Hardware_SetTransformToProjection_PF( const MATRIX *Matrix )
{
	Graphics_Hardware_ANDROID_RefreshProjectionMatrix() ;

	// ����I��
	return 0 ;
}

// �r���[�|�[�g�s����Z�b�g����
extern	int		Graphics_Hardware_SetTransformToViewport_PF( const MATRIX * /* Matrix */ )
{
	Graphics_Hardware_ANDROID_RefreshProjectionMatrix() ;

	// ����I��
	return 0 ;
}

// �e�N�X�`���A�h���X���[�h��ݒ肷��
extern	int		Graphics_Hardware_SetTextureAddressMode_PF( int Mode /* DX_TEXADDRESS_WRAP �� */, int Stage )
{
	Graphics_Android_DeviceState_SetTextureAddress( Mode, Stage ) ;

	// ����I��
	return 0 ;
}

// �e�N�X�`���A�h���X���[�h��ݒ肷��
extern	int		Graphics_Hardware_SetTextureAddressModeUV_PF( int ModeU, int ModeV, int Stage )
{
	Graphics_Android_DeviceState_SetTextureAddressU( ModeU, Stage ) ;
	Graphics_Android_DeviceState_SetTextureAddressV( ModeV, Stage ) ;

	// ����I��
	return 0 ;
}

// �e�N�X�`�����W�ϊ��s����Z�b�g����
extern	int		Graphics_Hardware_SetTextureAddressTransformMatrix_PF( int UseFlag, MATRIX *Matrix, int Sampler )
{
	Graphics_Android_DeviceState_SetTextureAddressTransformMatrix( UseFlag, Matrix ) ;

	// ����I��
	return 0 ;
}

// �t�H�O��L���ɂ��邩�ǂ�����ݒ肷��( TRUE:�L��  FALSE:���� )
extern	int		Graphics_Hardware_SetFogEnable_PF( int Flag )
{
	Graphics_Android_DeviceState_SetFogEnable( Flag ) ;

	// ����I��
	return 0 ;
}

// �t�H�O���[�h��ݒ肷��
extern	int		Graphics_Hardware_SetFogMode_PF( int Mode /* DX_FOGMODE_NONE �� */ )
{
	Graphics_Android_DeviceState_SetFogVertexMode( Mode ) ;

	// ����I��
	return 0 ;
}

// �t�H�O�J���[��ύX����
extern	int		Graphics_Hardware_SetFogColor_PF( DWORD FogColor )
{
	Graphics_Android_DeviceState_SetFogColor( FogColor ) ;

	// ����I��
	return 0 ;
}

// �t�H�O���n�܂鋗���ƏI�����鋗����ݒ肷��( 0.0f �` 1.0f )
extern	int		Graphics_Hardware_SetFogStartEnd_PF( float start, float end )
{
	Graphics_Android_DeviceState_SetFogStartEnd( start, end ) ;

	// ����I��
	return 0 ;
}

// �t�H�O�̖��x��ݒ肷��( 0.0f �` 1.0f )
extern	int		Graphics_Hardware_SetFogDensity_PF( float density )
{
	Graphics_Android_DeviceState_SetFogDensity( density ) ;

	// ����I��
	return 0 ;
}

// ���[���h�ϊ��p�s����Z�b�g����
extern	int		Graphics_Hardware_DeviceDirect_SetWorldMatrix_PF( const MATRIX *Matrix )
{
	return Graphics_Android_DeviceState_SetWorldMatrix( Matrix ) ;
}

// �r���[�ϊ��p�s����Z�b�g����
extern	int		Graphics_Hardware_DeviceDirect_SetViewMatrix_PF( const MATRIX *Matrix )
{
	return Graphics_Android_DeviceState_SetViewMatrix( Matrix ) ;
}

// ���e�ϊ��p�s����Z�b�g����
extern	int		Graphics_Hardware_DeviceDirect_SetProjectionMatrix_PF( const MATRIX *Matrix )
{
	return Graphics_Android_DeviceState_SetProjectionMatrix( Matrix ) ;
}

// ��{�f�[�^�ɐݒ肳��Ă���t�H�O�����n�[�h�E�F�A�ɔ��f����
extern	int		Graphics_Hardware_ApplyLigFogToHardware_PF( void )
{
	if( GANDR.Device.State.FogEnable != GSYS.DrawSetting.FogEnable )
	{
		Graphics_Android_DeviceState_SetFogEnable( GSYS.DrawSetting.FogEnable ) ;
	}

	// ����I��
	return 0 ;
}

// �ȑO�� DrawModiGraph �֐��̃R�[�h���g�p���邩�ǂ����̃t���O���Z�b�g����
extern	int		Graphics_Hardware_SetUseOldDrawModiGraphCodeFlag_PF( int Flag )
{
	GANDR.Setting.UseOldDrawModiGraphCodeFlag = Flag ;
	
	// �I��
	return 0 ;
}

// �`���ɐ��������l���������ނ��ǂ����̃t���O���X�V����
extern	int		Graphics_Hardware_RefreshAlphaChDrawMode_PF( void )
{
	IMAGEDATA *Image ;
	int i ;
	int NextFlag ;

	NextFlag = FALSE ;

	// �O�ԈȊO�ɂ��`��悪�ݒ肳��Ă����ꍇ�͒ʏ탂�[�h
	for( i = 1 ; i < DX_RENDERTARGET_COUNT ; i ++ )
	{
		if( GSYS.DrawSetting.TargetScreen[ i ] != 0 )
			goto END ;
	}

	// �`��悪�ʏ��ʂ̏ꍇ�͉������Ȃ�
	if( ( DWORD )GSYS.DrawSetting.TargetScreen[ 0 ] == DX_SCREEN_BACK ||
		( DWORD )GSYS.DrawSetting.TargetScreen[ 0 ] == DX_SCREEN_FRONT ||
		( DWORD )GSYS.DrawSetting.TargetScreen[ 0 ] == DX_SCREEN_WORK ||
		( DWORD )GSYS.DrawSetting.TargetScreen[ 0 ] == DX_SCREEN_TEMPFRONT )
		goto END ;

	// �`���ƂȂ��Ă���摜�������̏ꍇ�͉������Ȃ�
	if( GRAPHCHKFULL( GSYS.DrawSetting.TargetScreen[ 0 ], Image ) )
		goto END ;

	// �`���̉摜�Ƀ��`�����l���������ꍇ���������Ȃ�
	if( Image->Orig->FormatDesc.AlphaChFlag == FALSE )
		goto END ;
	
	// �e�N�X�`���ł͂Ȃ��ꍇ�͉������Ȃ�
	if( Image->Orig->FormatDesc.TextureFlag == FALSE )
		goto END ;

	// �����ɗ����Ƃ������Ƃ͐��m�ȃ��`�����l���̌v�Z���s���Ƃ�������
	NextFlag = TRUE ;

END :
/*
	// �e�N�X�`���̕ۑ�
	if( NextFlag == TRUE )
	{
		IMAGEDATA *WorkImage ;
		int WorkTextureHandle ;

		WorkTextureHandle = GetWorkTexture( Image->Orig->FormatDesc.FloatTypeFlag, Image->Width, Image->Height, 0 ) ;
		if( GRAPHCHK( WorkTextureHandle, WorkImage ) )
			return -1 ;

		GRH.RenderTargetTexture          = WorkImage->Orig->Hard.Tex[ 0 ].PF->D3D9.Texture ;
		GRH.RenderTargetSurface          =     Image->Orig->Hard.Tex[ 0 ].PF->D3D9.Surface[ 0 ] ;
		GRH.RenderTargetCopySurface      = WorkImage->Orig->Hard.Tex[ 0 ].PF->D3D9.Surface[ 0 ] ;
		GRH.RenderTargetTextureInvWidth  = 1.0f / WorkImage->Orig->Hard.Tex[ 0 ].TexWidth ;
		GRH.RenderTargetTextureInvHeight = 1.0f / WorkImage->Orig->Hard.Tex[ 0 ].TexHeight ;
	}
	else
	{
		GRH.RenderTargetTexture = FALSE ;
	}
*/
	// �ȑO�ƃt���O�̏�Ԃ��قȂ�ꍇ�̂݃u�����h���[�h�̍X�V���s��
	if( NextFlag != GSYS.DrawSetting.AlphaChDrawMode )
	{
		// �t���O�̕ۑ�
		GSYS.DrawSetting.AlphaChDrawMode = NextFlag ;
		GANDR.Device.DrawSetting.ChangeBlendParamFlag = TRUE ;
		GSYS.ChangeSettingFlag = TRUE ;
	}

	// �I��
	return 0 ;
}

// �~�h���E�F�A�����g�p������� Direct3D �� OpenGL �̂c�w���C�u�����p�̐ݒ���ēx�s�����߂̊֐�
extern int Graphics_Hardware_RefreshSetting_PF( void )
{
	Graphics_Android_DeviceState_RefreshRenderState() ;

	// �I��
	return 0 ;
}
























// ���ˑ��ݒ�֌W

// �n�[�h�E�G�A�̒��_���Z�����@�\���g�p���邩�ǂ�����ݒ肷��
extern	int		Graphics_Hardware_SetUseHardwareVertexProcessing_PF( int Flag )
{
	return 0 ;
}

// �s�N�Z���P�ʂŃ��C�e�B���O���s�����ǂ�����ݒ肷��A�v ShaderModel 3.0( TRUE:�s�N�Z���P�ʂ̃��C�e�B���O���s��  FALSE:���_�P�ʂ̃��C�e�B���O���s��( �f�t�H���g ) )
extern	int		Graphics_Hardware_SetUsePixelLighting_PF( int Flag )
{
	GANDR.UsePixelLightingShader = Flag ;

	// �I��
	return 0 ;
}

// �O���t�B�b�N�X�f�o�C�X�����X�g���畜�A�����ۂɌĂ΂��R�[���o�b�N�֐���ݒ肷��
extern	int		Graphics_Hardware_SetGraphicsDeviceRestoreCallbackFunction_PF( void (* Callback )( void *Data ), void *CallbackData )
{
	GANDR.Device.Setting.DeviceRestoreCallbackFunction = Callback ;
	GANDR.Device.Setting.DeviceRestoreCallbackData = CallbackData ;

	// �I��
	return 0 ;
}

// �O���t�B�b�N�X�f�o�C�X�����X�g���畜�A����O�ɌĂ΂��R�[���o�b�N�֐���ݒ肷��
extern	int		Graphics_Hardware_SetGraphicsDeviceLostCallbackFunction_PF( void (* Callback )( void *Data ), void *CallbackData )
{
	GANDR.Device.Setting.DeviceLostCallbackFunction = Callback ;
	GANDR.Device.Setting.DeviceLostCallbackData = CallbackData ;

	// �I��
	return 0 ;
}

// �ʏ�`��Ƀv���O���}�u���V�F�[�_�[���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����( �f�t�H���g )  FALSE:�g�p���Ȃ� )
extern	int		Graphics_Hardware_SetUseNormalDrawShader_PF( int Flag )
{
	return 0 ;
}

// �r�f�I�������̗e�ʂ𓾂�
extern	int		Graphics_Hardware_GetVideoMemorySize_PF( int *AllSize, int *FreeSize )
{
	return 0 ;
}

// Vista�ȍ~�� Windows Aero �𖳌��ɂ��邩�ǂ������Z�b�g����ATRUE:�����ɂ���  FALSE:�L���ɂ���( DxLib_Init �̑O�ɌĂԕK�v������܂� )
extern	int		Graphics_SetAeroDisableFlag_PF( int Flag )
{
	// �������O�̂ݗL��
	if( DxSysData.DxLib_InitializeFlag == TRUE )
	{
		return -1 ;
	}

	// �I��
	return 0 ;
}































// ���ˑ���ʊ֌W

// �ݒ�Ɋ�Â��Ďg�p����y�o�b�t�@���Z�b�g����
extern	int		Graphics_Hardware_SetupUseZBuffer_PF( void )
{
	// �I��
	return 0 ;
}

// ��ʂ̂y�o�b�t�@�̏�Ԃ�����������
extern	int		Graphics_Hardware_ClearDrawScreenZBuffer_PF( const RECT *ClearRect )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// �`��ΏۃT�[�t�F�X��ύX����
#ifndef DX_NON_MASK
	if( MASKD.MaskValidFlag && MASKANDR.MaskScreenFrameBuffer )
	{
		IMAGEDATA           *Image = NULL ;
		SHADOWMAPDATA       *ShadowMap = NULL ;

		// �`���摜�̉摜�����擾
		GRAPHCHKFULL( GSYS.DrawSetting.TargetScreen[ 0 ], Image ) ;
		SHADOWMAPCHKFULL( GSYS.DrawSetting.TargetScreen[ 0 ], ShadowMap ) ;

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
	}
#endif

	// �r���[�|�[�g���T�[�t�F�X�S�̂ɂ���
	{
		RECT Viewport ;

		_MEMSET( &Viewport, 0, sizeof( Viewport ) ) ;
		Viewport.left	= 0 ;
		Viewport.top	= 0 ;
		Viewport.right	= GANDR.Device.State.TargetFrameBufferWidth ;
		Viewport.bottom	= GANDR.Device.State.TargetFrameBufferHeight ;
		Graphics_Android_DeviceState_SetViewport( &Viewport ) ;
	}

	glClearColor(
		GSYS.Screen.BackgroundRed   / 255.0f,
		GSYS.Screen.BackgroundGreen / 255.0f,
		GSYS.Screen.BackgroundBlue  / 255.0f,
		GSYS.Screen.BackgroundAlpha / 255.0f
	) ;

	glDepthMask( GL_TRUE ) ;
    glClear( GL_DEPTH_BUFFER_BIT ) ;
	glDepthMask( GANDR.Device.State.DepthWriteEnable ? GL_TRUE : GL_FALSE ) ;

	// �`��ΏۃT�[�t�F�X�����ɖ߂�
#ifndef DX_NON_MASK
	if( MASKD.MaskValidFlag && MASKANDR.MaskScreenFrameBuffer )
	{
		Graphics_Android_DeviceState_SetRenderTarget(
			MASKANDR.MaskScreenFrameBuffer,
			MASKANDR.MaskTextureSizeX,
			MASKANDR.MaskTextureSizeY
		) ;
	}
#endif

	// �r���[�|�[�g�͈̔͂����ɖ߂�
	Graphics_Android_DeviceState_SetViewport( &GSYS.DrawSetting.DrawArea ) ;

	// �I��
	return 0 ;
}

// ��ʂ̏�Ԃ�����������
extern	int		Graphics_Hardware_ClearDrawScreen_PF( const RECT *ClearRect )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// �`��ΏۃT�[�t�F�X��ύX����
#ifndef DX_NON_MASK
	if( MASKD.MaskValidFlag && MASKANDR.MaskScreenFrameBuffer )
	{
		IMAGEDATA           *Image = NULL ;
		SHADOWMAPDATA       *ShadowMap = NULL ;

		// �`���摜�̉摜�����擾
		GRAPHCHKFULL( GSYS.DrawSetting.TargetScreen[ 0 ], Image ) ;
		SHADOWMAPCHKFULL( GSYS.DrawSetting.TargetScreen[ 0 ], ShadowMap ) ;

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
	}
#endif

	// �r���[�|�[�g���T�[�t�F�X�S�̂ɂ���
	{
		RECT Viewport ;

		_MEMSET( &Viewport, 0, sizeof( Viewport ) ) ;
		Viewport.left	= 0 ;
		Viewport.top	= 0 ;
		Viewport.right	= GANDR.Device.State.TargetFrameBufferWidth ;
		Viewport.bottom	= GANDR.Device.State.TargetFrameBufferHeight ;
		Graphics_Android_DeviceState_SetViewport( &Viewport ) ;
	}

	glClearColor(
		GSYS.Screen.BackgroundRed   / 255.0f,
		GSYS.Screen.BackgroundGreen / 255.0f,
		GSYS.Screen.BackgroundBlue  / 255.0f,
		GSYS.Screen.BackgroundAlpha / 255.0f
	) ;

	glDepthMask( GL_TRUE ) ;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) ;
	glDepthMask( GANDR.Device.State.DepthWriteEnable ? GL_TRUE : GL_FALSE ) ;

	// �`��ΏۃT�[�t�F�X�����ɖ߂�
#ifndef DX_NON_MASK
	if( MASKD.MaskValidFlag && MASKANDR.MaskScreenFrameBuffer )
	{
		Graphics_Android_DeviceState_SetRenderTarget(
			MASKANDR.MaskScreenFrameBuffer,
			MASKANDR.MaskTextureSizeX,
			MASKANDR.MaskTextureSizeY
		) ;
	}
#endif

	// �r���[�|�[�g�͈̔͂����ɖ߂�
	Graphics_Android_DeviceState_SetViewport( &GSYS.DrawSetting.DrawArea ) ;

	// �I��
	return 0 ;
}

// �`����ʂ̃Z�b�g
extern	int		Graphics_Hardware_SetDrawScreen_PF( int DrawScreen, int OldScreenSurface, int OldScreenMipLevel, IMAGEDATA *NewTargetImage, IMAGEDATA *OldTargetImage, SHADOWMAPDATA *NewTargetShadowMap, SHADOWMAPDATA *OldTargetShadowMap )
{
	int i ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// �Z�b�g���Ă����e�N�X�`���[���O��
	Graphics_Android_DrawSetting_SetTexture( NULL ) ;
	for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
	{
		Graphics_Android_DeviceState_SetTexture( 0, NULL ) ;
	}

	// �`���̕ύX

	// �}�X�N�T�[�t�F�X�����݂��Ă��Ċ��L���ȏꍇ�̓}�X�N�T�[�t�F�X��`��Ώۂɂ���
#ifndef DX_NON_MASK
	if( MASKD.MaskValidFlag && MASKANDR.MaskScreenFrameBuffer )
	{
		Graphics_Android_DeviceState_SetRenderTarget( MASKANDR.MaskScreenFrameBuffer, MASKANDR.MaskTextureSizeX, MASKANDR.MaskTextureSizeY ) ;
	}
	else
#endif
	// �V���h�E�}�b�v���L���ȏꍇ�̓V���h�E�}�b�v��`��Ώۂɂ���
	if( NewTargetShadowMap )
	{
		Graphics_Android_DeviceState_SetRenderTarget( NewTargetShadowMap->PF->FrameBuffer, NewTargetShadowMap->PF->Texture.Width, NewTargetShadowMap->PF->Texture.Height ) ;
	}
	else
	// �`��\�摜���L���ȏꍇ�͕`��\�摜��`��Ώۂɂ���
	if( NewTargetImage )
	{
		if( NewTargetImage->Hard.Draw[ 0 ].Tex->PF->MSRenderTarget != 0 )
		{
			Graphics_Android_DeviceState_SetRenderTarget( NewTargetImage->Hard.Draw[ 0 ].Tex->PF->MSRenderTarget, NewTargetImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width, NewTargetImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height ) ;
		}
		else
		{
			Graphics_Android_DeviceState_SetRenderTarget( NewTargetImage->Hard.Draw[ 0 ].Tex->PF->FrameBuffer, NewTargetImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width, NewTargetImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height ) ;
		}
	}
	else
	// ����ȊO�̏ꍇ�̓T�u�o�b�N�o�b�t�@��`��Ώۂɂ���
	{
		Graphics_Android_DeviceState_SetRenderTarget( GANDR.Device.Screen.SubBackBufferFrameBuffer, GANDR.Device.Screen.SubBackBufferTextureSizeX, GANDR.Device.Screen.SubBackBufferTextureSizeY ) ;
	}

	// �g�p����y�o�b�t�@�̃Z�b�g�A�b�v
	Graphics_Screen_SetupUseZBuffer() ;

	// ����I��
	return 0 ;
}

// SetDrawScreen �̍Ō�ŌĂ΂��֐�
extern	int		Graphics_Hardware_SetDrawScreen_Post_PF( int DrawScreen )
{
	// ����I��
	return 0 ;
}

// �`��\�̈�̃Z�b�g
extern	int		Graphics_Hardware_SetDrawArea_PF( int x1, int y1, int x2, int y2 )
{
	RECT Viewport ;

	if( GSYS.DrawSetting.DrawArea.right  - GSYS.DrawSetting.DrawArea.left == 0 ||
		GSYS.DrawSetting.DrawArea.bottom - GSYS.DrawSetting.DrawArea.top  == 0 )
	{
		return -1 ;
	}

	// �r���[�|�[�g�̃Z�b�g
	Viewport.left	= GSYS.DrawSetting.DrawArea.left ;
	Viewport.top	= GSYS.DrawSetting.DrawArea.top ;
	Viewport.right	= GSYS.DrawSetting.DrawArea.right  ;
	Viewport.bottom	= GSYS.DrawSetting.DrawArea.bottom ;
	Graphics_Android_DeviceState_SetViewport( &Viewport ) ;

	// �ˉe�s��ƃr���[�|�[�g�s��̋t�s�����Z�������̂��Z�b�g
	Graphics_Hardware_ANDROID_RefreshProjectionMatrix() ;
	GSYS.DrawSetting.MatchHardwareProjectionMatrix = TRUE ;

	// �A���`�r���[�|�[�g�s����X�V
	Graphics_Android_DeviceState_SetAntiViewportMatrix( &GSYS.DrawSetting.Direct3DViewportMatrixAntiF ) ;

	// ����I��
	return 0 ;
}

// �`���o�b�t�@�����b�N����
extern	int		Graphics_Hardware_LockDrawScreenBuffer_PF( RECT *LockRect, BASEIMAGE *BaseImage, int TargetScreen, IMAGEDATA *TargetImage, int TargetScreenSurface, int TargetScreenMipLevel, int ReadOnly, int TargetScreenTextureNo )
{
	GLuint TargetFrameBuffer ;
	GLuint TargetTexture ;
	GLuint TargetWidth ;
	GLuint TargetHeight ;
//	COLORDATA *TargetColorData ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// ��荞�݌��ƂȂ�T�[�t�F�X�̌���

	// �`��\�摜���Ώۂ̏ꍇ
	if( TargetImage )
	{
		TargetFrameBuffer = TargetImage->Orig->Hard.Tex[ TargetScreenTextureNo ].PF->FrameBuffer ;
		TargetTexture     = TargetImage->Orig->Hard.Tex[ TargetScreenTextureNo ].PF->Texture.TextureBuffer ;
		TargetWidth       = TargetImage->Orig->Hard.Tex[ TargetScreenTextureNo ].PF->Texture.Width ;
		TargetHeight      = TargetImage->Orig->Hard.Tex[ TargetScreenTextureNo ].PF->Texture.Height ;
	}
	else
	{
		TargetFrameBuffer = GANDR.Device.Screen.SubBackBufferFrameBuffer ;
		TargetTexture     = GANDR.Device.Screen.SubBackBufferTexture ;
		TargetWidth       = GANDR.Device.Screen.SubBackBufferTextureSizeX ;
		TargetHeight      = GANDR.Device.Screen.SubBackBufferTextureSizeY ;
	}

//	BaseImage->ColorData      = *TargetColorData ;
//	BaseImage->Width          = LockRect->right  - LockRect->left ;
//	BaseImage->Height         = LockRect->bottom - LockRect->top ;
//	BaseImage->Pitch          = TargetTexture->getPitch() * TargetColorData->PixelByte ;
//	BaseImage->GraphData      = ( BYTE * )TargetTexture->getBaseAddress() + LockRect->left * TargetColorData->PixelByte + LockRect->top * BaseImage->Pitch ;
//	BaseImage->MipMapCount    = 0 ;
//	BaseImage->GraphDataCount = 0 ;

	// �}�b�v
	if( Graphics_Android_Texture_Map( TargetTexture, TargetFrameBuffer, TargetWidth, TargetHeight, LockRect, BaseImage, &GANDR.Device.Screen.DrawScreenLockImage ) < 0 )
	{
		DXST_LOGFILE_ADDUTF16LE( "\xcf\x63\x3b\x75\xfe\x5b\x61\x8c\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x6e\x30\xed\x30\xc3\x30\xaf\x30\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�`��Ώۃo�b�t�@�̃��b�N�Ɏ��s���܂���\n" @*/ ) ;
		return -1 ;
	}

	// ����I��
	return 0 ;
}

// �`���o�b�t�@���A�����b�N����
extern	int		Graphics_Hardware_UnlockDrawScreenBuffer_PF( void )
{
	// �}�b�v������
	Graphics_Android_Texture_Unmap( GANDR.Device.Screen.DrawScreenLockImage ) ;

	// ����I��
	return 0 ;
}

// ����ʂ̓��e��\��ʂɕ`�悷��
extern	int		Graphics_Hardware_ScreenCopy_PF( int DrawTargetFrontScreenMode_Copy )
{
	// ����I��
	return 0 ;
}

// �f�B�X�v���C�̏����Z�b�g�A�b�v����
extern int Graphics_SetupDisplayInfo_PF( void )
{
	return 0 ;
}

// ���������M����҂�
extern	int		Graphics_Hardware_WaitVSync_PF( int SyncNum )
{
	return 0 ;
}

// ScreenFlip ���s���ɂu�r�x�m�b�҂������邩�ǂ�����ݒ肷��
extern	int		Graphics_SetWaitVSyncFlag_PF( int Flag )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return 0 ;
	}

	eglSwapInterval( GANDR.Device.Screen.Display, Flag ? 1 : 0 ) ;

	return 0 ;
}




// ����ʂƕ\��ʂ���������
extern	int		Graphics_ScreenFlipBase_PF( void )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I������
	Graphics_Android_RenderEnd() ;

	// �T�u�o�b�N�o�b�t�@�̓��e�����o�b�t�@�ɓ]������
	{
		RECT DestRect ;
		DWORD DestW ;
		DWORD DestH ;
		int BlendMode ;
		int NotWriteAlphaChannelFlag ;
		float VertexData[ 4 ][ 4 ] =
		{
			{ -1.0f,  1.0f,  0.0f, 0.0f },
			{  1.0f,  1.0f,  1.0f, 0.0f },
			{ -1.0f, -1.0f,  0.0f, 1.0f },
			{  1.0f, -1.0f,  1.0f, 1.0f },
		} ;

		if( g_AndroidSys.NativeWindow == NULL )
		{
			eglQuerySurface( GANDR.Device.Screen.Display, GANDR.Device.Screen.Surface, EGL_WIDTH,  &GANDR.Device.Screen.Width ) ;
			eglQuerySurface( GANDR.Device.Screen.Display, GANDR.Device.Screen.Surface, EGL_HEIGHT, &GANDR.Device.Screen.Height ) ;
		}
		else
		{
			GANDR.Device.Screen.Width = ANativeWindow_getWidth( ( ANativeWindow * )g_AndroidSys.NativeWindow ) ;
			GANDR.Device.Screen.Height = ANativeWindow_getHeight( ( ANativeWindow * )g_AndroidSys.NativeWindow ) ;
		}

		if( GSYS.Screen.FullScreenFitScalingFlag )
		{
			DestW = GANDR.Device.Screen.Width ;
			DestH = GANDR.Device.Screen.Height ;
		}
		else
		{
			DestW = GANDR.Device.Screen.Width ;
			DestH = GANDR.Device.Screen.Width * GANDR.Device.Screen.SubBackBufferTextureSizeY / GANDR.Device.Screen.SubBackBufferTextureSizeX ;
			if( DestH > ( DWORD )GANDR.Device.Screen.Height )
			{
				DestW = GANDR.Device.Screen.Height * GANDR.Device.Screen.SubBackBufferTextureSizeX / GANDR.Device.Screen.SubBackBufferTextureSizeY ;
				DestH = GANDR.Device.Screen.Height ;
			}
		}

		DestRect.left   = ( GANDR.Device.Screen.Width  - DestW ) / 2 ;
		DestRect.top    = ( GANDR.Device.Screen.Height - DestH ) / 2 ;
		DestRect.right  = DestRect.left + DestW ;
		DestRect.bottom = DestRect.top  + DestH ;

		// �u�����h���[�h���u�����h�����ɕύX
		BlendMode = GANDR.Device.State.BlendMode ;
		NotWriteAlphaChannelFlag = GANDR.Device.State.NotWriteAlphaChannelFlag ;
		Graphics_Android_DeviceState_SetBlendMode( DX_BLENDMODE_NOBLEND, FALSE ) ;

		// �`�����t���[���o�b�t�@�ɕύX( �ݒ�� Graphics_Android_DeviceState_RefreshRenderState �Ŗ߂� )
		glBindFramebuffer( GL_FRAMEBUFFER, 0 ) ;

		// �r���[�|�[�g���Z�b�g( �ݒ�� Graphics_Android_DeviceState_RefreshRenderState �Ŗ߂� )
		glViewport( DestRect.left, DestRect.top, DestRect.right - DestRect.left, DestRect.bottom - DestRect.top ) ;

		// �y�o�b�t�@�𖳌��ɂ���
		Graphics_Android_DeviceState_SetDepthEnable( FALSE ) ;
		Graphics_Android_DeviceState_SetDepthWriteEnable( FALSE ) ;

		// �J�����O�𖳌��ɂ���
		Graphics_Android_DeviceState_SetCullMode( DX_CULLING_NONE ) ;

		// ��ʂ��N���A( �ݒ�� Graphics_Android_DeviceState_RefreshRenderState �Ŗ߂� )
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ) ;
		glClear( GL_COLOR_BUFFER_BIT ) ;

		// �P���]���V�F�[�_�[���Z�b�g
		Graphics_Android_DeviceState_SetShader( &GANDR.Device.Shader.Base.StretchRect_Shader, FALSE ) ;

		// Uniform �̍X�V
		Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, 0 ) ;

		// �e�N�X�`�����Z�b�g( �ݒ�� Graphics_Android_DeviceState_RefreshRenderState �Ŗ߂� )
		glActiveTexture( GL_TEXTURE0 ) ;
		glBindTexture( GL_TEXTURE_2D, GANDR.Device.Screen.SubBackBufferTexture ) ;

		// ���[�U�[�w��̃������C���[�W�����邩�ǂ����ŏ����𕪊�
		if( GSYS.Screen.UserScreenImage != NULL )
		{
			BYTE *Src = ( BYTE * )GSYS.Screen.UserScreenImage ;
			BYTE *Dst = ( BYTE * )GANDR.Device.Screen.SubBackBufferTextureTempBuffer ;
			DWORD i ;
			DWORD Bytes ;

			// �l�C�e�B�u�ɑΉ����Ă��Ȃ��ꍇ�͕ϊ����Ă���]��
			if( GSYS.Screen.UserScreenImagePixelFormat == DX_USER_SCREEN_PIXEL_FORMAT_X8R8G8B8 &&
				GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_TEXTURE_FORMAT_BGRA8888 ] == FALSE )
			{
				Bytes = GANDR.Device.Screen.SubBackBufferTextureSizeX * GANDR.Device.Screen.SubBackBufferTextureSizeY * 4 ;
				for( i = 0 ; i < Bytes ; i += 4 )
				{
					Dst[ i + 2 ] = Src[ i + 0 ] ;
					Dst[ i + 1 ] = Src[ i + 1 ] ;
					Dst[ i + 0 ] = Src[ i + 2 ] ;
				}

				glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					0,
					0,
					GANDR.Device.Screen.SubBackBufferTextureSizeX,
					GANDR.Device.Screen.SubBackBufferTextureSizeY,
					GANDR.Device.Screen.SubBackBufferTexturePixelFormat,
					GANDR.Device.Screen.SubBackBufferTexturePixelType,
					GANDR.Device.Screen.SubBackBufferTextureTempBuffer
				) ;
			}
			else
			if( GSYS.Screen.UserScreenImagePixelFormat == DX_USER_SCREEN_PIXEL_FORMAT_X1R5G5B5 )
			{
				Bytes = GANDR.Device.Screen.SubBackBufferTextureSizeX * GANDR.Device.Screen.SubBackBufferTextureSizeY * 2 ;
				for( i = 0 ; i < Bytes ; i += 2 )
				{
					*( ( WORD * )&Dst[ i ] ) = ( WORD )( ( *( ( WORD * )&Src[ i ] ) << 1 ) | 1 ) ;
				}

				glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					0,
					0,
					GANDR.Device.Screen.SubBackBufferTextureSizeX,
					GANDR.Device.Screen.SubBackBufferTextureSizeY,
					GANDR.Device.Screen.SubBackBufferTexturePixelFormat,
					GANDR.Device.Screen.SubBackBufferTexturePixelType,
					GANDR.Device.Screen.SubBackBufferTextureTempBuffer
				) ;
			}
			else
			{
				glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					0,
					0,
					GANDR.Device.Screen.SubBackBufferTextureSizeX,
					GANDR.Device.Screen.SubBackBufferTextureSizeY,
					GANDR.Device.Screen.SubBackBufferTexturePixelFormat,
					GANDR.Device.Screen.SubBackBufferTexturePixelType,
					GSYS.Screen.UserScreenImage
				) ;
			}
		}
		else
		// �\�t�g�E�F�A�����_�����O���[�h�̏ꍇ�͂����Ńe�N�X�`�����X�V
		if( GSYS.Setting.NotUseHardware )
		{
			// �l�C�e�B�u�ɑΉ����Ă���ꍇ�͒P���]��
			if( GSYS.Screen.MainScreenColorBitDepth == 16 || GANDR.Device.Caps.Extensions[ ANDROID_GL_EXTENSION_TEXTURE_FORMAT_BGRA8888 ] )
			{
				glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					0,
					0,
					GANDR.Device.Screen.SubBackBufferTextureSizeX,
					GANDR.Device.Screen.SubBackBufferTextureSizeY,
					GANDR.Device.Screen.SubBackBufferTexturePixelFormat,
					GANDR.Device.Screen.SubBackBufferTexturePixelType,
					GSYS.SoftRender.MainBufferMemImg.UseImage
				) ;
			}
			else
			{
				BYTE *Src ;
				BYTE *Dst ;
				DWORD i ;
				DWORD Bytes ;

				// �Ή����Ă��Ȃ��ꍇ�͕ϊ����Ă���]��
				Src = GSYS.SoftRender.MainBufferMemImg.UseImage ;
				Dst = ( BYTE * )GANDR.Device.Screen.SubBackBufferTextureTempBuffer ;
				Bytes = GANDR.Device.Screen.SubBackBufferTextureSizeX * GANDR.Device.Screen.SubBackBufferTextureSizeY * 4 ;
				for( i = 0 ; i < Bytes ; i += 4 )
				{
					Dst[ i + 2 ] = Src[ i + 0 ] ;
					Dst[ i + 1 ] = Src[ i + 1 ] ;
					Dst[ i + 0 ] = Src[ i + 2 ] ;
				}

				glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					0,
					0,
					GANDR.Device.Screen.SubBackBufferTextureSizeX,
					GANDR.Device.Screen.SubBackBufferTextureSizeY,
					GANDR.Device.Screen.SubBackBufferTexturePixelFormat,
					GANDR.Device.Screen.SubBackBufferTexturePixelType,
					GANDR.Device.Screen.SubBackBufferTextureTempBuffer
				) ;
			}
		}

		// �g�僂�[�h���Z�b�g
		{
			GLint FilterMode = GL_LINEAR ;
			switch( GSYS.Screen.FullScreenScalingMode )
			{
			case DX_FSSCALINGMODE_BILINEAR :	FilterMode = GL_LINEAR ;	break ;
			case DX_FSSCALINGMODE_NEAREST :		FilterMode = GL_NEAREST ;	break ;
			}
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMode ) ;
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMode ) ;
		}

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ) ;

		// ���_�f�[�^�̃Z�b�g�A�b�v
		Graphics_Android_DeviceState_SetupShaderVertexData(
			&GANDR.Device.Shader.Base.StretchRect_Shader,
			&g_StretchRectVertexInputInfo,
			VertexData
		) ;

		// �`��
		glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 ) ;
		GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

		// �u�����h���[�h�����ɖ߂�
		Graphics_Android_DeviceState_SetBlendMode( BlendMode, NotWriteAlphaChannelFlag ) ;
	}

	// �X���b�v����
	eglSwapBuffers( GANDR.Device.Screen.Display, GANDR.Device.Screen.Surface );

	// ���܂ł̐ݒ�𕜋A����
	Graphics_Android_DeviceState_RefreshRenderState() ;

	return 0 ;
}

// ���C����ʂ̂y�o�b�t�@�̐ݒ��ύX����
extern	int		Graphics_Hardware_SetZBufferMode_PF( int ZBufferSizeX, int ZBufferSizeY, int ZBufferBitDepth )
{
	// ������
	return 0 ;
}

// �`���y�o�b�t�@�̃Z�b�g
extern	int		Graphics_Hardware_SetDrawZBuffer_PF( int DrawScreen, IMAGEDATA *Image )
{
	// ������
	return 0 ;
}

// ���݂̉�ʂ̃��t���b�V�����[�g���擾����
extern	int		Graphics_GetRefreshRate_PF( void )
{
	return 60 ;
}
























// ���ˑ����擾�֌W

// GetColor �� GetColor2 �Ŏg�p����J���[�f�[�^���擾����
extern const COLORDATA *Graphics_Hardware_GetMainColorData_PF( void )
{
	return Graphics_Android_GetDataFormatColorData( ANDROID_PIXEL_FORMAT_R8G8B8A8 ) ;
}

// �f�B�X�v���[�̃J���[�f�[�^�|�C���^�𓾂�
extern	const COLORDATA *Graphics_Hardware_GetDispColorData_PF( void )
{
	return Graphics_Android_GetDataFormatColorData( GANDR.Device.Caps.ScreenFormat ) ;
}

// �w����W�̐F���擾����
extern	DWORD Graphics_Hardware_GetPixel_PF( int x, int y )
{
	RECT            SrcRect ;
//	const COLORDATA *DestColorData ;
	BASEIMAGE       BufferImage ;
	DWORD           Ret = 0xffffffff ;
	int	Red, Green, Blue, Alpha ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// �`���o�b�t�@�����b�N
	SrcRect.left   = x ;
	SrcRect.right  = x + 1 ;
	SrcRect.top    = y ;
	SrcRect.bottom = y + 1 ;
	if( Graphics_Screen_LockDrawScreen( &SrcRect, &BufferImage, -1, -1, -1, TRUE, 0 ) < 0 )
	{
		return Ret ;
	}

	if( BufferImage.ColorData.FloatTypeFlag )
	{
		float RedF = 0.0f, GreenF = 0.0f, BlueF = 0.0f, AlphaF = 0.0f ;

		switch( BufferImage.ColorData.ChannelBitDepth )
		{
		case 16 :
			RedF   =                                        Float16ToFloat32( ( ( WORD * )BufferImage.GraphData )[ 0 ] ) ;
			GreenF = BufferImage.ColorData.ChannelNum > 1 ? Float16ToFloat32( ( ( WORD * )BufferImage.GraphData )[ 1 ] ) : 1.0f ;
			BlueF  = BufferImage.ColorData.ChannelNum > 2 ? Float16ToFloat32( ( ( WORD * )BufferImage.GraphData )[ 2 ] ) : 1.0f ;
			AlphaF = BufferImage.ColorData.ChannelNum > 3 ? Float16ToFloat32( ( ( WORD * )BufferImage.GraphData )[ 3 ] ) : 1.0f ;
			break ;

		case 32 :
			RedF   =                                        ( ( float * )BufferImage.GraphData )[ 0 ] ;
			GreenF = BufferImage.ColorData.ChannelNum > 1 ? ( ( float * )BufferImage.GraphData )[ 1 ] : 1.0f ;
			BlueF  = BufferImage.ColorData.ChannelNum > 2 ? ( ( float * )BufferImage.GraphData )[ 2 ] : 1.0f ;
			AlphaF = BufferImage.ColorData.ChannelNum > 3 ? ( ( float * )BufferImage.GraphData )[ 3 ] : 1.0f ;
			break ;
		}

		Red   = RedF   <= 0.0f ? 0 : ( RedF   >= 1.0f ? 255 : ( int )( RedF   * 255.0f ) ) ;
		Green = GreenF <= 0.0f ? 0 : ( GreenF >= 1.0f ? 255 : ( int )( GreenF * 255.0f ) ) ;
		Blue  = BlueF  <= 0.0f ? 0 : ( BlueF  >= 1.0f ? 255 : ( int )( BlueF  * 255.0f ) ) ;
		Alpha = AlphaF <= 0.0f ? 0 : ( AlphaF >= 1.0f ? 255 : ( int )( AlphaF * 255.0f ) ) ;
	}
	else
	{
		switch( BufferImage.ColorData.ColorBitDepth )
		{
		case 16 :
			NS_GetColor5( &BufferImage.ColorData, *( ( WORD   * )BufferImage.GraphData ), &Red, &Green, &Blue, &Alpha ) ;
			break ;

		case 32 :
			NS_GetColor5( &BufferImage.ColorData, *( ( DWORD  * )BufferImage.GraphData ), &Red, &Green, &Blue, &Alpha ) ;
			break ;
		}
	}

	Ret = 0xff000000 | ( ( ( unsigned int )Red ) << 16 ) | ( ( ( unsigned int )Green ) << 8 ) | ( ( unsigned int )Blue ) ;

	// �`���o�b�t�@���A�����b�N
	Graphics_Screen_UnlockDrawScreen() ;

	// �F��Ԃ�
	return Ret ;
}

// �w����W�̐F���擾����( float�^ )
extern COLOR_F Graphics_Hardware_GetPixelF_PF( int x, int y )
{
	RECT            SrcRect ;
//	const COLORDATA *DestColorData ;
	BASEIMAGE       BufferImage ;
	COLOR_F			Result ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// �`���o�b�t�@�����b�N
	SrcRect.left   = x ;
	SrcRect.right  = x + 1 ;
	SrcRect.top    = y ;
	SrcRect.bottom = y + 1 ;
	if( Graphics_Screen_LockDrawScreen( &SrcRect, &BufferImage, -1, -1, -1, TRUE, 0 ) < 0 )
	{
		return NS_GetColorF( -1.0f, -1.0f, -1.0f, -1.0f ) ;
	}

	if( BufferImage.ColorData.FloatTypeFlag )
	{
		switch( BufferImage.ColorData.ChannelBitDepth )
		{
		case 16 :
			Result.r =                                        Float16ToFloat32( ( ( WORD * )BufferImage.GraphData )[ 0 ] ) ;
			Result.g = BufferImage.ColorData.ChannelNum > 1 ? Float16ToFloat32( ( ( WORD * )BufferImage.GraphData )[ 1 ] ) : 1.0f ;
			Result.b = BufferImage.ColorData.ChannelNum > 2 ? Float16ToFloat32( ( ( WORD * )BufferImage.GraphData )[ 2 ] ) : 1.0f ;
			Result.a = BufferImage.ColorData.ChannelNum > 3 ? Float16ToFloat32( ( ( WORD * )BufferImage.GraphData )[ 3 ] ) : 1.0f ;
			break ;

		case 32 :
			Result.r =                                        ( ( float * )BufferImage.GraphData )[ 0 ] ;
			Result.g = BufferImage.ColorData.ChannelNum > 1 ? ( ( float * )BufferImage.GraphData )[ 1 ] : 1.0f ;
			Result.b = BufferImage.ColorData.ChannelNum > 2 ? ( ( float * )BufferImage.GraphData )[ 2 ] : 1.0f ;
			Result.a = BufferImage.ColorData.ChannelNum > 3 ? ( ( float * )BufferImage.GraphData )[ 3 ] : 1.0f ;
			break ;
		}
	}
	else
	{
		int Red, Green, Blue, Alpha ;

		switch( BufferImage.ColorData.ColorBitDepth )
		{
		case 16 :
			NS_GetColor5( &BufferImage.ColorData, *( ( WORD   * )BufferImage.GraphData ), &Red, &Green, &Blue, &Alpha ) ;
			break ;

		case 32 :
			NS_GetColor5( &BufferImage.ColorData, *( ( DWORD  * )BufferImage.GraphData ), &Red, &Green, &Blue, &Alpha ) ;
			break ;
		}

		Result.r = ( float )Red   / 255.0f ;
		Result.g = ( float )Green / 255.0f ;
		Result.b = ( float )Blue  / 255.0f ;
		Result.a = ( float )Alpha / 255.0f ;
	}

	// �`���o�b�t�@���A�����b�N
	Graphics_Screen_UnlockDrawScreen() ;

	// �F��Ԃ�
	return Result ;
}

























// ���ˑ��摜�֌W

// YUV�T�[�t�F�X���g���� Theora ����̓��e���O���t�B�b�N�X�n���h���̃e�N�X�`���ɓ]������
extern	int		Graphics_Hardware_UpdateGraphMovie_TheoraYUV_PF( MOVIEGRAPH *Movie, IMAGEDATA *Image )
{
	// ������
	return 0 ;
}

// �O���t�B�b�N�������̈�̃��b�N
extern	int		Graphics_Hardware_GraphLock_PF( IMAGEDATA *Image, COLORDATA **ColorDataP, int WriteOnly )
{
	COLORDATA    *TargetColorData ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// �J���[�t�H�[�}�b�g���擾����
	TargetColorData = Graphics_Android_GetDataFormatColorData( GANDR.Device.Caps.TextureFormat[ Image->Orig->ColorFormat ] ) ;

	// �W���t�H�[�}�b�g�ȊO�ł̓��b�N�ł��Ȃ�
	if( TargetColorData->Format != DX_BASEIMAGE_FORMAT_NORMAL )
	{
		return -1 ;
	}

	// �e���|�����o�b�t�@���m�ۂ���
	Image->LockImagePitch	= ( DWORD )( TargetColorData->PixelByte * Image->WidthI ) ;
	Image->LockImage		= ( BYTE * )DXALLOC( Image->LockImagePitch * Image->HeightI ) ;
	if( Image->LockImage == NULL )
	{
		DXST_LOGFILE_ADDUTF16LE( "\xed\x30\xc3\x30\xaf\x30\x28\x75\xc6\x30\xf3\x30\xdd\x30\xe9\x30\xea\x30\xa4\x30\xe1\x30\xfc\x30\xb8\x30\x3c\x68\x0d\x7d\x28\x75\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"���b�N�p�e���|�����C���[�W�i�[�p�������̊m�ۂɎ��s���܂���\n" @*/ ) ;
		goto ERR ;
	}

	// �������ݐ�p�ł͂Ȃ��ꍇ�̓e���|�����o�b�t�@�Ƀf�[�^��]������
	if( WriteOnly == FALSE )
	{
		int                  i ;
		BYTE                *Dest ;
		BYTE                *Src ;
//		DWORD                WidthByte ;
		BASEIMAGE            MapBaseImage ;
		void *				 MapTempImage ;
		IMAGEDATA_HARD_DRAW *DrawTex ;
		COLORDATA			SrcColorData ;
		POINT				DestPoint = { 0, 0 } ;
		RECT				SrcRect ;

		NS_CreateARGB8ColorData( &SrcColorData ) ;

		// �`����̐������J��Ԃ�
		DrawTex = Image->Hard.Draw ;
		for( i = 0 ; i < Image->Hard.DrawNum ; i ++, DrawTex ++ )
		{
			// �}�b�v
			if( Graphics_Android_Texture_Map(
				DrawTex->Tex->PF->Texture.TextureBuffer,
				DrawTex->Tex->PF->FrameBuffer,
				DrawTex->Tex->PF->Texture.Width,
				DrawTex->Tex->PF->Texture.Height,
				NULL,
				&MapBaseImage,
				&MapTempImage ) < 0 )
			{
				goto ERR ;
			}

			// �]��
			Src  = ( BYTE * )MapBaseImage.GraphData + DrawTex->UsePosXI  * TargetColorData->PixelByte + DrawTex->UsePosYI  * MapBaseImage.Pitch ;
			Dest = Image->LockImage                 + DrawTex->DrawPosXI * TargetColorData->PixelByte + DrawTex->DrawPosYI * Image->LockImagePitch ;
//			WidthByte = ( DWORD )( DrawTex->WidthI * TargetColorData->PixelByte ) ;
			SrcRect.left	= 0 ;
			SrcRect.top		= 0 ;
			SrcRect.right	= MapBaseImage.Width ;
			SrcRect.bottom	= MapBaseImage.Height ;
			NS_GraphColorMatchBltVer2(
				Dest, Image->LockImagePitch, TargetColorData,
				Src,  MapBaseImage.Pitch,    &SrcColorData,
				NULL, 0,                     NULL,
				DestPoint, &SrcRect, FALSE,
				FALSE, 0,
				BASEIM.ImageShavedMode, FALSE,
				FALSE, FALSE,
				FALSE
			) ;

			// �}�b�v�̉���
			Graphics_Android_Texture_Unmap( MapTempImage ) ;
		}
	}

	// �J���[�f�[�^�̃A�h���X��ۑ�
	*ColorDataP = TargetColorData ;

	// ����I��
	return 0 ;

ERR :

	if( Image->LockImage != NULL )
	{
		DXFREE( Image->LockImage ) ;
		Image->LockImage = NULL ;
	}

	// �G���[�I��
	return -1 ;
}

// �O���t�B�b�N�������̈�̃��b�N����
extern	int		Graphics_Hardware_GraphUnlock_PF( IMAGEDATA *Image )
{
	COLORDATA           *ColorData ;
	BASEIMAGE            BaseImage ;
	BASEIMAGE            AlphaBaseImage ;
	RECT                 Rect ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �J���[�t�H�[�}�b�g���擾����
	ColorData = Graphics_Android_GetDataFormatColorData( GANDR.Device.Caps.TextureFormat[ Image->Orig->ColorFormat ] ) ;

	// ��{�C���[�W���\�z����
	_MEMSET( &AlphaBaseImage, 0, sizeof( AlphaBaseImage ) ) ;
	BaseImage.ColorData      = *ColorData ;
	BaseImage.Width          = Image->WidthI ;
	BaseImage.Height         = Image->HeightI ;
	BaseImage.Pitch          = ColorData->PixelByte * Image->WidthI ;
	BaseImage.GraphData      = Image->LockImage ;
	BaseImage.MipMapCount    = 0 ;
	BaseImage.GraphDataCount = 0 ;

	// �]��
	Rect.left   = 0 ;
	Rect.top    = 0 ;
	Rect.right  = Image->WidthI ;
	Rect.bottom = Image->HeightI ;
	Graphics_Hardware_BltBmpOrBaseImageToGraph3_PF( &Rect, 0, 0, Image->HandleInfo.Handle, &BaseImage, &AlphaBaseImage, FALSE, FALSE, TRUE, FALSE ) ;

	// ���b�N�C���[�W�̉��
	if( Image->LockImage )
	{
		DXFREE( Image->LockImage ) ;
		Image->LockImage = NULL ;
	}

	// ����I��
	return 0 ;
}

// �O���t�B�b�N�̂y�o�b�t�@�̏�Ԃ�ʂ̃O���t�B�b�N�̂y�o�b�t�@�ɃR�s�[����( DestGrHandle �� SrcGrHandle ���y�o�b�t�@�������Ă���`��\�摜�ŁA���A���`�G�C���A�X�摜�ł͂Ȃ����Ƃ����� )
extern	int		Graphics_Hardware_CopyGraphZBufferImage_PF( IMAGEDATA *DestImage, IMAGEDATA *SrcImage )
{
	// ������
	return 0 ;
}

// �摜�f�[�^�̏�����
extern	int		Graphics_Hardware_InitGraph_PF( void )
{
	// ����I��
	return 0 ;
}

// �O���t�B�b�N�����̐F�œh��Ԃ�
extern	int		Graphics_Hardware_FillGraph_PF( IMAGEDATA *Image, int Red, int Green, int Blue, int Alpha, int ASyncThread )
{
	// �W���������s��
	return 2 ;
}

// �`��\�摜��o�b�N�o�b�t�@����w��̈�̃O���t�B�b�N���擾����
extern	int		Graphics_Hardware_GetDrawScreenGraphBase_PF( IMAGEDATA *Image, IMAGEDATA *TargetImage, int TargetScreen, int TargetScreenSurface, int TargetScreenMipLevel, int TargetScreenWidth, int TargetScreenHeight, int x1, int y1, int x2, int y2, int destX, int destY )
{
	RECT SrcRect ;
	RECT DestRect ;
	RECT Rect ;
	int Width, Height ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I�����Ă���
	Graphics_Android_RenderEnd() ;

	// ���ƍ������v�Z
	Width  = x2 - x1 ;
	Height = y2 - y1 ;

	// �]����ƂȂ�T�[�t�F�X���`��\�e�N�X�`���������ꍇ�͒P���ɓ]��
	if( Image->Orig->FormatDesc.DrawValidFlag )
	{
//		GLuint TargetFrameBuffer ;
		GLuint TargetTexture ;
		GLuint TargetWidth ;
		GLuint TargetHeight ;

		// ��荞�݌��ƂȂ�e�N�X�`���̌���

		// �`��\�摜���Ώۂ̏ꍇ
		if( TargetImage )
		{
//			TargetFrameBuffer = TargetImage->Orig->Hard.Tex[ 0 ].PF->FrameBuffer ;
			TargetTexture     = TargetImage->Orig->Hard.Tex[ 0 ].PF->Texture.TextureBuffer ;
			TargetWidth       = TargetImage->Orig->Hard.Tex[ 0 ].PF->Texture.Width ;
			TargetHeight      = TargetImage->Orig->Hard.Tex[ 0 ].PF->Texture.Height ;
		}
		else
		{
//			TargetFrameBuffer = GANDR.Device.Screen.SubBackBufferFrameBuffer ;
			TargetTexture     = GANDR.Device.Screen.SubBackBufferTexture ;
			TargetWidth       = GANDR.Device.Screen.SubBackBufferTextureSizeX ;
			TargetHeight      = GANDR.Device.Screen.SubBackBufferTextureSizeY ;
		}

		SrcRect.left    = x1 ;
		SrcRect.top     = y1 ;
		SrcRect.right   = x2 ;
		SrcRect.bottom  = y2 ;

		DestRect.left   = destX ;
		DestRect.top    = destY ;
		DestRect.right  = destX + Width ;
		DestRect.bottom = destY + Height ;

		Graphics_Android_StretchRect(
			TargetTexture, TargetWidth, TargetHeight, &SrcRect,
			Image->Orig->Hard.Tex[ 0 ].PF->FrameBuffer,
			Image->Orig->Hard.Tex[ 0 ].PF->Texture.Width,
			Image->Orig->Hard.Tex[ 0 ].PF->Texture.Height,
			&DestRect
		) ; 

		// �`����I�����Ă���
		Graphics_Android_RenderEnd() ;
	}
	else
	// �ʏ�̃e�N�X�`���������ꍇ�͍ŏ��Ƀ��b�N������
	{
		// �`���o�b�t�@�����b�N
		BASEIMAGE LockImage ;
		SrcRect.left   = x1 ;
		SrcRect.top    = y1 ;
		SrcRect.right  = x2 ;
		SrcRect.bottom = y2 ;
		if( Graphics_Screen_LockDrawScreen( &SrcRect, &LockImage, TargetScreen, TargetScreenSurface, TargetScreenMipLevel, TRUE, 0 ) < 0 )
		{
			return -1 ;
		}

		// �e�N�X�`���ɓ]��
		Rect.left   = 0 ;
		Rect.top    = 0 ;
		Rect.right  = LockImage.Width ;
		Rect.bottom = LockImage.Height ;
		Graphics_Image_BltBmpOrBaseImageToGraph3(
			&Rect,
			destX, destY,
			Image->HandleInfo.Handle,
			&LockImage, NULL,
			FALSE,
			FALSE,
			FALSE
		) ;

		// �`���o�b�t�@�̃A�����b�N
		Graphics_Screen_UnlockDrawScreen() ;
	}

	// ����I��
	return 0 ;
}

static int Graphics_Android_BltBmpOrBaseImageToGraph3_MipMapBlt(
	      IMAGEDATA_ORIG	*Orig,
	const RECT				*SrcRect,
	const RECT				*DestRect,
	      GLuint			UseTex,
	      int				TexWidth,
	      int				TexHeight,
	const BASEIMAGE			*RgbBaseImage,
	const BASEIMAGE			*AlphaBaseImage,
	      int				DestColorFormat,
	      int				RedIsAlphaFlag,
	      int				UseTransColorConvAlpha,
	      int				ASyncThread
)
{
	int			ImageSize ;
	int			ImageNum ;
	void		*ImageBuffer ;
	int			i ;
	int			j ;
	DWORD		MipMapCount ;
	const COLORDATA			*DestColor ;
	PIXELFORMAT_INFO_ANDR	*PixelFormat ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �e�N�X�`���̃J���[�����擾����
	DestColor = Graphics_Android_GetDataFormatColorData( DestColorFormat ) ;
	PixelFormat = &g_AndroidPixelFormat[ DestColorFormat ] ;

	MipMapCount = Orig->Hard.MipMapCount > 16 ? 16 : Orig->Hard.MipMapCount ;

	ImageNum = Orig->FormatDesc.CubeMapTextureFlag ? CUBEMAP_SURFACE_NUM : 1 ;

	// �]���悪�e�N�X�`���S�̂ŁA���]�����Ƀ~�b�v�}�b�v��񂪂���ꍇ�͕���
	if( DestRect->left == 0 && DestRect->right  == TexWidth  &&
		DestRect->top  == 0 && DestRect->bottom == TexHeight &&
		RgbBaseImage->MipMapCount >= Orig->Hard.MipMapCount )
	{
		ImageBuffer = RgbBaseImage->GraphData ;
		for( i = 0 ; i < ImageNum ; i ++ )
		{
			int Width ;
			int Height ;

			ImageSize = RgbBaseImage->Width * RgbBaseImage->Height * RgbBaseImage->ColorData.ColorBitDepth / 8 ;
			Width  = RgbBaseImage->Width ;
			Height = RgbBaseImage->Height ;
			for( j = 0 ; ( DWORD )j < MipMapCount ; j ++ )
			{
				// �e�N�X�`���֓]��
				glTexSubImage2D_ASync(
					UseTex,
					GL_TEXTURE_2D,
					i,
					0,
					0,
					Width,
					Height,
					PixelFormat->Format,
					PixelFormat->Type,
					ImageBuffer,
					ASyncThread
				) ;

				// ���̃C���[�W�̃T�C�Y���Z�b�g
				Width  >>= 1 ;
				Height >>= 1 ;
				if( Width  == 0 ) Width  = 1 ;
				if( Height == 0 ) Height = 1 ;

				// �]�����A�h���X��i�߂�
				ImageBuffer  = ( BYTE * )ImageBuffer + ImageSize ;
				ImageSize   /= 4 ;
				if( ImageSize < 8 )
				{
					ImageSize = 8 ;
				}
			}
		}
	}
	else
	{
		int		ImageW ;
		int		ImageH ;
		int		ImageDW ;
		int		ImageDH ;
		int		ImageSW ;
		int		ImageSH ;
		void	*Image1 ;
		void	*Image2 ;
		void	*ImageD ;
		void	*ImageS ;
		int		ImagePitch ;
		int		ImagePitchD ;
		int		ImagePitchS ;
		int		ts ;
		POINT	DestPoint ;
		int		RgbImageSize ;
		int		AlphaImageSize ;

		DestPoint.x = 0 ;
		DestPoint.y = 0 ;

		// �ꎞ�o�b�t�@�Ɋi�[
		ts = DestRect->right  - DestRect->left ;
		for( ImageW = 1 ; ImageW < ts ; ImageW <<= 1 ){}
		ts = DestRect->bottom - DestRect->top  ;
		for( ImageH = 1 ; ImageH < ts ; ImageH <<= 1 ){}
		ImagePitch  = DestColor->PixelByte * ImageW ;
		ImageSize   = ImagePitch * ImageH ;

		// �s�b�`�͂S�̔{���ɂ���
		ImagePitch = ( ImagePitch + 3 ) / 4 * 4 ;

		if( ASyncThread )
		{
			ImageBuffer = DXALLOC( ( size_t )( ImageSize * 2 ) ) ;
			if( ImageBuffer == NULL )
			{
				DXST_LOGFILE_ADDUTF16LE( "\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\x78\x30\xe2\x8e\x01\x90\x59\x30\x8b\x30\x3b\x75\xcf\x50\x92\x30\x00\x4e\x42\x66\x84\x76\x6b\x30\x3c\x68\x0d\x7d\x59\x30\x8b\x30\xe1\x30\xe2\x30\xea\x30\x18\x98\xdf\x57\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�e�N�X�`���֓]������摜���ꎞ�I�Ɋi�[���郁�����̈�̊m�ۂɎ��s���܂���\n" @*/ ) ;
				return -1 ;
			}
		}
		else
		{
			if( Graphics_Android_Texture_SetupCommonBuffer( ( unsigned int )( ImageSize * 2 ) ) < 0 )
			{
				return -1 ;
			}
			ImageBuffer = GANDR.Texture.CommonBuffer ;
		}
		Image1      = ImageBuffer ;
		Image2      = ( BYTE * )Image1 + ImageSize ;

		RgbImageSize   = RgbBaseImage->Pitch   * RgbBaseImage->Height ;
		AlphaImageSize = AlphaBaseImage->Pitch * AlphaBaseImage->Height ;
		for( i = 0 ; i < ImageNum ; i ++ )
		{
			// �~�b�v�}�b�v�̐[�������J��Ԃ�
			ImageSW     = ImageW ;
			ImageSH     = ImageH ;
			ImagePitchS = ImagePitch ;
			ImageDW     = ImageW ;
			ImageDH     = ImageH ;
			ImagePitchD = ImagePitch ;
			for( j = 0 ; j < Orig->Hard.MipMapCount ; j ++ )
			{
				// �k���摜�̍쐬
				if( j == 0 )
				{
					// level0 �̎��͓��{�̏o�̓t�H�[�}�b�g�摜���쐬����
					NS_GraphColorMatchBltVer2(
						Image1,                                                   ImagePitch,            DestColor,
						( BYTE * )RgbBaseImage->GraphData   + RgbImageSize   * i, RgbBaseImage->Pitch,   &RgbBaseImage->ColorData,
						( BYTE * )AlphaBaseImage->GraphData + AlphaImageSize * i, AlphaBaseImage->Pitch, &AlphaBaseImage->ColorData,
						DestPoint, SrcRect, FALSE,
						UseTransColorConvAlpha && ( DestColor->AlphaWidth != 0 && AlphaBaseImage->GraphData == NULL ), Orig->TransCode,
						BASEIM.ImageShavedMode, FALSE,
						RedIsAlphaFlag, FALSE,
						FALSE ) ;
					ImageD = Image1 ;
					ImagePitchD = ImagePitch ;
				}
				else
				{
					if( j & 1 )
					{
						ImageS = Image1 ;
						ImageD = Image2 ;
					}
					else
					{
						ImageS = Image2 ;
						ImageD = Image1 ;
					}

					GraphHalfScaleBlt( DestColor, ImageD, ImagePitchD, ImageS, ImagePitchS, 0, 0, 0, 0, ImageSW, ImageSH ) ;
				}

				// �e�N�X�`���ɓ]��
				{
					RECT TempRect ;

					TempRect.left   = DestRect->left   >> j ;
					TempRect.top    = DestRect->top    >> j ;
					TempRect.right  = DestRect->right  >> j ;
					TempRect.bottom = DestRect->bottom >> j ;
					if( TempRect.right == TempRect.left )
					{
						TempRect.right = TempRect.left + 1 ;
					}
					if( TempRect.bottom == TempRect.top )
					{
						TempRect.bottom = TempRect.top + 1 ;
					}

					glTexSubImage2D_ASync(
						UseTex,
						GL_TEXTURE_2D,
						j,
						TempRect.left,
						TempRect.top,
						TempRect.right  - TempRect.left,
						TempRect.bottom - TempRect.top,
						PixelFormat->Format,
						PixelFormat->Type,
						ImageD,
						ASyncThread
					) ;
				}

				// ���̃C���[�W�̃T�C�Y���Z�b�g
				ImageSW = ImageDW ;
				ImageSH = ImageDH ;
				ImagePitchS = ImagePitchD ;
				ImageDW >>= 1 ;
				ImageDH >>= 1 ;
				if( ImageDW == 0 ) ImageDW = 1 ;
				if( ImageDH == 0 ) ImageDH = 1 ;
				ImagePitchD = ImageDW * DestColor->PixelByte ;

				// �s�b�`�͂S�̔{���ɂ���
				ImagePitchD = ( ImagePitchD + 3 ) / 4 * 4 ;
			}
		}

		// �������̉��
		if( ASyncThread )
		{
			DXFREE( ImageBuffer ) ;
		}
	}

	// ����I��
	return 0 ;
}

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
)
{
	int				i ;
	int				k ;
	POINT			DestPoint ;
	int				H ;
	BYTE			*DestAddr ;
	BYTE			*SrcRgbAddr ;
	BYTE			*SrcAlphaAddr ;
	int				RightLineFillFlag ;
	int				BottomLineFillFlag ;
	DWORD			ImageSize ;
	DWORD			AlphaImageSize ;
	const COLORDATA *DestColor ;
	PIXELFORMAT_INFO_ANDR	*PixelFormat ;
	void			*TempBuffer = NULL ;
	unsigned int	TempBufferWidth ;
	unsigned int	TempBufferHeight ;
	unsigned int	TempBufferSize ;
	int				TempBufferPitch = 0 ;

	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �e�N�X�`���̃J���[�����擾����
	DestColor = Graphics_Android_GetDataFormatColorData( DestColorFormat ) ;
	PixelFormat = &g_AndroidPixelFormat[ DestColorFormat ] ;

	DestPoint.x = 0 ;
	DestPoint.y = 0 ;

	RightLineFillFlag  = FALSE ;
	BottomLineFillFlag = FALSE ;

	if( TexUseWidth  < TexWidth  && TexUseWidth  == DestRect->right )
	{
		RightLineFillFlag = TRUE ;
	}
	if( TexUseHeight < TexHeight && TexUseHeight == DestRect->bottom )
	{
		BottomLineFillFlag = TRUE ;
	}

	TempBufferWidth  = ( unsigned int )( DestRect->right  - DestRect->left ) ;
	TempBufferHeight = ( unsigned int )( DestRect->bottom - DestRect->top ) ;
	TempBufferPitch  =                   ( TempBufferWidth  + ( RightLineFillFlag  ? 1 : 0 ) ) * DestColor->PixelByte ;
	TempBufferSize   = ( unsigned int )( ( TempBufferHeight + ( BottomLineFillFlag ? 1 : 0 ) ) * TempBufferPitch ) ;

	// �s�b�`�͂S�̔{���ɂ���
	TempBufferPitch = ( TempBufferPitch + 3 ) / 4 * 4 ;

	if( ASyncThread )
	{
		TempBuffer      = DXALLOC( TempBufferSize ) ;
		if( TempBuffer == NULL )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\x6b\x30\x3b\x75\xcf\x50\x92\x30\xe2\x8e\x01\x90\x59\x30\x8b\x30\x5f\x30\x81\x30\x6e\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x5b\x00\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x69\x00\x63\x00\x73\x00\x5f\x00\x50\x00\x53\x00\x34\x00\x5f\x00\x42\x00\x6c\x00\x74\x00\x42\x00\x6d\x00\x70\x00\x4f\x00\x72\x00\x42\x00\x61\x00\x73\x00\x65\x00\x49\x00\x6d\x00\x61\x00\x67\x00\x65\x00\x54\x00\x6f\x00\x47\x00\x72\x00\x61\x00\x70\x00\x68\x00\x33\x00\x5f\x00\x4e\x00\x6f\x00\x4d\x00\x69\x00\x70\x00\x4d\x00\x61\x00\x70\x00\x42\x00\x6c\x00\x74\x00\x5d\x00\x0a\x00\x00"/*@ L"�e�N�X�`���ɉ摜��]�����邽�߂̃������̊m�ۂɎ��s���܂���[Graphics_Android_BltBmpOrBaseImageToGraph3_NoMipMapBlt]\n" @*/ )) ;
			return -1 ;
		}
	}
	else
	{
		if( Graphics_Android_Texture_SetupCommonBuffer( TempBufferSize ) < 0 )
		{
			return -1 ;
		}
		TempBuffer      = GANDR.Texture.CommonBuffer ;
	}

	for( i = 0 ; i < ImageNum ; i ++ )
	{
		// �]������

		ImageSize      = ( DWORD )( RgbBaseImage->Pitch   * RgbBaseImage->Height   ) ;
		AlphaImageSize = ( DWORD )( AlphaBaseImage->Pitch * AlphaBaseImage->Height ) ;

		SrcRgbAddr   = ( BYTE * )RgbBaseImage->GraphData   + i * ImageSize ;
		SrcAlphaAddr = ( BYTE * )AlphaBaseImage->GraphData + i * AlphaImageSize ;

		// �e���|�����o�b�t�@�ɉ摜�f�[�^��]������
		{
			NS_GraphColorMatchBltVer2(
				TempBuffer,     TempBufferPitch,       DestColor,
				SrcRgbAddr,     RgbBaseImage->Pitch,   &RgbBaseImage->ColorData,
				SrcAlphaAddr,   AlphaBaseImage->Pitch, &AlphaBaseImage->ColorData,
				DestPoint, SrcRect, FALSE,
				UseTransColorConvAlpha && ( DestColor->AlphaWidth != 0 && AlphaBaseImage->GraphData == NULL ), TransCode,
				BASEIM.ImageShavedMode, FALSE,
				RedIsAlphaFlag, FALSE,
				FALSE
			) ;

			if( BottomLineFillFlag )
			{
				_MEMCPY( ( BYTE * )TempBuffer + TempBufferHeight * TempBufferPitch,
						 ( BYTE * )TempBuffer + ( TempBufferHeight - 1 ) * TempBufferPitch,
						 ( size_t )( DestColor->PixelByte * ( SrcRect->right - SrcRect->left ) ) ) ;
			}
			if( RightLineFillFlag )
			{
				H = SrcRect->bottom - SrcRect->top ;
				DestAddr = ( BYTE * )TempBuffer + TempBufferWidth * DestColor->PixelByte ;
				switch( DestColor->PixelByte )
				{
				case 2 :
					for( k = 0 ; k < H ; k ++, DestAddr += TempBufferPitch )
					{
						*( ( WORD * )DestAddr ) = *( ( WORD * )DestAddr - 1 ) ;
					}
					break ;

				case 4 :
					for( k = 0 ; k < H ; k ++, DestAddr += TempBufferPitch )
					{
						*( ( DWORD * )DestAddr ) = *( ( DWORD * )DestAddr - 1 ) ;
					}
					break ;
				}
			}
			if( BottomLineFillFlag && RightLineFillFlag )
			{
				DestAddr = ( BYTE * )TempBuffer + TempBufferHeight * TempBufferPitch + TempBufferWidth * DestColor->PixelByte ;
				switch( DestColor->PixelByte )
				{
				case 2 : *( ( WORD  * )DestAddr ) = *( ( WORD  * )( DestAddr - TempBufferPitch ) - 1 ) ; break ;
				case 4 : *( ( DWORD * )DestAddr ) = *( ( DWORD * )( DestAddr - TempBufferPitch ) - 1 ) ; break ;
				}
			}

			// �e�N�X�`���֓]��
			glTexSubImage2D_ASync(
				UseTex,
				GL_TEXTURE_2D,
				0,
				DestRect->left,
				DestRect->top,
				DestRect->right  - DestRect->left + ( RightLineFillFlag ? 1 : 0 ),
				DestRect->bottom - DestRect->top + ( BottomLineFillFlag ? 1 : 0 ),
				PixelFormat->Format,
				PixelFormat->Type,
				TempBuffer,
				ASyncThread
			) ;
		}
	}


	if( ASyncThread )
	{
		if( TempBuffer != NULL )
		{
			DXFREE( TempBuffer ) ;
			TempBuffer = NULL ;
		}
	}

	// ����I��
	return 0 ;
}

// Android �̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]�����邽�߂̊֐�
extern	int		Graphics_Hardware_BltBmpOrBaseImageToGraph3_PF(
	const RECT		*SrcRect,
	      int		DestX,
	      int		DestY,
	      int		GrHandle,
	const BASEIMAGE	*RgbBaseImage,
	const BASEIMAGE	*AlphaBaseImage,
	      int		RedIsAlphaFlag,
	      int		UseTransColorConvAlpha,
	      int		TargetOrig,
	      int		ASyncThread
)
{
	IMAGEDATA					*Image ;
	IMAGEDATA_ORIG				*Orig ;
	IMAGEDATA_ORIG_HARD_TEX		*OrigTex ;
	IMAGEDATA_HARD_DRAW			*DrawTex ;
//	int							ImageNum ;
	int							i ;
//	POINT						DestPoint ;
	RECT						DestRect ;
	RECT						MoveRect ;
	int							IsDXT ;
	GLuint						UseTex ;
	int							SrcWidth ;
	int							SrcHeight ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO_ASYNC( ASyncThread ) ;

	// DXT���k�̉摜���𒲂ׂĂ���
	IsDXT =
		( RgbBaseImage->ColorData.Format == DX_BASEIMAGE_FORMAT_DXT1 ||
		  RgbBaseImage->ColorData.Format == DX_BASEIMAGE_FORMAT_DXT2 ||
		  RgbBaseImage->ColorData.Format == DX_BASEIMAGE_FORMAT_DXT3 ||
		  RgbBaseImage->ColorData.Format == DX_BASEIMAGE_FORMAT_DXT4 ||
		  RgbBaseImage->ColorData.Format == DX_BASEIMAGE_FORMAT_DXT5 ||
		  RgbBaseImage->ColorData.Format == DX_BASEIMAGE_FORMAT_BC7_UNORM ||
		  RgbBaseImage->ColorData.Format == DX_BASEIMAGE_FORMAT_BC7_UNORM_SRGB ) ? TRUE : FALSE ;

	// �]�������v�Z���Ă���
	SrcWidth  = SrcRect->right  - SrcRect->left ;
	SrcHeight = SrcRect->bottom - SrcRect->top ;
	if( SrcWidth <= 0 || SrcHeight <= 0 )
	{
		return 0 ;
	}

	// �G���[����
	if( ASyncThread )
	{
		if( GRAPHCHK_ASYNC( GrHandle, Image ) )
		{
			return -1 ;
		}
	}
	else
	{
		if( GRAPHCHK( GrHandle, Image ) )
		{
			return -1 ;
		}
	}
	Orig = Image->Orig ;

	// �C���[�W�̐����Z�b�g
//	ImageNum = RgbBaseImage->GraphDataCount == 0 ? 1 : RgbBaseImage->GraphDataCount ;

	// �]���ʒu�̃Z�b�g
//	DestPoint.x = 0 ;
//	DestPoint.y = 0 ;

	// �]���Ώۂ��I���W�i���摜�ɑ΂��Ă��ǂ����ŏ����𕪊�
	if( TargetOrig == TRUE )
	{
		// �I���W�i���摜�ɑ΂��Ă̏ꍇ

		// �e�N�X�`���̐������J��Ԃ�
		OrigTex = Orig->Hard.Tex ;
		for( i = 0 ; i < Orig->Hard.TexNum ; i ++, OrigTex ++ )
		{
			// �]����`�̍쐬
			if( Graphics_Image_BltBmpOrBaseImageToGraph3_Make_OrigTex_MoveRect(
					OrigTex,
					SrcRect,
					SrcWidth,
					SrcHeight,
					DestX,
					DestY,
					&DestRect,
					&MoveRect,
					IsDXT ) < 0 )
			{
				continue ;
			}

			UseTex = OrigTex->PF->Texture.TextureBuffer ;

			// �~�b�v�}�b�v���ǂ����ŏ����𕪊�
			if( Orig->Hard.MipMapCount > 1 )
			{
				if( Graphics_Android_BltBmpOrBaseImageToGraph3_MipMapBlt(
						Orig,
						&MoveRect,
						&DestRect,
						UseTex,
						OrigTex->TexWidth,
						OrigTex->TexHeight,
						RgbBaseImage,
						AlphaBaseImage,
						GANDR.Device.Caps.TextureFormat[ Orig->ColorFormat ],
						RedIsAlphaFlag,
						UseTransColorConvAlpha,
						ASyncThread ) < 0 )
					goto ERR ;
			}
			else
			{
				if( Graphics_Android_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
						&MoveRect,
						&DestRect,
						UseTex,
						Orig->FormatDesc.CubeMapTextureFlag ? CUBEMAP_SURFACE_NUM : 1,
						OrigTex->TexWidth,
						OrigTex->TexHeight,
						OrigTex->UseWidth,
						OrigTex->UseHeight,
						RgbBaseImage,
						AlphaBaseImage,
						GANDR.Device.Caps.TextureFormat[ Orig->ColorFormat ],
						RedIsAlphaFlag,
						UseTransColorConvAlpha,
						Orig->TransCode,
						ASyncThread ) < 0 )
					goto ERR ;
			}
		}
	}
	else
	{
		// �I���W�i���摜�ɑ΂��Ăł͂Ȃ��ꍇ

		// �`����̐������J��Ԃ�
		DrawTex = Image->Hard.Draw ;
//		DestPoint.x = 0 ;
//		DestPoint.y = 0 ;
		for( i = 0 ; i < Image->Hard.DrawNum ; i ++, DrawTex ++ )
		{
			// �]����`�̍쐬
			if( Graphics_Image_BltBmpOrBaseImageToGraph3_Make_DrawTex_MoveRect(
					DrawTex,
					SrcRect,
					SrcWidth,
					SrcHeight,
					DestX,
					DestY,
					&DestRect,
					&MoveRect,
					IsDXT ) < 0 )
			{
				continue ;
			}

			UseTex = DrawTex->Tex->PF->Texture.TextureBuffer ;

			// �~�b�v�}�b�v���ǂ����ŏ����𕪊�
			if( Orig->Hard.MipMapCount > 1 )
			{
				if( Graphics_Android_BltBmpOrBaseImageToGraph3_MipMapBlt(
						Orig,
						&MoveRect,
						&DestRect,
						UseTex,
						DrawTex->Tex->TexWidth,
						DrawTex->Tex->TexHeight,
						RgbBaseImage,
						AlphaBaseImage,
						GANDR.Device.Caps.TextureFormat[ Orig->ColorFormat ],
						RedIsAlphaFlag,
						UseTransColorConvAlpha,
						ASyncThread ) < 0 )
					goto ERR ;
			}
			else
			{
				if( Graphics_Android_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
						&MoveRect,
						&DestRect,
						UseTex,
						Orig->FormatDesc.CubeMapTextureFlag ? CUBEMAP_SURFACE_NUM : 1,
						DrawTex->Tex->TexWidth,
						DrawTex->Tex->TexHeight,
						DrawTex->Tex->UseWidth,
						DrawTex->Tex->UseHeight,
						RgbBaseImage,
						AlphaBaseImage,
						GANDR.Device.Caps.TextureFormat[ Orig->ColorFormat ],
						RedIsAlphaFlag,
						UseTransColorConvAlpha,
						Orig->TransCode,
						ASyncThread ) < 0 )
					goto ERR ;
			}
		}
	}

	// ����I��
	return 0 ;


	// �G���[�I��
ERR :
	return -1 ;
}

#ifndef DX_NON_ASYNCLOAD
static int Graphics_Hardware_CreateOrigTexture_ASyncCallback( ASYNCLOAD_MAINTHREAD_REQUESTINFO *Info )
{
	return Graphics_Hardware_CreateOrigTexture_PF( ( IMAGEDATA_ORIG * )Info->Data[ 0 ], FALSE ) ;
}
#endif // DX_NON_ASYNCLOAD

// �I���W�i���摜��񒆂̃e�N�X�`�����쐬����( 0:����  -1:���s )
extern	int		Graphics_Hardware_CreateOrigTexture_PF(  IMAGEDATA_ORIG *Orig, int ASyncThread )
{
	int							i, j ;
	IMAGEDATA_ORIG_HARD_TEX		*OrigTex ;

#ifndef DX_NON_ASYNCLOAD
	if( ASyncThread )
	{
		ASYNCLOAD_MAINTHREAD_REQUESTINFO AInfo ;

		AInfo.Function = Graphics_Hardware_CreateOrigTexture_ASyncCallback ;
		AInfo.Data[ 0 ] = ( DWORD_PTR )Orig ;
		return AddASyncLoadRequestMainThreadInfo( &AInfo ) ;
	}
#endif // DX_NON_ASYNCLOAD

	// �n�[�h�E�G�A���g�p����摜�ł͂Ȃ��ꍇ�͉��������ɏI��
	if( Orig->FormatDesc.TextureFlag == FALSE )
	{
		return 0 ;
	}

	// �e�N�X�`���̏ꍇ�̓e�N�X�`���̐������e�N�X�`�����쐬
	OrigTex = Orig->Hard.Tex ;
	for( i = 0 ; i < Orig->Hard.TexNum ; i ++, OrigTex ++ )
	{
		// �e�N�X�`�����쐬
		if( OrigTex->PF->Texture.TextureBuffer == 0 )
		{
			PIXELFORMAT_INFO_ANDR *PixelFormat ;

			OrigTex->PF->Texture.PixelFormat = GANDR.Device.Caps.TextureFormat[ Orig->ColorFormat ] ;
			PixelFormat = &g_AndroidPixelFormat[ OrigTex->PF->Texture.PixelFormat ] ;
			glGenTextures( 1, &OrigTex->PF->Texture.TextureBuffer ) ;
			glBindTexture( GL_TEXTURE_2D, OrigTex->PF->Texture.TextureBuffer ) ;

			OrigTex->PF->Texture.Width  = OrigTex->TexWidth ;
			OrigTex->PF->Texture.Height = OrigTex->TexHeight ;

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ) ;
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ) ;
			OrigTex->PF->Texture.MagFilter = GL_NEAREST ;
			OrigTex->PF->Texture.MinFilter = GL_NEAREST ;

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ) ;
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ) ;
			OrigTex->PF->Texture.WrapS = GL_CLAMP_TO_EDGE ;
			OrigTex->PF->Texture.WrapT = GL_CLAMP_TO_EDGE ;
			OrigTex->PF->Texture.WrapR = GL_CLAMP_TO_EDGE ;

			OrigTex->PF->Texture.MipMapCount = Orig->Hard.MipMapCount <= 1 ? 1 : Orig->Hard.MipMapCount ;
			for( j = 0 ; j < OrigTex->PF->Texture.MipMapCount ; j ++ )
			{
				int TexWidth ;
				int TexHeight ;

				TexWidth  = OrigTex->TexWidth  >> j ;
				if( TexWidth <= 0 )
				{
					TexWidth = 1 ;
				}

				TexHeight = OrigTex->TexHeight >> j ;
				if( TexHeight <= 0 )
				{
					TexHeight = 1 ;
				}

				if( PixelFormat->IsExtFormat )
				{
					glCompressedTexImage2D(
						GL_TEXTURE_2D,
						j,
						PixelFormat->InternalFormat,
						TexWidth,
						TexHeight,
						0,
						0,
						0
					) ;
				}
				else
				{
					glTexImage2D(
						GL_TEXTURE_2D,
						j,
						PixelFormat->InternalFormat,
						TexWidth,
						TexHeight,
						0,
						PixelFormat->Format,
						PixelFormat->Type,
						0
					) ;
				}
			}
		}

		// �`��Ώۂɂł���ꍇ�̓t���[���o�b�t�@���쐬
		if( Orig->FormatDesc.DrawValidFlag )
		{
			// �t���[���o�b�t�@���쐬
			if( OrigTex->PF->FrameBuffer == 0 )
			{
				glGenFramebuffers( 1, &OrigTex->PF->FrameBuffer ) ;
				glBindFramebuffer( GL_FRAMEBUFFER, OrigTex->PF->FrameBuffer ) ;

				// �[�x�o�b�t�@���쐬
				glGenRenderbuffers( 1, &OrigTex->PF->DepthBuffer ) ;
				glBindRenderbuffer( GL_RENDERBUFFER, OrigTex->PF->DepthBuffer ) ;
				glRenderbufferStorage( GL_RENDERBUFFER, GANDR.Device.Caps.DepthBufferFormat[ Orig->ZBufferBitDepthIndex ], OrigTex->TexWidth, OrigTex->TexHeight ) ;

				// �[�x�o�b�t�@�ƃe�N�X�`�����t���[���o�b�t�@�ɃA�^�b�`
				glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_RENDERBUFFER, OrigTex->PF->DepthBuffer ) ;
				glFramebufferTexture2D(    GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,   OrigTex->PF->Texture.TextureBuffer, 0 ) ;

				// �����_�����O�^�[�Q�b�g�����ɖ߂�
				glBindFramebuffer( GL_FRAMEBUFFER, GANDR.Device.State.TargetFrameBuffer ) ;
			}
		}
	}

	// �I��
	return 0 ;
}

// �e�N�X�`�����������
static int Graphics_Hardware_Android_DeleteTexture( GLuint Texture )
{
	int i ;
	int Flag ;

	// �V�F�[�_�[�Ŏg�p����e�N�X�`���Ƃ��Đݒ肳��Ă������������
	Flag = FALSE ;
	for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
	{
		if( GANDR.Device.State.SetTexture[ i ] == NULL ||
			GANDR.Device.State.SetTexture[ i ]->TextureBuffer != Texture )
		{
			continue ;
		}

		if( Flag == FALSE )
		{
			// �`��ҋ@���Ă���`�敨��`��
			DRAWSTOCKINFO
			Flag = TRUE ;
		}

		Graphics_Android_DeviceState_SetTexture( i, NULL ) ;
	}

	// �ǂ����̃X���b�g�ɃZ�b�g����Ă�����`��p�e�N�X�`��������
	if( Flag )
	{
		Graphics_Android_DrawSetting_SetTexture( NULL ) ;
	}

	// �e�N�X�`�����폜����
	glDeleteTextures( 1, &Texture ) ;

	return 0 ;
}

// �I���W�i���摜��񒆂̃e�N�X�`�����������
extern int Graphics_Hardware_ReleaseOrigTexture_PF( IMAGEDATA_ORIG *Orig )
{
	int i ;
	IMAGEDATA_ORIG_HARD_TEX *OrigTex ;

	// �n�[�h�E�G�A���g�p����摜�ł͂Ȃ��ꍇ�͉��������ɏI��
	if( Orig->FormatDesc.TextureFlag == FALSE )
	{
		return 0 ;
	}

	OrigTex = Orig->Hard.Tex ;
	for( i = 0 ; i < Orig->Hard.TexNum ; i ++, OrigTex ++ )
	{
		if( OrigTex->PF->FrameBuffer != 0 )
		{
			glDeleteFramebuffers( 1, &OrigTex->PF->FrameBuffer ) ;
			OrigTex->PF->FrameBuffer = 0 ;
		}

		if( OrigTex->PF->Texture.TextureBuffer != 0 )
		{
			Graphics_Hardware_Android_DeleteTexture( OrigTex->PF->Texture.TextureBuffer ) ;
			OrigTex->PF->Texture.TextureBuffer = 0 ;
		}

		if( OrigTex->PF->DepthBuffer != 0 )
		{
			glDeleteRenderbuffers( 1, &OrigTex->PF->DepthBuffer ) ;
			OrigTex->PF->DepthBuffer = 0 ;
		}
	}

	// �I��
	return 0 ;
}

// �w��̃}���`�T���v�����Ŏg�p�ł���ő�N�I���e�B�l���擾����
extern	int		Graphics_Hardware_GetMultiSampleQuality_PF( int Samples )
{
	return 0 ;
}

// �쐬����O���t�B�b�N�n���h���Ŏg�p������ˑ��̃e�N�X�`���t�H�[�}�b�g���w�肷��
extern int Graphics_Hardware_SetUsePlatformTextureFormat_PF( int PlatformTextureFormat )
{
	return 0 ;
}




























// ���ˑ����_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�֌W

// ���_�o�b�t�@�n���h���̒��_�o�b�t�@���쐬����
extern	int		Graphics_Hardware_VertexBuffer_Create_PF( VERTEXBUFFERHANDLEDATA *VertexBuffer )
{
	glGenBuffers( 1, &VertexBuffer->PF->VertexBuffer ) ;
	glBindBuffer( GL_ARRAY_BUFFER, VertexBuffer->PF->VertexBuffer ) ;
	glBufferData( GL_ARRAY_BUFFER, VertexBuffer->UnitSize * VertexBuffer->Num, NULL, GL_DYNAMIC_DRAW ) ;
	glBindBuffer( GL_ARRAY_BUFFER, 0 ) ;

	return 0 ;
}

// ���_�o�b�t�@�n���h���̌�n��
extern	int		Graphics_Hardware_VertexBuffer_Terminate_PF( VERTEXBUFFERHANDLEDATA *VertexBuffer )
{
	glDeleteBuffers( 1, &VertexBuffer->PF->VertexBuffer ) ;

	return 0 ;
}

// ���_�o�b�t�@�ɒ��_�f�[�^��]������
extern	int		Graphics_Hardware_VertexBuffer_SetData_PF( VERTEXBUFFERHANDLEDATA *VertexBuffer, int SetIndex, const void *VertexData, int VertexNum )
{
	glBindBuffer(    GL_ARRAY_BUFFER, VertexBuffer->PF->VertexBuffer ) ;
	glBufferSubData( GL_ARRAY_BUFFER, SetIndex * VertexBuffer->UnitSize, VertexNum * VertexBuffer->UnitSize, VertexData ) ;
	glBindBuffer(    GL_ARRAY_BUFFER, 0 ) ;

	// ����I��
	return 0 ;
}

// �C���f�b�N�X�o�b�t�@�n���h���̃Z�b�g�A�b�v���s��
extern	int		Graphics_Hardware_IndexBuffer_Create_PF( INDEXBUFFERHANDLEDATA *IndexBuffer )
{
	glGenBuffers( 1, &IndexBuffer->PF->IndexBuffer ) ;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->PF->IndexBuffer ) ;
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->UnitSize * IndexBuffer->Num, NULL, GL_DYNAMIC_DRAW ) ;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ) ;

	return 0 ;
}

// �C���f�b�N�X�o�b�t�@�n���h���̌�n��
extern	int		Graphics_Hardware_IndexBuffer_Terminate_PF( INDEXBUFFERHANDLEDATA *IndexBuffer )
{
	glDeleteBuffers( 1, &IndexBuffer->PF->IndexBuffer ) ;

	return 0 ;
}

// �C���f�b�N�X�o�b�t�@�ɃC���f�b�N�X�f�[�^��]������
extern	int		Graphics_Hardware_IndexBuffer_SetData_PF( INDEXBUFFERHANDLEDATA *IndexBuffer, int SetIndex, const void *IndexData, int IndexNum )
{
	glBindBuffer(    GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->PF->IndexBuffer ) ;
	glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, SetIndex * IndexBuffer->UnitSize, IndexNum * IndexBuffer->UnitSize, IndexData ) ;
	glBindBuffer(    GL_ELEMENT_ARRAY_BUFFER, 0 ) ;

	// ����I��
	return 0 ;
}























// ���ˑ����C�g�֌W

// ���C�e�B���O���s�����ǂ�����ݒ肷��
extern	int		Graphics_Hardware_Light_SetUse_PF( int Flag )
{
	return Graphics_Android_DeviceState_SetLighting( Flag ) ;
}

// �O���[�o���A���r�G���g���C�g�J���[��ݒ肷��
extern	int		Graphics_Hardware_Light_GlobalAmbient_PF( COLOR_F *Color )
{
	return Graphics_Android_DeviceState_SetAmbient( Color ) ;
}

// ���C�g�p�����[�^���Z�b�g
extern	int		Graphics_Hardware_Light_SetState_PF( int LightNumber, LIGHTPARAM *LightParam )
{
	return Graphics_Android_DeviceState_SetLightState( LightNumber, LightParam ) ;
}

// ���C�g�̗L���A������ύX
extern	int		Graphics_Hardware_Light_SetEnable_PF( int LightNumber, int EnableState )
{
	return Graphics_Android_DeviceState_SetLightEnable( LightNumber, EnableState ) ;
}




























// ���ˑ��V���h�E�}�b�v�֌W

// �V���h�E�}�b�v�f�[�^�ɕK�v�ȃe�N�X�`�����쐬����
extern	int		Graphics_Hardware_ShadowMap_CreateTexture_PF( SHADOWMAPDATA *ShadowMap, int ASyncThread )
{
	if( ANDR_CHECKVALID_HARDWARE == FALSE )
	{
		return -1 ;
	}

	// �t�H�[�}�b�g�̌���
	if( ShadowMap->TexFormat_Float )
	{
		if( ShadowMap->TexFormat_BitDepth == 16 )
		{
			ShadowMap->ColorFormat = DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_F16 ;
			ShadowMap->ZBufferFormat = ZBUFFER_FORMAT_16BIT ;
		}
		else
		{
			ShadowMap->ColorFormat = DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_F32 ;
			ShadowMap->ZBufferFormat = ZBUFFER_FORMAT_32BIT ;
		}
	}
	else
	{
		if( ShadowMap->TexFormat_BitDepth == 16 )
		{
			ShadowMap->ColorFormat = DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_F16 ;
			ShadowMap->ZBufferFormat = ZBUFFER_FORMAT_16BIT ;
		}
		else
		{
			ShadowMap->ColorFormat = DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ONE_F32 ;
			ShadowMap->ZBufferFormat = ZBUFFER_FORMAT_32BIT ;
		}
	}

//	// ���肵���t�H�[�}�b�g���쐬�ł��Ȃ��ꍇ�͎��s
//	if( GANDR.Device.Caps.TextureFormat[ ShadowMap->ColorFormat ] == D_DXGI_FORMAT_UNKNOWN )
//	{
//		DXST_LOGFILE_ADDUTF16LE( "\xb7\x30\xe3\x30\xc9\x30\xa6\x30\xde\x30\xc3\x30\xd7\x30\xc7\x30\xfc\x30\xbf\x30\x28\x75\x6e\x30\xd5\x30\xa9\x30\xfc\x30\xde\x30\xc3\x30\xc8\x30\x67\x30\x5c\x4f\x10\x62\x67\x30\x4d\x30\x8b\x30\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\xd5\x30\xa9\x30\xfc\x30\xde\x30\xc3\x30\xc8\x30\x4c\x30\x42\x30\x8a\x30\x7e\x30\x5b\x30\x93\x30\x67\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�V���h�E�}�b�v�f�[�^�p�̃t�H�[�}�b�g�ō쐬�ł���e�N�X�`���t�H�[�}�b�g������܂���ł���\n" @*/ ) ;
//		return -1 ;
//	}

	// �e�N�X�`�����쐬
	{
		PIXELFORMAT_INFO_ANDR *PixelFormat ;

		ShadowMap->PF->Texture.PixelFormat = GANDR.Device.Caps.TextureFormat[ ShadowMap->ColorFormat ] ;
		PixelFormat = &g_AndroidPixelFormat[ ShadowMap->PF->Texture.PixelFormat ] ;
		if( ShadowMap->PF->Texture.TextureBuffer == 0 )
		{
			glGenTextures( 1, &ShadowMap->PF->Texture.TextureBuffer ) ;
		}
		glBindTexture( GL_TEXTURE_2D, ShadowMap->PF->Texture.TextureBuffer ) ;

		ShadowMap->PF->Texture.Width  = ShadowMap->BaseSizeX ;
		ShadowMap->PF->Texture.Height = ShadowMap->BaseSizeY ;

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ) ;
		ShadowMap->PF->Texture.MagFilter = GL_NEAREST ;
		ShadowMap->PF->Texture.MinFilter = GL_NEAREST ;

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ) ;
		ShadowMap->PF->Texture.WrapS = GL_CLAMP_TO_EDGE ;
		ShadowMap->PF->Texture.WrapT = GL_CLAMP_TO_EDGE ;
		ShadowMap->PF->Texture.WrapR = GL_CLAMP_TO_EDGE ;

		if( PixelFormat->IsExtFormat )
		{
			glCompressedTexImage2D(
				GL_TEXTURE_2D,
				0,
				PixelFormat->InternalFormat,
				ShadowMap->BaseSizeX,
				ShadowMap->BaseSizeY,
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
				ShadowMap->BaseSizeX,
				ShadowMap->BaseSizeY,
				0,
				PixelFormat->Format,
				PixelFormat->Type,
				0
			) ;
		}
	}

	// �t���[���o�b�t�@���쐬
	if( ShadowMap->PF->FrameBuffer == 0 )
	{
		glGenFramebuffers( 1, &ShadowMap->PF->FrameBuffer ) ;
	}
	glBindFramebuffer( GL_FRAMEBUFFER, ShadowMap->PF->FrameBuffer ) ;

	// �[�x�o�b�t�@���쐬
	if( ShadowMap->PF->DepthBuffer == 0 )
	{
		glGenRenderbuffers( 1, &ShadowMap->PF->DepthBuffer ) ;
	}
	glBindRenderbuffer( GL_RENDERBUFFER, ShadowMap->PF->DepthBuffer ) ;
	glRenderbufferStorage( GL_RENDERBUFFER, GANDR.Device.Caps.DepthBufferFormat[ ShadowMap->ZBufferFormat ], ShadowMap->BaseSizeX, ShadowMap->BaseSizeY ) ;

	// �[�x�o�b�t�@�ƃe�N�X�`�����t���[���o�b�t�@�ɃA�^�b�`
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_RENDERBUFFER, ShadowMap->PF->DepthBuffer ) ;
	glFramebufferTexture2D(    GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,   ShadowMap->PF->Texture.TextureBuffer, 0 ) ;

	// �I��
	return 0 ;
}

// �V���h�E�}�b�v�f�[�^�ɕK�v�ȃe�N�X�`�����������
extern	int		Graphics_Hardware_ShadowMap_ReleaseTexture_PF( SHADOWMAPDATA *ShadowMap )
{
	if( ShadowMap->PF->FrameBuffer != 0 )
	{
		glDeleteFramebuffers( 1, &ShadowMap->PF->FrameBuffer ) ;
		ShadowMap->PF->FrameBuffer = 0 ;
	}

	if( ShadowMap->PF->Texture.TextureBuffer != 0 )
	{
		Graphics_Hardware_Android_DeleteTexture( ShadowMap->PF->Texture.TextureBuffer ) ;
		ShadowMap->PF->Texture.TextureBuffer = 0 ;
	}

	if( ShadowMap->PF->DepthBuffer != 0 )
	{
		glDeleteRenderbuffers( 1, &ShadowMap->PF->DepthBuffer ) ;
		ShadowMap->PF->DepthBuffer = 0 ;
	}

	// �I��
	return 0 ;
}

// ���_�V�F�[�_�[�ɐݒ肷��V���h�E�}�b�v�̏����X�V����
extern	void	Graphics_Hardware_ShadowMap_RefreshVSParam_PF( void )
{
	SHADOWMAPDATA *ShadowMap ;
	static float TranspMatDef[ 4 ][ 4 ] =
	{
		{ 0.0f, 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, 0.0f, -1.0f },
	} ;
	int i ;

	for( i = 0 ; i < MAX_USE_SHADOWMAP_NUM ; i ++ )
	{
		// �A�h���X�̎擾
		if( SHADOWMAPCHKFULL( GSYS.DrawSetting.ShadowMap[ i ], ShadowMap ) )
		{
			_MEMCPY( GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 ], TranspMatDef, sizeof( TranspMatDef ) ) ;
		}
		else
		{
			// �s��̃Z�b�g
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 0 ][ 0 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 0 ][ 0 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 0 ][ 1 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 1 ][ 0 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 0 ][ 2 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 2 ][ 0 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 0 ][ 3 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 3 ][ 0 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 1 ][ 0 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 0 ][ 1 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 1 ][ 1 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 1 ][ 1 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 1 ][ 2 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 2 ][ 1 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 1 ][ 3 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 3 ][ 1 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 2 ][ 0 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 0 ][ 2 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 2 ][ 1 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 1 ][ 2 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 2 ][ 2 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 2 ][ 2 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 2 ][ 3 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 3 ][ 2 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 3 ][ 0 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 0 ][ 3 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 3 ][ 1 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 1 ][ 3 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 3 ][ 2 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 2 ][ 3 ] ;
			GANDR.Device.Shader.Constant.uSMLVPMat[ i * 4 + 3 ][ 3 ] = ShadowMap->ShadowMapViewProjectionMatrix.m[ 3 ][ 3 ] ;
		}
	}
}

// �t���O�����g�V�F�[�_�[�ɐݒ肷��V���h�E�}�b�v�̏����X�V����
extern	void	Graphics_Hardware_ShadowMap_RefreshPSParam_PF( void )
{
	SHADOWMAPDATA *ShadowMap ;
	LIGHT_HANDLE  *pLH ;
	int           CheckNum ;
	int           i ;
	int           j ;

	CheckNum = GSYS.Light.EnableNum > 3 ? 3 : GSYS.Light.EnableNum ;

	for( i = 0 ; i < MAX_USE_SHADOWMAP_NUM ; i ++ )
	{
		GANDR.Device.Shader.Constant.uShadowMapLightEnable[ i ][ 0 ] = 1.0f ;
		GANDR.Device.Shader.Constant.uShadowMapLightEnable[ i ][ 1 ] = 1.0f ;
		GANDR.Device.Shader.Constant.uShadowMapLightEnable[ i ][ 2 ] = 1.0f ;

		// �A�h���X�̎擾
		if( SHADOWMAPCHKFULL( GSYS.DrawSetting.ShadowMap[ i ], ShadowMap ) )
		{
			GANDR.Device.Shader.Constant.uShadowMap_DAdj_Grad[ i ][ 0 ] = 1.0f ;
			GANDR.Device.Shader.Constant.uShadowMap_DAdj_Grad[ i ][ 1 ] = 0.0f ;
		}
		else
		{
			GANDR.Device.Shader.Constant.uShadowMap_DAdj_Grad[ i ][ 0 ] = ShadowMap->AdjustDepth ;
			GANDR.Device.Shader.Constant.uShadowMap_DAdj_Grad[ i ][ 1 ] = ShadowMap->GradationParam ;

			for( j = 0 ; j < CheckNum ; j ++ )
			{
				pLH = GSYS.Light.Data[ GSYS.Light.EnableHardwareIndex[ j ] ] ;
				if( pLH->ShadowMapSlotDisableFlag[ i ] == FALSE )
				{
					switch( j )
					{
					case 0 :
						GANDR.Device.Shader.Constant.uShadowMapLightEnable[ i ][ 0 ] = 0.0f ;
						break ;

					case 1 :
						GANDR.Device.Shader.Constant.uShadowMapLightEnable[ i ][ 1 ] = 0.0f ;
						break ;

					case 2 :
						GANDR.Device.Shader.Constant.uShadowMapLightEnable[ i ][ 2 ] = 0.0f ;
						break ;
					}
				}
			}
		}
	}
}

// �V���h�E�}�b�v�ւ̕`��̏������s��
extern	int		Graphics_Hardware_ShadowMap_DrawSetup_PF( SHADOWMAPDATA *ShadowMap )
{
	// ����I��
	return 0 ;
}

// �V���h�E�}�b�v�ւ̕`����I������
extern	int		Graphics_Hardware_ShadowMap_DrawEnd_PF( SHADOWMAPDATA *ShadowMap )
{
	// ����I��
	return 0 ;
}

// �`��Ŏg�p����V���h�E�}�b�v���w�肷��( �X���b�g�͂O���P�����w��\ )
extern	int		Graphics_Hardware_ShadowMap_SetUse_PF( int SlotIndex, SHADOWMAPDATA *ShadowMap )
{
	// ����I��
	return 0 ;
}































// ���ˑ��V�F�[�_�[�֌W

// �V�F�[�_�[�n���h��������������
extern	int		Graphics_Hardware_Shader_Create_PF(
	int ShaderHandle,
	int ShaderType,
	void *Image,
	int ImageSize,
	int ImageAfterFree,
	int ASyncThread
)
{
	SHADERHANDLEDATA   *pShader ;
	GLuint FragmentShader = 0 ;
	GLuint VertexShader = 0 ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO ShaderCodeInfo ;
	int Result ;

	// �G���[����
	if( ASyncThread )
	{
		if( SHADERCHK_ASYNC( ShaderHandle, pShader ) )
			return -1 ;
	}
	else
	{
		if( SHADERCHK( ShaderHandle, pShader ) )
			return -1 ;
	}

	// �V�F�[�_�[���쐬����
	ShaderCodeInfo.Binary = Image ;
	ShaderCodeInfo.Size   = ImageSize ;
	switch( ShaderType )
	{
	case DX_SHADERTYPE_VERTEX :
		Result = Graphics_Android_VertexShader_Create( &ShaderCodeInfo, &VertexShader, 1 ) ;
		if( Result < 0 )
		{
			DXST_LOGFILE_ADDUTF16LE( "\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"���_�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ ) ;
			goto ERR ;
		}
		break ;

	case DX_SHADERTYPE_PIXEL :
		Result = Graphics_Android_FragmentShader_Create( &ShaderCodeInfo, &FragmentShader, 1 ) ;
		if( Result < 0 )
		{
			DXST_LOGFILE_ADDUTF16LE( "\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�t���O�����g�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ ) ;
			goto ERR ;
		}
		break ;

	default :
		DXST_LOGFILE_ADDUTF16LE( "\xfe\x5b\xdc\x5f\x57\x30\x66\x30\x44\x30\x6a\x30\x44\x30\xbf\x30\xa4\x30\xd7\x30\x6e\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x92\x30\x5c\x4f\x10\x62\x57\x30\x88\x30\x46\x30\x68\x30\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�Ή����Ă��Ȃ��^�C�v�̃V�F�[�_�[���쐬���悤�Ƃ��܂���\n" @*/ ) ;
		goto ERR ;
	}

	// �o�C�i���C���[�W��ۑ����郁�����̈�̊m��
	pShader->FunctionCode = DXCALLOC( ( size_t )ImageSize ) ;
	if( pShader->FunctionCode == NULL )
	{
		DXST_LOGFILE_ADDUTF16LE( "\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x00"/*@ L"�������̊m�ۂɎ��s���܂���" @*/ ) ;
		goto ERR ;
	}

	// �o�C�i���C���[�W��ۑ�����
	_MEMCPY( pShader->FunctionCode, Image, ( size_t )ImageSize ) ;

	// �o�C�i���C���[�W�̃T�C�Y��ۑ�����
	pShader->FunctionCodeSize = ImageSize ;

	// �V�F�[�_�[�^�C�v��ۑ�����
	pShader->ShaderType = ShaderType ;

	// �V�F�[�_�[�̃A�h���X��ۑ�
	if( ShaderType == DX_SHADERTYPE_VERTEX )
	{
		pShader->PF->Shader = VertexShader ;
	}
	else
	{
		pShader->PF->Shader = FragmentShader ;
	}

	// ������ɉ�����ׂ��̃t���O�������Ă�����������
	if( ImageAfterFree )
	{
		DXFREE( Image ) ;
	}

	// ����I��
	return 0 ;

ERR :

	Graphics_Android_VertexShaderArray_Release( &VertexShader, 1 ) ;
	Graphics_Android_FragmentShaderArray_Release(  &FragmentShader,  1 ) ;

	// ������ɉ�����ׂ��̃t���O�������Ă�����������
	if( ImageAfterFree )
	{
		DXFREE( Image ) ;
	}

	return -1 ;
}

// �V�F�[�_�[�n���h���̌�n��
extern	int		Graphics_Hardware_Shader_TerminateHandle_PF( SHADERHANDLEDATA *Shader )
{
	// �V�F�[�_�[�̉��
	if( Shader->ShaderType == DX_SHADERTYPE_VERTEX )
	{
		Graphics_Android_VertexShaderArray_Release( &Shader->PF->Shader, 1 ) ;
	}
	else
	{
		Graphics_Android_FragmentShaderArray_Release(  &Shader->PF->Shader,  1 ) ;
	}

	// ����I��
	return 0 ;
}

// �g�p�ł���V�F�[�_�[�̃o�[�W�������擾����( 0=�g���Ȃ�  200=�V�F�[�_�[���f���Q�D�O���g�p�\  300=�V�F�[�_�[���f���R�D�O���g�p�\ )
extern	int		Graphics_Hardware_Shader_GetValidShaderVersion_PF( void )
{
	return 500 ;
}

// �w��̖��O�����萔���g�p����V�F�[�_�[�萔�̔ԍ����擾����
extern	int		Graphics_Hardware_Shader_GetConstIndex_PF( const wchar_t *ConstantName, SHADERHANDLEDATA *Shader )
{
	return 0 ;
}

// �w��̖��O�����萔���g�p����V�F�[�_�[�萔�̐����擾����
extern	int		Graphics_Hardware_Shader_GetConstCount_PF( const wchar_t *ConstantName, SHADERHANDLEDATA *Shader )
{
	return 0 ;
}

// �w��̖��O�������������_�萔�̃f�t�H���g�p�����[�^���i�[����Ă��郁�����A�h���X���擾����
extern	const FLOAT4 *Graphics_Hardware_Shader_GetConstDefaultParamF_PF( const wchar_t *ConstantName, SHADERHANDLEDATA *Shader )
{
	return 0 ;
}

// �V�F�[�_�[�萔����ݒ肷��
extern	int		Graphics_Hardware_Shader_SetConst_PF( int TypeIndex, int SetIndex, int ConstantIndex, const void *Param, int ParamNum, int UpdateUseArea )
{
	// ����I��
	return 0 ;
}

// �w��̈�̃V�F�[�_�[�萔�������Z�b�g����
extern	int		Graphics_Hardware_Shader_ResetConst_PF( int TypeIndex, int SetIndex, int ConstantIndex, int ParamNum )
{
	// ����I��
	return 0 ;
}

#ifndef DX_NON_MODEL
// �R�c���f���p�̃V�F�[�_�[�R�[�h�̏��������s��
extern	int		Graphics_Hardware_Shader_ModelCode_Init_PF( void )
{
	if( Graphics_Android_ShaderCode_Model_Initialize() == FALSE )
	{
		return -1 ;
	}

	// ����I��
	return 0 ;
}
#endif // DX_NON_MODEL
































// ���ˑ��V�F�[�_�[�p�萔�o�b�t�@�֌W

// �V�F�[�_�[�p�萔�o�b�t�@�n���h��������������
extern	int		Graphics_Hardware_ShaderConstantBuffer_Create_PF( int ShaderConstantBufferHandle, int BufferSize, int ASyncThread ) 
{
	return -1 ;
}

// �V�F�[�_�[�p�萔�o�b�t�@�n���h���̌�n��
extern	int		Graphics_Hardware_ShaderConstantBuffer_TerminateHandle_PF( SHADERCONSTANTBUFFERHANDLEDATA *ShaderConstantBuffer )
{
	// ����I��
	return 0 ;
}

// �V�F�[�_�[�p�萔�o�b�t�@�n���h���̒萔�o�b�t�@�̃A�h���X���擾����
extern	void *	Graphics_Hardware_ShaderConstantBuffer_GetBuffer_PF( SHADERCONSTANTBUFFERHANDLEDATA *ShaderConstantBuffer )
{
	return 0 ;
}

// �V�F�[�_�[�p�萔�o�b�t�@�n���h���̒萔�o�b�t�@�ւ̕ύX��K�p����
extern	int		Graphics_Hardware_ShaderConstantBuffer_Update_PF( SHADERCONSTANTBUFFERHANDLEDATA *ShaderConstantBuffer )
{
	// �I��
	return 0 ;
}

// �V�F�[�_�[�p�萔�o�b�t�@�n���h���̒萔�o�b�t�@���w��̃V�F�[�_�[�̎w��̃X���b�g�ɃZ�b�g����
extern	int		Graphics_Hardware_ShaderConstantBuffer_Set_PF( SHADERCONSTANTBUFFERHANDLEDATA *ShaderConstantBuffer, int TargetShader /* DX_SHADERTYPE_VERTEX �Ȃ� */, int Slot )
{
	// �I��
	return 0 ;
}





































// ���ˑ��`��֌W

// �w��_���狫�E�F������Ƃ���܂œh��Ԃ�
extern	int		Graphics_Hardware_Paint_PF( int x, int y, unsigned int FillColor, ULONGLONG BoundaryColor )
{
	// �f�t�H���g�̏������s��
	return 2 ;
}











// OpenGL �֌W�̏����擾����
extern int GetOpenGLInfo(
	TCHAR **Version,
	TCHAR **Renderer,
	TCHAR **Vendor,
	TCHAR ***ExtensionNames,
	TCHAR **Shading_Language_Version,
	int *Shader_Max_Vertex_Attribs,						// GL_MAX_VERTEX_ATTRIBS
	int *Shader_Max_Vertex_Uniform_Vectors,				// GL_MAX_VERTEX_UNIFORM_VECTORS
	int *Shader_Max_Varying_Vectors,					// GL_MAX_VARYING_VECTORS
	int *Shader_Max_Combined_Texture_Image_Units,		// GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
	int *Shader_Max_Vertex_Texture_Image_Units,			// GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
	int *Shader_Max_Texture_Image_Units,				// GL_MAX_TEXTURE_IMAGE_UNITS
	int *Shader_Max_Fragment_Uniform_Vectors			// GL_MAX_FRAGMENT_UNIFORM_VECTORS
)
{
	if( Version										!= NULL ) *Version									= GANDR.Device.Caps.Version	;
	if( Renderer									!= NULL ) *Renderer									= GANDR.Device.Caps.Renderer ;
	if( Vendor										!= NULL ) *Vendor									= GANDR.Device.Caps.Vendor ;
	if( ExtensionNames								!= NULL ) *ExtensionNames							= GANDR.Device.Caps.ExtensionNames ;
	if( Shading_Language_Version					!= NULL ) *Shading_Language_Version					= GANDR.Device.Caps.Shading_Language_Version ;

	if( Shader_Max_Vertex_Attribs					!= NULL ) *Shader_Max_Vertex_Attribs				= GANDR.Device.Caps.Shader_Max_Vertex_Attribs ;
	if( Shader_Max_Vertex_Uniform_Vectors			!= NULL ) *Shader_Max_Vertex_Uniform_Vectors		= GANDR.Device.Caps.Shader_Max_Vertex_Uniform_Vectors ;
	if( Shader_Max_Varying_Vectors					!= NULL ) *Shader_Max_Varying_Vectors				= GANDR.Device.Caps.Shader_Max_Varying_Vectors ;
	if( Shader_Max_Combined_Texture_Image_Units		!= NULL ) *Shader_Max_Combined_Texture_Image_Units	= GANDR.Device.Caps.Shader_Max_Combined_Texture_Image_Units ;
	if( Shader_Max_Vertex_Texture_Image_Units		!= NULL ) *Shader_Max_Vertex_Texture_Image_Units	= GANDR.Device.Caps.Shader_Max_Vertex_Texture_Image_Units ;
	if( Shader_Max_Texture_Image_Units				!= NULL ) *Shader_Max_Texture_Image_Units			= GANDR.Device.Caps.Shader_Max_Texture_Image_Units ;
	if( Shader_Max_Fragment_Uniform_Vectors			!= NULL ) *Shader_Max_Fragment_Uniform_Vectors		= GANDR.Device.Caps.Shader_Max_Fragment_Uniform_Vectors ;

	// �I��
	return 0 ;
}

// �O���t�B�b�N�n���h���̃e�N�X�`���I�u�W�F�N�g���擾����
extern unsigned int GetGraphOpenGLESTextureObject( int GrHandle )
{
	IMAGEDATA *Image ;
//	int Ret ;

	// ����������
	if( DxSysData.DxLib_InitializeFlag == FALSE )
	{
		return -1 ;
	}

	// �\�t�g����A�N�e�B�u�̏ꍇ�̓A�N�e�B�u�ɂȂ�܂ő҂�
	CheckActiveState() ;

	// �G���[����
	if( GRAPHCHK( GrHandle, Image ) )
	{
		return ( GLuint )-1 ;
	}

	return Image->Hard.Draw[ 0 ].Tex->PF->Texture.TextureBuffer ;
}


// �c�w���C�u�������s���� OpenGL ES �̐ݒ���ēx�s��( ����p�r )
extern int RefreshDxLibOpenGLESSetting( void )
{
	// ���܂ł̐ݒ�𕜋A����
	Graphics_Android_DeviceState_RefreshRenderState() ;

	return 0 ;
}











#ifndef DX_NON_ASYNCLOAD
static int glTexSubImage2D_ASyncCallback( ASYNCLOAD_MAINTHREAD_REQUESTINFO *Info )
{
	return glTexSubImage2D_ASync(
		( GLuint )Info->Data[ 0 ],
		( GLenum )Info->Data[ 1 ],
		( GLint )Info->Data[ 2 ],
		( GLint )Info->Data[ 3 ], ( GLint )Info->Data[ 4 ],
		( GLsizei )Info->Data[ 5 ], ( GLsizei )Info->Data[ 6 ],
		( GLenum )Info->Data[ 7 ], ( GLenum )Info->Data[ 8 ],
		( const GLvoid* )Info->Data[ 9 ],
		FALSE ) ;
}
#endif // DX_NON_ASYNCLOAD

// glTexSubImage2D �̔񓯊����s�p�̊֐�
static int glTexSubImage2D_ASync(
	GLuint texture,
	GLenum target,
	GLint level,
	GLint xoffset, GLint yoffset,
	GLsizei width, GLsizei height,
	GLenum format, GLenum type,
	const GLvoid* pixels,
	int ASyncThread
)
{
#ifndef DX_NON_ASYNCLOAD
	if( ASyncThread )
	{
		ASYNCLOAD_MAINTHREAD_REQUESTINFO AInfo ;

		AInfo.Function = glTexSubImage2D_ASyncCallback ;
		AInfo.Data[ 0 ] = ( DWORD_PTR )texture ;
		AInfo.Data[ 1 ] = ( DWORD_PTR )target ;
		AInfo.Data[ 2 ] = ( DWORD_PTR )level ;
		AInfo.Data[ 3 ] = ( DWORD_PTR )xoffset ;
		AInfo.Data[ 4 ] = ( DWORD_PTR )yoffset ;
		AInfo.Data[ 5 ] = ( DWORD_PTR )width ;
		AInfo.Data[ 6 ] = ( DWORD_PTR )height ;
		AInfo.Data[ 7 ] = ( DWORD_PTR )format ;
		AInfo.Data[ 8 ] = ( DWORD_PTR )type ;
		AInfo.Data[ 9 ] = ( DWORD_PTR )pixels ;
		return AddASyncLoadRequestMainThreadInfo( &AInfo ) ;
	}
#endif // DX_NON_ASYNCLOAD

	glBindTexture( target, texture ) ;
	glTexSubImage2D(
		target,
		level,
		xoffset, yoffset,
		width, height,
		format, type,
		pixels
	) ;
	glBindTexture( target, 0 ) ;

	return 0 ;
}





#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_GRAPHICS


