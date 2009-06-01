/**@file	ControlManager.h
 * @brief	CControlManager 클래스를 정의한다.
 * @author	siva
 */

#ifndef CONTROL_MANAGER_H
#define CONTROL_MANAGER_H

#include "LoginDlg.h"

/**@ingroup	GroupCTM
 * @class	CControlManager
 * @brief	사용자의 방해, 방해 해제, 특정/전체 프로세스 종료, 컴퓨터 강제 shut down, 특정 프로세스 실행 등의 사용자 컨트롤을 한다.
 */
class CControlManager
{
public :
	static CControlManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CControlManager();
		}
		return m_instance;
	}

	void RestraintUser();
	void ReleaseUser();
	
	void Login(void *a_userInfo);
	void Logout(void *a_message);
	
	void Shutdown(void *a_argument);
	void Reboot(void *a_argument);

	void GenocideProcesses(void *a_argument);
	void KillProcess(void *a_argument);

	void ExecuteProcess(void *a_argument);

protected :
	CControlManager();
	~CControlManager(){}

private :
	static CControlManager *m_instance;

	CLoginDlg *m_loginDlg;
	BOOL m_restraint;	//사용자 제한을 걸고 있는지 풀었는지 여부.

	void ShowLoginWindow();
	void HideLoginWindow();
};

#endif
