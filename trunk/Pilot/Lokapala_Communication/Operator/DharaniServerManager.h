/**@file	DharaniServerManager
 * @brief	CDharaniServerManager를 정의한다.
 * @author	siva
 */

#ifndef DHARANI_SERVER_MANAGER_H
#define DHARANI_SERVER_MANAGER_H

#include "Dharani.h"

/**@ingroup	GroupDharani
 * @class	CDharaniServerManager
 * @brief	Dharani 컴포넌트에서 서버 역할을 담당한다.
 * @remarks	singleton을 사용한다.
 */
class CDharaniServerManager
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CDharaniServerManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDharaniServerManager();
		}
		return m_instance;
	}
	void Initiallize();
protected :
	/**@brief	생성자	*/
	CDharaniServerManager(){}
	/**@brief	소멸자	*/
	~CDharaniServerManager(){}
private :
	/**@brief	completion port kernel object	*/
	HANDLE	m_hCompletionPort;
	SOCKET	m_hListenSocket;
	SOCKET_DATA m_clientSockets[MAXCLIENT];	//클라이언트 소켓들
	
	static unsigned int WINAPI CompletionThread(LPVOID a_hCompletionPort);
	static unsigned int WINAPI AcceptorThread(LPVOID a_hCompletionPort);

	/**@brief	singleton	*/
	static CDharaniServerManager *m_instance;
};

#endif