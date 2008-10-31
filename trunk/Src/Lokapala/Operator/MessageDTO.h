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