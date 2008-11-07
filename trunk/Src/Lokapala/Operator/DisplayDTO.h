/**@file	DisplayDTO.h
 * @brief	CDisplayDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef DISPLAY_DTO_H
#define DISPLAY_DTO_H

enum DisplayState {LOGIN, LOGOUT, HW, SW, HWSW, FINE, CRIMINAL, INNOCENT, SEATRESIZE, SEATADD, SEATDELETE, DISPLAY_CONNECTED, DISPLAY_DISCONNECTED};

/**@ingroup	GroupMediator
 * @class	CDisplayDTO
 * @brief	CBFMediator���� UI�� Ư�� ������ ���� ��ȭ�� ���� ����� �䱸 �� ��,
 *			�ش� ������ ���¿� ���� �����͸� ���� ����ü
 */
class CDisplayDTO
{
public :
	int m_seatMaxX;
	int m_seatMaxY;
	CString m_seatId;
	enum DisplayState m_displayState;
	CString m_argument;

	CDisplayDTO(CString a_seatId, enum DisplayState a_state, CString m_argument=_T(""), int a_seatMaxX=0, int a_seatMaxY=0)
	{
		m_seatMaxX = a_seatMaxX;
		m_seatMaxY = a_seatMaxY;
		m_seatId = a_seatId;
		m_displayState = a_state;
		m_argument = m_argument;
	}
	CDisplayDTO(){};
	~CDisplayDTO(){};
};

#endif