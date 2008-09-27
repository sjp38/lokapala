/**@file	RuleDataDTO.cpp
 * @brief	CRuleDataDTO 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "RuleDataDTO.h"

CRuleDataDTO::CRuleDataDTO(CString a_processName, CString a_caption,
						   CString a_targetSeatId, CString a_targetUserId, 
						   Reactions a_reaction, CString a_reactionArgument)
{
	m_processName = a_processName;
	m_caption = a_caption;
	m_targetSeatId = a_targetSeatId;
	a_targetUserId = a_targetUserId;
	m_reaction = a_reaction;
	m_reactionArgument = a_reactionArgument;
}