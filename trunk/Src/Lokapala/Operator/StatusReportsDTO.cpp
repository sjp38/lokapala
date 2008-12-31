/**@file	StatusReportsDTO.cpp
 * @brief	CStatusReportsDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "StatusReportsDTO.h"

/**@brief	��Ȳ ���� ������ �߰��Ѵ�.\n
 *			���� �߰��Ǵ� ��Ȳ�� ���°� VERIFIED, �� ���� ���� ���� �Ϸ��� �ش� �ּҿ� ���� ������ ��Ȳ ����� �����Ѵ�.
 *			���� ������ �ִ� ��Ȳ ������ �����Ѵ�.
 *			�׻� �迭 ���� �׸���� �ð� ������ ���ĵȴ�.
 */
void CStatusReportsDTO::AddReport(CStatusReportDTO *a_report)
{	
	if(a_report->m_state == VERIFIED)
	{
		DeleteReportAt(a_report->m_hostAddress);
	}
	int i;
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

/**@brief	Ư�� �ּҷκ����� ��Ȳ ���� �����Ѵ�.
 */
void CStatusReportsDTO::DeleteReportAt(CString a_hostAddress)
{	
	for(int i=0; i<m_reports.GetCount(); i++)
	{
		if(m_reports[i].m_hostAddress == a_hostAddress)
		{
			m_reports.RemoveAt(i--);
		}
	}
}

/**@brief	Ư�� �ּҷκ����� ��Ȳ ���� �����´�.
 * @brief	a_dest	�ش� ��Ȳ ������� �־��� ��Ȳ ���� ����ü �迭�� �ּ�.
 */
void CStatusReportsDTO::GetReportFrom(CString a_hostAddress, CStatusReportDTOArray *a_dest)
{
	for(int i=m_reports.GetCount()-1; i>=0; i--)
	{
		if(m_reports[i].m_hostAddress == a_hostAddress)
		{
			a_dest->Add(m_reports[i]);
		}
	}
}