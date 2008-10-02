// SeatAdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "SeatAdminDlg.h"

#include "SeatsDataDTO.h"


// CSeatAdminDlg dialog

IMPLEMENT_DYNAMIC(CSeatAdminDlg, CDialog)

CSeatAdminDlg::CSeatAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeatAdminDlg::IDD, pParent)
{

}

CSeatAdminDlg::~CSeatAdminDlg()
{
}

void CSeatAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSeatAdminDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD, &CSeatAdminDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CSeatAdminDlg::OnBnClickedDelete)
END_MESSAGE_MAP()


// CSeatAdminDlg message handlers

/**@brief	Add 버튼을 클릭	*/
void CSeatAdminDlg::OnBnClickedAdd()
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

/**@brief	Delete 버튼을 클릭	*/
void CSeatAdminDlg::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
	int x = GetDlgItemInt(IDC_X);
	int y = GetDlgItemInt(IDC_Y);
	CCBFMediator::Instance()->DeleteSeat(x,y);

	ShowSeats();
}

/**@brief	현재 좌석 정보를 보여 준다.	*/
void CSeatAdminDlg::ShowSeats()
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

BOOL CSeatAdminDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ShowSeats();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
