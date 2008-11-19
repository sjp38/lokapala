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

	virtual void InitiallizeAsServer();
	virtual void SendTextMessageTo(CString a_targetAddress, CString a_message);
	virtual void BroadcastTextMessage(CString a_message);
	virtual void SendLoginAcceptedNotifyMessage(void *a_acceptedData);
	virtual void SendShutdownInstruction(void *a_argument);
	virtual void SendRebootInstruction(void *a_argument);
	virtual void SendBanUserInstruction(void *a_argument);
	virtual void SendExecuteProcessInstruction(void *a_argument);
	virtual void SendKillProcessInstruction(void *a_argument);
	virtual void SendGenocideProcessInstruction(void *a_argument);
	virtual void SendWarningMessage(void *a_argument);
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