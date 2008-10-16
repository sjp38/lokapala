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
void CCommunicationFacade::NotifyAccepted(void *a_acceptedData)
{
	CCommunicationManager::Instance()->NotifyAccepted(a_acceptedData);
}

/**@brief	Ư�� ������� ��ǻ�͸� ��������.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::ShutdownUser(void *a_argument)
{
	CCommunicationManager::Instance()->ShutdownUser(a_argument);
}

/**@brief	Ư�� ������� ��ǻ�͸� ����� ��Ų��.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::RebootUser(void *a_argument)
{
	CCommunicationManager::Instance()->RebootUser(a_argument);
}

/**@brief	Ư�� ����ڸ� ���� �α׾ƿ� ��Ų��.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::LogoutUser(void *a_argument)
{
	CCommunicationManager::Instance()->LogoutUser(a_argument);
}

/**@brief	Ư�� ����ڿ��� Ư�� ���μ����� ���� ��Ų��.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::ExecuteUser(void *a_argument)
{
	CCommunicationManager::Instance()->ExecuteUser(a_argument);
}


/**@brief	Ư�� ������� �������� ��� ���μ����� ���δ�.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::GenocideUser(void *a_argument)
{
	CCommunicationManager::Instance()->GenocideUser(a_argument);
}

/**@brief	Ư�� ����ڿ��� ��� �޼����� ������.
 * @param	a_argment	��ǥ ������� ��ġ, ���� ���� �߰� �ൿ ���� ���� ����ü�� ������
 */
void CCommunicationFacade::WarnUser(void *a_argument)
{
	CCommunicationManager::Instance()->WarnUser(a_argument);
}