#pragma once
#include "afxwin.h"


// CMessengerDlg dialog

class CMessengerDlg : public CDialog
{
public :
	void DisplayConversation(CString a_message);
private :
	DECLARE_DYNAMIC(CMessengerDlg)

public:
	CMessengerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMessengerDlg();

// Dialog Data
	enum { IDD = IDD_MESSENGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_conversationBox;
	CListBox m_connectedList;
	CEdit m_input;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSend();
	virtual BOOL OnInitDialog();
};
