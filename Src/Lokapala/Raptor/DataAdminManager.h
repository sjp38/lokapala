/**@file	DataAdminManager.h
 * @brief	CDataAdminManager 클래스를 정의한다.
 * @author	siva
 */

#ifndef DATA_ADMIN_MANAGER_H
#define DATA_ADMIN_MANAGER_H

#include "UserDTO.h"
#include "StatusReportsDTO.h"

/**@ingroup	GroupDAM
 * @class	CDataAdminManager
 * @brief	오퍼레이터에서 관리해야 할 데이터를 관리하며 실질적 행동을 한다.
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

	void SaveStatusReportsToFile(CString a_filePath);
	void LoadStatusReportsFromFile(CString a_filePath);

protected :
	CDataAdminManager(){}
	~CDataAdminManager(){}

private :
	static CDataAdminManager *m_instance;

	CUserDTO m_user;
	CStatusReportsDTO m_statusReports;
};


#endif