/**@file	DecisionManager.cpp
 * @brief	CDecisionManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "DecisionManager.h"

#include "DCCommunicationSD.h"
#include "DCDataAdminSD.h"
#include "DCControlSD.h"

/**@brief	���۷����Ϳ��� �α��� ��û�� �Ѵ�.	*/
void CDecisionManager::LoginRequest(void *a_userInfo)
{
	CDCDataAdminSD::Instance()->RegistUser(a_userInfo);
	CDCCommunicationSD::Instance()->LoginRequest(a_userInfo);
}

/**@brief	�α��� ��� �޼����� �޾��� ��.
 *			����� ���� ������ �ߴ��ϰ�, ����� ���� ���� ���� ����Ѵ�.
 */
void CDecisionManager::LoginAccepted(int a_level)
{
	CDCDataAdminSD::Instance()->RegistUserLevel(a_level);
	CDCControlSD::Instance()->ReleaseUser();
	//AfxMessageBox(_T("login!!!"));
}

/**@brief	���۷����ͷκ����� ���� �α��� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionManager::LoginOrderReceived(void *a_message)
{
	CDCControlSD::Instance()->Login(a_message);
}

/**@brief	���۷����ͷκ����� ���� �α׾ƿ� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionManager::LogoutOrderReceived(void *a_message)
{
	CDCControlSD::Instance()->Logout(a_message);
}

/**@brief	���۷����ͷκ����� ���� ��ǻ�� ���� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionManager::ShutdownOrderReceived(void *a_message)
{
	CDCControlSD::Instance()->Shutdown(a_message);
}

/**@brief	���۷����ͷκ����� ���� ��ǻ�� ������ ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionManager::RebootOrderReceived(void *a_message)
{
	CDCControlSD::Instance()->Reboot(a_message);
}

/**@brief	���۷����ͷκ����� �������� ��� ���μ��� ���� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionManager::GenocideProcessesOrderReceived(void *a_message)
{
	CDCControlSD::Instance()->GenocideProcesses(a_message);
}

/**@brief	���۷����ͷκ����� Ư�� ���μ��� ���� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionManager::KillProcessOrderReceived(void *a_processName)
{
	CDCControlSD::Instance()->KillProcess(a_processName);
}

/**@brief	���۷����ͷκ����� Ư�� ���μ��� ���� ��ɿ� ���� ó���� �Ѵ�.
 */
void CDecisionManager::ExecuteProcessOrderReceived(void *a_processName)
{
	CDCControlSD::Instance()->ExecuteProcess(a_processName);
}




/**@brief	����� ���μ��� �̸��� ���� �޴´�.
 *			CCM�� �̿��� ���۷����Ϳ��� �����Ѵ�.
 */
void CDecisionManager::ReportExecutedProcess(CString *a_executedProcess)
{
	CDCCommunicationSD::Instance()->ReportExecutedProcess(a_executedProcess);
}

void CDecisionManager::ReportStatus(void *a_status)
{
	CDCCommunicationSD::Instance()->ReportStatus(a_status);
}