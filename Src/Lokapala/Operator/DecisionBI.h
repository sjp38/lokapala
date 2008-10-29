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
	/**@brief	����� �α��� ó��. �ùٸ� ��������� Ȯ���Ѵ�.
	 * @param	a_loginRequestData	����� �α��� ������ ������. �ش� DTO�� ������������ void �����ͷ� ĳ���� �� ����Ѵ�.
	 */
	virtual void JudgeLoginRequest(void *a_loginRequestData) = 0;

	/**@brief	����ڰ� ������ ���μ����� ���� ���� ó��.	*/
	virtual void JudgeUserExecutedProcess(void *a_executedProcessData) = 0;
	/**@brief	���ο� ���� ���� ���� ���� ó��	*/
	virtual void PresentStatusReport(void *a_statusReportData) = 0;
};

#endif