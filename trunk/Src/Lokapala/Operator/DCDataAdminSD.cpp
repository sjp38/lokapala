/**@file	DCDataAdminSD.cpp
 * @brief	DCM의 AdminSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCDataAdminSD.h"

/**@brief	DAM으로부터 사용자 전체 정보를 얻어온다.
 * @return	사용자 전체 정보 DTO의 포인터.
 */
void *CDCDataAdminSD::GetUsersDataDTO()
{
	return CCBFMediator::Instance()->GetUsers();
}


/**@brief	DAM으로부터 접속된 사용자 전체 정보를 얻어온다.
 * @return	접속된 사용자 전체 정보 DTO 의 포인터.
 */
void *CDCDataAdminSD::GetConnectedUsersDTO()
{
	return CCBFMediator::Instance()->GetConnectedHosts();
}

/**@brief	DAM으로부터 규칙 정보 전체를 얻어온다.
 */
void *CDCDataAdminSD::GetRulesDataDTO()
{
	return CCBFMediator::Instance()->GetRules();
}

/**@brief	DAM으로부터 좌석 정보 전체를 얻어온다.
 */
void *CDCDataAdminSD::GetSeatsDataDTO()
{
	return CCBFMediator::Instance()->GetSeats();
}

/**@brief	DAM으로부터 고장상태 정보 전체를 얻어온다.
 */
void *CDCDataAdminSD::GetStatusReportsDTO()
{
	return CCBFMediator::Instance()->GetStatusReports();
}
