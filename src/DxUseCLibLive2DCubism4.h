// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�W���b���C�u�����g�p�R�[�h�@Live2D Cubism4 �֌W�w�b�_�t�@�C��
// 
// 				Ver 3.24d
// 
// -------------------------------------------------------------------------------

/*

	DxUseCLibLive2DCubism4.cpp �� Live2D Cubism 4 SDK for Native �� Cubism Native Framework �y��
	Cubism Native Samples ���x�[�X�ƂȂ��Ă��āALive2D Open Software License ���K�p����܂��B
�@�@�@- Live2D Open Software License 
�@�@�@[���{��](http://www.live2d.com/eula/live2d-open-software-license-agreement_jp.html)
�@�@�@[English](http://www.live2d.com/eula/live2d-open-software-license-agreement_en.html)

*/

#ifndef DX_USECLIB_LIVE2DCUBISM4_H
#define DX_USECLIB_LIVE2DCUBISM4_H

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"

#ifndef DX_NON_LIVE2D_CUBISM4
#include "DxLib.h"
#include "DxHandle.h"
#include "DxThread.h"
#include "DxGraphics.h"
#include "DxBaseFunc.h"
#include "DxStatic.h"

// �}�N����` --------------------------------------------------------------------

// �N���X�E�\���́E�񋓌^��` ----------------------------------------------------

class D_CubismMotionQueueManager ;
class D_csmString ;

typedef void ( * csmLogFunctionP )( const char* message ) ;

typedef void( *D_CubismMotionEventFunction )( const D_CubismMotionQueueManager* caller, const D_csmString& eventValue, void* customData ) ;
typedef void* D_CubismMotionQueueEntryHandle ;
extern const D_CubismMotionQueueEntryHandle InvalidMotionQueueEntryHandleValue ;	// �����ȃ��[�V�����̎��ʔԍ��̒�`

// ���[�V�����̗D��x�萔
const int D_CubismMotion_PriorityNone = 0;
const int D_CubismMotion_PriorityIdle = 1;
const int D_CubismMotion_PriorityNormal = 2;
const int D_CubismMotion_PriorityForce = 3;

// �J���[�u�����f�B���O�̃��[�h
enum D_CubismBlendMode
{
	D_CubismBlendMode_Normal					= 0,		// �ʏ�
	D_CubismBlendMode_Additive					= 1,		// ���Z
	D_CubismBlendMode_Multiplicative			= 2,		// ��Z
} ;

// ���[�V�����J�[�u�̎��
enum D_CubismMotionCurveTarget
{
	D_CubismMotionCurveTarget_Model,						// ���f���ɑ΂���
	D_CubismMotionCurveTarget_Parameter,					// �p�����[�^�ɑ΂���
	D_CubismMotionCurveTarget_PartOpacity					// �p�[�c�̕s�����x�ɑ΂���
} ;

// ���[�V�����J�[�u�̃Z�O�����g�̎��
enum D_CubismMotionSegmentType
{
	D_CubismMotionSegmentType_Linear			= 0,		// ���j�A
	D_CubismMotionSegmentType_Bezier			= 1,		// �x�W�F�Ȑ�
	D_CubismMotionSegmentType_Stepped			= 2,		// �X�e�b�v
	D_CubismMotionSegmentType_InverseStepped	= 3			// �C���o�[�X�X�e�b�v
} ;

// Alignment constraints.
enum
{
	D_csmAlignofMoc								= 64,		// Necessary alignment for mocs (in bytes).
	D_csmAlignofModel							= 16		// Necessary alignment for models (in bytes).
} ;

// Bit masks for non-dynamic drawable flags.
enum
{
	D_csmBlendAdditive							= 1 << 0,	// Additive blend mode mask.
	D_csmBlendMultiplicative					= 1 << 1,	// Multiplicative blend mode mask.
	D_csmIsDoubleSided							= 1 << 2,	// Double-sidedness mask.
	D_csmIsInvertedMask							= 1 << 3	// Clipping mask inversion mode mask.
} ;


// Bit masks for dynamic drawable flags.
enum
{
	D_csmIsVisible								= 1 << 0,	// Flag set when visible.
	D_csmVisibilityDidChange					= 1 << 1,	// Flag set when visibility did change.
	D_csmOpacityDidChange						= 1 << 2,	// Flag set when opacity did change.
	D_csmDrawOrderDidChange						= 1 << 3,	// Flag set when draw order did change.
	D_csmRenderOrderDidChange					= 1 << 4,	// Flag set when render order did change.
	D_csmVertexPositionsDidChange				= 1 << 5	// Flag set when vertex positions did change.
} ;

// moc3 file format version.
enum
{
	D_csmMocVersion_Unknown						= 0,		// unknown
	D_csmMocVersion_30							= 1,		// moc3 file version 3.0.00 - 3.2.07
	D_csmMocVersion_33							= 2,		// moc3 file version 3.3.00 -
	D_csmMocVersion_40							= 3			// moc3 file version 4.0.00 -
} ;

#define CSM_STRING_SMALL_LENGTH					64
#define CSM_MAP_DEFAULT_SIZE					10
#define CSM_IDMANAGER_MAX_ID_NUM				65536


// ��`�`��(���W�E������float�l)���`����N���X
class D_csmRectF
{
public:
	D_csmRectF() ;																			// �R���X�g���N�^
	D_csmRectF( float x, float y, float w, float h ) ;										// �����t���R���X�g���N�^
	virtual ~D_csmRectF() ;																	// �f�X�g���N�^
	float						GetCenterX() const { return X + 0.5f * Width; }				// ��`������X���W���擾����
	float						GetCenterY() const { return Y + 0.5f * Height; }			// ��`������Y���W���擾����
	float						GetRight() const { return X + Width; }						// �E�[��X���W���擾����
	float						GetBottom() const { return Y + Height; }					// ���[��Y���W���擾����
	void						SetRect( D_csmRectF* r ) ;									// ��`�ɒl���Z�b�g����
	void						Expand( float w, float h ) ;								// ��`���������ɂ��ďc�����g�k����

	float						X ;							// ���[X���W
	float						Y ;							// ��[Y���W
	float						Width ;						// ��
	float						Height ;					// ����
} ;

// 2�����x�N�g���^
struct D_CubismVector2
{
	float X ;          // X���̒l
	float Y ;          // Y���̒l

	D_CubismVector2() : X( 0.0f ), Y( 0.0f ){}														// �R���X�g���N�^
	D_CubismVector2( float x, float y ) : X( x ), Y( y ){}											// �f�X�g���N�^
	friend D_CubismVector2		operator+( const D_CubismVector2& a, const D_CubismVector2& b ) ;	// �x�N�g���̉��Z
	friend D_CubismVector2		operator-( const D_CubismVector2& a, const D_CubismVector2& b ) ;	// �x�N�g���̌��Z
	friend D_CubismVector2		operator*( const D_CubismVector2& vector, const float scalar ) ;	// �x�N�g���̏�Z�i�x�N�g���l�ƃX�J���[�l�j
	friend D_CubismVector2		operator*( const float scalar, const D_CubismVector2& vector ) ;	// �x�N�g���̏�Z�i�X�J���[�l�ƃx�N�g���l�j
	friend D_CubismVector2		operator/( const D_CubismVector2& vector, const float scalar ) ;	// �x�N�g���̏��Z�i�x�N�g���l�ƃX�J���[�l�j
	const D_CubismVector2&		operator+=( const D_CubismVector2& rhs ) ;							// ���Z
	const D_CubismVector2&		operator-=( const D_CubismVector2& rhs ) ;							// ���Z
	const D_CubismVector2&		operator*=( const D_CubismVector2& rhs ) ;							// ��Z�i�x�N�g���l�j
	const D_CubismVector2&		operator/=( const D_CubismVector2& rhs ) ;							// ���Z�i�x�N�g���l�j
	const D_CubismVector2&		operator*=( const float scalar ) ;									// ��Z�i�X�J���[�l�j
	const D_CubismVector2&		operator/=( const float scalar ) ;									// ���Z�i�X�J���[�l�j
	bool						operator==( const D_CubismVector2& rhs ) const ;					// �������̊m�F�i���������H�j
	bool						operator!=( const D_CubismVector2& rhs ) const ;					// �������̊m�F�i�������Ȃ����H�j
	void						Normalize() ;														// ���K���̓K�p
	float						GetLength() const ;													// �x�N�g���̒����̎擾
	float						GetDistanceWith( D_CubismVector2 a ) const ;						// �x�N�g���̋����̎擾
	float						Dot( const D_CubismVector2& a ) const ;								// �h�b�g�ς̌v�Z
} ;

// Utility functions for csmVector2.
D_CubismVector2					operator+( const D_CubismVector2& a, const D_CubismVector2& b ) ;
D_CubismVector2					operator-( const D_CubismVector2& a, const D_CubismVector2& b ) ;
D_CubismVector2					operator*( const D_CubismVector2& vector, const float scalar ) ;
D_CubismVector2					operator*( const float scalar, const D_CubismVector2& vector ) ;
D_CubismVector2					operator/( const D_CubismVector2& vector, const float scalar ) ;

// ���l�v�Z�ȂǂɎg�p���郆�[�e�B���e�B�N���X
class D_CubismMath
{
public:
	static const float Pi;
	static float RangeF( float value, float min, float max ) ;								// �������̒l���ŏ��l�ƍő�l�͈̔͂Ɏ��߂��l��Ԃ�
	static float SinF( float x ){ float Sin, Cos ; _SINCOS( x, &Sin, &Cos ) ; return Sin ; }// �T�C���֐��̒l�����߂�
	static float CosF( float x ){ float Sin, Cos ; _SINCOS( x, &Sin, &Cos ) ; return Cos ; }// �R�T�C���֐��̒l�����߂�
	static float AbsF( float x ){ return x < 0.0f ? -x : x ; }								// ��Βl�̒l�����߂�
	static float SqrtF( float x ){ return _SQRT( x ) ; }									// ������(���[�g)�����߂�
	static float GetEasingSine( float value ) ;												// �C�[�W���O�������ꂽ�T�C�������߂�	
	static float Max( float l, float r ){ return ( l > r ) ? l : r ; }						// �傫�����̒l��Ԃ�
	static float Min( float l, float r ){ return ( l > r ) ? r : l ; }						// ���������̒l��Ԃ��B
	static float DegreesToRadian( float degrees ) ;											// �p�x�l�����W�A���l�ɕϊ����܂��B
	static float RadianToDegrees( float radian ) ;											// ���W�A���l���p�x�l�ɕϊ����܂��B
	static float DirectionToRadian( D_CubismVector2 from, D_CubismVector2 to ) ;			// 2�̃x�N�g�����烉�W�A���l�����߂܂��B
	static float DirectionToDegrees( D_CubismVector2 from, D_CubismVector2 to ) ;			// 2�̃x�N�g������p�x�l�����߂܂��B
	static D_CubismVector2 RadianToDirection( float totalAngle ) ;							// ���W�A���l������x�N�g���ɕϊ����܂��B

private:
	// private�R���X�g���N�^
	D_CubismMath() ;
} ;

// ������N���X
class D_csmString
{
public:
	D_csmString() ;																			// �R���X�g���N�^
	D_csmString( const D_csmString& s ) ;													// �����t���R���X�g���N�^
	D_csmString( const BYTE/*wchar_t*/ * c ) ;												// �����t���R���X�g���N�^
	D_csmString( const char * c ) ;															// �����t���R���X�g���N�^
	D_csmString( const char * c, int length ) ;												// �����t���R���X�g���N�^
	D_csmString( const char * c, int length, bool usePtr ) ;								// �����t���R���X�g���N�^
	virtual ~D_csmString() ;																// �f�X�g���N�^
	D_csmString&				operator=( const char* c ) ;								// =���Z�q�̃I�[�o�[���[�h( D_csmString�^ )
	bool						operator==( const D_csmString& s ) const ;					// ==���Z�q�̃I�[�o�[���[�h( D_csmString�^ )
	bool						operator==( const char* c ) const ;							// ==���Z�q�̃I�[�o�[���[�h( char�^ )
	D_csmString					operator+( const D_csmString& s ) const ;					// +���Z�q�̃I�[�o�[���[�h(D_csmString�^)
	D_csmString					operator+( const char* c ) const ;							// +���Z�q�̃I�[�o�[���[�h(char�^)
	D_csmString&				operator+=( const D_csmString& s ) ;						// +=���Z�q�̃I�[�o�[���[�h(D_csmString�^)
	D_csmString&				operator+=( const char* c ) ;								// +=���Z�q�̃I�[�o�[���[�h(char�^)
	D_csmString&				Append( const char* c, int length ) ;						// �����������ɒǉ�����
	D_csmString&				Append( int length, const char v ) ;						// �����T�C�Y���g�����ĕ����𖄂߂�
	const char *				GetRawString() const ;										// C���ꕶ����Ƃ��Ẵ|�C���^���擾����
	const char *				GetRawStringA() ;											// C���ꕶ����Ƃ��Ẵ|�C���^���擾����( �c�w���C�u�����̖߂�l�p )
	const BYTE/*wchar_t*/ *		GetRawStringW() ;											// C���ꕶ����Ƃ��Ẵ|�C���^���擾����( wchar_t�p )

protected:
	void						Initialize( const char* c, int length, bool usePtr ) ;		// D_csmString�C���X�^���X�̏������֐��B������̃Z�b�g�ƃn�b�V���R�[�h�̎Z�o���s���B
	int							Copy( const BYTE/*wchar_t*/ * c, int length ) ;				// ��������R�s�[����. �I�[��\0��ǉ�����
	int							Copy( const char* c, int length ) ;							// ��������R�s�[����. �I�[��\0��ǉ�����
	int							CalcHashcode( const char* c, int length ) ;					// �����񂩂�n�b�V���l�𐶐����ĕԂ�
	void						Clear() ;													// �|�C���^���������

private:
	bool						IsEmpty() const ;											// �����񂪋󂩂ǂ����H
	void						SetEmpty() ;												// ���������ɐݒ�
	char *						WritePointer() ;											// C���ꕶ����Ƃ��Ẵ|�C���^���擾����

	char *						_ptr ;						// �����^�z��̃|�C���^
	int							_length ;					// ���p�������i�������m�ۂ͍Ō��0�����邽��_length+1�j
	int							_hashcode ;					// �C���X�^���X�ɓ��Ă�ꂽ�n�b�V���l
	char						_small[ 64 ] ;				// ������̒�����64-1�����̏ꍇ�͂�������g�p

	bool						_enableA ;					// �c�w���C�u�����̖߂�l�p�̃f�[�^���L�����ǂ���
	char *						_ptrA ;						// �����^�z��̃|�C���^( �c�w���C�u�����̖߂�l�p )
	int							_lengthA ;					// ���p�������i�������m�ۂ͍Ō��0�����邽��_length+1�j( �c�w���C�u�����̖߂�l�p )
	char						_smallA[ 64 ] ;				// ������̒�����64-1�����̏ꍇ�͂�������g�p( �c�w���C�u�����̖߂�l�p )

	bool						_enableW ;					// wchar_t �p�̃f�[�^���L�����ǂ���
	BYTE/*wchar_t*/ *			_ptrW ;						// �����^�z��̃|�C���^( wchar_t�p )
	int							_lengthW ;					// ���p�������i�������m�ۂ͍Ō��0�����邽��_length+1�j( wchar_t�p )
	DWORD/*wchar_t*/			_smallW[ 64 ] ;				// ������̒�����64-1�����̏ꍇ�͂�������g�p( wchar_t�p )
} ;

// ������N���X( wchar_t�� )
class D_csmStringW
{
public:
	D_csmStringW() ;																		// �R���X�g���N�^
	D_csmStringW( const BYTE/*wchar_t*/ * c ) ;												// �����t���R���X�g���N�^
	D_csmStringW( const char* c ) ;															// �����t���R���X�g���N�^
	D_csmStringW( const BYTE/*wchar_t*/ * c, int length ) ;									// �����t���R���X�g���N�^
	D_csmStringW( const D_csmStringW& s ) ;													// �����t���R���X�g���N�^
	D_csmStringW( const BYTE/*wchar_t*/ * c, int length, bool usePtr ) ;						// �����t���R���X�g���N�^
	virtual ~D_csmStringW() ;																// �f�X�g���N�^
	D_csmStringW&				operator=( const D_csmStringW& s ) ;						// =���Z�q�̃I�[�o�[���[�h(D_csmStringW�^)
	D_csmStringW&				operator=( const BYTE/*wchar_t*/ * c ) ;					// =���Z�q�̃I�[�o�[���[�h(wchar_t�^)
	bool						operator==( const D_csmStringW& s ) const ;					// ==���Z�q�̃I�[�o�[���[�h(D_csmStringW�^)
	bool						operator==( const BYTE/*wchar_t*/ * c ) const ;				// ==���Z�q�̃I�[�o�[���[�h(wchar_t�^)
	bool						operator<( const D_csmStringW& s ) const ;					// <���Z�q�̃I�[�o�[���[�h(D_csmStringW�^)
	bool						operator<( const BYTE/*wchar_t*/ * c ) const ;				// <���Z�q�̃I�[�o�[���[�h(wchar_t�^)
	bool						operator>( const D_csmStringW& s ) const ;					// >���Z�q�̃I�[�o�[���[�h(D_csmStringW�^)
	bool						operator>( const BYTE/*wchar_t*/ * c ) const ;				// >���Z�q�̃I�[�o�[���[�h(wchar_t�^)
	D_csmStringW				operator+( const D_csmStringW& s ) const ;					// +���Z�q�̃I�[�o�[���[�h(D_csmStringW�^)
	D_csmStringW				operator+( const BYTE/*wchar_t*/ * c ) const ;				// +���Z�q�̃I�[�o�[���[�h(wchar_t�^)
	D_csmStringW&				operator+=( const D_csmStringW& s ) ;						// +=���Z�q�̃I�[�o�[���[�h(D_csmStringW�^)
	D_csmStringW&				operator+=( const BYTE/*wchar_t*/ * c ) ;					// +=���Z�q�̃I�[�o�[���[�h(wchar_t�^)
	D_csmStringW&				Append( const BYTE/*wchar_t*/ * c, int length ) ;			//  �����������ɒǉ�����
	D_csmStringW&				Append( int length, const DWORD/*wchar_t*/ v ) ;			// �����T�C�Y���g�����ĕ����𖄂߂�
	int							GetLength() const { return _length; }						// ������̒�����Ԃ�
	const BYTE/*wchar_t*/ *		GetRawString() const ;										// C���ꕶ����Ƃ��Ẵ|�C���^���擾����
	void						Clear() ;													// �|�C���^���������
	int							GetHashcode() ;												// �n�b�V���R�[�h���擾����

protected:
	void						Copy( const BYTE/*wchar_t*/ * c, int length ) ;				// ��������R�s�[����. �I�[��\0��ǉ�����
	void						Copy( const char* c, int length ) ;							// ��������R�s�[����. �I�[��\0��ǉ�����
	void						Initialize( const BYTE/*wchar_t*/ * c, int length, bool usePtr ) ;	// D_csmStringW�C���X�^���X�̏������֐��B������̃Z�b�g�ƃn�b�V���R�[�h�̎Z�o���s���B
	int							CalcHashcode( const BYTE/*wchar_t*/ * c, int length ) ;				// �����񂩂�n�b�V���l�𐶐����ĕԂ�

private:
	static int					s_totalInstanceNo ;			// �ʎZ�̃C���X�^���X�ԍ�
	BYTE/*wchar_t*/ *			_ptr ;						// �����^�z��̃|�C���^
	int							_length ;					// ���p�������i�������m�ۂ͍Ō��0�����邽��_length+1�j
	int							_hashcode ;					// �C���X�^���X�ɓ��Ă�ꂽ�n�b�V���l
	int							_instanceNo ;				// �C���X�^���X�Ɋ��蓖�Ă�ꂽ�ԍ�
	DWORD/*wchar_t*/ 			_small[ CSM_STRING_SMALL_LENGTH ] ;	// ������̒�����CSM_STRING_SMALL_LENGTH-1�����̏ꍇ�͂�������g�p 

	bool						IsEmpty() const ;											// �����񂪋󂩂ǂ����H
	void						SetEmpty() ;												// ���������ɐݒ�
	BYTE/*wchar_t*/ *			WritePointer() ;											// C���ꕶ����Ƃ��Ẵ|�C���^���擾����
} ;

class D_CubismIdManager ;

// �p�����[�^���E�p�[�c���EDrawable����ێ�
struct D_CubismId
{
	friend class D_CubismIdManager ;

