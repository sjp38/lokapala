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

	void HostConnected(void *a_hostData);
	void HostDisconnected(void *a_hostData);
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