/**@file	ConnectedHostDTO.cpp
 * @brief	CConnectedHostDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */


#include "stdafx.h"
#include "ConnectedHostDTO.h"

/**@brief	생성자
 */
CConnectedHostDTO::CConnectedHostDTO(CString a_user, CString a_hostAddress)
{
	m_userId = a_user;
	m_hostAddress = a_hostAddress;
}