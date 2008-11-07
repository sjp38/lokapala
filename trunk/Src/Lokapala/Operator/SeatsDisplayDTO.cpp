/**@file	SeatsDisplayDTO.cpp
 * @brief	CSeatsDisplayDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */


#include "stdafx.h"
#include "SeatsDisplayDTO.h"

/**@brief	새로운 표시 정보를 집어넣는다.
 *			기존에 동일한 좌석에 대한 정보가 있었다면 해당 정보는 삭제한다.
 *			즉, 최종적으로 한 좌석에 하나의 최신 상태 표시 정보만이 남는다.
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