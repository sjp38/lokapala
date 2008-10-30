/**@file	SeatsDataDTO.h
 * @brief	�ڸ��鿡 ���� ������ �����ϴ� CSeatsDataDTO�� �����Ѵ�.
 * @author	siva
 */

#ifndef SEATS_DATA_DTO_H
#define SEATS_DATA_DTO_H

#include "SeatDataDTO.h"

/**@ingroup	GroupDAM
 * @class	CSeatsDataDTO
 * @brief	��� �ڸ��鿡 ���� ������ �����Ѵ�.
 */
class CSeatsDataDTO
{
public :
	CMap <CString, LPCTSTR, CSeatDataDTO, CSeatDataDTO> m_seats;
	int m_maxX;
	int m_maxY;

	void SetSeats(int a_maxX, int a_maxY);
	void ClearSeats();
	void AddSeat(CSeatDataDTO *a_seat);
	void DeleteSeat(CString *a_seatId);
	CSeatDataDTO *GetSeatById(CString a_userId);

	CSeatsDataDTO();
	~CSeatsDataDTO(){}

private :
	void ResetSeats();
	BOOL ExistSameAddress(CSeatDataDTO *a_seat);
	
};

#endif