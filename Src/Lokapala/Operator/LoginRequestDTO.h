/**@file	LoginRequestDTO.h
 * @brief	로그인 요청 정보를 담는 CLoginRequestDTO 클래스를 정의한다.
 * @author	siva
 */

#ifndef LOGIN_REQUEST_DTO_H
#define LOGIN_REQUEST_DTO_H

/**@ingroup	GroupCCM
 * @class	CLoginRequestDTO
 * @brief	로그인 요청 시 사용되는 정보를 담는다. UserDataDTO에서 다루는 데이터에 로그인 요청 들어온 곳의 주소 정보가 포함된다.\n
 *			m_level은 DCM에게 로그인 요청 허용 여부 처리를 부탁할 때 -1의 값으로 초기화 되며, DCM이 로그인 허용 메세지를 보내라고 할 땐 실제 레벨 값이 들어간다.
 */
class CLoginRequestDTO
{
public :
	CString m_hostAddress;
	CString m_name;
	CString m_lowLevelPassword;
	CString m_highLevelPassword;
	int m_level;

	CLoginRequestDTO(){}
	~CLoginRequestDTO(){}

	CLoginRequestDTO(CString a_hostAddress, CString a_name, CString a_lowLevelPassword, CString a_highLevelPassword)
	{
		m_hostAddress = a_hostAddress;
		m_name = a_name;
		m_lowLevelPassword = a_lowLevelPassword;
		m_highLevelPassword = a_highLevelPassword;
		m_level = -1;
	}
};


#endif
