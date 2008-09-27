/**@file	RulesDataDTO.h
 * @brief	모든 실행 금지 프로세스 관련 규칙을 관리한다.
 * @author	siva
 */

#ifndef RULES_DATA_DTO_H
#define RULES_DATA_DTO_H

#include "RuleDataDTO.h"

class CRulesDataDTO
{
public :
	CArray <CRuleDataDTO, CRuleDataDTO> m_rules;

	void AddRule(CRuleDataDTO *a_rule);
	void DeleteRule(CRuleDataDTO *a_targetRule);

	CRulesDataDTO(){}
	~CRulesDataDTO(){}

private :	
	int FindRule(CRuleDataDTO *a_targetRule);
};


#endif