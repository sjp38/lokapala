/**@file	DCCommunicationSD.cpp
 * @brief	DCM�� CommunicationSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCCommunicationSD.h"


/**@brief	Ŀ�´����̼� ������Ʈ���� �α��� ��ȣ�� �������� �Ѵ�.
 */
void CDCCommunicationSD::LoginRequest(void *a_userInfo)
{
	CCBFMediator::Instance()->SendLoginRequest(a_userInfo);
}