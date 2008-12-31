// RaptorDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CRaptorDlg dialog
class CRaptorDlg : public CDialog
{
private :
	void Notify(CString a_message);

// Construction
public:
	CRaptorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RAPTOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnectbutton();
	afx_msg void OnBnClickedStartneverdieTest();
	afx_msg void OnBnClickedStopneverdieTest();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnStartObservation();
	afx_msg void OnStopObservation();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedStatusReport();
	afx_msg LRESULT OnStatusChanged(WPARAM wParam, LPARAM lParam);
	CEdit m_input;
	CListBox m_notifyList;
	afx_msg void OnDestroy();
};
