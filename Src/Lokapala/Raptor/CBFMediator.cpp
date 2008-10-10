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

/**@brief	사용자가, 또는 오퍼레이터로부터의 상태 변화 입력이 있었을 때, 상태를 저장한다.
 */
void CCBFMediator::ReportStatus(void *a_status)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->ReportStatus(a_status);
}




///////////////////////////////////////////////////////////////////////////////////////////////////
// DCM

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
void CCBFMediator::SendTextMessage(CString a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendTextMessage(a_message);
}

/**@brief	오퍼레이터에게 로그인 요청을 한다.
 */
void CCBFMediator::SendLoginRequest(void *a_userInfo)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendLoginRequest(a_userInfo);
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

/**@brief	DCM에게 실행된 프로세스를 알린다.
 * @param	a_executedProcess	실행된 프로세스의 이름
 */
void CCBFMediator::NotifyExecutedProcess(CString a_executedProcess)
{
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// OSM

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
void CCBFMediator::Logout()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Logout();
}

/**@brief	컴퓨터를 꺼버린다.
 */
void CCBFMediator::Shutdown()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Shutdown();
}

/**@brief	컴퓨터를 재부팅 시킨다.
 */
void CCBFMediator::Reboot()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->Reboot();
}

/**@brief	실행 중인 프로세스를 모조리 죽여버린다.
 */
void CCBFMediator::GenocideProcesses()
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->GenocideProcesses();
}

/**@brief	특정 이름의 프로세스를 죽인다.
 */
void CCBFMediator::KillProcess(CString *a_processName)
{
	CControlBI *_interface = CControlFacade::Instance();
	_interface->KillProcess(a_processName);
}

/**@brief	특정 이름의 프로세스를 실행시킨다.
 */
void CCBFMediator::ExecuteProcess(CString *a_processName)
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