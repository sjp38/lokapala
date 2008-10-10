/**@file	DecisionFacade.cpp
 * @brief	DCM의 Facade의 멤버 함수 구현
 * author	siva
 */

#include "stdafx.h"
#include "DecisionFacade.h"

#include "DecisionManager.h"

/**@brief	오퍼레이터에게 로그인 요청을 한다.	*/
void CDecisionFacade::LoginRequest(void *a_userInfo)
{
	CDecisionManager::Instance()->LoginRequest(a_userInfo);
}


/**@brief	로그인 허용 메세지에 응하는 서비스를 한다.(사용자 방해 제거)
 */
void CDecisionFacade::LoginAccepted(int a_level)
{
	CDecisionManager::Instance()->LoginAccepted(a_level);
}