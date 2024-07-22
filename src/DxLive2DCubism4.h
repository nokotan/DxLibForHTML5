// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Live2D Cubism4 �֌W�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.24d
// 
// -------------------------------------------------------------------------------

#ifndef DXLIVE2D_CUBISM4_H
#define DXLIVE2D_CUBISM4_H

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"

#ifndef DX_NON_LIVE2D_CUBISM4
#include "DxUseCLibLive2DCubism4.h"
#include "DxLib.h"
#include "DxHandle.h"
#include "DxThread.h"
#include "DxGraphics.h"
#include "DxBaseFunc.h"
#include "DxStatic.h"

#ifdef WINDOWS_DESKTOP_OS
	#include "Windows/DxLive2DCubism4Win.h"
#endif // WINDOWS_DESKTOP_OS

#ifdef __ANDROID__
	#include "Android/DxLive2DCubism4Android.h"
#endif // __ANDROID__

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
		#include "iOS/DxLive2DCubism4iOS.h"
    #endif // TARGET_OS_IPHONE
#endif // __APPLE__





#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif// DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

#define LIVE2DSYS					Live2DCubism4SysData
#define LIVE2DDLL					Live2DCubism4DLLData

#ifdef WINDOWS_DESKTOP_OS
#define CALL_csmGetVersion( x )					( Live2DCubism4DLLData.csmGetVersion					== NULL ? Live2DCubism4DLLData.std_csmGetVersion x				 	:	Live2DCubism4DLLData.csmGetVersion x				 	)
#define CALL_csmGetLatestMocVersion( x )		( Live2DCubism4DLLData.csmGetLatestMocVersion			== NULL ? Live2DCubism4DLLData.std_csmGetLatestMocVersion x		 	:	Live2DCubism4DLLData.csmGetLatestMocVersion x		 	)
#define CALL_csmGetMocVersion( x )				( Live2DCubism4DLLData.csmGetMocVersion					== NULL ? Live2DCubism4DLLData.std_csmGetMocVersion x				:	Live2DCubism4DLLData.csmGetMocVersion x					)
#define CALL_csmGetLogFunction( x )				( Live2DCubism4DLLData.csmGetLogFunction				== NULL ? Live2DCubism4DLLData.std_csmGetLogFunction x			 	:	Live2DCubism4DLLData.csmGetLogFunction x			 	)
#define CALL_csmSetLogFunction( x )				( Live2DCubism4DLLData.csmSetLogFunction				== NULL ? Live2DCubism4DLLData.std_csmSetLogFunction x			 	:	Live2DCubism4DLLData.csmSetLogFunction x			 	)
#define CALL_csmReviveMocInPlace( x )			( Live2DCubism4DLLData.csmReviveMocInPlace				== NULL ? Live2DCubism4DLLData.std_csmReviveMocInPlace x			:	Live2DCubism4DLLData.csmReviveMocInPlace x				)
#define CALL_csmGetSizeofModel( x )				( Live2DCubism4DLLData.csmGetSizeofModel				== NULL ? Live2DCubism4DLLData.std_csmGetSizeofModel x			 	:	Live2DCubism4DLLData.csmGetSizeofModel x			 	)
#define CALL_csmInitializeModelInPlace( x )		( Live2DCubism4DLLData.csmInitializeModelInPlace		== NULL ? Live2DCubism4DLLData.std_csmInitializeModelInPlace x	 	:	Live2DCubism4DLLData.csmInitializeModelInPlace x	 	)
#define CALL_csmUpdateModel( x )				( Live2DCubism4DLLData.csmUpdateModel					== NULL ? Live2DCubism4DLLData.std_csmUpdateModel x				 	:	Live2DCubism4DLLData.csmUpdateModel x				 	)
#define CALL_csmReadCanvasInfo( x )				( Live2DCubism4DLLData.csmReadCanvasInfo				== NULL ? Live2DCubism4DLLData.std_csmReadCanvasInfo x			 	:	Live2DCubism4DLLData.csmReadCanvasInfo x			 	)
#define CALL_csmGetParameterCount( x )			( Live2DCubism4DLLData.csmGetParameterCount				== NULL ? Live2DCubism4DLLData.std_csmGetParameterCount x			:	Live2DCubism4DLLData.csmGetParameterCount x				)
#define CALL_csmGetParameterIds( x )			( Live2DCubism4DLLData.csmGetParameterIds				== NULL ? Live2DCubism4DLLData.std_csmGetParameterIds x			 	:	Live2DCubism4DLLData.csmGetParameterIds x			 	)
#define CALL_csmGetParameterMinimumValues( x )	( Live2DCubism4DLLData.csmGetParameterMinimumValues		== NULL ? Live2DCubism4DLLData.std_csmGetParameterMinimumValues x	:	Live2DCubism4DLLData.csmGetParameterMinimumValues x		)
#define CALL_csmGetParameterMaximumValues( x )	( Live2DCubism4DLLData.csmGetParameterMaximumValues		== NULL ? Live2DCubism4DLLData.std_csmGetParameterMaximumValues x	:	Live2DCubism4DLLData.csmGetParameterMaximumValues x		)
#define CALL_csmGetParameterDefaultValues( x )	( Live2DCubism4DLLData.csmGetParameterDefaultValues		== NULL ? Live2DCubism4DLLData.std_csmGetParameterDefaultValues x	:	Live2DCubism4DLLData.csmGetParameterDefaultValues x		)
#define CALL_csmGetParameterValues( x )			( Live2DCubism4DLLData.csmGetParameterValues			== NULL ? Live2DCubism4DLLData.std_csmGetParameterValues x		 	:	Live2DCubism4DLLData.csmGetParameterValues x		 	)
#define CALL_csmGetPartCount( x )				( Live2DCubism4DLLData.csmGetPartCount					== NULL ? Live2DCubism4DLLData.std_csmGetPartCount x				:	Live2DCubism4DLLData.csmGetPartCount x					)
#define CALL_csmGetPartIds( x )					( Live2DCubism4DLLData.csmGetPartIds					== NULL ? Live2DCubism4DLLData.std_csmGetPartIds x				 	:	Live2DCubism4DLLData.csmGetPartIds x				 	)
#define CALL_csmGetPartOpacities( x )			( Live2DCubism4DLLData.csmGetPartOpacities				== NULL ? Live2DCubism4DLLData.std_csmGetPartOpacities x			:	Live2DCubism4DLLData.csmGetPartOpacities x				)
#define CALL_csmGetPartParentPartIndices( x )	( Live2DCubism4DLLData.csmGetPartParentPartIndices		== NULL ? Live2DCubism4DLLData.std_csmGetPartParentPartIndices x	:	Live2DCubism4DLLData.csmGetPartParentPartIndices x		)
#define CALL_csmGetDrawableCount( x )			( Live2DCubism4DLLData.csmGetDrawableCount				== NULL ? Live2DCubism4DLLData.std_csmGetDrawableCount x			:	Live2DCubism4DLLData.csmGetDrawableCount x				)
#define CALL_csmGetDrawableIds( x )				( Live2DCubism4DLLData.csmGetDrawableIds				== NULL ? Live2DCubism4DLLData.std_csmGetDrawableIds x			 	:	Live2DCubism4DLLData.csmGetDrawableIds x			 	)
#define CALL_csmGetDrawableConstantFlags( x )	( Live2DCubism4DLLData.csmGetDrawableConstantFlags		== NULL ? Live2DCubism4DLLData.std_csmGetDrawableConstantFlags x	:	Live2DCubism4DLLData.csmGetDrawableConstantFlags x		)
#define CALL_csmGetDrawableDynamicFlags( x )	( Live2DCubism4DLLData.csmGetDrawableDynamicFlags		== NULL ? Live2DCubism4DLLData.std_csmGetDrawableDynamicFlags x	 	:	Live2DCubism4DLLData.csmGetDrawableDynamicFlags x	 	)
#define CALL_csmGetDrawableTextureIndices( x )	( Live2DCubism4DLLData.csmGetDrawableTextureIndices		== NULL ? Live2DCubism4DLLData.std_csmGetDrawableTextureIndices x	:	Live2DCubism4DLLData.csmGetDrawableTextureIndices x		)
#define CALL_csmGetDrawableDrawOrders( x )		( Live2DCubism4DLLData.csmGetDrawableDrawOrders			== NULL ? Live2DCubism4DLLData.std_csmGetDrawableDrawOrders x		:	Live2DCubism4DLLData.csmGetDrawableDrawOrders x			)
#define CALL_csmGetDrawableRenderOrders( x )	( Live2DCubism4DLLData.csmGetDrawableRenderOrders		== NULL ? Live2DCubism4DLLData.std_csmGetDrawableRenderOrders x	 	:	Live2DCubism4DLLData.csmGetDrawableRenderOrders x	 	)
#define CALL_csmGetDrawableOpacities( x )		( Live2DCubism4DLLData.csmGetDrawableOpacities			== NULL ? Live2DCubism4DLLData.std_csmGetDrawableOpacities x		:	Live2DCubism4DLLData.csmGetDrawableOpacities x			)
#define CALL_csmGetDrawableMaskCounts( x )		( Live2DCubism4DLLData.csmGetDrawableMaskCounts			== NULL ? Live2DCubism4DLLData.std_csmGetDrawableMaskCounts x	 	:	Live2DCubism4DLLData.csmGetDrawableMaskCounts x	 		)
#define CALL_csmGetDrawableMasks( x )			( Live2DCubism4DLLData.csmGetDrawableMasks				== NULL ? Live2DCubism4DLLData.std_csmGetDrawableMasks x			:	Live2DCubism4DLLData.csmGetDrawableMasks x				)
#define CALL_csmGetDrawableVertexCounts( x )	( Live2DCubism4DLLData.csmGetDrawableVertexCounts		== NULL ? Live2DCubism4DLLData.std_csmGetDrawableVertexCounts x	 	:	Live2DCubism4DLLData.csmGetDrawableVertexCounts x	 	)
#define CALL_csmGetDrawableVertexPositions( x )	( Live2DCubism4DLLData.csmGetDrawableVertexPositions	== NULL ? Live2DCubism4DLLData.std_csmGetDrawableVertexPositions x 	:	Live2DCubism4DLLData.csmGetDrawableVertexPositions x 	)
#define CALL_csmGetDrawableVertexUvs( x )		( Live2DCubism4DLLData.csmGetDrawableVertexUvs			== NULL ? Live2DCubism4DLLData.std_csmGetDrawableVertexUvs x		:	Live2DCubism4DLLData.csmGetDrawableVertexUvs x			)
#define CALL_csmGetDrawableIndexCounts( x )		( Live2DCubism4DLLData.csmGetDrawableIndexCounts		== NULL ? Live2DCubism4DLLData.std_csmGetDrawableIndexCounts x	 	:	Live2DCubism4DLLData.csmGetDrawableIndexCounts x	 	)
#define CALL_csmGetDrawableIndices( x )			( Live2DCubism4DLLData.csmGetDrawableIndices			== NULL ? Live2DCubism4DLLData.std_csmGetDrawableIndices x		 	:	Live2DCubism4DLLData.csmGetDrawableIndices x		 	)
#define CALL_csmResetDrawableDynamicFlags( x )	( Live2DCubism4DLLData.csmResetDrawableDynamicFlags		== NULL ? Live2DCubism4DLLData.std_csmResetDrawableDynamicFlags x	:	Live2DCubism4DLLData.csmResetDrawableDynamicFlags x		)
#else // WINDOWS_DESKTOP_OS
#define CALL_csmGetVersion( x )					( Live2DCubism4DLLData.csmGetVersion x				 	)
#define CALL_csmGetLatestMocVersion( x )		( Live2DCubism4DLLData.csmGetLatestMocVersion x		 	)
#define CALL_csmGetMocVersion( x )				( Live2DCubism4DLLData.csmGetMocVersion x				)
#define CALL_csmGetLogFunction( x )				( Live2DCubism4DLLData.csmGetLogFunction x			 	)
#define CALL_csmSetLogFunction( x )				( Live2DCubism4DLLData.csmSetLogFunction x			 	)
#define CALL_csmReviveMocInPlace( x )			( Live2DCubism4DLLData.csmReviveMocInPlace x			)
#define CALL_csmGetSizeofModel( x )				( Live2DCubism4DLLData.csmGetSizeofModel x			 	)
#define CALL_csmInitializeModelInPlace( x )		( Live2DCubism4DLLData.csmInitializeModelInPlace x	 	)
#define CALL_csmUpdateModel( x )				( Live2DCubism4DLLData.csmUpdateModel x				 	)
#define CALL_csmReadCanvasInfo( x )				( Live2DCubism4DLLData.csmReadCanvasInfo x			 	)
#define CALL_csmGetParameterCount( x )			( Live2DCubism4DLLData.csmGetParameterCount x			)
#define CALL_csmGetParameterIds( x )			( Live2DCubism4DLLData.csmGetParameterIds x			 	)
#define CALL_csmGetParameterMinimumValues( x )	( Live2DCubism4DLLData.csmGetParameterMinimumValues x	)
#define CALL_csmGetParameterMaximumValues( x )	( Live2DCubism4DLLData.csmGetParameterMaximumValues x	)
#define CALL_csmGetParameterDefaultValues( x )	( Live2DCubism4DLLData.csmGetParameterDefaultValues x	)
#define CALL_csmGetParameterValues( x )			( Live2DCubism4DLLData.csmGetParameterValues x		 	)
#define CALL_csmGetPartCount( x )				( Live2DCubism4DLLData.csmGetPartCount x				)
#define CALL_csmGetPartIds( x )					( Live2DCubism4DLLData.csmGetPartIds x				 	)
#define CALL_csmGetPartOpacities( x )			( Live2DCubism4DLLData.csmGetPartOpacities x			)
#define CALL_csmGetPartParentPartIndices( x )	( Live2DCubism4DLLData.csmGetPartParentPartIndices x	)
#define CALL_csmGetDrawableCount( x )			( Live2DCubism4DLLData.csmGetDrawableCount x			)
#define CALL_csmGetDrawableIds( x )				( Live2DCubism4DLLData.csmGetDrawableIds x			 	)
#define CALL_csmGetDrawableConstantFlags( x )	( Live2DCubism4DLLData.csmGetDrawableConstantFlags x	)
#define CALL_csmGetDrawableDynamicFlags( x )	( Live2DCubism4DLLData.csmGetDrawableDynamicFlags x	 	)
#define CALL_csmGetDrawableTextureIndices( x )	( Live2DCubism4DLLData.csmGetDrawableTextureIndices x	)
#define CALL_csmGetDrawableDrawOrders( x )		( Live2DCubism4DLLData.csmGetDrawableDrawOrders x		)
#define CALL_csmGetDrawableRenderOrders( x )	( Live2DCubism4DLLData.csmGetDrawableRenderOrders x	 	)
#define CALL_csmGetDrawableOpacities( x )		( Live2DCubism4DLLData.csmGetDrawableOpacities x		)
#define CALL_csmGetDrawableMaskCounts( x )		( Live2DCubism4DLLData.csmGetDrawableMaskCounts x	 	)
#define CALL_csmGetDrawableMasks( x )			( Live2DCubism4DLLData.csmGetDrawableMasks x			)
#define CALL_csmGetDrawableVertexCounts( x )	( Live2DCubism4DLLData.csmGetDrawableVertexCounts x	 	)
#define CALL_csmGetDrawableVertexPositions( x )	( Live2DCubism4DLLData.csmGetDrawableVertexPositions x 	)
#define CALL_csmGetDrawableVertexUvs( x )		( Live2DCubism4DLLData.csmGetDrawableVertexUvs x		)
#define CALL_csmGetDrawableIndexCounts( x )		( Live2DCubism4DLLData.csmGetDrawableIndexCounts x	 	)
#define CALL_csmGetDrawableIndices( x )			( Live2DCubism4DLLData.csmGetDrawableIndices x		 	)
#define CALL_csmResetDrawableDynamicFlags( x )	( Live2DCubism4DLLData.csmResetDrawableDynamicFlags x	)
#endif // WINDOWS_DESKTOP_OS