	D_csmString&				GetString() { return _id ; }								// ID�����擾

private:
	D_CubismId(){}																			// �R���X�g���N�^
	D_CubismId( const char* id ){ _id = id ; }												// �R���X�g���N�^
	D_CubismId( const D_CubismId& c ) : _id( c._id ) {}
	~D_CubismId(){}																			// �f�X�g���N�^
	D_CubismId&					operator=( const D_CubismId& c ){ if( this != &c ){ _id = c._id ; } return *this ; }
	bool						operator==( const D_CubismId& c ) const { return ( _id == c._id ) ; }
	bool						operator!=( const D_CubismId& c ) const { return !( _id == c._id ) ; }

	D_csmString					_id ;														// ID��
} ;

typedef D_CubismId * D_CubismIdHandle ;

// �x�N�^�[�^�i�ϔz��^�j
template< class T >
class D_csmVector
{
public :
	D_csmVector() ;																			// �R���X�g���N�^
	D_csmVector( int initialCapacity, bool zeroClear = false ) ;							// �����t���R���X�g���N�^
	D_csmVector( const D_csmVector& c ){ Copy( c ) ; }										// �R�s�[�R���X�g���N�^
	virtual ~D_csmVector() ;																	// �f�X�g���N�^

	T*							GetPtr(){ return _ptr ; }									// �R���e�i�̐擪�A�h���X��Ԃ�
	T&							operator[]( int index ){ return _ptr[ index ]; }			// []���Z�q�̃I�[�o�[���[�h
	const T&					operator[]( int index ) const { return _ptr[ index ]; }		// []���Z�q�̃I�[�o�[���[�h( const)
	T&							At( int index ){ return _ptr[ index ] ;	}					// �C���f�b�N�X�Ŏw�肵���v�f��Ԃ�
	void						PushBack( const T& value, bool callPlacementNew = true ) ;	// PushBack����.�R���e�i�ɐV���ȗv�f��ǉ�����B
	void						Clear() ;													// �R���e�i�̑S�v�f���������
	unsigned int				GetSize() const { return _size ; }							// �R���e�i�̗v�f����Ԃ�
	void						Resize( int size, T value = T() ){ UpdateSize( size, value, true ) ; }	// vector#resize()�ɑ�������T�C�Y�ύX
	void						UpdateSize( int size, T value = T(), bool callPlacementNew = true ) ;	// vector#resize()�ɑ�������T�C�Y�ύX
	void						PrepareCapacity( int newSize ) ;							// �R���e�i�̃L���p�V�e�B���m�ۂ���

	class iterator ;			// D_csmVector<T>�̃C�e���[�^�̑O���錾

	void						Insert( iterator position, iterator begin, iterator end, bool callPlacementNew = true ) ;		// �R���e�i�ɃR���e�i�v�f��}������
	void						Assign( int newSize, T value = T(), bool callPlacementNew = true ) ;							// �R���e�i�̑S�v�f�ɑ΂��đ���������s���B
	bool						Remove( int index ) ;										// �R���e�i����C���f�b�N�X�Ŏw�肵���v�f���폜����

	// D_csmVector<T>�̃C�e���[�^
	class iterator
	{
		// D_csmVector<T>���t�����h�N���X�Ƃ���
		friend class D_csmVector ;

	public :
		iterator() : _index( 0 ) , _vector( NULL ){}										// �R���X�g���N�^
		iterator( D_csmVector< T > *v ) : _index( 0 ), _vector( v ){}						// �����t���R���X�g���N�^
		iterator( D_csmVector< T > *v, int idx ) : _index( idx ), _vector( v ){}			// �����t���R���X�g���N�^
		iterator&				operator=( const iterator& ite ){ _index = ite._index ; _vector = ite._vector ; return *this ; }	// =���Z�q�̃I�[�o�[���[�h
		iterator&				operator++(){ ++_index ; return *this ; }					// �O�u++���Z�q�̃I�[�o�[���[�h
		iterator&				operator--(){ --_index ; return *this ; }					// �O�u--���Z�q�̃I�[�o�[���[�h
		iterator				operator++( int ){ iterator iteold( _vector, _index++ ) ; return iteold ; }	// ��u++���Z�q�̃I�[�o�[���[�h( int�͌�u�p�̃_�~�[����)
		iterator				operator--( int ){ iterator iteold( _vector, _index-- ) ; return iteold ; }	// ��u--���Z�q�̃I�[�o�[���[�h( int�͌�u�p�̃_�~�[����)
		T&						operator*() const{ return _vector->_ptr[ _index ] ; }		// *���Z�q�̃I�[�o�[���[�h
		bool					operator!=( const iterator& ite ) const { return ( _index != ite._index ) || ( _vector != ite._vector ) ; }	// !=���Z�q�̃I�[�o�[���[�h

	public :
		int						_index ;					// �R���e�i�̃C���f�b�N�X�l
		D_csmVector< T >		*_vector ;					// �R���e�i�̎Q��
	} ;

	//D_csmVector<T>�̃C�e���[�^�iconst�j
	class const_iterator
	{
		// D_csmVector<T>���t�����h�N���X�Ƃ���
		friend class D_csmVector ;

	public :
		const_iterator() : _index( 0 ), _vector( NULL ){}									// �R���X�g���N�^
		const_iterator( const D_csmVector< T >* v ) : _index( 0 ), _vector( v ){}			// �����t���R���X�g���N�^
		const_iterator( const D_csmVector< T >* v, int idx ) : _index( idx ), _vector( v ){}	// �����t���R���X�g���N�^
		const_iterator&			operator=( const const_iterator& ite ){ _index = ite._index ; _vector = ite._vector ; return *this ; }	// =���Z�q�̃I�[�o�[���[�h
		const_iterator&			operator++(){ ++_index ; return *this ; }					// �O�u++���Z�q�̃I�[�o�[���[�h
		const_iterator&			operator--(){ --_index ; return *this ;	}					// �O�u--���Z�q�̃I�[�o�[���[�h
		const_iterator			operator++( int ){ const_iterator iteold( _vector, _index++ ) ; return iteold ; }	// ��u++���Z�q�̃I�[�o�[���[�h( int�͌�u�p�̃_�~�[����)
		const_iterator			operator--( int ){ const_iterator iteold( _vector, _index-- ) ; return iteold ; }	// ��u--���Z�q�̃I�[�o�[���[�h( int�͌�u�p�̃_�~�[����)
		T&						operator*() const { return _vector->_ptr[ _index] ; }		// *���Z�q�̃I�[�o�[���[�h
		bool					operator!=( const const_iterator& ite ) const { return ( _index != ite._index ) || ( _vector != ite._vector ) ; }	// !=���Z�q�̃I�[�o�[���[�h

	public:
		int						_index ;					// �R���e�i�̃C���f�b�N�X�l
		const D_csmVector< T >	*_vector ;					// �R���e�i�̃|�C���^
	} ;

	const iterator				Begin(){ iterator ite( this, 0 ) ; return ite ; }			// �R���e�i�̐擪�v�f��Ԃ�
	const iterator				End(){ iterator ite( this, _size ) ; return ite ; }			// �R���e�i�̏I�[�v�f��Ԃ�
	const const_iterator		Begin() const { const_iterator ite( this, 0 ) ; return ite ; }	// �R���e�i�̐擪�v�f��Ԃ�
	const const_iterator		End() const { const_iterator ite( this, _size ) ; return ite ; }	// �R���e�i�̏I�[�v�f��Ԃ�
	const iterator				Erase( const iterator& ite )								// �R���e�i����v�f���폜���đ��̗v�f���V�t�g����
	{
		int index = ite._index ;
		if( index < 0 || _size <= index ) return ite ;
		if( index < _size - 1 ) _MEMMOVE( &( _ptr[ index ] ), &( _ptr[ index + 1 ] ), sizeof( T ) * ( _size - index - 1 ) ) ;
		--_size ;
		iterator ite2( this, index ) ;
		return ite2 ;
	}
	const const_iterator		Erase( const const_iterator& ite )							// �R���e�i����v�f���폜���đ��̗v�f���V�t�g����
	{
		int index = ite._index ;
		if( index < 0 || _size <= index ) return ite ;
		if( index < _size - 1 ) _MEMMOVE( &( _ptr[ index ] ), &( _ptr[ index + 1 ] ), sizeof( T ) * ( _size - index - 1 ) ) ;
		--_size ;
		const_iterator ite2( this, index ) ;
		return ite2 ;
	}

	D_csmVector&				operator=( const D_csmVector& c ){ if( this != &c ){ Clear() ; Copy( c ) ; } return *this ; }	// �R�s�[�R���X�g���N�^

public:
	void						Copy( const D_csmVector& c ) ;	// D_csmVector<T>�̃R�s�[�֐�

	T*							_ptr ;						// �R���e�i�̐擪�A�h���X�i�|�C���^�j
	int							_size ;						// �R���e�i�̗v�f���i�T�C�Y�j
	int							_capacity ;					// �R���e�i�̃L���p�V�e�B
} ;

// Key-D_JsonValue�̃y�A���`����N���X
template< class _KeyT, class _ValT >
class D_csmPair
{
public:
	D_csmPair() : First(), Second() {}														// �R���X�g���N�^
	D_csmPair( const _KeyT& key ) : First( key ), Second() {}								// �����t���R���X�g���N�^
	D_csmPair( const _KeyT& key, const _ValT& value ) : First( key ), Second( value ) {}	// �����t���R���X�g���N�^
	virtual ~D_csmPair() {}																	// �f�X�g���N�^

	_KeyT						First ;						// Key�Ƃ��ėp����ϐ�
	_ValT						Second ;					// D_JsonValue�Ƃ��ėp����ϐ�
} ;

// �}�b�v�^
template< class _KeyT, class _ValT >
class D_csmMap
{
public:
	D_csmMap() ;																			// �R���X�g���N�^
	D_csmMap( int size ) ;																	// �����t���R���X�g���N�^
	virtual ~D_csmMap() ;																	// �f�X�g���N�^
	void						AppendKey( _KeyT& key ) ;									// �L�[��ǉ�����
	_ValT&						operator[]( _KeyT key ) ;									// �Y�����Z�q[key]�̃I�[�o�[���[�h
	const _ValT&				operator[]( _KeyT key ) const ;								// �Y�����Z�q[key]�̃I�[�o�[���[�h( const)
	bool						IsExist( _KeyT key ) ;										// �����œn����Key�����v�f�����݂��邩
	void						Clear() ;													// Key-D_JsonValue�̃|�C���^��S�ĉ������
	int							GetSize() const { return _size ; }							// �R���e�i�̃T�C�Y���擾����
	void						PrepareCapacity( int newSize, bool fitToSize ) ;			// �R���e�i�̃L���p�V�e�B���m�ۂ���

	// D_csmMap<T>�̃C�e���[�^
	class iterator
	{
		// D_csmMap<T>���t�����h�N���X�Ƃ���
		friend class D_csmMap;

	public:
		iterator() : _index( 0 ), _map( NULL ){}											// �R���X�g���N�^
		iterator( D_csmMap< _KeyT, _ValT >* v ) : _index( 0 ), _map( v ){}					// �����t���R���X�g���N�^
		iterator( D_csmMap< _KeyT, _ValT >* v, int idx ) : _index( idx ), _map( v ) {}		// �����t���R���X�g���N�^
		iterator&				operator=( const iterator& ite ){ _index = ite._index ; _map = ite._map ; return *this ; }	// =���Z�q�̃I�[�o�[���[�h
		iterator&				operator++(){ _index++ ; return *this ; }					// �O�u++���Z�q�̃I�[�o�[���[�h
		iterator&				operator--(){ _index-- ; return *this ; }					// �O�u--���Z�q�̃I�[�o�[���[�h
		iterator				operator++( int ){ iterator iteold( _map, _index++ ) ; return iteold ; }	// ��u++���Z�q�̃I�[�o�[���[�h( int�͌�u�p�̃_�~�[����)
		iterator				operator--( int ){ iterator iteold( _map, _index-- ) ; return iteold ; }	// ��u--���Z�q�̃I�[�o�[���[�h( int�͌�u�p�̃_�~�[����)
		D_csmPair< _KeyT, _ValT >& operator*() const { return _map->_keyValues[ _index ] ; }	// *���Z�q�̃I�[�o�[���[�h
		bool					operator!=( const iterator& ite ) const { return ( _index != ite._index ) || ( _map != ite._map ) ;	}	// !=���Z�q�̃I�[�o�[���[�h

	private:
		int						_index ;					// �R���e�i�̃C���f�b�N�X�l
		D_csmMap< _KeyT, _ValT >* _map ;					// �R���e�i�̃|�C���^
	} ;

	// D_csmMap<T>�̃C�e���[�^( const)
	class const_iterator
	{
		// D_csmMap<T>���t�����h�N���X�Ƃ���
		friend class D_csmMap;

	public:
		const_iterator() : _index( 0 ), _map( NULL ) {}										// �R���X�g���N�^
		const_iterator( const D_csmMap< _KeyT, _ValT >* v ) : _index( 0 ), _map( v ) {}		// �����t���R���X�g���N�^
		const_iterator( const D_csmMap< _KeyT, _ValT >* v, int idx ) : _index( idx ), _map( v ) {}	// �����t���R���X�g���N�^
		const_iterator&			operator=( const const_iterator& ite ){ _index = ite._index ; _map = ite._map ; return *this ; }	// =���Z�q�̃I�[�o�[���[�h
		const_iterator&			operator++(){ ++_index ; return *this ; }					// �O�u++���Z�q�̃I�[�o�[���[�h
		const_iterator&			operator--(){ --_index ; return *this ; }					// �O�u--���Z�q�̃I�[�o�[���[�h
		const_iterator			operator++( int ){ const_iterator iteold( _map, _index++ ) ; return iteold ; }	// ��u++���Z�q�̃I�[�o�[���[�h( int�͌�u�p�̃_�~�[����)
		const_iterator			operator--( int ){ const_iterator iteold( _map, _index-- ) ; return iteold ; }	// ��u--���Z�q�̃I�[�o�[���[�h( int�͌�u�p�̃_�~�[����)
		D_csmPair< _KeyT, _ValT >* operator->() const { return &_map->_keyValues[ _index ] ; }	// ->���Z�q�̃I�[�o�[���[�h
		D_csmPair< _KeyT, _ValT >& operator*() const { return _map->_keyValues[ _index ] ; }	// *���Z�q�̃I�[�o�[���[�h
		bool					operator!=( const const_iterator& ite ) const { return ( _index != ite._index ) || ( _map != ite._map ) ; }	// !=���Z�q�̃I�[�o�[���[�h

	private:
		int						_index ;					// �R���e�i�̃C���f�b�N�X�l
		const D_csmMap< _KeyT, _ValT >* _map ;				// �R���e�i�̃|�C���^( const)
	} ;

	const const_iterator		Begin() const { const_iterator ite( this, 0 ) ; return ite ; }	// �R���e�i�̐擪�v�f��Ԃ�
	const const_iterator		End() const { const_iterator ite( this, _size ) ; return ite ; }	// �R���e�i�̏I�[�v�f��Ԃ�
	const iterator				Erase( const iterator& ite )								// �R���e�i����v�f���폜����
	{
		int index = ite._index ;
		if( index < 0 || _size <= index ) return ite ;
		if( index < _size - 1 )
			_MEMMOVE( &( _keyValues[ index ] ), &( _keyValues[ index + 1 ] ), sizeof( D_csmPair< _KeyT, _ValT > ) * ( _size - index - 1 ) ) ;
		--_size ;
		iterator ite2( this, index ) ;
		return ite2 ;
	}
	const const_iterator		Erase( const const_iterator& ite )							// �R���e�i����v�f���폜����
	{
		int index = ite._index ;
		if( index < 0 || _size <= index ) return ite ;
		if( index < _size - 1 )
			_MEMMOVE( &( _keyValues[ index ] ), &( _keyValues[ index + 1 ] ), sizeof( D_csmPair< _KeyT, _ValT > ) * ( _size - index - 1 ) ) ;
		--_size ;
		const_iterator ite2( this, index ) ;
		return ite2 ;
	}

public:
	D_csmPair< _KeyT, _ValT > *	_keyValues ;				// Key-D_JsonValue�y�A�̔z��
	_ValT *						_dummyValuePtr ;			// ��̒l��Ԃ����߂̃_�~�[(static��templte��������邽�߃����o�Ƃ���j
	int							_size ;						// �R���e�i�̗v�f���i�T�C�Y�j
	int							_capacity ;					// �R���e�i�̃L���p�V�e�B
} ;

// ID���̊Ǘ�
class D_CubismIdManager
{
	friend struct D_CubismId ;

public:
	D_CubismIdManager() ;																	// �R���X�g���N�^
	~D_CubismIdManager() ;																	// �f�X�g���N�^
	void						RegisterIds( const char** ids, int count ) ;				// ID�������X�g����o�^
	void						RegisterIds( const D_csmVector< D_csmString >& ids ) ;		// ID�������X�g����o�^
	D_CubismId *				RegisterId( const char* id ) ;								// ID����o�^
	D_CubismId *				RegisterId( const D_csmString& id ) ;						// ID����o�^
	D_CubismId *				GetId( const D_csmString& id ) ;							// ID������ID���擾����
	D_CubismId *				GetId( const char* id ) ;									// ID������ID���擾����
	D_CubismId *				FindId( const char* id ) const ;							// ID������ID������
	bool						IsExist( const D_csmString& id ) const ;					// ID������ID�̊m�F
	bool						IsExist( const char* id ) const ;							// ID������ID�̊m�F

private:
	D_CubismIdManager( const D_CubismIdManager& ) ;
	D_CubismIdManager& operator=( const D_CubismIdManager& ) ;

	D_CubismId *				_ids[ CSM_IDMANAGER_MAX_ID_NUM ] ;							// �o�^����Ă���ID�̃��X�g
	volatile int				_idNum ;													// �o�^����Ă���ID�̐�
	DX_CRITICAL_SECTION			_criticalSection ;											// �N���e�B�J���Z�N�V����
} ;

class D_JsonValue ;
class D_JsonError ;
class D_JsonNullValue ;

#define D_CSM_JSON_ERROR_TYPE_MISMATCH            "D_JsonError:type mismatch"
#define D_CSM_JSON_ERROR_INDEX_OUT_OF_BOUNDS      "D_JsonError:index out of bounds"

// �p�[�X����JSON�G�������g�̗v�f�̊��N���X
class D_JsonValue
{
	friend class D_JsonArray ;

public:
	static D_JsonValue*			ErrorValue ;				// �ꎞ�I�ȕԂ�l�Ƃ��ĕԂ��G���[�BCubismFramework::Dispose()����܂ł�CSM_DELETE���Ȃ��B
	static D_JsonValue*			NullValue ;					// �ꎞ�I�ȕԂ�l�Ƃ��ĕԂ�NULL�BCubismFramework::Dispose()����܂ł�CSM_DELETE���Ȃ��B
	D_JsonValue() {}																		// �R���X�g���N�^
	virtual ~D_JsonValue() {}																// �f�X�g���N�^
	virtual D_csmString&		GetString( const D_csmString& defaultValue = "", const D_csmString& indent = "" ) = 0 ;// �v�f�𕶎���ŕԂ�(D_csmString�^)
	virtual const char*			GetRawString( const D_csmString& defaultValue = "", const D_csmString& indent = "" ) ;// �v�f�𕶎���ŕԂ�(char*)
	virtual const char*			GetRawStringA( const D_csmString& defaultValue = "", const D_csmString& indent = "" ) ;// �v�f�𕶎���ŕԂ�(�c�w���C�u�����p)
	virtual const BYTE/*wchar_t*/ *	GetRawStringW( const D_csmString& defaultValue = "", const D_csmString& indent = "" ) ;// �v�f�𕶎���ŕԂ�(wchar_t*)
	virtual int					ToInt( int defaultValue = 0 ) { return defaultValue ; }			// �v�f�𐔒l�^�ŕԂ�( int)
	virtual float				ToFloat( float defaultValue = 0.0f ) { return defaultValue ; }	// �v�f�𐔒l�^�ŕԂ�(float)
	virtual bool				ToBoolean( bool defaultValue = false ) { return defaultValue ; }	// �v�f��^�U�l�ŕԂ�(bool)
	virtual int					GetSize() { return 0; }											// �v�f��^�U�l�ŕԂ�(bool)
	virtual D_csmVector<D_JsonValue*>*				GetVector( D_csmVector<D_JsonValue*>* defaultValue = NULL ) { return defaultValue ; }		// �v�f���R���e�i�ŕԂ�(D_csmVector<D_JsonValue*>)
	virtual D_csmMap<D_csmString, D_JsonValue*>*	GetMap( D_csmMap<D_csmString, D_JsonValue*>* defaultValue = NULL ) { return defaultValue ; }	// �v�f���}�b�v�ŕԂ�(D_csmMap<D_csmString, D_JsonValue*>)
	virtual D_csmVector<D_csmString>&				GetKeys(){ return *s_dummyKeys ; }															// �}�b�v�̃L�[�ꗗ���R���e�i�ŕԂ�
	virtual D_JsonValue&		operator[]( int index )	;									// �Y�����Z�q[int]
	virtual D_JsonValue&		operator[]( const D_csmString& string )	;					// �Y�����Z�q[D_csmString]
	virtual D_JsonValue&		operator[]( const char* s )	;								// �Y�����Z�q[char*]
	virtual bool				IsError() { return false ; }								// D_JsonValue�̎�ނ��G���[�l�Ȃ�true�B
	virtual bool				IsNull() { return false ; }									// D_JsonValue�̎�ނ�NULL�l�Ȃ�true�B
	virtual bool				IsBool() { return false ; }									// D_JsonValue�̎�ނ��^�U�l�Ȃ�true�B
	virtual bool				IsFloat() { return false ; }								// D_JsonValue�̎�ނ����l�^�Ȃ�true�B
	virtual bool				IsString() { return false ; }								// D_JsonValue�̎�ނ�������Ȃ�true�B
	virtual bool				IsArray() { return false ; }								// D_JsonValue�̎�ނ��z��Ȃ�true�B
	virtual bool				IsMap() { return false ; }									// D_JsonValue�̎�ނ��}�b�v�^�Ȃ�true�B
	virtual bool				Equals( const D_csmString& /*value*/ ) { return false ; }	// �����̒l�Ɠ��������true�B
	virtual bool				Equals( const char* /*value*/ ) { return false ; }			// �����̒l�Ɠ��������true�B
	virtual bool				Equals( int /*value*/ ) { return false ; }					// �����̒l�Ɠ��������true�B
	virtual bool				Equals( float /*value*/ ) { return false ; }				// �����̒l�Ɠ��������true�B
	virtual bool				Equals( bool /*value*/ ) { return false ; }					// �����̒l�Ɠ��������true�B
	virtual bool				IsStatic() { return false ; }								// D_JsonValue�̒l���ÓI�Ȃ�true. �ÓI�Ȃ������Ȃ�
	virtual D_JsonValue*		SetErrorNotForClientCall( const char* /*errorStr*/ ) { return ErrorValue ; }// D_JsonValue�ɃG���[�l���Z�b�g����

