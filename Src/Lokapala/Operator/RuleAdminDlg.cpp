// RuleAdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "RuleAdminDlg.h"

#include "RulesDataDTO.h"


// CRuleAdminDlg dialog

IMPLEMENT_DYNAMIC(CRuleAdminDlg, CDialog)

CRuleAdminDlg::CRuleAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleAdminDlg::IDD, pParent)
{	
}

CRuleAdminDlg::~CRuleAdminDlg()
{
}

BOOL CRuleAdminDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetRulesOnControl();
	ShowRules();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRuleAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TARGET_SEAT, m_targetSeat);
	DDX_Control(pDX, IDC_TARGET_USER, m_targetUser);
	DDX_Control(pDX, IDC_TARGET_LEVEL, m_targetLevel);
	DDX_Control(pDX, IDC_PROCESS_NAME, m_processName);
	DDX_Control(pDX, IDC_TITLE, m_title);
	DDX_Control(pDX, IDC_REACTION, m_reaction);
	DDX_Control(pDX, IDC_ARGUMENT, m_argument);
	DDX_Control(pDX, IDC_RULELIST, m_ruleList);
}


BEGIN_MESSAGE_MAP(CRuleAdminDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD_RULE, &CRuleAdminDlg::OnBnClickedAddRule)
	ON_BN_CLICKED(IDC_DELETE_RULE, &CRuleAdminDlg::OnBnClickedDeleteRule)
	ON_LBN_SELCHANGE(IDC_RULELIST, &CRuleAdminDlg::OnLbnSelchangeRulelist)
END_MESSAGE_MAP()


// CRuleAdminDlg message handlers

/**@brief	���̾�α��� �Է°����� �о���δ�.
 */
void CRuleAdminDlg::GetInputVariables(CString *a_processName, CString *a_caption,
								  CString *a_targetSeat, CString *a_targetUser, int *a_targetLevel,
								  int *a_reaction, CString *a_reactionArgument)
{
	m_processName.GetWindowTextW(*a_processName);	
	m_title.GetWindowTextW(*a_caption);

	m_targetSeat.GetWindowTextW(*a_targetSeat);
	m_targetUser.GetWindowTextW(*a_targetUser);
	CString level;
	m_targetLevel.GetWindowTextW(level);
	*a_targetLevel = _ttoi(level);

	*a_reaction = m_reaction.GetCurSel();
	m_argument.GetWindowTextW(*a_reactionArgument);
}

/**@brief	���̾�α��� �Է� ���� Ư�� ��Ģ�� ������ ����ִ´�.
 * @param	a_pos	RulesDataDTO ���� RuleDataDTO �迭���� �ε��� ��.
 */
void CRuleAdminDlg::SetInputVariables(int a_pos)
{
	CRulesDataDTO *rulesData = (CRulesDataDTO *)CCBFMediator::Instance()->GetRules();
	CRuleDataDTO rule = rulesData->m_rules[a_pos];

	m_processName.SetWindowTextW(rule.m_processName);
	m_title.SetWindowTextW(rule.m_caption);
	m_targetSeat.SetWindowTextW(rule.m_targetSeatId);
	m_targetUser.SetWindowTextW(rule.m_targetUserId);

	CString value;
	value.Format(_T("%d"), rule.m_targetLevel);
	m_targetLevel.SetWindowTextW(value);
	m_reaction.SetCurSel((int)rule.m_reaction);
	m_argument.SetWindowTextW(rule.m_reactionArgument);
}

/**@brief	add ��ư Ŭ��	*/
void CRuleAdminDlg::OnBnClickedAddRule()
{
	// TODO: Add your control notification handler code here
	CString processName, caption;
	CString targetSeat, targetUser;
	int targetLevel;
	enum Reactions reaction;
	CString reactionArgument;
	
	GetInputVariables(&processName, &caption, &targetSeat, &targetUser, &targetLevel, (int *)&reaction, &reactionArgument);
	CRuleDataDTO rule(processName, caption, targetSeat, targetUser, targetLevel, reaction, reactionArgument);
	CCBFMediator::Instance()->AddRule( (void *)&rule );

	ShowRules();
}

/**@brief	delete ��ư Ŭ��	*/
void CRuleAdminDlg::OnBnClickedDeleteRule()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_ruleList.GetSelCount();

	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_ruleList.GetSelItems(selectedCount, selectedIndex.GetData());
	
	CRulesDataDTO *rulesData = (CRulesDataDTO *)CCBFMediator::Instance()->GetRules();
	for(int i=selectedCount-1; i>=0; i--)
	{
		rulesData->DeleteRule(selectedIndex[i]);		
	}
	ShowRules();
}


/**@brief	���׼� �޺��ڽ� ��Ʈ�ѿ� ���û����� ä���.	*/
void CRuleAdminDlg::SetRulesOnControl()
{
	CComboBox *pcomboBox = (CComboBox *)GetDlgItem(IDC_REACTION);
	pcomboBox->AddString(_T("ShutDown"));
	pcomboBox->AddString(_T("Reboot"));
	pcomboBox->AddString(_T("Logout"));
	pcomboBox->AddString(_T("Execute"));
	pcomboBox->AddString(_T("Kill"));
	pcomboBox->AddString(_T("Genocide Processes"));
	pcomboBox->AddString(_T("Warn"));
}


/**@brief	���� ���� ���̾�α׿� �����ش�.
 */
void CRuleAdminDlg::ShowRules()
{
	m_ruleList.ResetContent();

	CRulesDataDTO *pRulesData = (CRulesDataDTO *)CCBFMediator::Instance()->GetRules();

	for(int i=0; i<pRulesData->m_rules.GetCount(); i++)
	{
		CRuleDataDTO rule = pRulesData->m_rules[i];
		CString reaction;
		reaction.Format(_T("%d"),rule.m_reaction);
		m_ruleList.AddString(rule.m_processName+_T("/")+rule.m_caption+_T("(")+rule.m_targetSeatId+_T("/")+rule.m_targetUserId+_T(")")
			+reaction+_T("/")+rule.m_reactionArgument);
	}
}

/**@brief	����Ʈ�ڽ����� �� ���� ��
 */
void CRuleAdminDlg::OnLbnSelchangeRulelist()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_ruleList.GetSelCount();
	if(selectedCount == 0)
	{
		return;
	}
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_ruleList.GetSelItems(selectedCount, selectedIndex.GetData());
	int selected = selectedIndex[0];

	SetInputVariables(selected);
}
