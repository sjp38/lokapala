/**@file	ConnectedHostsDTO.h
 * @brief	CConnectedHostsDTO 클래스를 정의한다.
 * @author	siva
 */

#ifndef CONNECTED_HOSTS_DTO_H
#define CONNECTED_HOSTS_DTO_H

#include "ConnectedHostDTO.h"

/**@ingroup	GroupDAM
 * @class	CConnectedHostsDTO
 * @brief	연결된 유저 전체에 대한 데이터를 관리한다.
 */
class CConnectedHostsDTO
{
public :
	CArray<CConnectedHostDTO> m_connected;
	void RegistConnected(CConnectedHostDTO *a_connected);
	void RemoveConnected(CString *a_connected);	

private :
	int FindConnected(CString *a_key);
	
};


#endif