/**@file	MessengerBI.h
 * @brief	Messenger Manager�� Button Interface ����
 * @author	siva
 */

#ifndef MESSENGER_BI_H
#define MESSENGER_BI_H

/**@ingroup	GroupMSM
 * @class	CMessengerBI
 * @brief	Messenger Manager�� Button Interface.
 * @author	siva
 */
class CMessengerBI
{
public :
	/**@brief	�޽����� ���� ���� �޼����� �����Ѵ�.	*/
	virtual void PostTextMessageTo(void *a_message) = 0;
	virtual void ReceiveTextMessageFrom(void *a_message) = 0;
};

#endif