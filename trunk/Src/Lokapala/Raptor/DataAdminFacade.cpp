/**@file	DataAdminFacade.cpp
 * @brief	DAM�� Facade�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DataAdminFacade.h"

#include "DataAdminManager.h"

/**@brief	����� ������ �Է��Ѵ�. ������� �α��� ��û �ÿ� �ҷ�����.
 */
void CDataAdminFacade::RegistUser(void *a_userInfo)
{
	CDataAdminManager::Instance()->RegistUser(a_userInfo);
}

/**@brief	������� ������ �Է��Ѵ�. ������� �α��� ��� �ÿ� �ҷ�����.
 */
void CDataAdminFacade::RegistUserLevel(int a_level)
{
	CDataAdminManager::Instance()->RegistUserLevel(a_level);
}

/**@brief	��Ȳ ��ȭ ���� �����´�.
 * @return	��Ȳ ��ȭ ���� ����ü�� ������.
 */
void *CDataAdminFacade::GetStatusReports()
{
	return CDataAdminManager::Instance()->GetStatusReports();
}