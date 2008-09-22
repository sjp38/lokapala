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