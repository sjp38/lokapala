/**@file	APIHookingManager.cpp
 * @brief	CAPIHookingManager Ŭ������ ����Լ����� ����
 * @author	siva
 */

#include "stdafx.h"
#include "APIHookingManager.h"
#include "APIHookExport.h"

/**@brief	�ڽ��� ���� ��θ� �˾Ƴ��� �޸𸮿� ������ �д�.
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

/**@brief	APILib dll�� �̿��� TerminateProcess�� �۷ι� ��ŷ�Ѵ�.
 */
void CAPIHookingManager::StartAPIHooking()
{
	WriteSelfPathToMemory();
	TerminateProcessGlobalHook(true, 0);
}


/**@brief	APILib dll�� �̿��� TerminateProcess�� �۷ι� ��ŷ�� �����Ѵ�.
 */
void CAPIHookingManager::StopAPIHooking()
{
	TerminateProcessGlobalHook(false, 0);
}