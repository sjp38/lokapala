#include "stdafx.h"
#include "DataAdminManager.h"

/**@brief	사용자 정보를 저장한다. 로그인 요청 할 때 불려진다.
 */
void CDataAdminManager::RegistUser(void *a_user)
{
	CUserDTO *user = (CUserDTO *)a_user;
	m_user = *user;
}

/**@brief	사용자 레벨을 저장한다. 로그인 요청 허락 되었을 때 불려진다.
 */
void CDataAdminManager::RegistUserLevel(int a_level)
{
	m_user.m_level = a_level;
}

/**@brief	상태 변화 보고를 저장한다.
 */
void CDataAdminManager::ReportStatus(void *a_status)
{
}