﻿/**@file	CBFMediator.cpp
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

/**@brief	호스트가 접속했음.
 */
void CCBFMediator::HostConnected(void *a_hostData)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->HostConnected(a_hostData);
}

/**@brief	호스트가 접속을 끊었음. 로그아웃 했을 경우와 동일하다.
 */
void CCBFMediator::HostDisconnected(void *a_hostData)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->HostDisconnected(a_hostData);
}

/**@brief	사용자 로그인 처리. 올바른 사용자인지 확인한다.
 * @param	a_loginRequestData	사용자 로그인 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
 */
void CCBFMediator::JudgeLoginRequest(void *a_loginRequestData)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->JudgeLoginRequest(a_loginRequestData);
}

/**@brief	사용자가 실행한 프로세스에 대해 올바른 프로세스인지 어떤지 확인/처리한다.
 */
void CCBFMediator::JudgeUserExecutedProcess(void *a_executedProcessData)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->JudgeUserExecutedProcess(a_executedProcessData);
}


/**@brief	새로운 고장 상태 보고를 받는다.
 */
void CCBFMediator::PresentStatusReport(void *a_statusReportData)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->PresentStatusReport(a_statusReportData);
}


/**@brief	특정 호스트의 컴퓨터를 종료시킨다.
 */
void CCBFMediator::ShutdownHost(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ShutdownHost(a_argument);
}

/**@brief	특정 호스트의 컴퓨터를 리부팅 시킨다.
 */
void CCBFMediator::RebootHost(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->RebootHost(a_argument);
}

/**@brief	특정 유저를 강제로 로그아웃시킨다.
 */
void CCBFMediator::BanUser(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->BanUser(a_argument);
}

/**@brief	특정 호스트의 특정 프로세스를 실행시킨다.
 */
void CCBFMediator::ExecuteHostProcess(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->ExecuteHostProcess(a_argument);
}

/**@brief	특정 호스트의 특정 프로세스를 종료시킨다.
 */
void CCBFMediator::KillHostProcess(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->KillHostProcess(a_argument);
}

/**@brief	특정 호스트의 모든 프로세스를 종료시킨다.
 */
void CCBFMediator::GenocideHostProcess(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->GenocideHostProcess(a_argument);
}

/**@brief	특정 호스트에게 경고를 한다.
 */
void CCBFMediator::WarnHost(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->WarnHost(a_argument);
}

/**@brief	특정 호스트에게 상태 보고를 날린다.
 */
void CCBFMediator::SubmitStatusReportToHost(void *a_statusReport)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->SubmitStatusReportToHost(a_statusReport);
}

/**@brief	특정 호스트의 랩터 동작을 멈춘다.
 */
void CCBFMediator::TerminateRaptorOnHost(void *a_argument)
{
	CDecisionBI *_interface = CDecisionFacade::Instance();
	_interface->TerminateRaptorOnHost(a_argument);
}






////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CCM

/**@brief	CCM의 통신 초기화. 서버 구조를 구현하기 위해 리슨 소켓을 생성하고 랩터로부터의 연결 요청을 수락한다.
 * @remarks	다라니 컴포넌트 테스트 용.
 */
void CCBFMediator::BeginCommunication()
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->InitiallizeAsServer();
}

/**@brief	CCM을 이용해 문자를 방송한다. 연결되어 있는 모든 raptor에게 문자를 전송한다.
 * @param	a_message	방송할 문자.
 */
void CCBFMediator::BroadcastTextMessage(CString a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->BroadcastTextMessage(a_message);
}

/**@brief	CCM을 이용해서 문자를 전송한다.
 * @param	a_targetAddress	문자를 전송할 위치의 ip 주소.
 * @param	a_message	전송할 문자.
 */
void CCBFMediator::SendTextMessageTo(CString a_targetAddress, CString a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendTextMessageTo(a_targetAddress, a_message);
}


/**@brief	특정 주소로 로그인 허용 메세지를 전송한다.
 * @param	a_acceptedData	로그인 허용 메세지를 전송하는데 필요한 데이터의 포인터.
 */
void CCBFMediator::SendLoginAcceptedNotifyMessage(void *a_acceptedData)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendLoginAcceptedNotifyMessage(a_acceptedData);
}

/**@brief	특정 유저 컴퓨터를 꺼버린다.
 */
void CCBFMediator::SendShutdownInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendShutdownInstruction(a_argument);
}

/**@brief	특정 유저의 컴퓨터를 재부팅시킨다.
 */
