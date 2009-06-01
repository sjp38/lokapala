/**@file	MSCommunicationSD.h
 * @brief	MSM에서 CCM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef MSCOMMUNICATION_SD_H
#define MSCOMMUNICATION_SD_H

/**@ingroup GroupMSM
 * @class	CMSCommunicationSD
 * @brief	MSM에서 CCM으로의 Service Delegate.
 * @remarks	singleton을 사용한다.
 */
class CMSCommunicationSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
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
	/**@brief	생성자	*/
	CMSCommunicationSD(){}
	/**@brief	소멸자	*/
	~CMSCommunicationSD(){}
private :
	/**@brief	singleton.	*/
	static CMSCommunicationSD *m_instance;
};

#endif
