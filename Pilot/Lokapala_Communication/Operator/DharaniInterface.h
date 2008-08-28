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
	 * @param	a_sendData	�������� �ϴ� �޼����� ��ǥ �ּ��� ������ ip, �缳 ip�� ���� Ŭ����.
	 * @return	void
	 */
	virtual void DharaniSend(CDharaniDTO *a_sendData) = 0;

	/**@brief	���� �� �ʱ�ȭ. tcp ������� ���� ������ ����� IOCP �𵨸� ��Ŀ� �°� ��� �ʱ�ȭ �κ��� �����Ѵ�.
	 * @return	void
	 */
	virtual void DharaniServerInitiallize() = 0;

	/**@brief	Ŭ���̾�Ʈ �� �ʱ�ȭ.
	 */
	virtual void DharaniClientInitiallize() = 0;
};

#endif


/**@defgroup	GroupDharani	Dharani protocol communication component
  *				Dharani ���������� ����ϴ� communication component.
  */