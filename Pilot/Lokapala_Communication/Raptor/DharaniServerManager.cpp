/**@file	DharaniServerManager.cpp
 * @brief	CDharaniServerManager 의 멤버 함수를 구현
 * @author	siva
 */

#include "stdafx.h"
#include <process.h>
#include "DharaniExternSD.h"
#include "DharaniServerManager.h"

/**@brief	리슨 소켓. AcceptorThread와 공유하기 위해 사용되는 전역 변수. */
SOCKET hListenSocket;

/**@brief	Dharani 컴포넌트를 서버 역할로 초기화 시킨다.
 *			competion port object와 여기서 사용할 쓰레드의 생성, 리슨 소켓의 생성 까지를 담당하며,
 *			지속적으로 연결 요청을 받아주며 연결 성공된 소켓과 completion port를 연결해 주는 쓰레드를 생성한다.
 */
void CDharaniServerManager::Initiallize()
{
	m_hMutex = CreateMutex(NULL, FALSE, NULL);

	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		AfxMessageBox(CString(_T("WSAStartup() error!")));
	}

	//completion port kernel object handle 생성, 연결할 쓰레드 생성
	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, CONCURRENT_THREAD_NUM);

	for(int i=0;i<CONCURRENT_THREAD_NUM;i++)
	{
		_beginthreadex(NULL,0,&CDharaniServerManager::ReceiverThread,(LPVOID)m_hCompletionPort, 0, NULL);
	}

	//리슨 소켓 생성
	hListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	//바인드,리슨
	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERVER_PORT);
	bind(hListenSocket, (SOCKADDR *)&servAddr, sizeof(servAddr));
	listen(hListenSocket, 15);

	//accept 과정과 소켓/completion port의 연결 과정은 쓰레드로 분립시킨다.
	_beginthreadex(NULL,0,&CDharaniServerManager::AcceptorThread,(LPVOID)m_hCompletionPort, 0, NULL);
}

/**@brief	리슨 소켓을 가지고 클라이언트로부터의 연결 요청을 허락하고 연결된 소켓을 completion port에 연결한다.
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

		//클라이언트의 로컬 ip 정보(private ip일 수 있다)를 받고 연결을 알린다.
		in_addr clientLocalIp;
		recv(hClientSocket, (char *)((void *)&clientLocalIp), sizeof(in_addr), 0);		
		CDharaniExternSD::Instance()->NotifyAccepted(&clientAddress.sin_addr, (in_addr *)&clientLocalIp);
		
		//소켓 데이터 세팅
		socketData = (PTR_SOCKET_DATA)malloc(sizeof(SOCKET_DATA));
		socketData->descriptor = hClientSocket;
		memcpy(&(socketData->addr), &clientAddress, addrLen);
		socketData->localIp = (in_addr)clientLocalIp;
		
		//completion port에 소켓을 연결.
		CreateIoCompletionPort((HANDLE)hClientSocket, (HANDLE)a_hCompletionPort, (DWORD)socketData, 0);
		
		//클라이언트 소켓 목록에 소켓 정보를 추가(크리티컬 섹션).
		CDharaniServerManager::Instance()->AddToClientSockets(socketData);

		//매번 해당 소켓 전용 ioData를 동적 할당한다.
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
unsigned int WINAPI CDharaniServerManager::ReceiverThread(void *a_hCompletionPort)
{
	DWORD flags;
	DWORD bytesTransferred;
	PTR_SOCKET_DATA socketData;
	PTR_IO_DATA ioData;

	while(1)
	{
		GetQueuedCompletionStatus( (HANDLE)a_hCompletionPort, &bytesTransferred, (LPDWORD)&socketData, (LPOVERLAPPED *)&ioData, INFINITE);

		if(bytesTransferred == 0)	//EOF 전송(연결 끊어짐)
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

/**@brief	클라이언트들에게 메세지를 뿌려준다.
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

/**@brief	클라이언트 소켓 목록에 소켓 정보를 추가한다.
 */
void CDharaniServerManager::AddToClientSockets(PTR_SOCKET_DATA a_socketData)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	m_clientSockets[m_socketCount++] = *a_socketData;
	ReleaseMutex(m_hMutex);
}

/**@brief	클라이언트 소켓 목록에서 특정 소켓을 제거한다.
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