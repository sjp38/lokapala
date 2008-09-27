/**@file	StateDataDTO.h
 * @brief	상태에 관한 데이터를 저장하는 DTO를 정의한다.
 * @author	siva
 */

#ifndef STATE_DATA_DTO_H
#define STATE_DATA_DTO_H

enum State {HW, SW, Fixed, Verified};

/**@ingroup	GroupDAM
 * @class	CStateDataDTO
 * @brief	상태에 관한 정보를 저장한다.
 */
class CStateDataDTO
{
	int m_stateId;
	CString m_globalIp;
	CString m_localIp;
	enum State m_state;
	CString m_comment;
	CString m_date;
};

#endif