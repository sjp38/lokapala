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
	virtual void NotifyAccepted(void *a_acceptedData) = 0;
	virtual void ShutdownUser(void *a_argument) = 0;
	virtual void RebootUser(void *a_argument) = 0;
	virtual void LogoutUser(void *a_argument) = 0;
	virtual void ExecuteUser(void *a_argument) = 0;
	virtual void GenocideUser(void *a_argument) = 0;
	virtual void WarnUser(void *a_argument) = 0;
};

#endif