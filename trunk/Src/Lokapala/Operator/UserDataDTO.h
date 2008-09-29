/**@file	UserDataDTO.h
 * @brief	유저 개인의 정보를 담는 DTO를 정의한다.
 * @author	siva
 */

#ifndef USER_DATA_DTO_H
#define USER_DATA_DTO_H

/**@ingroup	GroupDAM
 * @class	CUserDataDTO
 * @brief	유저 개인의 정보를 담는다.\n
 * @remarks	비밀번호는 모두 단방향 해싱을 거친 값들을 갖는다.\n
 *			유저 id는 당방향 해싱 후의 로우레벨 패스워드(학번)다.
 */
class CUserDataDTO
{
public :
	/**@brief	여기선 단순히 해당 유저의 low level password를 사용한다.	*/
	CString m_userId;
	CString m_name;
	CString m_lowLevelPassword;
	/**@brief	sha1으로 해싱된 digest message를 갖는다.	*/
	CString m_highLevelPassword;
	int m_level;
	/**@brief	접속된 유저라면 TRUE, 아니면 FALSE	*/
	BOOL m_connected;
	/**@brief	접속되어 있다면, 접속한 자리의 id	*/
	CString m_seatId;
	
	CUserDataDTO(CString a_userId, CString a_name, CString a_lowLevelPassword, CString a_highLevelPassword, int level=0);
	CUserDataDTO(){}
	~CUserDataDTO(){}

private :
	CString HashMessage(CString a_message);
};


#endif