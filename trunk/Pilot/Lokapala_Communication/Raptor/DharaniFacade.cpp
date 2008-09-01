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
void CDharaniFacade::DharaniClientInitiallize()
{
	CDharaniClientManager::Instance()->Initiallize();
}

/**@brief	Ŭ���̾�Ʈ���� �޼����� ������.
 */
void CDharaniFacade::DharaniBroadcastText(CDharaniDTO *a_sendData)
{
	CDharaniServerManager::Instance()->BroadcastTextMessage(a_sendData->m_message);
}

/**@brief	�������� �޼����� ������.
 */
void CDharaniFacade::DharaniSendTextToServer(CDharaniDTO *a_sendData)
{
	CDharaniClientManager::Instance()->SendTextMessage(a_sendData->m_message);
}