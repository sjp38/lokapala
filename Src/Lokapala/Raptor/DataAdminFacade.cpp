﻿/**@file	DataAdminFacade.cpp
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

/**@brief	상황 변화 보고를 가져온다.
 * @return	상황 변화 보고 정보체의 포인터.
 */
void *CDataAdminFacade::GetStatusReports()
{
	return CDataAdminManager::Instance()->GetStatusReports();
}

/**@brief	상태 보고를 추가한다.
 */
void CDataAdminFacade::AddStatusReport(void *a_statusReport)
{
	CDataAdminManager::Instance()->AddStatusReport(a_statusReport);
}

/**@brief	현재 상황 보고 내용을 파일로 저장한다.
 */
void CDataAdminFacade::SaveStatusReportsToFile(CString a_filePath)
{
	CDataAdminManager::Instance()->SaveStatusReportsToFile(a_filePath);
}

/**@brief	파일로부터 현재 상황 보고 내용을 읽어 온다.
 */
void CDataAdminFacade::LoadStatusReportsFromFile(CString a_filePath)
{
	CDataAdminManager::Instance()->LoadStatusReportsFromFile(a_filePath);
}
