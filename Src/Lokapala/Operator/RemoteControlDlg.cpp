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


/**@brief	���õǾ��� ���� �ּҸ� ��� �´�.
 * @param	a_selectedIndex	�̰��� ���õ� �ּ��� ����Ʈ�ڽ������� �ε������� �־� �ش�.
 */
void CRemoteControlDlg::GetSelectedTarget(CArray<int> *a_selectedIndex)
{
	int selectedCount = m_targetList.GetSelCount();
	a_selectedIndex->SetSize(selectedCount);
	a_selectedIndex->SetSize(selectedCount);
	m_targetList.GetSelItems(selectedCount, a_selectedIndex->GetData());
}

// CRemoteControlDlg message handlers
/**@brief	Ư�� ���μ��� ����
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

/**@brief	Ư�� ���μ��� ����
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

/**@brief	������� ��� ���μ��� ����
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

/**@brief	����� ��ǻ�� ����
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

/**@brief	����� ��ǻ�� ������
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

/**@brief	����� �α׾ƿ�
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

/**@brief	���� �ð��� YYYY.MM.DD/HH:MM:SS �������� ��ȯ�Ѵ�.
 */
CString CRemoteControlDlg::GetTime()
{
	CTime nowTime = CTime::GetCurrentTime();
	CString nowTimeText;
	nowTimeText.Format(_T("%04d.%02d.%02d/%02d:%02d:%02d"), 
		nowTime.GetYear(), nowTime.GetMonth(), nowTime.GetDay(), nowTime.GetHour(), nowTime.GetMinute(), nowTime.GetSecond());

	return nowTimeText;
}

/**@brief	�������ͽ� ����
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

/**@brief	Terminate Raptor ��ư Ŭ��.
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


/**@brief	���̾�α� �ʱ�ȭ ��
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

/**@brief	�������ͽ� ��Ӵٿ� �ڽ��� ������ ���¸� �ִ´�.
 */
void CRemoteControlDlg::SetStatusOnControl()
{
	m_statusInput.AddString(_T("H/W defect"));
	m_statusInput.AddString(_T("S/W defect"));
	m_statusInput.AddString(_T("Repaired"));
	m_statusInput.AddString(_T("Verified"));
}

/**@brief	���̾�α� ����, ����ƽ ��Ʈ�� ���� ����
 */
HBRUSH CRemoteControlDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch( nCtlColor ) 
	{
	case CTLCOLOR_DLG :
		return (HBRUSH)CreateSolidBrush( RGB(255,255,255) ); // ���ϴ� �����ڵ带 �Է��Ѵ�.
		break;
	case CTLCOLOR_STATIC :
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(255,255,255));
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

/**@brief	Ÿ��Ʋ�� ���� ������ �� �ֵ��� �Ѵ�.
 */
void CRemoteControlDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialog::OnLButtonDown(nFlags, point);
}
