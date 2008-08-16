/*	Common Buisiness Framework Mediator */

#include "stdafx.h"
#include "CBFMediator.h"

void CCBFMediator::ReadDAM()
{
	CDataAdminBI *_interface = CDataAdminFacade::Instance();
	_interface->Read();
}