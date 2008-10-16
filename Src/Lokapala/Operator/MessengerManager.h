/**@file	MessengerManager.h
 * @brief	CMessengerManager Ŭ������ �����Ѵ�.
 * @author	siva
 */


#ifndef MESSENGER_MANAGER_H
#define MESSENGER_MANAGER_H

/**@ingorup	GroupMSM
 * @class	CMessengerManager
 * @brief	�޽��� ���� ����� ���������� �����Ѵ�.
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

	void PostTextMessageTo(void *a_message);
	void ReceiveTextMessageFrom(void *a_message);

protected :
	CMessengerManager(){}
	~CMessengerManager(){}

private :
	static CMessengerManager *m_instance;

};

#endif