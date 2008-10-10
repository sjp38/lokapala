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