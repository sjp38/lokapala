/**@file	DataAdminBI.h
 * @brief	DAM�� Button Interface ����
 * @author	siva
 */

#ifndef DATA_ADMIN_BI_H
#define DATA_ADMIN_BI_H

/**@ingroup GroupDAM
 * @class	CDataAdminBI
 * @brief	Communication Manager�� Button Interface.\n
			Mediator���� �ڽ��� �����Ͽ� Mediator�κ��� CCM������ �������̽��� �����Ѵ�.
 * @remarks	�������̽��� ������, Facade�� ����Ѵ�.
 */
class CDataAdminBI
{
public :
	virtual void RegistUser(void *a_userInfo) = 0;
	virtual void RegistUserLevel(int a_level) = 0;
	virtual void *GetStatusReports() = 0;
};

#endif