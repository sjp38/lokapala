/**@file	DCDataAdminSD.cpp
 * @brief	DCM의 AdminSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCDataAdminSD.h"


/**@brief	DAM으로부터 현재의 상태 정보 정보체를 얻어온다.
 */
void *CDCDataAdminSD::GetStatusReportsDTO()
{
	return CCBFMediator::Instance()->GetStatusReports();
}

/**@brief	DAM에 현재 랩터를 사용하는 사용자 정보를 등록한다.
 */
void CDCDataAdminSD::RegistUser(void *a_userInfo)
{
	CCBFMediator::Instance()->RegistUser(a_userInfo);
}

/**@brief	현재 랩터를 사용하는 사용자 정보에 레벨을 등록한다.
 */
void CDCDataAdminSD::RegistUserLevel(int a_level)
{
	CCBFMediator::Instance()->RegistUserLevel(a_level);
}

/**@brief	상태 정보를 추가한다.
 */
void CDCDataAdminSD::AddStatusReport(void *a_statusReport)
{
	CCBFMediator::Instance()->AddStatusReport(a_statusReport);
}

/**@brief	현재 고장 상태 정보를 파일로 저장한다.
 */
void CDCDataAdminSD::SaveStatusReportsToFile()
{
	CCBFMediator::Instance()->SaveStatusReportsToFile();
}