/**@file	CCDecisionSD.cpp
 * @brief	CCM의 DecisionSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "CCDecisionSD.h"

/**@brief	로그인 되었음을 알리며 그에 따른 서비스를 요청한다.
 * @param	a_level	로그인 허용된 사용자의 레벨.
 */
void CCCDecisionSD::LoginAccepted(int a_level)
{
	CCBFMediator::Instance()->LoginAccepted(a_level);
}

/**@brief	강제 로그인 명령이 들어왔음을 알린다.
 */
void CCCDecisionSD::Login(void *a_message)
{
	CCBFMediator::Instance()->LoginOrderReceived(a_message);
}

/**@brief	강제 로그아웃 명령이 들어왔음을 알린다.
 */
void CCCDecisionSD::Logout(void *a_message)
{
	CCBFMediator::Instance()->LogoutOrderReceived(a_message);
}

/**@brief	강제 컴퓨터 종료 명령이 들어왔음을 알린다.
 */
void CCCDecisionSD::Shutdown(void *a_message)
{
	CCBFMediator::Instance()->ShutdownOrderReceived(a_message);
}

/**@brief	강제 재부팅 명령이 들어왔음을 알린다.
 */
void CCCDecisionSD::Reboot(void *a_message)
{
	CCBFMediator::Instance()->RebootOrderReceived(a_message);
}

/**@brief	실행중인 모든 프로세스 종료 명령이 들어왔음을 알린다.
 */
void CCCDecisionSD::GenocideProcesses(void *a_processName)
{
	CCBFMediator::Instance()->GenocideProcessesOrderReceived(a_processName);
}

/**@brief	특정 프로세스 종료 명령이 들어왔음을 알린다.
 */
void CCCDecisionSD::KillProcess(void *a_processName)
{
	CCBFMediator::Instance()->KillProcessOrderReceived(a_processName);
}

/**@brief	특정 프로세스 실행 명령이 들어왔음을 알린다.
 */
void CCCDecisionSD::ExecuteProcess(void *a_processName)
{
	CCBFMediator::Instance()->ExecuteProcessOrderReceived(a_processName);
}

/**@brief	상태 정보가 들어왔음을 알린다.
 */
void CCCDecisionSD::StatusReportReceived(void *a_statusReport)
{
	CCBFMediator::Instance()->StatusReportReceived(a_statusReport);
}

/**@brief	랩터 동작 중지 명령을 받았음을 알린다.
 */
void CCCDecisionSD::TerminateRaptor()
{
	CCBFMediator::Instance()->RaptorTerminationOrderReceived();
}
