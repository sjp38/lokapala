/**@file	LogDTO.h
 * @brief	�α� ���� ������ ��� ����ü Ŭ���� CLogDTO�� �����Ѵ�.
 * @author	siva
 */

#ifndef LOG_DTO_H
#define LOG_DTO_H

//enum From{DCM, MSM};
//enum Behavior{LOGIN_REQUEST, LOGIN_ACCESS, LOGIN_REFUSE, GETSTATUSREPORT, };
//enum Type{ATTEMPT, SUCCESS, FALSE};

/**@ingroup	GroupLGM
 * @class	CLogDTO
 * @brief	���� ��Ͽ� ���� ������ ��´�.
 */
class CLogDTO
{
public :
	CString comment;
	CLogDTO(){}
	~CLogDTO(){}
};

#endif