/**@file	ProcessorObserver.cpp
 * @brief	�����츦 �����ϸ� ����Ǵ� ���μ����� �˾Ƴ� �� �̸��� �˷��ִ� dll
 * @author	siva
 */

#include <windows.h>
#include "Psapi.h"

#include <WindowsX.h>
#include <tchar.h>
#include <stdio.h>


//export ������ ������
extern "C" __declspec(dllexport)
BOOL WINAPI ObserveRunningProcesses(BOOL fInstall, DWORD dwThreadId);


HHOOK g_hhook=NULL;

///////////////////////////////////////////////////////////////////////////////


/**@brief	��ŷ ���μ���. WM_CREATE�޼����� ��ŷ�ߴٸ� ���� ������ ���μ����� �̸��� �˾Ƴ� Ŭ���̾�Ʈ���� �˷��ش�.
 */
static LRESULT WINAPI GetMsgProc(int code, WPARAM wParam, LPARAM lParam) {
	if(code==HSHELL_WINDOWCREATED) {	//���ο� �����찡 �����Ǿ��ٸ�
		DWORD runprocess[512], cb, nProcesses;
		unsigned int i;
		EnumProcesses(runprocess,sizeof(runprocess),&cb);	//���� �������� ���μ����� Ȯ��
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

					//raptor�� ���� �ڵ��� ��ϵ� �޸� �� ���� ����
					HANDLE map = OpenFileMapping(FILE_MAP_READ,FALSE,_T("raptorSelfWindowHandle"));
					if(!map)
					{
						MessageBox(NULL,_T("file mapping object open fail!!"),_T("failure"),MB_OK);
					}
					HWND *hRaptorWnd;
					hRaptorWnd = (HWND *)MapViewOfFile(map,FILE_MAP_READ,0,0,0);	//�޸� �� ���� ����


					COPYDATASTRUCT cds = {0,sizeof(WCHAR)*(wcslen(names)+1),names};					
					SendMessage( *hRaptorWnd, WM_COPYDATA,NULL, (LPARAM)&cds );
				}
			}
			CloseHandle(hProcess);
		}
	}
	return(CallNextHookEx(g_hhook, code, wParam, lParam));
}


/**@brief	�ش� �޸� �ּ� ����ϴ� ����� �ڵ� ����
 */
static HMODULE ModuleFromAddress(PVOID pv) {
   MEMORY_BASIC_INFORMATION mbi;
   //�ּ� ������ ȹ���� �� �ּ����� �� Base ��(����� �ڵ�)�� ����.
   return((VirtualQuery(pv, &mbi, sizeof(mbi)) != 0) 
      ? (HMODULE) mbi.AllocationBase : NULL);
}


/**@brief Ŭ���̾�Ʈ ���α׷����� ����Ʈ�ϴ� �Լ�. ���⼭ ���� �޼��� ���� �Ǵ�.
 */
BOOL WINAPI ObserveRunningProcesses(BOOL fInstall, DWORD dwThreadId) {

   BOOL fOk;

   if (fInstall) {	//���� ��ġ�ϰ��� �ϴ� ���
	   if(g_hhook==NULL) {
		   
		   // GetMsgProc���� ���� ���� �� ��ġ
		   g_hhook = SetWindowsHookEx(WH_SHELL, GetMsgProc, 
			   ModuleFromAddress(ObserveRunningProcesses), dwThreadId);
		   fOk = (g_hhook != NULL);
	   }
   } else {		//���� �����ϰ��� �ϴ� ���
	   if(g_hhook!=NULL) {
		   fOk = UnhookWindowsHookEx(g_hhook);	//���� �� ����
		   g_hhook = NULL;	//�� �ڵ� �ʱ�ȭ
	   }
   }

   return(fOk);
}
