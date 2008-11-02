/**@file	DCCommunicationSD.cpp
 * @brief	DCM의 CommunicationSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCCommunicationSD.h"


/**@brief	해당하는 주소의 사용자의 로그인 허용 메세지를 날린다.
 */
void CDCCommunicationSD::NotifyAccepted(void *a_acceptedData)
{
	CCBFMediator::Instance()->NotifyAccepted(a_acceptedData);
}


/**@brief	특정 유저의 컴퓨터를 꺼버린다.
 */
void CDCCommunicationSD::ShutdownUser(void *a_argument)
{
	CCBFMediator::Instance()->ShutdownUser(a_argument);
}

/**@brief	특정 유저의 컴퓨터를 재부팅 시킨다.
 */
void CDCCommunicationSD::RebootUser(void *a_argument)
{
	CCBFMediator::Instance()->RebootUser(a_argument);
}

/**@brief	특정 유저를 로그아웃 시킨다.
 */
void CDCCommunicationSD::LogoutUser(void *a_argument)
{
	CCBFMediator::Instance()->LogoutUser(a_argument);
}

/**@brief	특정 유저에게 특정 프로세스를 실행시킨다.
 */
void CDCCommunicationSD::ExecuteUser(void *a_argument)
{
	CCBFMediator::Instance()->ExecuteUser(a_argument);
}

/**@brief	특정 유저의 특정 프로세스를 종료시킨다.
 */
void CDCCommunicationSD::KillUser(void *a_argument)
{
	CCBFMediator::Instance()->KillUser(a_argument);
}

/**@brief	특정 유저가 실행하고 있는 모든 프로세스를 죽인다.
 */
void CDCCommunicationSD::GenocideUser(void *a_argument)
{
	CCBFMediator::Instance()->GenocideUser(a_argument);
}

/**@brief	특정 유저에게 경고 메세지를 넘긴다.
 */
void CDCCommunicationSD::WarnUser(void *a_argument)
{
	CCBFMediator::Instance()->WarnUser(a_argument);
}