/**@file	MSCommunicationSD.cpp
 * @brief	MSM�� CommunicationSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "MSCommunicationSD.h"


/**@brief	CCM�� �̿��ؼ� �ؽ�Ʈ �޼����� ���Ϳ��� ������.
 */
void CMSCommunicationSD::SendTextMessageToRaptor(void *a_messageData)
{
	CCBFMediator::Instance()->SendTextMessageToRaptor(a_messageData);
}