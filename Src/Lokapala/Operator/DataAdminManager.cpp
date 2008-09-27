/**@file	DataAdminManager.cpp
 * @brief	CDataAdminManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */


#include "stdafx.h"
#include "DataAdminManager.h"

void CDataAdminManager::LoadUserDataFrom(CFile *a_file)
{
	
}

/**@brief	파일로부터 데이터를 읽는다.
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

/**@file	사용자 정보를 특정 파일에 저장한다.
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

/**@file	좌석 정보를 특정 파일에 저장한다.
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

/**@file	금지 프로세스 규칙 정보를 특정 파일에 저장한다.
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

/**@file	현재 데이터를 파일로 저장한다.
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

/**@brief	유저 하나의 정보를 추가한다.
 * @param	a_user	유저 정보체(DTO).\n
 *					아규먼트 전달 오버헤드를 줄이기 위해 포인터를 사용하며, 노출성을 줄이기 위해 void 포인터로 캐스팅해 받는다.
 */
void CDataAdminManager::AddUser(void *a_user)
{
	m_usersData.AddUser((CUserDataDTO *)a_user);
}

/**@brief	유저 하나를 삭제한다.
 */
void CDataAdminManager::DeleteUser(CString *a_id)
{
	m_usersData.DeleteUser(a_id);
}

/**@brief	유저 전체 정보 DTO의 포인터를 알려준다.
 * @return	실제 데이터 관리에 사용하는 UsersDataDTO의 포인터.
 */
CUsersDataDTO *CDataAdminManager::GetUsers()
{
	return &m_usersData;
}




/**@brief	좌석 전체 크기 설정
 */
void CDataAdminManager::SetSeats(int a_x, int a_y)
{
	m_seatsData.SetSeats(a_x, a_y);
}

/**@brief	좌석 정보 추가
 * @param	a_seat	좌석 정보체(DTO).\n
 *					아규먼트 전달 오버헤드를 줄이기 위해 포인터를 사용하며, 노출성을 줄이기 위해 void 포인터로 캐스팅해 받는다.
 */
void CDataAdminManager::AddSeat(void *a_seat)
{
	m_seatsData.AddSeat((CSeatDataDTO *)a_seat);
}

/**@brief	좌석 정보 삭제
 */
void CDataAdminManager::DeleteSeat(int a_x, int a_y)
{
	m_seatsData.DeleteSeat(a_x, a_y);
}

/**@brief	전체 좌석 정보를 넘겨준다.
 */
CSeatsDataDTO *CDataAdminManager::GetSeats()
{
	return &m_seatsData;
}




/**@brief	금지 프로세스 관련 규칙 하나를 추가한다.
 * @param	a_rule	규칙 정보체(DTO).\n
 *					아규먼트 전달 오버헤드를 줄이기 위해 포인터를 사용하며, 노출성을 줄이기 위해 void 포인터로 캐스팅해 받는다.
 */
void CDataAdminManager::AddRule(void *a_rule)
{
	m_rulesData.AddRule((CRuleDataDTO *)a_rule);
}


/**@brief	금지 프로세스 관련 규칙 하나를 삭제한다.
 * @param	a_rule	규칙 정보체(DTO).\n
 *					아규먼트 전달 오버헤드를 줄이기 위해 포인터를 사용하며, 노출성을 줄이기 위해 void 포인터로 캐스팅해 받는다.
 */
void CDataAdminManager::DeleteRule(void *a_rule)
{
	m_rulesData.DeleteRule((CRuleDataDTO *)a_rule);
}

/**@brief	전체 규칙을 넘긴다.
 */
CRulesDataDTO *CDataAdminManager::GetRules()
{
	return &m_rulesData;
}