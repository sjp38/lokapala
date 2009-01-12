/**@file	CommunicationBI.h
 * @brief	CCM�� Button Interface ����
 * @author	siva
 */
#ifndef COMMUNICATION_BI_H
#define COMMUNICATION_BI_H

/**@ingroup GroupCCM
 * @class	CCommunicationBI
 * @brief	Communication Manager�� Button Interface.\n
			Mediator���� �ڽ��� �����Ͽ� Mediator�κ��� CCM������ �������̽��� �����Ѵ�.
 * @remarks	�������̽��� ������, Facade�� ����Ѵ�.
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