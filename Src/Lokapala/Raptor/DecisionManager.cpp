/**@file	DecisionManager.cpp
 * @brief	CDecisionManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "DecisionManager.h"

#include "DCCommunicationSD.h"
#include "DCDataAdminSD.h"
#include "DCControlSD.h"

/**@brief	���۷����Ϳ��� �α��� ��û�� �Ѵ�.	*/
void CDecisionManager::LoginRequest(void *a_userInfo)
{
	CDCDataAdminSD::Instance()->RegistUser(a_userInfo);
	CDCCommunicationSD::Instance()->LoginRequest(a_userInfo);
}

/**@brief	�α��� ��� �޼����� �޾��� ��.
 *			����� ���� ������ �ߴ��ϰ�, ����� ���� ���� ���� ����Ѵ�.
 */
void CDecisionManager::LoginAccepted(int a_level)
{
	CDCDataAdminSD::Instance()->RegistUserLevel(a_level);
	CDCControlSD::Instance()->ReleaseUser();
	//AfxMessageBox(_T("login!!!"));
}