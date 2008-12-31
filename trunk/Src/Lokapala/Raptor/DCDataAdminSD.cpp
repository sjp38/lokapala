/**@file	DCDataAdminSD.cpp
 * @brief	DCM�� AdminSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCDataAdminSD.h"

/**@brief	DAM�� ���� ���͸� ����ϴ� ����� ������ ����Ѵ�.
 */
void CDCDataAdminSD::RegistUser(void *a_userInfo)
{
	CCBFMediator::Instance()->RegistUser(a_userInfo);
}

/**@brief	���� ���͸� ����ϴ� ����� ������ ������ ����Ѵ�.
 */
void CDCDataAdminSD::RegistUserLevel(int a_level)
{
	CCBFMediator::Instance()->RegistUserLevel(a_level);
}

/**@brief	���� ���� ���� ������ ���Ϸ� �����Ѵ�.
 */
void CDCDataAdminSD::SaveStatusReportsToFile( CString a_fileName )
{
	CCBFMediator::Instance()->SaveStatusReportsToFile(a_fileName);
}