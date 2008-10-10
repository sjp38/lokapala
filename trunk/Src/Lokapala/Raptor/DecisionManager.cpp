/**@file	DecisionManager.cpp
 * @brief	CDecisionManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "DecisionManager.h"

#include "DCCommunicationSD.h"
#include "DCDataAdminSD.h"
#include "DCControlSD.h"

/**@brief	오퍼레이터에게 로그인 요청을 한다.	*/
void CDecisionManager::LoginRequest(void *a_userInfo)
{
	CDCDataAdminSD::Instance()->RegistUser(a_userInfo);
	CDCCommunicationSD::Instance()->LoginRequest(a_userInfo);
}

/**@brief	로그인 허용 메세지를 받았을 때.
 *			사용자 방해 행위를 중단하고, 사용자 레벨 정보 등을 기억한다.
 */
void CDecisionManager::LoginAccepted(int a_level)
{
	CDCDataAdminSD::Instance()->RegistUserLevel(a_level);
	CDCControlSD::Instance()->ReleaseUser();
	//AfxMessageBox(_T("login!!!"));
}