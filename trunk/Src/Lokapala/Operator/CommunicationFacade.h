/**@file	CommunicationFacade.h
 * @brief	CCM의 Facade 정의.
 * @author	siva
 */

#ifndef COMMUNICATION_FACADE_H
#define COMMUNICATION_FACADE_H

#include "CommunicationBI.h"
/**@ingroup	GroupCCM
 * @class	CCommunicationFacade
 * @brief	CCM의 Facade.\n
			실질적인 CCM 으로의 입구. Button Interface를 상속하며, 내부 컴포넌트 내부 클래스들을 사용해 BI에서 정의된 인터페이스 함수들을 구현한다.
 * @remarks	SingleTon을 사용한다.
 */
class CCommunicationFacade : public CCommunicationBI
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
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
	/**@brief	생성자	*/
	CCommunicationFacade(){}
	/**@brief	소멸자	*/
	~CCommunicationFacade(){}
private :
	/**@brief	singleton.	*/
	static CCommunicationFacade *m_instance;
};

#endif