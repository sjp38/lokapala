/**@file	LogDTO.h
 * @brief	로그 관련 정보를 담는 정보체 클래스 CLogDTO를 정의한다.
 * @author	siva
 */

#ifndef LOG_DTO_H
#define LOG_DTO_H

//enum From{DCM, MSM};
//enum Behavior{LOGIN_REQUEST, LOGIN_ACCESS, LOGIN_REFUSE, GETSTATUSREPORT, };
//enum Type{ATTEMPT, SUCCESS, FALSE};

/**@ingroup	GroupLGM
 * @class	CLogDTO
 * @brief	실행 기록에 관한 정보를 담는다.
 */
class CLogDTO
{
public :
	CString comment;
	CLogDTO(){}
	~CLogDTO(){}
};

#endif
