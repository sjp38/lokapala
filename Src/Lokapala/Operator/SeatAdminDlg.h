#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "SeatsDataDTO.h"


// CSeatAdminDlg dialog

class CSeatAdminDlg : public CDialog
{
private :
	void SetSeats();
	void GetInputVariables(CString *a_globalIp, CString *a_localIp, int *a_x, int *a_y, CString *a_nickname);
	void SetInputVariables(CSeatDataDTO *a_seat);
	void ShowSeats();
	DECLARE_DYNAMIC(CSeatAdminDlg)

public:
	CSeatAdminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSeatAdminDlg();

// Dialog Data
	enum { IDD = IDD_SEAT_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	virtual BOOL OnInitDialog();
	CEdit m_maxX;
	CEdit m_maxY;
	CEdit m_x;
	CEdit m_y;
	CIPAddressCtrl m_globalIp;
	CIPAddressCtrl m_localIp;
	CEdit m_nickname;
	CListBox m_seatList;
	afx_msg void OnLbnSelchangeSeatlist();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
