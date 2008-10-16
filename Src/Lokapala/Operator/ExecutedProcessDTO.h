/**@file	ExecutedProcessDTO
 * @brief	����� ���μ��� ���� ���� ������ ��� CExecutedProcessDTO Ŭ������ �����Ѵ�.
 * @author	siva
 */


#ifndef EXECUTED_PROCESS_DTO_H
#define EXECUTED_PROCESS_DTO_H

/**@ingroup	GroupDAM
 * @class	CExecutedProcessDTO
 * @brief	����� ���μ����� ���� ���õ� ������ ��� ����ü.
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