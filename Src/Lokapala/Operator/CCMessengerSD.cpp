/**@file	CCMessengerSD.cpp
 * @brief	CCM�� MessengerSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "CCMessengerSD.h"

/**@brief	MSM���� �޼����� �����Ѵ�.
 */
void CCCMessengerSD::PresentMessage(void *a_messageData)
{
	CCBFMediator::Instance()->PresentMessage(a_messageData);
}