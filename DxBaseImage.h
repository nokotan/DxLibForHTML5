// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�a�������h���������v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

#ifndef DXBASEIMAGE_H
#define DXBASEIMAGE_H

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"
#include "DxStatic.h"
#include "DxThread.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �L���[�u�}�b�v�̖ʂ̐�
#define CUBEMAP_SURFACE_NUM					(6)

// YUV�֘A�̒�`
#define YUV_RV								(0)
#define YUV_GU								(1)
#define YUV_GV								(2)
#define YUV_BU								(3)
#define YUV_Y								(4)

#define BASEIM								BaseImageManage

// �\���̒�` --------------------------------------------------------------------

// �ėp�摜�ǂݍ��݂ɕK�v�ȃO���[�o���f�[�^���W�߂��\����
struct CREATEBASEIMAGETYPE2_GPARAM
{
	int						( *UserImageLoadFunc4[ MAX_USERIMAGEREAD_FUNCNUM ] )( STREAMDATA *Src, BASEIMAGE *BaseImage ) ;	// ���[�U�[�摜�ǂݍ��݊֐�Ver4
	int						UserImageLoadFuncNum4 ;																		// ���[�U�[�摜�ǂݍ��݊֐�Ver4�̐�
	int						GetFormatOnly ;																				// �t�H�[�}�b�g�̎擾�݂̂��s�����ǂ���( TRUE:�t�H�[�}�b�g�̎擾�̂ݍs��  FALSE:�f�[�^���ǂݍ��� )
} ;

// �摜�̓ǂݍ��݂ɕK�v�ȃO���[�o���f�[�^��Z�߂��\����
struct LOADBASEIMAGE_GPARAM
{
	CREATEBASEIMAGETYPE2_GPARAM CreateGraphImageType2GParam ;		// CreateGraphImageType2_UseGParam �Ŏg�p����f�[�^

	STREAMDATASHREDTYPE2W	StreamDataShred2 ;						// �X�g���[���f�[�^�A�N�Z�X�p�֐��Q
	STREAMDATASHRED			FileStreamDataShred ;					// �t�@�C���f�[�^�A�N�Z�X�p�֐�
	STREAMDATASHRED			MemStreamDataShred ;					// �������f�[�^�A�N�Z�X�p�֐�

	int						ConvertPremultipliedAlpha ;				// �ǂݍ��ݏ�����ɏ�Z�ς݃A���t�@�̉摜�ɕϊ����邩�ǂ����̃t���O( TRUE:�ϊ��������s��  FALSE:�ϊ��������s��Ȃ� )
	int						AlphaTestImageCreateFlag ;				// �A���t�@�e�X�g���g�p����O���t�B�b�N���쐬���邩�ǂ����̃t���O( TRUE:���e�X�g���g�p����  FALSE:���e�X�g�͎g�p���Ȃ� )
	DWORD					TransColor ;							// ���ߐF( AlphaTestImageCreateFlag �� TRUE �̏ꍇ�p )
} ;

// BASEIMAGE + DIB �֌W�̏��\����
struct BASEIMAGEMANAGE
{
	int						( *UserImageLoadFunc4[ MAX_USERIMAGEREAD_FUNCNUM ] )( STREAMDATA *Src, BASEIMAGE *BaseImage ) ;																									// ���[�U�[�摜�ǂݍ��݊֐�Ver4
	int						UserImageLoadFuncNum4 ;																																										// ���[�U�[�摜�ǂݍ��݊֐�Ver4�̐�
/*
	int						( *UserImageLoadFunc3[ MAX_USERIMAGEREAD_FUNCNUM ] )( void *DataImage, int DataImageSize, int DataImageType, int BmpFlag, BASEIMAGE *BaseImage, BITMAPINFO **BmpInfo, void **GraphData ) ;		// ���[�U�[�摜�ǂݍ��݊֐�Ver3
	int						UserImageLoadFuncNum3 ;																																										// ���[�U�[�摜�ǂݍ��݊֐�Ver3�̐�

	int						( *UserImageLoadFunc2[ MAX_USERIMAGEREAD_FUNCNUM ] )( void *Image, int ImageSize, int ImageType, BITMAPINFO **BmpInfo, void **GraphData ) ;													// ���[�U�[�摜�ǂݍ��݊֐�Ver2
	int						UserImageLoadFuncNum2 ;																																										// ���[�U�[�摜�ǂݍ��݊֐�Ver2�̐�

	int						( *UserImageLoadFunc[ MAX_USERIMAGEREAD_FUNCNUM ] )( FILE *fp, BITMAPINFO **BmpInfo, void **GraphData ) ;																					// ���[�U�[�摜�ǂݍ��݊֐�
	int						UserImageLoadFuncNum ;																																										// ���[�U�[�摜�ǂݍ��݊֐��̐�
*/

