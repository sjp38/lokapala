/**@file	DCLogSD.h
 * @brief	DCM���� LGM������ Service Delegate ����.
 * @author	siva
 */

#ifndef DCLOG_SD_H
#define DCLOG_SD_H

/**@ingroup GroupDCM
 * @class	CDCLogSD
 * @brief	DCM���� LGM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class CDCLogSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CDCLogSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDCLogSD();
		}
		return m_instance;
	}

protected :
	/**@brief	������	*/
	CDCLogSD(){}
	/**@brief	�Ҹ���	*/
	~CDCLogSD(){}
private :
	/**@brief	singleton.	*/
	static CDCLogSD *m_instance;
};

#endif