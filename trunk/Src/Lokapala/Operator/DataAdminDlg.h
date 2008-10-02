#pragma once
#include "afxcmn.h"

#include "UserAdminDlg.h"
#include "SeatAdminDlg.h"
#include "RuleAdminDlg.h"

// CDataAdminDlg dialog

class CDataAdminDlg : public CDialog
{
private :
	void InitTabControl();
	void InitSubDialog();
	void CreateSubDialog();
	void InitTabCursor();
	void TerminateSubDialog();

	CUserAdminDlg *m_pUserDlg;
	CSeatAdminDlg *m_pSeatDlg;
	CRuleAdminDlg *m_pRuleDlg;

	DECLARE_DYNAMIC(CDataAdminDlg)

public:
	CDataAdminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataAdminDlg();

// Dialog Data
	enum { IDD = IDD_DATA_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	CTabCtrl m_tabCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangingDataAdminTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeDataAdminTab(NMHDR *pNMHDR, LRESULT *pResult);
};
