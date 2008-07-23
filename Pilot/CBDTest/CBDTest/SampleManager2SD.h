#ifndef SAMPLE_MANAGER_2_SD_H
#define SAMPLE_MANAGER_2_SD_H

class SampleManager2SD
{
public :
	static SampleManager2SD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new SampleManager2SD();
		}
		return m_instance;
	}

	void CallSampleManager2();
protected :
	SampleManager2SD(){}
	~SampleManager2SD(){}
private :
	static SampleManager2SD *m_instance;
};

#endif