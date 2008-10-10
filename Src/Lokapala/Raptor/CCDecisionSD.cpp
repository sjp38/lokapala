/**@file	CCDecisionSD.cpp
 * @brief	CCM의 DecisionSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "CCDecisionSD.h"

/**@brief	로그인 되었음을 알리며 그에 따른 서비스를 요청한다.
 * @param	a_level	로그인 허용된 사용자의 레벨.
 */
void CCCDecisionSD::LoginAccepted(int a_level)
{
	CCBFMediator::Instance()->LoginAccepted(a_level);
}