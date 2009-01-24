/**@file	UserDTO.cpp
 * @brief	CUserDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "UserDTO.h"

#include <openssl/sha.h>

CUserDTO::CUserDTO(CString a_name, CString a_lowLevelPassword, CString a_highLevelPassword)
{
	m_name = a_name;
	m_lowLevelPassword = a_lowLevelPassword;
	m_highLevelPassword = HashMessage(a_highLevelPassword);
	m_level = -1;
};

CUserDTO::CUserDTO(CString a_name, CString a_lowLevelPassword, CString a_highLevelPassword, int a_level)
{
	m_name = a_name;
	m_lowLevelPassword = a_lowLevelPassword;
	m_highLevelPassword = HashMessage(a_highLevelPassword);
	m_level = a_level;
};

/**@brief	sha1 �˰������� �޼����� �ؽ��Ѵ�.
 */
CString CUserDTO::HashMessage(CString a_message)
{
	unsigned char *digestMsg = (unsigned char *)malloc((SHA_DIGEST_LENGTH+1)*sizeof(unsigned char));

	USES_CONVERSION;
	char *original = W2A(a_message);
	SHA1((unsigned char *)original, strlen(original)*sizeof(char), digestMsg);
	digestMsg[SHA_DIGEST_LENGTH] = '\0';
	CString modified = A2W((LPCSTR)digestMsg);
	
	free(digestMsg);
	return modified;
}