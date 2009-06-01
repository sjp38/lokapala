/**@file	OSDecisionSD.h
 * @brief	OSM에서 DCM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef OSDECISION_SD_H
#define OSDECISION_SD_H

/**@ingroup GroupOSM
 * @class	COSDecisionSD
 * @brief	OSM에서 DCM으로의 Service Delegate.
 * @remarks	singleton을 사용한다.
 */
class COSDecisionSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static COSDecisionSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new COSDecisionSD();
		}
		return m_instance;
	}

	void NotifyExecutedProcess(CString a_executedProcess);

protected :
	/**@brief	생성자	*/
	COSDecisionSD(){}
	/**@brief	소멸자	*/
	~COSDecisionSD(){}
private :
	/**@brief	singleton.	*/
	static COSDecisionSD *m_instance;
};

#endif
