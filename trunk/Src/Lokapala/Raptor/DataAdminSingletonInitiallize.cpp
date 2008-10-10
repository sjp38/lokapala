/**@file	DataAdminSingletonInitiallize.cpp
 * @brief	Data Admin ������Ʈ�� ��� singleton�� �ʱ�ȭ�Ѵ�.
 * @author	siva
 */

#include "stdafx.h"

#include "DataAdminFacade.h"
#include "DataAdminManager.h"

CDataAdminFacade *CDataAdminFacade::m_instance = NULL;

CDataAdminManager *CDataAdminManager::m_instance = NULL;