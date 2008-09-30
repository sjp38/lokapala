/**@file	ConnectedUsersDTO.h
 * @brief	CConnectedUsersDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef CONNECTED_USERS_DTO_H
#define CONNECTED_USERS_DTO_H

#include "ConnectedUserDTO.h"

/**@ingroup	GroupDAM
 * @class	CConnectedUsersDTO
 * @brief	����� ���� ��ü�� ���� �����͸� �����Ѵ�.
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