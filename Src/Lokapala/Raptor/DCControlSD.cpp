/**@file	DCControlSD.cpp
 * @brief	DCM의 ControlSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCControlSD.h"

/**@brief	사용자를 자유롭게 컴퓨터를 사용 할 수 있도록 해준다.
 */
void CDCControlSD::ReleaseUser()
{
	CCBFMediator::Instance()->ReleaseUser();
}

/**@brief	강제로 로그인 시킨다.
 */
void CDCControlSD::Login(void *a_userInfo)
{
	CCBFMediator::Instance()->Login(a_userInfo);
}

/**@brief	강제로 로그아웃 시킨다.
 */
void CDCControlSD::Logout(void *a_message)
{
	CCBFMediator::Instance()->Logout(a_message);
}

/**@brief	강제로 컴퓨터 종료 시킨다.
 */
void CDCControlSD::Shutdown(void *a_message)
{
	CCBFMediator::Instance()->Shutdown(a_message);
}

/**@brief	강제로 리부팅 시킨다.
 */
void CDCControlSD::Reboot(void *a_message)
{
	CCBFMediator::Instance()->Reboot(a_message);
}

/**@brief	강제로 실행중인 모든 프로세스를 종료 시킨다.
 */
void CDCControlSD::GenocideProcesses(void *a_message)
{
	CCBFMediator::Instance()->GenocideProcesses(a_message);
}

/**@brief	강제로 실행중인 특정 프로세스를 종료 시킨다.
 */
void CDCControlSD::KillProcess(void *a_processName)
{
	CCBFMediator::Instance()->KillProcess(a_processName);
}

/**@brief	강제로 특정 프로세스를 실행 시킨다.
 */
void CDCControlSD::ExecuteProcess(void *a_processName)
{
	CCBFMediator::Instance()->ExecuteProcess(a_processName);
}
