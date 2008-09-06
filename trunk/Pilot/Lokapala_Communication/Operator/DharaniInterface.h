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
	 * @param	a_sendMessage	�������� �ϴ� �޼���(���ڿ� ����)
	 * @param	a_targetAddress	�������� �ϴ� ����� ip �ּ�(���ڿ� ����)
	 * @return	void
	 */
	virtual void DharaniSendTextMessageTo(CDharaniDTO *a_sendData) = 0;
	virtual void DharaniSendTextToServer(CDharaniDTO *a_sendData) = 0;

	/**@brief	�ʱ�ȭ. tcp ������� ���� ������ ����� IOCP �𵨸� ��Ŀ� �°� ��� �ʱ�ȭ �κ��� �����Ѵ�.
	 * @return	void
	 */
	virtual void DharaniServerInitiallize() = 0;
	virtual void DharaniClientInitiallize(DWORD a_ServerAddress) = 0;
};

#endif


/**@defgroup	GroupDharani	Dharani protocol communication component
  *				Dharani ���������� ����ϴ� communication component.
  */