#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "Resource.h"


// CLoginDlg dialog

class CLoginDlg : public CDialog
{
private :
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDlg();

// Dialog Data
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoginBtn();
	CEdit m_nameEdit;
	CEdit m_lowPassEdit;
	CEdit m_highPassEdit;
	CIPAddressCtrl m_operatorIPAddress;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedDisconnect();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
};
