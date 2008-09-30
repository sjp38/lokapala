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

	//���� ���� ũ�⿡ ���� ������ �¼� ���� �� ũ�⸦ �Ѵ� �¼��� ����� ���� �ʿ�
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
	if(ExistSameAddress(a_seat))
	{
		AfxMessageBox(_T("same address seat already exist!"));
		return;
	}
	m_seats.SetAt(a_seat->m_seatId, *a_seat);
}

/**@brief	�¼� ������ �ϳ� �����.
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


/**@brief	Ư�� ���̵��� �ڸ� ������ �����´�.
 */
CSeatDataDTO *CSeatsDataDTO::GetSeatById(CString a_seatId)
{
	CMap<CString, LPCTSTR, CSeatDataDTO, CSeatDataDTO>::CPair *pCursor;
	pCursor = m_seats.PLookup(a_seatId);
	return &(pCursor->value);
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
 *			�¼� id�� ��ǥ�θ� ����ϹǷ�, ip �ּҰ� ��ġ�� ���� �̸� Ȯ���Ѵ�.
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