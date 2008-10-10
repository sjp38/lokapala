/**@file	CommunicationFacade.cpp
 * @brief	CCM의 Facade의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "CommunicationFacade.h"

#include "CommunicationManager.h"

/**@brief	소켓을 생성한 후, 오퍼레이터에게 connect 한다.
 */
void CCommunicationFacade::Initiallize(DWORD a_ServerAddress)
{
	CCommunicationManager::Instance()->Initiallize(a_ServerAddress);
}

/**@brief	오퍼레이터와의 연결을 끊는다.
 */
void CCommunicationFacade::CloseConnection()
{
	CCommunicationManager::Instance()->CloseConnection();
}


/**@brief	텍스트 메세지를 오퍼레이터에게 보낸다.
 */
void CCommunicationFacade::SendTextMessage(CString a_message)
{
	CCommunicationManager::Instance()->SendTextMessage(a_message);
}


/**@brief	오퍼레이터에게 로그인 요청을 보낸다.
 */
void CCommunicationFacade::SendLoginRequest(void *a_userInfo)
{
	CCommunicationManager::Instance()->SendLoginRequest(a_userInfo);
}