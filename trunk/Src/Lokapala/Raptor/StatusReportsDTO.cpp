/**@file	StatusReportsDTO.cpp
 * @brief	CStatusReportsDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "StatusReportsDTO.h"

/**@brief	상황 보고 내용을 추가한다.\n
 *			만약 추가되는 상황의 상황가 VERIFIED, 즉 고장 상황 수리 완료라면 해당 주소에 대한 기존의 상황 보고는 삭제한다.
 */
void CStatusReportsDTO::AddReport(CStatusReportDTO *a_report)
{
	if(a_report->m_state == VERIFIED)
	{
		DeleteReportAt(a_report->m_globalIp, a_report->m_localIp);
	}
	m_reports.Add(*a_report);

}

/**@brief	특정 주소로부터의 상황 보고를 삭제한다.
 */
void CStatusReportsDTO::DeleteReportAt(CString a_globalIp, CString a_localIp)
{	
	for(int i=0; i<m_reports.GetCount(); i++)
	{
		if(m_reports[i].m_globalIp == a_globalIp && m_reports[i].m_localIp == a_localIp)
		{
			m_reports.RemoveAt(i);
		}
	}
}

/**@brief	특정 주소로부터의 상황 보고를 가져온다.
 * @brief	a_dest	해당 상황 보고들을 넣어줄 상황 보고 정보체 배열의 주소.
 */
void CStatusReportsDTO::GetReportFrom(CString a_globalIp, CString a_localIp, CStatusReportDTOArray *a_dest)
{
	for(int i=m_reports.GetCount()-1; i>=0; i--)
	{
		if(m_reports[i].m_globalIp == a_globalIp && m_reports[i].m_localIp == a_localIp)
		{
			a_dest->Add(m_reports[i]);
		}
	}
}