/**@file	CommunicationManager.cpp
 * @brief	CCommunicationManager Ŭ������ ����Լ��� �����Ѵ�.
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

/**@brief	������ ������ ��, ���۷����Ϳ��� connect �Ѵ�.
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

/**@brief	���۷����Ϳ��� ������ ���´�.
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


/**@brief	�ؽ�Ʈ �޼����� ���۷����Ϳ��� ������.
 */
void CCommunicationManager::SendTextMessage(CString a_message)
{
	USES_CONVERSION;
	CDharaniDTO message;
	message.m_message = W2A(a_message);

	CDharaniInterface *dharaniInterface = CDharaniFacade::Instance();
	dharaniInterface->DharaniSendTextToServer(&message);
}


/**@brief	�ٶ�� ������Ʈ�κ��� �����͸� ���۹޾����� ��´�.
 *			���۹��� �޼����� �м�, ������ �´� ���񽺸� DCM �Ǵ� MSM���� ��û�Ѵ�.
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
		//CCCDecisionSD::Instance()->StatusReport( A2W(proot->Attribute("message")) );	//�ƱԸ�Ʈ ���� ������ �ָ��ϹǷ� �̰� ���߿� ����.
		break;
	default :
		break;
	}
}




/**@brief	���۷����Ϳ��� �α��� ��û�� ������.
 * @param	a_userInfo	CUserDTO �����ͷ� �̸�, ��й�ȣ ���� ������ ���´�. void �����ͷ� ĳ���� �Ǿ� ���޵ȴ�.
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
	root->SetAttribute("highPassword", W2A(userInfo->m_highLevelPassword+_T("temp")));	//�ؽ̵� ���� �ұ��������� ��ũ����¡�� �ȵǴ� ���� ������ ��������  temp��� ���ڿ��� �ִ´�.

	TiXmlPrinter printer;
	printer.SetStreamPrinting();
	doc.Accept(&printer);
	const char *packet =	printer.CStr();

	SendTextMessage(A2W(packet));
}


/**@brief	���۷����ͷκ��� �α��� ��� �޼����� �޾��� ��.
 *			DCM������ SD�� ���� DCM���� �α��� ���� ���񽺸� ���ֽ� ��û�Ѵ�.
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


/**@brief	����� ���μ��� �̸��� ���۷����Ϳ��� �˸���.
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


/**@brief	�޽����� ��û�� ���� �ؽ�Ʈ �޼����� ���۷����Ϳ��� �����Ѵ�.
 *			���������� SendTextMessage �޼��带 ����ϴµ�, ���� �ٸ� �뵵���� ������ ��.
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


/**@brief	��Ȳ ���� ���۷����Ϳ��� �����Ѵ�.
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