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
	/**@brief	연결된 호스트에 대해 처리한다.	*/
	virtual void HostConnected(void *a_hostData) = 0;
	/**@brief	연결이 끊긴 호스트에 대해 처리한다.	*/
	virtual void HostDisconnected(void *a_hostData) = 0;
	/**@brief	사용자 로그인 처리. 올바른 사용자인지 확인한다.
	 * @param	a_loginRequestData	사용자 로그인 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
	 */
	virtual void JudgeLoginRequest(void *a_loginRequestData) = 0;

	/**@brief	사용자가 실행한 프로세스의 보고에 대한 처리.	*/
	virtual void JudgeUserExecutedProcess(void *a_executedProcessData) = 0;
	/**@brief	새로운 고장 상태 보고에 대한 처리	*/
	virtual void PresentStatusReport(void *a_statusReportData) = 0;
	/**@brief	특정 호스트의 컴퓨터를 종료시킨다.	*/
	virtual void ShutdownHost(void *a_argument) = 0;
	/**@brief	특정 호스트의 컴퓨터를 리부팅시킨다.	*/
	virtual void RebootHost(void *a_argument) = 0;
	/**@brief	특정 사용자를 강제로 로그아웃 시킨다.	*/
	virtual void BanUser(void *a_argument) = 0;
	/**@brief	특정 호스트의 특정 프로세스를 실행시킨다.	*/
	virtual void ExecuteHostProcess(void *a_argument) = 0;
	/**@brief	특정 호스트의 특정 프로세스를 종료시킨다.	*/
	virtual void KillHostProcess(void *a_argument) = 0;
	/**@brief	특정 호스트의 모든 프로세스를 실행시킨다.	*/
	virtual void GenocideHostProcess(void *a_argument) = 0;
	/**@brief	특정 호스트에게 경고를 한다.	*/
	virtual void WarnHost(void *a_argument) = 0;
	/**@brief	특정 호스트에게 상태 보고를 한다	*/
	virtual void SubmitStatusReportToHost(void *a_statusReport) = 0;
	/**@brief	특정 호스트의 랩터의 동작을 중지시킨다.	*/
	virtual void TerminateRaptorOnHost(void *a_argument) = 0;
};

#endif
