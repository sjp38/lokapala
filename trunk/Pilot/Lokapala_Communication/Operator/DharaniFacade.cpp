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

/**@brief	Ư�� Ŭ���̾�Ʈ���� �޼����� ������.
 * @param	a_sendData	���� �޼����� ���� Ŭ���̾�Ʈ�� �ּҸ� ������ �ִ�.
 */
void CDharaniFacade::DharaniSendTextMessageTo(CDharaniDTO *a_sendData)
{
	PTR_SOCKET_DATA destiny = CDharaniServerManager::Instance()->GetSocketByAddress(a_sendData->m_globalIp, a_sendData->m_localIp);
	CDharaniServerManager::Instance()->SendMessageTo(destiny, a_sendData->m_message);
}

/**@brief	����Ǿ� �ִ� ��� Ŭ���̾�Ʈ���� �޼����� ������.
 * @param	a_sendData	���� �޼����� ������ �ִ�.
 */
void CDharaniFacade::DharaniBroadcastTextMessage(CDharaniDTO *a_sendData)
{
	CDharaniServerManager::Instance()->BroadcastTextMessage(a_sendData->m_message);
}

/**@brief	�������� �޼����� ������.
 */
void CDharaniFacade::DharaniSendTextToServer(CDharaniDTO *a_sendData)
{
	CDharaniClientManager::Instance()->SendTextMessage(a_sendData->m_message);
}