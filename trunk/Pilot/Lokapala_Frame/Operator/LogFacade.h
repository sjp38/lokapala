#ifndef LOG_FACADE_H
#define LOG_FACADE_H

#include "LogBI.h"
class CLogFacade : public CLogBI
{
public :
	static CLogFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CLogFacade();
		}
		return m_instance;
	}
protected :
	CLogFacade(){}
	~CLogFacade(){}
private :
	static CLogFacade *m_instance;
};

#endif