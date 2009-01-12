/**@file	CCMessengerSD.h
 * @brief	CCM에서 MSM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef CCMESSENGER_SD_H
#define CCMESSENGER_SD_H

/**@ingroup GroupCCM
 * @class	CCCMessengerSD
 * @brief	CCM에서 MSM으로의 Service Delegate.
 * @remarks	singleton을 사용한다.
 */
class CCCMessengerSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CCCMessengerSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CCCMessengerSD();
		}
		return m_instance;
	}

	void TexeMessageReceived(CString a_message);

protected :
	/**@brief	생성자	*/
	CCCMessengerSD(){}
	/**@brief	소멸자	*/
	~CCCMessengerSD(){}
private :
	/**@brief	singleton.	*/
	static CCCMessengerSD *m_instance;
};

#endif