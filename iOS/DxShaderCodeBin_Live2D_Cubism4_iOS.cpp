// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		Live2D Cubism4 用シェーダーバイナリ
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_LIVE2D_CUBISM4

// インクルード----------------------------------------------------------------
#include "../DxLib.h"
#include "../DxStatic.h"

// データ定義------------------------------------------------------------------

// #ifndef DX_NON_NAMESPACE
// 
// namespace DxLib
// {
// 
// #endif // DX_NON_NAMESPACE

// シェーダーファイルを圧縮したもの
int  DxShaderCodeBin_Live2D_Cubism4_IOSConvert ;
BYTE DxShaderCodeBin_Live2D_Cubism4_IOS[] = 
{
	0x6c,0x1c,0x00,0x00,0x6b,0x06,0x00,0x00,0xfe,0x44,0x58,0x08,0x00,0x3c,0x06,0x00,
	0x00,0x40,0x00,0xfe,0x10,0x00,0x30,0x16,0xfe,0x10,0x07,0x04,0x03,0xfe,0x10,0x07,
	0x1c,0x06,0xfe,0x10,0x07,0xa4,0x03,0x00,0x00,0xfe,0x00,0x12,0x0a,0xfe,0x18,0x27,
	0xfe,0x20,0x00,0x70,0x72,0x65,0x63,0x69,0x73,0x69,0x6f,0x6e,0x20,0x6d,0x65,0x64,
	0x69,0x75,0x6d,0x70,0x20,0x66,0x6c,0x6f,0x61,0x74,0x3b,0x0a,0x76,0x61,0x72,0x79,
	0x69,0x6e,0x67,0xfe,0x28,0x16,0x76,0x65,0x63,0x32,0x20,0x76,0x5f,0x74,0x65,0x78,
	0x43,0x6f,0x6f,0x72,0x64,0xfe,0x30,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x20,0xfe,
	0x00,0x20,0x34,0x20,0x76,0x5f,0x63,0x6c,0x69,0x70,0x50,0x6f,0x73,0x3b,0x0a,0x75,
	0x6e,0x69,0x66,0x6f,0x72,0x6d,0x20,0x6c,0x6f,0x77,0xfe,0x00,0x1e,0xfe,0x10,0x1f,
	0x75,0x5f,0x63,0x68,0x61,0x6e,0x6e,0x65,0x6c,0x46,0x6c,0x61,0x67,0xfe,0xa8,0x23,
	0x62,0x61,0x73,0x65,0x43,0x6f,0x6c,0x6f,0x72,0xfe,0x30,0x21,0x73,0x61,0x6d,0x70,
	0x6c,0x65,0x72,0x32,0x44,0x20,0x75,0x44,0x69,0x66,0x4d,0x61,0x70,0x54,0x65,0x78,
	0xfe,0x88,0x1d,0x4e,0x72,0x6d,0xfe,0x20,0x1d,0x76,0x6f,0x69,0x64,0x20,0x6d,0x61,
	0x69,0x6e,0x28,0x20,0xfe,0x08,0x0a,0x29,0x0a,0x7b,0x0a,0xfe,0x40,0xcf,0x34,0x20,
	0x20,0x63,0x6f,0x6c,0x5f,0xfe,0x00,0x41,0x61,0x73,0x6b,0xfe,0x00,0x7f,0x20,0x3d,
	0x20,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x32,0x44,0x28,0xfe,0x38,0x69,0x20,0x2c,
	0xfe,0x38,0xfa,0x20,0x29,0x20,0x2a,0xfe,0x50,0xa4,0xfe,0x08,0x3a,0xfe,0x30,0x00,
	0xfe,0x38,0x54,0x2e,0x72,0x67,0x62,0x20,0x3d,0xfe,0x68,0x11,0x20,0x2a,0xfe,0x48,
	0x12,0x61,0x20,0x3b,0xfe,0x68,0x98,0x6c,0x69,0x70,0x4d,0xfe,0x20,0x95,0xfe,0x08,
	0x98,0x28,0x20,0x31,0x2e,0x30,0x20,0x2d,0xfe,0x48,0xa0,0xfe,0x28,0xec,0xfe,0x00,
	0x9f,0xfe,0x19,0x79,0x01,0x2e,0x78,0x79,0x20,0x2f,0xfe,0x38,0x0e,0x77,0x20,0x29,
	0xfe,0x18,0xb1,0xfe,0x49,0x7a,0x01,0xfe,0x51,0xef,0x01,0x20,0xfe,0x00,0x87,0x56,
	0x61,0x6c,0xfe,0x28,0xc3,0x3d,0xfe,0x28,0x81,0x2e,0x72,0x20,0x2b,0xfe,0x30,0x0c,
	0x67,0xfe,0x40,0x0c,0x62,0xfe,0x40,0x0c,0x61,0xfe,0xc1,0x07,0x01,0xfe,0x20,0x53,
	0xfe,0x38,0x11,0x2a,0xfe,0x20,0x73,0x3b,0x20,0xfe,0x60,0x38,0x67,0x6c,0x5f,0x46,
	0x72,0x61,0x67,0xfe,0x09,0x5d,0x01,0xfe,0x68,0x38,0x3b,0x20,0x0a,0x7d,0x0a,0xfe,
	0xcd,0x13,0xb7,0x02,0xfe,0x20,0xd1,0xfe,0x20,0x7b,0x29,0xfe,0x68,0x41,0xfe,0xd1,
	0xc0,0x02,0xfe,0x65,0x08,0xbf,0x02,0xfe,0x99,0xbc,0x02,0xfe,0xd9,0xbb,0x02,0xfe,
	0xb9,0x77,0x02,0xfe,0x4d,0x03,0x74,0x02,0xfe,0x6d,0x02,0x71,0x02,0xfe,0xdd,0x01,
	0x6e,0x02,0xfe,0xcd,0x11,0x6b,0x02,0xfe,0x15,0x01,0x92,0x07,0xfe,0x71,0x62,0x02,
	0xfe,0xbd,0x01,0x63,0x02,0xfe,0xe5,0x01,0x1f,0x02,0xfe,0xf1,0x01,0x02,0x63,0xfe,
	0x18,0xb4,0xfe,0x85,0x01,0xf9,0x01,0xfe,0x58,0xf7,0xfe,0x00,0x4f,0x28,0xfe,0x10,
	0x50,0xfe,0x09,0x10,0x07,0xfe,0x09,0x0f,0x07,0x6f,0x72,0x2e,0x61,0x2c,0xfe,0x09,
	0x58,0x01,0xfe,0x00,0x09,0x20,0x29,0xfe,0x11,0xa1,0x08,0xfe,0x6d,0x04,0x13,0x01,
	0xfe,0x58,0xca,0xfe,0x7d,0x01,0x0d,0x01,0xfe,0x85,0x02,0x4b,0x04,0x6d,0x79,0xfe,
	0x2d,0x03,0x49,0x04,0xfe,0xc9,0x29,0x02,0xfe,0x08,0xc6,0x20,0x69,0x73,0x49,0x6e,
	0x73,0x69,0x64,0x65,0x20,0x3d,0xfe,0x09,0x01,0x03,0x73,0x74,0x65,0x70,0x28,0xfe,
	0x40,0x62,0x2e,0xfe,0x09,0x21,0x01,0xfe,0x08,0xb3,0x2e,0x78,0xfe,0x09,0xcd,0x03,
	0xfe,0x10,0x0b,0x77,0x20,0x29,0x0a,0x20,0x2a,0xfe,0x78,0x2f,0x79,0xfe,0x30,0x2f,
	0xfe,0x11,0xfd,0x03,0xfe,0x78,0x2f,0xfe,0x58,0x00,0xfe,0x88,0x5f,0x2c,0xfe,0x48,
	0x55,0x7a,0xfe,0xf8,0x3e,0xfe,0x48,0x6e,0xfe,0x50,0x3e,0x77,0xfe,0x09,0x43,0x06,
	0xfe,0x59,0x0f,0x02,0xfe,0x49,0x6c,0x01,0x20,0x2a,0xfe,0x05,0x01,0x1f,0x02,0x2e,
	0x61,0x20,0x2a,0xfe,0x29,0x32,0x01,0xfe,0x11,0x07,0x04,0x61,0x74,0x74,0x72,0x69,
	0x62,0x75,0x74,0x65,0xfe,0x41,0xe7,0x01,0x33,0x20,0x61,0xfe,0x09,0xe4,0x01,0xfe,
	0x30,0x1c,0xfe,0x49,0x25,0x02,0x61,0x54,0x65,0x78,0x55,0x56,0x30,0xfe,0x31,0x22,
	0x02,0x20,0xfe,0xf1,0x45,0x02,0x20,0xfe,0xe9,0x93,0x06,0xfe,0x58,0x21,0x75,0x5f,
	0x6d,0x61,0x74,0x72,0x69,0x78,0x5b,0x20,0x34,0x20,0x5d,0xfe,0xb8,0x25,0xfe,0x11,
	0x39,0x05,0xfe,0x38,0x29,0xfe,0x89,0x35,0x02,0xfe,0x10,0x34,0xfe,0x08,0x32,0xfe,
	0x00,0xda,0x34,0x3b,0x0a,0xfe,0x10,0x07,0x2e,0x78,0x20,0x3d,0xfe,0x08,0x09,0x2e,
	0x78,0xfe,0x28,0x12,0x79,0xfe,0x20,0x12,0x79,0xfe,0x28,0x12,0x7a,0xfe,0x20,0x12,
	0x7a,0xfe,0x28,0x12,0x77,0x20,0x3d,0xfe,0x01,0x47,0x06,0xfe,0x11,0x97,0x01,0x50,
	0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0xfe,0x08,0x4e,0x64,0x6f,0x74,0x28,0xfe,0x10,
	0x24,0xfe,0x01,0xc5,0x01,0xfe,0x20,0xc5,0x30,0x20,0x5d,0xfe,0x21,0xc5,0x01,0xfe,
	0x28,0x2d,0xfe,0x00,0x69,0x2d,0xfe,0x98,0x2f,0x31,0xfe,0x78,0x2f,0xfe,0x00,0x86,
	0xfe,0x90,0x2d,0x32,0xfe,0x78,0x2d,0xfe,0x00,0xa1,0xfe,0x90,0x2d,0x33,0xfe,0x18,
	0x2d,0xfe,0x39,0xea,0x06,0xfe,0x68,0x2b,0xfe,0x41,0x57,0x01,0xfe,0x20,0xbb,0xfe,
	0x30,0x2f,0xfe,0x00,0xb9,0xfe,0xb0,0x2f,0xfe,0x20,0xbb,0xfe,0x30,0x2f,0xfe,0x70,
	0xb9,0xfe,0x40,0x2f,0xfe,0x20,0xbd,0xfe,0x41,0x6b,0x07,0xfe,0xc0,0x2f,0xfe,0x30,
	0xbf,0xfe,0x29,0xdb,0x02,0x3d,0xfe,0x31,0x95,0x02,0xfe,0x38,0x16,0xfe,0x08,0xa7,
	0xfe,0x11,0xed,0x07,0xfe,0x40,0x14,0xfe,0x11,0xfa,0x02,0xfe,0xed,0x02,0xfb,0x02,
	0xfe,0x15,0x01,0xd9,0x02,0xfe,0x4d,0x09,0xaf,0x02,0xfe,0xcd,0x04,0xef,0x01,0xfe,
	0xa9,0xeb,0x04,0xfe,0x59,0x33,0x07,0xfe,0x55,0x06,0x0f,0x02,0xfe,0xc5,0x03,0x0e,
	0x02,0xfe,0x21,0x78,0x07,0xfe,0xe0,0xb4,0xfe,0x31,0x63,0x07,0xfe,0xa0,0x29,0xfe,
	0x31,0xb2,0x04,0xfe,0x10,0x29,0xfe,0xf0,0xab,0xfe,0x31,0x1a,0x08,0xfe,0xdd,0x02,
	0xb6,0x02,0x00,0x08,0x00,0x3b,0x08,0x4c,0x49,0x56,0x45,0x32,0x44,0x53,0x48,0x41,
	0x44,0x45,0x52,0x5f,0x50,0x49,0x58,0x45,0x4c,0x4d,0x41,0x53,0x4b,0x45,0x44,0x2e,
	0x46,0x4c,0x41,0x47,0x00,0x00,0x00,0x4c,0x69,0x76,0x65,0x32,0x44,0x53,0x68,0x61,
	0x64,0x65,0x72,0x5f,0x50,0x69,0x78,0x65,0x6c,0xfe,0x01,0x4e,0x0c,0x65,0x64,0x2e,
	0x66,0x6c,0x61,0x67,0xfe,0x09,0x47,0x16,0x9c,0x0a,0xfe,0xa0,0x43,0x49,0x4e,0x56,
	0x45,0x52,0x54,0xfe,0xf0,0x4b,0x49,0x6e,0x76,0x65,0x72,0x74,0xfe,0x30,0x53,0x0c,
	0x00,0xc5,0x0c,0xfe,0xe0,0x53,0x50,0x52,0x45,0x4d,0x55,0x4c,0x54,0xfe,0x20,0x5a,
	0xfe,0xe8,0x5b,0x50,0x72,0x65,0x6d,0x75,0x6c,0x74,0xfe,0x20,0x62,0x00,0x0a,0x00,
	0x64,0xfe,0xa8,0xb7,0xfe,0x24,0x01,0x5b,0xfe,0x60,0x53,0x08,0x00,0x4f,0xfe,0x79,
	0x4f,0x01,0x4e,0x4f,0x52,0x4d,0x41,0x4c,0xfe,0xb1,0x03,0x01,0x4e,0xfe,0x01,0x3e,
	0x0d,0x6c,0xfe,0x31,0x4f,0x01,0x78,0xfe,0x78,0x97,0xfe,0x10,0x43,0xfe,0xf0,0x97,
	0xfe,0x10,0x4b,0xfe,0x60,0x97,0x09,0x00,0x43,0x09,0xfe,0x70,0x53,0x53,0x45,0x54,
	0x55,0x50,0xfe,0x00,0xf0,0xfe,0xb8,0x4f,0x53,0x65,0x74,0x75,0xfe,0x11,0x3f,0x0e,
	0xfe,0x30,0xe3,0x21,0xfe,0x50,0xe3,0xfe,0x01,0x8e,0x01,0xfe,0x19,0x32,0x02,0xfe,
	0x00,0x0a,0xfe,0x68,0x47,0x56,0x65,0x72,0x74,0xfe,0x19,0x32,0x02,0xfe,0x01,0x89,
	0x01,0xfe,0x10,0x43,0x35,0xfe,0x70,0x43,0xfe,0x10,0xe2,0xfe,0xb0,0x43,0xfe,0x10,
	0xda,0xfe,0x38,0x43,0x29,0xfe,0x50,0xd3,0xfe,0x00,0x38,0xfe,0x30,0xd2,0xfe,0x08,
	0x46,0xfe,0x68,0x43,0xfe,0x30,0xce,0xfe,0x20,0x46,0xfe,0x08,0x00,0x10,0xfe,0x59,
	0x0b,0x19,0xfe,0xe0,0x00,0xff,0xfe,0x18,0x00,0xfe,0x20,0x0f,0x04,0xfe,0x18,0x07,
	0x20,0xfe,0x18,0x07,0x4a,0xba,0x23,0x42,0xcf,0x50,0xd5,0x01,0x8e,0xe4,0x30,0xa1,
	0x86,0x6b,0xfe,0x30,0x07,0xfe,0x20,0x2f,0xb7,0x02,0xfe,0x50,0x47,0xfe,0x20,0x00,
	0x48,0xfe,0x58,0x47,0x9f,0x62,0xb7,0x5a,0xe1,0x64,0xd5,0x01,0xd3,0xc3,0x5b,0xfe,
	0x08,0x3f,0xfe,0x20,0x07,0xb8,0xfe,0x18,0x3f,0xbf,0xfe,0x98,0x47,0x9c,0xfe,0x58,
	0x47,0xc0,0xeb,0x14,0x5b,0xfe,0x00,0x47,0xe6,0x10,0xb1,0xfe,0x08,0x3f,0xfe,0x20,
	0x07,0x78,0x05,0xfe,0x10,0x1f,0x6b,0xfe,0x98,0x47,0x00,0xfe,0x18,0xb1,0xfe,0x20,
	0x47,0x92,0xde,0x37,0xfe,0x08,0xd7,0x43,0x98,0x83,0xfe,0x08,0x3f,0xfe,0x20,0x07,
	0xe4,0x07,0xfe,0x10,0x1f,0x62,0xfe,0x98,0x47,0x54,0xfe,0x58,0x47,0x60,0x7e,0xf5,
	0x41,0xfe,0x00,0x47,0xeb,0x15,0xd8,0xa0,0xfe,0x00,0x3f,0xfe,0x20,0x07,0x48,0xfe,
	0x19,0x94,0x1a,0x11,0xfe,0x18,0x2f,0xfe,0x60,0x47,0x98,0xfe,0x58,0x47,0x30,0x73,
	0x0d,0xfe,0x08,0x8f,0x30,0xa3,0x04,0xfe,0x08,0x87,0xfe,0x20,0x07,0x5c,0x0b,0xfe,
	0x10,0x1f,0xd3,0xfe,0x59,0xaf,0x01,0xfe,0x20,0x00,0xec,0xfe,0x58,0x47,0xb1,0x03,
	0xad,0xfe,0x08,0x8f,0xe3,0x0f,0x4f,0xfe,0x08,0x87,0xfe,0x20,0x07,0x30,0x0c,0xfe,
	0x10,0x1f,0x1e,0xfe,0x98,0xd7,0x38,0xfe,0x18,0x17,0xfe,0x20,0x47,0xe0,0x4c,0xde,
	0xfe,0x08,0x47,0xd7,0x8a,0xa9,0xfe,0x08,0x3f,0xfe,0x20,0x07,0x50,0x0e,0xfe,0x10,
	0x1f,0xf9,0xfe,0x98,0x47,0x7c,0xfe,0x58,0x47,0x02,0xc0,0xc3,0xfe,0x08,0x47,0x6d,
	0xb4,0x7a,0xfe,0x08,0x3f,0xfe,0x20,0x07,0x4c,0x11,0xfe,0x10,0x1f,0xed,0xfe,0x99,
	0x1f,0x01,0xc0,0xfe,0x58,0x47,0x86,0x6e,0xb4,0x2b,0xfe,0x00,0x47,0xbe,0xab,0x20,
	0xfe,0x08,0x3f,0xfe,0x20,0x07,0x3c,0x13,0xfe,0x10,0x1f,0xb4,0xfe,0x98,0x8f,0xfe,
	0x61,0xe7,0x02,0xfe,0x21,0x2b,0x1c,0xfe,0x21,0x9f,0x02,
} ;

// #ifndef DX_NON_NAMESPACE
// 
// }
// 
// #endif // DX_NON_NAMESPACE

#endif // DX_NON_LIVE2D_CUBISM4
