#include "stdafx.h"
#include "MessengerManager.h"

#include "MSCommunicationSD.h"
#include "MSLogSD.h"


/**@brief	오퍼레이터에게 텍스트 메세지를 보낸다.
 */
void CMessengerManager::PostTextMessageToOperator(CString *a_message)
{
	CMSCommunicationSD::Instance()->PostTextMessageToOperator(a_message);
}

/**@brief	오퍼레이터로부터 텍스트 메세지를 받았을 때 호출된다.
 */
void CMessengerManager::ReceiveTextMessageFromOperator(CString *a_message)
{
	CCBFMediator::Instance()->Notify(a_message);
}
