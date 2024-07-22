// ----------------------------------------------------------------------------
//
//		�c�w���C�u�����@�����g�p�֘A�p�w�b�_�t�@�C��
//
//				Ver 3.24d
//
// ----------------------------------------------------------------------------

// ���d�C���N���[�h�h�~�p�}�N��
#ifndef DX_STATIC_H
#define DX_STATIC_H

// �C���N���[�h --------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` ----------------------------------

#ifdef VISUALCPP_2005
#define RST  __restrict
#else
#define RST
#endif

// �\���̒�` --------------------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

// �f�[�^��` --------------------------------------------

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

// �֐��錾 -----------------------------------------------

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// ���C�u�����֐������Ăяo���ȗ����}�N�� -----------------


// DxSystem.cpp�֐��v���g�^�C�v�錾

#if defined( DX_THREAD_SAFE ) || defined( DX_THREAD_SAFE_NETWORK_ONLY )

// �������I���n�֐�
extern	int			NS_DxLib_Init( void ) ;													// ���C�u�����������֐�
extern	int			NS_DxLib_End( void ) ;														// ���C�u�����g�p�̏I���֐�

// ���b�Z�[�W�����֐�
extern	int			NS_ProcessMessage( void ) ;												// �E�C���h�E�Y�̃��b�Z�[�W���[�v�ɑ��鏈�����s��

#else

// �������I���n�֐�
#define NS_DxLib_Init	DxLib_Init
#define NS_DxLib_End	DxLib_End

// ���b�Z�[�W�����֐�
#define NS_ProcessMessage		ProcessMessage

#endif


#ifdef DX_THREAD_SAFE

// �ݒ�n�֐�
extern	int			NS_SetAlwaysRunFlag(						int Flag ) ;																		// �E�C���h�E���A�N�e�B�u�ł͂Ȃ���Ԃł������𑱍s���邩�A�t���O���Z�b�g����

extern	int			NS_DxLib_GlobalStructInitialize( void ) ;									// ���C�u�����̓����Ŏg�p���Ă���\���̂��[�����������āADxLib_Init �̑O�ɍs�����ݒ�𖳌�������( DxLib_Init �̑O�ł̂ݗL�� )
extern	int			NS_DxLib_IsInit( void ) ;													// ���C�u����������������Ă��邩�ǂ������擾����( �߂�l: TRUE=����������Ă���  FALSE=����Ă��Ȃ� )

// �G���[�֌W�֐�
extern	int			NS_GetLastErrorCode( void ) ;												// �Ō�ɔ��������G���[�̃G���[�R�[�h���擾����( �߂�l�@0:�G���[���������Ă��Ȃ��A���̓G���[�R�[�h�o�͂ɑΉ������G���[���������Ă��Ȃ��@�@0�ȊO�F�G���[�R�[�h�ADX_ERRORCODE_WIN_DESKTOP_24BIT_COLOR �Ȃ� )
extern	int			NS_GetLastErrorMessage( TCHAR *StringBuffer, int StringBufferBytes ) ;		// �Ō�ɔ��������G���[�̃G���[���b�Z�[�W���w��̕�����o�b�t�@�Ɏ擾����

#else

#define NS_SetAlwaysRunFlag					SetAlwaysRunFlag

#define NS_DxLib_GlobalStructInitialize		DxLib_GlobalStructInitialize
#define NS_DxLib_IsInit						DxLib_IsInit

#define NS_GetLastErrorCode					GetLastErrorCode
#define NS_GetLastErrorMessage				GetLastErrorMessage

#endif






// DxNetwork.cpp�֐��v���g�^�C�v�錾

#ifdef DX_THREAD_SAFE

#ifndef DX_NON_NETWORK

// �ʐM�֌W
extern	int			NS_ProcessNetMessage(				int RunReleaseProcess = FALSE ) ;														// �ʐM���b�Z�[�W�̏���������֐�

extern	int			NS_GetHostIPbyName(					const TCHAR *HostName,							IPDATA      *IPDataBuf, int IPDataBufLength = 1, int *IPDataGetNum = NULL ) ;	// �c�m�r�T�[�o�[���g���ăz�X�g������h�o�A�h���X���擾����( IPv4�� )
extern	int			NS_GetHostIPbyNameWithStrLen(		const TCHAR *HostName, size_t HostNameLength,	IPDATA      *IPDataBuf, int IPDataBufLength = 1, int *IPDataGetNum = NULL ) ;	// �c�m�r�T�[�o�[���g���ăz�X�g������h�o�A�h���X���擾����( IPv4�� )
extern	int			NS_GetHostIPbyName_IPv6(			const TCHAR *HostName,							IPDATA_IPv6 *IPDataBuf, int IPDataBufLength = 1, int *IPDataGetNum = NULL ) ;	// �c�m�r�T�[�o�[���g���ăz�X�g������h�o�A�h���X���擾����( IPv6�� )
extern	int			NS_GetHostIPbyName_IPv6WithStrLen(	const TCHAR *HostName, size_t HostNameLength,	IPDATA_IPv6 *IPDataBuf, int IPDataBufLength = 1, int *IPDataGetNum = NULL ) ;	// �c�m�r�T�[�o�[���g���ăz�X�g������h�o�A�h���X���擾����( IPv6�� )
extern	int			NS_ConnectNetWork(					IPDATA      IPData, int Port = -1 ) ;													// ���}�V���ɐڑ�����( IPv4�� )
extern	int			NS_ConnectNetWork_IPv6(			IPDATA_IPv6 IPData, int Port = -1 ) ;													// ���}�V���ɐڑ�����( IPv6�� )
extern	int			NS_ConnectNetWork_ASync(			IPDATA      IPData, int Port = -1 ) ;													// ���}�V���ɐڑ�����( IPv4�� )�A�񓯊���
extern	int			NS_ConnectNetWork_IPv6_ASync(		IPDATA_IPv6 IPData, int Port = -1 ) ;													// ���}�V���ɐڑ�����( IPv6�� )�A�񓯊���
extern	int			NS_PreparationListenNetWork(		int Port = -1 ) ;																		// �ڑ����󂯂����Ԃɂ���( IPv4�� )
extern	int			NS_PreparationListenNetWork_IPv6(	int Port = -1 ) ;																		// �ڑ����󂯂����Ԃɂ���( IPv6�� )
extern	int			NS_StopListenNetWork(				void ) ;																				// �ڑ����󂯂���Ԃ̉���
extern	int			NS_CloseNetWork(					int NetHandle ) ;																		// �ڑ����I������

extern	int			NS_GetNetWorkAcceptState(			int NetHandle ) ;																		// �ڑ���Ԃ��擾����
extern	int			NS_GetNetWorkDataLength(			int NetHandle ) ;																		// ��M�f�[�^�̗ʂ𓾂�
extern	int			NS_GetNetWorkSendDataLength(		int NetHandle ) ;																		// �����M�̃f�[�^�̗ʂ𓾂� 
extern	int			NS_GetNewAcceptNetWork(			void ) ;																				// �V���ɐڑ������ʐM����𓾂�
extern	int			NS_GetLostNetWork(					void ) ;																				// �ڑ���ؒf���ꂽ�ʐM����𓾂�
extern	int			NS_GetNetWorkIP(					int NetHandle, IPDATA      *IpBuf ) ;													// �ڑ���̂h�o�𓾂�( IPv4�� )
extern	int			NS_GetNetWorkIP_IPv6(				int NetHandle, IPDATA_IPv6 *IpBuf ) ;													// �ڑ���̂h�o�𓾂�( IPv6�� )
extern	int			NS_GetMyIPAddress(					IPDATA *IpBuf, int IpBufLength = 1, int *IpNum = NULL ) ;							// �����̂h�o�𓾂�
extern	int			NS_GetMyIPAddress_IPv6(				IPDATA_IPv6 *IpBuf, int IpBufLength = 1 , int *IpNum = NULL ) ;							// ������IPv6�𓾂�
extern	int			NS_SetConnectTimeOutWait(			int Time ) ;																			// �ڑ��̃^�C���A�E�g�܂ł̎��Ԃ�ݒ肷��
extern	int			NS_SetUseDXNetWorkProtocol(		int Flag ) ;																			// �c�w���C�u�����̒ʐM�`�Ԃ��g�����ǂ������Z�b�g����
extern	int			NS_GetUseDXNetWorkProtocol(		void ) ; 																				// �c�w���C�u�����̒ʐM�`�Ԃ��g�����ǂ������擾����
extern	int			NS_SetUseDXProtocol(				int Flag ) ;																			// SetUseDXNetWorkProtocol �̕ʖ�
extern	int			NS_GetUseDXProtocol(				void ) ; 																				// GetUseDXNetWorkProtocol �̕ʖ�
extern	int			NS_SetNetWorkCloseAfterLostFlag(	int Flag ) ;																			// �ڑ����ؒf���ꂽ����ɐڑ��n���h����������邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_GetNetWorkCloseAfterLostFlag(	void ) ;																				// �ڑ����ؒf���ꂽ����ɐڑ��n���h����������邩�ǂ����̃t���O���擾����
//extern	int			NS_SetProxySetting( int UseFlag, const char *Address, int Port ) ;														// �g�s�s�o�ʐM�Ŏg�p����v���L�V�ݒ���s��
//extern	int			NS_GetProxySetting( int *UseFlagBuffer, char *AddressBuffer, int *PortBuffer ) ;										// �g�s�s�o�ʐM�Ŏg�p����v���L�V�ݒ���擾����
//extern	int			NS_SetIEProxySetting( void ) ;																							// �h�d�̃v���L�V�ݒ��K������

extern	int			NS_NetWorkRecv(			int NetHandle, void *Buffer, int Length ) ;														// ��M�����f�[�^��ǂݍ���
extern	int			NS_NetWorkRecvToPeek(		int NetHandle, void *Buffer, int Length ) ;														// ��M�����f�[�^��ǂݍ��ށA�ǂݍ��񂾃f�[�^�̓o�b�t�@����폜����Ȃ�
extern	int			NS_NetWorkRecvBufferClear(	int NetHandle ) ;																				// ��M�����f�[�^���N���A����
extern	int			NS_NetWorkSend(			int NetHandle, const void *Buffer, int Length ) ;														// �f�[�^�𑗐M����

extern	int			NS_MakeUDPSocket(			int RecvPort = -1 ) ;																			// UDP���g�p�����ʐM���s���\�P�b�g�n���h�����쐬����( RecvPort �� -1 �ɂ���Ƒ��M��p�̃\�P�b�g�n���h���ɂȂ�܂� )
extern	int			NS_MakeUDPSocket_IPv6(		int RecvPort = -1 ) ;																			// UDP���g�p�����ʐM���s���\�P�b�g�n���h�����쐬����( RecvPort �� -1 �ɂ���Ƒ��M��p�̃\�P�b�g�n���h���ɂȂ�܂� )( IPv6�� )
extern	int			NS_DeleteUDPSocket(		int NetUDPHandle ) ;																			// UDP���g�p�����ʐM���s���\�P�b�g�n���h�����폜����
extern	int			NS_NetWorkSendUDP(		int NetUDPHandle, IPDATA       SendIP, int SendPort,  const void *Buffer, int Length ) ;				// UDP���g�p�����ʐM�Ŏw��̂h�o�Ƀf�[�^�𑗐M����ALength �͍ő�65507�ASendPort �� -1 �ɂ���� MakeUDPSocket �� RecvPort �œn�����|�[�g���g�p����܂�( �߂�l  0�ȏ�;���M�ł����f�[�^�T�C�Y  -1:�G���[  -2:���M�f�[�^���傫������  -3:���M�������ł��Ă��Ȃ�  )
extern	int			NS_NetWorkSendUDP_IPv6(	int NetUDPHandle, IPDATA_IPv6  SendIP, int SendPort,  const void *Buffer, int Length ) ;				// UDP���g�p�����ʐM�Ŏw��̂h�o�Ƀf�[�^�𑗐M����ALength �͍ő�65507�ASendPort �� -1 �ɂ���� MakeUDPSocket �� RecvPort �œn�����|�[�g���g�p����܂�( �߂�l  0�ȏ�;���M�ł����f�[�^�T�C�Y  -1:�G���[  -2:���M�f�[�^���傫������  -3:���M�������ł��Ă��Ȃ�  )( IPv6�� )
extern	int			NS_NetWorkRecvUDP(		int NetUDPHandle, IPDATA      *RecvIP, int *RecvPort, void *Buffer, int Length, int Peek ) ;	// UDP���g�p�����ʐM�Ńf�[�^����M����APeek �� TRUE ��n���Ǝ�M�ɐ������Ă��f�[�^����M�L���[����폜���܂���( �߂�l  0�ȏ�:��M�����f�[�^�̃T�C�Y  -1:�G���[  -2:�o�b�t�@�̃T�C�Y������Ȃ�  -3:��M�f�[�^���Ȃ� )
extern	int			NS_NetWorkRecvUDP_IPv6(	int NetUDPHandle, IPDATA_IPv6 *RecvIP, int *RecvPort, void *Buffer, int Length, int Peek ) ;	// UDP���g�p�����ʐM�Ńf�[�^����M����APeek �� TRUE ��n���Ǝ�M�ɐ������Ă��f�[�^����M�L���[����폜���܂���( �߂�l  0�ȏ�:��M�����f�[�^�̃T�C�Y  -1:�G���[  -2:�o�b�t�@�̃T�C�Y������Ȃ�  -3:��M�f�[�^���Ȃ� )( IPv6�� )
//extern int		NS_CheckNetWorkSendUDP(	int NetUDPHandle ) ;																			// UDP���g�p�����ʐM�Ńf�[�^�����M�ł����Ԃ��ǂ����𒲂ׂ�( �߂�l  -1:�G���[  TRUE:���M�\  FALSE:���M�s�\ )
extern	int			NS_CheckNetWorkRecvUDP(	int NetUDPHandle ) ;																			// UDP���g�p�����ʐM�ŐV���Ȏ�M�f�[�^�����݂��邩�ǂ����𒲂ׂ�( �߂�l  -1:�G���[  TRUE:��M�f�[�^����  FALSE:��M�f�[�^�Ȃ� )

/*	�g�p�s��
extern	int			NS_HTTP_FileDownload(			const char *FileURL, const char *SavePath = NULL , void **SaveBufferP = NULL , int *FileSize = NULL , char **ParamList = NULL ) ;						// HTTP ���g�p���ăl�b�g���[�N��̃t�@�C�����_�E�����[�h����
extern	int			NS_HTTP_GetFileSize(			const char *FileURL ) ;																		// HTTP ���g�p���ăl�b�g���[�N��̃t�@�C���̃T�C�Y�𓾂�

extern	int			NS_HTTP_StartFileDownload(		const char *FileURL, const char *SavePath, void **SaveBufferP = NULL , char **ParamList = NULL ) ;	// HTTP ���g�p�����l�b�g���[�N��̃t�@�C�����_�E�����[�h���鏈�����J�n����
extern	int			NS_HTTP_StartGetFileSize(		const char *FileURL ) ;																		// HTTP ���g�p�����l�b�g���[�N��̃t�@�C���̃T�C�Y�𓾂鏈�����J�n����
extern	int			NS_HTTP_Close(					int HttpHandle ) ;																			// HTTP �̏������I�����A�n���h�����������
extern	int			NS_HTTP_CloseAll(				void ) ;																					// �S�Ẵn���h���ɑ΂��� HTTP_Close ���s��
extern	int			NS_HTTP_GetState(				int HttpHandle ) ;																			// HTTP �����̌��݂̏�Ԃ𓾂�( NET_RES_COMPLETE �� )
extern	int			NS_HTTP_GetError(				int HttpHandle ) ;																			// HTTP �����ŃG���[�����������ꍇ�A�G���[�̓��e�𓾂�( HTTP_ERR_NONE �� )
extern	int			NS_HTTP_GetDownloadFileSize(	int HttpHandle ) ;																			// HTTP �����őΏۂƂȂ��Ă���t�@�C���̃T�C�Y�𓾂�( �߂�l: -1 = �G���[�E�Ⴕ���͂܂��t�@�C���̃T�C�Y���擾���Ă��Ȃ�  0�ȏ� = �t�@�C���̃T�C�Y )
extern	int			NS_HTTP_GetDownloadedFileSize( int HttpHandle ) ;																			// HTTP �����Ŋ��Ƀ_�E�����[�h�����t�@�C���̃T�C�Y���擾����

extern	int			NS_fgetsForNetHandle(			int NetHandle, char *strbuffer ) ;															// fgets �̃l�b�g���[�N�n���h����( -1:�擾�ł��� 0:�擾�ł��� )
extern	int			NS_URLAnalys(					const char *URL, char *HostBuf = NULL , char *PathBuf = NULL , char *FileNameBuf = NULL , int *PortBuf = NULL ) ;	// �t�q�k����͂���
extern	int			NS_URLConvert(					char *URL, int ParamConvert = TRUE , int NonConvert = FALSE ) ;								// HTTP �ɓn���Ȃ��L�����g��ꂽ�������n����悤�ȕ�����ɕϊ�����( �߂�l: -1 = �G���[  0�ȏ� = �ϊ���̕�����̃T�C�Y )
extern	int			NS_URLParamAnalysis(			char **ParamList, char **ParamStringP ) ;													// HTTP �p�p�����[�^���X�g�����̃p�����[�^��������쐬����( �߂�l:  -1 = �G���[  0�ȏ� = �p�����[�^�̕�����̒��� )
*/

#endif	// DX_NON_NETWORK

#else	// DX_THREAD_SAFE

#ifndef DX_NON_NETWORK

// �ʐM�֌W
#define NS_ProcessNetMessage					ProcessNetMessage

#define NS_GetHostIPbyName						GetHostIPbyName
#define NS_GetHostIPbyNameWithStrLen			GetHostIPbyNameWithStrLen
#define NS_GetHostIPbyName_IPv6					GetHostIPbyName_IPv6
#define NS_GetHostIPbyName_IPv6WithStrLen		GetHostIPbyName_IPv6WithStrLen
#define NS_ConnectNetWork						ConnectNetWork
#define NS_ConnectNetWork_IPv6					ConnectNetWork_IPv6
#define NS_ConnectNetWork_ASync					ConnectNetWork_ASync
#define NS_ConnectNetWork_IPv6_ASync			ConnectNetWork_IPv6_ASync
#define NS_PreparationListenNetWork				PreparationListenNetWork
#define NS_PreparationListenNetWork_IPv6		PreparationListenNetWork_IPv6
#define NS_StopListenNetWork					StopListenNetWork
#define NS_CloseNetWork							CloseNetWork

#define NS_GetNetWorkAcceptState				GetNetWorkAcceptState
#define NS_GetNetWorkDataLength					GetNetWorkDataLength
#define NS_GetNetWorkSendDataLength				GetNetWorkSendDataLength
#define NS_GetNewAcceptNetWork					GetNewAcceptNetWork
#define NS_GetLostNetWork						GetLostNetWork
#define NS_GetNetWorkIP							GetNetWorkIP
#define NS_GetNetWorkIP_IPv6					GetNetWorkIP_IPv6
#define NS_GetMyIPAddress						GetMyIPAddress
#define NS_GetMyIPAddress_IPv6					GetMyIPAddress_IPv6
#define NS_SetConnectTimeOutWait				SetConnectTimeOutWait
#define NS_SetUseDXNetWorkProtocol				SetUseDXNetWorkProtocol
#define NS_GetUseDXNetWorkProtocol				GetUseDXNetWorkProtocol
#define NS_SetUseDXProtocol						SetUseDXProtocol
#define NS_GetUseDXProtocol						GetUseDXProtocol
#define NS_SetNetWorkCloseAfterLostFlag			SetNetWorkCloseAfterLostFlag
#define NS_GetNetWorkCloseAfterLostFlag			GetNetWorkCloseAfterLostFlag
//#define NS_SetProxySetting					SetProxySetting
//#define NS_GetProxySetting					GetProxySetting
//#define NS_SetIEProxySetting					SetIEProxySetting

#define NS_NetWorkRecv							NetWorkRecv
#define NS_NetWorkRecvToPeek					NetWorkRecvToPeek
#define NS_NetWorkRecvBufferClear				NetWorkRecvBufferClear
#define NS_NetWorkSend							NetWorkSend

#define NS_MakeUDPSocket						MakeUDPSocket
#define NS_MakeUDPSocket_IPv6					MakeUDPSocket_IPv6
#define NS_DeleteUDPSocket						DeleteUDPSocket
#define NS_NetWorkSendUDP						NetWorkSendUDP
#define NS_NetWorkSendUDP_IPv6					NetWorkSendUDP_IPv6
#define NS_NetWorkRecvUDP						NetWorkRecvUDP
#define NS_NetWorkRecvUDP_IPv6					NetWorkRecvUDP_IPv6
#define NS_CheckNetWorkSendUDP					CheckNetWorkSendUDP
#define NS_CheckNetWorkRecvUDP					CheckNetWorkRecvUDP

/* �g�p�s��
#define NS_HTTP_FileDownload					HTTP_FileDownload
#define NS_HTTP_GetFileSize						HTTP_GetFileSize

#define NS_HTTP_StartFileDownload				HTTP_StartFileDownload
#define NS_HTTP_StartGetFileSize				HTTP_StartGetFileSize
#define NS_HTTP_Close							HTTP_Close
#define NS_HTTP_CloseAll						HTTP_CloseAll
#define NS_HTTP_GetState						HTTP_GetState
#define NS_HTTP_GetError						HTTP_GetError
#define NS_HTTP_GetDownloadFileSize				HTTP_GetDownloadFileSize
#define NS_HTTP_GetDownloadedFileSize			HTTP_GetDownloadedFileSize

#define NS_fgetsForNetHandle					fgetsForNetHandle
#define NS_URLAnalys							URLAnalys
#define NS_URLConvert							URLConvert
#define NS_URLParamAnalysis						URLParamAnalysis
*/

#endif	// DX_NON_NETWORK

#endif	// DX_THREAD_SAFE









#ifdef DX_THREAD_SAFE


// DxSystem.cpp�֐��v���g�^�C�v�錾

// �E�G�C�g�n�֐�
extern	int			NS_WaitTimer( int WaitTime ) ;												// �w��̎��Ԃ����������Ƃ߂�
#ifndef DX_NON_INPUT
extern	int			NS_WaitKey( void ) ;														// �L�[�̓��͑҂�
#endif // DX_NON_INPUT
extern	int			NS_SleepThread( int WaitTime ) ;											// �w��̎��Ԃ����X���b�h�𖰂点��

// �J�E���^�y�ю����擾�n�֐�
extern	int			NS_GetNowCount(				int UseRDTSCFlag = FALSE ) ;				// �~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
extern	LONGLONG	NS_GetNowHiPerformanceCount(	int UseRDTSCFlag = FALSE ) ;				// GetNowCount�̍����x�o�[�W����
extern	ULONGLONG	NS_GetNowSysPerformanceCount(	void ) ;									// OS���񋟂��鍂���x�J�E���^�̌��݂̒l�𓾂�
extern	ULONGLONG	NS_GetSysPerformanceFrequency(	void ) ;									// OS���񋟂��鍂���x�J�E���^�̎��g��( 1�b�ӂ�̃J�E���g�� )�𓾂�
extern	ULONGLONG	NS_ConvSysPerformanceCountToSeconds(		ULONGLONG Count ) ;				// OS���񋟂��鍂���x�J�E���^�̒l��b�̒l�ɕϊ�����
extern	ULONGLONG	NS_ConvSysPerformanceCountToMilliSeconds(	ULONGLONG Count ) ;				// OS���񋟂��鍂���x�J�E���^�̒l���~���b�̒l�ɕϊ�����
extern	ULONGLONG	NS_ConvSysPerformanceCountToMicroSeconds(	ULONGLONG Count ) ;				// OS���񋟂��鍂���x�J�E���^�̒l���}�C�N���b�̒l�ɕϊ�����
extern	ULONGLONG	NS_ConvSysPerformanceCountToNanoSeconds(	ULONGLONG Count ) ;				// OS���񋟂��鍂���x�J�E���^�̒l���i�m�b�̒l�ɕϊ�����
extern	ULONGLONG	NS_ConvSecondsToSysPerformanceCount(		ULONGLONG Seconds ) ;			// �b�̒l��OS���񋟂��鍂���x�J�E���^�̒l�ɕϊ�����
extern	ULONGLONG	NS_ConvMilliSecondsToSysPerformanceCount(	ULONGLONG MilliSeconds ) ;		// �~���b�̒l��OS���񋟂��鍂���x�J�E���^�̒l�ɕϊ�����
extern	ULONGLONG	NS_ConvMicroSecondsToSysPerformanceCount(	ULONGLONG MicroSeconds ) ;		// �}�C�N���b�̒l��OS���񋟂��鍂���x�J�E���^�̒l�ɕϊ�����
extern	ULONGLONG	NS_ConvNanoSecondsToSysPerformanceCount(	ULONGLONG NanoSeconds ) ;		// �i�m�b�̒l��OS���񋟂��鍂���x�J�E���^�̒l�ɕϊ�����
extern	int			NS_GetDateTime(				DATEDATA *DateBuf ) ;						// ���ݎ������擾���� 

// �����擾
extern	int			NS_GetRand( int RandMax ) ;												// �������擾����( RandMax : �Ԃ��ė���l�̍ő�l )
extern	int			NS_SRand(	 int Seed ) ;													// �����̏����l��ݒ肷��

#ifndef DX_NON_MERSENNE_TWISTER
extern	DWORD		NS_GetMersenneTwisterRand( void ) ;										// �����Z���k�E�c�C�X�^�[�A���S���Y���Ő������ꂽ�����l�𖳉��H�Ŏ擾����

extern	DWORD_PTR	NS_CreateRandHandle( int Seed ) ;											// �����n���h�����쐬����( �߂�l�@0�ȊO:�����n���h���@0:�G���[ )
extern	int			NS_DeleteRandHandle( DWORD_PTR RandHandle ) ;								// �����n���h�����폜����
extern	int			NS_SRandHandle( DWORD_PTR RandHandle, int Seed ) ;							// �����n���h���̏����l���Đݒ肷��
extern	int			NS_GetRandHandle( DWORD_PTR RandHandle, int RandMax ) ;						// �����n���h�����g�p���ė������擾����( RandMax : �Ԃ��ė���l�̍ő�l )
extern	DWORD		NS_GetMersenneTwisterRandHandle( DWORD_PTR RandHandle ) ;					// �����n���h�����g�p���ă����Z���k�E�c�C�X�^�[�A���S���Y���Ő������ꂽ�����l�𖳉��H�Ŏ擾����

#endif // DX_NON_MERSENNE_TWISTER

// �o�b�e���[�֘A
extern	int			NS_GetBatteryLifePercent( void ) ;											// �d�r�̎c�ʂ� % �Ŏ擾����( �߂�l�F 100=�t���[�d���  0=�[�d�c�ʖ��� )

// �N���b�v�{�[�h�֌W
extern	int			NS_GetClipboardText(			TCHAR *DestBuffer, int DestBufferBytes DEFAULTPARAM( = -1 ) ) ;									// �N���b�v�{�[�h�Ɋi�[����Ă���e�L�X�g�f�[�^��ǂݏo���A-1 �̏ꍇ�̓N���b�v�{�[�h�Ƀe�L�X�g�f�[�^�͖����Ƃ�������( DestBuffer �� NULL ��n���Ɗi�[�ɕK�v�ȃf�[�^�T�C�Y���Ԃ��Ă��� )
extern	int			NS_SetClipboardText(			const TCHAR *Text ) ;									// �N���b�v�{�[�h�Ƀe�L�X�g�f�[�^���i�[����
extern	int			NS_SetClipboardTextWithStrLen(	const TCHAR *Text, size_t TextLength ) ;										// �N���b�v�{�[�h�Ƀe�L�X�g�f�[�^���i�[����

// ini�t�@�C���֌W
extern	int			NS_GetPrivateProfileStringDx(                 const TCHAR *AppName,                       const TCHAR *KeyName,                       const TCHAR *Default,                       TCHAR *ReturnedStringBuffer, size_t ReturnedStringBufferBytes, const TCHAR *IniFilePath,                           int IniFileCharCodeFormat = -1 /* DX_CHARCODEFORMAT_SHIFTJIS ���A-1 �Ńf�t�H���g */ ) ;		// GetPrivateProfileString �̂c�w���C�u������
extern	int			NS_GetPrivateProfileStringDxWithStrLen(       const TCHAR *AppName, size_t AppNameLength, const TCHAR *KeyName, size_t KeyNameLength, const TCHAR *Default, size_t DefaultLength, TCHAR *ReturnedStringBuffer, size_t ReturnedStringBufferBytes, const TCHAR *IniFilePath, size_t IniFilePathLength, int IniFileCharCodeFormat = -1 /* DX_CHARCODEFORMAT_SHIFTJIS ���A-1 �Ńf�t�H���g */ ) ;		// GetPrivateProfileString �̂c�w���C�u������
extern	int			NS_GetPrivateProfileIntDx(                    const TCHAR *AppName,                       const TCHAR *KeyName,                       int          Default,                                                                                      const TCHAR *IniFilePath,                           int IniFileCharCodeFormat = -1 /* DX_CHARCODEFORMAT_SHIFTJIS ���A-1 �Ńf�t�H���g */ ) ;		// GetPrivateProfileInt �̂c�w���C�u������
extern	int			NS_GetPrivateProfileIntDxWithStrLen(          const TCHAR *AppName, size_t AppNameLength, const TCHAR *KeyName, size_t KeyNameLength, int          Default,                                                                                      const TCHAR *IniFilePath, size_t IniFilePathLength, int IniFileCharCodeFormat = -1 /* DX_CHARCODEFORMAT_SHIFTJIS ���A-1 �Ńf�t�H���g */ ) ;		// GetPrivateProfileInt �̂c�w���C�u������
extern	int			NS_GetPrivateProfileStringDxForMem(           const TCHAR *AppName,                       const TCHAR *KeyName,                       const TCHAR *Default,                       TCHAR *ReturnedStringBuffer, size_t ReturnedStringBufferBytes, const void *IniFileImage, size_t IniFileImageBytes, int IniFileCharCodeFormat = -1 /* DX_CHARCODEFORMAT_SHIFTJIS ���A-1 �Ńf�t�H���g */ ) ;		// GetPrivateProfileStringDx �̃���������ǂݍ��ޔ�
extern	int			NS_GetPrivateProfileStringDxForMemWithStrLen( const TCHAR *AppName, size_t AppNameLength, const TCHAR *KeyName, size_t KeyNameLength, const TCHAR *Default, size_t DefaultLength, TCHAR *ReturnedStringBuffer, size_t ReturnedStringBufferBytes, const void *IniFileImage, size_t IniFileImageBytes, int IniFileCharCodeFormat = -1 /* DX_CHARCODEFORMAT_SHIFTJIS ���A-1 �Ńf�t�H���g */ ) ;		// GetPrivateProfileStringDx �̃���������ǂݍ��ޔ�
extern	int			NS_GetPrivateProfileIntDxForMem(              const TCHAR *AppName,                       const TCHAR *KeyName,                       int          Default,                                                                                      const void *IniFileImage, size_t IniFileImageBytes, int IniFileCharCodeFormat = -1 /* DX_CHARCODEFORMAT_SHIFTJIS ���A-1 �Ńf�t�H���g */ ) ;		// GetPrivateProfileIntDx �̃���������ǂݍ��ޔ�
extern	int			NS_GetPrivateProfileIntDxForMemWithStrLen(    const TCHAR *AppName, size_t AppNameLength, const TCHAR *KeyName, size_t KeyNameLength, int          Default,                                                                                      const void *IniFileImage, size_t IniFileImageBytes, int IniFileCharCodeFormat = -1 /* DX_CHARCODEFORMAT_SHIFTJIS ���A-1 �Ńf�t�H���g */ ) ;		// GetPrivateProfileIntDx �̃���������ǂݍ��ޔ�
















// DxLog.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_LOG

// ���O�o�͐ݒ�֐�
extern	int			NS_SetOutApplicationLogValidFlag(			int Flag ) ;																		// ���O�o�͂��s�����ۂ��̃Z�b�g
extern	int			NS_SetOutApplicationSystemLogValidFlag(      int Flag ) ;													// ���O�t�@�C��( Log.txt ) �ɂc�w���C�u���������̃��O�o�͂��s�����ǂ����ݒ肷��( TRUE:�c�w���C�u���������̃��O�o�͂��s��( �f�t�H���g )  FALSE:�c�w���C�u���������̃��O�o�͂��s��Ȃ� )
extern	int			NS_SetApplicationLogFileName(      const TCHAR *FileName ) ;				// ���O�t�@�C���̖��O��ݒ肷��( Log.txt �ȊO�ɂ������ꍇ�Ɏg�p )
extern	int			NS_SetApplicationLogFileNameWithStrLen(      const TCHAR *FileName, size_t FileNameLength ) ;				// ���O�t�@�C���̖��O��ݒ肷��( Log.txt �ȊO�ɂ������ꍇ�Ɏg�p )
extern	int			NS_SetApplicationLogSaveDirectory(	          const TCHAR *DirectoryPath ) ;								// ���O�t�@�C��( Log.txt ) ��ۑ�����f�B���N�g���p�X��ݒ肷��
extern	int			NS_SetApplicationLogSaveDirectoryWithStrLen( const TCHAR *DirectoryPath, size_t DirectoryPathLength ) ;	// ���O�t�@�C��( Log.txt ) ��ۑ�����f�B���N�g���p�X��ݒ肷��
extern	int			NS_SetUseDateNameLogFile(					int Flag ) ;																		// ���O�t�@�C�����ɓ��t�����邩�ǂ������Z�b�g����

// ���O�t�@�C���֐�
extern	int			NS_LogFileAdd(			 const TCHAR *String ) ;							// ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���
extern	int			NS_LogFileAddWithStrLen(	const TCHAR *String, size_t StringLength ) ;	// ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���
extern 	int			NS_LogFileFmtAdd(		 const TCHAR *FormatString , ... ) ;				// �����t���� ���O�t�@�C��( Log.txt ) �ɕ�������o�͂���( ������ printf �Ɠ��� )
extern	int			NS_LogFileTabAdd(		 void ) ;											// ���O�t�@�C��( Log.txt ) �ɏo�͂��镶����̑O�ɕt����^�u�̐�������₷
extern	int			NS_LogFileTabSub(		 void ) ;											// ���O�t�@�C��( Log.txt ) �ɏo�͂��镶����̑O�ɕt����^�u�̐�������炷
extern	int			NS_ErrorLogAdd(			const TCHAR *String ) ;							// LogFileAdd �̋����̊֐�
extern 	int			NS_ErrorLogFmtAdd(		 const TCHAR *FormatString , ... ) ;				// LogFileFmtAdd �̋����̊֐�
extern	int			NS_ErrorLogTabAdd(		 void ) ;											// LogFileTabAdd �̋����̊֐�
extern	int			NS_ErrorLogTabSub(		 void ) ;											// LogFileTabSub �̋����̊֐�
extern	int			NS_SetUseTimeStampFlag( int UseFlag ) ;									// �^�C���X�^���v�̗L����ݒ肷��
extern 	int			NS_AppLogAdd(			 const TCHAR *String , ... ) ;						// �����t�����O������������o��

#ifndef DX_NON_PRINTF_DX

// ���O�o�͋@�\�֐�
extern	int			NS_SetLogDrawOutFlag(	 int DrawFlag ) ;									// ���O�o�̓t���O���Z�b�g����
extern 	int			NS_GetLogDrawFlag(		 void ) ;											// ���O�o�͂����邩�t���O�̎擾
extern	int			NS_SetLogFontSize(		 int Size ) ;										// printfDx �ŉ�ʂɏo�͂��郍�O�t�H���g�̃T�C�Y��ύX����
extern	int			NS_SetLogFontHandle(	 int FontHandle ) ;									// printfDx �̌��ʂ���ʂɏo�͂���ۂɎg�p����t�H���g�̃n���h����ύX����
extern	int			NS_SetLogDrawArea(		 int x1, int y1, int x2, int y2 ) ;					// printfDx �̌��ʂ���ʂɏo�͂���ۂ̕`�悷��̈��ݒ肷��

// �ȈՉ�ʏo�͊֐�
extern 	int			NS_printfDx(			 const TCHAR *FormatString , ... ) ;				// �ȈՉ�ʏo��
extern	int			NS_putsDx(				 const TCHAR *String, int NewLine = TRUE ) ;		// puts �Ɠ��������ŉ�ʂɕ������\�����邽�߂̊֐�
extern	int			NS_putsDxWithStrLen(	 const TCHAR *String, size_t StringLength, int NewLine = TRUE ) ;	// puts �Ɠ��������ŉ�ʂɕ������\�����邽�߂̊֐�
extern	int			NS_clsDx(				 void ) ;											// �ȈՉ�ʏo�͂��N���A����
extern	int			NS_setPrintColorDx(     int Color, int EdgeColor = 0 ) ;													// printf �� puts �ŕ\�����镶����̐F���w�肷��
#endif

#endif // DX_NON_LOG















#ifndef DX_NON_ASYNCLOAD

// DxASyncLoad.cpp�֐��v���g�^�C�v�錾

// �񓯊��ǂݍ��݊֌W
extern	int			NS_SetUseASyncLoadFlag(		int Flag ) ;								// �ǂݍ��ݏ����n�̊֐��Ŕ񓯊��ǂݍ��݂��s�����ǂ�����ݒ肷��( �񓯊��ǂݍ��݂ɑΉ����Ă���֐��̂ݗL�� )( TRUE:�񓯊��ǂݍ��݂��s��  FALSE:�񓯊��ǂݍ��݂��s��Ȃ�( �f�t�H���g ) )
extern	int			NS_GetUseASyncLoadFlag(			void ) ;									// �ǂݍ��ݏ����n�̊֐��Ŕ񓯊��ǂݍ��݂��s�����ǂ������擾����( �񓯊��ǂݍ��݂ɑΉ����Ă���֐��̂ݗL�� )( TRUE:�񓯊��ǂݍ��݂��s��  FALSE:�񓯊��ǂݍ��݂��s��Ȃ�( �f�t�H���g ) )
extern	int			NS_CheckHandleASyncLoad(		int Handle ) ;								// �n���h���̔񓯊��ǂݍ��݂��������Ă��邩�ǂ������擾����( TRUE:�܂��������Ă��Ȃ�  FALSE:�������Ă���  -1:�G���[ )
extern	int			NS_GetHandleASyncLoadResult(	int Handle ) ;								// �n���h���̔񓯊��ǂݍ��ݏ����̖߂�l���擾����( �񓯊��ǂݍ��ݒ��̏ꍇ�͈�O�̔񓯊��ǂݍ��ݏ����̖߂�l���Ԃ��Ă��܂� )
extern	int			NS_SetASyncLoadFinishDeleteFlag(	int Handle ) ;								// �n���h���̔񓯊��ǂݍ��ݏ���������������n���h�����폜����t���O�𗧂Ă�
extern	int			NS_SetASyncLoadFinishCallback(	int Handle, void ( *Callback )( int Handle, void *Data ), void *Data ) ;	// �n���h���̔񓯊��ǂݍ��ݏ���������������Ă΂��֐����Z�b�g����
extern	int			NS_WaitHandleASyncLoad(					int Handle ) ;								// �w��̃n���h���̔񓯊��ǂݍ��ݏ������I������܂ő҂�
extern	int			NS_WaitHandleASyncLoadAll(				void ) ;									// �S�Ă̔񓯊��ǂݍ��݃f�[�^���ǂݍ��ݏI���܂ő҂�
extern	int			NS_GetASyncLoadNum(			void ) ;									// �񓯊��ǂݍ��ݒ��̏����̐����擾����
extern	int			NS_SetASyncLoadThreadNum(		int ThreadNum ) ;							// �񓯊��ǂݍ��ݏ������s���X���b�h�̐���ݒ肷��

#endif // DX_NON_ASYNCLOAD













// DxHandle.cpp�֐��v���g�^�C�v�錾

extern	int			NS_SetDeleteHandleFlag(		int Handle, int *DeleteFlag ) ;					// �n���h�����폜���ꂽ�Ƃ��Ɂ|�P���ݒ肳���ϐ���o�^����
extern	int			NS_GetHandleNum(				int HandleType ) ;							// �w��̃^�C�v�̃n���h���̐����擾����
extern	int			NS_GetMaxHandleNum(			int HandleType ) ;							// �w��̃^�C�v�̃n���h�����ő�Ŋ�쐬�ł��邩���擾����
extern	int			NS_DumpHandleInfo(				int HandleType /* DX_HANDLETYPE_GRAPH�� */ ) ;			// �w��̃^�C�v�̑S�n���h���̏������O�ɏo�͂���














// DxWindow.cpp�֐��v���g�^�C�v�錾

#ifdef WINDOWS_DESKTOP_OS

// �֗��֐�
extern	int			NS_GetResourceInfo(		const TCHAR *ResourceName , const TCHAR *ResourceType , void **DataPointerP , size_t *DataSizeP ) ;		// �w��̃��\�[�X���擾����( -1:���s  0:���� )
extern	int			NS_GetResourceInfoWithStrLen(	const TCHAR *ResourceName, size_t ResourceNameLength, const TCHAR *ResourceType, size_t ResourceTypeLength, void **DataPointerP , size_t *DataSizeP ) ;		// �w��̖��O�A�^�C�v�̃��\�[�X�̃A�h���X�ƃT�C�Y���擾����( �߂�l  -1:���s  0:���� )
extern	const TCHAR* NS_GetResourceIDString(	int ResourceID ) ;																						// ���\�[�X�h�c���烊�\�[�X�h�c������𓾂� 

// �E�C���h�E�֌W���擾�֐�
extern	int			NS_GetWindowCRect(					RECT *RectBuf ) ;										// �E�C���h�E�̃N���C�A���g�̈���擾����
extern	int			NS_GetWindowClientRect(			RECT *RectBuf ) ;										// ���C���E�C���h�E�̃N���C�A���g�̈���擾����
extern	int			NS_GetWindowFrameRect(				RECT *RectBuf ) ;										// ���C���E�C���h�E�̘g�̕������܂߂��S�̗̂̈���擾����
extern	int			NS_GetWindowActiveFlag(			void ) ;												// �E�C���h�E�̃A�N�e�B�u�t���O���擾
extern	int			NS_GetWindowMinSizeFlag(			void ) ;												// ���C���E�C���h�E���ŏ�������Ă��邩�ǂ������擾����( �߂�l  TRUE:�ŏ�������Ă���  FALSE:�ŏ�������Ă��Ȃ� )
extern	int			NS_GetWindowMaxSizeFlag(			void ) ;												// ���C���E�C���h�E���ő剻����Ă��邩�ǂ������擾����( �߂�l  TRUE:�ő剻����Ă���  FALSE:�ő剻����Ă��Ȃ� )
extern	HWND		NS_GetMainWindowHandle(			void ) ;												// ���C���E�C���h�E�̃n���h�����擾����
extern	int			NS_GetWindowModeFlag(				void ) ;												// �E�C���h�E���[�h�ŋN�����Ă��邩�A�̃t���O���擾����
extern	int			NS_GetDefaultState(				int *SizeX , int *SizeY , int *ColorBitDepth, int *RefreshRate = NULL , int *LeftTopX = NULL , int *LeftTopY = NULL, int *PixelSizeX = NULL , int *PixelSizeY = NULL , int *XDpi = NULL , int *YDpi = NULL ) ;		// �N�����̃f�X�N�g�b�v�̉�ʃ��[�h���擾����
extern	int			NS_GetMonitorDpi(					int *XDpi, int *YDpi, int MonitorIndex = -1 ) ;			// ���j�^�[��DPI���擾����
extern	int			NS_GetActiveFlag(					void ) ;												// �\�t�g���A�N�e�B�u���ǂ������擾����
extern	int			NS_GetNoActiveState(				int ResetFlag = TRUE ) ;								// ��A�N�e�B�u�ɂȂ�A�������ꎞ��~���Ă������ǂ������擾����(���� ResetFlag=TRUE:��Ԃ����Z�b�g FALSE:��Ԃ����Z�b�g���Ȃ�    �߂�l: 0=�ꎞ��~�͂��Ă��Ȃ�  1=�ꎞ��~���Ă��� )
extern	int			NS_GetMouseDispFlag(				void ) ;												// �}�E�X��\�����邩�ǂ����̃t���O���擾����
extern	int			NS_GetAlwaysRunFlag(				void ) ;												// �E�C���h�E���A�N�e�B�u�ł͂Ȃ���Ԃł������𑱍s���邩�A�t���O���擾����
extern	int			NS__GetSystemInfo(					int *DxLibVer , int *DirectXVer , int *WindowsVer ) ;	// �c�w���C�u������ DirectX �̃o�[�W������ Windows �̃o�[�W�����𓾂�
extern	int			NS_GetPcInfo(						TCHAR *OSString , TCHAR *DirectXString , TCHAR *CPUString , int *CPUSpeed /* �P��MHz */ , double *FreeMemorySize /* �P��MByte */ , double *TotalMemorySize , TCHAR *VideoDriverFileName , TCHAR *VideoDriverString , double *FreeVideoMemorySize /* �P��MByte */ , double *TotalVideoMemorySize ) ;	// �o�b�̏��𓾂�
extern	int			NS_GetWindowOSVersion(				void ) ;												// WindowsOS�̃o�[�W�������擾����( �߂�l : DX_WINDOWSVERSION_10 �Ȃ� )
extern	int			NS_GetUseMMXFlag(					void ) ;												// �l�l�w���g���邩�ǂ����̏��𓾂�
extern	int			NS_GetUseSSEFlag(					void ) ;												// �r�r�d���g���邩�ǂ����̏��𓾂�
extern	int			NS_GetUseSSE2Flag(					void ) ;												// �r�r�d�Q���g���邩�ǂ����̏��𓾂�
extern	int			NS_GetWindowCloseFlag(				void ) ;												// �E�C���h�E����悤�Ƃ��Ă��邩�̏��𓾂�
extern	HINSTANCE	NS_GetTaskInstance(				void ) ;												// �\�t�g�̃C���X�^���X���擾����
extern	int			NS_GetUseWindowRgnFlag(			void ) ;												// ���[�W�������g���Ă��邩�ǂ������擾����
extern	int			NS_GetWindowSizeChangeEnableFlag(	int *FitScreen = NULL ) ;								// �E�C���h�E�̃T�C�Y��ύX�ł��邩�ǂ����̃t���O���擾����
extern	double		NS_GetWindowSizeExtendRate(		double *ExRateX = NULL , double *ExRateY = NULL ) ;		// �`���ʂ̃T�C�Y�ɑ΂���E�C���h�E�T�C�Y�̔䗦���擾����( �߂�l�� ExRateX �ɑ�������l�Ɠ����ł� )
extern	int			NS_GetWindowSize(					int *Width, int *Height ) ;								// �E�C���h�E���[�h�̃E�C���h�E�̃N���C�A���g�̈�̃T�C�Y���擾����
extern	int			NS_GetWindowEdgeWidth(				int *LeftWidth, int *RightWidth, int *TopWidth, int *BottomWidth ) ;	// �E�C���h�E�̏㉺���E�̉��̕����擾����
extern	int			NS_GetWindowPosition(				int *x, int *y ) ;										// �E�C���h�E���[�h�̃E�C���h�E�̈ʒu���擾����( �g���܂߂�������W )
extern	int			NS_GetWindowUserCloseFlag(			int StateResetFlag = FALSE ) ;							// �E�C���h�E�̕���{�^���������ꂽ���ǂ������擾����
extern	int			NS_CheckWindowMaximizeButtonInput(	int StateResetFlag = TRUE ) ;							// ���C���E�C���h�E�̍ő剻�{�^���������ꂽ���ǂ������擾����ASetWindowMaximizeButtonBehavior( 1 ); �����s����Ă���ꍇ�̂ݗL���Ȋ֐�( StateResetFlag  TRUE = �����ꂽ��Ԃ����Z�b�g����   FALSE = �����ꂽ��Ԃ����Z�b�g���Ȃ� )
extern	int			NS_GetNotDrawFlag(					void ) ;												// �`��@�\���g�����ǂ����̃t���O���擾����
extern	int			NS_GetPaintMessageFlag(			void ) ;												// WM_PAINT ���b�Z�[�W���������ǂ������擾����(�߂�l  TRUE:WM_PAINT���b�Z�[�W������(��x�擾����ƈȌ�A�Ă� WM_PAINT���b�Z�[�W������܂� FALSE ���Ԃ��Ă���悤�ɂȂ�)  FALSE:WM_PAINT ���b�Z�[�W�͗��Ă��Ȃ�)
extern	int			NS_GetValidHiPerformanceCounter(	void ) ;												// �p�t�H�[�}���X�J�E���^���L�����ǂ������擾����(�߂�l  TRUE:�L��  FALSE:����)
extern	TCHAR		NS_GetInputSystemChar(				int DeleteFlag ) ;										// ���͂��ꂽ�V�X�e���������擾����


// �ݒ�n�֐�
extern	int			NS_ChangeWindowMode(						int Flag ) ;																		// �E�C���h�E���[�h��ύX����
extern	int			NS_SetUseCharSet(							int CharSet /* = DX_CHARSET_SHFTJIS �� */ ) ;										// �c�w���C�u�����̕����񏈗��őO��Ƃ��镶����Z�b�g��ݒ肷��
extern	int			NS_LoadPauseGraph(							const TCHAR *FileName ) ;															// �A�N�e�B�u�E�C���h�E�����̃\�t�g�Ɉڂ��Ă���ۂɕ\������摜�̃��[�h(NULL �ŉ���)
extern	int			NS_LoadPauseGraphWithStrLen(				const TCHAR *FileName, size_t FileNameLength ) ;									// �A�N�e�B�u�E�C���h�E�����̃\�t�g�Ɉڂ��Ă���ۂɕ\������摜���t�@�C������ǂݍ���( FileName �� NULL ��n�����Ƃŉ���)
extern	int			NS_LoadPauseGraphFromMem(					const void *MemImage , int MemImageSize ) ;												// �A�N�e�B�u�E�C���h�E�����̃\�t�g�Ɉڂ��Ă���ۂɕ\������摜�̃��[�h(NULL �ŉ���)
extern	int			NS_SetActiveStateChangeCallBackFunction(	int (* CallBackFunction )( int ActiveState , void *UserData ) , void *UserData ) ;	// �E�C���h�E�̃A�N�e�B�u��Ԃɕω����������Ƃ��ɌĂ΂��R�[���o�b�N�֐����Z�b�g����( NULL ���Z�b�g����ƌĂ΂�Ȃ��Ȃ� )
#ifndef DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_SetWindowText(							const TCHAR *WindowText ) ;															// ���C���E�C���h�E�̃E�C���h�E�e�L�X�g��ύX����
#endif // DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_SetWindowTextDX(						const TCHAR *WindowText                          ) ;								// ���C���E�C���h�E�̃E�C���h�E�e�L�X�g��ύX����
extern	int			NS_SetWindowTextWithStrLen(				const TCHAR *WindowText, size_t WindowTextLength ) ;								// ���C���E�C���h�E�̃E�C���h�E�e�L�X�g��ύX����
extern	int			NS_SetMainWindowText(						const TCHAR *WindowText                          ) ;								// SetWindowText �̕ʖ��֐�
extern	int			NS_SetMainWindowTextWithStrLen(			const TCHAR *WindowText, size_t WindowTextLength ) ;								// SetWindowText �̕ʖ��֐�
extern	int			NS_SetMainWindowClassName(					const TCHAR *ClassName                         ) ;									// ���C���E�C���h�E�̃N���X����ݒ肷��( DxLib_Init �̑O�ł̂ݎg�p�\ )
extern	int			NS_SetMainWindowClassNameWithStrLen(		const TCHAR *ClassName, size_t ClassNameLength ) ;									// ���C���E�C���h�E�̃N���X����ݒ肷��( DxLib_Init �̑O�ł̂ݎg�p�\ )
extern	int			NS_SetWindowIconID(						int ID ) ;																			// �g�p����A�C�R���̂h�c���Z�b�g����
extern	int			NS_SetWindowIconHandle(					HICON Icon ) ;																		// �g�p����A�C�R���̃n���h�����Z�b�g����
extern	int			NS_SetUseASyncChangeWindowModeFunction(	int Flag , void (* CallBackFunction )( void * ) , void *Data ) ;					// �ő剻�{�^����ALT+ENTER�L�[�ɂ��񓯊��ȃE�C���h�E���[�h�̕ύX�̋@�\�̐ݒ���s��
extern	int			NS_SetShutdownCallbackFunction(			void (* CallbackFunction )( void * ), void *Data, const TCHAR *Message ) ;			// �V���b�g�_�E���ɂ��\�t�g�̋����I���̍ۂɌĂ΂��R�[���o�b�N�֐���o�^����
extern	int			NS_SetWindowStyleMode(						int Mode ) ;																		// �E�C���h�E�̃X�^�C����ύX����
extern	int			NS_SetWindowZOrder(						int ZType /* = DX_WIN_ZTYPE_TOP �� */ , int WindowActivateFlag ) ;					// ���C���E�C���h�E�̉��s���ʒu��ύX����
extern	int			NS_SetWindowSizeChangeEnableFlag(			int Flag, int FitScreen = TRUE ) ;													// �E�C���h�E�̃T�C�Y��ύX�ł��邩�ǂ����̃t���O���Z�b�g����( NotFitScreen:�E�C���h�E�̃N���C�A���g�̈�ɉ�ʂ��t�B�b�g������(�g�傳����)���ǂ���  TRUE:�t�B�b�g������  FALSE:�t�B�b�g�����Ȃ� )
extern	int			NS_SetWindowSizeExtendRate(				double ExRateX, double ExRateY = -1.0 ) ;											// �`���ʂ̃T�C�Y�ɑ΂���E�C���h�E�T�C�Y�̔䗦��ݒ肷��( ExRateY ���}�C�i�X�̏ꍇ�� ExRateX �̒l�� ExRateY �ɂ��g�p����܂� )
extern	int			NS_SetWindowSize(							int Width, int Height ) ;															// �E�C���h�E���[�h���̃E�C���h�E�̃N���C�A���g�̈�̃T�C�Y��ݒ肷��
extern	int			NS_SetWindowMaxSize(						int MaxWidth, int MaxHeight ) ;														// ���C���E�C���h�E�̃N���C�A���g�̈�̍ő�T�C�Y��ݒ肷��( SetWindowSizeChangeEnableFlag �̑������� TRUE �ŌĂяo���āA�E�C���h�E�̃T�C�Y���ύX�ł����Ԃł̂ݎg�p�����p�����[�^�ł� )
extern	int			NS_SetWindowMinSize(						int MinWidth, int MinHeight ) ;														// ���C���E�C���h�E�̃N���C�A���g�̈�̍ŏ��T�C�Y��ݒ肷��( SetWindowSizeChangeEnableFlag �̑������� TRUE �ŌĂяo���āA�E�C���h�E�̃T�C�Y���ύX�ł����Ԃł̂ݎg�p�����p�����[�^�ł� )
extern	int			NS_SetWindowPosition(						int x, int y ) ;																	// �E�C���h�E���[�h�̃E�C���h�E�̈ʒu��ݒ肷��( �g���܂߂�������W )
extern	int			NS_SetSysCommandOffFlag(					int Flag , const TCHAR *HookDllPath = NULL ) ;										// �^�X�N�X�C�b�`��L���ɂ��邩�ǂ�����ݒ肷��
extern	int			NS_SetSysCommandOffFlagWithStrLen(			int Flag , const TCHAR *HookDllPath = NULL , size_t HookDllPathLength = 0 ) ;		// �^�X�N�X�C�b�`��L���ɂ��邩�ǂ�����ݒ肷��
extern	int			NS_SetWindowMaximizeButtonBehavior(		int BehaviorType ) ;																// ���C���E�C���h�E�̍ő剻�{�^���������ꂽ�Ƃ��̋�����ݒ肷��( BehaviorType 0=�W������ 1=�W������͍s�킸�A�ő剻�{�^���������ꂽ���ǂ����� CheckWindowMaximizeButtonInput �Ŕ��肷�� )
extern	int			NS_SetHookWinProc(							WNDPROC WinProc ) ;																	// ���b�Z�[�W���t�b�N����E�C���h�E�v���[�W����o�^����
extern	int			NS_SetUseHookWinProcReturnValue(			int UseFlag ) ;																		// SetHookWinProc �Őݒ肵���E�C���h�E�v���[�W���̖߂�l���g�p���邩�ǂ�����ݒ肷��ASetHookWinProc �Őݒ肵���E�C���h�E�v���[�W���̒��ł̂ݎg�p�\( UseFlag TRUE:�߂�l���g�p���āA�c�w���C�u�����̃E�C���h�E�v���[�W���̏����͍s��Ȃ�  FALSE:�߂�l�͎g�p�����A�E�C���h�E�v���[�W������o����A�c�w���C�u�����̃E�C���h�E�v���[�W���̏������s�� )
extern	int			NS_SetDoubleStartValidFlag(				int Flag ) ;																		// �Q�d�N�����������ǂ����̃t���O���Z�b�g����
extern	int			NS_CheckDoubleStart(						void ) ;																			// �c�w���C�u�������g�p�����\�t�g�����ɋN�����Ă��邩�ǂ������擾����( TRUE:���ɋN�����Ă���  FALSE:�N�����Ă��Ȃ� )
extern	int			NS_AddMessageTakeOverWindow(				HWND Window ) ;																		// ���b�Z�[�W�������c�w���C�u�����Ɍ����肵�Ă��炤�E�C���h�E��ǉ�����
extern	int			NS_SubMessageTakeOverWindow(				HWND Window ) ;																		// ���b�Z�[�W�������c�w���C�u�����Ɍ����肵�Ă��炤�E�C���h�E�����炷

extern	int			NS_SetWindowInitPosition(					int x , int y ) ;																	// �E�C���h�E�̏����ʒu��ݒ肷��
extern	int			NS_SetNotWinFlag(							int Flag ) ;																		// �c�w���C�u�����̃E�C���h�E�֘A�̋@�\���g�p���Ȃ��t���O
extern	int			NS_SetNotDrawFlag(							int Flag ) ;																		// �`��@�\���g�����ǂ����̃t���O���Z�b�g����
extern	int			NS_SetNotSoundFlag(						int Flag ) ;																		// �T�E���h�@�\���g�����ǂ����̃t���O���Z�b�g����
extern	int			NS_SetNotInputFlag(						int Flag ) ;																		// ���͏�Ԃ̎擾�@�\���g�����ǂ����̃t���O���Z�b�g����
extern	int			NS_SetDialogBoxHandle(						HWND WindowHandle ) ;																// �c�w���C�u�����Ń��b�Z�[�W�������s���_�C�A���O�{�b�N�X��o�^����
extern	int			NS_SetWindowVisibleFlag(					int Flag ) ;																		// ���C���E�C���h�E��\�����邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetWindowMinimizeFlag(					int Flag ) ;																		// ���C���E�C���h�E���ŏ������邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetWindowUserCloseEnableFlag(			int Flag ) ;																		// ���C���E�C���h�E�́~�{�^�������������Ƀ��C�u�����������I�ɃE�C���h�E����邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetUseBorderlessWindowFlag(				int Flag ) ;																		// ���C���E�C���h�E���{�[�_�[���X�E�B���h�E�ɂ��邩�ǂ�����ݒ肷��( TRUE:�{�[�_�[���X�E�B���h�E�@FALSE:�ʏ�E�B���h�E )
extern	int			NS_SetDxLibEndPostQuitMessageFlag(			int Flag ) ;																		// �c�w���C�u�����I������ PostQuitMessage ���ĂԂ��ǂ����̃t���O���Z�b�g����
extern	int			NS_SetUserWindow(							HWND WindowHandle ) ;																// �c�w���C�u�����Ŏg�p����E�C���h�E�̃n���h�����Z�b�g����(DxLib_Init �����s����ȑO�ł̂ݗL��)
extern	int			NS_SetUserChildWindow(						HWND WindowHandle ) ;																// �c�w���C�u�����Ŏg�p����\���p�̎q�E�C���h�E�̃n���h�����Z�b�g����(DxLib_Init �����s����ȑO�ł̂ݗL��)
extern	int			NS_SetUserWindowMessageProcessDXLibFlag(	int Flag ) ;																		// SetUseWindow �Őݒ肵���E�C���h�E�̃��b�Z�[�W���[�v�������c�w���C�u�����ōs�����ǂ����A�t���O���Z�b�g����
extern	int			NS_SetUseFPUPreserveFlag(					int Flag ) ;																		// FPU�̐��x�𗎂Ƃ��Ȃ��ݒ���g�p���邩�ǂ�����ݒ肷��ADxLib_Init ���Ăяo���O�̂ݗL��( TRUE:�g�p����(���x�������Ȃ�)  FALSE:�g�p���Ȃ�(���x�𗎂Ƃ�(�f�t�H���g) )
extern	int			NS_SetValidMousePointerWindowOutClientAreaMoveFlag( int Flag ) ;																// �}�E�X�|�C���^���E�C���h�E�̃N���C�A���g�G���A�̊O�ɂ����邩�ǂ�����ݒ肷��( TRUE:������( �f�t�H���g�ݒ� )  FALSE:�����Ȃ� )
extern	int			NS_SetUseBackBufferTransColorFlag(			int Flag ) ;																		// �o�b�N�o�b�t�@�̓��ߐF�̕����𓧉߂����邩�ǂ�����ݒ肷��( TRUE:���߂�����  FALSE:���߂����Ȃ� )
extern	int			NS_SetUseUpdateLayerdWindowFlag(			int Flag ) ;																		// UpdateLayerdWindowForBaseImage �� UpdateLayerdWindowForSoftImage ���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
extern	int			NS_SetUseMouseEventTransparentWindowFlag(	int Flag ) ;																		// SetUseUpdateLayerdWindowFlag( TRUE ); �̐ݒ�̍ۂɃ}�E�X�֌W�̃C�x���g��w��̃E�B���h�E�ɓ��߂����邩��ݒ肷��( TRUE:���߂���   FALSE:���߂��Ȃ�( �f�t�H���g ) )
extern	int			NS_SetResourceModule(						HMODULE ResourceModule ) ;															// ���\�[�X��ǂݍ��ލۂɎg�p���郂�W���[����ݒ肷��( NULL ���w�肷��Ə�����Ԃɖ߂�܂��A�f�t�H���g�ł� NULL )
extern	int			NS_SetUseDxLibWM_PAINTProcess(				int Flag ) ;																		// WM_PAINT ���b�Z�[�W�������ۂɁw�c�w���C�u������ WM_PAINT���b�Z�[�W�������ۂ̏����x���s�����ǂ�����ݒ肷��( �ʃX���b�h�ŕ`�揈�����s���ꍇ�ȂǂŎg�p )
extern	int			NS_SetWindows10_WM_CHAR_CancelTime(		int MilliSecond ) ;																	// Windows10 �� WM_CHAR �ŒZ���ԂɘA�����ē������������͂��ꂽ�ꍇ�̖��������ɂ��鎞�Ԃ�ݒ肷��( MilliSecond �̃~���b�ȓ��ɘA�����ē������������͂��ꂽ�ꍇ�ɖ����ɂ���AMilliSecond �̒l���}�C�i�X�ɂ���ƃf�t�H���g�̐ݒ�ɖ߂� )
extern	int			NS_SetUseWindows10_WM_CHAR_CancelTime(		int Flag ) ;																		// Windows10 �� WM_CHAR �ŒZ���ԂɘA�����ē������������͂��ꂽ�ꍇ�̖��������ɂ��邩�ǂ�����ݒ肷��( TRUE:�Z���ԘA�����͖͂��������ɂ���(�f�t�H���g)  FALSE:�Z���ԘA�����͂������ɂ��Ȃ� )

// �h���b�O���h���b�v���ꂽ�t�@�C���֌W
extern	int			NS_SetDragFileValidFlag(		int Flag ) ;											// �t�@�C���̃h���b�O���h���b�v�@�\��L���ɂ��邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_DragFileInfoClear(			void ) ;												// �h���b�O���h���b�v���ꂽ�t�@�C���̏�������������
extern	int			NS_GetDragFilePath(			TCHAR *FilePathBuffer, int FilePathBufferBytes DEFAULTPARAM( = -1 ) ) ;								// �h���b�O���h���b�v���ꂽ�t�@�C�������擾����( -1:�擾�ł��Ȃ�����  0:�擾�ł��� )
extern	int			NS_GetDragFileNum(				void ) ;												// �h���b�O���h���b�v���ꂽ�t�@�C���̐����擾����

// �E�C���h�E�`��̈�ݒ�n�֐�
extern	HRGN		NS_CreateRgnFromGraph(			int Width , int Height , const void *MaskData , int Pitch , int Byte ) ;				// �C�ӂ̃O���t�B�b�N����RGN�n���h�����쐬����
extern	HRGN		NS_CreateRgnFromBaseImage(		BASEIMAGE *BaseImage, int TransColorR, int TransColorG, int TransColorB ) ;		// �C�ӂ̊�{�C���[�W�f�[�^�Ɠ��ߐF����RGN�n���h�����쐬����
extern	int			NS_SetWindowRgnGraph(			const TCHAR *FileName ) ;														// �C�ӂ̃O���t�B�b�N����q�f�m���Z�b�g����
extern	int			NS_SetWindowRgnGraphWithStrLen( const TCHAR *FileName, size_t FileNameLength ) ;								// �C�ӂ̉摜�t�@�C������q�f�m���Z�b�g����
extern	int			NS_UpdateTransColorWindowRgn(	void ) ;																		// �`���̉�ʂ̓��ߐF�̕����𓧉߂�����q�f�m���Z�b�g����

// �c�[���o�[�֌W
extern	int			NS_SetupToolBar(				const TCHAR *BitmapName , int DivNum , int ResourceID = -1 ) ;															// �c�[���o�[�̏���( BitmapName �� NULL, ResourceID �� -1 ���w�肷��ƃc�[���o�[�������AResourceID �� -1 �ȊO�� BitmapName �� NULL �̎��ɂ̂� ResourceID ���g�p����� )
extern	int			NS_SetupToolBarWithStrLen(		const TCHAR *BitmapName, size_t BitmapNameLength, int DivNum, int ResourceID = -1 ) ;									// �c�[���o�[�̏����ABitmapName �� NULL, ResourceID �� -1 ��n���ƃc�[���o�[������( BitmapName:�c�[���o�[�̃{�^���Ɏg�p����摜�t�@�C���p�X�AResourceID �� -1 �ȊO��n���ꍇ�� NULL �ɂ���  DivNum:�{�^���摜���̃{�^���̐�  ResourceID:�c�[���o�[�̃{�^���Ɏg�p����r�b�g�}�b�v���\�[�X�̂h�c�ABitmapName �� NULL ��n���Ƃ��̈������g�p����� )
extern	int			NS_AddToolBarButton(			int Type /* TOOLBUTTON_TYPE_NORMAL �� */ , int State /* TOOLBUTTON_STATE_ENABLE �� */ , int ImageIndex, int ID ) ;		// �c�[���o�[�Ƀ{�^����ǉ�
extern	int			NS_AddToolBarSep(				void ) ;																												// �c�[���o�[�Ɍ��Ԃ�ǉ�
extern	int			NS_GetToolBarButtonState(		int ID ) ;																												// �c�[���o�[�̃{�^���̏�Ԃ��擾( TRUE:������Ă��� or �����ꂽ  FALSE:������Ă��Ȃ� )
extern	int			NS_SetToolBarButtonState(		int ID , int State ) ;																									// �c�[���o�[�̃{�^���̏�Ԃ�ݒ�
extern	int			NS_DeleteAllToolBarButton(		void ) ;																												// �c�[���o�[�̃{�^����S�č폜

// ���j���[�֌W
extern	int			NS_SetUseMenuFlag(				int Flag ) ;																						// ���j���[��L���ɂ��邩�ǂ�����ݒ肷��
extern	int			NS_SetUseKeyAccelFlag(			int Flag ) ;																						// �L�[�{�[�h�A�N�Z�����[�^�[���g�p���邩�ǂ�����ݒ肷��

extern	int			NS_AddKeyAccel(				const TCHAR *ItemName , int ItemID , int KeyCode , int CtrlFlag , int AltFlag , int ShiftFlag ) ;	// �V���[�g�J�b�g�L�[��ǉ�����
extern	int			NS_AddKeyAccelWithStrLen(				const TCHAR *ItemName, size_t ItemNameLength, int ItemID , int KeyCode , int CtrlFlag , int AltFlag , int ShiftFlag ) ;	// �V���[�g�J�b�g�L�[��ǉ�����( ItemName:�V���[�g�J�b�g�L�[�����蓖�Ă郁�j���[�̃A�C�e����( AddMenuItem �� NewItemName �ɓn�������O )�AItemID ���g�p����ꍇ�� NULL ��n��  ItemID:���j���[���ڂ̎��ʔԍ�( AddMenuItem �̈��� NewItemID �Ŏw�肵������ )�AItemName ���g�p����ꍇ�� -1 ��n��  KeyCode:�V���[�g�J�b�g�L�[�̃L�[( KEY_INPUT_L �� )  CtrlFlag:������CTRL�L�[�������K�v������悤�ɂ��邩�ǂ���( TRUE:�����K�v������  FALSE:�����Ȃ��Ă��ǂ� )  AltFlag:������ALT�L�[�������K�v������悤�ɂ��邩�ǂ���( TRUE:�����K�v������  FALSE:�����Ȃ��Ă��ǂ� )  ShiftFlag:������SHIFT�L�[�������K�v������悤�ɂ��邩�ǂ���( TRUE:�����K�v������  FALSE:�����Ȃ��Ă��ǂ� )
extern	int			NS_AddKeyAccel_Name(					const TCHAR *ItemName,                        int KeyCode , int CtrlFlag , int AltFlag , int ShiftFlag ) ;				// �V���[�g�J�b�g�L�[��ǉ�����( �e�����̉���� AddKeyAccel �Ɠ����AItemID �������Ȃ������� )
extern	int			NS_AddKeyAccel_NameWithStrLen(			const TCHAR *ItemName, size_t ItemNameLength, int KeyCode , int CtrlFlag , int AltFlag , int ShiftFlag ) ;				// �V���[�g�J�b�g�L�[��ǉ�����( �e�����̉���� AddKeyAccel �Ɠ����AItemID �������Ȃ������� )
extern	int			NS_AddKeyAccel_ID(				int ItemID, int KeyCode, int CtrlFlag, int AltFlag, int ShiftFlag ) ;								// �V���[�g�J�b�g�L�[��ǉ�����
extern	int			NS_ClearKeyAccel(				void ) ;																							// �V���[�g�J�b�g�L�[�̏�������������

extern	int			NS_AddMenuItem(				int AddType /* MENUITEM_ADD_CHILD�� */ , const TCHAR *ItemName, int ItemID, int SeparatorFlag, const TCHAR *NewItemName = NULL , int NewItemID = -1 ) ;	// ���j���[�ɍ��ڂ�ǉ�����
extern	int			NS_AddMenuItemWithStrLen(				int AddType /* MENUITEM_ADD_CHILD�� */ , const TCHAR *ItemName, size_t ItemNameLength, int ItemID, int SeparatorFlag, const TCHAR *NewItemName = NULL , size_t NewItemNameLength = 0 , int NewItemID = -1 ) ;	// ���j���[�ɍ��ڂ�ǉ�����( AddType:���ڃ^�C�v( MENUITEM_ADD_CHILD ��( ����� #define �̒�`���Q�Ƃ��Ă������� ) )    ItemName:AddType �� MENUITEM_ADD_CHILD�̏ꍇ�͐e�ƂȂ鍀�ڂ̖��O�AMENUITEM_ADD_INSERT�̏ꍇ�͑}���ʒu�ƂȂ鍀�ڂ̖��O�ANULL ���w�肷��� ItemID ���g�p�����   ItemID:ItemName �̑���Ɏ��ʔԍ��Ŏw�肷����́AAddType���̈Ⴂ�� ItemName �̉���̒ʂ�A-1���w�肷��� ItemName ���g�p�����@�@SeparatorFlag:��؂����ǉ����邩�ǂ���( TRUE:��؂����ǉ��A���̏ꍇ NewItemName �� NewItemID �͖��������  FALSE:�ǉ�����̂͋�؂���ł͂Ȃ� )�@�@NewItemName:�V�������ڂ̖��O  NewItemID:�V�������ڂ̎��ʔԍ��A-1���w�肷��Ɠ����œK���Ȕԍ������蓖�Ă��� )
extern	int			NS_DeleteMenuItem(						const TCHAR *ItemName,                        int ItemID ) ;														// ���j���[����I�����ڂ��폜����( ItemName:�폜���鍀�ڂ̖��O( AddMenuItem �� NewItemName �ɓn�������O )�ANULL ���w�肷��� ItemID ���g�p�����  ItemID:�폜���鍀�ڂ̎��ʔԍ�( AddMenuItem �� NewItemID �ɓn�����ԍ� )�A-1 ���w�肷��� ItemName ���g�p����� )
extern	int			NS_DeleteMenuItemWithStrLen(			const TCHAR *ItemName, size_t ItemNameLength, int ItemID ) ;														// ���j���[����I�����ڂ��폜����( ItemName:�폜���鍀�ڂ̖��O( AddMenuItem �� NewItemName �ɓn�������O )�ANULL ���w�肷��� ItemID ���g�p�����  ItemID:�폜���鍀�ڂ̎��ʔԍ�( AddMenuItem �� NewItemID �ɓn�����ԍ� )�A-1 ���w�肷��� ItemName ���g�p����� )
extern	int			NS_CheckMenuItemSelect(				const TCHAR *ItemName,                        int ItemID ) ;														// ���j���[���I�����ꂽ���ǂ������擾����( �߂�l�@ 0:�I������Ă��Ȃ�  1:�I�����ꂽ   ItemName �� ItemID �ɂ��Ă͊֐� DeleteMenuItem �̒��߂��Q�Ƃ��Ă������� )
extern	int			NS_CheckMenuItemSelectWithStrLen(		const TCHAR *ItemName, size_t ItemNameLength, int ItemID ) ;														// ���j���[���I�����ꂽ���ǂ������擾����( �߂�l�@ 0:�I������Ă��Ȃ�  1:�I�����ꂽ   ItemName �� ItemID �ɂ��Ă͊֐� DeleteMenuItem �̒��߂��Q�Ƃ��Ă������� )
extern	int			NS_SetMenuItemEnable(					const TCHAR *ItemName,                        int ItemID, int EnableFlag ) ;										// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��( EnableFlag:���ڂ��I���ł��邩�ǂ���( TRUE:�I���ł���   FALSE:�I���ł��Ȃ� )   ItemName �� ItemID �ɂ��Ă͊֐� DeleteMenuItem �̒��߂��Q�Ƃ��Ă������� )
extern	int			NS_SetMenuItemEnableWithStrLen(		const TCHAR *ItemName, size_t ItemNameLength, int ItemID, int EnableFlag ) ;										// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��( EnableFlag:���ڂ��I���ł��邩�ǂ���( TRUE:�I���ł���   FALSE:�I���ł��Ȃ� )   ItemName �� ItemID �ɂ��Ă͊֐� DeleteMenuItem �̒��߂��Q�Ƃ��Ă������� )
extern	int			NS_SetMenuItemMark(					const TCHAR *ItemName,                        int ItemID, int Mark ) ;												// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��( Mark:�ݒ肷��}�[�N( MENUITEM_MARK_NONE ��( ����� #define �̒�`���Q�Ƃ��Ă������� )    ItemName �� ItemID �ɂ��Ă͊֐� DeleteMenuItem �̒��߂��Q�Ƃ��Ă������� ) )
extern	int			NS_SetMenuItemMarkWithStrLen(			const TCHAR *ItemName, size_t ItemNameLength, int ItemID, int Mark ) ;												// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��( Mark:�ݒ肷��}�[�N( MENUITEM_MARK_NONE ��( ����� #define �̒�`���Q�Ƃ��Ă������� )    ItemName �� ItemID �ɂ��Ă͊֐� DeleteMenuItem �̒��߂��Q�Ƃ��Ă������� ) )
extern	int			NS_CheckMenuItemSelectAll(		void ) ;																							// ���j���[�̍��ڂ��ǂꂩ�I�����ꂽ���ǂ������擾����( �߂�l  TRUE:�ǂꂩ�I�����ꂽ  FALSE:�I������Ă��Ȃ� )

extern	int			NS_AddMenuItem_Name(			const TCHAR *ParentItemName, const TCHAR *NewItemName ) ;											// ���j���[�ɑI�����ڂ�ǉ�����
extern	int			NS_AddMenuItem_NameWithStrLen(			const TCHAR *ParentItemName, size_t ParentItemNameLength, const TCHAR *NewItemName, size_t NewItemNameLength ) ;	// ���j���[�ɑI�����ڂ�ǉ�����( ParentItemName:�e�ƂȂ鍀�ڂ̖��O�A�e�������X�g�̖��[�ɐV�������ڂ�ǉ����܂�  NewItemName:�V�������ڂ̖��O )
extern	int			NS_AddMenuLine_Name(					const TCHAR *ParentItemName ) ;																						// ���j���[�̃��X�g�ɋ�؂����ǉ�����( ParentItemName:��؂����t���鍀�ڃ��X�g�̐e�̖��O�A���X�g�̖��[�ɋ�؂����ǉ����܂� )
extern	int			NS_AddMenuLine_NameWithStrLen(			const TCHAR *ParentItemName, size_t ParentItemNameLength ) ;														// ���j���[�̃��X�g�ɋ�؂����ǉ�����( ParentItemName:��؂����t���鍀�ڃ��X�g�̐e�̖��O�A���X�g�̖��[�ɋ�؂����ǉ����܂� )
extern	int			NS_InsertMenuItem_Name(				const TCHAR *ItemName,                        const TCHAR *NewItemName                           ) ;				// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊ԂɐV�������ڂ�ǉ�����
extern	int			NS_InsertMenuItem_NameWithStrLen(		const TCHAR *ItemName, size_t ItemNameLength, const TCHAR *NewItemName, size_t NewItemNameLength ) ;				// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊ԂɐV�������ڂ�ǉ�����
extern	int			NS_InsertMenuLine_Name(				const TCHAR *ItemName                        ) ;																	// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊Ԃɋ�؂����ǉ�����
extern	int			NS_InsertMenuLine_NameWithStrLen(		const TCHAR *ItemName, size_t ItemNameLength ) ;																	// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊Ԃɋ�؂����ǉ�����
extern	int			NS_DeleteMenuItem_Name(				const TCHAR *ItemName                        ) ;																	// ���j���[����I�����ڂ��폜����
extern	int			NS_DeleteMenuItem_NameWithStrLen(		const TCHAR *ItemName, size_t ItemNameLength ) ;																	// ���j���[����I�����ڂ��폜����
extern	int			NS_CheckMenuItemSelect_Name(			const TCHAR *ItemName                        ) ;																	// ���j���[���I�����ꂽ���ǂ������擾����( �߂�l�@0:�I������Ă��Ȃ�  1:�I�����ꂽ )
extern	int			NS_CheckMenuItemSelect_NameWithStrLen(	const TCHAR *ItemName, size_t ItemNameLength ) ;																	// ���j���[���I�����ꂽ���ǂ������擾����( �߂�l�@0:�I������Ă��Ȃ�  1:�I�����ꂽ )
extern	int			NS_SetMenuItemEnable_Name(				const TCHAR *ItemName,                        int EnableFlag ) ;													// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��( EnableFlag�@1:�I���ł���  0:�I���ł��Ȃ� )
extern	int			NS_SetMenuItemEnable_NameWithStrLen(	const TCHAR *ItemName, size_t ItemNameLength, int EnableFlag ) ;													// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��( EnableFlag�@1:�I���ł���  0:�I���ł��Ȃ� )
extern	int			NS_SetMenuItemMark_Name(				const TCHAR *ItemName,                        int Mark ) ;															// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��( Mark:�ݒ肷��}�[�N( MENUITEM_MARK_NONE �� ) )
extern	int			NS_SetMenuItemMark_NameWithStrLen(		const TCHAR *ItemName, size_t ItemNameLength, int Mark ) ;															// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��( Mark:�ݒ肷��}�[�N( MENUITEM_MARK_NONE �� ) )

extern	int			NS_AddMenuItem_ID(				int ParentItemID, const TCHAR *NewItemName, int NewItemID = -1 ) ;									// ���j���[�ɑI�����ڂ�ǉ�����
extern	int			NS_AddMenuItem_IDWithStrLen(			int ParentItemID, const TCHAR *NewItemName, size_t NewItemNameLength, int NewItemID = -1 ) ;						// ���j���[�ɑI�����ڂ�ǉ�����
extern	int			NS_AddMenuLine_ID(				int ParentItemID ) ;																				// ���j���[�̃��X�g�ɋ�؂����ǉ�����
extern	int			NS_InsertMenuItem_ID(			int ItemID, int NewItemID ) ;																		// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊ԂɐV�������ڂ�ǉ�����
extern	int			NS_InsertMenuLine_ID(			int ItemID, int NewItemID ) ;																		// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊Ԃɋ�؂����ǉ�����
extern	int			NS_DeleteMenuItem_ID(			int ItemID ) ;																						// ���j���[����I�����ڂ��폜����
extern	int			NS_CheckMenuItemSelect_ID(		int ItemID ) ;																						// ���j���[���I�����ꂽ���ǂ������擾����( 0:�I������Ă��Ȃ�  1:�I�����ꂽ )
extern	int			NS_SetMenuItemEnable_ID(		int ItemID, int EnableFlag ) ;																		// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��
extern	int			NS_SetMenuItemMark_ID(			int ItemID, int Mark ) ;																			// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��( MENUITEM_MARK_NONE �� )

extern	int			NS_DeleteMenuItemAll(			void ) ;																							// ���j���[�̑S�Ă̑I�����ڂ��폜����
extern	int			NS_ClearMenuItemSelect(		void ) ;																							// ���j���[���I�����ꂽ���ǂ����̏���������
#ifndef DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_GetMenuItemID(				const TCHAR *ItemName ) ;																			// ���j���[�̍��ږ�����h�c���擾����
#endif // DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_GetMenuItemIDDX(				const TCHAR *ItemName ) ;																			// ���j���[�̍��ږ�����h�c���擾����
extern	int			NS_GetMenuItemIDWithStrLen(			const TCHAR *ItemName, size_t ItemNameLength ) ;																	// ���j���[�̍��ږ����獀�ڎ��ʔԍ����擾����
extern	int			NS_GetMenuItemName(			int ItemID, TCHAR *NameBuffer ) ;																	// ���j���[�̍��ږ�����h�c���擾����
extern	int			NS_LoadMenuResource(			int MenuResourceID ) ;																				// ���j���[�����\�[�X����ǂݍ���
extern	int			NS_SetMenuItemSelectCallBackFunction(		void (* CallBackFunction )( const TCHAR *ItemName, int ItemID ) ) ;						// ���j���[�̑I�����ڂ��I�����ꂽ�Ƃ��ɌĂ΂��R�[���o�b�N�֐���ݒ肷��

extern	int			NS_SetWindowMenu(				int MenuID, int (* MenuProc )( WORD ID ) ) ;														// (�Â��֐�)�E�C���h�E�Ƀ��j���[��ݒ肷��
extern	int			NS_SetDisplayMenuFlag(			int Flag ) ;																						// ���j���[��\�����邩�ǂ������Z�b�g����
extern	int			NS_GetDisplayMenuFlag(			void ) ;																							// ���j���[��\�����Ă��邩�ǂ������擾����
extern	int			NS_GetUseMenuFlag(				void ) ;																							// ���j���[���g�p���Ă��邩�ǂ����𓾂�
extern	int			NS_SetAutoMenuDisplayFlag(		int Flag ) ;																						// �t���X�N���[�����Ƀ��j���[�������ŕ\���������\���ɂ����肷�邩�ǂ����̃t���O���Z�b�g����

#endif // WINDOWS_DESKTOP_OS

// �}�E�X�֌W�֐�
extern	int			NS_SetMouseDispFlag(		int DispFlag ) ;												// �}�E�X�̕\���t���O�̃Z�b�g
extern	int			NS_SetMouseDispIgnoreMenuFlag(	int IgnoreMenuFlag ) ;										// �}�E�X�|�C���^�̕\����Ԃɂ��ă��j���[�̕\����Ԃ𖳎����邩�ǂ�����ݒ肷��( TRUE:���j���[�̕\����Ԃ𖳎�����  FALSE:���j���[�̕\����Ԃ��l������( �f�t�H���g ) )
extern	int			NS_GetMousePoint(			int *XBuf, int *YBuf ) ;										// �}�E�X�̈ʒu���擾����
extern	int			NS_SetMousePoint(			int PointX, int PointY ) ;										// �}�E�X�̈ʒu���Z�b�g����
#ifndef DX_NON_INPUT
extern	int			NS_GetMouseInput(			void ) ;														// �}�E�X�̃{�^���̏�Ԃ𓾂� 
extern	int			NS_GetMouseWheelRotVol(	int CounterReset = TRUE ) ;										// �����}�E�X�z�C�[���̉�]�ʂ𓾂�
extern	int			NS_GetMouseHWheelRotVol(	int CounterReset = TRUE ) ;										// �����}�E�X�z�C�[���̉�]�ʂ𓾂�
extern	float		NS_GetMouseWheelRotVolF(	int CounterReset = TRUE ) ;										// �����}�E�X�z�C�[���̉�]�ʂ��擾����( �߂�l�� float �^ )
extern	float		NS_GetMouseHWheelRotVolF(	int CounterReset = TRUE ) ;										// �����}�E�X�z�C�[���̉�]�ʂ��擾����( �߂�l�� float �^ )
extern	int			NS_GetMouseInputLog(		int *Button, int *ClickX, int *ClickY, int LogDelete = TRUE ) ;					// �}�E�X�̃{�^����������������擾����( Button:�����ꂽ�{�^��( MOUSE_INPUT_LEFT �� )���i�[����ϐ��̃A�h���X  ClickX:�����ꂽ���̂w���W���i�[����ϐ��̃A�h���X  ClickY:�����ꂽ���̂x���W���i�[����ϐ��̃A�h���X   LogDelete:�擾������������������O����폜���邩�ǂ���( TRUE:�폜����  FALSE:�폜���Ȃ��A�܂莟�ɂ��̊֐����Ă΂ꂽ�Ƃ��ɓ����l���擾���邱�ƂɂȂ� )�@�@�߂�l  0:�����ꂽ���擾�ł����@-1:�����ꂽ��񂪖��������A�܂�O��̌Ăяo��( �܂��͋N��������ŏ��̌Ăяo�� )�̊ԂɈ�x���}�E�X�̃{�^����������Ȃ����� )
extern	int			NS_GetMouseInputLog2(		int *Button, int *ClickX, int *ClickY, int *LogType, int LogDelete = TRUE ) ;	// �}�E�X�̃{�^�����������藣�����肵��������擾����( Button:�����ꂽ�藣���ꂽ�肵���{�^��( MOUSE_INPUT_LEFT �� )���i�[����ϐ��̃A�h���X  ClickX:�����ꂽ�藣���ꂽ�肵�����̂w���W���i�[����ϐ��̃A�h���X  ClickY:�����ꂽ�藣���ꂽ�肵�����̂x���W���i�[����ϐ��̃A�h���X   LogDelete:�擾���������ꂽ�藣���ꂽ�肵������������O����폜���邩�ǂ���( TRUE:�폜����  FALSE:�폜���Ȃ��A�܂莟�ɂ��̊֐����Ă΂ꂽ�Ƃ��ɓ����l���擾���邱�ƂɂȂ� )�@�@�߂�l  0:�����ꂽ�藣���ꂽ�肵�����擾�ł����@-1:�����ꂽ�藣���ꂽ�肵����񂪖��������A�܂�O��̌Ăяo��( �܂��͋N��������ŏ��̌Ăяo�� )�̊ԂɈ�x���}�E�X�̃{�^���������ꂽ�藣���ꂽ�肵�Ȃ����� )
#endif // DX_NON_INPUT













// �^�b�`�p�l�����͊֌W�֐�
extern	int				NS_GetTouchInputNum( void ) ;															// �^�b�`����Ă��鐔���擾����
extern	int				NS_GetTouchInput( int InputNo, int *PositionX, int *PositionY, int *ID = NULL , int *Device = NULL, float *Pressure = NULL ) ;		// �^�b�`�̏����擾����

extern	int				NS_GetTouchInputLogNum( void ) ;														// �X�g�b�N����Ă���^�b�`���̐����擾����
extern	int				NS_ClearTouchInputLog( void ) ;															// �X�g�b�N����Ă���^�b�`�����N���A����
extern	TOUCHINPUTDATA	NS_GetTouchInputLogOne( int PeekFlag = FALSE ) ;										// �X�g�b�N����Ă���^�b�`��񂩂��ԌÂ������ЂƂ擾����
extern	int				NS_GetTouchInputLog( TOUCHINPUTDATA *TouchData, int GetNum, int PeekFlag = FALSE ) ;	// �X�g�b�N����Ă���^�b�`��񂩂�Â����Ɏw�萔�o�b�t�@�Ɏ擾����( �߂�l  -1:�G���[  0�ȏ�:�擾�������̐� )

extern	int				NS_GetTouchInputDownLogNum( void ) ;														// �X�g�b�N����Ă���^�b�`����n�߂����̐����擾����
extern	int				NS_ClearTouchInputDownLog( void ) ;														// �X�g�b�N����Ă���^�b�`����n�߂������N���A����
extern	TOUCHINPUTPOINT	NS_GetTouchInputDownLogOne( int PeekFlag = FALSE ) ;										// �X�g�b�N����Ă���^�b�`����n�߂���񂩂��ԌÂ������ЂƂ擾����
extern	int				NS_GetTouchInputDownLog( TOUCHINPUTPOINT *PointData, int GetNum, int PeekFlag = FALSE ) ;	// �X�g�b�N����Ă���^�b�`����n�߂���񂩂�Â����Ɏw�萔�o�b�t�@�Ɏ擾����( �߂�l  -1:�G���[  0�ȏ�:�擾�������̐� )

extern	int				NS_GetTouchInputUpLogNum( void ) ;															// �X�g�b�N����Ă���^�b�`�������ꂽ���̐����擾����
extern	int				NS_ClearTouchInputUpLog( void ) ;															// �X�g�b�N����Ă���^�b�`�������ꂽ�����N���A����
extern	TOUCHINPUTPOINT	NS_GetTouchInputUpLogOne( int PeekFlag = FALSE ) ;											// �X�g�b�N����Ă���^�b�`�������ꂽ��񂩂��ԌÂ������ЂƂ擾����
extern	int				NS_GetTouchInputUpLog( TOUCHINPUTPOINT *PointData, int GetNum, int PeekFlag = FALSE ) ;	// �X�g�b�N����Ă���^�b�`�������ꂽ��񂩂�Â����Ɏw�萔�o�b�t�@�Ɏ擾����( �߂�l  -1:�G���[  0�ȏ�:�擾�������̐� )


















// DxMemory.cpp�֐��v���g�^�C�v�錾

// �������m�یn�֐�
extern	void*		NS_DxAlloc(						size_t AllocSize , const char *File = NULL , int Line = -1 ) ;					// ���������m�ۂ���
extern	void*		NS_DxAllocAligned(					               size_t AllocSize , size_t Alignment , const char *File = NULL , int Line = -1 ) ;	// �w��̃T�C�Y�̃��������m�ۂ���( �A���C���w��� )( AllocSize:�m�ۂ��郁�����̃T�C�Y( �P��:byte )  Alignment:�m�ۂ��郁�����̈�̃A�h���X�l�̔{��  File:DxAlloc���Ă񂾃\�[�X�t�@�C����( �f�o�b�O�p )  Line:DxAlloc���Ă񂾃\�[�X�t�@�C�����̍s�ԍ�( �f�o�b�O�p )�@�@�߂�l  NULL:�������̊m�ێ��s   NULL�ȊO:�m�ۂ����������̈�̐擪�A�h���X )
extern	void*		NS_DxCalloc(						size_t AllocSize , const char *File = NULL , int Line = -1 ) ;					// ���������m�ۂ��ĂO�ŏ���������
extern	void*		NS_DxCallocAligned(				               size_t AllocSize , size_t Alignment , const char *File = NULL , int Line = -1 ) ;	// �w��̃T�C�Y�̃��������m�ۂ��āA�O�Ŗ��߂�A��������ɂO�Ŗ��߂�ȊO�� DxAllocAligned �Ɠ���͓���
extern	void*		NS_DxRealloc(						void *Memory , size_t AllocSize , const char *File = NULL , int Line = -1 ) ;	// �������̍Ċm�ۂ��s��
extern	void*		NS_DxReallocAligned(				void *Memory , size_t AllocSize , size_t Alignment , const char *File = NULL , int Line = -1 ) ;	// �������̍Ċm�ۂ��s��( �A���C���w��� )( Memory:�Ċm�ۂ��s���������̈�̐擪�A�h���X( DxAlloc �̖߂�l )  AllocSize:�V�����m�ۃT�C�Y   Alignment:�V�����m�ۂ��郁�����̈�̃A�h���X�l�̔{���@File��Line �̐����� DxAlloc �̒��߂̒ʂ� �@�߂�l NULL:�������̍Ċm�ێ��s�@NULL�ȊO:�Ċm�ۂ����V�����������̈�̐擪�A�h���X�@)
extern	void		NS_DxFree(							void *Memory ) ;																// ���������������
extern	size_t		NS_DxSetAllocSizeTrap(				size_t Size ) ;																	// �񋓑Ώۂɂ��郁�����̊m�ۗe�ʂ��Z�b�g����
extern	int			NS_DxSetAllocPrintFlag(			int Flag ) ;																	// �c�w���C�u�������Ń������m�ۂ��s���鎞�ɏ����o�͂��邩�ǂ������Z�b�g����
extern	size_t		NS_DxGetAllocSize(					void ) ;																		// DxAlloc �� DxCalloc �Ŋm�ۂ��Ă��郁�����T�C�Y���擾����
extern	int			NS_DxGetAllocNum(					void ) ;																		// DxAlloc �� DxCalloc �Ŋm�ۂ��Ă��郁�����̐����擾����
extern	void		NS_DxDumpAlloc(					void ) ;																		// DxAlloc �� DxCalloc �Ŋm�ۂ��Ă��郁������񋓂���
extern	void		NS_DxDrawAlloc(					int x, int y, int Width, int Height ) ;											// DxAlloc �� DxCalloc �Ŋm�ۂ��Ă��郁�����̏󋵂�`�悷��
extern	int			NS_DxErrorCheckAlloc(				void ) ;																		// �m�ۂ�����������񂪔j�󂳂�Ă��Ȃ������ׂ�( -1:�j�󂠂�  0:�Ȃ� )
extern	int			NS_DxSetAllocSizeOutFlag(			int Flag ) ;																	// ���������m�ہA������s����x�Ɋm�ۂ��Ă��郁�����̗e�ʂ��o�͂��邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_DxSetAllocMemoryErrorCheckFlag(	int Flag ) ;																	// �������̊m�ہA������s����x�Ɋm�ۂ��Ă��郁�����m�ۏ�񂪔j�����Ă��Ȃ������ׂ邩�ǂ����̃t���O���Z�b�g����














// DxBaseFunc.cpp �֐��v���g�^�C�v�錾

// �����R�[�h�֌W
extern	int			NS_GetCharBytes( int CharCodeFormat /* DX_CHARCODEFORMAT_SHIFTJIS �� */ , const void *String ) ;																												// ������̐擪�̕����̃o�C�g�����擾����
extern	int			NS_ConvertStringCharCodeFormat( int SrcCharCodeFormat /* DX_CHARCODEFORMAT_SHIFTJIS �� */, const void *SrcString, int DestCharCodeFormat /* DX_CHARCODEFORMAT_SHIFTJIS �� */, void *DestStringBuffer ) ;		// ������̕����R�[�h�`����ʂ̕����R�[�h�`���ɕϊ�����
extern	int			NS_SetUseCharCodeFormat( int CharCodeFormat /* DX_CHARCODEFORMAT_SHIFTJIS �� */ ) ;																														// ������̈����̕����R�[�h�`����ݒ肷��( ������`��n�֐��Ƃ��̑��ꕔ�֐������� )( UNICODE�łł͖��� )
extern	int			NS_GetUseCharCodeFormat( void ) ;															// ������̈����̕����R�[�h�`�����擾����( �߂�l�F�����R�[�h�`��( DX_CHARCODEFORMAT_SHIFTJIS �� ) )( UNICODE�łł͖��� )
extern	int			NS_Get_wchar_t_CharCodeFormat( void ) ;														// wchar_t�^�̕����R�[�h�`�����擾����( �߂�l�F DX_CHARCODEFORMAT_UTF16LE �Ȃ� )

// ������֌W
extern	void			NS_strcpyDx(      TCHAR *Dest,                   const TCHAR *Src ) ;						// strcpy �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strcpy_sDx(    TCHAR *Dest, size_t DestBytes, const TCHAR *Src ) ;						// strcpy_s �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strpcpyDx(     TCHAR *Dest,                   const TCHAR *Src, int Pos ) ;				// �ʒu�w��t�� strcpy�APos �̓R�s�[�J�n�ʒu�@( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strpcpy_sDx(   TCHAR *Dest, size_t DestBytes, const TCHAR *Src, int Pos ) ;				// �ʒu�w��t�� strcpy_s�APos �̓R�s�[�J�n�ʒu�@( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strpcpy2Dx(    TCHAR *Dest,                   const TCHAR *Src, int Pos ) ;				// �ʒu�w��t�� strcpy�APos �̓R�s�[�J�n�ʒu( �S�p������ 1 ���� )�@( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strpcpy2_sDx(  TCHAR *Dest, size_t DestBytes, const TCHAR *Src, int Pos ) ;				// �ʒu�w��t�� strcpy_s�APos �̓R�s�[�J�n�ʒu( �S�p������ 1 ���� )�@( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strncpyDx(     TCHAR *Dest,                   const TCHAR *Src, int Num ) ;				// strncpy �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strncpy_sDx(   TCHAR *Dest, size_t DestBytes, const TCHAR *Src, int Num ) ;				// strncpy_s �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strncpy2Dx(    TCHAR *Dest,                   const TCHAR *Src, int Num ) ;				// strncpy �� Num ��������( �S�p������ 1 ���� )�ɂȂ������́A�I�[�ɕK���k����������������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strncpy2_sDx(  TCHAR *Dest, size_t DestBytes, const TCHAR *Src, int Num ) ;				// strncpy_s �� Num ��������( �S�p������ 1 ���� )�ɂȂ������́A�I�[�ɕK���k����������������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strrncpyDx(    TCHAR *Dest,                   const TCHAR *Src, int Num ) ;				// strncpy �̕�����̏I�[����̕������w���( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strrncpy_sDx(  TCHAR *Dest, size_t DestBytes, const TCHAR *Src, int Num ) ;				// strncpy_s �̕�����̏I�[����̕������w���( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strrncpy2Dx(   TCHAR *Dest,                   const TCHAR *Src, int Num ) ;				// strncpy �̕�����̏I�[����̕�����( �S�p������ 1 ���� )�w��ŁA�I�[�ɕK���k����������������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strrncpy2_sDx( TCHAR *Dest, size_t DestBytes, const TCHAR *Src, int Num ) ;				// strncpy_s �̕�����̏I�[����̕�����( �S�p������ 1 ���� )�w��ŁA�I�[�ɕK���k����������������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strpncpyDx(    TCHAR *Dest,                   const TCHAR *Src, int Pos, int Num ) ;	// strncpy �̃R�s�[�J�n�ʒu�w��ŁAPos �̓R�s�[�J�n�ʒu�ANum �͕�����( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strpncpy_sDx(  TCHAR *Dest, size_t DestBytes, const TCHAR *Src, int Pos, int Num ) ;	// strncpy_s �̃R�s�[�J�n�ʒu�w��ŁAPos �̓R�s�[�J�n�ʒu�ANum �͕�����( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strpncpy2Dx(   TCHAR *Dest,                   const TCHAR *Src, int Pos, int Num ) ;	// strncpy �̃R�s�[�J�n�ʒu�w��ŁAPos �̓R�s�[�J�n�ʒu( �S�p������ 1 ���� )�ANum �͕�����( �S�p������ 1 ���� )�A�I�[�ɕK���k����������������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strpncpy2_sDx( TCHAR *Dest, size_t DestBytes, const TCHAR *Src, int Pos, int Num ) ;	// strncpy_s �̃R�s�[�J�n�ʒu�w��ŁAPos �̓R�s�[�J�n�ʒu( �S�p������ 1 ���� )�ANum �͕�����( �S�p������ 1 ���� )�A�I�[�ɕK���k����������������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strcatDx(      TCHAR *Dest,                   const TCHAR *Src ) ;						// strcat �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	void			NS_strcat_sDx(    TCHAR *Dest, size_t DestBytes, const TCHAR *Src ) ;						// strcat_s �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	size_t			NS_strlenDx(      const TCHAR *Str ) ;												// strlen �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	size_t			NS_strlen2Dx(     const TCHAR *Str ) ;												// strlen �̖߂�l��������( �S�p������ 1 ���� )�ɂȂ�������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strcmpDx(      const TCHAR *Str1, const TCHAR *Str2 ) ;							// strcmp �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_stricmpDx(     const TCHAR *Str1, const TCHAR *Str2 ) ;							// stricmp �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strncmpDx(     const TCHAR *Str1, const TCHAR *Str2, int Num ) ;				// strncmp �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strncmp2Dx(    const TCHAR *Str1, const TCHAR *Str2, int Num ) ;				// strncmp �� Num ��������( �S�p������ 1 ���� )�ɂȂ�������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strpncmpDx(    const TCHAR *Str1, const TCHAR *Str2, int Pos, int Num ) ;		// strncmp �̔�r�J�n�ʒu�w��ŁAPos �� Str1 �̔�r�J�n�ʒu�ANum ��������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strpncmp2Dx(   const TCHAR *Str1, const TCHAR *Str2, int Pos, int Num ) ;		// strncmp �̔�r�J�n�ʒu�w��ŁAPos �� Str1 �̔�r�J�n�ʒu( �S�p������ 1 ���� )�ANum ��������( �S�p������ 1 ���� )( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	DWORD			NS_strgetchrDx(   const TCHAR *Str, int Pos, int *CharNums = NULL ) ;				// ������̎w��̈ʒu�̕����R�[�h���擾����APos �͎擾����ʒu�ACharNums �͕�������������ϐ��̃A�h���X�A�߂�l�͕����R�[�h( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	DWORD			NS_strgetchr2Dx(  const TCHAR *Str, int Pos, int *CharNums = NULL ) ;				// ������̎w��̈ʒu�̕����R�[�h���擾����APos �͎擾����ʒu( �S�p������ 1 ���� )�ACharNums �͕�������������ϐ��̃A�h���X�A�߂�l�͕����R�[�h( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strputchrDx(   TCHAR *Str, int Pos, DWORD CharCode ) ;							// ������̎w��̈ʒu�ɕ����R�[�h���������ށAPos �͏������ވʒu�ACharCode �͕����R�[�h�A�߂�l�͏������񂾕�����( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strputchr2Dx(  TCHAR *Str, int Pos, DWORD CharCode ) ;							// ������̎w��̈ʒu�ɕ����R�[�h���������ށAPos �͏������ވʒu( �S�p������ 1 ���� )�ACharCode �͕����R�[�h�A�߂�l�͏������񂾕�����( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	const TCHAR *	NS_strposDx(      const TCHAR *Str, int Pos ) ;									// ������̎w��̈ʒu�̃A�h���X���擾����APos �͎擾����ʒu�@( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	const TCHAR *	NS_strpos2Dx(     const TCHAR *Str, int Pos ) ;									// ������̎w��̈ʒu�̃A�h���X���擾����APos �͎擾����ʒu( �S�p������ 1 ���� )�@( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	const TCHAR *	NS_strstrDx(      const TCHAR *Str1, const TCHAR *Str2 ) ;							// strstr �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strstr2Dx(     const TCHAR *Str1, const TCHAR *Str2 ) ;							// strstr �̖߂�l��������擪����̕�����( �S�p������ 1 ���� ) �ɂȂ�������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	const TCHAR *	NS_strrstrDx(     const TCHAR *Str1, const TCHAR *Str2 ) ;							// strrstr �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strrstr2Dx(    const TCHAR *Str1, const TCHAR *Str2 ) ;							// strrstr �̖߂�l��������擪����̕�����( �S�p������ 1 ���� ) �ɂȂ�������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	const TCHAR *	NS_strchrDx(      const TCHAR *Str, DWORD CharCode ) ;								// strchr �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strchr2Dx(     const TCHAR *Str, DWORD CharCode ) ;								// strchr �̖߂�l��������擪����̕�����( �S�p������ 1 ���� ) �ɂȂ�������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	const TCHAR *	NS_strrchrDx(     const TCHAR *Str, DWORD CharCode ) ;								// strrchr �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_strrchr2Dx(    const TCHAR *Str, DWORD CharCode ) ;								// strrchr �̖߂�l��������擪����̕�����( �S�p������ 1 ���� ) �ɂȂ�������( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	TCHAR *			NS_struprDx(      TCHAR *Str ) ;													// strupr �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_vsprintfDx(    TCHAR *Buffer,                    const TCHAR *FormatString, va_list Arg ) ;	// vsprintf �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_vsnprintfDx(   TCHAR *Buffer, size_t BufferSize, const TCHAR *FormatString, va_list Arg ) ;	// vsnprintf �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_sprintfDx(     TCHAR *Buffer,                    const TCHAR *FormatString, ... ) ;			// sprintf �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_snprintfDx(    TCHAR *Buffer, size_t BufferSize, const TCHAR *FormatString, ... ) ;			// snprintf �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	TCHAR *			NS_itoaDx(        int Value, TCHAR *Buffer,                     int Radix ) ;		// itoa �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	TCHAR *			NS_itoa_sDx(      int Value, TCHAR *Buffer, size_t BufferBytes, int Radix ) ;		// itoa_s �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_atoiDx(       const TCHAR *Str ) ;												// atoi �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	double			NS_atofDx(       const TCHAR *Str ) ;												// atof �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_vsscanfDx(    const TCHAR *String, const TCHAR *FormatString, va_list Arg ) ;	// vsscanf �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )
extern	int				NS_sscanfDx(     const TCHAR *String, const TCHAR *FormatString, ... ) ;			// sscanf �Ɠ����̋@�\( �}���`�o�C�g������łł͕����R�[�h�`���Ƃ��� SetUseCharCodeFormat �Őݒ肵���`�����g�p����܂� )













// DxInputString.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_INPUTSTRING

// �����R�[�h�o�b�t�@����֌W
extern	int			NS_StockInputChar(		TCHAR CharCode ) ;								// �o�b�t�@�ɃR�[�h���X�g�b�N����
extern	int			NS_ClearInputCharBuf(	void ) ;										// �����R�[�h�o�b�t�@���N���A����
extern	TCHAR		NS_GetInputChar(		int DeleteFlag ) ;								// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^���當���R�[�h���擾����
extern	TCHAR		NS_GetInputCharWait(	int DeleteFlag ) ;								// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^����P�o�C�g���擾����A�o�b�t�@�ɂȂɂ������R�[�h���Ȃ��ꍇ�̓L�[���������܂ő҂�

extern	int			NS_GetOneChar(			TCHAR *CharBuffer, int DeleteFlag ) ;			// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^����P�������擾����
extern	int			NS_GetOneCharWait(		TCHAR *CharBuffer, int DeleteFlag ) ;			// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^����P�������擾����A�o�b�t�@�ɉ��������R�[�h���Ȃ��ꍇ�̓L�[���������܂ő҂�
extern	int			NS_GetCtrlCodeCmp(		TCHAR Char ) ;									// �A�X�L�[�R���g���[���R�[�h�����ׂ�

#endif // DX_NON_INPUTSTRING

#ifndef DX_NON_KEYEX

extern	int			NS_DrawIMEInputString(				int x, int y,                                 int SelectStringNum , int DrawCandidateList = TRUE ) ;	// ��ʏ�ɓ��͒��̕������`�悷��
extern	int			NS_DrawIMEInputExtendString(		int x, int y, double ExRateX, double ExRateY, int SelectStringNum , int DrawCandidateList DEFAULTPARAM( = TRUE ) ) ;	// ��ʏ�ɓ��͒��̕������`�悷��( �g�嗦�t�� )
extern	int			NS_SetUseIMEFlag(					int UseFlag ) ;							// �h�l�d���g�p���邩�ǂ������Z�b�g����
extern	int			NS_GetUseIMEFlag(					void ) ;								// �h�l�d���g�p���邩�ǂ����̐ݒ���擾����
extern	int			NS_SetInputStringMaxLengthIMESync(	int Flag ) ;							// �h�l�d�œ��͂ł���ő啶������ MakeKeyInput �̐ݒ�ɍ��킹�邩�ǂ������Z�b�g����( TRUE:���킹��  FALSE:���킹�Ȃ�(�f�t�H���g) )
extern	int			NS_SetIMEInputStringMaxLength(		int Length ) ;							// �h�l�d�ň�x�ɓ��͂ł���ő啶������ݒ肷��( 0:�����Ȃ�  1�ȏ�:�w��̕������Ő��� )
extern	int			NS_SetUseTSFFlag( int UseFlag ) ;											// �h�l�d�̊����ϊ����\���̏����� TSF ���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����( �f�t�H���g )  FALSE:�g�p���Ȃ� )

#endif

extern	int			NS_GetStringPoint(				const TCHAR *String, int Point ) ;			// �S�p�����A���p�������藐��钆����w��̕������ł̔��p�������𓾂�
extern	int			NS_GetStringPointWithStrLen(	const TCHAR *String, size_t StringLength, int Point ) ;		// �S�p�����A���p�������藐��钆����w��̕������ł̔��p�������𓾂�
extern	int			NS_GetStringPoint2(			const TCHAR *String,                      int Point ) ;		// �S�p�����A���p�������藐��钆����w��̔��p�������ł̕������𓾂�
extern	int			NS_GetStringPoint2WithStrLen(	const TCHAR *String, size_t StringLength, int Point ) ;		// �S�p�����A���p�������藐��钆����w��̔��p�������ł̕������𓾂�
extern	int			NS_GetStringLength(			const TCHAR *String ) ;						// �S�p�����A���p�������藐��钆���當�������擾����

#ifndef DX_NON_FONT
extern	int			NS_DrawObtainsString(						int x, int y, int AddY, const TCHAR *String,                      unsigned int StrColor, unsigned int StrEdgeColor = 0 , int FontHandle = -1 , unsigned int SelectBackColor = 0xffffffff , unsigned int SelectStrColor = 0 , unsigned int SelectStrEdgeColor = 0xffffffff , int SelectStart = -1 , int SelectEnd = -1 , int *LineCount = NULL ) ;		// �`��\�̈�Ɏ��܂�悤�ɉ��s���Ȃ��當�����`��
extern	int			NS_DrawObtainsNString(						int x, int y, int AddY, const TCHAR *String, size_t StringLength, unsigned int StrColor, unsigned int StrEdgeColor = 0 , int FontHandle = -1 , unsigned int SelectBackColor = 0xffffffff , unsigned int SelectStrColor = 0 , unsigned int SelectStrEdgeColor = 0xffffffff , int SelectStart = -1 , int SelectEnd = -1 , int *LineCount = NULL ) ;		// �`��\�̈�Ɏ��܂�悤�ɉ��s���Ȃ��當�����`��
extern	int			NS_DrawObtainsString_CharClip(				int x, int y, int AddY, const TCHAR *String,                      unsigned int StrColor, unsigned int StrEdgeColor = 0 , int FontHandle = -1 , unsigned int SelectBackColor = 0xffffffff , unsigned int SelectStrColor = 0 , unsigned int SelectStrEdgeColor = 0xffffffff , int SelectStart = -1 , int SelectEnd = -1 , int *LineCount = NULL ) ;		// �`��\�̈�Ɏ��܂�悤�ɉ��s���Ȃ��當�����`��( �N���b�v�������P�� )
extern	int			NS_DrawObtainsNString_CharClip(				int x, int y, int AddY, const TCHAR *String, size_t StringLength, unsigned int StrColor, unsigned int StrEdgeColor = 0 , int FontHandle = -1 , unsigned int SelectBackColor = 0xffffffff , unsigned int SelectStrColor = 0 , unsigned int SelectStrEdgeColor = 0xffffffff , int SelectStart = -1 , int SelectEnd = -1 , int *LineCount = NULL ) ;		// �`��\�̈�Ɏ��܂�悤�ɉ��s���Ȃ��當�����`��( �N���b�v�������P�� )
extern	int			NS_DrawObtainsString_WordClip(				int x, int y, int AddY, const TCHAR *String,                      unsigned int StrColor, unsigned int StrEdgeColor = 0 , int FontHandle = -1 , unsigned int SelectBackColor = 0xffffffff , unsigned int SelectStrColor = 0 , unsigned int SelectStrEdgeColor = 0xffffffff , int SelectStart = -1 , int SelectEnd = -1 , int *LineCount = NULL ) ;		// �`��\�̈�Ɏ��܂�悤�ɉ��s���Ȃ��當�����`��( �N���b�v���P��P�� )
extern	int			NS_DrawObtainsNString_WordClip(				int x, int y, int AddY, const TCHAR *String, size_t StringLength, unsigned int StrColor, unsigned int StrEdgeColor = 0 , int FontHandle = -1 , unsigned int SelectBackColor = 0xffffffff , unsigned int SelectStrColor = 0 , unsigned int SelectStrEdgeColor = 0xffffffff , int SelectStart = -1 , int SelectEnd = -1 , int *LineCount = NULL ) ;		// �`��\�̈�Ɏ��܂�悤�ɉ��s���Ȃ��當�����`��( �N���b�v���P��P�� )
extern	int			NS_GetObtainsStringCharPosition(			int x, int y, int AddY, const TCHAR *String, int StrLen, int *PosX, int *PosY, int FontHandle = -1, int *LineCount = NULL ) ;		// �`��\�̈�Ɏ��܂�悤�ɉ��s���Ȃ��當�����`�悵���ꍇ�̕�����̖��[�̍��W���擾����
extern	int			NS_GetObtainsStringCharPosition_CharClip(	int x, int y, int AddY, const TCHAR *String, int StrLen, int *PosX, int *PosY, int FontHandle = -1, int *LineCount = NULL ) ;		// �`��\�̈�Ɏ��܂�悤�ɉ��s���Ȃ��當�����`�悵���ꍇ�̕�����̖��[�̍��W���擾����( �N���b�v�������P�� )
extern	int			NS_GetObtainsStringCharPosition_WordClip(	int x, int y, int AddY, const TCHAR *String, int StrLen, int *PosX, int *PosY, int FontHandle = -1, int *LineCount = NULL ) ;		// �`��\�̈�Ɏ��܂�悤�ɉ��s���Ȃ��當�����`�悵���ꍇ�̕�����̖��[�̍��W���擾����( �N���b�v���P��P�� )
#endif // DX_NON_FONT
extern	int			NS_DrawObtainsBox(				int x1, int y1, int x2, int y2, int AddY, unsigned int Color, int FillFlag ) ;																																										// �K��̈�Ɏ��߂��������ŋ�`��`�� 

#ifndef DX_NON_KEYEX

extern	int			NS_InputStringToCustom(		int x, int y, size_t BufLength, TCHAR *StrBuffer, int CancelValidFlag, int SingleCharOnlyFlag, int NumCharOnlyFlag, int DoubleCharOnlyFlag = FALSE , int EnableNewLineFlag = FALSE , int DisplayCandidateList = TRUE ) ;		// ������̓��͎擾

extern	int			NS_KeyInputString(				int x, int y, size_t CharMaxLength, TCHAR *StrBuffer, int CancelValidFlag ) ;														// ������̓��͎擾
extern	int			NS_KeyInputSingleCharString(	int x, int y, size_t CharMaxLength, TCHAR *StrBuffer, int CancelValidFlag ) ;														// ���p������݂̂̓��͎擾
extern	int			NS_KeyInputNumber(				int x, int y, int MaxNum, int MinNum, int CancelValidFlag ) ;																	// ���l�̓���

extern	int			NS_GetIMEInputModeStr(			TCHAR *GetBuffer ) ;																											// IME�̓��̓��[�h������̎擾
extern	const IMEINPUTDATA* NS_GetIMEInputData(			void ) ;																														// IME�œ��͒��̕�����̏����擾����
extern	int			NS_SetIMEInputString(				const TCHAR *String ) ;																											// IME�œ��͒��̕������ύX����( IME�ŕ��������͒��ł͂Ȃ������ꍇ�͉����N����܂��� )
extern	int			NS_SetIMEInputStringWithStrLen(	const TCHAR *String, size_t StringLength ) ;																					// IME�œ��͒��̕������ύX����( IME�ŕ��������͒��ł͂Ȃ������ꍇ�͉����N����܂��� )
extern	int			NS_SetKeyInputStringColor(		ULONGLONG NmlStr, ULONGLONG NmlCur, ULONGLONG IMEStrBack, ULONGLONG IMECur, ULONGLONG IMELine, ULONGLONG IMESelectStr, ULONGLONG IMEModeStr , ULONGLONG NmlStrE = 0 , ULONGLONG IMESelectStrE = 0 , ULONGLONG IMEModeStrE = 0 , ULONGLONG IMESelectWinE = ULL_PARAM( 0xffffffffffffffff ) ,	ULONGLONG IMESelectWinF = ULL_PARAM( 0xffffffffffffffff ) , ULONGLONG SelectStrBackColor = ULL_PARAM( 0xffffffffffffffff ) , ULONGLONG SelectStrColor = ULL_PARAM( 0xffffffffffffffff ) , ULONGLONG SelectStrEdgeColor = ULL_PARAM( 0xffffffffffffffff ), ULONGLONG IMEStr = ULL_PARAM( 0xffffffffffffffff ), ULONGLONG IMEStrE = ULL_PARAM( 0xffffffffffffffff ) ) ;	// InputString�֐��g�p���̕����̊e�F��ύX����
extern	int			NS_SetKeyInputStringColor2(	int TargetColor /* DX_KEYINPSTRCOLOR_NORMAL_STR �� */, unsigned int Color ) ;															// InputString�֐��g�p���̕����̊e�F��ύX����
extern	int			NS_ResetKeyInputStringColor2(	int TargetColor /* DX_KEYINPSTRCOLOR_NORMAL_STR �� */ ) ;																		// SetKeyInputStringColor2 �Őݒ肵���F���f�t�H���g�ɖ߂�
extern	int			NS_SetKeyInputStringFont(		int FontHandle ) ;																												// �L�[���͕�����`��֘A�Ŏg�p����t�H���g�̃n���h����ύX����(-1�Ńf�t�H���g�̃t�H���g�n���h��)
extern	int			NS_SetKeyInputStringEndCharaMode( int EndCharaMode /* DX_KEYINPSTR_ENDCHARAMODE_OVERWRITE �� */ ) ;															// �L�[���͕����񏈗��̓��͕����������E�ɒB���Ă����ԂŁA������̖��[�����œ��͂��s��ꂽ�ꍇ�̏������[�h��ύX����
extern	int			NS_DrawKeyInputModeString(		int x, int y ) ;																												// ���̓��[�h�������`�悷��

extern	int			NS_InitKeyInput(				void ) ;																														// �L�[���̓f�[�^������
extern	int			NS_MakeKeyInput(				size_t MaxStrLength, int CancelValidFlag, int SingleCharOnlyFlag, int NumCharOnlyFlag, int DoubleCharOnlyFlag = FALSE , int EnableNewLineFlag = FALSE ) ;			// �V�����L�[���̓f�[�^�̍쐬
extern	int			NS_DeleteKeyInput(				int InputHandle ) ;																												// �L�[���̓f�[�^�̍폜
extern	int			NS_SetActiveKeyInput(			int InputHandle ) ;																												// �w��̃L�[���͂��A�N�e�B�u�ɂ���( -1 ���w�肷��ƃA�N�e�B�u�ȃL�[���̓n���h����������ԂɂȂ�܂� )
extern	int			NS_GetActiveKeyInput(			void ) ;																														// ���݃A�N�e�B�u�ɂȂ��Ă���L�[���̓n���h�����擾����
extern	int			NS_CheckKeyInput(				int InputHandle ) ;																												// ���͂��I�����Ă��邩�擾����
extern	int			NS_ReStartKeyInput(			int InputHandle ) ;																												// ���͂����������L�[���͂��ēx�ҏW��Ԃɖ߂�
extern	int			NS_ProcessActKeyInput(			void ) ;																														// �L�[���͏����֐�
extern	int			NS_DrawKeyInputString(			int x, int y, int InputHandle , int DrawCandidateList = TRUE ) ;																								// �L�[���͒��f�[�^�̕`��
extern	int			NS_DrawKeyInputExtendString(		int x, int y, double ExRateX, double ExRateY, int InputHandle , int DrawCandidateList DEFAULTPARAM( = TRUE ) ) ;				// �L�[���̓n���h���̓��͒����̕`��( �g�嗦�w��t�� )
extern	int			NS_SetKeyInputDrawArea(		int x1, int y1, int x2, int y2, int InputHandle ) ;																				// �L�[���̓n���h���̓��͒��������`�悷��ۂ̕`��͈͂�ݒ肷��

extern	int			NS_SetKeyInputSelectArea(		int  SelectStart, int  SelectEnd, int InputHandle ) ;																			// �L�[���̓f�[�^�̎w��̗̈��I����Ԃɂ���( SelectStart �� SelectEnd �� -1 ���w�肷��ƑI����Ԃ���������܂� )
extern	int			NS_GetKeyInputSelectArea(		int *SelectStart, int *SelectEnd, int InputHandle ) ;																			// �L�[���̓f�[�^�̑I��̈���擾����
extern	int			NS_SetKeyInputDrawStartPos(	int DrawStartPos, int InputHandle ) ;																							// �L�[���͂̕`��J�n�����ʒu��ݒ肷��
extern	int			NS_GetKeyInputDrawStartPos(	int InputHandle ) ;																												// �L�[���͂̕`��J�n�����ʒu���擾����
extern	int			NS_SetKeyInputCursorBrinkTime(	int Time ) ;																													// �L�[���͎��̃J�[�\���̓_�ł��鑁�����Z�b�g����
extern	int			NS_SetKeyInputCursorBrinkFlag(	int Flag ) ;																													// �L�[���͎��̃J�[�\����_�ł����邩�ǂ������Z�b�g����
extern	int			NS_SetKeyInputString(			const TCHAR *String, int InputHandle ) ;																						// �L�[���̓f�[�^�Ɏw��̕�������Z�b�g����
extern	int			NS_SetKeyInputStringWithStrLen(	const TCHAR *String, size_t StringLength, int InputHandle ) ;																	// �L�[���̓n���h���Ɏw��̕�������Z�b�g����
extern	int			NS_SetKeyInputNumber(			int   Number,        int InputHandle ) ;																						// �L�[���̓f�[�^�Ɏw��̐��l�𕶎��ɒu�������ăZ�b�g����
extern	int			NS_SetKeyInputNumberToFloat(	float Number,        int InputHandle ) ;																						// �L�[���̓f�[�^�Ɏw��̕��������_�l�𕶎��ɒu�������ăZ�b�g����
extern	int			NS_GetKeyInputString(			TCHAR *StrBuffer,    int InputHandle ) ;																						// ���̓f�[�^�̕�������擾����
extern	int			NS_GetKeyInputNumber(			int InputHandle ) ;																												// ���̓f�[�^�̕�����𐮐��l�Ƃ��Ď擾����
extern	float		NS_GetKeyInputNumberToFloat(	int InputHandle ) ;																												// ���̓f�[�^�̕�����𕂓������_�l�Ƃ��Ď擾����
extern	int			NS_SetKeyInputCursorPosition(	int Position,        int InputHandle ) ;																						// �L�[���͂̌��݂̃J�[�\���ʒu��ݒ肷��
extern	int			NS_GetKeyInputCursorPosition(	int InputHandle ) ;																												// �L�[���͂̌��݂̃J�[�\���ʒu���擾����

#endif // DX_NON_KEYEX


















// DxFile.cpp�֐��v���g�^�C�v�錾

// �t�@�C���A�N�Z�X�֐�
extern	int			NS_FileRead_open(				const TCHAR *FilePath , int ASync = FALSE ) ;					// �t�@�C�����J��
extern	int			NS_FileRead_open_WithStrLen(			const TCHAR *FilePath, size_t FilePathLength, int ASync = FALSE ) ;	// �t�@�C�����J��
extern	int			NS_FileRead_open_mem(			const void *FileImage, size_t FileImageSize ) ;						// �������ɓW�J���ꂽ�t�@�C�����J��
extern	LONGLONG	NS_FileRead_size(				const TCHAR *FilePath ) ;										// �t�@�C���̃T�C�Y�𓾂�
extern	LONGLONG	NS_FileRead_size_WithStrLen(			const TCHAR *FilePath, size_t FilePathLength ) ;				// �t�@�C���̃T�C�Y���擾����
extern	LONGLONG	NS_FileRead_size_handle(				int FileHandle ) ;												// �t�@�C���̃T�C�Y���擾����( �t�@�C���n���h���g�p�� )
extern	int			NS_FileRead_close(				int FileHandle ) ;												// �t�@�C�������
extern	LONGLONG	NS_FileRead_tell(				int FileHandle ) ;												// �t�@�C���|�C���^�̌��݈ʒu�𓾂�
extern	int			NS_FileRead_seek(				int FileHandle , LONGLONG Offset , int Origin ) ;				// �t�@�C���|�C���^�̈ʒu��ύX����
extern	int			NS_FileRead_read(				void *Buffer , int ReadSize , int FileHandle ) ;				// �t�@�C������f�[�^��ǂݍ���
extern	int			NS_FileRead_idle_chk(			int FileHandle ) ;												// �t�@�C���ǂݍ��݂��������Ă��邩�ǂ������擾����
extern	int			NS_FileRead_eof(				int FileHandle ) ;												// �t�@�C���̏I�[���ǂ����𓾂�
extern	int			NS_FileRead_set_format(		int FileHandle, int CharCodeFormat /* DX_CHARCODEFORMAT_SHIFTJIS �� */ ) ;	// �t�@�C���̕����R�[�h�`����ݒ肷��( �e�L�X�g�t�@�C���p )
extern	int			NS_FileRead_gets(				TCHAR *Buffer , int BufferSize , int FileHandle ) ;				// �t�@�C�����當�����ǂݏo��
extern	TCHAR		NS_FileRead_getc(				int FileHandle ) ;												// �t�@�C������ꕶ���ǂݏo��
extern	int			NS_FileRead_scanf(				int FileHandle , const TCHAR *Format , ... ) ;					// �t�@�C�����珑�������ꂽ�f�[�^��ǂݏo��

extern	DWORD_PTR	NS_FileRead_createInfo(		const TCHAR *ObjectPath ) ;										// �t�@�C�����n���h�����쐬����( �߂�l  -1:�G���[  -1�ȊO:�t�@�C�����n���h�� )
extern	DWORD_PTR	NS_FileRead_createInfo_WithStrLen(		const TCHAR *ObjectPath, size_t ObjectPathLength ) ;			// �t�@�C�����n���h�����쐬����( �߂�l  -1:�G���[  -1�ȊO:�t�@�C�����n���h�� )
extern	int			NS_FileRead_getInfoNum(		DWORD_PTR FileInfoHandle ) ;									// �t�@�C�����n���h�����̃t�@�C���̐����擾����
extern	int			NS_FileRead_getInfo(			int Index , FILEINFO *Buffer , DWORD_PTR FileInfoHandle ) ;		// �t�@�C�����n���h�����̃t�@�C���̏����擾����
extern	int			NS_FileRead_deleteInfo(		DWORD_PTR FileInfoHandle ) ;									// �t�@�C�����n���h�����폜����

extern	DWORD_PTR	NS_FileRead_findFirst(			const TCHAR *FilePath, FILEINFO *Buffer ) ;						// �w��̃t�@�C�����̓t�H���_�̏����擾���A�t�@�C�������n���h�����쐬����( �߂�l: -1=�G���[  -1�ȊO=�t�@�C�������n���h�� )
extern	DWORD_PTR	NS_FileRead_findFirst_WithStrLen(		const TCHAR *FilePath, size_t FilePathLength, FILEINFO *Buffer ) ; // �w��̃t�@�C�����̓t�H���_�̏����擾���A�t�@�C�������n���h�����쐬����( �߂�l: -1=�G���[  -1�ȊO=�t�@�C�������n���h�� )
extern	int			NS_FileRead_findNext(			DWORD_PTR FindHandle, FILEINFO *Buffer ) ;						// �����̍��v���鎟�̃t�@�C���̏����擾����( �߂�l: -1=�G���[  0=���� )
extern	int			NS_FileRead_findClose(			DWORD_PTR FindHandle ) ;										// �t�@�C�������n���h�������( �߂�l: -1=�G���[  0=���� )

extern	int			NS_FileRead_fullyLoad(			const TCHAR *FilePath ) ;										// �w��̃t�@�C���̓��e��S�ă������ɓǂݍ��݁A���̏��̃A�N�Z�X�ɕK�v�ȃn���h����Ԃ�( �߂�l  -1:�G���[  -1�ȊO:�n���h�� )�A�g���I�������n���h���� FileRead_fullyLoad_delete �ō폜����K�v������܂�
extern	int			NS_FileRead_fullyLoad_WithStrLen(		const TCHAR *FilePath, size_t FilePathLength ) ;				// �w��̃t�@�C���̓��e��S�ă������ɓǂݍ��݁A���̏��̃A�N�Z�X�ɕK�v�ȃn���h����Ԃ�( �߂�l  -1:�G���[  -1�ȊO:�n���h�� )�A�g���I�������n���h���� FileRead_fullyLoad_delete �ō폜����K�v������܂�
extern	int			NS_FileRead_fullyLoad_delete(	int FLoadHandle ) ;										// FileRead_fullyLoad �œǂݍ��񂾃t�@�C��������������폜����
extern	const void*	NS_FileRead_fullyLoad_getImage( int FLoadHandle ) ;										// FileRead_fullyLoad �œǂݍ��񂾃t�@�C���̓��e���i�[�����������A�h���X���擾����
extern	LONGLONG	NS_FileRead_fullyLoad_getSize(	int FLoadHandle ) ;										// FileRead_fullyLoad �œǂݍ��񂾃t�@�C���̃T�C�Y���擾����

// �ݒ�֌W�֐�
extern	int			NS_GetStreamFunctionDefault(	void ) ;														// �c�w���C�u�����ŃX�g���[���f�[�^�A�N�Z�X�Ɏg�p����֐����f�t�H���g�̂��̂����ׂ�( TRUE:�f�t�H���g  FALSE:�f�t�H���g�ł͂Ȃ� )
extern	int			NS_ChangeStreamFunction(		const STREAMDATASHREDTYPE2 *StreamThread ) ;						// �c�w���C�u�����ŃX�g���[���f�[�^�A�N�Z�X�Ɏg�p����֐���ύX����
extern	int			NS_ChangeStreamFunctionW(		const STREAMDATASHREDTYPE2W *StreamThreadW ) ;					// �c�w���C�u�����ŃX�g���[���f�[�^�A�N�Z�X�Ɏg�p����֐���ύX����( wchar_t �g�p�� )

// �⏕�֌W�֐�
extern int			NS_ConvertFullPath( const TCHAR *Src, TCHAR *Dest, const TCHAR *CurrentDir = NULL ) ;			// �t���p�X�ł͂Ȃ��p�X��������t���p�X�ɕϊ�����( CurrentDir �̓t���p�X�ł���K�v������(����Ɂw\�x�������Ă������Ă��ǂ�) )( CurrentDir �� NULL �̏ꍇ�͌��݂̃J�����g�f�B���N�g�����g�p���� )
extern int			NS_ConvertFullPathWithStrLen(			const TCHAR *Src, size_t SrcLength, TCHAR *Dest, const TCHAR *CurrentDir = NULL, size_t CurrentDirLength = 0 ) ;	// �t���p�X�ł͂Ȃ��p�X��������t���p�X�ɕϊ�����( CurrentDir �̓t���p�X�ł���K�v������(����Ɂw\�x�������Ă������Ă��ǂ�) )( CurrentDir �� NULL �̏ꍇ�͌��݂̃J�����g�f�B���N�g�����g�p���� )












// DxNetwork.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_NETWORK
extern	int			NS_GetWinSockLastError( void ) ;				// WinSock �ōŌ�ɔ��������G���[�̃R�[�h���擾����
#endif // DX_NON_NETWORK















// DxInput.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_INPUT

// ���͏�Ԏ擾�֐�
extern	int			NS_CheckHitKey(							int KeyCode ) ;															// �L�[�{�[�h�̉�����Ԃ��擾����
extern	int			NS_CheckHitKeyAll(							int CheckType = DX_CHECKINPUT_ALL ) ;									// �ǂꂩ��ł��L�[��������Ă��邩�ǂ������擾( ������Ă�����߂�l�� 0 �ȊO�ɂȂ� )
extern	int			NS_GetHitKeyStateAll(						DX_CHAR *KeyStateBuf ) ;												// ���ׂẴL�[�̉�����Ԃ��擾����( KeyStateBuf:char�^256���̔z��̐擪�A�h���X )
extern	int			NS_GetHitKeyStateAllEx(					int *KeyStateArray ) ;													// ���ׂẴL�[�̉�����Ԃ��擾����( KeyStateBuf:int�^256���̔z��̐擪�A�h���X�A�z��̊e�v�f�̏�ԁ@0:������Ă��Ȃ��@1�F�����ꂽ�P��߁@2�ȏ�F�����ꑱ���Ă���񐔁@-1�F������ė����ꂽ�P��߁@-2�ȉ�:������ė�����Ă���̉� )
extern	int			NS_GetJoypadNum(							void ) ;																// �W���C�p�b�h���ڑ�����Ă��鐔���擾����
extern	int			NS_GetJoypadButtonNum(						int InputType ) ;														// �W���C�p�b�h�̃{�^���̐����擾����
extern	int			NS_GetJoypadInputState(					int InputType ) ;														// �W���C�p�b�h�̓��͏�Ԃ��擾����
extern	int			NS_GetJoypadAnalogInput(					int *XBuf, int *YBuf, int InputType ) ;									// �W���C�p�b�h�̃A�i���O�I�ȃX�e�B�b�N���͏��𓾂�
extern	int			NS_GetJoypadAnalogInputRight(				int *XBuf, int *YBuf, int InputType ) ;									// ( �g�p�񐄏� )�W���C�p�b�h�̃A�i���O�I�ȃX�e�B�b�N���͏��𓾂�(�E�X�e�B�b�N�p)
extern	int			NS_GetJoypadDirectInputState(				int InputType, DINPUT_JOYSTATE *DInputState ) ;							// DirectInput ���瓾����W���C�p�b�h�̐��̃f�[�^���擾����( DX_INPUT_KEY �� DX_INPUT_KEY_PAD1 �ȂǁA�L�[�{�[�h�����ރ^�C�v�� InputType �ɓn���ƃG���[�ƂȂ� -1 ��Ԃ� )
extern	int			NS_CheckJoypadXInput(						int InputType ) ;														// �w��̓��̓f�o�C�X�� XInput �ɑΉ����Ă��邩�ǂ������擾����( �߂�l  TRUE:XInput�Ή��̓��̓f�o�C�X  FALSE:XInput��Ή��̓��̓f�o�C�X   -1:�G���[ )( DX_INPUT_KEY �� DX_INPUT_KEY_PAD1 �ȂǁA�L�[�{�[�h�����ރ^�C�v�� InputType �ɓn���ƃG���[�ƂȂ� -1 ��Ԃ� )
extern	int			NS_GetJoypadXInputState(					int InputType, XINPUT_STATE *XInputState ) ;							// XInput ���瓾������̓f�o�C�X( Xbox360�R���g���[���� )�̐��̃f�[�^���擾����( XInput��Ή��̃p�b�h�̏ꍇ�̓G���[�ƂȂ� -1 ��Ԃ��ADX_INPUT_KEY �� DX_INPUT_KEY_PAD1 �ȂǁA�L�[�{�[�h�����ރ^�C�v�� InputType �ɓn���ƃG���[�ƂȂ� -1 ��Ԃ� )
extern	int			NS_SetJoypadInputToKeyInput(				int InputType, int PadInput, int KeyInput1, int KeyInput2 = -1 , int KeyInput3 = -1 , int KeyInput4 = -1  ) ; // �W���C�p�b�h�̓��͂ɑΉ������L�[�{�[�h�̓��͂�ݒ肷��( InputType:�ݒ��ύX����p�b�h�̎��ʎq( DX_INPUT_PAD1�� )�@�@PadInput:�ݒ��ύX����p�b�h�{�^���̎��ʎq( PAD_INPUT_1 �� )�@�@KeyInput1:PadInput �������������Ƃɂ���L�[�R�[�h( KEY_INPUT_A �Ȃ� )���̂P�@�@KeyInput2:���̂Q�A-1�Őݒ�Ȃ��@�@KeyInput3:���̂R�A-1�Őݒ�Ȃ��@�@KeyInput4:���̂S�A-1�Őݒ�Ȃ� )
extern	int			NS_SetJoypadDeadZone(						int InputType, double Zone ) ;											// �W���C�p�b�h�̖����]�[���̐ݒ���s��( InputType:�ݒ��ύX����p�b�h�̎��ʎq( DX_INPUT_PAD1�� )   Zone:�V���������]�[��( 0.0 �` 1.0 )�A�f�t�H���g�l�� 0.35 )
extern	double		NS_GetJoypadDeadZone(						int InputType ) ;														// �W���C�p�b�h�̖����]�[���̐ݒ���擾����( InputType:�ݒ��ύX����p�b�h�̎��ʎq( DX_INPUT_PAD1�� )  �߂�l:�����]�[��( 0.0 �` 1.0 )
extern	int			NS_SetJoypadDefaultDeadZoneAll(			double Zone ) ;															// �W���C�p�b�h�̃f�t�H���g�̖����]�[����ݒ肷��( Zone:�V���������]�[��( 0.0 �` 1.0 )�A�f�t�H���g�l�� 0.35 )
extern	double		NS_GetJoypadDefaultDeadZoneAll(			void ) ;																// �W���C�p�b�h�̃f�t�H���g�̖����]�[�����擾����( �߂�l:�����]�[��( 0.0 �` 1.0 ) )
extern	int			NS_StartJoypadVibration(					int InputType, int Power, int Time, int EffectIndex = -1 ) ;			// �W���C�p�b�h�̐U�����J�n����
extern	int			NS_StopJoypadVibration(					int InputType, int EffectIndex = -1 ) ;									// �W���C�p�b�h�̐U�����~����
extern	int			NS_GetJoypadPOVState(						int InputType, int POVNumber ) ;										// �W���C�p�b�h�̂o�n�u���͂̏�Ԃ𓾂�( �߂�l�@�w���POV�f�[�^�̊p�x�A�P�ʂ͊p�x�̂P�O�O�{( 90�x�Ȃ� 9000 ) ���S�ʒu�ɂ���ꍇ�� -1 ���Ԃ� )
extern	int			NS_ReSetupJoypad(							void ) ;																// �W���C�p�b�h�̍ăZ�b�g�A�b�v���s��( �V���ɐڑ����ꂽ�W���C�p�b�h���������猟�o����� )
extern	int			NS_ReSetupInputSystem(						void ) ;																// ���̓V�X�e���̍ăZ�b�g�A�b�v���s��

extern	int			NS_SetUseJoypadVibrationFlag(				int Flag ) ;															// �W���C�p�b�h�̐U���@�\���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����@�@FALSE:�g�p���Ȃ� )

#ifdef WINDOWS_DESKTOP_OS
extern	int			NS_SetKeyExclusiveCooperativeLevelFlag(	int Flag ) ;															// DirectInput �̃L�[�{�[�h�̋������x����r�����x���ɂ��邩�ǂ�����ݒ肷��( TRUE:�r�����x���ɂ���  FALSE:�W�����x���ɂ���( �f�t�H���g ) )�ADxLib_Init �̌Ăяo���O�ł̂ݎ��s�\�@
extern	int			NS_SetKeyboardNotDirectInputFlag(			int Flag ) ;															// �L�[�{�[�h�̓��͏����� DirectInput ���g��Ȃ����ǂ�����ݒ肷��( TRUE:DirectInput ���g�킸�AWindows�W���@�\���g�p����@�@FALSE:DirectInput ���g�p���� )
extern	int			NS_SetUseDirectInputFlag(					int Flag ) ;															// ���͏����� DirectInput ���g�p���邩�ǂ�����ݒ肷��( TRUE:DirectInput ���g�p����@�@FALSE:DirectInput ���g�킸�AWindows�W���@�\���g�p���� )
extern	int			NS_SetDirectInputMouseMode(				int Mode ) ;															// �}�E�X�̓��͏����� DirectInput ���g�p����ꍇ�̓��샂�[�h��ݒ肷��( 0:�E�B���h�E���A�N�e�B�u�ȏꍇ�̂� DirectInput ���g�p����  1:�E�B���h�E�̃A�N�e�B�u��ԂɊ֌W�Ȃ� DirectInput ���g�p���� )
extern	int			NS_SetUseXInputFlag(						int Flag ) ;															// Xbox360�R���g���[���̓��͏����� XInput ���g�p���邩�ǂ�����ݒ肷��( TRUE:XInput ���g�p����( �f�t�H���g )�@�@FALSE:XInput ���g�p���Ȃ� )
extern	int			NS_SetUseXboxControllerDirectInputFlag(	int Flag ) ;															// Xbox360�R���g���[���� Xbox One�R���g���[���� DirectInput�R���g���[���Ƃ��Ă����o���邩�ǂ�����ݒ肷��( TRUE:DirectInput�R���g���[���Ƃ��Ă����o����  FALSE:DirectInput�R���g���[���Ƃ��Ă͌��o���Ȃ�(�f�t�H���g) )
extern	int			NS_GetJoypadGUID(							int PadIndex, GUID *GuidInstanceBuffer, GUID *GuidProductBuffer ) ;		// �W���C�p�b�h�̂f�tI�c�𓾂�
extern	int			NS_GetJoypadName(							int InputType, TCHAR *InstanceNameBuffer, TCHAR *ProductNameBuffer ) ;	// �W���C�p�b�h�̃f�o�C�X�o�^���Ɛ��i�o�^�����擾����
extern	int			NS_GetJoypadType(							int PadIndex ) ;														// �W���C�p�b�h�̃^�C�v���擾����( �߂�l�F�W���C�p�b�h�^�C�v( DX_PADTYPE_XBOX_360 �Ȃ� ) )
extern	int			NS_ConvertKeyCodeToVirtualKey(				int KeyCode ) ;															// �c�w���C�u�����̃L�[�R�[�h( KEY_INPUT_A �Ȃ� )�ɑΉ����� Windows �̉��z�L�[�R�[�h( VK_LEFT �Ȃ� ) ���擾����( KeyCode:�ϊ��������c�w���C�u�����̃L�[�R�[�h�@�߂�l�FWindows�̉��z�L�[�R�[�h )
extern	int			NS_ConvertVirtualKeyToKeyCode(				int VirtualKey ) ;														//  Windows �̉��z�L�[�R�[�h( VK_LEFT �Ȃ� ) �ɑΉ�����c�w���C�u�����̃L�[�R�[�h( KEY_INPUT_A �Ȃ� )���擾����( VirtualKey:�ϊ�������Windows�̉��z�L�[�R�[�h�@�߂�l�F�c�w���C�u�����̃L�[�R�[�h )
#endif // WINDOWS_DESKTOP_OS

#endif // DX_NON_INPUT












#ifndef DX_NOTUSE_DRAWFUNCTION

// �摜�����n�֐��v���g�^�C�v�錾

// �O���t�B�b�N�n���h���쐬�֌W�֐�
extern	int			NS_MakeGraph(						int SizeX, int SizeY, int NotUse3DFlag = FALSE ) ;							// �O���t�B�b�N�n���h�����쐬����
extern	int			NS_MakeScreen(						int SizeX, int SizeY, int UseAlphaChannel = FALSE ) ;						// SetDrawScreen �ŕ`��Ώۂɂł���O���t�B�b�N�n���h�����쐬����
extern	int			NS_DerivationGraph(				int SrcX, int SrcY, int Width, int Height, int SrcGraphHandle ) ;			// �w��̃O���t�B�b�N�̎w�蕔�������𔲂��o���ĐV���ȃO���t�B�b�N�n���h�����쐬����
extern	int			NS_DerivationGraphF(				float SrcX, float SrcY, float Width, float Height, int SrcGraphHandle ) ;	// �w��̃O���t�B�b�N�n���h���̎w�蕔�������𔲂��o���ĐV���ȃO���t�B�b�N�n���h�����쐬����( float�� )
extern	int			NS_DeleteGraph(					int GrHandle ) ;														// �w��̃O���t�B�b�N�n���h�����폜����
extern	int			NS_DeleteSharingGraph(				int GrHandle ) ;															// �w��̃O���t�B�b�N�n���h���ƁA�����O���t�B�b�N�n���h������h�����Ă���O���t�B�b�N�n���h��( DerivationGraph �Ŕh�������n���h���ALoadDivGraph �ǂݍ���ō쐬���ꂽ�����̃n���h�� )����x�ɍ폜����
extern	int			NS_GetGraphNum(					void ) ;																	// �L���ȃO���t�B�b�N�n���h���̐����擾����
extern	int			NS_FillGraph(						int GrHandle, int Red, int Green, int Blue, int Alpha = 255 ) ;				// �O���t�B�b�N�n���h�������̐F�œh��Ԃ�
extern	int			NS_FillRectGraph(						int GrHandle, int x, int y, int Width, int Height, int Red, int Green, int Blue, int Alpha = 255 ) ;	// �O���t�B�b�N�n���h���̎w��͈̔͂��w��̐F�œh��Ԃ�
extern	int			NS_SetGraphLostFlag(				int GrHandle, int *LostFlag ) ;												// �O���t�B�b�N�n���h���폜���ɗ��Ă�t���O�̃A�h���X���Z�b�g����
extern	int			NS_InitGraph(						void ) ;																	// ���ׂẴO���t�B�b�N�n���h�����폜����
extern	int			NS_ReloadFileGraphAll(				void ) ;																	// �t�@�C������ǂݍ��񂾉摜���O���t�B�b�N�n���h���ɍēx�ǂݍ���

// �V���h�E�}�b�v�n���h���֌W�֐�
extern	int			NS_MakeShadowMap(					int SizeX, int SizeY ) ;													// �V���h�E�}�b�v���쐬����
extern	int			NS_DeleteShadowMap(				int SmHandle ) ;															// �V���h�E�}�b�v�n���h�����폜����
extern	int			NS_SetShadowMapLightDirection(		int SmHandle, VECTOR Direction ) ;											// �V���h�E�}�b�v���z�肷�郉�C�g�̕�����ݒ肷��
extern	int			NS_ShadowMap_DrawSetup(			int SmHandle ) ;										// �V���h�E�}�b�v�ւ̕`��̏������s��
extern	int			NS_ShadowMap_DrawEnd(				void ) ;															// �V���h�E�}�b�v�ւ̕`����I������
extern	int			NS_SetUseShadowMap(				int SlotIndex, int SmHandle ) ;												// �`��Ŏg�p����V���h�E�}�b�v���w�肷��A�L���ȃX���b�g�͂O�`�Q�ASmHandle �� -1 ��n���Ǝw��̃X���b�g�̃V���h�E�}�b�v������
extern	int			NS_SetShadowMapDrawArea(			int SmHandle, VECTOR MinPosition, VECTOR MaxPosition ) ;					// �V���h�E�}�b�v�ɕ`�悷��ۂ͈̔͂�ݒ肷��( ���̊֐��ŕ`��͈͂�ݒ肵�Ȃ��ꍇ�͎�������g�債���͈͂��`��͈͂ƂȂ� )
extern	int			NS_ResetShadowMapDrawArea(			int SmHandle ) ;															// SetShadowMapDrawArea �̐ݒ����������
extern	int			NS_SetShadowMapAdjustDepth(		int SmHandle, float Depth ) ;												// �V���h�E�}�b�v���g�p�����`�掞�̕␳�[�x��ݒ肷��
extern	int			NS_GetShadowMapViewProjectionMatrix( int SmHandle, MATRIX *MatrixBuffer ) ;									// �V���h�E�}�b�v�쐬����K�p���Ɏg�p����r���[�s��Ǝˉe�s�����Z�����s����擾����
extern	int			NS_SetShadowMapBlurParam(			int SmHandle, int Param ) ;													// �V���h�E�}�b�v�ɓK�p����ڂ����x������ݒ肷��
extern	int			NS_SetShadowMapGradationParam(		int SmHandle, float Param ) ;												// �V���h�E�}�b�v�ɓK�p����e���O���f�[�V����������͈͂�ݒ肷��
extern	int			NS_TestDrawShadowMap(				int SmHandle, int x1, int y1, int x2, int y2 ) ;							// �V���h�E�}�b�v����ʂɃe�X�g�`�悷��

// �O���t�B�b�N�n���h���ւ̉摜�]���֐�
extern	int			NS_BltBmpToGraph(					const COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int CopyPointX, int CopyPointY,                                                                                                   int GrHandle ) ;						// �a�l�o�̓��e���O���t�B�b�N�n���h���ɓ]��
extern	int			NS_BltBmpToDivGraph(				const COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int AllNum, int XNum, int YNum, int Width, int Height,                                                                      const int *GrHandle, int ReverseFlag ) ;	// �a�l�o�̓��e�𕪊��쐬�����O���t�B�b�N�n���h�������ɓ]��
extern	int			NS_BltBmpOrGraphImageToGraph(		const COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int BmpFlag, const BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int CopyPointX, int CopyPointY,                              int GrHandle ) ;						// �a�l�o �� BASEIMAGE ���O���t�B�b�N�n���h���ɓ]��
extern	int			NS_BltBmpOrGraphImageToGraph2(		const COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int BmpFlag, const BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, const RECT *SrcRect, int DestX, int DestY,                   int GrHandle ) ;						// �a�l�o �� BASEIMAGE �̎w��̗̈���O���t�B�b�N�n���h���ɓ]��
extern	int			NS_BltBmpOrGraphImageToDivGraph(	const COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int BmpFlag, const BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int AllNum, int XNum, int YNum, int Width, int Height, const int *GrHandle, int ReverseFlag ) ;	// �a�l�o �� BASEIMAGE �𕪊��쐬�����O���t�B�b�N�n���h�������ɓ]��
extern	int			NS_BltBmpOrGraphImageToDivGraphF(	const COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int BmpFlag, const BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int AllNum, int XNum, int YNum, float Width, float Height, const int *GrHandle, int ReverseFlag ) ;	// �a�l�o �� BASEIMAGE �𕪊��쐬�����O���t�B�b�N�n���h�������ɓ]��( float�^ )

// �摜����O���t�B�b�N�n���h�����쐬����֐�
extern	int			NS_LoadBmpToGraph(					const TCHAR *FileName, int TextureFlag, int ReverseFlag, int SurfaceMode = DX_MOVIESURFACE_NORMAL ) ;								// �摜�t�@�C������O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadBmpToGraphWithStrLen(			const TCHAR *FileName, size_t FileNameLength, int TextureFlag, int ReverseFlag, int SurfaceMode = DX_MOVIESURFACE_NORMAL ) ;										// �摜�t�@�C������O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadGraph(							const TCHAR *FileName,                        int NotUse3DFlag = FALSE ) ;																							// �摜�t�@�C������O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadGraphWithStrLen(				const TCHAR *FileName, size_t FileNameLength, int NotUse3DFlag = FALSE ) ;																							// �摜�t�@�C������O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadReverseGraph(					const TCHAR *FileName,                        int NotUse3DFlag = FALSE ) ;																							// �摜�t�@�C���𔽓]�������̂ŃO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadReverseGraphWithStrLen(			const TCHAR *FileName, size_t FileNameLength, int NotUse3DFlag = FALSE ) ;																							// �摜�t�@�C���𔽓]�������̂ŃO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraph(						const TCHAR *FileName,                        int AllNum, int XNum, int YNum, int   XSize, int   YSize, int *HandleArray, int NotUse3DFlag DEFAULTPARAM( = FALSE ) , int   XStride DEFAULTPARAM( = 0 ) , int   YStride DEFAULTPARAM( = 0 ) ) ;	// �摜�t�@�C���𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphWithStrLen(				const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, int   XSize, int   YSize, int *HandleArray, int NotUse3DFlag DEFAULTPARAM( = FALSE ) , int   XStride DEFAULTPARAM( = 0 ) , int   YStride DEFAULTPARAM( = 0 ) ) ;	// �摜�t�@�C���𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphF(						const TCHAR *FileName,                        int AllNum, int XNum, int YNum, float XSize, float YSize, int *HandleArray, int NotUse3DFlag DEFAULTPARAM( = FALSE ) , float XStride DEFAULTPARAM( = 0 ) , float YStride DEFAULTPARAM( = 0 ) ) ;	// �摜�t�@�C���𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphFWithStrLen(			const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, float XSize, float YSize, int *HandleArray, int NotUse3DFlag DEFAULTPARAM( = FALSE ) , float XStride DEFAULTPARAM( = 0 ) , float YStride DEFAULTPARAM( = 0 ) ) ;	// �摜�t�@�C���𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivBmpToGraph(					const TCHAR *FileName,                        int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, int *HandleArray, int TextureFlag, int ReverseFlag , int   XStride DEFAULTPARAM( = 0 ) , int   YStride DEFAULTPARAM( = 0 ) ) ;			// �摜�t�@�C���𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivBmpToGraphWithStrLen(		const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, int *HandleArray, int TextureFlag, int ReverseFlag , int   XStride DEFAULTPARAM( = 0 ) , int   YStride DEFAULTPARAM( = 0 ) ) ;			// �摜�t�@�C���𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivBmpToGraphF(					const TCHAR *FileName,                        int AllNum, int XNum, int YNum, float SizeX, float SizeY, int *HandleArray, int TextureFlag, int ReverseFlag , float XStride DEFAULTPARAM( = 0 ) , float YStride DEFAULTPARAM( = 0 ) ) ;			// �摜�t�@�C���𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivBmpToGraphFWithStrLen(		const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, float SizeX, float SizeY, int *HandleArray, int TextureFlag, int ReverseFlag , float XStride DEFAULTPARAM( = 0 ) , float YStride DEFAULTPARAM( = 0 ) ) ;			// �摜�t�@�C���𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadReverseDivGraph(				const TCHAR *FileName,                        int AllNum, int XNum, int YNum, int   XSize, int   YSize, int *HandleArray, int NotUse3DFlag DEFAULTPARAM( = FALSE ) , int   XStride DEFAULTPARAM( = 0 ) , int   YStride DEFAULTPARAM( = 0 ) ) ;	// �摜�t�@�C���𔽓]�������̂𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadReverseDivGraphWithStrLen(		const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, int   XSize, int   YSize, int *HandleArray, int NotUse3DFlag DEFAULTPARAM( = FALSE ) , int   XStride DEFAULTPARAM( = 0 ) , int   YStride DEFAULTPARAM( = 0 ) ) ;	// �摜�t�@�C���𔽓]�������̂𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadReverseDivGraphF(				const TCHAR *FileName,                        int AllNum, int XNum, int YNum, float XSize, float YSize, int *HandleArray, int NotUse3DFlag DEFAULTPARAM( = FALSE ) , float XStride DEFAULTPARAM( = 0 ) , float YStride DEFAULTPARAM( = 0 ) ) ;	// �摜�t�@�C���𔽓]�������̂𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadReverseDivGraphFWithStrLen(		const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, float XSize, float YSize, int *HandleArray, int NotUse3DFlag DEFAULTPARAM( = FALSE ) , float XStride DEFAULTPARAM( = 0 ) , float YStride DEFAULTPARAM( = 0 ) ) ;	// �摜�t�@�C���𔽓]�������̂𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadBlendGraph(						const TCHAR *FileName ) ;																																			// �摜�t�@�C������u�����h�p�O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadBlendGraphWithStrLen(			const TCHAR *FileName, size_t FileNameLength ) ;																													// �摜�t�@�C������u�����h�p�O���t�B�b�N�n���h�����쐬����
#ifdef WINDOWS_DESKTOP_OS
extern	int			NS_LoadGraphToResource(			int ResourceID ) ;																													// �摜���\�[�X����O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphToResource(			int ResourceID, int AllNum, int XNum, int YNum, int   XSize, int   YSize, int *HandleArray ) ;										// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphFToResource(		int ResourceID, int AllNum, int XNum, int YNum, float XSize, float YSize, int *HandleArray ) ;										// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����( float�^ )
#ifndef DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_LoadGraphToResource(			const TCHAR *ResourceName, const TCHAR *ResourceType ) ;																			// �摜���\�[�X����O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadGraphToResourceWithStrLen(		const TCHAR *ResourceName, size_t ResourceNameLength, const TCHAR *ResourceType, size_t ResourceTypeLength ) ;																				// �摜���\�[�X����O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphToResource(				const TCHAR *ResourceName,                            const TCHAR *ResourceType,                            int AllNum, int XNum, int YNum, int   XSize, int   YSize, int *HandleArray ) ;	// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphToResourceWithStrLen(	const TCHAR *ResourceName, size_t ResourceNameLength, const TCHAR *ResourceType, size_t ResourceTypeLength, int AllNum, int XNum, int YNum, int   XSize, int   YSize, int *HandleArray ) ;	// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphFToResource(			const TCHAR *ResourceName,                            const TCHAR *ResourceType,                            int AllNum, int XNum, int YNum, float XSize, float YSize, int *HandleArray ) ;	// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����( float�^ )
extern	int			NS_LoadDivGraphFToResourceWithStrLen(	const TCHAR *ResourceName, size_t ResourceNameLength, const TCHAR *ResourceType, size_t ResourceTypeLength, int AllNum, int XNum, int YNum, float XSize, float YSize, int *HandleArray ) ;	// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����( float�^ )
#endif // DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_LoadGraphToResource2(				const TCHAR *ResourceName,                            const TCHAR *ResourceType                            ) ;																				// �摜���\�[�X����O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadGraphToResourceWithStrLen2(		const TCHAR *ResourceName, size_t ResourceNameLength, const TCHAR *ResourceType, size_t ResourceTypeLength ) ;																				// �摜���\�[�X����O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphToResource2(			const TCHAR *ResourceName,                            const TCHAR *ResourceType,                            int AllNum, int XNum, int YNum, int   XSize, int   YSize, int *HandleArray ) ;	// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphToResourceWithStrLen2(	const TCHAR *ResourceName, size_t ResourceNameLength, const TCHAR *ResourceType, size_t ResourceTypeLength, int AllNum, int XNum, int YNum, int   XSize, int   YSize, int *HandleArray ) ;	// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphFToResource2(			const TCHAR *ResourceName,                            const TCHAR *ResourceType,                            int AllNum, int XNum, int YNum, float XSize, float YSize, int *HandleArray ) ;	// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����( float�^ )
extern	int			NS_LoadDivGraphFToResourceWithStrLen2(	const TCHAR *ResourceName, size_t ResourceNameLength, const TCHAR *ResourceType, size_t ResourceTypeLength, int AllNum, int XNum, int YNum, float XSize, float YSize, int *HandleArray ) ;	// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����( float�^ )
#ifndef DX_NON_DIRECT3D11
extern	int			NS_CreateGraphFromID3D11Texture2D( const void *pID3D11Texture2D ) ;									// ID3D11Texture2D ����O���t�B�b�N�n���h�����쐬����
#endif // DX_NON_DIRECT3D11
#endif // WINDOWS_DESKTOP_OS

extern	int			NS_CreateGraphFromMem(             const void *RGBFileImage, int RGBFileImageSize,               const void *AlphaFileImage = NULL , int AlphaFileImageSize = 0 ,                  int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// ��������̃O���t�B�b�N�C���[�W����O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraphFromMem(           const void *RGBFileImage, int RGBFileImageSize, int GrHandle, const void *AlphaFileImage = NULL , int AlphaFileImageSize = 0 ,                  int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// ��������̃O���t�B�b�N�C���[�W��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateDivGraphFromMem(          const void *RGBFileImage, int RGBFileImageSize, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY,       int *HandleArray,                 int TextureFlag = TRUE , int ReverseFlag = FALSE , const void *AlphaFileImage = NULL , int AlphaFileImageSize = 0 ) ;			// ��������̉摜�C���[�W���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraphFFromMem(         const void *RGBFileImage, int RGBFileImageSize, int AllNum, int XNum, int YNum, float SizeX, float SizeY,       int *HandleArray,                 int TextureFlag = TRUE , int ReverseFlag = FALSE , const void *AlphaFileImage = NULL , int AlphaFileImageSize = 0 ) ;			// ��������̉摜�C���[�W���番���O���t�B�b�N�n���h�����쐬����( float�� )
extern	int			NS_ReCreateDivGraphFromMem(        const void *RGBFileImage, int RGBFileImageSize, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, const int *HandleArray,                 int TextureFlag = TRUE , int ReverseFlag = FALSE , const void *AlphaFileImage = NULL , int AlphaFileImageSize = 0 ) ;			// ��������̉摜�C���[�W��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_ReCreateDivGraphFFromMem(       const void *RGBFileImage, int RGBFileImageSize, int AllNum, int XNum, int YNum, float SizeX, float SizeY, const int *HandleArray,                 int TextureFlag = TRUE , int ReverseFlag = FALSE , const void *AlphaFileImage = NULL , int AlphaFileImageSize = 0 ) ;			// ��������̉摜�C���[�W��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������( float�� )
extern	int			NS_CreateGraphFromBmp(             const BITMAPINFO *RGBBmpInfo, const void *RGBBmpImage,               const BITMAPINFO *AlphaBmpInfo = NULL , const void *AlphaBmpImage = NULL , int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																			// �r�b�g�}�b�v�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraphFromBmp(           const BITMAPINFO *RGBBmpInfo, const void *RGBBmpImage, int GrHandle, const BITMAPINFO *AlphaBmpInfo = NULL , const void *AlphaBmpImage = NULL , int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																			// �r�b�g�}�b�v�f�[�^��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateDivGraphFromBmp(          const BITMAPINFO *RGBBmpInfo, const void *RGBBmpImage, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY,       int *HandleArray,          int TextureFlag = TRUE , int ReverseFlag = FALSE , const BITMAPINFO *AlphaBmpInfo = NULL , const void *AlphaBmpImage = NULL ) ;	// �r�b�g�}�b�v�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraphFFromBmp(         const BITMAPINFO *RGBBmpInfo, const void *RGBBmpImage, int AllNum, int XNum, int YNum, float SizeX, float SizeY,       int *HandleArray,          int TextureFlag = TRUE , int ReverseFlag = FALSE , const BITMAPINFO *AlphaBmpInfo = NULL , const void *AlphaBmpImage = NULL ) ;	// �r�b�g�}�b�v�f�[�^���番���O���t�B�b�N�n���h�����쐬����( float�� )
extern	int			NS_ReCreateDivGraphFromBmp(        const BITMAPINFO *RGBBmpInfo, const void *RGBBmpImage, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, const int *HandleArray,          int TextureFlag = TRUE , int ReverseFlag = FALSE , const BITMAPINFO *AlphaBmpInfo = NULL , const void *AlphaBmpImage = NULL ) ;	// �r�b�g�}�b�v�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_ReCreateDivGraphFFromBmp(       const BITMAPINFO *RGBBmpInfo, const void *RGBBmpImage, int AllNum, int XNum, int YNum, float SizeX, float SizeY, const int *HandleArray,          int TextureFlag = TRUE , int ReverseFlag = FALSE , const BITMAPINFO *AlphaBmpInfo = NULL , const void *AlphaBmpImage = NULL ) ;	// �r�b�g�}�b�v�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������( float�� )
extern	int			NS_CreateDXGraph(					const BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage,                                                                                 int TextureFlag ) ;																									// ��{�C���[�W�f�[�^����T�C�Y������o���A����ɍ������O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateGraphFromGraphImage(			const BASEIMAGE *RgbBaseImage,                                                                                                                  int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraphFromGraphImage(		const BASEIMAGE *RgbBaseImage,                                  int GrHandle,                                                                   int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateDivGraphFromGraphImage(		      BASEIMAGE *RgbBaseImage,                                  int AllNum, int XNum, int YNum, int   SizeX, int   SizeY,       int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraphFFromGraphImage(		      BASEIMAGE *RgbBaseImage,                                  int AllNum, int XNum, int YNum, float SizeX, float SizeY,       int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^���番���O���t�B�b�N�n���h�����쐬����( float�� )
extern	int			NS_ReCreateDivGraphFromGraphImage(		      BASEIMAGE *RgbBaseImage,                                  int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, const int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_ReCreateDivGraphFFromGraphImage(	      BASEIMAGE *RgbBaseImage,                                  int AllNum, int XNum, int YNum, float SizeX, float SizeY, const int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������( float�� )
#ifndef DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_CreateGraphFromGraphImage(			const BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage,                                                                                 int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraphFromGraphImage(		const BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int GrHandle,                                                                   int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateDivGraphFromGraphImage(		      BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY,       int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraphFFromGraphImage(		      BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int AllNum, int XNum, int YNum, float SizeX, float SizeY,       int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^���番���O���t�B�b�N�n���h�����쐬����( float�� )
extern	int			NS_ReCreateDivGraphFromGraphImage(		      BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, const int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_ReCreateDivGraphFFromGraphImage(	      BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int AllNum, int XNum, int YNum, float SizeX, float SizeY, const int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������( float�� )
#endif // DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_CreateGraphFromGraphImage2(			const BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage,                                                                                 int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraphFromGraphImage2(		const BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int GrHandle,                                                                   int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateDivGraphFromGraphImage2(		      BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY,       int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraphFFromGraphImage2(		      BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int AllNum, int XNum, int YNum, float SizeX, float SizeY,       int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^���番���O���t�B�b�N�n���h�����쐬����( float�� )
extern	int			NS_ReCreateDivGraphFromGraphImage2(	      BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, const int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_ReCreateDivGraphFFromGraphImage2(	      BASEIMAGE *RgbBaseImage, const BASEIMAGE *AlphaBaseImage, int AllNum, int XNum, int YNum, float SizeX, float SizeY, const int *HandleArray, int TextureFlag DEFAULTPARAM( = TRUE ) , int ReverseFlag DEFAULTPARAM( = FALSE ) ) ;																// ��{�C���[�W�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������( float�� )
extern	int			NS_CreateGraph(                    int Width, int Height, int Pitch, const void *RGBImage, const void *AlphaImage = NULL , int GrHandle = -1 ) ;																																			// ��������̃r�b�g�}�b�v�C���[�W����O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraph(                 int Width, int Height, int Pitch, const void *RGBImage, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, int *HandleArray, const void *AlphaImage = NULL ) ;																						// ��������̃r�b�g�}�b�v�C���[�W���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraphF(                int Width, int Height, int Pitch, const void *RGBImage, int AllNum, int XNum, int YNum, float SizeX, float SizeY, int *HandleArray, const void *AlphaImage = NULL ) ;																						// ��������̃r�b�g�}�b�v�C���[�W���番���O���t�B�b�N�n���h�����쐬����( float�� )
extern	int			NS_ReCreateGraph(                  int Width, int Height, int Pitch, const void *RGBImage, int GrHandle, const void *AlphaImage = NULL ) ;																																					// ��������̃r�b�g�}�b�v�C���[�W����O���t�B�b�N�n���h�����č쐬����
#ifndef DX_NON_SOFTIMAGE
extern	int			NS_CreateBlendGraphFromSoftImage(  int SIHandle ) ;																													// �\�t�g�E�G�A�ň����C���[�W����u�����h�p�摜�O���t�B�b�N�n���h�����쐬����( -1:�G���[  -1�ȊO:�u�����h�p�O���t�B�b�N�n���h�� )
extern	int			NS_CreateGraphFromSoftImage(       int SIHandle ) ;																													// �\�t�g�E�G�A�ň����C���[�W����O���t�B�b�N�n���h�����쐬����( -1:�G���[  -1�ȊO:�O���t�B�b�N�n���h�� )
extern	int			NS_CreateGraphFromRectSoftImage(   int SIHandle, int x, int y, int SizeX, int SizeY ) ;																				// �\�t�g�E�G�A�ň����C���[�W�̎w��̗̈���g���ăO���t�B�b�N�n���h�����쐬����( -1:�G���[  -1�ȊO:�O���t�B�b�N�n���h�� )
extern	int			NS_ReCreateGraphFromSoftImage(     int SIHandle, int GrHandle ) ;																										// �\�t�g�E�G�A�ň����C���[�W��������̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]������
extern	int			NS_ReCreateGraphFromRectSoftImage( int SIHandle, int x, int y, int SizeX, int SizeY, int GrHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W��������̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]������
extern	int			NS_CreateDivGraphFromSoftImage(    int SIHandle, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, int *HandleArray ) ;											// �\�t�g�E�G�A�ň����C���[�W���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraphFFromSoftImage(   int SIHandle, int AllNum, int XNum, int YNum, float SizeX, float SizeY, int *HandleArray ) ;											// �\�t�g�E�G�A�ň����C���[�W���番���O���t�B�b�N�n���h�����쐬����( float�� )
extern	int			NS_ReCreateDivGraphFromSoftImage(  int SIHandle, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, const int *HandleArray ) ;										// �\�t�g�E�G�A�ň����C���[�W��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_ReCreateDivGraphFFromSoftImage( int SIHandle, int AllNum, int XNum, int YNum, float SizeX, float SizeY, const int *HandleArray ) ;										// �\�t�g�E�G�A�ň����C���[�W��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������( float�� )
#endif // DX_NON_SOFTIMAGE
extern	int			NS_CreateGraphFromBaseImage(       const BASEIMAGE *BaseImage ) ;																										// ��{�C���[�W�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateGraphFromRectBaseImage(   const BASEIMAGE *BaseImage, int x, int y, int SizeX, int SizeY ) ;																	// ��{�C���[�W�f�[�^�̎w��̗̈���g���ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraphFromBaseImage(     const BASEIMAGE *BaseImage,                                     int GrHandle ) ;													// ��{�C���[�W�f�[�^��������̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]������
extern	int			NS_ReCreateGraphFromRectBaseImage( const BASEIMAGE *BaseImage, int x, int y, int SizeX, int SizeY, int GrHandle ) ;													// ��{�C���[�W�f�[�^�̎w��̗̈���g���Ċ����̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]������
extern	int			NS_CreateDivGraphFromBaseImage(          BASEIMAGE *BaseImage, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, int *HandleArray ) ;							// ��{�C���[�W�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraphFFromBaseImage(         BASEIMAGE *BaseImage, int AllNum, int XNum, int YNum, float SizeX, float SizeY, int *HandleArray ) ;							// ��{�C���[�W�f�[�^���番���O���t�B�b�N�n���h�����쐬����( float�� )
extern	int			NS_ReCreateDivGraphFromBaseImage(		      BASEIMAGE *BaseImage, int AllNum, int XNum, int YNum, int   SizeX, int   SizeY, const int *HandleArray ) ;						// ��{�C���[�W�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_ReCreateDivGraphFFromBaseImage(	          BASEIMAGE *BaseImage, int AllNum, int XNum, int YNum, float SizeX, float SizeY, const int *HandleArray ) ;						// ��{�C���[�W�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������( float�� )
extern	int			NS_ReloadGraph(					const TCHAR *FileName, int GrHandle, int ReverseFlag = FALSE ) ;																	// �摜�t�@�C������O���t�B�b�N�n���h���։摜�f�[�^��]������
extern	int			NS_ReloadGraphWithStrLen(				const TCHAR *FileName, size_t FileNameLength, int GrHandle, int ReverseFlag = FALSE ) ;																		// �摜�t�@�C������O���t�B�b�N�n���h���։摜�f�[�^��]������
extern	int			NS_ReloadDivGraph(						const TCHAR *FileName,                        int AllNum, int XNum, int YNum, int   XSize, int   YSize, const int *HandleArray, int ReverseFlag = FALSE ) ;	// �摜�t�@�C������O���t�B�b�N�n���h�������։摜�f�[�^�𕪊��]������
extern	int			NS_ReloadDivGraphWithStrLen(			const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, int   XSize, int   YSize, const int *HandleArray, int ReverseFlag = FALSE ) ;	// �摜�t�@�C������O���t�B�b�N�n���h�������։摜�f�[�^�𕪊��]������
extern	int			NS_ReloadDivGraphF(					const TCHAR *FileName,                        int AllNum, int XNum, int YNum, float XSize, float YSize, const int *HandleArray, int ReverseFlag = FALSE ) ;	// �摜�t�@�C������O���t�B�b�N�n���h�������։摜�f�[�^�𕪊��]������( float�� )
extern	int			NS_ReloadDivGraphFWithStrLen(			const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, float XSize, float YSize, const int *HandleArray, int ReverseFlag = FALSE ) ;	// �摜�t�@�C������O���t�B�b�N�n���h�������։摜�f�[�^�𕪊��]������( float�� )
extern	int			NS_ReloadReverseGraph(					const TCHAR *FileName,                        int GrHandle ) ;																									// ReloadGraph �̉摜���]�����ǉ���
extern	int			NS_ReloadReverseGraphWithStrLen(		const TCHAR *FileName, size_t FileNameLength, int GrHandle ) ;																									// ReloadGraph �̉摜���]�����ǉ���
extern	int			NS_ReloadReverseDivGraph(				const TCHAR *FileName,                        int AllNum, int XNum, int YNum, int   XSize, int   YSize, const int *HandleArray ) ;								// ReloadDivGraph �̉摜���]�����ǉ���
extern	int			NS_ReloadReverseDivGraphWithStrLen(	const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, int   XSize, int   YSize, const int *HandleArray ) ;								// ReloadDivGraph �̉摜���]�����ǉ���
extern	int			NS_ReloadReverseDivGraphF(				const TCHAR *FileName,                        int AllNum, int XNum, int YNum, float XSize, float YSize, const int *HandleArray ) ;								// ReloadDivGraph �̉摜���]�����ǉ���( float�� )
extern	int			NS_ReloadReverseDivGraphFWithStrLen(	const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, float XSize, float YSize, const int *HandleArray ) ;								// ReloadDivGraph �̉摜���]�����ǉ���( float�� )

// �O���t�B�b�N�n���h���쐬���ݒ�W�֐�
extern	int			NS_SetGraphColorBitDepth(						int ColorBitDepth ) ;							// SetCreateGraphColorBitDepth �̋�����
extern	int			NS_GetGraphColorBitDepth(						void ) ;										// GetCreateGraphColorBitDepth �̋�����
extern	int			NS_SetCreateGraphColorBitDepth(				int BitDepth ) ;								// �쐬����O���t�B�b�N�̐F�[�x��ݒ肷��
extern	int			NS_GetCreateGraphColorBitDepth(				void ) ;										// �쐬����O���t�B�b�N�̐F�[�x���擾����
extern	int			NS_SetCreateGraphChannelBitDepth(				int BitDepth ) ;								// �쐬����O���t�B�b�N�̂P�`�����l���ӂ�̃r�b�g�[�x��ݒ肷��
extern	int			NS_GetCreateGraphChannelBitDepth(				void ) ;										// �쐬����O���t�B�b�N�̂P�`�����l���ӂ�̃r�b�g�[�x���擾����
extern	int			NS_SetCreateGraphInitGraphDelete(				int Flag ) ;									// �쐬����O���t�B�b�N�n���h���� InitGraph() �ō폜����邩��ݒ肷��( Flag  TRUE:InitGraph�ō폜�����(�f�t�H���g)  FALSE:InitGraph�ō폜����Ȃ� )
extern	int			NS_GetCreateGraphInitGraphDelete(				void ) ;										// �쐬����O���t�B�b�N�n���h���� InitGraph() �ō폜����邩���擾����( Flag  TRUE:InitGraph�ō폜�����(�f�t�H���g)  FALSE:InitGraph�ō폜����Ȃ� )
extern	int			NS_SetCreateGraphHandle(						int GrHandle ) ;								// �쐬����O���t�B�b�N�n���h���̃n���h���l��ݒ肷��A�O�ȉ��̒l��n���Ɛݒ����( ���݂��Ȃ��O���t�B�b�N�n���h���̒l�̏ꍇ�̂ݗL�� )
extern	int			NS_GetCreateGraphHandle(						void ) ;										// �쐬����O���t�B�b�N�n���h���̃n���h���l���擾����
extern	int			NS_SetCreateDivGraphHandle(					const int *HandleArray, int HandleNum ) ;		// �쐬����O���t�B�b�N�n���h���̃n���h���l��ݒ肷��ALoadDivGraph ���̕����摜�ǂݍ��ݗp�AHandleArray �� NULL ��n���Ɛݒ����( ���݂��Ȃ��O���t�B�b�N�n���h���̒l�̏ꍇ�̂ݗL�� )
extern	int			NS_GetCreateDivGraphHandle(					int *HandleArray ) ;							// �쐬����O���t�B�b�N�n���h���̃n���h���l���擾����ALoadDivGraph ���̕����摜�ǂݍ��ݗp�A�߂�l�� SetCreateDivGraphHandle �̈��� HandleNum �ɓn�����l�AHandleArray �� NULL �ɂ��邱�Ƃ��\
extern	int			NS_SetDrawValidGraphCreateFlag(				int Flag ) ;									// �`��\�ȃO���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����( TRUE:�`��\  FALSE:�`��s�\ )
extern	int			NS_GetDrawValidGraphCreateFlag(				void ) ;										// �`��\�ȃO���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetDrawValidFlagOf3DGraph(					int Flag ) ;									// SetDrawValidGraphCreateFlag �̋�����
extern	int			NS_SetLeftUpColorIsTransColorFlag(				int Flag ) ;									// �摜����̐F�𓧉ߐF�ɂ��邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetUsePaletteGraphFlag(						int Flag ) ;									// �ǂݍ��މ摜���p���b�g�摜�̏ꍇ�A�p���b�g�摜�Ƃ��Ďg�p�ł���ꍇ�̓p���b�g�摜�Ƃ��Ďg�p���邩�ǂ�����ݒ肷��( TRUE:�p���b�g�摜�Ƃ��Ďg�p�ł���ꍇ�̓p���b�g�摜�Ƃ��Ďg�p����( �f�t�H���g )  FALSE:�p���b�g�摜�Ƃ��Ďg�p�ł���ꍇ���p���b�g�摜�Ƃ��Ă͎g�p���Ȃ�( �ʏ�^�C�v�̉摜�ɕϊ����Ďg�p���� ) )
extern	int			NS_SetUseSystemMemGraphCreateFlag(				int Flag ) ;									// �V�X�e����������ɃO���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����( TRUE:�V�X�e����������ɍ쐬  FALSE:�u�q�`�l��ɍ쐬 )
extern	int			NS_GetUseSystemMemGraphCreateFlag(				void ) ;										// �V�X�e����������ɃO���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����( TRUE:�V�X�e����������ɍ쐬  FALSE:�u�q�`�l��ɍ쐬 )
extern	int			NS_SetUseBlendGraphCreateFlag(					int Flag ) ;									// �u�����h�����p�摜���쐬���邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_GetUseBlendGraphCreateFlag(					void ) ;										// �u�����h�����p�摜���쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetUseAlphaTestGraphCreateFlag(				int Flag ) ;									// �A���t�@�e�X�g���g�p����O���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_GetUseAlphaTestGraphCreateFlag(				void ) ;										// �A���t�@�e�X�g���g�p����O���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetUseAlphaTestFlag(						int Flag ) ;									// SetUseAlphaTestGraphCreateFlag �̋�����
extern	int			NS_GetUseAlphaTestFlag(						void ) ;										// GetUseAlphaTestGraphCreateFlag �̋�����
extern	int			NS_SetCubeMapTextureCreateFlag(				int Flag ) ;									// �L���[�u�}�b�v�e�N�X�`�����쐬���邩�ǂ����̃t���O��ݒ肷��
extern	int			NS_GetCubeMapTextureCreateFlag(				void ) ;										// �L���[�u�}�b�v�e�N�X�`�����쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetUseNoBlendModeParam(						int Flag ) ;									// SetDrawBlendMode �֐��̑������� DX_BLENDMODE_NOBLEND ���������ۂɁA�f�t�H���g�ł͑������͓����łQ�T�T���w�肵�����ƂɂȂ邪�A���̎����Q�T�T�������Ȃ����ǂ�����ݒ肷��( TRUE:���Ȃ�(�������̒l���g�p�����)   FALSE:����(�������̒l�͖�������� 255 ����Ɏg�p�����)(�f�t�H���g) )���`�����l���t���摜�ɑ΂��ĕ`����s���ꍇ�݈̂Ӗ�������֐�
extern	int			NS_SetDrawValidAlphaChannelGraphCreateFlag(	int Flag ) ;									// �`��\�ȃ��`�����l���t���摜���쐬���邩�ǂ����̃t���O���Z�b�g����,SetDrawValidGraphCreateFlag �֐��ŕ`��\�摜���쐬����悤�ɐݒ肳��Ă��Ȃ��ƌ��ʂ��Ȃ�( TRUE:���`�����l���t�� FALSE:���`�����l���Ȃ� )
extern	int			NS_GetDrawValidAlphaChannelGraphCreateFlag(	void ) ;										// �`��\�ȃ��`�����l���t���摜���쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetDrawValidFloatTypeGraphCreateFlag(		int Flag ) ;									// �`��\�ȕ��������_�^�̉摜���쐬���邩�ǂ����̃t���O���Z�b�g����,SetDrawValidGraphCreateFlag �֐��ŕ`��\�摜���쐬����悤�ɐݒ肳��Ă��Ȃ��ƌ��ʂ��Ȃ��A�f�o�t�� Float�^�̉摜�ɑΉ����Ă��Ȃ��ꍇ�͉摜�쐬�Ɏ��s����( TRUE:Float�^ FALSE:Int�^ )
extern	int			NS_GetDrawValidFloatTypeGraphCreateFlag(		void ) ;										// �`��\�ȕ��������_�^�̉摜���쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetDrawValidGraphCreateZBufferFlag(			int Flag ) ;									// �`��\�摜���쐬����ۂɐ�p�̂y�o�b�t�@���쐬���邩�ǂ�����ݒ肷��( �f�t�H���g�ł� TRUE( �쐬���� ) )
extern	int			NS_GetDrawValidGraphCreateZBufferFlag(			void ) ;										// �`��\�摜���쐬����ۂɐ�p�̂y�o�b�t�@���쐬���邩�ǂ������擾����
extern	int			NS_SetCreateDrawValidGraphZBufferBitDepth(		int BitDepth ) ;								// SetDrawScreen �̈����Ƃ��ēn����( �`��ΏۂƂ��Ďg�p�ł��� )�O���t�B�b�N�n���h���ɓK�p����y�o�b�t�@�̃r�b�g�[�x��ݒ肷��( BitDepth:�r�b�g�[�x( �w��\�Ȓl�� 16, 24, 32 �̉��ꂩ( SetDrawValidGraphCreateFlag �֐��ŕ`��ΏۂƂ��Ďg�p�ł���O���t�B�b�N�n���h�����쐬����悤�ɐݒ肳��Ă��Ȃ��ƌ��ʂ���܂��� )
extern	int			NS_GetCreateDrawValidGraphZBufferBitDepth(		void ) ;										// SetDrawScreen �̈����Ƃ��ēn����( �`��ΏۂƂ��Ďg�p�ł��� )�O���t�B�b�N�n���h���ɓK�p����y�o�b�t�@�̃r�b�g�[�x���擾����
extern	int			NS_SetCreateDrawValidGraphMipLevels(			int MipLevels ) ;								// SetDrawScreen �̈����Ƃ��ēn����( �`��ΏۂƂ��Ďg�p�ł��� )�O���t�B�b�N�n���h���ɓK�p����MipMap�̃��x����ݒ肷��
extern	int			NS_GetCreateDrawValidGraphMipLevels(			void ) ;										// SetDrawScreen �̈����Ƃ��ēn����( �`��ΏۂƂ��Ďg�p�ł��� )�O���t�B�b�N�n���h���ɓK�p����MipMap�̃��x�����擾����
extern	int			NS_SetCreateDrawValidGraphChannelNum(			int ChannelNum ) ;								// �쐬����`��\�ȉ摜�̃`�����l������ݒ肷��,SetDrawValidGraphCreateFlag �֐��ŕ`��\�摜���쐬����悤�ɐݒ肳��Ă��Ȃ��ƌ��ʂ��Ȃ�
extern	int			NS_GetCreateDrawValidGraphChannelNum(			void ) ;										// �쐬����`��\�ȉ摜�̃`�����l�������擾����
extern	int			NS_SetCreateDrawValidGraphMultiSample(			int Samples, int Quality ) ;					// SetDrawScreen �̈����Ƃ��ēn����( �`��ΏۂƂ��Ďg�p�ł��� )�O���t�B�b�N�n���h���ɓK�p����}���`�T���v�����O( �A���`�G�C���A�V���O )�ݒ���s��( Samples:�}���`�T���v�������Ɏg�p����h�b�g��( �����قǏd���Ȃ�܂� )  Quality:�}���`�T���v�������̕i�� )
extern	int			NS_SetDrawValidMultiSample(					int Samples, int Quality ) ;					// �`��\�ȉ摜�̃}���`�T���v�����O�ݒ���s��
extern	int			NS_GetMultiSampleQuality(						int Samples ) ;									// �w��̃}���`�T���v�����Ŏg�p�ł���ő�N�I���e�B�l���擾����( �߂�l���}�C�i�X�̏ꍇ�͈����̃T���v�������g�p�ł��Ȃ����Ƃ������܂� )
extern	int			NS_SetUseTransColor(							int Flag ) ;									// ���ߐF�@�\���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetUseTransColorGraphCreateFlag(			int Flag ) ;									// ���ߐF�@�\���g�p���邱�Ƃ�O��Ƃ����摜�̓ǂݍ��ݏ������s�����ǂ�����ݒ肷��( TRUE �ɂ���� SetDrawMode( DX_DRAWMODE_BILINEAR ); ��������Ԃ� DrawGraphF ���̕��������_�^���W���󂯎��֐��ŏ����_�ȉ��̒l���w�肵���ꍇ�ɔ�������`�挋�ʂ̕s���R���ɘa������ʂ����� ( �f�t�H���g�� FALSE ) )
extern	int			NS_SetUseGraphAlphaChannel(					int Flag ) ;									// SetUseAlphaChannelGraphCreateFlag �̋�����
extern	int			NS_GetUseGraphAlphaChannel(					void ) ;										// GetUseAlphaChannelGraphCreateFlag �̋�����
extern	int			NS_SetUseAlphaChannelGraphCreateFlag(			int Flag ) ;									// ���`�����l���t���O���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����( TRUE:���`�����l���t��   FALSE:���`�����l������ )
extern	int			NS_GetUseAlphaChannelGraphCreateFlag(			void ) ;										// ���`�����l���t���O���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����( TRUE:���`�����l���t��   FALSE:���`�����l������ )
extern	int			NS_SetUseNotManageTextureFlag(					int Flag ) ;									// ��Ǘ��e�N�X�`�����g�p���邩�A�̃t���O���Z�b�g( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
extern	int			NS_GetUseNotManageTextureFlag(					void ) ;										// ��Ǘ��e�N�X�`�����g�p���邩�A�̃t���O���擾����( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
extern	int			NS_SetUsePlatformTextureFormat(				int PlatformTextureFormat ) ;					// �쐬����O���t�B�b�N�n���h���Ŏg�p������ˑ��̃e�N�X�`���t�H�[�}�b�g���w�肷��( Direct3D9���Ȃ� DX_TEXTUREFORMAT_DIRECT3D9_R8G8B8 �ȂǁA0 ��n���Ɖ��� )
extern	int			NS_GetUsePlatformTextureFormat(				void ) ;										// �쐬����O���t�B�b�N�n���h���Ŏg�p������ˑ��̃e�N�X�`���t�H�[�}�b�g���擾����
extern	int			NS_SetTransColor(								int Red, int Green, int Blue ) ;				// �O���t�B�b�N�ɐݒ肷�铧�ߐF���Z�b�g����
extern	int			NS_GetTransColor(								int *Red, int *Green, int *Blue ) ;				// ���ߐF�𓾂�
extern	int			NS_SetUseDivGraphFlag(							int Flag ) ;									// �K�v�Ȃ�O���t�B�b�N�̕������s�����A�t���O�̃Z�b�g
extern	int			NS_SetUseAlphaImageLoadFlag(					int Flag ) ;									// LoadGraph �Ȃǂ̍ۂɃt�@�C�����̖����� _a ���t�����A���t�@�`�����l���p�̉摜�t�@�C����ǉ��œǂݍ��ޏ������s�����ǂ�����ݒ肷��( TRUE:�s��( �f�t�H���g )  FALSE:�s��Ȃ� )
extern	int			NS_SetUseMaxTextureSize(						int Size ) ;									// �g�p����e�N�X�`���[�̍ő�T�C�Y���Z�b�g(0�Ńf�t�H���g)
extern	int			NS_SetUseGraphBaseDataBackup(					int Flag ) ;									// �摜���쐬����ۂɎg�p�����摜�f�[�^�̃o�b�N�A�b�v�����ăf�o�C�X���X�g���Ɏg�p���邩�ǂ����̃t���O���Z�b�g����( TRUE:�o�b�N�A�b�v������( �f�t�H���g )  FALSE:�o�b�N�A�b�v�����Ȃ� )
extern	int			NS_GetUseGraphBaseDataBackup(					void ) ;										// �摜���쐬����ۂɎg�p�����摜�f�[�^�̃o�b�N�A�b�v�����ăf�o�C�X���X�g���Ɏg�p���邩�ǂ����̃t���O���擾����
extern	int			NS_SetUseLoadDivGraphSizeCheckFlag(			int Flag ) ;									// LoadDivGraph �n�̕����摜�ǂݍ��݊֐��ŃT�C�Y�̃`�F�b�N���s�����ǂ�����ݒ肷��( Flag:TRUE( �`�F�b�N���s��(�f�t�H���g) )  FALSE:�`�F�b�N���s��Ȃ� )
extern	int			NS_GetUseLoadDivGraphSizeCheckFlag(			void ) ;										// LoadDivGraph �n�̕����摜�ǂݍ��݊֐��ŃT�C�Y�̃`�F�b�N���s�����ǂ����̐ݒ���擾����

// �摜���֌W�֐�
extern	const unsigned int* NS_GetFullColorImage(				int GrHandle ) ;																		// �w��̉摜�̂`�q�f�a�W�̃t���J���[�C���[�W���擾����

extern	int			NS_GraphLock(						int GrHandle, int *PitchBuf, void **DataPointBuf, COLORDATA **ColorDataPP = NULL, int WriteOnly = FALSE ) ;	// �O���t�B�b�N�������̈�̃��b�N
extern	int			NS_GraphUnLock(					int GrHandle ) ;																		// �O���t�B�b�N�������̈�̃��b�N����

extern	int			NS_SetUseGraphZBuffer(				int GrHandle, int UseFlag, int BitDepth = -1 ) ;										// �O���t�B�b�N��p�̂y�o�b�t�@�������ǂ�����ݒ肷��( �`��\�摜�̂݉\ )
extern	int			NS_CopyGraphZBufferImage(			int DestGrHandle, int SrcGrHandle ) ;													// �O���t�B�b�N�̂y�o�b�t�@�̏�Ԃ�ʂ̃O���t�B�b�N�̂y�o�b�t�@�ɃR�s�[����( DestGrHandle �� SrcGrHandle ���y�o�b�t�@�������Ă���`��\�摜�ŁA�T�C�Y�������ł���A���A���`�G�C���A�X�摜�ł͂Ȃ����Ƃ����� )

extern	int			NS_SetDeviceLostDeleteGraphFlag(	int GrHandle, int DeleteFlag ) ;														// �O���t�B�b�N�X�f�o�C�X�̃f�o�C�X���X�g�������Ɏw��̃O���t�B�b�N�n���h�����폜���邩�ǂ�����ݒ肷��( TRUE:�f�o�C�X���X�g���ɍ폜����  FALSE:�f�o�C�X���X�g���������Ă��폜���Ȃ� )

extern	int			NS_GetGraphSize(					int GrHandle, int   *SizeXBuf, int   *SizeYBuf ) ;										// �O���t�B�b�N�n���h�������摜�̃T�C�Y�𓾂�
extern	int			NS_GetGraphSizeF(					int GrHandle, float *SizeXBuf, float *SizeYBuf ) ;										// �O���t�B�b�N�n���h�������摜�̃T�C�Y�𓾂�( float�^ )
extern	int			NS_GetGraphTextureSize(			int GrHandle, int   *SizeXBuf, int   *SizeYBuf ) ;										// �O���t�B�b�N�n���h��������ڂ̃e�N�X�`���̃T�C�Y�𓾂�
extern	int			NS_GetGraphUseBaseGraphArea(		int GrHandle, int   *UseX,     int   *UseY,    int *UseSizeX, int *UseSizeY ) ;			// LoadDivGraph �� DerivationGraph �Ō��摜�̈ꕔ�����g�p���Ă���ꍇ�ɁA�w��̃O���t�B�b�N�n���h�����g�p���Ă��錳�摜�͈̔͂��擾����
extern	int			NS_GetGraphMipmapCount(			int GrHandle ) ;																		// �O���t�B�b�N�����~�b�v�}�b�v���x���̐����擾����
extern	int			NS_GetGraphFilePath(				int GrHandle, TCHAR *FilePathBuffer ) ;													// �O���t�B�b�N�n���h�����摜�t�@�C������ǂݍ��܂�Ă����ꍇ�A���̉摜�̃t�@�C���p�X���擾����
extern	int			NS_CheckDrawValidGraph(			int GrHandle ) ;																		// �w��̃O���t�B�b�N�n���h�����`��Ώۂɂł���( SetDrawScreen �̈����ɓn���� )�O���t�B�b�N�n���h�����ǂ������擾����( �߂�l�@TRUE:�`��Ώۂɂł���O���t�B�b�N�n���h���@FALSE:�`��Ώۂɂł��Ȃ��O���t�B�b�N�n���h�� )

#ifdef WINDOWS_DESKTOP_OS
extern	const void*	NS_GetGraphID3D11Texture2D(		int GrHandle ) ;												// �O���t�B�b�N�n���h�������� ID3D11Texture2D ���擾����( Direct3D11 ���g�p���Ă���ꍇ�̂ݗL�� )( �߂�l�� ID3D11Texture2D * �ɃL���X�g���Ă������� )
extern	const void*	NS_GetGraphID3D11RenderTargetView(	int GrHandle ) ;												// �O���t�B�b�N�n���h�������� ID3D11RenderTargetView ���擾����( Direct3D11 ���g�p���Ă��āA���� MakeScreen �ō쐬�����O���t�B�b�N�n���h���ł̂ݗL�� )( �߂�l�� ID3D11RenderTargetView * �ɃL���X�g���Ă������� )
extern	const void*	NS_GetGraphID3D11DepthStencilView(	int GrHandle ) ;												// �O���t�B�b�N�n���h�������� ID3D11DepthStencilView ���擾����( Direct3D11 ���g�p���Ă��āA���� MakeScreen �ō쐬�����O���t�B�b�N�n���h���ł̂ݗL�� )( �߂�l�� ID3D11DepthStencilView * �ɃL���X�g���Ă������� )
#endif

extern	const COLORDATA*	NS_GetTexColorData(				int AlphaCh, int AlphaTest, int ColorBitDepth, int DrawValid = FALSE ) ;				// �J���[�f�[�^�𓾂�
#ifndef DX_COMPILE_TYPE_C_LANGUAGE
extern	const COLORDATA*	NS_GetTexColorData(				const IMAGEFORMATDESC *Format ) ;														// �t�H�[�}�b�g�Ɋ�Â����J���[�f�[�^�𓾂�
extern	const COLORDATA*	NS_GetTexColorData(				int FormatIndex ) ;																		// �w��̃t�H�[�}�b�g�C���f�b�N�X�̃J���[�f�[�^�𓾂�
#endif // DX_COMPILE_TYPE_C_LANGUAGE
extern	const COLORDATA*	NS_GetTexColorData2(			const IMAGEFORMATDESC *Format ) ;														// �t�H�[�}�b�g�Ɋ�Â����J���[�f�[�^�𓾂�
extern	const COLORDATA*	NS_GetTexColorData3(			int FormatIndex /* DX_GRAPHICSIMAGE_FORMAT_3D_RGB32 �� */ ) ;							// �w��̃t�H�[�}�b�g�C���f�b�N�X�̃J���[�f�[�^�𓾂�
extern	int			NS_GetMaxGraphTextureSize(			int *SizeX, int *SizeY ) ;																// �O���t�B�b�N�Ɏg�p�����ő�e�N�X�`���T�C�Y���擾����
extern	int			NS_GetValidRestoreShredPoint(		void ) ;																				// �O���t�B�b�N�����֐��̗L�����擾																
extern	int			NS_GetCreateGraphColorData(		COLORDATA *ColorData, IMAGEFORMATDESC *Format ) ;										// ���ꂩ��V���ɃO���t�B�b�N���쐬����ꍇ�Ɏg�p����J���[�����擾����

// �摜�p���b�g����֌W�֐�( �\�t�g�E�G�A�摜�̂ݎg�p�\ )
extern	int			NS_GetGraphPalette(				int GrHandle, int ColorIndex, int *Red, int *Green, int *Blue ) ;						// ��������ɓǂݍ��񂾉摜�̃p���b�g���擾����(�t���J���[�摜�̏ꍇ�͖���)
extern	int			NS_GetGraphOriginalPalette(		int GrHandle, int ColorIndex, int *Red, int *Green, int *Blue ) ;						// ��������ɓǂݍ��񂾉摜�� SetGraphPalette �ŕύX����O�̃p���b�g���擾����
extern	int			NS_SetGraphPalette(				int GrHandle, int ColorIndex, unsigned int Color ) ;												// ��������ɓǂݍ��񂾉摜�̃p���b�g��ύX����(�t���J���[�摜�̏ꍇ�͖���)
extern	int			NS_ResetGraphPalette(				int GrHandle ) ;																		// SetGraphPalette �ŕύX�����p���b�g��S�Č��ɖ߂�

// �}�`�`��֐�
extern	int			NS_DrawLine(         int   x1, int   y1, int   x2, int   y2,                                         unsigned int Color, int   Thickness = 1    ) ;						// ����`�悷��
extern	int			NS_DrawLineAA(       float x1, float y1, float x2, float y2,                                         unsigned int Color, float Thickness = 1.0f ) ;						// ����`�悷��( �A���`�G�C���A�X�t�� )
extern	int			NS_DrawBox(          int   x1, int   y1, int   x2, int   y2,                                         unsigned int Color, int FillFlag ) ;								// �l�p�`��`�悷��
extern	int			NS_DrawBoxAA(        float x1, float y1, float x2, float y2,                                         unsigned int Color, int FillFlag, float LineThickness = 1.0f ) ;	// �l�p�`��`�悷��( �A���`�G�C���A�X�t�� )
extern	int			NS_DrawFillBox(      int   x1, int   y1, int   x2, int   y2,                                         unsigned int Color ) ;												// ���g��h��Ԃ��l�p�`��`�悷��
extern	int			NS_DrawLineBox(      int   x1, int   y1, int   x2, int   y2,                                         unsigned int Color ) ;												// �g�����̎l�p�`�̕`�� ����
extern	int			NS_DrawCircle(       int   x,  int   y,  int   r,                                                    unsigned int Color, int FillFlag = TRUE, int   LineThickness = 1 ) ;	// �~��`�悷��
extern	int			NS_DrawCircleAA(     float x,  float y,  float r,            int posnum,                             unsigned int Color, int FillFlag = TRUE, float LineThickness = 1, float Angle = 0.0 ) ;	// �~��`�悷��( �A���`�G�C���A�X�t�� )
extern	int			NS_DrawOval(         int   x,  int   y,  int   rx, int   ry,                                         unsigned int Color, int FillFlag,        int   LineThickness = 1 ) ;	// �ȉ~��`�悷��
extern	int			NS_DrawOvalAA(       float x,  float y,  float rx, float ry, int posnum,                             unsigned int Color, int FillFlag,        float LineThickness = 1 ) ;	// �ȉ~��`�悷��( �A���`�G�C���A�X�t�� )
extern	int			NS_DrawOval_Rect(    int   x1, int   y1, int   x2, int   y2,                                         unsigned int Color, int FillFlag ) ;										// �w��̋�`�Ɏ��܂�~( �ȉ~ )��`�悷��
extern	int			NS_DrawTriangle(     int   x1, int   y1, int   x2, int   y2, int   x3, int   y3,                     unsigned int Color, int FillFlag ) ;									// �O�p�`��`�悷��
extern	int			NS_DrawTriangleAA(   float x1, float y1, float x2, float y2, float x3, float y3,                     unsigned int Color, int FillFlag, float LineThickness = 1.0f ) ;		// �O�p�`��`�悷��( �A���`�G�C���A�X�t�� )
extern	int			NS_DrawQuadrangle(   int   x1, int   y1, int   x2, int   y2, int   x3, int   y3, int   x4, int   y4, unsigned int Color, int FillFlag ) ;									// �l�p�`��`�悷��
extern	int			NS_DrawQuadrangleAA( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, unsigned int Color, int FillFlag, float LineThickness = 1.0f ) ;		// �l�p�`��`�悷��( �A���`�G�C���A�X�t�� )
extern	int			NS_DrawRoundRect(    int   x1, int   y1, int   x2, int   y2, int   rx, int   ry,                     unsigned int Color, int FillFlag ) ;									// �p�̊ۂ��l�p�`��`�悷��
extern	int			NS_DrawRoundRectAA(  float x1, float y1, float x2, float y2, float rx, float ry, int posnum,         unsigned int Color, int FillFlag, float LineThickness = 1.0f ) ;		// �p�̊ۂ��l�p�`��`�悷��( �A���`�G�C���A�X�t�� )
extern	int			NS_BeginAADraw(      void ) ;																																					// DrawTriangleAA �Ȃǂ̃A���`�G�C���A�X�t���}�`�`��̏������s��
extern	int			NS_EndAADraw(        void ) ;																																					// DrawTriangleAA �Ȃǂ̃A���`�G�C���A�X�t���}�`�`��̌�n�����s��
extern 	int			NS_DrawPixel(        int   x,  int   y,                                                              unsigned int Color ) ;												// �_��`�悷��

extern	int			NS_Paint(			int x, int y, unsigned int FillColor, ULONGLONG BoundaryColor = ULL_PARAM( 0xffffffffffffffff ) ) ;		// �w��_���狫�E�F������Ƃ���܂œh��Ԃ�(���E�F�� -1 �ɂ���Ǝw��_�̐F�̗̈��h��Ԃ�)

extern 	int			NS_DrawPixelSet(   const POINTDATA *PointData, int Num ) ;																	// �_�̏W����`�悷��
extern	int			NS_DrawLineSet(    const LINEDATA *LineData,   int Num ) ;																	// ���̏W����`�悷��
extern	int			NS_DrawBoxSet(     const RECTDATA *RectData,   int Num ) ;																	// ��`�̏W����`�悷��

extern	int			NS_DrawPixel3D(     VECTOR   Pos,                                                                 unsigned int Color ) ;						// �R�c�̓_��`�悷��
extern	int			NS_DrawPixel3DD(    VECTOR_D Pos,                                                                 unsigned int Color ) ;						// �R�c�̓_��`�悷��
extern	int			NS_DrawLine3D(      VECTOR   Pos1,   VECTOR   Pos2,                                               unsigned int Color ) ;						// �R�c�̐�����`�悷��
extern	int			NS_DrawLine3DD(     VECTOR_D Pos1,   VECTOR_D Pos2,                                               unsigned int Color ) ;						// �R�c�̐�����`�悷��
extern	int			NS_DrawTriangle3D(  VECTOR   Pos1,   VECTOR   Pos2, VECTOR   Pos3,                                unsigned int Color, int FillFlag ) ;		// �R�c�̎O�p�`��`�悷��
extern	int			NS_DrawTriangle3DD( VECTOR_D Pos1,   VECTOR_D Pos2, VECTOR_D Pos3,                                unsigned int Color, int FillFlag ) ;		// �R�c�̎O�p�`��`�悷��
extern	int			NS_DrawCube3D(      VECTOR   Pos1,   VECTOR   Pos2,                            unsigned int DifColor, unsigned int SpcColor, int FillFlag ) ;		// �R�c�̗����̂�`�悷��
extern	int			NS_DrawCube3DD(     VECTOR_D Pos1,   VECTOR_D Pos2,                            unsigned int DifColor, unsigned int SpcColor, int FillFlag ) ;		// �R�c�̗����̂�`�悷��
extern	int			NS_DrawCubeSet3D(   CUBEDATA *CubeDataArray, int Num, int FillFlag ) ;																				// �R�c�̗����̂̏W����`�悷��
extern	int			NS_DrawSphere3D(    VECTOR   CenterPos,                  float  r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag ) ;		// �R�c�̋��̂�`�悷��
extern	int			NS_DrawSphere3DD(   VECTOR_D CenterPos,                  double r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag ) ;		// �R�c�̋��̂�`�悷��
extern	int			NS_DrawCapsule3D(   VECTOR   Pos1,   VECTOR   Pos2,      float  r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag ) ;		// �R�c�̃J�v�Z����`�悷��
extern	int			NS_DrawCapsule3DD(  VECTOR_D Pos1,   VECTOR_D Pos2,      double r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag ) ;		// �R�c�̃J�v�Z����`�悷��
extern	int			NS_DrawCone3D(      VECTOR   TopPos, VECTOR   BottomPos, float  r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag ) ;		// �R�c�̉~����`�悷��
extern	int			NS_DrawCone3DD(     VECTOR_D TopPos, VECTOR_D BottomPos, double r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag ) ;		// �R�c�̉~����`�悷��

// �摜�`��֐�
extern	int			NS_LoadGraphScreen(          int x, int y, const TCHAR *GraphName, int TransFlag ) ;								// �a�l�o�t�@�C����ǂ݂���ŉ�ʂɕ`�悷��
extern	int			NS_LoadGraphScreenWithStrLen( int x, int y, const TCHAR *GraphName, size_t GraphNameLength, int TransFlag ) ;										// �摜�t�@�C����ǂ݂���ŉ�ʂɕ`�悷��

extern	int			NS_DrawGraph(                int x, int y,                                                                 int GrHandle, int TransFlag ) ;										// �O���t�B�b�N�̕`��
extern	int			NS_DrawExtendGraph(          int x1, int y1, int x2, int y2,                                               int GrHandle, int TransFlag ) ;										// �O���t�B�b�N�̊g��k���`��
extern	int			NS_DrawRotaGraph(            int x, int y,                 double ExRate,                    double Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;				// �O���t�B�b�N�̉�]�`��
extern	int			NS_DrawRotaGraph2(           int x, int y, int cx, int cy, double ExtRate,                   double Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE  ) ;				// �O���t�B�b�N�̉�]�`��Q
extern	int			NS_DrawRotaGraph3(           int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 				// �O���t�B�b�N�̉�]�`��R
extern	int			NS_DrawRotaGraphFast(        int x, int y,                 float  ExRate,                    float  Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;				// �摜�̉�]�`��( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRotaGraphFast2(       int x, int y, int cx, int cy, float  ExtRate,                   float  Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;				// �摜�̉�]�`��Q( ��]���S�w��t�� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRotaGraphFast3(       int x, int y, int cx, int cy, float  ExtRateX, float  ExtRateY, float  Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 				// �摜�̉�]�`��R( ��]���S�w��t���{�c���g�嗦�ʎw��� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawModiGraph(            int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,               int GrHandle, int TransFlag ) ;										// �摜�̎��R�ό`�`��
extern	int			NS_DrawTurnGraph(            int x, int y,                                                                 int GrHandle, int TransFlag ) ;										// �摜�̍��E���]�`��
extern	int			NS_DrawReverseGraph(         int x, int y,                                                                 int GrHandle, int TransFlag, int ReverseXFlag = FALSE , int ReverseYFlag = FALSE ) ;		// �摜�̔��]�`��

extern	int			NS_DrawGraphF(               float xf, float yf,                                                                       int GrHandle, int TransFlag ) ;							// �O���t�B�b�N�̕`��
extern	int			NS_DrawExtendGraphF(         float x1f, float y1f, float x2f, float y2,                                                int GrHandle, int TransFlag ) ;							// �O���t�B�b�N�̊g��k���`��
extern	int			NS_DrawRotaGraphF(           float xf, float yf,                       double ExRate,                    double Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE  ) ;	// �O���t�B�b�N�̉�]�`��
extern	int			NS_DrawRotaGraph2F(          float xf, float yf, float cxf, float cyf, double ExtRate,                   double Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE  ) ;	// �O���t�B�b�N�̉�]�`��Q
extern	int			NS_DrawRotaGraph3F(          float xf, float yf, float cxf, float cyf, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 	// �O���t�B�b�N�̉�]�`��R
extern	int			NS_DrawRotaGraphFastF(       float xf, float yf,                       float  ExRate,                    float  Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;	// �摜�̉�]�`��( ���W�w�肪 float �� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRotaGraphFast2F(      float xf, float yf, float cxf, float cyf, float  ExtRate,                   float  Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;	// �摜�̉�]�`��Q( ��]���S�w��t�� )( ���W�w�肪 float �� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRotaGraphFast3F(      float xf, float yf, float cxf, float cyf, float  ExtRateX, float  ExtRateY, float  Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 	// �摜�̉�]�`��R( ��]���S�w��t���{�c���g�嗦�ʎw��� )( ���W�w�肪 float �� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawModiGraphF(           float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,           int GrHandle, int TransFlag ) ;							// �摜�̎��R�ό`�`��( float �� )
extern	int			NS_DrawTurnGraphF(           float xf, float yf,                                                                       int GrHandle, int TransFlag ) ;							// �摜�̍��E���]�`��
extern	int			NS_DrawReverseGraphF(        float xf, float yf,                                                                       int GrHandle, int TransFlag, int ReverseXFlag = FALSE , int ReverseYFlag = FALSE ) ;		// �摜�̔��]�`��( ���W�w�肪 float �� )

extern	int			NS_DrawChipMap(              int Sx, int Sy, int XNum, int YNum, const int *MapData, int ChipTypeNum, int MapDataPitch, const int *ChipGrHandle, int TransFlag ) ;																											// �`�b�v�O���t�B�b�N���g�����}�b�v�`��
#ifndef DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_DrawChipMap(              int MapWidth, int MapHeight,        const int *MapData, int ChipTypeNum,                   const int *ChipGrHandle, int TransFlag, int MapDrawPointX, int MapDrawPointY, int MapDrawWidth, int MapDrawHeight, int ScreenX, int ScreenY ) ;	// �`�b�v�O���t�B�b�N���g�����}�b�v�`��
#endif // DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_DrawChipMap2(             int MapWidth, int MapHeight,        const int *MapData, int ChipTypeNum,                   const int *ChipGrHandle, int TransFlag, int MapDrawPointX, int MapDrawPointY, int MapDrawWidth, int MapDrawHeight, int ScreenX, int ScreenY ) ;	// �`�b�v�O���t�B�b�N���g�����}�b�v�`��
extern	int			NS_DrawTile(                 int x1, int y1, int x2, int y2, int Tx, int Ty, double ExtRate, double Angle, int GrHandle, int TransFlag ) ;																														// �O���t�B�b�N���w��̈�Ƀ^�C����ɕ`�悷��

extern	int			NS_DrawRectGraph(            int DestX,  int DestY,                          int SrcX, int SrcY, int    Width, int    Height,                         int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;				// �O���t�B�b�N�̎w���`�����݂̂�`��
extern	int			NS_DrawRectExtendGraph(      int DestX1, int DestY1, int DestX2, int DestY2, int SrcX, int SrcY, int SrcWidth, int SrcHeight,                         int GraphHandle, int TransFlag ) ;							// �O���t�B�b�N�̎w���`�����݂̂��g��`��
extern	int			NS_DrawRectRotaGraph(        int x, int y, int SrcX, int SrcY, int Width, int Height, double ExtRate, double Angle,                                   int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 
extern	int			NS_DrawRectRotaGraph2(       int x, int y, int SrcX, int SrcY, int Width, int Height, int cx, int cy, double ExtRate,  double Angle,                  int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 
extern	int			NS_DrawRectRotaGraph3(       int x, int y, int SrcX, int SrcY, int Width, int Height, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 
extern	int			NS_DrawRectRotaGraphFast(    int x, int y, int SrcX, int SrcY, int Width, int Height, float ExtRate, float Angle,                                   int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;				// �摜�̎w���`�����݂̂���]�`��( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRectRotaGraphFast2(   int x, int y, int SrcX, int SrcY, int Width, int Height, int cx, int cy, float ExtRate,  float Angle,                  int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;				// �摜�̎w���`�����݂̂���]�`��Q( ��]���S�w��t�� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRectRotaGraphFast3(   int x, int y, int SrcX, int SrcY, int Width, int Height, int cx, int cy, float ExtRateX, float ExtRateY, float Angle, int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;				// �摜�̎w���`�����݂̂���]�`��R( ��]���S�w��t���{�c���g�嗦�ʎw��� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRectModiGraph(        int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int SrcX, int SrcY, int Width, int Height,               int GraphHandle, int TransFlag ) ;							// �摜�̎w���`�����݂̂����R�ό`�`��

extern	int			NS_DrawRectGraphF(           float DestX,  float DestY,                              int SrcX, int SrcY, int    Width, int    Height,                           int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;	// �O���t�B�b�N�̎w���`�����݂̂�`��
extern	int			NS_DrawRectGraphF2(          float DestX,  float DestY,                              float SrcX, float SrcY, float  Width, float  Height,                           int GraphHandle, int TransFlag, int ReverseXFlag DEFAULTPARAM( = FALSE ) , int ReverseYFlag DEFAULTPARAM( = FALSE ) ) ;	// �摜�̎w���`�����݂̂𓙔{�`��( ���W�w�肪 float ��( �摜�����W�̎w��� float �� ) )
extern	int			NS_DrawRectExtendGraphF(     float DestX1, float DestY1, float DestX2, float DestY2, int SrcX, int SrcY, int SrcWidth, int SrcHeight,                           int GraphHandle, int TransFlag ) ;					// �O���t�B�b�N�̎w���`�����݂̂��g��`��
extern	int			NS_DrawRectExtendGraphF2(    float DestX1, float DestY1, float DestX2, float DestY2, float SrcX, float SrcY, float SrcWidth, float SrcHeight,                   int GraphHandle, int TransFlag ) ;															// �摜�̎w���`�����݂̂��g��`��( ���W�w�肪 float ��( �摜�����W�̎w��� float �� ) )
extern	int			NS_DrawRectRotaGraphF(       float x, float y, int SrcX, int SrcY, int Width, int Height,                       double ExtRate,                   double Angle, int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 
extern	int			NS_DrawRectRotaGraph2F(      float x, float y, int SrcX, int SrcY, int Width, int Height, float cxf, float cyf, double ExtRate,                   double Angle, int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 
extern	int			NS_DrawRectRotaGraph3F(      float x, float y, int SrcX, int SrcY, int Width, int Height, float cxf, float cyf, double ExtRateX, double ExtRateY, double Angle, int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 
extern	int			NS_DrawRectRotaGraphFastF(   float x, float y, int SrcX, int SrcY, int Width, int Height,                       float ExtRate,                    float  Angle, int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;	// �摜�̎w���`�����݂̂���]�`��( ���W�w�肪 float �� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRectRotaGraphFast2F(  float x, float y, int SrcX, int SrcY, int Width, int Height, float cxf, float cyf, float ExtRate,                    float  Angle, int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;	// �摜�̎w���`�����݂̂���]�`��Q( ��]���S�w��t�� )( ���W�w�肪 float �� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRectRotaGraphFast3F(  float x, float y, int SrcX, int SrcY, int Width, int Height, float cxf, float cyf, float ExtRateX,  float  ExtRateY, float  Angle, int GraphHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;	// �摜�̎w���`�����݂̂���]�`��R( ��]���S�w��t���{�c���g�嗦�ʎw��� )( ���W�w�肪 float �� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRectModiGraphF(       float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int SrcX, int SrcY, int Width, int Height,         int GraphHandle, int TransFlag ) ;					// �摜�̎w���`�����݂̂����R�ό`�`��( ���W�w�肪 float �� )

extern	int			NS_DrawBlendGraph(           int x, int y, int GrHandle, int TransFlag,                 int BlendGraph, int BorderParam, int BorderRange ) ;									// �u�����h�摜�ƍ������ĉ摜��`�悷��
extern	int			NS_DrawBlendGraphF(          float x, float y, int GrHandle, int TransFlag,                 int BlendGraph, int BorderParam, int BorderRange ) ;									// �u�����h�摜�ƍ������ĉ摜�𓙔{�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawBlendGraphPos(        int x, int y, int GrHandle, int TransFlag, int bx, int by, int BlendGraph, int BorderParam, int BorderRange ) ;									// �u�����h�摜�ƍ������ĉ摜��`�悷��( �u�����h�摜�̋N�_���W���w�肷��� )

extern	int			NS_DrawCircleGauge(          int CenterX, int CenterY, double Percent, int GrHandle, double StartPercent = 0.0 , double Scale = 1.0 , int ReverseX = FALSE , int ReverseY = FALSE ) ;														// �~�O���t�I�ȕ`����s��( GrHandle �̉摜�̏㉺���E�̒[�͓��ߐF�ɂ��Ă����K�v������܂� )
extern	int			NS_DrawCircleGaugeF(         float CenterX, float CenterY, double Percent, int GrHandle, double StartPercent = 0.0 , double Scale = 1.0 , int ReverseX = FALSE , int ReverseY = FALSE ) ;										// �~�O���t�I�ȕ`����s��( GrHandle �̉摜�̏㉺���E�̒[�͓��ߐF�ɂ��Ă����K�v������܂� )( ���W�w�肪 float �� )

extern	int			NS_DrawGraphToZBuffer(       int X, int Y,                                                                 int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĉ摜�̕`����s��
extern	int			NS_DrawTurnGraphToZBuffer(   int x, int y,                                                                 int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĉ摜�̍��E���]�`��
extern	int			NS_DrawReverseGraphToZBuffer( int x, int y,                                                                int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int ReverseXFlag = FALSE , int ReverseYFlag = FALSE ) ;							// �y�o�b�t�@�ɑ΂��ĉ摜�̔��]�`��
extern	int			NS_DrawExtendGraphToZBuffer( int x1, int y1, int x2, int y2,                                               int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĉ摜�̊g��k���`��
extern	int			NS_DrawRotaGraphToZBuffer(   int x, int y, double ExRate, double Angle,                                    int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;		// �y�o�b�t�@�ɑ΂��ĉ摜�̉�]�`��
extern	int			NS_DrawRotaGraph2ToZBuffer(  int x, int y, int cx, int cy, double ExtRate,                   double Angle, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;		// �y�o�b�t�@�ɑ΂��ĉ摜�̉�]�`��Q
extern	int			NS_DrawRotaGraph3ToZBuffer(  int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 	// �y�o�b�t�@�ɑ΂��ĉ摜�̉�]�`��R
extern	int			NS_DrawRotaGraphFastToZBuffer(   int x, int y, float ExRate, float Angle,                                   int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;	// �y�o�b�t�@�ɑ΂��ĉ摜�̉�]�`��( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRotaGraphFast2ToZBuffer(  int x, int y, int cx, int cy, float ExtRate,                  float Angle, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;	// �y�o�b�t�@�ɑ΂��ĉ摜�̉�]�`��Q( ��]���S�w��t�� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawRotaGraphFast3ToZBuffer(  int x, int y, int cx, int cy, float ExtRateX, float ExtRateY, float Angle, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ; 	// �y�o�b�t�@�ɑ΂��ĉ摜�̉�]�`��R( ��]���S�w��t���{�c���g�嗦�ʎw��� )( �����ŁA���W�v�Z�̃A���S���Y�����ȗ�������Ă��܂��A�`�挋�ʂɕs�s����������΂�����̕��������ł� )
extern	int			NS_DrawModiGraphToZBuffer(   int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,               int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĉ摜�̎��R�ό`�`��
extern	int			NS_DrawBoxToZBuffer(         int x1, int y1, int x2, int y2,                                               int FillFlag, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ċ�`�̕`����s��
extern	int			NS_DrawCircleToZBuffer(      int x, int y, int r,                                                          int FillFlag, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĉ~�̕`����s��
extern	int			NS_DrawTriangleToZBuffer(    int x1, int y1, int x2, int y2, int x3, int y3,                               int FillFlag, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĎO�p�`��`�悷��
extern	int			NS_DrawQuadrangleToZBuffer(  int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,               int FillFlag, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��Ďl�p�`��`�悷��
extern	int			NS_DrawRoundRectToZBuffer(   int x1, int y1, int x2, int y2, int rx, int ry,                               int FillFlag, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��Ċp�̊ۂ��l�p�`��`�悷��

extern	int			NS_DrawPolygon(                             const VERTEX    *Vertex, int PolygonNum,                                                                                                    int GrHandle, int TransFlag, int UVScaling = FALSE ) ;		// �Q�c�|���S����`�悷��( Vertex:�O�p�`���`�����钸�_�z��̐擪�A�h���X( ���_�̐��̓|���S���̐��~�R )  PolygonNum:�`�悷��|���S���̐�  GrHandle:�g�p����O���t�B�b�N�n���h��  TransFlag:���ߐF�������s�����ǂ���( TRUE:�s��  FALSE:�s��Ȃ� )  UVScaling:��{FALSE��OK )
extern	int			NS_DrawPolygon2D(                           const VERTEX2D  *Vertex, int PolygonNum,                                                                                                    int GrHandle, int TransFlag ) ;							// �Q�c�|���S����`�悷��
extern	int			NS_DrawPolygon3D(                           const VERTEX3D  *Vertex, int PolygonNum,                                                                                                    int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��
extern	int			NS_DrawPolygonIndexed2D(                    const VERTEX2D  *Vertex, int VertexNum, const unsigned short *Indices, int PolygonNum,                                                      int GrHandle, int TransFlag ) ;							// �Q�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p )
extern	int			NS_DrawPolygon32bitIndexed2D(               const VERTEX2D  *VertexArray, int VertexNum, const unsigned int   *IndexArray, int PolygonNum,                                                      int GrHandle, int TransFlag ) ;							// �Q�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p )
extern	int			NS_DrawPolygonIndexed3D(                    const VERTEX3D  *Vertex, int VertexNum, const unsigned short *Indices, int PolygonNum,                                                      int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p )
extern	int			NS_DrawPolygon32bitIndexed3D(               const VERTEX3D  *VertexArray, int VertexNum, const unsigned int   *IndexArray, int PolygonNum,                                                      int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p )
extern	int			NS_DrawPolygonIndexed3DBase(                const VERTEX_3D *Vertex, int VertexNum, const unsigned short *Indices, int IndexNum,   int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p )( ���o�[�W�����p )
extern	int			NS_DrawPolygon32bitIndexed3DBase(           const VERTEX_3D *VertexArray, int VertexNum, const unsigned int   *IndexArray, int IndexNum,   int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p )( ���o�[�W�����p )
extern	int			NS_DrawPolygon3DBase(                       const VERTEX_3D *Vertex, int VertexNum,                                                int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���o�[�W�����p )
#ifndef DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_DrawPolygon3D(                           const VERTEX_3D *Vertex, int PolygonNum,                                                                                                    int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���o�[�W�����p )
#endif // DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_DrawPolygon3D2(                          const VERTEX_3D *Vertex, int PolygonNum,                                                                                                    int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���o�[�W�����p )

extern	int			NS_DrawPolygonBase(                         const VERTEX    *Vertex, int VertexNum,                                                int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag, int UVScaling = FALSE ) ;		// �Q�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitive2D(                         const VERTEX2D  *Vertex, int VertexNum,                                                int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �Q�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitive3D(                         const VERTEX3D  *Vertex, int VertexNum,                                                int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �R�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitiveIndexed2D(                  const VERTEX2D  *Vertex, int VertexNum, const unsigned short *Indices, int IndexNum,   int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �Q�c�v���~�e�B�u��`�悷��(���_�C���f�b�N�X�g�p)
extern	int			NS_DrawPrimitive32bitIndexed2D(             const VERTEX2D  *VertexArray, int VertexNum, const unsigned int   *IndexArray, int IndexNum,   int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �Q�c�v���~�e�B�u��`�悷��(���_�C���f�b�N�X�g�p)
extern	int			NS_DrawPrimitiveIndexed3D(                  const VERTEX3D  *Vertex, int VertexNum, const unsigned short *Indices, int IndexNum,   int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �R�c�v���~�e�B�u��`�悷��(���_�C���f�b�N�X�g�p)
extern	int			NS_DrawPrimitive32bitIndexed3D(             const VERTEX3D  *VertexArray, int VertexNum, const unsigned int   *IndexArray, int IndexNum,   int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �R�c�v���~�e�B�u��`�悷��(���_�C���f�b�N�X�g�p)

extern	int			NS_DrawPolygon3D_UseVertexBuffer(           int VertexBufHandle,                                                                                                                                                               int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@���g�p���ĂR�c�|���S����`�悷��
extern	int			NS_DrawPrimitive3D_UseVertexBuffer(         int VertexBufHandle,                     int PrimitiveType  /* DX_PRIMTYPE_TRIANGLELIST �� */,                                                                                     int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@���g�p���ĂR�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitive3D_UseVertexBuffer2(        int VertexBufHandle,                     int PrimitiveType  /* DX_PRIMTYPE_TRIANGLELIST �� */,                 int StartVertex, int UseVertexNum,                                  int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@���g�p���ĂR�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPolygonIndexed3D_UseVertexBuffer(    int VertexBufHandle, int IndexBufHandle,                                                                                                                                           int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���g�p���ĂR�c�|���S����`�悷��
extern	int			NS_DrawPrimitiveIndexed3D_UseVertexBuffer(  int VertexBufHandle, int IndexBufHandle, int PrimitiveType  /* DX_PRIMTYPE_TRIANGLELIST �� */,                                                                                     int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���g�p���ĂR�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitiveIndexed3D_UseVertexBuffer2( int VertexBufHandle, int IndexBufHandle, int PrimitiveType  /* DX_PRIMTYPE_TRIANGLELIST �� */, int BaseVertex, int StartVertex, int UseVertexNum, int StartIndex, int UseIndexNum, int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���g�p���ĂR�c�v���~�e�B�u��`�悷��

extern	int			NS_DrawGraph3D(                             float x, float y, float z,                                                                     int GrHandle, int TransFlag ) ;								// �O���t�B�b�N�̂R�c�`��
extern	int			NS_DrawExtendGraph3D(                       float x, float y, float z, double ExRateX, double ExRateY,                                     int GrHandle, int TransFlag ) ;								// �O���t�B�b�N�̊g��R�c�`��
extern	int			NS_DrawRotaGraph3D(                         float x, float y, float z, double ExRate, double Angle,                                        int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;		// �O���t�B�b�N�̉�]�R�c�`��
extern	int			NS_DrawRota2Graph3D(                        float x, float y, float z, float cx, float cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;		// �O���t�B�b�N�̉�]�R�c�`��(��]���S�w��^)
extern	int			NS_DrawModiBillboard3D(                     VECTOR Pos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,    int GrHandle, int TransFlag ) ;								// �O���t�B�b�N�̎��R�ό`�R�c�`��
extern	int			NS_DrawBillboard3D(                         VECTOR Pos, float cx, float cy, float Size, float Angle,                                       int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;		// �R�c��ԏ�ɃO���t�B�b�N��`��


// �`��ݒ�֌W�֐�
extern	int			NS_SetDrawMode(						int DrawMode ) ;												// �`�惂�[�h���Z�b�g����
extern	int			NS_GetDrawMode(						void ) ;														// �`�惂�[�h���擾����
extern	int			NS_SetDrawBlendMode(					int BlendMode, int BlendParam ) ;								// �`��u�����h���[�h���Z�b�g����
extern	int			NS_GetDrawBlendMode(					int *BlendMode, int *BlendParam ) ;								// �`��u�����h���[�h���擾����
extern	int			NS_SetDrawCustomBlendMode(				int BlendEnable, int SrcBlendRGB /* DX_BLEND_SRC_COLOR �� */, int DestBlendRGB /* DX_BLEND_SRC_COLOR �� */, int BlendOpRGB /* DX_BLENDOP_ADD �� */, int SrcBlendA /* DX_BLEND_SRC_COLOR �� */, int DestBlendA /* DX_BLEND_SRC_COLOR �� */, int BlendOpA /* DX_BLENDOP_ADD �� */, int BlendParam ) ;		// �J�X�^���u�����h���[�h��ݒ肷��
extern	int			NS_GetDrawCustomBlendMode(				int *BlendEnable, int *SrcBlendRGB, int *DestBlendRGB, int *BlendOpRGB, int *SrcBlendA, int *DestBlendA, int *BlendOpA, int *BlendParam ) ;																																								// �J�X�^���u�����h���[�h���擾����
extern	int			NS_SetDrawAlphaTest(					int TestMode, int TestParam ) ;									// �`�掞�̃A���t�@�e�X�g�̐ݒ���s��( TestMode:DX_CMP_GREATER��( -1:�f�t�H���g����ɖ߂� )  TestParam:�`��A���t�@�l�Ƃ̔�r�Ɏg�p����l )
extern	int			NS_GetDrawAlphaTest(					int *TestMode, int *TestParam ) ;								// �`�掞�̃A���t�@�e�X�g�̐ݒ���擾����( TestMode:�e�X�g���[�h( DX_CMP_GREATER�� -1�Ńf�t�H���g����ɖ߂� )  TestParam:�`��A���t�@�l�Ƃ̔�r�Ɏg�p����l( 0�`255 ) )
extern	int			NS_SetBlendGraph(						int BlendGraph, int BorderParam, int BorderRange ) ;			// ( SetBlendGraphParam �� BlendType = DX_BLENDGRAPHTYPE_WIPE �̏������s�����֐� )�`�揈�����ɕ`�悷��摜�ƃu�����h���郿�`�����l���t���摜���Z�b�g����( BlendGraph �� -1 �Ńu�����h�@�\�𖳌� )
extern	int			NS_SetBlendGraphParam(					int BlendGraph, int BlendType, ... ) ;							// �`�揈�����ɕ`�悷��摜�ƃu�����h����摜�̃u�����h�ݒ���s���ABlendGraph �� -1 �ɂ���ΐݒ�������A���̏ꍇ BlendType �Ƃ��̌��̃p�����[�^�͖��������
//		int			NS_SetBlendGraphParam(					int BlendGraph, int BlendType = DX_BLENDGRAPHTYPE_NORMAL, int Ratio = ( 0( �u�����h���O�� )�`255( �u�����h���P�O�O�� ) ) ) ;
//		int			NS_SetBlendGraphParam(					int BlendGraph, int BlendType = DX_BLENDGRAPHTYPE_WIPE, int BorderParam, int BorderRange ) ;
extern	int			NS_SetBlendGraphPosition(				int x, int y ) ;												// �u�����h�摜�̋N�_���W���Z�b�g����
extern	int			NS_SetBlendGraphPositionMode(			int BlendGraphPositionMode /* DX_BLENDGRAPH_POSMODE_DRAWGRAPH �Ȃ� */ ) ;	// �u�����h�摜�̓K�����W���[�h��ݒ肷��
extern	int			NS_SetDrawBright(						int RedBright, int GreenBright, int BlueBright ) ;				// �`��P�x���Z�b�g
extern	int			NS_GetDrawBright(						int *Red, int *Green, int *Blue ) ;								// �`��P�x���擾����
extern	int			NS_SetDrawAddColor(					int Red, int Green, int Blue ) ;								// �`��J���[�ɉ��Z����F��ݒ肷��
extern	int			NS_GetDrawAddColor(					int *Red, int *Green, int *Blue ) ;								// �`��J���[�ɉ��Z����F���擾����
extern	int			NS_SetWriteAlphaChannelFlag(			int Flag ) ;													// �`���̃A���t�@�`�����l���̓��e�����������邩��ݒ肷��( FALSE:���������Ȃ�  TRUE:����������( �f�t�H���g ) )
extern	int			NS_GetWriteAlphaChannelFlag(			void ) ;														// �`���̃A���t�@�`�����l���̓��e�����������邩���擾����( FALSE:���������Ȃ�  TRUE:����������( �f�t�H���g ) )
extern	int			NS_CheckSeparateAlphaBlendEnable(		void ) ;														// �`���̃A���t�@�`�����l���̓��e�����������Ȃ����Ƃ��ł��邩�ǂ������擾����( TRUE:���������Ȃ����Ƃ��ł���  FALSE:���������Ȃ����Ƃ��ł��Ȃ� )
extern	int			NS_SetIgnoreDrawGraphColor(			int EnableFlag ) ;												// �`�悷��摜�̐F�����𖳎����邩�ǂ������w�肷��( EnableFlag:���̋@�\���g�����ǂ���( TRUE:�g��  FALSE:�g��Ȃ� ) )
extern	int			NS_GetIgnoreDrawGraphColor(			void ) ;														// �`�悷��摜�̂q�f�a�����𖳎����邩�ǂ������擾����( �߂�l  ���̋@�\���g�����ǂ���( TRUE:�g��  FALSE:�g��Ȃ� )
extern	int			NS_SetMaxAnisotropy(					int MaxAnisotropy ) ;											// �ő�ٕ����̒l���Z�b�g����
extern	int			NS_GetMaxAnisotropy(					void ) ;														// �ő�ٕ����l���擾����
extern	int			NS_SetUseLarge3DPositionSupport(		int UseFlag ) ;													// �R�c�����Ŏg�p������W�l�� 10000000.0f �Ȃǂ̑傫�Ȓl�ɂȂ��Ă��`��̕�����������}���鏈�����g�p���邩�ǂ�����ݒ肷��ADxLib_Init �̌Ăяo���O�ł̂ݎg�p�\( TRUE:�`��̕����}���鏈�����g�p����( CPU���ׂ��オ��܂� )�@�@FALSE:�`��̕����}���鏈���͎g�p���Ȃ�( �f�t�H���g ) )

extern	int			NS_SetUseZBufferFlag(					int Flag ) ;													// �y�o�b�t�@��L���ɂ��邩�A�t���O���Z�b�g����( �Q�c�ƂR�c�`��ɉe�� )
extern	int			NS_SetWriteZBufferFlag(				int Flag ) ;													// �y�o�b�t�@�ɏ������݂��s�����A�t���O���Z�b�g����( �Q�c�ƂR�c�`��ɉe�� )
extern	int			NS_SetZBufferCmpType(					int CmpType /* DX_CMP_NEVER �� */ ) ;							// �y�l�̔�r���[�h���Z�b�g����( �Q�c�ƂR�c�`��ɉe�� )
extern	int			NS_SetZBias(							int Bias ) ;													// �y�o�C�A�X���Z�b�g����( �Q�c�ƂR�c�`��ɉe�� )
extern	int			NS_SetUseZBuffer3D(					int Flag ) ;													// �y�o�b�t�@��L���ɂ��邩�A�t���O���Z�b�g����( �R�c�}�`�`��݂̂ɉe�� )
extern	int			NS_SetWriteZBuffer3D(					int Flag ) ;													// �y�o�b�t�@�ɏ������݂��s�����A�t���O���Z�b�g����( �R�c�}�`�`��݂̂ɉe�� )
extern	int			NS_SetZBufferCmpType3D(				int CmpType /* DX_CMP_NEVER �� */ ) ;							// �y�l�̔�r���[�h���Z�b�g����( �R�c�}�`�`��݂̂ɉe�� )
extern	int			NS_SetZBias3D(							int Bias ) ;													// �y�o�C�A�X���Z�b�g����( �R�c�}�`�`��݂̂ɉe�� )
extern	int			NS_SetDrawZ(							float Z ) ;														// �Q�c�`�掞�ɂy�o�b�t�@�ɏ������ނy�l��ύX����

extern	int			NS_SetDrawArea(						int x1, int y1, int x2, int y2 ) ;								// �`��\�̈�̃Z�b�g
extern	int			NS_GetDrawArea(						RECT *Rect ) ;													// �`��\�̈�𓾂�
extern	int			NS_SetDraw3DScale(						float Scale ) ;													// �R�c�`��̃X�P�[�����Z�b�g����
extern	int			NS_SetDrawAreaFull(					void ) ;														// �`��\�̈��`��Ώۉ�ʑS�̂ɂ���

extern	int			NS_SetRestoreShredPoint(				void (* ShredPoint )( void ) ) ;								// SetRestoreGraphCallback �̋���
extern	int			NS_SetRestoreGraphCallback(			void (* Callback )( void ) ) ;									// �O���t�B�b�N�n���h�������֐��̓o�^
extern	int			NS_RunRestoreShred(					void ) ;														// �O���t�B�b�N�����֐��̎��s
extern	int			NS_SetGraphicsDeviceRestoreCallbackFunction( void (* Callback )( void *Data ), void *CallbackData ) ;	// �O���t�B�b�N�X�f�o�C�X�����X�g���畜�A�����ۂɌĂ΂��R�[���o�b�N�֐���ݒ肷��
extern	int			NS_SetGraphicsDeviceLostCallbackFunction(    void (* Callback )( void *Data ), void *CallbackData ) ;	// �O���t�B�b�N�X�f�o�C�X�����X�g���畜�A����O�ɌĂ΂��R�[���o�b�N�֐���ݒ肷��

extern	int			NS_SetTransformTo2D(					const MATRIX   *Matrix ) ;										// �Q�c�`��Ɏg�p�����ϊ��s���ݒ肷��( �g�p�����̂�3�s2��̂� )
extern	int			NS_SetTransformTo2DD(					const MATRIX_D *Matrix ) ;										// �Q�c�`��Ɏg�p�����ϊ��s���ݒ肷��( �g�p�����̂�3�s2��̂� )
extern	int			NS_ResetTransformTo2D(					void ) ;														// �Q�c�`��p�Ɏg�p����ϊ��s��̐ݒ��������Ԃɖ߂�
extern	int			NS_SetTransformToWorld(					const MATRIX   *Matrix ) ;										// ���[�J�����W���烏�[���h���W�ɕϊ����邽�߂̍s���ݒ肷��
extern	int			NS_SetTransformToWorldD(				const MATRIX_D *Matrix ) ;										// ���[�J�����W���烏�[���h���W�ɕϊ����邽�߂̍s���ݒ肷��
extern	int			NS_GetTransformToWorldMatrix(			      MATRIX   *MatBuf ) ;										// ���[�J�����W���烏�[���h���W�ɕϊ����邽�߂̍s����擾����
extern	int			NS_GetTransformToWorldMatrixD(			      MATRIX_D *MatBuf ) ;										// ���[�J�����W���烏�[���h���W�ɕϊ����邽�߂̍s����擾����
extern	int			NS_SetTransformToView(					const MATRIX   *Matrix ) ;										// ���[���h���W����r���[���W�ɕϊ����邽�߂̍s���ݒ肷��
extern	int			NS_SetTransformToViewD(					const MATRIX_D *Matrix ) ;										// ���[���h���W����r���[���W�ɕϊ����邽�߂̍s���ݒ肷��
extern	int			NS_GetTransformToViewMatrix(			      MATRIX   *MatBuf ) ;										// ���[���h���W����r���[���W�ɕϊ����邽�߂̍s����擾����
extern	int			NS_GetTransformToViewMatrixD(			      MATRIX_D *MatBuf ) ;										// ���[���h���W����r���[���W�ɕϊ����邽�߂̍s����擾����
extern	int			NS_SetTransformToProjection(			const MATRIX   *Matrix ) ;										// �r���[���W����v���W�F�N�V�������W�ɕϊ����邽�߂̍s���ݒ肷��
extern	int			NS_SetTransformToProjectionD(			const MATRIX_D *Matrix ) ;										// �r���[���W����v���W�F�N�V�������W�ɕϊ����邽�߂̍s���ݒ肷��
extern	int			NS_GetTransformToProjectionMatrix(		      MATRIX   *MatBuf ) ;										// �r���[���W����v���W�F�N�V�������W�ɕϊ����邽�߂̍s����擾����
extern	int			NS_GetTransformToProjectionMatrixD(			  MATRIX_D *MatBuf ) ;										// �r���[���W����v���W�F�N�V�������W�ɕϊ����邽�߂̍s����擾����
extern	int			NS_SetTransformToViewport(				const MATRIX   *Matrix ) ;										// �r���[�|�[�g�s���ݒ肷��
extern	int			NS_SetTransformToViewportD(				const MATRIX_D *Matrix ) ;										// �r���[�|�[�g�s���ݒ肷��
extern	int			NS_GetTransformToViewportMatrix(	    MATRIX   *MatBuf ) ;											// �r���[�|�[�g�s����擾����
extern	int			NS_GetTransformToViewportMatrixD(	    MATRIX_D *MatBuf ) ;											// �r���[�|�[�g�s����擾����
extern	int			NS_GetTransformToAPIViewportMatrix(		MATRIX   *MatBuf ) ;											// Direct3D�Ŏ����K�p�����r���[�|�[�g�s����擾����
extern	int			NS_GetTransformToAPIViewportMatrixD(	MATRIX_D *MatBuf ) ;											// Direct3D�Ŏ����K�p�����r���[�|�[�g�s����擾����
extern	int			NS_SetDefTransformMatrix(				void ) ;														// �f�t�H���g�̕ϊ��s���ݒ肷��
extern	int			NS_GetTransformPosition(				VECTOR   *LocalPos, float  *x, float  *y ) ;					// ���[�J�����W����X�N���[�����W���擾����
extern	int			NS_GetTransformPositionD(				VECTOR_D *LocalPos, double *x, double *y ) ;					// ���[�J�����W����X�N���[�����W���擾����
extern	float		NS_GetBillboardPixelSize(				VECTOR   WorldPos, float  WorldSize ) ;							// ���[���h��ԏ�̃r���{�[�h�̃T�C�Y����X�N���[���ɓ��e�����ꍇ�̃s�N�Z���P�ʂ̃T�C�Y���擾����
extern	double		NS_GetBillboardPixelSizeD(				VECTOR_D WorldPos, double WorldSize ) ;							// ���[���h��ԏ�̃r���{�[�h�̃T�C�Y����X�N���[���ɓ��e�����ꍇ�̃s�N�Z���P�ʂ̃T�C�Y���擾����
extern	VECTOR		NS_ConvWorldPosToViewPos(				VECTOR   WorldPos ) ;											// ���[���h���W���r���[���W�ɕϊ�����
extern	VECTOR_D	NS_ConvWorldPosToViewPosD(				VECTOR_D WorldPos ) ;											// ���[���h���W���r���[���W�ɕϊ�����
extern	VECTOR		NS_ConvWorldPosToScreenPos(				VECTOR   WorldPos ) ;											// ���[���h���W���X�N���[�����W�ɕϊ�����
extern	VECTOR_D	NS_ConvWorldPosToScreenPosD(			VECTOR_D WorldPos ) ;											// ���[���h���W���X�N���[�����W�ɕϊ�����
extern	FLOAT4		NS_ConvWorldPosToScreenPosPlusW(		VECTOR   WorldPos ) ;											// ���[���h���W���X�N���[�����W�ɕϊ�����A�Ō�̂w�x�y���W���v�Ŋ���O�̒l�𓾂�
extern	DOUBLE4		NS_ConvWorldPosToScreenPosPlusWD(		VECTOR_D WorldPos ) ;											// ���[���h���W���X�N���[�����W�ɕϊ�����A�Ō�̂w�x�y���W���v�Ŋ���O�̒l�𓾂�
extern	VECTOR		NS_ConvScreenPosToWorldPos(				VECTOR   ScreenPos ) ;											// �X�N���[�����W�����[���h���W�ɕϊ�����
extern	VECTOR_D	NS_ConvScreenPosToWorldPosD(			VECTOR_D ScreenPos ) ;											// �X�N���[�����W�����[���h���W�ɕϊ�����
extern	VECTOR		NS_ConvScreenPosToWorldPos_ZLinear(		VECTOR   ScreenPos ) ;											// �X�N���[�����W�����[���h���W�ɕϊ�����( Z���W�����` )
extern	VECTOR_D	NS_ConvScreenPosToWorldPos_ZLinearD(	VECTOR_D ScreenPos ) ;											// �X�N���[�����W�����[���h���W�ɕϊ�����( Z���W�����` )

extern	int			NS_SetUseCullingFlag(					int Flag ) ;													// SetUseBackCulling �̋�����
extern	int			NS_SetUseBackCulling(					int Flag /* DX_CULLING_LEFT �� */ ) ;							// �|���S���J�����O�̗L���A�������Z�b�g����
extern	int			NS_GetUseBackCulling(					void ) ;														// �|���S���J�����O���[�h���擾����
extern	int			NS_SetUseRightHandClippingProcess(		int Flag ) ;													// �E����W�n�̃N���b�s���O�������s������ݒ肷��( TRUE:�E����W�n�̃N���b�s���O�������s��  FALSE:������W�n�̃N���b�s���O�������s��( �f�t�H���g ) )
extern	int			NS_GetUseRightHandClippingProcess(		void ) ;														// �E����W�n�̃N���b�s���O�������s�������擾����( TRUE:�E����W�n�̃N���b�s���O�������s��  FALSE:������W�n�̃N���b�s���O�������s��( �f�t�H���g ) )

extern	int			NS_SetTextureAddressMode(				int Mode /* DX_TEXADDRESS_WRAP �� */ , int Stage = -1 ) ;		// �e�N�X�`���A�h���X���[�h��ݒ肷��
extern	int			NS_SetTextureAddressModeUV(			int ModeU, int ModeV, int Stage = -1 ) ;						// �e�N�X�`���A�h���X���[�h��ݒ肷��
extern	int			NS_SetTextureAddressTransform(			float TransU, float TransV, float ScaleU, float ScaleV, float RotCenterU, float RotCenterV, float Rotate ) ;	// �e�N�X�`�����W�ϊ��p�����[�^���Z�b�g����
extern	int			NS_SetTextureAddressTransformMatrix(	MATRIX Matrix ) ;												// �e�N�X�`�����W�ϊ��s����Z�b�g����
extern	int			NS_ResetTextureAddressTransform(		void ) ;														// �e�N�X�`�����W�ϊ��p�����[�^�����Z�b�g����

extern	int			NS_SetFogEnable(						int Flag ) ;													// �t�H�O��L���ɂ��邩�ǂ�����ݒ肷��( TRUE:�L��  FALSE:���� )
extern	int			NS_GetFogEnable(						void ) ;														// �t�H�O���L�����ǂ������擾����( TRUE:�L��  FALSE:���� )
extern	int			NS_SetFogMode(							int Mode /* DX_FOGMODE_NONE �� */ ) ;							// �t�H�O���[�h��ݒ肷��
extern	int			NS_GetFogMode(							void ) ;														// �t�H�O���[�h���擾����
extern	int			NS_SetFogColor(						int  r, int  g, int  b ) ;										// �t�H�O�J���[��ݒ肷��
extern	int			NS_GetFogColor(						int *r, int *g, int *b ) ;										// �t�H�O�J���[���擾����
extern	int			NS_SetFogStartEnd(						float  start, float  end ) ;									// �t�H�O���n�܂鋗���ƏI�����鋗����ݒ肷��( 0.0f �` 1.0f )
extern	int			NS_GetFogStartEnd(						float *start, float *end ) ;									// �t�H�O���n�܂鋗���ƏI�����鋗�����擾����( 0.0f �` 1.0f )
extern	int			NS_SetFogDensity(						float density ) ;												// �t�H�O�̖��x��ݒ肷��( 0.0f �` 1.0f )
extern	float		NS_GetFogDensity(						void ) ;														// �t�H�O�̖��x���擾����( 0.0f �` 1.0f )


// ��ʊ֌W�֐�
#ifndef DX_COMPILE_TYPE_C_LANGUAGE
extern	unsigned int	NS_GetPixel(									int x, int y ) ;																// �w����W�̐F���擾����
#endif // DX_COMPILE_TYPE_C_LANGUAGE
extern	unsigned int	NS_GetPixelDX(									int x, int y ) ;																// �w����W�̐F���擾����
extern	COLOR_F			NS_GetPixelF(									int x, int y ) ;																// �w����W�̐F���擾����( float�^ )
extern	int				NS_SetBackgroundColor(							int Red, int Green, int Blue, int Alpha ) ;													// ���C���E�C���h�E�̃o�b�N�O���E���h�J���[��ݒ肷��
extern	int				NS_GetBackgroundColor(							int *Red, int *Green, int *Blue, int *Alpha ) ;												// ���C���E�C���h�E�̔w�i�F���擾����( Red,Green,Blue:���ꂼ�� �O�`�Q�T�T )
extern	int				NS_GetDrawScreenGraph(							                             int x1, int y1, int x2, int y2,                       int GrHandle, int UseClientFlag = TRUE ) ;	// �`���̉�ʂ���w��̈�̉摜�����O���t�B�b�N�n���h���ɓ]������
extern	int				NS_BltDrawValidGraph(							int TargetDrawValidGrHandle, int x1, int y1, int x2, int y2, int DestX, int DestY, int DestGrHandle ) ;							// �`��\�O���t�B�b�N�n���h������w��̈�̉摜�����O���t�B�b�N�n���h���ɓ]������
extern	int				NS_ScreenFlip(									void ) ;																		// ����ʂƕ\��ʂ̓��e����������
extern 	int				NS_ScreenCopy(									void ) ;																		// ����ʂ̓��e��\��ʂɓ]������
extern	int				NS_WaitVSync(									int SyncNum ) ;																	// ���������M����҂�
extern	int				NS_ClearDrawScreen(					        const RECT *ClearRect = NULL ) ;														// ��ʂ̏�Ԃ�����������
extern	int				NS_ClearDrawScreenZBuffer(						const RECT *ClearRect = NULL ) ;														// ��ʂ̂y�o�b�t�@�̏�Ԃ�����������
extern	int				NS_ClsDrawScreen(								void ) ;																		// ��ʂ̏�Ԃ�����������(ClearDrawScreen�̋�����)
extern	int				NS_SetDrawScreen(								int DrawScreen ) ;																// �`����ʂ̃Z�b�g
extern	int				NS_GetDrawScreen(								void ) ;																		// �`����ʂ̎擾
extern	int				NS_GetActiveGraph(								void ) ;																		// GetDrawScreen �̋�����
extern	int				NS_SetUseSetDrawScreenSettingReset(			int UseFlag ) ;																	// SetDrawScreen �����s�����ۂɃJ������`��͈͂̐ݒ�����Z�b�g���邩��ݒ肷��( UseFlag  TRUE:���Z�b�g����( �f�t�H���g )  FALSE:���Z�b�g���Ȃ� )
extern	int				NS_GetUseSetDrawScreenSettingReset(			void ) ;																		// SetDrawScreen �����s�����ۂɃJ������`��͈͂̐ݒ�����Z�b�g���邩���擾����
extern	int				NS_SetDrawZBuffer(								int DrawScreen ) ;																// �`���y�o�b�t�@�̃Z�b�g( DrawScreen �t���̂y�o�b�t�@��`���y�o�b�t�@�ɂ���ADrawScreen �� -1 �ɂ���ƃf�t�H���g�̕`���y�o�b�t�@�ɖ߂� )
#ifdef WINDOWS_DESKTOP_OS
extern	int				NS_BltBackScreenToWindow(						HWND Window, int ClientX, int ClientY ) ;										// ����ʂ̓��e���w��̃E�C���h�E�ɓ]������
extern	int				NS_BltRectBackScreenToWindow(					HWND Window, RECT BackScreenRect, RECT WindowClientRect ) ;						// ����ʂ̎w��̗̈���E�C���h�E�̃N���C�A���g�̈�̎w��̗̈�ɓ]������
extern	int				NS_SetScreenFlipTargetWindow(					HWND TargetWindow, double ScaleX, double ScaleY ) ;								// ScreenFlip �ŉ摜��]�������̃E�C���h�E��ݒ肷��( NULL ���w�肷��Ɛݒ���� )
extern	int				NS_GetDesktopScreenGraph(			int x1, int y1, int x2, int y2, int GrHandle, int DestX = 0 , int DestY = 0 ) ;				// �f�X�N�g�b�v��ʂ���w��̈�̉摜�����O���t�B�b�N�n���h���ɓ]������
extern	void *			NS_GetDesktopScreenGraphMemImage(	int x1, int y1, int x2, int y2, int *Width, int *Height, int *Stride, int ColorBitDepth = 32 ) ;	// �f�X�N�g�b�v��ʂ���w��̈�̉摜�̃������C���[�W�̐擪�A�h���X�ƃC���[�W�̕��E�����E�X�g���C�h���擾����( �C���[�W�̃t�H�[�}�b�g�� ColorBitDepth = 32( �o�C�g���� B8G8R8X8 �� 32bit�J���[ ) ColorBitDepth = 24( �o�C�g���� B8G8R8 �� 24bit�J���[ ) )
extern	int				NS_GetOtherWindowGraph(				HWND Window, int x1, int y1, int x2, int y2, int GrHandle, int DestX DEFAULTPARAM( = 0 ) , int DestY DEFAULTPARAM( = 0 ) ) ;		// �w��̃E�B���h�E�̎w��̈�̉摜�����O���t�B�b�N�n���h���ɓ]������
#endif // WINDOWS_DESKTOP_OS
extern	int				NS_SetGraphMode(								int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int RefreshRate = 60 ) ;	// ��ʃ��[�h��ݒ肷��
extern	int				NS_SetUserScreenImage(							void *Image, int PixelFormat /* DX_USER_SCREEN_PIXEL_FORMAT_R5G6B5 �� */ ) ;	// ��ʂ̃������C���[�W���Z�b�g����( DxLib_Init �̑O�ŌĂԕK�v������( DxLib_Init �̑O�Ɉ�x�ł��Ă�ł���΁ADxLib_Init ��� Image �̃A�h���X�݂̂̕ύX�ړI�ŌĂԂ��Ƃ͉\ )�APixelFormat �� DX_USER_SCREEN_PIXEL_FORMAT_R5G6B5 ���� DX_USER_SCREEN_PIXEL_FORMAT_X8R8G8B8 �̓�ȊO���w�肵���ꍇ�͂c�w���C�u�����̕`��֐��͈�؎g�p�ł��Ȃ��Ȃ�܂� )
extern	int				NS_SetFullScreenResolutionMode(					int ResolutionMode /* DX_FSRESOLUTIONMODE_NATIVE �� */ ) ;						// �t���X�N���[���𑜓x���[�h��ݒ肷��
extern	int				NS_GetFullScreenResolutionMode(				int *ResolutionMode, int *UseResolutionMode ) ;									// �t���X�N���[���𑜓x���[�h���擾����( UseResolutionMode �͎��ۂɎg�p����Ă���𑜓x���[�h( �Ⴆ�� DX_FSRESOLUTIONMODE_NATIVE ���w�肵�Ă��Ă����j�^���w��̉𑜓x�ɑΉ����Ă��Ȃ��ꍇ�� UseResolutionMode �� DX_FSRESOLUTIONMODE_DESKTOP �� DX_FSRESOLUTIONMODE_MAXIMUM �ɂȂ�܂� ) )
extern	int				NS_GetUseFullScreenResolutionMode(				void ) ;																		// �t���X�N���[���𑜓x���[�h���擾����( GetFullScreenResolutionMode �� UseResolutionMode �Ŏ擾�ł���l��Ԃ��֐� )
extern	int				NS_SetFullScreenScalingMode(					int ScalingMode /* DX_FSSCALINGMODE_NEAREST �� */ , int FitScaling = FALSE ) ;	// �t���X�N���[�����[�h���̉�ʊg�僂�[�h��ݒ肷��
extern	int				NS_SetEmulation320x240(						int Flag ) ;																	// �U�S�O���S�W�O�̉�ʂłR�Q�O���Q�S�O�̉�ʉ𑜓x�ɂ��邩�ǂ����̃t���O���Z�b�g����A�U�S�O���S�W�O�ȊO�̉𑜓x�ł͖���( TRUE:�L��  FALSE:���� )
extern	int				NS_SetZBufferSize(								int ZBufferSizeX, int ZBufferSizeY ) ;											// ��ʗp�̂y�o�b�t�@�̃T�C�Y��ݒ肷��
extern	int				NS_SetZBufferBitDepth(							int BitDepth ) ;																// ��ʗp�̂y�o�b�t�@�̃r�b�g�[�x��ݒ肷��( 16 or 24 or 32 )
extern	int				NS_SetWaitVSyncFlag(							int Flag ) ;																	// �u�r�x�m�b�҂������邩�̃t���O�Z�b�g
extern	int				NS_GetWaitVSyncFlag(							void ) ;																		// �u�r�x�m�b�҂�������ݒ�ɂȂ��Ă��邩�ǂ������擾����
extern	int				NS_SetFullSceneAntiAliasingMode(				int Samples, int Quality ) ;													// ��ʂ̃t���X�N���[���A���`�G�C���A�X���[�h�̐ݒ������( DxLib_Init �̑O�ł̂ݎg�p�\ )
extern	int				NS_SetGraphDisplayArea(						int x1, int y1, int x2, int y2 ) ;												// ScreenFlip ���ɕ\��ʑS�̂ɓ]�����闠��ʂ̗̈��ݒ肷��( DxLib_Init �̑O�ł̂ݎg�p�\ )
extern	int				NS_SetChangeScreenModeGraphicsSystemResetFlag(	int Flag ) ;																	// ��ʃ��[�h�ύX��( �ƃE�C���h�E���[�h�ύX�� )�ɃO���t�B�b�N�X�V�X�e���̐ݒ��O���t�B�b�N�n���h�������Z�b�g���邩�ǂ�����ݒ肷��( TRUE:���Z�b�g����  FALSE:���Z�b�g���Ȃ� )
extern	int				NS_GetScreenState(								int *SizeX, int *SizeY, int *ColorBitDepth ) ;									// ���݂̉�ʂ̑傫���ƃJ���[�r�b�g���𓾂� 
extern	int				NS_GetDrawScreenSize(							int *XBuf, int *YBuf ) ;														// �`��T�C�Y���擾����
extern	int				NS_GetScreenBitDepth(							void ) ;																		// �g�p�F�r�b�g����Ԃ�
extern	int				NS_GetColorBitDepth(							void ) ;																		// ��ʂ̐F�r�b�g�[�x�𓾂�
extern	int				NS_GetChangeDisplayFlag(						void ) ;																		// ��ʃ��[�h���ύX����Ă��邩�ǂ����̃t���O���擾����
extern	int				NS_GetVideoMemorySize(							int *AllSize, int *FreeSize ) ;													// �r�f�I�������̗e�ʂ𓾂�
extern	int				NS_GetVideoMemorySizeEx(						ULONGLONG *TotalSize, ULONGLONG *UseSize ) ;									// �r�f�I�������̗e�ʂ𓾂�( 64bit�� )
extern	int				NS_GetRefreshRate(								void ) ;																		// ���݂̉�ʂ̃��t���b�V�����[�g���擾����
extern	int				NS_GetDisplayNum(								void ) ;																		// �f�B�X�v���C�̐����擾
extern	int				NS_GetDisplayInfo(								int DisplayIndex, int *DesktopRectX, int *DesktopRectY, int *DesktopSizeX, int *DesktopSizeY, int *IsPrimary, int *DesktopRefreshRate ) ;	// �f�B�X�v���C�̃f�X�N�g�b�v��ł̋�`�ʒu���擾����
extern	int				NS_GetDisplayModeNum(							int DisplayIndex = 0 ) ;														// �ύX�\�ȃf�B�X�v���C���[�h�̐����擾����
extern	DISPLAYMODEDATA	NS_GetDisplayMode(								int ModeIndex, int DisplayIndex = 0 ) ;											// �ύX�\�ȃf�B�X�v���C���[�h�̏����擾����( ModeIndex �� 0 �` GetDisplayModeNum �̖߂�l-1 )
extern	DISPLAYMODEDATA	NS_GetFullScreenUseDisplayMode(				void ) ;																		// �t���X�N���[�����[�h�ŋN�����Ă���ꍇ�̎g�p���Ă���f�B�X�v���C���[�h�̏����擾����
extern	int				NS_GetDisplayMaxResolution(					int *SizeX, int *SizeY, int DisplayIndex = 0 ) ;								// �f�B�X�v���C�̍ő�𑜓x���擾����
extern	const COLORDATA* NS_GetDispColorData(							void ) ;																		// �f�B�X�v���[�̃J���[�f�[�^�|�C���^�𓾂�
extern	int				NS_GetMultiDrawScreenNum(						void ) ;																		// �����ɕ`����s�����Ƃ��ł����ʂ̐����擾����
extern	int				NS_GetDrawFloatCoordType(						void ) ;																		// DrawGraphF ���̕��������_�l�ō��W���w�肷��֐��ɂ�������W�^�C�v���擾����( �߂�l : DX_DRAWFLOATCOORDTYPE_DIRECT3D9 �Ȃ� )

// ���̑��ݒ�֌W�֐�
extern	int			NS_SetUseNormalDrawShader(						int Flag ) ;									// �ʏ�`��Ƀv���O���}�u���V�F�[�_�[���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����( �f�t�H���g )  FALSE:�g�p���Ȃ� )
extern	int			NS_SetUseSoftwareRenderModeFlag(				int Flag ) ;									// �\�t�g�E�G�A�����_�����O���[�h���g�p���邩�ǂ������Z�b�g����
extern	int			NS_SetNotUse3DFlag(							int Flag ) ;									// ( �����ʂ�SetUseSoftwareRenderModeFlag ���g�p���ĉ����� )�R�c�@�\���g��Ȃ��t���O�̃Z�b�g�A���ʂ� SetUse3DFlag �Ɠ���
extern	int			NS_SetUse3DFlag(								int Flag ) ;									// ( �����ʂ�SetUseSoftwareRenderModeFlag ���g�p���ĉ����� )�R�c�@�\���g�����A�̃t���O���Z�b�g
extern	int			NS_GetUse3DFlag(								void ) ;										// �`��ɂR�c�@�\���g�����t���O���擾
extern	int			NS_SetScreenMemToVramFlag(						int Flag ) ;									// ( �����ʂ�SetUseSoftwareRenderModeFlag ���g�p���ĉ����� )��ʃf�[�^���u�q�`�l�ɒu�����A�t���O
extern	int			NS_GetScreenMemToSystemMemFlag(				void ) ;										// ��ʃO���t�B�b�N�f�[�^���V�X�e���������ɑ��݂��邩�t���O�̎擾

extern	int			NS_SetUseBasicGraphDraw3DDeviceMethodFlag(		int Flag ) ;									// �P���}�`�̕`��ɂR�c�f�o�C�X�̋@�\���g�p���邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetUseDisplayIndex(							int Index ) ;									// �c�w���C�u�����̃E�C���h�E��\������f�B�X�v���C�f�o�C�X��ݒ肷��( -1 ���w�肷��ƃ}�E�X�J�[�\��������f�B�X�v���C�f�o�C�X�ɂc�w���C�u�����̃E�C���h�E��\������ )
extern	int			NS_SetWindowDrawRect(							const RECT *DrawRect ) ;								// �ʏ�g�p���Ȃ�
extern	int			NS_RestoreGraphSystem(							void ) ;										// �c�w���C�u�����̃O���t�B�b�N�֘A�̕��A�������s��
extern	int			NS_SetUseHardwareVertexProcessing(				int Flag ) ;									// �n�[�h�E�G�A�̒��_���Z�����@�\���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetUsePixelLighting(						int Flag ) ;									// �s�N�Z���P�ʂŃ��C�e�B���O���s�����ǂ�����ݒ肷��A�v ShaderModel 3.0( TRUE:�s�N�Z���P�ʂ̃��C�e�B���O���s��  FALSE:���_�P�ʂ̃��C�e�B���O���s��( �f�t�H���g ) )
extern	int			NS_SetUseOldDrawModiGraphCodeFlag(				int Flag ) ;									// �ȑO�� DrawModiGraph �֐��̃R�[�h���g�p���邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetUseVramFlag(								int Flag ) ;									// ( ���݌��ʂȂ� )�u�q�`�l���g�p���邩�̃t���O���Z�b�g����
extern	int			NS_GetUseVramFlag(								void ) ;										// ( ���݌��ʂȂ� )�Q�c�O���t�B�b�N�T�[�t�F�X�쐬���ɃV�X�e���������[���g�p���邩�̃t���O�擾
extern	int			NS_SetBasicBlendFlag(							int Flag ) ;									// ( ���݌��ʂȂ� )�ȗ����u�����h�������s�����ۂ��̃t���O���Z�b�g����
#ifdef WINDOWS_DESKTOP_OS
extern	int			NS_SetMultiThreadFlag(							int Flag ) ;									// DirectDraw �� Direct3D �̋������x�����}���`�X���b�h�Ή��ɂ��邩�ǂ������Z�b�g����
extern	int			NS_SetUseDirectDrawDeviceIndex(				int Index ) ;									// �g�p���� DirectDraw �f�o�C�X�̃C���f�b�N�X��ݒ肷��
extern	int			NS_SetAeroDisableFlag(							int Flag ) ;									// Vista�ȍ~�� Windows Aero �𖳌��ɂ��邩�ǂ������Z�b�g����ATRUE:�����ɂ���  FALSE:�L���ɂ���( DxLib_Init �̑O�ɌĂԕK�v������܂� )
extern	int			NS_SetUseDirect3D9Ex(							int Flag ) ;									// Vista�ȍ~�̊��� Direct3D9Ex ���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����( �f�t�H���g )  FALSE:�g�p���Ȃ� )( DxLib_Init �̑O�ɌĂԕK�v������܂� )
extern	int			NS_SetUseDirect3D11(							int Flag ) ;									// Direct3D11 ���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
extern	int			NS_SetUseDirect3D11MinFeatureLevel(			int Level /* DX_DIRECT3D_11_FEATURE_LEVEL_10_0 �Ȃ� */ ) ;		// Direct3D11 �Ŏg�p����Œ�@�\���x�����w�肷��֐��ł��A���ADX_DIRECT3D_11_FEATURE_LEVEL_11_0 ���Ⴂ�@�\���x���ł̐���ȓ���͕ۏ؂��܂���( �f�t�H���g�� DX_DIRECT3D_11_FEATURE_LEVEL_11_0 )
extern	int			NS_SetUseDirect3D11WARPDriver(						int Flag ) ;									// D3D_DRIVER_TYPE_WARP �^�C�v�� Direct3D 11 �h���C�o���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����  FALSE:�g�p���Ȃ�( �f�t�H���g ) )
extern	int			NS_SetUseDirect3DVersion(						int Version /* DX_DIRECT3D_9 �Ȃ� */ ) ;		// �g�p���� Direct3D �̃o�[�W������ݒ肷��ADxLib_Init �Ăяo���̑O�ł̂ݎg�p�\�@
extern	int			NS_GetUseDirect3DVersion(						void ) ;										// �g�p���Ă��� Direct3D �̃o�[�W�������擾����( DX_DIRECT3D_9 �Ȃ� )
extern	int			NS_GetUseDirect3D11FeatureLevel(				void ) ;										// �g�p���Ă��� Direct3D11 �� FeatureLevel ( DX_DIRECT3D_11_FEATURE_LEVEL_9_1 �� )���擾����( �߂�l�@-1�F�G���[�@-1�ȊO�FFeature Level )
extern	int			NS_SetUseDirect3D11AdapterIndex(					int Index ) ;									// �g�p����O���t�B�b�N�X�f�o�C�X�̃A�_�v�^�[�̃C���f�b�N�X��ݒ肷��
extern	int			NS_SetUseDirect3D11AdapterLUID(					LUID *UseLUID ) ;								// �g�p���� IDXGIAdapter �� LUID ��ݒ肷��
extern	LUID		NS_GetUseDirect3D11AdapterLUID(					void ) ;										// �g�p���� IDXGIAdapter �� LUID ���擾����
extern	int			NS_SetUseDirect3D11BGRASupport(					int Flag ) ;									// D3D11Device �쐬���� D3D11_CREATE_DEVICE_BGRA_SUPPORT ���w�肷�邩�ǂ���( TRUE:�w�肷��  FALSE:�w�肵�Ȃ�( �f�t�H���g ) )
extern	int			NS_GetUseDirect3D11BGRASupport(					void ) ;									// D3D11Device �쐬���� D3D11_CREATE_DEVICE_BGRA_SUPPORT ���w�肷�邩�ǂ������擾����
extern	int			NS_SetUseDirectDrawFlag(						int Flag ) ;									// ( �����ʂ�SetUseSoftwareRenderModeFlag ���g�p���ĉ����� )�c�����������c���������g�p���邩�ǂ������Z�b�g����
extern	int			NS_SetUseGDIFlag(								int Flag ) ;									// �f�c�h�`���K�v�Ƃ��邩�A��ύX����
extern	int			NS_GetUseGDIFlag(								void ) ;										// �f�c�h�`���K�v�Ƃ��邩�̏�Ԃ��擾����
extern	int			NS_SetDDrawUseGuid(							const GUID *Guid ) ;									// �c�����������c���������g�p����f�t�h�c��ݒ肷��
extern	const void*		NS_GetUseDDrawObj(								void ) ;										// ���ݎg�p���Ă���c�����������c�������I�u�W�F�N�g�̃A�h���X���擾����( �߂�l�� IDirectDraw7 * �ɃL���X�g���ĉ����� )
extern	const GUID*		NS_GetDirectDrawDeviceGUID(					int Number ) ;									// �L���� DirectDraw �f�o�C�X�� GUID ���擾����
extern	int			NS_GetDirectDrawDeviceDescription(				int Number, char *StringBuffer ) ;				// �L���� DirectDraw �f�o�C�X�̖��O�𓾂�
extern	int			NS_GetDirectDrawDeviceNum(						void ) ;										// �L���� DirectDraw �f�o�C�X�̐����擾����
extern	const void* NS_GetUseDirect3DDevice9(					void ) ;										// �g�p���̂c�����������R�c�c�����������X�I�u�W�F�N�g�𓾂�
extern	const void* NS_GetUseDirect3D9BackBufferSurface(		void ) ;										// �g�p���̃o�b�N�o�b�t�@��Direct3DSurface9�I�u�W�F�N�g���擾����
extern	const void*	NS_GetUseDirect3D11Device(							void ) ;										// �g�p����ID3D11Device�I�u�W�F�N�g���擾����( �߂�l�� ID3D11Device * �ɃL���X�g���ĉ����� )
extern	const void*	NS_GetUseDirect3D11DeviceContext(					void ) ;										// �g�p����ID3D11DeviceContext�I�u�W�F�N�g���擾����( �߂�l�� ID3D11DeviceContext * �ɃL���X�g���ĉ����� )
extern	const void*	NS_GetUseDirect3D11BackBufferTexture2D(			void ) ;										// �g�p���̃o�b�N�o�b�t�@��ID3D11Texture2D�I�u�W�F�N�g���擾����( �߂�l�� ID3D11Texture2D * �ɃL���X�g���Ă������� )
extern	const void*	NS_GetUseDirect3D11BackBufferRenderTargetView(		void ) ;										// �g�p���̃o�b�N�o�b�t�@��ID3D11RenderTargetView�I�u�W�F�N�g���擾����( �߂�l�� ID3D11RenderTargetView * �ɃL���X�g���Ă������� )
extern	const void*	NS_GetUseDirect3D11DepthStencilTexture2D(			void ) ;										// �g�p���̐[�x�X�e���V���o�b�t�@��ID3D11Texture2D�I�u�W�F�N�g���擾����( �߂�l�� ID3D11Texture2D * �ɃL���X�g���Ă������� )
extern	int			NS_SetDrawScreen_ID3D11RenderTargetView(			const void *pID3D11RenderTargetView, const void *pID3D11DepthStencilView = NULL ) ;		// �w��� ID3D11RenderTargetView ��`��Ώۂɂ���( pID3D11DepthStencilView �� NULL �̏ꍇ�̓f�t�H���g�̐[�x�X�e���V���o�b�t�@���g�p���� )
extern	int			NS_RefreshDxLibDirect3DSetting(				void ) ;										// �c�w���C�u�����̂c�����������R�c�ݒ�����Ȃ���( ����p�r )
#ifndef DX_NON_MEDIA_FOUNDATION
extern	int			NS_SetUseMediaFoundationFlag(						int Flag ) ;									// Media Foundation ���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����( �f�t�H���g )  FALSE:�g�p���Ȃ� )
#endif // DX_NON_MEDIA_FOUNDATION
#endif // WINDOWS_DESKTOP_OS
extern	int			NS_RenderVertex(								void ) ;										// ���_�o�b�t�@�ɗ��܂������_�f�[�^��f���o��( ����p�r )

// �`��p�t�H�[�}���X�֌W�֐�
extern	int			NS_GetDrawCallCount(							void ) ;										// �O�X��� ScreenFlip �Ăяo������A�O��� ScreenFlip �Ăяo���܂ł̊Ԃɍs��ꂽ�`��R�[���̉񐔂��擾����
extern	float		NS_GetFPS(										void ) ;										// �t���[�����[�g( �P�b�ԂɌĂ΂�� ScreenFlip �̉� )���擾����

#ifndef DX_NON_SAVEFUNCTION

// �`����ʕۑ��֐�
// Jpeg_Quality         = 0:��掿�`100:���掿
// Png_CompressionLevel = 0:�����k�`  9:�ō����k
extern	int			NS_SaveDrawScreen(       int x1, int y1, int x2, int y2, const TCHAR *FileName, int SaveType = DX_IMAGESAVETYPE_BMP , int Jpeg_Quality = 80 , int Jpeg_Sample2x1 = TRUE , int Png_CompressionLevel = -1 ) ;		// ���ݕ`��ΏۂɂȂ��Ă����ʂ�ۑ�����
extern	int			NS_SaveDrawScreenWithStrLen(       int x1, int y1, int x2, int y2, const TCHAR *FileName, size_t FileNameLength, int SaveType = DX_IMAGESAVETYPE_BMP , int Jpeg_Quality = 80 , int Jpeg_Sample2x1 = TRUE , int Png_CompressionLevel = -1 ) ;		// ���ݕ`��ΏۂɂȂ��Ă����ʂ��t�@�C���ŕۑ�����
extern	int			NS_SaveDrawScreenToBMP(            int x1, int y1, int x2, int y2, const TCHAR *FileName                        ) ;																																	// ���ݕ`��ΏۂɂȂ��Ă����ʂ��a�l�o�`���ŕۑ�����
extern	int			NS_SaveDrawScreenToBMPWithStrLen(  int x1, int y1, int x2, int y2, const TCHAR *FileName, size_t FileNameLength ) ;																																	// ���ݕ`��ΏۂɂȂ��Ă����ʂ��a�l�o�`���ŕۑ�����
extern	int			NS_SaveDrawScreenToDDS(            int x1, int y1, int x2, int y2, const TCHAR *FileName                        ) ;																																	// ���ݕ`��ΏۂɂȂ��Ă����ʂ��c�c�r�`���ŕۑ�����
extern	int			NS_SaveDrawScreenToDDSWithStrLen(  int x1, int y1, int x2, int y2, const TCHAR *FileName, size_t FileNameLength ) ;																																	// ���ݕ`��ΏۂɂȂ��Ă����ʂ��c�c�r�`���ŕۑ�����
extern	int			NS_SaveDrawScreenToJPEG(           int x1, int y1, int x2, int y2, const TCHAR *FileName,                        int Quality = 80 , int Sample2x1 = TRUE ) ;																						// ���ݕ`��ΏۂɂȂ��Ă����ʂ��i�o�d�f�`���ŕۑ����� Quality = �掿�A�l���傫���قǒሳ�k���掿,0�`100 
extern	int			NS_SaveDrawScreenToJPEGWithStrLen( int x1, int y1, int x2, int y2, const TCHAR *FileName, size_t FileNameLength, int Quality = 80 , int Sample2x1 = TRUE ) ;																						// ���ݕ`��ΏۂɂȂ��Ă����ʂ��i�o�d�f�`���ŕۑ����� Quality = �掿�A�l���傫���قǒሳ�k���掿,0�`100 
extern	int			NS_SaveDrawScreenToPNG(            int x1, int y1, int x2, int y2, const TCHAR *FileName,                        int CompressionLevel = -1 ) ;																										// ���ݕ`��ΏۂɂȂ��Ă����ʂ��o�m�f�`���ŕۑ����� CompressionLevel = ���k���A�l���傫���قǍ����k�������ׁA�O�͖����k,0�`9
extern	int			NS_SaveDrawScreenToPNGWithStrLen(  int x1, int y1, int x2, int y2, const TCHAR *FileName, size_t FileNameLength, int CompressionLevel = -1 ) ;																										// ���ݕ`��ΏۂɂȂ��Ă����ʂ��o�m�f�`���ŕۑ����� CompressionLevel = ���k���A�l���傫���قǍ����k�������ׁA�O�͖����k,0�`9

// �`��Ώۂɂł���O���t�B�b�N�n���h���ۑ��֐�
// Jpeg_Quality         = 0:��掿�`100:���掿
// Png_CompressionLevel = 0:�����k�`  9:�ō����k
extern	int			NS_SaveDrawValidGraph(       int GrHandle, int x1, int y1, int x2, int y2, const TCHAR *FileName, int SaveType = DX_IMAGESAVETYPE_BMP , int Jpeg_Quality = 80 , int Jpeg_Sample2x1 = TRUE , int Png_CompressionLevel = -1 ) ;		// �`��Ώۂɂł���O���t�B�b�N�n���h�����t�@�C���ŕۑ�����
extern	int			NS_SaveDrawValidGraphWithStrLen(       int GrHandle, int x1, int y1, int x2, int y2, const TCHAR *FileName, size_t FileNameLength, int SaveType = DX_IMAGESAVETYPE_BMP , int Jpeg_Quality = 80 , int Jpeg_Sample2x1 = TRUE , int Png_CompressionLevel = -1 ) ;		// �`��Ώۂɂł���O���t�B�b�N�n���h�����t�@�C���ŕۑ�����
extern	int			NS_SaveDrawValidGraphToBMP(            int GrHandle, int x1, int y1, int x2, int y2, const TCHAR *FileName                        ) ;																																// �`��Ώۂɂł���O���t�B�b�N�n���h�����a�l�o�`���ŕۑ�����
extern	int			NS_SaveDrawValidGraphToBMPWithStrLen(  int GrHandle, int x1, int y1, int x2, int y2, const TCHAR *FileName, size_t FileNameLength ) ;																																// �`��Ώۂɂł���O���t�B�b�N�n���h�����a�l�o�`���ŕۑ�����
extern	int			NS_SaveDrawValidGraphToDDS(            int GrHandle, int x1, int y1, int x2, int y2, const TCHAR *FileName                        ) ;																																// �`��Ώۂɂł���O���t�B�b�N�n���h�����c�c�r�`���ŕۑ�����
extern	int			NS_SaveDrawValidGraphToDDSWithStrLen(  int GrHandle, int x1, int y1, int x2, int y2, const TCHAR *FileName, size_t FileNameLength ) ;																																// �`��Ώۂɂł���O���t�B�b�N�n���h�����c�c�r�`���ŕۑ�����
extern	int			NS_SaveDrawValidGraphToJPEG(           int GrHandle, int x1, int y1, int x2, int y2, const TCHAR *FileName,                        int Quality = 80 , int Sample2x1 = TRUE ) ;																						// �`��Ώۂɂł���O���t�B�b�N�n���h�����i�o�d�f�`���ŕۑ����� Quality = �掿�A�l���傫���قǒሳ�k���掿,0�`100 
extern	int			NS_SaveDrawValidGraphToJPEGWithStrLen( int GrHandle, int x1, int y1, int x2, int y2, const TCHAR *FileName, size_t FileNameLength, int Quality = 80 , int Sample2x1 = TRUE ) ;																						// �`��Ώۂɂł���O���t�B�b�N�n���h�����i�o�d�f�`���ŕۑ����� Quality = �掿�A�l���傫���قǒሳ�k���掿,0�`100 
extern	int			NS_SaveDrawValidGraphToPNG(            int GrHandle, int x1, int y1, int x2, int y2, const TCHAR *FileName,                        int CompressionLevel = -1 ) ;																									// �`��Ώۂɂł���O���t�B�b�N�n���h�����o�m�f�`���ŕۑ����� CompressionLevel = ���k���A�l���傫���قǍ����k�������ׁA�O�͖����k,0�`9
extern	int			NS_SaveDrawValidGraphToPNGWithStrLen(  int GrHandle, int x1, int y1, int x2, int y2, const TCHAR *FileName, size_t FileNameLength, int CompressionLevel = -1 ) ;																									// �`��Ώۂɂł���O���t�B�b�N�n���h�����o�m�f�`���ŕۑ����� CompressionLevel = ���k���A�l���傫���قǍ����k�������ׁA�O�͖����k,0�`9

#endif // DX_NON_SAVEFUNCTION

// ���_�o�b�t�@�֌W�֐�
extern	int			NS_CreateVertexBuffer(		int VertexNum, int VertexType /* DX_VERTEX_TYPE_NORMAL_3D �� */ ) ;						// ���_�o�b�t�@���쐬����( -1:�G���[  0�ȏ�:���_�o�b�t�@�n���h�� )
extern	int			NS_DeleteVertexBuffer(		int VertexBufHandle ) ;																	// ���_�o�b�t�@���폜����
extern	int			NS_InitVertexBuffer(		void ) ;																				// ���ׂĂ̒��_�o�b�t�@���폜����
extern	int			NS_SetVertexBufferData(	int SetIndex, const void *VertexData, int VertexNum, int VertexBufHandle ) ;					// ���_�o�b�t�@�ɒ��_�f�[�^��]������
extern	void *		NS_GetBufferVertexBuffer(	int VertexBufHandle ) ;																	// ���_�o�b�t�@�n���h���̒��_�o�b�t�@�̃A�h���X���擾����
extern	int			NS_UpdateVertexBuffer(		int VertexBufHandle, int UpdateStartIndex, int UpdateVertexNum ) ;						// ���_�o�b�t�@�n���h���̒��_�o�b�t�@�ւ̕ύX��K�p����( GetBufferVertexBuffer �Ŏ擾�����o�b�t�@�ւ̕ύX�𔽉f���� )
extern	int			NS_CreateIndexBuffer(		int IndexNum, int IndexType /* DX_INDEX_TYPE_16BIT �� */  ) ;							// �C���f�b�N�X�o�b�t�@���쐬����( -1:�G���[�@0�ȏ�F�C���f�b�N�X�o�b�t�@�n���h�� )
extern	int			NS_DeleteIndexBuffer(		int IndexBufHandle ) ;																	// �C���f�b�N�X�o�b�t�@���폜����
extern	int			NS_InitIndexBuffer(		void ) ;																				// ���ׂẴC���f�b�N�X�o�b�t�@���폜����
extern	int			NS_SetIndexBufferData(		int SetIndex, const void *IndexData, int IndexNum, int IndexBufHandle ) ;						// �C���f�b�N�X�o�b�t�@�ɃC���f�b�N�X�f�[�^��]������
extern	void *		NS_GetBufferIndexBuffer(	int IndexBufHandle ) ;																	// �C���f�b�N�X�o�b�t�@�n���h���̃C���f�b�N�X�o�b�t�@�̃A�h���X���擾����
extern	int			NS_UpdateIndexBuffer(		int IndexBufHandle, int UpdateStartIndex, int UpdateIndexNum ) ;						// �C���f�b�N�X�o�b�t�@�n���h���̃C���f�b�N�X�o�b�t�@�ւ̕ύX��K�p����( GetBufferIndexBuffer �Ŏ擾�����o�b�t�@�ւ̕ύX�𔽉f���� )
extern	int			NS_GetMaxPrimitiveCount(	void ) ;																				// �O���t�B�b�N�X�f�o�C�X���Ή����Ă����x�ɕ`��ł���v���~�e�B�u�̍ő吔���擾����
extern	int			NS_GetMaxVertexIndex(		void ) ;																				// �O���t�B�b�N�X�f�o�C�X���Ή����Ă����x�Ɏg�p���邱�Ƃ̂ł���ő咸�_�����擾����

// �V�F�[�_�[�֌W�֐�
extern	int			NS_GetValidShaderVersion(		void ) ;												// �g�p�ł���V�F�[�_�[�̃o�[�W�������擾����( 0=�g���Ȃ�  200=�V�F�[�_�[���f���Q�D�O���g�p�\  300=�V�F�[�_�[���f���R�D�O���g�p�\ )

extern	int			NS_LoadVertexShader(			const TCHAR *FileName ) ;								// ���_�V�F�[�_�[�o�C�i�����t�@�C������ǂݍ��ݒ��_�V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadVertexShaderWithStrLen(	const TCHAR *FileName, size_t FileNameLength ) ;		// ���_�V�F�[�_�[�o�C�i�����t�@�C������ǂݍ��ݒ��_�V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadGeometryShader(				const TCHAR *FileName                        ) ;		// �s�N�Z���V�F�[�_�[�o�C�i�����t�@�C������ǂݍ��݃W�I���g���V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadGeometryShaderWithStrLen(	const TCHAR *FileName, size_t FileNameLength ) ;		// �s�N�Z���V�F�[�_�[�o�C�i�����t�@�C������ǂݍ��݃W�I���g���V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadPixelShader(			const TCHAR *FileName                        ) ;		// �s�N�Z���V�F�[�_�[�o�C�i�����t�@�C������ǂݍ��݃s�N�Z���V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadPixelShaderWithStrLen(	const TCHAR *FileName, size_t FileNameLength ) ;		// �s�N�Z���V�F�[�_�[�o�C�i�����t�@�C������ǂݍ��݃s�N�Z���V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadVertexShaderFromMem(	const void *ImageAddress, int ImageSize ) ;					// ��������ԏ�ɑ��݂��钸�_�V�F�[�_�[�o�C�i�����璸�_�V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadGeometryShaderFromMem(		const void *ImageAddress, int ImageSize ) ;				// �������ɓǂݍ��܂ꂽ���_�V�F�[�_�[�o�C�i������W�I���g���V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadPixelShaderFromMem(		const void *ImageAddress, int ImageSize ) ;					// ��������ԏ�ɑ��݂���s�N�Z���V�F�[�_�[�o�C�i������s�N�Z���V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_DeleteShader(				int ShaderHandle ) ;									// �V�F�[�_�[�n���h���̍폜
extern	int			NS_InitShader(					void ) ;												// �V�F�[�_�[�n���h����S�č폜����

extern	int			NS_GetConstIndexToShader(           const TCHAR *ConstantName, int ShaderHandle ) ;	// �w��̖��O�����萔���g�p����V�F�[�_�[�萔�̔ԍ����擾����
extern	int			NS_GetConstIndexToShaderWithStrLen(           const TCHAR *ConstantName, size_t ConstantNameLength, int ShaderHandle ) ;	// �w��̖��O�����萔���g�p����V�F�[�_�[�萔�̔ԍ����擾����
extern	int			NS_GetConstCountToShader(                     const TCHAR *ConstantName,                            int ShaderHandle ) ;	// �w��̖��O�����萔���g�p����V�F�[�_�[�萔�̐����擾����
extern	int			NS_GetConstCountToShaderWithStrLen(           const TCHAR *ConstantName, size_t ConstantNameLength, int ShaderHandle ) ;	// �w��̖��O�����萔���g�p����V�F�[�_�[�萔�̐����擾����
extern	const FLOAT4 *NS_GetConstDefaultParamFToShader(           const TCHAR *ConstantName,                            int ShaderHandle ) ;	// �w��̖��O�������������_���萔�̃f�t�H���g�p�����[�^���i�[����Ă��郁�����A�h���X���擾����
extern	const FLOAT4 *NS_GetConstDefaultParamFToShaderWithStrLen( const TCHAR *ConstantName, size_t ConstantNameLength, int ShaderHandle ) ;	// �w��̖��O�������������_���萔�̃f�t�H���g�p�����[�^���i�[����Ă��郁�����A�h���X���擾����
extern	int			NS_SetVSConstSF(         int ConstantIndex, float  Param ) ;							// ���_�V�F�[�_�[�� float �^�萔��ݒ肷��
extern	int			NS_SetVSConstF(          int ConstantIndex, FLOAT4 Param ) ;							// ���_�V�F�[�_�[�� float �^�萔��ݒ肷��
extern	int			NS_SetVSConstFMtx(       int ConstantIndex, MATRIX Param ) ;							// ���_�V�F�[�_�[�� float �^�萔�ɍs���ݒ肷��
extern	int			NS_SetVSConstFMtxT(      int ConstantIndex, MATRIX Param ) ;							// ���_�V�F�[�_�[�� float �^�萔�ɓ]�u�����s���ݒ肷��
extern	int			NS_SetVSConstSI(         int ConstantIndex, int    Param ) ;							// ���_�V�F�[�_�[�� int �^�萔��ݒ肷��
extern	int			NS_SetVSConstI(          int ConstantIndex, INT4   Param ) ;							// ���_�V�F�[�_�[�� int �^�萔��ݒ肷��
extern	int			NS_SetVSConstB(          int ConstantIndex, BOOL   Param ) ;							// ���_�V�F�[�_�[�� BOOL �^�萔��ݒ肷��
extern	int			NS_SetVSConstSFArray(    int ConstantIndex, const float  *ParamArray, int ParamNum ) ;	// ���_�V�F�[�_�[�� float �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstFArray(     int ConstantIndex, const FLOAT4 *ParamArray, int ParamNum ) ;	// ���_�V�F�[�_�[�� float �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstFMtxArray(  int ConstantIndex, const MATRIX *ParamArray, int ParamNum ) ;	// ���_�V�F�[�_�[�� float �^�萔�ɍs���ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstFMtxTArray( int ConstantIndex, const MATRIX *ParamArray, int ParamNum ) ;	// ���_�V�F�[�_�[�� float �^�萔�ɓ]�u�����s���ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstSIArray(    int ConstantIndex, const int    *ParamArray, int ParamNum ) ;	// ���_�V�F�[�_�[�� int   �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstIArray(     int ConstantIndex, const INT4   *ParamArray, int ParamNum ) ;	// ���_�V�F�[�_�[�� int   �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstBArray(     int ConstantIndex, const BOOL   *ParamArray, int ParamNum ) ;	// ���_�V�F�[�_�[�� BOOL  �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_ResetVSConstF(        int ConstantIndex, int ParamNum ) ;							// ���_�V�F�[�_�[�� float �^�萔�̐ݒ�����Z�b�g����
extern	int			NS_ResetVSConstI(        int ConstantIndex, int ParamNum ) ;							// ���_�V�F�[�_�[�� int �^�萔�̐ݒ�����Z�b�g����
extern	int			NS_ResetVSConstB(        int ConstantIndex, int ParamNum ) ;							// ���_�V�F�[�_�[�� BOOL �^�萔�̐ݒ�����Z�b�g����

extern	int			NS_SetPSConstSF(         int ConstantIndex, float  Param ) ;							// �s�N�Z���V�F�[�_�[�� float �^�萔��ݒ肷��
extern	int			NS_SetPSConstF(          int ConstantIndex, FLOAT4 Param ) ;							// �s�N�Z���V�F�[�_�[�� float �^�萔��ݒ肷��
extern	int			NS_SetPSConstFMtx(       int ConstantIndex, MATRIX Param ) ;							// �s�N�Z���V�F�[�_�[�� float �^�萔�ɍs���ݒ肷��
extern	int			NS_SetPSConstFMtxT(      int ConstantIndex, MATRIX Param ) ;							// �s�N�Z���V�F�[�_�[�� float �^�萔�ɓ]�u�����s���ݒ肷��
extern	int			NS_SetPSConstSI(         int ConstantIndex, int    Param ) ;							// �s�N�Z���V�F�[�_�[�� int �^�萔��ݒ肷��
extern	int			NS_SetPSConstI(          int ConstantIndex, INT4   Param ) ;							// �s�N�Z���V�F�[�_�[�� int �^�萔��ݒ肷��
extern	int			NS_SetPSConstB(          int ConstantIndex, BOOL   Param ) ;							// �s�N�Z���V�F�[�_�[�� BOOL �^�萔��ݒ肷��
extern	int			NS_SetPSConstSFArray(    int ConstantIndex, const float  *ParamArray, int ParamNum ) ;	// �s�N�Z���V�F�[�_�[�� float �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstFArray(     int ConstantIndex, const FLOAT4 *ParamArray, int ParamNum ) ;	// �s�N�Z���V�F�[�_�[�� float �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstFMtxArray(  int ConstantIndex, const MATRIX *ParamArray, int ParamNum ) ;	// �s�N�Z���V�F�[�_�[�� float �^�萔�ɍs���ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstFMtxTArray( int ConstantIndex, const MATRIX *ParamArray, int ParamNum ) ;	// �s�N�Z���V�F�[�_�[�� float �^�萔�ɓ]�u�����s���ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstSIArray(    int ConstantIndex, const int    *ParamArray, int ParamNum ) ;	// �s�N�Z���V�F�[�_�[�� int   �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstIArray(     int ConstantIndex, const INT4   *ParamArray, int ParamNum ) ;	// �s�N�Z���V�F�[�_�[�� int   �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstBArray(     int ConstantIndex, const BOOL   *ParamArray, int ParamNum ) ;	// �s�N�Z���V�F�[�_�[�� BOOL  �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_ResetPSConstF(        int ConstantIndex, int ParamNum ) ;							// �s�N�Z���V�F�[�_�[�� float �^�萔�̐ݒ�����Z�b�g����
extern	int			NS_ResetPSConstI(        int ConstantIndex, int ParamNum ) ;							// �s�N�Z���V�F�[�_�[�� int �^�萔�̐ݒ�����Z�b�g����
extern	int			NS_ResetPSConstB(        int ConstantIndex, int ParamNum ) ;							// �s�N�Z���V�F�[�_�[�� BOOL �^�萔�̐ݒ�����Z�b�g����

extern	int			NS_SetRenderTargetToShader( int TargetIndex, int DrawScreen, int SurfaceIndex = 0 , int MipLevel = 0 ) ;	// �V�F�[�_�[���g�p�����`��ł̕`����ݒ肷��
extern	int			NS_SetUseTextureToShader(   int StageIndex, int GraphHandle ) ;						// �V�F�[�_�[�`��Ŏg�p����O���t�B�b�N��ݒ肷��
extern	int			NS_SetUseVertexShader(      int ShaderHandle ) ;										// �V�F�[�_�[�`��Ɏg�p���钸�_�V�F�[�_�[��ݒ肷��( -1��n���Ɖ��� )
extern	int			NS_SetUseGeometryShader(    int ShaderHandle ) ;										// �V�F�[�_�[���g�p�����`��Ɏg�p����W�I���g���V�F�[�_�[��ݒ肷��( -1��n���Ɖ��� )
extern	int			NS_SetUsePixelShader(       int ShaderHandle ) ;										// �V�F�[�_�[�`��Ɏg�p����s�N�Z���V�F�[�_�[��ݒ肷��( -1��n���Ɖ��� )

extern	int			NS_CalcPolygonBinormalAndTangentsToShader(        VERTEX3DSHADER *Vertex, int PolygonNum ) ;													// �|���S���̒��_�̐ڐ��Ə]�@�����t�u���W����v�Z���ăZ�b�g����
extern	int			NS_CalcPolygonIndexedBinormalAndTangentsToShader( VERTEX3DSHADER *Vertex, int VertexNum, const unsigned short *Indices, int PolygonNum ) ;		// �|���S���̒��_�̐ڐ��Ə]�@�����t�u���W����v�Z���ăZ�b�g����( ���_�C���f�b�N�X���g�p���� )
extern	int			NS_CalcPolygon32bitIndexedBinormalAndTangentsToShader( VERTEX3DSHADER *VertexArray, int VertexNum, const unsigned int   *IndexArray, int PolygonNum ) ;	// �|���S���̒��_�̐ڐ��Ə]�@�����t�u���W����v�Z���ăZ�b�g����( ���_�C���f�b�N�X���g�p���� )

extern	int			NS_DrawBillboard3DToShader( VECTOR Pos, float cx, float cy, float Size, float Angle, int GrHandle, int TransFlag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE ) ;													// �V�F�[�_�[���g���ăr���{�[�h��`�悷��
extern	int			NS_DrawPolygon2DToShader(          const VERTEX2DSHADER *Vertex, int PolygonNum ) ;																										// �V�F�[�_�[���g���ĂQ�c�|���S����`�悷��
extern	int			NS_DrawPolygon3DToShader(          const VERTEX3DSHADER *Vertex, int PolygonNum ) ;																										// �V�F�[�_�[���g���ĂR�c�|���S����`�悷��
extern	int			NS_DrawPolygonIndexed2DToShader(   const VERTEX2DSHADER *Vertex, int VertexNum, const unsigned short *Indices, int PolygonNum ) ;															// �V�F�[�_�[���g���ĂQ�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p���� )
extern	int			NS_DrawPolygon32bitIndexed2DToShader(   const VERTEX2DSHADER *VertexArray, int VertexNum, const unsigned int   *IndexArray, int PolygonNum ) ;															// �V�F�[�_�[���g���ĂQ�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p���� )
extern	int			NS_DrawPolygonIndexed3DToShader(   const VERTEX3DSHADER *Vertex, int VertexNum, const unsigned short *Indices, int PolygonNum ) ;															// �V�F�[�_�[���g���ĂR�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p���� )
extern	int			NS_DrawPolygon32bitIndexed3DToShader(   const VERTEX3DSHADER *VertexArray, int VertexNum, const unsigned int   *IndexArray, int PolygonNum ) ;															// �V�F�[�_�[���g���ĂR�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p���� )
extern	int			NS_DrawPrimitive2DToShader(        const VERTEX2DSHADER *Vertex, int VertexNum,                                              int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;		// �V�F�[�_�[���g���ĂQ�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitive3DToShader(        const VERTEX3DSHADER *Vertex, int VertexNum,                                              int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;		// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitiveIndexed2DToShader( const VERTEX2DSHADER *Vertex, int VertexNum, const unsigned short *Indices, int IndexNum, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;		// �V�F�[�_�[���g���ĂQ�c�v���~�e�B�u��`�悷��( ���_�C���f�b�N�X���g�p���� )
extern	int			NS_DrawPrimitive32bitIndexed2DToShader( const VERTEX2DSHADER *VertexArray, int VertexNum, const unsigned int   *IndexArray, int IndexNum, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;		// �V�F�[�_�[���g���ĂQ�c�v���~�e�B�u��`�悷��( ���_�C���f�b�N�X���g�p���� )
extern	int			NS_DrawPrimitiveIndexed3DToShader( const VERTEX3DSHADER *Vertex, int VertexNum, const unsigned short *Indices, int IndexNum, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;		// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�C���f�b�N�X���g�p���� )
extern	int			NS_DrawPrimitive32bitIndexed3DToShader( const VERTEX3DSHADER *VertexArray, int VertexNum, const unsigned int   *IndexArray, int IndexNum, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;		// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�C���f�b�N�X���g�p���� )
extern	int			NS_DrawPolygon3DToShader_UseVertexBuffer(           int VertexBufHandle ) ;																												// �V�F�[�_�[���g���ĂR�c�|���S����`�悷��( ���_�o�b�t�@�g�p�� )
extern	int			NS_DrawPolygonIndexed3DToShader_UseVertexBuffer(    int VertexBufHandle, int IndexBufHandle ) ;																							// �V�F�[�_�[���g���ĂR�c�|���S����`�悷��( ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�g�p�� )
extern	int			NS_DrawPrimitive3DToShader_UseVertexBuffer(         int VertexBufHandle,                     int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;										// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�o�b�t�@�g�p�� )
extern	int			NS_DrawPrimitive3DToShader_UseVertexBuffer2(        int VertexBufHandle,                     int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int StartVertex, int UseVertexNum ) ;	// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�o�b�t�@�g�p�� )
extern	int			NS_DrawPrimitiveIndexed3DToShader_UseVertexBuffer(  int VertexBufHandle, int IndexBufHandle, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;										// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�g�p�� )
extern	int			NS_DrawPrimitiveIndexed3DToShader_UseVertexBuffer2( int VertexBufHandle, int IndexBufHandle, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int BaseVertex, int StartVertex, int UseVertexNum, int StartIndex, int UseIndexNum ) ;	// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�g�p�� )

// �V�F�[�_�[�p�萔�o�b�t�@�֌W�֐�
extern	int			NS_InitShaderConstantBuffer(		void ) ;																					// �S�ẴV�F�[�_�[�p�萔�o�b�t�@�n���h�����폜����
extern	int			NS_CreateShaderConstantBuffer(		int BufferSize ) ;																			// �V�F�[�_�[�p�萔�o�b�t�@�n���h��������������
extern	int			NS_DeleteShaderConstantBuffer(		int SConstBufHandle ) ;																		// �V�F�[�_�[�p�萔�o�b�t�@�n���h���̌�n��
extern	void *		NS_GetBufferShaderConstantBuffer(	int SConstBufHandle ) ;																		// �V�F�[�_�[�p�萔�o�b�t�@�n���h���̒萔�o�b�t�@�̃A�h���X���擾����
extern	int			NS_UpdateShaderConstantBuffer(		int SConstBufHandle ) ;																		// �V�F�[�_�[�p�萔�o�b�t�@�n���h���̒萔�o�b�t�@�ւ̕ύX��K�p����
extern	int			NS_SetShaderConstantBuffer(		int SConstBufHandle, int TargetShader /* DX_SHADERTYPE_VERTEX �Ȃ� */ , int Slot ) ;		// �V�F�[�_�[�p�萔�o�b�t�@�n���h���̒萔�o�b�t�@���w��̃V�F�[�_�[�̎w��̃X���b�g�ɃZ�b�g����

// �t�B���^�[�֌W�֐�
#ifndef DX_NON_FILTER
extern	int			NS_SetGraphFilterBltBlendMode( int BlendMode /* DX_BLENDMODE_ALPHA �Ȃ� */ ) ;												// GraphFilterBlt �� GraphBlendBlt �̌��ʂ�]����ɓ]������ۂ̃u�����h���[�h��ݒ肷��( ����őΉ����Ă���̂� DX_BLENDMODE_NOBLEND �� DX_BLENDMODE_ALPHA �̂� )
extern	int			NS_SetGraphBlendScalingFilterMode( int IsBilinearFilter ) ;																	// GraphBlend �� GrHandle �� BlendGrHandle �̃T�C�Y���قȂ�ꍇ�ɓK�p�����g��t�B���^�[���[�h��ݒ肷��( IsBilinearFilter  TRUE:�o�C���j�A�t�B���^�[(�f�t�H���g)  FALSE:�j�A���X�g�t�B���^�[ )
extern	int			NS_GraphFilter(        int    GrHandle,                                                                                     int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , ... ) ;		// �摜�Ƀt�B���^�[�������s��
extern	int			NS_GraphFilterBlt(     int SrcGrHandle, int DestGrHandle,                                                                   int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , ... ) ;		// �摜�̃t�B���^�[�t���]�����s��
extern	int			NS_GraphFilterRectBlt( int SrcGrHandle, int DestGrHandle, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int DestX, int DestY, int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , ... ) ;		// �摜�̃t�B���^�[�t���]�����s��( ��`�w�� )
extern	int			NS_GraphFilterRectBlt2( int SrcGrHandle, int DestGrHandle, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int DestX1, int DestY1, int DestX2, int DestY2, int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , ... ) ;		// �摜�̃t�B���^�[�t���]�����s��( ��`�w���R )
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_MONO, int Cb = �F��( -255 �` 255 ), int Cr = �ԐF��( -255 �` 255 ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_GAUSS, int PixelWidth = �g�p�s�N�Z����( 8 , 16 , 32 �̉��ꂩ ), int Param = �ڂ����p�����[�^( 100 �Ŗ�1�s�N�Z�����̕� ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_DOWN_SCALE, int DivNum = ���̃T�C�Y�̉����̂P���A�Ƃ����l( 2 , 4 , 8 �̉��ꂩ ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_BRIGHT_CLIP, int CmpType = �N���b�v�^�C�v( DX_CMP_LESS:CmpParam�ȉ����N���b�v  ����  DX_CMP_GREATER:CmpParam�ȏ���N���b�v ), int CmpParam = �N���b�v�p�����[�^( 0 �` 255 ), int ClipFillFlag = �N���b�v�����s�N�Z����h��Ԃ����ǂ���( TRUE:�h��Ԃ�  FALSE:�h��Ԃ��Ȃ� ), int ClipFillColor = �N���b�v�����s�N�Z���ɓh��F�l( GetColor �Ŏ擾���� )( ClipFillFlag �� FALSE �̏ꍇ�͎g�p���Ȃ� ), int ClipFillAlpha = �N���b�v�����s�N�Z���ɓh�郿�l( 0 �` 255 )( ClipFillFlag �� FALSE �̏ꍇ�͎g�p���Ȃ� ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_HSB, int HueType = Hue �̈Ӗ�( 0:���Βl  1:��Βl ), int Hue = �F���p�����[�^( HueType �� 0 �̏ꍇ = �s�N�Z���̐F���ɑ΂��鑊�Βl( -180 �` 180 )   HueType �� 1 �̏ꍇ = �F���̐�Βl( 0 �` 360 ) ), int Saturation = �ʓx( -255 �` ), int Bright = �P�x( -255 �` 255 ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_INVERT ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_LEVEL, int Min = �ϊ����̉����l( 0 �` 255 ), int Max = �ϊ����̏���l( 0 �` 255 ), int Gamma = �K���}�l( 100 �ŃK���}�␳�����A0 �Ƃ���ȉ��̒l�͕s�� ), int AfterMin = �ϊ���̍Œ�l( 0 �` 255 ), int AfterMax = �ϊ���̍ő�l( 0 �` 255 ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_TWO_COLOR, int Threshold = 臒l( 0 �` 255 ), int LowColor = 臒l���l���Ⴉ�����s�N�Z���̕ϊ���̐F�l( GetColor �Ŏ擾���� ), int LowAlpha = 臒l���l���Ⴉ�����s�N�Z���̕ϊ���̃��l( 0 �` 255 ), int HighColor = 臒l���l�����������s�N�Z���̕ϊ���̐F�l( GetColor �Ŏ擾���� ), int HighAlpha = 臒l���l�����������s�N�Z���̕ϊ���̃��l( 0 �` 255 ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_GRADIENT_MAP, int MapGrHandle = �O���f�[�V�����}�b�v�̃O���t�B�b�N�n���h��( ���摜�̋P�x����O���f�[�V�����}�b�v�摜�� x ���W���Z�o���܂��̂ŏc����1dot�ł��n�j ), int Reverse = �O���f�[�V�����}�b�v���E���]�t���O( TRUE : �O���f�[�V�����}�b�v�����E���]���Ďg��  FALSE : ���E���]���Ȃ� ) ) ;

extern	int			NS_GraphBlend(         int    GrHandle, int BlendGrHandle,                                                                                                                                         int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , ... ) ;	// ��̉摜���u�����h����
extern	int			NS_GraphBlendBlt(      int SrcGrHandle, int BlendGrHandle, int DestGrHandle,                                                                                                                       int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , ... ) ;	// ��̉摜���u�����h���Č��ʂ��w��̉摜�ɏo�͂���
extern	int			NS_GraphBlendRectBlt(  int SrcGrHandle, int BlendGrHandle, int DestGrHandle, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int BlendX,  int BlendY,                            int DestX, int DestY, int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , ... ) ;	// ��̉摜���u�����h���Č��ʂ��w��̉摜�ɏo�͂���( ��`�w�� )
extern	int			NS_GraphBlendRectBlt2( int SrcGrHandle, int BlendGrHandle, int DestGrHandle, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int BlendX1, int BlendY1, int BlendX2, int BlendY2, int DestX, int DestY, int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , ... ) ;	// ��̉摜���u�����h���Č��ʂ��w��̉摜�ɏo�͂���( ��`�w��A�u�����h�摜����`�w�� )
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_NORMAL ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_RGBA_SELECT_MIX, int SelectR = ( �o�͂̐ԕ��ƂȂ鐬�� DX_RGBA_SELECT_SRC_R �� ), int SelectG = ( �o�̗͂ΐ����ƂȂ鐬�� DX_RGBA_SELECT_SRC_R �� ), int SelectB = ( �o�͂̐����ƂȂ鐬�� DX_RGBA_SELECT_SRC_R �� ), int SelectA = ( �o�͂̃������ƂȂ鐬�� DX_RGBA_SELECT_SRC_R �� ) ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_MULTIPLE ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_DIFFERENCE ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_ADD ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_SCREEN ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_OVERLAY ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_DODGE ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_BURN ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_DARKEN ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_LIGHTEN ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_SOFTLIGHT ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_HARDLIGHT ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_EXCLUSION ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_HUE ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_SATURATION ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_COLOR ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_BRIGHT ) ;
#endif // DX_NON_FILTER

#ifndef DX_NON_MOVIE
// ���[�r�[�O���t�B�b�N�֌W�֐�
extern	int			NS_PlayMovie(						const TCHAR *FileName, int ExRate, int PlayType ) ;						// ����t�@�C���̍Đ�
extern	int			NS_PlayMovieWithStrLen(				const TCHAR *FileName, size_t FileNameLength, int ExRate, int PlayType ) ;	// ����t�@�C���̍Đ�
extern	int			NS_GetMovieImageSize_File(             const TCHAR *FileName,                        int *SizeX, int *SizeY ) ;	// ����t�@�C���̉��s�N�Z�����Əc�s�N�Z�������擾����
extern	int			NS_GetMovieImageSize_File_WithStrLen(  const TCHAR *FileName, size_t FileNameLength, int *SizeX, int *SizeY ) ;	// ����t�@�C���̉��s�N�Z�����Əc�s�N�Z�������擾����
extern	int			NS_GetMovieImageSize_Mem(              const void *FileImage, int FileImageSize, int *SizeX, int *SizeY ) ;	// ��������ɓW�J���ꂽ����t�@�C���̉��s�N�Z�����Əc�s�N�Z�������擾����
extern	int			NS_OpenMovieToGraph(				const TCHAR *FileName, int FullColor = TRUE ) ;							// ���[�r�[���J��
extern	int			NS_OpenMovieToGraphWithStrLen(			const TCHAR *FileName, size_t FileNameLength, int FullColor = TRUE ) ;		// ����t�@�C�����J��
extern	int			NS_PlayMovieToGraph(				int GraphHandle, int PlayType = DX_PLAYTYPE_BACK , int SysPlay = 0 ) ;	// ���[�r�[�O���t�B�b�N�Ɋ܂܂�郀�[�r�[�̍Đ����J�n����
extern	int			NS_PauseMovieToGraph(				int GraphHandle, int SysPause = 0 ) ;									// ���[�r�[�O���t�B�b�N�Ɋ܂܂�郀�[�r�[�̍Đ����X�g�b�v����
extern	int			NS_AddMovieFrameToGraph(			int GraphHandle, unsigned int FrameNum ) ;								// ���[�r�[�̃t���[����i�߂�A�߂����Ƃ͏o���Ȃ�( ���[�r�[����~��ԂŁA���� Ogg Theora �̂ݗL�� )
extern	int			NS_SeekMovieToGraph(				int GraphHandle, int Time ) ;											// ���[�r�[�̍Đ��ʒu��ݒ肷��(�~���b�P��)
extern	int			NS_SetPlaySpeedRateMovieToGraph(		int GraphHandle, double SpeedRate ) ;									// ����t�@�C���̍Đ����x��ݒ肷��( 1.0 = ���{��  2.0 = �Q�{�� )�A�ꕔ�̃t�@�C���t�H�[�}�b�g�݂̂ŗL���ȋ@�\�ł�
extern	int			NS_GetMovieStateToGraph(			int GraphHandle ) ;														// ���[�r�[�̍Đ���Ԃ𓾂�
extern	int			NS_SetMovieVolumeToGraph(			int Volume, int GraphHandle ) ;											// ���[�r�[�̃{�����[�����Z�b�g����(0�`10000)
extern	int			NS_GetMovieVolumeToGraph(				            int GraphHandle ) ;												// ����t�@�C���̉��ʂ��擾����(0�`10000)
extern	int			NS_ChangeMovieVolumeToGraph(		int Volume, int GraphHandle ) ;											// ���[�r�[�̃{�����[�����Z�b�g����(0�`255)
extern	int			NS_GetMovieVolumeToGraph2(				            int GraphHandle ) ;												// ����t�@�C���̉��ʂ��擾����(0�`255)
extern	const BASEIMAGE* NS_GetMovieBaseImageToGraph(	int GraphHandle, int *ImageUpdateFlag , int ImageUpdateFlagSetOnly ) ;	// ���[�r�[�̊�{�C���[�W�f�[�^���擾����
extern	int			NS_GetMovieTotalFrameToGraph(		int GraphHandle ) ;														// ���[�r�[�̑��t���[�����𓾂�( Ogg Theora �ł̂ݗL�� )
extern	int			NS_TellMovieToGraph(				int GraphHandle ) ;														// ���[�r�[�̍Đ��ʒu���擾����(�~���b�P��)
extern	int			NS_TellMovieToGraphToFrame(		int GraphHandle ) ;														// ���[�r�[�̍Đ��ʒu���擾����(�t���[���P��)
extern	int			NS_SeekMovieToGraphToFrame(		int GraphHandle, int Frame ) ;											// ���[�r�[�̍Đ��ʒu��ݒ肷��(�t���[���P��)
extern	LONGLONG	NS_GetOneFrameTimeMovieToGraph(	int GraphHandle ) ;														// ���[�r�[�̂P�t���[��������̎��Ԃ𓾂�
extern	int			NS_GetLastUpdateTimeMovieToGraph(	int GraphHandle ) ;														// ���[�r�[�̃C���[�W���Ō�ɍX�V�������Ԃ𓾂�(�~���b�P��)
extern	int			NS_UpdateMovieToGraph(					int GraphHandle ) ;															// ����t�@�C���̍X�V�������s��
extern	int			NS_SetMovieRightImageAlphaFlag(	int Flag ) ;															// �ǂݍ��ޓ���t�@�C���f���̉E�����̐Ԑ����������Ƃ��Ĉ������ǂ������Z�b�g����( TRUE:�����Ƃ��Ĉ���  FALSE:�����Ƃ��Ĉ���Ȃ�( �f�t�H���g ) )
extern	int			NS_SetMovieColorA8R8G8B8Flag(		int Flag ) ;															// �ǂݍ��ޓ���t�@�C����32bit�J���[�������ꍇ�AA8R8G8B8 �`���Ƃ��Ĉ������ǂ������Z�b�g����A32bit�J���[�ł͂Ȃ�����t�@�C���ɑ΂��Ă͖���( Flag  TRUE:A8R8G8B8�Ƃ��Ĉ���  FALSE:X8R8G8B8�Ƃ��Ĉ���( �f�t�H���g ) )
extern	int			NS_SetMovieUseYUVFormatSurfaceFlag(	int Flag ) ;															// �x�t�u�t�H�[�}�b�g�̃T�[�t�F�X���g�p�ł���ꍇ�͂x�t�u�t�H�[�}�b�g�̃T�[�t�F�X���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����( �f�t�H���g ) FALSE:�q�f�a�t�H�[�}�b�g�̃T�[�t�F�X���g�p���� )
#endif

// �J�����֌W�֐�
extern	int			NS_SetCameraNearFar(					float Near, float Far ) ;											// �J������ Near�N���b�v�ʂ� Far�N���b�v�ʂ̋�����ݒ肷��
extern	int			NS_SetCameraNearFarD(					double Near, double Far ) ;											// �J������ Near�N���b�v�ʂ� Far�N���b�v�ʂ̋�����ݒ肷��
extern	int			NS_SetCameraPositionAndTarget_UpVecY(  VECTOR    Position, VECTOR   Target ) ;								// �J�����̎��_�A�����_�A�A�b�v�x�N�g����ݒ肷��( �A�b�v�x�N�g���͂x���������瓱���o�� )
extern	int			NS_SetCameraPositionAndTarget_UpVecYD( VECTOR_D  Position, VECTOR_D Target ) ;								// �J�����̎��_�A�����_�A�A�b�v�x�N�g����ݒ肷��( �A�b�v�x�N�g���͂x���������瓱���o�� )
extern	int			NS_SetCameraPositionAndTargetAndUpVec( VECTOR    Position, VECTOR   TargetPosition, VECTOR   UpVector ) ;	// �J�����̎��_�A�����_�A�A�b�v�x�N�g����ݒ肷��
extern	int			NS_SetCameraPositionAndTargetAndUpVecD( VECTOR_D Position, VECTOR_D TargetPosition, VECTOR_D UpVector ) ;	// �J�����̎��_�A�����_�A�A�b�v�x�N�g����ݒ肷��
extern	int			NS_SetCameraPositionAndAngle(			VECTOR   Position, float  VRotate, float  HRotate, float  TRotate ) ;	// �J�����̎��_�A�����_�A�A�b�v�x�N�g����ݒ肷��( �����_�ƃA�b�v�x�N�g���͐�����]�p�x�A������]�p�x�A�P���]�p�x���瓱���o�� )
extern	int			NS_SetCameraPositionAndAngleD(			VECTOR_D Position, double VRotate, double HRotate, double TRotate ) ;	// �J�����̎��_�A�����_�A�A�b�v�x�N�g����ݒ肷��( �����_�ƃA�b�v�x�N�g���͐�����]�p�x�A������]�p�x�A�P���]�p�x���瓱���o�� )
extern	int			NS_SetCameraViewMatrix(					MATRIX   ViewMatrix ) ;												// �r���[�s��𒼐ڐݒ肷��
extern	int			NS_SetCameraViewMatrixD(				MATRIX_D ViewMatrix ) ;												// �r���[�s��𒼐ڐݒ肷��
extern	int			NS_SetCameraScreenCenter(				float x, float y ) ;												// ��ʏ�ɂ�����J���������Ă���f���̒��S�̍��W��ݒ肷��
extern	int			NS_SetCameraScreenCenterD(				double x, double y ) ;												// ��ʏ�ɂ�����J���������Ă���f���̒��S�̍��W��ݒ肷��

extern	int			NS_SetupCamera_Perspective(			float  Fov ) ;														// ���ߖ@�J�������Z�b�g�A�b�v����
extern	int			NS_SetupCamera_PerspectiveD(			double Fov ) ;														// ���ߖ@�J�������Z�b�g�A�b�v����
extern	int			NS_SetupCamera_Ortho(					float  Size ) ;														// ���ˉe�J�������Z�b�g�A�b�v����
extern	int			NS_SetupCamera_OrthoD(					double Size ) ;														// ���ˉe�J�������Z�b�g�A�b�v����
extern	int			NS_SetupCamera_ProjectionMatrix(		MATRIX   ProjectionMatrix ) ;										// �ˉe�s��𒼐ڐݒ肷��
extern	int			NS_SetupCamera_ProjectionMatrixD(		MATRIX_D ProjectionMatrix ) ;										// �ˉe�s��𒼐ڐݒ肷��
extern	int			NS_SetCameraDotAspect(					float  DotAspect ) ;												// �J�����̃h�b�g�A�X�y�N�g���ݒ肷��
extern	int			NS_SetCameraDotAspectD(				double DotAspect ) ;												// �J�����̃h�b�g�A�X�y�N�g���ݒ肷��

extern	int			NS_CheckCameraViewClip(				VECTOR   CheckPos ) ;													// �w��̍��W���J�����̎��E�ɓ����Ă��邩�ǂ����𔻒肷��( �߂�l TRUE:���E�ɓ����Ă��Ȃ�  FALSE:���E�ɓ����Ă��� )
extern	int			NS_CheckCameraViewClipD(				VECTOR_D CheckPos ) ;													// �w��̍��W���J�����̎��E�ɓ����Ă��邩�ǂ����𔻒肷��( �߂�l TRUE:���E�ɓ����Ă��Ȃ�  FALSE:���E�ɓ����Ă��� )
extern	int			NS_CheckCameraViewClip_Dir(			VECTOR   CheckPos ) ;													// �w��̍��W���J�����̎��E�ɓ����Ă��邩�ǂ����𔻒肷��A�߂�l�ŊO��Ă���������m�邱�Ƃ��ł���( �߂�l 0:���E�ɓ����Ă���  0�ȊO:���E�ɓ����Ă��Ȃ�( DX_CAMERACLIP_LEFT �� DX_CAMERACLIP_RIGHT �� or ���Z�ō������ꂽ���́Aand ���Z�ŕ������m�F�ł��� ) )
extern	int			NS_CheckCameraViewClip_DirD(			VECTOR_D CheckPos ) ;													// �w��̍��W���J�����̎��E�ɓ����Ă��邩�ǂ����𔻒肷��A�߂�l�ŊO��Ă���������m�邱�Ƃ��ł���( �߂�l 0:���E�ɓ����Ă���  0�ȊO:���E�ɓ����Ă��Ȃ�( DX_CAMERACLIP_LEFT �� DX_CAMERACLIP_RIGHT �� or ���Z�ō������ꂽ���́Aand ���Z�ŕ������m�F�ł��� ) )
extern	int			NS_CheckCameraViewClip_Box(			VECTOR   BoxPos1, VECTOR   BoxPos2 ) ;									// ��̍��W�ŕ\�����{�b�N�X���J�����̎��E�ɓ����Ă��邩�ǂ����𔻒肷��( �߂�l TRUE:���E�ɓ����Ă��Ȃ�  FALSE:���E�ɓ����Ă��� )
extern	int			NS_CheckCameraViewClip_BoxD(			VECTOR_D BoxPos1, VECTOR_D BoxPos2 ) ;									// ��̍��W�ŕ\�����{�b�N�X���J�����̎��E�ɓ����Ă��邩�ǂ����𔻒肷��( �߂�l TRUE:���E�ɓ����Ă��Ȃ�  FALSE:���E�ɓ����Ă��� )

extern	float		NS_GetCameraNear(						void ) ;															// �J������ Near �N���b�v�ʂ̋������擾����
extern	double		NS_GetCameraNearD(						void ) ;															// �J������ Near �N���b�v�ʂ̋������擾����
extern	float		NS_GetCameraFar(						void ) ;															// �J������ Far �N���b�v�ʂ̋������擾����
extern	double		NS_GetCameraFarD(						void ) ;															// �J������ Far �N���b�v�ʂ̋������擾����

extern	VECTOR		NS_GetCameraPosition(					void ) ;															// �J�����̈ʒu���擾����
extern	VECTOR_D	NS_GetCameraPositionD(					void ) ;															// �J�����̈ʒu���擾����
extern	VECTOR		NS_GetCameraTarget(					void ) ;															// �J�����̒����_���擾����
extern	VECTOR_D	NS_GetCameraTargetD(					void ) ;															// �J�����̒����_���擾����
extern	VECTOR		NS_GetCameraUpVector(					void ) ;															// �J�����̎����ɐ����ȏ�����̃x�N�g�����擾����
extern	VECTOR_D	NS_GetCameraUpVectorD(					void ) ;															// �J�����̎����ɐ����ȏ�����̃x�N�g�����擾����
extern	VECTOR		NS_GetCameraDownVector(				void ) ;															// �J�����̎����ɐ����ȉ������̃x�N�g�����擾����
extern	VECTOR_D	NS_GetCameraDownVectorD(				void ) ;															// �J�����̎����ɐ����ȉ������̃x�N�g�����擾����
extern	VECTOR		NS_GetCameraRightVector(				void ) ;															// �J�����̎����ɐ����ȉE�����̃x�N�g�����擾����
extern	VECTOR_D	NS_GetCameraRightVectorD(				void ) ;															// �J�����̎����ɐ����ȉE�����̃x�N�g�����擾����
extern	VECTOR		NS_GetCameraLeftVector(				void ) ;															// �J�����̎����ɐ����ȍ������̃x�N�g�����擾����
extern	VECTOR_D	NS_GetCameraLeftVectorD(				void ) ;															// �J�����̎����ɐ����ȍ������̃x�N�g�����擾����
extern	VECTOR		NS_GetCameraFrontVector(				void ) ;															// �J�����̌����Ă�������̃x�N�g�����擾����
extern	VECTOR_D	NS_GetCameraFrontVectorD(				void ) ;															// �J�����̌����Ă�������̃x�N�g�����擾����
extern	VECTOR		NS_GetCameraBackVector(				void ) ;															// �J�����̌������̃x�N�g�����擾����
extern	VECTOR_D	NS_GetCameraBackVectorD(				void ) ;															// �J�����̌������̃x�N�g�����擾����
extern	float		NS_GetCameraAngleHRotate(				void ) ;															// �J�����̐��������̌������擾����
extern	double		NS_GetCameraAngleHRotateD(				void ) ;															// �J�����̐��������̌������擾����
extern	float		NS_GetCameraAngleVRotate(				void ) ;															// �J�����̐��������̌������擾����
extern	double		NS_GetCameraAngleVRotateD(				void ) ;															// �J�����̐��������̌������擾����
extern	float		NS_GetCameraAngleTRotate(				void ) ;															// �J�����̌����̔P��p�x���擾����
extern	double		NS_GetCameraAngleTRotateD(				void ) ;															// �J�����̌����̔P��p�x���擾����

extern	MATRIX		NS_GetCameraViewMatrix(				void ) ;															// �r���[�s����擾����
extern	MATRIX_D	NS_GetCameraViewMatrixD(				void ) ;															// �r���[�s����擾����
extern	MATRIX		NS_GetCameraBillboardMatrix(			void ) ;															// �r���{�[�h�s����擾����
extern	MATRIX_D	NS_GetCameraBillboardMatrixD(			void ) ;															// �r���{�[�h�s����擾����
extern	int			NS_GetCameraScreenCenter(				float  *x, float  *y ) ;											// ��ʏ�ɂ�����J���������Ă���f���̒��S�̍��W���擾����
extern	int			NS_GetCameraScreenCenterD(				double *x, double *y ) ;											// ��ʏ�ɂ�����J���������Ă���f���̒��S�̍��W���擾����
extern	float		NS_GetCameraFov(						void ) ;															// �J�����̎���p���擾����
extern	double		NS_GetCameraFovD(						void ) ;															// �J�����̎���p���擾����
extern	float		NS_GetCameraSize(						void ) ;															// �J�����̎���T�C�Y���擾����
extern	double		NS_GetCameraSizeD(						void ) ;															// �J�����̎���T�C�Y���擾����
extern	MATRIX		NS_GetCameraProjectionMatrix(			void ) ;															// �ˉe�s����擾����
extern	MATRIX_D	NS_GetCameraProjectionMatrixD(			void ) ;															// �ˉe�s����擾����
extern	float		NS_GetCameraDotAspect(					void ) ;															// �J�����̃h�b�g�A�X�y�N�g��𓾂�
extern	double		NS_GetCameraDotAspectD(				void ) ;															// �J�����̃h�b�g�A�X�y�N�g��𓾂�
extern	MATRIX		NS_GetCameraViewportMatrix(			void ) ;															// �r���[�|�[�g�s����擾����
extern	MATRIX_D	NS_GetCameraViewportMatrixD(			void ) ;															// �r���[�|�[�g�s����擾����
extern	MATRIX		NS_GetCameraAPIViewportMatrix(			void ) ;															// Direct3D�Ŏ����K�p�����r���[�|�[�g�s����擾����
extern	MATRIX_D	NS_GetCameraAPIViewportMatrixD(		void ) ;															// Direct3D�Ŏ����K�p�����r���[�|�[�g�s����擾����

// ���C�g�֌W�֐�
extern	int			NS_SetUseLighting(				int Flag ) ;																// ���C�e�B���O�v�Z�@�\���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetMaterialUseVertDifColor( int UseFlag ) ;																// �R�c�}�`�`��̃��C�e�B���O�v�Z�ɒ��_�J���[�̃f�B�t���[�Y�J���[���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetMaterialUseVertSpcColor( int UseFlag ) ;																// �R�c�}�`�`��̃��C�e�B���O�v�Z�ɒ��_�J���[�̃X�y�L�����J���[���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetMaterialParam(			MATERIALPARAM Material ) ;													// �R�c�}�`�`��̃��C�e�B���O�v�Z�Ɏg�p����}�e���A���p�����[�^��ݒ肷��
extern	int			NS_SetUseSpecular(				int UseFlag ) ;																// �R�c�}�`�`��ɃX�y�L�������g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetGlobalAmbientLight(		COLOR_F Color ) ;															// �O���[�o���A���r�G���g���C�g�J���[��ݒ肷��
extern	int			NS_SetUseLightAngleAttenuation( int UseFlag ) ;																// �R�c�`��̃��C�e�B���O�v�Z�Ŋp�x�������s�����ǂ�����ݒ肷��( TRUE:�p�x�������s��( �f�t�H���g )  FALSE:�p�x�������s��Ȃ� )

extern	int			NS_ChangeLightTypeDir(			VECTOR Direction ) ;														// ���C�g�̃^�C�v���f�B���N�V���i�����C�g�ɂ���
extern	int			NS_ChangeLightTypeSpot(		VECTOR Position, VECTOR Direction, float OutAngle, float InAngle, float Range, float Atten0, float Atten1, float Atten2 ) ;	// ���C�g�̃^�C�v���X�|�b�g���C�g�ɂ���
extern	int			NS_ChangeLightTypePoint(		VECTOR Position, float Range, float Atten0, float Atten1, float Atten2 ) ;	// ���C�g�̃^�C�v���|�C���g���C�g�ɂ���
extern	int			NS_SetLightEnable(				int EnableFlag ) ;															// ���C�g�̗L���A�������Z�b�g����
extern	int			NS_SetLightDifColor(			COLOR_F Color ) ;															// ���C�g�̃f�B�t���[�Y�J���[��ݒ肷��
extern	int			NS_SetLightSpcColor(			COLOR_F Color ) ;															// ���C�g�̃X�y�L�����J���[��ݒ肷��
extern	int			NS_SetLightAmbColor(			COLOR_F Color ) ;															// ���C�g�̃A���r�G���g�J���[��ݒ肷��
extern	int			NS_SetLightDirection(			VECTOR Direction ) ;														// ���C�g�̕�����ݒ肷��
extern	int			NS_SetLightPosition(			VECTOR Position ) ;															// ���C�g�̈ʒu��ݒ肷��
extern	int			NS_SetLightRangeAtten(			float Range, float Atten0, float Atten1, float Atten2 ) ;					// ���C�g�̋��������p�����[�^��ݒ肷��( �L�������A���������W���O�A�P�A�Q )
extern	int			NS_SetLightAngle(				float OutAngle, float InAngle ) ;											// ���C�g�̃X�|�b�g���C�g�̃p�����[�^��ݒ肷��( �O���R�[���p�x�A�����R�[���p�x )
extern	int			NS_GetLightType(				void ) ;																	// ���C�g�̃^�C�v���擾����( �߂�l�� DX_LIGHTTYPE_DIRECTIONAL �� )
extern	int			NS_GetLightEnable(				void ) ;																	// ���C�g���ʂ̗L���A�������擾����( TRUE:�L��  FALSE:���� )
extern	COLOR_F		NS_GetLightDifColor(			void ) ;																	// ���C�g�̃f�B�t���[�Y�J���[���擾����
extern	COLOR_F		NS_GetLightSpcColor(			void ) ;																	// ���C�g�̃X�y�L�����J���[���擾����
extern	COLOR_F		NS_GetLightAmbColor(			void ) ;																	// ���C�g�̃A���r�G���g�J���[���擾����
extern	VECTOR		NS_GetLightDirection(			void ) ;																	// ���C�g�̕������擾����
extern	VECTOR		NS_GetLightPosition(			void ) ;																	// ���C�g�̈ʒu���擾����
extern	int			NS_GetLightRangeAtten(			float *Range, float *Atten0, float *Atten1, float *Atten2 )	;				// ���C�g�̋��������p�����[�^���擾����( �L�������A���������W���O�A�P�A�Q )
extern	int			NS_GetLightAngle(				float *OutAngle, float *InAngle ) ;											// ���C�g�̃X�|�b�g���C�g�̃p�����[�^���擾����( �O���R�[���p�x�A�����R�[���p�x )
extern	int			NS_SetLightUseShadowMap(		int SmSlotIndex, int UseFlag ) ;											// �f�t�H���g���C�g�� SetUseShadowMap �Ŏw�肵���V���h�E�}�b�v��K�p���邩�ǂ�����ݒ肷��( SmSlotIndex:�V���h�E�}�b�v�X���b�g( SetUseShadowMap �̑������ɐݒ肷��l ) UseFlag:�K�p�ɂ��邩�ǂ����̃t���O( TRUE:�K�p����( �f�t�H���g )  FALSE:�K�p���Ȃ� ) )

extern	int			NS_CreateDirLightHandle(       VECTOR Direction ) ;														// �f�B���N�V���i�����C�g�n���h�����쐬����
extern	int			NS_CreateSpotLightHandle(      VECTOR Position, VECTOR Direction, float OutAngle, float InAngle, float Range, float Atten0, float Atten1, float Atten2 ) ;	// �X�|�b�g���C�g�n���h�����쐬����
extern	int			NS_CreatePointLightHandle(     VECTOR Position, float Range, float Atten0, float Atten1, float Atten2 ) ;	// �|�C���g���C�g�n���h�����쐬����
extern	int			NS_DeleteLightHandle(          int LHandle ) ;																// ���C�g�n���h�����폜����
extern	int			NS_DeleteLightHandleAll(       void ) ;																	// ���C�g�n���h����S�č폜����
extern	int			NS_SetLightTypeHandle(         int LHandle, int LightType ) ;												// ���C�g�n���h���̃��C�g�̃^�C�v��ύX����( DX_LIGHTTYPE_DIRECTIONAL �� )
extern	int			NS_SetLightEnableHandle(       int LHandle, int EnableFlag ) ;												// ���C�g�n���h���̃��C�g���ʂ̗L���A������ݒ肷��( TRUE:�L��  FALSE:���� )
extern	int			NS_SetLightDifColorHandle(     int LHandle, COLOR_F Color ) ;												// ���C�g�n���h���̃��C�g�̃f�B�t���[�Y�J���[��ݒ肷��
extern	int			NS_SetLightSpcColorHandle(     int LHandle, COLOR_F Color ) ;												// ���C�g�n���h���̃��C�g�̃X�y�L�����J���[��ݒ肷��
extern	int			NS_SetLightAmbColorHandle(     int LHandle, COLOR_F Color ) ;												// ���C�g�n���h���̃��C�g�̃A���r�G���g�J���[��ݒ肷��
extern	int			NS_SetLightDirectionHandle(    int LHandle, VECTOR Direction ) ;											// ���C�g�n���h���̃��C�g�̕�����ݒ肷��
extern	int			NS_SetLightPositionHandle(     int LHandle, VECTOR Position ) ;											// ���C�g�n���h���̃��C�g�̈ʒu��ݒ肷��
extern	int			NS_SetLightRangeAttenHandle(   int LHandle, float Range, float Atten0, float Atten1, float Atten2 ) ;		// ���C�g�n���h���̃��C�g�̋��������p�����[�^��ݒ肷��( �L�������A���������W���O�A�P�A�Q )
extern	int			NS_SetLightAngleHandle(        int LHandle, float OutAngle, float InAngle ) ;								// ���C�g�n���h���̃��C�g�̃X�|�b�g���C�g�̃p�����[�^��ݒ肷��( �O���R�[���p�x�A�����R�[���p�x )
extern	int			NS_SetLightUseShadowMapHandle(	int LHandle, int SmSlotIndex, int UseFlag ) ;								// ���C�g�n���h���̃��C�g�� SetUseShadowMap �Ŏw�肵���V���h�E�}�b�v��K�p���邩�ǂ�����ݒ肷��( SmSlotIndex:�V���h�E�}�b�v�X���b�g( SetUseShadowMap �̑������ɐݒ肷��l ) UseFlag:�K�p�ɂ��邩�ǂ����̃t���O( TRUE:�K�p����( �f�t�H���g )  FALSE:�K�p���Ȃ� ) )
extern	int			NS_GetLightTypeHandle(         int LHandle ) ;																// ���C�g�n���h���̃��C�g�̃^�C�v���擾����( �߂�l�� DX_LIGHTTYPE_DIRECTIONAL �� )
extern	int			NS_GetLightEnableHandle(       int LHandle ) ;																// ���C�g�n���h���̃��C�g���ʂ̗L���A�������擾����( TRUE:�L��  FALSE:���� )
extern	COLOR_F		NS_GetLightDifColorHandle(     int LHandle ) ;																// ���C�g�n���h���̃��C�g�̃f�B�t���[�Y�J���[���擾����
extern	COLOR_F		NS_GetLightSpcColorHandle(     int LHandle ) ;																// ���C�g�n���h���̃��C�g�̃X�y�L�����J���[���擾����
extern	COLOR_F		NS_GetLightAmbColorHandle(     int LHandle ) ;																// ���C�g�n���h���̃��C�g�̃A���r�G���g�J���[���擾����
extern	VECTOR		NS_GetLightDirectionHandle(    int LHandle ) ;																// ���C�g�n���h���̃��C�g�̕������擾����
extern	VECTOR		NS_GetLightPositionHandle(     int LHandle ) ;																// ���C�g�n���h���̃��C�g�̈ʒu���擾����
extern	int			NS_GetLightRangeAttenHandle(   int LHandle, float *Range, float *Atten0, float *Atten1, float *Atten2 ) ;	// ���C�g�n���h���̃��C�g�̋��������p�����[�^���擾����( �L�������A���������W���O�A�P�A�Q )
extern	int			NS_GetLightAngleHandle(        int LHandle, float *OutAngle, float *InAngle ) ;							// ���C�g�n���h���̃��C�g�̃X�|�b�g���C�g�̃p�����[�^���擾����( �O���R�[���p�x�A�����R�[���p�x )

extern	int			NS_GetEnableLightHandleNum(	void ) ;																	// �L���ɂȂ��Ă��郉�C�g�n���h���̐����擾����
extern	int			NS_GetEnableLightHandle(		int Index ) ;																// �L���ɂȂ��Ă��郉�C�g�n���h�����擾����

// �F���擾�p�֐�
extern	int			NS_GetTexFormatIndex(			const IMAGEFORMATDESC *Format ) ;																								// �e�N�X�`���t�H�[�}�b�g�̃C���f�b�N�X�𓾂�
extern	int			NS_ColorKaiseki(				const void *PixelData, COLORDATA* ColorData ) ;																					// �F�r�b�g�����












// DxMask.cpp �֐��v���g�^�C�v�錾

#ifndef DX_NON_MASK

// �}�X�N�֌W 
extern	int			NS_CreateMaskScreen(				void ) ;																						// �}�X�N�X�N���[�����쐬����
extern	int			NS_DeleteMaskScreen(				void ) ;																						// �}�X�N�X�N���[�����폜����
extern	int			NS_DrawMaskToDirectData(			int x, int y, int Width, int Height, const void *MaskData , int TransMode ) ;					// �}�X�N�̃f�[�^�𒼐ڃZ�b�g
extern	int			NS_DrawFillMaskToDirectData(		int x1, int y1, int x2, int y2,  int Width, int Height, const void *MaskData ) ;				// �}�X�N�̃f�[�^�𒼐ڃ}�X�N��ʑS�̂ɕ`�悷��

extern	int			NS_SetUseMaskScreenFlag(			int ValidFlag ) ;																				// �}�X�N�g�p���[�h��ύX
extern	int			NS_GetUseMaskScreenFlag(			void ) ;																						// �}�X�N�g�p���[�h�̎擾
extern	int			NS_FillMaskScreen(					int Flag ) ;																					// �}�X�N�X�N���[�����w��̐F�œh��Ԃ�
extern	int			NS_SetMaskScreenGraph(				int GraphHandle ) ;																				// �}�X�N�X�N���[���Ƃ��Ďg�p����O���t�B�b�N�̃n���h����ݒ肷��A-1��n���Ɖ���( �����œn���O���t�B�b�N�n���h���� MakeScreen �ō쐬�����u�A���t�@�`�����l���t���̕`��Ώۂɂł���O���t�B�b�N�n���h���v�ł���K�v������܂�( �A���t�@�`�����l�����}�X�N�Ɏg�p����܂� ) )
extern	int			NS_SetMaskScreenGraphUseChannel(	int UseChannel /* DX_MASKGRAPH_CH_A �� */ ) ;													// �}�X�N�X�N���[���Ƃ��Ďg�p����O���t�B�b�N�́A�ǂ̃`�����l�����}�X�N�Ƃ��Ďg�p���邩��ݒ肷��( �f�t�H���g�� DX_MASKGRAPH_CH_A�A ���ADX_MASKGRAPH_CH_A�ȊO���g�p����ꍇ�̓O���t�B�b�N�X�f�o�C�X���V�F�[�_�[���f��2.0�ȍ~�ɑΉ����Ă���K�v������܂� )

extern	int			NS_InitMask(						void ) ;																						// �}�X�N�f�[�^������������
extern	int			NS_MakeMask(						int Width, int Height ) ;																		// �}�X�N�f�[�^�̒ǉ�
extern	int			NS_GetMaskSize(					int *WidthBuf, int *HeightBuf, int MaskHandle ) ;												// �}�X�N�̑傫���𓾂� 
extern	int			NS_GetMaskBaseImageInfo(				BASEIMAGE *BaseImage, int MaskHandle ) ;														// �}�X�N�n���h�������}�X�N�C���[�W��BASEIMAGE�f�[�^���擾����
extern	int			NS_SetDataToMask(					int Width, int Height, const void *MaskData, int MaskHandle ) ;										// �}�X�N�̃f�[�^���}�X�N�ɓ]������
extern	int			NS_DeleteMask(						int MaskHandle ) ;																				// �}�X�N�f�[�^���폜
extern	int			NS_BmpBltToMask(					HBITMAP Bmp, int BmpPointX, int BmpPointY, int MaskHandle ) ;									// �}�X�N�f�[�^�ɂa�l�o�f�[�^���}�X�N�f�[�^�ƌ����Ăē]��
extern	int			NS_GraphImageBltToMask(			const BASEIMAGE *BaseImage, int ImageX, int ImageY, int MaskHandle ) ;								// �}�X�N�n���h����BASEIMAGE�f�[�^��]������
extern	int			NS_LoadMask(						const TCHAR *FileName ) ;																		// �}�X�N�f�[�^�����[�h����
extern	int			NS_LoadMaskWithStrLen(					const TCHAR *FileName, size_t FileNameLength ) ;																			// �摜�t�@�C����ǂݍ��݃}�X�N�n���h�����쐬����
extern	int			NS_LoadDivMask(						const TCHAR *FileName,                        int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleArray ) ;	// �摜�t�@�C���𕪊��ǂݍ��݂��ă}�X�N�n���h�����쐬����
extern	int			NS_LoadDivMaskWithStrLen(				const TCHAR *FileName, size_t FileNameLength, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleArray ) ;	// �摜�t�@�C���𕪊��ǂݍ��݂��ă}�X�N�n���h�����쐬����
extern	int			NS_CreateMaskFromMem(				const void *FileImage, int FileImageSize ) ;																		// ��������ɂ���摜�t�@�C���C���[�W��ǂݍ��݃}�X�N�n���h�����쐬����
extern	int			NS_CreateDivMaskFromMem(			const void *FileImage, int FileImageSize, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleArray ) ;	// ��������ɂ���摜�t�@�C���C���[�W�𕪊��ǂݍ��݂��ă}�X�N�n���h�����쐬����
extern	int			NS_DrawMask(						int x, int y, int MaskHandle, int TransMode ) ;													// �}�X�N���Z�b�g����
#ifndef DX_NON_FONT
extern	int			NS_DrawFormatStringMask(			int x, int y, int Flag,                 const TCHAR *FormatString, ... ) ;						// �����w�肠��̕�������}�X�N�X�N���[���ɕ`�悷��
extern	int			NS_DrawFormatStringMaskToHandle(	int x, int y, int Flag, int FontHandle, const TCHAR *FormatString, ... ) ;						// �����w�肠��̕�������}�X�N�X�N���[���ɕ`�悷��(�t�H���g�n���h���w���)( SetFontCacheToTextureFlag( FALSE ) ; �ɂ��č쐬�����t�H���g�n���h���̂ݎg�p�\ )
extern	int			NS_DrawStringMask(					int x, int y, int Flag,                 const TCHAR *String ) ;									// ��������}�X�N�X�N���[���ɕ`�悷��
extern	int			NS_DrawNStringMask(					int x, int y, int Flag,                 const TCHAR *String, size_t StringLength ) ;			// ��������}�X�N�X�N���[���ɕ`�悷��
extern	int			NS_DrawStringMaskToHandle(			int x, int y, int Flag, int FontHandle, const TCHAR *String ) ;									// ��������}�X�N�X�N���[���ɕ`�悷��( �t�H���g�n���h���w��� )( SetFontCacheToTextureFlag( FALSE ) ; �ɂ��č쐬�����t�H���g�n���h���̂ݎg�p�\ )
extern	int			NS_DrawNStringMaskToHandle(			int x, int y, int Flag, int FontHandle, const TCHAR *String, size_t StringLength ) ;			// ��������}�X�N�X�N���[���ɕ`�悷��( �t�H���g�n���h���w��� )( SetFontCacheToTextureFlag( FALSE ) ; �ɂ��č쐬�����t�H���g�n���h���̂ݎg�p�\ )
#endif // DX_NON_FONT
extern	int			NS_DrawFillMask(					int x1, int y1, int x2, int y2, int MaskHandle ) ;												// �w��̃}�X�N����ʂ����ς��ɓW�J����	
extern	int			NS_SetMaskReverseEffectFlag(		int ReverseFlag ) ;																				// �}�X�N�̐��l�ɑ΂�����ʂ��t�]������

extern	int			NS_GetMaskScreenData(				int x1, int y1, int x2, int y2, int MaskHandle ) ;												// �}�X�N��ʏ�̕`���Ԃ��擾����
extern	int			NS_GetMaskUseFlag(					void ) ;																						// �}�X�N�X�N���[�����g�p�����t���O�̎擾

#endif // DX_NON_MASK

#endif // DX_NOTUSE_DRAWFUNCTION













// DxFont.cpp �֐��v���g�^�C�v�錾

#ifndef DX_NON_FONT

// �t�H���g�A������`��֌W�֐�
extern	int			NS_EnumFontName(                           TCHAR *NameBuffer, int NameBufferNum, int JapanOnlyFlag = TRUE ) ;								// �g�p�\�ȃt�H���g�̖��O�����ׂė񋓂���( NameBuffer �� 64�o�C�g��؂�Ŗ��O���i�[����܂� )
extern	int			NS_EnumFontNameEx(                         TCHAR *NameBuffer, int NameBufferNum, int CharSet = -1 /* DX_CHARSET_DEFAULT �� */ ) ;			// �g�p�\�ȃt�H���g�̖��O�����ׂė񋓂���( NameBuffer �� 64�o�C�g��؂�Ŗ��O���i�[����܂� )
extern	int			NS_EnumFontNameEx2(						TCHAR *NameBuffer, int NameBufferNum, const TCHAR *EnumFontName, int CharSet = -1 /* DX_CHARSET_DEFAULT �� */ ) ;	// �w��̃t�H���g���̃t�H���g��񋓂���
extern	int			NS_EnumFontNameEx2WithStrLen(				TCHAR *NameBuffer, int NameBufferNum, const TCHAR *EnumFontName, size_t EnumFontNameLength, int CharSet = -1 /* DX_CHARSET_DEFAULT �� */ ) ;	// �w��̃t�H���g���̃t�H���g��񋓂���
extern	int			NS_CheckFontName(							const TCHAR *FontName,                        int CharSet = -1 /* DX_CHARSET_DEFAULT �� */ ) ;												// �w��̃t�H���g���̃t�H���g�����݂��邩�ǂ������`�F�b�N����( �߂�l  TRUE:���݂���  FALSE:���݂��Ȃ� )
extern	int			NS_CheckFontNameWithStrLen(				const TCHAR *FontName, size_t FontNameLength, int CharSet = -1 /* DX_CHARSET_DEFAULT �� */ ) ;												// �w��̃t�H���g���̃t�H���g�����݂��邩�ǂ������`�F�b�N����( �߂�l  TRUE:���݂���  FALSE:���݂��Ȃ� )

extern	int			NS_InitFontToHandle(                       void ) ;																						// �t�H���g�̃X�e�[�^�X���f�t�H���g�ɖ߂�

extern	int			NS_CreateFontToHandle(                     const TCHAR *FontName, int Size, int Thick, int FontType = -1 , int CharSet = -1 , int EdgeSize = -1 , int Italic = FALSE , int Handle = -1 ) ;			// �V�����t�H���g�f�[�^���쐬
extern	int			NS_CreateFontToHandleWithStrLen(			const TCHAR *FontName, size_t FontNameLength, int Size, int Thick, int FontType = -1 , int CharSet = -1 , int EdgeSize = -1 , int Italic = FALSE , int Handle = -1 ) ;		// �t�H���g�n���h�����쐬����
extern	int			NS_LoadFontDataToHandle(					const TCHAR *FileName,                            int EdgeSize = 0 ) ;							// �t�H���g�f�[�^�t�@�C������t�H���g�n���h�����쐬����
extern	int			NS_LoadFontDataToHandleWithStrLen(			const TCHAR *FileName, size_t FileNameLength,     int EdgeSize = 0 ) ;							// �t�H���g�f�[�^�t�@�C������t�H���g�n���h�����쐬����
extern	int			NS_LoadFontDataFromMemToHandle(			const void *FontDataImage, int FontDataImageSize, int EdgeSize = -1 ) ;		// ��������̃t�H���g�f�[�^�t�@�C���C���[�W����t�H���g�n���h�����쐬����
extern	int			NS_SetFontSpaceToHandle(                   int Pixel, int FontHandle ) ;																	// ���Ԃ�ύX����
extern	int			NS_SetFontLineSpaceToHandle(               int Pixel, int FontHandle ) ;																	// �t�H���g�n���h���̍s�Ԃ�ύX����
extern	int			NS_SetFontCharCodeFormatToHandle(			int CharCodeFormat /* DX_CHARCODEFORMAT_SHIFTJIS �� */ , int FontHandle ) ;											// �w��̃t�H���g�n���h�����g�p����֐��̈����ɓn��������̕����R�[�h�`����ݒ肷��( UNICODE�łł͖��� )
extern	int			NS_SetDefaultFontState(                    const TCHAR *FontName, int Size, int Thick, int FontType = -1 , int CharSet = -1 , int EdgeSize = -1 , int Italic = FALSE ) ;	// �f�t�H���g�t�H���g�n���h���̐ݒ��ύX����
extern	int			NS_SetDefaultFontStateWithStrLen(          const TCHAR *FontName, size_t FontNameLength, int Size, int Thick, int FontType = -1 , int CharSet = -1 , int EdgeSize = -1 , int Italic = FALSE ) ;	// �f�t�H���g�t�H���g�n���h���̐ݒ��ύX����
extern	int			NS_DeleteFontToHandle(                     int FontHandle ) ;																				// �t�H���g�L���b�V���̐�����I������
extern	int			NS_SetFontLostFlag(                        int FontHandle, int *LostFlag ) ;																// ������� TRUE �ɂ���t���O�ւ̃|�C���^��ݒ肷��
extern	int			NS_AddFontImageToHandle(					int FontHandle, const TCHAR *Char, int GrHandle, int DrawX, int DrawY, int AddX ) ;				// �w��̕����̑���ɕ`�悷��O���t�B�b�N�n���h����o�^����
extern	int			NS_AddFontImageToHandleWithStrLen(			int FontHandle, const TCHAR *Char, size_t CharLength, int GrHandle, int DrawX, int DrawY, int AddX ) ;	// �w��̕����̑���ɕ`�悷��O���t�B�b�N�n���h����o�^����
extern	int			NS_SubFontImageToHandle(					int FontHandle, const TCHAR *Char                    ) ;												// �w��̕����̑���ɕ`�悷��O���t�B�b�N�n���h���̓o�^����������
extern	int			NS_SubFontImageToHandleWithStrLen(			int FontHandle, const TCHAR *Char, size_t CharLength ) ;												// �w��̕����̑���ɕ`�悷��O���t�B�b�N�n���h���̓o�^����������
extern	int			NS_AddSubstitutionFontToHandle(			int FontHandle, int SubstitutionFontHandle, int DrawX, int DrawY ) ;							// ��փt�H���g�n���h����o�^����
extern	int			NS_SubSubstitutionFontToHandle(			int FontHandle, int SubstitutionFontHandle ) ;													// ��փt�H���g�n���h���̓o�^����������

extern	int			NS_SetFontSize(                            int FontSize ) ;																				// �`�悷��t�H���g�̃T�C�Y���Z�b�g����
extern	int			NS_SetFontThickness(                       int ThickPal ) ;																				// �t�H���g�̑������Z�b�g
extern	int			NS_SetFontSpace(                           int Pixel ) ;																					// ���Ԃ�ύX����
extern	int			NS_GetFontSpace(                           void ) ;																						// �f�t�H���g�t�H���g�n���h���̎��Ԃ��擾����
extern	int			NS_SetFontLineSpace(                       int Pixel ) ;																					// �f�t�H���g�t�H���g�n���h���̍s�Ԃ�ύX����
extern	int			NS_GetFontLineSpace(                       void ) ;																						// �f�t�H���g�t�H���g�n���h���̍s�Ԃ��擾����
extern	int			NS_SetFontCharCodeFormat(					int CharCodeFormat /* DX_CHARCODEFORMAT_SHIFTJIS �� */ ) ;										// �f�t�H���g�t�H���g�n���h�����g�p����֐��̈����ɓn��������̕����R�[�h�`����ݒ肷��( UNICODE�łł͖��� )

extern	int			NS_SetFontCacheToTextureFlag(              int Flag ) ;																					// �t�H���g�̃L���b�V���Ƀe�N�X�`�����g�p���邩�A�t���O���Z�b�g����
extern	int			NS_SetFontChacheToTextureFlag(             int Flag ) ;																					// �t�H���g�̃L���b�V���Ƀe�N�X�`�����g�p���邩�A�t���O���Z�b�g����(�뎚��)
extern	int			NS_SetFontCacheCharNum(                    int CharNum ) ;																					// �t�H���g�L���b�V���ŃL���b�V���ł��镶�������w�肷��
extern	int			NS_ChangeFont(                             const TCHAR *FontName, int CharSet = -1 /* DX_CHARSET_SHFTJIS �� */ ) ;							// �t�H���g��ύX
extern	int			NS_ChangeFontWithStrLen(                   const TCHAR *FontName, size_t FontNameLength, int CharSet = -1 /* DX_CHARSET_SHFTJIS �� */ ) ;	// �f�t�H���g�t�H���g�n���h���Ŏg�p����t�H���g��ύX
extern	int			NS_ChangeFontFromHandle(					int FontHandle ) ;																				// �f�t�H���g�t�H���g�n���h���Ƃ��Ďg�p����t�H���g�n���h����ύX����
extern	int			NS_ChangeFontType(                         int FontType ) ;																				// �t�H���g�^�C�v�̕ύX
extern	const TCHAR *NS_GetFontName(							void ) ;																						// �f�t�H���g�t�H���g�n���h���̃t�H���g�����擾����
// FontCacheStringDraw �� DrawString ���g���Ă�������
extern	int			NS_FontCacheStringDrawToHandle(            int x, int y, const TCHAR *StrData, unsigned int Color, unsigned int EdgeColor, BASEIMAGE *DestImage, const RECT *ClipRect /* NULL �� */ , int FontHandle, int VerticalFlag = FALSE , SIZE *DrawSizeP = NULL ) ;
extern	int			NS_FontCacheStringDrawToHandleWithStrLen(  int x, int y, const TCHAR *StrData, size_t StrDataLength, unsigned int Color, unsigned int EdgeColor, BASEIMAGE *DestImage, const RECT *ClipRect /* NULL �� */ , int FontHandle, int VerticalFlag = FALSE , SIZE *DrawSizeP = NULL ) ;
extern	int			NS_FontBaseImageBlt(                       int x, int y, const TCHAR *StrData,                       BASEIMAGE *DestImage, BASEIMAGE *DestEdgeImage,                 int VerticalFlag = FALSE ) ;	// ��{�C���[�W�ɕ������`�悷��( �f�t�H���g�t�H���g�n���h�����g�p���� )
extern	int			NS_FontBaseImageBltWithStrLen(             int x, int y, const TCHAR *StrData, size_t StrDataLength, BASEIMAGE *DestImage, BASEIMAGE *DestEdgeImage,                 int VerticalFlag = FALSE ) ;	// ��{�C���[�W�ɕ������`�悷��( �f�t�H���g�t�H���g�n���h�����g�p���� )
extern	int			NS_FontBaseImageBltToHandle(               int x, int y, const TCHAR *StrData,                       BASEIMAGE *DestImage, BASEIMAGE *DestEdgeImage, int FontHandle, int VerticalFlag = FALSE ) ;	// ��{�C���[�W�ɕ������`�悷��
extern	int			NS_FontBaseImageBltToHandleWithStrLen(     int x, int y, const TCHAR *StrData, size_t StrDataLength, BASEIMAGE *DestImage, BASEIMAGE *DestEdgeImage, int FontHandle, int VerticalFlag = FALSE ) ;	// ��{�C���[�W�ɕ������`�悷��

extern	const TCHAR *NS_GetFontNameToHandle(					int FontHandle ) ;																				// �t�H���g�n���h���̃t�H���g�����擾����
extern	int			NS_GetFontMaxCacheCharNumToHandle(			int FontHandle ) ;																				// �t�H���g�n���h���̃L���b�V���ł��镶���̐����擾����
extern	int			NS_GetFontMaxWidth(                        void ) ;																						// �����̍ő啝�𓾂�
extern	int			NS_GetFontMaxWidthToHandle(                int FontHandle ) ;																				// �����̍ő啝�𓾂�
extern	int			NS_GetFontAscent(                          void ) ;																						// �f�t�H���g�t�H���g�n���h���̕`��ʒu����x�[�X���C���܂ł̍������擾����
extern	int			NS_GetFontAscentToHandle(                  int FontHandle ) ;																				// �t�H���g�n���h���̕`��ʒu����x�[�X���C���܂ł̍������擾����
extern	int			NS_GetFontCharInfo(                        int FontHandle, const TCHAR *Char, int *DrawX, int *DrawY, int *NextCharX, int *SizeX, int *SizeY ) ;		// �w��̕����̕`������擾����
extern	int			NS_GetFontCharInfoWithStrLen(              int FontHandle, const TCHAR *Char, size_t CharLength, int *DrawX, int *DrawY, int *NextCharX, int *SizeX, int *SizeY ) ;	// �t�H���g�n���h���̎w��̕����̕`������擾����
extern	int			NS_GetDrawStringWidth(                     const TCHAR *String, int StrLen, int VerticalFlag = FALSE ) ;									// ������̕��𓾂�
extern	int			NS_GetDrawNStringWidth(                    const TCHAR *String, size_t StringLength, int VerticalFlag = FALSE ) ;									// �f�t�H���g�t�H���g�n���h�����g�p����������̕`�敝���擾����
extern	int			NS_GetDrawFormatStringWidth(               const TCHAR *FormatString, ... ) ;																// �����t��������̕`�敝�𓾂�
extern	int			NS_GetDrawStringWidthToHandle(             const TCHAR *String, int StrLen, int FontHandle, int VerticalFlag = FALSE ) ;					// ������̕��𓾂�
extern	int			NS_GetDrawNStringWidthToHandle(            const TCHAR   *String, size_t StringLength, int FontHandle, int VerticalFlag = FALSE ) ;						// �t�H���g�n���h�����g�p����������̕`�敝���擾����
extern	int			NS_GetDrawFormatStringWidthToHandle(       int FontHandle, const TCHAR *FormatString, ... ) ;												// �����t��������̕`�敝�𓾂�
extern	int			NS_GetDrawExtendStringWidth(               double ExRateX, const TCHAR *String, int StrLen, int VerticalFlag = FALSE ) ;					// ������̕��𓾂�
extern	int			NS_GetDrawExtendNStringWidth(              double ExRateX, const TCHAR *String, size_t StringLength, int VerticalFlag = FALSE ) ;					// �f�t�H���g�t�H���g�n���h�����g�p����������̕`�敝���擾����( �g�嗦�t�� )
extern	int			NS_GetDrawExtendFormatStringWidth(         double ExRateX, const TCHAR *FormatString, ... ) ;												// �����t��������̕`�敝�𓾂�
extern	int			NS_GetDrawExtendStringWidthToHandle(       double ExRateX, const TCHAR *String, int StrLen, int FontHandle, int VerticalFlag = FALSE ) ;	// ������̕��𓾂�
extern	int			NS_GetDrawExtendNStringWidthToHandle(      double ExRateX, const TCHAR *String, size_t StringLength, int FontHandle, int VerticalFlag = FALSE ) ;			// �t�H���g�n���h�����g�p����������̕`�敝���擾����
extern	int			NS_GetDrawExtendFormatStringWidthToHandle( double ExRateX, int FontHandle, const TCHAR *FormatString, ... ) ;								// �����t��������̕`�敝�𓾂�
extern	int			NS_GetDrawStringSize(                      int *SizeX, int *SizeY, int *LineCount, const TCHAR *String, int StrLen, int VerticalFlag = FALSE ) ;									// �f�t�H���g�t�H���g�n���h�����g�p����������̕`�敝�E�����E�s�����擾����
extern	int			NS_GetDrawNStringSize(                     int *SizeX, int *SizeY, int *LineCount, const TCHAR *String, size_t StringLength, int VerticalFlag = FALSE ) ;											// �f�t�H���g�t�H���g�n���h�����g�p����������̕`�敝�E�����E�s�����擾����
extern	int			NS_GetDrawFormatStringSize(                int *SizeX, int *SizeY, int *LineCount, const TCHAR *FormatString, ... ) ;																// �f�t�H���g�t�H���g�n���h�����g�p���������t��������̕`�敝�E�����E�s�����擾����
extern	int			NS_GetDrawExtendStringSize(                int *SizeX, int *SizeY, int *LineCount, double ExRateX, double ExRateY, const TCHAR *String, int StrLen, int VerticalFlag = FALSE ) ;	// �f�t�H���g�t�H���g�n���h�����g�p����������̕`�敝�E�����E�s�����擾����( �g�嗦�t�� )
extern	int			NS_GetDrawExtendNStringSize(               int *SizeX, int *SizeY, int *LineCount, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength, int VerticalFlag = FALSE ) ;			// �f�t�H���g�t�H���g�n���h�����g�p����������̕`�敝�E�����E�s�����擾����( �g�嗦�t�� )
extern	int			NS_GetDrawExtendFormatStringSize(          int *SizeX, int *SizeY, int *LineCount, double ExRateX, double ExRateY, const TCHAR *FormatString, ... ) ;								// �f�t�H���g�t�H���g�n���h�����g�p���������t��������̕`�敝�E�����E�s�����擾����( �g�嗦�t�� )
extern	int			NS_GetDrawStringSizeToHandle(              int *SizeX, int *SizeY, int *LineCount, const TCHAR   *String, int StrLen, int FontHandle, int VerticalFlag = FALSE ) ;									// �t�H���g�n���h�����g�p����������̕`�敝�E�����E�s�����擾����
extern	int			NS_GetDrawNStringSizeToHandle(             int *SizeX, int *SizeY, int *LineCount, const TCHAR   *String, size_t StringLength, int FontHandle, int VerticalFlag = FALSE ) ;											// �t�H���g�n���h�����g�p����������̕`�敝�E�����E�s�����擾����
extern	int			NS_GetDrawFormatStringSizeToHandle(        int *SizeX, int *SizeY, int *LineCount, int FontHandle, const TCHAR *FormatString, ... ) ;																// �t�H���g�n���h�����g�p���������t��������̕`�敝�E�����E�s�����擾����
extern	int			NS_GetDrawExtendStringSizeToHandle(        int *SizeX, int *SizeY, int *LineCount, double ExRateX, double ExRateY, const TCHAR *String, int StrLen, int FontHandle, int VerticalFlag = FALSE ) ;	// �t�H���g�n���h�����g�p����������̕`�敝�E�����E�s�����擾����
extern	int			NS_GetDrawExtendNStringSizeToHandle(       int *SizeX, int *SizeY, int *LineCount, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength, int FontHandle, int VerticalFlag = FALSE ) ;				// �t�H���g�n���h�����g�p����������̕`�敝�E�����E�s�����擾����
extern	int			NS_GetDrawExtendFormatStringSizeToHandle(  int *SizeX, int *SizeY, int *LineCount, double ExRateX, double ExRateY, int FontHandle, const TCHAR *FormatString, ... ) ;								// �t�H���g�n���h�����g�p���������t��������̕`�敝�E�����E�s�����擾����
extern	int			NS_GetDrawStringCharInfo(                  DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, const TCHAR *String, int StrLen, int VerticalFlag = FALSE ) ;													// �f�t�H���g�t�H���g�n���h�����g�p����������̂P�������̏����擾����
extern	int			NS_GetDrawNStringCharInfo(                 DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, const TCHAR *String, size_t StringLength, int VerticalFlag = FALSE ) ;									// �f�t�H���g�t�H���g�n���h�����g�p����������̂P�������̏����擾����
extern	int			NS_GetDrawFormatStringCharInfo(            DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, const TCHAR *FormatString, ... ) ;																			// �f�t�H���g�t�H���g�n���h�����g�p���������t��������̂P�������̏����擾����
extern	int			NS_GetDrawExtendStringCharInfo(            DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, double ExRateX, double ExRateY, const TCHAR *String, int StrLen, int VerticalFlag = FALSE ) ;					// �f�t�H���g�t�H���g�n���h�����g�p����������̂P�������̏����擾����
extern	int			NS_GetDrawNStringCharInfoToHandle(         DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, const TCHAR *String, size_t StringLength, int FontHandle, int VerticalFlag = FALSE ) ;									// �t�H���g�n���h�����g�p����������̂P�������̏����擾����
extern	int			NS_GetDrawExtendFormatStringCharInfo(      DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, double ExRateX, double ExRateY, const TCHAR *FormatString, ... ) ;											// �f�t�H���g�t�H���g�n���h�����g�p���������t��������̂P�������̏����擾����
extern	int			NS_GetDrawStringKerningPairInfo(			const TCHAR *PairChar,                        int *KernAmount ) ;								// �f�t�H���g�t�H���g�n���h�����g�p������̕����̃y�A�̃J�[�j���O�����擾����( PairChar:�J�[�j���O���𒲂ׂ�y�A�ƂȂ�2�����̕�����( 2�����ȏ゠���Ă��擪��2���������g�p����܂� )  KernAmount:2�����ڂ̕�������{�̈ʒu���炸�炷�h�b�g����������int�^�ϐ��̃A�h���X )
extern	int			NS_GetDrawStringKerningPairInfoWithStrLen(	const TCHAR *PairChar, size_t PairCharLength, int *KernAmount ) ;								// �f�t�H���g�t�H���g�n���h�����g�p������̕����̃y�A�̃J�[�j���O�����擾����( PairChar:�J�[�j���O���𒲂ׂ�y�A�ƂȂ�2�����̕�����( 2�����ȏ゠���Ă��擪��2���������g�p����܂� )  KernAmount:2�����ڂ̕�������{�̈ʒu���炸�炷�h�b�g����������int�^�ϐ��̃A�h���X )
extern	int			NS_GetDrawStringCharInfoToHandle(          DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, const TCHAR *String, int StrLen, int FontHandle, int VerticalFlag = FALSE ) ;												// �t�H���g�n���h�����g�p����������̂P�������̏����擾����
extern	int			NS_GetDrawExtendNStringCharInfoToHandle(   DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength, int FontHandle, int VerticalFlag = FALSE ) ;	// �t�H���g�n���h�����g�p����������̂P�������̏����擾����
extern	int			NS_GetDrawFormatStringCharInfoToHandle(    DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, int FontHandle, const TCHAR *FormatString, ... ) ;																		// �t�H���g�n���h�����g�p���������t��������̂P�������̏����擾����
extern	int			NS_GetDrawExtendStringCharInfoToHandle(    DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, double ExRateX, double ExRateY, const TCHAR *String, int StrLen, int FontHandle, int VerticalFlag = FALSE ) ;				// �t�H���g�n���h�����g�p����������̂P�������̏����擾����
extern	int			NS_GetDrawExtendNStringCharInfo(           DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength, int VerticalFlag = FALSE ) ;	// �f�t�H���g�t�H���g�n���h�����g�p����������̂P�������̏����擾����
extern	int			NS_GetDrawExtendFormatStringCharInfoToHandle(  DRAWCHARINFO *InfoBuffer, size_t InfoBufferSize, double ExRateX, double ExRateY, int FontHandle, const TCHAR *FormatString, ... ) ;										// �t�H���g�n���h�����g�p���������t��������̂P�������̏����擾����
extern	int			NS_GetDrawStringKerningPairInfoToHandle(	        const TCHAR *PairChar,                        int *KernAmount, int FontHandle ) ;		// �t�H���g�n���h�����g�p������̕����̃y�A�̃J�[�j���O�����擾����( PairChar:�J�[�j���O���𒲂ׂ�y�A�ƂȂ�2�����̕�����( 2�����ȏ゠���Ă��擪��2���������g�p����܂� )  KernAmount:2�����ڂ̕�������{�̈ʒu���炸�炷�h�b�g����������int�^�ϐ��̃A�h���X )
extern	int			NS_GetDrawStringKerningPairInfoToHandleWithStrLen(	const TCHAR *PairChar, size_t PairCharLength, int *KernAmount, int FontHandle ) ;		// �t�H���g�n���h�����g�p������̕����̃y�A�̃J�[�j���O�����擾����( PairChar:�J�[�j���O���𒲂ׂ�y�A�ƂȂ�2�����̕�����( 2�����ȏ゠���Ă��擪��2���������g�p����܂� )  KernAmount:2�����ڂ̕�������{�̈ʒu���炸�炷�h�b�g����������int�^�ϐ��̃A�h���X )

extern	int			NS_GetFontStateToHandle(                   TCHAR *FontName, int *Size, int *Thick, int FontHandle, int *FontType = NULL , int *CharSet = NULL , int *EdgeSize = NULL , int *Italic = NULL ) ;		// �t�H���g�n���h���̏����擾����
extern	int			NS_GetDefaultFontHandle(                   void ) ;																						// �f�t�H���g�̃t�H���g�̃n���h���𓾂�
extern	int			NS_GetFontMaxCacheCharNum(					void ) ;																								// �f�t�H���g�t�H���g�n���h���̃L���b�V���ł��镶���̐����擾����
extern	int			NS_GetFontChacheToTextureFlag(             void ) ;																						// �t�H���g�Ƀe�N�X�`���L���b�V�����g�p���邩�ǂ������擾����(�뎚��)
extern	int			NS_SetFontCacheTextureColorBitDepth(		int ColorBitDepth ) ;																			// �t�H���g�̃L���b�V���Ƃ��Ďg�p����e�N�X�`���̃J���[�r�b�g�[�x��ݒ肷��( 16 ���� 32 �̂ݎw��\  �f�t�H���g�� 32 )
extern	int			NS_GetFontCacheTextureColorBitDepth(		void ) ;																						// �t�H���g�̃L���b�V���Ƃ��Ďg�p����e�N�X�`���̃J���[�r�b�g�[�x���擾����
extern	int			NS_GetFontCacheToTextureFlag(              void ) ;																						// �t�H���g�Ƀe�N�X�`���L���b�V�����g�p���邩�ǂ������擾����
extern	int			NS_CheckFontChacheToTextureFlag(           int FontHandle ) ;																				// �w��̃t�H���g���e�N�X�`���L���b�V�����g�p���Ă��邩�ǂ����𓾂�(�뎚��)
extern	int			NS_CheckFontCacheToTextureFlag(            int FontHandle ) ;																				// �w��̃t�H���g���e�N�X�`���L���b�V�����g�p���Ă��邩�ǂ����𓾂�
extern	int			NS_CheckFontHandleValid(                   int FontHandle ) ;																				// �w��̃t�H���g�n���h�����L�����ۂ����ׂ�
extern	int			NS_ClearFontCacheToHandle(					int FontHandle ) ;																				// �t�H���g�n���h���̃L���b�V����������������
extern	int			NS_MultiByteCharCheck(                     const char *Buf, int CharSet /* DX_CHARSET_SHFTJIS */ ) ;										// �Q�o�C�g���������ׂ�( TRUE:�Q�o�C�g����  FALSE:�P�o�C�g���� )
extern	int			NS_GetFontCacheCharNum(                    void ) ;																						// �t�H���g�L���b�V���ŃL���b�V���ł��镶�������擾����( �߂�l  0:�f�t�H���g  1�ȏ�:�w�蕶���� )
extern	int			NS_GetFontSize(                            void ) ;																						// �t�H���g�̃T�C�Y�𓾂�
extern	int			NS_GetFontEdgeSize(                        void ) ;																						// �f�t�H���g�t�H���g�n���h���̉��T�C�Y���擾����
extern	int			NS_GetFontSizeToHandle(                    int FontHandle ) ;																				// �t�H���g�̃T�C�Y�𓾂�
extern	int			NS_GetFontEdgeSizeToHandle(                int FontHandle ) ;																				// �t�H���g�n���h���̉��T�C�Y���擾����
extern	int			NS_GetFontSpaceToHandle(                   int FontHandle ) ;																				// �t�H���g�n���h���̎��Ԃ��擾����
extern	int			NS_GetFontLineSpaceToHandle(               int FontHandle ) ;																				// �t�H���g�n���h���̍s�Ԃ��擾����
extern	int			NS_SetFontCacheUsePremulAlphaFlag(         int Flag ) ;																					// �t�H���g�L���b�V���Ƃ��ĕۑ�����摜�̌`������Z�ς݃��`�����l���t���摜�ɂ��邩�ǂ�����ݒ肷��( TRUE:��Z�ς݃����g�p����  FLASE:��Z�ς݃����g�p���Ȃ�( �f�t�H���g ) )
extern	int			NS_GetFontCacheUsePremulAlphaFlag(         void ) ;																						// �t�H���g�L���b�V���Ƃ��ĕۑ�����摜�̌`������Z�ς݃��`�����l���t���摜�ɂ��邩�ǂ������擾����
extern	int			NS_SetFontUseAdjustSizeFlag(               int Flag ) ;																					// �t�H���g�̃T�C�Y��␳���鏈�����s�����ǂ�����ݒ肷��( Flag  TRUE:�s��( �f�t�H���g )  FALSE:�s��Ȃ� )
extern	int			NS_GetFontUseAdjustSizeFlag(               void ) ;																						// �t�H���g�̃T�C�Y��␳���鏈�����s�����ǂ������擾����
extern	int			NS_SetFontOnlyDrawType(					int OnlyType ) ;																				// �t�H���g�̕`��ŉ��̂݁A���͖{�̂̂ݕ`����s�����ǂ�����ݒ肷��( OnlyType  0:�ʏ�`�� 1:�{�̂̂ݕ`�� 2:���̂ݕ`�� )
extern	int			NS_GetFontOnlyDrawType(					void ) ;																						// �t�H���g�̕`��ŉ��̂݁A���͖{�̂̂ݕ`����s�����ǂ������擾����( �߂�l  0:�ʏ�`�� 1:�{�̂̂ݕ`�� 2:���̂ݕ`�� )
extern	int			NS_SetFontIgnoreLFFlag(					int Flag ) ;																					// DrawString �Ȃǂ� \n �𖳎����邩�ǂ�����ݒ肷��( TRUE : ��������    FALSE : �������Ȃ�( �f�t�H���g ) )
extern	int			NS_GetFontIgnoreLFFlag(					void ) ;																						// DrawString �Ȃǂ� \n �𖳎����邩�ǂ������擾����( TRUE : ��������    FALSE : �������Ȃ�( �f�t�H���g ) )

extern	HANDLE		NS_AddFontFile( const TCHAR *FontFilePath ) ;																			// �w��̃t�H���g�t�@�C�����V�X�e���ɒǉ�����( �߂�l  NULL:���s  NULL�ȊO:�t�H���g�n���h��( WindowsOS �̂��̂Ȃ̂ŁA�c�w���C�u�����̃t�H���g�n���h���Ƃ͕ʕ��ł� ) )
extern	HANDLE		NS_AddFontFileWithStrLen(			const TCHAR *FontFilePath, size_t FontFilePathLength ) ;										// �w��̃t�H���g�t�@�C�����V�X�e���ɒǉ�����( �߂�l  NULL:���s  NULL�ȊO:�t�H���g�n���h��( WindowsOS �̂��̂Ȃ̂ŁA�c�w���C�u�����̃t�H���g�n���h���Ƃ͕ʕ��ł� ) )
extern	HANDLE		NS_AddFontFileFromMem( const void *FontFileImage, int FontFileImageSize ) ;											// �w��̃������A�h���X�ɓW�J�����t�H���g�t�@�C���C���[�W���V�X�e���ɒǉ�����( �߂�l  NULL:���s  NULL�ȊO:�t�H���g�n���h��( WindowsOS �̂��̂Ȃ̂ŁA�c�w���C�u�����̃t�H���g�n���h���Ƃ͕ʕ��ł� ) )
extern	int			NS_RemoveFontFile( HANDLE FontHandle ) ;																				// �w��̃t�H���g�n���h�����V�X�e������폜����( ������ AddFontFile �� AddFontFileFromMem �̖߂�l )

#ifndef DX_NON_SAVEFUNCTION

extern	int			NS_CreateFontDataFile(						const TCHAR *SaveFilePath, const TCHAR *FontName, int Size, int BitDepth /* DX_FONTIMAGE_BIT_1�� */ , int Thick, int Italic = FALSE , int CharSet = -1 , const TCHAR *SaveCharaList = NULL ) ;				// �t�H���g�f�[�^�t�@�C�����쐬����
extern	int			NS_CreateFontDataFileWithStrLen(	const TCHAR *SaveFilePath, size_t SaveFilePathLength, const TCHAR *FontName, size_t FontNameLength, int Size, int BitDepth /* DX_FONTIMAGE_BIT_1�� */ , int Thick, int Italic = FALSE , int CharSet = -1 , const TCHAR *SaveCharaList = NULL , size_t SaveCharaListLength = 0 ) ;				// �t�H���g�f�[�^�t�@�C�����쐬����

#endif

// ������`��֐�
extern	int			NS_DrawString(                             int x, int y,                                              const TCHAR *String,                      unsigned int Color, unsigned int EdgeColor = 0 ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������`�悷��
extern	int			NS_DrawNString(                            int x, int y,                                              const TCHAR *String, size_t StringLength, unsigned int Color, unsigned int EdgeColor = 0 ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������`�悷��
extern	int			NS_DrawVString(                            int x, int y,                                              const TCHAR *String,                      unsigned int Color, unsigned int EdgeColor = 0 ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������`�悷��( �c���� )
extern	int			NS_DrawNVString(                           int x, int y,                                              const TCHAR *String, size_t StringLength, unsigned int Color, unsigned int EdgeColor = 0 ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������`�悷��( �c���� )
extern	int			NS_DrawFormatString(                       int x, int y,                                 unsigned int Color, const TCHAR *FormatString, ... ) ;																			// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��
extern	int			NS_DrawFormatVString(                      int x, int y,                                 unsigned int Color, const TCHAR *FormatString, ... ) ;																			// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( �c���� )
extern	int			NS_DrawFormatString2(                      int x, int y,                                 unsigned int Color, unsigned int EdgeColor, const TCHAR *FormatString, ... ) ;																	// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( ���̐F�����t�� )
extern	int			NS_DrawFormatVString2(                     int x, int y,                                 unsigned int Color, unsigned int EdgeColor, const TCHAR *FormatString, ... ) ;																	// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( ���̐F�����t�� )( �c���� )
extern	int			NS_DrawExtendString(                       int x, int y, double ExRateX, double ExRateY,              const TCHAR *String,                      unsigned int Color, unsigned int EdgeColor = 0 ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���ĕ�����̊g��`��
extern	int			NS_DrawExtendNString(                      int x, int y, double ExRateX, double ExRateY,              const TCHAR *String, size_t StringLength, unsigned int Color, unsigned int EdgeColor = 0 ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���ĕ�����̊g��`��
extern	int			NS_DrawExtendVString(                      int x, int y, double ExRateX, double ExRateY,              const TCHAR *String,                      unsigned int Color, unsigned int EdgeColor = 0 ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���ĕ�����̊g��`��( �c���� )
extern	int			NS_DrawExtendNVString(                     int x, int y, double ExRateX, double ExRateY,              const TCHAR *String, size_t StringLength, unsigned int Color, unsigned int EdgeColor = 0 ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���ĕ�����̊g��`��( �c���� )
extern	int			NS_DrawExtendFormatString(                 int x, int y, double ExRateX, double ExRateY, unsigned int Color, const TCHAR *FormatString, ... ) ;																			// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��
extern	int			NS_DrawExtendFormatVString(                int x, int y, double ExRateX, double ExRateY, unsigned int Color, const TCHAR *FormatString, ... ) ;																			// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( �c���� )
extern	int			NS_DrawExtendFormatString2(                int x, int y, double ExRateX, double ExRateY, unsigned int Color, unsigned int EdgeColor, const TCHAR *FormatString, ... ) ;																	// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( ���̐F�����t�� )
extern	int			NS_DrawExtendFormatVString2(               int x, int y, double ExRateX, double ExRateY, unsigned int Color, unsigned int EdgeColor, const TCHAR *FormatString, ... ) ;																	// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( ���̐F�����t�� )( �c���� )
extern	int			NS_DrawRotaString(							int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *String       = NULL                           ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ĕ��������]�`�悷��
extern	int			NS_DrawRotaNString(						int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *String       = NULL , size_t StringLength = 0 ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ĕ��������]�`�悷��
extern	int			NS_DrawRotaFormatString(					int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *FormatString = NULL , ...                     ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�������]�`�悷��
extern	int			NS_DrawModiString(							int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *String       = NULL                           ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������ό`�`�悷��
extern	int			NS_DrawModiNString(						int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *String       = NULL , size_t StringLength = 0 ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������ό`�`�悷��
extern	int			NS_DrawModiFormatString(					int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *FormatString = NULL , ...                     ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�����ό`�`�悷��

extern	int			NS_DrawStringF(                            float x, float y,                                              const TCHAR *String,                      unsigned int Color, unsigned int EdgeColor = 0 ) ;						// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawNStringF(                           float x, float y,                                              const TCHAR *String, size_t StringLength, unsigned int Color, unsigned int EdgeColor = 0 ) ;						// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawVStringF(                           float x, float y,                                              const TCHAR *String,                      unsigned int Color, unsigned int EdgeColor = 0 ) ;						// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������`�悷��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawNVStringF(                          float x, float y,                                              const TCHAR *String, size_t StringLength, unsigned int Color, unsigned int EdgeColor = 0 ) ;						// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������`�悷��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawFormatStringF(                      float x, float y,                                 unsigned int Color, const TCHAR *FormatString, ... ) ;																		// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawFormatVStringF(                     float x, float y,                                 unsigned int Color, const TCHAR *FormatString, ... ) ;																		// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawFormatString2F(                     float x, float y,                                 unsigned int Color, unsigned int EdgeColor, const TCHAR *FormatString, ... ) ;																// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( ���̐F�����t�� )( ���W�w�肪 float �� )
extern	int			NS_DrawFormatVString2F(                    float x, float y,                                 unsigned int Color, unsigned int EdgeColor, const TCHAR *FormatString, ... ) ;																// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( ���̐F�����t�� )( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawExtendStringF(                      float x, float y, double ExRateX, double ExRateY,              const TCHAR *String,                      unsigned int Color, unsigned int EdgeColor = 0 ) ;						// �f�t�H���g�t�H���g�n���h�����g�p���ĕ�����̊g��`��( ���W�w�肪 float �� )
extern	int			NS_DrawExtendNStringF(                     float x, float y, double ExRateX, double ExRateY,              const TCHAR *String, size_t StringLength, unsigned int Color, unsigned int EdgeColor = 0 ) ;						// �f�t�H���g�t�H���g�n���h�����g�p���ĕ�����̊g��`��( ���W�w�肪 float �� )
extern	int			NS_DrawExtendVStringF(                     float x, float y, double ExRateX, double ExRateY,              const TCHAR *String,                      unsigned int Color, unsigned int EdgeColor = 0 ) ;						// �f�t�H���g�t�H���g�n���h�����g�p���ĕ�����̊g��`��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawExtendNVStringF(                    float x, float y, double ExRateX, double ExRateY,              const TCHAR *String, size_t StringLength, unsigned int Color, unsigned int EdgeColor = 0 ) ;						// �f�t�H���g�t�H���g�n���h�����g�p���ĕ�����̊g��`��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawExtendFormatStringF(                float x, float y, double ExRateX, double ExRateY, unsigned int Color, const TCHAR *FormatString, ... ) ;																		// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawExtendFormatVStringF(               float x, float y, double ExRateX, double ExRateY, unsigned int Color, const TCHAR *FormatString, ... ) ;																		// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawExtendFormatString2F(               float x, float y, double ExRateX, double ExRateY, unsigned int Color, unsigned int EdgeColor, const TCHAR *FormatString, ... ) ;																// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( ���̐F�����t�� )( ���W�w�肪 float �� )
extern	int			NS_DrawExtendFormatVString2F(              float x, float y, double ExRateX, double ExRateY, unsigned int Color, unsigned int EdgeColor, const TCHAR *FormatString, ... ) ;																// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( ���̐F�����t�� )( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawRotaStringF(						float x, float y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *String       = NULL                           ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ĕ��������]�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawRotaNStringF(						float x, float y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *String       = NULL , size_t StringLength = 0 ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ĕ��������]�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawRotaFormatStringF(					float x, float y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *FormatString = NULL , ...                     ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�������]�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawModiStringF(						float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *String       = NULL                           ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������ό`�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawModiNStringF(						float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *String       = NULL , size_t StringLength = 0 ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ĕ������ό`�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawModiFormatStringF(					float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, unsigned int Color, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *FormatString = NULL , ...                     ) ;		// �f�t�H���g�t�H���g�n���h�����g�p���ď����w�蕶�����ό`�`�悷��( ���W�w�肪 float �� )

extern	int			NS_DrawNumberToI(                          int x, int y,                          int    Num, int RisesNum, unsigned int Color, unsigned int EdgeColor = 0 ) ;											// �f�t�H���g�t�H���g�n���h�����g�p���Đ����^�̐��l��`�悷��
extern	int			NS_DrawNumberToF(                          int x, int y,                          double Num, int Length,   unsigned int Color, unsigned int EdgeColor = 0 ) ;											// �f�t�H���g�t�H���g�n���h�����g�p���ĕ��������_�^�̐��l��`�悷��
extern	int			NS_DrawNumberPlusToI(                      int x, int y, const TCHAR *NoteString, int    Num, int RisesNum, unsigned int Color, unsigned int EdgeColor = 0 ) ;											// �f�t�H���g�t�H���g�n���h�����g�p���Đ����^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��
extern 	int			NS_DrawNumberPlusToF(                      int x, int y, const TCHAR *NoteString, double Num, int Length,   unsigned int Color, unsigned int EdgeColor = 0 ) ;											// �f�t�H���g�t�H���g�n���h�����g�p���ĕ��������_�^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��

extern	int			NS_DrawStringToZBuffer(                    int x, int y, const TCHAR *String,                                                                                        int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������`�悷��
extern	int			NS_DrawNStringToZBuffer(                   int x, int y, const TCHAR *String, size_t StringLength,                                                                   int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������`�悷��
extern	int			NS_DrawVStringToZBuffer(                   int x, int y, const TCHAR *String,                                                                                        int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������`�悷��( �c���� )
extern	int			NS_DrawNVStringToZBuffer(                  int x, int y, const TCHAR *String, size_t StringLength,                                                                   int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������`�悷��( �c���� )
extern	int			NS_DrawFormatStringToZBuffer(              int x, int y,                                                                                        int WriteZMode /* DX_ZWRITE_MASK �� */ , const TCHAR *FormatString, ... ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶�����`�悷��
extern	int			NS_DrawFormatVStringToZBuffer(             int x, int y,                                                                                        int WriteZMode /* DX_ZWRITE_MASK �� */ , const TCHAR *FormatString, ... ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶�����`�悷��( �c���� )
extern	int			NS_DrawExtendStringToZBuffer(              int x, int y, double ExRateX, double ExRateY, const TCHAR *String,                                                        int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ�������g��`�悷��
extern	int			NS_DrawExtendNStringToZBuffer(             int x, int y, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength,                                   int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ�������g��`�悷��
extern	int			NS_DrawExtendVStringToZBuffer(             int x, int y, double ExRateX, double ExRateY, const TCHAR *String,                                                        int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ�������g��`�悷��( �c���� )
extern	int			NS_DrawExtendNVStringToZBuffer(            int x, int y, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength,                                   int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ�������g��`�悷��( �c���� )
extern	int			NS_DrawExtendFormatStringToZBuffer(        int x, int y, double ExRateX, double ExRateY,                                                        int WriteZMode /* DX_ZWRITE_MASK �� */ , const TCHAR *FormatString, ... ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶������g��`�悷��
extern	int			NS_DrawExtendFormatVStringToZBuffer(       int x, int y, double ExRateX, double ExRateY,                                                        int WriteZMode /* DX_ZWRITE_MASK �� */ , const TCHAR *FormatString, ... ) ;							// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶������g��`�悷��( �c���� )
extern	int			NS_DrawRotaStringToZBuffer(				int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag , const TCHAR *String                            ) ;	// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ��������]�`�悷��
extern	int			NS_DrawRotaNStringToZBuffer(				int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag , const TCHAR *String,       size_t StringLength ) ;	// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ��������]�`�悷��
extern	int			NS_DrawRotaFormatStringToZBuffer(			int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag , const TCHAR *FormatString , ...                ) ;	// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶�������]�`�悷��
extern	int			NS_DrawModiStringToZBuffer(				int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,                                      int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag , const TCHAR *String                            ) ;	// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������ό`�`�悷��
extern	int			NS_DrawModiNStringToZBuffer(				int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,                                      int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag , const TCHAR *String,       size_t StringLength ) ;	// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������ό`�`�悷��
extern	int			NS_DrawModiFormatStringToZBuffer(			int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,                                      int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag , const TCHAR *FormatString , ...                ) ;	// �f�t�H���g�t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶�����ό`�`�悷��


extern	int			NS_DrawStringToHandle(                     int x, int y, const TCHAR *String,                      unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE ) ;											// �t�H���g�n���h�����g�p���ĕ������`�悷��
extern	int			NS_DrawNStringToHandle(                    int x, int y, const TCHAR *String, size_t StringLength, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE ) ;											// �t�H���g�n���h�����g�p���ĕ������`�悷��
extern	int			NS_DrawVStringToHandle(                    int x, int y, const TCHAR *String,                      unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;																		// �t�H���g�n���h�����g�p���ĕ������`�悷��( �c���� )
extern	int			NS_DrawNVStringToHandle(                   int x, int y, const TCHAR *String, size_t StringLength, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;																		// �t�H���g�n���h�����g�p���ĕ������`�悷��( �c���� )
extern	int			NS_DrawFormatStringToHandle(               int x, int y, unsigned int Color, int FontHandle, const TCHAR *FormatString, ... ) ;																											// �t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��
extern	int			NS_DrawFormatVStringToHandle(              int x, int y, unsigned int Color, int FontHandle, const TCHAR *FormatString, ... ) ;																											// �t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( �c���� )
extern	int			NS_DrawFormatString2ToHandle(              int x, int y, unsigned int Color, unsigned int EdgeColor, int FontHandle, const TCHAR *FormatString, ... ) ;																											// �t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( ���̐F�����t�� )
extern	int			NS_DrawFormatVString2ToHandle(             int x, int y, unsigned int Color, unsigned int EdgeColor, int FontHandle, const TCHAR *FormatString, ... ) ;																											// �t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( ���̐F�����t�� )( �c���� )
extern	int			NS_DrawExtendStringToHandle(               int x, int y, double ExRateX, double ExRateY, const TCHAR *String,                      unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE ) ;			// �t�H���g�n���h�����g�p���ĕ�������g��`�悷��
extern	int			NS_DrawExtendNStringToHandle(              int x, int y, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE ) ;			// �t�H���g�n���h�����g�p���ĕ�������g��`�悷��
extern	int			NS_DrawExtendVStringToHandle(              int x, int y, double ExRateX, double ExRateY, const TCHAR *String,                      unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;										// �t�H���g�n���h�����g�p���ĕ�������g��`�悷��( �c���� )
extern	int			NS_DrawExtendNVStringToHandle(             int x, int y, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;										// �t�H���g�n���h�����g�p���ĕ�������g��`�悷��( �c���� )
extern	int			NS_DrawExtendFormatStringToHandle(         int x, int y, double ExRateX, double ExRateY, unsigned int Color, int FontHandle, const TCHAR *FormatString, ... ) ;																			// �t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��
extern	int			NS_DrawExtendFormatVStringToHandle(        int x, int y, double ExRateX, double ExRateY, unsigned int Color, int FontHandle, const TCHAR *FormatString, ... ) ;																			// �t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( �c���� )
extern	int			NS_DrawExtendFormatString2ToHandle(        int x, int y, double ExRateX, double ExRateY, unsigned int Color, unsigned int EdgeColor, int FontHandle, const TCHAR *FormatString, ... ) ;																			// �t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( ���̐F�����t�� )
extern	int			NS_DrawExtendFormatVString2ToHandle(       int x, int y, double ExRateX, double ExRateY, unsigned int Color, unsigned int EdgeColor, int FontHandle, const TCHAR *FormatString, ... ) ;																			// �t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( ���̐F�����t�� )( �c���� )
extern	int			NS_DrawRotaStringToHandle(					int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, int FontHandle, unsigned int EdgeColor, int VerticalFlag, const TCHAR *String                            ) ;		// �t�H���g�n���h�����g�p���ĕ��������]�`�悷��
extern	int			NS_DrawRotaNStringToHandle(				int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, int FontHandle, unsigned int EdgeColor, int VerticalFlag, const TCHAR *String,       size_t StringLength ) ;		// �t�H���g�n���h�����g�p���ĕ��������]�`�悷��
extern	int			NS_DrawRotaFormatStringToHandle(			int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, int FontHandle, unsigned int EdgeColor, int VerticalFlag, const TCHAR *FormatString, ...                 ) ;		// �t�H���g�n���h�����g�p���ď����w�蕶�������]�`�悷��
extern	int			NS_DrawModiStringToHandle(					int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, unsigned int Color, int FontHandle, unsigned int EdgeColor, int VerticalFlag, const TCHAR *String                            ) ;	// �t�H���g�n���h�����g�p���ĕ������ό`�`�悷��
extern	int			NS_DrawModiNStringToHandle(				int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, unsigned int Color, int FontHandle, unsigned int EdgeColor, int VerticalFlag, const TCHAR *String,       size_t StringLength ) ;	// �t�H���g�n���h�����g�p���ĕ������ό`�`�悷��
extern	int			NS_DrawModiFormatStringToHandle(			int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, unsigned int Color, int FontHandle, unsigned int EdgeColor, int VerticalFlag, const TCHAR *FormatString, ...                 ) ;	// �t�H���g�n���h�����g�p���ď����w�蕶�����ό`�`�悷��

extern	int			NS_DrawStringFToHandle(                    float x, float y, const TCHAR *String,                      unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE ) ;										// �t�H���g�n���h�����g�p���ĕ������`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawNStringFToHandle(                   float x, float y, const TCHAR *String, size_t StringLength, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE ) ;										// �t�H���g�n���h�����g�p���ĕ������`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawVStringFToHandle(                   float x, float y, const TCHAR *String,                      unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;																	// �t�H���g�n���h�����g�p���ĕ������`�悷��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawNVStringFToHandle(                  float x, float y, const TCHAR *String, size_t StringLength, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;																	// �t�H���g�n���h�����g�p���ĕ������`�悷��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawFormatStringFToHandle(              float x, float y, unsigned int Color, int FontHandle, const TCHAR *FormatString, ... ) ;																										// �t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawFormatVStringFToHandle(             float x, float y, unsigned int Color, int FontHandle, const TCHAR *FormatString, ... ) ;																										// �t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawFormatString2FToHandle(             float x, float y, unsigned int Color, unsigned int EdgeColor, int FontHandle, const TCHAR *FormatString, ... ) ;																											// �t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( ���̐F�����t�� )( ���W�w�肪 float �� )
extern	int			NS_DrawFormatVString2FToHandle(            float x, float y, unsigned int Color, unsigned int EdgeColor, int FontHandle, const TCHAR *FormatString, ... ) ;																											// �t�H���g�n���h�����g�p���ď����w�蕶�����`�悷��( ���̐F�����t�� )( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawExtendStringFToHandle(              float x, float y, double ExRateX, double ExRateY, const TCHAR *String,                      unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE ) ;		// �t�H���g�n���h�����g�p���ĕ�������g��`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawExtendNStringFToHandle(             float x, float y, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE ) ;		// �t�H���g�n���h�����g�p���ĕ�������g��`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawExtendVStringFToHandle(             float x, float y, double ExRateX, double ExRateY, const TCHAR *String,                      unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;									// �t�H���g�n���h�����g�p���ĕ�������g��`�悷��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawExtendNVStringFToHandle(            float x, float y, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;									// �t�H���g�n���h�����g�p���ĕ�������g��`�悷��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawExtendFormatStringFToHandle(        float x, float y, double ExRateX, double ExRateY, unsigned int Color, int FontHandle, const TCHAR *FormatString, ... ) ;																		// �t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawExtendFormatVStringFToHandle(       float x, float y, double ExRateX, double ExRateY, unsigned int Color, int FontHandle, const TCHAR *FormatString, ... ) ;																		// �t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawExtendFormatString2FToHandle(       float x, float y, double ExRateX, double ExRateY, unsigned int Color, unsigned int EdgeColor, int FontHandle, const TCHAR *FormatString, ... ) ;																			// �t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( ���̐F�����t�� )( ���W�w�肪 float �� )
extern	int			NS_DrawExtendFormatVString2FToHandle(      float x, float y, double ExRateX, double ExRateY, unsigned int Color, unsigned int EdgeColor, int FontHandle, const TCHAR *FormatString, ... ) ;																			// �t�H���g�n���h�����g�p���ď����w�蕶������g��`�悷��( ���̐F�����t�� )( �c���� )( ���W�w�肪 float �� )
extern	int			NS_DrawRotaStringFToHandle(				float x, float y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *String       = NULL                           ) ;		// �t�H���g�n���h�����g�p���ĕ��������]�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawRotaNStringFToHandle(				float x, float y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *String       = NULL , size_t StringLength = 0 ) ;		// �t�H���g�n���h�����g�p���ĕ��������]�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawRotaFormatStringFToHandle(			float x, float y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 , int VerticalFlag = FALSE , const TCHAR *FormatString = NULL , ...                     ) ;		// �t�H���g�n���h�����g�p���ď����w�蕶�������]�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawModiStringFToHandle(				float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, unsigned int Color, int FontHandle, unsigned int EdgeColor, int VerticalFlag, const TCHAR *String                            ) ;		// �t�H���g�n���h�����g�p���ĕ������ό`�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawModiNStringFToHandle(				float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, unsigned int Color, int FontHandle, unsigned int EdgeColor, int VerticalFlag, const TCHAR *String,       size_t StringLength ) ;		// �t�H���g�n���h�����g�p���ĕ������ό`�`�悷��( ���W�w�肪 float �� )
extern	int			NS_DrawModiFormatStringFToHandle(			float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, unsigned int Color, int FontHandle, unsigned int EdgeColor, int VerticalFlag, const TCHAR *FormatString, ...                 ) ;		// �t�H���g�n���h�����g�p���ď����w�蕶�����ό`�`�悷��( ���W�w�肪 float �� )

extern	int			NS_DrawNumberToIToHandle(                  int x, int y,                          int    Num, int RisesNum, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;											// �t�H���g�n���h�����g�p���Đ����^�̐��l��`�悷��
extern	int			NS_DrawNumberToFToHandle(                  int x, int y,                          double Num, int Length,   unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;											// �t�H���g�n���h�����g�p���ĕ��������_�^�̐��l��`�悷��
extern	int			NS_DrawNumberPlusToIToHandle(              int x, int y, const TCHAR *NoteString, int    Num, int RisesNum, unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;											// �t�H���g�n���h�����g�p���Đ����^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��
extern	int			NS_DrawNumberPlusToFToHandle(              int x, int y, const TCHAR *NoteString, double Num, int Length,   unsigned int Color, int FontHandle, unsigned int EdgeColor = 0 ) ;											// �t�H���g�n���h�����g�p���ĕ��������_�^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��

extern	int			NS_DrawStringToHandleToZBuffer(            int x, int y, const TCHAR *String,                      int FontHandle,                                                                   int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag = FALSE ) ;							// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������`�悷��
extern	int			NS_DrawNStringToHandleToZBuffer(           int x, int y, const TCHAR *String, size_t StringLength, int FontHandle,                                                                   int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag = FALSE ) ;							// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������`�悷��
extern	int			NS_DrawVStringToHandleToZBuffer(           int x, int y, const TCHAR *String,                      int FontHandle,                                                                   int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;													// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������`�悷��( �c���� )
extern	int			NS_DrawNVStringToHandleToZBuffer(          int x, int y, const TCHAR *String, size_t StringLength, int FontHandle,                                                                   int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;													// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������`�悷��( �c���� )
extern	int			NS_DrawFormatStringToHandleToZBuffer(      int x, int y, int FontHandle,                                                                                        int WriteZMode /* DX_ZWRITE_MASK �� */ , const TCHAR *FormatString, ... ) ;										// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶�����`�悷��
extern	int			NS_DrawFormatVStringToHandleToZBuffer(     int x, int y, int FontHandle,                                                                                        int WriteZMode /* DX_ZWRITE_MASK �� */ , const TCHAR *FormatString, ... ) ;										// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶�����`�悷��( �c���� )
extern	int			NS_DrawExtendStringToHandleToZBuffer(      int x, int y, double ExRateX, double ExRateY, const TCHAR *String,                      int FontHandle,                                   int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag = FALSE ) ;							// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ�������g��`�悷��
extern	int			NS_DrawExtendNStringToHandleToZBuffer(     int x, int y, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength, int FontHandle,                                   int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag = FALSE ) ;							// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ�������g��`�悷��
extern	int			NS_DrawExtendVStringToHandleToZBuffer(     int x, int y, double ExRateX, double ExRateY, const TCHAR *String,                      int FontHandle,                                   int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;													// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ�������g��`�悷��( �c���� )
extern	int			NS_DrawExtendNVStringToHandleToZBuffer(    int x, int y, double ExRateX, double ExRateY, const TCHAR *String, size_t StringLength, int FontHandle,                                   int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;													// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ�������g��`�悷��( �c���� )
extern	int			NS_DrawExtendFormatStringToHandleToZBuffer(   int x, int y, double ExRateX, double ExRateY, int FontHandle,                                                      int WriteZMode /* DX_ZWRITE_MASK �� */ , const TCHAR *FormatString, ... ) ;										// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶������g��`�悷��
extern	int			NS_DrawExtendFormatVStringToHandleToZBuffer(  int x, int y, double ExRateX, double ExRateY, int FontHandle,                                                      int WriteZMode /* DX_ZWRITE_MASK �� */ , const TCHAR *FormatString, ... ) ;										// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶������g��`�悷��( �c���� )
extern	int			NS_DrawRotaStringToHandleToZBuffer(		int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, int FontHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag, const TCHAR *String                            ) ;		// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ��������]�`�悷��
extern	int			NS_DrawRotaNStringToHandleToZBuffer(		int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, int FontHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag, const TCHAR *String,       size_t StringLength ) ;		// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ��������]�`�悷��
extern	int			NS_DrawRotaFormatStringToHandleToZBuffer(	int x, int y, double ExRateX, double ExRateY, double RotCenterX, double RotCenterY, double RotAngle, int FontHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag, const TCHAR *FormatString, ...                 ) ;		// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶�������]�`�悷��
extern	int			NS_DrawModiStringToHandleToZBuffer(		int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int FontHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag, const TCHAR *String                            ) ;											// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������ό`�`�悷��
extern	int			NS_DrawModiNStringToHandleToZBuffer(		int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int FontHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag, const TCHAR *String,       size_t StringLength ) ;											// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ĕ������ό`�`�悷��
extern	int			NS_DrawModiFormatStringToHandleToZBuffer(	int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int FontHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag, const TCHAR *FormatString, ...                 ) ;											// �t�H���g�n���h�����g�p���Ăy�o�b�t�@�ɑ΂��ď����w�蕶�����ό`�`�悷��

#endif // DX_NON_FONT













// DxMath.cpp �֐��v���g�^�C�v�錾

// ���Z���C�u����
















// DxBaseImage.cpp �֐��v���g�^�C�v�錾

// ��{�C���[�W�f�[�^�̃��[�h�{�c�h�a�֌W
extern	int			NS_CreateGraphImageOrDIBGraph(    const TCHAR *FileName, const void *DataImage, int DataImageSize, int DataImageType /* LOADIMAGE_TYPE_FILE �� */ , int BmpFlag, int ReverseFlag, BASEIMAGE *BaseImage, BITMAPINFO **BmpInfo, void **GraphData ) ;					// �摜�t�@�C���Ⴕ���̓�������ɓW�J���ꂽ�摜�t�@�C���C���[�W��ǂݍ��݁A��{�C���[�W�f�[�^�Ⴕ���͂a�l�o�f�[�^���\�z����
extern	int			NS_CreateGraphImageOrDIBGraphWithStrLen(  const TCHAR *FileName, size_t FileNameLength, const void *DataImage, int DataImageSize, int DataImageType /* LOADIMAGE_TYPE_FILE �� */ , int BmpFlag, int ReverseFlag, BASEIMAGE *BaseImage, BITMAPINFO **BmpInfo, void **GraphData ) ;					// �摜�t�@�C���Ⴕ���̓�������ɓW�J���ꂽ�摜�t�@�C���C���[�W��ǂݍ��݁A��{�C���[�W�f�[�^�Ⴕ���͂a�l�o�f�[�^���\�z����
extern	int			NS_CreateGraphImageType2(         STREAMDATA *Src, BASEIMAGE *Dest ) ;																																															// �摜�f�[�^����\�z�����X�g���[���ǂݍ��ݗp�f�[�^���g�p���Ċ�{�C���[�W�f�[�^���\�z����
extern	int			NS_CreateBmpInfo(                 BITMAPINFO *BmpInfo, int Width, int Height, int Pitch, const void *SrcGrData, void **DestGrData ) ;																													// 24bit�J���[�`���̃r�b�g�}�b�v�f�[�^����a�l�o�f�[�^���\�z����
extern	int			NS_GetImageSize_File(             const TCHAR *FileName, int *SizeX, int *SizeY ) ;																																											// �摜�t�@�C���̉��s�N�Z�����Əc�s�N�Z�������擾����
extern	int			NS_GetImageSize_FileWithStrLen(   const TCHAR *FileName, size_t FileNameLength, int *SizeX, int *SizeY ) ;																																													// �摜�t�@�C���̉��s�N�Z�����Əc�s�N�Z�������擾����
extern	int			NS_GetImageSize_Mem(              const void *FileImage, int FileImageSize, int *SizeX, int *SizeY ) ;																																							// ��������ɓW�J���ꂽ�摜�t�@�C���̉��s�N�Z�����Əc�s�N�Z�������擾����
extern	unsigned int NS_GetGraphImageFullColorCode(   const BASEIMAGE *GraphImage, int x, int y ) ;																																												// ��{�C���[�W�f�[�^�̎w����W�̃t���J���[�R�[�h���擾����
extern	int			NS_CreateGraphImage_plus_Alpha(           const TCHAR *FileName,                        const void *RgbImage, int RgbImageSize, int RgbImageType, const void *AlphaImage, int AlphaImageSize, int AlphaImageType, BASEIMAGE *RgbGraphImage, BASEIMAGE *AlphaGraphImage, int ReverseFlag ) ;	// �摜�t�@�C���Ⴕ���̓�������ɓW�J���ꂽ�摜�t�@�C���C���[�W��ǂݍ��݁A��{�C���[�W�f�[�^���\�z����
extern	int			NS_CreateGraphImage_plus_AlphaWithStrLen( const TCHAR *FileName, size_t FileNameLength, const void *RgbImage, int RgbImageSize, int RgbImageType, const void *AlphaImage, int AlphaImageSize, int AlphaImageType, BASEIMAGE *RgbGraphImage, BASEIMAGE *AlphaGraphImage, int ReverseFlag ) ;	// �摜�t�@�C���Ⴕ���̓�������ɓW�J���ꂽ�摜�t�@�C���C���[�W��ǂݍ��݁A��{�C���[�W�f�[�^���\�z����
extern	int			NS_ReverseGraphImage(             BASEIMAGE *GraphImage ) ;																																																	// ��{�C���[�W�f�[�^�����E���]����
#ifdef WINDOWS_DESKTOP_OS
extern	HBITMAP		NS_CreateDIBGraph(                const TCHAR *FileName,                                                                                                                                        int ReverseFlag,          COLORDATA *SrcColor ) ;				// �摜�t�@�C������c�h�a�f�[�^���쐬����
extern	HBITMAP		NS_CreateDIBGraphWithStrLen(					const TCHAR *FileName, size_t FileNameLength,                                                                                                                                        int ReverseFlag,          COLORDATA *SrcColor ) ;					// �摜�t�@�C������c�h�a�f�[�^���쐬����
extern	HBITMAP		NS_CreateDIBGraphToMem(           const BITMAPINFO *BmpInfo, const void *GraphData,                                                                                                             int ReverseFlag,          COLORDATA *SrcColor ) ;				// �a�l�o�f�[�^����c�h�a�f�[�^�N���쐬����
extern	int			NS_CreateDIBGraph_plus_Alpha(     const TCHAR *FileName, HBITMAP *RGBBmp, HBITMAP *AlphaBmp,                                                                                                    int ReverseFlag = FALSE , COLORDATA *SrcColor = NULL ) ;		// �摜�t�@�C������c�h�a�f�[�^�ƃ}�X�N�p�c�h�a�f�[�^���쐬����
extern	int			NS_CreateDIBGraph_plus_AlphaWithStrLen(		const TCHAR *FileName, size_t FileNameLength, HBITMAP *RGBBmp, HBITMAP *AlphaBmp,                                                                                                    int ReverseFlag = FALSE , COLORDATA *SrcColor = NULL ) ;			// �摜�t�@�C������c�h�a�f�[�^�ƃ}�X�N�p�c�h�a�f�[�^���쐬����
extern	HBITMAP		NS_CreateDIBGraphVer2(            const TCHAR *FileName, const void *MemImage, int MemImageSize,                                             int ImageType,                                     int ReverseFlag,          COLORDATA *SrcColor ) ;				// �摜�t�@�C���Ⴕ���̓�������ɓW�J���ꂽ�摜�t�@�C���C���[�W����c�h�a�f�[�^���쐬����
extern	HBITMAP		NS_CreateDIBGraphVer2WithStrLen(				const TCHAR *FileName, size_t FileNameLength, const void *MemImage, int MemImageSize,                                             int ImageType,                                     int ReverseFlag,          COLORDATA *SrcColor ) ;					// �摜�t�@�C���Ⴕ���̓�������ɓW�J���ꂽ�摜�t�@�C���C���[�W����c�h�a�f�[�^���쐬����
extern	int			NS_CreateDIBGraphVer2_plus_Alpha(				const TCHAR *FileName,                        const void *MemImage, int MemImageSize, const void *AlphaImage, int AlphaImageSize, int ImageType, HBITMAP *RGBBmp, HBITMAP *AlphaBmp, int ReverseFlag,          COLORDATA *SrcColor ) ;					// �摜�t�@�C���Ⴕ���̓�������ɓW�J���ꂽ�摜�t�@�C���C���[�W����c�h�a�f�[�^�ƃ}�X�N�p�c�h�a�f�[�^���쐬����
extern	int			NS_CreateDIBGraphVer2_plus_AlphaWithStrLen(	const TCHAR *FileName, size_t FileNameLength, const void *MemImage, int MemImageSize, const void *AlphaImage, int AlphaImageSize, int ImageType, HBITMAP *RGBBmp, HBITMAP *AlphaBmp, int ReverseFlag,          COLORDATA *SrcColor ) ;					// �摜�t�@�C���Ⴕ���̓�������ɓW�J���ꂽ�摜�t�@�C���C���[�W����c�h�a�f�[�^�ƃ}�X�N�p�c�h�a�f�[�^���쐬����
extern	int			NS_ConvBitmapToGraphImage(        const BITMAPINFO *BmpInfo, void *GraphData, BASEIMAGE *GraphImage, int CopyFlag ) ;																																		// �a�l�o�f�[�^�����{�C���[�W�f�[�^���\�z����( Ret 0:����I��  1:�R�s�[���s����  -1:�G���[ )
extern	int			NS_ConvGraphImageToBitmap(        const BASEIMAGE *GraphImage, BITMAPINFO *BmpInfo, void **GraphData, int CopyFlag, int FullColorConv = TRUE ) ;																												// ��{�C���[�W�f�[�^���a�l�o�f�[�^�ɕϊ�����GraphImage �� �a�l�o �ɕϊ�����(�A���t�@�f�[�^�͂����Ă����������)( �߂�l�@0:����I��  1:�R�s�[���s����  -1:�G���[ )
#endif // WINDOWS_DESKTOP_OS

//extern int		NS_AddUserGraphLoadFunction( int ( *UserLoadFunc )( FILE *fp, BITMAPINFO **BmpInfo, void **GraphData ) ) ;																					// ���[�U�[��`�̉摜�f�[�^�ǂݍ��݊֐���o�^����
//extern int		NS_AddUserGraphLoadFunction2( int ( *UserLoadFunc )( void *Image, int ImageSize, int ImageType, BITMAPINFO **BmpInfo, void **GraphData ) ) ;												// ���[�U�[��`�̉摜�f�[�^�ǂݍ��݊֐���o�^����
//extern int		NS_AddUserGraphLoadFunction3( int ( *UserLoadFunc )( void *DataImage, int DataImageSize, int DataImageType, int BmpFlag, BASEIMAGE *BaseImage, BITMAPINFO **BmpInfo, void **GraphData ) ) ;	// ���[�U�[��`�̉摜�f�[�^�ǂݍ��݊֐�Ver3��o�^����
extern	int			NS_AddUserGraphLoadFunction4( int (* UserLoadFunc )( STREAMDATA *Src, BASEIMAGE *BaseImage ) ) ; 																								// ���[�U�[��`�̉摜�f�[�^�ǂݍ��݊֐�Ver4��o�^����
//extern int		NS_SubUserGraphLoadFunction( int ( *UserLoadFunc )( FILE *fp, BITMAPINFO **BmpInfo, void **GraphData ) ) ;																					// ���[�U�[��`�̉摜�f�[�^�ǂݍ��݊֐���o�^���疕������
//extern int		NS_SubUserGraphLoadFunction2( int ( *UserLoadFunc )( void *Image, int ImageSize, int ImageType, BITMAPINFO **BmpInfo, void **GraphData ) ) ;												// ���[�U�[��`�̉摜�f�[�^�ǂݍ��݊֐���o�^���疕������
//extern int		NS_SubUserGraphLoadFunction3( int ( *UserLoadFunc )( void *DataImage, int DataImageSize, int DataImageType, int BmpFlag, BASEIMAGE *BaseImage, BITMAPINFO **BmpInfo, void **GraphData ) ) ;	// ���[�U�[��`�̉摜�f�[�^�ǂݍ��݊֐�Ver3��o�^���疕������
extern	int			NS_SubUserGraphLoadFunction4( int (* UserLoadFunc )( STREAMDATA *Src, BASEIMAGE *BaseImage ) ) ; 																								// ���[�U�[��`�̉摜�f�[�^�ǂݍ��݊֐�Ver4��o�^���疕������

extern	int			NS_SetUseFastLoadFlag(            int Flag ) ;														// �����ǂݍ��݃��[�`�����g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����( �f�t�H���g )  FALSE:�g�p���Ȃ� )
extern	int			NS_SetGraphDataShavedMode(        int ShavedMode /* DX_SHAVEDMODE_NONE �� */ ) ;					// �摜���F���̉摜�򉻊ɘa�������[�h��ݒ肷��( �f�t�H���g�ł͊ɘa���������� DX_SHAVEDMODE_NONE )
extern	int			NS_GetGraphDataShavedMode(        void ) ;															// �摜���F���̉摜�򉻊ɘa�������[�h���擾����
extern	int			NS_SetUsePremulAlphaConvertLoad(  int UseFlag ) ;													// �摜�t�@�C���ǂݍ��ݎ��ɏ�Z�ς݃A���t�@�摜�ɕϊ����邩�ǂ�����ݒ肷��( TRUE:�ϊ��������s��  FALSE:�ϊ��������s��Ȃ�( �f�t�H���g ) )
extern	int			NS_GetUsePremulAlphaConvertLoad(    void ) ;															// �摜�t�@�C���ǂݍ��ݎ��ɏ�Z�ς݃A���t�@�摜�ɕϊ����邩�ǂ������擾����( TRUE:�ϊ��������s��  FALSE:�ϊ��������s��Ȃ�( �f�t�H���g ) )
extern	int			NS_SetUseConvertNormalFormatLoad(   int UseFlag ) ;													// �摜�t�@�C���ǂݍ��ݎ��� DX_BASEIMAGE_FORMAT_NORMAL �ȊO�̌`���̃C���[�W�� DX_BASEIMAGE_FORMAT_NORMAL �`���̃C���[�W�ɕϊ����邩�ǂ�����ݒ肷��( TRUE:�ϊ��������s��  FALSE:�ϊ��������s�Ȃ�Ȃ�( �f�t�H���g ) )
extern	int			NS_GetUseConvertNormalFormatLoad(   void ) ;															// �摜�t�@�C���ǂݍ��ݎ��� DX_BASEIMAGE_FORMAT_NORMAL �ȊO�̌`���̃C���[�W�� DX_BASEIMAGE_FORMAT_NORMAL �`���̃C���[�W�ɕϊ����邩�ǂ������擾����( TRUE:�ϊ��������s��  FALSE:�ϊ��������s�Ȃ�Ȃ�( �f�t�H���g ) )

// ��{�C���[�W�f�[�^�\���̊֌W
extern	int			NS_CreateBaseImage(               const TCHAR *FileName, const void *FileImage, int FileImageSize, int DataType /*=LOADIMAGE_TYPE_FILE*/ , BASEIMAGE *BaseImage,  int ReverseFlag ) ;			// �摜�t�@�C���Ⴕ���̓�������ɓW�J���ꂽ�摜�t�@�C���C���[�W�����{�C���[�W�f�[�^���\�z����
extern	int			NS_CreateBaseImageWithStrLen(       const TCHAR *FileName, size_t FileNameLength, const void *FileImage, int FileImageSize, int DataType /*=LOADIMAGE_TYPE_FILE*/ , BASEIMAGE *BaseImage,  int ReverseFlag ) ;			// �摜�t�@�C���Ⴕ���̓�������ɓW�J���ꂽ�摜�t�@�C���C���[�W�����{�C���[�W�f�[�^���\�z����
extern	int			NS_CreateGraphImage(                const TCHAR *FileName,                        const void *DataImage, int DataImageSize, int DataImageType,                      BASEIMAGE *GraphImage, int ReverseFlag ) ;			// CreateBaseImage �̋�����
extern	int			NS_CreateBaseImageToFile(           const TCHAR *FileName,                                                                                                          BASEIMAGE *BaseImage,  int ReverseFlag = FALSE ) ;	// �摜�t�@�C�������{�C���[�W�f�[�^���\�z����
extern	int			NS_CreateBaseImageToFileWithStrLen( const TCHAR *FileName, size_t FileNameLength,                                                                                   BASEIMAGE *BaseImage,  int ReverseFlag = FALSE ) ;	// �摜�t�@�C�������{�C���[�W�f�[�^���\�z����
extern	int			NS_CreateBaseImageToMem(                                 const void *FileImage, int FileImageSize,                                         BASEIMAGE *BaseImage,  int ReverseFlag = FALSE ) ;	// ��������ɓW�J���ꂽ�摜�t�@�C���C���[�W�����{�C���[�W�f�[�^���\�z����
extern	int			NS_CreateARGBF32ColorBaseImage(   int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �`�q�f�a�e�`�����l�� 32bit ���������_�^ �J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateARGBF16ColorBaseImage(   int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �`�q�f�a�e�`�����l�� 16bit ���������_�^ �J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateARGB8ColorBaseImage(     int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �`�q�f�a�W�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateXRGB8ColorBaseImage(     int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �w�q�f�a�W�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateRGBA8ColorBaseImage(       int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �q�f�a�`�W�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateABGR8ColorBaseImage(       int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �`�a�f�q�W�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateBGRA8ColorBaseImage(       int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �a�f�q�`�W�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateARGB4ColorBaseImage(     int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �`�q�f�a�S�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateA1R5G5B5ColorBaseImage(  int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �`�P�q�T�f�T�a�T�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateX1R5G5B5ColorBaseImage(  int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �w�P�q�T�f�T�a�T�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateR5G5B5A1ColorBaseImage(  int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �q�T�f�T�a�T�`�P�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateR5G6B5ColorBaseImage(    int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �q�T�f�U�a�T�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateRGB8ColorBaseImage(      int SizeX, int SizeY,                             BASEIMAGE *BaseImage ) ;																					// �q�f�a�W�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreatePAL8ColorBaseImage(      int SizeX, int SizeY,                             BASEIMAGE *BaseImage, int UseAlpha = FALSE ) ;																// �p���b�g�W�r�b�g�J���[�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateColorDataBaseImage(      int SizeX, int SizeY, const COLORDATA *ColorData, BASEIMAGE *BaseImage ) ;																					// �w��̃J���[�t�H�[�}�b�g�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_GetBaseImageGraphDataSize(     const BASEIMAGE *BaseImage ) ;																																// ��{�C���[�W�f�[�^�̃C���[�W�T�C�Y���擾����( �P�ʁFbyte )
extern	int			NS_DerivationBaseImage(           const BASEIMAGE *BaseImage, int x1, int y1, int x2, int y2, BASEIMAGE *NewBaseImage ) ;																		// ��{�C���[�W�f�[�^�̎w��̕����������g����{�C���[�W�f�[�^�̏����쐬����

extern	int			NS_ReleaseBaseImage(              BASEIMAGE *BaseImage ) ;																																		// ��{�C���[�W�f�[�^�̌�n�����s��
extern	int			NS_ReleaseGraphImage(             BASEIMAGE *GraphImage ) ;																																	// ReleaseBaseImage �̋�����

extern	int			NS_ConvertNormalFormatBaseImage(  BASEIMAGE *BaseImage, int ReleaseOrigGraphData = TRUE ) ;																									// DX_BASEIMAGE_FORMAT_NORMAL �ȊO�̌`���̃C���[�W�� DX_BASEIMAGE_FORMAT_NORMAL �`���̃C���[�W�ɕϊ�����
extern	int			NS_ConvertPremulAlphaBaseImage(   BASEIMAGE *BaseImage ) ;																																		// �ʏ�̃��`�����l���t���摜����Z�ς݃��`�����l���t���摜�ɕϊ�����( �s�N�Z���t�H�[�}�b�g�� ARGB8 �ȊO�̏ꍇ�� ARGB8 �ɕϊ�����܂� )
extern	int			NS_ConvertInterpAlphaBaseImage(   BASEIMAGE *BaseImage ) ;																																		// ��Z�ς݃��`�����l���t���摜��ʏ�̃��`�����l���t���摜�ɕϊ�����( �s�N�Z���t�H�[�}�b�g�� ARGB8 �ȊO�̏ꍇ�� ARGB8 �ɕϊ�����܂� )

extern	int			NS_GetDrawScreenBaseImage(        int x1, int y1, int x2, int y2, BASEIMAGE *BaseImage ) ;																										// �`��Ώۂ̉�ʂ���w��̈����{�C���[�W�f�[�^�ɓ]������
extern	int			NS_GetDrawScreenBaseImageDestPos( int x1, int y1, int x2, int y2, BASEIMAGE *BaseImage, int DestX, int DestY ) ;																				// �`��Ώۂ̉�ʂ���w��̈����{�C���[�W�f�[�^�ɓ]������( �]������W�w��� )
#ifdef WINDOWS_DESKTOP_OS
extern	int			NS_UpdateLayerdWindowForBaseImage(                    const BASEIMAGE *BaseImage ) ;																											// ��{�C���[�W�f�[�^���g�p���� UpdateLayerdWindow ���s��
extern	int			NS_UpdateLayerdWindowForBaseImageRect(                   const BASEIMAGE *BaseImage, int x1, int y1, int x2, int y2 ) ;																		// ��{�C���[�W�f�[�^�̎w��͈̔͂��g�p���� UpdateLayerdWindow ���s��
extern	int			NS_UpdateLayerdWindowForPremultipliedAlphaBaseImage(  const BASEIMAGE *BaseImage ) ;																											// ��Z�ς݃A���t�@�̊�{�C���[�W�f�[�^���g�p���� UpdateLayerdWindow ���s��
extern	int			NS_UpdateLayerdWindowForPremultipliedAlphaBaseImageRect( const BASEIMAGE *BaseImage, int x1, int y1, int x2, int y2 ) ;																		// ��Z�ς݃A���t�@�̊�{�C���[�W�f�[�^�̎w��͈̔͂��g�p���� UpdateLayerdWindow ���s��

// �f�X�N�g�b�v�L���v�`��
extern	int			NS_GetDesktopScreenBaseImage( int x1, int y1, int x2, int y2, BASEIMAGE *BaseImage, int DestX, int DestY ) ;						// �f�X�N�g�b�v�̎w��̗̈����{�C���[�W�f�[�^�ɓ]������
#endif // WINDOWS_DESKTOP_OS
extern	int			NS_FillBaseImage(                       BASEIMAGE *BaseImage, int r, int g, int b, int a ) ;																											// ��{�C���[�W�f�[�^���w��̐F�œh��Ԃ�
extern	int			NS_FillRectBaseImage(                   BASEIMAGE *BaseImage, int x, int y, int w, int h, int r, int g, int b, int a ) ;																				// ��{�C���[�W�f�[�^�̎w��̗̈���w��̐F�œh��Ԃ�
extern	int			NS_ClearRectBaseImage(                  BASEIMAGE *BaseImage, int x, int y, int w, int h ) ;																											// ��{�C���[�W�f�[�^�̎w��̗̈���O�N���A����
extern	int			NS_GetPaletteBaseImage(           const BASEIMAGE *BaseImage, int PaletteNo, int *r, int *g, int *b, int *a ) ;																						// ��{�C���[�W�f�[�^�̃p���b�g���擾����
extern	int			NS_SetPaletteBaseImage(                 BASEIMAGE *BaseImage, int PaletteNo, int  r, int  g, int  b, int  a ) ;																						// ��{�C���[�W�f�[�^�̃p���b�g���Z�b�g����
extern	int			NS_SetPixelPalCodeBaseImage(            BASEIMAGE *BaseImage, int x, int y, int palNo ) ;																												// ��{�C���[�W�f�[�^�̎w��̍��W�̐F�R�[�h��ύX����(�p���b�g�摜�p)
extern	int			NS_GetPixelPalCodeBaseImage(      const BASEIMAGE *BaseImage, int x, int y ) ;																															// ��{�C���[�W�f�[�^�̎w��̍��W�̐F�R�[�h���擾����(�p���b�g�摜�p)
extern	int			NS_SetPixelBaseImage(                   BASEIMAGE *BaseImage, int x, int y, int  r, int  g, int  b, int  a ) ;																							// ��{�C���[�W�f�[�^�̎w��̍��W�̐F��ύX����(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_SetPixelBaseImageF(                  BASEIMAGE *BaseImage, int x, int y, float  r, float  g, float  b, float  a ) ;																					// ��{�C���[�W�f�[�^�̎w��̍��W�̐F��ύX����(�e�F�v�f�͕��������_��)
extern	int			NS_GetPixelBaseImage(             const BASEIMAGE *BaseImage, int x, int y, int *r, int *g, int *b, int *a ) ;																							// ��{�C���[�W�f�[�^�̎w��̍��W�̐F���擾����(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_GetPixelBaseImageF(            const BASEIMAGE *BaseImage, int x, int y, float *r, float *g, float *b, float *a ) ;																					// ��{�C���[�W�f�[�^�̎w��̍��W�̐F���擾����(�e�F�v�f�͕��������_��)
extern	int			NS_DrawLineBaseImage(                   BASEIMAGE *BaseImage, int x1, int y1, int x2, int y2, int r, int g, int b, int a ) ;																			// ��{�C���[�W�f�[�^�̎w��̍��W�ɐ���`�悷��(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_DrawCircleBaseImage(                 BASEIMAGE *BaseImage, int x, int y, int radius, int r, int g, int b, int a, int FillFlag = TRUE ) ;															// ��{�C���[�W�f�[�^�̎w��̍��W�ɉ~��`�悷��(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_BltBaseImage(                        int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage ) ;									// ��{�C���[�W�f�[�^��ʂ̊�{�C���[�W�f�[�^�ɓ]������
#ifndef DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_BltBaseImage(                                                                        int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage ) ;									// ��{�C���[�W�f�[�^��ʂ̊�{�C���[�W�f�[�^�ɓ]������
#endif // DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_BltBaseImage2(                                                                       int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage ) ;									// ��{�C���[�W�f�[�^��ʂ̊�{�C���[�W�f�[�^�ɓ]������
extern	int			NS_BltBaseImageWithTransColor(          int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage, int Tr, int Tg, int Tb, int Ta ) ;	// ��{�C���[�W�f�[�^��ʂ̊�{�C���[�W�f�[�^�ɓ��ߐF�����t���œ]������
extern	int			NS_BltBaseImageWithAlphaBlend(          int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage, int Opacity = 255 ) ;					// ��{�C���[�W�f�[�^��ʂ̊�{�C���[�W�f�[�^�ɃA���t�@�l�̃u�����h���l��������œ]������( Opacity �͓����x : 0( ���S���� ) �` 255( ���S�s���� ) )( �o�͐悪 ARGB8 �`���ȊO�̏ꍇ�̓G���[�ɂȂ�܂� )
extern	int			NS_ReverseBaseImageH(                   BASEIMAGE *BaseImage ) ;																																		// ��{�C���[�W�f�[�^�����E���]����
extern	int			NS_ReverseBaseImageV(                   BASEIMAGE *BaseImage ) ;																																		// ��{�C���[�W�f�[�^���㉺���]����
extern	int			NS_ReverseBaseImage(                    BASEIMAGE *BaseImage ) ;																																		// ��{�C���[�W�f�[�^���㉺���E���]����
extern	int			NS_CheckPixelAlphaBaseImage(      const BASEIMAGE *BaseImage ) ;																																		// ��{�C���[�W�f�[�^�Ɋ܂܂��s�N�Z���̃A���t�@�l���`�F�b�N����( �߂�l   -1:�G���[  0:�摜�ɃA���t�@����������  1:�摜�ɃA���t�@����������A���ׂčő�(255)�l  2:�摜�ɃA���t�@����������A���݂���A���t�@�l�͍ŏ�(0)�ƍő�(255)�������͍ŏ�(0)�̂݁@3:�摜�ɃA���t�@����������A�ŏ��ƍő�ȊO�̒��Ԃ̒l������ )  
extern	int			NS_GetBaseImageUseMaxPaletteNo(   const BASEIMAGE *BaseImage ) ;																																		// ��{�C���[�W�f�[�^�Ŏg�p����Ă���p���b�g�ԍ��̍ő�l���擾����( �p���b�g�摜�ł͖����ꍇ�� -1 ���Ԃ� )

#ifndef DX_NON_JPEGREAD
extern	int			NS_ReadJpegExif(                  const TCHAR *JpegFilePath, BYTE *ExifBuffer, size_t ExifBufferSize ) ;																									// JPEG�t�@�C���� Exif�����擾����AExifBuffer �� NULL �ɓn���ƁA�߂�l�̏��̃T�C�Y�̂ݎ擾�ł��܂�( �߂�l  -1:�G���[  -1�ȊO�FExif���̃T�C�Y )
extern	int			NS_ReadJpegExifWithStrLen(          const TCHAR *JpegFilePath, size_t JpegFilePathLength, BYTE *ExifBuffer_Array, size_t ExifBufferSize ) ;																		// JPEG�t�@�C���� Exif�����擾����AExifBuffer �� NULL �ɓn���ƁA�߂�l�̏��̃T�C�Y�̂ݎ擾�ł��܂�( �߂�l  -1:�G���[  -1�ȊO�FExif���̃T�C�Y )
#endif // DX_NON_JPEGREAD

#ifndef DX_NON_SAVEFUNCTION

extern	int			NS_SaveBaseImageToBmp(            const TCHAR *FilePath, const BASEIMAGE *BaseImage ) ;																										// ��{�C���[�W�f�[�^���a�l�o�摜�Ƃ��ĕۑ�����
extern	int			NS_SaveBaseImageToBmpWithStrLen(    const TCHAR *FilePath, size_t FilePathLength, const BASEIMAGE *BaseImage ) ;																										// ��{�C���[�W�f�[�^���a�l�o�摜�Ƃ��ĕۑ�����
extern	int			NS_SaveBaseImageToDds(              const TCHAR *FilePath,                        const BASEIMAGE *BaseImage ) ;																										// ��{�C���[�W�f�[�^���c�c�r�摜�Ƃ��ĕۑ�����
extern	int			NS_SaveBaseImageToDdsWithStrLen(    const TCHAR *FilePath, size_t FilePathLength, const BASEIMAGE *BaseImage ) ;																										// ��{�C���[�W�f�[�^���c�c�r�摜�Ƃ��ĕۑ�����
#ifndef DX_NON_PNGREAD
extern	int			NS_SaveBaseImageToPng(              const TCHAR *FilePath,                        BASEIMAGE *BaseImage, int CompressionLevel ) ;																					// ��{�C���[�W�f�[�^���o�m�f�摜�Ƃ��ĕۑ�����
extern	int			NS_SaveBaseImageToPngWithStrLen(    const TCHAR *FilePath, size_t FilePathLength, BASEIMAGE *BaseImage, int CompressionLevel ) ;																					// ��{�C���[�W�f�[�^���o�m�f�摜�Ƃ��ĕۑ�����
#endif // DX_NON_PNGREAD
#ifndef DX_NON_JPEGREAD
extern	int			NS_SaveBaseImageToJpeg(             const TCHAR *FilePath,                        BASEIMAGE *BaseImage, int Quality, int Sample2x1 ) ;																			// ��{�C���[�W�f�[�^���i�o�d�f�摜�Ƃ��ĕۑ�����
extern	int			NS_SaveBaseImageToJpegWithStrLen(   const TCHAR *FilePath, size_t FilePathLength, BASEIMAGE *BaseImage, int Quality, int Sample2x1 ) ;																			// ��{�C���[�W�f�[�^���i�o�d�f�摜�Ƃ��ĕۑ�����
#endif // DX_NON_JPEGREAD

#endif // DX_NON_SAVEFUNCTION

// ��{�C���[�W�`��
extern	int			NS_DrawBaseImage(					int x, int y, BASEIMAGE *BaseImage ) ;																												// ��{�C���[�W�f�[�^��`�悷��

// �J���[�}�b�`���O���Ȃ���C���[�W�f�[�^�ԓ]�����s�� Ver2
extern int			NS_GraphColorMatchBltVer2(       void *DestGraphData, int DestPitch,  const COLORDATA *DestColorData,
											const void *SrcGraphData,  int SrcPitch,   const COLORDATA *SrcColorData,
											const void *AlphaMask,     int AlphaPitch, const COLORDATA *AlphaColorData,
											POINT DestPoint, const RECT *SrcRect, int ReverseFlag,
											int TransColorAlphaTestFlag, unsigned int TransColor,
											int ImageShavedMode, int AlphaOnlyFlag = FALSE ,
											int RedIsAlphaFlag = FALSE , int TransColorNoMoveFlag = FALSE ,
											int Pal8ColorMatch = FALSE ) ;


// �F���擾�֌W
extern	COLOR_F			NS_GetColorF(              float Red, float Green, float Blue, float Alpha ) ;												// ���������_�^�̃J���[�l���쐬����
extern	COLOR_U8		NS_GetColorU8(             int Red, int Green, int Blue, int Alpha ) ;														// �����Ȃ������W�r�b�g�̃J���[�l���쐬����
extern	unsigned int	NS_GetColor(               int Red, int Green, int Blue ) ;																	// DrawPixel ���̕`��֐��Ŏg�p����J���[�l���擾����
extern	int				NS_GetColor2(              unsigned int Color, int *Red, int *Green, int *Blue ) ;													// �J���[�l����ԁA�΁A�̒l���擾����
extern	unsigned int	NS_GetColor3(              const COLORDATA *ColorData, int Red, int Green, int Blue, int Alpha = 255 ) ;					// �w��̃s�N�Z���t�H�[�}�b�g�ɑΉ������J���[�l�𓾂�
extern	unsigned int	NS_GetColor4(              const COLORDATA *DestColorData, const COLORDATA* SrcColorData, unsigned int SrcColor ) ;				// �w��̃J���[�t�H�[�}�b�g�̃J���[�l��ʂ̃J���[�t�H�[�}�b�g�̃J���[�l�ɕϊ�����
extern	int				NS_GetColor5(              const COLORDATA *ColorData, unsigned int Color, int *Red, int *Green, int *Blue, int *Alpha = NULL ) ;	// �w��̃J���[�t�H�[�}�b�g�̃J���[�l��ԁA�΁A�A�A���t�@�̒l���擾����
extern	int				NS_CreatePaletteColorData( COLORDATA *ColorDataBuf ) ;																		// �p���b�g�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateARGBF32ColorData( COLORDATA *ColorDataBuf ) ;																		// �`�q�f�a�e�`�����l�� 32bit ���������_�^�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateARGBF16ColorData( COLORDATA *ColorDataBuf ) ;																		// �`�q�f�a�e�`�����l�� 16bit ���������_�^�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateXRGB8ColorData(   COLORDATA *ColorDataBuf ) ;																		// �w�q�f�a�W�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateARGB8ColorData(   COLORDATA *ColorDataBuf ) ;																		// �`�q�f�a�W�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateRGBA8ColorData(    COLORDATA *ColorDataBuf ) ;																			// �q�f�a�`�W�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateABGR8ColorData(    COLORDATA *ColorDataBuf ) ;																			// �`�a�f�q�W�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateBGRA8ColorData(    COLORDATA *ColorDataBuf ) ;																			// �a�f�q�`�W�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateBGR8ColorData(     COLORDATA *ColorDataBuf ) ;																			// �a�f�q�W�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateARGB4ColorData(   COLORDATA *ColorDataBuf ) ;																		// �`�q�f�a�S�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateA1R5G5B5ColorData( COLORDATA *ColorDataBuf ) ;																		// �`�P�q�T�f�T�a�T�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateX1R5G5B5ColorData( COLORDATA *ColorDataBuf ) ;																		// �w�P�q�T�f�T�a�T�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateR5G5B5A1ColorData( COLORDATA *ColorDataBuf ) ;																		// �q�T�f�T�a�T�`�P�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateR5G6B5ColorData(   COLORDATA *ColorDataBuf ) ;																		// �q�T�f�U�a�T�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateFullColorData(    COLORDATA *ColorDataBuf ) ;																		// �Q�S�r�b�g�J���[�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateGrayColorData(    COLORDATA *ColorDataBuf ) ;																		// �O���[�X�P�[���̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreatePal8ColorData(    COLORDATA *ColorDataBuf, int UseAlpha = FALSE ) ;													// �p���b�g�Q�T�U�F�̃J���[�t�H�[�}�b�g���\�z����
extern	int				NS_CreateColorData(        COLORDATA *ColorDataBuf, int ColorBitDepth,
													DWORD RedMask, DWORD GreenMask, DWORD BlueMask, DWORD AlphaMask,
													int ChannelNum = 0, int ChannelBitDepth = 0, int FloatTypeFlag = FALSE ) ;						// �J���[�t�H�[�}�b�g���쐬����
extern	void			NS_SetColorDataNoneMask(   COLORDATA *ColorData ) ;																		// NoneMask �ȊO�̗v�f�𖄂߂� COLORDATA �\���̂̏������� NoneMask ���Z�b�g����
extern	int				NS_CmpColorData(           const COLORDATA *ColorData1, const COLORDATA *ColorData2 ) ;									// ��̃J���[�t�H�[�}�b�g�����������ǂ������ׂ�( �߂�l�@TRUE:������  FALSE:�������Ȃ� )














// DxSoftImage.cpp�֐��v���g�^�C�v�錾
#ifndef DX_NON_SOFTIMAGE
extern	int			NS_InitSoftImage(                   void ) ;																			// �\�t�g�E�G�A�ň����C���[�W��S�ĉ������
extern	int			NS_LoadSoftImage(                   const TCHAR *FileName ) ;															// �摜�t�@�C����ǂݍ��݃\�t�g�E�G�A�C���[�W�n���h�����쐬����( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )
extern	int			NS_LoadSoftImageWithStrLen(              const TCHAR *FileName, size_t FileNameLength ) ;									// �摜�t�@�C����ǂݍ��݃\�t�g�E�G�A�C���[�W�n���h�����쐬����( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )
extern	int			NS_LoadARGB8ColorSoftImage(              const TCHAR *FileName                        ) ;									// �摜�t�@�C����ǂݍ��݃\�t�g�E�G�A�C���[�W�n���h�����쐬����( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )( �ǂݍ��񂾉摜�� RGBA8 �ȊO�̃t�H�[�}�b�g�������ꍇ�� RGBA8 �J���[�ɕϊ� )
extern	int			NS_LoadARGB8ColorSoftImageWithStrLen(    const TCHAR *FileName, size_t FileNameLength ) ;									// �摜�t�@�C����ǂݍ��݃\�t�g�E�G�A�C���[�W�n���h�����쐬����( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )( �ǂݍ��񂾉摜�� RGBA8 �ȊO�̃t�H�[�}�b�g�������ꍇ�� RGBA8 �J���[�ɕϊ� )
extern	int			NS_LoadXRGB8ColorSoftImage(              const TCHAR *FileName                        ) ;									// �摜�t�@�C����ǂݍ��݃\�t�g�E�G�A�C���[�W�n���h�����쐬����( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )( �ǂݍ��񂾉摜�� XGBA8 �ȊO�̃t�H�[�}�b�g�������ꍇ�� XGBA8 �J���[�ɕϊ� )
extern	int			NS_LoadXRGB8ColorSoftImageWithStrLen(    const TCHAR *FileName, size_t FileNameLength ) ;									// �摜�t�@�C����ǂݍ��݃\�t�g�E�G�A�C���[�W�n���h�����쐬����( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )( �ǂݍ��񂾉摜�� XGBA8 �ȊO�̃t�H�[�}�b�g�������ꍇ�� XGBA8 �J���[�ɕϊ� )
extern	int			NS_LoadSoftImageToMem(              const void *FileImage, int FileImageSize ) ;										// ��������ɓW�J���ꂽ�摜�t�@�C���C���[�W����\�t�g�E�G�A�C���[�W�n���h�����쐬����( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )
extern	int			NS_LoadARGB8ColorSoftImageToMem(    const void *FileImage, int FileImageSize ) ;										// ��������ɓW�J���ꂽ�摜�t�@�C���C���[�W����\�t�g�E�G�A�C���[�W�n���h�����쐬����( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )( �ǂݍ��񂾉摜�� RGBA8 �ȊO�̃t�H�[�}�b�g�������ꍇ�� RGBA8 �J���[�ɕϊ� )
extern	int			NS_LoadXRGB8ColorSoftImageToMem(    const void *FileImage, int FileImageSize ) ;										// ��������ɓW�J���ꂽ�摜�t�@�C���C���[�W����\�t�g�E�G�A�C���[�W�n���h�����쐬����( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )( �ǂݍ��񂾉摜�� XGBA8 �ȊO�̃t�H�[�}�b�g�������ꍇ�� XGBA8 �J���[�ɕϊ� )
extern	int			NS_MakeSoftImage(                   int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )
extern	int			NS_MakeARGBF32ColorSoftImage(       int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�C���[�W�n���h���̍쐬( RGBA �e�`�����l�� 32bit ���������_�^ �J���[ )
extern	int			NS_MakeARGBF16ColorSoftImage(       int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�C���[�W�n���h���̍쐬( RGBA �e�`�����l�� 16bit ���������_�^ �J���[ )
extern	int			NS_MakeARGB8ColorSoftImage(         int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( RGBA8 �J���[ )
extern	int			NS_MakeXRGB8ColorSoftImage(         int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( XRGB8 �J���[ )
extern	int			NS_MakeRGBA8ColorSoftImage(              int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�C���[�W�n���h���̍쐬( RGBA8 �J���[ )
extern	int			NS_MakeABGR8ColorSoftImage(              int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�C���[�W�n���h���̍쐬( ABGR8 �J���[ )
extern	int			NS_MakeBGRA8ColorSoftImage(              int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�C���[�W�n���h���̍쐬( BGRA8 �J���[ )
extern	int			NS_MakeARGB4ColorSoftImage(         int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( ARGB4 �J���[ )
extern	int			NS_MakeA1R5G5B5ColorSoftImage(      int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�C���[�W�n���h���̍쐬( A1R5G5B5 �J���[ )
extern	int			NS_MakeX1R5G5B5ColorSoftImage(      int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�C���[�W�n���h���̍쐬( X1R5G5B5 �J���[ )
extern	int			NS_MakeR5G5B5A1ColorSoftImage(      int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�C���[�W�n���h���̍쐬( R5G5B5A1 �J���[ )
extern	int			NS_MakeR5G6B5ColorSoftImage(        int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�C���[�W�n���h���̍쐬( R5G6B5 �J���[ )
extern	int			NS_MakeRGB8ColorSoftImage(          int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( RGB8 �J���[ )
extern	int			NS_MakePAL8ColorSoftImage(          int SizeX, int SizeY, int UseAlpha = FALSE ) ;										// �\�t�g�E�G�A�ň����C���[�W�̍쐬( �p���b�g�Q�T�U�F �J���[ )
extern	int			NS_MakeColorDataSoftImage(          int SizeX, int SizeY, const COLORDATA *ColorData ) ;								// �\�t�g�E�G�A�C���[�W�n���h���̍쐬( COLORDATA �Ńt�H�[�}�b�g�w�� )

extern	int			NS_DeleteSoftImage(                 int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̉��

extern	int			NS_GetSoftImageSize(                int SIHandle, int *Width, int *Height ) ;											// �\�t�g�E�G�A�ň����C���[�W�̃T�C�Y���擾����
extern	int			NS_CheckPaletteSoftImage(           int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W���p���b�g�摜���ǂ������擾����( TRUE:�p���b�g�摜  FALSE:�p���b�g�摜����Ȃ� )
extern	int			NS_CheckAlphaSoftImage(             int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̃t�H�[�}�b�g�Ƀ��v�f�����邩�ǂ������擾����( TRUE:����  FALSE:�Ȃ� )
extern	int			NS_CheckPixelAlphaSoftImage(        int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�Ɋ܂܂��s�N�Z���̃A���t�@�l���`�F�b�N����( �߂�l   -1:�G���[  0:�摜�ɃA���t�@����������  1:�摜�ɃA���t�@����������A���ׂčő�(255)�l  2:�摜�ɃA���t�@����������A���݂���A���t�@�l�͍ŏ�(0)�ƍő�(255)�������͍ŏ�(0)�̂݁@3:�摜�ɃA���t�@����������A�ŏ��ƍő�ȊO�̒��Ԃ̒l������ )  

extern	int			NS_GetDrawScreenSoftImage(          int x1, int y1, int x2, int y2, int SIHandle ) ;									// �`��Ώۂ̉�ʂ���w��̈�̃O���t�B�b�N���\�t�g�E�G�A�ň����C���[�W�ɓ]������
extern	int			NS_GetDrawScreenSoftImageDestPos(   int x1, int y1, int x2, int y2, int SIHandle, int DestX, int DestY ) ;				// �`��Ώۂ̉�ʂ���w��̈���\�t�g�E�G�A�C���[�W�n���h���ɓ]������( �]������W�w��� )
#ifdef WINDOWS_DESKTOP_OS
extern	int			NS_UpdateLayerdWindowForSoftImage(                       int SIHandle ) ;												// �\�t�g�E�G�A�C���[�W�n���h�����g�p���� UpdateLayerdWindow ���s��
extern	int			NS_UpdateLayerdWindowForSoftImageRect(                   int SIHandle, int x1, int y1, int x2, int y2 ) ;				// �\�t�g�E�G�A�C���[�W�n���h���̎w��͈̔͂��g�p���� UpdateLayerdWindow ���s��
extern	int			NS_UpdateLayerdWindowForPremultipliedAlphaSoftImage(     int SIHandle ) ;												// ��Z�ς݃A���t�@�̃\�t�g�E�G�A�C���[�W�n���h�����g�p���� UpdateLayerdWindow ���s��
extern	int			NS_UpdateLayerdWindowForPremultipliedAlphaSoftImageRect( int SIHandle, int x1, int y1, int x2, int y2 ) ;				// ��Z�ς݃A���t�@�̃\�t�g�E�G�A�C���[�W�n���h���̎w��͈̔͂��g�p���� UpdateLayerdWindow ���s��
extern	int			NS_GetDesktopScreenSoftImage( int x1, int y1, int x2, int y2, int SIHandle,         int DestX, int DestY ) ;						// �f�X�N�g�b�v�̎w��̗̈���\�t�g�E�G�A�C���[�W�n���h���ɓ]������
#endif // WINDOWS_DESKTOP_OS
extern	int			NS_FillSoftImage(                   int SIHandle, int r, int g, int b, int a ) ;										// �\�t�g�E�G�A�ň����C���[�W���w��F�œh��Ԃ�(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_ClearRectSoftImage(              int SIHandle, int x, int y, int w, int h ) ;										// �\�t�g�E�G�A�ň����C���[�W�̎w��̗̈���O�N���A����
extern	int			NS_GetPaletteSoftImage(             int SIHandle, int PaletteNo, int *r, int *g, int *b, int *a ) ;					// �\�t�g�E�G�A�ň����C���[�W�̃p���b�g���擾����(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_SetPaletteSoftImage(             int SIHandle, int PaletteNo, int  r, int  g, int  b, int  a ) ;					// �\�t�g�E�G�A�ň����C���[�W�̃p���b�g���Z�b�g����(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_DrawPixelPalCodeSoftImage(       int SIHandle, int x, int y, int palNo ) ;											// �\�t�g�E�G�A�ň����C���[�W�̎w����W�Ƀh�b�g��`�悷��(�p���b�g�摜�p�A�L���l�͂O�`�Q�T�T)
extern	int			NS_GetPixelPalCodeSoftImage(        int SIHandle, int x, int y ) ;														// �\�t�g�E�G�A�ň����C���[�W�̎w����W�̐F�R�[�h���擾����(�p���b�g�摜�p�A�߂�l�͂O�`�Q�T�T)
extern	void		*NS_GetImageAddressSoftImage(       int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̎��C���[�W���i�[����Ă��郁�����̈�̐擪�A�h���X���擾����
extern	int			NS_GetPitchSoftImage(               int SIHandle ) ;																	// �\�t�g�E�G�A�C���[�W�n���h���̃������Ɋi�[����Ă���摜�̃s�b�`( 1���C���ӂ�̃o�C�g�� )���擾����
extern	int			NS_DrawPixelSoftImage(              int SIHandle, int x, int y, int  r, int  g, int  b, int  a ) ;						// �\�t�g�E�G�A�ň����C���[�W�̎w����W�Ƀh�b�g��`�悷��(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_DrawPixelSoftImageF(             int SIHandle, int x, int y, float  r, float  g, float  b, float  a ) ;				// �\�t�g�E�G�A�C���[�W�n���h���̎w����W�Ƀh�b�g��`�悷��(�e�F�v�f�͕��������_��)
extern	void		NS_DrawPixelSoftImage_Unsafe_XRGB8( int SIHandle, int x, int y, int  r, int  g, int  b ) ;								// �\�t�g�E�G�A�ň����C���[�W�̎w����W�Ƀh�b�g��`�悷��(�e�F�v�f�͂O�`�Q�T�T)�A�G���[�`�F�b�N�����Ȃ�����ɍ����ł����A�͈͊O�̍��W�� ARGB8 �ȊO�̃t�H�[�}�b�g�̃\�t�g�n���h����n���ƕs���ȃ������A�N�Z�X�ŋ����I�����܂�
extern	void		NS_DrawPixelSoftImage_Unsafe_ARGB8( int SIHandle, int x, int y, int  r, int  g, int  b, int  a ) ;						// �\�t�g�E�G�A�ň����C���[�W�̎w����W�Ƀh�b�g��`�悷��(�e�F�v�f�͂O�`�Q�T�T)�A�G���[�`�F�b�N�����Ȃ�����ɍ����ł����A�͈͊O�̍��W�� XRGB8 �ȊO�̃t�H�[�}�b�g�̃\�t�g�n���h����n���ƕs���ȃ������A�N�Z�X�ŋ����I�����܂�
extern	int			NS_GetPixelSoftImage(               int SIHandle, int x, int y, int *r, int *g, int *b, int *a ) ;						// �\�t�g�E�G�A�ň����C���[�W�̎w����W�̐F���擾����(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_GetPixelSoftImageF(              int SIHandle, int x, int y, float *r, float *g, float *b, float *a ) ;				// �\�t�g�E�G�A�C���[�W�n���h���̎w����W�̐F���擾����(�e�F�v�f�͕��������_��)
extern	void		NS_GetPixelSoftImage_Unsafe_XRGB8(  int SIHandle, int x, int y, int *r, int *g, int *b ) ;								// �\�t�g�E�G�A�ň����C���[�W�̎w����W�̐F���擾����(�e�F�v�f�͂O�`�Q�T�T)�A�G���[�`�F�b�N�����Ȃ�����ɍ����ł����A�͈͊O�̍��W�� XRGB8 �ȊO�̃t�H�[�}�b�g�̃\�t�g�n���h����n���ƕs���ȃ������A�N�Z�X�ŋ����I�����܂�
extern	void		NS_GetPixelSoftImage_Unsafe_ARGB8(  int SIHandle, int x, int y, int *r, int *g, int *b, int *a ) ;						// �\�t�g�E�G�A�ň����C���[�W�̎w����W�̐F���擾����(�e�F�v�f�͂O�`�Q�T�T)�A�G���[�`�F�b�N�����Ȃ�����ɍ����ł����A�͈͊O�̍��W�� ARGB8 �ȊO�̃t�H�[�}�b�g�̃\�t�g�n���h����n���ƕs���ȃ������A�N�Z�X�ŋ����I�����܂�
extern	int			NS_DrawLineSoftImage(               int SIHandle, int x1, int y1, int x2, int y2, int r, int g, int b, int a ) ;		// �\�t�g�E�G�A�ň����C���[�W�̎w����W�ɐ���`�悷��(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_DrawCircleSoftImage(             int SIHandle, int x, int y, int radius, int r, int g, int b, int a, int FillFlag = TRUE ) ;	// �\�t�g�E�G�A�C���[�W�n���h���̎w����W�ɉ~��`�悷��(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_BltSoftImage(                    int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int SrcSIHandle, int DestX, int DestY, int DestSIHandle ) ;									// �\�t�g�E�G�A�ň����C���[�W��ʂ̃C���[�W��ɓ]������
extern	int			NS_BltSoftImageWithTransColor(      int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int SrcSIHandle, int DestX, int DestY, int DestSIHandle, int Tr, int Tg, int Tb, int Ta ) ;	// �\�t�g�E�G�A�ň����C���[�W�𓧉ߐF�����t���œ]������
extern	int			NS_BltSoftImageWithAlphaBlend(      int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int SrcSIHandle, int DestX, int DestY, int DestSIHandle, int Opacity = 255 ) ;					// �\�t�g�E�G�A�ň����C���[�W���A���t�@�l�̃u�����h���l��������œ]������( Opacity �͓����x : 0( ���S���� ) �` 255( ���S�s���� ) )( �o�͐悪 ARGB8 �`���ȊO�̏ꍇ�̓G���[�ɂȂ�܂� )
extern	int			NS_ReverseSoftImageH(               int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̍��E�𔽓]����
extern	int			NS_ReverseSoftImageV(               int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̏㉺�𔽓]����
extern	int			NS_ReverseSoftImage(                int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̏㉺���E�𔽓]����
extern	int			NS_ConvertPremulAlphaSoftImage(          int SIHandle ) ;																	// �ʏ�̃��`�����l���t���摜����Z�ς݃��`�����l���t���摜�ɕϊ�����( �s�N�Z���t�H�[�}�b�g�� ARGB8 �ȊO�̏ꍇ�� ARGB8 �ɕϊ�����܂� )
extern	int			NS_ConvertInterpAlphaSoftImage(          int SIHandle ) ;																	// ��Z�ς݃��`�����l���t���摜��ʏ�̃��`�����l���t���摜�ɕϊ�����( �s�N�Z���t�H�[�}�b�g�� ARGB8 �ȊO�̏ꍇ�� ARGB8 �ɕϊ�����܂� )

#ifndef DX_NON_FONT
extern	int			NS_BltStringSoftImage(              int x, int y, const TCHAR *StrData, int DestSIHandle, int DestEdgeSIHandle = -1 ,                                        int VerticalFlag = FALSE ) ;		// �\�t�g�E�G�A�ň����C���[�W�ɕ�����C���[�W��]������
extern	int			NS_BltStringSoftImageWithStrLen(         int x, int y, const TCHAR *StrData, size_t StrDataLength, int DestSIHandle, int DestEdgeSIHandle = -1 ,                                        int VerticalFlag = FALSE ) ;		// �\�t�g�E�G�A�C���[�W�n���h���ɕ������`�悷��( �f�t�H���g�t�H���g�n���h�����g�p���� )
extern	int			NS_BltStringSoftImageToHandle(           int x, int y, const TCHAR *StrData,                       int DestSIHandle, int DestEdgeSIHandle /* �����K�v�Ȃ��ꍇ�� -1 */ , int FontHandle, int VerticalFlag = FALSE ) ;		// �\�t�g�E�G�A�C���[�W�n���h���ɕ������`�悷��( �t�H���g�n���h���g�p�� )
extern	int			NS_BltStringSoftImageToHandleWithStrLen( int x, int y, const TCHAR *StrData, size_t StrDataLength, int DestSIHandle, int DestEdgeSIHandle /* �����K�v�Ȃ��ꍇ�� -1 */ , int FontHandle, int VerticalFlag = FALSE ) ;		// �\�t�g�E�G�A�C���[�W�n���h���ɕ������`�悷��( �t�H���g�n���h���g�p�� )
#endif // DX_NON_FONT

extern	int			NS_DrawSoftImage(                   int x, int y, int SIHandle ) ;														// �\�t�g�E�G�A�ň����C���[�W����ʂɕ`�悷��

#ifndef DX_NON_SAVEFUNCTION

extern	int			NS_SaveSoftImageToBmp(              const TCHAR *FilePath, int SIHandle ) ;											// �\�t�g�E�G�A�ň����C���[�W���a�l�o�摜�t�@�C���Ƃ��ĕۑ�����
extern	int			NS_SaveSoftImageToBmpWithStrLen(         const TCHAR *FilePath, size_t FilePathLength, int SIHandle ) ;											// �\�t�g�E�G�A�C���[�W�n���h�����a�l�o�摜�t�@�C���Ƃ��ĕۑ�����
extern	int			NS_SaveSoftImageToDds(                   const TCHAR *FilePath,                        int SIHandle ) ;											// �\�t�g�E�G�A�C���[�W�n���h�����c�c�r�摜�t�@�C���Ƃ��ĕۑ�����
extern	int			NS_SaveSoftImageToDdsWithStrLen(         const TCHAR *FilePath, size_t FilePathLength, int SIHandle ) ;											// �\�t�g�E�G�A�C���[�W�n���h�����c�c�r�摜�t�@�C���Ƃ��ĕۑ�����
#ifndef DX_NON_PNGREAD
extern	int			NS_SaveSoftImageToPng(              const TCHAR *FilePath, int SIHandle, int CompressionLevel ) ;						// �\�t�g�E�G�A�ň����C���[�W���o�m�f�摜�t�@�C���Ƃ��ĕۑ����� CompressionLevel = ���k���A�l���傫���قǍ����k�������ׁA�O�͖����k,0�`9
extern	int			NS_SaveSoftImageToPngWithStrLen(         const TCHAR *FilePath, size_t FilePathLength, int SIHandle, int CompressionLevel ) ;						// �\�t�g�E�G�A�C���[�W�n���h�����o�m�f�摜�t�@�C���Ƃ��ĕۑ����� CompressionLevel = ���k���A�l���傫���قǍ����k�������ׁA�O�͖����k,0�`9
#endif
#ifndef DX_NON_JPEGREAD
extern	int			NS_SaveSoftImageToJpeg(             const TCHAR *FilePath, int SIHandle, int Quality, int Sample2x1 ) ;				// �\�t�g�E�G�A�ň����C���[�W���i�o�d�f�摜�t�@�C���Ƃ��ĕۑ����� Quality = �掿�A�l���傫���قǒሳ�k���掿,0�`100 
extern	int			NS_SaveSoftImageToJpegWithStrLen(        const TCHAR *FilePath, size_t FilePathLength, int SIHandle, int Quality, int Sample2x1 ) ;				// �\�t�g�E�G�A�C���[�W�n���h�����i�o�d�f�摜�t�@�C���Ƃ��ĕۑ����� Quality = �掿�A�l���傫���قǒሳ�k���掿,0�`100 
#endif

#endif // DX_NON_SAVEFUNCTION

#endif // DX_NON_SOFTIMAGE















#ifndef DX_NON_SOUND

// DxSound.cpp�֐��v���g�^�C�v�錾

// �T�E���h�f�[�^�Ǘ��n�֐�
extern	int			NS_InitSoundMem(                        void ) ;																				// �S�ẴT�E���h�n���h�����폜����

extern	int			NS_AddSoundData(                        int Handle = -1 ) ;																											// �T�E���h�n���h�����쐬����
extern	int			NS_AddStreamSoundMem(                   STREAMDATA *Stream, int LoopNum,  int SoundHandle, int StreamDataType, int *CanStreamCloseFlag, int UnionHandle = -1 ) ;		// �X�g���[���Đ��^�C�v�̃T�E���h�n���h���ɃX�g���[���f�[�^���Đ��Ώۂɒǉ�����
extern	int			NS_AddStreamSoundMemToMem(              const void *FileImage, size_t FileImageSize, int LoopNum,  int SoundHandle, int StreamDataType, int UnionHandle = -1 ) ;		// �X�g���[���Đ��^�C�v�̃T�E���h�n���h���Ƀ�������ɓW�J�����T�E���h�t�@�C���C���[�W���Đ��Ώۂɒǉ�����
extern	int			NS_AddStreamSoundMemToFile(             const TCHAR *WaveFile,                            int LoopNum,  int SoundHandle, int StreamDataType, int UnionHandle = -1 ) ;	// �X�g���[���Đ��^�C�v�̃T�E���h�n���h���ɃT�E���h�t�@�C�����Đ��Ώۂɒǉ�����
extern	int			NS_AddStreamSoundMemToFileWithStrLen(   const TCHAR *WaveFile, size_t WaveFilePathLength, int LoopNum,  int SoundHandle, int StreamDataType, int UnionHandle = -1 ) ;	// �X�g���[���Đ��^�C�v�̃T�E���h�n���h���ɃT�E���h�t�@�C�����Đ��Ώۂɒǉ�����
extern	int			NS_SetupStreamSoundMem(                 int SoundHandle ) ;																		// �X�g���[���Đ��^�C�v�̃T�E���h�n���h���̍Đ�����������
extern	int			NS_PlayStreamSoundMem(                  int SoundHandle, int PlayType = DX_PLAYTYPE_LOOP , int TopPositionFlag = TRUE ) ;			// �X�g���[���Đ��^�C�v�̃T�E���h�n���h���̍Đ����J�n����
extern	int			NS_CheckStreamSoundMem(                 int SoundHandle ) ;																		// �X�g���[���Đ��^�C�v�̃T�E���h�n���h���̍Đ���Ԃ��擾����
extern	int			NS_StopStreamSoundMem(                  int SoundHandle, int IsNextLoopEnd = FALSE ) ;												// �X�g���[���Đ��^�C�v�̃T�E���h�n���h���̍Đ����~����
extern	int			NS_SetStreamSoundCurrentPosition(       LONGLONG Byte, int SoundHandle ) ;															// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŕύX����(�Đ����~�܂��Ă��鎞�̂ݗL��)
extern	LONGLONG	NS_GetStreamSoundCurrentPosition(       int SoundHandle ) ;																		// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŎ擾����
extern	int			NS_SetStreamSoundCurrentTime(           LONGLONG Time, int SoundHandle ) ;															// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŐݒ肷��(���k�`���̏ꍇ�͐������ݒ肳��Ȃ��ꍇ������)
extern	LONGLONG	NS_GetStreamSoundCurrentTime(           int SoundHandle ) ;																		// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŎ擾����(���k�`���̏ꍇ�͐������l���Ԃ��Ă��Ȃ��ꍇ������)
extern	int			NS_ProcessStreamSoundMem(               int SoundHandle ) ;																		// �X�g���[���Đ��^�C�v�̃T�E���h�n���h���̎����I�ȏ������s���֐�( �����Ŏ����I�ɌĂ΂�܂� )
extern	int			NS_ProcessStreamSoundMemAll(            void ) ;																					// �L���ȃX�g���[���Đ��^�C�v�̃T�E���h�n���h���ɑ΂��� ProcessStreamSoundMem �����s����( �����Ŏ����I�ɌĂ΂�܂� )


extern	int			NS_LoadSoundMem2(                       const TCHAR *FileName1,                         const TCHAR *FileName2                         ) ;	// �O�t���ƃ��[�v���ɕ����ꂽ�T�E���h�t�@�C����ǂݍ��݃T�E���h�n���h�����쐬����
extern	int			NS_LoadSoundMem2WithStrLen(             const TCHAR *FileName1, size_t FileName1Length, const TCHAR *FileName2, size_t FileName2Length ) ;	// �O�t���ƃ��[�v���ɕ����ꂽ�T�E���h�t�@�C����ǂݍ��݃T�E���h�n���h�����쐬����
extern	int			NS_LoadBGM(                             const TCHAR *FileName                        ) ;													// ��ɂa�f�l��ǂݍ��݃T�E���h�n���h�����쐬����̂ɓK�����֐�
extern	int			NS_LoadBGMWithStrLen(                   const TCHAR *FileName, size_t FileNameLength ) ;													// ��ɂa�f�l��ǂݍ��݃T�E���h�n���h�����쐬����̂ɓK�����֐�

extern	int			NS_LoadSoundMemBase(                    const TCHAR *FileName,                        int BufferNum,      int UnionHandle = -1 ) ;			// �T�E���h�t�@�C������T�E���h�n���h�����쐬����
extern	int			NS_LoadSoundMemBaseWithStrLen(          const TCHAR *FileName, size_t FileNameLength, int BufferNum,      int UnionHandle = -1 ) ;			// �T�E���h�t�@�C������T�E���h�n���h�����쐬����
extern	int			NS_LoadSoundMem(                        const TCHAR *FileName,                        int BufferNum = 3 , int UnionHandle = -1 ) ;			// LoadSoundMemBase �̕ʖ��֐�
extern	int			NS_LoadSoundMemWithStrLen(              const TCHAR *FileName, size_t FileNameLength, int BufferNum = 3 , int UnionHandle = -1 ) ;			// LoadSoundMemBase �̕ʖ��֐�
extern	int			NS_LoadSoundMemToBufNumSitei(           const TCHAR *FileName,                        int BufferNum ) ;									// LoadSoundMem ���g�p���ĉ�����
extern	int			NS_LoadSoundMemToBufNumSiteiWithStrLen( const TCHAR *FileName, size_t FileNameLength, int BufferNum ) ;									// LoadSoundMem ���g�p���ĉ�����
extern	int			NS_LoadSoundMemByResource(              const TCHAR *ResourceName, const TCHAR *ResourceType, int BufferNum = 1 ) ;				// �T�E���h���\�[�X����T�E���h�n���h�����쐬����
extern	int			NS_LoadSoundMemByResourceWithStrLen(    const TCHAR *ResourceName, size_t ResourceNameLength, const TCHAR *ResourceType, size_t ResourceTypeLength, int BufferNum = 1 ) ;				// �T�E���h���\�[�X����T�E���h�n���h�����쐬����
extern	int			NS_DuplicateSoundMem(                   int SrcSoundHandle, int BufferNum = 3 ) ;													// �����T�E���h�f�[�^���g�p����T�E���h�n���h�����쐬����( DX_SOUNDDATATYPE_MEMNOPRESS �^�C�v�̃T�E���h�n���h���̂݉\ )

extern	int			NS_LoadSoundMemByMemImageBase(          const void *FileImage, size_t FileImageSize, int BufferNum,      int UnionHandle = -1 ) ;				// ��������ɓW�J���ꂽ�T�E���h�t�@�C���C���[�W����T�E���h�n���h�����쐬����
extern	int			NS_LoadSoundMemByMemImage(              const void *FileImage, size_t FileImageSize, int BufferNum = 3 , int UnionHandle = -1 ) ;				// LoadSoundMemByMemImageBase �̕ʖ��֐�
extern	int			NS_LoadSoundMemByMemImage2(             const void *WaveImage, size_t WaveImageSize, const WAVEFORMATEX *WaveFormat, size_t WaveHeaderSize ) ;	// ��������ɓW�J���ꂽ�o�b�l�f�[�^����T�E���h�n���h�����쐬����
extern	int			NS_LoadSoundMemByMemImageToBufNumSitei( const void *FileImage, size_t FileImageSize, int BufferNum ) ;										// LoadSoundMemByMemImageBase ���g�p���ĉ�����
extern	int			NS_LoadSoundMem2ByMemImage(             const void *FileImage1, size_t FileImageSize1, const void *FileImage2, size_t FileImageSize2 ) ;	// �O�t���ƃ��[�v���ɕ����ꂽ��̃�������ɓW�J���ꂽ�T�E���h�t�@�C���C���[�W����T�E���h�n���h�����쐬����
extern	int			NS_LoadSoundMemFromSoftSound(           int SoftSoundHandle, int BufferNum = 3 ) ;													// �\�t�g�E�G�A�T�E���h�n���h�������T�E���h�f�[�^����T�E���h�n���h�����쐬����

extern	int			NS_DeleteSoundMem(                      int SoundHandle ) ;																		// �T�E���h�n���h�����폜����

extern	int			NS_PlaySoundMem(                        int SoundHandle, int PlayType, int TopPositionFlag = TRUE ) ;								// �T�E���h�n���h�����Đ�����
extern	int			NS_StopSoundMem(                                                                        int SoundHandle, int IsNextLoopEnd = FALSE ) ;	// �T�E���h�n���h���̍Đ����~����
extern	int			NS_CheckSoundMem(                                                                       int SoundHandle ) ;						// �T�E���h�n���h�����Đ������ǂ������擾����
extern	int			NS_SetPanSoundMem(                      int PanPal,                                     int SoundHandle ) ;						// �T�E���h�n���h���̃p����ݒ肷��( 100����1�f�V�x���P�� 0 �` 10000 )
extern	int			NS_ChangePanSoundMem(                   int PanPal,                                     int SoundHandle ) ;						// �T�E���h�n���h���̃p����ݒ肷��( -255 �` 255 )
extern	int			NS_GetPanSoundMem(                                                                      int SoundHandle ) ;						// �T�E���h�n���h���̃p�����擾����
extern	int			NS_SetVolumeSoundMem(                   int VolumePal,                                  int SoundHandle ) ;						// �T�E���h�n���h���̃{�����[����ݒ肷��( 100����1�f�V�x���P�� 0 �` 10000 )
extern	int			NS_ChangeVolumeSoundMem(                int VolumePal,                                  int SoundHandle ) ;						// �T�E���h�n���h���̃{�����[����ݒ肷��( 0 �` 255 )
extern	int			NS_GetVolumeSoundMem(                                                                   int SoundHandle ) ;						// �T�E���h�n���h���̃{�����[�����擾����
extern	int			NS_GetVolumeSoundMem2(                                                                  int SoundHandle ) ;						// �T�E���h�n���h���̃{�����[�����擾����( 0 �` 255 )
extern	int			NS_SetChannelVolumeSoundMem(            int Channel, int VolumePal,                     int SoundHandle ) ;						// �T�E���h�n���h���̎w��̃`�����l���̃{�����[����ݒ肷��( 100����1�f�V�x���P�� 0 �` 10000 )
extern	int			NS_ChangeChannelVolumeSoundMem(         int Channel, int VolumePal,                     int SoundHandle ) ;						// �T�E���h�n���h���̎w��̃`�����l���̃{�����[����ݒ肷��( 0 �` 255 )
extern	int			NS_GetChannelVolumeSoundMem(            int Channel,                                    int SoundHandle ) ;						// �T�E���h�n���h���̎w��̃`�����l���̃{�����[�����擾����
extern	int			NS_GetChannelVolumeSoundMem2(           int Channel,                                    int SoundHandle ) ;						// �T�E���h�n���h���̎w��̃`�����l���̃{�����[�����擾����( 0 �` 255 )
extern	int			NS_SetFrequencySoundMem(                int FrequencyPal,                               int SoundHandle ) ;						// �T�E���h�n���h���̍Đ����g����ݒ肷��
extern	int			NS_GetFrequencySoundMem(                                                                int SoundHandle ) ;						// �T�E���h�n���h���̍Đ����g�����擾����
extern	int			NS_ResetFrequencySoundMem(                                                              int SoundHandle ) ;						// �T�E���h�n���h���̍Đ����g����ǂݍ��ݒ���̏�Ԃɖ߂�

extern	int			NS_SetNextPlayPanSoundMem(              int PanPal,                                     int SoundHandle ) ;						// �T�E���h�n���h���̎��̍Đ��ɂ̂ݎg�p����p����ݒ肷��( 100����1�f�V�x���P�� 0 �` 10000 )
extern	int			NS_ChangeNextPlayPanSoundMem(           int PanPal,                                     int SoundHandle ) ;						// �T�E���h�n���h���̎��̍Đ��ɂ̂ݎg�p����p����ݒ肷��( -255 �` 255 )
extern	int			NS_SetNextPlayVolumeSoundMem(           int VolumePal,                                  int SoundHandle ) ;						// �T�E���h�n���h���̎��̍Đ��ɂ̂ݎg�p����{�����[����ݒ肷��( 100����1�f�V�x���P�� 0 �` 10000 )
extern	int			NS_ChangeNextPlayVolumeSoundMem(        int VolumePal,                                  int SoundHandle ) ;						// �T�E���h�n���h���̎��̍Đ��ɂ̂ݎg�p����{�����[����ݒ肷��( 0 �` 255 )
extern	int			NS_SetNextPlayChannelVolumeSoundMem(    int Channel, int VolumePal,                     int SoundHandle ) ;						// �T�E���h�n���h���̎��̍Đ��ɂ̂ݎg�p����`�����l���̃{�����[����ݒ肷��( 100����1�f�V�x���P�� 0 �` 10000 )
extern	int			NS_ChangeNextPlayChannelVolumeSoundMem( int Channel, int VolumePal,                     int SoundHandle ) ;						// �T�E���h�n���h���̎��̍Đ��ɂ̂ݎg�p����`�����l���̃{�����[����ݒ肷��( 0 �` 255 )
extern	int			NS_SetNextPlayFrequencySoundMem(        int FrequencyPal,                               int SoundHandle ) ;						// �T�E���h�n���h���̎��̍Đ��ɂ̂ݎg�p����Đ����g����ݒ肷��

extern	int			NS_SetCurrentPositionSoundMem(          LONGLONG SamplePosition,                        int SoundHandle ) ;						// �T�E���h�n���h���̍Đ��ʒu���T���v���P�ʂŐݒ肷��(�Đ����~�܂��Ă��鎞�̂ݗL��)
extern	LONGLONG	NS_GetCurrentPositionSoundMem(                                                          int SoundHandle ) ;						// �T�E���h�n���h���̍Đ��ʒu���T���v���P�ʂŎ擾����
extern	int			NS_SetSoundCurrentPosition(             LONGLONG Byte,                                  int SoundHandle ) ;						// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŐݒ肷��(�Đ����~�܂��Ă��鎞�̂ݗL��)
extern	LONGLONG	NS_GetSoundCurrentPosition(                                                             int SoundHandle ) ;						// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŎ擾����
extern	int			NS_SetSoundCurrentTime(                 LONGLONG Time,                                  int SoundHandle ) ;						// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŐݒ肷��(���k�`���̏ꍇ�͐������ݒ肳��Ȃ��ꍇ������)
extern	LONGLONG	NS_GetSoundCurrentTime(                                                                 int SoundHandle ) ;						// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŎ擾����(���k�`���̏ꍇ�͐������l���Ԃ��Ă��Ȃ��ꍇ������)
extern	LONGLONG	NS_GetSoundTotalSample(                                                                 int SoundHandle ) ;						// �T�E���h�n���h���̉��̑����Ԃ��T���v���P�ʂŎ擾����
extern	LONGLONG	NS_GetSoundTotalTime(                                                                   int SoundHandle ) ;						// �T�E���h�n���h���̉��̑����Ԃ��~���b�P�ʂŎ擾����

extern	int			NS_SetLoopPosSoundMem(                  LONGLONG LoopTime,                              int SoundHandle ) ;						// SetLoopTimePosSoundMem �̕ʖ��֐�
extern	int			NS_SetLoopTimePosSoundMem(              LONGLONG LoopTime,                              int SoundHandle ) ;						// �T�E���h�n���h���Ƀ��[�v�ʒu��ݒ肷��(�~���b�P��)
extern	int			NS_SetLoopSamplePosSoundMem(            LONGLONG LoopSamplePosition,                    int SoundHandle ) ;						// �T�E���h�n���h���Ƀ��[�v�ʒu��ݒ肷��(�T���v���P��)

extern	int			NS_SetLoopStartTimePosSoundMem(         LONGLONG LoopStartTime,                         int SoundHandle ) ;						// �T�E���h�n���h���Ƀ��[�v�J�n�ʒu��ݒ肷��(�~���b�P��)
extern	int			NS_SetLoopStartSamplePosSoundMem(       LONGLONG LoopStartSamplePosition,               int SoundHandle ) ;						// �T�E���h�n���h���Ƀ��[�v�J�n�ʒu��ݒ肷��(�T���v���P��)

extern	int			NS_SetLoopAreaTimePosSoundMem(          LONGLONG  LoopStartTime, LONGLONG  LoopEndTime,                     int SoundHandle ) ;	// �T�E���h�n���h���Ƀ��[�v�͈͂�ݒ肷��(�~���b�P��)
extern	int			NS_GetLoopAreaTimePosSoundMem(          LONGLONG *LoopStartTime, LONGLONG *LoopEndTime,                     int SoundHandle ) ;	// �T�E���h�n���h���Ƀ��[�v�͈͂��擾����(�~���b�P��)
extern	int			NS_SetLoopAreaSamplePosSoundMem(        LONGLONG  LoopStartSamplePosition, LONGLONG  LoopEndSamplePosition, int SoundHandle ) ;	// �T�E���h�n���h���Ƀ��[�v�͈͂�ݒ肷��(�T���v���P��)
extern	int			NS_GetLoopAreaSamplePosSoundMem(        LONGLONG *LoopStartSamplePosition, LONGLONG *LoopEndSamplePosition, int SoundHandle ) ;	// �T�E���h�n���h���Ƀ��[�v�͈͂��擾����(�T���v���P��)

extern	int			NS_SetPlayFinishDeleteSoundMem(         int DeleteFlag,                                 int SoundHandle ) ;						// �T�E���h�n���h���̍Đ����I�������玩���I�Ƀn���h�����폜���邩�ǂ�����ݒ肷��

extern	int			NS_Set3DReverbParamSoundMem(            const SOUND3D_REVERB_PARAM *Param,                    int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̃��o�[�u�p�����[�^��ݒ肷��
extern	int			NS_Set3DPresetReverbParamSoundMem(      int PresetNo /* DX_REVERB_PRESET_DEFAULT �� */ , int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̃��o�[�u�p�����[�^���v���Z�b�g���g�p���Đݒ肷��
extern	int			NS_Set3DReverbParamSoundMemAll(         const SOUND3D_REVERB_PARAM *Param, int PlaySoundOnly = FALSE ) ;							// �S�Ă̂R�c�T�E���h�̃T�E���h�n���h���Ƀ��o�[�u�p�����[�^��ݒ肷��( PlaySoundOnly TRUE:�Đ����̃T�E���h�ɂ̂ݐݒ肷��  FALSE:�Đ����Ă��Ȃ��T�E���h�ɂ��ݒ肷�� )
extern	int			NS_Set3DPresetReverbParamSoundMemAll(   int PresetNo /* DX_REVERB_PRESET_DEFAULT �� */ , int PlaySoundOnly = FALSE  ) ;			// �S�Ă̂R�c�T�E���h�̃T�E���h�n���h���Ƀ��o�[�u�p�����[�^���v���Z�b�g���g�p���Đݒ肷��( PlaySoundOnly TRUE:�Đ����̃T�E���h�ɂ̂ݐݒ肷��  FALSE:�Đ����Ă��Ȃ��T�E���h�ɂ��ݒ肷�� )
extern	int			NS_Get3DReverbParamSoundMem(            SOUND3D_REVERB_PARAM *ParamBuffer,              int SoundHandle ) ;						// �T�E���h�n���h���ɐݒ肳��Ă���R�c�T�E���h�p�̃��o�[�u�p�����[�^���擾����
extern	int			NS_Get3DPresetReverbParamSoundMem(      SOUND3D_REVERB_PARAM *ParamBuffer, int PresetNo /* DX_REVERB_PRESET_DEFAULT �� */ ) ;		// �v���Z�b�g�̂R�c�T�E���h�p�̃��o�[�u�p�����[�^���擾����

extern	int			NS_Set3DPositionSoundMem(               VECTOR Position,                                int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̍Đ��ʒu��ݒ肷��
extern	int			NS_Set3DRadiusSoundMem(                 float Radius,                                   int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̉����������鋗����ݒ肷��
extern	int			NS_Set3DVelocitySoundMem(               VECTOR Velocity,                                int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̈ړ����x��ݒ肷��

extern	int			NS_SetNextPlay3DPositionSoundMem(       VECTOR Position,                                int SoundHandle ) ;						// �T�E���h�n���h���̎��̍Đ��݂̂Ɏg�p����R�c�T�E���h�p�̍Đ��ʒu��ݒ肷��
extern	int			NS_SetNextPlay3DRadiusSoundMem(         float Radius,                                   int SoundHandle ) ;						// �T�E���h�n���h���̎��̍Đ��݂̂Ɏg�p����R�c�T�E���h�p�̉����������鋗����ݒ肷��
extern	int			NS_SetNextPlay3DVelocitySoundMem(       VECTOR Velocity,                                int SoundHandle ) ;						// �T�E���h�n���h���̎��̍Đ��݂̂Ɏg�p����R�c�T�E���h�p�̈ړ����x��ݒ肷��


// ����֐�
extern	int			NS_GetMP3TagInfo(           const TCHAR *FileName,                        TCHAR *TitleBuffer, size_t TitleBufferBytes, TCHAR *ArtistBuffer, size_t ArtistBufferBytes, TCHAR *AlbumBuffer, size_t AlbumBufferBytes, TCHAR *YearBuffer, size_t YearBufferBytes, TCHAR *CommentBuffer, size_t CommentBufferBytes, TCHAR *TrackBuffer, size_t TrackBufferBytes, TCHAR *GenreBuffer, size_t GenreBufferBytes, int *PictureGrHandle ) ;		// MP3�t�@�C���̃^�O�����擾����
extern	int			NS_GetMP3TagInfoWithStrLen( const TCHAR *FileName, size_t FileNameLength, TCHAR *TitleBuffer, size_t TitleBufferBytes, TCHAR *ArtistBuffer, size_t ArtistBufferBytes, TCHAR *AlbumBuffer, size_t AlbumBufferBytes, TCHAR *YearBuffer, size_t YearBufferBytes, TCHAR *CommentBuffer, size_t CommentBufferBytes, TCHAR *TrackBuffer, size_t TrackBufferBytes, TCHAR *GenreBuffer, size_t GenreBufferBytes, int *PictureGrHandle ) ;		// MP3�t�@�C���̃^�O�����擾����
#ifndef DX_NON_OGGVORBIS
extern	int			NS_GetOggCommentNum(           const TCHAR *FileName                        ) ;																			// Ogg�t�@�C���̃R�����g���̐����擾����
extern	int			NS_GetOggCommentNumWithStrLen( const TCHAR *FileName, size_t FileNameLength ) ;																			// Ogg�t�@�C���̃R�����g���̐����擾����
extern	int			NS_GetOggComment(              const TCHAR *FileName,                        int CommentIndex, TCHAR *CommentNameBuffer, size_t CommentNameBufferBytes, TCHAR *CommentBuffer, size_t CommentBufferBytes ) ;		// Ogg�t�@�C���̃R�����g�����擾����
extern	int			NS_GetOggCommentWithStrLen(    const TCHAR *FileName, size_t FileNameLength, int CommentIndex, TCHAR *CommentNameBuffer, size_t CommentNameBufferBytes, TCHAR *CommentBuffer, size_t CommentBufferBytes ) ;		// Ogg�t�@�C���̃R�����g�����擾����
#endif // DX_NON_OGGVORBIS


// �ݒ�֌W�֐�
extern	int			NS_SetCreateSoundDataType(              int SoundDataType ) ;																		// �쐬����T�E���h�n���h���̍Đ��^�C�v��ݒ肷��( DX_SOUNDDATATYPE_MEMNOPRESS �� )
extern	int			NS_GetCreateSoundDataType(              void ) ;																					// �쐬����T�E���h�n���h���̍Đ��^�C�v���擾����( DX_SOUNDDATATYPE_MEMNOPRESS �� )
extern	int			NS_SetCreateSoundPitchRate(             float Cents ) ;																				// �쐬����T�E���h�n���h���̃s�b�`���[�g��ݒ肷��( �P�ʂ̓Z���g( 100.0f�Ŕ����A1200.0f�łP�I�N�^�[�u )�A�v���X�̒l�ŉ����������A�}�C�i�X�̒l�ŉ������Ⴍ�Ȃ�܂� )
extern	float		NS_GetCreateSoundPitchRate(             void ) ;																					// �쐬����T�E���h�n���h���̃s�b�`���[�g���擾����( �P�ʂ̓Z���g( 100.0f�Ŕ����A1200.0f�łP�I�N�^�[�u )�A�v���X�̒l�ŉ����������A�}�C�i�X�̒l�ŉ������Ⴍ�Ȃ�܂� )
extern	int			NS_SetCreateSoundTimeStretchRate(       float Rate ) ;																				// �쐬����T�E���h�n���h���̃^�C���X�g���b�`( ������ς����ɉ��̒�����ύX���� )���[�g��ݒ肷��( �P�ʂ͔{���A2.0f �ŉ��̒������Q�{�ɁA0.5f �ŉ��̒����������ɂȂ�܂� )
extern	float		NS_GetCreateSoundTimeStretchRate(       void ) ;																					// �쐬����T�E���h�n���h���̃^�C���X�g���b�`( ������ς����ɉ��̒�����ύX���� )���[�g���擾����( �P�ʂ͔{���A2.0f �ŉ��̒������Q�{�ɁA0.5f �ŉ��̒����������ɂȂ�܂� )
extern	int			NS_SetCreateSoundLoopAreaTimePos(       LONGLONG  LoopStartTime,           LONGLONG  LoopEndTime ) ;								// �쐬����T�E���h�n���h���̃��[�v�͈͂�ݒ肷��( �~���b�P�� )
extern	int			NS_GetCreateSoundLoopAreaTimePos(       LONGLONG *LoopStartTime,           LONGLONG *LoopEndTime ) ;								// �쐬����T�E���h�n���h���̃��[�v�͈͂��擾����( �~���b�P�� )
extern	int			NS_SetCreateSoundLoopAreaSamplePos(     LONGLONG  LoopStartSamplePosition, LONGLONG  LoopEndSamplePosition ) ;						// �쐬����T�E���h�n���h���̃��[�v�͈͂�ݒ肷��( �T���v���P�� )
extern	int			NS_GetCreateSoundLoopAreaSamplePos(     LONGLONG *LoopStartSamplePosition, LONGLONG *LoopEndSamplePosition ) ;						// �쐬����T�E���h�n���h���̃��[�v�͈͂��擾����( �T���v���P�� )
extern	int			NS_SetCreateSoundIgnoreLoopAreaInfo(    int IgnoreFlag ) ;																			// LoadSoundMem �Ȃǂœǂݍ��ރT�E���h�f�[�^�Ƀ��[�v�͈͏�񂪂����Ă��������邩�ǂ�����ݒ肷��( TRUE:��������  FALSE:�������Ȃ�( �f�t�H���g ) )
extern	int			NS_GetCreateSoundIgnoreLoopAreaInfo(    void ) ;																					// LoadSoundMem �Ȃǂœǂݍ��ރT�E���h�f�[�^�Ƀ��[�v�͈͏�񂪂����Ă��������邩�ǂ������擾����( TRUE:��������  FALSE:�������Ȃ�( �f�t�H���g ) )
extern	int			NS_SetDisableReadSoundFunctionMask(     int Mask ) ;																				// �g�p���Ȃ��T�E���h�f�[�^�ǂݍ��ݏ����̃}�X�N��ݒ肷��( DX_READSOUNDFUNCTION_PCM �� )
extern	int			NS_GetDisableReadSoundFunctionMask(     void ) ;																					// �g�p���Ȃ��T�E���h�f�[�^�ǂݍ��ݏ����̃}�X�N���擾����( DX_READSOUNDFUNCTION_PCM �� )
extern	int			NS_SetEnableSoundCaptureFlag(           int Flag ) ;																				// �T�E���h�L���v�`����O��Ƃ�����������邩�ǂ�����ݒ肷��
extern	int			NS_SetUseSoftwareMixingSoundFlag(       int Flag ) ;																				// �T�E���h�̏������\�t�g�E�G�A�ōs�����ǂ�����ݒ肷��( TRUE:�\�t�g�E�G�A  FALSE:�n�[�h�E�G�A( �f�t�H���g ) )
extern	int			NS_SetEnableXAudioFlag(                 int Flag ) ;																				// �T�E���h�̍Đ���XAudio���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����  FALSE:�g�p���Ȃ�( �f�t�H���g ) )
extern	int			NS_SetEnableWASAPIFlag(                 int Flag, int IsExclusive = TRUE , int DevicePeriod = -1 , int SamplePerSec = 44100 ) ;		// �T�E���h�̍Đ���WASAPI���g�p���邩�ǂ�����ݒ肷��( Flag  TRUE:�g�p����  FALSE:�g�p���Ȃ�( �f�t�H���g ), IsExclusive  TRUE:�r�����[�h���g�p����  FALSE:�r�����[�h���g�p���Ȃ�, DevicePeriod �Đ��x�����ԁA100�i�m�b�P��( 100000 �� 10�~���b )�A-1�Ńf�t�H���g�l, SamplePerSec �T���v�����O���[�g )
#ifndef DX_NON_ASIO
extern	int			NS_SetEnableASIOFlag(                   int Flag, int BufferSize = -1 , int SamplePerSec = 44100 ) ;																					// �T�E���h�̍Đ���ASIO���g�p���邩�ǂ�����ݒ肷��( Flag  TRUE:�g�p����  FALSE:�g�p���Ȃ�( �f�t�H���g ), BufferSize �Đ��o�b�t�@�̃T�C�Y�A�������قǒx�������Ȃ��Ȃ�܂����A�������Ԃɍ��킸�Ƀu�c�u�c�m�C�Y����������\���������Ȃ�܂�( -1 �Ńf�t�H���g�l ), SamplePerSec �T���v�����O���[�g )
extern	int			NS_SetUseASIODriverIndex(               int Index ) ;																																	// �T�E���h�̍Đ��Ɏg�p����ASIO�h���C�o�[�̔ԍ���ݒ肷��( �f�t�H���g�ł� 0 )
#endif // DX_NON_ASIO
extern	int			NS_SetEnableMMEwaveOutFlag(             int Flag, int BufferSamples DEFAULTPARAM( = -1 ) , int SamplePerSec DEFAULTPARAM( = 44100 ) ) ;													// �T�E���h�̍Đ��Ƀ}���`���f�B�AAPI�� waveOut ���g�p���邩�ǂ�����ݒ肷��( Flag  TRUE:�g�p����  FALSE:�g�p���Ȃ�( �f�t�H���g ), BufferSize �Đ��o�b�t�@�̃T�C�Y�A�������قǒx�������Ȃ��Ȃ�܂����A�������Ԃɍ��킸�Ƀu�c�u�c�m�C�Y����������\���������Ȃ�܂�( -1 �Ńf�t�H���g�l ), SamplePerSec �T���v�����O���[�g )

extern	int			NS_SetUseOldVolumeCalcFlag(             int Flag ) ;																				// ChangeVolumeSoundMem, ChangeNextPlayVolumeSoundMem, ChangeMovieVolumeToGraph �̉��ʌv�Z���� Ver3.10c�ȑO�̂��̂��g�p���邩�ǂ�����ݒ肷��( TRUE:Ver3.10c�ȑO�̌v�Z�����g�p  FALSE:3.10d�ȍ~�̌v�Z�����g�p( �f�t�H���g ) )
extern	int			NS_SetSoundCurrentTimeType(             int Type /* DX_SOUNDCURRENTTIME_TYPE_LOW_LEVEL �Ȃ� */ ) ;									// GetSoundCurrentTime �Ȃǂ��g�p�����ꍇ�Ɏ擾�ł���Đ����Ԃ̃^�C�v��ݒ肷��
extern	int			NS_GetSoundCurrentTimeType(             void ) ;																					// GetSoundCurrentTime �Ȃǂ��g�p�����ꍇ�Ɏ擾�ł���Đ����Ԃ̃^�C�v���擾����

extern	int			NS_SetCreate3DSoundFlag(                     int Flag ) ;																			// ���ɍ쐬����T�E���h�n���h�����R�c�T�E���h�p�ɂ��邩�ǂ�����ݒ肷��( TRUE:�R�c�T�E���h�p�ɂ���  FALSE:�R�c�T�E���h�p�ɂ��Ȃ�( �f�t�H���g ) )
extern	int			NS_Set3DSoundOneMetre(                       float Distance ) ;																		// �R�c��Ԃ̂P���[�g���ɑ������鋗����ݒ肷��ADxLib_Init ���Ăяo���O�ł̂݌Ăяo���\( �f�t�H���g:1.0f )
extern	int			NS_Set3DSoundListenerPosAndFrontPos_UpVecY(  VECTOR Position, VECTOR FrontPosition ) ;												// �R�c�T�E���h�̃��X�i�[�̈ʒu�ƃ��X�i�[�̑O���ʒu��ݒ肷��( ���X�i�[�̏�����͂x���Œ� )
extern	int			NS_Set3DSoundListenerPosAndFrontPosAndUpVec( VECTOR Position, VECTOR FrontPosition, VECTOR UpVector ) ;								// �R�c�T�E���h�̃��X�i�[�̈ʒu�ƃ��X�i�[�̑O���ʒu�ƃ��X�i�[�̏������ݒ肷��
extern	int			NS_Set3DSoundListenerVelocity(               VECTOR Velocity ) ;																	// �R�c�T�E���h�̃��X�i�[�̈ړ����x��ݒ肷��
extern	int			NS_Set3DSoundListenerConeAngle(              float InnerAngle, float OuterAngle ) ;													// �R�c�T�E���h�̃��X�i�[�̉��p�x�͈͂�ݒ肷��
extern	int			NS_Set3DSoundListenerConeVolume(             float InnerAngleVolume, float OuterAngleVolume ) ;										// �R�c�T�E���h�̃��X�i�[�̉��p�x�͈͂̉��ʔ{����ݒ肷��

// ���擾�n�֐�
extern	const void*	NS_GetDSoundObj(                        void ) ;	/* �߂�l�� IDirectSound * �ɃL���X�g���ĉ����� */								// �c�w���C�u�������g�p���Ă��� DirectSound �I�u�W�F�N�g���擾����

#ifndef DX_NON_BEEP
// BEEP���Đ��p����
extern	int			NS_SetBeepFrequency(					int Freq ) ;																				// �r�[�v�����g���ݒ�֐�
extern	int			NS_PlayBeep(							void ) ;																					// �r�[�v�����Đ�����
extern	int			NS_StopBeep(							void ) ;																					// �r�[�v�����~�߂�
#endif // DX_NON_BEEP

// ���b�p�[�֐�
extern	int			NS_PlaySoundFile(						const TCHAR *FileName, int PlayType ) ;														// �T�E���h�t�@�C�����Đ�����
extern	int			NS_PlaySoundFileWithStrLen(			const TCHAR *FileName, size_t FileNameLength, int PlayType ) ;														// �T�E���h�t�@�C�����Đ�����
#ifndef DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_PlaySound(							const TCHAR *FileName,                        int PlayType ) ;														// PlaySoundFile �̋�����
extern	int			NS_PlaySoundWithStrLen(				const TCHAR *FileName, size_t FileNameLength, int PlayType ) ;														// PlaySoundFile �̋�����
#endif // DX_COMPILE_TYPE_C_LANGUAGE
extern	int			NS_PlaySoundDX(							const TCHAR *FileName,                        int PlayType ) ;														// PlaySoundFile �̋�����
extern	int			NS_PlaySoundDXWithStrLen(				const TCHAR *FileName, size_t FileNameLength, int PlayType ) ;														// PlaySoundFile �̋�����
extern	int			NS_CheckSoundFile(						void ) ;																					// �T�E���h�t�@�C���̍Đ������ǂ������擾����
extern	int			NS_CheckSound(							void ) ;																					// CheckSoundFile �̋�����
extern	int			NS_StopSoundFile(						void ) ;																					// �T�E���h�t�@�C���̍Đ����~����
extern	int			NS_StopSound(							void ) ;																					// StopSoundFile �̋�����
extern	int			NS_SetVolumeSoundFile(					int VolumePal ) ;																			// �T�E���h�t�@�C���̉��ʂ�ݒ肷��
extern	int			NS_SetVolumeSound(						int VolumePal ) ;																			// SetVolumeSound �̋�����

// �\�t�g�E�G�A����T�E���h�n�֐�
extern	int			NS_InitSoftSound(						void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h�������ׂč폜����
extern	int			NS_LoadSoftSound(						const TCHAR *FileName                        ) ;											// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h�����T�E���h�t�@�C������쐬����
extern	int			NS_LoadSoftSoundWithStrLen(			const TCHAR *FileName, size_t FileNameLength ) ;											// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h�����T�E���h�t�@�C������쐬����
extern	int			NS_LoadSoftSoundFromMemImage(			const void *FileImage, size_t FileImageSize ) ;												// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h������������ɓW�J���ꂽ�T�E���h�t�@�C���C���[�W����쐬����
extern	int			NS_MakeSoftSound(						int UseFormat_SoftSoundHandle, LONGLONG SampleNum ) ;										// �\�t�g�E�G�A�ň�����̔g�`�f�[�^�n���h�����쐬����( �t�H�[�}�b�g�͈����̃\�t�g�E�G�A�T�E���h�n���h���Ɠ������̂ɂ��� )
extern	int			NS_MakeSoftSound2Ch16Bit44KHz(			LONGLONG SampleNum ) ;																		// �\�t�g�E�G�A�ň�����̔g�`�f�[�^�n���h�����쐬����( �`�����l����:2 �ʎq���r�b�g��:16bit �T���v�����O���g��:44.1KHz )
extern	int			NS_MakeSoftSound2Ch16Bit22KHz(			LONGLONG SampleNum ) ;																		// �\�t�g�E�G�A�ň�����̔g�`�f�[�^�n���h�����쐬����( �`�����l����:2 �ʎq���r�b�g��:16bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSound2Ch8Bit44KHz(			LONGLONG SampleNum ) ;																		// �\�t�g�E�G�A�ň�����̔g�`�f�[�^�n���h�����쐬����( �`�����l����:2 �ʎq���r�b�g��: 8bit �T���v�����O���g��:44.1KHz )
extern	int			NS_MakeSoftSound2Ch8Bit22KHz(			LONGLONG SampleNum ) ;																		// �\�t�g�E�G�A�ň�����̔g�`�f�[�^�n���h�����쐬����( �`�����l����:2 �ʎq���r�b�g��: 8bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSound1Ch16Bit44KHz(			LONGLONG SampleNum ) ;																		// �\�t�g�E�G�A�ň�����̔g�`�f�[�^�n���h�����쐬����( �`�����l����:1 �ʎq���r�b�g��:16bit �T���v�����O���g��:44.1KHz )
extern	int			NS_MakeSoftSound1Ch16Bit22KHz(			LONGLONG SampleNum ) ;																		// �\�t�g�E�G�A�ň�����̔g�`�f�[�^�n���h�����쐬����( �`�����l����:1 �ʎq���r�b�g��:16bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSound1Ch8Bit44KHz(			LONGLONG SampleNum ) ;																		// �\�t�g�E�G�A�ň�����̔g�`�f�[�^�n���h�����쐬����( �`�����l����:1 �ʎq���r�b�g��: 8bit �T���v�����O���g��:44.1KHz )
extern	int			NS_MakeSoftSound1Ch8Bit22KHz(			LONGLONG SampleNum ) ;																		// �\�t�g�E�G�A�ň�����̔g�`�f�[�^�n���h�����쐬����( �`�����l����:1 �ʎq���r�b�g��: 8bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSoundCustom(				int ChannelNum, int BitsPerSample, int SamplesPerSec, LONGLONG SampleNum, int IsFloatType = 0 ) ;	// �\�t�g�E�G�A�ň�����̔g�`�f�[�^�n���h�����쐬����
extern	int			NS_DeleteSoftSound(					int SoftSoundHandle ) ;																		// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h�����폜����
#ifndef DX_NON_SAVEFUNCTION
extern	int			NS_SaveSoftSound(						int SoftSoundHandle, const TCHAR *FileName                        ) ;						// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h����WAVE�t�@�C��(PCM)�`���ŕۑ�����
extern	int			NS_SaveSoftSoundWithStrLen(			int SoftSoundHandle, const TCHAR *FileName, size_t FileNameLength ) ;						// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h����WAVE�t�@�C��(PCM)�`���ŕۑ�����
#endif // DX_NON_SAVEFUNCTION
extern	LONGLONG	NS_GetSoftSoundSampleNum(				int SoftSoundHandle ) ;																		// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̃T���v�������擾����
extern	int			NS_GetSoftSoundFormat(					int SoftSoundHandle, int *Channels, int *BitsPerSample, int *SamplesPerSec, int *IsFloatType = NULL ) ;				// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̃t�H�[�}�b�g���擾����
extern	int			NS_ReadSoftSoundData(					int SoftSoundHandle, LONGLONG SamplePosition, int   *Channel1, int   *Channel2 ) ;			// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̃T���v����ǂݎ��
extern	int			NS_ReadSoftSoundDataF(					int SoftSoundHandle, LONGLONG SamplePosition, float *Channel1, float *Channel2 ) ;			// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̃T���v����ǂݎ��( float�^�� )
extern	int			NS_WriteSoftSoundData(					int SoftSoundHandle, LONGLONG SamplePosition, int    Channel1, int    Channel2 ) ;			// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̃T���v������������
extern	int			NS_WriteSoftSoundDataF(				int SoftSoundHandle, LONGLONG SamplePosition, float  Channel1, float  Channel2 ) ;			// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̃T���v������������( float�^�� )
extern	int			NS_WriteTimeStretchSoftSoundData(		int SrcSoftSoundHandle, int DestSoftSoundHandle ) ;											// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̔g�`�f�[�^��������ς����Ƀf�[�^�̒�����ύX����
extern	int			NS_WritePitchShiftSoftSoundData(		int SrcSoftSoundHandle, int DestSoftSoundHandle ) ;											// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̔g�`�f�[�^�̒�����ύX����
extern	void*		NS_GetSoftSoundDataImage(				int SoftSoundHandle ) ;																		// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̔g�`�C���[�W���i�[����Ă��郁�����A�h���X���擾����
extern	int			NS_GetFFTVibrationSoftSound(			int SoftSoundHandle, int Channel, LONGLONG SamplePosition, int SampleNum, float *Buffer_Array, int BufferLength ) ;								// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̎w��͈̔͂������t�[���G�ϊ����s���A�e���g����̐U�����擾����( SampleNum �� 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 �̉��ꂩ�ł���K�v������܂��AChannel �� -1 �ɂ���Ɠ�̃`�����l���������������ʂɂȂ�܂� )
extern	int			NS_GetFFTVibrationSoftSoundBase(		int SoftSoundHandle, int Channel, LONGLONG SamplePosition, int SampleNum, float *RealBuffer_Array, float *ImagBuffer_Array, int BufferLength ) ;	// �\�t�g�E�G�A�ň����g�`�f�[�^�n���h���̎w��͈̔͂������t�[���G�ϊ����s���A�e���g����̐U�����擾����A���ʂ̎����Ƌ�����ʁX�Ɏ擾���邱�Ƃ��ł���o�[�W����( SampleNum �� 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 �̉��ꂩ�ł���K�v������܂��AChannel �� -1 �ɂ���Ɠ�̃`�����l���������������ʂɂȂ�܂� )

extern	int			NS_InitSoftSoundPlayer(				void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�������ׂĉ������
extern	int			NS_MakeSoftSoundPlayer(				int UseFormat_SoftSoundHandle ) ;															// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����쐬����( �t�H�[�}�b�g�͈����̃\�t�g�E�G�A�T�E���h�n���h���Ɠ������̂ɂ��� )
extern	int			NS_MakeSoftSoundPlayer2Ch16Bit44KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����쐬����( �`�����l����:2 �ʎq���r�b�g��:16bit �T���v�����O���g��:44.1KHz )
extern	int			NS_MakeSoftSoundPlayer2Ch16Bit22KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����쐬����( �`�����l����:2 �ʎq���r�b�g��:16bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSoundPlayer2Ch8Bit44KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����쐬����( �`�����l����:2 �ʎq���r�b�g��: 8bit �T���v�����O���g��:44.1KHz )
extern	int			NS_MakeSoftSoundPlayer2Ch8Bit22KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����쐬����( �`�����l����:2 �ʎq���r�b�g��: 8bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSoundPlayer1Ch16Bit44KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����쐬����( �`�����l����:1 �ʎq���r�b�g��:16bit �T���v�����O���g��:44.1KHz )
extern	int			NS_MakeSoftSoundPlayer1Ch16Bit22KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����쐬����( �`�����l����:1 �ʎq���r�b�g��:16bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSoundPlayer1Ch8Bit44KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����쐬����( �`�����l����:1 �ʎq���r�b�g��: 8bit �T���v�����O���g��:44.1KHz )
extern	int			NS_MakeSoftSoundPlayer1Ch8Bit22KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����쐬����( �`�����l����:1 �ʎq���r�b�g��: 8bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSoundPlayerCustom(			int ChannelNum, int BitsPerSample, int SamplesPerSec ) ;									// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����쐬����
extern	int			NS_DeleteSoftSoundPlayer(				int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h�����폜����
extern	int			NS_AddDataSoftSoundPlayer(				int SSoundPlayerHandle, int SoftSoundHandle, LONGLONG AddSamplePosition, int AddSampleNum ) ;	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h���ɔg�`�f�[�^��ǉ�����( �t�H�[�}�b�g�������ł͂Ȃ��ꍇ�̓G���[ )
extern	int			NS_AddDirectDataSoftSoundPlayer(		int SSoundPlayerHandle, const void *SoundData, int AddSampleNum ) ;							// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h���Ƀv���C���[���Ή������t�H�[�}�b�g�̐��g�`�f�[�^��ǉ�����
extern	int			NS_AddOneDataSoftSoundPlayer(			int SSoundPlayerHandle, int Channel1, int Channel2 ) ;										// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h���ɔg�`�f�[�^����ǉ�����
extern	int			NS_GetSoftSoundPlayerFormat(			int SSoundPlayerHandle, int *Channels, int *BitsPerSample, int *SamplesPerSec ) ;			// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h���������f�[�^�t�H�[�}�b�g���擾����
extern	int			NS_StartSoftSoundPlayer(				int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h���̍Đ��������J�n����
extern	int			NS_CheckStartSoftSoundPlayer(			int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h���̍Đ��������J�n����Ă��邩�擾����( TRUE:�J�n���Ă���  FALSE:��~���Ă��� )
extern	int			NS_StopSoftSoundPlayer(				int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h���̍Đ��������~����
extern	int			NS_ResetSoftSoundPlayer(				int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h���̏�Ԃ�������Ԃɖ߂�( �ǉ����ꂽ�g�`�f�[�^�͍폜����A�Đ���Ԃ������ꍇ�͒�~���� )
extern	int			NS_GetStockDataLengthSoftSoundPlayer(	int SSoundPlayerHandle, int *SoundBufferStockSamples = NULL ) ;								// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h���ɒǉ������g�`�f�[�^�ł܂��Đ��p�T�E���h�o�b�t�@�ɓ]������Ă��Ȃ��g�`�f�[�^�̃T���v�������擾����
extern	int			NS_CheckSoftSoundPlayerNoneData(		int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�n���h���ɍĐ��p�T�E���h�o�b�t�@�ɓ]�����Ă��Ȃ��g�`�f�[�^�������A�Đ��p�T�E���h�o�b�t�@�ɂ������f�[�^�ȊO�������ǂ������擾����( TRUE:�����f�[�^�ȊO����  FALSE:�L���f�[�^������ )




// �l�h�c�h����֐�
extern	int			NS_DeleteMusicMem(						int MusicHandle ) ;																			// �l�h�c�h�n���h�����폜����
extern	int			NS_LoadMusicMem(						const TCHAR *FileName ) ;																	// �l�h�c�h�t�@�C����ǂݍ���
extern	int			NS_LoadMusicMemWithStrLen(				const TCHAR *FileName, size_t FileNameLength ) ;											// �l�h�c�h�t�@�C����ǂݍ��݂l�h�c�h�n���h�����쐬����
extern	int			NS_LoadMusicMemByMemImage(				const void *FileImage, size_t FileImageSize ) ;														// ��������ɓW�J���ꂽ�l�h�c�h�t�@�C����ǂݍ���
extern	int			NS_LoadMusicMemByResource(				const TCHAR *ResourceName, const TCHAR *ResourceType ) ;									// ���\�[�X��̂l�h�c�h�t�@�C����ǂݍ���
extern	int			NS_LoadMusicMemByResourceWithStrLen(	const TCHAR *ResourceName, size_t ResourceNameLength, const TCHAR *ResourceType, size_t ResourceTypeLength ) ;									// ���\�[�X��̂l�h�c�h�t�@�C������l�h�c�h�n���h�����쐬����
extern	int			NS_PlayMusicMem(						int MusicHandle, int PlayType ) ;															// �ǂݍ��񂾂l�h�c�h�f�[�^�̉��t���J�n����
extern	int			NS_StopMusicMem(						int MusicHandle ) ;																			// �l�h�c�h�f�[�^�̉��t���~����
extern	int			NS_CheckMusicMem(						int MusicHandle ) ;																			// �l�h�c�h�f�[�^�����t�����ǂ������擾����( TRUE:���t��  FALSE:��~�� )
extern	int			NS_SetVolumeMusicMem(					int Volume, int MusicHandle ) ;																// �l�h�c�h�f�[�^�̍Đ����ʂ��Z�b�g����
extern	int			NS_GetMusicMemPosition(				int MusicHandle ) ;																			// �l�h�c�h�f�[�^�̌��݂̍Đ��ʒu���擾����
extern	int			NS_InitMusicMem(						void ) ;																					// �l�h�c�h�f�[�^�n���h�������ׂč폜����
extern	int			NS_ProcessMusicMem(					void ) ;																					// �l�h�c�h�f�[�^�̎����I����

extern	int			NS_PlayMusic(							const TCHAR *FileName, int PlayType ) ;														// �l�h�c�h�t�@�C�������t����
extern	int			NS_PlayMusicWithStrLen(				const TCHAR *FileName, size_t FileNameLength, int PlayType ) ;								// �l�h�c�h�t�@�C�������t����
extern	int			NS_PlayMusicByMemImage(				const void *FileImage, size_t FileImageSize, int PlayType ) ;										// ��������ɓW�J����Ă���l�h�c�h�t�@�C�������t����
extern	int			NS_PlayMusicByResource(				const TCHAR *ResourceName, const TCHAR *ResourceType, int PlayType ) ;						// ���\�[�X����l�h�c�h�t�@�C����ǂݍ���ŉ��t����
extern	int			NS_PlayMusicByResourceWithStrLen(		const TCHAR *ResourceName, size_t ResourceNameLength, const TCHAR *ResourceType, size_t ResourceTypeLength, int PlayType ) ;	// ���\�[�X����l�h�c�h�t�@�C����ǂݍ���ŉ��t����
extern	int			NS_SetVolumeMusic(						int Volume ) ;																				// �l�h�c�h�̍Đ����ʂ��Z�b�g����
extern	int			NS_StopMusic(							void ) ;																					// �l�h�c�h�t�@�C���̉��t��~
extern	int			NS_CheckMusic(							void ) ;																					// �l�h�c�h�t�@�C�������t�����ۂ������擾����
extern	int			NS_GetMusicPosition(					void ) ;																					// �l�h�c�h�̌��݂̍Đ��ʒu���擾����

extern	int			NS_SelectMidiMode(						int Mode ) ;																				// �l�h�c�h�̍Đ��`�����Z�b�g����

#endif // DX_NON_SOUND










// DxArchive_.cpp �֐� �v���g�^�C�v�錾
extern	int			NS_SetUseDXArchiveFlag(		int Flag ) ;													// �c�w�A�[�J�C�u�t�@�C���̓ǂݍ��݋@�\���g�����ǂ�����ݒ肷��( FALSE:�g�p���Ȃ�  TRUE:�g�p���� )
extern	int			NS_SetDXArchivePriority(					int Priority = 0 ) ;																// �c�w�A�[�J�C�u�t�@�C���ƒʏ�̃t�H���_�̂ǂ�������݂����ꍇ�A�ǂ����D�悳���邩��ݒ肷��( 1:�t�H���_��D�� 0:�c�w�A�[�J�C�u�t�@�C����D��(�f�t�H���g) )
extern	int			NS_SetDXArchiveExtension(					const TCHAR *Extension = NULL ) ;													// ��������c�w�A�[�J�C�u�t�@�C���̊g���q��ύX����
extern	int			NS_SetDXArchiveExtensionWithStrLen(	const TCHAR *Extension = NULL , size_t ExtensionLength = 0 ) ;	// ��������c�w�A�[�J�C�u�t�@�C���̊g���q��ݒ肷��( Extension:�g���q�������� )
extern	int			NS_SetDXArchiveKeyString(				const TCHAR *KeyString = NULL ) ;								// �c�w�A�[�J�C�u�t�@�C���̌��������ݒ肷��( KeyString:�������� )
extern	int			NS_SetDXArchiveKeyStringWithStrLen(	const TCHAR *KeyString = NULL , size_t KeyStringLength = 0 ) ;	// �c�w�A�[�J�C�u�t�@�C���̌��������ݒ肷��( KeyString:�������� )

extern	int			NS_DXArchivePreLoad(			const TCHAR *FilePath , int ASync = FALSE ) ;					// �w��̂c�w�`�t�@�C�����ۂ��ƃ������ɓǂݍ���( �߂�l: -1=�G���[  0=���� )
extern	int			NS_DXArchivePreLoadWithStrLen(			const TCHAR *FilePath, size_t FilePathLength, int ASync = FALSE ) ;		// �w��̂c�w�`�t�@�C�����ۂ��ƃ������ɓǂݍ���( �߂�l  -1:�G���[  0:���� )
extern	int			NS_DXArchiveCheckIdle(					const TCHAR *FilePath                        ) ;						// �w��̂c�w�`�t�@�C���̎��O�ǂݍ��݂������������ǂ������擾����( �߂�l  TRUE:�������� FALSE:�܂� )
extern	int			NS_DXArchiveCheckIdleWithStrLen(		const TCHAR *FilePath, size_t FilePathLength ) ;						// �w��̂c�w�`�t�@�C���̎��O�ǂݍ��݂������������ǂ������擾����( �߂�l  TRUE:�������� FALSE:�܂� )
extern	int			NS_DXArchiveRelease(					const TCHAR *FilePath                        ) ;						// �w��̂c�w�`�t�@�C��������������������
extern	int			NS_DXArchiveReleaseWithStrLen(			const TCHAR *FilePath, size_t FilePathLength ) ;						// �w��̂c�w�`�t�@�C��������������������
extern	int			NS_DXArchiveCheckFile(					const TCHAR *FilePath,                        const TCHAR *TargetFilePath                              ) ;	// �c�w�`�t�@�C���̒��Ɏw��̃t�@�C�������݂��邩�ǂ����𒲂ׂ�ATargetFilePath �͂c�w�`�t�@�C�����J�����g�t�H���_�Ƃ����ꍇ�̃p�X( �߂�l:  -1=�G���[  0:����  1:���� )
extern	int			NS_DXArchiveCheckFileWithStrLen(		const TCHAR *FilePath, size_t FilePathLength, const TCHAR *TargetFilePath, size_t TargetFilePathLength ) ;	// �c�w�`�t�@�C���̒��Ɏw��̃t�@�C�������݂��邩�ǂ����𒲂ׂ�ATargetFilePath �͂c�w�`�t�@�C�����J�����g�t�H���_�Ƃ����ꍇ�̃p�X( �߂�l:  -1=�G���[  0:����  1:���� )
extern	int			NS_DXArchiveSetMemImage(				void *ArchiveImage, int ArchiveImageSize, const TCHAR *EmulateFilePath,                               int ArchiveImageCopyFlag = FALSE , int ArchiveImageReadOnly = TRUE ) ;	// ��������ɓW�J���ꂽ�c�w�`�t�@�C�����w��̃t�@�C���p�X�ɂ��邱�Ƃɂ���( EmulateFilePath �͌����Ă� dxa �t�@�C���̃p�X�A�Ⴆ�΂c�w�`�t�@�C���C���[�W�� Image.dxa �Ƃ����t�@�C������ c:\Temp �ɂ��邱�Ƃɂ������ꍇ�� EmulateFilePath �� "c:\\Temp\\Image.dxa" ��n���ASetDXArchiveExtension �Ŋg���q��ύX���Ă���ꍇ�� EmulateFilePath �ɓn���t�@�C���p�X�̊g���q������ɍ��킹��K�v���� )
extern	int			NS_DXArchiveSetMemImageWithStrLen(		void *ArchiveImage, int ArchiveImageSize, const TCHAR *EmulateFilePath, size_t EmulateFilePathLength, int ArchiveImageCopyFlag = FALSE , int ArchiveImageReadOnly = TRUE ) ;	// ��������ɓW�J���ꂽ�c�w�`�t�@�C�����w��̃t�@�C���p�X�ɂ��邱�Ƃɂ���( EmulateFilePath �͌����Ă� dxa �t�@�C���̃p�X�A�Ⴆ�΂c�w�`�t�@�C���C���[�W�� Image.dxa �Ƃ����t�@�C������ c:\Temp �ɂ��邱�Ƃɂ������ꍇ�� EmulateFilePath �� "c:\\Temp\\Image.dxa" ��n���ASetDXArchiveExtension �Ŋg���q��ύX���Ă���ꍇ�� EmulateFilePath �ɓn���t�@�C���p�X�̊g���q������ɍ��킹��K�v���� )
extern	int			NS_DXArchiveReleaseMemImage(	void *ArchiveImage ) ;											// DXArchiveSetMemImage �̐ݒ����������




















// DxLive2DCubism4.cpp �֐� �v���g�^�C�v�錾

#ifndef DX_NON_LIVE2D_CUBISM4

extern	int			NS_Live2D_SetCubism4CoreDLLPath( const TCHAR *CoreDLLFilePath ) ;									// Live2DCubismCore.dll �̃t�@�C���p�X��ݒ肷��
extern	int			NS_Live2D_SetCubism4CoreDLLPathWithStrLen( const TCHAR *CoreDLLFilePath, size_t CoreDLLFilePathLength ) ;	// Live2DCubismCore.dll �̃t�@�C���p�X��ݒ肷��
extern	int			NS_Live2D_SetCubism3CoreDLLPath( const TCHAR *CoreDLLFilePath ) ;									// Live2DCubismCore.dll �̃t�@�C���p�X��ݒ肷��
extern	int			NS_Live2D_SetCubism3CoreDLLPathWithStrLen( const TCHAR *CoreDLLFilePath, size_t CoreDLLFilePathLength ) ;	// Live2DCubismCore.dll �̃t�@�C���p�X��ݒ肷��

extern	int			NS_Live2D_RenderBegin( void ) ;																			// Live2D �̕`�揈�����J�n
extern	int			NS_Live2D_RenderEnd( void ) ;																				// Live2D �̕`�揈�����I��

extern	int			NS_Live2D_LoadModel(			const TCHAR *FilePath ) ;													// Live2D �̃��f���t�@�C����ǂݍ���
extern	int			NS_Live2D_LoadModelWithStrLen(	const TCHAR *FilePath, size_t FilePathLength ) ;							// Live2D �̃��f���t�@�C����ǂݍ���
extern	int			NS_Live2D_DeleteModel( int Live2DModelHandle ) ;															// Live2D �̃��f�����폜����
extern	int			NS_Live2D_InitModel(			void ) ;																	// ���ׂĂ� Live2D �̃��f�����폜����

extern	int			NS_Live2D_SetUserShader( int TargetShader /* DX_LIVE2D_SHADER_NORMAL_PIXEL �� */ , int ShaderHandle DEFAULTPARAM( = -1 ) ) ;			// Live2D �̃��f���`��Ŏg�p����V�F�[�_�[��ݒ肷��( ShaderHandle �� -1 ��n���Ɖ��� )
extern	int			NS_Live2D_DrawCallback( void ( *Callback )( int Live2DModelHandle, int TextureIndex, void *UserData ), void *UserData ) ;			// Live2D �̃��f���`��̑O�ɌĂ΂��R�[���o�b�N�֐���ݒ肷�� Callback �� NULL ��n���Ɛݒ������ )
extern	int			NS_Live2D_SetUseAutoScaling( int UseFlag ) ;																// Live2D �̃��f���`�������ۂɁA��ʃT�C�Y�ɉ������X�P�[�����O���s������ݒ肷��( UseFlag  TRUE:�X�P�[�����O���s��( �f�t�H���g )  FALSE:�X�P�[�����O���s��Ȃ� )
extern	int			NS_Live2D_SetUseAutoCentering( int UseFlag ) ;																// Live2D �̃��f������ʂ̒��S�ɕ`�悷�邩��ݒ肷��( UseFlag   TRUE:��ʂ̒��S�ɕ`�悷��( �f�t�H���g )   FALSE:��ʂ̒��S�ɕ`�悵�Ȃ� )
extern	int			NS_Live2D_SetUseReverseYAxis( int UseFlag ) ;																// Live2D_Model_SetTranslate �Ŏw�肷�镽�s�ړ��l�� y �̌����𔽓]���邩��ݒ肷��( UseFlag   TRUE:���]����( �f�t�H���g )   FALSE:���]���Ȃ� )

extern	int			NS_Live2D_Model_Update( int Live2DModelHandle, float DeltaTime ) ;											// Live2D �̃��f���̏�Ԃ��X�V����
extern	int			NS_Live2D_Model_SetTranslate(		int Live2DModelHandle, float x, float y ) ;								// Live2D �̃��f���̈ʒu��ݒ肷��
extern	int			NS_Live2D_Model_SetExtendRate(		int Live2DModelHandle, float ExRateX, float ExRateY ) ;					// Live2D �̃��f���̊g�嗦��ݒ肷��
extern	int			NS_Live2D_Model_SetRotate(			int Live2DModelHandle, float Angle ) ;									// Live2D �̃��f���̉�]��ݒ肷��
extern	int			NS_Live2D_Model_Draw(				int Live2DModelHandle ) ;														// Live2D �̃��f����`�悷��

extern	int			NS_Live2D_Model_StartMotion(				int Live2DModelHandle, const TCHAR *group,						int no, float fadeInSeconds, float fadeOutSeconds, int isLoopFadeIn ) ;							// Live2D �̃��f���̎w��̃��[�V�������Đ�����
extern	int			NS_Live2D_Model_StartMotionWithStrLen(		int Live2DModelHandle, const TCHAR *group, size_t GroupLength,	int no, float fadeInSeconds, float fadeOutSeconds, int isLoopFadeIn ) ;							// Live2D �̃��f���̎w��̃��[�V�������Đ�����
extern	int			NS_Live2D_Model_GetLastPlayMotionNo(		int Live2DModelHandle ) ;																			// Live2D �̃��f���ōŌ�ɍĐ��������[�V�����̃O���[�v���̔ԍ����擾����
extern	int			NS_Live2D_Model_IsMotionFinished(			int Live2DModelHandle ) ;																			// Live2D �̃��f���̃��[�V�����Đ����I�����Ă��邩���擾����
extern	float		NS_Live2D_Model_GetMotionPlayTime(			int Live2DModelHandle ) ;																			// Live2D �̃��f���̃��[�V�����Đ����Ԃ��擾����
extern	int			NS_Live2D_Model_SetExpression(				int Live2DModelHandle, const TCHAR *expressionID ) ;												// Live2D �̃��f���̎w��̕\��[�V�������Z�b�g����
extern	int			NS_Live2D_Model_SetExpressionWithStrLen(	int Live2DModelHandle, const TCHAR *expressionID, size_t expressionIDLength ) ;						// Live2D �̃��f���̎w��̕\��[�V�������Z�b�g����
extern	int			NS_Live2D_Model_HitTest(					int Live2DModelHandle, const TCHAR *hitAreaName,							float x, float y ) ;	// �w��̍��W�� Live2D �̃��f���̎w��̓����蔻��̋�`�͈͓������肷��( TRUE:��`�͈͓�  FALSE:��`�͈͊O )
extern	int			NS_Live2D_Model_HitTestWithStrLen(			int Live2DModelHandle, const TCHAR *hitAreaName, size_t hitAreaNameLength,	float x, float y ) ;	// �w��̍��W�� Live2D �̃��f���̎w��̓����蔻��̋�`�͈͓������肷��( TRUE:��`�͈͓�  FALSE:��`�͈͊O )

extern	int			NS_Live2D_Model_GetParameterCount(						int Live2DModelHandle ) ;																// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^�̐����擾����
extern	const TCHAR *NS_Live2D_Model_GetParameterId(						int Live2DModelHandle, int index ) ;													// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^��ID���擾����
extern	float		NS_Live2D_Model_GetParameterValue(						int Live2DModelHandle, const TCHAR *parameterId ) ;										// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^���擾����
extern	float		NS_Live2D_Model_GetParameterValueWithStrLen(			int Live2DModelHandle, const TCHAR *parameterId, size_t parameterIdLength ) ;			// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^���擾����
extern	int			NS_Live2D_Model_SetParameterValue(						int Live2DModelHandle, const TCHAR *parameterId, float value ) ;						// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^��ݒ肷��
extern	int			NS_Live2D_Model_SetParameterValueWithStrLen(			int Live2DModelHandle, const TCHAR *parameterId, size_t parameterIdLength, float value ) ;	// Live2D �̃��f���ɐݒ肳��Ă���p�����[�^��ݒ肷��

extern	int			NS_Live2D_Model_GetHitAreasCount(						int Live2DModelHandle ) ;																// Live2D �̃��f���ɐݒ肳�ꂽ�����蔻��̐����擾����
extern	const TCHAR *NS_Live2D_Model_GetHitAreaName(						int Live2DModelHandle, int index ) ;													// Live2D �̃��f���̓����蔻��ɐݒ肳�ꂽ���O���擾����
extern	const TCHAR *NS_Live2D_Model_GetPhysicsFileName(					int Live2DModelHandle ) ;																// Live2D �̃��f���̕������Z�ݒ�t�@�C���̖��O���擾����
extern	const TCHAR *NS_Live2D_Model_GetPoseFileName(						int Live2DModelHandle ) ;																// Live2D �̃��f���̃p�[�c�؂�ւ��ݒ�t�@�C���̖��O���擾����
extern	int			NS_Live2D_Model_GetExpressionCount(					int Live2DModelHandle ) ;																// Live2D �̃��f���̕\��ݒ�t�@�C���̐����擾����
extern	const TCHAR *NS_Live2D_Model_GetExpressionName(					int Live2DModelHandle, int index ) ;													// Live2D �̃��f���̕\��ݒ�t�@�C�������ʂ���ID���擾����
extern	const TCHAR *NS_Live2D_Model_GetExpressionFileName(				int Live2DModelHandle, int index ) ;													// Live2D �̃��f���̕\��ݒ�t�@�C���̖��O���擾����
extern	int			NS_Live2D_Model_GetMotionGroupCount(					int Live2DModelHandle ) ;																// Live2D �̃��f���̃��[�V�����O���[�v�̐����擾����
extern	const TCHAR *NS_Live2D_Model_GetMotionGroupName(					int Live2DModelHandle, int index ) ;													// Live2D �̃��f���̃��[�V�����O���[�v�̖��O���擾����
extern	int			NS_Live2D_Model_GetMotionCount(						int Live2DModelHandle, const TCHAR* groupName ) ;										// Live2D �̃��f���̃��[�V�����O���[�v�Ɋ܂܂�郂�[�V�����̐����擾����
extern	int			NS_Live2D_Model_GetMotionCountWithStrLen(				int Live2DModelHandle, const TCHAR* groupName, size_t groupNameLength ) ;				// Live2D �̃��f���̃��[�V�����O���[�v�Ɋ܂܂�郂�[�V�����̐����擾����
extern	const TCHAR *NS_Live2D_Model_GetMotionFileName(					int Live2DModelHandle, const TCHAR* groupName,							int index ) ;	// Live2D �̃��f���̃O���[�v���ƃC���f�b�N�X�l���烂�[�V�����t�@�C���̖��O���擾����
extern	const TCHAR *NS_Live2D_Model_GetMotionFileNameWithStrLen(			int Live2DModelHandle, const TCHAR* groupName, size_t groupNameLength,	int index ) ;	// Live2D �̃��f���̃O���[�v���ƃC���f�b�N�X�l���烂�[�V�����t�@�C���̖��O���擾����
extern	const TCHAR *NS_Live2D_Model_GetMotionSoundFileName(				int Live2DModelHandle, const TCHAR* groupName,							int index ) ;	// Live2D �̃��f���̃��[�V�����ɑΉ�����T�E���h�t�@�C���̖��O���擾����
extern	const TCHAR *NS_Live2D_Model_GetMotionSoundFileNameWithStrLen(		int Live2DModelHandle, const TCHAR* groupName, size_t groupNameLength,	int index ) ;	// Live2D �̃��f���̃��[�V�����ɑΉ�����T�E���h�t�@�C���̖��O���擾����
extern	float		NS_Live2D_Model_GetMotionFadeInTimeValue(				int Live2DModelHandle, const TCHAR* groupName,							int index ) ;	// Live2D �̃��f���̃��[�V�����J�n���̃t�F�[�h�C���������Ԃ��擾����
extern	float		NS_Live2D_Model_GetMotionFadeInTimeValueWithStrLen(	int Live2DModelHandle, const TCHAR* groupName, size_t groupNameLength,	int index ) ;	// Live2D �̃��f���̃��[�V�����J�n���̃t�F�[�h�C���������Ԃ��擾����
extern	float		NS_Live2D_Model_GetMotionFadeOutTimeValue(				int Live2DModelHandle, const TCHAR* groupName,							int index ) ;	// Live2D �̃��f���̃��[�V�����I�����̃t�F�[�h�A�E�g�������Ԃ��擾����
extern	float		NS_Live2D_Model_GetMotionFadeOutTimeValueWithStrLen(	int Live2DModelHandle, const TCHAR* groupName, size_t groupNameLength,	int index ) ;	// Live2D �̃��f���̃��[�V�����I�����̃t�F�[�h�A�E�g�������Ԃ��擾����
extern	const TCHAR *NS_Live2D_Model_GetUserDataFile(						int Live2DModelHandle ) ;																// Live2D �̃��f���̃��[�U�f�[�^�̃t�@�C�������擾����
extern	int			NS_Live2D_Model_GetEyeBlinkParameterCount(				int Live2DModelHandle ) ;																// Live2D �̃��f���̖ڃp�`�Ɋ֘A�t����ꂽ�p�����[�^�̐����擾����
extern	const TCHAR *NS_Live2D_Model_GetEyeBlinkParameterId(				int Live2DModelHandle, int index ) ;													// Live2D �̃��f���̖ڃp�`�Ɋ֘A�t����ꂽ�p�����[�^��ID���擾����
extern	int			NS_Live2D_Model_GetLipSyncParameterCount(				int Live2DModelHandle ) ;																// Live2D �̃��f���̃��b�v�V���N�Ɋ֘A�t����ꂽ�p�����[�^�̐����擾����
extern	const TCHAR *NS_Live2D_Model_GetLipSyncParameterId(				int Live2DModelHandle, int index ) ;													// Live2D �̃��f���̃��b�v�V���N�Ɋ֘A�t����ꂽ�p�����[�^��ID���擾����
extern	float		NS_Live2D_Model_GetCanvasWidth(						int Live2DModelHandle ) ;																// Live2D �̃��f���̃L�����o�X�̉������擾����
extern	float		NS_Live2D_Model_GetCanvasHeight(						int Live2DModelHandle ) ;																// Live2D �̃��f���̃L�����o�X�̏c�����擾����

#endif // DX_NON_LIVE2D_CUBISM4































#else  // DX_THREAD_SAFE


// DxSystem.cpp�֐��v���g�^�C�v�錾

// �E�G�C�g�n�֐�
#define NS_WaitTimer							WaitTimer
#ifndef DX_NON_INPUT
#define NS_WaitKey								WaitKey
#endif // DX_NON_INPUT
#define NS_SleepThread							SleepThread

// �J�E���^�y�ю����擾�n�֐�
#define NS_GetNowCount								GetNowCount
#define NS_GetNowHiPerformanceCount					GetNowHiPerformanceCount
#define NS_GetNowSysPerformanceCount				GetNowSysPerformanceCount
#define NS_GetSysPerformanceFrequency				GetSysPerformanceFrequency
#define NS_ConvSysPerformanceCountToSeconds			ConvSysPerformanceCountToSeconds
#define NS_ConvSysPerformanceCountToMilliSeconds	ConvSysPerformanceCountToMilliSeconds
#define NS_ConvSysPerformanceCountToMicroSeconds	ConvSysPerformanceCountToMicroSeconds
#define NS_ConvSysPerformanceCountToNanoSeconds		ConvSysPerformanceCountToNanoSeconds
#define NS_ConvSecondsToSysPerformanceCount			ConvSecondsToSysPerformanceCount
#define NS_ConvMilliSecondsToSysPerformanceCount	ConvMilliSecondsToSysPerformanceCount
#define NS_ConvMicroSecondsToSysPerformanceCount	ConvMicroSecondsToSysPerformanceCount
#define NS_ConvNanoSecondsToSysPerformanceCount		ConvNanoSecondsToSysPerformanceCount
#define NS_GetDateTime								GetDateTime

// �����擾
#define NS_GetRand								GetRand
#define NS_SRand								SRand

#ifndef DX_NON_MERSENNE_TWISTER
#define NS_GetMersenneTwisterRand				GetMersenneTwisterRand

#define NS_CreateRandHandle						CreateRandHandle	
#define NS_DeleteRandHandle						DeleteRandHandle	
#define NS_SRandHandle							SRandHandle		
#define NS_GetRandHandle						GetRandHandle		
#define NS_GetMersenneTwisterRandHandle			GetMersenneTwisterRandHandle

#endif // DX_NON_MERSENNE_TWISTER

// �o�b�e���[�֘A
#define NS_GetBatteryLifePercent				GetBatteryLifePercent

// �N���b�v�{�[�h�֌W
#define NS_GetClipboardText						GetClipboardText
#define NS_SetClipboardText						SetClipboardText
#define NS_SetClipboardTextWithStrLen			SetClipboardTextWithStrLen

// ini�t�@�C���֌W
#define NS_GetPrivateProfileStringDx					GetPrivateProfileStringDx
#define NS_GetPrivateProfileStringDxWithStrLen			GetPrivateProfileStringDxWithStrLen
#define NS_GetPrivateProfileIntDx						GetPrivateProfileIntDx
#define NS_GetPrivateProfileIntDxWithStrLen				GetPrivateProfileIntDxWithStrLen
#define NS_GetPrivateProfileStringDxForMem				GetPrivateProfileStringDxForMem				
#define NS_GetPrivateProfileStringDxForMemWithStrLen	GetPrivateProfileStringDxForMemWithStrLen	
#define NS_GetPrivateProfileIntDxForMem					GetPrivateProfileIntDxForMem					
#define NS_GetPrivateProfileIntDxForMemWithStrLen		GetPrivateProfileIntDxForMemWithStrLen		










// DxLog.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_LOG

// ���O�o�͐ݒ�֐�
#define NS_SetOutApplicationLogValidFlag				SetOutApplicationLogValidFlag
#define NS_SetOutApplicationSystemLogValidFlag			SetOutApplicationSystemLogValidFlag
#define NS_SetApplicationLogFileName					SetApplicationLogFileName
#define NS_SetApplicationLogFileNameWithStrLen			SetApplicationLogFileNameWithStrLen
#define NS_SetApplicationLogSaveDirectory				SetApplicationLogSaveDirectory
#define NS_SetApplicationLogSaveDirectoryWithStrLen		SetApplicationLogSaveDirectoryWithStrLen
#define NS_SetUseDateNameLogFile						SetUseDateNameLogFile

// �G���[�����֐�
#define NS_LogFileAdd							LogFileAdd
#define NS_LogFileAddWithStrLen					LogFileAddWithStrLen
#define NS_LogFileFmtAdd						LogFileFmtAdd
#define NS_LogFileTabAdd						LogFileTabAdd
#define NS_LogFileTabSub						LogFileTabSub
#define NS_ErrorLogAdd							ErrorLogAdd
#define NS_ErrorLogFmtAdd						ErrorLogFmtAdd
#define NS_ErrorLogTabAdd						ErrorLogTabAdd
#define NS_ErrorLogTabSub						ErrorLogTabSub
#define NS_SetUseTimeStampFlag					SetUseTimeStampFlag
#define NS_AppLogAdd							AppLogAdd

#ifndef DX_NON_PRINTF_DX

// ���O�o�͋@�\�֐�
#define NS_SetLogDrawOutFlag					SetLogDrawOutFlag
#define NS_GetLogDrawFlag						GetLogDrawFlag
#define NS_SetLogFontSize						SetLogFontSize
#define NS_SetLogFontHandle						SetLogFontHandle
#define NS_SetLogDrawArea						SetLogDrawArea

// �ȈՉ�ʏo�͊֐�
#define NS_printfDx								printfDx
#define NS_putsDx								putsDx
#define NS_putsDxWithStrLen						putsDxWithStrLen
#define NS_clsDx								clsDx
#define NS_setPrintColorDx						setPrintColorDx
#endif

#endif // DX_NON_LOG













#ifndef DX_NON_ASYNCLOAD

// DxASyncLoad.cpp�֐��v���g�^�C�v�錾

// �񓯊��ǂݍ��݊֌W
#define NS_SetUseASyncLoadFlag					SetUseASyncLoadFlag
#define NS_GetUseASyncLoadFlag					GetUseASyncLoadFlag
#define NS_CheckHandleASyncLoad					CheckHandleASyncLoad
#define NS_GetHandleASyncLoadResult				GetHandleASyncLoadResult
#define NS_SetASyncLoadFinishDeleteFlag			SetASyncLoadFinishDeleteFlag
#define NS_SetASyncLoadFinishCallback			SetASyncLoadFinishCallback
#define NS_WaitHandleASyncLoad					WaitHandleASyncLoad
#define NS_WaitHandleASyncLoadAll				WaitHandleASyncLoadAll
#define NS_GetASyncLoadNum						GetASyncLoadNum
#define NS_SetASyncLoadThreadNum				SetASyncLoadThreadNum

#endif // DX_NON_ASYNCLOAD










// DxHandle.cpp�֐��v���g�^�C�v�錾

#define NS_SetDeleteHandleFlag					SetDeleteHandleFlag
#define NS_GetHandleNum							GetHandleNum
#define NS_GetMaxHandleNum						GetMaxHandleNum
#define NS_DumpHandleInfo						DumpHandleInfo














// DxWindow.cpp�֐��v���g�^�C�v�錾

#ifdef WINDOWS_DESKTOP_OS

// �֗��֐�
#define NS_GetResourceInfo						GetResourceInfo
#define NS_GetResourceInfoWithStrLen			GetResourceInfoWithStrLen
#define NS_GetResourceIDString					GetResourceIDString

// �E�C���h�E�֌W���擾�֐�
#define NS_GetWindowCRect						GetWindowCRect
#define NS_GetWindowClientRect					GetWindowClientRect
#define NS_GetWindowFrameRect					GetWindowFrameRect
#define NS_GetWindowActiveFlag					GetWindowActiveFlag
#define NS_GetWindowMinSizeFlag					GetWindowMinSizeFlag
#define NS_GetWindowMaxSizeFlag					GetWindowMaxSizeFlag
#define NS_GetMainWindowHandle					GetMainWindowHandle
#define NS_GetWindowModeFlag					GetWindowModeFlag
#define NS_GetDefaultState						GetDefaultState
#define NS_GetMonitorDpi						GetMonitorDpi
#define NS_GetActiveFlag						GetActiveFlag
#define NS_GetNoActiveState						GetNoActiveState
#define NS_GetMouseDispFlag						GetMouseDispFlag
#define NS_GetAlwaysRunFlag						GetAlwaysRunFlag
#define NS__GetSystemInfo						_GetSystemInfo
#define NS_GetPcInfo							GetPcInfo
#define NS_GetWindowOSVersion					GetWindowOSVersion
#define NS_GetUseMMXFlag						GetUseMMXFlag
#define NS_GetUseSSEFlag						GetUseSSEFlag
#define NS_GetUseSSE2Flag						GetUseSSE2Flag
#define NS_GetWindowCloseFlag					GetWindowCloseFlag
#define NS_GetTaskInstance						GetTaskInstance
#define NS_GetUseWindowRgnFlag					GetUseWindowRgnFlag
#define NS_GetWindowSizeChangeEnableFlag		GetWindowSizeChangeEnableFlag
#define NS_GetWindowSizeExtendRate				GetWindowSizeExtendRate
#define NS_GetWindowSize						GetWindowSize
#define NS_GetWindowEdgeWidth					GetWindowEdgeWidth
#define NS_GetWindowPosition					GetWindowPosition
#define NS_GetWindowUserCloseFlag				GetWindowUserCloseFlag
#define NS_CheckWindowMaximizeButtonInput		CheckWindowMaximizeButtonInput
#define NS_GetNotDrawFlag						GetNotDrawFlag
#define NS_GetPaintMessageFlag					GetPaintMessageFlag
#define NS_GetValidHiPerformanceCounter			GetValidHiPerformanceCounter
#define NS_GetInputSystemChar					GetInputSystemChar

// �ݒ�n�֐�
#define NS_ChangeWindowMode						ChangeWindowMode
#define NS_SetUseCharSet						SetUseCharSet
#define NS_LoadPauseGraph						LoadPauseGraph
#define NS_LoadPauseGraphWithStrLen				LoadPauseGraphWithStrLen
#define NS_LoadPauseGraphFromMem				LoadPauseGraphFromMem
#define NS_SetActiveStateChangeCallBackFunction	SetActiveStateChangeCallBackFunction
#define NS_SetWindowText						SetWindowText
#define NS_SetWindowTextDX						SetWindowTextDX
#define NS_SetWindowTextWithStrLen				SetWindowTextWithStrLen
#define NS_SetMainWindowText					SetMainWindowText
#define NS_SetMainWindowTextWithStrLen			SetMainWindowTextWithStrLen
#define NS_SetMainWindowClassName				SetMainWindowClassName
#define NS_SetMainWindowClassNameWithStrLen		SetMainWindowClassNameWithStrLen
#define NS_SetAlwaysRunFlag						SetAlwaysRunFlag
#define NS_SetWindowIconID						SetWindowIconID
#define NS_SetWindowIconHandle					SetWindowIconHandle
#define NS_SetUseASyncChangeWindowModeFunction	SetUseASyncChangeWindowModeFunction
#define NS_SetShutdownCallbackFunction			SetShutdownCallbackFunction
#define NS_SetWindowStyleMode					SetWindowStyleMode
#define NS_SetWindowZOrder						SetWindowZOrder
#define NS_SetWindowSizeChangeEnableFlag		SetWindowSizeChangeEnableFlag
#define NS_SetWindowSizeExtendRate				SetWindowSizeExtendRate
#define NS_SetWindowSize						SetWindowSize
#define NS_SetWindowMaxSize						SetWindowMaxSize
#define NS_SetWindowMinSize						SetWindowMinSize
#define NS_SetWindowPosition					SetWindowPosition
#define NS_SetSysCommandOffFlag					SetSysCommandOffFlag
#define NS_SetSysCommandOffFlagWithStrLen		SetSysCommandOffFlagWithStrLen
#define NS_SetWindowMaximizeButtonBehavior		SetWindowMaximizeButtonBehavior
#define NS_SetHookWinProc						SetHookWinProc
#define NS_SetUseHookWinProcReturnValue			SetUseHookWinProcReturnValue
#define NS_SetDoubleStartValidFlag				SetDoubleStartValidFlag
#define NS_CheckDoubleStart						CheckDoubleStart
#define NS_AddMessageTakeOverWindow				AddMessageTakeOverWindow
#define NS_SubMessageTakeOverWindow				SubMessageTakeOverWindow

#define NS_SetWindowInitPosition				SetWindowInitPosition
#define NS_SetNotWinFlag						SetNotWinFlag
#define NS_SetNotDrawFlag						SetNotDrawFlag
#define NS_SetNotSoundFlag						SetNotSoundFlag
#define NS_SetNotInputFlag						SetNotInputFlag
#define NS_SetDialogBoxHandle					SetDialogBoxHandle
#define NS_SetWindowVisibleFlag					SetWindowVisibleFlag
#define NS_SetWindowMinimizeFlag				SetWindowMinimizeFlag
#define NS_SetWindowUserCloseEnableFlag			SetWindowUserCloseEnableFlag
#define NS_SetUseBorderlessWindowFlag			SetUseBorderlessWindowFlag
#define NS_SetDxLibEndPostQuitMessageFlag		SetDxLibEndPostQuitMessageFlag
#define NS_SetUserWindow						SetUserWindow
#define NS_SetUserChildWindow					SetUserChildWindow
#define NS_SetUserWindowMessageProcessDXLibFlag	SetUserWindowMessageProcessDXLibFlag
#define NS_SetUseFPUPreserveFlag				SetUseFPUPreserveFlag
#define NS_SetValidMousePointerWindowOutClientAreaMoveFlag		SetValidMousePointerWindowOutClientAreaMoveFlag
#define NS_SetUseBackBufferTransColorFlag		SetUseBackBufferTransColorFlag
#define NS_SetUseUpdateLayerdWindowFlag			SetUseUpdateLayerdWindowFlag
#define NS_SetUseMouseEventTransparentWindowFlag SetUseMouseEventTransparentWindowFlag
#define NS_SetResourceModule					SetResourceModule
#define NS_SetUseDxLibWM_PAINTProcess			SetUseDxLibWM_PAINTProcess
#define NS_SetWindows10_WM_CHAR_CancelTime		SetWindows10_WM_CHAR_CancelTime
#define NS_SetUseWindows10_WM_CHAR_CancelTime	SetUseWindows10_WM_CHAR_CancelTime

// �h���b�O���h���b�v���ꂽ�t�@�C���֌W
#define NS_SetDragFileValidFlag					SetDragFileValidFlag
#define NS_DragFileInfoClear					DragFileInfoClear
#define NS_GetDragFilePath						GetDragFilePath
#define NS_GetDragFileNum						GetDragFileNum

// �E�C���h�E�`��̈�ݒ�n�֐�
#define NS_CreateRgnFromGraph					CreateRgnFromGraph
#define NS_CreateRgnFromBaseImage				CreateRgnFromBaseImage
#define NS_SetWindowRgnGraph					SetWindowRgnGraph
#define NS_SetWindowRgnGraphWithStrLen			SetWindowRgnGraphWithStrLen
#define NS_UpdateTransColorWindowRgn			UpdateTransColorWindowRgn

// �c�[���o�[�֌W
#define NS_SetupToolBar							SetupToolBar
#define NS_SetupToolBarWithStrLen				SetupToolBarWithStrLen
#define NS_AddToolBarButton						AddToolBarButton
#define NS_AddToolBarSep						AddToolBarSep
#define NS_GetToolBarButtonState				GetToolBarButtonState
#define NS_SetToolBarButtonState				SetToolBarButtonState
#define NS_DeleteAllToolBarButton				DeleteAllToolBarButton

// ���j���[�֌W
#define NS_SetUseMenuFlag						SetUseMenuFlag
#define NS_SetUseKeyAccelFlag					SetUseKeyAccelFlag

#define NS_AddKeyAccel							AddKeyAccel
#define NS_AddKeyAccelWithStrLen				AddKeyAccelWithStrLen
#define NS_AddKeyAccel_Name						AddKeyAccel_Name
#define NS_AddKeyAccel_NameWithStrLen			AddKeyAccel_NameWithStrLen
#define NS_AddKeyAccel_ID						AddKeyAccel_ID
#define NS_ClearKeyAccel						ClearKeyAccel

#define NS_AddMenuItem							AddMenuItem
#define NS_AddMenuItemWithStrLen				AddMenuItemWithStrLen
#define NS_DeleteMenuItem						DeleteMenuItem
#define NS_DeleteMenuItemWithStrLen				DeleteMenuItemWithStrLen
#define NS_CheckMenuItemSelect					CheckMenuItemSelect
#define NS_CheckMenuItemSelectWithStrLen		CheckMenuItemSelectWithStrLen
#define NS_SetMenuItemEnable					SetMenuItemEnable
#define NS_SetMenuItemEnableWithStrLen			SetMenuItemEnableWithStrLen
#define NS_SetMenuItemMark						SetMenuItemMark
#define NS_SetMenuItemMarkWithStrLen			SetMenuItemMarkWithStrLen
#define NS_CheckMenuItemSelectAll				CheckMenuItemSelectAll

#define NS_AddMenuItem_Name						AddMenuItem_Name
#define NS_AddMenuItem_NameWithStrLen			AddMenuItem_NameWithStrLen
#define NS_AddMenuLine_Name						AddMenuLine_Name
#define NS_AddMenuLine_NameWithStrLen			AddMenuLine_NameWithStrLen
#define NS_InsertMenuItem_Name					InsertMenuItem_Name
#define NS_InsertMenuItem_NameWithStrLen		InsertMenuItem_NameWithStrLen
#define NS_InsertMenuLine_Name					InsertMenuLine_Name
#define NS_InsertMenuLine_NameWithStrLen		InsertMenuLine_NameWithStrLen
#define NS_DeleteMenuItem_Name					DeleteMenuItem_Name
#define NS_DeleteMenuItem_NameWithStrLen		DeleteMenuItem_NameWithStrLen
#define NS_CheckMenuItemSelect_Name				CheckMenuItemSelect_Name
#define NS_CheckMenuItemSelect_NameWithStrLen	CheckMenuItemSelect_NameWithStrLen
#define NS_SetMenuItemEnable_Name				SetMenuItemEnable_Name
#define NS_SetMenuItemEnable_NameWithStrLen		SetMenuItemEnable_NameWithStrLen
#define NS_SetMenuItemMark_Name					SetMenuItemMark_Name
#define NS_SetMenuItemMark_NameWithStrLen		SetMenuItemMark_NameWithStrLen

#define NS_AddMenuItem_ID						AddMenuItem_ID
#define NS_AddMenuItem_IDWithStrLen				AddMenuItem_IDWithStrLen
#define NS_AddMenuLine_ID						AddMenuLine_ID
#define NS_InsertMenuItem_ID					InsertMenuItem_ID
#define NS_InsertMenuLine_ID					InsertMenuLine_ID
#define NS_DeleteMenuItem_ID					DeleteMenuItem_ID
#define NS_CheckMenuItemSelect_ID				CheckMenuItemSelect_ID
#define NS_SetMenuItemEnable_ID					SetMenuItemEnable_ID
#define NS_SetMenuItemMark_ID					SetMenuItemMark_ID

#define NS_DeleteMenuItemAll					DeleteMenuItemAll
#define NS_ClearMenuItemSelect					ClearMenuItemSelect
#define NS_GetMenuItemID						GetMenuItemID
#define NS_GetMenuItemIDDX						GetMenuItemIDDX
#define NS_GetMenuItemIDWithStrLen				GetMenuItemIDWithStrLen
#define NS_GetMenuItemName						GetMenuItemName
#define NS_LoadMenuResource						LoadMenuResource
#define NS_SetMenuItemSelectCallBackFunction	SetMenuItemSelectCallBackFunction

#define NS_SetWindowMenu						SetWindowMenu
#define NS_SetDisplayMenuFlag					SetDisplayMenuFlag
#define NS_GetDisplayMenuFlag					GetDisplayMenuFlag
#define NS_GetUseMenuFlag						GetUseMenuFlag
#define NS_SetAutoMenuDisplayFlag				SetAutoMenuDisplayFlag

#endif // WINDOWS_DESKTOP_OS

// �}�E�X�֌W�֐�
#define NS_SetMouseDispFlag						SetMouseDispFlag
#define NS_SetMouseDispIgnoreMenuFlag			SetMouseDispIgnoreMenuFlag
#ifndef DX_NON_INPUT
#define NS_GetMousePoint						GetMousePoint
#define NS_SetMousePoint						SetMousePoint
#define NS_GetMouseInput						GetMouseInput
#define NS_GetMouseWheelRotVol					GetMouseWheelRotVol
#define NS_GetMouseHWheelRotVol					GetMouseHWheelRotVol
#define NS_GetMouseWheelRotVolF					GetMouseWheelRotVolF
#define NS_GetMouseHWheelRotVolF				GetMouseHWheelRotVolF
#define NS_GetMouseInputLog						GetMouseInputLog
#define NS_GetMouseInputLog2					GetMouseInputLog2
#endif // DX_NON_INPUT













// �^�b�`�p�l�����͊֌W�֐�
#ifndef DX_NON_INPUT
#define NS_GetTouchInputNum						GetTouchInputNum
#define NS_GetTouchInput						GetTouchInput

#define NS_GetTouchInputLogNum					GetTouchInputLogNum
#define NS_ClearTouchInputLog					ClearTouchInputLog
#define NS_GetTouchInputLogOne					GetTouchInputLogOne
#define NS_GetTouchInputLog						GetTouchInputLog

#define NS_GetTouchInputDownLogNum				GetTouchInputDownLogNum
#define NS_ClearTouchInputDownLog				ClearTouchInputDownLog
#define NS_GetTouchInputDownLogOne				GetTouchInputDownLogOne
#define NS_GetTouchInputDownLog					GetTouchInputDownLog

#define NS_GetTouchInputUpLogNum				GetTouchInputUpLogNum
#define NS_ClearTouchInputUpLog					ClearTouchInputUpLog
#define NS_GetTouchInputUpLogOne				GetTouchInputUpLogOne
#define NS_GetTouchInputUpLog					GetTouchInputUpLog
#endif // DX_NON_INPUT












// DxMemory.cpp�֐��v���g�^�C�v�錾

// �������m�یn�֐�
#define NS_DxAlloc								DxAlloc
#define NS_DxAllocAligned						DxAllocAligned
#define NS_DxCalloc								DxCalloc
#define NS_DxCallocAligned						DxCallocAligned
#define NS_DxRealloc							DxRealloc
#define NS_DxReallocAligned						DxReallocAligned
#define NS_DxFree								DxFree
#define NS_DxSetAllocSizeTrap					DxSetAllocSizeTrap
#define NS_DxSetAllocPrintFlag					DxSetAllocPrintFlag
#define NS_DxGetAllocSize						DxGetAllocSize
#define NS_DxGetAllocNum						DxGetAllocNum
#define NS_DxDumpAlloc							DxDumpAlloc
#define NS_DxDrawAlloc							DxDrawAlloc
#define NS_DxErrorCheckAlloc					DxErrorCheckAlloc
#define NS_DxSetAllocSizeOutFlag				DxSetAllocSizeOutFlag
#define NS_DxSetAllocMemoryErrorCheckFlag		DxSetAllocMemoryErrorCheckFlag














// DxBaseFunc.cpp �֐��v���g�^�C�v�錾

// �����R�[�h�֌W
#define NS_GetCharBytes							GetCharBytes
#define NS_ConvertStringCharCodeFormat			ConvertStringCharCodeFormat
#define NS_SetUseCharCodeFormat					SetUseCharCodeFormat
#define NS_GetUseCharCodeFormat					GetUseCharCodeFormat
#define NS_Get_wchar_t_CharCodeFormat			Get_wchar_t_CharCodeFormat

// ������֌W
#define NS_strcpyDx								strcpyDx
#define NS_strcpy_sDx							strcpy_sDx
#define NS_strpcpyDx							strpcpyDx
#define NS_strpcpy_sDx							strpcpy_sDx
#define NS_strpcpy2Dx							strpcpy2Dx
#define NS_strpcpy2_sDx							strpcpy2_sDx
#define NS_strncpyDx							strncpyDx
#define NS_strncpy_sDx							strncpy_sDx
#define NS_strncpy2Dx							strncpy2Dx
#define NS_strncpy2_sDx							strncpy2_sDx
#define NS_strrncpyDx							strrncpyDx
#define NS_strrncpy_sDx							strrncpy_sDx
#define NS_strrncpy2Dx							strrncpy2Dx
#define NS_strrncpy2_sDx						strrncpy2_sDx
#define NS_strpncpyDx							strpncpyDx
#define NS_strpncpy_sDx							strpncpy_sDx
#define NS_strpncpy2Dx							strpncpy2Dx
#define NS_strpncpy2_sDx						strpncpy2_sDx
#define NS_strcatDx								strcatDx
#define NS_strcat_sDx							strcat_sDx
#define NS_strlenDx								strlenDx
#define NS_strlen2Dx							strlen2Dx
#define NS_strcmpDx								strcmpDx
#define NS_stricmpDx							stricmpDx
#define NS_strncmpDx							strncmpDx
#define NS_strncmp2Dx							strncmp2Dx
#define NS_strpncmpDx							strpncmpDx
#define NS_strpncmp2Dx							strpncmp2Dx
#define NS_strgetchrDx							strgetchrDx
#define NS_strgetchr2Dx							strgetchr2Dx
#define NS_strputchrDx							strputchrDx
#define NS_strputchr2Dx							strputchr2Dx
#define NS_strposDx								strposDx
#define NS_strpos2Dx							strpos2Dx
#define NS_strstrDx								strstrDx
#define NS_strstr2Dx							strstr2Dx
#define NS_strrstrDx							strrstrDx
#define NS_strrstr2Dx							strrstr2Dx
#define NS_strchrDx								strchrDx
#define NS_strchr2Dx							strchr2Dx
#define NS_strrchrDx							strrchrDx
#define NS_strrchr2Dx							strrchr2Dx
#define NS_struprDx								struprDx
#define NS_vsprintfDx							vsprintfDx
#define NS_vsnprintfDx							vsnprintfDx
#define NS_sprintfDx							sprintfDx
#define NS_snprintfDx							snprintfDx
#define NS_itoaDx								itoaDx
#define NS_itoa_sDx								itoa_sDx
#define NS_atoiDx								atoiDx
#define NS_atofDx								atofDx
#define NS_vsscanfDx							vsscanfDx
#define NS_sscanfDx								sscanfDx









// DxInputString.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_INPUTSTRING

// �����R�[�h�o�b�t�@����֌W
#define NS_StockInputChar						StockInputChar
#define NS_ClearInputCharBuf					ClearInputCharBuf
#define NS_GetInputChar							GetInputChar
#define NS_GetInputCharWait						GetInputCharWait

#define NS_GetOneChar							GetOneChar
#define NS_GetOneCharWait						GetOneCharWait
#define NS_GetCtrlCodeCmp						GetCtrlCodeCmp

#ifndef DX_NON_KEYEX

#define NS_DrawIMEInputString					DrawIMEInputString
#define NS_DrawIMEInputExtendString				DrawIMEInputExtendString
#define NS_SetUseIMEFlag						SetUseIMEFlag
#define NS_GetUseIMEFlag						GetUseIMEFlag
#define NS_SetInputStringMaxLengthIMESync		SetInputStringMaxLengthIMESync
#define NS_SetIMEInputStringMaxLength			SetIMEInputStringMaxLength
#define NS_SetUseTSFFlag						SetUseTSFFlag

#endif

#define NS_GetStringPoint						GetStringPoint
#define NS_GetStringPointWithStrLen				GetStringPointWithStrLen
#define NS_GetStringPoint2						GetStringPoint2
#define NS_GetStringPoint2WithStrLen			GetStringPoint2WithStrLen
#define NS_GetStringLength						GetStringLength

#ifndef DX_NON_FONT
#define NS_DrawObtainsString						DrawObtainsString
#define NS_DrawObtainsNString						DrawObtainsNString
#define NS_DrawObtainsString_CharClip				DrawObtainsString_CharClip
#define NS_DrawObtainsNString_CharClip				DrawObtainsNString_CharClip
#define NS_DrawObtainsString_WordClip				DrawObtainsString_WordClip
#define NS_DrawObtainsNString_WordClip				DrawObtainsNString_WordClip
#define NS_GetObtainsStringCharPosition				GetObtainsStringCharPosition
#define NS_GetObtainsStringCharPosition_CharClip	GetObtainsStringCharPosition_CharClip
#define NS_GetObtainsStringCharPosition_WordClip	GetObtainsStringCharPosition_WordClip
#endif // DX_NON_FONT
#define NS_DrawObtainsBox						DrawObtainsBox

#ifndef DX_NON_KEYEX

#define NS_InputStringToCustom					InputStringToCustom

#define NS_KeyInputString						KeyInputString
#define NS_KeyInputSingleCharString				KeyInputSingleCharString
#define NS_KeyInputNumber						KeyInputNumber

#define NS_GetIMEInputModeStr					GetIMEInputModeStr
#define NS_GetIMEInputData						GetIMEInputData
#define NS_SetIMEInputString					SetIMEInputString
#define NS_SetIMEInputStringWithStrLen			SetIMEInputStringWithStrLen
#define NS_SetKeyInputStringColor				SetKeyInputStringColor
#define NS_SetKeyInputStringColor2				SetKeyInputStringColor2
#define NS_ResetKeyInputStringColor2			ResetKeyInputStringColor2
#define NS_SetKeyInputStringFont				SetKeyInputStringFont
#define NS_SetKeyInputStringEndCharaMode		SetKeyInputStringEndCharaMode
#define NS_DrawKeyInputModeString				DrawKeyInputModeString

#define NS_InitKeyInput							InitKeyInput
#define NS_MakeKeyInput							MakeKeyInput
#define NS_DeleteKeyInput						DeleteKeyInput
#define NS_SetActiveKeyInput					SetActiveKeyInput
#define NS_GetActiveKeyInput					GetActiveKeyInput
#define NS_CheckKeyInput						CheckKeyInput
#define NS_ReStartKeyInput						ReStartKeyInput
#define NS_ProcessActKeyInput					ProcessActKeyInput
#define NS_DrawKeyInputString					DrawKeyInputString
#define NS_DrawKeyInputExtendString				DrawKeyInputExtendString
#define NS_SetKeyInputDrawArea					SetKeyInputDrawArea

#define NS_SetKeyInputSelectArea				SetKeyInputSelectArea
#define NS_GetKeyInputSelectArea				GetKeyInputSelectArea
#define NS_SetKeyInputDrawStartPos				SetKeyInputDrawStartPos
#define NS_GetKeyInputDrawStartPos				GetKeyInputDrawStartPos
#define NS_SetKeyInputCursorBrinkTime			SetKeyInputCursorBrinkTime
#define NS_SetKeyInputCursorBrinkFlag			SetKeyInputCursorBrinkFlag
#define NS_SetKeyInputString					SetKeyInputString
#define NS_SetKeyInputStringWithStrLen			SetKeyInputStringWithStrLen
#define NS_SetKeyInputNumber					SetKeyInputNumber
#define NS_SetKeyInputNumberToFloat				SetKeyInputNumberToFloat
#define NS_GetKeyInputString					GetKeyInputString
#define NS_GetKeyInputNumber					GetKeyInputNumber
#define NS_GetKeyInputNumberToFloat				GetKeyInputNumberToFloat
#define NS_SetKeyInputCursorPosition			SetKeyInputCursorPosition
#define NS_GetKeyInputCursorPosition			GetKeyInputCursorPosition

#endif // DX_NON_KEYEX

#endif // DX_NON_INPUTSTRING












// DxFile.cpp�֐��v���g�^�C�v�錾

// �t�@�C���A�N�Z�X�֐�
#define NS_FileRead_open						FileRead_open
#define NS_FileRead_open_WithStrLen				FileRead_open_WithStrLen
#define NS_FileRead_open_mem					FileRead_open_mem
#define NS_FileRead_size						FileRead_size
#define NS_FileRead_size_WithStrLen				FileRead_size_WithStrLen
#define NS_FileRead_size_handle					FileRead_size_handle
#define NS_FileRead_close						FileRead_close
#define NS_FileRead_tell						FileRead_tell
#define NS_FileRead_seek						FileRead_seek
#define NS_FileRead_read						FileRead_read
#define NS_FileRead_idle_chk					FileRead_idle_chk
#define NS_FileRead_eof							FileRead_eof
#define NS_FileRead_set_format					FileRead_set_format
#define NS_FileRead_gets						FileRead_gets
#define NS_FileRead_getc						FileRead_getc
#define NS_FileRead_scanf						FileRead_scanf

#define NS_FileRead_createInfo					FileRead_createInfo
#define NS_FileRead_createInfo_WithStrLen		FileRead_createInfo_WithStrLen
#define NS_FileRead_getInfoNum					FileRead_getInfoNum
#define NS_FileRead_getInfo						FileRead_getInfo
#define NS_FileRead_deleteInfo					FileRead_deleteInfo

#define NS_FileRead_findFirst					FileRead_findFirst
#define NS_FileRead_findFirst_WithStrLen		FileRead_findFirst_WithStrLen
#define NS_FileRead_findNext					FileRead_findNext
#define NS_FileRead_findClose					FileRead_findClose

#define NS_FileRead_fullyLoad					FileRead_fullyLoad
#define NS_FileRead_fullyLoad_WithStrLen		FileRead_fullyLoad_WithStrLen
#define NS_FileRead_fullyLoad_check				FileRead_fullyLoad_check
#define NS_FileRead_fullyLoad_delete			FileRead_fullyLoad_delete
#define NS_FileRead_fullyLoad_getImage			FileRead_fullyLoad_getImage
#define NS_FileRead_fullyLoad_getSize			FileRead_fullyLoad_getSize

// �ݒ�֌W�֐�
#define NS_GetStreamFunctionDefault				GetStreamFunctionDefault
#define NS_ChangeStreamFunction					ChangeStreamFunction
#define NS_ChangeStreamFunctionW				ChangeStreamFunctionW

// �⏕�֌W�֐�
#define NS_ConvertFullPath						ConvertFullPath
#define NS_ConvertFullPathWithStrLen			ConvertFullPathWithStrLen









// DxNetwork.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_NETWORK
#define NS_GetWinSockLastError					GetWinSockLastError
#endif // DX_NON_NETWORK







// DxInput.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_INPUT

// ���͏�Ԏ擾�֐�
#define NS_CheckHitKey							CheckHitKey
#define NS_CheckHitKeyAll						CheckHitKeyAll
#define NS_GetHitKeyStateAll					GetHitKeyStateAll
#define NS_GetHitKeyStateAllEx					GetHitKeyStateAllEx
#define NS_SetKeyExclusiveCooperativeLevelFlag	SetKeyExclusiveCooperativeLevelFlag
#define NS_GetJoypadNum							GetJoypadNum
#define NS_GetJoypadButtonNum					GetJoypadButtonNum
#define NS_GetJoypadInputState					GetJoypadInputState
#define NS_GetJoypadAnalogInput					GetJoypadAnalogInput
#define NS_GetJoypadAnalogInputRight			GetJoypadAnalogInputRight
#define NS_GetJoypadDirectInputState			GetJoypadDirectInputState
#define NS_CheckJoypadXInput					CheckJoypadXInput
#define NS_GetJoypadXInputState					GetJoypadXInputState
#define NS_GetJoypadGUID						GetJoypadGUID
#define NS_ConvertKeyCodeToVirtualKey			ConvertKeyCodeToVirtualKey
#define NS_ConvertVirtualKeyToKeyCode			ConvertVirtualKeyToKeyCode
#define NS_SetJoypadInputToKeyInput				SetJoypadInputToKeyInput
#define NS_SetJoypadDeadZone					SetJoypadDeadZone
#define NS_GetJoypadDeadZone					GetJoypadDeadZone
#define NS_SetJoypadDefaultDeadZoneAll			SetJoypadDefaultDeadZoneAll
#define NS_GetJoypadDefaultDeadZoneAll			GetJoypadDefaultDeadZoneAll
#define NS_StartJoypadVibration					StartJoypadVibration
#define NS_StopJoypadVibration					StopJoypadVibration
#define NS_GetJoypadPOVState					GetJoypadPOVState
#define NS_GetJoypadName						GetJoypadName
#define NS_GetJoypadType						GetJoypadType
#define NS_ReSetupJoypad						ReSetupJoypad
#define NS_ReSetupInputSystem					ReSetupInputSystem

#define NS_SetKeyboardNotDirectInputFlag		SetKeyboardNotDirectInputFlag
#define NS_SetUseDirectInputFlag				SetUseDirectInputFlag
#define NS_SetDirectInputMouseMode				SetDirectInputMouseMode
#define NS_SetUseXInputFlag						SetUseXInputFlag
#define NS_SetUseXboxControllerDirectInputFlag	SetUseXboxControllerDirectInputFlag
#define NS_SetUseJoypadVibrationFlag			SetUseJoypadVibrationFlag

#endif // DX_NON_INPUT













#ifndef DX_NOTUSE_DRAWFUNCTION

// �O���t�B�b�N�n���h���쐬�֌W�֐�
#define NS_MakeGraph							MakeGraph
#define NS_MakeScreen							MakeScreen
#define NS_DerivationGraph						DerivationGraph
#define NS_DerivationGraphF						DerivationGraphF
#define NS_DeleteGraph							DeleteGraph
#define NS_DeleteSharingGraph					DeleteSharingGraph
#define NS_GetGraphNum							GetGraphNum
#define NS_FillGraph							FillGraph
#define NS_FillRectGraph						FillRectGraph
#define NS_SetGraphLostFlag						SetGraphLostFlag
#define NS_InitGraph							InitGraph
#define NS_ReloadFileGraphAll					ReloadFileGraphAll

// �V���h�E�}�b�v�n���h���֌W�֐�
#define NS_MakeShadowMap						MakeShadowMap
#define NS_DeleteShadowMap						DeleteShadowMap
#define NS_SetShadowMapLightDirection			SetShadowMapLightDirection
#define NS_ShadowMap_DrawSetup					ShadowMap_DrawSetup
#define NS_ShadowMap_DrawEnd					ShadowMap_DrawEnd
#define NS_SetUseShadowMap						SetUseShadowMap
#define NS_SetShadowMapDrawArea					SetShadowMapDrawArea
#define NS_ResetShadowMapDrawArea				ResetShadowMapDrawArea
#define NS_SetShadowMapAdjustDepth				SetShadowMapAdjustDepth
#define NS_GetShadowMapViewProjectionMatrix		GetShadowMapViewProjectionMatrix
#define NS_SetShadowMapBlurParam				SetShadowMapBlurParam
#define NS_SetShadowMapGradationParam			SetShadowMapGradationParam
#define NS_TestDrawShadowMap					TestDrawShadowMap

// �O���t�B�b�N�n���h���ւ̉摜�]���֐�
#define NS_BltBmpToGraph						BltBmpToGraph
#define NS_BltBmpToDivGraph						BltBmpToDivGraph
#define NS_BltBmpOrGraphImageToGraph			BltBmpOrGraphImageToGraph
#define NS_BltBmpOrGraphImageToGraph2			BltBmpOrGraphImageToGraph2
#define NS_BltBmpOrGraphImageToDivGraph			BltBmpOrGraphImageToDivGraph
#define NS_BltBmpOrGraphImageToDivGraphF		BltBmpOrGraphImageToDivGraphF

// �摜����O���t�B�b�N�n���h�����쐬����֐�
#define NS_LoadBmpToGraph						LoadBmpToGraph
#define NS_LoadBmpToGraphWithStrLen				LoadBmpToGraphWithStrLen
#define NS_LoadGraph							LoadGraph
#define NS_LoadGraphWithStrLen					LoadGraphWithStrLen
#define NS_LoadReverseGraph						LoadReverseGraph
#define NS_LoadReverseGraphWithStrLen			LoadReverseGraphWithStrLen
#define NS_LoadDivGraph							LoadDivGraph
#define NS_LoadDivGraphWithStrLen				LoadDivGraphWithStrLen
#define NS_LoadDivGraphF						LoadDivGraphF
#define NS_LoadDivGraphFWithStrLen				LoadDivGraphFWithStrLen
#define NS_LoadDivBmpToGraph					LoadDivBmpToGraph
#define NS_LoadDivBmpToGraphWithStrLen			LoadDivBmpToGraphWithStrLen
#define NS_LoadDivBmpToGraphF					LoadDivBmpToGraphF
#define NS_LoadDivBmpToGraphFWithStrLen			LoadDivBmpToGraphFWithStrLen
#define NS_LoadReverseDivGraph					LoadReverseDivGraph
#define NS_LoadReverseDivGraphWithStrLen		LoadReverseDivGraphWithStrLen
#define NS_LoadReverseDivGraphF					LoadReverseDivGraphF
#define NS_LoadReverseDivGraphFWithStrLen		LoadReverseDivGraphFWithStrLen
#define NS_LoadBlendGraph						LoadBlendGraph
#define NS_LoadBlendGraphWithStrLen				LoadBlendGraphWithStrLen
#ifdef WINDOWS_DESKTOP_OS
#define NS_LoadGraphToResource					LoadGraphToResource
#define NS_LoadDivGraphToResource				LoadDivGraphToResource
#define NS_LoadDivGraphFToResource				LoadDivGraphFToResource
#define NS_LoadGraphToResource					LoadGraphToResource
#define NS_LoadGraphToResourceWithStrLen		LoadGraphToResourceWithStrLen
#define NS_LoadDivGraphToResource				LoadDivGraphToResource
#define NS_LoadDivGraphToResourceWithStrLen		LoadDivGraphToResourceWithStrLen
#define NS_LoadDivGraphFToResource				LoadDivGraphFToResource
#define NS_LoadDivGraphFToResourceWithStrLen	LoadDivGraphFToResourceWithStrLen
#define NS_LoadGraphToResource2					LoadGraphToResource2
#define NS_LoadGraphToResourceWithStrLen2		LoadGraphToResourceWithStrLen2
#define NS_LoadDivGraphToResource2				LoadDivGraphToResource2
#define NS_LoadDivGraphToResourceWithStrLen2	LoadDivGraphToResourceWithStrLen2
#define NS_LoadDivGraphFToResource2				LoadDivGraphFToResource2
#define NS_LoadDivGraphFToResourceWithStrLen2	LoadDivGraphFToResourceWithStrLen2
#ifndef DX_NON_DIRECT3D11
#define NS_CreateGraphFromID3D11Texture2D		CreateGraphFromID3D11Texture2D
#endif // DX_NON_DIRECT3D11
#endif // WINDOWS_DESKTOP_OS

#define NS_CreateGraphFromMem					CreateGraphFromMem
#define NS_ReCreateGraphFromMem					ReCreateGraphFromMem
#define NS_CreateDivGraphFromMem				CreateDivGraphFromMem
#define NS_CreateDivGraphFFromMem				CreateDivGraphFFromMem
#define NS_ReCreateDivGraphFromMem				ReCreateDivGraphFromMem
#define NS_ReCreateDivGraphFFromMem				ReCreateDivGraphFFromMem
#define NS_CreateGraphFromBmp					CreateGraphFromBmp
#define NS_ReCreateGraphFromBmp					ReCreateGraphFromBmp
#define NS_CreateDivGraphFromBmp				CreateDivGraphFromBmp
#define NS_CreateDivGraphFFromBmp				CreateDivGraphFFromBmp
#define NS_ReCreateDivGraphFromBmp				ReCreateDivGraphFromBmp
#define NS_ReCreateDivGraphFFromBmp				ReCreateDivGraphFFromBmp
#define NS_CreateDXGraph						CreateDXGraph
#define NS_CreateGraphFromGraphImage			CreateGraphFromGraphImage
#define NS_ReCreateGraphFromGraphImage			ReCreateGraphFromGraphImage
#define NS_CreateDivGraphFromGraphImage			CreateDivGraphFromGraphImage
#define NS_CreateDivGraphFFromGraphImage		CreateDivGraphFFromGraphImage
#define NS_ReCreateDivGraphFromGraphImage		ReCreateDivGraphFromGraphImage
#define NS_ReCreateDivGraphFFromGraphImage		ReCreateDivGraphFFromGraphImage
#define NS_CreateGraphFromGraphImage2			CreateGraphFromGraphImage2
#define NS_ReCreateGraphFromGraphImage2			ReCreateGraphFromGraphImage2
#define NS_CreateDivGraphFromGraphImage2		CreateDivGraphFromGraphImage2
#define NS_CreateDivGraphFFromGraphImage2		CreateDivGraphFFromGraphImage2
#define NS_ReCreateDivGraphFromGraphImage2		ReCreateDivGraphFromGraphImage2
#define NS_ReCreateDivGraphFFromGraphImage2		ReCreateDivGraphFFromGraphImage2
#define NS_CreateGraph							CreateGraph
#define NS_CreateDivGraph						CreateDivGraph
#define NS_CreateDivGraphF						CreateDivGraphF
#define NS_ReCreateGraph						ReCreateGraph
#ifndef DX_NON_SOFTIMAGE
#define NS_CreateBlendGraphFromSoftImage		CreateBlendGraphFromSoftImage
#define NS_CreateGraphFromSoftImage				CreateGraphFromSoftImage
#define NS_CreateGraphFromRectSoftImage			CreateGraphFromRectSoftImage
#define NS_ReCreateGraphFromSoftImage			ReCreateGraphFromSoftImage
#define NS_ReCreateGraphFromRectSoftImage		ReCreateGraphFromRectSoftImage
#define NS_CreateDivGraphFromSoftImage			CreateDivGraphFromSoftImage
#define NS_CreateDivGraphFFromSoftImage			CreateDivGraphFFromSoftImage
#define NS_ReCreateDivGraphFromSoftImage		ReCreateDivGraphFromSoftImage
#define NS_ReCreateDivGraphFFromSoftImage		ReCreateDivGraphFFromSoftImage
#endif // DX_NON_SOFTIMAGE
#define NS_CreateGraphFromBaseImage				CreateGraphFromBaseImage
#define NS_CreateGraphFromRectBaseImage			CreateGraphFromRectBaseImage
#define NS_ReCreateGraphFromBaseImage			ReCreateGraphFromBaseImage
#define NS_ReCreateGraphFromRectBaseImage		ReCreateGraphFromRectBaseImage
#define NS_CreateDivGraphFromBaseImage			CreateDivGraphFromBaseImage
#define NS_CreateDivGraphFFromBaseImage			CreateDivGraphFFromBaseImage
#define NS_ReCreateDivGraphFromBaseImage		ReCreateDivGraphFromBaseImage
#define NS_ReCreateDivGraphFFromBaseImage		ReCreateDivGraphFFromBaseImage
#define NS_ReloadGraph							ReloadGraph
#define NS_ReloadGraphWithStrLen				ReloadGraphWithStrLen
#define NS_ReloadDivGraph						ReloadDivGraph
#define NS_ReloadDivGraphWithStrLen				ReloadDivGraphWithStrLen
#define NS_ReloadDivGraphF						ReloadDivGraphF
#define NS_ReloadDivGraphFWithStrLen			ReloadDivGraphFWithStrLen
#define NS_ReloadReverseGraph					ReloadReverseGraph
#define NS_ReloadReverseGraphWithStrLen			ReloadReverseGraphWithStrLen
#define NS_ReloadReverseDivGraph				ReloadReverseDivGraph
#define NS_ReloadReverseDivGraphWithStrLen		ReloadReverseDivGraphWithStrLen
#define NS_ReloadReverseDivGraphF				ReloadReverseDivGraphF
#define NS_ReloadReverseDivGraphFWithStrLen		ReloadReverseDivGraphFWithStrLen

// �O���t�B�b�N�n���h���쐬���ݒ�W�֐�
#define NS_SetGraphColorBitDepth				SetGraphColorBitDepth
#define NS_GetGraphColorBitDepth				GetGraphColorBitDepth
#define NS_SetCreateGraphColorBitDepth			SetCreateGraphColorBitDepth
#define NS_GetCreateGraphColorBitDepth			GetCreateGraphColorBitDepth
#define NS_SetCreateGraphChannelBitDepth		SetCreateGraphChannelBitDepth
#define NS_GetCreateGraphChannelBitDepth		GetCreateGraphChannelBitDepth
#define NS_SetCreateGraphInitGraphDelete		SetCreateGraphInitGraphDelete
#define NS_GetCreateGraphInitGraphDelete		GetCreateGraphInitGraphDelete
#define NS_SetCreateGraphHandle					SetCreateGraphHandle
#define NS_GetCreateGraphHandle					GetCreateGraphHandle
#define NS_SetCreateDivGraphHandle				SetCreateDivGraphHandle
#define NS_GetCreateDivGraphHandle				GetCreateDivGraphHandle
#define NS_SetDrawValidGraphCreateFlag			SetDrawValidGraphCreateFlag
#define NS_GetDrawValidGraphCreateFlag			GetDrawValidGraphCreateFlag
#define NS_SetDrawValidFlagOf3DGraph			SetDrawValidFlagOf3DGraph
#define NS_SetLeftUpColorIsTransColorFlag		SetLeftUpColorIsTransColorFlag
#define NS_SetUsePaletteGraphFlag				SetUsePaletteGraphFlag
#define NS_SetUseSystemMemGraphCreateFlag		SetUseSystemMemGraphCreateFlag
#define NS_GetUseSystemMemGraphCreateFlag		GetUseSystemMemGraphCreateFlag
#define NS_SetUseBlendGraphCreateFlag			SetUseBlendGraphCreateFlag
#define NS_GetUseBlendGraphCreateFlag			GetUseBlendGraphCreateFlag
#define NS_SetUseAlphaTestGraphCreateFlag		SetUseAlphaTestGraphCreateFlag
#define NS_GetUseAlphaTestGraphCreateFlag		GetUseAlphaTestGraphCreateFlag
#define NS_SetUseAlphaTestFlag					SetUseAlphaTestFlag
#define NS_GetUseAlphaTestFlag					GetUseAlphaTestFlag
#define NS_SetCubeMapTextureCreateFlag			SetCubeMapTextureCreateFlag
#define NS_GetCubeMapTextureCreateFlag			GetCubeMapTextureCreateFlag
#define NS_SetUseNoBlendModeParam				SetUseNoBlendModeParam
#define NS_SetDrawValidAlphaChannelGraphCreateFlag		SetDrawValidAlphaChannelGraphCreateFlag
#define NS_GetDrawValidAlphaChannelGraphCreateFlag		GetDrawValidAlphaChannelGraphCreateFlag
#define NS_SetDrawValidFloatTypeGraphCreateFlag			SetDrawValidFloatTypeGraphCreateFlag
#define NS_GetDrawValidFloatTypeGraphCreateFlag			GetDrawValidFloatTypeGraphCreateFlag
#define NS_SetDrawValidGraphCreateZBufferFlag			SetDrawValidGraphCreateZBufferFlag
#define NS_GetDrawValidGraphCreateZBufferFlag			GetDrawValidGraphCreateZBufferFlag
#define NS_SetCreateDrawValidGraphZBufferBitDepth		SetCreateDrawValidGraphZBufferBitDepth
#define NS_GetCreateDrawValidGraphZBufferBitDepth		GetCreateDrawValidGraphZBufferBitDepth
#define NS_SetCreateDrawValidGraphMipLevels				SetCreateDrawValidGraphMipLevels
#define NS_GetCreateDrawValidGraphMipLevels				GetCreateDrawValidGraphMipLevels
#define NS_SetCreateDrawValidGraphChannelNum	SetCreateDrawValidGraphChannelNum
#define NS_GetCreateDrawValidGraphChannelNum	GetCreateDrawValidGraphChannelNum
#define NS_SetCreateDrawValidGraphMultiSample	SetCreateDrawValidGraphMultiSample
#define NS_SetDrawValidMultiSample				SetDrawValidMultiSample
#define NS_GetMultiSampleQuality				GetMultiSampleQuality
#define NS_SetUseTransColor						SetUseTransColor
#define NS_SetUseTransColorGraphCreateFlag		SetUseTransColorGraphCreateFlag
#define NS_SetUseGraphAlphaChannel				SetUseGraphAlphaChannel
#define NS_GetUseGraphAlphaChannel				GetUseGraphAlphaChannel
#define NS_SetUseAlphaChannelGraphCreateFlag	SetUseAlphaChannelGraphCreateFlag
#define NS_GetUseAlphaChannelGraphCreateFlag	GetUseAlphaChannelGraphCreateFlag
#define NS_SetUseNotManageTextureFlag			SetUseNotManageTextureFlag
#define NS_GetUseNotManageTextureFlag			GetUseNotManageTextureFlag
#define NS_SetUsePlatformTextureFormat			SetUsePlatformTextureFormat
#define NS_GetUsePlatformTextureFormat			GetUsePlatformTextureFormat
#define NS_SetTransColor						SetTransColor
#define NS_GetTransColor						GetTransColor
#define NS_SetUseDivGraphFlag					SetUseDivGraphFlag
#define NS_SetUseAlphaImageLoadFlag				SetUseAlphaImageLoadFlag
#define NS_SetUseMaxTextureSize					SetUseMaxTextureSize
#define NS_SetUseGraphBaseDataBackup			SetUseGraphBaseDataBackup
#define NS_GetUseGraphBaseDataBackup			GetUseGraphBaseDataBackup
#define NS_SetUseLoadDivGraphSizeCheckFlag		SetUseLoadDivGraphSizeCheckFlag
#define NS_GetUseLoadDivGraphSizeCheckFlag		GetUseLoadDivGraphSizeCheckFlag

// �摜���֌W�֐�
#define NS_GetFullColorImage					GetFullColorImage

#define NS_GraphLock							GraphLock
#define NS_GraphUnLock							GraphUnLock

#define NS_SetUseGraphZBuffer					SetUseGraphZBuffer
#define NS_CopyGraphZBufferImage				CopyGraphZBufferImage

#define NS_SetDeviceLostDeleteGraphFlag			SetDeviceLostDeleteGraphFlag

#define NS_GetGraphSize							GetGraphSize
#define NS_GetGraphSizeF						GetGraphSizeF
#define NS_GetGraphTextureSize					GetGraphTextureSize
#define NS_GetGraphUseBaseGraphArea				GetGraphUseBaseGraphArea
#define NS_GetGraphMipmapCount					GetGraphMipmapCount
#define NS_GetGraphFilePath						GetGraphFilePath
#define NS_CheckDrawValidGraph					CheckDrawValidGraph

#ifdef WINDOWS_DESKTOP_OS
#define NS_GetGraphID3D11Texture2D				GetGraphID3D11Texture2D
#define NS_GetGraphID3D11RenderTargetView		GetGraphID3D11RenderTargetView
#define NS_GetGraphID3D11DepthStencilView		GetGraphID3D11DepthStencilView
#endif // WINDOWS_DESKTOP_OS

#define NS_GetTexColorData						GetTexColorData
#define NS_GetTexColorData2						GetTexColorData2
#define NS_GetTexColorData3						GetTexColorData3
#define NS_GetMaxGraphTextureSize				GetMaxGraphTextureSize
#define NS_GetValidRestoreShredPoint			GetValidRestoreShredPoint
#define NS_GetCreateGraphColorData				GetCreateGraphColorData

// �p���b�g����֌W�֐�
#define NS_GetGraphPalette						GetGraphPalette
#define NS_GetGraphOriginalPalette				GetGraphOriginalPalette
#define NS_SetGraphPalette						SetGraphPalette
#define NS_ResetGraphPalette					ResetGraphPalette

// �}�`�`��֐�
#define NS_DrawLine										DrawLine
#define NS_DrawLineAA									DrawLineAA
#define NS_DrawBox										DrawBox
#define NS_DrawBoxAA									DrawBoxAA
#define NS_DrawFillBox									DrawFillBox
#define NS_DrawLineBox									DrawLineBox
#define NS_DrawCircle									DrawCircle
#define NS_DrawCircleAA									DrawCircleAA
#define NS_DrawOval										DrawOval
#define NS_DrawOvalAA									DrawOvalAA
#define NS_DrawOval_Rect								DrawOval_Rect
#define NS_DrawTriangle									DrawTriangle
#define NS_DrawTriangleAA								DrawTriangleAA
#define NS_DrawQuadrangle								DrawQuadrangle
#define NS_DrawQuadrangleAA								DrawQuadrangleAA
#define NS_DrawRoundRect								DrawRoundRect
#define NS_DrawRoundRectAA								DrawRoundRectAA
#define NS_BeginAADraw									BeginAADraw
#define NS_EndAADraw									EndAADraw
#define NS_DrawPixel									DrawPixel

#define NS_Paint										Paint

#define NS_DrawPixelSet									DrawPixelSet
#define NS_DrawLineSet									DrawLineSet
#define NS_DrawBoxSet									DrawBoxSet

#define NS_DrawPixel3D									DrawPixel3D
#define NS_DrawPixel3DD									DrawPixel3DD
#define NS_DrawLine3D									DrawLine3D
#define NS_DrawLine3DD									DrawLine3DD
#define NS_DrawTriangle3D								DrawTriangle3D
#define NS_DrawTriangle3DD								DrawTriangle3DD
#define NS_DrawCube3D									DrawCube3D
#define NS_DrawCube3DD									DrawCube3DD
#define NS_DrawCubeSet3D								DrawCubeSet3D
#define NS_DrawSphere3D									DrawSphere3D
#define NS_DrawSphere3DD								DrawSphere3DD
#define NS_DrawCapsule3D								DrawCapsule3D
#define NS_DrawCapsule3DD								DrawCapsule3DD
#define NS_DrawCone3D									DrawCone3D
#define NS_DrawCone3DD									DrawCone3DD

// �摜�`��֐�
#define NS_LoadGraphScreen								LoadGraphScreen
#define NS_LoadGraphScreenWithStrLen					LoadGraphScreenWithStrLen

#define NS_DrawGraph									DrawGraph
#define NS_DrawExtendGraph								DrawExtendGraph
#define NS_DrawRotaGraph								DrawRotaGraph
#define NS_DrawRotaGraph2								DrawRotaGraph2
#define NS_DrawRotaGraph3								DrawRotaGraph3
#define NS_DrawRotaGraphFast							DrawRotaGraphFast
#define NS_DrawRotaGraphFast2							DrawRotaGraphFast2
#define NS_DrawRotaGraphFast3							DrawRotaGraphFast3
#define NS_DrawModiGraph								DrawModiGraph
#define NS_DrawTurnGraph								DrawTurnGraph
#define NS_DrawReverseGraph								DrawReverseGraph

#define NS_DrawGraphF									DrawGraphF
#define NS_DrawExtendGraphF								DrawExtendGraphF
#define NS_DrawRotaGraphF								DrawRotaGraphF
#define NS_DrawRotaGraph2F								DrawRotaGraph2F
#define NS_DrawRotaGraph3F								DrawRotaGraph3F
#define NS_DrawRotaGraphFastF							DrawRotaGraphFastF
#define NS_DrawRotaGraphFast2F							DrawRotaGraphFast2F
#define NS_DrawRotaGraphFast3F							DrawRotaGraphFast3F
#define NS_DrawModiGraphF								DrawModiGraphF
#define NS_DrawTurnGraphF								DrawTurnGraphF
#define NS_DrawReverseGraphF							DrawReverseGraphF

#define NS_DrawChipMap									DrawChipMap
#define NS_DrawChipMap2									DrawChipMap2
#define NS_DrawTile										DrawTile

#define NS_DrawRectGraph								DrawRectGraph
#define NS_DrawRectExtendGraph							DrawRectExtendGraph
#define NS_DrawRectRotaGraph							DrawRectRotaGraph
#define NS_DrawRectRotaGraph2							DrawRectRotaGraph2
#define NS_DrawRectRotaGraph3							DrawRectRotaGraph3
#define NS_DrawRectRotaGraphFast						DrawRectRotaGraphFast
#define NS_DrawRectRotaGraphFast2						DrawRectRotaGraphFast2
#define NS_DrawRectRotaGraphFast3						DrawRectRotaGraphFast3
#define NS_DrawRectModiGraph							DrawRectModiGraph

#define NS_DrawRectGraphF								DrawRectGraphF
#define NS_DrawRectGraphF2								DrawRectGraphF2
#define NS_DrawRectExtendGraphF							DrawRectExtendGraphF
#define NS_DrawRectExtendGraphF2						DrawRectExtendGraphF2
#define NS_DrawRectRotaGraphF							DrawRectRotaGraphF
#define NS_DrawRectRotaGraph2F							DrawRectRotaGraph2F
#define NS_DrawRectRotaGraph3F							DrawRectRotaGraph3F
#define NS_DrawRectRotaGraphFastF						DrawRectRotaGraphFastF
#define NS_DrawRectRotaGraphFast2F						DrawRectRotaGraphFast2F
#define NS_DrawRectRotaGraphFast3F						DrawRectRotaGraphFast3F
#define NS_DrawRectModiGraphF							DrawRectModiGraphF

#define NS_DrawBlendGraph								DrawBlendGraph
#define NS_DrawBlendGraphF								DrawBlendGraphF
#define NS_DrawBlendGraphPos							DrawBlendGraphPos

#define NS_DrawCircleGauge								DrawCircleGauge
#define NS_DrawCircleGaugeF								DrawCircleGaugeF

#define NS_DrawGraphToZBuffer							DrawGraphToZBuffer
#define NS_DrawTurnGraphToZBuffer						DrawTurnGraphToZBuffer
#define NS_DrawReverseGraphToZBuffer					DrawReverseGraphToZBuffer
#define NS_DrawExtendGraphToZBuffer						DrawExtendGraphToZBuffer
#define NS_DrawRotaGraphToZBuffer						DrawRotaGraphToZBuffer
#define NS_DrawRotaGraph2ToZBuffer						DrawRotaGraph2ToZBuffer
#define NS_DrawRotaGraph3ToZBuffer						DrawRotaGraph3ToZBuffer
#define NS_DrawRotaGraphFastToZBuffer					DrawRotaGraphFastToZBuffer
#define NS_DrawRotaGraphFast2ToZBuffer					DrawRotaGraphFast2ToZBuffer
#define NS_DrawRotaGraphFast3ToZBuffer					DrawRotaGraphFast3ToZBuffer
#define NS_DrawModiGraphToZBuffer						DrawModiGraphToZBuffer
#define NS_DrawBoxToZBuffer								DrawBoxToZBuffer
#define NS_DrawCircleToZBuffer							DrawCircleToZBuffer
#define NS_DrawTriangleToZBuffer						DrawTriangleToZBuffer
#define NS_DrawQuadrangleToZBuffer						DrawQuadrangleToZBuffer
#define NS_DrawRoundRectToZBuffer						DrawRoundRectToZBuffer

#define NS_DrawPolygon									DrawPolygon
#define NS_DrawPolygon2D								DrawPolygon2D
#define NS_DrawPolygon3D								DrawPolygon3D
#define NS_DrawPolygonIndexed2D							DrawPolygonIndexed2D
#define NS_DrawPolygon32bitIndexed2D					DrawPolygon32bitIndexed2D
#define NS_DrawPolygonIndexed3D							DrawPolygonIndexed3D
#define NS_DrawPolygon32bitIndexed3D					DrawPolygon32bitIndexed3D
#define NS_DrawPolygonIndexed3DBase						DrawPolygonIndexed3DBase
#define NS_DrawPolygon32bitIndexed3DBase				DrawPolygon32bitIndexed3DBase
#define NS_DrawPolygon3DBase							DrawPolygon3DBase
#define NS_DrawPolygon3D2								DrawPolygon3D2

#define NS_DrawPolygonBase								DrawPolygonBase
#define NS_DrawPrimitive2D								DrawPrimitive2D
#define NS_DrawPrimitive3D								DrawPrimitive3D
#define NS_DrawPrimitiveIndexed2D						DrawPrimitiveIndexed2D
#define NS_DrawPrimitive32bitIndexed2D					DrawPrimitive32bitIndexed2D
#define NS_DrawPrimitiveIndexed3D						DrawPrimitiveIndexed3D
#define NS_DrawPrimitive32bitIndexed3D					DrawPrimitive32bitIndexed3D

#define NS_DrawPolygon3D_UseVertexBuffer				DrawPolygon3D_UseVertexBuffer
#define NS_DrawPrimitive3D_UseVertexBuffer				DrawPrimitive3D_UseVertexBuffer
#define NS_DrawPrimitive3D_UseVertexBuffer2				DrawPrimitive3D_UseVertexBuffer2
#define NS_DrawPolygonIndexed3D_UseVertexBuffer			DrawPolygonIndexed3D_UseVertexBuffer
#define NS_DrawPrimitiveIndexed3D_UseVertexBuffer		DrawPrimitiveIndexed3D_UseVertexBuffer
#define NS_DrawPrimitiveIndexed3D_UseVertexBuffer2		DrawPrimitiveIndexed3D_UseVertexBuffer2

#define NS_DrawGraph3D									DrawGraph3D
#define NS_DrawExtendGraph3D							DrawExtendGraph3D
#define NS_DrawRotaGraph3D								DrawRotaGraph3D
#define NS_DrawRota2Graph3D								DrawRota2Graph3D
#define NS_DrawModiBillboard3D							DrawModiBillboard3D
#define NS_DrawBillboard3D								DrawBillboard3D

// �`��ݒ�֌W�֐�
#define NS_SetDrawMode							SetDrawMode
#define NS_GetDrawMode							GetDrawMode
#define NS_SetDrawBlendMode						SetDrawBlendMode
#define NS_GetDrawBlendMode						GetDrawBlendMode
#define NS_SetDrawCustomBlendMode				SetDrawCustomBlendMode
#define NS_GetDrawCustomBlendMode				GetDrawCustomBlendMode
#define NS_SetDrawAlphaTest						SetDrawAlphaTest
#define NS_GetDrawAlphaTest						GetDrawAlphaTest
#define NS_SetBlendGraph						SetBlendGraph
#define NS_SetBlendGraphParam					SetBlendGraphParam
#define NS_SetBlendGraphPosition				SetBlendGraphPosition
#define NS_SetBlendGraphPositionMode			SetBlendGraphPositionMode
#define NS_SetDrawBright						SetDrawBright
#define NS_GetDrawBright						GetDrawBright
#define NS_SetDrawAddColor						SetDrawAddColor
#define NS_GetDrawAddColor						GetDrawAddColor
#define NS_SetWriteAlphaChannelFlag				SetWriteAlphaChannelFlag
#define NS_GetWriteAlphaChannelFlag				GetWriteAlphaChannelFlag
#define NS_CheckSeparateAlphaBlendEnable		CheckSeparateAlphaBlendEnable
#define NS_SetIgnoreDrawGraphColor				SetIgnoreDrawGraphColor
#define NS_GetIgnoreDrawGraphColor				GetIgnoreDrawGraphColor
#define NS_SetMaxAnisotropy						SetMaxAnisotropy
#define NS_GetMaxAnisotropy						GetMaxAnisotropy
#define NS_SetUseLarge3DPositionSupport			SetUseLarge3DPositionSupport

#define NS_SetUseZBufferFlag					SetUseZBufferFlag
#define NS_SetWriteZBufferFlag					SetWriteZBufferFlag
#define NS_SetZBufferCmpType					SetZBufferCmpType
#define NS_SetZBias								SetZBias
#define NS_SetUseZBuffer3D						SetUseZBuffer3D
#define NS_SetWriteZBuffer3D					SetWriteZBuffer3D
#define NS_SetZBufferCmpType3D					SetZBufferCmpType3D
#define NS_SetZBias3D							SetZBias3D
#define NS_SetDrawZ								SetDrawZ

#define NS_SetDrawArea							SetDrawArea
#define NS_GetDrawArea							GetDrawArea
#define NS_SetDraw3DScale						SetDraw3DScale
#define NS_SetDrawAreaFull						SetDrawAreaFull

#define NS_SetRestoreShredPoint					SetRestoreShredPoint
#define NS_SetRestoreGraphCallback				SetRestoreGraphCallback
#define NS_RunRestoreShred						RunRestoreShred
#define NS_SetGraphicsDeviceRestoreCallbackFunction		SetGraphicsDeviceRestoreCallbackFunction
#define NS_SetGraphicsDeviceLostCallbackFunction		SetGraphicsDeviceLostCallbackFunction

#define NS_SetTransformTo2D						SetTransformTo2D
#define NS_SetTransformTo2DD					SetTransformTo2DD
#define NS_ResetTransformTo2D					ResetTransformTo2D
#define NS_SetTransformToWorld					SetTransformToWorld
#define NS_SetTransformToWorldD					SetTransformToWorldD
#define NS_GetTransformToWorldMatrix			GetTransformToWorldMatrix
#define NS_GetTransformToWorldMatrixD			GetTransformToWorldMatrixD
#define NS_SetTransformToView					SetTransformToView
#define NS_SetTransformToViewD					SetTransformToViewD
#define NS_GetTransformToViewMatrix				GetTransformToViewMatrix
#define NS_GetTransformToViewMatrixD			GetTransformToViewMatrixD
#define NS_SetTransformToProjection				SetTransformToProjection
#define NS_SetTransformToProjectionD			SetTransformToProjectionD
#define NS_GetTransformToProjectionMatrix		GetTransformToProjectionMatrix
#define NS_GetTransformToProjectionMatrixD		GetTransformToProjectionMatrixD
#define NS_SetTransformToViewport				SetTransformToViewport
#define NS_SetTransformToViewportD				SetTransformToViewportD
#define NS_GetTransformToViewportMatrix			GetTransformToViewportMatrix
#define NS_GetTransformToViewportMatrixD		GetTransformToViewportMatrixD
#define NS_GetTransformToAPIViewportMatrix		GetTransformToAPIViewportMatrix
#define NS_GetTransformToAPIViewportMatrixD		GetTransformToAPIViewportMatrixD
#define NS_SetDefTransformMatrix				SetDefTransformMatrix
#define NS_SetDefTransformMatrixD				SetDefTransformMatrixD
#define NS_GetTransformPosition					GetTransformPosition
#define NS_GetTransformPositionD				GetTransformPositionD
#define NS_GetBillboardPixelSize				GetBillboardPixelSize
#define NS_GetBillboardPixelSizeD				GetBillboardPixelSizeD
#define	NS_ConvWorldPosToViewPos				ConvWorldPosToViewPos
#define	NS_ConvWorldPosToViewPosD				ConvWorldPosToViewPosD
#define NS_ConvWorldPosToScreenPos				ConvWorldPosToScreenPos
#define NS_ConvWorldPosToScreenPosD				ConvWorldPosToScreenPosD
#define NS_ConvWorldPosToScreenPosPlusW			ConvWorldPosToScreenPosPlusW
#define NS_ConvWorldPosToScreenPosPlusWD		ConvWorldPosToScreenPosPlusWD
#define NS_ConvScreenPosToWorldPos				ConvScreenPosToWorldPos
#define NS_ConvScreenPosToWorldPosD				ConvScreenPosToWorldPosD
#define NS_ConvScreenPosToWorldPos_ZLinear		ConvScreenPosToWorldPos_ZLinear
#define NS_ConvScreenPosToWorldPos_ZLinearD		ConvScreenPosToWorldPos_ZLinearD

#define NS_SetUseCullingFlag					SetUseCullingFlag
#define NS_SetUseBackCulling					SetUseBackCulling
#define NS_GetUseBackCulling					GetUseBackCulling
#define NS_SetUseRightHandClippingProcess		SetUseRightHandClippingProcess
#define NS_GetUseRightHandClippingProcess		GetUseRightHandClippingProcess

#define NS_SetTextureAddressMode				SetTextureAddressMode
#define NS_SetTextureAddressModeUV				SetTextureAddressModeUV
#define NS_SetTextureAddressTransform			SetTextureAddressTransform
#define NS_SetTextureAddressTransformMatrix		SetTextureAddressTransformMatrix
#define NS_ResetTextureAddressTransform			ResetTextureAddressTransform

#define NS_SetFogEnable							SetFogEnable
#define NS_GetFogEnable							GetFogEnable
#define NS_SetFogMode							SetFogMode
#define NS_GetFogMode							GetFogMode
#define NS_SetFogColor							SetFogColor
#define NS_GetFogColor							GetFogColor
#define NS_SetFogStartEnd						SetFogStartEnd
#define NS_GetFogStartEnd						GetFogStartEnd
#define NS_SetFogDensity						SetFogDensity
#define NS_GetFogDensity						GetFogDensity

// ��ʊ֌W�֐�
#define NS_GetPixel								GetPixel
#define NS_GetPixelDX							GetPixelDX
#define NS_GetPixelF							GetPixelF
#define NS_SetBackgroundColor					SetBackgroundColor
#define NS_GetBackgroundColor					GetBackgroundColor
#define NS_GetDrawScreenGraph					GetDrawScreenGraph
#define NS_BltDrawValidGraph					BltDrawValidGraph
#define NS_ScreenFlip							ScreenFlip
#define NS_ScreenCopy							ScreenCopy
#define NS_WaitVSync							WaitVSync
#define NS_ClearDrawScreen						ClearDrawScreen
#define NS_ClearDrawScreenZBuffer				ClearDrawScreenZBuffer
#define NS_ClsDrawScreen						ClsDrawScreen
#define NS_SetDrawScreen						SetDrawScreen
#define NS_GetDrawScreen						GetDrawScreen
#define NS_GetActiveGraph						GetActiveGraph
#define NS_SetUseSetDrawScreenSettingReset		SetUseSetDrawScreenSettingReset
#define NS_GetUseSetDrawScreenSettingReset		GetUseSetDrawScreenSettingReset
#define NS_SetDrawZBuffer						SetDrawZBuffer
#ifdef WINDOWS_DESKTOP_OS
#define NS_BltBackScreenToWindow				BltBackScreenToWindow
#define NS_BltRectBackScreenToWindow			BltRectBackScreenToWindow
#define NS_SetScreenFlipTargetWindow			SetScreenFlipTargetWindow
#define NS_GetDesktopScreenGraph				GetDesktopScreenGraph
#define NS_GetDesktopScreenGraphMemImage		GetDesktopScreenGraphMemImage
#define NS_GetOtherWindowGraph					GetOtherWindowGraph
#endif // WINDOWS_DESKTOP_OS
#define NS_SetGraphMode							SetGraphMode
#define NS_SetUserScreenImage					SetUserScreenImage
#define NS_SetFullScreenResolutionMode			SetFullScreenResolutionMode
#define NS_GetFullScreenResolutionMode			GetFullScreenResolutionMode
#define NS_GetUseFullScreenResolutionMode		GetUseFullScreenResolutionMode
#define NS_SetFullScreenScalingMode				SetFullScreenScalingMode
#define NS_SetEmulation320x240					SetEmulation320x240
#define NS_SetZBufferSize						SetZBufferSize
#define NS_SetZBufferBitDepth					SetZBufferBitDepth
#define NS_SetWaitVSyncFlag						SetWaitVSyncFlag
#define NS_GetWaitVSyncFlag						GetWaitVSyncFlag
#define NS_SetFullSceneAntiAliasingMode			SetFullSceneAntiAliasingMode
#define NS_SetGraphDisplayArea					SetGraphDisplayArea
#define NS_SetChangeScreenModeGraphicsSystemResetFlag	SetChangeScreenModeGraphicsSystemResetFlag
#define NS_GetScreenState						GetScreenState
#define NS_GetDrawScreenSize					GetDrawScreenSize
#define NS_GetScreenBitDepth					GetScreenBitDepth
#define NS_GetColorBitDepth						GetColorBitDepth
#define NS_GetChangeDisplayFlag					GetChangeDisplayFlag
#define NS_GetVideoMemorySize					GetVideoMemorySize
#define NS_GetVideoMemorySizeEx					GetVideoMemorySizeEx
#define NS_GetRefreshRate						GetRefreshRate
#define NS_GetDisplayNum						GetDisplayNum
#define NS_GetDisplayInfo						GetDisplayInfo
#define NS_GetDisplayModeNum					GetDisplayModeNum
#define NS_GetDisplayMode						GetDisplayMode
#define NS_GetFullScreenUseDisplayMode			GetFullScreenUseDisplayMode
#define NS_GetDisplayMaxResolution				GetDisplayMaxResolution
#define NS_GetDispColorData						GetDispColorData
#define NS_GetMultiDrawScreenNum				GetMultiDrawScreenNum
#define NS_GetDrawFloatCoordType				GetDrawFloatCoordType

// ���̑��ݒ�֌W�֐�
#define NS_SetUseNormalDrawShader				SetUseNormalDrawShader
#define NS_SetUseSoftwareRenderModeFlag			SetUseSoftwareRenderModeFlag
#define NS_SetNotUse3DFlag						SetNotUse3DFlag
#define NS_SetUse3DFlag							SetUse3DFlag
#define NS_GetUse3DFlag							GetUse3DFlag
#define NS_SetScreenMemToVramFlag				SetScreenMemToVramFlag
#define NS_GetScreenMemToSystemMemFlag			GetScreenMemToSystemMemFlag

#define NS_SetUseBasicGraphDraw3DDeviceMethodFlag	SetUseBasicGraphDraw3DDeviceMethodFlag
#define NS_SetUseDisplayIndex					SetUseDisplayIndex

#define NS_SetWindowDrawRect					SetWindowDrawRect
#define NS_RestoreGraphSystem					RestoreGraphSystem
#define NS_SetUseHardwareVertexProcessing		SetUseHardwareVertexProcessing
#define NS_SetUsePixelLighting					SetUsePixelLighting
#define NS_SetUseOldDrawModiGraphCodeFlag		SetUseOldDrawModiGraphCodeFlag
#define NS_SetUseVramFlag						SetUseVramFlag
#define NS_GetUseVramFlag						GetUseVramFlag
#define NS_SetBasicBlendFlag					SetBasicBlendFlag
#ifdef WINDOWS_DESKTOP_OS
#define NS_SetMultiThreadFlag					SetMultiThreadFlag
#define NS_SetUseDirectDrawDeviceIndex			SetUseDirectDrawDeviceIndex
#define NS_SetAeroDisableFlag					SetAeroDisableFlag
#define NS_SetUseDirect3D9Ex					SetUseDirect3D9Ex
#define NS_SetUseDirect3D11						SetUseDirect3D11
#define NS_SetUseDirect3D11MinFeatureLevel		SetUseDirect3D11MinFeatureLevel
#define NS_SetUseDirect3D11WARPDriver			SetUseDirect3D11WARPDriver
#define NS_SetUseDirect3DVersion				SetUseDirect3DVersion
#define NS_GetUseDirect3DVersion				GetUseDirect3DVersion
#define NS_GetUseDirect3D11FeatureLevel			GetUseDirect3D11FeatureLevel
#define NS_SetUseDirect3D11AdapterIndex			SetUseDirect3D11AdapterIndex
#define NS_SetUseDirect3D11BGRASupport			SetUseDirect3D11BGRASupport
#define NS_GetUseDirect3D11BGRASupport			GetUseDirect3D11BGRASupport
#define NS_SetUseDirect3D11AdapterLUID			SetUseDirect3D11AdapterLUID
#define NS_GetUseDirect3D11AdapterLUID			GetUseDirect3D11AdapterLUID
#define NS_SetUseDirectDrawFlag					SetUseDirectDrawFlag
#define NS_SetUseGDIFlag						SetUseGDIFlag
#define NS_GetUseGDIFlag						GetUseGDIFlag
#define NS_SetDDrawUseGuid						SetDDrawUseGuid
#define NS_GetUseDDrawObj						GetUseDDrawObj
#define NS_GetDirectDrawDeviceGUID				GetDirectDrawDeviceGUID
#define NS_GetDirectDrawDeviceDescription		GetDirectDrawDeviceDescription
#define NS_GetDirectDrawDeviceNum				GetDirectDrawDeviceNum
#define NS_GetUseDirect3DDevice9				GetUseDirect3DDevice9
#define NS_GetUseDirect3D9BackBufferSurface		GetUseDirect3D9BackBufferSurface
#define NS_GetUseDirect3D11Device						GetUseDirect3D11Device
#define NS_GetUseDirect3D11DeviceContext				GetUseDirect3D11DeviceContext
#define NS_GetUseDirect3D11BackBufferTexture2D			GetUseDirect3D11BackBufferTexture2D
#define NS_GetUseDirect3D11BackBufferRenderTargetView	GetUseDirect3D11BackBufferRenderTargetView
#define NS_GetUseDirect3D11DepthStencilTexture2D		GetUseDirect3D11DepthStencilTexture2D
#define NS_SetDrawScreen_ID3D11RenderTargetView	SetDrawScreen_ID3D11RenderTargetView
#define NS_RefreshDxLibDirect3DSetting			RefreshDxLibDirect3DSetting
#ifndef DX_NON_MEDIA_FOUNDATION
#define NS_SetUseMediaFoundationFlag			SetUseMediaFoundationFlag
#endif // DX_NON_MEDIA_FOUNDATION
#endif // WINDOWS_DESKTOP_OS
#define NS_RenderVertex							RenderVertex
#define NS_GetDrawCallCount						GetDrawCallCount
#define NS_GetFPS								GetFPS

#ifndef DX_NON_SAVEFUNCTION

// ��ʉ摜�ۑ��֐�
// Jpeg_Quality         = 0:��掿�`100:���掿
// Png_CompressionLevel = 0:�����k�`  9:�ō����k
#define NS_SaveDrawScreen						SaveDrawScreen
#define NS_SaveDrawScreenWithStrLen				SaveDrawScreenWithStrLen
#define NS_SaveDrawScreenToBMP					SaveDrawScreenToBMP
#define NS_SaveDrawScreenToBMPWithStrLen		SaveDrawScreenToBMPWithStrLen
#define NS_SaveDrawScreenToDDS					SaveDrawScreenToDDS
#define NS_SaveDrawScreenToDDSWithStrLen		SaveDrawScreenToDDSWithStrLen
#define NS_SaveDrawScreenToJPEG					SaveDrawScreenToJPEG
#define NS_SaveDrawScreenToJPEGWithStrLen		SaveDrawScreenToJPEGWithStrLen
#define NS_SaveDrawScreenToPNG					SaveDrawScreenToPNG
#define NS_SaveDrawScreenToPNGWithStrLen		SaveDrawScreenToPNGWithStrLen

// �`��Ώۂɂł���O���t�B�b�N�n���h���ۑ��֐�
// Jpeg_Quality         = 0:��掿�`100:���掿
// Png_CompressionLevel = 0:�����k�`  9:�ō����k
#define NS_SaveDrawValidGraph					SaveDrawValidGraph
#define NS_SaveDrawValidGraphWithStrLen			SaveDrawValidGraphWithStrLen
#define NS_SaveDrawValidGraphToBMP				SaveDrawValidGraphToBMP
#define NS_SaveDrawValidGraphToBMPWithStrLen	SaveDrawValidGraphToBMPWithStrLen
#define NS_SaveDrawValidGraphToDDS				SaveDrawValidGraphToDDS
#define NS_SaveDrawValidGraphToDDSWithStrLen	SaveDrawValidGraphToDDSWithStrLen
#define NS_SaveDrawValidGraphToJPEG				SaveDrawValidGraphToJPEG
#define NS_SaveDrawValidGraphToJPEGWithStrLen	SaveDrawValidGraphToJPEGWithStrLen
#define NS_SaveDrawValidGraphToPNG				SaveDrawValidGraphToPNG
#define NS_SaveDrawValidGraphToPNGWithStrLen	SaveDrawValidGraphToPNGWithStrLen

#endif // DX_NON_SAVEFUNCTION

// ���_�o�b�t�@�֌W�֐�
#define NS_CreateVertexBuffer					CreateVertexBuffer
#define NS_DeleteVertexBuffer					DeleteVertexBuffer
#define NS_InitVertexBuffer						InitVertexBuffer
#define NS_SetVertexBufferData					SetVertexBufferData
#define NS_GetBufferVertexBuffer				GetBufferVertexBuffer
#define NS_UpdateVertexBuffer					UpdateVertexBuffer
#define NS_CreateIndexBuffer					CreateIndexBuffer
#define NS_DeleteIndexBuffer					DeleteIndexBuffer
#define NS_InitIndexBuffer						InitIndexBuffer
#define NS_SetIndexBufferData					SetIndexBufferData
#define NS_GetBufferIndexBuffer					GetBufferIndexBuffer
#define NS_UpdateIndexBuffer					UpdateIndexBuffer
#define NS_GetMaxPrimitiveCount					GetMaxPrimitiveCount
#define NS_GetMaxVertexIndex					GetMaxVertexIndex

// �V�F�[�_�[�֌W�֐�
#define NS_GetValidShaderVersion				GetValidShaderVersion

#define NS_LoadVertexShader						LoadVertexShader
#define NS_LoadVertexShaderWithStrLen			LoadVertexShaderWithStrLen
#define NS_LoadPixelShader						LoadPixelShader
#define NS_LoadGeometryShader					LoadGeometryShader
#define NS_LoadGeometryShaderWithStrLen			LoadGeometryShaderWithStrLen
#define NS_LoadPixelShaderWithStrLen			LoadPixelShaderWithStrLen
#define NS_LoadVertexShaderFromMem				LoadVertexShaderFromMem
#define NS_LoadGeometryShaderFromMem			LoadGeometryShaderFromMem
#define NS_LoadPixelShaderFromMem				LoadPixelShaderFromMem
#define NS_DeleteShader							DeleteShader
#define NS_InitShader							InitShader

#define NS_GetConstIndexToShader				GetConstIndexToShader
#define NS_GetConstIndexToShaderWithStrLen		GetConstIndexToShaderWithStrLen
#define NS_GetConstCountToShader				GetConstCountToShader
#define NS_GetConstCountToShaderWithStrLen		GetConstCountToShaderWithStrLen
#define NS_GetConstDefaultParamFToShader		GetConstDefaultParamFToShader
#define NS_GetConstDefaultParamFToShaderWithStrLen GetConstDefaultParamFToShaderWithStrLen
#define NS_SetVSConstSF							SetVSConstSF
#define NS_SetVSConstF							SetVSConstF
#define NS_SetVSConstFMtx						SetVSConstFMtx
#define NS_SetVSConstFMtxT						SetVSConstFMtxT
#define NS_SetVSConstSI							SetVSConstSI
#define NS_SetVSConstI							SetVSConstI
#define NS_SetVSConstB							SetVSConstB
#define NS_SetVSConstSFArray					SetVSConstSFArray
#define NS_SetVSConstFArray						SetVSConstFArray
#define NS_SetVSConstFMtxArray					SetVSConstFMtxArray
#define NS_SetVSConstFMtxTArray					SetVSConstFMtxTArray
#define NS_SetVSConstSIArray					SetVSConstSIArray
#define NS_SetVSConstIArray						SetVSConstIArray
#define NS_SetVSConstBArray						SetVSConstBArray
#define NS_ResetVSConstF						ResetVSConstF
#define NS_ResetVSConstI						ResetVSConstI
#define NS_ResetVSConstB						ResetVSConstB

#define NS_SetPSConstSF							SetPSConstSF
#define NS_SetPSConstF							SetPSConstF
#define NS_SetPSConstFMtx						SetPSConstFMtx
#define NS_SetPSConstFMtxT						SetPSConstFMtxT
#define NS_SetPSConstSI							SetPSConstSI
#define NS_SetPSConstI							SetPSConstI
#define NS_SetPSConstB							SetPSConstB
#define NS_SetPSConstSFArray					SetPSConstSFArray
#define NS_SetPSConstFArray						SetPSConstFArray
#define NS_SetPSConstFMtxArray					SetPSConstFMtxArray
#define NS_SetPSConstFMtxTArray					SetPSConstFMtxTArray
#define NS_SetPSConstSIArray					SetPSConstSIArray
#define NS_SetPSConstIArray						SetPSConstIArray
#define NS_SetPSConstBArray						SetPSConstBArray
#define NS_ResetPSConstF						ResetPSConstF
#define NS_ResetPSConstI						ResetPSConstI
#define NS_ResetPSConstB						ResetPSConstB

#define NS_SetRenderTargetToShader				SetRenderTargetToShader
#define NS_SetUseTextureToShader				SetUseTextureToShader
#define NS_SetUseVertexShader					SetUseVertexShader
#define NS_SetUseGeometryShader					SetUseGeometryShader
#define NS_SetUsePixelShader					SetUsePixelShader

#define NS_CalcPolygonBinormalAndTangentsToShader				CalcPolygonBinormalAndTangentsToShader
#define NS_CalcPolygonIndexedBinormalAndTangentsToShader		CalcPolygonIndexedBinormalAndTangentsToShader
#define NS_CalcPolygon32bitIndexedBinormalAndTangentsToShader	CalcPolygon32bitIndexedBinormalAndTangentsToShader

#define NS_DrawBillboard3DToShader								DrawBillboard3DToShader
#define NS_DrawPolygon2DToShader								DrawPolygon2DToShader
#define NS_DrawPolygon3DToShader								DrawPolygon3DToShader
#define NS_DrawPolygonIndexed2DToShader							DrawPolygonIndexed2DToShader
#define NS_DrawPolygon32bitIndexed2DToShader					DrawPolygon32bitIndexed2DToShader
#define NS_DrawPolygonIndexed3DToShader							DrawPolygonIndexed3DToShader
#define NS_DrawPolygon32bitIndexed3DToShader					DrawPolygon32bitIndexed3DToShader
#define NS_DrawPrimitive2DToShader								DrawPrimitive2DToShader
#define NS_DrawPrimitive3DToShader								DrawPrimitive3DToShader
#define NS_DrawPrimitiveIndexed2DToShader						DrawPrimitiveIndexed2DToShader
#define NS_DrawPrimitive32bitIndexed2DToShader					DrawPrimitive32bitIndexed2DToShader
#define NS_DrawPrimitiveIndexed3DToShader						DrawPrimitiveIndexed3DToShader
#define NS_DrawPrimitive32bitIndexed3DToShader					DrawPrimitive32bitIndexed3DToShader
#define NS_DrawPolygon3DToShader_UseVertexBuffer				DrawPolygon3DToShader_UseVertexBuffer
#define NS_DrawPolygonIndexed3DToShader_UseVertexBuffer			DrawPolygonIndexed3DToShader_UseVertexBuffer
#define NS_DrawPrimitive3DToShader_UseVertexBuffer				DrawPrimitive3DToShader_UseVertexBuffer
#define NS_DrawPrimitive3DToShader_UseVertexBuffer2				DrawPrimitive3DToShader_UseVertexBuffer2
#define NS_DrawPrimitiveIndexed3DToShader_UseVertexBuffer		DrawPrimitiveIndexed3DToShader_UseVertexBuffer
#define NS_DrawPrimitiveIndexed3DToShader_UseVertexBuffer2		DrawPrimitiveIndexed3DToShader_UseVertexBuffer2

// �V�F�[�_�[�p�萔�o�b�t�@�֌W�֐�
#define NS_InitShaderConstantBuffer						InitShaderConstantBuffer
#define NS_CreateShaderConstantBuffer					CreateShaderConstantBuffer
#define NS_DeleteShaderConstantBuffer					DeleteShaderConstantBuffer
#define NS_GetBufferShaderConstantBuffer				GetBufferShaderConstantBuffer
#define NS_UpdateShaderConstantBuffer					UpdateShaderConstantBuffer
#define NS_SetShaderConstantBuffer						SetShaderConstantBuffer

// �t�B���^�[�֌W�֐�
#ifndef DX_NON_FILTER

#define NS_SetGraphFilterBltBlendMode			SetGraphFilterBltBlendMode
#define NS_SetGraphBlendScalingFilterMode		SetGraphBlendScalingFilterMode
#define NS_GraphFilter							GraphFilter
#define NS_GraphFilterBlt						GraphFilterBlt
#define NS_GraphFilterRectBlt					GraphFilterRectBlt
#define NS_GraphBlend							GraphBlend
#define NS_GraphBlendBlt						GraphBlendBlt
#define NS_GraphBlendRectBlt					GraphBlendRectBlt
#define NS_GraphBlendRectBlt2					GraphBlendRectBlt2

#endif // DX_NON_FILTER


#ifndef DX_NON_MOVIE

// ���[�r�[�O���t�B�b�N�֌W�֐�
#define NS_PlayMovie							PlayMovie
#define NS_PlayMovieWithStrLen					PlayMovieWithStrLen
#define NS_GetMovieImageSize_File				GetMovieImageSize_File
#define NS_GetMovieImageSize_File_WithStrLen	GetMovieImageSize_File_WithStrLen
#define NS_GetMovieImageSize_Mem				GetMovieImageSize_Mem
#define NS_OpenMovieToGraph						OpenMovieToGraph
#define NS_OpenMovieToGraphWithStrLen			OpenMovieToGraphWithStrLen
#define NS_PlayMovieToGraph						PlayMovieToGraph
#define NS_PauseMovieToGraph					PauseMovieToGraph
#define NS_AddMovieFrameToGraph					AddMovieFrameToGraph
#define NS_SeekMovieToGraph						SeekMovieToGraph
#define NS_SetPlaySpeedRateMovieToGraph			SetPlaySpeedRateMovieToGraph
#define NS_GetMovieStateToGraph					GetMovieStateToGraph
#define NS_SetMovieVolumeToGraph				SetMovieVolumeToGraph
#define NS_GetMovieVolumeToGraph				GetMovieVolumeToGraph
#define NS_ChangeMovieVolumeToGraph				ChangeMovieVolumeToGraph
#define NS_GetMovieVolumeToGraph2				GetMovieVolumeToGraph2
#define NS_GetMovieBaseImageToGraph				GetMovieBaseImageToGraph
#define NS_GetMovieTotalFrameToGraph			GetMovieTotalFrameToGraph
#define NS_TellMovieToGraph						TellMovieToGraph
#define NS_TellMovieToGraphToFrame				TellMovieToGraphToFrame
#define NS_SeekMovieToGraphToFrame				SeekMovieToGraphToFrame
#define NS_GetOneFrameTimeMovieToGraph			GetOneFrameTimeMovieToGraph
#define NS_GetLastUpdateTimeMovieToGraph		GetLastUpdateTimeMovieToGraph
#define NS_UpdateMovieToGraph					UpdateMovieToGraph
#define NS_SetMovieRightImageAlphaFlag			SetMovieRightImageAlphaFlag
#define NS_SetMovieColorA8R8G8B8Flag			SetMovieColorA8R8G8B8Flag
#define NS_SetMovieUseYUVFormatSurfaceFlag		SetMovieUseYUVFormatSurfaceFlag

#endif

// �J�����֌W�֐�
#define NS_SetCameraNearFar						SetCameraNearFar
#define NS_SetCameraNearFarD					SetCameraNearFarD
#define NS_SetCameraPositionAndTarget_UpVecY	SetCameraPositionAndTarget_UpVecY
#define NS_SetCameraPositionAndTarget_UpVecYD	SetCameraPositionAndTarget_UpVecYD
#define NS_SetCameraPositionAndTargetAndUpVec	SetCameraPositionAndTargetAndUpVec
#define NS_SetCameraPositionAndTargetAndUpVecD	SetCameraPositionAndTargetAndUpVecD
#define NS_SetCameraPositionAndAngle			SetCameraPositionAndAngle
#define NS_SetCameraPositionAndAngleD			SetCameraPositionAndAngleD
#define NS_SetCameraViewMatrix					SetCameraViewMatrix
#define NS_SetCameraViewMatrixD					SetCameraViewMatrixD
#define NS_SetCameraScreenCenter				SetCameraScreenCenter
#define NS_SetCameraScreenCenterD				SetCameraScreenCenterD

#define NS_SetupCamera_Perspective				SetupCamera_Perspective
#define NS_SetupCamera_PerspectiveD				SetupCamera_PerspectiveD
#define NS_SetupCamera_Ortho					SetupCamera_Ortho
#define NS_SetupCamera_OrthoD					SetupCamera_OrthoD
#define NS_SetupCamera_ProjectionMatrix			SetupCamera_ProjectionMatrix
#define NS_SetupCamera_ProjectionMatrixD		SetupCamera_ProjectionMatrixD
#define NS_SetCameraDotAspect					SetCameraDotAspect
#define NS_SetCameraDotAspectD					SetCameraDotAspectD

#define NS_CheckCameraViewClip					CheckCameraViewClip
#define NS_CheckCameraViewClipD					CheckCameraViewClipD
#define NS_CheckCameraViewClip_Dir				CheckCameraViewClip_Dir
#define NS_CheckCameraViewClip_DirD				CheckCameraViewClip_DirD
#define NS_CheckCameraViewClip_Box				CheckCameraViewClip_Box
#define NS_CheckCameraViewClip_BoxD				CheckCameraViewClip_BoxD

#define NS_GetCameraNear						GetCameraNear
#define NS_GetCameraNearD						GetCameraNearD
#define NS_GetCameraFar							GetCameraFar
#define NS_GetCameraFarD						GetCameraFarD

#define NS_GetCameraPosition					GetCameraPosition
#define NS_GetCameraPositionD					GetCameraPositionD
#define NS_GetCameraTarget						GetCameraTarget
#define NS_GetCameraTargetD						GetCameraTargetD
#define NS_GetCameraUpVector					GetCameraUpVector
#define NS_GetCameraUpVectorD					GetCameraUpVectorD
#define NS_GetCameraDownVector					GetCameraDownVector
#define NS_GetCameraDownVectorD					GetCameraDownVectorD
#define NS_GetCameraRightVector					GetCameraRightVector
#define NS_GetCameraRightVectorD				GetCameraRightVectorD
#define NS_GetCameraLeftVector					GetCameraLeftVector
#define NS_GetCameraLeftVectorD					GetCameraLeftVectorD
#define NS_GetCameraFrontVector					GetCameraFrontVector
#define NS_GetCameraFrontVectorD				GetCameraFrontVectorD
#define NS_GetCameraBackVector					GetCameraBackVector
#define NS_GetCameraBackVectorD					GetCameraBackVectorD
#define NS_GetCameraAngleHRotate				GetCameraAngleHRotate
#define NS_GetCameraAngleHRotateD				GetCameraAngleHRotateD
#define NS_GetCameraAngleVRotate				GetCameraAngleVRotate
#define NS_GetCameraAngleVRotateD				GetCameraAngleVRotateD
#define NS_GetCameraAngleTRotate				GetCameraAngleTRotate
#define NS_GetCameraAngleTRotateD				GetCameraAngleTRotateD

#define NS_GetCameraViewMatrix					GetCameraViewMatrix
#define NS_GetCameraViewMatrixD					GetCameraViewMatrixD
#define NS_GetCameraBillboardMatrix				GetCameraBillboardMatrix
#define NS_GetCameraBillboardMatrixD			GetCameraBillboardMatrixD
#define NS_GetCameraScreenCenter				GetCameraScreenCenter
#define NS_GetCameraScreenCenterD				GetCameraScreenCenterD
#define NS_GetCameraFov							GetCameraFov
#define NS_GetCameraFovD						GetCameraFovD
#define NS_GetCameraSize						GetCameraSize
#define NS_GetCameraSizeD						GetCameraSizeD
#define NS_GetCameraProjectionMatrix			GetCameraProjectionMatrix
#define NS_GetCameraProjectionMatrixD			GetCameraProjectionMatrixD
#define NS_GetCameraDotAspect					GetCameraDotAspect
#define NS_GetCameraDotAspectD					GetCameraDotAspectD
#define NS_GetCameraViewportMatrix				GetCameraViewportMatrix
#define NS_GetCameraViewportMatrixD				GetCameraViewportMatrixD
#define NS_GetCameraAPIViewportMatrix			GetCameraAPIViewportMatrix
#define NS_GetCameraAPIViewportMatrixD			GetCameraAPIViewportMatrixD

// ���C�g�֌W�֐�
#define NS_SetUseLighting						SetUseLighting
#define NS_SetMaterialUseVertDifColor			SetMaterialUseVertDifColor
#define NS_SetMaterialUseVertSpcColor			SetMaterialUseVertSpcColor
#define NS_SetMaterialParam						SetMaterialParam
#define NS_SetUseSpecular						SetUseSpecular
#define NS_SetGlobalAmbientLight				SetGlobalAmbientLight
#define NS_SetUseLightAngleAttenuation			SetUseLightAngleAttenuation

#define NS_ChangeLightTypeDir					ChangeLightTypeDir
#define NS_ChangeLightTypeSpot					ChangeLightTypeSpot
#define NS_ChangeLightTypePoint					ChangeLightTypePoint
#define NS_SetLightEnable						SetLightEnable
#define NS_SetLightDifColor						SetLightDifColor
#define NS_SetLightSpcColor						SetLightSpcColor
#define NS_SetLightAmbColor						SetLightAmbColor
#define NS_SetLightDirection					SetLightDirection
#define NS_SetLightPosition						SetLightPosition
#define NS_SetLightRangeAtten					SetLightRangeAtten
#define NS_SetLightAngle						SetLightAngle
#define NS_GetLightType							GetLightType
#define NS_GetLightEnable						GetLightEnable
#define NS_GetLightDifColor						GetLightDifColor
#define NS_GetLightSpcColor						GetLightSpcColor
#define NS_GetLightAmbColor						GetLightAmbColor
#define NS_GetLightDirection					GetLightDirection
#define NS_GetLightPosition						GetLightPosition
#define NS_GetLightRangeAtten					GetLightRangeAtten
#define NS_GetLightAngle						GetLightAngle
#define NS_SetLightUseShadowMap					SetLightUseShadowMap

#define NS_CreateDirLightHandle					CreateDirLightHandle
#define NS_CreateSpotLightHandle				CreateSpotLightHandle
#define NS_CreatePointLightHandle				CreatePointLightHandle
#define NS_DeleteLightHandle					DeleteLightHandle
#define NS_DeleteLightHandleAll					DeleteLightHandleAll
#define NS_SetLightTypeHandle					SetLightTypeHandle
#define NS_SetLightEnableHandle					SetLightEnableHandle
#define NS_SetLightDifColorHandle				SetLightDifColorHandle
#define NS_SetLightSpcColorHandle				SetLightSpcColorHandle
#define NS_SetLightAmbColorHandle				SetLightAmbColorHandle
#define NS_SetLightDirectionHandle				SetLightDirectionHandle
#define NS_SetLightPositionHandle				SetLightPositionHandle
#define NS_SetLightRangeAttenHandle				SetLightRangeAttenHandle
#define NS_SetLightAngleHandle					SetLightAngleHandle
#define NS_SetLightUseShadowMapHandle			SetLightUseShadowMapHandle
#define NS_GetLightTypeHandle					GetLightTypeHandle
#define NS_GetLightEnableHandle					GetLightEnableHandle
#define NS_GetLightDifColorHandle				GetLightDifColorHandle
#define NS_GetLightSpcColorHandle				GetLightSpcColorHandle
#define NS_GetLightAmbColorHandle				GetLightAmbColorHandle
#define NS_GetLightDirectionHandle				GetLightDirectionHandle
#define NS_GetLightPositionHandle				GetLightPositionHandle
#define NS_GetLightRangeAttenHandle				GetLightRangeAttenHandle
#define NS_GetLightAngleHandle					GetLightAngleHandle

#define NS_GetEnableLightHandleNum				GetEnableLightHandleNum
#define NS_GetEnableLightHandle					GetEnableLightHandle

// �F���擾�p�֐�
#define NS_GetTexFormatIndex					GetTexFormatIndex
#define NS_ColorKaiseki							ColorKaiseki


















// DxMask.cpp �֐��v���g�^�C�v�錾

#ifndef DX_NON_MASK

// �}�X�N�֌W 
#define NS_CreateMaskScreen						CreateMaskScreen
#define NS_DeleteMaskScreen						DeleteMaskScreen
#define NS_DrawMaskToDirectData					DrawMaskToDirectData
#define NS_DrawFillMaskToDirectData				DrawFillMaskToDirectData

#define NS_SetUseMaskScreenFlag					SetUseMaskScreenFlag
#define NS_GetUseMaskScreenFlag					GetUseMaskScreenFlag
#define NS_FillMaskScreen						FillMaskScreen
#define NS_SetMaskScreenGraph					SetMaskScreenGraph
#define NS_SetMaskScreenGraphUseChannel			SetMaskScreenGraphUseChannel

#define NS_InitMask								InitMask
#define NS_MakeMask								MakeMask
#define NS_GetMaskSize							GetMaskSize
#define NS_GetMaskBaseImageInfo					GetMaskBaseImageInfo
#define NS_SetDataToMask						SetDataToMask
#define NS_DeleteMask							DeleteMask
#define NS_BmpBltToMask							BmpBltToMask
#define NS_GraphImageBltToMask					GraphImageBltToMask
#define NS_LoadMask								LoadMask
#define NS_LoadMaskWithStrLen					LoadMaskWithStrLen
#define NS_LoadDivMask							LoadDivMask
#define NS_LoadDivMaskWithStrLen				LoadDivMaskWithStrLen
#define NS_CreateMaskFromMem					CreateMaskFromMem
#define NS_CreateDivMaskFromMem					CreateDivMaskFromMem
#define NS_DrawMask								DrawMask
#ifndef DX_NON_FONT
#define NS_DrawFormatStringMask					DrawFormatStringMask
#define NS_DrawFormatStringMaskToHandle			DrawFormatStringMaskToHandle
#define NS_DrawStringMask						DrawStringMask
#define NS_DrawNStringMask						DrawNStringMask
#define NS_DrawStringMaskToHandle				DrawStringMaskToHandle
#define NS_DrawNStringMaskToHandle				DrawNStringMaskToHandle
#endif // DX_NON_FONT
#define NS_DrawFillMask							DrawFillMask
#define NS_SetMaskReverseEffectFlag				SetMaskReverseEffectFlag

#define NS_GetMaskScreenData					GetMaskScreenData
#define NS_GetMaskUseFlag						GetMaskUseFlag

#endif // DX_NON_MASK

#endif // DX_NOTUSE_DRAWFUNCTION












// DxFont.cpp �֐��v���g�^�C�v�錾

#ifndef DX_NON_FONT

// �t�H���g�A������`��֌W�֐�
#define NS_EnumFontName								EnumFontName
#define NS_EnumFontNameEx							EnumFontNameEx
#define NS_EnumFontNameEx2							EnumFontNameEx2
#define NS_EnumFontNameEx2WithStrLen				EnumFontNameEx2WithStrLen
#define NS_CheckFontName							CheckFontName
#define NS_CheckFontNameWithStrLen					CheckFontNameWithStrLen

#define NS_InitFontToHandle							InitFontToHandle

#define NS_CreateFontToHandle						CreateFontToHandle
#define NS_CreateFontToHandleWithStrLen				CreateFontToHandleWithStrLen
#define NS_LoadFontDataToHandle						LoadFontDataToHandle
#define NS_LoadFontDataToHandleWithStrLen			LoadFontDataToHandleWithStrLen
#define NS_LoadFontDataFromMemToHandle				LoadFontDataFromMemToHandle
#define NS_SetFontSpaceToHandle						SetFontSpaceToHandle
#define NS_SetFontLineSpaceToHandle					SetFontLineSpaceToHandle
#define NS_SetFontCharCodeFormatToHandle			SetFontCharCodeFormatToHandle
#define NS_SetDefaultFontState						SetDefaultFontState
#define NS_SetDefaultFontStateWithStrLen			SetDefaultFontStateWithStrLen
#define NS_DeleteFontToHandle						DeleteFontToHandle
#define NS_SetFontLostFlag							SetFontLostFlag
#define NS_AddFontImageToHandle						AddFontImageToHandle
#define NS_AddFontImageToHandleWithStrLen			AddFontImageToHandleWithStrLen
#define NS_SubFontImageToHandle						SubFontImageToHandle
#define NS_SubFontImageToHandleWithStrLen			SubFontImageToHandleWithStrLen
#define NS_AddSubstitutionFontToHandle				AddSubstitutionFontToHandle
#define NS_SubSubstitutionFontToHandle				SubSubstitutionFontToHandle

#define NS_SetFontSize								SetFontSize
#define NS_SetFontThickness							SetFontThickness
#define NS_SetFontSpace								SetFontSpace
#define NS_GetFontSpace								GetFontSpace
#define NS_SetFontLineSpace							SetFontLineSpace
#define NS_GetFontLineSpace							GetFontLineSpace
#define NS_SetFontCharCodeFormat					SetFontCharCodeFormat

#define NS_SetFontCacheToTextureFlag				SetFontCacheToTextureFlag
#define NS_SetFontChacheToTextureFlag				SetFontChacheToTextureFlag
#define NS_SetFontCacheCharNum						SetFontCacheCharNum
#define NS_ChangeFont								ChangeFont
#define NS_ChangeFontWithStrLen						ChangeFontWithStrLen
#define NS_ChangeFontFromHandle						ChangeFontFromHandle
#define NS_ChangeFontType							ChangeFontType
#define NS_GetFontName								GetFontName

#define NS_FontCacheStringDrawToHandle				FontCacheStringDrawToHandle
#define NS_FontCacheStringDrawToHandleWithStrLen	FontCacheStringDrawToHandleWithStrLen
#define NS_FontBaseImageBlt							FontBaseImageBlt
#define NS_FontBaseImageBltWithStrLen				FontBaseImageBltWithStrLen
#define NS_FontBaseImageBltToHandle					FontBaseImageBltToHandle
#define NS_FontBaseImageBltToHandleWithStrLen		FontBaseImageBltToHandleWithStrLen

#define NS_GetFontNameToHandle						GetFontNameToHandle
#define NS_GetFontMaxCacheCharNumToHandle			GetFontMaxCacheCharNumToHandle
#define NS_GetFontMaxWidth							GetFontMaxWidth
#define NS_GetFontMaxWidthToHandle					GetFontMaxWidthToHandle
#define NS_GetFontAscent							GetFontAscent
#define NS_GetFontAscentToHandle					GetFontAscentToHandle
#define NS_GetFontCharInfo							GetFontCharInfo
#define NS_GetFontCharInfoWithStrLen				GetFontCharInfoWithStrLen
#define NS_GetDrawStringWidth						GetDrawStringWidth
#define NS_GetDrawNStringWidth						GetDrawNStringWidth
#define NS_GetDrawFormatStringWidth					GetDrawFormatStringWidth
#define NS_GetDrawStringWidthToHandle				GetDrawStringWidthToHandle
#define NS_GetDrawNStringWidthToHandle				GetDrawNStringWidthToHandle
#define NS_GetDrawFormatStringWidthToHandle			GetDrawFormatStringWidthToHandle
#define NS_GetDrawExtendStringWidth					GetDrawExtendStringWidth
#define NS_GetDrawExtendNStringWidth				GetDrawExtendNStringWidth
#define NS_GetDrawExtendFormatStringWidth			GetDrawExtendFormatStringWidth
#define NS_GetDrawExtendStringWidthToHandle			GetDrawExtendStringWidthToHandle
#define NS_GetDrawExtendNStringWidthToHandle		GetDrawExtendNStringWidthToHandle
#define NS_GetDrawExtendFormatStringWidthToHandle	GetDrawExtendFormatStringWidthToHandle
#define NS_GetDrawStringSize						GetDrawStringSize
#define NS_GetDrawNStringSize						GetDrawNStringSize
#define NS_GetDrawFormatStringSize					GetDrawFormatStringSize
#define NS_GetDrawExtendStringSize					GetDrawExtendStringSize
#define NS_GetDrawExtendNStringSize					GetDrawExtendNStringSize
#define NS_GetDrawExtendFormatStringSize			GetDrawExtendFormatStringSize
#define NS_GetDrawStringSizeToHandle				GetDrawStringSizeToHandle
#define NS_GetDrawNStringSizeToHandle				GetDrawNStringSizeToHandle
#define NS_GetDrawFormatStringSizeToHandle			GetDrawFormatStringSizeToHandle
#define NS_GetDrawExtendStringSizeToHandle			GetDrawExtendStringSizeToHandle
#define NS_GetDrawExtendNStringSizeToHandle			GetDrawExtendNStringSizeToHandle
#define NS_GetDrawExtendFormatStringSizeToHandle	GetDrawExtendFormatStringSizeToHandle
#define NS_GetDrawStringCharInfo					GetDrawStringCharInfo
#define NS_GetDrawNStringCharInfo					GetDrawNStringCharInfo
#define NS_GetDrawFormatStringCharInfo				GetDrawFormatStringCharInfo
#define NS_GetDrawExtendStringCharInfo				GetDrawExtendStringCharInfo
#define NS_GetDrawExtendNStringCharInfo				GetDrawExtendNStringCharInfo
#define NS_GetDrawExtendFormatStringCharInfo		GetDrawExtendFormatStringCharInfo
#define NS_GetDrawStringKerningPairInfo				GetDrawStringKerningPairInfo
#define NS_GetDrawStringKerningPairInfoWithStrLen	GetDrawStringKerningPairInfoWithStrLen
#define NS_GetDrawStringCharInfoToHandle			GetDrawStringCharInfoToHandle
#define NS_GetDrawNStringCharInfoToHandle			GetDrawNStringCharInfoToHandle
#define NS_GetDrawFormatStringCharInfoToHandle		GetDrawFormatStringCharInfoToHandle
#define NS_GetDrawExtendStringCharInfoToHandle		GetDrawExtendStringCharInfoToHandle
#define NS_GetDrawExtendNStringCharInfoToHandle		GetDrawExtendNStringCharInfoToHandle
#define NS_GetDrawExtendFormatStringCharInfoToHandle	GetDrawExtendFormatStringCharInfoToHandle
#define NS_GetDrawStringKerningPairInfoToHandle		GetDrawStringKerningPairInfoToHandle
#define NS_GetDrawStringKerningPairInfoToHandleWithStrLen		GetDrawStringKerningPairInfoToHandleWithStrLen

#define NS_GetFontStateToHandle						GetFontStateToHandle
#define NS_GetDefaultFontHandle						GetDefaultFontHandle
#define NS_GetFontMaxCacheCharNum					GetFontMaxCacheCharNum
#define NS_GetFontChacheToTextureFlag				GetFontChacheToTextureFlag
#define NS_SetFontCacheTextureColorBitDepth			SetFontCacheTextureColorBitDepth
#define NS_GetFontCacheTextureColorBitDepth			GetFontCacheTextureColorBitDepth
#define NS_GetFontCacheToTextureFlag				GetFontCacheToTextureFlag
#define NS_CheckFontChacheToTextureFlag				CheckFontChacheToTextureFlag
#define NS_CheckFontCacheToTextureFlag				CheckFontCacheToTextureFlag
#define NS_CheckFontHandleValid						CheckFontHandleValid
#define NS_ClearFontCacheToHandle					ClearFontCacheToHandle
#define NS_MultiByteCharCheck						MultiByteCharCheck
#define NS_GetFontCacheCharNum						GetFontCacheCharNum
#define NS_GetFontSize								GetFontSize
#define NS_GetFontEdgeSize							GetFontEdgeSize
#define NS_GetFontSizeToHandle						GetFontSizeToHandle
#define NS_GetFontEdgeSizeToHandle					GetFontEdgeSizeToHandle
#define NS_GetFontSpaceToHandle						GetFontSpaceToHandle
#define NS_GetFontLineSpaceToHandle					GetFontLineSpaceToHandle
#define	NS_SetFontCacheUsePremulAlphaFlag			SetFontCacheUsePremulAlphaFlag
#define NS_GetFontCacheUsePremulAlphaFlag			GetFontCacheUsePremulAlphaFlag
#define NS_SetFontUseAdjustSizeFlag					SetFontUseAdjustSizeFlag
#define NS_GetFontUseAdjustSizeFlag					GetFontUseAdjustSizeFlag
#define NS_SetFontOnlyDrawType						SetFontOnlyDrawType
#define NS_GetFontOnlyDrawType						GetFontOnlyDrawType
#define NS_SetFontIgnoreLFFlag						SetFontIgnoreLFFlag
#define NS_GetFontIgnoreLFFlag						GetFontIgnoreLFFlag

#define NS_AddFontFile								AddFontFile
#define NS_AddFontFileWithStrLen					AddFontFileWithStrLen
#define NS_AddFontFileFromMem						AddFontFileFromMem
#define NS_RemoveFontFile							RemoveFontFile

#define NS_CreateFontDataFile						CreateFontDataFile
#define NS_CreateFontDataFileWithStrLen				CreateFontDataFileWithStrLen

// ������`��֐�
#define NS_DrawString								DrawString
#define NS_DrawNString								DrawNString
#define NS_DrawVString								DrawVString
#define NS_DrawNVString								DrawNVString
#define NS_DrawFormatString							DrawFormatString
#define NS_DrawFormatVString						DrawFormatVString
#define NS_DrawFormatString2						DrawFormatString2
#define NS_DrawFormatVString2						DrawFormatVString2
#define NS_DrawExtendString							DrawExtendString
#define NS_DrawExtendNString						DrawExtendNString
#define NS_DrawExtendVString						DrawExtendVString
#define NS_DrawExtendNVString						DrawExtendNVString
#define NS_DrawExtendFormatString					DrawExtendFormatString
#define NS_DrawExtendFormatVString					DrawExtendFormatVString
#define NS_DrawExtendFormatString2					DrawExtendFormatString2
#define NS_DrawExtendFormatVString2					DrawExtendFormatVString2
#define NS_DrawRotaString							DrawRotaString
#define NS_DrawRotaNString							DrawRotaNString
#define NS_DrawRotaFormatString						DrawRotaFormatString
#define NS_DrawModiString							DrawModiString
#define NS_DrawModiNString							DrawModiNString
#define NS_DrawModiFormatString						DrawModiFormatString

#define NS_DrawStringF								DrawStringF
#define NS_DrawNStringF								DrawNStringF
#define NS_DrawVStringF								DrawVStringF
#define NS_DrawNVStringF							DrawNVStringF
#define NS_DrawFormatStringF						DrawFormatStringF
#define NS_DrawFormatVStringF						DrawFormatVStringF
#define NS_DrawFormatString2F						DrawFormatString2F
#define NS_DrawFormatVString2F						DrawFormatVString2F
#define NS_DrawExtendStringF						DrawExtendStringF
#define NS_DrawExtendNStringF						DrawExtendNStringF
#define NS_DrawExtendVStringF						DrawExtendVStringF
#define NS_DrawExtendNVStringF						DrawExtendNVStringF
#define NS_DrawExtendFormatStringF					DrawExtendFormatStringF
#define NS_DrawExtendFormatVStringF					DrawExtendFormatVStringF
#define NS_DrawExtendFormatString2F					DrawExtendFormatString2F
#define NS_DrawExtendFormatVString2F				DrawExtendFormatVString2F
#define NS_DrawRotaStringF							DrawRotaStringF
#define NS_DrawRotaNStringF							DrawRotaNStringF
#define NS_DrawRotaFormatStringF					DrawRotaFormatStringF
#define NS_DrawModiStringF							DrawModiStringF
#define NS_DrawModiNStringF							DrawModiNStringF
#define NS_DrawModiFormatStringF					DrawModiFormatStringF

#define NS_DrawNumberToI							DrawNumberToI
#define NS_DrawNumberToF							DrawNumberToF
#define NS_DrawNumberPlusToI						DrawNumberPlusToI
#define NS_DrawNumberPlusToF						DrawNumberPlusToF

#define NS_DrawStringToZBuffer						DrawStringToZBuffer
#define NS_DrawNStringToZBuffer						DrawNStringToZBuffer
#define NS_DrawVStringToZBuffer						DrawVStringToZBuffer
#define NS_DrawNVStringToZBuffer					DrawNVStringToZBuffer
#define NS_DrawFormatStringToZBuffer				DrawFormatStringToZBuffer
#define NS_DrawFormatVStringToZBuffer				DrawFormatVStringToZBuffer
#define NS_DrawExtendStringToZBuffer				DrawExtendStringToZBuffer
#define NS_DrawExtendNStringToZBuffer				DrawExtendNStringToZBuffer
#define NS_DrawExtendVStringToZBuffer				DrawExtendVStringToZBuffer
#define NS_DrawExtendNVStringToZBuffer				DrawExtendNVStringToZBuffer
#define NS_DrawExtendFormatStringToZBuffer			DrawExtendFormatStringToZBuffer
#define NS_DrawExtendFormatVStringToZBuffer			DrawExtendFormatVStringToZBuffer
#define NS_DrawRotaStringToZBuffer					DrawRotaStringToZBuffer
#define NS_DrawRotaNStringToZBuffer					DrawRotaNStringToZBuffer
#define NS_DrawRotaFormatStringToZBuffer			DrawRotaFormatStringToZBuffer
#define NS_DrawModiStringToZBuffer					DrawModiStringToZBuffer
#define NS_DrawModiNStringToZBuffer					DrawModiNStringToZBuffer
#define NS_DrawModiFormatStringToZBuffer			DrawModiFormatStringToZBuffer


#define NS_DrawStringToHandle						DrawStringToHandle
#define NS_DrawNStringToHandle						DrawNStringToHandle
#define NS_DrawVStringToHandle						DrawVStringToHandle
#define NS_DrawNVStringToHandle						DrawNVStringToHandle
#define NS_DrawFormatStringToHandle					DrawFormatStringToHandle
#define NS_DrawFormatVStringToHandle				DrawFormatVStringToHandle
#define NS_DrawFormatString2ToHandle				DrawFormatString2ToHandle
#define NS_DrawFormatVString2ToHandle				DrawFormatVString2ToHandle
#define NS_DrawExtendStringToHandle					DrawExtendStringToHandle
#define NS_DrawExtendNStringToHandle				DrawExtendNStringToHandle
#define NS_DrawExtendVStringToHandle				DrawExtendVStringToHandle
#define NS_DrawExtendNVStringToHandle				DrawExtendNVStringToHandle
#define NS_DrawExtendFormatStringToHandle			DrawExtendFormatStringToHandle
#define NS_DrawExtendFormatVStringToHandle			DrawExtendFormatVStringToHandle
#define NS_DrawExtendFormatString2ToHandle			DrawExtendFormatString2ToHandle
#define NS_DrawExtendFormatVString2ToHandle			DrawExtendFormatVString2ToHandle
#define NS_DrawRotaStringToHandle					DrawRotaStringToHandle
#define NS_DrawRotaNStringToHandle					DrawRotaNStringToHandle
#define NS_DrawRotaFormatStringToHandle				DrawRotaFormatStringToHandle
#define NS_DrawModiStringToHandle					DrawModiStringToHandle
#define NS_DrawModiNStringToHandle					DrawModiNStringToHandle
#define NS_DrawModiFormatStringToHandle				DrawModiFormatStringToHandle

#define NS_DrawStringFToHandle						DrawStringFToHandle
#define NS_DrawNStringFToHandle						DrawNStringFToHandle
#define NS_DrawVStringFToHandle						DrawVStringFToHandle
#define NS_DrawNVStringFToHandle					DrawNVStringFToHandle
#define NS_DrawFormatStringFToHandle				DrawFormatStringFToHandle
#define NS_DrawFormatVStringFToHandle				DrawFormatVStringFToHandle
#define NS_DrawFormatString2FToHandle				DrawFormatString2FToHandle
#define NS_DrawFormatVString2FToHandle				DrawFormatVString2FToHandle
#define NS_DrawExtendStringFToHandle				DrawExtendStringFToHandle
#define NS_DrawExtendNStringFToHandle				DrawExtendNStringFToHandle
#define NS_DrawExtendVStringFToHandle				DrawExtendVStringFToHandle
#define NS_DrawExtendNVStringFToHandle				DrawExtendNVStringFToHandle
#define NS_DrawExtendFormatStringFToHandle			DrawExtendFormatStringFToHandle
#define NS_DrawExtendFormatVStringFToHandle			DrawExtendFormatVStringFToHandle
#define NS_DrawExtendFormatString2FToHandle			DrawExtendFormatString2FToHandle
#define NS_DrawExtendFormatVString2FToHandle		DrawExtendFormatVString2FToHandle
#define NS_DrawRotaStringFToHandle					DrawRotaStringFToHandle
#define NS_DrawRotaNStringFToHandle					DrawRotaNStringFToHandle
#define NS_DrawRotaFormatStringFToHandle			DrawRotaFormatStringFToHandle
#define NS_DrawModiStringFToHandle					DrawModiStringFToHandle
#define NS_DrawModiNStringFToHandle					DrawModiNStringFToHandle
#define NS_DrawModiFormatStringFToHandle			DrawModiFormatStringFToHandle

#define NS_DrawNumberToIToHandle					DrawNumberToIToHandle
#define NS_DrawNumberToFToHandle					DrawNumberToFToHandle
#define NS_DrawNumberPlusToIToHandle				DrawNumberPlusToIToHandle
#define NS_DrawNumberPlusToFToHandle				DrawNumberPlusToFToHandle

#define NS_DrawStringToHandleToZBuffer				DrawStringToHandleToZBuffer
#define NS_DrawNStringToHandleToZBuffer				DrawNStringToHandleToZBuffer
#define NS_DrawVStringToHandleToZBuffer				DrawVStringToHandleToZBuffer
#define NS_DrawNVStringToHandleToZBuffer			DrawNVStringToHandleToZBuffer
#define NS_DrawFormatStringToHandleToZBuffer		DrawFormatStringToHandleToZBuffer
#define NS_DrawFormatVStringToHandleToZBuffer		DrawFormatVStringToHandleToZBuffer
#define NS_DrawExtendStringToHandleToZBuffer		DrawExtendStringToHandleToZBuffer
#define NS_DrawExtendNStringToHandleToZBuffer		DrawExtendNStringToHandleToZBuffer
#define NS_DrawExtendVStringToHandleToZBuffer		DrawExtendVStringToHandleToZBuffer
#define NS_DrawExtendNVStringToHandleToZBuffer		DrawExtendNVStringToHandleToZBuffer
#define NS_DrawExtendFormatStringToHandleToZBuffer	DrawExtendFormatStringToHandleToZBuffer
#define NS_DrawExtendFormatVStringToHandleToZBuffer	DrawExtendFormatVStringToHandleToZBuffer
#define NS_DrawRotaStringToHandleToZBuffer			DrawRotaStringToHandleToZBuffer
#define NS_DrawRotaNStringToHandleToZBuffer			DrawRotaNStringToHandleToZBuffer
#define NS_DrawRotaFormatStringToHandleToZBuffer	DrawRotaFormatStringToHandleToZBuffer
#define NS_DrawModiStringToHandleToZBuffer			DrawModiStringToHandleToZBuffer
#define NS_DrawModiNStringToHandleToZBuffer			DrawModiNStringToHandleToZBuffer
#define NS_DrawModiFormatStringToHandleToZBuffer	DrawModiFormatStringToHandleToZBuffer

#endif // DX_NON_FONT










// DxMath.cpp �֐��v���g�^�C�v�錾

// ���Z���C�u����









// DxBaseImage.cpp �֐��v���g�^�C�v�錾

// ��{�C���[�W�f�[�^�̃��[�h�{�c�h�a�֌W
#define NS_CreateGraphImageOrDIBGraph			CreateGraphImageOrDIBGraph
#define NS_CreateGraphImageOrDIBGraphWithStrLen	CreateGraphImageOrDIBGraphWithStrLen
#define NS_CreateGraphImageType2				CreateGraphImageType2
#define NS_CreateBmpInfo						CreateBmpInfo
#define NS_GetImageSize_File					GetImageSize_File
#define NS_GetImageSize_FileWithStrLen			GetImageSize_FileWithStrLen
#define NS_GetImageSize_Mem						GetImageSize_Mem
#define NS_GetGraphImageFullColorCode			GetGraphImageFullColorCode
#define NS_CreateGraphImage_plus_Alpha			CreateGraphImage_plus_Alpha
#define NS_CreateGraphImage_plus_AlphaWithStrLen CreateGraphImage_plus_AlphaWithStrLen
#define NS_ReverseGraphImage					ReverseGraphImage
#ifdef WINDOWS_DESKTOP_OS
#define NS_CreateDIBGraph						CreateDIBGraph
#define NS_CreateDIBGraphWithStrLen				CreateDIBGraphWithStrLen
#define NS_CreateDIBGraphToMem					CreateDIBGraphToMem
#define NS_CreateDIBGraph_plus_Alpha			CreateDIBGraph_plus_Alpha
#define NS_CreateDIBGraph_plus_AlphaWithStrLen	CreateDIBGraph_plus_AlphaWithStrLen
#define NS_CreateDIBGraphVer2					CreateDIBGraphVer2
#define NS_CreateDIBGraphVer2WithStrLen			CreateDIBGraphVer2WithStrLen
#define NS_CreateDIBGraphVer2_plus_Alpha		CreateDIBGraphVer2_plus_Alpha
#define NS_CreateDIBGraphVer2_plus_AlphaWithStrLen CreateDIBGraphVer2_plus_AlphaWithStrLen
#define NS_ConvBitmapToGraphImage				ConvBitmapToGraphImage
#define NS_ConvGraphImageToBitmap				ConvGraphImageToBitmap
#endif // WINDOWS_DESKTOP_OS

//#define NS_AddUserGraphLoadFunction			S_AddUserGraphLoadFunction
//#define NS_AddUserGraphLoadFunction2			S_AddUserGraphLoadFunction2
//#define NS_AddUserGraphLoadFunction3			S_AddUserGraphLoadFunction3
#define NS_AddUserGraphLoadFunction4			AddUserGraphLoadFunction4
//#define NS_SubUserGraphLoadFunction			S_SubUserGraphLoadFunction
//#define NS_SubUserGraphLoadFunction2			S_SubUserGraphLoadFunction2
//#define NS_SubUserGraphLoadFunction3			S_SubUserGraphLoadFunction3
#define NS_SubUserGraphLoadFunction4			SubUserGraphLoadFunction4

#define NS_SetUseFastLoadFlag					SetUseFastLoadFlag
#define NS_GetGraphDataShavedMode				GetGraphDataShavedMode
#define NS_SetGraphDataShavedMode				SetGraphDataShavedMode
#define NS_SetUsePremulAlphaConvertLoad			SetUsePremulAlphaConvertLoad
#define NS_GetUsePremulAlphaConvertLoad			GetUsePremulAlphaConvertLoad
#define NS_SetUseConvertNormalFormatLoad		SetUseConvertNormalFormatLoad
#define NS_GetUseConvertNormalFormatLoad		GetUseConvertNormalFormatLoad


//��{�C���[�W�f�[�^�\���̊֌W
#define NS_CreateBaseImage						CreateBaseImage
#define NS_CreateBaseImageWithStrLen			CreateBaseImageWithStrLen
#define NS_CreateGraphImage						CreateGraphImage
#define NS_CreateBaseImageToFile				CreateBaseImageToFile
#define NS_CreateBaseImageToFileWithStrLen		CreateBaseImageToFileWithStrLen
#define NS_CreateBaseImageToMem					CreateBaseImageToMem
#define NS_CreateARGBF32ColorBaseImage			CreateARGBF32ColorBaseImage
#define NS_CreateARGBF16ColorBaseImage			CreateARGBF16ColorBaseImage
#define NS_CreateARGB8ColorBaseImage			CreateARGB8ColorBaseImage
#define NS_CreateXRGB8ColorBaseImage			CreateXRGB8ColorBaseImage
#define NS_CreateRGB8ColorBaseImage				CreateRGB8ColorBaseImage
#define NS_CreateRGBA8ColorBaseImage			CreateRGBA8ColorBaseImage
#define NS_CreateABGR8ColorBaseImage			CreateABGR8ColorBaseImage
#define NS_CreateBGRA8ColorBaseImage			CreateBGRA8ColorBaseImage
#define NS_CreateARGB4ColorBaseImage			CreateARGB4ColorBaseImage
#define NS_CreateA1R5G5B5ColorBaseImage			CreateA1R5G5B5ColorBaseImage
#define NS_CreateX1R5G5B5ColorBaseImage			CreateX1R5G5B5ColorBaseImage
#define NS_CreateR5G5B5A1ColorBaseImage			CreateR5G5B5A1ColorBaseImage
#define NS_CreateR5G6B5ColorBaseImage			CreateR5G6B5ColorBaseImage
#define NS_CreatePAL8ColorBaseImage				CreatePAL8ColorBaseImage
#define NS_CreateColorDataBaseImage				CreateColorDataBaseImage
#define NS_GetBaseImageGraphDataSize			GetBaseImageGraphDataSize
#define NS_DerivationBaseImage					DerivationBaseImage

#define NS_ReleaseBaseImage						ReleaseBaseImage
#define NS_ReleaseGraphImage					ReleaseGraphImage

#define NS_ConvertNormalFormatBaseImage			ConvertNormalFormatBaseImage
#define NS_ConvertPremulAlphaBaseImage			ConvertPremulAlphaBaseImage
#define NS_ConvertInterpAlphaBaseImage			ConvertInterpAlphaBaseImage

#define NS_GetDrawScreenBaseImage				GetDrawScreenBaseImage
#define NS_GetDrawScreenBaseImageDestPos		GetDrawScreenBaseImageDestPos
#ifdef WINDOWS_DESKTOP_OS
#define NS_UpdateLayerdWindowForBaseImage		UpdateLayerdWindowForBaseImage
#define NS_UpdateLayerdWindowForBaseImageRect	UpdateLayerdWindowForBaseImageRect
#define NS_UpdateLayerdWindowForPremultipliedAlphaBaseImage			UpdateLayerdWindowForPremultipliedAlphaBaseImage
#define NS_UpdateLayerdWindowForPremultipliedAlphaBaseImageRect		UpdateLayerdWindowForPremultipliedAlphaBaseImageRect
#define NS_GetDesktopScreenBaseImage			GetDesktopScreenBaseImage
#endif // WINDOWS_DESKTOP_OS
#define NS_FillBaseImage						FillBaseImage
#define NS_FillRectBaseImage					FillRectBaseImage
#define NS_ClearRectBaseImage					ClearRectBaseImage
#define NS_GetPaletteBaseImage					GetPaletteBaseImage
#define NS_SetPaletteBaseImage					SetPaletteBaseImage
#define NS_SetPixelPalCodeBaseImage				SetPixelPalCodeBaseImage
#define NS_GetPixelPalCodeBaseImage				GetPixelPalCodeBaseImage
#define NS_SetPixelBaseImage					SetPixelBaseImage
#define NS_SetPixelBaseImageF					SetPixelBaseImageF
#define NS_GetPixelBaseImage					GetPixelBaseImage
#define NS_GetPixelBaseImageF					GetPixelBaseImageF
#define NS_DrawLineBaseImage					DrawLineBaseImage
#define NS_DrawCircleBaseImage					DrawCircleBaseImage
#define NS_BltBaseImage							BltBaseImage
#define NS_BltBaseImage2						BltBaseImage2
#define NS_BltBaseImageWithTransColor			BltBaseImageWithTransColor
#define NS_BltBaseImageWithAlphaBlend			BltBaseImageWithAlphaBlend
#define NS_ReverseBaseImageH					ReverseBaseImageH
#define NS_ReverseBaseImageV					ReverseBaseImageV
#define NS_ReverseBaseImage						ReverseBaseImage
#define NS_CheckPixelAlphaBaseImage				CheckPixelAlphaBaseImage
#define NS_GetBaseImageUseMaxPaletteNo			GetBaseImageUseMaxPaletteNo

#ifndef DX_NON_JPEGREAD
#define NS_ReadJpegExif							ReadJpegExif
#define NS_ReadJpegExifWithStrLen				ReadJpegExifWithStrLen
#endif // DX_NON_JPEGREAD

#ifndef DX_NON_SAVEFUNCTION

#define NS_SaveBaseImageToBmp					SaveBaseImageToBmp
#define NS_SaveBaseImageToBmpWithStrLen			SaveBaseImageToBmpWithStrLen
#define NS_SaveBaseImageToDds					SaveBaseImageToDds
#define NS_SaveBaseImageToDdsWithStrLen			SaveBaseImageToDdsWithStrLen
#ifndef DX_NON_PNGREAD
#define NS_SaveBaseImageToPng					SaveBaseImageToPng
#define NS_SaveBaseImageToPngWithStrLen			SaveBaseImageToPngWithStrLen
#endif
#ifndef DX_NON_JPEGREAD
#define NS_SaveBaseImageToJpeg					SaveBaseImageToJpeg
#define NS_SaveBaseImageToJpegWithStrLen		SaveBaseImageToJpegWithStrLen
#endif

#endif // DX_NON_SAVEFUNCTION

// ��{�C���[�W�`��
#define NS_DrawBaseImage						DrawBaseImage

// �J���[�}�b�`���O���Ȃ���O���t�B�b�N�f�[�^�ԓ]�����s�� Ver2
#define NS_GraphColorMatchBltVer2				GraphColorMatchBltVer2







// �F���擾�֌W
#define NS_GetColorF							GetColorF
#define NS_GetColorU8							GetColorU8
#define NS_GetColor								GetColor
#define NS_GetColor2							GetColor2
#define NS_GetColor3							GetColor3
#define NS_GetColor4							GetColor4
#define NS_GetColor5							GetColor5
#define NS_CreatePaletteColorData				CreatePaletteColorData
#define NS_CreateARGBF32ColorData				CreateARGBF32ColorData
#define NS_CreateARGBF16ColorData				CreateARGBF16ColorData
#define NS_CreateXRGB8ColorData					CreateXRGB8ColorData
#define NS_CreateARGB8ColorData					CreateARGB8ColorData
#define NS_CreateRGBA8ColorData					CreateRGBA8ColorData
#define NS_CreateABGR8ColorData					CreateABGR8ColorData
#define NS_CreateBGRA8ColorData					CreateBGRA8ColorData
#define NS_CreateBGR8ColorData					CreateBGR8ColorData
#define NS_CreateARGB4ColorData					CreateARGB4ColorData
#define NS_CreateA1R5G5B5ColorData				CreateA1R5G5B5ColorData
#define NS_CreateX1R5G5B5ColorData				CreateX1R5G5B5ColorData
#define NS_CreateR5G5B5A1ColorData				CreateR5G5B5A1ColorData
#define NS_CreateR5G6B5ColorData				CreateR5G6B5ColorData
#define NS_CreateFullColorData					CreateFullColorData
#define NS_CreateGrayColorData					CreateGrayColorData
#define NS_CreatePal8ColorData					CreatePal8ColorData
#define NS_CreateColorData						CreateColorData
#define NS_SetColorDataNoneMask					SetColorDataNoneMask
#define NS_CmpColorData							CmpColorData









// DxSoftImage.cpp�֐��v���g�^�C�v�錾
#ifndef DX_NON_SOFTIMAGE
#define NS_InitSoftImage						InitSoftImage
#define	NS_LoadSoftImage						LoadSoftImage
#define	NS_LoadSoftImageWithStrLen				LoadSoftImageWithStrLen
#define	NS_LoadARGB8ColorSoftImage				LoadARGB8ColorSoftImage
#define	NS_LoadARGB8ColorSoftImageWithStrLen	LoadARGB8ColorSoftImageWithStrLen
#define	NS_LoadXRGB8ColorSoftImage				LoadXRGB8ColorSoftImage
#define	NS_LoadXRGB8ColorSoftImageWithStrLen	LoadXRGB8ColorSoftImageWithStrLen
#define	NS_LoadSoftImageToMem					LoadSoftImageToMem
#define	NS_LoadARGB8ColorSoftImageToMem			LoadARGB8ColorSoftImageToMem
#define	NS_LoadXRGB8ColorSoftImageToMem			LoadXRGB8ColorSoftImageToMem
#define NS_MakeSoftImage						MakeSoftImage
#define NS_MakeARGBF32ColorSoftImage			MakeARGBF32ColorSoftImage
#define NS_MakeARGBF16ColorSoftImage			MakeARGBF16ColorSoftImage
#define NS_MakeARGB8ColorSoftImage				MakeARGB8ColorSoftImage
#define NS_MakeXRGB8ColorSoftImage				MakeXRGB8ColorSoftImage
#define NS_MakeRGBA8ColorSoftImage				MakeRGBA8ColorSoftImage
#define NS_MakeABGR8ColorSoftImage				MakeABGR8ColorSoftImage
#define NS_MakeBGRA8ColorSoftImage				MakeBGRA8ColorSoftImage
#define NS_MakeARGB4ColorSoftImage				MakeARGB4ColorSoftImage
#define NS_MakeA1R5G5B5ColorSoftImage			MakeA1R5G5B5ColorSoftImage
#define NS_MakeX1R5G5B5ColorSoftImage			MakeX1R5G5B5ColorSoftImage
#define NS_MakeR5G5B5A1ColorSoftImage			MakeR5G5B5A1ColorSoftImage
#define NS_MakeR5G6B5ColorSoftImage				MakeR5G6B5ColorSoftImage
#define NS_MakeRGB8ColorSoftImage				MakeRGB8ColorSoftImage
#define NS_MakePAL8ColorSoftImage				MakePAL8ColorSoftImage
#define NS_MakeColorDataSoftImage				MakeColorDataSoftImage


#define NS_DeleteSoftImage						DeleteSoftImage

#define NS_GetSoftImageSize						GetSoftImageSize
#define NS_CheckPaletteSoftImage				CheckPaletteSoftImage
#define NS_CheckAlphaSoftImage					CheckAlphaSoftImage
#define NS_CheckPixelAlphaSoftImage				CheckPixelAlphaSoftImage

#define NS_GetDrawScreenSoftImage				GetDrawScreenSoftImage
#define NS_GetDrawScreenSoftImageDestPos		GetDrawScreenSoftImageDestPos
#ifdef WINDOWS_DESKTOP_OS
#define NS_UpdateLayerdWindowForSoftImage		UpdateLayerdWindowForSoftImage
#define NS_UpdateLayerdWindowForSoftImageRect	UpdateLayerdWindowForSoftImageRect
#define NS_UpdateLayerdWindowForPremultipliedAlphaSoftImage			UpdateLayerdWindowForPremultipliedAlphaSoftImage
#define NS_UpdateLayerdWindowForPremultipliedAlphaSoftImageRect		UpdateLayerdWindowForPremultipliedAlphaSoftImageRect
#define NS_GetDesktopScreenSoftImage			GetDesktopScreenSoftImage
#endif // WINDOWS_DESKTOP_OS
#define NS_FillSoftImage						FillSoftImage
#define NS_ClearRectSoftImage					ClearRectSoftImage
#define NS_GetPaletteSoftImage					GetPaletteSoftImage
#define NS_SetPaletteSoftImage					SetPaletteSoftImage
#define NS_DrawPixelPalCodeSoftImage			DrawPixelPalCodeSoftImage
#define NS_GetPixelPalCodeSoftImage				GetPixelPalCodeSoftImage
#define NS_GetImageAddressSoftImage				GetImageAddressSoftImage
#define NS_GetPitchSoftImage					GetPitchSoftImage
#define NS_DrawPixelSoftImage					DrawPixelSoftImage
#define NS_DrawPixelSoftImageF					DrawPixelSoftImageF
#define NS_DrawPixelSoftImage_Unsafe_XRGB8		DrawPixelSoftImage_Unsafe_XRGB8
#define NS_DrawPixelSoftImage_Unsafe_ARGB8		DrawPixelSoftImage_Unsafe_ARGB8
#define NS_GetPixelSoftImage					GetPixelSoftImage
#define NS_GetPixelSoftImageF					GetPixelSoftImageF
#define NS_GetPixelSoftImage_Unsafe_XRGB8		GetPixelSoftImage_Unsafe_XRGB8
#define NS_GetPixelSoftImage_Unsafe_ARGB8		GetPixelSoftImage_Unsafe_ARGB8
#define NS_DrawLineSoftImage					DrawLineSoftImage
#define NS_DrawCircleSoftImage					DrawCircleSoftImage
#define NS_BltSoftImage							BltSoftImage
#define NS_BltSoftImageWithTransColor			BltSoftImageWithTransColor
#define NS_BltSoftImageWithAlphaBlend			BltSoftImageWithAlphaBlend
#define NS_ReverseSoftImageH					ReverseSoftImageH
#define NS_ReverseSoftImageV					ReverseSoftImageV
#define NS_ReverseSoftImage						ReverseSoftImage
#define NS_ConvertPremulAlphaSoftImage			ConvertPremulAlphaSoftImage
#define NS_ConvertInterpAlphaSoftImage			ConvertInterpAlphaSoftImage

#ifndef DX_NON_FONT
#define NS_BltStringSoftImage					BltStringSoftImage
#define NS_BltStringSoftImageWithStrLen			BltStringSoftImageWithStrLen
#define NS_BltStringSoftImageToHandle			BltStringSoftImageToHandle
#define NS_BltStringSoftImageToHandleWithStrLen	BltStringSoftImageToHandleWithStrLen
#endif  // DX_NON_FONT

#define NS_DrawSoftImage						DrawSoftImage

#ifndef DX_NON_SAVEFUNCTION

#define NS_SaveSoftImageToBmp					SaveSoftImageToBmp
#define NS_SaveSoftImageToBmpWithStrLen			SaveSoftImageToBmpWithStrLen
#define NS_SaveSoftImageToDds					SaveSoftImageToDds
#define NS_SaveSoftImageToDdsWithStrLen			SaveSoftImageToDdsWithStrLen
#ifndef DX_NON_PNGREAD
#define NS_SaveSoftImageToPng					SaveSoftImageToPng
#define NS_SaveSoftImageToPngWithStrLen			SaveSoftImageToPngWithStrLen
#endif
#ifndef DX_NON_JPEGREAD
#define NS_SaveSoftImageToJpeg					SaveSoftImageToJpeg
#define NS_SaveSoftImageToJpegWithStrLen		SaveSoftImageToJpegWithStrLen
#endif

#endif // DX_NON_SAVEFUNCTION

#endif // DX_NON_SOFTIMAGE
















#ifndef DX_NON_SOUND

// DxSound.cpp�֐��v���g�^�C�v�錾

// �T�E���h�f�[�^�Ǘ��n�֐�
#define NS_InitSoundMem							InitSoundMem

#define NS_AddSoundData							AddSoundData
#define NS_AddStreamSoundMem					AddStreamSoundMem
#define NS_AddStreamSoundMemToMem				AddStreamSoundMemToMem
#define NS_AddStreamSoundMemToFile				AddStreamSoundMemToFile
#define NS_AddStreamSoundMemToFileWithStrLen	AddStreamSoundMemToFileWithStrLen
#define NS_SetupStreamSoundMem					SetupStreamSoundMem
#define NS_PlayStreamSoundMem					PlayStreamSoundMem
#define NS_CheckStreamSoundMem					CheckStreamSoundMem
#define NS_StopStreamSoundMem					StopStreamSoundMem
#define NS_SetStreamSoundCurrentPosition		SetStreamSoundCurrentPosition
#define NS_GetStreamSoundCurrentPosition		GetStreamSoundCurrentPosition
#define NS_SetStreamSoundCurrentTime			SetStreamSoundCurrentTime
#define NS_GetStreamSoundCurrentTime			GetStreamSoundCurrentTime
#define NS_ProcessStreamSoundMem				ProcessStreamSoundMem
#define NS_ProcessStreamSoundMemAll				ProcessStreamSoundMemAll


#define NS_LoadSoundMem2						LoadSoundMem2
#define NS_LoadSoundMem2WithStrLen				LoadSoundMem2WithStrLen
#define NS_LoadBGM								LoadBGM
#define NS_LoadBGMWithStrLen					LoadBGMWithStrLen

#define NS_LoadSoundMemBase						LoadSoundMemBase
#define NS_LoadSoundMemBaseWithStrLen			LoadSoundMemBaseWithStrLen
#define NS_LoadSoundMem							LoadSoundMem
#define NS_LoadSoundMemWithStrLen				LoadSoundMemWithStrLen
#define NS_LoadSoundMemToBufNumSitei			LoadSoundMemToBufNumSitei
#define NS_LoadSoundMemToBufNumSiteiWithStrLen	LoadSoundMemToBufNumSiteiWithStrLen
#define NS_LoadSoundMemByResource				LoadSoundMemByResource
#define NS_LoadSoundMemByResourceWithStrLen		LoadSoundMemByResourceWithStrLen
#define NS_DuplicateSoundMem					DuplicateSoundMem

#define NS_LoadSoundMemByMemImageBase			LoadSoundMemByMemImageBase
#define NS_LoadSoundMemByMemImage				LoadSoundMemByMemImage
#define NS_LoadSoundMemByMemImage2				LoadSoundMemByMemImage2
#define NS_LoadSoundMemByMemImageToBufNumSitei	LoadSoundMemByMemImageToBufNumSitei
#define NS_LoadSoundMem2ByMemImage				LoadSoundMem2ByMemImage
#define NS_LoadSoundMemFromSoftSound			LoadSoundMemFromSoftSound

#define NS_DeleteSoundMem						DeleteSoundMem

#define NS_PlaySoundMem							PlaySoundMem
#define NS_StopSoundMem							StopSoundMem
#define NS_CheckSoundMem						CheckSoundMem
#define NS_SetPanSoundMem						SetPanSoundMem
#define NS_ChangePanSoundMem					ChangePanSoundMem
#define NS_GetPanSoundMem						GetPanSoundMem
#define NS_SetVolumeSoundMem					SetVolumeSoundMem
#define NS_ChangeVolumeSoundMem					ChangeVolumeSoundMem
#define NS_GetVolumeSoundMem					GetVolumeSoundMem
#define NS_GetVolumeSoundMem2					GetVolumeSoundMem2
#define NS_SetChannelVolumeSoundMem				SetChannelVolumeSoundMem
#define NS_ChangeChannelVolumeSoundMem			ChangeChannelVolumeSoundMem
#define NS_GetChannelVolumeSoundMem				GetChannelVolumeSoundMem
#define NS_GetChannelVolumeSoundMem2			GetChannelVolumeSoundMem2
#define NS_SetFrequencySoundMem					SetFrequencySoundMem
#define NS_GetFrequencySoundMem					GetFrequencySoundMem
#define NS_ResetFrequencySoundMem				ResetFrequencySoundMem

#define NS_SetNextPlayPanSoundMem				SetNextPlayPanSoundMem
#define NS_ChangeNextPlayPanSoundMem			ChangeNextPlayPanSoundMem
#define NS_SetNextPlayVolumeSoundMem			SetNextPlayVolumeSoundMem
#define NS_ChangeNextPlayVolumeSoundMem			ChangeNextPlayVolumeSoundMem
#define NS_SetNextPlayChannelVolumeSoundMem		SetNextPlayChannelVolumeSoundMem
#define NS_ChangeNextPlayChannelVolumeSoundMem	ChangeNextPlayChannelVolumeSoundMem
#define NS_SetNextPlayFrequencySoundMem			SetNextPlayFrequencySoundMem

#define NS_SetCurrentPositionSoundMem			SetCurrentPositionSoundMem
#define NS_GetCurrentPositionSoundMem			GetCurrentPositionSoundMem
#define NS_SetSoundCurrentPosition				SetSoundCurrentPosition
#define NS_GetSoundCurrentPosition				GetSoundCurrentPosition
#define NS_SetSoundCurrentTime					SetSoundCurrentTime
#define NS_GetSoundCurrentTime					GetSoundCurrentTime
#define NS_GetSoundTotalSample					GetSoundTotalSample
#define NS_GetSoundTotalTime					GetSoundTotalTime

#define NS_SetLoopPosSoundMem					SetLoopPosSoundMem
#define NS_SetLoopTimePosSoundMem				SetLoopTimePosSoundMem
#define NS_SetLoopSamplePosSoundMem				SetLoopSamplePosSoundMem

#define NS_SetLoopStartTimePosSoundMem			SetLoopStartTimePosSoundMem
#define NS_SetLoopStartSamplePosSoundMem		SetLoopStartSamplePosSoundMem

#define NS_SetLoopAreaTimePosSoundMem			SetLoopAreaTimePosSoundMem
#define NS_GetLoopAreaTimePosSoundMem			GetLoopAreaTimePosSoundMem
#define NS_SetLoopAreaSamplePosSoundMem			SetLoopAreaSamplePosSoundMem
#define NS_GetLoopAreaSamplePosSoundMem			GetLoopAreaSamplePosSoundMem

#define NS_SetPlayFinishDeleteSoundMem			SetPlayFinishDeleteSoundMem

#define NS_Set3DReverbParamSoundMem				Set3DReverbParamSoundMem
#define NS_Set3DPresetReverbParamSoundMem		Set3DPresetReverbParamSoundMem
#define NS_Set3DReverbParamSoundMemAll			Set3DReverbParamSoundMemAll
#define NS_Set3DPresetReverbParamSoundMemAll	Set3DPresetReverbParamSoundMemAll
#define NS_Get3DReverbParamSoundMem				Get3DReverbParamSoundMem
#define NS_Get3DPresetReverbParamSoundMem		Get3DPresetReverbParamSoundMem

#define NS_Set3DPositionSoundMem				Set3DPositionSoundMem
#define NS_Set3DRadiusSoundMem					Set3DRadiusSoundMem
//#define NS_Set3DInnerRadiusSoundMem			Set3DInnerRadiusSoundMem
#define NS_Set3DVelocitySoundMem				Set3DVelocitySoundMem
//#define NS_Set3DFrontPosition_UpVecYSoundMem	Set3DFrontPosition_UpVecYSoundMem
//#define NS_Set3DFrontPositionSoundMem			Set3DFrontPositionSoundMem
//#define NS_Set3DConeAngleSoundMem				Set3DConeAngleSoundMem
//#define NS_Set3DConeVolumeSoundMem			Set3DConeVolumeSoundMem

#define NS_SetNextPlay3DPositionSoundMem		SetNextPlay3DPositionSoundMem
#define NS_SetNextPlay3DRadiusSoundMem			SetNextPlay3DRadiusSoundMem
#define NS_SetNextPlay3DVelocitySoundMem		SetNextPlay3DVelocitySoundMem


// ����֐�
#define NS_GetMP3TagInfo						GetMP3TagInfo
#define NS_GetMP3TagInfoWithStrLen				GetMP3TagInfoWithStrLen
#ifndef DX_NON_OGGVORBIS
#define NS_GetOggCommentNum						GetOggCommentNum
#define NS_GetOggCommentNumWithStrLen			GetOggCommentNumWithStrLen
#define NS_GetOggComment						GetOggComment
#define NS_GetOggCommentWithStrLen				GetOggCommentWithStrLen
#endif // DX_NON_OGGVORBIS


// �ݒ�֌W�֐�
#define NS_SetCreateSoundDataType				SetCreateSoundDataType
#define NS_GetCreateSoundDataType				GetCreateSoundDataType
#define NS_SetCreateSoundPitchRate				SetCreateSoundPitchRate
#define NS_GetCreateSoundPitchRate				GetCreateSoundPitchRate
#define NS_SetCreateSoundTimeStretchRate		SetCreateSoundTimeStretchRate
#define NS_GetCreateSoundTimeStretchRate		GetCreateSoundTimeStretchRate
#define NS_SetCreateSoundLoopAreaTimePos		SetCreateSoundLoopAreaTimePos
#define NS_GetCreateSoundLoopAreaTimePos		GetCreateSoundLoopAreaTimePos
#define NS_SetCreateSoundLoopAreaSamplePos		SetCreateSoundLoopAreaSamplePos
#define NS_GetCreateSoundLoopAreaSamplePos		GetCreateSoundLoopAreaSamplePos
#define NS_SetCreateSoundIgnoreLoopAreaInfo		SetCreateSoundIgnoreLoopAreaInfo
#define NS_GetCreateSoundIgnoreLoopAreaInfo		GetCreateSoundIgnoreLoopAreaInfo
#define NS_SetDisableReadSoundFunctionMask		SetDisableReadSoundFunctionMask
#define NS_GetDisableReadSoundFunctionMask		GetDisableReadSoundFunctionMask
#define NS_SetEnableSoundCaptureFlag			SetEnableSoundCaptureFlag
#define NS_SetUseSoftwareMixingSoundFlag		SetUseSoftwareMixingSoundFlag
#define NS_SetEnableXAudioFlag					SetEnableXAudioFlag
#define NS_SetEnableWASAPIFlag					SetEnableWASAPIFlag
#ifndef DX_NON_ASIO
#define NS_SetEnableASIOFlag					SetEnableASIOFlag
#define NS_SetUseASIODriverIndex				SetUseASIODriverIndex
#endif // DX_NON_ASIO
#define NS_SetEnableMMEwaveOutFlag				SetEnableMMEwaveOutFlag

#define NS_SetUseOldVolumeCalcFlag				SetUseOldVolumeCalcFlag
#define NS_SetSoundCurrentTimeType				SetSoundCurrentTimeType
#define NS_GetSoundCurrentTimeType				GetSoundCurrentTimeType

#define NS_SetCreate3DSoundFlag					SetCreate3DSoundFlag
#define NS_Set3DSoundOneMetre					Set3DSoundOneMetre
#define NS_Set3DSoundListenerPosAndFrontPos_UpVecY	Set3DSoundListenerPosAndFrontPos_UpVecY
#define NS_Set3DSoundListenerPosAndFrontPosAndUpVec		Set3DSoundListenerPosAndFrontPosAndUpVec
#define NS_Set3DSoundListenerVelocity			Set3DSoundListenerVelocity
#define NS_Set3DSoundListenerConeAngle			Set3DSoundListenerConeAngle
#define NS_Set3DSoundListenerConeVolume			Set3DSoundListenerConeVolume


// ���擾�n�֐�
#define NS_GetDSoundObj							GetDSoundObj

#ifndef DX_NON_BEEP
// BEEP���Đ��p����
#define NS_SetBeepFrequency						SetBeepFrequency
#define NS_PlayBeep								PlayBeep
#define NS_StopBeep								StopBeep
#endif

// ���b�p�[�֐�
#define NS_PlaySoundFile						PlaySoundFile
#define NS_PlaySoundFileWithStrLen				PlaySoundFileWithStrLen
#define NS_PlaySound							PlaySound
#define NS_PlaySoundWithStrLen					PlaySoundWithStrLen
#define NS_PlaySoundDX							PlaySoundDX
#define NS_PlaySoundDXWithStrLen				PlaySoundDXWithStrLen
#define NS_CheckSoundFile						CheckSoundFile
#define NS_CheckSound							CheckSound
#define NS_StopSoundFile						StopSoundFile
#define NS_StopSound							StopSound
#define NS_SetVolumeSoundFile					SetVolumeSoundFile
#define NS_SetVolumeSound						SetVolumeSound

// �\�t�g�E�G�A����T�E���h�n�֐�
#define NS_InitSoftSound						InitSoftSound
#define NS_LoadSoftSound						LoadSoftSound
#define NS_LoadSoftSoundWithStrLen				LoadSoftSoundWithStrLen
#define NS_LoadSoftSoundFromMemImage			LoadSoftSoundFromMemImage
#define NS_MakeSoftSound						MakeSoftSound
#define NS_MakeSoftSound2Ch16Bit44KHz			MakeSoftSound2Ch16Bit44KHz
#define NS_MakeSoftSound2Ch16Bit22KHz			MakeSoftSound2Ch16Bit22KHz
#define NS_MakeSoftSound2Ch8Bit44KHz			MakeSoftSound2Ch8Bit44KHz
#define NS_MakeSoftSound2Ch8Bit22KHz			MakeSoftSound2Ch8Bit22KHz
#define NS_MakeSoftSound1Ch16Bit44KHz			MakeSoftSound1Ch16Bit44KHz
#define NS_MakeSoftSound1Ch16Bit22KHz			MakeSoftSound1Ch16Bit22KHz
#define NS_MakeSoftSound1Ch8Bit44KHz			MakeSoftSound1Ch8Bit44KHz
#define NS_MakeSoftSound1Ch8Bit22KHz			MakeSoftSound1Ch8Bit22KHz
#define NS_MakeSoftSoundCustom					MakeSoftSoundCustom
#define NS_DeleteSoftSound						DeleteSoftSound
#ifndef DX_NON_SAVEFUNCTION
#define NS_SaveSoftSound						SaveSoftSound
#define NS_SaveSoftSoundWithStrLen				SaveSoftSoundWithStrLen
#endif // DX_NON_SAVEFUNCTION
#define NS_GetSoftSoundSampleNum				GetSoftSoundSampleNum
#define NS_GetSoftSoundFormat					GetSoftSoundFormat
#define NS_ReadSoftSoundData					ReadSoftSoundData
#define NS_ReadSoftSoundDataF					ReadSoftSoundDataF
#define NS_WriteSoftSoundData					WriteSoftSoundData
#define NS_WriteSoftSoundDataF					WriteSoftSoundDataF
#define NS_WriteTimeStretchSoftSoundData		WriteTimeStretchSoftSoundData
#define NS_WritePitchShiftSoftSoundData			WritePitchShiftSoftSoundData
#define NS_GetSoftSoundDataImage				GetSoftSoundDataImage
#define NS_GetFFTVibrationSoftSound				GetFFTVibrationSoftSound
#define NS_GetFFTVibrationSoftSoundBase			GetFFTVibrationSoftSoundBase

#define NS_InitSoftSoundPlayer					InitSoftSoundPlayer
#define NS_MakeSoftSoundPlayer					MakeSoftSoundPlayer
#define NS_MakeSoftSoundPlayer2Ch16Bit44KHz		MakeSoftSoundPlayer2Ch16Bit44KHz
#define NS_MakeSoftSoundPlayer2Ch16Bit22KHz		MakeSoftSoundPlayer2Ch16Bit22KHz
#define NS_MakeSoftSoundPlayer2Ch8Bit44KHz		MakeSoftSoundPlayer2Ch8Bit44KHz
#define NS_MakeSoftSoundPlayer2Ch8Bit22KHz		MakeSoftSoundPlayer2Ch8Bit22KHz
#define NS_MakeSoftSoundPlayer1Ch16Bit44KHz		MakeSoftSoundPlayer1Ch16Bit44KHz
#define NS_MakeSoftSoundPlayer1Ch16Bit22KHz		MakeSoftSoundPlayer1Ch16Bit22KHz
#define NS_MakeSoftSoundPlayer1Ch8Bit44KHz		MakeSoftSoundPlayer1Ch8Bit44KHz
#define NS_MakeSoftSoundPlayer1Ch8Bit22KHz		MakeSoftSoundPlayer1Ch8Bit22KHz
#define NS_MakeSoftSoundPlayerCustom			MakeSoftSoundPlayerCustom
#define NS_DeleteSoftSoundPlayer				DeleteSoftSoundPlayer
#define NS_AddDataSoftSoundPlayer				AddDataSoftSoundPlayer
#define NS_AddDirectDataSoftSoundPlayer			AddDirectDataSoftSoundPlayer
#define NS_AddOneDataSoftSoundPlayer			AddOneDataSoftSoundPlayer
#define NS_GetSoftSoundPlayerFormat				GetSoftSoundPlayerFormat
#define NS_StartSoftSoundPlayer					StartSoftSoundPlayer
#define NS_CheckStartSoftSoundPlayer			CheckStartSoftSoundPlayer
#define NS_StopSoftSoundPlayer					StopSoftSoundPlayer
#define NS_ResetSoftSoundPlayer					ResetSoftSoundPlayer
#define NS_GetStockDataLengthSoftSoundPlayer	GetStockDataLengthSoftSoundPlayer
#define NS_CheckSoftSoundPlayerNoneData			CheckSoftSoundPlayerNoneData


// �l�h�c�h����֐�
#define NS_DeleteMusicMem						DeleteMusicMem
#define NS_LoadMusicMem							LoadMusicMem
#define NS_LoadMusicMemWithStrLen				LoadMusicMemWithStrLen
#define NS_LoadMusicMemByMemImage				LoadMusicMemByMemImage
#define NS_LoadMusicMemByResource				LoadMusicMemByResource
#define NS_LoadMusicMemByResourceWithStrLen		LoadMusicMemByResourceWithStrLen
#define NS_PlayMusicMem							PlayMusicMem
#define NS_StopMusicMem							StopMusicMem
#define NS_CheckMusicMem						CheckMusicMem
#define NS_SetVolumeMusicMem					SetVolumeMusicMem
#define NS_GetMusicMemPosition					GetMusicMemPosition
#define NS_InitMusicMem							InitMusicMem
#define NS_ProcessMusicMem						ProcessMusicMem

#define NS_PlayMusic							PlayMusic
#define NS_PlayMusicWithStrLen					PlayMusicWithStrLen
#define NS_PlayMusicByMemImage					PlayMusicByMemImage
#define NS_PlayMusicByResource					PlayMusicByResource
#define NS_PlayMusicByResourceWithStrLen		PlayMusicByResourceWithStrLen
#define NS_SetVolumeMusic						SetVolumeMusic
#define NS_StopMusic							StopMusic
#define NS_CheckMusic							CheckMusic
#define NS_GetMusicPosition						GetMusicPosition

#define NS_SelectMidiMode						SelectMidiMode

#endif // DX_NON_SOUND










// DxArchive_.cpp �֐� �v���g�^�C�v�錾
#define NS_SetUseDXArchiveFlag					SetUseDXArchiveFlag
#define NS_SetDXArchivePriority					SetDXArchivePriority
#define NS_SetDXArchivePriorityWithStrLen		SetDXArchivePriorityWithStrLen
#define NS_SetDXArchiveExtension				SetDXArchiveExtension
#define NS_SetDXArchiveExtensionWithStrLen		SetDXArchiveExtensionWithStrLen
#define NS_SetDXArchiveKeyString				SetDXArchiveKeyString
#define NS_SetDXArchiveKeyStringWithStrLen		SetDXArchiveKeyStringWithStrLen

#define NS_DXArchivePreLoad						DXArchivePreLoad
#define NS_DXArchivePreLoadWithStrLen			DXArchivePreLoadWithStrLen
#define NS_DXArchiveCheckIdle					DXArchiveCheckIdle
#define NS_DXArchiveCheckIdleWithStrLen			DXArchiveCheckIdleWithStrLen
#define NS_DXArchiveRelease						DXArchiveRelease
#define NS_DXArchiveReleaseWithStrLen			DXArchiveReleaseWithStrLen
#define NS_DXArchiveCheckFile					DXArchiveCheckFile
#define NS_DXArchiveCheckFileWithStrLen			DXArchiveCheckFileWithStrLen
#define NS_DXArchiveSetMemImage					DXArchiveSetMemImage
#define NS_DXArchiveSetMemImageWithStrLen		DXArchiveSetMemImageWithStrLen
#define NS_DXArchiveReleaseMemImage				DXArchiveReleaseMemImage
















// DxLive2DCubism4.cpp �֐� �v���g�^�C�v�錾

#ifndef DX_NON_LIVE2D_CUBISM4

#define NS_Live2D_SetCubism4CoreDLLPath							Live2D_SetCubism4CoreDLLPath
#define NS_Live2D_SetCubism4CoreDLLPathWithStrLen				Live2D_SetCubism4CoreDLLPathWithStrLen
#define NS_Live2D_SetCubism3CoreDLLPath							Live2D_SetCubism3CoreDLLPath
#define NS_Live2D_SetCubism3CoreDLLPathWithStrLen				Live2D_SetCubism3CoreDLLPathWithStrLen

#define NS_Live2D_RenderBegin									Live2D_RenderBegin
#define NS_Live2D_RenderEnd										Live2D_RenderEnd

#define NS_Live2D_LoadModel										Live2D_LoadModel
#define NS_Live2D_LoadModelWithStrLen							Live2D_LoadModelWithStrLen
#define NS_Live2D_DeleteModel									Live2D_DeleteModel
#define NS_Live2D_InitModel										Live2D_InitModel

#define NS_Live2D_SetUserShader									Live2D_SetUserShader
#define NS_Live2D_DrawCallback									Live2D_DrawCallback
#define NS_Live2D_SetUseAutoScaling								Live2D_SetUseAutoScaling
#define NS_Live2D_SetUseAutoCentering							Live2D_SetUseAutoCentering
#define NS_Live2D_SetUseReverseYAxis							Live2D_SetUseReverseYAxis

#define NS_Live2D_Model_Update									Live2D_Model_Update
#define NS_Live2D_Model_SetTranslate							Live2D_Model_SetTranslate
#define NS_Live2D_Model_SetExtendRate							Live2D_Model_SetExtendRate
#define NS_Live2D_Model_SetRotate								Live2D_Model_SetRotate
#define NS_Live2D_Model_Draw									Live2D_Model_Draw

#define NS_Live2D_Model_StartMotion								Live2D_Model_StartMotion
#define NS_Live2D_Model_StartMotionWithStrLen					Live2D_Model_StartMotionWithStrLen
#define NS_Live2D_Model_GetLastPlayMotionNo						Live2D_Model_GetLastPlayMotionNo
#define NS_Live2D_Model_IsMotionFinished						Live2D_Model_IsMotionFinished
#define NS_Live2D_Model_GetMotionPlayTime						Live2D_Model_GetMotionPlayTime
#define NS_Live2D_Model_SetExpression							Live2D_Model_SetExpression
#define NS_Live2D_Model_SetExpressionWithStrLen					Live2D_Model_SetExpressionWithStrLen
#define NS_Live2D_Model_HitTest									Live2D_Model_HitTest
#define NS_Live2D_Model_HitTestWithStrLen						Live2D_Model_HitTestWithStrLen

#define NS_Live2D_Model_GetParameterCount						Live2D_Model_GetParameterCount
#define NS_Live2D_Model_GetParameterId							Live2D_Model_GetParameterId
#define NS_Live2D_Model_GetParameterValue						Live2D_Model_GetParameterValue
#define NS_Live2D_Model_GetParameterValueWithStrLen				Live2D_Model_GetParameterValueWithStrLen
#define NS_Live2D_Model_SetParameterValue						Live2D_Model_SetParameterValue
#define NS_Live2D_Model_SetParameterValueWithStrLen				Live2D_Model_SetParameterValueWithStrLen

#define NS_Live2D_Model_GetHitAreasCount						Live2D_Model_GetHitAreasCount
#define NS_Live2D_Model_GetHitAreaName							Live2D_Model_GetHitAreaName
#define NS_Live2D_Model_GetPhysicsFileName						Live2D_Model_GetPhysicsFileName
#define NS_Live2D_Model_GetPoseFileName							Live2D_Model_GetPoseFileName
#define NS_Live2D_Model_GetExpressionCount						Live2D_Model_GetExpressionCount
#define NS_Live2D_Model_GetExpressionName						Live2D_Model_GetExpressionName
#define NS_Live2D_Model_GetExpressionFileName					Live2D_Model_GetExpressionFileName
#define NS_Live2D_Model_GetMotionGroupCount						Live2D_Model_GetMotionGroupCount
#define NS_Live2D_Model_GetMotionGroupName						Live2D_Model_GetMotionGroupName
#define NS_Live2D_Model_GetMotionCount							Live2D_Model_GetMotionCount
#define NS_Live2D_Model_GetMotionCountWithStrLen				Live2D_Model_GetMotionCountWithStrLen
#define NS_Live2D_Model_GetMotionFileName						Live2D_Model_GetMotionFileName
#define NS_Live2D_Model_GetMotionFileNameWithStrLen				Live2D_Model_GetMotionFileNameWithStrLen
#define NS_Live2D_Model_GetMotionSoundFileName					Live2D_Model_GetMotionSoundFileName
#define NS_Live2D_Model_GetMotionSoundFileNameWithStrLen		Live2D_Model_GetMotionSoundFileNameWithStrLen
#define NS_Live2D_Model_GetMotionFadeInTimeValue				Live2D_Model_GetMotionFadeInTimeValue
#define NS_Live2D_Model_GetMotionFadeInTimeValueWithStrLen		Live2D_Model_GetMotionFadeInTimeValueWithStrLen
#define NS_Live2D_Model_GetMotionFadeOutTimeValue				Live2D_Model_GetMotionFadeOutTimeValue
#define NS_Live2D_Model_GetMotionFadeOutTimeValueWithStrLen		Live2D_Model_GetMotionFadeOutTimeValueWithStrLen
#define NS_Live2D_Model_GetUserDataFile							Live2D_Model_GetUserDataFile
#define NS_Live2D_Model_GetEyeBlinkParameterCount				Live2D_Model_GetEyeBlinkParameterCount
#define NS_Live2D_Model_GetEyeBlinkParameterId					Live2D_Model_GetEyeBlinkParameterId
#define NS_Live2D_Model_GetLipSyncParameterCount				Live2D_Model_GetLipSyncParameterCount
#define NS_Live2D_Model_GetLipSyncParameterId					Live2D_Model_GetLipSyncParameterId		
#define NS_Live2D_Model_GetCanvasWidth							Live2D_Model_GetCanvasWidth
#define NS_Live2D_Model_GetCanvasHeight							Live2D_Model_GetCanvasHeight

#endif // DX_NON_LIVE2D_CUBISM4






#endif  // DX_THREAD_SAFE

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif

