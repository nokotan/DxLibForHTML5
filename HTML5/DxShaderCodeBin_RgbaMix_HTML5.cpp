// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		RGBAブレンド用シェーダーバイナリ
// 
// 				Ver 3.23 
// 
// -------------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_FILTER

// インクルード----------------------------------------------------------------
#include "../DxLib.h"
#include "../DxStatic.h"

// データ定義------------------------------------------------------------------

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// シェーダーファイルを圧縮したもの
BYTE DxShaderCodeBin_RgbaMix_HTML5[] = 
{
	0x00,0x0f,0x03,0x00,0xb2,0x0d,0x00,0x00,0xff,0x39,0x01,0xd2,0x01,0xff,0xc4,0x1f,
	0x03,0x70,0x72,0x65,0x63,0x69,0x73,0x69,0x6f,0x6e,0x20,0x6d,0x65,0x64,0x69,0x75,
	0x6d,0x70,0x20,0x66,0x6c,0x6f,0x61,0x74,0x3b,0x0a,0x75,0x6e,0x69,0x66,0x6f,0x72,
	0x6d,0xff,0x28,0x16,0x76,0x65,0x63,0x34,0x20,0x75,0x52,0x47,0x42,0x41,0x53,0x65,
	0x6c,0x65,0x63,0xff,0x38,0x21,0x73,0x61,0x6d,0x70,0x6c,0x65,0x72,0x32,0x44,0x20,
	0x20,0x75,0x53,0x72,0x63,0x54,0x65,0x78,0x20,0xff,0x90,0x1c,0x42,0x6c,0x65,0x6e,
	0x64,0xff,0x10,0x1e,0x76,0x61,0x72,0x79,0x69,0x6e,0x67,0xff,0x40,0x5d,0x32,0x20,
	0x76,0x54,0x65,0x78,0x55,0x56,0x30,0xff,0xd0,0x1e,0x31,0xff,0x00,0x1e,0x6f,0x69,
	0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,0x20,0xff,0x08,0x0a,0x29,0x0a,0x7b,0x0a,0xff,
	0x50,0xa8,0x43,0x6f,0x6c,0x6f,0x72,0x3b,0x0a,0xff,0x10,0x07,0x20,0x3d,0x20,0x74,
	0x65,0x78,0x74,0x75,0x72,0x65,0x32,0x44,0x28,0xff,0x20,0xa3,0x2c,0xff,0x28,0x6e,
	0x29,0x20,0xff,0x38,0x28,0xff,0x08,0x07,0x2e,0x72,0x72,0x72,0xff,0x00,0x3d,0xff,
	0x00,0x01,0x67,0x6c,0x5f,0x46,0x72,0x61,0x67,0xff,0x48,0x1f,0x3b,0x0a,0x7d,0x0a,
	0xff,0x25,0x08,0x38,0x01,0x69,0x66,0x28,0xff,0x10,0x2c,0x2e,0x61,0x20,0x3c,0x20,
	0x30,0x2e,0x30,0x30,0x31,0x20,0x29,0x0a,0x20,0x7b,0x0a,0x20,0xff,0x18,0x16,0xff,
	0x00,0x45,0x30,0x2e,0xff,0x00,0x9c,0xff,0x20,0x11,0x67,0xff,0x68,0x11,0x62,0xff,
	0x30,0x11,0x7d,0x0a,0x20,0x65,0x6c,0x73,0x65,0xff,0x48,0x41,0x67,0xff,0x00,0x1f,
	0xff,0x30,0x0b,0x2f,0xff,0x20,0x70,0xff,0x10,0x2e,0xff,0x99,0xba,0x01,0xff,0x30,
	0x2f,0x2a,0xff,0x20,0x1b,0xff,0x00,0x30,0xff,0xf5,0x08,0xd1,0x01,0xff,0x69,0x4f,
	0x01,0x67,0xff,0xb5,0x0d,0x0a,0x03,0xff,0x11,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0x62,0xff,0xb5,0x0d,0x0a,0x03,0xff,0x11,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,
	0x11,0x36,0x01,0xff,0x8d,0x0d,0x0a,0x03,0xff,0x11,0xba,0x01,0xff,0x2d,0x0a,0x0a,
	0x03,0x67,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x19,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x19,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x19,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x19,0xba,0x01,0xff,0x2d,0x0a,0x0a,0x03,0x62,0xff,0xb5,0x0d,0x2b,0x0c,
	0xff,0x19,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x19,
	0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x19,0xba,0x01,
	0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x19,0xba,0x01,0xff,0x2d,
	0x0a,0x0a,0x03,0x61,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x19,0xba,0x01,0xff,0x35,0x0a,
	0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x19,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x19,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x19,0xba,0x01,0xff,0x25,0x0a,0x0a,0x03,0x67,0xff,0xb5,0x0d,
	0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,
	0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x21,
	0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x21,0xba,0x01,
	0xff,0x2d,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,
	0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x67,0xff,0xb5,
	0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x67,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,
	0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x67,
	0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x67,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,
	0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,
	0x30,0x67,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x62,0xff,0xb5,0x0d,0xaf,0x30,
	0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x21,
	0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x21,0xba,0x01,
	0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x21,0xba,0x01,0xff,0x2d,
	0x0a,0x0a,0x03,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,
	0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x62,0xff,0xb5,0x0d,0xaf,
	0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,
	0x5d,0x0a,0xaf,0x30,0x62,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,
	0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x62,0xff,0xb5,
	0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x62,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,
	0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x62,
	0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x61,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,
	0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x21,0xba,0x01,
	0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x21,0xba,0x01,0xff,0x35,
	0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x21,0xba,0x01,0xff,0x2d,0x0a,0x0a,
	0x03,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,
	0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x61,0xff,0xb5,0x0d,0xaf,0x30,0xff,
	0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,
	0xaf,0x30,0x61,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,
	0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x61,0xff,0xb5,0x0d,0xaf,
	0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,
	0x5d,0x0a,0xaf,0x30,0x61,0xff,0xb5,0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,
	0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0x61,0xff,0xb5,
	0x0d,0xaf,0x30,0xff,0x21,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x55,0x0a,0xaf,0x30,0x67,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,
	0xff,0x35,0x0a,0x0a,0x03,0xff,0xa5,0x0d,0x2b,0x0c,0xff,0x29,0xba,0x01,0xff,0x35,
	0x0a,0x0a,0x03,0xff,0xa5,0x0d,0x2b,0x0c,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,
	0x03,0xff,0xa5,0x0d,0x2b,0x0c,0xff,0x29,0xba,0x01,0xff,0x2d,0x0a,0x0a,0x03,0xff,
	0xad,0x0d,0xaf,0x30,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,
	0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x67,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,
	0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,
	0x67,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,
	0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x67,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,
	0xaf,0x30,0x67,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,
	0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x67,0xff,0xb5,0x0d,0xbf,
	0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,
	0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,
	0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x67,0xff,0xb5,0x0d,
	0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,
	0xff,0x5d,0x0a,0xbf,0xc2,0x67,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,
	0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,
	0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,
	0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,
	0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x67,0xff,
	0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,
	0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x67,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,
	0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,
	0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,
	0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,
	0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,
	0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,
	0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,
	0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,
	0x67,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,
	0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x67,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,
	0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,
	0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,
	0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x62,0xff,0xb5,0x0d,0xbf,0xc2,
	0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xa5,0x0d,0x2b,0x0c,0xff,0x29,
	0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xa5,0x0d,0x2b,0x0c,0xff,0x29,0xba,0x01,
	0xff,0x35,0x0a,0x0a,0x03,0xff,0xa5,0x0d,0x2b,0x0c,0xff,0x29,0xba,0x01,0xff,0x2d,
	0x0a,0x0a,0x03,0xff,0xad,0x0d,0xaf,0x30,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,
	0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x62,0xff,0xb5,0x0d,0xbf,
	0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,
	0x55,0x0a,0xaf,0x30,0x62,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,
	0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x62,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x55,0x0a,0xaf,0x30,0x62,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,
	0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x62,
	0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,
	0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,
	0x62,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,
	0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x62,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,
	0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,
	0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,
	0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,
	0xbf,0xc2,0x62,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,
	0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x62,0xff,0xb5,0x0d,0xbf,
	0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,
	0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,
	0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,
	0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,
	0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,
	0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,
	0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,
	0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,
	0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,
	0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,
	0x5d,0x0a,0xbf,0xc2,0x62,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,
	0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x62,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,
	0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,
	0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,
	0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x61,0xff,
	0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xa5,0x0d,
	0x2b,0x0c,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xa5,0x0d,0x2b,0x0c,
	0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xa5,0x0d,0x2b,0x0c,0xff,0x29,
	0xba,0x01,0xff,0x2d,0x0a,0x0a,0x03,0xff,0xad,0x0d,0xaf,0x30,0xff,0x29,0xba,0x01,
	0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x61,
	0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x61,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,
	0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,
	0x30,0x61,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,0x0a,0xaf,0x30,0x61,0xff,0xb5,0x0d,0xbf,0xc2,
	0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x55,
	0x0a,0xaf,0x30,0x61,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,
	0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,
	0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,
	0x5d,0x0a,0xbf,0xc2,0x61,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,
	0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x61,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,
	0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,
	0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,
	0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,
	0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,
	0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x61,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,
	0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x61,
	0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,
	0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,
	0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,
	0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,
	0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,
	0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,
	0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,
	0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,
	0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,0xc2,0x61,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,
	0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xad,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xbf,
	0xc2,0x61,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,
	0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,
	0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,
	0xff,0xb5,0x0d,0x2b,0x0c,0xff,0x5d,0x0a,0xaf,0x30,0xff,0xb5,0x0d,0xbf,0xc2,0xff,
	0x29,0xba,0x01,0xff,0x35,0x0a,0x0a,0x03,0xff,0xb5,0x0d,0x2b,0x0c,0xff,0xa5,0x01,
	0xaf,0x30,
} ;

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_FILTER

