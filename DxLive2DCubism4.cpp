// ----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Live2D Cubism4 �֌W�v���O����
// 
// 				Ver 3.22a
// 
// ----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "DxCompileConfig.h"

#ifndef DX_NON_LIVE2D_CUBISM4

// �C���N���[�h----------------------------------------------------------------
#include "DxMemory.h"
#include "DxHandle.h"
#include "DxLive2DCubism4.h"
#include "DxSystem.h"
#include "DxLog.h"
#include "DxASyncLoad.h"
#include "DxUseCLibLive2DCubism4.h"

// ----------------------------------------------------------------------------

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����`------------------------------------------------------------------

// Live2D Cubism4 ���f���n���h���̗L�����`�F�b�N
#define LIVE2DCUBISM4MODELCHK( HAND, MPOINT )		HANDLECHK(       DX_HANDLETYPE_LIVE2D_CUBISM4_MODEL, HAND, *( ( HANDLEINFO ** )&MPOINT ) )
#define LIVE2DCUBISM4MODELCHK_ASYNC( HAND, MPOINT )	HANDLECHK_ASYNC( DX_HANDLETYPE_LIVE2D_CUBISM4_MODEL, HAND, *( ( HANDLEINFO ** )&MPOINT ) )

// �\���̐錾------------------------------------------------------------------

// �֐��錾--------------------------------------------------------------------

// �n���h���������E��n��
static	int			Live2DCubism4_Model_InitializeHandle( HANDLEINFO *HandleInfo ) ;						// Live2D Cubism 4 ���f���n���h���̏�����
static	int			Live2DCubism4_Model_TerminateHandle( HANDLEINFO *HandleInfo ) ;							// Live2D Cubism 4 ���f���n���h���̌�n��

// �f�[�^�錾------------------------------------------------------------------

// Live2D Cubism4 �V�X�e���f�[�^
LIVE2DCUBISM4SYSTEMDATA Live2DCubism4SysData ;

// Live2D Cubism 4 DLL
LIVE2DCUBISM4DLL Live2DCubism4DLLData ;

// �v���O�����R�[�h------------------------------------------------------------

// Live2D Cubism4 �֘A�̏������ƌ�n��

// Live2D Cubism4 �̏�����
extern int Live2DCubism4_Initialize( void )
{
	// ���ɏ������ς݂̏ꍇ�͉������Ȃ�
	if( LIVE2DSYS.InitializeFlag == TRUE ) return 0 ;

	// Live2D Cubism4 Model �n���h���Ǘ����̏�����
	InitializeHandleManage( DX_HANDLETYPE_LIVE2D_CUBISM4_MODEL, sizeof( LIVE2DCUBISM4MODEL ), MAX_LIVE2D_CUBISM4_MODEL_NUM, Live2DCubism4_Model_InitializeHandle, Live2DCubism4_Model_TerminateHandle, L"Live2DModel" ) ;

	//---- static ������ ----
	D_JsonValue::StaticInitializeNotForClientCall() ;

	// IDManager ��������
	LIVE2DSYS.s_cubismIdManager = new_D_CubismIdManager() ;

	// ���ˑ��̏�����
	if( Live2DCubism4_Initialize_PF() < 0 )
	{
		goto ERR ;
	}

	// �������ς݃t���O�𗧂Ă�
	LIVE2DSYS.InitializeFlag = TRUE ;

	// �I��
	return 0 ;

	// �G���[����
ERR:
	Live2DCubism4_Terminate() ;

	return -1;
}

// Live2D Cubism4 �̌�n��
extern int Live2DCubism4_Terminate( void )
{
	// Live2D Cubism4 Model �n���h����������
	AllHandleSub( DX_HANDLETYPE_LIVE2D_CUBISM4_MODEL ) ;

	// Live2D Cubism4 Model �n���h���Ǘ����̌�n��
	TerminateHandleManage( DX_HANDLETYPE_LIVE2D_CUBISM4_MODEL ) ;

	// ���ˑ��̌�n��
	if( Live2DCubism4_Terminate_PF() < 0 )
	{
		return -1 ;
	}

	//---- static ��n�� ----
	D_JsonValue::StaticReleaseNotForClientCall() ;

	// IDManager ���폜
    delete_D_CubismIdManager( LIVE2DSYS.s_cubismIdManager ) ;
	LIVE2DSYS.s_cubismIdManager = NULL ;

	//�����_���̐ÓI���\�[�X�i�V�F�[�_�v���O�������j���������
	D_CubismRenderer::StaticRelease() ;

	// �V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�̌�n��
	DXA_Terminate( &LIVE2DSYS.ShaderBinDxa ) ;
	if( LIVE2DSYS.ShaderBinDxaImage )
	{
		DXFREE( LIVE2DSYS.ShaderBinDxaImage ) ;
		LIVE2DSYS.ShaderBinDxaImage = NULL ;
	}

	// �������ς݃t���O��|��
	LIVE2DSYS.InitializeFlag = FALSE ;

	// ����I��
	return 0 ;
}








// �V�F�[�_�[DXA�t�@�C���̃Z�b�g�A�b�v
extern int Live2DCubism4_SetupShaderCode( int *ShaderCodeBinConvert, BYTE *ShaderCodeBin )
{
	int Size ;

	if( ShaderCodeBinConvert != NULL && *ShaderCodeBinConvert == 0 )
	{
		*ShaderCodeBinConvert = 1 ;
		Base64ToBin( ShaderCodeBin, ShaderCodeBin ) ;
	}

	// �V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�����k�����f�[�^���𓀂���
	Size = DXA_Decode( ShaderCodeBin, NULL ) ;
	LIVE2DSYS.ShaderBinDxaImage = DXALLOC( ( size_t )Size ) ;
	if( LIVE2DSYS.ShaderBinDxaImage == NULL )
	{
		goto ERR ;
	}

	DXA_Decode( ShaderCodeBin, LIVE2DSYS.ShaderBinDxaImage ) ;

	// �c�w�`�t�@�C�����I�[�v������
	DXA_Initialize( &LIVE2DSYS.ShaderBinDxa ) ;
	if( DXA_OpenArchiveFromMem( &LIVE2DSYS.ShaderBinDxa, LIVE2DSYS.ShaderBinDxaImage, Size, FALSE, FALSE ) != 0 )
	{
		goto ERR ;
	}

	// ����I��
	return 0 ;

ERR :
	if( LIVE2DSYS.ShaderBinDxaImage != NULL )
	{
		DXFREE( LIVE2DSYS.ShaderBinDxaImage ) ;
		LIVE2DSYS.ShaderBinDxaImage = NULL ;
	}

	return -1 ;
}

