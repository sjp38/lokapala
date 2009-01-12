/**@file	APIHookingManager.cpp
 * @brief	CAPIHookingManager 클래스의 멤버함수들을 구현
 * @author	siva
 */

#include "stdafx.h"
#include "APIHookingManager.h"
#include "APIHookExport.h"

/**@brief	자신의 실행 경로를 알아내서 메모리에 저장해 둔다.
 */
void CAPIHookingManager::WriteSelfPathToMemory()
{	
	WCHAR *selfPath = (WCHAR *)malloc(sizeof(WCHAR)*MAX_PATH);
	GetModuleFileName(NULL,selfPath,MAX_PATH);

	char *converted = (char *)malloc(sizeof(char)*MAX_PATH);

	m_map = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, sizeof(char)*MAX_PATH, _T("raptorSelfPath"));
	if(!m_map)
	{
		AfxMessageBox(_T("message map create fail!!"));
	}
	converted = (char *)MapViewOfFile(m_map, FILE_MAP_WRITE, 0, 0, 0);
	USES_CONVERSION;
	memcpy(converted, W2A(selfPath), MAX_PATH);
	
	free(selfPath);
}

/**@brief	APILib dll을 이용해 TerminateProcess를 글로벌 후킹한다.
 */
void CAPIHookingManager::StartAPIHooking()
{
	WriteSelfPathToMemory();
	TerminateProcessGlobalHook(true, 0);
}


/**@brief	APILib dll을 이용해 TerminateProcess의 글로벌 후킹을 해제한다.
 */
void CAPIHookingManager::StopAPIHooking()
{
	TerminateProcessGlobalHook(false, 0);
}