// �\���̒�` --------------------------------------------------------------------

// �t�@�C������Live2D���f���n���h�����쐬���鏈���ɕK�v�ȃO���[�o���f�[�^��Z�߂�����
struct LIVE2DCUBISM4_LOADMODEL_GPARAM
{
	int							Dummy ;
} ;

// Live2D Cubism4 ���f�����
struct LIVE2DCUBISM4MODEL
{
	HANDLEINFO					HandleInfo ;				// �n���h�����ʃf�[�^

	float						PosX ;						// �g�����X���[�V�����p�����[�^
	float						PosY ;
	float						ExRateX ;
	float						ExRateY ;
	float						RotAngle ;

	int							LastPlayMotionNo ;			// �Ō�ɍĐ��������[�V�����̃O���[�v���̔ԍ�

	D_LAppModel *				AppModel ;
} ;

// Live2D Cubism4 DLL �̊֐��|�C���^�\����
struct LIVE2DCUBISM4DLL
{
	wchar_t					Live2DCubismCoreDLLPath[ 1024 ] ;	// Live2D Cubism Core DLL �̃t�@�C���p�X

	DWORD					( *csmGetVersion )( void ) ;
	DWORD					( *csmGetLatestMocVersion )( void ) ;
	DWORD					( *csmGetMocVersion )( const void* address, const DWORD size ) ;
	csmLogFunctionP			( *csmGetLogFunction )( void ) ;
	void					( *csmSetLogFunction )( csmLogFunctionP handler ) ;
	void*					( *csmReviveMocInPlace )( void* address, const DWORD size ) ;
	DWORD 					( *csmGetSizeofModel )( const void* moc ) ;
	void* 					( *csmInitializeModelInPlace )( const void* moc, void* address, const DWORD size ) ;
	void 					( *csmUpdateModel )( void* model ) ;
	void 					( *csmReadCanvasInfo )( const void* model, D_CubismVector2* outSizeInPixels, D_CubismVector2* outOriginInPixels, float* outPixelsPerUnit ) ;
	int 					( *csmGetParameterCount )( const void* model ) ;
	const char** 			( *csmGetParameterIds )( const void* model ) ;
	const float*			( *csmGetParameterMinimumValues )( const void* model ) ;
	const float*			( *csmGetParameterMaximumValues )( const void* model ) ;
	const float*			( *csmGetParameterDefaultValues )( const void* model ) ;
	float* 					( *csmGetParameterValues )( void* model ) ;
	int 					( *csmGetPartCount )( const void* model ) ;
	const char**			( *csmGetPartIds )( const void* model ) ;
	float*					( *csmGetPartOpacities ) (void* model ) ;
	const int*				( *csmGetPartParentPartIndices )( const void* model ) ;
	int 					( *csmGetDrawableCount )( const void* model ) ;
	const char**			( *csmGetDrawableIds )( const void* model ) ;
	const BYTE*				( *csmGetDrawableConstantFlags )( const void* model ) ;
	const BYTE*				( *csmGetDrawableDynamicFlags )( const void* model ) ;
	const int*				( *csmGetDrawableTextureIndices )( const void* model ) ;
	const int*				( *csmGetDrawableDrawOrders )( const void* model ) ;
	const int*				( *csmGetDrawableRenderOrders )( const void* model ) ;
	const float*			( *csmGetDrawableOpacities )( const void* model ) ;
	const int*				( *csmGetDrawableMaskCounts )( const void* model ) ;
	const int**				( *csmGetDrawableMasks )( const void* model ) ;
	const int*				( *csmGetDrawableVertexCounts )( const void* model ) ;
	const D_CubismVector2**	( *csmGetDrawableVertexPositions )( const void* model ) ;
	const D_CubismVector2**	( *csmGetDrawableVertexUvs )( const void* model ) ;
	const int*				( *csmGetDrawableIndexCounts )( const void* model ) ;
	const unsigned short**	( *csmGetDrawableIndices )( const void* model ) ;
	void					( *csmResetDrawableDynamicFlags )( void* model ) ;

#ifdef WINDOWS_DESKTOP_OS
	DWORD					( __stdcall *std_csmGetVersion )( void ) ;
	DWORD					( __stdcall *std_csmGetLatestMocVersion )( void ) ;
	DWORD					( __stdcall *std_csmGetMocVersion )( const void* address, const DWORD size ) ;
	csmLogFunctionP			( __stdcall *std_csmGetLogFunction )( void ) ;
	void					( __stdcall *std_csmSetLogFunction )( csmLogFunctionP handler ) ;
	void*					( __stdcall *std_csmReviveMocInPlace )( void* address, const DWORD size ) ;
	DWORD 					( __stdcall *std_csmGetSizeofModel )( const void* moc ) ;
	void* 					( __stdcall *std_csmInitializeModelInPlace )( const void* moc, void* address, const DWORD size ) ;
	void 					( __stdcall *std_csmUpdateModel )( void* model ) ;
	void 					( __stdcall *std_csmReadCanvasInfo )( const void* model, D_CubismVector2* outSizeInPixels, D_CubismVector2* outOriginInPixels, float* outPixelsPerUnit ) ;
	int 					( __stdcall *std_csmGetParameterCount )( const void* model ) ;
	const char** 			( __stdcall *std_csmGetParameterIds )( const void* model ) ;
	const float*			( __stdcall *std_csmGetParameterMinimumValues )( const void* model ) ;
	const float*			( __stdcall *std_csmGetParameterMaximumValues )( const void* model ) ;
	const float*			( __stdcall *std_csmGetParameterDefaultValues )( const void* model ) ;
	float* 					( __stdcall *std_csmGetParameterValues )( void* model ) ;
	int 					( __stdcall *std_csmGetPartCount )( const void* model ) ;
	const char**			( __stdcall *std_csmGetPartIds )( const void* model ) ;
	float*					( __stdcall *std_csmGetPartOpacities ) (void* model ) ;
	const int*				( __stdcall *std_csmGetPartParentPartIndices )( const void* model ) ;
	int 					( __stdcall *std_csmGetDrawableCount )( const void* model ) ;
	const char**			( __stdcall *std_csmGetDrawableIds )( const void* model ) ;
	const BYTE*				( __stdcall *std_csmGetDrawableConstantFlags )( const void* model ) ;
	const BYTE*				( __stdcall *std_csmGetDrawableDynamicFlags )( const void* model ) ;
	const int*				( __stdcall *std_csmGetDrawableTextureIndices )( const void* model ) ;
	const int*				( __stdcall *std_csmGetDrawableDrawOrders )( const void* model ) ;
	const int*				( __stdcall *std_csmGetDrawableRenderOrders )( const void* model ) ;
	const float*			( __stdcall *std_csmGetDrawableOpacities )( const void* model ) ;
	const int*				( __stdcall *std_csmGetDrawableMaskCounts )( const void* model ) ;
	const int**				( __stdcall *std_csmGetDrawableMasks )( const void* model ) ;
	const int*				( __stdcall *std_csmGetDrawableVertexCounts )( const void* model ) ;
	const D_CubismVector2**	( __stdcall *std_csmGetDrawableVertexPositions )( const void* model ) ;
	const D_CubismVector2**	( __stdcall *std_csmGetDrawableVertexUvs )( const void* model ) ;
	const int*				( __stdcall *std_csmGetDrawableIndexCounts )( const void* model ) ;
	const unsigned short**	( __stdcall *std_csmGetDrawableIndices )( const void* model ) ;
	void					( __stdcall *std_csmResetDrawableDynamicFlags )( void* model ) ;
#endif // WINDOWS_DESKTOP_OS
} ;

