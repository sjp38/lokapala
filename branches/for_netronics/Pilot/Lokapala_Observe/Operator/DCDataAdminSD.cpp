/**@file	DCDataAdminSD.cpp
 * @brief	DCM의 AdminSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCDataAdminSD.h"

/**@brief	DCM에서 DAM으로의 service delegate 테스트용 멤버 함수. 곧바로 DAM에 요청하지 않고, mediator에게 요청을 한다.
 */
void CDCDataAdminSD::ReadDAM()
{
	CCBFMediator::Instance()->ReadDAM();
}