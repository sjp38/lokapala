/**@file	StatusReportsDTO.h
 * @brief	CStatusReportsDTO 클래스를 정의한다.
 * @author	siva
 */

#ifndef STATUS_REPORTS_DTO_H
#define STATUS_REPORTS_DTO_H

#include "StatusReportDTO.h"

typedef CArray<CStatusReportDTO> CStatusReportDTOArray;

/**@ingroup	GroupDAM
 * @class	CStatusReportsDTO
 * @brief	보고받은 상황 전체에 대한 정보체.\n
 *			최근의 상황 정보만을 가지며, VERIFIED 된 경우, 기존의 해당 위치에 대한 상황 보고는 삭제한다.
 */
class CStatusReportsDTO
{
public :
	CStatusReportDTOArray m_reports;
	void AddReport(CStatusReportDTO *a_report);
	void DeleteVerifiedReports(CStatusReportDTO *a_report);
	void DeleteReportAt(CString a_hostAddress);

	void GetReportFrom(CString a_hostAddress, CStatusReportDTOArray *a_dest);
	void ClearReports();
};

#endif