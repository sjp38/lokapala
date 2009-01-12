#include "stdafx.h"
#include "CBFMediator.h"

void CBFMediator::CallSampleManager(void)
{
	SampleManagerBI *_interface = SampleManagerFacade::Instance();
	_interface->CallSampleManager();
}

void CBFMediator::CallSampleManager2(void)
{
	SampleManager2BI *_interface = SampleManager2Facade::Instance();
	_interface->CallSampleManager2();
}