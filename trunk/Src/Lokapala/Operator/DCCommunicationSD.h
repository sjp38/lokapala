/**@file	DCCommunicationSD.h
 * @brief	DCM에서 CCM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef DCCOMMUNICATION_SD_H
#define DCCOMMUNICATION_SD_H

/**@ingroup GroupDCM
 * @class	CDCCommunicationSD
 * @brief	DCM에서 CCM으로의 Service Delegate.
 * @remarks	singleton을 사용한다.
 */
class CDCCommunicationSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
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
	/**@brief	생성자	*/
	CDCCommunicationSD(){}
	/**@brief	소멸자	*/
	~CDCCommunicationSD(){}
private :
	/**@brief	singleton.	*/
	static CDCCommunicationSD *m_instance;
};

#endif