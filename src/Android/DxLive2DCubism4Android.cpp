//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Live2D Cubism4�֌W�v���O����( Android )
// 
//  	Ver 3.24b
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_LIVE2D_CUBISM4

// �C���N���[�h----------------------------------------------------------------
#include "../DxLib.h"
#include "../DxStatic.h"
#include "../DxLive2DCubism4.h"
#include "../DxGraphics.h"
#include "../DxMemory.h"
#include "../DxArchive_.h"
#include "../DxLog.h"
#include "Live2DCubismCore.h"
#include "DxGraphicsAndroid.h"

// #ifndef DX_NON_NAMESPACE
// 
// namespace DxLib
// {
// 
// #endif // DX_NON_NAMESPACE

// �}�N����`------------------------------------------------------------------

// �^��`----------------------------------------------------------------------

// �f�[�^�錾------------------------------------------------------------------

extern BYTE DxShaderCodeBin_Live2D_Cubism4_ANDR[] ;

// �V�F�[�_�[�̑g�ݍ��킹[ 0:���_�V�F�[�_�[ 1:�t���O�����g�V�F�[�_�[ ]
static D_ShaderNames g_Live2D_Cubism4_ShaderSet[ LIVE2D_SHADER_Num ][ 2 ] =
{
	{ D_ShaderNames_SetupMask,		D_ShaderNames_SetupMask									},	// LIVE2D_SHADER_SetupMask_SetupMask								0
	{ D_ShaderNames_NormalMasked,	D_ShaderNames_NormalMaskedPremultipliedAlpha			},	// LIVE2D_SHADER_NormalMasked_NormalMaskedPremultipliedAlpha		1
	{ D_ShaderNames_NormalMasked,	D_ShaderNames_NormalMaskedInvertedPremultipliedAlpha	},	// LIVE2D_SHADER_NormalMasked_NormalMaskedInvertedPremultipliedAlpha		1
	{ D_ShaderNames_NormalMasked,	D_ShaderNames_NormalMasked								},	// LIVE2D_SHADER_NormalMasked_NormalMasked							2
	{ D_ShaderNames_NormalMasked,	D_ShaderNames_NormalMaskedInverted						},	// LIVE2D_SHADER_NormalMasked_NormalMaskedInverted							2
	{ D_ShaderNames_Normal,			D_ShaderNames_NormalPremultipliedAlpha					},	// LIVE2D_SHADER_Normal_NormalPremultipliedAlpha					3
	{ D_ShaderNames_Normal,			D_ShaderNames_Normal									},	// LIVE2D_SHADER_Normal_Normal										4
} ;

// �֐��v���g�^�C�v�錾 -------------------------------------------------------

// DLL �̓ǂݍ��݁E���
static	int			Live2DCubism4_DLL_Load( void ) ;														// Live2D Cubism 4 DLL �̓ǂݍ���
static	int			Live2DCubism4_DLL_Unload( void ) ;														// Live2D Cubism 4 DLL �̉��

// �v���O����------------------------------------------------------------------

// DLL �̓ǂݍ��݁E���

