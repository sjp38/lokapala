/**@file	CommunicationManager.cpp
 * @brief	CCommunicationManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */


#include "stdafx.h"
#include "CommunicationManager.h"

#include "tinyxml.h"

#include "LokapalaProtocol.h"
#include "CCDecisionSD.h"
#include "LoginRequestDTO.h"


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
	const char *header = proot->Attribute("Header");
	
	switch(atoi( header ))
	{
	case LOGIN_REQUEST :
		LoginProcess(&a_message, &a_localIp, &a_globalIp);
		break;
	case PROCESS_EXECUTED :
		break;
	case MESSAGE :
		break;
	case STATUS_CHANGED :
		break;
	default :
		break;
	}

}


/**@brief	로그인 성공했다는 걸 알려준다.
 */
void CCommunicationManager::NotifyAccepted(void *a_acceptedData)
{
	CLoginRequestDTO *acceptedData = (CLoginRequestDTO *)a_acceptedData;
	CString destinationGlobalIp = acceptedData->m_globalIp;
	CString destinationLocalIp = acceptedData->m_localIp;
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
	SendTextMessageTo(destinationGlobalIp + _T("/") + destinationLocalIp, A2W(packet));
}

/**@brief	로그인에 요청에 대한 처리를 해준다.
 */
void CCommunicationManager::LoginProcess(CString *a_message, CString *a_localIp, CString *a_globalIp)
{
	CLoginRequestDTO loginRequestData;

	USES_CONVERSION;
	TiXmlDocument doc;
	doc.Parse(W2A(*a_message));
	TiXmlElement *proot = doc.FirstChildElement("Packet");
	if(NULL == proot)
	{
		return;
	}
	const char *name = proot->Attribute("name");
	const char *lowPassword = proot->Attribute("lowPassword");
	const char *highPassword = proot->Attribute("highPassword");
	
	loginRequestData.m_name = A2W(name);
	loginRequestData.m_lowLevelPassword = A2W(lowPassword);
	loginRequestData.m_highLevelPassword = A2W(highPassword);
	loginRequestData.m_highLevelPassword.TrimRight(_T("temp"));
	loginRequestData.m_level = -1;
	loginRequestData.m_globalIp = *a_globalIp;
	loginRequestData.m_localIp = *a_localIp;

	CCCDecisionSD::Instance()->UserLogin(&loginRequestData);
	//	NotifyAccepted(level, a_localIp, a_globalIp);
	
}