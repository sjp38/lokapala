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
void CCBFMediator::InitiallizeCommunication()
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->Initiallize();
}