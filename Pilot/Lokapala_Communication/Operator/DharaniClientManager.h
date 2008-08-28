/**@file	DharaniClientManager.h
 * @brief	CDharaniClientManager를 정의한다.
 * @author	siva
 */

#ifndef DHARANI_CLIENT_MANAGER_H
#define DHARANI_CLIENT_MANAGER_H

/**@ingroup GroupDharani
 * @class	CDharaniClientManager
 * @brief	Dharani 컴포넌트에서 클라이언트 역할을 담당한다.
 * @remarks	singleton을 사용한다.
 */
class CDharaniClientManager
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CDharaniClientManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDharaniClientManager();
		}
		return m_instance;
	}

	void Initiallize();

protected :
	/**@brief	생성자	*/
	CDharaniClientManager(){}
	/**@brief	소멸자	*/
	~CDharaniClientManager(){}

private :
	SOCKET m_socket;
	/**@brief	싱글톤	*/
	static CDharaniClientManager *m_instance;

};

#endif