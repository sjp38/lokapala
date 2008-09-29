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
void CCBFMediator::DeleteSeat(int a_x, int a_y)
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->DeleteSeat(a_x, a_y);
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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**@brief	메인 다이얼로그의 포인터를 저장한다.
 */
void CCBFMediator::SetMainDlg(CDialog *a_pDlg)
{
	m_mainDlg = a_pDlg;
}


/**@brief	메인 다이얼로그의 포인터를 리턴한다.
 */
CDialog *CCBFMediator::GetMainDlg()
{
	return m_mainDlg;
}


