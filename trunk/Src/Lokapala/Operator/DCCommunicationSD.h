/**@file	DCCommunicationSD.h
 * @brief	DCM���� CCM������ Service Delegate ����.
 * @author	siva
 */

#ifndef DCCOMMUNICATION_SD_H
#define DCCOMMUNICATION_SD_H

/**@ingroup GroupDCM
 * @class	CDCCommunicationSD
 * @brief	DCM���� CCM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class CDCCommunicationSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CDCCommunicationSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDCCommunicationSD();
		}
		return m_instance;
	}

	void NotifyAccepted(void *a_acceptedData);

	void ShutdownUser(void *a_argument);
	void RebootUser(void *a_argument);
	void LogoutUser(void *a_argument);
	void ExecuteUser(void *a_argument);
	void KillUser(void *a_argument);
	void GenocideUser(void *a_argument);
	void WarnUser(void *a_argument);

protected :
	/**@brief	������	*/
	CDCCommunicationSD(){}
	/**@brief	�Ҹ���	*/
	~CDCCommunicationSD(){}
private :
	/**@brief	singleton.	*/
	static CDCCommunicationSD *m_instance;
};

#endif