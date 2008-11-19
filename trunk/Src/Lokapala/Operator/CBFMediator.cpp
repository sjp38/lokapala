/**@file	CBFMediator.cpp
 * @brief	Common Buisiness Framework Mediator.
 * @author	siva
 */

#include "stdafx.h"
#include "CBFMediator.h"

#include "Resource.h"

#include "DisplayDTO.h"
#include "StatusReportsDTO.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DCM

/**@brief	ȣ��Ʈ�� ��������.
 */
void CCBFMediator::HostConnected(void *a_hostData)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->HostConnected(a_hostData);
}

/**@brief	ȣ��Ʈ�� ������ ������. �α׾ƿ� ���� ���� �����ϴ�.
 */
void CCBFMediator::HostDisconnected(void *a_hostData)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->HostDisconnected(a_hostData);
}

/**@brief	����� �α��� ó��. �ùٸ� ��������� Ȯ���Ѵ�.
 * @param	a_loginRequestData	����� �α��� ������ ������. �ش� DTO�� ������������ void �����ͷ� ĳ���� �� ����Ѵ�.
 */
void CCBFMediator::JudgeLoginRequest(void *a_loginRequestData)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->JudgeLoginRequest(a_loginRequestData);
}

/**@brief	����ڰ� ������ ���μ����� ���� �ùٸ� ���μ������� ��� Ȯ��/ó���Ѵ�.
 */
void CCBFMediator::JudgeUserExecutedProcess(void *a_executedProcessData)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->JudgeUserExecutedProcess(a_executedProcessData);
}


/**@brief	���ο� ���� ���� ���� �޴´�.
 */
void CCBFMediator::PresentStatusReport(void *a_statusReportData)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->PresentStatusReport(a_statusReportData);
}


/**@brief	Ư�� ȣ��Ʈ�� ��ǻ�͸� �����Ų��.
 */
