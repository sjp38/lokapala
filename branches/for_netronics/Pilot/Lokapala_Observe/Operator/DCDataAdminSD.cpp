/**@file	DCDataAdminSD.cpp
 * @brief	DCM�� AdminSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCDataAdminSD.h"

/**@brief	DCM���� DAM������ service delegate �׽�Ʈ�� ��� �Լ�. ��ٷ� DAM�� ��û���� �ʰ�, mediator���� ��û�� �Ѵ�.
 */
void CDCDataAdminSD::ReadDAM()
{
	CCBFMediator::Instance()->ReadDAM();
}