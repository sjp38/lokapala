/**@file	RuleDataDTO.h
 * @brief	���� ���� ���μ��� ���� ��Ģ ������ ��� DTO�� �����Ѵ�.
 * @author	siva
 */

#ifndef RULE_DATA_DTO_H
#define RULE_DATA_DTO_H

enum Reactions {SHUTDOWN, REBOOT, LOGOUT, EXECUTE, KILL, GENOCIDEPROCESSES, WARN};

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
	/**@brief	��Ģ�� ������ ������ �ִ� ����	*/
	int m_targetLevel;
	enum Reactions m_reaction;
	/**@brief	���׼� �� ����ڿ��� ������ �޼���. ���׼��� EXECUTE ��� ������ ���μ����� ��θ� �ǹ��Ѵ�.	*/
	CString m_reactionArgument;

	CRuleDataDTO(CString a_processName, CString a_caption, 
		CString a_targetSeatId, CString a_targetUserId, int a_targetLevel,
		enum Reactions a_reaction, CString a_reactionArgument);
	CRuleDataDTO(CString a_processName);
	CRuleDataDTO(){}
	~CRuleDataDTO(){}
};


#endif