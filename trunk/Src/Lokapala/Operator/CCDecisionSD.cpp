/**@file	CCDecisionSD.cpp
 * @brief	CCM�� DecisionSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "CCDecisionSD.h"

/**@brief	������� �α��� ������ ���� ��ȿ�� ��������� Ȯ���Ѵ�.
 * @param	a_loginRequestData	����� �α��� ������ ������. �ش� DTO�� ������������ void �����ͷ� ĳ���� �� ����Ѵ�.
 */
void CCCDecisionSD::UserLogin(void *a_loginRequestData)
{
	CCBFMediator::Instance()->UserLogin(a_loginRequestData);
}
