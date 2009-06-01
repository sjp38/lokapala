/**@file	StatusReportsDTO.cpp
 * @brief	CStatusReportsDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "StatusReportsDTO.h"

/**@brief	상황 보고 내용을 추가한다.\n
 *			최종적으로 VERIFIED 된 이전의 상태 보고라면 무시한다.\n
 *			만약 추가되는 상황의 상태가 VERIFIED, 즉 고장 상태 수리 완료라면 해당 주소에 대한 기존의 상황 보고는 삭제한다.\n
 *			만약 기존에 있던 상황 보고라면 무시한다.\n
 *			항상 배열 내의 항목들은 시간 순으로 정렬된다.
 */
void CStatusReportsDTO::AddReport(CStatusReportDTO *a_report)
{		
	int i;
	for(int i=m_reports.GetCount()-1; i>=0; i--)
	{
		if(m_reports[i].m_state == VERIFIED)
		{
			if( a_report->m_date <= m_reports[i].m_date )
			{
				return;
			}
			break;
		}
	}

	if(a_report->m_state == VERIFIED)
	{
		DeleteVerifiedReports(a_report);
	}
	for(i=0; i<m_reports.GetCount(); i++)
	{
		if(m_reports[i].m_comment == a_report->m_comment &&
			m_reports[i].m_state == a_report->m_state &&
			m_reports[i].m_hostAddress == a_report->m_hostAddress &&
			m_reports[i].m_date == a_report->m_date )
		{
			return;
		}
		if(a_report->m_date < m_reports[i].m_date)
		{
			break;
		}
	}
	m_reports.InsertAt(i, *a_report);
}

/**@brief	VERIFIED 상태 보고가 들어왔을 경우. 해당 주소의, 이전 시각 상태 보고를 지운다.
 */
void CStatusReportsDTO::DeleteVerifiedReports(CStatusReportDTO *a_report)
{
	for(int i=m_reports.GetCount()-1; i>=0; i--)
	{
		if(m_reports[i].m_hostAddress == a_report->m_hostAddress && m_reports[i].m_date < a_report->m_date)
		{
			m_reports.RemoveAt(i);
		}
	}
}

/**@brief	특정 주소로부터의 상황 보고를 삭제한다.
 */
void CStatusReportsDTO::DeleteReportAt(CString a_hostAddress)
{	
	for(int i=m_reports.GetCount()-1; i>=0; i--)
	{
		if(m_reports[i].m_hostAddress == a_hostAddress)
		{
			m_reports.RemoveAt(i);
		}
	}
}

/**@brief	특정 주소로부터의 상황 보고를 가져온다.
 * @brief	a_dest	해당 상황 보고들을 넣어줄 상황 보고 정보체 배열의 주소.
 */
void CStatusReportsDTO::GetReportFrom(CString a_hostAddress, CStatusReportDTOArray *a_dest)
{
	for(int i=m_reports.GetCount()-1; i>=0; i--)
	{
		a_dest->Add(m_reports[i]);
	}
}
