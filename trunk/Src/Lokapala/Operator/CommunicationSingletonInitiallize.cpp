/**@brief	CCM에서 사용하는 싱글톤들을 초기화
 */


#include "stdafx.h"
#include "CommunicationFacade.h"
#include "CCDecisionSD.h"
#include "CCMessengerSD.h"


CCommunicationFacade *CCommunicationFacade::m_instance = NULL;
CCCDecisionSD *CCCDecisionSD::m_instance = NULL;
CCCMessengerSD *CCCMessengerSD::m_instance = NULL;