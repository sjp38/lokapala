/**@file	DharaniFacade.h
 * @brief	Dharani component�� facade
 * @author	siva
 */

#ifndef DHARANI_FACADE_H
#define DHARANI_FACADE_H

#include "DharaniInterface.h"
#include "DharaniDTO.h"

/**@ingroup	GroupDharani
 * @class	CDharaniFacade
 * @brief	Dharani Component�� Facade. Interface�� ��ӹ޾� �������� �ൿ�� �Ѵ�.
 */
class CDharaniFacade : public CDharaniInterface
{
public :
	static CDharaniFacade *Instance()
	{
		if(!m_instance)
		{
			m_instance = new CDharaniFacade();
		}
		return m_instance;
	}
	virtual void DharaniSendTextMessageTo(CDharaniDTO *a_sendData);
	virtual void DharaniBroadcastTextMessage(CDharaniDTO *a_sendData);
	virtual void DharaniSendTextToServer(CDharaniDTO *a_sendData);
	virtual void DharaniServerInitiallize(void);
	virtual void DharaniClientInitiallize(DWORD a_ServerAddress);

	CDharaniFacade(){}
	~CDharaniFacade(){}

protected :
private :
	static CDharaniFacade *m_instance;
	
};

#endif