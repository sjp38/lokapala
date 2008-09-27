/**@file	RulesDataDTO.cpp
 * @brief	CRulesDataDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "RulesDataDTO.h"


/**@brief	���� ���μ��� ���� ��Ģ �ϳ��� �߰��Ѵ�.
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

/**@brief	���� ���μ��� ���� ��Ģ �ϳ��� �����Ѵ�.
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


/**@brief	Ư�� ���� ���μ��� ���� ��Ģ�� ã�Ƴ���.
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