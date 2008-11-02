/**@file	DCCommunicationSD.cpp
 * @brief	DCM�� CommunicationSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCCommunicationSD.h"


/**@brief	�ش��ϴ� �ּ��� ������� �α��� ��� �޼����� ������.
 */
void CDCCommunicationSD::NotifyAccepted(void *a_acceptedData)
{
	CCBFMediator::Instance()->NotifyAccepted(a_acceptedData);
}


/**@brief	Ư�� ������ ��ǻ�͸� ��������.
 */
void CDCCommunicationSD::ShutdownUser(void *a_argument)
{
	CCBFMediator::Instance()->ShutdownUser(a_argument);
}

/**@brief	Ư�� ������ ��ǻ�͸� ����� ��Ų��.
 */
void CDCCommunicationSD::RebootUser(void *a_argument)
{
	CCBFMediator::Instance()->RebootUser(a_argument);
}

/**@brief	Ư�� ������ �α׾ƿ� ��Ų��.
 */
void CDCCommunicationSD::LogoutUser(void *a_argument)
{
	CCBFMediator::Instance()->LogoutUser(a_argument);
}

/**@brief	Ư�� �������� Ư�� ���μ����� �����Ų��.
 */
void CDCCommunicationSD::ExecuteUser(void *a_argument)
{
	CCBFMediator::Instance()->ExecuteUser(a_argument);
}

/**@brief	Ư�� ������ Ư�� ���μ����� �����Ų��.
 */
void CDCCommunicationSD::KillUser(void *a_argument)
{
	CCBFMediator::Instance()->KillUser(a_argument);
}

/**@brief	Ư�� ������ �����ϰ� �ִ� ��� ���μ����� ���δ�.
 */
void CDCCommunicationSD::GenocideUser(void *a_argument)
{
	CCBFMediator::Instance()->GenocideUser(a_argument);
}

/**@brief	Ư�� �������� ��� �޼����� �ѱ��.
 */
void CDCCommunicationSD::WarnUser(void *a_argument)
{
	CCBFMediator::Instance()->WarnUser(a_argument);
}