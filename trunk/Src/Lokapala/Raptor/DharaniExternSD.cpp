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
 *			���������δ� ����� Ŭ���̾�Ʈ�� �ּ� ������ ǥ�� �� �˷��� ���̴�.
 * @param	a_globalIp	����� Ŭ���̾�Ʈ�� global ip
 * @param	a_localIp	����� Ŭ���̾�Ʈ�� local ip
 */
void CDharaniExternSD::NotifyAccepted(in_addr *a_globalIp, in_addr *a_localIp)
{
	/*
	USES_CONVERSION;
	CString message = _T("accepted : ");
	CString address = A2W(inet_ntoa(*a_globalIp));
	address += _T("/");
	address += A2W(inet_ntoa(*a_localIp));
	message += address;
	CDialog *pDlg = CCBFMediator::Instance()->GetMainDlg();
	CListBox *pListBox = (CListBox *)(pDlg->GetDlgItem(IDC_LISTTEST));
	pListBox->AddString(message);

	pListBox = (CListBox *)(pDlg->GetDlgItem(IDC_USERLIST));
	pListBox->AddString(address);
	*/
}

/**@brief	Ư�� Ŭ���̾�Ʈ�� ���� ���� ������ �˸���.
 *			���������δ� �ش� ip�� ����Ʈ�ڽ����� ��� ���� �� ���̴�.
 * @param	a_globalIp	���� ������ Ŭ���̾�Ʈ�� global ip
 * @param	a_localIp	���� ������ Ŭ���̾�Ʈ�� local Ip
 */
void CDharaniExternSD::NotifyLeft(in_addr *a_globalIp, in_addr *a_localIp)
{
	/*
	USES_CONVERSION;
	CString address = A2W(inet_ntoa(*a_globalIp));
	address += _T("/");
	address += A2W(inet_ntoa(*a_localIp));

	CDialog *pDlg = CCBFMediator::Instance()->GetMainDlg();
	CListBox *pListBox = (CListBox *)(pDlg->GetDlgItem(IDC_USERLIST));
	UINT index = 0;
	index = pListBox->FindString(index, address);
	pListBox->DeleteString(index);

	pListBox = (CListBox *)(pDlg->GetDlgItem(IDC_LISTTEST));
	pListBox->AddString(address+_T(" leaved"));
	*/
}