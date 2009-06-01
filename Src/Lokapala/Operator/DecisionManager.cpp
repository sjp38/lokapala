﻿/**@file	DecisionManager.cpp
 * @brief	CDecisionManager 클래스의 멤버함수를 구현한다.
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


/**@brief	호스트의 접속에 대해 처리한다.
 */
void CDecisionManager::HostConnected(void *a_hostData)
{
	CConnectedHostDTO *host = (CConnectedHostDTO *)a_hostData;
	CConnectedHostsDTO *connectedHosts = (CConnectedHostsDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	connectedHosts->RegistConnected(host);

	CCBFMediator::Instance()->NotifyRaptorAccepted(&host->m_hostAddress);
	ReportStatusTo(&host->m_hostAddress);
}

/**@brief	호스트의 접속 종료에 대해 처리한다.
 */
void CDecisionManager::HostDisconnected(void *a_hostData)
{
	CConnectedHostDTO *host = (CConnectedHostDTO *)a_hostData;
	RemoveFromAcceptedUser(host->m_hostAddress);

	CCBFMediator::Instance()->NotifyRaptorLogout(&host->m_hostAddress);
	CCBFMediator::Instance()->NotifyRaptorLeaved(&host->m_hostAddress);
}

/**@brief	특정 주소로 상태 보고를 날린다.
 */
void CDecisionManager::ReportStatusTo(CString *a_hostAddress)
{	
	CStatusReportsDTO *statusReports = (CStatusReportsDTO *)CDCDataAdminSD::Instance()->GetStatusReportsDTO();
	CStatusReportDTOArray nowReports;
	statusReports->GetReportFrom(*a_hostAddress, &nowReports);
	for(int i=0; i<nowReports.GetCount(); i++)
	{
		SubmitStatusReportToHost(&nowReports[i]);
	}
}


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

	//DCCommunication SD를 이용해 로그인 허용 메세지를 날린다.
	CDCCommunicationSD::Instance()->NotifyAccepted(loginRequestData);		
	CCBFMediator::Instance()->NotifyRaptorLogin(&user.m_hostAddress);	
}


/**@brief	룰에 명시된 반응을 실제로 행한다.
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

/**@brief	룰들에 명시된 반응을 실제로 행한다.
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

/**@brief	특정 유저를 연결된 유저 목록에서 제거한다.
 */
void CDecisionManager::RemoveFromAcceptedUser(CString a_hostAddress)
{
	CConnectedHostsDTO *connectedUsers = (CConnectedHostsDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
	CString seatId = a_hostAddress;
	connectedUsers->RemoveConnected(&seatId);
}


/**@brief	특정 호스트의 컴퓨터를 종료시킨다.
 */
void CDecisionManager::ShutdownHost(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendShutdownInstruction(a_argument);
}

/**@brief	특정 호스트의 컴퓨터를 리부팅시킨다.
 */
void CDecisionManager::RebootHost(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendRebootInstruction(a_argument);
}

/**@brief	특정 유저를 강제로 로그아웃 시킨다.
 */
void CDecisionManager::BanUser(void *a_argument)
{
	CString hostAddress = ((CControlActionDTO *)a_argument)->m_targetHostAddress;
	RemoveFromAcceptedUser(hostAddress);
	
	CDCCommunicationSD::Instance()->SendBanUserInstruction(a_argument);
	CCBFMediator::Instance()->NotifyRaptorLogout(&hostAddress);
}

/**@brief	특정 호스트의 특정 프로세스를 실행시킨다.
 */
void CDecisionManager::ExecuteHostProcess(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendExecuteProcessInstruction(a_argument);
}

/**@brief	특정 호스트의 특정 프로세스를 종료 시킨다.
 */
void CDecisionManager::KillHostProcess(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendKillProcessInstruction(a_argument);
}

/**@brief	특정 호스트의 모든 프로세스를 종료시킨다.
 */
void CDecisionManager::GenocideHostProcess(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendGenocideProcessInstruction(a_argument);
}

/**@brief	특정 호스트에게 경고를 날린다.
 */
void CDecisionManager::WarnHost(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendWarningMessage(a_argument);
}

/**@brief	특정 호스트에게 상태 보고를 날린다.
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

/**@brief	특정 호스트의 랩터를 동작 정지시킨다.
 */
void CDecisionManager::TerminateRaptorOnHost(void *a_argument)
{
	CDCCommunicationSD::Instance()->SendRaptorTerminationInstruction(a_argument);
}
