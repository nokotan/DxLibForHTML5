// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�W���b���C�u�����g�p�R�[�h�@Live2D Cubism4 �֌W
// 
// 				Ver 3.24b
// 
// -------------------------------------------------------------------------------

/*

	DxUseCLibLive2DCubism4.cpp �� Live2D Cubism 4 SDK for Native �� Cubism Native Framework �y��
	Cubism Native Samples ���x�[�X�ƂȂ��Ă��āALive2D Open Software License ���K�p����܂��B
�@�@�@- Live2D Open Software License 
�@�@�@[���{��](http://www.live2d.com/eula/live2d-open-software-license-agreement_jp.html)
�@�@�@[English](http://www.live2d.com/eula/live2d-open-software-license-agreement_en.html)

*/

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"

#ifndef DX_NON_LIVE2D_CUBISM4
#include "DxUseCLibLive2DCubism4.h"
#include "DxLive2DCubism4.h"
#include "DxMemory.h"
#include "DxBaseFunc.h"
#include "DxFile.h"
#include "DxLog.h"
#include <float.h>
#include <math.h>
#include <new>

// operator new �֘A ----------------------------------------------------------

#define D_CSM_NEW                          new(GlobalTag)
#define D_CSM_PLACEMENT_NEW(addrs)         new((addrs))
#define D_CSM_DELETE_SELF(type, obj)       do { if (!obj){ break; } obj->~type(); operator delete(obj, GlobalTag); } while(0)
#define D_CSM_DELETE(obj)                  D_CsmDelete(obj)

class D_CubismAllocationTag
{ };

class D_CubismAllocationAlignedTag
{ };

static D_CubismAllocationTag GlobalTag;
//static D_CubismAllocationAlignedTag GloabalAlignedTag;

void* operator new ( size_t size, D_CubismAllocationTag tag ) ;
void* operator new ( size_t size, unsigned int alignment, D_CubismAllocationAlignedTag tag ) ;
void  operator delete( void* address, D_CubismAllocationTag tag ) ;
void  operator delete( void* address, D_CubismAllocationAlignedTag tag ) ;

void* operator new( size_t size, D_CubismAllocationTag /*tag*/ )
{
	return DXALLOC( size ) ;
}

void* operator new ( size_t size, unsigned int alignment, D_CubismAllocationAlignedTag /*tag*/ )
{
	return DXALLOCBASE( size, alignment );
}

void operator delete( void* address, D_CubismAllocationTag /*tag*/ )
{
	DXFREE( address );
}

void operator delete( void* address, D_CubismAllocationAlignedTag /*tag*/ )
{
	DXFREE( address );
}

template<typename T>
void D_CsmDelete(T* address)
{
    if (!address)
    {
        return;
    }

    address->~T();

    operator delete((void*)(address), GlobalTag);
}

// �}�N����`------------------------------------------------------------------

// �\���̌^�錾 ------------------------------------------------------------------

// �f�[�^�錾------------------------------------------------------------------

const int VertexOffset = 0;
const int VertexStep = 2;

const D_CubismMotionQueueEntryHandle InvalidMotionQueueEntryHandleValue = ( D_CubismMotionQueueEntryHandle * )( -1 ) ;

int Live2D_VertexShaderToDxLibShader_Table[ 7 ] =
{
	DX_LIVE2D_SHADER_SETUP_MASK_VERTEX,		// D_ShaderNames_SetupMask								= 0,
	DX_LIVE2D_SHADER_NORMAL_VERTEX,			// D_ShaderNames_Normal									= 1,
	DX_LIVE2D_SHADER_NORMAL_VERTEX_MASKED,	// D_ShaderNames_NormalMasked							= 2,
	DX_LIVE2D_SHADER_NORMAL_VERTEX_MASKED,	// D_ShaderNames_NormalMaskedInverted					= 3,
	DX_LIVE2D_SHADER_NORMAL_VERTEX,			// D_ShaderNames_NormalPremultipliedAlpha				= 4,
	DX_LIVE2D_SHADER_NORMAL_VERTEX_MASKED,	// D_ShaderNames_NormalMaskedPremultipliedAlpha			= 5,
	DX_LIVE2D_SHADER_NORMAL_VERTEX_MASKED,	// D_ShaderNames_NormalMaskedInvertedPremultipliedAlpha	= 6,
} ;

int Live2D_PixelShaderToDxLibShader_Table[ 7 ] =
{
	DX_LIVE2D_SHADER_SETUP_MASK_PIXEL,							// D_ShaderNames_SetupMask								= 0,
	DX_LIVE2D_SHADER_NORMAL_PIXEL,								// D_ShaderNames_Normal									= 1,
	DX_LIVE2D_SHADER_NORMAL_PIXEL_MASKED,						// D_ShaderNames_NormalMasked							= 2,
	DX_LIVE2D_SHADER_NORMAL_PIXEL_MASKED_INVERTED,				// D_ShaderNames_NormalMaskedInverted					= 3,
	DX_LIVE2D_SHADER_NORMAL_PIXEL_PREMULALPHA,					// D_ShaderNames_NormalPremultipliedAlpha				= 4,
	DX_LIVE2D_SHADER_NORMAL_PIXEL_MASKED_PREMULALPHA,			// D_ShaderNames_NormalMaskedPremultipliedAlpha			= 5,
	DX_LIVE2D_SHADER_NORMAL_PIXEL_MASKED_INVERTEX_PREMULALPHA,	// D_ShaderNames_NormalMaskedInvertedPremultipliedAlpha	= 6,
} ;

// �֐��v���g�^�C�v�錾 ----------------------------------------------------------

// �v���O���� --------------------------------------------------------------------

D_CubismIdManager *new_D_CubismIdManager( void )
{
	return D_CSM_NEW D_CubismIdManager() ;
}

void delete_D_CubismIdManager( D_CubismIdManager *obj )
{
	D_CSM_DELETE( obj ) ;
}

D_LAppModel *new_D_LAppModel( void )
{
	return D_CSM_NEW D_LAppModel() ;
}

void delete_D_LAppModel( D_LAppModel *obj )
{
	D_CSM_DELETE( obj ) ;
}

D_CubismMatrix44 *new_D_CubismMatrix44( void )
{
	return D_CSM_NEW D_CubismMatrix44() ;
}

void delete_D_CubismMatrix44( D_CubismMatrix44 *obj )
{
	D_CSM_DELETE( obj ) ;
}



template< class T >
D_csmVector< T >::D_csmVector()
    : _ptr(NULL)
    , _size(0)
    , _capacity(0)
{ }

template< class T >
D_csmVector< T >::D_csmVector( int initialCapacity, bool zeroClear )
{
	if( initialCapacity < 1 )
	{
		_ptr = NULL ;
		_capacity = 0 ;
		_size = 0 ;
	}
	else
	{
		_ptr = ( T * )DXALLOC( sizeof( T ) * initialCapacity ) ;
		if( zeroClear )
		{
			_MEMSET( _ptr, 0, sizeof( T ) * initialCapacity ) ;
		}
		_capacity = initialCapacity ;
		_size = 0 ;
	}
}

template< class T >
D_csmVector< T >::~D_csmVector()
{
    Clear() ;
}

template< class T >
void D_csmVector< T >::PushBack( const T& value, bool callPlacementNew )
{
	if( _size >= _capacity )
	{
		PrepareCapacity( _capacity == 0 ? 10 : _capacity * 2 ) ;
	}

	// placement new �w��̃A�h���X�ɁA���̂𐶐�����
	if( callPlacementNew )
	{
		D_CSM_PLACEMENT_NEW( &_ptr[ _size++ ] ) T( value ) ;
	}
	else
	{
		_ptr[ _size++ ] = value ;
	}
}

template< class T >
void D_csmVector< T >::PrepareCapacity( int newSize )
{
	if( newSize > _capacity )
	{
		if( _capacity == 0 )
		{
			_ptr = ( T * )DXALLOC( sizeof( T ) * newSize ) ;
			_capacity = newSize ;
		}
		else
		{
			int tmp_capacity = newSize ;
			T* tmp = ( T * )DXALLOC( sizeof( T ) * tmp_capacity ) ;
			_MEMCPY( ( void * )tmp, ( void * )_ptr, sizeof( T ) * _capacity ) ; // �ʏ��MALLOC�ɂȂ������߃R�s�[����
			DXFREE( _ptr ) ;

			_ptr = tmp ;
			_capacity = newSize ;
		}
	}
}

template< class T >
bool D_csmVector< T >::Remove( int index )
{
	if( index < 0 || _size <= index ) return false ; // �폜�͈͊O
	_ptr[ index ].~T() ;

	// �폜(���������V�t�g����)�A�Ō�̈���폜����ꍇ��move�s�v
	if( index < _size - 1 )
	{
		_MEMMOVE( &( _ptr[ index ] ), &( _ptr[ index + 1 ] ), sizeof( T ) * ( _size - index - 1 ) ) ;
	}
	-- _size ;

	return true ;
}

template< class T >
void D_csmVector< T >::Clear()
{
	for( int i = 0; i < _size; i++ )
	{
		_ptr[ i ].~T() ;
	}

	DXFREE( _ptr ) ;

	_ptr = NULL ;
	_size = 0 ;
	_capacity = 0 ;
}

template< class T >
void D_csmVector< T >::UpdateSize( int newSize, T value, bool callPlacementNew )
{
	int cur_size = _size ;
	if( cur_size < newSize )
	{
		PrepareCapacity( newSize ) ; // capacity�X�V

		if( callPlacementNew )
		{
			for( int i = _size; i < newSize; i++ )
			{
				// placement new �w��̃A�h���X�ɁA���̂𐶐�����
				D_CSM_PLACEMENT_NEW( &_ptr[ i ] ) T( value ) ;
			}
		}
		else
		{
			for( int i = _size; i < newSize; i++ )
			{
				_ptr[ i ] = value ;
			}
		}
	}
	else
	{
		for( int i = newSize; i < _size; i++ )
		{
			_ptr[ i ].~T() ; // �s�v�Ȃ̂Ŕj������
		}
	}
	this->_size = newSize ;
}

template< class T >
void D_csmVector< T >::Assign( int newSize, T value, bool callPlacementNew )
{
	int cur_size = _size ;

	// �S�ăf�X�g���N�g
	for( int i = 0; i < _size; i++ )
	{
		_ptr[ i ].~T() ;
	}

	//
	if( cur_size < newSize )
	{
		PrepareCapacity( newSize ); // capacity�X�V
	}

	if( callPlacementNew )
	{
		for( int i = 0; i < newSize; i++ )
		{
			D_CSM_PLACEMENT_NEW( &_ptr[ i ] ) T( value ) ; // placement new �w��̃A�h���X�ɁA���̂𐶐�����
		}
	}
	else
	{
		for( int i = 0; i < newSize; i++ )
		{
			_ptr[ i ] = value ;
		}
	}

	_size = newSize ;
}

template< class T >
void D_csmVector< T >::Insert( iterator position, iterator begin, iterator end, bool callPlacementNew )
{
	int dst_si = position._index ;
	int src_si = begin._index ;
	int src_ei = end._index ;

	int addcount = src_ei - src_si ;

	PrepareCapacity( _size + addcount ) ;

	// �}���p�Ɋ����f�[�^���V�t�g���Č��Ԃ����
	if( _size - dst_si > 0 )
	{
		_MEMMOVE( &( _ptr[ dst_si + addcount ] ), &( _ptr[ dst_si ] ), sizeof( T ) * ( _size - dst_si ) ) ;
	}

	// placement new �w��̃A�h���X�ɁA���̂𐶐�����
	if( callPlacementNew )
	{
		for( int i = src_si; i < src_ei; i++, dst_si++ )
		{
			D_CSM_PLACEMENT_NEW( &_ptr[ i ] ) T( begin._vector->_ptr[ i ] ) ;
		}
	}
	else
	{
		for( int i = src_si; i < src_ei; i++, dst_si++ )
		{
			_ptr[ dst_si ] = begin._vector->_ptr[ i ] ;
		}
	}

	_size = _size + addcount ;
}

template< class T >
void D_csmVector< T >::Copy( const D_csmVector& c )
{
	_size = c._size ;
	_capacity = c._capacity ;
	_ptr = ( T* )DXALLOC( _capacity * sizeof( T ) ) ;
	for( int i = 0; i < _size ; ++i )
	{
		D_CSM_PLACEMENT_NEW( &_ptr[ i ] ) T( c._ptr[ i ] ) ;
	}
}





















template< class _KeyT, class _ValT >
D_csmMap< _KeyT, _ValT >::D_csmMap()
	: _keyValues( NULL )
	, _dummyValuePtr( NULL )
	, _size( 0 )
	, _capacity( 0 )
{ }

template< class _KeyT, class _ValT >
D_csmMap< _KeyT, _ValT >::D_csmMap( int size )
	: _dummyValuePtr( NULL )
{
	if( size < 1 )
	{
		_keyValues = NULL ;
		_capacity = 0 ;
		_size = 0 ;
	}
	else
	{
		_keyValues = ( D_csmPair< _KeyT, _ValT > * )DXALLOC( size * sizeof( D_csmPair< _KeyT, _ValT > ) ) ;

		// �������� calloc �ɂ��A�m�ۂ����o�C�g��0�Ŗ��߂�
		_MEMSET( _keyValues, 0, size * sizeof( D_csmPair< _KeyT, _ValT > ) ) ;

		_capacity = size ;
		_size = size ;
	}
}

template< class _KeyT, class _ValT >
D_csmMap< _KeyT, _ValT >::~D_csmMap()
{
	Clear();
}

template< class _KeyT, class _ValT >
void D_csmMap< _KeyT, _ValT >::PrepareCapacity( int newSize, bool fitToSize )
{
	if( newSize > _capacity )
	{
		if( _capacity == 0 )
		{
			if( !fitToSize && newSize < CSM_MAP_DEFAULT_SIZE ) newSize = CSM_MAP_DEFAULT_SIZE;

			_keyValues = ( D_csmPair< _KeyT, _ValT > * )DXALLOC( sizeof( D_csmPair< _KeyT, _ValT > ) * newSize ) ;

			_capacity = newSize ;
		}
		else
		{
			if( !fitToSize && newSize < _capacity * 2 ) newSize = _capacity * 2; // �w��T�C�Y�ɍ��킹��K�v���Ȃ��ꍇ�́A�Q�{�ɍL����

			int tmp_capacity = newSize ;
			D_csmPair< _KeyT, _ValT >* tmp = ( D_csmPair< _KeyT, _ValT > * )DXALLOC( sizeof( D_csmPair< _KeyT, _ValT > ) * tmp_capacity ) ;

			// �ʏ��MALLOC�ɂȂ������߃R�s�[����
			_MEMCPY( ( void* )tmp, ( void* )_keyValues, sizeof( D_csmPair< _KeyT, _ValT > ) * _capacity ) ;
			DXFREE( _keyValues ) ;

			_keyValues = tmp ; // ���̂܂�
			_capacity = newSize ;
		}
	}
}

template< class _KeyT, class _ValT >
void D_csmMap< _KeyT, _ValT >::Clear()
{
	if( _dummyValuePtr ) D_CSM_DELETE( _dummyValuePtr ) ;
	for( int i = 0; i < _size; i++ )
	{
		_keyValues[ i ].~D_csmPair< _KeyT, _ValT >() ;
	}

	DXFREE( _keyValues ) ;

	_keyValues = NULL ;

	_size = 0 ;
	_capacity = 0 ;
}

template< class _KeyT, class _ValT >
void D_csmMap< _KeyT, _ValT >::AppendKey( _KeyT& key )
{
	// �V����Key/D_JsonValue�̃y�A�����
	PrepareCapacity( _size + 1, false ); //�P�ȏ���錄�Ԃ����
	// �V����key/value�̃C���f�b�N�X�� _size

	void* addr = &_keyValues[ _size ];
	D_CSM_PLACEMENT_NEW( addr ) D_csmPair<_KeyT, _ValT>( key ); //placement new

	_size += 1;
}

template< class _KeyT, class _ValT >
_ValT& D_csmMap< _KeyT, _ValT >::operator[]( _KeyT key )
{
	int found = -1;
	for( int i = 0; i < _size; i++ )
	{
		if( _keyValues[ i ].First == key )
		{
			found = i;
			break;
		}
	}
	if( found >= 0 )
	{
		return _keyValues[ found ].Second;
	}
	else
	{
		AppendKey( key ); // �V�K�L�[��ǉ�
		return _keyValues[ _size - 1 ].Second;
	}
}

template< class _KeyT, class _ValT >
const _ValT& D_csmMap< _KeyT, _ValT >::operator[]( _KeyT key ) const
{
	int found = -1;
	for( int i = 0; i < _size; i++ )
	{
		if( _keyValues[ i ].First == key )
		{
			found = i;
			break;
		}
	}
	if( found >= 0 )
	{
		return _keyValues[ found ].Second;
	}
	else
	{
		if( !_dummyValuePtr ) _dummyValuePtr = D_CSM_NEW _ValT();
		return *_dummyValuePtr;
	}
}

template< class _KeyT, class _ValT >
bool D_csmMap< _KeyT, _ValT >::IsExist( _KeyT key )
{
	for( int i = 0; i < _size; i++ )
	{
		if( _keyValues[ i ].First == key )
		{
			return true;
		}
	}
	return false;
}




















D_csmRectF::D_csmRectF()
{ }

D_csmRectF::D_csmRectF(float x, float y, float w, float h)
    : X(x)
    , Y(y)
    , Width(w)
    , Height(h)
{ }

D_csmRectF::~D_csmRectF()
{ }

void D_csmRectF::SetRect(D_csmRectF* r)
{
    X = r->X;
    Y = r->Y;
    Width = r->Width;
    Height = r->Height;
}

void D_csmRectF::Expand(float w, float h)
{
    X -= w;
    Y -= h;
    Width += w * 2.0f;
    Height += h * 2.0f;
}
















D_CubismVector2 operator+(const D_CubismVector2& a, const D_CubismVector2& b)
{
    return D_CubismVector2(a.X + b.X, a.Y + b.Y);
}

D_CubismVector2 operator-(const D_CubismVector2& a, const D_CubismVector2& b)
{
    return D_CubismVector2(a.X - b.X, a.Y - b.Y);
}

D_CubismVector2 operator*(const D_CubismVector2& vector, const float scalar)
{
    return D_CubismVector2(vector.X * scalar, vector.Y * scalar);
}

D_CubismVector2 operator*(const float scalar, const D_CubismVector2& vector)
{
    return D_CubismVector2(vector.X * scalar, vector.Y * scalar);
}

D_CubismVector2 operator/(const D_CubismVector2& vector, const float scalar)
{
    return D_CubismVector2(vector.X / scalar, vector.Y / scalar);
}

const D_CubismVector2& D_CubismVector2::operator+=(const D_CubismVector2& rhs)
{
    X += rhs.X;
    Y += rhs.Y;

    return *this;
}

const D_CubismVector2& D_CubismVector2::operator-=(const D_CubismVector2& rhs)
{
    X -= rhs.X;
    Y -= rhs.Y;

    return *this;
}

const D_CubismVector2& D_CubismVector2::operator*=(const D_CubismVector2& rhs)
{
    X *= rhs.X;
    Y *= rhs.Y;

    return *this;
}

const D_CubismVector2& D_CubismVector2::operator/=(const D_CubismVector2& rhs)
{
    X /= rhs.X;
    Y /= rhs.Y;

    return *this;
}

const D_CubismVector2& D_CubismVector2::operator*=(const float scalar)
{
    X *= scalar;
    Y *= scalar;

    return *this;
}

const D_CubismVector2& D_CubismVector2::operator/=(const float scalar)
{
    X /= scalar;
    Y /= scalar;

    return *this;
}

bool D_CubismVector2::operator==(const D_CubismVector2& rhs) const
{
    return (X == rhs.X) && (Y == rhs.Y);
}

bool D_CubismVector2::operator!=(const D_CubismVector2& rhs) const
{
    return !(*this == rhs);
}

float D_CubismVector2::GetLength() const
{
    return D_CubismMath::SqrtF(X * X + Y * Y);
}

float D_CubismVector2::GetDistanceWith(D_CubismVector2 a) const
{
    return D_CubismMath::SqrtF(((X - a.X) * (X - a.X)) + ((Y - a.Y) * (Y - a.Y)));
}

float D_CubismVector2::Dot(const D_CubismVector2& a) const
{
    return (X * a.X) + (Y * a.Y);
}

void D_CubismVector2::Normalize()
{
    const float length = powf((X * X) + (Y * Y), 0.5f);

    X = X / length;
    Y = Y / length;
}
























const float D_CubismMath::Pi = 3.1415926535897932384626433832795f;

float D_CubismMath::RangeF( float value, float min, float max )
{
	if( value < min ) value = min;
	else if( value > max ) value = max;
	return value;
};

float D_CubismMath::GetEasingSine( float value )
{
	if( value < 0.0f ) return 0.0f;
	else if( value > 1.0f ) return 1.0f;
	return ( float )( 0.5f - 0.5f * CosF( value * Pi ) );
}

float D_CubismMath::DegreesToRadian( float degrees )
{
	return ( degrees / 180.0f ) * Pi;
}

float D_CubismMath::RadianToDegrees( float radian )
{
	return ( radian * 180.0f ) / Pi;
}

float D_CubismMath::DirectionToRadian( D_CubismVector2 from, D_CubismVector2 to )
{
	float q1;
	float q2;
	float ret;

	q1 = atan2f( to.Y, to.X );
	q2 = atan2f( from.Y, from.X );

	ret = q1 - q2;

	while( ret < -Pi )
	{
		ret += Pi * 2.0f;
	}

	while( ret > Pi )
	{
		ret -= Pi * 2.0f;
	}

	return ret;
}

float D_CubismMath::DirectionToDegrees( D_CubismVector2 from, D_CubismVector2 to )
{
	float radian;
	float degree;

	radian = DirectionToRadian( from, to );
	degree = RadianToDegrees( radian );

	if( ( to.X - from.X ) > 0.0f )
	{
		degree = -degree;
	}

	return degree;
}

D_CubismVector2 D_CubismMath::RadianToDirection( float totalAngle )
{
	D_CubismVector2 ret;

	ret.X = D_CubismMath::SinF( totalAngle );
	ret.Y = D_CubismMath::CosF( totalAngle );

	return ret;
}













// ������N���X

// �R���X�g���N�^
D_csmString::D_csmString()
    : _ptr( NULL )
    , _length( 0 )
    , _hashcode( -1 )
    , _ptrW( NULL )
    , _lengthW( 0 )
    , _ptrA( NULL )
    , _lengthA( 0 )
{
	_small[ 0 ] = '\0' ;
	_hashcode = CalcHashcode( WritePointer(), _length ) ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;
}

D_csmString::D_csmString( const D_csmString& s )
{
	_enableW = false ;
	_ptrW = NULL ;
	_lengthW = 0 ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;

	_enableA = false ;
	_ptrA = NULL ;
	_lengthA = 0 ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;

	if( !s.IsEmpty() )
	{
		Copy( s.GetRawString(), s._length );
		this->_hashcode = s._hashcode;
	}
	else
	{
		SetEmpty();
	}
}

D_csmString::D_csmString( const BYTE/*wchar_t*/ * c )
{
	int count = ( int )( ConvString( ( const char * )c, -1, WCHAR_T_CHARCODEFORMAT, NULL, 0, DX_CHARCODEFORMAT_UTF8 ) - 1 ) ;

	_enableW = false ;
	_ptrW = NULL ;
	_lengthW = 0 ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;

	_enableA = false ;
	_ptrA = NULL ;
	_lengthA = 0 ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;

	if( count )
	{
		Copy( c, count );
		this->_hashcode = CalcHashcode( WritePointer(), _length );
	}
	else
	{
		SetEmpty();
	}
}

D_csmString::D_csmString( const char* c )
{
	const int count = ( int )CL_strlen( DX_CHARCODEFORMAT_UTF8, c ) ;

	_enableW = false ;
	_ptrW = NULL ;
	_lengthW = 0 ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;

	_enableA = false ;
	_ptrA = NULL ;
	_lengthA = 0 ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;

	if( count )
	{
		Copy( c, count );
		this->_hashcode = CalcHashcode( WritePointer(), _length );
	}
	else
	{
		SetEmpty();
	}
}

D_csmString::D_csmString( const char* s, int length )
{
	_enableW = false ;
	_ptrW = NULL ;
	_lengthW = 0 ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;

	_enableA = false ;
	_ptrA = NULL ;
	_lengthA = 0 ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;

	if( length )
	{
		Copy( s, length );
		this->_hashcode = CalcHashcode( WritePointer(), _length );
	}
	else
	{
		SetEmpty();
	}
}

D_csmString::D_csmString( const char* c, int length, bool useptr )
{
	_enableW = false ;
	_ptrW = NULL ;
	_lengthW = 0 ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;

	_enableA = false ;
	_ptrA = NULL ;
	_lengthA = 0 ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;

	Initialize( c, length, useptr ) ;
}

// �f�X�g���N�^
D_csmString::~D_csmString()
{
	if( IsEmpty() )
	{
		return;
	}

	if( _ptr ) 
	{
		DXFREE( _ptr );
		_ptr = NULL ;
	}

	if( _ptrW ) 
	{
		DXFREE( _ptrW );
		_ptrW = NULL ;
	}

	if( _ptrA ) 
	{
		DXFREE( _ptrA );
		_ptrA = NULL ;
	}
}

D_csmString& D_csmString::operator=( const char* c )
{
	Clear() ; //���݂̃|�C���^���J�����Ă��珈������

	Copy( c, ( int )CL_strlen( DX_CHARCODEFORMAT_UTF8, c ) ) ;
	_hashcode = CalcHashcode( GetRawString(), _length ) ;
	return *this ;
}

bool D_csmString::operator==( const D_csmString& s ) const
{
	//�T�C�Y�Ⴂ
	if( s._length != _length ) return false ;

	//hashcode��r
	if( _hashcode != s._hashcode ) return false ;

	const char* c1 = GetRawString() ;
	const char* c2 = s.GetRawString() ;

	//�����Ⴂ�i�t���Ȃ̂�PARAM�̔�r�̓����j
	for( int i = _length - 1; i >= 0; --i )
	{
		if( c1[ i ] != c2[ i ] ) return false ;
	}
	return true ;
}

bool D_csmString::operator==( const char* rc ) const
{
	//�T�C�Y�Ⴂ
	if( ( int )CL_strlen( DX_CHARCODEFORMAT_UTF8, rc ) != _length ) return false ;

	const char* lc = GetRawString() ;

	//�����Ⴂ�i�t���Ȃ̂�PARAM�̔�r�̓����j
	for( int i = _length - 1; i >= 0; --i )
	{
		if( lc[ i ] != rc[ i ] ) return false ;
	}
	return true ;
}

D_csmString D_csmString::operator+( const D_csmString& s ) const
{
	size_t len1 = ( size_t )this->_length ;
	size_t len2 = ( size_t )s._length ;

	if( !len1 && !len2 )
	{
		D_csmString ret;
		return ret;
	}

	if( len1 + len2 < sizeof( _small ) - 1 )
	{
		char buffer[ sizeof( _small ) ];
		char* newptr = buffer;

		//
		_MEMCPY( newptr, GetRawString(), sizeof( char ) * len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], s.GetRawString(), sizeof( char ) * ( s._length + 1 ) ); //null���܂߂�+1

		D_csmString ret( newptr, ( int )( len1 + len2 ), false );
		return ret;
	}
	else
	{
		//�������Ǘ��̑ΏۊO�Ƃ���i�������c���o���Ȃ��j
		char* newptr = ( char* )DXALLOC( sizeof( char ) * ( len1 + len2 + 1 ) ) ;

		if( newptr == NULL )
		{
			D_csmString ret;
			return ret;
		}

		//
		_MEMCPY( newptr, GetRawString(), sizeof( char ) * len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], s.GetRawString(), sizeof( char ) * ( s._length + 1 ) ); //null���܂߂�+1

		D_csmString ret( newptr, ( int )( len1 + len2 ), true );
		return ret;
	}
}

D_csmString D_csmString::operator+( const char* c ) const
{
	size_t len1 = ( size_t )this->_length ;
	size_t len2 = CL_strlen( DX_CHARCODEFORMAT_UTF8, c );

	if( len1 + len2 < sizeof( _small ) - 1 )
	{
		char buffer[ sizeof( _small ) ];
		char* newptr = buffer;

		//
		_MEMCPY( newptr, this->GetRawString(), sizeof( char ) * len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, sizeof( char ) * ( len2 + 1 ) ); //null���܂߂�+1

		D_csmString ret( newptr, ( int )( len1 + len2 ), false );
		return ret;
	}
	else
	{
		//�������Ǘ��̑ΏۊO�Ƃ���i�������c���o���Ȃ��j
		char* newptr = ( char* )DXALLOC( sizeof( char ) * ( len1 + len2 + 1 ) ) ;

		if( newptr == NULL )
		{
			D_csmString ret;
			return ret;
		}

		_MEMCPY( newptr, this->GetRawString(), sizeof( char ) * len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, sizeof( char ) * ( len2 + 1 ) ); //null���܂߂�+1

		D_csmString ret( newptr, ( int )( len1 + len2 ), true );
		return ret;
	}
}

D_csmString& D_csmString::operator+=( const D_csmString& s )
{
	char* newptr = NULL;
	int len1 = this->_length;

	if( this->_length + s._length < ( int )( sizeof( _small ) - 1 ) )
	{
		char buffer[ sizeof( _small ) ];
		newptr = buffer;

		_MEMCPY( newptr, this->GetRawString(), len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], s.GetRawString(), s._length + 1 ); //null���܂߂�+1

		Clear(); // ���݂̃|�C���^���J�����Ă��珈������
		Initialize( newptr, len1 + s._length, false );
	}
	else
	{
		newptr = ( char* )DXALLOC( sizeof( char ) * ( this->_length + s._length + 1 ) ) ;

		_MEMCPY( newptr, this->GetRawString(), len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], s.GetRawString(), s._length + 1 ); //null���܂߂�+1

		Clear(); //���݂̃|�C���^���J�����Ă��珈������
		Initialize( newptr, len1 + s._length, true );
	}
	return *this;
}

D_csmString& D_csmString::operator+=( const char* c )
{
	size_t len1 = ( size_t )( this->_length );
	size_t len2 = CL_strlen( DX_CHARCODEFORMAT_UTF8, c ) ;

	char* newptr = NULL;

	if( len1 + len2 < sizeof( _small ) - 1 )
	{
		char buffer[ sizeof( _small ) ];
		newptr = buffer;

		_MEMCPY( newptr, GetRawString(), len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, len2 + 1 ); //null���܂߂�+1

		Clear(); //���݂̃|�C���^���J�����Ă��珈������
		Initialize( newptr, ( int )( len1 + len2 ), false );
	}
	else
	{
		newptr = ( char* )DXALLOC( sizeof( char ) * ( len1 + len2 + 1 ) ) ;

		_MEMCPY( newptr, this->_ptr, len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, len2 + 1 ); //null���܂߂�+1

		Clear(); //���݂̃|�C���^���J�����Ă��珈������
		Initialize( newptr, ( int )( len1 + len2 ), true );
	}
	return *this;
}

// �|�C���^���������
void D_csmString::Clear()
{
	if( IsEmpty() )
	{
		return ;
	}

	if( _ptr != NULL )
	{
		DXFREE( _ptr ) ;
		_ptr = NULL ;
	}

	_enableW = false ;
	if( _ptrW != NULL )
	{
		DXFREE( _ptrW ) ;
		_ptrW = NULL ;
	}
	_lengthW = 0 ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;

	_enableA = false ;
	if( _ptrA != NULL )
	{
		DXFREE( _ptrA ) ;
		_ptrA = NULL ;
	}
	_lengthA = 0 ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;

	SetEmpty() ;
}

// D_csmString�C���X�^���X�̏������֐��B������̃Z�b�g�ƃn�b�V���R�[�h�̎Z�o���s���B
void D_csmString::Initialize( const char* c, int length, bool usePtr )
{
	_enableW = false ;
	if( _ptrW != NULL )
	{
		DXFREE( _ptrW ) ;
		_ptrW = NULL ;
	}
	_lengthW = 0 ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;

	_enableA = false ;
	if( _ptrA != NULL )
	{
		DXFREE( _ptrA ) ;
		_ptrA = NULL ;
	}
	_lengthA = 0 ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;

	if( !length )
	{
		SetEmpty() ;

		return ;
	}

	if( !usePtr )
	{
		Copy( c, length ) ;
	}
	else
	{
		_ptr = ( char * )c ;
		_length = length ;
		_ptr[ length ] = 0x0 ;
	}

	_hashcode = CalcHashcode( GetRawString(), _length ) ;
}

int D_csmString::Copy( const BYTE* c, int length )
{
	if( !length )
	{
		return 0 ;
	}

	this->_length = length;

	if( this->_length < ( int )( sizeof( _small ) -1 ) )
	{
		this->_ptr = NULL;

		ConvString( ( const char * )c, -1, WCHAR_T_CHARCODEFORMAT, ( char * )this->_small, sizeof( this->_small ), DX_CHARCODEFORMAT_UTF8  ) ;
	}
	else
	{
		this->_ptr = ( char* )DXALLOC( sizeof( char ) * ( length + 1 ) ) ;
		if( _ptr == NULL )
		{
			return -1 ;
		}

		ConvString( ( const char * )c, -1, WCHAR_T_CHARCODEFORMAT, ( char * )this->_ptr, sizeof( char ) * ( length + 1 ), DX_CHARCODEFORMAT_UTF8 ) ;
	}

	_enableW = false ;
	if( _ptrW != NULL )
	{
		DXFREE( _ptrW ) ;
		_ptrW = NULL ;
	}
	_lengthW = 0 ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;

	_enableA = false ;
	if( _ptrA != NULL )
	{
		DXFREE( _ptrA ) ;
		_ptrA = NULL ;
	}
	_lengthA = 0 ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;

	return 0 ;
}

// ��������R�s�[����. �I�[��\0��ǉ�����
int D_csmString::Copy( const char* c, int length )
{
	if( !length )
	{
		return 0 ;
	}

	_length = length ;

	if( _length < ( int )( sizeof( _small ) - 1 ) )
	{
		_ptr = NULL ;

		_MEMCPY( _small, c, length ) ;
		_small[ length ] = 0x0 ;
	}
	else
	{
		_ptr = ( char * )DXALLOC( sizeof( char ) * ( length + 1 ) ) ;
		if( _ptr == NULL )
		{
			return -1 ;
		}

		_MEMCPY( _ptr, c, length ) ;
		_ptr[ length ] = 0x0 ;
	}

	_enableW = false ;
	if( _ptrW != NULL )
	{
		DXFREE( _ptrW ) ;
		_ptrW = NULL ;
	}
	_lengthW = 0 ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;

	_enableA = false ;
	if( _ptrA != NULL )
	{
		DXFREE( _ptrA ) ;
		_ptrA = NULL ;
	}
	_lengthA = 0 ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;

	return 0 ;
}

// �����񂩂�n�b�V���l�𐶐����ĕԂ�
int D_csmString::CalcHashcode( const char* c, int length )
{
	int hash = 0;
	int i ;
	for( i = length ; i >= 0 ; --i )
	{
		hash = hash * 31 + c[ i ] ;
	}
	if( hash == -1 )
	{
		hash = -2 ; // -1�������ʂȈӖ�����������
	}
	return hash ;
}

// �����񂪋󂩂ǂ����H
bool D_csmString::IsEmpty() const
{
    return _ptr == NULL && _small[ 0 ] == '\0' ;
}

// ���������ɐݒ�
void D_csmString::SetEmpty( void )
{
	_ptr = NULL ;
	_small[ 0 ] = '\0' ;
	_length = 0 ;
	_hashcode = -1 ;
	_hashcode = CalcHashcode( WritePointer(), _length ) ;

	_enableW = false ;
	_ptrW = NULL ;
	( ( wchar_t * )_smallW )[ 0 ] = L'\0' ;
	_lengthW = 0 ;

	_enableA = false ;
	_ptrA = NULL ;
	_smallA[ 0 ] = '\0' ;
	_smallA[ 1 ] = '\0' ;
	_smallA[ 2 ] = '\0' ;
	_smallA[ 3 ] = '\0' ;
	_lengthA = 0 ;
}


D_csmString& D_csmString::Append( const char* c, int len2 )
{
	int len1 = this->_length;

	char* newptr = NULL;

	if( len1 + len2 < ( int )( sizeof( _small ) - 1 ) )
	{
		char buffer[ sizeof( _small ) ];
		newptr = buffer;

		_MEMCPY( newptr, this->GetRawString(), len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, len2 ); //null���܂߂�+1

		Clear(); // ���݂̃|�C���^���J�����Ă��珈������
		Initialize( newptr, len1 + len2, false );
	}
	else
	{
		newptr = ( char* )DXALLOC( sizeof( char ) * ( len1 + len2 + 1 ) ) ;

		_MEMCPY( newptr, this->GetRawString(), len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, len2 ); //null���܂߂�+1

		Clear(); //���݂̃|�C���^���J�����Ă��珈������
		Initialize( newptr, len1 + len2, true );
	}
	return *this;
}

D_csmString& D_csmString::Append( int len2, const char c )
{
	int len1 = this->_length;

	char* newptr = NULL;

	if( len1 + len2< ( int )( sizeof( _small ) -1 ) )
	{
		char buffer[ sizeof( _small ) ];
		newptr = buffer;
		_MEMCPY( newptr, this->GetRawString(), len1 ); //null���܂߂Ȃ�
		for( int i = len1 + len2 - 1; i >= len1; --i ) newptr[ i ] = c;

		Clear(); // ���݂̃|�C���^���J�����Ă��珈������
		Initialize( newptr, len1 + len2, false );
	}
	else
	{
		// �K�v�Ȓ���?NULL��1�o�C�g��V�K�m�� 
		newptr = ( char* )DXALLOC( sizeof( char ) * ( len1 + len2 + 1 ) ) ;
		// ���X�̕����R�s�[ 
		_MEMCPY( newptr, this->GetRawString(), len1 ); //null���܂߂Ȃ�
		// �V�����ӏ����R�s�[ 
		for( int i = len1 + len2 - 1; i >= len1; --i ) newptr[ i ] = c;

		Clear(); //���݂̃|�C���^���J�����Ă��珈������
		Initialize( newptr, len1 + len2, true );
	}
	return *this;
}

// C���ꕶ����Ƃ��Ẵ|�C���^���擾����
const char *D_csmString::GetRawString( void ) const 
{
	if( _length < ( int )( sizeof( _small ) - 1 ) )
	{
		return &_small[ 0 ] ;
	}
	else
	{
		return _ptr ;
	}
}

// C���ꕶ����Ƃ��Ẵ|�C���^���擾����( �c�w���C�u�����̖߂�l�p )
const char *D_csmString::GetRawStringA( void )
{
	if( _enableA == false )
	{
		this->_lengthA = ( int )( ConvString( ( const char * )GetRawString(), -1, DX_CHARCODEFORMAT_UTF8, NULL, 0, CHAR_CHARCODEFORMAT ) - 1 ) ;
		if( _lengthA < ( int )( sizeof( _smallA ) / sizeof( char ) - 1 ) )
		{
			this->_ptrA = NULL ;
			ConvString( GetRawString(), -1, DX_CHARCODEFORMAT_UTF8, this->_smallA, sizeof( this->_smallA ),  CHAR_CHARCODEFORMAT ) ;
		}
		else
		{
			this->_ptrA = ( char * )DXALLOC( sizeof( char ) * ( this->_lengthA + 1 ) ) ;
			ConvString( GetRawString(), -1, DX_CHARCODEFORMAT_UTF8, this->_ptrA, sizeof( char ) * ( this->_lengthA + 1 ), CHAR_CHARCODEFORMAT ) ;
		}

		_enableA = true ;
	}
	
	if( _lengthA < ( int )( sizeof( _smallA ) / sizeof( char ) - 1 ) )
	{
		return _smallA ;
	}
	else
	{
		return _ptrA ;
	}
}

// C���ꕶ����Ƃ��Ẵ|�C���^���擾����( wchar_t�p )
const BYTE *D_csmString::GetRawStringW( void )
{
	if( _enableW == false )
	{
		this->_lengthW = ( int )( ConvString( ( const char * )GetRawString(), -1, DX_CHARCODEFORMAT_UTF8, NULL, 0, WCHAR_T_CHARCODEFORMAT ) - 1 ) ;
		if( _lengthW < ( int )( sizeof( _smallW ) / sizeof( wchar_t ) - 1 ) )
		{
			this->_ptrW = NULL ;
			ConvString( ( const char * )GetRawString(), -1, DX_CHARCODEFORMAT_UTF8, ( char * )this->_smallW, sizeof( this->_smallW ),  WCHAR_T_CHARCODEFORMAT ) ;
		}
		else
		{
			this->_ptrW = ( BYTE * )DXALLOC( sizeof( wchar_t ) * ( this->_lengthW + 1 ) ) ;
			ConvString( ( const char * )GetRawString(), -1, DX_CHARCODEFORMAT_UTF8, ( char * )this->_ptrW, sizeof( wchar_t ) * ( this->_lengthW + 1 ), WCHAR_T_CHARCODEFORMAT ) ;
		}

		_enableW = true ;
	}
	
	if( _lengthW < ( int )( sizeof( _smallW ) / sizeof( wchar_t ) - 1 ) )
	{
		return ( BYTE * )&_smallW[ 0 ] ;
	}
	else
	{
		return _ptrW ;
	}
}

// C���ꕶ����Ƃ��Ẵ|�C���^���擾����
char *D_csmString::WritePointer( void )
{
	if( _length < ( int )( sizeof( _small ) - 1 ) )
	{
		return _small ;
	}
	else
	{
		return _ptr ;
	}
}











int D_csmStringW::s_totalInstanceNo = 0;

const wchar_t* s_emptyStringW = L"";

BYTE* GetEmptyStringW()
{
	return ( BYTE* )( s_emptyStringW );
}

D_csmStringW::D_csmStringW()
	: _ptr( NULL )
	, _length( 0 )
	, _hashcode( -1 )
{
	( ( wchar_t * )_small )[ 0 ] = '\0';
	_hashcode = CalcHashcode( WritePointer(), this->_length );
	_instanceNo = s_totalInstanceNo++;
}

D_csmStringW::D_csmStringW( const char* c )
{
	int count = ( int )( ConvString( c, -1, DX_CHARCODEFORMAT_UTF8, NULL, 0, WCHAR_T_CHARCODEFORMAT ) / sizeof( wchar_t ) - 1 ) ;

	if( count )
	{
		Copy( c, count );
		this->_hashcode = CalcHashcode( WritePointer(), _length );
	}
	else
	{
		SetEmpty();
	}

	_instanceNo = s_totalInstanceNo++;
}

D_csmStringW::D_csmStringW( const BYTE* c )
{
	int count = ( int )( CL_strlen( WCHAR_T_CHARCODEFORMAT, ( const char * )c ) );

	if( count )
	{
		Copy( c, count );
		this->_hashcode = CalcHashcode( WritePointer(), _length );
	}
	else
	{
		SetEmpty();
	}

	_instanceNo = s_totalInstanceNo++;
}

D_csmStringW::D_csmStringW( const D_csmStringW& s )
{
	if( !s.IsEmpty() )
	{
		Copy( s.GetRawString(), s._length );
		this->_hashcode = s._hashcode;
	}
	else
	{
		SetEmpty();
	}

	_instanceNo = s_totalInstanceNo++;
}

D_csmStringW::D_csmStringW( const BYTE* s, int length )
{
	if( length )
	{
		Copy( s, length );
		this->_hashcode = CalcHashcode( WritePointer(), _length );
	}
	else
	{
		SetEmpty();
	}

	_instanceNo = s_totalInstanceNo++;
}

D_csmStringW::D_csmStringW( const BYTE* c, int length, bool useptr )
{
	Initialize( c, length, useptr );
	_instanceNo = s_totalInstanceNo++;
}

void D_csmStringW::Initialize( const BYTE* c, int length, bool usePtr )
{
	if( !length )
	{
		SetEmpty();

		return;
	}

	if( !usePtr )
	{
		Copy( c, length );
	}
	else
	{
		this->_ptr = ( BYTE * )c ;
		this->_length = length;
		( ( wchar_t * )this->_ptr )[ length ] = 0x0;
	}

	this->_hashcode = CalcHashcode( this->GetRawString(), this->_length );
}

D_csmStringW::~D_csmStringW()
{
	if( IsEmpty() )
	{
		return;
	}

	if( this->_ptr )
	{
		DXFREE( this->_ptr );
	}
}

void D_csmStringW::Clear()
{
	if( IsEmpty() )
	{
		return;
	}

	DXFREE( this->_ptr );

	SetEmpty();
}

D_csmStringW& D_csmStringW::operator=( const BYTE* c )
{
	Clear(); //���݂̃|�C���^���J�����Ă��珈������

	Copy( c, ( int )CL_strlen( WCHAR_T_CHARCODEFORMAT, ( const char * )c ) );
	this->_hashcode = CalcHashcode( this->GetRawString(), this->_length );
	return *this;
}

D_csmStringW& D_csmStringW::operator=( const D_csmStringW& s )
{
	Clear(); //���݂̃|�C���^���J�����Ă��珈������

	Copy( s.GetRawString(), s._length );
	this->_hashcode = s._hashcode;
	return *this;
}

D_csmStringW D_csmStringW::operator+( const D_csmStringW& s ) const
{
	size_t len1 = ( size_t )this->_length ;
	size_t len2 = ( size_t )s._length ;

	if( !len1 && !len2 )
	{
		D_csmStringW ret;
		return ret;
	}

	if( len1 + len2 < CSM_STRING_SMALL_LENGTH - 1 )
	{
		wchar_t buffer[ CSM_STRING_SMALL_LENGTH ];
		wchar_t* newptr = buffer;

		//
		_MEMCPY( newptr, GetRawString(), sizeof( wchar_t ) * len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], s.GetRawString(), sizeof( wchar_t ) * ( s._length + 1 ) ); //null���܂߂�+1

		D_csmStringW ret( ( BYTE * )newptr, ( int )( len1 + len2 ), false );
		return ret;
	}
	else
	{
		//�������Ǘ��̑ΏۊO�Ƃ���i�������c���o���Ȃ��j
		wchar_t* newptr = ( wchar_t* )DXALLOC( sizeof( wchar_t ) * ( len1 + len2 + 1 ) ) ;

		if( newptr == NULL )
		{
			D_csmStringW ret;
			return ret;
		}

		//
		_MEMCPY( newptr, GetRawString(), sizeof( wchar_t ) * len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], s.GetRawString(), sizeof( wchar_t ) * ( s._length + 1 ) ); //null���܂߂�+1

		D_csmStringW ret( ( BYTE * )newptr, ( int )( len1 + len2 ), true );
		return ret;
	}
}

D_csmStringW D_csmStringW::operator+( const BYTE* c ) const
{
	size_t len1 = ( size_t )this->_length ;
	size_t len2 = CL_strlen( WCHAR_T_CHARCODEFORMAT, ( const char * )c );

	if( len1 + len2 < CSM_STRING_SMALL_LENGTH - 1 )
	{
		wchar_t buffer[ CSM_STRING_SMALL_LENGTH ];
		wchar_t* newptr = buffer;

		//
		_MEMCPY( newptr, this->GetRawString(), sizeof( wchar_t ) * len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, sizeof( wchar_t ) * ( len2 + 1 ) ); //null���܂߂�+1

		D_csmStringW ret( ( BYTE * )newptr, ( int )( len1 + len2 ), false );
		return ret;
	}
	else
	{
		//�������Ǘ��̑ΏۊO�Ƃ���i�������c���o���Ȃ��j
		wchar_t* newptr = ( wchar_t* )DXALLOC( sizeof( wchar_t ) * ( len1 + len2 + 1 ) ) ;

		if( newptr == NULL )
		{
			D_csmStringW ret;
			return ret;
		}

		_MEMCPY( newptr, this->GetRawString(), sizeof( wchar_t ) * len1 ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, sizeof( wchar_t ) * ( len2 + 1 ) ); //null���܂߂�+1

		D_csmStringW ret( ( BYTE * )newptr, ( int )( len1 + len2 ), true );
		return ret;
	}
}

D_csmStringW& D_csmStringW::operator+=( const D_csmStringW& s )
{
	wchar_t* newptr = NULL;
	int len1 = this->_length;

	if( this->_length + s._length < CSM_STRING_SMALL_LENGTH - 1 )
	{
		wchar_t buffer[ CSM_STRING_SMALL_LENGTH ];
		newptr = buffer;

		_MEMCPY( newptr, this->GetRawString(), len1 * sizeof( wchar_t ) ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], s.GetRawString(), ( s._length + 1 ) * sizeof( wchar_t ) ); //null���܂߂�+1

		Clear(); // ���݂̃|�C���^���J�����Ă��珈������
		Initialize( ( BYTE * )newptr, len1 + s._length, false );
	}
	else
	{
		newptr = ( wchar_t* )DXALLOC( sizeof( wchar_t ) * ( this->_length + s._length + 1 ) ) ;

		_MEMCPY( newptr, this->GetRawString(), len1 * sizeof( wchar_t ) ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], s.GetRawString(), ( s._length + 1 ) * sizeof( wchar_t ) ); //null���܂߂�+1

		Clear(); //���݂̃|�C���^���J�����Ă��珈������
		Initialize( ( BYTE * )newptr, len1 + s._length, true );
	}
	return *this;
}

D_csmStringW& D_csmStringW::operator+=( const BYTE* c )
{
	size_t len1 = ( size_t )this->_length ;
	size_t len2 = CL_strlen( WCHAR_T_CHARCODEFORMAT, ( const char * )c );

	wchar_t* newptr = NULL;

	if( len1 + len2 < CSM_STRING_SMALL_LENGTH - 1 )
	{
		wchar_t buffer[ CSM_STRING_SMALL_LENGTH ];
		newptr = buffer;

		_MEMCPY( newptr, GetRawString(), len1 * sizeof( wchar_t ) ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, ( len2 + 1 ) * sizeof( wchar_t ) ); //null���܂߂�+1

		Clear(); //���݂̃|�C���^���J�����Ă��珈������
		Initialize( ( BYTE * )newptr, ( int )( len1 + len2 ), false );
	}
	else
	{
		newptr = ( wchar_t* )DXALLOC( sizeof( wchar_t ) * ( len1 + len2 + 1 ) ) ;

		_MEMCPY( newptr, this->_ptr, len1 * sizeof( wchar_t ) ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, ( len2 + 1 ) * sizeof( wchar_t ) ); //null���܂߂�+1

		Clear(); //���݂̃|�C���^���J�����Ă��珈������
		Initialize( ( BYTE * )newptr, ( int )( len1 + len2 ), true );
	}
	return *this;
}

bool D_csmStringW::operator==(const D_csmStringW& s) const
{
    //�T�C�Y�Ⴂ
    if (s._length != this->_length) return false;

    //hashcode��r
    if (this->_hashcode != s._hashcode) return false;

    const wchar_t* c1 = ( wchar_t * )this->GetRawString();
    const wchar_t* c2 = ( wchar_t * )s.GetRawString();

    //�����Ⴂ�i�t���Ȃ̂�PARAM�̔�r�̓����j
    for (int i = this->_length - 1; i >= 0; --i)
    {
        if (c1[i] != c2[i]) return false;
    }
    return true;
}

bool D_csmStringW::operator==( const BYTE* rc ) const
{
	//�T�C�Y�Ⴂ
	if( ( int )CL_strlen( WCHAR_T_CHARCODEFORMAT, ( const char * )rc ) != this->_length ) return false;

	const wchar_t* lc = ( wchar_t * )this->GetRawString();

	//�����Ⴂ�i�t���Ȃ̂�PARAM�̔�r�̓����j
	for( int i = this->_length - 1; i >= 0; --i )
	{
		if( lc[ i ] != rc[ i ] ) return false;
	}
	return true;
}

bool D_csmStringW::operator<( const D_csmStringW& s ) const
{
	return CL_strcmp( WCHAR_T_CHARCODEFORMAT, ( const char * )this->GetRawString(), ( const char * )s.GetRawString() ) < 0;
}

bool D_csmStringW::operator<( const BYTE* c ) const
{
	return CL_strcmp( WCHAR_T_CHARCODEFORMAT, ( const char * )this->GetRawString(), ( const char * )c ) < 0;
}

bool D_csmStringW::operator>( const D_csmStringW& s ) const
{
	return CL_strcmp( WCHAR_T_CHARCODEFORMAT, ( const char * )this->GetRawString(), ( const char * )s.GetRawString() ) > 0;
}

bool D_csmStringW::operator>( const BYTE* c ) const
{
	return CL_strcmp( WCHAR_T_CHARCODEFORMAT, ( const char * )this->GetRawString(), ( const char * )c ) > 0;
}

D_csmStringW& D_csmStringW::Append( const BYTE* c, int len2 )
{
	int len1 = this->_length;

	wchar_t* newptr = NULL;

	if( len1 + len2 < CSM_STRING_SMALL_LENGTH - 1 )
	{
		wchar_t buffer[ CSM_STRING_SMALL_LENGTH ];
		newptr = buffer;

		_MEMCPY( newptr, this->GetRawString(), len1* sizeof( wchar_t ) ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, len2* sizeof( wchar_t ) ); //null���܂߂�+1

		Clear(); // ���݂̃|�C���^���J�����Ă��珈������
		Initialize( ( BYTE * )newptr, len1 + len2, false );
	}
	else
	{
		newptr = ( wchar_t* )DXALLOC( sizeof( wchar_t ) * ( len1 + len2 + 1 ) ) ;

		_MEMCPY( newptr, this->GetRawString(), len1* sizeof( wchar_t ) ); //null���܂߂Ȃ�
		_MEMCPY( &newptr[ len1 ], c, len2* sizeof( wchar_t ) ); //null���܂߂�+1

		Clear(); //���݂̃|�C���^���J�����Ă��珈������
		Initialize( ( BYTE * )newptr, len1 + len2, true );
	}
	return *this;
}

D_csmStringW& D_csmStringW::Append( int len2, const DWORD c )
{
	int len1 = this->_length;

	wchar_t* newptr = NULL;

	if( len1 + len2< CSM_STRING_SMALL_LENGTH -1 )
	{
		wchar_t buffer[ CSM_STRING_SMALL_LENGTH ];
		newptr = buffer;
		_MEMCPY( newptr, this->GetRawString(), len1* sizeof( wchar_t ) ); //null���܂߂Ȃ�
		for( int i = len1 + len2 - 1; i >= len1; --i ) newptr[ i ] = ( wchar_t )c;

		Clear(); // ���݂̃|�C���^���J�����Ă��珈������
		Initialize( ( BYTE * )newptr, len1 + len2, false );
	}
	else
	{
		// �K�v�Ȓ���?NULL��1�o�C�g��V�K�m�� 
		newptr = ( wchar_t* )DXALLOC( sizeof( wchar_t ) * ( len1 + len2 + 1 ) ) ;
		// ���X�̕����R�s�[ 
		_MEMCPY( newptr, this->GetRawString(), len1* sizeof( wchar_t ) ); //null���܂߂Ȃ�
		// �V�����ӏ����R�s�[ 
		for( int i = len1 + len2 - 1; i >= len1; --i ) newptr[ i ] = ( wchar_t )c;

		Clear(); //���݂̃|�C���^���J�����Ă��珈������
		Initialize( ( BYTE * )newptr, len1 + len2, true );
	}
	return *this;
}

void D_csmStringW::Copy( const BYTE* c, int length )
{
	if( !length )
	{
		return;
	}

	this->_length = length;

	if( this->_length < CSM_STRING_SMALL_LENGTH -1 )
	{
		this->_ptr = NULL;

		_MEMCPY( this->_small, c, length * sizeof( wchar_t ) );
		( ( wchar_t * )_small )[ length ] = 0x0;
	}
	else
	{
		this->_ptr = ( BYTE* )DXALLOC( sizeof( wchar_t ) * ( length + 1 ) ) ;

		_MEMCPY( this->_ptr, c, length* sizeof( wchar_t ) );
		( ( wchar_t * )this->_ptr )[ length ] = 0x0;
	}
}

void D_csmStringW::Copy( const char* c, int length )
{
	if( !length )
	{
		return;
	}

	this->_length = length;

	if( this->_length < CSM_STRING_SMALL_LENGTH -1 )
	{
		this->_ptr = NULL;
		ConvString( c, -1, DX_CHARCODEFORMAT_UTF8, ( char * )this->_small, sizeof( this->_small ), WCHAR_T_CHARCODEFORMAT ) ;
	}
	else
	{
		this->_ptr = ( BYTE* )DXALLOC( sizeof( wchar_t ) * ( length + 1 ) ) ;
		ConvString( c, -1, DX_CHARCODEFORMAT_UTF8, ( char * )this->_ptr, sizeof( wchar_t ) * ( length + 1 ), WCHAR_T_CHARCODEFORMAT ) ;
	}
}

int D_csmStringW::CalcHashcode( const BYTE* c, int length )
{
	int hash = 0;
	for( int i = length; i >= 0; --i )
	{
		hash = hash * 31 + ( ( wchar_t * )c )[ i ];
	}
	if( ( hash == -1 ) || ( c == ( BYTE * )GetEmptyStringW() ) )
	{
		hash = -2; //-1�������ʂȈӖ�����������
	}
	return hash;
}

const BYTE* D_csmStringW::GetRawString() const
{
	if( this->_length < CSM_STRING_SMALL_LENGTH -1 )
	{
		return ( BYTE * )&_small[ 0 ];
	}
	else
	{
		return _ptr;
	}
}

int D_csmStringW::GetHashcode()
{
    if (_hashcode == -1) _hashcode = CalcHashcode(WritePointer(), this->_length);
    return _hashcode;
}

bool D_csmStringW::IsEmpty() const
{
#ifdef CSM_DEBUG

    bool isEmpty = (_ptr == NULL && ( ( wchar_t * )_small )[0]=='\0');

    if (isEmpty)
    {
        CSM_ASSERT(_length == 0);
    }

    return isEmpty;

#else

    //return (_ptr == GetEmptyString());

    return (_ptr == NULL && ( ( wchar_t * )_small )[0] == '\0');

#endif
}

void D_csmStringW::SetEmpty()
{
    //_ptr = GetEmptyString();
    _ptr = NULL;
    ( ( wchar_t * )_small )[0] = '\0';
    _length = 0;
    _hashcode = -1;
    _hashcode = CalcHashcode(WritePointer(), this->_length);
}

BYTE* D_csmStringW::WritePointer()
{
    if(this->_length< CSM_STRING_SMALL_LENGTH -1)
    {
        return ( BYTE * )_small;
    }
    else
    {
        return _ptr;
    }
}














D_CubismIdManager::D_CubismIdManager()
{
	// �N���e�B�J���Z�N�V�����̏�����
	CriticalSection_Initialize( &_criticalSection ) ;

	_MEMSET( _ids, 0, sizeof( _ids ) ) ;
	_idNum = 0 ;
}

D_CubismIdManager::~D_CubismIdManager()
{
	// �N���e�B�J���Z�N�V�����̍폜
	CriticalSection_Delete( &_criticalSection ) ;

	for( int i = 0; i < _idNum; ++i )
	{
		D_CSM_DELETE_SELF( D_CubismId, _ids[ i ] );
	}
	_idNum = 0 ;
}

void D_CubismIdManager::RegisterIds( const char** ids, int count )
{
	for( int i = 0; i < count; ++i )
	{
		RegisterId( ids[ i ] );
	}
}

void D_CubismIdManager::RegisterIds( const D_csmVector< D_csmString >& ids )
{
	for( unsigned int i = 0; i < ids.GetSize(); ++i )
	{
		RegisterId( ids[ i ] );
	}
}

D_CubismId* D_CubismIdManager::GetId( const D_csmString& id )
{
	return RegisterId( id.GetRawString() );
}

D_CubismId* D_CubismIdManager::GetId( const char* id )
{
	return RegisterId( id );
}

bool D_CubismIdManager::IsExist( const D_csmString& id ) const
{
	return IsExist( id.GetRawString() );
}

bool D_CubismIdManager::IsExist( const char* id ) const
{
	return ( FindId( id ) != NULL );
}

D_CubismId* D_CubismIdManager::RegisterId( const char* id )
{
	D_CubismId* result = NULL;

	if( ( result = FindId( id ) ) != NULL )
	{
		return result;
	}

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &_criticalSection ) ;

	if( _idNum >= CSM_IDMANAGER_MAX_ID_NUM )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &_criticalSection ) ;

		return NULL ;
	}

	result = D_CSM_NEW D_CubismId( id );
	_ids[ _idNum ] = result;
	_idNum ++ ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &_criticalSection ) ;

	return result;
}

D_CubismId* D_CubismIdManager::RegisterId( const D_csmString& id )
{
	return RegisterId( id.GetRawString() ) ;
}

D_CubismId* D_CubismIdManager::FindId( const char* id ) const
{
	int idNumTemp = _idNum ;
	for( int i = 0; i < idNumTemp; ++i )
	{
		if( _ids[ i ]->GetString() == id )
		{
			return _ids[ i ];
		}
	}

	return NULL;
}


















//StaticInitializeNotForClientCall()�ŏ���������
D_JsonBoolean* D_JsonBoolean::TrueValue = NULL;
D_JsonBoolean* D_JsonBoolean::FalseValue = NULL;
D_JsonValue* D_JsonValue::ErrorValue = NULL;
D_JsonValue* D_JsonValue::NullValue = NULL;
D_csmVector<D_csmString>* D_JsonValue::s_dummyKeys = NULL;

const char* D_JsonValue::GetRawString( const D_csmString& defaultValue, const D_csmString& indent )
{
	return this->GetString( defaultValue, indent ).GetRawString();
}

const char* D_JsonValue::GetRawStringA( const D_csmString& defaultValue, const D_csmString& indent )
{
	return this->GetString( defaultValue, indent ).GetRawStringA();
}

const BYTE* D_JsonValue::GetRawStringW( const D_csmString& defaultValue, const D_csmString& indent )
{
	return this->GetString( defaultValue, indent ).GetRawStringW();
}

D_JsonValue& D_JsonValue::operator[]( int /*index*/ )										// �Y�����Z�q[int]
{
	return *( ErrorValue->SetErrorNotForClientCall( D_CSM_JSON_ERROR_TYPE_MISMATCH ) );
}
D_JsonValue& D_JsonValue::operator[]( const D_csmString& /*string*/ )						// �Y�����Z�q[D_csmString]
{
	return *( NullValue->SetErrorNotForClientCall( D_CSM_JSON_ERROR_TYPE_MISMATCH ) );
}
D_JsonValue& D_JsonValue::operator[]( const char* /*s*/ )									// �Y�����Z�q[char*]
{
	return *( NullValue->SetErrorNotForClientCall( D_CSM_JSON_ERROR_TYPE_MISMATCH ) );
}

void D_JsonValue::StaticReleaseNotForClientCall()
{
	D_CSM_DELETE( D_JsonBoolean::TrueValue );
	D_JsonBoolean::TrueValue = NULL;

	D_CSM_DELETE( D_JsonBoolean::FalseValue );
	D_JsonBoolean::FalseValue = NULL;

	D_CSM_DELETE( D_JsonError::ErrorValue );
	D_JsonError::ErrorValue = NULL;

	D_CSM_DELETE( D_JsonValue::NullValue );
	D_JsonValue::NullValue = NULL;

	D_CSM_DELETE( D_JsonValue::s_dummyKeys );
	D_JsonValue::s_dummyKeys = NULL;
}

void D_JsonValue::StaticInitializeNotForClientCall()
{
	D_JsonBoolean::TrueValue = D_CSM_NEW D_JsonBoolean( true );
	D_JsonBoolean::FalseValue = D_CSM_NEW D_JsonBoolean( false );

	D_JsonError::ErrorValue = D_CSM_NEW D_JsonError( "ERROR", true );
	NullValue = D_CSM_NEW D_JsonNullValue();

	D_JsonValue::s_dummyKeys = D_CSM_NEW D_csmVector<D_csmString>();
}

D_CubismJson::D_CubismJson()
	: _error( NULL )
	, _lineCount( 0 )
	, _root( NULL )
{ }

D_CubismJson::D_CubismJson( const BYTE* buffer, int length )
	: _error( NULL )
	, _lineCount( 0 )
	, _root( NULL )
{
	ParseBytes( buffer, length );
}

D_CubismJson::~D_CubismJson()
{
	if( _root && !_root->IsStatic() )
	{
		D_CSM_DELETE( _root );
	}

	_root = NULL;
}

void D_CubismJson::Delete( D_CubismJson* instance )
{
	D_CSM_DELETE_SELF( D_CubismJson, instance );
}


D_CubismJson* D_CubismJson::Create( const BYTE* buffer, size_t size )
{
	D_CubismJson* json = D_CSM_NEW D_CubismJson();
	const bool succeeded = json->ParseBytes( buffer, ( int )size );

	if( !succeeded )
	{
		D_CubismJson::Delete( json );
		return NULL;
	}
	else
	{
		return json;
	}
}

D_JsonValue& D_CubismJson::GetRoot() const
{
	return *_root;
}

bool D_CubismJson::ParseBytes( const BYTE* buffer, int size )
{
	int endPos;
	_root = ParseValue( ( const char* )( buffer ), size, 0, &endPos );

//	if( _error )
//	{
//#if defined(CSM_TARGET_WIN_GL) || defined(_MSC_VER)
//		char strbuf[ 256 ] = { '\0' };
//		_snprintf_s( strbuf, 256, 256, "Json parse error : @line %d\n", ( _lineCount + 1 ) );
//		_root = D_CSM_NEW D_JsonString( strbuf );
//#else
//		char strbuf[ 256 ] = { '\0' };
//		snprintf( strbuf, 256, "Json parse error : @line %d\n", ( _lineCount + 1 ) );
//		_root = D_CSM_NEW D_JsonString( strbuf );
//#endif
//		CubismLogInfo( "%s", _root->GetRawString() );
//		return false;
//	}
//	else if( _root == NULL )
//	{
//		_root = D_CSM_NEW D_JsonError( _error, false ); //root�͊J�������̂ŃG���[�I�u�W�F�N�g��ʓr���
//		return false;
//	}
	return true;
}

D_csmString D_CubismJson::ParseString( const char* string, int length, int begin, int* outEndPos )
{
	if( _error ) return ( const char * )NULL;
	int i = begin;
	char c, c2;
	D_csmString ret;
	int buf_start = begin; //sbuf�ɓo�^����Ă��Ȃ������̊J�n�ʒu

	for( ; i < length; i++ )
	{
		c = ( char )( string[ i ] & 0xFF );

		switch( c )
		{
		case '\"': {//�I�[�́h, �G�X�P�[�v�����͕ʂɏ��������̂ł����ɂ͂��Ȃ�
			*outEndPos = i + 1; // �h�̎��̕���
			ret.Append( ( const char* )( string + buf_start ), ( i - buf_start ) );
			return ret;
		}
		case '\\': {//�G�X�P�[�v�̏ꍇ
			i++; //�Q�������Z�b�g�ň���

			if( i - 1 > buf_start ) ret.Append( ( const char* )( string + buf_start ), ( i - buf_start - 1 ) ); //�O�̕����܂ł�o�^����
			buf_start = i + 1; //�G�X�P�[�v�i�Q�����j�̎��̕�������

			if( i < length )
			{
				c2 = ( char )( string[ i ] & 0xFF );
				switch( c2 )
				{
				case '\\': ret.Append( 1, '\\' );
					break;
				case '\"': ret.Append( 1, '\"' );
					break;
				case '/': ret.Append( 1, '/' );
					break;

				case 'b': ret.Append( 1, '\b' );
					break;
				case 'f': ret.Append( 1, '\f' );
					break;
				case 'n': ret.Append( 1, '\n' );
					break;
				case 'r': ret.Append( 1, '\r' );
					break;
				case 't': ret.Append( 1, '\t' );
					break;
				case 'u':
					_error = "parse string/unicode escape not supported";
				default:
					break;
				}
			}
			else
			{
				_error = "parse string/escape error";
			}
			break;
		}
		default: {
			break;
		}
		}
	}
	_error = "parse string/illegal end";
	return ( const char * )NULL;
}

D_JsonValue* D_CubismJson::ParseObject( const char* buffer, int length, int begin, int* outEndPos )
{
	if( _error ) return NULL;
	D_JsonMap* ret = D_CSM_NEW D_JsonMap();

	//key : value ,
	D_csmString key;
	int i = begin;
	char c;
	int local_ret_endpos2[ 1 ];
	bool ok = false;

	// , ���������胋�[�v
	for( ; i < length; i++ )
	{
		for( ; i < length; i++ )
		{
			c = ( char )( buffer[ i ] & 0xFF );

			switch( c )
			{
			case '\"':
				key = ParseString( buffer, length, i + 1, local_ret_endpos2 );
				if( _error ) return NULL;
				i = local_ret_endpos2[ 0 ];
				ok = true;
				goto BREAK_LOOP1; //-- loop����o��
			case '}': //���J�b�R
				*outEndPos = i + 1;
				return ret; //��
			case ':':
				_error = "illegal ':' position";
				break;
			case '\n': _lineCount++;
			default: break; //�X�L�b�v���镶��
			}
		}
	BREAK_LOOP1:
		if( !ok )
		{
			_error = "key not found";
			return NULL;
		}

		ok = false;

		// : ���`�F�b�N
		for( ; i < length; i++ )
		{
			c = ( char )( buffer[ i ] & 0xFF );

			switch( c )
			{
			case ':': ok = true;
				i++;
				goto BREAK_LOOP2; //-- loop����o��

			case '}':
				_error = "illegal '}' position";
				break;
			case '\n': _lineCount++;
				//case ' ': case '\t': case '\r':
			default: break; //�X�L�b�v���镶��
			}
		}
	BREAK_LOOP2:

		if( !ok )
		{
			_error = "':' not found";
			return NULL;
		}

		// �l���`�F�b�N
		D_JsonValue* value = ParseValue( buffer, length, i, local_ret_endpos2 );
		if( _error ) return NULL;
		i = local_ret_endpos2[ 0 ];
		// ret.put( key , value ) ;
		ret->Put( key, value );

		for( ; i < length; i++ )
		{
			c = ( char )( buffer[ i ] & 0xFF );

			switch( c )
			{
			case ',':
				goto BREAK_LOOP3;
			case '}':
				*outEndPos = i + 1;
				return ret; // << [] ����I�� >>
			case '\n': _lineCount++;
				//case ' ': case '\t': case '\r':
			default: break; //�X�L�b�v
			}
		}
	BREAK_LOOP3:
		; //dummy
	}

	_error = "illegal end of parseObject";
	return NULL;
}

D_JsonValue* D_CubismJson::ParseArray( const char* buffer, int length, int begin, int* outEndPos )
{
	if( _error ) return NULL;
	D_JsonArray* ret = D_CSM_NEW D_JsonArray();

	//key : value ,
	int i = begin;
	char c;
	int local_ret_endpos2[ 1 ];

	// , ���������胋�[�v
	for( ; i < length; i++ )
	{
		// : ���`�F�b�N
		D_JsonValue* value = ParseValue( buffer, length, i, local_ret_endpos2 );
		if( _error ) return NULL;
		i = local_ret_endpos2[ 0 ];
		if( value )
		{
			ret->Add( value );
		}

		//FOR_LOOP3:
		//bool breakflag = false;
		for( ; i < length; i++ )
		{
			c = ( char )( buffer[ i ] & 0xFF );

			switch( c )
			{
			case ',':
				// breakflag = true;
				// break;//����KEY,VALUE��
				goto BREAK_LOOP3;
			case ']':
				*outEndPos = i + 1;
				return ret; //�I��
			case '\n': ++_lineCount;
				//case ' ': case '\t': case '\r':
			default: break; //�X�L�b�v
			}
		}
	BREAK_LOOP3:
		; //dummy
	}

	D_CSM_DELETE( ret );
	_error = "illegal end of parseObject";
	return NULL;
}

D_JsonValue* D_CubismJson::ParseValue( const char* buffer, int length, int begin, int* outEndPos )
{
	if( _error ) return NULL;

	D_JsonValue* o = NULL;
	int i = begin;
	float f;
	D_csmString s1; //�f�o�b�O�p�Ɏg���Ă���

	for( ; i < length; i++ )
	{
		char c = ( char )( buffer[ i ] & 0xFF );

		switch( c )
		{
		case '-': case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9': 
		{
			const char* ret_ptr;
			ret_ptr = buffer + i + 1;
			for( ;; ret_ptr++ )
			{
				if( *ret_ptr != '.' && *ret_ptr != 'e' && *ret_ptr != '-' &&
					*ret_ptr != '0' && *ret_ptr != '1' && *ret_ptr != '2' && *ret_ptr != '3' && *ret_ptr != '4' &&
					*ret_ptr != '5' && *ret_ptr != '6' && *ret_ptr != '7' && *ret_ptr != '8' && *ret_ptr != '9' )
				{
					break ;
				}
			}
			D_csmString floatStr( buffer + i, ( int )( ret_ptr - ( buffer + i ) ) ) ;
			f = ( float )CL_atof( DX_CHARCODEFORMAT_UTF8, floatStr.GetRawString() );
			*outEndPos = ( int )( ret_ptr - buffer );
			return D_CSM_NEW D_JsonFloat( f );
		}
		case '\"':
			return D_CSM_NEW D_JsonString( ParseString( buffer, length, i + 1, outEndPos ) ); //\"�̎��̕�������
		case '[':
			o = ParseArray( buffer, length, i + 1, outEndPos );
			return o;
		case '{':
			o = ParseObject( buffer, length, i + 1, outEndPos );
			return o;
		case 'n': //null�ȊO�ɂȂ�
			if( i + 3 < length )
			{
				o = D_CSM_NEW D_JsonNullValue(); //�J���ł���悤�ɂ���
				*outEndPos = i + 4;
			}
			else _error = "parse null";
			return o;
		case 't': //true�ȊO�ɂȂ�
			if( i + 3 < length )
			{
				o = D_JsonBoolean::TrueValue;
				*outEndPos = i + 4;
			}
			else _error = "parse true";
			return o;
		case 'f': //false�ȊO�ɂȂ�
			if( i + 4 < length )
			{
				o = D_JsonBoolean::FalseValue;
				*outEndPos = i + 5;
			}
			else _error = "parse false";
			return o;
		case ',': //D_JsonArray separator
			_error = "illegal ',' position";
			return NULL;
		case ']': //�s����}�����X�L�b�v����B�z��̍Ō�ɕs�v�� , ������Ǝv����
			*outEndPos = i; //�����������ď���
			return NULL;
		case '\n': _lineCount++;
		case ' ': case '\t': case '\r':
		default: //�X�L�b�v
			break;
		}
	}

	_error = "illegal end of value";
	return NULL;
}

D_csmString& D_JsonFloat::GetString( const D_csmString& /*defaultValue*/, const D_csmString& /*indent*/ )
{
	char strbuf[ 32 ] = { '\0' };
	CL_snprintf( DX_CHARCODEFORMAT_UTF8, FALSE, DX_CHARCODEFORMAT_UTF8, DX_CHARCODEFORMAT_UTF16LE, strbuf, 32, "%f", this->_value );
	_stringBuffer = D_csmString( strbuf );
	return _stringBuffer;
}

D_csmString& D_JsonBoolean::GetString( const D_csmString& /*defaultValue*/, const D_csmString& /*indent*/ )
{
	_stringBuffer = D_csmString( _boolValue ? "true" : "false" );
	return _stringBuffer;
}

D_csmString& D_JsonString::GetString( const D_csmString& /*defaultValue*/, const D_csmString& /*indent*/ )
{
	return _stringBuffer;
}

D_JsonMap::~D_JsonMap()
{
	D_csmMap<D_csmString, D_JsonValue*>::const_iterator ite = _map.Begin();
	while( ite != _map.End() )
	{
		D_JsonValue* v = ( *ite ).Second;
		if( v && !v->IsStatic() ) D_CSM_DELETE( v );
		++ite;
	}

	if( _keys ) D_CSM_DELETE( _keys );
}

D_JsonValue& D_JsonMap::operator[]( const D_csmString& s )
{
	D_JsonValue* ret = _map[ s ];
	if( ret == NULL )
	{
		return *D_JsonValue::NullValue;
	}
	return *ret;
}

D_JsonValue& D_JsonMap::operator[]( const char* s )
{
	for( D_csmMap<D_csmString, D_JsonValue*>::const_iterator iter = _map.Begin(); iter != _map.End(); ++iter )
	{
		if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, iter->First.GetRawString(), s ) == 0 )
		{
			if( iter->Second==NULL )
			{
				return *D_JsonValue::NullValue;
			}
			return *iter->Second;
		}
	}

	return *D_JsonValue::NullValue;
}

D_JsonValue& D_JsonMap::operator[]( int /*index*/ )
{
	return *( ErrorValue->SetErrorNotForClientCall( D_CSM_JSON_ERROR_TYPE_MISMATCH ) );
}

D_csmString& D_JsonMap::GetString( const D_csmString& /*defaultValue*/, const D_csmString& indent )
{
	_stringBuffer = indent + "{\n";
	D_csmMap<D_csmString, D_JsonValue*>::const_iterator ite = _map.Begin();
	while( ite != _map.End() )
	{
		const D_csmString& key = ( *ite ).First;
		D_JsonValue* v = ( *ite ).Second;

		_stringBuffer += indent + "	" + key + " : " + v->GetString( indent + "	" ) + "\n";
		++ite;
	}
	_stringBuffer += indent + "}\n";
	return _stringBuffer;
}

D_csmMap<D_csmString, D_JsonValue*>* D_JsonMap::GetMap( D_csmMap<D_csmString, D_JsonValue*>* /*defaultValue*/ )
{
	return &_map;
}

void D_JsonMap::Put( D_csmString& key, D_JsonValue* v )
{
	_map[ key ] = v;
}

D_csmVector<D_csmString>& D_JsonMap::GetKeys()
{
	if( !_keys )
	{
		_keys = D_CSM_NEW D_csmVector<D_csmString>();
		D_csmMap<D_csmString, D_JsonValue*>::const_iterator ite = _map.Begin();
		while( ite != _map.End() )
		{
			const D_csmString& key = ( *ite ).First;
			_keys->PushBack( key, true );
			++ite;
		}
	}
	return *_keys;
}

D_JsonArray::~D_JsonArray()
{
	D_csmVector<D_JsonValue*>::iterator ite = _array.Begin();
	for( ; ite != _array.End(); ++ite )
	{
		D_JsonValue* v = ( *ite );
		if( v && !v->IsStatic() ) D_CSM_DELETE( v );
	}
}

D_JsonValue& D_JsonArray::operator[]( int index )
{
	if( index < 0 || ( ( int )_array.GetSize() <= index ) )
		return *( ErrorValue->SetErrorNotForClientCall( D_CSM_JSON_ERROR_INDEX_OUT_OF_BOUNDS ) );
	D_JsonValue* v = _array[ index ];

	if( v == NULL ) return *D_JsonValue::NullValue;
	return *v;
}

D_JsonValue& D_JsonArray::operator[]( const D_csmString& /*string*/ )
{
	return *( ErrorValue->SetErrorNotForClientCall( D_CSM_JSON_ERROR_TYPE_MISMATCH ) );
}

D_JsonValue& D_JsonArray::operator[]( const char* /*s*/ )
{
	return *( ErrorValue->SetErrorNotForClientCall( D_CSM_JSON_ERROR_TYPE_MISMATCH ) );
}

D_csmString& D_JsonArray::GetString( const D_csmString& /*defaultValue*/, const D_csmString& indent )
{
	_stringBuffer = indent + "[\n";
	D_csmVector<D_JsonValue*>::iterator ite = _array.Begin();
	for( ; ite != _array.End(); ite++ )
	{
		D_JsonValue* v = ( *ite );
		_stringBuffer += indent + "	" + v->GetString( indent + "	" ) + "\n";
	}
	_stringBuffer += indent + "]\n";

	return _stringBuffer;
}
















// JSON keys
const char* D_CubismMotionJson::Meta = "Meta";
const char* D_CubismMotionJson::Duration = "Duration";
const char* D_CubismMotionJson::Loop = "Loop";
const char* D_CubismMotionJson::CurveCount = "CurveCount";
const char* D_CubismMotionJson::Fps = "Fps";
const char* D_CubismMotionJson::TotalSegmentCount = "TotalSegmentCount";
const char* D_CubismMotionJson::TotalPointCount = "TotalPointCount";
const char* D_CubismMotionJson::Curves = "Curves";
const char* D_CubismMotionJson::Target = "Target";
const char* D_CubismMotionJson::Id = "Id";
const char* D_CubismMotionJson::FadeInTime = "FadeInTime";
const char* D_CubismMotionJson::FadeOutTime = "FadeOutTime";
const char* D_CubismMotionJson::Segments = "Segments";
const char* D_CubismMotionJson::UserData = "UserData";
const char* D_CubismMotionJson::UserDataCount = "UserDataCount";
const char* D_CubismMotionJson::TotalUserDataSize = "TotalUserDataSize";
const char* D_CubismMotionJson::Time = "Time";
const char* D_CubismMotionJson::Value = "Value";

D_CubismMotionJson::D_CubismMotionJson( const BYTE* buffer, size_t size )
{
	_json = D_CubismJson::Create( buffer, size );
}

D_CubismMotionJson::~D_CubismMotionJson()
{
	D_CubismJson::Delete( _json );
}

float D_CubismMotionJson::GetMotionDuration() const
{
	return _json->GetRoot()[ Meta ][ Duration ].ToFloat();
}

bool D_CubismMotionJson::IsMotionLoop() const
{
	return _json->GetRoot()[ Meta ][ Loop ].ToBoolean();
}

int D_CubismMotionJson::GetMotionCurveCount() const
{
	return _json->GetRoot()[ Meta ][ CurveCount ].ToInt();
}

float D_CubismMotionJson::GetMotionFps() const
{
	return _json->GetRoot()[ Meta ][ Fps ].ToFloat();
}

int D_CubismMotionJson::GetMotionTotalSegmentCount() const
{
	return _json->GetRoot()[ Meta ][ TotalSegmentCount ].ToInt();
}

int D_CubismMotionJson::GetMotionTotalPointCount() const
{
	return _json->GetRoot()[ Meta ][ TotalPointCount ].ToInt();
}

bool D_CubismMotionJson::IsExistMotionFadeInTime() const
{
	return !_json->GetRoot()[ Meta ][ FadeInTime ].IsNull();
}

bool D_CubismMotionJson::IsExistMotionFadeOutTime() const
{
	return !_json->GetRoot()[ Meta ][ FadeOutTime ].IsNull();
}

float D_CubismMotionJson::GetMotionFadeInTime() const
{
	return _json->GetRoot()[ Meta ][ FadeInTime ].ToFloat();
}

float D_CubismMotionJson::GetMotionFadeOutTime() const
{
	return _json->GetRoot()[ Meta ][ FadeOutTime ].ToFloat();
}

const char* D_CubismMotionJson::GetMotionCurveTarget( int curveIndex ) const
{
	return _json->GetRoot()[ Curves ][ curveIndex ][ Target ].GetRawString();
}

D_CubismIdHandle D_CubismMotionJson::GetMotionCurveId( int curveIndex )
{
	return LIVE2DSYS.s_cubismIdManager->GetId( _json->GetRoot()[ Curves ][ curveIndex ][ Id ].GetRawString() );
}

bool D_CubismMotionJson::IsExistMotionCurveFadeInTime( int curveIndex ) const
{
	return !_json->GetRoot()[ Curves ][ curveIndex ][ FadeInTime ].IsNull();
}

bool D_CubismMotionJson::IsExistMotionCurveFadeOutTime( int curveIndex ) const
{
	return !_json->GetRoot()[ Curves ][ curveIndex ][ FadeOutTime ].IsNull();
}

float D_CubismMotionJson::GetMotionCurveFadeInTime( int curveIndex ) const
{
	return _json->GetRoot()[ Curves ][ curveIndex ][ FadeInTime ].ToFloat();
}

float D_CubismMotionJson::GetMotionCurveFadeOutTime( int curveIndex ) const
{
	return _json->GetRoot()[ Curves ][ curveIndex ][ FadeOutTime ].ToFloat();
}

int D_CubismMotionJson::GetMotionCurveSegmentCount( int curveIndex ) const
{
	return ( int )( _json->GetRoot()[ Curves ][ curveIndex ][ Segments ].GetVector()->GetSize() );
}

float D_CubismMotionJson::GetMotionCurveSegment( int curveIndex, int segmentIndex ) const
{
	return _json->GetRoot()[ Curves ][ curveIndex ][ Segments ][ segmentIndex ].ToFloat();
}

int D_CubismMotionJson::GetEventCount() const
{
	return _json->GetRoot()[ Meta ][ UserDataCount ].ToInt();
}

int D_CubismMotionJson::GetTotalEventValueSize() const
{
	return _json->GetRoot()[ Meta ][ TotalUserDataSize ].ToInt();
}

float D_CubismMotionJson::GetEventTime( int userDataIndex ) const
{
	return _json->GetRoot()[ UserData ][ userDataIndex ][ Time ].ToFloat();
}

const char* D_CubismMotionJson::GetEventValue( int userDataIndex ) const
{
	return _json->GetRoot()[ UserData ][ userDataIndex ][ Value ].GetRawString();
}





























D_CubismMoc* D_CubismMoc::Create( const BYTE* mocBytes, size_t size )
{
	D_CubismMoc *cubismMoc = NULL ;

	void *alignedBuffer = DXALLOCBASE( size, D_csmAlignofMoc ) ;
	_MEMCPY( alignedBuffer, mocBytes, size ) ;

	void *moc = CALL_csmReviveMocInPlace( ( alignedBuffer, ( DWORD )size ) ) ;
	if( moc )
	{
		cubismMoc = D_CSM_NEW D_CubismMoc( moc ) ;
	}

	return cubismMoc ;
}

void D_CubismMoc::Delete( D_CubismMoc* moc )
{
	D_CSM_DELETE_SELF( D_CubismMoc, moc ) ;
}

D_CubismMoc::D_CubismMoc( void* moc )
	: _moc( moc )
	, _modelCount( 0 )
{ }

D_CubismMoc::~D_CubismMoc()
{
	DXFREE( _moc ) ;
}

D_CubismModel* D_CubismMoc::CreateModel()
{
	D_CubismModel *cubismModel = NULL ;
	const DWORD modelSize = CALL_csmGetSizeofModel( ( _moc ) ) ;
	void *modelMemory = DXALLOCBASE( modelSize, D_csmAlignofModel ) ;

	void *model = CALL_csmInitializeModelInPlace( ( _moc, modelMemory, modelSize ) ) ;
	if( model )
	{
		cubismModel = D_CSM_NEW D_CubismModel( model ) ;
		cubismModel->Initialize() ;

		++_modelCount ;
	}

	return cubismModel ;
}

void D_CubismMoc::DeleteModel( D_CubismModel* model )
{
	D_CSM_DELETE_SELF( D_CubismModel, model ) ;
	--_modelCount ;
}















static int IsBitSet( const BYTE byte, const BYTE mask )
{
	return ( ( byte & mask ) == mask );
}

D_CubismModel::D_CubismModel( void* model )
	: _model( model )
	, _parameterValues( NULL )
	, _parameterMaximumValues( NULL )
	, _parameterMinimumValues( NULL )
	, _partOpacities( NULL )
{ }

D_CubismModel::~D_CubismModel()
{
	DXFREE( _model );
}

float D_CubismModel::GetParameterValue( D_CubismIdHandle parameterId )
{
	// �������̂��߂�ParameterIndex���擾�ł���@�\�ɂȂ��Ă��邪�A�O������̐ݒ�̎��͌Ăяo���p�x���Ⴂ���ߕs�v
	const int parameterIndex = GetParameterIndex( parameterId );
	return GetParameterValue( parameterIndex );
}

void D_CubismModel::SetParameterValue( D_CubismIdHandle parameteId, float value, float weight, bool force )
{
	const int index = GetParameterIndex( parameteId );
	SetParameterValue( index, value, weight, force );
}

void D_CubismModel::AddParameterValue( D_CubismIdHandle parameterId, float value, float weight )
{
	const int index = GetParameterIndex( parameterId );
	AddParameterValue( index, value, weight );
}

void D_CubismModel::SetDisableChangeParameter( D_CubismIdHandle parameterId, bool isDisable )
{
	const int index = GetParameterIndex( parameterId );
	SetDisableChangeParameter( index, isDisable );
}

void D_CubismModel::SetDisableChangeParameter( int parameterIndex, bool isDisable )
{
	if( isDisable )
	{
		bool Flag = false ;
		for( D_csmVector< int >::iterator ite = _disableChangeParameterIndices.Begin(); ite != _disableChangeParameterIndices.End() ; ++ite )
		{
			if( *ite == parameterIndex )
			{
				Flag = true ;
				break ;
			}
		}
		if( Flag == false )
		{
			_disableChangeParameterIndices.PushBack( parameterIndex ) ;
		}
	}
	else
	{
		for( D_csmVector< int >::iterator ite = _disableChangeParameterIndices.Begin(); ite != _disableChangeParameterIndices.End() ; ++ite )
		{
			if( *ite == parameterIndex )
			{
				_disableChangeParameterIndices.Erase( ite );
				break ;
			}
		}
	}
}

void D_CubismModel::AddParameterValue( int parameterIndex, float value, float weight )
{
	SetParameterValue( parameterIndex, ( GetParameterValue( parameterIndex ) + ( value * weight ) ) );
}

void D_CubismModel::MultiplyParameterValue( D_CubismIdHandle parameterId, float value, float weight )
{
	const int index = GetParameterIndex( parameterId );
	MultiplyParameterValue( index, value, weight );
}

void D_CubismModel::MultiplyParameterValue( int parameterIndex, float value, float weight )
{
	SetParameterValue( parameterIndex, ( GetParameterValue( parameterIndex ) * ( 1.0f + ( value - 1.0f ) * weight ) ) );
}

void D_CubismModel::Update() const
{
	// Update model.
	CALL_csmUpdateModel( ( _model ) );

	// Reset dynamic drawable flags.
	CALL_csmResetDrawableDynamicFlags( ( _model ) );
}

void D_CubismModel::SetPartOpacity( D_CubismIdHandle partId, float opacity )
{
	// �������̂��߂�PartIndex���擾�ł���@�\�ɂȂ��Ă��邪�A�O������̐ݒ�̎��͌Ăяo���p�x���Ⴂ���ߕs�v
	const int index = GetPartIndex( partId );

	if( index < 0 )
	{
		return; // �p�[�c�������̂ŃX�L�b�v
	}

	SetPartOpacity( index, opacity );
}

void D_CubismModel::SetPartOpacity( int partIndex, float opacity )
{
	if( _notExistPartOpacities.IsExist( partIndex ) )
	{
		_notExistPartOpacities[ partIndex ] = opacity;
		return;
	}

	//�C���f�b�N�X�͈͓̔����m
	// CSM_ASSERT(0 <= partIndex && partIndex < GetPartCount());

	_partOpacities[ partIndex ] = opacity;
}

float D_CubismModel::GetPartOpacity( D_CubismIdHandle partId )
{
	// �������̂��߂�PartIndex���擾�ł���@�\�ɂȂ��Ă��邪�A�O������̐ݒ�̎��͌Ăяo���p�x���Ⴂ���ߕs�v
	const int index = GetPartIndex( partId );

	if( index < 0 )
	{
		return 0; //�p�[�c�������̂ŃX�L�b�v
	}

	return GetPartOpacity( index );
}

float D_CubismModel::GetPartOpacity( int partIndex )
{
	if( _notExistPartOpacities.IsExist( partIndex ) )
	{
		// ���f���ɑ��݂��Ȃ��p�[�cID�̏ꍇ�A�񑶍݃p�[�c���X�g����s�����x��Ԃ�
		return _notExistPartOpacities[ partIndex ];
	}

	//�C���f�b�N�X�͈͓̔����m
	// CSM_ASSERT( 0 <= partIndex && partIndex < GetPartCount() );

	return _partOpacities[ partIndex ];
}

D_CubismIdHandle D_CubismModel::GetParameterId( int parameterIndex )
{
	const int      idCount = CALL_csmGetParameterCount( ( _model ) );

	if( parameterIndex < 0 || parameterIndex >= idCount )
	{
		return NULL ;
	}

	return _parameterIds[ parameterIndex ] ;
}

int D_CubismModel::GetParameterCount() const
{
    return CALL_csmGetParameterCount( ( _model ) );
}

float D_CubismModel::GetParameterDefaultValue( DWORD parameterIndex ) const
{
	return CALL_csmGetParameterDefaultValues( ( _model ) )[ parameterIndex ];
}

float D_CubismModel::GetParameterMaximumValue( DWORD parameterIndex ) const
{
	return CALL_csmGetParameterMaximumValues( ( _model ) )[ parameterIndex ];
}

float D_CubismModel::GetParameterMinimumValue( DWORD parameterIndex ) const
{
	return CALL_csmGetParameterMinimumValues( ( _model ) )[ parameterIndex ];
}

int D_CubismModel::GetParameterIndex( D_CubismIdHandle parameterId )
{
	int            parameterIndex;
	const int      idCount = CALL_csmGetParameterCount( ( _model ) );


	for( parameterIndex = 0; parameterIndex < idCount; ++parameterIndex )
	{
		if( parameterId != _parameterIds[ parameterIndex ] )
		{
			continue;
		}

		return parameterIndex;
	}

	// ���f���ɑ��݂��Ă��Ȃ��ꍇ�A�񑶍݃p�����[�^ID���X�g�����������A���̃C���f�b�N�X��Ԃ�
	if( _notExistParameterId.IsExist( parameterId ) )
	{
		return _notExistParameterId[ parameterId ];
	}

	// �񑶍݃p�����[�^ID���X�g�ɂȂ��ꍇ�A�V�����v�f��ǉ�����
	parameterIndex = CALL_csmGetParameterCount( ( _model ) ) + _notExistParameterId.GetSize();

	_notExistParameterId[ parameterId ] = parameterIndex;
	_notExistParameterValues.AppendKey( parameterIndex );

	return parameterIndex;
}

float D_CubismModel::GetParameterValue( int parameterIndex )
{
	if( _notExistParameterValues.IsExist( parameterIndex ) )
	{
		return _notExistParameterValues[ parameterIndex ];
	}

	//�C���f�b�N�X�͈͓̔����m
	// CSM_ASSERT(0 <= parameterIndex && parameterIndex < GetParameterCount());

	return _parameterValues[ parameterIndex ];
}

void D_CubismModel::SetParameterValue( int parameterIndex, float value, float weight, bool force )
{
	if( force == false )
	{
		for( D_csmVector< int >::iterator ite = _disableChangeParameterIndices.Begin(); ite != _disableChangeParameterIndices.End() ; ++ite )
		{
			if( *ite == parameterIndex )
			{
				return;
			}
		}
	}

	if( _notExistParameterValues.IsExist( parameterIndex ) )
	{
		_notExistParameterValues[ parameterIndex ] =
			( weight == 1 )	? value
			: ( _notExistParameterValues[ parameterIndex ] * ( 1 - weight ) ) +	( value * weight );
		return;
	}

	//�C���f�b�N�X�͈͓̔����m
	// CSM_ASSERT(0 <= parameterIndex && parameterIndex < GetParameterCount());

	if( CALL_csmGetParameterMaximumValues( ( _model ) )[ parameterIndex ] < value )
	{
		value = CALL_csmGetParameterMaximumValues( ( _model ) )[ parameterIndex ];
	}
	if( CALL_csmGetParameterMinimumValues( ( _model ) )[ parameterIndex ] > value )
	{
		value = CALL_csmGetParameterMinimumValues( ( _model ) )[ parameterIndex ];
	}

	if( weight == 1.0f )
	{
		_parameterValues[ parameterIndex ] = value ;
	}
	else
	{
		_parameterValues[ parameterIndex ] = ( _parameterValues[ parameterIndex ] * ( 1.0f - weight ) ) + ( value * weight );
	}
}

float D_CubismModel::GetCanvasWidth() const
{
	if( _model == NULL )
	{
		return 0.0f;
	}

	D_CubismVector2 tmpSizeInPixels;
	D_CubismVector2 tmpOriginInPixels;
	float tmpPixelsPerUnit;

	CALL_csmReadCanvasInfo( ( _model, &tmpSizeInPixels, &tmpOriginInPixels, &tmpPixelsPerUnit ) );

	return tmpSizeInPixels.X / tmpPixelsPerUnit;
}

float D_CubismModel::GetCanvasHeight() const
{
	if( _model == NULL )
	{
		return 0.0f;
	}

	D_CubismVector2 tmpSizeInPixels;
	D_CubismVector2 tmpOriginInPixels;
	float tmpPixelsPerUnit;

	CALL_csmReadCanvasInfo( ( _model, &tmpSizeInPixels, &tmpOriginInPixels, &tmpPixelsPerUnit ) );

	return tmpSizeInPixels.Y / tmpPixelsPerUnit;
}

// �L�����o�X�̏����擾����
void D_CubismModel::GetCanvasInfo( D_CubismVector2 *SizeInPixels, D_CubismVector2 *OriginInPixels, float *PixelsPerUnit )
{
	if( _model == NULL )
	{
		return;
	}

	D_CubismVector2 tmpSizeInPixels;
	D_CubismVector2 tmpOriginInPixels;
	float tmpPixelsPerUnit;

	CALL_csmReadCanvasInfo( ( _model, &tmpSizeInPixels, &tmpOriginInPixels, &tmpPixelsPerUnit ) );
	if( SizeInPixels   != NULL ) *SizeInPixels   = tmpSizeInPixels ;
	if( OriginInPixels != NULL ) *OriginInPixels = tmpOriginInPixels ;
	if( PixelsPerUnit  != NULL ) *PixelsPerUnit  = tmpPixelsPerUnit ;
}

int D_CubismModel::GetDrawableIndex( D_CubismIdHandle drawableId ) const
{
	const int drawableCount = CALL_csmGetDrawableCount( ( _model ) );

	for( int drawableIndex = 0; drawableIndex < drawableCount; ++drawableIndex )
	{
		if( _drawableIds[ drawableIndex ] == drawableId )
		{
			return drawableIndex;
		}
	}

	return -1;
}

const float* D_CubismModel::GetDrawableVertices( int drawableIndex ) const
{
	return ( const float* )( GetDrawableVertexPositions( drawableIndex ) );
}

int D_CubismModel::GetPartIndex( D_CubismIdHandle partId )
{
	int            partIndex;
	const int      idCount = CALL_csmGetPartCount( ( _model ) );

	for( partIndex = 0; partIndex < idCount; ++partIndex )
	{
		if( partId == _partIds[ partIndex ] )
		{
			return partIndex;
		}
	}

	const int partCount = CALL_csmGetPartCount( ( _model ) );

	// ���f���ɑ��݂��Ă��Ȃ��ꍇ�A�񑶍݃p�[�cID���X�g���ɂ��邩���������A���̃C���f�b�N�X��Ԃ�
	if( _notExistPartId.IsExist( partId ) )
	{
		return _notExistPartId[ partId ];
	}

	// �񑶍݃p�[�cID���X�g�ɂȂ��ꍇ�A�V�����v�f��ǉ�����
	partIndex = partCount + _notExistPartId.GetSize();

	_notExistPartId[ partId ] = partIndex;
	_notExistPartOpacities.AppendKey( partIndex );

	return partIndex;
}

void D_CubismModel::Initialize()
{
	// CSM_ASSERT(_model);

	_parameterValues = CALL_csmGetParameterValues( ( _model ) );
	_partOpacities = CALL_csmGetPartOpacities( ( _model ) );
	_parameterMaximumValues = CALL_csmGetParameterMaximumValues( ( _model ) );
	_parameterMinimumValues = CALL_csmGetParameterMinimumValues( ( _model ) );

	{
		const char** parameterIds = CALL_csmGetParameterIds( ( _model ) );
		const int  parameterCount = CALL_csmGetParameterCount( ( _model ) );

		_parameterIds.PrepareCapacity( parameterCount );
		for( int i = 0; i < parameterCount; ++i )
		{
			_parameterIds.PushBack( LIVE2DSYS.s_cubismIdManager->GetId( parameterIds[ i ] ) );
		}
	}

	{
		const char** partIds = CALL_csmGetPartIds( ( _model ) );
		const int  partCount = CALL_csmGetPartCount( ( _model ) );

		_partIds.PrepareCapacity( partCount );
		for( int i = 0; i < partCount; ++i )
		{
			_partIds.PushBack( LIVE2DSYS.s_cubismIdManager->GetId( partIds[ i ] ) );
		}
	}

	{
		const char** drawableIds = CALL_csmGetDrawableIds( ( _model ) );
		const int  drawableCount = CALL_csmGetDrawableCount( ( _model ) );

		_drawableIds.PrepareCapacity( drawableCount );
		for( int i = 0; i < drawableCount; ++i )
		{
			_drawableIds.PushBack( LIVE2DSYS.s_cubismIdManager->GetId( drawableIds[ i ] ) );
		}
	}
}

D_CubismIdHandle D_CubismModel::GetDrawableId( int drawableIndex ) const
{
	const char** parameterIds = CALL_csmGetDrawableIds( ( _model ) );
	return LIVE2DSYS.s_cubismIdManager->GetId( parameterIds[ drawableIndex ] );
}

int D_CubismModel::GetPartCount() const
{
	const int partCount = CALL_csmGetPartCount( ( _model ) );
	return partCount;
}

const int* D_CubismModel::GetDrawableRenderOrders() const
{
	const int* renderOrders = CALL_csmGetDrawableRenderOrders( ( _model ) );
	return renderOrders;
}

int D_CubismModel::GetDrawableCount() const
{
	const int drawableCount = CALL_csmGetDrawableCount( ( _model ) );
	return drawableCount;
}

int D_CubismModel::GetDrawableTextureIndices( int drawableIndex ) const
{
	const int* textureIndices = CALL_csmGetDrawableTextureIndices( ( _model ) );
	return textureIndices[ drawableIndex ];
}

int D_CubismModel::GetDrawableVertexIndexCount( int drawableIndex ) const
{
	const int* indexCounts = CALL_csmGetDrawableIndexCounts( ( _model ) );
	return indexCounts[ drawableIndex ];
}

int D_CubismModel::GetDrawableVertexCount( int drawableIndex ) const
{
	const int* vertexCounts = CALL_csmGetDrawableVertexCounts( ( _model ) );
	return vertexCounts[ drawableIndex ];
}

const WORD* D_CubismModel::GetDrawableVertexIndices( int drawableIndex ) const
{
	const WORD** indicesArray = CALL_csmGetDrawableIndices( ( _model ) );
	return indicesArray[ drawableIndex ];
}

const D_CubismVector2* D_CubismModel::GetDrawableVertexPositions( int drawableIndex ) const
{
	const D_CubismVector2** verticesArray = CALL_csmGetDrawableVertexPositions( ( _model ) );
	return verticesArray[ drawableIndex ];
}

const D_CubismVector2* D_CubismModel::GetDrawableVertexUvs( int drawableIndex ) const
{
	const D_CubismVector2** uvsArray = CALL_csmGetDrawableVertexUvs( ( _model ) );
	return uvsArray[ drawableIndex ];
}

float D_CubismModel::GetDrawableOpacity( int drawableIndex ) const
{
	const float* opacities = CALL_csmGetDrawableOpacities( ( _model ) );
	return opacities[ drawableIndex ];
}

int D_CubismModel::GetDrawableCulling( int drawableIndex ) const
{
	const BYTE* constantFlags = CALL_csmGetDrawableConstantFlags( ( _model ) );
	return !IsBitSet( constantFlags[ drawableIndex ], D_csmIsDoubleSided );
}

bool D_CubismModel::GetDrawableDynamicFlagIsVisible( int drawableIndex ) const
{
	const BYTE* dynamicFlags = CALL_csmGetDrawableDynamicFlags( ( _model ) );
	return IsBitSet( dynamicFlags[ drawableIndex ], D_csmIsVisible )!=0 ? true : false;
}

bool D_CubismModel::GetDrawableDynamicFlagVisibilityDidChange( int drawableIndex ) const
{
	const BYTE* dynamicFlags = CALL_csmGetDrawableDynamicFlags( ( _model ) );
	return IsBitSet( dynamicFlags[ drawableIndex ], D_csmVisibilityDidChange )!=0 ? true : false;
}

bool D_CubismModel::GetDrawableDynamicFlagOpacityDidChange( int drawableIndex ) const
{
	const BYTE* dynamicFlags = CALL_csmGetDrawableDynamicFlags( ( _model ) );
	return IsBitSet( dynamicFlags[ drawableIndex ], D_csmOpacityDidChange ) != 0 ? true : false;
}

bool D_CubismModel::GetDrawableDynamicFlagDrawOrderDidChange( int drawableIndex ) const
{
	const BYTE* dynamicFlags = CALL_csmGetDrawableDynamicFlags( ( _model ) );
	return IsBitSet( dynamicFlags[ drawableIndex ], D_csmDrawOrderDidChange ) != 0 ? true : false;
}

bool D_CubismModel::GetDrawableDynamicFlagRenderOrderDidChange( int drawableIndex ) const
{
	const BYTE* dynamicFlags = CALL_csmGetDrawableDynamicFlags( ( _model ) );
	return IsBitSet( dynamicFlags[ drawableIndex ], D_csmRenderOrderDidChange ) != 0 ? true : false;
}

bool D_CubismModel::GetDrawableDynamicFlagVertexPositionsDidChange( int drawableIndex ) const
{
	const BYTE* dynamicFlags = CALL_csmGetDrawableDynamicFlags( ( _model ) );
	return IsBitSet( dynamicFlags[ drawableIndex ], D_csmVertexPositionsDidChange ) != 0 ? true : false;
}


D_CubismBlendMode D_CubismModel::GetDrawableBlendMode( int drawableIndex ) const
{
	const BYTE* constantFlags = CALL_csmGetDrawableConstantFlags( ( _model ) );
	return ( IsBitSet( constantFlags[ drawableIndex ], D_csmBlendAdditive ) )
		? D_CubismBlendMode_Additive
		: ( IsBitSet( constantFlags[ drawableIndex ], D_csmBlendMultiplicative ) )
		? D_CubismBlendMode_Multiplicative
		: D_CubismBlendMode_Normal;
}

bool D_CubismModel::GetDrawableInvertedMask( int drawableIndex ) const
{
	const BYTE* constantFlags = CALL_csmGetDrawableConstantFlags( ( _model ) );
	return IsBitSet( constantFlags[ drawableIndex ], D_csmIsInvertedMask ) != 0 ? true : false;
}

const int** D_CubismModel::GetDrawableMasks() const
{
	const int** masks = CALL_csmGetDrawableMasks( ( _model ) );
	return masks;
}

const int* D_CubismModel::GetDrawableMaskCounts() const
{
	const int* maskCounts = CALL_csmGetDrawableMaskCounts( ( _model ) );
	return maskCounts;
}

void D_CubismModel::LoadParameters()
{
	int       parameterCount = CALL_csmGetParameterCount( ( _model ) );
	const int savedParameterCount = ( int )( _savedParameters.GetSize() );

	if( parameterCount > savedParameterCount )
	{
		parameterCount = savedParameterCount;
	}

	for( int i = 0; i < parameterCount; ++i )
	{
		_parameterValues[ i ] = _savedParameters[ i ];
	}
}

void D_CubismModel::SaveParameters()
{
	const int parameterCount = CALL_csmGetParameterCount( ( _model ) );
	const int savedParameterCount = ( int )( _savedParameters.GetSize() );

	for( int i = 0; i < parameterCount; ++i )
	{
		if( i < savedParameterCount )
		{
			_savedParameters[ i ] = _parameterValues[ i ];
		}
		else
		{
			_savedParameters.PushBack( _parameterValues[ i ], false );
		}
	}
}

void* D_CubismModel::GetModel() const
{
	return _model;
}

bool D_CubismModel::IsUsingMasking() const
{
	for( int d = 0; d < CALL_csmGetDrawableCount( ( _model ) ); ++d )
	{
		if( CALL_csmGetDrawableMaskCounts( ( _model ) )[ d ] <= 0 )
		{
			continue;
		}
		return true;
	}

	return false;
}















D_CubismMotionQueueEntry::D_CubismMotionQueueEntry()
	: _autoDelete( false )
	, _motion( NULL )
	, _available( true )
	, _finished( false )
	, _started( false )
	, _startTimeSeconds( -1.0f )
	, _fadeInStartTimeSeconds( 0.0f )
	, _endTimeSeconds( -1.0f )
	, _stateTimeSeconds( 0.0f )
	, _stateWeight( 0.0f )
	, _lastEventCheckSeconds( 0.0f )
	, _motionQueueEntryHandle( NULL )
{
	this->_motionQueueEntryHandle = this;
}

D_CubismMotionQueueEntry::~D_CubismMotionQueueEntry()
{
	if( _autoDelete && _motion )
	{
		D_ACubismMotion::Delete( _motion ); //
	}
}

void D_CubismMotionQueueEntry::StartFadeout( float fadeOutSeconds, float userTimeSeconds )
{
	const float newEndTimeSeconds = userTimeSeconds + fadeOutSeconds;

	if( _endTimeSeconds < 0.0f || newEndTimeSeconds < _endTimeSeconds )
	{
		_endTimeSeconds = newEndTimeSeconds;
	}
}

bool D_CubismMotionQueueEntry::IsFinished() const
{
	return _finished;
}

bool D_CubismMotionQueueEntry::IsStarted() const
{
	return _started;
}

float D_CubismMotionQueueEntry::GetStartTime() const
{
	return _startTimeSeconds;
}

float D_CubismMotionQueueEntry::GetFadeInStartTime() const
{
	return _fadeInStartTimeSeconds;
}

float D_CubismMotionQueueEntry::GetEndTime() const
{
	return _endTimeSeconds;
}

void D_CubismMotionQueueEntry::SetStartTime( float startTime )
{
	this->_startTimeSeconds = startTime;
}

void D_CubismMotionQueueEntry::SetFadeInStartTime( float startTime )
{
	this->_fadeInStartTimeSeconds = startTime;
}

void D_CubismMotionQueueEntry::SetEndTime( float endTime )
{
	this->_endTimeSeconds = endTime;
}

void D_CubismMotionQueueEntry::IsFinished( bool f )
{
	this->_finished = f;
}

void D_CubismMotionQueueEntry::IsStarted( bool f )
{
	this->_started = f;
}

bool D_CubismMotionQueueEntry::IsAvailable() const
{
	return _available;
}

void D_CubismMotionQueueEntry::IsAvailable( bool v )
{
	this->_available = v;
}

void D_CubismMotionQueueEntry::SetState( float timeSeconds, float weight )
{
	this->_stateTimeSeconds = timeSeconds;
	this->_stateWeight = weight;
}

float D_CubismMotionQueueEntry::GetStateTime() const
{
	return this->_stateTimeSeconds;
}

float D_CubismMotionQueueEntry::GetStateWeight() const
{
	return this->_stateWeight;
}


float D_CubismMotionQueueEntry::GetLastCheckEventTime() const
{
	return this->_lastEventCheckSeconds;
}

void D_CubismMotionQueueEntry::SetLastCheckEventTime( float checkTime )
{
	this->_lastEventCheckSeconds = checkTime;
}












D_CubismMotionQueueManager::D_CubismMotionQueueManager()
	: _userTimeSeconds( 0.0f )
	, _motionPlayTime( 0.0f )
	, _eventCallback( NULL )
	, _eventCustomData( NULL )
{}

D_CubismMotionQueueManager::~D_CubismMotionQueueManager()
{
	for( DWORD i = 0; i < _motions.GetSize(); ++i )
	{
		if( _motions[ i ] )
		{
			D_CSM_DELETE( _motions[ i ] );
		}
	}
}

D_CubismMotionQueueEntryHandle D_CubismMotionQueueManager::StartMotion( D_ACubismMotion* motion, bool autoDelete, float userTimeSeconds )
{
	if( motion == NULL )
	{
		return InvalidMotionQueueEntryHandleValue;
	}

	D_CubismMotionQueueEntry* motionQueueEntry = NULL;

	// ���Ƀ��[�V����������ΏI���t���O�𗧂Ă�
	for( DWORD i = 0; i < _motions.GetSize(); ++i )
	{
		motionQueueEntry = _motions.At( i );
		if( motionQueueEntry == NULL )
		{
			continue;
		}

		motionQueueEntry->StartFadeout( motionQueueEntry->_motion->GetFadeOutTime(), userTimeSeconds ); //�t�F�[�h�A�E�g���J�n���I������
	}

	motionQueueEntry = D_CSM_NEW D_CubismMotionQueueEntry(); // �I�����ɔj������
	motionQueueEntry->_autoDelete = autoDelete;
	motionQueueEntry->_motion = motion;

	_motions.PushBack( motionQueueEntry, false );

	_motionPlayTime = 0.0f;

	return motionQueueEntry->_motionQueueEntryHandle;
}

bool D_CubismMotionQueueManager::DoUpdateMotion( D_CubismModel* model, float userTimeSeconds )
{
	bool updated = false;

	// ------- �������s�� --------
	// ���Ƀ��[�V����������ΏI���t���O�𗧂Ă�

	for( D_csmVector<D_CubismMotionQueueEntry*>::iterator ite = _motions.Begin(); ite != _motions.End();)
	{
		D_CubismMotionQueueEntry* motionQueueEntry = *ite;

		if( motionQueueEntry == NULL )
		{
			ite = _motions.Erase( ite );          // �폜
			continue;
		}

		D_ACubismMotion* motion = motionQueueEntry->_motion;

		if( motion == NULL )
		{
			D_CSM_DELETE( motionQueueEntry );
			ite = _motions.Erase( ite );          // �폜

			continue;
		}

		// ------ �l�𔽉f���� ------
		motion->UpdateParameters( model, motionQueueEntry, userTimeSeconds );
		updated = true;

		// ------ ���[�U�g���K�[�C�x���g���������� ----
		const D_csmVector<const D_csmString*>& firedList = motion->GetFiredEvent(
			motionQueueEntry->GetLastCheckEventTime() - motionQueueEntry->GetStartTime()
			, userTimeSeconds - motionQueueEntry->GetStartTime()
		);

		for( DWORD i = 0; i < firedList.GetSize(); ++i )
		{
			_eventCallback( this, *( firedList[ i ] ), _eventCustomData );
		}

		motionQueueEntry->SetLastCheckEventTime( userTimeSeconds );

		// ----- �I���ς݂̏���������΍폜���� ------
		if( motionQueueEntry->IsFinished() )
		{
			D_CSM_DELETE( motionQueueEntry );
			ite = _motions.Erase( ite );          // �폜
		}
		else
		{
			++ite;
		}
	}

	return updated;
}

D_CubismMotionQueueEntry* D_CubismMotionQueueManager::GetCubismMotionQueueEntry( D_CubismMotionQueueEntryHandle motionQueueEntryNumber )
{
	//------- �������s�� --------
	//���Ƀ��[�V����������ΏI���t���O�𗧂Ă�

	for( D_csmVector<D_CubismMotionQueueEntry*>::iterator ite = _motions.Begin(); ite != _motions.End(); ++ite )
	{
		D_CubismMotionQueueEntry* motionQueueEntry = *ite;

		if( motionQueueEntry == NULL )
		{
			continue;
		}

		if( motionQueueEntry->_motionQueueEntryHandle == motionQueueEntryNumber )
		{
			return motionQueueEntry;
		}
	}

	return NULL;
}

bool D_CubismMotionQueueManager::IsFinished()
{
	// ------- �������s�� --------
	// ���Ƀ��[�V����������ΏI���t���O�𗧂Ă�

	for( D_csmVector<D_CubismMotionQueueEntry*>::iterator ite = _motions.Begin(); ite != _motions.End();)
	{
		D_CubismMotionQueueEntry* motionQueueEntry = *ite;

		if( motionQueueEntry == NULL )
		{
			ite = _motions.Erase( ite );          // �폜
			continue;
		}

		D_ACubismMotion* motion = motionQueueEntry->_motion;

		if( motion == NULL )
		{
			D_CSM_DELETE( motionQueueEntry );
			ite = _motions.Erase( ite );          // �폜
			continue;
		}

		// ----- �I���ς݂̏���������΍폜���� ------
		if( !motionQueueEntry->IsFinished() )
		{
			return false;
		}
		else
		{
			++ite;
		}
	}

	return true;
}

bool D_CubismMotionQueueManager::IsFinished( D_CubismMotionQueueEntryHandle motionQueueEntryNumber )
{
	// ���Ƀ��[�V����������ΏI���t���O�𗧂Ă�

	for( D_csmVector<D_CubismMotionQueueEntry*>::iterator ite = _motions.Begin(); ite != _motions.End(); ite++ )
	{
		D_CubismMotionQueueEntry* motionQueueEntry = *ite;

		if( motionQueueEntry == NULL )
		{
			continue;
		}

		if( motionQueueEntry->_motionQueueEntryHandle == motionQueueEntryNumber && !motionQueueEntry->IsFinished() )
		{
			return false;
		}
	}

	return true;
}

void D_CubismMotionQueueManager::StopAllMotions()
{
	// ------- �������s�� --------
	// ���Ƀ��[�V����������ΏI���t���O�𗧂Ă�

	for( D_csmVector<D_CubismMotionQueueEntry*>::iterator ite = _motions.Begin(); ite != _motions.End();)
	{
		D_CubismMotionQueueEntry* motionQueueEntry = *ite;

		if( motionQueueEntry == NULL )
		{
			ite = _motions.Erase( ite );

			continue;
		}

		// ----- �I���ς݂̏���������΍폜���� ------
		D_CSM_DELETE( motionQueueEntry );
		ite = _motions.Erase( ite ); //�폜
	}
}

void D_CubismMotionQueueManager::SetEventCallback( D_CubismMotionEventFunction callback, void* customData )
{
	_eventCallback   = callback;
	_eventCustomData = customData;
}















// exp3.json�̃L�[�ƃf�t�H���g�l
const char* ExpressionKeyFadeIn = "FadeInTime";
const char* ExpressionKeyFadeOut = "FadeOutTime";
const char* ExpressionKeyParameters = "Parameters";
const char* ExpressionKeyId = "Id";
const char* ExpressionKeyValue = "Value";
const char* ExpressionKeyBlend = "Blend";
const char* BlendValueAdd = "Add";
const char* BlendValueMultiply = "Multiply";
const char* BlendValueOverwrite = "Overwrite";
const float DefaultFadeTime = 1.0f;

D_CubismExpressionMotion::D_CubismExpressionMotion()
{ }

D_CubismExpressionMotion::~D_CubismExpressionMotion()
{ }

D_CubismExpressionMotion* D_CubismExpressionMotion::Create( const BYTE* buffer, size_t size )
{
	D_CubismExpressionMotion* expression = D_CSM_NEW D_CubismExpressionMotion();

	D_CubismJson* json = D_CubismJson::Create( buffer, size );
	D_JsonValue& root = json->GetRoot();

	expression->SetFadeInTime( root[ ExpressionKeyFadeIn ].ToFloat( DefaultFadeTime ) );   // �t�F�[�h�C��
	expression->SetFadeOutTime( root[ ExpressionKeyFadeOut ].ToFloat( DefaultFadeTime ) ); // �t�F�[�h�A�E�g

	// �e�p�����[�^�ɂ���
	const int parameterCount = root[ ExpressionKeyParameters ].GetSize();
	expression->_parameters.PrepareCapacity( parameterCount );

	for( int i = 0; i < parameterCount; ++i )
	{
		D_JsonValue& param = root[ ExpressionKeyParameters ][ i ];
		const D_CubismIdHandle parameterId = LIVE2DSYS.s_cubismIdManager->GetId( param[ ExpressionKeyId ].GetRawString() ); // �p�����[�^ID
		const float value = ( float )( param[ ExpressionKeyValue ].ToFloat() );   // �l

		// �v�Z���@�̐ݒ�
		ExpressionBlendType blendType;

		if( param[ ExpressionKeyBlend ].IsNull() || param[ ExpressionKeyBlend ].GetString() == BlendValueAdd )
		{
			blendType = ExpressionBlendType_Add;
		}
		else if( param[ ExpressionKeyBlend ].GetString() == BlendValueMultiply )
		{
			blendType = ExpressionBlendType_Multiply;
		}
		else if( param[ ExpressionKeyBlend ].GetString() == BlendValueOverwrite )
		{
			blendType = ExpressionBlendType_Overwrite;
		}
		else
		{
			// ���̑� �d�l�ɂȂ��l��ݒ肵���Ƃ��͉��Z���[�h�ɂ��邱�Ƃŕ���
			blendType = ExpressionBlendType_Add;
		}

		// �ݒ�I�u�W�F�N�g���쐬���ă��X�g�ɒǉ�����
		D_ExpressionParameter item;

		item.ParameterId = parameterId;
		item.BlendType   = blendType;
		item.Value       = value;

		expression->_parameters.PushBack( item );
	}

	D_CubismJson::Delete( json ); // JSON�f�[�^�͕s�v�ɂȂ�����폜����

	return expression;
}

void D_CubismExpressionMotion::DoUpdateParameters( D_CubismModel* model, float /*userTimeSeconds*/, float weight, D_CubismMotionQueueEntry* /*motionQueueEntry*/ )
{
	for( DWORD i = 0; i < _parameters.GetSize(); ++i )
	{
		D_ExpressionParameter& parameter = _parameters[ i ];

		switch( parameter.BlendType )
		{
		case ExpressionBlendType_Add: {
			model->AddParameterValue( parameter.ParameterId, parameter.Value, weight );            // ���Εω� ���Z
			break;
		}
		case ExpressionBlendType_Multiply: {
			model->MultiplyParameterValue( parameter.ParameterId, parameter.Value, weight );       // ���Εω� ��Z
			break;
		}
		case ExpressionBlendType_Overwrite: {
			model->SetParameterValue( parameter.ParameterId, parameter.Value, weight );            // ��Εω� �㏑��
			break;
		}
		default:
			// �d�l�ɂȂ��l��ݒ肵���Ƃ��͊��ɉ��Z���[�h�ɂȂ��Ă���
			break;
		}
	}
}

















void D_ACubismMotion::Delete( D_ACubismMotion* motion )
{
	D_CSM_DELETE_SELF( D_ACubismMotion, motion );
}

D_ACubismMotion::D_ACubismMotion()
	: _fadeInSeconds( -1.0f )
	, _fadeOutSeconds( -1.0f )
	, _weight( 1.0f )
	, _offsetSeconds( 0.0f ) //�Đ��̊J�n����
{ }

D_ACubismMotion::~D_ACubismMotion()
{
	this->_weight = 0.0f;
}

void D_ACubismMotion::UpdateParameters( D_CubismModel* model, D_CubismMotionQueueEntry* motionQueueEntry, float userTimeSeconds )
{
	if( !motionQueueEntry->IsAvailable() || motionQueueEntry->IsFinished() )
	{
		return;
	}

	if( !motionQueueEntry->IsStarted() )
	{
		motionQueueEntry->IsStarted( true );
		motionQueueEntry->SetStartTime( userTimeSeconds - _offsetSeconds ); //���[�V�����̊J�n�������L�^
		motionQueueEntry->SetFadeInStartTime( userTimeSeconds ); //�t�F�[�h�C���̊J�n����

		const float duration = GetDuration();

		if( motionQueueEntry->GetEndTime() < 0 )
		{
			//�J�n���Ă��Ȃ������ɏI���ݒ肵�Ă���ꍇ������B
			motionQueueEntry->SetEndTime( ( duration <= 0 ) ? -1 : motionQueueEntry->GetStartTime() + duration );
			//duration == -1 �̏ꍇ�̓��[�v����
		}
	}

	float fadeWeight = _weight; //���݂̒l�Ɗ|�����킹�銄���@

	//---- �t�F�[�h�C���E�A�E�g�̏��� ----
	//�P���ȃT�C���֐��ŃC�[�W���O����
	const float fadeIn = _fadeInSeconds == 0.0f
		? 1.0f
		: D_CubismMath::GetEasingSine( ( userTimeSeconds - motionQueueEntry->GetFadeInStartTime() ) / _fadeInSeconds );

	const float fadeOut = ( _fadeOutSeconds == 0.0f || motionQueueEntry->GetEndTime() < 0.0f )
		? 1.0f
		: D_CubismMath::GetEasingSine( ( motionQueueEntry->GetEndTime() - userTimeSeconds ) / _fadeOutSeconds );

	fadeWeight = fadeWeight * fadeIn * fadeOut;

	motionQueueEntry->SetState( userTimeSeconds, fadeWeight );

	// CSM_ASSERT( 0.0f <= fadeWeight && fadeWeight <= 1.0f );

	//---- �S�Ẵp�����[�^ID�����[�v���� ----
	DoUpdateParameters( model, userTimeSeconds, fadeWeight, motionQueueEntry );

	//�㏈��
	//�I���������߂�����I���t���O�𗧂Ă�iD_CubismMotionQueueManager�j
	if( ( motionQueueEntry->GetEndTime() > 0 ) && ( motionQueueEntry->GetEndTime() < userTimeSeconds ) )
	{
		motionQueueEntry->IsFinished( true );      //�I��
	}
}

void D_ACubismMotion::SetFadeInTime( float fadeInSeconds )
{
	this->_fadeInSeconds = fadeInSeconds;
}

void D_ACubismMotion::SetFadeOutTime( float fadeOutSeconds )
{
	this->_fadeOutSeconds = fadeOutSeconds;
}

float D_ACubismMotion::GetFadeOutTime() const
{
	return this->_fadeOutSeconds;
}

float D_ACubismMotion::GetFadeInTime() const
{
	return this->_fadeInSeconds;
}

void D_ACubismMotion::SetWeight( float weight )
{
	this->_weight = weight;
}

float D_ACubismMotion::GetWeight() const
{
	return this->_weight;
}

float D_ACubismMotion::GetDuration()
{
	return -1.0f;
}

float D_ACubismMotion::GetLoopDuration()
{
	return -1.0f;
}

void D_ACubismMotion::SetOffsetTime( float offsetSeconds )
{
	this->_offsetSeconds = offsetSeconds;
}

const D_csmVector<const D_csmString*>& D_ACubismMotion::GetFiredEvent( float /*beforeCheckTimeSeconds*/, float /*motionTimeSeconds*/ )
{
	return _firedEventValues;
}













const char* EffectNameEyeBlink = "EyeBlink";
const char* EffectNameLipSync  = "LipSync";
const char* TargetNameModel = "Model";
const char* TargetNameParameter = "Parameter";
const char* TargetNamePartOpacity = "PartOpacity";

D_CubismMotionPoint LerpPoints( const D_CubismMotionPoint a, const D_CubismMotionPoint b, const float t )
{
	D_CubismMotionPoint result;

	result.Time = a.Time + ( ( b.Time - a.Time ) * t );
	result.Value = a.Value + ( ( b.Value - a.Value ) * t );

	return result;
}

float LinearEvaluate( const D_CubismMotionPoint* points, float time )
{
	float t = ( time - points[ 0 ].Time ) / ( points[ 1 ].Time - points[ 0 ].Time );

	if( t < 0.0f )
	{
		t = 0.0f;
	}

	return points[ 0 ].Value + ( ( points[ 1 ].Value - points[ 0 ].Value ) * t );
}

float BezierEvaluate( const D_CubismMotionPoint* points, float time )
{
	float t = ( time - points[ 0 ].Time ) / ( points[ 3 ].Time - points[ 0 ].Time );

	if( t < 0.0f )
	{
		t = 0.0f;
	}

	const D_CubismMotionPoint p01 = LerpPoints( points[ 0 ], points[ 1 ], t );
	const D_CubismMotionPoint p12 = LerpPoints( points[ 1 ], points[ 2 ], t );
	const D_CubismMotionPoint p23 = LerpPoints( points[ 2 ], points[ 3 ], t );

	const D_CubismMotionPoint p012 = LerpPoints( p01, p12, t );
	const D_CubismMotionPoint p123 = LerpPoints( p12, p23, t );

	return LerpPoints( p012, p123, t ).Value;
}

float SteppedEvaluate( const D_CubismMotionPoint* points, float /*time*/ )
{
	return points[ 0 ].Value;
}

float InverseSteppedEvaluate( const D_CubismMotionPoint* points, float /*time*/ )
{
	return points[ 1 ].Value;
}

float EvaluateCurve( const D_CubismMotionData* motionData, const int index, float time )
{
	// Find segment to evaluate.
	const D_CubismMotionCurve& curve = motionData->Curves[ index ];

	int target = -1;
	const int totalSegmentCount = curve.BaseSegmentIndex + curve.SegmentCount;
	int pointPosition = 0;
	for( int i = curve.BaseSegmentIndex; i < totalSegmentCount; ++i )
	{
		// Get first point of next segment.
		pointPosition = motionData->Segments[ i ].BasePointIndex
			+ ( motionData->Segments[ i ].SegmentType == D_CubismMotionSegmentType_Bezier
				? 3
				: 1 );


		// Break if time lies within current segment.
		if( motionData->Points[ pointPosition ].Time > time )
		{
			target = i;
			break;
		}
	}


	if( target == -1 )
	{
		return motionData->Points[ pointPosition ].Value;
	}


	const D_CubismMotionSegment& segment = motionData->Segments[ target ];

	return segment.Evaluate( &motionData->Points[ segment.BasePointIndex ], time );
}

D_CubismMotion::D_CubismMotion()
	: _sourceFrameRate( 30.0f )
	, _loopDurationSeconds( -1.0f )
	, _isLoop( false )                // true���� false �փf�t�H���g��ύX
	, _isLoopFadeIn( true )           // ���[�v���Ƀt�F�[�h�C�����L�����ǂ����̃t���O
	, _lastWeight( 0.0f )
	, _motionData( NULL )
	, _modelCurveIdEyeBlink( NULL )
	, _modelCurveIdLipSync( NULL )
{ }

D_CubismMotion::~D_CubismMotion()
{
	D_CSM_DELETE( _motionData );
}

D_CubismMotion* D_CubismMotion::Create( const BYTE* buffer, size_t size )
{
	D_CubismMotion* ret = D_CSM_NEW D_CubismMotion();

	ret->Parse( buffer, size );
	ret->_sourceFrameRate = ret->_motionData->Fps;
	ret->_loopDurationSeconds = ret->_motionData->Duration;

	// NOTE: Editor�ł̓��[�v����̃��[�V���������o���͔�Ή�
	// ret->_loop = (ret->_motionData->Loop > 0);

	return ret;
}

float D_CubismMotion::GetDuration()
{
	return _isLoop ? -1.0f : _loopDurationSeconds;
}

void D_CubismMotion::DoUpdateParameters( D_CubismModel* model, float userTimeSeconds, float fadeWeight, D_CubismMotionQueueEntry* motionQueueEntry )
{
	DWORD i ;

	if( _modelCurveIdEyeBlink == NULL )
	{
		_modelCurveIdEyeBlink = LIVE2DSYS.s_cubismIdManager->GetId( EffectNameEyeBlink );
	}

	if( _modelCurveIdLipSync == NULL )
	{
		_modelCurveIdLipSync = LIVE2DSYS.s_cubismIdManager->GetId( EffectNameLipSync );
	}

	float timeOffsetSeconds = userTimeSeconds - motionQueueEntry->GetStartTime();

	if( timeOffsetSeconds < 0.0f )
	{
		timeOffsetSeconds = 0.0f; // �G���[���
	}

	int lipSyncValueEnable = FALSE ;
	float lipSyncValue = 0.0f ;
	int eyeBlinkValueEnable = FALSE ;
	float eyeBlinkValue = 0.0f ;

	//�܂΂����A���b�v�V���N�̂������[�V�����̓K�p�����o���邽�߂̃r�b�g�imaxFlagCount�܂�
	const int MaxTargetSize = 64;
	ULONGLONG lipSyncFlags = 0;
	ULONGLONG eyeBlinkFlags = 0;

	//�u���A���b�v�V���N�̃^�[�Q�b�g��������𒴂��Ă���ꍇ
//	if (_eyeBlinkParameterIds.GetSize() > MaxTargetSize)
//	{
//	    CubismLogDebug("too many eye blink targets : %d", _eyeBlinkParameterIds.GetSize());
//	}
//	if (_lipSyncParameterIds.GetSize() > MaxTargetSize)
//	{
//	    CubismLogDebug("too many lip sync targets : %d", _lipSyncParameterIds.GetSize());
//	}

	const float tmpFadeIn = ( _fadeInSeconds <= 0.0f )
		? 1.0f
		: D_CubismMath::GetEasingSine( ( userTimeSeconds - motionQueueEntry->GetFadeInStartTime() ) / _fadeInSeconds );

	const float tmpFadeOut = ( _fadeOutSeconds <= 0.0f || motionQueueEntry->GetEndTime() < 0.0f )
		? 1.0f
		: D_CubismMath::GetEasingSine( ( motionQueueEntry->GetEndTime() - userTimeSeconds ) / _fadeOutSeconds );

	float value;
	int c, parameterIndex;

	// 'Repeat' time as necessary.
	float time = timeOffsetSeconds;

	if( _isLoop )
	{
		while( time > _motionData->Duration )
		{
			time -= _motionData->Duration;
		}
	}

	D_csmVector<D_CubismMotionCurve>& curves = _motionData->Curves;

	// Evaluate model curves.
	for( c = 0; c < _motionData->CurveCount && curves[ c ].Type == D_CubismMotionCurveTarget_Model; ++c )
	{
		// Evaluate curve and call handler.
		value = EvaluateCurve( _motionData, c, time );

		if( curves[ c ].Id == _modelCurveIdEyeBlink )
		{
			eyeBlinkValueEnable = TRUE ;
			eyeBlinkValue = value;
		}
		else if( curves[ c ].Id == _modelCurveIdLipSync )
		{
			lipSyncValueEnable = TRUE ;
			lipSyncValue = value;
		}
	}

	int parameterMotionCurveCount = 0;

	for( ; c < _motionData->CurveCount && curves[ c ].Type == D_CubismMotionCurveTarget_Parameter; ++c )
	{
		parameterMotionCurveCount++;

		// Find parameter index.
		parameterIndex = model->GetParameterIndex( curves[ c ].Id );

		// Skip curve evaluation if no value in sink.
		if( parameterIndex == -1 )
		{
			continue;
		}

		const float sourceValue = model->GetParameterValue( parameterIndex );

		// Evaluate curve and apply value.
		value = EvaluateCurve( _motionData, c, time );

		if( eyeBlinkValueEnable )
		{
			ULONGLONG Num = 1;
			for( i = 0; i < _eyeBlinkParameterIds.GetSize() && i < MaxTargetSize; ++i, Num *= 2 )
			{
				if( _eyeBlinkParameterIds[ i ] == curves[ c ].Id )
				{
					value *= eyeBlinkValue;
					eyeBlinkFlags |= Num;
					break;
				}
			}
		}

		if( lipSyncValueEnable )
		{
			ULONGLONG Num = 1;
			for( i = 0; i < _lipSyncParameterIds.GetSize() && i < MaxTargetSize; ++i, Num *= 2 )
			{
				if( _lipSyncParameterIds[ i ] == curves[ c ].Id )
				{
					value += lipSyncValue;
					lipSyncFlags |= Num;
					break;
				}
			}
		}

		float v;
		// �p�����[�^���Ƃ̃t�F�[�h
		if( curves[ c ].FadeInTime < 0.0f && curves[ c ].FadeOutTime < 0.0f )
		{
			//���[�V�����̃t�F�[�h��K�p
			v = sourceValue + ( value - sourceValue ) * fadeWeight;
		}
		else
		{
			// �p�����[�^�ɑ΂��ăt�F�[�h�C�����t�F�[�h�A�E�g���ݒ肵�Ă���ꍇ�͂������K�p
			float fin;
			float fout;

			if( curves[ c ].FadeInTime < 0.0f )
			{
				fin = tmpFadeIn;
			}
			else
			{
				fin = curves[ c ].FadeInTime == 0.0f
					? 1.0f
					: D_CubismMath::GetEasingSine( ( userTimeSeconds - motionQueueEntry->GetFadeInStartTime() ) / curves[ c ].FadeInTime );
			}

			if( curves[ c ].FadeOutTime < 0.0f )
			{
				fout = tmpFadeOut;
			}
			else
			{
				fout = ( curves[ c ].FadeOutTime == 0.0f || motionQueueEntry->GetEndTime() < 0.0f )
					? 1.0f
					: D_CubismMath::GetEasingSine( ( motionQueueEntry->GetEndTime() - userTimeSeconds ) / curves[ c ].FadeOutTime );
			}

			const float paramWeight = _weight * fin * fout;

			// �p�����[�^���Ƃ̃t�F�[�h��K�p
			v = sourceValue + ( value - sourceValue ) * paramWeight;
		}

		model->SetParameterValue( parameterIndex, v );
	}

	{
		if( eyeBlinkValueEnable )
		{
			for( i = 0; i < _eyeBlinkParameterIds.GetSize() && i < MaxTargetSize; ++i )
			{
				const float sourceValue = model->GetParameterValue( _eyeBlinkParameterIds[ i ] );
				//���[�V�����ł̏㏑�������������ɂ͂܂΂����͓K�p���Ȃ�
				if( ( eyeBlinkFlags >> i ) & 0x01 )
				{
					continue;
				}

				const float v = sourceValue + ( eyeBlinkValue - sourceValue ) * fadeWeight;

				model->SetParameterValue( _eyeBlinkParameterIds[ i ], v );
			}
		}

		if( lipSyncValueEnable )
		{
			for( i = 0; i < _lipSyncParameterIds.GetSize() && i < MaxTargetSize; ++i )
			{
				const float sourceValue = model->GetParameterValue( _lipSyncParameterIds[ i ] );
				//���[�V�����ł̏㏑�������������ɂ̓��b�v�V���N�͓K�p���Ȃ�
				if( ( lipSyncFlags >> i ) & 0x01 )
				{
					continue;
				}

				const float v = sourceValue + ( lipSyncValue - sourceValue ) * fadeWeight;

				model->SetParameterValue( _lipSyncParameterIds[ i ], v );
			}
		}
	}

	for( ; c < _motionData->CurveCount && curves[ c ].Type == D_CubismMotionCurveTarget_PartOpacity; ++c )
	{
		// Find parameter index.
		parameterIndex = model->GetParameterIndex( curves[ c ].Id );

		// Skip curve evaluation if no value in sink.
		if( parameterIndex == -1 )
		{
			continue;
		}

		// Evaluate curve and apply value.
		value = EvaluateCurve( _motionData, c, time );

		model->SetParameterValue( parameterIndex, value );
	}

	if( timeOffsetSeconds >= _motionData->Duration )
	{
		if( _isLoop )
		{
			motionQueueEntry->SetStartTime( userTimeSeconds ); //�ŏ��̏�Ԃ�
			if( _isLoopFadeIn )
			{
				//���[�v���Ń��[�v�p�t�F�[�h�C�����L���̂Ƃ��́A�t�F�[�h�C���ݒ肵����
				motionQueueEntry->SetFadeInStartTime( userTimeSeconds );
			}
		}
		else
		{
			motionQueueEntry->IsFinished( true );
		}
	}

	_lastWeight = fadeWeight;
}

void D_CubismMotion::Parse( const BYTE* motionJson, const size_t size )
{
	_motionData = D_CSM_NEW D_CubismMotionData;

	D_CubismMotionJson* json = D_CSM_NEW D_CubismMotionJson( motionJson, size );

	_motionData->Duration = json->GetMotionDuration();
	_motionData->Loop = json->IsMotionLoop();
	_motionData->CurveCount = ( short )json->GetMotionCurveCount();
	_motionData->Fps = json->GetMotionFps();
	_motionData->EventCount = json->GetEventCount();

	if( json->IsExistMotionFadeInTime() )
	{
		_fadeInSeconds = ( json->GetMotionFadeInTime() < 0.0f )
			? 1.0f
			: json->GetMotionFadeInTime();
	}
	else
	{
		_fadeInSeconds = 1.0f;
	}

	if( json->IsExistMotionFadeOutTime() )
	{
		_fadeOutSeconds = ( json->GetMotionFadeOutTime() < 0.0f )
			? 1.0f
			: json->GetMotionFadeOutTime();
	}
	else
	{
		_fadeOutSeconds = 1.0f;
	}

	_motionData->Curves.UpdateSize( _motionData->CurveCount, D_CubismMotionCurve(), true );
	_motionData->Segments.UpdateSize( json->GetMotionTotalSegmentCount(), D_CubismMotionSegment(), true );
	_motionData->Points.UpdateSize( json->GetMotionTotalPointCount(), D_CubismMotionPoint(), true );
	_motionData->Events.UpdateSize( _motionData->EventCount, D_CubismMotionEvent(), true );

	int totalPointCount = 0;
	int totalSegmentCount = 0;

	// Curves
	for( int curveCount = 0; curveCount < _motionData->CurveCount; ++curveCount )
	{
		if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, json->GetMotionCurveTarget( curveCount ), TargetNameModel ) == 0 )
		{
			_motionData->Curves[ curveCount ].Type = D_CubismMotionCurveTarget_Model;
		}
		else if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, json->GetMotionCurveTarget( curveCount ), TargetNameParameter ) == 0 )
		{
			_motionData->Curves[ curveCount ].Type = D_CubismMotionCurveTarget_Parameter;
		}
		else if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, json->GetMotionCurveTarget( curveCount ), TargetNamePartOpacity ) == 0 )
		{
			_motionData->Curves[ curveCount ].Type = D_CubismMotionCurveTarget_PartOpacity;
		}

		_motionData->Curves[ curveCount ].Id = json->GetMotionCurveId( curveCount );

		_motionData->Curves[ curveCount ].SegmentCount = 0;

		_motionData->Curves[ curveCount ].BaseSegmentIndex = totalSegmentCount;

		_motionData->Curves[ curveCount ].FadeInTime =
			( json->IsExistMotionCurveFadeInTime( curveCount ) )
			? json->GetMotionCurveFadeInTime( curveCount )
			: -1.0f ;
		_motionData->Curves[ curveCount ].FadeOutTime =
			( json->IsExistMotionCurveFadeOutTime( curveCount ) )
			? json->GetMotionCurveFadeOutTime( curveCount )
			: -1.0f;

		// Segments
		for( int segmentPosition = 0; segmentPosition < json->GetMotionCurveSegmentCount( curveCount );)
		{
			if( segmentPosition == 0 )
			{
				_motionData->Segments[ totalSegmentCount ].BasePointIndex = totalPointCount;

				_motionData->Points[ totalPointCount ].Time = json->GetMotionCurveSegment( curveCount, segmentPosition );
				_motionData->Points[ totalPointCount ].Value = json->GetMotionCurveSegment( curveCount, segmentPosition + 1 );

				totalPointCount += 1;
				segmentPosition += 2;
			}
			else
			{
				_motionData->Segments[ totalSegmentCount ].BasePointIndex = totalPointCount - 1;
			}

			const int segment = ( int )( json->GetMotionCurveSegment( curveCount, segmentPosition ) );

			switch( segment )
			{
			case D_CubismMotionSegmentType_Linear: {
				_motionData->Segments[ totalSegmentCount ].SegmentType = D_CubismMotionSegmentType_Linear;
				_motionData->Segments[ totalSegmentCount ].Evaluate = LinearEvaluate;

				_motionData->Points[ totalPointCount ].Time = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 1 ) );
				_motionData->Points[ totalPointCount ].Value = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 2 ) );

				totalPointCount += 1;
				segmentPosition += 3;

				break;
			}
			case D_CubismMotionSegmentType_Bezier: {
				_motionData->Segments[ totalSegmentCount ].SegmentType = D_CubismMotionSegmentType_Bezier;
				_motionData->Segments[ totalSegmentCount ].Evaluate = BezierEvaluate;

				_motionData->Points[ totalPointCount ].Time = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 1 ) );
				_motionData->Points[ totalPointCount ].Value = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 2 ) );

				_motionData->Points[ totalPointCount + 1 ].Time = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 3 ) );
				_motionData->Points[ totalPointCount + 1 ].Value = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 4 ) );

				_motionData->Points[ totalPointCount + 2 ].Time = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 5 ) );
				_motionData->Points[ totalPointCount + 2 ].Value = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 6 ) );

				totalPointCount += 3;
				segmentPosition += 7;

				break;
			}
			case D_CubismMotionSegmentType_Stepped: {
				_motionData->Segments[ totalSegmentCount ].SegmentType = D_CubismMotionSegmentType_Stepped;
				_motionData->Segments[ totalSegmentCount ].Evaluate = SteppedEvaluate;

				_motionData->Points[ totalPointCount ].Time = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 1 ) );
				_motionData->Points[ totalPointCount ].Value = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 2 ) );

				totalPointCount += 1;
				segmentPosition += 3;

				break;
			}
			case D_CubismMotionSegmentType_InverseStepped: {
				_motionData->Segments[ totalSegmentCount ].SegmentType = D_CubismMotionSegmentType_InverseStepped;
				_motionData->Segments[ totalSegmentCount ].Evaluate = InverseSteppedEvaluate;

				_motionData->Points[ totalPointCount ].Time = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 1 ) );
				_motionData->Points[ totalPointCount ].Value = json->GetMotionCurveSegment( curveCount, ( segmentPosition + 2 ) );

				totalPointCount += 1;
				segmentPosition += 3;

				break;
			}
			default: {
				// CSM_ASSERT(0);
				break;
			}
			}

			++_motionData->Curves[ curveCount ].SegmentCount;
			++totalSegmentCount;
		}
	}


	for( int userdatacount = 0; userdatacount < json->GetEventCount(); ++userdatacount )
	{
		_motionData->Events[ userdatacount ].FireTime = json->GetEventTime( userdatacount );
		_motionData->Events[ userdatacount ].Value = json->GetEventValue( userdatacount );
	}

	D_CSM_DELETE( json );
}

void D_CubismMotion::SetParameterFadeInTime( D_CubismIdHandle parameterId, float value )
{
	D_csmVector<D_CubismMotionCurve>& curves = _motionData->Curves;

	for( short i = 0; i < _motionData->CurveCount; ++i )
	{
		if( parameterId == curves[ i ].Id )
		{
			curves[ i ].FadeInTime = value;
			return;
		}
	}
}

void D_CubismMotion::SetParameterFadeOutTime( D_CubismIdHandle parameterId, float value )
{
	D_csmVector<D_CubismMotionCurve>& curves = _motionData->Curves;

	for( short i = 0; i < _motionData->CurveCount; ++i )
	{
		if( parameterId == curves[ i ].Id )
		{
			curves[ i ].FadeOutTime = value;
			return;
		}
	}
}

float D_CubismMotion::GetParameterFadeInTime( D_CubismIdHandle parameterId ) const
{
	D_csmVector<D_CubismMotionCurve>& curves = _motionData->Curves;

	for( short i = 0; i < _motionData->CurveCount; ++i )
	{
		if( parameterId == curves[ i ].Id )
		{
			return curves[ i ].FadeInTime;
		}
	}

	return -1;
}

float D_CubismMotion::GetParameterFadeOutTime( D_CubismIdHandle parameterId ) const
{
	D_csmVector<D_CubismMotionCurve>& curves = _motionData->Curves;

	for( short i = 0; i < _motionData->CurveCount; ++i )
	{
		if( parameterId == curves[ i ].Id )
		{
			return curves[ i ].FadeOutTime;
		}
	}

	return -1;
}

void D_CubismMotion::IsLoop( bool loop )
{
	this->_isLoop = loop;
}

bool D_CubismMotion::IsLoop() const
{
	return this->_isLoop;
}

void D_CubismMotion::IsLoopFadeIn( bool loopFadeIn )
{
	this->_isLoopFadeIn = loopFadeIn;
}

bool D_CubismMotion::IsLoopFadeIn() const
{
	return this->_isLoopFadeIn;
}

float D_CubismMotion::GetLoopDuration()
{
	return _loopDurationSeconds;
}

void D_CubismMotion::SetEffectIds( const D_csmVector<D_CubismIdHandle>& eyeBlinkParameterIds, const D_csmVector<D_CubismIdHandle>& lipSyncParameterIds )
{
	_eyeBlinkParameterIds = eyeBlinkParameterIds;
	_lipSyncParameterIds = lipSyncParameterIds;
}

const D_csmVector<const D_csmString*>& D_CubismMotion::GetFiredEvent( float beforeCheckTimeSeconds, float motionTimeSeconds )
{
	_firedEventValues.UpdateSize( 0 );
	// �C�x���g�̔��΃`�F�b�N
	for( int u = 0; u < _motionData->EventCount; ++u )
	{
		if( ( _motionData->Events[ u ].FireTime >beforeCheckTimeSeconds ) &&
			( _motionData->Events[ u ].FireTime <= motionTimeSeconds ) )
		{
			_firedEventValues.PushBack( &_motionData->Events[ u ].Value );
		}
	}

	return _firedEventValues;
}























D_CubismMatrix44::D_CubismMatrix44()
{
    LoadIdentity();
}

D_CubismMatrix44::~D_CubismMatrix44()
{ }

void D_CubismMatrix44::LoadIdentity()
{
    float c[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    SetMatrix(c);
}

float* D_CubismMatrix44::GetArray()
{
    return _tr;
}

void D_CubismMatrix44::Multiply( float* a, float* b, float* dst )
{
	int i, j, k ;
	float c[ 16 ] = {
						0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f
	};
	int n = 4;

	for( i = 0; i < n; ++i )
	{
		for( j = 0; j < n; ++j )
		{
			for( k = 0; k < n; ++k )
			{
				c[ j + i * 4 ] += a[ k + i * 4 ] * b[ j + k * 4 ];
			}
		}
	}

	for( i = 0; i < 16; ++i )
	{
		dst[ i ] = c[ i ];
	}
}

void D_CubismMatrix44::TranslateRelative(float x, float y)
{
    float tr1[16] = {
                          1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          x,    y,    0.0f, 1.0f
                          };

    Multiply(tr1, _tr, _tr);
}

void D_CubismMatrix44::Translate(float x, float y)
{
    _tr[12] = x;
    _tr[13] = y;
}

void D_CubismMatrix44::ScaleRelative(float x, float y)
{
    float tr1[16] = {
                          x,      0.0f,   0.0f, 0.0f,
                          0.0f,   y,      0.0f, 0.0f,
                          0.0f,   0.0f,   1.0f, 0.0f,
                          0.0f,   0.0f,   0.0f, 1.0f
                          };

    Multiply(tr1, _tr, _tr);
}

void D_CubismMatrix44::Scale(float x, float y)
{
    _tr[0] = x;
    _tr[5] = y;
}

void D_CubismMatrix44::RotateRelative( float angle )
{
	float Sin, Cos ;
	_SINCOS_PLATFORM( angle, &Sin, &Cos ) ;

    float tr1[16] = {
                          Cos,    Sin,   0.0f, 0.0f,
                          -Sin,   Cos,   0.0f, 0.0f,
                          0.0f,   0.0f,  1.0f, 0.0f,
                          0.0f,   0.0f,  0.0f, 1.0f
                          };

    Multiply(tr1, _tr, _tr);
}

float D_CubismMatrix44::TransformX(float src)
{
    return _tr[0] * src + _tr[12];
}

float D_CubismMatrix44::InvertTransformX(float src)
{
    return (src - _tr[12]) / _tr[0];
}

float D_CubismMatrix44::TransformY(float src)
{
    return _tr[5] * src + _tr[13];
}

float D_CubismMatrix44::InvertTransformY(float src)
{
    return (src - _tr[13]) / _tr[5];
}

void D_CubismMatrix44::SetMatrix(float* tr)
{
    for (int i = 0; i < 16; ++i)
    {
        _tr[i] = tr[i];
    }
}

float D_CubismMatrix44::GetScaleX() const
{
    return _tr[0];
}

float D_CubismMatrix44::GetScaleY() const
{
    return _tr[5];
}

float D_CubismMatrix44::GetTranslateX() const
{
    return _tr[12];
}

float D_CubismMatrix44::GetTranslateY() const
{
    return _tr[13];
}

void D_CubismMatrix44::TranslateX(float x)
{
    _tr[12] = x;
}

void D_CubismMatrix44::TranslateY(float y)
{
    _tr[13] = y;
}

void D_CubismMatrix44::MultiplyByMatrix(D_CubismMatrix44* m)
{
    Multiply(m->GetArray(), _tr, _tr);
}






















D_CubismModelMatrix::D_CubismModelMatrix()
                                : _width(0.0f)
                                , _height(0.0f)
{ }

D_CubismModelMatrix::D_CubismModelMatrix(float w, float h)
{
    _width = w;
    _height = h;

    // ���_(0,0)�𒆐S�ɂ��āA��ʂɎ��܂�悤�ȑ傫���ŏ�����
    if (_width > _height)
    {
        SetWidth(_height / _width);
    }
    else
    {
        SetHeight(1.0f);
    }
}

D_CubismModelMatrix::~D_CubismModelMatrix()
{ }

void D_CubismModelMatrix::SetCenterPosition(float x, float y)
{
    CenterX(x);
    CenterY(y);
}

void D_CubismModelMatrix::Bottom(float y)
{
    const float h = _height * GetScaleY();
    TranslateY(y - h);
}

void D_CubismModelMatrix::CenterY(float y)
{
    const float h = _height * GetScaleY();
    TranslateY(y - (h / 2.0f));
}

void D_CubismModelMatrix::Right(float x)
{
    const float w = _width * GetScaleX();
    TranslateX(x - w);
}

void D_CubismModelMatrix::CenterX(float x)
{
    const float w = _width * GetScaleX();
    TranslateX(x - (w / 2.0f));
}

void D_CubismModelMatrix::SetWidth(float w)
{
    const float scaleX = w / _width;
    const float scaleY = scaleX;
    Scale(scaleX, scaleY);
}

void D_CubismModelMatrix::SetHeight(float h)
{
    const float scaleX = h / _height;
    const float scaleY = scaleX;
    Scale(scaleX, scaleY);
}

void D_CubismModelMatrix::SetupFromLayout( D_csmMap<D_csmString, float>& layout )
{
	D_csmMap<D_csmString, float>::const_iterator ite ;
	const char* KeyWidth = "width";
	const char* KeyHeight = "height";
	const char* KeyX = "x";
	const char* KeyY = "y";
	const char* KeyCenterX = "center_x";
	const char* KeyCenterY = "center_y";
	const char* KeyTop = "top";
	const char* KeyBottom = "bottom";
	const char* KeyLeft = "left";
	const char* KeyRight = "right";

	for( ite = layout.Begin(); ite != layout.End(); ++ite )
	{
		const D_csmString key = ite->First;
		const float value = ite->Second;

		if( key == KeyWidth )
		{
			SetWidth( value );
		}
		else if( key == KeyHeight )
		{
			SetHeight( value );
		}
	}

	for( ite = layout.Begin(); ite != layout.End(); ++ite )
	{
		const D_csmString key = ite->First;
		const float value = ite->Second;

		if( key == KeyX )
		{
			SetX( value );
		}
		else if( key == KeyY )
		{
			SetY( value );
		}
		else if( key == KeyCenterX )
		{
			CenterX( value );
		}
		else if( key == KeyCenterY )
		{
			CenterY( value );
		}
		else if( key == KeyTop )
		{
			Top( value );
		}
		else if( key == KeyBottom )
		{
			Bottom( value );
		}
		else if( key == KeyLeft )
		{
			Left( value );
		}
		else if( key == KeyRight )
		{
			Right( value );
		}
	}
}

void D_CubismModelMatrix::SetPosition(float x, float y)
{
    Translate(x, y);
}

void D_CubismModelMatrix::Top(float y)
{
    SetY(y);
}

void D_CubismModelMatrix::Left(float x)
{
    SetX(x);
}

void D_CubismModelMatrix::SetX(float x)
{
    TranslateX(x);
}

void D_CubismModelMatrix::SetY(float y)
{
    TranslateY(y);
}



















D_CubismMotionManager::D_CubismMotionManager()
    : _currentPriority(0)
    , _reservePriority(0)
{ }

D_CubismMotionManager::~D_CubismMotionManager()
{ }

int D_CubismMotionManager::GetCurrentPriority() const
{
    return _currentPriority;
}

int D_CubismMotionManager::GetReservePriority() const
{
    return _reservePriority;
}

void D_CubismMotionManager::SetReservePriority(int val)
{
    _reservePriority = val;
}

D_CubismMotionQueueEntryHandle D_CubismMotionManager::StartMotionPriority(D_ACubismMotion* motion, bool autoDelete, int priority)
{
    if (priority == _reservePriority)
    {
        _reservePriority = 0;           // �\�������
    }

    _currentPriority = priority;        // �Đ������[�V�����̗D��x��ݒ�

    return D_CubismMotionQueueManager::StartMotion(motion, autoDelete, _userTimeSeconds);
}

bool D_CubismMotionManager::UpdateMotion(D_CubismModel* model, float deltaTimeSeconds)
{
    _userTimeSeconds += deltaTimeSeconds;
	_motionPlayTime += deltaTimeSeconds;

    const bool updated = D_CubismMotionQueueManager::DoUpdateMotion(model, _userTimeSeconds);

    if (IsFinished())
    {
        _currentPriority = 0;           // �Đ������[�V�����̗D��x������
    }

    return updated;
}

bool D_CubismMotionManager::ReserveMotion(int priority)
{
    if ((priority <= _reservePriority) || (priority <= _currentPriority))
    {
        return false;
    }

    _reservePriority = priority;

    return true;
}



















// ID�Ŏw�肳�ꂽ�ڂ̃p�����[�^���A0�̂Ƃ��ɕ���Ȃ� true �A1�̎��ɕ���Ȃ� false �B
const bool CloseIfZero = true;

D_CubismEyeBlink* D_CubismEyeBlink::Create(D_ICubismModelSetting* modelSetting)
{
    return D_CSM_NEW D_CubismEyeBlink(modelSetting);
}

void D_CubismEyeBlink::Delete(D_CubismEyeBlink* eyeBlink)
{
    D_CSM_DELETE_SELF(D_CubismEyeBlink, eyeBlink);
}

D_CubismEyeBlink::D_CubismEyeBlink(D_ICubismModelSetting* modelSetting)
    : _blinkingState(EyeState_First)
    , _nextBlinkingTime(0.0f)
    , _stateStartTimeSeconds(0.0f)
    , _blinkingIntervalSeconds(4.0f)
    , _closingSeconds(0.1f)
    , _closedSeconds(0.05f)
    , _openingSeconds(0.15f)
    , _userTimeSeconds(0.0f)
{
    if (modelSetting == NULL)
    {
        return;
    }

    for (int i = 0; i < modelSetting->GetEyeBlinkParameterCount(); ++i)
    {
        _parameterIds.PushBack(modelSetting->GetEyeBlinkParameterId(i));
    }
}

D_CubismEyeBlink::~D_CubismEyeBlink()
{ }

float D_CubismEyeBlink::DeterminNextBlinkingTiming() const
{
	const float r = NS_GetRand( 10000 ) / 10000.0f ;

	return _userTimeSeconds + ( r * ( 2.0f * _blinkingIntervalSeconds - 1.0f ) );
}

void D_CubismEyeBlink::SetBlinkingInterval( float blinkigInterval )
{
	_blinkingIntervalSeconds = blinkigInterval;
}

void D_CubismEyeBlink::SetBlinkingSettings( float closing, float closed, float opening )
{
	_closingSeconds = closing;
	_closedSeconds =  closed;
	_openingSeconds = opening;
}

void D_CubismEyeBlink::SetParameterIds( const D_csmVector<D_CubismIdHandle>& parameterIds )
{
	_parameterIds = parameterIds;
}

const D_csmVector<D_CubismIdHandle>& D_CubismEyeBlink::GetParameterIds() const
{
	return _parameterIds;
}

void D_CubismEyeBlink::UpdateParameters( D_CubismModel* model, float deltaTimeSeconds )
{
	_userTimeSeconds += deltaTimeSeconds;
	float parameterValue;
	float t = 0.0f;

	switch( _blinkingState )
	{
	case EyeState_Closing:
		t = ( ( _userTimeSeconds - _stateStartTimeSeconds ) / _closingSeconds );

		if( t >= 1.0f )
		{
			t = 1.0f;
			_blinkingState = EyeState_Closed;
			_stateStartTimeSeconds = _userTimeSeconds;
		}

		parameterValue = 1.0f - t;

		break;
	case EyeState_Closed:
		t = ( ( _userTimeSeconds - _stateStartTimeSeconds ) / _closedSeconds );

		if( t >= 1.0f )
		{
			_blinkingState = EyeState_Opening;
			_stateStartTimeSeconds = _userTimeSeconds;
		}

		parameterValue = 0.0f;

		break;
	case EyeState_Opening:
		t = ( ( _userTimeSeconds - _stateStartTimeSeconds ) /_openingSeconds );

		if( t >= 1.0f )
		{
			t = 1.0f;
			_blinkingState = EyeState_Interval;
			_nextBlinkingTime = DeterminNextBlinkingTiming();
		}

		parameterValue = t;

		break;
	case EyeState_Interval:
		if( _nextBlinkingTime < _userTimeSeconds )
		{
			_blinkingState = EyeState_Closing;
			_stateStartTimeSeconds = _userTimeSeconds;
		}

		parameterValue = 1.0f;

		break;
	case EyeState_First:
	default:
		_blinkingState = EyeState_Interval;
		_nextBlinkingTime = DeterminNextBlinkingTiming();

		parameterValue = 1.0f;

		break;
	}

	if( !CloseIfZero )
	{
		parameterValue = -parameterValue;
	}

	for( DWORD i = 0; i < _parameterIds.GetSize(); ++i )
	{
		model->SetParameterValue( _parameterIds[ i ], parameterValue );
	}
}





















D_CubismBreath* D_CubismBreath::Create()
{
    return D_CSM_NEW D_CubismBreath();
}

void D_CubismBreath::Delete( D_CubismBreath* instance )
{
	D_CSM_DELETE_SELF( D_CubismBreath, instance );
}

D_CubismBreath::D_CubismBreath()
	: _currentTime( 0.0f )
{ }

D_CubismBreath::~D_CubismBreath()
{ }

void D_CubismBreath::SetParameters( D_csmVector<BreathParameterData>& breathParameters )
{
	_breathParameters = breathParameters;
}

D_csmVector<D_CubismBreath::BreathParameterData>& D_CubismBreath::GetParameters()
{
	return _breathParameters;
}

void D_CubismBreath::UpdateParameters( D_CubismModel* model, float deltaTimeSeconds )
{
	_currentTime += deltaTimeSeconds;

	const float t = _currentTime * 2.0f * 3.14159f;

	for( DWORD i = 0; i < _breathParameters.GetSize(); ++i )
	{
		BreathParameterData* data = &_breathParameters[ i ];

		model->AddParameterValue( data->ParameterId, data->Offset + ( data->Peak * sinf( t / data->Cycle ) ), data->Weight );
	}
}





















#define Epsilon						(0.001f)
#define DefaultFadeInSeconds		(0.5f)

// Pose.json�̃^�O
const char*   FadeIn = "FadeInTime";
const char*   Link   = "Link";
const char*   Groups = "Groups";
const char*   Id     = "Id";

D_CubismPose::PartData::PartData()
{ }

D_CubismPose::PartData::~PartData()
{ }

D_CubismPose::PartData::PartData(const PartData& v)
                                            : ParameterIndex(0)
                                            , PartIndex(0)
{
    PartId = v.PartId;

    for (D_csmVector<PartData>::const_iterator ite = v.Link.Begin(); ite != v.Link.End(); ++ite)
    {
        Link.PushBack(*ite);
    }
}

D_CubismPose::PartData& D_CubismPose::PartData::operator=(const PartData& v)
{
    PartId = v.PartId;

    for (D_csmVector<PartData>::const_iterator ite = v.Link.Begin(); ite != v.Link.End(); ++ite)
    {
        Link.PushBack(*ite);
    }

    return (*this);
}

void D_CubismPose::PartData::Initialize(D_CubismModel* model)
{
    ParameterIndex = model->GetParameterIndex(PartId);
    PartIndex = model->GetPartIndex(PartId);

    model->SetParameterValue(ParameterIndex, 1);
}

D_CubismPose::D_CubismPose() : _fadeTimeSeconds(DefaultFadeInSeconds)
                         , _lastModel(NULL)
{ }

D_CubismPose::~D_CubismPose()
{ }

D_CubismPose* D_CubismPose::Create(const BYTE* pose3json, size_t size)
{
    D_CubismPose*         ret = D_CSM_NEW D_CubismPose();
    D_CubismJson*  json = D_CubismJson::Create(pose3json, size);
    D_JsonValue&       root = json->GetRoot();

    // �t�F�[�h���Ԃ̎w��
    if (!root[FadeIn].IsNull())
    {
        ret->_fadeTimeSeconds = root[FadeIn].ToFloat(DefaultFadeInSeconds);

        if (ret->_fadeTimeSeconds < 0.0f)
        {
            ret->_fadeTimeSeconds = DefaultFadeInSeconds;
        }
    }

    // �p�[�c�O���[�v
    D_JsonValue&      poseListInfo = root[Groups];
    const int     poseCount = poseListInfo.GetSize();

    for (int poseIndex = 0; poseIndex < poseCount; ++poseIndex)
    {
        D_JsonValue&      idListInfo = poseListInfo[poseIndex];
        const int    idCount = idListInfo.GetSize();
        int    groupCount = 0;

        for (int groupIndex = 0; groupIndex < idCount; ++groupIndex)
        {
            D_JsonValue&   partInfo = idListInfo[groupIndex];
            PartData        partData;
            const D_CubismIdHandle parameterId = LIVE2DSYS.s_cubismIdManager->GetId(partInfo[Id].GetRawString());

            partData.PartId = parameterId;

            // �����N����p�[�c�̐ݒ�
            if (!partInfo[Link].IsNull())
            {
                D_JsonValue&   linkListInfo = partInfo[Link];
                const int        linkCount = linkListInfo.GetSize();

                for (int linkIndex = 0; linkIndex < linkCount; ++linkIndex)
                {
                    PartData             linkPart;
                    const D_CubismIdHandle linkId = LIVE2DSYS.s_cubismIdManager->GetId(linkListInfo[linkIndex].GetString());

                    linkPart.PartId = linkId;

                    partData.Link.PushBack(linkPart);
                }
            }

            ret->_partGroups.PushBack(partData);

            ++groupCount;
        }

        ret->_partGroupCounts.PushBack(groupCount);

    }

    D_CubismJson::Delete(json);

    return ret;
}

void D_CubismPose::Delete(D_CubismPose* pose)
{
    D_CSM_DELETE_SELF(D_CubismPose, pose);
}

void D_CubismPose::Reset(D_CubismModel* model)
{
    int beginIndex = 0;

    for (DWORD i = 0; i < _partGroupCounts.GetSize(); ++i)
    {
        const int groupCount = _partGroupCounts[i];

        for (int j = beginIndex; j < beginIndex + groupCount; ++j)
        {
            _partGroups[j].Initialize(model);

            const int partsIndex = _partGroups[j].PartIndex;
            const int paramIndex = _partGroups[j].ParameterIndex;

            if (partsIndex < 0)
            {
                continue;
            }

            model->SetPartOpacity( partsIndex, (j == beginIndex ? 1.0f : 0.0f));
            model->SetParameterValue(   paramIndex, (j == beginIndex ? 1.0f : 0.0f));

            for (DWORD k = 0; k < _partGroups[j].Link.GetSize(); ++k)
            {
                _partGroups[j].Link[k].Initialize(model);
            }
        }

        beginIndex += groupCount;

    }

}

void D_CubismPose::CopyPartOpacities(D_CubismModel* model)
{
    for (DWORD groupIndex = 0; groupIndex < _partGroups.GetSize(); ++groupIndex)
    {
        PartData& partData = _partGroups[groupIndex];

        if (partData.Link.GetSize() == 0)
        {
            continue; // �A������p�����[�^�͂Ȃ�
        }

        const int    partIndex = _partGroups[groupIndex].PartIndex;
        const float  opacity = model->GetPartOpacity(partIndex);

        for (DWORD linkIndex = 0; linkIndex < partData.Link.GetSize(); ++linkIndex)
        {
            PartData&   linkPart = partData.Link[linkIndex];
            const int    linkPartIndex = linkPart.PartIndex;

            if (linkPartIndex < 0)
            {
                continue;
            }

            model->SetPartOpacity(linkPartIndex, opacity);
        }
    }
}

void D_CubismPose::DoFade( D_CubismModel* model, float deltaTimeSeconds, int beginIndex, int partGroupCount )
{
	int i ;
	int    visiblePartIndex = -1;
	float  newOpacity = 1.0f;

	const float Phi = 0.5f;
	const float BackOpacityThreshold = 0.15f;

	// ���݁A�\����ԂɂȂ��Ă���p�[�c���擾
	for( i = beginIndex; i < beginIndex + partGroupCount; ++i )
	{
		const int partIndex = _partGroups[ i ].PartIndex;
		const int paramIndex = _partGroups[ i ].ParameterIndex;

		if( model->GetParameterValue( paramIndex ) > Epsilon )
		{
			if( visiblePartIndex >= 0 )
			{
				break;
			}

			visiblePartIndex = i;
			newOpacity = model->GetPartOpacity( partIndex );

			// �V�����s�����x���v�Z
			newOpacity += ( deltaTimeSeconds / _fadeTimeSeconds );

			if( newOpacity > 1.0f )
			{
				newOpacity = 1.0f;
			}
		}
	}

	if( visiblePartIndex < 0 )
	{
		visiblePartIndex = 0;
		newOpacity = 1.0f;
	}

	//  �\���p�[�c�A��\���p�[�c�̕s�����x��ݒ肷��
	for( i = beginIndex; i < beginIndex + partGroupCount; ++i )
	{
		const int partsIndex = _partGroups[ i ].PartIndex;

		//  �\���p�[�c�̐ݒ�
		if( visiblePartIndex == i )
		{
			model->SetPartOpacity( partsIndex, newOpacity ); // ��ɐݒ�
		}
		// ��\���p�[�c�̐ݒ�
		else
		{
			float opacity = model->GetPartOpacity( partsIndex );
			float a1;          // �v�Z�ɂ���ċ��߂���s�����x

			if( newOpacity < Phi )
			{
				a1 = newOpacity * ( Phi - 1 ) / Phi + 1.0f; // (0,1),(phi,phi)��ʂ钼����
			}
			else
			{
				a1 = ( 1 - newOpacity ) * Phi / ( 1.0f - Phi ); // (1,0),(phi,phi)��ʂ钼����
			}

			// �w�i�̌����銄���𐧌�����ꍇ
			const float backOpacity = ( 1.0f - a1 ) * ( 1.0f - newOpacity );

			if( backOpacity > BackOpacityThreshold )
			{
				a1 = 1.0f - BackOpacityThreshold / ( 1.0f - newOpacity );
			}

			if( opacity > a1 )
			{
				opacity = a1; // �v�Z�̕s�����x�����傫����΁i�Z����΁j�s�����x���グ��
			}

			model->SetPartOpacity( partsIndex, opacity );
		}
	}
}

void D_CubismPose::UpdateParameters(D_CubismModel* model, float deltaTimeSeconds)
{
    // �O��̃��f���Ɠ����ł͂Ȃ��Ƃ��͏��������K�v
    if (model != _lastModel)
    {
        // �p�����[�^�C���f�b�N�X�̏�����
        Reset(model);
    }

    _lastModel = model;

    // �ݒ肩�玞�Ԃ�ύX����ƁA�o�ߎ��Ԃ��}�C�i�X�ɂȂ邱�Ƃ�����̂ŁA�o�ߎ���0�Ƃ��đΉ��B
    if (deltaTimeSeconds < 0.0f)
    {
        deltaTimeSeconds = 0.0f;
    }

    int beginIndex = 0;

    for (DWORD i = 0; i < _partGroupCounts.GetSize(); i++)
    {
        const int partGroupCount = _partGroupCounts[i];

        DoFade(model, deltaTimeSeconds, beginIndex, partGroupCount);

        beginIndex += partGroupCount;
    }

    CopyPartOpacities(model);
}

#undef Epsilon
#undef DefaultFadeInSeconds





















const int      FrameRate = 30;
const float    Epsilon = 0.01f;

D_CubismTargetPoint::D_CubismTargetPoint()
                                    : _faceTargetX(0.0f)
                                    , _faceTargetY(0.0f)
                                    , _faceX(0.0f)
                                    , _faceY(0.0f)
                                    , _faceVX(0.0f)
                                    , _faceVY(0.0f)
                                    , _lastTimeSeconds(0.0f)
                                    , _userTimeSeconds(0.0f)
{ }

D_CubismTargetPoint::~D_CubismTargetPoint()
{ }

void D_CubismTargetPoint::Update(float deltaTimeSeconds)
{
    // �f���^���Ԃ����Z����
    _userTimeSeconds += deltaTimeSeconds;

    // ��𒆉����獶�E�ɐU��Ƃ��̕��ϓI�ȑ�����  �b���x�B�����E�������l�����āA����2�{���ō����x�Ƃ���
    // ��̂ӂ����A����(0.0)����A���E��(+-1.0)�Ƃ���
    const float FaceParamMaxV = 40.0 / 10.0f;                                      // 7.5�b�Ԃ�40���ړ��i5.3/sc)
    const float MaxV = FaceParamMaxV * 1.0f / ( float )(FrameRate);  // 1frame������ɕω��ł��鑬�x�̏��

    if (_lastTimeSeconds == 0.0f)
    {
        _lastTimeSeconds = _userTimeSeconds;
        return;
    }

    const float  deltaTimeWeight = (_userTimeSeconds - _lastTimeSeconds) * ( float )(FrameRate);
    _lastTimeSeconds = _userTimeSeconds;

    // �ō����x�ɂȂ�܂ł̎��Ԃ�
    const float TimeToMaxSpeed = 0.15f;
    const float FrameToMaxSpeed = TimeToMaxSpeed * ( float )(FrameRate);     // sec * frame/sec
    const float MaxA = deltaTimeWeight * MaxV / FrameToMaxSpeed;                           // 1frame������̉����x

    // �ڎw�������́A(dx, dy)�����̃x�N�g���ƂȂ�
    const float dx = _faceTargetX - _faceX;
    const float dy = _faceTargetY - _faceY;

    if (D_CubismMath::AbsF(dx) <= Epsilon && D_CubismMath::AbsF(dy) <= Epsilon)
    {
        return; // �ω��Ȃ�
    }

    // ���x�̍ő�����傫���ꍇ�́A���x�𗎂Ƃ�
    const float d = D_CubismMath::SqrtF((dx * dx) + (dy * dy));

    // �i�s�����̍ő呬�x�x�N�g��
    const float vx = MaxV * dx / d;
    const float vy = MaxV * dy / d;

    // ���݂̑��x����A�V�K���x�ւ̕ω��i�����x�j�����߂�
    float ax = vx - _faceVX;
    float ay = vy - _faceVY;

    const float a = D_CubismMath::SqrtF((ax * ax) + (ay * ay));

    // �����̂Ƃ�
    if (a < -MaxA || a > MaxA)
    {
        ax *= MaxA / a;
        ay *= MaxA / a;
    }

    // �����x�����̑��x�ɑ����āA�V���x�Ƃ���
    _faceVX += ax;
    _faceVY += ay;

    // �ړI�̕����ɋ߂Â����Ƃ��A���炩�Ɍ������邽�߂̏���
    // �ݒ肳�ꂽ�����x�Ŏ~�܂邱�Ƃ̂ł��鋗���Ƒ��x�̊֌W����
    // ���݂Ƃ肤��ō����x���v�Z���A����ȏ�̂Ƃ��͑��x�𗎂Ƃ�
    // ���{���A�l�Ԃ͋ؗ͂ŗ́i�����x�j�𒲐��ł��邽�߁A��莩�R�x���������A�ȒP�ȏ����ł��܂��Ă���
    {
        // �����x�A���x�A�����̊֌W���B
        //            2  6           2               3
        //      sqrt(a  t  + 16 a h t  - 8 a h) - a t
        // v = --------------------------------------
        //                    2
        //                 4 t  - 2
        // (t=1)
        //  ����t�́A���炩���߉����x�A���x��1/60(�t���[�����[�g�A�P�ʂȂ�)��
        //  �l���Ă���̂ŁAt���P�Ƃ��ď����Ă悢�i�������؁j

        const float maxV = 0.5f * (D_CubismMath::SqrtF((MaxA * MaxA) + 16.0f * MaxA * d - 8.0f * MaxA * d) - MaxA);
        const float curV = D_CubismMath::SqrtF((_faceVX * _faceVX) + (_faceVY * _faceVY));

        if (curV > maxV)
        {
            // ���݂̑��x > �ō����x�̂Ƃ��A�ō����x�܂Ō���
            _faceVX *= maxV / curV;
            _faceVY *= maxV / curV;
        }
    }

    _faceX += _faceVX;
    _faceY += _faceVY;
}

void D_CubismTargetPoint::Set(float x, float y)
{
    this->_faceTargetX = x;
    this->_faceTargetY = y;
}

float D_CubismTargetPoint::GetX() const
{
    return this->_faceX;
}

float D_CubismTargetPoint::GetY() const
{
    return this->_faceY;
}





















// JSON keys
#define STR_Position				"Position"
#define STR_X						"X"
#define STR_Y						"Y"
#define STR_Angle					"Angle"
#define STR_Type					"Type"
#define STR_Id						"Id"

// Meta
#define STR_Meta					"Meta"
#define STR_EffectiveForces			"EffectiveForces"
#define STR_TotalInputCount			"TotalInputCount"
#define STR_TotalOutputCount		"TotalOutputCount"
#define STR_PhysicsSettingCount		"PhysicsSettingCount"
#define STR_Gravity					"Gravity"
#define STR_Wind					"Wind"
#define STR_VertexCount				"VertexCount"

// PhysicsSettings
#define STR_PhysicsSettings			"PhysicsSettings"
#define STR_Normalization			"Normalization"
#define STR_Minimum					"Minimum"
#define STR_Maximum					"Maximum"
#define STR_Default					"Default"
#define STR_Reflect					"Reflect"
#define STR_Weight					"Weight"

// Input
#define STR_Input					"Input"
#define STR_Source					"Source"

// Output
#define STR_Output					"Output"
#define STR_Scale					"Scale"
#define STR_VertexIndex				"VertexIndex"
#define STR_Destination				"Destination"

// Particle
#define STR_Vertices				"Vertices"
#define STR_Mobility				"Mobility"
#define STR_Delay					"Delay"
#define STR_Radius					"Radius"
#define STR_Acceleration			"Acceleration"

D_CubismPhysicsJson::D_CubismPhysicsJson(const BYTE* buffer, size_t size)
{
    _json = D_CubismJson::Create(buffer, size);
}

D_CubismPhysicsJson::~D_CubismPhysicsJson()
{
    D_CubismJson::Delete(_json);
}

D_CubismVector2 D_CubismPhysicsJson::GetGravity() const
{
    D_CubismVector2 ret;
    ret.X = _json->GetRoot()[STR_Meta][STR_EffectiveForces][STR_Gravity][STR_X].ToFloat();
    ret.Y = _json->GetRoot()[STR_Meta][STR_EffectiveForces][STR_Gravity][STR_Y].ToFloat();
    return ret;
}

D_CubismVector2 D_CubismPhysicsJson::GetWind() const
{
    D_CubismVector2 ret;
    ret.X = _json->GetRoot()[STR_Meta][STR_EffectiveForces][STR_Wind][STR_X].ToFloat();
    ret.Y = _json->GetRoot()[STR_Meta][STR_EffectiveForces][STR_Wind][STR_Y].ToFloat();
    return ret;
}

int D_CubismPhysicsJson::GetSubRigCount() const
{
    return _json->GetRoot()[STR_Meta][STR_PhysicsSettingCount].ToInt();
}

int D_CubismPhysicsJson::GetTotalInputCount() const
{
    return _json->GetRoot()[STR_Meta][STR_TotalInputCount].ToInt();
}

int D_CubismPhysicsJson::GetTotalOutputCount() const
{
    return _json->GetRoot()[STR_Meta][STR_TotalOutputCount].ToInt();
}

int D_CubismPhysicsJson::GetVertexCount() const
{
    return _json->GetRoot()[STR_Meta][STR_VertexCount].ToInt();
}

// Input
float D_CubismPhysicsJson::GetNormalizationPositionMinimumValue(int physicsSettingIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Normalization][STR_Position][STR_Minimum].ToFloat();
}

float D_CubismPhysicsJson::GetNormalizationPositionMaximumValue(int physicsSettingIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Normalization][STR_Position][STR_Maximum].ToFloat();
}

float D_CubismPhysicsJson::GetNormalizationPositionDefaultValue(int physicsSettingIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Normalization][STR_Position][STR_Default].ToFloat();
}

float D_CubismPhysicsJson::GetNormalizationAngleMinimumValue(int physicsSettingIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Normalization][STR_Angle][STR_Minimum].ToFloat();
}

float D_CubismPhysicsJson::GetNormalizationAngleMaximumValue(int physicsSettingIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Normalization][STR_Angle][STR_Maximum].ToFloat();
}

float D_CubismPhysicsJson::GetNormalizationAngleDefaultValue(int physicsSettingIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Normalization][STR_Angle][STR_Default].ToFloat();
}

int D_CubismPhysicsJson::GetInputCount(int physicsSettingIndex) const
{
    return ( int )(_json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Input].GetVector()->GetSize());
}

float D_CubismPhysicsJson::GetInputWeight(int physicsSettingIndex, int inputIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Input][inputIndex][STR_Weight].ToFloat();
}

bool D_CubismPhysicsJson::GetInputReflect(int physicsSettingIndex, int inputIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Input][inputIndex][STR_Reflect].ToBoolean();
}

const char* D_CubismPhysicsJson::GetInputType(int physicsSettingIndex, int inputIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Input][inputIndex][STR_Type].GetRawString();
}

D_CubismIdHandle D_CubismPhysicsJson::GetInputSourceId(int physicsSettingIndex, int inputIndex) const
{
    return LIVE2DSYS.s_cubismIdManager->GetId(_json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Input][inputIndex][STR_Source][Id].GetRawString());
}

// Output
int D_CubismPhysicsJson::GetOutputCount(int physicsSettingIndex) const
{
    return ( int )(_json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Output].GetVector()->GetSize());
}

int D_CubismPhysicsJson::GetOutputVertexIndex(int physicsSettingIndex, int outputIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Output][outputIndex][STR_VertexIndex].ToInt();
}

float D_CubismPhysicsJson::GetOutputAngleScale(int physicsSettingIndex, int outputIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Output][outputIndex][STR_Scale].ToFloat();
}

float D_CubismPhysicsJson::GetOutputWeight(int physicsSettingIndex, int outputIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Output][outputIndex][STR_Weight].ToFloat();
}

D_CubismIdHandle D_CubismPhysicsJson::GetOutputsDestinationId(int physicsSettingIndex, int outputIndex) const
{
    return LIVE2DSYS.s_cubismIdManager->GetId(_json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Output][outputIndex][STR_Destination][Id].GetRawString());
}

const char* D_CubismPhysicsJson::GetOutputType(int physicsSettingIndex, int outputIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Output][outputIndex][STR_Type].GetRawString();
}

bool D_CubismPhysicsJson::GetOutputReflect(int physicsSettingIndex, int outputIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Output][outputIndex][STR_Reflect].ToBoolean();
}

// Particle
int D_CubismPhysicsJson::GetParticleCount(int physicsSettingIndex) const
{
    return ( int )(_json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Vertices].GetVector()->GetSize());
}

float D_CubismPhysicsJson::GetParticleMobility(int physicsSettingIndex, int vertexIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Vertices][vertexIndex][STR_Mobility].ToFloat();
}

float D_CubismPhysicsJson::GetParticleDelay(int physicsSettingIndex, int vertexIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Vertices][vertexIndex][STR_Delay].ToFloat();
}

float D_CubismPhysicsJson::GetParticleAcceleration(int physicsSettingIndex, int vertexIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Vertices][vertexIndex][STR_Acceleration].ToFloat();
}

float D_CubismPhysicsJson::GetParticleRadius(int physicsSettingIndex, int vertexIndex) const
{
    return _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Vertices][vertexIndex][STR_Radius].ToFloat();
}

D_CubismVector2 D_CubismPhysicsJson::GetParticlePosition(int physicsSettingIndex, int vertexIndex) const
{
    return D_CubismVector2(_json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Vertices][vertexIndex][STR_Position][STR_X].ToFloat(),
        _json->GetRoot()[STR_PhysicsSettings][physicsSettingIndex][STR_Vertices][vertexIndex][STR_Position][STR_Y].ToFloat() );
}

#undef STR_Position				
#undef STR_X					
#undef STR_Y					
#undef STR_Angle				
#undef STR_Type					
#undef STR_Id					

// Meta
#undef STR_Meta					
#undef STR_EffectiveForces		
#undef STR_TotalInputCount		
#undef STR_TotalOutputCount		
#undef STR_PhysicsSettingCount	
#undef STR_Gravity				
#undef STR_Wind					
#undef STR_VertexCount			

// PhysicsSettings
#undef STR_PhysicsSettings		
#undef STR_Normalization		
#undef STR_Minimum				
#undef STR_Maximum				
#undef STR_Default				
#undef STR_Reflect				
#undef STR_Weight				

// Input
#undef STR_Input				
#undef STR_Source				

// Output
#undef STR_Output				
#undef STR_Scale				
#undef STR_VertexIndex			
#undef STR_Destination			

// Particle
#undef STR_Vertices				
#undef STR_Mobility				
#undef STR_Delay				
#undef STR_Radius				
#undef STR_Acceleration





















// physics types tags.
const char* PhysicsTypeTagX = "X";
const char* PhysicsTypeTagY = "Y";
const char* PhysicsTypeTagAngle = "Angle";

// Constant of air resistance.
const float AirResistance = 5.0f;

// Constant of maximum weight of input and output ratio.
const float MaximumWeight = 100.0f;

// Constant of threshold of movement.
const float MovementThreshold = 0.001f;


float GetRangeValue(float min, float max)
{
    float maxValue = D_CubismMath::Max(min, max);
    float minValue = D_CubismMath::Min(min, max);

    return D_CubismMath::AbsF(maxValue - minValue);
}


// Gets sign.
//
// @param  value  Evaluation target value.
//
// @return  Sign of value.
int Sign(float value)
{
    int ret = 0;

    if (value > 0.0f)
    {
        ret = 1;
    }
    else if (value < 0.0f)
    {
        ret = -1;
    }

    return ret;
}


float GetDefaultValue(float min, float max)
{
    const float minValue = D_CubismMath::Min(min, max);
    return minValue + (GetRangeValue(min, max) / 2.0f);
}

float NormalizeParameterValue(
    float value,
    float parameterMinimum,
    float parameterMaximum,
    float /*parameterDefault*/,
    float normalizedMinimum,
    float normalizedMaximum,
    float normalizedDefault,
    int isInverted)
{
    float result = 0.0f;

    const float maxValue = D_CubismMath::Max(parameterMaximum, parameterMinimum);

    if (maxValue < value)
    {
        value = maxValue;
    }

    const float minValue = D_CubismMath::Min(parameterMaximum, parameterMinimum);

    if (minValue > value)
    {
        value = minValue;
    }

    const float minNormValue = D_CubismMath::Min(normalizedMinimum, normalizedMaximum);
    const float maxNormValue = D_CubismMath::Max(normalizedMinimum, normalizedMaximum);
    const float middleNormValue = normalizedDefault;

    const float middleValue = GetDefaultValue(minValue, maxValue);
    const float paramValue = value - middleValue;

    switch (Sign(paramValue))
    {
    case 1: {
        const float nLength = maxNormValue - middleNormValue;
        const float pLength = maxValue - middleValue;
        if (pLength != 0.0f)
        {
            result = paramValue * (nLength / pLength);
            result += middleNormValue;
        }

        break;
    }
    case -1: {
        const float nLength = minNormValue - middleNormValue;
        const float pLength = minValue - middleValue;
        if (pLength != 0.0f)
        {
            result = paramValue * (nLength / pLength);
            result += middleNormValue;
        }

        break;
    }
    case 0: {
        result = middleNormValue;

        break;
    }
    default:{
        break;
    }
    }

    return (isInverted)
        ? result
        : (result * -1.0f);
}

void GetInputTranslationXFromNormalizedParameterValue(D_CubismVector2* targetTranslation, float* /*targetAngle*/, float value,
    float parameterMinimumValue, float parameterMaximumValue,
    float parameterDefaultValue,
    D_CubismPhysicsNormalization* normalizationPosition,
    D_CubismPhysicsNormalization* /*normalizationAngle*/, int isInverted,
    float weight)
{
    targetTranslation->X += NormalizeParameterValue(
        value,
        parameterMinimumValue,
        parameterMaximumValue,
        parameterDefaultValue,
        normalizationPosition->Minimum,
        normalizationPosition->Maximum,
        normalizationPosition->Default,
        isInverted
    ) * weight;
}

void GetInputTranslationYFromNormalizedParameterValue(D_CubismVector2* targetTranslation, float* /*targetAngle*/, float value,
    float parameterMinimumValue, float parameterMaximumValue,
    float parameterDefaultValue,
    D_CubismPhysicsNormalization* normalizationPosition,
    D_CubismPhysicsNormalization* /*normalizationAngle*/,
    int isInverted, float weight)
{
    targetTranslation->Y += NormalizeParameterValue(
        value,
        parameterMinimumValue,
        parameterMaximumValue,
        parameterDefaultValue,
        normalizationPosition->Minimum,
        normalizationPosition->Maximum,
        normalizationPosition->Default,
        isInverted
    ) * weight;
}

void GetInputAngleFromNormalizedParameterValue(D_CubismVector2* /*targetTranslation*/, float* targetAngle, float value,
    float parameterMinimumValue, float parameterMaximumValue,
    float parameterDefaultValue,
    D_CubismPhysicsNormalization* /*normalizationPosition*/,
    D_CubismPhysicsNormalization* normalizationAngle,
    int isInverted, float weight)
{
    *targetAngle += NormalizeParameterValue(
        value,
        parameterMinimumValue,
        parameterMaximumValue,
        parameterDefaultValue,
        normalizationAngle->Minimum,
        normalizationAngle->Maximum,
        normalizationAngle->Default,
        isInverted
    ) * weight;
}

float GetOutputTranslationX(D_CubismVector2 translation, D_CubismPhysicsParticle* /*particles*/, int /*particleIndex*/,
    int isInverted, D_CubismVector2 /*parentGravity*/)
{
    float outputValue = translation.X;

    if (isInverted)
    {
        outputValue *= -1.0f;
    }

    return outputValue;
}

float GetOutputTranslationY(D_CubismVector2 translation, D_CubismPhysicsParticle* /*particles*/, int /*particleIndex*/,
    int isInverted, D_CubismVector2 /*parentGravity*/)
{
    float outputValue = translation.Y;

    if (isInverted)
    {
        outputValue *= -1.0f;
    }

    return outputValue;
}

float GetOutputAngle(D_CubismVector2 translation, D_CubismPhysicsParticle* particles, int particleIndex, int isInverted,
    D_CubismVector2 parentGravity)
{
    float outputValue;

    if (particleIndex >= 2)
    {
        parentGravity.X = particles[particleIndex - 1].Position.X - particles[particleIndex - 2].Position.X;
        parentGravity.Y = particles[particleIndex - 1].Position.Y - particles[particleIndex - 2].Position.Y;
    }
    else
    {
        parentGravity.X *= -1.0f;
        parentGravity.Y *= -1.0f;
    }

    outputValue = D_CubismMath::DirectionToRadian(parentGravity, translation);

    if (isInverted)
    {
        outputValue *= -1.0f;
    }

    return outputValue;
}

float GetOutputScaleTranslationX(D_CubismVector2 translationScale, float /*angleScale*/)
{
    return translationScale.X;
}

float GetOutputScaleTranslationY(D_CubismVector2 translationScale, float /*angleScale*/)
{
    return translationScale.Y;
}

float GetOutputScaleAngle(D_CubismVector2 /*translationScale*/, float angleScale)
{
    return angleScale;
}

// Updates particles.
//
// @param  strand            Target array of particle.
// @param  strandCount       Count of particle.
// @param  totalTranslation  Total translation value.
// @param  totalAngle        Total angle.
// @param  windDirection              Direction of wind.
// @param  thresholdValue    Threshold of movement.
// @param  deltaTimeSeconds  Delta time.
// @param  airResistance     Air resistance.
void UpdateParticles(D_CubismPhysicsParticle* strand, int strandCount, D_CubismVector2 totalTranslation, float totalAngle,
    D_CubismVector2 windDirection, float thresholdValue, float deltaTimeSeconds, float airResistance)
{
    int i;
    float totalRadian;
    float delay;
    float radian;
    D_CubismVector2 currentGravity;
    D_CubismVector2 direction;
    D_CubismVector2 velocity;
    D_CubismVector2 force;
    D_CubismVector2 newDirection;

    strand[0].Position = totalTranslation;

    totalRadian = D_CubismMath::DegreesToRadian(totalAngle);
    currentGravity = D_CubismMath::RadianToDirection(totalRadian);
    currentGravity.Normalize();

    for (i = 1; i < strandCount; ++i)
    {
        strand[i].Force = (currentGravity * strand[i].Acceleration) + windDirection;

        strand[i].LastPosition = strand[i].Position;

        delay = strand[i].Delay * deltaTimeSeconds * 30.0f;

        direction.X = strand[i].Position.X - strand[i - 1].Position.X;
        direction.Y = strand[i].Position.Y - strand[i - 1].Position.Y;

        radian = D_CubismMath::DirectionToRadian(strand[i].LastGravity, currentGravity) / airResistance;

        direction.X = ((D_CubismMath::CosF(radian) * direction.X) - (direction.Y * D_CubismMath::SinF(radian)));
        direction.Y = ((D_CubismMath::SinF(radian) * direction.X) + (direction.Y * D_CubismMath::CosF(radian)));

        strand[i].Position = strand[i - 1].Position + direction;

        velocity.X = strand[i].Velocity.X * delay;
        velocity.Y = strand[i].Velocity.Y * delay;
        force = strand[i].Force * delay * delay;

        strand[i].Position = strand[i].Position + velocity + force;

        newDirection = strand[i].Position - strand[i - 1].Position;

        newDirection.Normalize();

        strand[i].Position = strand[i - 1].Position + (newDirection * strand[i].Radius);

        if (D_CubismMath::AbsF(strand[i].Position.X) < thresholdValue)
        {
            strand[i].Position.X = 0.0f;
        }

        if (delay != 0.0f)
        {
            strand[i].Velocity.X = strand[i].Position.X - strand[i].LastPosition.X;
            strand[i].Velocity.Y = strand[i].Position.Y - strand[i].LastPosition.Y;
            strand[i].Velocity /= delay;
            strand[i].Velocity *= strand[i].Mobility;
        }

        strand[i].Force = D_CubismVector2( 0.0f, 0.0f );
        strand[i].LastGravity = currentGravity;
    }
}

// Updates output parameter value.
//
// @param  parameterValue         Target parameter value.
// @param  parameterValueMinimum  Minimum of parameter value.
// @param  parameterValueMaximum  Maximum of parameter value.
// @param  translation            Translation value.
void UpdateOutputParameterValue(float* parameterValue, float parameterValueMinimum, float parameterValueMaximum,
    float translation, D_CubismPhysicsOutput* output)
{
    float outputScale;
    float value;
    float weight;

    outputScale = output->GetScale(output->TranslationScale, output->AngleScale);

    value = translation * outputScale;

    if (value < parameterValueMinimum)
    {
        if (value < output->ValueBelowMinimum)
        {
            output->ValueBelowMinimum = value;
        }

        value = parameterValueMinimum;
    }
    else if (value > parameterValueMaximum)
    {
        if (value > output->ValueExceededMaximum)
        {
            output->ValueExceededMaximum = value;
        }

        value = parameterValueMaximum;
    }

    weight = (output->Weight / MaximumWeight);

    if (weight >= 1.0f)
    {
        *parameterValue = value;
    }
    else
    {
        value = (*parameterValue * (1.0f - weight)) + (value * weight);
        *parameterValue = value;
    }
}

D_CubismPhysics::D_CubismPhysics()
    : _physicsRig(NULL)
{
    // set default options.
    _options.Gravity.Y = -1.0f;
    _options.Gravity.X = 0;
    _options.Wind.X = 0;
    _options.Wind.Y = 0;
}

D_CubismPhysics::~D_CubismPhysics()
{
    D_CSM_DELETE(_physicsRig);
}

// Initializes physics.
//
// @param  physics  Target rig.
void D_CubismPhysics::Initialize()
{
    D_CubismPhysicsParticle* strand;
    D_CubismPhysicsSubRig* currentSetting;
    int i, settingIndex;
    D_CubismVector2 radius;

    for (settingIndex = 0; settingIndex < _physicsRig->SubRigCount; ++settingIndex)
    {
        currentSetting = &_physicsRig->Settings[settingIndex];
        strand = &_physicsRig->Particles[currentSetting->BaseParticleIndex];

        // Initialize the top of particle.
        strand[0].InitialPosition = D_CubismVector2(0.0f, 0.0f);
        strand[0].LastPosition = strand[0].InitialPosition;
        strand[0].LastGravity = D_CubismVector2(0.0f, -1.0f);
        strand[0].LastGravity.Y *= -1.0f;
        strand[0].Velocity = D_CubismVector2(0.0f, 0.0f);
        strand[0].Force = D_CubismVector2(0.0f, 0.0f);

        // Initialize paritcles.
        for (i = 1; i < currentSetting->ParticleCount; ++i)
        {
            radius = D_CubismVector2(0.0f, 0.0f);
            radius.Y = strand[i].Radius;
            strand[i].InitialPosition = strand[i - 1].InitialPosition + radius;
            strand[i].Position = strand[i].InitialPosition;
            strand[i].LastPosition = strand[i].InitialPosition;
            strand[i].LastGravity = D_CubismVector2(0.0f, -1.0f);
            strand[i].LastGravity.Y *= -1.0f;
            strand[i].Velocity = D_CubismVector2(0.0f, 0.0f);
            strand[i].Force = D_CubismVector2(0.0f, 0.0f);
        }
    }
}

D_CubismPhysics* D_CubismPhysics::Create(const BYTE* buffer, size_t size)
{
    D_CubismPhysics* ret = D_CSM_NEW D_CubismPhysics();

    ret->Parse(buffer, size);
    ret->_physicsRig->Gravity.Y = 0;

    return ret;
}

void D_CubismPhysics::Delete(D_CubismPhysics* physics)
{
    D_CSM_DELETE_SELF(D_CubismPhysics, physics);
}

void D_CubismPhysics::Parse( const BYTE* physicsJson, size_t size )
{
	DWORD i ;
	int j ;
	_physicsRig = D_CSM_NEW D_CubismPhysicsRig;

	D_CubismPhysicsJson* json = D_CSM_NEW D_CubismPhysicsJson( physicsJson, size );

	_physicsRig->Gravity = json->GetGravity();
	_physicsRig->Wind = json->GetWind();
	_physicsRig->SubRigCount = json->GetSubRigCount();

	_physicsRig->Settings.UpdateSize( _physicsRig->SubRigCount, D_CubismPhysicsSubRig(), true );
	_physicsRig->Inputs.UpdateSize( json->GetTotalInputCount(), D_CubismPhysicsInput(), true );
	_physicsRig->Outputs.UpdateSize( json->GetTotalOutputCount(), D_CubismPhysicsOutput(), true );
	_physicsRig->Particles.UpdateSize( json->GetVertexCount(), D_CubismPhysicsParticle(), true );

	int inputIndex = 0, outputIndex = 0, particleIndex = 0;
	for( i = 0; i < _physicsRig->Settings.GetSize(); ++i )
	{
		_physicsRig->Settings[ i ].NormalizationPosition.Minimum = json->GetNormalizationPositionMinimumValue( i );
		_physicsRig->Settings[ i ].NormalizationPosition.Maximum = json->GetNormalizationPositionMaximumValue( i );
		_physicsRig->Settings[ i ].NormalizationPosition.Default = json->GetNormalizationPositionDefaultValue( i );

		_physicsRig->Settings[ i ].NormalizationAngle.Minimum = json->GetNormalizationAngleMinimumValue( i );
		_physicsRig->Settings[ i ].NormalizationAngle.Maximum = json->GetNormalizationAngleMaximumValue( i );
		_physicsRig->Settings[ i ].NormalizationAngle.Default = json->GetNormalizationAngleDefaultValue( i );

		// Input
		_physicsRig->Settings[ i ].InputCount = json->GetInputCount( i );
		_physicsRig->Settings[ i ].BaseInputIndex = inputIndex;
		for( j = 0; j < _physicsRig->Settings[ i ].InputCount; ++j )
		{
			_physicsRig->Inputs[ inputIndex + j ].SourceParameterIndex = -1;
			_physicsRig->Inputs[ inputIndex + j ].Weight = json->GetInputWeight( i, j );
			_physicsRig->Inputs[ inputIndex + j ].Reflect = json->GetInputReflect( i, j );

			if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, json->GetInputType( i, j ), PhysicsTypeTagX ) == 0 )
			{
				_physicsRig->Inputs[ inputIndex + j ].Type = D_CubismPhysicsSource_X;
				_physicsRig->Inputs[ inputIndex + j ].GetNormalizedParameterValue = GetInputTranslationXFromNormalizedParameterValue;
			}
			else if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, json->GetInputType( i, j ), PhysicsTypeTagY ) == 0 )
			{
				_physicsRig->Inputs[ inputIndex + j ].Type = D_CubismPhysicsSource_Y;
				_physicsRig->Inputs[ inputIndex + j ].GetNormalizedParameterValue = GetInputTranslationYFromNormalizedParameterValue;
			}
			else if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, json->GetInputType( i, j ), PhysicsTypeTagAngle ) == 0 )
			{
				_physicsRig->Inputs[ inputIndex + j ].Type = D_CubismPhysicsSource_Angle;
				_physicsRig->Inputs[ inputIndex + j ].GetNormalizedParameterValue = GetInputAngleFromNormalizedParameterValue;
			}

			_physicsRig->Inputs[ inputIndex + j ].Source.TargetType = D_CubismPhysicsTargetType_Parameter;
			_physicsRig->Inputs[ inputIndex + j ].Source.Id = json->GetInputSourceId( i, j );
		}
		inputIndex += _physicsRig->Settings[ i ].InputCount;

		// Output
		_physicsRig->Settings[ i ].OutputCount = json->GetOutputCount( i );
		_physicsRig->Settings[ i ].BaseOutputIndex = outputIndex;
		for( j = 0; j < _physicsRig->Settings[ i ].OutputCount; ++j )
		{
			_physicsRig->Outputs[ outputIndex + j ].DestinationParameterIndex = -1;
			_physicsRig->Outputs[ outputIndex + j ].VertexIndex = json->GetOutputVertexIndex( i, j );
			_physicsRig->Outputs[ outputIndex + j ].AngleScale = json->GetOutputAngleScale( i, j );
			_physicsRig->Outputs[ outputIndex + j ].Weight = json->GetOutputWeight( i, j );
			_physicsRig->Outputs[ outputIndex + j ].Destination.TargetType = D_CubismPhysicsTargetType_Parameter;

			_physicsRig->Outputs[ outputIndex + j ].Destination.Id = json->GetOutputsDestinationId( i, j );
			if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, json->GetOutputType( i, j ), PhysicsTypeTagX ) == 0 )
			{
				_physicsRig->Outputs[ outputIndex + j ].Type = D_CubismPhysicsSource_X;
				_physicsRig->Outputs[ outputIndex + j ].GetValue = GetOutputTranslationX;
				_physicsRig->Outputs[ outputIndex + j ].GetScale = GetOutputScaleTranslationX;
			}
			else if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, json->GetOutputType( i, j ), PhysicsTypeTagY ) == 0 )
			{
				_physicsRig->Outputs[ outputIndex + j ].Type = D_CubismPhysicsSource_Y;
				_physicsRig->Outputs[ outputIndex + j ].GetValue = GetOutputTranslationY;
				_physicsRig->Outputs[ outputIndex + j ].GetScale = GetOutputScaleTranslationY;
			}
			else if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, json->GetOutputType( i, j ), PhysicsTypeTagAngle ) == 0 )
			{
				_physicsRig->Outputs[ outputIndex + j ].Type = D_CubismPhysicsSource_Angle;
				_physicsRig->Outputs[ outputIndex + j ].GetValue = GetOutputAngle;
				_physicsRig->Outputs[ outputIndex + j ].GetScale = GetOutputScaleAngle;
			}

			_physicsRig->Outputs[ outputIndex + j ].Reflect = json->GetOutputReflect( i, j );
		}
		outputIndex += _physicsRig->Settings[ i ].OutputCount;

		// Particle
		_physicsRig->Settings[ i ].ParticleCount = json->GetParticleCount( i );
		_physicsRig->Settings[ i ].BaseParticleIndex = particleIndex;
		for( j = 0; j < _physicsRig->Settings[ i ].ParticleCount; ++j )
		{
			_physicsRig->Particles[ particleIndex + j ].Mobility = json->GetParticleMobility( i, j );
			_physicsRig->Particles[ particleIndex + j ].Delay = json->GetParticleDelay( i, j );
			_physicsRig->Particles[ particleIndex + j ].Acceleration = json->GetParticleAcceleration( i, j );
			_physicsRig->Particles[ particleIndex + j ].Radius = json->GetParticleRadius( i, j );
			_physicsRig->Particles[ particleIndex + j ].Position = json->GetParticlePosition( i, j );
		}

		particleIndex += _physicsRig->Settings[ i ].ParticleCount;
	}

	Initialize();

	D_CSM_DELETE( json );
}

void D_CubismPhysics::Evaluate(D_CubismModel* model, float deltaTimeSeconds)
{
    float totalAngle;
    float weight;
    float radAngle;
    float outputValue;
    D_CubismVector2 totalTranslation;
    int i, settingIndex, particleIndex;
    D_CubismPhysicsSubRig* currentSetting;
    D_CubismPhysicsInput* currentInput;
    D_CubismPhysicsOutput* currentOutput;
    D_CubismPhysicsParticle* currentParticles;

    float* parameterValue;
    const float* parameterMaximumValue;
    const float* parameterMinimumValue;
    const float* parameterDefaultValue;

    parameterValue = CALL_csmGetParameterValues( ( model->GetModel() ) );
    parameterMaximumValue = CALL_csmGetParameterMaximumValues( ( model->GetModel() ) );
    parameterMinimumValue = CALL_csmGetParameterMinimumValues( ( model->GetModel() ) );
    parameterDefaultValue = CALL_csmGetParameterDefaultValues( ( model->GetModel() ) );

    for (settingIndex = 0; settingIndex < _physicsRig->SubRigCount; ++settingIndex)
    {
        totalAngle = 0.0f;
        totalTranslation.X = 0.0f;
        totalTranslation.Y = 0.0f;
        currentSetting = &_physicsRig->Settings[settingIndex];
        currentInput = &_physicsRig->Inputs[currentSetting->BaseInputIndex];
        currentOutput = &_physicsRig->Outputs[currentSetting->BaseOutputIndex];
        currentParticles = &_physicsRig->Particles[currentSetting->BaseParticleIndex];

        // Load input parameters.
        for (i = 0; i < currentSetting->InputCount; ++i)
        {
            weight = currentInput[i].Weight / MaximumWeight;

            if (currentInput[i].SourceParameterIndex == -1)
            {
                currentInput[i].SourceParameterIndex = model->GetParameterIndex(currentInput[i].Source.Id);
            }

            currentInput[i].GetNormalizedParameterValue(
                &totalTranslation,
                &totalAngle,
                parameterValue[currentInput[i].SourceParameterIndex],
                parameterMinimumValue[currentInput[i].SourceParameterIndex],
                parameterMaximumValue[currentInput[i].SourceParameterIndex],
                parameterDefaultValue[currentInput[i].SourceParameterIndex],
                &currentSetting->NormalizationPosition,
                &currentSetting->NormalizationAngle,
                currentInput->Reflect,
                weight
            );
        }

        radAngle = D_CubismMath::DegreesToRadian(-totalAngle);

        totalTranslation.X = (totalTranslation.X * D_CubismMath::CosF(radAngle) - totalTranslation.Y * D_CubismMath::SinF(radAngle));
        totalTranslation.Y = (totalTranslation.X * D_CubismMath::SinF(radAngle) + totalTranslation.Y * D_CubismMath::CosF(radAngle));

        // Calculate particles position.
        UpdateParticles(
            currentParticles,
            currentSetting->ParticleCount,
            totalTranslation,
            totalAngle,
            _options.Wind,
            MovementThreshold * currentSetting->NormalizationPosition.Maximum,
            deltaTimeSeconds,
            AirResistance
        );

        // Update output parameters.
        for (i = 0; i < currentSetting->OutputCount; ++i)
        {
            particleIndex = currentOutput[i].VertexIndex;

            if (particleIndex < 1 || particleIndex >= currentSetting->ParticleCount)
            {
                break;
            }

            if (currentOutput[i].DestinationParameterIndex == -1)
            {
                currentOutput[i].DestinationParameterIndex = model->GetParameterIndex(currentOutput[i].Destination.Id);
            }

            D_CubismVector2 translation;
            translation.X = currentParticles[particleIndex].Position.X - currentParticles[particleIndex - 1].Position.X;
            translation.Y = currentParticles[particleIndex].Position.Y - currentParticles[particleIndex - 1].Position.Y;

            outputValue = currentOutput[i].GetValue(
                translation,
                currentParticles,
                particleIndex,
                currentOutput[i].Reflect,
                _options.Gravity
            );

            UpdateOutputParameterValue(
                &parameterValue[currentOutput[i].DestinationParameterIndex],
                parameterMinimumValue[currentOutput[i].DestinationParameterIndex],
                parameterMaximumValue[currentOutput[i].DestinationParameterIndex],
                outputValue,
                &currentOutput[i]);
        }
    }
}

void D_CubismPhysics::SetOptions(const Options& options)
{
    _options = options;
}

const D_CubismPhysics::Options& D_CubismPhysics::GetOptions() const
{
    return _options;
}


















#define STR_Meta					"Meta"
#define STR_UserDataCount			"UserDataCount"
#define STR_TotalUserDataSize		"TotalUserDataSize"
#define STR_UserData				"UserData"
#define STR_Target					"Target"
#define STR_Id						"Id"
#define STR_Value					"Value"

D_CubismModelUserDataJson::D_CubismModelUserDataJson(const BYTE* buffer, size_t size)
{
    _json = D_CubismJson::Create(buffer, size);
}

D_CubismModelUserDataJson::~D_CubismModelUserDataJson() 
{
    D_CubismJson::Delete(_json);
}
    
int D_CubismModelUserDataJson::GetUserDataCount() const
{
    return _json->GetRoot()[STR_Meta][STR_UserDataCount].ToInt();
}

int D_CubismModelUserDataJson::GetTotalUserDataSize() const
{
    return _json->GetRoot()[STR_Meta][STR_TotalUserDataSize].ToInt();
}

D_csmString D_CubismModelUserDataJson::GetUserDataTargetType(const int i) const
{
    return  _json->GetRoot()[STR_UserData][i][STR_Target].GetRawString();
}

D_CubismIdHandle D_CubismModelUserDataJson::GetUserDataId(const int i) const
{
    return LIVE2DSYS.s_cubismIdManager->GetId(_json->GetRoot()[STR_UserData][i][STR_Id].GetRawString());
}

const char* D_CubismModelUserDataJson::GetUserDataValue(const int i) const
{
    return _json->GetRoot()[STR_UserData][i][STR_Value].GetRawString();
}

#undef STR_Meta
#undef STR_UserDataCount
#undef STR_TotalUserDataSize
#undef STR_UserData
#undef STR_Target
#undef STR_Id
#undef STR_Value




















const char*  ArtMesh = "ArtMesh";

D_CubismModelUserData::~D_CubismModelUserData()
{
    for (DWORD i = 0;i < _userDataNodes.GetSize(); ++i)
    {
        D_CSM_DELETE((CubismModelUserDataNode*)(_userDataNodes[i]));
    }
}

const D_csmVector<const D_CubismModelUserData::CubismModelUserDataNode*>& D_CubismModelUserData::GetArtMeshUserDatas() const
{
    return _artMeshUserDataNodes;
}

D_CubismModelUserData* D_CubismModelUserData::Create(const BYTE* buffer, const size_t size)
{
    D_CubismModelUserData* ret = D_CSM_NEW D_CubismModelUserData();

    ret->ParseUserData(buffer, size);

    return ret;
}

void D_CubismModelUserData::Delete(D_CubismModelUserData* modelUserData)
{
    D_CSM_DELETE_SELF(D_CubismModelUserData, modelUserData);
}

void D_CubismModelUserData::ParseUserData(const BYTE* buffer, const size_t size)
{
    D_CubismModelUserDataJson* json = D_CSM_NEW D_CubismModelUserDataJson(buffer, size);

    const D_CubismIdHandle typeOfArtMesh = LIVE2DSYS.s_cubismIdManager->GetId(ArtMesh);

    const DWORD nodeCount = json->GetUserDataCount();

    for (DWORD i = 0; i < nodeCount; i++)
    {
        CubismModelUserDataNode*    addNode = D_CSM_NEW CubismModelUserDataNode();
        addNode->TargetId = json->GetUserDataId(i);
        addNode->TargetType = LIVE2DSYS.s_cubismIdManager->GetId(json->GetUserDataTargetType(i));
        addNode->Value = json->GetUserDataValue(i);
        _userDataNodes.PushBack(addNode);

        if (addNode->TargetType == typeOfArtMesh)
        {
            _artMeshUserDataNodes.PushBack(addNode);
        }
    }

    D_CSM_DELETE(json);
}



















void D_CubismRenderer::Delete(D_CubismRenderer* renderer)
{
    D_CSM_DELETE_SELF(D_CubismRenderer, renderer);
}

D_CubismRenderer::D_CubismRenderer()
    : _isCulling(false)
    , _isPremultipliedAlpha(false)
    , _anisotropy(0.0f)
    , _model(NULL)
    , _useHighPrecisionMask(false)
{
    //�P�ʍs��ɏ�����
    _mvpMatrix4x4.LoadIdentity();
}

D_CubismRenderer::~D_CubismRenderer()
{}

void D_CubismRenderer::Initialize( D_CubismModel* model, int /* ASyncThread */ )
{
	_model = model;
}

void D_CubismRenderer::DrawModel()
{
    if (GetModel() == NULL) return;

    /**
     * DoDrawModel�̕`��O�ƕ`���Ɉȉ��̊֐����Ă�ł��������B
     * �ESaveProfile();
     * �ERestoreProfile();
     * ����̓����_���̕`��ݒ��ۑ��E���A�����邱�ƂŁA
     * ���f���`�撼�O�̏�Ԃɖ߂����߂̏����ł��B
     */

    SaveProfile();

    DoDrawModel();

    RestoreProfile();
}

void D_CubismRenderer::SetMvpMatrix(D_CubismMatrix44* matrix4x4)
{
    _mvpMatrix4x4.SetMatrix(matrix4x4->GetArray());
}

D_CubismMatrix44 D_CubismRenderer::GetMvpMatrix() const
{
    return _mvpMatrix4x4;
}

void D_CubismRenderer::SetModelColor(float red, float green, float blue, float alpha)
{
    if (red < 0.0f) red = 0.0f;
    else if (red > 1.0f) red = 1.0f;

    if (green < 0.0f) green = 0.0f;
    else if (green > 1.0f) green = 1.0f;

    if (blue < 0.0f) blue = 0.0f;
    else if (blue > 1.0f) blue = 1.0f;

    if (alpha < 0.0f) alpha = 0.0f;
    else if (alpha > 1.0f) alpha = 1.0f;

    _modelColor.R = red;
    _modelColor.G = green;
    _modelColor.B = blue;
    _modelColor.A = alpha;
}

D_CubismRenderer::CubismTextureColor D_CubismRenderer::GetModelColor() const
{
    return  _modelColor;
}

void D_CubismRenderer::IsPremultipliedAlpha(bool enable)
{
    _isPremultipliedAlpha = enable;
}

bool D_CubismRenderer::IsPremultipliedAlpha() const
{
    return _isPremultipliedAlpha;
}

void D_CubismRenderer::IsCulling(bool culling)
{
    _isCulling = culling;
}

bool D_CubismRenderer::IsCulling() const
{
    return  _isCulling;
}

void D_CubismRenderer::SetAnisotropy(float n)
{
    _anisotropy = n;
}

float D_CubismRenderer::GetAnisotropy() const
{
    return _anisotropy;
}

D_CubismModel* D_CubismRenderer::GetModel() const
{
    return _model;
}

void D_CubismRenderer::UseHighPrecisionMask(bool high)
{
    _useHighPrecisionMask = high;
}

bool D_CubismRenderer::IsUsingHighPrecisionMask()
{
    return _useHighPrecisionMask;
}




















MATRIX D_ConvertToD3DX(D_CubismMatrix44& mtx)
{
    MATRIX retMtx;
    retMtx.m[0][0] = mtx.GetArray()[ 0];
    retMtx.m[0][1] = mtx.GetArray()[ 1];
    retMtx.m[0][2] = mtx.GetArray()[ 2];
    retMtx.m[0][3] = mtx.GetArray()[ 3];

    retMtx.m[1][0] = mtx.GetArray()[ 4];
    retMtx.m[1][1] = mtx.GetArray()[ 5];
    retMtx.m[1][2] = mtx.GetArray()[ 6];
    retMtx.m[1][3] = mtx.GetArray()[ 7];

    retMtx.m[2][0] = mtx.GetArray()[ 8];
    retMtx.m[2][1] = mtx.GetArray()[ 9];
    retMtx.m[2][2] = mtx.GetArray()[10];
    retMtx.m[2][3] = mtx.GetArray()[11];

    retMtx.m[3][0] = mtx.GetArray()[12];
    retMtx.m[3][1] = mtx.GetArray()[13];
    retMtx.m[3][2] = mtx.GetArray()[14];
    retMtx.m[3][3] = mtx.GetArray()[15];

    return retMtx;
}

const int ColorChannelCount = 4;   ///< ��������1�`�����l���̏ꍇ��1�ARGB�����̏ꍇ��3�A�A���t�@���܂߂�ꍇ��4

D_CubismClippingManager_DxLib::D_CubismClippingManager_DxLib()
    : _colorBuffer(NULL)
    , _currentFrameNo(0)
    , _clippingMaskBufferSize(256)
{
    D_CubismRenderer::CubismTextureColor* tmp = NULL;
    tmp = D_CSM_NEW D_CubismRenderer::CubismTextureColor();
    tmp->R = 1.0f;
    tmp->G = 0.0f;
    tmp->B = 0.0f;
    tmp->A = 0.0f;
    _channelColors.PushBack(tmp);
    tmp = D_CSM_NEW D_CubismRenderer::CubismTextureColor();
    tmp->R = 0.0f;
    tmp->G = 1.0f;
    tmp->B = 0.0f;
    tmp->A = 0.0f;
    _channelColors.PushBack(tmp);
    tmp = D_CSM_NEW D_CubismRenderer::CubismTextureColor();
    tmp->R = 0.0f;
    tmp->G = 0.0f;
    tmp->B = 1.0f;
    tmp->A = 0.0f;
    _channelColors.PushBack(tmp);
    tmp = D_CSM_NEW D_CubismRenderer::CubismTextureColor();
    tmp->R = 0.0f;
    tmp->G = 0.0f;
    tmp->B = 0.0f;
    tmp->A = 1.0f;
    _channelColors.PushBack(tmp);

}

D_CubismClippingManager_DxLib::~D_CubismClippingManager_DxLib()
{
	DWORD i ;

	for( i = 0; i < _clippingContextListForMask.GetSize(); i++ )
	{
		if( _clippingContextListForMask[ i ] ) D_CSM_DELETE_SELF( D_CubismClippingContext, _clippingContextListForMask[ i ] );
		_clippingContextListForMask[ i ] = NULL;
	}

	// _clippingContextListForDraw��_clippingContextListForMask�ɂ���C���X�^���X���w���Ă���B��L�̏����ɂ��v�f���Ƃ�DELETE�͕s�v�B
	for( i = 0; i < _clippingContextListForDraw.GetSize(); i++ )
	{
		_clippingContextListForDraw[ i ] = NULL;
	}

	for( i = 0; i < _channelColors.GetSize(); i++ )
	{
		if( _channelColors[ i ] ) D_CSM_DELETE( _channelColors[ i ] );
		_channelColors[ i ] = NULL;
	}
}

void D_CubismClippingManager_DxLib::Initialize(D_CubismModel& /*model*/, int drawableCount, const int** drawableMasks, const int* drawableMaskCounts)
{
    //�N���b�s���O�}�X�N���g���`��I�u�W�F�N�g��S�ēo�^����
    //�N���b�s���O�}�X�N�́A�ʏ퐔���x�Ɍ��肵�Ďg�����̂Ƃ���
    for (int i = 0; i < drawableCount; i++)
    {
        if (drawableMaskCounts[i] <= 0)
        {
            //�N���b�s���O�}�X�N���g�p����Ă��Ȃ��A�[�g���b�V���i�����̏ꍇ�g�p���Ȃ��j
            _clippingContextListForDraw.PushBack(NULL);
            continue;
        }

        // ���ɂ���ClipContext�Ɠ������`�F�b�N����
        D_CubismClippingContext* cc = FindSameClip(drawableMasks[i], drawableMaskCounts[i]);
        if (cc == NULL)
        {
            // ����̃}�X�N�����݂��Ă��Ȃ��ꍇ�͐�������
            cc = D_CSM_NEW D_CubismClippingContext(this, drawableMasks[i], drawableMaskCounts[i]);
            _clippingContextListForMask.PushBack(cc);
        }

        cc->AddClippedDrawable(i);

        _clippingContextListForDraw.PushBack(cc);
    }
}

D_CubismClippingContext* D_CubismClippingManager_DxLib::FindSameClip(const int* drawableMasks, int drawableMaskCounts) const
{
    // �쐬�ς�ClippingContext�ƈ�v���邩�m�F
    for (DWORD i = 0; i < _clippingContextListForMask.GetSize(); i++)
    {
        D_CubismClippingContext* cc = _clippingContextListForMask[i];
        const int count = cc->_clippingIdCount;
        if (count != drawableMaskCounts) continue; //�����Ⴄ�ꍇ�͕ʕ�
        int samecount = 0;

        // ����ID�������m�F�B�z��̐��������Ȃ̂ŁA��v�������������Ȃ瓯���������Ƃ���B
        for (int j = 0; j < count; j++)
        {
            const int clipId = cc->_clippingIdList[j];
            for (int k = 0; k < count; k++)
            {
                if (drawableMasks[k] == clipId)
                {
                    samecount++;
                    break;
                }
            }
        }
        if (samecount == count)
        {
            return cc;
        }
    }
    return NULL; //������Ȃ�����
}

void D_CubismClippingManager_DxLib::SetupClippingContext( D_CubismModel& model, D_CubismRenderer_DxLib* renderer, D_CubismOffscreenFrame_DxLib& useTarget )
{
	_currentFrameNo++;

	// �S�ẴN���b�s���O��p�ӂ���
	// �����N���b�v�i�����̏ꍇ�͂܂Ƃ߂ĂP�̃N���b�v�j���g���ꍇ�͂P�x�����ݒ肷��
	int usingClipCount = 0;
	for( DWORD clipIndex = 0; clipIndex < _clippingContextListForMask.GetSize(); clipIndex++ )
	{
		// �P�̃N���b�s���O�}�X�N�Ɋւ���
		D_CubismClippingContext* cc = _clippingContextListForMask[ clipIndex ];

		// ���̃N���b�v�𗘗p����`��I�u�W�F�N�g�Q�S�̂��͂ދ�`���v�Z
		CalcClippedDrawTotalBounds( model, cc );

		if( cc->_isUsing )
		{
			usingClipCount++; //�g�p���Ƃ��ăJ�E���g
		}
	}

	// �}�X�N�쐬����
	if( usingClipCount > 0 )
	{
		if( !renderer->IsUsingHighPrecisionMask() )
		{
			// �r���[�|�[�g�͑ޔ��ς� 
			// ��������FrameBuffer�Ɠ����T�C�Y�Ńr���[�|�[�g��ݒ�
			D_CubismRenderer_DxLib::GetRenderStateManager()->SetViewport(
				0,
				0,
				( float )( _clippingMaskBufferSize ),
				( float )( _clippingMaskBufferSize ),
				0.0f, 1.0f );

			useTarget.BeginDraw();
			// 1�������i�`����Ȃ��j�̈�A0���L���i�`�����j�̈�B�i�V�F�[�_�� Cd*Cs��0�ɋ߂��l�������ă}�X�N�����B1��������Ɖ����N����Ȃ��j
			useTarget.Clear( 1.0f, 1.0f, 1.0f, 1.0f );
		}

		// �e�}�X�N�̃��C�A�E�g�����肵�Ă���
		SetupLayoutBounds( renderer->IsUsingHighPrecisionMask() ? 0 : usingClipCount );

		// ���ۂɃ}�X�N�𐶐�����
		// �S�Ẵ}�X�N���ǂ̗l�Ƀ��C�A�E�g���ĕ`���������肵�AClipContext , ClippedDrawContext �ɋL������
		for( DWORD clipIndex = 0; clipIndex < _clippingContextListForMask.GetSize(); clipIndex++ )
		{
			// --- ���ۂɂP�̃}�X�N��`�� ---
			D_CubismClippingContext* clipContext = _clippingContextListForMask[ clipIndex ];
			D_csmRectF* allClippedDrawRect = clipContext->_allClippedDrawRect; //���̃}�X�N���g���A�S�Ă̕`��I�u�W�F�N�g�̘_�����W��̈͂݋�`
			D_csmRectF* layoutBoundsOnTex01 = clipContext->_layoutBounds; //���̒��Ƀ}�X�N�����߂�

			// ���f�����W��̋�`���A�K�X�}�[�W����t���Ďg��
			const float MARGIN = 0.05f;
			_tmpBoundsOnModel.SetRect( allClippedDrawRect );
			_tmpBoundsOnModel.Expand( allClippedDrawRect->Width * MARGIN, allClippedDrawRect->Height * MARGIN );
			//########## �{���͊��蓖�Ă�ꂽ�̈�̑S�̂��g�킸�K�v�Œ���̃T�C�Y���悢

			// �V�F�[�_�p�̌v�Z�������߂�B��]���l�����Ȃ��ꍇ�͈ȉ��̂Ƃ���
			// movePeriod' = movePeriod * scaleX + offX [[ movePeriod' = (movePeriod - tmpBoundsOnModel.movePeriod)*scale + layoutBoundsOnTex01.movePeriod ]]
			const float scaleX = layoutBoundsOnTex01->Width / _tmpBoundsOnModel.Width;
			const float scaleY = layoutBoundsOnTex01->Height / _tmpBoundsOnModel.Height;

			// �}�X�N�������Ɏg���s������߂�
			{
				// �V�F�[�_�ɓn���s������߂� <<<<<<<<<<<<<<<<<<<<<<<< �v�œK���i�t���Ɍv�Z����΃V���v���ɂł���j
				_tmpMatrix.LoadIdentity();
				{
					// Layout0..1 �� -1..1�ɕϊ�
					_tmpMatrix.TranslateRelative( -1.0f, -1.0f );
					_tmpMatrix.ScaleRelative( 2.0f, 2.0f );
				}
				{
					// view to Layout0..1
					_tmpMatrix.TranslateRelative( layoutBoundsOnTex01->X, layoutBoundsOnTex01->Y ); //new = [translate]
					_tmpMatrix.ScaleRelative( scaleX, scaleY ); //new = [translate][scale]
					_tmpMatrix.TranslateRelative( -_tmpBoundsOnModel.X, -_tmpBoundsOnModel.Y );
					//new = [translate][scale][translate]
				}
				// tmpMatrixForMask ���v�Z����
				_tmpMatrixForMask.SetMatrix( _tmpMatrix.GetArray() );
			}

			//--------- draw���� mask �Q�Ɨp�s����v�Z
			{
				// �V�F�[�_�ɓn���s������߂� <<<<<<<<<<<<<<<<<<<<<<<< �v�œK���i�t���Ɍv�Z����΃V���v���ɂł���j
				_tmpMatrix.LoadIdentity();
				{
					_tmpMatrix.TranslateRelative( layoutBoundsOnTex01->X, layoutBoundsOnTex01->Y ); //new = [translate]
					// �㉺���] 
					_tmpMatrix.ScaleRelative( scaleX, scaleY * -1.0f ); //new = [translate][scale]
					_tmpMatrix.TranslateRelative( -_tmpBoundsOnModel.X, -_tmpBoundsOnModel.Y );
					//new = [translate][scale][translate]
				}

				_tmpMatrixForDraw.SetMatrix( _tmpMatrix.GetArray() );
			}

			clipContext->_matrixForMask.SetMatrix( _tmpMatrixForMask.GetArray() );

			clipContext->_matrixForDraw.SetMatrix( _tmpMatrixForDraw.GetArray() );

			if( !renderer->IsUsingHighPrecisionMask() )
			{
				const int clipDrawCount = clipContext->_clippingIdCount;
				for( int i = 0; i < clipDrawCount; i++ )
				{
					const int clipDrawIndex = clipContext->_clippingIdList[ i ];

                    // ���_��񂪍X�V����Ă��炸�A�M�������Ȃ��ꍇ�͕`����p�X����
					if( !model.GetDrawableDynamicFlagVertexPositionsDidChange( clipDrawIndex ) )
					{
						continue;
					}

					renderer->IsCulling( model.GetDrawableCulling( clipDrawIndex ) != 0 );

					// �����p�̕ϊ���K�p���ĕ`��
					// �`�����l�����؂�ւ���K�v������(A,R,G,B)
					renderer->SetClippingContextBufferForMask( clipContext );
					renderer->DrawMeshDX11( clipDrawIndex,
						model.GetDrawableTextureIndices( clipDrawIndex ),
						model.GetDrawableVertexIndexCount( clipDrawIndex ),
						model.GetDrawableVertexCount( clipDrawIndex ),
						( WORD* )( model.GetDrawableVertexIndices( clipDrawIndex ) ),
						( float* )( model.GetDrawableVertices( clipDrawIndex ) ),
						( float* )( ( D_CubismVector2* )( model.GetDrawableVertexUvs( clipDrawIndex ) ) ),
						model.GetDrawableOpacity( clipDrawIndex ),
						D_CubismBlendMode_Normal, //�N���b�s���O�͒ʏ�`�������
						false   // �}�X�N�������̓N���b�s���O�̔��]�g�p�͑S���֌W���Ȃ�
					);
				}
			}
			else
			{
				// NOP ���̃��[�h�̍ۂ̓`�����l���𕪂����A�}�g���N�X�̌v�Z���������Ă����ĕ`�掩�͖̂{�̕`�撼�O�ōs�� 
			}
		}

		if( !renderer->IsUsingHighPrecisionMask() )
		{
			useTarget.EndDraw();

			renderer->SetClippingContextBufferForMask( NULL );
		}
	}
}

void D_CubismClippingManager_DxLib::CalcClippedDrawTotalBounds(D_CubismModel& model, D_CubismClippingContext* clippingContext)
{
    // ��N���b�s���O�}�X�N�i�}�X�N�����`��I�u�W�F�N�g�j�̑S�̂̋�`
    float clippedDrawTotalMinX = FLT_MAX, clippedDrawTotalMinY = FLT_MAX;
    float clippedDrawTotalMaxX = FLT_MIN, clippedDrawTotalMaxY = FLT_MIN;

    // ���̃}�X�N�����ۂɕK�v�����肷��
    // ���̃N���b�s���O�𗘗p����u�`��I�u�W�F�N�g�v���ЂƂł��g�p�\�ł���΃}�X�N�𐶐�����K�v������

    const int clippedDrawCount = clippingContext->_clippedDrawableIndexList->GetSize();
    for (int clippedDrawableIndex = 0; clippedDrawableIndex < clippedDrawCount; clippedDrawableIndex++)
    {
        // �}�X�N���g�p����`��I�u�W�F�N�g�̕`�悳����`�����߂�
        const int drawableIndex = (*clippingContext->_clippedDrawableIndexList)[clippedDrawableIndex];

        const int drawableVertexCount = model.GetDrawableVertexCount(drawableIndex);
        const float* drawableVertexes = (float*)(model.GetDrawableVertices(drawableIndex));

        float minX = FLT_MAX, minY = FLT_MAX;
        float maxX = FLT_MIN, maxY = FLT_MIN;

        int loop = drawableVertexCount * VertexStep;
        for (int pi = VertexOffset; pi < loop; pi += VertexStep)
        {
            float x = drawableVertexes[pi];
            float y = drawableVertexes[pi + 1];
            if (x < minX) minX = x;
            if (x > maxX) maxX = x;
            if (y < minY) minY = y;
            if (y > maxY) maxY = y;
        }

        //
        if (minX == FLT_MAX) continue; //�L���ȓ_���ЂƂ����Ȃ������̂ŃX�L�b�v����

        // �S�̂̋�`�ɔ��f
        if (minX < clippedDrawTotalMinX) clippedDrawTotalMinX = minX;
        if (minY < clippedDrawTotalMinY) clippedDrawTotalMinY = minY;
        if (maxX > clippedDrawTotalMaxX) clippedDrawTotalMaxX = maxX;
        if (maxY > clippedDrawTotalMaxY) clippedDrawTotalMaxY = maxY;
    }
    if (clippedDrawTotalMinX == FLT_MAX)
    {
        clippingContext->_allClippedDrawRect->X = 0.0f;
        clippingContext->_allClippedDrawRect->Y = 0.0f;
        clippingContext->_allClippedDrawRect->Width = 0.0f;
        clippingContext->_allClippedDrawRect->Height = 0.0f;
        clippingContext->_isUsing = false;
    }
    else
    {
        clippingContext->_isUsing = true;
        float w = clippedDrawTotalMaxX - clippedDrawTotalMinX;
        float h = clippedDrawTotalMaxY - clippedDrawTotalMinY;
        clippingContext->_allClippedDrawRect->X = clippedDrawTotalMinX;
        clippingContext->_allClippedDrawRect->Y = clippedDrawTotalMinY;
        clippingContext->_allClippedDrawRect->Width = w;
        clippingContext->_allClippedDrawRect->Height = h;
    }
}

void D_CubismClippingManager_DxLib::SetupLayoutBounds(int usingClipCount) const
{
    if(usingClipCount<=0)
    {// ���̏ꍇ�͈�̃}�X�N�^�[�Q�b�g�𖈉�N���A���Ďg�p���� 
        for (DWORD index = 0; index < _clippingContextListForMask.GetSize(); index++)
        {
            D_CubismClippingContext* cc = _clippingContextListForMask[index];
            cc->_layoutChannelNo = 0; // �ǂ�����������̂ŌŒ�ŗǂ� 
            cc->_layoutBounds->X = 0.0f;
            cc->_layoutBounds->Y = 0.0f;
            cc->_layoutBounds->Width = 1.0f;
            cc->_layoutBounds->Height = 1.0f;
        }
        return;
    }

    // �ЂƂ�RenderTexture���ɗ͂����ς��Ɏg���ă}�X�N�����C�A�E�g����
    // �}�X�N�O���[�v�̐���4�ȉ��Ȃ�RGBA�e�`�����l���ɂP���}�X�N��z�u���A5�ȏ�6�ȉ��Ȃ�RGBA��2,2,1,1�Ɣz�u����

    // RGBA�����ԂɎg���Ă����B
    const int div = usingClipCount / ColorChannelCount; //�P�`�����l���ɔz�u�����{�̃}�X�N��
    const int mod = usingClipCount % ColorChannelCount; //�]��A���̔ԍ��̃`�����l���܂łɂP���z������

    // RGBA���ꂼ��̃`�����l����p�ӂ��Ă���(0:R , 1:G , 2:B, 3:A, )
    int curClipIndex = 0; //���Ԃɐݒ肵�Ă���k

    for (int channelNo = 0; channelNo < ColorChannelCount; channelNo++)
    {
        // ���̃`�����l���Ƀ��C�A�E�g���鐔
        const int layoutCount = div + (channelNo < mod ? 1 : 0);

        // �������@�����肷��
        if (layoutCount == 0)
        {
            // �������Ȃ�
        }
        else if (layoutCount == 1)
        {
            //�S�Ă����̂܂܎g��
            D_CubismClippingContext* cc = _clippingContextListForMask[curClipIndex++];
            cc->_layoutChannelNo = channelNo;
            cc->_layoutBounds->X = 0.0f;
            cc->_layoutBounds->Y = 0.0f;
            cc->_layoutBounds->Width = 1.0f;
            cc->_layoutBounds->Height = 1.0f;
        }
        else if (layoutCount == 2)
        {
            for (int i = 0; i < layoutCount; i++)
            {
                const int xpos = i % 2;

                D_CubismClippingContext* cc = _clippingContextListForMask[curClipIndex++];
                cc->_layoutChannelNo = channelNo;

                cc->_layoutBounds->X = xpos * 0.5f;
                cc->_layoutBounds->Y = 0.0f;
                cc->_layoutBounds->Width = 0.5f;
                cc->_layoutBounds->Height = 1.0f;
                //UV��2�ɕ������Ďg��
            }
        }
        else if (layoutCount <= 4)
        {
            //4�������Ďg��
            for (int i = 0; i < layoutCount; i++)
            {
                const int xpos = i % 2;
                const int ypos = i / 2;

                D_CubismClippingContext* cc = _clippingContextListForMask[curClipIndex++];
                cc->_layoutChannelNo = channelNo;

                cc->_layoutBounds->X = xpos * 0.5f;
                cc->_layoutBounds->Y = ypos * 0.5f;
                cc->_layoutBounds->Width = 0.5f;
                cc->_layoutBounds->Height = 0.5f;
            }
        }
        else if (layoutCount <= 9)
        {
            //9�������Ďg��
            for (int i = 0; i < layoutCount; i++)
            {
                const int xpos = i % 3;
                const int ypos = i / 3;

                D_CubismClippingContext* cc = _clippingContextListForMask[curClipIndex++];
                cc->_layoutChannelNo = channelNo;

                cc->_layoutBounds->X = xpos / 3.0f;
                cc->_layoutBounds->Y = ypos / 3.0f;
                cc->_layoutBounds->Width = 1.0f / 3.0f;
                cc->_layoutBounds->Height = 1.0f / 3.0f;
            }
        }
        else
        {
            // CubismLogError("not supported mask count : %d", layoutCount);

            // �J�����[�h�̏ꍇ�͒�~������ 
            // CSM_ASSERT(0);

            // �����������s����ꍇ�A SetupShaderProgram�ŃI�[�o�[�A�N�Z�X����������̂Ŏd���Ȃ��K���ɓ���Ă��� 
            // �������`�挋�ʂ͂낭�Ȃ��ƂɂȂ�Ȃ� 
            for (int i = 0; i < layoutCount; i++)
            {
                D_CubismClippingContext* cc = _clippingContextListForMask[curClipIndex++];
                cc->_layoutChannelNo = 0;
                cc->_layoutBounds->X = 0.0f;
                cc->_layoutBounds->Y = 0.0f;
                cc->_layoutBounds->Width = 1.0f;
                cc->_layoutBounds->Height = 1.0f;
            }
        }
    }
}

D_CubismRenderer::CubismTextureColor* D_CubismClippingManager_DxLib::GetChannelFlagAsColor(int channelNo)
{
    return _channelColors[channelNo];
}

D_CubismOffscreenFrame_DxLib* D_CubismClippingManager_DxLib::GetColorBuffer() const
{
    return _colorBuffer;
}

D_csmVector<D_CubismClippingContext*>* D_CubismClippingManager_DxLib::GetClippingContextListForDraw()
{
    return &_clippingContextListForDraw;
}

void D_CubismClippingManager_DxLib::SetClippingMaskBufferSize(int size)
{
    _clippingMaskBufferSize = size;
}

int D_CubismClippingManager_DxLib::GetClippingMaskBufferSize() const
{
    return _clippingMaskBufferSize;
}

/*********************************************************************************************************************
*                                      D_CubismClippingContext
********************************************************************************************************************/
D_CubismClippingContext::D_CubismClippingContext(D_CubismClippingManager_DxLib* manager, const int* clippingDrawableIndices, int clipCount)
{
    _isUsing = false;

    _owner = manager;

    // �N���b�v���Ă���i���}�X�N�p�́jDrawable�̃C���f�b�N�X���X�g
    _clippingIdList = clippingDrawableIndices;

    // �}�X�N�̐�
    _clippingIdCount = clipCount;

    _layoutChannelNo = 0;

    _allClippedDrawRect = D_CSM_NEW D_csmRectF();
    _layoutBounds = D_CSM_NEW D_csmRectF();

    _clippedDrawableIndexList = D_CSM_NEW D_csmVector<int>();
}

D_CubismClippingContext::~D_CubismClippingContext()
{
    if (_layoutBounds != NULL)
    {
        D_CSM_DELETE(_layoutBounds);
        _layoutBounds = NULL;
    }

    if (_allClippedDrawRect != NULL)
    {
        D_CSM_DELETE(_allClippedDrawRect);
        _allClippedDrawRect = NULL;
    }

    if (_clippedDrawableIndexList != NULL)
    {
        D_CSM_DELETE(_clippedDrawableIndexList);
        _clippedDrawableIndexList = NULL;
    }
}

void D_CubismClippingContext::AddClippedDrawable(int drawableIndex)
{
    _clippedDrawableIndexList->PushBack(drawableIndex);
}

D_CubismClippingManager_DxLib* D_CubismClippingContext::GetClippingManager()
{
    return _owner;
}


/*********************************************************************************************************************
 *                                      D_CubismRenderer_DxLib
 ********************************************************************************************************************/

// �e��ÓI�ϐ� 
namespace
{
    D_CubismRenderState_DxLib* s_renderStateManager = NULL;   ///< �����_�[�X�e�[�g�̊Ǘ� 
    D_CubismShader_DxLib* s_shaderManagerInstance = NULL;     ///< �V�F�[�_�[�Ǘ� 

    DWORD s_bufferSetNum = 1;           ///< �쐬�R���e�L�X�g�̐��B���f�����[�h�O�ɐݒ肳��Ă���K�v����B 

    DWORD s_viewportWidth = 0;          ///< �`��^�[�Q�b�g�� D_CubismRenderer_DxLib::startframe�œn����� 
    DWORD s_viewportHeight = 0;         ///< �`��^�[�Q�b�g���� D_CubismRenderer_DxLib::startframe�œn����� 
}

D_CubismRenderer* D_CubismRenderer::Create()
{
    return D_CSM_NEW D_CubismRenderer_DxLib();
}

void D_CubismRenderer::StaticRelease()
{
    D_CubismRenderer_DxLib::DoStaticRelease();
}

D_CubismRenderState_DxLib* D_CubismRenderer_DxLib::GetRenderStateManager()
{
    if (s_renderStateManager == NULL)
    {
        s_renderStateManager = D_CSM_NEW D_CubismRenderState_DxLib();
    }
    return s_renderStateManager;
}

void D_CubismRenderer_DxLib::DeleteRenderStateManager()
{
    if (s_renderStateManager)
    {
        D_CSM_DELETE_SELF(D_CubismRenderState_DxLib, s_renderStateManager);
        s_renderStateManager = NULL;
    }
}

D_CubismShader_DxLib* D_CubismRenderer_DxLib::GetShaderManager()
{
    if (s_shaderManagerInstance == NULL)
    {
        s_shaderManagerInstance = D_CSM_NEW D_CubismShader_DxLib();
    }
    return s_shaderManagerInstance;
}

void D_CubismRenderer_DxLib::DeleteShaderManager()
{
    if (s_shaderManagerInstance)
    {
        D_CSM_DELETE_SELF(D_CubismShader_DxLib, s_shaderManagerInstance);
        s_shaderManagerInstance = NULL;
    }
}

void D_CubismRenderer_DxLib::GenerateShader()
{
    D_CubismShader_DxLib* shaderManager = GetShaderManager();
    if(shaderManager)
    {
        shaderManager->GenerateShaders();
    }
}

void D_CubismRenderer_DxLib::OnDeviceLost()
{
    // �V�F�[�_�[�E���_�錾�J�� 
    ReleaseShader();
}

void D_CubismRenderer_DxLib::ReleaseShader()
{
    D_CubismShader_DxLib* shaderManager = GetShaderManager();
    if (shaderManager)
    {
        shaderManager->ReleaseShaderProgram();
    }
}

D_CubismRenderer_DxLib::D_CubismRenderer_DxLib()
    : _vertexBuffers(NULL)
	, _indexBuffers(NULL)
	, _constantBuffers(NULL)
    , _drawableNum(0)
    , _clippingManager(NULL)
    , _clippingContextBufferForMask(NULL)
    , _clippingContextBufferForDraw(NULL)
{
    _commandBufferNum = 0;
    _commandBufferCurrent = 0;

    // �e�N�X�`���Ή��}�b�v�̗e�ʂ��m�ۂ��Ă���.
    _textures.PrepareCapacity(32, true);
}

D_CubismRenderer_DxLib::~D_CubismRenderer_DxLib()
{
	// �I�t�X�N���[�����쐬���Ă����̂Ȃ�J��  
	for( DWORD i = 0; i < _offscreenFrameBuffer.GetSize(); i++ )
	{
		_offscreenFrameBuffer[ i ].DestroyOffscreenFrame();
	}
	_offscreenFrameBuffer.Clear();

	const int drawableCount = _drawableNum; //GetModel()->GetDrawableCount();

	for( int buffer = 0; buffer < _commandBufferNum; buffer++ )
	{
		for( int drawAssign = 0; drawAssign < drawableCount; drawAssign++ )
		{
			if( _vertexBuffers[ buffer ][ drawAssign ]!=-1 )
			{
				DeleteVertexBuffer( _vertexBuffers[ buffer ][ drawAssign ] ) ;
				_vertexBuffers[ buffer ][ drawAssign ] = -1;
			}

			if( _indexBuffers[ buffer ][ drawAssign ]!=-1 )
			{
				DeleteIndexBuffer( _indexBuffers[ buffer ][ drawAssign ] ) ;
				_indexBuffers[ buffer ][ drawAssign ] = -1;
			}

			if( _constantBuffers[ buffer ][ drawAssign ] != -1 )
			{
				DeleteShaderConstantBuffer( _constantBuffers[ buffer ][ drawAssign ] ) ;
				_constantBuffers[ buffer ][ drawAssign ] = -1;
			}
		}

		DXFREE( _vertexBuffers[ buffer ] );
		DXFREE( _indexBuffers[ buffer ] );
		DXFREE( _constantBuffers[ buffer ] );
	}

	// 
	DXFREE( _vertexBuffers );
	DXFREE( _indexBuffers );
	DXFREE( _constantBuffers );

	D_CSM_DELETE_SELF( D_CubismClippingManager_DxLib, _clippingManager );
}

void D_CubismRenderer_DxLib::DoStaticRelease()
{
    // �����_�[�X�e�[�g�}�l�[�W���폜 
    DeleteRenderStateManager();
    // �V�F�[�_�}�l�[�W���폜 
    DeleteShaderManager();
}


void D_CubismRenderer_DxLib::Initialize( D_CubismModel* model, int ASyncThread )
{
	// 0�͋����ꂸ �����ɗ���܂łɐݒ肵�Ȃ���΂Ȃ�Ȃ� 
	if( s_bufferSetNum == 0 )
	{
		// CubismLogError("ContextNum has not been set.");
		// CSM_ASSERT(0);
		return;
	}

	if( model->IsUsingMasking() )
	{
		_clippingManager = D_CSM_NEW D_CubismClippingManager_DxLib();  //�N���b�s���O�}�X�N�E�o�b�t�@�O����������������
		_clippingManager->Initialize(
			*model,
			model->GetDrawableCount(),
			model->GetDrawableMasks(),
			model->GetDrawableMaskCounts()
		);
	}

	_sortedDrawableIndexList.Resize( model->GetDrawableCount(), 0 );

	D_CubismRenderer::Initialize( model, ASyncThread );  //�e�N���X�̏������Ă�

	// ���_�o�b�t�@���R���e�L�X�g�� 
	_vertexBuffers = ( int** )( DXALLOC( sizeof( int* ) * s_bufferSetNum ) );
	_indexBuffers = ( int** )( DXALLOC( sizeof( int* ) * s_bufferSetNum ) );
	_constantBuffers = ( int** )( DXALLOC( sizeof( int* ) * s_bufferSetNum ) );

	// ���f���p�[�c���ƂɊm�� 
	const int drawableCount = GetModel()->GetDrawableCount();
	_drawableNum = drawableCount;

	for( DWORD buffer = 0; buffer < s_bufferSetNum; buffer++ )
	{
		// ���_�o�b�t�@ 
		_vertexBuffers[ buffer ] = ( int* )( DXALLOC( sizeof( int ) * drawableCount ) );
		_indexBuffers[ buffer ] = ( int* )( DXALLOC( sizeof( int ) * drawableCount ) );
		_constantBuffers[ buffer ] = ( int* )( DXALLOC( sizeof( int ) * drawableCount ) );

		for( int drawAssign = 0; drawAssign < drawableCount; drawAssign++ )
		{
			// ���_ 
			const int vcount = GetModel()->GetDrawableVertexCount( drawAssign );
			if( vcount != 0 )
			{
				_vertexBuffers[ buffer ][ drawAssign ] = Graphics_VertexBuffer_Create( vcount, DX_VERTEX_TYPE_SHADER_3D, ASyncThread ) ;

				// ��Œ��_������̂ŗ̈悾�� 
				if( _vertexBuffers[ buffer ][ drawAssign ] < 0 )
				{
					// CubismLogError("Vertexbuffer create failed : %d", vcount);
				}
			}
			else
			{
				_vertexBuffers[ buffer ][ drawAssign ] = -1;
			}

			// �C���f�b�N�X�͂����ŗv�f�R�s�[���ς܂��� 
			_indexBuffers[ buffer ][ drawAssign ] = -1;
			const int icount = GetModel()->GetDrawableVertexIndexCount( drawAssign );
			if( icount != 0 )
			{
				_indexBuffers[ buffer ][ drawAssign ] = Graphics_IndexBuffer_Create( icount, DX_INDEX_TYPE_16BIT, ASyncThread ) ;

				if( _indexBuffers[ buffer ][ drawAssign ] < 0 )
				{
					// CubismLogError("Indexbuffer create failed : %d", icount);
				}

				SetIndexBufferData( 0, GetModel()->GetDrawableVertexIndices( drawAssign ), icount, _indexBuffers[ buffer ][ drawAssign ] ) ;
			}

			// �萔�o�b�t�@
			if( LIVE2DSYS.EnableConstantBuffer )
			{
				_constantBuffers[ buffer ][ drawAssign ] = Graphics_ShaderConstantBuffer_Create( sizeof( D_CubismConstantBufferDxLib ), FALSE, ASyncThread ) ;
				if( _constantBuffers[ buffer ][ drawAssign ] < 0 )
				{
					// CubismLogError("ConstantBuffers create failed");
				}
			}
			else
			{
				_constantBuffers[ buffer ][ drawAssign ] = -1 ;
			}
		}
	}

	_commandBufferNum = s_bufferSetNum;
	_commandBufferCurrent = 0;

	if( model->IsUsingMasking() )
	{
		DWORD i ;
		const int bufferHeight = _clippingManager->GetClippingMaskBufferSize();

		// �o�b�N�o�b�t�@���m�� 
		for( i = 0; i < s_bufferSetNum; i++ )
		{
			D_CubismOffscreenFrame_DxLib push;
			_offscreenFrameBuffer.PushBack( push );
		}
		// �I�t�X�N���[�� 
		for( i = 0; i < s_bufferSetNum; i++ )
		{
			_offscreenFrameBuffer[ i ].CreateOffscreenFrame( bufferHeight, bufferHeight );
		}
	}
}

void D_CubismRenderer_DxLib::PreDraw()
{
    SetDefaultRenderState();
}

void D_CubismRenderer_DxLib::PostDraw()
{
    _commandBufferCurrent++;
    if (_commandBufferNum <= _commandBufferCurrent)
    {
        _commandBufferCurrent = 0;
    }
}

void D_CubismRenderer_DxLib::DoDrawModel()
{
	int i ;

	PreDraw();

	//------------ �N���b�s���O�}�X�N�E�o�b�t�@�O���������̏ꍇ ------------
	if( _clippingManager != NULL )
	{
		_clippingManager->_colorBuffer = &_offscreenFrameBuffer[ _commandBufferCurrent ];

		// �T�C�Y���Ⴄ�ꍇ�͂����ō쐬���Ȃ��� 
		if( _clippingManager->_colorBuffer->GetBufferWidth() != ( DWORD )( _clippingManager->GetClippingMaskBufferSize() ) ||
			_clippingManager->_colorBuffer->GetBufferHeight() != ( DWORD )( _clippingManager->GetClippingMaskBufferSize() ) )
		{
			_clippingManager->_colorBuffer->DestroyOffscreenFrame();
			_clippingManager->_colorBuffer->CreateOffscreenFrame(
				( DWORD )( _clippingManager->GetClippingMaskBufferSize() ), ( DWORD )( _clippingManager->GetClippingMaskBufferSize() ) );
		}

		_clippingManager->SetupClippingContext( *GetModel(), this, *_clippingManager->_colorBuffer );

		if( !IsUsingHighPrecisionMask() )
		{
			// �r���[�|�[�g�����ɖ߂� 
			GetRenderStateManager()->SetViewport(
				0.0f,
				0.0f,
				( float )( s_viewportWidth ),
				( float )( s_viewportHeight ),
				0.0f, 1.0f );
		}
	}

	const int drawableCount = GetModel()->GetDrawableCount();
	const int* renderOrder = GetModel()->GetDrawableRenderOrders();

	// �C���f�b�N�X��`�揇�Ń\�[�g
	for( i = 0; i < drawableCount; ++i )
	{
		const int order = renderOrder[ i ];
		_sortedDrawableIndexList[ order ] = i;
	}

	// �`��
	for( i = 0; i < drawableCount; ++i )
	{
		const int drawableIndex = _sortedDrawableIndexList[ i ];

        // Drawable���\����ԂłȂ���Ώ������p�X����
		if( !GetModel()->GetDrawableDynamicFlagIsVisible( drawableIndex ) )
		{
			continue;
		}

		// �N���b�s���O�}�X�N���Z�b�g����
		D_CubismClippingContext* clipContext = ( _clippingManager != NULL )
			? ( *_clippingManager->GetClippingContextListForDraw() )[ drawableIndex ]
			: NULL;

		if( clipContext != NULL && IsUsingHighPrecisionMask() ) // �}�X�N�������K�v������ 
		{
			if( clipContext->_isUsing ) // �������ƂɂȂ��Ă��� 
			{
				D_CubismRenderer_DxLib::GetRenderStateManager()->SetViewport(
					0,
					0,
					( float )( _clippingManager->GetClippingMaskBufferSize() ),
					( float )( _clippingManager->GetClippingMaskBufferSize() ),
					0.0f, 1.0f );

				_clippingManager->_colorBuffer->BeginDraw();
				// 1�������i�`����Ȃ��j�̈�A0���L���i�`�����j�̈�B�i�V�F�[�_�� Cd*Cs��0�ɋ߂��l�������ă}�X�N�����B1��������Ɖ����N����Ȃ��j
				_clippingManager->_colorBuffer->Clear( 1.0f, 1.0f, 1.0f, 1.0f );

				const int clipDrawCount = clipContext->_clippingIdCount;
				for( int ctx = 0; ctx < clipDrawCount; ctx++ )
				{
					const int clipDrawIndex = clipContext->_clippingIdList[ ctx ];

                    // ���_��񂪍X�V����Ă��炸�A�M�������Ȃ��ꍇ�͕`����p�X����
					if( !GetModel()->GetDrawableDynamicFlagVertexPositionsDidChange( clipDrawIndex ) )
					{
						continue;
					}

					IsCulling( GetModel()->GetDrawableCulling( clipDrawIndex ) != 0 );

					// �����p�̕ϊ���K�p���ĕ`��
					// �`�����l�����؂�ւ���K�v������(A,R,G,B)
					SetClippingContextBufferForMask( clipContext );
					DrawMeshDX11( clipDrawIndex,
						GetModel()->GetDrawableTextureIndices( clipDrawIndex ),
						GetModel()->GetDrawableVertexIndexCount( clipDrawIndex ),
						GetModel()->GetDrawableVertexCount( clipDrawIndex ),
						( WORD* )( GetModel()->GetDrawableVertexIndices( clipDrawIndex ) ),
						( float* )( GetModel()->GetDrawableVertices( clipDrawIndex ) ),
						( float* )( ( D_CubismVector2* )( GetModel()->GetDrawableVertexUvs( clipDrawIndex ) ) ),
						GetModel()->GetDrawableOpacity( clipDrawIndex ),
						D_CubismBlendMode_Normal, //�N���b�s���O�͒ʏ�`�������
						false   // �}�X�N�������̓N���b�s���O�̔��]�g�p�͑S���֌W���Ȃ�
					);
				}

				_clippingManager->_colorBuffer->EndDraw();
				SetClippingContextBufferForMask( NULL );

				// �r���[�|�[�g�����ɖ߂� 
				GetRenderStateManager()->SetViewport(
					0.0f,
					0.0f,
					( float )( s_viewportWidth ),
					( float )( s_viewportHeight ),
					0.0f, 1.0f );
			}
		}

		// �N���b�s���O�}�X�N���Z�b�g����
		SetClippingContextBufferForDraw( clipContext );

		IsCulling( GetModel()->GetDrawableCulling( drawableIndex ) != 0 );

		DrawMeshDX11( drawableIndex,
			GetModel()->GetDrawableTextureIndices( drawableIndex ),
			GetModel()->GetDrawableVertexIndexCount( drawableIndex ),
			GetModel()->GetDrawableVertexCount( drawableIndex ),
			( WORD* )( GetModel()->GetDrawableVertexIndices( drawableIndex ) ),
			( float* )( GetModel()->GetDrawableVertices( drawableIndex ) ),
			( float* )( ( D_CubismVector2* )( GetModel()->GetDrawableVertexUvs( drawableIndex ) ) ),
			GetModel()->GetDrawableOpacity( drawableIndex ),
			GetModel()->GetDrawableBlendMode( drawableIndex ),
			GetModel()->GetDrawableInvertedMask( drawableIndex )   // �}�X�N�𔽓]�g�p���邩
		);
	}

	//
	PostDraw();
}

void D_CubismRenderer_DxLib::ExecuteDraw( int vertexBuffer, int indexBuffer, int constantBuffer,
	const int /*indexCount*/,
	const int textureNo, CubismTextureColor& modelColorRGBA, D_CubismBlendMode colorBlendMode, bool invertedMask )
{
	// �g�p�V�F�[�_�G�t�F�N�g�擾 
	D_CubismShader_DxLib* shaderManager = D_CubismRenderer_DxLib::GetShaderManager();
	if( !shaderManager )
	{
		return;
	}

	// �e�N�X�`���Z�b�g 
	int GraphHandle = -1;
	if( textureNo >= 0 )
	{
		GraphHandle = _textures[ textureNo ];
	}

	if( GraphHandle < 0 )
	{
		return;    // ���f�����Q�Ƃ���e�N�X�`�����o�C���h����Ă��Ȃ��ꍇ�͕`����X�L�b�v����
	}

	// �R�[���o�b�N���ݒ肳��Ă���ꍇ�͌Ăяo��
	if( LIVE2DSYS.DrawUserCallback != NULL )
	{
		LIVE2DSYS.DrawUserCallback( LIVE2DSYS.NowDrawLive2DModelHandle, textureNo, LIVE2DSYS.DrawUserCallbackData ) ;
	}

	D_CubismConstantBufferDxLib *cb = NULL ;
	D_CubismConstantBufferDxLib TempConstantBuffer ;
	if( LIVE2DSYS.EnableConstantBuffer )
	{
		cb = ( D_CubismConstantBufferDxLib * )GetBufferShaderConstantBuffer( constantBuffer );
	}
	else
	{
		cb = &TempConstantBuffer ;
	}
	_MEMSET( cb, 0, sizeof( cb ) );

	if( GetClippingContextBufferForMask() != NULL ) // �}�X�N������
	{
 		// �`�����l��
 		const int channelNo = GetClippingContextBufferForMask()->_layoutChannelNo;
 		// �`�����l����RGBA�ɕϊ� 
 		CubismTextureColor* colorChannel = GetClippingContextBufferForMask()->GetClippingManager()->GetChannelFlagAsColor( channelNo );
 
 		// �}�X�N�p�u�����h�X�e�[�g 
 		GetRenderStateManager()->SetBlend(
 			D_CubismRenderState_DxLib::Blend_Mask,
 			0, 0, 0, 0,
 			0xffffffff );
 //		SetDrawBlendMode( DX_BLENDMODE_ALPHA, 255 ) ;
 
 		// �萔�o�b�t�@ 
 		{
 			MATRIX proj = D_ConvertToD3DX( GetClippingContextBufferForMask()->_matrixForMask );
 			CreateTransposeMatrix( &cb->projectMatrix, &proj ) ;
 //			cb->projectMatrix = proj ;
 
 			D_csmRectF* rect = GetClippingContextBufferForMask()->_layoutBounds;
 			cb->baseColor.r = rect->X * 2.0f - 1.0f;
 			cb->baseColor.g = rect->Y * 2.0f - 1.0f;
 			cb->baseColor.b = rect->GetRight() * 2.0f - 1.0f;
 			cb->baseColor.a = rect->GetBottom() * 2.0f - 1.0f;
 			cb->channelFlag.r = colorChannel->R;
 			cb->channelFlag.g = colorChannel->G;
 			cb->channelFlag.b = colorChannel->B;
 			cb->channelFlag.a = colorChannel->A;
 		}
 
 		// �e�N�X�`�� 
 		SetUseTextureToShader( 0, GraphHandle ) ;
 		SetDrawMode( DX_DRAWMODE_BILINEAR ) ;
 		SetTextureAddressMode( DX_TEXADDRESS_WRAP, 0 ) ;
 
 		// �V�F�[�_�[�̃Z�b�g�A�b�v
 		Live2DCubism4_SetupShader_PF( constantBuffer, cb, D_ShaderNames_SetupMask, D_ShaderNames_SetupMask ) ;
 
 		// �`�� 
		DrawPolygonIndexed3DToShader_UseVertexBuffer( vertexBuffer, indexBuffer ) ;
 
 		// �`���ɌĂԊ��ˑ��֐�
 		Live2DCubism4_DrawAfter_PF() ;
	}
	else // �}�X�N�����ȊO�̏ꍇ
	{
		const bool masked = GetClippingContextBufferForDraw() != NULL;  // ���̕`��I�u�W�F�N�g�̓}�X�N�Ώۂ�
		const bool premult = IsPremultipliedAlpha();
		// const int offset = ( masked ? 1 : 0 ) + ( IsPremultipliedAlpha() ? 2 : 0 );

		// �u�����h�X�e�[�g 
		switch( colorBlendMode )
		{
		case D_CubismBlendMode_Normal:
		default:
			GetRenderStateManager()->SetBlend(
				D_CubismRenderState_DxLib::Blend_Normal,
				0, 0, 0, 0,
				0xffffffff );
			break;

		case D_CubismBlendMode_Additive:
			GetRenderStateManager()->SetBlend(
				D_CubismRenderState_DxLib::Blend_Add,
				0, 0, 0, 0,
				0xffffffff );
			break;

		case D_CubismBlendMode_Multiplicative:
			GetRenderStateManager()->SetBlend(
				D_CubismRenderState_DxLib::Blend_Mult,
				0, 0, 0, 0,
				0xffffffff );
			break;
		}

		{
			// �e�N�X�`��+�T���v���[�Z�b�g 
			if( !masked )
			{
				SetUseTextureToShader( 0, GraphHandle ) ;
			}
			else
			{
				SetUseTextureToShader( 0, GraphHandle ) ;
				SetUseTextureToShader( 1, _clippingManager->_colorBuffer->GetTextureView() ) ;
			}
			SetDrawMode( DX_DRAWMODE_ANISOTROPIC ) ;
			SetMaxAnisotropy( 16 ) ;
			SetTextureAddressMode( DX_TEXADDRESS_WRAP, 0 ) ;
			SetTextureAddressMode( DX_TEXADDRESS_WRAP, 1 ) ;

			// �萔�o�b�t�@ 
			{
				if( masked )
				{
					// View���W��ClippingContext�̍��W�ɕϊ����邽�߂̍s���ݒ� 
					MATRIX clip = D_ConvertToD3DX( GetClippingContextBufferForDraw()->_matrixForDraw );
					CreateTransposeMatrix( &cb->clipMatrix, &clip );
//					cb->clipMatrix =  clip;

					// �g�p����J���[�`�����l����ݒ�
					const int channelNo = GetClippingContextBufferForDraw()->_layoutChannelNo;
					D_CubismRenderer::CubismTextureColor* colorChannel = GetClippingContextBufferForDraw()->GetClippingManager()->GetChannelFlagAsColor( channelNo );
					cb->channelFlag.r = colorChannel->R ;
					cb->channelFlag.g = colorChannel->G ;
					cb->channelFlag.b = colorChannel->B ;
					cb->channelFlag.a = colorChannel->A ;
				}

				// �v���W�F�N�V����Mtx  
				D_CubismMatrix44 mvp = GetMvpMatrix();
				MATRIX proj = D_ConvertToD3DX( mvp );
				CreateTransposeMatrix( &cb->projectMatrix, &proj ) ;
//				cb->projectMatrix = proj ;

				// �F 
				cb->baseColor.r = modelColorRGBA.R;
				cb->baseColor.g = modelColorRGBA.G;
				cb->baseColor.b = modelColorRGBA.B;
				cb->baseColor.a = modelColorRGBA.A;
			}

			// �V�F�[�_�Z�b�g 
			if( masked )
			{
				if( premult )
				{
					if( invertedMask )
					{
						Live2DCubism4_SetupShader_PF( constantBuffer, cb, D_ShaderNames_NormalMasked, D_ShaderNames_NormalMaskedInvertedPremultipliedAlpha ) ;
					}
					else
					{
						Live2DCubism4_SetupShader_PF( constantBuffer, cb, D_ShaderNames_NormalMasked, D_ShaderNames_NormalMaskedPremultipliedAlpha ) ;
					}
				}
				else
				{
					if( invertedMask )
					{
						Live2DCubism4_SetupShader_PF( constantBuffer, cb, D_ShaderNames_NormalMasked, D_ShaderNames_NormalMaskedInverted ) ;
					}
					else
					{
						Live2DCubism4_SetupShader_PF( constantBuffer, cb, D_ShaderNames_NormalMasked, D_ShaderNames_NormalMasked ) ;
					}
				}
			}
			else
			{
				if( premult )
				{
					Live2DCubism4_SetupShader_PF( constantBuffer, cb, D_ShaderNames_Normal, D_ShaderNames_NormalPremultipliedAlpha ) ;
				}
				else
				{
					Live2DCubism4_SetupShader_PF( constantBuffer, cb, D_ShaderNames_Normal, D_ShaderNames_Normal ) ;
				}
			}

			// �`�� 
			DrawPolygonIndexed3DToShader_UseVertexBuffer( vertexBuffer, indexBuffer ) ;

			// �`���ɌĂԊ��ˑ��֐�
			Live2DCubism4_DrawAfter_PF() ;
		}
	}
//	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 255 ) ;
//	SetDrawBright( 255,255,255 ) ;
//	DrawExtendGraph( 0, 0, 256, 256, _clippingManager->_colorBuffer->GetTextureView(), TRUE ) ;
//	DrawExtendGraph( 0, 0, 256, 256, GraphHandle, TRUE ) ;
}

void D_CubismRenderer_DxLib::DrawMesh(int /*textureNo*/, int /*indexCount*/, int /*vertexCount*/
    , WORD* /*indexArray*/, float* /*vertexArray*/, float* /*uvArray*/
    , float /*opacity*/, D_CubismBlendMode /*colorBlendMode*/, bool /*invertedMask*/ )
{
    // CubismLogWarning("Use 'DrawMeshDX11' function");
    // CSM_ASSERT(0);
}

void D_CubismRenderer_DxLib::DrawMeshDX11( int drawableIndex
	, int textureNo, int indexCount, int vertexCount
	, WORD* /*indexArray*/, float* vertexArray, float* uvArray
	, float opacity, D_CubismBlendMode colorBlendMode, bool invertedMask )
{
	if( indexCount==0 )
	{// �`�敨���� 
		return;
	}
	// �`��s�v�Ȃ�`�揈�����X�L�b�v���� 
	if( opacity <= 0.0f && GetClippingContextBufferForMask() == NULL )
	{
		return;
	}

	// �e�N�X�`���Z�b�g 
	int textureView = 0;
	if( textureNo >= 0 )
	{
		textureView = _textures[ textureNo ];
	}

	if( textureView <= 0 ) return;    // ���f�����Q�Ƃ���e�N�X�`�����o�C���h����Ă��Ȃ��ꍇ�͕`����X�L�b�v����


	// ���ʕ`��̗L���E����
	if( IsCulling() )
	{
		GetRenderStateManager()->SetCullMode( D_CubismRenderState_DxLib::Cull_Ccw ); // CW������ 
	}
	else
	{
		GetRenderStateManager()->SetCullMode( D_CubismRenderState_DxLib::Cull_None ); // �J�����O���� 
	}

	CubismTextureColor modelColorRGBA = GetModelColor();

	if( GetClippingContextBufferForMask() == NULL ) // �}�X�N�������ȊO
	{
		modelColorRGBA.A *= opacity;
		if( IsPremultipliedAlpha() )
		{
			modelColorRGBA.R *= modelColorRGBA.A;
			modelColorRGBA.G *= modelColorRGBA.A;
			modelColorRGBA.B *= modelColorRGBA.A;
		}
	}

	// ���_�o�b�t�@�ɃR�s�[ 
	CopyToBuffer( drawableIndex, vertexCount, vertexArray, uvArray );

	// �V�F�[�_�[�Z�b�g 
	ExecuteDraw(
		_vertexBuffers[ _commandBufferCurrent ][ drawableIndex ], _indexBuffers[ _commandBufferCurrent ][ drawableIndex ], _constantBuffers[ _commandBufferCurrent ][ drawableIndex ],
		indexCount,
		textureNo, modelColorRGBA, colorBlendMode, invertedMask );

	SetClippingContextBufferForDraw( NULL );
	SetClippingContextBufferForMask( NULL );
}

void D_CubismRenderer_DxLib::SaveProfile()
{
    // ���݂̃����_�����O�X�e�[�g��Push 
    GetRenderStateManager()->SaveCurrentNativeState();
}

void D_CubismRenderer_DxLib::RestoreProfile()
{
    // SaveCurrentNativeState�Ƒ� 
    GetRenderStateManager()->RestoreNativeState();
}

void D_CubismRenderer_DxLib::BindTexture(DWORD modelTextureAssign, int GraphHandle)
{
    _textures[modelTextureAssign] = GraphHandle;
}

const D_csmMap<int, int>& D_CubismRenderer_DxLib::GetBindedTextures() const
{
    return _textures;
}

void D_CubismRenderer_DxLib::SetClippingMaskBufferSize(int size)
{
    //FrameBuffer�̃T�C�Y��ύX���邽�߂ɃC���X�^���X��j���E�č쐬����
    D_CSM_DELETE_SELF(D_CubismClippingManager_DxLib, _clippingManager);

    _clippingManager = D_CSM_NEW D_CubismClippingManager_DxLib();

    _clippingManager->SetClippingMaskBufferSize(size);

    _clippingManager->Initialize(
        *GetModel(),
        GetModel()->GetDrawableCount(),
        GetModel()->GetDrawableMasks(),
        GetModel()->GetDrawableMaskCounts()
    );
}

int D_CubismRenderer_DxLib::GetClippingMaskBufferSize() const
{
    return _clippingManager->GetClippingMaskBufferSize();
}

void D_CubismRenderer_DxLib::InitializeConstantSettings(DWORD bufferSetNum)
{
    s_bufferSetNum = bufferSetNum;

    // ���̂��쐬���Ă��� 
    D_CubismRenderer_DxLib::GetRenderStateManager();
}

void D_CubismRenderer_DxLib::SetDefaultRenderState()
{
    // Z�͖��� �`�揇�Ő��� 
    GetRenderStateManager()->SetZEnable(
        D_CubismRenderState_DxLib::Depth_Disable,
        0);

    // �r���[�|�[�g 
    GetRenderStateManager()->SetViewport(
        0.0f,
        0.0f,
        (float)(s_viewportWidth),
        (float)(s_viewportHeight),
        0.0f, 1.0f);
}

void D_CubismRenderer_DxLib::StartFrame(DWORD viewportWidth, DWORD viewportHeight)
{
    // �t���[���Ŏg�p����f�o�C�X�ݒ� 
    s_viewportWidth = viewportWidth;
    s_viewportHeight = viewportHeight;

    // �����_�[�X�e�[�g�t���[���擪���� 
    GetRenderStateManager()->StartFrame();

    // �V�F�[�_�E���_�錾 
    GetShaderManager()->SetupShader();
}

void D_CubismRenderer_DxLib::EndFrame()
{
}

void D_CubismRenderer_DxLib::SetClippingContextBufferForDraw(D_CubismClippingContext* clip)
{
    _clippingContextBufferForDraw = clip;
}

D_CubismClippingContext* D_CubismRenderer_DxLib::GetClippingContextBufferForDraw() const
{
    return _clippingContextBufferForDraw;
}

void D_CubismRenderer_DxLib::SetClippingContextBufferForMask(D_CubismClippingContext* clip)
{
    _clippingContextBufferForMask = clip;
}

D_CubismClippingContext* D_CubismRenderer_DxLib::GetClippingContextBufferForMask() const
{
    return _clippingContextBufferForMask;
}

void D_CubismRenderer_DxLib::CopyToBuffer( int drawAssign, const int vcount, const float* varray, const float* uvarray )
{
	const int icount = GetModel()->GetDrawableVertexIndexCount( drawAssign );

	if( vcount > 0 )
	{
		if( _vertexBuffers[ _commandBufferCurrent ][ drawAssign ] < 0 )
		{
			_vertexBuffers[ _commandBufferCurrent ][ drawAssign ] = Graphics_VertexBuffer_Create( vcount, DX_VERTEX_TYPE_SHADER_3D, FALSE ) ;

			// ��Œ��_������̂ŗ̈悾�� 
			if( _vertexBuffers[ _commandBufferCurrent ][ drawAssign ] < 0 )
			{
				// CubismLogError("Vertexbuffer create failed : %d", vcount);
			}

			NS_SetDeleteHandleFlag( _vertexBuffers[ _commandBufferCurrent ][ drawAssign ], &_vertexBuffers[ _commandBufferCurrent ][ drawAssign ] ) ;
		}

		// CubismVertexD3D11�̏������� 
		VERTEX3DSHADER *Vertex = ( VERTEX3DSHADER * )NS_GetBufferVertexBuffer( _vertexBuffers[ _commandBufferCurrent ][ drawAssign ] ) ;
		if( Vertex != NULL )
		{
			for( int ct = 0; ct < vcount * 2; ct += 2 )
			{	// ���f���f�[�^����̃R�s�[ 
				Vertex[ ct / 2 ].pos.x = varray[ ct + 0 ];
				Vertex[ ct / 2 ].pos.y = varray[ ct + 1 ];
				Vertex[ ct / 2 ].pos.z = 0.0f;
				Vertex[ ct / 2 ].u = uvarray[ ct + 0 ];
				Vertex[ ct / 2 ].v = uvarray[ ct + 1 ];
			}
			NS_UpdateVertexBuffer( _vertexBuffers[ _commandBufferCurrent ][ drawAssign ], 0, vcount ) ;
		}
	}

	if( icount > 0 )
	{
		if( _indexBuffers[ _commandBufferCurrent ][ drawAssign ] < 0 )
		{
			_indexBuffers[ _commandBufferCurrent ][ drawAssign ] = Graphics_IndexBuffer_Create( icount, DX_INDEX_TYPE_16BIT, FALSE ) ;

			if( _indexBuffers[ _commandBufferCurrent ][ drawAssign ] < 0 )
			{
				// CubismLogError("Indexbuffer create failed : %d", icount);
			}

			NS_SetDeleteHandleFlag( _indexBuffers[ _commandBufferCurrent ][ drawAssign ], &_indexBuffers[ _commandBufferCurrent ][ drawAssign ] ) ;
		}

		NS_SetIndexBufferData( 0, GetModel()->GetDrawableVertexIndices( drawAssign ), icount, _indexBuffers[ _commandBufferCurrent ][ drawAssign ] ) ;
	}
}



















D_CubismOffscreenFrame_DxLib::D_CubismOffscreenFrame_DxLib()
    : _GraphHandle(-1)
    , _BackupDrawScreen(-1)
    , _bufferWidth(0)
    , _bufferHeight(0)
{
}


void D_CubismOffscreenFrame_DxLib::BeginDraw()
{
    if(_GraphHandle==-1)
    {
        return;
    }

    // �o�b�N�o�b�t�@�̃T�[�t�F�C�X���L�����Ă���
    _BackupDrawScreen = GetDrawScreen() ;

    // ���O�̃����_�[�^�[�Q�b�g�ɐ؂�ւ�
	SetDrawScreen( _GraphHandle ) ;
}

void D_CubismOffscreenFrame_DxLib::EndDraw()
{
    if (_GraphHandle == -1)
    {
        return;
    }

    // �^�[�Q�b�g�����ɖ߂� 
	SetDrawScreen( _BackupDrawScreen ) ;
}

void D_CubismOffscreenFrame_DxLib::Clear(float r, float g, float b, float a)
{
    int lBackupDrawScreen = GetDrawScreen() ;
	int lBackupBackgroundColorR, lBackupBackgroundColorG, lBackupBackgroundColorB, lBackupBackgroundColorA ;
	SetDrawScreen( _GraphHandle ) ;
	GetBackgroundColor( &lBackupBackgroundColorR, &lBackupBackgroundColorG, &lBackupBackgroundColorB, &lBackupBackgroundColorA ) ;
	SetBackgroundColor( (int)( r * 255.0f ), (int)( g * 255.0f ), (int)( b * 255.0f ), (int)( a * 255.0f ) ) ;
	ClearDrawScreen( NULL ) ;
	SetBackgroundColor( lBackupBackgroundColorR, lBackupBackgroundColorG, lBackupBackgroundColorB, lBackupBackgroundColorA ) ;
	SetDrawScreen( lBackupDrawScreen ) ;
}

bool D_CubismOffscreenFrame_DxLib::CreateOffscreenFrame(DWORD displayBufferWidth, DWORD displayBufferHeight)
{
    // ��U�폜 
    DestroyOffscreenFrame();

//	SetCreateDrawValidGraphMultiSample( 4, 10 ) ;
	_GraphHandle = MakeScreen( displayBufferWidth, displayBufferHeight, TRUE ) ;

    _bufferWidth = displayBufferWidth;
    _bufferHeight = displayBufferHeight;

	if( _GraphHandle >= 0 )
	{
		// ���� 
		return true;
	}

    // ���s�����̂ō폜 
    DestroyOffscreenFrame();

    return false;
}

void D_CubismOffscreenFrame_DxLib::DestroyOffscreenFrame()
{
	DeleteGraph( _GraphHandle, FALSE ) ;
	_GraphHandle = -1 ;
}

int D_CubismOffscreenFrame_DxLib::GetTextureView() const
{
    return _GraphHandle;
}

DWORD D_CubismOffscreenFrame_DxLib::GetBufferWidth() const
{
    return _bufferWidth;
}

DWORD D_CubismOffscreenFrame_DxLib::GetBufferHeight() const
{
    return _bufferHeight;
}

bool D_CubismOffscreenFrame_DxLib::IsValid() const
{
    if (_GraphHandle == -1)
    {
        return false;
    }

    return true;
}

















D_CubismRenderState_DxLib::D_CubismRenderState_DxLib()
{
    // 
    _MEMSET(_stored._valid, 0, sizeof(_stored._valid));

    Create();
}

D_CubismRenderState_DxLib::~D_CubismRenderState_DxLib()
{
    _pushed.Clear();
}

void D_CubismRenderState_DxLib::Create()
{
}

void D_CubismRenderState_DxLib::StartFrame()
{
    _MEMSET(_stored._valid, 0, sizeof(_stored._valid));

    _pushed.Clear();
}

void D_CubismRenderState_DxLib::Save()
{
    // �����_�̃X�e�[�g��Push 
    _pushed.PushBack(_stored);
}

void D_CubismRenderState_DxLib::Restore()
{
    const DWORD size = _pushed.GetSize();

    if (size == 0)
    {
        return;
    }

    //for�ŒH���čŌ�ɐݒ肵�����܂Ń`�F�b�N 
    bool isSet[State_Max];
    _MEMSET(isSet, 0, sizeof(isSet));

    for (int i = (int)(_pushed.GetSize())-1; i>=0; i--)
    {
        Stored &current = _pushed[i];

        if (_pushed[i]._valid[State_Blend] && !isSet[State_Blend])
        {
            SetBlend(current._blendState, current._blendFactor_r, current._blendFactor_g, current._blendFactor_b, current._blendFactor_a, current._blendMask, true);
            isSet[State_Blend] = true;
        }
        if (_pushed[i]._valid[State_CullMode] && !isSet[State_CullMode])
        {
            SetCullMode(current._cullMode, true);
            isSet[State_CullMode] = true;
        }
        if (_pushed[i]._valid[State_Viewport] && !isSet[State_Viewport])
        {
            SetViewport(current._viewportX, current._viewportY, current._viewportWidth, current._viewportHeight, current._viewportMinZ, current._viewportMaxZ, true);
            isSet[State_Viewport] = true;
        }
        if (_pushed[i]._valid[State_ZEnable] && !isSet[State_ZEnable])
        {
            SetZEnable(current._depthEnable, current._depthRef, true);
            isSet[State_ZEnable] = true;
        }
        if (_pushed[i]._valid[State_Sampler] && !isSet[State_Sampler])
        {
            SetSampler(current._sampler, true);
            isSet[State_Sampler] = true;
        }
    }

    Stored store = _pushed[size - 1];
    _pushed.Remove(size - 1);
    if(_pushed.GetSize()==0)
    {
        _pushed.Clear();
    }
    _stored = store;
}

void D_CubismRenderState_DxLib::SetBlend( Blend blendState, float blendFactor_r, float blendFactor_g, float blendFactor_b, float blendFactor_a, DWORD mask,
    bool force)
{
    if( blendState<0 || Blend_Max<= blendState)
    {// �p�����[�^�ُ�`�F�b�N 
        return;
    }

    if (!_stored._valid[State_Blend] || force ||
        _stored._blendFactor_r != blendFactor_r || _stored._blendFactor_g != blendFactor_g || _stored._blendFactor_b != blendFactor_b || _stored._blendFactor_a != blendFactor_a ||
        _stored._blendMask != mask ||
        _stored._blendState != blendState)
    {
		switch( blendState )
		{
		case Blend_Origin:
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, 255 ) ;
			break;
		case Blend_Zero:
			SetDrawBlendMode( DX_BLENDMODE_LIVE2D_ZERO, 255 ) ;
			break;
		case Blend_Normal:
			SetDrawBlendMode( DX_BLENDMODE_LIVE2D_NORMAL, 255 ) ;
			break;
		case Blend_Add:
			SetDrawBlendMode( DX_BLENDMODE_LIVE2D_ADD, 255 ) ;
			break;
		case Blend_Mult:
			SetDrawBlendMode( DX_BLENDMODE_LIVE2D_MULT, 255 ) ;
			break;
		case Blend_Mask:
			SetDrawBlendMode( DX_BLENDMODE_LIVE2D_MASK, 255 ) ;
			break;

		default:
			break;
		}
    }

    _stored._blendState = blendState;
    _stored._blendFactor_r = blendFactor_r;
    _stored._blendFactor_g = blendFactor_g;
    _stored._blendFactor_b = blendFactor_b;
    _stored._blendFactor_a = blendFactor_a;
    _stored._blendMask = mask;

    _stored._valid[State_Blend] = true;
}

void D_CubismRenderState_DxLib::SetCullMode( Cull cullFace, bool force)
{
    if( cullFace<0 || Cull_Max <= cullFace)
    {// �p�����[�^�ُ�`�F�b�N 
        return;
    }

    if (!_stored._valid[State_CullMode] || force ||
        _stored._cullMode != cullFace)
    {
		switch( cullFace )
		{
		case Cull_Origin:///< ���X�̐ݒ� 
			SetUseBackCulling( DX_CULLING_LEFT ) ;
			break ;
		case Cull_None:  ///< �J�����O���� 
		default:
			SetUseBackCulling( DX_CULLING_NONE ) ;
			break ;
		case Cull_Ccw:   ///< CCW�\�� 
			SetUseBackCulling( DX_CULLING_RIGHT ) ;
			break ;
		}
    }

    _stored._cullMode = cullFace;

    _stored._valid[State_CullMode] = true;
}

void D_CubismRenderState_DxLib::SetViewport( float left, float top, float width, float height, float zMin, float zMax, bool force)
{
    if (!_stored._valid[State_Blend] || force ||
        _stored._viewportX != left || _stored._viewportY != top || _stored._viewportWidth != width || _stored._viewportHeight != height ||
        _stored._viewportMinZ != zMin || _stored._viewportMaxZ != zMax)
    {
        // �R���e�L�X�g�ɃZ�b�g
		SetDrawArea( ( int )left, ( int )top, ( int )( left + width ), ( int )( top + height ) ) ;
    }

    _stored._viewportX = left;
    _stored._viewportY = top;
    _stored._viewportWidth = width;
    _stored._viewportHeight = height;
    _stored._viewportMinZ = zMin;
    _stored._viewportMaxZ = zMax;

    _stored._valid[State_Viewport] = true;
}

void D_CubismRenderState_DxLib::SetZEnable( Depth enable, DWORD stelcilRef, bool force)
{
    if (enable<0 || Depth_Max <= enable)
    {// �p�����[�^�ُ�`�F�b�N 
        return;
    }

    if (!_stored._valid[State_ZEnable] || force ||
        _stored._depthEnable != enable)
    {
		switch( enable )
		{
		case Depth_Origin:   ///< ���X�̐ݒ� 
			SetUseZBufferFlag( FALSE ) ;
			break;
		case Depth_Disable:  ///< Zoff 
		default :
			SetUseZBufferFlag( FALSE ) ;
			break;
		case Depth_Enable:   ///< Zon 
			SetUseZBufferFlag( TRUE ) ;
			break;
		}
    }

    _stored._depthEnable = enable;
    _stored._depthRef = stelcilRef;

    _stored._valid[State_ZEnable] = true;
}

void D_CubismRenderState_DxLib::SetSampler( Sampler sample, bool force)
{
    if ( sample<0 || Sampler_Max <= sample)
    {// �p�����[�^�ُ�`�F�b�N 
        return;
    }

    if (!_stored._valid[State_ZEnable] || force ||
        _stored._sampler != sample)
    {
        // 0�Ԃ����g�p���Ă��� 
		switch( sample )
		{
		case Sampler_Origin: ///< ���X�̐ݒ� 
			SetDrawMode( DX_DRAWMODE_NEAREST ) ;
			break ;
		case Sampler_Normal: ///< �g�p�X�e�[�g 
		default :
			SetDrawMode( DX_DRAWMODE_ANISOTROPIC ) ;
			break ;
		}
    }

    _stored._sampler = sample;

    _stored._valid[State_Sampler] = true;
}

void D_CubismRenderState_DxLib::SaveCurrentNativeState()
{
    // �܂��͑S�j�� 
    _pushed.Clear();
    // ���ݒ舵���� 
    _MEMSET(_stored._valid, 0, sizeof(_stored._valid));

	GetDrawBlendMode( &backupBlendMode, &backupBlendParam ) ;
	GetDrawAlphaTest( &backupDrawAlphaTestMode, &backupDrawAlphaTestParam ) ;
	backupCullMode = GetUseBackCulling() ;
	backupUseZBuffer = FALSE ;
	backupMaxAnisotropy = GetMaxAnisotropy() ;
	backupDrawMode = GetDrawMode() ;
	GetDrawArea( &backupDrawArea ) ;
	SetDrawAlphaTest( DX_CMP_ALWAYS, 0 ) ;
}

void D_CubismRenderState_DxLib::RestoreNativeState()
{
    // �S�čČ� 
    for (int i = (int)(_pushed.GetSize()) - 1; i >= 0; i--)
    {
        Restore();
    }

	SetDrawBlendMode( backupBlendMode, backupBlendParam );
	SetUseBackCulling( backupCullMode ) ;
	SetUseZBufferFlag( backupUseZBuffer ) ;
	SetMaxAnisotropy( backupMaxAnisotropy ) ;
	SetDrawMode( backupDrawMode ) ;
	SetDrawAlphaTest( backupDrawAlphaTestMode, backupDrawAlphaTestParam ) ;
	SetDrawArea( backupDrawArea.left, backupDrawArea.top, backupDrawArea.right, backupDrawArea.bottom ) ;
}

















void D_CubismShader_DxLib::ReleaseShaderProgram()
{
    // ��͂��̂܂� 
    for (int i = 0; i < D_ShaderNames_Max; i++)
    {
        if( _shaderSetsVS[ i ] != -1 )
        {
			DeleteShader( _shaderSetsVS[ i ] ) ;
			_shaderSetsVS[ i ] = -1 ;
        }

        if( _shaderSetsPS[ i ] != -1 )
        {
			DeleteShader( _shaderSetsPS[ i ] ) ;
			_shaderSetsPS[ i ] = -1 ;
        }
    }
}

D_CubismShader_DxLib::D_CubismShader_DxLib()
{
    // ��쐬 
    for (int i = 0; i < D_ShaderNames_Max; i++)
    {
        _shaderSetsVS[ i ] = -1 ;
        _shaderSetsPS[ i ] = -1 ;
    }
}

D_CubismShader_DxLib::~D_CubismShader_DxLib()
{
    ReleaseShaderProgram();
}

void D_CubismShader_DxLib::GenerateShaders()
{
//	// ��U�J�� 
//	ReleaseShaderProgram();

	bool isSuccess = false;
	do
	{
		// �}�X�N 
		if( _shaderSetsVS[ D_ShaderNames_SetupMask ] < 0 )
		{
			if( !LoadShaderProgram( false, D_ShaderNames_SetupMask, "Live2DShader_VertSetupMask" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsVS[ D_ShaderNames_SetupMask ], &_shaderSetsVS[ D_ShaderNames_SetupMask ] ) ;
		}
		if( _shaderSetsPS[ D_ShaderNames_SetupMask ] < 0 )
		{
			if( !LoadShaderProgram( true, D_ShaderNames_SetupMask, "Live2DShader_PixelSetupMask" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsPS[ D_ShaderNames_SetupMask ], &_shaderSetsPS[ D_ShaderNames_SetupMask ] ) ;
		}

		// ���_�V�F�[�_ 
		if( _shaderSetsVS[ D_ShaderNames_Normal ] < 0 )
		{
			if( !LoadShaderProgram( false, D_ShaderNames_Normal, "Live2DShader_VertNormal" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsVS[ D_ShaderNames_Normal ], &_shaderSetsVS[ D_ShaderNames_Normal ] ) ;
		}
		if( _shaderSetsVS[ D_ShaderNames_NormalMasked ] < 0 )
		{
			if( !LoadShaderProgram( false, D_ShaderNames_NormalMasked, "Live2DShader_VertMasked" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsVS[ D_ShaderNames_NormalMasked ], &_shaderSetsVS[ D_ShaderNames_NormalMasked ] ) ;
		}

		// �s�N�Z���V�F�[�_ 
		if( _shaderSetsPS[ D_ShaderNames_Normal ] < 0 )
		{
			if( !LoadShaderProgram( true, D_ShaderNames_Normal, "Live2DShader_PixelNormal" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsPS[ D_ShaderNames_Normal ], &_shaderSetsPS[ D_ShaderNames_Normal ] ) ;
		}
		if( _shaderSetsPS[ D_ShaderNames_NormalMasked ] < 0 )
		{
			if( !LoadShaderProgram( true, D_ShaderNames_NormalMasked, "Live2DShader_PixelMasked" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsPS[ D_ShaderNames_NormalMasked ], &_shaderSetsPS[ D_ShaderNames_NormalMasked ] ) ;
		}
		if( _shaderSetsPS[ D_ShaderNames_NormalMasked ] < 0 )
		{
			if( !LoadShaderProgram( true, D_ShaderNames_NormalMasked, "Live2DShader_PixelMasked" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsPS[ D_ShaderNames_NormalMasked ], &_shaderSetsPS[ D_ShaderNames_NormalMasked ] ) ;
		}
		if( _shaderSetsPS[ D_ShaderNames_NormalMaskedInverted ] < 0 )
		{
			if( !LoadShaderProgram( true, D_ShaderNames_NormalMaskedInverted, "Live2DShader_PixelMaskedInverted" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsPS[ D_ShaderNames_NormalMaskedInverted ], &_shaderSetsPS[ D_ShaderNames_NormalMaskedInverted ] ) ;
		}
		if( _shaderSetsPS[ D_ShaderNames_NormalPremultipliedAlpha ] < 0 )
		{
			if( !LoadShaderProgram( true, D_ShaderNames_NormalPremultipliedAlpha, "Live2DShader_PixelNormalPremult" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsPS[ D_ShaderNames_NormalPremultipliedAlpha ], &_shaderSetsPS[ D_ShaderNames_NormalPremultipliedAlpha ] ) ;
		}
		if( _shaderSetsPS[ D_ShaderNames_NormalMaskedPremultipliedAlpha ] < 0 )
		{
			if( !LoadShaderProgram( true, D_ShaderNames_NormalMaskedPremultipliedAlpha, "Live2DShader_PixelMaskedPremult" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsPS[ D_ShaderNames_NormalMaskedPremultipliedAlpha ], &_shaderSetsPS[ D_ShaderNames_NormalMaskedPremultipliedAlpha ] ) ;
		}
		if( _shaderSetsPS[ D_ShaderNames_NormalMaskedInvertedPremultipliedAlpha ] < 0 )
		{
			if( !LoadShaderProgram( true, D_ShaderNames_NormalMaskedInvertedPremultipliedAlpha, "Live2DShader_PixelMaskedInvertedPremult" ) )
			{
				break;
			}
			NS_SetDeleteHandleFlag( _shaderSetsPS[ D_ShaderNames_NormalMaskedInvertedPremultipliedAlpha ], &_shaderSetsPS[ D_ShaderNames_NormalMaskedInvertedPremultipliedAlpha ] ) ;
		}

		if( Live2DCubism4_GenerateShaders_PF() < 0 )
		{
			break ;
		}

		// ���� 
		isSuccess = true;
	} while( 0 );

	if( !isSuccess )
	{
		// CubismLogError("Fail Compile shader");
		// CSM_ASSERT(0);
		return;
	}
}

int D_CubismShader_DxLib::GetVertexShader(DWORD assign)
{
    if(assign<D_ShaderNames_Max)
    {
        return _shaderSetsVS[assign];
    }

    return -1;
}

int D_CubismShader_DxLib::GetPixelShader(DWORD assign)
{
    if (assign<D_ShaderNames_Max)
    {
        return _shaderSetsPS[assign];
    }

    return -1;
}

void D_CubismShader_DxLib::SetupShader()
{
    // �܂��V�F�[�_�E���_�錾���쐬�Ȃ�΍쐬���� 
    GenerateShaders();
}




















D_CubismUserModel::D_CubismUserModel()
    : _moc(NULL)
    , _model(NULL)
    , _motionManager(NULL)
    , _expressionManager(NULL)
    , _eyeBlink(NULL)
    , _breath(NULL)
    , _modelMatrix(NULL)
    , _pose(NULL)
    , _dragManager(NULL)
    , _physics(NULL)
    , _modelUserData(NULL)
    , _initialized(false)
    , _updating(false)
    , _opacity(1.0f)
    , _lipSync(true)
    , _lastLipSyncValue(0.0f)
    , _dragX(0.0f)
    , _dragY(0.0f)
    , _accelerationX(0.0f)
    , _accelerationY(0.0f)
    , _accelerationZ(0.0f)
    , _debugMode(false)
    , _renderer(NULL)
{
    // ���[�V�����}�l�[�W���[���쐬
    // MotionQueueManager�N���X����̌p���Ȃ̂Ŏg�����͓���
    _motionManager = D_CSM_NEW D_CubismMotionManager();
    _motionManager->SetEventCallback(CubismDefaultMotionEventCallback, this);

    // �\��[�V�����}�l�[�W�����쐬
    _expressionManager = D_CSM_NEW D_CubismMotionManager();

    // �h���b�O�ɂ��A�j���[�V����
    _dragManager = D_CSM_NEW D_CubismTargetPoint();

}

D_CubismUserModel::~D_CubismUserModel()
{
    D_CSM_DELETE(_motionManager);
    D_CSM_DELETE(_expressionManager);
	if( _moc != NULL )
	{
		_moc->DeleteModel( _model );
	}
    D_CubismMoc::Delete(_moc);
    D_CSM_DELETE(_modelMatrix);
    D_CubismPose::Delete(_pose);
    D_CubismEyeBlink::Delete(_eyeBlink);
    D_CubismBreath::Delete(_breath);
    D_CSM_DELETE(_dragManager);
    D_CubismPhysics::Delete(_physics);
    D_CubismModelUserData::Delete(_modelUserData);

    DeleteRenderer();
}

void D_CubismUserModel::SetAcceleration(float x, float y, float z)
{
    _accelerationX = x;
    _accelerationY = y;
    _accelerationZ = z;
}

void D_CubismUserModel::LoadModel(const BYTE* buffer, size_t size)
{
    _moc = D_CubismMoc::Create(buffer, size);
    _model = _moc->CreateModel();
    _model->SaveParameters();

    if ((_moc == NULL) || (_model == NULL))
    {
//        CubismLogError("Failed to CreateModel().");
        return;
    }

    _modelMatrix = D_CSM_NEW D_CubismModelMatrix(_model->GetCanvasWidth(), _model->GetCanvasHeight());

}

D_ACubismMotion* D_CubismUserModel::LoadExpression(const BYTE* buffer, size_t size, const BYTE/*wchar_t*/ * /*name*/)
{
    return D_CubismExpressionMotion::Create(buffer, size);
}

void D_CubismUserModel::LoadPose(const BYTE* buffer, size_t size)
{
    _pose = D_CubismPose::Create(buffer, size);
}

void D_CubismUserModel::LoadPhysics(const BYTE* buffer, size_t size)
{
    _physics = D_CubismPhysics::Create(buffer, size);
}

void D_CubismUserModel::LoadUserData(const BYTE* buffer, size_t size)
{
    _modelUserData = D_CubismModelUserData::Create(buffer, size);
}
bool D_CubismUserModel::IsHit(D_CubismIdHandle drawableId, float pointX, float pointY)
{
    const int drawIndex = _model->GetDrawableIndex(drawableId);

    if (drawIndex < 0)
    {
        return false; // ���݂��Ȃ��ꍇ��false
    }

    const int    count = _model->GetDrawableVertexCount(drawIndex);
    const float* vertices = _model->GetDrawableVertices(drawIndex);

    float left = vertices[0];
    float right = vertices[0];
    float top = vertices[1];
    float bottom = vertices[1];

    for (int j = 1; j < count; ++j)
    {
        float x = vertices[VertexOffset + j * VertexStep];
        float y = vertices[VertexOffset + j * VertexStep + 1];

        if (x < left)
        {
            left = x; // Min x
        }

        if (x > right)
        {
            right = x; // Max x
        }

        if (y < top)
        {
            top = y; // Min y
        }

        if (y > bottom)
        {
            bottom = y; // Max y
        }
    }

    const float tx = _modelMatrix->InvertTransformX(pointX);
    const float ty = _modelMatrix->InvertTransformY(pointY);

    return ((left <= tx) && (tx <= right) && (top <= ty) && (ty <= bottom));
}

D_ACubismMotion* D_CubismUserModel::LoadMotion(const BYTE* buffer, size_t size, const BYTE/*wchar_t*/ * /*name*/)
{
    return D_CubismMotion::Create(buffer, size);
}

void D_CubismUserModel::SetDragging(float x, float y)
{
    _dragManager->Set(x, y);
}

D_CubismModelMatrix* D_CubismUserModel::GetModelMatrix() const
{
    return _modelMatrix;
}

bool D_CubismUserModel::IsInitialized()
{
    return _initialized;
}

void D_CubismUserModel::IsInitialized(bool v)
{
    _initialized = v;
}

bool D_CubismUserModel::IsUpdating()
{
    return _updating;
}

void D_CubismUserModel::IsUpdating(bool v)
{
    _updating = v;
}

void D_CubismUserModel::SetOpacity(float a)
{
    _opacity = a;
}

float D_CubismUserModel::GetOpacity()
{
    return _opacity;
}

D_CubismModel* D_CubismUserModel::GetModel() const
{
    return _model;
}

void D_CubismUserModel::CreateRenderer( int ASyncThread )
{
	if( _renderer )
	{
		DeleteRenderer();
	}
	_renderer = D_CubismRenderer::Create();

	_renderer->Initialize( _model, ASyncThread );
}

void D_CubismUserModel::DeleteRenderer()
{
    if (_renderer)
    {
        D_CubismRenderer::Delete(_renderer);

        _renderer = NULL;
    }
}

void D_CubismUserModel::CubismDefaultMotionEventCallback(const D_CubismMotionQueueManager* /*caller*/, const D_csmString& eventValue, void* customData)
{
    D_CubismUserModel* model = (D_CubismUserModel*)(customData);
    if (model != NULL)
    {
        model->MotionEventFired(eventValue);
    }
}

void D_CubismUserModel::MotionEventFired(const D_csmString& /*eventValue*/)
{
    // CubismLogInfo("%s",eventValue.GetRawString());
}






















// JSON keys
#define STR_Version					"Version"
#define STR_FileReferences			"FileReferences"
#define STR_Groups					"Groups"
#define STR_Layout					"Layout"
#define STR_HitAreas				"HitAreas"

#define STR_Moc						"Moc"
#define STR_Textures				"Textures"
#define STR_Physics					"Physics"
#define STR_Pose					"Pose"
#define STR_Expressions				"Expressions"
#define STR_Motions					"Motions"

#define STR_UserData				"UserData"
#define STR_Name					"Name"
#define STR_FilePath				"File"
#define STR_Id						"Id"
#define STR_Ids						"Ids"
#define STR_Target					"Target"

// Motions
#define STR_Idle					"Idle"
#define STR_TapBody					"TapBody"
#define STR_PinchIn					"PinchIn"
#define STR_PinchOut				"PinchOut"
#define STR_Shake					"Shake"
#define STR_FlickHead				"FlickHead"
#define STR_Parameter				"Parameter"

#define STR_SoundPath				"Sound"
#define STR_FadeInTime				"FadeInTime"
#define STR_FadeOutTime				"FadeOutTime"

// Layout
#define STR_CenterX					"CenterX"
#define STR_CenterY					"CenterY"
#define STR_X						"X"
#define STR_Y						"Y"
#define STR_Width					"Width"
#define STR_Height					"Height"

#define STR_LipSync					"LipSync"
#define STR_EyeBlink				"EyeBlink"

#define STR_InitParameter			"init_param"
#define STR_InitPartsVisible		"init_parts_visible"
#define STR_Val						"val"

// �L�[�����݂��邩�ǂ����̃`�F�b�N
bool D_CubismModelSettingJson::IsExistModelFile() const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_Moc]);
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistTextureFiles() const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_Textures]);
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistHitAreas() const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_HitAreas]);
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistPhysicsFile() const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_Physics]);
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistPoseFile() const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_Pose]);
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistExpressionFile() const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_Expressions]);
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistMotionGroups() const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_Motions]);
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistMotionGroupName(const char* groupName) const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_Motions])[groupName];
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistMotionSoundFile(const char* groupName, int index) const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_SoundPath];
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistMotionFadeIn(const char* groupName, int index) const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_FadeInTime];
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistMotionFadeOut(const char* groupName, int index) const
{
    D_JsonValue& node = (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_FadeOutTime];
    return !node.IsNull() && !node.IsError();
}
bool D_CubismModelSettingJson::IsExistUserDataFile() const { return !_json->GetRoot()[STR_FileReferences][STR_UserData].IsNull(); }


bool D_CubismModelSettingJson::IsExistEyeBlinkParameters() const
{
    if (_jsonValue[FrequentNode_Groups]->IsNull() || _jsonValue[FrequentNode_Groups]->IsError())
    {
        return false;
    }

    for (int i = 0; i < _jsonValue[FrequentNode_Groups]->GetSize(); ++i)
    {
        if (CL_strcmp( DX_CHARCODEFORMAT_UTF8,(*_jsonValue[FrequentNode_Groups])[i][STR_Name].GetRawString(), STR_EyeBlink) == 0)
        {
            return true;
        }
    }
    return false;
}

bool D_CubismModelSettingJson::IsExistLipSyncParameters() const
{
    if (_jsonValue[FrequentNode_Groups]->IsNull() || _jsonValue[FrequentNode_Groups]->IsError())
    {
        return false;
    }

    for (int i = 0; i < _jsonValue[FrequentNode_Groups]->GetSize(); ++i)
    {
        if (CL_strcmp( DX_CHARCODEFORMAT_UTF8,(*_jsonValue[FrequentNode_Groups])[i][STR_Name].GetRawString(), STR_LipSync) == 0)
        {
            return true;
        }
    }
    return false;
}

D_CubismModelSettingJson::D_CubismModelSettingJson(const BYTE* buffer, size_t size)
{
    _json = D_CubismJson::Create(buffer, size);

    if (_json)
    {
        _jsonValue.Clear();

        // ���Ԃ�enum FrequentNode�ƈ�v������ 
        _jsonValue.PushBack(&(_json->GetRoot()[STR_Groups]));
        _jsonValue.PushBack(&(_json->GetRoot()[STR_FileReferences][STR_Moc]));
        _jsonValue.PushBack(&(_json->GetRoot()[STR_FileReferences][STR_Motions]));
        _jsonValue.PushBack(&(_json->GetRoot()[STR_FileReferences][STR_Expressions]));
        _jsonValue.PushBack(&(_json->GetRoot()[STR_FileReferences][STR_Textures]));
        _jsonValue.PushBack(&(_json->GetRoot()[STR_FileReferences][STR_Physics]));
        _jsonValue.PushBack(&(_json->GetRoot()[STR_FileReferences][STR_Pose]));
        _jsonValue.PushBack(&(_json->GetRoot()[STR_HitAreas]));
    }
}

D_CubismModelSettingJson::~D_CubismModelSettingJson()
{
    D_CubismJson::Delete( _json);
}

D_CubismJson* D_CubismModelSettingJson::GetJsonPointer() const
{
    return _json;
}

const char* D_CubismModelSettingJson::GetModelFileName()
{
    if (!IsExistModelFile())return "";
    return (*_jsonValue[FrequentNode_Moc]).GetRawString();
}

const char* D_CubismModelSettingJson::GetModelFileNameA()
{
    if (!IsExistModelFile())return "";
    return (*_jsonValue[FrequentNode_Moc]).GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetModelFileNameW()
{
    if (!IsExistModelFile())return ( BYTE * )L"";
    return (*_jsonValue[FrequentNode_Moc]).GetRawStringW();
}

// �e�N�X�`���ɂ���
int D_CubismModelSettingJson::GetTextureCount()
{
    if (!IsExistTextureFiles())return 0;
    return (*_jsonValue[FrequentNode_Textures]).GetSize();
}

const char* D_CubismModelSettingJson::GetTextureDirectory()
{
    return (*_jsonValue[FrequentNode_Textures]).GetRawString();
}

const char* D_CubismModelSettingJson::GetTextureDirectoryA()
{
    return (*_jsonValue[FrequentNode_Textures]).GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetTextureDirectoryW()
{
    return (*_jsonValue[FrequentNode_Textures]).GetRawStringW();
}

const char* D_CubismModelSettingJson::GetTextureFileName(int index)
{
    return (*_jsonValue[FrequentNode_Textures])[index].GetRawString();
}

const char* D_CubismModelSettingJson::GetTextureFileNameA(int index)
{
    return (*_jsonValue[FrequentNode_Textures])[index].GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetTextureFileNameW(int index)
{
    return (*_jsonValue[FrequentNode_Textures])[index].GetRawStringW();
}

// �����蔻��ɂ���
int D_CubismModelSettingJson::GetHitAreasCount()
{
    if (!IsExistHitAreas())return 0;
    return (*_jsonValue[FrequentNode_HitAreas]).GetSize();
}

D_CubismIdHandle D_CubismModelSettingJson::GetHitAreaId(int index)
{
    return LIVE2DSYS.s_cubismIdManager->GetId((*_jsonValue[FrequentNode_HitAreas])[index][Id].GetRawString());
}

const char* D_CubismModelSettingJson::GetHitAreaName(int index)
{
    return (*_jsonValue[FrequentNode_HitAreas])[index][STR_Name].GetRawString();
}

const char* D_CubismModelSettingJson::GetHitAreaNameA(int index)
{
    return (*_jsonValue[FrequentNode_HitAreas])[index][STR_Name].GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetHitAreaNameW( int index )
{
    return (*_jsonValue[FrequentNode_HitAreas])[index][STR_Name].GetRawStringW();
}

// �������Z�A�p�[�c�؂�ւ��A�\��t�@�C���ɂ���
const char* D_CubismModelSettingJson::GetPhysicsFileName()
{
    if (!IsExistPhysicsFile())return "";
    return (*_jsonValue[FrequentNode_Physics]).GetRawString();
}

const char* D_CubismModelSettingJson::GetPhysicsFileNameA()
{
    if (!IsExistPhysicsFile())return "";
    return (*_jsonValue[FrequentNode_Physics]).GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetPhysicsFileNameW()
{
    if (!IsExistPhysicsFile())return ( BYTE * )L"";
    return (*_jsonValue[FrequentNode_Physics]).GetRawStringW();
}

const char* D_CubismModelSettingJson::GetPoseFileName()
{
    if (!IsExistPoseFile())return "";
    return (*_jsonValue[FrequentNode_Pose]).GetRawString();
}

const char* D_CubismModelSettingJson::GetPoseFileNameA()
{
    if (!IsExistPoseFile())return "";
    return (*_jsonValue[FrequentNode_Pose]).GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetPoseFileNameW()
{
    if (!IsExistPoseFile())return ( BYTE * )L"";
    return (*_jsonValue[FrequentNode_Pose]).GetRawStringW();
}

int D_CubismModelSettingJson::GetExpressionCount()
{
    if (!IsExistExpressionFile())return 0;
    return (*_jsonValue[FrequentNode_Expressions]).GetSize();
}

const char* D_CubismModelSettingJson::GetExpressionName(int index)
{
    return (*_jsonValue[FrequentNode_Expressions])[index][STR_Name].GetRawString();
}

const char* D_CubismModelSettingJson::GetExpressionNameA(int index)
{
    return (*_jsonValue[FrequentNode_Expressions])[index][STR_Name].GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetExpressionNameW(int index)
{
    return (*_jsonValue[FrequentNode_Expressions])[index][STR_Name].GetRawStringW();
}

const char* D_CubismModelSettingJson::GetExpressionFileName(int index)
{
    return (*_jsonValue[FrequentNode_Expressions])[index][STR_FilePath].GetRawString();
}

const char* D_CubismModelSettingJson::GetExpressionFileNameA(int index)
{
    return (*_jsonValue[FrequentNode_Expressions])[index][STR_FilePath].GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetExpressionFileNameW(int index)
{
    return (*_jsonValue[FrequentNode_Expressions])[index][STR_FilePath].GetRawStringW();
}

// ���[�V�����ɂ���
int D_CubismModelSettingJson::GetMotionGroupCount()
{
    if (!IsExistMotionGroups())
    {
        return 0;
    }
    return (*_jsonValue[FrequentNode_Motions]).GetKeys().GetSize();
}

const char* D_CubismModelSettingJson::GetMotionGroupName(int index)
{
    if (!IsExistMotionGroups())
    {
        return NULL;
    }
    return (*_jsonValue[FrequentNode_Motions]).GetKeys()[index].GetRawString();
}

const char* D_CubismModelSettingJson::GetMotionGroupNameA(int index)
{
    if (!IsExistMotionGroups())
    {
        return NULL;
    }
    return (*_jsonValue[FrequentNode_Motions]).GetKeys()[index].GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetMotionGroupNameW(int index)
{
    if (!IsExistMotionGroups())
    {
        return NULL;
    }
    return (*_jsonValue[FrequentNode_Motions]).GetKeys()[index].GetRawStringW();
}

int D_CubismModelSettingJson::GetMotionCount(const char* groupName)
{
    if (!IsExistMotionGroupName(groupName))return 0;
    return (*_jsonValue[FrequentNode_Motions])[groupName].GetSize();
}

const char* D_CubismModelSettingJson::GetMotionFileName(const char* groupName, int index)
{
    if (!IsExistMotionGroupName(groupName))return "";
    return (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_FilePath].GetRawString();
}

const char* D_CubismModelSettingJson::GetMotionFileNameA(const char* groupName, int index)
{
    if (!IsExistMotionGroupName(groupName))return "";
    return (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_FilePath].GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetMotionFileNameW(const char* groupName, int index)
{
    if (!IsExistMotionGroupName(groupName))return ( BYTE * )L"";
    return (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_FilePath].GetRawStringW();
}

const char* D_CubismModelSettingJson::GetMotionSoundFileName(const char* groupName, int index)
{
    if (!IsExistMotionSoundFile(groupName, index))return "";
    return (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_SoundPath].GetRawString();
}

const char* D_CubismModelSettingJson::GetMotionSoundFileNameA(const char* groupName, int index)
{
    if (!IsExistMotionSoundFile(groupName, index))return "";
    return (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_SoundPath].GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetMotionSoundFileNameW(const char* groupName, int index)
{
    if (!IsExistMotionSoundFile(groupName, index))return ( BYTE * )L"";
    return (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_SoundPath].GetRawStringW();
}

float D_CubismModelSettingJson::GetMotionFadeInTimeValue(const char* groupName, int index)
{
    if (!IsExistMotionFadeIn(groupName, index))return -1.0f;
    return (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_FadeInTime].ToFloat();
}

float D_CubismModelSettingJson::GetMotionFadeOutTimeValue(const char* groupName, int index)
{
    if (!IsExistMotionFadeOut(groupName, index))return -1.0f;
    return (*_jsonValue[FrequentNode_Motions])[groupName][index][STR_FadeOutTime].ToFloat();
}


const char* D_CubismModelSettingJson::GetUserDataFile()
{
    if (!IsExistUserDataFile())
    {
        return "";
    }
    return _json->GetRoot()[STR_FileReferences][STR_UserData].GetRawString();
}

const char* D_CubismModelSettingJson::GetUserDataFileA()
{
    if (!IsExistUserDataFile())
    {
        return "";
    }
    return _json->GetRoot()[STR_FileReferences][STR_UserData].GetRawStringA();
}

const BYTE/*wchar_t*/ * D_CubismModelSettingJson::GetUserDataFileW()
{
    if (!IsExistUserDataFile())
    {
        return ( BYTE * )L"";
    }
    return _json->GetRoot()[STR_FileReferences][STR_UserData].GetRawStringW();
}

bool D_CubismModelSettingJson::GetLayoutMap(D_csmMap<D_csmString, float>& outLayoutMap) 
{
    D_csmMap<D_csmString, D_JsonValue*>* map = _json->GetRoot()[STR_Layout].GetMap();
    if (map == NULL)
    {
        return false;
    }
    D_csmMap<D_csmString, D_JsonValue*>::const_iterator map_ite;
    bool ret = false;
    for (map_ite = map->Begin(); map_ite != map->End(); ++map_ite)
    {
        outLayoutMap[map_ite->First] = map_ite->Second->ToFloat();
        ret = true;
    }
    return ret;
}

int D_CubismModelSettingJson::GetEyeBlinkParameterCount()
{
    if (!IsExistEyeBlinkParameters())
    {
        return 0;
    }

    int num = 0;
    for (int i = 0; i < _jsonValue[FrequentNode_Groups]->GetSize(); i++)
    {
        D_JsonValue& refI = (*_jsonValue[FrequentNode_Groups])[i];
        if(refI.IsNull() || refI.IsError())
        {
            continue;
        }

        if (CL_strcmp( DX_CHARCODEFORMAT_UTF8,refI[STR_Name].GetRawString(), STR_EyeBlink) == 0)
        {
            num = refI[STR_Ids].GetVector()->GetSize();
            break;
        }
    }

    return num;
}

D_CubismIdHandle D_CubismModelSettingJson::GetEyeBlinkParameterId(int index)
{
    if (!IsExistEyeBlinkParameters())
    {
        return NULL;
    }

    for (int i = 0; i < _jsonValue[FrequentNode_Groups]->GetSize(); i++)
    {
        D_JsonValue& refI = (*_jsonValue[FrequentNode_Groups])[i];
        if (refI.IsNull() || refI.IsError())
        {
            continue;
        }

        if (CL_strcmp( DX_CHARCODEFORMAT_UTF8,refI[STR_Name].GetRawString(), STR_EyeBlink) == 0)
        {
            return LIVE2DSYS.s_cubismIdManager->GetId(refI[STR_Ids][index].GetRawString());
        }
    }
    return NULL;
}

int D_CubismModelSettingJson::GetLipSyncParameterCount()
{
    if (!IsExistLipSyncParameters())
    {
        return 0;
    }

    int num = 0;
    for (int i = 0; i < _jsonValue[FrequentNode_Groups]->GetSize(); i++)
    {
        D_JsonValue& refI = (*_jsonValue[FrequentNode_Groups])[i];
        if (refI.IsNull() || refI.IsError())
        {
            continue;
        }

        if (CL_strcmp( DX_CHARCODEFORMAT_UTF8,refI[STR_Name].GetRawString(), STR_LipSync) == 0)
        {
            num = refI[STR_Ids].GetVector()->GetSize();
            break;
        }
    }

    return num;
}

D_CubismIdHandle D_CubismModelSettingJson::GetLipSyncParameterId(int index)
{
    if (!IsExistLipSyncParameters())
    {
        return NULL;
    }

    for (int i = 0; i < _jsonValue[FrequentNode_Groups]->GetSize(); i++)
    {
        D_JsonValue& refI = (*_jsonValue[FrequentNode_Groups])[i];
        if (refI.IsNull() || refI.IsError())
        {
            continue;
        }

        if (CL_strcmp( DX_CHARCODEFORMAT_UTF8,refI[STR_Name].GetRawString(), STR_LipSync) == 0)
        {
            return LIVE2DSYS.s_cubismIdManager->GetId(refI[STR_Ids][index].GetRawString());
        }
    }
    return NULL;
}

#undef STR_Version				
#undef STR_FileReferences		
#undef STR_Groups				
#undef STR_Layout				
#undef STR_HitAreas				

#undef STR_Moc					
#undef STR_Textures				
#undef STR_Physics				
#undef STR_Pose					
#undef STR_Expressions			
#undef STR_Motions				

#undef STR_UserData				
#undef STR_Name					
#undef STR_FilePath				
#undef STR_Id					
#undef STR_Ids					
#undef STR_Target				

// Motions
#undef STR_Idle					
#undef STR_TapBody				
#undef STR_PinchIn				
#undef STR_PinchOut				
#undef STR_Shake				
#undef STR_FlickHead			
#undef STR_Parameter			

#undef STR_SoundPath			
#undef STR_FadeInTime			
#undef STR_FadeOutTime			

// Layout
#undef STR_CenterX				
#undef STR_CenterY				
#undef STR_X					
#undef STR_Y					
#undef STR_Width				
#undef STR_Height				

#undef STR_LipSync				
#undef STR_EyeBlink				

#undef STR_InitParameter		
#undef STR_InitPartsVisible		
#undef STR_Val					



















//�W���o�̖͂߂�l�����������̂ŃI�[�o�[�w�b�h�͑傫���B
D_csmString D_CubismString::GetFormatedString( const char* format, ... )
{
	int bufferSize = 2048;
	char* buffer = ( char* )( DXALLOC( sizeof( char )* bufferSize ) );

	va_list args;
	va_start( args, format );

	for(;;)
	{
		if( CL_vsnprintf( DX_CHARCODEFORMAT_UTF8, FALSE, DX_CHARCODEFORMAT_UTF8, WCHAR_T_CHARCODEFORMAT, buffer, bufferSize, format, args ) < bufferSize )
		{
			break;
		}
		else
		{
			// ������������Ȃ��ׁA�g�����Ċm�ۂ��Ȃ����B
			DXFREE( buffer );
			bufferSize *= 2;
			buffer = ( char* )( DXALLOC( sizeof( char )* bufferSize ) );
		}
	}
	va_end( args );

	D_csmString ret = buffer;
	DXFREE( buffer );

	return ret; // D_CubismString�^�ɂ���ĕԂ���邽�߃A�h���X��Ԃ��̂ŗǂ��B
}

bool D_CubismString::IsStartsWith(const char* text, const char* startWord)
{
    while (*startWord != '\0')
    {
        if (*text == '\0' || *(text++) != *(startWord++))
        {
            return false;
        }
    }
    return true;
}

float D_CubismString::StringToFloat(const char* string, int length, int position, int* outEndPos)
{
    int i = position;
    bool minus = false; //�}�C�i�X�t���O
    bool period = false;
    float v1 = 0;

    //�����̊m�F
    int c = string[i];
    if (c == '-')
    {
        minus = true;
        i++;
    }

    //�������̊m�F
    for (; i < length; i++)
    {
        c = string[i];
        if ('0' <= c && c <= '9')
        {
            v1 = v1 * 10 + (c - '0');
        }
        else if (c == '.')
        {
            period = true;
            i++;
            break;
        }
        else
        {
            break;
        }
    }

    //�������̊m�F
    if (period)
    {
        float mul = 0.1f;
        for (; i < length; i++)
        {
            c = string[i] & 0xFF;
            if ('0' <= c && c <= '9')
            {
                v1 += mul * (c - '0');
            }
            else
            {
                break;
            }
            mul *= 0.1f; //�ꌅ������
            if (!c) break;
        }
    }

    if (i == position)
    {
        //�ꕶ�����ǂݍ��܂Ȃ������ꍇ
        *outEndPos = -1; //�G���[�l������̂ŌĂяo�����œK�؂ȏ������s��
        return 0;
    }

    if (minus) v1 = -v1;

    *outEndPos = i;
    return v1;
}





















// �p�[�cID
const char* HitAreaPrefix = "HitArea";
const char* HitAreaHead = "Head";
const char* HitAreaBody = "Body";
const char* PartsIdCore = "Parts01Core";
const char* PartsArmPrefix = "Parts01Arm_";
const char* PartsArmLPrefix = "Parts01ArmL_";
const char* PartsArmRPrefix = "Parts01ArmR_";

// �p�����[�^ID
const char* ParamAngleX = "ParamAngleX";
const char* ParamAngleY = "ParamAngleY";
const char* ParamAngleZ = "ParamAngleZ";
const char* ParamEyeLOpen = "ParamEyeLOpen";
const char* ParamEyeLSmile = "ParamEyeLSmile";
const char* ParamEyeROpen = "ParamEyeROpen";
const char* ParamEyeRSmile = "ParamEyeRSmile";
const char* ParamEyeBallX = "ParamEyeBallX";
const char* ParamEyeBallY = "ParamEyeBallY";
const char* ParamEyeBallForm = "ParamEyeBallForm";
const char* ParamBrowLY = "ParamBrowLY";
const char* ParamBrowRY = "ParamBrowRY";
const char* ParamBrowLX = "ParamBrowLX";
const char* ParamBrowRX = "ParamBrowRX";
const char* ParamBrowLAngle = "ParamBrowLAngle";
const char* ParamBrowRAngle = "ParamBrowRAngle";
const char* ParamBrowLForm = "ParamBrowLForm";
const char* ParamBrowRForm = "ParamBrowRForm";
const char* ParamMouthForm = "ParamMouthForm";
const char* ParamMouthOpenY = "ParamMouthOpenY";
const char* ParamCheek = "ParamCheek";
const char* ParamBodyAngleX = "ParamBodyAngleX";
const char* ParamBodyAngleY = "ParamBodyAngleY";
const char* ParamBodyAngleZ = "ParamBodyAngleZ";
const char* ParamBreath = "ParamBreath";
const char* ParamArmLA = "ParamArmLA";
const char* ParamArmRA = "ParamArmRA";
const char* ParamArmLB = "ParamArmLB";
const char* ParamArmRB = "ParamArmRB";
const char* ParamHandL = "ParamHandL";
const char* ParamHandR = "ParamHandR";
const char* ParamHairFront = "ParamHairFront";
const char* ParamHairSide = "ParamHairSide";
const char* ParamHairBack = "ParamHairBack";
const char* ParamHairFluffy = "ParamHairFluffy";
const char* ParamShoulderY = "ParamShoulderY";
const char* ParamBustX = "ParamBustX";
const char* ParamBustY = "ParamBustY";
const char* ParamBaseX = "ParamBaseX";
const char* ParamBaseY = "ParamBaseY";
const char* ParamNONE = "NONE:";

// �O����`�t�@�C��(json)�ƍ��킹��
const char* MotionGroupIdle = "Idle"; // �A�C�h�����O
const char* MotionGroupTapBody = "TapBody"; // �̂��^�b�v�����Ƃ�

// �O����`�t�@�C��(json)�ƍ��킹��
const char* HitAreaNameHead = "Head";
const char* HitAreaNameBody = "Body";

BYTE* CreateBuffer( const BYTE/*wchar_t*/ * path, size_t* size )
{
	static char pathA[ 2048 ] ;
	void *Buffer ;
	LONGLONG fileSize ;
	DWORD_PTR fp ;

	fp = DX_FOPENW( ( char * )path ) ;
	if( fp == 0 )
	{
		ConvString( ( char * )path, -1, WCHAR_T_CHARCODEFORMAT, pathA, sizeof( pathA ), CHAR_CHARCODEFORMAT ) ;
		DXST_LOGFILEFMT_ADDA(( "Live2D Error : file open failed : %s", pathA )) ;
		return NULL ;
	}

	DX_FSEEK( fp, 0L, SEEK_END ) ;
	fileSize = DX_FTELL( fp ) ;
	DX_FSEEK( fp, 0L, SEEK_SET ) ;

	Buffer = DXALLOC( ( size_t )fileSize ) ;
	if( Buffer == NULL )
	{
		ConvString( ( char * )path, -1, WCHAR_T_CHARCODEFORMAT, pathA, sizeof( pathA ), CHAR_CHARCODEFORMAT ) ;
		DXST_LOGFILEFMT_ADDA(( "Live2D Error : alloc memory failed : %s", pathA )) ;
		return NULL ;
	}

	DX_FREAD( Buffer, ( int )fileSize, 1, fp ) ;
	DX_FCLOSE( fp ) ;

	if( size ) *size = ( size_t )fileSize ;

	return ( BYTE * )Buffer;
}

void DeleteBuffer(BYTE* buffer, const BYTE/*wchar_t*/ * /*path = ""*/)
{
	DxFree( buffer ) ;
}

D_LAppModel::D_LAppModel()
    : D_CubismUserModel()
    , _modelSetting(NULL)
    , _userTimeSeconds(0.0f)
    , _deleteModel(false)
{
//    if (DebugLogEnable)
//    {
//        _debugMode = true;
//    }
    
    _idParamAngleX = LIVE2DSYS.s_cubismIdManager->GetId(ParamAngleX);
    _idParamAngleY = LIVE2DSYS.s_cubismIdManager->GetId(ParamAngleY);
    _idParamAngleZ = LIVE2DSYS.s_cubismIdManager->GetId(ParamAngleZ);
    _idParamBodyAngleX = LIVE2DSYS.s_cubismIdManager->GetId(ParamBodyAngleX);
    _idParamEyeBallX = LIVE2DSYS.s_cubismIdManager->GetId(ParamEyeBallX);
    _idParamEyeBallY = LIVE2DSYS.s_cubismIdManager->GetId(ParamEyeBallY);
}

D_LAppModel::~D_LAppModel()
{
	ReleaseMotions();
	ReleaseExpressions();

	if( _modelSetting != NULL )
	{
		for( int i = 0; i < _modelSetting->GetMotionGroupCount(); i++ )
		{
			const char* group = _modelSetting->GetMotionGroupName( i );
			ReleaseMotionGroup( group );
		}

		D_CSM_DELETE( _modelSetting );
	}

	// �e�N�X�`���̊J�� 
	for( DWORD d = 0; d < _bindTextureId.GetSize(); d++ )
	{
		DeleteGraph( _bindTextureId[ d ], FALSE );
	}
	_bindTextureId.Clear();
}

bool D_LAppModel::LoadAssets( const BYTE/*wchar_t*/ * dir, const BYTE/*wchar_t*/ * fileName, int ASyncThread )
{
	_modelHomeDir = dir;

//	if (_debugMode)
//	{
//	    LogFileFmtAdd("[APP]load model setting: %s", fileName);
//	}

	size_t size;
	const D_csmStringW path = D_csmStringW( dir ) + fileName;

	BYTE* buffer = CreateBuffer( path.GetRawString(), &size );
	if( buffer == NULL )
	{
		return false ;
	}
	D_ICubismModelSetting* setting = D_CSM_NEW D_CubismModelSettingJson( buffer, size );
	DeleteBuffer( buffer, path.GetRawString() );

	if( SetupModel( setting ) == false )
	{
		return false ;
	}

	CreateRenderer( ASyncThread );

	SetupTextures( ASyncThread );

	return true ;
}


bool D_LAppModel::SetupModel( D_ICubismModelSetting* setting )
{
	_updating = true;
	_initialized = false;

	_modelSetting = setting;

	BYTE* buffer;
	size_t size;

	//Cubism Model
	if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, _modelSetting->GetModelFileName(), "" ) != 0 )
	{
		D_csmStringW path = _modelSetting->GetModelFileName();
		path = _modelHomeDir + path;

		//		if( _debugMode )
		//		{
		//			LogFileFmtAdd( "[APP]create model: %s", setting->GetModelFileName() );
		//		}

		buffer = CreateBuffer( path.GetRawString(), &size );
		if( buffer == NULL )
		{
			return false ;
		}
		LoadModel( buffer, size );
		DeleteBuffer( buffer, path.GetRawString() );
	}

	//Expression
	if( _modelSetting->GetExpressionCount() > 0 )
	{
		const int count = _modelSetting->GetExpressionCount();
		for( int i = 0; i < count; i++ )
		{
			D_csmStringW name = _modelSetting->GetExpressionName( i );
			D_csmStringW path = _modelSetting->GetExpressionFileName( i );
			path = _modelHomeDir + path;

			buffer = CreateBuffer( path.GetRawString(), &size );
			if( buffer == NULL )
			{
				return false ;
			}
			D_ACubismMotion* motion = LoadExpression( buffer, size, name.GetRawString() );

			if( _expressions.IsExist( name ) && _expressions[ name ] != NULL )
			{
				D_ACubismMotion::Delete( _expressions[ name ] );
				_expressions[ name ] = NULL;
			}
			_expressions[ name ] = motion;

			DeleteBuffer( buffer, path.GetRawString() );
		}
	}

	//Physics
	if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, _modelSetting->GetPhysicsFileName(), "" ) != 0 )
	{
		D_csmStringW path = _modelSetting->GetPhysicsFileName();
		path = _modelHomeDir + path;

		buffer = CreateBuffer( path.GetRawString(), &size );
		if( buffer == NULL )
		{
			return false ;
		}
		LoadPhysics( buffer, size );
		DeleteBuffer( buffer, path.GetRawString() );
	}

	//Pose
	if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, _modelSetting->GetPoseFileName(), "" ) != 0 )
	{
		D_csmStringW path = _modelSetting->GetPoseFileName();
		path = _modelHomeDir + path;

		buffer = CreateBuffer( path.GetRawString(), &size );
		if( buffer == NULL )
		{
			return false ;
		}
		LoadPose( buffer, size );
		DeleteBuffer( buffer, path.GetRawString() );
	}

	//EyeBlink
	if( _modelSetting->GetEyeBlinkParameterCount() > 0 )
	{
		_eyeBlink = D_CubismEyeBlink::Create( _modelSetting );
	}

	//Breath
	{
		_breath = D_CubismBreath::Create();
		D_csmVector<D_CubismBreath::BreathParameterData> breathParameters;

		breathParameters.PushBack( D_CubismBreath::BreathParameterData( _idParamAngleX, 0.0f, 15.0f, 6.5345f, 0.5f ) );
		breathParameters.PushBack( D_CubismBreath::BreathParameterData( _idParamAngleY, 0.0f, 8.0f, 3.5345f, 0.5f ) );
		breathParameters.PushBack( D_CubismBreath::BreathParameterData( _idParamAngleZ, 0.0f, 10.0f, 5.5345f, 0.5f ) );
		breathParameters.PushBack( D_CubismBreath::BreathParameterData( _idParamBodyAngleX, 0.0f, 4.0f, 15.5345f, 0.5f ) );
		breathParameters.PushBack( D_CubismBreath::BreathParameterData( LIVE2DSYS.s_cubismIdManager->GetId( ParamBreath ), 0.5f, 0.5f, 3.2345f, 0.5f ) );

		_breath->SetParameters( breathParameters );
	}

	// UserData
	if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, _modelSetting->GetUserDataFile(), "" ) != 0 )
	{
		D_csmStringW path = _modelSetting->GetUserDataFile();
		path = _modelHomeDir + path;
		buffer = CreateBuffer( path.GetRawString(), &size );
		if( buffer == NULL )
		{
			return false ;
		}
		LoadUserData( buffer, size );
		DeleteBuffer( buffer, path.GetRawString() );
	}

	// EyeBlinkIds
	{
		int eyeBlinkIdCount = _modelSetting->GetEyeBlinkParameterCount();
		for( int i = 0; i < eyeBlinkIdCount; ++i )
		{
			_eyeBlinkIds.PushBack( _modelSetting->GetEyeBlinkParameterId( i ) );
		}
	}

	// LipSyncIds
	{
		int lipSyncIdCount = _modelSetting->GetLipSyncParameterCount();
		for( int i = 0; i < lipSyncIdCount; ++i )
		{
			_lipSyncIds.PushBack( _modelSetting->GetLipSyncParameterId( i ) );
		}
	}

	//Layout
	D_csmMap<D_csmString, float> layout;
	_modelSetting->GetLayoutMap( layout );
	_modelMatrix->SetupFromLayout( layout );

	_model->SaveParameters();

	for( int i = 0; i < _modelSetting->GetMotionGroupCount(); i++ )
	{
		const char* group = _modelSetting->GetMotionGroupName( i );
		PreloadMotionGroup( group );
	}

	_motionManager->StopAllMotions();

	_updating = false;
	_initialized = true;

	return true ;
}

void D_LAppModel::PreloadMotionGroup( const char* group )
{
	const int count = _modelSetting->GetMotionCount( group );

	for( int i = 0; i < count; i++ )
	{
		//ex) idle_0
		D_csmStringW name = D_CubismString::GetFormatedString( "%s_%d", group, i ).GetRawString();
		D_csmStringW path = _modelSetting->GetMotionFileName( group, i );
		path = _modelHomeDir + path;

//		if (_debugMode)
//		{
//			LogFileFmtAdd("[APP]load motion: %s => [%s_%d] ", path.GetRawString(), group, i);
//		}

		BYTE* buffer;
		size_t size;
		buffer = CreateBuffer( path.GetRawString(), &size );
		if( buffer == NULL )
		{
			return ;
		}
		D_CubismMotion* tmpMotion = ( D_CubismMotion* )( LoadMotion( buffer, size, name.GetRawString() ) );

		float fadeTime = _modelSetting->GetMotionFadeInTimeValue( group, i );
		if( fadeTime >= 0.0f )
		{
			tmpMotion->SetFadeInTime( fadeTime );
		}

		fadeTime = _modelSetting->GetMotionFadeOutTimeValue( group, i );
		if( fadeTime >= 0.0f )
		{
			tmpMotion->SetFadeOutTime( fadeTime );
		}
		tmpMotion->SetEffectIds( _eyeBlinkIds, _lipSyncIds );

		if( _motions.IsExist( name ) && _motions[ name ] != NULL )
		{
			D_ACubismMotion::Delete( _motions[ name ] );
		}
		_motions[ name ] = tmpMotion;

		DeleteBuffer( buffer, path.GetRawString() );
	}
}

void D_LAppModel::ReleaseMotionGroup( const char* group ) const
{
	const int count = _modelSetting->GetMotionCount( group );
	for( int i = 0; i < count; i++ )
	{
		D_csmStringW voice = _modelSetting->GetMotionSoundFileName( group, i );
		if( CL_strcmp( WCHAR_T_CHARCODEFORMAT, ( const char * )voice.GetRawString(), "" ) != 0 )
		{
			D_csmStringW path = voice;
			path = _modelHomeDir + path;
		}
	}
}

void D_LAppModel::ReleaseMotions()
{
	for( D_csmMap<D_csmStringW, D_ACubismMotion*>::const_iterator iter = _motions.Begin(); iter != _motions.End(); ++iter )
	{
		D_ACubismMotion::Delete( iter->Second );
	}

	_motions.Clear();
}

void D_LAppModel::ReleaseExpressions()
{
	for( D_csmMap<D_csmStringW, D_ACubismMotion*>::const_iterator iter = _expressions.Begin(); iter != _expressions.End(); ++iter )
	{
		D_ACubismMotion::Delete( iter->Second );
	}

	_expressions.Clear();
}

void D_LAppModel::Update( float deltaTimeSeconds )
{
	//    const float deltaTimeSeconds = 1.0f / 60.0f;
	_userTimeSeconds += deltaTimeSeconds;

	_dragManager->Update( deltaTimeSeconds );
	_dragX = _dragManager->GetX();
	_dragY = _dragManager->GetY();

	// ���[�V�����ɂ��p�����[�^�X�V�̗L��
	bool motionUpdated = false;

	//-----------------------------------------------------------------
	_model->LoadParameters(); // �O��Z�[�u���ꂽ��Ԃ����[�h
	if( _motionManager->IsFinished() )
	{
		// ���[�V�����̍Đ����Ȃ��ꍇ�A�ҋ@���[�V�����̒����烉���_���ōĐ�����
//        StartRandomMotion(MotionGroupIdle, PriorityIdle);
	}
	else
	{
		motionUpdated = _motionManager->UpdateMotion( _model, deltaTimeSeconds ); // ���[�V�������X�V
	}
	_model->SaveParameters(); // ��Ԃ�ۑ�
	//-----------------------------------------------------------------

	// �܂΂���
	if( !motionUpdated )
	{
		if( _eyeBlink != NULL )
		{
			// ���C�����[�V�����̍X�V���Ȃ��Ƃ�
			_eyeBlink->UpdateParameters( _model, deltaTimeSeconds ); // �ڃp�`
		}
	}

	if( _expressionManager != NULL )
	{
		_expressionManager->UpdateMotion( _model, deltaTimeSeconds ); // �\��Ńp�����[�^�X�V�i���Εω��j
	}

	//�h���b�O�ɂ��ω�
	//�h���b�O�ɂ���̌����̒���
//	_model->AddParameterValue( _idParamAngleX, _dragX * 30 ); // -30����30�̒l��������
//	_model->AddParameterValue( _idParamAngleY, _dragY * 30 );
//	_model->AddParameterValue( _idParamAngleZ, _dragX * _dragY * -30 );

	//�h���b�O�ɂ��̂̌����̒���
//	_model->AddParameterValue( _idParamBodyAngleX, _dragX * 10 ); // -10����10�̒l��������

	//�h���b�O�ɂ��ڂ̌����̒���
//	_model->AddParameterValue( _idParamEyeBallX, _dragX ); // -1����1�̒l��������
//	_model->AddParameterValue( _idParamEyeBallY, _dragY );

	// �ċz�Ȃ�
	if( _breath != NULL )
	{
		_breath->UpdateParameters( _model, deltaTimeSeconds );
	}

	// �������Z�̐ݒ�
	if( _physics != NULL )
	{
		_physics->Evaluate( _model, deltaTimeSeconds );
	}

	// ���b�v�V���N�̐ݒ�
	if( _lipSync )
	{
		float value = 0; // ���A���^�C���Ń��b�v�V���N���s���ꍇ�A�V�X�e�����特�ʂ��擾����0?1�͈̔͂Œl����͂��܂��B

		for( DWORD i = 0; i < _lipSyncIds.GetSize(); ++i )
		{
			_model->AddParameterValue( _lipSyncIds[ i ], value, 0.8f );
		}
	}

	// �|�[�Y�̐ݒ�
	if( _pose != NULL )
	{
		_pose->UpdateParameters( _model, deltaTimeSeconds );
	}

	// ���[�U�[�ݒ�̃p�����[�^
	for( D_csmVector< D_LAppModelParameter >::iterator ite = _userParameters.Begin(); ite != _userParameters.End() ; ++ite )
	{
		_model->SetParameterValue( ( *ite ).parameterIndex, ( *ite ).parameterValue ) ;
	}

	_model->Update();

}

D_CubismMotionQueueEntryHandle D_LAppModel::StartMotion( const char* group, int no, int priority )
{
	bool autoDelete = false;
	D_CubismMotion* motion = NULL ;

	if( priority == D_CubismMotion_PriorityForce )
	{
		_motionManager->SetReservePriority( priority );
	}
	else
		if( !_motionManager->ReserveMotion( priority ) )
		{
			//		if( _debugMode )
			//		{
			//			LogFileFmtAdd( "[APP]can't start motion." );
			//		}
			return InvalidMotionQueueEntryHandleValue;
		}

	if( _modelSetting->GetMotionCount( group ) <= no )
	{
		return InvalidMotionQueueEntryHandleValue;
	}
	const D_csmStringW fileName = _modelSetting->GetMotionFileName( group, no );

	//ex) idle_0
	D_csmString name = D_CubismString::GetFormatedString( "%s_%d", group, no );
	if( _motions.IsExist( name.GetRawString() ) )
	{
		motion = ( D_CubismMotion* )( _motions[ name.GetRawString() ] );

		if( motion == NULL )
		{
			D_csmStringW path = fileName;
			path = _modelHomeDir + path;

			BYTE* buffer;
			size_t size;
			buffer = CreateBuffer( path.GetRawString(), &size );
			if( buffer == NULL )
			{
				return InvalidMotionQueueEntryHandleValue;
			}
			motion = ( D_CubismMotion* )LoadMotion( buffer, size, NULL );
			float fadeTime = _modelSetting->GetMotionFadeInTimeValue( group, no );
			if( fadeTime >= 0.0f )
			{
				motion->SetFadeInTime( fadeTime );
			}

			fadeTime = _modelSetting->GetMotionFadeOutTimeValue( group, no );
			if( fadeTime >= 0.0f )
			{
				motion->SetFadeOutTime( fadeTime );
			}
			motion->SetEffectIds( _eyeBlinkIds, _lipSyncIds );
			autoDelete = true; // �I�����Ƀ���������폜

			DeleteBuffer( buffer, path.GetRawString() );
		}
	}

	//voice
	D_csmStringW voice = _modelSetting->GetMotionSoundFileName( group, no );
	if( CL_strcmp( WCHAR_T_CHARCODEFORMAT, ( const char * )voice.GetRawString(), "" ) != 0 )
	{
		D_csmStringW path = voice;
		path = _modelHomeDir + path;
	}

//	if( _debugMode )
//	{
//		LogFileFmtAdd( "[APP]start motion: [%s_%d]", group, no );
//	}
	return  _motionManager->StartMotionPriority( motion, autoDelete, priority );
}

D_CubismMotionQueueEntryHandle D_LAppModel::StartRandomMotion( const char* group, int priority )
{
	if( _modelSetting->GetMotionCount( group ) == 0 )
	{
		return InvalidMotionQueueEntryHandleValue;
	}

	int no = NS_GetRand( _modelSetting->GetMotionCount( group ) - 1 );

	return StartMotion( group, no, priority );
}

void D_LAppModel::DoDraw()
{
	( ( D_CubismRenderer_DxLib * )GetRenderer() )->DrawModel() ;
}

void D_LAppModel::Draw( D_CubismMatrix44& matrix, bool isMultModelMatrix )
{
	D_CubismRenderer_DxLib* renderer = ( D_CubismRenderer_DxLib * )GetRenderer();

	if( _model == NULL || _deleteModel || renderer==NULL )
	{
		return;
	}

	// ���e�s��Ə�Z 
	if( isMultModelMatrix )
	{
		matrix.MultiplyByMatrix( _modelMatrix );
	}

	renderer->SetMvpMatrix( &matrix );

	DoDraw();
}

bool D_LAppModel::HitTest( const char* hitAreaName, float x, float y )
{
	// �������͓����蔻��Ȃ��B
	if( _opacity < 1 )
	{
		return false;
	}
	const int count = _modelSetting->GetHitAreasCount();
	for( int i = 0; i < count; i++ )
	{
		if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, _modelSetting->GetHitAreaName( i ), hitAreaName ) == 0 )
		{
			const D_CubismIdHandle drawID = _modelSetting->GetHitAreaId( i );
			return IsHit( drawID, x, y );
		}
	}
	return false; // ���݂��Ȃ��ꍇ��false
}

void D_LAppModel::SetUserParameter( int parameterIndex, float parameterValue )
{
	bool Flag = false ;
	for( D_csmVector< D_LAppModelParameter >::iterator ite = _userParameters.Begin(); ite != _userParameters.End() ; ++ite )
	{
		if( ( *ite ).parameterIndex == parameterIndex )
		{
			( *ite ).parameterValue = parameterValue ;
			break ;
		}
	}
	if( Flag == false )
	{
		D_LAppModelParameter NewParam ;

		NewParam.parameterIndex = parameterIndex ;
		NewParam.parameterValue = parameterValue ;
		_userParameters.PushBack( NewParam ) ;
	}
}

void D_LAppModel::SetExpression( const BYTE/*wchar_t*/ * expressionID )
{
	D_ACubismMotion* motion ;

	if( _expressions.IsExist( expressionID ) == false )
	{
		return ;
	}

	motion = _expressions[ expressionID ];
//	if( _debugMode )
//	{
//		LogFileFmtAdd( "[APP]expression: [%s]", expressionID );
//	}

	if( motion != NULL )
	{
		_expressionManager->StartMotionPriority( motion, false, D_CubismMotion_PriorityForce );
	}
	else
	{
//		if( _debugMode )
//		{
//			LogFileFmtAdd( "[APP]expression[%s] is null ", expressionID );
//		}
	}
}

void D_LAppModel::SetRandomExpression()
{
	if( _expressions.GetSize() == 0 )
	{
		return;
	}

	int no = NS_GetRand( _expressions.GetSize() - 1 );
	D_csmMap<D_csmStringW, D_ACubismMotion*>::const_iterator map_ite;
	int i = 0;
	for( map_ite = _expressions.Begin(); map_ite != _expressions.End(); map_ite++ )
	{
		if( i == no )
		{
			D_csmStringW name = ( *map_ite ).First;
			SetExpression( name.GetRawString() );
			return;
		}
		i++;
	}
}

void D_LAppModel::ReloadRenderer( int ASyncThread )
{
	DeleteRenderer();

	CreateRenderer( ASyncThread );

	SetupTextures( ASyncThread );
}

void D_LAppModel::SetupTextures( int ASyncThread )
{
#ifdef PREMULTIPLIED_ALPHA_ENABLE
	const bool isPreMult = true;
	// ������������Ă��Ȃ��e�N�X�`���𖳗�������ō�������������s���ꍇ��true�ɂ��� 
	const bool isTextureMult = false;
#else
	const bool isPreMult = false;
	const bool isTextureMult = false;
#endif

	_bindTextureId.Clear();

	for( int modelTextureNumber = 0; modelTextureNumber < _modelSetting->GetTextureCount(); modelTextureNumber++ )
	{
		// �e�N�X�`�������󕶎��������ꍇ�̓��[�h�E�o�C���h�������X�L�b�v
		if( CL_strcmp( DX_CHARCODEFORMAT_UTF8, _modelSetting->GetTextureFileName( modelTextureNumber ), "" ) == 0 )
		{
			continue;
		}

		//�e�N�X�`�������[�h���� 
		D_csmStringW texturePath = _modelSetting->GetTextureFileName( modelTextureNumber );
		texturePath = _modelHomeDir + texturePath;

		LOADGRAPH_GPARAM GParam ;
		Graphics_Image_InitLoadGraphGParam( &GParam ) ;
		GParam.LoadBaseImageGParam.ConvertPremultipliedAlpha = isTextureMult ? TRUE : FALSE ;
		GParam.CreateGraphGParam.NotUseTransColor = TRUE ;
		GParam.CreateGraphGParam.InitHandleGParam.MipMapCount = -1 ;
		int GraphHandle = Graphics_Image_LoadBmpToGraphW_UseGParam( &GParam, FALSE, -1, ( char * )texturePath.GetRawString(), TRUE, FALSE, 0, FALSE, ASyncThread ) ;
		if( GraphHandle >= 0 )
		{
			( ( D_CubismRenderer_DxLib * )GetRenderer() )->BindTexture( modelTextureNumber, GraphHandle );
			_bindTextureId.PushBack( GraphHandle );
		}
	}

	// premult�ł���Ȃ�ݒ� 
	( ( D_CubismRenderer_DxLib * )GetRenderer() )->IsPremultipliedAlpha( isPreMult );
}

void D_LAppModel::MotionEventFired( const D_csmString& /*eventValue*/ )
{
	//CubismLogInfo("%s is fired on D_LAppModel!!", eventValue.GetRawString());
}




#endif // DX_NON_LIVE2D_CUBISM4
