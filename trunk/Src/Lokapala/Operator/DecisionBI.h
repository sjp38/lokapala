/**@file	DecisionBI.h
 * @brief	DCM�� Button Interface ����
 * @author	siva
 */
#ifndef DECISION_BI_H
#define DECISION_BI_H

/**@ingroup	GroupDCM
 * @class	CDecisionBI
 * @brief	DCM�� Button Interface.
 * @remarks	�������̽��� ���̴�.
 */
class CDecisionBI
{
public :
	/**@brief	����� ȣ��Ʈ�� ���� ó���Ѵ�.	*/
	virtual void HostConnected(void *a_hostData) = 0;
	/**@brief	������ ���� ȣ��Ʈ�� ���� ó���Ѵ�.	*/
	virtual void HostDisconnected(void *a_hostData) = 0;
	/**@brief	����� �α��� ó��. �ùٸ� ��������� Ȯ���Ѵ�.
	 * @param	a_loginRequestData	����� �α��� ������ ������. �ش� DTO�� ������������ void �����ͷ� ĳ���� �� ����Ѵ�.
	 */
	virtual void JudgeLoginRequest(void *a_loginRequestData) = 0;

	/**@brief	����ڰ� ������ ���μ����� ���� ���� ó��.	*/
	virtual void JudgeUserExecutedProcess(void *a_executedProcessData) = 0;
	/**@brief	���ο� ���� ���� ���� ���� ó��	*/
	virtual void PresentStatusReport(void *a_statusReportData) = 0;
	/**@brief	Ư�� ȣ��Ʈ�� ��ǻ�͸� �����Ų��.	*/
	virtual void ShutdownHost(void *a_argument) = 0;
	/**@brief	Ư�� ȣ��Ʈ�� ��ǻ�͸� �����ý�Ų��.	*/
	virtual void RebootHost(void *a_argument) = 0;
	/**@brief	Ư�� ����ڸ� ������ �α׾ƿ� ��Ų��.	*/
	virtual void BanUser(void *a_argument) = 0;
	/**@brief	Ư�� ȣ��Ʈ�� Ư�� ���μ����� �����Ų��.	*/
	virtual void ExecuteHostProcess(void *a_argument) = 0;
	/**@brief	Ư�� ȣ��Ʈ�� Ư�� ���μ����� �����Ų��.	*/
	virtual void KillHostProcess(void *a_argument) = 0;
	/**@brief	Ư�� ȣ��Ʈ�� ��� ���μ����� �����Ų��.	*/
	virtual void GenocideHostProcess(void *a_argument) = 0;
	/**@brief	Ư�� ȣ��Ʈ���� ��� �Ѵ�.	*/
	virtual void WarnHost(void *a_argument) = 0;
	/**@brief	Ư�� ȣ��Ʈ���� ���� ���� �Ѵ�	*/
	virtual void SubmitStatusReportToHost(void *a_statusReport) = 0;
	/**@brief	Ư�� ȣ��Ʈ�� ������ ������ ������Ų��.	*/
	virtual void TerminateRaptorOnHost(void *a_argument) = 0;
};

#endif