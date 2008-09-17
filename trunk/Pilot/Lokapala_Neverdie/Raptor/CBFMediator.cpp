/**@file	CBFMediator.cpp
 * @brief	Common Buisiness Framework Mediator.
 * @author	siva
 */

#include "stdafx.h"
#include "CBFMediator.h"

/**@brief	컴포넌트 간 통신 테스트용 멤버함수. DAM으로부터 데이터를 읽는다.
 * @remarks		단순히 테스트용. 실질적으로 하는 일은 없다;
 */
void CCBFMediator::ReadDAM()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->Read();
}

/**@brief	CCM의 통신 초기화. 클라이언트 구조를 만들기 위해 소켓을 생성하고 오퍼레이터에게 connect 한다.
 * @remarks	다라니 컴포넌트 테스트 용.
 */
void CCBFMediator::InitiallizeCommunication(DWORD a_ServerAddress)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->Initiallize(a_ServerAddress);
}

/**@brief	특정 메세지를 오퍼레이터에게 전달한다.
 */
void CCBFMediator::SendTextMessage(CString a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendTextMessage(a_message);
}

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