/**@file	ProcessObserverExport.h
 * @brief	���� ���μ��� ���ø� ���� �Լ��� import�� ���� ���ȴ�.
 * @author	siva
 */

#ifndef OBSERVER_EXPORT_H
#define OBSERVER_EXPORT_H



extern "C" __declspec(dllimport)
BOOL WINAPI ObserveRunningProcesses(BOOL fInstall, DWORD dwThreadId);



#endif