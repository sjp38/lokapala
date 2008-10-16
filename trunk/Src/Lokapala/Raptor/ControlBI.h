/**@file	ControlBI.h
 * @brief	CTM의 Button Interface 정의
 * @author	siva
 */

#ifndef CONTROL_BI_H
#define CONTROL_BI_H

/**@ingroup GroupCTM
 * @class	CControlBI
 * @brief	Control Manager의 Button Interface.\n
			Mediator에게 자신을 노출하여 Mediator로부터 CCM으로의 인터페이스를 공개한다.
 * @remarks	인터페이스일 뿐으로, Facade가 상속한다.
 */
class CControlBI
{
public :
	/**@brief	사용자의 정상적인 컴퓨터 사용을 제한한다.	*/
	virtual void RestraintUser() = 0;

	/**@brief	사용자의 정상적인 컴퓨터 사용을 허락한다.	*/
	virtual void ReleaseUser() = 0;

	/**@brief	강제로 사용자의 로그인을 해준다.	*/
	virtual void Login(void *a_userInfo) = 0;

	/**@brief	강제로 사용자를 로그아웃 시킨다.	*/
	virtual void Logout(void *a_message) = 0;

	/**@brief	컴퓨터를 꺼버린다.	*/
	virtual void Shutdown(void *a_message) = 0;

	/**@brief	컴퓨터를 재부팅 시킨다.	*/
	virtual void Reboot(void *a_message) = 0;

	/**@brief	실행 중인 프로세스를 모조리 죽여버린다.	*/
	virtual void GenocideProcesses(void *a_message) = 0;

	/**@brief	특정 이름의 프로세스를 죽인다.	*/
	virtual void KillProcess(void *a_processName) = 0;

	/**@brief	특정 이름의 프로세스를 실행시킨다.	*/
	virtual void ExecuteProcess(void *a_processName) = 0;
};

#endif