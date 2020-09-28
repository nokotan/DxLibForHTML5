// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android��p�֐��v���g�^�C�v�錾�p�w�b�_�t�@�C��
// 
// 				Ver 3.22a
// 
// -------------------------------------------------------------------------------

#ifndef DX_FUNCTIONANDROID_H
#define DX_FUNCTIONANDROID_H

// �C���N���[�h ------------------------------------------------------------------
#include <android/native_activity.h>
#include <android/window.h>

// ��`---------------------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE


// �A�v���Ŏg�p���Ă��� NativeActivity ���擾����
extern const ANativeActivity *GetNativeActivity( void ) ;

// Android �� API���x�����擾����
extern int GetAndroidAPILevel( void ) ;

// �\�t�g�̃f�[�^�ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetInternalDataPath( TCHAR *PathBuffer, int PathBufferBytes ) ;

// �\�t�g�̊O���f�[�^�ۑ��p�̃f�B���N�g���p�X���擾����
// PathBuffer : �p�X��ۑ�����o�b�t�@
// PathBufferBytes : �p�X��ۑ�����o�b�t�@�̃T�C�Y( �P�ʁF�o�C�g )
// PathIndex : �O���f�[�^�ۑ��p�̃f�B���N�g���p�X�̔ԍ�( ��������ꍇ������̂� )
// IsRemovableFlag : PathIndex �Ŏw�肵���p�X�����O���\�ȃf�o�C�X���ǂ�����ۑ����� int�^�ϐ��̃A�h���X( �i�[���ꂽ�l�@TRUE:���O���\( SD�J�[�h�� )  FALSE:���O���s�\( �����X�g���[�W�� ) )
extern int GetExternalDataPath( TCHAR *PathBuffer, int PathBufferBytes, int PathIndex = 0, int *IsRemovableFlag = NULL ) ;

// �\�t�g�̊O���f�[�^�ۑ��p�̃f�B���N�g���p�X�̐����擾����
extern int GetExternalDataPathNum( void ) ;

// �[���ɐݒ肳��Ă��錾����擾����( �߂�l�@-1�F�G���[�@0�ȏ�F���ꖼ������̊i�[�ɕK�v�ȃo�C�g�� )
extern int GetLanguage( TCHAR *StringBuffer, int StringBufferSize ) ;

// �[���ɐݒ肳��Ă��鍑���擾����( �߂�l�@-1�F�G���[�@0�ȏ�F����������̊i�[�ɕK�v�ȃo�C�g�� )
extern int GetCountry( TCHAR *StringBuffer, int StringBufferSize ) ;

// �����������擾����
// TotalMemory : ���������e�ʂ�������ϐ�( �P�ʁFbyte )�A( ���̎擾���s�v�ȏꍇ�� NULL ��n�� )
// FreeMrmoyy : �󂫃������e�ʂ�������ϐ�( �P�ʁFbyte )�A( ���̎擾���s�v�ȏꍇ�� NULL ��n�� )
// UseMemory : �A�v�����g�p���Ă��郁�����e�ʂ�������ϐ�( �P��:byte )�A( ���̎擾���s�v�ȏꍇ�� NULL ��n�� )�A( �g�p�������ʂ̎擾�͔��ɏ������ׂ������̂ŁA�s�v�ȏꍇ�͕K�� NULL ��n���悤�ɂ��Ă������� )
extern int GetAndroidMemoryInfo( LONGLONG *TotalMemory, LONGLONG *FreeMemory, LONGLONG *UseMemory ) ;

// �f�B�X�v���C�̉𑜓x���擾����
extern int GetAndroidDisplayResolution( int *SizeX, int *SizeY ) ;

// �f�B�X�v���C��{�̐ݒ�ɏ]���Ď��Ԍo�߂ŃX���[�v��ԂɂȂ邱�Ƃ������邩�ǂ�����ݒ肷��( Flag  TRUE = �X���[�v��ԂɂȂ邱�Ƃ������Ȃ�  FALSE = �X���[�v��Ԃ�������( �f�t�H���g ) )
extern int SetKeepScreenOnFlag( int Flag ) ;

// �����x�Z���T�[�̃x�N�g���l���擾����
extern VECTOR GetAccelerometerVector( void ) ;

