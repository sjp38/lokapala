/**@file	ControlActionDTO.h
 * @brief	���۷����ͷκ��� ���ͷ��� Ư�� �ൿ�� ���� ������ ��� CControlActionDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */


#ifndef REACTION_DTO
#define REACTION_DTO

/**@ingourp	GroupDAM
 * @class	CControlActionDTO
 * @brief	���۷����ͷκ��� ���ͷ��� ���� �ൿ�� ���� ������ ��´�.
 */
class CControlActionDTO
{
public :
	CString m_targetHostAddress;
	CString m_reactionArgument;
	enum Reactions m_action;
};

#endif