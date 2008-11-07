/**@file	SeatsDisplayDTO.h
 * @brief	CSeatsDisplayDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */


#ifndef SEATS_DISPLAY_DTO_H
#define SEATS_DISPLAY_DTO_H

#include "DisplayDTO.h"

/**@ingroup	GroupMediator
 * @brief	����Ʈ ��Ʈ���� �̿��� �¼��� ���� ǥ�ø� ���� �ؾ� �� ��츦 ���� �¼� ���¿� ���� ǥ�� ������ ���������� ���´�.
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