//#############################################################################
//		 2008.9. coded by siva.		API 후킹 라이브러리 제공 DLL.
//			reference document : Jeffery Ritcher's code
//#############################################################################

#include <windows.h>
#include "Psapi.h"

//#define WINVER       0x0500
#include "CmnHdr.h"
#include <WindowsX.h>
#include <tchar.h>
#include <stdio.h>
#include "APIHook.h"


//export 선언자 디파인
#define APILIBFUNCTION extern "C" __declspec(dllexport)

APILIBFUNCTION BOOL WINAPI TerminateProcessGlobalHook(BOOL fInstall, 
   DWORD dwThreadId);




///////////////////////////////////////////////////////////////////////////////


// Prototypes for the hooked functions
typedef BOOL (WINAPI *PFNTERMINATEPROCESS)(HANDLE hProcess, UINT uExitCode);


// We need to reference these variables before we create them.
extern CAPIHook g_TerminateProcess;


///////////////////////////////////////////////////////////////////////////////

//TerminateProcess 대체함수
BOOL WINAPI Hook_TerminateProcess( HANDLE hProcess, UINT uExitCode ) {
    HANDLE outProcess;
	//outProcess 핸들로 권한 높여서 핸들 복사.
    BOOL res = DuplicateHandle(GetCurrentProcess(), hProcess, GetCurrentProcess(),
		&outProcess,PROCESS_ALL_ACCESS, FALSE, 0);

    if(res) {
        //outProcess로 원하는 프로세스 정보를 모두 가져올수 있다.

		//현재 죽이려는 프로세스의 경로
        char szFileName[ MAX_PATH ] ;
        HMODULE hMods[1024];
        DWORD cbNeeded; 

		//EnumProcessModules : Retrieves a handle for each module in the specified process
        if(EnumProcessModules(outProcess, hMods, sizeof(hMods), &cbNeeded)) {
			//GetModuleFileNameEx : Retrieves the fully-qualified path for the file
			//containing the specified module
            GetModuleFileNameEx(outProcess, NULL, szFileName, sizeof( szFileName ));
            //szFileName이 종료되는 프로세스의 실행파일 풀 패스
			
			//raptor의 실행경로가 기록된 메모리 맵 파일 오픈
			HANDLE map = OpenFileMapping(FILE_MAP_READ,FALSE,"raptorSelfPath");
			if(!map)
			{
				MessageBox(NULL,"file mapping object open fail!!","failure",MB_OK);
			}
			char *selfPath = (char *)malloc(sizeof(char)*MAX_PATH);
			selfPath = (char *)MapViewOfFile(map,FILE_MAP_READ,0,0,0);	//메모리 맵 파일 리드

			//MessageBox(NULL,szFileName,"name of target",MB_OK);
			//MessageBox(NULL,selfPath,"name of client",MB_OK);

			if(strcmp(selfPath,szFileName)==0)
			{
				CloseHandle(outProcess);
				return FALSE;
			}
        }
    }
	//원래의 TerminateProcess 호출.
    return TerminateProcess( hProcess, uExitCode );
}


///////////////////////////////////////////////////////////////////////////////


// TerminateProcess, MessageBoxW 객체 생성, 후킹.
CAPIHook g_TerminateProcess("Kernel32.dll", "TerminateProcess", 
   (PROC) Hook_TerminateProcess, TRUE);

/*
// Since we do DLL injection with Windows' hooks, we need to save the hook
// handle in a shared memory block (Windows 2000 actually doesn't need this)
#pragma data_seg("Shared")
HHOOK g_hhook = NULL;
#pragma data_seg()
#pragma comment(linker, "/Section:Shared,rws")
*/
HHOOK g_hhook=NULL;	//훅 걸려있는지 아닌지 플래그.

///////////////////////////////////////////////////////////////////////////////


//전역 윈도우 훅. 움직임만 감지하고 별다른 행위 취하지 않고 되돌려준다.
static LRESULT WINAPI GetMsgProc(int code, WPARAM wParam, LPARAM lParam) {
	
	return(CallNextHookEx(g_hhook, code, wParam, lParam));
}


///////////////////////////////////////////////////////////////////////////////


//해당 메모리 주소 사용하는 모듈의 핸들 리턴
static HMODULE ModuleFromAddress(PVOID pv) {
   MEMORY_BASIC_INFORMATION mbi;
   //주소 정보를 획득한 후 주소정보 중 Base 값(모듈의 핸들)을 리턴.
   return((VirtualQuery(pv, &mbi, sizeof(mbi)) != 0) 
      ? (HMODULE) mbi.AllocationBase : NULL);
}


///////////////////////////////////////////////////////////////////////////////

//App에서 임포트하는 함수. 이를 시작으로 전역 api 훅을 건다.
BOOL WINAPI TerminateProcessGlobalHook(BOOL fInstall, DWORD dwThreadId) {

   BOOL fOk;

   if (fInstall) {	//훅을 설치하고자 하는 경우
	   if(g_hhook==NULL) {	//미리 설치되어 있지 않다면 설치한다.
		   //chASSERT(g_hhook == NULL); //겹쳐서 설치하진 않는다.

		   // GetMsgProc으로 전역 윈도 훅 설치
		   g_hhook = SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, 
			   ModuleFromAddress(TerminateProcessGlobalHook), dwThreadId);
		   fOk = (g_hhook != NULL);
	   }
   } else {		//훅을 해제하고자 하는 경우
	   if(g_hhook!=NULL) {	//미리 설치되어 있다면 해제한다.
		   //chASSERT(g_hhook != NULL); // 미리 설치되어 있을 때만 해제
		   fOk = UnhookWindowsHookEx(g_hhook);	//윈도 훅 해제
		   g_hhook = NULL;	//훅 핸들 초기화
	   }
	}

   return(fOk);
}


//////////////////////////////// End of File //////////////////////////////////
