// OperatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "OperatorDlg.h"

//������ ���� ���̾�α�
#include "DataAdminDlg.h"

#include "DisplayDTO.h"

#include "StatusReportsDTO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// COperatorDlg dialog




COperatorDlg::COperatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COperatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOTIFY_LIST, m_notifyList);
	DDX_Control(pDX, IDC_CONNECTED_LIST, m_connectedList);
	DDX_Control(pDX, IDC_CRIMINAL_LIST, m_criminalList);
	DDX_Control(pDX, IDC_COMMAND, m_command);
	DDX_Control(pDX, IDC_STATE_DISPLAY, m_stateDisplayList);
}

BEGIN_MESSAGE_MAP(COperatorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	
	ON_BN_CLICKED(IDC_CMD_EXECUTE, &COperatorDlg::OnBnClickedCmdExecute)
	ON_BN_CLICKED(IDC_DATA_ADMIN, &COperatorDlg::OnBnClickedDataAdmin)
	ON_MESSAGE(LKPLM_NOTIFYMESSAGE, &COperatorDlg::OnNotifyMessage)
	ON_MESSAGE(LKPLM_SHOWCHANGED, &COperatorDlg::OnShowChanged)
	ON_MESSAGE(LKPLM_SHOWSTATUS, &COperatorDlg::OnShowStatus)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_STATE_DISPLAY, &COperatorDlg::OnLvnItemchangedStateDisplay)
END_MESSAGE_MAP()


// COperatorDlg message handlers

BOOL COperatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CCBFMediator::Instance()->SetMainDlg(this);
	CCBFMediator::Instance()->BeginCommunication();
	InitiallizeStatusListCtrl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COperatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COperatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COperatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/**@brief	Ŀ�ǵ� ��ư Ŭ��	*/
void COperatorDlg::OnBnClickedCmdExecute()
{
	// TODO: Add your control notification handler code here
	CString message;
	m_command.GetWindowTextW(message);

	int selectedCount = m_connectedList.GetSelCount();

	if(selectedCount<=0)
	{
		CCBFMediator::Instance()->BroadcastTextMessage(message);
		return;
	}

	CString address;
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_connectedList.GetSelItems(selectedCount, selectedIndex.GetData());
	for(int i=0; i<selectedCount; i++)
	{
		m_connectedList.GetText(selectedIndex[i], address);
		CCBFMediator::Instance()->SendTextMessageTo(address, message);
	}
}




/**@brief	������ ���� ��ư Ŭ��
 */
void COperatorDlg::OnBnClickedDataAdmin()
{
	// TODO: Add your control notification handler code here
	CDataAdminDlg dataAdminDlg;
	dataAdminDlg.DoModal();
}


void COperatorDlg::Notify(CString a_message)
{
	m_notifyList.AddString(a_message);

	static int maxSize;
	CDC* pDc = m_notifyList.GetDC();
	int messageSize = (pDc->GetTextExtent(a_message)).cx;

	if( maxSize < messageSize )
	{
		maxSize = messageSize;
		m_notifyList.SetHorizontalExtent(maxSize);
		m_notifyList.ReleaseDC(pDc);		
	}

	m_notifyList.SetCurSel(m_notifyList.GetCount()-1);	
}


/**@brief	LKPLM_NOTIFYMESSAGE  �޼��� �ڵ鷯.
 *			���� ����Ʈ�ڽ��� �޼����� ����.
 */
LRESULT COperatorDlg::OnNotifyMessage(WPARAM wParam, LPARAM lParam)
{
	CString *notifyMessage = (CString *)( (void *)wParam );

	m_notifyList.AddString(*notifyMessage);

	static int maxSize;
	CDC* pDc = m_notifyList.GetDC();
	int messageSize = (pDc->GetTextExtent(*notifyMessage)).cx;

	if( maxSize < messageSize )
	{
		maxSize = messageSize;
		m_notifyList.SetHorizontalExtent(maxSize);
		m_notifyList.ReleaseDC(pDc);		
	}
	m_notifyList.SetCurSel(m_notifyList.GetCount()-1);
//	Notify(*notifyMessage);
	return 0;
}


/**@brief	LKPLM_SHOWCHANGED  �޼��� �ڵ鷯
 */
