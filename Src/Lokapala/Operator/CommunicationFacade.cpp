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