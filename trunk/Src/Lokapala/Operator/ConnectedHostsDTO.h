/**@file	ConnectedHostsDTO.h
 * @brief	CConnectedHostsDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef CONNECTED_HOSTS_DTO_H
#define CONNECTED_HOSTS_DTO_H

#include "ConnectedHostDTO.h"

/**@ingroup	GroupDAM
 * @class	CConnectedHostsDTO
 * @brief	����� ���� ��ü�� ���� �����͸� �����Ѵ�.
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