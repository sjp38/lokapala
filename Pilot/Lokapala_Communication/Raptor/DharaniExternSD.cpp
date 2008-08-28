/**@file	DharaniExternSD.cpp
 * @brief	DharaniExternSD를 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DharaniExternSD.h"

/**@brief	Dharani가 관리하게 되는 클라이언트가 데이터를 받은 경우, 클라이언트 코드 측에 이 사실과 받은 내용을 알린다.
 * @param	a_srcAddress	데이터를 전송한 클라이언트의 ip 주소.
 * @param	a_message		전송받은 메세지
 */
void CDharaniExternSD::NotifyReceived(CString a_srcAddress, CString a_message)
{
}