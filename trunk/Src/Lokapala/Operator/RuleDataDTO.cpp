/**@file	RuleDataDTO.cpp
 * @brief	CRuleDataDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "RuleDataDTO.h"

/**@brief	생성자.	*/
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

/**@brief	RulesData 에서 프로세스 이름만 가지고 룰을 검색하고자 룰을 만들 때의 생성자.
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