/**@file	CommunicationFacade.h
 * @brief	CCM�� Facade ����.
 * @author	siva
 */

#ifndef COMMUNICATION_FACADE_H
#define COMMUNICATION_FACADE_H

#include "CommunicationBI.h"
/**@ingroup	GroupCCM
 * @class	CCommunicationFacade
 * @brief	CCM�� Facade.\n
			�������� CCM ������ �Ա�. Button Interface�� ����ϸ�, ���� ������Ʈ ���� Ŭ�������� ����� BI���� ���ǵ� �������̽� �Լ����� �����Ѵ�.
 * @remarks	SingleTon�� ����Ѵ�.
 */
class CCommunicationFacade : public CCommunicationBI
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CCommunicationFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CCommunicationFacade();
		}
		return m_instance;
	}

	virtual void Initiallize(DWORD a_ServerAddress);
	virtual void CloseConnection();
	virtual void SendTextMessageToOperator(CString *a_message);
	virtual void SendLoginRequest(void *a_userInfo);
	virtual void SendExecutedProcessReport(CString *a_executedProcess);
	virtual void SendStatusReport(void *a_statusReport);

protected :
	/**@brief	������	*/
	CCommunicationFacade(){}
	/**@brief	�Ҹ���	*/
	~CCommunicationFacade(){}
private :
	/**@brief	singleton.	*/
	static CCommunicationFacade *m_instance;
};

#endif