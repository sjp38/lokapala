/**@file	DecisionManager.h
 * @brief	CDecisionManager 클래스를 정의한다.
 * @author	siva
 */

#ifndef DECISION_MANAGER_H
#define DECISION_MANAGER_H


/**@ingroup	GroupDCM
 * @class	CDecisionManager
 * @brief	DCM의 실질적인 행동을 한다.\n
 *			추후, 데이터 처리, 명령, 판결로 클래스를 나눌것.
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

	void HostConnected(void *a_hostData);
	void HostDisconnected(void *a_hostData);

	void ReportStatusTo(CString *a_hostAddress);

	void JudgeLoginRequest(void *a_loginRequestData);
	void JudgeUserExecutedProcess(void *a_executedProcessData);
	void PresentStatusReport(void *a_statusReportData);

	void ShutdownHost(void *a_argument);
	void RebootHost(void *a_argument);
	void BanUser(void *a_argument);
	void ExecuteHostProcess(void *a_argument);
	void KillHostProcess(void *a_argument);
	void GenocideHostProcess(void *a_argument);
	void WarnHost(void *a_argument);
	void SubmitStatusReportToHost(void *a_statusReport);
	void TerminateRaptorOnHost(void *a_argument);

protected :
	CDecisionManager(){}
	~CDecisionManager(){}

private :
	static CDecisionManager *m_instance;


	void ControlRaptor(void *a_controlAction);
	void DoReactionsTo(void *a_executedProcess, void *a_rules);
	void DoReactionTo(void *a_executedProcess, void *a_rule);
	void RemoveFromAcceptedUser(CString a_hostAddress);
};

#endif
