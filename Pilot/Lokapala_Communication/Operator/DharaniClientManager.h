/**@file	DharaniClientManager.h
 * @brief	CDharaniClientManager�� �����Ѵ�.
 * @author	siva
 */

#ifndef DHARANI_CLIENT_MANAGER_H
#define DHARANI_CLIENT_MANAGER_H


#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/rc4.h>

/**@ingroup GroupDharani
 * @class	CDharaniClientManager
 * @brief	Dharani ������Ʈ���� Ŭ���̾�Ʈ ������ ����Ѵ�.
 * @remarks	singleton�� ����Ѵ�.
 */
class CDharaniClientManager
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CDharaniClientManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDharaniClientManager();
		}
		return m_instance;
	}

	void Initiallize(DWORD a_ServerAddress);
	void SendTextMessage(char *a_message);

protected :
	/**@brief	������	*/
	CDharaniClientManager(){}
	/**@brief	�Ҹ���	*/
	~CDharaniClientManager(){}

private :
	static unsigned int WINAPI ReceiverThread(LPVOID a_serverSocket);
	void Encrypt(char *a_plainText, char *a_cipherText);
	void Decrypt(char *a_plainText, char *a_cipherText);

	/**@brief	completion port kernel object handle	*/
	SOCKET m_serverSocket;	//���� ���� ��ũ����
	int m_passwd;
	in_addr m_selfAddress;	

	/**@brief	�̱���	*/
	static CDharaniClientManager *m_instance;

};

#endif