/**@file	NeverDieFacade.cpp
 * @brief	NDM�� Facade�� ����Լ� ����
 * author	siva
 */

#include "stdafx.h"
#include "NeverDieFacade.h"
#include "APIHookingManager.h"

/**@brief	� ��쿡�� ���Ͱ� ���� �ʰ� �����.\n
 *			���������� �۷ι� api ��ŷ���� TerminateProcess�� ��ŷ�ϰ�, ��ǻ�� ���� �� �ڵ� ������ �ǵ��� ������Ʈ���� ���� ��,
 *			������Ʈ�� ������ ����, WM_CLOSE ���� ���� �޼����鿡 �����Ѵ�.
 */
void CNeverDieFacade::StartNeverDie()
{
	CAPIHookingManager::Instance()->StartAPIHooking();
}


void CNeverDieFacade::StopNeverDie()
{
	CAPIHookingManager::Instance()->StopAPIHooking();
}