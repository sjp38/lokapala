/**@file	CCMessengerSD.h
 * @brief	CCM���� MSM������ Service Delegate ����.
 * @author	siva
 */

#ifndef CCMESSENGER_SD_H
#define CCMESSENGER_SD_H

/**@ingroup GroupCCM
 * @class	CCCMessengerSD
 * @brief	CCM���� MSM������ Service Delegate.
 * @remarks	singleton�� ����Ѵ�.
 */
class CCCMessengerSD
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CCCMessengerSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CCCMessengerSD();
		}
		return m_instance;
	}

	void TexeMessageReceived(CString a_message);

protected :
	/**@brief	������	*/
	CCCMessengerSD(){}
	/**@brief	�Ҹ���	*/
	~CCCMessengerSD(){}
private :
	/**@brief	singleton.	*/
	static CCCMessengerSD *m_instance;
};

#endif