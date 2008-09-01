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
	virtual void Initiallize() = 0;
	virtual void SendTextMessage(CString a_message) = 0;
};

#endif