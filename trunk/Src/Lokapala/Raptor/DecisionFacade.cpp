/**@file	DecisionFacade.cpp
 * @brief	DCM�� Facade�� ��� �Լ� ����
 * author	siva
 */

#include "stdafx.h"
#include "DecisionFacade.h"

#include "DecisionManager.h"

/**@brief	���۷����Ϳ��� �α��� ��û�� �Ѵ�.	*/
void CDecisionFacade::LoginRequest(void *a_userInfo)
{
	CDecisionManager::Instance()->LoginRequest(a_userInfo);
}


/**@brief	�α��� ��� �޼����� ���ϴ� ���񽺸� �Ѵ�.(����� ���� ����)
 */
void CDecisionFacade::LoginAccepted(int a_level)
{
	CDecisionManager::Instance()->LoginAccepted(a_level);
}