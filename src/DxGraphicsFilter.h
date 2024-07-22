// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		GraphFilter�n�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.24b
// 
// -------------------------------------------------------------------------------

#ifndef DX_GRAPHICSFILTER_H
#define DX_GRAPHICSFILTER_H

#include "DxCompileConfig.h"

#ifndef DX_NON_FILTER

// �C���N���[�h ------------------------------------------------------------------
#include "DxLib.h"
#include "DxGraphics.h"
#include <stdarg.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------


// �\���̒�` --------------------------------------------------------------------

// �t�B���^�[���\����
struct GRAPHFILTER_INFO
{
	int						BlendGraphScalingFilterIsBilinear ;
	int						BltBlendMode ;
	int						IsBlend ;
	int						FilterOrBlendType ;
	int						SrcGrHandle ;
	int						BlendGrHandle ;
	int						DestGrHandle ;
	int						SrcEqualDestClearFlag ;
	float					BlendRatio ;
	int						Pass ;
	int						SrcX1 ;
	int						SrcY1 ;
	int						SrcX2 ;
	int						SrcY2 ;
	int						SrcDivNum ;
	int						BlendX ;
	int						BlendY ;
	int						BlendPosEnable ;
	int						BlendX2 ;
	int						BlendY2 ;
	int						BlendPos2Enable ;
	int						DestX ;
	int						DestY ;

	int						PassNum ;
	int						UseWorkScreen ;

	int						DestWidth ;
	int						DestHeight ;
	BASEIMAGE				SrcBaseImage ;
	BASEIMAGE				BlendBaseImage ;
	BASEIMAGE				DestBaseImage ;

	IMAGEDATA				*SrcImage ;
	IMAGEDATA				*DestImage ;
	IMAGEDATA				*BlendImage ;
	IMAGEDATA				*TargetScreenImage ;
} ;

// �t�B���^�[�����
struct GRAPHFILTER_PARAM
{
	int						Gauss_PixelWidth ;
	float					Gauss_Param ;
	int						Bright_Clip_CmpType ;
	float					Bright_Clip_CmpParam ;
	int						Bright_Clip_ClipFillFlag ;
	COLOR_F					Bright_Clip_ClipFillColor ;
	int						Bright_Scale_Min ;
	int						Bright_Scale_Max ;
	int						Hsb_HueType ;
	float					Hsb_Hue ;
	float					Hsb_Saturation ;
	float					Hsb_Bright ;
	float					Mono_Cb ;
	float					Mono_Cr ;
	float					Lv_Min ;
	float					Lv_Max ;
	float					Lv_Gamma ;
	float					Lv_AfterMin ;
	float					Lv_AfterMax ;
	float					TC_Threshold ;
	COLOR_F					TC_LowColor ;
	COLOR_F					TC_HighColor ;
	int						GM_MapGrHandle ;
	int						GM_Reverse ;
	int						UVGrHandle ;
	int						DestSizeX ;
	int						DestSizeY ;
	COLOR_U8				TargetColor ;
	COLOR_U8				NextColor ;
	int						DepthMapGrHandle ;
	float					SSAO_KernelRadius ;
	float					SSAO_MinDistance ;
	float					SSAO_MaxDistance ;
	float					SSAO_Strength ;
	int						SSAO_OcclusionColor ;
	float					SSAO_OcclusionPower ;
	int						SSAO_ColorMapHandle ;
	COLOR_F					ColorScale ;
	COLOR_F					ColorPreSub ;

	int						RGBA_R ;
	int						RGBA_G ;
	int						RGBA_B ;
	int						RGBA_A ;
} ;

