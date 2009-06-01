/**@file	UsersDataDTO.cpp
 * @brief	UsersDataDTO의 멤버함수를 구현
 * @author	siva
 */

#include "stdafx.h"
#include "UsersDataDTO.h"

/**@brief	생성자\n
 *			유저 데이터 맵의 크기를 잡는다.
 */
CUsersDataDTO::CUsersDataDTO()
{
	m_users.InitHashTable(USER_MAX);
}


/**@brief	새로운 유저를 추가한다.
 */
void CUsersDataDTO::AddUser(CUserDataDTO *a_user)
{
	m_users.SetAt(a_user->m_userId, *a_user);
}

/**@brief	유저를 삭제한다.
 */
void CUsersDataDTO::DeleteUser(CString *a_id)
{
	if( m_users.RemoveKey(*a_id)==0 )
	{
		AfxMessageBox(_T("Delete Failed! no such user"));
	}
}


/**@brief	전체 사용자 정보를 삭제한다.
 */
void CUsersDataDTO::ClearUsers()
{
	m_users.RemoveAll();
}


/**@brief	id을 가지고 해당 유저를 찾아낸다.
 * @return	id로 찾아낸 유저의 데이터 DTO
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

/**@brief	동일한 id의 유저가 있는지 찾아본다.
 * @return	동일한 id의 유저가 있다면 TRUE, 없다면 FALSE
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
