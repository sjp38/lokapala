/**@file	CommunicationFacade.cpp
 * @brief	CCM의 Facade의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include <atlconv.h>
#include "CommunicationFacade.h"

#include "CommunicationManager.h"

/**@brief	서버로써의 통신을 위한 초기화를 한다.
 */
void CCommunicationFacade::InitiallizeAsServer()
{
	CCommunicationManager::Instance()->InitiallizeAsServer();
}

/**@brief	특정 주소의 raptor에게 문자열을 보낸다.
 * @param	a_targetAddress	문자열을 받을 raptor의 ip 주소
 * @param	a_message	보낼 문자열 메세지.
 */
void CCommunicationFacade::SendTextMessageTo(CString a_targetAddress, CString a_message)
{
	CCommunicationManager::Instance()->SendTextMessageTo(a_targetAddress, a_message);
}

/**@brief	연결되어 있는 모든 raptor에게 문자를 보낸다.
 * @param	a_message	보낼 문자열 메세지.
 */
void CCommunicationFacade::BroadcastTextMessage(CString a_message)
{	
	CCommunicationManager::Instance()->BroadcastTextMessage(a_message);
}

/**@brief	특정 사용자에게 로그인 허용 메세지를 전송한다.
 * @param	a_acceptedData	로그인 허용된 사용자의 주소 및 레벨 등의 데이터를 담은 정보체의 포인터
 */
void CCommunicationFacade::NotifyAccepted(void *a_acceptedData)
{
	CCommunicationManager::Instance()->NotifyAccepted(a_acceptedData);
}