/**@file	DharaniFacade.h
 * @brief	Dharani component의 facade
 * @author	siva
 */

#ifndef DHARANI_FACADE_H
#define DHARANI_FACADE_H

#include "DharaniInterface.h"
#include "DharaniDTO.h"

/**@ingroup	GroupDharani
 * @class	CDharaniFacade
 * @brief	Dharani Component의 Facade. Interface를 상속받아 실질적인 행동을 한다.
 */
class CDharaniFacade : public CDharaniInterface
{
public :
	virtual void DharaniBroadcastText(CDharaniDTO *a_sendData);
	virtual void DharaniSendTextToServer(CDharaniDTO *a_sendData);
	virtual void DharaniServerInitiallize(void);
	virtual void DharaniClientInitiallize(void);

	CDharaniFacade(){}
	~CDharaniFacade(){}

protected :
	
};

#endif