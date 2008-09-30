/**@file	UserDataDTO.cpp
 * @brief	CUserDataDTO의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "UserDataDTO.h"

#include <openssl/sha.h>

/**@brief	생성자. high 레벨 패스워드는 sha1 알고리즘을 통해 해싱 해서 관리한다.	*/
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

/**@brief	단방향 해싱을 한다. sha1 알고리즘을 사용한다.
 * @param	a_message	해싱을 하고자 하는 메세지
 * @return	해싱된 메세지
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