//-----------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用GraphFilter系プログラム
// 
<<<<<<< HEAD
//  	Ver 3.24b
=======
//  	Ver 3.24d
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
// 
//-----------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_GRAPHICS

// インクルード ---------------------------------------------------------------
#include "DxGraphicsHTML5.h"
#include "DxGraphicsFilterHTML5.h"
#include "DxGraphicsHTML5.h"
#include "DxShader_DataType_HTML5.h"
#include "DxShader_FS_HTML5.h"
#include "../DxGraphics.h"
#include "../DxLog.h"
#include "../DxBaseFunc.h"

#ifndef DX_NON_FILTER

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 -----------------------------------------------------------------

// 構造体宣言 -----------------------------------------------------------------

// データ定義 -----------------------------------------------------------------

GRAPHFILTER_SYSTEMIFNO_HTML5 GraphFilterSystemInfoHTML5 ;

// 関数宣言 -------------------------------------------------------------------

static int		HTML5_GraphFilter_GetWorkTexture( int IsFloatType, DWORD TexSizeW, DWORD TexSizeH, DWORD HandleIndex ) ;	// フィルター作業用のテクスチャハンドルを取得する
static int		HTML5_MemLoadShaderCode( const char *ShaderName, int ShaderType /* DX_SHADERTYPE_VERTEX 等 */ ) ;			// 指定名の事前用意シェーダーを読み込む
static GLuint	HTML5_GetFragmentShader( int PixelShaderHandle ) ;														// ピクセルシェーダーハンドルの中のフラグメントシェーダーを取得する
static int		HTML5_FilterStretchBlt( GRAPHICS_HTML5_SHADER *UseShader, GRAPHFILTER_INFO *Info, int IsLinearFilter = TRUE, int ScaleDivNum = 1, int SubImageHandle = -1, VERTEX_TEX8_2D *Texcoord8Vertex = NULL ) ;

// プログラム -----------------------------------------------------------------

// フィルター作業用のテクスチャハンドルを取得する
static int	HTML5_GraphFilter_GetWorkTexture( int IsFloatType, DWORD TexSizeW, DWORD TexSizeH, DWORD HandleIndex )
{
	IMAGEDATA *BaseImage ;
	DWORD       NPowW ;
	DWORD       NPowH ;
	int         WorkTexSizeW ;
	int         WorkTexSizeH ;

	for( NPowW = 0 ; ( DWORD )( 1 << NPowW ) < TexSizeW ; NPowW ++ ){}
	for( NPowH = 0 ; ( DWORD )( 1 << NPowH ) < TexSizeH ; NPowH ++ ){}
	WorkTexSizeW = ( int )( 1 << NPowW ) ;
	WorkTexSizeH = ( int )( 1 << NPowH ) ;

	if( GRAPHCHK( GraphFilterSystemInfoHTML5.WorkDrawValidGrHandle[ IsFloatType ][ NPowW ][ NPowH ][ HandleIndex ], BaseImage ) )
	{
		SETUP_GRAPHHANDLE_GPARAM GParam ;

		Graphics_Image_InitSetupGraphHandleGParam_Normal_DrawValid_NoneZBuffer( &GParam, 32, TRUE ) ;
		GParam.DrawValidFloatTypeGraphCreateFlag = IsFloatType ;

		GraphFilterSystemInfoHTML5.WorkDrawValidGrHandle[ IsFloatType ][ NPowW ][ NPowH ][ HandleIndex ] = Graphics_Image_MakeGraph_UseGParam( &GParam, WorkTexSizeW, WorkTexSizeH, FALSE, FALSE, 0, FALSE ) ;
		if( GraphFilterSystemInfoHTML5.WorkDrawValidGrHandle[ IsFloatType ][ NPowW ][ NPowH ][ HandleIndex ] < 0 )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\x5c\x4f\x6d\x69\x28\x75\xcf\x63\x3b\x75\xef\x53\xfd\x80\xc6\x30\xaf\x30\xb9\x30\xc1\x30\xe3\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x53\x00\x69\x00\x7a\x00\x65\x00\x3a\x00\x25\x00\x64\x00\x78\x00\x25\x00\x64\x00\x00"/*@ L"作業用描画可能テクスチャの作成に失敗しました Size:%dx%d" @*/, WorkTexSizeW, WorkTexSizeH )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterSystemInfoHTML5.WorkDrawValidGrHandle[ IsFloatType ][ NPowW ][ NPowH ][ HandleIndex ], &GraphFilterSystemInfoHTML5.WorkDrawValidGrHandle[ IsFloatType ][ NPowW ][ NPowH ][ HandleIndex ] ) ;
	}

	return GraphFilterSystemInfoHTML5.WorkDrawValidGrHandle[ IsFloatType ][ NPowW ][ NPowH ][ HandleIndex ] ;
}

// 指定名の事前用意シェーダーを読み込む
static int HTML5_MemLoadShaderCode( const char *ShaderName, int ShaderType /* DX_SHADERTYPE_VERTEX 等 */ )
{
	int Addr, Size ;
	BYTE *FileImage ;
	int Ret ;

	if( GHTML5.ShaderCode.Base.BaseShaderInitializeFlag == FALSE )
	{
		return -1 ;
	}

	if( DXA_GetFileInfo( &GHTML5.ShaderCode.Base.FilterShaderBinDxa, DX_CHARCODEFORMAT_ASCII, ShaderName, &Addr, &Size ) < 0 )
	{
		return -1 ;
	}

	FileImage = ( BYTE * )DXA_GetFileImage( &GHTML5.ShaderCode.Base.FilterShaderBinDxa ) + Addr ;

	Ret = Graphics_Shader_CreateHandle_UseGParam( ShaderType, FileImage, Size, FALSE, FALSE ) ;

	return Ret ;
}

// ピクセルシェーダーハンドルの中のフラグメントシェーダーを取得する
static GLuint HTML5_GetFragmentShader( int PixelShaderHandle )
{
	SHADERHANDLEDATA   *pShader ;

	if( SHADERCHK( PixelShaderHandle, pShader ) )
		return 0 ;

	return pShader->PF->Shader ;
}

static int HTML5_FilterStretchBlt( GRAPHICS_HTML5_SHADER *UseShader, GRAPHFILTER_INFO *Info, int IsLinearFilter, int ScaleDivNum, int SubImageHandle, VERTEX_TEX8_2D *Texcoord8Vertex )
{
	IMAGEDATA *          SrcImage              = NULL ;
	IMAGEDATA *          BlendImage            = NULL ;
	IMAGEDATA *          DestImage             = NULL ;
	SHADOWMAPDATA *      SrcShadowMap          = NULL ;
	SHADOWMAPDATA *      DestShadowMap         = NULL ;
	GLuint               SrcTexture            = 0 ;
	uint32_t             SrcTextureWidth       = 0 ;
	uint32_t             SrcTextureHeight      = 0 ;
	GLuint               DestFrameBuffer       = 0 ;
	uint32_t             DestFrameBufferWidth  = 0 ;
	uint32_t             DestFrameBufferHeight = 0 ;
	GLuint               BlendTexture          = 0 ;
	uint32_t             BlendTextureWidth     = 0 ;
	uint32_t             BlendTextureHeight    = 0 ;
	int  SrcWidth ;
	int  SrcHeight ;
	RECT SrcRect ;
	RECT DestRect ;
	RECT BlendRect ;

	if( GRAPHCHK(     Info->SrcGrHandle, SrcImage    ) &&
		SHADOWMAPCHK( Info->SrcGrHandle, SrcShadowMap ) )
	{
		return -1 ;
	}

	if( Info->DestGrHandle != DX_SCREEN_BACK &&
<<<<<<< HEAD
 		GRAPHCHK(     Info->DestGrHandle, DestImage    ) &&
=======
		GRAPHCHK(     Info->DestGrHandle, DestImage    ) &&
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
		SHADOWMAPCHK( Info->DestGrHandle, DestShadowMap ) )
	{
		return -1 ;
	}

	if( SrcShadowMap != NULL )
	{
		SrcTexture       = SrcShadowMap->PF->Texture.TextureBuffer ;
		SrcTextureWidth  = SrcShadowMap->PF->Texture.Width ;
		SrcTextureHeight = SrcShadowMap->PF->Texture.Height ;
	}
	else
	{
		SrcTexture       = SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.TextureBuffer ;
		SrcTextureWidth  = SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width ;
		SrcTextureHeight = SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height ;
	}

	if( DestShadowMap != NULL )
	{
		DestFrameBuffer       = DestShadowMap->PF->FrameBuffer ;
		DestFrameBufferWidth  = DestShadowMap->PF->Texture.Width ;
		DestFrameBufferHeight = DestShadowMap->PF->Texture.Height ;
	}
<<<<<<< HEAD
	else if( DestImage != NULL )
=======
	else
	if( DestImage != NULL )
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	{
		DestFrameBuffer       = DestImage->Hard.Draw[ 0 ].Tex->PF->FrameBuffer ;
		DestFrameBufferWidth  = DestImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width ;
		DestFrameBufferHeight = DestImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height ;
	}
	else
<<<<<<< HEAD
 	{
 		DestFrameBuffer       = GHTML5.Device.Screen.SubBackBufferFrameBuffer ;
 		DestFrameBufferWidth  = GHTML5.Device.Screen.SubBackBufferTextureSizeX ;
 		DestFrameBufferHeight = GHTML5.Device.Screen.SubBackBufferTextureSizeY ;
 	}
=======
	{
		DestFrameBuffer       = GHTML5.Device.Screen.SubBackBufferFrameBuffer ;
		DestFrameBufferWidth  = GHTML5.Device.Screen.SubBackBufferTextureSizeX ;
		DestFrameBufferHeight = GHTML5.Device.Screen.SubBackBufferTextureSizeY ;
	}
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	SrcRect.left   = Info->SrcX1 ;
	SrcRect.top    = Info->SrcY1 ;
	SrcRect.right  = Info->SrcX2 ;
	SrcRect.bottom = Info->SrcY2 ;

	SrcWidth  = Info->SrcX2 - Info->SrcX1 ;
	SrcHeight = Info->SrcY2 - Info->SrcY1 ;

	if( ScaleDivNum != 1 )
	{
		DestRect.left   = Info->DestX                           ;
		DestRect.right  = Info->DestX + SrcWidth  / ScaleDivNum ;
		DestRect.top    = Info->DestY                           ;
		DestRect.bottom = Info->DestY + SrcHeight / ScaleDivNum ;
	}
	else
	{
		DestRect.left   = Info->DestX             ;
		DestRect.right  = Info->DestX + SrcWidth  ;
		DestRect.top    = Info->DestY             ;
		DestRect.bottom = Info->DestY + SrcHeight ;
	}

	if( Info->IsBlend || SubImageHandle >= 0 )
	{
		if( GRAPHCHK( Info->IsBlend ? Info->BlendGrHandle : SubImageHandle, BlendImage ) )
			return -1 ;

		BlendTexture       = BlendImage->Hard.Draw[ 0 ].Tex->PF->Texture.TextureBuffer ;
		BlendTextureWidth  = BlendImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width ;
		BlendTextureHeight = BlendImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height ;

		if( Info->BlendPosEnable )
		{
			BlendRect.left   = BlendImage->Hard.Draw[ 0 ].UsePosXF + Info->BlendX             ;
			BlendRect.top    = BlendImage->Hard.Draw[ 0 ].UsePosYF + Info->BlendY             ;
			if( Info->BlendPos2Enable )
			{
				BlendRect.right  = BlendImage->Hard.Draw[ 0 ].UsePosXF + Info->BlendX2 ;
				BlendRect.bottom = BlendImage->Hard.Draw[ 0 ].UsePosYF + Info->BlendY2 ;
			}
			else
			{
				BlendRect.right  = BlendImage->Hard.Draw[ 0 ].UsePosXF + Info->BlendX + SrcWidth  ;
				BlendRect.bottom = BlendImage->Hard.Draw[ 0 ].UsePosYF + Info->BlendY + SrcHeight ;
			}
		}
		else
		{
			BlendRect.left   = BlendImage->Hard.Draw[ 0 ].UsePosXF ;
			BlendRect.right  = BlendImage->Hard.Draw[ 0 ].UsePosXF + BlendImage->Hard.Draw[ 0 ].WidthF ;
			BlendRect.top    = BlendImage->Hard.Draw[ 0 ].UsePosYF ;
			BlendRect.bottom = BlendImage->Hard.Draw[ 0 ].UsePosYF + BlendImage->Hard.Draw[ 0 ].HeightF ;
		}
	}

	// 転送
	Graphics_HTML5_StretchRect(
		SrcTexture,      SrcTextureWidth,      SrcTextureHeight,      &SrcRect,
		DestFrameBuffer, DestFrameBufferWidth, DestFrameBufferHeight, &DestRect,
		IsLinearFilter ? GL_LINEAR : GL_NEAREST,
		Info->BltBlendMode == DX_BLENDMODE_ALPHA ? TRUE : FALSE,
		UseShader,
		BlendTexture,    BlendTextureWidth,    BlendTextureHeight,    &BlendRect,
		Texcoord8Vertex
	) ;

	// 終了
	return 0 ;
}













// 環境依存関係

extern int	GraphFilter_Initialize_PF( void )
{
	return 0 ;
}

