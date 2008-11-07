/**@file	SeatsDisplayDTO.cpp
 * @brief	CSeatsDisplayDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */


#include "stdafx.h"
#include "SeatsDisplayDTO.h"

/**@brief	���ο� ǥ�� ������ ����ִ´�.
 *			������ ������ �¼��� ���� ������ �־��ٸ� �ش� ������ �����Ѵ�.
 *			��, ���������� �� �¼��� �ϳ��� �ֽ� ���� ǥ�� �������� ���´�.
 */
void CSeatsDisplayDTO::AddDisplayDTO(CDisplayDTO a_displayDTO)
{
	if(a_displayDTO.m_displayState == SEATRESIZE || a_displayDTO.m_displayState == DISPLAY_CONNECTED || a_displayDTO.m_displayState == DISPLAY_DISCONNECTED)
	{
		return;
	}
	for(int i=0; i<m_displayDTOs.GetCount(); i++)
	{
		if(m_displayDTOs[i].m_seatId == a_displayDTO.m_seatId)
		{
			m_displayDTOs.RemoveAt(i);
			break;
		}
	}
	m_displayDTOs.Add(a_displayDTO);
}