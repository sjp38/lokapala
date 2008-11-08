#pragma once
#include "afxwin.h"


// CRuleAdminDlg dialog

class CRuleAdminDlg : public CDialog
{

private :
	void GetInputVariables(CString *a_processName, CString *a_caption,
		CString *a_targetSeat, CString *a_targetUser, int *a_targetLevel,
		int *a_reaction, CString *a_reactionArgument);
	void SetInputVariables(int a_pos);
	DECLARE_DYNAMIC(CRuleAdminDlg)

public:
	CRuleAdminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRuleAdminDlg();

// Dialog Data
	enum { IDD = IDD_RULE_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddRule();
	afx_msg void OnBnClickedDeleteRule();

private :
	void SetRulesOnControl();
	void ShowRules();
public:
	virtual BOOL OnInitDialog();
	CEdit m_targetSeat;
	CEdit m_targetUser;
	CEdit m_targetLevel;
	CEdit m_processName;
	CEdit m_title;
	CComboBox m_reaction;
	CEdit m_argument;
	CListBox m_ruleList;
	afx_msg void OnLbnSelchangeRulelist();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
