/**@file	LokapalaProtocol.h
 * @brief	��ī�Ķ󿡼� ���Ǵ� �������ݿ� ���� ����� ���� ��´�.
 * @author	siva
 */

//���� -> ���۷����� ���
//enum RaptorToOperatorPacketHeader {LOGIN_REQUEST, PROCESS_EXECUTED, STATUS_CHANGED, MESSAGE};

#define LOGIN_REQUEST		1
#define PROCESS_EXECUTED	2
#define STATUS_CHANGED		3
#define MESSAGE				4

//���۷����� -> ���� ���
#define LOGIN_ACCEPT		5
#define LOGIN				6
#define LOGOUT				7
#define SHUTDOWN			8
#define REBOOT				9
#define GENOCIDE			10
#define KILL				11
#define EXECUTE				12
#define STATUS_CHANGE		13