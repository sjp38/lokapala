/**@file	DecisionFacade.cpp
 * @brief	DCM의 Facade의 멤버 함수 구현
 * author	siva
 */

#include "stdafx.h"
#include "DecisionFacade.h"

#include "DecisionManager.h"

/**@brief	사용자 로그인 처리. 올바른 사용자인지 확인한다.
 * @param	a_loginRequestData	사용자 로그인 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
 */
void CDecisionFacade::UserLogin(void *a_loginRequestData)
{
	CDecisionManager::Instance()->UserLogin(a_loginRequestData);
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