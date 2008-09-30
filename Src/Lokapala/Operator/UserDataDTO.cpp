/**@file	UserDataDTO.cpp
 * @brief	CUserDataDTO�� ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "UserDataDTO.h"

#include <openssl/sha.h>

/**@brief	������. high ���� �н������ sha1 �˰����� ���� �ؽ� �ؼ� �����Ѵ�.	*/
CUserDataDTO::CUserDataDTO(CString a_userId, CString a_name, CString a_lowLevelPassword, CString a_highLevelPassword, int a_level)
{
	m_userId = a_userId;
	if(m_userId == _T(""))
	{
		m_userId = a_lowLevelPassword;
	}
	m_name = a_name;
	m_lowLevelPassword = a_lowLevelPassword;
	m_highLevelPassword = HashMessage(a_highLevelPassword);
	m_level = a_level;
}

/**@brief	�ܹ��� �ؽ��� �Ѵ�. sha1 �˰����� ����Ѵ�.
 * @param	a_message	�ؽ��� �ϰ��� �ϴ� �޼���
 * @return	�ؽ̵� �޼���
 */
CString CUserDataDTO::HashMessage(CString a_message)
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