// �t�B���^�[�̃V�F�[�_�[�n���h��
struct GRAPHFILTER_SHADER_HANDLE
{
	int						Gauss_PS[ 3 ] ;							// �K�E�X�t�B���^�̃s�N�Z���V�F�[�_�[
	int						BrightClipPS[ 2 ][ 2 ][ 2 ] ;			// ���邳�ŃN���b�v����t�B���^�̃s�N�Z���V�F�[�_�[[ 1:���ȏ�N���b�v  0:���ȉ��N���b�v ][ 1:�N���b�v�h��Ԃ����� 0:�h��Ԃ��Ȃ� ][ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						BrightScalePS[ 2 ] ;					// �w��̖��邳�̗̈���g�傷��t�B���^�̃s�N�Z���V�F�[�_�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						DownScalePS[ 3 ] ;						// �k���t�B���^�[( 0:X2 1:X4 2:X8 )
	int						HsbPS[ 3 ][ 2 ] ;						// �g�r�a�t�B���^�[[ 0:RGB to HSI  1:HSI to RGB  2:HSB �� HLock ][ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						MonoPS ;								// ���m�g�[���t�B���^�[
	int						InvertPS[ 2 ] ;							// �K�����]�t�B���^�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						LevelPS[ 2 ] ;							// ���x���␳�t�B���^�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						GammaTex ;								// �K���}�␳�Ɏg�p����摜
	float					PrevGamma ;								// �O��̃K���}�t�B���^�̍ۂ̃K���}�l
	int						TwoColorPS[ 2 ] ;						// �Q�l���t�B���^�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						GradientMapPS[ 2 ][ 2 ] ;				// �O���f�[�V�����}�b�v�t�B���^�[[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						ReplacementPS[ 2 ] ;					// �F�̒u��[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						PreMulAlphaPS ;							// �ʏ�摜�����Z�ς݃A���t�@�摜���쐬����ׂ̃t�B���^�[
	int						InterpAlphaPS ;							// ��Z�ς݃A���t�@�摜����ʏ�摜���쐬����ׂ̃t�B���^�[
	int						YUVtoRGBPS[ 4 ] ;						// YUV�J���[��RGB�J���[�ɕϊ�����t�B���^�[
	int						BicubicPS ;								// �o�C�L���[�r�b�N��ԃt�B���^�[
	int						Lanczos3PS ;							// Lanczos-3��ԃt�B���^�[
	int						SSAOPS[ 3 ] ;							// SSAO�t�B���^�[
	int						SSAOMixPS ;								// SSAO�̉B���W���ƃJ���[�o�b�t�@����������t�B���^�[
	int						FloatColorScalePS ;						// FloatColorScale�t�B���^�[

	int						BasicBlendPS[ DX_GRAPH_BLEND_NUM ] ;	// ��{�I�ȃu�����h�t�B���^�[
	int						RgbaMixBasePS[ 2 ] ;					// RGBAMix�u�����h��{[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						RgbaMixSRGBB[ 4 ][ 2 ] ;				// RGBAMix�u�����h�� A ���� BRGBA �̂S��[ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						RgbaMixSRRRB[ 4 ][ 4 ][ 2 ] ;			// RGBAMix�u�����h�� SYYY BX �̂P�U�� [ Y ][ X ][ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
	int						RgbaMixS[ 4 ][ 4 ][ 4 ][ 4 ][ 2 ] ;		// RGBAMix�u�����h�� S �����̑g�ݍ��킹256��[ R ][ G ][ B ][ A ][ 0:�ʏ�p  1:��Z�ς݃A���t�@�p ]
} ;

// �t�B���^�[�����̃V�X�e���f�[�^
struct GRAPHFILTER_SYSTEM_DATA
{
	int						BlendGraphScalingFilterIsNotBilinear ;	// SrcGrHandle �� BlendGrHandle �̃T�C�Y���قȂ����ꍇ�̃X�P�[�����O�t�B���^�[���[�h�̓o�C���j�A�����ł͂Ȃ����ǂ���
	int						BltBlendMode ;							// �]����Ƃ̃u�����h���[�h
} ;

// �������ϐ��錾 --------------------------------------------------------------

extern GRAPHFILTER_SHADER_HANDLE GraphFilterShaderHandle ;
extern GRAPHFILTER_SYSTEM_DATA GraphFilterSystemData ;
extern float SSAO_Kernel[ /*32*//*18*/64 * 4 ] ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern int	GraphFilter_Initialize( void ) ;	// �t�B���^�[�����̏�����
extern int	GraphFilter_Terminate( void ) ;		// �t�B���^�[�����̌�n��

