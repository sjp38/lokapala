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
	void *GetStatusReports();

	void AddStatusReport(void *a_statusReport);
	void SaveStatusReportsToFile(CString a_filePath=_T("statusReports.xml"));
	void LoadStatusReportsFromFile(CString a_filePath=_T("statusReports.xml"));

protected :
	CDataAdminManager(){}
	~CDataAdminManager(){}

private :
	static CDataAdminManager *m_instance;

	CUserDTO m_user;
	CStatusReportsDTO m_statusReports;
};


#endif