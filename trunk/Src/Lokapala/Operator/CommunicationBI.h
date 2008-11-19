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
	virtual void InitiallizeAsServer() = 0;
	virtual void SendTextMessageTo(CString a_targetAddress, CString a_message) = 0;
	virtual void BroadcastTextMessage(CString a_message) = 0;
	virtual void SendLoginAcceptedNotifyMessage(void *a_acceptedData) = 0;
	virtual void SendShutdownInstruction(void *a_argument) = 0;
	virtual void SendRebootInstruction(void *a_argument) = 0;
	virtual void SendBanUserInstruction(void *a_argument) = 0;
	virtual void SendExecuteProcessInstruction(void *a_argument) = 0;
	virtual void SendKillProcessInstruction(void *a_argument) = 0;
	virtual void SendGenocideProcessInstruction(void *a_argument) = 0;
	virtual void SendWarningMessage(void *a_argument) = 0;
	virtual void SendStatusReport(void *a_statusReport) = 0;
};

#endif