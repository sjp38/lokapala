// RemoteControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "RemoteControlDlg.h"

#include "ConnectedHostsDTO.h"
#include "ControlActionDTO.h"
#include "StatusReportsDTO.h"


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
	DDX_Control(pDX, IDC_STATUS, m_statusInput);
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
	ON_BN_CLICKED(IDC_STATUS_REPORT, &CRemoteControlDlg::OnBnClickedStatusReport)
	ON_BN_CLICKED(IDC_TERMINATE_RAPTOR, &CRemoteControlDlg::OnBnClickedTerminateRaptor)
END_MESSAGE_MAP()


/**@brief	선택되어진 목적 주소를 얻어 온다.
 * @param	a_selectedIndex	이곳에 선택된 주소의 리스트박스에서의 인덱스들을 넣어 준다.
 */
void CRemoteControlDlg::GetSelectedTarget(CArray<int> *a_selectedIndex)
{
	int selectedCount = m_targetList.GetSelCount();
	a_selectedIndex->SetSize(selectedCount);
	a_selectedIndex->SetSize(selectedCount);
	m_targetList.GetSelItems(selectedCount, a_selectedIndex->GetData());
}

// CRemoteControlDlg message handlers
/**@brief	특정 프로세스 실행
 */
void CRemoteControlDlg::OnBnClickedExecuteProcess()
{
	// TODO: Add your control notification handler code here
	CArray<int> selectedIndex;
	GetSelectedTarget(&selectedIndex);

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->ExecuteHostProcess(&action);
		//CCBFMediator::Instance()->SendExecuteProcessInstruction(&action);
	}
}

/**@brief	특정 프로세스 종료
 */
void CRemoteControlDlg::OnBnClickedKillProcess()
{
	// TODO: Add your control notification handler code here
	CArray<int> selectedIndex;
	GetSelectedTarget(&selectedIndex);

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->KillHostProcess(&action);
		//CCBFMediator::Instance()->SendKillProcessInstruction(&action);
	}
}

/**@brief	사용자의 모든 프로세스 종료
 */
void CRemoteControlDlg::OnBnClickedGenocideProcesses()
{
	// TODO: Add your control notification handler code here
	CArray<int> selectedIndex;
	GetSelectedTarget(&selectedIndex);

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->GenocideHostProcess(&action);
		//CCBFMediator::Instance()->SendGenocideProcessInstruction(&action);
	}
}

/**@brief	사용자 컴퓨터 종료
 */
void CRemoteControlDlg::OnBnClickedShutdown()
{
	// TODO: Add your control notification handler code here
	CArray<int> selectedIndex;
	GetSelectedTarget(&selectedIndex);

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->ShutdownHost(&action);
		//CCBFMediator::Instance()->SendShutdownInstruction(&action);
	}
}

/**@brief	사용자 컴퓨터 리부팅
 */
void CRemoteControlDlg::OnBnClickedReboot()
{
	// TODO: Add your control notification handler code here
	CArray<int> selectedIndex;
	GetSelectedTarget(&selectedIndex);

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->RebootHost(&action);
		//CCBFMediator::Instance()->SendRebootInstruction(&action);
	}
}

/**@brief	사용자 로그아웃
 */
void CRemoteControlDlg::OnBnClickedLogout()
{
	// TODO: Add your control notification handler code here
	CArray<int> selectedIndex;
	GetSelectedTarget(&selectedIndex);

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->BanUser(&action);
		//CCBFMediator::Instance()->SendBanUserInstruction(&action);
	}
}

/**@brief	현재 시각을 YYYY.MM.DD/HH:MM:SS 포맷으로 반환한다.
 */
CString CRemoteControlDlg::GetTime()
{
	CTime nowTime = CTime::GetCurrentTime();
	CString nowTimeText;
	nowTimeText.Format(_T("%04d.%02d.%02d/%02d:%02d:%02d"), 
		nowTime.GetYear(), nowTime.GetMonth(), nowTime.GetDay(), nowTime.GetHour(), nowTime.GetMinute(), nowTime.GetSecond());

	return nowTimeText;
}

/**@brief	스테이터스 보고
 */
void CRemoteControlDlg::OnBnClickedStatusReport()
{
	// TODO: Add your control notification handler code here
	CArray<int> selectedIndex;
	GetSelectedTarget(&selectedIndex);

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CString targetAddress;
		m_targetList.GetText(selectedIndex[i], targetAddress);
		CString comment;
		m_argumentInput.GetWindowTextW(comment);

		enum State state = (enum State)m_statusInput.GetCurSel();
		CString date = GetTime();

		CStatusReportDTO report(targetAddress, state, date, comment);
		CStatusReportsDTO *statusReportsData = (CStatusReportsDTO *)CCBFMediator::Instance()->GetStatusReports();
		statusReportsData->AddReport(&report);
		CCBFMediator::Instance()->SubmitStatusReportToHost(&report);
	}
}

/**@brief	Terminate Raptor 버튼 클릭.
 */
void CRemoteControlDlg::OnBnClickedTerminateRaptor()
{
	// TODO: Add your control notification handler code here
	CArray<int> selectedIndex;
	GetSelectedTarget(&selectedIndex);

	for(int i=0; i<selectedIndex.GetCount(); i++)
	{
		CControlActionDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->BanUser(&action);
		
		CCBFMediator::Instance()->TerminateRaptorOnHost(&action);
	}
}


/**@brief	다이얼로그 초기화 시
 */
BOOL CRemoteControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CConnectedHostsDTO *connectedHostsData = (CConnectedHostsDTO *)CCBFMediator::Instance()->GetConnectedHosts();

	for(int i=0; i<connectedHostsData->m_connected.GetCount(); i++)
	{
		m_targetList.AddString(connectedHostsData->m_connected[i].m_hostAddress);
	}

	for(int i=0; i<m_selectedTarget.GetCount(); i++)
	{
		int selected = m_targetList.FindString(0, m_selectedTarget[i]);
		m_targetList.SetSel(selected);
	}

	SetStatusOnControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/**@brief	스테이터스 드롭다운 박스에 선택할 상태를 넣는다.
 */
void CRemoteControlDlg::SetStatusOnControl()
{
	m_statusInput.AddString(_T("H/W defect"));
	m_statusInput.AddString(_T("S/W defect"));
	m_statusInput.AddString(_T("Repaired"));
	m_statusInput.AddString(_T("Verified"));
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
