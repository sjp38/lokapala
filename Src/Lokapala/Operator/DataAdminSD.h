#ifndef DATA_ADMIN_SD_H
#define DATA_ADMIN_SD_H

class CDataAdminSD
{
public :
	static CDataAdminSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDataAdminSD();
		}
		return m_instance;
	}

	void ReadDAM();
protected :
	CDataAdminSD(){}
	~CDataAdminSD(){}
private :
	static CDataAdminSD *m_instance;
};

#endif
