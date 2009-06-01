/**@brief	DAM에서 사용하는 싱글톤들을 초기화
 */

#include "stdafx.h"
#include "DataAdminFacade.h"
#include "DataAdminManager.h"


CDataAdminFacade *CDataAdminFacade::m_instance = NULL;
CDataAdminManager *CDataAdminManager::m_instance = NULL;
