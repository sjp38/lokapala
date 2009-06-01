// StatusReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Raptor.h"
#include "StatusReportDlg.h"

#include "StatusReportsDTO.h"


// CStatusReportDlg dialog

IMPLEMENT_DYNAMIC(CStatusReportDlg, CDialog)

CStatusReportDlg::CStatusReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatusReportDlg::IDD, pParent)
{

}

CStatusReportDlg::~CStatusReportDlg()
{
}

void CStatusReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS, m_statusCtrl);
	DDX_Control(pDX, IDC_COMMENT, m_commentCtrl);
	DDX_Control(pDX, IDC_STATUS_LIST, m_statusList);
}


BEGIN_MESSAGE_MAP(CStatusReportDlg, CDialog)
	ON_BN_CLICKED(IDC_REPORT, &CStatusReportDlg::OnBnClickedReport)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CStatusReportDlg message handlers

BOOL CStatusReportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetStatusOnControl();
	DisplayStatusReports();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


/**@brief	스테이터스 콤보박스에 스테이터스 종류를 채워 넣는다.
 */
void CStatusReportDlg::SetStatusOnControl()
{
	m_statusCtrl.AddString(_T("H/W defect"));
	m_statusCtrl.AddString(_T("S/W defect"));
	m_statusCtrl.AddString(_T("Repaired"));
	m_statusCtrl.AddString(_T("Verified"));
}

/**@brief	현재 시간을 스테이터스 보고 형식에 맞게 맞춰서 문자열을 리턴한다.
 */
CString CStatusReportDlg::GetTime()
{
	CTime nowTime = CTime::GetCurrentTime();
	CString nowTimeText;
	nowTimeText.Format(_T("%04d.%02d.%02d/%02d:%02d:%02d"), 
		nowTime.GetYear(), nowTime.GetMonth(), nowTime.GetDay(), nowTime.GetHour(), nowTime.GetMinute(), nowTime.GetSecond());

	return nowTimeText;
}

/**@brief	스테이터스 보고 버튼을 눌렀을 때.
 */
void CStatusReportDlg::OnBnClickedReport()
{
	// TODO: Add your control notification handler code here
	enum State state = (enum State)m_statusCtrl.GetCurSel();
	CString date = GetTime();
	CString comment;
	m_commentCtrl.GetWindowTextW(comment);

	CStatusReportDTO report(state, date, comment);

	CCBFMediator::Instance()->AddStatusReport(&report);
	CCBFMediator::Instance()->ReportStatus(&report);

	DisplayStatusReports();
}


/**@brief	리스트박스에 현재 상태를 보여준다.
 */
void CStatusReportDlg::DisplayStatusReports()
{
	m_statusList.ResetContent();
	CStatusReportsDTO *statusReportsData = (CStatusReportsDTO *)CCBFMediator::Instance()->GetStatusReports();
	CStatusReportDTOArray statusReports;
	statusReportsData->GetReportFrom(_T(""), &statusReports);
	for(int i=0; i<statusReports.GetCount(); i++)
	{
		CStatusReportDTO statusReport = statusReports[i];
		CString state;
		switch(statusReport.m_state)
		{
		case HW_DEFECT :
			state = _T("HW_DEFECT");
			break;
		case SW_DEFECT :
			state = _T("SW_DEFECT");
			break;
		case REPAIRED :
			state = _T("REPAIRED");
			break;
		case VERIFIED :
			state = _T("VERIFIED");
			break;
		}
		CString message = _T("[") + statusReport .m_date + _T("]") + state + _T(" : ") + statusReport.m_comment;
		m_statusList.AddString( message );	

		static int maxSize = 0;
		CDC *pDc = m_statusList.GetDC();
		int messageSize = (pDc->GetTextExtent(message)).cx;
		if(maxSize < messageSize)
		{
			maxSize = messageSize;
			m_statusList.SetHorizontalExtent(maxSize);
			m_statusList.ReleaseDC(pDc);
		}		
	}
}

/**@brief	배경색 하얗게 수정
 */
HBRUSH CStatusReportDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch( nCtlColor ) 
	{
	case CTLCOLOR_DLG :
		return (HBRUSH)CreateSolidBrush( RGB(255,255,255) ); // 원하는 색상코드를 입력한다.
		break;
	case CTLCOLOR_STATIC :
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(255,255,255));
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

/**@brief	프레임 없는 상태에서 윈도우 이동 가능하도록
 */
void CStatusReportDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default	
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CDialog::OnLButtonDown(nFlags, point);
}
