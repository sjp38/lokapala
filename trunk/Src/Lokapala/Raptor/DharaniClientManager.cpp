/**@file	DharaniClientManager.cpp
 * @brief	CDharaniClientManager의 멤버 함수를 구현
 * @author	siva
 */

#include "stdafx.h"
#include <process.h>
#include "Dharani.h"
#include "DharaniExternSD.h"
#include "DharaniClientManager.h"


/**@brief	클라이언트의 형태로 소켓 상황 등을 초기화하고 프로토콜 초기 행위(암호화 키 교환 등)를 한다.
 * @return	정상적으로 초기화를 마쳤을 경우 0, 문제가 있을 경우 -1
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
	_beginthreadex(NULL,0,&CDharaniClientManager::LifeSignalSenderThread,(LPVOID)m_serverSocket, 0, NULL);
	CDharaniExternSD::Instance()->NotifyConnected();
	return 0;
}



int CDharaniClientManager::m_passwd = 0;

/**@brief	쓰레드로 돌면서 1초마다 한번씩 서버측으로 생명 신호를 날린다.
 */
unsigned int WINAPI CDharaniClientManager::LifeSignalSenderThread(LPVOID a_serverSocket)
{
	SOCKET serverSocket = (SOCKET)a_serverSocket;
	char lifeSignal[] = "tkfdkdlTdma";
	while(1)
	{
		int size = strlen(lifeSignal)+1;	

		char encrypted[BUFSIZE];
		Encrypt(lifeSignal, encrypted+sizeof(size));
		memcpy(encrypted, &size, sizeof(size));

		send(serverSocket, encrypted, sizeof(size)+size, 0);

		Sleep(1000);
	}
	return 0;
}

/**@brief	특정 소켓으로부터 특정 크기의 데이터를 완벽하게 받아낸다. tcp 특유의 데이터 분절 문제를 해결한다.
 * @param	a_srcSocket	데이터를 받아 올 소켓
 * @param	a_size		받아 올 데이터의 크기
 * @param	a_target	받아 온 데이터를 넣어 줄 포인터.
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

/**@brief	쓰레드로 돌며 소켓으로 들어오는 값을 받는다.
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

/**@brief	서버와의 연결을 끊는다.
 */
void CDharaniClientManager::CloseConnection()
{
	closesocket(m_serverSocket);
	WSACleanup();
}

/**@brief	메세지를 서버에게 날린다.
 * @param	a_message	보낼 메세지
 */
void CDharaniClientManager::SendTextMessage(char *a_message)
{
	int size = strlen(a_message)+1;	

	char encrypted[BUFSIZE];
	this->Encrypt(a_message, encrypted+sizeof(size));
	memcpy(encrypted, &size, sizeof(size));
	
	send(m_serverSocket, encrypted, sizeof(size)+size, 0);
}


/**@brief	특정 문자열을 암호화 한다. RC4 알고리즘을 사용한다.
 * @param	a_plainText	암호화 될, 오리지널 문자열
 * @param	a_cipherText	암호화 된 후의 문자열
 */
void CDharaniClientManager::Encrypt(char *a_plainText, char *a_cipherText)
{
	RC4_KEY rc4Key;
	RC4_set_key(&rc4Key, strlen((char *)&m_passwd),(unsigned char *)&m_passwd);
	RC4(&rc4Key, strlen(a_plainText)+1, (unsigned char *)a_plainText, (unsigned char *)a_cipherText);
}

/**@brief	특정 문자열을 복호화 한다. RC4 알고리즘을 사용한다.
 * @param	a_plainText	복호화 된 후의 문자열
 * @param	a_cipherText	복호화 될 오리지널 암호문자열
 */
void CDharaniClientManager::Decrypt(char *a_plainText, char *a_cipherText, unsigned int a_size)
{
	RC4_KEY rc4Key;
	RC4_set_key(&rc4Key, strlen((char *)&m_passwd),(unsigned char *)&m_passwd);
	RC4(&rc4Key, a_size, (unsigned char *)a_cipherText, (unsigned char *)a_plainText);
}