LRESULT COperatorDlg::OnShowChanged(WPARAM wParam, LPARAM lParam)
{
	CDisplayDTO *displayData = (CDisplayDTO *)wParam;

	UINT index = 0;
	switch(displayData->m_displayState)
	{
	case LOGIN :		
		Notify(displayData->m_seatId + _T(" login"));		
		m_connectedList.AddString(displayData->m_seatId);
		DisplayIconAsLogin(displayData->m_seatId);
		break;

	case LOGOUT :		
		index = m_connectedList.FindString(index, displayData->m_seatId);
		m_connectedList.DeleteString(index);
		Notify(displayData->m_seatId + _T(" logout"));
		DisplayIconAsLogout(displayData->m_seatId);
		break;
	case HW :
		Notify(displayData->m_seatId + _T(" reported H/W defect!"));
		DisplayIconAsAbnormal(displayData->m_seatId);
		break;
	case SW :
		Notify(displayData->m_seatId + _T(" reported h/w defect!"));
		DisplayIconAsAbnormal(displayData->m_seatId);
		break;
	case FINE :
		Notify(displayData->m_seatId + _T(" verified"));
		DisplayIconAsNormal(displayData->m_seatId);
		break;
	case CRIMINAL :
		Notify(displayData->m_seatId + _T(" have done limited process!"));
		DisplayIconAsAttention(displayData->m_seatId);
		break;
	case INNOCENT :
		Notify(displayData->m_seatId + _T(" have judged innocent"));
		DisplayIconAsAbnormal(displayData->m_seatId);
		break;
	case SEATADD :
		Notify(displayData->m_seatId + _T(" added"));
		DisplayAddedSeat(displayData->m_seatId);
		break;
	case SEATDELETE :
		Notify(displayData->m_seatId + _T(" deleted"));
		DisplayDeletedSeat(displayData->m_seatId);
	}

	return 0;
}

/**@brief	LKPLM_SHOWSTATUS  �޼��� �ڵ鷯
 */
