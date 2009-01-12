/**@file	DharaniInterface.h
 * @brief	Dharani Protocol ��� ������Ʈ�� �������̽�
 * @author	siva
 */

#ifndef DHARANI_BI_H
#define DHARANI_BI_H

#include "DharaniDTO.h"

/**@ingroup	GroupDharani
 * @class	CDharaniInterface
 * @brief	Dharani ������Ʈ�� �ܺη� ����Ǵ� �������̽�.
 */
class CDharaniInterface
{
public :
	/**@brief	���ϴ� address�� ���ϴ� �޼����� ������. non-blocking �ȴ�.
	 * @param	a_sendData	�������� �ϴ� ������. CDharaniDTO �����ͷ�, ���ڿ� �ּҸ� ���´�.
	 */
	virtual void DharaniSendTextMessageTo(CDharaniDTO *a_sendData) = 0;
	/**@brief	����� ��� Ŭ���̾�Ʈ���� �޼����� ������.
	 * @param a_sendData	�������� �ϴ� ������. CDharaniDTO �����ͷ�, ���ڿ� �ּҸ� ���´�. �ּҴ� �ǹ̰� ����.
	 */
	virtual void DharaniBroadcastTextMessage(CDharaniDTO *a_sendData) = 0;
	virtual void DharaniSendTextToServer(CDharaniDTO *a_sendData) = 0;

	/**@brief	�ʱ�ȭ. tcp ������� ���� ������ ����� IOCP �𵨸� ��Ŀ� �°� ��� �ʱ�ȭ �κ��� �����Ѵ�.
	 * @return	void
	 */
	virtual void DharaniServerInitiallize() = 0;
	virtual int DharaniClientInitiallize(DWORD a_ServerAddress) = 0;

	/**@brief	�������� ������ �����Ѵ�.
	 */
	virtual void DharaniCloseServerConnection() = 0;
};

#endif


/**@defgroup	GroupDharani	Dharani protocol communication component
  *				Dharani ���������� ����ϴ� communication component.
  */