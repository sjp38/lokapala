#ifndef CBF_MEDIATOR_H
#define CBF_MEDIATOR_H

#include "SampleManagerBI.h"
#include "SampleManagerFacade.h"
#include "SampleManager2BI.h"
#include "SampleManager2Facade.h"

class CBFMediator
{
public :
	static CBFMediator *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CBFMediator();
		}
		return m_instance;
	}
	//SM
	void CallSampleManager(void);

	//SM2
	void CallSampleManager2(void);


protected :
	CBFMediator(){}
private :
	static CBFMediator *m_instance;
};

#endif