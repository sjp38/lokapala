/**@file	ProcessorObserver.cpp
 * @brief	윈도우를 생성하며 실행되는 프로세스를 알아내 그 이름을 알려주는 dll
 * @author	siva
 */

#include <windows.h>
#include "Psapi.h"

#include <WindowsX.h>
#include <tchar.h>
#include <stdio.h>


//export 선언자 디파인
extern "C" __declspec(dllexport)
BOOL WINAPI ObserveRunningProcesses(BOOL fInstall, DWORD dwThreadId);


HHOOK g_hhook=NULL;

///////////////////////////////////////////////////////////////////////////////


/**@brief	후킹 프로세스. WM_CREATE메세지를 후킹했다면 현재 생성된 프로세스의 이름을 알아내 클라이언트에게 알려준다.
 */
static LRESULT WINAPI GetMsgProc(int code, WPARAM wParam, LPARAM lParam) {
	if(code==HSHELL_WINDOWCREATED) {	//새로운 윈도우가 생성되었다면
		DWORD runprocess[512], cb, nProcesses;
		unsigned int i;
		EnumProcesses(runprocess,sizeof(runprocess),&cb);	//현재 수행중인 프로세스를 확인
		nProcesses = cb/sizeof(DWORD);

		WCHAR names[MAX_PATH];

		for(i=nProcesses-1;i<nProcesses;i++) {
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,
				FALSE,runprocess[i]);
			if(NULL!=hProcess) {
				HMODULE hMod;
				DWORD cbNeed;
				
				if(EnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeed)) {
					GetModuleBaseName(hProcess,hMod,names,sizeof(WCHAR)*nProcesses);					

					//raptor의 윈도 핸들이 기록된 메모리 맵 파일 오픈
					HANDLE map = OpenFileMapping(FILE_MAP_READ,FALSE,_T("raptorSelfWindowHandle"));
					if(!map)
					{
						MessageBox(NULL,_T("file mapping object open fail!!"),_T("failure"),MB_OK);
					}
					HWND *hRaptorWnd;
					hRaptorWnd = (HWND *)MapViewOfFile(map,FILE_MAP_READ,0,0,0);	//메모리 맵 파일 리드


					COPYDATASTRUCT cds = {0,sizeof(WCHAR)*(wcslen(names)+1),names};					
					SendMessage( *hRaptorWnd, WM_COPYDATA,NULL, (LPARAM)&cds );
				}
			}
			CloseHandle(hProcess);
		}
	}
	return(CallNextHookEx(g_hhook, code, wParam, lParam));
}


/**@brief	해당 메모리 주소 사용하는 모듈의 핸들 리턴
 */
static HMODULE ModuleFromAddress(PVOID pv) {
   MEMORY_BASIC_INFORMATION mbi;
   //주소 정보를 획득한 후 주소정보 중 Base 값(모듈의 핸들)을 리턴.
   return((VirtualQuery(pv, &mbi, sizeof(mbi)) != 0) 
      ? (HMODULE) mbi.AllocationBase : NULL);
}


/**@brief 클라이언트 프로그램에서 임포트하는 함수. 여기서 전역 메세지 훅을 건다.
 */
BOOL WINAPI ObserveRunningProcesses(BOOL fInstall, DWORD dwThreadId) {

   BOOL fOk;

   if (fInstall) {	//훅을 설치하고자 하는 경우
	   if(g_hhook==NULL) {
		   
		   // GetMsgProc으로 전역 윈도 훅 설치
		   g_hhook = SetWindowsHookEx(WH_SHELL, GetMsgProc, 
			   ModuleFromAddress(ObserveRunningProcesses), dwThreadId);
		   fOk = (g_hhook != NULL);
	   }
   } else {		//훅을 해제하고자 하는 경우
	   if(g_hhook!=NULL) {
		   fOk = UnhookWindowsHookEx(g_hhook);	//윈도 훅 해제
		   g_hhook = NULL;	//훅 핸들 초기화
	   }
   }

   return(fOk);
}
