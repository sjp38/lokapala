/**@file	DataAdminFacade.cpp
 * @brief	DAM의 Facade의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "DataAdminFacade.h"

#include "DataAdminManager.h"


/**@brief	현재 데이터를 파일로 저장한다.
 */
void CDataAdminFacade::SaveDataAs(CString *a_filePath)
{
	CDataAdminManager::Instance()->SaveToFile(a_filePath);
}

/**@brief	파일로부터 데이터를 읽어들인다.
 */
void CDataAdminFacade::LoadDataFrom(CString *a_filePath)
{
	CDataAdminManager::Instance()->LoadFromFile(a_filePath);
}

/**@brief	유저 하나를 추가한다.
 */
void CDataAdminFacade::AddUser(void *a_user)
{
	CDataAdminManager::Instance()->AddUser(a_user);
}

/**@brief	유저 하나를 삭제한다.
 */
void CDataAdminFacade::DeleteUser(CString *a_id)
{
	CDataAdminManager::Instance()->DeleteUser(a_id);
}

/**@brief	유저 정보 전체를 알려준다.\n
 *			실제 유저 정보체의 구조를 모든 곳에서 알게 될 필요는 없으므로 포인터는 void 포인터로 캐스팅 되어 전달된다.\n
 *			최종 클라이언트 코드에서만 실제 유저 정보체의 구조를 알면(유저 정보체 헤더를 인클루드) 된다.
 * @return	void 포인터로 캐스팅 된 유저 정보 구조체의 포인터
 */
void *CDataAdminFacade::GetUsers()
{
	return CDataAdminManager::Instance()->GetUsers();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**@brief	전체 좌석 크기를 설정한다.
 */
void CDataAdminFacade::SetSeats(int a_x, int a_y)
{
	CDataAdminManager::Instance()->SetSeats(a_x, a_y);
}

/**@brief	좌석 정보를 추가한다.
 */
void CDataAdminFacade::AddSeat(void *a_seat)
{
	CDataAdminManager::Instance()->AddSeat(a_seat);
}

/**@brief	좌석 정보를 삭제한다.
 */
void CDataAdminFacade::DeleteSeat(int a_x, int a_y)
{
	CDataAdminManager::Instance()->DeleteSeat(a_x, a_y);
}

/**@brief	전체 좌석 정보를 얻는다.
 *			void 포인터로 캐스팅 되어 전달되므로 최종 클라이언트 코드에서만 실제 좌석 정보체 구조를 알면 된다.
 */
void *CDataAdminFacade::GetSeats()
{
	return CDataAdminManager::Instance()->GetSeats();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**@brief	금지 프로세스 관련 규칙 하나를 추가한다.
 */
void CDataAdminFacade::AddRule(void *a_rule)
{
	CDataAdminManager::Instance()->AddRule(a_rule);
}


/**@brief	금지 프로세스 관련 규칙 하나를 삭제한다.
 */
void CDataAdminFacade::DeleteRule(void *a_rule)
{
	CDataAdminManager::Instance()->DeleteRule(a_rule);
}

/**@brief	금지 프로세스 관련 규칙 전체를 반환한다.
 *			void 포인터로 캐스팅 되어 전달되므로 최종 클라이언트 코드에서만 실제 좌석 정보체 구조를 알면 된다.
 */
void *CDataAdminFacade::GetRules()
{
	return CDataAdminManager::Instance()->GetRules();
}

/**@brief	현재 접속된 전체 사용자 정보를 얻는다.
 *			void 포인터로 캐스팅 되어 전달되므로 최종 클라이언트 코드에서만 실제 좌석 정보체 구조를 알면 된다.
 */
void *CDataAdminFacade::GetConnectedUsers()
{
	return CDataAdminManager::Instance()->GetConnectedUsers();
}

/**@brief	컴포넌트 간 통신을 테스트 하기 위한 멤버 함수.\n
 *			DAM으로부터 데이터 리드를 하는 역할. 다른 컴포넌트에서 SD를 통해 mediator에 요청하면, mediator에서 DAM의 BI를 통해 호출한다.
 */
void CDataAdminFacade::Read()
{
	;
}