// �Z���T�[���瓾������p���擾����
// �c����( �n�ʂɑ΂��Ē[���𐂒��Ɏ�������� )�̏ꍇ�ɐ������l���擾�ł��܂�
// �߂�l�� x:���p( �P�ʁF���W�A��  0.0f:�k  ��/2.0f:��  -��/2.0f:��  -�� or ��:�� )
// �߂�l�� y:�O��̌X��( �P�ʁF���W�A��  0.0f:�[�����c�����Ő���( �t���܂Ő����̏ꍇ�܂� )�̏��  ��/2.0f:�O��������90�x�|�������( ��ʂ���������Ă����� )  -��/2.0f:���������90�x�|�������( ��ʂ��n�ʂ������Ă����� ) )
// �߂�l�� z:���E�̌X��( �P�ʁF���W�A��  0.0f:�[�����c�����Ő����̏��  ��/2.0f:�E������90�x�|�������  -��/2.0f:��������90�x�|�������  -�� or ��:�[�����㉺�������܂Ő����̏�� )
extern VECTOR GetOrientationVector( void ) ;

// �Z���T�[�̃x�N�g���l���擾����
extern VECTOR GetAndroidSensorVector( int SensorType /* DX_ANDROID_SENSOR_ACCELEROMETER �Ȃ� */ ) ;

// �Z���T�[���L�����ǂ������擾����( �߂�l�@TRUE�F�L���@FALSE�F���� )
extern int CheckAndroidSensor( int SensorType /* DX_ANDROID_SENSOR_ACCELEROMETER �Ȃ� */ ) ;



// �U���@�\�֌W( �g�p����ɂ� AndroidManifest.xml �� <uses-permission android:name="android.permission.VIBRATE" /> ������������K�v������܂� )

// �U���@�\�����邩�擾����( �߂�l�@TRUE : �U���@�\����  FALSE : �U���@�\�Ȃ� )
extern int Vibrator_hasVibrator( void ) ;

// �U���@�\�ɐU������( �U���̋������� )�@�\�����邩�ǂ������擾����( �߂�l�@TRUE : �U�����䂪�ł���  FALSE : �U������͂ł��Ȃ� )
extern int Vibrator_hasAmplitudeControl( void ) ;

// �U�����J�n����
// Milliseconds : �U�������鎞��( �P�ʁF�~���b )
// Amplitude : �U���̋���( 0( �U���Ȃ� ) �` 255( �ő�U�� ) )�A�U���̋����̐���ɑΉ����Ă��Ȃ��ꍇ�͖�������܂�
extern int Vibrator_vibrate( int Milliseconds, int Amplitude ) ;

// �U���p�^�[���t���̐U�����J�n����
// Timings : �U���p�^�[�����`���鎞��( �P�ʁF�~���b )�̔z��( Timings[0]:�U�����J�n����܂ł̑҂����ԁATimings[1]:�U���������鎞�ԁATimings[2]:�U�����~���Ă��鎞�ԁATimings[3]:�U���������鎞�ԁATimings[4]:�U�����~���Ă��鎞�ԁ@�@�ȉ��J��Ԃ� )
// TimingsLength : Timings �̔z��̒���
// Repeat : �U���p�^�[�����J��Ԃ��ꍇ�̔z��̗v�f�ԍ�( ��@0=�ŏ�����J��Ԃ�  1:�z��v�f��1����J��Ԃ� )�A-1 �ŌJ��Ԃ�����
extern int Vibrator_vibrate_with_OnOffTimings( int *Timings, int TimingsLength, int Repeat ) ;

// �U������t��( �U���̋����w��t�� )�U�����J�n����( Vibrator_hasAmplitudeControl �̖߂�l�� TRUE �̏ꍇ�̂ݎg�p�\ )
// Timings : �U���̋�����ύX����^�C�~���O( �P�ʁF�~���b )�̔z��
// Amplitudes : �U���̋���( 0( �U���Ȃ� ) �` 255( �ő�U�� ) )�̔z��
// ArrayLength : Timings �� Amplitudes �̔z��̒���( �z��̒����͂ǂ���������ł���K�v������܂� )
// Repeat : Timings �� Amplitudes �Ŏ������U���p�^�[�����J��Ԃ��ꍇ�̔z��̗v�f�ԍ�( ��@0=�ŏ�����J��Ԃ�  1:�z��v�f��1����J��Ԃ� )�A-1 �ŌJ��Ԃ�����
extern int Vibrator_vibrate_with_Amplitudes( int *Timings, int *Amplitudes, int ArrayLength, int Repeat ) ;

