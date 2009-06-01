﻿/**@file	DataAdminBI.h
 * @brief	DAM의 Button Interface 정의
 * @author	siva
 */

#ifndef DATA_ADMIN_BI_H
#define DATA_ADMIN_BI_H

/**@ingroup GroupDAM
 * @class	CDataAdminBI
 * @brief	Communication Manager의 Button Interface.\n
			Mediator에게 자신을 노출하여 Mediator로부터 CCM으로의 인터페이스를 공개한다.
 * @remarks	인터페이스일 뿐으로, Facade가 상속한다.
 */
class CDataAdminBI
{
public :
	virtual void RegistUser(void *a_userInfo) = 0;
	virtual void RegistUserLevel(int a_level) = 0;
	virtual void *GetStatusReports() = 0;

	virtual void AddStatusReport(void *a_statusReport) = 0;
	virtual void SaveStatusReportsToFile(CString a_filePath) = 0;
	virtual void LoadStatusReportsFromFile(CString a_filePath) = 0;
};

#endif
