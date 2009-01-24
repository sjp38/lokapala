/**@file	DharaniClientManager.cpp
 * @brief	CDharaniClientManager의 멤버 함수를 구현
 * @author	siva
 */

#include "stdafx.h"
#include <process.h>
#include "Dharani.h"
#include "DharaniExternSD.h"
#include "DharaniClientManager.h"

void CDharaniClientManager::Initiallize(DWORD a_ServerAddress)
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		AfxMessageBox(_T("WSAStartup() error!"));
		return;
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
		return;
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
		int totalReceived=0;
		while(1)
		{
			int receivedBytes = recv(serverSocket, buffer+totalReceived, BUFSIZE, 0);
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

			char size[3];
			_itoa_s(buffer[0],size,16);
			CDharaniExternSD::Instance()->NotifyReceived(size);
			CDharaniExternSD::Instance()->NotifyReceived(buffer);	//테스트용.

			CDharaniClientManager::Instance()->Decrypt(decrypted, buffer+1);
			
			totalReceived += receivedBytes;
			if(totalReceived == buffer[0]+1)
			{
				decrypted[totalReceived]='\0';
				break;
			}
		}
		CDharaniExternSD::Instance()->NotifyReceived(decrypted);
	}
	return 0;
}

/**@brief	메세지를 서버에게 날린다.
 * @param	a_message	보낼 메세지
 */
void CDharaniClientManager::SendTextMessage(char *a_message)
{
	char encrypted[BUFSIZE];
	encrypted[0] = (unsigned char)strlen(a_message);
	this->Encrypt(a_message, encrypted+1);
	send(m_serverSocket, encrypted, strlen(a_message)+1, 0);
}


/**@brief	특정 문자열을 암호화 한다. RC4 알고리즘을 사용한다.
 * @param	a_plainText	암호화 될, 오리지널 문자열
 * @param	a_cipherText	암호화 된 후의 문자열
 */
void CDharaniClientManager::Encrypt(char *a_plainText, char *a_cipherText)
{
	RC4_KEY rc4Key;
	RC4_set_key(&rc4Key, strlen((char *)&m_passwd),(unsigned char *)&m_passwd);
	RC4(&rc4Key, strlen(a_plainText), (unsigned char *)a_plainText, (unsigned char *)a_cipherText);
}

/**@brief	특정 문자열을 복호화 한다. RC4 알고리즘을 사용한다.
 * @param	a_plainText	복호화 된 후의 문자열
 * @param	a_cipherText	복호화 될 오리지널 암호문자열
 */
void CDharaniClientManager::Decrypt(char *a_plainText, char *a_cipherText)
{
	RC4_KEY rc4Key;
	RC4_set_key(&rc4Key, strlen((char *)&m_passwd),(unsigned char *)&m_passwd);
	RC4(&rc4Key, strlen(a_cipherText), (unsigned char *)a_cipherText, (unsigned char *)a_plainText);
}