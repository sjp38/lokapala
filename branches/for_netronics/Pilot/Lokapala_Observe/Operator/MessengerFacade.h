/**@file	MessengerFacade.h
 * @brief	Messenger Manager의 Facade 정의
 * @author	siva
 */

#ifndef MESSENGER_FACADE_H
#define MESSENGER_FACADE_H

#include "MessengerBI.h"

/**@ingroup GroupMSM
 * @class	CMessengerFacade
 * @brief	Messenger Manager의 Facade 정의
 * @remarks	SingleTon 사용
 */
class CMessengerFacade : public CMessengerBI
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CMessengerFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CMessengerFacade();
		}
		return m_instance;
	}
protected :
	/**@brief	생성자	*/
	CMessengerFacade(){}
	/**@brief	소멸자	*/
	~CMessengerFacade(){}
private :
	/**@brief	SingleTon	*/
	static CMessengerFacade *m_instance;
};

#endif