﻿/**@file	StatusReportDTO.cpp
 * @brief	CStatusReportDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "StatusReportDTO.h"

/**@brief	생성자	*/
CStatusReportDTO::CStatusReportDTO(CString a_hostAddress, State a_state, CString a_date, CString a_comment)
{
	m_hostAddress = a_hostAddress;
	m_state = a_state;
	m_date = a_date;
	m_comment = a_comment;
}
