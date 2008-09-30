/**@file	DataAdminManager.h
 * @brief	실질적으로 데이터를 관리하는 CDataAdminManager 클래스를 정의한다.
 * @author	siva
 */


#ifndef DATA_ADMIN_MANAGER_H
#define DATA_ADMIN_MANAGER_H


#include "UsersDataDTO.h"
#include "SeatsDataDTO.h"
#include "RulesDataDTO.h"

#include "ConnectedUsersDTO.h"
#include "StatusReportDTO.h"


/**@ingroup	GroupDAM
 * @class	CDataAdminManager
 * @brief	실질적인 데이터 관리를 한다.
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
	
	//with file
	void LoadFromFile(CString *a_filePath);
	void SaveToFile(CString *a_filePath);

	//user
	void AddUser(void *a_user);
	void DeleteUser(CString *a_id);
	CUsersDataDTO *GetUsers();

	//seat
	void SetSeats(int a_x, int a_y);
	void AddSeat(void *a_seat);
	void DeleteSeat(int a_x, int a_y);
	CSeatsDataDTO *GetSeats();

	//rule
	void AddRule(void *a_rule);
	void DeleteRule(void *a_rule);
	CRulesDataDTO *GetRules();

protected :
	CDataAdminManager(){}
	~CDataAdminManager(){}


private :	
	void LoadUserDataFrom(void *a_xmlRoot);
	void LoadSeatDataFrom(void *a_xmlRoot);
	void LoadRuleDataFrom(void *a_xmlRoot);

	void SaveUserDataTo(void *a_xmlRoot);
	void SaveSeatDataTo(void *a_xmlRoot);
	void SaveRuleDataTo(void *a_xmlRoot);

	CUsersDataDTO m_usersData;
	CSeatsDataDTO m_seatsData;
	CRulesDataDTO m_rulesData;

	CConnectedUsersDTO m_connectedUsers;

	static CDataAdminManager *m_instance;
	
};

#endif