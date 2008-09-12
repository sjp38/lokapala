/**@file	CBFMediator.cpp
 * @brief	Common Buisiness Framework Mediator.
 * @author	siva
 */

#include "stdafx.h"
#include "CBFMediator.h"

/**@brief	������Ʈ �� ��� �׽�Ʈ�� ����Լ�. DAM���κ��� �����͸� �д´�.
 * @remarks		�ܼ��� �׽�Ʈ��. ���������� �ϴ� ���� ����;
 */
void CCBFMediator::ReadDAM()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->Read();
}


/**@brief	CCM�� ��� �ʱ�ȭ. ���� ������ �����ϱ� ���� ���� ������ �����ϰ� ���ͷκ����� ���� ��û�� �����Ѵ�.
 * @remarks	�ٶ�� ������Ʈ �׽�Ʈ ��.
 */
void CCBFMediator::BeginCommunication()
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->InitiallizeAsServer();
}

/**@brief	CCM�� �̿��� ���ڸ� ����Ѵ�. ����Ǿ� �ִ� ��� raptor���� ���ڸ� �����Ѵ�.
 * @param	a_message	����� ����.
 */
void CCBFMediator::BroadcastTextMessage(CString a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->BroadcastTextMessage(a_message);
}

/**@brief	CCM�� �̿��ؼ� ���ڸ� �����Ѵ�.
 * @param	a_targetAddress	���ڸ� ������ ��ġ�� ip �ּ�.
 * @param	a_message	������ ����.
 */
void CCBFMediator::SendTextMessageTo(CString a_targetAddress, CString a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendTextMessageTo(a_targetAddress, a_message);
}


/**@brief	���� ���̾�α��� �����͸� �����Ѵ�.
 */
void CCBFMediator::SetMainDlg(CDialog *a_pDlg)
{
	m_mainDlg = a_pDlg;
}


/**@brief	���� ���̾�α��� �����͸� �����Ѵ�.
 */
CDialog *CCBFMediator::GetMainDlg()
{
	return m_mainDlg;
}