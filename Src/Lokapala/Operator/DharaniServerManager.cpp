/**@file	DharaniServerManager.cpp
 * @brief	CDharaniServerManager �� ��� �Լ��� ����
 * @author	siva
 */

#include "stdafx.h"
#include <process.h>

//openssl ��� include
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/rc4.h>

#include "DharaniExternSD.h"
#include "DharaniServerManager.h"

/**@brief	���� ����. AcceptorThread�� �����ϱ� ���� ���Ǵ� ���� ����. */
SOCKET hListenSocket;


/**@brief	Dharani ������Ʈ�� ���� ���ҷ� �ʱ�ȭ ��Ų��.
 *			competion port object�� ���⼭ ����� �������� ����, ���� ������ ���� ������ ����ϸ�,
 *			���������� ���� ��û�� �޾��ָ� ���� ������ ���ϰ� completion port�� ������ �ִ� �����带 �����Ѵ�.
 */
void CDharaniServerManager::Initiallize()
{
	m_hMutex = CreateMutex(NULL, FALSE, NULL);

	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		AfxMessageBox(CString(_T("WSAStartup() error!")));
	}

	//completion port kernel object handle ����, ������ ������ ����
	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, CONCURRENT_THREAD_NUM);

	for(int i=0;i<CONCURRENT_THREAD_NUM;i++)
	{
		_beginthreadex(NULL,0,&CDharaniServerManager::ReceiverThread,(LPVOID)m_hCompletionPort, 0, NULL);
	}

	//���� ���� ����
	hListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	//���ε�,����
	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERVER_PORT);
	if(-1 == bind(hListenSocket, (SOCKADDR *)&servAddr, sizeof(servAddr)) )
	{
		AfxMessageBox(_T("bind() Failed!"));
	}
	listen(hListenSocket, 15);

	//accept ������ ����/completion port�� ���� ������ ������� �и���Ų��.
	_beginthreadex(NULL,0,&CDharaniServerManager::AcceptorThread,(LPVOID)m_hCompletionPort, 0, NULL);
}

/**@brief	���� ������ ������ Ŭ���̾�Ʈ�κ����� ���� ��û�� ����ϰ� ����� ������ completion port�� �����Ѵ�.
 */
unsigned int WINAPI CDharaniServerManager::AcceptorThread(LPVOID a_hCompletionPort)
{
	PTR_SOCKET_DATA socketData;
	PTR_IO_DATA ioData;

	while(1)
	{
		SOCKET hClientSocket;
		SOCKADDR_IN clientAddress;
		int addrLen = sizeof(clientAddress);

		hClientSocket = accept(hListenSocket, (SOCKADDR *)&clientAddress, &addrLen);

		//Ŭ���̾�Ʈ�� ���� ip ����(private ip�� �� �ִ�)�� �޴´�.
		in_addr clientLocalIp;
		recv(hClientSocket, (char *)((void *)&clientLocalIp), sizeof(in_addr), 0);		

		//��ȣȭ Ű ����
		int passwd = rand();
		//��ȣȭ Ű ����
		WSABUF wsaBuf;
		wsaBuf.buf = (char *)&passwd;
		wsaBuf.len = sizeof(int);
		WSASend(hClientSocket, &wsaBuf, 1, NULL, 0, NULL, NULL);
		
		//���� ������ ����
		socketData = (PTR_SOCKET_DATA)malloc(sizeof(SOCKET_DATA));
		socketData->descriptor = hClientSocket;
		memcpy(&(socketData->addr), &clientAddress, addrLen);
		socketData->localIp = (in_addr)clientLocalIp;
		socketData->passwd = passwd;
		
		//completion port�� ������ ����.
		CreateIoCompletionPort((HANDLE)hClientSocket, (HANDLE)a_hCompletionPort, (DWORD)socketData, 0);
		
		//Ŭ���̾�Ʈ ���� ��Ͽ� ���� ������ �߰�(ũ��Ƽ�� ����).
		CDharaniServerManager::Instance()->AddToClientSockets(socketData);

		//�ش� ���� ���� ioData�� ���� �Ҵ��Ѵ�.
		ioData = (PTR_IO_DATA)malloc(sizeof(IO_DATA));
		memset(&(ioData->overlapped), 0, sizeof(OVERLAPPED));
		ioData->wsaBuf.len = sizeof(int);
		ioData->wsaBuf.buf = ioData->buffer;
		ioData->formerReceivedBytes = 0;
		DWORD Flags=0;
		DWORD RecvBytes;

		WSARecv(socketData->descriptor, &(ioData->wsaBuf), 1, &RecvBytes, &Flags, &(ioData->overlapped), NULL);

		CDharaniExternSD::Instance()->NotifyAccepted(&clientAddress.sin_addr, (in_addr *)&clientLocalIp);
	}
}


