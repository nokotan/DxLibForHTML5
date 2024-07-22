//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		���f���f�[�^����v���O����( Android )
// 
//  	Ver 3.24d
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_GRAPHICS

#ifndef DX_NON_MODEL

// �C���N���[�h----------------------------------------------------------------
#include "DxGraphicsAndroid.h"
#include "DxSystemAndroid.h"
#include "DxModelAndroid.h"
#include "DxShader_DataType_Android.h"
#include "DxShader_FS_Android.h"
#include "DxShader_VS_Android.h"
#include "../DxASyncLoad.h"
#include "../DxMask.h"
#include "../DxLog.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����`------------------------------------------------------------------

#define MV1_ANDR_COMMONBUFFER_ADDSIZE			(16 * 1024)

#define WORD_MAX								0x10000

// �^��`----------------------------------------------------------------------

// �f�[�^�錾------------------------------------------------------------------

// �P�ʍs��
static MATRIX IdentityMat =
{
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	}
} ;

static GLenum DrawModeToFilterTable[ 2 ][ 3 ] =
{
	{
		GL_NEAREST,
		GL_LINEAR,
		GL_LINEAR,
	},

	{
		GL_NEAREST_MIPMAP_LINEAR,
		GL_LINEAR_MIPMAP_LINEAR,
		GL_LINEAR_MIPMAP_LINEAR,
	}
} ;

// [ �o���v�}�b�v���t�����ǂ���( 1:�o���v�}�b�v�t�� 0:�t���ĂȂ� ) ]
// [ �X�L�j���O���b�V�����ǂ���( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V�� 2:8�{�[�����X�L�j���O���b�V�� ) ]
VERTEXBUFFER_INPUT_INFO_ANDR g_Model_VertexFormat[ 2 ][ 3 ] =
{
	// �o���v�}�b�v�Ȃ�
	{
		// ���̃��b�V��
		{
			64,
			6,
			{
				{ ANDROID_VERTEX_ATTR_POS_F3,       NULL,  0 },
				{ ANDROID_VERTEX_ATTR_NRM,		    NULL, 12 },
				{ ANDROID_VERTEX_ATTR_DIF,		    NULL, 24 },
				{ ANDROID_VERTEX_ATTR_SPC,		    NULL, 28 },
				{ ANDROID_VERTEX_ATTR_TEXUV0_F4,    NULL, 32 },
				{ ANDROID_VERTEX_ATTR_TEXUV1_F4,    NULL, 48 },
			},
		},

		// 4�{�[�����X�L�j���O���b�V��
		{
			96,
			8,
			{
				{ ANDROID_VERTEX_ATTR_POS_F3,       NULL,  0 },
				{ ANDROID_VERTEX_ATTR_NRM,		    NULL, 12 },
				{ ANDROID_VERTEX_ATTR_DIF,		    NULL, 24 },
				{ ANDROID_VERTEX_ATTR_SPC,		    NULL, 28 },
				{ ANDROID_VERTEX_ATTR_TEXUV0_F4,    NULL, 32 },
				{ ANDROID_VERTEX_ATTR_TEXUV1_F4,    NULL, 48 },
				{ ANDROID_VERTEX_ATTR_BLENDIND0,    NULL, 64 },
				{ ANDROID_VERTEX_ATTR_BLENDWEIGHT0, NULL, 80 },
			},
		},

		// 8�{�[�����X�L�j���O���b�V��
		{
			128,
			10,
			{
				{ ANDROID_VERTEX_ATTR_POS_F3,       NULL,  0 },
				{ ANDROID_VERTEX_ATTR_NRM,		    NULL, 12 },
				{ ANDROID_VERTEX_ATTR_DIF,		    NULL, 24 },
				{ ANDROID_VERTEX_ATTR_SPC,		    NULL, 28 },
				{ ANDROID_VERTEX_ATTR_TEXUV0_F4,    NULL, 32 },
				{ ANDROID_VERTEX_ATTR_TEXUV1_F4,    NULL, 48 },
				{ ANDROID_VERTEX_ATTR_BLENDIND0,    NULL, 64 },
				{ ANDROID_VERTEX_ATTR_BLENDWEIGHT0, NULL, 80 },
				{ ANDROID_VERTEX_ATTR_BLENDIND1,    NULL, 96 },
				{ ANDROID_VERTEX_ATTR_BLENDWEIGHT1, NULL, 112 },
			},
		},
	},

	// �o���v�}�b�v����
	{
		// ���̃��b�V��
		{
			86,
			8,
			{
				{ ANDROID_VERTEX_ATTR_POS_F3,       NULL,  0 },
				{ ANDROID_VERTEX_ATTR_NRM,		    NULL, 12 },
				{ ANDROID_VERTEX_ATTR_DIF,		    NULL, 24 },
				{ ANDROID_VERTEX_ATTR_SPC,		    NULL, 28 },
				{ ANDROID_VERTEX_ATTR_TEXUV0_F4,    NULL, 32 },
				{ ANDROID_VERTEX_ATTR_TEXUV1_F4,    NULL, 48 },
				{ ANDROID_VERTEX_ATTR_TAN,          NULL, 64 },
				{ ANDROID_VERTEX_ATTR_BIN,          NULL, 76 },
			},
		},

		// 4�{�[�����X�L�j���O���b�V��
		{
			120,
			10,
			{
				{ ANDROID_VERTEX_ATTR_POS_F3,       NULL,  0 },
				{ ANDROID_VERTEX_ATTR_NRM,		    NULL, 12 },
				{ ANDROID_VERTEX_ATTR_DIF,		    NULL, 24 },
				{ ANDROID_VERTEX_ATTR_SPC,		    NULL, 28 },
				{ ANDROID_VERTEX_ATTR_TEXUV0_F4,    NULL, 32 },
				{ ANDROID_VERTEX_ATTR_TEXUV1_F4,    NULL, 48 },
				{ ANDROID_VERTEX_ATTR_TAN,          NULL, 64 },
				{ ANDROID_VERTEX_ATTR_BIN,          NULL, 76 },
				{ ANDROID_VERTEX_ATTR_BLENDIND0,    NULL, 88 },
				{ ANDROID_VERTEX_ATTR_BLENDWEIGHT0, NULL, 104 },
			},
		},

		// 8�{�[�����X�L�j���O���b�V��
		{
			152,
			12,
			{
				{ ANDROID_VERTEX_ATTR_POS_F3,	    NULL,   0 },
				{ ANDROID_VERTEX_ATTR_NRM,		    NULL,  12 },
				{ ANDROID_VERTEX_ATTR_DIF,		    NULL,  24 },
				{ ANDROID_VERTEX_ATTR_SPC,		    NULL,  28 },
				{ ANDROID_VERTEX_ATTR_TEXUV0_F4,    NULL,  32 },
				{ ANDROID_VERTEX_ATTR_TEXUV1_F4,    NULL,  48 },
				{ ANDROID_VERTEX_ATTR_TAN,          NULL,  64 },
				{ ANDROID_VERTEX_ATTR_BIN,          NULL,  76 },
				{ ANDROID_VERTEX_ATTR_BLENDIND0,    NULL,  88 },
				{ ANDROID_VERTEX_ATTR_BLENDWEIGHT0, NULL, 104 },
				{ ANDROID_VERTEX_ATTR_BLENDIND1,    NULL, 120 },
				{ ANDROID_VERTEX_ATTR_BLENDWEIGHT1, NULL, 136 },
			},
		},
	}
} ;

MV1_MODEL_MANAGE_ANDR MV1Man_Android ;

// �֐��v���g�^�C�v�錾 -------------------------------------------------------

// ���_�o�b�t�@�̍쐬�����C���X���b�h�ōs�����߂̊֐�
static int glGenVertexBuffer_ASync(
	GLuint     *VertexBuffer,
	GLsizeiptr  VertexBufferSize,
	int         ASyncThread
) ;

// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬�����C���X���b�h�ōs�����߂̊֐�
static int glGenVertexAndIndexBuffer_ASync(
	GLuint		*VertexBuffer,
	GLsizeiptr	 VertexBufferSize,
	GLuint		*IndexBuffer,
	GLsizeiptr	 IndexBufferSize,
	int			 ASyncThread
) ;

// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍폜�����C���X���b�h�ōs�����߂̊֐�
static int glDeleteVertexAndIndexBuffer_ASync(
	GLuint      *VertexBuffer,
	GLuint      *IndexBuffer,
	int          ASyncThread
) ;

// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�ւ̃f�[�^�̓]�������C���X���b�h�ōs�����߂̊֐�
static int glSubDataVertexAndIndexBuffer_ASync(
	GLuint        VertexBuffer,
	GLsizeiptr    VertexBufferSize,
	const GLvoid *VertexData, 
	GLuint        IndexBuffer,
	GLsizeiptr    IndexBufferSize,
	const GLvoid *IndexData,
	int           ASyncThread
) ;

// �v���O����------------------------------------------------------------------

// �ėp�o�b�t�@�֐�

// �w��T�C�Y�̔ėp�o�b�t�@�̏������s��
extern int MV1_ANDR_CommonBuffer_Setup( int Size )
{
	if( Size <= MV1Man_Android.CommonBufferSize )
	{
		return 0 ;
	}

	MV1_ANDR_CommonBuffer_Terminate() ;

	Size += MV1_ANDR_COMMONBUFFER_ADDSIZE ;
	Size = ( Size + 15 ) / 16 * 16 ;

	MV1Man_Android.CommonBuffer = DXALLOC( ( size_t )Size ) ;
	if( MV1Man_Android.CommonBuffer == NULL )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\xe2\x30\xc7\x30\xeb\x30\xe6\x51\x06\x74\x28\x75\x6e\x30\x4e\x6c\x28\x75\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x28\x00\x20\x00\xb5\x30\xa4\x30\xba\x30\x20\x00\x25\x00\x64\x00\x20\x00\x62\x00\x79\x00\x74\x00\x65\x00\x20\x00\x29\x00\x0a\x00\x00"/*@ L"���f�������p�̔ėp�o�b�t�@�̍쐬�Ɏ��s���܂���( �T�C�Y %d byte )\n" @*/, Size ) ) ;
		return -1 ;
	}

	MV1Man_Android.CommonBufferSize = Size ;

	// ����I��
	return 0 ;
}

// �ėp�o�b�t�@�̌�n�����s��
extern int MV1_ANDR_CommonBuffer_Terminate( void )
{
	if( MV1Man_Android.CommonBuffer == NULL )
	{
		return 0 ;
	}

	DXFREE( MV1Man_Android.CommonBuffer ) ;
	MV1Man_Android.CommonBuffer = NULL ;

	MV1Man_Android.CommonBufferSize = 0 ;

	return 0 ;
}








// ���ˑ��֐�

// ���f���@�\�̌�n��
extern int MV1_Terminate_PF( void )
{
	// �ėp�o�b�t�@�̉��
	MV1_ANDR_CommonBuffer_Terminate() ;

	return 0 ;
}

// ���f���f�[�^�n���h���̌�n��
extern int MV1_TerminateModelBaseHandle_PF( MV1_MODEL_BASE *ModelBase )
{
	// �I��
	return 0 ;
}

// �g���C�A���O�����X�g�̈ꎞ�����p�̃o�b�t�@���J������
extern int MV1_TerminateTriangleListBaseTempBuffer_PF( MV1_TRIANGLE_LIST_BASE *MBTList )
{
	MV1_TRIANGLE_LIST_BASE_PF *MBTListPF ;

	MBTListPF = ( MV1_TRIANGLE_LIST_BASE_PF * )MBTList->PFBuffer ;

	if( MBTListPF->SkinFreeBoneVertexBuffer )
	{
		DXFREE( MBTListPF->SkinFreeBoneVertexBuffer ) ;
		MBTListPF->SkinFreeBoneVertexBuffer = NULL ;
	}

	// �I��
	return 0 ;
}

// ���������`��֌W�̏����Z�b�g�A�b�v����
extern void MV1_SetupPackDrawInfo_PF( MV1_MODEL_BASE *ModelBase )
{
	MV1_TRIANGLE_LIST_BASE *MBTList ;
	int MaxPackDrawNum ;
	int UseBoneNum ;
	int i ;

	// �ő哯���`�搔������o��
	ModelBase->PackDrawMaxNum = WORD_MAX / ModelBase->TriangleListMinVertexNum ;

	MaxPackDrawNum = WORD_MAX / ModelBase->TriangleListMinIndexNum ;
	if( ModelBase->PackDrawMaxNum > MaxPackDrawNum )
	{
		ModelBase->PackDrawMaxNum = MaxPackDrawNum ;
	}

	MaxPackDrawNum = DX_ANDR_VS_CONST_WORLD_MAT_NUM / ModelBase->TriangleListMinMatrixNum ;
	if( ModelBase->PackDrawMaxNum > MaxPackDrawNum )
	{
		ModelBase->PackDrawMaxNum = MaxPackDrawNum ;
	}

	MBTList = ModelBase->TriangleList ;
	for( i = 0 ; i < ModelBase->TriangleListNum ; i ++, MBTList ++ )
	{
		switch( MBTList->VertexType )
		{
		case MV1_VERTEX_TYPE_NORMAL :
			UseBoneNum = 1 ;
			break ;

		case MV1_VERTEX_TYPE_SKIN_FREEBONE :
			continue ;

		default :
			UseBoneNum = MBTList->UseBoneNum ;
			break ;
		}

		MBTList->PackDrawMaxNum = WORD_MAX / MBTList->VertexNum ;

		MaxPackDrawNum = WORD_MAX / ( MBTList->IndexNum + MBTList->ToonOutLineIndexNum ) ;
		if( MBTList->PackDrawMaxNum > MaxPackDrawNum )
		{
			MBTList->PackDrawMaxNum = MaxPackDrawNum ;
		}

		MaxPackDrawNum = DX_ANDR_VS_CONST_WORLD_MAT_NUM / UseBoneNum ;
		if( MBTList->PackDrawMaxNum > MaxPackDrawNum )
		{
			MBTList->PackDrawMaxNum = MaxPackDrawNum ;
		}
	}
}

// MV1_ANDR_SetupVertexBufferBase_PF �̒��_�f�[�^�쐬�p�̕⏕�֐�
__inline void MV1_ANDR_SetVertexData(
	      BYTE **		DestP,
	const VECTOR *		Position,
	const VECTOR *		Normal,
	const COLOR_U8 *	Diffuse,
	const COLOR_U8 *	Specular,
	const FLOAT2 *		TexCoord0		= NULL,
	const FLOAT2 *		TexCoord1		= NULL,
	const VECTOR *		Tangent			= NULL,
	const VECTOR *		Binormal		= NULL,
	const BYTE *		BlendIndices0	= NULL,
	const FLOAT4 *		BlendWeight0	= NULL,
	const BYTE *		BlendIndices1	= NULL,
	const FLOAT4 *		BlendWeight1	= NULL
)
{
	BYTE *Dest = *DestP ;

	*( ( VECTOR * )Dest )		= *Position ;
	Dest += sizeof( VECTOR ) ;

	*( ( VECTOR * )Dest )		= *Normal ;
	Dest += sizeof( VECTOR ) ;

	( ( COLOR_U8 * )Dest )->r	= Diffuse->b ;
	( ( COLOR_U8 * )Dest )->g	= Diffuse->g ;
	( ( COLOR_U8 * )Dest )->b	= Diffuse->r ;
	( ( COLOR_U8 * )Dest )->a	= Diffuse->a ;
	Dest += sizeof( COLOR_U8 ) ;

	( ( COLOR_U8 * )Dest )->r	= Specular->b ;
	( ( COLOR_U8 * )Dest )->g	= Specular->g ;
	( ( COLOR_U8 * )Dest )->b	= Specular->r ;
	( ( COLOR_U8 * )Dest )->a	= Specular->a ;
	Dest += sizeof( COLOR_U8 ) ;

	if( TexCoord0 != NULL )
	{
		( ( FLOAT4 * )Dest )->x = TexCoord0->u ;
		( ( FLOAT4 * )Dest )->y = TexCoord0->v ;
	}
	else
	{
		( ( FLOAT4 * )Dest )->x = 0.0f ;
		( ( FLOAT4 * )Dest )->y = 0.0f ;
	}
	( ( FLOAT4 * )Dest )->z = 1.0f ;
	( ( FLOAT4 * )Dest )->w = 1.0f ;
	Dest += sizeof( FLOAT4 ) ;

	if( TexCoord1 != NULL )
	{
		( ( FLOAT4 * )Dest )->x = TexCoord1->u ;
		( ( FLOAT4 * )Dest )->y = TexCoord1->v ;
	}
	else
	{
		if( TexCoord0 != NULL )
		{
			( ( FLOAT4 * )Dest )->x = TexCoord0->u ;
			( ( FLOAT4 * )Dest )->y = TexCoord0->v ;
		}
		else
		{
			( ( FLOAT4 * )Dest )->x = 0.0f ;
			( ( FLOAT4 * )Dest )->y = 0.0f ;
		}
	}
	( ( FLOAT4 * )Dest )->z = 1.0f ;
	( ( FLOAT4 * )Dest )->w = 1.0f ;
	Dest += sizeof( FLOAT4 ) ;

	if( Tangent != NULL )
	{
		*( ( VECTOR * )Dest )	= *Tangent ;
		Dest += sizeof( VECTOR ) ;
	}

	if( Binormal != NULL )
	{
		*( ( VECTOR * )Dest )	= *Binormal ;
		Dest += sizeof( VECTOR ) ;
	}

	if( BlendIndices0 != NULL )
	{
		( ( float * )Dest )[ 0 ] = ( float )( BlendIndices0[ 0 ] * 3 ) ;
		( ( float * )Dest )[ 1 ] = ( float )( BlendIndices0[ 1 ] * 3 ) ;
		( ( float * )Dest )[ 2 ] = ( float )( BlendIndices0[ 2 ] * 3 ) ;
		( ( float * )Dest )[ 3 ] = ( float )( BlendIndices0[ 3 ] * 3 ) ;
		Dest += sizeof( FLOAT4 ) ;
	}

	if( BlendWeight0 != NULL )
	{
		*( ( FLOAT4 * )Dest ) = *BlendWeight0 ;
		Dest += sizeof( FLOAT4 ) ;
	}

	if( BlendIndices1 != NULL )
	{
		( ( float * )Dest )[ 0 ] = ( BYTE )( BlendIndices1[ 0 ] * 3 ) ;
		( ( float * )Dest )[ 1 ] = ( BYTE )( BlendIndices1[ 1 ] * 3 ) ;
		( ( float * )Dest )[ 2 ] = ( BYTE )( BlendIndices1[ 2 ] * 3 ) ;
		( ( float * )Dest )[ 3 ] = ( BYTE )( BlendIndices1[ 3 ] * 3 ) ;
		Dest += sizeof( FLOAT4 ) ;
	}

	if( BlendWeight1 != NULL )
	{
		*( ( FLOAT4 * )Dest ) = *BlendWeight1 ;
		Dest += sizeof( FLOAT4 ) ;
	}

	*DestP = Dest ;
}

// ���_�f�[�^�̃T�C�Y���擾����
static DWORD MV1_ANDR_GetVertexSize( int Bump, int Type /* 0:����  1:4�{�[��  2:8�{�[�� */  )
{
	DWORD Result ;

	Result = 
		sizeof( VECTOR ) +				//	{ "POSITION",     0, D_DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D_ANDR_INPUT_PER_VERTEX_DATA, 0 },
		sizeof( VECTOR ) +				//	{ "NORMAL",       0, D_DXGI_FORMAT_R32G32B32_FLOAT,    0, 12, D_ANDR_INPUT_PER_VERTEX_DATA, 0 },
		sizeof( COLOR_U8 ) +			//	{ "COLOR",        0, D_DXGI_FORMAT_B8G8R8A8_UNORM,     0, 24, D_ANDR_INPUT_PER_VERTEX_DATA, 0 },
		sizeof( COLOR_U8 ) +			//	{ "COLOR",        1, D_DXGI_FORMAT_B8G8R8A8_UNORM,     0, 28, D_ANDR_INPUT_PER_VERTEX_DATA, 0 },
		sizeof( FLOAT4 ) +				//	{ "TEXCOORD",     0, D_DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D_ANDR_INPUT_PER_VERTEX_DATA, 0 },
		sizeof( FLOAT4 ) ;				//	{ "TEXCOORD",     1, D_DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48, D_ANDR_INPUT_PER_VERTEX_DATA, 0 },

	if( Bump != 0 )
	{
		Result +=
			sizeof( VECTOR ) +			//	MakeANDRInputElement( "TANGENT",      0, D_DXGI_FORMAT_R32G32B32_FLOAT,    0, offset ) ;
			sizeof( VECTOR ) ;			//	MakeANDRInputElement( "BINORMAL",     0, D_DXGI_FORMAT_R32G32B32_FLOAT,    0, offset ) ;
	}

	switch( Type )
	{
	case 0 :	// ���̃��b�V��
		break ;

	case 1 :	// �S�{�[���ȓ��X�L�j���O���b�V��
	case 2 :	// �W�{�[���ȓ��X�L�j���O���b�V��
		Result +=
			sizeof( FLOAT4 ) +			//	MakeANDRInputElement( "BLENDINDICES", 0, D_DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offset ) ;
			sizeof( FLOAT4 ) ;			//	MakeANDRInputElement( "BLENDWEIGHT",  0, D_DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offset ) ;

		// �W�{�[���ȓ��X�L�j���O���b�V��
		if( Type == 2 )
		{
			Result +=
				sizeof( FLOAT4 ) +		//	MakeANDRInputElement( "BLENDINDICES", 1, D_DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offset ) ;
				sizeof( FLOAT4 ) ;		//	MakeANDRInputElement( "BLENDWEIGHT",  1, D_DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offset ) ;
		}
		break ;
	}

	return Result ;
}

#ifndef DX_NON_ASYNCLOAD
static int glGenVertexBuffer_ASyncCallback( ASYNCLOAD_MAINTHREAD_REQUESTINFO *Info )
{
	return glGenVertexBuffer_ASync(
		( GLuint *   )Info->Data[ 0 ],
		( GLsizeiptr )Info->Data[ 1 ],
		FALSE ) ;
}
#endif // DX_NON_ASYNCLOAD

// ���_�o�b�t�@�̍쐬�����C���X���b�h�ōs�����߂̊֐�
static int glGenVertexBuffer_ASync(
	GLuint     *VertexBuffer,
	GLsizeiptr  VertexBufferSize,
	int         ASyncThread
)
{
#ifndef DX_NON_ASYNCLOAD
	if( ASyncThread )
	{
		ASYNCLOAD_MAINTHREAD_REQUESTINFO AInfo ;

		AInfo.Function = glGenVertexBuffer_ASyncCallback ;
		AInfo.Data[ 0 ] = ( DWORD_PTR )VertexBuffer ;
		AInfo.Data[ 1 ] = ( DWORD_PTR )VertexBufferSize ;
		return AddASyncLoadRequestMainThreadInfo( &AInfo ) ;
	}
#endif // DX_NON_ASYNCLOAD

	glGenBuffers( 1, VertexBuffer ) ;
	glBindBuffer( GL_ARRAY_BUFFER, *VertexBuffer ) ;
	glBufferData( GL_ARRAY_BUFFER, VertexBufferSize, NULL, GL_STATIC_DRAW ) ;

	return 0 ;
}

#ifndef DX_NON_ASYNCLOAD
static int glGenVertexAndIndexBuffer_ASyncCallback( ASYNCLOAD_MAINTHREAD_REQUESTINFO *Info )
{
	return glGenVertexAndIndexBuffer_ASync(
		( GLuint *   )Info->Data[ 0 ],
		( GLsizeiptr )Info->Data[ 1 ],
		( GLuint *   )Info->Data[ 2 ],
		( GLsizeiptr )Info->Data[ 3 ],
		FALSE ) ;
}
#endif // DX_NON_ASYNCLOAD

// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬�����C���X���b�h�ōs�����߂̊֐�
static int glGenVertexAndIndexBuffer_ASync(
	GLuint		*VertexBuffer,
	GLsizeiptr	 VertexBufferSize,
	GLuint		*IndexBuffer,
	GLsizeiptr	 IndexBufferSize,
	int			 ASyncThread
)
{
#ifndef DX_NON_ASYNCLOAD
	if( ASyncThread )
	{
		ASYNCLOAD_MAINTHREAD_REQUESTINFO AInfo ;

		AInfo.Function = glGenVertexAndIndexBuffer_ASyncCallback ;
		AInfo.Data[ 0 ] = ( DWORD_PTR )VertexBuffer ;
		AInfo.Data[ 1 ] = ( DWORD_PTR )VertexBufferSize ;
		AInfo.Data[ 2 ] = ( DWORD_PTR )IndexBuffer ;
		AInfo.Data[ 3 ] = ( DWORD_PTR )IndexBufferSize ;
		return AddASyncLoadRequestMainThreadInfo( &AInfo ) ;
	}
#endif // DX_NON_ASYNCLOAD

	// ���_�o�b�t�@���쐬
	glGenBuffers( 1, VertexBuffer ) ;
	glBindBuffer( GL_ARRAY_BUFFER, *VertexBuffer ) ;
	glBufferData( GL_ARRAY_BUFFER, VertexBufferSize, NULL, GL_STATIC_DRAW ) ;

	// �C���f�b�N�X�o�b�t�@���쐬
	glGenBuffers( 1, IndexBuffer ) ;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, *IndexBuffer ) ;
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, IndexBufferSize, NULL, GL_STATIC_DRAW ) ;

	glBindBuffer( GL_ARRAY_BUFFER, 0 ) ;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ) ;

	return 0 ;
}

#ifndef DX_NON_ASYNCLOAD
static int glDeleteVertexAndIndexBuffer_ASyncCallback( ASYNCLOAD_MAINTHREAD_REQUESTINFO *Info )
{
	return glDeleteVertexAndIndexBuffer_ASync(
		( GLuint * )Info->Data[ 0 ],
		( GLuint * )Info->Data[ 1 ],
		FALSE ) ;
}
#endif // DX_NON_ASYNCLOAD

// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍폜�����C���X���b�h�ōs�����߂̊֐�
static int glDeleteVertexAndIndexBuffer_ASync(
	GLuint      *VertexBuffer,
	GLuint      *IndexBuffer,
	int          ASyncThread
)
{
#ifndef DX_NON_ASYNCLOAD
	if( ASyncThread )
	{
		ASYNCLOAD_MAINTHREAD_REQUESTINFO AInfo ;

		AInfo.Function = glDeleteVertexAndIndexBuffer_ASyncCallback ;
		AInfo.Data[ 0 ] = ( DWORD_PTR )VertexBuffer ;
		AInfo.Data[ 1 ] = ( DWORD_PTR )IndexBuffer ;
		return AddASyncLoadRequestMainThreadInfo( &AInfo ) ;
	}
#endif // DX_NON_ASYNCLOAD

	if( *VertexBuffer )
	{
		glDeleteBuffers( 1, VertexBuffer ) ;
		*VertexBuffer = 0 ;
	}

	if( *IndexBuffer )
	{
		glDeleteBuffers( 1, IndexBuffer ) ;
		*IndexBuffer = 0 ;
	}

	return 0 ;
}

#ifndef DX_NON_ASYNCLOAD
static int glSubDataVertexAndIndexBuffer_ASyncCallback( ASYNCLOAD_MAINTHREAD_REQUESTINFO *Info )
{
	return glSubDataVertexAndIndexBuffer_ASync(
		( GLuint         )Info->Data[ 0 ],
		( GLsizeiptr     )Info->Data[ 1 ],
		( const GLvoid * )Info->Data[ 2 ],
		( GLuint         )Info->Data[ 3 ],
		( GLsizeiptr     )Info->Data[ 4 ],
		( const GLvoid * )Info->Data[ 5 ],
		FALSE ) ;
}
#endif // DX_NON_ASYNCLOAD

// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�ւ̃f�[�^�̓]�������C���X���b�h�ōs�����߂̊֐�
static int glSubDataVertexAndIndexBuffer_ASync(
	GLuint        VertexBuffer,
	GLsizeiptr    VertexBufferSize,
	const GLvoid *VertexData, 
	GLuint        IndexBuffer,
	GLsizeiptr    IndexBufferSize,
	const GLvoid *IndexData,
	int           ASyncThread
)
{
#ifndef DX_NON_ASYNCLOAD
	if( ASyncThread )
	{
		ASYNCLOAD_MAINTHREAD_REQUESTINFO AInfo ;

		AInfo.Function = glSubDataVertexAndIndexBuffer_ASyncCallback ;
		AInfo.Data[ 0 ] = ( DWORD_PTR )VertexBuffer ;
		AInfo.Data[ 1 ] = ( DWORD_PTR )VertexBufferSize ;
		AInfo.Data[ 2 ] = ( DWORD_PTR )VertexData ;
		AInfo.Data[ 3 ] = ( DWORD_PTR )IndexBuffer ;
		AInfo.Data[ 4 ] = ( DWORD_PTR )IndexBufferSize ;
		AInfo.Data[ 5 ] = ( DWORD_PTR )IndexData ;
		return AddASyncLoadRequestMainThreadInfo( &AInfo ) ;
	}
#endif // DX_NON_ASYNCLOAD

	if( VertexBuffer != 0 )
	{
		glBindBuffer(    GL_ARRAY_BUFFER, VertexBuffer ) ;
		glBufferSubData( GL_ARRAY_BUFFER, 0, VertexBufferSize, VertexData ) ;
		glBindBuffer(    GL_ARRAY_BUFFER, 0 ) ;
	}

	if( IndexBuffer != 0 )
	{
		glBindBuffer(    GL_ELEMENT_ARRAY_BUFFER, IndexBuffer ) ;
		glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, IndexBufferSize, IndexData ) ;
		glBindBuffer(    GL_ELEMENT_ARRAY_BUFFER, 0 ) ;
	}

	return 0 ;
}