// �w�薼�̃V�F�[�_�[��ǂݍ���
extern int Live2DCubism4_LoadShaderCode( const char *ShaderName, int ShaderType )
{
	int Addr, Size ;
	BYTE *FileImage ;
	int Ret ;

	if( DXA_GetFileInfo( &LIVE2DSYS.ShaderBinDxa, DX_CHARCODEFORMAT_ASCII, ShaderName, &Addr, &Size ) < 0 )
	{
		return -1 ;
	}

	FileImage = ( BYTE * )DXA_GetFileImage( &LIVE2DSYS.ShaderBinDxa ) + Addr ;

	Ret = Graphics_Shader_CreateHandle_UseGParam( ShaderType, FileImage, Size, FALSE, FALSE ) ;

	return Ret ;
}









// �n���h���������E��n��

// Live2D Cubism 4 ���f���n���h���̏�����
static int Live2DCubism4_Model_InitializeHandle( HANDLEINFO * HandleInfo )
{
	LIVE2DCUBISM4MODEL *Model = ( LIVE2DCUBISM4MODEL * )HandleInfo ;

	// �g�����X���[�V�����p�����[�^��������
	Model->PosX = 0.0f ;
	Model->PosY = 0.0f ;
	Model->ExRateX = 1.0f ;
	Model->ExRateY = 1.0f ;
	Model->RotAngle = 0.0f ;

	// �I��
	return 0 ;
}

// Live2D Cubism 4 ���f���n���h���̌�n��
static int Live2DCubism4_Model_TerminateHandle( HANDLEINFO *HandleInfo )
{
	LIVE2DCUBISM4MODEL *Model = ( LIVE2DCUBISM4MODEL * )HandleInfo ;

	delete_D_LAppModel( Model->AppModel ) ;
	Model->AppModel = NULL ;

	// �I��
	return 0 ;
}

// LIVE2DCUBISM4_LOADMODEL_GPARAM �̃f�[�^���Z�b�g����
extern void Live2DCubism4_InitLoadModelGParam( LIVE2DCUBISM4_LOADMODEL_GPARAM *GParam )
{
	_MEMSET( GParam, 0, sizeof( *GParam ) ) ;
}







