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
		LogoutUser(loginRequestData->m_globalIp, loginRequestData->m_localIp);
		return;
	}
	CConnectedUsersDTO *connectedUsers = (CConnectedUsersDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	CConnectedUserDTO user;
	user.m_userId = loginRequestData->m_lowLevelPassword;
	user.m_seatId = loginRequestData->m_globalIp + _T("/") + loginRequestData->m_localIp;
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
	CExecutedProcessDTO *executedProcess = (CExecutedProcessDTO *)a_executedProcess;;

	CRuleDataDTO *rule = (CRuleDataDTO *)a_rule;
	CReactionArgumentDTO reactionArgument;
	reactionArgument.m_targetGlobalIp = executedProcess->m_executedGlobalIp;
	reactionArgument.m_targetLocalIp = executedProcess->m_executedLocalIp;
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
		LogoutUser(executedProcess->m_executedGlobalIp, executedProcess->m_executedLocalIp);		
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
}

/**@brief	������ ������ �α׾ƿ� ��Ų��.
 */
void CDecisionManager::LogoutUser(CString a_globalIp, CString a_localIp)
{
	RemoveFromAcceptedUser(a_globalIp, a_localIp);
	
	CReactionArgumentDTO reactionArgument;
	reactionArgument.m_targetGlobalIp = a_globalIp;
	reactionArgument.m_targetLocalIp = a_localIp;
	reactionArgument.m_reactionArgument = _T("");	
	CDCCommunicationSD::Instance()->LogoutUser(&reactionArgument);

	CString address = a_globalIp + _T("/") + a_localIp;
	CCBFMediator::Instance()->NotifyRaptorLogout(&address);
}

/**@brief	Ư�� ������ ����� ���� ��Ͽ��� �����Ѵ�.
 */
void CDecisionManager::RemoveFromAcceptedUser(CString a_globalIp, CString a_localIp)
{
	CConnectedUsersDTO *connectedUsers = (CConnectedUsersDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	CString seatId = a_globalIp + _T("/") + a_localIp;
	connectedUsers->RemoveConnected(&seatId);
}