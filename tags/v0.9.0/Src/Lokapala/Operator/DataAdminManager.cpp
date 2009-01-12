/**@file	DataAdminManager.cpp
 * @brief	CDataAdminManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */


#include "stdafx.h"
#include "DataAdminManager.h"

#include "tinyxml.h"

/**@brief	Ư�� ���Ϸκ��� ����� �����͸� �д´�.
 *			��������� xml ���ϸ� �����Ѵ�.
 * @param	a_xmlRoot	xml ������ ��Ʈ ������Ʈ�� ������. void �����ͷ� ĳ������ ���ȴ�.
 */
void CDataAdminManager::LoadUserDataFrom(void *a_xmlRoot)
{
	TiXmlElement *root = (TiXmlElement *)a_xmlRoot;
	TiXmlElement *users = root->FirstChildElement("Users");
	TiXmlElement *user = users->FirstChildElement("User");
	USES_CONVERSION;
	for(user;user;user = user->NextSiblingElement())
	{
		CString name = A2W(user->Attribute("name"));
		CString lowPassword = A2W(user->Attribute("lowPassword"));
		CString highPassword = A2W(user->Attribute("highPassword"));
		int level;
		user->Attribute("level", &level);

		CUserDataDTO newUser(lowPassword, name, lowPassword, level, highPassword);
		CCBFMediator::Instance()->AddUser(&newUser);
	}	
}

/**@brief	���Ϸκ��� �¼� ������ �д´�.
 */
void CDataAdminManager::LoadSeatDataFrom(void *a_xmlRoot)
{
	TiXmlElement *root = (TiXmlElement *)a_xmlRoot;
	TiXmlElement *seats = root->FirstChildElement("Seats");
	int maxX, maxY;
	seats->Attribute("maxX", &maxX);
	seats->Attribute("maxY", &maxY);
	m_seatsData.SetSeats(maxX, maxY);

	TiXmlElement *seat = seats->FirstChildElement("Seat");
	USES_CONVERSION;
	for(seat; seat; seat = seat->NextSiblingElement())
	{
		CString hostAddress = A2W(seat->Attribute("hostAddress"));
		int x,y;
		seat->Attribute("x", &x);
		seat->Attribute("y", &y);
		CString nickname = A2W(seat->Attribute("nickname"));

		CSeatDataDTO newSeat(hostAddress, x, y, nickname);
		CCBFMediator::Instance()->AddSeat(&newSeat);
	}
}

/**@brief	���Ϸκ��� �������μ��� ���� ��Ģ ������ �о���δ�.
 */
void CDataAdminManager::LoadRuleDataFrom(void *a_xmlRoot)
{
	TiXmlElement *root = (TiXmlElement *)a_xmlRoot;
	TiXmlElement *rules = root->FirstChildElement("Rules");
	
	TiXmlElement *rule = rules->FirstChildElement("Rule");
	USES_CONVERSION;
	for(rule; rule; rule = rule->NextSiblingElement())
	{
		CString processName = A2W(rule->Attribute("processName"));
		CString caption = A2W(rule->Attribute("caption"));
		CString targetSeat = A2W(rule->Attribute("targetSeat"));
		CString targetUser = A2W(rule->Attribute("targetUser"));
		int targetLevel;
		rule->Attribute("targetLevel", &targetLevel);
		
		int action;
		rule->Attribute("reaction", &action);
		enum Reactions reaction = (enum Reactions)action;
		CString argument = A2W(rule->Attribute("argument"));

		CRuleDataDTO newRule(processName, caption, targetSeat, targetUser, targetLevel, reaction, argument);
		CCBFMediator::Instance()->AddRule(&newRule);
	}
}

/**@brief	���Ϸκ��� ���� ���� �����͸� �о���δ�.
 */
void CDataAdminManager::LoadStatusReportsFrom(void *a_xmlRoot)
{
	TiXmlElement *root = (TiXmlElement *)a_xmlRoot;
	TiXmlElement *statusReports = root->FirstChildElement("StatusReports");

	TiXmlElement *statusReport = statusReports->FirstChildElement("StatusReport");
	USES_CONVERSION;
	for(statusReport; statusReport; statusReport = statusReport->NextSiblingElement())
	{
		CString hostAddress = A2W(statusReport->Attribute("hostAddress"));
		int state;
		statusReport->Attribute("state", &state);		
		CString date = A2W(statusReport->Attribute("date"));
		CString comment = A2W(statusReport->Attribute("comment"));

		CStatusReportDTO newStateReport(hostAddress, (State)state, date, comment);
		m_statusReports.AddReport(&newStateReport);
	}

}

/**@brief	���Ϸκ��� �����͸� �д´�.
 */
void CDataAdminManager::LoadFromFile(CString *a_filePath)
{	
	USES_CONVERSION;
	TiXmlDocument document(W2A(*a_filePath));
	document.LoadFile();
	TiXmlElement *root = document.FirstChildElement("Datas");
	if(root==NULL)
	{
		AfxMessageBox(_T("invalid xml file!"));
		return;
	}

	LoadUserDataFrom(root);
	LoadSeatDataFrom(root);
	LoadRuleDataFrom(root);

	LoadStatusReportsFrom(root);
}

/**@brief	����� ������ Ư�� ���Ͽ� �����Ѵ�.
 * @param	a_xmlRoot	xml�� ��Ʈ ������Ʈ ������.
 */
