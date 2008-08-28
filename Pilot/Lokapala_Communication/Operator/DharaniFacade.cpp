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


void CDharaniFacade::DharaniSend(CDharaniDTO *a_sendData)
{
}