// Live2D Cubism4 �V�X�e���p�f�[�^�\����
struct LIVE2DCUBISM4SYSTEMDATA
{
	int						InitializeFlag ;						// �������t���O

	int						EnableConstantBuffer ;					// �R���X�^���g�o�b�t�@���g�p�ł��邩�ǂ���

	SCREENDRAWSETTINGINFO	ScreenDrawSettingInfo ;					// Live2D�`��J�n�O�̕`��ݒ�

	D_CubismIdManager *		s_cubismIdManager ;

	DXARC					ShaderBinDxa ;							// �V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�\����
	void					*ShaderBinDxaImage ;					// �V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�̃o�C�i���C���[�W

	int						NowDrawLive2DModelHandle ;				// ���ݕ`����s���Ă��� Live2D���f���̃n���h��

	int						UserShader[ DX_LIVE2D_SHADER_NUM ] ;	// ���[�U�[�V�F�[�_�[

	void					( *DrawUserCallback )( int Live2DModelHandle, int TextureIndex, void *UserData ) ;		// �`��̑O�ɌĂԃR�[���o�b�N�֐�
	void					*DrawUserCallbackData ;					// �`��̑O�ɌĂԃR�[���o�b�N�֐��ɓn���A�h���X

	int						NotUseAutoScaling ;						// ��ʃT�C�Y�ɉ����������X�P�[�����O���s�Ȃ�Ȃ����ǂ���( TRUE:�s�Ȃ�Ȃ�  FALSE:�s�� )
	int						NotUseAutoCentering ;					// �����ŉ�ʂ̒��S�ɕ`�悷�邩�ǂ���( TRUE:��ʂ̒��S�ɕ`�悵�Ȃ�   FALSE:��ʂ̒��S�ɕ`�悷�� )
	int						NotUseReverseYAxis ;					// Live2D_Model_SetTranslate �Ŏw�肷�镽�s�ړ��l�� y �̌����𔽓]���Ȃ����ǂ���( TRUE:���]���Ȃ�   FALSE:���]���� )

