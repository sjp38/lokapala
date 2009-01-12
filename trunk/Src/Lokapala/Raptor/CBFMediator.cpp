/**@file	CBFMediator.cpp
 * @brief	Common Buisiness Framework Mediator.
 * @author	siva
 */

#include "stdafx.h"
#include "CBFMediator.h"

#include "Resource.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// DAM

/**@brief	현재 사용자 정보를 등록한다.
 *			로그인 요청 시 이름, 비밀 번호 등을 기록하며, 이후 로그인 허락 시 레벨은 RegistUserLevel로 추가 기록한다.
 */
void CCBFMediator::RegistUser(void *a_userInfo)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->RegistUser(a_userInfo);
}

/**@brief	로그인이 허락되었을 때, 현재 사용자의 레벨을 기록한다.
 */
void CCBFMediator::RegistUserLevel(int a_level)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->RegistUserLevel(a_level);
}

/**@brief	현재 관리하고 있는 상황 정보체를 가져온다.
 * @return	상황 정보체의 포인터.
 */
void *CCBFMediator::GetStatusReports()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetStatusReports();
}

/**@brief	상태 정보를 추가한다.
 */
void CCBFMediator::AddStatusReport(void *a_statusReport)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->AddStatusReport(a_statusReport);
}

/**@brief	현재 상태 정보를 파일(xml 포맷)로 저장한다.
 * @param	a_fileName	파일 이름.
 */
void CCBFMediator::SaveStatusReportsToFile(CString a_filePath)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->SaveStatusReportsToFile(a_filePath);
}

/**@brief	특정 파일(xml 포맷)로부터 현재 상태 정보를 불러온다.
 * @param	a_fileName	파일 이름.
 */
void CCBFMediator::LoadStatusReportsFromFile(CString a_filePath)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->LoadStatusReportsFromFile(a_filePath);
}




///////////////////////////////////////////////////////////////////////////////////////////////////
// DCM

/**@brief	오퍼레이터와 연결이 되었을 때.
 */
void CCBFMediator::Connected()
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->Connected();
}

/**@brief	오퍼레이터와의 연결이 끊겼을 때.
 */
void CCBFMediator::Disconnected()
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->Disconnected();
}

/**@brief	로그인. DCM에게 로그인 부탁을 하도록 명령한다.
 */
void CCBFMediator::LoginRequest(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->LoginRequest(a_userInfo);
}

/**@brief	로그인이 허용되었을 때. 사용자 방해를 멈추고 사용자 레벨을 저장한다.
 */
void CCBFMediator::LoginAccepted(int a_level)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->LoginAccepted(a_level);
}

/**@brief	오퍼레이터로부터 강제 로그인 명령이 내려왔을 때.
 */
void CCBFMediator::LoginOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->LoginOrderReceived(a_userInfo);
}

/**@brief	오퍼레이터로부터 강제 로그아웃 명령이 내려왔을 때.
 */
void CCBFMediator::LogoutOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->LogoutOrderReceived(a_userInfo);
}

/**@brief	오퍼레이터로부터 강제 컴퓨터 종료 명령이 내려왔을 때.
 */
void CCBFMediator::ShutdownOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ShutdownOrderReceived(a_userInfo);
}

/**@brief	오퍼레이터로부터 강제 컴퓨터 재부팅 명령이 내려왔을 때.
 */
void CCBFMediator::RebootOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->RebootOrderReceived(a_userInfo);
}

/**@brief	오퍼레이터로부터 실행중인 모든 프로세스 종료 명령이 내려왔을 때.
 */
void CCBFMediator::GenocideProcessesOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->GenocideProcessesOrderReceived(a_userInfo);
}

/**@brief	오퍼레이터로부터 실행중인 특정 프로세스 종료 명령이 내려왔을 때.
 */
void CCBFMediator::KillProcessOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->KillProcessOrderReceived(a_userInfo);
}

/**@brief	오퍼레이터로부터 특정 프로세스 실행 명령이 내려왔을 때.
 */
void CCBFMediator::ExecuteProcessOrderReceived(void *a_userInfo)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ExecuteProcessOrderReceived(a_userInfo);
}

