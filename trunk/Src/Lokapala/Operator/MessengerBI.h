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
	/**@brief	메신저를 통해 들어온 메세지를 전달한다.	*/
	virtual void PostTextMessageTo(void *a_message) = 0;
	virtual void ReceiveTextMessageFrom(void *a_message) = 0;
};

#endif