void CCBFMediator::ShutdownHost(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ShutdownHost(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� ��ǻ�͸� ������ ��Ų��.
 */
void CCBFMediator::RebootHost(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->RebootHost(a_argument);
}

/**@brief	Ư�� ������ ������ �α׾ƿ���Ų��.
 */
void CCBFMediator::BanUser(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->BanUser(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� Ư�� ���μ����� �����Ų��.
 */
void CCBFMediator::ExecuteHostProcess(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ExecuteHostProcess(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� Ư�� ���μ����� �����Ų��.
 */
void CCBFMediator::KillHostProcess(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->KillHostProcess(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� ��� ���μ����� �����Ų��.
 */
void CCBFMediator::GenocideHostProcess(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->GenocideHostProcess(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ���� ��� �Ѵ�.
 */
void CCBFMediator::WarnHost(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->WarnHost(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ���� ���� ���� ������.
 */
void CCBFMediator::SubmitStatusReportToHost(void *a_statusReport)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->SubmitStatusReportToHost(a_statusReport);
}






////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CCM

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


/**@brief	Ư�� �ּҷ� �α��� ��� �޼����� �����Ѵ�.
 * @param	a_acceptedData	�α��� ��� �޼����� �����ϴµ� �ʿ��� �������� ������.
 */
void CCBFMediator::SendLoginAcceptedNotifyMessage(void *a_acceptedData)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendLoginAcceptedNotifyMessage(a_acceptedData);
}

/**@brief	Ư�� ���� ��ǻ�͸� ��������.
 */
void CCBFMediator::SendShutdownInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendShutdownInstruction(a_argument);
}

/**@brief	Ư�� ������ ��ǻ�͸� ����ý�Ų��.
 */
void CCBFMediator::SendRebootInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendRebootInstruction(a_argument);
}

/**@brief	Ư�� ������ ���� �α׾ƿ� ��Ų��.
 */
void CCBFMediator::SendBanUserInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendBanUserInstruction(a_argument);
}

/**@brief	Ư�� �������� Ư�� ���μ����� �����Ų��.
 */
void CCBFMediator::SendExecuteProcessInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendExecuteProcessInstruction(a_argument);
}

void CCBFMediator::SendKillProcessInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendKillProcessInstruction(a_argument);
}

/**@brief	Ư�� ������ �������� ���μ��� ���θ� �׿�������.
 */
void CCBFMediator::SendGenocideProcessInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendGenocideProcessInstruction(a_argument);
}

/**@brief	Ư�� �������� ��� �޼����� ����.
 */
void CCBFMediator::SendWarningMessage(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendWarningMessage(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� ���� ���� ���� ������.
 */
void CCBFMediator::SendStatusReport(void *a_statusReport)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendStatusReport(a_statusReport);
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
void CCBFMediator::DeleteSeat(void *a_seat)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->DeleteSeat(a_seat);
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

/**@brief	���� ���� ���� ��ü�� ���´�.
 */
void *CCBFMediator::GetStatusReports()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetStatusReports();
}

/**@brief	���ӵ� ����� ��ü ������ ���´�.
 */
void *CCBFMediator::GetConnectedHosts()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetConnectedHosts();
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DAM

void CCBFMediator::PresentMessage(void *a_messageData)
{
	CMessengerBI *_interface = CMessengerFacade::Instance();
	_interface->ReceiveTextMessageFrom(a_messageData);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**@brief	���� ���̾�α��� �����͸� �����Ѵ�.
 */
void CCBFMediator::SetMainDlg(CDialog *a_pDlg)
{
	m_mainDlg = a_pDlg;
}


/**@brief	���� ����Ʈ�ڽ��� ���������� ǥ���Ѵ�.
 */
void CCBFMediator::Notify(CString *a_notifyMessage)
{
	void *notifyMessage = (void *)a_notifyMessage;
	SendMessage(m_mainDlg->m_hWnd, LKPLM_NOTIFYMESSAGE, (WPARAM)notifyMessage, NULL);
}

/**@brief	���ο� ������ �α����� �˸���.
 */
void CCBFMediator::NotifyRaptorLogin(CString *a_address)
{	
	CDisplayDTO displayData(*a_address, LOGIN);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&displayData, NULL);	
}

/**@brief	Ư�� ������ �α׾ƿ��� �˸���.
 */
void CCBFMediator::NotifyRaptorLogout(CString *a_address)
{	
	CDisplayDTO displayData(*a_address, LOGOUT);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&displayData, NULL);
}

/**@brief	Ư�� ���� ���μ����� ���������� �˸���.
 */
void CCBFMediator::NotifyRaptorExecutedProcess(CString *a_hostAddress, CString *a_executedProcess)
{	
	CDisplayDTO displayData(*a_hostAddress, CRIMINAL, *a_executedProcess);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&displayData, NULL);
}

/**@brief	��Ȳ ���� �˸���.
 */
void CCBFMediator::NotifyRaptorStatusChange(void *a_statusReports)
{
	CStatusReportDTOArray *statusReports = (CStatusReportDTOArray *)a_statusReports;
	if( (*statusReports)[0].m_state == VERIFIED )
	{
		CDisplayDTO displayData( (*statusReports)[0].m_hostAddress, FINE, _T(""));
		SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&displayData, NULL);
		return;
	}

	BOOL sw = FALSE;
	BOOL hw = FALSE;
	for(int i=0;i<statusReports->GetCount(); i++)
	{		
		if( (*statusReports)[i].m_state == SW_DEFECT )
		{
			sw = TRUE;
		}
		else if( (*statusReports)[i].m_state == HW_DEFECT )
		{
			hw = TRUE;
		}
	}

	enum DisplayState state;
	if(sw)
	{
		state = SW;
	}
	if(hw)
	{
		state = HW;
	}
	if(sw && hw)
	{
		state = HWSW;
	}
	if(!sw && !hw)
	{
		state = FINE;
	}
	
	CDisplayDTO displayData( (*statusReports)[0].m_hostAddress, state);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&displayData, NULL);
}

/**@brief	Ư�� ���ͷκ����� ���� ������ �������� �˸���.
 *			�̴� �� �α��� �õ����� �ǹ��Ѵ�.
 */
void CCBFMediator::NotifyRaptorAccepted(CString *a_address)
{
	CDisplayDTO display(*a_address, DISPLAY_CONNECTED);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}

/**@brief	Ư�� ���ͷκ����� ���� ������ ���������� �˸���.
 *			�̴� ���۷������� ���� �α׾ƿ��� ���ؼ��� ����, �ش� ������ ���� ������ ���ؼ��� ���� �ִ�.
 *			������ ��·�� �ش� ���ʹ� �α׾ƿ� ���¿� ������.
 */
void CCBFMediator::NotifyRaptorLeaved(CString *a_address)
{
	CDisplayDTO display(*a_address, DISPLAY_DISCONNECTED);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}

/**@brief	�¼��� ũ�� ������ �˸���.
 */
void CCBFMediator::NotifySeatResized(int a_maxX, int a_maxY)
{
	CDisplayDTO display(_T(""), SEATRESIZE, _T(""), a_maxX, a_maxY);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}


/**@brief	���ο� �¼��� �߰��� �˸���.
 */
void CCBFMediator::NotifySeatAdded(CString *a_seatId)
{
	CDisplayDTO display(*a_seatId, SEATADD);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}


/**@brief	�¼��� ������ �˸���.
 */
void CCBFMediator::NotifySeatDeleted(CString *a_seatId)
{
	CDisplayDTO display(*a_seatId, SEATDELETE);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}