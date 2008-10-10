/**@file	DataAdminFacade.cpp
 * @brief	DAM의 Facade의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DataAdminFacade.h"

#include "DataAdminManager.h"

/**@brief	사용자 정보를 입력한다. 사용자의 로그인 요청 시에 불려진다.
 */
void CDataAdminFacade::RegistUser(void *a_userInfo)
{
	CDataAdminManager::Instance()->RegistUser(a_userInfo);
}

/**@brief	사용자의 레벨을 입력한다. 사용자의 로그인 허락 시에 불려진다.
 */
void CDataAdminFacade::RegistUserLevel(int a_level)
{
	CDataAdminManager::Instance()->RegistUserLevel(a_level);
}

/**@brief	상태 변화를 기록한다.
 */
void CDataAdminFacade::ReportStatus(void *a_status)
{
	CDataAdminManager::Instance()->ReportStatus(a_status);
}