/**@file	DharaniClientManager.cpp
 * @brief	CDharaniClientManager의 멤버 함수를 구현
 * @author	siva
 */

#include "stdafx.h"
#include <process.h>
#include "Dharani.h"
#include "DharaniExternSD.h"
#include "DharaniClientManager.h"

void CDharaniClientManager::Initiallize()
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		AfxMessageBox(_T("WSAStartup() error!"));
	}

	m_serverSocket = WSASocket(PF_INET, SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);

	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(SERVER_PORT);
	
	if(connect(m_serverSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("connect() error!"));
	}

	_beginthreadex(NULL,0,&CDharaniClientManager::ReceiverThread,(LPVOID)m_serverSocket, 0, NULL);
}

/**@brief	쓰레드로 돌며 소켓으로 들어오는 값을 받는다.
 */
unsigned int WINAPI CDharaniClientManager::ReceiverThread(LPVOID a_serverSocket)
{
	SOCKET serverSocket = (SOCKET)a_serverSocket;
	char buffer[BUFSIZE];
	int receivedBytes;

	while(1)
	{
		receivedBytes = recv(serverSocket, buffer, BUFSIZE, 0);
		if(receivedBytes == SOCKET_ERROR)
		{
			AfxMessageBox(_T("receive failed!"));
			closesocket(serverSocket);
			WSACleanup();
			return 0;
		}
		if(receivedBytes == 0)
		{
			AfxMessageBox(_T("server connect failed!"));
			closesocket(serverSocket);
			WSACleanup();
			return 0;
		}

		buffer[receivedBytes]='\0';
		CDharaniExternSD::Instance()->NotifyReceived(buffer);
	}
	return 0;
}

/**@brief	메세지를 서버에게 날린다.
 */
void CDharaniClientManager::SendTextMessage(char *a_message)
{
	send(m_serverSocket, a_message, strlen(a_message), 0);
}