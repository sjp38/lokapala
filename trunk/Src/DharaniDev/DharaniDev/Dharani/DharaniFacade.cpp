/**@file	DharaniFacade.cpp
 * @brief	DharaniFacade의 멤버 함수들을 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DharaniClientManager.h"
#include "DharaniServerManager.h"
#include "DharaniFacade.h"

/**@brief	dharani 컴포넌트의 서버 모델 초기화. 리슨 소켓을 만들고 IOCP를 위한 준비 단계를 수행한다.
 */
void CDharaniFacade::DharaniServerInitiallize()
{
	CDharaniServerManager::Instance()->Initiallize();
}

/**@brief	dharani 컴포넌트의 클라이언트 모델 초기화.
 * @return	정상적으로 초기화 했을 때 0, 문제가 발생 했을 때 -1
 */
int CDharaniFacade::DharaniClientInitiallize(DWORD a_ServerAddress)
{
	return CDharaniClientManager::Instance()->Initiallize(a_ServerAddress);
}

/**@brief	특정 클라이언트에게 메세지를 날린다.
 * @param	a_sendData	보낼 메세지와 목적 클라이언트의 주소를 가지고 있다.
 */
void CDharaniFacade::DharaniSendTextMessageTo(CDharaniDTO *a_sendData)
{
	PTR_SOCKET_DATA destiny = CDharaniServerManager::Instance()->GetSocketByAddress(a_sendData->m_globalIp, a_sendData->m_localIp);
	CDharaniServerManager::Instance()->SendMessageTo(destiny, a_sendData->m_message);
}

/**@brief	연결되어 있는 모든 클라이언트에게 메세지를 날린다.
 * @param	a_sendData	보낼 메세지를 가지고 있다.
 */
void CDharaniFacade::DharaniBroadcastTextMessage(CDharaniDTO *a_sendData)
{
	CDharaniServerManager::Instance()->BroadcastTextMessage(a_sendData->m_message);
}

/**@brief	서버에게 메세지를 날린다.
 */
void CDharaniFacade::DharaniSendTextToServer(CDharaniDTO *a_sendData)
{
	CDharaniClientManager::Instance()->SendTextMessage(a_sendData->m_message);
}
