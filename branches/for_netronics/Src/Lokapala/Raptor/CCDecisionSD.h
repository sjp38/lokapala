/**@file	CCDecisionSD.h
 * @brief	CCM에서 DCM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef CCDECISION_SD_H
#define CCDECISION_SD_H

/**@ingroup GroupCCM
 * @class	CCCDecisionSD
 * @brief	CCM에서 DCM으로의 Service Delegate.
 * @remarks	singleton을 사용한다.
 */
class CCCDecisionSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CCCDecisionSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CCCDecisionSD();
		}
		return m_instance;
	}

	void LoginAccepted(int a_level);

	void Login(void *a_message);
	void Logout(void *a_message);
	void Shutdown(void *a_message);
	void Reboot(void *a_message);
	void GenocideProcesses(void *a_processName);
	void KillProcess(void *a_processName);
	void ExecuteProcess(void *a_processName);
	void StatusReportReceived(void *a_statusReport);
	void TerminateRaptor();

protected :
	/**@brief	생성자	*/
	CCCDecisionSD(){}
	/**@brief	소멸자	*/
	~CCCDecisionSD(){}
private :
	/**@brief	singleton.	*/
	static CCCDecisionSD *m_instance;
};

#endif