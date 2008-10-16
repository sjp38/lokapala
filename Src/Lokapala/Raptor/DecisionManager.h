/**@file	DecisionManager.h
 * @brief	������ DCM�� �ൿ�� �ϴ� CDecisionManager Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef DECISION_MANAGER_H
#define DECISION_MANAGER_H


/**@ingroup	GroupDCM
 * @class	CDecisionManager
 * @brief	������ ��ü�� ������ ����/�ൿ�Ѵ�.
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

	void LoginRequest(void *a_userInfo);
	void LoginAccepted(int a_level);
	void LoginOrderReceived(void *a_userInfo);
	void LogoutOrderReceived(void *a_message);	
	void ShutdownOrderReceived(void *a_message);
	void RebootOrderReceived(void *a_message);
	void GenocideProcessesOrderReceived(void *a_message);
	void KillProcessOrderReceived(void *a_processName);
	void ExecuteProcessOrderReceived(void *a_processName);

	void ReportExecutedProcess(CString *a_executedProcess);
	void ReportStatus(void *a_status);

protected :
	CDecisionManager(){}
	~CDecisionManager(){}

private :
	static CDecisionManager *m_instance;
};

#endif