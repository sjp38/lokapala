/**@file	CCDecisionSD.h
 * @brief	CCM���� DCM������ Service Delegate ����.
 * @author	siva
 */

#ifndef CCDECISION_SD_H
#define CCDECISION_SD_H

/**@ingroup GroupCCM
 * @class	CCCDecisionSD
 * @brief	CCM���� DCM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class CCCDecisionSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CCCDecisionSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CCCDecisionSD();
		}
		return m_instance;
	}

	void UserLogin(void *a_loginRequestData);
	void JudgeUserExecutedProcess(void *a_executedProcessData);	
	void PresentStatusReport(void *a_statusReportData);

protected :
	/**@brief	������	*/
	CCCDecisionSD(){}
	/**@brief	�Ҹ���	*/
	~CCCDecisionSD(){}
private :
	/**@brief	singleton.	*/
	static CCCDecisionSD *m_instance;
};

#endif