/**@brief	오퍼레이터로부터 상태 보고가 내려왔을 때.
 */
void CCBFMediator::StatusReportReceived(void *a_statusReport)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->StatusReportReceived(a_statusReport);
}

/**@brief	오퍼레이터로부터 동작 정지 명령이 내려왔을 때.
 */
void CCBFMediator::RaptorTerminationOrderReceived()
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->RaptorTerminationOrderReceived();
}

/**@brief	실행된 프로세스 이름을 보고받는다.
 */
void CCBFMediator::ReportExecutedProcess(CString *a_executedProcess)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ReportExecutedProcess(a_executedProcess);
}

/**@brief	사용자가, 또는 오퍼레이터로부터의 상황 변화 입력이 있었을 때, 상황를 저장한다.
 */
void CCBFMediator::ReportStatus(void *a_status)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ReportStatus(a_status);
}

/**@brief	사용자가 프로그램을 종료시키려 할 때.
 */
void CCBFMediator::UserTryingToKillMe()
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->UserTryingToKillMe();
}




///////////////////////////////////////////////////////////////////////////////////////////////////
// CCM

/**@brief	CCM의 통신 초기화. 클라이언트 구조를 만들기 위해 소켓을 생성하고 오퍼레이터에게 connect 한다.
 * @remarks	다라니 컴포넌트 테스트 용.
 */
void CCBFMediator::InitiallizeCommunication(DWORD a_ServerAddress)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->Initiallize(a_ServerAddress);
}

/**@brief	오퍼레이터와의 연결을 끊는다.
 */
void CCBFMediator::CloseConnection()
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->CloseConnection();
}

/**@brief	특정 메세지를 오퍼레이터에게 전달한다.
 */
void CCBFMediator::SendTextMessageToOperator(CString *a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendTextMessageToOperator(a_message);
}

/**@brief	오퍼레이터에게 로그인 요청을 한다.
 */
void CCBFMediator::SendLoginRequest(void *a_userInfo)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendLoginRequest(a_userInfo);
}

/**@brief	오퍼레이터에게 실행된 프로세스 보고를 전달한다.
 */
void CCBFMediator::SendExecutedProcessReport(CString *a_executedProcess)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendExecutedProcessReport(a_executedProcess);
}

/**@brief	상황 변화 보고를 오퍼레이터에게 전송한다.
 */
void CCBFMediator::SendStatusReport(void *a_statusReport)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendStatusReport(a_statusReport);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// 공통 서비스

/**@brief	MSM을 이용해 텍스트 메세지를 오퍼레이터에게 보낸다.
 */
void CCBFMediator::PostTextMessageToOperator(CString *a_message)
{
	CMessengerBI *_interface = CMessengerFacade::Instance();
	_interface->PostTextMessageToOperator(a_message);
}

/**@brief	오퍼레이터로부터 텍스트 메세지를 받았음을 MSM에게 알린다.
 */
void CCBFMediator::ReceiveTextMessageFromOperator(CString *a_message)
{
	CMessengerBI *_interface = CMessengerFacade::Instance();
	_interface->ReceiveTextMessageFromOperator(a_message);
}






///////////////////////////////////////////////////////////////////////////////////////////////////
// 공통 서비스

/**@brief	메인 다이얼로그의 포인터를 저장
 */
void CCBFMediator::SetMainDlg(CDialog *a_pDlg)
{
	m_mainDlg = a_pDlg;
}

/**@brief	메인 다이얼로그의 포인터를 획득
 */
CDialog *CCBFMediator::GetMainDlg()
{
	return m_mainDlg;
}

/**@brief	로그인 다이얼로그의 포인터를 저장
 */
void CCBFMediator::SetLoginDlg(CDialog *a_pDlg)
{
	m_loginDlg = a_pDlg;
}

/**@brief	로그인 다이얼로그의 포인터를 획득
 */
