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

	//DCM
	void HostConnected(void *a_hostData);
	void HostDisconnected(void *a_hostData);
	void JudgeLoginRequest(void *a_loginRequestData);
	void JudgeUserExecutedProcess(void *a_executedProcessData);
	void PresentStatusReport(void *a_statusReportData);
	void ShutdownHost(void *a_argument);
	void RebootHost(void *a_argument);
	void BanUser(void *a_argument);
	void ExecuteHostProcess(void *a_argument);
	void KillHostProcess(void *a_argument);
	void GenocideHostProcess(void *a_argument);
	void WarnHost(void *a_argument);
	void SubmitStatusReportToHost(void *a_statusReport);
	void TerminateRaptorOnHost(void *a_argument);

	//CCM
	void BeginCommunication();
	void BroadcastTextMessage(CString a_message);
	void SendTextMessageTo(CString a_targetAddress, CString a_message);		//�ܼ� �ؽ�Ʈ ����.(��ī�Ķ��� xml ���� ��Ŷ ������ ���� �ʴ´�.)
	void SendLoginAcceptedNotifyMessage(void *a_acceptedData);	//�α��� ���
	void SendShutdownInstruction(void *a_argument);
	void SendRebootInstruction(void *a_argument);
	void SendBanUserInstruction(void *a_argument);
	void SendExecuteProcessInstruction(void *a_argument);
	void SendKillProcessInstruction(void *a_argument);
	void SendGenocideProcessInstruction(void *a_argument);
	void SendWarningMessage(void *a_argument);
	void SendStatusReport(void *a_statusReport);
	void SendRaptorTerminationInstruction(void *a_argument);
	void SendTextMessageToRaptor(void *a_message);	


	//DAM
	void SaveDataAs(CString *a_filePath);
	void LoadDataFrom(CString *a_filePath);

	void AddUser(void *a_user);
	void DeleteUser(CString *a_id);
	void *GetUsers();

	void SetSeats(int a_x, int a_y);
	void AddSeat(void *a_seat);
	void DeleteSeat(void *a_seat);	
	void *GetSeats();

	void AddRule(void *a_rule);
	void DeleteRule(void *a_rule);
	void *GetRules();

	void *GetStatusReports();

	void *GetConnectedHosts();


	//MSM
	void PostTextMessgeTo(void *a_messageData);
	void PresentMessage(void *a_messageData);


	//common
	void SetMainDlg(CDialog *a_pDlg);	
	void Notify(CString *a_notifyMessage);
	void NotifyRaptorLogin(CString *a_hostAddress);
	void NotifyRaptorLogout(CString *a_hostAddress);
	void NotifyRaptorExecutedProcess(CString *a_hostAddress, CString *a_executedProcess);
	void NotifyRaptorStatusChange(void *a_statusReports);

	void NotifyRaptorAccepted(CString *a_hostAddress);
	void NotifyRaptorLeaved(CString *a_hostAddress);

	void NotifySeatResized(int a_maxX, int a_maxY);
	void NotifySeatAdded(CString *a_seatId);
	void NotifySeatDeleted(CString *a_seatId);

	void NotifyRaptorMessageReceived(CString a_hostAddress, CString a_message);
	void NotifyTextMessageToRaptorSended(CString a_hostAddress, CString a_message);

	

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