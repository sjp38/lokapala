/**@file	ConnectedHostDTO.cpp
 * @brief	CConnectedHostDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */


#include "stdafx.h"
#include "ConnectedHostDTO.h"

/**@brief	������
 */
CConnectedHostDTO::CConnectedHostDTO(CString a_user, CString a_hostAddress)
{
	m_userId = a_user;
	m_hostAddress = a_hostAddress;
}