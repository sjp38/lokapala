/**@file	DCLogSD.h
 * @brief	DCM에서 LGM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef DCLOG_SD_H
#define DCLOG_SD_H

/**@ingroup GroupDCM
 * @class	CDCLogSD
 * @brief	DCM에서 LGM으로의 Service Delegate.
 * @remarks	singleton을 사용한다.
 */
class CDCLogSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CDCLogSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDCLogSD();
		}
		return m_instance;
	}

protected :
	/**@brief	생성자	*/
	CDCLogSD(){}
	/**@brief	소멸자	*/
	~CDCLogSD(){}
private :
	/**@brief	singleton.	*/
	static CDCLogSD *m_instance;
};

#endif
