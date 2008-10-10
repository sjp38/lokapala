/**@file	DecisionManager.cpp
 * @brief	CDecisionManager Ŭ������ ����Լ��� �����Ѵ�.
 * @author	siva
 */

#include "stdafx.h"
#include "DecisionManager.h"

#include "DCDataAdminSD.h"
#include "UsersDataDTO.h"
#include "LoginRequestDTO.h"
#include "ConnectedUsersDTO.h"
#include "DCCommunicationSD.h"


/**@brief	����� �α��� ó��. �ùٸ� ��������� Ȯ���Ѵ�.
 * @param	a_loginRequestData	����� �α��� ������ ������. �ش� DTO�� ������������ void �����ͷ� ĳ���� �� ����Ѵ�.
 */
void CDecisionManager::UserLogin(void *a_loginRequestData)
{
	CLoginRequestDTO *loginRequestData;
	loginRequestData = (CLoginRequestDTO *)a_loginRequestData;

	//SD�� ���� DAM���κ��� ����� ������ ���� �����Ѵ�.
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
		
		//DCCommunication SD�� �̿��� �α��� ��� �޼����� ������.
		CDCCommunicationSD::Instance()->NotifyAccepted(loginRequestData);
	}
}