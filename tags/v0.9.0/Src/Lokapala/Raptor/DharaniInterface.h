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
	 * @param	a_sendData	보내고자 하는 데이터. CDharaniDTO 포인터로, 문자와 주소를 갖는다.
	 */
	virtual void DharaniSendTextMessageTo(CDharaniDTO *a_sendData) = 0;
	/**@brief	연결된 모든 클라이언트에게 메세지를 보낸다.
	 * @param a_sendData	보내고자 하는 데이터. CDharaniDTO 포인터로, 문자와 주소를 갖는다. 주소는 의미가 없다.
	 */
	virtual void DharaniBroadcastTextMessage(CDharaniDTO *a_sendData) = 0;
	virtual void DharaniSendTextToServer(CDharaniDTO *a_sendData) = 0;

	/**@brief	초기화. tcp 기반으로 리슨 소켓을 만들고 IOCP 모델링 방식에 맞게 모든 초기화 부분을 수행한다.
	 * @return	void
	 */
	virtual void DharaniServerInitiallize() = 0;
	virtual int DharaniClientInitiallize(DWORD a_ServerAddress) = 0;

	/**@brief	서버와의 연결을 종료한다.
	 */
	virtual void DharaniCloseServerConnection() = 0;
};

#endif


/**@defgroup	GroupDharani	Dharani protocol communication component
  *				Dharani 프로토콜을 사용하는 communication component.
  */