/**@brief	MSM���� ����ϴ� �̱������ �ʱ�ȭ
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
