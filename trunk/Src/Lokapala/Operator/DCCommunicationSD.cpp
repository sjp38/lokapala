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
	CCBFMediator::Instance()->SendLoginAcceptedNotifyMessage(a_acceptedData);
}


/**@brief	Ư�� ������ ��ǻ�͸� ��������.
 */
void CDCCommunicationSD::SendShutdownInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendShutdownInstruction(a_argument);
}

/**@brief	Ư�� ������ ��ǻ�͸� ����� ��Ų��.
 */
void CDCCommunicationSD::SendRebootInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendRebootInstruction(a_argument);
}

/**@brief	Ư�� ������ �α׾ƿ� ��Ų��.
 */
void CDCCommunicationSD::SendBanUserInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendBanUserInstruction(a_argument);
}

/**@brief	Ư�� �������� Ư�� ���μ����� �����Ų��.
 */
void CDCCommunicationSD::SendExecuteProcessInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendExecuteProcessInstruction(a_argument);
}

/**@brief	Ư�� ������ Ư�� ���μ����� �����Ų��.
 */
void CDCCommunicationSD::SendKillProcessInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendKillProcessInstruction(a_argument);
}

/**@brief	Ư�� ������ �����ϰ� �ִ� ��� ���μ����� ���δ�.
 */
void CDCCommunicationSD::SendGenocideProcessInstruction(void *a_argument)
{
	CCBFMediator::Instance()->SendGenocideProcessInstruction(a_argument);
}

/**@brief	Ư�� �������� ��� �޼����� �ѱ��.
 */
void CDCCommunicationSD::SendWarningMessage(void *a_argument)
{
	CCBFMediator::Instance()->SendWarningMessage(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ���� ���� ���� ������.
 */
void CDCCommunicationSD::SendStatusReport(void *a_statusReport)
{
	CCBFMediator::Instance()->SendStatusReport(a_statusReport);
}