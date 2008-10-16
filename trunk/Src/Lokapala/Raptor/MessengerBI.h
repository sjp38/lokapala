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
	/**@brief	�ؽ�Ʈ �޼����� ���۷����Ϳ��� �����Ѵ�.	*/
	virtual void PostTextMessageToOperator(CString *a_message) = 0;
	/**@brief	���۷����ͷκ��� �ؽ�Ʈ �޼����� �޴´�.	*/
	virtual void ReceiveTextMessageFromOperator(CString *a_message) = 0;
};

#endif