/**@file	DecisionFacade.cpp
 * @brief	DCM�� Facade�� ��� �Լ� ����
 * author	siva
 */

#include "stdafx.h"
#include "DecisionFacade.h"

#include "DecisionManager.h"

/**@brief	���۷����Ϳ��� �α��� ��û�� �Ѵ�.	*/
void CDecisionFacade::LoginRequest(void *a_userInfo)
{
	CDecisionManager::Instance()->LoginRequest(a_userInfo);
}


/**@brief	�α��� ��� �޼����� ���ϴ� ���񽺸� �Ѵ�.(����� ���� ����)
 */
void CDecisionFacade::LoginAccepted(int a_level)
{
	CDecisionManager::Instance()->LoginAccepted(a_level);
}

/**@brief	���۷����ͷκ����� ���� �α��� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionFacade::LoginOrderReceived(void *a_message)
{
	CDecisionManager::Instance()->LoginOrderReceived(a_message);
}

/**@brief	���۷����ͷκ����� ���� �α׾ƿ� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionFacade::LogoutOrderReceived(void *a_message)
{
	CDecisionManager::Instance()->LogoutOrderReceived(a_message);
}

/**@brief	���۷����ͷκ����� ���� ��ǻ�� ���� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionFacade::ShutdownOrderReceived(void *a_message)
{
	CDecisionManager::Instance()->ShutdownOrderReceived(a_message);
}

/**@brief	���۷����ͷκ����� ���� ��ǻ�� ������ ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionFacade::RebootOrderReceived(void *a_message)
{
	CDecisionManager::Instance()->RebootOrderReceived(a_message);
}

/**@brief	���۷����ͷκ����� �������� ��� ���μ��� ���� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionFacade::GenocideProcessesOrderReceived(void *a_message)
{
	CDecisionManager::Instance()->GenocideProcessesOrderReceived(a_message);
}

/**@brief	���۷����ͷκ����� Ư�� ���μ��� ���� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionFacade::KillProcessOrderReceived(void *a_processName)
{
	CDecisionManager::Instance()->KillProcessOrderReceived(a_processName);
}

/**@brief	���۷����ͷκ����� Ư�� ���μ��� ���� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionFacade::ExecuteProcessOrderReceived(void *a_processName)
{
	CDecisionManager::Instance()->ExecuteProcessOrderReceived(a_processName);
}



/**@brief	����� ���μ��� �̸��� ����޴´�.
 */
void CDecisionFacade::ReportExecutedProcess(CString *a_executedProcess)
{
	CDecisionManager::Instance()->ReportExecutedProcess(a_executedProcess);
}


/**@brief	��Ȳ ��ȭ�� �����Ѵ�.
 */
void CDecisionFacade::ReportStatus(void *a_status)
{
	CDecisionManager::Instance()->ReportStatus(a_status);
}