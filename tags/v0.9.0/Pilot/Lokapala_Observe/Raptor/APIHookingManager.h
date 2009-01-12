/**@file	APIHookingManager.h
 * @brief	API ��ŷ�� ���� ������ å������.
 * @author	siva
 */


#ifndef	API_HOOKING_MANAGER_H
#define API_HOOKING_MANAGER_H

/**@ingroup	GroupNDM
 * @class	CAPIHookingManager
 * @brief	global API ��ŷ�� ���� TerminateProcess�� �����Ѵ�.
 */
class CAPIHookingManager
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
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