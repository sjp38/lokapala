/**@file	CommunicationManager.cpp
 * @brief	CCommunicationManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */


#include "stdafx.h"
#include "CommunicationManager.h"

#include "LokapalaProtocol.h"
#include "CCDecisionSD.h"
#include "LoginRequestDTO.h"
#include "ExecutedProcessDTO.h"
#include "StatusReportDTO.h"

#include "CCMessengerSD.h"
#include "MessageDTO.h"
#include "ReactionArgumentDTO.h"


/**@brief	서버로써의 통신을 위한 초기화를 한다.
 */
void CCommunicationManager::InitiallizeAsServer()
{
	CDharaniInterface *dharaniInterface;
	dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniServerInitiallize();
}

/**@brief	특정 주소의 raptor에게 문자열을 보낸다.
 * @param	a_targetAddress	문자열을 받을 raptor의 ip 주소. {글로벌 ip}/{로컬 ip}의 구조로 되어 있다.
 * @param	a_message	보낼 문자열 메세지.
 */
void CCommunicationManager::SendTextMessageTo(CString a_targetAddress, CString a_message)
{
	USES_CONVERSION;
	CDharaniDTO message;
	int tokenIndex = 0;
	message.m_globalIp = inet_addr( W2A(a_targetAddress.Tokenize(_T("/"), tokenIndex)) );
	message.m_localIp = inet_addr( W2A(a_targetAddress.Tokenize(_T("/"), tokenIndex)) );
	message.m_message = W2A(a_message);

	CDharaniInterface *dharaniInterface;
	dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniSendTextMessageTo(&message);
}

/**@brief	연결되어 있는 모든 raptor에게 문자를 보낸다.
 * @param	a_message	보낼 문자열 메세지.
 */
