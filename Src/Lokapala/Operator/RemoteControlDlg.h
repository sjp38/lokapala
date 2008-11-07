#pragma once
#include "afxwin.h"


// CRemoteControlDlg dialog

class CRemoteControlDlg : public CDialog
{
public :
	CArray<CString> m_selectedTarget;

	DECLARE_DYNAMIC(CRemoteControlDlg)

public:
	CRemoteControlDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRemoteControlDlg();

// Dialog Data
	enum { IDD = IDD_REMOTE_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_targetList;
	CEdit m_argumentInput;
	afx_msg void OnBnClickedExecuteProcess();
	afx_msg void OnBnClickedKillProcess();
	afx_msg void OnBnClickedGenocideProcesses();
	afx_msg void OnBnClickedShutdown();
	afx_msg void OnBnClickedReboot();
	afx_msg void OnBnClickedLogout();
	virtual BOOL OnInitDialog();
};