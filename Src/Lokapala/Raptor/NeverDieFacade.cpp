/**@file	NeverDieFacade.cpp
 * @brief	NDM의 Facade의 멤버함수 구현
 * author	siva
 */

#include "stdafx.h"
#include "NeverDieFacade.h"
#include "APIHookingManager.h"
#include "AutoExecuteManager.h"

/**@brief	빌어먹을 윈도우 기본 디버거를 막기 위한 최악의 코드의 시작ㅡㅜ 전역변수라니!
 */
BYTE defaultDebugger[512];
DWORD defaultDebuggerLength = MAX_PATH;
/**@brief	어떤 경우에도 랩터가 죽지 않게 만든다.\n
 *			내부적으로 글로벌 api 후킹으로 TerminateProcess를 후킹하고, 컴퓨터 부팅 시 자동 실행이 되도록 레지스트리를 만진 후,
 *			레지스트리 접근을 막고, WM_CLOSE 등의 종료 메세지들에 대응한다.
 */
void CNeverDieFacade::StartNeverDie()
{
	m_state = true;
	CAPIHookingManager::Instance()->StartAPIHooking();
	CAutoExecuteManager::Instance()->SetAutoExecute();

	//빌어먹을 윈도우 기본 디버거를 막기 위한 최악의 코드ㅡㅜ 레지스트리 값을 건든다. 추후, 반드시 여길 수정할 것.
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


/**@brief	랩터가 죽을 수 있게 만든다.\n
 */
void CNeverDieFacade::StopNeverDie()
{
	m_state = false;
	CAPIHookingManager::Instance()->StopAPIHooking();
	CAutoExecuteManager::Instance()->ClearAutoExecute();

	//빌어먹을 윈도우 기본 디버거를 막기 위한 최악의 코드ㅡㅜ 레지스트리 값을 복구한다. 추후, 반드시 여길 수정할 것.
	HKEY hDebugRegKey;
	if( RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug"),
		0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &hDebugRegKey, 0) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("fail!!"));
	}
	RegSetValueEx(hDebugRegKey, _T("Debugger"), 0, REG_SZ, (const BYTE*)defaultDebugger, defaultDebuggerLength);
	RegCloseKey(hDebugRegKey);
}


/**@brief	현재 랩터가 죽어도 되는지 안되는지를 리턴값을 통해 알려준다.
 * @return	죽어선 안된다면 true, 죽어도 된다면 false를 리턴한다.
 */
bool CNeverDieFacade::GetNeverDieState()
{
	return m_state;
}
