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
	/**@brief	오퍼레이터와 연결이 되었을 때.	*/
	virtual void Connected() = 0;
	/**@brief	오퍼레이터와의 연결이 끊겼을 때.	*/
	virtual void Disconnected() = 0;
	/**@brief	오퍼레이터에게 로그인 요청을 한다.	 */
	virtual void LoginRequest(void *a_userInfo) = 0;
	/**@brief	로그인 허용에 대해 서비스를 한다.	 */
	virtual void LoginAccepted(int a_level) = 0;
	/**@brief	강제 로그인 명령을 받았을 때.	*/
	virtual void LoginOrderReceived(void *a_userInfo) = 0;
	/**@brief	강제 로그아웃 명령을 받았을 때.	*/
	virtual void LogoutOrderReceived(void *a_message) = 0;	
	/**@brief	강제 컴퓨터 종료 명령을 받았을 때.	*/
	virtual void ShutdownOrderReceived(void *a_message) = 0;
	/**@brief	강제 컴퓨터 리부팅 명령을 받았을 때.	*/
	virtual void RebootOrderReceived(void *a_message) = 0;
	/**@brief	실행중인 모든 프로세스 종료 명령을 받았을 때.	*/
	virtual void GenocideProcessesOrderReceived(void *a_message) = 0;
	/**@brief	특정 프로세스 종료 명령을 받았을 때.	*/
	virtual void KillProcessOrderReceived(void *a_processName) = 0;
	/**@brief	특정 프로세스 실행 명령을 받았을 때.	*/
	virtual void ExecuteProcessOrderReceived(void *a_processName) = 0;
	/**@brief	오퍼레이터로부터 상태 보고가 내려왔을 때.	*/
	virtual void StatusReportReceived(void *a_statusReport) = 0;
	/**@brief	오퍼레이터로부터 동작 정지 명령이 내려왔을 때.	*/
	virtual void RaptorTerminationOrderReceived() = 0;

	/**@brief	실행된 프로세스의 이름을 보고받는다.	*/
	virtual void ReportExecutedProcess(CString *a_executedProcess) = 0;
	/**@brief	상황 변화를 보고한다.	*/
	virtual void ReportStatus(void *a_status) = 0;

	virtual void UserTryingToKillMe() = 0;
};

#endif