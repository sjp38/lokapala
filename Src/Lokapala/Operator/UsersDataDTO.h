/**@file	UsersDataDTO.h
 * @brief	��� ������� �������� ��� DTO�� �����Ѵ�.
 * @author	siva
 */

#ifndef USERS_DATA_DTO_H
#define USERS_DATA_DTO_H

#include "UserDataDTO.h"
#include "DataAdminConstant.h"


/**@ingroup	DAM
 * @class	CUsersDataDTO
 * @brief	��� ������ ������ ���´�.\n
 *			���������� CUserDataDTO�� ���� ���´�.
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
};

#endif