	LIVE2DCUBISM4SYSTEMDATA_PF	PF ;								// ���ˑ��f�[�^
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// Live2D Cubism4 �V�X�e���f�[�^
extern LIVE2DCUBISM4SYSTEMDATA Live2DCubism4SysData ;

// Live2D Cubism 4 DLL
extern LIVE2DCUBISM4DLL Live2DCubism4DLLData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// Live2D Cubism4 �֘A�̏������ƌ�n��
extern	int		Live2DCubism4_Initialize( void ) ;					// Live2D Cubism4 �̏�����
extern	int		Live2DCubism4_Terminate( void ) ;					// Live2D Cubism4 �̌�n��


extern	int		Live2DCubism4_SetupShaderCode( int *ShaderCodeBinConvert, BYTE *ShaderCodeBin ) ;	// �V�F�[�_�[DXA�t�@�C���̃Z�b�g�A�b�v
extern	int		Live2DCubism4_LoadShaderCode( const char *ShaderName, int ShaderType ) ;			// �w�薼�̃V�F�[�_�[��ǂݍ���

extern	void	Live2DCubism4_InitLoadModelGParam( LIVE2DCUBISM4_LOADMODEL_GPARAM *GParam ) ;		// LIVE2DCUBISM4_LOADMODEL_GPARAM �̃f�[�^���Z�b�g����

extern	int		Live2DCubism4_LoadModel_UseGParam( LIVE2DCUBISM4_LOADMODEL_GPARAM *GParam, const wchar_t *FilePath, int ASyncLoadFlag = FALSE, int ASyncThread = FALSE ) ;				// Live2D_LoadModel �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����




// wchar_t�Ŋ֐�
extern	int			Live2D_SetCubism4CoreDLLPath_WCHAR_T(			const wchar_t *CoreDLLFilePath ) ;
extern	int			Live2D_LoadModel_WCHAR_T(						const wchar_t *FilePath ) ;
extern	int			Live2D_Model_StartMotion_WCHAR_T(				int Live2DModelHandle, const wchar_t *group, int no, float fadeInSeconds, float fadeOutSeconds, int isLoopFadeIn ) ;
extern	int			Live2D_Model_SetExpression_WCHAR_T(				int Live2DModelHandle, const wchar_t *expressionID ) ;
extern	int			Live2D_Model_HitTest_WCHAR_T(					int Live2DModelHandle, const wchar_t *hitAreaName, float x, float y ) ;
extern	float		Live2D_Model_GetParameterValue_WCHAR_T(			int Live2DModelHandle, const wchar_t *parameterId ) ;
extern	int			Live2D_Model_SetParameterValue_WCHAR_T(			int Live2DModelHandle, const wchar_t *parameterId, float value ) ;
extern	int			Live2D_Model_GetMotionCount_WCHAR_T(			int Live2DModelHandle, const wchar_t *groupName ) ;
extern	const TCHAR *Live2D_Model_GetMotionFileName_WCHAR_T(		int Live2DModelHandle, const wchar_t *groupName, int index ) ;
extern	const TCHAR *Live2D_Model_GetMotionSoundFileName_WCHAR_T(	int Live2DModelHandle, const wchar_t *groupName, int index ) ;
extern	float		Live2D_Model_GetMotionFadeInTimeValue_WCHAR_T(	int Live2DModelHandle, const wchar_t *groupName, int index ) ;
extern	float		Live2D_Model_GetMotionFadeOutTimeValue_WCHAR_T(	int Live2DModelHandle, const wchar_t *groupName, int index ) ;



#ifndef DX_NON_NAMESPACE

}

#endif// DX_NON_NAMESPACE



// ���ˑ��֐�
extern	int		Live2DCubism4_Initialize_PF( void ) ;										// Live2D Cubism4 �֘A�̏���������֐��̊��ˑ��������s���֐�
extern	int		Live2DCubism4_Terminate_PF( void ) ;										// Live2D Cubism4 �֘A�̌�n��������֐��̊��ˑ��������s���֐�

extern	int		Live2DCubism4_GenerateShaders_PF( void ) ;									// Live2D Cubism4 �̃V�F�[�_�[�쐬�̊��ˑ��������s��
extern	int		Live2DCubism4_SetupShader_PF( int ConstantBufferHandle, D_CubismConstantBufferDxLib *ConstantBuffer, D_ShaderNames VertexShader, D_ShaderNames PixelShader ) ;	// Live2D Cubism4 �̃V�F�[�_�[�̃Z�b�g�A�b�v���s��
extern	int		Live2DCubism4_DrawAfter_PF( void ) ;										// Live2D Cubism4 �̕`��̌�ɌĂ΂����ˑ��֐�



#endif// DX_NON_LIVE2D_CUBISM4

#endif// DXLIVE2D_CUBISM4_H
