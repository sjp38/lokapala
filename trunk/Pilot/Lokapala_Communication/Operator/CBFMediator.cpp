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
	_interface->Initiallize();
}

void CCBFMediator::SendTextMessage(CString a_message)
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->SendTextMessage(a_message);
}


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