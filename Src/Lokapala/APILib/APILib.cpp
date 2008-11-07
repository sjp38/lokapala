//#############################################################################
//		 2008.9. coded by siva.		API ��ŷ ���̺귯�� ���� DLL.
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


//export ������ ������
#define APILIBFUNCTION extern "C" __declspec(dllexport)

APILIBFUNCTION BOOL WINAPI TerminateProcessGlobalHook(BOOL fInstall, 
   DWORD dwThreadId);




///////////////////////////////////////////////////////////////////////////////


// Prototypes for the hooked functions
typedef BOOL (WINAPI *PFNTERMINATEPROCESS)(HANDLE hProcess, UINT uExitCode);


// We need to reference these variables before we create them.
extern CAPIHook g_TerminateProcess;


///////////////////////////////////////////////////////////////////////////////

//TerminateProcess ��ü�Լ�
BOOL WINAPI Hook_TerminateProcess( HANDLE hProcess, UINT uExitCode ) {
    HANDLE outProcess;
	//outProcess �ڵ�� ���� ������ �ڵ� ����.
    BOOL res = DuplicateHandle(GetCurrentProcess(), hProcess, GetCurrentProcess(),
		&outProcess,PROCESS_ALL_ACCESS, FALSE, 0);

    if(res) {
        //outProcess�� ���ϴ� ���μ��� ������ ��� �����ü� �ִ�.

		//���� ���̷��� ���μ����� ���
        char szFileName[ MAX_PATH ] ;
        HMODULE hMods[1024];
        DWORD cbNeeded; 

		//EnumProcessModules : Retrieves a handle for each module in the specified process
        if(EnumProcessModules(outProcess, hMods, sizeof(hMods), &cbNeeded)) {
			//GetModuleFileNameEx : Retrieves the fully-qualified path for the file
			//containing the specified module
            GetModuleFileNameEx(outProcess, NULL, szFileName, sizeof( szFileName ));
            //szFileName�� ����Ǵ� ���μ����� �������� Ǯ �н�
			
			//raptor�� �����ΰ� ��ϵ� �޸� �� ���� ����
			HANDLE map = OpenFileMapping(FILE_MAP_READ,FALSE,"raptorSelfPath");
			if(!map)
			{
				MessageBox(NULL,"file mapping object open fail!!","failure",MB_OK);
			}
			char *selfPath = (char *)malloc(sizeof(char)*MAX_PATH);
			selfPath = (char *)MapViewOfFile(map,FILE_MAP_READ,0,0,0);	//�޸� �� ���� ����

			//MessageBox(NULL,szFileName,"name of target",MB_OK);
			//MessageBox(NULL,selfPath,"name of client",MB_OK);

			if(strcmp(selfPath,szFileName)==0)
			{
				CloseHandle(outProcess);
				return FALSE;
			}
        }
    }
	//������ TerminateProcess ȣ��.
    return TerminateProcess( hProcess, uExitCode );
}


///////////////////////////////////////////////////////////////////////////////


// TerminateProcess, MessageBoxW ��ü ����, ��ŷ.
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
HHOOK g_hhook=NULL;	//�� �ɷ��ִ��� �ƴ��� �÷���.

///////////////////////////////////////////////////////////////////////////////


//���� ������ ��. �����Ӹ� �����ϰ� ���ٸ� ���� ������ �ʰ� �ǵ����ش�.
static LRESULT WINAPI GetMsgProc(int code, WPARAM wParam, LPARAM lParam) {
	
	return(CallNextHookEx(g_hhook, code, wParam, lParam));
}


///////////////////////////////////////////////////////////////////////////////


//�ش� �޸� �ּ� ����ϴ� ����� �ڵ� ����
static HMODULE ModuleFromAddress(PVOID pv) {
   MEMORY_BASIC_INFORMATION mbi;
   //�ּ� ������ ȹ���� �� �ּ����� �� Base ��(����� �ڵ�)�� ����.
   return((VirtualQuery(pv, &mbi, sizeof(mbi)) != 0) 
      ? (HMODULE) mbi.AllocationBase : NULL);
}


///////////////////////////////////////////////////////////////////////////////

//App���� ����Ʈ�ϴ� �Լ�. �̸� �������� ���� api ���� �Ǵ�.
BOOL WINAPI TerminateProcessGlobalHook(BOOL fInstall, DWORD dwThreadId) {

   BOOL fOk;

   if (fInstall) {	//���� ��ġ�ϰ��� �ϴ� ���
	   if(g_hhook==NULL) {	//�̸� ��ġ�Ǿ� ���� �ʴٸ� ��ġ�Ѵ�.
		   //chASSERT(g_hhook == NULL); //���ļ� ��ġ���� �ʴ´�.

		   // GetMsgProc���� ���� ���� �� ��ġ
		   g_hhook = SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, 
			   ModuleFromAddress(TerminateProcessGlobalHook), dwThreadId);
		   fOk = (g_hhook != NULL);
	   }
   } else {		//���� �����ϰ��� �ϴ� ���
	   if(g_hhook!=NULL) {	//�̸� ��ġ�Ǿ� �ִٸ� �����Ѵ�.
		   //chASSERT(g_hhook != NULL); // �̸� ��ġ�Ǿ� ���� ���� ����
		   fOk = UnhookWindowsHookEx(g_hhook);	//���� �� ����
		   g_hhook = NULL;	//�� �ڵ� �ʱ�ȭ
	   }
	}

   return(fOk);
}


//////////////////////////////// End of File //////////////////////////////////
