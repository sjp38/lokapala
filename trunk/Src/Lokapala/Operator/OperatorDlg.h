// OperatorDlg.h : header file
//

#pragma once
#include "afxwin.h"


// COperatorDlg dialog
class COperatorDlg : public CDialog
{
// Construction
public:
	COperatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_OPERATOR_DIALOG };

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
	afx_msg LRESULT OnNotifyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowStatus(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtontest();
	afx_msg void OnBnClickedDataAdmin();
	CListBox m_notifyList;
	CListBox m_connectedList;
	CListBox m_criminalList;
};
