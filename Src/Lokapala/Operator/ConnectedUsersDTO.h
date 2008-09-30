/**@file	ConnectedUsersDTO.h
 * @brief	CConnectedUsersDTO 클래스를 정의한다.
 * @author	siva
 */

#ifndef CONNECTED_USERS_DTO_H
#define CONNECTED_USERS_DTO_H

#include "ConnectedUserDTO.h"

/**@ingroup	GroupDAM
 * @class	CConnectedUsersDTO
 * @brief	연결된 유저 전체에 대한 데이터를 관리한다.
 */
class CConnectedUsersDTO
{
public :
	CArray<CConnectedUserDTO, CConnectedUserDTO> m_connected;
	void RegistConnected(CConnectedUserDTO *a_connected);
	void RemoveConnected(CString *a_connected);

private :
	int FindConnected(CString *a_key);
};


#endif