// Live2DCubismCore.dll �̃t�@�C���p�X��ݒ肷��
extern int NS_Live2D_SetCubism4CoreDLLPath( const TCHAR *CoreDLLFilePath )
{
#ifdef UNICODE
	return Live2D_SetCubism4CoreDLLPath_WCHAR_T(
		CoreDLLFilePath
	) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( CoreDLLFilePath, return -1 )

	Result = Live2D_SetCubism4CoreDLLPath_WCHAR_T(
		UseCoreDLLFilePathBuffer
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( CoreDLLFilePath )

	return Result ;
#endif
}

// Live2DCubismCore.dll �̃t�@�C���p�X��ݒ肷��
extern int NS_Live2D_SetCubism4CoreDLLPathWithStrLen( const TCHAR *CoreDLLFilePath, size_t CoreDLLFilePathLength )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( CoreDLLFilePath, CoreDLLFilePathLength, return -1 )
	Result = Live2D_SetCubism4CoreDLLPath_WCHAR_T( UseCoreDLLFilePathBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( CoreDLLFilePath )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( CoreDLLFilePath, CoreDLLFilePathLength, return -1 )
	Result = Live2D_SetCubism4CoreDLLPath_WCHAR_T( UseCoreDLLFilePathBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( CoreDLLFilePath )
#endif
	return Result ;
}

// Live2DCubismCore.dll �̃t�@�C���p�X��ݒ肷��
extern int NS_Live2D_SetCubism3CoreDLLPath( const TCHAR *CoreDLLFilePath )
{
#ifdef UNICODE
	return Live2D_SetCubism4CoreDLLPath_WCHAR_T(
		CoreDLLFilePath
	) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( CoreDLLFilePath, return -1 )

	Result = Live2D_SetCubism4CoreDLLPath_WCHAR_T(
		UseCoreDLLFilePathBuffer
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( CoreDLLFilePath )

	return Result ;
#endif
}

// Live2DCubismCore.dll �̃t�@�C���p�X��ݒ肷��
extern int NS_Live2D_SetCubism3CoreDLLPathWithStrLen( const TCHAR *CoreDLLFilePath, size_t CoreDLLFilePathLength )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( CoreDLLFilePath, CoreDLLFilePathLength, return -1 )
	Result = Live2D_SetCubism4CoreDLLPath_WCHAR_T( UseCoreDLLFilePathBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( CoreDLLFilePath )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( CoreDLLFilePath, CoreDLLFilePathLength, return -1 )
	Result = Live2D_SetCubism4CoreDLLPath_WCHAR_T( UseCoreDLLFilePathBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( CoreDLLFilePath )
#endif
	return Result ;
}

extern int Live2D_SetCubism4CoreDLLPath_WCHAR_T( const wchar_t *CoreDLLFilePath )
{
	// �p�X������������G���[
	if( CL_strlen( WCHAR_T_CHARCODEFORMAT, ( char * )CoreDLLFilePath ) >= sizeof( LIVE2DDLL.Live2DCubismCoreDLLPath ) / sizeof( wchar_t ) )
	{
		return -1 ;
	}

	// �p�X��ۑ�
	CL_strcpy( WCHAR_T_CHARCODEFORMAT, ( char * )LIVE2DDLL.Live2DCubismCoreDLLPath, ( char * )CoreDLLFilePath ) ;

	// ����I��
	return 0 ;
}

// Live2D �̕`�揈�����J�n
extern int NS_Live2D_RenderBegin( void )
{
	int windowWidth, windowHeight ;

	// ������������Ă��Ȃ���΃G���[
	if( LIVE2DSYS.InitializeFlag == FALSE )
	{
		return -1 ;
	}

	// �e��`��ݒ�����擾
	Graphics_DrawSetting_GetScreenDrawSettingInfo( &LIVE2DSYS.ScreenDrawSettingInfo ) ;

	// D3D11 �t���[���擪���� 
	// �e�t���[���ł́ACubism�̏����O�ɃR�[�� 
	NS_GetGraphSize( NS_GetDrawScreen(), &windowWidth, &windowHeight ) ;
	D_CubismRenderer_DxLib::StartFrame( windowWidth, windowHeight ) ;

	// ����I��
	return 0 ;
}

// Live2D �̕`�揈�����I��
extern int NS_Live2D_RenderEnd( void )
{
	// ������������Ă��Ȃ���΃G���[
	if( LIVE2DSYS.InitializeFlag == FALSE )
	{
		return -1 ;
	}

	// D3D11 �t���[���I������ 
	// �e�t���[���ł́ACubism�̏�����ɃR�[��
	D_CubismRenderer_DxLib::EndFrame() ;

	// �c�w���C�u�����p�̐ݒ�ɖ߂�
	Graphics_Hardware_RefreshSetting_PF() ;
	Graphics_DrawSetting_SetScreenDrawSettingInfo( &LIVE2DSYS.ScreenDrawSettingInfo ) ;

	// ����I��
	return 0 ;
}

// Live2D �̃��f���t�@�C����ǂݍ���
extern int NS_Live2D_LoadModel( const TCHAR *FilePath )
{
#ifdef UNICODE
	return Live2D_LoadModel_WCHAR_T(
		FilePath
	) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( FilePath, return -1 )

	Result = Live2D_LoadModel_WCHAR_T(
		UseFilePathBuffer
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( FilePath )

	return Result ;
#endif
}

// Live2D �̃��f���t�@�C����ǂݍ���
extern int NS_Live2D_LoadModelWithStrLen( const TCHAR *FilePath, size_t FilePathLength )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( FilePath, FilePathLength, return -1 )
	Result = Live2D_LoadModel_WCHAR_T( UseFilePathBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( FilePath )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( FilePath, FilePathLength, return -1 )
	Result = Live2D_LoadModel_WCHAR_T( UseFilePathBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( FilePath )
#endif
	return Result ;
}

extern int Live2D_LoadModel_WCHAR_T( const wchar_t *FilePath )
{
	LIVE2DCUBISM4_LOADMODEL_GPARAM GParam ;

	Live2DCubism4_InitLoadModelGParam( &GParam ) ;

	return Live2DCubism4_LoadModel_UseGParam( &GParam, FilePath, GetASyncLoadFlag() ) ;
}

// Live2D_LoadModel �̎������֐�
extern int Live2DCubism4_LoadModel_Static(
	LIVE2DCUBISM4_LOADMODEL_GPARAM * /*GParam*/,
	int Live2DModelHandle,
	const wchar_t *FilePath,
	int ASyncThread
)
{
	LIVE2DCUBISM4MODEL * Model ;
	wchar_t DirPath[ 1024 ], FileName[ 256 ] ;

	// �G���[����
	if( ASyncThread )
	{
		if( LIVE2DCUBISM4MODELCHK_ASYNC( Live2DModelHandle, Model ) )
			return -1 ;
	}
	else
	{
		if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
			return -1 ;
	}

	// D_LAppModel �̍쐬
	Model->AppModel = new_D_LAppModel() ;

	// �t�@�C���̓ǂݍ���
	AnalysisFileNameAndDirPathW_( FilePath, FileName, sizeof( FileName ), DirPath, sizeof( DirPath ) ) ;
	SetEnMarkW_( DirPath, sizeof( DirPath ) ) ;
	if( Model->AppModel->LoadAssets( ( BYTE * )DirPath, ( BYTE * )FileName, ASyncThread ) == false )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4c\x00\x69\x00\x76\x00\x65\x00\x32\x00\x44\x00\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x3a\x00\x20\x00\xe2\x30\xc7\x30\xeb\x30\xd5\x30\xa1\x30\xa4\x30\xeb\x30\x20\x00\x25\x00\x73\x00\x20\x00\x6e\x30\xad\x8a\x7f\x30\xbc\x8f\x7f\x30\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x00"/*@ L"Live2D Error : ���f���t�@�C�� %s �̓ǂݍ��݂Ɏ��s���܂���" @*/, DirPath )) ;
		return -1 ;
	}

	// ����I��
	return 0 ;
}

#ifndef DX_NON_ASYNCLOAD

// Live2D_LoadModel �̔񓯊��ǂݍ��݃X���b�h����Ă΂��֐�
static void Live2DCubism4_LoadModel_ASync( ASYNCLOADDATA_COMMON *AParam )
{
	LIVE2DCUBISM4_LOADMODEL_GPARAM *GParam ;
	int Live2DModelHandle ;
	const wchar_t *FilePath ;
	int Addr ;
	int Result ;

	Addr = 0 ;
	GParam = ( LIVE2DCUBISM4_LOADMODEL_GPARAM * )GetASyncLoadParamStruct( AParam->Data, &Addr ) ;
	Live2DModelHandle = GetASyncLoadParamInt( AParam->Data, &Addr ) ;
	FilePath = GetASyncLoadParamString( AParam->Data, &Addr ) ;

	Result = Live2DCubism4_LoadModel_Static( GParam, Live2DModelHandle, FilePath, TRUE ) ;
	DecASyncLoadCount( Live2DModelHandle ) ;
	if( Result < 0 )
	{
		SubHandle( Live2DModelHandle ) ;
	}
}

#endif // DX_NON_ASYNCLOAD

// Live2D_LoadModel �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern int Live2DCubism4_LoadModel_UseGParam(
	LIVE2DCUBISM4_LOADMODEL_GPARAM *GParam,
	const wchar_t *FilePath,
	int ASyncLoadFlag,
	int ASyncThread
)
{
	int Live2DModelHandle = -1 ;
	wchar_t FullPath[ 1024 ] ;

	if( LIVE2DSYS.InitializeFlag == FALSE )
	{
		return -1 ;
	}

	Live2DModelHandle = AddHandle( DX_HANDLETYPE_LIVE2D_CUBISM4_MODEL, ASyncThread, -1 );
	if( Live2DModelHandle == -1 )
		goto ERR ;

	ConvertFullPathW_( FilePath, FullPath, sizeof( FullPath ) ) ;

#ifndef DX_NON_ASYNCLOAD
	if( ASyncLoadFlag && ASyncThread == FALSE )
	{
		ASYNCLOADDATA_COMMON *AParam = NULL ;
		int Addr ;

		// �p�����[�^�ɕK�v�ȃ������̃T�C�Y���Z�o
		Addr = 0 ;
		AddASyncLoadParamStruct( NULL, &Addr, GParam, sizeof( *GParam ) ) ;
		AddASyncLoadParamInt( NULL, &Addr, Live2DModelHandle ) ;
		AddASyncLoadParamString( NULL, &Addr, FullPath ) ;

		// �������̊m��
		AParam = AllocASyncLoadDataMemory( Addr ) ;
		if( AParam == NULL )
			goto ERR ;

		// �����ɕK�v�ȏ����Z�b�g
		AParam->ProcessFunction = Live2DCubism4_LoadModel_ASync ;
		Addr = 0 ;
		AddASyncLoadParamStruct( AParam->Data, &Addr, GParam, sizeof( *GParam ) ) ;
		AddASyncLoadParamInt( AParam->Data, &Addr, Live2DModelHandle ) ;
		AddASyncLoadParamString( AParam->Data, &Addr, FullPath ) ;

		// �f�[�^��ǉ�
		if( AddASyncLoadData( AParam ) < 0 )
		{
			DXFREE( AParam ) ;
			AParam = NULL ;
			goto ERR ;
		}

		// �񓯊��ǂݍ��݃J�E���g���C���N�������g
		IncASyncLoadCount( Live2DModelHandle, AParam->Index ) ;
	}
	else
#endif // DX_NON_ASYNCLOAD
	{
		if( Live2DCubism4_LoadModel_Static( GParam, Live2DModelHandle, FullPath, ASyncThread ) < 0 )
			goto ERR ;
	}

#ifndef DX_NON_ASYNCLOAD
	if( ASyncThread )
	{
		DecASyncLoadCount( Live2DModelHandle ) ;
	}
#endif // DX_NON_ASYNCLOAD

	// �n���h����Ԃ�
	return Live2DModelHandle ;

ERR :
#ifndef DX_NON_ASYNCLOAD
	if( ASyncThread )
	{
		DecASyncLoadCount( Live2DModelHandle ) ;
	}
#endif // DX_NON_ASYNCLOAD

	SubHandle( Live2DModelHandle ) ;
	Live2DModelHandle = -1 ;

	// �I��
	return -1 ;
}

// Live2D �̃��f�����폜����
extern int NS_Live2D_DeleteModel( int Live2DModelHandle )
{
	return SubHandle( Live2DModelHandle ) ;
}

// ���ׂĂ� Live2D �̃��f�����폜����
extern int NS_Live2D_InitModel( void )
{
	return AllHandleSub( DX_HANDLETYPE_LIVE2D_CUBISM4_MODEL ) ;
}

// Live2D �̃��f���̏�Ԃ��X�V����
extern int NS_Live2D_Model_Update( int Live2DModelHandle, float DeltaTimeSeconds )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// Cubism���f���̍X�V
	Model->AppModel->Update( DeltaTimeSeconds ) ;

	// ����I��
	return 0 ;
}

// Live2D �̃��f���̈ʒu��ݒ肷��
extern int NS_Live2D_Model_SetTranslate( int Live2DModelHandle, float x, float y )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �l�̕ۑ�
	Model->PosX = x ;
	Model->PosY = y ;

	// ����I��
	return 0 ;
}

// Live2D �̃��f���̊g�嗦��ݒ肷��
extern int NS_Live2D_Model_SetExtendRate( int Live2DModelHandle, float ExRateX, float ExRateY )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �l�̕ۑ�
	Model->ExRateX = ExRateX ;
	Model->ExRateY = ExRateY ;

	// ����I��
	return 0 ;
}

// Live2D �̃��f���̉�]��ݒ肷��
extern int NS_Live2D_Model_SetRotate( int Live2DModelHandle, float RotAngle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �l�̕ۑ�
	Model->RotAngle = RotAngle ;

	// ����I��
	return 0 ;
}

// Live2D �̃��f����`�悷��
extern int NS_Live2D_Model_Draw( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;
	int windowWidth, windowHeight ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// ���e�p�}�g���b�N�X 
	D_CubismMatrix44 *projection = new_D_CubismMatrix44() ;
	NS_GetGraphSize( NS_GetDrawScreen(), &windowWidth, &windowHeight ) ;
	projection->Scale( Model->ExRateX, Model->ExRateY * ( ( float )windowWidth / ( float )windowHeight ) ) ;
	if( Model->PosX != 0.0f || Model->PosY != 0.0f )
	{
		projection->Translate( Model->PosX / windowWidth * 2.0f, Model->PosY / windowHeight * 2.0f ) ;
	}
	if( Model->RotAngle != 0.0f )
	{
		projection->RotateRelative( -Model->RotAngle ) ;
	}

	// �`��
	Model->AppModel->Draw( *projection );

	delete_D_CubismMatrix44( projection ) ;

	// ����I��
	return 0 ;
}

// Live2D �̃��f���̎w��̃��[�V�������Đ�����
extern int NS_Live2D_Model_StartMotion( int Live2DModelHandle, const TCHAR *group, int no )
{
#ifdef UNICODE
	return Live2D_Model_StartMotion_WCHAR_T(
		Live2DModelHandle, group, no
	) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( group, return -1 )

	Result = Live2D_Model_StartMotion_WCHAR_T(
		Live2DModelHandle, UsegroupBuffer, no
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( group )

	return Result ;
#endif
}

// Live2D �̃��f���̎w��̃��[�V�������Đ�����
extern int NS_Live2D_Model_StartMotionWithStrLen( int Live2DModelHandle, const TCHAR *group, size_t groupLength, int no )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( group, groupLength, return -1 )
	Result = Live2D_Model_StartMotion_WCHAR_T( Live2DModelHandle, UsegroupBuffer, no ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( group )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( group, groupLength, return -1 )
	Result = Live2D_Model_StartMotion_WCHAR_T( Live2DModelHandle, UsegroupBuffer, no ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( group )
#endif
	return Result ;
}

extern int Live2D_Model_StartMotion_WCHAR_T( int Live2DModelHandle, const wchar_t *group, int no )
{
	LIVE2DCUBISM4MODEL * Model ;
	D_CubismMotionQueueEntryHandle Result ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
	{
		return -1 ;
	}

	// ���[�V�����̍Đ�
	WCHAR_T_TO_CHAR_STRING_ONE_BEGIN( group, return -1, DX_CHARCODEFORMAT_UTF8 )
	Result = Model->AppModel->StartMotion( UsegroupBuffer, no, D_CubismMotion_PriorityForce ) ;
	WCHAR_T_TO_CHAR_STRING_END( group )

	// �I��
	return Result == InvalidMotionQueueEntryHandleValue ? -1 : 0 ;
}

// Live2D �̃��f���̃��[�V�����Đ����I�����Ă��邩���擾����
extern int NS_Live2D_Model_IsMotionFinished( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// ���[�V�����̍Đ����I�����Ă��邩�ǂ����Ԃ��Đ�
	return Model->AppModel->_motionManager->IsFinished() ? TRUE : FALSE ;
}

// Live2D �̃��f���̎w��̕\��[�V�������Z�b�g����
extern int NS_Live2D_Model_SetExpression( int Live2DModelHandle, const TCHAR *expressionID )
{
#ifdef UNICODE
	return Live2D_Model_SetExpression_WCHAR_T(
		Live2DModelHandle, expressionID
	) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( expressionID, return -1 )

	Result = Live2D_Model_SetExpression_WCHAR_T(
		Live2DModelHandle, UseexpressionIDBuffer
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( expressionID )

	return Result ;
#endif
}

// Live2D �̃��f���̎w��̕\��[�V�������Z�b�g����
extern int NS_Live2D_Model_SetExpressionWithStrLen(	int Live2DModelHandle, const TCHAR *expressionID, size_t expressionIDLength )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( expressionID, expressionIDLength, return -1 )
	Result = Live2D_Model_SetExpression_WCHAR_T( Live2DModelHandle, UseexpressionIDBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( expressionID )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( expressionID, expressionIDLength, return -1 )
	Result = Live2D_Model_SetExpression_WCHAR_T( Live2DModelHandle, UseexpressionIDBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( expressionID )
#endif
	return Result ;
}

extern int Live2D_Model_SetExpression_WCHAR_T( int Live2DModelHandle, const wchar_t *expressionID )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �\��[�V�����̐ݒ�
	Model->AppModel->SetExpression( ( BYTE * )expressionID ) ;

	// ����I��
	return 0 ;
}

// �w��̍��W�� Live2D �̃��f���̎w��̓����蔻��̋�`�͈͓������肷��( TRUE:��`�͈͓�  FALSE:��`�͈͊O )
extern int NS_Live2D_Model_HitTest( int Live2DModelHandle, const TCHAR *hitAreaName, float x, float y )
{
#ifdef UNICODE
	return Live2D_Model_HitTest_WCHAR_T(
		Live2DModelHandle, hitAreaName, x, y
	) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( hitAreaName, return -1 )

	Result = Live2D_Model_HitTest_WCHAR_T(
		Live2DModelHandle, UsehitAreaNameBuffer, x, y
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( hitAreaName )

	return Result ;
#endif
}

// �w��̍��W�� Live2D �̃��f���̎w��̓����蔻��̋�`�͈͓������肷��( TRUE:��`�͈͓�  FALSE:��`�͈͊O )
extern int NS_Live2D_Model_HitTestWithStrLen( int Live2DModelHandle, const TCHAR *hitAreaName, size_t hitAreaNameLength, float x, float y )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( hitAreaName, hitAreaNameLength, return -1 )
	Result = Live2D_Model_HitTest_WCHAR_T( Live2DModelHandle, UsehitAreaNameBuffer, x, y ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( hitAreaName )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( hitAreaName, hitAreaNameLength, return -1 )
	Result = Live2D_Model_HitTest_WCHAR_T( Live2DModelHandle, UsehitAreaNameBuffer, x, y ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( hitAreaName )
#endif
	return Result ;
}

extern int Live2D_Model_HitTest_WCHAR_T( int Live2DModelHandle, const wchar_t *hitAreaName, float x, float y )
{
	LIVE2DCUBISM4MODEL * Model ;
	int windowWidth, windowHeight;
	float tx, ty ;
	bool Result ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �X�N���[�����W��Live2D���W�ɕϊ�
	NS_GetGraphSize( NS_GetDrawScreen(), &windowWidth, &windowHeight ) ;
	tx = ( ( x - Model->PosX ) - windowWidth  * 0.5f ) /  windowWidth * 2.0f / Model->ExRateX ;
	ty = ( ( y - Model->PosY ) - windowHeight * 0.5f ) / -windowWidth * 2.0f / Model->ExRateY ;
	if( Model->RotAngle != 0.0f )
	{
		float Sin, Cos ;
		float tmp ;
		_SINCOS_PLATFORM( Model->RotAngle, &Sin, &Cos ) ;
		tmp = Cos * tx - Sin * ty ;
		ty  = Sin * tx + Cos * ty ;
		tx  = tmp ;
	}

	// �\��[�V�����̐ݒ�
	WCHAR_T_TO_CHAR_STRING_ONE_BEGIN( hitAreaName, return -1, DX_CHARCODEFORMAT_UTF8 )
	Result = Model->AppModel->HitTest( UsehitAreaNameBuffer, tx, ty ) ;
	WCHAR_T_TO_CHAR_STRING_END( hitAreaName )

	return Result ? TRUE : FALSE ;
}

// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^�̐����擾����
extern int NS_Live2D_Model_GetParameterCount( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �l��Ԃ�
	return Model->AppModel->GetModel()->GetParameterCount() ;
}

// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^��ID���擾����
extern const TCHAR *NS_Live2D_Model_GetParameterId( int Live2DModelHandle, int index )
{
	LIVE2DCUBISM4MODEL * Model ;
	D_CubismIdHandle IdHandle ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

	// �l��Ԃ�
	IdHandle = Model->AppModel->GetModel()->GetParameterId( index ) ;
#ifdef UNICODE
	return ( wchar_t * )( IdHandle != NULL ? IdHandle->GetString().GetRawStringW() : NULL ) ;
#else
	return IdHandle != NULL ? IdHandle->GetString().GetRawStringA() : NULL ;
#endif
}

// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^���擾����
extern float NS_Live2D_Model_GetParameterValue( int Live2DModelHandle, const TCHAR *parameterId )
{
#ifdef UNICODE
	return Live2D_Model_GetParameterValue_WCHAR_T(
		Live2DModelHandle, parameterId
	) ;
#else
	float Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( parameterId, return -1 )

	Result = Live2D_Model_GetParameterValue_WCHAR_T(
		Live2DModelHandle, UseparameterIdBuffer
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( parameterId )

	return Result ;
#endif
}

// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^���擾����
extern float NS_Live2D_Model_GetParameterValueWithStrLen( int Live2DModelHandle, const TCHAR *parameterId, size_t parameterIdLength )
{
	float Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( parameterId, parameterIdLength, return -1 )
	Result = Live2D_Model_GetParameterValue_WCHAR_T( Live2DModelHandle, UseparameterIdBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( parameterId )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( parameterId, parameterIdLength, return -1 )
	Result = Live2D_Model_GetParameterValue_WCHAR_T( Live2DModelHandle, UseparameterIdBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( parameterId )
#endif
	return Result ;
}

extern float Live2D_Model_GetParameterValue_WCHAR_T( int Live2DModelHandle, const wchar_t *parameterId )
{
	LIVE2DCUBISM4MODEL * Model ;
	float Result = -1.0f ;
	int Count ;
	int i ;
	D_CubismModel *CModel ;
	D_CubismIdHandle IdHandle ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1.0f ;

	CModel = Model->AppModel->GetModel() ;
	Count = CModel->GetParameterCount() ;

	// �l��Ԃ�
	WCHAR_T_TO_CHAR_STRING_ONE_BEGIN( parameterId, return -1.0f, DX_CHARCODEFORMAT_UTF8 )
	IdHandle = LIVE2DSYS.s_cubismIdManager->FindId( UseparameterIdBuffer ) ;
	if( IdHandle != NULL )
	{
		for( i = 0 ; i < Count ; i ++ )
		{
			if( CModel->GetParameterId( i ) == IdHandle )
			{
				Result = Model->AppModel->GetModel()->GetParameterValue( i ) ;
				break ;
			}
		}
	}
	WCHAR_T_TO_CHAR_STRING_END( parameterId )

	return Result ;
}

// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^��ݒ肷��
extern int NS_Live2D_Model_SetParameterValue( int Live2DModelHandle, const TCHAR *parameterId, float value )
{
#ifdef UNICODE
	return Live2D_Model_SetParameterValue_WCHAR_T(
		Live2DModelHandle, parameterId, value
	) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( parameterId, return -1 )

	Result = Live2D_Model_SetParameterValue_WCHAR_T(
		Live2DModelHandle, UseparameterIdBuffer, value
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( parameterId )

	return Result ;
#endif
}

// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^��ݒ肷��
extern int NS_Live2D_Model_SetParameterValueWithStrLen( int Live2DModelHandle, const TCHAR *parameterId, size_t parameterIdLength, float value )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( parameterId, parameterIdLength, return -1 )
	Result = Live2D_Model_SetParameterValue_WCHAR_T( Live2DModelHandle, UseparameterIdBuffer, value ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( parameterId )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( parameterId, parameterIdLength, return -1 )
	Result = Live2D_Model_SetParameterValue_WCHAR_T( Live2DModelHandle, UseparameterIdBuffer, value ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( parameterId )
#endif
	return Result ;
}

extern int Live2D_Model_SetParameterValue_WCHAR_T( int Live2DModelHandle, const wchar_t *parameterId, float value )
{
	LIVE2DCUBISM4MODEL * Model ;
	int Count ;
	int i ;
	D_CubismModel *CModel ;
	D_CubismIdHandle IdHandle ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	CModel = Model->AppModel->GetModel() ;
	Count = CModel->GetParameterCount() ;

	// �p�����[�^��ݒ肷��
	WCHAR_T_TO_CHAR_STRING_ONE_BEGIN( parameterId, return -1, DX_CHARCODEFORMAT_UTF8 )
	IdHandle = LIVE2DSYS.s_cubismIdManager->FindId( UseparameterIdBuffer ) ;
	if( IdHandle != NULL )
	{
		for( i = 0 ; i < Count ; i ++ )
		{
			if( CModel->GetParameterId( i ) == IdHandle )
			{
				Model->AppModel->SetUserParameter( i, value ) ;
				break ;
			}
		}
	}
	WCHAR_T_TO_CHAR_STRING_END( parameterId )

	return 0 ;
}

// Live2D �̃��f���ɐݒ肳�ꂽ�����蔻��̐����擾����
extern int NS_Live2D_Model_GetHitAreasCount( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �l��Ԃ�
	return Model->AppModel->_modelSetting->GetHitAreasCount() ;
}

// Live2D �̃��f���̓����蔻��ɐݒ肳�ꂽ���O���擾����
extern const TCHAR *NS_Live2D_Model_GetHitAreaName( int Live2DModelHandle, int index )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

#ifdef UNICODE
	return ( wchar_t * )Model->AppModel->_modelSetting->GetHitAreaNameW( index ) ;
#else
	return Model->AppModel->_modelSetting->GetHitAreaNameA( index ) ;
#endif 
}

// Live2D �̃��f���̕������Z�ݒ�t�@�C���̖��O���擾����
extern const TCHAR *NS_Live2D_Model_GetPhysicsFileName( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

#ifdef UNICODE
	return ( wchar_t * )Model->AppModel->_modelSetting->GetPhysicsFileNameW() ;
#else
	return Model->AppModel->_modelSetting->GetPhysicsFileNameA() ;
#endif 
}

// Live2D �̃��f���̃p�[�c�؂�ւ��ݒ�t�@�C���̖��O���擾����
extern const TCHAR *NS_Live2D_Model_GetPoseFileName( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

#ifdef UNICODE
	return ( wchar_t * )Model->AppModel->_modelSetting->GetPoseFileNameW() ;
#else
	return Model->AppModel->_modelSetting->GetPoseFileNameA() ;
#endif 
}

// Live2D �̃��f���̕\��ݒ�t�@�C���̐����擾����
extern int NS_Live2D_Model_GetExpressionCount( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �l��Ԃ�
	return Model->AppModel->_modelSetting->GetExpressionCount() ;
}

// Live2D �̃��f���̕\��ݒ�t�@�C�������ʂ���ID���擾����
extern const TCHAR *NS_Live2D_Model_GetExpressionName( int Live2DModelHandle, int index )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

#ifdef UNICODE
	return ( wchar_t * )Model->AppModel->_modelSetting->GetExpressionNameW( index ) ;
#else
	return Model->AppModel->_modelSetting->GetExpressionNameA( index ) ;
#endif 
}

// Live2D �̃��f���̕\��ݒ�t�@�C���̖��O���擾����
extern const TCHAR *NS_Live2D_Model_GetExpressionFileName( int Live2DModelHandle, int index )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

#ifdef UNICODE
	return ( wchar_t * )Model->AppModel->_modelSetting->GetExpressionFileNameW( index ) ;
#else
	return Model->AppModel->_modelSetting->GetExpressionFileNameA( index ) ;
#endif 
}

// Live2D �̃��f���̃��[�V�����O���[�v�̐����擾����
extern int NS_Live2D_Model_GetMotionGroupCount( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �l��Ԃ�
	return Model->AppModel->_modelSetting->GetMotionGroupCount() ;
}

// Live2D �̃��f���̃��[�V�����O���[�v�̖��O���擾����
extern const TCHAR *NS_Live2D_Model_GetMotionGroupName( int Live2DModelHandle, int index )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

#ifdef UNICODE
	return ( wchar_t * )Model->AppModel->_modelSetting->GetMotionGroupNameW( index ) ;
#else
	return Model->AppModel->_modelSetting->GetMotionGroupNameA( index ) ;
#endif 
}

// Live2D �̃��f���̃��[�V�����O���[�v�Ɋ܂܂�郂�[�V�����̐����擾����
extern int NS_Live2D_Model_GetMotionCount( int Live2DModelHandle, const TCHAR *groupName )
{
#ifdef UNICODE
	return Live2D_Model_GetMotionCount_WCHAR_T(
		Live2DModelHandle, groupName
	) ;
#else
	int Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, return -1 )

	Result = Live2D_Model_GetMotionCount_WCHAR_T(
		Live2DModelHandle, UsegroupNameBuffer
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( groupName )

	return Result ;
#endif
}

// Live2D �̃��f���̃��[�V�����O���[�v�Ɋ܂܂�郂�[�V�����̐����擾����
extern int NS_Live2D_Model_GetMotionCountWithStrLen( int Live2DModelHandle, const TCHAR *groupName, size_t groupNameLength )
{
	int Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, groupNameLength, return -1 )
	Result = Live2D_Model_GetMotionCount_WCHAR_T( Live2DModelHandle, UsegroupNameBuffer ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( groupName )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, groupNameLength, return -1 )
	Result = Live2D_Model_GetMotionCount_WCHAR_T( Live2DModelHandle, UsegroupNameBuffer ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( groupName )
#endif
	return Result ;
}

extern int Live2D_Model_GetMotionCount_WCHAR_T( int Live2DModelHandle, const wchar_t *groupName )
{
	LIVE2DCUBISM4MODEL * Model ;
	int Result ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �l��Ԃ�
	WCHAR_T_TO_CHAR_STRING_ONE_BEGIN( groupName, return -1, DX_CHARCODEFORMAT_UTF8 )
	Result = Model->AppModel->_modelSetting->GetMotionCount( UsegroupNameBuffer ) ;
	WCHAR_T_TO_CHAR_STRING_END( groupName )

	return Result ;
}

// Live2D �̃��f���̃O���[�v���ƃC���f�b�N�X�l���烂�[�V�����t�@�C���̖��O���擾����
extern const TCHAR *NS_Live2D_Model_GetMotionFileName( int Live2DModelHandle, const TCHAR *groupName, int index )
{
#ifdef UNICODE
	return Live2D_Model_GetMotionFileName_WCHAR_T(
		Live2DModelHandle, groupName, index
	) ;
#else
	const TCHAR *Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, return NULL )

	Result = Live2D_Model_GetMotionFileName_WCHAR_T(
		Live2DModelHandle, UsegroupNameBuffer, index
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( groupName )

	return Result ;
#endif
}

// Live2D �̃��f���̃O���[�v���ƃC���f�b�N�X�l���烂�[�V�����t�@�C���̖��O���擾����
extern const TCHAR *NS_Live2D_Model_GetMotionFileNameWithStrLen( int Live2DModelHandle, const TCHAR *groupName, size_t groupNameLength, int index )
{
	const TCHAR *Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, groupNameLength, return NULL )
	Result = Live2D_Model_GetMotionFileName_WCHAR_T( Live2DModelHandle, UsegroupNameBuffer, index ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( groupName )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, groupNameLength, return NULL )
	Result = Live2D_Model_GetMotionFileName_WCHAR_T( Live2DModelHandle, UsegroupNameBuffer, index ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( groupName )
#endif
	return Result ;
}

extern const TCHAR *Live2D_Model_GetMotionFileName_WCHAR_T( int Live2DModelHandle, const wchar_t *groupName, int index )
{
	LIVE2DCUBISM4MODEL * Model ;
	const TCHAR *Result ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

	WCHAR_T_TO_CHAR_STRING_ONE_BEGIN( groupName, return NULL, DX_CHARCODEFORMAT_UTF8 )
#ifdef UNICODE
	Result = ( wchar_t * )Model->AppModel->_modelSetting->GetMotionFileNameW( UsegroupNameBuffer, index ) ;
#else
	Result = Model->AppModel->_modelSetting->GetMotionFileNameA( UsegroupNameBuffer, index ) ;
#endif 
	WCHAR_T_TO_CHAR_STRING_END( groupName )

	return Result ;
}

// Live2D �̃��f���̃��[�V�����ɑΉ�����T�E���h�t�@�C���̖��O���擾����
extern const TCHAR *NS_Live2D_Model_GetMotionSoundFileName( int Live2DModelHandle, const TCHAR *groupName, int index )
{
#ifdef UNICODE
	return Live2D_Model_GetMotionSoundFileName_WCHAR_T(
		Live2DModelHandle, groupName, index
	) ;
#else
	const TCHAR *Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, return NULL )

	Result = Live2D_Model_GetMotionSoundFileName_WCHAR_T(
		Live2DModelHandle, UsegroupNameBuffer, index
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( groupName )

	return Result ;
#endif
}

// Live2D �̃��f���̃��[�V�����ɑΉ�����T�E���h�t�@�C���̖��O���擾����
extern const TCHAR *NS_Live2D_Model_GetMotionSoundFileNameWithStrLen( int Live2DModelHandle, const TCHAR *groupName, size_t groupNameLength, int index )
{
	const TCHAR * Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, groupNameLength, return NULL )
	Result = Live2D_Model_GetMotionSoundFileName_WCHAR_T( Live2DModelHandle, UsegroupNameBuffer, index ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( groupName )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, groupNameLength, return NULL )
	Result = Live2D_Model_GetMotionSoundFileName_WCHAR_T( Live2DModelHandle, UsegroupNameBuffer, index ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( groupName )
#endif
	return Result ;
}

extern const TCHAR *Live2D_Model_GetMotionSoundFileName_WCHAR_T( int Live2DModelHandle, const wchar_t *groupName, int index )
{
	LIVE2DCUBISM4MODEL * Model ;
	const TCHAR *Result ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

	WCHAR_T_TO_CHAR_STRING_ONE_BEGIN( groupName, return NULL, DX_CHARCODEFORMAT_UTF8 )
#ifdef UNICODE
	Result = ( wchar_t * )Model->AppModel->_modelSetting->GetMotionSoundFileNameW( UsegroupNameBuffer, index ) ;
#else
	Result = Model->AppModel->_modelSetting->GetMotionSoundFileNameA( UsegroupNameBuffer, index ) ;
#endif 
	WCHAR_T_TO_CHAR_STRING_END( groupName )

	return Result ;
}

// Live2D �̃��f���̃��[�V�����J�n���̃t�F�[�h�C���������Ԃ��擾����
extern float NS_Live2D_Model_GetMotionFadeInTimeValue( int Live2DModelHandle, const TCHAR *groupName, int index )
{
#ifdef UNICODE
	return Live2D_Model_GetMotionFadeInTimeValue_WCHAR_T(
		Live2DModelHandle, groupName, index
	) ;
#else
	float Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, return -1.0f )

	Result = Live2D_Model_GetMotionFadeInTimeValue_WCHAR_T(
		Live2DModelHandle, UsegroupNameBuffer, index
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( groupName )

	return Result ;
#endif
}

// Live2D �̃��f���̃��[�V�����J�n���̃t�F�[�h�C���������Ԃ��擾����
extern float NS_Live2D_Model_GetMotionFadeInTimeValueWithStrLen( int Live2DModelHandle, const TCHAR *groupName, size_t groupNameLength, int index )
{
	float Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, groupNameLength, return -1.0f )
	Result = Live2D_Model_GetMotionFadeInTimeValue_WCHAR_T( Live2DModelHandle, UsegroupNameBuffer, index ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( groupName )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, groupNameLength, return -1.0f )
	Result = Live2D_Model_GetMotionFadeInTimeValue_WCHAR_T( Live2DModelHandle, UsegroupNameBuffer, index ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( groupName )
#endif
	return Result ;
}

extern float Live2D_Model_GetMotionFadeInTimeValue_WCHAR_T(	int Live2DModelHandle, const wchar_t *groupName, int index )
{
	LIVE2DCUBISM4MODEL * Model ;
	float Result ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1.0f ;

	// �l��Ԃ�
	WCHAR_T_TO_CHAR_STRING_ONE_BEGIN( groupName, return -1.0f, DX_CHARCODEFORMAT_UTF8 )
	Result = Model->AppModel->_modelSetting->GetMotionFadeInTimeValue( UsegroupNameBuffer, index ) ;
	WCHAR_T_TO_CHAR_STRING_END( groupName )

	return Result ;
}

// Live2D �̃��f���̃��[�V�����I�����̃t�F�[�h�A�E�g�������Ԃ��擾����
extern float NS_Live2D_Model_GetMotionFadeOutTimeValue( int Live2DModelHandle, const TCHAR *groupName, int index )
{
#ifdef UNICODE
	return Live2D_Model_GetMotionFadeOutTimeValue_WCHAR_T(
		Live2DModelHandle, groupName, index
	) ;
#else
	float Result ;

	TCHAR_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, return -1.0f )

	Result = Live2D_Model_GetMotionFadeOutTimeValue_WCHAR_T(
		Live2DModelHandle, UsegroupNameBuffer, index
	) ;

	TCHAR_TO_WCHAR_T_STRING_END( groupName )

	return Result ;
#endif
}

// Live2D �̃��f���̃��[�V�����I�����̃t�F�[�h�A�E�g�������Ԃ��擾����
extern float NS_Live2D_Model_GetMotionFadeOutTimeValueWithStrLen( int Live2DModelHandle, const TCHAR *groupName, size_t groupNameLength, int index )
{
	float Result ;
#ifdef UNICODE
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, groupNameLength, return -1.0f )
	Result = Live2D_Model_GetMotionFadeOutTimeValue_WCHAR_T( Live2DModelHandle, UsegroupNameBuffer, index ) ;
	WCHAR_T_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( groupName )
#else
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_ONE_BEGIN( groupName, groupNameLength, return -1.0f )
	Result = Live2D_Model_GetMotionFadeOutTimeValue_WCHAR_T( Live2DModelHandle, UsegroupNameBuffer, index ) ;
	TCHAR_STRING_WITH_STRLEN_TO_WCHAR_T_STRING_END( groupName )
#endif
	return Result ;
}

extern float Live2D_Model_GetMotionFadeOutTimeValue_WCHAR_T( int Live2DModelHandle, const wchar_t *groupName, int index )
{
	LIVE2DCUBISM4MODEL * Model ;
	float Result ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1.0f ;

	// �l��Ԃ�
	WCHAR_T_TO_CHAR_STRING_ONE_BEGIN( groupName, return -1.0f, DX_CHARCODEFORMAT_UTF8 )
	Result = Model->AppModel->_modelSetting->GetMotionFadeOutTimeValue( UsegroupNameBuffer, index ) ;
	WCHAR_T_TO_CHAR_STRING_END( groupName )

	return Result ;
}

// Live2D �̃��f���̃��[�U�f�[�^�̃t�@�C�������擾����
extern const TCHAR *NS_Live2D_Model_GetUserDataFile( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

#ifdef UNICODE
	return ( wchar_t * )Model->AppModel->_modelSetting->GetUserDataFileW() ;
#else
	return Model->AppModel->_modelSetting->GetUserDataFileA() ;
#endif 
}

// Live2D �̃��f���̖ڃp�`�Ɋ֘A�t����ꂽ�p�����[�^�̐����擾����
extern int NS_Live2D_Model_GetEyeBlinkParameterCount( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �l��Ԃ�
	return Model->AppModel->_modelSetting->GetEyeBlinkParameterCount() ;
}

// Live2D �̃��f���̖ڃp�`�Ɋ֘A�t����ꂽ�p�����[�^��ID���擾����
extern const TCHAR *NS_Live2D_Model_GetEyeBlinkParameterId( int Live2DModelHandle, int index )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

#ifdef UNICODE
	return ( wchar_t * )Model->AppModel->_modelSetting->GetEyeBlinkParameterId( index )->GetString().GetRawStringW() ;
#else
	return Model->AppModel->_modelSetting->GetEyeBlinkParameterId( index )->GetString().GetRawStringA() ;
#endif 
}

// Live2D �̃��f���̃��b�v�V���N�Ɋ֘A�t����ꂽ�p�����[�^�̐����擾����
extern int NS_Live2D_Model_GetLipSyncParameterCount( int Live2DModelHandle )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return -1 ;

	// �l��Ԃ�
	return Model->AppModel->_modelSetting->GetLipSyncParameterCount() ;
}

// Live2D �̃��f���̃��b�v�V���N�Ɋ֘A�t����ꂽ�p�����[�^��ID���擾����
extern const TCHAR *NS_Live2D_Model_GetLipSyncParameterId( int Live2DModelHandle, int index )
{
	LIVE2DCUBISM4MODEL * Model ;

	// �G���[����
	if( LIVE2DCUBISM4MODELCHK( Live2DModelHandle, Model ) )
		return NULL ;

#ifdef UNICODE
	return ( wchar_t * )Model->AppModel->_modelSetting->GetLipSyncParameterId( index )->GetString().GetRawStringW() ;
#else
	return Model->AppModel->_modelSetting->GetLipSyncParameterId( index )->GetString().GetRawStringA() ;
#endif 
}








#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_LIVE2D_CUBISM4
