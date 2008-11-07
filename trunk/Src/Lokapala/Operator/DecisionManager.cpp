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
	//CDCCommunicationSD::Instance()->ReportStatus();
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
		LogoutUser(loginRequestData->m_hostAddress);
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
		CDCCommunicationSD::Instance()->ShutdownUser(&controlAction);
		break;
	case REBOOT :
		CDCCommunicationSD::Instance()->RebootUser(&controlAction);
		break;
	case LOGOUT :
		LogoutUser(controlAction.m_targetHostAddress);		
		break;
	case EXECUTE :
		CDCCommunicationSD::Instance()->ExecuteUser(&controlAction);
		break;
	case KILL :
		CDCCommunicationSD::Instance()->KillUser(&controlAction);
		break;
	case GENOCIDEPROCESSES :
		CDCCommunicationSD::Instance()->GenocideUser(&controlAction);
		break;
	case WARN :
		CDCCommunicationSD::Instance()->WarnUser(&controlAction);
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

/**@brief	������ ������ �α׾ƿ� ��Ų��.
 */
void CDecisionManager::LogoutUser(CString a_hostAddress)
{
	RemoveFromAcceptedUser(a_hostAddress);
	
	CControlActionDTO controlAction;
	controlAction.m_targetHostAddress = a_hostAddress;
	controlAction.m_reactionArgument = _T("");	
	CDCCommunicationSD::Instance()->LogoutUser(&controlAction);

	CString address = a_hostAddress;
	CCBFMediator::Instance()->NotifyRaptorLogout(&address);
}

/**@brief	Ư�� ������ ����� ���� ��Ͽ��� �����Ѵ�.
 */
void CDecisionManager::RemoveFromAcceptedUser(CString a_hostAddress)
{
	CConnectedHostsDTO *connectedUsers = (CConnectedHostsDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	CString seatId = a_hostAddress;
	connectedUsers->RemoveConnected(&seatId);
}