/**@file	DecisionFacade.cpp
 * @brief	DCM의 Facade의 멤버 함수 구현
 * author	siva
 */

#include "stdafx.h"
#include "DecisionFacade.h"

#include "DecisionManager.h"

/**@brief	오퍼레이터에게 로그인 요청을 한다.	*/
void CDecisionFacade::LoginRequest(void *a_userInfo)
{
	CDecisionManager::Instance()->LoginRequest(a_userInfo);
}


/**@brief	로그인 허용 메세지에 응하는 서비스를 한다.(사용자 방해 제거)
 */
void CDecisionFacade::LoginAccepted(int a_level)
{
	CDecisionManager::Instance()->LoginAccepted(a_level);
}

/**@brief	오퍼레이터로부터의 강제 로그인 명령에 대한 처리를 한다.
 */
void CDecisionFacade::LoginOrderReceived(void *a_message)
{
	CDecisionManager::Instance()->LoginOrderReceived(a_message);
}

/**@brief	오퍼레이터로부터의 강제 로그아웃 명령에 대한 처리를 한다.
 */
void CDecisionFacade::LogoutOrderReceived(void *a_message)
{
	CDecisionManager::Instance()->LogoutOrderReceived(a_message);
}

/**@brief	오퍼레이터로부터의 강제 컴퓨터 종료 명령에 대한 처리를 한다.
 */
void CDecisionFacade::ShutdownOrderReceived(void *a_message)
{
	CDecisionManager::Instance()->ShutdownOrderReceived(a_message);
}

/**@brief	오퍼레이터로부터의 강제 컴퓨터 리부팅 명령에 대한 처리를 한다.
 */
void CDecisionFacade::RebootOrderReceived(void *a_message)
{
	CDecisionManager::Instance()->RebootOrderReceived(a_message);
}

/**@brief	오퍼레이터로부터의 실행중인 모든 프로세스 종료 명령에 대한 처리를 한다.
 */
void CDecisionFacade::GenocideProcessesOrderReceived(void *a_message)
{
	CDecisionManager::Instance()->GenocideProcessesOrderReceived(a_message);
}

/**@brief	오퍼레이터로부터의 특정 프로세스 종료 명령에 대한 처리를 한다.
 */
void CDecisionFacade::KillProcessOrderReceived(void *a_processName)
{
	CDecisionManager::Instance()->KillProcessOrderReceived(a_processName);
}

/**@brief	오퍼레이터로부터의 특정 프로세스 실행 명령에 대한 처리를 한다.
 */
void CDecisionFacade::ExecuteProcessOrderReceived(void *a_processName)
{
	CDecisionManager::Instance()->ExecuteProcessOrderReceived(a_processName);
}



/**@brief	실행된 프로세스 이름을 보고받는다.
 */
void CDecisionFacade::ReportExecutedProcess(CString *a_executedProcess)
{
	CDecisionManager::Instance()->ReportExecutedProcess(a_executedProcess);
}


/**@brief	상황 변화를 보고한다.
 */
void CDecisionFacade::ReportStatus(void *a_status)
{
	CDecisionManager::Instance()->ReportStatus(a_status);
}