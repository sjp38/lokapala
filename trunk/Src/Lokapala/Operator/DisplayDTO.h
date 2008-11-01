/**@file	DisplayDTO.h
 * @brief	CDisplayDTO 클래스를 정의한다.
 * @author	siva
 */

#ifndef DISPLAY_DTO_H
#define DISPLAY_DTO_H

enum DisplayState {LOGIN, LOGOUT, HW, SW, HWSW, FINE, CRIMINAL, INNOCENT, SEATADD, SEATDELETE};

/**@ingroup	GroupMediator
 * @class	CDisplayDTO
 * @brief	CBFMediator에서 UI로 특정 유저의 상태 변화에 대한 출력을 요구 할 때,
 *			해당 유저의 상태에 대한 데이터를 갖는 정보체
 */
class CDisplayDTO
{
public :
	CString m_seatId;
	enum DisplayState m_displayState;
	CString m_argument;

	CDisplayDTO(CString a_seatId, enum DisplayState a_state, CString m_argument=_T(""))
	{
		m_seatId = a_seatId;
		m_displayState = a_state;
		m_argument = m_argument;
	}
	CDisplayDTO(){};
	~CDisplayDTO(){};
};

#endif