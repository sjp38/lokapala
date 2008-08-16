// stdafx.cpp : source file that includes just the standard includes
// Operator.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


/**@brief	instance들의 초기값을 null로 잡아준다.
 */
#include "CBFMediator.h"
#include "DataAdminFacade.h"
#include "DecisionFacade.h"
#include "DataAdminSD.h"
#include "LogFacade.h"
#include "CommunicationFacade.h"
#include "MessengerFacade.h"

//CBFMediator
CCBFMediator *CCBFMediator::m_instance = NULL;

//Facade
CDataAdminFacade *CDataAdminFacade::m_instance = NULL;
CDecisionFacade *CDecisionFacade::m_instance = NULL;
CLogFacade *CLogFacade::m_instance = NULL;
CCommunicationFacade *CCommunicationFacade::m_instance = NULL;
CMessengerFacade *CMessengerFacade::m_instance = NULL;

//Service Delegate
CDataAdminSD *CDataAdminSD::m_instance = NULL;