/**@file	DecisionManager.h
 * @brief	실질적 DCM의 행동을 하는 CDecisionManager 클래스를 정의한다.
 * @author	siva
 */

#ifndef DECISION_MANAGER_H
#define DECISION_MANAGER_H


/**@ingroup	GroupDCM
 * @class	CDecisionManager
 * @brief	랩터의 전체적 동작을 결정/행동한다.
 */
class CDecisionManager
{
public :
	static CDecisionManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDecisionManager();
		}
		return m_instance;
	}

	void LoginRequest(void *a_userInfo);
	void LoginAccepted(int a_level);

protected :
	CDecisionManager(){}
	~CDecisionManager(){}

private :
	static CDecisionManager *m_instance;
};

#endif