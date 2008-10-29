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
}


BEGIN_MESSAGE_MAP(CRuleAdminDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD_RULE, &CRuleAdminDlg::OnBnClickedAddRule)
	ON_BN_CLICKED(IDC_DELETE_RULE, &CRuleAdminDlg::OnBnClickedDeleteRule)
END_MESSAGE_MAP()


// CRuleAdminDlg message handlers

/**@brief	add ��ư Ŭ��	*/
void CRuleAdminDlg::OnBnClickedAddRule()
{
	// TODO: Add your control notification handler code here
	CString processName;
	GetDlgItemTextW(IDC_PROCESS_NAME, processName);

	CString caption;
	GetDlgItemTextW(IDC_TITLE, caption);

	CString targetSeat;
	GetDlgItemTextW(IDC_TARGET_SEAT, targetSeat);

	CString targetUser;
	GetDlgItemTextW(IDC_TARGET_USER, targetUser);

	CComboBox *pcomboBox = (CComboBox *)GetDlgItem(IDC_REACTION);
	enum Reactions reaction = (enum Reactions)pcomboBox->GetCurSel();

	CString reactionArgument;
	GetDlgItemTextW(IDC_ARGUMENT, reactionArgument);

	CRuleDataDTO rule(processName, caption, targetSeat, targetUser, reaction, reactionArgument);
	CCBFMediator::Instance()->AddRule( (void *)&rule );

	ShowRules();
}

/**@brief	delete ��ư Ŭ��	*/
void CRuleAdminDlg::OnBnClickedDeleteRule()
{
	// TODO: Add your control notification handler code here
	CString processName;
	GetDlgItemTextW(IDC_PROCESS_NAME, processName);

	CString caption;
	GetDlgItemTextW(IDC_TITLE, caption);

	CString targetSeat;
	GetDlgItemTextW(IDC_TARGET_SEAT, targetSeat);

	CString targetUser;
	GetDlgItemTextW(IDC_TARGET_USER, targetUser);

	CComboBox *pcomboBox = (CComboBox *)GetDlgItem(IDC_REACTION);
	enum Reactions reaction = (enum Reactions)pcomboBox->GetCurSel();

	CString reactionArgument;
	GetDlgItemTextW(IDC_ARGUMENT, reactionArgument);


	CRuleDataDTO rule(processName, caption, targetSeat, targetUser, reaction, reactionArgument);
	CCBFMediator::Instance()->DeleteRule( (void *)&rule );

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
	pcomboBox->AddString(_T("Genocide Processes"));
	pcomboBox->AddString(_T("Warn"));
}


/**@brief	���� ���� ���̾�α׿� �����ش�.
 */
void CRuleAdminDlg::ShowRules()
{
	CListBox *pListBox = (CListBox *)GetDlgItem(IDC_RULELIST);
	pListBox->ResetContent();

	CRulesDataDTO *pRulesData = (CRulesDataDTO *)CCBFMediator::Instance()->GetRules();

	for(int i=0; i<pRulesData->m_rules.GetCount(); i++)
	{
		CRuleDataDTO rule = pRulesData->m_rules[i];
		CString reaction;
		reaction.Format(_T("%d"),rule.m_reaction);
		pListBox->AddString(rule.m_processName+_T("/")+rule.m_caption+_T("(")+rule.m_targetSeatId+_T("/")+rule.m_targetUserId+_T(")")
			+reaction+_T("/")+rule.m_reactionArgument);
	}
}