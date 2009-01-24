/**@file	ConnectedHostDTO.h
 * @brief	CConnnectedHostDTO 클래스를 정의한다.
 * @author	siva
 */

#ifndef CONNECTED_HOST_DTO_H
#define CONNECTED_HOST_DTO_H

/**@ingroup	GroupDAM
 * @class	CConnectedHostDTO
 * @brief	현재 연결된 사용자 개인의 정보를 갖는다.
 */
class CConnectedHostDTO
{
public :
	CString m_userId;
	CString m_hostAddress;

	CConnectedHostDTO(CString a_user, CString a_hostAddress);

	CConnectedHostDTO(){}
	~CConnectedHostDTO(){}
};

#endif