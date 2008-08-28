/**@file	DharaniClientManager.h
 * @brief	CDharaniClientManager�� �����Ѵ�.
 * @author	siva
 */

#ifndef DHARANI_CLIENT_MANAGER_H
#define DHARANI_CLIENT_MANAGER_H

/**@ingroup GroupDharani
 * @class	CDharaniClientManager
 * @brief	Dharani ������Ʈ���� Ŭ���̾�Ʈ ������ ����Ѵ�.
 * @remarks	singleton�� ����Ѵ�.
 */
class CDharaniClientManager
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CDharaniClientManager *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDharaniClientManager();
		}
		return m_instance;
	}

	void Initiallize();

protected :
	/**@brief	������	*/
	CDharaniClientManager(){}
	/**@brief	�Ҹ���	*/
	~CDharaniClientManager(){}

private :
	SOCKET m_socket;
	/**@brief	�̱���	*/
	static CDharaniClientManager *m_instance;

};

#endif