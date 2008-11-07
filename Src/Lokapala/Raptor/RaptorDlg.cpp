// RaptorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Raptor.h"
#include "RaptorDlg.h"

#include "StatusReportDlg.h"

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
	CCBFMediator::Instance()->SetMainDlg(this);
	CCBFMediator::Instance()->StartNeverDie();
	(CButton *)(GetDlgItem(IDC_STARTNEVERDIE_TEST))->EnableWindow(0);
	(CButton *)(GetDlgItem(IDC_STOPNEVERDIE_TEST))->EnableWindow(1);

	CCBFMediator::Instance()->RestraintUser();

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

/**@brief	WM_CLOSE �޼��� �̺�Ʈ �ڵ鷯.
 *			������ �׾� �ֵ�, ���� �׾ �ȵȴٸ� �ڽŰ� ���� ���μ����� �ϳ� �� �����ϰ� �״´�.
 */
void CRaptorDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if(CCBFMediator::Instance()->GetNeverDieState())
	{
		WCHAR *selfPath = (WCHAR *)malloc(sizeof(WCHAR)*MAX_PATH);
		GetModuleFileName(NULL,selfPath,MAX_PATH);
		ShellExecute(NULL, _T("open"), selfPath, NULL, NULL, SW_SHOWNORMAL);
	}

	CDialog::OnClose();
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
