// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		iOS用モデルデータ制御プログラムヘッダファイル
// 
// 				Ver 3.24b
// 
// -------------------------------------------------------------------------------

#ifndef DX_MODELIOS_H
#define DX_MODELIOS_H

// インクルード ------------------------------------------------------------------
#include "../DxCompileConfig.h"

#ifndef DX_NON_MODEL

#include "../DxLib.h"
#include "../DxModel.h"
#include <OpenGLES/ES2/gl.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 --------------------------------------------------------------------

// 構造体定義 --------------------------------------------------------------------

// iOS用 モデルデータ管理用構造体
struct MV1_MODEL_MANAGE_IOS
{
	void *					CommonBuffer ;						// 主にシェイプ座標の更新で使用する汎用バッファ
	int						CommonBufferSize ;					// 主にシェイプ座標の更新で使用する汎用バッファのサイズ

	int						EnableLightNum ;					// 有効なライトの数
} ;

// iOS用 頂点バッファ環境依存情報
struct MV1_VERTEXBUFFER_PF
{
	GLuint					VertexBufferObject ;				// 頂点バッファ
	GLuint					IndexBufferObject ;					// インデックスバッファ
} ;

// iOS用 トライアングルリスト基データ環境依存情報
struct MV1_TRIANGLE_LIST_BASE_PF
{
	BYTE					SkinFreeBoneVertexBufferUpdate ;	// ９ボーン以上のスキニングメッシュ処理用頂点データを更新したかどうか( TRUE:更新済み  FALSE:未更新 )
	void *					SkinFreeBoneVertexBuffer ;			// ９ボーン以上のスキニングメッシュ処理用頂点データ
} ;

// iOS用 トライアングルリスト環境依存情報
struct MV1_TRIANGLE_LIST_PF
{
	void *					SkinFreeBoneVertexPositionBuffer ;	// ９ボーン以上のスキニングメッシュ処理用頂点座標データ
	GLuint					VertexBufferObject ;				// 頂点バッファ
} ;

// 内部大域変数宣言 --------------------------------------------------------------

extern MV1_MODEL_MANAGE_IOS MV1Man_iOS ;

// 関数プロトタイプ宣言-----------------------------------------------------------

// 汎用バッファ関数
extern	int				MV1_IOS_CommonBuffer_Setup( int Size ) ;						// 指定サイズの汎用バッファの準備を行う
extern	int				MV1_IOS_CommonBuffer_Terminate( void ) ;						// 汎用バッファの後始末を行う

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_MODEL

#endif // DX_MODELIOS_H
