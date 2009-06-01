/**@file	DCNeverDieSD.h
 * @brief	DCM에서 NDM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef DCNEVERDIE_SD_H
#define DCNEVERDIE_SD_H

/**@ingroup GroupDCM
 * @class	CDCNeverDieSD
 * @brief	DCM에서 NDM으로의 Service Delegate.
 * @remarks	singleton을 사용한다.
 */
class CDCNeverDieSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CDCNeverDieSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDCNeverDieSD();
		}
		return m_instance;
	}

	void StopNeverDie();

protected :
	/**@brief	생성자	*/
	CDCNeverDieSD(){}
	/**@brief	소멸자	*/
	~CDCNeverDieSD(){}
private :
	/**@brief	singleton.	*/
	static CDCNeverDieSD *m_instance;
};

#endif
