/**@file	ConnectedUserDTO.h
 * @brief	CConnnectedUserDataDTO 클래스를 정의한다.
 * @author	siva
 */

#ifndef CONNECTED_USER_DTO_H
#define CONNECTED_USER_DTO_H

/**@ingroup	GroupDAM
 * @class	CConnectedUserDTO
 * @brief	현재 연결된 사용자 개인의 정보를 갖는다.
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