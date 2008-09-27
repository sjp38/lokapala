#pragma once


// CUserAdminDlg dialog

class CUserAdminDlg : public CDialog
{
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
};
