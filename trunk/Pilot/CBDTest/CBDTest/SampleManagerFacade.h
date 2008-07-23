#ifndef SAMPLE_MANAGER_FACADE_H
#define SAMPLE_MANAGER_FACADE_H

#include "SampleManagerBI.h"
#include "SampleManager2SD.h"

class SampleManagerFacade : public SampleManagerBI
{
public :
	static SampleManagerFacade *Instance(void)
	{
		if(!m_instance)
		{
			m_instance = new SampleManagerFacade();
		}
		return m_instance;
	}

	void CallSampleManager();

protected :
	SampleManagerFacade(){}
	~SampleManagerFacade(){}
private :
	static SampleManagerFacade *m_instance;
};

#endif