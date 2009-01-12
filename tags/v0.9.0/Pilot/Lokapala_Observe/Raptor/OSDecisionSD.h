/**@file	OSDecisionSD.h
 * @brief	OSM���� DCM������ Service Delegate ����.
 * @author	siva
 */

#ifndef OSDECISION_SD_H
#define OSDECISION_SD_H

/**@ingroup GroupOSM
 * @class	COSDecisionSD
 * @brief	OSM���� DCM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class COSDecisionSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static COSDecisionSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new COSDecisionSD();
		}
		return m_instance;
	}

	void NotifyExecutedProcess(CString a_executedProcess);

protected :
	/**@brief	������	*/
	COSDecisionSD(){}
	/**@brief	�Ҹ���	*/
	~COSDecisionSD(){}
private :
	/**@brief	singleton.	*/
	static COSDecisionSD *m_instance;
};

#endif