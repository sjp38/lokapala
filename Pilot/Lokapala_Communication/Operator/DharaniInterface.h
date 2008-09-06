/**@file	DharaniInterface.h
 * @brief	Dharani Protocol 통신 컴포넌트의 인터페이스
 * @author	siva
 */

#ifndef DHARANI_BI_H
#define DHARANI_BI_H

#include "DharaniDTO.h"

/**@ingroup	GroupDharani
 * @class	CDharaniInterface
 * @brief	Dharani 컴포넌트의 외부로 노출되는 인터페이스.
 */
class CDharaniInterface
{
public :
	/**@brief	원하는 address로 원하는 메세지를 보낸다. non-blocking 된다.
	 * @param	a_sendMessage	보내고자 하는 메세지(문자열 형태)
	 * @param	a_targetAddress	보내고자 하는 대상의 ip 주소(문자열 형태)
	 * @return	void
	 */
	virtual void DharaniSendTextMessageTo(CDharaniDTO *a_sendData) = 0;
	virtual void DharaniSendTextToServer(CDharaniDTO *a_sendData) = 0;

	/**@brief	초기화. tcp 기반으로 리슨 소켓을 만들고 IOCP 모델링 방식에 맞게 모든 초기화 부분을 수행한다.
	 * @return	void
	 */
	virtual void DharaniServerInitiallize() = 0;
	virtual void DharaniClientInitiallize(DWORD a_ServerAddress) = 0;
};

#endif


/**@defgroup	GroupDharani	Dharani protocol communication component
  *				Dharani 프로토콜을 사용하는 communication component.
  */