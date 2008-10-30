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

/**@brief	���� ���μ��� ���� ��Ģ �ϳ��� �����Ѵ�. �迭 �������� ��ġ�� �̿��ϵ��� �����ε�Ǿ���.
 * @param	a_position	��Ģ �迭 ������ �����ϰ��� �ϴ� ��Ģ�� �ε���
 */
void CRulesDataDTO::DeleteRule(int a_position)
{
	m_rules.RemoveAt(a_position);
}


/**@brief	Ư�� ����� ���μ����� ����, �ش��ϴ� ��Ģ�� �˻��ؼ� �˷��ش�.
 * @param	a_searchedRules	�˻��� ��Ģ�� �޾� �� ������.
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
			|| m_rules[i].m_targetUserId.Find() != -1 )*/	//�ϴ� target user�� ����.
		  )
		{
			a_searchedRules->AddRule(&m_rules[i]);
		}
	}
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