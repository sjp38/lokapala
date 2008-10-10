/**@file	ControlFacade.h
 * @brief	Control Manager의 Facade 정의.
 * author	siva
 */

#ifndef CONTROL_FACADE_H
#define CONTROL_FACADE_H

#include "ControlBI.h"

/**@ingroup GroupCTM
 * @class	CControlFacade
 * @brief	CTM의 Facade.
 * @remarks	SingleTon을 사용한다.
 */
class CControlFacade : public CControlBI
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
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
	/**@brief	생성자	*/
	CControlFacade(){}
	/**@brief	소멸자	*/
	~CControlFacade(){}
private :
	/**@brief	singleton	*/
	static CControlFacade *m_instance;
};

#endif