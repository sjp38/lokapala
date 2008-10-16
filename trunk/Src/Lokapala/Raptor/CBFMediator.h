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
	void *GetStatusReports();

	//DCM
	void LoginRequest(void *a_userInfo);
	void LoginAccepted(int a_level);
	void LoginOrderReceived(void *a_userInfo);
	void LogoutOrderReceived(void *a_message);	
	void ShutdownOrderReceived(void *a_message);
	void RebootOrderReceived(void *a_message);
	void GenocideProcessesOrderReceived(void *a_message);
	void KillProcessOrderReceived(void *a_processName);
	void ExecuteProcessOrderReceived(void *a_processName);

	void ReportExecutedProcess(CString *a_executedProcess);	
	void ReportStatus(void *a_status);

	//CCM
	void InitiallizeCommunication(DWORD a_ServerAddress);
	void CloseConnection();
	void SendTextMessageToOperator(CString *a_message);	//MSM�� ���� �ҷ�����.
	void SendLoginRequest(void *a_userInfo);
	void SendExecutedProcessReport(CString *a_executedProcess);
	void SendStatusReport(void *a_statusReport);

	//MSM
	void PostTextMessageToOperator(CString *a_message);			//��·�ų� send��� ����� CCM�� �� �� �ִ�.
	void ReceiveTextMessageFromOperator(CString *a_message);

	//NDM
	void StartNeverDie();
	void StopNeverDie();
	bool GetNeverDieState();

	//OSM
	void StartProcessObservation();
	void StopProcessObservation();
	void ReceiveExecutedProcess(CString a_executedProcess);
	//void NotifyExecutedProcess(CString a_executedProcess);

	//CTM
	void RestraintUser();
	void ReleaseUser();	
	void Login(void *a_userInfo);
	void Logout(void *a_message);	
	void Shutdown(void *a_message);
	void Reboot(void *a_message);
	void GenocideProcesses(void *a_message);
	void KillProcess(void *a_processName);
	void ExecuteProcess(void *a_processName);	

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