/**@file	MessengerFacade.cpp
 * @brief	MSM�� Facade�� ��� �Լ� ����.
 * @author	siva
 */

#include "stdafx.h"
#include "MessengerFacade.h"

#include "MessengerManager.h"

/**@brief	�ؽ�Ʈ �޼����� ���۷����Ϳ��� ������.
 */
void CMessengerFacade::PostTextMessageToOperator(CString *a_message)
{
	CMessengerManager::Instance()->PostTextMessageToOperator(a_message);
}

/**@brief	���۷����ͷκ��� �ؽ�Ʈ �޼����� �޴´�.
 */
void CMessengerFacade::ReceiveTextMessageFromOperator(CString *a_message)
{
	CMessengerManager::Instance()->ReceiveTextMessageFromOperator(a_message);
}