	DX_CRITICAL_SECTION		CriticalProcessHandle ;					// �f�[�^�����Փˉ��p�N���e�B�J���Z�N�V����
	int						InitializeFlag ;						// �������t���O

	int						Bmp32AllZeroAlphaToXRGB8 ;				// 32bit bmp �摜�̂`���������ׂĂO��������`�����𖳎����邩�ǂ���
	int						LowLoadFlag ;							// �O���t�B�b�N�̒ᑬ�ǂݍ��݂��s�����t���O
	int						ImageShavedMode ;						// ���F���̊g�U�p�^�[��
	int						ConvertPremultipliedAlpha ;				// �ǂݍ��ݏ�����ɏ�Z�ς݃A���t�@�̉摜�ɕϊ����邩�ǂ����̃t���O( TRUE:�ϊ��������s��  FALSE:�ϊ��������s��Ȃ� )

	int						AlphaTestImageCreateFlag ;				// �A���t�@�e�X�g���g�p����O���t�B�b�N���쐬���邩�ǂ����̃t���O( TRUE:���e�X�g���g�p����  FALSE:���e�X�g�͎g�p���Ȃ� )
	DWORD					TransColor ;							// ���ߐF( AlphaTestImageCreateFlag �� TRUE �̏ꍇ�p )

	BYTE					RgbToPmaTable[ 256 ][ 256 ] ;			// RGB�l��PMA�l�ɕϊ�����ۂɎg�p����e�[�u��[ RGB�l ][ A�l ]
	BYTE					PmaToRgbTable[ 256 ][ 256 ] ;			// PMA�l��RGB�l�ɕϊ�����ۂɎg�p����e�[�u��[ RGB�l ][ A�l ]
} ;


// �e�[�u��-----------------------------------------------------------------------

extern BYTE YUVLimitTable[ 512 * 2 + 256 ] ;
extern int YUVTable[ 5 ][ 256 ] ;		// 0:rv  1:gu   2:gv   3:bu   4:y

// �������ϐ��錾 --------------------------------------------------------------

// ���ˑ��̉摜�ǂݍ��݊֐��z��
extern int ( *DefaultImageLoadFunc_PF[] )( STREAMDATA *Src, BASEIMAGE *BaseImage, int GetFormatOnly ) ;

// ��{�C���[�W�Ǘ��p�f�[�^
extern BASEIMAGEMANAGE BaseImageManage ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �������A��n��
extern	int		InitializeBaseImageManage( void ) ;															// ��{�C���[�W�Ǘ����̏�����
extern	int		TerminateBaseImageManage( void ) ;															// ��{�C���[�W�Ǘ����̌�n��

// �摜�ǂݍ��݊֐�
extern	int		SetBmp32AllZeroAlphaToXRGB8( int Flag ) ;															// 32bit bmp �摜�̂`���������ׂĂO��������`�����𖳎����邩�ǂ����̃t���O���Z�b�g����

extern	int		ScalingBltBaseImage(
					int SrcX1,  int SrcY1,  int SrcX2,  int SrcY2,  BASEIMAGE *SrcBaseImage,
					int DestX1, int DestY1, int DestX2, int DestY2, BASEIMAGE *DestBaseImage, int Bilinear = TRUE ) ;		// ��{�C���[�W�f�[�^���g��]������
extern	int		GraphHalfScaleBlt(	const COLORDATA *ColorData,
										      void *DestGraphData, int DestPitch,
										const void *SrcGraphData,  int SrcPitch,
										int DestX, int DestY, int SrcX, int SrcY, int SrcWidth, int SrcHeight ) ;	// �Q���̂P�X�P�[�����O���Ȃ���O���t�B�b�N�f�[�^�ԓ]�����s���A���̂��ߊ�{���̓]����`�͎w��ł��Ȃ�
extern	int		NoneMaskFill( RECT *Rect, void *ImageData, int Pitch, COLORDATA *ColorData, unsigned int Fill = 0xff ) ;		// �g���Ă��Ȃ��r�b�g���w��̒l�Ŗ��߂�


