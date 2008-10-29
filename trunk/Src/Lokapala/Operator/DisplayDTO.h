/**@file	DisplayDTO.h
 * @brief	CDisplayDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */

#ifndef DISPLAY_DTO_H
#define DISPLAY_DTO_H

enum DisplayState {LOGIN, LOGOUT, HW, SW, VERIFIED, CRIMINAL, INNOCENT};

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

	CDisplayDTO(CString a_seatId, enum DisplayState a_state)
	{
		m_seatId = a_seatId;
		m_displayState = a_state;
	}
	CDisplayDTO(){};
	~CDisplayDTO(){};
};

#endif