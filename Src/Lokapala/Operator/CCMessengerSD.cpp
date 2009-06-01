/**@file	CCMessengerSD.cpp
 * @brief	CCM의 MessengerSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "CCMessengerSD.h"

/**@brief	MSM에게 메세지를 전달한다.
 */
void CCCMessengerSD::PresentMessage(void *a_messageData)
{
	CCBFMediator::Instance()->PresentMessage(a_messageData);
}
