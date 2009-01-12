/**@file	ObserveFacade.cpp
 * @brief	OSM�� Facade�� ����Լ� ����
 * author	siva
 */

#include "stdafx.h"
#include "ObserveFacade.h"

#include "OSDecisionSD.h"
#include "ProcessObserverExport.h"

/**@brief	���� ���μ��� ���ø� �����Ѵ�.
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

/**@brief	���� ���μ��� ���ø� �ߴ��Ѵ�.
 */
void CObserveFacade::StopProcessObservation()
{
	ObserveRunningProcesses(false, NULL);
}


/**@brief	����� ���μ����� OSM �ڽſ��� �˸���.
 */
void CObserveFacade::ReceiveExecutedProcess(CString a_executedProcess)
{
	COSDecisionSD::Instance()->NotifyExecutedProcess(a_executedProcess);
}