// �U���𒆒f����
extern int Vibrator_cancel( void ) ;



// �j����T�Ɋւ�������擾����
// DayOfWeek : �j��( 1:���j�� 2:���j�� 3:�Ηj�� 4:���j�� 5:�ؗj�� 6:���j�� 7:�y�j�� )
// WeekOfMonth : �����������̉��T�ڂȂ̂��̒l( 1:�P�T��  2:�Q�T��  3:�R�T��  4:�S�T��  5:�T�T�� )
// DayOfWeekInMonth : �����̗j������������ڂɓ����邩�A�̒l( 1:�P���  2:�Q���  3:�R���  4:�S��� ... )
extern int GetAndroidWeekInfo( int *DayOfWeek, int *WeekOfMonth, int *DayOfWeekInMonth ) ;

// res/values/strings.xml �� string ���\�[�X���擾����
// ValueName�Fstring ���
// StringBuffer�FValueName ��������������i�[����o�b�t�@�̐擪�A�h���X
// StringBufferBytes�FStringBuffer �̃T�C�Y( �P�ʁF�o�C�g )
// �߂�l�@�@-1�F�w��� string ���͖��������@�@-1�ȊO�FStringBuffer �ɕK�v�ȃo�b�t�@�̃T�C�Y( �P�ʁF�o�C�g )
extern int GetAndroidResource_Strings_String(           const TCHAR *ValueName,                         TCHAR *StringBuffer, int StringBufferBytes ) ;
extern int GetAndroidResource_Strings_StringWithStrLen( const TCHAR *ValueName, size_t ValueNameLength, TCHAR *StringBuffer, int StringBufferBytes ) ;

// AndroidManifest.xml �ɏ����ꂽ <meta-data android:name="test0" android:value="abcde" /> �Ȃǂ̃��^�f�[�^�̕�������擾����
// ValueName�F���^�f�[�^��
// StringBuffer�FValueName ��������������i�[����o�b�t�@�̐擪�A�h���X
// StringBufferBytes�FStringBuffer �̃T�C�Y( �P�ʁF�o�C�g )
// �߂�l�@�@-1�F�w��̃��^�f�[�^�͖��������@�@-1�ȊO�FStringBuffer �ɕK�v�ȃo�b�t�@�̃T�C�Y( �P�ʁF�o�C�g )
extern int GetAndroidMetaData_String(           const TCHAR *ValueName,                         TCHAR *StringBuffer, int StringBufferBytes ) ;
extern int GetAndroidMetaData_StringWithStrLen( const TCHAR *ValueName, size_t ValueNameLength, TCHAR *StringBuffer, int StringBufferBytes ) ;

// AndroidManifest.xml �ɏ����ꂽ <meta-data android:name="bool0" android:value="true" /> �Ȃǂ� Boolean�^�̃��^�f�[�^���擾����
// ValueName�F���^�f�[�^��
// �߂�l�@�@-1�F�w��̃��^�f�[�^�͖��������@�@TRUE�F�w��̃��^�f�[�^�� true ������   FALSE�F�w��̃��^�f�[�^�� false ������
// extern int GetAndroidMetaData_Boolean(           const TCHAR *ValueName                         ) ;
// extern int GetAndroidMetaData_BooleanWithStrLen( const TCHAR *ValueName, size_t ValueNameLength ) ;

