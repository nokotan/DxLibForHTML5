// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		��������̓v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.24b
// 
// -------------------------------------------------------------------------------

#ifndef DX_INPUTSTRING_H
#define DX_INPUTSTRING_H

#include "DxCompileConfig.h"

#ifndef DX_NON_INPUTSTRING

// �C���N���[�h ------------------------------------------------------------------
#include "DxLib.h"

#ifndef DX_NON_KEYEX
#include "Windows/DxDirectX.h"
#include "Windows/DxGuid.h"
#endif // DX_NON_KEYEX

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

#define CHARBUFFER_SIZE				(1024)				// �����R�[�h�o�b�t�@�e��

// �\���̒�` --------------------------------------------------------------------

#ifndef DX_NON_KEYEX

// �N���X��` --------------------------------------------------------------------

// TSF�����p�N���X
//class DX_UIElementSink : public D_ITfUIElementSink, public D_ITfInputProcessorProfileActivationSink, public D_ITfCompartmentEventSink
class DX_UIElementSink : public D_ITfUIElementSink
{
public:
	DX_UIElementSink();
	~DX_UIElementSink();

	// IUnknown
	HRESULT __stdcall QueryInterface	( REFIID riid, void **ppvObj ) ;
	ULONG	__stdcall AddRef			( void ) ;
	ULONG	__stdcall Release			( void ) ;

	// ITfUIElementSink
	//   Notifications for Reading Window events. We could process candidate as well, but we'll use IMM for simplicity sake.
	HRESULT	__stdcall BeginUIElement	( DWORD dwUIElementId, BOOL *pbShow ) ;
	HRESULT	__stdcall UpdateUIElement	( DWORD dwUIElementId ) ;
	HRESULT	__stdcall EndUIElement		( DWORD dwUIElementId ) ;

//	// ITfInputProcessorProfileActivationSink
//	//   Notification for keyboard input locale change
//	HRESULT __stdcall OnActivated		( DWORD dwProfileType, LANGID langid, REFCLSID clsid, REFGUID catid, REFGUID guidProfile, HKL hkl, DWORD dwFlags ) ;
//
//	// ITfCompartmentEventSink
//	//    Notification for open mode (toggle state) change
//	HRESULT __stdcall OnChange			( REFGUID rguid ) ;

private:
	LONG RefCount ;
} ;

// ��������͒��f�[�^�\����
struct INPUTDATA
{
	int						UseFlag ;							// �g�p�����t���O

	int						ID ;								// �G���[�`�F�b�N�Ɏg�p����h�c

	int						EndFlag ;							// ���͂��I�����Ă��邩�t���O
	int						CancellFlag ;						// ���͂��L�����Z�����ꂽ���̃t���O

//	RECT					DrawRect ;							// �`��̈�

	int						StrLength ;							// ���͒�������̒���
	int						MaxStrLength ;						// ������̍ő咷( Unicode�ł̏ꍇ�� wchar_t �̐��A�}���`�o�C�g������ł̏ꍇ�� char �̐� )
	int						SelectStart ;						// �I��͈͊J�n�ʒu
	int						SelectEnd ;							// �I��͈͏I���ʒu
	int						DrawStartPos ;						// �`����J�n����ʒu
	int						Point ;								// �J�[�\���̈ʒu
	wchar_t *				Buffer ;							// ���s���ɕҏW���镶����o�b�t�@
	char *					TempBuffer ;						// Buffer ���}���`�o�C�g������ɂ������̂��i�[���邽�߂̃o�b�t�@
	size_t					TempBufferBytes ;					// TempBuffer �̃T�C�Y
//	char					*DestBuffer ;						// ���͏I�����ɓ]�����镶����o�b�t�@�ւ̃|�C���^

	int						CancelValidFlag ;					// �L�����Z���L���t���O
	int						SingleCharOnlyFlag ;				// �_�u���o�C�g�����͈���Ȃ����t���O
	int						NumCharOnlyFlag ;					// ���p�p���������g��Ȃ����t���O
	int						DoubleCharOnlyFlag ;				// �_�u���o�C�g������������Ȃ����t���O
	int						EnableNewLineFlag ;					// ���s�������邩�t���O

	int						DrawAreaValidFlag ;					// �`��\�͈͂��L�����ǂ����̃t���O
	RECT					DrawArea ;							// �`��\�͈�
} ;

#endif // DX_NON_KEYEX

