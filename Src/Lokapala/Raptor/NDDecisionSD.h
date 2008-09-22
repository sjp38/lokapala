/**@file	NDDecisionSD.h
 * @brief	NDM���� DCM������ Service Delegate ����.
 * @author	siva
 */

#ifndef NDDECISION_SD_H
#define NDDECISION_SD_H

/**@ingroup GroupNDM
 * @class	CNDDecisionSD
 * @brief	NDM���� DCM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class CNDDecisionSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CNDDecisionSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CNDDecisionSD();
		}
		return m_instance;
	}

protected :
	/**@brief	������	*/
	CNDDecisionSD(){}
	/**@brief	�Ҹ���	*/
	~CNDDecisionSD(){}
private :
	/**@brief	singleton.	*/
	static CNDDecisionSD *m_instance;
};

#endif