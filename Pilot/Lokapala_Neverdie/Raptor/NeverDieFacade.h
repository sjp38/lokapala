/**@file	NeverDieFacade.h
 * @brief	NeverDie Manager�� Facade ����.
 * author	siva
 */

#ifndef NEVERDIE_FACADE_H
#define NEVERDIE_FACADE_H

#include "NeverDieBI.h"

/**@ingroup GroupNDM
 * @class	CNeverDieFacade
 * @brief	NDM�� Facade.
 * @remarks	SingleTon�� ����Ѵ�.
 */
class CNeverDieFacade : public CNeverDieBI
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CNeverDieFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CNeverDieFacade();
		}
		return m_instance;
	}

	virtual void StartNeverDie();
	virtual void StopNeverDie();
	virtual bool GetNeverDieState();
protected :
	/**@brief	������	*/
	CNeverDieFacade(){m_state = false;}
	/**@brief	�Ҹ���	*/
	~CNeverDieFacade(){}
private :
	/**@brief	���� ���α׷��� �׾ �Ǵ��� �ȵǴ���	*/
	bool m_state;
	/**@brief	singleton	*/
	static CNeverDieFacade *m_instance;
};

#endif