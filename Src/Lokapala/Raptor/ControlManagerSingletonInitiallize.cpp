/**@file	ControlManagerSingletonInitiallize.cpp
 * @brief	Control Manager 컴포넌트의 모든 싱글톤을 초기화한다.
 * @author	siva
 */

#include "stdafx.h"
#include "ControlFacade.h"
#include "ControlManager.h"


CControlFacade *CControlFacade::m_instance = NULL;
CControlManager *CControlManager::m_instance = NULL;