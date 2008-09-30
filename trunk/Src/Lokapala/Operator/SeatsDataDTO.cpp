/**@file	SeatsDataDTO.cpp
 * @brief	CSeatsDataDTO 의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "SeatsDataDTO.h"

#include "DataAdminConstant.h"

/**@brief	생성자. 좌석 정보 구조체의 전체 크기를 잡는다.	*/
CSeatsDataDTO::CSeatsDataDTO()
{
	m_seats.InitHashTable(MAX_SEAT_X*MAX_SEAT_Y+1);
}

/**@brief	전체 좌석의 크기를 정한다.
 * @param	a_maxX	전체 좌석의 가로 길이
 * @param	a_maxY	전체 좌석의 세로 길이
 */
void CSeatsDataDTO::SetSeats(int a_maxX, int a_maxY)
{
	if(a_maxX > MAX_SEAT_X || a_maxY > MAX_SEAT_Y)
	{
		AfxMessageBox(_T("too many seat!"));
		return;
	}
	m_maxX = a_maxX;
	m_maxY = a_maxY;

	ResetSeats();

	//새로 잡힌 크기에 맞춰 기존의 좌석 정보 중 크기를 넘는 좌석을 지우는 과정 필요
}

/**@brief	좌석 정보를 모두 삭제한다.
 */
void CSeatsDataDTO::ClearSeats()
{
	m_seats.RemoveAll();
}

/**@brief	좌석 정보를 하나 만든다.
 */
void CSeatsDataDTO::AddSeat(CSeatDataDTO *a_seat)
{
	if(a_seat->m_position.x > m_maxX || a_seat->m_position.y > m_maxY)
	{
		AfxMessageBox(_T("seat info add fail!! invalid position!!"));
		return;
	}
	if(ExistSameAddress(a_seat))
	{
		AfxMessageBox(_T("same address seat already exist!"));
		return;
	}
	m_seats.SetAt(a_seat->m_seatId, *a_seat);
}

/**@brief	좌석 정보를 하나 지운다.
 */
void CSeatsDataDTO::DeleteSeat(int a_x, int a_y)
{
	if(a_x > m_maxX || a_y > m_maxY)
	{
		AfxMessageBox(_T("seat info add fail!! invalid position!!"));
		return;
	}

	CString key;
	key.Format(_T("%d/%d"),a_x,a_y);
	if( m_seats.RemoveKey(key)==0 )
	{
		AfxMessageBox(_T("seat info delete fail!!"));
	}
}


/**@brief	특정 아이디의 자리 정보를 가져온다.
 */
CSeatDataDTO *CSeatsDataDTO::GetSeatById(CString a_seatId)
{
	CMap<CString, LPCTSTR, CSeatDataDTO, CSeatDataDTO>::CPair *pCursor;
	pCursor = m_seats.PLookup(a_seatId);
	return &(pCursor->value);
}


/**@brief	좌석정보의 안전성을 다시금 챙긴다.
 *			전체 좌석 크기에 어긋나는, 잘못된 정보를 없앤다.
 */
void CSeatsDataDTO::ResetSeats()
{	
	POSITION pos = m_seats.GetStartPosition();
	CString key;
	CSeatDataDTO value;
	while(pos != NULL)
	{
		m_seats.GetNextAssoc(pos, key, value);
		if(value.m_position.x > m_maxX || value.m_position.y > m_maxY)
		{
			m_seats.RemoveKey(key);
		}
	}
}

/**@brief	동일한 주소의 좌석 정보가 있는지 확인한다.
 *			좌석 id는 좌표로만 사용하므로, ip 주소가 겹치는 곳을 미리 확인한다.
 */
BOOL CSeatsDataDTO::ExistSameAddress(CSeatDataDTO *a_seat)
{
	POSITION pos = m_seats.GetStartPosition();
	CString key;
	CSeatDataDTO value;
	while(pos != NULL)
	{
		m_seats.GetNextAssoc(pos, key, value);
		if(value.m_globalIp == a_seat->m_globalIp && value.m_localIp == a_seat->m_localIp)
		{
			return TRUE;
		}
	}
	return FALSE;
}