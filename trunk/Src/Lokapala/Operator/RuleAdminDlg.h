#pragma once


// CRuleAdminDlg dialog

class CRuleAdminDlg : public CDialog
{
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
};
