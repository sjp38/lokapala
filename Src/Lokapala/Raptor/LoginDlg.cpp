// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Raptor.h"
#include "LoginDlg.h"

#include "UserDTO.h"
#include "StatusReportsDTO.h"


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
	DDX_Control(pDX, IDC_LIST1, m_statusList);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDC_LOGIN_BTN, &CLoginDlg::OnBnClickedLoginBtn)
	ON_BN_CLICKED(IDC_CONNECT, &CLoginDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, &CLoginDlg::OnBnClickedDisconnect)
	ON_WM_DESTROY()
	ON_MESSAGE(LKPLM_STATUS_CHANGED, &CLoginDlg::OnStatusChanged)
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
	CFile file;
	if( file.Open(_T("operatorAddress.cfg"), CFile::modeRead) )
	{
		DWORD address;
		file.Read(&address, sizeof(address));
		m_operatorIPAddress.SetAddress(address);
		file.Close();
	}	

	DWORD serverIp;
	m_operatorIPAddress.GetAddress(serverIp);
	CCBFMediator::Instance()->InitiallizeCommunication(serverIp);	

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


/**@brief	현재 컴퓨터의 상태를 알린다.
 */
void CLoginDlg::NotifyStatus(CString a_message)
{
	m_statusList.AddString(a_message);

	static int maxSize;
	CDC* pDc = m_statusList.GetDC();
	int messageSize = (pDc->GetTextExtent(a_message)).cx;

	if( maxSize < messageSize )
	{
		maxSize = messageSize;
		m_statusList.SetHorizontalExtent(maxSize);
		m_statusList.ReleaseDC(pDc);		
	}

	m_statusList.SetCurSel(m_statusList.GetCount()-1);	
}

/**@brief	LKPLM_STATSU_CHANGED 메세지 핸들러. 상태 변경 시 호출된다.
 */
LRESULT CLoginDlg::OnStatusChanged(WPARAM wParam, LPARAM lParam)
{
	CStatusReportDTO statusReport = *(CStatusReportDTO *)wParam;

	CString state;
	switch(statusReport.m_state)
	{
	case HW_DEFECT :
		state = _T("HW_DEFECT");
		break;
	case SW_DEFECT :
		state = _T("SW_DEFECT");
		break;
	case REPAIRED :
		state = _T("REPAIRED");
		break;
	case VERIFIED :
		state = _T("VERIFIED");
		break;
	}
	NotifyStatus( _T("[") + statusReport .m_date + _T("]") + state + _T(" : ") + statusReport.m_comment);

	return 0;
}