	static void					StaticInitializeNotForClientCall() ;							//  �������p���\�b�h
	static void					StaticReleaseNotForClientCall() ;							// �����[�X�p���\�b�h
protected:
	D_csmString					_stringBuffer ;				// ������o�b�t�@

private:
	static D_csmVector<D_csmString>* s_dummyKeys ;			// �_�~�[�L�[
} ;

// Ascii�����̂ݑΉ������ŏ����̌y��JSON�p�[�T�B
class D_CubismJson
{
public:
	static D_CubismJson*		Create( const BYTE* buffer, size_t size ) ;					// �o�C�g�f�[�^���璼�ڃ��[�h���ăp�[�X����
	static void					Delete( D_CubismJson* instance ) ;							// �p�[�X����JSON�I�u�W�F�N�g�̉������
	D_JsonValue&				GetRoot() const ;											// �p�[�X����JSON�̃��[�g�v�f�̃|�C���^��Ԃ�
	const char*					GetParseError() const { return _error ; }					// �p�[�X���̃G���[�l��Ԃ�
	bool						CheckEndOfFile() const { return ( *_root )[ 1 ].Equals( "EOF" ) ; }// ���[�g�v�f�̎��̗v�f���t�@�C���̏I�[��������true��Ԃ�

protected:
	bool ParseBytes( const BYTE* buffer, int size ) ;// JSON�̃p�[�X�����s����
	D_csmString ParseString( const char* string, int length, int begin, int* outEndPos ) ;	// ���́u"�v�܂ł̕�������p�[�X����B������͊O���ŉ������K�v������B
	D_JsonValue* ParseObject( const char* buffer, int length, int begin, int* outEndPos ) ;	// JSON�̃I�u�W�F�N�g�G�������g���p�[�X����D_JsonValue�I�u�W�F�N�g��Ԃ�
	D_JsonValue* ParseArray( const char* buffer, int length, int begin, int* outEndPos ) ;	// JSON�̔z��G�������g���p�[�X����D_JsonValue�I�u�W�F�N�g��Ԃ�
	D_JsonValue* ParseValue( const char* buffer, int length, int begin, int* outEndPos ) ;	// JSON�G�������g����D_JsonValue(float,D_JsonString,D_JsonValue*,D_JsonArray,null,true,false)���p�[�X����G�������g�̏����ɉ����ē�����ParseString(), ParseObject(), ParseArray()���Ă�

private:
	D_CubismJson() ;																			// �R���X�g���N�^
	D_CubismJson( const BYTE* buffer, int length ) ;											// �����t���R���X�g���N�^
	virtual ~D_CubismJson() ;																// �f�X�g���N�^

	const char*					_error ;						// �p�[�X���̃G���[
	int							_lineCount ;					// �G���[�񍐂ɗp����s���J�E���g
	D_JsonValue*				_root ;						// �p�[�X���ꂽ���[�g�v�f
} ;

// �p�[�X����JSON�̗v�f��Double�l�Ƃ��Ĉ���
class D_JsonFloat : public D_JsonValue
{
public:
	D_JsonFloat( float v ) : D_JsonValue() { this->_value = v; }							// �R���X�g���N�^
	virtual ~D_JsonFloat() {}																// �f�X�g���N�^
	virtual bool				IsFloat() { return true ; }									// D_JsonValue�̎�ނ����l�^�Ȃ�true�B
	virtual D_csmString&		GetString( const D_csmString& defaultValue = "", const D_csmString& indent = "" ) ;	// �v�f�𕶎���ŕԂ�(D_csmString�^)
	virtual int					ToInt( int /*defaultValue*/ = 0 ) { return static_cast< int >( this->_value ) ; }	// �v�f�𐔒l�^�ŕԂ�( int)
	virtual float				ToFloat( float /*defaultValue*/ = 0 ) { return this->_value ; }						// �v�f�𐔒l�^�ŕԂ�(float)
	virtual bool				Equals( float v ) { return v == this->_value ; }			// �����̒l�Ɠ��������true
	virtual bool				Equals( const D_csmString& /*v*/ ) { return false ; }		// �����̒l�Ɠ��������true
	virtual bool				Equals( const char* /*v*/ ) { return false ; }				// �����̒l�Ɠ��������true
	virtual bool				Equals( int /*v*/ ) { return false ; }						// �����̒l�Ɠ��������true
	virtual bool				Equals( bool /*v*/ ) { return false ; }						// �����̒l�Ɠ��������true

private:
	float						_value ;						// JSON�v�f�̒l
} ;

// �p�[�X����JSON�̗v�f��^�U�l�Ƃ��Ĉ���
class D_JsonBoolean : public D_JsonValue
{
	friend class D_JsonValue ;

public:
	static D_JsonBoolean*		TrueValue ; // true
	static D_JsonBoolean*		FalseValue ;// false
	virtual ~D_JsonBoolean() {}																// �f�X�g���N�^
	virtual bool				IsBool() { return true ; }									// D_JsonValue�̎�ނ��^�U�l�Ȃ�true�B
	virtual bool				ToBoolean( bool /*defaultValue = false*/ ) { return _boolValue ; }// �v�f��^�U�l�ŕԂ�(bool)
	virtual D_csmString&		GetString( const D_csmString& defaultValue = "", const D_csmString& indent = "" ) ;// �v�f�𕶎���ŕԂ�(D_csmString�^)
	virtual bool				Equals( bool v ) { return v == _boolValue ; }				// �����̒l�Ɠ��������true�B
	virtual bool				Equals( const D_csmString& /*v*/ ) { return false ; }		// �����̒l�Ɠ��������true�B
	virtual bool				Equals( const char* /*v*/ ) { return false ; }				// �����̒l�Ɠ��������true�B
	virtual bool				Equals( int /*v*/ ) { return false ; }						// �����̒l�Ɠ��������true�B
	virtual bool				Equals( float /*v*/ ) { return false ; }					// �����̒l�Ɠ��������true�B
	virtual bool				IsStatic() { return true ; }								// D_JsonValue�̒l���ÓI�Ȃ�true. �ÓI�Ȃ������Ȃ�

private:
	D_JsonBoolean( bool v ) : D_JsonValue() { this->_boolValue = v; }						// �����t���R���X�g���N�^
	bool						_boolValue ;					// JSON�v�f�̒l
} ;

// �p�[�X����JSON�̗v�f�𕶎���Ƃ��Ĉ���
class D_JsonString : public D_JsonValue
{
public:
	D_JsonString( const D_csmString& s ) : D_JsonValue() { this->_stringBuffer = s ; }		// �����t���R���X�g���N�^
	D_JsonString( const char* s ) : D_JsonValue() { this->_stringBuffer = s ; }				// �����t���R���X�g���N�^
	virtual ~D_JsonString() {}																// �f�X�g���N�^
	virtual bool				IsString() { return true ; }									// D_JsonValue�̎�ނ�������Ȃ�true�B
	virtual D_csmString&		GetString( const D_csmString& defaultValue = "", const D_csmString& indent = "" ) ;// �v�f�𕶎���ŕԂ�(D_csmString�^)
	virtual bool				Equals( const D_csmString& v ) { return ( _stringBuffer == v ) ; }// �����̒l�Ɠ��������true�B
	virtual bool				Equals( const char* v ) { return ( _stringBuffer == v ) ; }	// �����̒l�Ɠ��������true�B
	virtual bool				Equals( int /*v*/ ) { return false ; }						// �����̒l�Ɠ��������true�B
	virtual bool				Equals( float /*v*/ ) { return false ; }					// �����̒l�Ɠ��������true�B
	virtual bool				Equals( bool /*v*/ ) { return false ; }						// �����̒l�Ɠ��������true�B
} ;

// JSON�p�[�X���̃G���[���ʁB������^�̂悤�ɐU�镑��
class D_JsonError : public D_JsonString
{
	friend class D_JsonValue ; //
	friend class D_JsonArray ; //
	friend class D_CubismJson ; //

public:
	virtual bool				IsStatic() { return _isStatic ; }							// D_JsonValue�̒l���ÓI�Ȃ�true. �ÓI�Ȃ������Ȃ�
	virtual D_JsonValue*		SetErrorNotForClientCall( const char* s ){ _stringBuffer = s ; return this ; }	//  �G���[�����Z�b�g����

protected:
	D_JsonError( const D_csmString& s, bool isStatic ) : D_JsonString( s ), _isStatic( isStatic ) {}// �����t���R���X�g���N�^
	virtual ~D_JsonError() {}																// �f�X�g���N�^
	virtual bool				IsError() { return true ; }									// D_JsonValue�̎�ނ��G���[�l�Ȃ�true�B

	bool						_isStatic ;					// �ÓI��D_JsonValue���ǂ���
} ;

// �p�[�X����JSON�̗v�f��Null�l�Ƃ��Ď���
class D_JsonNullValue : public D_JsonValue
{
	friend class D_JsonValue ; //
	friend class D_CubismJson ; //

public:
	virtual ~D_JsonNullValue() {}															// �f�X�g���N�^
	virtual bool IsNull() { return true ; }													// D_JsonValue�̎�ނ�NULL�l�Ȃ�true�B
	virtual D_csmString& GetString( const D_csmString& /*defaultValue = ""*/, const D_csmString& /*indent = ""*/ ){ return _stringBuffer ; }	// �v�f�𕶎���ŕԂ�(D_csmString�^)
	virtual bool IsStatic() { return true ; }												// D_JsonValue�̒l���ÓI�Ȃ�true. �ÓI�Ȃ������Ȃ�

private:
	D_JsonNullValue() : D_JsonValue() { _stringBuffer = "D_JsonNullValue"; }				//  �R���X�g���N�^
} ;

// �p�[�X����JSON�̗v�f��z��Ƃ��Ď���
class D_JsonArray : public D_JsonValue
{
public:
	D_JsonArray() : D_JsonValue(), _array() {}												//  �R���X�g���N�^
	virtual ~D_JsonArray() ;																// �f�X�g���N�^
	virtual bool				IsArray() { return true ; }									// D_JsonValue�̎�ނ��z��Ȃ�true�B
	virtual D_JsonValue&		operator[]( int index ) ;									// �Y�����Z�q[int]
	virtual D_JsonValue&		operator[]( const D_csmString& string ) ;					// �Y�����Z�q[D_csmString]
	virtual D_JsonValue&		operator[]( const char* s ) ;								// �Y�����Z�q[char*]
	virtual D_csmString&		GetString( const D_csmString& defaultValue = "", const D_csmString& indent = "" ) ;// �v�f�𕶎���ŕԂ�(D_csmString�^)
	void						Add( D_JsonValue* v ) { _array.PushBack( v, false ) ; }		// �z��v�f��ǉ�����
	virtual D_csmVector<D_JsonValue*>* GetVector( D_csmVector<D_JsonValue*>* /*defaultValue = NULL*/ ) { return &_array ; }// �v�f���R���e�i�ŕԂ�(D_csmVector<D_JsonValue*>)
	virtual int					GetSize() { return static_cast< int >( _array.GetSize() ) ; }// �v�f�̐���Ԃ�

private:
	D_csmVector<D_JsonValue*>	_array ;						// JSON�v�f�̒l
} ;

// �p�[�X����JSON�̗v�f���}�b�v�Ƃ��Ď���
class D_JsonMap : public D_JsonValue
{
public:
	D_JsonMap() : D_JsonValue(), _keys( NULL ) {}											//  �R���X�g���N�^
	virtual ~D_JsonMap() ;																	//  �f�X�g���N�^
	virtual bool				IsMap() { return true ; }									//  D_JsonValue�̒l��D_JsonMap�^�Ȃ�true
	virtual D_JsonValue&		operator[]( const D_csmString& s ) ;						// �Y�����Z�q[D_csmString]
	virtual D_JsonValue&		operator[]( const char* s ) ;								// �Y�����Z�q[char*]
	virtual D_JsonValue&		operator[]( int index ) ;									// �Y�����Z�q[int]
	virtual D_csmString&		GetString( const D_csmString& defaultValue = "", const D_csmString& indent = "" ) ;
	void						Put( D_csmString& key, D_JsonValue* v ) ;					// D_JsonMap�ɗv�f��ǉ�����
	virtual int					GetSize() { return static_cast< int >( _keys->GetSize() ) ; }// D_JsonMap�̗v�f�����擾����
	virtual D_csmMap<D_csmString, D_JsonValue*>* GetMap( D_csmMap<D_csmString, D_JsonValue*>* defaultValue = NULL ) ;//  �v�f��D_JsonMap�^�ŕԂ�
	virtual D_csmVector<D_csmString>& GetKeys() ;											//  D_JsonMap����L�[�̃��X�g���擾����

private:
	D_csmMap<D_csmString, D_JsonValue*>	_map;		// JSON�v�f�̒l
	D_csmVector<D_csmString>*			_keys ;		// JSON�v�f�̒l
} ;

// motion3.json�̃R���e�i�B
class D_CubismMotionJson
{
public:
	D_CubismMotionJson( const BYTE* buffer, size_t size ) ;									// �R���X�g���N�^
	virtual ~D_CubismMotionJson() ;															// �f�X�g���N�^
	float						GetMotionDuration() const ;									// ���[�V�����̒����̎擾
	bool						IsMotionLoop() const ;										// ���[�V�����̃��[�v���̎擾
	int							GetMotionCurveCount() const ;								// ���[�V�����J�[�u�̌��̎擾
	float						GetMotionFps() const ;										// ���[�V�����̃t���[�����[�g�̎擾
	int							GetMotionTotalSegmentCount() const ;						// ���[�V�����̃Z�O�����g�̑����v�̎擾
	int							GetMotionTotalPointCount() const ;							// ���[�V�����̃J�[�u�̐���_�̑����v�̎擾
	bool						IsExistMotionFadeInTime() const ;							// ���[�V�����̃t�F�[�h�C�����Ԃ̑���
	bool						IsExistMotionFadeOutTime() const ;							// ���[�V�����̃t�F�[�h�A�E�g���Ԃ̑���
	float						GetMotionFadeInTime() const ;								// ���[�V�����̃t�F�[�h�C�����Ԃ̎擾
	float						GetMotionFadeOutTime() const ;								// ���[�V�����̃t�F�[�h�A�E�g���Ԃ̎擾
	const char*					GetMotionCurveTarget( int curveIndex ) const ;				// ���[�V�����̃J�[�u�̎�ނ̎擾
	D_CubismIdHandle			GetMotionCurveId( int curveIndex ) ;						// ���[�V�����̃J�[�u��ID�̎擾
	bool						IsExistMotionCurveFadeInTime( int curveIndex ) const ;		// ���[�V�����̃J�[�u�̃t�F�[�h�C�����Ԃ̑���
	bool						IsExistMotionCurveFadeOutTime( int curveIndex ) const ;		// ���[�V�����̃J�[�u�̃t�F�[�h�A�E�g���Ԃ̑���
	float						GetMotionCurveFadeInTime( int curveIndex ) const ;			// ���[�V�����̃J�[�u�̃t�F�[�h�C�����Ԃ̎擾
	float						GetMotionCurveFadeOutTime( int curveIndex ) const ;			// ���[�V�����̃J�[�u�̃t�F�[�h�A�E�g���Ԃ̎擾
	int							GetMotionCurveSegmentCount( int curveIndex ) const ;		// ���[�V�����̃J�[�u�̃Z�O�����g�̌��̎擾
	float						GetMotionCurveSegment( int curveIndex, int segmentIndex ) const ;// ���[�V�����̃J�[�u�̃Z�O�����g�̒l�̎擾
	int							GetEventCount() const ;										// �C�x���g�̌��̎擾
	int							GetTotalEventValueSize() const ;							// �C�x���g�̑��������̎擾
	float						GetEventTime( int userDataIndex ) const ;					// �C�x���g�̎��Ԃ̎擾
	const char*					GetEventValue( int userDataIndex ) const ;					// �C�x���g�̎擾

private:
	static const char*			Meta ;
	static const char*			Duration ;
	static const char*			Loop;
	static const char*			CurveCount ;
	static const char*			Fps ;
	static const char*			TotalSegmentCount ;
	static const char*			TotalPointCount ;
	static const char*			Curves ;
	static const char*			Target ;
	static const char*			Id ;
	static const char*			FadeInTime ;
	static const char*			FadeOutTime ;
	static const char*			Segments ;
	static const char*			UserData ;
	static const char*			UserDataCount ;
	static const char*			TotalUserDataSize ;
	static const char*			Time ;
	static const char*			Value ;
	D_CubismJson*				_json ;      // motion3.json�f�[�^
} ;

// ���[�V�����J�[�u�̐���_
struct D_CubismMotionPoint
{
	float						Time ;						// ����[�b]
	float						Value ;						// �l
} ;

// ���[�V�����J�[�u�̃Z�O�����g
struct D_CubismMotionSegment
{
    float						( *Evaluate )( const D_CubismMotionPoint *points, float time ) ;	// �g�p����]���֐�
	int							BasePointIndex ;			// �ŏ��̃Z�O�����g�ւ̃C���f�b�N�X
	int							SegmentType ;				// �Z�O�����g�̎��
} ;

// ���[�V�����J�[�u�B
struct D_CubismMotionCurve
{
	D_CubismMotionCurveTarget	Type ;						// �J�[�u�̎��
	D_CubismIdHandle			Id ;						// �J�[�u��ID
	int							SegmentCount ;				// �Z�O�����g�̌�
	int							BaseSegmentIndex ;			// �ŏ��̃Z�O�����g�̃C���f�b�N�X
	float						FadeInTime ;				// �t�F�[�h�C���ɂ����鎞��[�b]
	float						FadeOutTime ;				// �t�F�[�h�A�E�g�ɂ����鎞��[�b]
} ;

// �C�x���g�B
struct D_CubismMotionEvent
{
	float						FireTime ;
	D_csmString					Value ;
} ;

// ���[�V�����f�[�^�B
struct D_CubismMotionData
{
	float						Duration ;					// ���[�V�����̒���[�b]
	short						Loop ;						// ���[�v���邩�ǂ���
	short						CurveCount ;				// �J�[�u�̌�
	int							EventCount ;				// UserData�̌�
	float						Fps ;						// �t���[�����[�g

	D_csmVector< D_CubismMotionCurve >		Curves ;		// �J�[�u�̃��X�g
	D_csmVector< D_CubismMotionSegment >	Segments ;		// �Z�O�����g�̃��X�g
	D_csmVector< D_CubismMotionPoint >		Points ;		// �|�C���g�̃��X�g
	D_csmVector< D_CubismMotionEvent >		Events ;		// �C�x���g�̃��X�g
} ;

class D_CubismModel ;

