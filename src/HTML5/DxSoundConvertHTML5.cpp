//-----------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用サウンドデータ変換プログラム
// 
//  	Ver 3.24b
// 
//-----------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_SOUND

// インクルード----------------------------------------------------------------
#include "DxSoundConvertHTML5.h"
#include "../DxSoundConvert.h"
#include "../DxSystem.h"
#include "../DxHeap.h"
#include "../DxMemory.h"
#include "../DxStatic.h"
#include "../DxLog.h"

#include <emscripten.h>
#include <emscripten/threading.h>
#include <emscripten/proxying.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義------------------------------------------------------------------

// 型定義----------------------------------------------------------------------

typedef struct tagDECODEDAUDIO
{
	void* SrcBuffer;
	int SrcLength;

	int ChannelNum;
	int DecodedId;
	int SamplingRate;
	int Length;
} DECODEDAUDIO;

typedef struct SOUNDCONV_BROWSER
{
	int							BufferId;
	int							ReadPos;
} SOUNDCONV_BROWSER;

// データ宣言------------------------------------------------------------------

SOUNDCONVERTDATA_HTML5 GSoundConvertData_HTML5 ;

// 関数プロトタイプ宣言 -------------------------------------------------------

// プログラム------------------------------------------------------------------

// 初期化・終了関数

static int InitializeDecodeAudioOnBrowser() {
	return MAIN_THREAD_EM_ASM_INT({
		if (!Module["DxLib"]) {
			Module["DxLib"] = {};
		}

		Module["DxLib"].audioContext = new AudioContext();
		Module["DxLib"].NextDecodedAudioId = 1;
		Module["DxLib"].DecodedAudio = [];

		return 0;
	});
}

// サウンドデータ変換処理の環境依存の初期化を行う
extern	int InitializeSoundConvert_PF( void )
{
	InitializeDecodeAudioOnBrowser();
	return 0 ;
}

static int TerminateDecodeAudioOnBrowser() {
	return MAIN_THREAD_EM_ASM_INT({
		if (Module["DxLib"]) {
			delete Module["DxLib"].audioContext;
			delete Module["DxLib"].NextDecodedAudioId;
			delete Module["DxLib"].DecodedAudio;
		}

		return 0;
	});
}

// サウンドデータ変換処理の環境依存の終了処理を行う
extern	int TerminateSoundConvert_PF( void )
{
	TerminateDecodeAudioOnBrowser();
	
	// 正常終了
	return 0 ;
}








