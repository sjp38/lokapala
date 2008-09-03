/**@file	DharaniClientManager.h
 * @brief	CDharaniClientManager�� �����Ѵ�.
 * @author	siva
 */

#ifndef DHARANI_CLIENT_MANAGER_H
#define DHARANI_CLIENT_MANAGER_H

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
	/**@brief	completion port kernel object handle	*/
	SOCKET m_serverSocket;	//���� ���� ��ũ����
	in_addr m_selfAddress;
	static unsigned int WINAPI ReceiverThread(LPVOID a_serverSocket);

	/**@brief	�̱���	*/
	static CDharaniClientManager *m_instance;

};

#endif