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
	void SendTextMessageTo(CString a_targetAddress, CString a_message);		//단순 텍스트 전송.(로카파라의 xml 포맷 패킷 형식을 갖지 않는다.)
	void SendLoginAcceptedNotifyMessage(void *a_acceptedData);	//로그인 허용
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