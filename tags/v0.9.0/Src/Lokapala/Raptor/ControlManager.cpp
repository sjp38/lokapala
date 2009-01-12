/**@file	ControlManager.cpp
 * @brief	CControlManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "ControlManager.h"

#include "Psapi.h"


/**@brief	������. �α��� ���̾�α׸� �����ϰ� ��ġ�� ��´�.
 */
CControlManager::CControlManager()
{
	m_loginDlg = new CLoginDlg();
	m_loginDlg->Create(IDD_LOGIN_DIALOG);
	int screenx = GetSystemMetrics(SM_CXSCREEN);
	int screeny = GetSystemMetrics(SM_CYSCREEN);
	m_loginDlg->MoveWindow(0,0,screenx, screeny);
	
	::SetWindowPos(m_loginDlg->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);	//�����츦 �ֻ����� ��ġ��Ų��.
	CCBFMediator::Instance()->SetLoginDlg(m_loginDlg);
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
	CString message = _T("violent login");
	CCBFMediator::Instance()->Notify(&message);
	//AfxMessageBox(_T("violent login!"));
}

/**@brief	������ ����ڸ� �α׾ƿ� ��Ų��.
 */
void CControlManager::Logout(void *a_argument)
{
	CString message = _T("violent logout : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);
	CCBFMediator::Instance()->TrySuicide();
}

/**@brief	��ǻ�͸� �����Ų��. NT �迭 ����.
 */
void CControlManager::Shutdown(void *a_argument)
{
	CString message = _T("violent shutdown : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);

	HANDLE h_token;
	TOKEN_PRIVILEGES privilege_info;

	// ���� ���μ����� ���Ѱ� ���õ� ������ �����ϱ� ���� ��ū������ ����.
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &h_token) ) 
	{
		return;
	}

	// ���� ���μ����� SE_SHUTDOWN_NAME ������ ����Ҽ� �ֵ��� �����Ѵ�.
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privilege_info.Privileges[0].Luid);
	privilege_info.PrivilegeCount = 1;
	privilege_info.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// ������ ������ ������ �����Ѵ�.
	AdjustTokenPrivileges(h_token, FALSE, &privilege_info, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if(GetLastError() != ERROR_SUCCESS)
	{
		return;
	}
	ExitWindowsEx(EWX_FORCE | EWX_POWEROFF, 0);
}

/**@brief	��ǻ�͸� �����ý�Ų��. NT �迭 ����.
 */
void CControlManager::Reboot(void *a_argument)
{
	CString message = _T("violent reboot : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);

	HANDLE h_token;
	TOKEN_PRIVILEGES privilege_info;

	// ���� ���μ����� ���Ѱ� ���õ� ������ �����ϱ� ���� ��ū������ ����.
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &h_token) ) 
	{
		return;
	}

	// ���� ���μ����� SE_SHUTDOWN_NAME ������ ����Ҽ� �ֵ��� �����Ѵ�.
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privilege_info.Privileges[0].Luid);
	privilege_info.PrivilegeCount = 1;
	privilege_info.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// ������ ������ ������ �����Ѵ�.
	AdjustTokenPrivileges(h_token, FALSE, &privilege_info, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if(GetLastError() != ERROR_SUCCESS)
	{
		return;
	}
	ExitWindowsEx(EWX_FORCE | EWX_REBOOT, 0);
}

/**@brief	����ǰ� �ִ� ��� ���μ����� �����Ų��.
 */
void CControlManager::GenocideProcesses(void *a_argument)
{
	CString message = _T("violent genocide : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);

	DWORD runprocess[512], cb, nProcesses;
	unsigned int i;
	EnumProcesses(runprocess,sizeof(runprocess),&cb);	//���� �������� ���μ����� ���´�.
	nProcesses = cb/sizeof(DWORD);

	for(i=0;i<nProcesses;i++) {
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,runprocess[i]);
		if(NULL!=hProcess) {
			TerminateProcess(hProcess, NULL);
		}
		CloseHandle(hProcess);
	}
}

/**@brief	Ư�� ���μ����� �����Ų��.
 * @param	a_processName	�����Ű���� �ϴ� ���μ����� �̸�
 */
void CControlManager::KillProcess(void *a_argument)
{
	CString message = _T("violent kill : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);

	CString processName = *(CString *)a_argument;

	DWORD runprocess[512], cb, nProcesses;
	unsigned int i;
	EnumProcesses(runprocess,sizeof(runprocess),&cb);	//���� �������� ���μ����� ���´�.
	nProcesses = cb/sizeof(DWORD);

	WCHAR name[MAX_PATH];

	for(i=0;i<nProcesses;i++) {
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,runprocess[i]);
		if(NULL!=hProcess) {
			HMODULE hMod;
			DWORD cbNeed;

			if(EnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeed)) {
				GetModuleBaseName(hProcess,hMod,name,sizeof(WCHAR)*MAX_PATH);

				CString findedProcessName = name;
				if( findedProcessName.Find(processName) != -1 )
				{
					TerminateProcess(hProcess, NULL);
				}				
			}
			
		}
		CloseHandle(hProcess);
	}
}

/**@brief	Ư�� ���μ����� �����Ų��.
 * @param	a_processName	�����ϰ��� �ϴ� ���μ����� �̸�
 */
void CControlManager::ExecuteProcess(void *a_argument)
{
	CString message = _T("violent execute : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);

	CString command = *(CString *)a_argument;
	int tokenIndex = 0;
	CString processName = command.Tokenize(_T(" "), tokenIndex);
	CString parameter = command.Tokenize(_T(" "), tokenIndex);

	SHELLEXECUTEINFO SEInfo;

    memset( &SEInfo, 0, sizeof(SEInfo));
    SEInfo.cbSize = sizeof(SHELLEXECUTEINFO);

    SEInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	SEInfo.lpFile = processName.GetBuffer();
	SEInfo.lpParameters = parameter.GetBuffer();
	SEInfo.lpVerb = _T("open");
    SEInfo.nShow = SW_SHOWNORMAL;

    ShellExecuteEx(&SEInfo);
}