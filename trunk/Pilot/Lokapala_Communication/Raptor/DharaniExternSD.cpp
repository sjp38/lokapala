/**@file	DharaniExternSD.cpp
 * @brief	DharaniExternSD�� ����
 * @author	siva
 */

#include <atlconv.h>
#include "stdafx.h"
#include "Resource.h"
#include "DharaniExternSD.h"

/**@brief	Dharani�� �����ϰ� �Ǵ� Ŭ���̾�Ʈ�� �����͸� ���� ���, Ŭ���̾�Ʈ �ڵ� ���� �� ��ǰ� ���� ������ �˸���.
 * @param	a_srcAddress	�����͸� ������ Ŭ���̾�Ʈ�� ip �ּ�.
 * @param	a_message		���۹��� �޼���
 */
void CDharaniExternSD::NotifyReceived(char *a_receivedMessage)
{
	USES_CONVERSION;
	CString message = A2W(a_receivedMessage);
	CDialog *pDlg = CCBFMediator::Instance()->GetMainDlg();
	CListBox *pListBox = (CListBox *)(pDlg->GetDlgItem(IDC_LISTTEST));
	pListBox->AddString(message);
}

/**@brief	Ŭ���̾�Ʈ�κ����� ������ ����Ǿ����� �˸���.
 */
void CDharaniExternSD::NotifyAccepted(in_addr *a_clientIp, in_addr *a_localIp)
{
	USES_CONVERSION;
	CString message = _T("accepted : ");
	CString address = A2W(inet_ntoa(*a_clientIp));
	address += _T("/");
	address += A2W(inet_ntoa(*a_localIp));
	message += address;
	CDialog *pDlg = CCBFMediator::Instance()->GetMainDlg();
	CListBox *pListBox = (CListBox *)(pDlg->GetDlgItem(IDC_LISTTEST));
	pListBox->AddString(message);

	//pListBox = (CListBox *)(pDlg->GetDlgItem(IDC_USERLIST));
	//pListBox->AddString(address);
}

void CDharaniExternSD::NotifyLeft()
{
	CDialog *pDlg = CCBFMediator::Instance()->GetMainDlg();
	CListBox *pListBox = (CListBox *)(pDlg->GetDlgItem(IDC_LISTTEST));
	pListBox->AddString(_T("leave"));
}