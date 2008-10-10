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
	/**@brief	���۷����Ϳ��� �α��� ��û�� �Ѵ�.
	 */
	virtual void LoginRequest(void *a_userInfo) = 0;
	/**@brief	�α��� ��뿡 ���� ���񽺸� �Ѵ�.
	 */
	virtual void LoginAccepted(int a_level) = 0;
};

#endif