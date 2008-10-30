/**@file	MessengerManager.h
 * @brief	CMessengerManager Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef MESSENGER_MANAGER_H
#define MESSENGER_MANAGER_H

/**@ingroup	GroupMSM
 * @class	CMessengerManager
 * @brief	�޽��� ������Ʈ�� ������ ������ å������.
 */
class CMessengerManager
{
public :
	static CMessengerManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CMessengerManager();
		}
		return m_instance;
	}

	void PostTextMessageToOperator(CString *a_message);
	void ReceiveTextMessageFromOperator(CString *a_message);

protected :
	CMessengerManager(){}
	~CMessengerManager(){}

private :
	static CMessengerManager *m_instance;

};


#endif