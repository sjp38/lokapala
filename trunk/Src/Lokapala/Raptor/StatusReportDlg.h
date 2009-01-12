#pragma once
#include "afxwin.h"


// CStatusReportDlg dialog

class CStatusReportDlg : public CDialog
{
private :
	CString GetTime();
	void SetStatusOnControl();
	void DisplayStatusReports();
	DECLARE_DYNAMIC(CStatusReportDlg)

public:
	CStatusReportDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStatusReportDlg();

// Dialog Data
	enum { IDD = IDD_STATUS_REPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_statusCtrl;
	virtual BOOL OnInitDialog();
	CEdit m_commentCtrl;
	afx_msg void OnBnClickedReport();
	CListBox m_statusList;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
