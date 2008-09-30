// DataAdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "DataAdminDlg.h"


#include "UserAdminDlg.h"
#include "SeatInfoAdminDlg.h"
#include "RuleAdminDlg.h"


// CDataAdminDlg dialog

IMPLEMENT_DYNAMIC(CDataAdminDlg, CDialog)

CDataAdminDlg::CDataAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataAdminDlg::IDD, pParent)
{

}

CDataAdminDlg::~CDataAdminDlg()
{
}

void CDataAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDataAdminDlg, CDialog)
	ON_BN_CLICKED(IDC_USER_ADMIN, &CDataAdminDlg::OnBnClickedUserAdmin)
	ON_BN_CLICKED(IDC_SEAT_ADMIN, &CDataAdminDlg::OnBnClickedSeatAdmin)	
	ON_BN_CLICKED(IDC_RULE_ADMIN, &CDataAdminDlg::OnBnClickedRuleAdmin)
	ON_BN_CLICKED(IDC_SAVE, &CDataAdminDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &CDataAdminDlg::OnBnClickedLoad)
END_MESSAGE_MAP()


// CDataAdminDlg message handlers

/**@brief	����� ���� ���� ��ư Ŭ��
 */
void CDataAdminDlg::OnBnClickedUserAdmin()
{
	// TODO: Add your control notification handler code here
	CUserAdminDlg userAdminDlg;
	userAdminDlg.DoModal();
}

/**@brief	�¼� ���� ���� ��ư Ŭ��
 */
void CDataAdminDlg::OnBnClickedSeatAdmin()
{
	// TODO: Add your control notification handler code here
	CSeatInfoAdminDlg seatInfoAdminDlg;
	seatInfoAdminDlg.DoModal();
}

/**@brief	���� ���μ��� ���� ������ ��ư Ŭ��
 */
void CDataAdminDlg::OnBnClickedRuleAdmin()
{
	// TODO: Add your control notification handler code here
	CRuleAdminDlg ruleAdminDlg;
	ruleAdminDlg.DoModal();
}

/**@brief	���̺� ��ư Ŭ��
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

/**@brief	�ε� ��ư Ŭ��
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
}

