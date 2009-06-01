/**@file	DCCommunicationSD.cpp
 * @brief	DCM의 CommunicationSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DCCommunicationSD.h"


/**@brief	커뮤니케이션 컴포넌트에게 로그인 신호를 보내도록 한다.
 */
void CDCCommunicationSD::LoginRequest(void *a_userInfo)
{
	CCBFMediator::Instance()->SendLoginRequest(a_userInfo);
}

/**@brief	CCM에게 실행 프로세스 보고를 보내도록 한다.
 */
void CDCCommunicationSD::ReportExecutedProcess(CString *a_executedProcess)
{
	CCBFMediator::Instance()->SendExecutedProcessReport(a_executedProcess);
}

/**@brief	CCM에게 변경된 상황를 보고한다.
 */
void CDCCommunicationSD::ReportStatus(void *a_status)
{
	CCBFMediator::Instance()->SendStatusReport(a_status);
}
