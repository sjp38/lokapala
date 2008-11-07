/**@file	CommunicationManager.cpp
 * @brief	CCommunicationManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "CommunicationManager.h"

#include "tinyxml.h"

#include "DharaniInterface.h"
#include "DharaniFacade.h"
#include "LokapalaProtocol.h"

#include "UserDTO.h"
#include "StatusReportDTO.h"

#include "CCDecisionSD.h"

/**@brief	소켓을 생성한 후, 오퍼레이터에게 connect 한다.
 */
void CCommunicationManager::Initiallize(DWORD a_ServerAddress)
{
	if(m_connected == TRUE)
	{
		return;
	}
	CDharaniInterface *dharaniInterface = CDharaniFacade::Instance();	
	
	if( 0 == dharaniInterface->DharaniClientInitiallize(a_ServerAddress) )
	{
		m_connected =TRUE;
		CFile file;
		file.Open(_T("operatorAddress.cfg"), CFile::modeCreate | CFile::modeWrite);
		file.Write(&a_ServerAddress, sizeof(a_ServerAddress));
		file.Close();

		m_operatorAddress = a_ServerAddress;
	}
}

/**@brief	오퍼레이터와의 연결을 끊는다.
 */
void CCommunicationManager::CloseConnection()
{
	if(m_connected == FALSE)
	{
		return;
	}
	CDharaniInterface *dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniCloseServerConnection();

	m_connected = FALSE;
}


/**@brief	텍스트 메세지를 오퍼레이터에게 보낸다.
 */
void CCommunicationManager::SendTextMessage(CString a_message)
{
	USES_CONVERSION;
	CDharaniDTO message;
	message.m_message = W2A(a_message);

	CDharaniInterface *dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniSendTextToServer(&message);
}


/**@brief	다라니 컴포넌트로부터 데이터를 전송받았음을 듣는다.
 *			전송받은 메세지를 분석, 행위에 맞는 서비스를 DCM 또는 MSM에게 요청한다.
 */
void CCommunicationManager::NotifyReceived(CString a_message)
{
	USES_CONVERSION;
	TiXmlDocument doc;
	doc.Parse(W2A(a_message));
	TiXmlElement *proot = doc.FirstChildElement("Packet");
	if(NULL == proot)
	{
		return;
	}
	const char *header = proot->Attribute("Header");
	CString argument = A2W(proot->Attribute("argument"));
	
	switch( atoi(header) )
	{
	case LOGIN_ACCEPT :
		LoginAccepted(&a_message);
		break;
	case LOGIN :
		
		CCCDecisionSD::Instance()->Login( &argument );
		break;
	case LOGOUT :
		CCCDecisionSD::Instance()->Logout( &argument );
		break;
	case SHUTDOWN :
		CCCDecisionSD::Instance()->Shutdown( &argument );
		break;
	case REBOOT :
		CCCDecisionSD::Instance()->Reboot( &argument );
		break;
	case GENOCIDE :
		CCCDecisionSD::Instance()->GenocideProcesses( &argument );
		break;
	case KILL :
		CCCDecisionSD::Instance()->KillProcess( &argument );
		break;
	case EXECUTE :
		CCCDecisionSD::Instance()->ExecuteProcess( &argument );
		break;
	case MESSAGE :
		//CCCMessengerSD::Instnace()->ReceiveTextMessageFrom( A2W(proot->Attribute("message")) );
		break;
	case STATUS_CHANGE :
		//CCCDecisionSD::Instance()->StatusReport( A2W(proot->Attribute("message")) );	//아규먼트 등의 구현이 애매하므로 이건 나중에 구현.
		break;
	default :
		break;
	}
}




/**@brief	오퍼레이터에게 로그인 요청을 보낸다.
 * @param	a_userInfo	CUserDTO 포인터로 이름, 비밀번호 등의 정보를 갖는다. void 포인터로 캐스팅 되어 전달된다.
 */
void CCommunicationManager::SendLoginRequest(void *a_userInfo)
{
	CUserDTO *userInfo = (CUserDTO *)a_userInfo;
	USES_CONVERSION;
	TiXmlDocument doc;

	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", LOGIN_REQUEST);
	root->SetAttribute("name", W2A(userInfo->m_name));
	root->SetAttribute("lowPassword", W2A(userInfo->m_lowLevelPassword));
	root->SetAttribute("highPassword", W2A(userInfo->m_highLevelPassword+_T("temp")));	//해싱된 값의 불균형성으로 토크나이징이 안되는 점을 감안해 마지막에  temp라는 문자열을 넣는다.

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet =	printer.CStr();

	SendTextMessage(A2W(packet));
}


/**@brief	오퍼레이터로부터 로그인 허용 메세지를 받았을 때.
 *			DCM으로의 SD를 통해 DCM에서 로그인 관련 서비스를 해주실 요청한다.
 */
void CCommunicationManager::LoginAccepted(CString *a_message)
{
	USES_CONVERSION;
	TiXmlDocument doc;
	doc.Parse(W2A(*a_message));
	TiXmlElement *proot = doc.FirstChildElement("Packet");
	if(NULL == proot)
	{
		return;
	}
	int level;
	proot->Attribute("level", &level);
	
	CCCDecisionSD::Instance()->LoginAccepted(level);
}


/**@brief	실행된 프로세스 이름을 오퍼레이터에게 알린다.
 */
void CCommunicationManager::SendExecutedProcessReport(CString *a_executedProcess)
{
	USES_CONVERSION;
	TiXmlDocument doc;

	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", PROCESS_EXECUTED);
	root->SetAttribute("executedProcessName", W2A(*a_executedProcess));

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet =	printer.CStr();

	SendTextMessage(A2W(packet));
}


/**@brief	메신저의 요청에 따라 텍스트 메세지를 오퍼레이터에게 전송한다.
 *			내부적으로 SendTextMessage 메서드를 사용하는데, 서로 다른 용도임을 주의할 것.
 */
void CCommunicationManager::SendTextMessageToOperator(CString *a_message)
{
	USES_CONVERSION;
	TiXmlDocument doc;

	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", MESSAGE);
	root->SetAttribute("message", W2A(*a_message));

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet =	printer.CStr();

	SendTextMessage(A2W(packet));
}


/**@brief	상황 보고를 오퍼레이터에게 전송한다.
 */
void CCommunicationManager::SendStatusReport(void *a_statusReport)
{
	CStatusReportDTO *statusReport = (CStatusReportDTO *)a_statusReport;

	USES_CONVERSION;
	TiXmlDocument doc;

	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", STATUS_CHANGED);
	root->SetAttribute("state", statusReport->m_state);
	root->SetAttribute("date", W2A(statusReport->m_date));
	root->SetAttribute("comment", W2A(statusReport->m_comment));

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet =	printer.CStr();

	SendTextMessage(A2W(packet));
}