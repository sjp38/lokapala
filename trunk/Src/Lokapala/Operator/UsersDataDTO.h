/**@file	UsersDataDTO.h
 * @brief	모든 사용자의 정보들을 담는 DTO를 정의한다.
 * @author	siva
 */

#ifndef USERS_DATA_DTO_H
#define USERS_DATA_DTO_H

#include "UserDataDTO.h"
#include "DataAdminConstant.h"


/**@ingroup	DAM
 * @class	CUsersDataDTO
 * @brief	모든 유저의 정보를 갖는다.\n
 *			내부적으로 CUserDataDTO의 맵을 갖는다.
 */
class CUsersDataDTO
{
public :
	CMap <CString, LPCTSTR, CUserDataDTO, CUserDataDTO> m_users;

	void AddUser(CUserDataDTO *a_user);
	void DeleteUser(CString *a_id);
	void ClearUsers();
	CUserDataDTO *GetUserById(CString a_seatId);

	CUsersDataDTO();
	~CUsersDataDTO(){};

private :
	BOOL AlreadyExist(CString a_userId);
};

#endif
