/**@file	NeverDieFacade.cpp
 * @brief	NDM�� Facade�� ����Լ� ����
 * author	siva
 */

#include "stdafx.h"
#include "NeverDieFacade.h"
#include "APIHookingManager.h"
#include "AutoExecuteManager.h"

/**@brief	������� ������ �⺻ ����Ÿ� ���� ���� �־��� �ڵ��� ���ۤѤ� �����������!
 */
BYTE defaultDebugger[512];
DWORD defaultDebuggerLength = MAX_PATH;
/**@brief	� ��쿡�� ���Ͱ� ���� �ʰ� �����.\n
 *			���������� �۷ι� api ��ŷ���� TerminateProcess�� ��ŷ�ϰ�, ��ǻ�� ���� �� �ڵ� ������ �ǵ��� ������Ʈ���� ���� ��,
 *			������Ʈ�� ������ ����, WM_CLOSE ���� ���� �޼����鿡 �����Ѵ�.
 */
void CNeverDieFacade::StartNeverDie()
{
	m_state = true;
	CAPIHookingManager::Instance()->StartAPIHooking();
	CAutoExecuteManager::Instance()->SetAutoExecute();

	//������� ������ �⺻ ����Ÿ� ���� ���� �־��� �ڵ�Ѥ� ������Ʈ�� ���� �ǵ��. ����, �ݵ�� ���� ������ ��.
	HKEY hDebugRegKey;
	if( RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug"),
		0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &hDebugRegKey, 0) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("fail!!"));
	}
	DWORD type = REG_SZ;
	RegQueryValueEx(hDebugRegKey, _T("Debugger"), 0, &type, (LPBYTE)defaultDebugger, (LPDWORD)&defaultDebuggerLength);
	CString value = _T("");
	RegSetValueEx(hDebugRegKey, _T("Debugger"), 0, REG_SZ, (const BYTE*)&value, 0);
	RegCloseKey(hDebugRegKey);
}


/**@brief	���Ͱ� ���� �� �ְ� �����.\n
 */
void CNeverDieFacade::StopNeverDie()
{
	m_state = false;
	CAPIHookingManager::Instance()->StopAPIHooking();
	CAutoExecuteManager::Instance()->ClearAutoExecute();

	//������� ������ �⺻ ����Ÿ� ���� ���� �־��� �ڵ�Ѥ� ������Ʈ�� ���� �����Ѵ�. ����, �ݵ�� ���� ������ ��.
	HKEY hDebugRegKey;
	if( RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug"),
		0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &hDebugRegKey, 0) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("fail!!"));
	}
	RegSetValueEx(hDebugRegKey, _T("Debugger"), 0, REG_SZ, (const BYTE*)defaultDebugger, defaultDebuggerLength);
	RegCloseKey(hDebugRegKey);
}


/**@brief	���� ���Ͱ� �׾ �Ǵ��� �ȵǴ����� ���ϰ��� ���� �˷��ش�.
 * @return	�׾ �ȵȴٸ� true, �׾ �ȴٸ� false�� �����Ѵ�.
 */
bool CNeverDieFacade::GetNeverDieState()
{
	return m_state;
}