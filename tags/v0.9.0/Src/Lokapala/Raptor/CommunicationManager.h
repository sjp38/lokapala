/**@file	CommunicationManager.h
 * @brief	CCM의 행동을 실질적으로 하는 CCommunicationManager 클래스를 정의한다.
 * @author	siva
 */

#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

/**@ingroup	GroupCCM
 * @class	CCommunicationManager
 * @brief	실질적인 CCM의 모든 행위를 담당/시작한다.\n
 *			다라니 컴포넌트는 여기서만 사용한다.
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