// Moc�f�[�^�̊Ǘ�
class D_CubismMoc
{
	friend class D_CubismModel ;
public:
	static D_CubismMoc*			Create( const BYTE* mocBytes, size_t size ) ;				// �o�b�t�@����Moc�f�[�^�̍쐬
	static void					Delete( D_CubismMoc* moc ) ;								// Moc�f�[�^���폜
	D_CubismModel*				CreateModel() ;												// ���f�����쐬
	void						DeleteModel( D_CubismModel* model ) ;						// ���f�����폜

private:
	D_CubismMoc( void* moc ) ;																// �R���X�g���N�^
	virtual ~D_CubismMoc() ;																// �f�X�g���N�^

	void *						_moc ;						// Moc�f�[�^
	int							_modelCount ;				// Moc�f�[�^������ꂽ���f���̌�
} ;

// ���f��
class D_CubismModel
{
	friend class D_CubismMoc ;
public:
	void						Update() const ;											// ���f���̃p�����[�^�̍X�V
	float						GetCanvasWidth() const ;									// �L�����o�X�̕��̎擾
	float						GetCanvasHeight() const ;									// �L�����o�X�̍����̎擾
	void						GetCanvasInfo( D_CubismVector2 *SizeInPixels, D_CubismVector2 *OriginInPixels, float *PixelsPerUnit ) ;		// �L�����o�X�̏����擾����
	int							GetPartIndex( D_CubismIdHandle partId ) ;					// �p�[�c�̃C���f�b�N�X�̎擾
	int							GetPartCount() const ;										// �p�[�c�̌��̎擾
	void						SetPartOpacity( D_CubismIdHandle partId, float opacity ) ;	// �p�[�c�̕s�����x�̐ݒ�
	void						SetPartOpacity( int partIndex, float opacity ) ;			// �p�[�c�̕s�����x�̐ݒ�
	float						GetPartOpacity( D_CubismIdHandle partId ) ;					// �p�[�c�̕s�����x�̎擾
	float						GetPartOpacity( int partIndex ) ;							// �p�[�c�̕s�����x�̎擾
	int							GetParameterIndex( D_CubismIdHandle parameterId ) ;			// �p�����[�^�̃C���f�b�N�X�̎擾
	int							GetParameterCount() const ;									// �p�����[�^�̌��̎擾
	D_CubismIdHandle			GetParameterId( int parameterIndex ) ;						// �p�����[�^��ID�̎擾
	float						GetParameterMaximumValue( DWORD parameterIndex ) const ;	// �p�����[�^�̍ő�l�̎擾
	float						GetParameterMinimumValue( DWORD parameterIndex ) const ;	// �p�����[�^�̍ŏ��l�̎擾
	float						GetParameterDefaultValue( DWORD parameterIndex ) const ;	// �p�����[�^�̃f�t�H���g�l�̎擾
	float						GetParameterValue( D_CubismIdHandle parameterId ) ;			// �p�����[�^�̒l�̎擾
	float						GetParameterValue( int parameterIndex ) ;					// �p�����[�^�̒l�̎擾
	void						SetParameterValue( D_CubismIdHandle parameterId, float value, float weight = 1.0f, bool force = false ) ;	// �p�����[�^�̒l�̐ݒ�
	void						SetParameterValue( int parameterIndex, float value, float weight = 1.0f, bool force = false ) ;				// �p�����[�^�̒l�̐ݒ�
	void						SetDisableChangeParameter( D_CubismIdHandle parameterId, bool isDisable ) ;	// �p�����[�^�̒l�̕ύX�𖳌������邩�ǂ�����ݒ肷��
	void						SetDisableChangeParameter( int parameterIndex, bool isDisable ) ;			// �p�����[�^�̒l�̕ύX�𖳌������邩�ǂ�����ݒ肷��
	void						AddParameterValue( D_CubismIdHandle parameterId, float value, float weight = 1.0f ) ;	// �p�����[�^�̒l�̉��Z
	void						AddParameterValue( int parameterIndex, float value, float weight = 1.0f ) ;				// �p�����[�^�̒l�̉��Z
	void						MultiplyParameterValue( D_CubismIdHandle parameterId, float value, float weight = 1.0f ) ;	// �p�����[�^�̒l�̏�Z
	void						MultiplyParameterValue( int parameterIndex, float value, float weight = 1.0f ) ;		// �p�����[�^�̒l�̏�Z
	int							GetDrawableIndex( D_CubismIdHandle drawableId ) const ;		// Drawable�̃C���f�b�N�X�̎擾
	int							GetDrawableCount() const ;									// Drawable�̌��̎擾
	D_CubismIdHandle			GetDrawableId( int drawableIndex ) const ;					// Drawable��ID�̎擾
	const int *					GetDrawableRenderOrders() const ;							// Drawable�̕`�揇���X�g�̎擾
	int							GetDrawableTextureIndices( int drawableIndex ) const ;		// Drawable�̃e�N�X�`���C���f�b�N�X���X�g�̎擾
	int							GetDrawableVertexIndexCount( int drawableIndex ) const ;	// Drawable�̒��_�C���f�b�N�X�̌��̎擾
	int							GetDrawableVertexCount( int drawableIndex ) const ;			// Drawable�̒��_�̌��̎擾
	const float *				GetDrawableVertices( int drawableIndex ) const ;			// Drawable�̒��_���X�g�̎擾
	const WORD *				GetDrawableVertexIndices( int drawableIndex ) const ;		// Drawable�̒��_�C���f�b�N�X���X�g�̎擾
	const D_CubismVector2 *		GetDrawableVertexPositions( int drawableIndex ) const ;		// Drawable�̒��_���X�g�̎擾
	const D_CubismVector2 *		GetDrawableVertexUvs( int drawableIndex ) const ;			// Drawable�̒��_��UV���X�g�̎擾
	float						GetDrawableOpacity( int drawableIndex ) const ;				// Drawable�̕s�����x�̎擾
	int							GetDrawableCulling( int drawableIndex ) const ;				// Drawable�̃J�����O���̎擾
	D_CubismBlendMode			GetDrawableBlendMode( int drawableIndex ) const ;			// Drawable�̃u�����h���[�h�̎擾
	bool						GetDrawableInvertedMask( int drawableIndex ) const ;		// Drawable�̃}�X�N�̔��]�g�p�̎擾
	bool						GetDrawableDynamicFlagIsVisible( int drawableIndex ) const ;	// Drawable�̕\�����̎擾
	bool						GetDrawableDynamicFlagVisibilityDidChange( int drawableIndex ) const ;	// Drawable�̕\����Ԃ̕ω��̎擾
	bool						GetDrawableDynamicFlagOpacityDidChange( int drawableIndex ) const ;	// Drawable�̕s�����x�̕ω����̎擾
	bool						GetDrawableDynamicFlagDrawOrderDidChange( int drawableIndex ) const ;	// Drawable��DrawOrder�̕ω����̎擾
	bool						GetDrawableDynamicFlagRenderOrderDidChange( int drawableIndex ) const ;	// Drawable�̕`�揇���̕ω����̎擾
	bool						GetDrawableDynamicFlagVertexPositionsDidChange( int drawableIndex ) const ;	// Drawable��VertexPositions�̕ω����̎擾
	const int**					GetDrawableMasks() const ;									// Drawable�̃N���b�s���O�}�X�N���X�g�̎擾
	const int*					GetDrawableMaskCounts() const ;								// Drawable�̃N���b�s���O�}�X�N�̌����X�g�̎擾
	bool						IsUsingMasking() const ;									// �N���b�s���O�}�X�N�̎g�p���
	void						LoadParameters() ;											// �ۑ����ꂽ�p�����[�^�̓ǂݍ���
	void						SaveParameters() ;											// �p�����[�^�̕ۑ�
	void*						GetModel() const ;

private:
	D_CubismModel( void* model ) ;															// �R���X�g���N�^
	virtual ~D_CubismModel() ;																// �f�X�g���N�^
	D_CubismModel( const D_CubismModel& ) ;

	D_CubismModel&				operator=( const D_CubismModel& ) ;
	void						Initialize() ;												// ������

	D_csmMap< int, float >				_notExistPartOpacities ;	// ���݂��Ă��Ȃ��p�[�c�̕s�����x�̃��X�g
	D_csmMap< D_CubismIdHandle, int >	_notExistPartId ;			// ���݂��Ă��Ȃ��p�[�cID�̃��X�g
	D_csmMap< int, float >				_notExistParameterValues ;	// ���݂��Ă��Ȃ��p�����[�^�̒l�̃��X�g
	D_csmMap< D_CubismIdHandle, int >	_notExistParameterId ;		// ���݂��Ă��Ȃ��p�����[�^ID�̃��X�g
	D_csmVector< int >					_disableChangeParameterIndices ;	// �ʏ�̕ύX�͋��ۂ����p�����[�^�ԍ�
	D_csmVector< float >				_savedParameters ;			// �ۑ����ꂽ�p�����[�^
	void *								_model ;					// ���f��
	float *								_parameterValues ;			// �p�����[�^�̒l�̃��X�g
	const float *						_parameterMaximumValues ;	// �p�����[�^�̍ő�l�̃��X�g
	const float *						_parameterMinimumValues ;	// �p�����[�^�̍ŏ��l�̃��X�g
	float *								_partOpacities ;			// �p�[�c�̕s�����x�̃��X�g
	D_csmVector< D_CubismIdHandle >		_parameterIds ;
	D_csmVector< D_CubismIdHandle >		_partIds ;
	D_csmVector< D_CubismIdHandle >		_drawableIds ;
} ;

// D_CubismMotionQueueManager�ōĐ����Ă���e���[�V�����̊Ǘ�
class D_CubismMotionQueueEntry
{
	friend class D_CubismMotionQueueManager ;
	friend class D_ACubismMotion ;
	friend class D_CubismMotion ;

public:
	D_CubismMotionQueueEntry() ;															// �R���X�g���N�^
	virtual ~D_CubismMotionQueueEntry() ;// �f�X�g���N�^
	void						StartFadeout( float fadeOutSeconds, float userTimeSeconds ) ;	// �t�F�[�h�A�E�g�̊J�n
	bool						IsFinished() const ;										// ���[�V�����̏I���̊m�F
	bool						IsStarted() const ;											// ���[�V�����̊J�n�̊m�F
	float						GetStartTime() const ;										// ���[�V�����̊J�n�����̎擾
	float						GetFadeInStartTime() const ;								// �t�F�[�h�C���̊J�n�����̎擾
	float						GetEndTime() const ;										// �t�F�[�h�C���̏I�������̎擾
	void						SetStartTime( float startTime ) ;							// ���[�V�����̊J�n�����̐ݒ�
	void						SetFadeInStartTime( float startTime ) ;						// �t�F�[�h�C���̊J�n�����̐ݒ�
	void						SetEndTime( float endTime )	;								// �t�F�[�h�C���̏I�������̐ݒ�
	void						IsFinished( bool f ) ;										// ���[�V�����̏I���̐ݒ�
	void						IsStarted( bool f ) ;										// ���[�V�����̊J�n�̐ݒ�
	bool						IsAvailable() const ;										// ���[�V�����̗L�����̊m�F
	void						IsAvailable( bool v ) ;										// ���[�V�����̗L�����̐ݒ�
	void						SetState( float timeSeconds, float weight ) ;				// ���[�V�����̏�Ԃ̐ݒ�
	float						GetStateTime() const ;										// ���[�V�����̌��ݎ����̎擾
	float						GetStateWeight() const ;									// ���[�V�����̏d�݂̎擾
	float						GetLastCheckEventTime() const ;								// �Ō�ɃC�x���g�̔��΂��`�F�b�N�������Ԃ��擾
	void						SetLastCheckEventTime( float checkTime ) ;					// �Ō�ɃC�x���g���`�F�b�N�������Ԃ�ݒ�

private:
	bool						_autoDelete ;					// �����폜
	class D_ACubismMotion*		_motion ;						// ���[�V����
	bool						_available ;					// �L�����t���O
	bool						_finished ;						// �I���t���O
	bool						_started ;						// �J�n�t���O�i0.9.00�ȍ~�j
	float						_startTimeSeconds ;				//  ���[�V�����Đ��J�n����[�b]
	float						_fadeInStartTimeSeconds ;		//  �t�F�[�h�C���J�n�����i���[�v�̎��͏���̂݁j[�b]
	float						_endTimeSeconds ;				// �I���\�莞��[�b]
	float						_stateTimeSeconds ;				//  �����̏��[�b]
	float						_stateWeight ;					//  �d�݂̏��
	float						_lastEventCheckSeconds ;		//   �ŏI��Motion���̃`�F�b�N��������
	D_CubismMotionQueueEntryHandle  _motionQueueEntryHandle	;	// �C���X�^���X���ƂɈ�ӂ̒l�������ʔԍ�
} ;

// ���[�V�����Đ��̊Ǘ�
class D_CubismMotionQueueManager
{
public:
	D_CubismMotionQueueManager() ;															// �R���X�g���N�^
	virtual ~D_CubismMotionQueueManager() ;													// �f�X�g���N�^
	D_CubismMotionQueueEntryHandle StartMotion( D_ACubismMotion* motion, bool autoDelete, float userTimeSeconds ) ;		// �w�肵�����[�V�����̊J�n
	bool						IsFinished() ;																			// ���ׂẴ��[�V�����̏I���̊m�F
	bool						IsFinished( D_CubismMotionQueueEntryHandle motionQueueEntryNumber ) ;					// �w�肵�����[�V�����̏I���̊m�F
	void						StopAllMotions() ;																		// ���ׂẴ��[�V�����̒�~
	D_CubismMotionQueueEntry *	GetCubismMotionQueueEntry( D_CubismMotionQueueEntryHandle motionQueueEntryNumber ) ;	// �w�肵��D_CubismMotionQueueEntry�̎擾
	void						SetEventCallback( D_CubismMotionEventFunction callback, void* customData = NULL ) ;		// �C�x���g���󂯎��Callback�̓o�^
	float						GetMotionPlayTime(){ return _motionPlayTime; }

protected:
	virtual bool				DoUpdateMotion( D_CubismModel* model, float userTimeSeconds ) ;							// ���[�V�����̍X�V

	float										_userTimeSeconds ;	// �f���^���Ԃ̐ώZ�l[�b]
	float										_motionPlayTime ;	// ���[�V�����Đ�����

private:
	D_csmVector< D_CubismMotionQueueEntry * >   _motions ;			// ���[�V����
	D_CubismMotionEventFunction					_eventCallback ;	// �R�[���o�b�N�֐��|�C���^
	void*										_eventCustomData ;	// �R�[���o�b�N�ɖ߂����f�[�^
} ;

// ���[�V�����̒��ۊ��N���X
class D_ACubismMotion
{
public:
	static void					Delete( D_ACubismMotion* motion ) ;							// �C���X�^���X�̔j��
	D_ACubismMotion() ;																		// �R���X�g���N�^
	void						UpdateParameters( D_CubismModel* model, D_CubismMotionQueueEntry* motionQueueEntry, float userTimeSeconds ) ;	// ���f���̃p�����[�^�X�V
	void						SetFadeInTime( float fadeInSeconds ) ;						// �t�F�[�h�C��
	void						SetFadeOutTime( float fadeOutSeconds ) ;					// �t�F�[�h�A�E�g
	float						GetFadeOutTime() const ;									// �t�F�[�h�A�E�g�ɂ����鎞�Ԃ̎擾
	float						GetFadeInTime() const ;										// �t�F�[�h�C���ɂ����鎞�Ԃ̎擾
	void						SetWeight( float weight ) ;									// ���[�V�����K�p�̏d�݂̐ݒ�
	float						GetWeight() const ;											// ���[�V�����K�p�̏d�݂̎擾
	virtual float				GetDuration() ;												// ���[�V�����̒����̎擾
	virtual float				GetLoopDuration() ;											// ���[�V�����̃��[�v1�񕪂̒����̎擾
	void						SetOffsetTime( float offsetSeconds ) ;						// ���[�V�����Đ��̊J�n�����̐ݒ�
	virtual const D_csmVector< const D_csmString * >& GetFiredEvent( float beforeCheckTimeSeconds, float motionTimeSeconds ) ;	// ���f���̃p�����[�^�X�V

private:
	// Prevention of copy Constructor
	D_ACubismMotion( const D_ACubismMotion& ) ;
	D_ACubismMotion& operator=( const D_ACubismMotion& ) ;

protected:
	virtual ~D_ACubismMotion() ;															// �f�X�g���N�^
	virtual void				DoUpdateParameters( D_CubismModel* model, float userTimeSeconds, float weight, D_CubismMotionQueueEntry* motionQueueEntry ) = 0 ;// ���f���̃p�����[�^�̍X�V�̎��s

	float						_fadeInSeconds ;			// �t�F�[�h�C���ɂ����鎞��[�b]
	float						_fadeOutSeconds ;			// �t�F�[�h�A�E�g�ɂ����鎞��[�b]
	float						_weight ;					// ���[�V�����̏d��
	float						_offsetSeconds ;			// ���[�V�����Đ��̊J�n����[�b]
	D_csmVector< const D_csmString * >	_firedEventValues ;
} ;

// �\��̃��[�V����
class D_CubismExpressionMotion : public D_ACubismMotion
{
private:
	// �\��p�����[�^�l�̌v�Z����
	enum ExpressionBlendType
	{
		ExpressionBlendType_Add					= 0,		// ���Z
		ExpressionBlendType_Multiply			= 1,		// ��Z
		ExpressionBlendType_Overwrite			= 2			// �㏑��
	} ;

public:
	// �\��̃p�����[�^���
	struct D_ExpressionParameter
	{
		D_CubismIdHandle		ParameterId ;	// �p�����[�^ID
		ExpressionBlendType		BlendType ;		// �p�����[�^�̉��Z���
		float					Value ;			// �l
	} ;
	static D_CubismExpressionMotion*	Create( const BYTE* buf, size_t size ) ;				// �C���X�^���X�̍쐬
	virtual void						DoUpdateParameters( D_CubismModel* model, float userTimeSeconds, float weight, D_CubismMotionQueueEntry* motionQueueEntry ) ;	// ���f���̃p�����[�^�̍X�V�̎��s

private:
	D_CubismExpressionMotion() ;
	virtual ~D_CubismExpressionMotion() ;

	D_csmVector<D_ExpressionParameter> _parameters ;		// �\��̃p�����[�^��񃊃X�g
} ;

// ���[�V�����N���X
class D_CubismMotion : public D_ACubismMotion
{
public:
	static D_CubismMotion*		Create( const BYTE* buffer, size_t size ) ;									// �C���X�^���X�̐���
	virtual void				DoUpdateParameters( D_CubismModel* model, float userTimeSeconds, float fadeWeight, D_CubismMotionQueueEntry* motionQueueEntry ) ;	// ���f���̃p�����[�^�̍X�V�̎��s
	void						IsLoop( bool loop ) ;														// ���[�v���̐ݒ�
	bool						IsLoop() const ;															// ���[�v���̎擾
	void						IsLoopFadeIn( bool loopFadeIn ) ;											// ���[�v���̃t�F�[�h�C�����̐ݒ�
	bool						IsLoopFadeIn() const ;														// ���[�v���̃t�F�[�h�C�����̎擾
	virtual float				GetDuration() ;																// ���[�V�����̒����̎擾
	virtual float				GetLoopDuration() ;															// ���[�V�����̃��[�v���̒����̎擾
	void						SetParameterFadeInTime( D_CubismIdHandle parameterId, float value ) ;		// �p�����[�^�ɑ΂���t�F�[�h�C���̎��Ԃ̐ݒ�
	void						SetParameterFadeOutTime( D_CubismIdHandle parameterId, float value ) ;		// �p�����[�^�ɑ΂���t�F�[�h�A�E�g�̎��Ԃ̐ݒ�
	float						GetParameterFadeInTime( D_CubismIdHandle parameterId ) const ;				// �p�����[�^�ɑ΂���t�F�[�h�C���̎��Ԃ̎擾
	float						GetParameterFadeOutTime( D_CubismIdHandle parameterId ) const ;				// �p�����[�^�ɑ΂���t�F�[�h�A�E�g�̎��Ԃ̎擾
	void						SetEffectIds( const D_csmVector<D_CubismIdHandle>& eyeBlinkParameterIds, const D_csmVector<D_CubismIdHandle>& lipSyncParameterIds ) ;	// �����G�t�F�N�g���������Ă���p�����[�^ID���X�g�̐ݒ�
	virtual const D_csmVector< const D_csmString * >& GetFiredEvent( float beforeCheckTimeSeconds, float motionTimeSeconds ) ;	// ���f���̃p�����[�^�X�V

private:
	D_CubismMotion() ;																		// �R���X�g���N�^
	virtual ~D_CubismMotion() ;																// �f�X�g���N�^
	D_CubismMotion( const D_CubismMotion& ) ;												// Prevention of copy Constructor
	D_CubismMotion& operator=( const D_CubismMotion& ) ;
	void Parse( const BYTE* motionJson, const size_t size ) ;								// motion3.json�̃p�[�X

