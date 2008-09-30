/**@file	ConnectedUserDTO.cpp
 * @brief	CConnectedUserDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */


#include "stdafx.h"
#include "ConnectedUserDTO.h"

/**@brief	생성자
 */
CConnectedUserDTO::CConnectedUserDTO(CString a_user, CString a_seat)
{
	m_userId = a_user;
	m_seatId = a_seat;
}