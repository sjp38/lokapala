/**@file	DCNeverDieSD.h
 * @brief	DCM���� NDM������ Service Delegate ����.
 * @author	siva
 */

#ifndef DCNEVERDIE_SD_H
#define DCNEVERDIE_SD_H

/**@ingroup GroupDCM
 * @class	CDCNeverDieSD
 * @brief	DCM���� NDM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class CDCNeverDieSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CDCNeverDieSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDCNeverDieSD();
		}
		return m_instance;
	}

protected :
	/**@brief	������	*/
	CDCNeverDieSD(){}
	/**@brief	�Ҹ���	*/
	~CDCNeverDieSD(){}
private :
	/**@brief	singleton.	*/
	static CDCNeverDieSD *m_instance;
};

#endif