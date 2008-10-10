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
void CControlFacade::Logout()
{
	CControlManager::Instance()->Logout();
}

/**@brief	��ǻ�͸� ��������.
 */
void CControlFacade::Shutdown()
{
	CControlManager::Instance()->Shutdown();
}

/**@brief	��ǻ�͸� ����� ��Ų��.
 */
void CControlFacade::Reboot()
{
	CControlManager::Instance()->Reboot();
}

/**@brief	���� ���� ���μ����� ������ �׿�������.
 */
void CControlFacade::GenocideProcesses()
{
	CControlManager::Instance()->GenocideProcesses();
}

/**@brief	Ư�� �̸��� ���μ����� ���δ�.
 */
void CControlFacade::KillProcess(CString *a_processName)
{
	CControlManager::Instance()->KillProcess(a_processName);
}

/**@brief	Ư�� �̸��� ���μ����� �����Ų��.
 */
void CControlFacade::ExecuteProcess(CString *a_processName)
{
	CControlManager::Instance()->ExecuteProcess(a_processName);
}