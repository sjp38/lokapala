#pragma once


// CSeatInfoAdminDlg dialog

class CSeatInfoAdminDlg : public CDialog
{
	DECLARE_DYNAMIC(CSeatInfoAdminDlg)

public:
	CSeatInfoAdminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSeatInfoAdminDlg();

// Dialog Data
	enum { IDD = IDD_SEAT_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();

private :
	void ShowSeats();
};
