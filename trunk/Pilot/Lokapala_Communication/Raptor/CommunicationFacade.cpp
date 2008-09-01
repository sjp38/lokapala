/**@file	CommunicationFacade.cpp
 * @brief	CCM의 Facade의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include <atlconv.h>
#include "DharaniInterface.h"
#include "DharaniFacade.h"
#include "CommunicationFacade.h"

/**@brief	소켓을 생성한 후, 오퍼레이터에게 connect 한다.
 */
void CCommunicationFacade::Initiallize()
{
	CDharaniInterface *dharaniInterface;
	dharaniInterface = new CDharaniFacade();
	dharaniInterface->DharaniClientInitiallize();
}


/**@brief	텍스트 메세지를 오퍼레이터에게 보낸다.
 */
void CCommunicationFacade::SendTextMessage(CString a_message)
{
	USES_CONVERSION;
	CDharaniDTO message;
	message.m_message = W2A(a_message);

	CDharaniInterface *dharaniInterface;
	dharaniInterface = new CDharaniFacade();
	dharaniInterface->DharaniSendTextToServer(&message);
}