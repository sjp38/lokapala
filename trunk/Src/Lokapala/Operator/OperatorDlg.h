// OperatorDlg.h : header file
//

#pragma once


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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtontest();
	afx_msg void OnBnClickedUserAdmin();
	afx_msg void OnBnClickedSeatAdmin();
	afx_msg void OnBnClickedRuleAdmin();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedSave();
};
