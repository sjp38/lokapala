/**@file	NeverDieFacade.h
 * @brief	NeverDie Manager의 Facade 정의.
 * author	siva
 */

#ifndef NEVERDIE_FACADE_H
#define NEVERDIE_FACADE_H

#include "NeverDieBI.h"

/**@ingroup GroupNDM
 * @class	CNeverDieFacade
 * @brief	NDM의 Facade.
 * @remarks	SingleTon을 사용한다.
 */
class CNeverDieFacade : public CNeverDieBI
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
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
	/**@brief	생성자	*/
	CNeverDieFacade(){m_state = false;}
	/**@brief	소멸자	*/
	~CNeverDieFacade(){}
private :
	/**@brief	현재 프로그램이 죽어도 되는지 안되는지	*/
	bool m_state;
	/**@brief	singleton	*/
	static CNeverDieFacade *m_instance;
};

#endif