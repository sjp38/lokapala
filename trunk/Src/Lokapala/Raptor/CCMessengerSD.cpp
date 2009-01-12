/**@file	CCMessengerSD.cpp
 * @brief	CCM의 MessengerSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "CCMessengerSD.h"


/**@brief	텍스트 메세지 수신. 그냥 화면에 뿌려준다.
 */
void CCCMessengerSD::TexeMessageReceived(CString a_message)
{
	CString message = _T("[Operator]") + a_message;
	CCBFMediator::Instance()->Notify(&message);
}