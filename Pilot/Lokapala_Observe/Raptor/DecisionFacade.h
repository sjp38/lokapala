/**@file	DecisionFacade.h
 * @brief	DCM 의 Facade 정의
 * @author	siva
 */

#ifndef DECISION_FACADE_H
#define DECISION_FACADE_H

#include "DecisionBI.h"

/**@ingroup GroupDCM
 * @class	CDecisionFacade
 * @brief	DCM의 Facade.
 * @remarks	SingleTon을 사용한다.
 */
class CDecisionFacade : public CDecisionBI
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CDecisionFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDecisionFacade();
		}
		return m_instance;
	}
protected :
	/**@brief	생성자	*/
	CDecisionFacade(){}
	/**@brief	소멸자	*/
	~CDecisionFacade(){}
private :
	/**@brief	singleton	*/
	static CDecisionFacade *m_instance;
			
};

#endif