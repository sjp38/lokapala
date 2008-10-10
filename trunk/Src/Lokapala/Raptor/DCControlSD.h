/**@file	DCControlSD.h
 * @brief	DCM에서 CTM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef DCCONTROL_SD_H
#define DCCONTROL_SD_H

/**@ingroup GroupDCM
 * @class	CDCControlSD
 * @brief	DCM에서 CTM으로의 Service Delegate.
 * @remarks	singleton을 사용한다.
 */
class CDCControlSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
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

protected :
	/**@brief	생성자	*/
	CDCControlSD(){}
	/**@brief	소멸자	*/
	~CDCControlSD(){}
private :
	/**@brief	singleton.	*/
	static CDCControlSD *m_instance;
};

#endif