/**@file	DharaniServerManager.cpp
 * @brief	CDharaniServerManager 의 멤버 함수를 구현
 * @author	siva
 */

#include "stdafx.h"
#include <process.h>
#include "DharaniServerManager.h"

/**@brief	리슨 소켓. AcceptorThread와 공유하기 위해 사용되는 전역 변수. */
SOCKET hListenSocket;

/**@brief	Dharani 컴포넌트를 서버 역할로 초기화 시킨다.
 *			competion port object와 여기서 사용할 쓰레드의 생성, 리슨 소켓의 생성 까지를 담당하며,
 *			지속적으로 연결 요청을 받아주며 연결 성공된 소켓과 completion port를 연결해 주는 쓰레드를 생성한다.
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

/**@brief	리슨 소켓을 가지고 클라이언트로부터의 연결 요청을 허락한다.
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


/**@brief	completion port에서 일하게 되는 쓰레드.
 *			completion port에 연결된 소켓에 입력된 데이터가 있을 때, SD를 통해 클라이언트 코드 측으로 데이터를 넘겨준다.
 *			이후, 계속해서 데이터 입력을 기다린다.
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

		if(bytesTransferred == 0)	//EOF 전송
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