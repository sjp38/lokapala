/**@file	DataAdminSingletonInitiallize.cpp
 * @brief	Data Admin 컴포넌트의 모든 singleton을 초기화한다.
 * @author	siva
 */

#include "stdafx.h"

#include "DataAdminFacade.h"
#include "DataAdminManager.h"

CDataAdminFacade *CDataAdminFacade::m_instance = NULL;

CDataAdminManager *CDataAdminManager::m_instance = NULL;
