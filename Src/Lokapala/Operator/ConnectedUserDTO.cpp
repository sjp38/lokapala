/**@file	ConnectedUserDTO.cpp
 * @brief	CConnectedUserDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */


#include "stdafx.h"
#include "ConnectedUserDTO.h"

/**@brief	������
 */
CConnectedUserDTO::CConnectedUserDTO(CString a_user, CString a_seat)
{
	m_userId = a_user;
	m_seatId = a_seat;
}