	float						_sourceFrameRate ;			// ���[�h�����t�@�C����FPS�B�L�q��������΃f�t�H���g�l15fps�ƂȂ�
	float						_loopDurationSeconds ;		// mtn�t�@�C���Œ�`������A�̃��[�V�����̒���
	bool						_isLoop ;					// ���[�v���邩?
	bool						_isLoopFadeIn ;				// ���[�v���Ƀt�F�[�h�C�����L�����ǂ����̃t���O�B�����l�ł͗L���B
	float						_lastWeight ;				// �Ō�ɐݒ肳�ꂽ�d��
	D_CubismMotionData*			_motionData ;				// ���ۂ̃��[�V�����f�[�^�{��
	D_csmVector< D_CubismIdHandle >	_eyeBlinkParameterIds ;	// �����܂΂�����K�p����p�����[�^ID�n���h���̃��X�g�B  ���f���i���f���Z�b�e�B���O�j�ƃp�����[�^��Ή��t����B
	D_csmVector< D_CubismIdHandle >	_lipSyncParameterIds ;	// ���b�v�V���N��K�p����p�����[�^ID�n���h���̃��X�g�B  ���f���i���f���Z�b�e�B���O�j�ƃp�����[�^��Ή��t����B
	D_CubismIdHandle			_modelCurveIdEyeBlink ;		// ���f�����������܂΂����p�p�����[�^ID�̃n���h���B  ���f���ƃ��[�V������Ή��t����B
	D_CubismIdHandle			_modelCurveIdLipSync ;		// ���f���������b�v�V���N�p�p�����[�^ID�̃n���h���B  ���f���ƃ��[�V������Ή��t����B
} ;

// 4x4�̍s��
class D_CubismMatrix44
{
public:
	D_CubismMatrix44() ;																	// �R���X�g���N�^
	virtual ~D_CubismMatrix44() ;															// �f�X�g���N�^
	static void					Multiply( float* a, float* b, float* dst ) ;				// ��Z
	void						LoadIdentity() ;											// �P�ʍs��ɏ�����
	float*						GetArray() ;												// �s��𕂓������_���̔z��Ŏ擾
	void						SetMatrix( float* tr ) ;									// �s���ݒ�
	float						GetScaleX() const ;											// X���̊g�嗦���擾
	float						GetScaleY() const ;											// Y���̊g�嗦���擾
	float						GetTranslateX() const ;										// X���̈ړ��ʂ��擾
	float						GetTranslateY() const ;										// Y���̈ړ��ʂ��擾
	float						TransformX( float src ) ;									// X���̒l�����݂̍s��Ōv�Z
	float						TransformY( float src ) ;									// Y���̒l�����݂̍s��Ōv�Z
	float						InvertTransformX( float src ) ;								// X���̒l�����݂̍s��ŋt�v�Z
	float						InvertTransformY( float src ) ;								// Y���̒l�����݂̍s��ŋt�v�Z
	void						TranslateRelative( float x, float y ) ;						// ���݂̍s��̈ʒu���N�_�ɂ��Ĉړ�
	void						Translate( float x, float y ) ;								// ���݂̍s��̈ʒu���ړ�
	void						TranslateX( float x ) ;										// ���݂̍s���X���̈ʒu���ړ�
	void						TranslateY( float y ) ;										// ���݂̍s���Y���̈ʒu���ړ�
	void						ScaleRelative( float x, float y ) ;							// ���݂̍s��̊g�嗦�𑊑ΓI�ɐݒ�
	void						Scale( float x, float y ) ;									// ���݂̍s��̊g�嗦��ݒ�
	void						RotateRelative( float angle ) ;								// ���݂̍s��̉�]( ���W�A�� )�𑊑ΓI�ɐݒ�
	void						MultiplyByMatrix( D_CubismMatrix44* m ) ;					// ���݂̍s��ɍs�����Z

protected:
	float						_tr[ 16 ] ;					// 4x4�s��f�[�^
} ;

// ���f�����W�ݒ�p��4x4�s��
class D_CubismModelMatrix : public D_CubismMatrix44
{
public:
	D_CubismModelMatrix() ;																	// �R���X�g���N�^
	D_CubismModelMatrix( float w, float h ) ;												// �R���X�g���N�^
	virtual ~D_CubismModelMatrix() ;														// �f�X�g���N�^
	void						SetWidth( float w ) ;										// ������ݒ�
	void						SetHeight( float h ) ;										// �c����ݒ�
	void						SetPosition( float x, float y ) ;							// �ʒu��ݒ�
	void						SetCenterPosition( float x, float y ) ;						// ���S�ʒu��ݒ�
	void						Top( float y ) ;											// ��ӂ̈ʒu��ݒ�
	void						Bottom( float y ) ;											// ���ӂ̈ʒu��ݒ�
	void						Left( float x ) ;											// ���ӂ̈ʒu��ݒ�
	void						Right( float x ) ;											// �E�ӂ̈ʒu��ݒ�
	void						CenterX( float x ) ;										// X���̒��S�ʒu��ݒ�
	void						SetX( float x ) ;											// X���̈ʒu��ݒ�
	void						CenterY( float y ) ;										// Y���̒��S�ʒu��ݒ�
	void						SetY( float y ) ;											// Y���̈ʒu��ݒ�
	void						SetupFromLayout( D_csmMap<D_csmString, float>& layout ) ;	// ���C�A�E�g��񂩂�ʒu��ݒ�

private:
	float						_width ;					// ����
	float						_height ;					// �c��
} ;

// ���[�V�����̊Ǘ�
class D_CubismMotionManager : public D_CubismMotionQueueManager
{
public:
	D_CubismMotionManager() ;																// �R���X�g���N�^
	virtual ~D_CubismMotionManager() ;														// �f�X�g���N�^
	int							GetCurrentPriority() const ;								// �Đ����̃��[�V�����̗D��x�̎擾
	int							GetReservePriority() const ;								// �\�񒆂̃��[�V�����̗D��x�̎擾
	void						SetReservePriority( int val ) ;								// �\�񒆂̃��[�V�����̗D��x�̐ݒ�
	D_CubismMotionQueueEntryHandle StartMotionPriority( D_ACubismMotion* motion, bool autoDelete, int priority ) ;// �D��x��ݒ肵�ă��[�V�����̊J�n
	bool						UpdateMotion( D_CubismModel* model, float deltaTimeSeconds ) ;	// ���[�V�����̍X�V
	bool						ReserveMotion( int priority ) ;								// ���[�V�����̗\��

private:
	int							_currentPriority ;                 // ���ݍĐ����̃��[�V�����̗D��x
	int							_reservePriority ;                 // �Đ��\��̃��[�V�����̗D��x�B�Đ�����0�ɂȂ�B���[�V�����t�@�C����ʃX���b�h�œǂݍ��ނƂ��̏���
} ;

// ���f���ݒ������舵���֐���錾�����������z�N���X�B
class D_ICubismModelSetting
{
public:
	virtual ~D_ICubismModelSetting() {}																// �f�X�g���N�^
	virtual const char*					GetModelFileName() = 0 ;											// Moc�t�@�C���̖��O���擾����
	virtual const char*					GetModelFileNameA() = 0 ;											// Moc�t�@�C���̖��O���擾����
	virtual const BYTE/*wchar_t*/ *		GetModelFileNameW() = 0 ;											// Moc�t�@�C���̖��O���擾����
	virtual int							GetTextureCount() = 0 ;												// ���f�����g�p����e�N�X�`���̐����擾����
	virtual const char*					GetTextureDirectory() = 0 ;											// �e�N�X�`�����z�u���ꂽ�f�B���N�g���̖��O���擾����
	virtual const char*					GetTextureDirectoryA() = 0 ;										// �e�N�X�`�����z�u���ꂽ�f�B���N�g���̖��O���擾����
	virtual const BYTE/*wchar_t*/ *		GetTextureDirectoryW() = 0 ;										// �e�N�X�`�����z�u���ꂽ�f�B���N�g���̖��O���擾����
	virtual const char*					GetTextureFileName( int index ) = 0 ;								// ���f�����g�p����e�N�X�`���̖��O���擾����
	virtual const char*					GetTextureFileNameA( int index ) = 0 ;								// ���f�����g�p����e�N�X�`���̖��O���擾����
	virtual const BYTE/*wchar_t*/ *		GetTextureFileNameW( int index ) = 0 ;								// ���f�����g�p����e�N�X�`���̖��O���擾����
	virtual int							GetHitAreasCount() = 0 ;											// ���f���ɐݒ肳�ꂽ�����蔻��̐����擾����
	virtual D_CubismIdHandle			GetHitAreaId( int index ) = 0 ;										// �����蔻��ɐݒ肳�ꂽID���擾����
	virtual const char*					GetHitAreaName( int index ) = 0 ;									// �����蔻��ɐݒ肳�ꂽ���O���擾����
	virtual const char*					GetHitAreaNameA( int index ) = 0 ;									// �����蔻��ɐݒ肳�ꂽ���O���擾����
	virtual const BYTE/*wchar_t*/ *		GetHitAreaNameW( int index ) = 0 ;									// �����蔻��ɐݒ肳�ꂽ���O���擾����
	virtual const char*					GetPhysicsFileName() = 0 ;											// �������Z�ݒ�t�@�C���̖��O���擾����
	virtual const char*					GetPhysicsFileNameA() = 0 ;											// �������Z�ݒ�t�@�C���̖��O���擾����
	virtual const BYTE/*wchar_t*/ *		GetPhysicsFileNameW() = 0 ;											// �������Z�ݒ�t�@�C���̖��O���擾����
	virtual const char*					GetPoseFileName() = 0 ;												// �p�[�c�؂�ւ��ݒ�t�@�C���̖��O���擾����
	virtual const char*					GetPoseFileNameA() = 0 ;											// �p�[�c�؂�ւ��ݒ�t�@�C���̖��O���擾����
	virtual const BYTE/*wchar_t*/ *		GetPoseFileNameW() = 0 ;											// �p�[�c�؂�ւ��ݒ�t�@�C���̖��O���擾����
	virtual int							GetExpressionCount() = 0 ;											// �\��ݒ�t�@�C���̐����擾����
	virtual const char*					GetExpressionName( int index ) = 0 ;								// �\��ݒ�t�@�C�������ʂ��閼�O�i�ʖ��j���擾����
	virtual const char*					GetExpressionNameA( int index ) = 0 ;								// �\��ݒ�t�@�C�������ʂ��閼�O�i�ʖ��j���擾����
	virtual const BYTE/*wchar_t*/ *		GetExpressionNameW( int index ) = 0 ;								// �\��ݒ�t�@�C�������ʂ��閼�O�i�ʖ��j���擾����
	virtual const char*					GetExpressionFileName( int index ) = 0 ;							// �\��ݒ�t�@�C���̖��O���擾����
	virtual const char*					GetExpressionFileNameA( int index ) = 0 ;							// �\��ݒ�t�@�C���̖��O���擾����
	virtual const BYTE/*wchar_t*/ *		GetExpressionFileNameW( int index ) = 0 ;							// �\��ݒ�t�@�C���̖��O���擾����
	virtual int							GetMotionGroupCount() = 0 ;											// ���[�V�����O���[�v�̐����擾����
	virtual const char*					GetMotionGroupName( int index ) = 0 ;								// ���[�V�����O���[�v�̖��O���擾����
	virtual const char*					GetMotionGroupNameA( int index ) = 0 ;								// ���[�V�����O���[�v�̖��O���擾����
	virtual const BYTE/*wchar_t*/ *		GetMotionGroupNameW( int index ) = 0 ;								// ���[�V�����O���[�v�̖��O���擾����
	virtual int							GetMotionCount( const char* groupName ) = 0 ;						// ���[�V�����O���[�v�Ɋ܂܂�郂�[�V�����̐����擾����
	virtual const char*					GetMotionFileName( const char* groupName, int index ) = 0 ;			// �O���[�v���ƃC���f�b�N�X�l���烂�[�V�����t�@�C���̖��O���擾����
	virtual const char*					GetMotionFileNameA( const char* groupName, int index ) = 0 ;		// �O���[�v���ƃC���f�b�N�X�l���烂�[�V�����t�@�C���̖��O���擾����
	virtual const BYTE/*wchar_t*/ *		GetMotionFileNameW( const char* groupName, int index ) = 0 ;		// �O���[�v���ƃC���f�b�N�X�l���烂�[�V�����t�@�C���̖��O���擾����
	virtual const char*					GetMotionSoundFileName( const char* groupName, int index ) = 0 ;	// ���[�V�����ɑΉ�����T�E���h�t�@�C���̖��O���擾����
	virtual const char*					GetMotionSoundFileNameA( const char* groupName, int index ) = 0 ;	// ���[�V�����ɑΉ�����T�E���h�t�@�C���̖��O���擾����
	virtual const BYTE/*wchar_t*/ *		GetMotionSoundFileNameW( const char* groupName, int index ) = 0 ;	// ���[�V�����ɑΉ�����T�E���h�t�@�C���̖��O���擾����
	virtual float						GetMotionFadeInTimeValue( const char* groupName, int index ) = 0 ;	// ���[�V�����J�n���̃t�F�[�h�C���������Ԃ��擾����
	virtual float						GetMotionFadeOutTimeValue( const char* groupName, int index ) = 0 ;	// ���[�V�����I�����̃t�F�[�h�A�E�g�������Ԃ��擾����
	virtual const char*					GetUserDataFile() = 0 ;												// ���[�U�f�[�^�̃t�@�C�������擾����
	virtual const char*					GetUserDataFileA() = 0 ;											// ���[�U�f�[�^�̃t�@�C�������擾����
	virtual const BYTE/*wchar_t*/ *		GetUserDataFileW() = 0 ;											// ���[�U�f�[�^�̃t�@�C�������擾����
	virtual bool						GetLayoutMap( D_csmMap<D_csmString, float>& outLayoutMap ) = 0 ;	// ���C�A�E�g�����擾����
	virtual int							GetEyeBlinkParameterCount() = 0 ;									// �ڃp�`�Ɋ֘A�t����ꂽ�p�����[�^�̐����擾����
	virtual D_CubismIdHandle			GetEyeBlinkParameterId( int index ) = 0 ;							// �ڃp�`�Ɋ֘A�t����ꂽ�p�����[�^��ID���擾����
	virtual int							GetLipSyncParameterCount() = 0 ;									// ���b�v�V���N�Ɋ֘A�t����ꂽ�p�����[�^�̐����擾����
	virtual D_CubismIdHandle			GetLipSyncParameterId( int index ) = 0 ;							// ���b�v�V���N�Ɋ֘A�t����ꂽ�p�����[�^��ID���擾����
} ;

// Model3Json�p�[�T�[.
class D_CubismModelSettingJson : public D_ICubismModelSetting
{
public:
	D_CubismModelSettingJson( const BYTE* buffer, size_t size ) ;								// �����t���R���X�g���N�^
	virtual ~D_CubismModelSettingJson() ;													// �f�X�g���N�^
	D_CubismJson*				GetJsonPointer() const ;									// CubismJson�I�u�W�F�N�g�̃|�C���^���擾����
	const char*					GetModelFileName() ;
	const char*					GetModelFileNameA() ;
	const BYTE/*wchar_t*/ *		GetModelFileNameW() ;
	int							GetTextureCount() ;
	const char*					GetTextureDirectory() ;
	const char*					GetTextureDirectoryA() ;
	const BYTE/*wchar_t*/ *		GetTextureDirectoryW() ;
	const char*					GetTextureFileName( int index ) ;
	const char*					GetTextureFileNameA( int index ) ;
	const BYTE/*wchar_t*/ *		GetTextureFileNameW( int index ) ;
	int							GetHitAreasCount() ;
	D_CubismIdHandle			GetHitAreaId( int index ) ;
	const char*					GetHitAreaName( int index ) ;
	const char*					GetHitAreaNameA( int index ) ;
	const BYTE/*wchar_t*/ *		GetHitAreaNameW( int index ) ;
	const char*					GetPhysicsFileName() ;
	const char*					GetPhysicsFileNameA() ;
	const BYTE/*wchar_t*/ *		GetPhysicsFileNameW() ;
	const char*					GetPoseFileName() ;
	const char*					GetPoseFileNameA() ;
	const BYTE/*wchar_t*/ *		GetPoseFileNameW() ;
	int							GetExpressionCount() ;
	const char*					GetExpressionName( int index ) ;
	const char*					GetExpressionNameA( int index ) ;
	const BYTE/*wchar_t*/ *		GetExpressionNameW( int index ) ;
	const char*					GetExpressionFileName( int index ) ;
	const char*					GetExpressionFileNameA( int index ) ;
	const BYTE/*wchar_t*/ *		GetExpressionFileNameW( int index ) ;
	int							GetMotionGroupCount() ;
	const char*					GetMotionGroupName( int index ) ;
	const char*					GetMotionGroupNameA( int index ) ;
	const BYTE/*wchar_t*/ *		GetMotionGroupNameW( int index ) ;
	int							GetMotionCount( const char* groupName ) ;
	const char*					GetMotionFileName( const char* groupName, int index ) ;
	const char*					GetMotionFileNameA( const char* groupName, int index ) ;
	const BYTE/*wchar_t*/ *		GetMotionFileNameW( const char* groupName, int index ) ;
	const char*					GetMotionSoundFileName( const char* groupName, int index ) ;
	const char*					GetMotionSoundFileNameA( const char* groupName, int index ) ;
	const BYTE/*wchar_t*/ *		GetMotionSoundFileNameW( const char* groupName, int index ) ;
	float						GetMotionFadeInTimeValue( const char* groupName, int index ) ;
	float						GetMotionFadeOutTimeValue( const char* groupName, int index ) ;
	const char*					GetUserDataFile() ;
	const char*					GetUserDataFileA() ;
	const BYTE/*wchar_t*/ *		GetUserDataFileW() ;
	bool						GetLayoutMap( D_csmMap<D_csmString, float>& outLayoutMap ) ;
	int							GetEyeBlinkParameterCount() ;
	D_CubismIdHandle			GetEyeBlinkParameterId( int index ) ;
	int							GetLipSyncParameterCount() ;
	D_CubismIdHandle			GetLipSyncParameterId( int index ) ;

private:
	enum FrequentNode
	{
		FrequentNode_Groups,		// GetRoot()[Groups] 
		FrequentNode_Moc,			// GetRoot()[FileReferences][Moc] 
		FrequentNode_Motions,		// GetRoot()[FileReferences][Motions] 
		FrequentNode_Expressions,	// GetRoot()[FileReferences][Expressions] 
		FrequentNode_Textures,		// GetRoot()[FileReferences][Textures] 
		FrequentNode_Physics,		// GetRoot()[FileReferences][Physics] 
		FrequentNode_Pose,			// GetRoot()[FileReferences][Pose] 
		FrequentNode_HitAreas,		// GetRoot()[HitAreas] 
	} ;

	bool						IsExistModelFile() const ;											// ���f���t�@�C���̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistTextureFiles() const ;										// �e�N�X�`���t�@�C���̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistHitAreas() const ;											// �����蔻��̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistPhysicsFile() const ;										// �������Z�t�@�C���̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistPoseFile() const ;											// �|�[�Y�ݒ�t�@�C���̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistExpressionFile() const ;										// �\��ݒ�t�@�C���̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistMotionGroups() const ;										// ���[�V�����O���[�v�̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistMotionGroupName( const char* groupName ) const ;				// �����Ŏw�肵�����[�V�����O���[�v�̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistMotionSoundFile( const char* groupName, int index ) const ;	// �����Ŏw�肵�����[�V�����ɑΉ�����T�E���h�t�@�C���̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistMotionFadeIn( const char* groupName, int index ) const ;		// �����Ŏw�肵�����[�V�����ɑΉ�����t�F�[�h�C�����Ԃ̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistMotionFadeOut( const char* groupName, int index ) const ;	// �����Ŏw�肵�����[�V�����ɑΉ�����t�F�[�h�A�E�g���Ԃ̃L�[�����݂��邩�ǂ������m�F����
	bool						IsExistUserDataFile() const ;										// UserData�̃t�@�C���������݂��邩�m�F
	bool						IsExistEyeBlinkParameters() const ;									// �ڃp�`�ɑΉ��t����ꂽ�p�����[�^�����݂��邩�ǂ������m�F����
	bool						IsExistLipSyncParameters() const ;									// ���b�v�V���N�ɑΉ��t����ꂽ�p�����[�^�����݂��邩�ǂ������m�F����

