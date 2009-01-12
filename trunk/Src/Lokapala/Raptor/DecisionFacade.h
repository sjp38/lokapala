/**@file	DecisionFacade.h
 * @brief	DCM �� Facade ����
 * @author	siva
 */

#ifndef DECISION_FACADE_H
#define DECISION_FACADE_H

#include "DecisionBI.h"

/**@ingroup GroupDCM
 * @class	CDecisionFacade
 * @brief	DCM�� Facade.
 * @remarks	SingleTon�� ����Ѵ�.
 */
class CDecisionFacade : public CDecisionBI
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CDecisionFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDecisionFacade();
		}
		return m_instance;
	}
	
	virtual void Connected();
	virtual void Disconnected();
	virtual void LoginRequest(void *a_userInfo);
	virtual void LoginAccepted(int a_level);
	virtual void LoginOrderReceived(void *a_userInfo);
	virtual void LogoutOrderReceived(void *a_message);	
	virtual void ShutdownOrderReceived(void *a_message);
	virtual void RebootOrderReceived(void *a_message);
	virtual void GenocideProcessesOrderReceived(void *a_message);
	virtual void KillProcessOrderReceived(void *a_processName);
	virtual void ExecuteProcessOrderReceived(void *a_processName);
	virtual void StatusReportReceived(void *a_stautsReport);
	virtual void RaptorTerminationOrderReceived();

	virtual void ReportExecutedProcess(CString *a_executedProcess);
	virtual void ReportStatus(void *a_status);
	virtual void UserTryingToKillMe(void);

protected :
	/**@brief	������	*/
	CDecisionFacade(){}
	/**@brief	�Ҹ���	*/
	~CDecisionFacade(){}
private :
	/**@brief	singleton	*/
	static CDecisionFacade *m_instance;
			
};

#endif