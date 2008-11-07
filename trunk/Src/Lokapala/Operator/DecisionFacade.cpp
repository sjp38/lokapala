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