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
	void SendMessageTo(PTR_SOCKET_DATA a_receiver, char *a_message);
	void BroadcastTextMessage(char *a_message);
	PTR_SOCKET_DATA GetSocketByAddress(DWORD a_globalIp, DWORD a_localIp);
protected :
	/**@brief	������	*/
	CDharaniServerManager(){m_socketCount = 0;}
	/**@brief	�Ҹ���	*/
	~CDharaniServerManager(){}

private :	
	static unsigned int WINAPI ReceiverThread(LPVOID a_hCompletionPort);
	static unsigned int WINAPI AcceptorThread(LPVOID a_hCompletionPort);
	void RemoveFromClientSockets(SOCKET a_socket);
	void AddToClientSockets(PTR_SOCKET_DATA a_socketData);	
	void AnalyzeReceived(char *a_receivedMessage, SOCKET a_sender);
	void Decrypt(int a_passwd, char *a_plainText, char *a_cipherText);
	void Encrypt(int a_passwd, char *a_plainText, char *a_cipherText);

	/**@brief	completion port kernel object	*/
	HANDLE	m_hCompletionPort;
	SOCKET	m_hListenSocket;
	SOCKET_DATA m_clientSockets[MAXCLIENT];	//Ŭ���̾�Ʈ ���ϵ�
	int m_socketCount;

	HANDLE m_hMutex;		//���ؽ� �ڵ�	

	/**@brief	singleton	*/
	static CDharaniServerManager *m_instance;
};

#endif