// stdafx.cpp : source file that includes just the standard includes
// Raptor.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


/**@brief	instance들의 초기값을 null로 잡아준다.
 */
#include "CBFMediator.h"





#include "LogFacade.h"



#include "MessengerFacade.h"
#include "MSCommunicationSD.h"
#include "MSLogSD.h"

#include "NeverDieFacade.h"
#include "NDDecisionSD.h"
#include "APIHookingManager.h"
#include "AutoExecuteManager.h"

#include "ObserveFacade.h"
#include "OSDecisionSD.h"



//CBFMediator
CCBFMediator *CCBFMediator::m_instance = NULL;

//Facade


CLogFacade *CLogFacade::m_instance = NULL;

CMessengerFacade *CMessengerFacade::m_instance = NULL;
CNeverDieFacade *CNeverDieFacade::m_instance = NULL;
CObserveFacade *CObserveFacade::m_instance = NULL;

//Service Delegate




CMSCommunicationSD *CMSCommunicationSD::m_instance = NULL;
CMSLogSD *CMSLogSD::m_instance = NULL;

CNDDecisionSD *CNDDecisionSD::m_instance = NULL;

COSDecisionSD *COSDecisionSD::m_instance = NULL;



CAPIHookingManager *CAPIHookingManager::m_instance = NULL;
CAutoExecuteManager *CAutoExecuteManager::m_instance = NULL;