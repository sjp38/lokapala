/**@file	CommunicationManager.h
 * @brief	CCommunicationManager 클래스를 정의한다.
 * @author	siva
 */

#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

#include "DharaniInterface.h"
#include "DharaniFacade.h"

/**@ingroup	GroupCCM
 * @class	CCommunicationManager
 * @brief	CCM의 실질적인 동작. 다라니 컴포넌트는 여기서만 사용한다.
 */
class CCommunicationManager
{
public :
	static CCommunicationManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CCommunicationManager();
		}
		return m_instance;
	}

	void InitiallizeAsServer();
	void SendTextMessageTo(CString a_targetAddress, CString a_message);
	void BroadcastTextMessage(CString a_message);

	void NotifyReceived(CString a_message, CString a_localIp, CString a_globalIp);
	void NotifyAccepted(void *a_acceptedData);

	void LoginProcess(CString *a_message, CString *a_localIp, CString *a_globalIp);

protected :
	CCommunicationManager(){}
	~CCommunicationManager(){}

private :
	static CCommunicationManager *m_instance;
};

#endif