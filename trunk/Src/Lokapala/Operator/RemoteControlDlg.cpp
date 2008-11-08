// RemoteControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "RemoteControlDlg.h"

#include "ConnectedHostsDTO.h"
#include "ControlActionDTO.h"


// CRemoteControlDlg dialog

IMPLEMENT_DYNAMIC(CRemoteControlDlg, CDialog)

CRemoteControlDlg::CRemoteControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemoteControlDlg::IDD, pParent)
{

}

CRemoteControlDlg::~CRemoteControlDlg()
{
}

void CRemoteControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TARGET, m_targetList);
	DDX_Control(pDX, IDC_ARGUMENT, m_argumentInput);
}


BEGIN_MESSAGE_MAP(CRemoteControlDlg, CDialog)
	ON_BN_CLICKED(IDC_EXECUTE_PROCESS, &CRemoteControlDlg::OnBnClickedExecuteProcess)
	ON_BN_CLICKED(IDC_KILL_PROCESS, &CRemoteControlDlg::OnBnClickedKillProcess)
	ON_BN_CLICKED(IDC_GENOCIDE_PROCESSES, &CRemoteControlDlg::OnBnClickedGenocideProcesses)
	ON_BN_CLICKED(IDC_SHUTDOWN, &CRemoteControlDlg::OnBnClickedShutdown)
	ON_BN_CLICKED(IDC_REBOOT, &CRemoteControlDlg::OnBnClickedReboot)
	ON_BN_CLICKED(IDC_LOGOUT, &CRemoteControlDlg::OnBnClickedLogout)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRemoteControlDlg message handlers
/**@brief	특정 프로세스 실행
 */
void CRemoteControlDlg::OnBnClickedExecuteProcess()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_targetList.GetSelCount();
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_targetList.GetSelItems(selectedCount, selectedIndex.GetData());

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->ExecuteUser(&action);
	}
}

/**@brief	특정 프로세스 종료
 */
void CRemoteControlDlg::OnBnClickedKillProcess()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_targetList.GetSelCount();
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_targetList.GetSelItems(selectedCount, selectedIndex.GetData());

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->KillUser(&action);
	}
}

/**@brief	사용자의 모든 프로세스 종료
 */
void CRemoteControlDlg::OnBnClickedGenocideProcesses()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_targetList.GetSelCount();
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_targetList.GetSelItems(selectedCount, selectedIndex.GetData());

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->GenocideUser(&action);
	}
}

/**@brief	사용자 컴퓨터 종료
 */
void CRemoteControlDlg::OnBnClickedShutdown()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_targetList.GetSelCount();
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_targetList.GetSelItems(selectedCount, selectedIndex.GetData());

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->ShutdownUser(&action);
	}
}

/**@brief	사용자 컴퓨터 리부팅
 */
void CRemoteControlDlg::OnBnClickedReboot()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_targetList.GetSelCount();
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_targetList.GetSelItems(selectedCount, selectedIndex.GetData());

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->RebootUser(&action);
	}
}

/**@brief	사용자 로그아웃
 */
void CRemoteControlDlg::OnBnClickedLogout()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_targetList.GetSelCount();
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_targetList.GetSelItems(selectedCount, selectedIndex.GetData());

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->LogoutUser(&action);
	}
}

/**@brief	다이얼로그 초기화 시
 */
BOOL CRemoteControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CConnectedHostsDTO *connectedHostsData = (CConnectedHostsDTO *)CCBFMediator::Instance()->GetConnectedUsers();

	for(int i=0; i<connectedHostsData->m_connected.GetCount(); i++)
	{
		m_targetList.AddString(connectedHostsData->m_connected[i].m_hostAddress);
	}

	for(int i=0; i<m_selectedTarget.GetCount(); i++)
	{
		int selected = m_targetList.FindString(0, m_selectedTarget[i]);
		m_targetList.SetSel(selected);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/**@brief	다이얼로그 배경색, 스태틱 컨트롤 배경색 조정
 */
HBRUSH CRemoteControlDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch( nCtlColor ) 
	{
	case CTLCOLOR_DLG :
		return (HBRUSH)CreateSolidBrush( RGB(255,255,255) ); // 원하는 색상코드를 입력한다.
		break;
	case CTLCOLOR_STATIC :
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(255,255,255));
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

/**@brief	타이틀바 없이 움직일 수 있도록 한다.
 */
void CRemoteControlDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialog::OnLButtonDown(nFlags, point);
}
