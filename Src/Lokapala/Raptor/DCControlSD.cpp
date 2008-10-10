/**@file	DCControlSD.cpp
 * @brief	DCM의 ControlSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCControlSD.h"

/**@brief	사용자를 자유롭게 컴퓨터를 사용 할 수 있도록 해준다.
 */
void CDCControlSD::ReleaseUser()
{
	CCBFMediator::Instance()->ReleaseUser();
}