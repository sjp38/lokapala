/**@file	MessengerFacade.cpp
 * @brief	MSM�� Facade�� ��� �Լ� ����.
 * @author	siva
 */

#include "stdafx.h"
#include "MessengerFacade.h"

#include "MessengerManager.h"

/**@brief	�ؽ�Ʈ �޼����� ���۷����Ϳ��� ������.
 */
void CMessengerFacade::PostTextMessageTo(void *a_message)
{
	CMessengerManager::Instance()->PostTextMessageTo(a_message);
}

/**@brief	���۷����ͷκ��� �ؽ�Ʈ �޼����� �޴´�.
 */
void CMessengerFacade::ReceiveTextMessageFrom(void *a_message)
{
	CMessengerManager::Instance()->ReceiveTextMessageFrom(a_message);
}