/**@file	DharaniServerManager.cpp
 * @brief	CDharaniServerManager 의 멤버 함수를 구현
 * @author	siva
 */

#include "stdafx.h"
#include <process.h>

//openssl 헤더 include
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/rc4.h>

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
	if(-1 == bind(hListenSocket, (SOCKADDR *)&servAddr, sizeof(servAddr)) )
	{
		AfxMessageBox(_T("bind() Failed!"));
	}
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

		//클라이언트의 로컬 ip 정보(private ip일 수 있다)를 받는다.
		in_addr clientLocalIp;
		recv(hClientSocket, (char *)((void *)&clientLocalIp), sizeof(in_addr), 0);		

		//암호화 키 생성
		int passwd = rand();
		//암호화 키 전송
		WSABUF wsaBuf;
		wsaBuf.buf = (char *)&passwd;
		wsaBuf.len = sizeof(int);
		WSASend(hClientSocket, &wsaBuf, 1, NULL, 0, NULL, NULL);
		
		//소켓 데이터 세팅
		socketData = (PTR_SOCKET_DATA)malloc(sizeof(SOCKET_DATA));
		socketData->descriptor = hClientSocket;
		memcpy(&(socketData->addr), &clientAddress, addrLen);
		socketData->localIp = (in_addr)clientLocalIp;
		socketData->passwd = passwd;
		
		//completion port에 소켓을 연결.
		CreateIoCompletionPort((HANDLE)hClientSocket, (HANDLE)a_hCompletionPort, (DWORD)socketData, 0);
		
		//클라이언트 소켓 목록에 소켓 정보를 추가(크리티컬 섹션).
		CDharaniServerManager::Instance()->AddToClientSockets(socketData);

		//해당 소켓 전용 ioData를 동적 할당한다.
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
	int size=0;

	while(1)
	{
		GetQueuedCompletionStatus( (HANDLE)a_hCompletionPort, &bytesTransferred, (LPDWORD)&socketData, (LPOVERLAPPED *)&ioData, INFINITE);

		if(bytesTransferred == 0)	//EOF 전송(연결 끊어짐)
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

		//연속성 처리 : 데이터가 아직 다 들어오지 않았을 때
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

		//데이터가 모두 들어왔을 때
		//CDharaniExternSD::Instance()->NotifyReceived(ioData->buffer, socketData->localIp, socketData->addr.sin_addr);	//복호화 이전. 테스트

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


/**@brief	입력받은 메세지를 dharani 프로토콜에 맞게 해석한다.\n
			현재 시점에서는 사용되지 않으며, 추후 파일 전송 기능 추가 시, 헤더 정보로 파일/메세지를 구분한다.\n
			메세지 길이 처리 또한 이쪽으로 분담할 수도 있다.
 * @param	a_receivedMessage	받은 메세지.
 * @param	a_sender			메세지를 보낸 상대방으로의 소켓.
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

/**@brief	특정 소켓에게 메세지를 보낸다.
 * @param	a_receiver	상대방으로의 소켓
 * @param	a_message	보낼 메세지
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

/**@brief	클라이언트들에게 메세지를 뿌려준다.
 *			내부적으로 SendMessageTo 메소드를 사용한다.
 * @param	a_message	방송하고자 하는 메세지
 */
void CDharaniServerManager::BroadcastTextMessage(char *a_message)
{
	for(int i=0 ;i<this->m_socketCount ; i++)
	{
		SendMessageTo(&m_clientSockets[i], a_message);
	}
}

/**@brief	클라이언트 소켓 목록에서 특정 소켓의 정보를 얻어온다.
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

/**@brief	클라이언트 소켓 목록에 소켓 정보를 추가한다.
 */
void CDharaniServerManager::AddToClientSockets(PTR_SOCKET_DATA a_socketData)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	m_clientSockets[m_socketCount++] = *a_socketData;
	ReleaseMutex(m_hMutex);
}

/**@brief	클라이언트 소켓 목록에서 특정 소켓을 제거하고, 제거 했음을 알린다.
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


/**@brief	글로벌, 로컬 아이피를 가지고 현재 연결된 클라이언트 목록에서 해당 클라이언트의 소켓을 찾아 소켓 데이터를 반환한다.
 * @param	a_globalIp	찾고자 하는 클라이언트의 글로벌 아이피
 * @param	a_localIp	찾고자 하는 클라이언트의 로컬 아이피
 * @return	해당 클라이언트의 소켓 데이터(SOCKET_DATA) 포인터. 찾지 못했을 경우 0
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


/**@brief	특정 문자열을 복호화 한다.
 * @param	a_passwd	RC4 알고리즘 키
 * @param	a_length	복호/암호화 할 문자열의 길이
 * @param	a_plainText	복호화 된 후의 문자열의 포인터
 * @param	a_cipherText	복호화 될, 암호화 된 문자열
 */
void CDharaniServerManager::Decrypt(int a_passwd, size_t a_length, char *a_plainText, char *a_cipherText)
{
	RC4_KEY rc4Key;
	RC4_set_key(&rc4Key,strlen((char *)&a_passwd),(unsigned char *)&a_passwd);
	RC4(&rc4Key, a_length, (unsigned char *)a_cipherText, (unsigned char *)a_plainText);
}

/**@brief	특정 문자열을 암호화 한다.
 * @param	a_key	RC4 알고리즘 키
 * @param	a_plainText	암호화 될 오리지널 문자열
 * @param	a_cipherText	암호화 된 후의 문자열의 포인터
 */
void CDharaniServerManager::Encrypt(int a_passwd, char *a_plainText, char *a_cipherText)
{
	RC4_KEY rc4Key;
	RC4_set_key(&rc4Key,strlen((char *)&a_passwd),(unsigned char *)&a_passwd);
	RC4(&rc4Key, strlen(a_plainText)+1, (unsigned char *)a_plainText, (unsigned char *)a_cipherText);
}