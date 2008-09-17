//#############################################################################
//		 2007.7. coded by siva.		API ��ŷ ���̺귯�� ���� ��ü �����ڵ�.
//			reference document : Jeffery Ritcher's code
//#############################################################################


#include "CmnHdr.h"
#include <ImageHlp.h>
#pragma comment(lib, "ImageHlp")

#include "APIHook.h"
#include "Toolhelp.h"


///////////////////////////////////////////////////////////////////////////////


// When an application runs on Windows 98 under a debugger, the debugger
// makes the module's import section point to a stub that calls the desired 
// function. To account for this, the code in this module must do some crazy 
// stuff. These variables are needed to help with the crazy stuff.


// The highest private memory address (used for Windows 98 only)
//PVOID CAPIHook::sm_pvMaxAppAddr = NULL;	//����98 ���� �κ�
//const BYTE cPushOpCode = 0x68;   // The PUSH opcode on x86 platforms


///////////////////////////////////////////////////////////////////////////////


// The head of the linked-list of CAPIHook objects
CAPIHook* CAPIHook::sm_pHead = NULL;


///////////////////////////////////////////////////////////////////////////////

//������.
CAPIHook::CAPIHook(PSTR pszCalleeModName, PSTR pszFuncName, PROC pfnHook, 
   BOOL fExcludeAPIHookMod) {

	//���� 98 ���� �κ�.
	/*
   if (sm_pvMaxAppAddr == NULL) {
      // Functions with address above lpMaximumApplicationAddress require
      // special processing (Windows 98 only)
      SYSTEM_INFO si;
      GetSystemInfo(&si);
      sm_pvMaxAppAddr = si.lpMaximumApplicationAddress;
   }
   */

	m_pNext  = sm_pHead;   // ���� ���� ���� ��带 �ְ�
	sm_pHead = this;       // ���� ��带 ���� ��ü

	// �� �з����͸� ��ü �� ��������� ����.
	m_pszCalleeModName   = pszCalleeModName;
	m_pszFuncName        = pszFuncName;
	m_pfnHook            = pfnHook;
	m_fExcludeAPIHookMod = fExcludeAPIHookMod;
	m_pfnOrig            = GetProcAddressRaw(GetModuleHandleA(pszCalleeModName), m_pszFuncName);
	chASSERT(m_pfnOrig != NULL);  // �����Լ��� �����߾�� ��.

	/*
	if (m_pfnOrig > sm_pvMaxAppAddr) {
		// The address is in a shared DLL; the address needs fixing up 
		PBYTE pb = (PBYTE) m_pfnOrig;
		if (pb[0] == cPushOpCode) {
			// Skip over the PUSH op code and grab the real address
			PVOID pv = * (PVOID*) &pb[1];
			m_pfnOrig = (PROC) pv;
		}
	}
	*/
	//������ ��� ��⿡ ���� �ɾ��ش�.
	ReplaceIATEntryInAllMods(m_pszCalleeModName, m_pfnOrig, m_pfnHook, 
		m_fExcludeAPIHookMod);
}


///////////////////////////////////////////////////////////////////////////////

//�Ҹ���
CAPIHook::~CAPIHook() {

	//��ũ�Լ�, �����Լ��� �Ųٷ� ��ũ�ɾ� ��ũ ����.
	ReplaceIATEntryInAllMods(m_pszCalleeModName, m_pfnHook, m_pfnOrig, 
		m_fExcludeAPIHookMod);

	//��ũ�帮��Ʈ�κ��� ����
	CAPIHook* p = sm_pHead; 
	if (p == this) {     // Removing the head node
		sm_pHead = p->m_pNext; 
	} else {
		BOOL fFound = FALSE;
		// Next�� NULL�� ������, �� ������ ����Ʈ���� ����.
		for (; !fFound && (p->m_pNext != NULL); p = p->m_pNext) {
			if (p->m_pNext == this) {
				// Make the node that points to us point to the our next node
				p->m_pNext = p->m_pNext->m_pNext;
				break; 
			}
		}
		chASSERT(fFound);
	}
}


///////////////////////////////////////////////////////////////////////////////


// NOTE: This function must NOT be inlined
FARPROC CAPIHook::GetProcAddressRaw(HMODULE hmod, PCSTR pszProcName) {
	return(::GetProcAddress(hmod, pszProcName));
}


