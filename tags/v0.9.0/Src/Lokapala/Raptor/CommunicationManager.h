/**@file	CommunicationManager.h
 * @brief	CCM�� �ൿ�� ���������� �ϴ� CCommunicationManager Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

/**@ingroup	GroupCCM
 * @class	CCommunicationManager
 * @brief	�������� CCM�� ��� ������ ���/�����Ѵ�.\n
 *			�ٶ�� ������Ʈ�� ���⼭�� ����Ѵ�.
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

	bool m_connected;

	//raptor -> dharani
	void Initiallize(DWORD a_ServerAddress);
	void CloseConnection();
	void SendTextMessage(CString a_message);

	//dharani -> raptor
	void NotifyReceived(CString a_message);
	void Connected();
	void Disconnected();

	//raptor -> operator
	void SendLoginRequest(void *a_userInfo);
	void SendExecutedProcessReport(CString *a_executedProcess);
	void SendTextMessageToOperator(CString *a_message);
	void SendStatusReport(void *a_statusReport);

protected :
	CCommunicationManager(){ m_connected = FALSE; }
	~CCommunicationManager(){}	

private :
	void LoginAccepted(CString *a_message);
	void ChangeStatus(CString *a_message);

	DWORD m_operatorAddress;
	static CCommunicationManager *m_instance;
};


#endif