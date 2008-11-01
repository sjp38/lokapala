/**@file	DecisionManager.cpp
 * @brief	CDecisionManager 클래스의 멤버함수를 구현한다.
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


/**@brief	사용자 로그인 처리. 올바른 사용자인지 확인한다.
 * @param	a_loginRequestData	사용자 로그인 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
 */
void CDecisionManager::JudgeLoginRequest(void *a_loginRequestData)
{
	CLoginRequestDTO *loginRequestData;
	loginRequestData = (CLoginRequestDTO *)a_loginRequestData;

	//SD를 통해 DAM으로부터 사용자 정보를 얻어와 대조한다.
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

	//DCCommunication SD를 이용해 로그인 허용 메세지를 날린다.
	CDCCommunicationSD::Instance()->NotifyAccepted(loginRequestData);		
	CCBFMediator::Instance()->NotifyRaptorLogin(&user.m_seatId);	
}


/**@brief	룰에 명시된 반응을 실제로 행한다.
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

/**@brief	룰들에 명시된 반응을 실제로 행한다.
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

/**@brief	룰 데이터를 불러와 실행한 프로세스에 해당하는 항목이 있는 경우, 룰에 명시된 처리를 한다.
 */
void CDecisionManager::JudgeUserExecutedProcess(void *a_executedProcessData)
{
	CExecutedProcessDTO *executedProcessData = (CExecutedProcessDTO *)a_executedProcessData;

	CRulesDataDTO *rulesData = (CRulesDataDTO *)CDCDataAdminSD::Instance()->GetRulesDataDTO();
	CRulesDataDTO searchedRules;
	rulesData->GetReactionsFor(executedProcessData, &searchedRules);

	DoReactionsTo(executedProcessData, &searchedRules);
}


/**@brief	현재 상황 보고 데이터를 불러와 새로 보고된 내용을 넣는다.
 *			Verified 상태라면 이전의 기록을 모두 로그로 남기고, 지운다.
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

/**@brief	유저를 강제로 로그아웃 시킨다.
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

/**@brief	특정 유저를 연결된 유저 목록에서 제거한다.
 */
void CDecisionManager::RemoveFromAcceptedUser(CString a_hostAddress)
{
	CConnectedUsersDTO *connectedUsers = (CConnectedUsersDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	CString seatId = a_hostAddress;
	connectedUsers->RemoveConnected(&seatId);
}