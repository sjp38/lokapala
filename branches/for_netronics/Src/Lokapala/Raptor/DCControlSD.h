/**@file	DCControlSD.h
 * @brief	DCM���� CTM������ Service Delegate ����.
 * @author	siva
 */

#ifndef DCCONTROL_SD_H
#define DCCONTROL_SD_H

/**@ingroup GroupDCM
 * @class	CDCControlSD
 * @brief	DCM���� CTM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class CDCControlSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CDCControlSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDCControlSD();
		}
		return m_instance;
	}

	void ReleaseUser();

	void Login(void *a_userInfo);
	void Logout(void *a_message);	
	void Shutdown(void *a_message);
	void Reboot(void *a_message);
	void GenocideProcesses(void *a_message);
	void KillProcess(void *a_processName);
	void ExecuteProcess(void *a_processName);

protected :
	/**@brief	������	*/
	CDCControlSD(){}
	/**@brief	�Ҹ���	*/
	~CDCControlSD(){}
private :
	/**@brief	singleton.	*/
	static CDCControlSD *m_instance;
};

#endif