extern int	GraphFilter_Terminate_PF( void )
{
	// 全てのシェーダーを解放する
	GraphFilter_HTML5_ReleaseShaderAll() ;

	return 0 ;
}

extern int	GraphFilter_Mono_PF(       GRAPHFILTER_INFO *Info, float Cb, float Cr )
{
	static const char *FlagFileName[ 1 ] =
	{
		"Mono.flag",
	};
	DX_HTML5_SHADER_FLOAT4 ParamF4[ 2 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	if( GraphFilterShaderHandle.MonoPS < 0 )
	{
		GraphFilterShaderHandle.MonoPS = HTML5_MemLoadShaderCode( FlagFileName[ 0 ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.MonoPS < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ 0 ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.MonoPS, &GraphFilterShaderHandle.MonoPS ) ;
	}
	if( GraphFilterSystemInfoHTML5.Mono.Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.Mono, GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.MonoPS ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.Mono ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.Mono ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	ParamF4[ 0 ][ 0 ] = 0.29900f ;
	ParamF4[ 0 ][ 1 ] = 0.58700f ;
	ParamF4[ 0 ][ 2 ] = 0.11400f ;
	ParamF4[ 0 ][ 3 ] = 0.0f ;
	ParamF4[ 1 ][ 0 ] = 1.40200f * Cr ;
	ParamF4[ 1 ][ 1 ] = 0.34414f * Cb - 0.71414f * Cr ;
	ParamF4[ 1 ][ 2 ] = 1.77200f * Cb ;
	ParamF4[ 1 ][ 3 ] = 0.0f ;

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"     ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uRGBToY"     ), ParamF4[ 0 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uYCbCrToRGB" ), ParamF4[ 1 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"     ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uRGBToY"     ), ParamF4[ 0 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uYCbCrToRGB" ), ParamF4[ 1 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_Gauss_PF(      GRAPHFILTER_INFO *Info, int PixelWidth, float Param, float *Table )
{
	static const char *FlagFileName[] =
	{
		"Gauss_08Pixel_FS.flag",
		"Gauss_16Pixel_FS.flag",
		"Gauss_32Pixel_FS.flag"
	} ;
	IMAGEDATA               *SrcImage      = NULL ;
	SHADOWMAPDATA           *SrcShadowMap  = NULL ;
	IMAGEDATA               *DestImage     = NULL ;
	SHADOWMAPDATA           *DestShadowMap = NULL ;
	int                      UseShader = 0 ;
	int                      TexWidth ;
	int                      TexHeight ;
	float                    TexWidthF ;
	float                    TexHeightF ;
//	RECT                     BltRect ;

	if( GRAPHCHK(     Info->SrcGrHandle, SrcImage    ) &&
		SHADOWMAPCHK( Info->SrcGrHandle, SrcShadowMap ) )
	{
		return -1 ;
	}

	// PixelWidth によってシェーダーを変更
	switch( PixelWidth )
	{
	case 8  : UseShader = 0 ; break ;
	case 16 : UseShader = 1 ; break ;
	case 32 : UseShader = 2 ; break ;
	}

	NS_GetGraphTextureSize( Info->SrcGrHandle, &TexWidth, &TexHeight ) ;
	TexWidthF  = ( float )TexWidth ;
	TexHeightF = ( float )TexHeight ;
/*	BltRect.left   = 0 ;
	BltRect.top    = 0 ;
	BltRect.right  = TexWidth ;
	BltRect.bottom = TexHeight ;
*/
/*	if( Param < 0.0000001f )
	{
		IMAGEDATA *DestImage = NULL ;
		SHADOWMAPDATA *DestShadowMap = NULL ;

		if( GRAPHCHK(     Info->DestGrHandle, DestImage    ) &&
			SHADOWMAPCHK( Info->DestGrHandle, DestShadowMap ) )
			return -1 ;

		if( DestShadowMap )
		{
			Graphics_HTML5_StretchRect(
				SrcImage->Hard.Draw[ 0 ].Tex->PF->D3D11.Texture, SrcImage->Hard.Draw[ 0 ].Tex->PF->D3D11.TextureSRV, &BltRect,
				DestShadowMap->PF->D3D11.DepthTexture,           DestShadowMap->PF->D3D11.DepthTextureRTV,           &BltRect ) ;
		}
		else
		{
			Graphics_HTML5_StretchRect(
				SrcImage->Hard.Draw[ 0 ].Tex->PF->D3D11.Texture,  SrcImage->Hard.Draw[ 0 ].Tex->PF->D3D11.TextureSRV,  &BltRect,
				DestImage->Hard.Draw[ 0 ].Tex->PF->D3D11.Texture, DestImage->Hard.Draw[ 0 ].Tex->PF->D3D11.TextureRTV, &BltRect ) ;
		}
	}
	else */
	{
		DX_HTML5_SHADER_FLOAT4 ParamF4Buf[ 12 ] ;
		DX_HTML5_SHADER_FLOAT4 *ParamF4 = ParamF4Buf ;
<<<<<<< HEAD
		GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
		GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

		// 使用するシェーダーのセットアップ
		if( GraphFilterShaderHandle.Gauss_PS[ UseShader ] < 0 )
		{
			GraphFilterShaderHandle.Gauss_PS[ UseShader ] = HTML5_MemLoadShaderCode( FlagFileName[ UseShader ], DX_SHADERTYPE_PIXEL ) ;
			if( GraphFilterShaderHandle.Gauss_PS[ UseShader ] < 0 )
			{
				char PathUTF16LE[ 128 ] ;

				ConvString( FlagFileName[ UseShader ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
				DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
				return -1 ;
			}
			NS_SetDeleteHandleFlag( GraphFilterShaderHandle.Gauss_PS[ UseShader ], &GraphFilterShaderHandle.Gauss_PS[ UseShader ] ) ;
		}
		if( GraphFilterSystemInfoHTML5.Gauss[ UseShader ].Shader == 0 )
		{
			Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.Gauss[ UseShader ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.Gauss_PS[ UseShader ] ) ) ;
		}
<<<<<<< HEAD
		UseHTML5Shader = &GraphFilterSystemInfoHTML5.Gauss[ UseShader ] ;
=======
		UseAndrShader = &GraphFilterSystemInfoHTML5.Gauss[ UseShader ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

		ParamF4[ 0 ][ 0 ] = Table[ 0 ] ;
		ParamF4[ 0 ][ 1 ] = Table[ 1 ] ;
		ParamF4[ 0 ][ 2 ] = Table[ 2 ] ;
		ParamF4[ 0 ][ 3 ] = Table[ 3 ] ;
		ParamF4[ 1 ][ 0 ] = Table[ 4 ] ;
		ParamF4[ 1 ][ 1 ] = Table[ 5 ] ;
		ParamF4[ 1 ][ 2 ] = Table[ 6 ] ;
		ParamF4[ 1 ][ 3 ] = Table[ 7 ] ;
		ParamF4[ 2 ][ 0 ] = Table[ 8 ] ;
		ParamF4[ 2 ][ 1 ] = Table[ 9 ] ;
		ParamF4[ 2 ][ 2 ] = Table[ 10 ] ;
		ParamF4[ 2 ][ 3 ] = Table[ 11 ] ;
		ParamF4[ 3 ][ 0 ] = Table[ 12 ] ;
		ParamF4[ 3 ][ 1 ] = Table[ 13 ] ;
		ParamF4[ 3 ][ 2 ] = Table[ 14 ] ;
		ParamF4[ 3 ][ 3 ] = Table[ 15 ] ;
		ParamF4 += 4 ;

		// パスによって処理を分岐
		switch( Info->Pass )
		{
		case 0 :
			ParamF4[ 0 ][ 0 ] =  0.0f / TexWidthF ; ParamF4[ 0 ][ 1 ] = 0.0f ;
			ParamF4[ 0 ][ 2 ] =  1.5f / TexWidthF ; ParamF4[ 0 ][ 3 ] = 0.0f ;
			ParamF4[ 1 ][ 0 ] =  3.5f / TexWidthF ; ParamF4[ 1 ][ 1 ] = 0.0f ;
			ParamF4[ 1 ][ 2 ] =  5.5f / TexWidthF ; ParamF4[ 1 ][ 3 ] = 0.0f ;
			ParamF4[ 2 ][ 0 ] =  7.5f / TexWidthF ; ParamF4[ 2 ][ 1 ] = 0.0f ;
			ParamF4[ 2 ][ 2 ] =  9.5f / TexWidthF ; ParamF4[ 2 ][ 3 ] = 0.0f ;
			ParamF4[ 3 ][ 0 ] = 11.5f / TexWidthF ; ParamF4[ 3 ][ 1 ] = 0.0f ;
			ParamF4[ 3 ][ 2 ] = 13.5f / TexWidthF ; ParamF4[ 3 ][ 3 ] = 0.0f ;
			ParamF4[ 4 ][ 0 ] = 15.5f / TexWidthF ; ParamF4[ 4 ][ 1 ] = 0.0f ;
			ParamF4[ 4 ][ 2 ] = 17.5f / TexWidthF ; ParamF4[ 4 ][ 3 ] = 0.0f ;
			ParamF4[ 5 ][ 0 ] = 19.5f / TexWidthF ; ParamF4[ 5 ][ 1 ] = 0.0f ;
			ParamF4[ 5 ][ 2 ] = 21.5f / TexWidthF ; ParamF4[ 5 ][ 3 ] = 0.0f ;
			ParamF4[ 6 ][ 0 ] = 23.5f / TexWidthF ; ParamF4[ 6 ][ 1 ] = 0.0f ;
			ParamF4[ 6 ][ 2 ] = 25.5f / TexWidthF ; ParamF4[ 6 ][ 3 ] = 0.0f ;
			ParamF4[ 7 ][ 0 ] = 27.5f / TexWidthF ; ParamF4[ 7 ][ 1 ] = 0.0f ;
			ParamF4[ 7 ][ 2 ] = 29.5f / TexWidthF ; ParamF4[ 7 ][ 3 ] = 0.0f ;
			break ;

		case 1 :
			ParamF4[ 0 ][ 0 ] = 0.0f ; ParamF4[ 0 ][ 1 ] =  0.0f / TexHeightF ;
			ParamF4[ 0 ][ 2 ] = 0.0f ; ParamF4[ 0 ][ 3 ] =  1.5f / TexHeightF ;
			ParamF4[ 1 ][ 0 ] = 0.0f ; ParamF4[ 1 ][ 1 ] =  3.5f / TexHeightF ;
			ParamF4[ 1 ][ 2 ] = 0.0f ; ParamF4[ 1 ][ 3 ] =  5.5f / TexHeightF ;
			ParamF4[ 2 ][ 0 ] = 0.0f ; ParamF4[ 2 ][ 1 ] =  7.5f / TexHeightF ;
			ParamF4[ 2 ][ 2 ] = 0.0f ; ParamF4[ 2 ][ 3 ] =  9.5f / TexHeightF ;
			ParamF4[ 3 ][ 0 ] = 0.0f ; ParamF4[ 3 ][ 1 ] = 11.5f / TexHeightF ;
			ParamF4[ 3 ][ 2 ] = 0.0f ; ParamF4[ 3 ][ 3 ] = 13.5f / TexHeightF ;
			ParamF4[ 4 ][ 0 ] = 0.0f ; ParamF4[ 4 ][ 1 ] = 15.5f / TexHeightF ;
			ParamF4[ 4 ][ 2 ] = 0.0f ; ParamF4[ 4 ][ 3 ] = 17.5f / TexHeightF ;
			ParamF4[ 5 ][ 0 ] = 0.0f ; ParamF4[ 5 ][ 1 ] = 19.5f / TexHeightF ;
			ParamF4[ 5 ][ 2 ] = 0.0f ; ParamF4[ 5 ][ 3 ] = 21.5f / TexHeightF ;
			ParamF4[ 6 ][ 0 ] = 0.0f ; ParamF4[ 6 ][ 1 ] = 23.5f / TexHeightF ;
			ParamF4[ 6 ][ 2 ] = 0.0f ; ParamF4[ 6 ][ 3 ] = 25.5f / TexHeightF ;
			ParamF4[ 7 ][ 0 ] = 0.0f ; ParamF4[ 7 ][ 1 ] = 27.5f / TexHeightF ;
			ParamF4[ 7 ][ 2 ] = 0.0f ; ParamF4[ 7 ][ 3 ] = 29.5f / TexHeightF ;
			break ;
		}

		// シェーダーを使用状態にセット
<<<<<<< HEAD
		glUseProgram( UseHTML5Shader->Shader ) ;

		// Uniform の値をセット
		UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"      ), 0            ) ;
		glUniform4fv( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uPixelWeight" ), 4, ParamF4Buf[ 0 ] ) ;
		glUniform4fv( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uPixelOffset" ), 8, ParamF4Buf[ 4 ] ) ;

		HTML5_FilterStretchBlt( UseHTML5Shader, Info ) ;
=======
		glUseProgram( UseAndrShader->Shader ) ;

		// Uniform の値をセット
		UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"      ), 0            ) ;
		glUniform4fv( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uPixelWeight" ), 4, ParamF4Buf[ 0 ] ) ;
		glUniform4fv( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uPixelOffset" ), 8, ParamF4Buf[ 4 ] ) ;

		HTML5_FilterStretchBlt( UseAndrShader, Info ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

		if( Info->Pass == 0 )
		{
			GLuint      SrcTexture            = 0 ;
			uint32_t    SrcTextureWidth       = 0 ;
			uint32_t    SrcTextureHeight      = 0 ;
			GLuint      DestFrameBuffer       = 0 ;
			uint32_t    DestFrameBufferWidth  = 0 ;
			uint32_t    DestFrameBufferHeight = 0 ;
			RECT SrcRect ;
			RECT DestRect ;
			int Width ;
			int Height ;
			int TexWidth ;
			int TexHeight ;

			if( GRAPHCHK(     Info->SrcGrHandle, SrcImage    ) &&
				SHADOWMAPCHK( Info->SrcGrHandle, SrcShadowMap ) )
			{
				return -1 ;
			}

			if( GRAPHCHK(     Info->DestGrHandle, DestImage    ) &&
				SHADOWMAPCHK( Info->DestGrHandle, DestShadowMap ) )
			{
				return -1 ;
			}

			if( SrcShadowMap != NULL )
			{
				SrcTexture       = SrcShadowMap->PF->Texture.TextureBuffer ;
				SrcTextureWidth  = SrcShadowMap->PF->Texture.Width ;
				SrcTextureHeight = SrcShadowMap->PF->Texture.Height ;
			}
			else
			{
				SrcTexture       = SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.TextureBuffer ;
				SrcTextureWidth  = SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width ;
				SrcTextureHeight = SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height ;
			}

			if( DestShadowMap != NULL )
			{
				DestFrameBuffer       = DestShadowMap->PF->FrameBuffer ;
				DestFrameBufferWidth  = DestShadowMap->PF->Texture.Width ;
				DestFrameBufferHeight = DestShadowMap->PF->Texture.Height ;
			}
			else
			{
				DestFrameBuffer       = SrcImage->Hard.Draw[ 0 ].Tex->PF->FrameBuffer ;
				DestFrameBufferWidth  = SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width ;
				DestFrameBufferHeight = SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height ;
			}

			GetGraphTextureSize( Info->DestGrHandle, &TexWidth, &TexHeight ) ;
			Width  = Info->SrcX2 - Info->SrcX1 ;
			Height = Info->SrcY2 - Info->SrcY1 ;

			SrcRect.left    = Info->SrcX1 ;
			SrcRect.right   = Info->SrcX2 ;
			SrcRect.top     = Info->SrcY2 - 1 ;
			SrcRect.bottom  = Info->SrcY2 ;

			DestRect.left   = Info->DestX ;
			DestRect.right  = Info->DestX + Width ;
			DestRect.top    = Info->DestY + Height ;
			DestRect.bottom = TexHeight ;

			if( DestRect.top != DestRect.bottom )
			{
				Graphics_HTML5_StretchRect(
					SrcTexture,      SrcTextureWidth,      SrcTextureHeight,      &SrcRect,
					DestFrameBuffer, DestFrameBufferWidth, DestFrameBufferHeight, &DestRect
				) ;
			}
		}
	}

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_Down_Scale_PF(  GRAPHFILTER_INFO *Info, int DivNum )
{
	static const char *FlagFileName[ 3 ] =
	{
		"DownScaleX2.flag",
		"DownScaleX4.flag",
		"DownScaleX8.flag",
	} ;
	IMAGEDATA              *SrcImage ;
	int                    UseShader = 0 ;
	int                    UseConstNum = 0 ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 8 ] ;
	int                    TextureW ;
	int                    TextureH ;
	float                  TextureWF ;
	float                  TextureHF ;
	int                    i ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	if( GRAPHCHK( Info->SrcGrHandle, SrcImage ) )
	{
		return -1 ;
	}

	// 使用するシェーダーのセットアップ
	switch( DivNum )
	{
<<<<<<< HEAD
=======
	case 1 :
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	case 2 : UseShader = 0 ; break ;
	case 4 : UseShader = 1 ; break ;
	case 8 : UseShader = 2 ; break ;
	}
	if( GraphFilterShaderHandle.DownScalePS[ UseShader ] < 0 )
	{
		GraphFilterShaderHandle.DownScalePS[ UseShader ] = HTML5_MemLoadShaderCode( FlagFileName[ UseShader ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.DownScalePS[ UseShader ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ UseShader ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.DownScalePS[ UseShader ], &GraphFilterShaderHandle.DownScalePS[ UseShader ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.DownScale[ UseShader ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.DownScale[ UseShader ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.DownScalePS[ UseShader ] ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.DownScale[ UseShader ] ;

	switch( DivNum )
	{
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.DownScale[ UseShader ] ;

	switch( DivNum )
	{
	case 1 :
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	case 2 :
		ParamF4[ 0 ][ 0 ] = 0.0f ; ParamF4[ 0 ][ 1 ] = 0.0f ;
		UseConstNum = 1 ;
		break ;

	case 4 :
		ParamF4[ 0 ][ 0 ] = -1.0f ; ParamF4[ 0 ][ 1 ] = -1.0f ;
		ParamF4[ 0 ][ 2 ] =  1.0f ; ParamF4[ 0 ][ 3 ] = -1.0f ;
		ParamF4[ 1 ][ 0 ] = -1.0f ; ParamF4[ 1 ][ 1 ] =  1.0f ;
		ParamF4[ 1 ][ 2 ] =  1.0f ; ParamF4[ 1 ][ 3 ] =  1.0f ;
		UseConstNum = 4 ;
		break ;

	case 8 :
		ParamF4[ 0 ][ 0 ] = -3.0f ; ParamF4[ 0 ][ 1 ] = -3.0f ;
		ParamF4[ 0 ][ 2 ] = -1.0f ; ParamF4[ 0 ][ 3 ] = -3.0f ;
		ParamF4[ 1 ][ 0 ] =  1.0f ; ParamF4[ 1 ][ 1 ] = -3.0f ;
		ParamF4[ 1 ][ 2 ] =  3.0f ; ParamF4[ 1 ][ 3 ] = -3.0f ;
		ParamF4[ 2 ][ 0 ] = -3.0f ; ParamF4[ 2 ][ 1 ] = -1.0f ;
		ParamF4[ 2 ][ 2 ] = -1.0f ; ParamF4[ 2 ][ 3 ] = -1.0f ;
		ParamF4[ 3 ][ 0 ] =  1.0f ; ParamF4[ 3 ][ 1 ] = -1.0f ;
		ParamF4[ 3 ][ 2 ] =  3.0f ; ParamF4[ 3 ][ 3 ] = -1.0f ;
		ParamF4[ 4 ][ 0 ] = -3.0f ; ParamF4[ 4 ][ 1 ] =  1.0f ;
		ParamF4[ 4 ][ 2 ] = -1.0f ; ParamF4[ 4 ][ 3 ] =  1.0f ;
		ParamF4[ 5 ][ 0 ] =  1.0f ; ParamF4[ 5 ][ 1 ] =  1.0f ;
		ParamF4[ 5 ][ 2 ] =  3.0f ; ParamF4[ 5 ][ 3 ] =  1.0f ;
		ParamF4[ 6 ][ 0 ] = -3.0f ; ParamF4[ 6 ][ 1 ] =  3.0f ;
		ParamF4[ 6 ][ 2 ] = -1.0f ; ParamF4[ 6 ][ 3 ] =  3.0f ;
		ParamF4[ 7 ][ 0 ] =  1.0f ; ParamF4[ 7 ][ 1 ] =  3.0f ;
		ParamF4[ 7 ][ 2 ] =  3.0f ; ParamF4[ 7 ][ 3 ] =  3.0f ;
		UseConstNum = 16 ;
		break ;
	}
	NS_GetGraphTextureSize( Info->SrcGrHandle, &TextureW, &TextureH ) ;
	TextureWF = ( float )TextureW ;
	TextureHF = ( float )TextureH ;
	for( i = 0 ; i < UseConstNum ; i ++ )
	{
		if( i % 2 == 0 )
		{
			ParamF4[ i / 2 ][ 0 ] /= TextureWF ;
			ParamF4[ i / 2 ][ 1 ] /= TextureHF ;
		}
		else
		{
			ParamF4[ i / 2 ][ 2 ] /= TextureWF ;
			ParamF4[ i / 2 ][ 3 ] /= TextureHF ;
		}
	}

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"      ), 0               ) ;
	glUniform4fv(       Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uPixelOffset" ), 8, ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, TRUE, DivNum ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"      ), 0               ) ;
	glUniform4fv(       Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uPixelOffset" ), 8, ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, TRUE, DivNum ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_Bright_Clip_PF( GRAPHFILTER_INFO *Info, int CmpType, float CmpParam, int ClipFillFlag, COLOR_F *ClipFillColor, int IsPMA )
{
	static const char *FlagFileName[ 2 ][ 2 ][ 2 ] =
	{
		{
			{
				"BrightClipLess.flag",
				"BrightClipLess_PMA.flag"
			},
			{
				"BrightClipFillLess.flag",
				"BrightClipFillLess_PMA.flag"
			},
		},
		{
			{
				"BrightClipGreater.flag",
				"BrightClipGreater_PMA.flag"
			},
			{
				"BrightClipFillGreater.flag",
				"BrightClipFillGreater_PMA.flag"
			},
		}
	} ;
	int UseShader = 0 ;
	int UseFill ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 3 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	UseFill = ClipFillFlag == TRUE ? 1 : 0 ;
	switch( CmpType )
	{
	case DX_CMP_GREATER :
		UseShader = 1 ;
		break ;

	case DX_CMP_LESS :
		UseShader = 0 ;
		break ;
	}
	if( GraphFilterShaderHandle.BrightClipPS[ UseShader ][ UseFill ][ IsPMA ] < 0 )
	{
		GraphFilterShaderHandle.BrightClipPS[ UseShader ][ UseFill ][ IsPMA ] = HTML5_MemLoadShaderCode( FlagFileName[ UseShader ][ UseFill ][ IsPMA ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.BrightClipPS[ UseShader ][ UseFill ][ IsPMA ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ UseShader ][ UseFill ][ IsPMA ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.BrightClipPS[ UseShader ][ UseFill ][ IsPMA ], &GraphFilterShaderHandle.BrightClipPS[ UseShader ][ UseFill ][ IsPMA ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.BrightClip[ UseShader ][ UseFill ][ IsPMA ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.BrightClip[ UseShader ][ UseFill ][ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.BrightClipPS[ UseShader ][ UseFill ][ IsPMA ] ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.BrightClip[ UseShader ][ UseFill ][ IsPMA ] ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.BrightClip[ UseShader ][ UseFill ][ IsPMA ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	ParamF4[  0 ][ 0 ] = CmpParam ;
	ParamF4[  0 ][ 1 ] = CmpParam ;
	ParamF4[  0 ][ 2 ] = CmpParam ;
	ParamF4[  0 ][ 3 ] = CmpParam ;
	ParamF4[  1 ][ 0 ] = 0.299f ;
	ParamF4[  1 ][ 1 ] = 0.587f ;
	ParamF4[  1 ][ 2 ] = 0.114f ;
	ParamF4[  1 ][ 3 ] = 0.0f ;
	if( ClipFillColor != NULL )
	{
		ParamF4[  2 ][ 0 ] = ClipFillColor->r ;
		ParamF4[  2 ][ 1 ] = ClipFillColor->g ;
		ParamF4[  2 ][ 2 ] = ClipFillColor->b ;
		ParamF4[  2 ][ 3 ] = ClipFillColor->a ;
	}

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"         ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uClipBrightness" ), ParamF4[ 0 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uRGBToY"         ), ParamF4[ 1 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uClipFillColor"  ), ParamF4[ 2 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"         ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uClipBrightness" ), ParamF4[ 0 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uRGBToY"         ), ParamF4[ 1 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uClipFillColor"  ), ParamF4[ 2 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_Bright_Scale_PF( GRAPHFILTER_INFO *Info, int BrightMin, int BrightMax, int IsPMA )
{
	static const char *FlagFileName[ 2 ] =
	{
		"BrightnessScale.flag",
		"BrightnessScale_PMA.flag",
	} ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 1 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	if( GraphFilterShaderHandle.BrightScalePS[ IsPMA ] < 0 )
	{
		GraphFilterShaderHandle.BrightScalePS[ IsPMA ] = HTML5_MemLoadShaderCode( FlagFileName[ IsPMA ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.BrightScalePS[ IsPMA ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ IsPMA ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.BrightScalePS[ IsPMA ], &GraphFilterShaderHandle.BrightScalePS[ IsPMA ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.BrightScale[ IsPMA ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.BrightScale[ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.BrightScalePS[ IsPMA ] ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.BrightScale[ IsPMA ] ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.BrightScale[ IsPMA ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	ParamF4[  0 ][ 0 ] = BrightMin / 255.0f ;
	ParamF4[  0 ][ 1 ] = 255.0f / ( float )( BrightMax - BrightMin ) ;
	ParamF4[  0 ][ 2 ] = 0.0f ;
	ParamF4[  0 ][ 3 ] = 0.0f ;

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"      ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uMinB_ScaleB" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"      ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uMinB_ScaleB" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_HSB_PF(         GRAPHFILTER_INFO *Info, int HueType, float Hue, float Saturation, float Bright, int IsPMA )
{
	static const char *FlagFileName[ 3 ][ 2 ] =
	{
		{
			"Hsb_HSB_BASE.flag",
			"Hsb_HSB_BASE_PMA.flag"
		},
		{
			"Hsb_HSB_HLOCK.flag",
			"Hsb_HSB_HLOCK_PMA.flag"
		},
	} ;
	int                    UseShader ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 1 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	UseShader = HueType ;
	if( GraphFilterShaderHandle.HsbPS[ UseShader ][ IsPMA ] < 0 )
	{
		GraphFilterShaderHandle.HsbPS[ UseShader ][ IsPMA ] = HTML5_MemLoadShaderCode( FlagFileName[ UseShader ][ IsPMA ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.HsbPS[ UseShader ][ IsPMA ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ UseShader ][ IsPMA ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.HsbPS[ UseShader ][ IsPMA ], &GraphFilterShaderHandle.HsbPS[ UseShader ][ IsPMA ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.Hsb[ UseShader ][ IsPMA ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.Hsb[ UseShader ][ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.HsbPS[ UseShader ][ IsPMA ] ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.Hsb[ UseShader ][ IsPMA ] ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.Hsb[ UseShader ][ IsPMA ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	ParamF4[ 0 ][ 0 ] = Hue ;
	ParamF4[ 0 ][ 1 ] = Saturation > 0.0f ? Saturation * 5.0f : Saturation ;
	ParamF4[ 0 ][ 2 ] = Bright ;
	ParamF4[ 0 ][ 3 ] = 0.0f ;

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex" ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uParam"  ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex" ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uParam"  ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_Invert_PF(      GRAPHFILTER_INFO *Info, int IsPMA )
{
	static const char *FlagFileName[ 2 ] =
	{
		"Invert.flag",
		"Invert_PMA.flag",
	} ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	if( GraphFilterShaderHandle.InvertPS[ IsPMA ] < 0 )
	{
		GraphFilterShaderHandle.InvertPS[ IsPMA ] = HTML5_MemLoadShaderCode( FlagFileName[ IsPMA ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.InvertPS[ IsPMA ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ IsPMA ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.InvertPS[ IsPMA ], &GraphFilterShaderHandle.InvertPS[ IsPMA ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.Invert[ IsPMA ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.Invert[ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.InvertPS[ IsPMA ] ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.Invert[ IsPMA ] ;

	// シェーダーを使用状態にセット
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"      ), 0            ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE ) ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.Invert[ IsPMA ] ;

	// シェーダーを使用状態にセット
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"      ), 0            ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_Level_PF(       GRAPHFILTER_INFO *Info, float Min, float Max, float Gamma, float AfterMin, float AfterMax, int IsPMA )
{
	static const char *FlagFileName[ 2 ] =
	{
		"Level.flag",
		"Level_PMA.flag",
	} ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 1 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	if( GraphFilterShaderHandle.LevelPS[ IsPMA ] < 0 )
	{
		GraphFilterShaderHandle.LevelPS[ IsPMA ] = HTML5_MemLoadShaderCode( FlagFileName[ IsPMA ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.LevelPS[ IsPMA ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ IsPMA ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.LevelPS[ IsPMA ], &GraphFilterShaderHandle.LevelPS[ IsPMA ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.Level[ IsPMA ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.Level[ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.LevelPS[ IsPMA ] ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.Level[ IsPMA ] ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.Level[ IsPMA ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	ParamF4[ 0 ][ 0 ] = Min ;
	ParamF4[ 0 ][ 1 ] = 1.0f / ( Max - Min ) ;
	ParamF4[ 0 ][ 2 ] = AfterMin ;
	ParamF4[ 0 ][ 3 ] = AfterMax ;

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"                       ), 0            ) ;
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uGammaTex"                     ), 1            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uMin_LenRev_AfterMin_AfterMax" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, TRUE, 1, GraphFilterShaderHandle.GammaTex ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"                       ), 0            ) ;
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uGammaTex"                     ), 1            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uMin_LenRev_AfterMin_AfterMax" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, TRUE, 1, GraphFilterShaderHandle.GammaTex ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_TwoColor_PF(    GRAPHFILTER_INFO *Info, float Threshold, COLOR_F *LowColor, COLOR_F *HighColor, int IsPMA )
{
	Threshold /= 255.0f ;

	static const char *FlagFileName[ 2 ] =
	{
		"TwoColor.flag",
		"TwoColor_PMA.flag",
	} ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 3 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	if( GraphFilterShaderHandle.TwoColorPS[ IsPMA ] < 0 )
	{
		GraphFilterShaderHandle.TwoColorPS[ IsPMA ] = HTML5_MemLoadShaderCode( FlagFileName[ IsPMA ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.TwoColorPS[ IsPMA ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ IsPMA ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.TwoColorPS[ IsPMA ], &GraphFilterShaderHandle.TwoColorPS[ IsPMA ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.TwoColor[ IsPMA ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.TwoColor[ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.TwoColorPS[ IsPMA ] ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.TwoColor[ IsPMA ] ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.TwoColor[ IsPMA ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	ParamF4[ 0 ][ 0 ] = 0.29900f ;
	ParamF4[ 0 ][ 1 ] = 0.58700f ;
	ParamF4[ 0 ][ 2 ] = 0.11400f ;
	ParamF4[ 0 ][ 3 ] = Threshold ;
	ParamF4[ 1 ][ 0 ] = LowColor->r ;
	ParamF4[ 1 ][ 1 ] = LowColor->g ;
	ParamF4[ 1 ][ 2 ] = LowColor->b ;
	ParamF4[ 1 ][ 3 ] = LowColor->a ;
	ParamF4[ 2 ][ 0 ] = HighColor->r ;
	ParamF4[ 2 ][ 1 ] = HighColor->g ;
	ParamF4[ 2 ][ 2 ] = HighColor->b ;
	ParamF4[ 2 ][ 3 ] = HighColor->a ;

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"     ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uRGBToY_Cmp" ), ParamF4[ 0 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uLowColor"   ), ParamF4[ 1 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uHighColor"  ), ParamF4[ 2 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"     ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uRGBToY_Cmp" ), ParamF4[ 0 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uLowColor"   ), ParamF4[ 1 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uHighColor"  ), ParamF4[ 2 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_GradientMap_PF( GRAPHFILTER_INFO *Info, int MapGrHandle, int Reverse, int IsPMA )
{
	static const char *FlagFileName[ 2 ][ 2 ] =
	{
		{
			"GradientMap.flag",
			"GradientMap_PMA.flag"
		},
		{
			"GradientMapRev.flag",
			"GradientMapRev_PMA.flag"
		}
	} ;
	int                    UseShader ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 1 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	UseShader = Reverse ? 1 : 0 ;
	if( GraphFilterShaderHandle.GradientMapPS[ UseShader ][ IsPMA ] < 0 )
	{
		GraphFilterShaderHandle.GradientMapPS[ UseShader ][ IsPMA ] = HTML5_MemLoadShaderCode( FlagFileName[ UseShader ][ IsPMA ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.GradientMapPS[ UseShader ][ IsPMA ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ UseShader ][ IsPMA ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.GradientMapPS[ UseShader ][ IsPMA ], &GraphFilterShaderHandle.GradientMapPS[ UseShader ][ IsPMA ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.GradientMap[ UseShader ][ IsPMA ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.GradientMap[ UseShader ][ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.GradientMapPS[ UseShader ][ IsPMA ] ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.GradientMap[ UseShader ][ IsPMA ] ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.GradientMap[ UseShader ][ IsPMA ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	ParamF4[ 0 ][ 0 ] = 0.29900f ;
	ParamF4[ 0 ][ 1 ] = 0.58700f ;
	ParamF4[ 0 ][ 2 ] = 0.11400f ;
	ParamF4[ 0 ][ 3 ] = 0.0f ;

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"     ), 0            ) ;
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uGradMapTex" ), 1            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uRGBToY"     ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE, 1, MapGrHandle ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"     ), 0            ) ;
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uGradMapTex" ), 1            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uRGBToY"     ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE, 1, MapGrHandle ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_Replacement_PF(    GRAPHFILTER_INFO *Info, COLOR_U8 TargetColor, COLOR_U8 NextColor, int IsPMA )
{
<<<<<<< HEAD
 	static const char *FlagFileName[ 2 ] =
 	{
 		"Replacement.flag",
 		"Replacement_PMA.flag",
 	} ;
 	DX_HTML5_SHADER_FLOAT4  ParamF4[ 2 ] ;
 	GRAPHICS_HTML5_SHADER *UseAndrShader ;

  	// 使用するシェーダーのセットアップ
 	if( GraphFilterShaderHandle.ReplacementPS[ IsPMA ] < 0 )
 	{
 		GraphFilterShaderHandle.ReplacementPS[ IsPMA ] = HTML5_MemLoadShaderCode( FlagFileName[ IsPMA ], DX_SHADERTYPE_PIXEL ) ;
 		if( GraphFilterShaderHandle.ReplacementPS[ IsPMA ] < 0 )
 		{
 			char PathUTF16LE[ 128 ] ;

  			ConvString( FlagFileName[ IsPMA ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
 			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
 			return -1 ;
 		}
 		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.ReplacementPS[ IsPMA ], &GraphFilterShaderHandle.ReplacementPS[ IsPMA ] ) ;
 	}
 	if( GraphFilterSystemInfoHTML5.Replacement[ IsPMA ].Shader == 0 )
 	{
 		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.Replacement[ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.ReplacementPS[ IsPMA ] ) ) ;
 	}
 	UseAndrShader = &GraphFilterSystemInfoHTML5.Replacement[ IsPMA ] ;

  	ParamF4[ 0 ][ 0 ] = ( float )TargetColor.r / 255.0f ;
 	ParamF4[ 0 ][ 1 ] = ( float )TargetColor.g / 255.0f ;
 	ParamF4[ 0 ][ 2 ] = ( float )TargetColor.b / 255.0f ;
 	ParamF4[ 0 ][ 3 ] = ( float )TargetColor.a / 255.0f ;
 	ParamF4[ 1 ][ 0 ] = ( float )NextColor.r / 255.0f ;
 	ParamF4[ 1 ][ 1 ] = ( float )NextColor.g / 255.0f ;
 	ParamF4[ 1 ][ 2 ] = ( float )NextColor.b / 255.0f ;
 	ParamF4[ 1 ][ 3 ] = ( float )NextColor.a / 255.0f ;

  	// シェーダーを使用状態にセット
 	glUseProgram( UseAndrShader->Shader ) ;

  	// Uniform の値をセット
 	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"      ), 0            ) ;
 	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uTargetColor" ), ParamF4[ 0 ] ) ;
 	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uNextColor"   ), ParamF4[ 1 ] ) ;

  	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE ) ;

  	// 正常終了
 	return 0 ;
=======
	static const char *FlagFileName[ 2 ] =
	{
		"Replacement.flag",
		"Replacement_PMA.flag",
	} ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 2 ] ;
	GRAPHICS_HTML5_SHADER *UseAndrShader ;

	// 使用するシェーダーのセットアップ
	if( GraphFilterShaderHandle.ReplacementPS[ IsPMA ] < 0 )
	{
		GraphFilterShaderHandle.ReplacementPS[ IsPMA ] = HTML5_MemLoadShaderCode( FlagFileName[ IsPMA ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.ReplacementPS[ IsPMA ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ IsPMA ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.ReplacementPS[ IsPMA ], &GraphFilterShaderHandle.ReplacementPS[ IsPMA ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.Replacement[ IsPMA ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.Replacement[ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.ReplacementPS[ IsPMA ] ) ) ;
	}
	UseAndrShader = &GraphFilterSystemInfoHTML5.Replacement[ IsPMA ] ;

	ParamF4[ 0 ][ 0 ] = ( float )TargetColor.r / 255.0f ;
	ParamF4[ 0 ][ 1 ] = ( float )TargetColor.g / 255.0f ;
	ParamF4[ 0 ][ 2 ] = ( float )TargetColor.b / 255.0f ;
	ParamF4[ 0 ][ 3 ] = ( float )TargetColor.a / 255.0f ;
	ParamF4[ 1 ][ 0 ] = ( float )NextColor.r / 255.0f ;
	ParamF4[ 1 ][ 1 ] = ( float )NextColor.g / 255.0f ;
	ParamF4[ 1 ][ 2 ] = ( float )NextColor.b / 255.0f ;
	ParamF4[ 1 ][ 3 ] = ( float )NextColor.a / 255.0f ;

	// シェーダーを使用状態にセット
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"      ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uTargetColor" ), ParamF4[ 0 ] ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uNextColor"   ), ParamF4[ 1 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE ) ;

	// 正常終了
	return 0 ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
}

extern int	GraphFilter_PremulAlpha_PF( GRAPHFILTER_INFO *Info )
{
	static const char *FlagFileName[ 1 ] =
	{
		"PremultipliedAlpha.flag",
	} ;
	int UseShader ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	UseShader = 0 ;
	if( GraphFilterShaderHandle.PreMulAlphaPS < 0 )
	{
		GraphFilterShaderHandle.PreMulAlphaPS = HTML5_MemLoadShaderCode( FlagFileName[ UseShader ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.PreMulAlphaPS < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ UseShader ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.PreMulAlphaPS, &GraphFilterShaderHandle.PreMulAlphaPS ) ;
	}
	if( GraphFilterSystemInfoHTML5.PreMulAlpha.Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.PreMulAlpha, GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.PreMulAlphaPS ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.PreMulAlpha ;

	// シェーダーを使用状態にセット
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"      ), 0            ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE ) ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.PreMulAlpha ;

	// シェーダーを使用状態にセット
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"      ), 0            ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_InterpAlpha_PF( GRAPHFILTER_INFO *Info )
{
	static const char *FlagFileName[ 1 ] =
	{
		"InterpolatedAlpha.flag",
	} ;
	int UseShader ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	UseShader = 0 ;
	if( GraphFilterShaderHandle.InterpAlphaPS < 0 )
	{
		GraphFilterShaderHandle.InterpAlphaPS = HTML5_MemLoadShaderCode( FlagFileName[ UseShader ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.InterpAlphaPS < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ UseShader ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.InterpAlphaPS, &GraphFilterShaderHandle.InterpAlphaPS ) ;
	}
	if( GraphFilterSystemInfoHTML5.InterpAlpha.Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.InterpAlpha, GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.InterpAlphaPS ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.InterpAlpha ;

	// シェーダーを使用状態にセット
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"      ), 0            ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE ) ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.InterpAlpha ;

	// シェーダーを使用状態にセット
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"      ), 0            ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_YUVtoRGB_PF( GRAPHFILTER_INFO *Info, int UVGrHandle )
{
	static const char *FlagFileName[ 4 ] =
	{
		"Y2uv2ToRgb.flag",
		"Y2uv1ToRgb.flag",

		"Y2uv2ToRgb_RRA.flag",
		"Y2uv1ToRgb_RRA.flag",
	} ;
	int                    UseShader ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 1 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	int RRAFlag = ( Info->FilterOrBlendType == DX_GRAPH_FILTER_YUV_TO_RGB_RRA || Info->FilterOrBlendType == DX_GRAPH_FILTER_Y2UV1_TO_RGB_RRA ) ? TRUE : FALSE ;

	// 使用するシェーダーのセットアップ
	UseShader = ( UVGrHandle < 0 ? 0 : 1 ) + ( RRAFlag ? 2 : 0 ) ;
	if( GraphFilterShaderHandle.YUVtoRGBPS[ UseShader ] < 0 )
	{
		GraphFilterShaderHandle.YUVtoRGBPS[ UseShader ] = HTML5_MemLoadShaderCode( FlagFileName[ UseShader ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.YUVtoRGBPS[ UseShader ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ UseShader ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.YUVtoRGBPS[ UseShader ], &GraphFilterShaderHandle.YUVtoRGBPS[ UseShader ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.YUVtoRGB[ UseShader ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.YUVtoRGB[ UseShader ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRect_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.YUVtoRGBPS[ UseShader ] ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.YUVtoRGB[ UseShader ] ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.YUVtoRGB[ UseShader ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	if( UVGrHandle >= 0 )
	{
		int YImgWidth, YImgHeight ;
		int YTexWidth, YTexHeight ;
		float YU, YV ;
		int UVImgWidth, UVImgHeight ;
		int UVTexWidth, UVTexHeight ;
		float UVU, UVV ;

		NS_GetGraphSize(        Info->SrcGrHandle, &YImgWidth,  &YImgHeight ) ;
		NS_GetGraphTextureSize( Info->SrcGrHandle, &YTexWidth,  &YTexHeight ) ;
		NS_GetGraphSize(        UVGrHandle,        &UVImgWidth, &UVImgHeight  ) ;
		NS_GetGraphTextureSize( UVGrHandle,        &UVTexWidth, &UVTexHeight  ) ;

		YU  = ( float )YImgWidth   / YTexWidth ;
		YV  = ( float )YImgHeight  / YTexHeight ;
		UVU = ( float )UVImgWidth  / UVTexWidth ;
		UVV = ( float )UVImgHeight / UVTexHeight ;

		ParamF4[ 0 ][ 0 ] = UVU / YU ;
		ParamF4[ 0 ][ 1 ] = UVV / YV ;
		ParamF4[ 0 ][ 2 ] = 0.0f ;
		ParamF4[ 0 ][ 3 ] = 0.0f ;
	}

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"                 ), 0            ) ;
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uUVTex"                  ), 1            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uUVTexUVScale_RRA_Add_U" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE, 1, UVGrHandle ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"                 ), 0            ) ;
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uUVTex"                  ), 1            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uUVTexUVScale_RRA_Add_U" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE, 1, UVGrHandle ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_BicubicScale_PF( GRAPHFILTER_INFO *Info, int DestSizeX, int DestSizeY )
{
	static const char *PsoFileName[ 4 ] =
	{
		"Bicubic.flag",
	} ;
	int UseShader ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 1 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	VERTEX_TEX8_2D VertexTex8[ 4 ] ;

	// 使用するシェーダーのセットアップ
	UseShader = 0 ;
	if( GraphFilterShaderHandle.BicubicPS < 0 )
	{
		GraphFilterShaderHandle.BicubicPS = HTML5_MemLoadShaderCode( PsoFileName[ UseShader ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.BicubicPS < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( PsoFileName[ UseShader ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.BicubicPS, &GraphFilterShaderHandle.BicubicPS ) ;
	}
	if( GraphFilterSystemInfoHTML5.Bicubic.Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.Bicubic, GraphicsHardDataHTML5.Device.Shader.Base.StretchRectTex8_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.BicubicPS ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.Bicubic ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.Bicubic ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	int TexW, TexH ;
	NS_GetGraphTextureSize( Info->SrcGrHandle, &TexW, &TexH ) ;

	ParamF4[ 0 ][ 0 ] = ( float )TexW ;
	ParamF4[ 0 ][ 1 ] = ( float )TexH ;
	ParamF4[ 0 ][ 2 ] = 2.0f / ( float )TexW ;
	ParamF4[ 0 ][ 3 ] = 0.0f ;

	float du = 1.0f / TexW ;
	float dv = 1.0f / TexH ;

	VertexTex8[ 0 ].pos.x = 0.0f ;
	VertexTex8[ 0 ].pos.y = 0.0f ;
	VertexTex8[ 0 ].pos.z = 0.2f ;
	VertexTex8[ 0 ].rhw = 1.0f ;
	VertexTex8[ 0 ].u0 = 0.0f - 1.5f * du ;	VertexTex8[ 0 ].v0 = 0.0f - 1.5f * dv ;
	VertexTex8[ 0 ].u1 = 0.0f - 1.5f * du ;	VertexTex8[ 0 ].v1 = 0.0f - 0.5f * dv ;
	VertexTex8[ 0 ].u2 = 0.0f - 1.5f * du ;	VertexTex8[ 0 ].v2 = 0.0f + 0.5f * dv ;
	VertexTex8[ 0 ].u3 = 0.0f - 1.5f * du ;	VertexTex8[ 0 ].v3 = 0.0f + 1.5f * dv ;
	VertexTex8[ 0 ].u4 = 0.0f - 0.5f * du ;	VertexTex8[ 0 ].v4 = 0.0f - 1.5f * dv ;
	VertexTex8[ 0 ].u5 = 0.0f - 0.5f * du ;	VertexTex8[ 0 ].v5 = 0.0f - 0.5f * dv ;
	VertexTex8[ 0 ].u6 = 0.0f - 0.5f * du ;	VertexTex8[ 0 ].v6 = 0.0f + 0.5f * dv ;
	VertexTex8[ 0 ].u7 = 0.0f - 0.5f * du ;	VertexTex8[ 0 ].v7 = 0.0f + 1.5f * dv ;

	VertexTex8[ 1 ].pos.x = ( float )DestSizeX ;
	VertexTex8[ 1 ].pos.y = 0.0f ;
	VertexTex8[ 1 ].pos.z = 0.2f ;
	VertexTex8[ 1 ].rhw = 1.0f ;
	VertexTex8[ 1 ].u0 = 1.0f - 1.5f * du ;	VertexTex8[ 1 ].v0 = 0.0f - 1.5f * dv ;
	VertexTex8[ 1 ].u1 = 1.0f - 1.5f * du ;	VertexTex8[ 1 ].v1 = 0.0f - 0.5f * dv ;
	VertexTex8[ 1 ].u2 = 1.0f - 1.5f * du ;	VertexTex8[ 1 ].v2 = 0.0f + 0.5f * dv ;
	VertexTex8[ 1 ].u3 = 1.0f - 1.5f * du ;	VertexTex8[ 1 ].v3 = 0.0f + 1.5f * dv ;
	VertexTex8[ 1 ].u4 = 1.0f - 0.5f * du ;	VertexTex8[ 1 ].v4 = 0.0f - 1.5f * dv ;
	VertexTex8[ 1 ].u5 = 1.0f - 0.5f * du ;	VertexTex8[ 1 ].v5 = 0.0f - 0.5f * dv ;
	VertexTex8[ 1 ].u6 = 1.0f - 0.5f * du ;	VertexTex8[ 1 ].v6 = 0.0f + 0.5f * dv ;
	VertexTex8[ 1 ].u7 = 1.0f - 0.5f * du ;	VertexTex8[ 1 ].v7 = 0.0f + 1.5f * dv ;

	VertexTex8[ 2 ].pos.x = 0.0f ;
	VertexTex8[ 2 ].pos.y = ( float )DestSizeY ;
	VertexTex8[ 2 ].pos.z = 0.2f ;
	VertexTex8[ 2 ].rhw = 1.0f ;
	VertexTex8[ 2 ].u0 = 0.0f - 1.5f * du ;	VertexTex8[ 2 ].v0 = 1.0f - 1.5f * dv ;
	VertexTex8[ 2 ].u1 = 0.0f - 1.5f * du ;	VertexTex8[ 2 ].v1 = 1.0f - 0.5f * dv ;
	VertexTex8[ 2 ].u2 = 0.0f - 1.5f * du ;	VertexTex8[ 2 ].v2 = 1.0f + 0.5f * dv ;
	VertexTex8[ 2 ].u3 = 0.0f - 1.5f * du ;	VertexTex8[ 2 ].v3 = 1.0f + 1.5f * dv ;
	VertexTex8[ 2 ].u4 = 0.0f - 0.5f * du ;	VertexTex8[ 2 ].v4 = 1.0f - 1.5f * dv ;
	VertexTex8[ 2 ].u5 = 0.0f - 0.5f * du ;	VertexTex8[ 2 ].v5 = 1.0f - 0.5f * dv ;
	VertexTex8[ 2 ].u6 = 0.0f - 0.5f * du ;	VertexTex8[ 2 ].v6 = 1.0f + 0.5f * dv ;
	VertexTex8[ 2 ].u7 = 0.0f - 0.5f * du ;	VertexTex8[ 2 ].v7 = 1.0f + 1.5f * dv ;

	VertexTex8[ 3 ].pos.x = ( float )DestSizeX ;
	VertexTex8[ 3 ].pos.y = ( float )DestSizeY ;
	VertexTex8[ 3 ].pos.z = 0.2f ;
	VertexTex8[ 3 ].rhw = 1.0f ;
	VertexTex8[ 3 ].u0 = 1.0f - 1.5f * du ;	VertexTex8[ 3 ].v0 = 1.0f - 1.5f * dv ;
	VertexTex8[ 3 ].u1 = 1.0f - 1.5f * du ;	VertexTex8[ 3 ].v1 = 1.0f - 0.5f * dv ;
	VertexTex8[ 3 ].u2 = 1.0f - 1.5f * du ;	VertexTex8[ 3 ].v2 = 1.0f + 0.5f * dv ;
	VertexTex8[ 3 ].u3 = 1.0f - 1.5f * du ;	VertexTex8[ 3 ].v3 = 1.0f + 1.5f * dv ;
	VertexTex8[ 3 ].u4 = 1.0f - 0.5f * du ;	VertexTex8[ 3 ].v4 = 1.0f - 1.5f * dv ;
	VertexTex8[ 3 ].u5 = 1.0f - 0.5f * du ;	VertexTex8[ 3 ].v5 = 1.0f - 0.5f * dv ;
	VertexTex8[ 3 ].u6 = 1.0f - 0.5f * du ;	VertexTex8[ 3 ].v6 = 1.0f + 0.5f * dv ;
	VertexTex8[ 3 ].u7 = 1.0f - 0.5f * du ;	VertexTex8[ 3 ].v7 = 1.0f + 1.5f * dv ;

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"           ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uTexSize_X2PixelU" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE, 1, -1, VertexTex8 ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"           ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uTexSize_X2PixelU" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE, 1, -1, VertexTex8 ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_Lanczos3Scale_PF( GRAPHFILTER_INFO *Info, int DestSizeX, int DestSizeY )
{
	static const char *PsoFileName[ 4 ] =
	{
		"Lanczos3.flag",
	} ;
	int UseShader ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 1 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	VERTEX_TEX8_2D VertexTex8[ 4 ] ;

	// 使用するシェーダーのセットアップ
	UseShader = 0 ;
	if( GraphFilterShaderHandle.Lanczos3PS < 0 )
	{
		GraphFilterShaderHandle.Lanczos3PS = HTML5_MemLoadShaderCode( PsoFileName[ UseShader ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.Lanczos3PS < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( PsoFileName[ UseShader ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.Lanczos3PS, &GraphFilterShaderHandle.Lanczos3PS ) ;
	}
	if( GraphFilterSystemInfoHTML5.Lanczos3.Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.Lanczos3, GraphicsHardDataHTML5.Device.Shader.Base.StretchRectTex8_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.Lanczos3PS ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.Lanczos3 ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.Lanczos3 ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	int TexW, TexH ;
	NS_GetGraphTextureSize( Info->SrcGrHandle, &TexW, &TexH ) ;

	ParamF4[ 0 ][ 0 ] = ( float )TexW ;
	ParamF4[ 0 ][ 1 ] = ( float )TexH ;
	ParamF4[ 0 ][ 2 ] = 1.0f / ( float )TexW ;
	ParamF4[ 0 ][ 3 ] = 0.0f ;

	float du = 1.0f / TexW ;
	float dv = 1.0f / TexH ;

	VertexTex8[ 0 ].pos.x = 0.0f ;
	VertexTex8[ 0 ].pos.y = 0.0f ;
	VertexTex8[ 0 ].pos.z = 0.0f ;
	VertexTex8[ 0 ].rhw = 1.0f ;
	VertexTex8[ 0 ].u0 = 0.0f - 0.5f * du ;	VertexTex8[ 0 ].v0 = 0.0f - 2.5f * dv ;
	VertexTex8[ 0 ].u1 = 0.0f - 0.5f * du ;	VertexTex8[ 0 ].v1 = 0.0f - 1.5f * dv ;
	VertexTex8[ 0 ].u2 = 0.0f - 0.5f * du ;	VertexTex8[ 0 ].v2 = 0.0f - 0.5f * dv ;
	VertexTex8[ 0 ].u3 = 0.0f - 0.5f * du ;	VertexTex8[ 0 ].v3 = 0.0f + 0.5f * dv ;
	VertexTex8[ 0 ].u4 = 0.0f - 0.5f * du ;	VertexTex8[ 0 ].v4 = 0.0f + 1.5f * dv ;
	VertexTex8[ 0 ].u5 = 0.0f - 0.5f * du ;	VertexTex8[ 0 ].v5 = 0.0f + 2.5f * dv ;

	VertexTex8[ 1 ].pos.x = ( float )DestSizeX ;
	VertexTex8[ 1 ].pos.y = 0.0f ;
	VertexTex8[ 1 ].pos.z = 0.0f ;
	VertexTex8[ 1 ].rhw = 1.0f ;
	VertexTex8[ 1 ].u0 = 1.0f - 0.5f * du ;	VertexTex8[ 1 ].v0 = 0.0f - 2.5f * dv ;
	VertexTex8[ 1 ].u1 = 1.0f - 0.5f * du ;	VertexTex8[ 1 ].v1 = 0.0f - 1.5f * dv ;
	VertexTex8[ 1 ].u2 = 1.0f - 0.5f * du ;	VertexTex8[ 1 ].v2 = 0.0f - 0.5f * dv ;
	VertexTex8[ 1 ].u3 = 1.0f - 0.5f * du ;	VertexTex8[ 1 ].v3 = 0.0f + 0.5f * dv ;
	VertexTex8[ 1 ].u4 = 1.0f - 0.5f * du ;	VertexTex8[ 1 ].v4 = 0.0f + 1.5f * dv ;
	VertexTex8[ 1 ].u5 = 1.0f - 0.5f * du ;	VertexTex8[ 1 ].v5 = 0.0f + 2.5f * dv ;

	VertexTex8[ 2 ].pos.x = 0.0f ;
	VertexTex8[ 2 ].pos.y = ( float )DestSizeY ;
	VertexTex8[ 2 ].pos.z = 0.0f ;
	VertexTex8[ 2 ].rhw = 1.0f ;
	VertexTex8[ 2 ].u0 = 0.0f - 0.5f * du ;	VertexTex8[ 2 ].v0 = 1.0f - 2.5f * dv ;
	VertexTex8[ 2 ].u1 = 0.0f - 0.5f * du ;	VertexTex8[ 2 ].v1 = 1.0f - 1.5f * dv ;
	VertexTex8[ 2 ].u2 = 0.0f - 0.5f * du ;	VertexTex8[ 2 ].v2 = 1.0f - 0.5f * dv ;
	VertexTex8[ 2 ].u3 = 0.0f - 0.5f * du ;	VertexTex8[ 2 ].v3 = 1.0f + 0.5f * dv ;
	VertexTex8[ 2 ].u4 = 0.0f - 0.5f * du ;	VertexTex8[ 2 ].v4 = 1.0f + 1.5f * dv ;
	VertexTex8[ 2 ].u5 = 0.0f - 0.5f * du ;	VertexTex8[ 2 ].v5 = 1.0f + 2.5f * dv ;

	VertexTex8[ 3 ].pos.x = ( float )DestSizeX ;
	VertexTex8[ 3 ].pos.y = ( float )DestSizeY ;
	VertexTex8[ 3 ].pos.z = 0.0f ;
	VertexTex8[ 3 ].rhw = 1.0f ;
	VertexTex8[ 3 ].u0 = 1.0f - 0.5f * du ;	VertexTex8[ 3 ].v0 = 1.0f - 2.5f * dv ;
	VertexTex8[ 3 ].u1 = 1.0f - 0.5f * du ;	VertexTex8[ 3 ].v1 = 1.0f - 1.5f * dv ;
	VertexTex8[ 3 ].u2 = 1.0f - 0.5f * du ;	VertexTex8[ 3 ].v2 = 1.0f - 0.5f * dv ;
	VertexTex8[ 3 ].u3 = 1.0f - 0.5f * du ;	VertexTex8[ 3 ].v3 = 1.0f + 0.5f * dv ;
	VertexTex8[ 3 ].u4 = 1.0f - 0.5f * du ;	VertexTex8[ 3 ].v4 = 1.0f + 1.5f * dv ;
	VertexTex8[ 3 ].u5 = 1.0f - 0.5f * du ;	VertexTex8[ 3 ].v5 = 1.0f + 2.5f * dv ;

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"           ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uTexSize_X1PixelU" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, FALSE, 1, -1, VertexTex8 ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"           ), 0            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uTexSize_X1PixelU" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, FALSE, 1, -1, VertexTex8 ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphFilter_SSAO_PF( GRAPHFILTER_INFO *Info, int DepthMapGrHandle, float KernelRadius, float MinDistance, float MaxDistance, float Strength, int OcclusionColor, float OcclusionPower, int ColorMapGrHandle )
{
	return 0 ;
}

extern int GraphFilter_FloatColorScale_PF( GRAPHFILTER_INFO *Info, COLOR_F ColorScale, COLOR_F ColorPreSub )
{
	return 0 ;
}

extern int GraphFilter_RectBltBase_Timing0_PF( GRAPHFILTER_INFO *Info, GRAPHFILTER_PARAM *Param )
{
	Info->PassNum = -1 ;
	if( Info->IsBlend )
	{
		// パスの数を取得
		Info->PassNum = 1 ;

		// 作業用テクスチャを使用するかどうかを取得
		Info->UseWorkScreen = FALSE ;
	}
	else
	{
		// ガウスフィルタのみ２パス
		if( Info->FilterOrBlendType == DX_GRAPH_FILTER_GAUSS )
		{
			Info->UseWorkScreen = TRUE ;
			Info->PassNum = 2 ;
		}
		else
		{
			Info->UseWorkScreen = FALSE ;
			Info->PassNum = 1 ;
		}
	}

	if( Info->SrcX1 != Info->DestX ||
		Info->SrcY1 != Info->DestY  )
	{
		Info->UseWorkScreen = 1 ;
	}

	return 0 ;
}

extern int GraphFilter_RectBltBase_Timing1_PF( void )
{
	// 正常終了
	return 0 ;
}

extern int GraphFilter_DestGraphSetup_PF( GRAPHFILTER_INFO *Info, int *UseSrcGrHandle, int *UseDestGrHandle )
{
	SHADOWMAPDATA *SrcShadowMap  = NULL ;
	SHADOWMAPDATA *DestShadowMap = NULL ;
	IMAGEDATA     *SrcImage      = NULL ;
	IMAGEDATA     *DestImage     = NULL ;
	IMAGEDATA     *TempSrcImage  = NULL ;
	int TexSizeW ;
	int TexSizeH ;
	int SrcTexFloatType ;
	int DestTexFloatType ;
	int SrcEqDestOrDestNonDrawValidHandle ;
	int AlwaysUseDestWorkHandle ;
	int UseDestWorkHandleIndex ;
	int UseSrcWorkHandleIndex ;
	int SrcGraphDivFlag ;

	if( !GRAPHCHK( Info->SrcGrHandle, SrcImage ) )
	{
		SrcTexFloatType = SrcImage->Orig->FormatDesc.FloatTypeFlag ;
	}
	else
	if( !SHADOWMAPCHK( Info->SrcGrHandle, SrcShadowMap ) )
	{
		SrcTexFloatType = SrcShadowMap->TexFormat_Float ;
	}
	else
	{
		return -1 ;
	}

	if( !GRAPHCHK( Info->DestGrHandle, DestImage ) )
	{
		DestTexFloatType = DestImage->Orig->FormatDesc.FloatTypeFlag ;
	}
	else
	if( !SHADOWMAPCHK( Info->DestGrHandle, DestShadowMap ) )
	{
		DestTexFloatType = DestShadowMap->TexFormat_Float ;
	}
	else
	{
		return -1 ;
	}

	UseSrcWorkHandleIndex = 0 ;

	if( SrcShadowMap == NULL &&
		( ( /*Info->UseWorkScreen == 1 &&*/ Info->SrcGrHandle == Info->DestGrHandle ) ||
		  DestImage->Orig->FormatDesc.DrawValidFlag == FALSE ) )
	{
		SrcEqDestOrDestNonDrawValidHandle = TRUE ;
	}
	else
	{
		SrcEqDestOrDestNonDrawValidHandle = FALSE ;
	}

	if( Info->UseWorkScreen == 1 &&
		( ( Info->Pass % 2 == 0 && Info->PassNum % 2 == 0 ) ||
		  ( Info->Pass % 2 == 1 && Info->PassNum % 2 == 1 ) ) )
	{
		AlwaysUseDestWorkHandle = TRUE ;
	}
	else
	{
		AlwaysUseDestWorkHandle = FALSE ;
	}

	if(
		SrcShadowMap == NULL &&
		Info->Pass == 0 &&
		(
		  SrcImage->Hard.DrawNum != 1 ||
		  SrcImage->Hard.Draw[ 0 ].UsePosXI != 0 ||
		  SrcImage->Hard.Draw[ 0 ].UsePosYI != 0
		)
	  )
	{
		SrcGraphDivFlag = TRUE ;
	}
	else
	{
		SrcGraphDivFlag = FALSE ;
	}

	if( SrcEqDestOrDestNonDrawValidHandle || AlwaysUseDestWorkHandle )
	{
		if( AlwaysUseDestWorkHandle == FALSE && SrcEqDestOrDestNonDrawValidHandle == TRUE )
		{
			UseDestWorkHandleIndex = 1 ;
			UseSrcWorkHandleIndex  = 0 ;
		}
		else
		{
			UseDestWorkHandleIndex = 0 ;
			UseSrcWorkHandleIndex  = 1 ;
		}

		if( SrcGraphDivFlag )
		{
			TexSizeW = SrcImage->WidthI ;
			TexSizeH = SrcImage->HeightI ;
		}
		else
		{
			NS_GetGraphTextureSize( Info->SrcGrHandle, &TexSizeW, &TexSizeH ) ;
		}

		*UseDestGrHandle = HTML5_GraphFilter_GetWorkTexture( DestTexFloatType, ( DWORD )TexSizeW, ( DWORD )TexSizeH, ( DWORD )UseDestWorkHandleIndex ) ;
		if( *UseDestGrHandle < 0 )
		{
			return -1 ;
		}
	}
	else
	{
		*UseDestGrHandle = Info->DestGrHandle ;
	}

	if( SrcGraphDivFlag )
	{
		RECT DestRect ;
		RECT SrcRect ;
		int i ;

		TexSizeW = SrcImage->WidthI ;
		TexSizeH = SrcImage->HeightI ;

		*UseSrcGrHandle = HTML5_GraphFilter_GetWorkTexture( SrcTexFloatType, ( DWORD )TexSizeW, ( DWORD )TexSizeH, ( DWORD )UseSrcWorkHandleIndex ) ;
		if( *UseSrcGrHandle < 0 )
		{
			return -1 ;
		}

		GRAPHCHK( *UseSrcGrHandle, TempSrcImage ) ;

		for( i = 0 ; i < SrcImage->Hard.DrawNum ; i ++ )
		{
			SrcRect.left    = SrcImage->Hard.Draw[ i ].UsePosXI ;
			SrcRect.top     = SrcImage->Hard.Draw[ i ].UsePosYI ;
			SrcRect.right   = SrcImage->Hard.Draw[ i ].UsePosXI  + SrcImage->Hard.Draw[ i ].WidthI ;
			SrcRect.bottom  = SrcImage->Hard.Draw[ i ].UsePosYI  + SrcImage->Hard.Draw[ i ].HeightI ;

			DestRect.left   = SrcImage->Hard.Draw[ i ].DrawPosXI ;
			DestRect.top    = SrcImage->Hard.Draw[ i ].DrawPosYI ;
			DestRect.right  = SrcImage->Hard.Draw[ i ].DrawPosXI + SrcImage->Hard.Draw[ i ].WidthI ;
			DestRect.bottom = SrcImage->Hard.Draw[ i ].DrawPosYI + SrcImage->Hard.Draw[ i ].HeightI ;

			Graphics_HTML5_StretchRect(
				SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.TextureBuffer,
				SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width,
				SrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height,
				&SrcRect,

				TempSrcImage->Hard.Draw[ 0 ].Tex->PF->FrameBuffer,
				TempSrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width,
				TempSrcImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height,
				&DestRect,

				GL_NEAREST
			) ;
		}
	}

	return 0 ;
}

extern int GraphFilter_DestGraphUpdate_PF( GRAPHFILTER_INFO *Info, int UseDestGrHandle, int FilterResult )
{
	if( FilterResult >= 0 )
	{
		if( ( Info->UseWorkScreen == 1 && Info->SrcGrHandle == Info->DestGrHandle ) ||
			UseDestGrHandle != Info->DestGrHandle )
		{
			Graphics_Image_GetDrawScreenGraphBase(
				UseDestGrHandle,
				0,
				0,
				Info->DestX,
				Info->DestY,
				Info->DestX + ( Info->SrcX2 - Info->SrcX1 ) / Info->SrcDivNum,
				Info->DestY + ( Info->SrcY2 - Info->SrcY1 ) / Info->SrcDivNum,
				Info->DestX,
				Info->DestY,
				Info->DestGrHandle
			) ;
		}
	}

	// 正常終了
	return 0 ;
}



extern int	GraphBlend_Basic_PF(           GRAPHFILTER_INFO *Info, int IsPMA )
{
	static const char *FlagFileName[ DX_GRAPH_BLEND_NUM ] =
	{
		"BasBF_Normal.flag",				// DX_GRAPH_BLEND_NORMAL
		NULL,								// DX_GRAPH_BLEND_RGBA_SELECT_MIX
		"BasBF_Multiple.flag",				// DX_GRAPH_BLEND_MULTIPLE
		"BasBF_Difference.flag",			// DX_GRAPH_BLEND_DIFFERENCE
		"BasBF_Add.flag",					// DX_GRAPH_BLEND_ADD
		"BasBF_Screen.flag",				// DX_GRAPH_BLEND_SCREEN
		"BasBF_Overlay.flag",				// DX_GRAPH_BLEND_OVERLAY
		"BasBF_Dodge.flag",					// DX_GRAPH_BLEND_DODGE
		"BasBF_Burn.flag",					// DX_GRAPH_BLEND_BURN
		"BasBF_Darken.flag",				// DX_GRAPH_BLEND_DARKEN
		"BasBF_Lighten.flag",				// DX_GRAPH_BLEND_LIGHTEN
		"BasBF_SoftLight.flag",				// DX_GRAPH_BLEND_SOFTLIGHT
		"BasBF_HardLight.flag",				// DX_GRAPH_BLEND_HARDLIGHT
		"BasBF_Exclusion.flag",				// DX_GRAPH_BLEND_EXCLUSION
		"BasBF_Normal_AlphaCh.flag",		// DX_GRAPH_BLEND_NORMAL_ALPHACH
		"BasBF_Add_AlphaCh.flag",			// DX_GRAPH_BLEND_ADD_ALPHACH
		"BasBF_Multiple_AOnly.flag",		// DX_GRAPH_BLEND_MULTIPLE_A_ONLY
		"BasBF_Normal_PMA.flag",			// DX_GRAPH_BLEND_PMA_NORMAL
		NULL,								// DX_GRAPH_BLEND_PMA_RGBA_SELECT_MIX
		"BasBF_Multiple_PMA.flag",			// DX_GRAPH_BLEND_PMA_MULTIPLE
		"BasBF_Difference_PMA.flag",		// DX_GRAPH_BLEND_PMA_DIFFERENCE
		"BasBF_Add_PMA.flag",				// DX_GRAPH_BLEND_PMA_ADD
		"BasBF_Screen_PMA.flag",			// DX_GRAPH_BLEND_PMA_SCREEN
		"BasBF_Overlay_PMA.flag",			// DX_GRAPH_BLEND_PMA_OVERLAY
		"BasBF_Dodge_PMA.flag",				// DX_GRAPH_BLEND_PMA_DODGE
		"BasBF_Burn_PMA.flag",				// DX_GRAPH_BLEND_PMA_BURN
		"BasBF_Darken_PMA.flag",			// DX_GRAPH_BLEND_PMA_DARKEN
		"BasBF_Lighten_PMA.flag",			// DX_GRAPH_BLEND_PMA_LIGHTEN
		"BasBF_SoftLight_PMA.flag",			// DX_GRAPH_BLEND_PMA_SOFTLIGHT
		"BasBF_HardLight_PMA.flag",			// DX_GRAPH_BLEND_PMA_HARDLIGHT
		"BasBF_Exclusion_PMA.flag",			// DX_GRAPH_BLEND_PMA_EXCLUSION
		"BasBF_Normal_AlphaCh_PMA.flag",	// DX_GRAPH_BLEND_PMA_NORMAL_ALPHACH
		"BasBF_Add_AlphaCh_PMA.flag",		// DX_GRAPH_BLEND_PMA_ADD_ALPHACH
		"BasBF_Multiple_AOnly_PMA.flag",	// DX_GRAPH_BLEND_PMA_MULTIPLE_A_ONLY
<<<<<<< HEAD
	} ;
	int                    UseShader ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 1 ] ;
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
		"BasBF_Mask.flag",					// DX_GRAPH_BLEND_MASK
		"BasBF_Mask_PMA.flag",				// DX_GRAPH_BLEND_PMA_MASK
	} ;
	int                    UseShader ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 1 ] ;
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 使用するシェーダーのセットアップ
	UseShader = Info->FilterOrBlendType ;
	if( GraphFilterShaderHandle.BasicBlendPS[ UseShader ] < 0 )
	{
		GraphFilterShaderHandle.BasicBlendPS[ UseShader ] = HTML5_MemLoadShaderCode( FlagFileName[ UseShader ], DX_SHADERTYPE_PIXEL ) ;
		if( GraphFilterShaderHandle.BasicBlendPS[ UseShader ] < 0 )
		{
			char PathUTF16LE[ 128 ] ;

			ConvString( FlagFileName[ UseShader ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
			return -1 ;
		}
		NS_SetDeleteHandleFlag( GraphFilterShaderHandle.BasicBlendPS[ UseShader ], &GraphFilterShaderHandle.BasicBlendPS[ UseShader ] ) ;
	}
	if( GraphFilterSystemInfoHTML5.BasicBlend[ UseShader ].Shader == 0 )
	{
		Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.BasicBlend[ UseShader ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRectTex2_VS, HTML5_GetFragmentShader( GraphFilterShaderHandle.BasicBlendPS[ UseShader ] ) ) ;
	}
<<<<<<< HEAD
	UseHTML5Shader = &GraphFilterSystemInfoHTML5.BasicBlend[ UseShader ] ;
=======
	UseAndrShader = &GraphFilterSystemInfoHTML5.BasicBlend[ UseShader ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	
	ParamF4[ 0 ][ 0 ] = Info->BlendRatio ;
	ParamF4[ 0 ][ 1 ] = Info->BlendRatio ;
	ParamF4[ 0 ][ 2 ] = Info->BlendRatio ;
	ParamF4[ 0 ][ 3 ] = Info->BlendRatio ;

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"     ), 0            ) ;
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uBlendTex"   ), 1            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uBlendRatio" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, Info->BlendGraphScalingFilterIsBilinear ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"     ), 0            ) ;
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uBlendTex"   ), 1            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uBlendRatio" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, Info->BlendGraphScalingFilterIsBilinear ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	// 正常終了
	return 0 ;
}

extern int	GraphBlend_RGBA_Select_Mix_PF( GRAPHFILTER_INFO *Info, int SelectR, int SelectG, int SelectB, int SelectA, int IsPMA )
{
	static const char *FlagFileName[ 2 ] =
	{
		"RGBAMix_Base.flag",
		"RGBAMix_Base_PMA.flag",
	} ;
	static const char *CharTable[ 4 ] =
	{
		"R", "G", "B", "A"
	};
	int                    *PixelShaderHandle ;
	DX_HTML5_SHADER_FLOAT4  ParamF4[ 1 ] ;
<<<<<<< HEAD
	GRAPHICS_HTML5_SHADER *UseHTML5Shader ;
=======
	GRAPHICS_HTML5_SHADER *UseAndrShader ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	char                   FileName[ 64 ] ;
	int                    SrcBlendReverse = FALSE ;
	int                    HandleTemp ;
	int                    SrcOnlyFlag = FALSE ;
	char                   PathUTF16LE[ 64 ] ;

	// 使用するシェーダーのセットアップ
	if( ( SelectR >= DX_RGBA_SELECT_SRC_INV_R && SelectR <= DX_RGBA_SELECT_BLEND_INV_A ) ||
<<<<<<< HEAD
 		( SelectG >= DX_RGBA_SELECT_SRC_INV_R && SelectG <= DX_RGBA_SELECT_BLEND_INV_A ) ||
 		( SelectB >= DX_RGBA_SELECT_SRC_INV_R && SelectB <= DX_RGBA_SELECT_BLEND_INV_A ) ||
 		( SelectA >= DX_RGBA_SELECT_SRC_INV_R && SelectA <= DX_RGBA_SELECT_BLEND_INV_A ) )
 	{
 		goto USE_BASE_SHADER ;
 	}
=======
		( SelectG >= DX_RGBA_SELECT_SRC_INV_R && SelectG <= DX_RGBA_SELECT_BLEND_INV_A ) ||
		( SelectB >= DX_RGBA_SELECT_SRC_INV_R && SelectB <= DX_RGBA_SELECT_BLEND_INV_A ) ||
		( SelectA >= DX_RGBA_SELECT_SRC_INV_R && SelectA <= DX_RGBA_SELECT_BLEND_INV_A ) ||
		Info->BlendImage->WidthI  != Info->SrcImage->WidthI  ||
		Info->BlendImage->HeightI != Info->SrcImage->HeightI ||
		( Info->BlendPosEnable  && ( Info->BlendX  != Info->SrcX1 || Info->BlendY  != Info->SrcY1 ) ) || 
		( Info->BlendPos2Enable && ( Info->BlendX2 != Info->SrcX2 || Info->BlendY2 != Info->SrcY2 ) ) )
	{
		goto USE_BASE_SHADER ;
	}
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	if( SelectR >= DX_RGBA_SELECT_SRC_R && SelectR <= DX_RGBA_SELECT_SRC_A &&
		SelectG >= DX_RGBA_SELECT_SRC_R && SelectG <= DX_RGBA_SELECT_SRC_A &&
		SelectB >= DX_RGBA_SELECT_SRC_R && SelectB <= DX_RGBA_SELECT_SRC_A &&
		SelectA >= DX_RGBA_SELECT_SRC_R && SelectA <= DX_RGBA_SELECT_SRC_A )
	{
		SrcOnlyFlag = TRUE ;
	}
	else
	if( SelectR >= DX_RGBA_SELECT_BLEND_R && SelectR <= DX_RGBA_SELECT_BLEND_A &&
		SelectG >= DX_RGBA_SELECT_BLEND_R && SelectG <= DX_RGBA_SELECT_BLEND_A &&
		SelectB >= DX_RGBA_SELECT_BLEND_R && SelectB <= DX_RGBA_SELECT_BLEND_A &&
		SelectA >= DX_RGBA_SELECT_BLEND_R && SelectA <= DX_RGBA_SELECT_BLEND_A )
	{
		SelectR -= DX_RGBA_SELECT_BLEND_R ;
		SelectG -= DX_RGBA_SELECT_BLEND_R ;
		SelectB -= DX_RGBA_SELECT_BLEND_R ;
		SelectA -= DX_RGBA_SELECT_BLEND_R ;

		SrcOnlyFlag     = TRUE ;
		SrcBlendReverse = TRUE ;

		HandleTemp          = Info->BlendGrHandle ;
		Info->BlendGrHandle = Info->SrcGrHandle ;
		Info->SrcGrHandle   = HandleTemp ;
	}

	if( SrcOnlyFlag )
	{
		PixelShaderHandle = &GraphFilterShaderHandle.RgbaMixS[ SelectR ][ SelectG ][ SelectB ][ SelectA ][ IsPMA ] ;
		if( *PixelShaderHandle < 0 )
		{
			if( GHTML5.ShaderCode.Base.RGBAMixS_ShaderPackImage != NULL )
			{
				*PixelShaderHandle = NS_LoadPixelShaderFromMem( GHTML5.ShaderCode.Base.RGBAMixS_FS_Code[ SelectR ][ SelectG ][ SelectB ][ SelectA ][ IsPMA ].Binary, GHTML5.ShaderCode.Base.RGBAMixS_FS_Code[ SelectR ][ SelectG ][ SelectB ][ SelectA ][ IsPMA ].Size ) ;
				if( *PixelShaderHandle < 0 )
				{
					DXST_LOGFILEFMT_ADDUTF16LE(( "\x52\x00\x47\x00\x42\x00\x41\x00\x4d\x00\x69\x00\x78\x00\x53\x00\x20\x00\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x00"/*@ L"RGBAMixS フィルター用シェーダーの作成に失敗しました" @*/ )) ;
					return -1 ;
				}
				NS_SetDeleteHandleFlag( *PixelShaderHandle, PixelShaderHandle ) ;
			}
		}
		if( GraphFilterSystemInfoHTML5.RgbaMixS[ SelectR ][ SelectG ][ SelectB ][ SelectA ][ IsPMA ].Shader == 0 )
		{
			Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.RgbaMixS[ SelectR ][ SelectG ][ SelectB ][ SelectA ][ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRectTex2_VS, HTML5_GetFragmentShader( *PixelShaderHandle ) ) ;
		}
<<<<<<< HEAD
		UseHTML5Shader = &GraphFilterSystemInfoHTML5.RgbaMixS[ SelectR ][ SelectG ][ SelectB ][ SelectA ][ IsPMA ] ;
=======
		UseAndrShader = &GraphFilterSystemInfoHTML5.RgbaMixS[ SelectR ][ SelectG ][ SelectB ][ SelectA ][ IsPMA ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	}
	else
	if( SelectR == SelectG && SelectR == SelectB && SelectR != DX_RGBA_SELECT_BLEND_A && SelectR != DX_RGBA_SELECT_SRC_A )
	{
		if( SelectR >= DX_RGBA_SELECT_BLEND_R && SelectR <= DX_RGBA_SELECT_BLEND_A )
		{
			SelectR -= DX_RGBA_SELECT_BLEND_R ;
			SelectG -= DX_RGBA_SELECT_BLEND_R ;
			SelectB -= DX_RGBA_SELECT_BLEND_R ;
			SelectA += DX_RGBA_SELECT_BLEND_R ;

			SrcBlendReverse = TRUE ;

			HandleTemp          = Info->BlendGrHandle ;
			Info->BlendGrHandle = Info->SrcGrHandle ;
			Info->SrcGrHandle   = HandleTemp ;
		}

		PixelShaderHandle = &GraphFilterShaderHandle.RgbaMixSRRRB[ SelectR ][ SelectA - DX_RGBA_SELECT_BLEND_R ][ IsPMA ] ;
		if( *PixelShaderHandle < 0 )
		{
			_SNPRINTF( FileName, sizeof( FileName ), "RGBAMix_S%sS%sS%sB%s%s.flag", CharTable[ SelectR ], CharTable[ SelectG ], CharTable[ SelectB ], CharTable[ SelectA - DX_RGBA_SELECT_BLEND_R ], IsPMA ? "_PMA" : "" ) ;
			*PixelShaderHandle = HTML5_MemLoadShaderCode( FileName, DX_SHADERTYPE_PIXEL ) ;
			if( *PixelShaderHandle < 0 )
			{
				ConvString( FileName, -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x52\x00\x47\x00\x42\x00\x41\x00\x4d\x00\x69\x00\x78\x00\x53\x00\x20\x00\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"RGBAMixS フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
				return -1 ;
			}
			NS_SetDeleteHandleFlag( *PixelShaderHandle, PixelShaderHandle ) ;
		}
		if( GraphFilterSystemInfoHTML5.RgbaMixSRRRB[ SelectR ][ SelectA - DX_RGBA_SELECT_BLEND_R ][ IsPMA ].Shader == 0 )
		{
			Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.RgbaMixSRRRB[ SelectR ][ SelectA - DX_RGBA_SELECT_BLEND_R ][ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRectTex2_VS, HTML5_GetFragmentShader( *PixelShaderHandle ) ) ;
		}
<<<<<<< HEAD
		UseHTML5Shader = &GraphFilterSystemInfoHTML5.RgbaMixSRRRB[ SelectR ][ SelectA - DX_RGBA_SELECT_BLEND_R ][ IsPMA ] ;
=======
		UseAndrShader = &GraphFilterSystemInfoHTML5.RgbaMixSRRRB[ SelectR ][ SelectA - DX_RGBA_SELECT_BLEND_R ][ IsPMA ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	}
	else
	if( ( SelectR == DX_RGBA_SELECT_SRC_R   && SelectG == DX_RGBA_SELECT_SRC_G   && SelectB == DX_RGBA_SELECT_SRC_B   ) ||
		( SelectR == DX_RGBA_SELECT_BLEND_R && SelectG == DX_RGBA_SELECT_BLEND_G && SelectB == DX_RGBA_SELECT_BLEND_B ) )
	{
		if( SelectR == DX_RGBA_SELECT_BLEND_R )
		{
			SelectR -= DX_RGBA_SELECT_BLEND_R ;
			SelectG -= DX_RGBA_SELECT_BLEND_R ;
			SelectB -= DX_RGBA_SELECT_BLEND_R ;
			SelectA += DX_RGBA_SELECT_BLEND_R ;

			SrcBlendReverse = TRUE ;

			HandleTemp          = Info->BlendGrHandle ;
			Info->BlendGrHandle = Info->SrcGrHandle ;
			Info->SrcGrHandle   = HandleTemp ;
		}

		PixelShaderHandle = &GraphFilterShaderHandle.RgbaMixSRGBB[ SelectA - DX_RGBA_SELECT_BLEND_R ][ IsPMA ] ;
		if( *PixelShaderHandle < 0 )
		{
			_SNPRINTF( FileName, sizeof( FileName ), "RGBAMix_S%sS%sS%sB%s%s.flag", CharTable[ SelectR ], CharTable[ SelectG ], CharTable[ SelectB ], CharTable[ SelectA - DX_RGBA_SELECT_BLEND_R ], IsPMA ? "_PMA" : "" ) ;
			*PixelShaderHandle = HTML5_MemLoadShaderCode( FileName, DX_SHADERTYPE_PIXEL ) ;
			if( *PixelShaderHandle < 0 )
			{
				ConvString( FileName, -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
				DXST_LOGFILEFMT_ADDUTF16LE(( "\x52\x00\x47\x00\x42\x00\x41\x00\x4d\x00\x69\x00\x78\x00\x53\x00\x20\x00\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"RGBAMixS フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
				return -1 ;
			}
			NS_SetDeleteHandleFlag( *PixelShaderHandle, PixelShaderHandle ) ;
		}
		if( GraphFilterSystemInfoHTML5.RgbaMixSRGBB[ SelectA - DX_RGBA_SELECT_BLEND_R ][ IsPMA ].Shader == 0 )
		{
			Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.RgbaMixSRGBB[ SelectA - DX_RGBA_SELECT_BLEND_R ][ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRectTex2_VS, HTML5_GetFragmentShader( *PixelShaderHandle ) ) ;
		}
<<<<<<< HEAD
		UseHTML5Shader = &GraphFilterSystemInfoHTML5.RgbaMixSRGBB[ SelectA - DX_RGBA_SELECT_BLEND_R ][ IsPMA ] ;
=======
		UseAndrShader = &GraphFilterSystemInfoHTML5.RgbaMixSRGBB[ SelectA - DX_RGBA_SELECT_BLEND_R ][ IsPMA ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	}
	else
	{
USE_BASE_SHADER:
		PixelShaderHandle = &GraphFilterShaderHandle.RgbaMixBasePS[ IsPMA ] ;
		if( *PixelShaderHandle < 0 )
		{
			*PixelShaderHandle = HTML5_MemLoadShaderCode( FlagFileName[ IsPMA ], DX_SHADERTYPE_PIXEL ) ;
			if( *PixelShaderHandle < 0 )
			{
				ConvString( FlagFileName[ IsPMA ], -1, DX_CHARCODEFORMAT_ASCII, ( char * )PathUTF16LE, sizeof( PathUTF16LE ), DX_CHARCODEFORMAT_UTF16LE ) ;
				DXST_LOGFILEFMT_ADDUTF16LE(( "\xd5\x30\xa3\x30\xeb\x30\xbf\x30\xfc\x30\x28\x75\xb7\x30\xa7\x30\xfc\x30\xc0\x30\xfc\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x25\x00\x73\x00\x00"/*@ L"フィルター用シェーダーの作成に失敗しました %s" @*/, PathUTF16LE )) ;
				return -1 ;
			}
			NS_SetDeleteHandleFlag( *PixelShaderHandle, PixelShaderHandle ) ;
		}
		if( GraphFilterSystemInfoHTML5.RgbaMixBase[ IsPMA ].Shader == 0 )
		{
			Graphics_HTML5_Shader_Create( &GraphFilterSystemInfoHTML5.RgbaMixBase[ IsPMA ], GraphicsHardDataHTML5.Device.Shader.Base.StretchRectTex2_VS, HTML5_GetFragmentShader( *PixelShaderHandle ) ) ;
		}
<<<<<<< HEAD
		UseHTML5Shader = &GraphFilterSystemInfoHTML5.RgbaMixBase[ IsPMA ] ;
=======
		UseAndrShader = &GraphFilterSystemInfoHTML5.RgbaMixBase[ IsPMA ] ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)
	}

	ParamF4[ 0 ][ 0 ] = ( float )SelectR + 0.5f ;
	ParamF4[ 0 ][ 1 ] = ( float )SelectG + 0.5f ;
	ParamF4[ 0 ][ 2 ] = ( float )SelectB + 0.5f ;
	ParamF4[ 0 ][ 3 ] = ( float )SelectA + 0.5f ;

	// シェーダーを使用状態にセット
<<<<<<< HEAD
	glUseProgram( UseHTML5Shader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uSrcTex"     ), 0            ) ;
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uBlendTex"   ), 1            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseHTML5Shader, "uRGBASelect" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseHTML5Shader, Info, Info->BlendGraphScalingFilterIsBilinear ) ;
=======
	glUseProgram( UseAndrShader->Shader ) ;

	// Uniform の値をセット
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uSrcTex"     ), 0            ) ;
	UNIFORM_SET_INT1(   Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uBlendTex"   ), 1            ) ;
	UNIFORM_SET_FLOAT4( Graphics_HTML5_Shader_GetUniformIndex( UseAndrShader, "uRGBASelect" ), ParamF4[ 0 ] ) ;

	HTML5_FilterStretchBlt( UseAndrShader, Info, Info->BlendGraphScalingFilterIsBilinear ) ;
>>>>>>> d570d3a ([Bot] Update iOS Part before 3.24d)

	if( SrcBlendReverse )
	{
		HandleTemp          = Info->BlendGrHandle ;
		Info->BlendGrHandle = Info->SrcGrHandle ;
		Info->SrcGrHandle   = HandleTemp ;
	}

	// 正常終了
	return 0 ;
}

// フィルターで使用している全てのシェーダーを解放する
extern int GraphFilter_HTML5_ReleaseShaderAll( void )
{
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.Gauss,			sizeof( GraphFilterSystemInfoHTML5.Gauss			) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.BrightClip,		sizeof( GraphFilterSystemInfoHTML5.BrightClip		) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.BrightScale,	sizeof( GraphFilterSystemInfoHTML5.BrightScale	) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.DownScale,		sizeof( GraphFilterSystemInfoHTML5.DownScale		) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.Hsb,			sizeof( GraphFilterSystemInfoHTML5.Hsb			) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )&GraphFilterSystemInfoHTML5.Mono,			sizeof( GraphFilterSystemInfoHTML5.Mono			) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.Invert,			sizeof( GraphFilterSystemInfoHTML5.Invert			) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.Level,			sizeof( GraphFilterSystemInfoHTML5.Level			) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.TwoColor,		sizeof( GraphFilterSystemInfoHTML5.TwoColor		) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.GradientMap,	sizeof( GraphFilterSystemInfoHTML5.GradientMap	) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.Replacement,	sizeof( GraphFilterSystemInfoHTML5.Replacement	) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )&GraphFilterSystemInfoHTML5.PreMulAlpha,	sizeof( GraphFilterSystemInfoHTML5.PreMulAlpha	) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )&GraphFilterSystemInfoHTML5.InterpAlpha,	sizeof( GraphFilterSystemInfoHTML5.InterpAlpha	) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.YUVtoRGB,		sizeof( GraphFilterSystemInfoHTML5.YUVtoRGB		) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )&GraphFilterSystemInfoHTML5.Bicubic,		sizeof( GraphFilterSystemInfoHTML5.Bicubic		) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )&GraphFilterSystemInfoHTML5.Lanczos3,		sizeof( GraphFilterSystemInfoHTML5.Lanczos3		) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.BasicBlend,		sizeof( GraphFilterSystemInfoHTML5.BasicBlend		) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.RgbaMixBase,	sizeof( GraphFilterSystemInfoHTML5.RgbaMixBase	) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.RgbaMixSRGBB,	sizeof( GraphFilterSystemInfoHTML5.RgbaMixSRGBB	) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.RgbaMixSRRRB,	sizeof( GraphFilterSystemInfoHTML5.RgbaMixSRRRB	) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;
	Graphics_HTML5_ShaderArray_Release( ( GRAPHICS_HTML5_SHADER * )GraphFilterSystemInfoHTML5.RgbaMixS,		sizeof( GraphFilterSystemInfoHTML5.RgbaMixS		) / sizeof( GRAPHICS_HTML5_SHADER ) ) ;

	return 0 ;
}


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_FILTER

#endif // DX_NON_GRAPHICS

