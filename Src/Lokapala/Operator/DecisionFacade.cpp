/**@file	DecisionFacade.cpp
 * @brief	DCM의 Facade의 멤버 함수 구현
 * author	siva
 */

#include "stdafx.h"
#include "DecisionFacade.h"

#include "DecisionManager.h"

/**@brief	접속한 호스트에 대한 처리
 */
void CDecisionFacade::HostConnected(void *a_hostData)
{
	CDecisionManager::Instance()->HostConnected(a_hostData);
}

/**@brief	접속 종료한 호스트에 대한 처리
 */
void CDecisionFacade::HostDisconnected(void *a_hostData)
{
	CDecisionManager::Instance()->HostDisconnected(a_hostData);
}

/**@brief	사용자 로그인 처리. 올바른 사용자인지 확인한다.
 * @param	a_loginRequestData	사용자 로그인 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
 */
void CDecisionFacade::JudgeLoginRequest(void *a_loginRequestData)
{
	CDecisionManager::Instance()->JudgeLoginRequest(a_loginRequestData);
}


/**@brief	사용자 실행 프로세스에 대한 처리.
 */
void CDecisionFacade::JudgeUserExecutedProcess(void *a_executedProcessData)
{
	CDecisionManager::Instance()->JudgeUserExecutedProcess(a_executedProcessData);
}


/**@brief	새로운 고장 상태 보고에 대한 처리.
 */
void CDecisionFacade::PresentStatusReport(void *a_statusReportData)
{
	CDecisionManager::Instance()->PresentStatusReport(a_statusReportData);
}


/**@brief	특정 호스트의 컴퓨터를 종료 시킨다.
 */
void CDecisionFacade::ShutdownHost(void *a_argument)
{
	CDecisionManager::Instance()->ShutdownHost(a_argument);
}

/**@brief	특정 호스트의 컴퓨터를 리부팅 시킨다.
 */
void CDecisionFacade::RebootHost(void *a_argument)
{
	CDecisionManager::Instance()->RebootHost(a_argument);
}

/**@brief	특정 사용자를 강제로 로그아웃 시킨다.
 */
void CDecisionFacade::BanUser(void *a_argument)
{
	CDecisionManager::Instance()->BanUser(a_argument);
}

/**@brief	특정 호스트의 특정 프로세스를 실행시킨다.
 */
void CDecisionFacade::ExecuteHostProcess(void *a_argument)
{
	CDecisionManager::Instance()->ExecuteHostProcess(a_argument);
}

/**@brief	특정 호스트의 특정 프로세스를 종료 시킨다.
 */
void CDecisionFacade::KillHostProcess(void *a_argument)
{
	CDecisionManager::Instance()->KillHostProcess(a_argument);
}

/**@brief	특정 호스트의 모든 프로세스를 종료 시킨다.
 */
void CDecisionFacade::GenocideHostProcess(void *a_argument)
{
	CDecisionManager::Instance()->GenocideHostProcess(a_argument);
}

/**@brief	특정 호스트에게 경고를 날린다.
 */
void CDecisionFacade::WarnHost(void *a_argument)
{
	CDecisionManager::Instance()->WarnHost(a_argument);
}

/**@brief	특정 호스트에게 상태 보고를 날린다.
 */
void CDecisionFacade::SubmitStatusReportToHost(void *a_statusReport)
{
	CDecisionManager::Instance()->SubmitStatusReportToHost(a_statusReport);
}