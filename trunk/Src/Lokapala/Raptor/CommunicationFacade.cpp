/**@file	CommunicationFacade.cpp
 * @brief	CCM�� Facade�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "CommunicationFacade.h"

#include "CommunicationManager.h"

/**@brief	������ ������ ��, ���۷����Ϳ��� connect �Ѵ�.
 */
void CCommunicationFacade::Initiallize(DWORD a_ServerAddress)
{
	CCommunicationManager::Instance()->Initiallize(a_ServerAddress);
}

/**@brief	���۷����Ϳ��� ������ ���´�.
 */
void CCommunicationFacade::CloseConnection()
{
	CCommunicationManager::Instance()->CloseConnection();
}


/**@brief	�ؽ�Ʈ �޼����� ���۷����Ϳ��� ������.
 */
void CCommunicationFacade::SendTextMessageToOperator(CString *a_message)
{
	CCommunicationManager::Instance()->SendTextMessageToOperator(a_message);
}


/**@brief	���۷����Ϳ��� �α��� ��û�� ������.
 */
void CCommunicationFacade::SendLoginRequest(void *a_userInfo)
{
	CCommunicationManager::Instance()->SendLoginRequest(a_userInfo);
}


/**@brief	���۷����Ϳ��� ����� ���μ��� �̸��� ������.
 */
void CCommunicationFacade::SendExecutedProcessReport(CString *a_executedProcess)
{
	CCommunicationManager::Instance()->SendExecutedProcessReport(a_executedProcess);
}


/**@brief	��Ȳ ���� ���۷����Ϳ��� �����Ѵ�.
 */
void CCommunicationFacade::SendStatusReport(void *a_statusReport)
{
	CCommunicationManager::Instance()->SendStatusReport(a_statusReport);
}