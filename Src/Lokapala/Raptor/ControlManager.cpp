/**@file	ControlManager.cpp
 * @brief	CControlManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "ControlManager.h"

#include "Psapi.h"


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
	CCBFMediator::Instance()->SetLoginDlg(m_loginDlg);
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
	CString message = _T("violent login");
	CCBFMediator::Instance()->Notify(&message);
	//AfxMessageBox(_T("violent login!"));
}

/**@brief	강제로 사용자를 로그아웃 시킨다.
 */
void CControlManager::Logout(void *a_argument)
{
	CString message = _T("violent logout : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);
	CCBFMediator::Instance()->TrySuicide();
}

/**@brief	컴퓨터를 종료시킨다. NT 계열 전용.
 */
void CControlManager::Shutdown(void *a_argument)
{
	CString message = _T("violent shutdown : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);

	HANDLE h_token;
	TOKEN_PRIVILEGES privilege_info;

	// 현재 프로세스의 권한과 관련된 정보를 변경하기 위해 토큰정보를 연다.
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &h_token) ) 
	{
		return;
	}

	// 현재 프로세스가 SE_SHUTDOWN_NAME 권한을 사용할수 있도록 설정한다.
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privilege_info.Privileges[0].Luid);
	privilege_info.PrivilegeCount = 1;
	privilege_info.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// 지정한 값으로 권한을 조정한다.
	AdjustTokenPrivileges(h_token, FALSE, &privilege_info, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if(GetLastError() != ERROR_SUCCESS)
	{
		return;
	}
	ExitWindowsEx(EWX_FORCE | EWX_POWEROFF, 0);
}

/**@brief	컴퓨터를 리부팅시킨다. NT 계열 전용.
 */
void CControlManager::Reboot(void *a_argument)
{
	CString message = _T("violent reboot : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);

	HANDLE h_token;
	TOKEN_PRIVILEGES privilege_info;

	// 현재 프로세스의 권한과 관련된 정보를 변경하기 위해 토큰정보를 연다.
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &h_token) ) 
	{
		return;
	}

	// 현재 프로세스가 SE_SHUTDOWN_NAME 권한을 사용할수 있도록 설정한다.
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privilege_info.Privileges[0].Luid);
	privilege_info.PrivilegeCount = 1;
	privilege_info.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// 지정한 값으로 권한을 조정한다.
	AdjustTokenPrivileges(h_token, FALSE, &privilege_info, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if(GetLastError() != ERROR_SUCCESS)
	{
		return;
	}
	ExitWindowsEx(EWX_FORCE | EWX_REBOOT, 0);
}

/**@brief	실행되고 있는 모든 프로세스를 종료시킨다.
 */
void CControlManager::GenocideProcesses(void *a_argument)
{
	CString message = _T("violent genocide : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);

	DWORD runprocess[512], cb, nProcesses;
	unsigned int i;
	EnumProcesses(runprocess,sizeof(runprocess),&cb);	//현재 수행중인 프로세스를 얻어온다.
	nProcesses = cb/sizeof(DWORD);

	for(i=0;i<nProcesses;i++) {
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,runprocess[i]);
		if(NULL!=hProcess) {
			TerminateProcess(hProcess, NULL);
		}
		CloseHandle(hProcess);
	}
}

/**@brief	특정 프로세스를 종료시킨다.
 * @param	a_processName	종료시키고자 하는 프로세스의 이름
 */
void CControlManager::KillProcess(void *a_argument)
{
	CString message = _T("violent kill : ") + *(CString *)a_argument;
	CCBFMediator::Instance()->Notify(&message);

	CString processName = *(CString *)a_argument;

	DWORD runprocess[512], cb, nProcesses;
	unsigned int i;
	EnumProcesses(runprocess,sizeof(runprocess),&cb);	//현재 수행중인 프로세스를 얻어온다.
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

/**@brief	특정 프로세스를 실행시킨다.
 * @param	a_processName	실행하고자 하는 프로세스의 이름
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
