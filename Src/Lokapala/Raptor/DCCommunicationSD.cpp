/**@file	DCCommunicationSD.cpp
 * @brief	DCM�� CommunicationSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCCommunicationSD.h"


/**@brief	Ŀ�´����̼� ������Ʈ���� �α��� ��ȣ�� �������� �Ѵ�.
 */
void CDCCommunicationSD::LoginRequest(void *a_userInfo)
{
	CCBFMediator::Instance()->SendLoginRequest(a_userInfo);
}

/**@brief	CCM���� ���� ���μ��� ���� �������� �Ѵ�.
 */
void CDCCommunicationSD::ReportExecutedProcess(CString *a_executedProcess)
{
	CCBFMediator::Instance()->SendExecutedProcessReport(a_executedProcess);
}

/**@brief	CCM���� ����� ��Ȳ�� �����Ѵ�.
 */
void CDCCommunicationSD::ReportStatus(void *a_status)
{
	CCBFMediator::Instance()->SendStatusReport(a_status);
}