/**@file	DecisionManager.cpp
 * @brief	CDecisionManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "DecisionManager.h"

#include "DCDataAdminSD.h"
#include "UsersDataDTO.h"
#include "LoginRequestDTO.h"
#include "ConnectedHostsDTO.h"
#include "DCCommunicationSD.h"

#include "RulesDataDTO.h"
#include "StatusReportsDTO.h"
#include "ExecutedProcessDTO.h"
#include "ControlActionDTO.h"


/**@brief	ȣ��Ʈ�� ���ӿ� ���� ó���Ѵ�.
 */
void CDecisionManager::HostConnected(void *a_hostData)
{
	CConnectedHostDTO *host = (CConnectedHostDTO *)a_hostData;
	CConnectedHostsDTO *connectedHosts = (CConnectedHostsDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	connectedHosts->RegistConnected(host);

	CCBFMediator::Instance()->NotifyRaptorAccepted(&host->m_hostAddress);
	ReportStatusTo(&host->m_hostAddress);
}

/**@brief	ȣ��Ʈ�� ���� ���ῡ ���� ó���Ѵ�.
 */
void CDecisionManager::HostDisconnected(void *a_hostData)
{
	CConnectedHostDTO *host = (CConnectedHostDTO *)a_hostData;
	RemoveFromAcceptedUser(host->m_hostAddress);

	CCBFMediator::Instance()->NotifyRaptorLogout(&host->m_hostAddress);
	CCBFMediator::Instance()->NotifyRaptorLeaved(&host->m_hostAddress);
}

/**@brief	Ư�� �ּҷ� ���� ���� ������.
 */
void CDecisionManager::ReportStatusTo(CString *a_hostAddress)
{
	CStatusReportsDTO *statusReports = (CStatusReportsDTO *)CCBFMediator::Instance()->GetStatusReports();
	CStatusReportDTOArray nowReports;
	statusReports->GetReportFrom(*a_hostAddress, &nowReports);
	for(int i=0; i<nowReports.GetCount(); i++)
	{
		SubmitStatusReportToHost(&nowReports[i]);
	}
}


/**@brief	����� �α��� ó��. �ùٸ� ��������� Ȯ���Ѵ�.
 * @param	a_loginRequestData	����� �α��� ������ ������. �ش� DTO�� ������������ void �����ͷ� ĳ���� �� ����Ѵ�.
 */
void CDecisionManager::JudgeLoginRequest(void *a_loginRequestData)
{
	CLoginRequestDTO *loginRequestData;
	loginRequestData = (CLoginRequestDTO *)a_loginRequestData;

	//SD�� ���� DAM���κ��� ����� ������ ���� �����Ѵ�.
	CUsersDataDTO *usersData;
	usersData = (CUsersDataDTO *)( CDCDataAdminSD::Instance()->GetUsersDataDTO() );
	CUserDataDTO *userData;
	userData = usersData->GetUserById( loginRequestData->m_lowLevelPassword );
	if(userData == NULL 
		|| userData->m_name != loginRequestData->m_name 
		|| userData->m_highLevelPassword != loginRequestData->m_highLevelPassword )
	{
		CControlActionDTO action;
		action.m_targetHostAddress = loginRequestData->m_hostAddress;
		BanUser(&action);
		return;
	}
	CConnectedHostsDTO *connectedUsers = (CConnectedHostsDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	CConnectedHostDTO user;
	user.m_userId = loginRequestData->m_lowLevelPassword;
	user.m_hostAddress = loginRequestData->m_hostAddress;
	connectedUsers->RegistConnected(&user);

	loginRequestData->m_level = userData->m_level;

	//DCCommunication SD�� �̿��� �α��� ��� �޼����� ������.
	CDCCommunicationSD::Instance()->NotifyAccepted(loginRequestData);		
	CCBFMediator::Instance()->NotifyRaptorLogin(&user.m_hostAddress);	
}


/**@brief	�꿡 ��õ� ������ ������ ���Ѵ�.
 */
void CDecisionManager::ControlRaptor(/*void *a_executedProcess, */void *a_controlAction)
{
	//CExecutedProcessDTO *executedProcess = (CExecutedProcessDTO *)a_executedProcess;

	//CCBFMediator::Instance()->NotifyRaptorExecutedProcess(&executedProcess->m_executedHostAddress,
	//	&executedProcess->m_executedProcessName);

	
	CControlActionDTO controlAction = *(CControlActionDTO *)a_controlAction;

	switch(controlAction.m_action)
	{
	case SHUTDOWN :
		ShutdownHost(a_controlAction);		
		break;
	case REBOOT :
		RebootHost(a_controlAction);
		break;
	case LOGOUT :
		BanUser(a_controlAction);
		break;
	case EXECUTE :
		ExecuteHostProcess(a_controlAction);
		break;
	case KILL :
		KillHostProcess(a_controlAction);
		break;
	case GENOCIDEPROCESSES :
		GenocideHostProcess(a_controlAction);
		break;
	case WARN :
		WarnHost(a_controlAction);
		break;
	}	
}

/**@brief	��鿡 ��õ� ������ ������ ���Ѵ�.
 */
void CDecisionManager::DoReactionsTo(void *a_executedProcess, void *a_rules)
{
	CRulesDataDTO *rules = (CRulesDataDTO *)a_rules;
	CExecutedProcessDTO *executedProcess = (CExecutedProcessDTO *)a_executedProcess;	
	if(rules->m_rules.GetCount() > 0)
	{		
		CCBFMediator::Instance()->NotifyRaptorExecutedProcess( &executedProcess->m_executedHostAddress, &executedProcess->m_executedProcessName); 
	}

	for(int i=0; i<rules->m_rules.GetCount(); i++)
	{
		CRuleDataDTO rule = rules->m_rules[i];
		CControlActionDTO controlAction;
		controlAction.m_targetHostAddress = executedProcess->m_executedHostAddress;
		controlAction.m_reactionArgument = rule.m_reactionArgument;
		controlAction.m_action = rule.m_reaction;
		ControlRaptor(&controlAction);
	}
}

/**@brief	�� �����͸� �ҷ��� ������ ���μ����� �ش��ϴ� �׸��� �ִ� ���, �꿡 ��õ� ó���� �Ѵ�.
 */
void CDecisionManager::JudgeUserExecutedProcess(void *a_executedProcessData)
{
	CExecutedProcessDTO *executedProcessData = (CExecutedProcessDTO *)a_executedProcessData;

	CRulesDataDTO *rulesData = (CRulesDataDTO *)CDCDataAdminSD::Instance()->GetRulesDataDTO();
	CRulesDataDTO searchedRules;
	rulesData->GetReactionsFor(executedProcessData, &searchedRules);

	DoReactionsTo(executedProcessData, &searchedRules);
}


/**@brief	���� ��Ȳ ���� �����͸� �ҷ��� ���� ����� ������ �ִ´�.
 *			Verified ���¶�� ������ ����� ��� �α׷� �����, �����.
 */
void CDecisionManager::PresentStatusReport(void *a_statusReportData)
{
	CStatusReportDTO *statusReport = (CStatusReportDTO *)a_statusReportData;
	CStatusReportsDTO *statusReports = (CStatusReportsDTO *)CDCDataAdminSD::Instance()->GetStatusReportsDTO();
	statusReports->AddReport(statusReport);

	CStatusReportDTOArray targetStatusReports;
	statusReports->GetReportFrom(statusReport->m_hostAddress, &targetStatusReports);

	CCBFMediator::Instance()->NotifyRaptorStatusChange(&targetStatusReports);
}

/**@brief	Ư�� ������ ����� ���� ��Ͽ��� �����Ѵ�.
 */
void CDecisionManager::RemoveFromAcceptedUser(CString a_hostAddress)
{
	CConnectedHostsDTO *connectedUsers = (CConnectedHostsDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	CString seatId = a_hostAddress;
	connectedUsers->RemoveConnected(&seatId);
}


/**@brief	Ư�� ȣ��Ʈ�� ��ǻ�͸� �����Ų��.
 */
void CDecisionManager::ShutdownHost(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendShutdownInstruction(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� ��ǻ�͸� �����ý�Ų��.
 */
void CDecisionManager::RebootHost(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendRebootInstruction(a_argument);
}

/**@brief	Ư�� ������ ������ �α׾ƿ� ��Ų��.
 */
void CDecisionManager::BanUser(void *a_argument)
{
	CString hostAddress = ((CControlActionDTO *)a_argument)->m_targetHostAddress;
	RemoveFromAcceptedUser(hostAddress);
	
	CDCCommunicationSD::Instance()->SendBanUserInstruction(a_argument);
	CCBFMediator::Instance()->NotifyRaptorLogout(&hostAddress);
}

/**@brief	Ư�� ȣ��Ʈ�� Ư�� ���μ����� �����Ų��.
 */
void CDecisionManager::ExecuteHostProcess(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendExecuteProcessInstruction(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� Ư�� ���μ����� ���� ��Ų��.
 */
void CDecisionManager::KillHostProcess(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendKillProcessInstruction(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ�� ��� ���μ����� �����Ų��.
 */
void CDecisionManager::GenocideHostProcess(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendGenocideProcessInstruction(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ���� ��� ������.
 */
void CDecisionManager::WarnHost(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendWarningMessage(a_argument);
}

/**@brief	Ư�� ȣ��Ʈ���� ���� ���� ������.
 */
void CDecisionManager::SubmitStatusReportToHost(void *a_statusReport)
{
	CStatusReportDTO *statusReport = (CStatusReportDTO *)a_statusReport;
	CStatusReportsDTO *statusReports = (CStatusReportsDTO *)CDCDataAdminSD::Instance()->GetStatusReportsDTO();
	
	CStatusReportDTOArray statusReportArray;
	statusReports->GetReportFrom(statusReport->m_hostAddress, &statusReportArray);
	CCBFMediator::Instance()->NotifyRaptorStatusChange(&statusReportArray);
	CDCCommunicationSD::Instance()->SendStatusReport(a_statusReport);
}