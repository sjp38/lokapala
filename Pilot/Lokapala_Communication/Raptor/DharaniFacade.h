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
	virtual void DharaniSend(CDharaniDTO *a_sendData);
	virtual void DharaniServerInitiallize(void);
	virtual void DharaniClientInitiallize(void);

	CDharaniFacade(){}
	~CDharaniFacade(){}

protected :
	
};

#endif