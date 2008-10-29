/**@file	ControlManager.cpp
 * @brief	CControlManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "ControlManager.h"


/**@brief	������. �α��� ���̾�α׸� �����ϰ� ��ġ�� ��´�.
 */
CControlManager::CControlManager()
{
	m_loginDlg = new CLoginDlg();
	m_loginDlg->Create(IDD_LOGIN_DIALOG);
	int screenx = GetSystemMetrics(SM_CXSCREEN);
	int screeny = GetSystemMetrics(SM_CYSCREEN);
	m_loginDlg->MoveWindow(0,0,screenx, screeny);
	//::SetWindowPos(m_loginDlg->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);	//�����츦 �ֻ����� ��ġ��Ų��.
}

/**@brief	�α��� �����츦 ȭ�� �ֻ�ܿ� ȭ�� ũ��� ���̰� �Ѵ�.
 */
void CControlManager::ShowLoginWindow()
{
	m_loginDlg->ShowWindow(SW_SHOW);
}

/**@brief	�α��� �����츦 ������� �� ������� ��ǻ�� �̿� ������ �����Ѵ�.
 */
void CControlManager::HideLoginWindow()
{
	if(!m_restraint)
	{
		m_loginDlg->ShowWindow(SW_HIDE);
	}
}

/**@brief	������� ������ ��ǻ�� ����� �����Ѵ�.
 *			�α��� â�� ȭ�� �ֻ�ܿ� ȭ�� ũ��� ���̰� �� ������� ������ ��ǻ�� �̿��� �����Ѵ�.
 */
void CControlManager::RestraintUser()
{
	m_restraint = TRUE;
	ShowLoginWindow();
}

/**@brief	������� ������ ��ǻ�� ����� �����ϰ� �����.
 *			�α��� â�� ���ش�.
 */
void CControlManager::ReleaseUser()
{
	m_restraint = FALSE;
	HideLoginWindow();
}

/**@brief	������ ����ڸ� �α��� ��Ų��.
 */
void CControlManager::Login(void *a_userInfo)
{
	AfxMessageBox(_T("violent login!"));
}

/**@brief	������ ����ڸ� �α׾ƿ� ��Ų��.
 */
void CControlManager::Logout(void *a_message)
{
	AfxMessageBox(_T("violent logout!"));
	CCBFMediator::Instance()->TrySuicide();
}

/**@brief	��ǻ�͸� �����Ų��.
 */
void CControlManager::Shutdown(void *a_message)
{
	AfxMessageBox(_T("violent shutdown"));
}

/**@brief	��ǻ�͸� �����ý�Ų��.
 */
void CControlManager::Reboot(void *a_message)
{
	AfxMessageBox(_T("violent reboot!"));
}

/**@brief	����ǰ� �ִ� ��� ���μ����� �����Ų��.
 */
void CControlManager::GenocideProcesses(void *a_message)
{
	AfxMessageBox(_T("violent genocide!"));
}

/**@brief	Ư�� ���μ����� �����Ų��.
 * @param	a_processName	�����Ű���� �ϴ� ���μ����� �̸�
 */
void CControlManager::KillProcess(void *a_processName)
{
	AfxMessageBox(_T("violent kill!"));
}

/**@brief	Ư�� ���μ����� �����Ų��.
 * @param	a_processName	�����ϰ��� �ϴ� ���μ����� �̸�
 */
void CControlManager::ExecuteProcess(void *a_processName)
{
	AfxMessageBox(_T("violent execute!"));
}