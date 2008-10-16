#include "stdafx.h"
#include "MessengerManager.h"

#include "MSCommunicationSD.h"
#include "MSLogSD.h"


/**@brief	���۷����Ϳ��� �ؽ�Ʈ �޼����� ������.
 */
void CMessengerManager::PostTextMessageToOperator(CString *a_message)
{
	CMSCommunicationSD::Instance()->PostTextMessageToOperator(a_message);
}

/**@brief	���۷����ͷκ��� �ؽ�Ʈ �޼����� �޾��� �� ȣ��ȴ�.
 */
void CMessengerManager::ReceiveTextMessageFromOperator(CString *a_message)
{
	CCBFMediator::Instance()->Notify(a_message);
}