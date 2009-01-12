/**@file	CBFMediator.cpp
 * @brief	Common Buisiness Framework Mediator.
 * @author	siva
 */

#include "stdafx.h"
#include "CBFMediator.h"

/**@brief	������Ʈ �� ��� �׽�Ʈ�� ����Լ�. DAM���κ��� �����͸� �д´�.
 * @remarks		�ܼ��� �׽�Ʈ��. ���������� �ϴ� ���� ����;
 */
void CCBFMediator::ReadDAM()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->Read();
}