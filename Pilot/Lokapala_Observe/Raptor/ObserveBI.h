/**@file	ObserveBI.h
 * @brief	OSM�� BI ����.
 * @author	siva
 */

#ifndef OBSERVE_BI_H
#define OBSERVE_BI_H

/**@ingroup	GroupOSM
 * @class	CObserveBI
 * @brief	Observe Manager �� Button Interface.
 * @remarks	�������̴�.
 */
class CObserveBI
{
public :
	/**@brief	���μ��� ���� ���ø� �����Ѵ�.	*/
	virtual void StartProcessObservation() = 0;
	/**@brief	���μ��� ���� ���ø� �����Ѵ�.	*/
	virtual void StopProcessObservation() = 0;
	/**@brief	����� ���μ��� �̸��� OSM���� �˸���.	*/
	virtual void ReceiveExecutedProcess(CString a_executedProcess) = 0;
};

#endif