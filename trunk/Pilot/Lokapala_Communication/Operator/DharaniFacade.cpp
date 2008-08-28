/**@file	DharaniFacade.cpp
 * @brief	DharaniFacade의 멤버 함수들을 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DharaniClientManager.h"
#include "DharaniServerManager.h"
#include "DharaniFacade.h"

/**@brief	dharani 컴포넌트의 서버 모델 초기화. 리슨 소켓을 만들고 IOCP를 위한 준비 단계를 수행한다.
 */
void CDharaniFacade::DharaniServerInitiallize()
{
	CDharaniServerManager::Instance()->Initiallize();
}

/**@brief	dharani 컴포넌트의 클라이언트 모델 초기화.
 */
void CDharaniFacade::DharaniClientInitiallize()
{
	CDharaniClientManager::Instance()->Initiallize();
}


void CDharaniFacade::DharaniSend(CDharaniDTO *a_sendData)
{
}