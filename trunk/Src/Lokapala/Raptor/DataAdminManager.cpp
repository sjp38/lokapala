#include "stdafx.h"
#include "DataAdminManager.h"

/**@brief	����� ������ �����Ѵ�. �α��� ��û �� �� �ҷ�����.
 */
void CDataAdminManager::RegistUser(void *a_user)
{
	CUserDTO *user = (CUserDTO *)a_user;
	m_user = *user;
}

/**@brief	����� ������ �����Ѵ�. �α��� ��û ��� �Ǿ��� �� �ҷ�����.
 */
void CDataAdminManager::RegistUserLevel(int a_level)
{
	m_user.m_level = a_level;
}


/**@brief	���� ��Ȳ ��ȭ ���� ����ü�� �����´�.
 * @return	��Ȳ ��ȭ ���� ����ü�� ������.
 */
void *CDataAdminManager::GetStatusReports()
{
	return &m_statusReports;
}