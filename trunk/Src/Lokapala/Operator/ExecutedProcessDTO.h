/**@file	ExecutedProcessDTO
 * @brief	실행된 프로세스 보고 관련 정보를 담는 CExecutedProcessDTO 클래스를 정의한다.
 * @author	siva
 */


#ifndef EXECUTED_PROCESS_DTO_H
#define EXECUTED_PROCESS_DTO_H

/**@ingroup	GroupDAM
 * @class	CExecutedProcessDTO
 * @brief	실행된 프로세스의 보고에 관련된 정보를 담는 정보체.
 */
class CExecutedProcessDTO
{
public :
	CString m_executedProcessName;
	CString m_executedLocalIp;
	CString m_executedGlobalIp;

	CExecutedProcessDTO(CString a_executedProcessName, CString a_executedLocalIp, CString a_executedGlobalIp)
	{
		m_executedProcessName = a_executedProcessName;
		m_executedLocalIp = a_executedLocalIp;
		m_executedGlobalIp = a_executedGlobalIp;
	}
	CExecutedProcessDTO(){}
	~CExecutedProcessDTO(){}
};


#endif