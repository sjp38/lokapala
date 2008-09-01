/**@file	CommunicationFacade.cpp
 * @brief	CCM�� Facade�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include <atlconv.h>
#include "DharaniInterface.h"
#include "DharaniFacade.h"
#include "CommunicationFacade.h"

/**@brief	������ ������ ��, ���۷����Ϳ��� connect �Ѵ�.
 */
void CCommunicationFacade::Initiallize()
{
	CDharaniInterface *dharaniInterface;
	dharaniInterface = new CDharaniFacade();
	dharaniInterface->DharaniClientInitiallize();
}


/**@brief	�ؽ�Ʈ �޼����� ���۷����Ϳ��� ������.
 */
void CCommunicationFacade::SendTextMessage(CString a_message)
{
	USES_CONVERSION;
	CDharaniDTO message;
	message.m_message = W2A(a_message);

	CDharaniInterface *dharaniInterface;
	dharaniInterface = new CDharaniFacade();
	dharaniInterface->DharaniSendTextToServer(&message);
}