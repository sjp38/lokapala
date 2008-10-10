/**@file	DataAdminManager.h
 * @brief	CDataAdminManager Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef DATA_ADMIN_MANAGER_H
#define DATA_ADMIN_MANAGER_H

#include "UserDTO.h"
#include "StatusReportsDTO.h"

/**@ingroup	GroupDAM
 * @class	CDataAdminManager
 * @brief	���۷����Ϳ��� �����ؾ� �� �����͸� �����ϸ� ������ �ൿ�� �Ѵ�.
 */
class CDataAdminManager
{
public :
	static CDataAdminManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDataAdminManager();
		}
		return m_instance;
	}

	void RegistUser(void *a_user);
	void RegistUserLevel(int a_level);
	void ReportStatus(void *a_status);

protected :
	CDataAdminManager(){}
	~CDataAdminManager(){}

private :
	static CDataAdminManager *m_instance;

	CUserDTO m_user;
	CStatusReportsDTO m_statusReports;
};


#endif