// �����R�[�h�o�b�t�@�\����
struct CHARBUFFER
{
#ifndef UNICODE
	char					TempStock[ 16 ] ;					// �Q�o�C�g������ StockInputChar �ɓn���ꂽ�ꍇ�ɂP�o�C�g�ڂ����ł� wchar_t �ɕϊ��ł��Ȃ��̂ŁA�Q�o�C�g�ڂ��n�����܂ł̈ꎞ�ۑ��p�ϐ�
	int						TempStockNum ;						// TempStock �ɑ������Ă���L���ȃo�C�g��

	char					TempGetStock[ 16 ] ;				// �Q�o�C�g������ GetInputChar �Ŏ擾�����Ƃ��� wchar_t ���� char �ɕϊ�������A��x�� GetInputChar �ł͖߂�l�Ƃ��ēn���Ȃ��̂ŁAwchar_t ���� char �ɕϊ�������������ꎞ�I�ɕۑ����邽�߂̕ϐ�
	int						TempGetStockNum ;					// TempGetStock �ɑ������Ă���L���ȃo�C�g��
#endif // UNICODE

	wchar_t					CharBuffer[ CHARBUFFER_SIZE + 1 ] ;	// ���͂��ꂽ������
	int						StPoint , EdPoint ;					// �����O�o�b�t�@�p�|�C���^

	wchar_t					SecondString[CHARBUFFER_SIZE + 1 ] ;
	int						IMEInputFlag ;						// ���͏��������A�t���O
	int						InputPoint ;						// ���͒��̕ҏW�������̈ʒu
	wchar_t					InputString[ CHARBUFFER_SIZE + 1 ] ;// �h�l�d�ɂ����͒��̕�����
	wchar_t					InputTempString[ CHARBUFFER_SIZE + 1 ] ;// �h�l�d�ɂ����͒��̕�����̃e���|�����o�b�t�@
	PCANDIDATELIST			CandidateList ;						// �ϊ����̃��X�g�f�[�^
	int						CandidateListSize ;					// �ϊ����̃��X�g�f�[�^�ɕK�v�ȃf�[�^�e��
	int						IMEUseFlag ;						// �h�l�d�̎g�p���
	int						IMEUseFlag_System ;					// �h�l�d�̎g�p���( �c�w���C�u���������p )
	int						IMEUseFlag_OSSet ;					// �n�r�ɑ΂��Đݒ肵�Ă���h�l�d�̎g�p���
	HIMC					IMEContext ;						// �h�l�d�̓��̓R���e�L�X�g
	int						IMESwitch ;							// �h�l�d�̋N�����
	int						IMEInputStringMaxLengthIMESync ;	// �h�l�d�œ��͂ł���ő啶������ MakeKeyInput �̍ő吔�ɓ��������邩�ǂ���( TRUE:����������  FALSE:�����Ȃ� )
	int						IMEInputMaxLength ;					// �h�l�d�ň�x�ɓ��͂ł��镶����( 0:���ɐ����Ȃ�  1�ȏ�:���������� )
	int						IMERefreshStep ;					// �h�l�d�̓��͕����񃊃t���b�V���p�X�e�b�v�ϐ�
	IMEINPUTDATA			*IMEInputData ;						// �h�l�d�̓��͒��̏��( ���[�U�[�p )
	int						TSFNotUseFlag ;						// �h�l�d�̕ϊ����\���� TSF ���g�p���Ȃ����ǂ����̃t���O

	int						IMEProcessNum ;						// �h�l�d�̕����擾�v���Z�X�ԍ�
	int						ClauseData[ 1024 ] ;				// ���߃f�[�^
	int						ClauseNum ;							// ���ߐ�
	BYTE					CharAttr[ 1024 ] ;					// �e�����̑������
	int						CharAttrNum ;						// �e�����̑������̗v�f��
	int						ChangeFlag ;						// �h�l�d���͂ɕω������������t���O

