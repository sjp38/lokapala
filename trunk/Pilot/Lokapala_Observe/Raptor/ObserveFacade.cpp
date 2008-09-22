/**@file	ObserveFacade.cpp
 * @brief	OSM의 Facade의 멤버함수 구현
 * author	siva
 */

#include "stdafx.h"
#include "ObserveFacade.h"

#include "OSDecisionSD.h"
#include "ProcessObserverExport.h"

/**@brief	실행 프로세스 감시를 시작한다.
 */
void CObserveFacade::StartProcessObservation()
{
	HWND selfHandle = (CCBFMediator::Instance()->GetMainDlg())->m_hWnd;
	HWND *pSelfHandle;

	HANDLE m_map = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, sizeof(char)*MAX_PATH, _T("raptorSelfWindowHandle"));
	if(!m_map)
	{
		AfxMessageBox(_T("message map create fail!!"));
	}
	pSelfHandle = (HWND *)MapViewOfFile(m_map, FILE_MAP_WRITE, 0, 0, 0);
	*pSelfHandle = selfHandle;

	ObserveRunningProcesses(true, NULL);
}

/**@brief	실행 프로세스 감시를 중단한다.
 */
void CObserveFacade::StopProcessObservation()
{
	ObserveRunningProcesses(false, NULL);
}


/**@brief	실행된 프로세스를 OSM 자신에게 알린다.
 */
void CObserveFacade::ReceiveExecutedProcess(CString a_executedProcess)
{
	COSDecisionSD::Instance()->NotifyExecutedProcess(a_executedProcess);
}