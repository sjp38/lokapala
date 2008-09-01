/**@file	SingletonInitiallize.cpp
 * @brief	Dharani ������Ʈ���� ���Ǵ� �̱������ NULL�� �ʱ�ȭ�Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
//Dharani
#include "DharaniServerManager.h"
#include "DharaniClientManager.h"
#include "DharaniExternSD.h"

CDharaniServerManager *CDharaniServerManager::m_instance = NULL;
CDharaniClientManager *CDharaniClientManager::m_instance = NULL;
CDharaniExternSD *CDharaniExternSD::m_instance = NULL;