void CCommunicationManager::BroadcastTextMessage(CString a_message)
{
	USES_CONVERSION;
	CDharaniDTO message;
	message.m_message = W2A(a_message);
	message.m_globalIp = 0;
	message.m_localIp = 0;

	CDharaniInterface *dharaniInterface;
	dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniBroadcastTextMessage(&message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Dharani -> CCM

/**@brief	다라니 컴포넌트로부터 새로운 랩터의 연결을 알린다.
 */
void CCommunicationManager::RaptorAccepted(CString a_address)
{
	CCBFMediator::Instance()->NotifyRaptorAccepted(&a_address);
}


/**@brief	다라니 컴포넌트로부터 특정 랩터로부터의 연결이 끊어졌음을 알린다.
 */
void CCommunicationManager::RaptorLeaved(CString a_globalIp, CString a_localIp)
{
	CString address = a_globalIp + _T("/") + a_localIp;	
	CCBFMediator::Instance()->NotifyRaptorLeaved(&address);

	//해당 사용자를 로그아웃 시키기 위해 필요없는 정보를 넣어 로그인 판정을 받는다.
	CLoginRequestDTO loginRequestData(address, _T(""), _T(""), _T(""));
	CCCDecisionSD::Instance()->UserLogin(&loginRequestData);
}


/**@brief	다라니 컴포넌트로부터 전송받은 메세지를 받는다.
 */
void CCommunicationManager::NotifyReceived(CString a_message, CString a_localIp, CString a_globalIp)
{
	USES_CONVERSION;
	TiXmlDocument doc;
	doc.Parse(W2A(a_message));
	TiXmlElement *proot = doc.FirstChildElement("Packet");
	if(NULL == proot)
	{
		return;
	}
	CString address = a_globalIp + _T("/") + a_localIp;
	const char *header = proot->Attribute("Header");
	
	switch(atoi( header ))
	{
	case LOGIN_REQUEST :
		LoginRequestReceived(&a_message, &address);
		break;
	case PROCESS_EXECUTED :
		UserExecutedProcessReceived(&a_message, &address);
		break;
	case MESSAGE :
		MessageReceived(&a_message, &address);
		break;
	case STATUS_CHANGED :
		StatusReportReceived(&a_message, &address);
		break;
	default :
		break;
	}

}

//////////////////////////////////////////////////////////////////////////////////////
//	Operator -> Raptpr

/**@brief	로그인 성공했다는 걸 알려준다.
 */
void CCommunicationManager::NotifyAccepted(void *a_acceptedData)
{
	CLoginRequestDTO *acceptedData = (CLoginRequestDTO *)a_acceptedData;
	CString destinationHostAddress = acceptedData->m_hostAddress;
	int level = acceptedData->m_level;

	TiXmlDocument doc;
	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", LOGIN_ACCEPT);
	root->SetAttribute("level", level);

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet = printer.CStr();

	USES_CONVERSION;
	SendTextMessageTo(destinationHostAddress, A2W(packet));
}

/**@brief	특정 사용자의 컴퓨터를 끈다.
 */
void CCommunicationManager::ShutdownUser(void *a_argument)
{
	CReactionArgumentDTO *argument = (CReactionArgumentDTO *)a_argument;
	CString targetHostAddress = argument->m_targetHostAddress;
		
	TiXmlDocument doc;
	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", SHUTDOWN);
	USES_CONVERSION;
	root->SetAttribute("message", W2A(argument->m_reactionArgument));

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet = printer.CStr();
	
	SendTextMessageTo(targetHostAddress, A2W(packet));
}

/**@brief	특정 사용자의 컴퓨터를 재부팅 시킨다.
 */
void CCommunicationManager::RebootUser(void *a_argument)
{
	CReactionArgumentDTO *argument = (CReactionArgumentDTO *)a_argument;
	CString targetHostAddress = argument->m_targetHostAddress;
		
	TiXmlDocument doc;
	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", REBOOT);
	USES_CONVERSION;
	root->SetAttribute("message", W2A(argument->m_reactionArgument));

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet = printer.CStr();
	
	SendTextMessageTo(targetHostAddress, A2W(packet));
}

/**@brief	특정 사용자를 로그아웃시킨다.
 */
void CCommunicationManager::LogoutUser(void *a_argument)
{
	CReactionArgumentDTO *argument = (CReactionArgumentDTO *)a_argument;
	CString targetHostAddress = argument->m_targetHostAddress;
		
	TiXmlDocument doc;
	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", LOGOUT);
	USES_CONVERSION;
	root->SetAttribute("message", W2A(argument->m_reactionArgument));

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet = printer.CStr();
	
	SendTextMessageTo(targetHostAddress, A2W(packet));
}

/**@brief	특정 사용자에게 특정 프로세스를 실행시킨다.
 */
void CCommunicationManager::ExecuteUser(void *a_argument)
{
	CReactionArgumentDTO *argument = (CReactionArgumentDTO *)a_argument;
	CString targetHostAddress = argument->m_targetHostAddress;
		
	TiXmlDocument doc;
	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", EXECUTE);
	USES_CONVERSION;
	root->SetAttribute("processName", W2A(argument->m_reactionArgument));

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet = printer.CStr();
	
	SendTextMessageTo(targetHostAddress, A2W(packet));
}

/**@brief	특정 사용자의 실행중인 모든 프로세스를 종료시킨다.
 */
void CCommunicationManager::GenocideUser(void *a_argument)
{
	CReactionArgumentDTO *argument = (CReactionArgumentDTO *)a_argument;
	CString targetHostAddress = argument->m_targetHostAddress;
		
	TiXmlDocument doc;
	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", GENOCIDE);
	USES_CONVERSION;
	root->SetAttribute("message", W2A(argument->m_reactionArgument));

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet = printer.CStr();
	
	SendTextMessageTo(targetHostAddress, A2W(packet));
}

/**@brief	특정 사용자에게 경고 메세지를 띄운다.
 */
void CCommunicationManager::WarnUser(void *a_argument)
{
	CReactionArgumentDTO *argument = (CReactionArgumentDTO *)a_argument;
	CString targetHostAddress = argument->m_targetHostAddress;
		
	TiXmlDocument doc;
	TiXmlElement *root = new TiXmlElement("Packet");
	doc.LinkEndChild(root);
	root->SetAttribute("Header", WARN);
	USES_CONVERSION;
	root->SetAttribute("message", W2A(argument->m_reactionArgument));

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet = printer.CStr();
	
	SendTextMessageTo(targetHostAddress, A2W(packet));
}




/**@brief	문자열을 xml 형식으로 파싱하고 packet 엘레먼트의 포인트를 반환한다.
 */
TiXmlElement *CCommunicationManager::GetXmlParsedPacketElement(CString *a_packet)
{
	USES_CONVERSION;
	TiXmlDocument doc;
	doc.Parse(W2A(*a_packet));
	TiXmlElement *proot = doc.FirstChildElement("Packet");
	
	return proot;
}




//////////////////////////////////////////////////////////////////////////////////////
//	Raptor -> Operator

/**@brief	로그인에 요청에 대한 처리를 해준다.
 */
void CCommunicationManager::LoginRequestReceived(CString *a_message, CString *a_hostAddress)
{	
	USES_CONVERSION;
	TiXmlDocument doc;
	doc.Parse(W2A(*a_message));
	TiXmlElement *proot = doc.FirstChildElement("Packet");
	if(proot == NULL)
	{
		return;
	}
	
	const char *name = proot->Attribute("name");
	const char *lowPassword = proot->Attribute("lowPassword");	
	CString highPassword =  A2W(proot->Attribute("highPassword"));
	highPassword.TrimRight(_T("temp"));
	
	CLoginRequestDTO loginRequestData(*a_hostAddress, A2W(name), A2W(lowPassword), highPassword);

	CCCDecisionSD::Instance()->UserLogin(&loginRequestData);	
}


/**@brief	랩터로부터 보고된 실행 프로세스에 대한 처리.
 */
void CCommunicationManager::UserExecutedProcessReceived(CString *a_message, CString *a_hostAddress)
{
	USES_CONVERSION;
	TiXmlDocument doc;
	doc.Parse(W2A(*a_message));
	TiXmlElement *proot = doc.FirstChildElement("Packet");
	if(proot == NULL)
	{
		return;
	}
	const char *processName = proot->Attribute("executedProcessName");

	CExecutedProcessDTO executedProcessData(A2W(processName), *a_hostAddress);

	CCCDecisionSD::Instance()->JudgeUserExecutedProcess(&executedProcessData);
}

/**@brief	랩터로부터 들어온 고장 상황 보고에 대한 처리.
 */
void CCommunicationManager::StatusReportReceived(CString *a_message, CString *a_hostAddress)
{
	USES_CONVERSION;
	TiXmlDocument doc;
	doc.Parse(W2A(*a_message));
	TiXmlElement *proot = doc.FirstChildElement("Packet");
	if(proot == NULL)
	{
		return;
	}
	int tempState;
	proot->Attribute("state", &tempState);
	enum State state = (enum State)tempState;
	const char *date = proot->Attribute("date");
	const char *comment = proot->Attribute("comment");

	CStatusReportDTO statusReportData(*a_hostAddress, state, A2W(date), A2W(comment));

	CCCDecisionSD::Instance()->PresentStatusReport(&statusReportData);
}

/**@brief	랩터로부터 메신저를 통해 들어온 메세지에 대한 처리.
 */
void CCommunicationManager::MessageReceived(CString *a_message, CString *a_hostAddress)
{
	USES_CONVERSION;
	TiXmlDocument doc;
	doc.Parse(W2A(*a_message));
	TiXmlElement *proot = doc.FirstChildElement("Packet");
	if(proot == NULL)
	{
		return;
	}
	const char *message = proot->Attribute("message");

	CMessageDTO messageData(*a_hostAddress, A2W(message));
	CCCMessengerSD::Instance()->PresentMessage(&messageData);	
}