	DWORD					NormalStrColor ;					// ���͕�����̐F
	DWORD					NormalStrEdgeColor ;				// ���͕�����̉��̐F
	DWORD					NormalCursorColor ;					// �h�l�d���g�p���̃J�[�\���̐F
	DWORD					SelectStrColor ;					// �I�����ꂽ���͕�����̐F
	DWORD					SelectStrEdgeColor ;				// �I�����ꂽ���͕�����̉��̐F
	DWORD					SelectStrBackColor ;				// �I�����ꂽ���͕�����̔w�i�̐F
	DWORD					IMEStrColor ;						// �h�l�d�g�p���̓��͕�����̐F
	DWORD					IMEStrEdgeColorEnable ;				// IMEStrEdgeColor ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	DWORD					IMEStrEdgeColor ;					// �h�l�d�g�p���̓��͕�����̉��̐F
	DWORD					IMEStrBackColor ;					// �h�l�d�g�p���̓��͕�����̎���̐F
	DWORD					IMECursorColor ;					// �h�l�d�g�p���̃J�[�\���̐F
	DWORD					IMELineColor ;						// �h�l�d�g�p���̕ϊ�������̉���
	DWORD					IMESelectStrColor ;					// �h�l�d�g�p���̑I��Ώۂ̕ϊ���╶����̐F
	DWORD					IMESelectStrEdgeColorEnable ;		// IMESelectStrEdgeColor ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	DWORD					IMESelectStrEdgeColor ;				// �h�l�d�g�p���̑I��Ώۂ̕ϊ���╶����̉��̐F
	DWORD					IMESelectStrBackColor ;				// �h�l�d�g�p���̑I��Ώۂ̕ϊ���╶����̎���̐F
	DWORD					IMEConvWinStrColor ;				// �h�l�d�g�p���̕ϊ����E�C���h�E���̕�����̐F
	DWORD					IMEConvWinStrEdgeColor ;			// �h�l�d�g�p���̕ϊ����E�C���h�E���̕�����̉��̐F
	DWORD					IMEConvWinSelectStrColor ;			// �h�l�d�g�p���̕ϊ����E�C���h�E���őI�����Ă��镶����̐F
	DWORD					IMEConvWinSelectStrEdgeColor ;		// �h�l�d�g�p���̕ϊ����E�C���h�E���őI�����Ă��镶����̉��̐F
	DWORD					IMEConvWinSelectStrBackColorEnable ;// IMEConvWinSelectStrBackColor ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	DWORD					IMEConvWinSelectStrBackColor ;		// �h�l�d�g�p���̕ϊ����E�C���h�E���őI�����Ă��镶����̎���̐F
	DWORD					IMEConvWinEdgeColor ;				// �h�l�d�g�p���̕ϊ����E�C���h�E�̉��̐F
	DWORD					IMEConvWinBackColor ;				// �h�l�d�g�p���̕ϊ����E�C���h�E�̉��n�̐F
	DWORD					IMEModeStrColor ;					// �h�l�d�g�p���̓��̓��[�h������̐F(�u�S�p�Ђ炪�ȁv��)
	DWORD					IMEModeStrEdgeColor ;				// �h�l�d�g�p���̓��̓��[�h������̉��̐F

	int						EndCharaMode ;						// ��������͏����̓��͕����������E�ɒB���Ă����ԂŁA������̖��[�����œ��͂��s��ꂽ�ꍇ�̏������[�h( DX_KEYINPSTR_ENDCHARAMODE_OVERWRITE �� )
	
	int						CBrinkFlag ;						// �J�[�\����_�ł����邩�A�t���O
	int						CBrinkCount ;						// �J�[�\����_�ł�����ꍇ�̃J�E���^
	int						CBrinkWait ;						// �J�[�\���̓_�ł̑��x
	int						CBrinkDrawFlag ;					// �J�[�\����`�悷�邩�ǂ����̃t���O

	int						ActiveInputHandle ;					// ���͂��A�N�e�B�u�ɂȂ��Ă�����̓n���h��
	int						UseFontHandle ;						// ������`��Ɏg�p����t�H���g�̃n���h��(-1�Ńf�t�H���g�̃n���h��)
#ifndef DX_NON_KEYEX
	INPUTDATA				InputData[ MAX_INPUT_NUM ] ;		// �C���v�b�g�f�[�^
	int						HandleID ;							// �n���h���Ɋ��蓖�Ă�h�c

	D_ITfThreadMgrEx		*ITfThreadMgrEx ;
	DX_UIElementSink		*TsfSink ;
	int						TsfCandidateRefCount ;
	DWORD					TsfElementSinkCookie ;
#endif
} ;

// ���̓��[�h�\����
struct INPUTMODE
{
	DWORD					InputState ;						// ���̓��[�h�l
	wchar_t					InputName[ 16 ] ;					// ���̓��[�h�l�[��
} ;

// �e�[�u��-----------------------------------------------------------------------

