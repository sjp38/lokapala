/**@file	DharaniServerManager
 * @brief	CDharaniServerManager�� �����Ѵ�.
 * @author	siva
 */

#ifndef DHARANI_SERVER_MANAGER_H
#define DHARANI_SERVER_MANAGER_H

#include "Dharani.h"

/**@ingroup	GroupDharani
 * @class	CDharaniServerManager
 * @brief	Dharani ������Ʈ���� ���� ������ ����Ѵ�.
 * @remarks	singleton�� ����Ѵ�.
 */
class CDharaniServerManager
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
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
	/**@brief	������	*/
	CDharaniServerManager(){}
	/**@brief	�Ҹ���	*/
	~CDharaniServerManager(){}
private :
	/**@brief	completion port kernel object	*/
	HANDLE	m_hCompletionPort;
	SOCKET	m_hListenSocket;
	SOCKET_DATA m_clientSockets[MAXCLIENT];	//Ŭ���̾�Ʈ ���ϵ�
	
	static unsigned int WINAPI CompletionThread(LPVOID a_hCompletionPort);
	static unsigned int WINAPI AcceptorThread(LPVOID a_hCompletionPort);

	/**@brief	singleton	*/
	static CDharaniServerManager *m_instance;
};

#endif