// �ʒm�𔭍s����
// Title         : �^�C�g��
// SubTitle      : �T�u�^�C�g��
// Icon          : �A�C�R�� ( -1 �Ńf�t�H���g�̃A�C�R�� )
// ShowWhen      : �ʒm������\�����邩 ( TRUE : �\������  FALSE : �\�����Ȃ� )
// AutoCancel    : �ʒm���^�b�v���ꂽ��ʒm���폜���邩 ( TRUE : �^�b�v���ꂽ��ʒm���폜����   FALSE : Cancel �����܂Œʒm���폜���Ȃ� )
// NotifyID      : �ʒmID
// Vibrate       : �U���p�^�[���p�� int�^�z��( ���Ԃ̒P�ʂ̓~���b )�ANULL �̏ꍇ�͐U���Ȃ�( Vibrate[0]:�U����~����  Vibrate[1]:�U������  Vibrate[2]:�U����~����  Vibrate[3]:�U������  ... �ȉ��J��Ԃ� )
// VibrateLength : Vibrate �z��̗v�f��
// LightColor    : �ʒm���̃��C�g�̐F( GetColor �Ŏ擾 )�ALightOnTime �� LightOffTime �� 0 �̏ꍇ�̓��C�g�̓_������
// LightOnTime   : ���C�g�̓_������( �P�ʁF�~���b )
// LightOffTime  : ���C�g�̏�������( �P�ʁF�~���b )
extern int AndroidNotification(
	const TCHAR *Title, const TCHAR *SubTitle, int Icon = -1, int ShowWhen = TRUE,
	int AutoCancel = TRUE, int NotifyId = 0, int *Vibrate = NULL, int VibrateLength = 0,
	unsigned int LightColor = 0, int LightOnTime = 0, int LightOffTime = 0 ) ;
extern int AndroidNotificationWithStrLen(
	const TCHAR *Title, size_t TitleLength, const TCHAR *SubTitle, size_t SubTitleLength, int Icon = -1, int ShowWhen = TRUE,
	int AutoCancel = TRUE, int NotifyId = 0, int *Vibrate = NULL, int VibrateLength = 0,
	unsigned int LightColor = 0, int LightOnTime = 0, int LightOffTime = 0 ) ;

// �ʒm���L�����Z������
// NotifyID : �ʒmID
extern int AndroidNotificationCancel( int NotifyId ) ;

// �S�Ă̒ʒm���L�����Z������
extern int AndroidNotificationCancelAll( void ) ;

// �w��� URL ���u���E�U�ŊJ��( BrowserAppPackageName �� BrowserAppClassName �� NULL �̏ꍇ�͕W���u���E�U�ŊJ�� )
// URL                   : �J��URL
// BrowserAppPackageName : �u���E�U�̃p�b�P�[�W��( NULL �ŕW���u���E�U )
// BrowserAppClassName   : �u���E�U�̃N���X��( NULL �ŕW���u���E�U )
extern int AndroidJumpURL(           const TCHAR *URL,                   const TCHAR *BrowserAppPackageName = NULL,                                         const TCHAR *BrowserAppClassName = NULL                                       ) ;
extern int AndroidJumpURLWithStrLen( const TCHAR *URL, size_t URLLength, const TCHAR *BrowserAppPackageName = NULL, size_t BrowserAppPackageNameLength = 0, const TCHAR *BrowserAppClassName = NULL, size_t BrowserAppClassNameLength = 0 ) ;

// Wifi �̓d�g���x���擾����( �߂�l�F�d�g�̋��x 0 �` 100 )
// ( �g�p����ɂ� AndroidManifest.xml �� <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" /> ������������K�v������܂� )
extern int GetWifiSignalLevel( void ) ;

// �A�v������A�N�e�B�u�ɂȂ����ۂɌĂ΂��R�[���o�b�N�֐���o�^����
extern int SetAndroidLostFocusCallbackFunction( void (* Callback )( void *Data ), void *CallbackData ) ;

// �A�v�����A�N�e�B�u�ɂȂ����ۂɌĂ΂��R�[���o�b�N�֐���o�^����
extern int SetAndroidGainedFocusCallbackFunction( void (* Callback )( void *Data ), void *CallbackData ) ;

// �A�v�����I�������ۂɁA�v���Z�X�����S�ɏI�����邩��ݒ肷��( KillProcessFlag  TRUE : �A�v�����I��������A�v���Z�X�����S�ɏI������  FALSE : �A�v�����I�����Ă��A�v���Z�X�͊��S�ɂ͏I������Ȃ�( �f�t�H���g ) )
extern int SetUseAndroidKillProcessFlag( int KillProcessFlag ) ;



