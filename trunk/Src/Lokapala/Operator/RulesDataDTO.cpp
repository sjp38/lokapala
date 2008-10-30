/**@file	RulesDataDTO.cpp
 * @brief	CRulesDataDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "RulesDataDTO.h"


/**@brief	금지 프로세스 관련 규칙 하나를 추가한다.
 */
void CRulesDataDTO::AddRule(CRuleDataDTO *a_rule)
{
	if( FindRule(a_rule) != -1)
	{
		AfxMessageBox(_T("same rule exist!!"));
		return;
	}
	m_rules.Add(*a_rule);
}

/**@brief	금지 프로세스 관련 규칙 하나를 제거한다.
 */
void CRulesDataDTO::DeleteRule(CRuleDataDTO *a_targetRule)
{
	int cursor = FindRule(a_targetRule);
	if( cursor != -1 )
	{
		m_rules.RemoveAt(cursor);		
		return;
	}
	AfxMessageBox(_T("delete fail! no such rules!"));
	return;
}

/**@brief	금지 프로세스 관련 규칙 하나를 제거한다. 배열 내에서의 위치를 이용하도록 오버로드되었다.
 * @param	a_position	규칙 배열 내에서 제거하고자 하는 규칙의 인덱스
 */
void CRulesDataDTO::DeleteRule(int a_position)
{
	m_rules.RemoveAt(a_position);
}


/**@brief	특정 실행된 프로세스에 대해, 해당하는 규칙을 검색해서 알려준다.
 * @param	a_searchedRules	검색된 규칙을 받아 갈 포인터.
 */
void CRulesDataDTO::GetReactionsFor(CExecutedProcessDTO *a_executedProcess, CRulesDataDTO *a_searchedRules)
{
	CString seatId = a_executedProcess->m_executedGlobalIp + _T("/") + a_executedProcess->m_executedLocalIp;

	for(int i=0; i<m_rules.GetCount(); i++)
	{
		if( ( m_rules[i].m_processName == _T("")
			|| m_rules[i].m_processName.Find(a_executedProcess->m_executedProcessName) != -1 )
			&&
			( m_rules[i].m_targetSeatId == _T("")
			|| m_rules[i].m_targetSeatId.Find(seatId) != -1 )
			/*&&
			( m_rules[i].m_targetUserId == _T("")
			|| m_rules[i].m_targetUserId.Find() != -1 )*/	//일단 target user는 유보.
		  )
		{
			a_searchedRules->AddRule(&m_rules[i]);
		}
	}
}


/**@brief	특정 금지 프로세스 관련 규칙을 찾아낸다.
 */
int CRulesDataDTO::FindRule(CRuleDataDTO *a_targetRule)
{
	for(int i=0; i<m_rules.GetCount(); i++)
	{
		if( a_targetRule->m_processName == m_rules[i].m_processName
			&& a_targetRule->m_caption == m_rules[i].m_caption
			&& a_targetRule->m_targetSeatId == m_rules[i].m_targetSeatId
			&& a_targetRule->m_targetUserId == m_rules[i].m_targetUserId
			&& a_targetRule->m_reaction == m_rules[i].m_reaction
			&& a_targetRule->m_reactionArgument == m_rules[i].m_reactionArgument )
		{
			return i;
		}
	}
	return -1;
}