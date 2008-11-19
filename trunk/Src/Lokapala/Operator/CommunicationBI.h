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