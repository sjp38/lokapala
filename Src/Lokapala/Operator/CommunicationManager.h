/**@file	CommunicationManager.h
 * @brief	CCommunicationManager Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

#include "DharaniInterface.h"
#include "DharaniFacade.h"

#include "tinyxml.h"

/**@ingroup	GroupCCM
 * @class	CCommunicationManager
 * @brief	CCM�� �������� ����. �ٶ�� ������Ʈ�� ���⼭�� ����Ѵ�.
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
	void SendLoginAcceptedNotifyMessage(void *a_acceptedData);
	void SendShutdownInstruction(void *a_argument);
	void SendRebootInstruction(void *a_argument);
	void SendBanUserInstruction(void *a_argument);
	void SendExecuteProcessInstruction(void *a_argument);
	void SendKillProcessInstruction(void *a_argument);
	void SendGenocideProcessInstruction(void *a_argument);
	void SendWarningMessage(void *a_argument);
	void SendStatusReport(void *a_statusReport);

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