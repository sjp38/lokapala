/**@file	DecisionManager.cpp
 * @brief	CDecisionManager 클래스의 멤버함수를 구현한다.
 * @author	siva
 */

#include "stdafx.h"
#include "DecisionManager.h"

#include "DCDataAdminSD.h"
#include "UsersDataDTO.h"
#include "LoginRequestDTO.h"
#include "ConnectedUsersDTO.h"
#include "DCCommunicationSD.h"


/**@brief	사용자 로그인 처리. 올바른 사용자인지 확인한다.
 * @param	a_loginRequestData	사용자 로그인 정보의 포인터. 해당 DTO의 포인터이지만 void 포인터로 캐스팅 해 사용한다.
 */
void CDecisionManager::UserLogin(void *a_loginRequestData)
{
	CLoginRequestDTO *loginRequestData;
	loginRequestData = (CLoginRequestDTO *)a_loginRequestData;

	//SD를 통해 DAM으로부터 사용자 정보를 얻어와 대조한다.
	CUsersDataDTO *usersData;
	usersData = (CUsersDataDTO *)( CDCDataAdminSD::Instance()->GetUsersDataDTO() );
	CUserDataDTO *userData;
	userData = usersData->GetUserById( loginRequestData->m_lowLevelPassword );
	if(userData == NULL)
	{
		return;
	}
	if( userData->m_name == loginRequestData->m_name 
		&& userData->m_highLevelPassword == loginRequestData->m_highLevelPassword )
	{
		CConnectedUsersDTO *connectedUsers = (CConnectedUsersDTO *)CDCDataAdminSD::Instance()->GetConnectedUsersDTO();
		CConnectedUserDTO user;
		user.m_userId = loginRequestData->m_lowLevelPassword;
		connectedUsers->RegistConnected(&user);

		loginRequestData->m_level = userData->m_level;
		
		//DCCommunication SD를 이용해 로그인 허용 메세지를 날린다.
		CDCCommunicationSD::Instance()->NotifyAccepted(loginRequestData);
	}
}