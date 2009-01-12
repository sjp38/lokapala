/**@file	MSLogSD.h
 * @brief	MSM���� LGM������ Service Delegate ����.
 * @author	siva
 */

#ifndef MSLOG_SD_H
#define MSLOG_SD_H

/**@ingroup GroupMSM
 * @class	CMSLogSD
 * @brief	MSM���� LGM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class CMSLogSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CMSLogSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CMSLogSD();
		}
		return m_instance;
	}

protected :
	/**@brief	������	*/
	CMSLogSD(){}
	/**@brief	�Ҹ���	*/
	~CMSLogSD(){}
private :
	/**@brief	singleton.	*/
	static CMSLogSD *m_instance;
};

#endif