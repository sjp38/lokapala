/** @file	CBFMediator.h
 *	@brief	Common Business Framework Mediator를 정의한다.
 *	@author	siva
 */



#ifndef CBF_MEDIATOR_H
#define CBF_MEDIATOR_H

#include "DataAdminBI.h"
#include "DataAdminFacade.h"
#include "DecisionBI.h"
#include "DecisionFacade.h"
#include "LogBI.h"
#include "LogFacade.h"
#include "CommunicationBI.h"
#include "CommunicationFacade.h"
#include "MessengerBI.h"
#include "MessengerFacade.h"
#include "NeverDieBI.h"
#include "NeverDieFacade.h"
#include "ObserveBI.h"
#include "ObserveFacade.h"
#include "ControlBI.h"
#include "ControlFacade.h"

/**@ingroup GroupMediator
 * @class	CCBFMediator
 * @brief	Mediator.\n 모든 컴포넌트는 오직 이 메디에이터와 통신한다.
 * @remarks	각 컴포넌트의 Button Interface를 통해 컴포넌트에게 명령을 내리고, Service Delegate로 명령을 받는다.\n
 *			singleton을 사용한다.
 */
class CCBFMediator
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	CCBFMediator 포인터 타입의 singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CCBFMediator *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CCBFMediator();
		}
		return m_instance;
	}
	CDialog *GetMainDlg();
	void SetMainDlg(CDialog *a_pDlg);

	//DCM
	void ReadDAM();

	//CCM
	void InitiallizeCommunication(DWORD a_ServerAddress);
	void SendTextMessage(CString a_message);

	//NDM
	void StartNeverDie();
	void StopNeverDie();
	bool GetNeverDieState();

protected :
	/**@breif	생성자	*/
	CCBFMediator(){}
	/**@breif	소멸자	*/
	~CCBFMediator(){}
private :
	/**@brief	singleton. 언제나 단 하나만 존재한다.	*/
	static CCBFMediator *m_instance;
	CDialog *m_mainDlg;
};

#endif