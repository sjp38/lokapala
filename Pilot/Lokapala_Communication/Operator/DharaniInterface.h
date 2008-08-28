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
	 * @param	a_sendData	보내고자 하는 메세지와 목표 주소의 공유기 ip, 사설 ip를 갖는 클래스.
	 * @return	void
	 */
	virtual void DharaniSend(CDharaniDTO *a_sendData) = 0;

	/**@brief	서버 모델 초기화. tcp 기반으로 리슨 소켓을 만들고 IOCP 모델링 방식에 맞게 모든 초기화 부분을 수행한다.
	 * @return	void
	 */
	virtual void DharaniServerInitiallize() = 0;

	/**@brief	클라이언트 모델 초기화.
	 */
	virtual void DharaniClientInitiallize() = 0;
};

#endif


/**@defgroup	GroupDharani	Dharani protocol communication component
  *				Dharani 프로토콜을 사용하는 communication component.
  */