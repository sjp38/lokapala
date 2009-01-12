/**@file	ControlFacade.h
 * @brief	Control Manager�� Facade ����.
 * author	siva
 */

#ifndef CONTROL_FACADE_H
#define CONTROL_FACADE_H

#include "ControlBI.h"

/**@ingroup GroupCTM
 * @class	CControlFacade
 * @brief	CTM�� Facade.
 * @remarks	SingleTon�� ����Ѵ�.
 */
class CControlFacade : public CControlBI
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CControlFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CControlFacade();
		}
		return m_instance;
	}
protected :
	/**@brief	������	*/
	CControlFacade(){}
	/**@brief	�Ҹ���	*/
	~CControlFacade(){}
private :
	/**@brief	singleton	*/
	static CControlFacade *m_instance;
};

#endif