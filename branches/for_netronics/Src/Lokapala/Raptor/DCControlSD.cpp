/**@file	DCControlSD.cpp
 * @brief	DCM�� ControlSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCControlSD.h"

/**@brief	����ڸ� �����Ӱ� ��ǻ�͸� ��� �� �� �ֵ��� ���ش�.
 */
void CDCControlSD::ReleaseUser()
{
	CCBFMediator::Instance()->ReleaseUser();
}

/**@brief	������ �α��� ��Ų��.
 */
void CDCControlSD::Login(void *a_userInfo)
{
	CCBFMediator::Instance()->Login(a_userInfo);
}

/**@brief	������ �α׾ƿ� ��Ų��.
 */
void CDCControlSD::Logout(void *a_message)
{
	CCBFMediator::Instance()->Logout(a_message);
}

/**@brief	������ ��ǻ�� ���� ��Ų��.
 */
void CDCControlSD::Shutdown(void *a_message)
{
	CCBFMediator::Instance()->Shutdown(a_message);
}

/**@brief	������ ������ ��Ų��.
 */
void CDCControlSD::Reboot(void *a_message)
{
	CCBFMediator::Instance()->Reboot(a_message);
}

/**@brief	������ �������� ��� ���μ����� ���� ��Ų��.
 */
void CDCControlSD::GenocideProcesses(void *a_message)
{
	CCBFMediator::Instance()->GenocideProcesses(a_message);
}

/**@brief	������ �������� Ư�� ���μ����� ���� ��Ų��.
 */
void CDCControlSD::KillProcess(void *a_processName)
{
	CCBFMediator::Instance()->KillProcess(a_processName);
}

/**@brief	������ Ư�� ���μ����� ���� ��Ų��.
 */
void CDCControlSD::ExecuteProcess(void *a_processName)
{
	CCBFMediator::Instance()->ExecuteProcess(a_processName);
}