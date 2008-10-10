/**@file	DataAdminFacade.cpp
 * @brief	DAM�� Facade�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "DataAdminFacade.h"

#include "DataAdminManager.h"


/**@brief	���� �����͸� ���Ϸ� �����Ѵ�.
 */
void CDataAdminFacade::SaveDataAs(CString *a_filePath)
{
	CDataAdminManager::Instance()->SaveToFile(a_filePath);
}

/**@brief	���Ϸκ��� �����͸� �о���δ�.
 */
void CDataAdminFacade::LoadDataFrom(CString *a_filePath)
{
	CDataAdminManager::Instance()->LoadFromFile(a_filePath);
}

/**@brief	���� �ϳ��� �߰��Ѵ�.
 */
void CDataAdminFacade::AddUser(void *a_user)
{
	CDataAdminManager::Instance()->AddUser(a_user);
}

/**@brief	���� �ϳ��� �����Ѵ�.
 */
void CDataAdminFacade::DeleteUser(CString *a_id)
{
	CDataAdminManager::Instance()->DeleteUser(a_id);
}

/**@brief	���� ���� ��ü�� �˷��ش�.\n
 *			���� ���� ����ü�� ������ ��� ������ �˰� �� �ʿ�� �����Ƿ� �����ʹ� void �����ͷ� ĳ���� �Ǿ� ���޵ȴ�.\n
 *			���� Ŭ���̾�Ʈ �ڵ忡���� ���� ���� ����ü�� ������ �˸�(���� ����ü ����� ��Ŭ���) �ȴ�.
 * @return	void �����ͷ� ĳ���� �� ���� ���� ����ü�� ������
 */
void *CDataAdminFacade::GetUsers()
{
	return CDataAdminManager::Instance()->GetUsers();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**@brief	��ü �¼� ũ�⸦ �����Ѵ�.
 */
void CDataAdminFacade::SetSeats(int a_x, int a_y)
{
	CDataAdminManager::Instance()->SetSeats(a_x, a_y);
}

/**@brief	�¼� ������ �߰��Ѵ�.
 */
void CDataAdminFacade::AddSeat(void *a_seat)
{
	CDataAdminManager::Instance()->AddSeat(a_seat);
}

/**@brief	�¼� ������ �����Ѵ�.
 */
void CDataAdminFacade::DeleteSeat(int a_x, int a_y)
{
	CDataAdminManager::Instance()->DeleteSeat(a_x, a_y);
}

/**@brief	��ü �¼� ������ ��´�.
 *			void �����ͷ� ĳ���� �Ǿ� ���޵ǹǷ� ���� Ŭ���̾�Ʈ �ڵ忡���� ���� �¼� ����ü ������ �˸� �ȴ�.
 */
void *CDataAdminFacade::GetSeats()
{
	return CDataAdminManager::Instance()->GetSeats();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**@brief	���� ���μ��� ���� ��Ģ �ϳ��� �߰��Ѵ�.
 */
void CDataAdminFacade::AddRule(void *a_rule)
{
	CDataAdminManager::Instance()->AddRule(a_rule);
}


/**@brief	���� ���μ��� ���� ��Ģ �ϳ��� �����Ѵ�.
 */
void CDataAdminFacade::DeleteRule(void *a_rule)
{
	CDataAdminManager::Instance()->DeleteRule(a_rule);
}

/**@brief	���� ���μ��� ���� ��Ģ ��ü�� ��ȯ�Ѵ�.
 *			void �����ͷ� ĳ���� �Ǿ� ���޵ǹǷ� ���� Ŭ���̾�Ʈ �ڵ忡���� ���� �¼� ����ü ������ �˸� �ȴ�.
 */
void *CDataAdminFacade::GetRules()
{
	return CDataAdminManager::Instance()->GetRules();
}

/**@brief	���� ���ӵ� ��ü ����� ������ ��´�.
 *			void �����ͷ� ĳ���� �Ǿ� ���޵ǹǷ� ���� Ŭ���̾�Ʈ �ڵ忡���� ���� �¼� ����ü ������ �˸� �ȴ�.
 */
void *CDataAdminFacade::GetConnectedUsers()
{
	return CDataAdminManager::Instance()->GetConnectedUsers();
}

/**@brief	������Ʈ �� ����� �׽�Ʈ �ϱ� ���� ��� �Լ�.\n
 *			DAM���κ��� ������ ���带 �ϴ� ����. �ٸ� ������Ʈ���� SD�� ���� mediator�� ��û�ϸ�, mediator���� DAM�� BI�� ���� ȣ���Ѵ�.
 */
void CDataAdminFacade::Read()
{
	;
}