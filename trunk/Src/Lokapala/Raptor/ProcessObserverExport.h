/**@file	ProcessObserverExport.h
 * @brief	실행 프로세스 감시를 위한 함수의 import를 위해 사용된다.
 * @author	siva
 */

#ifndef OBSERVER_EXPORT_H
#define OBSERVER_EXPORT_H



extern "C" __declspec(dllimport)
BOOL WINAPI ObserveRunningProcesses(BOOL fInstall, DWORD dwThreadId);



#endif
