/**@file	ObserveFacade.cpp
 * @brief	OSM의 Facade의 멤버함수 구현
 * author	siva
 */

#include "stdafx.h"
#include "ObserveFacade.h"

#include "ProcessObserverExport.h"

/**@brief	실행 프로세스 감시를 시작한다.
 */
void CObserveFacade::StartProcessObservation()
{
	ObserveRunningProcesses(true, NULL);
}

/**@brief	실행 프로세스 감시를 중단한다.
 */
void CObserveFacade::StopProcessObservation()
{
	ObserveRunningProcesses(false, NULL);
}