LRESULT COperatorDlg::OnShowStatus(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


/**@brief	�¼� ��ȣ�� �ش� �¼��� ����Ʈ ��Ʈ�� �� �ε����� ���´�.
 */
int COperatorDlg::GetIconIndexBySeatId(CString a_seatId)
{
	CSeatsDataDTO *seatData = (CSeatsDataDTO *)CCBFMediator::Instance()->GetSeats();
	CSeatDataDTO *seat = seatData->GetSeatById(a_seatId);
	if(seat == NULL)
	{
		return -1;
	}
	return (seat->m_position.x - 1) * seatData->m_maxX + seat->m_position.y - 1;
}


/**@brief	���ο� �¼��� �߰��� ��Ÿ����.
 */
void COperatorDlg::DisplayAddedSeat(CString a_seatId)
{	
	CSeatsDataDTO *seatData = (CSeatsDataDTO *)CCBFMediator::Instance()->GetSeats();
	CSeatDataDTO *seat = seatData->GetSeatById(a_seatId);
	if(seat == NULL)
	{
		return;
	}
	int seatNumber = (seat->m_position.x - 1) * seatData->m_maxX + seat->m_position.y - 1;
	CString seatName = seat->m_nickname + _T("(") + seat->m_hostAddress + _T(")") ;
	m_stateDisplayList.SetItemText(seatNumber, 0, seatName.GetBuffer());
}

/**@brief	���ο� �¼��� ������ ��Ÿ����.
 */
void COperatorDlg::DisplayDeletedSeat(CString a_seatId)
{
	int seatNumber = GetIconIndexBySeatId(a_seatId);
	m_stateDisplayList.SetItemText(seatNumber, 0, _T(""));
}


/**@brief	�α��� �Ǿ����� ����Ʈ ��Ʈ���� ���������� ǥ���Ѵ�.
 */
void COperatorDlg::DisplayIconAsLogin(CString a_seatId)
{
	int seatNumber = GetIconIndexBySeatId(a_seatId);
	m_stateDisplayList.SetItemState( seatNumber, 0, LVIS_CUT);
}

/**@brief	�α׾ƿ� �Ǿ����� ����Ʈ ��Ʈ���� ���������� ǥ���Ѵ�.
 */
void COperatorDlg::DisplayIconAsLogout(CString a_seatId)
{
	int seatNumber = GetIconIndexBySeatId(a_seatId);
	m_stateDisplayList.SetItemState( seatNumber, LVIS_CUT, LVIS_CUT);
}

/**@brief	���� ���°� �Ǿ����� ����Ʈ ��Ʈ���� ���������� ǥ���Ѵ�.
 */
void COperatorDlg::DisplayIconAsNormal(CString a_seatId)
{
	int seatNumber = GetIconIndexBySeatId(a_seatId);

	UINT state = m_stateDisplayList.GetItemState(seatNumber, LVIS_CUT);
	CString text = m_stateDisplayList.GetItemText(seatNumber, 0);

	LVITEM item;
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	item.iItem = seatNumber;
	item.iSubItem = 0;
	item.pszText = text.GetBuffer();
	item.iImage = 0;
	item.state = state;

	m_stateDisplayList.SetItem( &item);
}

/**@brief	������ ���°� �Ǿ����� ����Ʈ ��Ʈ���� ���������� ǥ���Ѵ�.
 */
void COperatorDlg::DisplayIconAsAbnormal(CString a_seatId)
{
	int seatNumber = GetIconIndexBySeatId(a_seatId);

	UINT state = m_stateDisplayList.GetItemState(seatNumber, LVIS_CUT);
	CString text = m_stateDisplayList.GetItemText(seatNumber, 0);

	LVITEM item;
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	item.iItem = seatNumber;
	item.iSubItem = 0;
	item.pszText = text.GetBuffer();
	item.iImage = 1;
	item.state = state;

	m_stateDisplayList.SetItem( &item);
}


/**@brief	�������� ���� ���·� ����� �ָ��ϰ� �����.
 */
void COperatorDlg::DisplayIconAsAttention(CString a_seatId)
{
	m_stateDisplayList.SetFocus();
	int seatNumber = GetIconIndexBySeatId(a_seatId);
	m_stateDisplayList.SetItemState( seatNumber, LVIS_SELECTED, LVIS_SELECTED);
	m_stateDisplayList.SetFocus();
}




/**@brief	���� ǥ�� ����Ʈ ��Ʈ���� �ʱ�ȭ �Ѵ�.
 */
void COperatorDlg::InitiallizeStatusListCtrl()
{
	m_stateImage.Create(48,48,ILC_COLOR24, 2,0);
	CBitmap normal, abnormal;
	normal.LoadBitmapW(IDB_NORMAL);
	abnormal.LoadBitmapW(IDB_ABNORMAL);
	COLORREF crMask = RGB(0,0,0);
	m_stateImage.Add(&normal, crMask);
	m_stateImage.Add(&abnormal, crMask);

	m_stateDisplayList.SetImageList(&m_stateImage, LVSIL_NORMAL);

	CSeatsDataDTO *seatData = (CSeatsDataDTO *)CCBFMediator::Instance()->GetSeats();
	int maxX = seatData->m_maxX;
	int maxY = seatData->m_maxY;
	for(int i=0; i<maxX; i++)
	{
		for(int j=0; j<maxY; j++)
		{
			LVITEM item = {0};
			item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVS_SHOWSELALWAYS;
			item.iItem = i*maxX + j;
			item.iSubItem = 0;
			item.iImage = 0;			
			item.state = LVIS_CUT | LVS_AUTOARRANGE;			
			item.pszText = _T("");

			m_stateDisplayList.InsertItem(&item);			
			m_stateDisplayList.SetItemPosition(i*maxX + j, CPoint(j*84, i*84));
		}
	}
}

/**@brief	����Ʈ �ڽ����� ������ ���� ��. �ش� �ڸ��� state report ������ notify ����Ʈ�ڽ��� ���� �����ش�.
 */
void COperatorDlg::OnLvnItemchangedStateDisplay(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	
	int iItem = m_stateDisplayList.GetNextItem(-1, LVNI_SELECTED);
	if(iItem<0)
	{		
		return;
	}
	
	CString seatName = m_stateDisplayList.GetItemText(iItem, 0);
	if(seatName==_T(""))
	{
		return;
	}
	int tokenIndex = 0;
	CString seatId = seatName.Tokenize(_T("( )"), tokenIndex);
	seatId = seatName.Tokenize(_T("( )"), tokenIndex);

	CStatusReportDTOArray statusReports;
	CStatusReportsDTO *statusReportsData = (CStatusReportsDTO *)CCBFMediator::Instance()->GetStatusReports();
	
	statusReportsData->GetReportFrom(seatId, &statusReports);
	for(int i=0;i < statusReports.GetCount(); i++)
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
		Notify( _T("[") + statusReport .m_date + _T("]") + state + _T(" : ") + statusReport.m_comment);
	}
	

	*pResult = 0;
}
