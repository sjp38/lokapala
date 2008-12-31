/**@file	DCDataAdminSD.h
 * @brief	DCM에서 DAM으로의 Service Delegate 정의.
 * @author	siva
 */

#ifndef DCDATA_ADMIN_SD_H
#define DCDATA_ADMIN_SD_H

/**@ingroup GroupDCM
 * @class	CDCDataAdminSD
 * @brief	DCM에서 DAM으로의 Service Delegate. DCM에서 DAM으로 요구하는 바가 있을 때 사용된다.
 * @remarks	singleton을 사용한다.
 */
class CDCDataAdminSD
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CDCDataAdminSD *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDCDataAdminSD();
		}
		return m_instance;
	}

	void RegistUser(void *a_userInfo);
	void RegistUserLevel(int a_level);

	void SaveStatusReportsToFile( CString a_fileName=_T("stateReports.cfg") );
	
protected :
	/**@brief	생성자	*/
	CDCDataAdminSD(){}
	/**@brief	소멸자	*/
	~CDCDataAdminSD(){}
private :
	/**@brief	singleton.	*/
	static CDCDataAdminSD *m_instance;
};

#endif