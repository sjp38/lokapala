/**@file	DCControlSD.cpp
 * @brief	DCM�� ControlSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCControlSD.h"

/**@brief	����ڸ� �����Ӱ� ��ǻ�͸� ��� �� �� �ֵ��� ���ش�.
 */
void CDCControlSD::ReleaseUser()
{
	CCBFMediator::Instance()->ReleaseUser();
}