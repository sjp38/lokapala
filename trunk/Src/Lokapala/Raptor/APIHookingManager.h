/**@file	APIHookingManager.h
 * @brief	API 후킹에 관한 사항을 책임진다.
 * @author	siva
 */


#ifndef	API_HOOKING_MANAGER_H
#define API_HOOKING_MANAGER_H

/**@ingroup	GroupNDM
 * @class	CAPIHookingManager
 * @brief	global API 후킹을 통해 TerminateProcess를 통제한다.
 */
class CAPIHookingManager
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CAPIHookingManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CAPIHookingManager();
		}
		return m_instance;
	}

	void StartAPIHooking();
	void StopAPIHooking();

protected :
	CAPIHookingManager(){}
	~CAPIHookingManager(){}

private :
	void WriteSelfPathToMemory();

	HANDLE m_map;
	static CAPIHookingManager *m_instance;
};


#endif
