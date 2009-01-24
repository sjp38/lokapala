/**@file	UsersDataDTO.cpp
 * @brief	UsersDataDTO�� ����Լ��� ����
 * @author	siva
 */

#include "stdafx.h"
#include "UsersDataDTO.h"

/**@brief	������\n
 *			���� ������ ���� ũ�⸦ ��´�.
 */
CUsersDataDTO::CUsersDataDTO()
{
	m_users.InitHashTable(USER_MAX);
}


/**@brief	���ο� ������ �߰��Ѵ�.
 */
void CUsersDataDTO::AddUser(CUserDataDTO *a_user)
{
	m_users.SetAt(a_user->m_userId, *a_user);
}

/**@brief	������ �����Ѵ�.
 */
void CUsersDataDTO::DeleteUser(CString *a_id)
{
	if( m_users.RemoveKey(*a_id)==0 )
	{
		AfxMessageBox(_T("Delete Failed! no such user"));
	}
}


/**@brief	��ü ����� ������ �����Ѵ�.
 */
void CUsersDataDTO::ClearUsers()
{
	m_users.RemoveAll();
}


/**@brief	id�� ������ �ش� ������ ã�Ƴ���.
 * @return	id�� ã�Ƴ� ������ ������ DTO
 */
CUserDataDTO *CUsersDataDTO::GetUserById(CString a_userId)
{
	if( AlreadyExist(a_userId) )
	{
		CMap<CString, LPCTSTR, CUserDataDTO, CUserDataDTO>::CPair *pCursor;
		pCursor = m_users.PLookup(a_userId);
		return &(pCursor->value);
	}
	return NULL;
}

/**@brief	������ id�� ������ �ִ��� ã�ƺ���.
 * @return	������ id�� ������ �ִٸ� TRUE, ���ٸ� FALSE
 */
BOOL CUsersDataDTO::AlreadyExist(CString a_userId)
{
	CUserDataDTO value;
	if( m_users.Lookup(a_userId, value) == 0)
	{
		return FALSE;
	}
	return TRUE;	
}