/**@file	ConnectedHostsDTO.cpp
 * @brief	CConnectedHostsDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "ConnectedHostsDTO.h"

/**@brief	새로 연결된 유저의 정보를 등록한다.
 */
void CConnectedHostsDTO::RegistConnected(CConnectedHostDTO *a_connected)
{
	RemoveConnected(&a_connected->m_hostAddress);
	RemoveConnected(&a_connected->m_userId);
	m_connected.Add(*a_connected);
}

/**@brief	연결된 목록에서 특정 데이터를 삭제한다.
 * @param	a_key	삭제하고자 하는 데이터의 사용자 또는 좌석 id.
 */
void CConnectedHostsDTO::RemoveConnected(CString *a_key)
{
	int cursor = FindConnected(a_key);
	if(cursor != -1)
	{
		m_connected.RemoveAt(cursor);		
	}
	if(cursor = FindConnected(a_key) != -1)
	{
		m_connected.RemoveAt(cursor);
	}
	return;
}

/**@brief	연결된 목록에서 원하는 연결 사항을 찾는다.
 * @param	a_key	찾고자 하는 연결 항목의 유저 id 또는 좌석 id.
 */
int CConnectedHostsDTO::FindConnected(CString *a_key)
{
	for(int i=0; i<m_connected.GetCount(); i++)
	{
		if( m_connected[i].m_userId == *a_key || m_connected[i].m_hostAddress == *a_key )
		{
			return i;
		}
	}
	return -1;
}