/**@file	AutoExecuteManager.cpp
 * @brief	CAutoExecuteManager의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "AutoExecuteManager.h"

/**@brief	생성자\n
			부팅 시 자동 실행 설정, regedit 방지를 설정 할 수 있는 위치의 레지스트리를 연다.
 */
CAutoExecuteManager::CAutoExecuteManager()
{
	m_hautoExec = OpenRegistry(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	m_hregeditEnable = OpenRegistry(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"));
}

/**@brief	소멸자\n
 *			레지스트리 키를 닫는다.
 */
CAutoExecuteManager::~CAutoExecuteManager()
{
	RegCloseKey(m_hautoExec);
	RegCloseKey(m_hregeditEnable);
}

/**@brief	특정 위치 레지스트리를 열고 그 키를 반납한다.
 * @param	a_path	열고자 하는 레지스트리의 경로
 * @return	연 레지스트리 키
 */
HKEY CAutoExecuteManager::OpenRegistry(CString a_path)
{
	HKEY hKey;
	if( RegCreateKeyEx(HKEY_CURRENT_USER, a_path,
		0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &hKey, 0) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("registry open failed!!"));
	}
	return hKey;
}

/**@brief	컴퓨터 부팅 시 자동으로 실행되도록 레지스트리를 설정한다.\n
 *			사용자의 레지스트리 임의 수정을 막기 위해 regedit을 사용할 수 없게 만든다.
 */
void CAutoExecuteManager::SetAutoExecute()
{
	SetRegEditDisable();

	WCHAR selfPath[MAX_PATH];
	GetModuleFileName(NULL, selfPath, MAX_PATH);
	
	if(RegSetValueEx(m_hautoExec, _T("LokapalaRaptor"), 0, REG_SZ, (const BYTE *)selfPath, wcslen(selfPath)*2+1) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("registry record fail!!"));
	}
}

/**@brief	컴퓨터 부팅 시 자동으로 실행되지 않도록 레지스트리를 재설정한다.
 */
void CAutoExecuteManager::ClearAutoExecute()
{
	SetRegEditAvailable();
	
	long result = RegDeleteValue(m_hautoExec, _T("LokapalaRaptor"));
	if(result != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("registry value delete fail!!"));
	}
}


/**@brief	regedit를 사용 가능하게 만든다.
 */
void CAutoExecuteManager::SetRegEditAvailable()
{
	DWORD regeditDisable = 0;
	RegSetValueEx(m_hregeditEnable, _T("DisableRegistryTools"), 0, REG_DWORD, (const BYTE*)&regeditDisable, sizeof(DWORD));
}

/**@brief	regedit를 사용 불가능하게 만든다.
 */
void CAutoExecuteManager::SetRegEditDisable()
{
	DWORD regeditAvailable = 1;
	RegSetValueEx(m_hregeditEnable, _T("DisableRegistryTools"), 0, REG_DWORD, (const unsigned char *)&regeditAvailable, sizeof(DWORD));
}