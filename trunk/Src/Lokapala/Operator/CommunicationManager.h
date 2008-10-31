/**@file	CommunicationManager.h
 * @brief	CCommunicationManager 클래스를 정의한다.
 * @author	siva
 */

#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

#include "DharaniInterface.h"
#include "DharaniFacade.h"

#include "tinyxml.h"

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

	//dharani -> ccm
	void RaptorAccepted(CString a_address);
	void RaptorLeaved(CString a_globalIp, CString a_localIp);
	void NotifyReceived(CString a_message, CString a_localIp, CString a_globalIp);	

	//Operator -> Raptor
	void NotifyAccepted(void *a_acceptedData);
	void ShutdownUser(void *a_argument);
	void RebootUser(void *a_argument);
	void LogoutUser(void *a_argument);
	void ExecuteUser(void *a_argument);
	void GenocideUser(void *a_argument);
	void WarnUser(void *a_argument);

protected :
	CCommunicationManager(){}
	~CCommunicationManager(){}

private :	
	static CCommunicationManager *m_instance;
	
	TiXmlElement *GetXmlParsedPacketElement(CString *a_packet);
	//Raptor -> Operator
	void LoginRequestReceived(CString *a_message, CString *a_hostAddress);
	void UserExecutedProcessReceived(CString *a_message, CString *a_hostAddress);	
	void StatusReportReceived(CString *a_message, CString *a_hostAddress);

	void MessageReceived(CString *a_message, CString *a_hostAddress);
};

#endif