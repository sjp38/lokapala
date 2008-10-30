/**@file	StatusReportDTO.cpp
 * @brief	CStatusReportDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "StatusReportDTO.h"

/**@brief	������. ���Ϳ��� �̰� ���� �ʴ´�.	*/
CStatusReportDTO::CStatusReportDTO(CString a_globalIp, CString a_localIp, State a_state, CString a_date, CString a_comment)
{
	m_globalIp = a_globalIp;
	m_localIp = a_localIp;
	m_state = a_state;
	m_date = a_date;
	m_comment = a_comment;
}

/**@brief	������. ���Ϳ��� �̰� ���� �ȴ�.	*/
CStatusReportDTO::CStatusReportDTO(State a_state, CString a_date, CString a_comment)
{
	m_globalIp = _T("");
	m_localIp = _T("");
	m_state = a_state;
	m_date = a_date;
	m_comment = a_comment;
}