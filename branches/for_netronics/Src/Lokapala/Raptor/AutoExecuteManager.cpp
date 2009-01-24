/**@file	AutoExecuteManager.cpp
 * @brief	CAutoExecuteManager�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "AutoExecuteManager.h"

/**@brief	������\n
			���� �� �ڵ� ���� ����, regedit ������ ���� �� �� �ִ� ��ġ�� ������Ʈ���� ����.
 */
CAutoExecuteManager::CAutoExecuteManager()
{
	m_hautoExec = OpenRegistry(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	m_hregeditEnable = OpenRegistry(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"));
}

/**@brief	�Ҹ���\n
 *			������Ʈ�� Ű�� �ݴ´�.
 */
CAutoExecuteManager::~CAutoExecuteManager()
{
	RegCloseKey(m_hautoExec);
	RegCloseKey(m_hregeditEnable);
}

/**@brief	Ư�� ��ġ ������Ʈ���� ���� �� Ű�� �ݳ��Ѵ�.
 * @param	a_path	������ �ϴ� ������Ʈ���� ���
 * @return	�� ������Ʈ�� Ű
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

/**@brief	��ǻ�� ���� �� �ڵ����� ����ǵ��� ������Ʈ���� �����Ѵ�.\n
 *			������� ������Ʈ�� ���� ������ ���� ���� regedit�� ����� �� ���� �����.
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

/**@brief	��ǻ�� ���� �� �ڵ����� ������� �ʵ��� ������Ʈ���� �缳���Ѵ�.
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


/**@brief	regedit�� ��� �����ϰ� �����.
 */
void CAutoExecuteManager::SetRegEditAvailable()
{
	DWORD regeditDisable = 0;
	RegSetValueEx(m_hregeditEnable, _T("DisableRegistryTools"), 0, REG_DWORD, (const BYTE*)&regeditDisable, sizeof(DWORD));
}

/**@brief	regedit�� ��� �Ұ����ϰ� �����.
 */
void CAutoExecuteManager::SetRegEditDisable()
{
	DWORD regeditAvailable = 1;
	RegSetValueEx(m_hregeditEnable, _T("DisableRegistryTools"), 0, REG_DWORD, (const unsigned char *)&regeditAvailable, sizeof(DWORD));
}