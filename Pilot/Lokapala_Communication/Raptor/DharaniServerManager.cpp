/**@file	DharaniServerManager.cpp
 * @brief	CDharaniServerManager �� ��� �Լ��� ����
 * @author	siva
 */

#include "stdafx.h"
#include <process.h>
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
	bind(hListenSocket, (SOCKADDR *)&servAddr, sizeof(servAddr));
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

		//Ŭ���̾�Ʈ�� ���� ip ����(private ip�� �� �ִ�)�� �ް� ������ �˸���.
		in_addr clientLocalIp;
		recv(hClientSocket, (char *)((void *)&clientLocalIp), sizeof(in_addr), 0);		
		CDharaniExternSD::Instance()->NotifyAccepted(&clientAddress.sin_addr, (in_addr *)&clientLocalIp);
		
		//���� ������ ����
		socketData = (PTR_SOCKET_DATA)malloc(sizeof(SOCKET_DATA));
		socketData->descriptor = hClientSocket;
		memcpy(&(socketData->addr), &clientAddress, addrLen);
		socketData->localIp = (in_addr)clientLocalIp;
		
		//completion port�� ������ ����.
		CreateIoCompletionPort((HANDLE)hClientSocket, (HANDLE)a_hCompletionPort, (DWORD)socketData, 0);
		
		//Ŭ���̾�Ʈ ���� ��Ͽ� ���� ������ �߰�(ũ��Ƽ�� ����).
		CDharaniServerManager::Instance()->AddToClientSockets(socketData);

		//�Ź� �ش� ���� ���� ioData�� ���� �Ҵ��Ѵ�.
		ioData = (PTR_IO_DATA)malloc(sizeof(IO_DATA));
		memset(&(ioData->overlapped), 0, sizeof(OVERLAPPED));
		ioData->wsaBuf.len = BUFSIZE;
		ioData->wsaBuf.buf = ioData->buffer;
		DWORD Flags=0;
		DWORD RecvBytes;

		WSARecv(socketData->descriptor, &(ioData->wsaBuf), 1, &RecvBytes, &Flags, &(ioData->overlapped), NULL);
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

	while(1)
	{
		GetQueuedCompletionStatus( (HANDLE)a_hCompletionPort, &bytesTransferred, (LPDWORD)&socketData, (LPOVERLAPPED *)&ioData, INFINITE);

		if(bytesTransferred == 0)	//EOF ����(���� ������)
		{
			CDharaniServerManager::Instance()->RemoveFromClientSockets(socketData->descriptor);
			CDharaniExternSD::Instance()->NotifyLeft();
			closesocket(socketData->descriptor);
			free(socketData);
			free(ioData);
			continue;
		}

		ioData->buffer[bytesTransferred] = '\0';
		CDharaniExternSD::Instance()->NotifyReceived(ioData->buffer);

		memset(&(ioData->overlapped), 0, sizeof(OVERLAPPED));
		ioData->wsaBuf.len = BUFSIZE;
		ioData->wsaBuf.buf = ioData->buffer;

		flags=0;
		WSARecv(socketData->descriptor, &(ioData->wsaBuf), 1, NULL, &flags, &(ioData->overlapped), NULL);
	}

	return 0;
}

/**@brief	Ŭ���̾�Ʈ�鿡�� �޼����� �ѷ��ش�.
 */
void CDharaniServerManager::BroadcastTextMessage(char *a_message)
{
	WSABUF wsaBuf;
	wsaBuf.buf = a_message;
	wsaBuf.len = strlen(a_message)*sizeof(char);

	for(int i=0 ;i<this->m_socketCount ; i++)
	{
		WSASend((m_clientSockets[i]).descriptor, &wsaBuf, 1, NULL, 0, NULL, NULL);
	}
}

/**@brief	Ŭ���̾�Ʈ ���� ��Ͽ� ���� ������ �߰��Ѵ�.
 */
void CDharaniServerManager::AddToClientSockets(PTR_SOCKET_DATA a_socketData)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	m_clientSockets[m_socketCount++] = *a_socketData;
	ReleaseMutex(m_hMutex);
}

/**@brief	Ŭ���̾�Ʈ ���� ��Ͽ��� Ư�� ������ �����Ѵ�.
 */
void CDharaniServerManager::RemoveFromClientSockets(SOCKET a_socket)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	for(int i=0; i<m_socketCount; i++)
	{
		if(m_clientSockets[i].descriptor == a_socket)
		{
			m_clientSockets[m_socketCount--] = m_clientSockets[i];
			for(int j=i; j<m_socketCount; j++)
			{
				m_clientSockets[j] = m_clientSockets[j+1];
			}
		}
	}
	ReleaseMutex(m_hMutex);
}