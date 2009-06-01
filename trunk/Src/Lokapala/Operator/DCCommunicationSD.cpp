/**@file	DCCommunicationSD.cpp
 * @brief	DCM의 CommunicationSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCCommunicationSD.h"


/**@brief	해당하는 주소의 사용자의 로그인 허용 메세지를 날린다.
 */
void CDCCommunicationSD::NotifyAccepted(void *a_acceptedData)
{
	CCBFMediator::Instance()->SendLoginAcceptedNotifyMessage(a_acceptedData);
}


/**@brief	특정 유저의 컴퓨터를 꺼버린다.
 */
void CDCCommunicationSD::SendShutdownInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendShutdownInstruction(a_argument);
}

/**@brief	특정 유저의 컴퓨터를 재부팅 시킨다.
 */
void CDCCommunicationSD::SendRebootInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendRebootInstruction(a_argument);
}

/**@brief	특정 유저를 로그아웃 시킨다.
 */
void CDCCommunicationSD::SendBanUserInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendBanUserInstruction(a_argument);
}

/**@brief	특정 유저에게 특정 프로세스를 실행시킨다.
 */
void CDCCommunicationSD::SendExecuteProcessInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendExecuteProcessInstruction(a_argument);
}

/**@brief	특정 유저의 특정 프로세스를 종료시킨다.
 */
void CDCCommunicationSD::SendKillProcessInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendKillProcessInstruction(a_argument);
}

/**@brief	특정 유저가 실행하고 있는 모든 프로세스를 죽인다.
 */
void CDCCommunicationSD::SendGenocideProcessInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendGenocideProcessInstruction(a_argument);
}

/**@brief	특정 유저에게 경고 메세지를 넘긴다.
 */
void CDCCommunicationSD::SendWarningMessage(void *a_argument)
{
	CCBFMediator::Instance()->SendWarningMessage(a_argument);
}

/**@brief	특정 호스트에게 상태 보고를 날린다.
 */
void CDCCommunicationSD::SendStatusReport(void *a_statusReport)
{
	CCBFMediator::Instance()->SendStatusReport(a_statusReport);
}

/**@brief	특정 호스트로 랩터 동작 중지 명령을 날린다.
 */
void CDCCommunicationSD::SendRaptorTerminationInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendRaptorTerminationInstruction(a_argument);
}
