/**@file	SeatsDisplayDTO.h
 * @brief	CSeatsDisplayDTO 클래스를 정의한다.
 * @author	siva
 */


#ifndef SEATS_DISPLAY_DTO_H
#define SEATS_DISPLAY_DTO_H

#include "DisplayDTO.h"

/**@ingroup	GroupMediator
 * @brief	리스트 컨트롤을 이용한 좌석의 상태 표시를 새로 해야 할 경우를 위해 좌석 상태에 대한 표시 정보를 지속적으로 갖는다.
 */
class CSeatsDisplayDTO
{
public :
	CArray<CDisplayDTO> m_displayDTOs;

	CSeatsDisplayDTO(){}
	~CSeatsDisplayDTO(){}

	void AddDisplayDTO(CDisplayDTO a_displayDTO);
private :
};


#endif