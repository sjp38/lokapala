/**@file	MSCommunicationSD.cpp
 * @brief	MSM의 CommunicationSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "MSCommunicationSD.h"

/**@brief	오퍼레이터에게 텍스트 메세지를 넘긴다.
 */
void CMSCommunicationSD::PostTextMessageToOperator(CString *a_message)
{
	CCBFMediator::Instance()->SendTextMessageToOperator(a_message);
}
