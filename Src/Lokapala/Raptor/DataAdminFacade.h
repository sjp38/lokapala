/**@file	DataAdminFacade.h
 * @brief	DAM의 Facade 정의.
 * @author	siva
 */
#ifndef DATA_ADMIN_FACADE_H
#define DATA_ADMIN_FACADE_H

#include "DataAdminBI.h"
/**@ingroup GroupDAM
 * @class	CDataAdminFacade
 * @brief	DAM의 Facade.\n
 *			실질적인 DAM으로의 입구. Button Interface를 상속하며, 내부 컴포넌트 내부 클래스들을 사용해 BI에서 정의된 인터페이스 함수들을 구현한다.
 * @remarks	SingleTon을 사용한다. 
 */
class CDataAdminFacade : public CDataAdminBI
{
public :
	/**@brief	singleton을 생성, 반환한다.
	 * @return	singleton
	 * @remarks	static 함수이므로 어디서든 호출 할 수 있다.
	 */
	static CDataAdminFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDataAdminFacade();
		}
		return m_instance;
	}

	void RegistUser(void *a_userInfo);
	void RegistUserLevel(int a_level);
	void *GetStatusReports();

	void AddStatusReport(void *a_statusReport);
	void SaveStatusReportsToFile(CString a_filePath);
	void LoadStatusReportsFromFile(CString a_filePath);

protected :
	/**@brief	생성자	*/
	CDataAdminFacade(){}
	/**@brief	소멸자	*/
	~CDataAdminFacade(){}
private :
	/**@brief	singleton	*/
	static CDataAdminFacade *m_instance;
};

#endif
