/**@file	DecisionSingletonInitiallize.cpp
 * @brief	DCM의 모든 싱글톤을 초기화한다.
 */

#include "stdafx.h"

#include "DecisionFacade.h"
#include "DecisionManager.h"

#include "DCDataAdminSD.h"
#include "DCCommunicationSD.h"
#include "DCControlSD.h"
#include "DCLogSD.h"
#include "DCNeverDieSD.h"

CDecisionFacade *CDecisionFacade::m_instance = NULL;
CDecisionManager *CDecisionManager::m_instance = NULL;

CDCDataAdminSD *CDCDataAdminSD::m_instance = NULL;
CDCCommunicationSD *CDCCommunicationSD::m_instance = NULL;
CDCControlSD *CDCControlSD::m_instance = NULL;
CDCLogSD *CDCLogSD::m_instance = NULL;
CDCNeverDieSD *CDCNeverDieSD::m_instance = NULL;
