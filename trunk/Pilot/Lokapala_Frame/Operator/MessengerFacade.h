#ifndef MESSENGER_FACADE_H
#define MESSENGER_FACADE_H

#include "MessengerBI.h"
class CMessengerFacade : public CMessengerBI
{
public :
	static CMessengerFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CMessengerFacade();
		}
		return m_instance;
	}
protected :
	CMessengerFacade(){}
	~CMessengerFacade(){}
private :
	static CMessengerFacade *m_instance;
};

#endif