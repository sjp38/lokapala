/**@file	DecisionManager.h
 * @brief	CDecisionManager Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef DECISION_MANAGER_H
#define DECISION_MANAGER_H


/**@ingroup	GroupDCM
 * @class	CDecisionManager
 * @brief	DCM�� �������� �ൿ�� �Ѵ�.\n
 *			����, ������ ó��, ���, �ǰ�� Ŭ������ ������.
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

	void LogoutUser(CString a_hostAddress);	

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