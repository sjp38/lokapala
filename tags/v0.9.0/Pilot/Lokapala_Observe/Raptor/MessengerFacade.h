/**@file	MessengerFacade.h
 * @brief	Messenger Manager�� Facade ����
 * @author	siva
 */

#ifndef MESSENGER_FACADE_H
#define MESSENGER_FACADE_H

#include "MessengerBI.h"

/**@ingroup GroupMSM
 * @class	CMessengerFacade
 * @brief	Messenger Manager�� Facade ����
 * @remarks	SingleTon ���
 */
class CMessengerFacade : public CMessengerBI
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
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
	/**@brief	������	*/
	CMessengerFacade(){}
	/**@brief	�Ҹ���	*/
	~CMessengerFacade(){}
private :
	/**@brief	SingleTon	*/
	static CMessengerFacade *m_instance;
};

#endif