// OpenGL �֌W�̏����擾����
extern int GetOpenGLInfo(
	TCHAR **Version = NULL,
	TCHAR **Renderer = NULL,
	TCHAR **Vendor = NULL,
	TCHAR ***ExtensionNames = NULL,
	TCHAR **Shader_Language_Version = NULL,
	int *Shader_Max_Vertex_Attribs = NULL,						// GL_MAX_VERTEX_ATTRIBS
	int *Shader_Max_Vertex_Uniform_Vectors = NULL,				// GL_MAX_VERTEX_UNIFORM_VECTORS
	int *Shader_Max_Varying_Vectors = NULL,						// GL_MAX_VARYING_VECTORS
	int *Shader_Max_Combined_Texture_Image_Units = NULL,		// GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
	int *Shader_Max_Vertex_Texture_Image_Units = NULL,			// GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
	int *Shader_Max_Texture_Image_Units = NULL,					// GL_MAX_TEXTURE_IMAGE_UNITS
	int *Shader_Max_Fragment_Uniform_Vectors = NULL				// GL_MAX_FRAGMENT_UNIFORM_VECTORS
) ;

// �O���t�B�b�N�n���h���̃e�N�X�`���I�u�W�F�N�g���擾����
extern unsigned int GetGraphOpenGLESTextureObject( int GrHandle ) ;

// �c�w���C�u�������s���� OpenGL ES �̐ݒ���ēx�s��( ����p�r )
extern int RefreshDxLibOpenGLESSetting( void ) ;




// �C�R���C�U�[�@�\���g�p���邩�ǂ�����ݒ肷��( DxLib_Init �Ăяo���O�̂ݎ��s�\ )
// UseFlag  TRUE:�g�p����  FALSE:�g�p���Ȃ�
extern int          SetUseEqualizer( int UseFlag ) ;

// �C�R���C�U�[�֌W�֐�
extern int			SearchEqualizerBandIndex( int Frequency ) ;							// �C�R���C�U�[�̗^����ꂽ���g���ɍł��e����^������g���ш���擾���܂�( �߂�l�@-1:�G���[  0�ȏ�F���g���ш�C���f�b�N�X )
extern int			GetEqualizerBandNum( void ) ;										// �C�R���C�U�[�Ɏw��ł�����g���ш�̐����擾����
extern int			SetEqualizerBandLevel( int BandIndex, int Level ) ;					// �^����ꂽ�C�R���C�U�[�̎��g���ш��^����ꂽ�Q�C���l�ɐݒ肵�܂�
extern int			GetEqualizerBandLevel( int BandIndex ) ;							// �C�R���C�U�[�̎w�肳�ꂽ���g���ш�̃Q�C���l���擾���܂�
extern int			GetEqualizerBandFreqRange( int BandIndex, int *pMin, int *pMax ) ;	// �C�R���C�U�[�̎w�肳�ꂽ���g���ш�̎��g���͈͂��擾���܂�( pMin �� pMax �ɍŏ����g���ƍő���g�����i�[����܂�( �P�ʁF�w���c ) )
extern int			GetEqualizerBandCenterFreq( int BandIndex ) ;						// �C�R���C�U�[�̎w�肳�ꂽ���g���ш�̒��S���g�����擾���܂�( �߂�l�@���S���g��( �P�ʁF�w���c ) )
extern int			GetEqualizerCurrentPreset( void ) ;									// �C�R���C�U�[�̌��݂̃v���Z�b�g���擾���܂�( �߂�l�@�v���Z�b�g�ԍ� )
extern int			GetEqualizerPresetNum( void ) ;										// �C�R���C�U�[�̃v���Z�b�g�̐����擾���܂�( �߂�l�@�v���Z�b�g�̐� )
extern const TCHAR *GetEqualizerPresetName( int PresetIndex ) ;							// �C�R���C�U�[�̃v���Z�b�g�����擾���܂�( �߂�l�@�v���Z�b�g���̕����񂪊i�[���ꂽ�������̈�̐擪�A�h���X )
extern int			SetUseEqualizerPreset( int PresetIndex ) ;							// �w�肵���v���Z�b�g�ɏ]���ăC�R���C�U�[��ݒ肵�܂�



#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_FUNCTIONANDROID_H

