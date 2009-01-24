/**@file	DharaniExternSD.cpp
 * @brief	DharaniExternSD�� ����
 * @author	siva
 */

#include <atlconv.h>
#include "stdafx.h"
#include "Resource.h"
#include "DharaniExternSD.h"

#include "CommunicationManager.h"

/**@brief	Dharani�� �����ϰ� �Ǵ� Ŭ���̾�Ʈ�� �����͸� ���� ���, Ŭ���̾�Ʈ �ڵ� ���� �� ��ǰ� ���� ������ �˸���.
 * @param	a_receivedMessage		���۹��� �޼���
 * @remarks	Ŭ���̾�Ʈ ���� �Լ��̴�.
 */
void CDharaniExternSD::NotifyReceived(char *a_receivedMessage)
{
	USES_CONVERSION;
	CString message = A2W(a_receivedMessage);

	CCommunicationManager::Instance()->NotifyReceived(message);
}

/**@brief	Dharani�� �����ϰ� �Ǵ� Ŭ���̾�Ʈ�� �����͸� ���� ���, Ŭ���̾�Ʈ �ڵ� ���� �� ��ǰ� ���� ������ �˸���.
 *			������ ���� �ּҰ� �ʿ���, �� ������ ����� ��� ���Ǵ� �����ε� �Լ�.
 * @param	a_message		���۹��� �޼���
 * @param	a_localIp		�޼����� ������ Ŭ���̾�Ʈ�� ���� �ּ�
 * @param	a_globalIp		�޼����� ������ Ŭ���̾�Ʈ�� �۷ι� �ּ�
 * @remarks	���� ���� �Լ��̹Ƿ� ���Ϳ����� �������� �ʴ´�.
 */
void CDharaniExternSD::NotifyReceived(char *a_receivedMessage, in_addr a_localIp, in_addr a_globalIp)
{
}

/**@brief	������ ���ῡ ���������� �˸���.
 * @remarks	Ŭ���̾�Ʈ ���� �Լ���.
 */
void CDharaniExternSD::NotifyConnected()
{
	CCommunicationManager::Instance()->Connected();
}


/**@brief	�������� ������ �������� �˸���.
 * @remarks	Ŭ���̾�Ʈ ���� �Լ���.
 */
void CDharaniExternSD::NotifyDisconnected()
{
	CCommunicationManager::Instance()->Disconnected();
}

/**@brief	Ŭ���̾�Ʈ�κ����� ������ ����Ǿ����� �˸���.
 *			���������δ� ����� Ŭ���̾�Ʈ�� �ּ� ������ ǥ�� �� �˷��� ���̴�.
 * @param	a_globalIp	����� Ŭ���̾�Ʈ�� global ip
 * @param	a_localIp	����� Ŭ���̾�Ʈ�� local ip
 * @remarks	���� ���� �Լ��̹Ƿ� ���Ϳ����� �������� �ʴ´�.
 */
void CDharaniExternSD::NotifyAccepted(in_addr *a_globalIp, in_addr *a_localIp)
{
}

/**@brief	Ư�� Ŭ���̾�Ʈ�� ���� ���� ������ �˸���.
 *			���������δ� �ش� ip�� ����Ʈ�ڽ����� ��� ���� �� ���̴�.
 * @param	a_globalIp	���� ������ Ŭ���̾�Ʈ�� global ip
 * @param	a_localIp	���� ������ Ŭ���̾�Ʈ�� local Ip
 * @remarks	���� ���� �Լ��̹Ƿ� ���Ϳ����� �������� �ʴ´�.
 */
void CDharaniExternSD::NotifyLeft(in_addr *a_globalIp, in_addr *a_localIp)
{
}