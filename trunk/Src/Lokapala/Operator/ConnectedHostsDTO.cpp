/**@file	ConnectedHostsDTO.cpp
 * @brief	CConnectedHostsDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "ConnectedHostsDTO.h"

/**@brief	���� ����� ������ ������ ����Ѵ�.
 */
void CConnectedHostsDTO::RegistConnected(CConnectedHostDTO *a_connected)
{
	RemoveConnected(&a_connected->m_hostAddress);
	RemoveConnected(&a_connected->m_userId);
	m_connected.Add(*a_connected);
}

/**@brief	����� ��Ͽ��� Ư�� �����͸� �����Ѵ�.
 * @param	a_key	�����ϰ��� �ϴ� �������� ����� �Ǵ� �¼� id.
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

/**@brief	����� ��Ͽ��� ���ϴ� ���� ������ ã�´�.
 * @param	a_key	ã���� �ϴ� ���� �׸��� ���� id �Ǵ� �¼� id.
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