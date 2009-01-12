/**@file	StatusReportDTO.h
 * @brief	CStatusReportDTO Ŭ������ ����
 * @author	siva
 */


#ifndef STATUS_REPORT_DTO_H
#define STATUS_REPORT_DTO_H

enum State {HW_DEFECT, SW_DEFECT, REPAIRED, VERIFIED};

/**@ingroup	GroupDAM
 * @class	CStatusReportDTO
 * @brief	���� ��Ȳ�� ���� ����ü
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