#ifdef PROXY_TO_PTHREAD
EM_JS(void, SetupDecodeAudioOnBrowserJs, (em_proxying_ctx* ctx, void* Data),
#else
EM_JS(void, SetupDecodeAudioOnBrowserJs, (DECODEDAUDIO* Data), 
#endif
	{
		function DecodeAudioImpl(wakeUp) {
			const SrcBuffer = HEAPU32[(Data>>2)+0];
			const Length = HEAPU32[(Data>>2)+1];

			const audioData = HEAPU8.slice(SrcBuffer, SrcBuffer + Length);
			const onSuccess = function(decoded) {
				const id = Module["DxLib"].NextDecodedAudioId++;
				Module["DxLib"].DecodedAudio[id] = decoded;

				HEAP32[(Data>>2)+2] = decoded.numberOfChannels;
				HEAP32[(Data>>2)+3] = id;
				HEAPU32[(Data>>2)+4] = decoded.sampleRate;
				HEAPU32[(Data>>2)+5] = decoded.length*decoded.numberOfChannels;

				wakeUp();
			};

			const onFailure = function() {
				HEAP32[(Data>>2)+2] = 0;
				HEAP32[(Data>>2)+3] = -1;
				HEAPU32[(Data>>2)+4] = 0;
				HEAPU32[(Data>>2)+5] = 0;

				wakeUp();
			};

			Module["DxLib"].audioContext.decodeAudioData(audioData.buffer, onSuccess, onFailure); 
		}

	#ifdef ASYNCIFY
		Asyncify.handleSleep(DecodeAudioImpl);
	#elif defined(PROXY_TO_PTHREAD)
		DecodeAudioImpl(function() {
			_emscripten_proxy_finish(ctx);
		});
	#endif
	})

static int SetupDecodeAudioOnBrowser(DECODEDAUDIO* Data) 
{
#ifdef ASYNCIFY
	SetupDecodeAudioOnBrowserJs(Data);
#elif defined(PROXY_TO_PTHREAD)
	auto defaultQueue = emscripten_proxy_get_system_queue();
	emscripten_proxy_sync_with_ctx(
		defaultQueue,
		emscripten_main_runtime_thread_id(),
		&SetupDecodeAudioOnBrowserJs,
		(void*)Data);
#endif

	return Data->DecodedId;
}

// (環境依存処理)変換処理のセットアップ( [戻] -1:エラー )
extern	int SetupSoundConvert_PF( SOUNDCONV *SoundConv, STREAMDATA *Stream, int DisableReadSoundFunctionMask )
{
	DWORD_PTR sp;
	STREAMDATASHRED *sstr;
	size_t FileSize;
	BYTE *AudioData = NULL;
	DECODEDAUDIO DecodedAudio;
	SOUNDCONV_BROWSER* SoundConvBrowser;

	{
		sstr = &Stream->ReadShred ;
		sp   = Stream->DataPoint ;

		// ファイルサイズを得る
		sstr->Seek( sp, 0, STREAM_SEEKTYPE_END ) ;
		FileSize = ( size_t )sstr->Tell( sp ) ;
		sstr->Seek( sp, 0, STREAM_SEEKTYPE_SET ) ;
	}

	// デコード後のデータを格納するメモリ領域の確保
	AudioData = (BYTE *)DXALLOC( ( size_t )FileSize ) ;	
	if( AudioData == NULL ) goto ERR ;
	if( ( sstr->Read( AudioData, sizeof(BYTE), FileSize, sp ) ) <= 0 ) goto ERR ;

	{
		DecodedAudio.SrcBuffer = AudioData;
		DecodedAudio.SrcLength = FileSize;
	}

	if( SetupDecodeAudioOnBrowser(&DecodedAudio) == -1) goto ERR ;

	SoundConv->HeaderPos = 0;
	SoundConv->HeaderSize = 0;
	SoundConv->DataPos = 0;
	SoundConv->DataSize = DecodedAudio.Length ;

	SoundConv->OutFormat.nSamplesPerSec  = DecodedAudio.SamplingRate ;
	SoundConv->OutFormat.nChannels       = DecodedAudio.ChannelNum ;
	SoundConv->OutFormat.wBitsPerSample  = 16 ;
	SoundConv->OutFormat.wFormatTag      = WAVE_FORMAT_PCM ;
	SoundConv->OutFormat.nBlockAlign     = ( WORD )( SoundConv->OutFormat.wBitsPerSample  * SoundConv->OutFormat.nChannels / 8 ) ;
	SoundConv->OutFormat.nAvgBytesPerSec = SoundConv->OutFormat.nBlockAlign * SoundConv->OutFormat.nSamplesPerSec ;

	SoundConvBrowser = (SOUNDCONV_BROWSER*)SoundConv->ConvFunctionBuffer;
	SoundConvBrowser->BufferId = DecodedAudio.DecodedId;
	SoundConvBrowser->ReadPos = 0;

	// 変換後のＰＣＭデータを一時的に保存するメモリ領域のサイズをセット
	SoundConv->DestDataSize = ( LONGLONG )SoundConv->OutFormat.nAvgBytesPerSec ;

	// タイプセット
	SoundConv->MethodType = SOUND_METHODTYPE_BROWSER ;

	DXFREE(AudioData);

	return 0 ;
ERR:
	DXFREE(AudioData);

	return -1 ;
}

// (環境依存処理)変換処理の位置を変更する( サンプル単位 )
extern	int SetSampleTimeSoundConvert_PF(    SOUNDCONV *SoundConv, LONGLONG SampleTime )
{
	int res = -1 ;

	return res ;
}

int ConvertDecodeAudioOnBrowser(int BufferId, void* Buffer, size_t ReadSize, int ReadPos) {
	return MAIN_THREAD_EM_ASM_INT({
		const BufferId = $0;
		const Buffer = $1;
		const ReadSize = $2;
		const ReadPos = $3;

		const decoded = Module["DxLib"].DecodedAudio[BufferId];

		if (!decoded) {
			return -1;
		}

		const readSizeByChannel = ReadSize / decoded.numberOfChannels;
		const readPosByChannel = ReadPos / decoded.numberOfChannels;

		for (let i = 0; i < decoded.numberOfChannels; i++) {
			const rawData = decoded.getChannelData(i);
			for (let j = readPosByChannel; j < readPosByChannel + readSizeByChannel; j++) {
				HEAP16[(Buffer>>1)+j*decoded.numberOfChannels+i]=rawData[j] * 32767;
			}
		}

		return 0;
	}, BufferId, Buffer, ReadSize, ReadPos);
}

// (環境依存処理)変換後のバッファにデータを補充する
extern	int ConvertProcessSoundConvert_PF(  SOUNDCONV *SoundConv )
{
	LONGLONG readsize, pos ;
	SOUNDCONV_BROWSER* SoundConvBrowser;

	SoundConvBrowser = (SOUNDCONV_BROWSER*)SoundConv->ConvFunctionBuffer;
	
	pos = SoundConvBrowser->ReadPos - SoundConv->DataPos ;
	if( pos >= SoundConv->DataSize ) return -1 ;

	// 読み込むデータサイズを決定する
	readsize = SoundConv->DataSize - pos ;
	if( SoundConv->DestDataSize < readsize ) readsize = SoundConv->DestDataSize ;

	ConvertDecodeAudioOnBrowser(SoundConvBrowser->BufferId, SoundConv->DestData, readsize, pos);
	SoundConv->DestDataValidSize = readsize ;
	SoundConvBrowser->ReadPos += readsize ;

	return 0 ;
}

int DeleteDecodeAudioOnBrowser(int BufferId) {
	return MAIN_THREAD_EM_ASM_INT({
		delete Module["DxLib"].DecodedAudio[$0];
		return 0;
	}, BufferId);
}

// (環境依存処理)変換処理の後始末を行う
extern	int TerminateSoundConvert_PF(        SOUNDCONV *SoundConv )
{
	SOUNDCONV_BROWSER* SoundConvBrowser;

	SoundConvBrowser = (SOUNDCONV_BROWSER*)SoundConv->ConvFunctionBuffer;

	DeleteDecodeAudioOnBrowser(SoundConvBrowser->BufferId);

	return 0 ;
}

// (環境依存処理)変換後の大凡のデータサイズを得る
extern	LONGLONG GetSoundConvertDestSize_Fast_PF( SOUNDCONV *SoundConv )
{
	DWORD_PTR sp;
	STREAMDATASHRED *sstr;
	size_t FileSize;

	{
		sstr = &SoundConv->Stream.ReadShred ;
		sp   = SoundConv->Stream.DataPoint ;

		// ファイルサイズを得る
		sstr->Seek( sp, 0, STREAM_SEEKTYPE_END ) ;
		FileSize = ( size_t )sstr->Tell( sp ) ;
		sstr->Seek( sp, 0, STREAM_SEEKTYPE_SET ) ;
	}

	return FileSize ;
}





















#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_SOUND

