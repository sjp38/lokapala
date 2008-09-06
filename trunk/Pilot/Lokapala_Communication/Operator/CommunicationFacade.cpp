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
	dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniServerInitiallize();
}

/**@brief	문자열을 보낸다.
 */
void CCommunicationFacade::SendTextMessage(CString a_message)
{
	int tokenIndex = 0;
	CString address;
	address = a_message.Tokenize(_T(":"), tokenIndex);
	
	USES_CONVERSION;
	CDharaniDTO message;
	message.m_message = W2A(a_message);
	if(address==a_message)
	{
		message.m_globalIp = 0;
		message.m_localIp = 0;
	}
	else
	{
		tokenIndex = 0;
		message.m_globalIp = inet_addr( W2A(address.Tokenize(_T("/"), tokenIndex)) );
		message.m_localIp = inet_addr( W2A(address.Tokenize(_T("/"), tokenIndex)) );
	}

	CDharaniInterface *dharaniInterface;
	dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniSendTextMessageTo(&message);
}