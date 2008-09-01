/**@file	CommunicationFacade.cpp
 * @brief	CCM의 Facade의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include <atlconv.h>
#include "CommunicationFacade.h"

/**@brief	통신을 위한 초기화를 한다.
 */
void CCommunicationFacade::Initiallize()
{
	CDharaniInterface *dharaniInterface;
	dharaniInterface = new CDharaniFacade();
	dharaniInterface->DharaniServerInitiallize();
}

/**@brief	문자열을 보낸다.
 */
void CCommunicationFacade::SendTextMessage(CString a_message)
{
	USES_CONVERSION;
	CDharaniDTO message;
	message.m_message = W2A(a_message);

	CDharaniInterface *dharaniInterface;
	dharaniInterface = new CDharaniFacade();
	dharaniInterface->DharaniBroadcastText(&message);
}