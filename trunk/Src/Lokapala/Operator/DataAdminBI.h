/**@file	DataAdminBI.h
 * @brief	DAM�� Button Interface ����
 * @author	siva
 */

#ifndef DATA_ADMIN_BI_H
#define DATA_ADMIN_BI_H

/**@ingroup GroupDAM
 * @class	CDataAdminBI
 * @brief	Communication Manager�� Button Interface.\n
			Mediator���� �ڽ��� �����Ͽ� Mediator�κ��� CCM������ �������̽��� �����Ѵ�.
 * @remarks	�������̽��� ������, Facade�� ����Ѵ�.
 */
class CDataAdminBI
{
public :
	/**@brief	���Ͽ� ���� �����͸� �����Ѵ�.	*/
	virtual void SaveDataAs(CString *a_filePath) = 0;

	/**@brief	���Ϸκ��� �����͸� �о���δ�.	*/
	virtual void LoadDataFrom(CString *a_filePath) = 0;

	//user
	/**@breif	������ �߰��Ѵ�.	*/
	virtual void AddUser(void *a_user) = 0;
	/**@brief	Ư�� id�� ������ �����Ѵ�.	*/
	virtual void DeleteUser(CString *a_id) = 0;
	/**@brief	���� ���� ��ü�� �˷��ش�.\n
	 *			���� ���� ����ü�� ������ ��� ������ �˰� �� �ʿ�� �����Ƿ� �����ʹ� void �����ͷ� ĳ���� �Ǿ� ���޵ȴ�.\n
	 *			���� Ŭ���̾�Ʈ �ڵ忡���� ���� ���� ����ü�� ������ �˸�(���� ����ü ����� ��Ŭ���) �ȴ�.
	 * @return	void �����ͷ� ĳ���� �� ���� ���� ����ü�� ������
	 */
	virtual void *GetUsers() = 0;


	//seat
	/**@brief	�¼��� ��ü ũ�⸦ �����Ѵ�.	*/
	virtual void SetSeats(int a_x, int a_y) = 0;
	/**@brief	�¼� ������ �߰��Ѵ�.	*/
	virtual void AddSeat(void *a_seat) = 0;
	/**@brief	�¼� ������ �����Ѵ�.	*/
	virtual void DeleteSeat(int a_x, int a_y) = 0;
	/**@brief	��ü �¼� ������ ��´�.
	 *			void �����ͷ� ĳ���� �Ǿ� ���޵ǹǷ� ���� Ŭ���̾�Ʈ �ڵ忡���� ���� �¼� ����ü ������ �˸� �ȴ�.
	 */
	virtual void *GetSeats() = 0;


	//rule
	/**@brief	���� ���μ��� ���� ��Ģ �ϳ��� �߰��Ѵ�.	*/
	virtual void AddRule(void *a_rule) = 0;
	/**@brief	���� ���μ��� ���� ��Ģ �ϳ��� �����Ѵ�.	*/
	virtual void DeleteRule(void *a_rule) = 0;
	/**@brief	��ü ���� ���μ��� ���� ��Ģ�� ��´�.
	 *			void �����ͷ� ĳ���� �Ǿ� ���޵ǹǷ� ���� Ŭ���̾�Ʈ �ڵ忡���� ���� �¼� ����ü ������ �˸� �ȴ�.
	 */
	virtual void *GetRules() = 0;


	//connected users
	/**@brief	���� ���ӵ� ��ü ����� ������ ��´�.
	 *			void �����ͷ� ĳ���� �Ǿ� ���޵ǹǷ� ���� Ŭ���̾�Ʈ �ڵ忡���� ���� �¼� ����ü ������ �˸� �ȴ�.
	 */
	virtual void *GetConnectedUsers() = 0;


	virtual void Read()=0;
};

#endif