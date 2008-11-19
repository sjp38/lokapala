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

	void SendShutdownInstruction(void *a_argument);
	void SendRebootInstruction(void *a_argument);
	void SendBanUserInstruction(void *a_argument);
	void SendExecuteProcessInstruction(void *a_argument);
	void SendKillProcessInstruction(void *a_argument);
	void SendGenocideProcessInstruction(void *a_argument);
	void SendWarningMessage(void *a_argument);
	void SendStatusReport(void *a_statusReport);

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