/**@file	MessengerManager.cpp
 * @brief	CMessengerManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "MessengerManager.h"

#include "MessageDTO.h"
#include "MSCommunicationSD.h"


/**@brief	랩터에게 텍스트 메세지를 보낸다.
 */
void CMessengerManager::PostTextMessageTo(void *a_messageData)
{	
	CMessageDTO *messageData = (CMessageDTO *)a_messageData;		//로그 데이터를 남길 때 쓴다.
	CMSCommunicationSD::Instance()->SendTextMessageToRaptor(a_messageData);	

	CCBFMediator::Instance()->NotifyTextMessageToRaptorSended(messageData->m_hostAddress, messageData->m_message);
}

/**@brief	랩터로부터 텍스트 메세지를 받았을 때 호출된다.
 */
void CMessengerManager::ReceiveTextMessageFrom(void *a_messageData)
{
	CMessageDTO *messageData = (CMessageDTO *)a_messageData;

	CCBFMediator::Instance()->NotifyRaptorMessageReceived(messageData->m_hostAddress, messageData->m_message);
}