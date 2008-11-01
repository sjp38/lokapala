/**@file	DisplayDTO.h
 * @brief	CDisplayDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef DISPLAY_DTO_H
#define DISPLAY_DTO_H

enum DisplayState {LOGIN, LOGOUT, HW, SW, HWSW, FINE, CRIMINAL, INNOCENT, SEATADD, SEATDELETE};

/**@ingroup	GroupMediator
 * @class	CDisplayDTO
 * @brief	CBFMediator���� UI�� Ư�� ������ ���� ��ȭ�� ���� ����� �䱸 �� ��,
 *			�ش� ������ ���¿� ���� �����͸� ���� ����ü
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