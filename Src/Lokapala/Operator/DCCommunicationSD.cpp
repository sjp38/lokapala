/**@file	DCCommunicationSD.cpp
 * @brief	DCM의 CommunicationSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCCommunicationSD.h"


/**@brief	해당하는 주소의 사용자의 로그인 허용 메세지를 날린다.
 */
void CDCCommunicationSD::NotifyAccepted(void *a_acceptedData)
{
	CCBFMediator::Instance()->NotifyAccepted(a_acceptedData);
}