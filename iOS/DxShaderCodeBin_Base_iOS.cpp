// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		固定機能パイプラインの代わり用シェーダーバイナリ
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

// インクルード----------------------------------------------------------------
#include "../DxLib.h"
#include "../DxStatic.h"

// データ定義------------------------------------------------------------------

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// シェーダーファイルを圧縮したもの
BYTE DxShaderCodeBin_Base_IOS[] = 
{
	0xbf,0x40,0x04,0x00,0xbf,0x11,0x00,0x00,0xff,0x85,0x02,0x95,0x02,0xa5,0x02,0xb5,
	0x04,0x2b,0x05,0xa1,0x05,0xa1,0x05,0x85,0x01,0x8c,0x03,0xb3,0x01,0xba,0x03,0xaa,
	0x01,0xb1,0x03,0x9a,0x01,0xa1,0x03,0x9d,0x01,0xa4,0x03,0xc2,0x01,0xc9,0x03,0xb2,
	0x01,0xb9,0x03,0x10,0x02,0x17,0x04,0x25,0x02,0x2c,0x04,0x4c,0x02,0x53,0x04,0x61,
	0x02,0x68,0x04,0x3e,0x02,0x45,0x04,0x53,0x02,0x5a,0x04,0x7a,0x02,0x81,0x04,0x8f,
	0x02,0x96,0x04,0x36,0x02,0x3d,0x04,0x4b,0x02,0x52,0x04,0x72,0x02,0x79,0x04,0x87,
	0x02,0x8e,0xff,0x08,0x2b,0x3a,0x02,0x41,0xff,0x08,0x2b,0x76,0x02,0x7d,0x04,0x28,
	0x02,0x2f,0x04,0x3d,0x02,0x44,0x04,0x64,0x02,0x6b,0x04,0x79,0x02,0x80,0x04,0x4e,
	0x02,0x55,0x04,0x63,0x02,0x6a,0x04,0x8a,0x02,0x91,0x04,0x9f,0x02,0xa6,0xff,0x08,
	0x1b,0x52,0x02,0x59,0xff,0x08,0x1b,0x8e,0x02,0x95,0x04,0x02,0x03,0x09,0x05,0x17,
	0x03,0x1e,0x05,0x3e,0x03,0x45,0x05,0x53,0x03,0x5a,0x05,0x30,0x03,0x37,0x05,0x45,
	0x03,0x4c,0x05,0x6c,0x03,0x73,0x05,0x81,0x03,0x88,0x05,0x28,0x03,0x2f,0x05,0x3d,
	0x03,0x44,0x05,0x64,0x03,0x6b,0x05,0x79,0x03,0x80,0xff,0x08,0x2b,0x2c,0x03,0x33,
	0xff,0x08,0x2b,0x68,0x03,0x6f,0x05,0x32,0x04,0x39,0x06,0x47,0x04,0x4e,0x06,0x6e,
	0x04,0x75,0x06,0x83,0x04,0x8a,0x06,0x58,0x04,0x5f,0x06,0x6d,0x04,0x74,0x06,0x94,
	0x04,0x9b,0x06,0xa9,0x04,0xb0,0xff,0x08,0x1b,0x5c,0x04,0x63,0xff,0x08,0x1b,0x98,
	0x04,0x9f,0x06,0x25,0x03,0x2c,0x05,0x3a,0x03,0x41,0x05,0x61,0x03,0x68,0x05,0x76,
	0x03,0x7d,0xff,0x28,0x47,0x8f,0x03,0x96,0x05,0xa4,0x03,0xab,0x05,0x4b,0x03,0x52,
	0x05,0x60,0x03,0x67,0x05,0x87,0x03,0x8e,0x05,0x9c,0x03,0xa3,0xff,0x08,0x2b,0x4f,
	0x03,0x56,0xff,0x08,0x2b,0x8b,0x03,0x92,0x05,0x59,0x04,0x60,0xff,0x08,0x6b,0x95,
	0x04,0x9c,0x06,0xaa,0x04,0xb1,0x06,0x7f,0x04,0x86,0xff,0x08,0x6b,0xbb,0x04,0xc2,
	0x06,0xd0,0x04,0xd7,0xff,0x28,0x87,0xff,0x00,0x1b,0xbf,0x04,0xc6,0x06,0xee,0x02,
	0xf5,0x04,0x03,0x03,0x0a,0x05,0x2a,0x03,0x31,0x05,0x3f,0x03,0x46,0x05,0x1c,0x03,
	0x23,0x05,0x31,0x03,0x38,0x05,0x58,0x03,0x5f,0x05,0x6d,0x03,0x74,0x05,0x14,0x03,
	0x1b,0x05,0x29,0x03,0x30,0x05,0x50,0x03,0x57,0x05,0x65,0x03,0x6c,0x05,0xff,0x00,
	0x2b,0x18,0x03,0x1f,0xff,0x08,0x2b,0x54,0x03,0x5b,0x05,0x1e,0x04,0x25,0x06,0x33,
	0x04,0x3a,0x06,0x5a,0x04,0x61,0x06,0x6f,0x04,0x76,0x06,0x44,0x04,0x4b,0x06,0xff,
	0x00,0x83,0x80,0x04,0x87,0xff,0x08,0x83,0xff,0x00,0x1b,0x48,0x04,0x4f,0xff,0x08,
	0x1b,0x84,0x04,0x8b,0x06,0x5b,0x01,0x58,0x01,0x5a,0x01,0xbc,0xff,0x18,0x01,0xb6,
	0xff,0x18,0x01,0x01,0x01,0x57,0x01,0x6b,0x03,0x9b,0x00,0xab,0x00,0x6d,0x00,0xff,
	0x00,0x00,0x61,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x20,0x68,0x69,0x67,0x68,
	0x70,0x20,0x76,0x65,0x63,0x34,0x20,0x61,0x50,0x6f,0x73,0x46,0x34,0x20,0x3b,0x0a,
	0xff,0x30,0x1d,0x6c,0x6f,0x77,0xff,0x20,0x1c,0x44,0x69,0x66,0x20,0x3b,0x20,0x20,
	0x20,0x0a,0x75,0x6e,0x69,0x66,0x6f,0x72,0x6d,0x20,0xff,0x40,0x3a,0x75,0x41,0x6e,
	0x74,0x69,0x56,0x50,0x4d,0x61,0x74,0x5b,0x20,0x34,0x20,0x5d,0x20,0x3b,0x0a,0x76,
	0x61,0x72,0x79,0x69,0x6e,0x67,0x20,0xff,0x38,0x42,0x76,0xff,0x08,0x42,0xff,0x30,
	0x19,0x6d,0x65,0x64,0x69,0x75,0x6d,0xff,0x08,0x1c,0x32,0x20,0x76,0x54,0x65,0x78,
	0x55,0x56,0x30,0xff,0xd8,0x1f,0x31,0xff,0x00,0x1f,0x6f,0x69,0x64,0x20,0x6d,0x61,
	0x69,0x6e,0x28,0x20,0xff,0x08,0x0a,0x29,0x0a,0x7b,0x0a,0xff,0x40,0x8b,0x6c,0x50,
	0x6f,0x73,0x20,0x3b,0xff,0x50,0x12,0x41,0x56,0xff,0x18,0x14,0xff,0x00,0x01,0xff,
	0x08,0x87,0x3d,0xff,0x18,0xd1,0x0a,0xff,0x20,0x79,0x2e,0x78,0x20,0x3d,0x20,0x30,
	0x2e,0xff,0x00,0x81,0xff,0x28,0x12,0x79,0xff,0x60,0x12,0x31,0xff,0x70,0x25,0x31,
	0xff,0x40,0x25,0xff,0x08,0x7b,0x3d,0xff,0x31,0x49,0x01,0xff,0x08,0x10,0x2e,0x77,
	0x20,0x3d,0x20,0x31,0x2e,0x30,0x20,0x2f,0xff,0x20,0x0e,0xff,0x20,0x18,0x78,0x20,
	0x2a,0x3d,0xff,0x60,0x13,0x79,0xff,0x78,0x13,0x7a,0xff,0x50,0x13,0x0a,0xff,0x18,
	0xd0,0xff,0x08,0x8c,0x64,0x6f,0x74,0x28,0xff,0x08,0x1b,0x2c,0xff,0x49,0x85,0x01,
	0x30,0x20,0x5d,0x20,0x29,0xff,0x08,0x40,0xff,0x10,0x2a,0xff,0x00,0xa4,0xff,0x98,
	0x2a,0x31,0xff,0x58,0x2a,0x7a,0xff,0xb0,0x2a,0x32,0xff,0x58,0x2a,0xff,0x00,0xd9,
	0xff,0x98,0x2a,0x33,0xff,0x20,0x2a,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,
	0x6f,0x6e,0x20,0x3d,0xff,0x31,0x8a,0x01,0x7d,0xff,0x39,0x66,0x02,0xff,0x75,0x01,
	0x84,0x02,0xff,0x78,0x3b,0x32,0x20,0x61,0xff,0x21,0x43,0x02,0xff,0xb5,0x06,0xa5,
	0x02,0xff,0x00,0x11,0xff,0x28,0x83,0xff,0x6d,0x0d,0x94,0x02,0xff,0xb8,0x20,0x31,
	0xff,0x6d,0x07,0xb5,0x02,0xff,0x28,0x14,0xff,0x00,0x78,0xff,0xed,0x09,0xa4,0x02,
	0x33,0xff,0x09,0x3a,0x01,0xff,0x59,0x65,0x02,0xff,0x39,0xe5,0x01,0xff,0x41,0xa7,
	0x02,0xff,0x81,0x05,0x02,0xff,0x21,0x42,0x02,0xff,0xa0,0x1f,0xff,0x39,0x45,0x02,
	0xff,0xd8,0x21,0xff,0xb9,0xc9,0x02,0x4c,0x57,0xff,0x28,0xe0,0xff,0xa8,0x23,0x56,
	0x69,0x65,0x77,0xff,0xf0,0x25,0x50,0x72,0x6f,0x6a,0xff,0x31,0x11,0x03,0xff,0x40,
	0x25,0xff,0x48,0xd3,0x75,0x54,0x65,0x78,0xff,0x08,0x26,0x36,0x20,0xff,0x08,0x27,
	0xff,0xe9,0xe0,0x02,0x20,0x20,0x20,0x6c,0x4c,0x6f,0x63,0x61,0xff,0x79,0xe8,0x02,
	0xff,0x00,0x1a,0x57,0x6f,0x72,0x6c,0x64,0xff,0x90,0x1a,0xff,0x00,0xb7,0xff,0x18,
	0x19,0xff,0x48,0x82,0xff,0x00,0x1b,0xff,0x09,0x17,0x01,0x54,0x65,0x6d,0x70,0xff,
	0x19,0x83,0x02,0xff,0x20,0x61,0x2e,0x78,0x79,0x7a,0x20,0x20,0xff,0x19,0xf6,0x02,
	0xff,0x00,0x1b,0xff,0x30,0x19,0x77,0xff,0x00,0x38,0xff,0x19,0xfd,0x02,0xff,0x10,
	0x34,0xff,0x20,0x7b,0x2e,0x78,0xff,0x18,0x1a,0xff,0x11,0x3e,0x02,0xff,0x20,0x31,
	0x2c,0xff,0x29,0x5e,0x01,0xff,0x31,0xc0,0x02,0xff,0x28,0x32,0x79,0xff,0xd8,0x32,
	0xff,0x31,0xc8,0x02,0xff,0x28,0x32,0xff,0x00,0x98,0xff,0xc0,0x32,0xff,0x31,0xd0,
	0x02,0xff,0x28,0x32,0xff,0x38,0xb3,0xff,0x10,0xb2,0xff,0x19,0x13,0x01,0xff,0x18,
	0xb1,0xff,0x28,0x4c,0xff,0x20,0x30,0x2c,0xff,0x39,0xed,0x01,0xff,0x30,0xb4,0xff,
	0x20,0x34,0xff,0x10,0xb3,0xff,0xc8,0x34,0xff,0x30,0xb6,0xff,0x20,0x34,0xff,0x10,
	0xb5,0xff,0xc8,0x34,0xff,0x30,0xb8,0xff,0x20,0x34,0xff,0x10,0xb7,0xff,0x38,0xb8,
	0xff,0x39,0x78,0x03,0xff,0x39,0x29,0x04,0xff,0x18,0x2e,0x2c,0xff,0x39,0x7d,0x02,
	0xff,0x28,0xb5,0xff,0x40,0x31,0xff,0x31,0x30,0x04,0xff,0x78,0x31,0xff,0x28,0xb2,
	0xff,0x40,0x31,0xff,0x31,0x37,0x04,0xff,0x78,0x31,0xff,0x28,0xaf,0xff,0x40,0x31,
	0xff,0x31,0x3e,0x04,0xff,0x78,0x31,0xff,0x29,0x40,0x04,0xff,0x19,0x8f,0x05,0xff,
	0x08,0xdb,0xff,0x21,0x92,0x05,0xff,0x31,0x8c,0x02,0xff,0x08,0x76,0xff,0x19,0x5f,
	0x02,0xff,0x38,0x15,0xff,0x21,0x73,0x05,0xff,0x55,0x02,0x1a,0x0b,0xff,0xed,0x01,
	0xb4,0x04,0xff,0x88,0x20,0xff,0x51,0x5e,0x07,0xff,0x2d,0x21,0xd7,0x04,0xff,0x38,
	0x15,0x78,0xff,0x00,0xd5,0xff,0x69,0x9c,0x0a,0xff,0x11,0xf2,0x04,0xff,0x10,0x88,
	0xff,0x28,0x2b,0x2c,0xff,0x31,0x76,0x03,0xff,0x29,0x1f,0x01,0xff,0x41,0x0e,0x05,
	0xff,0xb0,0x2e,0xff,0x29,0x1c,0x01,0xff,0x2d,0x04,0x2a,0x05,0xff,0xc8,0x22,0xff,
	0x11,0xe9,0x04,0xff,0xf5,0x24,0x4d,0x05,0xff,0x90,0x78,0xff,0x09,0x4e,0x10,0xff,
	0x41,0x68,0x05,0xff,0x2c,0x01,0x78,0xff,0x11,0x84,0x05,0xff,0xf0,0x78,0xff,0xfd,
	0x2c,0xa0,0x05,0x70,0x72,0x65,0x63,0x69,0x73,0xff,0x01,0x38,0x15,0xff,0x21,0xc5,
	0x03,0x66,0x6c,0x6f,0x61,0x74,0x3b,0xff,0x29,0x60,0x04,0xff,0x09,0x3a,0x17,0xff,
	0x08,0x13,0x20,0x75,0x41,0x54,0x65,0x73,0x74,0x52,0x65,0xff,0x01,0x57,0x01,0xff,
	0x48,0x1e,0xff,0x19,0xf8,0x03,0x75,0x41,0x64,0x64,0x43,0x6f,0x6c,0x6f,0x72,0xff,
	0x39,0x40,0x17,0xff,0x71,0x79,0x17,0xff,0x01,0x86,0x04,0x41,0x6c,0x70,0x68,0x61,
	0xff,0x00,0x4c,0x28,0xff,0x40,0x5f,0x69,0x6e,0xff,0x08,0x17,0xff,0x11,0xa4,0x04,
	0x69,0x66,0x28,0xff,0x28,0x10,0x3c,0x3d,0xff,0x38,0x7b,0x29,0x0a,0x20,0x7b,0x0a,
	0x20,0x20,0x64,0x69,0x73,0x63,0x61,0x72,0x64,0xff,0x00,0xf3,0x7d,0x0a,0x7d,0xff,
	0x91,0xe8,0x04,0xff,0x30,0x7c,0x6c,0xff,0x20,0x97,0xff,0x20,0x09,0x3d,0xff,0x20,
	0x8f,0xff,0x48,0x8b,0xff,0x08,0x1b,0x2e,0x61,0x20,0x29,0xff,0x28,0x28,0x2e,0x72,
	0x20,0x2b,0xff,0x00,0x7d,0xff,0x18,0xd9,0x2e,0xff,0x38,0x43,0x2e,0x67,0xff,0x50,
	0x1a,0x67,0xff,0x38,0x1a,0x62,0xff,0x50,0x1a,0x62,0xff,0x19,0xcf,0x02,0x46,0x72,
	0x61,0x67,0xff,0x20,0x7f,0xff,0x28,0x92,0xff,0xf5,0x01,0x84,0x01,0x69,0x6e,0x74,
	0xff,0x01,0xf4,0x02,0xff,0x10,0x1a,0x43,0x6d,0x70,0x4d,0x6f,0x64,0x65,0xff,0x05,
	0x03,0xa3,0x01,0xff,0x11,0xa5,0x01,0xff,0x50,0x76,0x3d,0x3d,0x20,0x32,0xff,0x21,
	0xa3,0x01,0xff,0x41,0xc3,0x01,0x3e,0xff,0x59,0xc3,0x01,0xff,0x08,0x20,0xff,0x41,
	0xc5,0x01,0x20,0x7d,0xff,0x01,0xc9,0x01,0x20,0x65,0x6c,0x73,0x65,0xff,0xa8,0x59,
	0x33,0xff,0x80,0x59,0x21,0xff,0x04,0x02,0x59,0x34,0xff,0x88,0xb3,0xff,0x21,0x53,
	0x01,0xff,0xc4,0x01,0x59,0x35,0xff,0x80,0x59,0xff,0x61,0xd1,0x02,0xff,0x8c,0x01,
	0x59,0x36,0xff,0x80,0x59,0x3d,0xff,0x04,0x02,0x59,0x37,0xff,0x88,0xb3,0xff,0x15,
	0x01,0x0d,0x01,0xff,0xdd,0x07,0x8b,0x03,0xff,0xf5,0x05,0x10,0x05,0xff,0x28,0x10,
	0xff,0x21,0x84,0x01,0x20,0x2d,0xff,0x09,0x20,0x07,0x29,0x20,0x2a,0xff,0x31,0x95,
	0x01,0x2b,0xff,0x21,0x33,0x07,0xff,0x45,0x1c,0x3e,0x05,0xff,0x6d,0x07,0xb9,0x03,
	0xff,0x9d,0x05,0x6c,0x05,0x2e,0x72,0x67,0x62,0xff,0x19,0x75,0x0c,0x2d,0xff,0x08,
	0x99,0xff,0x08,0x10,0xff,0x30,0x1e,0x61,0xff,0x09,0xc1,0x0c,0xff,0x08,0x18,0x61,
	0xff,0x0d,0x1c,0x63,0x05,0xff,0x7d,0x07,0xb0,0x03,0xff,0x25,0x06,0xc7,0x0a,0xff,
	0x09,0xa9,0x01,0x2a,0x3d,0x20,0x34,0xff,0xa5,0x1c,0xae,0x0a,0xff,0x75,0x06,0xa0,
	0x03,0xff,0x3d,0x09,0x13,0x15,0xff,0x51,0x02,0x02,0xff,0x31,0x40,0x07,0xff,0x45,
	0x1c,0x2b,0x15,0xff,0x75,0x03,0xa3,0x03,0xff,0x65,0x0a,0xd6,0x0f,0xff,0x65,0x19,
	0x65,0x05,0xff,0x3d,0x08,0xc8,0x03,0xff,0xe5,0x09,0x06,0x10,0xff,0xbd,0x19,0xe0,
	0x0a,0xff,0x6d,0x06,0xb8,0x03,0x73,0x61,0x6d,0x70,0x6c,0x65,0x72,0x32,0x44,0x20,
	0x20,0x75,0x53,0x72,0x63,0x54,0x65,0x78,0xff,0x61,0x97,0x03,0xff,0x45,0x02,0x87,
	0x05,0xff,0x18,0x18,0xff,0x39,0x40,0x3d,0xff,0x39,0xde,0x3c,0xff,0x95,0x03,0xa4,
	0x05,0x54,0x65,0x78,0xff,0x31,0xee,0x01,0xff,0x81,0x02,0x02,0xff,0x28,0x20,0x3d,
	0x20,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x32,0x44,0x28,0xff,0x21,0x2c,0x01,0x2c,
	0xff,0x28,0xc0,0xff,0x11,0x33,0x27,0xff,0x20,0x29,0xff,0x30,0x35,0x2a,0xff,0xd1,
	0x1c,0x0d,0xff,0x41,0xd6,0x01,0xff,0x05,0x04,0x46,0x12,0xff,0xc5,0x01,0x0f,0x02,
	0xff,0x6d,0x02,0xe5,0x05,0xff,0x05,0x02,0x2e,0x02,0xff,0x9d,0x11,0x02,0x06,0xff,
	0x3d,0x0a,0x16,0x04,0xff,0x5d,0x09,0x26,0x06,0xff,0x29,0x04,0x02,0xff,0xe9,0xcd,
	0x0d,0xff,0xf5,0x1f,0x3b,0x06,0xff,0x95,0x07,0x2b,0x04,0xff,0x7d,0x08,0x50,0x06,
	0xff,0x20,0x2c,0x2e,0xff,0x00,0x2e,0xff,0x11,0x42,0x35,0xff,0x30,0x13,0x67,0xff,
	0x78,0x13,0xff,0x19,0x4b,0x14,0xff,0xbd,0x20,0xb3,0x0c,0xff,0xad,0x09,0x52,0x04,
	0xff,0x3d,0x0b,0x9e,0x06,0xff,0x65,0x20,0x2b,0x0d,0xff,0x55,0x0a,0x67,0x04,0xff,
	0x8d,0x09,0xb8,0x13,0xff,0xcd,0x01,0xe9,0x36,0xff,0x25,0x20,0xd1,0x13,0xff,0x2d,
	0x08,0x44,0x04,0xff,0x05,0x0a,0x3b,0x1a,0xff,0x3d,0x22,0x97,0x06,0xff,0xd5,0x08,
	0x59,0x04,0xff,0x6d,0x0b,0xf8,0x13,0xff,0xfd,0x20,0xd3,0x06,0xff,0x1d,0x0b,0x80,
	0x04,0xff,0xe5,0x0b,0xf3,0x1a,0xff,0x1d,0x24,0x0f,0x07,0xff,0xbd,0x11,0x1f,0x0e,
	0xff,0x39,0xdd,0x3c,0xff,0x48,0x15,0xff,0x0d,0x21,0xa1,0x28,0xff,0xad,0x08,0x3c,
	0x04,0xff,0x8d,0x0a,0x72,0x06,0xff,0xb5,0x20,0x75,0x28,0xff,0x55,0x09,0x51,0x04,
	0xff,0x5d,0x0a,0x34,0x14,0xff,0x1d,0x22,0x4b,0x0d,0xff,0x8d,0x0a,0x78,0x04,0xff,
	0x6d,0x0c,0xea,0x06,0xff,0x45,0x22,0x39,0x36,0xff,0x3d,0x12,0xff,0x0d,0xff,0xf9,
	0x24,0x02,0xff,0xf9,0x7b,0x52,0xff,0x2d,0x20,0xae,0x2f,0xff,0x5d,0x07,0x2b,0x04,
	0xff,0x35,0x0a,0x2d,0x36,0xff,0x4d,0x21,0x65,0x06,0xff,0x05,0x08,0x40,0x04,0xff,
	0x75,0x0b,0x00,0x2f,0xff,0x2d,0x20,0xa1,0x06,0xff,0x55,0x0a,0x67,0x04,0xff,0x15,
	0x0c,0xc9,0x35,0xff,0x2d,0x23,0xdd,0x06,0xff,0x9d,0x10,0xbb,0x0d,0xff,0x15,0x04,
	0xac,0x23,0xff,0x5d,0x04,0xef,0x6c,0xff,0xe5,0x1c,0xdf,0x6a,0xff,0xd5,0x0d,0x1e,
	0x71,0xff,0xdd,0x03,0x03,0x23,0xff,0x0d,0x1e,0x6b,0x06,0xff,0x55,0x08,0x43,0x04,
	0xff,0x8d,0x0e,0x27,0x6b,0xff,0x2d,0x1d,0xa7,0x06,0xff,0x6d,0x0a,0x6a,0x04,0xff,
	0x35,0x0f,0x57,0x6b,0xff,0xed,0x1f,0xe3,0x06,0xff,0x3d,0x11,0xc7,0x0d,0xff,0xf5,
	0x04,0x72,0x3e,0xff,0x7d,0x1d,0xcd,0x06,0xff,0x6d,0x09,0x54,0x04,0xff,0x85,0x0e,
	0x67,0x50,0xff,0x3d,0x1f,0xb7,0x06,0xff,0xcd,0x12,0x37,0x1b,0xff,0xdd,0x22,0xab,
	0x0d,0xff,0x4d,0x0b,0x90,0x04,0xff,0x65,0x10,0xc7,0x50,0xff,0x1d,0x21,0x2f,0x07,
	0xff,0xed,0x10,0x5f,0x0e,0xff,0xbd,0x04,0x87,0x3f,0xff,0x45,0x1e,0x18,0x30,0xff,
	0x1d,0x08,0x43,0x04,0xff,0xfd,0x0d,0x27,0x51,0xff,0xb5,0x1e,0xae,0x36,0xff,0xed,
	0x10,0xaa,0x06,0xff,0x9d,0x06,0xef,0x4c,0xff,0x25,0x20,0xf4,0x2f,0xff,0xad,0x13,
	0xf8,0x06,0xff,0x95,0x21,0xdf,0x0d,0xff,0xc5,0x0a,0x94,0x04,0xff,0x40,0x1c,0x42,
	0x6c,0x65,0x6e,0x64,0xff,0x79,0xb3,0x04,0xff,0x11,0x63,0xe6,0x46,0x61,0x63,0x74,
	0x6f,0x72,0xff,0x20,0x77,0xff,0x95,0x03,0x62,0x07,0xff,0xa0,0x1c,0xff,0x29,0x9b,
	0xf9,0xff,0x7d,0x04,0x7f,0x07,0xff,0x28,0x13,0xff,0x21,0x5e,0x01,0xff,0x28,0x1a,
	0xff,0x50,0x10,0xff,0x21,0x9d,0xe5,0xff,0x41,0x0f,0x03,0xff,0x20,0x21,0xff,0xa1,
	0x11,0x03,0xff,0x18,0x34,0xff,0x68,0x38,0xff,0x29,0xe9,0x01,0xff,0x20,0x38,0x31,
	0xff,0x59,0x2a,0x11,0x28,0x20,0x28,0xff,0x58,0x7e,0xff,0x39,0x6e,0x1e,0xff,0x09,
	0x3c,0x8a,0xff,0x41,0xef,0x01,0xff,0x09,0x42,0x8a,0xff,0x50,0x1e,0xff,0x35,0x06,
	0x56,0x76,0xff,0xdd,0x02,0x01,0x03,0xff,0x55,0x03,0xd6,0x07,0xff,0x05,0x02,0x20,
	0x03,0xff,0xa5,0x12,0xf3,0x07,0xff,0xdd,0x0f,0x08,0x05,0xff,0xed,0x0e,0x0a,0x08,
	0xff,0x9d,0x06,0x61,0x77,0xff,0x1d,0x22,0x1f,0x08,0xff,0x95,0x09,0x1d,0x05,0xff,
	0x65,0x0c,0x34,0x08,0xff,0x05,0x02,0x8a,0x13,0xff,0xed,0x27,0x7b,0x10,0xff,0x55,
	0x0d,0x44,0x05,0xff,0xcd,0x10,0x82,0x08,0xff,0x4d,0x26,0xf3,0x10,0xff,0xfd,0x0d,
	0x59,0x05,0xff,0x1d,0x0f,0x64,0x19,0xff,0x35,0x07,0xef,0xab,0xff,0x4d,0x22,0x7d,
	0x19,0xff,0x2d,0x0a,0x36,0x05,0xff,0x95,0x0f,0xcb,0x21,0xff,0xcd,0x29,0x7b,0x08,
	0xff,0xd5,0x0a,0x4b,0x05,0xff,0xfd,0x10,0xa4,0x19,0xff,0xe5,0x26,0xb7,0x08,0xff,
	0xc5,0x0e,0x72,0x05,0xff,0x75,0x11,0x83,0x22,0xff,0xad,0x2b,0xf3,0x08,0xff,0xa5,
	0x17,0xe7,0x11,0xff,0x05,0x01,0xb7,0x62,0xff,0x3d,0x28,0xf9,0x33,0xff,0x55,0x0c,
	0x2e,0x05,0xff,0x1d,0x10,0x56,0x08,0xff,0x9d,0x26,0xcd,0x33,0xff,0xfd,0x0c,0x43,
	0x05,0xff,0x45,0x0e,0xe0,0x19,0xff,0xad,0x29,0x13,0x11,0xff,0x35,0x0e,0x6a,0x05,
	0xff,0xfd,0x11,0xce,0x08,0xff,0x2d,0x28,0x59,0x45,0xff,0xcd,0x19,0xc7,0x11,0xff,
	0xa5,0x02,0x16,0x03,0xff,0x65,0x06,0xbe,0xbb,0xff,0x55,0x22,0xea,0x3c,0xff,0x5d,
	0x09,0x1d,0x05,0xff,0xc5,0x0f,0x4d,0x45,0xff,0xdd,0x28,0x49,0x08,0xff,0x05,0x0a,
	0x32,0x05,0xff,0x05,0x11,0x3c,0x3c,0xff,0x15,0x26,0x85,0x08,0xff,0xfd,0x0d,0x59,
	0x05,0xff,0xa5,0x11,0xe9,0x44,0xff,0xbd,0x2a,0xc1,0x08,0xff,0xed,0x12,0x83,0x11,
	0xff,0x30,0x1a,0x50,0x72,0x65,0x6d,0x75,0xff,0x28,0x4a,0xff,0x78,0x1a,0xff,0x68,
	0x3b,0xff,0x80,0x16,0xff,0x0d,0x01,0xa3,0x03,0xff,0x50,0x6a,0xff,0x81,0xdc,0x03,
	0xff,0x21,0xa1,0x03,0x20,0xff,0x51,0xa3,0x03,0xff,0x91,0x15,0x04,0xff,0x80,0x87,
	0x2f,0xff,0x80,0x15,0x2e,0x61,0xff,0x60,0x43,0xff,0x0a,0x57,0x4e,0x01,0xff,0x98,
	0x43,0xff,0x08,0x2d,0xff,0x91,0x4e,0x04,0xff,0x80,0xc0,0xff,0x20,0x71,0xff,0x90,
	0x3e,0xff,0x18,0x68,0xff,0x80,0x3e,0xff,0x10,0x28,0xff,0xbd,0x05,0x28,0x2f,0xff,
	0x51,0x96,0x04,0xff,0x28,0x6c,0xff,0xd5,0x1e,0xa0,0x09,0xff,0x8d,0x18,0x38,0x06,
	0xff,0x9d,0x17,0x6a,0x0a,0xff,0x4d,0x04,0xff,0xb2,0xff,0xed,0x2d,0x7f,0x0a,0xff,
	0x65,0x0a,0x4d,0x06,0xff,0x15,0x15,0x94,0x0a,0xff,0x9d,0x07,0x98,0x89,0xff,0xd5,
	0x2b,0xbb,0x0a,0xff,0x25,0x0e,0x74,0x06,0xff,0x7d,0x19,0xe2,0x0a,0xff,0xcd,0x2f,
	0xb3,0x15,0xff,0xcd,0x0e,0x89,0x06,0xff,0x65,0x15,0x0c,0x0b,0xff,0x9d,0x06,0x3e,
	0x5a,0xff,0x25,0x2c,0xe1,0x0a,0xff,0x25,0x0d,0x5e,0x06,0xff,0xcd,0x18,0xb6,0x0a,
	0xff,0x1d,0x30,0xad,0x15,0xff,0xcd,0x0d,0x73,0x06,0xff,0xf5,0x16,0xa4,0x20,0xff,
	0x2d,0x33,0xd3,0x15,0xff,0x05,0x0f,0x9a,0x06,0xff,0xad,0x1a,0x2e,0x0b,0xff,0xad,
	0x31,0xf9,0x2b,0xff,0x4d,0x23,0x87,0x16,0xff,0x65,0x06,0x13,0x64,0xff,0x95,0x2e,
	0xa4,0x4c,0xff,0x2d,0x0a,0x4d,0x06,0xff,0x45,0x18,0x39,0x57,0xff,0x8d,0x32,0xa9,
	0x0a,0xff,0xd5,0x0a,0x62,0x06,0xff,0xb5,0x19,0x80,0x4c,0xff,0x95,0x2f,0xe5,0x0a,
	0xff,0xcd,0x0e,0x89,0x06,0xff,0x25,0x1a,0x8d,0x57,0xff,0x6d,0x34,0x21,0x0b,0xff,
	0xbd,0x13,0x43,0x16,0xff,0xbd,0x03,0x57,0x97,0xff,0xca,0xbe,0x0e,0x01,0x2a,0x3d,
	0x20,0x63,0x6c,0x61,0x6d,0x70,0xff,0x69,0x6a,0x03,0xff,0x09,0x4d,0x03,0xff,0x59,
	0x5e,0x03,0xff,0x69,0x71,0x03,0x62,0x2c,0x20,0x30,0x2e,0x30,0x2c,0xff,0x19,0x95,
	0xca,0xff,0xfd,0x25,0x83,0x9c,0xff,0x4d,0x0c,0x2b,0x05,0xff,0x8d,0x0d,0x50,0x08,
	0xff,0x79,0x61,0x0b,0xff,0x55,0x29,0x65,0x08,0xff,0x0d,0x0c,0x40,0x05,0xff,0x85,
	0x0e,0x4a,0x9c,0xff,0x05,0x29,0x07,0x11,0xff,0x6d,0x0e,0x67,0x05,0xff,0x6d,0x0f,
	0xc8,0x08,0xff,0xc5,0x28,0x7f,0x11,0xff,0x15,0x0f,0x7c,0x05,0xff,0x05,0x10,0x87,
	0x22,0xff,0x56,0x27,0x6e,0x04,0x01,0xff,0xbd,0x0d,0x59,0x05,0xff,0xad,0x10,0xe3,
	0x22,0xff,0x3d,0x28,0xc1,0x08,0xff,0x7d,0x0d,0x6e,0x05,0xff,0xe5,0x11,0x3f,0x23,
	0xff,0x36,0x29,0x82,0x04,0x01,0xff,0x3d,0x1a,0xfb,0x11,0xff,0x0d,0x06,0x1e,0x1e,
	0xff,0x1d,0x2a,0x39,0x09,0xff,0x4d,0x1a,0x73,0x12,0xff,0xee,0x01,0x97,0x70,0x01,
	0xff,0x6d,0x28,0xbf,0x2c,0xff,0x6d,0x0d,0x51,0x05,0xff,0xbd,0x0e,0x9c,0x08,0xff,
	0x15,0x29,0x71,0x35,0xff,0x15,0x0e,0x66,0x05,0xff,0xb6,0x0f,0x9c,0x05,0x01,0xff,
	0xe5,0x2a,0x3d,0x47,0xff,0x8d,0x1a,0xdb,0x11,0xff,0x2e,0x04,0x4c,0x8b,0x01,0xff,
	0x9d,0x2c,0x29,0x09,0xff,0x5d,0x1c,0xaf,0x47,0xff,0x5e,0x26,0xd0,0x06,0x01,0xff,
	0xf5,0x0c,0x40,0x05,0xff,0xdd,0x10,0x7d,0x47,0xff,0x45,0x27,0x8f,0x08,0xff,0xb5,
	0x0c,0x55,0x05,0xff,0x15,0x12,0x4b,0x47,0xff,0x3e,0x28,0xe4,0x06,0x01,0xff,0x75,
	0x19,0x97,0x11,0xff,0x3d,0x06,0x6e,0x41,0xff,0x25,0x29,0x07,0x09,0xff,0x9d,0x15,
	0x0f,0x12,0xff,0x95,0x04,0xff,0x91,0xff,0xa1,0xc6,0x03,0xff,0xed,0x01,0xff,0x91,
	0xff,0x68,0x44,0xff,0xd1,0x00,0x92,0xff,0xb1,0x73,0x04,0xff,0x15,0x01,0x01,0x92,
	0xff,0x48,0x3f,0xff,0xc9,0x02,0x92,0xff,0xfd,0x06,0x55,0x89,0xff,0x3d,0x24,0x5f,
	0x98,0xff,0x15,0x15,0x5f,0x06,0xff,0x5d,0x16,0xb8,0x0a,0xff,0x55,0x06,0x3c,0x32,
	0xff,0x1d,0x2d,0xcd,0x0a,0xff,0xdd,0x0c,0x74,0x06,0xff,0x35,0x15,0xe2,0x0a,0xff,
	0xb5,0x08,0xe9,0x8d,0xff,0xf5,0x2b,0x09,0x0b,0xff,0x3d,0x0f,0x9b,0x06,0xff,0x3d,
	0x18,0x30,0x0b,0xff,0x65,0x32,0x4f,0x16,0xff,0xe5,0x0f,0xb0,0x06,0xff,0x85,0x15,
	0x5a,0x0b,0xff,0xb5,0x07,0xfb,0x5c,0xff,0x45,0x2c,0x2f,0x0b,0xff,0x3d,0x0e,0x85,
	0x06,0xff,0x8d,0x17,0x04,0x0b,0xff,0xb5,0x32,0x49,0x16,0xff,0xe5,0x0e,0x9a,0x06,
	0xff,0x15,0x17,0x8e,0x21,0xff,0x65,0x34,0x6f,0x16,0xff,0x1d,0x10,0xc1,0x06,0xff,
	0x6d,0x19,0x7c,0x0b,0xff,0x45,0x34,0x31,0x2d,0xff,0x85,0x24,0x23,0x17,0xff,0x7d,
	0x07,0xf0,0x66,0xff,0x95,0x2f,0x94,0x59,0xff,0xfd,0x17,0x01,0xfd,0xff,0xe5,0x0b,
	0x34,0x53,0xff,0x15,0x31,0xf7,0x0a,0xff,0x85,0x0d,0x89,0x06,0xff,0xb5,0x1a,0xd3,
	0x59,0xff,0xed,0x2f,0x33,0x0b,0xff,0xe5,0x0f,0xb0,0x06,0xff,0x5d,0x1b,0xfd,0x59,
	0xff,0xf5,0x32,0x6f,0x0b,0xff,0x6d,0x16,0xdf,0x16,0xff,0x75,0x03,0xda,0x89,0xff,
	0x3d,0x01,0xda,0x0e,0xff,0x79,0x4c,0x04,0xff,0x9d,0x25,0xcf,0x8e,0xff,0xdd,0x0a,
	0xf4,0x04,0xff,0x9d,0x0d,0xe2,0x07,0xff,0xa1,0x4d,0x0b,0xff,0x75,0x27,0xf7,0x07,
	0xff,0x45,0x0a,0x09,0x05,0xff,0x75,0x0c,0x0c,0x08,0xff,0x05,0x03,0x06,0x1f,0xff,
	0x4d,0x26,0x33,0x08,0xff,0xa5,0x0c,0x30,0x05,0xff,0x7d,0x0f,0x5a,0x08,0xff,0x0d,
	0x27,0xa3,0x10,0xff,0x4d,0x0d,0x45,0x05,0xff,0x4d,0x0e,0xcf,0x20,0xff,0x0d,0x27,
	0xce,0xf6,0xff,0x4d,0x0c,0x22,0x05,0xff,0xf5,0x0e,0x2b,0x21,0xff,0x4d,0x28,0x53,
	0x08,0xff,0xb5,0x0b,0x37,0x05,0xff,0x2d,0x10,0x87,0x21,0xff,0x25,0x27,0x8f,0x08,
	0xff,0x15,0x0e,0x5e,0x05,0xff,0xd5,0x10,0xe3,0x21,0xff,0x2d,0x2a,0xcb,0x08,0xff,
	0x95,0x18,0x97,0x11,0xff,0x05,0x02,0xed,0x7e,0xff,0x9d,0x26,0x99,0x2a,0xff,0xa5,
	0x0b,0x1a,0x05,0xff,0xcd,0x0e,0x2e,0x08,0xff,0x5d,0x27,0xdd,0x32,0xff,0x4d,0x0c,
	0x2f,0x05,0xff,0x55,0x0e,0x68,0x19,0xff,0x0d,0x29,0xc3,0x10,0xff,0x85,0x0d,0x56,
	0x05,0xff,0xad,0x10,0xa6,0x08,0xff,0xed,0x28,0x19,0x44,0xff,0x2d,0x19,0x77,0x11,
	0xff,0xed,0x01,0xfc,0x2d,0xff,0x15,0x26,0xf4,0xf3,0xff,0x85,0x0b,0x09,0x05,0xff,
	0x25,0x0f,0x0d,0x44,0xff,0x55,0x27,0x21,0x08,0xff,0xed,0x0a,0x1e,0x05,0xff,0x5d,
	0x10,0xdb,0x43,0xff,0x2d,0x26,0x5d,0x08,0xff,0x4d,0x0d,0x45,0x05,0xff,0x05,0x11,
	0xa9,0x43,0xff,0x35,0x29,0x99,0x08,0xff,0xd5,0x13,0x33,0x11,0xff,0x5d,0x07,0x46,
	0x8b,0xff,0xae,0x04,0xd7,0x9e,0x01,0xff,0x25,0x05,0x4c,0x2e,0xff,0x05,0x27,0x6b,
	0x91,0xff,0x75,0x10,0x24,0x06,0xff,0x4d,0x16,0x42,0x0a,0xff,0x8d,0x04,0xd3,0x2f,
	0xff,0x0d,0x2d,0x57,0x0a,0xff,0x15,0x0b,0x39,0x06,0xff,0x25,0x15,0x6c,0x0a,0xff,
	0xed,0x06,0x2c,0x87,0xff,0xe5,0x2b,0x93,0x0a,0xff,0x75,0x0d,0x60,0x06,0xff,0x2d,
	0x18,0xba,0x0a,0xff,0x8d,0x30,0x63,0x15,0xff,0x1d,0x0e,0x75,0x06,0xff,0x75,0x15,
	0xe4,0x0a,0xff,0xed,0x05,0xc2,0x58,0xff,0x35,0x2c,0xb9,0x0a,0xff,0x75,0x0c,0x4a,
	0x06,0xff,0x7d,0x17,0x8e,0x0a,0xff,0xdd,0x30,0x5d,0x15,0xff,0x1d,0x0d,0x5f,0x06,
	0xff,0x05,0x17,0x2c,0x20,0xff,0x8d,0x32,0x83,0x15,0xff,0x55,0x0e,0x86,0x06,0xff,
	0x5d,0x19,0x06,0x0b,0xff,0x6d,0x32,0x59,0x2b,0xff,0xad,0x22,0x37,0x16,0xff,0xb5,
	0x05,0x97,0x62,0xff,0xbd,0x2d,0xe4,0x55,0xff,0xc5,0x1a,0x49,0xf2,0xff,0x45,0x07,
	0xbf,0x4f,0xff,0x05,0x31,0x81,0x0a,0xff,0xbd,0x0b,0x4e,0x06,0xff,0xdd,0x18,0x23,
	0x56,0xff,0xdd,0x2f,0xbd,0x0a,0xff,0x1d,0x0e,0x75,0x06,0xff,0x85,0x19,0x4d,0x56,
	0xff,0xe5,0x32,0xf9,0x0a,0xff,0xd5,0x06,0x8a,0x06,0xff,0x92,0xec,0x1f,0x04,0x50,
	0x6f,0x73,0x46,0x32,0xff,0x4a,0x49,0x20,0x04,0xff,0x66,0x02,0x02,0x0e,0x04,0xff,
	0x86,0x02,0xef,0x1f,0x04,0xff,0x2a,0x75,0x1f,0x04,0xff,0x1a,0xa1,0x1f,0x04,0x32,
	0x2e,0xff,0x01,0x17,0x07,0xff,0x10,0x14,0xff,0x0a,0xd8,0x09,0x04,0xff,0x10,0x14,
	0x79,0xff,0x28,0x14,0x7a,0xff,0x52,0x7e,0x22,0x04,0xff,0x42,0x8d,0x0a,0x04,0xff,
	0x6a,0xd7,0x1e,0x04,0xff,0x18,0x63,0xff,0x2e,0x01,0x2b,0x20,0x04,0xff,0x9d,0x02,
	0xe5,0x07,0xff,0x21,0x2b,0x01,0xff,0xd9,0x4a,0x01,0xff,0x45,0x01,0x49,0x01,0xff,
	0x2d,0x01,0x7f,0x84,0xff,0xd1,0xa5,0x04,0xff,0x19,0x6c,0x04,0xff,0x01,0xaa,0x05,
	0xff,0x48,0x36,0x2e,0x72,0x20,0x3e,0xff,0x01,0x65,0x01,0x30,0x31,0xff,0x89,0x32,
	0x0c,0xff,0x61,0x9b,0x02,0xff,0xe2,0x88,0x2a,0x03,0xff,0x45,0x08,0x57,0x01,0x3c,
	0x20,0x30,0x2e,0x39,0x39,0x39,0xff,0x91,0x57,0x01,0xff,0x0d,0x07,0x59,0x01,0xff,
	0x91,0x94,0x07,0x44,0xff,0x01,0x46,0x08,0xff,0x6d,0x01,0x5e,0x87,0xff,0x0d,0x01,
	0x86,0x01,0xff,0x45,0x01,0x7e,0x07,0xff,0x19,0xb7,0x07,0xff,0x28,0x8d,0xff,0x19,
	0x6f,0x31,0xff,0x49,0x7e,0x31,0xff,0x48,0x1f,0xff,0x12,0xda,0xee,0x03,0xff,0x11,
	0x8f,0x31,0xff,0x79,0x5e,0x06,0xff,0x59,0xcf,0x01,0xff,0x40,0xe5,0xff,0xc5,0x0c,
	0xbb,0x01,0xff,0x08,0xae,0xff,0x9d,0x0d,0xbb,0x01,0xff,0x09,0x72,0x09,0xff,0x9d,
	0x0d,0xbb,0x01,0xff,0x81,0xc1,0x8b,0xff,0x45,0x0a,0xbb,0x01,0xff,0x6a,0x8a,0x29,
	0x02,0xff,0x9d,0x01,0xbb,0x01,0xff,0x55,0x0b,0xe9,0x06,0xff,0x95,0x02,0xb5,0x01,
	0xff,0xe5,0x0a,0xe3,0x06,0xff,0x95,0x02,0xb5,0x01,0xff,0xe5,0x0a,0xdd,0x06,0xff,
	0x95,0x02,0xb5,0x01,0xff,0xf1,0xd7,0x06,0xff,0xd5,0x01,0xd4,0x11,0xff,0xf1,0xaf,
	0x11,0xff,0xdd,0x04,0x8f,0x11,0xff,0xed,0x01,0x00,0x01,0xff,0xe1,0xd3,0x12,0xff,
	0xa5,0x07,0xd1,0x12,0xff,0x05,0x03,0x2c,0x14,0xff,0xc8,0x22,0x32,0xff,0xf0,0x22,
	0x33,0xff,0xf0,0x22,0x34,0xff,0xf0,0x22,0x35,0xff,0xf0,0x22,0x36,0xff,0xf0,0x22,
	0x37,0xff,0x15,0x02,0xfe,0x14,0xff,0xb8,0x1f,0xff,0x01,0x77,0x01,0xff,0xc0,0x1f,
	0x33,0xff,0xd8,0x1f,0x34,0xff,0xd8,0x1f,0x35,0xff,0xd8,0x1f,0x36,0xff,0xd8,0x1f,
	0x37,0xff,0xa5,0x05,0xec,0x02,0xff,0x29,0x5f,0x01,0xff,0x20,0x14,0xff,0x01,0x69,
	0x01,0xff,0x29,0x54,0x01,0xff,0x20,0x14,0xff,0x01,0x5e,0x01,0xff,0x29,0x49,0x01,
	0xff,0x20,0x14,0xff,0x01,0x53,0x01,0xff,0x29,0x3e,0x01,0xff,0x20,0x14,0xff,0x01,
	0x48,0x01,0xff,0x29,0x33,0x01,0xff,0x20,0x14,0xff,0x01,0x3d,0x01,0xff,0x29,0x28,
	0x01,0xff,0x20,0x14,0xff,0x01,0x32,0x01,0xff,0xa5,0x01,0x78,0x07,0xff,0xe1,0x59,
	0x07,0xff,0x81,0x89,0x01,0xff,0x6d,0x01,0x25,0x14,0xff,0xd1,0x05,0x04,0xff,0x3d,
	0x04,0xed,0x01,0xff,0x26,0x01,0xce,0xff,0x03,0xff,0x08,0x97,0x75,0x43,0x6c,0x65,
	0x61,0xff,0x29,0x2b,0x1f,0xff,0x05,0x01,0x29,0x01,0xff,0x50,0x31,0x7d,0x0a,
} ;

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