void CCBFMediator::SendRebootInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendRebootInstruction(a_argument);
}

/**@brief	특정 유저를 강제 로그아웃 시킨다.
 */
void CCBFMediator::SendBanUserInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendBanUserInstruction(a_argument);
}

/**@brief	특정 유저에게 특정 프로세스를 실행시킨다.
 */
void CCBFMediator::SendExecuteProcessInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendExecuteProcessInstruction(a_argument);
}

void CCBFMediator::SendKillProcessInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendKillProcessInstruction(a_argument);
}

/**@brief	특정 유저의 실행중인 프로세스 전부를 죽여버린다.
 */
void CCBFMediator::SendGenocideProcessInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendGenocideProcessInstruction(a_argument);
}

/**@brief	특정 유저에게 경고 메세지를 띄운다.
 */
void CCBFMediator::SendWarningMessage(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendWarningMessage(a_argument);
}

/**@brief	특정 호스트로 고장 상태 보고를 날린다.
 */
void CCBFMediator::SendStatusReport(void *a_statusReport)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendStatusReport(a_statusReport);
}

/**@brief	특정 호스트로 랩터 동작 중지 명령을 날린다.
 */
void CCBFMediator::SendRaptorTerminationInstruction(void *a_argument)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendRaptorTerminationInstruction(a_argument);
}

/**@brief	특정 호스트로 메세지를 날린다(로카파라의 xml 포맷 패킷으로 만들어서 날린다).
 * @remarks	단순히 해당 문자열만을 날리는 SendTextMessageTo 와 구별하도록.
 */
void CCBFMediator::SendTextMessageToRaptor(void *a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendTextMessageToRaptor(a_message);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DAM

/**@brief	현재 DAM의 모든 데이터를 파일로 저장한다.
 */
void CCBFMediator::SaveDataAs(CString *a_filePath)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->SaveDataAs(a_filePath);
}

/**@brief	외부 파일로부터 데이터를 읽어들인다.
 */
void CCBFMediator::LoadDataFrom(CString *a_filePath)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->LoadDataFrom(a_filePath);
}

/**@brief	DAM에 유저를 추가한다.
 */
void CCBFMediator::AddUser(void *a_user)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->AddUser(a_user);
}

/**@brief	DAM에서 유저를 삭제한다.
 */
void CCBFMediator::DeleteUser(CString *a_id)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->DeleteUser(a_id);
}


/**@brief	유저 정보 전체를 알려준다.\n
 *			실제 유저 정보체의 구조를 모든 곳에서 알게 될 필요는 없으므로 포인터는 void 포인터로 캐스팅 되어 전달된다.\n
 *			최종 클라이언트 코드에서만 실제 유저 정보체의 구조를 알면(유저 정보체 헤더를 인클루드) 된다.
 * @return	void 포인터로 캐스팅 된 유저 정보 구조체의 포인터
 */
void *CCBFMediator::GetUsers()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetUsers();
}


/**@brief	좌석의 전체 크기를 설정한다.	*/
void CCBFMediator::SetSeats(int a_x, int a_y)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->SetSeats(a_x, a_y);
}

/**@brief	좌석 정보를 추가한다.	*/
void CCBFMediator::AddSeat(void *a_seat)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->AddSeat(a_seat);
}

/**@brief	좌석 정보를 삭제한다.	*/
void CCBFMediator::DeleteSeat(void *a_seat)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->DeleteSeat(a_seat);
}

/**@brief	전체 좌석 정보를 얻는다.
*			void 포인터로 캐스팅 되어 전달되므로 최종 클라이언트 코드에서만 실제 좌석 정보체 구조를 알면 된다.
*/
void *CCBFMediator::GetSeats()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetSeats();
}


/**@brief	금지 프로세스 관련 규칙을 하나 추가한다.
 */
void CCBFMediator::AddRule(void *a_rule)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->AddRule(a_rule);
}

/**@brief	금지 프로세스 관련 규칙을 하나 삭제한다.
 */
void CCBFMediator::DeleteRule(void *a_rule)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->DeleteRule(a_rule);
}

/**@brief	금지 프로세스 관련 규칙 전체를 얻어온다.
 */
void *CCBFMediator::GetRules()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetRules();
}

/**@brief	고장 상태 정보 전체를 얻어온다.
 */
void *CCBFMediator::GetStatusReports()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetStatusReports();
}

/**@brief	접속된 사용자 전체 정보를 얻어온다.
 */