void CDataAdminManager::SaveUserDataTo(void *a_xmlRoot)
{
	TiXmlElement *root = (TiXmlElement *)a_xmlRoot;

	TiXmlComment *comment = new TiXmlComment();
	comment->SetValue("data for user informations");
	root->LinkEndChild(comment);

	TiXmlElement *users = new TiXmlElement("Users");
	root->LinkEndChild(users);


	USES_CONVERSION;
	POSITION pos = m_usersData.m_users.GetStartPosition();
	CString key;
	CUserDataDTO value;
	while(pos != NULL)
	{
		m_usersData.m_users.GetNextAssoc(pos, key, value);
		TiXmlElement *user = new TiXmlElement("User");
		users->LinkEndChild(user);
		user->SetAttribute("name",W2A(value.m_name));
		user->SetAttribute("lowPassword",W2A(value.m_lowLevelPassword));
		user->SetAttribute("highPassword",W2A(value.m_highLevelPassword));
		user->SetAttribute("level",value.m_level);
	}
}

/**@file	�¼� ������ Ư�� ���Ͽ� �����Ѵ�.
 */
void CDataAdminManager::SaveSeatDataTo(void *a_xmlRoot)
{
	TiXmlElement *root = (TiXmlElement *)a_xmlRoot;

	TiXmlComment *comment = new TiXmlComment();
	comment->SetValue("data for seat informations");
	root->LinkEndChild(comment);

	TiXmlElement *seats = new TiXmlElement("Seats");
	root->LinkEndChild(seats);
	seats->SetAttribute("maxX", m_seatsData.m_maxX);
	seats->SetAttribute("maxY", m_seatsData.m_maxY);


	USES_CONVERSION;
	POSITION pos = m_seatsData.m_seats.GetStartPosition();
	CString key;
	CSeatDataDTO value;
	while(pos != NULL)
	{
		m_seatsData.m_seats.GetNextAssoc(pos, key, value);
		TiXmlElement *seat = new TiXmlElement("Seat");
		seats->LinkEndChild(seat);
		seat->SetAttribute("hostAddress", W2A(value.m_hostAddress));
		seat->SetAttribute("x",value.m_position.x);
		seat->SetAttribute("y",value.m_position.y);
		seat->SetAttribute("nickname",W2A(value.m_nickname));
	}
}

/**@file	���� ���μ��� ��Ģ ������ Ư�� ���Ͽ� �����Ѵ�.
 */
void CDataAdminManager::SaveRuleDataTo(void *a_xmlRoot)
{
	TiXmlElement *root = (TiXmlElement *)a_xmlRoot;

	TiXmlComment *comment = new TiXmlComment();
	comment->SetValue("data for rule informations");
	root->LinkEndChild(comment);

	TiXmlElement *rules = new TiXmlElement("Rules");
	root->LinkEndChild(rules);

	USES_CONVERSION;
	for(int i=0; i<m_rulesData.m_rules.GetCount(); i++)
	{
		TiXmlElement *rule = new TiXmlElement("Rule");
		rules->LinkEndChild(rule);
		rule->SetAttribute("processName", W2A(m_rulesData.m_rules[i].m_processName));
		rule->SetAttribute("caption", W2A(m_rulesData.m_rules[i].m_caption));
		rule->SetAttribute("targetSeat", W2A(m_rulesData.m_rules[i].m_targetSeatId));
		rule->SetAttribute("targetUser", W2A(m_rulesData.m_rules[i].m_targetUserId));
		rule->SetAttribute("reaction", m_rulesData.m_rules[i].m_reaction);
		rule->SetAttribute("argument", W2A(m_rulesData.m_rules[i].m_reactionArgument));
	}
}

void CDataAdminManager::SaveStatusReportsTo(void *a_xmlRoot)
{
	TiXmlElement *root = (TiXmlElement *)a_xmlRoot;

	TiXmlComment *comment = new TiXmlComment();
	comment->SetValue("data for status reports");
	root->LinkEndChild(comment);

	TiXmlElement *statusReports = new TiXmlElement("StatusReports");
	root->LinkEndChild(statusReports);

	USES_CONVERSION;
	for(int i=0; i<m_statusReports.m_reports.GetCount(); i++)
	{
		TiXmlElement *statusReport = new TiXmlElement("StatusReport");
		statusReports->LinkEndChild(statusReport);
		statusReport->SetAttribute("hostAddress", W2A(m_statusReports.m_reports[i].m_hostAddress));
		statusReport->SetAttribute("state", m_statusReports.m_reports[i].m_state);
		statusReport->SetAttribute("date", W2A(m_statusReports.m_reports[i].m_date));
		statusReport->SetAttribute("comment", W2A(m_statusReports.m_reports[i].m_comment));
	}
}

/**@file	���� �����͸� ���Ϸ� �����Ѵ�. �ϴ� xml ���˸��� �����Ѵ�.
 */
void CDataAdminManager::SaveToFile(CString *a_filePath)
{
	TiXmlDocument doc;
	TiXmlDeclaration *decl = new TiXmlDeclaration( "1.0", "euc-kr", "" );
	doc.LinkEndChild( decl );

	TiXmlElement *root = new TiXmlElement( "Datas" );
	doc.LinkEndChild( root );

	SaveUserDataTo(root);
	SaveSeatDataTo(root);
	SaveRuleDataTo(root);

	SaveStatusReportsTo(root);
	
	USES_CONVERSION;
	doc.SaveFile(W2A(*a_filePath));
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
void CDataAdminManager::DeleteSeat(void *a_seatId)
{
	m_seatsData.DeleteSeat((CString *)a_seatId);
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


/**@brief	��ü ���� ���� ���� �ѱ��.
 */
CStatusReportsDTO *CDataAdminManager::GetStatusReports()
{
	return &m_statusReports;
}



/**@brief	���ӵ� ����� ������ �ѱ��.
 */
CConnectedHostsDTO *CDataAdminManager::GetConnectedHosts()
{
	return &m_connectedHosts;
}