/**@file	DecisionManager.h
 * @brief	실질적 DCM의 행동을 하는 CDecisionManager 클래스를 정의한다.
 * @author	siva
 */

#ifndef DECISION_MANAGER_H
#define DECISION_MANAGER_H


/**@ingroup	GroupDCM
 * @class	CDecisionManager
 * @brief	랩터의 전체적 동작을 결정/행동한다.
 */
class CDecisionManager
{
public :
	static CDecisionManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDecisionManager();
		}
		return m_instance;
	}

	void Connected();
	void Disconnected();
	void LoginRequest(void *a_userInfo);
	void LoginAccepted(int a_level);
	void LoginOrderReceived(void *a_userInfo);
	void LogoutOrderReceived(void *a_message);	
	void ShutdownOrderReceived(void *a_message);
	void RebootOrderReceived(void *a_message);
	void GenocideProcessesOrderReceived(void *a_message);
	void KillProcessOrderReceived(void *a_processName);
	void ExecuteProcessOrderReceived(void *a_processName);
	void StatusReportReceived(void *a_statusReport);
	void RaptorTerminationOrderReceived();

	void ReportExecutedProcess(CString *a_executedProcess);
	void ReportStatus(void *a_status);

	void UserTryingToKillMe(void);

protected :
	CDecisionManager(){}
	~CDecisionManager(){}

private :
	static CDecisionManager *m_instance;
};

#endif
