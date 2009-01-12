//#############################################################################
//		 2007.7. coded by siva.		API 후킹 라이브러리 제공 객체 구현코드.
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
//PVOID CAPIHook::sm_pvMaxAppAddr = NULL;	//윈도98 전용 부분
//const BYTE cPushOpCode = 0x68;   // The PUSH opcode on x86 platforms


///////////////////////////////////////////////////////////////////////////////


// The head of the linked-list of CAPIHook objects
CAPIHook* CAPIHook::sm_pHead = NULL;


///////////////////////////////////////////////////////////////////////////////

//생성자.
CAPIHook::CAPIHook(PSTR pszCalleeModName, PSTR pszFuncName, PROC pfnHook, 
   BOOL fExcludeAPIHookMod) {

	//윈도 98 전용 부분.
	/*
   if (sm_pvMaxAppAddr == NULL) {
      // Functions with address above lpMaximumApplicationAddress require
      // special processing (Windows 98 only)
      SYSTEM_INFO si;
      GetSystemInfo(&si);
      sm_pvMaxAppAddr = si.lpMaximumApplicationAddress;
   }
   */

	m_pNext  = sm_pHead;   // 다음 노드로 현재 헤드를 주고
	sm_pHead = this;       // 현재 노드를 헤드로 대체

	// 각 패러미터를 객체 내 멤버변수로 저장.
	m_pszCalleeModName   = pszCalleeModName;
	m_pszFuncName        = pszFuncName;
	m_pfnHook            = pfnHook;
	m_fExcludeAPIHookMod = fExcludeAPIHookMod;
	m_pfnOrig            = GetProcAddressRaw(GetModuleHandleA(pszCalleeModName), m_pszFuncName);
	chASSERT(m_pfnOrig != NULL);  // 원본함수는 존재했어야 함.

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
	//현재의 모든 모듈에 훅을 걸어준다.
	ReplaceIATEntryInAllMods(m_pszCalleeModName, m_pfnOrig, m_pfnHook, 
		m_fExcludeAPIHookMod);
}


///////////////////////////////////////////////////////////////////////////////

