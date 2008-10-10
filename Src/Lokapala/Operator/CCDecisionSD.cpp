/**@file	CCDecisionSD.cpp
 * @brief	CCM의 DecisionSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "CCDecisionSD.h"

/**@brief	사용자의 로그인 정보에 대해 유효한 사용자인지 확인한다.
 * @param	a_loginRequestData	사용자 로그인 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
 */
void CCCDecisionSD::UserLogin(void *a_loginRequestData)
{
	CCBFMediator::Instance()->UserLogin(a_loginRequestData);
}
