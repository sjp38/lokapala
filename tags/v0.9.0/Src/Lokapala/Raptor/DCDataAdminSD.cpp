/**@file	DCDataAdminSD.cpp
 * @brief	DCM�� AdminSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCDataAdminSD.h"


/**@brief	DAM���κ��� ������ ���� ���� ����ü�� ���´�.
 */
void *CDCDataAdminSD::GetStatusReportsDTO()
{
	return CCBFMediator::Instance()->GetStatusReports();
}

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

/**@brief	���� ������ �߰��Ѵ�.
 */
void CDCDataAdminSD::AddStatusReport(void *a_statusReport)
{
	CCBFMediator::Instance()->AddStatusReport(a_statusReport);
}

/**@brief	���� ���� ���� ������ ���Ϸ� �����Ѵ�.
 */
void CDCDataAdminSD::SaveStatusReportsToFile()
{
	CCBFMediator::Instance()->SaveStatusReportsToFile();
}