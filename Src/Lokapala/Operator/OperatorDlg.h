// OperatorDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "SeatsDisplayDTO.h"


// COperatorDlg dialog
class COperatorDlg : public CDialog
{
private :
	bool m_imageListSetted;
	CImageList m_stateImage;
	CSeatsDisplayDTO m_seatsDisplayData;

	void Notify(CString a_message);
	void NotifyConnected(CString a_message);
	void NotifyCriminal(CString a_message);

	void InitiallizeStatusListCtrl();
	
	int GetIconIndexBySeatId(CString a_seatId);

	void DisplayChangedSeatSize(int a_maxX, int a_maxY);
	void DisplayAddedSeat(CString a_seatId);
	void DisplayDeletedSeat(CString a_seatId);

	void DisplayIconAsLogin(CString a_seatId);
	void DisplayIconAsLogout(CString a_seatId);
	void DisplayIconAsNormal(CString a_seatId);	
	void DisplayIconAsAbnormal(CString a_seatId);
	void DisplayIconAsAttention(CString a_seatId);

	void GetSelectedIconSeatId(CArray<CString> *a_target);



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
	afx_msg LRESULT OnOptionClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnControlClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessengerClick(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCmdExecute();
	CListBox m_notifyList;
	CListBox m_connectedList;
	CListBox m_criminalList;
	CEdit m_command;
	CListCtrl m_stateDisplayList;
	afx_msg void OnLvnItemchangedStateDisplay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickStateDisplay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRemoteControl();
	afx_msg void OnSetSeat();
	afx_msg void OnBnClickedControl();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStnClickedSidebar();
};