// Live2D Cubism 4 DLL �̓ǂݍ���
static int Live2DCubism4_DLL_Load( void )
{
	LIVE2DDLL.csmGetVersion						= ( DWORD					( LIVE2D_CUBISM4_FUNC * )( void ) )csmGetVersion ;
	LIVE2DDLL.csmGetLatestMocVersion			= ( DWORD					( LIVE2D_CUBISM4_FUNC * )( void ) )csmGetLatestMocVersion ;
	LIVE2DDLL.csmGetMocVersion					= ( DWORD					( LIVE2D_CUBISM4_FUNC * )( const void* address, const DWORD size ) )csmGetMocVersion ;
	LIVE2DDLL.csmGetLogFunction					= ( csmLogFunctionP			( LIVE2D_CUBISM4_FUNC * )( void ) )csmGetLogFunction ;
	LIVE2DDLL.csmSetLogFunction					= ( void					( LIVE2D_CUBISM4_FUNC * )( csmLogFunctionP handler ) )csmSetLogFunction ;
	LIVE2DDLL.csmReviveMocInPlace				= ( void*					( LIVE2D_CUBISM4_FUNC * )( void* address, const DWORD size ) )csmReviveMocInPlace ;
	LIVE2DDLL.csmGetSizeofModel					= ( DWORD 					( LIVE2D_CUBISM4_FUNC * )( const void* moc ) )csmGetSizeofModel ;
	LIVE2DDLL.csmInitializeModelInPlace			= ( void* 					( LIVE2D_CUBISM4_FUNC * )( const void* moc, void* address, const DWORD size ) )csmInitializeModelInPlace ;
	LIVE2DDLL.csmUpdateModel					= ( void 					( LIVE2D_CUBISM4_FUNC * )( void* model ) )csmUpdateModel ;
	LIVE2DDLL.csmReadCanvasInfo					= ( void 					( LIVE2D_CUBISM4_FUNC * )( const void* model, D_CubismVector2* outSizeInPixels, D_CubismVector2* outOriginInPixels, float* outPixelsPerUnit ) )csmReadCanvasInfo ;
	LIVE2DDLL.csmGetParameterCount				= ( int 					( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetParameterCount ;
	LIVE2DDLL.csmGetParameterIds 				= ( const char** 			( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetParameterIds ;
	LIVE2DDLL.csmGetParameterMinimumValues		= ( const float*			( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetParameterMinimumValues ;
	LIVE2DDLL.csmGetParameterMaximumValues		= ( const float*			( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetParameterMaximumValues ;
	LIVE2DDLL.csmGetParameterDefaultValues		= ( const float*			( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetParameterDefaultValues ;
	LIVE2DDLL.csmGetParameterValues				= ( float* 					( LIVE2D_CUBISM4_FUNC * )( void* model ) )csmGetParameterValues ;
	LIVE2DDLL.csmGetPartCount					= ( int 					( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetPartCount ;
	LIVE2DDLL.csmGetPartIds						= ( const char**			( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetPartIds ;
	LIVE2DDLL.csmGetPartOpacities				= ( float*					( LIVE2D_CUBISM4_FUNC * ) (void* model ) )csmGetPartOpacities ;
	LIVE2DDLL.csmGetPartParentPartIndices 		= ( const int*				( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetPartParentPartIndices ;
	LIVE2DDLL.csmGetDrawableCount				= ( int 					( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableCount ;
	LIVE2DDLL.csmGetDrawableIds					= ( const char**			( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableIds ;
	LIVE2DDLL.csmGetDrawableConstantFlags 		= ( const BYTE*				( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableConstantFlags ;
	LIVE2DDLL.csmGetDrawableDynamicFlags		= ( const BYTE*				( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableDynamicFlags ;
	LIVE2DDLL.csmGetDrawableTextureIndices		= ( const int*				( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableTextureIndices ;
	LIVE2DDLL.csmGetDrawableDrawOrders			= ( const int*				( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableDrawOrders ;
	LIVE2DDLL.csmGetDrawableRenderOrders		= ( const int*				( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableRenderOrders ;
	LIVE2DDLL.csmGetDrawableOpacities			= ( const float*			( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableOpacities ;
	LIVE2DDLL.csmGetDrawableMaskCounts 			= ( const int*				( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableMaskCounts ;
	LIVE2DDLL.csmGetDrawableMasks				= ( const int**				( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableMasks ;
	LIVE2DDLL.csmGetDrawableVertexCounts		= ( const int*				( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableVertexCounts ;
	LIVE2DDLL.csmGetDrawableVertexPositions		= ( const D_CubismVector2**	( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableVertexPositions ;
	LIVE2DDLL.csmGetDrawableVertexUvs			= ( const D_CubismVector2**	( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableVertexUvs ;
	LIVE2DDLL.csmGetDrawableIndexCounts			= ( const int*				( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableIndexCounts ;
	LIVE2DDLL.csmGetDrawableIndices 			= ( const unsigned short**	( LIVE2D_CUBISM4_FUNC * )( const void* model ) )csmGetDrawableIndices ;
	LIVE2DDLL.csmResetDrawableDynamicFlags		= ( void					( LIVE2D_CUBISM4_FUNC * )( void* model ) )csmResetDrawableDynamicFlags ;

	// ����I��
	return 0 ;
}

// Live2D Cubism 4 DLL �̉��
static int Live2DCubism4_DLL_Unload( void )
{
	LIVE2DDLL.csmGetVersion						= NULL ;
	LIVE2DDLL.csmGetLatestMocVersion			= NULL ;
	LIVE2DDLL.csmGetMocVersion					= NULL ;
	LIVE2DDLL.csmGetLogFunction					= NULL ;
	LIVE2DDLL.csmSetLogFunction					= NULL ;
	LIVE2DDLL.csmReviveMocInPlace				= NULL ;
	LIVE2DDLL.csmGetSizeofModel					= NULL ;
	LIVE2DDLL.csmInitializeModelInPlace			= NULL ;
	LIVE2DDLL.csmUpdateModel					= NULL ;
	LIVE2DDLL.csmReadCanvasInfo					= NULL ;
	LIVE2DDLL.csmGetParameterCount				= NULL ;
	LIVE2DDLL.csmGetParameterIds 				= NULL ;
	LIVE2DDLL.csmGetParameterMinimumValues		= NULL ;
	LIVE2DDLL.csmGetParameterMaximumValues		= NULL ;
	LIVE2DDLL.csmGetParameterDefaultValues		= NULL ;
	LIVE2DDLL.csmGetParameterValues				= NULL ;
	LIVE2DDLL.csmGetPartCount					= NULL ;
	LIVE2DDLL.csmGetPartIds						= NULL ;
	LIVE2DDLL.csmGetPartOpacities				= NULL ;
	LIVE2DDLL.csmGetPartParentPartIndices 		= NULL ;
	LIVE2DDLL.csmGetDrawableCount				= NULL ;
	LIVE2DDLL.csmGetDrawableIds					= NULL ;
	LIVE2DDLL.csmGetDrawableConstantFlags 		= NULL ;
	LIVE2DDLL.csmGetDrawableDynamicFlags		= NULL ;
	LIVE2DDLL.csmGetDrawableTextureIndices		= NULL ;
	LIVE2DDLL.csmGetDrawableDrawOrders			= NULL ;
	LIVE2DDLL.csmGetDrawableRenderOrders		= NULL ;
	LIVE2DDLL.csmGetDrawableOpacities			= NULL ;
	LIVE2DDLL.csmGetDrawableMaskCounts 			= NULL ;
	LIVE2DDLL.csmGetDrawableMasks				= NULL ;
	LIVE2DDLL.csmGetDrawableVertexCounts		= NULL ;
	LIVE2DDLL.csmGetDrawableVertexPositions		= NULL ;
	LIVE2DDLL.csmGetDrawableVertexUvs			= NULL ;
	LIVE2DDLL.csmGetDrawableIndexCounts			= NULL ;
	LIVE2DDLL.csmGetDrawableIndices 			= NULL ;
	LIVE2DDLL.csmResetDrawableDynamicFlags		= NULL ;

	// ����I��
	return 0 ;
}

// Live2D Cubism4 �Ŏg�p���Ă���S�ẴV�F�[�_�[���J������
extern int Live2D_Cubism4_Android_ReleaseShaderAll( void )
{
	Graphics_Android_ShaderArray_Release( LIVE2DSYS.PF.Shader, LIVE2D_SHADER_Num ) ;

	return 0 ;
}

// ���ˑ��֐�

// Live2D Cubism4 �֘A�̏���������֐��̊��ˑ��������s���֐�
extern int Live2DCubism4_Initialize_PF( void )
{
	// DLL �̓ǂݍ���
	if( Live2DCubism4_DLL_Load() < 0 )
	{
		return -1 ;
	}

	// �R���X�^���g�o�b�t�@���g�p�ł��邩�ǂ������Z�b�g
	LIVE2DSYS.EnableConstantBuffer = FALSE ;

	// �V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�����k�����f�[�^���𓀂���
	if( Live2DCubism4_SetupShaderCode( NULL, DxShaderCodeBin_Live2D_Cubism4_ANDR ) < 0 )
	{
		return -1 ;
	}

	return 0 ;
}

// Live2D Cubism4 �֘A�̌�n��������֐��̊��ˑ��������s���֐�
extern int Live2DCubism4_Terminate_PF( void )
{
	// DLL �̃A�����[�h
	Live2DCubism4_DLL_Unload() ;

	return 0 ;
}

// Live2D Cubism4 �̃V�F�[�_�[�쐬�̊��ˑ��������s��
extern int Live2DCubism4_GenerateShaders_PF( void )
{
	int i ;
	D_CubismShader_DxLib* shaderManager = D_CubismRenderer_DxLib::GetShaderManager();

	for( i = 0 ; i < LIVE2D_SHADER_Num ; i ++ )
	{
		SHADERHANDLEDATA *pVertexShader ;
		SHADERHANDLEDATA *pPixelShader ;
		int VertexShaderHandle ;
		int PixelShaderHandle ;

		if( LIVE2DSYS.PF.Shader[ i ].Shader != 0 )
		{
			continue ;
		}

		VertexShaderHandle = shaderManager->GetVertexShader( g_Live2D_Cubism4_ShaderSet[ i ][ 0 ] ) ;
		PixelShaderHandle  = shaderManager->GetPixelShader(  g_Live2D_Cubism4_ShaderSet[ i ][ 1 ] ) ;

		if( SHADERCHK( VertexShaderHandle, pVertexShader ) )
			continue ;

		if( SHADERCHK( PixelShaderHandle, pPixelShader ) )
			continue ;

		Graphics_Android_Shader_Create( &LIVE2DSYS.PF.Shader[ i ], pVertexShader->PF->Shader, pPixelShader->PF->Shader ) ;
	}

	return 0 ;
}

// �V�F�[�_�[�̃Z�b�g�A�b�v���s��
extern int Live2DCubism4_SetupShader_PF( int ConstantBufferHandle, D_CubismConstantBufferDxLib *ConstantBuffer, D_ShaderNames VertexShader, D_ShaderNames PixelShader )
{
	D_CubismShader_DxLib* shaderManager = D_CubismRenderer_DxLib::GetShaderManager();
	int index = 0 ;

	if( shaderManager == NULL )
	{
		return -1 ;
	}

	for( index = 0 ; g_Live2D_Cubism4_ShaderSet[ index ][ 0 ] != VertexShader || g_Live2D_Cubism4_ShaderSet[ index ][ 1 ] != PixelShader ; index ++ ){}

	// �V�F�[�_�[���g�p��ԂɃZ�b�g
	glUseProgram( LIVE2DSYS.PF.Shader[ index ].Shader ) ;

	GLuint u_matrix      = Graphics_Android_Shader_GetUniformIndex( &LIVE2DSYS.PF.Shader[ index ], "u_matrix" ) ;
	GLuint u_clipMatrix  = Graphics_Android_Shader_GetUniformIndex( &LIVE2DSYS.PF.Shader[ index ], "u_clipMatrix" ) ;
	GLuint u_channelFlag = Graphics_Android_Shader_GetUniformIndex( &LIVE2DSYS.PF.Shader[ index ], "u_channelFlag" ) ;
	GLuint u_baseColor   = Graphics_Android_Shader_GetUniformIndex( &LIVE2DSYS.PF.Shader[ index ], "u_baseColor" ) ;

	if( u_matrix != 0xffffffff )
	{
		glUniform4fv( u_matrix, 4, &ConstantBuffer->projectMatrix.m[ 0 ][ 0 ] ) ;
	}
	if( u_clipMatrix != 0xffffffff )
	{
		glUniform4fv( u_clipMatrix, 4, &ConstantBuffer->clipMatrix.m[ 0 ][ 0 ] ) ;
	}
	if( u_channelFlag != 0xffffffff )
	{
		UNIFORM_SET_FLOAT4( u_channelFlag, ( ( float * )&ConstantBuffer->channelFlag ) )
	}
	if( u_baseColor != 0xffffffff )
	{
		UNIFORM_SET_FLOAT4( u_baseColor, ( ( float * )&ConstantBuffer->baseColor ) )
	}

	GANDR.Device.State.SetShader_Force = &LIVE2DSYS.PF.Shader[ index ] ;

	return 0 ;
}

// Live2D Cubism4 �̕`��̌�ɌĂ΂����ˑ��֐�
extern int Live2DCubism4_DrawAfter_PF( void )
{
	GANDR.Device.State.SetShader_Force = NULL ;

	return 0 ;
}

bool D_CubismShader_DxLib::LoadShaderProgram( bool isPs, int assign, const char* entryPoint )
{
	bool bRet = false;
	char FilePath[ 1024 ];

	int vertexShader = -1;
	int pixelShader = -1;

	do
	{
		CL_strcpy( DX_CHARCODEFORMAT_ASCII, FilePath, entryPoint );
		if( isPs )
		{
			CL_strcat( DX_CHARCODEFORMAT_ASCII, FilePath, ".flag" ) ;
			pixelShader = Live2DCubism4_LoadShaderCode( FilePath, DX_SHADERTYPE_PIXEL ) ;
			if( pixelShader < 0 )
			{
				// CubismLogWarning("Fail Create Shader");
				break;
			}
			_shaderSetsPS[ assign ] = pixelShader;
		}
		else
		{
			CL_strcat( DX_CHARCODEFORMAT_ASCII, FilePath, ".vert" ) ;
			vertexShader = Live2DCubism4_LoadShaderCode( FilePath, DX_SHADERTYPE_VERTEX ) ;
			if( vertexShader < 0 )
			{
				// CubismLogWarning("Fail Create Shader");
				break;
			}
			_shaderSetsVS[ assign ] = vertexShader;
		}
		// ���� 
		bRet = true;
	} while( 0 );

	return bRet;
}

// #ifndef DX_NON_NAMESPACE
// 
// }
// 
// #endif // DX_NON_NAMESPACE

#endif // DX_NON_LIVE2D_CUBISM4

