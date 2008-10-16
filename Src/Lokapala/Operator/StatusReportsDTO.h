/**@file	StatusReportsDTO.h
 * @brief	CStatusReportsDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef STATUS_REPORTS_DTO_H
#define STATUS_REPORTS_DTO_H

#include "StatusReportDTO.h"

typedef CArray<CStatusReportDTO> CStatusReportDTOArray;

/**@ingroup	GroupDAM
 * @class	CStatusReportsDTO
 * @brief	������� ��Ȳ ��ü�� ���� ����ü.\n
 *			�ֱ��� ��Ȳ �������� ������, VERIFIED �� ���, ������ �ش� ��ġ�� ���� ��Ȳ ����� �����Ѵ�.
 */
class CStatusReportsDTO
{
public :
	CStatusReportDTOArray m_reports;
	void AddReport(CStatusReportDTO *a_report);
	void DeleteReportAt(CString a_globalIp, CString a_localIp);

	void GetReportFrom(CString a_globalIp, CString a_localIp, CStatusReportDTOArray *a_dest);
	void ClearReports();
};

#endif