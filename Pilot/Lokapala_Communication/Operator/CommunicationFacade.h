/**@file	CommunicationFacade.h
 * @brief	CCM�� Facade ����.
 * @author	siva
 */

#ifndef COMMUNICATION_FACADE_H
#define COMMUNICATION_FACADE_H

#include "DharaniInterface.h"
#include "DharaniFacade.h"

#include "CommunicationBI.h"
/**@ingroup	GroupCCM
 * @class	CCommunicationFacade
 * @brief	CCM�� Facade.\n
			�������� CCM ������ �Ա�. Button Interface�� ����ϸ�, ���� ������Ʈ ���� Ŭ�������� ����� BI���� ���ǵ� �������̽� �Լ����� �����Ѵ�.
 * @remarks	SingleTon�� ����Ѵ�.
 */
class CCommunicationFacade : public CCommunicationBI
{
public :
	/**@brief	singleton�� ����, ��ȯ�Ѵ�.
	 * @return	singleton
	 * @remarks	static �Լ��̹Ƿ� ��𼭵� ȣ�� �� �� �ִ�.
	 */
	static CCommunicationFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CCommunicationFacade();
		}
		return m_instance;
	}

	virtual void Initiallize();
	virtual void SendTextMessage(CString a_message);
protected :
	/**@brief	������	*/
	CCommunicationFacade(){}
	/**@brief	�Ҹ���	*/
	~CCommunicationFacade(){}
private :
	/**@brief	singleton.	*/
	static CCommunicationFacade *m_instance;
};

#endif