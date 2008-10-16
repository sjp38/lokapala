/**@file	ControlBI.h
 * @brief	CTM�� Button Interface ����
 * @author	siva
 */

#ifndef CONTROL_BI_H
#define CONTROL_BI_H

/**@ingroup GroupCTM
 * @class	CControlBI
 * @brief	Control Manager�� Button Interface.\n
			Mediator���� �ڽ��� �����Ͽ� Mediator�κ��� CCM������ �������̽��� �����Ѵ�.
 * @remarks	�������̽��� ������, Facade�� ����Ѵ�.
 */
class CControlBI
{
public :
	/**@brief	������� �������� ��ǻ�� ����� �����Ѵ�.	*/
	virtual void RestraintUser() = 0;

	/**@brief	������� �������� ��ǻ�� ����� ����Ѵ�.	*/
	virtual void ReleaseUser() = 0;

	/**@brief	������ ������� �α����� ���ش�.	*/
	virtual void Login(void *a_userInfo) = 0;

	/**@brief	������ ����ڸ� �α׾ƿ� ��Ų��.	*/
	virtual void Logout(void *a_message) = 0;

	/**@brief	��ǻ�͸� ��������.	*/
	virtual void Shutdown(void *a_message) = 0;

	/**@brief	��ǻ�͸� ����� ��Ų��.	*/
	virtual void Reboot(void *a_message) = 0;

	/**@brief	���� ���� ���μ����� ������ �׿�������.	*/
	virtual void GenocideProcesses(void *a_message) = 0;

	/**@brief	Ư�� �̸��� ���μ����� ���δ�.	*/
	virtual void KillProcess(void *a_processName) = 0;

	/**@brief	Ư�� �̸��� ���μ����� �����Ų��.	*/
	virtual void ExecuteProcess(void *a_processName) = 0;
};

#endif