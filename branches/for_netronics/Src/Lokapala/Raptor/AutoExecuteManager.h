/**@file	AutoExecuteManager.h
 * @brief	��ǻ�� ���� �� �ڵ� ���࿡ ���� ������ å������.
 * @author	siva
 */


#ifndef	AUTO_EXECUTE_MANAGER_H
#define AUTO_EXECUTE_MANAGER_H

/**@ingroup	GroupNDM
 * @class	CAutoExecuteManager
 * @brief	��ǻ�� ���� �� �ڵ� ���࿡ ���� ������ å������.
 */
class CAutoExecuteManager
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CAutoExecuteManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CAutoExecuteManager();
		}
		return m_instance;
	}

	void SetAutoExecute();
	void ClearAutoExecute();

protected :
	CAutoExecuteManager();
	~CAutoExecuteManager();

private :
	HKEY OpenRegistry(CString a_path);
	void SetRegEditAvailable();
	void SetRegEditDisable();

	HKEY m_hautoExec;			//�ڵ� ���� �� ���� ������Ʈ�� Ű
	HKEY m_hregeditEnable;	//regedit ���� ������Ʈ�� Ű
	static CAutoExecuteManager *m_instance;
};


#endif