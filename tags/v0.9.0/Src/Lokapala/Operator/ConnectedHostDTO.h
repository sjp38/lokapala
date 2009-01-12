/**@file	ConnectedHostDTO.h
 * @brief	CConnnectedHostDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef CONNECTED_HOST_DTO_H
#define CONNECTED_HOST_DTO_H

/**@ingroup	GroupDAM
 * @class	CConnectedHostDTO
 * @brief	���� ����� ����� ������ ������ ���´�.
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