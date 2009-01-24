/**@file	SingletonInitiallize.cpp
 * @brief	Dharani ������Ʈ���� ���Ǵ� �̱������ NULL�� �ʱ�ȭ�Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
//Dharani
#include "DharaniFacade.h"
#include "DharaniServerManager.h"
#include "DharaniClientManager.h"
#include "DharaniExternSD.h"

CDharaniFacade *CDharaniFacade::m_instance = NULL;
CDharaniServerManager *CDharaniServerManager::m_instance = NULL;
CDharaniClientManager *CDharaniClientManager::m_instance = NULL;
CDharaniExternSD *CDharaniExternSD::m_instance = NULL;