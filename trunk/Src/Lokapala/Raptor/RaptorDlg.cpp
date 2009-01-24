// RaptorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Raptor.h"
#include "RaptorDlg.h"

#include "StatusReportDlg.h"

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


// CRaptorDlg dialog




CRaptorDlg::CRaptorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRaptorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRaptorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT, m_input);
	DDX_Control(pDX, IDC_NOTIFY_LIST, m_notifyList);
}

BEGIN_MESSAGE_MAP(CRaptorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CONNECTBUTTON, &CRaptorDlg::OnBnClickedConnectbutton)
	ON_BN_CLICKED(IDC_STARTNEVERDIE_TEST, &CRaptorDlg::OnBnClickedStartneverdieTest)
	ON_BN_CLICKED(IDC_STOPNEVERDIE_TEST, &CRaptorDlg::OnBnClickedStopneverdieTest)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CRaptorDlg::OnStartObservation)
	ON_BN_CLICKED(IDC_BUTTON3, &CRaptorDlg::OnStopObservation)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_SEND, &CRaptorDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_STATUS_REPORT, &CRaptorDlg::OnBnClickedStatusReport)
	ON_MESSAGE(LKPLM_STATUS_CHANGED, &CRaptorDlg::OnStatusChanged)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRaptorDlg message handlers

BOOL CRaptorDlg::OnInitDialog()
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
	TCHAR filePath[MAX_PATH];
	GetModuleFileName(NULL, filePath, MAX_PATH);
	CString directory = filePath;

	int position = directory.ReverseFind('\\');
	directory = directory.Left(position);
	directory += "\\";
	SetCurrentDirectory(directory);

	SetWindowText(_T("Raptor"));
	CCBFMediator::Instance()->SetMainDlg(this);
	CCBFMediator::Instance()->StartNeverDie();
	CCBFMediator::Instance()->RestraintUser();

	CCBFMediator::Instance()->LoadStatusReportsFromFile();

	DWORD address;
	CFile file;
	
	if( file.Open(_T("operatorAddress.cfg"), CFile::modeRead) )
	{		
		file.Read(&address, sizeof(address));
		file.Close();
		CCBFMediator::Instance()->InitiallizeCommunication(address);
	}

	//�׽�Ʈ��. ���߿� ������.
	(CButton *)(GetDlgItem(IDC_STARTNEVERDIE_TEST))->EnableWindow(0);
	(CButton *)(GetDlgItem(IDC_STOPNEVERDIE_TEST))->EnableWindow(1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRaptorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRaptorDlg::OnPaint()
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
HCURSOR CRaptorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/**@brief	���۷����ͷ� ���� ��ư Ŭ��
 */
void CRaptorDlg::OnBnClickedConnectbutton()
{
	// TODO: Add your control notification handler code here
	CIPAddressCtrl *pIpControl = (CIPAddressCtrl *)(this->GetDlgItem(IDC_SERVERIP));
	DWORD serverIp;
	pIpControl->GetAddress(serverIp);
	CCBFMediator::Instance()->InitiallizeCommunication(serverIp);
}

/**@brief	�׹����� ��� ��ŸƮ ��ư Ŭ��
 */
void CRaptorDlg::OnBnClickedStartneverdieTest()
{
	// TODO: Add your control notification handler code here
	CCBFMediator::Instance()->StartNeverDie();
	(CButton *)(GetDlgItem(IDC_STARTNEVERDIE_TEST))->EnableWindow(0);
	(CButton *)(GetDlgItem(IDC_STOPNEVERDIE_TEST))->EnableWindow(1);
}

/**@brief	�׹����� ��� ���� ��ư Ŭ��
 */
void CRaptorDlg::OnBnClickedStopneverdieTest()
{
	// TODO: Add your control notification handler code here
	CCBFMediator::Instance()->StopNeverDie();
	(CButton *)(GetDlgItem(IDC_STARTNEVERDIE_TEST))->EnableWindow(1);
	(CButton *)(GetDlgItem(IDC_STOPNEVERDIE_TEST))->EnableWindow(0);
}

/**@brief	PreTranslateMessage�� �������̵�.\n
 *			esc, return�� �Է� �� �ڵ����� ����Ǵ� ���̾�α� ���̽��� ����� ������ ���⼭ �ذ��Ѵ�.
 */
BOOL CRaptorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
			case VK_ESCAPE :
			case VK_RETURN :
				return TRUE;
			default :
				break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

/**@brief	���μ��� ���� ���� ��ư�� ������ ��.
 */
void CRaptorDlg::OnStartObservation()
{
	// TODO: Add your control notification handler code here
	CCBFMediator::Instance()->StartProcessObservation();
}

/**@brief	���μ��� ���� ���� ��ư�� ������ ��.
 */
void CRaptorDlg::OnStopObservation()
{
	// TODO: Add your control notification handler code here
	CCBFMediator::Instance()->StopProcessObservation();
}

/**@brief	WM_COPYDATA �̺�Ʈ �ڵ鷯. ���� ����� ���μ����� �˸���.
 */
BOOL CRaptorDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox((LPCTSTR)pCopyDataStruct->lpData);
	CString executed = (LPCTSTR)pCopyDataStruct->lpData;
	CCBFMediator::Instance()->ReceiveExecutedProcess(executed);

	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

/**@brief	���۷����Ϳ��� �޼��� ���� ��ư ������ ��
 */
void CRaptorDlg::OnBnClickedSend()
{
	// TODO: Add your control notification handler code here
	CString message;
	m_input.GetWindowTextW(message);
	CCBFMediator::Instance()->PostTextMessageToOperator(&message);
}

/**@brief	�������ͽ� ����Ʈ ��ư Ŭ��
 */
void CRaptorDlg::OnBnClickedStatusReport()
{
	// TODO: Add your control notification handler code here
	CStatusReportDlg statusReportDlg;
	statusReportDlg.DoModal();
}


/**@brief	���� ��ȭ ������ ���۷����ͷκ��� �޾��� ��.
*/
LRESULT CRaptorDlg::OnStatusChanged(WPARAM wParam, LPARAM lParam)
{
	CStatusReportDTO statusReport = *(CStatusReportDTO *)wParam;

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
	return 0;
}


/**@brief	���� ���̾�α׸� ���� �޼����� �Ѹ���.
 */
void CRaptorDlg::Notify(CString a_message)
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


/**@brief	WM_CLOSE �޼��� �̺�Ʈ �ڵ鷯.
 */
void CRaptorDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

/**@brief	WM_DESTROY �޼��� �̺�Ʈ �ڵ鷯.
 *			WM_CLOSE �޼��� �̺�Ʈ �ڵ鷯�� ���� ���� �Ѵ�.
 */
void CRaptorDlg::OnDestroy()
{
	CCBFMediator::Instance()->UserTryingToKillMe();
	if(CCBFMediator::Instance()->GetNeverDieState())
	{
		CCBFMediator::Instance()->CloseConnection();
		WCHAR *selfPath = (WCHAR *)malloc(sizeof(WCHAR)*MAX_PATH);
		GetModuleFileName(NULL,selfPath,MAX_PATH);
		ShellExecute(NULL, _T("open"), selfPath, NULL, NULL, SW_SHOWNORMAL);
	}

	//CDialog::OnClose();
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

/**@brief	���� ������� ��ü
 */
HBRUSH CRaptorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void CRaptorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CDialog::OnLButtonDown(nFlags, point);
}