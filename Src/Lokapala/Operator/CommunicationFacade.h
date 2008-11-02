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
	virtual void NotifyAccepted(void *a_acceptedData);
	virtual void ShutdownUser(void *a_argument);
	virtual void RebootUser(void *a_argument);
	virtual void LogoutUser(void *a_argument);
	virtual void ExecuteUser(void *a_argument);
	virtual void KillUser(void *a_argument);
	virtual void GenocideUser(void *a_argument);
	virtual void WarnUser(void *a_argument);

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