/**@file	StatusReportDTO.cpp
 * @brief	CStatusReportDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "StatusReportDTO.h"

/**@brief	������	*/
CStatusReportDTO::CStatusReportDTO(CString a_hostAddress, State a_state, CString a_date, CString a_comment)
{
	m_hostAddress = a_hostAddress;
	m_state = a_state;
	m_date = a_date;
	m_comment = a_comment;
}