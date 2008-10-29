// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Raptor.h"
#include "LoginDlg.h"

#include "UserDTO.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAME, m_nameEdit);
	DDX_Control(pDX, IDC_LOWPASS, m_lowPassEdit);
	DDX_Control(pDX, IDC_HIGHPASS, m_highPassEdit);
	DDX_Control(pDX, IDC_OPERATOR_IPADDRESS, m_operatorIPAddress);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDC_LOGIN_BTN, &CLoginDlg::OnBnClickedLoginBtn)
	ON_BN_CLICKED(IDC_CONNECT, &CLoginDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, &CLoginDlg::OnBnClickedDisconnect)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLoginDlg message handlers

/**@brief	로그인 버튼 클릭
 */
void CLoginDlg::OnBnClickedLoginBtn()
{
	// TODO: Add your control notification handler code here

	//오퍼레이터에게 접속
	DWORD serverIp;
	m_operatorIPAddress.GetAddress(serverIp);
	CCBFMediator::Instance()->InitiallizeCommunication(serverIp);

	//로그인 데이터 전송
	CString name;
	m_nameEdit.GetWindowTextW(name);
	CString lowPassword;
	m_lowPassEdit.GetWindowTextW(lowPassword);
	CString highPassword;
	m_highPassEdit.GetWindowTextW(highPassword);

	CUserDTO loginRequest(name, lowPassword, highPassword);
	CCBFMediator::Instance()->LoginRequest(&loginRequest);
}


/**@brief	오퍼레이터에게 접속 버튼 클릭
 */
void CLoginDlg::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here
	DWORD serverIp;
	m_operatorIPAddress.GetAddress(serverIp);
	CCBFMediator::Instance()->InitiallizeCommunication(serverIp);
}

/**@brief	오퍼레이터로부터 접속 취소 클릭
 */
void CLoginDlg::OnBnClickedDisconnect()
{
	// TODO: Add your control notification handler code here
	CString message = _T("Break connection from now operator");
	CCBFMediator::Instance()->Logout(&message);
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
			case VK_ESCAPE :
			case VK_RETURN :
				return TRUE;
			default :
				break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CLoginDlg::OnDestroy()
{
	if(CCBFMediator::Instance()->GetNeverDieState())
	{
		return;
		//WCHAR *selfPath = (WCHAR *)malloc(sizeof(WCHAR)*MAX_PATH);
		//GetModuleFileName(NULL,selfPath,MAX_PATH);
		//ShellExecute(NULL, _T("open"), selfPath, NULL, NULL, SW_SHOWNORMAL);
	}

	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}