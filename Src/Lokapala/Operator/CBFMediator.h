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
 * @remarks	�� ������Ʈ�� Button Interface�� ���� ������Ʈ���� ������ ������, Service Delegate�� ������ �޴´�.\n
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
	void JudgeLoginRequest(void *a_loginRequestData);
	void JudgeUserExecutedProcess(void *a_executedProcessData);
	void PresentStatusReport(void *a_statusReportData);

	//CCM
	void BeginCommunication();
	void BroadcastTextMessage(CString a_message);
	void SendTextMessageTo(CString a_targetAddress, CString a_message);
	void NotifyAccepted(void *a_acceptedData);
	void ShutdownUser(void *a_argument);
	void RebootUser(void *a_argument);
	void LogoutUser(void *a_argument);
	void ExecuteUser(void *a_argument);
	void GenocideUser(void *a_argument);
	void WarnUser(void *a_argument);


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

	void *GetConnectedUsers();


	//MSM
	void PresentMessage(void *a_messageData);


	//common
	void SetMainDlg(CDialog *a_pDlg);	
	void Notify(CString *a_notifyMessage);
	void NotifyRaptorLogin(CString *a_address);
	void NotifyRaptorLogout(CString *a_address);

	void NotifyRaptorAccepted(CString *a_address);
	void NotifyRaptorLeaved(CString *a_address);

	void InitStatusViewAs(int a_column, int a_row);
	

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