/**@brief	completion port���� ���ϰ� �Ǵ� ������.
 *			completion port�� ����� ���Ͽ� �Էµ� �����Ͱ� ���� ��, SD�� ���� Ŭ���̾�Ʈ �ڵ� ������ �����͸� �Ѱ��ش�.
 *			����, ����ؼ� ������ �Է��� ��ٸ���.
 */
unsigned int WINAPI CDharaniServerManager::ReceiverThread(void *a_hCompletionPort)
{
	DWORD flags;
	DWORD bytesTransferred;
	PTR_SOCKET_DATA socketData;
	PTR_IO_DATA ioData;
	int size=0;

	while(1)
	{
		GetQueuedCompletionStatus( (HANDLE)a_hCompletionPort, &bytesTransferred, (LPDWORD)&socketData, (LPOVERLAPPED *)&ioData, INFINITE);

		if(bytesTransferred == 0)	//EOF ����(���� ������)
		{
			CDharaniServerManager::Instance()->RemoveFromClientSockets(socketData->descriptor);
			
			closesocket(socketData->descriptor);
			free(socketData);
			free(ioData);
			continue;
		}

		memcpy(&size, ioData->buffer, sizeof(size));
		if( sizeof(size) > bytesTransferred + ioData->formerReceivedBytes )
		{
			size = 0;
		}		

		//���Ӽ� ó�� : �����Ͱ� ���� �� ������ �ʾ��� ��
		if( size > bytesTransferred + ioData->formerReceivedBytes  ||  size == 0 )
		{
			/*USES_CONVERSION;
			AfxMessageBox(A2W(ioData->buffer));*/
			ioData->formerReceivedBytes += bytesTransferred;
			memset(&(ioData->overlapped), 0, sizeof(OVERLAPPED));
			ioData->wsaBuf.len = size+sizeof(size) - ioData->formerReceivedBytes;
			ioData->wsaBuf.buf = ioData->buffer + ioData->formerReceivedBytes;

			flags=0;
			WSARecv(socketData->descriptor, &(ioData->wsaBuf), 1, NULL, &flags, &(ioData->overlapped), NULL);
			continue;
		}
		if(size < bytesTransferred)
		{
			AfxMessageBox(_T("flow"));
		}

		//�����Ͱ� ��� ������ ��
		//CDharaniExternSD::Instance()->NotifyReceived(ioData->buffer, socketData->localIp, socketData->addr.sin_addr);	//��ȣȭ ����. �׽�Ʈ

		char decrypted[BUFSIZE];
		CDharaniServerManager::Instance()->Decrypt(socketData->passwd, size, decrypted, ioData->buffer+sizeof(size));
		CDharaniExternSD::Instance()->NotifyReceived(decrypted, socketData->localIp, socketData->addr.sin_addr);

		memset(&(ioData->overlapped), 0, sizeof(OVERLAPPED));
		ioData->wsaBuf.len = sizeof(size);
		ioData->wsaBuf.buf = ioData->buffer;
		ioData->formerReceivedBytes=0;

		flags=0;
		WSARecv(socketData->descriptor, &(ioData->wsaBuf), 1, NULL, &flags, &(ioData->overlapped), NULL);		
	}
	return 0;
}


/**@brief	�Է¹��� �޼����� dharani �������ݿ� �°� �ؼ��Ѵ�.\n
			���� ���������� ������ ������, ���� ���� ���� ��� �߰� ��, ��� ������ ����/�޼����� �����Ѵ�.\n
			�޼��� ���� ó�� ���� �������� �д��� ���� �ִ�.
 * @param	a_receivedMessage	���� �޼���.
 * @param	a_sender			�޼����� ���� ���������� ����.
 */
void CDharaniServerManager::AnalyzeReceived(char *a_receivedMessage, SOCKET a_sender)
{
	//char ackMessage;
	switch(a_receivedMessage[0])
	{
	case HELLO :
		//ackMessage = ACK_HELLO;
		//SendMessageTo(a_sender, &ackMessage);
		break;
	case ACK_HELLO :
		break;
	case KEY :
		break;
	case ACK_KEY :
		break;
	case DATA :
		break;
	case ACK_DATA :
		break;
	}
}

/**@brief	Ư�� ���Ͽ��� �޼����� ������.
 * @param	a_receiver	���������� ����
 * @param	a_message	���� �޼���
 */
void CDharaniServerManager::SendMessageTo(PTR_SOCKET_DATA a_receiver, char *a_message)
{	
	int size = strlen(a_message)+1;	

	char encrypted[BUFSIZE];	
	this->Encrypt(a_receiver->passwd, a_message, encrypted+sizeof(size));
	memcpy(encrypted, &size, sizeof(size));

	WSABUF wsaBuf;
	wsaBuf.buf = encrypted;
	wsaBuf.len = sizeof(size)+size;
	WSASend(a_receiver->descriptor, &wsaBuf, 1, NULL, 0, NULL, NULL);
}

