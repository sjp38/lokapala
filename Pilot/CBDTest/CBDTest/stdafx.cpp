// stdafx.cpp : source file that includes just the standard includes
// CBDTest.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

/**@brief	instance들의 초기값을 null로 잡아준다.
 */
#include "CBFMediator.h"
#include "SampleManagerFacade.h"
#include "SampleManager2Facade.h"
#include "SampleManager2SD.h"

//CBFMEdiator
CBFMediator *CBFMediator::m_instance = NULL;

//Facade
SampleManagerFacade *SampleManagerFacade::m_instance = NULL;
SampleManager2Facade *SampleManager2Facade::m_instance = NULL;

//Service Delegate
SampleManager2SD *SampleManager2SD::m_instance = NULL;