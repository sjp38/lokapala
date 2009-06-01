﻿/**@file	SeatsDataDTO.h
 * @brief	자리들에 대한 정보를 관리하는 CSeatsDataDTO를 정의한다.
 * @author	siva
 */

#ifndef SEATS_DATA_DTO_H
#define SEATS_DATA_DTO_H

#include "SeatDataDTO.h"

/**@ingroup	GroupDAM
 * @class	CSeatsDataDTO
 * @brief	모든 자리들에 대한 정보를 관리한다.
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
	CString GetSeatIdByAxis(int a_x, int a_y);
	CString GetSeatNicknameByAxis(int a_x, int a_y);


	void GetEntireSeatId(CArray<CString> *a_dest);

	CSeatsDataDTO();
	~CSeatsDataDTO(){}

private :
	void ResetSeats();
	BOOL ExistSameAddress(CSeatDataDTO *a_seat);
	
};

#endif
