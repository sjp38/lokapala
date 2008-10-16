/**@file	DCDataAdminSD.cpp
 * @brief	DCM�� AdminSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DCDataAdminSD.h"

/**@brief	DAM���κ��� ����� ��ü ������ ���´�.
 * @return	����� ��ü ���� DTO�� ������.
 */
void *CDCDataAdminSD::GetUsersDataDTO()
{
	return CCBFMediator::Instance()->GetUsers();
}


/**@brief	DAM���κ��� ���ӵ� ����� ��ü ������ ���´�.
 * @return	���ӵ� ����� ��ü ���� DTO �� ������.
 */
void *CDCDataAdminSD::GetConnectedUsersDTO()
{
	return CCBFMediator::Instance()->GetConnectedUsers();
}

/**@brief	DAM���κ��� ��Ģ ���� ��ü�� ���´�.
 */
void *CDCDataAdminSD::GetRulesDataDTO()
{
	return CCBFMediator::Instance()->GetRules();
}

/**@brief	DAM���κ��� �¼� ���� ��ü�� ���´�.
 */
void *CDCDataAdminSD::GetSeatsDataDTO()
{
	return CCBFMediator::Instance()->GetSeats();
}

/**@brief	DAM���κ��� ������� ���� ��ü�� ���´�.
 */
void *CDCDataAdminSD::GetStatusReportsDTO()
{
	return CCBFMediator::Instance()->GetStatusReports();
}