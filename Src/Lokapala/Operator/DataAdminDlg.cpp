// DataAdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "DataAdminDlg.h"


// CDataAdminDlg dialog

IMPLEMENT_DYNAMIC(CDataAdminDlg, CDialog)

CDataAdminDlg::CDataAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataAdminDlg::IDD, pParent)
{
	InitSubDialog();
}

CDataAdminDlg::~CDataAdminDlg()
{
	TerminateSubDialog();
}

void CDataAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA_ADMIN_TAB, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(CDataAdminDlg, CDialog)
	ON_BN_CLICKED(IDC_SAVE, &CDataAdminDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &CDataAdminDlg::OnBnClickedLoad)
	ON_NOTIFY(TCN_SELCHANGING, IDC_DATA_ADMIN_TAB, &CDataAdminDlg::OnTcnSelchangingDataAdminTab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_DATA_ADMIN_TAB, &CDataAdminDlg::OnTcnSelchangeDataAdminTab)
END_MESSAGE_MAP()


// CDataAdminDlg message handlers

/**@brief	세이브 버튼 클릭
 */
void CDataAdminDlg::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
	CString szFilters =
      _T("XML Files(*.xml) |*.xml| ");

   CFileDialog fileDlg (FALSE, _T("xml"), NULL, OFN_FILEMUSTEXIST| OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters, this);
   
   if( fileDlg.DoModal ()==IDOK )
   {
      CString pathName = fileDlg.GetPathName();

	  CCBFMediator::Instance()->SaveDataAs(&pathName);
   } 
}

/**@brief	로드 버튼 클릭
 */
void CDataAdminDlg::OnBnClickedLoad()
{
	// TODO: Add your control notification handler code here
	CString szFilters =
      _T("XML Files(*.xml) |*.xml| ");

   CFileDialog fileDlg (TRUE, _T("xml"), NULL, OFN_FILEMUSTEXIST, szFilters, this);
   
   if( fileDlg.DoModal ()==IDOK )
   {
      CString pathName = fileDlg.GetPathName();

	  CCBFMediator::Instance()->LoadDataFrom(&pathName);
   } 

   TerminateSubDialog();
   CreateSubDialog();
   InitTabCursor();
}


/**@brief	탭 컨트롤을 초기화한다.	*/
BOOL CDataAdminDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitTabControl();

	CreateSubDialog();

	InitTabCursor();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/**@brief	탭 이동 중. 기존에 선택되었던 다이얼로그를 보이지 않게 한다.	*/
void CDataAdminDlg::OnTcnSelchangingDataAdminTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nTab = m_tabCtrl.GetCurSel();
	switch(nTab)
	{
	case 0 :
		m_pUserDlg->ShowWindow(SW_HIDE);
		break;
	case 1 :
		m_pSeatDlg->ShowWindow(SW_HIDE);
		break;
	case 2 :
		m_pRuleDlg->ShowWindow(SW_HIDE);
		break;
	default :
		break;
	}

	*pResult = 0;
}

/**@brief	탭 이동 후. 선택된 다이얼로그를 표시한다.	*/
void CDataAdminDlg::OnTcnSelchangeDataAdminTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nTab = m_tabCtrl.GetCurSel();
	switch(nTab)
	{
	case 0 :
		m_pUserDlg->ShowWindow(SW_SHOW);
		break;
	case 1 :
		m_pSeatDlg->ShowWindow(SW_SHOW);
		break;
	case 2 :
		m_pRuleDlg->ShowWindow(SW_SHOW);
		break;
	default :
		break;
	}

	*pResult = 0;
}


/**@brief	탭 컨트롤의 탭을 초기화한다(탭 이름 및 값 설정).	*/
void CDataAdminDlg::InitTabControl()
{
	TCITEM item;
	item.mask = TCIF_TEXT;
	item.pszText = _T("User Data");
	m_tabCtrl.InsertItem(0, &item);
	item.pszText = _T("Seat Data");
	m_tabCtrl.InsertItem(1, &item);
	item.pszText = _T("Rule Data");
	m_tabCtrl.InsertItem(2, &item);
}

/**@brief	실제 값을 조정하는 서브 다이얼로그들을 NULL로 초기화한다.
 */
void CDataAdminDlg::InitSubDialog()
{
	m_pUserDlg = NULL;
	m_pSeatDlg = NULL;
	m_pRuleDlg = NULL;
}


/**@brief	실제 값을 조정하는 서브 다이얼로그들을 생성한다.
 */
void CDataAdminDlg::CreateSubDialog()
{
	CRect rect;
	m_pUserDlg = new CUserAdminDlg;
	m_pUserDlg->Create(IDD_USER_ADMIN, &m_tabCtrl);
	m_pUserDlg->GetWindowRect(&rect);
	m_pUserDlg->MoveWindow(5, 25, rect.Width(), rect.Height());
	m_pUserDlg->ShowWindow(SW_HIDE);

	m_pSeatDlg = new CSeatAdminDlg;
	m_pSeatDlg->Create(IDD_SEAT_ADMIN, &m_tabCtrl);
	m_pSeatDlg->GetWindowRect(&rect);
	m_pSeatDlg->MoveWindow(5, 25, rect.Width(), rect.Height());
	m_pSeatDlg->ShowWindow(SW_HIDE);

	m_pRuleDlg = new CRuleAdminDlg;
	m_pRuleDlg->Create(IDD_RULE_ADMIN, &m_tabCtrl);
	m_pRuleDlg->GetWindowRect(&rect);
	m_pRuleDlg->MoveWindow(5, 25, rect.Width(), rect.Height());
	m_pRuleDlg->ShowWindow(SW_HIDE);
}


/**@brief	탭 컨트롤의 첫번째 탭을 가리키고 표시하게 한다.
 */
void CDataAdminDlg::InitTabCursor()
{
	m_tabCtrl.SetCurSel(0);
	m_pUserDlg->ShowWindow(SW_SHOW);
}


/**@brief	실제 값을 조정하는 서브 다이얼로그들을 메모리 해제하고 NULL로 만들어 버린다.
 */
void CDataAdminDlg::TerminateSubDialog()
{
	if(m_pUserDlg!=NULL)
	{
		delete m_pUserDlg;
	}
	if(m_pSeatDlg!=NULL)
	{
		delete m_pSeatDlg;
	}
	if(m_pRuleDlg!=NULL)
	{
		delete m_pRuleDlg;
	}
}