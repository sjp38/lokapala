/**@file	ControlFacade.h
 * @brief	Control Manager�� Facade ����.
 * author	siva
 */

#ifndef CONTROL_FACADE_H
#define CONTROL_FACADE_H

#include "ControlBI.h"

/**@ingroup GroupCTM
 * @class	CControlFacade
 * @brief	CTM�� Facade.
 * @remarks	SingleTon�� ����Ѵ�.
 */
class CControlFacade : public CControlBI
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CControlFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CControlFacade();
		}
		return m_instance;
	}

	virtual void RestraintUser();
	virtual void ReleaseUser();
	
	virtual void Login(void *a_userInfo);
	virtual void Logout();
	
	virtual void Shutdown();
	virtual void Reboot();

	virtual void GenocideProcesses();
	virtual void KillProcess(CString *a_processName);

	virtual void ExecuteProcess(CString *a_processName);

protected :
	/**@brief	������	*/
	CControlFacade(){}
	/**@brief	�Ҹ���	*/
	~CControlFacade(){}
private :
	/**@brief	singleton	*/
	static CControlFacade *m_instance;
};

#endif