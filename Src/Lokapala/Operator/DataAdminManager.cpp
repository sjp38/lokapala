/**@file	DataAdminManager.cpp
 * @brief	CDataAdminManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */


#include "stdafx.h"
#include "DataAdminManager.h"

void CDataAdminManager::LoadUserDataFrom(CFile *a_file)
{
	
}

/**@brief	���Ϸκ��� �����͸� �д´�.
 */
void CDataAdminManager::LoadFromFile(CString *a_filePath)
{
	CFile file;
	if(!file.Open(*a_filePath, CFile::modeRead))
	{
		AfxMessageBox(_T("fail to open file!"));
		return;
	}
	LoadUserDataFrom(&file);
	//LoadSeatDataFrom(&file);
	//LoadRuleDataFrom(&file);
	
	file.Close();
}

/**@file	����� ������ Ư�� ���Ͽ� �����Ѵ�.
 */
void CDataAdminManager::SaveUserDataTo(CFile *a_file)
{
	USES_CONVERSION;
	CString userData;
	char *data;
	userData = _T("user data\n");
	data = W2A(userData);
	a_file->Write(data, strlen(data));

	POSITION pos = m_usersData.m_users.GetStartPosition();
	CString key;
	CUserDataDTO value;
	while(pos != NULL)
	{
		m_usersData.m_users.GetNextAssoc(pos, key, value);
		userData.Format(_T("%s\n%s\n%s\n%s\n%d\n"),
			value.m_userId, value.m_name, value.m_lowLevelPassword, value.m_highLevelPassword, value.m_level);
		data = W2A(userData);
		a_file->Write(data, strlen(data));
	}
}

/**@file	�¼� ������ Ư�� ���Ͽ� �����Ѵ�.
 */
void CDataAdminManager::SaveSeatDataTo(CFile *a_file)
{
	USES_CONVERSION;
	CString seatData;
	char *data;
	seatData.Format(_T("seat data\n%d\n%d\n"), m_seatsData.m_maxX, m_seatsData.m_maxY);
	data = W2A(seatData);
	a_file->Write(data, strlen(data));

	POSITION pos = m_seatsData.m_seats.GetStartPosition();
	CString key;
	CSeatDataDTO value;
	while(pos != NULL)
	{
		m_seatsData.m_seats.GetNextAssoc(pos, key, value);
		seatData.Format(_T("%s\n%s\n%d\n%d\n%s\n"),
			value.m_globalIp, value.m_localIp, value.m_position.x, value.m_position.y, value.m_nickname);
		data =W2A(seatData);
			
		a_file->Write(data, strlen(data));
	}
}

/**@file	���� ���μ��� ��Ģ ������ Ư�� ���Ͽ� �����Ѵ�.
 */
void CDataAdminManager::SaveRuleDataTo(CFile *a_file)
{
	USES_CONVERSION;
	char *data;
	CString ruleData;
	ruleData = _T("rule data\n");
	data = W2A(ruleData);
	a_file->Write(data, strlen(data));
	for(int i=0; i<m_rulesData.m_rules.GetCount(); i++)
	{
		CRuleDataDTO rule = m_rulesData.m_rules[i];
		ruleData.Format(_T("%s\n%s\n%s\n%s\n%d\n%s"), 
			rule.m_processName, rule.m_caption, rule.m_targetSeatId, rule.m_targetUserId, rule.m_reaction, rule.m_reactionArgument);
		data = W2A(ruleData);
		a_file->Write(data, strlen(data));
	}
}

/**@file	���� �����͸� ���Ϸ� �����Ѵ�.
 */
void CDataAdminManager::SaveToFile(CString *a_filePath)
{
	CFile file;
	if(!file.Open(*a_filePath, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox(_T("fail to open file!"));
		return;
	}
	SaveUserDataTo(&file);
	SaveSeatDataTo(&file);
	SaveRuleDataTo(&file);
	
	file.Close();	
}

/**@brief	���� �ϳ��� ������ �߰��Ѵ�.
 * @param	a_user	���� ����ü(DTO).\n
 *					�ƱԸ�Ʈ ���� ������带 ���̱� ���� �����͸� ����ϸ�, ���⼺�� ���̱� ���� void �����ͷ� ĳ������ �޴´�.
 */
void CDataAdminManager::AddUser(void *a_user)
{
	m_usersData.AddUser((CUserDataDTO *)a_user);
}

/**@brief	���� �ϳ��� �����Ѵ�.
 */
void CDataAdminManager::DeleteUser(CString *a_id)
{
	m_usersData.DeleteUser(a_id);
}

/**@brief	���� ��ü ���� DTO�� �����͸� �˷��ش�.
 * @return	���� ������ ������ ����ϴ� UsersDataDTO�� ������.
 */
CUsersDataDTO *CDataAdminManager::GetUsers()
{
	return &m_usersData;
}




/**@brief	�¼� ��ü ũ�� ����
 */
void CDataAdminManager::SetSeats(int a_x, int a_y)
{
	m_seatsData.SetSeats(a_x, a_y);
}

/**@brief	�¼� ���� �߰�
 * @param	a_seat	�¼� ����ü(DTO).\n
 *					�ƱԸ�Ʈ ���� ������带 ���̱� ���� �����͸� ����ϸ�, ���⼺�� ���̱� ���� void �����ͷ� ĳ������ �޴´�.
 */
void CDataAdminManager::AddSeat(void *a_seat)
{
	m_seatsData.AddSeat((CSeatDataDTO *)a_seat);
}

/**@brief	�¼� ���� ����
 */
void CDataAdminManager::DeleteSeat(int a_x, int a_y)
{
	m_seatsData.DeleteSeat(a_x, a_y);
}

/**@brief	��ü �¼� ������ �Ѱ��ش�.
 */
CSeatsDataDTO *CDataAdminManager::GetSeats()
{
	return &m_seatsData;
}




/**@brief	���� ���μ��� ���� ��Ģ �ϳ��� �߰��Ѵ�.
 * @param	a_rule	��Ģ ����ü(DTO).\n
 *					�ƱԸ�Ʈ ���� ������带 ���̱� ���� �����͸� ����ϸ�, ���⼺�� ���̱� ���� void �����ͷ� ĳ������ �޴´�.
 */
void CDataAdminManager::AddRule(void *a_rule)
{
	m_rulesData.AddRule((CRuleDataDTO *)a_rule);
}


/**@brief	���� ���μ��� ���� ��Ģ �ϳ��� �����Ѵ�.
 * @param	a_rule	��Ģ ����ü(DTO).\n
 *					�ƱԸ�Ʈ ���� ������带 ���̱� ���� �����͸� ����ϸ�, ���⼺�� ���̱� ���� void �����ͷ� ĳ������ �޴´�.
 */
void CDataAdminManager::DeleteRule(void *a_rule)
{
	m_rulesData.DeleteRule((CRuleDataDTO *)a_rule);
}

/**@brief	��ü ��Ģ�� �ѱ��.
 */
CRulesDataDTO *CDataAdminManager::GetRules()
{
	return &m_rulesData;
}