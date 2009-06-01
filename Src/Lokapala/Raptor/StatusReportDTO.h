/**@file	StatusReportDTO.h
 * @brief	CStatusReportDTO 클래스의 정의
 * @author	siva
 */


#ifndef STATUS_REPORT_DTO_H
#define STATUS_REPORT_DTO_H

enum State {HW_DEFECT, SW_DEFECT, REPAIRED, VERIFIED};

/**@ingroup	GroupDAM
 * @class	CStatusReportDTO
 * @brief	고장 상황에 대한 정보체
 */
class CStatusReportDTO
{
public :
	CString m_hostAddress;
	enum State m_state;
	CString m_date;
	CString m_comment;

	CStatusReportDTO(CString a_hostAddress, enum State a_state, CString a_date, CString a_comment);
	CStatusReportDTO(enum State a_state, CString a_date, CString a_comment);

	CStatusReportDTO(){}
	~CStatusReportDTO(){}
};

#endif
