/**@file	APIHookExport.h
 * @brief	API �۷ι� ��ŷ�� ���� dll�κ��� �Լ��� �ҷ����δ�.
 * @author	siva
 */

#ifndef API_HOOK_EXPORT_H
#define API_HOOK_EXPORT_H


#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <windowsx.h>
#include <tchar.h>


#define APILIBFUNCTION extern "C" __declspec(dllimport)



///////////////////////////////////////////////////////////////////////////////


APILIBFUNCTION BOOL WINAPI TerminateProcessGlobalHook(BOOL fInstall, 
   DWORD dwThreadId);



#endif