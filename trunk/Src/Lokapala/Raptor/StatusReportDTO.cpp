/**@file	StatusReportDTO.cpp
 * @brief	CStatusReportDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "StatusReportDTO.h"

/**@brief	생성자. 랩터에선 이걸 쓰진 않는다.	*/
CStatusReportDTO::CStatusReportDTO(CString a_globalIp, CString a_localIp, State a_state, CString a_date, CString a_comment)
{
	m_globalIp = a_globalIp;
	m_localIp = a_localIp;
	m_state = a_state;
	m_date = a_date;
	m_comment = a_comment;
}

/**@brief	생성자. 랩터에선 이걸 쓰게 된다.	*/
CStatusReportDTO::CStatusReportDTO(State a_state, CString a_date, CString a_comment)
{
	m_globalIp = _T("");
	m_localIp = _T("");
	m_state = a_state;
	m_date = a_date;
	m_comment = a_comment;
}