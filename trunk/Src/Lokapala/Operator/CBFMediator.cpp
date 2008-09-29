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




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DAM

/**@brief	���� DAM�� ��� �����͸� ���Ϸ� �����Ѵ�.
 */
void CCBFMediator::SaveDataAs(CString *a_filePath)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->SaveDataAs(a_filePath);
}

/**@brief	�ܺ� ���Ϸκ��� �����͸� �о���δ�.
 */
void CCBFMediator::LoadDataFrom(CString *a_filePath)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->LoadDataFrom(a_filePath);
}

/**@brief	DAM�� ������ �߰��Ѵ�.
 */
void CCBFMediator::AddUser(void *a_user)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->AddUser(a_user);
}

/**@brief	DAM���� ������ �����Ѵ�.
 */
void CCBFMediator::DeleteUser(CString *a_id)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->DeleteUser(a_id);
}


/**@brief	���� ���� ��ü�� �˷��ش�.\n
 *			���� ���� ����ü�� ������ ��� ������ �˰� �� �ʿ�� �����Ƿ� �����ʹ� void �����ͷ� ĳ���� �Ǿ� ���޵ȴ�.\n
 *			���� Ŭ���̾�Ʈ �ڵ忡���� ���� ���� ����ü�� ������ �˸�(���� ����ü ����� ��Ŭ���) �ȴ�.
 * @return	void �����ͷ� ĳ���� �� ���� ���� ����ü�� ������
 */
void *CCBFMediator::GetUsers()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetUsers();
}


/**@brief	�¼��� ��ü ũ�⸦ �����Ѵ�.	*/
void CCBFMediator::SetSeats(int a_x, int a_y)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->SetSeats(a_x, a_y);
}

/**@brief	�¼� ������ �߰��Ѵ�.	*/
void CCBFMediator::AddSeat(void *a_seat)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->AddSeat(a_seat);
}

/**@brief	�¼� ������ �����Ѵ�.	*/
void CCBFMediator::DeleteSeat(int a_x, int a_y)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->DeleteSeat(a_x, a_y);
}

/**@brief	��ü �¼� ������ ��´�.
*			void �����ͷ� ĳ���� �Ǿ� ���޵ǹǷ� ���� Ŭ���̾�Ʈ �ڵ忡���� ���� �¼� ����ü ������ �˸� �ȴ�.
*/
void *CCBFMediator::GetSeats()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetSeats();
}


/**@brief	���� ���μ��� ���� ��Ģ�� �ϳ� �߰��Ѵ�.
 */
void CCBFMediator::AddRule(void *a_rule)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->AddRule(a_rule);
}

/**@brief	���� ���μ��� ���� ��Ģ�� �ϳ� �����Ѵ�.
 */
void CCBFMediator::DeleteRule(void *a_rule)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->DeleteRule(a_rule);
}

/**@brief	���� ���μ��� ���� ��Ģ ��ü�� ���´�.
 */
void *CCBFMediator::GetRules()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetRules();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


