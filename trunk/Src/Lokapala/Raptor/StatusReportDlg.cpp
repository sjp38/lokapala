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
	CStatusReportsDTO *statusReports = (CStatusReportsDTO *)CCBFMediator::Instance()->GetStatusReports();
	statusReports->AddReport(&report);

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
		m_statusList.AddString( _T("[") + statusReport .m_date + _T("]") + state + _T(" : ") + statusReport.m_comment);	
	}
}