/**@file	SeatDataDTO.h
 * @brief	자리 관련 정보를 저장하는 DTO를 정의한다.
 * @author	siva
 */

#ifndef SEAT_DATA_DTO_H
#define SEAT_DATA_DTO_H


/**@ingroup	GroupDAM
 * @class	CSeatDataDTO
 * @brief	각 자리의 정보를 저장한다.
 */
class CSeatDataDTO
{
public :
	/**@brief	{글로벌 ip}/{로컬 ip} 의 형태를 갖는다.	*/
	CString m_seatId;
	CString m_globalIp;
	CString m_localIp;
	CPoint m_position;
	CString m_nickname;

	CSeatDataDTO(CString a_globalIp, CString a_localIp, int a_x, int a_y, CString a_nickname);
	CSeatDataDTO(){}
	~CSeatDataDTO(){}
};


#endif