void *CCBFMediator::GetConnectedHosts()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	return _interface->GetConnectedHosts();
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MSM

/**@brief	랩터에게 텍스트 메세지를 보낸다.
 */
void CCBFMediator::PostTextMessgeTo(void *a_messageData)
{
	CMessengerBI *_interface = CMessengerFacade::Instance();
	_interface->PostTextMessageTo(a_messageData);
}

/**@brief	랩터로부터 텍스트 메세지를 받았음을 알린다.
 */
void CCBFMediator::PresentMessage(void *a_messageData)
{
	CMessengerBI *_interface = CMessengerFacade::Instance();
	_interface->ReceiveTextMessageFrom(a_messageData);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**@brief	메인 다이얼로그의 포인터를 저장한다.
 */
void CCBFMediator::SetMainDlg(CDialog *a_pDlg)
{
	m_mainDlg = a_pDlg;
}


/**@brief	공지 리스트박스에 공지사항을 표시한다.
 */
void CCBFMediator::Notify(CString *a_notifyMessage)
{
	void *notifyMessage = (void *)a_notifyMessage;
	SendMessage(m_mainDlg->m_hWnd, LKPLM_NOTIFYMESSAGE, (WPARAM)notifyMessage, NULL);
}

/**@brief	새로운 랩터의 로그인을 알린다.
 */
void CCBFMediator::NotifyRaptorLogin(CString *a_address)
{	
	CDisplayDTO displayData(*a_address, LOGIN);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&displayData, NULL);	
}

/**@brief	특정 랩터의 로그아웃을 알린다.
 */
void CCBFMediator::NotifyRaptorLogout(CString *a_address)
{	
	CDisplayDTO displayData(*a_address, LOGOUT);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&displayData, NULL);
}

/**@brief	특정 금지 프로세스를 실행했음을 알린다.
 */
void CCBFMediator::NotifyRaptorExecutedProcess(CString *a_hostAddress, CString *a_executedProcess)
{	
	CDisplayDTO displayData(*a_hostAddress, CRIMINAL, *a_executedProcess);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&displayData, NULL);
}

/**@brief	상황 보고를 알린다.
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

/**@brief	특정 랩터로부터의 소켓 연결이 들어왔음을 알린다.
 *			이는 곧 로그인 시도임을 의미한다.
 */
void CCBFMediator::NotifyRaptorAccepted(CString *a_address)
{
	CDisplayDTO display(*a_address, DISPLAY_CONNECTED);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}

/**@brief	특정 랩터로부터의 소켓 연결이 끊어졌음을 알린다.
 *			이는 오퍼레이터의 강제 로그아웃에 의해서일 수도, 해당 랩터의 연결 해제에 의해서일 수도 있다.
 *			하지만 어쨌건 해당 랩터는 로그아웃 상태에 빠진다.
 */
void CCBFMediator::NotifyRaptorLeaved(CString *a_address)
{
	CDisplayDTO display(*a_address, DISPLAY_DISCONNECTED);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}

/**@brief	좌석의 크기 변경을 알린다.
 */
void CCBFMediator::NotifySeatResized(int a_maxX, int a_maxY)
{
	CDisplayDTO display(_T(""), SEATRESIZE, _T(""), a_maxX, a_maxY);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}


/**@brief	새로운 좌석의 추가를 알린다.
 */
void CCBFMediator::NotifySeatAdded(CString *a_seatId)
{
	CDisplayDTO display(*a_seatId, SEATADD);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}


/**@brief	좌석의 삭제를 알린다.
 */
void CCBFMediator::NotifySeatDeleted(CString *a_seatId)
{
	CDisplayDTO display(*a_seatId, SEATDELETE);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}

/**@brief	랩터로부터의 텍스트 메세지 도착을 유저에게 알린다.
 */
void CCBFMediator::NotifyRaptorMessageReceived(CString a_hostAddress, CString a_message)
{
	CDisplayDTO display(a_hostAddress, MESSAGE_FROM_RAPTOR_RECEIVED, a_message);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}

/**@brief	랩터에게 텍스트 메세지를 날렸음을 유저에게 알린다.
 */
void CCBFMediator::NotifyTextMessageToRaptorSended(CString a_hostAddress, CString a_message)
{
	CDisplayDTO display(a_hostAddress, MESSAGE_TO_RAPTOR_SENDED, a_message);
	SendMessage(m_mainDlg->m_hWnd, LKPLM_SHOWCHANGED, (WPARAM)&display, NULL);
}
