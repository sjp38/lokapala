/**@file	LokapalaProtocol.h
 * @brief	로카파라에서 사용되는 프로토콜에 관한 상수값 등을 잡는다.
 * @author	siva
 */

//랩터 -> 오퍼레이터 헤더
//enum RaptorToOperatorPacketHeader {LOGIN_REQUEST, PROCESS_EXECUTED, STATUS_CHANGED, MESSAGE};

#define LOGIN_REQUEST		1
#define PROCESS_EXECUTED	2
#define STATUS_CHANGED		3
#define MESSAGE				4

//오퍼레이터 -> 랩터 헤더
#define LOGIN_ACCEPT		5
#define LOGIN				6
#define LOGOUT				7
#define SHUTDOWN			8
#define REBOOT				9
#define GENOCIDE			10
#define KILL				11
#define EXECUTE				12
#define STATUS_CHANGE		13