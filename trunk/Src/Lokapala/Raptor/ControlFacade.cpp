/**@file	ControlFacade.cpp
 * @brief	CTM의 Facade의 멤버함수 구현
 * author	siva
 */

#include "stdafx.h"
#include "ControlFacade.h"

#include "ControlManager.h"

/**@brief	사용자의 정상적인 컴퓨터 사용을 제한한다.
 */
void CControlFacade::RestraintUser()
{
	CControlManager::Instance()->RestraintUser();
}

/**@brief	사용자의 정상적인 컴퓨터 사용을 허락한다.
 */
void CControlFacade::ReleaseUser()
{
	CControlManager::Instance()->ReleaseUser();
}

/**@brief	강제로 사용자의 로그인을 해준다.
 */
void CControlFacade::Login(void *a_userInfo)
{
	CControlManager::Instance()->Login(a_userInfo);
}

/**@brief	강제로 사용자를 로그아웃 시킨다.
 */
void CControlFacade::Logout(void *a_message)
{
	CControlManager::Instance()->Logout(a_message);
}

/**@brief	컴퓨터를 꺼버린다.
 */
void CControlFacade::Shutdown(void *a_message)
{
	CControlManager::Instance()->Shutdown(a_message);
}

/**@brief	컴퓨터를 재부팅 시킨다.
 */
void CControlFacade::Reboot(void *a_message)
{
	CControlManager::Instance()->Reboot(a_message);
}

/**@brief	실행 중인 프로세스를 모조리 죽여버린다.
 */
void CControlFacade::GenocideProcesses(void *a_message)
{
	CControlManager::Instance()->GenocideProcesses(a_message);
}

/**@brief	특정 이름의 프로세스를 죽인다.
 */
void CControlFacade::KillProcess(void *a_processName)
{
	CControlManager::Instance()->KillProcess(a_processName);
}

/**@brief	특정 이름의 프로세스를 실행시킨다.
 */
void CControlFacade::ExecuteProcess(void *a_processName)
{
	CControlManager::Instance()->ExecuteProcess(a_processName);
}
