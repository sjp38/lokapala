/**@file	ConnectedUserDTO.h
 * @brief	CConnnectedUserDataDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef CONNECTED_USER_DTO_H
#define CONNECTED_USER_DTO_H

/**@ingroup	GroupDAM
 * @class	CConnectedUserDTO
 * @brief	���� ����� ����� ������ ������ ���´�.
 */
class CConnectedUserDTO
{
public :
	CString m_userId;
	CString m_seatId;

	CConnectedUserDTO(CString a_user, CString a_seat);

	CConnectedUserDTO(){}
	~CConnectedUserDTO(){}
};

#endif