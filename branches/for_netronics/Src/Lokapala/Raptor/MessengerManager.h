/**@file	MessengerManager.h
 * @brief	CMessengerManager 클래스를 구현한다.
 * @author	siva
 */

#ifndef MESSENGER_MANAGER_H
#define MESSENGER_MANAGER_H

/**@ingroup	GroupMSM
 * @class	CMessengerManager
 * @brief	메신저 컴포넌트의 실질적 동작을 책임진다.
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