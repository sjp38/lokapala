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

		WCHAR names[MAX_PATH*128];

		for(i=nProcesses-1;i<nProcesses;i++) {
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,
				FALSE,runprocess[i]);
			if(NULL!=hProcess) {
				HMODULE hMod;
				DWORD cbNeed;
				
				if(EnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeed)) {
					GetModuleBaseName(hProcess,hMod,names+i*MAX_PATH,sizeof(WCHAR)*nProcesses);
					MessageBox(NULL,names+i*MAX_PATH,_T("ab"),MB_OK);
/*
					WCHAR sz[MAX_PATH];
					wsprintf(sz,"%s",names+i*MAX_PATH);					

					COPYDATASTRUCT cds = {0,lstrlenA(names+i*MAX_PATH)+1,sz};

					//SendMessage(FindWindow(NULL,TEXT("wndApp")),
					//	WM_COPYDATA,NULL,(LPARAM)&cds);
					SendMessage(FindWindow(NULL,TEXT("Admin Program - CLIENT")),
						WM_COPYDATA,NULL,(LPARAM)&cds);
					
					//char tem[MAX_PATH];
					//wsprintf(tem,"%d",FindWindow(NULL,TEXT("Admin Program - CLIENT")));
					//MessageBox(NULL,tem,"window handle",MB_OK);*/
				}
			}
			//names[(i+1)*MAX_PATH]='\n';
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
