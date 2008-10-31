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
	CString m_hostAddress;
	CString m_message;

	CMessageDTO(){}
	~CMessageDTO(){}

	CMessageDTO(CString a_hostAddress, CString a_message)
	{
		m_hostAddress = a_hostAddress;
		m_message = a_message;
	}
};


#endif