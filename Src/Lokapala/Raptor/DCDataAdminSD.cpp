/**@file	DCDataAdminSD.cpp
 * @brief	DCM의 AdminSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCDataAdminSD.h"

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

/**@brief	현재 고장 상태 정보를 파일로 저장한다.
 */
void CDCDataAdminSD::SaveStatusReportsToFile( CString a_fileName )
{
	CCBFMediator::Instance()->SaveStatusReportsToFile(a_fileName);
}