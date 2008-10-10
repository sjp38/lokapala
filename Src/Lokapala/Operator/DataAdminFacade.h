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

	virtual void SaveDataAs(CString *a_filePath);
	virtual void LoadDataFrom(CString *a_filePath);

	//user
	virtual void AddUser(void *a_user);
	virtual void DeleteUser(CString *a_id);
	virtual void *GetUsers();

	//seat
	virtual void SetSeats(int a_x, int a_y);
	virtual void AddSeat(void *a_seat);
	virtual void DeleteSeat(int a_x, int a_y);
	virtual void *GetSeats();

	//rule
	virtual void AddRule(void *a_rule);
	virtual void DeleteRule(void *a_rule);
	virtual void *GetRules();

	//connected users	
	virtual void *GetConnectedUsers();

	void Read();
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