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
void CCommunicationFacade::SendLoginAcceptedNotifyMessage(void *a_acceptedData)
{
	CCommunicationManager::Instance()->SendLoginAcceptedNotifyMessage(a_acceptedData);
}

/**@brief	특정 사용자의 컴퓨터를 꺼버린다.
 * @param	a_argment	목표 사용자의 위치, 동작 시의 추가 행동 등을 담은 정보체의 포인터
 */
void CCommunicationFacade::SendShutdownInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendShutdownInstruction(a_argument);
}

/**@brief	특정 사용자의 컴퓨터를 재부팅 시킨다.
 * @param	a_argment	목표 사용자의 위치, 동작 시의 추가 행동 등을 담은 정보체의 포인터
 */
void CCommunicationFacade::SendRebootInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendRebootInstruction(a_argument);
}

/**@brief	특정 사용자를 강제 로그아웃 시킨다.
 * @param	a_argment	목표 사용자의 위치, 동작 시의 추가 행동 등을 담은 정보체의 포인터
 */
void CCommunicationFacade::SendBanUserInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendBanUserInstruction(a_argument);
}

/**@brief	특정 사용자에게 특정 프로세스를 실행 시킨다.
 * @param	a_argment	목표 사용자의 위치, 동작 시의 추가 행동 등을 담은 정보체의 포인터
 */
void CCommunicationFacade::SendExecuteProcessInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendExecuteProcessInstruction(a_argument);
}

/**@brief	특정 사용자의 특정 프로세스를 종료시킨다.
 * @param	a_argument	목표 사용자의 위치, 동작 시의 추가 행동 등을 담은 정보체의 포인터
 */
void CCommunicationFacade::SendKillProcessInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendKillProcessInstruction(a_argument);
}


/**@brief	특정 사용자의 실행중인 모든 프로세스를 죽인다.
 * @param	a_argment	목표 사용자의 위치, 동작 시의 추가 행동 등을 담은 정보체의 포인터
 */
void CCommunicationFacade::SendGenocideProcessInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendGenocideProcessInstruction(a_argument);
}

/**@brief	특정 사용자에게 경고 메세지를 날린다.
 * @param	a_argment	목표 사용자의 위치, 동작 시의 추가 행동 등을 담은 정보체의 포인터
 */
void CCommunicationFacade::SendWarningMessage(void *a_argument)
{
	CCommunicationManager::Instance()->SendWarningMessage(a_argument);
}

/**@brief	특정 사용자에게 상태 보고를 날린다.
 * @param	a_statusReport	상태 보고 정보를 담은 정보체의 포인터.
 */
void CCommunicationFacade::SendStatusReport(void *a_statusReport)
{
	CCommunicationManager::Instance()->SendStatusReport(a_statusReport);
}