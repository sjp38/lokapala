/**@file	SeatDataDTO.cpp
 * @brief	CSeatDataDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "SeatDataDTO.h"

CSeatDataDTO::CSeatDataDTO(CString a_globalIp, CString a_localIp, int a_x, int a_y, CString a_nickname)
{
	m_seatId.Format(_T("%d/%d"),a_globalIp,a_localIp);
	m_globalIp = a_globalIp;
	m_localIp = a_localIp;
	m_position.x = a_x;
	m_position.y = a_y;
	m_nickname = a_nickname;
}