/**@file	SeatDataDTO.cpp
 * @brief	CSeatDataDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "SeatDataDTO.h"

CSeatDataDTO::CSeatDataDTO(CString a_hostAddress, int a_x, int a_y, CString a_nickname)
{
	m_seatId = a_hostAddress;
	m_hostAddress = a_hostAddress;
	m_position.x = a_x;
	m_position.y = a_y;
	m_nickname = a_nickname;
}