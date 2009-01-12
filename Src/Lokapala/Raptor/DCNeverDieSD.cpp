/**@file	DCNeverDieSD.cpp
 * @brief	DCM의 NeverDieSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCNeverDieSD.h"

/**@brief	네버다이 모드를 종료한다.
 */
void CDCNeverDieSD::StopNeverDie()
{
	CCBFMediator::Instance()->StopNeverDie();
}