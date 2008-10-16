/**@file	MessgeDTO.h
 * @brief	커뮤니케이션 컴포넌트로 보낼 메세지 관련 정보를 담는다.
 * @author	siva
 */

#ifndef MESSAGE_DTO_H
#define MESSAGE_DTO_H

/**@ingroup	DAM
 * @class	CMessageDTO
 * @brief	커뮤니케이션 컴포넌트로 보낼 메세지 관련 정보를 담는다.
 */
class CMessageDTO
{
public :
	CString m_globalIp;
	CString m_localIp;
	CString m_message;

	CMessageDTO(){}
	~CMessageDTO(){}

	CMessageDTO(CString a_globalIp, CString a_localIp, CString a_message)
	{
		m_globalIp = a_globalIp;
		m_localIp = a_localIp;
		m_message = a_message;
	}
};


#endif