/**@brief	Ŭ���̾�Ʈ�鿡�� �޼����� �ѷ��ش�.
 *			���������� SendMessageTo �޼ҵ带 ����Ѵ�.
 * @param	a_message	����ϰ��� �ϴ� �޼���
 */
void CDharaniServerManager::BroadcastTextMessage(char *a_message)
{
	for(int i=0 ;i<this->m_socketCount ; i++)
	{
		SendMessageTo(&m_clientSockets[i], a_message);
	}
}

/**@brief	Ŭ���̾�Ʈ ���� ��Ͽ��� Ư�� ������ ������ ���´�.
 */
SOCKET_DATA CDharaniServerManager::GetSocketDataFromClientSockets(SOCKET a_socket)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	for(int i=0; i<m_socketCount; i++)
	{
		if(m_clientSockets[i].descriptor == a_socket)
		{
			SOCKET_DATA socketData = m_clientSockets[i];			
			ReleaseMutex(m_hMutex);
			return socketData;
		}
	}
	ReleaseMutex(m_hMutex);
	SOCKET_DATA socketData;
	socketData.descriptor = -1;
	return socketData;
}

/**@brief	Ŭ���̾�Ʈ ���� ��Ͽ� ���� ������ �߰��Ѵ�.
 */
void CDharaniServerManager::AddToClientSockets(PTR_SOCKET_DATA a_socketData)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	m_clientSockets[m_socketCount++] = *a_socketData;
	ReleaseMutex(m_hMutex);
}

/**@brief	Ŭ���̾�Ʈ ���� ��Ͽ��� Ư�� ������ �����ϰ�, ���� ������ �˸���.
 */
void CDharaniServerManager::RemoveFromClientSockets(SOCKET a_socket)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	for(int i=0; i<m_socketCount; i++)
	{
		if(m_clientSockets[i].descriptor == a_socket)
		{			
			CDharaniExternSD::Instance()->NotifyLeft(&m_clientSockets[i].addr.sin_addr, &m_clientSockets[i].localIp);
			m_clientSockets[m_socketCount--] = m_clientSockets[i];
			for(int j=i; j<m_socketCount; j++)
			{
				m_clientSockets[j] = m_clientSockets[j+1];
			}
		}
	}
	ReleaseMutex(m_hMutex);
}


/**@brief	�۷ι�, ���� �����Ǹ� ������ ���� ����� Ŭ���̾�Ʈ ��Ͽ��� �ش� Ŭ���̾�Ʈ�� ������ ã�� ���� �����͸� ��ȯ�Ѵ�.
 * @param	a_globalIp	ã���� �ϴ� Ŭ���̾�Ʈ�� �۷ι� ������
 * @param	a_localIp	ã���� �ϴ� Ŭ���̾�Ʈ�� ���� ������
 * @return	�ش� Ŭ���̾�Ʈ�� ���� ������(SOCKET_DATA) ������. ã�� ������ ��� 0
 */
PTR_SOCKET_DATA CDharaniServerManager::GetSocketByAddress(DWORD a_globalIp, DWORD a_localIp)
{
	for(int i=0; i<m_socketCount; i++)
	{
		if(m_clientSockets[i].addr.sin_addr.s_addr == a_globalIp && m_clientSockets[i].localIp.s_addr == a_localIp)
		{
			return &m_clientSockets[i];
		}
	}
	return 0;
}


/**@brief	Ư�� ���ڿ��� ��ȣȭ �Ѵ�.
 * @param	a_passwd	RC4 �˰��� Ű
 * @param	a_length	��ȣ/��ȣȭ �� ���ڿ��� ����
 * @param	a_plainText	��ȣȭ �� ���� ���ڿ��� ������
 * @param	a_cipherText	��ȣȭ ��, ��ȣȭ �� ���ڿ�
 */
void CDharaniServerManager::Decrypt(int a_passwd, size_t a_length, char *a_plainText, char *a_cipherText)
{
	RC4_KEY rc4Key;
	RC4_set_key(&rc4Key,strlen((char *)&a_passwd),(unsigned char *)&a_passwd);
	RC4(&rc4Key, a_length, (unsigned char *)a_cipherText, (unsigned char *)a_plainText);
}

/**@brief	Ư�� ���ڿ��� ��ȣȭ �Ѵ�.
 * @param	a_key	RC4 �˰��� Ű
 * @param	a_plainText	��ȣȭ �� �������� ���ڿ�
 * @param	a_cipherText	��ȣȭ �� ���� ���ڿ��� ������
 */
void CDharaniServerManager::Encrypt(int a_passwd, char *a_plainText, char *a_cipherText)
{
	RC4_KEY rc4Key;
	RC4_set_key(&rc4Key,strlen((char *)&a_passwd),(unsigned char *)&a_passwd);
	RC4(&rc4Key, strlen(a_plainText)+1, (unsigned char *)a_plainText, (unsigned char *)a_cipherText);
}