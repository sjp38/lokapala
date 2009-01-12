/**@file	CCDecisionSD.h
 * @brief	CCM���� DCM������ Service Delegate ����.
 * @author	siva
 */

#ifndef CCDECISION_SD_H
#define CCDECISION_SD_H

/**@ingroup GroupCCM
 * @class	CCCDecisionSD
 * @brief	CCM���� DCM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class CCCDecisionSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
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
	/**@brief	������	*/
	CCCDecisionSD(){}
	/**@brief	�Ҹ���	*/
	~CCCDecisionSD(){}
private :
	/**@brief	singleton.	*/
	static CCCDecisionSD *m_instance;
};

#endif