///////////////////////////////////////////////////////////////////////////////


//������ �޸� ���� HMODULE ����
static HMODULE ModuleFromAddress(PVOID pv) {
	MEMORY_BASIC_INFORMATION mbi;
	return((VirtualQuery(pv, &mbi, sizeof(mbi)) != 0)	//�ش� ������ ���
		? (HMODULE) mbi.AllocationBase : NULL);	//���̽�(module)�� ����.
}


///////////////////////////////////////////////////////////////////////////////


void CAPIHook::ReplaceIATEntryInAllMods(PCSTR pszCalleeModName, 
   PROC pfnCurrent, PROC pfnNew, BOOL fExcludeAPIHookMod) {

	//�� �Լ��� �Ҽӵ� ��� �ڵ��� ����
	HMODULE hmodThisMod = fExcludeAPIHookMod 
		? ModuleFromAddress(ReplaceIATEntryInAllMods) : NULL;
	
	//���μ��� �� ������ ����Ʈ�� ����
	CToolhelp th(TH32CS_SNAPMODULE, GetCurrentProcessId());

	MODULEENTRY32 me = { sizeof(me) };
	//��� ������ �˻��ϸ�
	for (BOOL fOk = th.ModuleFirst(&me); fOk; fOk = th.ModuleNext(&me)) {
		// ReplaceIATEntryInAllMods �ڽ��� ����� �����ϰ�
		if (me.hModule != hmodThisMod) {
			// ���� ��ũ�� �ɾ��ش�.
			ReplaceIATEntryInOneMod(pszCalleeModName, pfnCurrent, pfnNew, me.hModule);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////


void CAPIHook::ReplaceIATEntryInOneMod(PCSTR pszCalleeModName, PROC pfnCurrent,
									   PROC pfnNew, HMODULE hmodCaller) {
	// Get the address of the module's import section
	ULONG ulSize;
	//�ݷ� ����� ����Ʈ ��ũ���� ȹ��.
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)
		ImageDirectoryEntryToData(hmodCaller, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);
	
	if (pImportDesc == NULL)
		return;  // This module has no import section

	//����Ʈ ��ũ���� �� �ݸ� ����� ����Ʈ��ũ���͸� ã�´�
	for (; pImportDesc->Name; pImportDesc++) {
		PSTR pszModName = (PSTR) ((PBYTE) hmodCaller + pImportDesc->Name);
		if (lstrcmpiA(pszModName, pszCalleeModName) == 0)
			break;   // Found
	}
	if (pImportDesc->Name == 0)	//�ش� �ݸ� ����� ����Ʈ ��ũ���Ͱ� ����ġ ����
		return;

	//�ݸ��� ����Ʈ ��ũ������ First Thunk ȹ��
	PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)((PBYTE) hmodCaller + pImportDesc->FirstThunk);
	
	//ûũ�� �������� ����ŷ �Լ��� ûũ�� �˻�
	for (; pThunk->u1.Function; pThunk++) {
		//�ش� ûũ�� ����Ű�� �Լ��� ����ŷ�Լ� ��
		PROC* ppfn = (PROC*) &pThunk->u1.Function;
		BOOL fFound = (*ppfn == pfnCurrent);
		
		/*
		//����ŷ�Լ��� ûũ�� �ƴ����� DLL���� ���� �ִٸ�(DLL, APP�� ���� �ִ� 98 �޸� ����),
		//����� �� ûũ�� ����Ű�� �Լ� ��巹���� ���Ѵ�.
		if (!fFound && (*ppfn > sm_pvMaxAppAddr)) {
			// If this is not the function and the address is in a shared DLL, 
			// then maybe we're running under a debugger on Windows 98. In this 
			// case, this address points to an instruction that may have the 
			// correct address.
			PBYTE pbInFunc = (PBYTE) *ppfn;
			if (pbInFunc[0] == cPushOpCode) {
				// Ǫ�� ����� �־��ٸ� �� ���� ���� ��, ���� �Լ� ��巹�� ȹ��
				ppfn = (PROC*) &pbInFunc[1];
				// Is this the function we're looking for?
				fFound = (*ppfn == pfnCurrent);
			}
		}
		*/

		//����ư� ����ŷ�Լ��� ûũ�� ã�Ҵٸ�
		if (fFound) {
			//����Ʈ���� ��巹���� ��ü�Լ��� ��ü(�޸� ��������Ʈ)
			WriteProcessMemory(GetCurrentProcess(), ppfn, &pfnNew, sizeof(pfnNew), NULL);
			return;
		}
	}

   // If we get to here, the function is not in the caller's import section
}


///////////////////////////////////////////////////////////////////////////////

/*
// LoadLibrary �Լ�, GetProcAddress �Լ��� ���� ���Ǿ� ��ũ�� �����İ� �� �ִ�.
// �̵��� ������ ��ũ.

CAPIHook CAPIHook::sm_LoadLibraryA  ("Kernel32.dll", "LoadLibraryA",   
   (PROC) CAPIHook::LoadLibraryA, TRUE);

CAPIHook CAPIHook::sm_LoadLibraryW  ("Kernel32.dll", "LoadLibraryW",   
   (PROC) CAPIHook::LoadLibraryW, TRUE);

CAPIHook CAPIHook::sm_LoadLibraryExA("Kernel32.dll", "LoadLibraryExA", 
   (PROC) CAPIHook::LoadLibraryExA, TRUE);

CAPIHook CAPIHook::sm_LoadLibraryExW("Kernel32.dll", "LoadLibraryExW", 
   (PROC) CAPIHook::LoadLibraryExW, TRUE);

CAPIHook CAPIHook::sm_GetProcAddress("Kernel32.dll", "GetProcAddress", 
   (PROC) CAPIHook::GetProcAddress, TRUE);


///////////////////////////////////////////////////////////////////////////////


void CAPIHook::FixupNewlyLoadedModule(HMODULE hmod, DWORD dwFlags) {
	//LoadLibrary�� ���ο� ����� �ε�� ���, �ٽ��ѹ� ������ ��ŷ�Ѵ�.
	if ((hmod != NULL) && ((dwFlags & LOAD_LIBRARY_AS_DATAFILE) == 0)) {
		for (CAPIHook* p = sm_pHead; p != NULL; p = p->m_pNext) {
			ReplaceIATEntryInOneMod(p->m_pszCalleeModName, p->m_pfnOrig, p->m_pfnHook, hmod);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////


HMODULE WINAPI CAPIHook::LoadLibraryA(PCSTR pszModulePath) {
	HMODULE hmod = ::LoadLibraryA(pszModulePath);
	FixupNewlyLoadedModule(hmod, 0);
	return(hmod);
}


///////////////////////////////////////////////////////////////////////////////


HMODULE WINAPI CAPIHook::LoadLibraryW(PCWSTR pszModulePath) {
	HMODULE hmod = ::LoadLibraryW(pszModulePath);
	FixupNewlyLoadedModule(hmod, 0);
	return(hmod);
}


///////////////////////////////////////////////////////////////////////////////


HMODULE WINAPI CAPIHook::LoadLibraryExA(PCSTR pszModulePath, HANDLE hFile, DWORD dwFlags) {
	HMODULE hmod = ::LoadLibraryExA(pszModulePath, hFile, dwFlags);
	FixupNewlyLoadedModule(hmod, dwFlags);
	return(hmod);
}


///////////////////////////////////////////////////////////////////////////////


HMODULE WINAPI CAPIHook::LoadLibraryExW(PCWSTR pszModulePath, HANDLE hFile, DWORD dwFlags) {
	HMODULE hmod = ::LoadLibraryExW(pszModulePath, hFile, dwFlags);
	FixupNewlyLoadedModule(hmod, dwFlags);
	return(hmod);
}


///////////////////////////////////////////////////////////////////////////////


FARPROC WINAPI CAPIHook::GetProcAddress(HMODULE hmod, PCSTR pszProcName) {
	// �Լ��� ���ּ� ȹ��
	FARPROC pfn = GetProcAddressRaw(hmod, pszProcName);

	CAPIHook* p = sm_pHead;
	// GetProcAddress�� �ҷ��� �Լ��� ����ũ �Լ������ ����
	for (; (pfn != NULL) && (p != NULL); p = p->m_pNext) {
		if (pfn == p->m_pfnOrig) {
			//����ũ�Լ��� �����ϴٸ� ��ũ�Լ��� ��ġ
			pfn = p->m_pfnHook;
			break;
		}
	}
	return(pfn);
}
*/

//////////////////////////////// End of File //////////////////////////////////
