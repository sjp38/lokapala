/**@file	CCDecisionSD.cpp
 * @brief	CCM�� DecisionSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "CCDecisionSD.h"

/**@brief	�α��� �Ǿ����� �˸��� �׿� ���� ���񽺸� ��û�Ѵ�.
 * @param	a_level	�α��� ���� ������� ����.
 */
void CCCDecisionSD::LoginAccepted(int a_level)
{
	CCBFMediator::Instance()->LoginAccepted(a_level);
}

/**@brief	���� �α��� ����� �������� �˸���.
 */
void CCCDecisionSD::Login(void *a_message)
{
	CCBFMediator::Instance()->LoginOrderReceived(a_message);
}

/**@brief	���� �α׾ƿ� ����� �������� �˸���.
 */
void CCCDecisionSD::Logout(void *a_message)
{
	CCBFMediator::Instance()->LogoutOrderReceived(a_message);
}

/**@brief	���� ��ǻ�� ���� ����� �������� �˸���.
 */
void CCCDecisionSD::Shutdown(void *a_message)
{
	CCBFMediator::Instance()->ShutdownOrderReceived(a_message);
}

/**@brief	���� ����� ����� �������� �˸���.
 */
void CCCDecisionSD::Reboot(void *a_message)
{
	CCBFMediator::Instance()->RebootOrderReceived(a_message);
}

/**@brief	�������� ��� ���μ��� ���� ����� �������� �˸���.
 */
void CCCDecisionSD::GenocideProcesses(void *a_processName)
{
	CCBFMediator::Instance()->GenocideProcessesOrderReceived(a_processName);
}

/**@brief	Ư�� ���μ��� ���� ����� �������� �˸���.
 */
void CCCDecisionSD::KillProcess(void *a_processName)
{
	CCBFMediator::Instance()->KillProcessOrderReceived(a_processName);
}

/**@brief	Ư�� ���μ��� ���� ����� �������� �˸���.
 */
void CCCDecisionSD::ExecuteProcess(void *a_processName)
{
	CCBFMediator::Instance()->ExecuteProcessOrderReceived(a_processName);
}