/**@file	DecisionManager.h
 * @brief	CDecisionManager 클래스를 정의한다.
 * @author	siva
 */

#ifndef DECISION_MANAGER_H
#define DECISION_MANAGER_H


/**@ingroup	GroupDCM
 * @class	CDecisionManager
 * @brief	DCM의 실질적인 행동을 한다.
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

	void UserLogin(void *a_loginRequestData);
	void JudgeUserExecutedProcess(void *a_executedProcessData);
	void PresentStatusReport(void *a_statusReportData);
	void RemoveFromAcceptedUser(CString a_globalIp, CString a_localIp);

protected :
	CDecisionManager(){}
	~CDecisionManager(){}

private :
	static CDecisionManager *m_instance;

	void DoReactionsTo(void *a_executedProcess, void *a_rules);
	void DoReactionTo(void *a_executedProcess, void *a_rule);
};

#endif