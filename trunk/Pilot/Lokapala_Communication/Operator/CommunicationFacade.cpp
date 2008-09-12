/**@file	CommunicationFacade.cpp
 * @brief	CCM의 Facade의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include <atlconv.h>
#include "CommunicationFacade.h"

/**@brief	서버로써의 통신을 위한 초기화를 한다.
 */
void CCommunicationFacade::InitiallizeAsServer()
{
	CDharaniInterface *dharaniInterface;
	dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniServerInitiallize();
}

/**@brief	특정 주소의 raptor에게 문자열을 보낸다.
 * @param	a_targetAddress	문자열을 받을 raptor의 ip 주소
 * @param	a_message	보낼 문자열 메세지.
 */
void CCommunicationFacade::SendTextMessageTo(CString a_targetAddress, CString a_message)
{
	USES_CONVERSION;
	CDharaniDTO message;
	int tokenIndex = 0;
	message.m_globalIp = inet_addr( W2A(a_targetAddress.Tokenize(_T("/"), tokenIndex)) );
	message.m_localIp = inet_addr( W2A(a_targetAddress.Tokenize(_T("/"), tokenIndex)) );
	message.m_message = W2A(a_message);

	CDharaniInterface *dharaniInterface;
	dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniSendTextMessageTo(&message);
}

/**@brief	연결되어 있는 모든 raptor에게 문자를 보낸다.
 * @param	a_message	보낼 문자열 메세지.
 */
void CCommunicationFacade::BroadcastTextMessage(CString a_message)
{	
	USES_CONVERSION;
	CDharaniDTO message;
	message.m_message = W2A(a_message);
	message.m_globalIp = 0;
	message.m_localIp = 0;

	CDharaniInterface *dharaniInterface;
	dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniBroadcastTextMessage(&message);
}