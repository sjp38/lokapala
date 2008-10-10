/**@file	ControlManager.cpp
 * @brief	CControlManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "ControlManager.h"


/**@brief	생성자. 로그인 다이얼로그를 생성하고 위치를 잡는다.
 */
CControlManager::CControlManager()
{
	m_loginDlg = new CLoginDlg();
	m_loginDlg->Create(IDD_LOGIN_DIALOG);
	int screenx = GetSystemMetrics(SM_CXSCREEN);
	int screeny = GetSystemMetrics(SM_CYSCREEN);
	m_loginDlg->MoveWindow(0,0,screenx, screeny);
	::SetWindowPos(m_loginDlg->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);	//윈도우를 최상위로 위치시킨다.
}

/**@brief	로그인 윈도우를 화면 최상단에 화면 크기로 보이게 한다.
 */
void CControlManager::ShowLoginWindow()
{
	m_loginDlg->ShowWindow(SW_SHOW);
}

/**@brief	로그인 윈도우를 사라지게 해 사용자의 컴퓨터 이용 제한을 해제한다.
 */
void CControlManager::HideLoginWindow()
{
	if(!m_restraint)
	{
		m_loginDlg->ShowWindow(SW_HIDE);
	}
}

/**@brief	사용자의 정상적 컴퓨터 사용을 제한한다.
 *			로그인 창을 화면 최상단에 화면 크기로 보이게 해 사용자의 정상적 컴퓨터 이용을 제한한다.
 */
void CControlManager::RestraintUser()
{
	m_restraint = TRUE;
	ShowLoginWindow();
}

/**@brief	사용자의 정상적 컴퓨터 사용을 가능하게 만든다.
 *			로그인 창을 없앤다.
 */
void CControlManager::ReleaseUser()
{
	m_restraint = FALSE;
	HideLoginWindow();
}

/**@brief	강제로 사용자를 로그인 시킨다.
 */
void CControlManager::Login(void *a_userInfo)
{
}

/**@brief	강제로 사용자를 로그아웃 시킨다.
 */
void CControlManager::Logout()
{
}

/**@brief	컴퓨터를 종료시킨다.
 */
void CControlManager::Shutdown()
{
}

/**@brief	컴퓨터를 리부팅시킨다.
 */
void CControlManager::Reboot()
{
}

/**@brief	실행되고 있는 모든 프로세스를 종료시킨다.
 */
void CControlManager::GenocideProcesses()
{
}

/**@brief	특정 프로세스를 종료시킨다.
 * @param	a_processName	종료시키고자 하는 프로세스의 이름
 */
void CControlManager::KillProcess(CString *a_processName)
{
}

/**@brief	특정 프로세스를 실행시킨다.
 * @param	a_processName	실행하고자 하는 프로세스의 이름
 */
void CControlManager::ExecuteProcess(CString *a_processName)
{
}