	D_CubismJson*				_json ;      // ���f���f�[�^json 
	D_csmVector<D_JsonValue*>	_jsonValue ; // ��json�̕p�o�m�[�h 
} ;

// �����܂΂�������
class D_CubismEyeBlink
{
public:
	// �܂΂����̏��
	enum EyeState
	{
		EyeState_First							= 0,		// �������
		EyeState_Interval						= 1,		// �܂΂������Ă��Ȃ����
		EyeState_Closing						= 2,		// �܂Ԃ������Ă����r���̏��
		EyeState_Closed							= 3,		// �܂Ԃ������Ă�����
		EyeState_Opening						= 4			// �܂Ԃ����J���Ă����r���̏��
	} ;

	static D_CubismEyeBlink*	Create( D_ICubismModelSetting* modelSetting = NULL ) ;				// �C���X�^���X�̍쐬
	static void					Delete( D_CubismEyeBlink* eyeBlink ) ;								// �C���X�^���X�̔j��
	void						SetBlinkingInterval( float blinkigInterval ) ;						// �܂΂����̊Ԋu�̐ݒ�
	void						SetBlinkingSettings( float closing, float closed, float opening ) ;	// �܂��΂��̃��[�V�����̏ڍאݒ�
	void						SetParameterIds( const D_csmVector<D_CubismIdHandle>& parameterIds ) ;// �܂΂���������p�����[�^ID�̃��X�g�̐ݒ�
	const D_csmVector<D_CubismIdHandle>&     GetParameterIds() const ;								// �܂΂���������p�����[�^ID�̃��X�g�̎擾
	void						UpdateParameters( D_CubismModel* model, float deltaTimeSeconds ) ;	// ���f���̃p�����[�^�̍X�V

public:
	D_CubismEyeBlink( D_ICubismModelSetting* modelSetting ) ;								// �R���X�g���N�^
	virtual ~D_CubismEyeBlink() ;															// �f�X�g���N�^
	float						DeterminNextBlinkingTiming() const ;						// ���̂܂΂����̃^�C�~���O�̌���

	int							_blinkingState ;			// ���݂̏��
	D_csmVector<D_CubismIdHandle>   _parameterIds ;			// ����Ώۂ̃p�����[�^��ID�̃��X�g
	float						_nextBlinkingTime ;			// ���̂܂΂����̎���[�b]
	float						_stateStartTimeSeconds ;	// ���݂̏�Ԃ��J�n��������[�b]
	float						_blinkingIntervalSeconds ;	// �܂΂����̊Ԋu[�b]
	float						_closingSeconds ;			// �܂Ԃ�����铮��̏��v����[�b]
	float						_closedSeconds ;			// �܂Ԃ�����Ă��铮��̏��v����[�b]
	float						_openingSeconds ;			// �܂Ԃ����J������̏��v����[�b]
	float						_userTimeSeconds ;			// �f���^���Ԃ̐ώZ�l[�b]

} ;

// �ċz����
class D_CubismBreath
{
public:
	// �ċz�̃p�����[�^���
	struct BreathParameterData
	{
		BreathParameterData() : ParameterId( NULL ), Offset( 0.0f ), Peak( 0.0f ), Cycle( 0.0f ), Weight( 0.0f ) { }	// �R���X�g���N�^
		BreathParameterData( D_CubismIdHandle parameterId, float offset, float peak, float cycle, float weight )		// �R���X�g���N�^
			: ParameterId( parameterId )
			, Offset( offset )
			, Peak( peak )
			, Cycle( cycle )
			, Weight( weight )
		{ }
		D_CubismIdHandle		ParameterId ;				// �ċz���Ђ��Â���p�����[�^ID
		float					Offset ;					// �ċz�𐳌��g�Ƃ����Ƃ��́A�g�̃I�t�Z�b�g
		float					Peak ;						// �ċz�𐳌��g�Ƃ����Ƃ��́A�g�̍���
		float					Cycle ;						// �ċz�𐳌��g�Ƃ����Ƃ��́A�g�̎���
		float					Weight ;					// �p�����[�^�ւ̏d��
	} ;
	static D_CubismBreath*		Create() ;																	// �C���X�^���X�̍쐬
	static void					Delete( D_CubismBreath* instance ) ;										// �C���X�^���X�̔j��
	void						SetParameters( D_csmVector<BreathParameterData>& breathParameters ) ;		// �ċz�̃p�����[�^�̂Ђ��Â�
	D_csmVector<BreathParameterData>& GetParameters() ;														// �ċz�ɂЂ��Â��Ă���p�����[�^�̎擾
	void						UpdateParameters( D_CubismModel* model, float deltaTimeSeconds ) ;			// ���f���̃p�����[�^�̍X�V

private:
	D_CubismBreath() ;																		// �R���X�g���N�^
	virtual ~D_CubismBreath() ;																// �f�X�g���N�^

	D_csmVector<BreathParameterData> _breathParameters ;	// �ċz�ɂЂ��Â��Ă���p�����[�^�̃��X�g
	float						_currentTime ;				// �ώZ����[�b]
} ;

// �p�[�c�̕s�����x�̐ݒ�
class D_CubismPose
{
public:
	// �p�[�c�ɂ܂��f�[�^���Ǘ�
	struct PartData
	{
		PartData() ;																		// �R���X�g���N�^
		PartData( const PartData& v ) ;														// �R�s�[�R���X�g���N�^
		virtual ~PartData() ;																// �f�X�g���N�^
		PartData&				operator=( const PartData& v ) ;							// ����̃I�[�o�[���[�h
		void					Initialize( D_CubismModel* model ) ;						// ������

		D_CubismIdHandle		PartId ;					// �p�[�cID
		int						ParameterIndex ;			// �p�����[�^�̃C���f�b�N�X
		int						PartIndex ;					// �p�[�c�̃C���f�b�N�X
		D_csmVector<PartData>	Link ;						// �A������p�����[�^
	} ;
	static D_CubismPose*		Create( const BYTE* pose3json, size_t size ) ;// �C���X�^���X�̍쐬
	static void					Delete( D_CubismPose* pose ) ;// �C���X�^���X�̔j��
	void						UpdateParameters( D_CubismModel* model, float deltaTimeSeconds ) ;// ���f���̃p�����[�^�̍X�V

private:
	D_CubismPose() ;																		// �R���X�g���N�^
	virtual ~D_CubismPose() ;																// �f�X�g���N�^
	void						Reset( D_CubismModel* model ) ;								// �\����������
	void						CopyPartOpacities( D_CubismModel* model ) ;					// �p�[�c�̕s�����x���R�s�[
	void						DoFade( D_CubismModel* model, float deltaTimeSeconds, int beginIndex, int partGroupCount ) ;// �p�[�c�̃t�F�[�h��������s

	D_csmVector<PartData>		_partGroups ;				// �p�[�c�O���[�v
	D_csmVector<int>			_partGroupCounts ;			// ���ꂼ��̃p�[�c�O���[�v�̌�
	float						_fadeTimeSeconds ;			// �t�F�[�h����[�b]
	D_CubismModel*				_lastModel ;				// �O�񑀍삵�����f��
} ;

// ��̌����̐��䏈��
class D_CubismTargetPoint
{
public:
	D_CubismTargetPoint() ;																	// �R���X�g���N�^
	virtual ~D_CubismTargetPoint() ;														// �f�X�g���N�^
	void						Update( float deltaTimeSeconds ) ;							// �X�V����
	float						GetX() const ;												// X���̊�̌����̒l���擾
	float						GetY() const ;												// Y���̊�̌����̒l���擾
	void						Set( float x, float y ) ;									// ��̌����̖ڕW�l��ݒ�

private:
	float						_faceTargetX ;				// ��̌�����X�ڕW�l(���̒l�ɋ߂Â��Ă���)
	float						_faceTargetY ;				// ��̌�����Y�ڕW�l(���̒l�ɋ߂Â��Ă���)
	float						_faceX ;					// ��̌���X(-1.0 - 1.0)
	float						_faceY ;					// ��̌���Y(-1.0 - 1.0)
	float						_faceVX ;					// ��̌����̕ω����xX
	float						_faceVY ;					// ��̌����̕ω����xY
	float						_lastTimeSeconds ;			// �Ō�̎��s����[�b]
	float						_userTimeSeconds ;			// �f���^���Ԃ̐ώZ�l[�b]
} ;

// �������Z�̓K�p��̎��
enum D_CubismPhysicsTargetType
{
    D_CubismPhysicsTargetType_Parameter			= 0,		// �p�����[�^�ɑ΂��ēK�p
} ;

// �������Z�̓��͂̎��
enum D_CubismPhysicsSource
{
    D_CubismPhysicsSource_X						= 0,		// X���̈ʒu����
    D_CubismPhysicsSource_Y						= 1,		// Y���̈ʒu����
    D_CubismPhysicsSource_Angle					= 2,		// �p�x����
} ;

// �������Z�Ŏg�p����O���̗�
struct D_PhysicsJsonEffectiveForces
{
    D_CubismVector2				Gravity ;					// �d��
    D_CubismVector2				Wind ;						// ��
} ;

// �������Z�̃p�����[�^���
struct D_CubismPhysicsParameter
{
    D_CubismIdHandle			Id ;						// �p�����[�^ID
    D_CubismPhysicsTargetType	TargetType ;				// �K�p��̎��
} ;

// �������Z�̐��K�����
struct D_CubismPhysicsNormalization
{
    float						Minimum ;					// �ő�l
    float						Maximum ;					// �ŏ��l
    float						Default ;					// �f�t�H���g�l
} ;

// �������Z�̉��Z�Ɏg�p���镨���_�̏��
struct D_CubismPhysicsParticle
{
    D_CubismVector2				InitialPosition ;			// �����ʒu
    float						Mobility ;					// �����₷��
    float						Delay ;						// �x��
    float						Acceleration ;				// �����x
    float						Radius ;					// ����
    D_CubismVector2				Position ;					// ���݂̈ʒu
    D_CubismVector2				LastPosition ;				// �Ō�̈ʒu
    D_CubismVector2				LastGravity ;				// �Ō�̏d��
    D_CubismVector2				Force ;						// ���݂������Ă����
    D_CubismVector2				Velocity ;					// ���݂̑��x
} ;

// �������Z�̕����_�̊Ǘ�
struct D_CubismPhysicsSubRig
{
    int							InputCount ;				// ���͂̌�
    int							OutputCount ;				// �o�͂̌�
    int							ParticleCount ;				// �����_�̌�
    int							BaseInputIndex ;			// ���͂̍ŏ��̃C���f�b�N�X
    int							BaseOutputIndex ;			// �o�͂̍ŏ��̃C���f�b�N�X
    int							BaseParticleIndex ;			// �����_�̍ŏ��̃C���f�b�N�X
    D_CubismPhysicsNormalization NormalizationPosition ;	// ���K�����ꂽ�ʒu
    D_CubismPhysicsNormalization NormalizationAngle ;		// ���K�����ꂽ�p�x
} ;

// ���K�����ꂽ�p�����[�^�̎擾�֐��̐錾
typedef void ( *D_NormalizedPhysicsParameterValueGetter )(
    D_CubismVector2*			targetTranslation,
    float*						targetAngle,
    float						value,
    float						parameterMinimumValue,
    float						parameterMaximumValue,
    float						parameterDefaultValue,
    D_CubismPhysicsNormalization* normalizationPosition,
    D_CubismPhysicsNormalization* normalizationAngle,
    int							isInverted,
    float						weight
) ;

// �������Z�̒l�̎擾�֐��̐錾
typedef float ( *D_PhysicsValueGetter )(
    D_CubismVector2				translation,
    D_CubismPhysicsParticle*	particles,
    int							particleIndex,
    int							isInverted,
    D_CubismVector2				parentGravity
) ;

// �������Z�̃X�P�[���̎擾�֐��̐錾
typedef float ( *D_PhysicsScaleGetter )( D_CubismVector2 translationScale, float angleScale ) ;

// �������Z�̓��͏��
struct D_CubismPhysicsInput
{
    D_CubismPhysicsParameter	Source ;					// ���͌��̃p�����[�^
    int							SourceParameterIndex ;		// ���͌��̃p�����[�^�̃C���f�b�N�X
    float						Weight ;					// �d��
    short						Type ;						// ���͂̎��
    short						Reflect ;					// �l�����]����Ă��邩�ǂ���
    D_NormalizedPhysicsParameterValueGetter GetNormalizedParameterValue ;	// ���K�����ꂽ�p�����[�^�l�̎擾�֐�
} ;

// �������Z�̏o�͏��
struct D_CubismPhysicsOutput
{
    D_CubismPhysicsParameter	Destination ;				// �o�͐�̃p�����[�^
    int							DestinationParameterIndex ;	// �o�͐�̃p�����[�^�̃C���f�b�N�X
    int							VertexIndex ;				// �U��q�̃C���f�b�N�X
    D_CubismVector2				TranslationScale ;			// �ړ��l�̃X�P�[��
    float						AngleScale ;				// �p�x�̃X�P�[��
    float						Weight ;					// �d��
    D_CubismPhysicsSource		Type ;						// �o�͂̎��
    short						Reflect ;					// �l�����]����Ă��邩�ǂ���
    float						ValueBelowMinimum ;			// �ŏ��l������������̒l
    float						ValueExceededMaximum ;		// �ő�l�����������̒l
    D_PhysicsValueGetter		GetValue ;					// �������Z�̒l�̎擾�֐�
    D_PhysicsScaleGetter		GetScale ;					// �������Z�̃X�P�[���l�̎擾�֐�
} ;

// �������Z�̃f�[�^
struct D_CubismPhysicsRig
{
    int							SubRigCount ;				// �������Z�̕����_�̌�
    D_csmVector<D_CubismPhysicsSubRig> Settings ;			// �������Z�̕����_�̊Ǘ��̃��X�g
    D_csmVector<D_CubismPhysicsInput> Inputs ;				// �������Z�̓��͂̃��X�g
    D_csmVector<D_CubismPhysicsOutput> Outputs ;			// �������Z�̏o�͂̃��X�g
    D_csmVector<D_CubismPhysicsParticle> Particles ;		// �������Z�̕����_�̃��X�g
    D_CubismVector2				Gravity ;					// �d��
    D_CubismVector2				Wind ;						// ��
} ;

// physics3.json�̃R���e�i
class D_CubismPhysicsJson
{
public:
	D_CubismPhysicsJson( const BYTE* buffer, size_t size ) ;													// �R���X�g���N�^
	virtual ~D_CubismPhysicsJson() ;																			// �f�X�g���N�^
	D_CubismVector2				GetGravity() const ;														// �d�͂̎擾
	D_CubismVector2				GetWind() const ;															// ���̎擾
	int							GetSubRigCount() const ;													// �����_�̊Ǘ��̌��̎擾
	int							GetTotalInputCount() const ;												// ���͂̑����v�̎擾
	int							GetTotalOutputCount() const ;												// �o�͂̑����v�̎擾
	int							GetVertexCount() const ;													// �����_�̌��̎擾
	float						GetNormalizationPositionMinimumValue( int physicsSettingIndex ) const ;		// ���K�����ꂽ�ʒu�̍ŏ��l�̎擾
	float						GetNormalizationPositionMaximumValue( int physicsSettingIndex ) const ;		// ���K�����ꂽ�ʒu�̍ő�l�̎擾
	float						GetNormalizationPositionDefaultValue( int physicsSettingIndex ) const ;		// ���K�����ꂽ�ʒu�̃f�t�H���g�l�̎擾
	float						GetNormalizationAngleMinimumValue( int physicsSettingIndex ) const ;		// ���K�����ꂽ�p�x�̍ŏ��l�̎擾
	float						GetNormalizationAngleMaximumValue( int physicsSettingIndex ) const ;		// ���K�����ꂽ�p�x�̍ő�l�̎擾
	float						GetNormalizationAngleDefaultValue( int physicsSettingIndex ) const ;		// ���K�����ꂽ�p�x�̃f�t�H���g�l�̎擾
	int							GetInputCount( int physicsSettingIndex ) const ;							// ���͂̌��̎擾
	float						GetInputWeight( int physicsSettingIndex, int inputIndex ) const ;			// ���͂̏d�݂̎擾
	bool						GetInputReflect( int physicsSettingIndex, int inputIndex ) const ;			// ���͂̔��]�̎擾
	const char*					GetInputType( int physicsSettingIndex, int inputIndex ) const ;				// ���͂̎�ނ̎擾
	D_CubismIdHandle			GetInputSourceId( int physicsSettingIndex, int inputIndex ) const ;			// ���͌���ID�̎擾
	int							GetOutputCount( int physicsSettingIndex ) const ;							// �o�͂̌��̎擾
	int							GetOutputVertexIndex( int physicsSettingIndex, int outputIndex ) const ;	// �o�͂̕����_�̃C���f�b�N�X�̎擾
	float						GetOutputAngleScale( int physicsSettingIndex, int outputIndex ) const ;		// �o�͂̊p�x�̃X�P�[���̎擾
	float						GetOutputWeight( int physicsSettingIndex, int outputIndex ) const ;			// �o�͂̏d�݂̎擾
	D_CubismIdHandle			GetOutputsDestinationId( int physicsSettingIndex, int outputIndex ) const ;	// �o�͐��ID�̎擾
	const char*					GetOutputType( int physicsSettingIndex, int outputIndex ) const ;			// �o�͂̎�ނ̎擾
	bool						GetOutputReflect( int physicsSettingIndex, int outputIndex ) const ;		// �o�͂̔��]�̎擾
	int							GetParticleCount( int physicsSettingIndex ) const ;							// �����_�̌��̎擾
	float						GetParticleMobility( int physicsSettingIndex, int vertexIndex ) const ;		// �����_�̓����₷���̎擾
	float						GetParticleDelay( int physicsSettingIndex, int vertexIndex ) const ;		// �����_�̒x��̎擾
	float						GetParticleAcceleration( int physicsSettingIndex, int vertexIndex ) const ;	// �����_�̉����x�̎擾
	float						GetParticleRadius( int physicsSettingIndex, int vertexIndex ) const ;		// �����_�̋����̎擾
	D_CubismVector2				GetParticlePosition( int physicsSettingIndex, int vertexIndex ) const ;		// �����_�̈ʒu�̎擾

private:
	D_CubismJson* _json ;          // physics3.json�f�[�^
} ;

// �������Z�N���X
class D_CubismPhysics
{
public:
	// �I�v�V����
	struct Options
	{
		D_CubismVector2			Gravity ;					// �d�͕���
		D_CubismVector2			Wind ;						// ���̕���
	} ;
	static D_CubismPhysics*		Create( const BYTE* buffer, size_t size ) ;					// �C���X�^���X�̍쐬
	static void					Delete( D_CubismPhysics* physics ) ;						// �C���X�^���X�̔j��
	void						Evaluate( D_CubismModel* model, float deltaTimeSeconds ) ;	// �������Z�̕]��
	void						SetOptions( const Options& options ) ;						// �I�v�V�����̐ݒ�
	const Options&				GetOptions() const ;										// �I�v�V�����̎擾

private:
	D_CubismPhysics() ;																		// �R���X�g���N�^
	virtual ~D_CubismPhysics() ;															// �f�X�g���N�^
	D_CubismPhysics( const D_CubismPhysics& ) ;
	D_CubismPhysics&			operator=( const D_CubismPhysics& ) ;
	void						Parse( const BYTE* physicsJson, size_t size ) ;				// physics3.json�̃p�[�X
	void						Initialize() ;												// ������

	D_CubismPhysicsRig*			_physicsRig ;				// �������Z�̃f�[�^
	Options						_options ;					// �I�v�V����
} ;

class D_CubismModelUserDataJson
{
public:
	D_CubismModelUserDataJson( const BYTE* buffer, size_t size ) ;							// �R���X�g���N�^
	virtual ~D_CubismModelUserDataJson() ;													// �f�X�g���N�^
	int							GetUserDataCount() const ;									// ���[�U�f�[�^���̎擾
	int							GetTotalUserDataSize() const ;								// ���[�U�f�[�^�������񐔂̎擾
	D_csmString					GetUserDataTargetType( int i ) const ;						// ���[�U�f�[�^�̃^�C�v�̎擾
	D_CubismIdHandle			GetUserDataId( int i ) const ;								// ���[�U�f�[�^�̃^�[�Q�b�gID�̎擾
	const char*					GetUserDataValue( int i ) const ;							// ���[�U�f�[�^�̕�����̎擾

private:
	D_CubismJson*				_json ;
} ;