extern	int		ConvertYV12ToXRGB32( void *YV12Image, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// YV12 �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����
extern	int		ConvertNV11ToXRGB32( void *NV11Image, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// NV11 �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����
extern	int		ConvertNV12ToXRGB32( void *NV12Image, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// NV12 �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����
extern	int		ConvertYUY2ToXRGB32( void *YUY2Image, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// YUY2 �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����
extern	int		ConvertUYVYToXRGB32( void *UYVYImage, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// UYVY �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����
extern	int		ConvertYVYUToXRGB32( void *YVYUImage, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// YVYU �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����

extern	int		ConvertYV12ToYPlane_UVPlane( void *YV12Image, int Width, int Height, void *YBuffer, void *UVBuffer ) ;	// YV12 �t�H�[�}�b�g�̃C���[�W�� Y������UV�����̃C���[�W�ɕ�������
extern	int		ConvertNV11ToYPlane_UVPlane( void *NV11Image, int Width, int Height, void *YBuffer, void *UVBuffer ) ;	// NV11 �t�H�[�}�b�g�̃C���[�W�� Y������UV�����̃C���[�W�ɕ�������
extern	int		ConvertNV12ToYPlane_UVPlane( void *NV12Image, int Width, int Height, void *YBuffer, void *UVBuffer ) ;	// NV12 �t�H�[�}�b�g�̃C���[�W�� Y������UV�����̃C���[�W�ɕ�������
extern	int		ConvertYUY2ToYPlane_UVPlane( void *YUY2Image, int Width, int Height, void *YBuffer, void *UVBuffer ) ;	// YUY2 �t�H�[�}�b�g�̃C���[�W�� Y������UV�����̃C���[�W�ɕ�������
extern	int		ConvertUYVYToYPlane_UVPlane( void *UYVYImage, int Width, int Height, void *YBuffer, void *UVBuffer ) ;	// UYVY �t�H�[�}�b�g�̃C���[�W�� Y������UV�����̃C���[�W�ɕ�������
extern	int		ConvertYVYUToYPlane_UVPlane( void *YVYUImage, int Width, int Height, void *YBuffer, void *UVBuffer ) ;	// YVYU �t�H�[�}�b�g�̃C���[�W�� Y������UV�����̃C���[�W�ɕ�������

extern	void	InitCreateBaseImageType2GParam( CREATEBASEIMAGETYPE2_GPARAM *GParam, int GetFormatOnly ) ;				// CREATEBASEIMAGETYPE2_GPARAM �̃f�[�^���Z�b�g����
extern	void	InitLoadBaseImageGParam( LOADBASEIMAGE_GPARAM *GParam, int GetFormatOnly ) ;							// LOADBASEIMAGE_GPARAM �̃f�[�^���Z�b�g����

// CreateGraphImageType2 �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateGraphImageType2_UseGParam( CREATEBASEIMAGETYPE2_GPARAM *GParam, STREAMDATA *Src, BASEIMAGE *Dest ) ;

// CreateGraphImageOrDIBGraph �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateGraphImageOrDIBGraph_UseGParam(
					LOADBASEIMAGE_GPARAM *GParam,
					const wchar_t *FileName,
					const void *DataImage, int DataImageSize, int DataImageType,
					int BmpFlag, int ReverseFlag, int NotUseTransColor,
					BASEIMAGE *BaseImage, BITMAPINFO **BmpInfo, void **GraphData
				) ;

// CreateGraphImage_plus_Alpha �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateGraphImage_plus_Alpha_UseGParam(
					LOADBASEIMAGE_GPARAM *GParam,
					const wchar_t *FileName,
					const void *RgbImage, int RgbImageSize, int RgbImageType,
					const void *AlphaImage, int AlphaImageSize, int AlphaImageType,
					BASEIMAGE *RgbGraphImage, BASEIMAGE *AlphaGraphImage,
					int ReverseFlag, int NotUseTransColor
				) ;


// wchar_t�Ŋ֐�
extern	int		CreateGraphImageOrDIBGraph_WCHAR_T(    const wchar_t *FileName, const void *DataImage, int DataImageSize, int DataImageType /* LOADIMAGE_TYPE_FILE �� */ , int BmpFlag, int ReverseFlag, int NotUseTransColor, BASEIMAGE *BaseImage, BITMAPINFO **BmpInfo, void **GraphData ) ;
extern	int		GetImageSize_File_WCHAR_T(             const wchar_t *FileName, int *SizeX, int *SizeY ) ;
extern	int		CreateGraphImage_plus_Alpha_WCHAR_T(   const wchar_t *FileName, const void *RgbBaseImage, int RgbImageSize, int RgbImageType, const void *AlphaImage, int AlphaImageSize, int AlphaImageType, BASEIMAGE *RgbGraphImage, BASEIMAGE *AlphaGraphImage, int ReverseFlag, int NotUseTransColor ) ;
#ifdef WINDOWS_DESKTOP_OS
extern	HBITMAP	CreateDIBGraph_WCHAR_T(                const wchar_t *FileName,                                                                                                                                        int ReverseFlag,          COLORDATA *SrcColor ) ;
extern	int		CreateDIBGraph_plus_Alpha_WCHAR_T(     const wchar_t *FileName, HBITMAP *RGBBmp, HBITMAP *AlphaBmp,                                                                                                    int ReverseFlag = FALSE , COLORDATA *SrcColor = NULL ) ;
extern	HBITMAP	CreateDIBGraphVer2_WCHAR_T(            const wchar_t *FileName, const void *MemImage, int MemImageSize,                                             int ImageType,                                     int ReverseFlag,          COLORDATA *SrcColor ) ;
extern	int		CreateDIBGraphVer2_plus_Alpha_WCHAR_T( const wchar_t *FileName, const void *MemImage, int MemImageSize, const void *AlphaImage, int AlphaImageSize, int ImageType, HBITMAP *RGBBmp, HBITMAP *AlphaBmp, int ReverseFlag,          COLORDATA *SrcColor ) ;
#endif // WINDOWS_DESKTOP_OS
extern	int		CreateBaseImage_WCHAR_T(               const wchar_t *FileName, const void *FileImage, int FileImageSize, int DataType /*=LOADIMAGE_TYPE_FILE*/ , BASEIMAGE *BaseImage,  int ReverseFlag ) ;
extern	int		CreateBaseImageToFile_WCHAR_T(         const wchar_t *FileName,                                                                                   BASEIMAGE *BaseImage,  int ReverseFlag = FALSE ) ;

#ifndef DX_NON_JPEGREAD
extern	int		ReadJpegExif_WCHAR_T(                  const wchar_t *FilePath, const void *FileImage, size_t FileImageSize, BYTE *ExifBuffer, size_t ExifBufferSize ) ;
#endif // DX_NON_JPEGREAD

#ifndef DX_NON_SAVEFUNCTION

extern	int		SaveBaseImageToBmp_WCHAR_T(            const wchar_t *FilePath, const BASEIMAGE *BaseImage ) ;
extern	int		SaveBaseImageToDds_WCHAR_T(            const wchar_t *FilePath, const BASEIMAGE *BaseImage, int CubeMapFlag = FALSE , int MipMapCount = 1 ) ;
#ifndef DX_NON_PNGREAD
extern	int		SaveBaseImageToPng_WCHAR_T(            const wchar_t *FilePath,       BASEIMAGE *BaseImage, int CompressionLevel ) ;
#endif // DX_NON_PNGREAD
#ifndef DX_NON_JPEGREAD
extern	int		SaveBaseImageToJpeg_WCHAR_T(           const wchar_t *FilePath,       BASEIMAGE *BaseImage, int Quality, int Sample2x1 ) ;
#endif // DX_NON_JPEGREAD

#endif // DX_NON_SAVEFUNCTION



// ���ˑ��������E�I���֐�
extern	int		InitializeBaseImageManage_PF( void ) ;													// ��{�C���[�W�Ǘ����̊��ˑ������̏�����
extern	int		TerminateBaseImageManage_PF( void ) ;													// ��{�C���[�W�Ǘ����̊��ˑ������̌�n��


// �C�����C���֐��E�}�N��---------------------------------------------------------

// �����x���������_��P���x���������_�ɕϊ�����
__inline float Float16ToFloat32( WORD Float16 )
{
	unsigned int s ;
	int e ;
	unsigned int f ;
	unsigned int dest ;

	if( Float16 == 0 )
	{
		return	0.0f ;
	}

	s =     Float16 & 0x8000 ;
	e = ( ( Float16 & 0x7c00 ) >> 10 ) - 15 + 127 ;
	f =     Float16 & 0x03ff ;
	dest = ( s << 16 ) | ( ( e << 23 ) & 0x7f800000 ) | ( f << 13 ) ;
	return	*( ( float * )&dest ) ;
}

// �P���x���������_�𔼐��x���������_�ɕϊ�����
__inline WORD Float32ToFloat16( float Float32 )
{
	unsigned int src = *( ( DWORD * )&Float32 ) ;
	int e ;
	unsigned int s ;
	unsigned int f ;

	if( src == 0 )
	{
		return 0 ;
	}

	e = ( ( src & 0x7f800000 ) >> 23 ) - 127 + 15 ;
	if( e < 0 )
	{
		return 0 ;
	}
	else
	if( e > 31 )
	{
		e = 31 ;
	}

	s = src & 0x80000000 ;
	f = src & 0x007fffff ;
	return ( ( s >> 16 ) & 0x8000 ) | ( ( e << 10 ) & 0x7c00 ) | ( ( f >> 13 ) & 0x03ff ) ;
}

// DrawPixel ���̕`��֐��Ŏg�p����J���[�l���擾����
#ifndef DX_NON_GRAPHICS
	#define GetColor_Macro( /*int*/ Red, /*int*/ Green, /*int*/ Blue, /*int*/ Dest )\
	{\
		const COLORDATA *ColorData ;\
	\
		/* �F����Ԃ� */\
		if( GSYS.Setting.ValidHardware && GSYS.Screen.UserScreenImagePixelFormatMatchSoftRenderMode == FALSE )\
		{\
			Dest = 0xff000000 | ( ( ( unsigned int )( Red ) ) << 16 ) | ( ( ( unsigned int )( Green ) ) << 8 ) | ( ( unsigned int )( Blue ) ) ;\
		}\
		else\
		{\
			ColorData = GetMemImgColorData( GSYS.Screen.MainScreenColorBitDepth == 16 ? 0 : 1, FALSE, FALSE ) ;\
			Dest = ColorData->NoneMask +\
						( ( ( BYTE )( Red   ) >> ( 8 - ColorData->RedWidth   ) ) << ColorData->RedLoc   ) +\
						( ( ( BYTE )( Green ) >> ( 8 - ColorData->GreenWidth ) ) << ColorData->GreenLoc ) +\
						( ( ( BYTE )( Blue  ) >> ( 8 - ColorData->BlueWidth  ) ) << ColorData->BlueLoc  ) ;\
		}\
	}
#else // DX_NON_GRAPHICS
	#define GetColor_Macro( /*int*/ Red, /*int*/ Green, /*int*/ Blue, /*int*/ Dest )	0
#endif // DX_NON_GRAPHICS

// �J���[�l����ԁA�΁A�A�A���t�@�̒l���擾����
#ifndef DX_NON_GRAPHICS
	#define GetColor2_Macro( /* unsigned int */ Color, /* int */Red, /* int */Green, /* int */Blue )\
	{\
		/* �F����Ԃ� */\
		if( GSYS.Setting.ValidHardware && GSYS.Screen.UserScreenImagePixelFormatMatchSoftRenderMode == FALSE )\
		{\
			Red   = ( int )( ( Color >> 16 ) & 0xff ) ;\
			Green = ( int )( ( Color >>  8 ) & 0xff ) ;\
			Blue  = ( int )( ( Color       ) & 0xff ) ;\
		}\
		else\
		{\
			const COLORDATA *ColorData ;\
			int MaxRed ;\
			int MaxGreen ;\
			int MaxBlue ;\
\
			ColorData = GetMemImgColorData( GSYS.Screen.MainScreenColorBitDepth == 16 ? 0 : 1, FALSE, FALSE ) ;\
\
			MaxRed		= ( 1 << ColorData->RedWidth   ) - 1 ;\
			MaxGreen	= ( 1 << ColorData->GreenWidth ) - 1 ;\
			MaxBlue		= ( 1 << ColorData->BlueWidth  ) - 1 ;\
\
			/* �F�����i�[���� */\
			Red		= ( int )( ( ( Color & ColorData->RedMask   ) >> ColorData->RedLoc   ) * 255 / MaxRed   ) ;\
			Green	= ( int )( ( ( Color & ColorData->GreenMask ) >> ColorData->GreenLoc ) * 255 / MaxGreen ) ;\
			Blue	= ( int )( ( ( Color & ColorData->BlueMask  ) >> ColorData->BlueLoc  ) * 255 / MaxBlue  ) ;\
		}\
	}
#else // DX_NON_GRAPHICS
	#define GetColor2_Macro( /* unsigned int */ Color, /* int */ Red, /* int */ Green, /* int */ Blue )
#endif // DX_NON_GRAPHICS


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DXBASEIMAGE_H
