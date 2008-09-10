/**@file	DharaniFacade.cpp
 * @brief	DharaniFacade�� ��� �Լ����� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DharaniClientManager.h"
#include "DharaniServerManager.h"
#include "DharaniFacade.h"

/**@brief	dharani ������Ʈ�� ���� �� �ʱ�ȭ. ���� ������ ����� IOCP�� ���� �غ� �ܰ踦 �����Ѵ�.
 */
void CDharaniFacade::DharaniServerInitiallize()
{
	CDharaniServerManager::Instance()->Initiallize();
}

/**@brief	dharani ������Ʈ�� Ŭ���̾�Ʈ �� �ʱ�ȭ.
 */
void CDharaniFacade::DharaniClientInitiallize(DWORD a_ServerAddress)
{
	CDharaniClientManager::Instance()->Initiallize(a_ServerAddress);
}

/**@brief	Ŭ���̾�Ʈ���� �޼����� ������.
 */
void CDharaniFacade::DharaniSendTextMessageTo(CDharaniDTO *a_sendData)
{
	if(a_sendData->m_globalIp == 0)
	{
		CDharaniServerManager::Instance()->BroadcastTextMessage(a_sendData->m_message);
	}
	else
	{
		PTR_SOCKET_DATA destiny = CDharaniServerManager::Instance()->GetSocketByAddress(a_sendData->m_globalIp, a_sendData->m_localIp);
		CDharaniServerManager::Instance()->SendMessageTo(destiny, a_sendData->m_message);
	}
}

/**@brief	�������� �޼����� ������.
 */
void CDharaniFacade::DharaniSendTextToServer(CDharaniDTO *a_sendData)
{
	CDharaniClientManager::Instance()->SendTextMessage(a_sendData->m_message);
}