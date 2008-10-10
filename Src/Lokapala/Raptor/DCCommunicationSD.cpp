/**@file	DCCommunicationSD.cpp
 * @brief	DCM의 CommunicationSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCCommunicationSD.h"


/**@brief	커뮤니케이션 컴포넌트에게 로그인 신호를 보내도록 한다.
 */
void CDCCommunicationSD::LoginRequest(void *a_userInfo)
{
	CCBFMediator::Instance()->SendLoginRequest(a_userInfo);
}