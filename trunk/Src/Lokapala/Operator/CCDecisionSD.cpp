/**@file	CCDecisionSD.cpp
 * @brief	CCM�� DecisionSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "CCDecisionSD.h"

/**@brief	������� �α��� ������ ���� ��ȿ�� ��������� Ȯ���Ѵ�.
 * @param	a_loginRequestData	����� �α��� ������ ������. �ش� DTO�� ������������ void �����ͷ� ĳ���� �� ����Ѵ�.
 */
void CCCDecisionSD::UserLogin(void *a_loginRequestData)
{
	CCBFMediator::Instance()->UserLogin(a_loginRequestData);
}


/**@brief	������� ������ ���μ��� ���� ���� ����, �����ص� �Ǵ� ���μ������� ��� Ȯ��, ó�����ش�.
 * @param	a_executedProcessData	����ڰ� ������ ���μ����� ���� ������ ������. �ش� DTO�� ������������ void �����ͷ� ĳ���� �� ����Ѵ�.
 */
void CCCDecisionSD::JudgeUserExecutedProcess(void *a_executedProcessData)
{
	CCBFMediator::Instance()->JudgeUserExecutedProcess(a_executedProcessData);
}


/**@brief	����ڷκ����� ���� ���� ���� ���� ó��.
 * @param	a_statusReportData	����ڰ� ������ ���� ���� ���� ���뿡 ���� ������ ������. �ش� DTO�� ������������ void �����ͷ� ĳ���� �� ����Ѵ�.
 */
void CCCDecisionSD::PresentStatusReport(void *a_statusReportData)
{
	CCBFMediator::Instance()->PresentStatusReport(a_statusReportData);
}