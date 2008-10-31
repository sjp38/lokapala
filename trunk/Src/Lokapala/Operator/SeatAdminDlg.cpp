// SeatAdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "SeatAdminDlg.h"


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
	DDX_Control(pDX, IDC_MAXX, m_maxX);
	DDX_Control(pDX, IDC_MAXY, m_maxY);
	DDX_Control(pDX, IDC_X, m_x);
	DDX_Control(pDX, IDC_Y, m_y);
	DDX_Control(pDX, IDC_GLOBALIP, m_globalIp);
	DDX_Control(pDX, IDC_LOCALIP, m_localIp);
	DDX_Control(pDX, IDC_NICKNAME, m_nickname);
	DDX_Control(pDX, IDC_SEATLIST, m_seatList);
}


BEGIN_MESSAGE_MAP(CSeatAdminDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD, &CSeatAdminDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CSeatAdminDlg::OnBnClickedDelete)
	ON_LBN_SELCHANGE(IDC_SEATLIST, &CSeatAdminDlg::OnLbnSelchangeSeatlist)
END_MESSAGE_MAP()


// CSeatAdminDlg message handlers

/**@brief	좌석 정보의 최대 크기를 다시 설정한다.
 */
void CSeatAdminDlg::SetSeats()
{
	CString maxX, maxY;
	m_maxX.GetWindowTextW(maxX);
	m_maxY.GetWindowTextW(maxY);

	if(_ttoi(maxX) > 0 && _ttoi(maxY) > 0)
	{
		CCBFMediator::Instance()->SetSeats(_ttoi(maxX), _ttoi(maxY));
	}
}

/**@brief	다이얼로그에 입력된 값들을 읽는다.
 */
void CSeatAdminDlg::GetInputVariables(CString *a_globalIp, CString *a_localIp, int *a_x, int *a_y, CString *a_nickname)
{
	CString value;
	m_x.GetWindowTextW(value);
	*a_x = _ttoi(value);
	m_y.GetWindowTextW(value);
	*a_y = _ttoi(value);

	m_globalIp.GetWindowTextW(*a_globalIp);
	m_localIp.GetWindowTextW(*a_localIp);

	m_nickname.GetWindowTextW(*a_nickname);
}

/**@brief	특정 좌석 정보를 입력 창에 뿌린다.
 */
void CSeatAdminDlg::SetInputVariables(CSeatDataDTO *a_seat)
{
	CString value;
	value.Format(_T("%d"), a_seat->m_position.x);
	m_x.SetWindowTextW(value);
	value.Format(_T("%d"), a_seat->m_position.y);
	m_y.SetWindowTextW(value);

	CString hostAddress = a_seat->m_hostAddress;
	int tokenIndex=0;
	
	m_globalIp.SetWindowTextW( hostAddress.Tokenize(_T("/"), tokenIndex) );
	m_localIp.SetWindowTextW( hostAddress.Tokenize(_T("/"), tokenIndex) );

	m_nickname.SetWindowTextW(a_seat->m_nickname);
}

/**@brief	Add 버튼을 클릭	*/
void CSeatAdminDlg::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
	SetSeats();
	CString globalIp, localIp, nickname;
	int x,y;
	GetInputVariables(&globalIp, &localIp, &x, &y, &nickname);

	CString hostAddress = globalIp + _T("/") + localIp;

	CSeatDataDTO seat(hostAddress, x, y, nickname);
	CCBFMediator::Instance()->AddSeat( (void *)&seat );

	ShowSeats();
}

/**@brief	Delete 버튼을 클릭	*/
void CSeatAdminDlg::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_seatList.GetSelCount();

	CString id;
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_seatList.GetSelItems(selectedCount, selectedIndex.GetData());
	for(int i=0; i<selectedCount; i++)
	{
		m_seatList.GetText(selectedIndex[i], id);
		int tokenIndex = 0;
		id = id.Tokenize(_T(":"),tokenIndex);
		CCBFMediator::Instance()->DeleteSeat(&id);		
	}
	ShowSeats();
}

/**@brief	현재 좌석 정보를 보여 준다.	*/
void CSeatAdminDlg::ShowSeats()
{
	m_seatList.ResetContent();

	CSeatsDataDTO *pSeatsData = (CSeatsDataDTO *)CCBFMediator::Instance()->GetSeats();

	POSITION pos = pSeatsData->m_seats.GetStartPosition();
	CString key;
	CSeatDataDTO value;
	while(pos != NULL)
	{
		pSeatsData->m_seats.GetNextAssoc(pos, key, value);
		CString seatDisplay;

		CString hostAddress = value.m_hostAddress;
		int tokenIndex=0;
		CString globalIp = hostAddress.Tokenize(_T("/"), tokenIndex);
		CString localIp = hostAddress.Tokenize(_T("/"), tokenIndex);
		seatDisplay = globalIp + _T("/") + localIp + _T(":") + value.m_nickname;
		m_seatList.AddString(seatDisplay);
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

/**@brief	좌석 리스트에서 좌석을 선택했을 때.
 */
void CSeatAdminDlg::OnLbnSelchangeSeatlist()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_seatList.GetSelCount();
	if(selectedCount == 0)
	{
		return;
	}
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_seatList.GetSelItems(selectedCount, selectedIndex.GetData());
	int selected = selectedIndex[0];
	
	CString seatId;
	m_seatList.GetText(selected, seatId);
	selected=0;
	seatId = seatId.Tokenize(_T(":"), selected);

	CSeatsDataDTO *seatData = (CSeatsDataDTO *)CCBFMediator::Instance()->GetSeats();
	CSeatDataDTO *seat = seatData->GetSeatById(seatId);
	SetInputVariables(seat);
}
