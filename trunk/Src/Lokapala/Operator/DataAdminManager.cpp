/**@file	DataAdminManager.cpp
 * @brief	CDataAdminManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */


#include "stdafx.h"
#include "DataAdminManager.h"

#include "tinyxml.h"

/**@brief	특정 파일로부터 사용자 데이터를 읽는다.
 *			현재까지는 xml 파일만 지원한다.
 * @param	a_xmlRoot	xml 파일의 루트 엘레먼트의 포인터. void 포인터로 캐스팅해 사용된다.
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

		CUserDataDTO newUser(lowPassword, name, lowPassword, highPassword, level);
		CCBFMediator::Instance()->AddUser(&newUser);
	}	
}

/**@brief	파일로부터 좌석 정보를 읽는다.
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
		CString globalIp = A2W(seat->Attribute("globalIp"));
		CString localIp = A2W(seat->Attribute("localIp"));
		int x,y;
		seat->Attribute("x", &x);
		seat->Attribute("y", &y);
		CString nickname = A2W(seat->Attribute("nickname"));

		CSeatDataDTO newSeat(globalIp, localIp, x, y, nickname);
		CCBFMediator::Instance()->AddSeat(&newSeat);
	}
}

/**@brief	파일로부터 금지프로세스 관련 규칙 정보를 읽어들인다.
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
		
		int action;
		rule->Attribute("reaction", &action);
		enum Reactions reaction = (enum Reactions)action;
		CString argument = A2W(rule->Attribute("argument"));

		CRuleDataDTO newRule(processName, caption, targetSeat, targetUser, reaction, argument);
		CCBFMediator::Instance()->AddRule(&newRule);
	}
}

/**@brief	파일로부터 데이터를 읽는다.
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
}

/**@brief	사용자 정보를 특정 파일에 저장한다.
 * @param	a_xmlRoot	xml의 루트 엘레먼트 포인터.
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

/**@file	좌석 정보를 특정 파일에 저장한다.
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
		seat->SetAttribute("globalIp", W2A(value.m_globalIp));
		seat->SetAttribute("localIp",W2A(value.m_localIp));
		seat->SetAttribute("x",value.m_position.x);
		seat->SetAttribute("y",value.m_position.y);
		seat->SetAttribute("nickname",W2A(value.m_nickname));
	}
}

/**@file	금지 프로세스 규칙 정보를 특정 파일에 저장한다.
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

/**@file	현재 데이터를 파일로 저장한다. 일단 xml 포맷만을 지원한다.
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
	
	USES_CONVERSION;
	doc.SaveFile(W2A(*a_filePath));
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