extern int	GraphFilter_Mono(            GRAPHFILTER_INFO *Info, float Cb, float Cr ) ;
extern int	GraphFilter_Gauss(           GRAPHFILTER_INFO *Info, int PixelWidth, float Param ) ;
extern int	GraphFilter_Down_Scale(      GRAPHFILTER_INFO *Info, int DivNum ) ;
extern int	GraphFilter_Bright_Clip(     GRAPHFILTER_INFO *Info, int CmpType, float CmpParam, int ClipFillFlag, COLOR_F *ClipFillColor, int IsPMA ) ;
extern int	GraphFilter_Bright_Scale(    GRAPHFILTER_INFO *Info, int BrightMin, int BrightMax, int IsPMA ) ;
extern int	GraphFilter_HSB(             GRAPHFILTER_INFO *Info, int HueType, float Hue, float Saturation, float Bright, int IsPMA ) ;
extern int	GraphFilter_Invert(          GRAPHFILTER_INFO *Info, int IsPMA ) ;
extern int	GraphFilter_Level(           GRAPHFILTER_INFO *Info, float Min, float Max, float Gamma, float AfterMin, float AfterMax, int IsPMA ) ;
extern int	GraphFilter_TwoColor(        GRAPHFILTER_INFO *Info, float Threshold, COLOR_F *LowColor, COLOR_F *HighColor, int IsPMA ) ;
extern int	GraphFilter_GradientMap(     GRAPHFILTER_INFO *Info, int MapGrHandle, int Reverse, int IsPMA ) ;
extern int	GraphFilter_Replacement(     GRAPHFILTER_INFO *Info, COLOR_U8 TargetColor, COLOR_U8 NextColor, int IsPMA ) ;
extern int	GraphFilter_PremulAlpha(     GRAPHFILTER_INFO *Info ) ;
extern int	GraphFilter_InterpAlpha(     GRAPHFILTER_INFO *Info ) ;
extern int	GraphFilter_YUVtoRGB(        GRAPHFILTER_INFO *Info, int UVGrHandle ) ;
extern int	GraphFilter_BicubicScale(    GRAPHFILTER_INFO *Info, int DestSizeX, int DestSizeY ) ;
extern int	GraphFilter_Lanczos3Scale(   GRAPHFILTER_INFO *Info, int DestSizeX, int DestSizeY ) ;
extern int	GraphFilter_SSAO(            GRAPHFILTER_INFO *Info, int DepthMapGrHandle, float KernelRadius, float MinDistance, float MaxDistance, float Strength, int OcclusionColor, float OcclusionPower, int ColorMapGrHandle ) ;
extern int	GraphFilter_FloatColorScale( GRAPHFILTER_INFO *Info, COLOR_F ColorScale, COLOR_F ColorPreSub ) ;

extern int	GraphFilter_RectBltBase( int IsBlend, int SrcGrHandle, int BlendGrHandle, int DestGrHandle, int BlendRatio, int FilterOrBlendType, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int BlendX, int BlendY, int BlendPosEnable, int BlendX2, int BlendY2, int BlendPos2Enable, int DestX, int DestY, va_list ParamList ) ;

extern int	GraphBlend_Basic(           GRAPHFILTER_INFO *Info, int IsPMA ) ;
extern int	GraphBlend_RGBA_Select_Mix( GRAPHFILTER_INFO *Info, int SelectR, int SelectG, int SelectB, int SelectA, int IsPMA ) ;



// va_list �֐�
extern	int	GraphFilter_VaList(			int    GrHandle,                                                                                                               int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , va_list VaList ) ;		// �摜�Ƀt�B���^�[�������s��
extern	int	GraphFilterBlt_VaList(		int SrcGrHandle, int DestGrHandle,                                                                                             int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , va_list VaList ) ;		// �摜�̃t�B���^�[�t���]�����s��
extern	int	GraphFilterRectBlt_VaList(	int SrcGrHandle, int DestGrHandle, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int DestX,  int DestY,                          int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , va_list VaList ) ;		// �摜�̃t�B���^�[�t���]�����s��( ��`�w�� )
extern	int	GraphBlend_VaList(			int    GrHandle, int BlendGrHandle,                                                                                                                                          int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , va_list VaList ) ;	// ��̉摜���u�����h����
extern	int	GraphBlendBlt_VaList(		int SrcGrHandle, int BlendGrHandle, int DestGrHandle,                                                                                                                        int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , va_list VaList ) ;	// ��̉摜���u�����h���Č��ʂ��w��̉摜�ɏo�͂���
extern	int	GraphBlendRectBlt_VaList(	int SrcGrHandle, int BlendGrHandle, int DestGrHandle, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int BlendX,  int BlendY,                             int DestX, int DestY, int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , va_list VaList ) ;	// ��̉摜���u�����h���Č��ʂ��w��̉摜�ɏo�͂���( ��`�w�� )
extern	int	GraphBlendRectBlt2_VaList(	int SrcGrHandle, int BlendGrHandle, int DestGrHandle, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int BlendX1, int BlendY1, int BlendX2,  int BlendY2, int DestX, int DestY, int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , va_list VaList ) ;	// ��̉摜���u�����h���Č��ʂ��w��̉摜�ɏo�͂���( ��`�w��A�u�����h�摜�̋�`���w�� )

