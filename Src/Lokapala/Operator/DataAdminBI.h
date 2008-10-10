/**@file	DataAdminBI.h
 * @brief	DAM의 Button Interface 정의
 * @author	siva
 */

#ifndef DATA_ADMIN_BI_H
#define DATA_ADMIN_BI_H

/**@ingroup GroupDAM
 * @class	CDataAdminBI
 * @brief	Communication Manager의 Button Interface.\n
			Mediator에게 자신을 노출하여 Mediator로부터 CCM으로의 인터페이스를 공개한다.
 * @remarks	인터페이스일 뿐으로, Facade가 상속한다.
 */
class CDataAdminBI
{
public :
	/**@brief	파일에 현재 데이터를 저장한다.	*/
	virtual void SaveDataAs(CString *a_filePath) = 0;

	/**@brief	파일로부터 데이터를 읽어들인다.	*/
	virtual void LoadDataFrom(CString *a_filePath) = 0;

	//user
	/**@breif	유저를 추가한다.	*/
	virtual void AddUser(void *a_user) = 0;
	/**@brief	특정 id의 유저를 삭제한다.	*/
	virtual void DeleteUser(CString *a_id) = 0;
	/**@brief	유저 정보 전체를 알려준다.\n
	 *			실제 유저 정보체의 구조를 모든 곳에서 알게 될 필요는 없으므로 포인터는 void 포인터로 캐스팅 되어 전달된다.\n
	 *			최종 클라이언트 코드에서만 실제 유저 정보체의 구조를 알면(유저 정보체 헤더를 인클루드) 된다.
	 * @return	void 포인터로 캐스팅 된 유저 정보 구조체의 포인터
	 */
	virtual void *GetUsers() = 0;


	//seat
	/**@brief	좌석의 전체 크기를 설정한다.	*/
	virtual void SetSeats(int a_x, int a_y) = 0;
	/**@brief	좌석 정보를 추가한다.	*/
	virtual void AddSeat(void *a_seat) = 0;
	/**@brief	좌석 정보를 삭제한다.	*/
	virtual void DeleteSeat(int a_x, int a_y) = 0;
	/**@brief	전체 좌석 정보를 얻는다.
	 *			void 포인터로 캐스팅 되어 전달되므로 최종 클라이언트 코드에서만 실제 좌석 정보체 구조를 알면 된다.
	 */
	virtual void *GetSeats() = 0;


	//rule
	/**@brief	금지 프로세스 관련 규칙 하나를 추가한다.	*/
	virtual void AddRule(void *a_rule) = 0;
	/**@brief	금지 프로세스 관련 규칙 하나를 삭제한다.	*/
	virtual void DeleteRule(void *a_rule) = 0;
	/**@brief	전체 금지 프로세스 관련 규칙을 얻는다.
	 *			void 포인터로 캐스팅 되어 전달되므로 최종 클라이언트 코드에서만 실제 좌석 정보체 구조를 알면 된다.
	 */
	virtual void *GetRules() = 0;


	//connected users
	/**@brief	현재 접속된 전체 사용자 정보를 얻는다.
	 *			void 포인터로 캐스팅 되어 전달되므로 최종 클라이언트 코드에서만 실제 좌석 정보체 구조를 알면 된다.
	 */
	virtual void *GetConnectedUsers() = 0;


	virtual void Read()=0;
};

#endif