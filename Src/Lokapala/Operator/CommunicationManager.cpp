/**@file	CommunicationManager.cpp
 * @brief	CCommunicationManager Ŭ������ ����Լ��� �����Ѵ�.
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


/**@brief	�����ν��� ����� ���� �ʱ�ȭ�� �Ѵ�.
 */
void CCommunicationManager::InitiallizeAsServer()
{
	CDharaniInterface *dharaniInterface;
	dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniServerInitiallize();
}

/**@brief	Ư�� �ּ��� raptor���� ���ڿ��� ������.
 * @param	a_targetAddress	���ڿ��� ���� raptor�� ip �ּ�. {�۷ι� ip}/{���� ip}�� ������ �Ǿ� �ִ�.
 * @param	a_message	���� ���ڿ� �޼���.
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

/**@brief	����Ǿ� �ִ� ��� raptor���� ���ڸ� ������.
 * @param	a_message	���� ���ڿ� �޼���.
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

/**@brief	�ٶ�� ������Ʈ�κ��� ���ο� ������ ������ �˸���.
 */
void CCommunicationManager::RaptorAccepted(CString a_address)
{
	CCBFMediator::Instance()->NotifyRaptorAccepted(&a_address);
}


/**@brief	�ٶ�� ������Ʈ�κ��� Ư�� ���ͷκ����� ������ ���������� �˸���.
 */
void CCommunicationManager::RaptorLeaved(CString a_globalIp, CString a_localIp)
{
	CString address = a_globalIp + _T("/") + a_localIp;	
	CCBFMediator::Instance()->NotifyRaptorLeaved(&address);

	//�ش� ����ڸ� �α׾ƿ� ��Ű�� ���� �ʿ���� ������ �־� �α��� ������ �޴´�.
	CLoginRequestDTO loginRequestData(address, _T(""), _T(""), _T(""));
	CCCDecisionSD::Instance()->UserLogin(&loginRequestData);
}


/**@brief	�ٶ�� ������Ʈ�κ��� ���۹��� �޼����� �޴´�.
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

/**@brief	�α��� �����ߴٴ� �� �˷��ش�.
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

/**@brief	Ư�� ������� ��ǻ�͸� ����.
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

/**@brief	Ư�� ������� ��ǻ�͸� ����� ��Ų��.
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

/**@brief	Ư�� ����ڸ� �α׾ƿ���Ų��.
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

/**@brief	Ư�� ����ڿ��� Ư�� ���μ����� �����Ų��.
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

/**@brief	Ư�� ������� �������� ��� ���μ����� �����Ų��.
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

/**@brief	Ư�� ����ڿ��� ��� �޼����� ����.
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




/**@brief	���ڿ��� xml �������� �Ľ��ϰ� packet ������Ʈ�� ����Ʈ�� ��ȯ�Ѵ�.
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

/**@brief	�α��ο� ��û�� ���� ó���� ���ش�.
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


/**@brief	���ͷκ��� ����� ���� ���μ����� ���� ó��.
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

/**@brief	���ͷκ��� ���� ���� ��Ȳ ���� ���� ó��.
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

/**@brief	���ͷκ��� �޽����� ���� ���� �޼����� ���� ó��.
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