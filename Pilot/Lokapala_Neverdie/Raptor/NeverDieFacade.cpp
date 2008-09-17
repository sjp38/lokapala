/**@file	NeverDieFacade.cpp
 * @brief	NDM의 Facade의 멤버함수 구현
 * author	siva
 */

#include "stdafx.h"
#include "NeverDieFacade.h"
#include "APIHookingManager.h"

/**@brief	어떤 경우에도 랩터가 죽지 않게 만든다.\n
 *			내부적으로 글로벌 api 후킹으로 TerminateProcess를 후킹하고, 컴퓨터 부팅 시 자동 실행이 되도록 레지스트리를 만진 후,
 *			레지스트리 접근을 막고, WM_CLOSE 등의 종료 메세지들에 대응한다.
 */
void CNeverDieFacade::StartNeverDie()
{
	CAPIHookingManager::Instance()->StartAPIHooking();
}


void CNeverDieFacade::StopNeverDie()
{
	CAPIHookingManager::Instance()->StopAPIHooking();
}