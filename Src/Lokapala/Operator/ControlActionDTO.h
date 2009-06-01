/**@file	ControlActionDTO.h
 * @brief	오퍼레이터로부터 랩터로의 특정 행동에 대한 정보를 담는 CControlActionDTO 클래스를 정의한다.
 * @author	siva
 */


#ifndef REACTION_DTO
#define REACTION_DTO

/**@ingourp	GroupDAM
 * @class	CControlActionDTO
 * @brief	오퍼레이터로부터 랩터로의 제어 행동에 대한 정보를 담는다.
 */
class CControlActionDTO
{
public :
	CString m_targetHostAddress;
	CString m_reactionArgument;
	enum Reactions m_action;
};

#endif
