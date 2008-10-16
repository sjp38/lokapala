/**@file	MessgeDTO.h
 * @brief	Ŀ�´����̼� ������Ʈ�� ���� �޼��� ���� ������ ��´�.
 * @author	siva
 */

#ifndef MESSAGE_DTO_H
#define MESSAGE_DTO_H

/**@ingroup	DAM
 * @class	CMessageDTO
 * @brief	Ŀ�´����̼� ������Ʈ�� ���� �޼��� ���� ������ ��´�.
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