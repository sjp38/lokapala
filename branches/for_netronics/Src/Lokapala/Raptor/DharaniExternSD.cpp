/**@file	DharaniExternSD.cpp
 * @brief	DharaniExternSD를 구현
 * @author	siva
 */

#include <atlconv.h>
#include "stdafx.h"
#include "Resource.h"
#include "DharaniExternSD.h"

#include "CommunicationManager.h"

/**@brief	Dharani가 관리하게 되는 클라이언트가 데이터를 받은 경우, 클라이언트 코드 측에 이 사실과 받은 내용을 알린다.
 * @param	a_receivedMessage		전송받은 메세지
 * @remarks	클라이언트 전용 함수이다.
 */
void CDharaniExternSD::NotifyReceived(char *a_receivedMessage)
{
	USES_CONVERSION;
	CString message = A2W(a_receivedMessage);

	CCommunicationManager::Instance()->NotifyReceived(message);
}

/**@brief	Dharani가 관리하게 되는 클라이언트가 데이터를 받은 경우, 클라이언트 코드 측에 이 사실과 받은 내용을 알린다.
 *			전송한 측의 주소가 필요한, 즉 서버로 사용할 경우 사용되는 오버로드 함수.
 * @param	a_message		전송받은 메세지
 * @param	a_localIp		메세지를 전송한 클라이언트의 로컬 주소
 * @param	a_globalIp		메세지를 전송한 클라이언트의 글로벌 주소
 * @remarks	서버 전용 함수이므로 랩터에서는 구현하지 않는다.
 */
void CDharaniExternSD::NotifyReceived(char *a_receivedMessage, in_addr a_localIp, in_addr a_globalIp)
{
}

/**@brief	서버와 연결에 성공했음을 알린다.
 * @remarks	클라이언트 전용 함수다.
 */
void CDharaniExternSD::NotifyConnected()
{
	CCommunicationManager::Instance()->Connected();
}


/**@brief	서버와의 연결이 끊겼음을 알린다.
 * @remarks	클라이언트 전용 함수다.
 */
void CDharaniExternSD::NotifyDisconnected()
{
	CCommunicationManager::Instance()->Disconnected();
}

/**@brief	클라이언트로부터의 연결이 성사되었음을 알린다.
 *			내부적으로는 연결된 클라이언트의 주소 정보를 표시 해 알려줄 뿐이다.
 * @param	a_globalIp	연결된 클라이언트의 global ip
 * @param	a_localIp	연결된 클라이언트의 local ip
 * @remarks	서버 전용 함수이므로 랩터에서는 구현하지 않는다.
 */
void CDharaniExternSD::NotifyAccepted(in_addr *a_globalIp, in_addr *a_localIp)
{
}

/**@brief	특정 클라이언트가 접속 해제 했음을 알린다.
 *			내부적으로는 해당 ip를 리스트박스에서 목록 제거 할 뿐이다.
 * @param	a_globalIp	접속 해제한 클라이언트의 global ip
 * @param	a_localIp	접속 해제한 클라이언트의 local Ip
 * @remarks	서버 전용 함수이므로 랩터에서는 구현하지 않는다.
 */
void CDharaniExternSD::NotifyLeft(in_addr *a_globalIp, in_addr *a_localIp)
{
}