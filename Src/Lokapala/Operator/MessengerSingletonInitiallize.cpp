/**@brief	MSM에서 사용하는 싱글톤들을 초기화
 */


#include "stdafx.h"
#include "MessengerFacade.h"
#include "MessengerManager.h"
#include "MSCommunicationSD.h"
#include "MSLogSD.h"


//Facade
CMessengerFacade *CMessengerFacade::m_instance = NULL;

CMessengerManager *CMessengerManager::m_instance = NULL;

//Service Delegate
CMSLogSD *CMSLogSD::m_instance = NULL;
CMSCommunicationSD *CMSCommunicationSD::m_instance = NULL;
