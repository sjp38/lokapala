/**@file	RulesDataDTO.h
 * @brief	��� ���� ���� ���μ��� ���� ��Ģ�� �����Ѵ�.
 * @author	siva
 */

#ifndef RULES_DATA_DTO_H
#define RULES_DATA_DTO_H

#include "RuleDataDTO.h"
#include "ExecutedProcessDTO.h"

class CRulesDataDTO
{
public :
	CArray <CRuleDataDTO, CRuleDataDTO> m_rules;

	void AddRule(CRuleDataDTO *a_rule);
	void DeleteRule(CRuleDataDTO *a_targetRule);

	void GetReactionsFor(CExecutedProcessDTO *a_executedProcess, CRulesDataDTO *a_searchedRules);

	CRulesDataDTO(){}
	~CRulesDataDTO(){}

private :	
	int FindRule(CRuleDataDTO *a_targetRule);
};


#endif