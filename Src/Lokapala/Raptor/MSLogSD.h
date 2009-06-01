/**@file	MSLogSD.h
 * @brief	MSM에서 LGM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef MSLOG_SD_H
#define MSLOG_SD_H

/**@ingroup GroupMSM
 * @class	CMSLogSD
 * @brief	MSM에서 LGM으로의 Service Delegate.
 * @remarks	singleton을 사용한다.
 */
class CMSLogSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CMSLogSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CMSLogSD();
		}
		return m_instance;
	}

protected :
	/**@brief	생성자	*/
	CMSLogSD(){}
	/**@brief	소멸자	*/
	~CMSLogSD(){}
private :
	/**@brief	singleton.	*/
	static CMSLogSD *m_instance;
};

#endif
