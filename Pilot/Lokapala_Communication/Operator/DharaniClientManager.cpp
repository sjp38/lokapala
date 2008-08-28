/**@file	DharaniClientManager.cpp
 * @brief	CDharaniClientManager의 멤버 함수를 구현
 * @author	siva
 */

#include "stdafx.h"
#include "Dharani.h"
#include "DharaniClientManager.h"

void CDharaniClientManager::Initiallize()
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		AfxMessageBox(_T("WSAStartup() error!"));
	}
	m_socket = WSASocket(PF_INET, SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);

	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(SERVER_PORT);
	
	if(connect(m_socket, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("connect() error!"));
	}

	WSABUF dataBuf;
	char message[]="sample message";
	dataBuf.len = strlen(message);
	dataBuf.buf = message;

	WSASend(m_socket, &dataBuf, 1, NULL, 0, NULL, NULL);

}