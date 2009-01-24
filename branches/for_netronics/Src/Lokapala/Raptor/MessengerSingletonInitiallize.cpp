#include "stdafx.h"

#include "MessengerFacade.h"
#include "MessengerManager.h"

#include "MSCommunicationSD.h"
#include "MSLogSD.h"

CMessengerFacade *CMessengerFacade::m_instance = NULL;
CMessengerManager *CMessengerManager::m_instance = NULL;

CMSCommunicationSD *CMSCommunicationSD::m_instance = NULL;
CMSLogSD *CMSLogSD::m_instance = NULL;