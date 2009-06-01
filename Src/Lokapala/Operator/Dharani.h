/**@file	Dharani.h
 * @brief	Dharani component 에서 사용되는 자료형 및 상수 들을 정의
 * @author	siva
 */

#ifndef DHARANI_H
#define DHARANI_H

#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/rc4.h>

#define BUFSIZE	1024
#define CONCURRENT_THREAD_NUM 10
#define SERVER_PORT 9987
#define MAXCLIENT 128


//헤더
#define LOCAL_IP 7
#define ACK_LOCAL_IP 8
#define HELLO 1
#define ACK_HELLO 2
#define KEY 3
#define ACK_KEY 4
#define DATA 5
#define ACK_DATA 6

#define RC4PASSWD "RC4Pass!"


typedef struct 
{
	SOCKET descriptor;
	SOCKADDR_IN addr;
	in_addr localIp;
	int passwd;
	bool lifeSignal;
	int lifeSignalUnchecked;
} SOCKET_DATA, *PTR_SOCKET_DATA;

typedef struct
{
	OVERLAPPED overlapped;
	char buffer[BUFSIZE];
	WSABUF wsaBuf;
	unsigned short formerReceivedBytes;
} IO_DATA, *PTR_IO_DATA;

#endif