// ���f����f�[�^�̒��_�o�b�t�@�̃Z�b�g�A�b�v������( -1:�G���[ )
extern	int	MV1_SetupVertexBufferBase_PF( int MV1ModelBaseHandle, int DuplicateNum, int ASyncThread )
{
	int i, j, k, l, Type, UVType, Bump, VertexNum, UVNum, MeshVertSize, BaseMatrixIndex ;
	MV1_MODEL_BASE *MBase ;
	MV1_MESH_NORMAL *MeshNorm, *MNorm ;
	MV1_MESH_VERTEX *MeshVert, *MVert ;
	MV1_TRIANGLE_LIST_BASE *MBTList ;
	MV1_VERTEXBUFFER *VBuf[ 3 ][ 2 ][ 9 ], *TVBuf, *TVBuf2 ;
	DWORD *MVInd ;
	int IndexNum ;
	BYTE *Dest, *DestBase ;
	BYTE BlendIndicesTemp[ 4 ] ;
	BYTE BlendIndicesTemp2[ 4 ] ;
	FLOAT4 BlendWeightTemp ;

	// �n���h���`�F�b�N
	if( MV1BMDLCHK( MV1ModelBaseHandle, MBase ) )
	{
		return -1 ;
	}

	// ���ɃZ�b�g�A�b�v����Ă���ꍇ�͉��������I��
	if( MBase->SetupVertexBuffer )
	{
		return 0 ;
	}

	// ��]����I�u�W�F�N�g�R�s�[�̐���ۑ�����
	MBase->ObjectDuplicateNum = DuplicateNum ;

	// ���_�o�b�t�@�̐��𒲂ׂ�
	_MEMSET( MBase->VertexBufferFirst, 0, sizeof( MBase->VertexBufferFirst ) ) ;
	_MEMSET( MBase->VertexBufferLast,  0, sizeof( MBase->VertexBufferLast  ) ) ;
	_MEMSET( MBase->VertexBufferNum,   0, sizeof( MBase->VertexBufferNum   ) ) ;
	MBase->TotalVertexBufferNum = 0 ;
	_MEMSET( VBuf,             0, sizeof( VBuf             ) ) ;
	MBTList = MBase->TriangleList ;
	for( i = 0 ; i < MBase->TriangleListNum ; i ++, MBTList ++ )
	{
		// UV�͂Q�Œ�
		UVType = 2 ;

		// ���_�^�C�v���Z�b�g
		switch( MBTList->VertexType )
		{
		case MV1_VERTEX_TYPE_NORMAL :
			Type = MBase->UsePackDraw ? 1 : 0 ;
			break ;

		case MV1_VERTEX_TYPE_SKIN_4BONE :
			Type = 1 ;
			break ;

		case MV1_VERTEX_TYPE_SKIN_8BONE :
			Type = 2 ;
			break ;

		case MV1_VERTEX_TYPE_SKIN_FREEBONE :
			Type = 0 ;
			break ;

		default :
			continue ;
		}

		// ���������`��ɑΉ�����ꍇ�͒��_���͍ő哯���`��\���{�ɂȂ�
		VertexNum = MBTList->VertexNum ;
		IndexNum  = MBTList->IndexNum + MBTList->ToonOutLineIndexNum ;
		if( MBase->UsePackDraw )
		{
			VertexNum *= MBTList->PackDrawMaxNum ;
			IndexNum  *= MBTList->PackDrawMaxNum ;
		}

		// �o���v�}�b�v�̗L�����Z�b�g
		Bump = MBTList->Container->Material->NormalLayerNum ? 1 : 0 ;

		// �����̐���ۑ�����
//		MBTList->VertexDuplicateNum = ObjectDuplicateNum ;

		// �^�C�v�̃o�b�t�@���m�ۂ���Ă��Ȃ�������m��
		if( VBuf[ Type ][ Bump ][ UVType ] == NULL )
		{
			MBase->TotalVertexBufferNum ++ ;
			MBase->VertexBufferNum[ Type ][ Bump ][ UVType ] ++ ;

			VBuf[ Type ][ Bump ][ UVType ] = ( MV1_VERTEXBUFFER * )DXALLOC( sizeof( MV1_VERTEXBUFFER ) + sizeof( MV1_VERTEXBUFFER_PF ) ) ;
			_MEMSET( VBuf[ Type ][ Bump ][ UVType ], 0, sizeof( MV1_VERTEXBUFFER ) + sizeof( MV1_VERTEXBUFFER_PF ) ) ;

			VBuf[ Type ][ Bump ][ UVType ]->PF                 = ( MV1_VERTEXBUFFER_PF * )( VBuf[ Type ][ Bump ][ UVType ] + 1 ) ;
			MBase->VertexBufferFirst[ Type ][ Bump ][ UVType ] = VBuf[ Type ][ Bump ][ UVType ] ;
			MBase->VertexBufferLast[  Type ][ Bump ][ UVType ] = VBuf[ Type ][ Bump ][ UVType ] ;
		}
		TVBuf = VBuf[ Type ][ Bump ][ UVType ] ;

		// ���_�I�t�Z�b�g���g�p�ł��Ȃ��̂ŁA�K���V�����o�b�t�@���쐬����
		if( TVBuf->IndexCount > 0 ||
			TVBuf->VertexCount > 0 )
//		// �K�萔�𒴂��Ă��܂��ꍇ�͎��̃o�b�t�@���쐬
//		if( TVBuf->IndexCount  + IndexNum  >= MV1_INDEXBUFFER_MAX_INDEXNUM ||
//			TVBuf->VertexCount + VertexNum >= MV1_VERTEXBUFFER_MAX_VERTNUM )
		{
			MBase->TotalVertexBufferNum ++ ;
			MBase->VertexBufferNum[ Type ][ Bump ][ UVType ] ++ ;

			TVBuf->DataNext = ( MV1_VERTEXBUFFER * )DXALLOC( sizeof( MV1_VERTEXBUFFER ) + sizeof( MV1_VERTEXBUFFER_PF ) ) ;
			_MEMSET( TVBuf->DataNext, 0, sizeof( MV1_VERTEXBUFFER ) + sizeof( MV1_VERTEXBUFFER_PF ) ) ;

			TVBuf->DataNext->PF       = ( MV1_VERTEXBUFFER_PF * )( TVBuf->DataNext + 1 ) ;
			TVBuf->DataNext->DataPrev = TVBuf ;

			MBase->VertexBufferLast[ Type ][ Bump ][ UVType ] = TVBuf->DataNext ;
			VBuf[ Type ][ Bump ][ UVType ]                    = TVBuf->DataNext ;

			TVBuf = VBuf[ Type ][ Bump ][ UVType ] ;
		}

		// �g�p����o�b�t�@��ۑ�
		MBTList->VertexBuffer = TVBuf ;

		// �J�n�A�h���X��ۑ�
		MBTList->VBStartVertex               = TVBuf->VertexCount ;
		MBTList->VBStartIndex                = TVBuf->IndexCount ;
		if( MBase->UsePackDraw )
		{
			MBTList->ToonOutLineVBStartIndex = MBTList->VBStartIndex + MBTList->IndexNum * MBTList->PackDrawMaxNum ;
		}
		else
		{
			MBTList->ToonOutLineVBStartIndex = MBTList->VBStartIndex + MBTList->IndexNum ;
		}

		// ���𑫂�
		TVBuf->VertexCount += VertexNum ;
		TVBuf->IndexCount  += IndexNum ;

	}

	// �������_���Ȃ��o�b�t�@�͍폜����
	for( i = 0 ; i < 3 ; i ++ )
	{
		for( j = 0 ; j < 2 ; j ++ )
		{
			for( k = 0 ; k < 9 ; k ++ )
			{
				TVBuf = MBase->VertexBufferLast[ i ][ j ][ k ] ;
				if( TVBuf == NULL || TVBuf->IndexCount != 0 ) continue ;

				MBase->VertexBufferLast[ i ][ j ][ k ] = TVBuf->DataPrev ;
				if( TVBuf->DataPrev ) TVBuf->DataPrev->DataNext = NULL ;
				DXFREE( TVBuf ) ;

				MBase->TotalVertexBufferNum -- ;
				MBase->VertexBufferNum[ i ][ j ][ k ] -- ;
			}
		}
	}

	// ���_�o�b�t�@���쐬����
	for( i = 0 ; i < 3 ; i ++ )
	{
		for( j = 0 ; j < 2 ; j ++ )
		{
			for( k = 0 ; k < 9 ; k ++ )
			{
				VBuf[ i ][ j ][ k ] = MBase->VertexBufferFirst[ i ][ j ][ k ] ;
				for( TVBuf = VBuf[ i ][ j ][ k ] ; TVBuf ; TVBuf = TVBuf->DataNext )
				{
					// �P���_������̃T�C�Y���擾
					TVBuf->UnitSize = MV1_ANDR_GetVertexSize( j, i ) ;

					// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���쐬
					glGenVertexAndIndexBuffer_ASync(
						&TVBuf->PF->VertexBufferObject, TVBuf->UnitSize * TVBuf->VertexCount,
						&TVBuf->PF->IndexBufferObject,  sizeof( WORD )  * TVBuf->IndexCount,
						ASyncThread
					) ;

					// �]���p�f�[�^���i�[���郁�����̈�̊m��
					TVBuf->VertexBufferL = DXALLOC( TVBuf->UnitSize * TVBuf->VertexCount ) ;
					if( TVBuf->VertexBufferL == NULL )
					{
						goto ERR ;
					}

					// �]���p�f�[�^���i�[���郁�����̈�̊m��
					TVBuf->IndexBufferL = DXALLOC( sizeof( WORD ) * TVBuf->IndexCount ) ;
					if( TVBuf->IndexBufferL == NULL )
					{
						goto ERR ;
					}
				}
			}
		}
	}

	// �e���|�����o�b�t�@�Ƀf�[�^���i�[����
	MBTList = MBase->TriangleList ;
	for( i = 0 ; i < MBase->TriangleListNum ; i ++, MBTList ++ )
	{
		if( MBTList->VertexBuffer == NULL ||
			MBTList->VertexBuffer->PF->VertexBufferObject == 0 ||
			MBTList->VertexBuffer->PF->IndexBufferObject  == 0 )
		{
			continue ;
		}

		// �o���v�}�b�v�̗L�����Z�b�g
		Bump = MBTList->Container->Material->NormalLayerNum ? 1 : 0 ;

		// �g�p���钸�_�o�b�t�@���Z�b�g
		TVBuf = MBTList->VertexBuffer ;

		// ���_�^�C�v�ɂ���ď����𕪊�
		VertexNum    = MBTList->VertexNum ;
		UVNum        = MBTList->Container->UVSetUnitNum ;
		MeshNorm     = MBTList->Container->Container->Normal ;
		MeshVertSize = MBTList->Container->VertUnitSize ;
		MeshVert     = MBTList->Container->Vertex ;
		if( UVNum > 2 )
		{
			UVNum = 2 ;
		}
		switch( MBTList->VertexType )
		{
		case MV1_VERTEX_TYPE_NORMAL :
			{
				MV1_TLIST_NORMAL_POS *Src ;

				if( MBase->UsePackDraw )
				{
					BlendIndicesTemp[ 0 ] = 0 ;
					BlendIndicesTemp[ 1 ] = 0 ;
					BlendIndicesTemp[ 2 ] = 0 ;
					BlendIndicesTemp[ 3 ] = 0 ;

					BlendWeightTemp.x = 1.0f ;
					BlendWeightTemp.y = 0.0f ;
					BlendWeightTemp.z = 0.0f ;
					BlendWeightTemp.w = 0.0f ;

					DestBase = ( BYTE * )TVBuf->VertexBufferL + MBTList->VBStartVertex * MBTList->VertexBuffer->UnitSize ;
					Dest     = DestBase ;
					Src      = ( MV1_TLIST_NORMAL_POS * )ADDR16( MBTList->NormalPosition ) ;
					MVInd    = MBTList->MeshVertexIndex ;
					for( j = 0 ; j < VertexNum ; j ++, Src ++, MVInd ++ )
					{
						MVert = ( MV1_MESH_VERTEX * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
						MNorm = MeshNorm + MVert->NormalIndex ;

						MV1_ANDR_SetVertexData(
							&Dest,
							( VECTOR * )&Src->Position,
							&MNorm->Normal,
							&MVert->DiffuseColor,
							&MVert->SpecularColor,
							UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
							UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
							Bump ? &MNorm->Tangent  : NULL,
							Bump ? &MNorm->Binormal : NULL,
							BlendIndicesTemp,
							&BlendWeightTemp
						) ;
					}

					BaseMatrixIndex = 1 ;
					for( k = 1 ; k < MBTList->PackDrawMaxNum ; k ++, BaseMatrixIndex += 1 )
					{
						Src      = ( MV1_TLIST_NORMAL_POS * )ADDR16( MBTList->NormalPosition ) ;
						MVInd    = MBTList->MeshVertexIndex ;
						for( j = 0 ; j < VertexNum ; j ++, Src ++, MVInd ++ )
						{
							MVert = ( MV1_MESH_VERTEX * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
							MNorm = MeshNorm + MVert->NormalIndex ;

							BlendIndicesTemp[ 0 ] = ( BYTE )BaseMatrixIndex ;

							MV1_ANDR_SetVertexData(
								&Dest,
								( VECTOR * )&Src->Position,
								&MNorm->Normal,
								&MVert->DiffuseColor,
								&MVert->SpecularColor,
								UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
								UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
								Bump ? &MNorm->Tangent  : NULL,
								Bump ? &MNorm->Binormal : NULL,
								BlendIndicesTemp,
								&BlendWeightTemp
							) ;
						}
					}
				}
				else
				{
					Dest	= ( BYTE * )TVBuf->VertexBufferL + MBTList->VBStartVertex * MBTList->VertexBuffer->UnitSize ;
					Src		= ( MV1_TLIST_NORMAL_POS * )ADDR16( MBTList->NormalPosition ) ;
					MVInd   = MBTList->MeshVertexIndex ;
					for( j = 0 ; j < VertexNum ; j ++, Src ++, MVInd ++ )
					{
						MVert = ( MV1_MESH_VERTEX   * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
						MNorm = MeshNorm + MVert->NormalIndex ;

						MV1_ANDR_SetVertexData(
							&Dest,
							( VECTOR * )&Src->Position,
							&MNorm->Normal,
							&MVert->DiffuseColor,
							&MVert->SpecularColor,
							UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
							UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
							Bump ? &MNorm->Tangent  : NULL,
							Bump ? &MNorm->Binormal : NULL
						) ;
					}
				}
			}
			break ;

		case MV1_VERTEX_TYPE_SKIN_4BONE :
			{
				MV1_TLIST_SKIN_POS_4B *Src ;

				DestBase = ( BYTE * )TVBuf->VertexBufferL + MBTList->VBStartVertex * MBTList->VertexBuffer->UnitSize ;
				Dest     = DestBase ;
				Src      = ( MV1_TLIST_SKIN_POS_4B * )ADDR16( MBTList->SkinPosition4B ) ;
				MVInd    = MBTList->MeshVertexIndex ;
				for( j = 0 ; j < VertexNum ; j ++, Src ++, MVInd ++ )
				{
					MVert = ( MV1_MESH_VERTEX   * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
					MNorm = MeshNorm + MVert->NormalIndex ;

					MV1_ANDR_SetVertexData(
						&Dest,
						( VECTOR * )&Src->Position,
						&MNorm->Normal,
						&MVert->DiffuseColor,
						&MVert->SpecularColor,
						UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
						UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
						Bump ? &MNorm->Tangent  : NULL,
						Bump ? &MNorm->Binormal : NULL,
						Src->MatrixIndex,
						( FLOAT4 * )Src->MatrixWeight
					) ;
				}

				if( MBase->UsePackDraw )
				{
					BaseMatrixIndex = MBTList->UseBoneNum ;
					for( k = 1 ; k < MBTList->PackDrawMaxNum ; k ++, BaseMatrixIndex += MBTList->UseBoneNum )
					{
						Src      = ( MV1_TLIST_SKIN_POS_4B * )ADDR16( MBTList->SkinPosition4B ) ;
						MVInd    = MBTList->MeshVertexIndex ;
						for( j = 0 ; j < VertexNum ; j ++, Src ++, MVInd ++ )
						{
							MVert = ( MV1_MESH_VERTEX   * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
							MNorm = MeshNorm + MVert->NormalIndex ;

							BlendIndicesTemp[ 0 ] = ( BYTE )( Src->MatrixIndex[ 0 ] + BaseMatrixIndex ) ;
							BlendIndicesTemp[ 1 ] = ( BYTE )( Src->MatrixIndex[ 1 ] + BaseMatrixIndex ) ;
							BlendIndicesTemp[ 2 ] = ( BYTE )( Src->MatrixIndex[ 2 ] + BaseMatrixIndex ) ;
							BlendIndicesTemp[ 3 ] = ( BYTE )( Src->MatrixIndex[ 3 ] + BaseMatrixIndex ) ;

							MV1_ANDR_SetVertexData(
								&Dest,
								( VECTOR * )&Src->Position,
								&MNorm->Normal,
								&MVert->DiffuseColor,
								&MVert->SpecularColor,
								UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
								UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
								Bump ? &MNorm->Tangent  : NULL,
								Bump ? &MNorm->Binormal : NULL,
								BlendIndicesTemp,
								( FLOAT4 * )Src->MatrixWeight
							) ;
						}
					}
				}
			}
			break ;

		case MV1_VERTEX_TYPE_SKIN_8BONE :
			{
				MV1_TLIST_SKIN_POS_8B *Src ;

				DestBase = ( BYTE * )TVBuf->VertexBufferL + MBTList->VBStartVertex * MBTList->VertexBuffer->UnitSize ;
				Dest     = DestBase ;
				Src      = ( MV1_TLIST_SKIN_POS_8B * )ADDR16( MBTList->SkinPosition8B ) ;
				MVInd    = MBTList->MeshVertexIndex ;
				for( j = 0 ; j < VertexNum ; j ++, Src ++, MVInd ++ )
				{
					MVert = ( MV1_MESH_VERTEX   * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
					MNorm = MeshNorm + MVert->NormalIndex ;

					MV1_ANDR_SetVertexData(
						&Dest,
						( VECTOR * )&Src->Position,
						&MNorm->Normal,
						&MVert->DiffuseColor,
						&MVert->SpecularColor,
						UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
						UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
						Bump ? &MNorm->Tangent  : NULL,
						Bump ? &MNorm->Binormal : NULL,
						Src->MatrixIndex1,
						( FLOAT4 * )&Src->MatrixWeight[ 0 ],
						Src->MatrixIndex2,
						( FLOAT4 * )&Src->MatrixWeight[ 4 ]
					) ;
				}

				if( MBase->UsePackDraw )
				{
					BaseMatrixIndex = MBTList->UseBoneNum ;
					for( k = 1 ; k < MBTList->PackDrawMaxNum ; k ++, BaseMatrixIndex += MBTList->UseBoneNum )
					{
						Src      = ( MV1_TLIST_SKIN_POS_8B * )ADDR16( MBTList->SkinPosition8B ) ;
						MVInd    = MBTList->MeshVertexIndex ;
						for( j = 0 ; j < VertexNum ; j ++, Src ++, MVInd ++ )
						{
							MVert = ( MV1_MESH_VERTEX   * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
							MNorm = MeshNorm + MVert->NormalIndex ;

							BlendIndicesTemp[ 0 ]  = ( BYTE )( Src->MatrixIndex1[ 0 ] + BaseMatrixIndex ) ;
							BlendIndicesTemp[ 1 ]  = ( BYTE )( Src->MatrixIndex1[ 1 ] + BaseMatrixIndex ) ;
							BlendIndicesTemp[ 2 ]  = ( BYTE )( Src->MatrixIndex1[ 2 ] + BaseMatrixIndex ) ;
							BlendIndicesTemp[ 3 ]  = ( BYTE )( Src->MatrixIndex1[ 3 ] + BaseMatrixIndex ) ;

							BlendIndicesTemp2[ 0 ] = ( BYTE )( Src->MatrixIndex2[ 0 ] + BaseMatrixIndex ) ;
							BlendIndicesTemp2[ 1 ] = ( BYTE )( Src->MatrixIndex2[ 1 ] + BaseMatrixIndex ) ;
							BlendIndicesTemp2[ 2 ] = ( BYTE )( Src->MatrixIndex2[ 2 ] + BaseMatrixIndex ) ;
							BlendIndicesTemp2[ 3 ] = ( BYTE )( Src->MatrixIndex2[ 3 ] + BaseMatrixIndex ) ;

							MV1_ANDR_SetVertexData(
								&Dest,
								( VECTOR * )&Src->Position,
								&MNorm->Normal,
								&MVert->DiffuseColor,
								&MVert->SpecularColor,
								UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
								UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
								Bump ? &MNorm->Tangent  : NULL,
								Bump ? &MNorm->Binormal : NULL,
								BlendIndicesTemp,
								( FLOAT4 * )&Src->MatrixWeight[ 0 ],
								BlendIndicesTemp2,
								( FLOAT4 * )&Src->MatrixWeight[ 4 ]
							) ;
						}
					}
				}
			}
			break ;

		case MV1_VERTEX_TYPE_SKIN_FREEBONE :
			{
				MV1_TLIST_SKIN_POS_FREEB *Src ;

				if( MBase->UsePackDraw )
				{
					// ��Ή�
				}
				else
				{
					Dest	= ( BYTE * )TVBuf->VertexBufferL + MBTList->VBStartVertex * MBTList->VertexBuffer->UnitSize ;
					Src		= ( MV1_TLIST_SKIN_POS_FREEB * )ADDR16( MBTList->SkinPositionFREEB ) ;
					MVInd   = MBTList->MeshVertexIndex ;
					for( j = 0 ; j < VertexNum ; j ++, Src = ( MV1_TLIST_SKIN_POS_FREEB * )( ( BYTE * )Src + MBTList->PosUnitSize ), MVInd ++ )
					{
						MVert = ( MV1_MESH_VERTEX   * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
						MNorm = MeshNorm + MVert->NormalIndex ;

						MV1_ANDR_SetVertexData(
							&Dest,
							( VECTOR * )&Src->Position,
							&MNorm->Normal,
							&MVert->DiffuseColor,
							&MVert->SpecularColor,
							UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
							UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
							Bump ? &MNorm->Tangent  : NULL,
							Bump ? &MNorm->Binormal : NULL
						) ;
					}
				}
			}
			break ;
		}

		// �C���f�b�N�X�f�[�^�̏�������
		{
			WORD *Dest, *ToonDest ;
			int DestBaseIndex ;
			int ToonDestBaseIndex ;

			Dest     = ( WORD * )( ( BYTE * )TVBuf->IndexBufferL + MBTList->VBStartIndex            * sizeof( WORD ) ) ;
			ToonDest = ( WORD * )( ( BYTE * )TVBuf->IndexBufferL + MBTList->ToonOutLineVBStartIndex * sizeof( WORD ) ) ;
			_MEMCPY( Dest, MBTList->Index, sizeof( WORD ) * MBTList->IndexNum ) ;
			if( MBTList->ToonOutLineIndexNum > 0 )
			{
				_MEMCPY( ToonDest, MBTList->ToonOutLineIndex, sizeof( WORD ) * MBTList->ToonOutLineIndexNum ) ;
			}

			if( MBase->UsePackDraw )
			{
				Dest              += MBTList->IndexNum ;
				DestBaseIndex      = MBTList->VertexNum ;

				ToonDest          += MBTList->ToonOutLineIndexNum ;
				ToonDestBaseIndex  = MBTList->VertexNum ;
				for( j = 1 ; j < MBTList->PackDrawMaxNum ; j ++ )
				{
					_MEMCPY( Dest, MBTList->Index, sizeof( WORD ) * MBTList->IndexNum ) ;
					for( k = 0 ; k < MBTList->IndexNum ; k ++, Dest ++ )
					{
						*Dest += ( WORD )DestBaseIndex ;
					}
					DestBaseIndex += MBTList->VertexNum ;

					if( MBTList->ToonOutLineIndexNum > 0 )
					{
						_MEMCPY( ToonDest, MBTList->ToonOutLineIndex, sizeof( WORD ) * MBTList->ToonOutLineIndexNum ) ;
						for( k = 0 ; k < MBTList->ToonOutLineIndexNum ; k ++, ToonDest ++ )
						{
							*ToonDest += ( WORD )ToonDestBaseIndex ;
						}
						ToonDestBaseIndex += MBTList->VertexNum ;
					}
				}
			}
		}
	}

	// ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�փe���|�����o�b�t�@�̓��e��]��
	for( i = 0 ; i < 3 ; i ++ )
	{
		for( j = 0 ; j < 2 ; j ++ )
		{
			for( k = 0 ; k < 9 ; k ++ )
			{
				for( TVBuf = MBase->VertexBufferFirst[ i ][ j ][ k ] ; TVBuf ; TVBuf = TVBuf2 )
				{
					TVBuf2 = TVBuf->DataNext ;

					// �o�b�t�@���m�ۂł��Ă��Ȃ�������������
					if( TVBuf->PF->VertexBufferObject == 0 ||
						TVBuf->PF->IndexBufferObject  == 0 )
					{
						if( TVBuf->DataPrev != NULL )
						{
							TVBuf->DataPrev->DataNext = TVBuf->DataNext ;
						}
						else
						{
							MBase->VertexBufferFirst[ i ][ j ][ k ] = TVBuf->DataNext ;
						}

						if( TVBuf->DataNext != NULL )
						{
							TVBuf->DataNext->DataPrev = TVBuf->DataPrev ;
						}
						else
						{
							MBase->VertexBufferLast[ i ][ j ][ k ] = TVBuf->DataPrev ;
						}

						if( TVBuf->VertexBufferL != NULL )
						{
							DXFREE( TVBuf->VertexBufferL ) ;
							TVBuf->VertexBufferL = NULL ;
						}

						if( TVBuf->IndexBufferL != NULL )
						{
							DXFREE( TVBuf->IndexBufferL ) ;
							TVBuf->IndexBufferL = NULL ;
						}

						glDeleteVertexAndIndexBuffer_ASync(
							&TVBuf->PF->VertexBufferObject,
							&TVBuf->PF->IndexBufferObject,
							ASyncThread
						) ;

						// ���̃o�b�t�@���g�p���Ă����g���C�A���O�����X�g�̃|�C���^���N���A����
						MBTList = MBase->TriangleList ;
						for( l = 0 ; l < MBase->TriangleListNum ; l ++, MBTList ++ )
						{
							if( MBTList->VertexBuffer != TVBuf ) continue ;
							MBTList->VertexBuffer = NULL ;
						}

						DXFREE( TVBuf ) ;
						MBase->VertexBufferNum[ i ][ j ][ k ] -- ;
						MBase->TotalVertexBufferNum -- ;
					}
					else
					{
						// �m�ۂł��Ă�����f�[�^��]������
						glSubDataVertexAndIndexBuffer_ASync(
							TVBuf->PF->VertexBufferObject, TVBuf->UnitSize * TVBuf->VertexCount, TVBuf->VertexBufferL,
							TVBuf->PF->IndexBufferObject,  sizeof( WORD ) * TVBuf->IndexCount,   TVBuf->IndexBufferL,
							ASyncThread
						) ;
					}
				}
			}
		}
	}

	// �e���|�����o�b�t�@�̉��
	for( i = 0 ; i < 3 ; i ++ )
	{
		for( j = 0 ; j < 2 ; j ++ )
		{
			for( k = 0 ; k < 9 ; k ++ )
			{
				for( TVBuf = MBase->VertexBufferFirst[ i ][ j ][ k ] ; TVBuf ; TVBuf = TVBuf->DataNext )
				{
					if( TVBuf->VertexBufferL )
					{
						DXFREE( TVBuf->VertexBufferL ) ;
						TVBuf->VertexBufferL = NULL ;
					}

					if( TVBuf->IndexBufferL )
					{
						DXFREE( TVBuf->IndexBufferL ) ;
						TVBuf->IndexBufferL = NULL ;
					}
				}
			}
		}
	}

	// �Z�b�g�A�b�v�����t���O�𗧂Ă�
	MBase->SetupVertexBuffer = TRUE ;

	// ���̃n���h�����g�p���Ă��郂�f���̒��_�o�b�t�@���Z�b�g�A�b�v����
	{
		MV1_MODEL *Model ;

		if( HandleManageArray[ DX_HANDLETYPE_MODEL ].InitializeFlag )
		{
			for( i = HandleManageArray[ DX_HANDLETYPE_MODEL ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_MODEL ].AreaMax ; i ++ )
			{
				Model = ( MV1_MODEL * )HandleManageArray[ DX_HANDLETYPE_MODEL ].Handle[ i ] ;
				if( Model == NULL ) continue ;
#ifndef DX_NON_ASYNCLOAD
				if( Model->HandleInfo.ASyncLoadCount != 0 ) continue ;
#endif // DX_NON_ASYNCLOAD
				if( Model->BaseData != MBase ) continue ;

				MV1_SetupVertexBuffer_PF( Model->HandleInfo.Handle, ASyncThread ) ;
			}
		}
	}

	// �I��
	return 0 ;

ERR:
	// �m�ۂ������_�o�b�t�@�Ȃǂ����
	for( i = 0 ; i < 3 ; i ++ )
	{
		for( j = 0 ; j < 2 ; j ++ )
		{
			for( k = 0 ; k < 9 ; k ++ )
			{
				for( TVBuf = MBase->VertexBufferFirst[ i ][ j ][ k ] ; TVBuf ; TVBuf = TVBuf2 )
				{
					if( TVBuf->VertexBufferL )
					{
						DXFREE( TVBuf->VertexBufferL ) ;
						TVBuf->VertexBufferL = NULL ;
					}

					if( TVBuf->IndexBufferL )
					{
						DXFREE( TVBuf->IndexBufferL ) ;
						TVBuf->IndexBufferL = NULL ;
					}

					glDeleteVertexAndIndexBuffer_ASync(
						&TVBuf->PF->VertexBufferObject,
						&TVBuf->PF->IndexBufferObject,
						ASyncThread
					) ;

					TVBuf2 = TVBuf->DataNext ;
					DXFREE( TVBuf ) ;
				}
				MBase->VertexBufferFirst[ i ][ j ][ k ] = NULL ;
				MBase->VertexBufferLast[ i ][ j ][ k ] = NULL ;
				MBase->VertexBufferNum[ i ][ j ][ k ] = 0 ;
			}
		}
	}
	MBase->TotalVertexBufferNum = 0 ;

	// �I��
	return -1 ;
}

// ���f���f�[�^�̒��_�o�b�t�@�̃Z�b�g�A�b�v������( -1:�G���[ )
extern int MV1_SetupVertexBuffer_PF( int MHandle, int ASyncThread )
{
	MV1_MODEL              *Model ;
	MV1_MODEL_BASE         *MBase ;
	MV1_MESH               *Mesh ;
	MV1_MESH_BASE          *MBMesh ;
	MV1_FRAME_BASE         *MBFrame ;
	MV1_FRAME              *Frame ;
	MV1_TRIANGLE_LIST      *TList ;
	MV1_TRIANGLE_LIST_BASE *MBTList ;
	int                    i ;
	int                    l ;
	int                    m ;

	// ����������Ă��Ȃ�������G���[
	if( MV1Man.Initialize == false )
	{
		return -1 ;
	}

	// �A�h���X�擾
	if( ASyncThread )
	{
		if( MV1MDLCHK_ASYNC( MHandle, Model ) )
			return -1 ;
	}
	else
	{
		if( MV1MDLCHK( MHandle, Model ) )
			return -1 ;
	}
	MBase = Model->BaseData ;

	// �V�F�C�v���g�p����Ă���t���[���̂ݏ�������
	MBFrame = MBase->Frame ;
	Frame = Model->Frame ;
	for( i = 0 ; i < MBase->FrameNum ; i ++, Frame ++, MBFrame ++ )
	{
		if( MBFrame->ShapeNum == 0 ) continue ;

		MBMesh = MBFrame->Mesh ;
		Mesh = Frame->Mesh ;
		for( l = 0 ; l < MBFrame->MeshNum ; l ++, MBMesh ++, Mesh ++ )
		{
			if( MBMesh->Shape == 0 ) continue ;

			MBTList = MBMesh->TriangleList ;
			TList = Mesh->TriangleList ;
			for( m = 0 ; m < MBMesh->TriangleListNum ; m ++, MBTList ++, TList = ( MV1_TRIANGLE_LIST * )( ( BYTE * )TList + sizeof( MV1_TRIANGLE_LIST ) + sizeof( MV1_TRIANGLE_LIST_PF ) ) )
			{
				// �X�{�[���ȏ�̃X�L�j���O���b�V�����ǂ����ŏ����𕪊�
				if( MBTList->VertexType == MV1_VERTEX_TYPE_SKIN_FREEBONE )
				{
					// �V�X�e���������o�b�t�@�̊m�ۂ��s��
					if( TList->PF->SkinFreeBoneVertexPositionBuffer == NULL )
					{
						TList->PF->SkinFreeBoneVertexPositionBuffer = DXALLOC( sizeof( VECTOR ) * MBTList->VertexNum ) ;
						if( TList->PF->SkinFreeBoneVertexPositionBuffer == NULL )
						{
							return -1 ;
						}

						// �V�F�C�v�̃Z�b�g�A�b�v���s���Ă��Ȃ���Ԃɂ���
						Model->ShapeChangeFlag = true ;
						TList->Container->Container->ShapeChangeFlag = true ;
					}
				}
				else
				{
					// ���_�o�b�t�@���Z�b�g�A�b�v����Ă��Ȃ������炷��
					if( TList->PF->VertexBufferObject == 0 && MBTList->VertexBuffer != NULL )
					{
						glGenVertexBuffer_ASync(
							&TList->PF->VertexBufferObject,
							MBTList->VertexBuffer->UnitSize * MBTList->VertexNum,
							ASyncThread
						) ;

						// �V�F�C�v�̃Z�b�g�A�b�v���s���Ă��Ȃ���Ԃɂ���
						Model->ShapeChangeFlag = true ;
						TList->Container->Container->ShapeChangeFlag = true ;
					}
				}
			}
		}
	}

	// �I��
	return 0 ;
}

// ���_�o�b�t�@�̌�n��������( -1:�G���[ )
extern int MV1_TerminateVertexBufferBase_PF( int MV1ModelBaseHandle )
{
	int i, j, k ;
	MV1_MODEL_BASE *MBase ;
	MV1_MODEL *Model ;
	MV1_TRIANGLE_LIST_BASE *MBTList ;
	MV1_VERTEXBUFFER *TVBuf, *TVBuf2 ;

	// �n���h���`�F�b�N
	if( MV1BMDLCHK( MV1ModelBaseHandle, MBase ) )
	{
		return -1 ;
	}

	if( MBase == NULL )
	{
		return -1 ;
	}

	// ���_�o�b�t�@���Z�b�g�A�b�v����Ă��Ȃ��ꍇ�͉��������I��
	if( MBase->SetupVertexBuffer == FALSE )
	{
		return 0 ;
	}

	// �m�ۂ������_�o�b�t�@�Ȃǂ����
	for( i = 0 ; i < 3 ; i ++ )
	{
		for( j = 0 ; j < 2 ; j ++ )
		{
			for( k = 0 ; k < 9 ; k ++ )
			{
				for( TVBuf = MBase->VertexBufferFirst[ i ][ j ][ k ] ; TVBuf ; )
				{
					if( TVBuf->PF->VertexBufferObject )
					{
						glDeleteBuffers( 1, &TVBuf->PF->VertexBufferObject ) ;
						TVBuf->PF->VertexBufferObject = 0 ;
					}

					if( TVBuf->PF->IndexBufferObject )
					{
						glDeleteBuffers( 1, &TVBuf->PF->IndexBufferObject ) ;
						TVBuf->PF->IndexBufferObject = 0 ;
					}

					TVBuf2 = TVBuf->DataNext ;
					DXFREE( TVBuf ) ;
					TVBuf = TVBuf2 ;
				}
				MBase->VertexBufferFirst[ i ][ j ][ k ] = NULL ;
				MBase->VertexBufferLast[ i ][ j ][ k ] = NULL ;
				MBase->VertexBufferNum[ i ][ j ][ k ] = 0 ;
			}
		}
	}
	MBase->TotalVertexBufferNum = 0 ;

	// �g���C�A���O�����X�g�̐������J��Ԃ�
	MBTList = MBase->TriangleList ;
	for( i = 0 ; i < MBase->TriangleListNum ; i ++, MBTList ++ )
	{
		// ���_�o�b�t�@�̏����N���A
		MBTList->VertexBuffer = NULL ;
		MBTList->VBStartVertex = 0 ;
		MBTList->VBStartIndex = 0 ;
	}

	// ���_�o�b�t�@�Z�b�g�A�b�v�t���O��|��
	MBase->SetupVertexBuffer = FALSE ;

	// ���̃n���h�����g�p���Ă��郂�f���̒��_�o�b�t�@���������
	if( HandleManageArray[ DX_HANDLETYPE_MODEL ].InitializeFlag )
	{
		for( i = HandleManageArray[ DX_HANDLETYPE_MODEL ].AreaMin ; i <= HandleManageArray[ DX_HANDLETYPE_MODEL ].AreaMax ; i ++ )
		{
			Model = ( MV1_MODEL * )HandleManageArray[ DX_HANDLETYPE_MODEL ].Handle[ i ] ;
			if( Model == NULL ) continue ;
#ifndef DX_NON_ASYNCLOAD
			if( Model->HandleInfo.ASyncLoadCount != 0 ) continue ;
#endif // DX_NON_ASYNCLOAD
			if( Model->BaseData != MBase ) continue ;

			MV1_TerminateVertexBuffer_PF( Model->HandleInfo.Handle ) ;
		}
	}

	// �I��
	return 0 ;
}

// ���_�o�b�t�@�̌�n��������( -1:�G���[ )
extern int MV1_TerminateVertexBuffer_PF( int MV1ModelHandle )
{
	int i ;
	MV1_MODEL *Model ;
	MV1_TRIANGLE_LIST *TList ;

	// �n���h���`�F�b�N
	if( MV1MDLCHK_ASYNC( MV1ModelHandle, Model ) )
	{
		return -1 ;
	}

	// �g���C�A���O�����X�g�̐������J��Ԃ�
	TList = Model->TriangleList ;
	for( i = 0 ; i < Model->BaseData->TriangleListNum ; i ++, TList = ( MV1_TRIANGLE_LIST * )( ( BYTE * )TList + sizeof( MV1_TRIANGLE_LIST ) + sizeof( MV1_TRIANGLE_LIST_PF ) ) )
	{
		// �X�{�[���ȏ�̃X�L�j���O���b�V���p�̃o�b�t�@���m�ۂ��Ă�������
		if( TList->PF->SkinFreeBoneVertexPositionBuffer != NULL )
		{
			DXFREE( TList->PF->SkinFreeBoneVertexPositionBuffer ) ;
			TList->PF->SkinFreeBoneVertexPositionBuffer = NULL ;
		}

		// ���_�o�b�t�@�̏����N���A
		if( TList->PF->VertexBufferObject )
		{
			glDeleteBuffers( 1, &TList->PF->VertexBufferObject ) ;
			TList->PF->VertexBufferObject = 0 ;
		}
	}

	// �I��
	return 0 ;
}

// �V�F�C�v�f�[�^�̃Z�b�g�A�b�v������
extern int MV1_SetupShapeVertex_PF( int MHandle )
{
	MV1_MODEL              *Model ;
	MV1_MODEL_BASE         *MBase ;
	MV1_MESH               *Mesh ;
	MV1_MESH_BASE          *MBMesh ;
	MV1_FRAME_BASE         *MBFrame ;
	MV1_FRAME              *Frame ;
	MV1_TRIANGLE_LIST      *TList ;
	MV1_TRIANGLE_LIST_BASE *MBTList ;
	MV1_SHAPE              *Shape ;
	MV1_SHAPE_BASE         *MBShape ;
	MV1_SHAPE_MESH_BASE    *MBShapeMesh ;
	MV1_SHAPE_VERTEX       *ShapeVertex ;
	MV1_SHAPE_VERTEX       *SVert ;
	MV1_SHAPE_VERTEX_BASE  *MBShapeVertex ;
	MV1_MESH_VERTEX        *MeshVertex ;
	MV1_MESH_NORMAL        *MeshNorm ;
	MV1_MESH_NORMAL        *MNorm ;
	MV1_MESH_VERTEX        *MeshVert ;
	MV1_MESH_VERTEX        *MVert ;
	MV1_MODEL_ANIM         *MAnim ;
	MV1_MODEL_ANIM         *MAnim2 ;
	MV1_MODEL_ANIMSET      *MAnimSet ;
	int                    i ;
	int                    j ;
	int                    k ;
	int                    l ;
	int                    m ;
	int                    VertexNum ;
	int                    UVNum ;
	int                    MeshVertSize ;
//	DWORD                  DestUnitSize ;
	DWORD                  *MVInd ;
	float                  Rate ;
	int                    Bump ;
	BYTE                   *Dest ;

	// ����������Ă��Ȃ�������G���[
	if( MV1Man.Initialize == false )
	{
		return -1 ;
	}

	// �A�h���X�擾
	if( MV1MDLCHK( MHandle, Model ) )
	{
		return -1 ;
	}
	MBase = Model->BaseData ;

	// �V�F�C�v�̏�Ԃ��ω����Ă��Ȃ��ꍇ�͉������Ȃ�
	if( Model->ShapeChangeFlag == false )
	{
		return 0 ;
	}
	Model->ShapeChangeFlag = false ;

	// �V�F�C�v���g�p����Ă��郁�b�V���̂ݏ�������
	MBMesh = MBase->Mesh ;
	Mesh = Model->Mesh ;
	for( i = 0 ; i < MBase->MeshNum ; i ++, Mesh ++, MBMesh ++ )
	{
		if( MBMesh->Shape == 0 )
		{
			continue ;
		}

		// �V�F�C�v���ω����Ă��Ȃ��ꍇ�͉������Ȃ�
		if( Mesh->Container->ShapeChangeFlag == false )
		{
			continue ;
		}

		// �������_�f�[�^�̍쐬
		MBFrame = MBMesh->Container ;

		// �ŏ��͊�̒��_�f�[�^���Z�b�g
		ShapeVertex = Mesh->ShapeVertex ;
		MeshVertex  = MBMesh->Vertex ;
		for( j = 0 ; j < MBMesh->VertexNum ; j ++, ShapeVertex ++, MeshVertex = ( MV1_MESH_VERTEX * )( ( BYTE * )MeshVertex + MBMesh->VertUnitSize ) )
		{
			ShapeVertex->Position = ( ( MV1_MESH_POSITION * )( ( BYTE * )MBFrame->Position + MeshVertex->PositionIndex * MBFrame->PosUnitSize ) )->Position ;
			ShapeVertex->Normal   = MBFrame->Normal[ MeshVertex->NormalIndex ].Normal ;
		}
	}

	// �V�F�C�v���g�p����Ă���t���[���̂ݏ�������
	MBFrame = MBase->Frame ;
	Frame   = Model->Frame ;
	MAnim   = Model->Anim ;
	for( i = 0 ; i < MBase->FrameNum ; i ++, Frame ++, MBFrame ++, MAnim += Model->AnimSetMaxNum )
	{
		if( MBFrame->ShapeNum == 0 )
		{
			continue ;
		}

		// �V�F�C�v���ω����Ă��Ȃ��ꍇ�͉������Ȃ�
		if( Frame->ShapeChangeFlag == false )
		{
			continue ;
		}
		Frame->ShapeChangeFlag = false ;

		// �V�F�C�v���g�p���Ȃ��t���O�������Ă������{��񂻂̂܂܂��g�p����
		if( Model->ShapeDisableFlag == false )
		{
			Shape = Frame->Shape ;
			for( j = 0 ; j < MBFrame->ShapeNum ; j ++, Shape ++ )
			{
				MBShape = Shape->BaseData ;

				// �u�����h�����擾����
				Rate = 0.0f ;
				switch( Shape->ShapeRateApplyType )
				{
				case DX_MV1_SHAPERATE_ADD :
					Rate     = Shape->ShapeRate ;
					MAnim2   = MAnim ;
					MAnimSet = Model->AnimSet ;
					for( k = 0 ; k < Model->AnimSetMaxNum ; k ++, MAnim2 ++, MAnimSet ++ )
					{
						if( MAnim2->Use == false )
						{
							continue ;
						}

						if( MAnimSet->DisableShapeFlag )
						{
							continue ;
						}

						Rate += MAnim2->BlendRate * MAnim2->Anim->ShapeRate[ j ] ;
					}
					break ;

				case DX_MV1_SHAPERATE_OVERWRITE :
					Rate     = Shape->ShapeRate ;
					break ;
				}
				if( Rate < 0.0000001f ) continue ;

				MBShapeMesh = MBShape->Mesh ;
				for( k = 0 ; k < MBShape->MeshNum ; k ++, MBShapeMesh ++ )
				{
					Mesh = MBShapeMesh->TargetMesh - MBase->Mesh + Model->Mesh ;
					MBMesh = Mesh->BaseData ;

					MBShapeVertex = MBShapeMesh->Vertex ;
					for( l = 0 ; ( DWORD )l < MBShapeMesh->VertexNum ; l ++, MBShapeVertex ++ )
					{
						ShapeVertex              = &Mesh->ShapeVertex[ MBShapeVertex->TargetMeshVertex ] ;
						ShapeVertex->Position.x += MBShapeVertex->Position.x * Rate ;
						ShapeVertex->Position.y += MBShapeVertex->Position.y * Rate ;
						ShapeVertex->Position.z += MBShapeVertex->Position.z * Rate ;
						ShapeVertex->Normal.x   += MBShapeVertex->Normal.x   * Rate ;
						ShapeVertex->Normal.y   += MBShapeVertex->Normal.y   * Rate ;
						ShapeVertex->Normal.z   += MBShapeVertex->Normal.z   * Rate ;
					}
				}
			}
		}

		MBMesh = MBFrame->Mesh ;
		Mesh   = Frame->Mesh ;
		for( l = 0 ; l < MBFrame->MeshNum ; l ++, MBMesh ++, Mesh ++ )
		{
			if( MBMesh->Shape == 0 ) continue ;

			MeshNorm     = MBMesh->Container->Normal ;
			UVNum        = MBMesh->UVSetUnitNum ;
			MeshVertSize = MBMesh->VertUnitSize ;
			MeshVert     = MBMesh->Vertex ;
			ShapeVertex  = Mesh->ShapeVertex ;
			Bump         = MBMesh->Material->NormalLayerNum ? 1 : 0 ;

			MBTList = MBMesh->TriangleList ;
			TList   = Mesh->TriangleList ;
			for( m = 0 ; m < MBMesh->TriangleListNum ; m ++, MBTList ++, TList = ( MV1_TRIANGLE_LIST * )( ( BYTE * )TList + sizeof( MV1_TRIANGLE_LIST ) + sizeof( MV1_TRIANGLE_LIST_PF ) ) )
			{
				MVInd = MBTList->MeshVertexIndex ;
				VertexNum = MBTList->VertexNum ;

				// �X�{�[���ȏ�̃X�L�j���O���b�V�����ǂ����ŏ����𕪊�
				if( MBTList->VertexType == MV1_VERTEX_TYPE_SKIN_FREEBONE )
				{
					if( TList->PF->SkinFreeBoneVertexPositionBuffer == NULL )
					{
						continue ;
					}

					Dest = ( BYTE * )TList->PF->SkinFreeBoneVertexPositionBuffer ;
				}
				else
				{
					if( TList->PF->VertexBufferObject == 0 )
					{
						continue ;
					}

					// �e���|�����o�b�t�@�̏���
					if( MV1_ANDR_CommonBuffer_Setup( ( int )( MBTList->VertexBuffer->UnitSize * MBTList->VertexNum ) ) < 0 )
					{
						continue ;
					}

					Dest = ( BYTE * )MV1Man_Android.CommonBuffer ;
				}

//				DestUnitSize = MBTList->VertexBuffer->UnitSize ;
				switch( MBTList->VertexType )
				{
				case MV1_VERTEX_TYPE_NORMAL :
					for( j = 0 ; j < VertexNum ; j ++, MVInd ++ )
					{
						MVert = ( MV1_MESH_VERTEX   * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
						MNorm = MeshNorm + MVert->NormalIndex ;
						SVert = ShapeVertex + *MVInd ;

						MV1_ANDR_SetVertexData(
							&Dest,
							&SVert->Position,
							&MNorm->Normal,
							&MVert->DiffuseColor,
							&MVert->SpecularColor,
							UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
							UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
							Bump ? &MNorm->Tangent  : NULL,
							Bump ? &MNorm->Binormal : NULL
						) ;
					}
					break ;

				case MV1_VERTEX_TYPE_SKIN_4BONE :
					{
						MV1_TLIST_SKIN_POS_4B *Src ;

						Src = ( MV1_TLIST_SKIN_POS_4B * )ADDR16( MBTList->SkinPosition4B ) ;
						for( j = 0 ; j < VertexNum ; j ++, Src ++, MVInd ++ )
						{
							MVert = ( MV1_MESH_VERTEX   * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
							MNorm = MeshNorm + MVert->NormalIndex ;
							SVert = ShapeVertex + *MVInd ;

							MV1_ANDR_SetVertexData(
								&Dest,
								&SVert->Position,
								&MNorm->Normal,
								&MVert->DiffuseColor,
								&MVert->SpecularColor,
								UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
								UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
								Bump ? &MNorm->Tangent  : NULL,
								Bump ? &MNorm->Binormal : NULL,
								Src->MatrixIndex,
								( FLOAT4 * )Src->MatrixWeight
							) ;
						}
					}
					break ;

				case MV1_VERTEX_TYPE_SKIN_8BONE :
					{
						MV1_TLIST_SKIN_POS_8B *Src ;

						Src = ( MV1_TLIST_SKIN_POS_8B * )ADDR16( MBTList->SkinPosition8B ) ;
						for( j = 0 ; j < VertexNum ; j ++, Src ++, MVInd ++ )
						{
							MVert = ( MV1_MESH_VERTEX   * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
							MNorm = MeshNorm + MVert->NormalIndex ;
							SVert = ShapeVertex + *MVInd ;

							MV1_ANDR_SetVertexData(
								&Dest,
								&SVert->Position,
								&MNorm->Normal,
								&MVert->DiffuseColor,
								&MVert->SpecularColor,
								UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
								UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
								Bump ? &MNorm->Tangent  : NULL,
								Bump ? &MNorm->Binormal : NULL,
								Src->MatrixIndex1,
								( FLOAT4 * )&Src->MatrixWeight[ 0 ],
								Src->MatrixIndex2,
								( FLOAT4 * )&Src->MatrixWeight[ 4 ]
							) ;
						}
					}
					break ;

				case MV1_VERTEX_TYPE_SKIN_FREEBONE :
					{
						MV1_TLIST_SKIN_POS_FREEB *Src ;
						DWORD SrcUnitSize ;

						Src         = ( MV1_TLIST_SKIN_POS_FREEB * )ADDR16( MBTList->SkinPositionFREEB ) ;
						SrcUnitSize = MBTList->PosUnitSize ;
						for( j = 0 ; j < VertexNum ; j ++, Src = ( MV1_TLIST_SKIN_POS_FREEB * )( ( BYTE * )Src + SrcUnitSize ), Dest += sizeof( VECTOR ), MVInd ++ )
						{
							SVert = ShapeVertex + *MVInd ;

							*( ( VECTOR * )Dest ) = SVert->Position ;
						}
					}
					break ;
				}

				if( MBTList->VertexType != MV1_VERTEX_TYPE_SKIN_FREEBONE )
				{
					// ���_�f�[�^���X�V
					glBindBuffer( GL_ARRAY_BUFFER, TList->PF->VertexBufferObject ) ;
					glBufferSubData( GL_ARRAY_BUFFER, 0, MBTList->VertexBuffer->UnitSize * MBTList->VertexNum, MV1Man_Android.CommonBuffer ) ;
				}
			}
		}
	}

	glBindBuffer( GL_ARRAY_BUFFER, 0 ) ;

	// �I��
	return 0 ;
}

// �R�c���f���̃����_�����O�̏������s��
extern int MV1_BeginRender_PF( MV1_MODEL *Model )
{
	int i ;

	// �o�b�t�@�ɂ��܂��Ă��钸�_���o��
	NS_RenderVertex() ;

	// Graphics_Android_RenderBegin �����s���Ă��Ȃ���������s����
	if( GANDR.Device.DrawInfo.BeginSceneFlag == FALSE )
	{
		Graphics_Android_RenderBegin() ;
	}

	// ���C�g�̐ݒ肪�ύX����Ă����甽�f����
	Graphics_Light_RefreshState() ;

	MV1Man.WorldMatrixIsIdentity = FALSE ;

	// �[�x�o�b�t�@�ݒ�𔽉f����
	Graphics_Android_DeviceState_SetDepthEnable(      Model->EnableZBufferFlag ) ;
	Graphics_Android_DeviceState_SetDepthWriteEnable( Model->WriteZBufferFlag ) ;
	Graphics_Android_DeviceState_SetDepthFunc(        g_DXCmpModeToGLES2CompareFunc[ Model->ZBufferCmpType ] ) ;
	Graphics_Android_DeviceState_SetDepthBias(        Model->ZBias ) ;

	// �t�H�O�̐ݒ�𔽉f����
	Graphics_DrawSetting_ApplyLibFogToHardware() ;

	// �ٕ����t�B���^�����O�̍ő原����ݒ肷��
	for( i = 0 ; i < 3 ; i ++ )
	{
		Graphics_Android_DeviceState_SetMaxAnisotropy( Model->MaxAnisotropy, i ) ;
	}

	// �R�c�s����n�[�h�E�G�A�ɔ��f����
	if( GSYS.DrawSetting.MatchHardware3DMatrix == FALSE && GSYS.Setting.ValidHardware )
		Graphics_DrawSetting_ApplyLib3DMatrixToHardware() ;

	GSYS.DrawSetting.MatchHardwareWorldMatrix    = FALSE ;
	GSYS.DrawSetting.MatchHardware3DMatrix       = FALSE ;

	GANDR.Device.State.DrawMode                 = DX_DRAWMODE_OTHER ;
	GANDR.Device.DrawSetting.AlphaTestMode      = -1 ;
	GANDR.Device.DrawSetting.AlphaTestParam     = 0 ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;
	GANDR.Device.DrawSetting.ChangeTextureFlag  = TRUE ;

	// �J���[�ɃA���t�@�l����Z���邩�ǂ����̏����Z�b�g����
	Graphics_Android_DeviceState_SetMulAlphaColor( Model->UseDrawMulAlphaColor ) ;

	// �I��
	return 0 ;
}

// �R�c���f���̃����_�����O�̌�n�����s��
extern int MV1_EndRender_PF( void )
{
	Graphics_Android_DeviceState_SetWorldMatrix( &GSYS.DrawSetting.WorldMatrixF ) ;

	// �I��
	return 0 ;
}

// �w��̃��b�V���̊�{�����̃}�e���A�����Z�b�g�A�b�v����
static bool MV1_ANDR_SetupMeshDrawMaterialCommon( MV1_MESH *Mesh )
{
	MV1_MESH_BASE     *MBMesh ;
	MATERIALPARAM     Material ;
	MV1_MATERIAL      * RST MMaterial ;
//	MV1_MATERIAL_BASE * RST MBMaterial ;
	MV1_FRAME         * RST Frame ;
	int               BlendMode ;

	Frame      = Mesh->Container ;
	MBMesh     = Mesh->BaseData ;
	MMaterial  = Mesh->Material ;
//	MBMaterial = MMaterial->BaseData ;

	// �}�e���A���̃Z�b�g
	if( Mesh->SetupDrawMaterial.UseColorScale )
	{
		// �A���t�@���O�̏ꍇ�͕`�悵�Ȃ�
		if( Mesh->SetupDrawMaterial.DiffuseScale.a * MMaterial->Diffuse.a <= 0.0000001f )
		{
			return false ;
		}

		Material.Diffuse.r  = MMaterial->Diffuse.r  * Mesh->SetupDrawMaterial.DiffuseScale.r ;
		Material.Diffuse.g  = MMaterial->Diffuse.g  * Mesh->SetupDrawMaterial.DiffuseScale.g ;
		Material.Diffuse.b  = MMaterial->Diffuse.b  * Mesh->SetupDrawMaterial.DiffuseScale.b ;
		Material.Diffuse.a  = MMaterial->Diffuse.a  * Mesh->SetupDrawMaterial.DiffuseScale.a ;
		Material.Specular.r = MMaterial->Specular.r * Mesh->SetupDrawMaterial.SpecularScale.r ;
		Material.Specular.g = MMaterial->Specular.g * Mesh->SetupDrawMaterial.SpecularScale.g ;
		Material.Specular.b = MMaterial->Specular.b * Mesh->SetupDrawMaterial.SpecularScale.b ;
		Material.Specular.a = MMaterial->Specular.a * Mesh->SetupDrawMaterial.SpecularScale.a ;
		Material.Emissive.r = MMaterial->Emissive.r * Mesh->SetupDrawMaterial.EmissiveScale.r ;
		Material.Emissive.g = MMaterial->Emissive.g * Mesh->SetupDrawMaterial.EmissiveScale.g ;
		Material.Emissive.b = MMaterial->Emissive.b * Mesh->SetupDrawMaterial.EmissiveScale.b ;
		Material.Emissive.a = MMaterial->Emissive.a * Mesh->SetupDrawMaterial.EmissiveScale.a ;
		Material.Ambient.r  = MMaterial->Ambient.r  * Mesh->SetupDrawMaterial.AmbientScale.r ;
		Material.Ambient.g  = MMaterial->Ambient.g  * Mesh->SetupDrawMaterial.AmbientScale.g ;
		Material.Ambient.b  = MMaterial->Ambient.b  * Mesh->SetupDrawMaterial.AmbientScale.b ;
		Material.Ambient.a  = MMaterial->Ambient.a  * Mesh->SetupDrawMaterial.AmbientScale.a ;
	}
	else
	{
		// �A���t�@���O�̏ꍇ�͕`�悵�Ȃ�
		if( MMaterial->Diffuse.a <= 0.0000001f )
		{
			return false ;
		}

		Material.Diffuse   = MMaterial->Diffuse ;
		Material.Specular  = MMaterial->Specular ;
		Material.Ambient   = MMaterial->Ambient ;
		Material.Emissive  = MMaterial->Emissive ;
	}
	Material.Power = MMaterial->Power ;
	_MEMCPY( GSYS.Light.MaterialTypeParam , MMaterial->TypeParam, sizeof( MMaterial->TypeParam ) ) ;
	GSYS.Light.ChangeMaterial = 1 ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;
	Graphics_Android_DeviceState_SetMaterial( &Material ) ;

	// �J�����O�ݒ�
	Graphics_Android_DeviceState_SetCullMode( GSYS.DrawSetting.ShadowMapDraw ? FALSE : MBMesh->BackCulling ) ; 

	// �A���t�@�e�X�g�ݒ�
//	if( MMaterial->UseAlphaTest )
//	{
//		Graphics_Android_DeviceState_SetAlphaTestCmpMode( MMaterial->AlphaFunc ) ;
//		Graphics_Android_DeviceState_SetAlphaTestRef(     MMaterial->AlphaRef ) ;
//	}

	// FactorColor �̐ݒ�
	{
		float FloatFactorColor[ 4 ] ;

		FloatFactorColor[ 0 ] = 1.0f ;
		FloatFactorColor[ 1 ] = 1.0f ;
		FloatFactorColor[ 2 ] = 1.0f ;
		FloatFactorColor[ 3 ] = Mesh->SetupDrawMaterial.OpacityRate * ( Mesh->DrawBlendParam != -1 ? Mesh->DrawBlendParam : MMaterial->DrawBlendParam ) / 255.0f ;
		Graphics_Android_DeviceState_SetFactorColor( &FloatFactorColor ) ;
	}

	// ���Z�J���[�̐ݒ�
	NS_SetDrawAddColor( MMaterial->DrawAddColor.x, MMaterial->DrawAddColor.y, MMaterial->DrawAddColor.z ) ; 

	// �u�����h���[�h�̐ݒ�
	BlendMode = GSYS.DrawSetting.ShadowMapDraw ? DX_BLENDMODE_NOBLEND : ( Mesh->DrawBlendMode != -1 ? Mesh->DrawBlendMode : MMaterial->DrawBlendMode ) ;
	switch( BlendMode )
	{
	case DX_BLENDMODE_INVSRC :
	case DX_BLENDMODE_MUL :
	case DX_BLENDMODE_MULA :
	case DX_BLENDMODE_SRCCOLOR :
	case DX_BLENDMODE_NOBLEND :
		Graphics_Android_DeviceState_SetBlendMode( BlendMode, FALSE, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		break ;

	case DX_BLENDMODE_ALPHA :
		if( Frame->Container->UseDrawMulAlphaColor )
		{
			Graphics_Android_DeviceState_SetBlendMode( DX_BLENDMODE_PMA_ALPHA, FALSE, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		}
		else
		{
			Graphics_Android_DeviceState_SetBlendMode( DX_BLENDMODE_ALPHA, FALSE, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		}
		break ;

	case DX_BLENDMODE_ADD :
		if( Frame->Container->UseDrawMulAlphaColor )
		{
			Graphics_Android_DeviceState_SetBlendMode( DX_BLENDMODE_PMA_ADD, FALSE, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		}
		else
		{
			Graphics_Android_DeviceState_SetBlendMode( DX_BLENDMODE_ADD, FALSE, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		}
		break ;
	}

	// �X�y�L�������L�����ǂ������Z�b�g����
	Graphics_Android_DeviceState_SetSpecularEnable(
		MBMesh->UseVertexSpecularColor ||
		Material.Specular.r > 0.00001f ||
		Material.Specular.g > 0.00001f ||
		Material.Specular.b > 0.00001f ? TRUE : FALSE ) ;

	// �f�B�t���[�Y�}�e���A���Ƃ��Ē��_�J���[���g�p���邩�ǂ������Z�b�g
	Graphics_Android_DeviceState_SetUseVertexDiffuseColor( MBMesh->UseVertexDiffuseColor ) ;

	// �X�y�L�����}�e���A���Ƃ��Ē��_�J���[���g�p���邩�ǂ������Z�b�g
	Graphics_Android_DeviceState_SetUseVertexSpecularColor( MBMesh->UseVertexSpecularColor ) ;

	return true ;
}

// �g�D�[���ׂ̈̃}�e���A�����Z�b�g�A�b�v����
static void MV1_ANDR_SetupToonOutLineMeshDrawMaterialCommon( MV1_MESH *Mesh, float OutLineWidth )
{
//	MV1_MESH_BASE     *MBMesh ;
	MATERIALPARAM     Material ;
	MV1_MATERIAL      * RST MMaterial ;
//	MV1_MATERIAL_BASE * RST MBMaterial ;
	MV1_FRAME         * RST Frame ;
	int               BlendMode ;

	Frame      = Mesh->Container ;
//	MBMesh     = Mesh->BaseData ;
	MMaterial  = Mesh->Material ;
//	MBMaterial = MMaterial->BaseData ;

	// �}�e���A���̃Z�b�g
	Material.Diffuse    = MMaterial->OutLineColor ;
	Material.Diffuse.a  = 1.0f ;
	Material.Specular.r = 0.0f ;
	Material.Specular.g = 0.0f ;
	Material.Specular.b = 0.0f ;
	Material.Specular.a = 0.0f ;
	Material.Emissive   = Material.Specular ;
	Material.Ambient    = Material.Specular ;
	Material.Power      = 0.0f ;
	GSYS.Light.ChangeMaterial = 1 ;
	GANDR.Device.DrawSetting.DrawPrepAlwaysFlag = TRUE ;
	Graphics_Android_DeviceState_SetMaterial( &Material ) ;

	// �֊s���̑������Z�b�g����
	Graphics_Android_DeviceState_SetToonOutLineSize( OutLineWidth ) ;

	// �J�����O�ݒ�
	Graphics_Android_DeviceState_SetCullMode( 2 ) ; 

	// FactorColor �̐ݒ�
	{
		float FloatFactorColor[ 4 ] ;

		FloatFactorColor[ 0 ] = 1.0f ;
		FloatFactorColor[ 1 ] = 1.0f ;
		FloatFactorColor[ 2 ] = 1.0f ;
		FloatFactorColor[ 3 ] = ( Mesh->SetupDrawMaterial.OpacityRate * ( Mesh->DrawBlendParam != -1 ? Mesh->DrawBlendParam : MMaterial->DrawBlendParam ) ) / 255.0f ;
		Graphics_Android_DeviceState_SetFactorColor( &FloatFactorColor ) ;
	}

	// ���Z�J���[�̐ݒ�
	NS_SetDrawAddColor( MMaterial->DrawAddColor.x, MMaterial->DrawAddColor.y, MMaterial->DrawAddColor.z ) ; 

	// �u�����h���[�h�̐ݒ�
	BlendMode = GSYS.DrawSetting.ShadowMapDraw ? DX_BLENDMODE_NOBLEND : ( Mesh->DrawBlendMode != -1 ? Mesh->DrawBlendMode : MMaterial->DrawBlendMode ) ;
	switch( BlendMode )
	{
	case DX_BLENDMODE_INVSRC :
	case DX_BLENDMODE_MUL :
	case DX_BLENDMODE_MULA :
	case DX_BLENDMODE_SRCCOLOR :
	case DX_BLENDMODE_NOBLEND :
		Graphics_Android_DeviceState_SetBlendMode( BlendMode, FALSE, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		break ;

	case DX_BLENDMODE_ALPHA :
		if( Frame->Container->UseDrawMulAlphaColor )
		{
			Graphics_Android_DeviceState_SetBlendMode( DX_BLENDMODE_PMA_ALPHA, FALSE, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		}
		else
		{
			Graphics_Android_DeviceState_SetBlendMode( DX_BLENDMODE_ALPHA, FALSE, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		}
		break ;

	case DX_BLENDMODE_ADD :
		if( Frame->Container->UseDrawMulAlphaColor )
		{
			Graphics_Android_DeviceState_SetBlendMode( DX_BLENDMODE_PMA_ADD, FALSE, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		}
		else
		{
			Graphics_Android_DeviceState_SetBlendMode( DX_BLENDMODE_ADD, FALSE, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, DX_BLEND_ONE, DX_BLEND_ZERO, DX_BLENDOP_ADD, GSYS.DrawSetting.NotWriteAlphaChannelFlag ) ;
		}
		break ;
	}

	// �X�y�L�����𖳌��ɂ���
	Graphics_Android_DeviceState_SetSpecularEnable( FALSE ) ;
}

// �O���t�B�b�N�n���h������e�N�X�`�����擾����
static GRAPHICS_ANDROID_TEXTURE	*MV1_ANDR_GetGraphHandleTexture( int GraphHandle )
{
	IMAGEDATA *Image ;

	Image = Graphics_Image_GetData( GraphHandle ) ;
	if( Image == NULL )
	{
		return NULL ;
	}

	return &Image->Hard.Draw[ 0 ].Tex->PF->Texture ;
}

// �V���h�E�}�b�v�n���h������e�N�X�`�����擾����
static GRAPHICS_ANDROID_TEXTURE	*MV1_ANDR_GetShadowMapHandleTexture( int ShadowMapHandle )
{
	SHADOWMAPDATA *ShadowMap ;

	ShadowMap = Graphics_ShadowMap_GetData( ShadowMapHandle ) ;
	if( ShadowMap == NULL )
	{
		return NULL ;
	}

	return &ShadowMap->PF->Texture ;
}

// MV1_TEXTURE ����e�N�X�`�����擾����
static GRAPHICS_ANDROID_TEXTURE	*MV1_ANDR_GetTextureTexture( MV1_TEXTURE *Tex )
{
	MV1_TEXTURE_BASE *TexBase ;
	int               GraphHandle ;

	TexBase = Tex->BaseData ;
	if( Tex->UseUserGraphHandle )
	{
		GraphHandle = Tex->UserGraphHandle ;
	}
	else
	if( Tex->UseGraphHandle )
	{
		GraphHandle = Tex->GraphHandle ;
	}
	else
	if( TexBase->UseUserGraphHandle )
	{
		GraphHandle = TexBase->UserGraphHandle ;
	}
	else
	{
		GraphHandle = TexBase->GraphHandle ;
	}

	return MV1_ANDR_GetGraphHandleTexture( GraphHandle ) ;
}

// �e�N�X�`�������������ꍇ�ɃZ�b�g����e�N�X�`�����擾����
static GRAPHICS_ANDROID_TEXTURE	*MV1_ANDR_GetNoneGraphHandleTexture( void )
{
	// �f�t�H���g�e�N�X�`���n���h���̏������`�F�b�N
	if( MV1Man.TexNoneHandle < 0 )
	{
		MV1SetupTexNoneHandle() ;
	}
	return MV1_ANDR_GetGraphHandleTexture( MV1Man.TexNoneHandle ) ;
}

// �w��̃��b�V���̃}�e���A�����Z�b�g�A�b�v����
static void MV1_ANDR_SetupMeshDrawMaterial( MV1_MESH *Mesh )
{
	MV1_TEXTURE_BASE			*TexBase ;
	MV1_TEXTURE					*Tex ;
	MV1_FRAME					*Frame ;
	MV1_MODEL					*Model ;
//	MV1_MATERIAL				* RST MMaterial ;
//	int							BlendMode ;
	int							TextureUVScaling ;
	float						TextureScaleU ;
	float						TextureScaleV ;
	GRAPHICS_ANDROID_TEXTURE	*SetTexture[ 16 ] = { NULL } ;
	int							SetTextureNum = 0 ;
	int							IsToon ;

	// ���ʕ����̃Z�b�g
	Frame     = Mesh->Container ;
	Model     = Frame->Container ;
//	MMaterial = Mesh->Material ;
//	BlendMode = Mesh->DrawBlendMode != -1 ? Mesh->DrawBlendMode : MMaterial->DrawBlendMode ;
	IsToon    = Mesh->Material->BaseData->Type == DX_MATERIAL_TYPE_TOON || Mesh->Material->BaseData->Type == DX_MATERIAL_TYPE_TOON_2 ;

	// �f�B�t���[�Y�e�N�X�`���̃X�P�[���� 1.0f �ȊO���𒲂ׂ�
	TextureUVScaling = FALSE ;
	if( Mesh->Material->DiffuseLayerNum > 0 )
	{
		Tex = &Model->Texture[ Mesh->Material->DiffuseLayer[ 0 ].Texture ] ;

		if( Tex->ScaleU - 1.0f >  0.0001f || Tex->ScaleU - 1.0f < -0.0001f ||
			Tex->ScaleV - 1.0f >  0.0001f || Tex->ScaleV - 1.0f < -0.0001f )
		{
			TextureUVScaling = TRUE ;
			TextureScaleU = Tex->ScaleU ;
			TextureScaleV = Tex->ScaleV ;
		}
	}

	// �e�N�X�`�����W�ϊ��p�����[�^�̃Z�b�g
	if( Frame->TextureAddressTransformUse == FALSE && TextureUVScaling == FALSE )
	{
		if( GSYS.DrawSetting.TextureAddressTransformUse )
		{
			GSYS.DrawSetting.MatchHardwareTextureAddressTransformMatrix = FALSE ;
		}

		Graphics_Android_DeviceState_SetTextureAddressTransformMatrix( FALSE, NULL ) ;
	}
	else
	{
		GSYS.DrawSetting.MatchHardwareTextureAddressTransformMatrix = FALSE ;

		if( TextureUVScaling )
		{
			MATRIX TempMatrix ;

			TempMatrix = Frame->TextureAddressTransformMatrix ;
			TempMatrix.m[ 0 ][ 0 ] *= TextureScaleU ;
			TempMatrix.m[ 1 ][ 1 ] *= TextureScaleV ;

			Graphics_Android_DeviceState_SetTextureAddressTransformMatrix( TRUE, &TempMatrix ) ;
		}
		else
		{
			Graphics_Android_DeviceState_SetTextureAddressTransformMatrix( TRUE, &Frame->TextureAddressTransformMatrix ) ;
		}
	}

	// �e�N�X�`���̃Z�b�g�A�b�v
	{
		if( Mesh->Material->DiffuseLayerNum )
		{
			Tex = &Model->Texture[ Mesh->Material->DiffuseLayer[ 0 ].Texture ] ;
			SetTexture[ 0 ] = MV1_ANDR_GetTextureTexture( Tex ) ;
			Graphics_Android_DeviceState_SetTextureAddressUVW( Tex->AddressModeU, Tex->AddressModeV, DX_TEXADDRESS_CLAMP, 0 ) ;
			Graphics_Android_DeviceState_SetSampleFilterMode( DrawModeToFilterTable[ SetTexture[ 0 ]->MipMapCount <= 1 ? 0 : 1 ][ Tex->FilterMode ], 0 ) ;
		}
		else
		{
			SetTexture[ 0 ] = MV1_ANDR_GetNoneGraphHandleTexture() ;
			Graphics_Android_DeviceState_SetSampleFilterMode( GL_NEAREST, 0 ) ;
		}
		SetTextureNum = 1 ;

		if( Mesh->BaseData->Material->NormalLayerNum )
		{
			SetTextureNum = 2 ;

			Tex = &Model->Texture[ Mesh->BaseData->Material->NormalLayer[ 0 ].Texture ] ;
			SetTexture[ 1 ] = MV1_ANDR_GetTextureTexture( Tex ) ;
			Graphics_Android_DeviceState_SetTextureAddressUVW( Tex->AddressModeU, Tex->AddressModeV, DX_TEXADDRESS_CLAMP, 1 ) ;
			Graphics_Android_DeviceState_SetSampleFilterMode( DrawModeToFilterTable[ SetTexture[ 1 ]->MipMapCount <= 1 ? 0 : 1 ][ Tex->FilterMode ], 1 ) ;
		}

		if( Mesh->Material->SpecularLayerNum )
		{
			SetTextureNum = 3 ;

			Tex = &Model->Texture[ Mesh->Material->SpecularLayer[ 0 ].Texture ] ;
			SetTexture[ 2 ] = MV1_ANDR_GetTextureTexture( Tex ) ;
			Graphics_Android_DeviceState_SetTextureAddressUVW( Tex->AddressModeU, Tex->AddressModeV, DX_TEXADDRESS_CLAMP, 2 ) ;
			Graphics_Android_DeviceState_SetSampleFilterMode( DrawModeToFilterTable[ SetTexture[ 2 ]->MipMapCount <= 1 ? 0 : 1 ][ Tex->FilterMode ], 2 ) ;
		}
		else
		{
			SetTextureNum = 3 ;

			SetTexture[ 2 ] = MV1_ANDR_GetNoneGraphHandleTexture() ;
			Graphics_Android_DeviceState_SetSampleFilterMode( GL_NEAREST, 2 ) ;
		}

		if( IsToon )
		{
			SetTextureNum = 5 ;

			if( Mesh->Material->DiffuseGradTexture >= 0 )
			{
				Tex = &Model->Texture[ Mesh->Material->DiffuseGradTexture ] ;
				SetTexture[ 3 ] = MV1_ANDR_GetTextureTexture( Tex ) ;
				Graphics_Android_DeviceState_SetTextureAddressUVW( Tex->AddressModeU, Tex->AddressModeV, DX_TEXADDRESS_CLAMP, 3 ) ;
				Graphics_Android_DeviceState_SetSampleFilterMode( DrawModeToFilterTable[ SetTexture[ 3 ]->MipMapCount <= 1 ? 0 : 1 ][ Tex->FilterMode ], 3 ) ;
			}
			else
			if( Mesh->Material->BaseData->Type == DX_MATERIAL_TYPE_TOON )
			{
				SetTexture[ 3 ] = MV1_ANDR_GetGraphHandleTexture( MV1GetDefaultToonTexture( Mesh->Material->DiffuseGradTexture ) ) ;
				Graphics_Android_DeviceState_SetSampleFilterMode( GL_LINEAR, 3 ) ;
			}
			else
			{
				SetTexture[ 3 ] = MV1_ANDR_GetNoneGraphHandleTexture() ;
				Graphics_Android_DeviceState_SetSampleFilterMode( GL_NEAREST, 3 ) ;
			}

			if( Mesh->Material->SpecularGradTexture >= 0 )
			{
				Tex = &Model->Texture[ Mesh->Material->SpecularGradTexture ] ;
				SetTexture[ 4 ] = MV1_ANDR_GetTextureTexture( Tex ) ;
				Graphics_Android_DeviceState_SetTextureAddressUVW( Tex->AddressModeU, Tex->AddressModeV, DX_TEXADDRESS_CLAMP, 4 ) ;
				Graphics_Android_DeviceState_SetSampleFilterMode( DrawModeToFilterTable[ SetTexture[ 4 ]->MipMapCount <= 1 ? 0 : 1 ][ Tex->FilterMode ], 4 ) ;
			}
			else
			{
				SetTexture[ 4 ] = MV1_ANDR_GetGraphHandleTexture( MV1GetDefaultToonTexture( Mesh->Material->SpecularGradTexture ) ) ;
				Graphics_Android_DeviceState_SetSampleFilterMode( GL_LINEAR, 4 ) ;
			}

			if( Mesh->Material->SphereMapTexture >= 0 )
			{
				SetTextureNum = 6 ;

				Tex = &Model->Texture[ Mesh->Material->SphereMapTexture ] ;
				TexBase = Tex->BaseData ;
				if( Tex->UseUserGraphHandle )
				{
					SetTexture[ 5 ] = MV1_ANDR_GetGraphHandleTexture( Tex->UserGraphHandle ) ;
				}
				else
				if( Tex->UseGraphHandle && Tex->IsDefaultTexture == FALSE )
				{
					SetTexture[ 5 ] = MV1_ANDR_GetGraphHandleTexture( Tex->GraphHandle ) ;
				}
				else
				if( TexBase->UseUserGraphHandle )
				{
					SetTexture[ 5 ] = MV1_ANDR_GetGraphHandleTexture( TexBase->UserGraphHandle ) ;
				}
				else
				if( TexBase->IsDefaultTexture == FALSE )
				{
					SetTexture[ 5 ] = MV1_ANDR_GetGraphHandleTexture( TexBase->GraphHandle ) ;
				}
				else
				{
					if( MV1Man.TexNoneHandle < 0 )
					{
						MV1SetupTexNoneHandle() ;
					}

					if( Mesh->Material->SphereMapBlendType == DX_MATERIAL_BLENDTYPE_MODULATE )
					{
						SetTexture[ 5 ] = MV1_ANDR_GetGraphHandleTexture( MV1Man.TexNoneHandle ) ;
					}
					else
					{
						SetTexture[ 5 ] = MV1_ANDR_GetGraphHandleTexture( MV1Man.TexNoneBlackHandle ) ;
					}
				}
				Graphics_Android_DeviceState_SetTextureAddressUVW( Tex->AddressModeU, Tex->AddressModeV, DX_TEXADDRESS_CLAMP, 5 ) ;
				Graphics_Android_DeviceState_SetSampleFilterMode( DrawModeToFilterTable[ SetTexture[ 5 ]->MipMapCount <= 1 ? 0 : 1 ][ Tex->FilterMode ], 5 ) ;
			}


//			SetTextureNum = 7 ;
//			SetTexture[ 6 ] = &GANDR.RGBtoVMaxRGBVolumeTexture ;
//			Graphics_Android_DeviceState_SetTextureAddressUVW( DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP, 6 ) ;
//			Graphics_Android_DeviceState_SetSampleFilterMode( Gnm::kFilterModeBilinear, 6 ) ;
		}

		if( Mesh->Material->DiffuseLayerNum > 1 )
		{
			SetTextureNum = 8 ;

			Tex = &Model->Texture[ Mesh->Material->DiffuseLayer[ 1 ].Texture ] ;
			SetTexture[ 7 ] = MV1_ANDR_GetTextureTexture( Tex ) ;
			Graphics_Android_DeviceState_SetTextureAddressUVW( Tex->AddressModeU, Tex->AddressModeV, DX_TEXADDRESS_CLAMP, 7 ) ;
			Graphics_Android_DeviceState_SetSampleFilterMode( DrawModeToFilterTable[ SetTexture[ 7 ]->MipMapCount <= 1 ? 0 : 1 ][ Tex->FilterMode ], 7 ) ;
		}

		// �V���h�E�}�b�v�̐ݒ�
		{
			int i ;

			for( i = 0 ; i < MAX_USE_SHADOWMAP_NUM ; i ++ )
			{
				if( GSYS.DrawSetting.ShadowMap[ i ] > 0 )
				{
					SetTexture[ 8 + i ] = MV1_ANDR_GetShadowMapHandleTexture( GSYS.DrawSetting.ShadowMap[ i ])  ;
					Graphics_Android_DeviceState_SetTextureAddressUVW( DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP, 8 + i ) ;
					Graphics_Android_DeviceState_SetSampleFilterMode( GL_LINEAR, 8 + i ) ;
				}
				else
				{
					SetTexture[ 8 + i ] = NULL ;
				}
			}
			SetTextureNum = 9 + MAX_USE_SHADOWMAP_NUM - 1 ;
		}

		// ���[�U�[�ݒ���g�p����ꍇ�͂����Ńe�N�X�`�����Z�b�g
		if( MV1Man.UseOrigShaderFlag )
		{
			int i ;
			int LastNo ;

			LastNo = -1 ;
			for( i = 0 ; i < USE_TEXTURESTAGE_NUM ; i ++ )
			{
				IMAGEDATA     *TempImage ;
				SHADOWMAPDATA *TempShadowMap ;

				if( !GRAPHCHKFULL( GSYS.DrawSetting.UserShaderRenderInfo.SetTextureGraphHandle[ i ], TempImage ) )
				{
					SetTexture[ i ] = &TempImage->Hard.Draw[ 0 ].Tex->PF->Texture ;
				}
				else
				if( !SHADOWMAPCHKFULL( GSYS.DrawSetting.UserShaderRenderInfo.SetTextureGraphHandle[ i ], TempShadowMap ) )
				{
					SetTexture[ i ] = &TempShadowMap->PF->Texture ;
				}
				else
				{
					continue ;
				}

				LastNo = i ;
				Graphics_Android_DeviceState_SetTextureAddressUVW( GSYS.DrawSetting.TexAddressModeU[ i ], GSYS.DrawSetting.TexAddressModeV[ i ], GSYS.DrawSetting.TexAddressModeW[ i ], i ) ;
				Graphics_Android_DeviceState_SetSampleFilterMode( DrawModeToFilterTable[ SetTexture[ i ]->MipMapCount <= 1 ? 0 : 1 ][ GSYS.DrawSetting.DrawMode ], i ) ;
			}

			if( LastNo > 0 && LastNo + 1 > SetTextureNum )
			{
				SetTextureNum = LastNo + 1 ;
			}
		}

		// �e�N�X�`�����Z�b�g
		{
			int i ;

			for( i = 0 ; i < SetTextureNum ; i ++ )
			{
				Graphics_Android_DeviceState_SetTexture( i, SetTexture[ i ] ) ;
			}
		}
	}
}

// �w��̃��b�V���̃g�D�[�������_�����O�̗֊s���p�̃}�e���A�����Z�b�g�A�b�v����
static void MV1_ANDR_SetupToonOutLineMeshDrawMaterial(	MV1_MESH *Mesh )
{
//	MV1_FRAME					*Frame ;
//	MV1_MODEL					*Model ;
//	MV1_MATERIAL				* RST MMaterial ;
//	int							BlendMode ;
	GRAPHICS_ANDROID_TEXTURE	*SetTexture = NULL ;

	// ���ʕ����̃Z�b�g

//	Frame     = Mesh->Container ;
//	Model     = Frame->Container ;
//	MMaterial = Mesh->Material ;
//	BlendMode = Mesh->DrawBlendMode != -1 ? Mesh->DrawBlendMode : MMaterial->DrawBlendMode ;

	// �f�t�H���g�e�N�X�`���n���h���̏������`�F�b�N
	if( MV1Man.TexNoneHandle < 0 )
	{
		MV1SetupTexNoneHandle() ;
	}

	// �e�N�X�`���̃Z�b�g�A�b�v
	SetTexture = MV1_ANDR_GetNoneGraphHandleTexture() ;

	// �e�N�X�`�����Z�b�g
	Graphics_Android_DeviceState_SetTexture( 0, SetTexture ) ;
}

// �w��̃��f���`��p�V�F�[�_�[���Z�b�g�A�b�v����( TRUE:����  FALSE:���s )
static int  MV1_ANDR_ShaderSetup( MV1_MESH *Mesh, int VertexType, int IsToonOutLine )
{
	GRAPHICS_HARDWARE_ANDROID_SHADER_MODEL		*SM           = &GANDR.Device.Shader.Model ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_MODEL	*SCM          = &GANDR.ShaderCode.Model ;
	int											ValidPL ;
	GRAPHICS_ANDROID_SHADER						**Shader_PL   = NULL ;
	GLuint										*VS_PL        = NULL ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*VSAddress_PL = NULL ;
	GLuint										*FS_PL        = NULL ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*FSAddress_PL = NULL ;
	GRAPHICS_ANDROID_SHADER						**Shader      = NULL ;
	GLuint										*VS           = NULL ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*VSAddress    = NULL ;
	GLuint										*FS           = NULL ;
	GRAPHICS_HARDWARE_ANDROID_SHADERCODE_INFO	*FSAddress    = NULL ;
	MV1_MATERIAL_BASE                       * RST MBMaterial ;
	MV1_MATERIAL                            * RST MMaterial ;
	int										ShadowMap ;
	int										FogType ;
//	int										LightIndex84 ;
	int										LightIndex20 ;
	int										LightIndex10 ;
	int										AlphaTestMode ;
	int										BumpMap ;
	int                                     MultiTexMode ;
	int                                     IsToon ;
//	int                                     SpecularMap ;
	int                                     UseOrigShader ;
	int										EnableLightNum = 0 ;

	MMaterial  = Mesh->Material ;
	MBMaterial = MMaterial->BaseData ;

	if( GANDR.ShaderCode.Model.ModelShaderInitializeFlag == FALSE &&
		Graphics_Android_ShaderCode_Model_Initialize()   == FALSE )
	{
		return FALSE ;
	}

	MV1Man_Android.EnableLightNum = 0 ;

	// �X�{�[���ȏ�̏ꍇ�͍��̃��b�V���Ƃ��ď���
	if( VertexType == MV1_VERTEX_TYPE_SKIN_FREEBONE )
	{
		VertexType = MV1_VERTEX_TYPE_NORMAL ;
	}

	if( MMaterial->UseAlphaTest )
	{
		AlphaTestMode = Graphics_Android_Shader_GetAlphaTestModeIndex( MMaterial->UseAlphaTest, MMaterial->AlphaFunc ) ;
		Graphics_Android_DeviceState_SetAlphaTestRef( MMaterial->AlphaRef ) ;
	}
	else
	{
		AlphaTestMode = ANDROID_FS_ALPHATEST_CMP_GREATER ;
		Graphics_Android_DeviceState_SetAlphaTestRef( -1 ) ;
	}
	ShadowMap     = GSYS.DrawSetting.UseShadowMapNum != 0 ? 1 : 0 ;
	FogType       = GANDR.Device.State.FogEnable ? GANDR.Device.State.FogMode : DX_FOGMODE_NONE ;
	IsToon        = MMaterial->BaseData->Type == DX_MATERIAL_TYPE_TOON || MMaterial->BaseData->Type == DX_MATERIAL_TYPE_TOON_2 ;
	BumpMap       = MBMaterial->NormalLayerNum  > 0 ;
	MultiTexMode  = MMaterial->DiffuseLayerNum  > 1 ? MMaterial->DiffuseLayer[ 1 ].BlendType + 1 : 0 ;
//	SpecularMap   = MMaterial->SpecularLayerNum > 0 ;

	if( IsToonOutLine )
	{
		// �g�D�[�������_�����O�̗֊s���`��

		if( GSYS.DrawSetting.ShadowMapDraw )
		{
			VS           =  &SM->MV1_ToonOutLine_ShadowMap_VS     [ VertexType ][ BumpMap ] ;
			VSAddress    = &SCM->MV1_ToonOutLine_ShadowMap_VS_Code[ VertexType ][ BumpMap ] ;

			FS           =  &SM->MV1_ShadowMap_Normal_FS     [ AlphaTestMode ] ;
			FSAddress    = &SCM->MV1_ShadowMap_Normal_FS_Code[ AlphaTestMode ] ;

			Shader       =  &SM->MV1_ToonOutLine_ShadowMap_Shader[ VertexType ][ BumpMap ][ AlphaTestMode ] ;
		}
		else
		{
			VS           =  &SM->MV1_ToonOutLine_VS     [ VertexType ][ BumpMap ][ FogType ] ;
			VSAddress    = &SCM->MV1_ToonOutLine_VS_Code[ VertexType ][ BumpMap ][ FogType ] ;

			FS           =  &SM->MV1_NoLighting_Normal_FS     [ 0 ][ AlphaTestMode ] ;
			FSAddress    = &SCM->MV1_NoLighting_Normal_FS_Code[ 0 ][ AlphaTestMode ] ;

			Shader       = &SM->MV1_NoLighting_Normal_Shader[ VertexType ][ BumpMap ][ FogType ][ 0 ][ AlphaTestMode ] ;
		}
	}
	else
	if( GSYS.DrawSetting.ShadowMapDraw )
	{
		// �V���h�E�}�b�v�ւ̕`��

		VS           =  &SM->MV1_ShadowMap_VS     [ VertexType ][ BumpMap ] ;
		VSAddress    = &SCM->MV1_ShadowMap_VS_Code[ VertexType ][ BumpMap ] ;

		if( IsToon )
		{
			switch( MMaterial->BaseData->Type )
			{
			case DX_MATERIAL_TYPE_TOON :
				{
					int DiffuseGradBlendType ;

					DiffuseGradBlendType  = MMaterial->DiffuseGradBlendType  == MV1_LAYERBLEND_TYPE_MODULATE ? 1 : 0 ;

					FS           =  &SM->MV1_ShadowMap_Toon_FS     [ 0 ][ 0 ][ DiffuseGradBlendType ][ AlphaTestMode ] ;
					FSAddress    = &SCM->MV1_ShadowMap_Toon_FS_Code[ 0 ][ 0 ][ DiffuseGradBlendType ][ AlphaTestMode ] ;

					Shader       =  &SM->MV1_ShadowMap_Toon_Shader[ VertexType ][ BumpMap ][ 0 ][ 0 ][ DiffuseGradBlendType ][ AlphaTestMode ] ;
				}
				break ;

			case DX_MATERIAL_TYPE_TOON_2 :
				{
					int SphereMapBlendType = 0 ;

					if( MMaterial->SphereMapTexture >= 0 )
					{
						switch( MMaterial->SphereMapBlendType )
						{
						case MV1_LAYERBLEND_TYPE_MODULATE :
							SphereMapBlendType = 1 ;
							break ;

						case MV1_LAYERBLEND_TYPE_ADDITIVE :
							SphereMapBlendType = 2 ;
							break ;
						}
					}

					FS           =  &SM->MV1_ShadowMap_Toon_FS     [ 1 ][ SphereMapBlendType ][ 0 ][ AlphaTestMode ] ;
					FSAddress    = &SCM->MV1_ShadowMap_Toon_FS_Code[ 1 ][ SphereMapBlendType ][ 0 ][ AlphaTestMode ] ;

					Shader       =  &SM->MV1_ShadowMap_Toon_Shader[ VertexType ][ BumpMap ][ 1 ][ SphereMapBlendType ][ 0 ][ AlphaTestMode ] ;
				}
				break ;
			}
		}
		else
		{
			FS           =  &SM->MV1_ShadowMap_Normal_FS     [ AlphaTestMode ] ;
			FSAddress    = &SCM->MV1_ShadowMap_Normal_FS_Code[ AlphaTestMode ] ;

			Shader       =  &SM->MV1_ShadowMap_Normal_Shader[ VertexType ][ BumpMap ][ AlphaTestMode ] ;
		}
	}
	else
	if( MMaterial->BaseData->Type >= DX_MATERIAL_TYPE_MAT_SPEC_LUMINANCE_UNORM &&
		MMaterial->BaseData->Type <= DX_MATERIAL_TYPE_MAT_SPEC_POWER_CMP_GREATEREQUAL )
	{
		// ����}�e���A���^�C�v

		VS        =  &SM->MV1_NoLighting_VS     [ VertexType ][ BumpMap ][ 0 ] ;
		VSAddress = &SCM->MV1_NoLighting_VS_Code[ VertexType ][ BumpMap ][ 0 ] ;

		FS        =  &SM->MV1_MaterialType_FS     [ MMaterial->BaseData->Type ][ AlphaTestMode ] ;
		FSAddress = &SCM->MV1_MaterialType_FS_Code[ MMaterial->BaseData->Type ][ AlphaTestMode ] ;

		Shader    =  &SM->MV1_MaterialType_Shader[ VertexType ][ BumpMap ][ MMaterial->BaseData->Type ][ AlphaTestMode ] ;
	}
	else
	if( GANDR.Device.State.Lighting )
	{
		// ���C�e�B���O����`��

		int LightMode[ DX_PIXELLIGHTING_LIGHT_NUM ] ;
		int i ;

		for( i = 0 ; i < DX_PIXELLIGHTING_LIGHT_NUM ; i ++ )
		{
			if( GANDR.Device.State.LightEnableFlag[ i ] )
			{
				LightMode[ i ] = GANDR.Device.State.LightParam[ i ].LightType ;
				EnableLightNum ++ ;
			}
			else
			{
				LightMode[ i ] = 0 ;
			}
		}

//		LightIndex84 = GANDR.ShaderCode.Base.LightIndexList84[ LightMode[ 0 ] ][ LightMode[ 1 ] ][ LightMode[ 2 ] ][ LightMode[ 3 ] ][ LightMode[ 4 ] ][ LightMode[ 5 ] ] ;
		LightIndex20 = GANDR.ShaderCode.Base.LightIndexList20[ LightMode[ 0 ] ][ LightMode[ 1 ] ][ LightMode[ 2 ] ] ;
		LightIndex10 = GANDR.ShaderCode.Base.LightIndexList10
				[ LightMode[ 0 ] == DX_LIGHTTYPE_D3DLIGHT_DIRECTIONAL ? 2 : ( LightMode[ 0 ] ? 1 : 0 ) ]
				[ LightMode[ 1 ] == DX_LIGHTTYPE_D3DLIGHT_DIRECTIONAL ? 2 : ( LightMode[ 1 ] ? 1 : 0 ) ]
				[ LightMode[ 2 ] == DX_LIGHTTYPE_D3DLIGHT_DIRECTIONAL ? 2 : ( LightMode[ 2 ] ? 1 : 0 ) ] ;

		VS_PL        =  &SM->MV1_PixelLighting_VS     [ ShadowMap ][ VertexType ][ BumpMap ][ FogType ] ;
		VSAddress_PL = &SCM->MV1_PixelLighting_VS_Code[ ShadowMap ][ VertexType ][ BumpMap ][ FogType ] ;

		VS           =  &SM->MV1_VertexLighting_VS     [ ShadowMap ][ VertexType ][ BumpMap ][ FogType ][ LightIndex20 ] ;
		VSAddress    = &SCM->MV1_VertexLighting_VS_Code[ ShadowMap ][ VertexType ][ BumpMap ][ FogType ][ LightIndex20 ] ;

		if( IsToon )
		{
			switch( MMaterial->BaseData->Type )
			{
			case DX_MATERIAL_TYPE_TOON :
				{
					int DiffuseGradBlendType ;
					int SpecularGradBlendType ;

					DiffuseGradBlendType  = MMaterial->DiffuseGradBlendType == MV1_LAYERBLEND_TYPE_MODULATE  ? 1 : 0 ;
					SpecularGradBlendType = MMaterial->SpecularGradBlendType == MV1_LAYERBLEND_TYPE_ADDITIVE ? 1 : 0 ;

					if( EnableLightNum != 0 )
					{
						FS_PL        =  &SM->MV1_PixelLighting_ToonType1_FS      [ ShadowMap ][ DiffuseGradBlendType ][ SpecularGradBlendType ][ BumpMap ][ EnableLightNum - 1 ][ AlphaTestMode ] ;
						FSAddress_PL = &SCM->MV1_PixelLighting_ToonType1_FS_Code [ ShadowMap ][ DiffuseGradBlendType ][ SpecularGradBlendType ][ BumpMap ][ EnableLightNum - 1 ][ AlphaTestMode ] ;

						Shader_PL    =  &SM->MV1_PixelLighting_ToonType1_Shader  [ ShadowMap ][ BumpMap ][ VertexType ][ FogType ][ DiffuseGradBlendType ][ SpecularGradBlendType ][ EnableLightNum - 1 ][ AlphaTestMode ] ;
					}

					FS           =  &SM->MV1_VertexLighting_ToonType1_FS     [ ShadowMap ][ DiffuseGradBlendType ][ SpecularGradBlendType ][ BumpMap ][ LightIndex10 ][ AlphaTestMode ] ;
					FSAddress    = &SCM->MV1_VertexLighting_ToonType1_FS_Code[ ShadowMap ][ DiffuseGradBlendType ][ SpecularGradBlendType ][ BumpMap ][ LightIndex10 ][ AlphaTestMode ] ;

					Shader       =  &SM->MV1_VertexLighting_ToonType1_Shader [ ShadowMap ][ BumpMap ][ VertexType ][ FogType ][ LightIndex20 ][ DiffuseGradBlendType ][ SpecularGradBlendType ][ LightIndex10 ][ AlphaTestMode ] ;
				}
				break ;

			case DX_MATERIAL_TYPE_TOON_2 :
				{
					int SphereMapBlendType = 0 ;

					if( MMaterial->SphereMapTexture >= 0 )
					{
						switch( MMaterial->SphereMapBlendType )
						{
						case MV1_LAYERBLEND_TYPE_MODULATE :
							SphereMapBlendType = 1 ;
							break ;

						case MV1_LAYERBLEND_TYPE_ADDITIVE :
							SphereMapBlendType = 2 ;
							break ;
						}
					}

					if( EnableLightNum != 0 )
					{
						FS_PL        =  &SM->MV1_PixelLighting_ToonType2_FS      [ ShadowMap ][ SphereMapBlendType ][ EnableLightNum - 1 ][ AlphaTestMode ] ;
						FSAddress_PL = &SCM->MV1_PixelLighting_ToonType2_FS_Code [ ShadowMap ][ SphereMapBlendType ][ EnableLightNum - 1 ][ AlphaTestMode ] ;

						Shader_PL    =  &SM->MV1_PixelLighting_ToonType2_Shader  [ ShadowMap ][ VertexType ][ BumpMap ][ FogType ][ SphereMapBlendType ][ EnableLightNum - 1 ][ AlphaTestMode ] ;
					}

					FS           =  &SM->MV1_VertexLighting_ToonType2_FS     [ ShadowMap ][ SphereMapBlendType ][ LightIndex10 ][ AlphaTestMode ] ;
					FSAddress    = &SCM->MV1_VertexLighting_ToonType2_FS_Code[ ShadowMap ][ SphereMapBlendType ][ LightIndex10 ][ AlphaTestMode ] ;

					Shader       =  &SM->MV1_VertexLighting_ToonType2_Shader [ ShadowMap ][ VertexType ][ BumpMap ][ FogType ][ LightIndex20 ][ SphereMapBlendType ][ LightIndex10 ][ AlphaTestMode ] ;
				}
				break ;
			}
		}
		else
		{
			if( EnableLightNum != 0 )
			{
				FS_PL        =  &SM->MV1_PixelLighting_Normal_FS     [ ShadowMap ][ MultiTexMode ][ BumpMap ][ EnableLightNum - 1 ][ AlphaTestMode ] ;
				FSAddress_PL = &SCM->MV1_PixelLighting_Normal_FS_Code[ ShadowMap ][ MultiTexMode ][ BumpMap ][ EnableLightNum - 1 ][ AlphaTestMode ] ;

				Shader_PL    =  &SM->MV1_PixelLighting_Normal_Shader [ ShadowMap ][ BumpMap ][ VertexType ][ FogType ][ MultiTexMode ][ EnableLightNum - 1 ][ AlphaTestMode ] ;
			}

			FS           =  &SM->MV1_VertexLighting_Normal_FS     [ ShadowMap ][ MultiTexMode ][ BumpMap ][ LightIndex10 ][ AlphaTestMode ] ;
			FSAddress    = &SCM->MV1_VertexLighting_Normal_FS_Code[ ShadowMap ][ MultiTexMode ][ BumpMap ][ LightIndex10 ][ AlphaTestMode ] ;

			Shader       =  &SM->MV1_VertexLighting_Normal_Shader [ ShadowMap ][ BumpMap ][ VertexType ][ FogType ][ LightIndex20 ][ MultiTexMode ][ LightIndex10 ][ AlphaTestMode ] ;
		}
	}
	else
	{
		// ���C�e�B���O�Ȃ��`��

		VS           =  &SM->MV1_NoLighting_VS     [ VertexType ][ BumpMap ][ FogType ] ;
		VSAddress    = &SCM->MV1_NoLighting_VS_Code[ VertexType ][ BumpMap ][ FogType ] ;

		if( IsToon )
		{
			switch( MMaterial->BaseData->Type )
			{
			case DX_MATERIAL_TYPE_TOON :
				{
					int DiffuseGradBlendType ;

					DiffuseGradBlendType  = MMaterial->DiffuseGradBlendType == MV1_LAYERBLEND_TYPE_MODULATE ? 1 : 0 ;

					FS           =  &SM->MV1_NoLighting_Toon_FS     [ 0 ][ DiffuseGradBlendType ][ AlphaTestMode ] ;
					FSAddress    = &SCM->MV1_NoLighting_Toon_FS_Code[ 0 ][ DiffuseGradBlendType ][ AlphaTestMode ] ;

					Shader       =  &SM->MV1_NoLighting_Toon_Shader [ VertexType ][ BumpMap ][ FogType ][ 0 ][ DiffuseGradBlendType ][ AlphaTestMode ] ;
				}
				break ;

			case DX_MATERIAL_TYPE_TOON_2 :
				FS           =  &SM->MV1_NoLighting_Toon_FS     [ 1 ][ 0 ][ AlphaTestMode ] ;
				FSAddress    = &SCM->MV1_NoLighting_Toon_FS_Code[ 1 ][ 0 ][ AlphaTestMode ] ;

				Shader       =  &SM->MV1_NoLighting_Toon_Shader [ VertexType ][ BumpMap ][ FogType ][ 1 ][ 0 ][ AlphaTestMode ] ;
				break ;
			}
		}
		else
		{
			FS        =  &SM->MV1_NoLighting_Normal_FS     [ MultiTexMode ][ AlphaTestMode ] ;
			FSAddress = &SCM->MV1_NoLighting_Normal_FS_Code[ MultiTexMode ][ AlphaTestMode ] ;

			Shader    =  &SM->MV1_NoLighting_Normal_Shader [ VertexType ][ BumpMap ][ FogType ][ MultiTexMode ][ AlphaTestMode ] ;
		}
	}

	ValidPL = 
		VSAddress_PL != NULL && VSAddress_PL->Binary != NULL &&
		FSAddress_PL != NULL && FSAddress_PL->Binary != NULL ;

	// �I���W�i���V�F�[�_�[���g�p����ꍇ�̓I���W�i���V�F�[�_�[���Z�b�g�A�b�v
	UseOrigShader = FALSE ;
//	if( MV1Man.UseOrigShaderFlag )
//	{
//		UseOrigShader = TRUE ;
//
//		// ���_�V�F�[�_�[�̃Z�b�g�A�b�v
//		if( GSYS.DrawSetting.UserShaderRenderInfo.SetVertexShaderHandle > 0 )
//		{
//			if( Graphics_Android_DeviceState_SetVertexShaderToHandle( GSYS.DrawSetting.UserShaderRenderInfo.SetVertexShaderHandle ) < 0 )
//			{
//				UseOrigShader = FALSE ;
//			}
//		}
//
//		// �t���O�����g�V�F�[�_�[�̃Z�b�g�A�b�v
//		if( GSYS.DrawSetting.UserShaderRenderInfo.SetPixelShaderHandle > 0 )
//		{
//			if( Graphics_Android_DeviceState_SetPixelShaderToHandle( GSYS.DrawSetting.UserShaderRenderInfo.SetPixelShaderHandle ) < 0 )
//			{
//				UseOrigShader = FALSE ;
//			}
//		}
//	}

	// �I���W�i���V�F�[�_�[���g�p���Ȃ����A�I���W�i���V�F�[�_�[�̃Z�b�g�A�b�v�Ɏ��s������f�t�H���g�V�F�[�_�[���Z�b�g�A�b�v����
	if( UseOrigShader == FALSE )
	{
		if( ( GSYS.Light.EnableNum > DX_VERTEXLIGHTING_LIGHT_NUM || GANDR.UsePixelLightingShader ) && ValidPL )
		{
			// ���_�V�F�[�_�[�����邩�ǂ����𒲂ׂ�
			if( *VS_PL == 0 )
			{
				// ���_�V�F�[�_�[�̍쐬�����݂�
				if( Graphics_Android_VertexShader_Create( VSAddress_PL, VS_PL, 1 ) != 0 )
				{
					DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x56\x00\x31\x00\x5f\x00\x41\x00\x4e\x00\x44\x00\x52\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"MV1_ANDR_ShaderSetup �Ńs�N�Z�����C�e�B���O�p���_�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
					return FALSE ;
				}
			}

			// �t���O�����g�V�F�[�_�[�����邩�ǂ����𒲂ׂ�
			if( *FS_PL == 0 )
			{
				// �t���O�����g�V�F�[�_�[�̍쐬�����݂�
				if( Graphics_Android_FragmentShader_Create( FSAddress_PL, FS_PL, 1 ) != 0 )
				{
					DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x56\x00\x31\x00\x5f\x00\x41\x00\x4e\x00\x44\x00\x52\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\xd5\x30\xe9\x30\xb0\x30\xe1\x30\xf3\x30\xc8\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"MV1_ANDR_ShaderSetup �Ńs�N�Z�����C�e�B���O�p�t���O�����g�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
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
					DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x56\x00\x31\x00\x5f\x00\x41\x00\x4e\x00\x44\x00\x52\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\xd4\x30\xaf\x30\xbb\x30\xeb\x30\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"MV1_ANDR_ShaderSetup �Ńs�N�Z�����C�e�B���O�p�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
					return FALSE ;
				}
			}

			MV1Man_Android.EnableLightNum = EnableLightNum ;

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
					DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x56\x00\x31\x00\x5f\x00\x41\x00\x4e\x00\x44\x00\x52\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\x02\x98\xb9\x70\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\x02\x98\xb9\x70\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"MV1_ANDR_ShaderSetup �Œ��_���C�e�B���O�p���_�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
					return FALSE ;
				}
			}

			// �V�F�[�_�[�����邩�ǂ����𒲂ׂ�
			if( *FS == 0 )
			{
				// �V�F�[�_�[�̍쐬�����݂�
				if( Graphics_Android_FragmentShader_Create( FSAddress, FS, 1 ) != 0 )
				{
					DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x56\x00\x31\x00\x5f\x00\x41\x00\x4e\x00\x44\x00\x52\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\x02\x98\xb9\x70\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\xd5\x30\xe9\x30\xb0\x30\xe1\x30\xf3\x30\xc8\x30\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"MV1_ANDR_ShaderSetup �Œ��_���C�e�B���O�p�t���O�����g�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
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
					DXST_LOGFILEFMT_ADDUTF16LE(( "\x4d\x00\x56\x00\x31\x00\x5f\x00\x41\x00\x4e\x00\x44\x00\x52\x00\x5f\x00\x53\x00\x68\x00\x61\x00\x64\x00\x65\x00\x72\x00\x53\x00\x65\x00\x74\x00\x75\x00\x70\x00\x20\x00\x67\x30\x02\x98\xb9\x70\xe9\x30\xa4\x30\xc6\x30\xa3\x30\xf3\x30\xb0\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"MV1_ANDR_ShaderSetup �Œ��_���C�e�B���O�p�V�F�[�_�[�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
					return FALSE ;
				}
			}

			MV1Man_Android.EnableLightNum = EnableLightNum > 3 ? 3 : EnableLightNum ;

			// �V�F�[�_�[�̃Z�b�g�A�b�v
			Graphics_Android_DeviceState_SetShader( *Shader, FALSE ) ;
		}
	}

	// �I��
	return TRUE ;
}

// ���[�J���@���@���[���h�s��� MATRIX_4X4CT ��ݒ肷��
static void MV1_ANDR_SetWorldMatrix_MATRIX_4X4CT( const MATRIX_4X4CT *Matrix, int UseWorldViewMatrix )
{
	// �萔�f�[�^�ɔ��f
	if( GSYS.DrawSetting.Large3DPositionSupport )
	{
		if( UseWorldViewMatrix )
		{
			GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 0 ] = ( float )Matrix->md.m[ 0 ][ 0 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 1 ] = ( float )Matrix->md.m[ 0 ][ 1 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 2 ] = ( float )Matrix->md.m[ 0 ][ 2 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 3 ] = ( float )Matrix->md.m[ 0 ][ 3 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 0 ] = ( float )Matrix->md.m[ 1 ][ 0 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 1 ] = ( float )Matrix->md.m[ 1 ][ 1 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 2 ] = ( float )Matrix->md.m[ 1 ][ 2 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 3 ] = ( float )Matrix->md.m[ 1 ][ 3 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 0 ] = ( float )Matrix->md.m[ 2 ][ 0 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 1 ] = ( float )Matrix->md.m[ 2 ][ 1 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 2 ] = ( float )Matrix->md.m[ 2 ][ 2 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 3 ] = ( float )Matrix->md.m[ 2 ][ 3 ] ;
		}
		else
		{
			MATRIX_4X4CT ViewMat ;
			MATRIX_4X4CT TempMat ;

			ConvertMatrixDToMatrix4x4cD( &ViewMat.md, &GSYS.DrawSetting.ViewMatrix ) ;
			UnSafeMultiplyMatrix4X4CTD( &TempMat.md, &Matrix->md, &ViewMat.md ) ;

			GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 0 ] = ( float )TempMat.md.m[ 0 ][ 0 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 1 ] = ( float )TempMat.md.m[ 0 ][ 1 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 2 ] = ( float )TempMat.md.m[ 0 ][ 2 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 3 ] = ( float )TempMat.md.m[ 0 ][ 3 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 0 ] = ( float )TempMat.md.m[ 1 ][ 0 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 1 ] = ( float )TempMat.md.m[ 1 ][ 1 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 2 ] = ( float )TempMat.md.m[ 1 ][ 2 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 3 ] = ( float )TempMat.md.m[ 1 ][ 3 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 0 ] = ( float )TempMat.md.m[ 2 ][ 0 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 1 ] = ( float )TempMat.md.m[ 2 ][ 1 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 2 ] = ( float )TempMat.md.m[ 2 ][ 2 ] ;
			GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 3 ] = ( float )TempMat.md.m[ 2 ][ 3 ] ;

			Graphics_Android_DeviceState_SetViewMatrix( &IdentityMat ) ;
		}
	}
	else
	{
		GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 0 ] = Matrix->mf.m[ 0 ][ 0 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 1 ] = Matrix->mf.m[ 0 ][ 1 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 2 ] = Matrix->mf.m[ 0 ][ 2 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 0 ][ 3 ] = Matrix->mf.m[ 0 ][ 3 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 0 ] = Matrix->mf.m[ 1 ][ 0 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 1 ] = Matrix->mf.m[ 1 ][ 1 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 2 ] = Matrix->mf.m[ 1 ][ 2 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 1 ][ 3 ] = Matrix->mf.m[ 1 ][ 3 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 0 ] = Matrix->mf.m[ 2 ][ 0 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 1 ] = Matrix->mf.m[ 2 ][ 1 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 2 ] = Matrix->mf.m[ 2 ][ 2 ] ;
		GANDR.Device.Shader.Constant.uLWMat[ 2 ][ 3 ] = Matrix->mf.m[ 2 ][ 3 ] ;
	}

	GANDR.Device.Shader.Constant.UpdateCount ++ ;
}

// ���f���`���p�� ���[�J���@���@���[���h�s����Z�b�g�A�b�v����
static void MV1_ANDR_SetupModelDrawWorldMatrix( MV1_FRAME *Frame, MV1_TRIANGLE_LIST_BASE *MBTList, int UseWorldViewMatrix )
{
	MATRIX_4X4CT * RST SrcMatrix ;
	DX_ANDR_SHADER_FLOAT4 *Dest ;
	int i ;

	// �萔�f�[�^�ɔ��f
	Dest = GANDR.Device.Shader.Constant.uLWMat ;
	if( GSYS.DrawSetting.Large3DPositionSupport )
	{
		if( UseWorldViewMatrix )
		{
			for( i = 0 ; i < MBTList->UseBoneNum ; i ++ )
			{
				SrcMatrix = Frame->UseSkinBoneMatrix[ MBTList->UseBone[ i ] ] ;

				Dest[ 0 ][ 0 ] = ( float )SrcMatrix->md.m[ 0 ][ 0 ] ;
				Dest[ 0 ][ 1 ] = ( float )SrcMatrix->md.m[ 0 ][ 1 ] ;
				Dest[ 0 ][ 2 ] = ( float )SrcMatrix->md.m[ 0 ][ 2 ] ;
				Dest[ 0 ][ 3 ] = ( float )SrcMatrix->md.m[ 0 ][ 3 ] ;
				Dest[ 1 ][ 0 ] = ( float )SrcMatrix->md.m[ 1 ][ 0 ] ;
				Dest[ 1 ][ 1 ] = ( float )SrcMatrix->md.m[ 1 ][ 1 ] ;
				Dest[ 1 ][ 2 ] = ( float )SrcMatrix->md.m[ 1 ][ 2 ] ;
				Dest[ 1 ][ 3 ] = ( float )SrcMatrix->md.m[ 1 ][ 3 ] ;
				Dest[ 2 ][ 0 ] = ( float )SrcMatrix->md.m[ 2 ][ 0 ] ;
				Dest[ 2 ][ 1 ] = ( float )SrcMatrix->md.m[ 2 ][ 1 ] ;
				Dest[ 2 ][ 2 ] = ( float )SrcMatrix->md.m[ 2 ][ 2 ] ;
				Dest[ 2 ][ 3 ] = ( float )SrcMatrix->md.m[ 2 ][ 3 ] ;
				Dest += 3 ;
			}
		}
		else
		{
			MATRIX_4X4CT ViewMat ;
			MATRIX_4X4CT TempMat ;

			ConvertMatrixDToMatrix4x4cD( &ViewMat.md, &GSYS.DrawSetting.ViewMatrix ) ;
			for( i = 0 ; i < MBTList->UseBoneNum ; i ++ )
			{
				UnSafeMultiplyMatrix4X4CTD( &TempMat.md, &Frame->UseSkinBoneMatrix[ MBTList->UseBone[ i ] ]->md, &ViewMat.md )  ;

				Dest[ 0 ][ 0 ] = ( float )TempMat.md.m[ 0 ][ 0 ] ;
				Dest[ 0 ][ 1 ] = ( float )TempMat.md.m[ 0 ][ 1 ] ;
				Dest[ 0 ][ 2 ] = ( float )TempMat.md.m[ 0 ][ 2 ] ;
				Dest[ 0 ][ 3 ] = ( float )TempMat.md.m[ 0 ][ 3 ] ;
				Dest[ 1 ][ 0 ] = ( float )TempMat.md.m[ 1 ][ 0 ] ;
				Dest[ 1 ][ 1 ] = ( float )TempMat.md.m[ 1 ][ 1 ] ;
				Dest[ 1 ][ 2 ] = ( float )TempMat.md.m[ 1 ][ 2 ] ;
				Dest[ 1 ][ 3 ] = ( float )TempMat.md.m[ 1 ][ 3 ] ;
				Dest[ 2 ][ 0 ] = ( float )TempMat.md.m[ 2 ][ 0 ] ;
				Dest[ 2 ][ 1 ] = ( float )TempMat.md.m[ 2 ][ 1 ] ;
				Dest[ 2 ][ 2 ] = ( float )TempMat.md.m[ 2 ][ 2 ] ;
				Dest[ 2 ][ 3 ] = ( float )TempMat.md.m[ 2 ][ 3 ] ;
				Dest += 3 ;
			}

			Graphics_Android_DeviceState_SetViewMatrix( &IdentityMat ) ;
		}
	}
	else
	{
		for( i = 0 ; i < MBTList->UseBoneNum ; i ++ )
		{
			SrcMatrix = Frame->UseSkinBoneMatrix[ MBTList->UseBone[ i ] ] ;

			Dest[ 0 ][ 0 ] = SrcMatrix->mf.m[ 0 ][ 0 ] ;
			Dest[ 0 ][ 1 ] = SrcMatrix->mf.m[ 0 ][ 1 ] ;
			Dest[ 0 ][ 2 ] = SrcMatrix->mf.m[ 0 ][ 2 ] ;
			Dest[ 0 ][ 3 ] = SrcMatrix->mf.m[ 0 ][ 3 ] ;
			Dest[ 1 ][ 0 ] = SrcMatrix->mf.m[ 1 ][ 0 ] ;
			Dest[ 1 ][ 1 ] = SrcMatrix->mf.m[ 1 ][ 1 ] ;
			Dest[ 1 ][ 2 ] = SrcMatrix->mf.m[ 1 ][ 2 ] ;
			Dest[ 1 ][ 3 ] = SrcMatrix->mf.m[ 1 ][ 3 ] ;
			Dest[ 2 ][ 0 ] = SrcMatrix->mf.m[ 2 ][ 0 ] ;
			Dest[ 2 ][ 1 ] = SrcMatrix->mf.m[ 2 ][ 1 ] ;
			Dest[ 2 ][ 2 ] = SrcMatrix->mf.m[ 2 ][ 2 ] ;
			Dest[ 2 ][ 3 ] = SrcMatrix->mf.m[ 2 ][ 3 ] ;
			Dest += 3 ;
		}
	}

	GANDR.Device.Shader.Constant.UpdateCount ++ ;
}

// �X�{�[���ȏチ�b�V���̒��_�����X�V����
static int MV1_ANDR_UpdateSkinFreeBoneMeshVertexData(
	MV1_FRAME_BASE         *MBFrame,
	MV1_TRIANGLE_LIST_BASE *MBTList,
	MV1_FRAME              *Frame,
	MV1_TRIANGLE_LIST      *TList
)
{
	MV1_TRIANGLE_LIST_BASE_PF         *MBTListPF ;
	MV1_TLIST_SKIN_POS_FREEB          *PosSKFB ;
	BYTE                              *Dest ;
	VECTOR                            *ShapePos ;
	DWORD                             SrcUnitSize ;
	DWORD                             DestUnitSize ;
	MV1_SKINBONE_BLEND                *VBlend ;
	float                             Weight ;
	DWORD                             VertexNum ;
	MATRIX_4X4CT                      *pSkinBoneMatrix[ MV1_TRIANGLE_LIST_USE_BONE_MAX_NUM ] ;
	MATRIX_4X4CT                      *Mat ;
	MATRIX_4X4CT                      BlendMat ;
	DWORD                             i ;
	DWORD                             j ;
	DWORD                             MaxBoneNum ;

	MBTListPF    = ( MV1_TRIANGLE_LIST_BASE_PF * )MBTList->PFBuffer ;
	SrcUnitSize  = MBTList->PosUnitSize ;
	DestUnitSize = MBTList->VertexBuffer->UnitSize ;
	VertexNum    = ( DWORD )MBTList->VertexNum ;
	MaxBoneNum   = ( DWORD )MBTList->MaxBoneNum;
	ShapePos     = ( VECTOR * )TList->PF->SkinFreeBoneVertexPositionBuffer ;

	// ���ɍX�V�ς݂̏ꍇ�͉��������I��
	if( MBTListPF->SkinFreeBoneVertexBufferUpdate )
	{
		return 0 ;
	}
	
	// �܂��f�[�^�]���p�̃������̈悪�m�ۂ���Ă��Ȃ��ꍇ�͊m�ۂ���
	if( MBTListPF->SkinFreeBoneVertexBuffer == NULL )
	{
		DWORD           *MVInd ;
		MV1_MESH_NORMAL *MNorm ;
		MV1_MESH_NORMAL *MeshNorm ;
		MV1_MESH_VERTEX *MVert ;
		MV1_MESH_VERTEX *MeshVert ;
		DWORD           MeshVertSize ;
		int             Bump ;
		DWORD           UVNum ;

		MBTListPF->SkinFreeBoneVertexBuffer = DXALLOC( DestUnitSize * MBTList->VertexNum ) ;
		if( MBTListPF->SkinFreeBoneVertexBuffer == NULL )
		{
			return -1 ;
		}

		// �ω����Ȃ��f�[�^�͂����ŃZ�b�g����
		Bump		 = MBTList->Container->Material->NormalLayerNum ? 1 : 0 ;
		UVNum		 = ( DWORD )( MBTList->Container->UVSetUnitNum > 2 ? 2 : MBTList->Container->UVSetUnitNum ) ;
		Dest		 = ( BYTE * )MBTListPF->SkinFreeBoneVertexBuffer ;
		PosSKFB		 = ( MV1_TLIST_SKIN_POS_FREEB * )ADDR16( MBTList->SkinPositionFREEB ) ;
		MVInd		 = MBTList->MeshVertexIndex ;
		MeshNorm     = MBTList->Container->Container->Normal ;
		MeshVertSize = ( DWORD )MBTList->Container->VertUnitSize ;
		MeshVert	 = MBTList->Container->Vertex ;
		for( i = 0 ; i < VertexNum ; i ++, PosSKFB = ( MV1_TLIST_SKIN_POS_FREEB * )( ( BYTE * )PosSKFB + SrcUnitSize ), MVInd ++ )
		{
			MVert = ( MV1_MESH_VERTEX   * )( ( BYTE * )MeshVert + MeshVertSize * *MVInd ) ;
			MNorm = MeshNorm + MVert->NormalIndex ;

			MV1_ANDR_SetVertexData(
				&Dest,
				( VECTOR * )&PosSKFB->Position,
				&MNorm->Normal,
				&MVert->DiffuseColor,
				&MVert->SpecularColor,
				UVNum >= 1 ? ( FLOAT2 * )MVert->UVs[ 0 ] : NULL,
				UVNum >= 2 ? ( FLOAT2 * )MVert->UVs[ 1 ] : NULL,
				Bump ? &MNorm->Tangent  : NULL,
				Bump ? &MNorm->Binormal : NULL
			) ;
		}
	}

	PosSKFB = ( MV1_TLIST_SKIN_POS_FREEB * )ADDR16( MBTList->SkinPositionFREEB ) ;
	Dest	= ( BYTE * )MBTListPF->SkinFreeBoneVertexBuffer ;

	// �g�p���Ă���{�[���̍ő吔�� MV1_TRIANGLE_LIST_USE_BONE_MAX_NUM �ȉ���������e�[�u�����g�p����
	if( MBFrame->UseSkinBoneNum < MV1_TRIANGLE_LIST_USE_BONE_MAX_NUM )
	{
		// �g�p����s��̏������s��
		for( i = 0 ; i < ( DWORD )MBFrame->UseSkinBoneNum ; i ++ )
		{
			pSkinBoneMatrix[ i ] = Frame->UseSkinBoneMatrix[ i ] ;
		}

		if( GSYS.DrawSetting.Large3DPositionSupport )
		{
			for( i = 0 ; i < VertexNum ; i ++, PosSKFB = ( MV1_TLIST_SKIN_POS_FREEB * )( ( BYTE * )PosSKFB + SrcUnitSize ), Dest += DestUnitSize )
			{
				// �g���Ă���{�[�����ЂƂ̏ꍇ�̓u�����h�s��̍쐬�̓X�L�b�v����
				if( PosSKFB->MatrixWeight[ 0 ].W == 1.0f )
				{
					Mat = pSkinBoneMatrix[ PosSKFB->MatrixWeight[ 0 ].Index ] ;

					if( ShapePos != NULL )
					{
						VectorTransform4X4CTD(   ( VECTOR * )&Dest[  0 ], ShapePos,                       &Mat->md ) ;
					}
					else
					{
						VectorTransform4X4CTD(   ( VECTOR * )&Dest[  0 ], ( VECTOR * )&PosSKFB->Position, &Mat->md ) ;
					}
					VectorTransformSR4X4CTD( ( VECTOR * )&Dest[ 12 ], ( VECTOR * )&PosSKFB->Normal,   &Mat->md ) ;
				}
				else
				{
					// �u�����h�s��̍쐬
					VBlend = PosSKFB->MatrixWeight ;
					Weight = VBlend->W ;

					// �O�Ԗڂ͉��Z�ł͂Ȃ��̂ŕʏ���
					Mat = pSkinBoneMatrix[ PosSKFB->MatrixWeight[ 0 ].Index ] ;
					UnSafeMatrix4X4CT_D_Eq_D_Mul_S( &BlendMat.md, &Mat->md, Weight ) ;
					VBlend ++ ;

					// �P�Ԗڂ���͉��Z
					for( j = 1 ; j < MaxBoneNum && VBlend->Index != -1 ; j ++, VBlend ++ )
					{
						Weight = VBlend->W ;

						if( Weight == 0.0f ) continue ;

						Mat = pSkinBoneMatrix[ VBlend->Index ] ;
						UnSafeMatrix4X4CT_D_EqPlus_D_Mul_S( &BlendMat.md, &Mat->md, Weight ) ;
					}

					// ���_���W�ƃu�����h�s�����Z
					if( ShapePos != NULL )
					{
						VectorTransform4X4CTD(   ( VECTOR * )&Dest[  0 ], ShapePos,                       &BlendMat.md ) ;
					}
					else
					{
						VectorTransform4X4CTD(   ( VECTOR * )&Dest[  0 ], ( VECTOR * )&PosSKFB->Position, &BlendMat.md ) ;
					}
					VectorTransformSR4X4CTD( ( VECTOR * )&Dest[ 12 ], ( VECTOR * )&PosSKFB->Normal,   &BlendMat.md ) ;
				}

				if( ShapePos != NULL )
				{
					ShapePos ++ ;
				}
			}
		}
		else
		{
			for( i = 0 ; i < VertexNum ; i ++, PosSKFB = ( MV1_TLIST_SKIN_POS_FREEB * )( ( BYTE * )PosSKFB + SrcUnitSize ), Dest += DestUnitSize )
			{
				// �g���Ă���{�[�����ЂƂ̏ꍇ�̓u�����h�s��̍쐬�̓X�L�b�v����
				if( PosSKFB->MatrixWeight[ 0 ].W == 1.0f )
				{
					Mat = pSkinBoneMatrix[ PosSKFB->MatrixWeight[ 0 ].Index ] ;

					if( ShapePos != NULL )
					{
						VectorTransform4X4CTF(   ( VECTOR * )&Dest[  0 ], ShapePos,                       &Mat->mf ) ;
					}
					else
					{
						VectorTransform4X4CTF(   ( VECTOR * )&Dest[  0 ], ( VECTOR * )&PosSKFB->Position, &Mat->mf ) ;
					}
					VectorTransformSR4X4CTF( ( VECTOR * )&Dest[ 12 ], ( VECTOR * )&PosSKFB->Normal,   &Mat->mf ) ;
				}
				else
				{
					// �u�����h�s��̍쐬
					VBlend = PosSKFB->MatrixWeight ;
					Weight = VBlend->W ;

					// �O�Ԗڂ͉��Z�ł͂Ȃ��̂ŕʏ���
					Mat = pSkinBoneMatrix[ PosSKFB->MatrixWeight[ 0 ].Index ] ;
					UnSafeMatrix4X4CT_F_Eq_F_Mul_S( &BlendMat.mf, &Mat->mf, Weight ) ;
					VBlend ++ ;

					// �P�Ԗڂ���͉��Z
					for( j = 1 ; j < MaxBoneNum && VBlend->Index != -1 ; j ++, VBlend ++ )
					{
						Weight = VBlend->W ;

						if( Weight == 0.0f ) continue ;

						Mat = pSkinBoneMatrix[ VBlend->Index ] ;
						UnSafeMatrix4X4CT_F_EqPlus_F_Mul_S( &BlendMat.mf, &Mat->mf, Weight ) ;
					}

					// ���_���W�ƃu�����h�s�����Z
					if( ShapePos != NULL )
					{
						VectorTransform4X4CTF(   ( VECTOR * )&Dest[  0 ], ShapePos,                       &BlendMat.mf ) ;
					}
					else
					{
						VectorTransform4X4CTF(   ( VECTOR * )&Dest[  0 ], ( VECTOR * )&PosSKFB->Position, &BlendMat.mf ) ;
					}
					VectorTransformSR4X4CTF( ( VECTOR * )&Dest[ 12 ], ( VECTOR * )&PosSKFB->Normal,   &BlendMat.mf ) ;
				}

				if( ShapePos != NULL )
				{
					ShapePos ++ ;
				}
			}
		}
	}
	else
	{
		if( GSYS.DrawSetting.Large3DPositionSupport )
		{
			for( i = 0 ; i < VertexNum ; i ++, PosSKFB = ( MV1_TLIST_SKIN_POS_FREEB * )( ( BYTE * )PosSKFB + SrcUnitSize ), Dest += DestUnitSize )
			{
				// �g���Ă���{�[�����ЂƂ̏ꍇ�̓u�����h�s��̍쐬�̓X�L�b�v����
				if( PosSKFB->MatrixWeight[ 0 ].W == 1.0f )
				{
					Mat = Frame->UseSkinBoneMatrix[ PosSKFB->MatrixWeight[ 0 ].Index ] ;

					// ���_���W�ƃu�����h�s�����Z
					if( ShapePos != NULL )
					{
						VectorTransform4X4CTD(   ( VECTOR * )&Dest[  0 ], ShapePos,                       &Mat->md ) ;
					}
					else
					{
						VectorTransform4X4CTD(   ( VECTOR * )&Dest[  0 ], ( VECTOR * )&PosSKFB->Position, &Mat->md ) ;
					}
					VectorTransformSR4X4CTD( ( VECTOR * )&Dest[ 12 ], ( VECTOR * )&PosSKFB->Normal,   &Mat->md ) ;
				}
				else
				{
					// �u�����h�s��̍쐬
					VBlend = PosSKFB->MatrixWeight ;
					Weight = VBlend->W ;

					// �O�Ԗڂ͉��Z�ł͂Ȃ��̂ŕʏ���
					Mat = Frame->UseSkinBoneMatrix[ VBlend->Index ] ;
					UnSafeMatrix4X4CT_D_Eq_D_Mul_S( &BlendMat.md, &Mat->md, Weight ) ;
					VBlend ++ ;

					// �P�Ԗڂ���͉��Z
					for( j = 1 ; j < MaxBoneNum && VBlend->Index != -1 ; j ++, VBlend ++ )
					{
						Weight = VBlend->W ;

						if( Weight == 0.0f ) continue ;

						Mat = Frame->UseSkinBoneMatrix[ VBlend->Index ] ;
						UnSafeMatrix4X4CT_D_EqPlus_D_Mul_S( &BlendMat.md, &Mat->md, Weight ) ;
					}

					// ���_���W�ƃu�����h�s�����Z
					if( ShapePos != NULL )
					{
						VectorTransform4X4CTD(   ( VECTOR * )&Dest[  0 ], ShapePos,                       &BlendMat.md ) ;
					}
					else
					{
						VectorTransform4X4CTD(   ( VECTOR * )&Dest[  0 ], ( VECTOR * )&PosSKFB->Position, &BlendMat.md ) ;
					}
					VectorTransformSR4X4CTD( ( VECTOR * )&Dest[ 12 ], ( VECTOR * )&PosSKFB->Normal,   &BlendMat.md ) ;
				}

				if( ShapePos != NULL )
				{
					ShapePos ++ ;
				}
			}
		}
		else
		{
			for( i = 0 ; i < VertexNum ; i ++, PosSKFB = ( MV1_TLIST_SKIN_POS_FREEB * )( ( BYTE * )PosSKFB + SrcUnitSize ), Dest += DestUnitSize )
			{
				// �g���Ă���{�[�����ЂƂ̏ꍇ�̓u�����h�s��̍쐬�̓X�L�b�v����
				if( PosSKFB->MatrixWeight[ 0 ].W == 1.0f )
				{
					Mat = Frame->UseSkinBoneMatrix[ PosSKFB->MatrixWeight[ 0 ].Index ] ;

					// ���_���W�ƃu�����h�s�����Z
					if( ShapePos != NULL )
					{
						VectorTransform4X4CTF(   ( VECTOR * )&Dest[  0 ], ShapePos,                       &Mat->mf ) ;
					}
					else
					{
						VectorTransform4X4CTF(   ( VECTOR * )&Dest[  0 ], ( VECTOR * )&PosSKFB->Position, &Mat->mf ) ;
					}
					VectorTransformSR4X4CTF( ( VECTOR * )&Dest[ 12 ], ( VECTOR * )&PosSKFB->Normal,   &Mat->mf ) ;
				}
				else
				{
					// �u�����h�s��̍쐬
					VBlend = PosSKFB->MatrixWeight ;
					Weight = VBlend->W ;

					// �O�Ԗڂ͉��Z�ł͂Ȃ��̂ŕʏ���
					Mat = Frame->UseSkinBoneMatrix[ VBlend->Index ] ;
					UnSafeMatrix4X4CT_F_Eq_F_Mul_S( &BlendMat.mf, &Mat->mf, Weight ) ;
					VBlend ++ ;

					// �P�Ԗڂ���͉��Z
					for( j = 1 ; j < MaxBoneNum && VBlend->Index != -1 ; j ++, VBlend ++ )
					{
						Weight = VBlend->W ;

						if( Weight == 0.0f ) continue ;

						Mat = Frame->UseSkinBoneMatrix[ VBlend->Index ] ;
						UnSafeMatrix4X4CT_F_EqPlus_F_Mul_S( &BlendMat.mf, &Mat->mf, Weight ) ;
					}

					// ���_���W�ƃu�����h�s�����Z
					if( ShapePos != NULL )
					{
						VectorTransform4X4CTF(   ( VECTOR * )&Dest[  0 ], ShapePos,                       &BlendMat.mf ) ;
					}
					else
					{
						VectorTransform4X4CTF(   ( VECTOR * )&Dest[  0 ], ( VECTOR * )&PosSKFB->Position, &BlendMat.mf ) ;
					}
					VectorTransformSR4X4CTF( ( VECTOR * )&Dest[ 12 ], ( VECTOR * )&PosSKFB->Normal,   &BlendMat.mf ) ;
				}

				if( ShapePos != NULL )
				{
					ShapePos ++ ;
				}
			}
		}
	}

	// �X�V�ς݃t���O�𗧂Ă�
	MBTListPF->SkinFreeBoneVertexBufferUpdate = TRUE ;

	// ���_�o�b�t�@���X�V
	glBindBuffer( GL_ARRAY_BUFFER, MBTList->VertexBuffer->PF->VertexBufferObject ) ;
	glBufferSubData( GL_ARRAY_BUFFER, MBTList->VBStartVertex * DestUnitSize, MBTList->VertexNum * DestUnitSize, MBTListPF->SkinFreeBoneVertexBuffer ) ;
//	glBindBuffer( GL_ARRAY_BUFFER, 0 ) ;

	return 0 ;
}


// ���b�V���`�敔���𔲂��o��������
extern	void			MV1_DrawMesh_PF( MV1_MESH *Mesh, int TriangleListIndex )
{
	MV1_TRIANGLE_LIST          * RST TList ;
	MV1_TRIANGLE_LIST_BASE     * RST MBTList ;
//	MV1_TRIANGLE_LIST_BASE_PF  *     MBTListPF ;
	MV1_MESH_BASE              * RST MBMesh ;
	MV1_MODEL_BASE             * RST MBase ;
	MV1_MODEL                  * RST Model ;
	MV1_FRAME                  * RST Frame ;
	MV1_FRAME_BASE             * RST MBFrame ;
	int                              i ;
//	int                              SetupShaderMaterial ;
	int                              UseWorldViewMatrix ;

	Frame   = Mesh->Container ;
	Model   = Frame->Container ;
	MBFrame = Frame->BaseData ;
	MBase   = Model->BaseData ;
	MBMesh  = Mesh->BaseData ;

	// �`��f�o�C�X�������������牽�����Ȃ�
	if( Graphics_Hardware_CheckValid_PF() == 0 )
	{
		return ;
	}

	UseWorldViewMatrix = FALSE ;
	if( GSYS.DrawSetting.Large3DPositionSupport )
	{
		for( i = 0 ; i < MAX_USE_SHADOWMAP_NUM ; i ++ )
		{
			if( GSYS.DrawSetting.ShadowMap[ i ] != 0 )
			{
				break ;
			}
		}
		if( i != MAX_USE_SHADOWMAP_NUM )
		{
			UseWorldViewMatrix = TRUE ;
		}
	}

	// �}�e���A���̋��ʕ����̃Z�b�g�A�b�v
	if( MV1_ANDR_SetupMeshDrawMaterialCommon( Mesh ) == false )
	{
		return ;
	}

	// �}�e���A���̃Z�b�g�A�b�v
	MV1_ANDR_SetupMeshDrawMaterial( Mesh ) ;

	// �X�{�[���ȏ�̃X�L�j���O���b�V���̍X�V���������ǂ����̃t���O��|��
	MBTList = MBMesh->TriangleList ;
	for( i = 0 ; i < MBMesh->TriangleListNum ; i ++ , MBTList ++ )
	{
		( ( MV1_TRIANGLE_LIST_BASE_PF * )MBTList->PFBuffer )->SkinFreeBoneVertexBufferUpdate = FALSE ;
	}

	// �ʏ탁�b�V���̔�\���t���O�������Ă�����`�悵�Ȃ�
	if( Model->MeshCategoryHide[ DX_MV1_MESHCATEGORY_NORMAL ] == FALSE )
	{
		// �g���C�A���O�����X�g�̐������J��Ԃ�
		TList   = Mesh->TriangleList ;
		MBTList = MBMesh->TriangleList ;
//		SetupShaderMaterial = -1 ;
		for( i = 0 ; i < MBMesh->TriangleListNum ; i ++ , MBTList ++, TList = ( MV1_TRIANGLE_LIST * )( ( BYTE * )TList + sizeof( MV1_TRIANGLE_LIST ) + sizeof( MV1_TRIANGLE_LIST_PF ) ) )
		{
//			MBTListPF = ( MV1_TRIANGLE_LIST_BASE_PF * )MBTList->PFBuffer ;

			// �g���C�A���O�����X�g�̎w�肪����ꍇ�͂���ȊO�̃g���C�A���O�����X�g�͕`�悵�Ȃ�
			if( TriangleListIndex >= 0 && i != TriangleListIndex )
			{
				continue ;
			}

			// �V�F�[�_�[�̃Z�b�g�A�b�v
			if( MBTList->VertexType == MV1_VERTEX_TYPE_NORMAL && MBase->UsePackDraw )
			{
				if( MV1_ANDR_ShaderSetup( Mesh, MV1_VERTEX_TYPE_SKIN_4BONE, FALSE ) == FALSE )
				{
					continue ;
				}
			}
			else
			{
				if( MV1_ANDR_ShaderSetup( Mesh, MBTList->VertexType, FALSE ) == FALSE )
				{
					continue ;
				}
			}

			// ���_�o�b�t�@�̃Z�b�g�A�b�v
			if( TList->PF->VertexBufferObject )
			{
				Graphics_Android_DeviceState_SetupShaderVertexData(
					GANDR.Device.State.SetShader,
					&g_Model_VertexFormat[ MBTList->Container->Material->NormalLayerNum ? 1 : 0 ][ MBTList->VertexType != MV1_VERTEX_TYPE_SKIN_FREEBONE ? MBTList->VertexType : MV1_VERTEX_TYPE_NORMAL ],
					NULL,
					TList->PF->VertexBufferObject
				) ;
			}
			else
			{
				Graphics_Android_DeviceState_SetupShaderVertexData(
					GANDR.Device.State.SetShader,
					&g_Model_VertexFormat[ MBTList->Container->Material->NormalLayerNum ? 1 : 0 ][ MBTList->VertexType != MV1_VERTEX_TYPE_SKIN_FREEBONE ? MBTList->VertexType : MV1_VERTEX_TYPE_NORMAL ],
					NULL,
					MBTList->VertexBuffer->PF->VertexBufferObject
				) ;
			}
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, MBTList->VertexBuffer->PF->IndexBufferObject ) ;

			// ���_�̃^�C�v�ɂ���ď����𕪊�
			switch( MBTList->VertexType )
			{
			case MV1_VERTEX_TYPE_NORMAL :		// ���̃g���C�A���O�����X�g
				// ���������`��̏ꍇ�͂S�{�[���X�L�j���O���b�V���Ƃ��ĕ`�悷��
				if( MBase->UsePackDraw )
				{
					goto SD4BONESKIN ;
				}

				// �g�p���郍�[�J�������[���h�s��̗p��
				MV1_ANDR_SetWorldMatrix_MATRIX_4X4CT( &Frame->LocalWorldMatrix, UseWorldViewMatrix ) ;

#ifndef NOT_RENDER
				// �X�e�[�g�ƒ萔�o�b�t�@�̍X�V
				Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, MV1Man_Android.EnableLightNum ) ;

				// �`��
				glDrawElements(
					GL_TRIANGLES,
					MBTList->IndexNum,
					GL_UNSIGNED_SHORT,
					0
				) ;
				GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

				// �`����I������
//				Graphics_ANDR_RenderEnd() ;
#endif // NOT_RENDER

				if( GSYS.DrawSetting.Large3DPositionSupport && UseWorldViewMatrix == FALSE )
				{
					Graphics_Android_DeviceState_SetViewMatrix( &GSYS.DrawSetting.ViewMatrixF ) ;
				}
				break ;

				// �S�{�[���ȓ��g���C�A���O�����X�g�ƂW�{�[���ȓ��g���C�A���O�����X�g
			case MV1_VERTEX_TYPE_SKIN_4BONE :
			case MV1_VERTEX_TYPE_SKIN_8BONE :
SD4BONESKIN:
				{
					int n ;

					// ���������`�悩�ǂ����ŏ����𕪊�
					if( MBase->UsePackDraw )
					{
						DX_ANDR_SHADER_FLOAT4 *Dest ;
						int l ;
						int UsePackIndex ;
						int TotalDrawStockNum ;
						int DrawStockNum ;
						MATRIX_4X4CT_F *PackDrawMatrix ;

						if( MBTList->VertexType == MV1_VERTEX_TYPE_NORMAL )
						{
							PackDrawMatrix = Model->PackDrawMatrix + MBase->SkinBoneNum + ( Frame - Model->Frame ) ;
						}
						else
						{
							PackDrawMatrix = Model->PackDrawMatrix ;
						}

						UsePackIndex = 0 ;
						for( TotalDrawStockNum = Model->PackDrawStockNum ; TotalDrawStockNum > 0 ; )
						{
							DrawStockNum = TotalDrawStockNum ;
							if( DrawStockNum > MBTList->PackDrawMaxNum )
							{
								DrawStockNum = MBTList->PackDrawMaxNum ;
							}

							if( MBTList->VertexType == MV1_VERTEX_TYPE_NORMAL )
							{
								Dest = GANDR.Device.Shader.Constant.uLWMat ;
								for( l = 0 ; l < DrawStockNum ; l ++, PackDrawMatrix += MBase->PackDrawMatrixUnitNum )
								{
									Dest[ 0 ][ 0 ] = PackDrawMatrix->m[ 0 ][ 0 ] ;
									Dest[ 0 ][ 1 ] = PackDrawMatrix->m[ 0 ][ 1 ] ;
									Dest[ 0 ][ 2 ] = PackDrawMatrix->m[ 0 ][ 2 ] ;
									Dest[ 0 ][ 3 ] = PackDrawMatrix->m[ 0 ][ 3 ] ;
									Dest[ 1 ][ 0 ] = PackDrawMatrix->m[ 1 ][ 0 ] ;
									Dest[ 1 ][ 1 ] = PackDrawMatrix->m[ 1 ][ 1 ] ;
									Dest[ 1 ][ 2 ] = PackDrawMatrix->m[ 1 ][ 2 ] ;
									Dest[ 1 ][ 3 ] = PackDrawMatrix->m[ 1 ][ 3 ] ;
									Dest[ 2 ][ 0 ] = PackDrawMatrix->m[ 2 ][ 0 ] ;
									Dest[ 2 ][ 1 ] = PackDrawMatrix->m[ 2 ][ 1 ] ;
									Dest[ 2 ][ 2 ] = PackDrawMatrix->m[ 2 ][ 2 ] ;
									Dest[ 2 ][ 3 ] = PackDrawMatrix->m[ 2 ][ 3 ] ;
									Dest += 3 ;
								}
							}
							else
							{
								int MatrixIndex ;
								MATRIX_4X4CT_F *Src ;

								MatrixIndex = 0 ;
								for( l = 0 ; l < DrawStockNum ; l ++, PackDrawMatrix += MBase->PackDrawMatrixUnitNum )
								{
									for( n = 0 ; n < MBTList->UseBoneNum ; n ++, MatrixIndex ++ )
									{
										Src  = &PackDrawMatrix[ Frame->UseSkinBoneMatrix[ MBTList->UseBone[ n ] ] - Model->SkinBoneMatrix ] ;
										Dest = &GANDR.Device.Shader.Constant.uLWMat[ MatrixIndex * 3 ] ;

										Dest[ 0 ][ 0 ] = Src->m[ 0 ][ 0 ] ;
										Dest[ 0 ][ 1 ] = Src->m[ 0 ][ 1 ] ;
										Dest[ 0 ][ 2 ] = Src->m[ 0 ][ 2 ] ;
										Dest[ 0 ][ 3 ] = Src->m[ 0 ][ 3 ] ;
										Dest[ 1 ][ 0 ] = Src->m[ 1 ][ 0 ] ;
										Dest[ 1 ][ 1 ] = Src->m[ 1 ][ 1 ] ;
										Dest[ 1 ][ 2 ] = Src->m[ 1 ][ 2 ] ;
										Dest[ 1 ][ 3 ] = Src->m[ 1 ][ 3 ] ;
										Dest[ 2 ][ 0 ] = Src->m[ 2 ][ 0 ] ;
										Dest[ 2 ][ 1 ] = Src->m[ 2 ][ 1 ] ;
										Dest[ 2 ][ 2 ] = Src->m[ 2 ][ 2 ] ;
										Dest[ 2 ][ 3 ] = Src->m[ 2 ][ 3 ] ;
									}
								}
							}

							GANDR.Device.Shader.Constant.UpdateCount ++ ;

#ifndef NOT_RENDER
							// �X�e�[�g�ƒ萔�o�b�t�@�̍X�V
							Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, MV1Man_Android.EnableLightNum, 162 ) ;

							// �`��
							glDrawElements(
								GL_TRIANGLES,
								MBTList->IndexNum * DrawStockNum,
								GL_UNSIGNED_SHORT,
								0
							) ;
							GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

							// �`����I������
//							Graphics_ANDR_RenderEnd() ;
#endif

							TotalDrawStockNum -= DrawStockNum ;
							UsePackIndex      += DrawStockNum ;
						}
					}
					else
					{
						MV1_ANDR_SetupModelDrawWorldMatrix( Frame, MBTList, UseWorldViewMatrix ) ;
#ifndef NOT_RENDER
						// �X�e�[�g�ƒ萔�o�b�t�@�̍X�V
						Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, MV1Man_Android.EnableLightNum, MBTList->UseBoneNum * 3 ) ;

						// �`��
						glDrawElements(
							GL_TRIANGLES,
							MBTList->IndexNum,
							GL_UNSIGNED_SHORT,
							0
						) ;
						GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

						// �`����I������
//						Graphics_ANDR_RenderEnd() ;
#endif
						if( GSYS.DrawSetting.Large3DPositionSupport && UseWorldViewMatrix == FALSE )
						{
							Graphics_Android_DeviceState_SetViewMatrix( &GSYS.DrawSetting.ViewMatrixF ) ;
						}
					}
				}
				break ;

				// �{�[�����������g���C�A���O�����X�g
			case MV1_VERTEX_TYPE_SKIN_FREEBONE :
				// ���[�J�������[���h�s��͒P�ʍs��ɂ���
				Graphics_Android_DeviceState_SetWorldMatrix( &IdentityMat ) ;

#ifndef NOT_RENDER
				// ���_�f�[�^���X�V����
				MV1_ANDR_UpdateSkinFreeBoneMeshVertexData( MBFrame, MBTList, Frame, TList ) ;

				// �X�e�[�g�ƒ萔�o�b�t�@�̍X�V
				Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, MV1Man_Android.EnableLightNum ) ;

				// �`��
				glDrawElements(
					GL_TRIANGLES,
					MBTList->IndexNum,
					GL_UNSIGNED_SHORT,
					0
				) ;
				GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

				// �`����I������
//				Graphics_ANDR_RenderEnd() ;
#endif // NOT_RENDER
				break ;
			}
		}
	}

	// �g�D�[��������ꍇ�͗֊s����`��
	if( ( ( Model->MeshCategoryHide[ DX_MV1_MESHCATEGORY_OUTLINE ]             == FALSE && MV1Man.UseOrigShaderFlag == FALSE ) ||
		  ( Model->MeshCategoryHide[ DX_MV1_MESHCATEGORY_OUTLINE_ORIG_SHADER ] == FALSE && MV1Man.UseOrigShaderFlag == TRUE  ) ) && 
		( Mesh->Material->BaseData->Type == DX_MATERIAL_TYPE_TOON || Mesh->Material->BaseData->Type == DX_MATERIAL_TYPE_TOON_2 ) &&
		GSYS.DrawSetting.ShadowMapDraw == FALSE )
	{
		// �֊s���̕`��
		if( Mesh->Material->OutLineWidth    > 0.000001f ||
			Mesh->Material->OutLineDotWidth > 0.000001f )
		{
			float OutLineWidth ;

			// �֊s���̑������Z�b�g
			OutLineWidth = Mesh->Material->OutLineWidth /*/ Mesh->Container->Container->Scale*/ ;

			// �����X�N���[�����W��łP�h�b�g�ɖ����Ȃ��ꍇ�͑�������
			{
				VECTOR_D WorldPos1, WorldPos2 ;
				VECTOR_D ScreenPos1, ScreenPos2 ;
				double Width, DotWidth ;

				if( GSYS.DrawSetting.Large3DPositionSupport )
				{
					WorldPos1.x = Frame->LocalWorldMatrix.md.m[ 0 ][ 3 ] ;
					WorldPos1.y = Frame->LocalWorldMatrix.md.m[ 1 ][ 3 ] ;
					WorldPos1.z = Frame->LocalWorldMatrix.md.m[ 2 ][ 3 ] ;
				}
				else
				{
					WorldPos1.x = Frame->LocalWorldMatrix.mf.m[ 0 ][ 3 ] ;
					WorldPos1.y = Frame->LocalWorldMatrix.mf.m[ 1 ][ 3 ] ;
					WorldPos1.z = Frame->LocalWorldMatrix.mf.m[ 2 ][ 3 ] ;
				}
				ScreenPos1 = NS_ConvWorldPosToScreenPosD( WorldPos1 ) ;

				WorldPos2.x = WorldPos1.x + GSYS.DrawSetting.ViewMatrix.m[ 0 ][ 0 ] * OutLineWidth ;
				WorldPos2.y = WorldPos1.y + GSYS.DrawSetting.ViewMatrix.m[ 1 ][ 0 ] * OutLineWidth ;
				WorldPos2.z = WorldPos1.z + GSYS.DrawSetting.ViewMatrix.m[ 2 ][ 0 ] * OutLineWidth ;
				ScreenPos2 = NS_ConvWorldPosToScreenPosD( WorldPos2 ) ;

				Width = ScreenPos1.x - ScreenPos2.x ;
				if( Width < 0.0 )
				{
					Width = -Width ;
				}

				DotWidth = Mesh->Material->OutLineDotWidth ;
				if( DotWidth < 0.0000001 )
				{
					DotWidth = 1.125 ;
				}

				if( Width < DotWidth )
				{
					if( Width < 0.00000001 )
					{
						OutLineWidth *= 10000000.0f ;
					}
					else
					{
						OutLineWidth *= ( float )( DotWidth / Width ) ;
					}
				}
			}

			// �}�e���A���̋��ʕ����̃Z�b�g�A�b�v
			MV1_ANDR_SetupToonOutLineMeshDrawMaterialCommon( Mesh, OutLineWidth ) ;

			// �`��}�e���A���̃Z�b�g�A�b�v
			MV1_ANDR_SetupToonOutLineMeshDrawMaterial( Mesh ) ;

			// �g���C�A���O�����X�g�̐������J��Ԃ�
			TList   = Mesh->TriangleList ;
			MBTList = MBMesh->TriangleList ;
//			SetupShaderMaterial = -1 ;
			for( i = 0 ; i < MBMesh->TriangleListNum ; i ++ , MBTList ++, TList = ( MV1_TRIANGLE_LIST * )( ( BYTE * )TList + sizeof( MV1_TRIANGLE_LIST ) + sizeof( MV1_TRIANGLE_LIST_PF ) ) )
			{
//				MBTListPF = ( MV1_TRIANGLE_LIST_BASE_PF * )MBTList->PFBuffer ;

				// �g���C�A���O�����X�g�̎w�肪����ꍇ�͂���ȊO�̃g���C�A���O�����X�g�͕`�悵�Ȃ�
				if( TriangleListIndex >= 0 && i != TriangleListIndex )
				{
					continue ;
				}

				// �g�D�[���̗֊s���p�̃|���S���������ꍇ�͉������Ȃ�
				if( MBTList->ToonOutLineIndexNum == 0 )
				{
					continue ;
				}

				// �V�F�[�_�[�̃Z�b�g�A�b�v
				if( MBTList->VertexType == MV1_VERTEX_TYPE_NORMAL && MBase->UsePackDraw )
				{
					if( MV1_ANDR_ShaderSetup( Mesh, MV1_VERTEX_TYPE_SKIN_4BONE, TRUE ) == FALSE )
					{
						continue ;
					}
				}
				else
				{
					if( MV1_ANDR_ShaderSetup( Mesh, MBTList->VertexType, TRUE ) == FALSE )
					{
						continue ;
					}
				}

				// ���_�o�b�t�@�̃Z�b�g�A�b�v
				if( TList->PF->VertexBufferObject )
				{
					Graphics_Android_DeviceState_SetupShaderVertexData(
						GANDR.Device.State.SetShader,
						&g_Model_VertexFormat[ MBTList->Container->Material->NormalLayerNum ? 1 : 0 ][ MBTList->VertexType != MV1_VERTEX_TYPE_SKIN_FREEBONE ? MBTList->VertexType : MV1_VERTEX_TYPE_NORMAL ],
						NULL,
						TList->PF->VertexBufferObject
					) ;
				}
				else
				{
					Graphics_Android_DeviceState_SetupShaderVertexData(
						GANDR.Device.State.SetShader,
						&g_Model_VertexFormat[ MBTList->Container->Material->NormalLayerNum ? 1 : 0 ][ MBTList->VertexType != MV1_VERTEX_TYPE_SKIN_FREEBONE ? MBTList->VertexType : MV1_VERTEX_TYPE_NORMAL ],
						NULL,
						MBTList->VertexBuffer->PF->VertexBufferObject
					) ;
				}
				glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, MBTList->VertexBuffer->PF->IndexBufferObject ) ;

				switch( MBTList->VertexType )
				{
					// ���̃g���C�A���O�����X�g
				case MV1_VERTEX_TYPE_NORMAL :
					{
						// ���������`��̏ꍇ�͂S�{�[���X�L�j���O���b�V���Ƃ��ĕ`�悷��
						if( MBase->UsePackDraw )
						{
							goto T_SD4BONESKIN ;
						}

						// �g�p���郍�[�J�������[���h�s��̗p��
						MV1_ANDR_SetWorldMatrix_MATRIX_4X4CT( &Frame->LocalWorldMatrix, UseWorldViewMatrix ) ;
#ifndef NOT_RENDER
						// �X�e�[�g�ƒ萔�o�b�t�@�̍X�V
						Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, MV1Man_Android.EnableLightNum ) ;

						// �`��
						glDrawElements(
							GL_TRIANGLES,
							MBTList->ToonOutLineIndexNum,
							GL_UNSIGNED_SHORT,
							( void * )( sizeof( WORD ) * MBTList->ToonOutLineVBStartIndex )
						) ;
						GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

						// �`����I������
//						Graphics_ANDR_RenderEnd() ;
#endif // NOT_RENDER
						if( GSYS.DrawSetting.Large3DPositionSupport && UseWorldViewMatrix == FALSE )
						{
							Graphics_Android_DeviceState_SetViewMatrix( &GSYS.DrawSetting.ViewMatrixF ) ;
						}
					}
					break ;

					// �S�{�[���ȓ��g���C�A���O�����X�g�ƂW�{�[���ȓ��g���C�A���O�����X�g
				case MV1_VERTEX_TYPE_SKIN_4BONE :
				case MV1_VERTEX_TYPE_SKIN_8BONE :
T_SD4BONESKIN:
					{
						int n ;

						// ���������`�悩�ǂ����ŏ����𕪊�
						if( MBase->UsePackDraw )
						{
							DX_ANDR_SHADER_FLOAT4 *Dest ;
							int l ;
							int UsePackIndex ;
							int TotalDrawStockNum ;
							int DrawStockNum ;
							MATRIX_4X4CT_F *PackDrawMatrix ;

							if( MBTList->VertexType == MV1_VERTEX_TYPE_NORMAL )
							{
								PackDrawMatrix = Model->PackDrawMatrix + MBase->SkinBoneNum + ( Frame - Model->Frame ) ;
							}
							else
							{
								PackDrawMatrix = Model->PackDrawMatrix ;
							}

							UsePackIndex = 0 ;
							for( TotalDrawStockNum = Model->PackDrawStockNum ; TotalDrawStockNum > 0 ; )
							{
								DrawStockNum = TotalDrawStockNum ;
								if( DrawStockNum > MBTList->PackDrawMaxNum )
								{
									DrawStockNum = MBTList->PackDrawMaxNum ;
								}

								if( MBTList->VertexType == MV1_VERTEX_TYPE_NORMAL )
								{
									Dest = GANDR.Device.Shader.Constant.uLWMat ;
									for( l = 0 ; l < DrawStockNum ; l ++, PackDrawMatrix += MBase->PackDrawMatrixUnitNum )
									{
										Dest[ 0 ][ 0 ] = PackDrawMatrix->m[ 0 ][ 0 ] ;
										Dest[ 0 ][ 1 ] = PackDrawMatrix->m[ 0 ][ 1 ] ;
										Dest[ 0 ][ 2 ] = PackDrawMatrix->m[ 0 ][ 2 ] ;
										Dest[ 0 ][ 3 ] = PackDrawMatrix->m[ 0 ][ 3 ] ;
										Dest[ 1 ][ 0 ] = PackDrawMatrix->m[ 1 ][ 0 ] ;
										Dest[ 1 ][ 1 ] = PackDrawMatrix->m[ 1 ][ 1 ] ;
										Dest[ 1 ][ 2 ] = PackDrawMatrix->m[ 1 ][ 2 ] ;
										Dest[ 1 ][ 3 ] = PackDrawMatrix->m[ 1 ][ 3 ] ;
										Dest[ 2 ][ 0 ] = PackDrawMatrix->m[ 2 ][ 0 ] ;
										Dest[ 2 ][ 1 ] = PackDrawMatrix->m[ 2 ][ 1 ] ;
										Dest[ 2 ][ 2 ] = PackDrawMatrix->m[ 2 ][ 2 ] ;
										Dest[ 2 ][ 3 ] = PackDrawMatrix->m[ 2 ][ 3 ] ;
										Dest += 3 ;
									}
								}
								else
								{
									int MatrixIndex ;
									MATRIX_4X4CT_F *Src ;

									MatrixIndex = 0 ;
									for( l = 0 ; l < DrawStockNum ; l ++, PackDrawMatrix += MBase->PackDrawMatrixUnitNum )
									{
										for( n = 0 ; n < MBTList->UseBoneNum ; n ++, MatrixIndex ++ )
										{
											Src  = &PackDrawMatrix[ Frame->UseSkinBoneMatrix[ MBTList->UseBone[ n ] ] - Model->SkinBoneMatrix ] ;
											Dest = &GANDR.Device.Shader.Constant.uLWMat[ MatrixIndex * 3 ] ;

											Dest[ 0 ][ 0 ] = Src->m[ 0 ][ 0 ] ;
											Dest[ 0 ][ 1 ] = Src->m[ 0 ][ 1 ] ;
											Dest[ 0 ][ 2 ] = Src->m[ 0 ][ 2 ] ;
											Dest[ 0 ][ 3 ] = Src->m[ 0 ][ 3 ] ;
											Dest[ 1 ][ 0 ] = Src->m[ 1 ][ 0 ] ;
											Dest[ 1 ][ 1 ] = Src->m[ 1 ][ 1 ] ;
											Dest[ 1 ][ 2 ] = Src->m[ 1 ][ 2 ] ;
											Dest[ 1 ][ 3 ] = Src->m[ 1 ][ 3 ] ;
											Dest[ 2 ][ 0 ] = Src->m[ 2 ][ 0 ] ;
											Dest[ 2 ][ 1 ] = Src->m[ 2 ][ 1 ] ;
											Dest[ 2 ][ 2 ] = Src->m[ 2 ][ 2 ] ;
											Dest[ 2 ][ 3 ] = Src->m[ 2 ][ 3 ] ;
										}
									}
								}

								GANDR.Device.Shader.Constant.UpdateCount ++ ;

#ifndef NOT_RENDER
								// �X�e�[�g�ƒ萔�o�b�t�@�̍X�V
								Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, MV1Man_Android.EnableLightNum, 162 ) ;

								// �`��
								glDrawElements(
									GL_TRIANGLES,
									MBTList->ToonOutLineIndexNum * DrawStockNum,
									GL_UNSIGNED_SHORT,
									( void * )( sizeof( WORD ) * MBTList->ToonOutLineVBStartIndex )
								) ;
								GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

								// �`����I������
//								Graphics_ANDR_RenderEnd() ;
#endif

								TotalDrawStockNum -= DrawStockNum ;
								UsePackIndex      += DrawStockNum ;
							}
						}
						else
						{
							MV1_ANDR_SetupModelDrawWorldMatrix( Frame, MBTList, UseWorldViewMatrix ) ;
#ifndef NOT_RENDER
							// �X�e�[�g�ƒ萔�o�b�t�@�̍X�V
							Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, MV1Man_Android.EnableLightNum, MBTList->UseBoneNum * 3 ) ;

							// �`��
							glDrawElements(
								GL_TRIANGLES,
								MBTList->ToonOutLineIndexNum,
								GL_UNSIGNED_SHORT,
								( void * )( sizeof( WORD ) * MBTList->ToonOutLineVBStartIndex )
							) ;
							GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

							// �`����I������
//							Graphics_ANDR_RenderEnd() ;
#endif	// NOT_RENDER
							if( GSYS.DrawSetting.Large3DPositionSupport && UseWorldViewMatrix == FALSE )
							{
								Graphics_Android_DeviceState_SetViewMatrix( &GSYS.DrawSetting.ViewMatrixF ) ;
							}
						}
					}
					break ;

					// �{�[�����������g���C�A���O�����X�g
				case MV1_VERTEX_TYPE_SKIN_FREEBONE :
					// ���[�J�������[���h�s��͒P�ʍs��ɂ���
					Graphics_Android_DeviceState_SetWorldMatrix( &IdentityMat ) ;

#ifndef NOT_RENDER
					// ���_�f�[�^���X�V����
					MV1_ANDR_UpdateSkinFreeBoneMeshVertexData( MBFrame, MBTList, Frame, TList ) ;

					// �X�e�[�g�ƒ萔�o�b�t�@�̍X�V
					Graphics_Android_DeviceState_UpdateShaderUniform( GANDR.Device.State.SetShader, MV1Man_Android.EnableLightNum ) ;

					// �`��
					glDrawElements(
						GL_TRIANGLES,
						MBTList->ToonOutLineIndexNum,
						GL_UNSIGNED_SHORT,
						( void * )( sizeof( WORD ) * MBTList->ToonOutLineVBStartIndex )
					) ;
					GSYS.PerformanceInfo.NowFrameDrawCallCount ++ ;

					// �`����I������
//					Graphics_ANDR_RenderEnd() ;

#endif // NOT_RENDER
					break ;
				}
			}
		}
	}

	glBindBuffer( GL_ARRAY_BUFFER, 0 ) ;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ) ;

//	SetUserBlendInfo( NULL ) ;
}



#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_MODEL

#endif // DX_NON_GRAPHICS
