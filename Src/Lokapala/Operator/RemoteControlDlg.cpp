// RemoteControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "RemoteControlDlg.h"

#include "SeatsDataDTO.h"
#include "ReactionArgumentDTO.h"


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
END_MESSAGE_MAP()


// CRemoteControlDlg message handlers
/**@brief	Ư�� ���μ��� ����
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
		CReactionArgumentDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->ExecuteUser(&action);
	}
}

/**@brief	Ư�� ���μ��� ����
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
		CReactionArgumentDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->KillUser(&action);
	}
}

/**@brief	������� ��� ���μ��� ����
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
		CReactionArgumentDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->GenocideUser(&action);
	}
}

/**@brief	����� ��ǻ�� ����
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
		CReactionArgumentDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->ShutdownUser(&action);
	}
}

/**@brief	����� ��ǻ�� ������
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
		CReactionArgumentDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->RebootUser(&action);
	}
}

/**@brief	����� �α׾ƿ�
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
		CReactionArgumentDTO action;
		m_targetList.GetText(selectedIndex[i], action.m_targetHostAddress);
		m_argumentInput.GetWindowTextW(action.m_reactionArgument);
		CCBFMediator::Instance()->LogoutUser(&action);
	}
}

/**@brief	���̾�α� �ʱ�ȭ ��
 */
BOOL CRemoteControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CSeatsDataDTO *seatData = (CSeatsDataDTO *)CCBFMediator::Instance()->GetSeats();
	CArray<CString> seats;
	seatData->GetEntireSeatId(&seats);

	for(int i=0; i<seats.GetCount(); i++)
	{
		m_targetList.AddString(seats[i]);
	}

	for(int i=0; i<m_selectedTarget.GetCount(); i++)
	{
		int selected = m_targetList.FindString(0, m_selectedTarget[i]);
		m_targetList.SetSel(selected);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
