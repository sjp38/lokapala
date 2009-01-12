/**@file	MessengerManager.cpp
 * @brief	CMessengerManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "MessengerManager.h"

#include "MessageDTO.h"
#include "MSCommunicationSD.h"


/**@brief	���Ϳ��� �ؽ�Ʈ �޼����� ������.
 */
void CMessengerManager::PostTextMessageTo(void *a_messageData)
{	
	CMessageDTO *messageData = (CMessageDTO *)a_messageData;		//�α� �����͸� ���� �� ����.
	CMSCommunicationSD::Instance()->SendTextMessageToRaptor(a_messageData);	

	CCBFMediator::Instance()->NotifyTextMessageToRaptorSended(messageData->m_hostAddress, messageData->m_message);
}

/**@brief	���ͷκ��� �ؽ�Ʈ �޼����� �޾��� �� ȣ��ȴ�.
 */
void CMessengerManager::ReceiveTextMessageFrom(void *a_messageData)
{
	CMessageDTO *messageData = (CMessageDTO *)a_messageData;

	CCBFMediator::Instance()->NotifyRaptorMessageReceived(messageData->m_hostAddress, messageData->m_message);
}