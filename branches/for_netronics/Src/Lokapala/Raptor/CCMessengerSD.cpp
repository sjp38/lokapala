/**@file	CCMessengerSD.cpp
 * @brief	CCM�� MessengerSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "CCMessengerSD.h"


/**@brief	�ؽ�Ʈ �޼��� ����. �׳� ȭ�鿡 �ѷ��ش�.
 */
void CCCMessengerSD::TexeMessageReceived(CString a_message)
{
	CString message = _T("[Operator]") + a_message;
	CCBFMediator::Instance()->Notify(&message);
}