/**@file	MSCommunicationSD.h
 * @brief	MSM���� CCM������ Service Delegate ����.
 * @author	siva
 */

#ifndef MSCOMMUNICATION_SD_H
#define MSCOMMUNICATION_SD_H

/**@ingroup GroupMSM
 * @class	CMSCommunicationSD
 * @brief	MSM���� CCM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class CMSCommunicationSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CMSCommunicationSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CMSCommunicationSD();
		}
		return m_instance;
	}

	void SendTextMessageToRaptor(void *a_messageData);

protected :
	/**@brief	������	*/
	CMSCommunicationSD(){}
	/**@brief	�Ҹ���	*/
	~CMSCommunicationSD(){}
private :
	/**@brief	singleton.	*/
	static CMSCommunicationSD *m_instance;
};

#endif