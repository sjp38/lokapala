#ifndef COMMUNICATION_FACADE_H
#define COMMUNICATION_FACADE_H

#include "CommunicationBI.h"
class CCommunicationFacade : public CCommunicationBI
{
public :
	static CCommunicationFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CCommunicationFacade();
		}
		return m_instance;
	}
protected :
	CCommunicationFacade(){}
	~CCommunicationFacade(){}
private :
	static CCommunicationFacade *m_instance;
};

#endif