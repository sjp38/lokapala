/**@file	DCNeverDieSD.cpp
 * @brief	DCM�� NeverDieSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCNeverDieSD.h"

/**@brief	�׹����� ��带 �����Ѵ�.
 */
void CDCNeverDieSD::StopNeverDie()
{
	CCBFMediator::Instance()->StopNeverDie();
}