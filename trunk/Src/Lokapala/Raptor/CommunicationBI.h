/**@file	CommunicationBI.h
 * @brief	CCM의 Button Interface 정의
 * @author	siva
 */
#ifndef COMMUNICATION_BI_H
#define COMMUNICATION_BI_H

/**@ingroup GroupCCM
 * @class	CCommunicationBI
 * @brief	Communication Manager의 Button Interface.\n
			Mediator에게 자신을 노출하여 Mediator로부터 CCM으로의 인터페이스를 공개한다.
 * @remarks	인터페이스일 뿐으로, Facade가 상속한다.
 */
class CCommunicationBI
{
public :
	virtual void Initiallize(DWORD a_ServerAddress) = 0;
	virtual void CloseConnection() = 0;
	virtual void SendTextMessageToOperator(CString *a_message) = 0;
	virtual void SendLoginRequest(void *a_userInfo) = 0;
	virtual void SendExecutedProcessReport(CString *a_executedProcess) = 0;
	virtual void SendStatusReport(void *a_statusReport) = 0;
};

#endif
