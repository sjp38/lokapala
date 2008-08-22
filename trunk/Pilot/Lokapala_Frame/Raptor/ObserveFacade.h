/**@file	ObserveFacade.h
 * @brief	Observe Manager�� Facade ����.
 * author	siva
 */

#ifndef OBSERVE_FACADE_H
#define OBSERVE_FACADE_H

#include "ObserveBI.h"

/**@ingroup GroupOSM
 * @class	CObserveFacade
 * @brief	OSM�� Facade.
 * @remarks	SingleTon�� ����Ѵ�.
 */
class CObserveFacade : public CObserveBI
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
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
	/**@brief	������	*/
	CObserveFacade(){}
	/**@brief	�Ҹ���	*/
	~CObserveFacade(){}
private :
	/**@brief	singleton	*/
	static CObserveFacade *m_instance;
};

#endif