/**@file	DharaniExternSD.cpp
 * @brief	DharaniExternSD를 구현
 * @author	siva
 */

#include <atlconv.h>
#include "stdafx.h"
#include "Resource.h"
#include "DharaniExternSD.h"

/**@brief	Dharani가 관리하게 되는 클라이언트가 데이터를 받은 경우, 클라이언트 코드 측에 이 사실과 받은 내용을 알린다.
 * @param	a_srcAddress	데이터를 전송한 클라이언트의 ip 주소.
 * @param	a_message		전송받은 메세지
 */
void CDharaniExternSD::NotifyReceived(char *a_receivedMessage)
{
	USES_CONVERSION;
	CString message = A2W(a_receivedMessage);
	CDialog *pDlg = CCBFMediator::Instance()->GetMainDlg();
	CListBox *pListBox = (CListBox *)(pDlg->GetDlgItem(IDC_LISTTEST));
	pListBox->AddString(message);
}

/**@brief	클라이언트로부터의 연결이 성사되었음을 알린다.
 *			내부적으로는 연결된 클라이언트의 주소 정보를 표시 해 알려줄 뿐이다.
 * @param	a_globalIp	연결된 클라이언트의 global ip
 * @param	a_localIp	연결된 클라이언트의 local ip
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

/**@brief	특정 클라이언트가 접속 해제 했음을 알린다.
 *			내부적으로는 해당 ip를 리스트박스에서 목록 제거 할 뿐이다.
 * @param	a_globalIp	접속 해제한 클라이언트의 global ip
 * @param	a_localIp	접속 해제한 클라이언트의 local Ip
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