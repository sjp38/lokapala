// stdafx.cpp : source file that includes just the standard includes
// Raptor.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


/**@brief	instance들의 초기값을 null로 잡아준다.
 */
#include "CBFMediator.h"

#include "DataAdminFacade.h"

#include "DecisionFacade.h"
#include "DCDataAdminSD.h"
#include "DCCommunicationSD.h"
#include "DCControlSD.h"
#include "DCLogSD.h"
#include "DCNeverDieSD.h"

#include "LogFacade.h"

#include "CommunicationFacade.h"
#include "CCDecisionSD.h"
#include "CCMessengerSD.h"

#include "MessengerFacade.h"
#include "MSCommunicationSD.h"
#include "MSLogSD.h"

#include "NeverDieFacade.h"
#include "NDDecisionSD.h"
#include "APIHookingManager.h"
#include "AutoExecuteManager.h"

#include "ObserveFacade.h"
#include "OSDecisionSD.h"

#include "ControlFacade.h"

//CBFMediator
CCBFMediator *CCBFMediator::m_instance = NULL;

//Facade
CDataAdminFacade *CDataAdminFacade::m_instance = NULL;
CDecisionFacade *CDecisionFacade::m_instance = NULL;
CLogFacade *CLogFacade::m_instance = NULL;
CCommunicationFacade *CCommunicationFacade::m_instance = NULL;
CMessengerFacade *CMessengerFacade::m_instance = NULL;
CNeverDieFacade *CNeverDieFacade::m_instance = NULL;
CObserveFacade *CObserveFacade::m_instance = NULL;
CControlFacade *CControlFacade::m_instance = NULL;

//Service Delegate
CDCDataAdminSD *CDCDataAdminSD::m_instance = NULL;
CDCCommunicationSD *CDCCommunicationSD::m_instance = NULL;
CDCControlSD *CDCControlSD::m_instance = NULL;
CDCLogSD *CDCLogSD::m_instance = NULL;
CDCNeverDieSD *CDCNeverDieSD::m_instance = NULL;

CCCDecisionSD *CCCDecisionSD::m_instance = NULL;
CCCMessengerSD *CCCMessengerSD::m_instance = NULL;

CMSCommunicationSD *CMSCommunicationSD::m_instance = NULL;
CMSLogSD *CMSLogSD::m_instance = NULL;

CNDDecisionSD *CNDDecisionSD::m_instance = NULL;

COSDecisionSD *COSDecisionSD::m_instance = NULL;



CAPIHookingManager *CAPIHookingManager::m_instance = NULL;
CAutoExecuteManager *CAutoExecuteManager::m_instance = NULL;