/**@file	StatusReportsDTO.cpp
 * @brief	CStatusReportsDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "StatusReportsDTO.h"

/**@brief	��Ȳ ���� ������ �߰��Ѵ�.\n
 *			���� �߰��Ǵ� ��Ȳ�� ��Ȳ�� VERIFIED, �� ���� ��Ȳ ���� �Ϸ��� �ش� �ּҿ� ���� ������ ��Ȳ ����� �����Ѵ�.
 */
void CStatusReportsDTO::AddReport(CStatusReportDTO *a_report)
{
	if(a_report->m_state == VERIFIED)
	{
		DeleteReportAt(a_report->m_globalIp, a_report->m_localIp);
	}
	m_reports.Add(*a_report);

}

/**@brief	Ư�� �ּҷκ����� ��Ȳ ���� �����Ѵ�.
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

/**@brief	Ư�� �ּҷκ����� ��Ȳ ���� �����´�.
 * @brief	a_dest	�ش� ��Ȳ ������� �־��� ��Ȳ ���� ����ü �迭�� �ּ�.
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