/**@file	ObserveFacade.cpp
 * @brief	OSM�� Facade�� ����Լ� ����
 * author	siva
 */

#include "stdafx.h"
#include "ObserveFacade.h"

#include "ProcessObserverExport.h"

/**@brief	���� ���μ��� ���ø� �����Ѵ�.
 */
void CObserveFacade::StartProcessObservation()
{
	ObserveRunningProcesses(true, NULL);
}

/**@brief	���� ���μ��� ���ø� �ߴ��Ѵ�.
 */
void CObserveFacade::StopProcessObservation()
{
	ObserveRunningProcesses(false, NULL);
}