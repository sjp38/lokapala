/**@file	CBFMediator.cpp
 * @brief	Common Buisiness Framework Mediator.
 * @author	siva
 */

#include "stdafx.h"
#include "CBFMediator.h"

#include "Resource.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// DAM

/**@brief	���� ����� ������ ����Ѵ�.
 *			�α��� ��û �� �̸�, ��� ��ȣ ���� ����ϸ�, ���� �α��� ��� �� ������ RegistUserLevel�� �߰� ����Ѵ�.
 */
void CCBFMediator::RegistUser(void *a_userInfo)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->RegistUser(a_userInfo);
}

/**@brief	�α����� ����Ǿ��� ��, ���� ������� ������ ����Ѵ�.
 */
void CCBFMediator::RegistUserLevel(int a_level)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->RegistUserLevel(a_level);
}

/**@brief	����ڰ�, �Ǵ� ���۷����ͷκ����� ���� ��ȭ �Է��� �־��� ��, ���¸� �����Ѵ�.
 */
void CCBFMediator::ReportStatus(void *a_status)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->ReportStatus(a_status);
}




///////////////////////////////////////////////////////////////////////////////////////////////////
// DCM

/**@brief	�α���. DCM���� �α��� ��Ź�� �ϵ��� ����Ѵ�.
 */
void CCBFMediator::LoginRequest(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->LoginRequest(a_userInfo);
}

/**@brief	�α����� ���Ǿ��� ��. ����� ���ظ� ���߰� ����� ������ �����Ѵ�.
 */
void CCBFMediator::LoginAccepted(int a_level)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->LoginAccepted(a_level);
}




///////////////////////////////////////////////////////////////////////////////////////////////////
// CCM

/**@brief	CCM�� ��� �ʱ�ȭ. Ŭ���̾�Ʈ ������ ����� ���� ������ �����ϰ� ���۷����Ϳ��� connect �Ѵ�.
 * @remarks	�ٶ�� ������Ʈ �׽�Ʈ ��.
 */
void CCBFMediator::InitiallizeCommunication(DWORD a_ServerAddress)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->Initiallize(a_ServerAddress);
}

/**@brief	���۷����Ϳ��� ������ ���´�.
 */
void CCBFMediator::CloseConnection()
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->CloseConnection();
}

/**@brief	Ư�� �޼����� ���۷����Ϳ��� �����Ѵ�.
 */
void CCBFMediator::SendTextMessage(CString a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendTextMessage(a_message);
}

/**@brief	���۷����Ϳ��� �α��� ��û�� �Ѵ�.
 */
void CCBFMediator::SendLoginRequest(void *a_userInfo)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendLoginRequest(a_userInfo);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ����

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



///////////////////////////////////////////////////////////////////////////////////////////////////
// NDM

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

/**@brief	���� ���μ����� �׾ �Ǵ��� ������ �ȵǴ����� �˷��ش�.
 * @return	�׾ �ȴٸ� FALSE, �׾ �ȵȴٸ� TRUE
 */
bool CCBFMediator::GetNeverDieState()
{
	CNeverDieBI *_interface = CNeverDieFacade::Instance();
	return _interface->GetNeverDieState();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// OSM

/**@brief	����Ǵ� ���μ��� ���ø� �����Ѵ�.
 */
void CCBFMediator::StartProcessObservation()
{
	CObserveBI *_interface = CObserveFacade::Instance();
	_interface->StartProcessObservation();
}

/**@brief	����Ǵ� ���μ��� ���ø� �����Ѵ�.
 */
void CCBFMediator::StopProcessObservation()
{
	CObserveBI *_interface = CObserveFacade::Instance();
	_interface->StopProcessObservation();
}

/**@brief	OSM���� ���� ����� ���μ��� �̸��� �˸���.
 * @param	a_executedProcess	���� ����� ���μ����� �̸�
 */
void CCBFMediator::ReceiveExecutedProcess(CString a_executedProcess)
{
	CObserveBI *_interface = CObserveFacade::Instance();
	_interface->ReceiveExecutedProcess(a_executedProcess);
}

/**@brief	DCM���� ����� ���μ����� �˸���.
 * @param	a_executedProcess	����� ���μ����� �̸�
 */
void CCBFMediator::NotifyExecutedProcess(CString a_executedProcess)
{
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// OSM

/**@brief	������� �������� ��ǻ�� ����� �����Ѵ�.
 */
void CCBFMediator::RestraintUser()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->RestraintUser();
}

/**@brief	������� �������� ��ǻ�� ����� ����Ѵ�.
 */
void CCBFMediator::ReleaseUser()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->ReleaseUser();
}

/**@brief	������ ������� �α����� ���ش�.
 */
void CCBFMediator::Login(void *a_userInfo)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Login(a_userInfo);
}

/**@brief	������ ����ڸ� �α׾ƿ� ��Ų��.
 */
void CCBFMediator::Logout()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Logout();
}

/**@brief	��ǻ�͸� ��������.
 */
void CCBFMediator::Shutdown()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Shutdown();
}

/**@brief	��ǻ�͸� ����� ��Ų��.
 */
void CCBFMediator::Reboot()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Reboot();
}

/**@brief	���� ���� ���μ����� ������ �׿�������.
 */
void CCBFMediator::GenocideProcesses()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->GenocideProcesses();
}

/**@brief	Ư�� �̸��� ���μ����� ���δ�.
 */
void CCBFMediator::KillProcess(CString *a_processName)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->KillProcess(a_processName);
}

/**@brief	Ư�� �̸��� ���μ����� �����Ų��.
 */
void CCBFMediator::ExecuteProcess(CString *a_processName)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->ExecuteProcess(a_processName);
}



///////////////////////////////////////////////////////////////////////////////
//common

/**@brief	Ư�� ������ ���� ����Ʈ�ڽ��� ���� ǥ���Ѵ�.
 */
void CCBFMediator::Notify(CString *a_message)
{
	CListBox *notifyList = (CListBox *)( m_mainDlg->GetDlgItem(IDC_NOTIFY_LIST) );
	notifyList->AddString(*a_message);
}