// ���[�U�f�[�^�̊Ǘ��N���X
class D_CubismModelUserData
{
public:
	// ���[�U�f�[�^�\����
	struct CubismModelUserDataNode
	{
		D_CubismIdHandle		TargetType ;				// ���[�U�f�[�^�^�[�Q�b�g�^�C�v
		D_CubismIdHandle		TargetId ;					// ���[�U�f�[�^�^�[�Q�b�g��ID
		D_csmString				Value ;						// ���[�U�f�[�^
	} ;
	static D_CubismModelUserData* Create( const BYTE* buffer, size_t size ) ;				// �C���X�^���X�̍쐬
	static void					Delete( D_CubismModelUserData* modelUserData ) ;			// �C���X�^���X�̔j��
	virtual ~D_CubismModelUserData() ;														// �f�X�g���N�^
	const D_csmVector<const CubismModelUserDataNode*>& GetArtMeshUserDatas() const ;		// ArtMesh�̃��[�U�f�[�^�̃��X�g�̎擾

private:
	void ParseUserData( const BYTE* buffer, size_t size ) ;									// userdata3.json�̃p�[�X

	D_csmVector<const CubismModelUserDataNode*> _userDataNodes ;		// ���[�U�f�[�^�\���̔z��
	D_csmVector<const CubismModelUserDataNode*> _artMeshUserDataNodes ;	// �{�����X�g�ێ�
} ;

// ���f���`����������郌���_��
class D_CubismRenderer
{
public:
	// �e�N�X�`���̐F��RGBA�ň������߂̍\����
	struct CubismTextureColor
	{
		CubismTextureColor() : R( 1.0f ), G( 1.0f ), B( 1.0f ), A( 1.0f ) {} ;				// �R���X�g���N�^
		virtual ~CubismTextureColor() {} ;													// �f�X�g���N�^

		float					R ;							// �ԃ`�����l��
		float					G ;							// �΃`�����l��
		float					B ;							// �`�����l��
		float					A ;							// ���`�����l��
	} ; // CubismTextureColor
	static D_CubismRenderer*	Create() ;													// �����_���̃C���X�^���X�𐶐����Ď擾����
	static void					Delete( D_CubismRenderer* renderer ) ;						// �����_���̃C���X�^���X���������
	static void					StaticRelease() ;											// �����_�����ێ�����ÓI�ȃ��\�[�X���������
	virtual void				Initialize( D_CubismModel* model, int ASyncThread ) ;		// �����_���̏��������������s����
	void						DrawModel() ;												// ���f����`�悷��
	void						SetMvpMatrix( D_CubismMatrix44* matrix4x4 ) ;				// Model-View-Projection �s����Z�b�g����
	D_CubismMatrix44			GetMvpMatrix() const ;										// Model-View-Projection �s����擾����
	void						SetModelColor( float red, float green, float blue, float alpha ) ;	// ���f���̐F���Z�b�g����B
	CubismTextureColor			GetModelColor() const ;										// ���f���̐F���擾����B
	void						IsPremultipliedAlpha( bool enable ) ;						//  ��Z�ς݃��̗L���E�������Z�b�g����B
	bool						IsPremultipliedAlpha() const ;								//  ��Z�ς݃��̗L���E�������擾����B
	void						IsCulling( bool culling ) ;									//  �J�����O�i�Жʕ`��j�̗L���E�������Z�b�g����B
	bool						IsCulling() const ;											//  �J�����O�i�Жʕ`��j�̗L���E�������擾����B
	void						SetAnisotropy( float anisotropy ) ;							// �e�N�X�`���ٕ̈����t�B���^�����O�̃p�����[�^���Z�b�g����
	float						GetAnisotropy() const ;										// �e�N�X�`���ٕ̈����t�B���^�����O�̃p�����[�^���Z�b�g����
	D_CubismModel*				GetModel() const ;											// �����_�����O���郂�f�����擾����B
	void						UseHighPrecisionMask( bool high ) ;							// �}�X�N�`��̕�����ύX����B
	bool						IsUsingHighPrecisionMask() ;								// �}�X�N�`��̕������擾����B

protected:
	D_CubismRenderer() ;																	// �R���X�g���N�^
	virtual ~D_CubismRenderer() ;															// �f�X�g���N�^
	virtual void				DoDrawModel() = 0 ;											// ���f���`��̎���
	virtual void				DrawMesh( int textureNo, int indexCount, int vertexCount, WORD* indexArray, float* vertexArray, float* uvArray, float opacity, D_CubismBlendMode colorBlendMode, bool invertedMask ) = 0 ;	// �`��I�u�W�F�N�g�i�A�[�g���b�V���j��`�悷��B
	virtual void				SaveProfile() = 0 ;											// ���f���`�撼�O�̃����_���̃X�e�[�g��ێ�����
	virtual void				RestoreProfile() = 0 ;										// ���f���`�撼�O�̃����_���̃X�e�[�g�𕜋A������

private:
	// �R�s�[�R���X�g���N�^���B��
	D_CubismRenderer( const D_CubismRenderer& ) ;
	D_CubismRenderer&			operator=( const D_CubismRenderer& ) ;

	D_CubismMatrix44			_mvpMatrix4x4 ;				// Model-View-Projection �s��
	CubismTextureColor			_modelColor ;				// ���f�����̂̃J���[(RGBA)
	bool						_isCulling ;				// �J�����O���L���Ȃ�true
	bool						_isPremultipliedAlpha ;		// ��Z�ς݃��Ȃ�true
	float						_anisotropy ;				// �e�N�X�`���ٕ̈����t�B���^�����O�̃p�����[�^
	D_CubismModel*				_model ;					// �����_�����O�Ώۂ̃��f��
	bool						_useHighPrecisionMask ;		// false�̏ꍇ�A�}�X�N��Z�߂ĕ`�悷�� true�̏ꍇ�A�}�X�N�̓p�[�c�`�悲�Ƃɏ������� 
} ;

//  �O���錾
class D_CubismRenderer_DxLib ;
class D_CubismShader_DxLib ;
class D_CubismClippingContext ;

//  �I�t�X�N���[���`��p�\����
class D_CubismOffscreenFrame_DxLib
{
public:
	D_CubismOffscreenFrame_DxLib() ;
	void						BeginDraw() ;												// �w��̕`��^�[�Q�b�g�Ɍ����ĕ`��J�n
	void						EndDraw() ;													// �`��I��
	void						Clear( float r, float g, float b, float a ) ;				// �����_�����O�^�[�Q�b�g�̃N���A
	bool						CreateOffscreenFrame( DWORD displayBufferWidth, DWORD displayBufferHeight ) ;// CubismOffscreenFrame�쐬
	void						DestroyOffscreenFrame() ;									// CubismOffscreenFrame�̍폜
	void						SetClearColor( float r, float g, float b, float a ) ;		// �N���A�J���[�̏㏑��
	int							GetTextureView() const ;									// �e�N�X�`���r���[�ւ̃A�N�Z�b�T
	DWORD						GetBufferWidth() const ;									// �o�b�t�@���擾
	DWORD						GetBufferHeight() const ;									// �o�b�t�@�����擾
	bool						IsValid() const ;											// ���ݗL�����ǂ���

private:
	int							_GraphHandle ;				// �����e�N�X�`�� 
	int							_BackupDrawScreen ;
	DWORD						_bufferWidth ;				// Create���Ɏw�肳�ꂽ�T�C�Y 
	DWORD						_bufferHeight ;				// Create���Ɏw�肳�ꂽ�T�C�Y 

} ;

// DirectX::XMMATRIX�ɕϊ�
MATRIX D_ConvertToD3DX( D_CubismMatrix44& mtx ) ;

//  �N���b�s���O�}�X�N�̏��������s����N���X
class D_CubismClippingManager_DxLib
{
	friend class D_CubismShader_DxLib ;
	friend class D_CubismRenderer_DxLib ;

private:
	D_CubismClippingManager_DxLib() ;														//  �R���X�g���N�^
	virtual ~D_CubismClippingManager_DxLib() ;												//  �f�X�g���N�^
	D_CubismRenderer::CubismTextureColor* GetChannelFlagAsColor( int channelNo ) ;			// �J���[�`�����l��(RGBA)�̃t���O���擾����
	void						CalcClippedDrawTotalBounds( D_CubismModel& model, D_CubismClippingContext* clippingContext ) ;// �}�X�N�����`��I�u�W�F�N�g�Q�S�̂��͂ދ�`(���f�����W�n)���v�Z����
	void						Initialize( D_CubismModel& model, int drawableCount, const int** drawableMasks, const int* drawableMaskCounts ) ;//  �}�l�[�W���̏���������
	void						SetupClippingContext( D_CubismModel& model, D_CubismRenderer_DxLib* renderer, D_CubismOffscreenFrame_DxLib& useTarget ) ;// �N���b�s���O�R���e�L�X�g���쐬����B���f���`�掞�Ɏ��s����B
	D_CubismClippingContext*	FindSameClip( const int* drawableMasks, int drawableMaskCounts ) const ;// ���Ƀ}�X�N������Ă��邩���m�F�B
	void						SetupLayoutBounds( int usingClipCount ) const ;				// �N���b�s���O�R���e�L�X�g��z�u���郌�C�A�E�g�B
	D_CubismOffscreenFrame_DxLib* GetColorBuffer() const ;									// �J���[�o�b�t�@�̃A�h���X���擾����
	D_csmVector<D_CubismClippingContext*>* GetClippingContextListForDraw() ;				// ��ʕ`��Ɏg�p����N���b�s���O�}�X�N�̃��X�g���擾����
	void						SetClippingMaskBufferSize( int size ) ;						// �N���b�s���O�}�X�N�o�b�t�@�̃T�C�Y��ݒ肷��
	int							GetClippingMaskBufferSize() const ;							// �N���b�s���O�}�X�N�o�b�t�@�̃T�C�Y���擾����

	D_CubismOffscreenFrame_DxLib*						_colorBuffer ;						// �}�X�N�p�J���[�o�b�t�@�[�̃A�h���X
	int													_currentFrameNo ;					// �}�X�N�e�N�X�`���ɗ^����t���[���ԍ�
	D_csmVector<D_CubismRenderer::CubismTextureColor*>	_channelColors ;
	D_csmVector<D_CubismClippingContext*>				_clippingContextListForMask ;		// �}�X�N�p�N���b�s���O�R���e�L�X�g�̃��X�g
	D_csmVector<D_CubismClippingContext*>				_clippingContextListForDraw ;		// �`��p�N���b�s���O�R���e�L�X�g�̃��X�g
	int													_clippingMaskBufferSize ;			// �N���b�s���O�}�X�N�̃o�b�t�@�T�C�Y�i�����l:256�j
	D_CubismMatrix44									_tmpMatrix ;						// �}�X�N�v�Z�p�̍s��
	D_CubismMatrix44									_tmpMatrixForMask ;					// �}�X�N�v�Z�p�̍s��
	D_CubismMatrix44									_tmpMatrixForDraw ;					// �}�X�N�v�Z�p�̍s��
	D_csmRectF											_tmpBoundsOnModel ;					// �}�X�N�z�u�v�Z�p�̋�`
} ;

// �N���b�s���O�}�X�N�̃R���e�L�X�g
class D_CubismClippingContext
{
	friend class D_CubismClippingManager_DxLib;
	friend class D_CubismShader_DxLib;
	friend class D_CubismRenderer_DxLib;

public:
	D_CubismClippingContext( D_CubismClippingManager_DxLib* manager, const int* clippingDrawableIndices, int clipCount ) ;// �����t���R���X�g���N�^
	virtual ~D_CubismClippingContext() ;													// �f�X�g���N�^
	void						AddClippedDrawable( int drawableIndex ) ;					// ���̃}�X�N�ɃN���b�v�����`��I�u�W�F�N�g��ǉ�����
	D_CubismClippingManager_DxLib*	GetClippingManager() ;									// ���̃}�X�N���Ǘ�����}�l�[�W���̃C���X�^���X���擾����B

	bool						_isUsing ;					// ���݂̕`���ԂŃ}�X�N�̏������K�v�Ȃ�true
	const int*					_clippingIdList ;			// �N���b�s���O�}�X�N��ID���X�g
	int							_clippingIdCount ;			// �N���b�s���O�}�X�N�̐�
	int							_layoutChannelNo ;			// RGBA�̂�����̃`�����l���ɂ��̃N���b�v��z�u���邩(0:R , 1:G , 2:B , 3:A)
	D_csmRectF*					_layoutBounds ;				// �}�X�N�p�`�����l���̂ǂ̗̈�Ƀ}�X�N�����邩(View���W-1..1, UV��0..1�ɒ���)
	D_csmRectF*					_allClippedDrawRect ;		// ���̃N���b�s���O�ŁA�N���b�s���O�����S�Ă̕`��I�u�W�F�N�g�̈͂݋�`�i����X�V�j
	D_CubismMatrix44			_matrixForMask ;			// �}�X�N�̈ʒu�v�Z���ʂ�ێ�����s��
	D_CubismMatrix44			_matrixForDraw ;			// �`��I�u�W�F�N�g�̈ʒu�v�Z���ʂ�ێ�����s��
	D_csmVector<int>*			_clippedDrawableIndexList ;	// ���̃}�X�N�ɃN���b�v�����`��I�u�W�F�N�g�̃��X�g
	D_CubismClippingManager_DxLib* _owner;					// ���̃}�X�N���Ǘ����Ă���}�l�[�W���̃C���X�^���X
} ;

class D_CubismRenderer_DxLib ;

//  CubismDX11�����Őݒ肷��X�e�[�g�̂����A�r���ŕύX����\���̂�����̂��Ǘ��BD_CubismRenderer_DxLib���V���O���g���Ƃ��ĊǗ��B
class D_CubismRenderState_DxLib
{
	friend class D_CubismRenderer_DxLib;
public:
	enum
	{
		State_None								= 0,
		State_Blend								= 1,		// �u�����h���[�h 
		State_Viewport							= 2,		// �r���[�|�[�g 
		State_ZEnable							= 3,		// Z�L������ 
		State_CullMode							= 4,		// �J�����O���[�h 
		State_Sampler							= 5,		// �e�N�X�`���t�B���^�[ 
		State_Max								= 6,
	} ;
	// �u�����h�X�e�[�g D3D11�ł̓I�u�W�F�N�g�P�ʂł̊Ǘ� 
	enum Blend
	{
		Blend_Origin							= 0,
		Blend_Zero								= 1,
		Blend_Normal							= 2,
		Blend_Add								= 3,
		Blend_Mult								= 4,
		Blend_Mask								= 5,
		Blend_Max								= 6,
	} ;
	// �J�����O D3D11�ł̓I�u�W�F�N�g�P�ʂł̊Ǘ� 
	enum Cull
	{
		Cull_Origin								= 0,		// ���X�̐ݒ� 
		Cull_None								= 1,		// �J�����O���� 
		Cull_Ccw								= 2,		// CCW�\�� 
		Cull_Max								= 3,
	} ;
	// Z D3D11�ł̓I�u�W�F�N�g�P�ʂł̊Ǘ� 
	enum Depth
	{
		Depth_Origin							= 0,		// ���X�̐ݒ� 
		Depth_Disable							= 1,		// Zoff 
		Depth_Enable							= 2,		// Zon 
		Depth_Max								= 3,
	} ;
	// �T���v���[�X�e�[�g D3D11�ł̓I�u�W�F�N�g�P�ʂł̊Ǘ� 
	enum Sampler
	{
		Sampler_Origin							= 0,		// ���X�̐ݒ� 
		Sampler_Normal							= 1,		// �g�p�X�e�[�g 
		Sampler_Max								= 2,
	} ;

	// �f�t�H���g��=�ŃR�s�[���܂�
	struct Stored
	{
		Stored()
		{
			_blendState = Blend_Zero;
			_blendFactor_r = 0.0f;
			_blendFactor_g = 0.0f;
			_blendFactor_b = 0.0f;
			_blendFactor_a = 0.0f;
			_blendMask = 0xffffffff;
			_cullMode = Cull_None;
			_depthEnable = Depth_Disable;
			_depthRef = 0 ;
			_viewportX = 0 ;
			_viewportY = 0 ;
			_viewportWidth = 0 ;
			_viewportHeight = 0 ;
			_viewportMinZ = 0.0f;
			_viewportMaxZ = 0.0f;
			_sampler = Sampler_Normal;
			_MEMSET( _valid, 0, sizeof( _valid ) ) ;
		}
		// State_Blend 
		Blend					_blendState ;
		float					_blendFactor_r ;
		float					_blendFactor_g ;
		float					_blendFactor_b ;
		float					_blendFactor_a ;
		DWORD					_blendMask ;
		// State_CullMode 
		Cull					_cullMode ;
		// State_Viewport 
		float					_viewportX ;
		float					_viewportY ;
		float					_viewportWidth ;
		float					_viewportHeight ;
		float					_viewportMinZ ;
		float					_viewportMaxZ ;
		// State_ZEnable 
		Depth					_depthEnable ;
		DWORD					_depthRef ;
		// State_Sampler 
		Sampler					_sampler ;
		bool					_valid[ State_Max ] ;   // �ݒ肵�����ǂ����B���݂�StartFrame�ň�ʂ�͌Ă�ł��� 
	} ;

	void						StartFrame() ;												// �t���[���擪�ŌĂяo������
	void						Save() ;													// �Ǘ����̃X�e�[�g��Push
	void						Restore() ;													// Push���X�e�[�g��Pop�ASave�̍ۂ�D_CubismRenderState_DxLib�Őݒ肵�Ă��Ȃ��������ڂ͖߂��Ȃ����Ƃɒ���
	void						SetBlend( Blend blendState, float blendFactor_r, float blendFactor_g, float blendFactor_b, float blendFactor_a, DWORD mask, bool force=false ) ;// �u�����h���[�h�Z�b�g
	void						SetCullMode( Cull cullFace, bool force = false ) ;			// �J�����O���[�h�Z�b�g
	void						SetViewport( float left, float top, float width, float height, float zMin, float zMax, bool force = false ) ;// �r���[�|�[�g�Z�b�g
	void						SetZEnable( Depth enable, DWORD stelcilRef, bool force = false ) ;// Z�L�������Z�b�g
	void						SetSampler( Sampler sample, bool force = false ) ;			//  �T���v���[�X�e�[�g�Z�b�g

private:
	D_CubismRenderState_DxLib() ;
	~D_CubismRenderState_DxLib() ;
	void						Create() ;													// �e��I�u�W�F�N�g���쐬����
	void						SaveCurrentNativeState() ;									// D3DDevice����ACubism�Ɋ֌W����l���擾����������D_CubismRenderState_DxLib�ɔ��f��Save���Ăяo���A_pushed�͔j���ACubism�t���[�������̍ŏ��AStartFrame�̌�ŌĂ�ł���
	void						RestoreNativeState() ;										// �ŏ���Push�����X�e�[�g�܂Ŗ߂�

	Stored						_stored ;					// �X�g�A���ꂽ�e��ݒ� 
	D_csmVector<Stored>			_pushed ;
	int							backupBlendMode ;
	int							backupBlendParam ;
	int							backupCullMode ;
	int							backupUseZBuffer ;
	int							backupMaxAnisotropy ;
	int							backupDrawMode ;
	RECT						backupDrawArea ;
	int							backupDrawAlphaTestMode ;
	int							backupDrawAlphaTestParam ;
	int							backupDrawBright_r ;
	int							backupDrawBright_g ;
	int							backupDrawBright_b ;
} ;

enum D_ShaderNames
{
	// SetupMask
	D_ShaderNames_SetupMask									= 0,

	//Normal
	D_ShaderNames_Normal									= 1,
	D_ShaderNames_NormalMasked								= 2,
	D_ShaderNames_NormalMaskedInverted						= 3,
	D_ShaderNames_NormalPremultipliedAlpha					= 4,
	D_ShaderNames_NormalMaskedPremultipliedAlpha			= 5,
	D_ShaderNames_NormalMaskedInvertedPremultipliedAlpha	= 6,

	//Add
	D_ShaderNames_Add										= 7,
	D_ShaderNames_AddMasked									= 8,
	D_ShaderNames_AddMaskedInverted							= 9,
	D_ShaderNames_AddPremultipliedAlpha						= 10,
	D_ShaderNames_AddMaskedPremultipliedAlpha				= 11,
	D_ShaderNames_AddMaskedInvertedPremultipliedAlpha		= 12,

	//Mult
	D_ShaderNames_Mult										= 13,
	D_ShaderNames_MultMasked								= 14,
	D_ShaderNames_MultMaskedInverted						= 15,
	D_ShaderNames_MultPremultipliedAlpha					= 16,
	D_ShaderNames_MultMaskedPremultipliedAlpha				= 17,
	D_ShaderNames_MultMaskedInvertedPremultipliedAlpha		= 18,

	D_ShaderNames_Max										= 19,
} ;

//  �O���錾
class D_CubismRenderer_DxLib ;
class D_CubismClippingContext ;

