/**@file	ConnectedUsersDTO.cpp
 * @brief	CConnectedUsersDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "ConnectedUsersDTO.h"

/**@brief	���� ����� ������ ������ ����Ѵ�.
 */
void CConnectedUsersDTO::RegistConnected(CConnectedUserDTO *a_connected)
{
	m_connected.Add(*a_connected);
}

/**@brief	����� ��Ͽ��� Ư�� �����͸� �����Ѵ�.
 * @param	a_key	�����ϰ��� �ϴ� �������� ����� �Ǵ� �¼� id.
 */
void CConnectedUsersDTO::RemoveConnected(CString *a_key)
{
	int cursor = FindConnected(a_key);
	if( cursor != -1 )
	{
		m_connected.RemoveAt(cursor);		
		return;
	}
	AfxMessageBox(_T("delete fail! no such rules!"));
	return;
}


/**@brief	����� ��Ͽ��� ���ϴ� ���� ������ ã�´�.
 * @param	a_key	ã���� �ϴ� ���� �׸��� ���� id �Ǵ� �¼� id.
 */
int CConnectedUsersDTO::FindConnected(CString *a_key)
{
	for(int i=0; i<m_connected.GetCount(); i++)
	{
		if( m_connected[i].m_userId == *a_key || m_connected[i].m_seatId == *a_key )
		{
			return i;
		}
	}
	return -1;
}