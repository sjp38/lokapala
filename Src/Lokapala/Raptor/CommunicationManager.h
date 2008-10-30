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

	void Initiallize(DWORD a_ServerAddress);
	void CloseConnection();
	void SendTextMessage(CString a_message);	
	void NotifyReceived(CString a_message);

	//raptor -> operator
	void SendLoginRequest(void *a_userInfo);
	void SendExecutedProcessReport(CString *a_executedProcess);
	void SendTextMessageToOperator(CString *a_message);
	void SendStatusReport(void *a_statusReport);

protected :
	CCommunicationManager(){}
	~CCommunicationManager(){}	

private :
	void LoginAccepted(CString *a_message);

	DWORD m_operatorAddress;
	static CCommunicationManager *m_instance;
};


#endif