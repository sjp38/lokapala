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
}


BEGIN_MESSAGE_MAP(CUserAdminDlg, CDialog)
	ON_BN_CLICKED(IDC_USER_ADD, &CUserAdminDlg::OnBnClickedUserAdd)
	ON_BN_CLICKED(IDC_USER_DELETE, &CUserAdminDlg::OnBnClickedUserDelete)
END_MESSAGE_MAP()


// CUserAdminDlg message handlers

/**@brief	유저 추가 버튼 클릭	*/
void CUserAdminDlg::OnBnClickedUserAdd()
{
	// TODO: Add your control notification handler code here
	CString name;
	GetDlgItemTextW(IDC_NAME, name);
	CString lowPass;
	GetDlgItemTextW(IDC_LOWPASS, lowPass);
	CString highPass;
	GetDlgItemTextW(IDC_HIGHPASS, highPass);
	int level = GetDlgItemInt(IDC_LEVEL);

	CUserDataDTO user(_T(""), name, lowPass, highPass, level);

	CCBFMediator::Instance()->AddUser( (void *)&user);

	ShowUsers();
}

/**@brief	유저 삭제 버튼 클릭	*/
void CUserAdminDlg::OnBnClickedUserDelete()
{
	// TODO: Add your control notification handler code here
	CListBox *plistBox = (CListBox *)(this->GetDlgItem(IDC_USERLIST));

	int selectedCount = plistBox->GetSelCount();

	CString id;
	CArray<int,int> selectedIndex;
	selectedIndex.SetSize(selectedCount);
	plistBox->GetSelItems(selectedCount, selectedIndex.GetData());
	for(int i=0; i<selectedCount; i++)
	{
		plistBox->GetText(selectedIndex[i], id);
		int tokenIndex = 0;
		id = id.Tokenize(_T("/"),tokenIndex);
		CCBFMediator::Instance()->DeleteUser(&id);
	}
	ShowUsers();
}

/**@brief	현재 유저 목록을 표시
 */
void CUserAdminDlg::ShowUsers()
{
	CListBox *pListBox = (CListBox *)GetDlgItem(IDC_USERLIST);
	pListBox->ResetContent();

	CUsersDataDTO *pUsersData = (CUsersDataDTO *)CCBFMediator::Instance()->GetUsers();

	POSITION pos = pUsersData->m_users.GetStartPosition();
	CString key;
	CUserDataDTO value;
	while(pos != NULL)
	{
		pUsersData->m_users.GetNextAssoc(pos, key, value);
		CString userDisplay;
		userDisplay = value.m_lowLevelPassword+_T("/")+/*value.m_name+_T("/")+*/value.m_highLevelPassword;
		pListBox->AddString(userDisplay);
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
