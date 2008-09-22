/** @file	CBFMediator.h
 *	@brief	Common Business Framework Mediator�� �����Ѵ�.
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
 * @brief	Mediator.\n ��� ������Ʈ�� ���� �� �޵����Ϳ� ����Ѵ�.
 * @remarks	�� ������Ʈ�� Button Interface�� ���� ������Ʈ���� ����� ������, Service Delegate�� ����� �޴´�.\n
 *			singleton�� ����Ѵ�.
 */
class CCBFMediator
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	CCBFMediator ������ Ÿ���� singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
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

	//OSM
	void StartProcessObservation();
	void StopProcessObservation();

protected :
	/**@breif	������	*/
	CCBFMediator(){}
	/**@breif	�Ҹ���	*/
	~CCBFMediator(){}
private :
	/**@brief	singleton. ������ �� �ϳ��� �����Ѵ�.	*/
	static CCBFMediator *m_instance;
	CDialog *m_mainDlg;
};

#endif