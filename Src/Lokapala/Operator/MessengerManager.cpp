/**@file	MessengerManager.cpp
 * @brief	CMessengerManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "MessengerManager.h"

#include "MessageDTO.h"


/**@brief	���۷����Ϳ��� �ؽ�Ʈ �޼����� ������.
 */
void CMessengerManager::PostTextMessageTo(void *a_message)
{
	/*
	CMessageDTO *messageData = (CMessageDTO *)a_message;
	CMSCommunicationSD::Instance()->PostTextMessageToOperator(a_message);*/
}

/**@brief	���۷����ͷκ��� �ؽ�Ʈ �޼����� �޾��� �� ȣ��ȴ�.
 */
void CMessengerManager::ReceiveTextMessageFrom(void *a_message)
{
	CMessageDTO *messageData = (CMessageDTO *)a_message;
	CString message = messageData->m_globalIp + _T("/") + messageData->m_localIp + _T(":") + messageData->m_message;

	CCBFMediator::Instance()->Notify(&message);
}