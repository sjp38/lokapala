/**@file	ControlManager.h
 * @brief	CControlManager Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef CONTROL_MANAGER_H
#define CONTROL_MANAGER_H

#include "LoginDlg.h"

/**@ingroup	GroupCTM
 * @class	CControlManager
 * @brief	������� ����, ���� ����, Ư��/��ü ���μ��� ����, ��ǻ�� ���� shut down, Ư�� ���μ��� ���� ���� ����� ��Ʈ���� �Ѵ�.
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
	
	void Shutdown(void *a_message);
	void Reboot(void *a_message);

	void GenocideProcesses(void *a_message);
	void KillProcess(void *a_processName);

	void ExecuteProcess(void *a_processName);

protected :
	CControlManager();
	~CControlManager(){}

private :
	static CControlManager *m_instance;

	CLoginDlg *m_loginDlg;
	BOOL m_restraint;	//����� ������ �ɰ� �ִ��� Ǯ������ ����.

	void ShowLoginWindow();
	void HideLoginWindow();
};

#endif