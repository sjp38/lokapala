/**@file	DecisionBI.h
 * @brief	DCM의 Button Interface 정의
 * @author	siva
 */
#ifndef DECISION_BI_H
#define DECISION_BI_H

/**@ingroup	GroupDCM
 * @class	CDecisionBI
 * @brief	DCM의 Button Interface.
 * @remarks	인터페이스일 뿐이다.
 */
class CDecisionBI
{
public :
	/**@brief	오퍼레이터에게 로그인 요청을 한다.
	 */
	virtual void LoginRequest(void *a_userInfo) = 0;
	/**@brief	로그인 허용에 대해 서비스를 한다.
	 */
	virtual void LoginAccepted(int a_level) = 0;
};

#endif