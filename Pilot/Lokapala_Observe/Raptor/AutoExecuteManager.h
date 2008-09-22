/**@file	AutoExecuteManager.h
 * @brief	컴퓨터 부팅 시 자동 실행에 관한 사항을 책임진다.
 * @author	siva
 */


#ifndef	AUTO_EXECUTE_MANAGER_H
#define AUTO_EXECUTE_MANAGER_H

/**@ingroup	GroupNDM
 * @class	CAutoExecuteManager
 * @brief	컴퓨터 부팅 시 자동 실행에 관한 사항을 책임진다.
 */
class CAutoExecuteManager
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
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

	HKEY m_hautoExec;			//자동 실행 값 저장 레지스트리 키
	HKEY m_hregeditEnable;	//regedit 금지 레지스트리 키
	static CAutoExecuteManager *m_instance;
};


#endif