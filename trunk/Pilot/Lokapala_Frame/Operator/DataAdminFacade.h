#ifndef DATA_ADMIN_FACADE_H
#define DATA_ADMIN_FACADE_H

#include "DataAdminBI.h"
class CDataAdminFacade : public CDataAdminBI
{
public :
	static CDataAdminFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDataAdminFacade();
		}
		return m_instance;
	}

	void Read();
protected :
	CDataAdminFacade(){}
	~CDataAdminFacade(){}
private :
	static CDataAdminFacade *m_instance;
};

#endif