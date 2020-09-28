// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Nintendo Switch�p�f�[�^�^�C�v��`�w�b�_�t�@�C��
// 
// 				Ver 3.22a
// 
// -------------------------------------------------------------------------------

#ifndef DX_DATATYPENSW_H
#define DX_DATATYPENSW_H

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"

// #ifndef DX_NON_NAMESPACE
// 
// namespace DxLib
// {
// 
// #endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �Z���T�[
#define DX_ANDROID_SENSOR_ACCELEROMETER			(0)		// �����x�Z���T�[
#define DX_ANDROID_SENSOR_MAGNETIC_FIELD		(1)		// ���E�Z���T�[
#define DX_ANDROID_SENSOR_GYROSCOPE				(2)		// �W���C���X�R�[�v�Z���T�[
#define DX_ANDROID_SENSOR_LIGHT					(3)		// �Ɠx�Z���T�[
#define DX_ANDROID_SENSOR_PROXIMITY				(4)		// �ߐڃZ���T�[
#define DX_ANDROID_SENSOR_PRESSURE				(5)		// �����Z���T�[
#define DX_ANDROID_SENSOR_AMBIENT_TEMPERATURE	(6)		// ���x�Z���T�[
#define DX_ANDROID_SENSOR_NUM					(7)

// ���ˑ��L�[���[�h�Ȃ�
#ifndef FASTCALL
#define FASTCALL
#endif

typedef void *		HBITMAP ;
typedef void *		HINSTANCE ;
typedef char *		LPSTR ;

#ifndef TRUE
#define TRUE		(1)
#endif

#ifndef FALSE
#define FALSE		(0)
#endif

#ifndef BOOL
#define BOOL		int
#endif

#ifndef TCHAR
#ifdef UNICODE
#define TCHAR		wchar_t
#else
#define TCHAR		char
#endif
#endif

#ifndef _T
#ifdef UNICODE
#define _T( x )		L ## x
#else
#define _T( x )		x
#endif
#endif

#ifndef TEXT
#ifdef UNICODE
#define TEXT( x )	L ## x
#else
#define TEXT( x )	x
#endif
#endif

#ifndef NEAR
#define NEAR
#endif

#ifndef FAR
#define FAR
#endif

#ifndef WINAPI
#define WINAPI
#endif

#ifndef LONG
#define LONG		int
#endif

typedef int *		LPLONG ;

#ifndef LONGLONG
#define LONGLONG	int64_t
#endif

#ifndef ULONGLONG
#define ULONGLONG	uint64_t
#endif

#ifndef BYTE
#define BYTE		uint8_t
#endif

#ifndef WORD
#define WORD		uint16_t
#endif

#ifndef DWORD
#define DWORD		uint32_t
#endif

typedef uint32_t *	LPDWORD ;

#ifndef DWORD_PTR
#ifdef __LP64__
#define DWORD_PTR	uint64_t
#else
#define DWORD_PTR	uint32_t
#endif
#endif

#ifndef LONG_PTR
#define LONG_PTR	int32_t
#endif

#define _FPCLASS_SNAN		0x0001
#define _FPCLASS_QNAN		0x0002
#define _FPCLASS_NINF		0x0004
#define _FPCLASS_NN			0x0008
#define _FPCLASS_ND			0x0010
#define _FPCLASS_NZ			0x0020
#define _FPCLASS_PZ			0x0040
#define _FPCLASS_PD			0x0080
#define _FPCLASS_PN			0x0100
#define _FPCLASS_PINF		0x0200

#define FILE_ATTRIBUTE_DIRECTORY			0x00000010

#define BI_RGB				0L
#define BI_RLE8				1L
#define BI_RLE4				2L
#define BI_BITFIELDS		3L

#define MAKEFOURCC( ch0, ch1, ch2, ch3 )                              \
			( ( DWORD )( BYTE )( ch0 )        | ( ( DWORD )( BYTE )( ch1 ) << 8  ) |   \
			( ( DWORD )( BYTE )( ch2 ) << 16) | ( ( DWORD )( BYTE )( ch3 ) << 24 ) )


#define DX_READSOUNDFUNCTION_AT9					(1 << ( DX_READSOUNDFUNCTION_DEFAULT_NUM + 0 ))		// ATRAC9 ���g�p�����ǂݍ��ݏ���
	
// �\���̒�` --------------------------------------------------------------------

typedef struct tagRECT
{
	LONG				left ;
	LONG				top ;
	LONG				right ;
	LONG				bottom ;
} RECT, *PRECT, NEAR *NPRECT, FAR *LPRECT ;

typedef struct tagPOINT
{
	LONG				x ;
	LONG				y ;
} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT ;


typedef struct tagSIZE
{
	LONG				cx ;
	LONG				cy ;
} SIZE, *PSIZE, *LPSIZE ;

#pragma pack(push, 2)
typedef struct tagBITMAPFILEHEADER
{
	WORD				bfType ;
	DWORD				bfSize ;
	WORD				bfReserved1 ;
	WORD				bfReserved2 ;
	DWORD				bfOffBits ;
} BITMAPFILEHEADER, FAR *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER ;
#pragma pack(pop)

typedef struct tagRGBQUAD
{
	BYTE				rgbBlue ;
	BYTE				rgbGreen ;
	BYTE				rgbRed ;
	BYTE				rgbReserved ;
} RGBQUAD ;

typedef struct tagBITMAPINFOHEADER
{
	DWORD				biSize ;
	LONG				biWidth ;
	LONG				biHeight ;
	WORD				biPlanes ;
	WORD				biBitCount ;
	DWORD				biCompression ;
	DWORD				biSizeImage ;
	LONG				biXPelsPerMeter ;
	LONG				biYPelsPerMeter ;
	DWORD				biClrUsed ;
	DWORD				biClrImportant ;
} BITMAPINFOHEADER, FAR *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER ;

typedef struct tagBITMAPINFO
{
	BITMAPINFOHEADER	bmiHeader ;
	RGBQUAD				bmiColors[ 1 ] ;
} BITMAPINFO, FAR *LPBITMAPINFO, *PBITMAPINFO ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// #ifndef DX_NON_NAMESPACE
// 
// }
// 
// #endif // DX_NON_NAMESPACE

#endif // DX_DATATYPENSW_H
