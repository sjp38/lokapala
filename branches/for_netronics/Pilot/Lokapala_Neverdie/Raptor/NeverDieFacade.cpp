/**@file	NeverDieFacade.cpp
 * @brief	NDM�� Facade�� ����Լ� ����
 * author	siva
 */

#include "stdafx.h"
#include "NeverDieFacade.h"
#include "APIHookingManager.h"
#include "AutoExecuteManager.h"

/**@brief	� ��쿡�� ���Ͱ� ���� �ʰ� �����.\n
 *			���������� �۷ι� api ��ŷ���� TerminateProcess�� ��ŷ�ϰ�, ��ǻ�� ���� �� �ڵ� ������ �ǵ��� ������Ʈ���� ���� ��,
 *			������Ʈ�� ������ ����, WM_CLOSE ���� ���� �޼����鿡 �����Ѵ�.
 */
void CNeverDieFacade::StartNeverDie()
{
	m_state = true;
	CAPIHookingManager::Instance()->StartAPIHooking();
	CAutoExecuteManager::Instance()->SetAutoExecute();
}


/**@brief	���Ͱ� ���� �� �ְ� �����.\n
 */
void CNeverDieFacade::StopNeverDie()
{
	m_state = false;
	CAPIHookingManager::Instance()->StopAPIHooking();
	CAutoExecuteManager::Instance()->ClearAutoExecute();
}


/**@brief	���� ���Ͱ� �׾ �Ǵ��� �ȵǴ����� ���ϰ��� ���� �˷��ش�.
 * @return	�׾ �ȵȴٸ� true, �׾ �ȴٸ� false�� �����Ѵ�.
 */
bool CNeverDieFacade::GetNeverDieState()
{
	return m_state;
}