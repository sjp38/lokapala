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
void CCBFMediator::NotifyAccepted(void *a_acceptedData)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->NotifyAccepted(a_acceptedData);
}

/**@brief	Ư�� ���� ��ǻ�͸� ��������.
 */
void CCBFMediator::ShutdownUser(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->ShutdownUser(a_argument);
}

/**@brief	Ư�� ������ ��ǻ�͸� ����ý�Ų��.
 */
void CCBFMediator::RebootUser(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->RebootUser(a_argument);
}

/**@brief	Ư�� ������ ���� �α׾ƿ� ��Ų��.
 */
void CCBFMediator::LogoutUser(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->LogoutUser(a_argument);
}

/**@brief	Ư�� �������� Ư�� ���μ����� �����Ų��.
 */
void CCBFMediator::ExecuteUser(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->ExecuteUser(a_argument);
}

void CCBFMediator::KillUser(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->KillUser(a_argument);
}

/**@brief	Ư�� ������ �������� ���μ��� ���θ� �׿�������.
 */
void CCBFMediator::GenocideUser(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->GenocideUser(a_argument);
}

/**@brief	Ư�� �������� ��� �޼����� ����.
 */
void CCBFMediator::WarnUser(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->WarnUser(a_argument);
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
void *CCBFMediator::GetConnectedUsers()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetConnectedUsers();
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
	CString message = *a_address + _T(" socket connected");
	Notify(&message);
}

/**@brief	Ư�� ���ͷκ����� ���� ������ ���������� �˸���.
 *			�̴� ���۷������� ���� �α׾ƿ��� ���ؼ��� ����, �ش� ������ ���� ������ ���ؼ��� ���� �ִ�.
 *			������ ��·�� �ش� ���ʹ� �α׾ƿ� ���¿� ������.
 */
void CCBFMediator::NotifyRaptorLeaved(CString *a_address)
{
	CString message = *a_address + _T(" socket disconnected");
	Notify(&message);
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