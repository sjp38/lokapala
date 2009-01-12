/**@file	DharaniClientManager.cpp
 * @brief	CDharaniClientManager�� ��� �Լ��� ����
 * @author	siva
 */

#include "stdafx.h"
#include <process.h>
#include "Dharani.h"
#include "DharaniExternSD.h"
#include "DharaniClientManager.h"


/**@brief	Ŭ���̾�Ʈ�� ���·� ���� ��Ȳ ���� �ʱ�ȭ�ϰ� �������� �ʱ� ����(��ȣȭ Ű ��ȯ ��)�� �Ѵ�.
 * @return	���������� �ʱ�ȭ�� ������ ��� 0, ������ ���� ��� -1
 */
int CDharaniClientManager::Initiallize(DWORD a_ServerAddress)
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		AfxMessageBox(_T("WSAStartup() error!"));
		return -1;
	}

	m_serverSocket = WSASocket(PF_INET, SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);

	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(a_ServerAddress);
	serverAddr.sin_port = htons(SERVER_PORT);
	
	if(connect(m_serverSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("connect() error!"));
		closesocket(m_serverSocket);
		WSACleanup();
		return -1;
	}
	
	hostent *hostAddress = gethostbyname("");
	memcpy(&m_selfAddress, hostAddress->h_addr_list[0], sizeof(m_selfAddress));
	CDharaniExternSD::Instance()->NotifyReceived(inet_ntoa(m_selfAddress));	

	send(m_serverSocket, (char *)((void *)&m_selfAddress), sizeof(m_selfAddress), 0);
	int totalReceived = 0;
	while(1)
	{
		int received = recv(m_serverSocket, (char *)(&m_passwd+totalReceived), sizeof(m_passwd), 0);
		totalReceived += received;
		if(totalReceived==sizeof(m_passwd))
		{
			char keyNotify[BUFSIZE];
			_itoa_s(m_passwd, keyNotify, 16);
			CDharaniExternSD::Instance()->NotifyReceived("received cryption key is :");
			CDharaniExternSD::Instance()->NotifyReceived(keyNotify);

			break;
		}
	}

	_beginthreadex(NULL,0,&CDharaniClientManager::ReceiverThread,(LPVOID)m_serverSocket, 0, NULL);
	CDharaniExternSD::Instance()->NotifyConnected();
	return 0;
}

/**@brief	Ư�� �������κ��� Ư�� ũ���� �����͸� �Ϻ��ϰ� �޾Ƴ���. tcp Ư���� ������ ���� ������ �ذ��Ѵ�.
 * @param	a_srcSocket	�����͸� �޾� �� ����
 * @param	a_size		�޾� �� �������� ũ��
 * @param	a_target	�޾� �� �����͸� �־� �� ������.
 */
int CDharaniClientManager::Receive(SOCKET a_srcSocket, void *a_target, unsigned int a_size)
{
	int totalReceived = 0;
	while(1)
	{
		int receivedBytes = recv(a_srcSocket, (char *)a_target+totalReceived, a_size - totalReceived, 0);
		if(receivedBytes == SOCKET_ERROR)
		{
			//AfxMessageBox(_T("receive failed!"));
			closesocket(a_srcSocket);
			WSACleanup();
			return 1;
		}			
		if(receivedBytes == 0)
		{
			//AfxMessageBox(_T("server connect failed!"));
			closesocket(a_srcSocket);
			WSACleanup();
			return 1;
		}

		totalReceived += receivedBytes;

		if(totalReceived == a_size)
		{
			break;
		}
	}
	return 0;
}

/**@brief	������� ���� �������� ������ ���� �޴´�.
 */
unsigned int WINAPI CDharaniClientManager::ReceiverThread(LPVOID a_serverSocket)
{
	SOCKET serverSocket = (SOCKET)a_serverSocket;
	char buffer[BUFSIZE];
	char decrypted[BUFSIZE];
	
	while(1)
	{
		int size;
		int result;
		result = Receive(serverSocket, &size, sizeof(size));
		if( result != 0 )
		{
			CDharaniExternSD::Instance()->NotifyDisconnected();
			break;
		}
		result = Receive(serverSocket, buffer, size);
		CDharaniClientManager::Instance()->Decrypt(decrypted, buffer, size);
		CDharaniExternSD::Instance()->NotifyReceived(decrypted);		
	}
	return 0;
}

/**@brief	�������� ������ ���´�.
 */
void CDharaniClientManager::CloseConnection()
{
	closesocket(m_serverSocket);
	WSACleanup();
}

/**@brief	�޼����� �������� ������.
 * @param	a_message	���� �޼���
 */
void CDharaniClientManager::SendTextMessage(char *a_message)
{
	int size = strlen(a_message)+1;	

	char encrypted[BUFSIZE];
	this->Encrypt(a_message, encrypted+sizeof(size));
	memcpy(encrypted, &size, sizeof(size));
	
	send(m_serverSocket, encrypted, sizeof(size)+size, 0);
}


/**@brief	Ư�� ���ڿ��� ��ȣȭ �Ѵ�. RC4 �˰����� ����Ѵ�.
 * @param	a_plainText	��ȣȭ ��, �������� ���ڿ�
 * @param	a_cipherText	��ȣȭ �� ���� ���ڿ�
 */
void CDharaniClientManager::Encrypt(char *a_plainText, char *a_cipherText)
{
	RC4_KEY rc4Key;
	RC4_set_key(&rc4Key, strlen((char *)&m_passwd),(unsigned char *)&m_passwd);
	RC4(&rc4Key, strlen(a_plainText)+1, (unsigned char *)a_plainText, (unsigned char *)a_cipherText);
}

/**@brief	Ư�� ���ڿ��� ��ȣȭ �Ѵ�. RC4 �˰����� ����Ѵ�.
 * @param	a_plainText	��ȣȭ �� ���� ���ڿ�
 * @param	a_cipherText	��ȣȭ �� �������� ��ȣ���ڿ�
 */
void CDharaniClientManager::Decrypt(char *a_plainText, char *a_cipherText, unsigned int a_size)
{
	RC4_KEY rc4Key;
	RC4_set_key(&rc4Key, strlen((char *)&m_passwd),(unsigned char *)&m_passwd);
	RC4(&rc4Key, a_size, (unsigned char *)a_cipherText, (unsigned char *)a_plainText);
}