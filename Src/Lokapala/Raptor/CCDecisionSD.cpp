/**@file	CCDecisionSD.cpp
 * @brief	CCM�� DecisionSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "CCDecisionSD.h"

/**@brief	�α��� �Ǿ����� �˸��� �׿� ���� ���񽺸� ��û�Ѵ�.
 * @param	a_level	�α��� ���� ������� ����.
 */
void CCCDecisionSD::LoginAccepted(int a_level)
{
	CCBFMediator::Instance()->LoginAccepted(a_level);
}