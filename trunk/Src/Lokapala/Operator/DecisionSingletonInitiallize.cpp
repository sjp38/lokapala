/**@brief	LGM���� ����ϴ� �̱������ �ʱ�ȭ
 */


#include "stdafx.h"
#include "DecisionFacade.h"
#include "DCDataAdminSD.h"
#include "DCLogSD.h"
#include "DCCommunicationSD.h"


CDecisionFacade *CDecisionFacade::m_instance = NULL;

CDCDataAdminSD *CDCDataAdminSD::m_instance = NULL;
CDCCommunicationSD *CDCCommunicationSD::m_instance = NULL;
CDCLogSD *CDCLogSD::m_instance = NULL;