/**@file	SeatsDataDTO.cpp
 * @brief	CSeatsDataDTO �� ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "SeatsDataDTO.h"

#include "DataAdminConstant.h"

/**@brief	������. �¼� ���� ����ü�� ��ü ũ�⸦ ��´�.	*/
CSeatsDataDTO::CSeatsDataDTO()
{
	m_maxX = 5;
	m_maxY = 5;
	m_seats.InitHashTable(MAX_SEAT_X*MAX_SEAT_Y+1);
}

/**@brief	��ü �¼��� ũ�⸦ ���Ѵ�.
 * @param	a_maxX	��ü �¼��� ���� ����
 * @param	a_maxY	��ü �¼��� ���� ����
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
}

/**@brief	�¼� ������ ��� �����Ѵ�.
 */
void CSeatsDataDTO::ClearSeats()
{
	m_seats.RemoveAll();
}

/**@brief	�¼� ������ �ϳ� �����.
 */
void CSeatsDataDTO::AddSeat(CSeatDataDTO *a_seat)
{
	if(a_seat->m_position.x > m_maxX || a_seat->m_position.y > m_maxY)
	{
		AfxMessageBox(_T("seat info add fail!! invalid position!!"));
		return;
	}
	m_seats.SetAt(a_seat->m_seatId, *a_seat);
	CCBFMediator::Instance()->NotifySeatAdded(&a_seat->m_seatId);
}

/**@brief	�¼� ������ �ϳ� �����.
 */
void CSeatsDataDTO::DeleteSeat(CString *a_seatId)
{
	CCBFMediator::Instance()->NotifySeatDeleted(a_seatId);
	if( m_seats.RemoveKey(*a_seatId)==0 )
	{
		AfxMessageBox(_T("seat info delete fail!!"));
	}
}


/**@brief	Ư�� ���̵��� �ڸ� ������ �����´�.
 */
CSeatDataDTO *CSeatsDataDTO::GetSeatById(CString a_seatId)
{
	CMap<CString, LPCTSTR, CSeatDataDTO, CSeatDataDTO>::CPair *pCursor;
	pCursor = m_seats.PLookup(a_seatId);
	if(pCursor == NULL)
	{
		return NULL;
	}
	return &(pCursor->value);
}


/**@brief	��ǥ�� �¼� �̸��� ���� ��ȯ�Ѵ�.
 */
CString CSeatsDataDTO::GetSeatNicknameByAxis(int a_x, int a_y)
{
	POSITION pos = m_seats.GetStartPosition();
	CString key;
	CSeatDataDTO value;
	while(pos != NULL)
	{
		m_seats.GetNextAssoc(pos, key, value);
		if(value.m_position.x == a_x && value.m_position.y == a_y)
		{
			return value.m_nickname;
		}
	}
	key = _T("");
	return key;
}


/**@brief	�¼������� �������� �ٽñ� ì���.
 *			��ü �¼� ũ�⿡ ��߳���, �߸��� ������ ���ش�.
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

/**@brief	������ �ּ��� �¼� ������ �ִ��� Ȯ���Ѵ�.
 *			�¼� id�� ip �ּҸ� ����ϹǷ�, ���� ��ǥ������ Ȯ���Ѵ�.
 */
BOOL CSeatsDataDTO::ExistSameAddress(CSeatDataDTO *a_seat)
{
	POSITION pos = m_seats.GetStartPosition();
	CString key;
	CSeatDataDTO value;
	while(pos != NULL)
	{
		m_seats.GetNextAssoc(pos, key, value);
		if(value.m_position.x == a_seat->m_position.x && value.m_position.y == a_seat->m_position.y)
		{
			return TRUE;
		}
	}
	return FALSE;
}