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


/**@brief	�������ͽ� �޺��ڽ��� �������ͽ� ������ ä�� �ִ´�.
 */
void CStatusReportDlg::SetStatusOnControl()
{
	m_statusCtrl.AddString(_T("H/W defect"));
	m_statusCtrl.AddString(_T("S/W defect"));
	m_statusCtrl.AddString(_T("Repaired"));
	m_statusCtrl.AddString(_T("Verified"));
}

/**@brief	���� �ð��� �������ͽ� ���� ���Ŀ� �°� ���缭 ���ڿ��� �����Ѵ�.
 */
CString CStatusReportDlg::GetTime()
{
	CTime nowTime = CTime::GetCurrentTime();
	CString nowTimeText;
	nowTimeText.Format(_T("%04d.%02d.%02d/%02d:%02d:%02d"), 
		nowTime.GetYear(), nowTime.GetMonth(), nowTime.GetDay(), nowTime.GetHour(), nowTime.GetMinute(), nowTime.GetSecond());

	return nowTimeText;
}

/**@brief	�������ͽ� ���� ��ư�� ������ ��.
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


/**@brief	����Ʈ�ڽ��� ���� ���¸� �����ش�.
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

/**@brief	���� �Ͼ�� ����
 */
HBRUSH CStatusReportDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch( nCtlColor ) 
	{
	case CTLCOLOR_DLG :
		return (HBRUSH)CreateSolidBrush( RGB(255,255,255) ); // ���ϴ� �����ڵ带 �Է��Ѵ�.
		break;
	case CTLCOLOR_STATIC :
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(255,255,255));
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

/**@brief	������ ���� ���¿��� ������ �̵� �����ϵ���
 */
void CStatusReportDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default	
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CDialog::OnLButtonDown(nFlags, point);
}