// ���ˑ��֌W
extern int	GraphFilter_Initialize_PF( void ) ;
extern int	GraphFilter_Terminate_PF( void ) ;

extern int	GraphFilter_Mono_PF(                GRAPHFILTER_INFO *Info, float Cb, float Cr ) ;
extern int	GraphFilter_Gauss_PF(               GRAPHFILTER_INFO *Info, int PixelWidth, float Param, float *Table ) ;
extern int	GraphFilter_Down_Scale_PF(          GRAPHFILTER_INFO *Info, int DivNum ) ;
extern int	GraphFilter_Bright_Clip_PF(         GRAPHFILTER_INFO *Info, int CmpType, float CmpParam, int ClipFillFlag, COLOR_F *ClipFillColor, int IsPMA ) ;
extern int	GraphFilter_Bright_Scale_PF(        GRAPHFILTER_INFO *Info, int BrightMin, int BrightMax, int IsPMA ) ;
extern int	GraphFilter_HSB_PF(                 GRAPHFILTER_INFO *Info, int HueType, float Hue, float Saturation, float Bright, int IsPMA ) ;
extern int	GraphFilter_Invert_PF(              GRAPHFILTER_INFO *Info, int IsPMA ) ;
extern int	GraphFilter_Level_PF(               GRAPHFILTER_INFO *Info, float Min, float Max, float Gamma, float AfterMin, float AfterMax, int IsPMA ) ;
extern int	GraphFilter_TwoColor_PF(            GRAPHFILTER_INFO *Info, float Threshold, COLOR_F *LowColor, COLOR_F *HighColor, int IsPMA ) ;
extern int	GraphFilter_GradientMap_PF(         GRAPHFILTER_INFO *Info, int MapGrHandle, int Reverse, int IsPMA ) ;
extern int	GraphFilter_Replacement_PF(         GRAPHFILTER_INFO *Info, COLOR_U8 TargetColor, COLOR_U8 NextColor, int IsPMA ) ;
extern int	GraphFilter_PremulAlpha_PF(         GRAPHFILTER_INFO *Info ) ;
extern int	GraphFilter_InterpAlpha_PF(         GRAPHFILTER_INFO *Info ) ;
extern int	GraphFilter_YUVtoRGB_PF(            GRAPHFILTER_INFO *Info, int UVGrHandle ) ;
extern int	GraphFilter_BicubicScale_PF(        GRAPHFILTER_INFO *Info, int DestSizeX, int DestSizeY ) ;
extern int	GraphFilter_Lanczos3Scale_PF(       GRAPHFILTER_INFO *Info, int DestSizeX, int DestSizeY ) ;
extern int	GraphFilter_SSAO_PF(                GRAPHFILTER_INFO *Info, int DepthMapGrHandle, float KernelRadius, float MinDistance, float MaxDistance, float Strength, int OcclusionColor, float OcclusionPower, int ColorMapGrHandle ) ;
extern int	GraphFilter_FloatColorScale_PF(     GRAPHFILTER_INFO *Info, COLOR_F ColorScale, COLOR_F ColorPreSub ) ;
extern int	GraphFilter_RectBltBase_Timing0_PF( GRAPHFILTER_INFO *Info, GRAPHFILTER_PARAM *Param ) ;
extern int	GraphFilter_RectBltBase_Timing1_PF( void ) ;
extern int	GraphFilter_DestGraphSetup_PF(      GRAPHFILTER_INFO *Info, int *UseSrcGrHandle, int *UseDestGrHandle ) ;
extern int	GraphFilter_DestGraphUpdate_PF(     GRAPHFILTER_INFO *Info, int UseDestGrHandle, int FilterResult ) ;

extern int	GraphBlend_Basic_PF(                GRAPHFILTER_INFO *Info, int IsPMA ) ;
extern int	GraphBlend_RGBA_Select_Mix_PF(      GRAPHFILTER_INFO *Info, int SelectR, int SelectG, int SelectB, int SelectA, int IsPMA ) ;

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_FILTER

#endif // DX_GRAPHICSFILTER_H

