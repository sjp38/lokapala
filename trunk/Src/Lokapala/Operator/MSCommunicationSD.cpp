/**@file	MSCommunicationSD.cpp
 * @brief	MSM의 CommunicationSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "MSCommunicationSD.h"


/**@brief	CCM을 이용해서 텍스트 메세지를 랩터에게 보낸다.
 */
void CMSCommunicationSD::SendTextMessageToRaptor(void *a_messageData)
{
	CCBFMediator::Instance()->SendTextMessageToRaptor(a_messageData);
}
