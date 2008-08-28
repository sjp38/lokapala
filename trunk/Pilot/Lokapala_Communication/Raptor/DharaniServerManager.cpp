/**@file	DharaniServerManager.cpp
 * @brief	CDharaniServerManager �� ��� �Լ��� ����
 * @author	siva
 */

#include "stdafx.h"
#include <process.h>
#include "DharaniServerManager.h"

/**@brief	���� ����. AcceptorThread�� �����ϱ� ���� ���Ǵ� ���� ����. */
SOCKET hListenSocket;

/**@brief	Dharani ������Ʈ�� ���� ���ҷ� �ʱ�ȭ ��Ų��.
 *			competion port object�� ���⼭ ����� �������� ����, ���� ������ ���� ������ ����ϸ�,
 *			���������� ���� ��û�� �޾��ָ� ���� ������ ���ϰ� completion port�� ������ �ִ� �����带 �����Ѵ�.
 */
void CDharaniServerManager::Initiallize()
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		AfxMessageBox(CString(_T("WSAStartup() error!")));
	}

	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, CONCURRENT_THREAD_NUM);

	for(int i=0;i<CONCURRENT_THREAD_NUM;i++)
	{
		_beginthreadex(NULL,0,&CDharaniServerManager::CompletionThread,(LPVOID)m_hCompletionPort, 0, NULL);
	}

	hListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERVER_PORT);
	bind(hListenSocket, (SOCKADDR *)&servAddr, sizeof(servAddr));

	listen(hListenSocket, 15);

	_beginthreadex(NULL,0,&CDharaniServerManager::AcceptorThread,(LPVOID)m_hCompletionPort, 0, NULL);
}

/**@brief	���� ������ ������ Ŭ���̾�Ʈ�κ����� ���� ��û�� ����Ѵ�.
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
				
		socketData = (PTR_SOCKET_DATA)malloc(sizeof(SOCKET_DATA));
		socketData->descriptor = hClientSocket;
		memcpy(&(socketData->addr), &clientAddress, addrLen);
		CreateIoCompletionPort((HANDLE)hClientSocket, (HANDLE)a_hCompletionPort, (DWORD)socketData, 0);

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
unsigned int WINAPI CDharaniServerManager::CompletionThread(void *a_hCompletionPort)
{
	DWORD flags;
	DWORD bytesTransferred;
	PTR_SOCKET_DATA socketData;
	PTR_IO_DATA ioData;

	while(1)
	{
		GetQueuedCompletionStatus( (HANDLE)a_hCompletionPort, &bytesTransferred, (LPDWORD)&socketData, (LPOVERLAPPED *)&ioData, INFINITE);

		if(bytesTransferred == 0)	//EOF ����
		{
			closesocket(socketData->descriptor);
			free(socketData);
			free(ioData);
			continue;
		}

		ioData->wsaBuf.len = bytesTransferred;
		WSASend(socketData->descriptor, &(ioData->wsaBuf), 1, NULL, 0, NULL, NULL);

		memset(&(ioData->overlapped), 0, sizeof(OVERLAPPED));
		ioData->wsaBuf.len = BUFSIZE;
		ioData->wsaBuf.buf = ioData->buffer;

		flags=0;
		WSARecv(socketData->descriptor, &(ioData->wsaBuf), 1, NULL, &flags, &(ioData->overlapped), NULL);
	}

	return 0;
}