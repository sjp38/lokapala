/**@file	SeatDataDTO.h
 * @brief	�ڸ� ���� ������ �����ϴ� DTO�� �����Ѵ�.
 * @author	siva
 */

#ifndef SEAT_DATA_DTO_H
#define SEAT_DATA_DTO_H


/**@ingroup	GroupDAM
 * @class	CSeatDataDTO
 * @brief	�� �ڸ��� ������ �����Ѵ�.
 */
class CSeatDataDTO
{
public :
	/**@brief	{�۷ι� ip}/{���� ip} �� ���¸� ���´�.	*/
	CString m_seatId;
	CString m_hostAddress;
	CPoint m_position;
	CString m_nickname;

	CSeatDataDTO(CString a_hostAddress, int a_x, int a_y, CString a_nickname);
	CSeatDataDTO(){}
	~CSeatDataDTO(){}
};


#endif