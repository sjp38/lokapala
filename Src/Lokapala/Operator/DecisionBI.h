/**@file	DecisionBI.h
 * @brief	DCM의 Button Interface 정의
 * @author	siva
 */
#ifndef DECISION_BI_H
#define DECISION_BI_H

/**@ingroup	GroupDCM
 * @class	CDecisionBI
 * @brief	DCM의 Button Interface.
 * @remarks	인터페이스일 뿐이다.
 */
class CDecisionBI
{
public :
	/**@brief	사용자 로그인 처리. 올바른 사용자인지 확인한다.
	 * @param	a_loginRequestData	사용자 로그인 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
	 */
	virtual void JudgeLoginRequest(void *a_loginRequestData) = 0;

	/**@brief	사용자가 실행한 프로세스의 보고에 대한 처리.	*/
	virtual void JudgeUserExecutedProcess(void *a_executedProcessData) = 0;
	/**@brief	새로운 고장 상태 보고에 대한 처리	*/
	virtual void PresentStatusReport(void *a_statusReportData) = 0;
};

#endif