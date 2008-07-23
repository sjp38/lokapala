#ifndef SAMPLE_MANAGER_2_FACADE_H
#define SAMPLE_MANAGER_2_FACADE_H

#include "SampleManager2BI.h"

class SampleManager2Facade : public SampleManager2BI
{
public :
	static SampleManager2Facade *Instance(void)
	{
		if(!m_instance)
		{
			m_instance = new SampleManager2Facade();
		}
		return m_instance;
	}
	void CallSampleManager2(void);

protected :
	SampleManager2Facade(){};
	~SampleManager2Facade(){};
private :
	static SampleManager2Facade *m_instance;
};

#endif