// Cubism�Ŏg�p����V�F�[�_�Ǘ��N���X�AD_CubismRenderer_DxLib��static�ϐ��Ƃ��Ĉ�������̉������
class D_CubismShader_DxLib
{
	friend class D_CubismRenderer_DxLib;

public:
	D_CubismShader_DxLib() ;																// private�ȃR���X�g���N�^
	virtual ~D_CubismShader_DxLib() ;														// private�ȃf�X�g���N�^
	void						ReleaseShaderProgram() ;									// �V�F�[�_�v���O�������������
	int							GetVertexShader( DWORD assign ) ;							// ���_�V�F�[�_�̎擾
	int							GetPixelShader( DWORD assign ) ;							// �s�N�Z���V�F�[�_�̎擾
	void						SetupShader() ;												// ���_�錾�̃f�o�C�X�ւ̐ݒ�A�V�F�[�_���܂����ݒ�Ȃ烍�[�h

private:
	void						GenerateShaders() ;											// �V�F�[�_�v���O����������������
	bool						LoadShaderProgram( bool isPs, int assign, const char* entryPoint ) ;// �V�F�[�_�v���O���������[�h

	int							_shaderSetsVS[ D_ShaderNames_Max ] ;	// ���[�h�����V�F�[�_�v���O������ێ�����ϐ�(VS) 
	int							_shaderSetsPS[ D_ShaderNames_Max ] ;	// ���[�h�����V�F�[�_�v���O������ێ�����ϐ�(PS) 
} ;

// �V�F�[�_�[�R���X�^���g�o�b�t�@
struct D_CubismConstantBufferDxLib
{
	MATRIX						projectMatrix ;
	MATRIX						clipMatrix ;
	COLOR_F						baseColor ;
	COLOR_F						channelFlag ;
} ;

// DirectX11�p�̕`�施�߂����������N���X
class D_CubismRenderer_DxLib : public D_CubismRenderer
{
	friend class D_CubismRenderer;
	friend class D_CubismClippingManager_DxLib;
	friend class D_CubismShader_DxLib;

public:
	static void					InitializeConstantSettings( DWORD bufferSetNum ) ;			// �����_�����쐬���邽�߂̊e��ݒ�
	static void					SetDefaultRenderState() ;									// CubismRenderState�Ƀf�t�H���g�̐ݒ���Z�b�g����
	static void					StartFrame( DWORD viewportWidth, DWORD viewportHeight ) ;	// Cubism�`��֘A�̐擪�ōs�������B�e�t���[���ł�Cubism�����O�ɂ�����Ă�ł��炤
	static void					EndFrame() ;												// Cubism�`��֘A�̏I�����s�������B�e�t���[���ł�Cubism�����O�ɂ�����Ă�ł��炤
	static D_CubismRenderState_DxLib* GetRenderStateManager() ;								// D_CubismRenderer_DxLib�Ŏg�p���郌���_�[�X�e�[�g�Ǘ��}�l�[�W���擾
	static void					DeleteRenderStateManager() ;								// �����_�[�X�e�[�g�Ǘ��}�l�[�W���폜
	static D_CubismShader_DxLib* GetShaderManager() ;										// �V�F�[�_�Ǘ��@�\�̎擾
	static void					DeleteShaderManager() ;										// �V�F�[�_�Ǘ��@�\�̍폜
	static void					OnDeviceLost() ;											// �f�o�C�X���X�g�E�f�o�C�X�č쐬���R�[������
	static void					GenerateShader() ;											// �g�p�V�F�[�_�[�쐬
	virtual void				Initialize( D_CubismModel* model, int ASyncThread ) ;		// �����_���̏��������������s����A�����ɓn�������f�����烌���_���̏����������ɕK�v�ȏ������o�����Ƃ��ł���
	void						BindTexture( DWORD modelTextureAssign, int textureView ) ;	// OpenGL�e�N�X�`���̃o�C���h�����AD_CubismRenderer�Ƀe�N�X�`����ݒ肵�AD_CubismRenderer���ł��̉摜���Q�Ƃ��邽�߂�Index�l��߂�l�Ƃ���
	const D_csmMap<int, int>&	GetBindedTextures() const ;									// OpenGL�Ƀo�C���h���ꂽ�e�N�X�`���̃��X�g���擾����
	void						SetClippingMaskBufferSize( int size ) ;						//  �N���b�s���O�}�X�N�o�b�t�@�̃T�C�Y��ݒ肷��A�}�X�N�p��FrameBuffer��j���E�č쐬���邽�ߏ����R�X�g�͍����B
	int							GetClippingMaskBufferSize() const ;							//  �N���b�s���O�}�X�N�o�b�t�@�̃T�C�Y���擾����
	void						ExecuteDraw( int vertexBuffer, int indexBuffer, int constantBuffer, const int indexCount, const int textureNo, CubismTextureColor& modelColorRGBA, D_CubismBlendMode colorBlendMode, bool invertedMask ) ;	//  �g�p����V�F�[�_�̐ݒ�E�R���X�^���g�o�b�t�@�̐ݒ�Ȃǂ��s���A�`������s

protected:
	D_CubismRenderer_DxLib() ;																// �R���X�g���N�^
	virtual ~D_CubismRenderer_DxLib() ;														// �f�X�g���N�^
	virtual void				DoDrawModel() ;												// ���f����`�悷����ۂ̏���
	void						DrawMesh( int textureNo, int indexCount, int vertexCount, WORD* indexArray, float* vertexArray, float* uvArray, float opacity, D_CubismBlendMode colorBlendMode, bool invertedMask ) ;
	void						DrawMeshDX11( int drawableIndex, int textureNo, int indexCount, int vertexCount, WORD* indexArray, float* vertexArray, float* uvArray, float opacity, D_CubismBlendMode colorBlendMode, bool invertedMask ) ;// �`��I�u�W�F�N�g�i�A�[�g���b�V���j��`�悷��B�|���S�����b�V���ƃe�N�X�`���ԍ����Z�b�g�œn���B

private:
	static void					DoStaticRelease() ;											// �����_�����ێ�����ÓI�ȃ��\�[�X���������
	static void					ReleaseShader() ;											// �g�p�V�F�[�_�[�ƒ��_��`�̍폜
	D_CubismRenderer_DxLib( const D_CubismRenderer_DxLib& ) ;								// Prevention of copy Constructor
	D_CubismRenderer_DxLib&		operator=( const D_CubismRenderer_DxLib& ) ;
	void						PreDraw() ;													// �`��J�n���̒ǉ������B���f����`�悷��O�ɃN���b�s���O�}�X�N�ɕK�v�ȏ������������Ă���B
	void						PostDraw() ;												// �`�抮����̒ǉ������B
	virtual void				SaveProfile() ;												// ���f���`�撼�O�̃X�e�[�g��ێ�����
	virtual void				RestoreProfile() ;											// ���f���`�撼�O�̃X�e�[�g��ێ�����
	void						SetClippingContextBufferForMask( D_CubismClippingContext* clip ) ;// �}�X�N�e�N�X�`���ɕ`�悷��N���b�s���O�R���e�L�X�g���Z�b�g����B
	D_CubismClippingContext*	GetClippingContextBufferForMask() const ;					// �}�X�N�e�N�X�`���ɕ`�悷��N���b�s���O�R���e�L�X�g���擾����B
	void						SetClippingContextBufferForDraw( D_CubismClippingContext* clip ) ;// ��ʏ�ɕ`�悷��N���b�s���O�R���e�L�X�g���Z�b�g����B
	D_CubismClippingContext*	GetClippingContextBufferForDraw() const ;					// ��ʏ�ɕ`�悷��N���b�s���O�R���e�L�X�g���擾����B
	void						CopyToBuffer( int drawAssign, const int vcount, const float* varray, const float* uvarray ) ;// GetDrawableVertices,GetDrawableVertexUvs�̓��e���o�b�t�@�փR�s�[

	int**						_vertexBuffers ;			// ���_�̃o�b�t�@ 
	int**						_indexBuffers ;				// �C���f�b�N�X�̃o�b�t�@ 
	int**						_constantBuffers ;			// �萔�̃o�b�t�@
	DWORD						_drawableNum ;				// _vertexBuffers, _indexBuffers�̊m�ې� 
	int							_commandBufferNum ;
	int							_commandBufferCurrent ;
	D_csmVector<int>			_sortedDrawableIndexList ;	// �`��I�u�W�F�N�g�̃C���f�b�N�X��`�揇�ɕ��ׂ����X�g
	D_csmMap<int, int>			_textures ;					// ���f�����Q�Ƃ���e�N�X�`���ƃ����_���Ńo�C���h���Ă���e�N�X�`���Ƃ̃}�b�v
	D_csmVector<D_CubismOffscreenFrame_DxLib>	_offscreenFrameBuffer ;			// �}�X�N�`��p�̃t���[���o�b�t�@ 
	D_CubismClippingManager_DxLib*				_clippingManager ;				// �N���b�s���O�}�X�N�Ǘ��I�u�W�F�N�g
	D_CubismClippingContext*					_clippingContextBufferForMask ;	// �}�X�N�e�N�X�`���ɕ`�悷�邽�߂̃N���b�s���O�R���e�L�X�g
	D_CubismClippingContext*					_clippingContextBufferForDraw ;	// ��ʏ�`�悷�邽�߂̃N���b�s���O�R���e�L�X�g
} ;

// ���[�U�[�����ۂɎg�p���郂�f��
class D_CubismUserModel
{
public:
	D_CubismUserModel() ;																	// �R���X�g���N�^
	virtual ~D_CubismUserModel() ;															// �f�X�g���N�^
	virtual bool				IsInitialized() ;											// ��������Ԃ̎擾
	virtual void				IsInitialized( bool v ) ;									// ��������Ԃ̐ݒ�
	virtual bool				IsUpdating() ;												// �X�V��Ԃ̎擾
	virtual void				IsUpdating( bool v ) ;										// �X�V��Ԃ̐ݒ�
	virtual void				SetDragging( float x, float y )	;							// �}�E�X�h���b�O���̐ݒ�
	virtual void				SetAcceleration( float x, float y, float z ) ;				// �����x���̐ݒ�
	D_CubismModelMatrix*		GetModelMatrix() const ;									// ���f���s��̎擾
	virtual void				SetOpacity( float a ) ;										// �s�����x�̐ݒ�
	virtual float				GetOpacity() ;												// �s�����x�̎擾
	virtual void				LoadModel( const BYTE* buffer, size_t size ) ;				// ���f���f�[�^�̓ǂݍ���
	virtual D_ACubismMotion*	LoadMotion( const BYTE* buffer, size_t size, const BYTE/*wchar_t*/ * name ) ;// ���[�V�����f�[�^�̓ǂݍ���
	virtual D_ACubismMotion*	LoadExpression( const BYTE* buffer, size_t size, const BYTE/*wchar_t*/ * name ) ;// �\��f�[�^�̓ǂݍ���
	virtual void				LoadPose( const BYTE* buffer, size_t size ) ;				// �|�[�Y�f�[�^�̓ǂݍ���
	virtual void				LoadPhysics( const BYTE* buffer, size_t size ) ;			// �������Z�f�[�^�̓ǂݍ���
	virtual void				LoadUserData( const BYTE* buffer, size_t size ) ;			// ���f���ɕt�����郆�[�U�[�f�[�^��ǂݍ���
	virtual bool				IsHit( D_CubismIdHandle drawableId, float pointX, float pointY ) ;// �����蔻��̎擾
	D_CubismModel*				GetModel() const ;											// ���f���̎擾
	D_CubismRenderer*			GetRenderer() { return _renderer ; }						// �����_���̎擾
	void						CreateRenderer( int ASyncThread ) ;							// �����_���̐���
	void						DeleteRenderer() ;											// �����_���̉��
	virtual void				MotionEventFired( const D_csmString& eventValue ) ;			//  �C�x���g���Ύ��̕W������
	static void					CubismDefaultMotionEventCallback( const D_CubismMotionQueueManager* caller, const D_csmString& eventValue, void* customData ) ;//  �C�x���g�p��Callback

public:
	D_CubismMoc*				_moc ;						// Moc�f�[�^
	D_CubismModel*				_model ;					// Model�C���X�^���X
	D_CubismMotionManager*		_motionManager ;			// ���[�V�����Ǘ�
	D_CubismMotionManager*		_expressionManager ;		// �\��Ǘ�
	D_CubismEyeBlink*			_eyeBlink ;					// �����܂΂���
	D_CubismBreath*				_breath ;					// �ċz
	D_CubismModelMatrix*		_modelMatrix ;				// ���f���s��
	D_CubismPose*				_pose ;						// �|�[�Y�Ǘ�
	D_CubismTargetPoint*		_dragManager ;				// �}�E�X�h���b�O
	D_CubismPhysics*			_physics ;					// �������Z
	D_CubismModelUserData*		_modelUserData ;			// ���[�U�f�[�^
	bool						_initialized ;				// ���������ꂽ���ǂ���
	bool						_updating ;					// �X�V���ꂽ���ǂ���
	float						_opacity ;					// �s�����x
	bool						_lipSync ;					// ���b�v�V���N���邩�ǂ���
	float						_lastLipSyncValue ;			// �Ō�̃��b�v�V���N�̐���l
	float						_dragX ;					// �}�E�X�h���b�O��X�ʒu
	float						_dragY ;					// �}�E�X�h���b�O��Y�ʒu
	float						_accelerationX ;			// X�������̉����x
	float						_accelerationY ;			// Y�������̉����x
	float						_accelerationZ ;			// Z�������̉����x
	bool						_debugMode ;				// �f�o�b�O���[�h���ǂ���

private:
	D_CubismRenderer*			_renderer ;      // �����_��
} ;

class D_CubismString
{
public:
	static D_csmString			GetFormatedString( const char* format, ... ) ;						// �W���o�͂̏�����K�p������������擾����B
	static bool					IsStartsWith( const char* text, const char* startWord ) ;			// text��startWord�Ŏn�܂��Ă��邩�ǂ�����Ԃ�
	static float				StringToFloat( const char* string, int length, int position, int* outEndPos ) ;// position�ʒu�̕������琔������͂���B

private:
	// �R���X�g���N�^�E�f�X�g���N�^�Ăяo���s�ȐÓI�N���X�ɂ���
	D_CubismString() ;
} ;

struct D_LAppModelParameter
{
	int							parameterIndex ;
	float						parameterValue ;
} ;

// ���[�U�[�����ۂɎg�p���郂�f���̎����N���X���f�������A�����R���|�[�l���g�����A�X�V�����ƃ����_�����O�̌Ăяo�����s���B
class D_LAppModel : public D_CubismUserModel
{
public:
	D_LAppModel() ;																			// �R���X�g���N�^
	virtual ~D_LAppModel() ;																// �f�X�g���N�^
	bool						LoadAssets( const BYTE/*wchar_t*/ * dir, const BYTE/*wchar_t*/ * fileName, int ASyncThread ) ;	// model3.json���u���ꂽ�f�B���N�g���ƃt�@�C���p�X���烂�f���𐶐�����
	void						ReloadRenderer( int ASyncThread ) ;							// �����_�����č\�z����
	void						Update( float deltaTimeSeconds ) ;							// ���f���̍X�V�����B���f���̃p�����[�^����`���Ԃ����肷��B
	void						Draw( D_CubismMatrix44& matrix, bool isMultModelMatrix ) ;	// ���f����`�悷�鏈���B���f����`�悷���Ԃ�View-Projection�s���n���B
	D_CubismMotionQueueEntryHandle StartMotion( const char* group, int no, int priority, float fadeInSeconds, float fadeOutSeconds, bool isLoopFadeIn = true ) ;	// �����Ŏw�肵�����[�V�����̍Đ����J�n����B
	D_CubismMotionQueueEntryHandle StartRandomMotion( const char* group, int priority ) ;	// �����_���ɑI�΂ꂽ���[�V�����̍Đ����J�n����B
	void						SetExpression( const BYTE/*wchar_t*/ * expressionID ) ;		// �����Ŏw�肵���\��[�V�������Z�b�g����
	void						SetRandomExpression() ;										// �����_���ɑI�΂ꂽ�\��[�V�������Z�b�g����
	virtual void				MotionEventFired( const D_csmString& eventValue ) ;			// �C�x���g�̔��΂��󂯎��
	virtual bool				HitTest( const char* hitAreaName, float x, float y ) ;		//  �����蔻��e�X�g�B
	void						DeleteMark() { _deleteModel = true ; }						// ���f���ɍ폜�}�[�N��t����
	D_CubismOffscreenFrame_DxLib& GetRenderBuffer() ;										// �ʃ^�[�Q�b�g�ɕ`�悷��ۂɎg�p����o�b�t�@�̎擾
	void						SetUserParameter( int parameterIndex, float parameterValue ) ;	// ���[�U�[�ݒ�̃p�����[�^��ݒ肷��

protected:
	void						DoDraw() ;													// ���f����`�悷�鏈���B���f����`�悷���Ԃ�View-Projection�s���n���B

public:
	bool						SetupModel( D_ICubismModelSetting* setting ) ;				// model3.json���烂�f���𐶐�����Bmodel3.json�̋L�q�ɏ]���ă��f�������A���[�V�����A�������Z�Ȃǂ̃R���|�[�l���g�������s���B
	void						SetupTextures( int ASyncThread ) ;							// �e�N�X�`�������[�h����
	void						PreloadMotionGroup( const char* group ) ;					// ���[�V�����f�[�^���O���[�v������ꊇ�Ń��[�h����B���[�V�����f�[�^�̖��O�͓�����ModelSetting����擾����B
	void						ReleaseMotionGroup( const char* group ) const ;				// ���[�V�����f�[�^���O���[�v������ꊇ�ŉ������B���[�V�����f�[�^�̖��O�͓�����ModelSetting����擾����B
	void						ReleaseMotions() ;											// ���ׂẴ��[�V�����f�[�^�̉��
	void						ReleaseExpressions() ;										// ���ׂĂ̕\��f�[�^�̉��

	D_ICubismModelSetting*		_modelSetting ;				// ���f���Z�b�e�B���O���
	D_csmStringW				_modelHomeDir ;				// ���f���Z�b�e�B���O���u���ꂽ�f�B���N�g��
	float						_userTimeSeconds ;			// �f���^���Ԃ̐ώZ�l[�b]
	D_csmVector<D_CubismIdHandle> _eyeBlinkIds ;			// ���f���ɐݒ肳�ꂽ�܂΂��������p�p�����[�^ID
	D_csmVector<D_CubismIdHandle> _lipSyncIds ;				// ���f���ɐݒ肳�ꂽ���b�v�V���N�����p�p�����[�^ID
	D_csmMap<D_csmStringW, D_ACubismMotion*> _motions ;		// �ǂݍ��܂�Ă��郂�[�V�����̃��X�g
	D_csmMap<D_csmStringW, D_ACubismMotion*> _expressions ;	// �ǂݍ��܂�Ă���\��̃��X�g
	D_csmVector<D_csmRectF>		_hitArea ;
	D_csmVector<D_csmRectF>		_userArea ;
	D_CubismId*					_idParamAngleX ;			// �p�����[�^ID: ParamAngleX
	D_CubismId*					_idParamAngleY ;			// �p�����[�^ID: ParamAngleX
	D_CubismId*					_idParamAngleZ ;			// �p�����[�^ID: ParamAngleX
	D_CubismId*					_idParamBodyAngleX ;		// �p�����[�^ID: ParamBodyAngleX
	D_CubismId*					_idParamEyeBallX ;			// �p�����[�^ID: ParamEyeBallX
	D_CubismId*					_idParamEyeBallY ;			// �p�����[�^ID: ParamEyeBallXY
	D_csmVector<int>			_bindTextureId ;			// �e�N�X�`��ID 
	D_csmVector<D_LAppModelParameter>	_userParameters ;	// ���[�U�[�ݒ�̃p�����[�^
	bool						_deleteModel ;				// ���̏��ŗ\��t���O Draw���Ă΂Ȃ� 
	D_CubismOffscreenFrame_DxLib _renderBuffer ;			// �t���[���o�b�t�@�ȊO�̕`��� 
} ;

// �e�[�u��-----------------------------------------------------------------------

extern int Live2D_VertexShaderToDxLibShader_Table[ 7 ] ;
extern int Live2D_PixelShaderToDxLibShader_Table[ 7 ] ;

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern D_CubismIdManager *	new_D_CubismIdManager( void ) ;
extern void					delete_D_CubismIdManager( D_CubismIdManager *obj ) ;
extern D_LAppModel *		new_D_LAppModel( void ) ;
extern void					delete_D_LAppModel( D_LAppModel *obj ) ;
extern D_CubismMatrix44 *	new_D_CubismMatrix44( void ) ;
extern void					delete_D_CubismMatrix44( D_CubismMatrix44 *obj ) ;

#endif // DX_NON_LIVE2D_CUBISM4

#endif // DX_USECLIB_LIVE2DCUBISM4_H
