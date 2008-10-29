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

	void JudgeLoginRequest(void *a_loginRequestData);
	void JudgeUserExecutedProcess(void *a_executedProcessData);
	void PresentStatusReport(void *a_statusReportData);	

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