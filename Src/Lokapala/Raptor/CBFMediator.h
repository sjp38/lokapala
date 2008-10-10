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

	//DAM
	void RegistUser(void *a_userInfo);
	void RegistUserLevel(int a_level);
	void ReportStatus(void *a_status);

	//DCM
	void LoginRequest(void *a_userInfo);
	void LoginAccepted(int a_level);

	//CCM
	void InitiallizeCommunication(DWORD a_ServerAddress);
	void CloseConnection();
	void SendTextMessage(CString a_message);
	void SendLoginRequest(void *a_userInfo);

	//NDM
	void StartNeverDie();
	void StopNeverDie();
	bool GetNeverDieState();

	//OSM
	void StartProcessObservation();
	void StopProcessObservation();
	void ReceiveExecutedProcess(CString a_executedProcess);
	void NotifyExecutedProcess(CString a_executedProcess);

	//CTM
	void RestraintUser();
	void ReleaseUser();	
	void Login(void *a_userInfo);
	void Logout();	
	void Shutdown();
	void Reboot();
	void GenocideProcesses();
	void KillProcess(CString *a_processName);
	void ExecuteProcess(CString *a_processName);

	//common
	void Notify(CString *a_message);

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