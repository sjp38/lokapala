/**@file	CommunicationFacade.cpp
 * @brief	CCM�� Facade�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include <atlconv.h>
#include "CommunicationFacade.h"

#include "CommunicationManager.h"

/**@brief	�����ν��� ����� ���� �ʱ�ȭ�� �Ѵ�.
 */
void CCommunicationFacade::InitiallizeAsServer()
{
	CCommunicationManager::Instance()->InitiallizeAsServer();
}

/**@brief	Ư�� �ּ��� raptor���� ���ڿ��� ������.
 * @param	a_targetAddress	���ڿ��� ���� raptor�� ip �ּ�
 * @param	a_message	���� ���ڿ� �޼���.
 */
void CCommunicationFacade::SendTextMessageTo(CString a_targetAddress, CString a_message)
{
	CCommunicationManager::Instance()->SendTextMessageTo(a_targetAddress, a_message);
}

/**@brief	����Ǿ� �ִ� ��� raptor���� ���ڸ� ������.
 * @param	a_message	���� ���ڿ� �޼���.
 */
void CCommunicationFacade::BroadcastTextMessage(CString a_message)
{	
	CCommunicationManager::Instance()->BroadcastTextMessage(a_message);
}

/**@brief	Ư�� ����ڿ��� �α��� ��� �޼����� �����Ѵ�.
 * @param	a_acceptedData	�α��� ���� ������� �ּ� �� ���� ���� �����͸� ���� ����ü�� ������
 */
void CCommunicationFacade::SendLoginAcceptedNotifyMessage(void *a_acceptedData)
{
	CCommunicationManager::Instance()->SendLoginAcceptedNotifyMessage(a_acceptedData);
}

/**@brief	Ư�� ������� ��ǻ�͸� ��������.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::SendShutdownInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendShutdownInstruction(a_argument);
}

/**@brief	Ư�� ������� ��ǻ�͸� ����� ��Ų��.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::SendRebootInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendRebootInstruction(a_argument);
}

/**@brief	Ư�� ����ڸ� ���� �α׾ƿ� ��Ų��.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::SendBanUserInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendBanUserInstruction(a_argument);
}

/**@brief	Ư�� ����ڿ��� Ư�� ���μ����� ���� ��Ų��.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::SendExecuteProcessInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendExecuteProcessInstruction(a_argument);
}

/**@brief	Ư�� ������� Ư�� ���μ����� �����Ų��.
 * @param	a_argument	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::SendKillProcessInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendKillProcessInstruction(a_argument);
}


/**@brief	Ư�� ������� �������� ��� ���μ����� ���δ�.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::SendGenocideProcessInstruction(void *a_argument)
{
	CCommunicationManager::Instance()->SendGenocideProcessInstruction(a_argument);
}

/**@brief	Ư�� ����ڿ��� ��� �޼����� ������.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::SendWarningMessage(void *a_argument)
{
	CCommunicationManager::Instance()->SendWarningMessage(a_argument);
}

/**@brief	Ư�� ����ڿ��� ���� ���� ������.
 * @param	a_statusReport	���� ���� ������ ���� ����ü�� ������.
 */
void CCommunicationFacade::SendStatusReport(void *a_statusReport)
{
	CCommunicationManager::Instance()->SendStatusReport(a_statusReport);
}