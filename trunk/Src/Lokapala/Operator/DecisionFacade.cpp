/**@file	DecisionFacade.cpp
 * @brief	DCM�� Facade�� ��� �Լ� ����
 * author	siva
 */

#include "stdafx.h"
#include "DecisionFacade.h"

#include "DecisionManager.h"

/**@brief	������ ȣ��Ʈ�� ���� ó��
 */
void CDecisionFacade::HostConnected(void *a_hostData)
{
	CDecisionManager::Instance()->HostConnected(a_hostData);
}

/**@brief	���� ������ ȣ��Ʈ�� ���� ó��
 */
void CDecisionFacade::HostDisconnected(void *a_hostData)
{
	CDecisionManager::Instance()->HostDisconnected(a_hostData);
}

/**@brief	����� �α��� ó��. �ùٸ� ��������� Ȯ���Ѵ�.
 * @param	a_loginRequestData	����� �α��� ������ ������. �ش� DTO�� ������������ void �����ͷ� ĳ���� �� ����Ѵ�.
 */
void CDecisionFacade::JudgeLoginRequest(void *a_loginRequestData)
{
	CDecisionManager::Instance()->JudgeLoginRequest(a_loginRequestData);
}


/**@brief	����� ���� ���μ����� ���� ó��.
 */
void CDecisionFacade::JudgeUserExecutedProcess(void *a_executedProcessData)
{
	CDecisionManager::Instance()->JudgeUserExecutedProcess(a_executedProcessData);
}


/**@brief	���ο� ���� ���� ���� ���� ó��.
 */
void CDecisionFacade::PresentStatusReport(void *a_statusReportData)
{
	CDecisionManager::Instance()->PresentStatusReport(a_statusReportData);
}


/**@brief	Ư�� ȣ��Ʈ�� ��ǻ�͸� ���� ��Ų��.
 */
void CDecisionFacade::ShutdownHost(void *a_argument)
{
	CDecisionManager::Instance()->ShutdownHost(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� ��ǻ�͸� ������ ��Ų��.
 */
void CDecisionFacade::RebootHost(void *a_argument)
{
	CDecisionManager::Instance()->RebootHost(a_argument);
}

/**@brief	Ư�� ����ڸ� ������ �α׾ƿ� ��Ų��.
 */
void CDecisionFacade::BanUser(void *a_argument)
{
	CDecisionManager::Instance()->BanUser(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� Ư�� ���μ����� �����Ų��.
 */
void CDecisionFacade::ExecuteHostProcess(void *a_argument)
{
	CDecisionManager::Instance()->ExecuteHostProcess(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� Ư�� ���μ����� ���� ��Ų��.
 */
void CDecisionFacade::KillHostProcess(void *a_argument)
{
	CDecisionManager::Instance()->KillHostProcess(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� ��� ���μ����� ���� ��Ų��.
 */
void CDecisionFacade::GenocideHostProcess(void *a_argument)
{
	CDecisionManager::Instance()->GenocideHostProcess(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ���� ��� ������.
 */
void CDecisionFacade::WarnHost(void *a_argument)
{
	CDecisionManager::Instance()->WarnHost(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ���� ���� ���� ������.
 */
void CDecisionFacade::SubmitStatusReportToHost(void *a_statusReport)
{
	CDecisionManager::Instance()->SubmitStatusReportToHost(a_statusReport);
}