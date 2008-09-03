/**@file	Dharani.h
 * @brief	Dharani component 에서 사용되는 자료형 및 상수 들을 정의
 * @author	siva
 */

#ifndef DHARANI_H
#define DHARANI_H

#define BUFSIZE	256
#define CONCURRENT_THREAD_NUM 10
#define SERVER_PORT 9987
#define MAXCLIENT 128

typedef struct 
{
	SOCKET descriptor;
	SOCKADDR_IN addr;
	in_addr localIp;
} SOCKET_DATA, *PTR_SOCKET_DATA;

typedef struct
{
	OVERLAPPED overlapped;
	char buffer[BUFSIZE];
	WSABUF wsaBuf;
} IO_DATA, *PTR_IO_DATA;

#endif