//소멸자
CAPIHook::~CAPIHook() {

	//후크함수, 원본함수를 거꾸로 후크걸어 후크 해제.
	ReplaceIATEntryInAllMods(m_pszCalleeModName, m_pfnHook, m_pfnOrig, 
		m_fExcludeAPIHookMod);

	//링크드리스트로부터 제거
	CAPIHook* p = sm_pHead; 
	if (p == this) {     // Removing the head node
		sm_pHead = p->m_pNext; 
	} else {
		BOOL fFound = FALSE;
		// Next가 NULL일 때까지, 즉 모조리 리스트에서 제거.
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


//지정된 메모리 포함 HMODULE 리턴
static HMODULE ModuleFromAddress(PVOID pv) {
	MEMORY_BASIC_INFORMATION mbi;
	return((VirtualQuery(pv, &mbi, sizeof(mbi)) != 0)	//해당 정보를 얻고
		? (HMODULE) mbi.AllocationBase : NULL);	//베이스(module)을 리턴.
}


///////////////////////////////////////////////////////////////////////////////


void CAPIHook::ReplaceIATEntryInAllMods(PCSTR pszCalleeModName, 
   PROC pfnCurrent, PROC pfnNew, BOOL fExcludeAPIHookMod) {

	//이 함수가 소속된 모듈 핸들을 습득
	HMODULE hmodThisMod = fExcludeAPIHookMod 
		? ModuleFromAddress(ReplaceIATEntryInAllMods) : NULL;
	
	//프로세스 내 모듈들의 리스트를 습득
	CToolhelp th(TH32CS_SNAPMODULE, GetCurrentProcessId());

	MODULEENTRY32 me = { sizeof(me) };
	//모든 모듈들을 검사하며
	for (BOOL fOk = th.ModuleFirst(&me); fOk; fOk = th.ModuleNext(&me)) {
		// ReplaceIATEntryInAllMods 자신의 모듈을 제외하고
		if (me.hModule != hmodThisMod) {
			// 각각 후크를 걸어준다.
			ReplaceIATEntryInOneMod(pszCalleeModName, pfnCurrent, pfnNew, me.hModule);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////


void CAPIHook::ReplaceIATEntryInOneMod(PCSTR pszCalleeModName, PROC pfnCurrent,
									   PROC pfnNew, HMODULE hmodCaller) {
	// Get the address of the module's import section
	ULONG ulSize;
	//콜러 모듈의 임포트 디스크립터 획득.
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)
		ImageDirectoryEntryToData(hmodCaller, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);
	
	if (pImportDesc == NULL)
		return;  // This module has no import section

	//임포트 디스크립터 중 콜리 모듈의 임포트디스크립터를 찾는다
	for (; pImportDesc->Name; pImportDesc++) {
		PSTR pszModName = (PSTR) ((PBYTE) hmodCaller + pImportDesc->Name);
		if (lstrcmpiA(pszModName, pszCalleeModName) == 0)
			break;   // Found
	}
	if (pImportDesc->Name == 0)	//해당 콜리 모듈의 임포트 디스크립터가 존재치 않음
		return;

	//콜리의 임포트 디스크립터의 First Thunk 획득
	PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)((PBYTE) hmodCaller + pImportDesc->FirstThunk);
	
	//청크를 뒤져가며 피후킹 함수의 청크를 검색
	for (; pThunk->u1.Function; pThunk++) {
		//해당 청크가 가리키는 함수와 피후킹함수 비교
		PROC* ppfn = (PROC*) &pThunk->u1.Function;
		BOOL fFound = (*ppfn == pfnCurrent);
		
		/*
		//피후킹함수의 청크가 아니지만 DLL공간 내에 있다면(DLL, APP가 따로 있는 98 메모리 구조),
		//제대로 된 청크가 가리키는 함수 어드레스를 구한다.
		if (!fFound && (*ppfn > sm_pvMaxAppAddr)) {
			// If this is not the function and the address is in a shared DLL, 
			// then maybe we're running under a debugger on Windows 98. In this 
			// case, this address points to an instruction that may have the 
			// correct address.
			PBYTE pbInFunc = (PBYTE) *ppfn;
			if (pbInFunc[0] == cPushOpCode) {
				// 푸시 명령이 있었다면 그 다음 값을 비교, 실제 함수 어드레스 획득
				ppfn = (PROC*) &pbInFunc[1];
				// Is this the function we're looking for?
				fFound = (*ppfn == pfnCurrent);
			}
		}
		*/

		//어찌됐건 피후킹함수의 청크를 찾았다면
		if (fFound) {
			//임포트섹션 어드레스를 대체함수로 교체(메모리 오버라이트)
			WriteProcessMemory(GetCurrentProcess(), ppfn, &pfnNew, sizeof(pfnNew), NULL);
			return;
		}
	}

   // If we get to here, the function is not in the caller's import section
}


///////////////////////////////////////////////////////////////////////////////

/*
// LoadLibrary 함수, GetProcAddress 함수가 이후 사용되어 후크를 지나쳐갈 수 있다.
// 이들을 모조리 후크.

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
	//LoadLibrary로 새로운 모듈이 로드된 경우, 다시한번 모조리 후킹한다.
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
	// 함수의 실주소 획득
	FARPROC pfn = GetProcAddressRaw(hmod, pszProcName);

	CAPIHook* p = sm_pHead;
	// GetProcAddress로 불러온 함수와 피후크 함수목록을 대조
	for (; (pfn != NULL) && (p != NULL); p = p->m_pNext) {
		if (pfn == p->m_pfnOrig) {
			//피후크함수와 동일하다면 후크함수로 대치
			pfn = p->m_pfnHook;
			break;
		}
	}
	return(pfn);
}
*/

//////////////////////////////// End of File //////////////////////////////////
