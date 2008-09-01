/**@file	CommunicationFacade.cpp
 * @brief	CCM�� Facade�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include <atlconv.h>
#include "CommunicationFacade.h"

/**@brief	����� ���� �ʱ�ȭ�� �Ѵ�.
 */
void CCommunicationFacade::Initiallize()
{
	CDharaniInterface *dharaniInterface;
	dharaniInterface = new CDharaniFacade();
	dharaniInterface->DharaniServerInitiallize();
}

/**@brief	���ڿ��� ������.
 */
void CCommunicationFacade::SendTextMessage(CString a_message)
{
	USES_CONVERSION;
	CDharaniDTO message;
	message.m_message = W2A(a_message);

	CDharaniInterface *dharaniInterface;
	dharaniInterface = new CDharaniFacade();
	dharaniInterface->DharaniBroadcastText(&message);
}