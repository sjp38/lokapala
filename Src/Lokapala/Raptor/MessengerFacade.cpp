/**@file	MessengerFacade.cpp
 * @brief	MSM의 Facade의 멤버 함수 구현.
 * @author	siva
 */

#include "stdafx.h"
#include "MessengerFacade.h"

#include "MessengerManager.h"

/**@brief	텍스트 메세지를 오퍼레이터에게 보낸다.
 */
void CMessengerFacade::PostTextMessageToOperator(CString *a_message)
{
	CMessengerManager::Instance()->PostTextMessageToOperator(a_message);
}

/**@brief	오퍼레이터로부터 텍스트 메세지를 받는다.
 */
void CMessengerFacade::ReceiveTextMessageFromOperator(CString *a_message)
{
	CMessengerManager::Instance()->ReceiveTextMessageFromOperator(a_message);
}