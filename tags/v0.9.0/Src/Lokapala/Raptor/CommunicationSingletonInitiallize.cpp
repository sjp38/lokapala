/**@file	CommunicationSingletonInitiallize.cpp
 * @brief	CCM�� ��� �̱����� �ʱ�ȭ�� ���ش�.
 * @author	siva
 */

#include "stdafx.h"
#include "CommunicationFacade.h"
#include "CommunicationManager.h"
#include "CCDecisionSD.h"
#include "CCMessengerSD.h"

CCommunicationFacade *CCommunicationFacade::m_instance = NULL;
CCommunicationManager *CCommunicationManager::m_instance = NULL;

CCCDecisionSD *CCCDecisionSD::m_instance = NULL;
CCCMessengerSD *CCCMessengerSD::m_instance = NULL;