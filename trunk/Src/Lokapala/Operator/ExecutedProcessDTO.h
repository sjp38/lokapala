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
	CString m_executedHostAddress;

	CExecutedProcessDTO(CString a_executedProcessName, CString a_executedHostAddress)
	{
		m_executedProcessName = a_executedProcessName;
		m_executedHostAddress = a_executedHostAddress;
	}
	CExecutedProcessDTO(){}
	~CExecutedProcessDTO(){}
};


#endif