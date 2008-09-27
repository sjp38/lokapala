/**@file	RuleDataDTO.h
 * @brief	실행 금지 프로세스 관련 규칙 정보를 담는 DTO를 정의한다.
 * @author	siva
 */

#ifndef RULE_DATA_DTO_H
#define RULE_DATA_DTO_H

enum Reactions {SHUTDOWN, REBOOT, LOGOUT, EXUCUTE};

/**@ingroup GroupDAM
 * @class	CRuleDataDTO
 * @brief	실행 금지 프로세스 관련 규칙에 대한 정보를 담는다.
 */
class CRuleDataDTO
{
public :
	CString m_processName;
	CString m_caption;
	/**@brief	규칙을 적용할 좌석의 id(좌석별로 규칙 적용 가능)	*/
	CString m_targetSeatId;
	/**@brief	규칙을 적용할 유저 id(유저별로 규칙 적용 가능)	*/
	CString m_targetUserId;
	enum Reactions m_reaction;
	/**@brief	리액션 시 사용자에게 전송할 메세지. 리액션이 EXECUTE 라면 실행할 프로세스의 경로를 의미한다.	*/
	CString m_reactionArgument;

	CRuleDataDTO(CString a_processName, CString a_caption, 
		CString a_targetSeatId, CString a_targetUserId, 
		enum Reactions a_reaction, CString a_reactionArgument);
	CRuleDataDTO(){}
	~CRuleDataDTO(){}
};


#endif