/**@file	DataAdminFacade.h
 * @brief	DAM�� Facade ����.
 * @author	siva
 */
#ifndef DATA_ADMIN_FACADE_H
#define DATA_ADMIN_FACADE_H

#include "DataAdminBI.h"

/**@ingroup GroupDAM
 * @class	CDataAdminFacade
 * @brief	DAM�� Facade.\n
 *			�������� DAM������ �Ա�. Button Interface�� ����ϸ�, ���� ������Ʈ ���� Ŭ�������� ����� BI���� ���ǵ� �������̽� �Լ����� �����Ѵ�.
 * @remarks	SingleTon�� ����Ѵ�. 
 */
class CDataAdminFacade : public CDataAdminBI
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
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
	/**@brief	������	*/
	CDataAdminFacade(){}
	/**@brief	�Ҹ���	*/
	~CDataAdminFacade(){}
private :
	/**@brief	singleton	*/
	static CDataAdminFacade *m_instance;
};

#endif