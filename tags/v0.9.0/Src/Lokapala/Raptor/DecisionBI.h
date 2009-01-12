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
	/**@brief	���۷����Ϳ� ������ �Ǿ��� ��.	*/
	virtual void Connected() = 0;
	/**@brief	���۷����Ϳ��� ������ ������ ��.	*/
	virtual void Disconnected() = 0;
	/**@brief	���۷����Ϳ��� �α��� ��û�� �Ѵ�.	 */
	virtual void LoginRequest(void *a_userInfo) = 0;
	/**@brief	�α��� ��뿡 ���� ���񽺸� �Ѵ�.	 */
	virtual void LoginAccepted(int a_level) = 0;
	/**@brief	���� �α��� ����� �޾��� ��.	*/
	virtual void LoginOrderReceived(void *a_userInfo) = 0;
	/**@brief	���� �α׾ƿ� ����� �޾��� ��.	*/
	virtual void LogoutOrderReceived(void *a_message) = 0;	
	/**@brief	���� ��ǻ�� ���� ����� �޾��� ��.	*/
	virtual void ShutdownOrderReceived(void *a_message) = 0;
	/**@brief	���� ��ǻ�� ������ ����� �޾��� ��.	*/
	virtual void RebootOrderReceived(void *a_message) = 0;
	/**@brief	�������� ��� ���μ��� ���� ����� �޾��� ��.	*/
	virtual void GenocideProcessesOrderReceived(void *a_message) = 0;
	/**@brief	Ư�� ���μ��� ���� ����� �޾��� ��.	*/
	virtual void KillProcessOrderReceived(void *a_processName) = 0;
	/**@brief	Ư�� ���μ��� ���� ����� �޾��� ��.	*/
	virtual void ExecuteProcessOrderReceived(void *a_processName) = 0;
	/**@brief	���۷����ͷκ��� ���� ���� �������� ��.	*/
	virtual void StatusReportReceived(void *a_statusReport) = 0;
	/**@brief	���۷����ͷκ��� ���� ���� ����� �������� ��.	*/
	virtual void RaptorTerminationOrderReceived() = 0;

	/**@brief	����� ���μ����� �̸��� ����޴´�.	*/
	virtual void ReportExecutedProcess(CString *a_executedProcess) = 0;
	/**@brief	��Ȳ ��ȭ�� �����Ѵ�.	*/
	virtual void ReportStatus(void *a_status) = 0;

	virtual void UserTryingToKillMe() = 0;
};

#endif