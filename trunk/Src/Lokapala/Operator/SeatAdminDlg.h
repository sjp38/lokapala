#pragma once


// CSeatAdminDlg dialog

class CSeatAdminDlg : public CDialog
{
private :
	void ShowSeats();
	DECLARE_DYNAMIC(CSeatAdminDlg)

public:
	CSeatAdminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSeatAdminDlg();

// Dialog Data
	enum { IDD = IDD_SEAT_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	virtual BOOL OnInitDialog();
};
