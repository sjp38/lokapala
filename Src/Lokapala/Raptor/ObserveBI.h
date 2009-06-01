/**@file	ObserveBI.h
 * @brief	OSM의 BI 정의.
 * @author	siva
 */

#ifndef OBSERVE_BI_H
#define OBSERVE_BI_H

/**@ingroup	GroupOSM
 * @class	CObserveBI
 * @brief	Observe Manager 의 Button Interface.
 * @remarks	인터페이다.
 */
class CObserveBI
{
public :
	/**@brief	프로세스 실행 감시를 시작한다.	*/
	virtual void StartProcessObservation() = 0;
	/**@brief	프로세스 실행 감시를 중지한다.	*/
	virtual void StopProcessObservation() = 0;
	/**@brief	실행된 프로세스 이름을 OSM에게 알린다.	*/
	virtual void ReceiveExecutedProcess(CString a_executedProcess) = 0;
};

#endif
