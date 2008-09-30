// CSeatInfoAdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "SeatInfoAdminDlg.h"

#include "SeatsDataDTO.h"


// CSeatInfoAdminDlg dialog

IMPLEMENT_DYNAMIC(CSeatInfoAdminDlg, CDialog)

CSeatInfoAdminDlg::CSeatInfoAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeatInfoAdminDlg::IDD, pParent)
{

}

CSeatInfoAdminDlg::~CSeatInfoAdminDlg()
{
}

void CSeatInfoAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSeatInfoAdminDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD, &CSeatInfoAdminDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CSeatInfoAdminDlg::OnBnClickedDelete)
END_MESSAGE_MAP()

/**@brief	Add 버튼 클릭	*/
void CSeatInfoAdminDlg::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
	int maxX = GetDlgItemInt(IDC_MAXX);
	int maxY = GetDlgItemInt(IDC_MAXY);
	if(maxX > 0 && maxY > 0)
	{
		CCBFMediator::Instance()->SetSeats(maxX, maxY);
	}
	int x = GetDlgItemInt(IDC_X);
	int y = GetDlgItemInt(IDC_Y);

	CString globalIp, localIp;
	GetDlgItemTextW(IDC_GLOBALIP, globalIp);
	GetDlgItemTextW(IDC_LOCALIP, localIp);

	CString nickname;
	GetDlgItemTextW(IDC_NICKNAME, nickname);

	CSeatDataDTO seat(globalIp, localIp, x, y, nickname);
	CCBFMediator::Instance()->AddSeat( (void *)&seat );

	ShowSeats();
}

/**@brief	Delete 버튼 클릭	*/
void CSeatInfoAdminDlg::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
	int x = GetDlgItemInt(IDC_X);
	int y = GetDlgItemInt(IDC_Y);
	CCBFMediator::Instance()->DeleteSeat(x,y);

	ShowSeats();
}


/**@brief	현재 좌석 정보를 보여 준다.	*/
void CSeatInfoAdminDlg::ShowSeats()
{
	CListBox *pListBox = (CListBox *)GetDlgItem(IDC_SEATLIST);
	pListBox->ResetContent();

	CSeatsDataDTO *pSeatsData = (CSeatsDataDTO *)CCBFMediator::Instance()->GetSeats();

	POSITION pos = pSeatsData->m_seats.GetStartPosition();
	CString key;
	CSeatDataDTO value;
	while(pos != NULL)
	{
		pSeatsData->m_seats.GetNextAssoc(pos, key, value);
		CString seatDisplay;
		seatDisplay = value.m_globalIp+_T("/")+value.m_localIp+_T(":")+value.m_nickname;
		pListBox->AddString(seatDisplay);
	}
}
BOOL CSeatInfoAdminDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ShowSeats();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
