/**@file	SingletonInitiallize.cpp
 * @brief	Dharani 컴포넌트에서 사용되는 싱글톤들을 NULL로 초기화한다.
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