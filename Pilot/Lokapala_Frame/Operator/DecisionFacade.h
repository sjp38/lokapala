#ifndef DECISION_FACADE_H
#define DECISION_FACADE_H

#include "DecisionBI.h"

class CDecisionFacade : public CDecisionBI
{
public :
	static CDecisionFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDecisionFacade();
		}
		return m_instance;
	}
protected :
	CDecisionFacade(){}
	~CDecisionFacade(){}
private :
	static CDecisionFacade *m_instance;
			
};

#endif