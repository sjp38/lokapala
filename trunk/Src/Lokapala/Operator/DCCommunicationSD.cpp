/**@file	DCCommunicationSD.cpp
 * @brief	DCM�� CommunicationSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCCommunicationSD.h"


/**@brief	�ش��ϴ� �ּ��� ������� �α��� ��� �޼����� ������.
 */
void CDCCommunicationSD::NotifyAccepted(void *a_acceptedData)
{
	CCBFMediator::Instance()->NotifyAccepted(a_acceptedData);
}