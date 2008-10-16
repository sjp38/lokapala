/**@file	ControlFacade.cpp
 * @brief	CTM�� Facade�� ����Լ� ����
 * author	siva
 */

#include "stdafx.h"
#include "ControlFacade.h"

#include "ControlManager.h"

/**@brief	������� �������� ��ǻ�� ����� �����Ѵ�.
 */
void CControlFacade::RestraintUser()
{
	CControlManager::Instance()->RestraintUser();
}

/**@brief	������� �������� ��ǻ�� ����� ����Ѵ�.
 */
void CControlFacade::ReleaseUser()
{
	CControlManager::Instance()->ReleaseUser();
}

/**@brief	������ ������� �α����� ���ش�.
 */
void CControlFacade::Login(void *a_userInfo)
{
	CControlManager::Instance()->Login(a_userInfo);
}

/**@brief	������ ����ڸ� �α׾ƿ� ��Ų��.
 */
void CControlFacade::Logout(void *a_message)
{
	CControlManager::Instance()->Logout(a_message);
}

/**@brief	��ǻ�͸� ��������.
 */
void CControlFacade::Shutdown(void *a_message)
{
	CControlManager::Instance()->Shutdown(a_message);
}

/**@brief	��ǻ�͸� ����� ��Ų��.
 */
void CControlFacade::Reboot(void *a_message)
{
	CControlManager::Instance()->Reboot(a_message);
}

/**@brief	���� ���� ���μ����� ������ �׿�������.
 */
void CControlFacade::GenocideProcesses(void *a_message)
{
	CControlManager::Instance()->GenocideProcesses(a_message);
}

/**@brief	Ư�� �̸��� ���μ����� ���δ�.
 */
void CControlFacade::KillProcess(void *a_processName)
{
	CControlManager::Instance()->KillProcess(a_processName);
}

/**@brief	Ư�� �̸��� ���μ����� �����Ų��.
 */
void CControlFacade::ExecuteProcess(void *a_processName)
{
	CControlManager::Instance()->ExecuteProcess(a_processName);
}