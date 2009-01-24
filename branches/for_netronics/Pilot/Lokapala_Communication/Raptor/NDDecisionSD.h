/**@file	NDDecisionSD.h
 * @brief	NDM에서 DCM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef NDDECISION_SD_H
#define NDDECISION_SD_H

/**@ingroup GroupNDM
 * @class	CNDDecisionSD
 * @brief	NDM에서 DCM으로의 Service Delegate.
 * @remarks	singleton을 사용한다.
 */
class CNDDecisionSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CNDDecisionSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CNDDecisionSD();
		}
		return m_instance;
	}

protected :
	/**@brief	생성자	*/
	CNDDecisionSD(){}
	/**@brief	소멸자	*/
	~CNDDecisionSD(){}
private :
	/**@brief	singleton.	*/
	static CNDDecisionSD *m_instance;
};

#endif