/**@file	ObserveFacade.h
 * @brief	Observe Manager의 Facade 정의.
 * author	siva
 */

#ifndef OBSERVE_FACADE_H
#define OBSERVE_FACADE_H

#include "ObserveBI.h"

/**@ingroup GroupOSM
 * @class	CObserveFacade
 * @brief	OSM의 Facade.
 * @remarks	SingleTon을 사용한다.
 */
class CObserveFacade : public CObserveBI
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CObserveFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CObserveFacade();
		}
		return m_instance;
	}
protected :
	/**@brief	생성자	*/
	CObserveFacade(){}
	/**@brief	소멸자	*/
	~CObserveFacade(){}
private :
	/**@brief	singleton	*/
	static CObserveFacade *m_instance;
};

#endif