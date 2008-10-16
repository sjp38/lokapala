/**@file	MessengerManager.h
 * @brief	CMessengerManager 클래스를 정의한다.
 * @author	siva
 */


#ifndef MESSENGER_MANAGER_H
#define MESSENGER_MANAGER_H

/**@ingorup	GroupMSM
 * @class	CMessengerManager
 * @brief	메신저 관련 기능을 실질적으로 구현한다.
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