/**@file	APIHookExport.h
 * @brief	API 글로벌 후킹을 위한 dll로부터 함수를 불러들인다.
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