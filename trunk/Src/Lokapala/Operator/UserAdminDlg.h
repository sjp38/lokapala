#pragma once
#include "afxwin.h"


// CUserAdminDlg dialog

class CUserAdminDlg : public CDialog
{
private :
	void GetInputVariables(CString *a_name, CString *a_lowPassword, CString *a_highPassword, int *a_level);
	void SetInputVariables(void *a_user);


	DECLARE_DYNAMIC(CUserAdminDlg)

public:
	CUserAdminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserAdminDlg();

// Dialog Data
	enum { IDD = IDD_USER_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUserAdd();
	afx_msg void OnBnClickedUserDelete();

private :
	void ShowUsers();
public:
	virtual BOOL OnInitDialog();
	CEdit m_name;
	CEdit m_lowPassword;
	CEdit m_highPassword;
	CEdit m_level;
	CListBox m_userList;
	afx_msg void OnLbnSelchangeUserlist();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
