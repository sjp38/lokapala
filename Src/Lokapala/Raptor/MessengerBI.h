/**@file	MessengerBI.h
 * @brief	Messenger Manager의 Button Interface 정의
 * @author	siva
 */

#ifndef MESSENGER_BI_H
#define MESSENGER_BI_H

/**@ingroup	GroupMSM
 * @class	CMessengerBI
 * @brief	Messenger Manager의 Button Interface.
 * @author	siva
 */
class CMessengerBI
{
public :
	/**@brief	텍스트 메세지를 오퍼레이터에게 전송한다.	*/
	virtual void PostTextMessageToOperator(CString *a_message) = 0;
	/**@brief	오퍼레이터로부터 텍스트 메세지를 받는다.	*/
	virtual void ReceiveTextMessageFromOperator(CString *a_message) = 0;
};

#endif