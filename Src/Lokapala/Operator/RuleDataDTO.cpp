/**@file	RuleDataDTO.cpp
 * @brief	CRuleDataDTO Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "RuleDataDTO.h"

/**@brief	������.	*/
CRuleDataDTO::CRuleDataDTO(CString a_processName, CString a_caption,
						   CString a_targetSeatId, CString a_targetUserId, int a_targetLevel,
						   Reactions a_reaction, CString a_reactionArgument)
{
	m_processName = a_processName;
	m_caption = a_caption;
	m_targetSeatId = a_targetSeatId;
	m_targetUserId = a_targetUserId;
	m_targetLevel = a_targetLevel;
	m_reaction = a_reaction;
	m_reactionArgument = a_reactionArgument;
}

/**@brief	RulesData ���� ���μ��� �̸��� ������ ���� �˻��ϰ��� ���� ���� ���� ������.
 */
CRuleDataDTO::CRuleDataDTO(CString a_processName)
{
	m_processName = a_processName;
	m_caption = _T("");
	m_targetSeatId = _T("");
	m_targetUserId = _T("");
	m_reaction = WARN;
	m_reactionArgument = _T("");
}