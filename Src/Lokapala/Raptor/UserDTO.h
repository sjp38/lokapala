/**@file	UserDTO.h
 * @brief	CUserDTO 클래스를 정의한다.
 * @author	siva
 */

#ifndef USER_DTO_H
#define USER_DTO_H

/**@ingroup	GroupDAM
 * @class	CUserDTO
 * @brief	사용자 관련 정보를 갖는다. 현재 사용자 정보를 유지하는데도 사용되며, 로그인 요청용으로도 사용된다.
 */
class CUserDTO
{
public :
	CString m_name;
	CString m_lowLevelPassword;
	CString m_highLevelPassword;
	int m_level;

	CUserDTO(CString a_name, CString a_lowLevelPassword, CString a_highLevelPassword);
	CUserDTO(CString a_name, CString a_lowLevelPassword, CString a_highLevelPassword, int a_level);
	CUserDTO(){}
	~CUserDTO(){}

private :
	CString HashMessage(CString a_message);
};


#endif
