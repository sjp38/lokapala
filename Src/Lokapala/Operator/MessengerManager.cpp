/**@file	MessengerManager.cpp
 * @brief	CMessengerManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "MessengerManager.h"

#include "MessageDTO.h"


/**@brief	오퍼레이터에게 텍스트 메세지를 보낸다.
 */
void CMessengerManager::PostTextMessageTo(void *a_message)
{
	/*
	CMessageDTO *messageData = (CMessageDTO *)a_message;
	CMSCommunicationSD::Instance()->PostTextMessageToOperator(a_message);*/
}

/**@brief	오퍼레이터로부터 텍스트 메세지를 받았을 때 호출된다.
 */
void CMessengerManager::ReceiveTextMessageFrom(void *a_message)
{
	CMessageDTO *messageData = (CMessageDTO *)a_message;
	CString message = messageData->m_globalIp + _T("/") + messageData->m_localIp + _T(":") + messageData->m_message;

	CCBFMediator::Instance()->Notify(&message);
}