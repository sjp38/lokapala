/**@file	RuleDataDTO.h
 * @brief	���� ���� ���μ��� ���� ��Ģ ������ ��� DTO�� �����Ѵ�.
 * @author	siva
 */

#ifndef RULE_DATA_DTO_H
#define RULE_DATA_DTO_H

enum Reactions {SHUTDOWN, REBOOT, LOGOUT, EXUCUTE};

/**@ingroup GroupDAM
 * @class	CRuleDataDTO
 * @brief	���� ���� ���μ��� ���� ��Ģ�� ���� ������ ��´�.
 */
class CRuleDataDTO
{
public :
	CString m_processName;
	CString m_caption;
	/**@brief	��Ģ�� ������ �¼��� id(�¼����� ��Ģ ���� ����)	*/
	CString m_targetSeatId;
	/**@brief	��Ģ�� ������ ���� id(�������� ��Ģ ���� ����)	*/
	CString m_targetUserId;
	enum Reactions m_reaction;
	/**@brief	���׼� �� ����ڿ��� ������ �޼���. ���׼��� EXECUTE ��� ������ ���μ����� ��θ� �ǹ��Ѵ�.	*/
	CString m_reactionArgument;

	CRuleDataDTO(CString a_processName, CString a_caption, 
		CString a_targetSeatId, CString a_targetUserId, 
		enum Reactions a_reaction, CString a_reactionArgument);
	CRuleDataDTO(){}
	~CRuleDataDTO(){}
};


#endif