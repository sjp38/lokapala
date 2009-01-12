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

/**@brief	���� �����ϰ� �ִ� ��Ȳ ����ü�� �����´�.
 * @return	��Ȳ ����ü�� ������.
 */
void *CCBFMediator::GetStatusReports()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetStatusReports();
}

/**@brief	���� ������ �߰��Ѵ�.
 */
void CCBFMediator::AddStatusReport(void *a_statusReport)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->AddStatusReport(a_statusReport);
}

/**@brief	���� ���� ������ ����(xml ����)�� �����Ѵ�.
 * @param	a_fileName	���� �̸�.
 */
void CCBFMediator::SaveStatusReportsToFile(CString a_filePath)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->SaveStatusReportsToFile(a_filePath);
}

/**@brief	Ư�� ����(xml ����)�κ��� ���� ���� ������ �ҷ��´�.
 * @param	a_fileName	���� �̸�.
 */
void CCBFMediator::LoadStatusReportsFromFile(CString a_filePath)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->LoadStatusReportsFromFile(a_filePath);
}




///////////////////////////////////////////////////////////////////////////////////////////////////
// DCM

/**@brief	���۷����Ϳ� ������ �Ǿ��� ��.
 */
void CCBFMediator::Connected()
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->Connected();
}

/**@brief	���۷����Ϳ��� ������ ������ ��.
 */
void CCBFMediator::Disconnected()
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->Disconnected();
}

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

/**@brief	���۷����ͷκ��� ���� �α��� ����� �������� ��.
 */
void CCBFMediator::LoginOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->LoginOrderReceived(a_userInfo);
}

/**@brief	���۷����ͷκ��� ���� �α׾ƿ� ����� �������� ��.
 */
void CCBFMediator::LogoutOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->LogoutOrderReceived(a_userInfo);
}

/**@brief	���۷����ͷκ��� ���� ��ǻ�� ���� ����� �������� ��.
 */
void CCBFMediator::ShutdownOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ShutdownOrderReceived(a_userInfo);
}

/**@brief	���۷����ͷκ��� ���� ��ǻ�� ����� ����� �������� ��.
 */
void CCBFMediator::RebootOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->RebootOrderReceived(a_userInfo);
}

/**@brief	���۷����ͷκ��� �������� ��� ���μ��� ���� ����� �������� ��.
 */
void CCBFMediator::GenocideProcessesOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->GenocideProcessesOrderReceived(a_userInfo);
}

/**@brief	���۷����ͷκ��� �������� Ư�� ���μ��� ���� ����� �������� ��.
 */
void CCBFMediator::KillProcessOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->KillProcessOrderReceived(a_userInfo);
}

/**@brief	���۷����ͷκ��� Ư�� ���μ��� ���� ����� �������� ��.
 */
void CCBFMediator::ExecuteProcessOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ExecuteProcessOrderReceived(a_userInfo);
}

/**@brief	���۷����ͷκ��� ���� ���� �������� ��.
 */
void CCBFMediator::StatusReportReceived(void *a_statusReport)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->StatusReportReceived(a_statusReport);
}

/**@brief	���۷����ͷκ��� ���� ���� ����� �������� ��.
 */
void CCBFMediator::RaptorTerminationOrderReceived()
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->RaptorTerminationOrderReceived();
}

/**@brief	����� ���μ��� �̸��� ����޴´�.
 */
void CCBFMediator::ReportExecutedProcess(CString *a_executedProcess)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ReportExecutedProcess(a_executedProcess);
}

/**@brief	����ڰ�, �Ǵ� ���۷����ͷκ����� ��Ȳ ��ȭ �Է��� �־��� ��, ��Ȳ�� �����Ѵ�.
 */
void CCBFMediator::ReportStatus(void *a_status)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ReportStatus(a_status);
}

/**@brief	����ڰ� ���α׷��� �����Ű�� �� ��.
 */
void CCBFMediator::UserTryingToKillMe()
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->UserTryingToKillMe();
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
void CCBFMediator::SendTextMessageToOperator(CString *a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendTextMessageToOperator(a_message);
}

/**@brief	���۷����Ϳ��� �α��� ��û�� �Ѵ�.
 */
void CCBFMediator::SendLoginRequest(void *a_userInfo)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendLoginRequest(a_userInfo);
}

/**@brief	���۷����Ϳ��� ����� ���μ��� ���� �����Ѵ�.
 */
void CCBFMediator::SendExecutedProcessReport(CString *a_executedProcess)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendExecutedProcessReport(a_executedProcess);
}

/**@brief	��Ȳ ��ȭ ���� ���۷����Ϳ��� �����Ѵ�.
 */
void CCBFMediator::SendStatusReport(void *a_statusReport)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendStatusReport(a_statusReport);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ����

/**@brief	MSM�� �̿��� �ؽ�Ʈ �޼����� ���۷����Ϳ��� ������.
 */
void CCBFMediator::PostTextMessageToOperator(CString *a_message)
{
	CMessengerBI *_interface = CMessengerFacade::Instance();
	_interface->PostTextMessageToOperator(a_message);
}

/**@brief	���۷����ͷκ��� �ؽ�Ʈ �޼����� �޾����� MSM���� �˸���.
 */
void CCBFMediator::ReceiveTextMessageFromOperator(CString *a_message)
{
	CMessengerBI *_interface = CMessengerFacade::Instance();
	_interface->ReceiveTextMessageFromOperator(a_message);
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

/**@brief	�α��� ���̾�α��� �����͸� ����
 */
void CCBFMediator::SetLoginDlg(CDialog *a_pDlg)
{
	m_loginDlg = a_pDlg;
}

/**@brief	�α��� ���̾�α��� �����͸� ȹ��
 */
CDialog *CCBFMediator::GetLoginDlg()
{
	return m_loginDlg;
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





////////////////////////////////////////////////////////////////////////////////////////////
// CTM

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
void CCBFMediator::Logout(void *a_message)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Logout(a_message);
}

/**@brief	��ǻ�͸� ��������.
 */
void CCBFMediator::Shutdown(void *a_message)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Shutdown(a_message);
}

/**@brief	��ǻ�͸� ����� ��Ų��.
 */
void CCBFMediator::Reboot(void *a_message)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Reboot(a_message);
}

/**@brief	���� ���� ���μ����� ������ �׿�������.
 */
void CCBFMediator::GenocideProcesses(void *a_message)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->GenocideProcesses(a_message);
}

/**@brief	Ư�� �̸��� ���μ����� ���δ�.
 */
void CCBFMediator::KillProcess(void *a_processName)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->KillProcess(a_processName);
}

/**@brief	Ư�� �̸��� ���μ����� �����Ų��.
 */
void CCBFMediator::ExecuteProcess(void *a_processName)
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


/**@brief	�����ο��� WM_CLOSE �޼����� ������.
 */
void CCBFMediator::TrySuicide()
{
	SendMessage(m_mainDlg->m_hWnd, WM_CLOSE, NULL, NULL);
}


/**@brief	��Ȳ ���� �޾����� �˸���. �α��� ���̾�α׿� �̸� ǥ���Ѵ�.
 */
void CCBFMediator::NotifyStatusReceived(void *a_statusReport)
{
	SendMessage(m_mainDlg->m_hWnd, LKPLM_STATUS_CHANGED, (WPARAM)a_statusReport, NULL);
	SendMessage(m_loginDlg->m_hWnd, LKPLM_STATUS_CHANGED, (WPARAM)a_statusReport, NULL);
}