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

/**@brief	CCM�� ��� �ʱ�ȭ. Ŭ���̾�Ʈ ������ ����� ���� ������ �����ϰ� ���۷����Ϳ��� connect �Ѵ�.
 * @remarks	�ٶ�� ������Ʈ �׽�Ʈ ��.
 */
void CCBFMediator::InitiallizeCommunication(DWORD a_ServerAddress)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->Initiallize(a_ServerAddress);
}

/**@brief	Ư�� �޼����� ���۷����Ϳ��� �����Ѵ�.
 */
void CCBFMediator::SendTextMessage(CString a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendTextMessage(a_message);
}

/**@brief	���� ���̾�α��� �����͸� ����
 */
void CCBFMediator::SetMainDlg(CDialog *a_pDlg)
{
	m_mainDlg = a_pDlg;
}

/**@brief	���� ���̾�α��� �����͸� ȹ��
 */
CDialog *CCBFMediator::GetMainDlg()
{
	return m_mainDlg;
}


/**@brief	���μ����� ���� ���� �ʰԲ� �Ѵ�.
 */
void CCBFMediator::StartNeverDie()
{
	CNeverDieBI *_interface = CNeverDieFacade::Instance();
	_interface->StartNeverDie();
}


/**@brief	���μ����� ���� �� �ְԲ� �Ѵ�.
 */
void CCBFMediator::StopNeverDie()
{
	CNeverDieBI *_interface = CNeverDieFacade::Instance();
	_interface->StopNeverDie();
}