// ���z�L�[�R�[�h���R���g���[�������R�[�h�ɕϊ����邽�߂̃e�[�u��
extern char CtrlCode[ 10 ][ 2 ] ;

// �������ϐ��錾 --------------------------------------------------------------

// ��������̓f�[�^
extern CHARBUFFER CharBuf ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �����R�[�h�o�b�t�@����֌W
extern	int			InitializeInputCharBuf( void ) ;										// �����R�[�h�o�b�t�@�֌W�̏�����
extern	int			TerminateInputCharBuf( void ) ;											// �����R�[�h�o�b�t�@�֌W�̌�n��
#ifndef DX_NON_KEYEX
extern	LRESULT		IMEProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) ;			// �h�l�d���b�Z�[�W�̃R�[���o�b�N�֐�
extern	void		RefreshIMEFlag( int Always = FALSE ) ;										// �h�l�d���g�p���邩�ǂ����̏�Ԃ��X�V����
#endif


// wchar_t�Ŋ֐�
#ifndef DX_NON_INPUTSTRING
extern	int			StockInputChar_WCHAR_T(		wchar_t CharCode ) ;
extern	wchar_t		GetInputChar_WCHAR_T(		int DeleteFlag ) ;
extern	wchar_t		GetInputCharWait_WCHAR_T(	int DeleteFlag ) ;
extern	int			GetOneChar_WCHAR_T(			wchar_t *CharBuffer, int DeleteFlag ) ;
extern	int			GetOneCharWait_WCHAR_T(		wchar_t *CharBuffer, int DeleteFlag ) ;
extern	int			GetCtrlCodeCmp_WCHAR_T(		wchar_t Char ) ;
#endif // DX_NON_INPUTSTRING

extern	int			GetStringPoint_WCHAR_T(				const wchar_t *String, int Point ) ;
extern	int			GetStringPoint2_WCHAR_T(			const wchar_t *String, int Point ) ;
extern	int			GetStringLength_WCHAR_T(			const wchar_t *String ) ;

#ifndef DX_NON_FONT
extern	int			DrawObtainsString_WCHAR_T(			int x, int y,                                                   int AddY, const wchar_t *String, int StrLen, unsigned int StrColor, unsigned int StrEdgeColor = 0 , int FontHandle = -1 , unsigned int SelectBackColor = 0xffffffff , unsigned int SelectStrColor = 0 , unsigned int SelectStrEdgeColor = 0xffffffff , int SelectStart = -1 , int SelectEnd = -1 , int DrawFlag = TRUE, int *PosX = NULL, int *PosY = NULL ) ;
extern	int			DrawObtainsString_CharClip_WCHAR_T(	int x, int y, int EnableExRate, double ExRateX, double ExRateY, int AddY, const wchar_t *String, int StrLen, unsigned int StrColor, unsigned int StrEdgeColor = 0 , int FontHandle = -1 , unsigned int SelectBackColor = 0xffffffff , unsigned int SelectStrColor = 0 , unsigned int SelectStrEdgeColor = 0xffffffff , int SelectStart = -1 , int SelectEnd = -1 , int DrawFlag = TRUE, int *PosX = NULL, int *PosY = NULL ) ;
#endif // DX_NON_FONT

#ifndef DX_NON_KEYEX
extern	int			InputStringToCustom_WCHAR_T(		int x, int y, size_t BufLength, wchar_t *StrBuffer, int CancelValidFlag, int SingleCharOnlyFlag, int NumCharOnlyFlag, int DoubleCharOnlyFlag = FALSE , int EnableNewLineFlag = FALSE , int DisplayCandidateList = TRUE ) ;
extern	int			KeyInputString_WCHAR_T(				int x, int y, size_t CharMaxLength, wchar_t *StrBuffer, int CancelValidFlag ) ;
extern	int			KeyInputSingleCharString_WCHAR_T(	int x, int y, size_t CharMaxLength, wchar_t *StrBuffer, int CancelValidFlag ) ;
extern	int			GetIMEInputModeStr_WCHAR_T(			wchar_t *GetBuffer ) ;
extern	int			SetIMEInputString_WCHAR_T(			const wchar_t *String ) ;
extern	int			SetKeyInputString_WCHAR_T(			const wchar_t *String, int InputHandle ) ;
extern	int			GetKeyInputString_WCHAR_T(			wchar_t *StrBuffer,    int InputHandle ) ;
#endif // DX_NON_KEYEX



#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_INPUTSTRING

#endif // DX_INPUTSTRING_H