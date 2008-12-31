#include "stdafx.h"
#include "DataAdminManager.h"

#include "tinyxml.h"

/**@brief	����� ������ �����Ѵ�. �α��� ��û �� �� �ҷ�����.
 */
void CDataAdminManager::RegistUser(void *a_user)
{
	CUserDTO *user = (CUserDTO *)a_user;
	m_user = *user;
}

/**@brief	����� ������ �����Ѵ�. �α��� ��û ��� �Ǿ��� �� �ҷ�����.
 */
void CDataAdminManager::RegistUserLevel(int a_level)
{
	m_user.m_level = a_level;
}


/**@brief	���� ��Ȳ ��ȭ ���� ����ü�� �����´�.
 * @return	��Ȳ ��ȭ ���� ����ü�� ������.
 */
void *CDataAdminManager::GetStatusReports()
{
	return &m_statusReports;
}

/**@brief	���� ��Ȳ ��ȭ ���� ������ ���Ϸ� �����Ѵ�.
 */
void CDataAdminManager::SaveStatusReportsToFile(CString a_filePath)
{
	USES_CONVERSION;

	TiXmlDocument doc;
	TiXmlDeclaration *decl = new TiXmlDeclaration( "1.0", "euc-kr", "" );
	doc.LinkEndChild( decl );

	TiXmlElement *root = new TiXmlElement( "StatusReports" );
	doc.LinkEndChild( root );

	CStatusReportDTOArray statusReports;
	m_statusReports.GetReportFrom(_T(""), &statusReports);
	for(int i=0; i<statusReports.GetCount(); i++)
	{
		TiXmlElement *statusReport = new TiXmlElement( "StatusReport" );
		root->LinkEndChild(statusReport);
		statusReport->SetAttribute( "hostAddress", W2A(statusReports[i].m_hostAddress) );
		statusReport->SetAttribute( "date", W2A(statusReports[i].m_date) );
		statusReport->SetAttribute( "state", statusReports[i].m_state );
		statusReport->SetAttribute( "comment", W2A(statusReports[i].m_comment) );
	}	

	doc.SaveFile(W2A(a_filePath));
}

/**@brief	���Ϸκ��� ��Ȳ ��ȭ ���� ������ �о���δ�.
 */
void CDataAdminManager::LoadStatusReportsFromFile(CString a_filePath)
{
	USES_CONVERSION;
	TiXmlDocument document(W2A(a_filePath));
	document.LoadFile();
	TiXmlElement *statusReports = document.FirstChildElement("StatusReports");
	if(statusReports==NULL)
	{
		AfxMessageBox(_T("invalid xml file!"));
		return;
	}

	TiXmlElement *statusReport = statusReports->FirstChildElement("StatusReport");
	for(statusReport; statusReport; statusReport = statusReport->NextSiblingElement())
	{
		CString hostAddress = A2W(statusReport->Attribute("hostAddress"));
		int state;
		statusReport->Attribute("state", &state);		
		CString date = A2W(statusReport->Attribute("date"));
		CString comment = A2W(statusReport->Attribute("comment"));

		CStatusReportDTO newStateReport(hostAddress, (State)state, date, comment);
		m_statusReports.AddReport(&newStateReport);
	}
}