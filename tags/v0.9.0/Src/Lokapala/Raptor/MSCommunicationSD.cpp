/**@file	MSCommunicationSD.cpp
 * @brief	MSM�� CommunicationSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "MSCommunicationSD.h"

/**@brief	���۷����Ϳ��� �ؽ�Ʈ �޼����� �ѱ��.
 */
void CMSCommunicationSD::PostTextMessageToOperator(CString *a_message)
{
	CCBFMediator::Instance()->SendTextMessageToOperator(a_message);
}