CDialog *CCBFMediator::GetLoginDlg()
{
	return m_loginDlg;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// NDM

/**@brief	프로세스가 절대 죽지 않게끔 한다.
 */
void CCBFMediator::StartNeverDie()
{
	CNeverDieBI *_interface = CNeverDieFacade::Instance();
	_interface->StartNeverDie();
}


/**@brief	프로세스가 죽을 수 있게끔 한다.
 */
void CCBFMediator::StopNeverDie()
{
	CNeverDieBI *_interface = CNeverDieFacade::Instance();
	_interface->StopNeverDie();
}

/**@brief	현재 프로세스가 죽어도 되는지 죽으면 안되는지를 알려준다.
 * @return	죽어도 된다면 FALSE, 죽어선 안된다면 TRUE
 */
bool CCBFMediator::GetNeverDieState()
{
	CNeverDieBI *_interface = CNeverDieFacade::Instance();
	return _interface->GetNeverDieState();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// OSM

/**@brief	실행되는 프로세스 감시를 시작한다.
 */
void CCBFMediator::StartProcessObservation()
{
	CObserveBI *_interface = CObserveFacade::Instance();
	_interface->StartProcessObservation();
}

/**@brief	실행되는 프로세스 감시를 중지한다.
 */
void CCBFMediator::StopProcessObservation()
{
	CObserveBI *_interface = CObserveFacade::Instance();
	_interface->StopProcessObservation();
}

/**@brief	OSM에게 현재 실행된 프로세스 이름을 알린다.
 * @param	a_executedProcess	현재 실행된 프로세스의 이름
 */
void CCBFMediator::ReceiveExecutedProcess(CString a_executedProcess)
{
	CObserveBI *_interface = CObserveFacade::Instance();
	_interface->ReceiveExecutedProcess(a_executedProcess);
}





////////////////////////////////////////////////////////////////////////////////////////////
// CTM

/**@brief	사용자의 정상적인 컴퓨터 사용을 방해한다.
 */
void CCBFMediator::RestraintUser()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->RestraintUser();
}

/**@brief	사용자의 정상적인 컴퓨터 사용을 허락한다.
 */
void CCBFMediator::ReleaseUser()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->ReleaseUser();
}

/**@brief	강제로 사용자의 로그인을 해준다.
 */
void CCBFMediator::Login(void *a_userInfo)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Login(a_userInfo);
}

/**@brief	강제로 사용자를 로그아웃 시킨다.
 */
void CCBFMediator::Logout(void *a_message)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Logout(a_message);
}

/**@brief	컴퓨터를 꺼버린다.
 */
void CCBFMediator::Shutdown(void *a_message)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Shutdown(a_message);
}

/**@brief	컴퓨터를 재부팅 시킨다.
 */
void CCBFMediator::Reboot(void *a_message)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Reboot(a_message);
}

/**@brief	실행 중인 프로세스를 모조리 죽여버린다.
 */
void CCBFMediator::GenocideProcesses(void *a_message)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->GenocideProcesses(a_message);
}

/**@brief	특정 이름의 프로세스를 죽인다.
 */
void CCBFMediator::KillProcess(void *a_processName)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->KillProcess(a_processName);
}

/**@brief	특정 이름의 프로세스를 실행시킨다.
 */
void CCBFMediator::ExecuteProcess(void *a_processName)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->ExecuteProcess(a_processName);
}



///////////////////////////////////////////////////////////////////////////////
//common

/**@brief	특정 정보를 메인 리스트박스를 통해 표시한다.
 */
void CCBFMediator::Notify(CString *a_message)
{
	CListBox *notifyList = (CListBox *)( m_mainDlg->GetDlgItem(IDC_NOTIFY_LIST) );
	notifyList->AddString(*a_message);
}


/**@brief	스스로에게 WM_CLOSE 메세지를 던진다.
 */
void CCBFMediator::TrySuicide()
{
	SendMessage(m_mainDlg->m_hWnd, WM_CLOSE, NULL, NULL);
}


/**@brief	상황 보고를 받았음을 알린다. 로그인 다이얼로그에 이를 표시한다.
 */
void CCBFMediator::NotifyStatusReceived(void *a_statusReport)
{
	SendMessage(m_mainDlg->m_hWnd, LKPLM_STATUS_CHANGED, (WPARAM)a_statusReport, NULL);
	SendMessage(m_loginDlg->m_hWnd, LKPLM_STATUS_CHANGED, (WPARAM)a_statusReport, NULL);
}