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


/**@brief	CCM�� ��� �ʱ�ȭ. ���� ������ �����ϱ� ���� ���� ������ �����ϰ� ���ͷκ����� ���� ��û�� �����Ѵ�.
 * @remarks	�ٶ�� ������Ʈ �׽�Ʈ ��.
 */
void CCBFMediator::InitiallizeCommunication()
{
	CCommunicationBI *_interface = CCommunicationFacade::Instance();
	_interface->Initiallize();
}