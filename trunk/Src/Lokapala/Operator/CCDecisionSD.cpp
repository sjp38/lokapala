/**@file	CCDecisionSD.cpp
 * @brief	CCM의 DecisionSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "CCDecisionSD.h"

/**@brief	사용자의 로그인 정보에 대해 유효한 사용자인지 확인한다.
 * @param	a_loginRequestData	사용자 로그인 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
 */
void CCCDecisionSD::UserLogin(void *a_loginRequestData)
{
	CCBFMediator::Instance()->UserLogin(a_loginRequestData);
}


/**@brief	사용자의 실행한 프로세스 감시 보고에 대해, 실행해도 되는 프로세스인지 어떤지 확인, 처리해준다.
 * @param	a_executedProcessData	사용자가 실행한 프로세스에 대한 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
 */
void CCCDecisionSD::JudgeUserExecutedProcess(void *a_executedProcessData)
{
	CCBFMediator::Instance()->JudgeUserExecutedProcess(a_executedProcessData);
}


/**@brief	사용자로부터의 고장 상태 보고에 대한 처리.
 * @param	a_statusReportData	사용자가 보고한 고장 상태 보고 내용에 대한 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
 */
void CCCDecisionSD::PresentStatusReport(void *a_statusReportData)
{
	CCBFMediator::Instance()->PresentStatusReport(a_statusReportData);
}