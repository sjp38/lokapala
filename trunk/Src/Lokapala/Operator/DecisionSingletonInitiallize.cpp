/**@brief	LGM에서 사용하는 싱글톤들을 초기화
 */


#include "stdafx.h"
#include "DecisionFacade.h"
#include "DecisionManager.h"
#include "DCDataAdminSD.h"
#include "DCLogSD.h"
#include "DCCommunicationSD.h"


CDecisionFacade *CDecisionFacade::m_instance = NULL;
CDecisionManager *CDecisionManager::m_instance = NULL;

CDCDataAdminSD *CDCDataAdminSD::m_instance = NULL;
CDCCommunicationSD *CDCCommunicationSD::m_instance = NULL;
CDCLogSD *CDCLogSD::m_instance = NULL;
