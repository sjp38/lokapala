/**@file	DecisionManager.cpp
 * @brief	CDecisionManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "DecisionManager.h"

#include "DCDataAdminSD.h"
#include "UsersDataDTO.h"
#include "LoginRequestDTO.h"
#include "ConnectedUsersDTO.h"
#include "DCCommunicationSD.h"

#include "RulesDataDTO.h"
#include "StatusReportsDTO.h"
#include "ExecutedProcessDTO.h"
#include "ReactionArgumentDTO.h"


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
	CConnectedUsersDTO *connectedUsers = (CConnectedUsersDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	CConnectedUserDTO user;
	user.m_userId = loginRequestData->m_lowLevelPassword;
	user.m_seatId = loginRequestData->m_hostAddress;
	connectedUsers->RegistConnected(&user);

	loginRequestData->m_level = userData->m_level;

	//DCCommunication SD�� �̿��� �α��� ��� �޼����� ������.
	CDCCommunicationSD::Instance()->NotifyAccepted(loginRequestData);		
	CCBFMediator::Instance()->NotifyRaptorLogin(&user.m_seatId);	
}


/**@brief	�꿡 ��õ� ������ ������ ���Ѵ�.
 */
void CDecisionManager::DoReactionTo(void *a_executedProcess, void *a_rule)
{
	CExecutedProcessDTO *executedProcess = (CExecutedProcessDTO *)a_executedProcess;

	CCBFMediator::Instance()->NotifyRaptorExecutedProcess(&executedProcess->m_executedHostAddress,
		&executedProcess->m_executedProcessName);

	CRuleDataDTO *rule = (CRuleDataDTO *)a_rule;
	CReactionArgumentDTO reactionArgument;
	reactionArgument.m_targetHostAddress = executedProcess->m_executedHostAddress;
	reactionArgument.m_reactionArgument = rule->m_reactionArgument;

	switch(rule->m_reaction)
	{
	case SHUTDOWN :
		CDCCommunicationSD::Instance()->ShutdownUser(&reactionArgument);
		break;
	case REBOOT :
		CDCCommunicationSD::Instance()->RebootUser(&reactionArgument);
		break;
	case LOGOUT :
		LogoutUser(executedProcess->m_executedHostAddress);		
		break;
	case EXECUTE :
		CDCCommunicationSD::Instance()->ExecuteUser(&reactionArgument);
		break;
	case GENOCIDEPROCESSES :
		CDCCommunicationSD::Instance()->GenocideUser(&reactionArgument);
		break;
	case WARN :
		CDCCommunicationSD::Instance()->WarnUser(&reactionArgument);
		break;
	}	
}

/**@brief	��鿡 ��õ� ������ ������ ���Ѵ�.
 */
void CDecisionManager::DoReactionsTo(void *a_executedProcess, void *a_rules)
{
	CRulesDataDTO *rules = (CRulesDataDTO *)a_rules;
	if(rules->m_rules.GetCount() > 0)
	{
		CExecutedProcessDTO *executedProcess = (CExecutedProcessDTO *)a_executedProcess;
		CCBFMediator::Instance()->NotifyRaptorExecutedProcess( &executedProcess->m_executedHostAddress, &executedProcess->m_executedProcessName); 
	}

	for(int i=0; i<rules->m_rules.GetCount(); i++)
	{
		DoReactionTo(a_executedProcess, &(rules->m_rules[i]));
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
	
	CReactionArgumentDTO reactionArgument;
	reactionArgument.m_targetHostAddress = a_hostAddress;
	reactionArgument.m_reactionArgument = _T("");	
	CDCCommunicationSD::Instance()->LogoutUser(&reactionArgument);

	CString address = a_hostAddress;
	CCBFMediator::Instance()->NotifyRaptorLogout(&address);
}

/**@brief	Ư�� ������ ����� ���� ��Ͽ��� �����Ѵ�.
 */
void CDecisionManager::RemoveFromAcceptedUser(CString a_hostAddress)
{
	CConnectedUsersDTO *connectedUsers = (CConnectedUsersDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	CString seatId = a_hostAddress;
	connectedUsers->RemoveConnected(&seatId);
}