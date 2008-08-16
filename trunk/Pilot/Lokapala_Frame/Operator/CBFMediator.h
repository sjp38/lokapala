/*	Common Buisiness Framework Mediator */

#ifndef CBF_MEDIATOR_H
#define CBF_MEDIATOR_H

#include "DataAdminBI.h"
#include "DataAdminFacade.h"
#include "DecisionBI.h"
#include "DecisionFacade.h"
#include "LogBI.h"
#include "LogFacade.h"
#include "CommunicationBI.h"
#include "CommunicationFacade.h"
#include "MessengerBI.h"
#include "MessengerFacade.h"

class CCBFMediator
{
public :
	static CCBFMediator *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CCBFMediator();
		}
		return m_instance;
	}

	//DCM
	void ReadDAM();

protected :
	CCBFMediator(){}
	~CCBFMediator(){}
private :
	static CCBFMediator *m_instance;
};

#endif