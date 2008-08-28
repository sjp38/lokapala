/**@file	CommunicationFacade.cpp
 * @brief	CCM�� Facade�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DharaniInterface.h"
#include "DharaniFacade.h"
#include "CommunicationFacade.h"


void CCommunicationFacade::Initiallize()
{
	CDharaniInterface *dharaniInterface;
	dharaniInterface = new CDharaniFacade();
	dharaniInterface->DharaniClientInitiallize();
}