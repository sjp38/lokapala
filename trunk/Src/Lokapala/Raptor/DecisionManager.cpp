/**@file	DecisionManager.cpp
 * @brief	CDecisionManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "DecisionManager.h"

#include "DCCommunicationSD.h"
#include "DCDataAdminSD.h"
#include "DCControlSD.h"
#include "DCNeverDieSD.h"

#include "StatusReportsDTO.h"

/**@brief	오퍼레이터와 연결 되었을 때.
 *			현재 자신이 가지고 있는 상태 정보를 보낸다.
 */
void CDecisionManager::Connected()
{
	CStatusReportsDTO *statusReports = (CStatusReportsDTO *)CDCDataAdminSD::Instance()->GetStatusReportsDTO();
	CStatusReportDTOArray nowReports;
	nowReports.Copy(statusReports->m_reports);
	for(int i=0; i<nowReports.GetCount(); i++)
	{
		ReportStatus(&nowReports[i]);
	}
}

/**@brief	오퍼레이터와 연결이 끊겼을 때.
 *			자기 자신을 죽인다.
 */
void CDecisionManager::Disconnected()
{
	AfxMessageBox(_T("disconnected!"));
}

/**@brief	오퍼레이터에게 로그인 요청을 한다.	*/
void CDecisionManager::LoginRequest(void *a_userInfo)
{
	CDCDataAdminSD::Instance()->RegistUser(a_userInfo);
	CDCCommunicationSD::Instance()->LoginRequest(a_userInfo);
}

/**@brief	로그인 허용 메세지를 받았을 때.
 *			사용자 방해 행위를 중단하고, 사용자 레벨 정보 등을 기억한다.
 */
void CDecisionManager::LoginAccepted(int a_level)
{
	CDCDataAdminSD::Instance()->RegistUserLevel(a_level);
	CDCControlSD::Instance()->ReleaseUser();
	//AfxMessageBox(_T("login!!!"));
}

/**@brief	오퍼레이터로부터의 강제 로그인 명령에 대한 처리를 한다.
 */
void CDecisionManager::LoginOrderReceived(void *a_message)
{
	CDCControlSD::Instance()->Login(a_message);
}

/**@brief	오퍼레이터로부터의 강제 로그아웃 명령에 대한 처리를 한다.
 */
void CDecisionManager::LogoutOrderReceived(void *a_message)
{
	CDCControlSD::Instance()->Logout(a_message);
}

/**@brief	오퍼레이터로부터의 강제 컴퓨터 종료 명령에 대한 처리를 한다.
 */
void CDecisionManager::ShutdownOrderReceived(void *a_message)
{
	CDCControlSD::Instance()->Shutdown(a_message);
}

/**@brief	오퍼레이터로부터의 강제 컴퓨터 리부팅 명령에 대한 처리를 한다.
 */
void CDecisionManager::RebootOrderReceived(void *a_message)
{
	CDCControlSD::Instance()->Reboot(a_message);
}

/**@brief	오퍼레이터로부터의 실행중인 모든 프로세스 종료 명령에 대한 처리를 한다.
 */
void CDecisionManager::GenocideProcessesOrderReceived(void *a_message)
{
	CDCControlSD::Instance()->GenocideProcesses(a_message);
}

/**@brief	오퍼레이터로부터의 특정 프로세스 종료 명령에 대한 처리를 한다.
 */
void CDecisionManager::KillProcessOrderReceived(void *a_processName)
{
	CDCControlSD::Instance()->KillProcess(a_processName);
}

/**@brief	오퍼레이터로부터의 특정 프로세스 실행 명령에 대한 처리를 한다.
 */
void CDecisionManager::ExecuteProcessOrderReceived(void *a_processName)
{
	CDCControlSD::Instance()->ExecuteProcess(a_processName);
}

/**@brief	오퍼레이터로부터 상태 정보를 받았을 때.
 */
void CDecisionManager::StatusReportReceived(void *a_statusReport)
{
	CDCDataAdminSD::Instance()->AddStatusReport(a_statusReport);	
}

/**@brief	오퍼레이터로부터 랩터 동작 종료 명령을 받았을 때. 네버다이 모드를 풀고, 죽는다.
 */
void CDecisionManager::RaptorTerminationOrderReceived()
{
	CDCNeverDieSD::Instance()->StopNeverDie();
	CCBFMediator::Instance()->TrySuicide();
}




/**@brief	실행된 프로세스 이름을 보고 받는다.
 *			CCM을 이용해 오퍼레이터에게 보고한다.
 */
void CDecisionManager::ReportExecutedProcess(CString *a_executedProcess)
{
	CDCCommunicationSD::Instance()->ReportExecutedProcess(a_executedProcess);
}

void CDecisionManager::ReportStatus(void *a_status)
{
	CDCCommunicationSD::Instance()->ReportStatus(a_status);
}

/**@brief	사용자가 프로그램을 종료 하고자 한 경우.
 *			종료에 대한 처리는 다이얼로그에서 한다. 여기선, 현재 고장 상태(state reports)를 파일로 저장한다.
 */
void CDecisionManager::UserTryingToKillMe()
{
	CDCDataAdminSD::Instance()->SaveStatusReportsToFile();
}
