#pragma once


// CDataAdminDlg dialog

class CDataAdminDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataAdminDlg)

public:
	CDataAdminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataAdminDlg();

// Dialog Data
	enum { IDD = IDD_DATA_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUserAdmin();
	afx_msg void OnBnClickedSeatAdmin();
	afx_msg void OnBnClickedRuleAdmin();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
};
