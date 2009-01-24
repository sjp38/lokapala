// UserAdmin.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "UserAdminDlg.h"

#include "UsersDataDTO.h"


// CUserAdminDlg dialog

IMPLEMENT_DYNAMIC(CUserAdminDlg, CDialog)

CUserAdminDlg::CUserAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserAdminDlg::IDD, pParent)
{

}

CUserAdminDlg::~CUserAdminDlg()
{
}

void CUserAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAME, m_name);
	DDX_Control(pDX, IDC_LOWPASS, m_lowPassword);
	DDX_Control(pDX, IDC_HIGHPASS, m_highPassword);
	DDX_Control(pDX, IDC_LEVEL, m_level);
	DDX_Control(pDX, IDC_USERLIST, m_userList);
}


BEGIN_MESSAGE_MAP(CUserAdminDlg, CDialog)
	ON_BN_CLICKED(IDC_USER_ADD, &CUserAdminDlg::OnBnClickedUserAdd)
	ON_BN_CLICKED(IDC_USER_DELETE, &CUserAdminDlg::OnBnClickedUserDelete)
	ON_LBN_SELCHANGE(IDC_USERLIST, &CUserAdminDlg::OnLbnSelchangeUserlist)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CUserAdminDlg message handlers

/**@brief	���̾�α׷κ��� �Է°��� �о���δ�.
 */
 void CUserAdminDlg::GetInputVariables(CString *a_name, CString *a_lowPassword, CString *a_highPassword, int *a_level)
{
	m_name.GetWindowTextW(*a_name);
	m_lowPassword.GetWindowTextW(*a_lowPassword);
	m_highPassword.GetWindowTextW(*a_highPassword);
	CString value;	
	m_level.GetWindowTextW(value);
	*a_level = _ttoi(value);
}


/**@brief	Ư�� ������ ������ �Է�â�� ����.
 */
void CUserAdminDlg::SetInputVariables(void *a_user)
{
	CUserDataDTO *user = (CUserDataDTO *)a_user;
	m_name.SetWindowTextW(user->m_name);
	m_lowPassword.SetWindowTextW(user->m_lowLevelPassword);
	CString value;
	value.Format(_T("%d"), user->m_level);
	m_level.SetWindowTextW(value);
}

/**@brief	���� �߰� ��ư Ŭ��	*/
void CUserAdminDlg::OnBnClickedUserAdd()
{
	// TODO: Add your control notification handler code here
	CString name, lowPassword, highPassword;
	int level;

	GetInputVariables(&name, &lowPassword, &highPassword, &level);	
	CUserDataDTO user(_T(""), name, lowPassword, highPassword, level);
	CCBFMediator::Instance()->AddUser( (void *)&user);

	ShowUsers();
}

/**@brief	���� ���� ��ư Ŭ��	*/
void CUserAdminDlg::OnBnClickedUserDelete()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_userList.GetSelCount();

	CString id;
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_userList.GetSelItems(selectedCount, selectedIndex.GetData());
	for(int i=0; i<selectedCount; i++)
	{
		m_userList.GetText(selectedIndex[i], id);
		int tokenIndex = 0;
		id = id.Tokenize(_T("/"),tokenIndex);
		CCBFMediator::Instance()->DeleteUser(&id);
	}
	ShowUsers();
}

/**@brief	���� ���� ����� ǥ��
 */
void CUserAdminDlg::ShowUsers()
{
	m_userList.ResetContent();

	CUsersDataDTO *pUsersData = (CUsersDataDTO *)CCBFMediator::Instance()->GetUsers();

	POSITION pos = pUsersData->m_users.GetStartPosition();
	CString key;
	CUserDataDTO value;
	while(pos != NULL)
	{
		pUsersData->m_users.GetNextAssoc(pos, key, value);
		CString userDisplay;
		userDisplay = value.m_lowLevelPassword + _T("/") + value.m_name;
		m_userList.AddString(userDisplay);
	}
}


BOOL CUserAdminDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ShowUsers();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/**@brief	����Ʈ�ڽ����� ������ �������� ��.
 */
void CUserAdminDlg::OnLbnSelchangeUserlist()
{
	// TODO: Add your control notification handler code here
	int selectedCount = m_userList.GetSelCount();
	if(selectedCount == 0)
	{
		return;
	}
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	m_userList.GetSelItems(selectedCount, selectedIndex.GetData());
	int selected = selectedIndex[0];

	CString userId;
	m_userList.GetText(selected, userId);
	selected = 0;
	userId = userId.Tokenize(_T("/"), selected);
	CUsersDataDTO *usersData = (CUsersDataDTO *)CCBFMediator::Instance()->GetUsers();
	CUserDataDTO *user = usersData->GetUserById(userId);

	SetInputVariables((void *)user);	
}

/**@brief	���̾�α� ����, ����ƽ ��Ʈ�� ���� ����
 */
HBRUSH CUserAdminDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch( nCtlColor ) 
	{
	case CTLCOLOR_DLG :
		return (HBRUSH)CreateSolidBrush( RGB(244,243,238) ); // ���ϴ� �����ڵ带 �Է��Ѵ�.
		break;
	case CTLCOLOR_STATIC :
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(244,243,238));
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
