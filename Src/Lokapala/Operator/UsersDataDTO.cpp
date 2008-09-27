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


/**@brief	�̸��� ������ �ش� ������ ã�Ƴ���.
 * @return	�̸����� ã�Ƴ� ������ ������ DTO
 */
CUserDataDTO *CUsersDataDTO::GetUserById(CString a_userId)
{
	CMap<CString, LPCTSTR, CUserDataDTO, CUserDataDTO>::CPair *pCursor;
	pCursor = m_users.PLookup(a_userId);
	return &(pCursor->value);
}